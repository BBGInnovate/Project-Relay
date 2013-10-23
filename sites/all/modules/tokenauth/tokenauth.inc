<?php
/**
 * @file
 * Provides tokenauth API for Token Authentication module.
 */

/**
 * API function to reset all tokens.
 *
 * @param $uid
 *  [optional] UID of a specific user to reset. Will default to resetting all users.
 * @param $token
 *  [optional] A specific string to use as the token. Defaults to a string generated randomly with user_password().
 * @param $update
 *  [optional] If true, will update the user's token entry. Otherwise will insert a new one.
 *
 * @return
 *  For a single user, returns token string. For multiple users, returns TRUE.
 */
function tokenauth_reset($uid = NULL, $token = NULL, $update = TRUE) {
  if (!is_null($uid)) {
    return tokenauth_reset_user($uid, $token, $update);
  }
  else {
    $sql = 'SELECT uid FROM {users} WHERE uid > 0';
    $results = db_query($sql);
    foreach ($results as $row) {
      tokenauth_reset_user($row->uid, $token, $update);
    }
    return TRUE;
  }
}

/**
 * API Function to reset a user's token.
 *
 * @param $uid
 *  [optional] User ID of the user whose token to reset. Defaults to current user.
 * @param $token
 *  [optional] A specific string to use as the token. Defaults to a string generated randomly with user_password().
 * @param $update
 *  [optional] If true, will update the user's token entry. Otherwise will insert a new one.
 *
 * @return
 *  The token string to which the user has been inserted/updated. FALSE if it fails.
 */
function tokenauth_reset_user($uid = NULL, $token = NULL, $update = TRUE) {
  if (is_null($uid)) {
    $uid = $GLOBALS['user']->uid;
  }
  $entry = array(
    'uid' => $uid,
    'token' => isset($token) ? $token : user_password(variable_get('tokenauth_length', TOKENAUTH_DEFAULT_TOKEN_LENGTH)),
  );
  if (!$update) {
    // drupal_write_record mysteriously failing from tokenauth_enable().
    $return = db_insert('tokenauth_tokens')
      ->fields($entry)
      ->execute();
  }
  else {
    $return = db_update('tokenauth_tokens')
      ->fields($entry)
      ->condition('uid', $entry['uid'])
      ->execute();
  }
  tokenauth_get_token($uid, TRUE);
  return $return === FALSE ? FALSE : $entry['token'];
}

/**
 * API Function to insert new user tokens.
 *
 * @param $uid
 *  [optional] UID of a specific user for whom to add a token.
 * @param $token
 *  [optional] A specific string to use as the token.
 */
function tokenauth_insert($uid = NULL, $token = NULL) {
  return tokenauth_reset($uid, $token, FALSE);
}

/**
 * API function for retrieving the token for a given user.
 *
 * @param string $uid
 *  Assumes current user if no user is provided.
 * @param $reset
 *  Whether to reset the internal cache.
 *
 * @return
 *  The user's token.
 */
function tokenauth_get_token($uid = NULL, $reset = FALSE) {
  static $tokens;
  if (is_null($uid)) {
    $uid = $GLOBALS['user']->uid;
  }
  if (!isset($tokens[$uid]) || $reset) {
    $sql = "SELECT token FROM {tokenauth_tokens} WHERE uid = :uid";
    $tokens[$uid] = db_query($sql, array(':uid' => $uid))->fetchField();
  }
  return $tokens[$uid];
}

/**
 * API function for retrieving the user for a given token.
 *
 * Note that while this filters out blocked users, it does not check whether the user has access to use tokenauth.
 *
 * @param $token
 *  An alphanumeric string.
 */
function tokenauth_get_user($token) {
  $sql = "SELECT tt.uid FROM {tokenauth_tokens} tt INNER JOIN {users} u ON tt.uid = u.uid WHERE token = :token AND u.status != 0";
  return db_query($sql, array(':token' => $token))->fetchField();
}

/**
 * Helper function to determine if the current path is tokenauth-enabled.
 *
 * @param $path
 *  The Drupal path to be checked for access.
 *
 * @return
 *   Return TRUE if current page may be viewed using only a token
 */
function tokenauth_allowed_pages($path) {
  $patterns = variable_get('tokenauth_pages', "rss.xml\n*/feed\n*/opml");
  if (drupal_match_path($path, $patterns)) {
    return TRUE;
  }
}

/**
 * Helper function to build a token reset form.
 */
function tokenauth_reset_user_form($uid, $label = NULL, $token = NULL) {
  $form = array();
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $uid
  );
  $form['tokenauth'] = array(
    '#type' => 'value',
    '#value' => $token
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => isset($label) ? $label :  t('Reset token')
  );
  $form['#action'] = url('user/' . $uid . '/tokenauth/reset');
  $form['#method'] = 'get';
  return $form;
}

/**
 * Helper function to pull tokenauth UI text from the variables table, and optionally render.
 *
 * @param $account
 *  User object for which the text will be pulled. Only useful in render mode.
 * @param $render
 *  Whether to pass along the raw text or render using specific input format. (And token replacement, if enabled.)
 */
function tokenauth_text_load($account = NULL, $render = FALSE) {
  $tokenauth_text = variable_get('tokenauth_text', array());

  if (empty($tokenauth_text)) {
    $tokenauth_text['value'] =<<<EOT
You may use an alphanumeric token to see restricted content using RSS Feed Readers or other simple content viewers. This token authenticates your user account, and as unique to you. If you have reason to believe someone else is misusing your token, please press the <em>Reset token</em> button to get a new one, and update your RSS readers.

Append the string below to the end of URLs approved for use with Token Authentication for temporary authentication.
EOT;

    if (module_exists('token')) {
      $key = tokenauth_get_token_key();
      $tokenauth_text['value'] .= "\n\n<strong>Your token:</strong> ?$key=<code>[user:tokenauth-token]</code>";
    }
    $tokenauth_text['format'] = filter_format_exists('filtered_html') ? 'filtered_html' : filter_fallback_format();
  }
  if (!$render) {
    return $tokenauth_text;
  }
  if (module_exists('token')) {
    if (empty($account)) {
      $account = $GLOBALS['user'];
    }
    $tokenauth_text['value'] = token_replace($tokenauth_text['value'], array('user' => $account));
  }

  return check_markup($tokenauth_text['value'], $tokenauth_text['format']);
}
