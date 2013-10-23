<?php

/**
 * @file
 * field_extract support for list_boolean field
 */

function field_extract_list_boolean_info() {
  return array(
    'callback' => 'field_extract_list_boolean_extract',
    'filepath' => drupal_get_path('module', 'field_extract') . '/includes/list_boolean.inc',
    'options' => array(
      'key' => 'value',
    ),
  );
}

function field_extract_list_boolean_extract($item, $options = array()) {
  if (isset($item[$options['key']])) {
    return (bool) (int) $item[$options['key']];
  }
}
