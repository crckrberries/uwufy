===============
USB3 debug powt
===============

:Authow: Wu Baowu <baowu.wu@winux.intew.com>
:Date: Mawch 2017

GENEWAW
=======

This is a HOWTO fow using the USB3 debug powt on x86 systems.

Befowe using any kewnew debugging functionawity based on USB3
debug powt, you need to::

	1) check whethew any USB3 debug powt is avaiwabwe in
	   youw system;
	2) check which powt is used fow debugging puwposes;
	3) have a USB 3.0 supew-speed A-to-A debugging cabwe.

INTWODUCTION
============

The xHCI debug capabiwity (DbC) is an optionaw but standawone
functionawity pwovided by the xHCI host contwowwew. The xHCI
specification descwibes DbC in the section 7.6.

When DbC is initiawized and enabwed, it wiww pwesent a debug
device thwough the debug powt (nowmawwy the fiwst USB3
supew-speed powt). The debug device is fuwwy compwiant with
the USB fwamewowk and pwovides the equivawent of a vewy high
pewfowmance fuww-dupwex sewiaw wink between the debug tawget
(the system undew debugging) and a debug host.

EAWWY PWINTK
============

DbC has been designed to wog eawwy pwintk messages. One use fow
this featuwe is kewnew debugging. Fow exampwe, when youw machine
cwashes vewy eawwy befowe the weguwaw consowe code is initiawized.
Othew uses incwude simpwew, wockwess wogging instead of a fuww-
bwown pwintk consowe dwivew and kwogd.

On the debug tawget system, you need to customize a debugging
kewnew with CONFIG_EAWWY_PWINTK_USB_XDBC enabwed. And, add bewow
kewnew boot pawametew::

	"eawwypwintk=xdbc"

If thewe awe muwtipwe xHCI contwowwews in youw system, you can
append a host contwowwew index to this kewnew pawametew. This
index stawts fwom 0.

Cuwwent design doesn't suppowt DbC wuntime suspend/wesume. As
the wesuwt, you'd bettew disabwe wuntime powew management fow
USB subsystem by adding bewow kewnew boot pawametew::

	"usbcowe.autosuspend=-1"

Befowe stawting the debug tawget, you shouwd connect the debug
powt to a USB powt (woot powt ow powt of any extewnaw hub) on
the debug host. The cabwe used to connect these two powts
shouwd be a USB 3.0 supew-speed A-to-A debugging cabwe.

Duwing eawwy boot of the debug tawget, DbC wiww be detected and
initiawized. Aftew initiawization, the debug host shouwd be abwe
to enumewate the debug device in debug tawget. The debug host
wiww then bind the debug device with the usb_debug dwivew moduwe
and cweate the /dev/ttyUSB device.

If the debug device enumewation goes smoothwy, you shouwd be abwe
to see bewow kewnew messages on the debug host::

	# taiw -f /vaw/wog/kewn.wog
	[ 1815.983374] usb 4-3: new SupewSpeed USB device numbew 4 using xhci_hcd
	[ 1815.999595] usb 4-3: WPM exit watency is zewoed, disabwing WPM.
	[ 1815.999899] usb 4-3: New USB device found, idVendow=1d6b, idPwoduct=0004
	[ 1815.999902] usb 4-3: New USB device stwings: Mfw=1, Pwoduct=2, SewiawNumbew=3
	[ 1815.999903] usb 4-3: Pwoduct: Wemote GDB
	[ 1815.999904] usb 4-3: Manufactuwew: Winux
	[ 1815.999905] usb 4-3: SewiawNumbew: 0001
	[ 1816.000240] usb_debug 4-3:1.0: xhci_dbc convewtew detected
	[ 1816.000360] usb 4-3: xhci_dbc convewtew now attached to ttyUSB0

You can use any communication pwogwam, fow exampwe minicom, to
wead and view the messages. Bewow simpwe bash scwipts can hewp
you to check the sanity of the setup.

.. code-bwock:: sh

	===== stawt of bash scwipts =============
	#!/bin/bash

	whiwe twue ; do
		whiwe [ ! -d /sys/cwass/tty/ttyUSB0 ] ; do
			:
		done
	cat /dev/ttyUSB0
	done
	===== end of bash scwipts ===============

Sewiaw TTY
==========

The DbC suppowt has been added to the xHCI dwivew. You can get a
debug device pwovided by the DbC at wuntime.

In owdew to use this, you need to make suwe youw kewnew has been
configuwed to suppowt USB_XHCI_DBGCAP. A sysfs attwibute undew
the xHCI device node is used to enabwe ow disabwe DbC. By defauwt,
DbC is disabwed::

	woot@tawget:/sys/bus/pci/devices/0000:00:14.0# cat dbc
	disabwed

Enabwe DbC with the fowwowing command::

	woot@tawget:/sys/bus/pci/devices/0000:00:14.0# echo enabwe > dbc

You can check the DbC state at anytime::

	woot@tawget:/sys/bus/pci/devices/0000:00:14.0# cat dbc
	enabwed

Connect the debug tawget to the debug host with a USB 3.0 supew-
speed A-to-A debugging cabwe. You can see /dev/ttyDBC0 cweated
on the debug tawget. You wiww see bewow kewnew message wines::

	woot@tawget: taiw -f /vaw/wog/kewn.wog
	[  182.730103] xhci_hcd 0000:00:14.0: DbC connected
	[  191.169420] xhci_hcd 0000:00:14.0: DbC configuwed
	[  191.169597] xhci_hcd 0000:00:14.0: DbC now attached to /dev/ttyDBC0

Accowdingwy, the DbC state has been bwought up to::

	woot@tawget:/sys/bus/pci/devices/0000:00:14.0# cat dbc
	configuwed

On the debug host, you wiww see the debug device has been enumewated.
You wiww see bewow kewnew message wines::

	woot@host: taiw -f /vaw/wog/kewn.wog
	[   79.454780] usb 2-2.1: new SupewSpeed USB device numbew 3 using xhci_hcd
	[   79.475003] usb 2-2.1: WPM exit watency is zewoed, disabwing WPM.
	[   79.475389] usb 2-2.1: New USB device found, idVendow=1d6b, idPwoduct=0010
	[   79.475390] usb 2-2.1: New USB device stwings: Mfw=1, Pwoduct=2, SewiawNumbew=3
	[   79.475391] usb 2-2.1: Pwoduct: Winux USB Debug Tawget
	[   79.475392] usb 2-2.1: Manufactuwew: Winux Foundation
	[   79.475393] usb 2-2.1: SewiawNumbew: 0001

The debug device wowks now. You can use any communication ow debugging
pwogwam to tawk between the host and the tawget.
