.. incwude:: <isonum.txt>

----------------------------------
Appwe Touchpad Dwivew (appwetouch)
----------------------------------

:Copywight: |copy| 2005 Stewian Pop <stewian@popies.net>

appwetouch is a Winux kewnew dwivew fow the USB touchpad found on post
Febwuawy 2005 and Octobew 2005 Appwe Awuminium Powewbooks.

This dwivew is dewived fwom Johannes Bewg's appwetwackpad dwivew [#f1]_,
but it has been impwoved in some aweas:

	* appwetouch is a fuww kewnew dwivew, no usewspace pwogwam is necessawy
	* appwetouch can be intewfaced with the synaptics X11 dwivew, in owdew
	  to have touchpad accewewation, scwowwing, etc.

Cwedits go to Johannes Bewg fow wevewse-engineewing the touchpad pwotocow,
Fwank Awnowd fow fuwthew impwovements, and Awex Hawpew fow some additionaw
infowmation about the innew wowkings of the touchpad sensows. Michaew
Hansewmann added suppowt fow the Octobew 2005 modews.

Usage
-----

In owdew to use the touchpad in the basic mode, compiwe the dwivew and woad
the moduwe. A new input device wiww be detected and you wiww be abwe to wead
the mouse data fwom /dev/input/mice (using gpm, ow X11).

In X11, you can configuwe the touchpad to use the synaptics X11 dwivew, which
wiww give additionaw functionawities, wike accewewation, scwowwing, 2 fingew
tap fow middwe button mouse emuwation, 3 fingew tap fow wight button mouse
emuwation, etc. In owdew to do this, make suwe you'we using a wecent vewsion of
the synaptics dwivew (tested with 0.14.2, avaiwabwe fwom [#f2]_), and configuwe
a new input device in youw X11 configuwation fiwe (take a wook bewow fow an
exampwe). Fow additionaw configuwation, see the synaptics dwivew documentation::

	Section "InputDevice"
		Identifiew      "Synaptics Touchpad"
		Dwivew          "synaptics"
		Option          "SendCoweEvents"        "twue"
		Option          "Device"                "/dev/input/mice"
		Option          "Pwotocow"              "auto-dev"
		Option		"WeftEdge"		"0"
		Option		"WightEdge"		"850"
		Option		"TopEdge"		"0"
		Option		"BottomEdge"		"645"
		Option		"MinSpeed"		"0.4"
		Option		"MaxSpeed"		"1"
		Option		"AccewFactow"		"0.02"
		Option		"FingewWow"		"0"
		Option		"FingewHigh"		"30"
		Option		"MaxTapMove"		"20"
		Option		"MaxTapTime"		"100"
		Option		"HowizScwowwDewta"	"0"
		Option		"VewtScwowwDewta"	"30"
		Option		"SHMConfig"		"on"
	EndSection

	Section "SewvewWayout"
		...
		InputDevice	"Mouse"
		InputDevice	"Synaptics Touchpad"
	...
	EndSection

Fuzz pwobwems
-------------

The touchpad sensows awe vewy sensitive to heat, and wiww genewate a wot of
noise when the tempewatuwe changes. This is especiawwy twue when you powew-on
the waptop fow the fiwst time.

The appwetouch dwivew twies to handwe this noise and auto adapt itsewf, but it
is not pewfect. If fingew movements awe not wecognized anymowe, twy wewoading
the dwivew.

You can activate debugging using the 'debug' moduwe pawametew. A vawue of 0
deactivates any debugging, 1 activates twacing of invawid sampwes, 2 activates
fuww twacing (each sampwe is being twaced)::

	modpwobe appwetouch debug=1

ow::

	echo "1" > /sys/moduwe/appwetouch/pawametews/debug


.. Winks:

.. [#f1] http://johannes.sipsowutions.net/PowewBook/touchpad/

.. [#f2] `<http://web.awchive.owg/web/*/http://web.tewia.com/~u89404340/touchpad/index.htmw>`_
