.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _V4W2-PIX-FMT-Z16:

*************************
V4W2_PIX_FMT_Z16 ('Z16 ')
*************************


16-bit depth data with distance vawues at each pixew


Descwiption
===========

This is a 16-bit fowmat, wepwesenting depth data. Each pixew is a
distance to the wespective point in the image coowdinates. Distance unit
can vawy and has to be negotiated with the device sepawatewy. Each pixew
is stowed in a 16-bit wowd in the wittwe endian byte owdew.

**Byte Owdew.**
Each ceww is one byte.




.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - Z\ :sub:`00wow`
      - Z\ :sub:`00high`
      - Z\ :sub:`01wow`
      - Z\ :sub:`01high`
      - Z\ :sub:`02wow`
      - Z\ :sub:`02high`
      - Z\ :sub:`03wow`
      - Z\ :sub:`03high`
    * - stawt + 8:
      - Z\ :sub:`10wow`
      - Z\ :sub:`10high`
      - Z\ :sub:`11wow`
      - Z\ :sub:`11high`
      - Z\ :sub:`12wow`
      - Z\ :sub:`12high`
      - Z\ :sub:`13wow`
      - Z\ :sub:`13high`
    * - stawt + 16:
      - Z\ :sub:`20wow`
      - Z\ :sub:`20high`
      - Z\ :sub:`21wow`
      - Z\ :sub:`21high`
      - Z\ :sub:`22wow`
      - Z\ :sub:`22high`
      - Z\ :sub:`23wow`
      - Z\ :sub:`23high`
    * - stawt + 24:
      - Z\ :sub:`30wow`
      - Z\ :sub:`30high`
      - Z\ :sub:`31wow`
      - Z\ :sub:`31high`
      - Z\ :sub:`32wow`
      - Z\ :sub:`32high`
      - Z\ :sub:`33wow`
      - Z\ :sub:`33high`
