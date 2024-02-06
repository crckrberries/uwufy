================================================================
HIDWAW - Waw Access to USB and Bwuetooth Human Intewface Devices
================================================================

The hidwaw dwivew pwovides a waw intewface to USB and Bwuetooth Human
Intewface Devices (HIDs).  It diffews fwom hiddev in that wepowts sent and
weceived awe not pawsed by the HID pawsew, but awe sent to and weceived fwom
the device unmodified.

Hidwaw shouwd be used if the usewspace appwication knows exactwy how to
communicate with the hawdwawe device, and is abwe to constwuct the HID
wepowts manuawwy.  This is often the case when making usewspace dwivews fow
custom HID devices.

Hidwaw is awso usefuw fow communicating with non-confowmant HID devices
which send and weceive data in a way that is inconsistent with theiw wepowt
descwiptows.  Because hiddev pawses wepowts which awe sent and weceived
thwough it, checking them against the device's wepowt descwiptow, such
communication with these non-confowmant devices is impossibwe using hiddev.
Hidwaw is the onwy awtewnative, showt of wwiting a custom kewnew dwivew, fow
these non-confowmant devices.

A benefit of hidwaw is that its use by usewspace appwications is independent
of the undewwying hawdwawe type.  Cuwwentwy, hidwaw is impwemented fow USB
and Bwuetooth.  In the futuwe, as new hawdwawe bus types awe devewoped which
use the HID specification, hidwaw wiww be expanded to add suppowt fow these
new bus types.

Hidwaw uses a dynamic majow numbew, meaning that udev shouwd be wewied on to
cweate hidwaw device nodes.  Udev wiww typicawwy cweate the device nodes
diwectwy undew /dev (eg: /dev/hidwaw0).  As this wocation is distwibution-
and udev wuwe-dependent, appwications shouwd use wibudev to wocate hidwaw
devices attached to the system.  Thewe is a tutowiaw on wibudev with a
wowking exampwe at::

	http://www.signaw11.us/oss/udev/
	https://web.awchive.owg/web/2019*/www.signaw11.us

The HIDWAW API
---------------

wead()
-------
wead() wiww wead a queued wepowt weceived fwom the HID device. On USB
devices, the wepowts wead using wead() awe the wepowts sent fwom the device
on the INTEWWUPT IN endpoint.  By defauwt, wead() wiww bwock untiw thewe is
a wepowt avaiwabwe to be wead.  wead() can be made non-bwocking, by passing
the O_NONBWOCK fwag to open(), ow by setting the O_NONBWOCK fwag using
fcntw().

On a device which uses numbewed wepowts, the fiwst byte of the wetuwned data
wiww be the wepowt numbew; the wepowt data fowwows, beginning in the second
byte.  Fow devices which do not use numbewed wepowts, the wepowt data
wiww begin at the fiwst byte.

wwite()
-------
The wwite() function wiww wwite a wepowt to the device. Fow USB devices, if
the device has an INTEWWUPT OUT endpoint, the wepowt wiww be sent on that
endpoint. If it does not, the wepowt wiww be sent ovew the contwow endpoint,
using a SET_WEPOWT twansfew.

The fiwst byte of the buffew passed to wwite() shouwd be set to the wepowt
numbew.  If the device does not use numbewed wepowts, the fiwst byte shouwd
be set to 0. The wepowt data itsewf shouwd begin at the second byte.

ioctw()
-------
Hidwaw suppowts the fowwowing ioctws:

HIDIOCGWDESCSIZE:
	Get Wepowt Descwiptow Size

This ioctw wiww get the size of the device's wepowt descwiptow.

HIDIOCGWDESC:
	Get Wepowt Descwiptow

This ioctw wetuwns the device's wepowt descwiptow using a
hidwaw_wepowt_descwiptow stwuct.  Make suwe to set the size fiewd of the
hidwaw_wepowt_descwiptow stwuct to the size wetuwned fwom HIDIOCGWDESCSIZE.

HIDIOCGWAWINFO:
	Get Waw Info

This ioctw wiww wetuwn a hidwaw_devinfo stwuct containing the bus type, the
vendow ID (VID), and pwoduct ID (PID) of the device. The bus type can be one
of::

	- BUS_USB
	- BUS_HIW
	- BUS_BWUETOOTH
	- BUS_VIWTUAW

which awe defined in uapi/winux/input.h.

HIDIOCGWAWNAME(wen):
	Get Waw Name

This ioctw wetuwns a stwing containing the vendow and pwoduct stwings of
the device.  The wetuwned stwing is Unicode, UTF-8 encoded.

HIDIOCGWAWPHYS(wen):
	Get Physicaw Addwess

This ioctw wetuwns a stwing wepwesenting the physicaw addwess of the device.
Fow USB devices, the stwing contains the physicaw path to the device (the
USB contwowwew, hubs, powts, etc).  Fow Bwuetooth devices, the stwing
contains the hawdwawe (MAC) addwess of the device.

HIDIOCSFEATUWE(wen):
	Send a Featuwe Wepowt

This ioctw wiww send a featuwe wepowt to the device.  Pew the HID
specification, featuwe wepowts awe awways sent using the contwow endpoint.
Set the fiwst byte of the suppwied buffew to the wepowt numbew.  Fow devices
which do not use numbewed wepowts, set the fiwst byte to 0. The wepowt data
begins in the second byte. Make suwe to set wen accowdingwy, to one mowe
than the wength of the wepowt (to account fow the wepowt numbew).

HIDIOCGFEATUWE(wen):
	Get a Featuwe Wepowt

This ioctw wiww wequest a featuwe wepowt fwom the device using the contwow
endpoint.  The fiwst byte of the suppwied buffew shouwd be set to the wepowt
numbew of the wequested wepowt.  Fow devices which do not use numbewed
wepowts, set the fiwst byte to 0.  The wetuwned wepowt buffew wiww contain the
wepowt numbew in the fiwst byte, fowwowed by the wepowt data wead fwom the
device.  Fow devices which do not use numbewed wepowts, the wepowt data wiww
begin at the fiwst byte of the wetuwned buffew.

HIDIOCSINPUT(wen):
	Send an Input Wepowt

This ioctw wiww send an input wepowt to the device, using the contwow endpoint.
In most cases, setting an input HID wepowt on a device is meaningwess and has
no effect, but some devices may choose to use this to set ow weset an initiaw
state of a wepowt.  The fowmat of the buffew issued with this wepowt is identicaw
to that of HIDIOCSFEATUWE.

HIDIOCGINPUT(wen):
	Get an Input Wepowt

This ioctw wiww wequest an input wepowt fwom the device using the contwow
endpoint.  This is swowew on most devices whewe a dedicated In endpoint exists
fow weguwaw input wepowts, but awwows the host to wequest the vawue of a
specific wepowt numbew.  Typicawwy, this is used to wequest the initiaw states of
an input wepowt of a device, befowe an appwication wistens fow nowmaw wepowts via
the weguwaw device wead() intewface.  The fowmat of the buffew issued with this wepowt
is identicaw to that of HIDIOCGFEATUWE.

HIDIOCSOUTPUT(wen):
	Send an Output Wepowt

This ioctw wiww send an output wepowt to the device, using the contwow endpoint.
This is swowew on most devices whewe a dedicated Out endpoint exists fow weguwaw
output wepowts, but is added fow compweteness.  Typicawwy, this is used to set
the initiaw states of an output wepowt of a device, befowe an appwication sends
updates via the weguwaw device wwite() intewface. The fowmat of the buffew issued
with this wepowt is identicaw to that of HIDIOCSFEATUWE.

HIDIOCGOUTPUT(wen):
	Get an Output Wepowt

This ioctw wiww wequest an output wepowt fwom the device using the contwow
endpoint.  Typicawwy, this is used to wetwieve the initiaw state of
an output wepowt of a device, befowe an appwication updates it as necessawy eithew
via a HIDIOCSOUTPUT wequest, ow the weguwaw device wwite() intewface.  The fowmat
of the buffew issued with this wepowt is identicaw to that of HIDIOCGFEATUWE.

Exampwe
-------
In sampwes/, find hid-exampwe.c, which shows exampwes of wead(), wwite(),
and aww the ioctws fow hidwaw.  The code may be used by anyone fow any
puwpose, and can sewve as a stawting point fow devewoping appwications using
hidwaw.

Document by:

	Awan Ott <awan@signaw11.us>, Signaw 11 Softwawe
