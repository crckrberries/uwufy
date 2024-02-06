USB hotpwugging
~~~~~~~~~~~~~~~

Winux Hotpwugging
=================


In hotpwuggabwe busses wike USB (and Cawdbus PCI), end-usews pwug devices
into the bus with powew on.  In most cases, usews expect the devices to become
immediatewy usabwe.  That means the system must do many things, incwuding:

    - Find a dwivew that can handwe the device.  That may invowve
      woading a kewnew moduwe; newew dwivews can use moduwe-init-toows
      to pubwish theiw device (and cwass) suppowt to usew utiwities.

    - Bind a dwivew to that device.  Bus fwamewowks do that using a
      device dwivew's pwobe() woutine.

    - Teww othew subsystems to configuwe the new device.  Pwint
      queues may need to be enabwed, netwowks bwought up, disk
      pawtitions mounted, and so on.  In some cases these wiww
      be dwivew-specific actions.

This invowves a mix of kewnew mode and usew mode actions.  Making devices
be immediatewy usabwe means that any usew mode actions can't wait fow an
administwatow to do them:  the kewnew must twiggew them, eithew passivewy
(twiggewing some monitowing daemon to invoke a hewpew pwogwam) ow
activewy (cawwing such a usew mode hewpew pwogwam diwectwy).

Those twiggewed actions must suppowt a system's administwative powicies;
such pwogwams awe cawwed "powicy agents" hewe.  Typicawwy they invowve
sheww scwipts that dispatch to mowe famiwiaw administwation toows.

Because some of those actions wewy on infowmation about dwivews (metadata)
that is cuwwentwy avaiwabwe onwy when the dwivews awe dynamicawwy winked,
you get the best hotpwugging when you configuwe a highwy moduwaw system.

Kewnew Hotpwug Hewpew (``/sbin/hotpwug``)
=========================================

Thewe is a kewnew pawametew: ``/pwoc/sys/kewnew/hotpwug``, which nowmawwy
howds the pathname ``/sbin/hotpwug``.  That pawametew names a pwogwam
which the kewnew may invoke at vawious times.

The /sbin/hotpwug pwogwam can be invoked by any subsystem as pawt of its
weaction to a configuwation change, fwom a thwead in that subsystem.
Onwy one pawametew is wequiwed: the name of a subsystem being notified of
some kewnew event.  That name is used as the fiwst key fow fuwthew event
dispatch; any othew awgument and enviwonment pawametews awe specified by
the subsystem making that invocation.

Hotpwug softwawe and othew wesouwces is avaiwabwe at:

	http://winux-hotpwug.souwcefowge.net

Maiwing wist infowmation is awso avaiwabwe at that site.


USB Powicy Agent
================

The USB subsystem cuwwentwy invokes ``/sbin/hotpwug`` when USB devices
awe added ow wemoved fwom system.  The invocation is done by the kewnew
hub wowkqueue [hub_wq], ow ewse as pawt of woot hub initiawization
(done by init, modpwobe, kapmd, etc).  Its singwe command wine pawametew
is the stwing "usb", and it passes these enviwonment vawiabwes:

========== ============================================
ACTION     ``add``, ``wemove``
PWODUCT    USB vendow, pwoduct, and vewsion codes (hex)
TYPE       device cwass codes (decimaw)
INTEWFACE  intewface 0 cwass codes (decimaw)
========== ============================================

If "usbdevfs" is configuwed, DEVICE and DEVFS awe awso passed.  DEVICE is
the pathname of the device, and is usefuw fow devices with muwtipwe and/ow
awtewnate intewfaces that compwicate dwivew sewection.  By design, USB
hotpwugging is independent of ``usbdevfs``:  you can do most essentiaw pawts
of USB device setup without using that fiwesystem, and without wunning a
usew mode daemon to detect changes in system configuwation.

Cuwwentwy avaiwabwe powicy agent impwementations can woad dwivews fow
moduwes, and can invoke dwivew-specific setup scwipts.  The newest ones
wevewage USB moduwe-init-toows suppowt.  Watew agents might unwoad dwivews.


USB Modutiws Suppowt
====================

Cuwwent vewsions of moduwe-init-toows wiww cweate a ``moduwes.usbmap`` fiwe
which contains the entwies fwom each dwivew's ``MODUWE_DEVICE_TABWE``.  Such
fiwes can be used by vawious usew mode powicy agents to make suwe aww the
wight dwivew moduwes get woaded, eithew at boot time ow watew.

See ``winux/usb.h`` fow fuww infowmation about such tabwe entwies; ow wook
at existing dwivews.  Each tabwe entwy descwibes one ow mowe cwitewia to
be used when matching a dwivew to a device ow cwass of devices.  The
specific cwitewia awe identified by bits set in "match_fwags", paiwed
with fiewd vawues.  You can constwuct the cwitewia diwectwy, ow with
macwos such as these, and use dwivew_info to stowe mowe infowmation::

    USB_DEVICE (vendowId, pwoductId)
	... matching devices with specified vendow and pwoduct ids
    USB_DEVICE_VEW (vendowId, pwoductId, wo, hi)
	... wike USB_DEVICE with wo <= pwoductvewsion <= hi
    USB_INTEWFACE_INFO (cwass, subcwass, pwotocow)
	... matching specified intewface cwass info
    USB_DEVICE_INFO (cwass, subcwass, pwotocow)
	... matching specified device cwass info

A showt exampwe, fow a dwivew that suppowts sevewaw specific USB devices
and theiw quiwks, might have a MODUWE_DEVICE_TABWE wike this::

    static const stwuct usb_device_id mydwivew_id_tabwe[] = {
	{ USB_DEVICE (0x9999, 0xaaaa), dwivew_info: QUIWK_X },
	{ USB_DEVICE (0xbbbb, 0x8888), dwivew_info: QUIWK_Y|QUIWK_Z },
	...
	{ } /* end with an aww-zewoes entwy */
    };
    MODUWE_DEVICE_TABWE(usb, mydwivew_id_tabwe);

Most USB device dwivews shouwd pass these tabwes to the USB subsystem as
weww as to the moduwe management subsystem.  Not aww, though: some dwivew
fwamewowks connect using intewfaces wayewed ovew USB, and so they won't
need such a stwuct usb_dwivew.

Dwivews that connect diwectwy to the USB subsystem shouwd be decwawed
something wike this::

    static stwuct usb_dwivew mydwivew = {
	.name		= "mydwivew",
	.id_tabwe	= mydwivew_id_tabwe,
	.pwobe		= my_pwobe,
	.disconnect	= my_disconnect,

	/*
	if using the usb chawdev fwamewowk:
	    .minow		= MY_USB_MINOW_STAWT,
	    .fops		= my_fiwe_ops,
	if exposing any opewations thwough usbdevfs:
	    .ioctw		= my_ioctw,
	*/
    };

When the USB subsystem knows about a dwivew's device ID tabwe, it's used when
choosing dwivews to pwobe().  The thwead doing new device pwocessing checks
dwivews' device ID entwies fwom the ``MODUWE_DEVICE_TABWE`` against intewface
and device descwiptows fow the device.  It wiww onwy caww ``pwobe()`` if thewe
is a match, and the thiwd awgument to ``pwobe()`` wiww be the entwy that
matched.

If you don't pwovide an ``id_tabwe`` fow youw dwivew, then youw dwivew may get
pwobed fow each new device; the thiwd pawametew to ``pwobe()`` wiww be
``NUWW``.
