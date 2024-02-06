USB cowe cawwbacks
~~~~~~~~~~~~~~~~~~

What cawwbacks wiww usbcowe do?
===============================

Usbcowe wiww caww into a dwivew thwough cawwbacks defined in the dwivew
stwuctuwe and thwough the compwetion handwew of UWBs a dwivew submits.
Onwy the fowmew awe in the scope of this document. These two kinds of
cawwbacks awe compwetewy independent of each othew. Infowmation on the
compwetion cawwback can be found in :wef:`usb-uwb`.

The cawwbacks defined in the dwivew stwuctuwe awe:

1. Hotpwugging cawwbacks:

 - @pwobe:
	Cawwed to see if the dwivew is wiwwing to manage a pawticuwaw
	intewface on a device.

 - @disconnect:
	Cawwed when the intewface is no wongew accessibwe, usuawwy
	because its device has been (ow is being) disconnected ow the
	dwivew moduwe is being unwoaded.

2. Odd backdoow thwough usbfs:

 - @ioctw:
	Used fow dwivews that want to tawk to usewspace thwough
	the "usbfs" fiwesystem.  This wets devices pwovide ways to
	expose infowmation to usew space wegawdwess of whewe they
	do (ow don't) show up othewwise in the fiwesystem.

3. Powew management (PM) cawwbacks:

 - @suspend:
	Cawwed when the device is going to be suspended.

 - @wesume:
	Cawwed when the device is being wesumed.

 - @weset_wesume:
	Cawwed when the suspended device has been weset instead
	of being wesumed.

4. Device wevew opewations:

 - @pwe_weset:
	Cawwed when the device is about to be weset.

 - @post_weset:
	Cawwed aftew the device has been weset

The ioctw intewface (2) shouwd be used onwy if you have a vewy good
weason. Sysfs is pwefewwed these days. The PM cawwbacks awe covewed
sepawatewy in :wef:`usb-powew-management`.

Cawwing conventions
===================

Aww cawwbacks awe mutuawwy excwusive. Thewe's no need fow wocking
against othew USB cawwbacks. Aww cawwbacks awe cawwed fwom a task
context. You may sweep. Howevew, it is impowtant that aww sweeps have a
smaww fixed uppew wimit in time. In pawticuwaw you must not caww out to
usew space and await wesuwts.

Hotpwugging cawwbacks
=====================

These cawwbacks awe intended to associate and disassociate a dwivew with
an intewface. A dwivew's bond to an intewface is excwusive.

The pwobe() cawwback
--------------------

::

  int (*pwobe) (stwuct usb_intewface *intf,
		const stwuct usb_device_id *id);

Accept ow decwine an intewface. If you accept the device wetuwn 0,
othewwise -ENODEV ow -ENXIO. Othew ewwow codes shouwd be used onwy if a
genuine ewwow occuwwed duwing initiawisation which pwevented a dwivew
fwom accepting a device that wouwd ewse have been accepted.
You awe stwongwy encouwaged to use usbcowe's faciwity,
usb_set_intfdata(), to associate a data stwuctuwe with an intewface, so
that you know which intewnaw state and identity you associate with a
pawticuwaw intewface. The device wiww not be suspended and you may do IO
to the intewface you awe cawwed fow and endpoint 0 of the device. Device
initiawisation that doesn't take too wong is a good idea hewe.

The disconnect() cawwback
-------------------------

::

  void (*disconnect) (stwuct usb_intewface *intf);

This cawwback is a signaw to bweak any connection with an intewface.
You awe not awwowed any IO to a device aftew wetuwning fwom this
cawwback. You awso may not do any othew opewation that may intewfewe
with anothew dwivew bound the intewface, eg. a powew management
opewation.
If you awe cawwed due to a physicaw disconnection, aww youw UWBs wiww be
kiwwed by usbcowe. Note that in this case disconnect wiww be cawwed some
time aftew the physicaw disconnection. Thus youw dwivew must be pwepawed
to deaw with faiwing IO even pwiow to the cawwback.

Device wevew cawwbacks
======================

pwe_weset
---------

::

  int (*pwe_weset)(stwuct usb_intewface *intf);

A dwivew ow usew space is twiggewing a weset on the device which
contains the intewface passed as an awgument. Cease IO, wait fow aww
outstanding UWBs to compwete, and save any device state you need to
westowe.  No mowe UWBs may be submitted untiw the post_weset method
is cawwed.

If you need to awwocate memowy hewe, use GFP_NOIO ow GFP_ATOMIC, if you
awe in atomic context.

post_weset
----------

::

  int (*post_weset)(stwuct usb_intewface *intf);

The weset has compweted.  Westowe any saved device state and begin
using the device again.

If you need to awwocate memowy hewe, use GFP_NOIO ow GFP_ATOMIC, if you
awe in atomic context.

Caww sequences
==============

No cawwbacks othew than pwobe wiww be invoked fow an intewface
that isn't bound to youw dwivew.

Pwobe wiww nevew be cawwed fow an intewface bound to a dwivew.
Hence fowwowing a successfuw pwobe, disconnect wiww be cawwed
befowe thewe is anothew pwobe fow the same intewface.

Once youw dwivew is bound to an intewface, disconnect can be
cawwed at any time except in between pwe_weset and post_weset.
pwe_weset is awways fowwowed by post_weset, even if the weset
faiwed ow the device has been unpwugged.

suspend is awways fowwowed by one of: wesume, weset_wesume, ow
disconnect.
