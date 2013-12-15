<?php

/**
 * Implementation of hook_services_resources().
 */
function services_entity_services_resources() {
  $resources = array();

  foreach (entity_get_info() as $entity_type => $info) {
    if (entity_type_supports($entity_type, 'create')) {
      $resources["entity_$entity_type"]['create'] = array(
        'file' => array('type' => 'inc', 'module' => 'services_entity', 'name' => 'services_entity.resources'),
        'callback' => '_services_entity_resource_create',
        'description' => "Creates a $entity_type",
        'args' => array(
          array(
            'name' => 'entity_type',
            'optional' => TRUE,  // Otherwise throws an error
            'default value' => $entity_type,
            'type' => 'string',
            'description' => 'The type of the entity to create',
          ),
          array(
            'name' => 'values',
            'optional' => FALSE,
            'source' => 'data',
            'description' => 'The values used to create the entity',
            'type' => 'struct',
          ),
        ),
        'access callback' => '_services_entity_resource_access',
        'access arguments' => array('create'),
        'access arguments append' => TRUE,
      );
    }

    $resources["entity_$entity_type"]['retrieve'] = array(
      'file' => array('type' => 'inc', 'module' => 'services_entity', 'name' => 'services_entity.resources'),
      'callback' => '_services_entity_resource_retrieve',
      'description' => "Retrieves a $entity_type",
      'args' => array(
        array(
          'name' => 'entity_type',
          'optional' => TRUE,  // Otherwise throws an error
          'default value' => $entity_type,
          'type' => 'string',
          'description' => 'The type of the entity to get',
        ),
        array(
          'name' => $entity_type . '_id',
          'optional' => FALSE,
          'source' => array('path' => 0),
          'type' => 'int',
          'description' => 'The ID of the ' . $entity_type . ' to retrieve.',
        ),
        array(
          'name' => 'fields',
          'optional' => TRUE,
          'type' => 'string',
          'description' => 'A comma separated list of fields to get.',
          'default value' => '*',
          'source' => array('param' => 'fields'),
        ),
      ),
      'access callback' => '_services_entity_resource_access',
      'access arguments' => array('view'),
      'access arguments append' => TRUE,
    );

    if (entity_type_supports($entity_type, 'save')) {
      $resources["entity_$entity_type"]['update'] = array(
        'file' => array('type' => 'inc', 'module' => 'services_entity', 'name' => 'services_entity.resources'),
        'callback' => '_services_entity_resource_update',
        'description' => "Updates a $entity_type",
        'args' => array(
          array(
            'name' => 'entity_type',
            'optional' => TRUE,  // Otherwise throws an error
            'default value' => $entity_type,
            'type' => 'string',
            'description' => 'The type of the entity to update',
          ),
          array(
            'name' => $entity_type . '_id',
            'optional' => FALSE,
            'source' => array('path' => 0),
            'type' => 'int',
          'description' => 'The ID of the ' . $entity_type . ' to update.',
          ),
          array(
            'name' => 'values',
            'optional' => FALSE,
            'source' => 'data',
            'description' => 'The entity data to update',
            'type' => 'struct',
          ),
        ),
        'access callback' => '_services_entity_resource_access',
        'access arguments' => array('update'),
        'access arguments append' => TRUE,
      );
    }

    if (entity_type_supports($entity_type, 'delete')) {
      $resources["entity_$entity_type"]['delete'] = array(
        'file' => array('type' => 'inc', 'module' => 'services_entity', 'name' => 'services_entity.resources'),
        'callback' => '_services_entity_resource_delete',
        'description' => "Deletes a $entity_type",
        'args' => array(
          array(
            'name' => 'entity_type',
            'optional' => TRUE,  // Otherwise throws an error
            'default value' => $entity_type,
            'type' => 'string',
            'description' => 'The type of the entity to delete',
          ),
          array(
            'name' => $entity_type . '_id',
            'optional' => FALSE,
            'source' => array('path' => 0),
            'type' => 'int',
            'description' => 'The ID of the ' . $entity_type . ' to delete.',
          ),
        ),
        'access callback' => '_services_entity_resource_access',
        'access arguments' => array('delete'),
        'access arguments append' => TRUE,
      );
    }

    $resources["entity_$entity_type"]['index'] = array(
      'file' => array('type' => 'inc', 'module' => 'services_entity', 'name' => 'services_entity.resources'),
      'callback' => '_services_entity_resource_index',
      'description' => "Returns a list of $entity_type",
      'args' => array(
        array(
          'name' => 'entity_type',
          'optional' => TRUE,  // Otherwise throws an error
          'default value' => $entity_type,
          'type' => 'string',
          'description' => 'The type of the entity to get',
        ),
        /**
         * Fields to return
         *
         * these should be specified in a comma separated list like ?fields=title,created,uid
         */
        array(
          'name' => 'fields',
          'optional' => TRUE,
          'type' => 'string',
          'description' => 'A comma separated list of fields to get.',
          'default value' => '*',
          'source' => array('param' => 'fields'),
        ),
        /**
         * Filter parameters
         *
         * these should be specified by ?parameters[title]=My Title&param[created]=4403305
         */
        array(
          'name' => 'parameters',
          'optional' => TRUE,
          'type' => 'array',
          'description' => 'Filter parameters array such as parameters[title]="test"',
          'default value' => array(),
          'source' => array('param' => 'parameters'),
        ),
        /**
         * Page number
         *
         * A zero based page number like ?page=3 (returns the fourth page)
         */
        array(
          'name' => 'page',
          'optional' => TRUE,
          'type' => 'int',
          'description' => 'The zero-based index of the page to get, defaults to 0.',
          'default value' => 0,
          'source' => array('param' => 'page'),
        ),
        /**
         * Page Size
         *
         * How many records per page to return. ?pagesize=20
         */
        array(
          'name' => 'pagesize',
          'optional' => TRUE,
          'type' => 'int',
          'description' => 'Number of records to get per page.',
          'default value' => variable_get('services_entity_' . $entity_type . '_index_page_size', 20),
          'source' => array('param' => 'pagesize'),
        ),
        /**
         * Sort field
         *
         * Which field to sort on. ?sort=created
         */
        array(
          'name' => 'sort',
          'optional' => TRUE,
          'type' => 'string',
          'description' => 'Field to sort by.',
          'default value' => '',
          'source' => array('param' => 'sort'),
        ),
        /**
         * Sort Direction
         *
         * Which direction to sort. Possible Values = "ASC|DESC" ?direction=DESC
         */
        array(
          'name' => 'direction',
          'optional' => TRUE,
          'type' => 'string',
          'description' => 'Direction of the sort. ASC or DESC.',
          'default value' => 'ASC',
          'source' => array('param' => 'direction'),
        ),
      ),
      'access callback' => '_services_entity_resource_access',
      'access arguments' => array('index'),
      'access arguments append' => TRUE,
    );
  }

  return $resources;
}
