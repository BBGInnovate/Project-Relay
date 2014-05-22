;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; audio.js module
;;
;; Original author: jtphelan (http://drupal.org/user/54285)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

CONTENTS OF THIS FILE
=====================
* OVERVIEW
* USAGE
* INSTALLATION


OVERVIEW
========

The audio.js modules provides a field formatter for the file field type using 
the audio.js javascript library created by Anthony Kolber. 
http://kolber.github.com/audiojs/
 
It uses the native HTML5 <audio> where available and an invisible flash player 
to emulate <audio> for other browsers. It provides a consistent html player 
UI to all browsers which can be styled with custom css.

With Flash as a fallback, it should work pretty much anywhere.
It has been verified to work across:
Mobile Safari (iOS 3+)
Android (2.2+, w/Flash)
Safari (4+)
Chrome (7+)
Firefox (3+, w/ Flash)
Opera (10+, w/ Flash)
IE (6, 7, 8, w/ Flash)

Note that the audio.js library currently supports MP3 audio only.


USAGE
=====

audio.js creates a new field formattor for the file field type. Under your 
content types display settings select audio.js or audio.js playlist as you 
field format.



INSTALLATION
============

You must first download the audio.js library here: 
http://kolber.github.com/audiojs/

Extract the audiojs archive and copy the contents into your Drupal 
libraries directory, so that the audio.min.js file can be found at 
sites/all/libraries/audiojs/audiojs/audio.min.js
