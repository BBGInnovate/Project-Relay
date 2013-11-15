<?php

/**
 * @file
 *  Tokenauth drush commands.
 */

/**
 * Implements hook_drush_command().
 */
function tokenauth_drush_command() {
  $items = array();

  $items['tokenauth-reset'] = array(
    'description' => 'Reset the tokenauth token for the specified user.',
    'examples' => array(
      'drush tokenauth-reset 3' => 'Reset the token for user/3.',
      'drush tokenauth-reset bob' => 'Reset the token for user "bob".',
    ),
    'arguments' => array(
      'user' => 'Specify a user whose token to reset. You may use uid or username.',
    ),
    'drupal dependencies' => array('tokenauth'),
  );
  $items['tokenauth-reset-all'] = array(
    'description' => 'Reset the tokenauth token for all users.',
    'examples' => array(
      'drush tokenauth-reset-all' => 'Reset the tokens for all users.',
    ),
    'drupal dependencies' => array('tokenauth'),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function tokenauth_drush_help($section) {
  switch ($section) {
    case 'drush:tokenauth-reset':
      return dt('Reset the Token Authentication token for one user.');
    case 'drush:tokenauth-reset-all':
      return dt('Reset the Token Authentication token for all users.');
  }
}

/**
 * Drush command callback for "tokenauth-reset".
 */
function drush_tokenauth_reset($user = NULL) {
  if (is_null($user)) {
    drush_log(dt('No user specified.'), 'warning');
    return;
  }
  elseif (is_numeric($user)) {
    $account = user_load($user);
  }
  else {
    $account = user_load_by_name($user);
  }
  if (!$account) {
    drush_log(dt('User !user does not exist.', array('!user' => $user)), 'warning');
    return;
  }

  $message = dt('Are you sure you want to reset the token of user !user <!uid>?',
    array('!user' => $account->name, '!uid' => $account->uid)
  );

  if (!drush_confirm($message)) {
    return;
  }

  $return = tokenauth_reset($account->uid);
  if ($return !== FALSE) {
    drush_log(dt('Token has been reset.'), 'success');
    return;
  }
  drush_log(dt('Token failed to reset.'), 'error');
}

/**
 * Drush command callback for "tokenauth-reset-all".
 */
function drush_tokenauth_reset_all() {
  if (!drush_confirm(dt('Are you sure you want to reset all Token Authentication tokens?'))) {
    return;
  }

  $return = tokenauth_reset();
  if ($return !== FALSE) {
    drush_log(dt('Tokens have been reset.'), 'success');
    return;
  }
  drush_log(dt('Tokens failed to reset.'), 'error');
}
