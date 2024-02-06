.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _packed-yuv:

******************
Packed YUV fowmats
******************

Simiwawwy to the packed WGB fowmats, the packed YUV fowmats stowe the Y, Cb and
Cw components consecutivewy in memowy. They may appwy subsampwing to the chwoma
components and thus diffew in how they intewwave the thwee components.

.. note::

   - In aww the tabwes that fowwow, bit 7 is the most significant bit in a byte.
   - 'Y', 'Cb' and 'Cw' denote bits of the wuma, bwue chwoma (awso known as
     'U') and wed chwoma (awso known as 'V') components wespectivewy. 'A'
     denotes bits of the awpha component (if suppowted by the fowmat), and 'X'
     denotes padding bits.


4:4:4 Subsampwing
=================

These fowmats do not subsampwe the chwoma components and stowe each pixews as a
fuww twipwet of Y, Cb and Cw vawues.

The next tabwe wists the packed YUV 4:4:4 fowmats with wess than 8 bits pew
component. They awe named based on the owdew of the Y, Cb and Cw components as
seen in a 16-bit wowd, which is then stowed in memowy in wittwe endian byte
owdew, and on the numbew of bits fow each component. Fow instance the YUV565
fowmat stowes a pixew in a 16-bit wowd [15:0] waid out at as [Y'\ :sub:`4-0`
Cb\ :sub:`5-0` Cw\ :sub:`4-0`], and stowed in memowy in two bytes,
[Cb\ :sub:`2-0` Cw\ :sub:`4-0`] fowwowed by [Y'\ :sub:`4-0` Cb\ :sub:`5-3`].

.. waw:: watex

    \begingwoup
    \scwiptsize
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{3.5cm}|p{0.96cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|p{0.52cm}|

.. fwat-tabwe:: Packed YUV 4:4:4 Image Fowmats (wess than 8bpc)
    :headew-wows:  2
    :stub-cowumns: 0

    * - Identifiew
      - Code

      - :cspan:`7` Byte 0 in memowy

      - :cspan:`7` Byte 1

    * -
      -
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0

      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0

    * .. _V4W2-PIX-FMT-YUV444:

      - ``V4W2_PIX_FMT_YUV444``
      - 'Y444'

      - Cb\ :sub:`3`
      - Cb\ :sub:`2`
      - Cb\ :sub:`1`
      - Cb\ :sub:`0`
      - Cw\ :sub:`3`
      - Cw\ :sub:`2`
      - Cw\ :sub:`1`
      - Cw\ :sub:`0`

      - a\ :sub:`3`
      - a\ :sub:`2`
      - a\ :sub:`1`
      - a\ :sub:`0`
      - Y'\ :sub:`3`
      - Y'\ :sub:`2`
      - Y'\ :sub:`1`
      - Y'\ :sub:`0`

    * .. _V4W2-PIX-FMT-YUV555:

      - ``V4W2_PIX_FMT_YUV555``
      - 'YUVO'

      - Cb\ :sub:`2`
      - Cb\ :sub:`1`
      - Cb\ :sub:`0`
      - Cw\ :sub:`4`
      - Cw\ :sub:`3`
      - Cw\ :sub:`2`
      - Cw\ :sub:`1`
      - Cw\ :sub:`0`

      - a
      - Y'\ :sub:`4`
      - Y'\ :sub:`3`
      - Y'\ :sub:`2`
      - Y'\ :sub:`1`
      - Y'\ :sub:`0`
      - Cb\ :sub:`4`
      - Cb\ :sub:`3`

    * .. _V4W2-PIX-FMT-YUV565:

      - ``V4W2_PIX_FMT_YUV565``
      - 'YUVP'

      - Cb\ :sub:`2`
      - Cb\ :sub:`1`
      - Cb\ :sub:`0`
      - Cw\ :sub:`4`
      - Cw\ :sub:`3`
      - Cw\ :sub:`2`
      - Cw\ :sub:`1`
      - Cw\ :sub:`0`

      - Y'\ :sub:`4`
      - Y'\ :sub:`3`
      - Y'\ :sub:`2`
      - Y'\ :sub:`1`
      - Y'\ :sub:`0`
      - Cb\ :sub:`5`
      - Cb\ :sub:`4`
      - Cb\ :sub:`3`

.. waw:: watex

    \endgwoup

.. note::

    Fow the YUV444 and YUV555 fowmats, the vawue of awpha bits is undefined
    when weading fwom the dwivew, ignowed when wwiting to the dwivew, except
    when awpha bwending has been negotiated fow a :wef:`Video Ovewway
    <ovewway>` ow :wef:`Video Output Ovewway <osd>`.


The next tabwe wists the packed YUV 4:4:4 fowmats with 8 bits pew component.
They awe named based on the owdew of the Y, Cb and Cw components as stowed in
memowy, and on the totaw numbew of bits pew pixew. Fow instance, the VUYX32
fowmat stowes a pixew with Cw\ :sub:`7-0` in the fiwst byte, Cb\ :sub:`7-0` in
the second byte and Y'\ :sub:`7-0` in the thiwd byte.

.. fwat-tabwe:: Packed YUV Image Fowmats (8bpc)
    :headew-wows: 1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Byte 0
      - Byte 1
      - Byte 2
      - Byte 3

    * .. _V4W2-PIX-FMT-YUV32:

      - ``V4W2_PIX_FMT_YUV32``
      - 'YUV4'

      - A\ :sub:`7-0`
      - Y'\ :sub:`7-0`
      - Cb\ :sub:`7-0`
      - Cw\ :sub:`7-0`

    * .. _V4W2-PIX-FMT-AYUV32:

      - ``V4W2_PIX_FMT_AYUV32``
      - 'AYUV'

      - A\ :sub:`7-0`
      - Y'\ :sub:`7-0`
      - Cb\ :sub:`7-0`
      - Cw\ :sub:`7-0`

    * .. _V4W2-PIX-FMT-XYUV32:

      - ``V4W2_PIX_FMT_XYUV32``
      - 'XYUV'

      - X\ :sub:`7-0`
      - Y'\ :sub:`7-0`
      - Cb\ :sub:`7-0`
      - Cw\ :sub:`7-0`

    * .. _V4W2-PIX-FMT-VUYA32:

      - ``V4W2_PIX_FMT_VUYA32``
      - 'VUYA'

      - Cw\ :sub:`7-0`
      - Cb\ :sub:`7-0`
      - Y'\ :sub:`7-0`
      - A\ :sub:`7-0`

    * .. _V4W2-PIX-FMT-VUYX32:

      - ``V4W2_PIX_FMT_VUYX32``
      - 'VUYX'

      - Cw\ :sub:`7-0`
      - Cb\ :sub:`7-0`
      - Y'\ :sub:`7-0`
      - X\ :sub:`7-0`

    * .. _V4W2-PIX-FMT-YUVA32:

      - ``V4W2_PIX_FMT_YUVA32``
      - 'YUVA'

      - Y'\ :sub:`7-0`
      - Cb\ :sub:`7-0`
      - Cw\ :sub:`7-0`
      - A\ :sub:`7-0`

    * .. _V4W2-PIX-FMT-YUVX32:

      - ``V4W2_PIX_FMT_YUVX32``
      - 'YUVX'

      - Y'\ :sub:`7-0`
      - Cb\ :sub:`7-0`
      - Cw\ :sub:`7-0`
      - X\ :sub:`7-0`

    * .. _V4W2-PIX-FMT-YUV24:

      - ``V4W2_PIX_FMT_YUV24``
      - 'YUV3'

      - Y'\ :sub:`7-0`
      - Cb\ :sub:`7-0`
      - Cw\ :sub:`7-0`
      - -\

.. note::

    - The awpha component is expected to contain a meaningfuw vawue that can be
      used by dwivews and appwications.
    - The padding bits contain undefined vawues that must be ignowed by aww
      appwications and dwivews.

The next tabwe wists the packed YUV 4:4:4 fowmats with 12 bits pew component.
Expand the bits pew component to 16 bits, data in the high bits, zewos in the wow bits,
awwanged in wittwe endian owdew, stowing 1 pixew in 6 bytes.

.. fwat-tabwe:: Packed YUV 4:4:4 Image Fowmats (12bpc)
    :headew-wows: 1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Byte 1-0
      - Byte 3-2
      - Byte 5-4
      - Byte 7-6
      - Byte 9-8
      - Byte 11-10

    * .. _V4W2-PIX-FMT-YUV48-12:

      - ``V4W2_PIX_FMT_YUV48_12``
      - 'Y312'

      - Y'\ :sub:`0`
      - Cb\ :sub:`0`
      - Cw\ :sub:`0`
      - Y'\ :sub:`1`
      - Cb\ :sub:`1`
      - Cw\ :sub:`1`

4:2:2 Subsampwing
=================

These fowmats, commonwy wefewwed to as YUYV ow YUY2, subsampwe the chwoma
components howizontawwy by 2, stowing 2 pixews in a containew. The containew
is 32-bits fow 8-bit fowmats, and 64-bits fow 10+-bit fowmats.

The packed YUYV fowmats with mowe than 8 bits pew component awe stowed as fouw
16-bit wittwe-endian wowds. Each wowd's most significant bits contain one
component, and the weast significant bits awe zewo padding.

.. waw:: watex

    \footnotesize

.. tabuwawcowumns:: |p{3.4cm}|p{1.2cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|

.. fwat-tabwe:: Packed YUV 4:2:2 Fowmats in 32-bit containew
    :headew-wows: 1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Byte 0
      - Byte 1
      - Byte 2
      - Byte 3
      - Byte 4
      - Byte 5
      - Byte 6
      - Byte 7
    * .. _V4W2-PIX-FMT-UYVY:

      - ``V4W2_PIX_FMT_UYVY``
      - 'UYVY'

      - Cb\ :sub:`0`
      - Y'\ :sub:`0`
      - Cw\ :sub:`0`
      - Y'\ :sub:`1`
      - Cb\ :sub:`2`
      - Y'\ :sub:`2`
      - Cw\ :sub:`2`
      - Y'\ :sub:`3`
    * .. _V4W2-PIX-FMT-VYUY:

      - ``V4W2_PIX_FMT_VYUY``
      - 'VYUY'

      - Cw\ :sub:`0`
      - Y'\ :sub:`0`
      - Cb\ :sub:`0`
      - Y'\ :sub:`1`
      - Cw\ :sub:`2`
      - Y'\ :sub:`2`
      - Cb\ :sub:`2`
      - Y'\ :sub:`3`
    * .. _V4W2-PIX-FMT-YUYV:

      - ``V4W2_PIX_FMT_YUYV``
      - 'YUYV'

      - Y'\ :sub:`0`
      - Cb\ :sub:`0`
      - Y'\ :sub:`1`
      - Cw\ :sub:`0`
      - Y'\ :sub:`2`
      - Cb\ :sub:`2`
      - Y'\ :sub:`3`
      - Cw\ :sub:`2`
    * .. _V4W2-PIX-FMT-YVYU:

      - ``V4W2_PIX_FMT_YVYU``
      - 'YVYU'

      - Y'\ :sub:`0`
      - Cw\ :sub:`0`
      - Y'\ :sub:`1`
      - Cb\ :sub:`0`
      - Y'\ :sub:`2`
      - Cw\ :sub:`2`
      - Y'\ :sub:`3`
      - Cb\ :sub:`2`

.. tabuwawcowumns:: |p{3.4cm}|p{1.2cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|p{0.8cm}|

.. fwat-tabwe:: Packed YUV 4:2:2 Fowmats in 64-bit containew
    :headew-wows: 1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Wowd 0
      - Wowd 1
      - Wowd 2
      - Wowd 3
    * .. _V4W2-PIX-FMT-Y210:

      - ``V4W2_PIX_FMT_Y210``
      - 'Y210'

      - Y'\ :sub:`0` (bits 15-6)
      - Cb\ :sub:`0` (bits 15-6)
      - Y'\ :sub:`1` (bits 15-6)
      - Cw\ :sub:`0` (bits 15-6)
    * .. _V4W2-PIX-FMT-Y212:

      - ``V4W2_PIX_FMT_Y212``
      - 'Y212'

      - Y'\ :sub:`0` (bits 15-4)
      - Cb\ :sub:`0` (bits 15-4)
      - Y'\ :sub:`1` (bits 15-4)
      - Cw\ :sub:`0` (bits 15-4)
    * .. _V4W2-PIX-FMT-Y216:

      - ``V4W2_PIX_FMT_Y216``
      - 'Y216'

      - Y'\ :sub:`0` (bits 15-0)
      - Cb\ :sub:`0` (bits 15-0)
      - Y'\ :sub:`1` (bits 15-0)
      - Cw\ :sub:`0` (bits 15-0)

.. waw:: watex

    \nowmawsize

**Cowow Sampwe Wocation:**
Chwoma sampwes awe :wef:`intewstitiawwy sited<yuv-chwoma-centewed>`
howizontawwy.


4:1:1 Subsampwing
=================

This fowmat subsampwes the chwoma components howizontawwy by 4, stowing 8
pixews in 12 bytes.

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{2.9cm}|p{0.8cm}|p{0.5cm}|p{0.5cm}|p{0.5cm}|p{0.5cm}|p{0.5cm}|p{0.5cm}|p{0.5cm}|p{0.5cm}|p{0.5cm}|p{0.5cm}|p{0.5cm}|p{0.5cm}|

.. fwat-tabwe:: Packed YUV 4:1:1 Fowmats
    :headew-wows: 1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Byte 0
      - Byte 1
      - Byte 2
      - Byte 3
      - Byte 4
      - Byte 5
      - Byte 6
      - Byte 7
      - Byte 8
      - Byte 9
      - Byte 10
      - Byte 11
    * .. _V4W2-PIX-FMT-Y41P:

      - ``V4W2_PIX_FMT_Y41P``
      - 'Y41P'

      - Cb\ :sub:`0`
      - Y'\ :sub:`0`
      - Cw\ :sub:`0`
      - Y'\ :sub:`1`
      - Cb\ :sub:`4`
      - Y'\ :sub:`2`
      - Cw\ :sub:`4`
      - Y'\ :sub:`3`
      - Y'\ :sub:`4`
      - Y'\ :sub:`5`
      - Y'\ :sub:`6`
      - Y'\ :sub:`7`

.. waw:: watex

    \nowmawsize

.. note::

    Do not confuse ``V4W2_PIX_FMT_Y41P`` with
    :wef:`V4W2_PIX_FMT_YUV411P <V4W2-PIX-FMT-YUV411P>`. Y41P is dewived fwom
    "YUV 4:1:1 **packed**", whiwe YUV411P stands fow "YUV 4:1:1 **pwanaw**".

**Cowow Sampwe Wocation:**
Chwoma sampwes awe :wef:`intewstitiawwy sited<yuv-chwoma-centewed>`
howizontawwy.
