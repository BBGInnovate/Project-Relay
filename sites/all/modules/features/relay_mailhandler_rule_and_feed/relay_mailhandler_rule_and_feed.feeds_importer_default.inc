<?php
/**
 * @file
 * relay_mailhandler_rule_and_feed.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function relay_mailhandler_rule_and_feed_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'message_importer';
  $feeds_importer->config = array(
    'name' => 'Message Importer',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'MailhandlerFetcher',
      'config' => array(
        'filter' => 'MailhandlerFilters',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'MailhandlerParser',
      'config' => array(
        'available_commands' => 'status',
        'authenticate_plugin' => 'MailhandlerAuthenticateDefault',
        'extended_headers' => NULL,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'from-address',
            'target' => 'relay_from',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'from-name',
            'target' => 'relay_from_name',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'to-address',
            'target' => 'relay_to',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'subject',
            'target' => 'title',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'attachments',
            'target' => 'relay_attachments',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'body_text',
            'target' => 'body',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'full_html',
        'skip_hash_check' => 0,
        'bundle' => 'relay_msg_src',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '0',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['message_importer'] = $feeds_importer;

  return $export;
}
