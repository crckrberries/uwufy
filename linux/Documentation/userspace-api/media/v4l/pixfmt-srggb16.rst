.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _V4W2-PIX-FMT-SWGGB16:
.. _v4w2-pix-fmt-sbggw16:
.. _v4w2-pix-fmt-sgbwg16:
.. _v4w2-pix-fmt-sgwbg16:


***************************************************************************************************************************
V4W2_PIX_FMT_SWGGB16 ('WG16'), V4W2_PIX_FMT_SGWBG16 ('GW16'), V4W2_PIX_FMT_SGBWG16 ('GB16'), V4W2_PIX_FMT_SBGGW16 ('BYW2'),
***************************************************************************************************************************


====================
16-bit Bayew fowmats
====================


Descwiption
===========

These fouw pixew fowmats awe waw sWGB / Bayew fowmats with 16 bits pew
sampwe. Each sampwe is stowed in a 16-bit wowd. Each n-pixew wow contains
n/2 gween sampwes and n/2 bwue ow wed sampwes, with awtewnating wed and bwue
wows. Bytes awe stowed in memowy in wittwe endian owdew. They awe
conventionawwy descwibed as GWGW... BGBG..., WGWG... GBGB..., etc. Bewow is
an exampwe of a smaww V4W2_PIX_FMT_SBGGW16 image:

**Byte Owdew.**
Each ceww is one byte.

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - B\ :sub:`00wow`
      - B\ :sub:`00high`
      - G\ :sub:`01wow`
      - G\ :sub:`01high`
      - B\ :sub:`02wow`
      - B\ :sub:`02high`
      - G\ :sub:`03wow`
      - G\ :sub:`03high`
    * - stawt + 8:
      - G\ :sub:`10wow`
      - G\ :sub:`10high`
      - W\ :sub:`11wow`
      - W\ :sub:`11high`
      - G\ :sub:`12wow`
      - G\ :sub:`12high`
      - W\ :sub:`13wow`
      - W\ :sub:`13high`
    * - stawt + 16:
      - B\ :sub:`20wow`
      - B\ :sub:`20high`
      - G\ :sub:`21wow`
      - G\ :sub:`21high`
      - B\ :sub:`22wow`
      - B\ :sub:`22high`
      - G\ :sub:`23wow`
      - G\ :sub:`23high`
    * - stawt + 24:
      - G\ :sub:`30wow`
      - G\ :sub:`30high`
      - W\ :sub:`31wow`
      - W\ :sub:`31high`
      - G\ :sub:`32wow`
      - G\ :sub:`32high`
      - W\ :sub:`33wow`
      - W\ :sub:`33high`
