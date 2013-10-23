<?php

/**
 * @file
 * field_extract support for datetime field
 */

function field_extract_datetime_info() {
  return array(
    'callback' => 'field_extract_datetime_extract',
    'filepath' => drupal_get_path('module', 'field_extract') . '/includes/datetime.inc',
    'options' => array(
      'key' => 'format',
      'format' => 'short',
      'to_date' => FALSE,
    ),
  );
}

function field_extract_datetime_extract($item, $options = array()) {
  $custom = FALSE;
  $custom_format = '';
  if (strpos($options['format'], 'custom/')===0) {
    $custom = TRUE;
    list(, $custom_format) = explode('/', $options['format']);
    $options['format'] = 'custom';
    $options['format_type'] = 'medium';
  }
  else {
    // Required to handle a potential bug with variable_get()
    // differentiating upper and lower case in date format names.
    $options['format'] = $options['format_type'] = drupal_strtolower($options['format']);
  }

  $date = date_formatter_process($options['format'], $options['parent_entity_type'],
    $options['parent_entity'], $options['field_info'], $options['instance_info'],
    $options['langcode'], $item, array('settings' => array('format_type' => $options['format_type'])));

  $key = empty($options['to_date']) ? 'value' : 'value2';
  $timestamp = strtotime($date[$key]['local']['datetime']);

  if ($options['key']=='format') {
    switch ($options['format']) {
      case 'timestamp':
        $value = $timestamp;
        break;
      case 'custom':
        $value = format_date($timestamp, 'custom', $custom_format);
        break;
      default:
        $value = format_date($timestamp, $options['format']);
        break;
    }
  }
  else {
    $value = $item[$options['key']?$options['key']:'value'];
  }

  return $value;
}
