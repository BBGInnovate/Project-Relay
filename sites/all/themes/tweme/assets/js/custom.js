(function ($) {
$(document).ready(function() {
    
	//jQuery(".views_slideshow_jcarousel_pager_item .views-field-php").insertBefore(".views_slideshow_jcarousel_pager_item .views-field-created");

function deviceWidth() { 
	var w = document.documentElement.clientWidth;
	
	window.onresize=function(){
		w = document.documentElement.clientWidth;
	console.log('resize deviceWidth='+w);
	};
	
	return w;
}
//Set the width of the SoundCloud iframe
function setSoundCloudWidth() {
	var w = document.documentElement.clientWidth;
	var scw = w - (w * .25);
	$('.media-soundcloud-preview-wrapper iframe').attr('width', scw);
}

deviceWidth();
setSoundCloudWidth();

//Reset width on window resize
window.onresize=function(){
	//setSoundCloudWidth();
	deviceWidth();
};


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
		//if ( ! video.parents( 'object' ).length && videoClass !== 'vimeo-player') {
			video.wrap( '<div class="responsive-video-wrapper" style="padding-top: ' + ( aspect_ratio * 100 ) + '%" />' );
		} 
	/*	remove wrapper div styles for vimeo videos that are created by the module's script: /sites/all/modules/media_vimeo/js/media_vimeo.js*/
		if (videoClass == 'vimeo-player') {
			/*video.parent().removeAttr( 'style', 'width height' );
			video.parent().parent().removeAttr( 'style' );*/
			video.parent().parent().parent().removeAttr( 'style' );
		}
	
	});
};

$('body').responsiveVideo();

//Carousel Pager - Add active class on click
$('.views_slideshow_jcarousel_pager_item, #views_slideshow_controls_text_previous_event_card-block_1 a, #views_slideshow_controls_text_next_event_card-block_1 a').click(function() {
	$(this).addClass('views_slideshow_active_pager_field_item').siblings().removeClass('views_slideshow_active_pager_field_item');
	
	var slideIndex = $('.views_slideshow_cycle_slide:visible').index();
console.log('visible slide='+slideIndex);
});

$('#views_slideshow_controls_text_previous_event_card-block_1 a').click(function(){
	//alert('nav btn clicked');
});

/*var slideIndex = $('.views_slideshow_cycle_slide:visible').index();
console.log('visible slide='+slideIndex);*/

	
});
})(jQuery);

