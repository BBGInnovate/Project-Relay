(function ($) {
  function youtubechannel_setvideo(href) {
    youtubeid = href.replace("#","");
    jQuery('#youtubechannel-frame').attr('src','http://www.youtube.com/embed/' + youtubeid);
  }

  Drupal.behaviors.youtubechannel = {
    attach: function (context, settings) {
      youtubechannel_setvideo(jQuery('#youtubechannel-list a:first').attr('href'));
      jQuery('#youtubechannel-list a').click(function(e) {
        youtubechannel_setvideo($(this).attr('href'));
        return false;
      });
    }
  }
}(jQuery));
