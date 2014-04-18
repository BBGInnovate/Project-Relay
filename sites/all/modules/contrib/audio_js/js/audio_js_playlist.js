/**
 * @file
 *
 * Replaces all instances of the <audio> tag using audio.js.
 * Looks for an ordered list below the <audio> tag to use as the playlist.
 */

(function ($) {
  Drupal.behaviors.audio_js = {
    attach: function(context) {
    // Setup the player to autoplay the next track.
      var loop = Drupal.settings.audio_js.loop;
      var SWFpath = Drupal.settings.audio_js.swf;
      var a = audiojs.createAll({
        css: false,
        swfLocation: SWFpath,
        trackEnded: function() {
          if (loop) {
            var next = $('ol li.playing').next();
            if (!next.length) {
              next = $('ol li').first();
            }
            next.addClass('playing').siblings().removeClass('playing');
            audio.load($('a', next).attr('data-src'));
            audio.play();
          };
        }
      });
      // Load in the first track.
      var audio = a[0];
      first = $('ol a').attr('data-src');
      $('ol li').first().addClass('playing');
      audio.load(first);
      // Load in a track on click.
      $('ol li').click(function(e) {
        e.preventDefault();
        $(this).addClass('playing').siblings().removeClass('playing');
        audio.load($('a', this).attr('data-src'));
        audio.play();
      });
      // Keyboard shortcuts.
      $(document).keydown(function(e) {
        var unicode = e.charCode ? e.charCode : e.keyCode;
        // If right arrow is pressed.
        if (unicode == 39) {
          var next = $('li.playing').next();
          if (!next.length) {
            next = $('ol li').first();
          }
          next.click();
        // If back arrow is pressed.
        } else if (unicode == 37) {
          var prev = $('li.playing').prev();
          if (!prev.length) {
            prev = $('ol li').last();
          }
          prev.click();
        // If spacebar is pressed.
        } else if (unicode == 32) {
          audio.playPause();
        }
      })
    }
  };
})(jQuery);
