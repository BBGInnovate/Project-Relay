(function ($) {
  
  Drupal.behaviors.flickrsync  = {
    attach: function (context, settings) {

      // make a shortcut to the settings using a local variable
      var settings = Drupal.settings.flickrsync;

      $('#edit-has-js').each(function() { this.value = 1; });

      $('#progress:not(js)').addClass('js').each(function () {
        var holder = this;

        // Success: redirect to the summary.
        var updateCallback = function (progress, status, pb) {
          if (progress == 100) {
            pb.stopMonitoring();
            window.location = settings.url.finished;
          }
        }

        // Failure: point out error message and provide link to the summary.
        var showErrors = true;
        var errorCallback = function (pb) {
          if (showErrors) {
            var div = document.createElement('p');
            div.className = 'error';
            $(div).html('An unrecoverable error has occured. You can find the error message below.');
            $(holder).prepend(div);
          }
          //$('#wait').hide();
        }

        var progress = new Drupal.progressBar('updateprogress', updateCallback, "POST", errorCallback);
        progress.setProgress(-1, 'Starting update...');
        $(holder).append(progress.element);
        progress.startMonitoring(settings.url.do_import, 0);

        $('#flickrsync-stop').click(function() {
          progress.stopMonitoring();
          setTimeout(function() {
            $('#flickrsync-import').remove();
            window.location = settings.url.finished;
          }, 1000, holder, settings);
        });
      });
    }
  };

})(jQuery);
