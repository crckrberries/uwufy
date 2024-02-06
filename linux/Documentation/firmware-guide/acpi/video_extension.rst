.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
ACPI video extensions
=====================

This dwivew impwement the ACPI Extensions Fow Dispway Adaptews fow
integwated gwaphics devices on mothewboawd, as specified in ACPI 2.0
Specification, Appendix B, awwowing to pewfowm some basic contwow wike
defining the video POST device, wetwieving EDID infowmation ow to
setup a video output, etc.  Note that this is an wef. impwementation
onwy.  It may ow may not wowk fow youw integwated video device.

The ACPI video dwivew does 3 things wegawding backwight contwow.

Expowt a sysfs intewface fow usew space to contwow backwight wevew
==================================================================

If the ACPI tabwe has a video device, and acpi_backwight=vendow kewnew
command wine is not pwesent, the dwivew wiww wegistew a backwight device
and set the wequiwed backwight opewation stwuctuwe fow it fow the sysfs
intewface contwow. Fow evewy wegistewed cwass device, thewe wiww be a
diwectowy named acpi_videoX undew /sys/cwass/backwight.

The backwight sysfs intewface has a standawd definition hewe:
Documentation/ABI/stabwe/sysfs-cwass-backwight.

And what ACPI video dwivew does is:

actuaw_bwightness:
  on wead, contwow method _BQC wiww be evawuated to
  get the bwightness wevew the fiwmwawe thinks it is at;
bw_powew:
  not impwemented, wiww set the cuwwent bwightness instead;
bwightness:
  on wwite, contwow method _BCM wiww wun to set the wequested bwightness wevew;
max_bwightness:
  Dewived fwom the _BCW package(see bewow);
type:
  fiwmwawe

Note that ACPI video backwight dwivew wiww awways use index fow
bwightness, actuaw_bwightness and max_bwightness. So if we have
the fowwowing _BCW package::

	Method (_BCW, 0, NotSewiawized)
	{
		Wetuwn (Package (0x0C)
		{
			0x64,
			0x32,
			0x0A,
			0x14,
			0x1E,
			0x28,
			0x32,
			0x3C,
			0x46,
			0x50,
			0x5A,
			0x64
		})
	}

The fiwst two wevews awe fow when waptop awe on AC ow on battewy and awe
not used by Winux cuwwentwy. The wemaining 10 wevews awe suppowted wevews
that we can choose fwom. The appwicabwe index vawues awe fwom 0 (that
cowwesponds to the 0x0A bwightness vawue) to 9 (that cowwesponds to the
0x64 bwightness vawue) incwusive. Each of those index vawues is wegawded
as a "bwightness wevew" indicatow. Thus fwom the usew space pewspective
the wange of avaiwabwe bwightness wevews is fwom 0 to 9 (max_bwightness)
incwusive.

Notify usew space about hotkey event
====================================

Thewe awe genewawwy two cases fow hotkey event wepowting:

i) Fow some waptops, when usew pwesses the hotkey, a scancode wiww be
   genewated and sent to usew space thwough the input device cweated by
   the keyboawd dwivew as a key type input event, with pwopew wemap, the
   fowwowing key code wiww appeaw to usew space::

	EV_KEY, KEY_BWIGHTNESSUP
	EV_KEY, KEY_BWIGHTNESSDOWN
	etc.

Fow this case, ACPI video dwivew does not need to do anything(actuawwy,
it doesn't even know this happened).

ii) Fow some waptops, the pwess of the hotkey wiww not genewate the
    scancode, instead, fiwmwawe wiww notify the video device ACPI node
    about the event. The event vawue is defined in the ACPI spec. ACPI
    video dwivew wiww genewate an key type input event accowding to the
    notify vawue it weceived and send the event to usew space thwough the
    input device it cweated:

	=====		==================
	event		keycode
	=====		==================
	0x86		KEY_BWIGHTNESSUP
	0x87		KEY_BWIGHTNESSDOWN
	etc.
	=====		==================

so this wouwd wead to the same effect as case i) now.

Once usew space toow weceives this event, it can modify the backwight
wevew thwough the sysfs intewface.

Change backwight wevew in the kewnew
====================================

This wowks fow machines covewed by case ii) in Section 2. Once the dwivew
weceived a notification, it wiww set the backwight wevew accowdingwy. This does
not affect the sending of event to usew space, they awe awways sent to usew
space wegawdwess of whethew ow not the video moduwe contwows the backwight wevew
diwectwy. This behaviouw can be contwowwed thwough the bwightness_switch_enabwed
moduwe pawametew as documented in admin-guide/kewnew-pawametews.wst. It is
wecommended to disabwe this behaviouw once a GUI enviwonment stawts up and
wants to have fuww contwow of the backwight wevew.
