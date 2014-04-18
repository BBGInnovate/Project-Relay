<?php

/**
 * Defines common fields all cards have (pin card boolean, authors, addthis field, event reference)
 */
function _relay_card_types_base_fields( &$fields ) {

  //
  $fields[] = array(
    'field_name' => 'relay_pin_card', 
    'type' => 'list_boolean', 
    'locked' => TRUE, 
    'cardinality' => 1, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),
    'settings' => array(
      'allowed_values' => array(
        0 => 'No',
        1 => 'Yes',
      ),
      'allowed_values_function' => '',
    ),
  );

  //
  $fields[] = array(
    'field_name' => 'relay_authors', 
    'type' => 'text', 
    'locked' => TRUE, 
    'cardinality' => 1, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  );

  //
  $fields[] = array(
    'field_name' => 'relay_events_ref', 
    'type' => 'taxonomy_term_reference', 
    'locked' => TRUE, 
    'cardinality' => 1, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),
    'settings' => array(
      'allowed_values' => array(
        array(
          'vocabulary' => 'relay_events',
          'parent' => 0
        ),
      ),
    ),
  );  

  //
  $fields[] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'relay_addthis',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'addthis',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'addthis',
  );

  //
  $fields[] = array(
    'field_name' => 'relay_tweet_status_id', 
    'type' => 'text', 
    'locked' => TRUE, 
    'cardinality' => 1, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  );

}
 
/**
 * Defines instances criteria for comming fields
 * (pin card boolean, authors, addthis field, event reference)
 */
function _relay_card_types_base_field_instances( &$instances ) {

  //
  $instances[] = array(
    'field_name' => 'relay_pin_card', // From above.
    'label' => t('Pin Card'),
    'widget' => array(
      'type' => 'options_onoff',
      'settings' => array('display_label' => 1),
    ),
    'settings' => array(
      'allowed_values' => array(
        '0' => 'No',
        '1' => 'Yes',
      )
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        ),
      )
  );

  //
  $instances[] = array(
    'field_name' => 'relay_authors', // From above.
    'label' => t('Authors'),
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'type' => 'text_default',
        'label' => 'hidden',
        ),
      )
  );

  //
  $instances[] = array(
    'field_name' => 'relay_events_ref', // From above.
    'label' => t('Event'),
    'widget' => array(
      'type' => 'options_select',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        ),
      )
  );

  //
  $instances[] = array(
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'addthis',
        'settings' => array(),
        'type' => 'addthis_disabled',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'field_name' => 'relay_addthis',
    'label' => 'Share',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'addthis',
      'settings' => array(),
      'type' => 'addthis_button_widget',
      'weight' => 32,
    ),
  );

  //
  $instances[] = array(
    'field_name' => 'relay_tweet_status_id', // From above.
    'label' => t('Twitter Status Id'),
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        ),
      )
  );
}

/**
 * Audio fields and field instances
 */
function _relay_card_types_audio_fields( &$fields ) {
  
  //
  $fields[] = array(
    'field_name' => 'relay_audio_file', 
    'type' => 'file', 
    'locked' => TRUE, 
    'cardinality' => 1,
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  );
}
 
function _relay_card_types_audio_field_instances( &$instances ) {

  //
  $instances[] = array(
    'field_name' => 'relay_audio_file', // From above.
    'label' => t('Audio File'),
    'settings' => array(
      'file_extensions' => 'mp3'
    ),
    'widget' => array(
      'type' => 'file_generic',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'audio_js'
        ),
      )
  );
}

/**
 * Photos fields and field instances
 */
function _relay_card_types_photo_fields( &$fields ) {

  //
  $fields[] = array(
    'field_name' => 'relay_photo_file', 
    'type' => 'image', 
    'locked' => TRUE, 
    'cardinality' => 1,
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  );
}
 
function _relay_card_types_photo_field_instances( &$instances ) {

  //
  $instances[] = array(
    'field_name' => 'relay_photo_file', // From above.
    'label' => t('Photo File'),
    'settings' => array(
      'file_extensions' => 'gif png jpg jpeg bmp tiff'
    ),
    'widget' => array(
      'type' => 'image_image',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        ),
      )
  );
}

/**
 * Editorial fields and field instances
 */
function _relay_card_types_editorial_fields( &$fields ) {
  
  //
  $fields[] = array(
    'field_name' => 'relay_editor_email', 
    'type' => 'text', 
    'locked' => TRUE, 
    'cardinality' => 1, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  );
}
 
function _relay_card_types_editorial_field_instances( &$instances ) {

  //
  $instances[] = array(
    'field_name' => 'relay_editor_email', // From above.
    'label' => t('Editor Email'),
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'type' => 'text_default',
        'label' => 'hidden',
        ),
      )
  );
}

/**
 * Article fields and field instances
 */
function _relay_card_types_article_fields( &$fields ) {

  //
  $fields[] = array(
    'field_name' => 'relay_more_link', 
    'type' => 'text', 
    'locked' => TRUE, 
    'cardinality' => 1, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  );

}
 
function _relay_card_types_article_field_instances( &$instances ) {

  //
  $instances[] = array(
    'field_name' => 'relay_more_link', // From above.
    'label' => t('More Link'),
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'type' => 'text_default',
        'label' => 'hidden',
        ),
      )
  );
}

/**
 * Tweet fields and field instances
 */
function _relay_card_types_tweet_fields( &$fields ) {
}
 
function _relay_card_types_tweet_field_instances( &$instances ) {
}

/**
 * Videos fields and field instances
 */
function _relay_card_types_video_fields( &$fields ) {
  //
  $fields[] = array(
    'field_name' => 'relay_video_file', 
    'type' => 'file', 
    'locked' => TRUE, 
    'cardinality' => 1,
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  );

  //
  $fields[] = array(
    'field_name' => 'relay_youtube_code', 
    'type' => 'text', 
    'locked' => TRUE, 
    'cardinality' => 1, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  ); 
}
 
function _relay_card_types_video_field_instances( &$instances ) {

  //
  $instances[] = array(
    'field_name' => 'relay_video_file', // From above.
    'label' => t('Video File'),
    'settings' => array(
      'file_extensions' => 'mov mpg m4v'
    ),
    'widget' => array(
      'type' => 'file_generic',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'videojs'
        ),
      )
  );

  //
  $instances[] = array(
    'field_name' => 'relay_youtube_code', // From above.
    'label' => t('YouTube Embed ID'),
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'type' => 'text_default',
        'label' => 'inline',
        ),
      )
  );


}

/**
 * Live fields and field instances
 */
function _relay_card_types_live_fields( &$fields ) {
  //
  $fields[] = array(
    'field_name' => 'relay_live_embed_code', 
    'type' => 'text_long', 
    'locked' => TRUE, 
    'cardinality' => 1, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  );
}
 
function _relay_card_types_live_field_instances( &$instances ) {

  //
  $instances[] = array(
    'field_name' => 'relay_live_embed_code', // From above.
    'label' => t('Embed Code'),
    'widget' => array(
      'type' => 'text_textarea',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        ),
      )
  );
}

/**
 * Events Taxonomy fields and field instances
 */
function _relay_card_types_event_vocab_fields( &$fields ) {
}
 
function _relay_card_types_event_vocab_field_instances( &$instances ) {
}

/**
 * Email Message Source fields and field instances
 */
function _relay_card_types_msg_src_fields( &$fields ) {
  //
  $fields[] = array(
    'field_name' => 'relay_to', 
    'type' => 'text', 
    'locked' => TRUE, 
    'cardinality' => 1, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  ); 

  //
  $fields[] = array(
    'field_name' => 'relay_from', 
    'type' => 'text', 
    'locked' => TRUE, 
    'cardinality' => 1, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  ); 

  //
  $fields[] = array(
    'field_name' => 'relay_from_name', 
    'type' => 'text', 
    'locked' => TRUE, 
    'cardinality' => 1, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  );  

  //
  $fields[] = array(
    'field_name' => 'relay_attachments', 
    'type' => 'file', 
    'locked' => TRUE, 
    'cardinality' => FIELD_CARDINALITY_UNLIMITED, 
    'storage' => array( 
      'type' => 'field_sql_storage',
    ),    
  );  
}
 
function _relay_card_types_msg_src_field_instances( &$instances ) {

  //
  $instances[] = array(
    'field_name' => 'relay_to', // From above.
    'label' => t('To'),
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'type' => 'text_default',
        'label' => 'inline',
        ),
      )
  );

  //
  $instances[] = array(
    'field_name' => 'relay_from', // From above.
    'label' => t('From'),
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'type' => 'text_default',
        'label' => 'inline',
        ),
      )
  );

  //
  $instances[] = array(
    'field_name' => 'relay_from_name', // From above.
    'label' => t('From Name'),
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'type' => 'text_default',
        'label' => 'inline',
        ),
      )
  );

  //
  $instances[] = array(
    'field_name' => 'relay_attachments', // From above.
    'label' => t('Attachments'),
    'settings' => array(
      'file_extensions' => 'mp3 gif png jpg jpeg bmp tiff mov mpg m4v'
    ),
    'widget' => array(
      'type' => 'file_generic',
    ),
    'display' => array(
      'default' => array(
        'label' => 'inline',
        ),
      )
  );
}