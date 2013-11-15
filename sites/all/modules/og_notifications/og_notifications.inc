<?php

/**
 * @file
 * Group subscriptions for Notifications and group field (node:gid) for Notifications.
 */

/**
 * Generic content subscription Thread subscription.
 */
class Og_Notifications_Subscription extends Notifications_Content_Subscription {

  /**
   * Set all the fields we can get from node.
   */
  public function set_node($node) {
    parent::set_node($node);
    $this->set_group($node);
    return $this;
  }

  /**
   * Set group.
   */
  public function set_group($node) {
    if (og_get_group_type('node', $node->type)) {
      $gid = $node->nid;
    }
    elseif (og_get_group_type('node', $node->type, 'group content')) {
      $gid = array_pop(array_pop(og_get_entity_groups('node', $node)));
    }
    $this->get_field('node:gid')->set_value($gid);
    return $this;
  }

  /**
   * Get group (group field).
   */
  public function get_group() {
    return $this->get_field('node:gid');
  }

  /**
   * Get name.
   */
  function get_name() {
    if (isset($this->name)) {
      return $this->name;
    }
    else {
      $group_name = $this->get_group()->get_name();
      if ($type = $this->get_field('node:type')) {
        return t('@type posts in  @group.', array('@type' => $type->get_name(), '@group' => $group_name));
      }
      else {
        return t('All posts in @group.', array('@group' => $group_name));
      }
    }
  }

}

/**
 * Drupal user
 */
class Og_Notifications_Field extends Notifications_Field_Autocomplete {

  public $type = 'node:gid';
  public $object_type = 'group';

  /**
   * Get title for field
   */
  function get_title() {
    return t('Group');
  }

  /**
   * Get proper name
   */
  function get_name() {
    $obj = $this->get_object();
    return ($obj->value) ? node_load($obj->value)->title : '';
  }

  /**
   * Get description
   */
  function get_description() {
    return t('Group');
  }

  /**
   * Get autocomplete path
   */
  function autocomplete_path() {
    return 'group_label/autocomplete';
  }

  /**
   * Parse value from autocomplete
   */
  function autocomplete_parse($string) {
    if ($gid = _og_notifications_get_gid_by_lable($string)) {
      return $gid;
    }
  }

  function format_name($format) {
    return messaging_user_format_name($this->value);
  }

  /**
   * Get value from node or from node type
   */
  public function object_value($object) {
    $node = node_load($object->get_value());
    if (og_get_group_type('node', $node->type)) {
      return $node->nid;
    }
    elseif (og_get_group_type('node', $node->type, 'group content')) {
      return array_pop(array_pop(og_get_entity_groups('node', $node)));
    }
  }
}

