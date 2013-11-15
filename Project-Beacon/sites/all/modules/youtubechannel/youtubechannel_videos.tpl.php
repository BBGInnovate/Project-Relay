<?php

/**
 * @file
 * Theme file to display youtubechannel.
 */

if ($vars['content']) :
?>
  <div id="youtubechannel-player" style="width: <?php print $vars['width']; ?>px; height: <?php print $vars['height']; ?>px;">
    <iframe id="youtubechannel-frame" title="Youtube Video Player" width="<?php print $vars['width'] ?>" height="<?php print $vars['height'] ?>" src="" frameborder="0" allowfullscreen></iframe>
  </div>

  <div id="youtubechannel-list" style="width: <?php print $vars['width']; ?>px; height: <?php print ($vars['height'] > 140) ? (140) : $vars['height']; ?>px;">
    <ul>
      <?php foreach ($vars['content'] as $key => $value) : ?>
      <li><a href="#<?php print $key; ?>"><?php print $value; ?></a></li>
      <?php endforeach; ?>
    </ul>
  </div>

<?php

else :
?>
  <h3><?php print t('Could not fetch videos from youtube channel.'); ?></h3>
<?php
endif;
?>
