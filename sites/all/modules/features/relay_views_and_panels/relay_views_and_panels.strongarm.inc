<?php
/**
 * @file
 * relay_views_and_panels.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function relay_views_and_panels_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_frontpage';
  $strongarm->value = 'front_page_panel';
  $export['site_frontpage'] = $strongarm;

  return $export;
}
