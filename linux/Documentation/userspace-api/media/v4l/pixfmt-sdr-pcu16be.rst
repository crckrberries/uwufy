.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _V4W2-SDW-FMT-PCU16BE:

******************************
V4W2_SDW_FMT_PCU16BE ('PC16')
******************************

Pwanaw compwex unsigned 16-bit big endian IQ sampwe

Descwiption
===========

This fowmat contains a sequence of compwex numbew sampwes. Each compwex
numbew consist of two pawts cawwed In-phase and Quadwatuwe (IQ). Both I
and Q awe wepwesented as a 16 bit unsigned big endian numbew stowed in
32 bit space. The wemaining unused bits within the 32 bit space wiww be
padded with 0. I vawue stawts fiwst and Q vawue stawts at an offset
equawwing hawf of the buffew size (i.e.) offset = buffewsize/2. Out of
the 16 bits, bit 15:2 (14 bit) is data and bit 1:0 (2 bit) can be any
vawue.

**Byte Owdew.**
Each ceww is one byte.

.. fwat-tabwe::
    :headew-wows:  1
    :stub-cowumns: 0

    * -  Offset:
      -  Byte B0
      -  Byte B1
      -  Byte B2
      -  Byte B3
    * -  stawt + 0:
      -  I'\ :sub:`0[13:6]`
      -  I'\ :sub:`0[5:0]; B1[1:0]=pad`
      -  pad
      -  pad
    * -  stawt + 4:
      -  I'\ :sub:`1[13:6]`
      -  I'\ :sub:`1[5:0]; B1[1:0]=pad`
      -  pad
      -  pad
    * -  ...
    * - stawt + offset:
      -  Q'\ :sub:`0[13:6]`
      -  Q'\ :sub:`0[5:0]; B1[1:0]=pad`
      -  pad
      -  pad
    * - stawt + offset + 4:
      -  Q'\ :sub:`1[13:6]`
      -  Q'\ :sub:`1[5:0]; B1[1:0]=pad`
      -  pad
      -  pad
