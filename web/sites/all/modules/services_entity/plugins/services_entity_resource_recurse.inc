<?php
/**
 * Class that allows following field entities recursively.
 */
class ServicesEntityResourceControllerRecurse extends ServicesEntityResourceController {

  public function retrieve($entity_type, $entity_id, $fields) {
    $fields = explode(',', $fields);
    // Build an EFQ to retrieve the entity. This also satisfies access control.
    $query = new EntityFieldQuery();
    $query
        ->entityCondition('entity_type', $entity_type)
        ->addTag('service_entity_resource')
        ->addMetaData('entity_type', $entity_type);

    // If there's no : in the entity key, we're looking for the id.
    if (strpos($entity_key, ':') == 0) {
      $query->entityCondition('entity_id', $entity_id);
  }
    else {
      // First split the property key and the value.
      list($key, $value) = explode(':', $entity_id);
      // We need to be sure that is a unique property to avoid multiple results
      // index option should be used instead.
      $info = entity_get_info($entity_type);
      $schema = drupal_get_schema($info['base table']);
      if (!empty($schema['unique keys'][$key])) {
        $query->propertyCondition($key, $value);
      }
      else {
        // If this is not a unique property, avoid doing the query.
        return services_error(t('Loading an entity using a non unique property is not allowed.'), 404);
      }
    }

    $entities = $query->execute();

    if (!empty($query->ordered_results)) {
      $result = $this->postprocess_entities($entities, $query->ordered_results, $fields);
      return reset($result);
    }
    else {
      return services_error(t('No entities retrieved.'), 404);
    }
  }

  public function index($entity_type, $fields, $parameters, $page, $pagesize, $sort, $direction) {
    $fields = explode(',', $fields);
    // Build an EFQ based on the arguments.
    $query = new EntityFieldQuery();
    $query
            ->entityCondition('entity_type', $entity_type)
            ->range($page * $pagesize, $pagesize);

    if (!empty($bundle)) {
      $query->entityCondition('bundle', $bundle, '=');
    }

    $entities = $query->execute();

    if (empty($entities)) {
      return services_error(t('No entities found.'), 404);
    }

    return $this->postprocess_entities($entities, $query->ordered_results, $fields);
  }

  protected function postprocess_entities($entities, $ordered_results, $fields) {
    // Prepare the fields.
    $fields = $this->transform_fields($fields);

    // Load the full entities.
    foreach ($entities as $entity_type => &$entities_of_type) {
      $entities_of_type = entity_load($entity_type, array_keys($entities_of_type));

      // Allow other modules to modify the returned entities.
      drupal_alter('services_entity_postprocess', $entities_of_type, $entity_type);
    }

    // Now return the entities in the correct order.
    $result = array();
    foreach ($ordered_results as $partial_entity) {
      if (isset($entities[$partial_entity->entity_type][$partial_entity->entity_id])) {
        $entity = $entities[$partial_entity->entity_type][$partial_entity->entity_id];

        if (!entity_access('view', $entity_type, $entity)) {
          continue;
        }

        $wrapper = entity_metadata_wrapper($partial_entity->entity_type, $entity);
        $entity_result = (object) $this->prepare_structure($wrapper, $fields);
        if (!empty($entity_result)) {
          $entity_result->uri = services_resource_uri(array('entity_' . $partial_entity->entity_type, $partial_entity->entity_id));
        }

        $result[] = $entity_result;
      }
    }

    // Allow other modules to alter the returned result.
    drupal_alter('services_entity_postprocess_result', $result, $partial_entity->entity_type);

    return $result;
  }

  /**
   * Recursive function to get all fields and the children of those fields
   * noted by field_name:child_name.
   */
  protected function transform_fields(array $fields) {
    $transformed_fields = array();
    foreach ($fields as $field) {
      if (!strpos($field, ':') == 0) {
        list($parent, $child) = explode(':', $field, 2);
        $value = $this->transform_fields(array($child));
        $transformed_fields[$parent] = isset($transformed_fields[$parent]) ? array_merge_recursive($transformed_fields[$parent], $value) : $value;
      }
      else {
        $transformed_fields[$field] = $field;
      }
    }

    return $transformed_fields;
  }
  /**
   * Prepare data structrure recursively and using metadata wrapper to retrieve
   * the hierarchical properties.
   */
  protected function prepare_structure(EntityStructureWrapper $wrapper, array $properties = array()) {
    if (empty($properties)) {
      // By default, expand all the non-computed properties.
      $properties = array();
      foreach ($wrapper->getPropertyInfo() as $property_name => $property_info) {
        if (empty($property_info['computed'])) {
          $properties[$property_name] = $property_name;
        }
      }
    }

    return $this->_prepare_structure($wrapper, $properties);
  }

  private function _prepare_structure(EntityMetadataWrapper $wrapper, array $fields) {
    $result = array();

    foreach ($fields as $property_name => $sub_properties) {
      $property_wrapper = $wrapper->$property_name;
      $type = $property_wrapper->type();
      $info = $property_wrapper->info();

      if (!empty($info['field'])) {
        $field_info = field_info_field($property_name);
        $translatable = !empty($field_info['translatable']) ? 1 : 0;
        $cardinality = $field_info['cardinality'];

        // Fetch the list of actual languages for this field in the underlying entity.
        $underlying_entity = $wrapper->value();
        $languages = isset($underlying_entity->$property_name) ? array_keys($underlying_entity->$property_name) : array();
      }
      else {
        $translatable = 0;
        $cardinality = $type == 'list' || entity_property_list_extract_type($type) ? -1 : 1;
        $languages = array(LANGUAGE_NONE);
      }

      // Remove the inner list layer.
      if ($sub_type = entity_property_list_extract_type($type)) {
        $type = $sub_type;
        $is_list = TRUE;
      }
      else {
        $is_list = FALSE;
      }

      // Now iterate on the list of languages to fetch the values.
      $property_result = array();
      foreach ($languages as $language) {
        $wrapper->language($language);
        $property_wrapper = $wrapper->$property_name;

        foreach ($is_list ? $property_wrapper : array($property_wrapper) as $index => $sub_wrapper) {
          if ($sub_wrapper instanceof EntityStructureWrapper) {
            // Required because Entity API doesn't propagate the language for us.
            $sub_wrapper->language($language);
          }

          if (is_array($sub_properties)) {
            $property_result[$language][$index] = $this->prepare_structure($sub_wrapper, $sub_properties);
          }
          else {
            $value = $sub_wrapper->raw();
            if (is_array($value)) {
              $property_result[$language][$index] = $value;
            }
            else {
              $property_result[$language][$index] = array(
                'value' => $type == 'boolean' && !$value ? '0' : $value,
              );
            }
          }
        }
      }

      if (count($property_result)) {
        $result[$property_name] = $property_result + array(
          'type' => $type,
          'cardinality' => $cardinality,
          'translatable' => $translatable,
        );
      }
      else {
        $result[$property_name] = NULL;
      }

    }

    return $result;
  }
}