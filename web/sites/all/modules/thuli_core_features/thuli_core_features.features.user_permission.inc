<?php
/**
 * @file
 * thuli_core_features.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function thuli_core_features_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access comments'.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access site-wide contact form'.
  $permissions['access site-wide contact form'] = array(
    'name' => 'access site-wide contact form',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'access user contact forms'.
  $permissions['access user contact forms'] = array(
    'name' => 'access user contact forms',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'citizen' => 'citizen',
      'junior officer' => 'junior officer',
      'senior officer' => 'senior officer',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer comments'.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(),
    'module' => 'comment',
  );

  // Exported permission: 'administer contact forms'.
  $permissions['administer contact forms'] = array(
    'name' => 'administer contact forms',
    'roles' => array(
      'senior officer' => 'senior officer',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'junior officer' => 'junior officer',
      'senior officer' => 'senior officer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'create bid content'.
  $permissions['create bid content'] = array(
    'name' => 'create bid content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create thuli content'.
  $permissions['create thuli content'] = array(
    'name' => 'create thuli content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any bid content'.
  $permissions['delete any bid content'] = array(
    'name' => 'delete any bid content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any thuli content'.
  $permissions['delete any thuli content'] = array(
    'name' => 'delete any thuli content',
    'roles' => array(
      'junior officer' => 'junior officer',
      'senior officer' => 'senior officer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own bid content'.
  $permissions['delete own bid content'] = array(
    'name' => 'delete own bid content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own thuli content'.
  $permissions['delete own thuli content'] = array(
    'name' => 'delete own thuli content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any bid content'.
  $permissions['edit any bid content'] = array(
    'name' => 'edit any bid content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any thuli content'.
  $permissions['edit any thuli content'] = array(
    'name' => 'edit any thuli content',
    'roles' => array(
      'junior officer' => 'junior officer',
      'senior officer' => 'senior officer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own bid content'.
  $permissions['edit own bid content'] = array(
    'name' => 'edit own bid content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(),
    'module' => 'comment',
  );

  // Exported permission: 'edit own thuli content'.
  $permissions['edit own thuli content'] = array(
    'name' => 'edit own thuli content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'flag vote_up'.
  $permissions['flag vote_up'] = array(
    'name' => 'flag vote_up',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'unflag vote_up'.
  $permissions['unflag vote_up'] = array(
    'name' => 'unflag vote_up',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'view own userpoints'.
  $permissions['view own userpoints'] = array(
    'name' => 'view own userpoints',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'citizen' => 'citizen',
      'junior officer' => 'junior officer',
      'senior officer' => 'senior officer',
    ),
    'module' => 'userpoints',
  );

  // Exported permission: 'view userpoints'.
  $permissions['view userpoints'] = array(
    'name' => 'view userpoints',
    'roles' => array(
      'citizen' => 'citizen',
      'junior officer' => 'junior officer',
      'senior officer' => 'senior officer',
    ),
    'module' => 'userpoints',
  );

  return $permissions;
}
