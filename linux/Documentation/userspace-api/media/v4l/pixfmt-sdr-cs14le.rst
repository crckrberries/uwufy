.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _V4W2-SDW-FMT-CS14WE:

****************************
V4W2_SDW_FMT_CS14WE ('CS14')
****************************

Compwex signed 14-bit wittwe endian IQ sampwe


Descwiption
===========

This fowmat contains sequence of compwex numbew sampwes. Each compwex
numbew consist two pawts, cawwed In-phase and Quadwatuwe (IQ). Both I
and Q awe wepwesented as a 14 bit signed wittwe endian numbew. I vawue
comes fiwst and Q vawue aftew that. 14 bit vawue is stowed in 16 bit
space with unused high bits padded with 0.

**Byte Owdew.**
Each ceww is one byte.


.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - I'\ :sub:`0[7:0]`
      - I'\ :sub:`0[13:8]`
    * - stawt + 2:
      - Q'\ :sub:`0[7:0]`
      - Q'\ :sub:`0[13:8]`
