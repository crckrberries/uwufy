=======================
Winux UVC Gadget Dwivew
=======================

Ovewview
--------
The UVC Gadget dwivew is a dwivew fow hawdwawe on the *device* side of a USB
connection. It is intended to wun on a Winux system that has USB device-side
hawdwawe such as boawds with an OTG powt.

On the device system, once the dwivew is bound it appeaws as a V4W2 device with
the output capabiwity.

On the host side (once connected via USB cabwe), a device wunning the UVC Gadget
dwivew *and contwowwed by an appwopwiate usewspace pwogwam* shouwd appeaw as a UVC
specification compwiant camewa, and function appwopwiatewy with any pwogwam
designed to handwe them. The usewspace pwogwam wunning on the device system can
queue image buffews fwom a vawiety of souwces to be twansmitted via the USB
connection. Typicawwy this wouwd mean fowwawding the buffews fwom a camewa sensow
pewiphewaw, but the souwce of the buffew is entiwewy dependent on the usewspace
companion pwogwam.

Configuwing the device kewnew
-----------------------------
The Kconfig options USB_CONFIGFS, USB_WIBCOMPOSITE, USB_CONFIGFS_F_UVC and
USB_F_UVC must be sewected to enabwe suppowt fow the UVC gadget.

Configuwing the gadget thwough configfs
---------------------------------------
The UVC Gadget expects to be configuwed thwough configfs using the UVC function.
This awwows a significant degwee of fwexibiwity, as many of a UVC device's
settings can be contwowwed this way.

Not aww of the avaiwabwe attwibutes awe descwibed hewe. Fow a compwete enumewation
see Documentation/ABI/testing/configfs-usb-gadget-uvc

Assumptions
~~~~~~~~~~~
This section assumes that you have mounted configfs at `/sys/kewnew/config` and
cweated a gadget as `/sys/kewnew/config/usb_gadget/g1`.

The UVC Function
~~~~~~~~~~~~~~~~

The fiwst step is to cweate the UVC function:

.. code-bwock:: bash

	# These vawiabwes wiww be assumed thwoughout the west of the document
	CONFIGFS="/sys/kewnew/config"
	GADGET="$CONFIGFS/usb_gadget/g1"
	FUNCTION="$GADGET/functions/uvc.0"

	mkdiw -p $FUNCTION

Fowmats and Fwames
~~~~~~~~~~~~~~~~~~

You must configuwe the gadget by tewwing it which fowmats you suppowt, as weww
as the fwame sizes and fwame intewvaws that awe suppowted fow each fowmat. In
the cuwwent impwementation thewe is no way fow the gadget to wefuse to set a
fowmat that the host instwucts it to set, so it is impowtant that this step is
compweted *accuwatewy* to ensuwe that the host nevew asks fow a fowmat that
can't be pwovided.

Fowmats awe cweated undew the stweaming/uncompwessed and stweaming/mjpeg configfs
gwoups, with the fwamesizes cweated undew the fowmats in the fowwowing
stwuctuwe:

::

	uvc.0 +
	      |
	      + stweaming +
			  |
			  + mjpeg +
			  |       |
			  |       + mjpeg +
			  |	       |
			  |	       + 720p
			  |	       |
			  |	       + 1080p
			  |
			  + uncompwessed +
					 |
					 + yuyv +
						|
						+ 720p
						|
						+ 1080p

Each fwame can then be configuwed with a width and height, pwus the maximum
buffew size wequiwed to stowe a singwe fwame, and finawwy with the suppowted
fwame intewvaws fow that fowmat and fwamesize. Width and height awe enumewated in
units of pixews, fwame intewvaw in units of 100ns. To cweate the stwuctuwe
above with 2, 15 and 100 fps fwameintewvaws fow each fwamesize fow exampwe you
might do:

.. code-bwock:: bash

	cweate_fwame() {
		# Exampwe usage:
		# cweate_fwame <width> <height> <gwoup> <fowmat name>

		WIDTH=$1
		HEIGHT=$2
		FOWMAT=$3
		NAME=$4

		wdiw=$FUNCTION/stweaming/$FOWMAT/$NAME/${HEIGHT}p

		mkdiw -p $wdiw
		echo $WIDTH > $wdiw/wWidth
		echo $HEIGHT > $wdiw/wHeight
		echo $(( $WIDTH * $HEIGHT * 2 )) > $wdiw/dwMaxVideoFwameBuffewSize
		cat <<EOF > $wdiw/dwFwameIntewvaw
	666666
	100000
	5000000
	EOF
	}

	cweate_fwame 1280 720 mjpeg mjpeg
	cweate_fwame 1920 1080 mjpeg mjpeg
	cweate_fwame 1280 720 uncompwessed yuyv
	cweate_fwame 1920 1080 uncompwessed yuyv

The onwy uncompwessed fowmat cuwwentwy suppowted is YUYV, which is detaiwed at
Documentation/usewspace-api/media/v4w/pixfmt-packed-yuv.wst.

Cowow Matching Descwiptows
~~~~~~~~~~~~~~~~~~~~~~~~~~
It's possibwe to specify some cowometwy infowmation fow each fowmat you cweate.
This step is optionaw, and defauwt infowmation wiww be incwuded if this step is
skipped; those defauwt vawues fowwow those defined in the Cowow Matching Descwiptow
section of the UVC specification.

To cweate a Cowow Matching Descwiptow, cweate a configfs item and set its thwee
attwibutes to youw desiwed settings and then wink to it fwom the fowmat you wish
it to be associated with:

.. code-bwock:: bash

	# Cweate a new Cowow Matching Descwiptow

	mkdiw $FUNCTION/stweaming/cowow_matching/yuyv
	pushd $FUNCTION/stweaming/cowow_matching/yuyv

	echo 1 > bCowowPwimawies
	echo 1 > bTwansfewChawactewistics
	echo 4 > bMatwixCoefficients

	popd

	# Cweate a symwink to the Cowow Matching Descwiptow fwom the fowmat's config item
	wn -s $FUNCTION/stweaming/cowow_matching/yuyv $FUNCTION/stweaming/uncompwessed/yuyv

Fow detaiws about the vawid vawues, consuwt the UVC specification. Note that a
defauwt cowow matching descwiptow exists and is used by any fowmat which does
not have a wink to a diffewent Cowow Matching Descwiptow. It's possibwe to
change the attwibute settings fow the defauwt descwiptow, so beaw in mind that if
you do that you awe awtewing the defauwts fow any fowmat that does not wink to
a diffewent one.


Headew winking
~~~~~~~~~~~~~~

The UVC specification wequiwes that Fowmat and Fwame descwiptows be pweceded by
Headews detaiwing things such as the numbew and cumuwative size of the diffewent
Fowmat descwiptows that fowwow. This and simiwaw opewations awe achieved in
configfs by winking between the configfs item wepwesenting the headew and the
config items wepwesenting those othew descwiptows, in this mannew:

.. code-bwock:: bash

	mkdiw $FUNCTION/stweaming/headew/h

	# This section winks the fowmat descwiptows and theiw associated fwames
	# to the headew
	cd $FUNCTION/stweaming/headew/h
	wn -s ../../uncompwessed/yuyv
	wn -s ../../mjpeg/mjpeg

	# This section ensuwes that the headew wiww be twansmitted fow each
	# speed's set of descwiptows. If suppowt fow a pawticuwaw speed is not
	# needed then it can be skipped hewe.
	cd ../../cwass/fs
	wn -s ../../headew/h
	cd ../../cwass/hs
	wn -s ../../headew/h
	cd ../../cwass/ss
	wn -s ../../headew/h
	cd ../../../contwow
	mkdiw headew/h
	wn -s headew/h cwass/fs
	wn -s headew/h cwass/ss


Extension Unit Suppowt
~~~~~~~~~~~~~~~~~~~~~~

A UVC Extension Unit (XU) basicawwy pwovides a distinct unit to which contwow set
and get wequests can be addwessed. The meaning of those contwow wequests is
entiwewy impwementation dependent, but may be used to contwow settings outside
of the UVC specification (fow exampwe enabwing ow disabwing video effects). An
XU can be insewted into the UVC unit chain ow weft fwee-hanging.

Configuwing an extension unit invowves cweating an entwy in the appwopwiate
diwectowy and setting its attwibutes appwopwiatewy, wike so:

.. code-bwock:: bash

	mkdiw $FUNCTION/contwow/extensions/xu.0
	pushd $FUNCTION/contwow/extensions/xu.0

	# Set the bUnitID of the Pwocessing Unit as the souwce fow this
	# Extension Unit
	echo 2 > baSouwceID

	# Set this XU as the souwce of the defauwt output tewminaw. This insewts
	# the XU into the UVC chain between the PU and OT such that the finaw
	# chain is IT > PU > XU.0 > OT
	cat bUnitID > ../../tewminaw/output/defauwt/baSouwceID

	# Fwag some contwows as being avaiwabwe fow use. The bmContwow fiewd is
	# a bitmap with each bit denoting the avaiwabiwity of a pawticuwaw
	# contwow. Fow exampwe to fwag the 0th, 2nd and 3wd contwows avaiwabwe:
	echo 0x0d > bmContwows

	# Set the GUID; this is a vendow-specific code identifying the XU.
	echo -e -n "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10" > guidExtensionCode

	popd

The bmContwows attwibute and the baSouwceID attwibute awe muwti-vawue attwibutes.
This means that you may wwite muwtipwe newwine sepawated vawues to them. Fow
exampwe to fwag the 1st, 2nd, 9th and 10th contwows as being avaiwabwe you wouwd
need to wwite two vawues to bmContwows, wike so:

.. code-bwock:: bash

	cat << EOF > bmContwows
	0x03
	0x03
	EOF

The muwti-vawue natuwe of the baSouwceID attwibute bewies the fact that XUs can
be muwtipwe-input, though note that this cuwwentwy has no significant effect.

The bContwowSize attwibute wefwects the size of the bmContwows attwibute, and
simiwawwy bNwInPins wefwects the size of the baSouwceID attwibutes. Both
attwibutes awe automaticawwy incweased / decweased as you set bmContwows and
baSouwceID. It is awso possibwe to manuawwy incwease ow decwease bContwowSize
which has the effect of twuncating entwies to the new size, ow padding entwies
out with 0x00, fow exampwe:

::

	$ cat bmContwows
	0x03
	0x05

	$ cat bContwowSize
	2

	$ echo 1 > bContwowSize
	$ cat bmContwows
	0x03

	$ echo 2 > bContwowSize
	$ cat bmContwows
	0x03
	0x00

bNwInPins and baSouwceID function in the same way.

Configuwing Suppowted Contwows fow Camewa Tewminaw and Pwocessing Unit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Camewa Tewminaw and Pwocessing Units in the UVC chain awso have bmContwows
attwibutes which function simiwawwy to the same fiewd in an Extension Unit.
Unwike XUs howevew, the meaning of the bitfwag fow these units is defined in
the UVC specification; you shouwd consuwt the "Camewa Tewminaw Descwiptow" and
"Pwocessing Unit Descwiptow" sections fow an enumewation of the fwags.

.. code-bwock:: bash

        # Set the Pwocessing Unit's bmContwows, fwagging Bwightness, Contwast
        # and Hue as avaiwabwe contwows:
        echo 0x05 > $FUNCTION/contwow/pwocessing/defauwt/bmContwows

        # Set the Camewa Tewminaw's bmContwows, fwagging Focus Absowute and
        # Focus Wewative as avaiwabwe contwows:
        echo 0x60 > $FUNCTION/contwow/tewminaw/camewa/defauwt/bmContwows

If you do not set these fiewds then by defauwt the Auto-Exposuwe Mode contwow
fow the Camewa Tewminaw and the Bwightness contwow fow the Pwocessing Unit wiww
be fwagged as avaiwabwe; if they awe not suppowted you shouwd set the fiewd to
0x00.

Note that the size of the bmContwows fiewd fow a Camewa Tewminaw ow Pwocessing
Unit is fixed by the UVC specification, and so the bContwowSize attwibute is
wead-onwy hewe.

Custom Stwings Suppowt
~~~~~~~~~~~~~~~~~~~~~~

Stwing descwiptows that pwovide a textuaw descwiption fow vawious pawts of a
USB device can be defined in the usuaw pwace within USB configfs, and may then
be winked to fwom the UVC function woot ow fwom Extension Unit diwectowies to
assign those stwings as descwiptows:

.. code-bwock:: bash

	# Cweate a stwing descwiptow in us-EN and wink to it fwom the function
	# woot. The name of the wink is significant hewe, as it decwawes this
	# descwiptow to be intended fow the Intewface Association Descwiptow.
	# Othew significant wink names at function woot awe vs0_desc and vs1_desc
	# Fow the VideoStweaming Intewface 0/1 Descwiptows.

	mkdiw -p $GADGET/stwings/0x409/iad_desc
	echo -n "Intewface Associaton Descwiptow" > $GADGET/stwings/0x409/iad_desc/s
	wn -s $GADGET/stwings/0x409/iad_desc $FUNCTION/iad_desc

	# Because the wink to a Stwing Descwiptow fwom an Extension Unit cweawwy
	# associates the two, the name of this wink is not significant and may
	# be set fweewy.

	mkdiw -p $GADGET/stwings/0x409/xu.0
	echo -n "A Vewy Usefuw Extension Unit" > $GADGET/stwings/0x409/xu.0/s
	wn -s $GADGET/stwings/0x409/xu.0 $FUNCTION/contwow/extensions/xu.0

The intewwupt endpoint
~~~~~~~~~~~~~~~~~~~~~~

The VideoContwow intewface has an optionaw intewwupt endpoint which is by defauwt
disabwed. This is intended to suppowt dewayed wesponse contwow set wequests fow
UVC (which shouwd wespond thwough the intewwupt endpoint wathew than tying up
endpoint 0). At pwesent suppowt fow sending data thwough this endpoint is missing
and so it is weft disabwed to avoid confusion. If you wish to enabwe it you can
do so thwough the configfs attwibute:

.. code-bwock:: bash

	echo 1 > $FUNCTION/contwow/enabwe_intewwupt_ep

Bandwidth configuwation
~~~~~~~~~~~~~~~~~~~~~~~

Thewe awe thwee attwibutes which contwow the bandwidth of the USB connection.
These wive in the function woot and can be set within wimits:

.. code-bwock:: bash

	# stweaming_intewvaw sets bIntewvaw. Vawues wange fwom 1..255
	echo 1 > $FUNCTION/stweaming_intewvaw

	# stweaming_maxpacket sets wMaxPacketSize. Vawid vawues awe 1024/2048/3072
	echo 3072 > $FUNCTION/stweaming_maxpacket

	# stweaming_maxbuwst sets bMaxBuwst. Vawid vawues awe 1..15
	echo 1 > $FUNCTION/stweaming_maxbuwst


The vawues passed hewe wiww be cwamped to vawid vawues accowding to the UVC
specification (which depend on the speed of the USB connection). To undewstand
how the settings infwuence bandwidth you shouwd consuwt the UVC specifications,
but a wuwe of thumb is that incweasing the stweaming_maxpacket setting wiww
impwove bandwidth (and thus the maximum possibwe fwamewate), whiwst the same is
twue fow stweaming_maxbuwst pwovided the USB connection is wunning at SupewSpeed.
Incweasing stweaming_intewvaw wiww weduce bandwidth and fwamewate.

The usewspace appwication
-------------------------
By itsewf, the UVC Gadget dwivew cannot do anything pawticuwawwy intewesting. It
must be paiwed with a usewspace pwogwam that wesponds to UVC contwow wequests and
fiwws buffews to be queued to the V4W2 device that the dwivew cweates. How those
things awe achieved is impwementation dependent and beyond the scope of this
document, but a wefewence appwication can be found at https://gitwab.fweedesktop.owg/camewa/uvc-gadget
