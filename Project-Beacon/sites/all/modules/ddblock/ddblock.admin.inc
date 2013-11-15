<?php

/**
 * @file
 *  admin blocks of the ddblock module.
 *
 */

/**
 * Form with overview of all dynamic display blocks to manage and to add dynamic display blocks.
 */
function ddblock_block_add_form($form, &$form_state) {

  // get dynamic display  block.
  $rows = array();
  $blocks = ddblock_get_blocks(NULL);

  foreach ($blocks as $block) {
    $rows[] = array(
      'name' => check_plain($block->title),
      'edit' => l(t('Edit'), "admin/structure/ddblock/edit/$block->delta"),
      'delete' => l(t('Delete'), "admin/structure/ddblock/delete/$block->delta"),
      'block' => l(t('Configure block'), "admin/structure/block/manage/ddblock/$block->delta/configure"),
    );
  }
  if (empty($rows)) {
    $rows[] = array(array(
        'data' => t('No dynamic display blocks available.'),
        'colspan' => '4',
      ));
  }

  $header = array(t('Name'), array(
      'data' => t('Operation'),
      'colspan' => '3',
    ));
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'dynamic display block')));

  $form = array();
  $form['list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dynamic display blocks'),
    '#collapsible' => TRUE,
  );
  $form['list']['table'] = array(
    '#type' => 'item',
    '#prefix' => '<div>',
    '#markup' => $output,
    '#suffix' => '</div>',
  );

  // add dynamic display  block.
  $form['block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add dynamic display block.'),
  );

  $form['block']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#description' => t('A block with this same name will be created.'),
    '#default_value' => '',
    '#required' => TRUE,
  );

  $form['block']['op'] = array(
    '#type' => 'submit',
    '#value' => t('Add block'),
  );

  return $form;
}

/**
 * Validate "Add Block" form.
 */
function ddblock_block_add_form_validate($form, &$form_state) {
  $blocks = ddblock_get_blocks(NULL);
  $block_titles = array();
  foreach ($blocks as $block) {
    $block_titles[] = $block->title;
  }

  if (!empty($block_titles)) {
    // Check if name is unique
    if (in_array($form_state['values']['title'], $block_titles)) {
      form_set_error('', t('Dynamic display block %s already exists. Please use a different name.', array('%s' => $form_state['values']['title'])));
    }
  }
}
/**
 * Add dynamic display block to database from "Add Block" form.
 */
function ddblock_block_add_form_submit($form, &$form_state) {
  $id = db_insert('ddblock_block')
  ->fields(array(
    'title' => $form_state['values']['title'],
    'module' => 'ddblock',
  ))
  ->execute();

  drupal_set_message(t('Dynamic display block %s added.', array('%s' => $form_state['values']['title'])));
}

/**
 * Edit block form.
 */
function ddblock_block_edit_form($form, &$form_state, $delta) {
  $block = ddblock_get_blocks($delta);
  $form = array();

  $form['delta'] = array(
    '#type' => 'hidden',
    '#value' => $delta,
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#description' => t('The block name must be unique.'),
    '#default_value' => $block->title,
    '#required' => TRUE,
  );

  $form['op'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Validate edit block form.
 */
function ddblock_block_edit_form_validate($form, &$form_state) {
  $blocks = ddblock_get_blocks(NULL);
  $block_titles = array();
  foreach ($blocks as $block) {
    $block_titles[$block->delta] = $block->title;
  }

  // Remove current blockname to prevent false error.
  unset($block_titles[$form_state['values']['delta']]);

  if (!empty($block_titles)) {
    // Check if name is unique.
    if (in_array($form_state['values']['title'], $block_titles)) {
      form_set_error('', t('Dynamic display block %s already exists. Please use a different name.', array('%s' => $form_state['values']['title'])));
    }
  }
}

/**
 * Submit edit block form.
 */
function ddblock_block_edit_form_submit($form, &$form_state) {
  db_update('ddblock_block')
  ->fields(array(
    'title' => $form_state['values']['title'],
  ))
  ->condition('delta', $form_state['values']['delta'])
  ->execute();

  drupal_set_message(t('Dynamic display block block updated.'));
  $form_state['redirect'] = 'admin/structure/ddblock';
  return $form;
}

/**
 * Delete block form.
 */
function ddblock_block_confirm_delete_form($form, &$form_state, $delta) {
  $block = ddblock_get_blocks($delta);
  if (empty($block)) {
    drupal_set_message(t('The block with delta @delta was not found.', array('@delta' => $delta)), 'error');
    return array();
  }
  else {
    if ($block->enabled == 1) {

      //The question to ask the user.
      $question = t('Are you sure you want to delete the dynamic display block instance %title?', array('%title' => $block->title));
    }
    else {
      //The question to ask the user.
      $question = t('Are you sure you want to delete the dynamic display block %title?', array('%title' => $block->title));
    }
    // The page to go to if the user denies the action.
    $path = 'admin/structure/ddblock';

    // Additional text to display (defaults to "This action cannot be undone.").
    $description = t('This action cannot be undone.');

    // A caption for the button which confirms the action.
    $yes = t('Delete');

    // A caption for the link which denies the action.
    $no = t('Cancel');

    // set delta value to use in submit function.
    $form['delta'] = array(
      '#type' => 'value',
      '#value' => $delta,
    );

    // set original module value to use in submit function.
    $form['origin'] = array(
      '#type' => 'value',
      '#value' => $block->module,
    );

    // set the redirect path value to use in submit function.
    $form_state['redirect'] = $path;
    return confirm_form(
      $form,
      $question,
      $path,
      $description,
      $yes,
      $no
    );
  }
}

/**
 * Delete a dynamic display block or dynamic display block instance.
 */
function ddblock_block_confirm_delete_form_submit($form, &$form_state) {

  if (ddblock_block_confirm_delete($form_state['values']['delta'])) {
    if ($form_state['values']['origin'] == 'ddblock') {
      $succes_message = t('Dynamic display block successfully deleted!');
    }
    else {
      $succes_message = t('Dynamic display block instance successfully deleted!');
    }
    drupal_set_message($succes_message);
  }
  else {
    if ($form_state['values']['origin'] == 'ddblock') {
      $failure_message = t('There was a problem deleting the dynamic display block');
    }
    else {
      $failure_message = t('There was a problem deleting the dynamic display block instance');
    }
    drupal_set_message($failure_message);
  }
  $form_state['redirect'] = 'admin/structure/ddblock';
  return $form;
}

/**
 * Delete a dynamic display block or dynamic display block instance from the database.
 */
/*function ddblock_block_confirm_delete($delta) {
  $result = db_delete('ddblock_block')
  ->condition('delta', (int) $delta)
  ->execute();
  if (ctype_digit($delta)) {
    _block_rehash();
    // variable_del includes a clear cache.
    variable_del('ddblock_block_ddblock_' . $delta . '_cycle_settings');
    return TRUE;
  }
  else {
    return FALSE;
  }
}
*/
function ddblock_block_confirm_delete($delta) {
  _block_rehash();
  $result = db_delete('ddblock_block')
  ->condition('delta', (int) $delta)
  ->execute();

  $result = db_delete('block')
  ->condition('module', 'ddblock')
  ->condition('delta', $delta)
  ->execute();

  // variable_del includes a clear cache.
  variable_del('ddblock_block_ddblock_' . $delta . '_settings');
  variable_del('ddblock_block_ddblock_' . $delta . '_cycle_settings');
  variable_del('ddblock_block_ddblock_' . $delta . '_cycle_mapping_settings');

  return TRUE;
}

/**
 * Dynamic display block settings form for setting the content types to be used with the dynamic display block module.
 */
function ddblock_settings_form($form, &$form_state) {
  $form = array();
  // get a list of all available content types,  names parameter is used to get an associative array of content type names.
  // the key is the machine-readable name of the content type and the value the human-readable name of the content type.
  $content_types = node_type_get_names();

  $form['ddblock_node_type'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#description' => t('The content type(s) that can be used with the dynamic display block module.'),
    '#default_value' => variable_get('ddblock_node_type', array()),
    '#options' => $content_types,
    '#multiple' => TRUE,
    '#required' => FALSE,
  );

  // Fetch blocks directly from modules using block.module function.
  $blocks = _block_rehash();

  // Sort blocks how we want them.
  usort($blocks, 'ddblock_block_sort');

  // Turn $blocks into form options of available blocks.
  $options = array();
  foreach ($blocks as $block) {
    // Don't include ddblock module blocks in the list.
    if ($block['module'] != 'ddblock') {
      $options[$block['module'] . ':' . $block['delta'] . ':' . $block['info']] = $block['module'] . ' - ' . $block['info'];
    }
  }

  $form['ddblock_blocks'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Blocks'),
    '#description' => t('The block(s) that can be used with the dynamic display block module.'),
    '#default_value' => variable_get('ddblock_blocks', array()),
    '#options' => $options,
    '#multiple' => TRUE,
    '#required' => FALSE,
  );


  $form_state['redirect'] = 'admin/structure/ddblock/list';

  return system_settings_form($form);
}
