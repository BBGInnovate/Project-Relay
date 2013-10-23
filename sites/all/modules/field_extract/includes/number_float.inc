<?php

/**
 * @file
 * field_extract support for number_float field
 */

function field_extract_number_float_info() {
  return array(
    'callback' => 'field_extract_number_float_extract',
    'filepath' => drupal_get_path('module', 'field_extract') . '/includes/number_float.inc',
    'options' => array(
      'key' => 'value',
    ),
  );
}

function field_extract_number_float_extract($item, $options = array()) {
  if (isset($item[$options['key']])) {
    return (float) $item[$options['key']];
  }
}
