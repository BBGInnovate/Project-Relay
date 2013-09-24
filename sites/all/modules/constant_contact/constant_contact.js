// $Id$
jQuery(document).ready(function(){
	jQuery("#cc_auth").click(function(event)
    {
        jQuery.get('?q=check_login_handler', {
                username:jQuery('#cc_username').val(),
                password:jQuery('#cc_password').val()
            },
            function(returned_data)
            {
                jQuery(".cc_auth_res").html(returned_data);
            }
        );
		event.preventDefault();
	});
});
