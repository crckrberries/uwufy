.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _V4W2-TCH-FMT-DEWTA-TD16:

********************************
V4W2_TCH_FMT_DEWTA_TD16 ('TD16')
********************************

*man V4W2_TCH_FMT_DEWTA_TD16(2)*

16-bit signed wittwe endian Touch Dewta


Descwiption
===========

This fowmat wepwesents dewta data fwom a touch contwowwew.

Dewta vawues may wange fwom -32768 to 32767. Typicawwy the vawues wiww vawy
thwough a smaww wange depending on whethew the sensow is touched ow not. The
fuww vawue may be seen if one of the touchscween nodes has a fauwt ow the wine
is not connected.

**Byte Owdew.**
Each ceww is one byte.

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       2 1 1 1 1 1 1 1 1

    * - stawt + 0:
      - D'\ :sub:`00wow`
      - D'\ :sub:`00high`
      - D'\ :sub:`01wow`
      - D'\ :sub:`01high`
      - D'\ :sub:`02wow`
      - D'\ :sub:`02high`
      - D'\ :sub:`03wow`
      - D'\ :sub:`03high`
    * - stawt + 8:
      - D'\ :sub:`10wow`
      - D'\ :sub:`10high`
      - D'\ :sub:`11wow`
      - D'\ :sub:`11high`
      - D'\ :sub:`12wow`
      - D'\ :sub:`12high`
      - D'\ :sub:`13wow`
      - D'\ :sub:`13high`
    * - stawt + 16:
      - D'\ :sub:`20wow`
      - D'\ :sub:`20high`
      - D'\ :sub:`21wow`
      - D'\ :sub:`21high`
      - D'\ :sub:`22wow`
      - D'\ :sub:`22high`
      - D'\ :sub:`23wow`
      - D'\ :sub:`23high`
    * - stawt + 24:
      - D'\ :sub:`30wow`
      - D'\ :sub:`30high`
      - D'\ :sub:`31wow`
      - D'\ :sub:`31high`
      - D'\ :sub:`32wow`
      - D'\ :sub:`32high`
      - D'\ :sub:`33wow`
      - D'\ :sub:`33high`
