<?php
// $Id$
/**
 * @file
 */

/**
 * Displays the export page
 */
function constant_contact_export()
{
	$cc = constant_contact_create_object();
	if(!is_object($cc)):
		return '';
	endif;
	
	$form = array();
	
	$form['constant_contact']['export'] = array(
		'#type' => 'fieldset',
		'#tree' => true,
		'#title' => t('Export Subscribers'),
	);
	
	$options = array('CSV' => t('CSV'), 'TXT' => t('TXT'));
	$form['constant_contact']['export']['type'] = array(
		'#type' => 'radios',
		'#title' => t('File Format'),
		'#description' => t('Choose what format to use for the export'),
		'#size' => 60,
   		'#options' => $options,
    	'#default_value' =>  'CSV',
		'#required' => true,
	);
	
	$form['constant_contact']['export']['columns'] = array(
		'#type' => 'select',
		'#title' => t('Columns'),
		'#options' => $cc->get_export_file_columns(),
		'#multiple' => true,
		'#size' => 10,
		'#description' => t('You can select which columns to include in the export file'),
	);
		  
	$lists = constant_contact_get_lists($cc, 0);
	  
	$form['constant_contact']['export']['list'] = array(
		'#type' => 'select',
		'#title' => t('Contact list'),
		'#options' => $lists,
		'#size' => 1,
		'#description' => t('Select which contact list you want to export from'),
		'#required' => true,
	);
	
	$sort_by = array('DATE_DESC' => t('Date Subscribed'), 'EMAIL_ADDRESS' => t('Email Address'));
	$form['constant_contact']['export']['sort_by'] = array(
		'#type' => 'select',
		'#title' => t('Sort By'),
		'#description' => t('Choose how to sort the data'),
   		'#options' => $sort_by,
    	'#default_value' =>  'DATE_DESC',
		'#required' => true,
	);
	
	$form['#redirect'] = 'admin/settings/constant_contact/activities';
	$form['submit'] = array('#type' => 'submit', '#value' => t('Export'));
	return $form;
}

/**
 * Submit handler for the module export page
 */
function constant_contact_export_submit($form, &$form_state)
{
	$cc = constant_contact_create_object();
	if(!is_object($cc)):
		return;
	endif;
	
	$type = $form_state['values']['export']['type'];
	$columns = array_values($form_state['values']['export']['columns']);
	$list_id = $form_state['values']['export']['list'];
	$sort_by = $form_state['values']['export']['sort_by'];
	
	// check we have an object
	$cc = constant_contact_create_object();
	
	$status = false;
	$status = $cc->export_contacts($list_id, $type, $columns, $sort_by);
		
	if($status):
		drupal_set_message(t('An export activity has been created and the download will be available soon'));
	else:
		drupal_set_message(t('Your subscribers could not be exported: ' . $cc->last_error), 'error');
	endif;
}