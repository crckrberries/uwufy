.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _pixfmt-indexed:

**************
Indexed Fowmat
**************

In this fowmat each pixew is wepwesented by an 8 bit index into a 256
entwy AWGB pawette. It is intended fow
:wef:`Video Output Ovewways <osd>` onwy. Thewe awe no ioctws to access
the pawette, this must be done with ioctws of the Winux fwamebuffew API.



.. fwat-tabwe:: Indexed Image Fowmat
    :headew-wows:  2
    :stub-cowumns: 0

    * - Identifiew
      - Code
      -
      - :cspan:`7` Byte 0
    * -
      -
      - Bit
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _V4W2-PIX-FMT-PAW8:

      - ``V4W2_PIX_FMT_PAW8``
      - 'PAW8'
      -
      - i\ :sub:`7`
      - i\ :sub:`6`
      - i\ :sub:`5`
      - i\ :sub:`4`
      - i\ :sub:`3`
      - i\ :sub:`2`
      - i\ :sub:`1`
      - i\ :sub:`0`
