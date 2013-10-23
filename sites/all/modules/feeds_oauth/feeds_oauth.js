(function ($) {
// START jQuery

Drupal.behaviors.feeds_oauth = {
  attach: function(context, settings) {
    // Automatically update callback URL with site id.
    $("input#edit-site-id", context).keyup(function() {
      var url = $("code.site-id em", context).html();
      $("code.site-id em", context).html(
        url.substring(0, url.lastIndexOf('/') + 1) + $("input#edit-site-id", context).val().trim()
      );
    });
  }
}

// END jQuery
})(jQuery);

if (!String.prototype.trim) {
  String.prototype.trim=function(){return this.replace(/^\s+|\s+$/g, '');};
}
