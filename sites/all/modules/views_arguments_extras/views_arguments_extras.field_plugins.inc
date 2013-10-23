<?php

function views_arguments_extras_get_plugin_options() {
  $fields = field_info_fields();
  $options = array();
  $plugins = array();
  $plugins = views_plugin_argument_default_field();
  $type_selector = array();
  // find all types that are useed and which fields use them
  $types = array();
  foreach ($fields as $key => $field) {
    $types[$field['type']][$key] = $key;
  }
  foreach ($plugins as $id => $plugin) {
    if (array_intersect($plugin['types'], array_keys($types))) {
      //build info for type select box
      foreach ($plugin['types'] as $type_name) {
        foreach ($types[$type_name] as $fid => $fname) {
          $options[$plugin['title']]["$id::$fid"] = $fname;
        }
      }
    }
  }
  return $options;
}



