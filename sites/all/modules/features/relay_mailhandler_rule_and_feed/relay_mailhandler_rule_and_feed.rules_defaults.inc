<?php
/**
 * @file
 * relay_mailhandler_rule_and_feed.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function relay_mailhandler_rule_and_feed_default_rules_configuration() {
  $items = array();
  $items['rules_poll_for_cards'] = entity_import('rules_config', '{ "rules_poll_for_cards" : {
      "LABEL" : "Poll for Cards",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Relay" ],
      "REQUIRES" : [ "relay_card_types" ],
      "ON" : { "relay_card_types_poll_elapsed" : [] },
      "DO" : [
        { "relay_card_types_pull_from_flickr" : [] },
        { "relay_card_types_pull_from_vimeo" : [] },
        { "relay_card_types_pull_from_youtube" : [] },
        { "relay_card_types_pull_from_sound_cloud" : [] },
        { "relay_card_types_pull_from_twitter" : [] }
      ]
    }
  }');
  return $items;
}
