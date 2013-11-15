<?php
// $Id$

/**
 * @file
 */


/**
 * Displays the manage contact lists admin page
 */
function constant_contact_manage_lists()
{
	$cc = constant_contact_create_object();
	if(!is_object($cc)):
		return '';
	endif;
	
	$lists = constant_contact_get_lists($cc);
	
	$html = '';
	$html .= '<p>'. l(t('Add a new contact list'), "admin/config/services/constant_contact/lists/add").'</p>';
	
	$html .= '<table cellspacing="3" cellpadding="3" border="0">';
	
	$html .= '<tr><th>List Name</th><th colspan="2">&nbsp;</th></tr>';
	
	foreach($lists as $id => $name):
		$html .= '<tr>';
		$html .= '<td>'.$name.'</td>';
		$html .= '<td>'. l(t('Edit'), "admin/config/services/constant_contact/lists/edit/$id").'</td>';
		$html .= '<td>'. l(t('Delete'), "admin/config/services/constant_contact/lists/delete/$id").'</td>';
		$html .= '</tr>';
	endforeach;
		
	$html .= '</table>';

	return $html;
}


/**
 * Displays the manage contact lists page in the admin
 */
function constant_contact_edit_list($id)
{
	$node = array('id' => $id);
	return drupal_get_form('constant_contact_edit_list_form', $node);
}


/**
 * Displays the manage contact lists page in the admin
 */
function constant_contact_edit_list_form($form, $formstate)
{
	$cc = constant_contact_create_object();
	if(!is_object($cc)):
		return '';
	endif;
	
	$id = arg(6);
	$cclist = $cc->get_list($id);
	$form = array();
		
	// list name
	$form['list'] = array(
		'#type' => 'textfield',
		'#title' => t('List Name'),
		'#description' => t('Enter a name for the contact list'),
		'#default_value' => htmlentities($cclist['Name']),
		'#size' => 60,
	);
		
	// Sort Order
	$form['sort_order'] = array(
		'#type' => 'textfield',
		'#title' => t('Sort Order'),
		'#description' => t('Enter the position this list will appear at'),
		'#default_value' => $cclist['SortOrder'],
		'#size' => 5,
	);
		
	$form['#redirect'] = 'admin/config/services/constant_contact/lists';
		
	$form['id'] = array('#type' => 'value', '#value' => $id);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
	return $form;
}


/**
 * Submit handler for the add contact list admin page
 */
function constant_contact_edit_list_form_submit($form, &$form_state)
{
	$cc = constant_contact_create_object();
	if(!is_object($cc)):
		return;
	endif;
	
	$id = (isset($form_state['values']['id'])) ? $form_state['values']['id'] :  0;
	$list = (isset($form_state['values']['list'])) ? $form_state['values']['list'] : '';
	$sort_order = (isset($form_state['values']['sort_order'])) ? $form_state['values']['sort_order'] : 99;
	
	$status = $cc->update_list($id, $list, 'false', $sort_order);

    // refresh the lists, bypass cache
    constant_contact_get_lists($cc, 3, true);

	if($status):
		drupal_set_message(t("The contact list has been saved"));
	else:
		drupal_set_message(t("The contact list could not be saved: {$cc->last_error}"), 'error');
	endif;
}



/**
 * delete a contact list
 */
function constant_contact_delete_list($id)
{
	$node = array('id' => $id);
	$html = '<p>Please confirm you would like to delete this contact list?</p>';
	$html .= drupal_render(drupal_get_form('constant_contact_delete_list_form', $node));
	return $html;
}


/**
 * delete a contact list
 */
function constant_contact_delete_list_form($form, $formstate)
{
	$id = arg(6);
	
	$form = array();
	
	$form['#redirect'] = 'admin/config/services/constant_contact/lists';
	$form['id'] = array('#type' => 'value', '#value' => $id);
	
	$form['cancel'] = array(
		'#type' => 'submit',
		'#value' => t('Cancel'),
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Continue'),
	);
	
	return $form;
}


/**
 * Submit handler for the delete contact list admin page
 */
function constant_contact_delete_list_form_submit($form, &$form_state)
{
	if(isset($form_state['values']['op'])):
		if(trim($form_state['values']['op']) == 'Continue'):
			$id = (isset($form_state['values']['id'])) ? $form_state['values']['id'] : 0;
            
			$cc = constant_contact_create_object();
			if(!is_object($cc)):
				return;
			endif;
			
			$status = $cc->delete_list($id);

            // refresh the lists, bypass cache
            constant_contact_get_lists($cc, 3, true);

			if($status):
				drupal_set_message(t('The Contact list has been deleted'));
			else:
				drupal_set_message(t("Failed to delete contact list: {$cc->last_error}"), 'error');
			endif;
            
            drupal_goto('admin/config/services/constant_contact/lists');
        else:
            drupal_goto('admin/config/services/constant_contact/lists');
		endif;
	endif;
}



/**
 * Add a new contact list page in the admin function
 */
function constant_contact_add_list()
{
	return drupal_get_form('constant_contact_add_list_form');
}


/**
 * Add a new contact list page in the admin function
 */
function constant_contact_add_list_form()
{
	$form = array();
			
	// add account settings
	$form['list'] = array(
		'#type' => 'textfield',
		'#title' => t('List Name'),
		'#description' => t('Enter a name for the new contact list'),
		'#default_value' => '',
		'#size' => 60,
	);
	
	// Sort Order
	$form['sort_order'] = array(
		'#type' => 'textfield',
		'#title' => t('Sort Order'),
		'#description' => t('Enter the position this list will appear at'),
		'#default_value' => 99,
		'#size' => 5,
	);
	
	$form['#redirect'] = 'admin/config/services/constant_contact/lists';
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
	return $form;
}


/**
 * Submit handler for the add contact list admin page
 */
function constant_contact_add_list_form_submit($form, &$form_state)
{
	$cc = constant_contact_create_object();
	if(!is_object($cc)):
		return;
	endif;
	
	$list = (isset($form_state['values']['list'])) ? $form_state['values']['list'] :  '';
	$sort_order = (isset($form_state['values']['sort_order'])) ? $form_state['values']['sort_order'] : 99;
	
	$status = $cc->create_list($list, 'false', $sort_order);
    
    // refresh the lists, bypass cache
    constant_contact_get_lists($cc, 3, true);

	if($status):
		drupal_set_message(t('A new contact list has been created'));
	else:
		drupal_set_message(t("Failed to create new contact list: {$cc->last_error}"), 'error');
	endif;
}

?>