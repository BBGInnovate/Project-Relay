<?php

/**
 * @file media_soundcloud/includes/themes/media-soundcloud-audio.tpl.php
 *
 * Template file for theme('media_soundcloud_audio').
 *
 * Variables available:
 *  $uri - The uri to the SoundCloud audio, such as soundcloud://u/[user-name]/a/[song-name].
 *  $user_name - The unique identifier of the SoundCloud user.
 *  $audio_name - The unique identifier of the SoundCloud audio song.
 *  $width - The width to render.
 *  $autoplay - If TRUE, then start the player automatically when displaying.
 *
 * Note that we set the width of the outer wrapper manually so that
 * the JS will respect that when resizing later.
 */
?>
<div class="media-soundcloud-outer-wrapper" id="media-soundcloud-<?php print $id; ?>">
  <div class="media-soundcloud-preview-wrapper" id="<?php print $wrapper_id; ?>">
    <?php print $output; ?>
  </div>
</div>
