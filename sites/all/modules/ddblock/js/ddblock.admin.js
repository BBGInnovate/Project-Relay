(function ($) {
/*
 *  @file
 *  Javascript functionality for the Dynamic display block module admin page
 */

/*
 * Show/hide advanced settings sections on the ddblock instance settings page.
 * don't change
 */
Drupal.behaviors.ddblockShowHideAdvancedOptions = {
  attach: function(context, settings) {
    // Show/hide slide advanced options depending on the checkbox.
    $('#edit-advanced:not(.ddblock-show-hide-advanced-options-processed)', context)
    .addClass('ddblock-show-hide-advanced-options-processed')
    .bind("click change", function() {
      if (this.checked) {
        $("#ddblock-advanced-settings-wrapper").show();
        $("#ddblock-pager-position-wrapper").show();
        $("#ddblock-pager-event-wrapper").show();
        $("#ddblock-pager-height-wrapper").hide();
        $("#ddblock-pager-width-wrapper").hide();
        $("#edit-content-container").hide();
        $("#ddblock-advanced-content-container-overflow-wrapper").hide();
        $("#ddblock-advanced-content-container-height-wrapper").hide();
        $("#ddblock-advanced-content-container-width-wrapper").hide();
        $("#ddblock-image-settings-wrapper").hide();
        $("#pager-dimensions-wrapper").hide();
        $("#ddblock-template-wrapper").show();
        $("#edit-image-style-toggle-wrapper").show();
        $("#ddblock-image-style-settings-wrapper").show();
        $("#edit-image-height-wrapper").hide();
        $("#edit-image-width-wrapper").hide();
        $("#edit-custom-template-wrapper").show();
        $('#edit-pager-settings option[value="custom-pager"]').show();
      }
      else {
        $("#ddblock-advanced-settings-wrapper").hide();
        $("#ddblock-pager-position-wrapper").hide();
        $("#ddblock-pager-event-wrapper").hide();
        $("#ddblock-pager-height-wrapper").show();
        $("#ddblock-pager-width-wrapper").show();
        $("#edit-content-container").show();
        $("#ddblock-advanced-content-container-overflow-wrapper").show();
        $("#ddblock-advanced-content-container-height-wrapper").show();
        $("#ddblock-advanced-content-container-width-wrapper").show();
        $("#ddblock-image-settings-wrapper").show();
        $("#pager-dimensions-wrapper").show();
        $("#ddblock-template-wrapper").hide();
        $("#edit-image-style-toggle-wrapper").hide();
        $("#ddblock-image-style-settings-wrapper").hide();
        $("#edit-image-height-wrapper").show();
        $("#edit-image-width-wrapper").show();
        $("#edit-custom-template-wrapper").hide();
        $('#edit-pager-settings option[value="custom-pager"]').hide();
        $('#edit-pager-settings #edit-pager').val('number-pager');
      }
      return true;
    }).trigger('change').trigger('change')
  }
};

/*
 * Show/hide imagefolder/contenttype settings sections on the ddblock settings page.
 * don't change
 */
Drupal.behaviors.ddblockShowHideContentOptions = {
  attach: function(context, settings) {
  // get the child elements of the pager dropdown when the DOM has loaded
  var pagerOptions = $("#edit-pager").children('option');
  // Show/hide imagefolder/contenttype options depending on the select.
  $('#edit-input-type:not(.ddblock-show-hide-content-options-processed)', context)
  .addClass('ddblock-show-hide-content-options-processed')
  .bind("click change", function() {
    if ($('#ddblock-content-settings #edit-input-type').val() == 'images') {
      $("#ddblock-image-folder-settings-wrapper").show();
      $("#ddblock-content-types-settings-wrapper").hide();
      $('.form-item-image-style-toggle').show();
      $('.form-item-image-style-toggle').val(0);
      $("#ddblock-image-style-settings-wrapper").show();
      var regexEnabled = /^(n|p|\i)/; // number, prev/next, image
    }
    else {
      $("#ddblock-image-folder-settings-wrapper").hide();
      $("#ddblock-content-types-settings-wrapper").show();
//      $('.form-item-image-style-toggle').hide();
      $('.form-item-image-style-toggle').val(0);
      $("#ddblock-image-style-settings-wrapper").hide();
      var regexEnabled = /^(p)/; // prev/next
    }
    // set the pager options depending on the input type chosen
    $("#edit-pager").html(
      $(pagerOptions)
      // filter the option elements to only those we want to include in the dropdown
      .filter( function() { return this.value.match(regexEnabled);})
    );
    return false;
  }).trigger('change').trigger('change')
}
};

/*
 * Show/hide image styles settings sections on the ddblock instance settings page.
 * don't change
 */
Drupal.behaviors.ddblockShowHideImageStyleOptions = {
  attach: function(context, settings) {
  // Show/hide image style options depending on the checkbox.
  $('#ddblock-instance-settings #edit-image-style-toggle:not(.ddblock-show-hide-image-style-options-processed)', context)
  .addClass('ddblock-show-hide-image-style-options-processed')
  .bind("click change", function() {
    if (this.checked) {
      $("#ddblock-image-style-settings-wrapper").show();
    }
    else {
      $("#ddblock-image-style-settings-wrapper").hide();
    }
    return true;
  }).trigger('change').trigger('change')
  // Show/hide image style options depending on the checkbox.
  $('#ddblock-block-settings #edit-image-style-toggle:not(.ddblock-show-hide-image-style-options-processed)', context)
  .addClass('ddblock-show-hide-image-style-options-processed')
  // click for IE
  .bind("click change", function() {
    if (this.checked) {
      $("#ddblock-image-style-settings-wrapper").show();
    }
    else {
      $("#ddblock-image-style-settings-wrapper").hide();
    }
    return true;
  }).trigger('change').trigger('change')
}
};

/*
 * Show/hide pager settings sections on the ddblock instance settings page.
 * don't change
 */
Drupal.behaviors.ddblockShowHidePagerOptions = {
  attach: function(context, settings) {
  // Show/hide pager options depending on the checkbox.
  $('#ddblock-instance-settings #edit-pager-toggle:not(.ddblock-show-hide-pager-options-processed)', context)
  .addClass('ddblock-show-hide-pager-options-processed')
  .bind("click change", function() {
    if (this.checked){
      $("#ddblock-pager-settings-wrapper").show();
    }
    else {
      $("#ddblock-pager-settings-wrapper").hide();
    }
    return true;
  }).trigger('change').trigger('change')
  // Show/hide pager options depending on the checkbox.
  $('#ddblock-block-settings #edit-pager-toggle:not(.ddblock-show-hide-pager-options-processed)', context)
  .addClass('ddblock-show-hide-pager-options-processed')
  .bind("click change", function(){
    if (this.checked) {
      $("#ddblock-pager-settings-wrapper").show();
    }
    else {
      $("#ddblock-pager-settings-wrapper").hide();
    }
    return true;
  }).trigger('change').trigger('change')
 }
};

/*
 * Show/hide prev/next pager settings sections on the ddblock instance settings page.
 * don't change
 */
Drupal.behaviors.ddblockShowHidePrevNextPagerOptions = {
  attach: function(context, settings) {
  // Show/hide pager options depending on the checkbox.
  $('#ddblock-instance-settings #edit-pager2:not(.ddblock-show-hide-prev-next-pager-options-processed)', context)
  .addClass('ddblock-show-hide-prev-next-pager-options-processed')
  .bind("click change", function() {
    if (this.checked){
      $("#ddblock-pager2-settings-wrapper").show();
    }
    else {
      $("#ddblock-pager2-settings-wrapper").hide();
    }
    return true;
  }).trigger('change').trigger('change')
  // Show/hide pager options depending on the checkbox.
  $('#ddblock-block-settings #edit-pager2:not(.ddblock-show-hide-prev-next-pager-options-processed)', context)
  .addClass('ddblock-show-hide-prev-next-pager-options-processed')
  .bind("click change", function(){
    if (this.checked) {
      $("#ddblock-pager2-settings-wrapper").show();
    }
    else {
      $("#ddblock-pager2-settings-wrapper").hide();
    }
    return true;
  }).trigger('change').trigger('change')
 }
};

/*
 * Show/hide slide text settings sections on the ddblock instance settings page.
 * don't change
 */
Drupal.behaviors.ddblockShowHideSlideTextOptions = {
  attach: function(context, settings) {
  // Show/hide slide text options depending on the checkbox.
  $('#ddblock-instance-settings #edit-slide-text:not(.ddblock-show-hide-text-options-processed)', context)
  .addClass('ddblock-show-hide-text-options-processed')
  .bind("click change", function() {
    if (this.checked) {
      $("#ddblock-slide-text-settings-wrapper").show();
    }
    else {
      $("#ddblock-slide-text-settings-wrapper").hide();
    }
    return true;
  }).trigger('change').trigger('change')
}
};

/*
 * Show/hide jquery slide text settings sections on the ddblock instance settings page.
 * don't change
 */
Drupal.behaviors.ddblockShowHideSlideJqueryTextOptions = {
  attach: function(context, settings) {
  // Show/hide slide text options depending on the checkbox.
  $('#ddblock-instance-settings #edit-slide-text-jquery:not(.ddblock-show-hide-text-jquery-options-processed)', context)
  .addClass('ddblock-show-hide-text-jquery-options-processed')
  .bind("click change", function() {
    if (this.checked) {
      $("#ddblock-slide-jquery-settings-wrapper").show();
    }
    else {
      $("#ddblock-slide-jquery-settings-wrapper").hide();
    }
    return true;
  }).trigger('change').trigger('change')
}
};

/*
 * Show/hide Disable Pager click
 * Show when pager event is mouseover
 * Hide when pager event is click
 */
Drupal.behaviors.ddblockShowHideDisablepagerClickOptions = {
  attach: function(context, settings) {
  $('#edit-pager-event:not(.ddblock-show-hide-disable-pager-click-options-processed)', context)
  .addClass('ddblock-show-hide-disable-pager-click-options-processed')
  .bind("click change", function() {
    val = $('#edit-pager-event').val();
    switch (val) {
      case "click" :
        $('#ddblock-pager-disable-click-wrapper').hide();
      break;
      case "mouseover" :
        $('#ddblock-pager-disable-click-wrapper').show();
      break;
    }
    return false;
  }).trigger('change').trigger('change')
}
};

/*
 * Change pager container depending on the pager.
 */
Drupal.behaviors.ddblockChangePagerContainerOptions = {
  attach: function(context, settings) {
  // Change pager container option depending on select.
  $('#edit-pager:not(.ddblock-change-pager-container-options-processed)', context)
  .addClass('ddblock-change-pager-container-options-processed')
  .bind("change", function() {
    val = $('#edit-pager').val();
    switch (val) {
      case "number-pager" :
      case "prev-next-pager" :
      case "custom-pager" :
        $('#edit-pager-container').val('.custom-pager-item');
      break;
      case "scrollable-pager" :
        $('#edit-pager-container').val('.scrollable-pager-item');
      break;
    }
    return false;
  }).trigger('change').trigger('change')
}
};

/*
 * Show/hide custom template settings sections on the ddblock instance settings page.
 * don't change
 */
Drupal.behaviors.ddblockShowHideCustomTemplateOptions = {
  attach: function(context, settings) {
    // get variables
    var ddblockSettings = settings.ddblockCustomTemplate;
    // get the child elements of the pager dropdown when the DOM has loaded
    var pagerOptions = $("#edit-pager").children('option');
    // get the child elements of the pager position dropdown when the DOM has loaded
    var pagerPositionOptions = $("#edit-pager-position").children('option');

    // Show/hide imagefolder/contenttype options depending on the select.
    $('#ddblock-instance-settings #edit-template:not(.ddblock-show-hide-custom-template-options-processed)', context)
    .addClass('ddblock-show-hide-custom-template-options-processed')
    .bind("change", function() {
      val = $('#ddblock-instance-settings #edit-template').val();
      var pagertype = val.substr(val.indexOf('0')-1,2);
      var slideshowOrientation = val.substr(val.indexOf('0')+1,1);
      var regexEnabled;
      var pager;
      switch (pagertype) {
        case "10" :
          regexEnabled = /^nu/; // start with nu (number pager)
          pager = 'number-pager';
          $('#edit-pager-container').val('.custom-pager-item');
          $("#ddblock-pager-prev-next-loop-wrapper").hide();
          $("#ddblock-nr-of-pager-items-wrapper").hide();
          $("#ddblock-pager-scrollable-loop-wrapper").hide();
        break;
        case "20" :
          regexEnabled = /^p/; // start with p (prev/next pager)
          pager = 'prev-next-pager';
          $('#edit-pager-container').val('.custom-pager-item');
          $("#ddblock-pager-prev-next-loop-wrapper").show();
          $("#ddblock-nr-of-pager-items-wrapper").hide();
          $("#ddblock-pager-scrollable-loop-wrapper").hide();
        break;
        case "30" :
        case "40" :
        case "50" :
          regexEnabled = /^c/; // start with c (custom pager)
          pager = 'custom-pager';
          $('#edit-pager-container').val('.custom-pager-item');
          $("#ddblock-pager-prev-next-loop-wrapper").hide();
          $("#ddblock-nr-of-pager-items-wrapper").show();
          $("#ddblock-pager-scrollable-loop-wrapper").hide();
        break;
        case "60" :
        case "70" :
        case "80" :
        case "90" :
          regexEnabled = /^s/; // start with s (scrollable pager)
          pager = 'scrollable-pager';
          $('#edit-pager-container').val('.scrollable-pager-item');
          $("#ddblock-pager-prev-next-loop-wrapper").hide();
          $("#ddblock-nr-of-pager-items-wrapper").show();
          $("#ddblock-pager-scrollable-loop-wrapper").show();
        break;
      }
      // set the pager options depending on the theme choosen
      $("#edit-pager").html(
        $(pagerOptions)
        // filter the option elements to only those we want to include in the dropdown
        .filter( function() { return this.value.match(regexEnabled);})
      );

      if (slideshowOrientation == 'p') {
        var regexEnabled = /^(t|b)/; // start with t or b
      }
      else {
        var regexEnabled = /^(r|l)/; // start with r or l
      }
      // set the pager position options depending on the theme choosen
      $("#edit-pager-position").html(
        $(pagerPositionOptions)
        // filter the option elements to only those we want to include in the dropdown
        .filter( function() { return this.value.match(regexEnabled);})
      );
      return false;
    }).trigger('change').trigger('change')
  }
};
})(jQuery);