<?php

/**
 * @file
 * Builds profile-specific register, login, and password forms.
 */

/**
 * Page callback: Displays a user login form.
 *
 * Path: [path-setting]/login
 *
 * @param object $profiles
 *   Object containing single row from profile2_regpath_get_profiles() database
 *   result.
 *
 * @see profile2_regpath_menu()
 */
function _profile2_regpath_user_login($profiles) {
  module_load_include('pages.inc', 'user', 'user');
  $output = user_page();
  _profile2_regpath_set_title($profiles, 'login_title');
  return $output;
}

/**
 * Page callback: Displays a user registration form.
 *
 * Path: [path-setting]/register
 *
 * @param object object $profiles
 *   Object containing single row from profile2_regpath_get_profiles() database
 *   result.
 *
 * @see profile2_regpath_menu()
 */
function _profile2_regpath_user_register($profiles) {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_register_form');
  _profile2_regpath_set_title($profiles, 'register_title');
  return $output;
}

/**
 * Page callback: Displays the forgot password form.
 *
 * Path: [path-setting]/password
 *
 * @param object $profiles
 *   Object containing single row from profile2_regpath_get_profiles() database
 *   result.
 *
 * @see profile2_regpath_menu()
 */
function _profile2_regpath_user_password($profiles) {
  module_load_include('pages.inc', 'user', 'user');
  $output = drupal_get_form('user_pass');
  _profile2_regpath_set_title($profiles, 'password_title');
  return $output;
}

/**
 * Sets page title for registration, login, and forgot password pages.
 *
 * @param object $profiles
 *   Object containing single row from profile2_regpath_get_profiles() database
 *   result.
 *
 * @param string $key
 *   Array key for 'misc' array. This will determine the title settings.
 */
function _profile2_regpath_set_title($profiles, $key) {
  // Look for custom title in foremost profile, according to weight.
  if (isset($profiles[0]->misc) && $misc = unserialize($profiles[0]->misc)) {
    if (array_key_exists($key, $misc)) {
      $title = $misc[$key];
    }
  }
  // Set default title.
  else {
    $title = 'User account';
  }
  // Set title. See http://drupal.org/node/1800116 for use of t().
  drupal_set_title(t($title));
}