<?php

function relay_card_types_verify_vimeo_library(){

	//
  if (($library = libraries_detect('vimeo_api')) && !empty($library['installed'])) {
    
    //The library is installed. Awesome! Load it
    libraries_load('vimeo_api');

    //we are good
    return true;

  }
  else {
    
    // This contains a short status code of what went wrong, such as 'not found'.
    $error = $library['error'];
    
    // This contains a detailed (localized) error message.
    $error_message = $library['error message'];

    //no library so the attemp failed
    //watchdog( 'relay_card_types', t($error_message) );

    //
    return false;
  }
}

function relay_card_types_verify_youtube_library(){

	//
  if (($library = libraries_detect('youtube_api')) && !empty($library['installed'])) {
    
    //
    set_include_path( get_include_path() . PATH_SEPARATOR . $_SERVER['DOCUMENT_ROOT'] . libraries_get_path( 'youtube_api', true ) . '/src/' );

    //The library is installed. Awesome! Load it
    libraries_load('youtube_api');

    //we are good
    return true;

  }
  else {
    
    // This contains a short status code of what went wrong, such as 'not found'.
    $error = $library['error'];
    
    // This contains a detailed (localized) error message.
    $error_message = $library['error message'];

    //no library so the attemp failed
    //watchdog( 'relay_card_types', t($error_message) );

    //
    return false;
  }
}

function relay_card_types_verify_sound_cloud_library(){

	//
  if (($library = libraries_detect('soundcloud_api')) && !empty($library['installed'])) {
    
    //The library is installed. Awesome! Load it
    libraries_load('soundcloud_api');

    //we are good
    return true;

  }
  else {
    
    // This contains a short status code of what went wrong, such as 'not found'.
    $error = $library['error'];
    
    // This contains a detailed (localized) error message.
    $error_message = $library['error message'];

    //no library so the attemp failed
    //watchdog( 'relay_card_types', t($error_message) );

    //
    return false;
  }
}

function relay_card_types_verify_twitter_library(){

  //
  if (($library = libraries_detect('twitter_api')) && !empty($library['installed'])) {
    
    //The library is installed. Awesome! Load it
    libraries_load('twitter_api');

    //we are good
    return true;

  }
  else {
    
    // This contains a short status code of what went wrong, such as 'not found'.
    $error = $library['error'];
    
    // This contains a detailed (localized) error message.
    $error_message = $library['error message'];

    //no library so the attemp failed
    //watchdog( 'relay_card_types', t($error_message) );

    //
    return false;
  }
}