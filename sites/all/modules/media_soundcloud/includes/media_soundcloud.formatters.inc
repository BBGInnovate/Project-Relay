<?php

/**
 * @file
 */

/**
 * Implements hook_file_formatter_info().
 */
function media_soundcloud_file_formatter_info() {
  $formatters['media_soundcloud_audio'] = array(
    'label' => t('SoundCloud Audio'),
    'file types' => array('audio'),
    'default settings' => array(
      'width' => media_soundcloud_variable_get('width'),
      'autoplay' => media_soundcloud_variable_get('autoplay'),
      'extra_params' => media_soundcloud_variable_get('extra_params'),
    ),
    'view callback' => 'media_soundcloud_file_formatter_audio_view',
    'settings callback' => 'media_soundcloud_file_formatter_audio_settings',
  );
  $formatters['media_soundcloud_image'] = array(
    'label' => t('SoundCloud Preview Image'),
    'file types' => array('audio'),
    'default settings' => array(
      'image_style' => '',
    ),
    'view callback' => 'media_soundcloud_file_formatter_image_view',
    'settings callback' => 'media_soundcloud_file_formatter_image_settings',
  );
  return $formatters;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_soundcloud_file_formatter_audio_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support audio inside a running editor instance.
  if ($scheme == 'soundcloud' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'media_soundcloud_audio',
      '#uri' => $file->uri,
    );
    foreach (array('width', 'autoplay', 'extra_params') as $setting) {
      $element['#' . $setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_soundcloud_file_formatter_audio_settings($form, &$form_state, $settings) {
  $element = array();
  $element['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => $settings['width'],
  );
  $element['autoplay'] = array(
    '#title' => t('Autoplay'),
    '#type' => 'checkbox',
    '#default_value' => $settings['autoplay'],
  );
  $element['extra_params'] = array(
    '#title' => t('Extra parameters'),
    '#description' => t('Add multiple parameters as comma separated colon separated pairs. Eg. color: 2582fa, iframe: true. See http://developers.soundcloud.com/docs/oembed for more parameters.'),
    '#type' => 'textfield',
    '#default_value' => $settings['extra_params'],
  );
  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_soundcloud_file_formatter_image_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  if ($scheme == 'soundcloud') {
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $image_style = $display['settings']['image_style'];
    $valid_image_styles = image_style_options(FALSE);
    if (empty($image_style) || !isset($valid_image_styles[$image_style])) {
      $element = array(
        '#theme' => 'image',
        '#path' => $wrapper->getLocalThumbnailPath(),
      );
    }
    else {
      $element = array(
        '#theme' => 'image_style',
        '#style_name' => $image_style,
        '#path' => $wrapper->getLocalThumbnailPath(),
      );
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_soundcloud_file_formatter_image_settings($form, &$form_state, $settings) {
  $element = array();
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
  );
  return $element;
}

/**
 * Implements hook_file_default_displays().
 */
function media_soundcloud_file_default_displays() {
  $default_displays = array();

  // Default settings for displaying as a audio.
  $default_audio_settings = array(
    'default' => array(
      'width' => 640,
      'autoplay' => FALSE,
      'extra_params' => media_soundcloud_variable_get('extra_params'),
    ),
    'teaser' => array(
      'width' => "100%",
      'autoplay' => FALSE,
      'extra_params' => media_soundcloud_variable_get('extra_params'),
    ),
    // Legacy view modes included to support older versions of Media,
    // before #1051090 went through. They do no harm and can sit here
    // until there is a Media 2.x stable.
    // @TODO: Remove when Media 2.0 is released.
    'media_large' => array(
      'width' => 480,
      'autoplay' => FALSE,
      'extra_params' => media_soundcloud_variable_get('extra_params'),
    ),
    'media_original' => array(
      'width' => "100%",
      'autoplay' => media_soundcloud_variable_get('autoplay'),
      'extra_params' => media_soundcloud_variable_get('extra_params'),
    ),
  );
  foreach ($default_audio_settings as $view_mode => $settings) {
    $display_name = 'audio__' . $view_mode . '__media_soundcloud_audio';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 1,
      'settings' => $settings,
    );
  }

  // Default settings for displaying a audio preview image. We enable preview
  // images even for view modes that also play audio, for use inside a running
  // WYSIWYG editor. The higher weight ensures that the audio display is used
  // where possible.
  $default_image_styles = array(
    'default' => 'large',
    'preview' => 'square_thumbnail',
    'teaser' => 'large',
    // Legacy view modes, see note above.
    'media_large' => 'large',
    'media_original' => '',
  );
  foreach ($default_image_styles as $view_mode => $image_style) {
    $display_name = 'audio__' . $view_mode . '__media_soundcloud_image';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 2,
      'settings' => array('image_style' => $image_style),
    );
  }

  return $default_displays;
}
