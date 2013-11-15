<?php

/**
 * @file
 * field_extract support for term_reference field
 */

function field_extract_taxonomy_term_reference_info() {
  return array(
    'options' => array(
      'entity_type' => 'taxonomy_term',
    ),
  );
}
