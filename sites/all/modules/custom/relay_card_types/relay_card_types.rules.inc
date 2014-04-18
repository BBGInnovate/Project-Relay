<?php

/**
* Implementation of hook_rules_event_info().
* @ingroup rules
*/
function relay_card_types_rules_event_info() {
  
  //defines the events this module broadcasts
  $events = array(
    'relay_card_types_poll_elapsed' => array(
      'label' => t('Relay Poll Interval Elapsed.'),
      'group' => t('Relay'),
      'module' => 'relay_card_types'
    ),
  );

  //
  return $events;
}

//listens for cron tasks to run and invokes tasks
function relay_card_types_poll_cron(){

  //track the time the cron ran for next time
  variable_set( 'relay_cron_last_run', time() );

  //invoke cron to run so mailhandler happens too
  //this should also run our rule to check for files 
  //drupal_cron_run();

  //until we can find a better solution this
  //will invoke our action and let us know things are running
  //Well I guess runing cron this often mean this too,, right?
  _relay_card_types_run_poll();
}

//
function _relay_card_types_run_poll(){

  //display a watchdog message
  watchdog( 'relay_card_types', t('Relay Poll interval has elapsed.') );

  //when the poll period ellapses do this
  rules_invoke_event( 'relay_card_types_poll_elapsed' );
}

/**
 * Implementation of hook_rules_action_info().
 */
function relay_card_types_rules_action_info() {
  
  //defines the action to create cards from messages
  $actions = array(
    'relay_card_types_check_mailhandler' => array(
      'label' => t('Check mailhandler.'),
      'group' => t('Relay'),
      'module' => 'relay_card_types',
    ),
    'relay_card_types_process_message' => array(
      'label' => t('Process new mail messages and create cards..'),
      'group' => t('Relay'),
      'module' => 'relay_card_types',
      'parameter' => array(
        'message_id' => array('type' => 'node', 'label' => t('The id of the relay email message received') ),
      )
    ),
    'relay_card_types_pull_from_flickr' => array(
      'label' => t('Pull Flickr images into Relay.'),
      'group' => t('Relay'),
      'module' => 'relay_card_types',
    ),
    'relay_card_types_pull_from_youtube' => array(
      'label' => t('Pull YouTube videos into Relay.'),
      'group' => t('Relay'),
      'module' => 'relay_card_types',
    ),
    'relay_card_types_pull_from_vimeo' => array(
      'label' => t('Pull Vimeo videos into Relay.'),
      'group' => t('Relay'),
      'module' => 'relay_card_types',
    ),
    'relay_card_types_pull_from_sound_cloud' => array(
      'label' => t('Pull SoundCloud images into Relay.'),
      'group' => t('Relay'),
      'module' => 'relay_card_types',
    ),
    'relay_card_types_pull_from_twitter' => array(
      'label' => t('Pull Twitter images into Relay.'),
      'group' => t('Relay'),
      'module' => 'relay_card_types',
    ),            
  );

  //
  return $actions;
} 

//
function relay_card_types_node_insert( $message ){

  //create a new message when an email ius received
  //if( $message->type != 'relay_msg_src' )
    //return;
}


function relay_card_types_process_message( $message ){

  //
  watchdog( 'relay_card_types', t('Process Relay Email Message and convert to matching type.') );
  
  //
  $published = false;  //determines if the user has permission to publish the record
  $success = false;   //tracks if the action happened succesfully or not

  //parse the message and expand it using the elements and hash values
  _relay_card_types_parse_message( $message );

  //loads the user loaded and determines if they are valid
  $author = _relay_card_types_locate_user( $message->relay_from[$message->language][0]['value'] );

  //determine if we have a user or not
  if( $author != null && user_access( 'email cards to relay', $author ) ){

    //look at the user's role and determine if they have permission to make this item published or not
    if( user_access( 'publish cards by email to relay', $author ) ){
  
      //mark it as published on default
      $published = true;
    }

  } else {

    //this person does not have permission to post
    watchdog( 'relay_card_types', t('Message was ignored, the user does not have permission to post. Message has been archived for review.') );

  	//no user no reason to process this message
  	return;
  }

  //determine which node type relates to the message pulled in
  switch ( $message->card_type ) {
    case 'audio':
      $success = _relay_card_types_create_audio( $message, $author, $published );
    break;

  	case 'photo':
  	  $success = _relay_card_types_create_photo( $message, $author, $published );
  	break;

  	case 'update':
  	  $success = _relay_card_types_create_editorial( $message, $author, $published );
  	break;

  	case 'article':
  	  $success = _relay_card_types_create_article( $message, $author, $published );
  	break;

  	case 'tweet':
  	  $success = _relay_card_types_create_tweet( $message, $author, $published );
  	break;

  	case 'video':
  	  $success = _relay_card_types_create_video( $message, $author, $published );
  	break;

  	case 'live':
  	  $success = _relay_card_types_create_live_stream( $message, $author, $published );
  	break;

    /*
    case 'event':
      $success = 
    break;
    */

  	default:
  	  $success = false; //no value found so it fails
 	  break;
  }

  //restore the session state
  //$user = $current_user;
  //drupal_save_session( $old_state );

  //if it was succesful lets delete the message to clean out the original data
  if( $success ){

    //
    watchdog( 'relay_card_types', t('New message of type ' . $message->card_type .' created.') );
  
  //if it failed to convert
  }else{

    //
    watchdog( 'relay_card_types', t('Message creation failed.  Message deleted.') );

    //send an email to the user explaining possible fixes
    _relay_card_types_create_failed( $message );

  }

  //delete the message regardless
  node_delete( $message->nid );

}

//forces the mailhandler to run right now and grab any cards
//waiting to be created
function relay_card_types_check_mailhandler(){

  //do this as an admin
  /*
  global $user;
  $current_user = $user;
  $old_state = drupal_save_session();
  drupal_save_session( false );
  $user = user_load(1);
  */

  //grab the configured mailhandler and attempt to feed in all data
  $mailhandlerFeed = feeds_source('message_importer');

  //capture any exceptions caused by this call
  try{

    //The delay between page loads and the status messages reported are
    //an issue.  I'm trying to see if this is really an issue and if the
    //delay the user sees can be fixed.  1 minute interval may be too much

    //
    //$mailhandlerFeed->import();
    //$mailhandlerFeed->startImport();
    while( FEEDS_BATCH_COMPLETE != $mailhandlerFeed->import() );

  //it failed so lets capture that and no it happened
  }catch(Exception $e){

    //log the error message
    watchdog( 'relay_card_types', t( $e->getMessage() ) );
  }

  //restore the session state
  /*
  $user = $current_user;
  drupal_save_session( $old_state );
  */
}

//This action pulls all images tagged for relay from flickr
function relay_card_types_pull_from_flickr(){

  //is the service enabled and should we poll it?
  if( !variable_get( 'relay_flickr_enabled', FALSE ) ) 
    return;

  //
  watchdog( 'relay_card_types', t('Relay flickr pull action begin.') );

  //invoke a call to the flickr api
  $flickr = flickrapi_phpFlickr(); //should return back an instance of the flickr php service

  //retreive the attached user account
  $user = $flickr->people_findByUsername( variable_get( 'relay_flickr_username', '' ) );

  //
  if( $user == '' ){

    //
    watchdog( 'relay_card_types', t('Relay flickr pull action failed.  Username is required.') );

    //
    return;
  }

  //retreive the taxonomy terms we want to look at and turn into a space delimeted list
  $tags = '';

  //retreuve all the events available
  $vocab = taxonomy_vocabulary_machine_name_load( 'relay_events' );
  $terms = taxonomy_get_tree( $vocab->vid );

  //create a comma delemeted list of all the possible options
  foreach( $terms as $term ) {

    //handles the to lowercase and space removal
    $buffer = preg_replace('/\s*/', '', $term->name);
    $buffer = strtolower($buffer);    
    
    $tags .= $buffer . ',';
  }

  //remove trailing commas
  $tags = rtrim($tags, ",");

  //request these items from flickr
  $photos = $flickr->people_getPhotos( $user['id'] );//, array( 'tags' => $tags, "tag_mode"=>"any" ) );

  //an array of photos returned
  foreach ($photos['photos']['photo'] as $photo) {
    
    //verify if the photo was uploaded already, if so skip her
    $title = $photo['title'];
    $path = $flickr->buildPhotoURL( $photo, 'large' );

    //get the file path of this asset
    $keys = parse_url($path);
    $paths_items = explode( '/', $keys['path'] );
    $file_name = array_pop( $paths_items );

    //determine if we have a file with this path already
    $results = db_query( 'SELECT * FROM file_managed WHERE filename=:filename', array( ':filename' => $file_name ) );

    //did we find this filename already there?
    if( $results->rowCount() > 0 )
      continue; //oops we got results.  Lets consider as already existing

    //if we do not get the full information about this photo
    $photo_details = $flickr->photos_getInfo( $photo['id'] );

    //seeds a default event
    $tag = variable_get( 'relay_default_event', 0 );

    //iterate through the tags returned
    foreach( $photo_details['photo']['tags']['tag'] as $buffer ){
      $buffer = _relay_card_types_locate_event( $buffer['raw'] );

      $tag = $buffer != variable_get( 'relay_default_event', 0 ) ? $buffer : variable_get( 'relay_default_event', 0 );
    }

    //create the message object that reflects the structure of a message
    $message = new stdClass();

    //
    $message->card_type = 'photo';
    $message->card_event = $tag;
    $message->card_title = $photo_details['photo']['title'];
    $message->card_pin = false;
    $message->card_body = $photo_details['photo']['description'];;
    $message->card_author = 'Flickr';  
    $message->language = 'und';
    $message->relay_attachments[$message->language] = system_retrieve_file( $path, null, true, true );  //gets the file and stores it on the file system

    //create the card
    _relay_card_types_create_photo( $message, user_load(1), true, true );

    //report that we got one!
    watchdog( 'relay_card_types', t('Relay Flickr picture ' . $message->card_title . ' was created.') );      
  }

}

//This action pulls all videos tagged for relay from youtube
function relay_card_types_pull_from_youtube(){

  //is the service enabled and should we poll it?
  if( !variable_get( 'relay_youtube_enabled', FALSE ) ) 
    return;  

  //
  watchdog( 'relay_card_types', t('Relay YouTube pull action begin.') );


  //fetches 50 most recent videos from site using youtube call
  $feedURL = 'http://gdata.youtube.com/feeds/api/users/'. variable_get( 'relay_youtube_key', '') . '/uploads?max-results=5';
  $sxml = simplexml_load_file($feedURL);

  //iterate through each of the 50 entries
  foreach ($sxml->entry as $entry) {

    //search the title for a hashtag
    preg_match( '/#(\w+)/', (String)$entry->title, $card_tag_match );

    //did we get a hashtag?
    if( count( $card_tag_match ) < 2 )
      continue; //nope so lets just keep going

    //if we did do we have a hash of a valid event name?
    $tag = _relay_card_types_locate_event( $card_tag_match[1] );

    //if we can't match the event then forget about it
    if( $tag = variable_get( 'relay_default_event', 0 ) )
      continue; //we are not interested in this hash

    //captures the url value of the video
    preg_match('/[\\?\\&]v=([^\\?\\&]+)/', (String)$entry->link['href'], $youtube_id_matches );

    //make sure we actually got an id
    if( count( $youtube_id_matches ) < 2 )
      continue; //fail... so move on

    //ok so we have a video with a matching event.  Does it already exist?
    //we should be able to query the field relay_youtube_code for any instance of this code.  If its there we have this video already
    $results = db_query( 'SELECT * FROM field_data_relay_youtube_code WHERE relay_youtube_code_value = :relay_youtube_code', array( ':relay_youtube_code' => $youtube_id_matches[1] ) );

    //did we find this? is it already there?
    if( $results->rowCount() > 0 )
      continue; //oops we got results.  Lets consider as already existing

    //it dosen't exist so lets create a video element using the provided name
    $message = new stdClass();

    //
    $message->card_type = 'video';
    $message->card_event = $tag;
    $message->card_title = (String)$entry->title;
    $message->card_pin = false;
    $message->card_body = (String)$entry->content . '<object width="425" height="350" data="http://www.youtube.com/v/' . $youtube_id_matches[1] . '" type="application/x-shockwave-flash"><param name="src" value="http://www.youtube.com/v/' . $youtube_id_matches[1] . '" /></object>';
    $message->card_author = 'YouTube';  
    $message->language = 'und';
    $message->relay_youtube_code = $youtube_id_matches[1];
    //$message->relay_attachments[$message->language] = system_retrieve_file( $path, null, true, true );  //gets the file and stores it on the file system

    //create the card
    _relay_card_types_create_video( $message, user_load(1), true, true ); 

    //report that we got one!
    watchdog( 'relay_card_types', t('Relay YouTube video ' . $message->card_title . ' was created.') );  
  }

}

//This action pulls all videos tagged for relay from vimeo
function relay_card_types_pull_from_vimeo(){

  //is the service enabled and should we poll it?
  if( !variable_get( 'relay_vimeo_enabled', FALSE ) || !relay_card_types_verify_vimeo_library() ) 
    return;

  //
  watchdog( 'relay_card_types', t('Relay Vimeo pull action begin.') );


}

//This action pulls all audio files tagged for relay from soundcloud
function relay_card_types_pull_from_sound_cloud(){

  //is the service enabled and should we poll it?
  if( !variable_get( 'relay_sound_cloud_enabled', FALSE ) || !relay_card_types_verify_sound_cloud_library() ) 
    return;

  //
  watchdog( 'relay_card_types', t('Relay SoundCloud pull action begin.') );

}

//This action pulls all audio files tagged for relay from twitte
function relay_card_types_pull_from_twitter(){

  //is the service enabled and should we poll it?
  if( !variable_get( 'relay_twitter_enabled', FALSE ) || !relay_card_types_verify_twitter_library() ) 
    return;

  //
  watchdog( 'relay_card_types', t('Relay Twitter pull action begin.') );

  //create an instance of twitter
  $twitter = new Twitter( variable_get( 'relay_twitter_api_key', ''), variable_get( 'relay_twitter_api_secret_key', ''), variable_get( 'relay_twitter_access_token', ''), variable_get( 'relay_twitter_access_token_secret', '') );

  //pull the last post made by this user over the last few days
  $statuses = $twitter->load(Twitter::ME);

  //iterate through the posts to see if any of these should be moved into the site as embeds
  foreach( $statuses as $status ){

    //search tweet text for the hash tag that matches
    preg_match_all( '/#(\w+)/','This is a tweet with multiple #hash1 #hash2 #hash3 #hash4', $card_tag_matches );

    //do we have results?
    if( count( $card_tag_matches ) > 1 ){

      //iterate through each tag
      foreach( $card_tag_matches[1] as $buffer ){

        //see if this is a valid event
        $buffer = relay_card_types_locate_event( $buffer );

        //if it is not a valid event lets keep on on
        if( $buffer == variable_get( 'relay_default_event', 0 ) )
          continue;

        //set the tag var
        $tag = $buffer;

        //we have a matching event lets use this one
        break;
      }

    }

    //
    if( $buffer == variable_get( 'relay_default_event', 0 ) )
      continue; 

    //how will we determine if the tweet is here?
    //we should be able to search on the relay_tweet_status_id accross all fields.  Any with this same status id already exist
    $results = db_query( 'SELECT * FROM  field_data_relay_tweet_status_id WHERE relay_tweet_status_id_value = :relay_tweet_status_id', array( ':relay_tweet_status_id' => $status->id ) );

    //did we find this? is it already there?
    if( $results->rowCount() > 0 )
      continue; //oops we got results.  Lets consider as already existing

    //it dosen't exist so lets create a video element using the provided name
    $message = new stdClass();

    //
    $message->card_type = 'tweet';
    $message->card_event = 1;//$tag;
    $message->card_title = 'From Twitter';
    $message->card_pin = false;
    $message->card_body = '<blockquote class="twitter-tweet" lang="en">' . $status->text . '<a href="https://twitter.com/lNVENTlONS/statuses/' . $status->id . '">' . $status->created_at . '</a></blockquote><script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>';
    $message->card_author = 'Twitter';  
    $message->language = 'und';
    $message->relay_tweet_status_id = $status->id;
    //$message->relay_attachments[$message->language] = system_retrieve_file( $path, null, true, true );  //gets the file and stores it on the file system

    //create the card
    _relay_card_types_create_tweet( $message, user_load(1), true, true ); 

    //report that we got one!
    watchdog( 'relay_card_types', t('Relay Twitter tweet ' . $message->card_title . ' was created.') );  
  }
}

//reads the body of the message, parses it, and translates the elements
function _relay_card_types_parse_message( &$message ){

  //all of the possible types
  $types = array( 'article', 'audio', 'update', 'tweet', 'video', 'photo', 'live' );

  //looks for the hashtags of type and taxonomy in the subject
  preg_match_all( '/#(\w+)/', $message->title, $card_type_and_tax_match );

  //
  $card_event_filtered = '';
  $card_type = '';
  $card_pin = false;

  //otherwise lets loop through and determine what we have here
  foreach ($card_type_and_tax_match[1] as $value) {
    
    //is this a type?
    if( in_array(strtolower($value), $types) ){
      $card_type = $value;

    //is this a pin?
    } else if( strtolower($value) == 'pin' ){
      $card_pin = true;

    //must be the event name?
    } else {
      $card_event_filtered = $value;
    }
  }

  //we have one requirement.  Must have a valid cart type.  If not fail now
  if( !isset( $card_type ) || $card_type == '' )
    return;

  //variable to create and store for the message
  //$card_title =  ltrim( preg_replace( '/#(\w+)/','', $message->title) );  //the title of the card - hash
  //$card_body = $message->body[$message->language][0]['value'];

  //
  $current_body = str_replace( array( "\r", "\r\n", "\n\r" ), "\n", $message->body[$message->language][0]['value'] );
  $body_matches = explode( "\n", $current_body, 2);
  $card_title = $body_matches[0]; //sets the title as the first line of the body or the entire body if no line is present
  $card_body = count( $body_matches ) > 1 ? $body_matches[1] : '';  //get the second index and use it as the body

  //returns the card taxonomy id for this element  
  $card_event = _relay_card_types_locate_event( $card_event_filtered );

  //reads in the message body and author
  $card_author = $message->relay_from_name[$message->language][0]['value'];

  //takes the results and stores them in the message for creation
  $message->card_type = $card_type;
  $message->card_event = $card_event;
  $message->card_title = $card_title;
  $message->card_pin = $card_pin ? 1 : 0;
  $message->card_body = $card_body;
  $message->card_author = $card_author;
}

//iterates through the attachments and returns the first to meet our requirements
function _relay_card_types_process_attachments( $type, $attachments ){

  //
  $file = null;
  $formats = array();
  $audio_formats = array('audio/mpeg','auido/mp3');
  $photo_formats = array('image/png','image/jpeg','image/gif');
  $video_formats = array('video/quicktime','video/mpeg','video/mp4','video/mov');

  //determine the format to compare with
  switch ($type) {
    case 'audio':
      $formats = $audio_formats;
    break;

    case 'photo':
      $formats = $photo_formats;
    break;

    case 'video':
      $formats = $video_formats;
    break;
  }

  //iterate through the attachemnts array
  foreach ($attachments as $attached_file) {

    //loads the full information about this file from the database
    //if( is_array($attached_file) )
      $attached_file = file_load( $attached_file['fid'] );
    //else
      //$attached_file = file_load( $attached_file->fid );

    //if the file is in the formats
    if( in_array( $attached_file->filemime, $formats) ){

      //set this as the file to return
      $file = array();
      $file['fid'] = $attached_file->fid;
      $file['filemime'] = $attached_file->filemime;
      $file['filename'] = $attached_file->filename;
      $file['uri'] = $attached_file->uri;
      $file['filesize'] = $attached_file->filesize;
      $file['uid'] = $attached_file->uid;
      $file['timestamp'] = $attached_file->timestamp;
      $file['status'] = $attached_file->status;
      $file['display'] = 1;

      //no need to keep looping
      break;
    }
  }

  return $file;
}

//determine user who created the message using the email address
function _relay_card_types_locate_user( $email ){

  //attempt to fetch the user who sent the message
  $author = user_load_by_mail( $email );

  //if no user loaded return back a null element
  if( !$author ) return null;

  //
  return $author;
}

//takes the event hashtag and finds the matching event taxonomy
function _relay_card_types_locate_event( $event_name ){

  //get the default card event
  $card_event = variable_get( 'relay_default_event', 0 );

  //if the passed in event does not exist use the default
  if( $event_name == null )
    return $card_event;

  //filtered term
  $filter_term = str_replace( "_"," ", $event_name );
  $filter_term = str_replace( "-"," ", $event_name );

  //
  $taxonomy_terms = taxonomy_get_term_by_name( $filter_term );

  //
  if( count( $taxonomy_terms ) > 0 ){

    //
    $card_event = array_shift($taxonomy_terms)->tid;
  }

  //
  return $card_event;
}

//if it fails send this message to the user alerting them how to fix things
function _relay_card_types_create_failed( $message ){

  //defines criteria needed to send the message
  $message = array(
    'id' =>  'relay_card_types_create_failed_email',
    'to' => $message->relay_from[$message->language][0]['value'],
    'subject' => 'Relay Create Failed',
    'body' => array(
      'First line of the message.',
      'Second line of the message'
    ),
    'headers' => array(
      'From' => variable_get('system_mail', 'example@example.com'), 
      'Sender' => variable_get('system_mail', 'example@example.com'), 
      'Return-Path' => variable_get('system_mail', 'example@example.com'),
    ),
  );

  //get a reference to send the message
  $system = drupal_mail_system( 'relay_card_types', 'relay_card_types_create_failed_email');

  //formats the message for delivery
  $message = $system->format($message);

  //sends the message
  $system->mail($message);

}

//parses the bare minimum to set create a node with shared fields (i.e. a card)
function _relay_card_types_create_card( $message, $author, $published ){

  //creates a basic node of type card and inserts the items into it
  $node = new stdClass();

  //provides the language and the title of the node
  $node->title    = $message->card_title;
  $node->language = $message->language;

  //sets the body element of the node
  $node->body[$node->language][0]['value']   = $message->card_body;
  $node->body[$node->language][0]['summary'] = text_summary('');
  $node->body[$node->language][0]['format']  = 'full_html';

  //sets the author element of the node
  $node->relay_authors[$node->language][0]['value']   = $message->card_author;
  $node->relay_authors[$node->language][0]['format']  = NULL;

  //sets the event term reference of the card
  $node->relay_events_ref[$node->language][0]['tid'] = $message->card_event;

  //sets teh user who is publishing this article
  $node->uid = $author->uid;

  //sets if this item is published or not
  $node->status = $published ? '1' : '0'; //1 is published 0 is not

  //disable or enable the comments system
  $node->comment = 0; // 0 = comments disabled, 1 = read only, 2 = read/write

  //sets the pin value of the card
  $node->relay_pin_card[$node->language][0]['value'] = $message->card_pin;

  //returns back the card
  return $node;
}

//parse the body of the node to create a audio instance
function _relay_card_types_create_audio( $message, $author, $published ){

  //creates a card as the base of the instance
  $card = _relay_card_types_create_card( $message, $author, $published );

  //customize the card to make it a photo
  $card->type = 'relay_audio';

  //determine if we have an attachment that meets our qualifications
  $file = _relay_card_types_process_attachments( 'audio', $message->relay_attachments[$message->language] );

  //the file attached was invalid, do not publish
  if( $file == null ){
    return FALSE;
  }

  //attach the file to the content type
  $card->relay_audio_file[$card->language][0] = $file;

  //
  node_object_prepare($card);  //prefills many default values as needed

  //saves the card to th database
  node_save( $card );

  //is this type in this list?
  if( variable_get( 'relay_twitter_push_enabled', FALSE ) && in_array( $card->type, variable_get( 'relay_twitter_push_enabled_types', array() ) ) ){

    //push this item to twitter
    _relay_card_types_push_to_twitter( $card );
  }

  //push the audio clip to sound cloud as well
  if( variable_get( 'relay_sound_cloud_push_enabled', FALSE ) ){
    
    if (($library = libraries_detect('soundcloud_api')) && !empty($library['installed'])) {
      
      //The library is installed. Awesome! Load it
      libraries_load('soundcloud_api');

      //use the api to upload audio

    }
    else {
      
      // This contains a short status code of what went wrong, such as 'not found'.
      $error = $library['error'];
      
      // This contains a detailed (localized) error message.
      $error_message = $library['error message'];

      //no library so the attemp failed
      watchdog( 'relay_card_types', t($error_message) );
    }

  }

  //
  return true;
}

//parse the body of the node to create a photo instance
function _relay_card_types_create_photo( $message, $author, $published, $pushed=false ){

  //creates a card as the base of the instance
  $card = _relay_card_types_create_card( $message, $author, $published );

  //customize the card to make it a photo
  $card->type = 'relay_photo';

  //determine if we have an attachment that meets our qualifications
  $file = _relay_card_types_process_attachments( 'photo', $message->relay_attachments[$message->language] );

  //the file attached was invalid, do not publish
  if( $file == null ){
    return FALSE;
  }

  //attach the file to the content type
  $card->relay_photo_file[$card->language][0] = $file;

  //is this type in this list?
  if( !$pushed && variable_get( 'relay_twitter_push_enabled', FALSE ) && in_array( $card->type, variable_get( 'relay_twitter_push_enabled_types', array() ) ) ){

    //push this item to twitter
    _relay_card_types_push_to_twitter( $card, $status_id );

    //stores the status id so we see if we have this later
    $card->relay_tweet_status_id[$card->language][0]['value'] = $status_id;
  }

  //
  node_object_prepare($card);  //prefills many default values as needed

  //saves the card to th database
  node_save( $card );

  //push the photo to flickr as well
  if( !$pushed && variable_get( 'relay_flickr_push_enabled', FALSE ) ){

    //invoke a call to the flickr api
    $flickr = flickrapi_phpFlickr(); //should return back an instance of the flickr php service

    //determine the tags to apply to this asset
    $tags = '';

    //sets the token from app authorization
    $flickr->setToken( $_GET['frob'] );

    //upload this item to flickr, do it async
    //for later figure out how to make the photo upload happen.. is that a binary file?
    $flickr->sync_upload( drupal_realpath( $file->uri ), $card->title, $card->body[$node->language][0]['value'], $tags, TRUE, null, null );
  }

  //
  return true;
}

//parse the body of the node to create a article instance
function _relay_card_types_create_article( $message, $author, $published ){

  //creates a card as the base of the instance
  $card = _relay_card_types_create_card( $message, $author, $published );

  //customize the card to make it a article
  $card->type = 'relay_article';

  //is this type in this list?
  if( variable_get( 'relay_twitter_push_enabled', FALSE ) && in_array( $card->type, variable_get( 'relay_twitter_push_enabled_types', array() ) ) ){

    //push this item to twitter
    _relay_card_types_push_to_twitter( $card, $status_id );

    //stores the status id so we see if we have this later
    $card->relay_tweet_status_id[$card->language][0]['value'] = $status_id;
  }

  //
  node_object_prepare( $card );  //prefills many default values as needed  

  //saves the card to th database
  node_save( $card );

  //
  return true;
}

//parse the body of the node to create a editorial instance
function _relay_card_types_create_editorial( $message, $author, $published ){

  //creates a card as the base of the instance
  $card = _relay_card_types_create_card( $message, $author, $published );

  //customize the card to make it a editorial
  $card->type = 'relay_editorial';

  //is this type in this list?
  if( variable_get( 'relay_twitter_push_enabled', FALSE ) && in_array( $card->type, variable_get( 'relay_twitter_push_enabled_types', array() ) ) ){

    //push this item to twitter
    _relay_card_types_push_to_twitter( $card, $status_id );

    //stores the status id so we see if we have this later
    $card->relay_tweet_status_id[$card->language][0]['value'] = $status_id;
  }

  //
  node_object_prepare($card);  //prefills many default values as needed  

  //saves the card to th database
  node_save( $card );

  //
  return true;
}

//parse the body of the node to create a tweet instance
function _relay_card_types_create_tweet( $message, $author, $published, $pushed=false  ){

  //creates a card as the base of the instance
  $card = _relay_card_types_create_card( $message, $author, $published );

  //customize the card to make it a tweet
  $card->type = 'relay_tweet';

  //store the youtube id if we need too
  $card->relay_tweet_status_id[$card->language][0]['value'] = $message->relay_tweet_status_id == null ? '' : $message->relay_tweet_status_id;
  $card->relay_tweet_status_id[$card->language][0]['format'] = null;

  //
  node_object_prepare($card);  //prefills many default values as needed  

  //is this type in this list?
  if( !$pushed && variable_get( 'relay_twitter_push_enabled', FALSE ) && in_array( $card->type, variable_get( 'relay_twitter_push_enabled_types', array() ) ) ){

    //push this item to twitter
    $body = _relay_card_types_push_to_twitter( $card, $status_id );

    //if the body ain't null use it to replace whats there
    if( $body != null )
      $card->body[$card->language][0]['value'] = $body;

    //stores the status id so we see if we have this later
    $card->relay_tweet_status_id[$card->language][0]['value'] = $status_id;
  }

  //saves the card to th database
  node_save( $card );

  //
  return true;
}

//parse the body of the node to create a video instance
function _relay_card_types_create_video( $message, $author, $published, $pushed=false  ){

  //creates a card as the base of the instance
  $card = _relay_card_types_create_card( $message, $author, $published );

  //customize the card to make it a video
  $card->type = 'relay_video';

  //store the youtube id if we need too
  $card->relay_youtube_code[$card->language][0]['value'] = $message->relay_youtube_code == null ? '' : $message->relay_youtube_code;
  $card->relay_youtube_code[$card->language][0]['format'] = null;

  //determine if we have an attachment that meets our qualifications
  if( !$pushed ){
    $file = _relay_card_types_process_attachments( 'video', $message->relay_attachments[$message->language] );
  }

  //the file attached was invalid, do not publish
  if( !$pushed && $file == null ){
    return FALSE;
  }

  //attach the file to the content type
  if( !$pushed )
    $card->relay_video_file[$card->language][0] = $file;

  //is this type in this list?
  if( !$pushed && variable_get( 'relay_twitter_push_enabled', FALSE ) && in_array( $card->type, variable_get( 'relay_twitter_push_enabled_types', array() ) ) ){

    //push this item to twitter
    _relay_card_types_push_to_twitter( $card, $status_id );

    //stores the status id so we see if we have this later
    $card->relay_tweet_status_id[$card->language][0]['value'] = $status_id;
  }

  //
  node_object_prepare($card);  //prefills many default values as needed  

  //saves the card to th database
  node_save( $card );

  //push the video clip to vimeo as well
  if( !$pushed && variable_get( 'relay_vimeo_push_enabled', FALSE ) && relay_card_types_verify_vimeo_library() ){

    //gets a reference to the vimeo instance
    $vimeo = new Vimeo( variable_get( 'relay_vimeo_application_id', ''), variable_get( 'relay_vimeo_application_secret', ''), variable_get( 'relay_vimeo_access_token', ''));

    //uplaod the video to vimeo
    $vimeo->upload( drupal_realpath( $file->uri ) );

  }

  //push the video clip to youtube as well
  if( !$pushed && variable_get( 'relay_youtube_push_enabled', FALSE ) && relay_card_types_verify_youtube_library() ){

  }

  //
  return true;
}

//parse the body of the node to create a live stream instance
function _relay_card_types_create_live_stream( $message, $author, $published ){

  //creates a card as the base of the instance
  $card = _relay_card_types_create_card( $message, $author, $published );

  //customize the card to make it a live stream
  $card->type = 'relay_live';

  //is this type in this list?
  if( variable_get( 'relay_twitter_push_enabled', FALSE ) && in_array( $card->type, variable_get( 'relay_twitter_push_enabled_types', array() ) ) ){

    //push this item to twitter
    _relay_card_types_push_to_twitter( $card, $status_id );

    //stores the status id so we see if we have this later
    $card->relay_tweet_status_id[$card->language][0]['value'] = $status_id;
  }

  //
  node_object_prepare($card);  //prefills many default values as needed  

  //saves the card to th database
  node_save( $card );

  //
  return true;
}

//
function _relay_card_types_push_to_twitter( $card, &$status_id ){

  //push the message to twitter as well
  if( variable_get( 'relay_twitter_push_enabled', FALSE ) && relay_card_types_verify_twitter_library() ){

    //create a twitter object
    $twitter = new Twitter( variable_get( 'relay_twitter_api_key', ''), variable_get( 'relay_twitter_api_secret_key', ''), variable_get( 'relay_twitter_access_token', ''), variable_get( 'relay_twitter_access_token_secret', '') );

    //try to send the tweet
    try {

      //creates a message with the tweet and a link to the site apppeneded to the end.  Also limits to 120 characters
      $message = substr( $card->body[$card->language][0]['value'], 0, 140 );

      //see if we have an image to attach
      //$media = url( drupal_get_path_alias('node/' . $card->nid), array('absolute' => TRUE) );
      $media = null;

      //send the card body as a tweet
      $tweet = $twitter->send( $message, $media ); // you can add $imagePath as second argument

      //the id should be enough to link to the tweet or embed it
      $body = '<blockquote class="twitter-tweet" lang="en">' . $tweet->text . '<a href="https://twitter.com/lNVENTlONS/statuses/' . $tweet->id . '">' . $tweet->created_at . '</a></blockquote><script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>';
      
      //set the status id as well
      $status_id = $tweet->id;

      //return back the tweet body
      return $body;

    //if it failed for some reason
    } catch (TwitterException $e) {

      //broadcast the error attempting to send this message
      watchdog( 'relay_card_types', t('Error: ' . $e->getMessage() ) );
    }

  } 
}



