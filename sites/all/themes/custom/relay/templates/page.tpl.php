<!--.page -->
<?php
// Get Pinned Node ID
$nid = $cs_pinned_nid;
$node = node_load($nid);

// Get hashtag
if ($node->relay_events_ref) {
$cs_tid=taxonomy_term_load($node->relay_events_ref['und'][0]['tid']);
$cs_items = field_get_items('taxonomy_term', $cs_tid, 'relay_hash_tag');
$cs_first_item = array_shift($cs_items);
$cs_rawhashtag = '#' . $cs_first_item['value'];
} else {
	$cs_rawhashtag = '';
}
?>

<div id="container" class="row cs_dark-grey">
  <!-- Header Section -->
  <div class="small-12 column">
    <div class="row">
      <div class="contain-to-grid fixed header"><nav class="top-bar cs_bg_white" data-topbar>
        <!-- Site logo + Name -->
        <ul class="title-area">
          <li class="name">
            <h1> <a href="<?php print $front_page; ?>"><img class="logo" src="/<?php print path_to_theme(); ?>/images/VOA-blue.png" alt="VOA logo" /> <?php print $site_name; ?> </h1>
          </li>
          <li class="toggle-topbar menu-icon"> <a href="#"></a> </li>
        </ul>
        <!-- Top Nav Section -->
        <section class="top-bar-section">
        <ul class="right">
          <li><a href="/about">About Relay</a></li>
          <li><a href="#"><i class="fa fa-twitter"></i> Follow Us</a></li>
          <li><a href="#"><i class="fa fa-facebook"></i> Become a Fan</a></li>
          <li><a href="/contact">Contact Us</a></li>
        </ul>
        </section> </nav>
<!-- Ticker Bar Section -->
          <div class="small-12 ticker">
              <p class="left"> <i class="fa fa-twitter"></i> Follow the Conversation with <?php print $cs_rawhashtag; ?> </p>
          </div>
      </div>
    </div>
    <!-- End Header Section -->

    <div class="small-12<?php if (!$is_front): ?> row<?php endif; ?>">

      <?php if (!empty($tabs)): ?>
        <?php print render($tabs); ?>
        <?php if (!empty($tabs2)): print render($tabs2); endif; ?>
      <?php endif; ?>

      <?php if ($action_links): ?>
        <ul class="action-links">
          <?php print render($action_links); ?>
        </ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>

      <?php if ($messages && $zurb_foundation_messages_modal): print $messages; endif; ?>
    </div>
  </div>
</div>
<!--/.page -->
