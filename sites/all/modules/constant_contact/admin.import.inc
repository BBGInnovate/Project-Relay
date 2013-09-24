<?php
// $Id$
/**
 * @file
 */


/**
 * Displays the import page
 */
function constant_contact_import()
{
	$cc = constant_contact_create_object();
	if(!is_object($cc)):
		return '';
	endif;
	
	$form = array();
	$form['#attributes'] = array('enctype' => "multipart/form-data");
  
	// upload
	$form['constant_contact']['import'] = array(
		'#type' => 'fieldset',
		'#title' => t('Import Subscribers'),
	);
	
	$form['constant_contact']['import']['file'] = array(
		'#type' => 'file',
		'#title' => t('CSV file'),
		'#description' => t('Upload a CSV or TXT file containing your subscribers, see <a href="@fileformat" target="_blank">this page</a> for help with formatting the file', 
		array(
	  		'@fileformat' => 'http://constantcontact.custhelp.com/cgi-bin/constantcontact.cfg/php/enduser/std_adp.php?p_faqid=2523',
	  )),
		'#size' => 60,
	);
		  
	$lists = constant_contact_get_lists($cc);
	  
	$form['constant_contact']['import']['lists'] = array(
		'#type' => 'select',
		'#title' => t('Contact lists'),
		'#options' => $lists,
		'#multiple' => true,
		'#size' => 10,
		'#description' => t('Select which contact lists you want to subscribe these users to, you must select at least one list'),
		'#required' => true,
	);
	
	$form['#redirect'] = 'admin/config/services/constant_contact/activities';
	$form['submit'] = array('#type' => 'submit', '#value' => t('Import'));
	return $form;
}

/**
 * Submit handler for the module import page
 */
function constant_contact_import_submit($form, &$form_state)
{
	$cc = constant_contact_create_object();
	if(!is_object($cc)):
		return;
	endif;
	
	$status = false;
	$lists = $form_state['values']['lists'];
	
	$status = false;
	if(isset($_FILES['files']['tmp_name']['file']) && is_uploaded_file($_FILES['files']['tmp_name']['file'])):
		$status = $cc->create_contacts($_FILES['files']['tmp_name']['file'], $lists);
	else:
		drupal_set_message(t('The uploaded file is invalid please try again'), 'error');
		return;
	endif;
		
	if($status):
		drupal_set_message(t('An import activity has been created and will be completed soon'));
	else:
		drupal_set_message(t('Your subscribers could not be imported: ' . $cc->last_error), 'error');
	endif;
}
