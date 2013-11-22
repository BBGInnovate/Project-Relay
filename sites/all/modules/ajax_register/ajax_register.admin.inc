<?php

/**
 * @file
 * Provides form with AJAX REGISTER module settings.
 */

/**
 * Administrative settings form.
 */
function ajax_register_admin_form($form, $form_state) {

  $form['ajax_register_modal'] = array(
    '#type' => 'fieldset',
    '#title' => t('Modal window settings'),
  );

  $form['ajax_register_modal']['ajax_register_modal_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Modal window width'),
    '#size' => 4,
    '#field_suffix' => 'px',
    '#default_value' => variable_get('ajax_register_modal_width', 550),
  );

  $form['ajax_register_modal']['ajax_register_modal_background_opacity'] = array(
    '#type' => 'select',
    '#title' => t('Background opacity'),
    '#options' => array(
      '0'   => '0%',
      '0.1' => '10%',
      '0.2' => '20%',
      '0.3' => '30%',
      '0.4' => '40%',
      '0.5' => '50%',
      '0.6' => '60%',
      '0.7' => '70%',
      '0.8' => '80%',
      '0.9' => '90%',
      '1'   => '100%',
    ),
    '#default_value' => variable_get('ajax_register_modal_background_opacity', '0.7'),
  );

  $form['ajax_register_modal']['ajax_register_modal_background_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Background color'),
    '#size' => 6,
    '#maxlength' => 6,
    '#field_prefix' => '#',
    '#default_value' => variable_get('ajax_register_modal_background_color', '000000'),
  );

  $form['ajax_register_modal']['ajax_register_hide_captcha'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide captcha in modal dialog'),
    '#description' => t('Capctha protects your site from spambots.
      But they have no js enabled, so spambots will never see modal dialog and will be redirected to normal login/register form with captcha.'),
    '#default_value' => variable_get('ajax_register_hide_captcha', FALSE),
  );

  if (!module_exists('captcha')) {
    $form['ajax_register_modal']['ajax_register_hide_captcha']['#disabled'] = TRUE;
    $form['ajax_register_modal']['ajax_register_hide_captcha']['#title'] .= ' (' . t('requires CAPTCHA module') . ')';
  }

  $form['ajax_register_forms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form settings'),
  );

  $form['ajax_register_forms']['ajax_register_form_enable_modal_links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable links in modal window'),
    '#description' => t('Check if links to another forms should appear in modal form'),
    '#default_value' => variable_get('ajax_register_form_enable_modal_links', TRUE),
  );

  $form['ajax_register_redirect'] = array(
    '#type' => 'fieldset',
    '#title' => t('Redirect behaviors'),
  );

  // Add redirect settings to the login form type.
  ajax_register_add_redirect_settings($form['ajax_register_redirect'], 'login');

  // Add redirect settings to the register form type.
  ajax_register_add_redirect_settings($form['ajax_register_redirect'], 'register');

  // Add redirect settings to the password form type.
  ajax_register_add_redirect_settings($form['ajax_register_redirect'], 'password');

  // Return the form.
  return system_settings_form($form);
}

/**
 * Adds standard redirect options to admin form for different form types.
 */
function ajax_register_add_redirect_settings(&$form, $form_type) {

  $form[$form_type] = array(
    '#type' => 'fieldset',
    '#title' => t(drupal_ucfirst($form_type) . ' Form'),
  );

  // Provide a list of redirect behaviors.
  $redirect_behaviors = array(
    'default' => t('Default'),
    'refresh' => t('Refresh'),
    'custom'  => t('Custom'),
    'none'    => t('No Redirect'),
  );

  // Only provide the no redirect behavior for non-login forms.
  if ($form_type == 'login') {
    array_pop($redirect_behaviors);
  }

  $redirect = variable_get('ajax_register_' . $form_type . '_redirect_behavior', 'default');
  $form[$form_type]['ajax_register_' . $form_type . '_redirect_behavior'] = array(
    '#form_type' => $form_type,
    '#type' => 'select',
    '#title' => t('Redirect Behavior'),
    '#options' => $redirect_behaviors,
    '#default_value' => $redirect,
  );

  $form[$form_type]['ajax_register_' . $form_type . '_redirect_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect URL'),
    '#description' => t('Enter the URL that the user will be redirected to after a successful login.'),
    '#default_value' => variable_get('ajax_register_' . $form_type . '_redirect_url', ''),
    '#states' => array(
      // Hide the settings when the redirect checkbox is has wrong value.
      'visible' => array(
        ':input[name="ajax_register_' . $form_type . '_redirect_behavior"]' => array('value' => 'custom'),
      ),
      'required' => array(
        ':input[name="ajax_register_' . $form_type . '_redirect_behavior"]' => array('value' => 'custom'),
      ),
    ),
  );

  // Provide descriptions for redirect behaviors.
  $redirect_descriptions = array(
    t('Default')     => t('After successful submission of the form, the redirect path is handled by Drupal and will redirect the user to whatever the $form_state["redirect"] variable is set to. NOTE: This option may be required if there are additional modules or features that handle the redirect logic.'),
    t('Refresh')     => t('After successful submission of the form, the page will be refreshed.'),
    t('Custom')      => t('After successful submission of the form, users will be redirected to this manually set custom URL.'),
    t('No Redirect') => t('After successful submission of the form, the modal window will simply close and not redirect the user to any location.'),
  );

  // Only provide the no redirect behavior for non-login forms.
  if ($form_type == 'login') {
    array_pop($redirect_descriptions);
  }

  // Theme descriptions as an item list.
  $items = array();
  foreach ($redirect_descriptions as $title => $description) {
    $items[] = '<strong>' . $title . '</strong> - ' . $description;
  }
  $redirect_description = theme('item_list', array('items' => $items));

  $form[$form_type]['ajax_register_' . $form_type . '_redirect_behavior']['#description'] = $redirect_description;
}
