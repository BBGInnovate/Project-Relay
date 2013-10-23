<?php

/**
 * @file
 * Theme template for a list of YouTube video feed.
 *
 * Available variables in the theme is
 * An array of $videos, where each video object has:
 *   $video->title
 *   $video->description
 *   $video->watchURL
 *   $video->thumbnailFull
 *   $video->thumbnailDefault
 *   $video->thumbnailMQ
 *   $video->thumbnailHQ
 *   $video->thumbnailStart
 *   $video->thumbnailMiddle
 *   $video->thumbnailEnd
 *   $video->length
 *   $video->viewCount
 *   $video->rating
 *   $video->commentsURL
 *   $video->commentsCount
 *   $video->responsesURL
 *   $video->relatedURL
 */
?>
<div class="youtube-pull-listing">

  <?php foreach ($videos as $video): ?>
    <div class="youtube-pull-item">
      <div class="thumbnail">
        <a href="<?php print $video->watchURL; ?>">
          <img src="<?php print $video->thumbnailDefault; ?>"/>
        </a>
      </div>
      <div class="title">
        <a href="<?php print $video->watchURL; ?>">
          <?php print $video->title; ?>
        </a>
      </div>
      <div class="view-count">
        <?php print format_plural($video->viewCount, '1 view', '@count views'); ?>
      </div>
    </div>
  <?php endforeach; ?>

</div>