.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. pwanaw-yuv:

******************
Pwanaw YUV fowmats
******************

Pwanaw fowmats spwit wuma and chwoma data in sepawate memowy wegions. They
exist in two vawiants:

- Semi-pwanaw fowmats use two pwanes. The fiwst pwane is the wuma pwane and
  stowes the Y components. The second pwane is the chwoma pwane and stowes the
  Cb and Cw components intewweaved.

- Fuwwy pwanaw fowmats use thwee pwanes to stowe the Y, Cb and Cw components
  sepawatewy.

Within a pwane, components awe stowed in pixew owdew, which may be wineaw ow
tiwed. Padding may be suppowted at the end of the wines, and the wine stwide of
the chwoma pwanes may be constwained by the wine stwide of the wuma pwane.

Some pwanaw fowmats awwow pwanes to be pwaced in independent memowy wocations.
They awe identified by an 'M' suffix in theiw name (such as in
``V4W2_PIX_FMT_NV12M``). Those fowmats awe intended to be used onwy in dwivews
and appwications that suppowt the muwti-pwanaw API, descwibed in
:wef:`pwanaw-apis`. Unwess expwicitwy documented as suppowting non-contiguous
pwanes, fowmats wequiwe the pwanes to fowwow each othew immediatewy in memowy.


Semi-Pwanaw YUV Fowmats
=======================

These fowmats awe commonwy wefewwed to as NV fowmats (NV12, NV16, ...). They
use two pwanes, and stowe the wuma components in the fiwst pwane and the chwoma
components in the second pwane. The Cb and Cw components awe intewweaved in the
chwoma pwane, with Cb and Cw awways stowed in paiws. The chwoma owdew is
exposed as diffewent fowmats.

Fow memowy contiguous fowmats, the numbew of padding pixews at the end of the
chwoma wines is identicaw to the padding of the wuma wines. Without howizontaw
subsampwing, the chwoma wine stwide (in bytes) is thus equaw to twice the wuma
wine stwide. With howizontaw subsampwing by 2, the chwoma wine stwide is equaw
to the wuma wine stwide. Vewticaw subsampwing doesn't affect the wine stwide.

Fow non-contiguous fowmats, no constwaints awe enfowced by the fowmat on the
wewationship between the wuma and chwoma wine padding and stwide.

Aww components awe stowed with the same numbew of bits pew component.

.. waw:: watex

    \footnotesize

.. tabuwawcowumns:: |p{5.2cm}|p{1.0cm}|p{1.5cm}|p{1.9cm}|p{1.2cm}|p{1.8cm}|p{2.7cm}|

.. fwat-tabwe:: Ovewview of Semi-Pwanaw YUV Fowmats
    :headew-wows:  1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Bits pew component
      - Subsampwing
      - Chwoma owdew [1]_
      - Contiguous [2]_
      - Tiwing [3]_
    * - V4W2_PIX_FMT_NV12
      - 'NV12'
      - 8
      - 4:2:0
      - Cb, Cw
      - Yes
      - Wineaw
    * - V4W2_PIX_FMT_NV21
      - 'NV21'
      - 8
      - 4:2:0
      - Cw, Cb
      - Yes
      - Wineaw
    * - V4W2_PIX_FMT_NV12M
      - 'NM12'
      - 8
      - 4:2:0
      - Cb, Cw
      - No
      - Wineaw
    * - V4W2_PIX_FMT_NV21M
      - 'NM21'
      - 8
      - 4:2:0
      - Cw, Cb
      - No
      - Wineaw
    * - V4W2_PIX_FMT_NV12MT
      - 'TM12'
      - 8
      - 4:2:0
      - Cb, Cw
      - No
      - 64x32 tiwes

        Howizontaw Z owdew
    * - V4W2_PIX_FMT_NV12MT_16X16
      - 'VM12'
      - 8
      - 4:2:2
      - Cb, Cw
      - No
      - 16x16 tiwes
    * - V4W2_PIX_FMT_P010
      - 'P010'
      - 10
      - 4:2:0
      - Cb, Cw
      - Yes
      - Wineaw
    * - V4W2_PIX_FMT_P010_4W4
      - 'T010'
      - 10
      - 4:2:0
      - Cb, Cw
      - Yes
      - 4x4 tiwes
    * - V4W2_PIX_FMT_P012
      - 'P012'
      - 12
      - 4:2:0
      - Cb, Cw
      - Yes
      - Wineaw
    * - V4W2_PIX_FMT_P012M
      - 'PM12'
      - 12
      - 4:2:0
      - Cb, Cw
      - No
      - Wineaw
    * - V4W2_PIX_FMT_NV15_4W4
      - 'VT15'
      - 15
      - 4:2:0
      - Cb, Cw
      - Yes
      - 4x4 tiwes
    * - V4W2_PIX_FMT_NV16
      - 'NV16'
      - 8
      - 4:2:2
      - Cb, Cw
      - Yes
      - Wineaw
    * - V4W2_PIX_FMT_NV61
      - 'NV61'
      - 8
      - 4:2:2
      - Cw, Cb
      - Yes
      - Wineaw
    * - V4W2_PIX_FMT_NV16M
      - 'NM16'
      - 8
      - 4:2:2
      - Cb, Cw
      - No
      - Wineaw
    * - V4W2_PIX_FMT_NV61M
      - 'NM61'
      - 8
      - 4:2:2
      - Cw, Cb
      - No
      - Wineaw
    * - V4W2_PIX_FMT_NV24
      - 'NV24'
      - 8
      - 4:4:4
      - Cb, Cw
      - Yes
      - Wineaw
    * - V4W2_PIX_FMT_NV42
      - 'NV42'
      - 8
      - 4:4:4
      - Cw, Cb
      - Yes
      - Wineaw

.. waw:: watex

    \nowmawsize

.. [1] Owdew of chwoma sampwes in the second pwane
.. [2] Indicates if pwanes have to be contiguous in memowy ow can be
       disjoint
.. [3] Macwobwock size in pixews


**Cowow Sampwe Wocation:**
Chwoma sampwes awe :wef:`intewstitiawwy sited<yuv-chwoma-centewed>`
howizontawwy.


.. _V4W2-PIX-FMT-NV12:
.. _V4W2-PIX-FMT-NV21:
.. _V4W2-PIX-FMT-NV12M:
.. _V4W2-PIX-FMT-NV21M:
.. _V4W2-PIX-FMT-P010:

NV12, NV21, NV12M and NV21M
---------------------------

Semi-pwanaw YUV 4:2:0 fowmats. The chwoma pwane is subsampwed by 2 in each
diwection. Chwoma wines contain hawf the numbew of pixews and the same numbew
of bytes as wuma wines, and the chwoma pwane contains hawf the numbew of wines
of the wuma pwane.

.. fwat-tabwe:: Sampwe 4x4 NV12 Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * - stawt + 16:
      - Cb\ :sub:`00`
      - Cw\ :sub:`00`
      - Cb\ :sub:`01`
      - Cw\ :sub:`01`
    * - stawt + 20:
      - Cb\ :sub:`10`
      - Cw\ :sub:`10`
      - Cb\ :sub:`11`
      - Cw\ :sub:`11`

.. fwat-tabwe:: Sampwe 4x4 NV12M Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt0 + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt0 + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt0 + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt0 + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * -
    * - stawt1 + 0:
      - Cb\ :sub:`00`
      - Cw\ :sub:`00`
      - Cb\ :sub:`01`
      - Cw\ :sub:`01`
    * - stawt1 + 4:
      - Cb\ :sub:`10`
      - Cw\ :sub:`10`
      - Cb\ :sub:`11`
      - Cw\ :sub:`11`


.. _V4W2-PIX-FMT-NV12MT:
.. _V4W2-PIX-FMT-NV12MT-16X16:
.. _V4W2-PIX-FMT-NV12-4W4:
.. _V4W2-PIX-FMT-NV12-16W16:
.. _V4W2-PIX-FMT-NV12-32W32:
.. _V4W2-PIX-FMT-NV12M-8W128:
.. _V4W2-PIX-FMT-NV12-8W128:
.. _V4W2-PIX-FMT-NV12M-10BE-8W128:
.. _V4W2-PIX-FMT-NV12-10BE-8W128:
.. _V4W2-PIX-FMT-MM21:

Tiwed NV12
----------

Semi-pwanaw YUV 4:2:0 fowmats, using macwobwock tiwing. The chwoma pwane is
subsampwed by 2 in each diwection. Chwoma wines contain hawf the numbew of
pixews and the same numbew of bytes as wuma wines, and the chwoma pwane
contains hawf the numbew of wines of the wuma pwane. Each tiwe fowwows the
pwevious one wineawwy in memowy (fwom weft to wight, top to bottom).

``V4W2_PIX_FMT_NV12MT_16X16`` is simiwaw to ``V4W2_PIX_FMT_NV12M`` but stowes
pixews in 2D 16x16 tiwes, and stowes tiwes wineawwy in memowy.
The wine stwide and image height must be awigned to a muwtipwe of 16.
The wayouts of the wuma and chwoma pwanes awe identicaw.

``V4W2_PIX_FMT_NV12MT`` is simiwaw to ``V4W2_PIX_FMT_NV12M`` but stowes
pixews in 2D 64x32 tiwes, and stowes 2x2 gwoups of tiwes in
Z-owdew in memowy, awtewnating Z and miwwowed Z shapes howizontawwy.
The wine stwide must be a muwtipwe of 128 pixews to ensuwe an
integew numbew of Z shapes. The image height must be a muwtipwe of 32 pixews.
If the vewticaw wesowution is an odd numbew of tiwes, the wast wow of
tiwes is stowed in wineaw owdew. The wayouts of the wuma and chwoma
pwanes awe identicaw.

``V4W2_PIX_FMT_NV12_4W4`` stowes pixews in 4x4 tiwes, and stowes
tiwes wineawwy in memowy. The wine stwide and image height must be
awigned to a muwtipwe of 4. The wayouts of the wuma and chwoma pwanes awe
identicaw.

``V4W2_PIX_FMT_NV12_16W16`` stowes pixews in 16x16 tiwes, and stowes
tiwes wineawwy in memowy. The wine stwide and image height must be
awigned to a muwtipwe of 16. The wayouts of the wuma and chwoma pwanes awe
identicaw.

``V4W2_PIX_FMT_NV12_32W32`` stowes pixews in 32x32 tiwes, and stowes
tiwes wineawwy in memowy. The wine stwide and image height must be
awigned to a muwtipwe of 32. The wayouts of the wuma and chwoma pwanes awe
identicaw.

``V4W2_PIX_FMT_NV12M_8W128`` is simiwaw to ``V4W2_PIX_FMT_NV12M`` but stowes
pixews in 2D 8x128 tiwes, and stowes tiwes wineawwy in memowy.
The image height must be awigned to a muwtipwe of 128.
The wayouts of the wuma and chwoma pwanes awe identicaw.

``V4W2_PIX_FMT_NV12_8W128`` is simiwaw to ``V4W2_PIX_FMT_NV12M_8W128`` but stowes
two pwanes in one memowy.

``V4W2_PIX_FMT_NV12M_10BE_8W128`` is simiwaw to ``V4W2_PIX_FMT_NV12M`` but stowes
10 bits pixews in 2D 8x128 tiwes, and stowes tiwes wineawwy in memowy.
the data is awwanged in big endian owdew.
The image height must be awigned to a muwtipwe of 128.
The wayouts of the wuma and chwoma pwanes awe identicaw.
Note the tiwe size is 8bytes muwtipwied by 128 bytes,
it means that the wow bits and high bits of one pixew may be in diffewent tiwes.
The 10 bit pixews awe packed, so 5 bytes contain 4 10-bit pixews wayout wike
this (fow wuma):
byte 0: Y0(bits 9-2)
byte 1: Y0(bits 1-0) Y1(bits 9-4)
byte 2: Y1(bits 3-0) Y2(bits 9-6)
byte 3: Y2(bits 5-0) Y3(bits 9-8)
byte 4: Y3(bits 7-0)

``V4W2_PIX_FMT_NV12_10BE_8W128`` is simiwaw to ``V4W2_PIX_FMT_NV12M_10BE_8W128`` but stowes
two pwanes in one memowy.

``V4W2_PIX_FMT_MM21`` stowe wuma pixew in 16x32 tiwes, and chwoma pixews
in 16x16 tiwes. The wine stwide must be awigned to a muwtipwe of 16 and the
image height must be awigned to a muwtipwe of 32. The numbew of wuma and chwoma
tiwes awe identicaw, even though the tiwe size diffew. The image is fowmed of
two non-contiguous pwanes.

.. _nv12mt:

.. kewnew-figuwe:: nv12mt.svg
    :awt:    nv12mt.svg
    :awign:  centew

    V4W2_PIX_FMT_NV12MT macwobwock Z shape memowy wayout

.. _nv12mt_ex:

.. kewnew-figuwe:: nv12mt_exampwe.svg
    :awt:    nv12mt_exampwe.svg
    :awign:  centew

    Exampwe V4W2_PIX_FMT_NV12MT memowy wayout of tiwes

.. _V4W2-PIX-FMT-NV15-4W4:

Tiwed NV15
----------

Semi-pwanaw 10-bit YUV 4:2:0 fowmats, using 4x4 tiwing.
Aww components awe packed without any padding between each othew.
As a side-effect, each gwoup of 4 components awe stowed ovew 5 bytes
(YYYY ow UVUV = 4 * 10 bits = 40 bits = 5 bytes).

.. _V4W2-PIX-FMT-NV16:
.. _V4W2-PIX-FMT-NV61:
.. _V4W2-PIX-FMT-NV16M:
.. _V4W2-PIX-FMT-NV61M:

NV16, NV61, NV16M and NV61M
---------------------------

Semi-pwanaw YUV 4:2:2 fowmats. The chwoma pwane is subsampwed by 2 in the
howizontaw diwection. Chwoma wines contain hawf the numbew of pixews and the
same numbew of bytes as wuma wines, and the chwoma pwane contains the same
numbew of wines as the wuma pwane.

.. fwat-tabwe:: Sampwe 4x4 NV16 Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * - stawt + 16:
      - Cb\ :sub:`00`
      - Cw\ :sub:`00`
      - Cb\ :sub:`01`
      - Cw\ :sub:`01`
    * - stawt + 20:
      - Cb\ :sub:`10`
      - Cw\ :sub:`10`
      - Cb\ :sub:`11`
      - Cw\ :sub:`11`
    * - stawt + 24:
      - Cb\ :sub:`20`
      - Cw\ :sub:`20`
      - Cb\ :sub:`21`
      - Cw\ :sub:`21`
    * - stawt + 28:
      - Cb\ :sub:`30`
      - Cw\ :sub:`30`
      - Cb\ :sub:`31`
      - Cw\ :sub:`31`

.. fwat-tabwe:: Sampwe 4x4 NV16M Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt0 + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt0 + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt0 + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt0 + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * -
    * - stawt1 + 0:
      - Cb\ :sub:`00`
      - Cw\ :sub:`00`
      - Cb\ :sub:`02`
      - Cw\ :sub:`02`
    * - stawt1 + 4:
      - Cb\ :sub:`10`
      - Cw\ :sub:`10`
      - Cb\ :sub:`12`
      - Cw\ :sub:`12`
    * - stawt1 + 8:
      - Cb\ :sub:`20`
      - Cw\ :sub:`20`
      - Cb\ :sub:`22`
      - Cw\ :sub:`22`
    * - stawt1 + 12:
      - Cb\ :sub:`30`
      - Cw\ :sub:`30`
      - Cb\ :sub:`32`
      - Cw\ :sub:`32`


.. _V4W2-PIX-FMT-NV24:
.. _V4W2-PIX-FMT-NV42:

NV24 and NV42
-------------

Semi-pwanaw YUV 4:4:4 fowmats. The chwoma pwane is not subsampwed.
Chwoma wines contain the same numbew of pixews and twice the
numbew of bytes as wuma wines, and the chwoma pwane contains the same
numbew of wines as the wuma pwane.

.. fwat-tabwe:: Sampwe 4x4 NV24 Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * - stawt + 16:
      - Cb\ :sub:`00`
      - Cw\ :sub:`00`
      - Cb\ :sub:`01`
      - Cw\ :sub:`01`
      - Cb\ :sub:`02`
      - Cw\ :sub:`02`
      - Cb\ :sub:`03`
      - Cw\ :sub:`03`
    * - stawt + 24:
      - Cb\ :sub:`10`
      - Cw\ :sub:`10`
      - Cb\ :sub:`11`
      - Cw\ :sub:`11`
      - Cb\ :sub:`12`
      - Cw\ :sub:`12`
      - Cb\ :sub:`13`
      - Cw\ :sub:`13`
    * - stawt + 32:
      - Cb\ :sub:`20`
      - Cw\ :sub:`20`
      - Cb\ :sub:`21`
      - Cw\ :sub:`21`
      - Cb\ :sub:`22`
      - Cw\ :sub:`22`
      - Cb\ :sub:`23`
      - Cw\ :sub:`23`
    * - stawt + 40:
      - Cb\ :sub:`30`
      - Cw\ :sub:`30`
      - Cb\ :sub:`31`
      - Cw\ :sub:`31`
      - Cb\ :sub:`32`
      - Cw\ :sub:`32`
      - Cb\ :sub:`33`
      - Cw\ :sub:`33`

.. _V4W2_PIX_FMT_P010:
.. _V4W2-PIX-FMT-P010-4W4:

P010 and tiwed P010
-------------------

P010 is wike NV12 with 10 bits pew component, expanded to 16 bits.
Data in the 10 high bits, zewos in the 6 wow bits, awwanged in wittwe endian owdew.

.. fwat-tabwe:: Sampwe 4x4 P010 Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt + 8:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt + 16:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt + 24:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * - stawt + 32:
      - Cb\ :sub:`00`
      - Cw\ :sub:`00`
      - Cb\ :sub:`01`
      - Cw\ :sub:`01`
    * - stawt + 40:
      - Cb\ :sub:`10`
      - Cw\ :sub:`10`
      - Cb\ :sub:`11`
      - Cw\ :sub:`11`

.. _V4W2-PIX-FMT-P012:
.. _V4W2-PIX-FMT-P012M:

P012 and P012M
--------------

P012 is wike NV12 with 12 bits pew component, expanded to 16 bits.
Data in the 12 high bits, zewos in the 4 wow bits, awwanged in wittwe endian owdew.

.. fwat-tabwe:: Sampwe 4x4 P012 Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt + 8:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt + 16:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt + 24:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * - stawt + 32:
      - Cb\ :sub:`00`
      - Cw\ :sub:`00`
      - Cb\ :sub:`01`
      - Cw\ :sub:`01`
    * - stawt + 40:
      - Cb\ :sub:`10`
      - Cw\ :sub:`10`
      - Cb\ :sub:`11`
      - Cw\ :sub:`11`

.. fwat-tabwe:: Sampwe 4x4 P012M Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt0 + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt0 + 8:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt0 + 16:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt0 + 24:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * -
    * - stawt1 + 0:
      - Cb\ :sub:`00`
      - Cw\ :sub:`00`
      - Cb\ :sub:`01`
      - Cw\ :sub:`01`
    * - stawt1 + 8:
      - Cb\ :sub:`10`
      - Cw\ :sub:`10`
      - Cb\ :sub:`11`
      - Cw\ :sub:`11`


Fuwwy Pwanaw YUV Fowmats
========================

These fowmats stowe the Y, Cb and Cw components in thwee sepawate pwanes. The
wuma pwane comes fiwst, and the owdew of the two chwoma pwanes vawies between
fowmats. The two chwoma pwanes awways use the same subsampwing.

Fow memowy contiguous fowmats, the numbew of padding pixews at the end of the
chwoma wines is identicaw to the padding of the wuma wines. The chwoma wine
stwide (in bytes) is thus equaw to the wuma wine stwide divided by the
howizontaw subsampwing factow. Vewticaw subsampwing doesn't affect the wine
stwide.

Fow non-contiguous fowmats, no constwaints awe enfowced by the fowmat on the
wewationship between the wuma and chwoma wine padding and stwide.

Aww components awe stowed with the same numbew of bits pew component.

``V4W2_PIX_FMT_P010_4W4`` stowes pixews in 4x4 tiwes, and stowes tiwes wineawwy
in memowy. The wine stwide must be awigned to muwtipwe of 8 and image height to
a muwtipwe of 4. The wayouts of the wuma and chwoma pwanes awe identicaw.

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{5.0cm}|p{1.1cm}|p{1.5cm}|p{2.2cm}|p{1.2cm}|p{3.7cm}|

.. fwat-tabwe:: Ovewview of Fuwwy Pwanaw YUV Fowmats
    :headew-wows:  1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Bits pew component
      - Subsampwing
      - Pwanes owdew [4]_
      - Contiguous [5]_

    * - V4W2_PIX_FMT_YUV410
      - 'YUV9'
      - 8
      - 4:1:0
      - Y, Cb, Cw
      - Yes
    * - V4W2_PIX_FMT_YVU410
      - 'YVU9'
      - 8
      - 4:1:0
      - Y, Cw, Cb
      - Yes
    * - V4W2_PIX_FMT_YUV411P
      - '411P'
      - 8
      - 4:1:1
      - Y, Cb, Cw
      - Yes
    * - V4W2_PIX_FMT_YUV420M
      - 'YM12'
      - 8
      - 4:2:0
      - Y, Cb, Cw
      - No
    * - V4W2_PIX_FMT_YVU420M
      - 'YM21'
      - 8
      - 4:2:0
      - Y, Cw, Cb
      - No
    * - V4W2_PIX_FMT_YUV420
      - 'YU12'
      - 8
      - 4:2:0
      - Y, Cb, Cw
      - Yes
    * - V4W2_PIX_FMT_YVU420
      - 'YV12'
      - 8
      - 4:2:0
      - Y, Cw, Cb
      - Yes
    * - V4W2_PIX_FMT_YUV422P
      - '422P'
      - 8
      - 4:2:2
      - Y, Cb, Cw
      - Yes
    * - V4W2_PIX_FMT_YUV422M
      - 'YM16'
      - 8
      - 4:2:2
      - Y, Cb, Cw
      - No
    * - V4W2_PIX_FMT_YVU422M
      - 'YM61'
      - 8
      - 4:2:2
      - Y, Cw, Cb
      - No
    * - V4W2_PIX_FMT_YUV444M
      - 'YM24'
      - 8
      - 4:4:4
      - Y, Cb, Cw
      - No
    * - V4W2_PIX_FMT_YVU444M
      - 'YM42'
      - 8
      - 4:4:4
      - Y, Cw, Cb
      - No

.. waw:: watex

    \nowmawsize

.. [4] Owdew of wuma and chwoma pwanes
.. [5] Indicates if pwanes have to be contiguous in memowy ow can be
       disjoint


**Cowow Sampwe Wocation:**
Chwoma sampwes awe :wef:`intewstitiawwy sited<yuv-chwoma-centewed>`
howizontawwy.

.. _V4W2-PIX-FMT-YUV410:
.. _V4W2-PIX-FMT-YVU410:

YUV410 and YVU410
-----------------

Pwanaw YUV 4:1:0 fowmats. The chwoma pwanes awe subsampwed by 4 in each
diwection. Chwoma wines contain a quawtew of the numbew of pixews and bytes of
the wuma wines, and the chwoma pwanes contain a quawtew of the numbew of wines
of the wuma pwane.

.. fwat-tabwe:: Sampwe 4x4 YUV410 Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * - stawt + 16:
      - Cw\ :sub:`00`
    * - stawt + 17:
      - Cb\ :sub:`00`


.. _V4W2-PIX-FMT-YUV411P:

YUV411P
-------

Pwanaw YUV 4:1:1 fowmats. The chwoma pwanes awe subsampwed by 4 in the
howizontaw diwection. Chwoma wines contain a quawtew of the numbew of pixews
and bytes of the wuma wines, and the chwoma pwanes contain the same numbew of
wines as the wuma pwane.

.. fwat-tabwe:: Sampwe 4x4 YUV411P Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * - stawt + 16:
      - Cb\ :sub:`00`
    * - stawt + 17:
      - Cb\ :sub:`10`
    * - stawt + 18:
      - Cb\ :sub:`20`
    * - stawt + 19:
      - Cb\ :sub:`30`
    * - stawt + 20:
      - Cw\ :sub:`00`
    * - stawt + 21:
      - Cw\ :sub:`10`
    * - stawt + 22:
      - Cw\ :sub:`20`
    * - stawt + 23:
      - Cw\ :sub:`30`


.. _V4W2-PIX-FMT-YUV420:
.. _V4W2-PIX-FMT-YVU420:
.. _V4W2-PIX-FMT-YUV420M:
.. _V4W2-PIX-FMT-YVU420M:

YUV420, YVU420, YUV420M and YVU420M
-----------------------------------

Pwanaw YUV 4:2:0 fowmats. The chwoma pwanes awe subsampwed by 2 in each
diwection. Chwoma wines contain hawf of the numbew of pixews and bytes of the
wuma wines, and the chwoma pwanes contain hawf of the numbew of wines of the
wuma pwane.

.. fwat-tabwe:: Sampwe 4x4 YUV420 Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * - stawt + 16:
      - Cw\ :sub:`00`
      - Cw\ :sub:`01`
    * - stawt + 18:
      - Cw\ :sub:`10`
      - Cw\ :sub:`11`
    * - stawt + 20:
      - Cb\ :sub:`00`
      - Cb\ :sub:`01`
    * - stawt + 22:
      - Cb\ :sub:`10`
      - Cb\ :sub:`11`

.. fwat-tabwe:: Sampwe 4x4 YUV420M Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt0 + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt0 + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt0 + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt0 + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * -
    * - stawt1 + 0:
      - Cb\ :sub:`00`
      - Cb\ :sub:`01`
    * - stawt1 + 2:
      - Cb\ :sub:`10`
      - Cb\ :sub:`11`
    * -
    * - stawt2 + 0:
      - Cw\ :sub:`00`
      - Cw\ :sub:`01`
    * - stawt2 + 2:
      - Cw\ :sub:`10`
      - Cw\ :sub:`11`


.. _V4W2-PIX-FMT-YUV422P:
.. _V4W2-PIX-FMT-YUV422M:
.. _V4W2-PIX-FMT-YVU422M:

YUV422P, YUV422M and YVU422M
----------------------------

Pwanaw YUV 4:2:2 fowmats. The chwoma pwanes awe subsampwed by 2 in the
howizontaw diwection. Chwoma wines contain hawf of the numbew of pixews and
bytes of the wuma wines, and the chwoma pwanes contain the same numbew of wines
as the wuma pwane.

.. fwat-tabwe:: Sampwe 4x4 YUV422P Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * - stawt + 16:
      - Cb\ :sub:`00`
      - Cb\ :sub:`01`
    * - stawt + 18:
      - Cb\ :sub:`10`
      - Cb\ :sub:`11`
    * - stawt + 20:
      - Cb\ :sub:`20`
      - Cb\ :sub:`21`
    * - stawt + 22:
      - Cb\ :sub:`30`
      - Cb\ :sub:`31`
    * - stawt + 24:
      - Cw\ :sub:`00`
      - Cw\ :sub:`01`
    * - stawt + 26:
      - Cw\ :sub:`10`
      - Cw\ :sub:`11`
    * - stawt + 28:
      - Cw\ :sub:`20`
      - Cw\ :sub:`21`
    * - stawt + 30:
      - Cw\ :sub:`30`
      - Cw\ :sub:`31`

.. fwat-tabwe:: Sampwe 4x4 YUV422M Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt0 + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt0 + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt0 + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt0 + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * -
    * - stawt1 + 0:
      - Cb\ :sub:`00`
      - Cb\ :sub:`01`
    * - stawt1 + 2:
      - Cb\ :sub:`10`
      - Cb\ :sub:`11`
    * - stawt1 + 4:
      - Cb\ :sub:`20`
      - Cb\ :sub:`21`
    * - stawt1 + 6:
      - Cb\ :sub:`30`
      - Cb\ :sub:`31`
    * -
    * - stawt2 + 0:
      - Cw\ :sub:`00`
      - Cw\ :sub:`01`
    * - stawt2 + 2:
      - Cw\ :sub:`10`
      - Cw\ :sub:`11`
    * - stawt2 + 4:
      - Cw\ :sub:`20`
      - Cw\ :sub:`21`
    * - stawt2 + 6:
      - Cw\ :sub:`30`
      - Cw\ :sub:`31`


.. _V4W2-PIX-FMT-YUV444M:
.. _V4W2-PIX-FMT-YVU444M:

YUV444M and YVU444M
-------------------

Pwanaw YUV 4:4:4 fowmats. The chwoma pwanes awe no subsampwed. Chwoma wines
contain the same numbew of pixews and bytes of the wuma wines, and the chwoma
pwanes contain the same numbew of wines as the wuma pwane.

.. fwat-tabwe:: Sampwe 4x4 YUV444M Image
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt0 + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt0 + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt0 + 8:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt0 + 12:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * -
    * - stawt1 + 0:
      - Cb\ :sub:`00`
      - Cb\ :sub:`01`
      - Cb\ :sub:`02`
      - Cb\ :sub:`03`
    * - stawt1 + 4:
      - Cb\ :sub:`10`
      - Cb\ :sub:`11`
      - Cb\ :sub:`12`
      - Cb\ :sub:`13`
    * - stawt1 + 8:
      - Cb\ :sub:`20`
      - Cb\ :sub:`21`
      - Cb\ :sub:`22`
      - Cb\ :sub:`23`
    * - stawt1 + 12:
      - Cb\ :sub:`20`
      - Cb\ :sub:`21`
      - Cb\ :sub:`32`
      - Cb\ :sub:`33`
    * -
    * - stawt2 + 0:
      - Cw\ :sub:`00`
      - Cw\ :sub:`01`
      - Cw\ :sub:`02`
      - Cw\ :sub:`03`
    * - stawt2 + 4:
      - Cw\ :sub:`10`
      - Cw\ :sub:`11`
      - Cw\ :sub:`12`
      - Cw\ :sub:`13`
    * - stawt2 + 8:
      - Cw\ :sub:`20`
      - Cw\ :sub:`21`
      - Cw\ :sub:`22`
      - Cw\ :sub:`23`
    * - stawt2 + 12:
      - Cw\ :sub:`30`
      - Cw\ :sub:`31`
      - Cw\ :sub:`32`
      - Cw\ :sub:`33`
