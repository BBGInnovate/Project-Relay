<?php 

/**
 * @file
 * Import page callbacks for the flickrsync module.
 */

/**
 * Import page, which calls the update process from JavaScript (to improve page responsiveness)
 */
function flickrsync_import() {
  $op = isset($_REQUEST['op']) ? $_REQUEST['op'] : '';

  switch ($op) {
    case 'finished':
      return flickrsync_import_finished_page(TRUE);
      break;

    case 'error':
      return flickrsync_import_finished_page(FALSE);
      break;

    case 'do_import_js':
      print flickrsync_import_do_import_js();
      break;

    case 'do_import_nojs':
      return flickrsync_import_progress_page_nojs();
      break;

    default:
      return flickrsync_import_start_page();
      break;
  }
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function flickrsync_init_header() {
  $path = drupal_get_path('module', 'flickrsync');

  // add CSS
  drupal_add_css($path . '/flickrsync.css');

  // JavaScript
  drupal_add_js('misc/progress.js', array('type' => 'file', 'weight' => JS_LIBRARY));
  drupal_add_js($path . '/flickrsync.js', array('cache' => FALSE));
  drupal_add_js(
    array(
    'flickrsync' => array(
      'url' => array(
        'finished' => url('admin/config/media/flickrsync/import', array('query' => array('op' => 'finished'))),
        'do_import' => url('admin/config/media/flickrsync/import', array('query' => array('op' => 'do_import_js'))),
      ),
    ),
  ), array('type' => 'setting'
  , 'scope' => JS_DEFAULT));
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function flickrsync_import_start_page() {
  global $user;
  $fuser = user_load($user->uid);

  // verify that the user has a Flickr username identifier
  if (empty($fuser->flickrsync) || !$fuser->flickrsync['nsid']) {
    drupal_set_message(t("Unable to find your Flickr username!
                          Please configure it in your !account-settings.",
                          array(
      '!account-settings' => l('account settings', 'user/' . $fuser->uid . '/edit'),
    )),
                          'error');
    return '';
  }

  // add JS and CSS
  flickrsync_init_header();

  // get user's start date
  $posted_after = '';
  if ($fuser->flickrsync['start_date']) {
    $posted_after = 'posted on or after ' . date('m/d/y', $fuser->flickrsync['start_date']);
  }

  // get user's tags
  if ($fuser->flickrsync['tags']) {
    $tags = explode(',', $fuser->flickrsync['tags']);
    $formatted_tags = array();
    foreach ($tags as $tag) {
      $formatted_tags[] = '<span class="tag">' . trim($tag) . '</span>';
    }
    $tags = implode(', ', $formatted_tags);
  }

  // build formatted string
  if (!empty($tags)) {
    $text = t('Only images !posted-after-date with these tags will be imported: !tags',
              array('!posted-after-date' => $posted_after, '!tags' => $tags));
  }
  elseif ($posted_after) {
    $text = t('Only images !posted-after-date will be imported.',
              array('!posted-after-date' => $posted_after));
  }
  else {
    $text = t('All your Flickr images will be imported. !edit-your-account to limit the import to specific
              image tags or to limit the import to only recent images.',
              array('!edit-your-account' => l('Edit your account', 'user/' . $user->uid . '/edit')));
  }

  $output[] = '<div id="flickrsync-import">';
  $output[] = '  <div class="notes">' . $text . '</div>';

  if (!empty($_POST['op'])) {
    $_SESSION['flickrsync_init'] = 1;
    if (!empty($_POST['has_js'])) {
      $output[] = flickrsync_import_progress_page_js();
    }
    else {
      drupal_goto('admin/config/media/flickrsync/import', array('query' => array('op' => 'do_import_nojs')));
    }
  }
  else {
    $output[] = drupal_render(drupal_get_form('flickrsync_import_start_form'));
  }

  $output[] = '</div>';
  return implode("\n", $output);
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function flickrsync_import_start_form($form) {
  $form = array();
  $form['has_js'] = array(
    '#type' => 'hidden',
    '#default_value' => FALSE,
    '#attributes' => array('id' => 'edit-has_js'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Import',
  );
  return $form;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function flickrsync_import_progress_page_js() {
  $output = array();
  $output[] = '<div id="progress"></div>';
  $msg = t('Importing your images may take awhile.  You can stop the import at anytime and resume later.');
  $output[] = '<p id="flickrsync-stop-msg">' . $msg . '</p>';
  $output[] = '<div id="flickrsync-btns">';
  $output[] = '  <input id="flickrsync-stop" type="button" value="Stop" />';
  $output[] = '</div>';
  return implode("\n", $output);
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function flickrsync_import_progress_page_nojs() {
  // add JS and CSS
  flickrsync_init_header();

  $new_op = 'do_import_nojs';
  if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    // Error handling: if PHP dies, it will output whatever is in the output
    // buffer, followed by the error message.
    ob_start();
    print '<p class="error">An unrecoverable error has occurred. You can find the error message below.</p>';

    list($percentage, $message) = flickrsync_import_do_import();
    if ($percentage == 100) {
      $new_op = 'finished';
    }

    // import successful; remove fallback
    ob_end_clean();
  }
  else {
    // This is the first page so return some output immediately.
    $percentage = 0;
    $message = 'Starting updates';
  }

  // TODO The second parameter to this function call should be an array.
  drupal_add_html_head('<meta http-equiv="Refresh" content="0; URL=' . url('admin/config/media/flickrsync/import', array('query' => array('op' => $new_op))) . '">', $key = NULL /* TODO Set this variable. */);
  $output  = '<div id="flickrsync-import">';
  $output .= theme('progress_bar', array('percent' => $percentage, 'message' => $message));
  $msg = t('Importing your images may take awhile.  You can !stop-the-import at anytime and resume later.',
            array('!stop-the-import' => l('stop the import', 'admin/config/media/flickrsync/import')));
  $output .= '<p id="flickrsync-stop-msg">' . $msg . '</p>';
  $output .= '</div>';

  return $output;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function flickrsync_import_do_import_js() {
  // Error handling: if PHP dies, the output will fail to parse as JSON, and
  // the Javascript will tell the user to continue to the op=error page.
  list($percentage, $message) = flickrsync_import_do_import();
  print drupal_json_encode(array('status' => TRUE, 'percentage' => $percentage, 'message' => $message));
}

/**
 * Perform updates for one second or until finished.
 *
 * @return
 *   An array indicating the status after doing updates. The first element is
 *   the overall percentage finished. The second element is a status message.
 */
function flickrsync_import_do_import() {
  // intialization step one: just display a loading message
  if ($_SESSION['flickrsync_init'] == 1) {
    $_SESSION['flickrsync_init'] = 2;
    return array(0, 'Loading list of images to import');

    // intialization step one: load the user's Flickr feed
  }
  elseif ($_SESSION['flickrsync_init'] == 2) {
    $_SESSION['flickrsync_init'] = 0;

    global $user;
    $fuser = user_load($user->uid);

    // get a list of the new photos for the current user
    $feed = flickrsync_get_new_photos_feed($fuser);

    // reset session variables, used by the AJAX callback
    $_SESSION['flickrsync_remaining'] = $feed['photos'];
    $_SESSION['flickrsync_total'] = $feed['count'];
    $_SESSION['flickrsync_current'] = 0;
    $_SESSION['flickrsync_timer'] = REQUEST_TIME;
    $_SESSION['flickrsync_start'] = FALSE;

    return array(0, 'Starting import');
  }

  // start actual import
  while (isset($_SESSION['flickrsync_remaining']) && ($update = reset($_SESSION['flickrsync_remaining']))) {
    if ($_SESSION['flickrsync_current'] != $update['id']) {
      $_SESSION['flickrsync_current'] = $update['id'];
      $_SESSION['flickrsync_timer'] = REQUEST_TIME;

      $result = flickrsync_create_node($update['id']);
      if ($result['success'] == TRUE) {
        // Dequeue the completed update.
        unset($_SESSION['flickrsync_remaining'][key($_SESSION['flickrsync_remaining'])]);
      }
    }

    if (timer_read('page') > 1000) {
      break;
    }
  }

  // timeout if one photo takes too long
  if (($_SESSION['flickrsync_timer'] + variable_get('flickrsync_timeout', 30)) < REQUEST_TIME) {
    drupal_set_message(t('Timeout: Unable to import from Flickr'), 'error');
    return array(100, 'Timeout: Unable to import from Flickr');
  }

  if ($_SESSION['flickrsync_total']) {
    $percentage = floor(($_SESSION['flickrsync_total'] - count($_SESSION['flickrsync_remaining']) + $update_finished) / $_SESSION['flickrsync_total'] * 100);
  }
  else {
    $percentage = 100;
  }

  return array($percentage, isset($update['title']) ? 'Importing image: ' . $update['title'] : 'Flickr sync complete');
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function flickrsync_import_finished_page() {
  $output = array();
  $output[] = '<div id="flickrsync-update">';
  $output[] = '  <div>The import from your Flickr photostream is complete!</div>';
  $output[] = '</div>';
  return implode("\n", $output);
}
