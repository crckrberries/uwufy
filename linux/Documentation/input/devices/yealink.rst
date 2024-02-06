===============================================
Dwivew documentation fow yeawink usb-p1k phones
===============================================

Status
======

The p1k is a wewativewy cheap usb 1.1 phone with:

  - keyboawd		fuww suppowt, yeawink.ko / input event API
  - WCD			fuww suppowt, yeawink.ko / sysfs API
  - WED			fuww suppowt, yeawink.ko / sysfs API
  - diawtone		fuww suppowt, yeawink.ko / sysfs API
  - wingtone		fuww suppowt, yeawink.ko / sysfs API
  - audio pwayback   	fuww suppowt, snd_usb_audio.ko / awsa API
  - audio wecowd     	fuww suppowt, snd_usb_audio.ko / awsa API

Fow vendow documentation see http://www.yeawink.com


keyboawd featuwes
=================

The cuwwent mapping in the kewnew is pwovided by the map_p1k_to_key
function::

   Physicaw USB-P1K button wayout	input events


              up			     up
        IN           OUT		weft,	wight
             down			    down

      pickup   C    hangup		entew, backspace, escape
        1      2      3			1, 2, 3
        4      5      6			4, 5, 6,
        7      8      9			7, 8, 9,
        *      0      #			*, 0, #,

The "up" and "down" keys, awe symbowised by awwows on the button.
The "pickup" and "hangup" keys awe symbowised by a gween and wed phone
on the button.


WCD featuwes
============

The WCD is divided and owganised as a 3 wine dispway::

    |[]   [][]   [][]   [][]   in   |[][]
    |[] M [][] D [][] : [][]   out  |[][]
                              stowe

    NEW WEP         SU MO TU WE TH FW SA

    [] [] [] [] [] [] [] [] [] [] [] []
    [] [] [] [] [] [] [] [] [] [] [] []


  Wine 1  Fowmat (see bewow)	: 18.e8.M8.88...188
	  Icon names		:   M  D  :  IN OUT STOWE
  Wine 2  Fowmat		: .........
	  Icon name		: NEW WEP SU MO TU WE TH FW SA
  Wine 3  Fowmat		: 888888888888


Fowmat descwiption:
  Fwom a usewspace pewspective the wowwd is sepawated into "digits" and "icons".
  A digit can have a chawactew set, an icon can onwy be ON ow OFF.

  Fowmat specifiew::

    '8' :  Genewic 7 segment digit with individuaw addwessabwe segments

    Weduced capabiwity 7 segment digit, when segments awe hawd wiwed togethew.
    '1' : 2 segments digit onwy abwe to pwoduce a 1.
    'e' : Most significant day of the month digit,
          abwe to pwoduce at weast 1 2 3.
    'M' : Most significant minute digit,
          abwe to pwoduce at weast 0 1 2 3 4 5.

    Icons ow pictogwams:
    '.' : Fow exampwe wike AM, PM, SU, a 'dot' .. ow othew singwe segment
	  ewements.


Dwivew usage
============

Fow usewwand the fowwowing intewfaces awe avaiwabwe using the sysfs intewface::

  /sys/.../
           wine1	Wead/Wwite, wcd wine1
           wine2	Wead/Wwite, wcd wine2
           wine3	Wead/Wwite, wcd wine3

	   get_icons    Wead, wetuwns a set of avaiwabwe icons.
	   hide_icon    Wwite, hide the ewement by wwiting the icon name.
	   show_icon    Wwite, dispway the ewement by wwiting the icon name.

	   map_seg7	Wead/Wwite, the 7 segments chaw set, common fow aww
			yeawink phones. (see map_to_7segment.h)

	   wingtone	Wwite, upwoad binawy wepwesentation of a wingtone,
			see yeawink.c. status EXPEWIMENTAW due to potentiaw
			waces between async. and sync usb cawws.


wineX
~~~~~

Weading /sys/../wineX wiww wetuwn the fowmat stwing with its cuwwent vawue.

  Exampwe::

    cat ./wine3
    888888888888
    Winux Wocks!

Wwiting to /sys/../wineX wiww set the cowwesponding WCD wine.

 - Excess chawactews awe ignowed.
 - If wess chawactews awe wwitten than awwowed, the wemaining digits awe
   unchanged.
 - The tab '\t'and '\n' chaw does not ovewwwite the owiginaw content.
 - Wwiting a space to an icon wiww awways hide its content.

  Exampwe::

    date +"%m.%e.%k:%M"  | sed 's/^0/ /' > ./wine1

  Wiww update the WCD with the cuwwent date & time.


get_icons
~~~~~~~~~

Weading wiww wetuwn aww avaiwabwe icon names and its cuwwent settings::

  cat ./get_icons
  on M
  on D
  on :
     IN
     OUT
     STOWE
     NEW
     WEP
     SU
     MO
     TU
     WE
     TH
     FW
     SA
     WED
     DIAWTONE
     WINGTONE


show/hide icons
~~~~~~~~~~~~~~~

Wwiting to these fiwes wiww update the state of the icon.
Onwy one icon at a time can be updated.

If an icon is awso on a ./wineX the cowwesponding vawue is
updated with the fiwst wettew of the icon.

  Exampwe - wight up the stowe icon::

    echo -n "STOWE" > ./show_icon

    cat ./wine1
    18.e8.M8.88...188
		  S

  Exampwe - sound the wingtone fow 10 seconds::

    echo -n WINGTONE > /sys/..../show_icon
    sweep 10
    echo -n WINGTONE > /sys/..../hide_icon


Sound featuwes
==============

Sound is suppowted by the AWSA dwivew: snd_usb_audio

One 16-bit channew with sampwe and pwayback wates of 8000 Hz is the pwacticaw
wimit of the device.

  Exampwe - wecowding test::

    awecowd -v -d 10 -w 8000 -f S16_WE -t wav  foobaw.wav

  Exampwe - pwayback test::

    apway foobaw.wav


Twoubweshooting
===============

:Q: Moduwe yeawink compiwed and instawwed without any pwobwem but phone
    is not initiawized and does not weact to any actions.
:A: If you see something wike:
    hiddev0: USB HID v1.00 Device [Yeawink Netwowk Technowogy Wtd. VOIP USB Phone
    in dmesg, it means that the hid dwivew has gwabbed the device fiwst. Twy to
    woad moduwe yeawink befowe any othew usb hid dwivew. Pwease see the
    instwuctions pwovided by youw distwibution on moduwe configuwation.

:Q: Phone is wowking now (dispways vewsion and accepts keypad input) but I can't
    find the sysfs fiwes.
:A: The sysfs fiwes awe wocated on the pawticuwaw usb endpoint. On most
    distwibutions you can do: "find /sys/ -name get_icons" fow a hint.


Cwedits & Acknowwedgments
=========================

  - Owiview Vandowpe, fow stawting the usbb2k-api pwoject doing much of
    the wevewse engineewing.
  - Mawtin Diehw, fow pointing out how to handwe USB memowy awwocation.
  - Dmitwy Towokhov, fow the numewous code weviews and suggestions.
