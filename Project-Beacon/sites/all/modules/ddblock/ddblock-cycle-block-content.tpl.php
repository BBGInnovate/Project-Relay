<?php

/*
 * @file
 * Default theme implementation to display a dynamic display blocks from a dynamic display block instance.
 *
 * Available variables:
 * - $origin: Original module of the block.
 * - $delta: Block number of the block.
 * - $pager: Pager type to add the dynamic display block.
 * - $pager_height: Pager container height.
 * - $pager_width: Pager container width.
 * - $imgcache_pager_item: Image cache preset name for the pager item.
 * - $content: themed content.
 *
 * notes: don't change the ID names, they are used by the jQuery script.
 */
 $settings = $ddblock_cycle_slider_settings;

?>

<!-- block content. -->
<div id="ddblock-<?php print $settings['delta']; ?>" class="ddblock-contents clearfix" style="visibility:hidden">

 <div class="ddblock-content clearfix">

  <?php if ($content): ?>

   <?php if (($settings['pager'] == 'number-pager')): ?>
    <!-- number pager. -->
    <div id="ddblock-<?php print $settings['pager'] ."-". $settings['delta'] ?>" class="ddblock-<?php print $settings['pager'] ?> ddblock-pager clearfix" style="height: <?php print $settings['pager_height']; ?>px; width:<?php print $settings['pager_width']; ?>px;">
     <?php $item_counter=1; ?>
     <ul>
      <?php foreach ($content['slide_image'] as $item): ?>
       <li class="number-pager-item">
        <a href="#" class="pager-link" title="click to navigate to topic">
         <?php print $item_counter; ?>
        </a>
       </li>
       <?php $item_counter++;?>
      <?php endforeach; ?>
     </ul>
    </div>
   <?php endif; ?>

   <?php if (($settings['pager'] == 'image-pager')): ?>

    <!-- image pager. -->
    <ul id="ddblock-<?php print $settings['pager'] ."-". $settings['delta'] ?>" class="ddblock-<?php print $settings['pager'] ?> ddblock-pager clearfix" style="height: <?php print $settings['pager_height'] ?>px; width:<?php print $settings['pager_width'] ?>px;">
      <?php foreach ($content['pager_image'] as $image_file): ?>
       <li>
        <a href="#" title="click to navigate to topic"><?php print $image_file; ?></a>
       </li>
      <?php endforeach; ?>
    </ul>
   <?php endif; ?>

   <?php if ($settings['pager'] == 'prev-next-pager'): ?>
    <!-- prev next pager. -->
    <div id="ddblock-<?php print $settings['pager'] ."-". $settings['delta'] ?>" class="ddblock-<?php print $settings['pager'] ?> ddblock-pager clearfix" style="height: <?php print $settings['pager_height'] ?>px; width:<?php print $settings['pager_width'] ?>px;">
     <a id="prev" class="prev" href="#">Prev</a>
     <a id="next" class="next" href="#">Next</a>
    </div>
   <?php endif; ?>

   <?php if ($settings['output_type'] == 'images') : ?>
    <div class="ddblock-container clearfix">
     <div class="slider">
      <?php foreach ($content['slide_image'] as $image_file): ?>
       <div class="slide"><?php print $image_file; ?></div>
      <?php endforeach; ?>
     </div>
     <!-- prev/next pager on slide -->
     <?php if ($settings['pager2'] == 1): ?>
      <div class="pager-slide prev-container prev-container-<?php print $settings['pager_position'] ?>">
       <a class="prev" href="#"><?php print $settings['pager2_slide_prev']?></a>
      </div>
      <div class="pager-slide next-container next-container-<?php print $settings['pager_position'] ?>">
       <a class="next" href="#"><?php print $settings['pager2_slide_next'] ?></a>
      </div>
     <?php endif; ?>
    </div>
   <?php endif; ?>

   <?php if ($settings['output_type'] == 'content_array') : ?>
    <div class="ddblock-container">
     <?php foreach ($content as $item): ?>
      <?php print($item); ?>
     <?php endforeach; ?>
     <!-- prev/next pager on slide -->
     <?php if ($settings['pager2'] == 1): ?>
      <div class="pager-slide prev-container prev-container-<?php print $settings['pager_position'] ?>">
       <a class="prev" href="#"><?php print $settings['pager2_slide_prev']?></a>
      </div>
      <div class="pager-slide next-container next-container-<?php print $settings['pager_position'] ?>">
       <a class="next" href="#"><?php print $settings['pager2_slide_next'] ?></a>
      </div>
     <?php endif; ?>
    </div>
   <?php endif; ?>

   <?php if ($settings['output_type'] == 'view_content') : ?>
    <div class="ddblock-container">
     <?php print($content); ?>
    </div>
   <?php endif; ?>
  <?php endif; ?>
 </div>
</div>
