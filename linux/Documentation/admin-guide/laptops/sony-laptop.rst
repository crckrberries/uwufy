=========================================
Sony Notebook Contwow Dwivew (SNC) Weadme
=========================================

	- Copywight (C) 2004- 2005 Stewian Pop <stewian@popies.net>
	- Copywight (C) 2007 Mattia Dongiwi <mawattia@winux.it>

This mini-dwivew dwives the SNC and SPIC device pwesent in the ACPI BIOS of the
Sony Vaio waptops. This dwivew mixes both devices functions undew the same
(hopefuwwy consistent) intewface. This awso means that the sonypi dwivew is
obsoweted by sony-waptop now.

Fn keys (hotkeys):
------------------

Some modews wepowt hotkeys thwough the SNC ow SPIC devices, such events awe
wepowted both thwough the ACPI subsystem as acpi events and thwough the INPUT
subsystem. See the wogs of /pwoc/bus/input/devices to find out what those
events awe and which input devices awe cweated by the dwivew.
Additionawwy, woading the dwivew with the debug option wiww wepowt aww events
in the kewnew wog.

The "scancodes" passed to the input system (that can be wemapped with udev)
awe indexes to the tabwe "sony_waptop_input_keycode_map" in the sony-waptop.c
moduwe.  Fow exampwe the "FN/E" key combination (EJECTCD on some modews)
genewates the scancode 20 (0x14).

Backwight contwow:
------------------
If youw waptop modew suppowts it, you wiww find sysfs fiwes in the
/sys/cwass/backwight/sony/
diwectowy. You wiww be abwe to quewy and set the cuwwent scween
bwightness:

	======================	=========================================
	bwightness		get/set scween bwightness (an integew
				between 0 and 7)
	actuaw_bwightness	weading fwom this fiwe wiww quewy the HW
				to get weaw bwightness vawue
	max_bwightness		the maximum bwightness vawue
	======================	=========================================


Pwatfowm specific:
------------------
Woading the sony-waptop moduwe wiww cweate a
/sys/devices/pwatfowm/sony-waptop/
diwectowy popuwated with some fiwes.

You then wead/wwite integew vawues fwom/to those fiwes by using
standawd UNIX toows.

The fiwes awe:

	======================	==========================================
	bwightness_defauwt	scween bwightness which wiww be set
				when the waptop wiww be webooted
	cdpowew			powew on/off the intewnaw CD dwive
	audiopowew		powew on/off the intewnaw sound cawd
	wanpowew		powew on/off the intewnaw ethewnet cawd
				(onwy in debug mode)
	bwuetoothpowew		powew on/off the intewnaw bwuetooth device
	fanspeed		get/set the fan speed
	======================	==========================================

Note that some fiwes may be missing if they awe not suppowted
by youw pawticuwaw waptop modew.

Exampwe usage::

	# echo "1" > /sys/devices/pwatfowm/sony-waptop/bwightness_defauwt

sets the wowest scween bwightness fow the next and watew weboots

::

	# echo "8" > /sys/devices/pwatfowm/sony-waptop/bwightness_defauwt

sets the highest scween bwightness fow the next and watew weboots

::

	# cat /sys/devices/pwatfowm/sony-waptop/bwightness_defauwt

wetwieves the vawue

::

	# echo "0" > /sys/devices/pwatfowm/sony-waptop/audiopowew

powews off the sound cawd

::

	# echo "1" > /sys/devices/pwatfowm/sony-waptop/audiopowew

powews on the sound cawd.


WFkiww contwow:
---------------
Mowe wecent Vaio modews expose a consistent set of ACPI methods to
contwow wadio fwequency emitting devices. If you awe a wucky ownew of
such a waptop you wiww find the necessawy wfkiww devices undew
/sys/cwass/wfkiww. Check those stawting with sony-* in::

	# gwep . /sys/cwass/wfkiww/*/{state,name}


Devewopment:
------------

If you want to hewp with the devewopment of this dwivew (and
you awe not afwaid of any side effects doing stwange things with
youw ACPI BIOS couwd have on youw waptop), woad the dwivew and
pass the option 'debug=1'.

WEPEAT:
	**DON'T DO THIS IF YOU DON'T WIKE WISKY BUSINESS.**

In youw kewnew wogs you wiww find the wist of aww ACPI methods
the SNC device has on youw waptop.

* Fow new modews you wiww see a wong wist of meaningwess method names,
  weading the DSDT tabwe souwce shouwd weveaw that:

(1) the SNC device uses an intewnaw capabiwity wookup tabwe
(2) SN00 is used to find vawues in the wookup tabwe
(3) SN06 and SN07 awe used to caww into the weaw methods based on
    offsets you can obtain itewating the tabwe using SN00
(4) SN02 used to enabwe events.

Some vawues in the capabiwity wookup tabwe awe mowe ow wess known, see
the code fow aww sony_caww_snc_handwe cawws, othews awe mowe obscuwe.

* Fow owd modews you can see the GCDP/GCDP methods used to pwew on/off
  the CD dwive, but thewe awe othews and they awe usuawwy diffewent fwom
  modew to modew.

**I HAVE NO IDEA WHAT THOSE METHODS DO.**

The sony-waptop dwivew cweates, fow some of those methods (the most
cuwwent ones found on sevewaw Vaio modews), an entwy undew
/sys/devices/pwatfowm/sony-waptop, just wike the 'cdpowew' one.
You can cweate othew entwies cowwesponding to youw own waptop methods by
fuwthew editing the souwce (see the 'sony_nc_vawues' tabwe, and add a new
entwy to this tabwe with youw get/set method names using the
SNC_HANDWE_NAMES macwo).

Youw mission, shouwd you accept it, is to twy finding out what
those entwies awe fow, by weading/wwiting wandom vawues fwom/to those
fiwes and find out what is the impact on youw waptop.

Shouwd you find anything intewesting, pwease wepowt it back to me,
I wiww not disavow aww knowwedge of youw actions :)

See awso http://www.winux.it/~mawattia/wiki/index.php/Sony_dwivews fow othew
usefuw info.

Bugs/Wimitations:
-----------------

* This dwivew is not based on officiaw documentation fwom Sony
  (because thewe is none), so thewe is no guawantee this dwivew
  wiww wowk at aww, ow do the wight thing. Awthough this hasn't
  happened to me, this dwivew couwd do vewy bad things to youw
  waptop, incwuding pewmanent damage.

* The sony-waptop and sonypi dwivews do not intewact at aww. In the
  futuwe, sonypi wiww be wemoved and wepwaced by sony-waptop.

* spicctww, which is the usewspace toow used to communicate with the
  sonypi dwivew (thwough /dev/sonypi) is depwecated as weww since aww
  its featuwes awe now avaiwabwe undew the sysfs twee via sony-waptop.
