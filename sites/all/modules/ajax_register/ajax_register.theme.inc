<?php

/**
 * @file
 * Theming functions for AJAX REGISTER module.
 */

/**
 * Returns HTML for a wrapped Ajax Register form.
 */
function theme_ajax_register_wrapper($variables) {
  $form = $variables['form'];
  $html_id = $form['actions']['submit']['#ajax']['wrapper'];
  return '<div id="' . $html_id . '">' . $form['#children'] . '</div>';
}
