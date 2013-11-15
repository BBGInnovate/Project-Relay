(function ($) {
  $(document).ready(function() {
   
   alert('drupal.js here');
    $('.field-type-text-long table').addClass('table table-bordered');
    $('.field-type-text-with-summary table').addClass('table table-bordered');
  });
})(jQuery);
;
(function ($) {
$(document).ready(function() {
    
	//jQuery(".views_slideshow_jcarousel_pager_item .views-field-php").insertBefore(".views_slideshow_jcarousel_pager_item .views-field-created");

//Display Comments

alert('custom.js here');

$('.comments-btn').click(function(){
	
	var card = $(this).parent().parent().parent().parent().attr('id');
	alert('parent id='+ card);
	
	
});	
	
	
	
});
})(jQuery);
;
