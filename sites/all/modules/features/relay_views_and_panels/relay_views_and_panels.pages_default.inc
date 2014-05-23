<?php
/**
 * @file
 * relay_views_and_panels.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function relay_views_and_panels_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'Event';
  $page->task = 'page';
  $page->admin_title = 'Event';
  $page->admin_description = '';
  $page->path = 'event';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_Event_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'Event';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'foundation_1col';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '69e11412-2f40-44e9-abd0-c148950de30f';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-debc06c2-d67a-4b39-babe-9e9e9968ab8e';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = 'event_carousel';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 1,
      'link_to_view' => 0,
      'args' => '%0',
      'url' => '',
      'display' => 'page',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'show-for-medium-up',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'debc06c2-d67a-4b39-babe-9e9e9968ab8e';
    $display->content['new-debc06c2-d67a-4b39-babe-9e9e9968ab8e'] = $pane;
    $display->panels['middle'][0] = 'new-debc06c2-d67a-4b39-babe-9e9e9968ab8e';
    $pane = new stdClass();
    $pane->pid = 'new-16a20cdb-5ee3-4e61-bfb3-f3417793481a';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = 'Event';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '10',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 1,
      'link_to_view' => 0,
      'args' => '%0',
      'url' => '',
      'display' => 'page',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'hide-for-medium-up',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '16a20cdb-5ee3-4e61-bfb3-f3417793481a';
    $display->content['new-16a20cdb-5ee3-4e61-bfb3-f3417793481a'] = $pane;
    $display->panels['middle'][1] = 'new-16a20cdb-5ee3-4e61-bfb3-f3417793481a';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['Event'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'front_page_panel';
  $page->task = 'page';
  $page->admin_title = 'Front Page Panel';
  $page->admin_description = '';
  $page->path = 'front_page_panel';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_front_page_panel_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'front_page_panel';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'foundation_1col';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'c98c85e8-37eb-4f47-8df4-8e2c39d22abb';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-9f9cf3b2-f6d3-46d0-ae5c-8f527fdfd6b3';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = 'sticky_card';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '1',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'page',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '9f9cf3b2-f6d3-46d0-ae5c-8f527fdfd6b3';
    $display->content['new-9f9cf3b2-f6d3-46d0-ae5c-8f527fdfd6b3'] = $pane;
    $display->panels['middle'][0] = 'new-9f9cf3b2-f6d3-46d0-ae5c-8f527fdfd6b3';
    $pane = new stdClass();
    $pane->pid = 'new-db9e5cee-b240-4b83-9d99-1f47947c0090';
    $pane->panel = 'middle';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Past Events',
      'title' => '',
      'body' => '<div class="cs_pastevents_panel"><p><a href="#"><i class="fa fa-folder"></i> Past Events</a></p></div>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'card_pastevents_row',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'db9e5cee-b240-4b83-9d99-1f47947c0090';
    $display->content['new-db9e5cee-b240-4b83-9d99-1f47947c0090'] = $pane;
    $display->panels['middle'][1] = 'new-db9e5cee-b240-4b83-9d99-1f47947c0090';
    $pane = new stdClass();
    $pane->pid = 'new-0cca03ff-6d68-4904-9ab6-fe45a81c8569';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = 'events';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '10',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'page',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '0cca03ff-6d68-4904-9ab6-fe45a81c8569';
    $display->content['new-0cca03ff-6d68-4904-9ab6-fe45a81c8569'] = $pane;
    $display->panels['middle'][2] = 'new-0cca03ff-6d68-4904-9ab6-fe45a81c8569';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-9f9cf3b2-f6d3-46d0-ae5c-8f527fdfd6b3';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['front_page_panel'] = $page;

  return $pages;

}
