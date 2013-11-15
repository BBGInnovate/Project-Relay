<?php

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetSoundCloudHandler extends MediaInternetBaseHandler {
  public function parse($embedCode) {
    $patterns = array(
        '@soundcloud\.com/([0-9A-Za-z\@\&\$_-]+)/([0-9A-Za-z\@\&\$_-]+)/([0-9A-Za-z\@\&\$_-]+)@i',
        '@soundcloud\.com/([0-9A-Za-z\@\&\$_-]+)/([0-9A-Za-z\@\&\$_-]+)@i',
        '@soundcloud\.com/([0-9A-Za-z\@\&\$_-]+)@i',
    );
    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      if ( isset($matches[1]) && !isset($matches[2]) ) {
        return file_stream_wrapper_uri_normalize('soundcloud://u/' . $matches[1]);
      }
      if( isset($matches[2]) && !isset($matches[3])) {
          if($matches[1] == 'groups'){
            return file_stream_wrapper_uri_normalize('soundcloud://g/' . $matches[2] );
          }else{
            return file_stream_wrapper_uri_normalize('soundcloud://u/' . $matches[1] . '/a/' . $matches[2]);
          }        
      }
      if( isset($matches[3])){
          if($matches[2] == 'sets'){
            return file_stream_wrapper_uri_normalize('soundcloud://u/' . $matches[1] . '/s/' . $matches[3]);  
          }
      }
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function validate() {
    // @todo: add some kind of validation?
  }

  public function save() {
    $file = $this->getFileObject();
    file_save($file);
    return $file;
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    return file_uri_to_object($uri, TRUE);
  }

  /**
   * Returns information about the media. See http://video.search.yahoo.com/mrss.
   *
   * @return
   *   If ATOM+MRSS information is available, a SimpleXML element containing
   *   ATOM and MRSS elements, as per those respective specifications.
   *
   * @todo Would be better for the return value to be an array rather than a
   *   SimpleXML element, but media_retrieve_xml() needs to be upgraded to
   *   handle namespaces first.
   */
  /*public function getMRSS() {
    $uri = $this->parse($this->embedCode);
    $audio_id = arg(1, file_uri_target($uri));
    $rss_url = url('http://gdata.soundcloud.com/feeds/api/audios/' . $audio_id, array('query' => array('v' => '2')));
    // @todo Use media_retrieve_xml() once it's upgraded to include elements
    //   from all namespaces, not just the document default namespace.
    $entry = simplexml_load_file($rss_url);
    return $entry;
  }*/

  /**
   * Returns information about the media. See http://www.oembed.com/.
   *
   * @return
   *   If oEmbed information is available, an array containing 'title', 'type',
   *   'url', and other information as specified by the oEmbed standard.
   *   Otherwise, NULL.
   */
  public function getOEmbed() {
      //drupal_set_message("getOEmbed");
    $uri = $this->parse($this->embedCode);
    $external_url = drupal_realpath($uri);
    $oembed_url = url('http://soundcloud.com/oembed', array('query' => array('url' => $external_url, 'format' => 'json')));
    $response = drupal_http_request($oembed_url);
    //drupal_set_message(print_r($response,true)); 
    if (!isset($response->error)) {
      return drupal_json_decode($response->data);
    }
  }
}
