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

// Get event name
$result = field_view_field('node', $node, 'relay_events_ref', array('default'));
if (drupal_is_front_page()) {
    $cs_eventurl =  '/event/' . $result['#object']->relay_events_ref['und'][0]['taxonomy_term']->tid;
    $cs_title = 'Live Now';
} else {
    $cs_eventurl =  $node_url;
    $cs_title =  $result['#object']->relay_events_ref['und'][0]['taxonomy_term']->name;
}

// Setup social sharing links
Global $base_url;
$facebookShare =  'http://www.facebook.com/sharer.php?u=' . $base_url . '&t=' . $cs_title;
$twitterShare =  'http://twitter.com/intent/tweet?source=sharethiscom&text=' . $cs_title . '&url=' . $base_url;
$googleShare =  'https://plus.google.com/share?url=' . $base_url;

?>


<div class="small-12 column cs_bg_blue card_top_row"> <span class="left spotlight"><i class="fa fa-bolt"></i> <?php print $cs_title; ?></span></div>
<div class="card_content">
    <?php
    //print render($content['FIELDNAME']);
    //print render($content);
    //hide($content['title']);
    //hide($content['body']);
    hide($content['relay_to']);
    hide($content['relay_from']);
    hide($content['relay_from_name']);
    hide($content['relay_attachments']);
    hide($content['comments']);
    hide($content['links']);
    hide($content['field_tags']);
    print render($content);
    ?>
</div>
<div class="small-12 column card_time_row"><span class="left"><?php print $cs_rawhashtag ?></span><span class="
timeago right
thin"><?php echo format_interval(time()-$node->created),' ago'; ?></span> </div>
<div class="small-12 column card_latest_row cs_bg_white dark">
    <p><a href="<?php print $node_url; ?>"><?php print $title; ?></a></p>
    <div class="card_social dark"><span class="left"><a href="<?php print $facebookShare; ?>"><i class="fa fa-facebook-square"></i></a> <a href="<?php print $twitterShare; ?>"><i class="fa fa-twitter"></i></a> <a href="<?php print $googleShare; ?>"><i class="fa fa-google-plus-square"></i></a></span><span class="right"><a href="#"><i class="fa fa-comment"></i></a></span></div>
    <p class="card_follow_live"><a href="<?php print $cs_eventurl; ?>">Follow our live coverage <i class="fa fa-chevron-circle-right"></i></a></p>
</div>
