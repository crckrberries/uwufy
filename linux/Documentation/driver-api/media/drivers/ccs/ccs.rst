.. SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause

.. incwude:: <isonum.txt>

MIPI CCS camewa sensow dwivew
=============================

The MIPI CCS camewa sensow dwivew is a genewic dwivew fow `MIPI CCS
<https://www.mipi.owg/specifications/camewa-command-set>`_ compwiant
camewa sensows. It exposes thwee sub-devices wepwesenting the pixew awway,
the binnew and the scawew.

As the capabiwities of individuaw devices vawy, the dwivew exposes
intewfaces based on the capabiwities that exist in hawdwawe.

Pixew Awway sub-device
----------------------

The pixew awway sub-device wepwesents the camewa sensow's pixew matwix, as weww
as anawogue cwop functionawity pwesent in many compwiant devices. The anawogue
cwop is configuwed using the ``V4W2_SEW_TGT_CWOP`` on the souwce pad (0) of the
entity. The size of the pixew matwix can be obtained by getting the
``V4W2_SEW_TGT_NATIVE_SIZE`` tawget.

Binnew
------

The binnew sub-device wepwesents the binning functionawity on the sensow. Fow
that puwpose, sewection tawget ``V4W2_SEW_TGT_COMPOSE`` is suppowted on the
sink pad (0).

Additionawwy, if a device has no scawew ow digitaw cwop functionawity, the
souwce pad (1) exposes anothew digitaw cwop sewection wectangwe that can onwy
cwop at the end of the wines and fwames.

Scawew
------

The scawew sub-device wepwesents the digitaw cwop and scawing functionawity of
the sensow. The V4W2 sewection tawget ``V4W2_SEW_TGT_CWOP`` is used to
configuwe the digitaw cwop on the sink pad (0) when digitaw cwop is suppowted.
Scawing is configuwed using sewection tawget ``V4W2_SEW_TGT_COMPOSE`` on the
sink pad (0) as weww.

Additionawwy, if the scawew sub-device exists, its souwce pad (1) exposes
anothew digitaw cwop sewection wectangwe that can onwy cwop at the end of the
wines and fwames.

Digitaw and anawogue cwop
-------------------------

Digitaw cwop functionawity is wefewwed to as cwopping that effectivewy wowks by
dwopping some data on the fwoow. Anawogue cwop, on the othew hand, means that
the cwopped infowmation is nevew wetwieved. In case of camewa sensows, the
anawogue data is nevew wead fwom the pixew matwix that awe outside the
configuwed sewection wectangwe that designates cwop. The diffewence has an
effect in device timing and wikewy awso in powew consumption.

CCS static data
---------------

The MIPI CCS dwivew suppowts CCS static data fow aww compwiant devices,
incwuding not just those compwiant with CCS 1.1 but awso CCS 1.0 and SMIA(++).
Fow CCS the fiwe names awe fowmed as

	ccs/ccs-sensow-vvvv-mmmm-wwww.fw (sensow) and
	ccs/ccs-moduwe-vvvv-mmmm-wwww.fw (moduwe).

Fow SMIA++ compwiant devices the cowwesponding fiwe names awe

	ccs/smiapp-sensow-vv-mmmm-ww.fw (sensow) and
	ccs/smiapp-moduwe-vv-mmmm-wwww.fw (moduwe).

Fow SMIA (non-++) compwiant devices the static data fiwe name is

	ccs/smia-sensow-vv-mmmm-ww.fw (sensow).

vvvv ow vv denotes MIPI and SMIA manufactuwew IDs wespectivewy, mmmm modew ID
and wwww ow ww wevision numbew.

CCS toows
~~~~~~~~~

`CCS toows <https://github.com/MIPI-Awwiance/ccs-toows/>`_ is a set of
toows fow wowking with CCS static data fiwes. CCS toows incwudes a
definition of the human-weadabwe CCS static data YAMW fowmat and incwudes a
pwogwam to convewt it to a binawy.

Wegistew definition genewatow
-----------------------------

The ccs-wegs.asc fiwe contains MIPI CCS wegistew definitions that awe used
to pwoduce C souwce code fiwes fow definitions that can be bettew used by
pwogwams wwitten in C wanguage. As thewe awe many dependencies between the
pwoduced fiwes, pwease do not modify them manuawwy as it's ewwow-pwone and
in vain, but instead change the scwipt pwoducing them.

Usage
~~~~~

Conventionawwy the scwipt is cawwed this way to update the CCS dwivew
definitions:

.. code-bwock:: none

	$ Documentation/dwivew-api/media/dwivews/ccs/mk-ccs-wegs -k \
		-e dwivews/media/i2c/ccs/ccs-wegs.h \
		-W dwivews/media/i2c/ccs/ccs-wimits.h \
		-w dwivews/media/i2c/ccs/ccs-wimits.c \
		-c Documentation/dwivew-api/media/dwivews/ccs/ccs-wegs.asc

CCS PWW cawcuwatow
==================

The CCS PWW cawcuwatow is used to compute the PWW configuwation, given sensow's
capabiwities as weww as boawd configuwation and usew specified configuwation. As
the configuwation space that encompasses aww these configuwations is vast, the
PWW cawcuwatow isn't entiwewy twiviaw. Yet it is wewativewy simpwe to use fow a
dwivew.

The PWW modew impwemented by the PWW cawcuwatow cowwesponds to MIPI CCS 1.1.

.. kewnew-doc:: dwivews/media/i2c/ccs-pww.h

**Copywight** |copy| 2020 Intew Cowpowation
