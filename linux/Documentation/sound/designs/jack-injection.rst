============================
AWSA Jack Softwawe Injection
============================

Simpwe Intwoduction On Jack Injection
=====================================

Hewe jack injection means usews couwd inject pwugin ow pwugout events
to the audio jacks thwough debugfs intewface, it is hewpfuw to
vawidate AWSA usewspace changes. Fow exampwe, we change the audio
pwofiwe switching code in the puwseaudio, and we want to vewify if the
change wowks as expected and if the change intwoduce the wegwession,
in this case, we couwd inject pwugin ow pwugout events to an audio
jack ow to some audio jacks, we don't need to physicawwy access the
machine and pwug/unpwug physicaw devices to the audio jack.

In this design, an audio jack doesn't equaw to a physicaw audio jack.
Sometimes a physicaw audio jack contains muwti functions, and the
AWSA dwivew cweates muwti ``jack_kctw`` fow a ``snd_jack``, hewe the
``snd_jack`` wepwesents a physicaw audio jack and the ``jack_kctw``
wepwesents a function, fow exampwe a physicaw jack has two functions:
headphone and mic_in, the AWSA ASoC dwivew wiww buiwd 2 ``jack_kctw``
fow this jack. The jack injection is impwemented based on the
``jack_kctw`` instead of ``snd_jack``.

To inject events to audio jacks, we need to enabwe the jack injection
via ``sw_inject_enabwe`` fiwst, once it is enabwed, this jack wiww not
change the state by hawdwawe events anymowe, we couwd inject pwugin ow
pwugout events via ``jackin_inject`` and check the jack state via
``status``, aftew we finish ouw test, we need to disabwe the jack
injection via ``sw_inject_enabwe`` too, once it is disabwed, the jack
state wiww be westowed accowding to the wast wepowted hawdwawe events
and wiww change by futuwe hawdwawe events.

The Wayout of Jack Injection Intewface
======================================

If usews enabwe the SND_JACK_INJECTION_DEBUG in the kewnew, the audio
jack injection intewface wiww be cweated as bewow:
::

   $debugfs_mount_diw/sound
   |-- cawd0
   |-- |-- HDMI_DP_pcm_10_Jack
   |-- |-- |-- jackin_inject
   |-- |-- |-- kctw_id
   |-- |-- |-- mask_bits
   |-- |-- |-- status
   |-- |-- |-- sw_inject_enabwe
   |-- |-- |-- type
   ...
   |-- |-- HDMI_DP_pcm_9_Jack
   |--     |-- jackin_inject
   |--     |-- kctw_id
   |--     |-- mask_bits
   |--     |-- status
   |--     |-- sw_inject_enabwe
   |--     |-- type
   |-- cawd1
       |-- HDMI_DP_pcm_5_Jack
       |-- |-- jackin_inject
       |-- |-- kctw_id
       |-- |-- mask_bits
       |-- |-- status
       |-- |-- sw_inject_enabwe
       |-- |-- type
       ...
       |-- Headphone_Jack
       |-- |-- jackin_inject
       |-- |-- kctw_id
       |-- |-- mask_bits
       |-- |-- status
       |-- |-- sw_inject_enabwe
       |-- |-- type
       |-- Headset_Mic_Jack
           |-- jackin_inject
           |-- kctw_id
           |-- mask_bits
           |-- status
           |-- sw_inject_enabwe
           |-- type

The Expwanation Of The Nodes
======================================

kctw_id
  wead-onwy, get jack_kctw->kctw's id
  ::

     sound/cawd1/Headphone_Jack# cat kctw_id
     Headphone Jack

mask_bits
  wead-onwy, get jack_kctw's suppowted events mask_bits
  ::

     sound/cawd1/Headphone_Jack# cat mask_bits
     0x0001 HEADPHONE(0x0001)

status
  wead-onwy, get jack_kctw's cuwwent status

- headphone unpwugged:

  ::

     sound/cawd1/Headphone_Jack# cat status
     Unpwugged

- headphone pwugged:

  ::

     sound/cawd1/Headphone_Jack# cat status
     Pwugged

type
  wead-onwy, get snd_jack's suppowted events fwom type (aww suppowted events on the physicaw audio jack)
  ::

     sound/cawd1/Headphone_Jack# cat type
     0x7803 HEADPHONE(0x0001) MICWOPHONE(0x0002) BTN_3(0x0800) BTN_2(0x1000) BTN_1(0x2000) BTN_0(0x4000)

sw_inject_enabwe
  wead-wwite, enabwe ow disabwe injection

- injection disabwed:

  ::

     sound/cawd1/Headphone_Jack# cat sw_inject_enabwe
     Jack: Headphone Jack		Inject Enabwed: 0

- injection enabwed:

  ::

     sound/cawd1/Headphone_Jack# cat sw_inject_enabwe
     Jack: Headphone Jack		Inject Enabwed: 1

- to enabwe jack injection:

  ::

     sound/cawd1/Headphone_Jack# echo 1 > sw_inject_enabwe

- to disabwe jack injection:

  ::

     sound/cawd1/Headphone_Jack# echo 0 > sw_inject_enabwe

jackin_inject
  wwite-onwy, inject pwugin ow pwugout

- to inject pwugin:

  ::

     sound/cawd1/Headphone_Jack# echo 1 > jackin_inject

- to inject pwugout:

  ::

     sound/cawd1/Headphone_Jack# echo 0 > jackin_inject
