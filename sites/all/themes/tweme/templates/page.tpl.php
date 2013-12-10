<?php

/**
 * @file
 * Custom theme implementation to display a single Drupal page.
 */

?>

<!-- Navbar -->
<div id="navbar" class="navbar navbar-medium navbar-inverse navbar-static-top">
	<div class="navbar-inner">
		<div class="container">
                        <?php if ($navbar_menu): ?>
			<nav class="nav-collapse collapse" role="navigation">
        <?php print $navbar_menu ?>
			<?php endif ?>
      <?php print $navbar_toggler ?>
			<?php print $navbar_brand ?>
      <?php print $navbar_search ?>
        </nav>
                    <div id="header-top">
                        <?php print render($page['header_top']); ?>
                    </div>
		</div>
	</div>
</div>

<?php if ($page['featured']): ?>
<!-- Featured -->
<div id="featured" class="container-wrapper hidden-phone">
  <div class="container">
    <?php print render($page['featured']) ?>
  </div>
</div>
<?php endif ?>

<?php if ($preface): ?>
<!-- Header -->
<?php 
$edit_class = '';
if((arg(0)=='node') && (is_numeric(arg(1)) && (arg(2)=='edit'))){
$edit_class = 'node-edit';
}
?>
<header id="header" class="container-wrapper <?php echo $edit_class; ?>">
  <div class="container">
    <?php print $preface ?>
  </div>
</header>
<?php endif ?>

<!-- Main -->
<div id="main">
  <div class="container">
    <?php print $messages ?>
    <div class="row row-toggle">
      <?php if ($has_sidebar_first): ?>
      <!-- Sidebar first -->
      <aside id="sidebar-first" class="sidebar span3 hidden-phone">
        <?php print render($page['sidebar_first']) ?>
        <?php print render($page['sidebar_first_affix']) ?>
      </aside>
      <?php endif ?>
      <!-- Content -->
      <section id="content" class="span<?php print $content_cols ?>">
        <?php print render($page['content']) ?>
      </section>
      <?php if ($has_sidebar_second): ?>
      <!-- Sidebar second -->
      <aside id="sidebar-second" class="sidebar span3 hidden-phone">
        <?php print render($page['sidebar_second']) ?>
        <?php print render($page['sidebar_second_affix']) ?>
      </aside>
      <?php endif ?>
    </div>
	</div>
</div>

<!-- Footer -->
<footer id="footer" class="container-wrapper">
	<div class="container">
    <div class="footer-links pull-right">
      <?php if ($feed_icons): ?><?php print $feed_icons ?><?php endif ?>
      <?php if ($secondary_menu): ?>
			<?php foreach ($secondary_menu as $item): ?>
			<?php print l($item['title'], $item['href']) ?>
			<?php endforeach ?>
      <a href="#"><?php print t('Back to top') ?> </a>
      <?php endif ?>
    </div>
    <?php print $copyright ?>
	</div>
</footer>
