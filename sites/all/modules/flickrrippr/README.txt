Flickr Rippr

http://drupal.org/project/flickrrippr
=====================================


DESCRIPTION
------------
Flickr Rippr reads flickr.com for users latest public photos, and turns these into content (nodes) on your drupal website.

You need only publish to flickr.com, and they will automagically appear on your drupal website after each cron run. Join this up with the Views module and make photo galleries, block, and other awesomes.

Example available on author's blog: http://coffee.geek.nz/photos

requires the Flickr API module.

Features:
 * Multiple flickr accounts per drupal user
 * filter imported photos by one or more tag
 * Configurable size of jpegs
 * Option to save jpeg photo file locally on yoru sever, or leave on flickr.com
 * creates photos as image.module nodes (BETA, experimental feature).
 * syncs tags from flickr.com as terms in a drupal taxonomy vocab.
 * syncs comments from flickr, saved as drupal comments
 * Updates latest photos on hook_cron and/or manual update of individual nodes.



REQUIREMENTS
------------
Drupal 6.x
Flickr API module http://drupal.org/project/flickrapi
Job Queue Module http://drupal.org/project/job_queue

for Shadow Box integration, the Shadowbox module is needed. http://drupal.org/project/shadowbox


INSTALLING
----------
1. Copy the 'flickrrippr' folder to your sites/all/modules directory.

2. Go to Administer > Site building > Modules. Enable the module.
Read more about installing modules at http://drupal.org/node/70151


CONFIGURING AND USING
---------------------
1. Go to Administer > User management > Permissions. Under section 'flickrrippr module' set appropriate permissions.

2. Go to admin/settings/flickrapi. Type in your Flickr Api Key. For example '4aac5309645301718877x3c6ce426ars'. Click on SAVE button.

3. Go to admin/settings/flickrrippr. Configure jpegs sizes. 

4. Go to user/flickrippr. Add 1 or more flickr account.
Note: Your Flickr Screen Name/User name can be found at http://www.flickr.com/account. Under the section 'Your screen name'.

5. Publish photos + descriptions to flickr, and see these automagically appear on your Drupal site.

6. Nodes are updated by CRON run, or manually on the node's edit page. To run cron go to admin/reports/status. Click on 'run cron manually' link. If any configuration error are display under 'Status report' title you must fix them. Then run CRON again.


REPORTING ISSUE. REQUESTING SUPPORT. REQUESTING NEW FEATURE
-----------------------------------------------------------
1. Go to the module issue queue at http://drupal.org/project/issues/flickrrippr?status=All&amp;categories=All
2. Click on CREATE A NEW ISSUE link.
3. Fill the form.
4. To get a status report on your request go to http://drupal.org/project/issues/user


UPGRADING
---------
Read more at http://drupal.org/node/250790
