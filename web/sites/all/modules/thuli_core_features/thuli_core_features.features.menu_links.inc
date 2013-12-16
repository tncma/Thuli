<?php
/**
 * @file
 * thuli_core_features.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function thuli_core_features_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: user-menu_explore-thulis:thulis/explore
  $menu_links['user-menu_explore-thulis:thulis/explore'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'thulis/explore',
    'router_path' => 'thulis/explore',
    'link_title' => 'Explore Thulis',
    'options' => array(
      'identifier' => 'user-menu_explore-thulis:thulis/explore',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: user-menu_leaderboard:leaderboard
  $menu_links['user-menu_leaderboard:leaderboard'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'leaderboard',
    'router_path' => 'leaderboard',
    'link_title' => 'Leaderboard',
    'options' => array(
      'identifier' => 'user-menu_leaderboard:leaderboard',
      'attributes' => array(),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: user-menu_log-out:user/logout
  $menu_links['user-menu_log-out:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'identifier' => 'user-menu_log-out:user/logout',
      'html' => 1,
      'attributes' => array(),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: user-menu_manage-thulis:thulis/manage
  $menu_links['user-menu_manage-thulis:thulis/manage'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'thulis/manage',
    'router_path' => 'thulis/manage',
    'link_title' => 'Manage Thulis',
    'options' => array(
      'identifier' => 'user-menu_manage-thulis:thulis/manage',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: user-menu_my-points:myuserpoints
  $menu_links['user-menu_my-points:myuserpoints'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'myuserpoints',
    'router_path' => 'myuserpoints',
    'link_title' => 'My !points',
    'options' => array(
      'identifier' => 'user-menu_my-points:myuserpoints',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: user-menu_my-thulis:my-thulis
  $menu_links['user-menu_my-thulis:my-thulis'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'my-thulis',
    'router_path' => 'my-thulis',
    'link_title' => 'My Thulis',
    'options' => array(
      'identifier' => 'user-menu_my-thulis:my-thulis',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: user-menu_span-classglyphicon-glyphicon-editspan-post-a-thuli:node/add/thuli
  $menu_links['user-menu_span-classglyphicon-glyphicon-editspan-post-a-thuli:node/add/thuli'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/thuli',
    'router_path' => 'node/add/thuli',
    'link_title' => '<span class="glyphicon glyphicon-edit"></span> Post a Thuli',
    'options' => array(
      'identifier' => 'user-menu_span-classglyphicon-glyphicon-editspan-post-a-thuli:node/add/thuli',
      'attributes' => array(),
      'html' => 1,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
  );
  // Exported menu link: user-menu_user-account:user
  $menu_links['user-menu_user-account:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
      'identifier' => 'user-menu_user-account:user',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('<span class="glyphicon glyphicon-edit"></span> Post a Thuli');
  t('Explore Thulis');
  t('Leaderboard');
  t('Log out');
  t('Manage Thulis');
  t('My !points');
  t('My Thulis');
  t('User account');


  return $menu_links;
}
