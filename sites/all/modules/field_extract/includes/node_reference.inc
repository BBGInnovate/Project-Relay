<?php

/**
 * @file
 * field_extract support for node_reference field
 */

function field_extract_node_reference_info() {
  return array(
    'options' => array(
      'entity_type' => 'node',
    ),
  );
}
