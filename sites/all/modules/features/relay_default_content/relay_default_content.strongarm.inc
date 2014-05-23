<?php
/**
 * @file
 * relay_default_content.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function relay_default_content_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_relay_article';
  $strongarm->value = '0';
  $export['comment_relay_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_relay_video';
  $strongarm->value = '0';
  $export['comment_relay_video'] = $strongarm;

  return $export;
}