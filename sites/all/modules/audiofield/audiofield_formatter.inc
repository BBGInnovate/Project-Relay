<?php
// $Id: audiofield_formatter.inc,v 1.21.2.3 2011/02/20 10:13:26 tamerzg Exp $:
/**@file
 * Theme function for 'embedded' audio.
 */
function theme_audiofield_formatter_audiofield_embedded($variables) {
  global $user;
  $file = $variables['file'];

  if (!$file) {
    return '';
  }

  $audiofile = file_create_url($file->uri);
  $info = pathinfo($audiofile);
  $op = $info['extension'];
  $output = audiofield_get_player($audiofile, $op);

  //If user is file owner check for download permission and display download link
  if ($user->uid == $file->uid && user_access('download own audio files')) {
    $output .= '<div class="audio-download"><b>Download:</b>' . theme('file_link', array('file' => (object) $file)) . '</div>';
  }
  elseif (user_access('download all audio files')) {
    //If user has permission to download all audio files, then display download link
    $output .= '<div class="audio-download"><b>Download:</b>' . theme('file_link', array('file' => (object) $file)) . '</div>';
  }

  return $output;
}

/*
 * Theme function for 'embedded' audio.
 */
function theme_audiofield_formatter_audiofield_nodownload($variables) {
  global $user;
  $file = $variables['file'];

  if (!$file) {
    return '';
  }

  $audiofile = file_create_url($file->uri);
  $info = pathinfo($audiofile);
  $op = $info['extension'];
  $output = audiofield_get_player($audiofile, $op);

  return $output;
}
