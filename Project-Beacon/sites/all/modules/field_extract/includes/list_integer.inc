<?php

/**
 * @file
 * field_extract support for list_integer field
 */

function field_extract_list_integer_info() {
  return array(
    'callback' => 'field_extract_list_integer_extract',
    'filepath' => drupal_get_path('module', 'field_extract') . '/includes/list_integer.inc',
    'options' => array(
      'key' => 'value',
    ),
  );
}

function field_extract_list_integer_extract($item, $options = array()) {
  if (isset($item[$options['key']])) {
    return (int) $item[$options['key']];
  }
}
