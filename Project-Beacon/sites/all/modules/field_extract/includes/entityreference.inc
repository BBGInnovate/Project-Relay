<?php
// $Id$

/**
 * @file
 * field_extract support for date field
 */

function field_extract_entityreference_info() {
  return array(
    'callback' => 'field_extract_entityreference_extract',
    'filepath' => drupal_get_path('module', 'field_extract') . '/includes/entityreference.inc',
    'options' => array(
      'key' => 'target_id',
    ),
  );
}

function field_extract_entityreference_extract($item, $options = array()) {
  $entity_type = $options['field_info']['settings']['target_type'];
  $entity = reset(entity_load($entity_type, array($item[$options['key']])));
  $entity->entity_type = $entity_type;
  return $entity;
}
