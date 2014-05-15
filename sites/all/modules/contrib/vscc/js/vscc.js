(function ($) {
	
  /**
   * VSCC Controls
   */

  // Add views slieshow api calls for views slideshow text controls.
  Drupal.behaviors.vscc = {
    attach: function (context) {

      // Process previous link
      $('.vscc_controls_previous:not(.vscc-previous-processed)', context).addClass('vscc-previous-processed').each(function() {
        var uniqueID = $(this).attr('id').replace('vscc_controls_previous_', '');
        $(this).click(function() {
          Drupal.viewsSlideshow.action({ "action": 'previousSlide', "slideshowID": uniqueID });
          return false;
        });
      });

      // Process next link
      $('.vscc_controls_next:not(.vscc-next-processed)', context).addClass('vscc-next-processed').each(function() {
        var uniqueID = $(this).attr('id').replace('vscc_controls_next_', '');
        $(this).click(function() {
          Drupal.viewsSlideshow.action({ "action": 'nextSlide', "slideshowID": uniqueID });
          return false;
        });
      });

      // Process pause link
      $('.vscc_controls_pause:not(.vscc-pause-processed)', context).addClass('vscc-pause-processed').each(function() {
        var uniqueID = $(this).attr('id').replace('vscc_controls_pause_', '');
        $(this).click(function() {
          if (Drupal.settings.viewsSlideshow[uniqueID].paused) {
            Drupal.viewsSlideshow.action({ "action": 'play', "slideshowID": uniqueID, "force": true });
          }
          else {
            Drupal.viewsSlideshow.action({ "action": 'pause', "slideshowID": uniqueID, "force": true });
          }
          return false;
        });
      });
    }
  };

  Drupal.vsccControls = Drupal.vsccControls || {};

  /**
   * Implement the pause hook for configurable controls.
   */
  Drupal.vsccControls.pause = function (options) {
    $('#vscc_controls_pause_' + options.slideshowID + ' span.vscc-pause').hide();
    $('#vscc_controls_pause_' + options.slideshowID + ' span.vscc-resume').show();
  };

  /**
   * Implement the play hook for configurable controls.
   */
  Drupal.vsccControls.play = function (options) {
    $('#vscc_controls_pause_' + options.slideshowID + ' span.vscc-resume').hide();
    $('#vscc_controls_pause_' + options.slideshowID + ' span.vscc-pause').show();
  };
})(jQuery);