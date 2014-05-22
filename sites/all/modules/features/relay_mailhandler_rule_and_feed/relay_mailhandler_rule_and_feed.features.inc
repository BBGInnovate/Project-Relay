<?php
/**
 * @file
 * relay_mailhandler_rule_and_feed.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function relay_mailhandler_rule_and_feed_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}
