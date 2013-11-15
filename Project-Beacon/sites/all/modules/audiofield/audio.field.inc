<?php
/**
 * @file
 * Implement an audio field, based on the file module's file field.
 */

/**
 * Implements hook_field_prepare_view().
 */
function audiofield_field_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items) {
  //TODO: Check this:
  //  Remove files specified to not be displayed.
  foreach ($entities as $id => $entity) {
    foreach ($items[$id] as $delta => $item) {
      if (!file_field_displayed($item, $field)) {
        unset($items[$id][$delta]);
      }
      // Ensure consecutive deltas.
      $items[$id] = array_values($items[$id]);
    }
  }
}

/**
 * Implements hook_field_is_empty().
 */
function audiofield_field_is_empty($item, $field) {
  return file_field_is_empty($item, $field);
}

/**
 * Implements hook_field_widget_info().
 */
function audiofield_field_widget_info() {
  return array(
    'audiofield_widget' => array(
      'label' => t('Audio Upload'),
      'field types' => array('file'),
      'settings' => array(
        'progress_indicator' => 'throbber',
        //'file_extensions' => 'mp3',
      ),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
        'default value' => FIELD_BEHAVIOR_NONE,
      ),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function audiofield_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {

  // Add display_field setting to field because file_field_widget_form() assumes it is set.
  $field['settings']['display_field'] = 0;

  $elements = file_field_widget_form($form, $form_state, $field, $instance, $langcode, $items, $delta, $element);
  $settings = $instance['settings'];

  foreach (element_children($elements) as $delta) {
    $elements[$delta]['#process'] = array('audiofield_field_widget_process');
  }
  if ($field['cardinality'] == 1) {
    // If there's only one field, return it as delta 0.
    if (empty($elements[0]['#default_value']['fid'])) {
      $elements[0]['#description'] = theme('file_upload_help', array(
        'description' => $instance['description'],
        'upload_validators' => $elements[0]['#upload_validators']
      ));
    }
  }
  else {
    $elements['#file_upload_description'] = theme('file_upload_help', array('upload_validators' => $elements[0]['#upload_validators']));
  }

  return $elements;
}

/**
 * An element #process callback for the audiofield_widget field type.
 *
 * Display audio player in node edit mode
 */
function audiofield_field_widget_process($element, &$form_state, $form) {
  $fid = isset($element['#value']['fid']) ? $element['#value']['fid'] : 0;
  $element = file_managed_file_process($element, $form_state, $form);
  
  $item = $element['#value'];
  $item['fid'] = $element['fid']['#value'];
  $field = field_widget_field($element, $form_state);
  $instance = field_widget_instance($element, $form_state);
   // Add the display field if enabled.
  if (!empty($field['settings']['display_field']) && $item['fid']) {
    $element['display'] = array(
      '#type' => empty($item['fid']) ? 'hidden' : 'checkbox',
      '#title' => t('Include file in display'),
      '#value' => isset($item['display']) ? $item['display'] : $field['settings']['display_default'],
      '#attributes' => array('class' => array('file-display')),
    );
  }
  else {
    $element['display'] = array(
      '#type' => 'hidden',
      '#value' => '1',
    );
  }
  if ($fid && $element['#file']) {
    $audiofile = file_create_url($element['#file']->uri);
    $info = pathinfo($audiofile);
    $op = $info['extension'];
    $element['filename'] = array(
      '#type' => 'markup',
      '#markup' => audiofield_get_player($audiofile, $op),
      '#weight' => -10,
    );
  }
  
  // Add the description field if enabled.
  if (!empty($instance['settings']['description_field']) && $item['fid']) {
    $element['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Description'),
      '#value' => isset($item['description']) ? $item['description'] : '',
      '#type' => variable_get('file_description_type', 'textfield'),
      '#maxlength' => variable_get('file_description_length', 128),
      '#description' => t('The description may be used as the label of the link to the file.'),
    );
  }
  return $element;
}

/**
 * Implements hook_field_formatter_info().
 */
function audiofield_field_formatter_info() {
  $formatters = array(
    'audiofield_embedded' => array(
      'label' => t('Audio player with download'),
      'field types' => array('file'),
      'description' => t('Displays an audio player and optional download link.'),
    ),
    'audiofield_nodownload' => array(
      'label' => t('Audio player only'),
      'field types' => array('file'),
      'description' => t('Displays only an audio player.'),
    ),
  );

  return $formatters;
}

/**
 * Implements hook_field_formatter_view().
TODO: Can implement playlists to group audios hold in multiple valued fields
 */
function audiofield_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $elements = array();

  switch ($display['type']) {
    case 'audiofield_embedded' :
      foreach ($items as $delta => $item) {
        $elements[] = array('#markup' => theme('audiofield_formatter_audiofield_embedded', array('file' => (object) $item)));
      }
      break;
    case 'audiofield_nodownload':
      foreach ($items as $delta => $item) {
        $elements[] = array('#markup' => theme('audiofield_formatter_audiofield_nodownload', array('file' => (object) $item)));
      }
      break;
  }

  return $elements;
}
