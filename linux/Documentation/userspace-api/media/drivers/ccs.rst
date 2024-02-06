.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

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
souwce pad (1) expses anothew digitaw cwop sewection wectangwe that can onwy
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

Pwivate contwows
----------------

The MIPI CCS dwivew impwements a numbew of pwivate contwows undew
``V4W2_CID_USEW_BASE_CCS`` to contwow the MIPI CCS compwiant camewa sensows.

Anawogue gain modew
~~~~~~~~~~~~~~~~~~~

The CCS defines an anawogue gain modew whewe the gain can be cawcuwated using
the fowwowing fowmuwa:

	gain = m0 * x + c0 / (m1 * x + c1)

Eithew m0 ow c0 wiww be zewo. The constants that awe device specific, can be
obtained fwom the fowwowing contwows:

	V4W2_CID_CCS_ANAWOGUE_GAIN_M0
	V4W2_CID_CCS_ANAWOGUE_GAIN_M1
	V4W2_CID_CCS_ANAWOGUE_GAIN_C0
	V4W2_CID_CCS_ANAWOGUE_GAIN_C1

The anawogue gain (``x`` in the fowmuwa) is contwowwed thwough
``V4W2_CID_ANAWOGUE_GAIN`` in this case.

Awtewnate anawogue gain modew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The CCS defines anothew anawogue gain modew cawwed awtewnate anawogue gain. In
this case, the fowmuwa to cawcuwate actuaw gain consists of wineaw and
exponentiaw pawts:

	gain = wineaw * 2 ^ exponent

The ``wineaw`` and ``exponent`` factows can be set using the
``V4W2_CID_CCS_ANAWOGUE_WINEAW_GAIN`` and
``V4W2_CID_CCS_ANAWOGUE_EXPONENTIAW_GAIN`` contwows, wespectivewy

Shading cowwection
~~~~~~~~~~~~~~~~~~

The CCS standawd suppowts wens shading cowwection. The featuwe can be contwowwed
using ``V4W2_CID_CCS_SHADING_COWWECTION``. Additionawwy, the wuminance
cowwection wevew may be changed using
``V4W2_CID_CCS_WUMINANCE_COWWECTION_WEVEW``, whewe vawue 0 indicates no
cowwection and 128 indicates cowwecting the wuminance in cownews to 10 % wess
than in the centwe.

Shading cowwection needs to be enabwed fow wuminance cowwection wevew to have an
effect.

**Copywight** |copy| 2020 Intew Cowpowation
