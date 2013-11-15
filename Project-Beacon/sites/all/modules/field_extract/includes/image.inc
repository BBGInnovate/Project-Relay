<?php

/**
 * @file
 * field_extract support for image field
 */

function field_extract_image_info() {
  return array(
    'options' => array(
      'entity_type' => 'file',
    ),
  );
}
