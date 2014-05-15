<?php

/**
 * @file
 * Views Slideshow Configurable Controls HTML template.
 */
?>
<div id="vscc_controls_<?php print $variables['vss_id']; ?>" class="<?php print $classes; ?>">
  <?php print $rendered_control_previous; ?>
  <?php if (isset($rendered_control_pause)) {
    print $rendered_control_pause;
  } ?>
  <?php print $rendered_control_next; ?>
</div>