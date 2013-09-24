AUDIOFIELD.MODULE
--------------------------------------------------------------------------------
This module allows embedding an audio file in a CCK field
This module is for adding new field that allows embedding an mp3 audio.

This module will use the  Google Reader MP3 Player to play your audio files by default, but you may choose one of several other suppoted players:
1. http://wpaudioplayer.com/download *Note make sure you should download the standalone edition
2. http://prdownloads.sourceforge.net/musicplayer/xspf_player_slim-correct-0.2.3.zip?download
3. http://prdownloads.sourceforge.net/musicplayer/button_player-0.1.zip?download
4. http://www.premiumbeat.com/flash_music_players/original/single/  (DEPRECATED)
5. http://www.premiumbeat.com/flash_music_players/original/thin/    (DEPRECATED)
6. http://www.premiumbeat.com/flash_music_players/original/mini/    (DEPRECATED)
7. Soundmanager2 http://www.schillmania.com/projects/soundmanager2/doc/download/

Or install FlowPlayer module (http://drupal.org/project/flowplayer) to use Flowplayer.
Or use Google Reader player (already installed with the module).

Once you got the above audio players you have to create a new folder called "player "at this
directory "sites/all/libraries". Now you can unzip the audio players directly into the "player" folder.

The resulting folder structure should resemble the following (you may need to rename the folders and files to match):

> The standalone WordPress player should be at:
/sites/all/libraries/player/audio-player/player.swf

> The XSPF slim player should be at:
/sites/all/libraries/player/xspf_player_slim.swf

> The XSPF button player should be at:
/sites/all/libraries/player/button/musicplayer.swf

> The Premium Beat single track player should be at:
/sites/all/libraries/player/playersinglepackage/playerSingle.swf

> The Premium Beat single track thin player should be at:
/sites/all/libraries/player/OriginalThinMusicPlayer.swf

> The Premium Beat single track mini player should be at:
/sites/all/libraries/player/LWMusicPlayer.swf


This module gives you the ability to choose the audio player you would like to
get on your web site from many audio players, from configuration page.

Finally you have to put any mp3 audio file at "\sites\all\libraries\player\"
and you have to name it as Sample_Track.mp3, this step just to gives the ability
to test all audio players before you choose your default audio player

API:
Originally this module supports only mp3 audio files. But other modules can extend this support by implementing hook_audiofield_players() in their modules.

For example to implement support for new example player you would do:
<?php
/* Example of creating additional players through hook_audiofield_players() */
function example_module_audiofield_players(){
    $players['example']=array(
        'path' => drupal_get_path('module','example_module').'/players/player.swf', //relative path to the player
        'name' => 'Example player',
        'download_link' => 'http://example.com/download',
        'filetypes' => array('mp3','wav','wma'),   //List of audio files your player can play
        'callback' =>'example_module_example_player',
    );

    return $players;
}

function example_module_example_player($player_path,$audio_file){
return '<object><param name="autoplay" value="true" />
            <param name="controller"value="true" />
            <embed src="' . $player_path . '"  width="65" height="21" float="left" wmode="transparent" flashvars="mediaPath=' . $audio_file .'&defaultVolume=100" autostart="true" loop="false"  controller="true" bgcolor="#FF9900" pluginspage="http://www.macromedia.com/go/getflashplayer" >
            </embed></object>';
}
?>

DISPLAY FORMATTERS
--------------------------------------------------------------------------------
There are 2 display formaters:
1. Audio player with download
2. Audio player only

MAINTAINERS
--------------------------------------------------------------------------------
Tamer Zoubi - <tamerzg@gmail.com>


