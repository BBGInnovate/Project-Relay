<?php

/**
 * @file
 * field_extract support for number_decimal field
 */

function field_extract_number_decimal_info() {
  return array(
    'callback' => 'field_extract_number_decimal_extract',
    'filepath' => drupal_get_path('module', 'field_extract') . '/includes/number_decimal.inc',
    'options' => array(
      'key' => 'value',
    ),
  );
}

function field_extract_number_decimal_extract($item, $options = array()) {
  if (isset($item[$options['key']])) {
    return 0 + $item[$options['key']];
  }
}
