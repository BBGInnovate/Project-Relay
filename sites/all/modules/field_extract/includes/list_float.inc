<?php

/**
 * @file
 * field_extract support for list_float field
 */

function field_extract_list_float_info() {
  return array(
    'callback' => 'field_extract_list_float_extract',
    'filepath' => drupal_get_path('module', 'field_extract') . '/includes/list_float.inc',
    'options' => array(
      'key' => 'value',
    ),
  );
}

function field_extract_list_float_extract($item, $options = array()) {
  if (isset($item[$options['key']])) {
    return (float) $item[$options['key']];
  }
}
