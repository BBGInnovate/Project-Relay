<?php

/**
 * @file
 * Views Slideshow Configurable Controls theme callbacks.
 */

function theme_vscc_control($vars) {
  $id = 'vscc_controls_' . $vars['element'] . '_' . $vars['vss_id'];
  $vars['classes'][] = 'vscc_controls_' . $vars['element'];
  $output = '<span id="' . $id . '" class="' . implode(' ', $vars['classes']) . '">';
  $output .= '<a href="#">';
  if ($vars['element'] == 'pause') {
    $output .= '<span class="vscc-pause">' . theme('vscc_element_' . $vars['skin'], $vars) . '</span>';
    $vars['element'] = 'resume';
    $output .= '<span class="vscc-resume vscc-disabled">' . theme('vscc_element_' . $vars['skin'], $vars) . '</span>';
  }
  else {
    $output .= theme('vscc_element_' . $vars['skin'], $vars);
  }
  $output .= '</a></span>';

  return $output;
}

function theme_vscc_element_text($vars) {
  return t($vars['element']);
}

function theme_vscc_element_white_icons($vars) {
  $vars['color'] = 'white';
  $image_vars = _vscc_element_icon($vars);
  return theme('image', $image_vars);
}

function theme_vscc_element_black_icons($vars) {
  $vars['color'] = 'black';
  $image_vars = _vscc_element_icon($vars);
  return theme('image', $image_vars);
}

function _vscc_element_icon($vars) {
  switch ($vars['element']) {
    case 'pause':
      $image = 'pause';
      break;
    case 'previous':
      $image = 'arrow_left';
      break;
    case 'resume':
    case 'next':
      $image = 'arrow_right';
      break;
    default: break;
  }

  return array(
    'path' => drupal_get_path('module', 'vscc') . '/images/' . $vars['color'] . '_' . $image . '.png',
    'alt' => t($vars['element']),
    'title' => t($vars['element']),
  );
}