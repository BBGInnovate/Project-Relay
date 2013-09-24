<?php
// $Id$
/**
 * @file
 */

/**
 * Define default settings for the module
 * These are here purely for convience
 * They can all be overridden on the settings page
 */

// method to use for the register page, can be either checkbox or lists
define('CC_REGISTER_PAGE_METHOD', 'none');

// determines how many blocks will be shown to the admin for configuration
define('CC_BLOCK_COUNT', 1);

// determines if we show the contact list selection in the form block
define('CC_BLOCK_SHOW_LIST_SELECTION', 1);

// determines if we should opt-in users by default (register page)
define('CC_DEFAULT_OPT_IN', 1);

// determines if we should synce unsubscribed users with constant contact
define('CC_SYNC_UNSUBSCRIBED_USERS', 0);

// the title of the signup checkbox box
define('CC_SIGNUP_TITLE', 'Subscribe to the Newsletter');

// the description of the signup checkbox box
define('CC_SIGNUP_DESCRIPTION', 'Select your areas of interest / would you like to receive the newsletter?');

// The URL for the Constant Contact 60-day trial
define('CC_TRIAL_URL', 'http://bit.ly/cctrial');

// The format for the list selection form element, checkbox or select
define('CC_LIST_SELECTION_FORMAT', 'select');

// default email format, HTML or Text
define('CC_SUBSCRIBE_FORMAT', 'HTML');

// Should be show a selection to the user to pick what format email they will receive
define('CC_SHOW_FORMAT_CHOICE', 0);

// how we should sort the contact lists, give a field name, SortOrder, Name, id
define('CC_CONTACT_LIST_SORT_ORDER', 'SortOrder');

// how long should we keep contact lists in the cache for, default is 1 hour
define('CC_CONTACT_LISTS_CACHE_EXPIRE', 3600);

?>