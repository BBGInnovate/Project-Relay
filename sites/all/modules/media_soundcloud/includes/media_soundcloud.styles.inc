<?php

/**
 * @file media_soundcloud/includes/media_soundcloud.styles.inc
 * Styles definitions for Media: SoundCloud.
 */

/**
 * Implementation of Styles module hook_styles_register().
 */
function media_soundcloud_styles_register() {
  return array(
    'MediaSoundCloudStyles' => array(
      'field_types' => 'file',
      'name' => t('MediaSoundCloud'),
      'description' => t('Media SoundCloud styles.'),
      'path' => drupal_get_path('module', 'media_soundcloud') .'/includes',
      'file' => 'media_soundcloud.styles.inc',
    ),
  );
}

/**
 *  Implements hook_styles_containers(). (Deprecated in version 2)
 */
function media_soundcloud_styles_containers() {
  return array(
    'file' => array(
      'containers' => array(
        'media_soundcloud' => array(
          'label' => t('SoundCloud Styles'),
          'data' => array(
            'streams' => array(
              'soundcloud',
            ),
            'mimetypes' => array(
              'audio/soundcloud',
            ),
          ),
          'weight' => 0,
          'filter callback' => 'media_soundcloud_formatter_filter',
          'themes' => array(
            'field_formatter_styles' => 'media_soundcloud_field_formatter_styles',
            'styles' => 'media_soundcloud_styles',
            'preview' => 'media_soundcloud_preview_style',
          ),
          'description' => t('SoundCloud Styles will display embedded SoundCloud audio and thumbnails to your choosing, such as by resizing, setting colors, and autoplay. You can !manage.', array('!manage' => l(t('manage your SoundCloud styles here'), 'admin/config/media/media-soundcloud-styles'))),
        ),
      ),
    ),
  );
}

function media_soundcloud_formatter_filter($variables) {
  if (isset($variables['object'])) {
    $object = isset($variables['object']->file) ? $variables['object']->file : $variables['object'];
    return (file_uri_scheme($object->uri) == 'soundcloud') && ($object->filemime == 'audio/soundcloud');
  }
}

/**
 * Implementation of the File Styles module's hook_file_styles_filter().
 */
function media_soundcloud_file_styles_filter($object) {
  $file = isset($object->file) ? $object->file : $object;
  if ((file_uri_scheme($file->uri) == 'soundcloud') && ($file->filemime == 'audio/soundcloud')) {
    return 'media_soundcloud';
  }
}

/**
 *  Implements hook_styles_styles().
 */
function media_soundcloud_styles_styles() {
  $styles = array(
    'file' => array(
      'containers' => array(
        'media_soundcloud' => array(
          'styles' => array(
            'soundcloud_thumbnail' => array(
              'name' => 'soundcloud_thumbnail',
              'effects' => array(
                array('label' => t('Thumbnail'), 'name' => 'thumbnail', 'data' => array('thumbnail' => 1)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => 100, 'height' => 75)),
              ),
            ),
            'soundcloud_preview' => array(
              'name' => 'soundcloud_preview',
              'effects' => array(
                array('label' => t('Autoplay'), 'name' => 'autoplay', 'data' => array('autoplay' => 1)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => 220, 'height' => 165)),
              ),
            ),
            'soundcloud_full' => array(
              'name' => 'soundcloud_full',
              'effects' => array(
                array('label' => t('Autoplay'), 'name' => 'autoplay', 'data' => array('autoplay' => 0)),
                array('label' => t('Resize'), 'name' => 'resize', 'data' => array('width' => '100%')),
              ),
            ),
          ),
        ),
      ),
    ),
  );

  // Allow any image style to be applied to the thumbnail.
  foreach (image_styles() as $style_name => $image_style) {
    $styles['file']['containers']['media_soundcloud']['styles']['soundcloud_thumbnail_' . $style_name] = array(
      'name' => 'soundcloud_thumbnail_' . $style_name,
      'image_style' => $style_name,
      'effects' => array(
        array('label' => t('Thumbnail'), 'name' => 'thumbnail', 'data' => array('thumbnail' => 1)),
      ),
    );
  }

  return $styles;
}

/**
 *  Implements hook_styles_presets().
 */
function media_soundcloud_styles_presets() {
  $presets = array(
    'file' => array(
      'square_thumbnail' => array(
        'media_soundcloud' => array(
          'soundcloud_thumbnail_square_thumbnail',
        ),
      ),
      'thumbnail' => array(
        'media_soundcloud' => array(
          'soundcloud_thumbnail',
        ),
      ),
      'small' => array(
        'media_soundcloud' => array(
          'soundcloud_preview',
        ),
      ),
      'large' => array(
        'media_soundcloud' => array(
          'soundcloud_full',
        ),
      ),
      'original' => array(
        'media_soundcloud' => array(
          'soundcloud_full',
        ),
      ),
    ),
  );
  return $presets;
}

/**
 * Implementation of Styles module hook_styles_default_containers().
 */
function media_soundcloud_styles_default_containers() {
  // We append SoundCloud to the file containers.
  return array(
    'file' => array(
      'containers' => array(
        'media_soundcloud' => array(
          'class' => 'MediaSoundCloudStyles',
          'name' => 'media_soundcloud',
          'label' => t('SoundCloud'),
          'preview' => 'media_soundcloud_preview_style',
        ),
      ),
    ),
  );
}


/**
 * Implementation of Styles module hook_styles_default_presets().
 */
function media_soundcloud_styles_default_presets() {
  $presets = array(
    'file' => array(
      'containers' => array(
        'media_soundcloud' => array(
          'default preset' => 'unlinked_thumbnail',
          'styles' => array(
            'original' => array(
              'default preset' => 'audio',
            ),
            'thumbnail' => array(
              'default preset' => 'linked_thumbnail',
            ),
            'square_thumbnail' => array(
              'default preset' => 'linked_square_thumbnail',
            ),
            'medium' => array(
              'default preset' => 'linked_medium',
            ),
            'large' => array(
              'default preset' => 'audio',
            ),
          ),
          'presets' => array(
            'audio' => array(
              array(
                'name' => 'audio',
                'settings' => array(),
              ),
            ),            
          ),
        ),
      ),
    ),
  );
  // Allow any image style to be applied to the thumbnail.
  foreach (image_styles() as $style_name => $image_style) {
    $presets['file']['containers']['media_soundcloud']['presets']['linked_' . $style_name] = array(
      array(
        'name' => 'linkToMedia',
        'settings' => array(),
      ),
      array(
        'name' => 'imageStyle',
        'settings' => array(
          'image_style' => $style_name,
        ),
      ),
      array(
        'name' => 'thumbnail',
        'settings' => array(),
      ),
    );
    $presets['file']['containers']['media_soundcloud']['presets']['unlinked_' . $style_name] = $presets['file']['containers']['media_soundcloud']['presets']['linked_' . $style_name];
    array_shift($presets['file']['containers']['media_soundcloud']['presets']['unlinked_' . $style_name]);
  }
  return $presets;
}
