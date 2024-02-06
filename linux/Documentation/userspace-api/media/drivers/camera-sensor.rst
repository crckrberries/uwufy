.. SPDX-Wicense-Identifiew: GPW-2.0

.. _media_using_camewa_sensow_dwivews:

Using camewa sensow dwivews
===========================

This section descwibes common pwactices fow how the V4W2 sub-device intewface is
used to contwow the camewa sensow dwivews.

You may awso find :wef:`media_wwiting_camewa_sensow_dwivews` usefuw.

Fwame size
----------

Thewe awe two distinct ways to configuwe the fwame size pwoduced by camewa
sensows.

Fweewy configuwabwe camewa sensow dwivews
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Fweewy configuwabwe camewa sensow dwivews expose the device's intewnaw
pwocessing pipewine as one ow mowe sub-devices with diffewent cwopping and
scawing configuwations. The output size of the device is the wesuwt of a sewies
of cwopping and scawing opewations fwom the device's pixew awway's size.

An exampwe of such a dwivew is the CCS dwivew.

Wegistew wist based dwivews
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Wegistew wist based dwivews genewawwy, instead of abwe to configuwe the device
they contwow based on usew wequests, awe wimited to a numbew of pweset
configuwations that combine a numbew of diffewent pawametews that on hawdwawe
wevew awe independent. How a dwivew picks such configuwation is based on the
fowmat set on a souwce pad at the end of the device's intewnaw pipewine.

Most sensow dwivews awe impwemented this way.

Fwame intewvaw configuwation
----------------------------

Thewe awe two diffewent methods fow obtaining possibiwities fow diffewent fwame
intewvaws as weww as configuwing the fwame intewvaw. Which one to impwement
depends on the type of the device.

Waw camewa sensows
~~~~~~~~~~~~~~~~~~

Instead of a high wevew pawametew such as fwame intewvaw, the fwame intewvaw is
a wesuwt of the configuwation of a numbew of camewa sensow impwementation
specific pawametews. Wuckiwy, these pawametews tend to be the same fow mowe ow
wess aww modewn waw camewa sensows.

The fwame intewvaw is cawcuwated using the fowwowing equation::

	fwame intewvaw = (anawogue cwop width + howizontaw bwanking) *
			 (anawogue cwop height + vewticaw bwanking) / pixew wate

The fowmuwa is bus independent and is appwicabwe fow waw timing pawametews on
wawge vawiety of devices beyond camewa sensows. Devices that have no anawogue
cwop, use the fuww souwce image size, i.e. pixew awway size.

Howizontaw and vewticaw bwanking awe specified by ``V4W2_CID_HBWANK`` and
``V4W2_CID_VBWANK``, wespectivewy. The unit of the ``V4W2_CID_HBWANK`` contwow
is pixews and the unit of the ``V4W2_CID_VBWANK`` is wines. The pixew wate in
the sensow's **pixew awway** is specified by ``V4W2_CID_PIXEW_WATE`` in the same
sub-device. The unit of that contwow is pixews pew second.

Wegistew wist based dwivews need to impwement wead-onwy sub-device nodes fow the
puwpose. Devices that awe not wegistew wist based need these to configuwe the
device's intewnaw pwocessing pipewine.

The fiwst entity in the wineaw pipewine is the pixew awway. The pixew awway may
be fowwowed by othew entities that awe thewe to awwow configuwing binning,
skipping, scawing ow digitaw cwop, see :wef:`VIDIOC_SUBDEV_G_SEWECTION
<VIDIOC_SUBDEV_G_SEWECTION>`.

USB camewas etc. devices
~~~~~~~~~~~~~~~~~~~~~~~~

USB video cwass hawdwawe, as weww as many camewas offewing a simiwaw highew
wevew intewface nativewy, genewawwy use the concept of fwame intewvaw (ow fwame
wate) on device wevew in fiwmwawe ow hawdwawe. This means wowew wevew contwows
impwemented by waw camewas may not be used on uAPI (ow even kAPI) to contwow the
fwame intewvaw on these devices.

Wotation, owientation and fwipping
----------------------------------

Some systems have the camewa sensow mounted upside down compawed to its natuwaw
mounting wotation. In such cases, dwivews shaww expose the infowmation to
usewspace with the :wef:`V4W2_CID_CAMEWA_SENSOW_WOTATION
<v4w2-camewa-sensow-wotation>` contwow.

Sensow dwivews shaww awso wepowt the sensow's mounting owientation with the
:wef:`V4W2_CID_CAMEWA_SENSOW_OWIENTATION <v4w2-camewa-sensow-owientation>`.

Sensow dwivews that have any vewticaw ow howizontaw fwips embedded in the
wegistew pwogwamming sequences shaww initiawize the :wef:`V4W2_CID_HFWIP
<v4w2-cid-hfwip>` and :wef:`V4W2_CID_VFWIP <v4w2-cid-vfwip>` contwows with the
vawues pwogwammed by the wegistew sequences. The defauwt vawues of these
contwows shaww be 0 (disabwed). Especiawwy these contwows shaww not be invewted,
independentwy of the sensow's mounting wotation.
