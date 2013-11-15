<?php

/**
 * @file
 *   Subscriptions to Organic Groups.
 */

/**
 *  Site-wide settings form.
 */
function og_notifications_settings_form($form, &$form_state) {
  // Build check boxes table with content types x subscription types
  $form['og'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enabled subscription types'),
    '#weight' => -10,
    '#collapsible' => TRUE,
    '#description' => t('Check the subscription types that will be enabled. You can use the global settings here or set different options for each content type.'),
  );
  $form['og']['og_notifications'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Global options'),
    '#options' => _og_notifications_get_group_types(),
    '#default_value' => variable_get('og_notifications', array()),
    '#description' => t('Content types for which subscriptions will be enabled.'),
  );

  return system_settings_form($form);
}
