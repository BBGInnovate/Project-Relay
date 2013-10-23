<?php

$plugin =  array(
    'title' => 'Field Collection',
    'types' => array('field_collection'),
    'form callback' => 'views_plugin_argument_default_field_field_collection_form',
    'argument callback' => 'views_plugin_argument_default_field_field_collection_argument',

  );


function views_plugin_argument_default_field_field_collection_form() {
  return array(
    'argument_default_field_field_collection_delta' => array(
      '#title' => 'Delta',
      '#type' => 'select',
      '#options' => array('all', 1, 2, 3, 4, 5, 6, 7, 8, 9),
    ),
  );
}
function views_plugin_argument_default_field_field_collection_argument($field, $options) {
  $delta  = isset($options['argument_default_field_field_collection_delta']) ? $options['argument_default_field_field_collection_delta'] : 0;
  $return = array();
  $field = $delta ? array($field[$delta]) : $field;
  foreach ($field as $item) {
    if (isset($item['value'])) {
      $value = $item['value'];
      $return[] = $value;
    }
  }
  //return False if we do not have any values
  if (empty($return)) {
    return FALSE;
  }
  return implode('+', $return);
}
