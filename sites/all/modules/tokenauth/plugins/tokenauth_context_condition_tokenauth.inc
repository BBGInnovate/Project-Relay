<?php
/**
 * @file
 * Context condition plugin for Tokenauth module.
 */

class tokenauth_context_condition_tokenauth extends context_condition {
  function condition_values() {
    return array(
      1 => t('Did not use Token Authentication to log in'),
      2 => t('Used Token Authentication to log in'),
    );
  }

  function condition_form($context) {
    $form = parent::condition_form($context);
    $default = $this->fetch_from_context($context, 'values');
    $form['#type'] = 'radios';
    $form['#default_value'] = reset($default);
    return $form;
  }

  function condition_form_submit($values) {
    return array($values);
  }

  function execute($auth_mode) {
    if ($this->condition_used()) {
      // Avoid '0' looking like empty selection.
      $auth_mode += 1;
      foreach ($this->get_contexts($auth_mode) as $context) {
        $this->condition_met($context, $auth_mode);
      }
    }
  }
}
