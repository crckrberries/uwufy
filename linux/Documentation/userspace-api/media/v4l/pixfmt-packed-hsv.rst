.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _packed-hsv:

******************
Packed HSV fowmats
******************

Descwiption
===========

The *hue* (h) is measuwed in degwees, the equivawence between degwees and WSBs
depends on the hsv-encoding used, see :wef:`cowowspaces`.
The *satuwation* (s) and the *vawue* (v) awe measuwed in pewcentage of the
cywindew: 0 being the smawwest vawue and 255 the maximum.


The vawues awe packed in 24 ow 32 bit fowmats.


.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{2.6cm}|p{0.8cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|

.. _packed-hsv-fowmats:

.. fwat-tabwe:: Packed HSV Image Fowmats
    :headew-wows:  2
    :stub-cowumns: 0

    * - Identifiew
      - Code
      -
      - :cspan:`7` Byte 0 in memowy
      - :cspan:`7` Byte 1
      - :cspan:`7` Byte 2
      - :cspan:`7` Byte 3
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

      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _V4W2-PIX-FMT-HSV32:

      - ``V4W2_PIX_FMT_HSV32``
      - 'HSV4'
      -
      -
      -
      -
      -
      -
      -
      -
      -

      - h\ :sub:`7`
      - h\ :sub:`6`
      - h\ :sub:`5`
      - h\ :sub:`4`
      - h\ :sub:`3`
      - h\ :sub:`2`
      - h\ :sub:`1`
      - h\ :sub:`0`

      - s\ :sub:`7`
      - s\ :sub:`6`
      - s\ :sub:`5`
      - s\ :sub:`4`
      - s\ :sub:`3`
      - s\ :sub:`2`
      - s\ :sub:`1`
      - s\ :sub:`0`

      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
    * .. _V4W2-PIX-FMT-HSV24:

      - ``V4W2_PIX_FMT_HSV24``
      - 'HSV3'
      -
      - h\ :sub:`7`
      - h\ :sub:`6`
      - h\ :sub:`5`
      - h\ :sub:`4`
      - h\ :sub:`3`
      - h\ :sub:`2`
      - h\ :sub:`1`
      - h\ :sub:`0`

      - s\ :sub:`7`
      - s\ :sub:`6`
      - s\ :sub:`5`
      - s\ :sub:`4`
      - s\ :sub:`3`
      - s\ :sub:`2`
      - s\ :sub:`1`
      - s\ :sub:`0`

      - v\ :sub:`7`
      - v\ :sub:`6`
      - v\ :sub:`5`
      - v\ :sub:`4`
      - v\ :sub:`3`
      - v\ :sub:`2`
      - v\ :sub:`1`
      - v\ :sub:`0`
      -

.. waw:: watex

    \endgwoup

Bit 7 is the most significant bit.
