(function($) {
  // Re-enable form elements that are disabled for non-ajax situations.
  Drupal.behaviors.pollfield = {
    attach: function() {
      var field_name=$('input.pollfield-more-choice-button').attr('name');
      var number_of_choices = 0;
      $('.' + field_name + '-pollfield-choices').each(function(){
        number_of_choices++;
      });
      console.log(number_of_choices);
      $('input.pollfield-more-choice-button').click(function(event){
        var field_name=$(this).attr('name');

        var number_of_choices = 0;
        $('.' + field_name + '-pollfield-choices').each(function(){
          number_of_choices++;
        });

        var choice_id = new String;
        choice_id = field_name + '-0';
        var choice = $('#' + choice_id);
        var new_choice = choice.clone();

        new_choice.children().children().children('input').val('');
        new_choice.attr('id', field_name + '-' + number_of_choices);
        // Change input name.
        new_choice.children().children().children('input').each(function() {
          var name=String;
            name = $(this).attr('name');
            var new_name=name.replace('[group][0]', '[group][' + number_of_choices + ']');
            $(this).attr('name', new_name);
            var id = String;
            id = $(this).attr('id');
            var new_id = id.replace('group-0', 'group-' + number_of_choices);
            $(this).attr('id', new_id);
        })
        //change label for
        new_choice.children().children().children('label').each(function() {
          var for_name=String;
          for_name = $(this).attr('for');
            var new_for_name = for_name.replace('group-0', 'group-' + number_of_choices);
            $(this).attr('for', new_for_name);
        });

        number_of_choices++;
        new_choice.children().children().children('em').text(number_of_choices);
        $(this).before(new_choice);
        event.preventDefault();
      })
    }
  };
})(jQuery);
