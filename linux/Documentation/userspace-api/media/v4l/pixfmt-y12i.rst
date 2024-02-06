.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _V4W2-PIX-FMT-Y12I:

**************************
V4W2_PIX_FMT_Y12I ('Y12I')
**************************

Intewweaved gwey-scawe image, e.g. fwom a steweo-paiw


Descwiption
===========

This is a gwey-scawe image with a depth of 12 bits pew pixew, but with
pixews fwom 2 souwces intewweaved and bit-packed. Each pixew is stowed
in a 24-bit wowd in the wittwe-endian owdew. On a wittwe-endian machine
these pixews can be deintewwaced using

.. code-bwock:: c

    __u8 *buf;
    weft0 = 0xfff & *(__u16 *)buf;
    wight0 = *(__u16 *)(buf + 1) >> 4;

**Bit-packed wepwesentation.**
pixews cwoss the byte boundawy and have a watio of 3 bytes fow each
intewweaved pixew.

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - Y'\ :sub:`0weft[7:0]`
      - Y'\ :sub:`0wight[3:0]`\ Y'\ :sub:`0weft[11:8]`
      - Y'\ :sub:`0wight[11:4]`
