------------------------
NOTIFY 7.x MODULE README
------------------------

This is a simple notification module. It provides e-mail notifications to
members about updates and changes to the Drupal web site.

Send comments via the issues queue on drupal.org:
http://drupal.org/project/issues/notify

------------------------
REQUIREMENTS
------------------------

This module requires a supported version of Drupal and cron to be
running.

------------------------
INSTALLATION
------------------------

1. Extract the notify project directory into the directory where you
   keep contributed modules (e.g. sites/all/modules/).

2. Enable the notify module on the Modules list page.  The database
   tables will be created automagically for you at this point.

3. Run the update script if you're upgrading from 7.x-1.0-alpha1.

4. Modify permissions on the People >> Permissions page.

   To set the notification checkbox default on new user registration
   form, or let new users opt in for notifications during
   registration, you must grant the anonymous user the right to access
   notify.  To allow users to control their own notification settings
   (recommended) you must also grant authenticated users the right to
   access notify

5. Configure the other general notification settings.

   See the "Usage" section below for details.

Note that no after installing Notify. no users will be subscribed to
notificatons.  Before anyone is subscribed, no notifications will be
sent.

------------------------
USAGE
------------------------

The administrative interface is at: Administer >> Configuration >>
People >> Notification settings.

The Settings tab allow you to configure how the module shall work.

You can specify how often notifications are sent, the hour to send
them (if the frequency is one day or greater), the number of failed
sends after which notifications are disabled, and the maximum number
of notifications to send out per cron run.

When setting how often notifications are sent, note that e-mail
updates can only happen as frequently as the cron is set to run.

If you check "Include updated posts in notifications", any change to a
node or content will cause it to be included in the next notification.
Note that even minor changes, such as correcting a trivial typo or
setting or unsetting the "sticky" attribute for the node will flag it
as updated, so use this option with caution in order to avoid excess
notificatons.

If you check "Administrators shall be notified about unpublished
content", users belonging to roles with the "administer nodes" and
"administer comments" permissions granted will receive notifications
about unpublished content.  This is mainly to make the module useful
to manage moderation queues.

The checkbox under "Notification default for new users" is used as the
default value for the notification master switch on the new user
registration.  Note that this setting has no effect unless you grant
the anonymous user the right to access notify.

The final section under the Settings tab let you set up notification
by node type.  Having nothing checked defaults to sending
notifications about all node types.

The Users tab is to review and see per-user settings, to process the
notification queue, and to inspect the current status of the
notification queue.

The radio buttons below the heading "Process notification queue" has
the following meanings:

 - Update status: Update the status panel at the bottom of the page,
   but do not change the queue.

 - Send batch: Force sending a notification batch without waiting for
   the next cron run.  Note that if the number of notifications queue
   exceeds the maximum number of notifications to send out per cron
   run, only the maximum number is sent.  The rest will be queued for
   the next cron run ir the next manual send batch (whatever happens
   first),

 - Truncate queue: Truncate the queue of pending notifications without
   sending any.

If you enable node revisions (http://drupal.org/node/320614), the
notification e-mail will also mention the name of the last person to
edit the node.

To manage your own notification preferences, click on the
"Notification settings" on your "My account" page.

------------------------
AUTHOR / MAINTAINER
------------------------

Kjartan Mannes <kjartan@drop.org> is the original author.

Rob Barreca <rob@electronicinsight.com> was a previous maintainer.

Matt Chapman <matt@ninjitsuweb.com> is the current maintainer.

Ishmael Sanchez (http://ishmaelsanchez.com),
Ward Poelmans <wpoely86@gmail.com>,
John Oltman <john.oltman@sitebasin.com>,
Ajit Shinde (https://www.facebook.com/shinde.ajit), and 
Gisle Hannemyr <gisle@hannemyr.no> contributed to the Drupal 7 port.

------------------------
RELATED PROJECTS & ALTERNATIVES
------------------------

http://drupal.org/project/notify_by_views
http://drupal.org/project/subscriptions
http://drupal.org/project/notifications
