<?php
/**
 * @file
 * thuli_core_features.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function thuli_core_features_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['locale-language_content'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'language_content',
    'module' => 'locale',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'shiny' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'shiny',
        'weight' => 0,
      ),
      'thuli_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'thuli_theme',
        'weight' => 0,
      ),
      'zen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'zen',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-help'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'help',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'shiny' => array(
        'region' => 'help',
        'status' => 1,
        'theme' => 'shiny',
        'weight' => 5,
      ),
      'thuli_theme' => array(
        'region' => 'help',
        'status' => 1,
        'theme' => 'thuli_theme',
        'weight' => 5,
      ),
      'zen' => array(
        'region' => 'help',
        'status' => 1,
        'theme' => 'zen',
        'weight' => 5,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-main'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'main',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'shiny' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'shiny',
        'weight' => 0,
      ),
      'thuli_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'thuli_theme',
        'weight' => 0,
      ),
      'zen' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'zen',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-powered-by'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'powered-by',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'shiny' => array(
        'region' => 'footer',
        'status' => 1,
        'theme' => 'shiny',
        'weight' => 10,
      ),
      'thuli_theme' => array(
        'region' => 'footer',
        'status' => 1,
        'theme' => 'thuli_theme',
        'weight' => 10,
      ),
      'zen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'zen',
        'weight' => 10,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
