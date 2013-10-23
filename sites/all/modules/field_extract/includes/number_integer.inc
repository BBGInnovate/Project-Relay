<?php

/**
 * @file
 * field_extract support for number_integer field
 */

function field_extract_number_integer_info() {
  return array(
    'callback' => 'field_extract_number_integer_extract',
    'filepath' => drupal_get_path('module', 'field_extract') . '/includes/number_integer.inc',
    'options' => array(
      'key' => 'value',
    ),
  );
}

function field_extract_number_integer_extract($item, $options = array()) {
  if (isset($item[$options['key']])) {
    return (int) $item[$options['key']];
  }
}
