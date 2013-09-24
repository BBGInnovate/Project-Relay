(function ($) {
/**
  * Set image settings
  * only used if no template is choosen for the dynamic display block
  */
Drupal.behaviors.ddblockImg = {
  attach: function(context, settings) {
    for (var base in settings.ddblockImages) {
      // get variables
      var ddblockSettings = settings.ddblockImages[base];

      // if no template and CCS is used set the image dimensions here
      if (ddblockSettings.setDimensions == 'none') {
        if ((ddblockSettings.imageHeight > 0) && (ddblockSettings.imageWidth > 0 )) {
          $('#ddblock-'+ ddblockSettings.block +' .ddblock-container img:not(.ddblock-processed)', context)
          .css('height',ddblockSettings.imageHeight + 'px')
          .css('width',ddblockSettings.imageWidth + 'px')
          .addClass('ddblock-processed');
        }
        else{
          $('#ddblock-'+ ddblockSettings.block +' .slider:not(.ddblock-slider-visble-processed)', context)
          .addClass('overflow-visible')
          .addClass('ddblock-slider-visible-processed');        
        }
      }
    }
  }
};

/**
  * Set content dimensions.
  * only used if no template is choosen for the dynamic display block
  */
Drupal.behaviors.ddblockImgContainer = {
  attach: function(context, settings) {
    for (var base in settings.ddblockImageContainer) {
      // get variables
      var ddblockSettings = settings.ddblockImageContainer[base];
      // if no template and CCS is used set the content dimensions here
      if (ddblockSettings.setDimensions == 'none') {
        if ((ddblockSettings.imageContainerHeight > 12) && (ddblockSettings.imageContainerWidth > 12 )) {

          $('#ddblock-' + ddblockSettings.block  +' .ddblock-container:not(.ddblock-processed)', context)
          .css('height',ddblockSettings.imageContainerHeight + 'px')
          .css('width',ddblockSettings.imageContainerWidth + 'px')
          .css('overflow','hidden')
          .addClass('ddblock-processed');
        }
      }
    }
  }
};

/**
  * Set the cycle plugin settings.
  *
  * Examples how and what to override for your own blocks
  *   Replace ddblockCycle with the ddblockCycle[BLOCKNUMBER]
  *   Change the onBefore and onAfter functions
  *
  */
Drupal.behaviors.ddblockCycle = {
  attach: function(context, settings) {

    //helper function to clone the options object
    function CloneObject(inObj) {
      for (i in inObj) {
        this[i] = inObj[i];
      }
    }

    // cycle Plugin onBefore function to add functionality before the next slide shows up
    // can be used to add the following effects to slide-text
    // fadeOut - Fade out all matched elements by adjusting their opacity and firing an optional callback after completion.
    // slideUp - Hide all matched elements by adjusting their height and firing an optional callback after completion.
    // hide - Hide all matched elements using a graceful animation and firing an optional callback after completion.
    function onBefore(curr, next, opts, fwd) {
      if (opts.currSlide != opts.nextSlide) {
        if (opts.slideTextjQuery == 1){
          if (opts.slideTextEffectBeforeSpeed == 0) {
            opts.slideTextEffectBeforeSpeed = 1;
          };
          if (opts.slideTextEffectBeforeEasing == 'none') {
            opts.slideTextEffectBeforeEasing = '';
          };
          switch (opts.slideTextEffectBefore) {
            case "fadeOut":
              $("#ddblock-" + opts.ddblocknr + ' ' + opts.slideTextContainer + '-' + opts.slideTextPosition)
              .stop(true,true)
              .fadeOut(opts.slideTextEffectBeforeSpeed, opts.slideTextEffectBeforeEasing);
              $("#ddblock-"+ opts.ddblocknr + ' div.slide-' + opts.nextSlide + ' ' + opts.slideTextContainer + '-' + opts.slideTextPosition).css({"display":"none"});
            break;
            case "slideUp":
              $("#ddblock-"+ opts.ddblocknr + ' ' + opts.slideTextContainer + '-' + opts.slideTextPosition)
              .stop(true,true)
              .slideUp(opts.slideTextEffectBeforeSpeed, opts.slideTextEffectBeforeEasing);
//              .effect('easeOutBounce','',opts.slideTextEffectAfterSpeed);
             $("#ddblock-"+ opts.ddblocknr + ' div.slide-' + opts.nextSlide + ' ' + opts.slideTextContainer + '-' + opts.slideTextPosition).css({"display":"none"});
            break;
            default:
              $("#ddblock-"+ opts.ddblocknr + ' ' + opts.slideTextContainer + '-' + opts.slideTextPosition)
              .stop(true,true)
              .hide(opts.slideTextEffectBeforeSpeed, opts.slideTextEffectBeforeEasing);
              $("#ddblock-"+ opts.ddblocknr + ' div.slide-' + opts.nextSlide + ' ' + opts.slideTextContainer + '-' + opts.slideTextPosition).css({"display":"none"});
           }
        }
      }
    }

    // cycle Plugin onAfter function to add functionality after the next slide shows up
    // can be used to add the following effects to slide-text
    // fadein - Fade in all matched elements by adjusting their opacity and firing an optional callback after completion.
    // slideDown - Reveal all matched elements by adjusting their height and firing an optional callback after completion.
    // show - Show all matched elements using a graceful animation and firing an optional callback after completion.
    function onAfter(curr, next, opts, fwd) {
      if (opts.slideTextjQuery == 1){
        if (opts.slideTextEffectAfterSpeed == 0) {
          opts.slideTextEffectAfterSpeed = 1;
        };
        if (opts.slideTextEffectAfterEasing == 'none') {
          opts.slideTextEffectAfterEasing = '';
        };
        switch (opts.slideTextEffectAfter) {
          case "fadeIn":
            $("#ddblock-"+ opts.ddblocknr + ' ' + opts.slideTextContainer + '-'  + opts.slideTextPosition)
            .fadeIn(opts.slideTextEffectAfterSpeed, opts.slideTextEffectAfterEasing);
            $("#ddblock-"+ opts.ddblocknr + ' div.slide-' + opts.nextSlide + ' ' + opts.slideTextContainer + '-' + opts.slideTextPosition).css({"display":"none"});
          break;
          case 'slideDown':
            $("#ddblock-"+ opts.ddblocknr + ' ' + opts.slideTextContainer + '-' + opts.slideTextPosition)
            .slideDown(opts.slideTextEffectAfterSpeed, opts.slideTextEffectAfterEasing);
            $("#ddblock-"+ opts.ddblocknr + ' div.slide-' + opts.nextSlide + ' ' + opts.slideTextContainer + '-' + opts.slideTextPosition).css({"display":"none"});
          break;
          default:
            $("#ddblock-"+ opts.ddblocknr + ' ' + opts.slideTextContainer + '-' + opts.slideTextPosition)
            .show(opts.slideTextEffectAfterSpeed, opts.slideTextEffectAfterEasing);
            $("#ddblock-"+ opts.ddblocknr + ' div.slide-' + opts.nextSlide + ' ' + opts.slideTextContainer + '-' + opts.slideTextPosition).css({"display":"none"});
        }
      }
      //when scrollable pager is used set active pager-item to current slide
      if (opts.pager1 == 'scrollable-pager' && opts.myScrollable){
        opts.myScrollable.click(opts.currSlide);
      }

      // show pager count (0 of x)
      $("#ddblock-"+ opts.ddblocknr + ' ' + 'a.count').html((opts.currSlide + 1) + " of " + opts.slideCount);

      // Only show prev if previous slide exist - Only show next if next slide exist
      if (opts.pagerPrevNextLoop == 0) {
        var index = $(this).parent().children().index(this);
        $("#ddblock-"+ opts.ddblocknr + ' li.pager-prev ' + ' a.prev')[index == 0 ? 'hide' : 'show']();
        $("#ddblock-"+ opts.ddblocknr + ' li.pager-prev ' + ' a.next')[index == opts.slideCount - 1 ? 'hide' : 'show']();
      }

      // For prev/next pager in the slides. Only show prev if previous slide exist - Only show next if next slide exist

      if (opts.pager2SlideHide == 1) {
        var index = $(this).parent().children().index(this);
        $("#ddblock-"+ opts.ddblocknr + ' div.prev-container ' + 'a.prev')[index == 0 ? 'hide' : 'show']();
        $("#ddblock-"+ opts.ddblocknr + ' div.next-container ' + 'a.next')[index == opts.slideCount - 1 ? 'hide' : 'show']();
      }
    }

    i=0;
    for (var base in settings.ddblockContent) {
      // new options var for every block
      var options = new CloneObject($.fn.cycle.defaults);

      // simplify variable name
      var ddblockSettings = settings.ddblockContent[base];
      var block = ddblockSettings.block;
      var custom = ddblockSettings.custom;
      var pager = ddblockSettings.pager;
      var pager2 = ddblockSettings.pager2;
      var contentContainer = ddblockSettings.contentContainer;
      var pagerContainer = ddblockSettings.pagerContainer;

      // if not processed
      if (!$('#ddblock-' + block + '.ddblock-processed', context).size()) {

        // set transition option
        options.fx = ddblockSettings.fx;
//        options.easeOut = ddblockSettings.easeOut;
        if (ddblockSettings.easeOut != 'none') {
          options.easeOut = ddblockSettings.easeOut;
        }  
        if (ddblockSettings.easeIn != 'none') {
          options.easeIn = ddblockSettings.easeIn;
        }  

        //set delay option for the blocks at different values so they less interfere with eachother
        options.delay = i * -1000;

        // set pager. You can have only one pager per block this way
        if (pager == 'image-pager' || pager == 'number-pager' || pager == 'custom-pager' || pager == 'scrollable-pager') {
          // number pager, image pager , custom pager and scrollable pager
          options.pager = "#ddblock-" + pager + "-" + block;

          //store pager1
          options.pager1 = pager;

          if (pager == 'number-pager') {
            options.pagerAnchorBuilder = function(idx, slide) {
              // return selector string for existing anchor
              return "#ddblock-" + pager + "-" + block + " li.number-pager-item:eq(" + idx + ") a.pager-link";
            }
          }
          if (pager == 'image-pager') {
            options.pagerAnchorBuilder = function(idx, slide) {
              // return selector string for existing anchor
              return "#ddblock-" + pager + "-" + block + " li:eq(" + idx + ") a";
            }
          }
          if (pager == 'custom-pager') {
            options.pagerAnchorBuilder = function(idx, slide) {
              // return selector string for existing anchor
              return "#ddblock-" + pager + "-" + block + " " + pagerContainer + ":eq(" + idx + ") a.pager-link";
            }
          }
          if (pager == 'scrollable-pager') {
            options.pagerAnchorBuilder = function(idx, slide) {
              // return selector string for existing anchor
              return "#ddblock-" + pager + "-" + block + " " + pagerContainer + ":eq(" + idx + ") a.pager-link";
            }
          }
        } // set pager.
        if (pager == 'prev-next-pager' || pager2 == 1) {
          //store pagerPrevNextLoop
          options.pagerPrevNextLoop = ddblockSettings.pagerPrevNextLoop;
          options.prev = "#ddblock-"+ block + " .prev";
          options.next = "#ddblock-"+ block + " .next";
        }
        else {
          //set next
          if (ddblockSettings.next == 1) {
            options.next = "#ddblock-"+ block + ' ' + contentContainer;
          }
        }

        //set event which drives the pager navigation
        options.pagerEvent = ddblockSettings.pagerEvent;

        // If pager fast set use fastOnEvent pager
        options.fastOnEvent = (ddblockSettings.pagerFast == 1) ? 1 : 0;

        // pause slideshow on pager hover
        options.pauseOnPagerHover = (ddblockSettings.pagerPause == 1) ? 1 : 0;

        // disable click if pager is mouseover
        if (ddblockSettings.pagerEvent == 'mouseover') {
          if (ddblockSettings.pagerDisableClick == 1) {
            $("#ddblock-" + pager + "-" + block + " a.pager-link").click(function() {
              return false;
            });
          }
          else {
            $("#ddblock-" + pager + "-" + block + " a.pager-link").click(function() {
              location.href = this.href;
            });
          }
        }

        options.pager2SlideHide = ddblockSettings.pager2SlideHide;

        //set expression for selecting slides (if something other than all children is required)
        //options.slideExpr = contentContainer;

        //set speed of the transition (any valid fx speed value)
        options.speed = parseInt(ddblockSettings.speed);
        if (options.speed == 0) {
          options.speed = 1;
        };

        //set timeout in milliseconds between slide transitions (0 to disable auto advance)
        options.timeout = parseInt(ddblockSettings.timeOut);

        //set pause, true to enable "pause on hover"
        options.pause = (ddblockSettings.pause == 1) ? 1 : 0;

        //set custom options, custom need to start with the character {,
        //to prevent errors from a wywsiwyg editor which adds e.g. <br /> to the custom field.
        // use custom.substr(0,1) instead of custom[0] to prevent error with IE7
        if (custom && custom.substr(0,1) == '{') {
          // get the \r\n from the string
          var custom1 = custom.replace(/\r\n/gi,"");

          // parse into JSON object
          var custom2 = JSON.parse(custom1);

          // merge custom2 with options object
          jQuery.extend(true, options, custom2);
        }

        options.ddblocknr = block;
        options.before = onBefore;
        options.after = onAfter;
        options.pagerContainer = ddblockSettings.pagerContainer;

        // redefine Cycle's updateActivePagerLink function
        $.fn.cycle.updateActivePagerLink = function(pager, currSlide) {
          $(pager)
          .find('a.pager-link')
          .removeClass('activeSlide')
          .filter('a.pager-link:eq('+currSlide+')')
          .addClass('activeSlide');
          $(pager)
          .find('.custom-pager-item')
          .removeClass('active-pager-item')
          .filter('.custom-pager-item:eq('+currSlide+')')
          .addClass('active-pager-item');
          $(pager)
          .find('.scrollable-pager-item')
          .removeClass('active-pager-item')
          .filter('.scrollable-pager-item:eq('+currSlide+')')
          .addClass('active-pager-item');
        };
        
        //Basic block
        if (ddblockSettings.setDimensions == 'none') {
          //only one slide
          if (ddblockSettings.nrOfItems <= 1) {
            var $container = $('#ddblock-' + block + ' ' + contentContainer).parent();
            $container
            .css('visibility', 'visible')
            .addClass('ddblock-processed');
            $(contentContainer, $container).css('display', 'block');
            var $slideshowContainer = $('#ddblock-' + block);
            //hide the pager
            $('#ddblock-' + pager + '-' + block, $slideshowContainer).css('display', 'none');
            //hide navi, prev and next pager of scrollable pager
            if (pager == 'scrollable-pager') {
              $('.navi', $slideshowContainer).css('display', 'none');
              $('.prev', $slideshowContainer).css('display', 'none');
              $('.next', $slideshowContainer).css('display', 'none');
            }
          }
          //more than one slide
          else {
            var $container = $('#ddblock-' + block + ' ' + contentContainer).parent();
            $container
            .cycle(options)
            .css('height',ddblockSettings.Height + 'px')
            .css('width',ddblockSettings.Width + 'px')
            .css('overflow', ddblockSettings.overflow)
            .css('visibility', 'visible')
            .addClass('ddblock-processed');
            $('#ddblock-' + block).css('visibility', 'visible');
          }
        }
        // advanced block
        else {
          if (ddblockSettings.slideTextjQuery == 1) {
            //set slidetext options
            options.slideTextContainer = ddblockSettings.slideTextContainer;
            options.slideTextPosition = ddblockSettings.slideTextPosition;
            options.slideTextEffectBefore = ddblockSettings.slideTextEffectBefore;
            options.slideTextEffectBeforeSpeed = ddblockSettings.slideTextEffectBeforeSpeed;
            options.slideTextEffectBeforeEasing = ddblockSettings.slideTextEffectBeforeEasing;
            options.slideTextEffectAfter = ddblockSettings.slideTextEffectAfterEasing;
            options.slideTextEffectAfterSpeed = ddblockSettings.slideTextEffectAfterSpeed;
            options.slideTextEffectAfterEasing = ddblockSettings.slideTextEffectAfterEasing;
            options.slideTextjQuery = ddblockSettings.slideTextjQuery;
          }

          if (pager == 'scrollable-pager') {
            // set scrollableVertical to true when pager at left of right right, otherwise the scrollableVertical to false
            if (ddblockSettings.pagerPosition == 'left' || ddblockSettings.pagerPosition == 'right') {
               scrollableVertical = true;
            }
            else {
              scrollableVertical = false;
            }
            // create one scrollable element and return the API by enabling the "api" property
            if ($('#ddblock-scrollable-pager-' + block).length > 0){
              var myScrollable = $('#ddblock-scrollable-pager-' + block).scrollable({

                // number of items vissible in scrollable pager
                size: ddblockSettings.nrOfPagerItems,

                //vertical slideshow
                vertical: scrollableVertical,

                circular: true,

                //nextitem navigation, default used
                next: '.next',

                //previtem navigation, default used
                prev: '.prev',

                //enable api property
                api: true

              });
              if (myScrollable) {
                //set first slide as activate slide in scrollable pager
                myScrollable.click(0);

                //set myScrollable cycle option to scrollable API to use in onafter
                options.myScrollable = myScrollable;

                //set total nr of pager items
                options.nrOfPagerItems = ddblockSettings.nrOfPagerItems;
              }
            }
          }

          //only one slide
          if (ddblockSettings.nrOfItems <= 1) {
            //Use the parent of the slides as the parent container so the children function
            //can be used for the second pager
            var $container = $('#ddblock-' + block + ' ' + contentContainer).parent();
            $container
            .css('visibility', 'visible')
            .addClass('ddblock-processed');
            $(contentContainer, $container).css('display', 'block');
            var $slideshowContainer = $('#ddblock-' + block);
            //hide the pager
            $('#ddblock-' + pager + '-' + block, $slideshowContainer).css('display', 'none');
            //hide navi, prev and next pager of scrollable pager
            if (pager == 'scrollable-pager') {
              $('.navi', $slideshowContainer).css('display', 'none');
              $('.prev', $slideshowContainer).css('display', 'none');
              $('.next', $slideshowContainer).css('display', 'none');
            }
          }
          //more then one slide
          else {
            var $container = $('#ddblock-' + block + ' ' + contentContainer).parent();
            $container
            .cycle(options)
            .css('visibility', 'visible')
            .addClass('ddblock-processed');
          }
        }  // advanced block
      } // if not processed
      i++;
    } // for settings.ddblockContent
  } // attach
}; // drupal.behaviors

})(jQuery);
