<?php

/**
 * @file
 * Page callback for ajax links.
 */

/**
 * Returns USER LOGIN / REGITER / PASSWORD form.
 * @param $form_type
 *   Type of form that should be loaded.
 * @param $js
 *   Show whether user has enabled js in his browser.
 */
function ajax_register_page_callback($form_type, $js) {

  // Check whether js is enabled.
  if ($js) {

    // Include ctools modal plugin.
    ctools_include('modal');

    $form_state = array('ajax' => TRUE);

    // Array with ajax response.
    $commands = array();

    if ($form_type == 'password') {
      // Show USER PASSWORD form.
      module_load_include('pages.inc', 'user');
      $form_state['title'] = t('Request new password');
      $commands = ctools_modal_form_wrapper('user_pass', $form_state);
    }
    elseif ($form_type == 'register') {
      // Show USER REGISTER form.
      $form_state['title'] = t('Create new account');
      $commands = ctools_modal_form_wrapper('user_register_form', $form_state);
    }
    elseif ($form_type == 'login') {
      // Show USER LOGIN form.
      $form_state['title'] = t('Login');
      $commands = ctools_modal_form_wrapper('user_login', $form_state);
    }

    // If form was submited.
    if (!empty($form_state['executed'])) {
      $commands = _ajax_register_execute_form($form_type, $form_state);
    }
    return array('#type' => 'ajax', '#commands' => $commands);
  }
  else {
    // If user has no js support redirect him to standart drupal forms.
    drupal_goto('user/' . $form_type);
  }
}
