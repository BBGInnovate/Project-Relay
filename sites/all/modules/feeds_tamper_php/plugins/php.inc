<?php

/**
 * @file
 */

$plugin = array(
  'form'     => 'feeds_tamper_php_form',
  'callback' => 'feeds_tamper_php_callback',
  'name'     => 'Execute php code',
  'multi'    => 'direct',
  'category' => 'Other',
);

function feeds_tamper_php_form($importer, $element_key, $settings) {
  $form = array();

  $form['php'] = array(
    '#type' => 'textarea',
    '#title' => t('PHP code'),
    '#default_value' => isset($settings['php']) ? $settings['php'] : '',
    '#description' => t('This code will be executed. Use $field as value of this field. Do not use < ?php and ? >. <br />For example, use:      return substr($field, 0, 10);'),
  );
  return $form;
}

function feeds_tamper_php_callback($source, $item_key, $element_key, &$field, $settings) {
  $field = feeds_tamper_php_value($settings['php'], $field);
}

function feeds_tamper_php_value($code, $field) {
  ob_start(); 
  $code = eval($code);
  ob_end_clean(); 
  return $code;
}



