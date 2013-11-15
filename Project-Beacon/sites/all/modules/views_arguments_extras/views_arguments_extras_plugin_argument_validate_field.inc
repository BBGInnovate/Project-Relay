<?php
/**
 * @file
 * Contains the php code argument validator plugin.
 */

/**
 * Provide PHP code to validate whether or not an argument is ok.
 *
 * @ingroup views_argument_validate_plugins
 */
class views_plugin_argument_validate_field_extractor extends views_plugin_argument_validate {
  function option_definition() {
    $options = parent::option_definition();
    $options['entity_type'] = array('default' => '');
    $options['field'] = array('default' => '');
    $options['settings'] = array('default' => array());

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $entity_infos = entity_get_info();
    foreach($entity_infos as $key => $info) {
      $entity_options[$key] = $info['label'];
    }
    $form['entity_type'] = array(
      '#title' => 'Entity Type',
      '#type' => 'select',
      '#options' => $entity_options,
      '#default_value' => $this->options['entity_type'],
    );
    module_load_include("inc", "views_arguments_extras", "views_arguments_extras.field_plugins");
    $options = views_arguments_extras_get_plugin_options();

    $form['field'] = array(
      '#title' => 'Field',
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $this->options['field'],
      '#ajax' => array(
        'callback' => 'views_plugin_argument_validator_field_field_callback',
        'wrapper' => 'field-settings-wrapper',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    );
    $form['settings'] = array(
      '#title' => "Settings",
      '#type' => 'fieldset',
      '#prefix' => '<div class="field-settings-wrapper">',
      '#suffix' => '</div>',
    );
    if ($this->options['field']) {
      $plugins = views_plugin_argument_default_field();
      list($p_id, $field) = explode("::", $this->options['field']);
      $plugin = $plugins[$p_id];
      $form['settings']['#title'] = "Settings for {$plugin['name']}";
      if ($form_fun = ctools_plugin_get_function($plugin, "form callback")) {
        $plugin_form = $form_fun();
        foreach ($plugin_form as $id => $form_element) {
          $form['settings'][$id] = $form_element;
          $form['settings'][$id]['#default_value'] = $this->options['settings'][$id];
        }
      }
    }
  }

  /**
   * We are going to take the current argument, find the enitity object to which it relates
   * and then change the argument to reflect a value from one if its fields
   */
  function validate_argument(&$argument) {
    // set up variables to make it easier to reference during the argument.
    // TODO parse arguement on , and allow for multiple values
    $view = &$this->view;
    $handler = &$this->argument;
    $id = $handler->argument;
    if ($this->options['field']) {
      global $language;
      list($plugin_id, $field_name) = explode("::", $this->options['field']);
      if(($this->options['entity_type'] == 'entity_boxes') && !is_numeric($id)) {
        $entity = array_pop(entity_boxes_load_delta($id));
      }
      else {
        $entity = array_pop(entity_load($this->options['entity_type'], array($id)));
      }
      $lang = isset($entity->{$field_name}[$language->language]) ? $language->language : LANGUAGE_NONE;
      $field = isset($entity->{$field_name}[$lang]) ? $entity->{$field_name}[$lang] : array();
      module_load_include("inc", "views_arguments_extras", "views_arguments_extras.field_plugins");
      module_load_include("inc", "views_arguments_extras", "views_plugin_argument_default_field");
      $plugin = views_plugin_argument_default_field($plugin_id);
      if ($arg_fun = ctools_plugin_get_function($plugin, "argument callback")) {
        $return = $arg_fun($field, $this->options['settings'], $entity, $this);
        $handler->argument = $return;
        return TRUE;
      }


    }

    return FALSE;
  }
}

