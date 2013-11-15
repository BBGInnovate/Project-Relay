<?php
/**
 * @file
 * The admin settings for the Flickr module
 */

/**
 * Implements hook_settings().
 */
function flickr_admin_settings() {
  $form['flickr_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API Key'),
    '#required' => TRUE,
    '#default_value' => variable_get('flickr_api_key', ''),
    '#description' => t('API Key from Flickr'),
  );
  $form['flickr_api_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('API Shared Secret'),
    '#required' => TRUE,
    '#default_value' => variable_get('flickr_api_secret', ''),
    '#description' => t("API key's secret from Flickr."),
  );
  $form['flickr_default_userid'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Flickr User Id'),
    '#default_value' => variable_get('flickr_default_userid', ''),
    '#description' => t('An, optional, default Flickr username or user id. This will be used when no user is specified.'),
  );
  $times = array(
    900,
    1800,
    2700,
    3600,
    7200,
    10800,
    14400,
    18000,
    21600,
    43200,
    86400,
  );
  $ageoptions = drupal_map_assoc($times, 'format_interval');
  $form['flickr_cache_duration'] = array(
    '#type' => 'select',
    '#title' => t('Update interval'),
    '#options' => $ageoptions,
    '#default_value' => variable_get('flickr_cache_duration', 3600),
    '#description' => t('The refresh interval indicating how often you want to check cached Flickr API calls are up to date.'),
  );
  $form['flickr_photos_per_page'] = array(
    '#type' => 'select',
    '#title' => t('Number of photos per photoset'),
    '#default_value' => variable_get('flickr_photos_per_page', '30'),
    '#options' => array(
      '10' => t('10'),
      '30' => t('30'),
      '50' => t('50'),
      '100' => t('100'),
      '150' => t('150'),
      '200' => t('200'),
      '300' => t('300'),
      '400' => t('400'),
      '500' => t('500'),
    ),
    '#description' => t('The number indicates how many photos of a photoset display in your nodes. After saving the configuration, <a href="?q=admin/config/development/performance">clear the cache</a>.'),
  );
  if (module_exists('flickr_filter')) {
    $form['flickr_default_size'] = array(
      '#type' => 'select',
      '#title' => t('Default size'),
      '#default_value' => variable_get('flickr_default_size', 'm'),
      '#options' => array(
        's' => t('s: 75 px square'),
        't' => t('t: 100 px on longest side'),
        'q' => t('q: 150 px square'),
        'm' => t('m: 240 px on longest side'),
        'n' => t('n: 320 px on longest side (!)'),
        '-' => t('-: 500 px on longest side'),
        'z' => t('z: 640 px on longest side'),
        'c' => t('c: 800 px on longest side (!)'),
        'b' => t('b: 1024 px on longest side'),
      ),
      '#description' => t('A default Flickr size to use. This will be used when no size is specified, for example [flickr-photo:id=3711935987].<br />After saving the configuration, <a href="?q=admin/config/development/performance">clear the cache</a>.<br />!: TAKE CARE, n (320px) and c (800px) sizes are missing on many "older" Flickr images!'),
    );
  }
  $form['flickr_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use flickr.css'),
    '#default_value' => variable_get('flickr_css', 1),
    '#description' => t('Uncheck to take care of the styling yourself in custom CSS.'),
  );
  $form['overlay_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Overlay browser settings'),
    '#description' => t('Leave empty to link directly to the Flickr photo page instead of opening the bigger version of the image.'),
  );
  $form['overlay_settings']['flickr_class'] = array(
    '#type' => 'textfield',
    '#title' => t('class'),
    '#default_value' => variable_get('flickr_class', ''),
    '#description' => t('E.g.: colorbox'),
  );
  $form['overlay_settings']['flickr_rel'] = array(
    '#type' => 'textfield',
    '#title' => t('rel'),
    '#default_value' => variable_get('flickr_rel', ''),
    '#description' => t('E.g.: gallery-all'),
  );
  $form['overlay_settings']['flickr_opening_size'] = array(
    '#type' => 'select',
    '#title' => t('Image size to open'),
    '#default_value' => variable_get('flickr_opening_size', ''),
    '#options' => array(
      'm' => t('m: 240 px on longest side'),
      'n' => t('n: 320 px on longest side (!)'),
      '' => t('-: 500 px on longest side'),
      'z' => t('z: 640 px on longest side'),
      'c' => t('c: 800 px on longest side (!)'),
      'b' => t('b: 1024 px on longest side'),
    ),
    '#description' => t('The image size to open in the overlay browser when clicking the image. Larger sizes make navigating to next and previous pictures slower.<br />After saving the configuration, <a href="?q=admin/config/development/performance">clear the cache</a>.<br />!: TAKE CARE, n (320px) and c (800px) sizes are missing on many "older" Flickr images!'),
  );
  // We need an api key before we can verify usernames.
  if (!$form['flickr_api_key']['#default_value']) {
    $form['flickr_default_userid']['#disabled'] = TRUE;
    $form['flickr_default_userid']['#description'] .= t('Disabled until a valid API Key is set.');
  }

  return system_settings_form($form);
}

/**
 * Validate user input.
 */
function flickr_admin_settings_validate($form, &$form_state) {
  $key = trim($form_state['values']['flickr_api_key']);
  $sec = trim($form_state['values']['flickr_api_secret']);
  $uid = trim($form_state['values']['flickr_default_userid']);

  if ($key && (preg_match('/^[A-Fa-f\d]{32}$/', $key) != 1)) {
    form_set_error('flickr_api_key', t('This does not appear to be a Flickr API key.'));
  }
  if ($sec && (preg_match('/^[A-Fa-f\d]{16}$/', $sec) != 1)) {
    form_set_error('flickr_api_secret', t('This does not appear to be a Flickr API secret.'));
  }
  if ($uid) {
    if (flickr_is_nsid($uid)) {
      // It's already a uid.
    }
    else {
      $user = flickr_user_find_by_username($uid);
      if (!$user) {
        form_set_error('flickr_default_userid', t('%uid is not a Flickr user id and it does not appear to be a valid user name.', array('%uid' => $uid)));
      }
    }
  }
}

/**
 * Submit form data.
 */
function flickr_admin_settings_submit($form, &$form_state) {
  // Clean up the data.
  $form_state['values']['flickr_api_key'] = trim($form_state['values']['flickr_api_key']);
  $form_state['values']['flickr_api_secret'] = trim($form_state['values']['flickr_api_secret']);
  $form_state['values']['flickr_photos_per_page'] = trim($form_state['values']['flickr_photos_per_page']);
  $form_state['values']['flickr_default_userid'] = trim($form_state['values']['flickr_default_userid']);

  // Replace the usernames with a uid.
  if (!flickr_is_nsid($form_state['values']['flickr_default_userid'])) {
    $username = $form_state['values']['flickr_default_userid'];
    if ($user = flickr_user_find_by_username($username)) {
      drupal_set_message(t('The Flickr username %username has been replaced with the corresponding user id %uid.', array('%username' => $form_state['values']['flickr_default_userid'], '%uid' => $user['id'])));
      $form_state['values']['flickr_default_userid'] = $user['id'];
    }
  }

  // Save the settings.
  system_settings_form_submit($form, $form_state);
}

