<?php
/**
 * @file
 * thuli_core_features.features.language.inc
 */

/**
 * Implements hook_locale_default_languages().
 */
function thuli_core_features_locale_default_languages() {
  $languages = array();

  // Exported language: en.
  $languages['en'] = array(
    'language' => 'en',
    'name' => 'English',
    'native' => 'English',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 0,
    'formula' => '',
    'domain' => '',
    'prefix' => 'en',
    'weight' => 0,
  );
  // Exported language: ta.
  $languages['ta'] = array(
    'language' => 'ta',
    'name' => 'Tamil',
    'native' => 'தமிழ்',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 0,
    'formula' => '',
    'domain' => '',
    'prefix' => 'ta',
    'weight' => 0,
  );
  return $languages;
}
