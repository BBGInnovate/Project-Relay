# Video.js support module 2 for Drupal 7

## Required dependencies

- Drupal core File module

## Optional dependencies

- [Libraries API 2](http://drupal.org/project/libraries)

## Installation

1. Install the Video.js module by copying the sources to a modules directory, 
   such as `sites/all/modules` or `sites/[yoursite]/modules`.
2. Download the Video.js library from http://videojs.com. Extract the module to
   `sites/all/libraries/video-js` and make sure that
   `sites/all/libraries/video-js/video.min.js` exists.
3. In your Drupal site, enable the module.
4. If not yet created, create a File field for one of your content types at
   Structure -> Content types -> [type] -> Manage fields. Make sure
   the allowed extensions contain only HTML5 video extensions, such as mp4,
   webm, mov and ogv. Use the `Number of values` setting to allow users to
   upload alternative versions of the same video, for instance MP4 and Ogg.
   To allow users to upload a poster image, also allow png, gif or jpg.
5. At the Manage display tab, select `Video.js` for your File field.
6. Create a piece of content with the configured field.
7. Create a poster image and upload the image in the FileField field created in
   step #4.

## Poster images from a separate field

It is possible to display images uploaded to an image field as the video
poster image. After you added an image field to your content type, edit the
display settings of the Video.js field and specify the image field in the
"Poster image field" setting.

## Installation with the Video module

If you are using the Video module, you can't configure the player at the
`Manage display` tab. Instead, select Video.js at the Players tab of the
Video settings page (admin/config/media/video/players).

## Support

Report bugs at http://drupal.org/project/issues/videojs
