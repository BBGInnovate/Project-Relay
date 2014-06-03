<?php
/**
 * @file
 * relay_default_content.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function relay_default_content_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Test Event',
    'description' => '',
    'format' => 'full_html',
    'weight' => 0,
    'uuid' => '4dbc1135-244a-424a-850b-02444abba9f0',
    'vocabulary_machine_name' => 'relay_events',
    'relay_hash_tag' => array(
      'und' => array(
        0 => array(
          'value' => 'testEvent',
          'format' => NULL,
          'safe_value' => 'testEvent',
        ),
      ),
    ),
  );
  return $terms;
}
