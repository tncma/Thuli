<?php

/**
 * Generic controller for entity-bases resources.
 */
class ServicesEntityResourceController implements ServicesResourceControllerInterface {

  /**
   * Implements ServicesResourceControllerInterface::access().
   */
  public function access($op, $args) {
    if ($op == 'index') {
      // Access is handled per-entity by index().
      return TRUE;
    }
    if ($op == 'create') {
      list($entity_type) = $args;
      // Pass the entity to the access control.
      return entity_access($op, $entity_type);
    }
    else {
      // Retrieve, Delete, Update.
      list($entity_type, $entity_id) = $args;

      $entity = entity_load_single($entity_type, $entity_id);

      // Pass the entity to the access control.
      return entity_access($op, $entity_type, $entity ? $entity : NULL);
    }
  }

  /**
   * Implements ServicesResourceControllerInterface::create().
   */
  public function create($entity_type, array $values) {
    $entity = entity_create($entity_type, $values);
    entity_save($entity_type, $entity);
    list($id, ) = entity_extract_ids($entity_type, $entity);

    // Check we got an ID back for the new entity.
    if (!isset($id)) {
      services_error('Error saving entity.', 406);
    }

    return $entity;
  }

  /**
   * Implements ServicesResourceControllerInterface::retrieve().
   */
  public function retrieve($entity_type, $entity_id, $fields) {
    $entity = entity_load_single($entity_type, $entity_id);
    if (!$entity) {
      services_error('Entity not found', 404);
    }
    // Users get special treatment to remove sensitive data.
    if ($entity_type == 'user') {
      // Use the helper that Services module already has.
      services_remove_user_data($entity);
    }
    services_remove_user_data($entity);
    return $this->limit_fields($entity, $fields);
  }

  /**
   * Implements ServicesResourceControllerInterface::update().
   */
  public function update($entity_type, $entity_id, array $values) {
    $wrapper = entity_metadata_wrapper($entity_type, (object) $values);
    if ($entity_id == $wrapper->getIdentifier()) {
      $wrapper->save();
      return $wrapper->value();
    }
    else {
      services_error('Invalid Entity Identifier. You can only update the entity referenced in the URL.', 406);
    }
  }

  /**
   * Implements ServicesResourceControllerInterface::delete().
   */
  public function delete($entity_type, $entity_id) {
    entity_delete($entity_type, $entity_id);
  }

  /**
   * Implements ServicesResourceControllerInterface::index().
   */
  public function index($entity_type, $fields, $parameters, $page, $pagesize, $sort, $direction) {
    // Make sure the pagesize is not too large.
    $max_pagesize = variable_get('services_entity_max_pagesize', 100);
    $pagesize = ($max_pagesize < $pagesize) ? $max_pagesize : $pagesize;

    // Build an EFQ based on the arguments.
    $query = new EntityFieldQuery();
    $query
        ->entityCondition('entity_type', $entity_type)
        ->range($page * $pagesize, $pagesize);

    if (!empty($parameters)) {
      foreach ($parameters as $field => $value) {
        $this->propertyQueryOperation($entity_type, $query, 'Condition', $field, $value);
      }
    }
    if ($sort != '') {
      $direction = ($direction == 'DESC') ? 'DESC' : 'ASC'; // Ensure a valid direction
      $this->propertyQueryOperation($entity_type, $query, 'OrderBy', $sort, $direction);
    }

    $result = $query->execute();

    if (empty($result)) {
      return services_error(t('No entities found.'), 404);
    }
    // Convert to actual entities.
    $entities = entity_load($entity_type, array_keys($result[$entity_type]));

    foreach ($entities as $id => $entity) {
      if (entity_access('view', $entity_type, $entity)) {
        // Users get special treatment to remove sensitive data.
        if ($entity_type == 'user') {
          // Use the helper that Services module already has.
          services_remove_user_data($entity);
        }

        $return[] = $this->limit_fields($entity, $fields);
      }
    }

    // The access check may have resulted in there being no entities left.
    if (empty($return)) {
      return services_error(t('No entities found.'), 404);
    }

    return $return;
  }

  /**
   * Implements ServicesResourceControllerInterface::field().
   */
  public function field($entity_type, $entity_id, $field_name, $fields = '*', $raw = FALSE) {
    $entity = entity_load_single($entity_type, $entity_id);
    if (!$entity) {
      services_error('Entity not found', 404);
    }

    $wrapper = entity_metadata_wrapper($entity_type, $entity_id);
    if ($raw) {
      $return = $wrapper->{$field_name}->raw();
    }
    else {
      $return = $wrapper->{$field_name}->value();
    }

    $field = field_info_field($field_name);

    // Special handling for entityreference fields: run the new entities through
    // limit fields.
    if ($field['type'] == 'entityreference' && !$raw) {
      $entities = $return;
      $return = array();

      foreach ($entities as $id => $entity) {
        // The entity type here is the target type of the entityreference field.
        if (entity_access('view', $field['settings']['target_type'], $entity)) {
          $return[] = $this->limit_fields($entity, $fields);
        }
      }
    }

    return $return;
  }

  /**
   * Limit the fields in an entity to the list provided.
   *
   * @param $entity
   *  The entity to limit the fields of.
   * @param $fields
   *  A list of field names. '*' is a wildcard, and leaves the entity unchanged.
   *
   * @return
   *  The entity with any property not specified in $fields removed from it.
   */
  protected function limit_fields($entity, $fields) {
    if ($fields == '*') {
      return $entity;
    }
    $field_array = explode(',', $fields);
    foreach ($entity as $field => $value) {
      if (!in_array($field, $field_array)) {
        unset($entity->{$field});
      }
    }
    return $entity;
  }

  /**
   * Helper function for adding a property to an EntityFieldQuery.
   *
   * This takes care of distinguishing between fields and entity properties when
   * adding a condition or ordering to an EntityFieldQuery. It executes the
   * right EntityFieldQuery method to add the property to the query.
   *
   * @param string $entity_type
   *   The entity type for the query.
   * @param EntityFieldQuery $query
   *   The EntityFieldQuery object.
   * @param string $operation
   *   The general method name, without the words 'property' or 'field'. E.g.,
   *   one of 'Condition' or 'OrderBy'.
   * @param string $property
   *   The name of the raw property or field which is to be added to the query.
   * @param string|array $value
   *   The value for the function.
   */
  protected function propertyQueryOperation($entity_type, EntityFieldQuery $query, $operation, $property, $value) {
    // First pass: check the entity's table schema.
    // Get the database schema for the entity's table.
    $entity_info = entity_get_info($entity_type);
    $schema = drupal_get_schema($entity_info['base table']);
    if (isset($schema['fields'][$property])) {
      // If the property is defined in the schema, use the schema property.
      // The EFQ method is either 'propertyCondition' or 'OrderByCondition'.
      $operation = 'property' . $operation;
      $query->$operation($property, $value);
      return;
    }

    // Second pass: check fields.
    // Get the metadata property info for the entity type, including properties
    // for all bundles.
    $properties = entity_get_all_property_info($entity_type);
    if (isset($properties[$property]) && !empty($properties[$property]['field'])) {
      // For fields we need the field info to get the right column for the
      // query.
      $field_info = field_info_field($property);
      $operation = 'field' . $operation;
      if (is_array($value)) {
        // Specific column filters are given, so add a query condition for each
        // one of them.
        foreach ($value as $column => $val) {
          $query->$operation($field_info, $column, $val);
        }
      }
      else {
        // Just pick the first field column for the operation.
        $columns = array_keys($field_info['columns']);
        $column = $columns[0];
        $query->$operation($field_info, $column, $value);
      }

      return;
    }

    // Still here if no matching property was found.
    services_error(t('Parameter @prop does not exist', array('@prop' => $property)), 406);
  }

}
