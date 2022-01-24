# Deadrage
Airsoft Dead Light


ok so this is my first major project and i am looking for collaberation or anyone willing to help out with coding, hardware developement, etc
i have a basic hardware base i am currently employing but first let me explain my goal with this project.

The basic goal of this project started with a simple visual indicator of a dead light, then with that why not include a bleed out timer.  Then the thought 
occured to me why not try to make this web page configureable, or even work with blue tooth low energy to "talk" to other dead lights in proximity.  
with bluetooth my first idea was a way that someone could be medic'd, if your light started the bleedout, you could not be revived unless another deadlight
that was alive was in proximity of the light that was bleeding out(in my mind it would stop cheating from occuring by self revive) as well as i was thinking 
of putting a bluetooth transmitter in the spawn zone that would then allow the dead light to be reset and the light turned off.  there is also the posibility of
collecting stats of players: ie(deaths, revives, medic actions).  

At current state of my project i have made a 3d printable model to house the components.
The internals include:
  -LILYGO® TTGO MINI 32 V2.0 ESP32 WiFi bluetooth Module Development Board
    https://banggood.onelink.me/zMT7/1d876a25
  -CJMCU 12 Bit WS2812 5050 RGB LED Driver Development Board(neo pixel ring)
    https://banggood.onelink.me/zMT7/938f5d13
  -JJRC Upgraded 3.7v 200mAh 30C PH2.0 Plug Li-ion Battery for H36F Terzetto 1/20 RC Vehicle Drone Boat
    https://banggood.onelink.me/zMT7/f4da2df3
  -20Pcs Tactile Push Button Switch Momentary Tact Caps
    https://banggood.onelink.me/zMT7/a30dc12c
the coding works for bleedout, dead, and revive with animation, deep sleep
currently working on web interface to control bleedout time
   
