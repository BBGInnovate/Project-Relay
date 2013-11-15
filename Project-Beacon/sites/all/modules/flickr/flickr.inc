<?php
/**
 * @file
 * The Flickr API functions.
 */

define('FLICKR_REST_ENDPOINT', 'http://api.flickr.com/services/rest/');

/**
 * A list of possible photo sizes with description and label.
 *
 * @return array
 *   An array of photo sizes.
 */
function flickr_photo_sizes() {
  return array(
    's' => array(
      'label' => 'Square',
      'description' => t('s: 75 px square'),
    ),
    't' => array(
      'label' => 'Thumbnail',
      'description' => t('t: 100 px on longest side'),
    ),
    'q' => array(
      'label' => 'Large Square',
      'description' => t('q: 150 px square'),
    ),
    'm' => array(
      'label' => 'Small',
      'description' => t('m: 240 px on longest side'),
    ),
    'n' => array(
      'label' => 'Small 320',
      'description' => t('n: 320 px on longest side'),
    ),
    '-' => array(
      'label' => 'Medium',
      'description' => t('-: 500 px on longest side'),
    ),
    'z' => array(
      'label' => 'Medium 640',
      'description' => t('z: 640 px on longest side'),
    ),
    'c' => array(
      'label' => 'Medium 800',
      'description' => t('c: 800 px on longest side'),
    ),
    'b' => array(
      'label' => 'Large',
      'description' => t('b: 1024 px on longest side'),
    ),
    'h' => array(
      'label' => 'Large 1600',
      'description' => t('h: 1600 px on longest side'),
    ),
    'k' => array(
      'label' => 'Large 2048',
      'description' => t('k: 2048 px on longest side'),
    ),
    'o' => array(
      'label' => 'Original',
      'description' => t('o: Original image'),
    ),
  );
};

/**
 * Submit a request to Flickr.
 *
 * @param string $method
 *   String method name.
 * @param string $args
 *   Associative array of arguments names and values.
 * @param string $cacheable
 *   Boolean indicating if it's safe cache the results of this request.
 * @param string $return_errors
 *   Boolean indicating if the caller will handle displaying error messages.
 *
 * @return array
 *   an array with the the result of the request, or FALSE on error.
 */
function flickr_request($method, $args, $cacheable = TRUE, $return_errors = FALSE) {
  // Add in additional parameters then sort them for signing.
  $args['api_key'] = trim(variable_get('flickr_api_key', ''));
  $args['method'] = $method;
  $args['format'] = 'php_serial';
  ksort($args);

  // Build an argument hash API signing (we'll also use it for the cache id).
  $arg_hash = '';
  foreach ($args as $k => $v) {
    $arg_hash .= $k . $v;
  }
  // If we've got a secret, sign the arguments.
  if ($secret = trim(variable_get('flickr_api_secret', ''))) {
    $args['api_sig'] = md5($secret . $arg_hash);
  }

  // Build the URL.
  foreach ($args as $k => $v) {
    $encoded_params[] = urlencode($k) . '=' . urlencode($v);
  }
  $url = FLICKR_REST_ENDPOINT . '?' . implode('&', $encoded_params);

  // If it's a cachable request, try to load a cached value.
  if ($cacheable) {
    if ($cache = cache_get("flickr_$arg_hash", 'cache')) {
      // Check that the value is still "fresh".
      if ($cache->expire > time()) {
        return unserialize($cache->data);
      }
    }
  }

  // If a cached value wasn't suitable, attempt to connect and fetch a result.
  $result = drupal_http_request($url);
  if ($result->code != 200) {
    if ($return_errors) {
      return array(
        'stat' => 'error',
        // In Drupal <= 5.1, only HTTP errors are stored in $result->code
        // correctly, not TCP/IP errors. We can not count on this variable being
        // correct until this module requires Drupal 5.2 or above.
        'code' => $result->code,
        'message' => $result->error,
      );
    }
    flickr_set_error(t("Could not connect to Flickr, Error: @error", array('@error' => $result->error)));
    return FALSE;
  }

  // Make sure it unserializes.
  $response = unserialize($result->data);
  if (!$response) {
    if ($return_errors) {
      return array(
        'stat' => 'error',
        'code' => '-1',
        'message' => 'The response was corrupted, it could not be unserialized.',
      );
    }
    flickr_set_error(t("Flickr's response was corrupted and could not be unserialized."));
    return FALSE;
  }

  // Check that the request was successful.
  if (flickr_response_has_error($response)) {
    if ($return_errors) {
      return $response;
    }
    flickr_set_error($response);
    return FALSE;
  }

  // Save cacheable results for future use.
  if ($cacheable) {
    cache_set("flickr_$arg_hash", $result->data, 'cache', time() + variable_get('flickr_cache_duration', 3600));
  }

  return $response;
}

/**
 * This function will try to create a html image tag referencing the Flickr
 * photo with the desired size if that size is available for this photo.
 *
 * @param string $photo
 *   The photo variable.
 * @param string $size
 *   The desired image size.
 * @param string $attributes
 *   An optional array of HTML attributes to pass to the image.
 *
 * @return array
 *   a html image tag referencing the image of the desired
 *   size if it is available.
 */
function flickr_img($photo, $size = NULL, $attributes = NULL) {
  $sizes = flickr_photo_sizes();
  if (!isset($size)) {
    $size = '-';
  }
  if (!isset($sizes[$size])) {
    return;
  }
  if (!isset($attributes) || !is_array($attributes)) {
    $attributes = array();
  }
  if (empty($attributes['class'])) {
    $attributes['class'] = NULL;
  }

  // photoset's use primary instead of id to specify the image.
  if (isset($photo['primary'])) {
    $id = $photo['primary'];
    $attributes['class'] = implode(' ', array(
      $attributes['class'],
      'flickr-photoset-img',
    ));
  }
  else {
    $id = $photo['id'];
    $attributes['class'] = implode(' ', array(
      $attributes['class'],
      'flickr-photo-img',
    ));
  }

  if ($size == 's') {
    $attributes['height'] = $attributes['width'] = 75;
    $img_url = flickr_photo_img($photo, $size);
  }
  else {
    $image_sizes = flickr_photo_get_sizes($id);
    if ($image_sizes) {
      foreach ($image_sizes as $image_size) {
        if ($image_size['label'] == $sizes[$size]['label']) {
          break;
        }
      }
      if (isset($image_size)) {
        $img_url = $image_size['source'];
        $attributes['height'] = $image_size['height'];
        $attributes['width'] = $image_size['width'];
      }
    }
    else {
      $img_url = flickr_photo_img($photo, $size);
    }
  }
  $title = is_array($photo['title']) ? $photo['title']['_content'] : $photo['title'];
  return theme('image', array(
    'path' => $img_url,
    'alt' => $title,
    'title' => $title,
    'attributes' => $attributes,
    'getsize' => FALSE,
  ));
}

/**
 * Returns the URL to $photo with size $size using the correct image farm
 * from the $photo variable.
 *
 * @param string $photo
 *   Photo to which the url should point.
 * @param string $size
 *   Size of the photo.
 * @param string $format
 *   Format of the photo.
 *
 * @return array
 *   URL for $photo with the correct size and format.
 */
function flickr_photo_img($photo, $size = NULL, $format = NULL) {
  // Early images don't have a farm setting so default to 1.
  $farm = isset($photo['farm']) ? $photo['farm'] : 1;
  $server = $photo['server'];
  // photoset's use primary instead of id to specify the image.
  $id = isset($photo['primary']) ? $photo['primary'] : $photo['id'];
  $secret = $photo['secret'];

  return "http://farm{$farm}.static.flickr.com/{$server}/{$id}_{$secret}" . ($size ? "_$size." : '.') . ($size == 'o' ? $format : 'jpg');
}

/**
 * Returns the URL for the Flick photo page.
 *
 * @param string $owner
 *   Owner of the photo.
 * @param string $id
 *   ID of the photo to reference in the URL.
 *
 * @return array
 *   URL for the flickr photo page showing photo with $id of $owner.
 */
function flickr_photo_page_url($owner, $id = NULL) {
  $nsid = is_array($owner) ? $owner['nsid'] : $owner;
  if ($person = flickr_people_get_info($nsid)) {
    return $person['photosurl']['_content'] . $id;
  }
  else {
    return "http://flickr.com/photos/$nsid/$id";
  }
}

/**
 * Returns the URL of a given photoset page.
 *
 * @param string $owner
 *   Owner of the photoset.
 * @param string $id
 *   ID of the photoset to which the url must lead.
 *
 * @return array
 *   URL for the photoset page of photoset $id of owner $owner.
 */
function flickr_photoset_page_url($owner, $id = NULL) {
  $nsid = is_array($owner) ? $owner['nsid'] : $owner;
  if ($person = flickr_people_get_info($nsid)) {
    return $person['photosurl']['_content'] . 'sets/' . $id;
  }
  else {
    return "http://flickr.com/photos/$nsid/sets/$id";
  }
}

/**
 * Get information about a photo.
 *
 * @param string $photo_id
 *   ID of the photo to get info about.
 *
 * @return array
 *   Response from the flickr method flickr.photos.getInfo.
 *   (http://www.flickr.com/services/api/flickr.photos.getInfo.html)
 */
function flickr_photo_get_info($photo_id) {
  $response = flickr_request(
    'flickr.photos.getInfo',
    array('photo_id' => $photo_id)
  );
  if ($response) {
    return $response['photo'];
  }
  return FALSE;
}

/**
 * Returns the available sizes for a photo.
 *
 * @param string $photo_id
 *   ID of the photo to get the available sizes of.
 *
 * @return array
 *   Response from the flickr method flickr.photos.getSizes.
 *   (http://www.flickr.com/services/api/flickr.photos.getSizes.html)
 */
function flickr_photo_get_sizes($photo_id) {
  $response = flickr_request(
    'flickr.photos.getSizes',
    array('photo_id' => $photo_id)
  );
  if ($response) {
    return $response['sizes']['size'];
  }
  return FALSE;
}

/**
 * Gets information about a photoset.
 *
 * @param string $photoset_id
 *   ID of the photoset to get information about.
 *
 * @return array
 *   Response from the flickr method flickr.photosets.getInfo.
 *   (http://www.flickr.com/services/api/flickr.photosets.getInfo.html)
 */
function flickr_photoset_get_info($photoset_id) {
  $response = flickr_request(
    'flickr.photosets.getInfo',
    array('photoset_id' => $photoset_id)
  );
  if ($response) {
    return $response['photoset'];
  }
  return FALSE;
}

/**
 * Returns the photosets belonging to the specified user.
 *
 * @param string $nsid
 *   NSID of the user whose photoset list you want.
 *
 * @return array
 *   Response from the flickr method flickr.photosets.getList.
 *   (http://www.flickr.com/services/api/flickr.photosets.getList.html)
 */
function flickr_photoset_get_list($nsid) {
  $response = flickr_request(
    'flickr.photosets.getList',
    array('user_id' => $nsid)
  );
  if ($response) {
    return $response['photosets']['photoset'];
  }
  return FALSE;
}

/**
 * Get information about a user.
 *
 * @param string $nsid
 *   The Flickr user's NSID.
 *
 * @return array
 *   Array with person's info from flickr.people.getInfo.
 *   (http://www.flickr.com/services/api/flickr.people.getInfo.html)
 *   or FALSE on error.
 */
function flickr_people_get_info($nisd) {
  $response = flickr_request(
    'flickr.people.getInfo',
    array('user_id' => $nisd)
  );
  if ($response) {
    return $response['person'];
  }
  return FALSE;
}

/**
 * Tries to match an 'identifier' onto a flickr nsid.
 *
 * This function will first see whether $identifier is already
 * a nsid (format check only, no api call).  If it is not and the
 * identifier has the format of an email, an api call will be made to
 * check whether there is an nsid for that email.  If this is not the
 * case, the $identifier is treated as a username and an api call is
 * made to find the nsid for that username.
 *
 * If none of these succeed, the result will be false
 *
 * @param string $identifier
 *   Identifier to find an NSID for.
 *
 * @return array
 *   Valid NSID or false if none can be found.
 */
function flickr_user_find_by_identifier($identifier) {
  if (flickr_is_nsid($identifier)) {
    // Identifier is an NSID.
    return $identifier;
  }
  if (valid_email_address($identifier) && ($user = flickr_user_find_by_email($identifier))) {
    return $user['nsid'];
  }
  if ($user = flickr_user_find_by_username($identifier)) {
    return $user['nsid'];
  }

  return FALSE;
}

/**
 * Flickr is NSID.
 */
function flickr_is_nsid($id) {
  return preg_match('/^\d+@N\d+$/', $id);
}

/**
 * Return a user's NSID, given their username.
 *
 * @param string $username
 *   Username to look for.
 *
 * @return array
 *   Response from the flickr method flickr.people.findByUsername.
 *   (http://www.flickr.com/services/api/flickr.people.findByUsername.html)
 */
function flickr_user_find_by_username($username) {
  $response = flickr_request(
    'flickr.people.findByUsername',
    array('username' => $username)
  );
  if ($response) {
    return $response['user'];
  }
  return FALSE;
}

/**
 * Return a user's NSID, given their email address.
 *
 * @param string $email
 *   Email to look for.
 *
 * @return array
 *   Response from the flickr method flickr.people.findByEmail.
 *   (http://www.flickr.com/services/api/flickr.people.findByEmail.html)
 */
function flickr_user_find_by_email($email) {
  $response = flickr_request(
    'flickr.people.findByEmail',
    array('find_email' => $email)
  );
  if ($response) {
    return $response['user'];
  }
  return FALSE;
}

/**
 * Get the popular tags for a given user.
 *
 * @param string $nsid
 *   NSID of the user whose tags will be returned.
 * @param string $count
 *   Number of tags to return.
 *
 * @return array
 *   Response from the flickr method flickr.tags.getListUserPopular.
 *   (http://www.flickr.com/services/api/flickr.tags.getListUserPopular.html)
 */
function flickr_tags_get_list_user_popular($nsid, $count = NULL) {
  $args = array('user_id' => $nsid);
  if ($count != NULL) {
    $args['count'] = $count;
  }
  $response = flickr_request('flickr.tags.getListUserPopular', $args);
  if ($response) {
    return $response['who']['tags']['tag'];
  }
  return FALSE;
}

/**
 * Get the tag list for a given user.
 *
 * @param string $nsid
 *   NSID of the user whose photoset tags will be returned.
 *
 * @return array
 *   Response from the flickr method flickr.tags.getListUser.
 *   (http://www.flickr.com/services/api/flickr.tags.getListUser.html)
 */
function flickr_tags_get_list_user($nsid) {
  $response = flickr_request(
    'flickr.tags.getListUser',
    array('user_id' => $nsid)
  );
  if ($response) {
    return $response['who']['tags']['tag'];
  }
  return FALSE;
}


/**
 * Flickr photos search.
 */
function flickr_photos_search($nsid, $page = 1, $other_args = array()) {
  $args = array(
    'user_id' => $nsid,
    'page' => $page,
  );

  // Set per_page to flickr module default if not specified in $other_args.
  if (!isset($other_args['per_page'])) {
    $args['per_page'] = variable_get('flickr_photos_per_page', 20);
  }

  $response = flickr_request('flickr.photos.search', array_merge($args, $other_args));
  if ($response) {
    return $response['photos'];
  }
  return FALSE;
}

/**
 * Flickr tag request.
 */
function flickr_tag_request_args($tags = array(), $mode = 'all') {
  $args = array();
  if (!empty($tags)) {
    $args['tags'] = implode(',', $tags);
    $args['tag_mode'] = $mode == 'all' ? $mode : 'any';
  }
  return $args;
}

/**
 * Check if the response from the Flickr api call was an error.
 *
 * @param string $response
 *   Response to check.
 *
 * @return array
 *   True if the response is an error message.
 */
function flickr_response_has_error($response) {
  return !(isset($response['stat']) && $response['stat'] == 'ok');
}

/**
 * Display an error message to flickr admins and write an error to watchdog.
 *
 * @param string $message_or_response
 *   Message or error response to display.
 */
function flickr_set_error($message_or_response) {
  if (is_array($message_or_response)) {
    $message = t('Flickr error @error_id: %flickr_error', array(
      '@error_id' => $message_or_response['code'],
      '%flickr_error' => $message_or_response['message'],
    ));
  }
  else {
    $message = $message_or_response;
  }

  if (user_access('administer flickr')) {
    drupal_set_message($message, 'error');
  }
  watchdog('flickr', $message, array(), WATCHDOG_WARNING);
}

/**
 * Returns the photosets belonging to the specified user.
 *
 * @param string $nsid
 *   NSID of the group whose photos you want.
 *
 * @return array
 *   Response from the flickr method flickr.photosets.getList.
 *   (http://www.flickr.com/services/api/flickr.photosets.getList.html)
 */
function flickr_get_group_photos($nsid, $page = 1, $other_args = array()) {
  $args = array(
    'group_id' => $nsid,
    'page' => $page,
  );

  // Set per_page to flickr module default if not specified in $other_args.
  if (!isset($other_args['per_page'])) {
    $args['per_page'] = variable_get('flickr_photos_per_page', 20);
  }

  $response = flickr_request('flickr.groups.pools.getPhotos', array_merge($args, $other_args));
  if ($response) {
    return $response['photos'];
  }
  return FALSE;
}

/**
 * Returns a list of favorite public photos for the given user.
 *
 * @param string $nsid
 *   NSID of the user whose photoset tags will be returned.
 * @param string $page
 *   Page of results to return.
 *
 * @return array
 *   response from the flickr method flickr.favorites.getPublicList
 *   (http://www.flickr.com/services/api/flickr.favorites.getPublicList.html)
 */
function flickr_favorites_get_public_list($nsid, $page = 1, $other_args = array()) {
  $args = array(
    'user_id' => $nsid,
    'page' => $page,
  );

  // Set per_page to flickr module default if not specified in $other_args.
  if (!isset($other_args['per_page'])) {
    $args['per_page'] = variable_get('flickr_photos_per_page', 20);
  }

  $response = flickr_request('flickr.favorites.getPublicList', array_merge($args, $other_args));
  if ($response) {
    return $response['photos'];
  }
  return FALSE;
}

