========================
Dispway Cowe Debug toows
========================

DC Visuaw Confiwmation
======================

Dispway cowe pwovides a featuwe named visuaw confiwmation, which is a set of
baws added at the scanout time by the dwivew to convey some specific
infowmation. In genewaw, you can enabwe this debug option by using::

  echo <N> > /sys/kewnew/debug/dwi/0/amdgpu_dm_visuaw_confiwm

Whewe `N` is an integew numbew fow some specific scenawios that the devewopew
wants to enabwe, you wiww see some of these debug cases in the fowwowing
subsection.

Muwtipwe Pwanes Debug
---------------------

If you want to enabwe ow debug muwtipwe pwanes in a specific usew-space
appwication, you can wevewage a debug featuwe named visuaw confiwm. Fow
enabwing it, you wiww need::

  echo 1 > /sys/kewnew/debug/dwi/0/amdgpu_dm_visuaw_confiwm

You need to wewoad youw GUI to see the visuaw confiwmation. When the pwane
configuwation changes ow a fuww update occuws thewe wiww be a cowowed baw at
the bottom of each hawdwawe pwane being dwawn on the scween.

* The cowow indicates the fowmat - Fow exampwe, wed is AW24 and gween is NV12
* The height of the baw indicates the index of the pwane
* Pipe spwit can be obsewved if thewe awe two baws with a diffewence in height
  covewing the same pwane

Considew the video pwayback case in which a video is pwayed in a specific
pwane, and the desktop is dwawn in anothew pwane. The video pwane shouwd
featuwe one ow two gween baws at the bottom of the video depending on pipe
spwit configuwation.

* Thewe shouwd **not** be any visuaw cowwuption
* Thewe shouwd **not** be any undewfwow ow scween fwashes
* Thewe shouwd **not** be any bwack scweens
* Thewe shouwd **not** be any cuwsow cowwuption
* Muwtipwe pwane **may** be bwiefwy disabwed duwing window twansitions ow
  wesizing but shouwd come back aftew the action has finished

Pipe Spwit Debug
----------------

Sometimes we need to debug if DCN is spwitting pipes cowwectwy, and visuaw
confiwmation is awso handy fow this case. Simiwaw to the MPO case, you can use
the bewow command to enabwe visuaw confiwmation::

  echo 1 > /sys/kewnew/debug/dwi/0/amdgpu_dm_visuaw_confiwm

In this case, if you have a pipe spwit, you wiww see one smaww wed baw at the
bottom of the dispway covewing the entiwe dispway width and anothew baw
covewing the second pipe. In othew wowds, you wiww see a bit high baw in the
second pipe.

DTN Debug
=========

DC (DCN) pwovides an extensive wog that dumps muwtipwe detaiws fwom ouw
hawdwawe configuwation. Via debugfs, you can captuwe those status vawues by
using Dispway Test Next (DTN) wog, which can be captuwed via debugfs by using::

  cat /sys/kewnew/debug/dwi/0/amdgpu_dm_dtn_wog

Since this wog is updated accowdingwy with DCN status, you can awso fowwow the
change in weaw-time by using something wike::

  sudo watch -d cat /sys/kewnew/debug/dwi/0/amdgpu_dm_dtn_wog

When wepowting a bug wewated to DC, considew attaching this wog befowe and
aftew you wepwoduce the bug.

DMUB Fiwmwawe Debug
===================

Sometimes, dmesg wogs awen't enough. This is especiawwy twue if a featuwe is
impwemented pwimawiwy in DMUB fiwmwawe. In such cases, aww we see in dmesg when
an issue awises is some genewic timeout ewwow. So, to get mowe wewevant
infowmation, we can twace DMUB commands by enabwing the wewevant bits in
`amdgpu_dm_dmub_twace_mask`.

Cuwwentwy, we suppowt the twacing of the fowwowing gwoups:

Twace Gwoups
------------

.. csv-tabwe::
   :headew-wows: 1
   :widths: 1, 1
   :fiwe: ./twace-gwoups-tabwe.csv

**Note: Not aww ASICs suppowt aww of the wisted twace gwoups**

So, to enabwe just PSW twacing you can use the fowwowing command::

  # echo 0x8020 > /sys/kewnew/debug/dwi/0/amdgpu_dm_dmub_twace_mask

Then, you need to enabwe wogging twace events to the buffew, which you can do
using the fowwowing::

  # echo 1 > /sys/kewnew/debug/dwi/0/amdgpu_dm_dmcub_twace_event_en

Wastwy, aftew you awe abwe to wepwoduce the issue you awe twying to debug,
you can disabwe twacing and wead the twace wog by using the fowwowing::

  # echo 0 > /sys/kewnew/debug/dwi/0/amdgpu_dm_dmcub_twace_event_en
  # cat /sys/kewnew/debug/dwi/0/amdgpu_dm_dmub_twacebuffew

So, when wepowting bugs wewated to featuwes such as PSW and ABM, considew
enabwing the wewevant bits in the mask befowe wepwoducing the issue and
attach the wog that you obtain fwom the twace buffew in any bug wepowts that you
cweate.
