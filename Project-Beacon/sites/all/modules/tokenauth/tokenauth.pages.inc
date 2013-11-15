<?php

/**
 * @file
 *  Provides administrative user interface for Tokenauth module.
 */

/**
 * Menu callback for Tokenauth administration interface.
 */
function tokenauth_admin_settings() {
  $form = array();

  $form['tokenauth_general'] = array(
    '#type' => 'fieldset',
    '#title' => t('Token settings'),
  );
  $form['tokenauth_general']['tokenauth_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Token length'),
    '#size' => 4,
    '#maxlength' => 4,
    '#required' => TRUE,
    '#default_value' => variable_get('tokenauth_length', TOKENAUTH_DEFAULT_TOKEN_LENGTH),
    '#description' => t('Does not affect existing tokens.'),
  );
  $form['tokenauth_general']['tokenauth_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Activate tokens on specific pages'),
    '#default_value' => variable_get('tokenauth_pages', "rss.xml\n*/feed\n*/opml"),
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page. Read <a href=\"http://api.drupal.org/api/function/drupal_match_path/6\">drupal_match_path()</a> for the details.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
  );

  $text = tokenauth_text_load();
  $form['tokenauth_text'] = array(
    '#type' => 'text_format',
    '#title' => t('User text'),
    '#description' => t('This text will be displayed on a tab in each user\'s profile. Use it to explain what functionality Tokenauth provides your site.'),
    '#default_value' => $text['value'],
    '#format' => $text['format'],
    '#rows' => 5,
  );

  if (module_exists('token')) {
    $form['tokenauth_text']['token_help'] = array(
      '#title' => t('Replacement tokens'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 10,
    );
    $form['tokenauth_text']['token_help']['view'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('user'),
      '#global_types' => TRUE,
      '#click_insert' => TRUE,
    );
  }

  $form['tokenauth_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Token actions'),
    '#weight' => 15,
    '#description' => t('Reset the tokens for all users. If you have changed token length, be sure to save that change before resetting all tokens.'),
  );
  $form['tokenauth_advanced']['tokenauth_reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset tokens')
  );

  return system_settings_form($form);
}

/**
 * Validate callback.
 */
function tokenauth_admin_settings_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Reset tokens')) {
    drupal_goto('admin/settings/tokenauth/reset');
  }
  if ($form_state['values']['tokenauth_length'] > 33) {
    form_set_error('tokenauth_length', t('The maximum token length is 32.'));
  }
}

/**
 * Menu callback: confirm reset tokens.
 */
function tokenauth_reset_confirm() {
  return confirm_form(array(), t('Are you sure you want to reset all tokens?'),
           'admin/settings/tokenauth', t('After the tokens have been reset, all users who use tokenised URLs will have to update them. This action cannot be undone.'), t('Reset tokens'), t('Cancel'));
}

/**
 * Handler for reset tokens confirmation
 */
function tokenauth_reset_confirm_submit(&$form_state) {
  tokenauth_reset();
  drupal_set_message(t('All tokens have been reset.'));
  $form_state['#redirect']  = 'admin/settings/tokenauth';
}

/**
 * Menu callback: confirm reset users token.
 */
function tokenauth_user_reset_confirm() {
  if (arg(0) == 'user' && is_numeric(arg(1))) {
    $uid = arg(1);
  }
  return confirm_form(
    array('uid' => array('#type' => 'hidden', '#value' => $uid)),
    t('Are you sure you want to reset this user token?'),
    "user/$uid/tokenauth",
    t('After the token has been reset, please update your feed readers or other applications that depend on them. This action cannot be undone.'),
    t('Reset token'),
    t('Cancel')
  );
}

/**
 * Handler for reset tokens confirmation
 */
function tokenauth_user_reset_confirm_submit($form, &$form_state) {
  tokenauth_reset($form['uid']['#value']);
  drupal_set_message(t('The token has been reset.'));
  $form_state['redirect'] = 'user/' . $form['uid']['#value'] . '/tokenauth';
}

/**
 * Menu callback. Prints the token and instructions.
 */
function tokenauth_user_profile_form($form, &$form_state, $account) {
  drupal_set_title($account->name);
  $token = tokenauth_get_token($account->uid);
  $form['preamble'] = array('#markup' => tokenauth_text_load($account, TRUE));
  if (!module_exists('token')) {
    $key = tokenauth_get_token_key();
    $form['preamble']['#markup'] .= "<p><strong>" . t('Your token:') . "</strong> ?$key=<code>$token</code></p>";
  }
  $form = array_merge($form, tokenauth_reset_user_form($account->uid, NULL, $token));
  return $form;
}
