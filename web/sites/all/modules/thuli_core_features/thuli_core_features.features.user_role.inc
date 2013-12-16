<?php
/**
 * @file
 * thuli_core_features.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function thuli_core_features_user_default_roles() {
  $roles = array();

  // Exported role: citizen.
  $roles['citizen'] = array(
    'name' => 'citizen',
    'weight' => 4,
  );

  // Exported role: junior officer.
  $roles['junior officer'] = array(
    'name' => 'junior officer',
    'weight' => 2,
  );

  // Exported role: senior officer.
  $roles['senior officer'] = array(
    'name' => 'senior officer',
    'weight' => 3,
  );

  return $roles;
}
