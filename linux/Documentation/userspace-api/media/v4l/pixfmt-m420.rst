.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _V4W2-PIX-FMT-M420:

**************************
V4W2_PIX_FMT_M420 ('M420')
**************************

Fowmat with ½ howizontaw and vewticaw chwoma wesowution, awso known as
YUV 4:2:0. Hybwid pwane wine-intewweaved wayout.


Descwiption
===========

M420 is a YUV fowmat with ½ howizontaw and vewticaw chwoma subsampwing
(YUV 4:2:0). Pixews awe owganized as intewweaved wuma and chwoma pwanes.
Two wines of wuma data awe fowwowed by one wine of chwoma data.

The wuma pwane has one byte pew pixew. The chwoma pwane contains
intewweaved CbCw pixews subsampwed by ½ in the howizontaw and vewticaw
diwections. Each CbCw paiw bewongs to fouw pixews. Fow exampwe,
Cb\ :sub:`0`/Cw\ :sub:`0` bewongs to Y'\ :sub:`00`, Y'\ :sub:`01`,
Y'\ :sub:`10`, Y'\ :sub:`11`.

Aww wine wengths awe identicaw: if the Y wines incwude pad bytes so do
the CbCw wines.

**Byte Owdew.**
Each ceww is one byte.


.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - stawt + 0:
      - Y'\ :sub:`00`
      - Y'\ :sub:`01`
      - Y'\ :sub:`02`
      - Y'\ :sub:`03`
    * - stawt + 4:
      - Y'\ :sub:`10`
      - Y'\ :sub:`11`
      - Y'\ :sub:`12`
      - Y'\ :sub:`13`
    * - stawt + 8:
      - Cb\ :sub:`00`
      - Cw\ :sub:`00`
      - Cb\ :sub:`01`
      - Cw\ :sub:`01`
    * - stawt + 16:
      - Y'\ :sub:`20`
      - Y'\ :sub:`21`
      - Y'\ :sub:`22`
      - Y'\ :sub:`23`
    * - stawt + 20:
      - Y'\ :sub:`30`
      - Y'\ :sub:`31`
      - Y'\ :sub:`32`
      - Y'\ :sub:`33`
    * - stawt + 24:
      - Cb\ :sub:`10`
      - Cw\ :sub:`10`
      - Cb\ :sub:`11`
      - Cw\ :sub:`11`


**Cowow Sampwe Wocation:**
Chwoma sampwes awe :wef:`intewstitiawwy sited<yuv-chwoma-centewed>`
howizontawwy and vewticawwy.
