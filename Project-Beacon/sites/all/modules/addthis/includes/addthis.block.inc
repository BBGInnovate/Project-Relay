<?php

/**
 * @file
 * Block related hook implementations for the AddThis-module.
 */

/**
 * Implements hook_block_info().
 */
function addthis_block_info() {
  $block_info = array();
  $block_info[AddThis::BLOCK_NAME] = array(
    'info' => t('AddThis'),
    'cache' => DRUPAL_NO_CACHE,
  );
  return $block_info;
}

/**
 * Implements hook_block_view().
 *
 * #block key allows alter hooks to react on this information. Someone might
 * want to change this specific display.
 */
function addthis_block_view($block_name = '') {
  if ($block_name == AddThis::BLOCK_NAME) {
    $widget_type = AddThis::getInstance()->getBlockDisplayType();
    $markup = AddThis::getInstance()->getDisplayMarkup($widget_type, array('#block' => AddThis::BLOCK_NAME));
    return array(
      'subject' => '',
      'content' => $markup,
    );
  }
}

/**
 * Implements hook_block_configure().
 */
function addthis_block_configure($delta = '') {
  $form[AddThis::BLOCK_WIDGET_TYPE_KEY] = array(
    '#type' => 'select',
    '#title' => t('AddThis display type'),
    '#options' => AddThis::getInstance()->getDisplayTypes(),
    '#default_value' => AddThis::getInstance()->getBlockDisplayType(),
  );
  return $form;
}

/**
 * Implements hook_block_save().
 */
function addthis_block_save($delta = '', $edit = array()) {
  variable_set(AddThis::BLOCK_WIDGET_TYPE_KEY, $edit[AddThis::BLOCK_WIDGET_TYPE_KEY]);
}
