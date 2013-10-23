(function ($) {
  $(document).ready(function() {
    $('.field-type-text-long table').addClass('table table-bordered');
    $('.field-type-text-with-summary table').addClass('table table-bordered');
  });
})(jQuery);
;
jQuery(document).ready(function() {
    var argVal = getURLParameter('nid');
    jQuery('.views_slideshow_cycle_slide').each(function(i){
        if(jQuery(this).find('.views-field-nid .field-content').html()==argVal){
            setTimeout(function() {
                jQuery('.views-slideshow-pager-field-item').eq(i).trigger('click');
            },10);
            return false;
        }
    })
});
function getURLParameter(name) {
    return decodeURIComponent((new RegExp('[?|&]' + name + '=' + '([^&;]+?)(&|#|;|$)').exec(location.search)||[,""])[1].replace(/\+/g, '%20'))||null;
}
;
