<?php

//
/*
function relay_card_types_theme_registry_alter(&$theme_registry) {
  // Defined path to current module.
  $module_path = drupal_get_path('module', 'relay_card_types');
  // Find all .tpl.php files in this module's folder recursively.
  $template_file_objects = drupal_find_theme_templates($theme_registry, '.tpl.php', $module_path);
  // Itterate through all found template file objects.
  foreach ($template_file_objects as $key => $template_file_object) {
    // If the template has not already been overridden by a theme.
    //if (!preg_match('#/themes/#', $theme_registry[$key]['theme path'])) {
      // Alter the theme path and template elements.
      $theme_registry[$key]['theme path'] = $module_path;
      $theme_registry[$key] = array_merge($theme_registry[$key], $template_file_object);
    //}
  }
}
*/

//
function relay_card_types_preprocess_page( &$variables ) {

	//add some javascript for relay_card_types
	drupal_add_js( drupal_get_path('module', 'relay_card_types') . '/js/relay_card_types.js');

	//add some css for relay_card-types
	drupal_add_css( drupal_get_path('module', 'relay_card_types') . '/css/relay_card_types.css');

}

//
function relay_card_types_preprocess_node( &$variables ) {

	//an array of our custom content types
	$types = array( 'relay_audio', 'relay_photo', 'relay_editorial', 'relay_article', 'relay_tweet', 'relay_video', 'relay_live' );

	//do this if the type is one of ours
	if( !in_array( $variables['node']->type, $types) )
		return;

	//add card tpl as an option for the valid card types
	$variables['theme_hook_suggestions'][] = 'card';
	$variables['theme_hook_suggestions'][] = 'card_' . $variables['node']->type;
}

//
function relay_card_types_preprocess_taxonomy_term( &$variables ) {

	//is this part of our event system?
	if( $variables['term']->vocabulary_machine_name != 'relay_events' )
		return;

	//add event tpl as an option for this
	$variables['theme_hook_suggestions'][] = 'event';
}

//make images always 100% width and height?
function relay_card_types_image($variables) {
  $attributes = $variables['attributes'];
  $attributes['src'] = file_create_url($variables['path']);

  foreach (array('width', 'height', 'alt', 'title') as $key) {

    if (isset($variables[$key])) {
      $attributes[$key] = $variables[$key];
    }
  }

  return '<figure><img' . drupal_attributes($attributes) . ' /><figcaption></figcaption></figure>';
}








