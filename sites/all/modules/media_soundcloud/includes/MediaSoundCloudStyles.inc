<?php

/**
 * @file
 * Styles class implementation for Media: SoundCloud.
 */

class MediaSoundCloudStyles extends FileStyles {
  public $autoplay;
  public $extra_params;

  function getAutoplay() {
      //drupal_set_message("getAutoplay");
    return $this->get('autoplay');
  }
  function setAutoplay($value) {
      //drupal_set_message("setAutoplay");
    return $this->set('autoplay', $value);
  }

  function getExtraParams() {
      //drupal_set_message("getExtraParams");
    return $this->get('extra_params');
  }
  function setExtrasParams($value) {
      //drupal_set_message("setExtrasParams");
    return $this->set('extra_params', $value);
  }

  function getImageUri() {
      //drupal_set_message("getImageUri");
    if ($image_uri = $this->get('imageUri')) {
      return $image_uri;
    }
    $object = $this->getObject();
    if ($object->uri) {
      $wrapper = file_stream_wrapper_get_instance_by_uri($object->uri);
      return $wrapper->getLocalThumbnailPath();
    }
  }
  function audio($effect) {
      //drupal_set_message("audio");
    $variables = array(
      'uri' => $this->getUri(),
      'width' => $this->getWidth(),
      'autoplay' => $this->getAutoplay(),
      'extra_params' => $this->getExtraParams(),
    );
    $this->setOutput(theme('media_soundcloud_audio', $variables));
  }
}
