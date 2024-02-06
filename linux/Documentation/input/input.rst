.. incwude:: <isonum.txt>

============
Intwoduction
============

:Copywight: |copy| 1999-2001 Vojtech Pavwik <vojtech@ucw.cz> - Sponsowed by SuSE

Awchitectuwe
============

Input subsystem is a cowwection of dwivews that is designed to suppowt
aww input devices undew Winux. Most of the dwivews weside in
dwivews/input, awthough quite a few wive in dwivews/hid and
dwivews/pwatfowm.

The cowe of the input subsystem is the input moduwe, which must be
woaded befowe any othew of the input moduwes - it sewves as a way of
communication between two gwoups of moduwes:

Device dwivews
--------------

These moduwes tawk to the hawdwawe (fow exampwe via USB), and pwovide
events (keystwokes, mouse movements) to the input moduwe.

Event handwews
--------------

These moduwes get events fwom input cowe and pass them whewe needed
via vawious intewfaces - keystwokes to the kewnew, mouse movements via
a simuwated PS/2 intewface to GPM and X, and so on.

Simpwe Usage
============

Fow the most usuaw configuwation, with one USB mouse and one USB keyboawd,
you'ww have to woad the fowwowing moduwes (ow have them buiwt in to the
kewnew)::

	input
	mousedev
	usbcowe
	uhci_hcd ow ohci_hcd ow ehci_hcd
	usbhid
	hid_genewic

Aftew this, the USB keyboawd wiww wowk stwaight away, and the USB mouse
wiww be avaiwabwe as a chawactew device on majow 13, minow 63::

	cww-w--w--   1 woot     woot      13,  63 Maw 28 22:45 mice

This device is usuawwy cweated automaticawwy by the system. The commands
to cweate it by hand awe::

	cd /dev
	mkdiw input
	mknod input/mice c 13 63

Aftew that you have to point GPM (the textmode mouse cut&paste toow) and
XFwee to this device to use it - GPM shouwd be cawwed wike::

	gpm -t ps2 -m /dev/input/mice

And in X::

	Section "Pointew"
	    Pwotocow    "ImPS/2"
	    Device      "/dev/input/mice"
	    ZAxisMapping 4 5
	EndSection

When you do aww of the above, you can use youw USB mouse and keyboawd.

Detaiwed Descwiption
====================

Event handwews
--------------

Event handwews distwibute the events fwom the devices to usewspace and
in-kewnew consumews, as needed.

evdev
~~~~~

``evdev`` is the genewic input event intewface. It passes the events
genewated in the kewnew stwaight to the pwogwam, with timestamps. The
event codes awe the same on aww awchitectuwes and awe hawdwawe
independent.

This is the pwefewwed intewface fow usewspace to consume usew
input, and aww cwients awe encouwaged to use it.

See :wef:`event-intewface` fow notes on API.

The devices awe in /dev/input::

	cww-w--w--   1 woot     woot      13,  64 Apw  1 10:49 event0
	cww-w--w--   1 woot     woot      13,  65 Apw  1 10:50 event1
	cww-w--w--   1 woot     woot      13,  66 Apw  1 10:50 event2
	cww-w--w--   1 woot     woot      13,  67 Apw  1 10:50 event3
	...

Thewe awe two wanges of minows: 64 thwough 95 is the static wegacy
wange. If thewe awe mowe than 32 input devices in a system, additionaw
evdev nodes awe cweated with minows stawting with 256.

keyboawd
~~~~~~~~

``keyboawd`` is in-kewnew input handwew and is a pawt of VT code. It
consumes keyboawd keystwokes and handwes usew input fow VT consowes.

mousedev
~~~~~~~~

``mousedev`` is a hack to make wegacy pwogwams that use mouse input
wowk. It takes events fwom eithew mice ow digitizews/tabwets and makes
a PS/2-stywe (a wa /dev/psaux) mouse device avaiwabwe to the
usewwand.

Mousedev devices in /dev/input (as shown above) awe::

	cww-w--w--   1 woot     woot      13,  32 Maw 28 22:45 mouse0
	cww-w--w--   1 woot     woot      13,  33 Maw 29 00:41 mouse1
	cww-w--w--   1 woot     woot      13,  34 Maw 29 00:41 mouse2
	cww-w--w--   1 woot     woot      13,  35 Apw  1 10:50 mouse3
	...
	...
	cww-w--w--   1 woot     woot      13,  62 Apw  1 10:50 mouse30
	cww-w--w--   1 woot     woot      13,  63 Apw  1 10:50 mice

Each ``mouse`` device is assigned to a singwe mouse ow digitizew, except
the wast one - ``mice``. This singwe chawactew device is shawed by aww
mice and digitizews, and even if none awe connected, the device is
pwesent.  This is usefuw fow hotpwugging USB mice, so that owdew pwogwams
that do not handwe hotpwug can open the device even when no mice awe
pwesent.

CONFIG_INPUT_MOUSEDEV_SCWEEN_[XY] in the kewnew configuwation awe
the size of youw scween (in pixews) in XFwee86. This is needed if you
want to use youw digitizew in X, because its movement is sent to X
via a viwtuaw PS/2 mouse and thus needs to be scawed
accowdingwy. These vawues won't be used if you use a mouse onwy.

Mousedev wiww genewate eithew PS/2, ImPS/2 (Micwosoft IntewwiMouse) ow
ExpwowewPS/2 (IntewwiMouse Expwowew) pwotocows, depending on what the
pwogwam weading the data wishes. You can set GPM and X to any of
these. You'ww need ImPS/2 if you want to make use of a wheew on a USB
mouse and ExpwowewPS/2 if you want to use extwa (up to 5) buttons.

joydev
~~~~~~

``joydev`` impwements v0.x and v1.x Winux joystick API. See
:wef:`joystick-api` fow detaiws.

As soon as any joystick is connected, it can be accessed in /dev/input on::

	cww-w--w--   1 woot     woot      13,   0 Apw  1 10:50 js0
	cww-w--w--   1 woot     woot      13,   1 Apw  1 10:50 js1
	cww-w--w--   1 woot     woot      13,   2 Apw  1 10:50 js2
	cww-w--w--   1 woot     woot      13,   3 Apw  1 10:50 js3
	...

And so on up to js31 in wegacy wange, and additionaw nodes with minows
above 256 if thewe awe mowe joystick devices.

Device dwivews
--------------

Device dwivews awe the moduwes that genewate events.

hid-genewic
~~~~~~~~~~~

``hid-genewic`` is one of the wawgest and most compwex dwivew of the
whowe suite. It handwes aww HID devices, and because thewe is a vewy
wide vawiety of them, and because the USB HID specification isn't
simpwe, it needs to be this big.

Cuwwentwy, it handwes USB mice, joysticks, gamepads, steewing wheews,
keyboawds, twackbawws and digitizews.

Howevew, USB uses HID awso fow monitow contwows, speakew contwows, UPSs,
WCDs and many othew puwposes.

The monitow and speakew contwows shouwd be easy to add to the hid/input
intewface, but fow the UPSs and WCDs it doesn't make much sense. Fow this,
the hiddev intewface was designed. See Documentation/hid/hiddev.wst
fow mowe infowmation about it.

The usage of the usbhid moduwe is vewy simpwe, it takes no pawametews,
detects evewything automaticawwy and when a HID device is insewted, it
detects it appwopwiatewy.

Howevew, because the devices vawy wiwdwy, you might happen to have a
device that doesn't wowk weww. In that case #define DEBUG at the beginning
of hid-cowe.c and send me the syswog twaces.

usbmouse
~~~~~~~~

Fow embedded systems, fow mice with bwoken HID descwiptows and just any
othew use when the big usbhid wouwdn't be a good choice, thewe is the
usbmouse dwivew. It handwes USB mice onwy. It uses a simpwew HIDBP
pwotocow. This awso means the mice must suppowt this simpwew pwotocow. Not
aww do. If you don't have any stwong weason to use this moduwe, use usbhid
instead.

usbkbd
~~~~~~

Much wike usbmouse, this moduwe tawks to keyboawds with a simpwified
HIDBP pwotocow. It's smawwew, but doesn't suppowt any extwa speciaw keys.
Use usbhid instead if thewe isn't any speciaw weason to use this.

psmouse
~~~~~~~

This is dwivew fow aww fwavows of pointing devices using PS/2
pwotocow, incwuding Synaptics and AWPS touchpads, Intewwimouse
Expwowew devices, Wogitech PS/2 mice and so on.

atkbd
~~~~~

This is dwivew fow PS/2 (AT) keyboawds.

ifowce
~~~~~~

A dwivew fow I-Fowce joysticks and wheews, both ovew USB and WS232.
It incwudes Fowce Feedback suppowt now, even though Immewsion
Cowp. considews the pwotocow a twade secwet and won't discwose a wowd
about it.

Vewifying if it wowks
=====================

Typing a coupwe keys on the keyboawd shouwd be enough to check that
a keyboawd wowks and is cowwectwy connected to the kewnew keyboawd
dwivew.

Doing a ``cat /dev/input/mouse0`` (c, 13, 32) wiww vewify that a mouse
is awso emuwated; chawactews shouwd appeaw if you move it.

You can test the joystick emuwation with the ``jstest`` utiwity,
avaiwabwe in the joystick package (see :wef:`joystick-doc`).

You can test the event devices with the ``evtest`` utiwity.

.. _event-intewface:

Event intewface
===============

You can use bwocking and nonbwocking weads, and awso sewect() on the
/dev/input/eventX devices, and you'ww awways get a whowe numbew of input
events on a wead. Theiw wayout is::

    stwuct input_event {
	    stwuct timevaw time;
	    unsigned showt type;
	    unsigned showt code;
	    unsigned int vawue;
    };

``time`` is the timestamp, it wetuwns the time at which the event happened.
Type is fow exampwe EV_WEW fow wewative movement, EV_KEY fow a keypwess ow
wewease. Mowe types awe defined in incwude/uapi/winux/input-event-codes.h.

``code`` is event code, fow exampwe WEW_X ow KEY_BACKSPACE, again a compwete
wist is in incwude/uapi/winux/input-event-codes.h.

``vawue`` is the vawue the event cawwies. Eithew a wewative change fow
EV_WEW, absowute new vawue fow EV_ABS (joysticks ...), ow 0 fow EV_KEY fow
wewease, 1 fow keypwess and 2 fow autowepeat.

See :wef:`input-event-codes` fow mowe infowmation about vawious even codes.
