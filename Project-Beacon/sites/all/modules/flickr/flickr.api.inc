<?php
/**
 * @file
 * Flickr API functions.
 */

// TODO: Would like to implement a consistent naming for drupal wrapper
// functions around flick API methods e.g covert a "." to an "underscore" only
// i.e for flickr.photos.getInfo use flickr_photos_getinfo()
/**
 * Get information about a photo.
 *
 * @param string $photo_id
 *   ID of the photo to get info about.
 *
 * @return array
 *   response from the flickr method flickr.photos.getInfo
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
 *   response from the flickr method flickr.photos.getSizes
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
 * Return a list of photos matching some criteria.
 *
 * @param string $nsid
 *   NSID of the user whose photoset tags will be returned.
 * @param string $page
 *   Page of results to return.
 *
 * @return array
 *   response from the flickr method flickr.photos.search
 *   (http://www.flickr.com/services/api/flickr.photos.search.html)
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

/**
 * Gets information about a photoset.
 *
 * @param string $photoset_id
 *   ID of the photoset to get information about.
 *
 * @return array
 *   response from the flickr method flickr.photosets.getInfo
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
 *   response from the flickr method flickr.photosets.getList
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
 * Get the list of photos in a set.
 *
 * @param string $photoset_id
 *   The Flickr photoset ID.
 *
 * @return array
 *   response from the flickr method flickr.photosets.getPhotos
 *   (http://www.flickr.com/services/api/flickr.photosets.getPhotos.html)
 */
function flickr_photoset_get_photos($photoset_id) {
  $response = flickr_request('flickr.photosets.getPhotos',
  array(
    'photoset_id' => $photoset_id,
    'per_page' => 500,
    'extras' => 'owner',
  ));
  if ($response) {
    return $response;
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
 *   array with person's info from flickr.people.getInfo
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
 * Return a user's NSID, given their username.
 *
 * @param string $username
 *   username to look for
 *
 * @return array
 *   response from the flickr method flickr.people.findByUsername
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
 *   response from the flickr method flickr.people.findByEmail
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
 *   response from the flickr method flickr.tags.getListUserPopular
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
 *   response from the flickr method flickr.tags.getListUser
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

// TODO: Change name to flickr_groups_pools_get_photos()?
/**
 * Returns a list of pool photos for a given group.
 *
 * @param string $nid
 *   NSID of the group whose photos you want.
 *
 * @return array
 *   response from the flickr method flickr.groups.pools.getPhotos
 *   (http://www.flickr.com/services/api/flickr.groups.pools.getPhotos.html)
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

