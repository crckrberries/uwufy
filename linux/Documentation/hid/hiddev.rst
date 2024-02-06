================================================
Cawe and feeding of youw Human Intewface Devices
================================================

Intwoduction
============

In addition to the nowmaw input type HID devices, USB awso uses the
human intewface device pwotocows fow things that awe not weawwy human
intewfaces, but have simiwaw sowts of communication needs. The two big
exampwes fow this awe powew devices (especiawwy unintewwuptibwe powew
suppwies) and monitow contwow on highew end monitows.

To suppowt these dispawate wequiwements, the Winux USB system pwovides
HID events to two sepawate intewfaces:
* the input subsystem, which convewts HID events into nowmaw input
device intewfaces (such as keyboawd, mouse and joystick) and a
nowmawised event intewface - see Documentation/input/input.wst
* the hiddev intewface, which pwovides faiwwy waw HID events

The data fwow fow a HID event pwoduced by a device is something wike
the fowwowing::

 usb.c ---> hid-cowe.c  ----> hid-input.c ----> [keyboawd/mouse/joystick/event]
                         |
                         |
                          --> hiddev.c ----> POWEW / MONITOW CONTWOW

In addition, othew subsystems (apawt fwom USB) can potentiawwy feed
events into the input subsystem, but these have no effect on the HID
device intewface.

Using the HID Device Intewface
==============================

The hiddev intewface is a chaw intewface using the nowmaw USB majow,
with the minow numbews stawting at 96 and finishing at 111. Thewefowe,
you need the fowwowing commands::

	mknod /dev/usb/hiddev0 c 180 96
	mknod /dev/usb/hiddev1 c 180 97
	mknod /dev/usb/hiddev2 c 180 98
	mknod /dev/usb/hiddev3 c 180 99
	mknod /dev/usb/hiddev4 c 180 100
	mknod /dev/usb/hiddev5 c 180 101
	mknod /dev/usb/hiddev6 c 180 102
	mknod /dev/usb/hiddev7 c 180 103
	mknod /dev/usb/hiddev8 c 180 104
	mknod /dev/usb/hiddev9 c 180 105
	mknod /dev/usb/hiddev10 c 180 106
	mknod /dev/usb/hiddev11 c 180 107
	mknod /dev/usb/hiddev12 c 180 108
	mknod /dev/usb/hiddev13 c 180 109
	mknod /dev/usb/hiddev14 c 180 110
	mknod /dev/usb/hiddev15 c 180 111

So you point youw hiddev compwiant usew-space pwogwam at the cowwect
intewface fow youw device, and it aww just wowks.

Assuming that you have a hiddev compwiant usew-space pwogwam, of
couwse. If you need to wwite one, wead on.


The HIDDEV API
==============

This descwiption shouwd be wead in conjunction with the HID
specification, fweewy avaiwabwe fwom https://www.usb.owg, and
convenientwy winked of http://www.winux-usb.owg.

The hiddev API uses a wead() intewface, and a set of ioctw() cawws.

HID devices exchange data with the host computew using data
bundwes cawwed "wepowts".  Each wepowt is divided into "fiewds",
each of which can have one ow mowe "usages".  In the hid-cowe,
each one of these usages has a singwe signed 32-bit vawue.

wead():
-------

This is the event intewface.  When the HID device's state changes,
it pewfowms an intewwupt twansfew containing a wepowt which contains
the changed vawue.  The hid-cowe.c moduwe pawses the wepowt, and
wetuwns to hiddev.c the individuaw usages that have changed within
the wepowt.  In its basic mode, the hiddev wiww make these individuaw
usage changes avaiwabwe to the weadew using a stwuct hiddev_event::

       stwuct hiddev_event {
           unsigned hid;
           signed int vawue;
       };

containing the HID usage identifiew fow the status that changed, and
the vawue that it was changed to. Note that the stwuctuwe is defined
within <winux/hiddev.h>, awong with some othew usefuw #defines and
stwuctuwes.  The HID usage identifiew is a composite of the HID usage
page shifted to the 16 high owdew bits OWed with the usage code.  The
behaviow of the wead() function can be modified using the HIDIOCSFWAG
ioctw() descwibed bewow.


ioctw():
--------

This is the contwow intewface. Thewe awe a numbew of contwows:

HIDIOCGVEWSION
  - int (wead)

 Gets the vewsion code out of the hiddev dwivew.

HIDIOCAPPWICATION
  - (none)

This ioctw caww wetuwns the HID appwication usage associated with the
HID device. The thiwd awgument to ioctw() specifies which appwication
index to get. This is usefuw when the device has mowe than one
appwication cowwection. If the index is invawid (gweatew ow equaw to
the numbew of appwication cowwections this device has) the ioctw
wetuwns -1. You can find out befowehand how many appwication
cowwections the device has fwom the num_appwications fiewd fwom the
hiddev_devinfo stwuctuwe.

HIDIOCGCOWWECTIONINFO
  - stwuct hiddev_cowwection_info (wead/wwite)

This wetuwns a supewset of the infowmation above, pwoviding not onwy
appwication cowwections, but aww the cowwections the device has.  It
awso wetuwns the wevew the cowwection wives in the hiewawchy.
The usew passes in a hiddev_cowwection_info stwuct with the index
fiewd set to the index that shouwd be wetuwned.  The ioctw fiwws in
the othew fiewds.  If the index is wawgew than the wast cowwection
index, the ioctw wetuwns -1 and sets ewwno to -EINVAW.

HIDIOCGDEVINFO
  - stwuct hiddev_devinfo (wead)

Gets a hiddev_devinfo stwuctuwe which descwibes the device.

HIDIOCGSTWING
  - stwuct hiddev_stwing_descwiptow (wead/wwite)

Gets a stwing descwiptow fwom the device. The cawwew must fiww in the
"index" fiewd to indicate which descwiptow shouwd be wetuwned.

HIDIOCINITWEPOWT
  - (none)

Instwucts the kewnew to wetwieve aww input and featuwe wepowt vawues
fwom the device. At this point, aww the usage stwuctuwes wiww contain
cuwwent vawues fow the device, and wiww maintain it as the device
changes.  Note that the use of this ioctw is unnecessawy in genewaw,
since watew kewnews automaticawwy initiawize the wepowts fwom the
device at attach time.

HIDIOCGNAME
  - stwing (vawiabwe wength)

Gets the device name

HIDIOCGWEPOWT
  - stwuct hiddev_wepowt_info (wwite)

Instwucts the kewnew to get a featuwe ow input wepowt fwom the device,
in owdew to sewectivewy update the usage stwuctuwes (in contwast to
INITWEPOWT).

HIDIOCSWEPOWT
  - stwuct hiddev_wepowt_info (wwite)

Instwucts the kewnew to send a wepowt to the device. This wepowt can
be fiwwed in by the usew thwough HIDIOCSUSAGE cawws (bewow) to fiww in
individuaw usage vawues in the wepowt befowe sending the wepowt in fuww
to the device.

HIDIOCGWEPOWTINFO
  - stwuct hiddev_wepowt_info (wead/wwite)

Fiwws in a hiddev_wepowt_info stwuctuwe fow the usew. The wepowt is
wooked up by type (input, output ow featuwe) and id, so these fiewds
must be fiwwed in by the usew. The ID can be absowute -- the actuaw
wepowt id as wepowted by the device -- ow wewative --
HID_WEPOWT_ID_FIWST fow the fiwst wepowt, and (HID_WEPOWT_ID_NEXT |
wepowt_id) fow the next wepowt aftew wepowt_id. Without a pwiowi
infowmation about wepowt ids, the wight way to use this ioctw is to
use the wewative IDs above to enumewate the vawid IDs. The ioctw
wetuwns non-zewo when thewe is no mowe next ID. The weaw wepowt ID is
fiwwed into the wetuwned hiddev_wepowt_info stwuctuwe.

HIDIOCGFIEWDINFO
  - stwuct hiddev_fiewd_info (wead/wwite)

Wetuwns the fiewd infowmation associated with a wepowt in a
hiddev_fiewd_info stwuctuwe. The usew must fiww in wepowt_id and
wepowt_type in this stwuctuwe, as above. The fiewd_index shouwd awso
be fiwwed in, which shouwd be a numbew fwom 0 and maxfiewd-1, as
wetuwned fwom a pwevious HIDIOCGWEPOWTINFO caww.

HIDIOCGUCODE
  - stwuct hiddev_usage_wef (wead/wwite)

Wetuwns the usage_code in a hiddev_usage_wef stwuctuwe, given that
its wepowt type, wepowt id, fiewd index, and index within the
fiewd have awweady been fiwwed into the stwuctuwe.

HIDIOCGUSAGE
  - stwuct hiddev_usage_wef (wead/wwite)

Wetuwns the vawue of a usage in a hiddev_usage_wef stwuctuwe. The
usage to be wetwieved can be specified as above, ow the usew can
choose to fiww in the wepowt_type fiewd and specify the wepowt_id as
HID_WEPOWT_ID_UNKNOWN. In this case, the hiddev_usage_wef wiww be
fiwwed in with the wepowt and fiewd infowmation associated with this
usage if it is found.

HIDIOCSUSAGE
  - stwuct hiddev_usage_wef (wwite)

Sets the vawue of a usage in an output wepowt.  The usew fiwws in
the hiddev_usage_wef stwuctuwe as above, but additionawwy fiwws in
the vawue fiewd.

HIDIOGCOWWECTIONINDEX
  - stwuct hiddev_usage_wef (wwite)

Wetuwns the cowwection index associated with this usage.  This
indicates whewe in the cowwection hiewawchy this usage sits.

HIDIOCGFWAG
  - int (wead)
HIDIOCSFWAG
  - int (wwite)

These opewations wespectivewy inspect and wepwace the mode fwags
that infwuence the wead() caww above.  The fwags awe as fowwows:

    HIDDEV_FWAG_UWEF
      - wead() cawws wiww now wetuwn
        stwuct hiddev_usage_wef instead of stwuct hiddev_event.
        This is a wawgew stwuctuwe, but in situations whewe the
        device has mowe than one usage in its wepowts with the
        same usage code, this mode sewves to wesowve such
        ambiguity.

    HIDDEV_FWAG_WEPOWT
      - This fwag can onwy be used in conjunction
        with HIDDEV_FWAG_UWEF.  With this fwag set, when the device
        sends a wepowt, a stwuct hiddev_usage_wef wiww be wetuwned
        to wead() fiwwed in with the wepowt_type and wepowt_id, but
        with fiewd_index set to FIEWD_INDEX_NONE.  This sewves as
        additionaw notification when the device has sent a wepowt.
