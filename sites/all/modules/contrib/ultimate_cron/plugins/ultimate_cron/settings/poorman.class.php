<?php
/**
 * @file
 * Poormans cron settings for Ultimate Cron.
 */

/**
 * Poormans cron settings plugin class.
 */
class UltimateCronPoormanSettings extends UltimateCronSettings {
  /**
   * Default settings.
   */
  public function defaultSettings() {
    return array(
      'launcher' => '',
    );
  }

  /**
   * Settings form.
   */
  public function settingsForm(&$form, &$form_state, $job = NULL) {
    $elements = &$form['settings'][$this->type][$this->name];
    $values = &$form_state['values']['settings'][$this->type][$this->name];

    if (!$job) {
      $launchers = ultimate_cron_plugin_load_all('launcher');
      $options = array('' => '-- ' . t('Disabled') . ' --');
      foreach ($launchers as $name => $launcher) {
        if ($launcher->isValid() && method_exists($launcher, 'launchPoorman')) {
          $options[$name] = $launcher->title;
        }
      }
      $elements['launcher'] = array(
        '#type' => 'select',
        '#title' => t('Launcher'),
        '#options' => $options,
        '#default_value' => $values['launcher'],
        '#description' => t('Select the launcher to use for handling poormans cron.'),
        '#fallback' => TRUE,
      );
    }
    else {
      $elements['no_settings'] = array(
        '#markup' => '<p>' . t('This plugin has no settings.') . '</p>',
      );
    }
  }
}
