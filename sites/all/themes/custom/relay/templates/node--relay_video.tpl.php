<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $display_submitted: whether submission information should be displayed.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>

<?php
if (drupal_is_front_page()) {
    $cs_title = 'Live Now';
    $nid = 2;
    $node = node_load($nid);
    $result = field_view_field('node', $node, 'relay_events_ref', array('default'));
    $cs_eventurl =  '/event/' . $result['#object']->relay_events_ref['und'][0]['taxonomy_term']->tid;
} else {
    $nid = 2;
    $node = node_load($nid);
    $result = field_view_field('node', $node, 'relay_events_ref', array('default'));
    $cs_title =  $result['#object']->relay_events_ref['und'][0]['taxonomy_term']->name;
    $cs_eventurl =  $node_url;
}
?>

<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

    <section>
        <div class="small-12 column cs_bg_blue card_top_row"> <span class="left spotlight"><i class="fa fa-bolt"></i> <a href="<?php print $cs_eventurl; ?>" class="cs_white"><?php print $cs_title; ?></a></span>
    </section>

    <section class="cs_main relay_video">
      <div class="column" style="padding-left: 0;padding-right: 0;">
        <div class="flex-video widescreen">
        <?php
        // We hide the comments and links now so that we can render them later.
        hide($content['title']);
        hide($content['relay_pin_card']);
        hide($content['relay_authors']);
        hide($content['relay_events_ref']);
        hide($content['relay_addthis']);
        hide($content['relay_tweet_status_id']);
        hide($content['relay_video_file']);
        hide($content['relay_youtube_code']);
        hide($content['comments']);
        hide($content['links']);
        hide($content['field_tags']);
        print render($content);
        ?>
        </div>
      </div>
    </section>

    <section class="footer-content">

        <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>

        <div class="card_social light">
		  <span class="left">
			  <a href="#"><i class="fa fa-facebook-square"></i></a>
			  <a href="#"><i class="fa fa-twitter"></i></a>
			  <a href="#"><i class="fa fa-google-plus-square"></i></a>
		  </span>
        </div>
    </section>
</article>
