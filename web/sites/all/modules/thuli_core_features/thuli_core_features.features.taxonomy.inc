<?php
/**
 * @file
 * thuli_core_features.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function thuli_core_features_taxonomy_default_vocabularies() {
  return array(
    'municipality' => array(
      'name' => 'Municipality',
      'machine_name' => 'municipality',
      'description' => 'List of municipalities covered by Thuli',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
