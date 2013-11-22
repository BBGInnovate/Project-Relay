(function ($) {

Drupal.behaviors.ajaxRegister = {
  attach: function (context){

    // Make modal window height scaled automatically.
    $('.ctools-modal-content, #modal-content', context).height('auto');

    // Position code lifted from http://www.quirksmode.org/viewport/compatibility.html
    if (self.pageYOffset) { // all except Explorer
      var wt = self.pageYOffset;
    }
    else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
      var wt = document.documentElement.scrollTop;
    }
    else if (document.body) { // all other Explorers
      var wt = document.body.scrollTop;
    }

    // Fix CTools bug: calculate correct 'top' value.
    var mdcTop = wt + ( $(window).height() / 2 ) - ($('#modalContent', context).outerHeight() / 2);
    $('#modalContent', context).css({top: mdcTop + 'px'});
  }
}

})(jQuery);
