//Test for phones not tablets
function mobileCheck() {
var check = false;
(function(a){if(/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|mobile.+firefox|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows (ce|phone)|xda|xiino/i.test(a)||/1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i.test(a.substr(0,4)))check = true})(navigator.userAgent||navigator.vendor||window.opera);
return check; }

(function ($) {
$(document).ready(function() {
    
	/**
	 * Begin listening for new content
	 */
	if(Drupal.settings.ogContext !== undefined && Drupal.settings.ogContext.gid !== undefined){
	    gid = Drupal.settings.ogContext.gid;
	    currentCount = Drupal.settings.viewsSlideshowCycle["#views_slideshow_cycle_main_event_card-block_1"].num_divs;
	    $('.notifications').on("click", '.notifications .menu-item, .notifications .notification-count', function(){
	    	//cheap: force a page refresh to show new content
	    	location.reload();
	    });
	    setInterval(function() {
	    	var call = $.getJSON( "event/" + gid + "/count", function(data) {
			  if(data.count > currentCount){
			  	//set the number of new items
	            $('.notifications .notification-count').text(data.count - currentCount);
	            //display notification
	            $('.notifications').show();
			  } else {
				$('.notifications').hide();
			  }
			});
	    }, 10000);
	}

	//jQuery(".views_slideshow_jcarousel_pager_item .views-field-php").insertBefore(".views_slideshow_jcarousel_pager_item .views-field-created");

/*$('head').append('<script src="/sites/all/themes/tweme/assets/js/jquery.nicescroll.min.js"></script>');
$('head').append('<script src="/sites/all/themes/tweme/assets/js/jquery.touchSwipe.min.js"></script>');
*/

//Set the width of the SoundCloud iframe
function setSoundCloudWidth() {
	var w = document.documentElement.clientWidth;
	var scw = w - (w * .25);
	$('.media-soundcloud-preview-wrapper iframe').attr('width', scw);
}

setSoundCloudWidth();

//Responsive Iframes
var el = $(this);
var embedIframe = el.find('iframe');
var embedImg = el.find('.views-field-field-card-upload-image img');

//Photo cards: remove width & height attr
embedImg.each(function() {
	var img = $(this);
	img.removeAttr('width height');
});

//Remove width and heights from all embeded iframes and videos
$.fn.responsiveVideo = function() {
	var el = $(this),
	all_videos = el.find( 'iframe, object, embed' );
	// Cycle through each video and add wrapper div with appropriate aspect ratio
	all_videos.each( function() {
		var video = $(this)
		aspect_ratio = video.attr( 'height' ) / video.attr( 'width' );
		video.removeAttr( 'height width' );
		var videoClass = video.attr('class');
		
		if ( ! video.parents( 'object' ).length) {
			video.wrap( '<div class="responsive-video-wrapper" style="padding-top: ' + ( aspect_ratio * 100 ) + '%" />' );
		} 
	/*	remove wrapper div styles for vimeo videos that are created by the module's script: /sites/all/modules/media_vimeo/js/media_vimeo.js*/
		if (videoClass == 'vimeo-player') {
			video.parent().parent().parent().removeAttr( 'style' );
		}
	});
};

$('body').responsiveVideo();

//Only 1 Disqus open instance is allowed per page. Remove any open threads when changing cards.
function removeComments() {
	$('#disqus_thread').remove();
	$('.nav-tabs li:first-child, .info-pane').addClass('active').siblings().removeClass('active');
}

//jCarousel Pager - Add active class when item in horizontal nav item is clicked
$('.views_slideshow_jcarousel_pager_item').click(function() {
	$(this).addClass('views_slideshow_active_pager_field_item').siblings().removeClass('views_slideshow_active_pager_field_item');
	
	removeComments();
});


//jCarousel Pager - Add active class when views slider arrows are clicked
var jc = $('.views_slideshow_jcarousel_pager').data('jcarousel'); //get jcarousel instance

var slide, slideId;

$('#views_slideshow_controls_text_previous_event_card-block_1 a, #views_slideshow_controls_text_next_event_card-block_1 a').click(function(){
  
  	   removeComments();
	   
	  //wait until the slide transition ends to get the id
	  setTimeout(function() {
  	
		  //get the id of the visible slide	
		  slide = $('#views_slideshow_cycle_teaser_section_event_card-block_1').find('.views-slideshow-cycle-main-frame-row:visible').attr('id');
		  slideId = slide.split('card-block');
		  var pattern = /\d{1,}$/;
		  var id = slideId[1].match(pattern);
		
		  jc.scroll(id-1); //slide jcarousel to active item
	
			//add active class to the matching jcarousel item
		  $('#views_slideshow_jcarousel_pager_item_bottom_event_card-block'+slideId[1]).addClass('views_slideshow_active_pager_field_item').siblings().removeClass('views_slideshow_active_pager_field_item');	
		  
		}, 1050) 
  });

//Set up footer nav for phones
$('<div id="current-card-wrapper"><div id="current-card"></div> <button data-target=".show-footer" data-toggle="collapse" class="btn btn-navbar" type="button" id="footer-btn"><span class="open">More Updates</span></div>').insertAfter('.views_slideshow_jcarousel_pager');

if($('#current-card-wrapper).is(:visible)')) {
	//Onload copy active nav item content to #current-card
	$('li.views_slideshow_active_pager_field_item').clone().appendTo('#current-card').removeClass('views_slideshow_active_pager_field_item');
}

function displayMobileNav(w) {
	if (w <= 640)	{
		
		//hide Get Alerts text
		$('#header-top #block-block-9 a').html('');
		$('.views-slideshow-controls-bottom').show();
		
		$('.views_slideshow_jcarousel_pager').addClass('collapse show-footer').css({
				'height': 0,
				'overflow': 'hidden'
		});
		
		//do this when div is immediately opened
		$('.show-footer').on('show', function () {
				//$("html, body").animate({ scrollTop: $(document).height() }, "slow");
				$('#current-card-wrapper').addClass('border');
				
				$('body').attr('style', 'overflow:hidden'); //prevent background scrolling when menu is open
		});
	  	//do this when div is opened and all transitions have stopped
		$('.show-footer').on('shown', function () {
				$('#footer-btn span').html('Close').removeClass('open').addClass('closed');
				$('.views_slideshow_jcarousel_pager').css({
						'overflow': 'auto',
						'z-index': 9999,
						'height': 'auto'
				});	
					
		});
		//do this when div is completely hidden and all transitions have stopped
		$('.show-footer').on('hidden', function () {
				$('#footer-btn span').html('More Updates').removeClass('closed').addClass('open');
				
				$('#current-card-wrapper').removeClass('border');

				$('body').attr('style', ''); 

				$('.views_slideshow_jcarousel_pager').css({
					'overflow': 'hidden',
					'z-index': 0,
					'height': 0
				});		
		});
		
		//on click change #current-card content
		$('.views_slideshow_jcarousel_pager_item').click(function() {
			$('#content').scrollTop(0);
			$('.show-footer').collapse('hide');
			$('#current-card').html('');
			$(this).clone().appendTo('#current-card').removeClass('views_slideshow_active_pager_field_item');
		});
		
	}
	else {
		$('.views_slideshow_jcarousel_pager').removeClass('collapse show-footer');		
		
		$('.views_slideshow_jcarousel_pager').css({
				'height': 'auto',
				'overflow': 'visible'
		});
	}
}

function updateCurrCard() {
	setTimeout(function() {
		if($('#current-card-wrapper).is(:visible)')) {
			//On swipe, copy active nav item content to #current-card
			$('#current-card').html('');
			$('li.views_slideshow_active_pager_field_item').clone().appendTo('#current-card');
		}
	}, 1200);
}


//Add swipe funtionality to main slider - jQuery Cycle
//Source: http://labs.rampinteractive.co.uk/touchSwipe/demos/
$("#views_slideshow_cycle_main_event_card-block_1").swipe({
        swipeLeft: function(event, direction, distance, duration, fingerCount) {   
			removeComments();
			$('#views_slideshow_controls_text_next_event_card-block_1 a').click();
		 	updateCurrCard();	
        },
        swipeRight: function(event, direction, distance, duration, fingerCount) {
            removeComments();
			$('#views_slideshow_controls_text_previous_event_card-block_1 a').click();
			updateCurrCard();
        }
    });

var dw = document.documentElement.clientWidth;

//onload
displayMobileNav(dw);
	
window.onresize=function(){
	dw = document.documentElement.clientWidth;
	displayMobileNav(dw);
};

//Fix for iOS 7 bug - scroll to top of the page when rotating to landscape mode
function setScroll() {
	if(window.orientation == 90 || window.orientation == -90) {
		window.scrollTo(0, 0);
	}
}

setScroll();
window.addEventListener('orientationchange', setScroll);

/*Temporary solution for orientation and scale bug on phones. The meta viewport attributes do not work when rotating the phone.
Source: http://adactio.com/journal/4470/ */
var viewportmeta = document.querySelector('meta[name="viewport"]');
if (viewportmeta) {
  viewportmeta.content = 'width=device-width, minimum-scale=1.0, maximum-scale=1.0, initial-scale=1.0';
  document.body.addEventListener('gesturestart', function () {
	  viewportmeta.content = 'width=device-width, minimum-scale=0.25, maximum-scale=1.6';
  }, false);
}


//for desktops and tablets
if(!mobileCheck()) {
	$('.views_slideshow_jcarousel_pager').removeClass('collapse');
	
	//Add the custom scrollbar to the comments tab content
	$('.comments-pane').niceScroll({
		  autohidemode: false,
		  cursorcolor: '#222222',
		  cursorwidth: 10,
		  cursorborder: 'none',
		  horizrailenabled: false,
		  cursorfixedheight: '50px'
	});

	$('.load_comments').click(function(){
		  //resize niceScroll after comments iframe loads
		  setTimeout(function(){
			  $('.comments-pane').getNiceScroll().resize();
		  }, 3600);
	});

	//Apply custom scrollbar to users who are not logged in
	if($('body').hasClass('not-logged-in')) { 
		
		$('html').niceScroll({
			autohidemode: false,
			cursorcolor: '#222222',
			cursorwidth: 6,
			cursorborder: 'none',
			horizrailenabled: false
		});
		
		$('html').css('overflow', 'hidden');
	}	
}


});
})(jQuery);
jQuery(document).ready(function(){

    jQuery(document).bind('DOMNodeInserted', function(event) {
        if(jQuery(event.target).attr('class') == 'messages status' && jQuery(event.target).parent('div').attr('id')=='modal-content'){
            setTimeout(function(){location.reload();},1000);
        }
    });   
    jQuery('#edit-field-card-headline').addClass("hidden");
    jQuery('#edit-field-author').addClass("hidden");
    //Add card node hide
    jQuery('#edit-field-card-type .form-radio').click(function(){
        if(jQuery(this).attr("id")=="edit-field-card-type-und-producermessage" || jQuery(this).attr("id")=="edit-field-card-type-und-ftweet" || jQuery(this).attr("id")=="edit-field-card-type-und-poll"){
            jQuery('#edit-field-card-headline').addClass("hidden");
            jQuery('#edit-field-author').addClass("hidden");
        }
        else{
            jQuery('#edit-field-card-headline').removeClass("hidden");
            jQuery('#edit-field-author').removeClass("hidden");
        }
    });
    /*Custom code to hide description field*/
    jQuery('#edit-field-card-type .form-radio').click(function(){
        if(jQuery(this).attr("id")=="edit-field-card-type-und-producermessage" || jQuery(this).attr("id")=="edit-field-card-type-und-ftweet" || jQuery(this).attr("id")=="edit-field-card-type-und-article"){
            jQuery('#edit-field-card-description').addClass("hidden");
        }
        else{
             jQuery('#edit-field-card-description').removeClass("hidden");
            }
    });
    /*end of custom code*/

});

