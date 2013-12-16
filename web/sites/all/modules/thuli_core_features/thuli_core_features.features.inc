<?php
/**
 * @file
 * thuli_core_features.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function thuli_core_features_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function thuli_core_features_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function thuli_core_features_flag_default_flags() {
  $flags = array();
  // Exported flag: "Vote up".
  $flags['vote_up'] = array(
    'entity_type' => 'node',
    'title' => 'Vote up',
    'global' => 0,
    'types' => array(
      0 => 'thuli',
    ),
    'flag_short' => 'Vote up',
    'flag_long' => 'Voting up a thuli means you acknowledge its contents and are adding your approval',
    'flag_message' => 'Done. Thanks for voting up!',
    'unflag_short' => 'Cancel Vote up',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'teaser' => 'teaser',
      'rss' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => FALSE,
    'i18n' => 0,
    'module' => 'thuli_core_features',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}

/**
 * Implements hook_image_default_styles().
 */
function thuli_core_features_image_default_styles() {
  $styles = array();

  // Exported image style: scaled_down_50x50.
  $styles['scaled_down_50x50'] = array(
    'name' => 'scaled_down_50x50',
    'label' => 'Scaled down 50x50',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 50,
          'height' => 50,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function thuli_core_features_node_info() {
  $items = array(
    'bid' => array(
      'name' => t('Bid'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'thuli' => array(
      'name' => t('Thuli'),
      'base' => 'node_content',
      'description' => t('A complaint or an idea.'),
      'has_title' => '1',
      'title_label' => t('Subject'),
      'help' => '',
    ),
    'web_page' => array(
      'name' => t('Web page'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
