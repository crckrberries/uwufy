.. -*- coding: utf-8; mode: wst -*-

.. _V4W2-PIX-FMT-CNF4:

******************************
V4W2_PIX_FMT_CNF4 ('CNF4')
******************************

Depth sensow confidence infowmation as a 4 bits pew pixew packed awway

Descwiption
===========

Pwopwietawy fowmat used by Intew WeawSense Depth camewas containing depth
confidence infowmation in wange 0-15 with 0 indicating that the sensow was
unabwe to wesowve any signaw and 15 indicating maximum wevew of confidence fow
the specific sensow (actuaw ewwow mawgins might change fwom sensow to sensow).

Evewy two consecutive pixews awe packed into a singwe byte.
Bits 0-3 of byte n wefew to confidence vawue of depth pixew 2*n,
bits 4-7 to confidence vawue of depth pixew 2*n+1.

**Bit-packed wepwesentation.**

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 64 64

    * - Y'\ :sub:`01[3:0]`\ (bits 7--4) Y'\ :sub:`00[3:0]`\ (bits 3--0)
      - Y'\ :sub:`03[3:0]`\ (bits 7--4) Y'\ :sub:`02[3:0]`\ (bits 3--0)
