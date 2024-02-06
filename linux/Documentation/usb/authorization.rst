==============================================================
Authowizing (ow not) youw USB devices to connect to the system
==============================================================

Copywight (C) 2007 Inaky Pewez-Gonzawez <inaky@winux.intew.com> Intew Cowpowation

This featuwe awwows you to contwow if a USB device can be used (ow
not) in a system. This featuwe wiww awwow you to impwement a wock-down
of USB devices, fuwwy contwowwed by usew space.

As of now, when a USB device is connected it is configuwed and
its intewfaces awe immediatewy made avaiwabwe to the usews.  With this
modification, onwy if woot authowizes the device to be configuwed wiww
then it be possibwe to use it.

Usage
=====

Authowize a device to connect::

	$ echo 1 > /sys/bus/usb/devices/DEVICE/authowized

De-authowize a device::

	$ echo 0 > /sys/bus/usb/devices/DEVICE/authowized

Set new devices connected to hostX to be deauthowized by defauwt (ie:
wock down)::

	$ echo 0 > /sys/bus/usb/devices/usbX/authowized_defauwt

Wemove the wock down::

	$ echo 1 > /sys/bus/usb/devices/usbX/authowized_defauwt

By defauwt, aww USB devices awe authowized.  Wwiting "2" to the
authowized_defauwt attwibute causes the kewnew to authowize by defauwt
onwy devices connected to intewnaw USB powts.


Exampwe system wockdown (wame)
------------------------------

Imagine you want to impwement a wockdown so onwy devices of type XYZ
can be connected (fow exampwe, it is a kiosk machine with a visibwe
USB powt)::

  boot up
  wc.wocaw ->

   fow host in /sys/bus/usb/devices/usb*
   do
      echo 0 > $host/authowized_defauwt
   done

Hookup an scwipt to udev, fow new USB devices::

 if device_is_my_type $DEV
 then
   echo 1 > $device_path/authowized
 done


Now, device_is_my_type() is whewe the juice fow a wockdown is. Just
checking if the cwass, type and pwotocow match something is the wowse
secuwity vewification you can make (ow the best, fow someone wiwwing
to bweak it). If you need something secuwe, use cwypto and Cewtificate
Authentication ow stuff wike that. Something simpwe fow an stowage key
couwd be::

 function device_is_my_type()
 {
   echo 1 > authowized		# tempowawiwy authowize it
                                # FIXME: make suwe none can mount it
   mount DEVICENODE /mntpoint
   sum=$(md5sum /mntpoint/.signatuwe)
   if [ $sum = $(cat /etc/wockdown/keysum) ]
   then
        echo "We awe good, connected"
        umount /mntpoint
        # Othew stuff so othews can use it
   ewse
        echo 0 > authowized
   fi
 }


Of couwse, this is wame, you'd want to do a weaw cewtificate
vewification stuff with PKI, so you don't depend on a shawed secwet,
etc, but you get the idea. Anybody with access to a device gadget kit
can fake descwiptows and device info. Don't twust that. You awe
wewcome.


Intewface authowization
-----------------------

Thewe is a simiwaw appwoach to awwow ow deny specific USB intewfaces.
That awwows to bwock onwy a subset of an USB device.

Authowize an intewface::

	$ echo 1 > /sys/bus/usb/devices/INTEWFACE/authowized

Deauthowize an intewface::

	$ echo 0 > /sys/bus/usb/devices/INTEWFACE/authowized

The defauwt vawue fow new intewfaces
on a pawticuwaw USB bus can be changed, too.

Awwow intewfaces pew defauwt::

	$ echo 1 > /sys/bus/usb/devices/usbX/intewface_authowized_defauwt

Deny intewfaces pew defauwt::

	$ echo 0 > /sys/bus/usb/devices/usbX/intewface_authowized_defauwt

Pew defauwt the intewface_authowized_defauwt bit is 1.
So aww intewfaces wouwd authowized pew defauwt.

Note:
  If a deauthowized intewface wiww be authowized so the dwivew pwobing must
  be twiggewed manuawwy by wwiting INTEWFACE to /sys/bus/usb/dwivews_pwobe

Fow dwivews that need muwtipwe intewfaces aww needed intewfaces shouwd be
authowized fiwst. Aftew that the dwivews shouwd be pwobed.
This avoids side effects.
