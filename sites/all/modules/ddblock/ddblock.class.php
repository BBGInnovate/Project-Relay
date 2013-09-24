<?php
class ddblockConfigurationSettings {

  /**
   * @var array default configuration settings
   */
  protected $settings = array(
    'content_type'             => array('format' => '%s', 'value' => 'none'),
    'folder'                   => array('format' => '%s', 'value' => 'images/ddblock'),
    'ignore_files'             => array('format' => '%s', 'value' => ''),
    'input_type'               => array('format' => '%s', 'value' => 'images'),
    'nodes'                    => array('format' => '%s', 'value' => ''),
    'node_body_teaser'         => array('format' => '%s', 'value' => 'body'),
    'order'                    => array('format' => '%s', 'value' => 'asc'),
    'output'                   => array('format' => '%s', 'value' => 'view_content'),
    'widget'                   => array('format' => '%s', 'value' => 'cycle'),
  );

  public function __construct (Array $settings) {
    foreach ($settings as $key => $value) {
      $this->__set($key, $value);
    }
  }

  /**
   * Use overload functions to get and set $settings
   *
   * Keys passed to the set function should be keys that already
   * exist in the settings array.
   */
  public function __set($key, $value) {
    if (!array_key_exists($key, $this->settings)) {
      return;
    }
    $this->settings[$key]['value'] = sprintf($this->settings[$key]['format'], $value);
  }

  /**
   * Use overload functions to get and set $settings
   */
  public function __get($key) {
    if (!array_key_exists($key, $this->settings)) {
      return null;
    }
    return $this->settings[$key]['value'];
  }

  /**
   * Alternate function to __get
   */
  public function get($key, $default) {
    return ($this->__get($key) !== NULL) ? $this->__get($key) : $default;
  }

  public function settings() {
    $settings = array();
    foreach ($this->settings as $key => $value) {
      $settings[$key] = $value['value'];
    }
    return $settings;
  }
}

class ddblockCycleConfigurationSettings {

  /**
   * @var array default configuration settings
   */
  protected $settings = array(
    'advanced'                 => array('format' => '%d', 'value' => 1),
    'container_advanced'       => array('format' => '%s', 'value' => 'div.slide'),
    'container_basic'          => array('format' => '%s', 'value' => 'div.slide'),
    'custom_jquery'            => array('format' => '%s', 'value' => ''),
    'fx'                       => array('format' => '%s', 'value' => 'fade'),
    'easing_out'               => array('format' => '%s', 'value' => 'linear'),
    'easing_in'                => array('format' => '%s', 'value' => 'linear'),
    'height'                   => array('format' => '%d', 'value' => 195),
    'image_height'             => array('format' => '%d', 'value' => 183),
    'image_width'              => array('format' => '%d', 'value' => 183),
    'image_style_toggle'       => array('format' => '%d', 'value' => 0),
    'image_style_slide'        => array('format' => '%s', 'value' => '<none>'),
    'image_style_pager_item'   => array('format' => '%s', 'value' => '<none>'),
    'max_image'                => array('format' => '%d', 'value' => 5),
    'next'                     => array('format' => '%d', 'value' => 0),
    'nr_of_pager_items'        => array('format' => '%d', 'value' => 4),
    'overflow'                 => array('format' => '%d', 'value' => 1),
    'pager'                    => array('format' => '%s', 'value' => 'none'),
    'pager_container'          => array('format' => '%s', 'value' => 'pager-item'),
    'pager_disable_click'      => array('format' => '%d', 'value' => 1),
    'pager_event'              => array('format' => '%s', 'value' => 'click'),
    'pager_fast'               => array('format' => '%d', 'value' => 1),
    'pager_height'             => array('format' => '%d', 'value' => 25),
    'pager_pause'              => array('format' => '%d', 'value' => 1),
    'pager_width'              => array('format' => '%d', 'value' => 195),
    'pager_position'           => array('format' => '%s', 'value' => 'top'),
    'pager_prev_next_loop'     => array('format' => '%d', 'value' => 1),
    'pager_scrollable_loop'    => array('format' => '%d', 'value' => 1),
    'pager_toggle'             => array('format' => '%d', 'value' => 1),
    'pager2'                   => array('format' => '%d', 'value' => 0),
    'pager2_event'             => array('format' => '%s', 'value' => 'click'),
    'pager2_slide_prev'        => array('format' => '%s', 'value' => ''),
    'pager2_slide_next'        => array('format' => '%s', 'value' => ''),
    'pager2_slide_hide'        => array('format' => '%d', 'value' => 0),
    'pause'                    => array('format' => '%d', 'value' => 1),
    'slide_text'               => array('format' => '%d', 'value' => 1),
    'slide_text_after_effect'  => array('format' => '%s', 'value' => 'fadeIn'),
    'slide_text_after_speed'   => array('format' => '%d', 'value' => 1000),
    'slide_text_after_easing'  => array('format' => '%s', 'value' => 'linear'),
    'slide_text_before_effect' => array('format' => '%s', 'value' => 'fadeOut'),
    'slide_text_before_speed'  => array('format' => '%d', 'value' => 250),
    'slide_text_before_easing' => array('format' => '%s', 'value' => 'linear'),
    'slide_text_container'     => array('format' => '%s', 'value' => 'div.slide-text'),
    'slide_text_jquery'        => array('format' => '%d', 'value' => 0),
    'slide_text_position'      => array('format' => '%s', 'value' => 'bottom'),
    'speed'                    => array('format' => '%d', 'value' => 500),
    'template'                 => array('format' => '%s', 'value' => 'none'),
    'template_size'            => array('format' => '%s', 'value' => 'default'),
    'timeout'                  => array('format' => '%d', 'value' => 5000),
    'width'                    => array('format' => '%d', 'value' => 195),
  );

  public function __construct (Array $settings) {
    foreach ($settings as $key => $value) {
      $this->__set($key, $value);
    }
  }

  /**
   * Use overload functions to get and set $settings
   *
   * Keys passed to the set function should be keys that already
   * exist in the settings array.
   */
  public function __set($key, $value) {
    if (!array_key_exists($key, $this->settings)) {
      return;
    }
    $this->settings[$key]['value'] = sprintf($this->settings[$key]['format'], $value);
  }

  /**
   * Use overload functions to get and set $settings
   */
  public function __get($key) {
    if (!array_key_exists($key, $this->settings)) {
      return null;
    }
    return $this->settings[$key]['value'];
  }

  /**
   * Alternate function to __get
   */
  public function get($key, $default) {
    return ($this->__get($key) !== NULL) ? $this->__get($key) : $default;
  }

  public function settings() {
    $settings = array();
    foreach ($this->settings as $key => $value) {
      $settings[$key] = $value['value'];
    }
    return $settings;
  }
}

class ddblockCycleMappingSettings {

  /**
   * @var array default configuration settings
   */
  protected $settings = array(
    0  => array('target' => 'node_id', 'source' => '', ),
    1  => array('target' => 'slide_image', 'source' => '', ),
    2  => array('target' => 'slide_title', 'source' => '', ),
    3  => array('target' => 'slide_text', 'source' => '', ),
    4  => array('target' => 'slide_read_more', 'source' => '', ),
    5  => array('target' => 'pager_image', 'source' => '', ),
    6  => array('target' => 'pager_text', 'source' => '', ),
    7  => array('target' => '', 'source' => '', ),
    8  => array('target' => '', 'source' => '', ),
    9  => array('target' => '', 'source' => '', ),
    10 => array('target' => '', 'source' => '', ),
    11 => array('target' => '', 'source' => '', ),
    12 => array('target' => '', 'source' => '', ),
    13 => array('target' => '', 'source' => '', ),
    14 => array('target' => '', 'source' => '', ),
    15 => array('target' => '', 'source' => '', ),
  );

  public function __construct (Array $settings) {
    foreach ($settings as $key => $value) {
      $this->__set($key, $value);
    }
  }

  /**
   * Use overload functions to get and set $settings
   *
   * Keys passed to the set function should be keys that already
   * exist in the settings array.
   */
  public function __set($key, $value) {
    if (!array_key_exists($key, $this->settings)) {
      return;
    }
    $this->settings[$key]['target'] = $value['target'];
    $this->settings[$key]['source'] = $value['source'];
  }

  /**
   * Use overload functions to get and set $settings
   */
  public function __get($key) {
    if (!array_key_exists($key, $this->settings)) {
      return null;
    }
    return $this->settings[$key];
  }

  /**
   * Alternate function to __get
   */
  public function get($key, $default) {
    return ($this->__get($key) !== NULL) ? $this->__get($key) : $default;
  }

  public function settings() {
    $settings = array();
    foreach ($this->settings as $key => $value) {
      $settings[$key]['target'] = $value['target'];
      $settings[$key]['source'] = $value['source'];
    }
    return $settings;
  }
}