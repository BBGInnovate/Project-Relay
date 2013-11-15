<?php

/**
 * @file
 * field_extract support for user_reference field
 */

function field_extract_user_reference_info() {
  return array(
    'options' => array(
      'entity_type' => 'user',
    ),
  );
}
