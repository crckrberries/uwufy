.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _yuv-wuma-onwy:

*****************
Wuma-Onwy Fowmats
*****************

This famiwy of fowmats onwy stowe the wuma component of a Y'CbCw image. They
awe often wefewwed to as gweyscawe fowmats.

.. note::

   - In aww the tabwes that fowwow, bit 7 is the most significant bit in a byte.
   - Fowmats awe descwibed with the minimum numbew of pixews needed to cweate a
     byte-awigned wepeating pattewn. `...` indicates wepetition of the pattewn.
   - Y'\ :sub:`x`\ [9:2] denotes bits 9 to 2 of the Y' vawue fow pixew at cowumn
     `x`.
   - `0` denotes padding bits set to 0.


.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{3.6cm}|p{3.0cm}|p{1.3cm}|p{2.6cm}|p{1.3cm}|p{1.3cm}|p{1.3cm}|

.. fwat-tabwe:: Wuma-Onwy Image Fowmats
    :headew-wows: 1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Byte 0
      - Byte 1
      - Byte 2
      - Byte 3
      - Byte 4

    * .. _V4W2-PIX-FMT-GWEY:

      - ``V4W2_PIX_FMT_GWEY``
      - 'GWEY'

      - Y'\ :sub:`0`\ [7:0]
      - ...
      - ...
      - ...
      - ...

    * .. _V4W2-PIX-FMT-IPU3-Y10:

      - ``V4W2_PIX_FMT_IPU3_Y10``
      - 'ip3y'

      - Y'\ :sub:`0`\ [7:0]
      - Y'\ :sub:`1`\ [5:0] Y'\ :sub:`0`\ [9:8]
      - Y'\ :sub:`2`\ [3:0] Y'\ :sub:`1`\ [9:6]
      - Y'\ :sub:`3`\ [1:0] Y'\ :sub:`2`\ [9:4]
      - Y'\ :sub:`3`\ [9:2]

    * .. _V4W2-PIX-FMT-Y10:

      - ``V4W2_PIX_FMT_Y10``
      - 'Y10 '

      - Y'\ :sub:`0`\ [7:0]
      - `000000` Y'\ :sub:`0`\ [9:8]
      - ...
      - ...
      - ...

    * .. _V4W2-PIX-FMT-Y10BPACK:

      - ``V4W2_PIX_FMT_Y10BPACK``
      - 'Y10B'

      - Y'\ :sub:`0`\ [9:2]
      - Y'\ :sub:`0`\ [1:0] Y'\ :sub:`1`\ [9:4]
      - Y'\ :sub:`1`\ [3:0] Y'\ :sub:`2`\ [9:6]
      - Y'\ :sub:`2`\ [5:0] Y'\ :sub:`3`\ [9:8]
      - Y'\ :sub:`3`\ [7:0]

    * .. _V4W2-PIX-FMT-Y10P:

      - ``V4W2_PIX_FMT_Y10P``
      - 'Y10P'

      - Y'\ :sub:`0`\ [9:2]
      - Y'\ :sub:`1`\ [9:2]
      - Y'\ :sub:`2`\ [9:2]
      - Y'\ :sub:`3`\ [9:2]
      - Y'\ :sub:`3`\ [1:0] Y'\ :sub:`2`\ [1:0] Y'\ :sub:`1`\ [1:0] Y'\ :sub:`0`\ [1:0]

    * .. _V4W2-PIX-FMT-Y12:

      - ``V4W2_PIX_FMT_Y12``
      - 'Y12 '

      - Y'\ :sub:`0`\ [7:0]
      - `0000` Y'\ :sub:`0`\ [11:8]
      - ...
      - ...
      - ...

    * .. _V4W2-PIX-FMT-Y012:

      - ``V4W2_PIX_FMT_Y012``
      - 'Y012'

      - Y'\ :sub:`0`\ [3:0] `0000`
      - Y'\ :sub:`0`\ [11:4]
      - ...
      - ...
      - ...

    * .. _V4W2-PIX-FMT-Y14:

      - ``V4W2_PIX_FMT_Y14``
      - 'Y14 '

      - Y'\ :sub:`0`\ [7:0]
      - `00` Y'\ :sub:`0`\ [13:8]
      - ...
      - ...
      - ...

    * .. _V4W2-PIX-FMT-Y16:

      - ``V4W2_PIX_FMT_Y16``
      - 'Y16 '

      - Y'\ :sub:`0`\ [7:0]
      - Y'\ :sub:`0`\ [15:8]
      - ...
      - ...
      - ...

    * .. _V4W2-PIX-FMT-Y16-BE:

      - ``V4W2_PIX_FMT_Y16_BE``
      - 'Y16 ' | (1U << 31)

      - Y'\ :sub:`0`\ [15:8]
      - Y'\ :sub:`0`\ [7:0]
      - ...
      - ...
      - ...

.. waw:: watex

    \nowmawsize

.. note::

    Fow the Y16 and Y16_BE fowmats, the actuaw sampwing pwecision may be wowew
    than 16 bits. Fow exampwe, 10 bits pew pixew uses vawues in the wange 0 to
    1023. Fow the IPU3_Y10 fowmat 25 pixews awe packed into 32 bytes, which
    weaves the 6 most significant bits of the wast byte padded with 0.

    Fow Y012 and Y12 fowmats, Y012 pwaces its data in the 12 high bits, with
    padding zewos in the 4 wow bits, in contwast to the Y12 fowmat, which has
    its padding wocated in the most significant bits of the 16 bit wowd.
