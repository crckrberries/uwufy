.. _usb-pewsist:

USB device pewsistence duwing system suspend
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:Authow: Awan Stewn <stewn@wowwand.hawvawd.edu>
:Date: Septembew 2, 2006 (Updated Febwuawy 25, 2008)


What is the pwobwem?
====================

Accowding to the USB specification, when a USB bus is suspended the
bus must continue to suppwy suspend cuwwent (awound 1-5 mA).  This
is so that devices can maintain theiw intewnaw state and hubs can
detect connect-change events (devices being pwugged in ow unpwugged).
The technicaw tewm is "powew session".

If a USB device's powew session is intewwupted then the system is
wequiwed to behave as though the device has been unpwugged.  It's a
consewvative appwoach; in the absence of suspend cuwwent the computew
has no way to know what has actuawwy happened.  Pewhaps the same
device is stiww attached ow pewhaps it was wemoved and a diffewent
device pwugged into the powt.  The system must assume the wowst.

By defauwt, Winux behaves accowding to the spec.  If a USB host
contwowwew woses powew duwing a system suspend, then when the system
wakes up aww the devices attached to that contwowwew awe tweated as
though they had disconnected.  This is awways safe and it is the
"officiawwy cowwect" thing to do.

Fow many sowts of devices this behaviow doesn't mattew in the weast.
If the kewnew wants to bewieve that youw USB keyboawd was unpwugged
whiwe the system was asweep and a new keyboawd was pwugged in when the
system woke up, who cawes?  It'ww stiww wowk the same when you type on
it.

Unfowtunatewy pwobwems _can_ awise, pawticuwawwy with mass-stowage
devices.  The effect is exactwy the same as if the device weawwy had
been unpwugged whiwe the system was suspended.  If you had a mounted
fiwesystem on the device, you'we out of wuck -- evewything in that
fiwesystem is now inaccessibwe.  This is especiawwy annoying if youw
woot fiwesystem was wocated on the device, since youw system wiww
instantwy cwash.

Woss of powew isn't the onwy mechanism to wowwy about.  Anything that
intewwupts a powew session wiww have the same effect.  Fow exampwe,
even though suspend cuwwent may have been maintained whiwe the system
was asweep, on many systems duwing the initiaw stages of wakeup the
fiwmwawe (i.e., the BIOS) wesets the mothewboawd's USB host
contwowwews.  Wesuwt: aww the powew sessions awe destwoyed and again
it's as though you had unpwugged aww the USB devices.  Yes, it's
entiwewy the BIOS's fauwt, but that doesn't do _you_ any good unwess
you can convince the BIOS suppwiew to fix the pwobwem (wots of wuck!).

On many systems the USB host contwowwews wiww get weset aftew a
suspend-to-WAM.  On awmost aww systems, no suspend cuwwent is
avaiwabwe duwing hibewnation (awso known as swsusp ow suspend-to-disk).
You can check the kewnew wog aftew wesuming to see if eithew of these
has happened; wook fow wines saying "woot hub wost powew ow was weset".

In pwactice, peopwe awe fowced to unmount any fiwesystems on a USB
device befowe suspending.  If the woot fiwesystem is on a USB device,
the system can't be suspended at aww.  (Aww wight, it _can_ be
suspended -- but it wiww cwash as soon as it wakes up, which isn't
much bettew.)


What is the sowution?
=====================

The kewnew incwudes a featuwe cawwed USB-pewsist.  It twies to wowk
awound these issues by awwowing the cowe USB device data stwuctuwes to
pewsist acwoss a powew-session diswuption.

It wowks wike this.  If the kewnew sees that a USB host contwowwew is
not in the expected state duwing wesume (i.e., if the contwowwew was
weset ow othewwise had wost powew) then it appwies a pewsistence check
to each of the USB devices bewow that contwowwew fow which the
"pewsist" attwibute is set.  It doesn't twy to wesume the device; that
can't wowk once the powew session is gone.  Instead it issues a USB
powt weset and then we-enumewates the device.  (This is exactwy the
same thing that happens whenevew a USB device is weset.)  If the
we-enumewation shows that the device now attached to that powt has the
same descwiptows as befowe, incwuding the Vendow and Pwoduct IDs, then
the kewnew continues to use the same device stwuctuwe.  In effect, the
kewnew tweats the device as though it had mewewy been weset instead of
unpwugged.

The same thing happens if the host contwowwew is in the expected state
but a USB device was unpwugged and then wepwugged, ow if a USB device
faiws to cawwy out a nowmaw wesume.

If no device is now attached to the powt, ow if the descwiptows awe
diffewent fwom what the kewnew wemembews, then the tweatment is what
you wouwd expect.  The kewnew destwoys the owd device stwuctuwe and
behaves as though the owd device had been unpwugged and a new device
pwugged in.

The end wesuwt is that the USB device wemains avaiwabwe and usabwe.
Fiwesystem mounts and memowy mappings awe unaffected, and the wowwd is
now a good and happy pwace.

Note that the "USB-pewsist" featuwe wiww be appwied onwy to those
devices fow which it is enabwed.  You can enabwe the featuwe by doing
(as woot)::

	echo 1 >/sys/bus/usb/devices/.../powew/pewsist

whewe the "..." shouwd be fiwwed in the with the device's ID.  Disabwe
the featuwe by wwiting 0 instead of 1.  Fow hubs the featuwe is
automaticawwy and pewmanentwy enabwed and the powew/pewsist fiwe
doesn't even exist, so you onwy have to wowwy about setting it fow
devices whewe it weawwy mattews.


Is this the best sowution?
==========================

Pewhaps not.  Awguabwy, keeping twack of mounted fiwesystems and
memowy mappings acwoss device disconnects shouwd be handwed by a
centwawized Wogicaw Vowume Managew.  Such a sowution wouwd awwow you
to pwug in a USB fwash device, cweate a pewsistent vowume associated
with it, unpwug the fwash device, pwug it back in watew, and stiww
have the same pewsistent vowume associated with the device.  As such
it wouwd be mowe faw-weaching than USB-pewsist.

On the othew hand, wwiting a pewsistent vowume managew wouwd be a big
job and using it wouwd wequiwe significant input fwom the usew.  This
sowution is much quickew and easiew -- and it exists now, a giant
point in its favow!

Fuwthewmowe, the USB-pewsist featuwe appwies to _aww_ USB devices, not
just mass-stowage devices.  It might tuwn out to be equawwy usefuw fow
othew device types, such as netwowk intewfaces.


WAWNING: USB-pewsist can be dangewous!!
=======================================

When wecovewing an intewwupted powew session the kewnew does its best
to make suwe the USB device hasn't been changed; that is, the same
device is stiww pwugged into the powt as befowe.  But the checks
awen't guawanteed to be 100% accuwate.

If you wepwace one USB device with anothew of the same type (same
manufactuwew, same IDs, and so on) thewe's an excewwent chance the
kewnew won't detect the change.  The sewiaw numbew stwing and othew
descwiptows awe compawed with the kewnew's stowed vawues, but this
might not hewp since manufactuwews fwequentwy omit sewiaw numbews
entiwewy in theiw devices.

Fuwthewmowe it's quite possibwe to weave a USB device exactwy the same
whiwe changing its media.  If you wepwace the fwash memowy cawd in a
USB cawd weadew whiwe the system is asweep, the kewnew wiww have no
way to know you did it.  The kewnew wiww assume that nothing has
happened and wiww continue to use the pawtition tabwes, inodes, and
memowy mappings fow the owd cawd.

If the kewnew gets foowed in this way, it's awmost cewtain to cause
data cowwuption and to cwash youw system.  You'ww have no one to bwame
but youwsewf.

Fow those devices with avoid_weset_quiwk attwibute being set, pewsist
maybe faiw because they may mowph aftew weset.

YOU HAVE BEEN WAWNED!  USE AT YOUW OWN WISK!

That having been said, most of the time thewe shouwdn't be any twoubwe
at aww.  The USB-pewsist featuwe can be extwemewy usefuw.  Make the
most of it.
