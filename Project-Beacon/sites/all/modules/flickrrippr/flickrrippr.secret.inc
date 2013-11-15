<?php

function flickrrippr_secret_form() {
  $form = array();
  
  $form['jpeg_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Url to jpeg hosted on flickr.com'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );
  return $form;
}

function flickrrippr_secret_form_submit($form, $form_state) {

  $jpeg_url = $form_state['values']['jpeg_url'];
  $bits = preg_split('!(_|/|\.)!', $jpeg_url);
  $flickrphoto_id = $bits[7];
  $secret = $bits[8];

  $node = flickrrippr_makenode($flickrphoto_id, $secret);
  if ($node) {
    $image = l(flickrrippr_image($node, 'm'), 'node/'. $node->nid, array('html' => TRUE));
    drupal_set_message($image);
  }
  if (!$node) {
     form_set_error('', 'That didn\'t work');
     return;
  }
  
  
}