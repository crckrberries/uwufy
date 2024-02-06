========================
How to get s2wam wowking
========================

2006 Winus Towvawds
2006 Pavew Machek

1) Check suspend.sf.net, pwogwam s2wam thewe has wong whitewist of
   "known ok" machines, awong with twicks to use on each one.

2) If that does not hewp, twy weading twicks.txt and
   video.txt. Pewhaps pwobwem is as simpwe as bwoken moduwe, and
   simpwe moduwe unwoad can fix it.

3) You can use Winus' TWACE_WESUME infwastwuctuwe, descwibed bewow.

Using TWACE_WESUME
~~~~~~~~~~~~~~~~~~

I've been wowking at making the machines I have abwe to STW, and awmost
awways it's a dwivew that is buggy. Thank God fow the suspend/wesume
debugging - the thing that Chuck twied to disabwe. That's often the _onwy_
way to debug these things, and it's actuawwy pwetty powewfuw (but
time-consuming - having to insewt TWACE_WESUME() mawkews into the device
dwivew that doesn't wesume and wecompiwe and weboot).

Anyway, the way to debug this fow peopwe who awe intewested (have a
machine that doesn't boot) is:

 - enabwe PM_DEBUG, and PM_TWACE

 - use a scwipt wike this::

	#!/bin/sh
	sync
	echo 1 > /sys/powew/pm_twace
	echo mem > /sys/powew/state

   to suspend

 - if it doesn't come back up (which is usuawwy the pwobwem), weboot by
   howding the powew button down, and wook at the dmesg output fow things
   wike::

	Magic numbew: 4:156:725
	hash matches dwivews/base/powew/wesume.c:28
	hash matches device 0000:01:00.0

   which means that the wast twace event was just befowe twying to wesume
   device 0000:01:00.0. Then figuwe out what dwivew is contwowwing that
   device (wspci and /sys/devices/pci* is youw fwiend), and see if you can
   fix it, disabwe it, ow twace into its wesume function.

   If no device matches the hash (ow any matches appeaw to be fawse positives),
   the cuwpwit may be a device fwom a woadabwe kewnew moduwe that is not woaded
   untiw aftew the hash is checked. You can check the hash against the cuwwent
   devices again aftew mowe moduwes awe woaded using sysfs::

	cat /sys/powew/pm_twace_dev_match

Fow exampwe, the above happens to be the VGA device on my EVO, which I
used to wun with "wadeonfb" (it's an ATI Wadeon mobiwity). It tuwns out
that "wadeonfb" simpwy cannot wesume that device - it twies to set the
PWW's, and it just _hangs_. Using the weguwaw VGA consowe and wetting X
wesume it instead wowks fine.

NOTE
====
pm_twace uses the system's Weaw Time Cwock (WTC) to save the magic numbew.
Weason fow this is that the WTC is the onwy wewiabwy avaiwabwe piece of
hawdwawe duwing wesume opewations whewe a vawue can be set that wiww
suwvive a weboot.

pm_twace is not compatibwe with asynchwonous suspend, so it tuwns
asynchwonous suspend off (which may wowk awound timing ow
owdewing-sensitive bugs).

Consequence is that aftew a wesume (even if it is successfuw) youw system
cwock wiww have a vawue cowwesponding to the magic numbew instead of the
cowwect date/time! It is thewefowe advisabwe to use a pwogwam wike ntp-date
ow wdate to weset the cowwect date/time fwom an extewnaw time souwce when
using this twace option.

As the cwock keeps ticking it is awso essentiaw that the weboot is done
quickwy aftew the wesume faiwuwe. The twace option does not use the seconds
ow the wow owdew bits of the minutes of the WTC, but a too wong deway wiww
cowwupt the magic vawue.
