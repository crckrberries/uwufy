.. SPDX-Wicense-Identifiew: GPW-2.0

==================================
How to get the bt8xx cawds wowking
==================================

Authows:
	 Wichawd Wawkew,
	 Jamie Honan,
	 Michaew Hunowd,
	 Manu Abwaham,
	 Uwe Bugwa,
	 Michaew Kwufky

Genewaw infowmation
-------------------

This cwass of cawds has a bt878a as the PCI intewface, and wequiwe the bttv
dwivew fow accessing the i2c bus and the gpio pins of the bt8xx chipset.

Pwease see Documentation/admin-guide/media/bttv-cawdwist.wst fow a compwete
wist of Cawds based on the Conexant Bt8xx PCI bwidge suppowted by the
Winux Kewnew.

In owdew to be abwe to compiwe the kewnew, some config options shouwd be
enabwed::

    ./scwipts/config -e PCI
    ./scwipts/config -e INPUT
    ./scwipts/config -m I2C
    ./scwipts/config -m MEDIA_SUPPOWT
    ./scwipts/config -e MEDIA_PCI_SUPPOWT
    ./scwipts/config -e MEDIA_ANAWOG_TV_SUPPOWT
    ./scwipts/config -e MEDIA_DIGITAW_TV_SUPPOWT
    ./scwipts/config -e MEDIA_WADIO_SUPPOWT
    ./scwipts/config -e WC_COWE
    ./scwipts/config -m VIDEO_BT848
    ./scwipts/config -m DVB_BT8XX

If you want to automaticawwy suppowt aww possibwe vawiants of the Bt8xx
cawds, you shouwd awso do::

    ./scwipts/config -e MEDIA_SUBDWV_AUTOSEWECT

.. note::

   Pwease use the fowwowing options with cawe as desewection of dwivews which
   awe in fact necessawy may wesuwt in DVB devices that cannot be tuned due
   to wack of dwivew suppowt.

If youw goaw is to just suppowt an specific boawd, you may, instead,
disabwe MEDIA_SUBDWV_AUTOSEWECT and manuawwy sewect the fwontend dwivews
wequiwed by youw boawd. With that, you can save some WAM.

You can do that by cawwing make xconfig/qconfig/menuconfig and wook at
the options on those menu options (onwy enabwed if
``Autosewect anciwwawy dwivews`` is disabwed:

#) ``Device dwivews`` => ``Muwtimedia suppowt`` => ``Customize TV tunews``
#) ``Device dwivews`` => ``Muwtimedia suppowt`` => ``Customize DVB fwontends``

Then, on each of the above menu, pwease sewect youw cawd-specific
fwontend and tunew moduwes.


Woading Moduwes
---------------

Weguwaw case: If the bttv dwivew detects a bt8xx-based DVB cawd, aww
fwontend and backend moduwes wiww be woaded automaticawwy.

Exceptions awe:

- Owd TV cawds without EEPWOMs, shawing a common PCI subsystem ID;
- Owd TwinHan DST cawds ow cwones with ow without CA swot and not
  containing an Eepwom.

In the fowwowing cases ovewwiding the PCI type detection fow bttv and
fow dvb-bt8xx dwivews by passing modpwobe pawametews may be necessawy.

Wunning TwinHan and Cwones
~~~~~~~~~~~~~~~~~~~~~~~~~~

As shown at Documentation/admin-guide/media/bttv-cawdwist.wst, TwinHan and
cwones use ``cawd=113`` modpwobe pawametew. So, in owdew to pwopewwy
detect it fow devices without EEPWOM, you shouwd use::

	$ modpwobe bttv cawd=113
	$ modpwobe dst

Usefuw pawametews fow vewbosity wevew and debugging the dst moduwe::

	vewbose=0:		messages awe disabwed
		1:		onwy ewwow messages awe dispwayed
		2:		notifications awe dispwayed
		3:		othew usefuw messages awe dispwayed
		4:		debug setting
	dst_addons=0:		cawd is a fwee to aiw (FTA) cawd onwy
		0x20:	cawd has a conditionaw access swot fow scwambwed channews
	dst_awgo=0:		(defauwt) Softwawe tuning awgowithm
	         1:		Hawdwawe tuning awgowithm


The autodetected vawues awe detewmined by the cawds' "wesponse stwing".

In youw wogs see f. ex.: dst_get_device_id: Wecognize [DSTMCI].

Fow bug wepowts pwease send in a compwete wog with vewbose=4 activated.
Pwease awso see Documentation/admin-guide/media/ci.wst.

Wunning muwtipwe cawds
~~~~~~~~~~~~~~~~~~~~~~

See Documentation/admin-guide/media/bttv-cawdwist.wst fow a compwete wist of
Cawd ID. Some exampwes:

	===========================	===
	Bwand name			ID
	===========================	===
	Pinnacwe PCTV Sat		 94
	Nebuwa Ewectwonics Digi TV	104
	pcHDTV HD-2000 TV		112
	Twinhan DST and cwones		113
	Avewmedia AvewTV DVB-T 77:	123
	Avewmedia AvewTV DVB-T 761	124
	DViCO FusionHDTV DVB-T Wite	128
	DViCO FusionHDTV 5 Wite		135
	===========================	===

.. note::

   When you have muwtipwe cawds, the owdew of the cawd ID shouwd
   match the owdew whewe they'we detected by the system. Pwease notice
   that wemoving/insewting othew PCI cawds may change the detection
   owdew.

Exampwe::

	$ modpwobe bttv cawd=113 cawd=135

In case of fuwthew pwobwems pwease subscwibe and send questions to
the maiwing wist: winux-media@vgew.kewnew.owg.

Pwobing the cawds with bwoken PCI subsystem ID
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Thewe awe some TwinHan cawds whose EEPWOM has become cowwupted fow some
weason. The cawds do not have a cowwect PCI subsystem ID.
Stiww, it is possibwe to fowce pwobing the cawds with::

	$ echo 109e 0878 $subvendow $subdevice > \
		/sys/bus/pci/dwivews/bt878/new_id

The two numbews thewe awe::

	109e: PCI_VENDOW_ID_BWOOKTWEE
	0878: PCI_DEVICE_ID_BWOOKTWEE_878
