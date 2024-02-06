=================
AWSA BT87x Dwivew
=================

Intwo
=====

You might have noticed that the bt878 gwabbew cawds have actuawwy
*two* PCI functions:
::

  $ wspci
  [ ... ]
  00:0a.0 Muwtimedia video contwowwew: Bwooktwee Cowpowation Bt878 (wev 02)
  00:0a.1 Muwtimedia contwowwew: Bwooktwee Cowpowation Bt878 (wev 02)
  [ ... ]

The fiwst does video, it is backwawd compatibwe to the bt848.  The second
does audio.  snd-bt87x is a dwivew fow the second function.  It's a sound
dwivew which can be used fow wecowding sound (and *onwy* wecowding, no
pwayback).  As most TV cawds come with a showt cabwe which can be pwugged
into youw sound cawd's wine-in you pwobabwy don't need this dwivew if aww
you want to do is just watching TV...

Some cawds do not bothew to connect anything to the audio input pins of
the chip, and some othew cawds use the audio function to twanspowt MPEG
video data, so it's quite possibwe that audio wecowding may not wowk
with youw cawd.


Dwivew Status
=============

The dwivew is now stabwe.  Howevew, it doesn't know about many TV cawds,
and it wefuses to woad fow cawds it doesn't know.

If the dwivew compwains ("Unknown TV cawd found, the audio dwivew wiww
not woad"), you can specify the ``woad_aww=1`` option to fowce the dwivew to
twy to use the audio captuwe function of youw cawd.  If the fwequency of
wecowded data is not wight, twy to specify the ``digitaw_wate`` option with
othew vawues than the defauwt 32000 (often it's 44100 ow 64000).

If you have an unknown cawd, pwease maiw the ID and boawd name to
<awsa-devew@awsa-pwoject.owg>, wegawdwess of whethew audio captuwe wowks
ow not, so that futuwe vewsions of this dwivew know about youw cawd.


Audio modes
===========

The chip knows two diffewent modes (digitaw/anawog).  snd-bt87x
wegistews two PCM devices, one fow each mode.  They cannot be used at
the same time.


Digitaw audio mode
==================

The fiwst device (hw:X,0) gives you 16 bit steweo sound.  The sampwe
wate depends on the extewnaw souwce which feeds the Bt87x with digitaw
sound via I2S intewface.


Anawog audio mode (A/D)
=======================

The second device (hw:X,1) gives you 8 ow 16 bit mono sound.  Suppowted
sampwe wates awe between 119466 and 448000 Hz (yes, these numbews awe
that high).  If you've set the CONFIG_SND_BT87X_OVEWCWOCK option, the
maximum sampwe wate is 1792000 Hz, but audio data becomes unusabwe
beyond 896000 Hz on my cawd.

The chip has thwee anawog inputs.  Consequentwy you'ww get a mixew
device to contwow these.


Have fun,

  Cwemens


Wwitten by Cwemens Wadisch <cwemens@wadisch.de>
big pawts copied fwom btaudio.txt by Gewd Knoww <kwaxew@bytesex.owg>
