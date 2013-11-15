
/**
 * @file media_soundcloud/js/media_soundcloud.js
 */

(function ($) {

Drupal.media_soundcloud = {};
Drupal.behaviors.media_soundcloud = {
  attach: function (context, settings) {
    // Check the browser to see if it supports html5 audio.
    var audio = document.createElement('audio');
    var html5 = audio.canPlayType ? true : false;

    // If it has audio, does it support the correct codecs?
    if (html5) {
      html5 = false;
      if (audio.canPlayType( 'audio/webm; codecs="mp3, vorbis"' )) {
        html5 = true;
      }
    }

    // Put a prompt in the audio wrappers to let users know they need flash
    if (!FlashDetect.installed && !html5){
      $('.media-soundcloud-preview-wrapper').each(Drupal.media_soundcloud.needFlash);
    }
  }
};

Drupal.media_soundcloud.needFlash = function () {
  var id = $(this).attr('id');
  var wrapper = $('.media-soundcloud-preview-wrapper');
  var hw = Drupal.settings.media_soundcloud[id].height / Drupal.settings.media_soundcloud[id].width;
  wrapper.html('<div class="js-fallback">' + Drupal.t('You need Flash to listen to this audio. <a href="@flash">Get Flash</a>', {'@flash':'http://get.adobe.com/flashplayer'}) + '</div>');
  wrapper.height(wrapper.width() * hw);
};

Drupal.media_soundcloud.insertEmbed = function (embed_id) {
  var audioWrapper = $('#' + embed_id + '.media-soundcloud-preview-wrapper');
  var settings = Drupal.settings.media_soundcloud[embed_id];

  // Calculate the ratio of the dimensions of the embed.
  settings.hw = settings.height / settings.width;

  // Replace the object embed with SoundCloud's iframe. This isn't done by the
  // theme function because SoundCloud doesn't have a no-JS or no-Flash fallback.
  var audio = $('<iframe class="soundcloud-player" type="text/html" frameborder="0"></iframe>');
  var src = settings.embed_url;

  // Allow other modules to modify the audio settings.
  settings.options.wmode = 'opaque';
  $(window).trigger('media_soundcloud_load', settings);

  // Merge SoundCloud options (such as autoplay) into the source URL.
  var query = $.param(settings.options);
  if (query) {
    src += '?' + query;
  }

  // Set up the iframe with its contents and add it to the page.
  audio
    .attr('id', settings.id)
    .attr('width', settings.width)
    .attr('src', src);
  audioWrapper.html(audio);

  // Bind a resize event to handle fluid layouts.
  $(window).bind('resize', Drupal.media_soundcloud.resizeEmbeds);

  // For some reason Chrome does not properly size the container around the
  // embed and it will just render the embed at full size unless we set this
  // timeout.
  if (!$('.lightbox-stack').length) {
    setTimeout(Drupal.media_soundcloud.resizeEmbeds, 1);
  }
};

Drupal.media_soundcloud.resizeEmbeds = function () {
  $('.media-soundcloud-preview-wrapper').each(Drupal.media_soundcloud.resizeEmbed);
};

Drupal.media_soundcloud.resizeEmbed = function () {
  var context = $(this).parent();
  var audio = $(this).children(':first-child');
  var hw = Drupal.settings.media_soundcloud[$(this).attr('id')].hw;
  // Change the height of the wrapper that was given a fixed height by the
  // SoundCloud theming function.
  $(this)
    .height(context.width() * hw)
    .width(context.width());

  // Change the attributes on the embed to match the new size.
  audio
    .height(context.width() * hw)
    .width(context.width());
};

})(jQuery);