<?php

/**
 * @file
 * Administrative page callbacks for the flickrsync module.
 */

/**
 * Implements hook_settings().
 */
function flickrsync_admin_settings($form, &$form_state) {
  $node_types = node_type_get_types();
  $types[] = '<none>';
  foreach ($node_types as $type => $obj) {
    $types[$type] = $obj->name;
  }
  $form['flickrsync_node_type'] = array(
    '#type' => 'select',
    '#title' => t('Node type to use with Flickr Sync'),
    '#default_value' => variable_get('flickrsync_node_type', ''),
    '#options' => $types,
    '#description' => t('You must select a node type that has an imagefield for the Flickr image download and optionally a free-tagging taxonomy vocabulary.'),
  );
  if ($type = variable_get('flickrsync_node_type', '')) {
    //$fields = content_fields(NULL, $type); // doesn't seem to work as expected
    $fields = field_info_fields();

    $field_choices = array();
    $vocab_choices = array();
    
    foreach ($fields as $field_name => $field) {

      // Get field/bundle info. 
      $instance = field_info_instance('node', $field_name, $type);

      if ($field['module'] == 'image' && in_array($type, $field['bundles']['node'])) {
        if (empty($instance)) {
          $instance['label'] = $field_name;
        }
        $field_choices[$field['field_name']] = $instance['label'];
      }
      if ($field['module'] == 'taxonomy' && $instance['widget']['type'] == 'taxonomy_autocomplete') {
        $vocab_machine_name = $field['settings']['allowed_values'][0]['vocabulary'];
        $vocab = taxonomy_vocabulary_machine_name_load($vocab_machine_name);
        $vocab_choices[$vocab->vid] = $vocab->name;
      }
    } 

    if ($field_choices) {
      $form['flickrsync_image_field'] = array(
        '#type' => 'select',
        '#title' => t('Image field for attaching Flickr photo'),
        '#default_value' => variable_get('flickrsync_image_field', ''),
        '#options' => $field_choices,
        '#description' => t('Select the image field to use for attaching Flickr images to Drupal nodes.'),
      );
    }
    else {
      drupal_set_message(t("The node type selected doesn't have any image fields.  Please select a different node type, or add an image field to this node type."), 'error');
    }

    if ($vocab_choices) {
      $form['flickrsync_vocab'] = array(
        '#type' => 'select',
        '#title' => t('Vocabulary for importing Flickr tags'),
        '#default_value' => variable_get('flickrsync_vocab', ''),
        '#options' => $vocab_choices,
        '#description' => t('Select a free-tagging vocabulary to use for importing Flickr tags.'),
      );
    }
    else {
      drupal_set_message(t("The node type selected doesn't have a free tagging vocabulary.
        This is optional, but you want want to consider configuring a vocabulary so that Flickr tags
        can be imported."));
    }
  }
  $form['flickrsync_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout when importing Flickr images'),
    '#default_value' => variable_get('flickrsync_timeout', 30),
    '#description' => t('The number of seconds to allow for an individual image import to complete.'),
  );
  $form['flickrsync_cron_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of Flickr images to import during each cron run'),
    '#default_value' => variable_get('flickrsync_cron_number', 10),
    '#description' => t('Use a low number to avoid PHP timing out during cron, especially if other intensive cron tasks are also running.  Keep in mind that you may need to run cron frequently if lots of Flickr photos need to be imported.'),
  );
  return system_settings_form($form);
}