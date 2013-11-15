<?php
// $Id$
/**
 * @file
 */

/**
 * Displays the view activities page
 */
function constant_contact_view_activities()
{
	$cc = constant_contact_create_object();
	if(!is_object($cc)):
		return '';
	endif;
	
	$activities = array();
	$_activities = $cc->get_activities();
		
	if($_activities):
	foreach($_activities as $k => $v):
		$activities[$v['id']] = $v;
	endforeach;
	endif;
	
	$html = '';
	$html .= '<table cellspacing="3" cellpadding="3" border="0">';
	
	$html .= '<tr><th>Created</th><th>Type</th><th>Status</th><th>Errors</th><th>Transactions</th><th colspan="2">&nbsp;</th></tr>';
	
	foreach($activities as $id => $v):
		$html .= '<tr>';
		$html .= '<td>'.date('jS F Y \- H:i', $cc->convert_timestamp($v['InsertTime'])).'</td>';
		$html .= '<td>'.$v['Type'].'</td>';
		$html .= '<td>'.$v['Status'].'</td>';
		$html .= '<td>'.(isset($v['Errors']) ? $v['Errors'] : 'None').'</td>';
		$html .= '<td>'.(isset($v['TransactionCount']) ? $v['TransactionCount'] : 'None').'</td>';
		$html .= '<td>'. l(t('View'), "admin/config/services/constant_contact/activities/$id").'</td>';
		$html .= '</tr>';
	endforeach;
		
	$html .= '</table>';

	return $html;
}


/**
 * Displays the view activity page
 */
function constant_contact_view_activity($id)
{
	$cc = constant_contact_create_object();
	if(!is_object($cc)):
		return '';
	endif;
	
	$activity = $cc->get_activity($id);
	
	$html = '';
	$html .= '<table cellspacing="3" cellpadding="3" border="0">';
	
	$dateformat = 'jS F Y \- H:i:s';
	
	$html .= '<tr><td>ID</td><td>'.$activity['id'].'</td></tr>';
	$html .= '<tr><td>Type</td><td>'.$activity['Type'].'</td></tr>';
	$html .= '<tr><td>Status</td><td>'.$activity['Status'].'</td></tr>';
	$html .= '<tr><td>Errors</td><td>'.(isset($activity['Errors']) ? $activity['Errors'] : 'None').'</td></tr>';
	$html .= '<tr><td>Transactions</td><td>'.(isset($activity['TransactionCount']) ? $activity['TransactionCount'] : 'None').'</td></tr>';
	$html .= '<tr><td>Created</td><td>'.date($dateformat, $cc->convert_timestamp($activity['InsertTime'])).'</td></tr>';
	
	if(isset($activity['RunStartTime'], $activity['RunFinishTime'])):
		$html .= '<tr><td>Started</td><td>'.date($dateformat, $cc->convert_timestamp($activity['RunStartTime'])).'</td></tr>';
		$html .= '<tr><td>Finished</td><td>'.date($dateformat, $cc->convert_timestamp($activity['RunFinishTime'])).'</td></tr>';
		
		$runtime = $activity['RunFinishTime']-$activity['RunStartTime'];
		$html .= '<tr><td>Runtime</td><td>'.((!$runtime)?'Less than 1 second':"$runtime seconds").'</td></tr>';
	endif;
	
	if(isset($activity['FileName'])):
		$html .= '<tr><td colspan="2"><a href="'.url('admin/config/services/constant_contact/activities/download/').$activity['FileName'].'">Download File</a></td></tr>';
	endif;
		
	$html .= '</table>';

	return $html;
}

/**
 * Download an activity file
 */
function constant_contact_download_activity($filename)
{
	// create the object
	$cc = constant_contact_create_object();
	
	if(!is_object($cc)):
		return;
	endif;
	
	$filext = strtolower(substr($filename, -4));
	
	if($filext == '.csv'):
		header('Content-type: text/csv');
	elseif($filext == '.txt'):
		header('Content-type: text/plain');
	else:
		header('Content-type: application/octet-stream');
	endif;
		
	header('Content-Disposition: attachment; filename="'.$filename.'"');
	echo $cc->download_activity_file($filename);
	exit;
}