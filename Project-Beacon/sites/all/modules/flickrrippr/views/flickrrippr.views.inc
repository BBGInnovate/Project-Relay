<?php


function flickrrippr_views_data() {
  flickrrippr_photos_views_data($data);
  flickrrippr_accounts_views_data($data);
  return $data;
}

function flickrrippr_accounts_views_data(&$data) {
  $data['flickrusers']['table']['group'] = t('Flickr Accounts');
  $data['flickrusers']['table']['base'] = array(
    'field' => 'flickrid',
    'title' => t('Account'),
  );

  $data['flickrusers']['uid'] = array(
    'title' => t('User ID'),
//     'help' => t('Description on photo from flickr.com'),
    'field' => array(
      'views_handler_field',
      'click sortable' => false,
    ),
  );

  

    $data['flickrusers']['flickrusername'] = array(
      'title' => t('Username'),
      'help' => t('Name used on flickr.com'),
      'field' => array(
        'views_handler_field',
        'click sortable' => false,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );


  $data['flickrusers']['flickrispro'] = array(
     'title' => t('Pro'),
     'help' => t('Is this a pro account?'),
     'field' => array(
       'handler' => 'views_handler_field_boolean',
       'click sortable' => TRUE,
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_boolean_operator',
       'label' => t('Failed to refetch'),
       'type' => 'yes-no',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
   );

    $data['flickrusers']['flickrphotosurl'] = array(
      'title' => t('Photos Url'),
      'help' => t('Url to photos on flickr.com'),
      'field' => array(
        'views_handler_field',
        'click sortable' => false,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['flickrusers']['flickrmobileeurl'] = array(
      'title' => t('Mobile Url'),
      'help' => t('Url to profile on flickr.com'),
      'field' => array(
        'views_handler_field',
        'click sortable' => false,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['flickrusers']['flickrrealname'] = array(
      'title' => t('Real Name'),
      'help' => t('Real name as set on flickr.com'),
      'field' => array(
        'views_handler_field',
        'click sortable' => false,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['flickrusers']['flickrlocation'] = array(
      'title' => t('Location'),
      'help' => t('Location as set on flickr.com'),
      'field' => array(
        'views_handler_field',
        'click sortable' => false,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );
    
    $data['flickrusers']['flickrprofileurl'] = array(
      'title' => t('Profile Url'),
      'help' => t('Url to profile on flickr.com'),
      'field' => array(
        'views_handler_field',
        'click sortable' => false,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data['flickrusers']['flickravatar'] = array(
      'title' => t('Avatar Url'),
      'help' => t('Url to avatar image'),
      'field' => array(
        'views_handler_field',
        'click sortable' => false,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

}

function flickrrippr_photos_views_data(&$data) {
  $data['flickrphotos']['table']['group'] = t('Flickr');
  $data['flickrphotos']['table']['base'] = array(
    'field' => 'nid',
    'title' => t('Photo'),
  );
  
  $data['flickrphotos']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid'
    ),
    'flickrusers' => array(
      'left_field' => 'flickrid',
      'field' => 'owner_nsid',
    ),
    'help' => t('Photos imported from Flickr.com'),
  );

  $data['flickrphotos']['nid'] = array(
    'title' => t('Photo'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Flickr Photo'),
    )
  );


  $data['flickrphotos']['description'] = array(
    'title' => t('Photo description'),
    'help' => t('Description on photo from flickr.com'),
    'field' => array(
      'views_handler_field',
      'click sortable' => false,
    ),
//     'sort' => array(
//       'handler' => 'views_handler_sort',
//     ),
//     'filter' => array(
//       'handler' => 'views_handler_filter_string',
//     ),
  );


  $data['flickrphotos']['photo'] = array(
    'title' => t('Photo'),
    'help' => t('The pretty photo'),
    'field' => array(
      'field' => 'flickrphoto_id',
      'handler' => 'flickrrippr_handler_photo',
      'click sortable' => FALSE,
    ),
  );

  $data['flickrphotos']['jpeg_path'] = array(
    'title' => t('Jpeg'),
    'help' => t('Full path to the jpeg'),
    'field' => array(
      'field' => 'flickrphoto_id',
      'handler' => 'flickrrippr_handler_photo_path',
      'click sortable' => FALSE,
    ),
  );

  $data['flickrphotos']['avatar'] = array(
    'title' => t('Photo owner avatar'),
    'field' => array(
      'field' => 'owner_nsid',
      'handler' => 'flickrrippr_handler_avatar',
      'click sortable' => FALSE,
    ),
  );


  $data['flickrphotos']['photopage'] = array(
    'title' => t('Flickr Url'),
    'help' => t('URL to this photo on flickr'),
    'field' => array(
      'views_handler_field',
      'click sortable' => false,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );


  $data['flickrphotos']['media'] = array(
    'title' => t('Media Type'),
    'field' => array(
      'views_handler_field',
      'click sortable' => false,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );
  
  $data['flickrphotos']['owner_nsid'] = array(
    'title' => t('Owner NSID'),
    'field' => array(
      'views_handler_field',
      'click sortable' => false,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'relationship' => array(
      'base' => 'flickrusers',
      'field' => 'flickrid',
      'handler' => 'views_handler_relationship',
      'label' => t('Flickr Account'),
    )
  );


  $data['flickrphotos']['lastfetched'] = array(
     'title' => t('Last Fetched from Flickr.com'),
     'help' => t('Updated everytime we refetch a photo'),
     'field' => array(
       'handler' => 'views_handler_field_date',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort_date',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_date',
     ),
  );

  $data['flickrphotos']['flickrphoto_id'] = array(
     'title' => t('Flickr Photo Id'),
     'help' => t('The ID of photo on flickr'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
  );

  $data['flickrphotos']['failed'] = array(
     'title' => t('Failed to refetch'),
     'help' => t('Has fetching from flickr.com failed?'),
     'field' => array(
       'handler' => 'views_handler_field_boolean',
       'click sortable' => TRUE,
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_boolean_operator',
       'label' => t('Failed to refetch'),
       'type' => 'yes-no',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
   );

  $data['flickrphotos']['secret'] = array(
    'title' => t('Photo Secret'),
    'help' => t('Secret string for access to photo from flickr.com'),
    'field' => array(
      'views_handler_field',
      'click sortable' => false,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );
  
  $data['flickrphotos']['dateuploaded'] = array(
    'title' => t('Date Uploaded'),
    'help' => t('when uploaded to flickr.com'),
    'field' => array(
      'views_handler_field',
      'click sortable' => false,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['flickrphotos']['license'] = array(
    'title' => t('Licence'),
    'help' => t('What licence is this photo under?'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );


  $data['flickrphotos']['rotation'] = array(
    'title' => t('Rotation'),
    'help' => t('Has this jpeg been rotated?'),
     'field' => array(
       'handler' => 'views_handler_field_boolean',
       'click sortable' => TRUE,
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_boolean_operator',
       'label' => t('Failed to refetch'),
       'type' => 'yes-no',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
  );

  $data['flickrphotos']['date_posted'] = array(
    'title' => t('Date Posted'),
    'help' => t('when posted to flickr.com'),
    'field' => array(
      'views_handler_field',
      'click sortable' => false,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );


  $data['flickrphotos']['date_taken'] = array(
    'title' => t('Date Taken'),
    'help' => t('Time and date the photo was taken, according to jpeg exif info and/or flickr.com'),
    'field' => array(
      'views_handler_field',
      'click sortable' => false,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['flickrphotos']['date_lastupdate'] = array(
     'title' => t('Last Update'),
     'help' => t('Time and date the photo on flickr.com was last modified/updated'),
     'field' => array(
       'handler' => 'views_handler_field_date',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort_date',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_date',
     ),
  );

  $data['flickrphotos']['views'] = array(
     'title' => t('Views'),
     'help' => t('Number of views of the photo on flickr.com'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
  );

}


/**
 * Implementation of hook_views_handlers().
 */
function project_issue_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'flickrrippr') .'/views/handlers',
    ),
    'handlers' => array(
      'flickrrippr_handler_photo' => array(
        'parent' => 'views_handler_field',
      ),
      'flickrrippr_handler_photo_path' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}



include_once(drupal_get_path('module', 'views') .'/handlers/views_handler_field.inc');

class flickrrippr_handler_photo_path extends views_handler_field   {
  function render($values) {
    $node->nid = $values->nid;
    flickrrippr_load($node);
    return flickrrippr_path($node, $this->options['photo_size']);
  }
  function options_form(&$form, &$form_state) {
    $sizes = _flickr_rippr_jpeg_sizes();
    $form['photo_size'] = array(
      '#title' => t('Photo size'),
      '#type' => 'radios',
      '#options' => $sizes,
      '#default_value' => $this->options['photo_size'],
    );
    parent::options_form($form, $form_state);
  }
}

class flickrrippr_handler_photo extends views_handler_field   {
  function render($values) {
    
    $node->nid = $values->nid;
    flickrrippr_load($node);
    $src = flickrrippr_path($node, $this->options['photo_size']);
    $image = theme('image', $src, $values->node_title, $values->node_title, NULL, FALSE);

    return $image;
     
  }
  function options_form(&$form, &$form_state) {
    $sizes = _flickr_rippr_jpeg_sizes();
    $form['photo_size'] = array(
      '#title' => t('Photo size'),
      '#type' => 'radios',
      '#options' => $sizes,
      '#default_value' => $this->options['photo_size'],
    );
    parent::options_form($form, $form_state);
  }

}

class flickrrippr_handler_avatar extends views_handler_field   {
  function render($values) {

//     $node->nid = $values->nid;
//     flickrrippr_load($node);
    $user = flickrrippr_get_user_by_nsid($values->flickrphotos_owner_nsid);
    
    if(isset($user->flickr_info) && !empty($user->flickr_info->flickravatar)) {
      return theme('image', check_plain($user->flickr_info->flickravatar), check_plain($user->flickr_info->flickrusername), check_plain($user->flickr_info->flickrusername), array(), FALSE);
    }
    return '';
  }

}

function flickrrippr_views_default_views() {
  $view = new view;
  $view->name = 'flickrphotos';
  $view->description = '';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'nid' => array(
      'label' => 'Flickr Photo',
      'required' => 1,
      'id' => 'nid',
      'table' => 'flickrphotos',
      'field' => 'nid',
      'relationship' => 'none',
    ),
    'owner_nsid' => array(
      'label' => 'Flickr Account',
      'required' => 0,
      'id' => 'owner_nsid',
      'table' => 'flickrphotos',
      'field' => 'owner_nsid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'avatar' => array(
      'label' => 'Photo owner avatar',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'avatar',
      'table' => 'flickrphotos',
      'field' => 'avatar',
      'relationship' => 'none',
    ),
    'photo' => array(
      'label' => 'Photo',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'photo',
      'table' => 'flickrphotos',
      'field' => 'photo',
      'relationship' => 'none',
      'size' => 'm',
      'photo_size' => 's',
    ),
    'title' => array(
      'label' => 'Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'views' => array(
      'label' => 'Views',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'views',
      'table' => 'flickrphotos',
      'field' => 'views',
      'relationship' => 'none',
    ),
    'flickrusername' => array(
      'label' => 'Flickr Account name',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'flickrusername',
      'table' => 'flickrusers',
      'field' => 'flickrusername',
      'relationship' => 'owner_nsid',
    ),
    'flickravatar' => array(
      'label' => 'Avatar Url',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'flickravatar',
      'table' => 'flickrusers',
      'field' => 'flickravatar',
      'relationship' => 'owner_nsid',
    ),
    'flickrphotosurl' => array(
      'id' => 'flickrphotosurl',
      'table' => 'flickrusers',
      'field' => 'flickrphotosurl',
    ),
    'flickrispro' => array(
      'id' => 'flickrispro',
      'table' => 'flickrusers',
      'field' => 'flickrispro',
    ),
    'flickrprofileurl' => array(
      'id' => 'flickrprofileurl',
      'table' => 'flickrusers',
      'field' => 'flickrprofileurl',
      'relationship' => 'owner_nsid',
    ),
    'latitude' => array(
      'label' => 'latitude',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'latitude',
      'table' => 'flickrgeo',
      'field' => 'latitude',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'longitude' => array(
      'label' => 'longitude',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'longitude',
      'table' => 'flickrgeo',
      'field' => 'longitude',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'views' => array(
      'order' => 'DESC',
      'id' => 'views',
      'table' => 'flickrphotos',
      'field' => 'views',
      'relationship' => 'none',
    ),
    'dateuploaded' => array(
      'id' => 'dateuploaded',
      'table' => 'flickrphotos',
      'field' => 'dateuploaded',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'failed' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => '',
        'label' => 'Failed to refetch',
        'identifier' => 'failed',
        'optional' => 1,
        'remember' => 0,
      ),
      'id' => 'failed',
      'table' => 'flickrphotos',
      'field' => 'failed',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'time',
    'results_lifespan' => '3600',
    'output_lifespan' => '3600',
  ));
  $handler->override_option('title', 'Photos');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 5);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler = $view->new_display('block', 'Big Block', 'block_1');
  $handler->override_option('fields', array(
    'nid' => array(
      'label' => 'Nid',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 1,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 1,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'photo' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => 'node/[nid]',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'photo',
      'table' => 'flickrphotos',
      'field' => 'photo',
      'relationship' => 'none',
      'size' => 'm',
      'photo_size' => 's',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('sorts', array(
    'dateuploaded' => array(
      'order' => 'DESC',
      'id' => 'dateuploaded',
      'table' => 'flickrphotos',
      'field' => 'dateuploaded',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('items_per_page', 100);
  $handler->override_option('use_pager', FALSE);
  $handler->override_option('style_plugin', 'grid');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'columns' => '8',
    'alignment' => 'horizontal',
    'fill_single_line' => 1,
  ));
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('page', 'Photos Page', 'page_1');
  $handler->override_option('fields', array(
    'nid' => array(
      'label' => 'Nid',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 1,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'avatar' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'avatar',
      'table' => 'flickrphotos',
      'field' => 'avatar',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<h2>[title]</h2>',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'photo' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => 'node/[nid]',
        'link_class' => '',
        'alt' => '[title]',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'photo',
      'table' => 'flickrphotos',
      'field' => 'photo',
      'relationship' => 'none',
      'size' => 'm',
      'photo_size' => 'z',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'views' => array(
      'label' => 'Views',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'views',
      'table' => 'flickrphotos',
      'field' => 'views',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'flickrrippr_photo' => 'flickrrippr_photo',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'failed' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'failed',
      'table' => 'flickrphotos',
      'field' => 'failed',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('items_per_page', 20);
  $handler->override_option('style_plugin', 'default');
  $handler->override_option('row_options', array(
    'inline' => array(
      'photo' => 'photo',
      'title' => 'title',
    ),
    'separator' => '',
    'hide_empty' => 0,
  ));
  $handler->override_option('path', 'photos');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Photos',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'tab',
    'title' => 'Photos',
    'description' => '',
    'weight' => '0',
    'name' => 'primary-links',
  ));
  $handler = $view->new_display('page', 'Time Map', 'page_3');
  $handler->override_option('fields', array(
    'photo' => array(
      'label' => 'Photo',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'photo',
      'table' => 'flickrphotos',
      'field' => 'photo',
      'relationship' => 'none',
      'size' => 'm',
      'photo_size' => 't',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'title' => array(
      'label' => 'Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'views' => array(
      'label' => 'Views',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'views',
      'table' => 'flickrphotos',
      'field' => 'views',
      'relationship' => 'none',
    ),
    'latitude' => array(
      'label' => 'latitude',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'latitude',
      'table' => 'flickrgeo',
      'field' => 'latitude',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'longitude' => array(
      'label' => 'longitude',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'longitude',
      'table' => 'flickrgeo',
      'field' => 'longitude',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'created' => array(
      'label' => 'Post date',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'date_format' => 'small',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'failed' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => '',
        'label' => 'Failed to refetch',
        'identifier' => 'failed',
        'optional' => 1,
        'remember' => 0,
      ),
      'id' => 'failed',
      'table' => 'flickrphotos',
      'field' => 'failed',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'latitude' => array(
      'operator' => 'not empty',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'case' => 1,
      'id' => 'latitude',
      'table' => 'flickrgeo',
      'field' => 'latitude',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'longitude' => array(
      'operator' => 'not empty',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'case' => 1,
      'id' => 'longitude',
      'table' => 'flickrgeo',
      'field' => 'longitude',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'timemap');
  $handler->override_option('style_plugin', 'timelinemap');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'display' => array(
      'width' => '100%',
      'tlheight' => '400px',
      'mheight' => '400px',
      'embed_link' => 0,
      'layers' => array(
        'layer' => array(),
        'overlay' => '',
        'defaultlayer' => 'map',
      ),
    ),
    'datasource' => 'basic',
    'fields' => array(
      'title' => 'title',
      'link' => 1,
      'description' => 'title',
      'table' => array(
        'photo' => array(
          'weight' => '1',
          'added' => 0,
        ),
        'title' => array(
          'weight' => '2',
          'added' => 0,
        ),
        'views' => array(
          'weight' => '3',
          'added' => 0,
        ),
        'latitude' => array(
          'weight' => '4',
          'added' => 0,
        ),
        'longitude' => array(
          'weight' => '5',
          'added' => 0,
        ),
        'created' => array(
          'weight' => '6',
          'added' => 0,
        ),
      ),
      'icon' => '',
      'start' => 'created',
      'end' => '',
      'latitude' => 'latitude',
      'longitude' => 'longitude',
    ),
    'pathcolor' => '',
    'colors' => array(
      'values' => 'custom',
      'custom_values' => array(
        'yellow' => 'yellow',
        'green' => 'green',
        'light blue' => 'light blue',
        'orange' => 'orange',
        'purple' => 'purple',
        'blue' => 'blue',
        'red' => 'red',
      ),
    ),
    'bands' => array(
      'band1_unit' => 'DAY',
      'band2_unit' => 'MONTH',
    ),
  ));
  $handler->override_option('path', 'photos/timemap');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Timeline',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'Shadow Box', 'page_2');
  $handler->override_option('fields', array(
    'jpeg_path' => array(
      'label' => 'Path to Jpeg',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 1,
      'id' => 'jpeg_path',
      'table' => 'flickrphotos',
      'field' => 'jpeg_path',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'photo_size' => 'b',
    ),
    'title' => array(
      'label' => 'Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 1,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'photo' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => '[jpeg_path]',
        'link_class' => '',
        'alt' => '[title] ',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'photo',
      'table' => 'flickrphotos',
      'field' => 'photo',
      'relationship' => 'none',
      'size' => 'm',
      'photo_size' => 't',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('sorts', array(
    'dateuploaded' => array(
      'order' => 'DESC',
      'id' => 'dateuploaded',
      'table' => 'flickrphotos',
      'field' => 'dateuploaded',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Shadowbox');
  $handler->override_option('items_per_page', 120);
  $handler->override_option('style_plugin', 'grid');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'columns' => '6',
    'alignment' => 'horizontal',
    'fill_single_line' => 1,
  ));
  $handler->override_option('path', 'photos/shadowbox');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Shadowbox',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  
  $views[$view->name] = $view;

  return $views;
}