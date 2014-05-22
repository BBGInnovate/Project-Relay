<?php

//
function _relay_card_types_configuration_form($form, &$form_state){

	//
	$form['message'] = array(
		'#markup' => t('<p>Thank you for using Relay.  Please configure the <a href="/admin/structure/mailhandler">mailhandler settings</a> to point to a valid email account.</p><p>Once configured Relay will transform email messages to that account using serveral social tools.</p><p>Installation also requires the following api libraries to be dropped into the sites/all/libraries directory.</p><ul><li><a href="https://github.com/dg/twitter-php/releases/tag/v3.3">Twitter API as twitter_api</a></li><li><a href="https://github.com/google/google-api-php-client">Google YouTube API as youtube_api</a></li><li><a href="https://github.com/vimeo/vimeo.php">Vimeo API as vimeo_api</a></li><li><a href="https://github.com/mptre/php-soundcloud">SoundCloud API as soundcloud_api</a></li></ul><p>For additional help read the Realy install.txt file.</p>')
	);

	//
	$form['flickr'] = array(
	  '#type' => 'fieldset', 
	  '#title' => t('flickr Settings'), 
	  '#weight' => 0, 
	  '#collapsible' => TRUE, 
	  '#collapsed' => !variable_get( 'relay_flickr_enabled', FALSE ) || !variable_get( 'relay_flickr_push_enabled', FALSE ),
	);

	//
	$form['flickr']['relay_flickr_enabled'] = array(
	  '#type' => 'checkbox', 
	  '#title' => t('Enable flickr Polling'),
	  '#description' => t('Polls flickr for items tagged for Relay events.'), 
	  '#weight' => 0, 
  	  '#default_value' => variable_get( 'relay_flickr_enabled', FALSE ), 
    );

	//
	$form['flickr']['relay_flickr_push_enabled'] = array(
	  '#type' => 'checkbox', 
	  '#title' => t('Enable flickr Push'),
	  '#description' => 'Pushes images received as emails to the attached flickr account.', 
	  '#weight' => 0, 
  	  '#default_value' => variable_get( 'relay_flickr_push_enabled', FALSE ), 
    );    

	//
	$form['flickr']['relay_flickr_message'] = array(
	  '#markup' => t('<p>flickr integration uses the flickr API.  Please configure the module to succesfully push or pull messages from flickr.  <a href="">Configure your module</a>.</p>'), 
    );

 	//
	$form['flickr']['relay_flickr_username'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Flickr Username'), 
	  '#weight' => 1, 
	  '#default_value' => variable_get( 'relay_flickr_username', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );

	//
	$form['vimeo'] = array(
	  '#type' => 'fieldset', 
	  '#title' => t('Vimeo Settings'),
	  '#weight' => 0, 
	  '#collapsible' => TRUE, 
	  '#collapsed' => !variable_get( 'relay_vimeo_enabled', FALSE )  || !variable_get( 'relay_vimeo_push_enabled', FALSE ),
	);

	//
	$form['vimeo']['relay_vimeo_enabled'] = array(
	  '#type' => 'checkbox', 
	  '#title' => t('Enable Vimeo Polling'),
	  '#description' => t('Polls Vimeo for items tagged for Relay events.'), 
	  '#weight' => 0, 
  	  '#default_value' => variable_get( 'relay_vimeo_enabled', FALSE ), 
    );

	//
	$form['vimeo']['relay_vimeo_push_enabled'] = array(
	  '#type' => 'checkbox', 
	  '#title' => t('Enable Vimeo Push'),
	  '#description' => 'Pushes videos received as emails to the attached vimeo account.', 
	  '#weight' => 0, 
  	  '#default_value' => variable_get( 'relay_vimeo_push_enabled', FALSE ), 
    );  

	//
	$form['vimeo']['relay_vimeo_application_id'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Application ID'), 
	  '#weight' => 1, 
	  '#default_value' => variable_get( 'relay_vimeo_application_id', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );

	//
	$form['vimeo']['relay_vimeo_application_secret'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Application Secret'), 
	  '#weight' => 1, 
	  '#default_value' => variable_get( 'relay_vimeo_application_secret', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );

	//
	$form['vimeo']['relay_vimeo_access_token'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Access Token'), 
	  '#weight' => 1, 
	  '#default_value' => variable_get( 'relay_vimeo_access_token', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );

	//
	$form['youtube'] = array(
	  '#type' => 'fieldset', 
	  '#title' => t('YouTube Settings'),
	  '#description' => t('To authorize youTube integration activate here: <a href="' . $GLOBALS['base_url'] . '/admin/config/system/relay/youtube_authorize">Activate</a>.  You must provide a valid Client ID and Secret from Google by applying for a <a href="https://console.developers.google.com">developer account</a> and creating a project.'),
	  '#weight' => 0, 
	  '#collapsible' => TRUE, 
	  '#collapsed' => !variable_get( 'relay_youtube_enabled', FALSE ),
	);

	//
	$form['youtube']['relay_youtube_enabled'] = array(
	  '#type' => 'checkbox', 
	  '#title' => t('Enable YouTube Polling'), 
	  '#description' => t('Polls YouTube for items tagged for Relay events.'), 
	  '#weight' => 0, 
  	  '#default_value' => variable_get( 'relay_youtube_enabled', FALSE ), 
    );

 	//
	$form['youtube']['relay_youtube_push_enabled'] = array(
	  '#type' => 'checkbox', 
	  '#title' => t('Enable YouTube Push'),
	  '#description' => 'Pushes videos received as emails to the attached youTube account.', 
	  '#weight' => 0, 
  	  '#default_value' => variable_get( 'relay_youtube_push_enabled', FALSE ), 
    );

	//
	$form['youtube']['relay_youtube_username'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('YouTube Username'), 
	  '#weight' => 1, 
	  '#default_value' => variable_get( 'relay_youtube_username', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );

	//
	$form['youtube']['relay_youtube_client_id'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('YouTube Client ID'), 
	  '#weight' => 2, 
	  '#default_value' => variable_get( 'relay_youtube_client_id', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );

	//
	$form['youtube']['relay_youtube_client_secret'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('YouTube Client Secret'), 
	  '#weight' => 3, 
	  '#default_value' => variable_get( 'relay_youtube_client_secret', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );

	//
	$form['sound_cloud'] = array(
	  '#type' => 'fieldset', 
	  '#title' => t('SoundCloud Settings'),
	  '#weight' => 0, 
	  '#collapsible' => TRUE, 
	  '#collapsed' => !variable_get( 'relay_sound_cloud_enabled', FALSE ) || !variable_get( 'relay_sound_cloud_push_enabled', FALSE ),
	);

	//
	$form['sound_cloud']['relay_sound_cloud_enabled'] = array(
	  '#type' => 'checkbox', 
	  '#title' => t('Enable SoundCloud Polling'), 
	  '#description' => t('Polls SoundCloud for items tagged for Relay events.'), 
	  '#weight' => 0, 
  	  '#default_value' => variable_get( 'relay_sound_cloud_enabled', FALSE ), 
    );

 	//
	$form['sound_cloud']['relay_sound_cloud_push_enabled'] = array(
	  '#type' => 'checkbox', 
	  '#title' => t('Enable SoundCloud Push'),
	  '#description' => 'Pushes videos received as emails to the attached SoundCloud account.', 
	  '#weight' => 0, 
  	  '#default_value' => variable_get( 'relay_sound_cloud_push_enabled', FALSE ), 
    );

	//
	$form['sound_cloud']['relay_sound_cloud_key'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('SoundCloud API Key'), 
	  '#weight' => 1, 
	  '#default_value' => variable_get( 'relay_sound_cloud_key', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );

	//
	$form['twitter'] = array(
	  '#type' => 'fieldset', 
	  '#title' => t('Twitter Settings'),
	  '#description' => t('Sign in to the http://twitter.com and register an application from the http://dev.twitter.com/apps page. Remember
to never reveal your consumer secrets. Click on My Access Token link from the sidebar and retrieve your own access
token. Now you have consumer key, consumer secret, access token and access token secret.'),
	  '#weight' => 0, 
	  '#collapsible' => TRUE, 
	  '#collapsed' => !variable_get( 'relay_twitter_enabled', FALSE ) || !variable_get( 'relay_twitter_push_enabled', FALSE ),
	);

	//
	$form['twitter']['relay_twitter_enabled'] = array(
	  '#type' => 'checkbox', 
	  '#title' => t('Enable Twitter Polling'), 
	  '#description' => t('Polls Twitter for items tagged for Relay events.'), 
	  '#weight' => 0, 
  	  '#default_value' => variable_get( 'relay_twitter_enabled', FALSE ), 
    );	

 	//
	$form['twitter']['relay_twitter_push_enabled'] = array(
	  '#type' => 'checkbox', 
	  '#title' => t('Enable Twitter Push'),
	  '#description' => 'Pushes messages received as emails to the attached Twitter account.', 
	  '#weight' => 1, 
  	  '#default_value' => variable_get( 'relay_twitter_push_enabled', FALSE ), 
    );

 	//
	$form['twitter']['relay_twitter_push_enabled_types'] = array(
	  '#type' => 'checkboxes', 
	  '#title' => t('Content types to push to twitter.'),
	  '#description' => t('Content types to push to twitter.'), 
	  '#weight' => 2, 
	  '#disabled' => !variable_get( 'relay_twitter_push_enabled', FALSE ),
  	  '#default_value' => variable_get( 'relay_twitter_push_enabled_types', array() ),
  	  '#options' => node_type_get_names(), 
    );

	//
	$form['twitter']['relay_twitter_api_key'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Twitter API Key'), 
	  '#weight' => 3, 
	  '#default_value' => variable_get( 'relay_twitter_api_key', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );

	//
	$form['twitter']['relay_twitter_api_secret_key'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Twitter API Secret Key'), 
	  '#weight' => 4, 
	  '#default_value' => variable_get( 'relay_twitter_api_secret_key', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );

	//
	$form['twitter']['relay_twitter_access_token'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Twitter Access Token'), 
	  '#weight' => 5, 
	  '#default_value' => variable_get( 'relay_twitter_access_token', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );

	//
	$form['twitter']['relay_twitter_access_token_secret'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Twitter Access Token Secret'), 
	  '#weight' => 6, 
	  '#default_value' => variable_get( 'relay_twitter_access_token_secret', ''), 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#required' => FALSE,
	 );	 	

	//
	return system_settings_form($form);
}

/*
function _relay_card_types_configuration_form_validate($form, &$form_state, $example_id){
	
}
*/

//This should alter the cron rule of elysia
function _relay_card_types_configuration_form_submit($form, &$form_state, $example_id){
	
}

//
function _relay_card_types_youtube_authorization(){

	//do we have the youtube library
	if( !relay_card_types_verify_youtube_library() )
		return 'YouTube library is not installed.';

    //
    //set_include_path( get_include_path() . PATH_SEPARATOR . '/Users/jasonmperry/Sites/devdesktop/relay_test/sites/all/libraries/youtube_api/src/' );

    //
    $client = new Google_Client();
    $client->setClientId( variable_get( 'relay_youtube_client_id', '') );
    $client->setClientSecret( variable_get( 'relay_youtube_client_secret', '') );
    $client->setScopes( 'https://www.googleapis.com/auth/youtube.upload' );

    //
    //n$redirect = filter_var('http://' . $_SERVER['HTTP_HOST'] . $_SERVER['PHP_SELF'], FILTER_SANITIZE_URL);
    $redirect = filter_var( $GLOBALS['base_url'] . '/admin/config/system/relay/youtube_authorize', FILTER_SANITIZE_URL );
    
    //
    $client->setRedirectUri( $redirect );

    //
	if (isset($_GET['code'])) {

	  //
	  $client->authenticate($_GET['code']);
	  variable_set( 'relay_youtube_token_secret', $_GET['code'] );	  
	  variable_set( 'relay_youtube_token', $client->getAccessToken() );
	  header('Location: ' . $redirect);
	}

	//
	if ( variable_get( 'relay_youtube_token', '' ) != '' ) {
	  $client->setAccessToken( variable_get( 'relay_youtube_token', '' ) );
	}

	//
	return '<a href="'. $client->createAuthUrl() .'">Authorize YouTube</a>';


}










