<?php
/**
 * @file
 * Views module hooks for the Video.js module.
 */

/**
 * Implements hook_views_plugins().
 */
function videojs_views_plugins() {
  $path = drupal_get_path('module', 'videojs');

  return array();
}
