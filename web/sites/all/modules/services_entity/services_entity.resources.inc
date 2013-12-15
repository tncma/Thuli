<?php

/**
 * Services resource access callback.
 */
function _services_entity_resource_access($op, $args) {
  $resourceclass = variable_get('services_entity_resource_class', 'ServicesEntityResourceController');
  $resource = new $resourceclass;
  return $resource->access($op, $args);
}

/**
 * Services resource callback.
 */
function _services_entity_resource_create($entity_type, $values) {
  $resourceclass = variable_get('services_entity_resource_class', 'ServicesEntityResourceController');
  $resource = new $resourceclass;
  return $resource->create($entity_type, $values);
}

/**
 * Services resource callback.
 */
function _services_entity_resource_retrieve($entity_type, $entity_key, $fields) {
  $resourceclass = variable_get('services_entity_resource_class', 'ServicesEntityResourceController');
  $resource = new $resourceclass;
  return $resource->retrieve($entity_type, $entity_key, $fields);
}

/**
 * Services resource callback.
 */
function _services_entity_resource_update($entity_type, $entity_id, $values) {
  $resourceclass = variable_get('services_entity_resource_class', 'ServicesEntityResourceController');
  $resource = new $resourceclass;
  return $resource->update($entity_type, $entity_id, $values);
}

/**
 * Services resource callback.
 */
function _services_entity_resource_delete($entity_type, $entity_id) {
  $resourceclass = variable_get('services_entity_resource_class', 'ServicesEntityResourceController');
  $resource = new $resourceclass;
  return $resource->delete($entity_type, $entity_id);
}

/**
 * Services resource callback.
 */
function _services_entity_resource_index($entity_type, $fields, $parameters, $page, $pagesize, $sort, $direction) {
  $resourceclass = variable_get('services_entity_resource_class', 'ServicesEntityResourceController');
  $resource = new $resourceclass;
  return $resource->index($entity_type, $fields, $parameters, $page, $pagesize, $sort, $direction);
}
