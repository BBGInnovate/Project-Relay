
/**
 *  @file
 *  Javascript to enhance the views slideshow cycle form options.
 */

/**
 * This will set our initial behavior, by starting up each individual slideshow.
 */
(function ($) {
  
  // Since Drupal 7 doesn't support having a field based on one of 3 values of
  // a select box we need to add our own javascript handling.
  Drupal.behaviors.viewsSlideshowCycleAmountAllowedVisible = {
    attach: function (context) {
      
      // If necessary at start hide the amount allowed visible box.
      var type = $(":input[name='style_options[views_slideshow_cycle][pause_when_hidden_type]']").val();
      if (type == 'full') {
        $(":input[name='style_options[views_slideshow_cycle][amount_allowed_visible]']").parent().hide();
      }
      
      // Handle dependency on action advanced checkbox.
      $(":input[name='style_options[views_slideshow_cycle][action_advanced]']").change(function() {
        processValues('action_advanced');
      });
      
      // Handle dependency on pause when hidden checkbox.
      $(':input[name="style_options[views_slideshow_cycle][pause_when_hidden]"]').change(function() {
        processValues('pause_when_hidden');
      });
      
      // Handle dependency on pause when hidden type select box.
      $(":input[name='style_options[views_slideshow_cycle][pause_when_hidden_type]']").change(function() {
        processValues('pause_when_hidden_type');
      });
      
      // Process our dependencies.
      function processValues(field) {
        switch (field) {
          case 'action_advanced':
            if (!$(':input[name="style_options[views_slideshow_cycle][action_advanced]"]').is(':checked')) {
              $(":input[name='style_options[views_slideshow_cycle][amount_allowed_visible]']").parent().hide();
              break;
            }
          case 'pause_when_hidden':
            if (!$(':input[name="style_options[views_slideshow_cycle][pause_when_hidden]"]').is(':checked')) {
              $(":input[name='style_options[views_slideshow_cycle][amount_allowed_visible]']").parent().hide();
              break;
            }
          case 'pause_when_hidden_type':
            if ($(":input[name='style_options[views_slideshow_cycle][pause_when_hidden_type]']").val() == 'full') {
              $(":input[name='style_options[views_slideshow_cycle][amount_allowed_visible]']").parent().hide();
            }
            else {
              $(":input[name='style_options[views_slideshow_cycle][amount_allowed_visible]']").parent().show();
            }
        }
      }
    }
  }
  
  // Manage advanced options 
  Drupal.behaviors.viewsSlideshowCycleOptions = {
    attach: function (context) {
      if ($(":input[name='style_options[views_slideshow_cycle][advanced_options]']").length) {
        $(":input[name='style_options[views_slideshow_cycle][advanced_options]']").parent().hide();
        
        $(":input[name='style_options[views_slideshow_cycle][advanced_options_entry]']").parent().after(
          '<div style="margin-left: 10px; padding: 10px 0;">' + 
            '<a id="edit-style-options-views-slideshow-cycle-advanced-options-update-link" href="#">' + Drupal.t('Update Advanced Option') + '</a>' +
          '</div>'
        );
        
        $("#edit-style-options-views-slideshow-cycle-advanced-options-table").append('<tr><th colspan="2">' + Drupal.t('Applied Options') + '</th><tr>')
        
        var initialValue = $(":input[name='style_options[views_slideshow_cycle][advanced_options]']").val();
        var advancedOptions = JSON.parse(initialValue);
        for (var option in advancedOptions) {
          viewsSlideshowCycleAdvancedOptionsAddRow(option);
        }
        
        // Add the remove event to the advanced items.
        viewsSlideshowCycleAdvancedOptionsRemoveEvent();
        
        $(":input[name='style_options[views_slideshow_cycle][advanced_options_choices]']").change(function() {
          var selectedValue = $(":input[name='style_options[views_slideshow_cycle][advanced_options_choices]'] option:selected").val();
          if (typeof advancedOptions[selectedValue] !== 'undefined') {
            $(":input[name='style_options[views_slideshow_cycle][advanced_options_entry]']").val(advancedOptions[selectedValue]);
          }
          else {
            $(":input[name='style_options[views_slideshow_cycle][advanced_options_entry]']").val('');
          }
        });
    
        $('#edit-style-options-views-slideshow-cycle-advanced-options-update-link').click(function() {
          var option = $(":input[name='style_options[views_slideshow_cycle][advanced_options_choices]']").val();
          if (option) {
            var value = $(":input[name='style_options[views_slideshow_cycle][advanced_options_entry]']").val();
          
            if (typeof advancedOptions[option] == 'undefined') {
              viewsSlideshowCycleAdvancedOptionsAddRow(option);
              viewsSlideshowCycleAdvancedOptionsRemoveEvent()
            }
            advancedOptions[option] = value;
            viewsSlideshowCycleAdvancedOptionsSave();
          }
          
          return false;
        });
      }
      
      function viewsSlideshowCycleAdvancedOptionsAddRow(option) {
        $("#edit-style-options-views-slideshow-cycle-advanced-options-table").append(
          '<tr id="views-slideshow-cycle-advanced-options-table-row-' + option + '">' +
            '<td>' + option + '</td>' +
            '<td style="width: 20px;">' +
              '<a style="margin-top: 6px" title="Remove ' + option + '" alt="Remove ' + option + '" class="views-hidden views-button-remove views-slideshow-cycle-advanced-options-table-remove" id="views-slideshow-cycle-advanced-options-table-remove-' + option + '" href="#"><span>Remove</span></a>' +
            '</td>' +
          '</tr>'
        );
      }
      
      function viewsSlideshowCycleAdvancedOptionsRemoveEvent() {
        $('.views-slideshow-cycle-advanced-options-table-remove').unbind().click(function() {
          var itemID = $(this).attr('id');
          var uniqueID = itemID.replace('views-slideshow-cycle-advanced-options-table-remove-', '');
          delete advancedOptions[uniqueID];
          $('#views-slideshow-cycle-advanced-options-table-row-' + uniqueID).remove();
          viewsSlideshowCycleAdvancedOptionsSave();
          return false;
        });
      }
      
      function viewsSlideshowCycleAdvancedOptionsSave() {
        var advancedOptionsString = JSON.stringify(advancedOptions);
        $(":input[name='style_options[views_slideshow_cycle][advanced_options]']").val(advancedOptionsString);
      }
    }
  }
})(jQuery);
;
(function ($) {

/**
 * Toggle the visibility of a fieldset using smooth animations.
 */
Drupal.toggleFieldset = function (fieldset) {
  var $fieldset = $(fieldset);
  if ($fieldset.is('.collapsed')) {
    var $content = $('> .fieldset-wrapper', fieldset).hide();
    $fieldset
      .removeClass('collapsed')
      .trigger({ type: 'collapsed', value: false })
      .find('> legend span.fieldset-legend-prefix').html(Drupal.t('Hide'));
    $content.slideDown({
      duration: 'fast',
      easing: 'linear',
      complete: function () {
        Drupal.collapseScrollIntoView(fieldset);
        fieldset.animating = false;
      },
      step: function () {
        // Scroll the fieldset into view.
        Drupal.collapseScrollIntoView(fieldset);
      }
    });
  }
  else {
    $fieldset.trigger({ type: 'collapsed', value: true });
    $('> .fieldset-wrapper', fieldset).slideUp('fast', function () {
      $fieldset
        .addClass('collapsed')
        .find('> legend span.fieldset-legend-prefix').html(Drupal.t('Show'));
      fieldset.animating = false;
    });
  }
};

/**
 * Scroll a given fieldset into view as much as possible.
 */
Drupal.collapseScrollIntoView = function (node) {
  var h = document.documentElement.clientHeight || document.body.clientHeight || 0;
  var offset = document.documentElement.scrollTop || document.body.scrollTop || 0;
  var posY = $(node).offset().top;
  var fudge = 55;
  if (posY + node.offsetHeight + fudge > h + offset) {
    if (node.offsetHeight > h) {
      window.scrollTo(0, posY);
    }
    else {
      window.scrollTo(0, posY + node.offsetHeight - h + fudge);
    }
  }
};

Drupal.behaviors.collapse = {
  attach: function (context, settings) {
    $('fieldset.collapsible', context).once('collapse', function () {
      var $fieldset = $(this);
      // Expand fieldset if there are errors inside, or if it contains an
      // element that is targeted by the URI fragment identifier.
      var anchor = location.hash && location.hash != '#' ? ', ' + location.hash : '';
      if ($fieldset.find('.error' + anchor).length) {
        $fieldset.removeClass('collapsed');
      }

      var summary = $('<span class="summary"></span>');
      $fieldset.
        bind('summaryUpdated', function () {
          var text = $.trim($fieldset.drupalGetSummary());
          summary.html(text ? ' (' + text + ')' : '');
        })
        .trigger('summaryUpdated');

      // Turn the legend into a clickable link, but retain span.fieldset-legend
      // for CSS positioning.
      var $legend = $('> legend .fieldset-legend', this);

      $('<span class="fieldset-legend-prefix element-invisible"></span>')
        .append($fieldset.hasClass('collapsed') ? Drupal.t('Show') : Drupal.t('Hide'))
        .prependTo($legend)
        .after(' ');

      // .wrapInner() does not retain bound events.
      var $link = $('<a class="fieldset-title" href="#"></a>')
        .prepend($legend.contents())
        .appendTo($legend)
        .click(function () {
          var fieldset = $fieldset.get(0);
          // Don't animate multiple times.
          if (!fieldset.animating) {
            fieldset.animating = true;
            Drupal.toggleFieldset(fieldset);
          }
          return false;
        });

      $legend.append(summary);
    });
  }
};

})(jQuery);
;
(function ($) {

Drupal.behaviors.textarea = {
  attach: function (context, settings) {
    $('.form-textarea-wrapper.resizable', context).once('textarea', function () {
      var staticOffset = null;
      var textarea = $(this).addClass('resizable-textarea').find('textarea');
      var grippie = $('<div class="grippie"></div>').mousedown(startDrag);

      grippie.insertAfter(textarea);

      function startDrag(e) {
        staticOffset = textarea.height() - e.pageY;
        textarea.css('opacity', 0.25);
        $(document).mousemove(performDrag).mouseup(endDrag);
        return false;
      }

      function performDrag(e) {
        textarea.height(Math.max(32, staticOffset + e.pageY) + 'px');
        return false;
      }

      function endDrag(e) {
        $(document).unbind('mousemove', performDrag).unbind('mouseup', endDrag);
        textarea.css('opacity', 1);
      }
    });
  }
};

})(jQuery);
;
