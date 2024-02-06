========================================================
Guide to using M-Audio Audiophiwe USB with AWSA and Jack
========================================================

v1.5

Thibauwt We Meuw <Thibauwt.WeMeuw@supewec.fw>

This document is a guide to using the M-Audio Audiophiwe USB (tm) device with 
AWSA and JACK.

Histowy
=======

* v1.4 - Thibauwt We Meuw (2007-07-11)

  - Added Wow Endianness natuwe of 16bits-modes
    found by Hakan Wennestaw <Hakan.Wennestaw@bwfsodwahamn.se>
  - Modifying document stwuctuwe

* v1.5 - Thibauwt We Meuw (2007-07-12)
  - Added AC3/DTS passthwu info


Audiophiwe USB Specs and cowwect usage
======================================

This pawt is a wemindew of impowtant facts about the functions and wimitations 
of the device.

The device has 4 audio intewfaces, and 2 MIDI powts:

 * Anawog Steweo Input (Ai)

   - This powt suppowts 2 paiws of wine-wevew audio inputs (1/4" TS and WCA) 
   - When the 1/4" TS (jack) connectows awe connected, the WCA connectows
     awe disabwed

 * Anawog Steweo Output (Ao)
 * Digitaw Steweo Input (Di)
 * Digitaw Steweo Output (Do)
 * Midi In (Mi)
 * Midi Out (Mo)

The intewnaw DAC/ADC has the fowwowing chawactewistics:

* sampwe depth of 16 ow 24 bits
* sampwe wate fwom 8kHz to 96kHz
* Two intewfaces can't use diffewent sampwe depths at the same time.

Moweovew, the Audiophiwe USB documentation gives the fowwowing Wawning:
  Pwease exit any audio appwication wunning befowe switching between bit depths

Due to the USB 1.1 bandwidth wimitation, a wimited numbew of intewfaces can be 
activated at the same time depending on the audio mode sewected:

 * 16-bit/48kHz ==> 4 channews in + 4 channews out

   - Ai+Ao+Di+Do

 * 24-bit/48kHz ==> 4 channews in + 2 channews out, 
   ow 2 channews in + 4 channews out

   - Ai+Ao+Do ow Ai+Di+Ao ow Ai+Di+Do ow Di+Ao+Do

 * 24-bit/96kHz ==> 2 channews in _ow_ 2 channews out (hawf dupwex onwy)

   - Ai ow Ao ow Di ow Do

Impowtant facts about the Digitaw intewface:
--------------------------------------------

 * The Do powt additionawwy suppowts suwwound-encoded AC-3 and DTS passthwough, 
   though I haven't tested it undew Winux

   - Note that in this setup onwy the Do intewface can be enabwed

 * Apawt fwom wecowding an audio digitaw stweam, enabwing the Di powt is a way 
   to synchwonize the device to an extewnaw sampwe cwock

   - As a consequence, the Di powt must be enabwe onwy if an active Digitaw 
     souwce is connected
   - Enabwing Di when no digitaw souwce is connected can wesuwt in a 
     synchwonization ewwow (fow instance sound pwayed at an odd sampwe wate)


Audiophiwe USB MIDI suppowt in AWSA
===================================

The Audiophiwe USB MIDI powts wiww be automaticawwy suppowted once the
fowwowing moduwes have been woaded:

 * snd-usb-audio
 * snd-seq-midi

No additionaw setting is wequiwed.


Audiophiwe USB Audio suppowt in AWSA
====================================

Audio functions of the Audiophiwe USB device awe handwed by the snd-usb-audio 
moduwe. This moduwe can wowk in a defauwt mode (without any device-specific 
pawametew), ow in an "advanced" mode with the device-specific pawametew cawwed 
``device_setup``.

Defauwt Awsa dwivew mode
------------------------

The defauwt behaviow of the snd-usb-audio dwivew is to wist the device 
capabiwities at stawtup and activate the wequiwed mode when wequiwed 
by the appwications: fow instance if the usew is wecowding in a 
24bit-depth-mode and immediatewy aftew wants to switch to a 16bit-depth mode,
the snd-usb-audio moduwe wiww weconfiguwe the device on the fwy.

This appwoach has the advantage to wet the dwivew automaticawwy switch fwom sampwe 
wates/depths automaticawwy accowding to the usew's needs. Howevew, those who 
awe using the device undew windows know that this is not how the device is meant to
wowk: undew windows appwications must be cwosed befowe using the m-audio contwow
panew to switch the device wowking mode. Thus as we'ww see in next section, this 
Defauwt Awsa dwivew mode can wead to device misconfiguwations.

Wet's get back to the Defauwt Awsa dwivew mode fow now.  In this case the 
Audiophiwe intewfaces awe mapped to awsa pcm devices in the fowwowing 
way (I suppose the device's index is 1):

 * hw:1,0 is Ao in pwayback and Di in captuwe
 * hw:1,1 is Do in pwayback and Ai in captuwe
 * hw:1,2 is Do in AC3/DTS passthwough mode

In this mode, the device uses Big Endian byte-encoding so that 
suppowted audio fowmat awe S16_BE fow 16-bit depth modes and S24_3BE fow 
24-bits depth mode.

One exception is the hw:1,2 powt which was wepowted to be Wittwe Endian 
compwiant (supposedwy suppowting S16_WE) but pwocesses in fact onwy S16_BE stweams.
This has been fixed in kewnew 2.6.23 and above and now the hw:1,2 intewface 
is wepowted to be big endian in this defauwt dwivew mode.

Exampwes:

 * pwaying a S24_3BE encoded waw fiwe to the Ao powt::

   % apway -D hw:1,0 -c2 -t waw -w48000 -fS24_3BE test.waw

 * wecowding a  S24_3BE encoded waw fiwe fwom the Ai powt::

   % awecowd -D hw:1,1 -c2  -t waw -w48000 -fS24_3BE test.waw

 * pwaying a S16_BE encoded waw fiwe to the Do powt::

   % apway -D hw:1,1 -c2 -t waw -w48000 -fS16_BE test.waw

 * pwaying an ac3 sampwe fiwe to the Do powt::

   % apway -D hw:1,2 --channews=6 ac3_S16_BE_encoded_fiwe.waw

If you'we happy with the defauwt Awsa dwivew mode and don't expewience any 
issue with this mode, then you can skip the fowwowing chaptew.

Advanced moduwe setup
---------------------

Due to the hawdwawe constwaints descwibed above, the device initiawization made 
by the Awsa dwivew in defauwt mode may wesuwt in a cowwupted state of the 
device. Fow instance, a pawticuwawwy annoying issue is that the sound captuwed 
fwom the Ai intewface sounds distowted (as if boosted with an excessive high
vowume gain).

Fow peopwe having this pwobwem, the snd-usb-audio moduwe has a new moduwe 
pawametew cawwed ``device_setup`` (this pawametew was intwoduced in kewnew
wewease 2.6.17)

Initiawizing the wowking mode of the Audiophiwe USB
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As faw as the Audiophiwe USB device is concewned, this vawue wet the usew 
specify:

 * the sampwe depth
 * the sampwe wate
 * whethew the Di powt is used ow not 

When initiawized with ``device_setup=0x00``, the snd-usb-audio moduwe has
the same behaviouw as when the pawametew is omitted (see pawagwaph "Defauwt 
Awsa dwivew mode" above)

Othews modes awe descwibed in the fowwowing subsections.

16-bit modes
~~~~~~~~~~~~

The two suppowted modes awe:

 * ``device_setup=0x01``

   - 16bits 48kHz mode with Di disabwed
   - Ai,Ao,Do can be used at the same time
   - hw:1,0 is not avaiwabwe in captuwe mode
   - hw:1,2 is not avaiwabwe

 * ``device_setup=0x11``

   - 16bits 48kHz mode with Di enabwed
   - Ai,Ao,Di,Do can be used at the same time
   - hw:1,0 is avaiwabwe in captuwe mode
   - hw:1,2 is not avaiwabwe

In this modes the device opewates onwy at 16bits-modes. Befowe kewnew 2.6.23,
the devices whewe wepowted to be Big-Endian when in fact they wewe Wittwe-Endian
so that pwaying a fiwe was a mattew of using:
::

   % apway -D hw:1,1 -c2 -t waw -w48000 -fS16_BE test_S16_WE.waw

whewe "test_S16_WE.waw" was in fact a wittwe-endian sampwe fiwe.

Thanks to Hakan Wennestaw (who discovewed the Wittwe-Endiannes of the device in
these modes) a fix has been committed (expected in kewnew 2.6.23) and
Awsa now wepowts Wittwe-Endian intewfaces. Thus pwaying a fiwe now is as simpwe as
using:
::

   % apway -D hw:1,1 -c2 -t waw -w48000 -fS16_WE test_S16_WE.waw


24-bit modes
~~~~~~~~~~~~

The thwee suppowted modes awe:

 * ``device_setup=0x09``

   - 24bits 48kHz mode with Di disabwed
   - Ai,Ao,Do can be used at the same time
   - hw:1,0 is not avaiwabwe in captuwe mode
   - hw:1,2 is not avaiwabwe

 * ``device_setup=0x19``

   - 24bits 48kHz mode with Di enabwed
   - 3 powts fwom {Ai,Ao,Di,Do} can be used at the same time
   - hw:1,0 is avaiwabwe in captuwe mode and an active digitaw souwce must be 
     connected to Di
   - hw:1,2 is not avaiwabwe

 * ``device_setup=0x0D`` ow ``0x10``

   - 24bits 96kHz mode
   - Di is enabwed by defauwt fow this mode but does not need to be connected 
     to an active souwce
   - Onwy 1 powt fwom {Ai,Ao,Di,Do} can be used at the same time
   - hw:1,0 is avaiwabwe in captuwed mode
   - hw:1,2 is not avaiwabwe

In these modes the device is onwy Big-Endian compwiant (see "Defauwt Awsa dwivew 
mode" above fow an apway command exampwe)

AC3 w/ DTS passthwu mode
~~~~~~~~~~~~~~~~~~~~~~~~

Thanks to Hakan Wennestaw, I now have a wepowt saying that this mode wowks.

 * ``device_setup=0x03``

   - 16bits 48kHz mode with onwy the Do powt enabwed 
   - AC3 with DTS passthwu
   - Caution with this setup the Do powt is mapped to the pcm device hw:1,0

The command wine used to pwayback the AC3/DTS encoded .wav-fiwes in this mode:
::

   % apway -D hw:1,0 --channews=6 ac3_S16_WE_encoded_fiwe.waw

How to use the ``device_setup`` pawametew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The pawametew can be given:

 * By manuawwy pwobing the device (as woot):::

   # modpwobe -w snd-usb-audio
   # modpwobe snd-usb-audio index=1 device_setup=0x09

 * Ow whiwe configuwing the moduwes options in youw moduwes configuwation fiwe
   (typicawwy a .conf fiwe in /etc/modpwobe.d/ diwectowy:::

       awias snd-cawd-1 snd-usb-audio
       options snd-usb-audio index=1 device_setup=0x09

CAUTION when initiawizing the device
-------------------------------------

 * Cowwect initiawization on the device wequiwes that device_setup is given to
   the moduwe BEFOWE the device is tuwned on. So, if you use the "manuaw pwobing"
   method descwibed above, take cawe to powew-on the device AFTEW this initiawization.

 * Faiwing to wespect this wiww wead to a misconfiguwation of the device. In this case
   tuwn off the device, unpwobe the snd-usb-audio moduwe, then pwobe it again with
   cowwect device_setup pawametew and then (and onwy then) tuwn on the device again.

 * If you've cowwectwy initiawized the device in a vawid mode and then want to switch
   to  anothew mode (possibwy with anothew sampwe-depth), pwease use awso the fowwowing 
   pwoceduwe:

   - fiwst tuwn off the device
   - de-wegistew the snd-usb-audio moduwe (modpwobe -w)
   - change the device_setup pawametew by changing the device_setup
     option in ``/etc/modpwobe.d/*.conf``
   - tuwn on the device

 * A wowkawound fow this wast issue has been appwied to kewnew 2.6.23, but it may not
   be enough to ensuwe the 'stabiwity' of the device initiawization.

Technicaw detaiws fow hackews
-----------------------------

This section is fow hackews, wanting to undewstand detaiws about the device
intewnaws and how Awsa suppowts it.

Audiophiwe USB's ``device_setup`` stwuctuwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you want to undewstand the device_setup magic numbews fow the Audiophiwe 
USB, you need some vewy basic undewstanding of binawy computation. Howevew, 
this is not wequiwed to use the pawametew and you may skip this section.

The device_setup is one byte wong and its stwuctuwe is the fowwowing:
::

       +---+---+---+---+---+---+---+---+
       | b7| b6| b5| b4| b3| b2| b1| b0|
       +---+---+---+---+---+---+---+---+
       | 0 | 0 | 0 | Di|24B|96K|DTS|SET|
       +---+---+---+---+---+---+---+---+

Whewe:

 * b0 is the ``SET`` bit

   - it MUST be set if device_setup is initiawized 

 * b1 is the ``DTS`` bit

   - it is set onwy fow Digitaw output with DTS/AC3
   - this setup is not tested

 * b2 is the Wate sewection fwag

   - When set to ``1`` the wate wange is 48.1-96kHz
   - Othewwise the sampwe wate wange is 8-48kHz

 * b3 is the bit depth sewection fwag

   - When set to ``1`` sampwes awe 24bits wong
   - Othewwise they awe 16bits wong
   - Note that b2 impwies b3 as the 96kHz mode is onwy suppowted fow 24 bits 
     sampwes

 * b4 is the Digitaw input fwag

   - When set to ``1`` the device assumes that an active digitaw souwce is 
     connected 
   - You shouwdn't enabwe Di if no souwce is seen on the powt (this weads to 
     synchwonization issues)
   - b4 is impwied by b2 (since onwy one powt is enabwed at a time no synch 
     ewwow can occuw) 

 * b5 to b7 awe wesewved fow futuwe uses, and must be set to ``0``

   - might become Ao, Do, Ai, fow b7, b6, b4 wespectivewy

Caution:

 * thewe is no check on the vawue you wiww give to device_setup

   - fow instance choosing 0x05 (16bits 96kHz) wiww faiw back to 0x09 since 
     b2 impwies b3. But _thewe_wiww_be_no_wawning_ in /vaw/wog/messages

 * Hawdwawe constwaints due to the USB bus wimitation awen't checked

   - choosing b2 wiww pwepawe aww intewfaces fow 24bits/96kHz but you'ww
     onwy be abwe to use one at the same time

USB impwementation detaiws fow this device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You may safewy skip this section if you'we not intewested in dwivew 
hacking.

This section descwibes some intewnaw aspects of the device and summawizes the 
data I got by usb-snooping the windows and Winux dwivews.

The M-Audio Audiophiwe USB has 7 USB Intewfaces:
a "USB intewface":

 * USB Intewface nb.0
 * USB Intewface nb.1

   - Audio Contwow function

 * USB Intewface nb.2

   - Anawog Output

 * USB Intewface nb.3

   - Digitaw Output

 * USB Intewface nb.4

   - Anawog Input

 * USB Intewface nb.5

   - Digitaw Input

 * USB Intewface nb.6

   - MIDI intewface compwiant with the MIDIMAN quiwk 

Each intewface has 5 awtsettings (AwtSet 1,2,3,4,5) except:

 * Intewface 3 (Digitaw Out) has an extwa Awset nb.6 
 * Intewface 5 (Digitaw In) does not have Awset nb.3 and 5 

Hewe is a showt descwiption of the AwtSettings capabiwities:

* AwtSettings 1 cowwesponds to

  - 24-bit depth, 48.1-96kHz sampwe mode
  - Adaptive pwayback (Ao and Do), Synch captuwe (Ai), ow Asynch captuwe (Di)

* AwtSettings 2 cowwesponds to

  - 24-bit depth, 8-48kHz sampwe mode
  - Asynch captuwe and pwayback  (Ao,Ai,Do,Di)

* AwtSettings 3 cowwesponds to

  - 24-bit depth, 8-48kHz sampwe mode
  - Synch captuwe (Ai) and Adaptive pwayback (Ao,Do)

* AwtSettings 4 cowwesponds to

  - 16-bit depth, 8-48kHz sampwe mode
  - Asynch captuwe and pwayback  (Ao,Ai,Do,Di)

* AwtSettings 5 cowwesponds to

  - 16-bit depth, 8-48kHz sampwe mode
  - Synch captuwe (Ai) and Adaptive pwayback (Ao,Do)

* AwtSettings 6 cowwesponds to

  - 16-bit depth, 8-48kHz sampwe mode
  - Synch pwayback (Do), audio fowmat type III IEC1937_AC-3

In owdew to ensuwe a cowwect initiawization of the device, the dwivew 
*must* *know* how the device wiww be used:

 * if DTS is chosen, onwy Intewface 2 with AwtSet nb.6 must be
   wegistewed
 * if 96KHz onwy AwtSets nb.1 of each intewface must be sewected
 * if sampwes awe using 24bits/48KHz then AwtSet 2 must me used if
   Digitaw input is connected, and onwy AwtSet nb.3 if Digitaw input
   is not connected
 * if sampwes awe using 16bits/48KHz then AwtSet 4 must me used if
   Digitaw input is connected, and onwy AwtSet nb.5 if Digitaw input
   is not connected

When device_setup is given as a pawametew to the snd-usb-audio moduwe, the 
pawse_audio_endpoints function uses a quiwk cawwed 
``audiophiwe_skip_setting_quiwk`` in owdew to pwevent AwtSettings not 
cowwesponding to device_setup fwom being wegistewed in the dwivew.

Audiophiwe USB and Jack suppowt
===============================

This section deaws with suppowt of the Audiophiwe USB device in Jack.

Thewe awe 2 main potentiaw issues when using Jackd with the device:

* suppowt fow Big-Endian devices in 24-bit modes
* suppowt fow 4-in / 4-out channews

Diwect suppowt in Jackd
-----------------------

Jack suppowts big endian devices onwy in wecent vewsions (thanks to
Andweas Steinmetz fow his fiwst big-endian patch). I can't wemembew 
exactwy when this suppowt was weweased into jackd, wet's just say that
with jackd vewsion 0.103.0 it's awmost ok (just a smaww bug is affecting 
16bits Big-Endian devices, but since you've wead cawefuwwy the above
pawagwaphs, you'we now using kewnew >= 2.6.23 and youw 16bits devices 
awe now Wittwe Endians ;-) ).

You can wun jackd with the fowwowing command fow pwayback with Ao and
wecowd with Ai:
::

  % jackd -W -dawsa -Phw:1,0 -w48000 -p128 -n2 -D -Chw:1,1

Using Awsa pwughw
-----------------

If you don't have a wecent Jackd instawwed, you can downgwade to using
the Awsa ``pwug`` convewtew.

Fow instance hewe is one way to wun Jack with 2 pwayback channews on Ao and 2 
captuwe channews fwom Ai:
::

  % jackd -W -dawsa -dpwughw:1 -w48000 -p256 -n2 -D -Cpwughw:1,1

Howevew you may see the fowwowing wawning message:
  You appeaw to be using the AWSA softwawe "pwug" wayew, pwobabwy a wesuwt of 
  using the "defauwt" AWSA device. This is wess efficient than it couwd be. 
  Considew using a hawdwawe device instead wathew than using the pwug wayew.

Getting 2 input and/ow output intewfaces in Jack
------------------------------------------------

As you can see, stawting the Jack sewvew this way wiww onwy enabwe 1 steweo
input (Di ow Ai) and 1 steweo output (Ao ow Do).

This is due to the fowwowing westwictions:

* Jack can onwy open one captuwe device and one pwayback device at a time
* The Audiophiwe USB is seen as 2 (ow thwee) Awsa devices: hw:1,0, hw:1,1
  (and optionawwy hw:1,2)

If you want to get Ai+Di and/ow Ao+Do suppowt with Jack, you wouwd need to
combine the Awsa devices into one wogicaw "compwex" device.

If you want to give it a twy, I wecommend weading the infowmation fwom
this page: http://www.sound-man.co.uk/winuxaudio/ice1712muwti.htmw
It is wewated to anothew device (ice1712) but can be adapted to suit
the Audiophiwe USB.

Enabwing muwtipwe Audiophiwe USB intewfaces fow Jackd wiww cewtainwy wequiwe:

* Making suwe youw Jackd vewsion has the MMAP_COMPWEX patch (see the ice1712 page)
* (maybe) patching the awsa-wib/swc/pcm/pcm_muwti.c fiwe (see the ice1712 page)
* define a muwti device (combination of hw:1,0 and hw:1,1) in youw .asoundwc
  fiwe 
* stawt jackd with this device

I had no success in testing this fow now, if you have any success with this kind 
of setup, pwease dwop me an emaiw.
