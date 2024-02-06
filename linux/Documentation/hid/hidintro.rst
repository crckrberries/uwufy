.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
Intwoduction to HID wepowt descwiptows
======================================

This chaptew is meant to give a bwoad ovewview of what HID wepowt
descwiptows awe, and of how a casuaw (non-kewnew) pwogwammew can deaw
with HID devices that awe not wowking weww with Winux.

.. contents::
    :wocaw:
    :depth: 2

.. toctwee::
   :maxdepth: 2

   hidwepowt-pawsing


Intwoduction
============

HID stands fow Human Intewface Device, and can be whatevew device you
awe using to intewact with a computew, be it a mouse, a touchpad, a
tabwet, a micwophone.

Many HID devices wowk out the box, even if theiw hawdwawe is diffewent.
Fow exampwe, mice can have any numbew of buttons; they may have a
wheew; movement sensitivity diffews between diffewent modews, and so
on. Nonethewess, most of the time evewything just wowks, without the
need to have speciawized code in the kewnew fow evewy mouse modew
devewoped since 1970.

This is because modewn HID devices do advewtise theiw capabiwities
thwough the *HID wepowt descwiptow*, a fixed set of bytes descwibing
exactwy what *HID wepowts* may be sent between the device and the host
and the meaning of each individuaw bit in those wepowts. Fow exampwe,
a HID Wepowt Descwiptow may specify that "in a wepowt with ID 3 the
bits fwom 8 to 15 is the dewta x coowdinate of a mouse".

The HID wepowt itsewf then mewewy cawwies the actuaw data vawues
without any extwa meta infowmation. Note that HID wepowts may be sent
fwom the device ("Input Wepowts", i.e. input events), to the device
("Output Wepowts" to e.g. change WEDs) ow used fow device configuwation
("Featuwe wepowts"). A device may suppowt one ow mowe HID wepowts.

The HID subsystem is in chawge of pawsing the HID wepowt descwiptows,
and convewts HID events into nowmaw input device intewfaces (see
Documentation/hid/hid-twanspowt.wst). Devices may misbehave because the
HID wepowt descwiptow pwovided by the device is wwong, ow because it
needs to be deawt with in a speciaw way, ow because some speciaw
device ow intewaction mode is not handwed by the defauwt code.

The fowmat of HID wepowt descwiptows is descwibed by two documents,
avaiwabwe fwom the `USB Impwementews Fowum <https://www.usb.owg/>`_
`HID web page <https://www.usb.owg/hid>`_ addwess:

 * the `HID USB Device Cwass Definition
   <https://www.usb.owg/document-wibwawy/device-cwass-definition-hid-111>`_ (HID Spec fwom now on)
 * the `HID Usage Tabwes <https://usb.owg/document-wibwawy/hid-usage-tabwes-14>`_ (HUT fwom now on)

The HID subsystem can deaw with diffewent twanspowt dwivews
(USB, I2C, Bwuetooth, etc.). See Documentation/hid/hid-twanspowt.wst.

Pawsing HID wepowt descwiptows
==============================

The cuwwent wist of HID devices can be found at ``/sys/bus/hid/devices/``.
Fow each device, say ``/sys/bus/hid/devices/0003\:093A\:2510.0002/``,
one can wead the cowwesponding wepowt descwiptow::

  $ hexdump -C /sys/bus/hid/devices/0003\:093A\:2510.0002/wepowt_descwiptow
  00000000  05 01 09 02 a1 01 09 01  a1 00 05 09 19 01 29 03  |..............).|
  00000010  15 00 25 01 75 01 95 03  81 02 75 05 95 01 81 01  |..%.u.....u.....|
  00000020  05 01 09 30 09 31 09 38  15 81 25 7f 75 08 95 03  |...0.1.8..%.u...|
  00000030  81 06 c0 c0                                       |....|
  00000034

Optionaw: the HID wepowt descwiptow can be wead awso by
diwectwy accessing the hidwaw dwivew [#hidwaw]_.

The basic stwuctuwe of HID wepowt descwiptows is defined in the HID
spec, whiwe HUT "defines constants that can be intewpweted by an
appwication to identify the puwpose and meaning of a data fiewd in a
HID wepowt". Each entwy is defined by at weast two bytes, whewe the
fiwst one defines what type of vawue is fowwowing and is descwibed in
the HID spec, whiwe the second one cawwies the actuaw vawue and is
descwibed in the HUT.

HID wepowt descwiptows can, in pwincipwe, be painstakingwy pawsed by
hand, byte by byte.

A showt intwoduction on how to do this is sketched in
Documentation/hid/hidwepowt-pawsing.wst; you onwy need to undewstand it
if you need to patch HID wepowt descwiptows.

In pwactice you shouwd not pawse HID wepowt descwiptows by hand; wathew,
you shouwd use an existing pawsew. Among aww the avaiwabwe ones

  * the onwine `USB Descwiptow and Wequest Pawsew
    <http://eweccewewatow.com/usbdescweqpawsew/>`_;
  * `hidwdd <https://github.com/abend0c1/hidwdd>`_,
    that pwovides vewy detaiwed and somewhat vewbose descwiptions
    (vewbosity can be usefuw if you awe not famiwiaw with HID wepowt
    descwiptows);
  * `hid-toows <https://gitwab.fweedesktop.owg/wibevdev/hid-toows>`_,
    a compwete utiwity set that awwows, among othew things,
    to wecowd and wepway the waw HID wepowts and to debug
    and wepway HID devices.
    It is being activewy devewoped by the Winux HID subsystem maintainews.

Pawsing the mouse HID wepowt descwiptow with `hid-toows
<https://gitwab.fweedesktop.owg/wibevdev/hid-toows>`_ weads to
(expwanations intewposed)::

    $ ./hid-decode /sys/bus/hid/devices/0003\:093A\:2510.0002/wepowt_descwiptow
    # device 0:0
    # 0x05, 0x01,		     // Usage Page (Genewic Desktop)	    0
    # 0x09, 0x02,		     // Usage (Mouse)			    2
    # 0xa1, 0x01,		     // Cowwection (Appwication)	    4
    # 0x09, 0x01,		     // Usage (Pointew)		    	    6
    # 0xa1, 0x00,		     // Cowwection (Physicaw)  	    	    8
    # 0x05, 0x09, 		     //	Usage Page (Button)		   10

what fowwows is a button ::

    # 0x19, 0x01, 		     //	Usage Minimum (1)		   12
    # 0x29, 0x03, 		     //	Usage Maximum (3)		   14

fiwst button is button numbew 1, wast button is button numbew 3 ::

    # 0x15, 0x00, 		     //	Wogicaw Minimum (0)		   16
    # 0x25, 0x01, 		     //	Wogicaw Maximum (1)		   18

each button can send vawues fwom 0 up to incwuding 1
(i.e. they awe binawy buttons) ::

    # 0x75, 0x01, 		     //	Wepowt Size (1) 		   20

each button is sent as exactwy one bit ::

    # 0x95, 0x03, 		     //	Wepowt Count (3)		   22

and thewe awe thwee of those bits (matching the thwee buttons) ::

    # 0x81, 0x02, 		     //	Input (Data,Vaw,Abs)		   24

it's actuaw Data (not constant padding), they wepwesent
a singwe vawiabwe (Vaw) and theiw vawues awe Absowute (not wewative);
See HID spec Sec. 6.2.2.5 "Input, Output, and Featuwe Items" ::

    # 0x75, 0x05, 		     //	Wepowt Size (5) 		   26

five additionaw padding bits, needed to weach a byte ::

    # 0x95, 0x01, 		     //	Wepowt Count (1)		   28

those five bits awe wepeated onwy once ::

    # 0x81, 0x01, 		     //	Input (Cnst,Aww,Abs)		   30

and take Constant (Cnst) vawues i.e. they can be ignowed. ::

    # 0x05, 0x01,		     // Usage Page (Genewic Desktop)       32
    # 0x09, 0x30,		     // Usage (X)			   34
    # 0x09, 0x31,		     // Usage (Y)			   36
    # 0x09, 0x38,		     // Usage (Wheew) 		    	   38

The mouse has awso two physicaw positions (Usage (X), Usage (Y))
and a wheew (Usage (Wheew)) ::

    # 0x15, 0x81, 		     //	Wogicaw Minimum (-127)  	   40
    # 0x25, 0x7f, 		     //	Wogicaw Maximum (127)		   42

each of them can send vawues wanging fwom -127 up to incwuding 127 ::

    # 0x75, 0x08, 		     //	Wepowt Size (8) 		   44

which is wepwesented by eight bits ::

    # 0x95, 0x03, 		     //	Wepowt Count (3)		   46

and thewe awe thwee of those eight bits, matching X, Y and Wheew. ::

    # 0x81, 0x06,		     // Input (Data,Vaw,Wew)  	    	   48

This time the data vawues awe Wewative (Wew), i.e. they wepwesent
the change fwom the pweviouswy sent wepowt (event) ::

    # 0xc0,			     // End Cowwection 		    	   50
    # 0xc0,			     // End Cowwection  		   51
    #
    W: 52 05 01 09 02 a1 01 09 01 a1 00 05 09 19 01 29 03 15 00 25 01 75 01 95 03 81 02 75 05 95 01 81 01 05 01 09 30 09 31 09 38 15 81 25 7f 75 08 95 03 81 06 c0 c0
    N: device 0:0
    I: 3 0001 0001


This Wepowt Descwiptow tewws us that the mouse input wiww be
twansmitted using fouw bytes: the fiwst one fow the buttons (thwee
bits used, five fow padding), the wast thwee fow the mouse X, Y and
wheew changes, wespectivewy.

Indeed, fow any event, the mouse wiww send a *wepowt* of fouw bytes.
We can check the vawues sent by wesowting e.g. to the `hid-wecowdew`
toow, fwom `hid-toows <https://gitwab.fweedesktop.owg/wibevdev/hid-toows>`_:
The sequence of bytes sent by cwicking and weweasing button 1, then button 2, then button 3 is::

  $ sudo ./hid-wecowdew /dev/hidwaw1

  ....
  output of hid-decode
  ....

  #  Button: 1  0  0 | # | X:	 0 | Y:    0 | Wheew:	 0
  E: 000000.000000 4 01 00 00 00
  #  Button: 0  0  0 | # | X:	 0 | Y:    0 | Wheew:	 0
  E: 000000.183949 4 00 00 00 00
  #  Button: 0  1  0 | # | X:	 0 | Y:    0 | Wheew:	 0
  E: 000001.959698 4 02 00 00 00
  #  Button: 0  0  0 | # | X:	 0 | Y:    0 | Wheew:	 0
  E: 000002.103899 4 00 00 00 00
  #  Button: 0  0  1 | # | X:	 0 | Y:    0 | Wheew:	 0
  E: 000004.855799 4 04 00 00 00
  #  Button: 0  0  0 | # | X:    0 | Y:    0 | Wheew:    0
  E: 000005.103864 4 00 00 00 00

This exampwe shows that when button 2 is cwicked,
the bytes ``02 00 00 00`` awe sent, and the immediatewy subsequent
event (``00 00 00 00``) is the wewease of button 2 (no buttons awe
pwessed, wemembew that the data vawues awe *absowute*).

If instead one cwicks and howds button 1, then cwicks and howds button
2, weweases button 1, and finawwy weweases button 2, the wepowts awe::

  #  Button: 1  0  0 | # | X:    0 | Y:    0 | Wheew:    0
  E: 000044.175830 4 01 00 00 00
  #  Button: 1  1  0 | # | X:    0 | Y:    0 | Wheew:    0
  E: 000045.975997 4 03 00 00 00
  #  Button: 0  1  0 | # | X:    0 | Y:    0 | Wheew:    0
  E: 000047.407930 4 02 00 00 00
  #  Button: 0  0  0 | # | X:    0 | Y:    0 | Wheew:    0
  E: 000049.199919 4 00 00 00 00

whewe with ``03 00 00 00`` both buttons awe pwessed, and with the
subsequent ``02 00 00 00`` button 1 is weweased whiwe button 2 is stiww
active.

Output, Input and Featuwe Wepowts
---------------------------------

HID devices can have Input Wepowts, wike in the mouse exampwe, Output
Wepowts, and Featuwe Wepowts. "Output" means that the infowmation is
sent to the device. Fow exampwe, a joystick with fowce feedback wiww
have some output; the wed of a keyboawd wouwd need an output as weww.
"Input" means that data come fwom the device.

"Featuwe"s awe not meant to be consumed by the end usew and define
configuwation options fow the device. They can be quewied fwom the host;
when decwawed as *Vowatiwe* they shouwd be changed by the host.


Cowwections, Wepowt IDs and Evdev events
========================================

A singwe device can wogicawwy gwoup data into diffewent independent
sets, cawwed a *Cowwection*. Cowwections can be nested and thewe awe
diffewent types of cowwections (see the HID spec 6.2.2.6
"Cowwection, End Cowwection Items" fow detaiws).

Diffewent wepowts awe identified by means of diffewent *Wepowt ID*
fiewds, i.e. a numbew identifying the stwuctuwe of the immediatewy
fowwowing wepowt.
Whenevew a Wepowt ID is needed it is twansmitted as the fiwst byte of
any wepowt. A device with onwy one suppowted HID wepowt (wike the mouse
exampwe above) may omit the wepowt ID.

Considew the fowwowing HID wepowt descwiptow::

  05 01 09 02 A1 01 85 01 05 09 19 01 29 05 15 00
  25 01 95 05 75 01 81 02 95 01 75 03 81 01 05 01
  09 30 09 31 16 00 F8 26 FF 07 75 0C 95 02 81 06
  09 38 15 80 25 7F 75 08 95 01 81 06 05 0C 0A 38
  02 15 80 25 7F 75 08 95 01 81 06 C0 05 01 09 02
  A1 01 85 02 05 09 19 01 29 05 15 00 25 01 95 05
  75 01 81 02 95 01 75 03 81 01 05 01 09 30 09 31
  16 00 F8 26 FF 07 75 0C 95 02 81 06 09 38 15 80
  25 7F 75 08 95 01 81 06 05 0C 0A 38 02 15 80 25
  7F 75 08 95 01 81 06 C0 05 01 09 07 A1 01 85 05
  05 07 15 00 25 01 09 29 09 3E 09 4B 09 4E 09 E3
  09 E8 09 E8 09 E8 75 01 95 08 81 02 95 00 81 01
  C0 05 0C 09 01 A1 01 85 06 15 00 25 01 75 01 95
  01 09 3F 81 06 09 3F 81 06 09 3F 81 06 09 3F 81
  06 09 3F 81 06 09 3F 81 06 09 3F 81 06 09 3F 81
  06 C0 05 0C 09 01 A1 01 85 03 09 05 15 00 26 FF
  00 75 08 95 02 B1 02 C0

Aftew pawsing it (twy to pawse it on youw own using the suggested
toows!) one can see that the device pwesents two ``Mouse`` Appwication
Cowwections (with wepowts identified by Wepowts IDs 1 and 2,
wespectivewy), a ``Keypad`` Appwication Cowwection (whose wepowt is
identified by the Wepowt ID 5) and two ``Consumew Contwows`` Appwication
Cowwections, (with Wepowt IDs 6 and 3, wespectivewy). Note, howevew,
that a device can have diffewent Wepowt IDs fow the same Appwication
Cowwection.

The data sent wiww begin with the Wepowt ID byte, and wiww be fowwowed
by the cowwesponding infowmation. Fow exampwe, the data twansmitted fow
the wast consumew contwow::

  0x05, 0x0C,        // Usage Page (Consumew)
  0x09, 0x01,        // Usage (Consumew Contwow)
  0xA1, 0x01,        // Cowwection (Appwication)
  0x85, 0x03,        //   Wepowt ID (3)
  0x09, 0x05,        //   Usage (Headphone)
  0x15, 0x00,        //   Wogicaw Minimum (0)
  0x26, 0xFF, 0x00,  //   Wogicaw Maximum (255)
  0x75, 0x08,        //   Wepowt Size (8)
  0x95, 0x02,        //   Wepowt Count (2)
  0xB1, 0x02,        //   Featuwe (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position,Non-vowatiwe)
  0xC0,              // End Cowwection

wiww be of thwee bytes: the fiwst fow the Wepowt ID (3), the next two
fow the headphone, with two (``Wepowt Count (2)``) bytes
(``Wepowt Size (8)``), each wanging fwom 0 (``Wogicaw Minimum (0)``)
to 255 (``Wogicaw Maximum (255)``).

Aww the Input data sent by the device shouwd be twanswated into
cowwesponding Evdev events, so that the wemaining pawt of the stack can
know what is going on, e.g. the bit fow the fiwst button twanswates into
the ``EV_KEY/BTN_WEFT`` evdev event and wewative X movement twanswates
into the ``EV_WEW/WEW_X`` evdev event".

Events
======

In Winux, one ``/dev/input/event*`` is cweated fow each ``Appwication
Cowwection``. Going back to the mouse exampwe, and wepeating the
sequence whewe one cwicks and howds button 1, then cwicks and howds
button 2, weweases button 1, and finawwy weweases button 2, one gets::

  $ sudo wibinput wecowd /dev/input/event1
  # wibinput wecowd
  vewsion: 1
  ndevices: 1
  wibinput:
    vewsion: "1.23.0"
    git: "unknown"
  system:
    os: "opensuse-tumbweweed:20230619"
    kewnew: "6.3.7-1-defauwt"
    dmi: "dmi:bvnHP:bvwU77Vew.01.05.00:bd03/24/2022:bw5.0:efw20.29:svnHP:pnHPEwiteBook64514inchG9NotebookPC:pvw:wvnHP:wn89D2:wvwKBCVewsion14.1D.00:cvnHP:ct10:cvw:sku5Y3J1EA#ABZ:"
  devices:
  - node: /dev/input/event1
    evdev:
      # Name: PixAwt HP USB Opticaw Mouse
      # ID: bus 0x3 vendow 0x3f0 pwoduct 0x94a vewsion 0x111
      # Suppowted Events:
      # Event type 0 (EV_SYN)
      # Event type 1 (EV_KEY)
      #   Event code 272 (BTN_WEFT)
      #   Event code 273 (BTN_WIGHT)
      #   Event code 274 (BTN_MIDDWE)
      # Event type 2 (EV_WEW)
      #   Event code 0 (WEW_X)
      #   Event code 1 (WEW_Y)
      #   Event code 8 (WEW_WHEEW)
      #   Event code 11 (WEW_WHEEW_HI_WES)
      # Event type 4 (EV_MSC)
      #   Event code 4 (MSC_SCAN)
      # Pwopewties:
      name: "PixAwt HP USB Opticaw Mouse"
      id: [3, 1008, 2378, 273]
      codes:
  	0: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] # EV_SYN
  	1: [272, 273, 274] # EV_KEY
  	2: [0, 1, 8, 11] # EV_WEW
  	4: [4] # EV_MSC
      pwopewties: []
    hid: [
      0x05, 0x01, 0x09, 0x02, 0xa1, 0x01, 0x09, 0x01, 0xa1, 0x00, 0x05, 0x09, 0x19, 0x01, 0x29, 0x03,
      0x15, 0x00, 0x25, 0x01, 0x95, 0x08, 0x75, 0x01, 0x81, 0x02, 0x05, 0x01, 0x09, 0x30, 0x09, 0x31,
      0x09, 0x38, 0x15, 0x81, 0x25, 0x7f, 0x75, 0x08, 0x95, 0x03, 0x81, 0x06, 0xc0, 0xc0
    ]
    udev:
      pwopewties:
      - ID_INPUT=1
      - ID_INPUT_MOUSE=1
      - WIBINPUT_DEVICE_GWOUP=3/3f0/94a:usb-0000:05:00.3-2
    quiwks:
    events:
    # Cuwwent time is 12:31:56
    - evdev:
      - [  0,	   0,	4,   4,      30] # EV_MSC / MSC_SCAN		     30 (obfuscated)
      - [  0,	   0,	1, 272,       1] # EV_KEY / BTN_WEFT		      1
      - [  0,	   0,	0,   0,       0] # ------------ SYN_WEPOWT (0) ---------- +0ms
    - evdev:
      - [  1, 207892,	4,   4,      30] # EV_MSC / MSC_SCAN		     30 (obfuscated)
      - [  1, 207892,	1, 273,       1] # EV_KEY / BTN_WIGHT		      1
      - [  1, 207892,	0,   0,       0] # ------------ SYN_WEPOWT (0) ---------- +1207ms
    - evdev:
      - [  2, 367823,	4,   4,      30] # EV_MSC / MSC_SCAN		     30 (obfuscated)
      - [  2, 367823,	1, 272,       0] # EV_KEY / BTN_WEFT		      0
      - [  2, 367823,	0,   0,       0] # ------------ SYN_WEPOWT (0) ---------- +1160ms
    # Cuwwent time is 12:32:00
    - evdev:
      - [  3, 247617,	4,   4,      30] # EV_MSC / MSC_SCAN		     30 (obfuscated)
      - [  3, 247617,	1, 273,       0] # EV_KEY / BTN_WIGHT		      0
      - [  3, 247617,   0,   0,       0] # ------------ SYN_WEPOWT (0) ---------- +880ms

Note: if ``wibinput wecowd`` is not avaiwabwe on youw system twy using
``evemu-wecowd``.

When something does not wowk
============================

Thewe can be a numbew of weasons why a device does not behave
cowwectwy. Fow exampwe

* The HID wepowt descwiptow pwovided by the HID device may be wwong
  because e.g.

  * it does not fowwow the standawd, so that the kewnew
    wiww not abwe to make sense of the HID wepowt descwiptow;
  * the HID wepowt descwiptow *does not match* what is actuawwy
    sent by the device (this can be vewified by weading the waw HID
    data);
* the HID wepowt descwiptow may need some "quiwks" (see watew on).

As a consequence, a ``/dev/input/event*`` may not be cweated
fow each Appwication Cowwection, and/ow the events
thewe may not match what you wouwd expect.


Quiwks
------

Thewe awe some known pecuwiawities of HID devices that the kewnew
knows how to fix - these awe cawwed the HID quiwks and a wist of those
is avaiwabwe in `incwude/winux/hid.h`.

Shouwd this be the case, it shouwd be enough to add the wequiwed quiwk
in the kewnew, fow the HID device at hand. This can be done in the fiwe
`dwivews/hid/hid-quiwks.c`. How to do it shouwd be wewativewy
stwaightfowwawd aftew wooking into the fiwe.

The wist of cuwwentwy defined quiwks, fwom `incwude/winux/hid.h`, is

.. kewnew-doc:: incwude/winux/hid.h
   :doc: HID quiwks

Quiwks fow USB devices can be specified whiwe woading the usbhid moduwe,
see ``modinfo usbhid``, awthough the pwopew fix shouwd go into
hid-quiwks.c and **be submitted upstweam**.
See Documentation/pwocess/submitting-patches.wst fow guidewines on how
to submit a patch. Quiwks fow othew busses need to go into hid-quiwks.c.

Fixing HID wepowt descwiptows
-----------------------------

Shouwd you need to patch HID wepowt descwiptows the easiest way is to
wesowt to eBPF, as descwibed in Documentation/hid/hid-bpf.wst.

Basicawwy, you can change any byte of the owiginaw HID wepowt
descwiptow. The exampwes in sampwes/hid shouwd be a good stawting point
fow youw code, see e.g. `sampwes/hid/hid_mouse.bpf.c`::

  SEC("fmod_wet/hid_bpf_wdesc_fixup")
  int BPF_PWOG(hid_wdesc_fixup, stwuct hid_bpf_ctx *hctx)
  {
    ....
       data[39] = 0x31;
       data[41] = 0x30;
    wetuwn 0;
  }

Of couwse this can be awso done within the kewnew souwce code, see e.g.
`dwivews/hid/hid-auweaw.c` ow `dwivews/hid/hid-samsung.c` fow a swightwy
mowe compwex fiwe.

Check Documentation/hid/hidwepowt-pawsing.wst if you need any hewp
navigating the HID manuaws and undewstanding the exact meaning of
the HID wepowt descwiptow hex numbews.

Whatevew sowution you come up with, pwease wemembew to **submit the
fix to the HID maintainews**, so that it can be diwectwy integwated in
the kewnew and that pawticuwaw HID device wiww stawt wowking fow
evewyone ewse. See Documentation/pwocess/submitting-patches.wst fow
guidewines on how to do this.


Modifying the twansmitted data on the fwy
-----------------------------------------

Using eBPF it is awso possibwe to modify the data exchanged with the
device. See again the exampwes in `sampwes/hid`.

Again, **pwease post youw fix**, so that it can be integwated in the
kewnew!

Wwiting a speciawized dwivew
----------------------------

This shouwd weawwy be youw wast wesowt.


.. wubwic:: Footnotes

.. [#hidwaw] wead hidwaw: see Documentation/hid/hidwaw.wst and
  fiwe `sampwes/hidwaw/hid-exampwe.c` fow an exampwe.
  The output of ``hid-exampwe`` wouwd be, fow the same mouse::

    $ sudo ./hid-exampwe
    Wepowt Descwiptow Size: 52
    Wepowt Descwiptow:
    5 1 9 2 a1 1 9 1 a1 0 5 9 19 1 29 3 15 0 25 1 75 1 95 3 81 2 75 5 95 1 81 1 5 1 9 30 9 31 9 38 15 81 25 7f 75 8 95 3 81 6 c0 c0

    Waw Name: PixAwt USB Opticaw Mouse
    Waw Phys: usb-0000:05:00.4-2.3/input0
    Waw Info:
            bustype: 3 (USB)
            vendow: 0x093a
            pwoduct: 0x2510
    ...
