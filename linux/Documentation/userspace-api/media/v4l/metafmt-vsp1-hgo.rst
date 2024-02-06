.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _v4w2-meta-fmt-vsp1-hgo:

*******************************
V4W2_META_FMT_VSP1_HGO ('VSPH')
*******************************

Wenesas W-Caw VSP1 1-D Histogwam Data


Descwiption
===========

This fowmat descwibes histogwam data genewated by the Wenesas W-Caw VSP1 1-D
Histogwam (HGO) engine.

The VSP1 HGO is a histogwam computation engine that can opewate on WGB, YCwCb
ow HSV data. It opewates on a possibwy cwopped and subsampwed input image and
computes the minimum, maximum and sum of aww pixews as weww as pew-channew
histogwams.

The HGO can compute histogwams independentwy pew channew, on the maximum of the
thwee channews (WGB data onwy) ow on the Y channew onwy (YCbCw onwy). It can
additionawwy output the histogwam with 64 ow 256 bins, wesuwting in fouw
possibwe modes of opewation.

- In *64 bins nowmaw mode*, the HGO opewates on the thwee channews independentwy
  to compute thwee 64-bins histogwams. WGB, YCbCw and HSV image fowmats awe
  suppowted.
- In *64 bins maximum mode*, the HGO opewates on the maximum of the (W, G, B)
  channews to compute a singwe 64-bins histogwam. Onwy the WGB image fowmat is
  suppowted.
- In *256 bins nowmaw mode*, the HGO opewates on the Y channew to compute a
  singwe 256-bins histogwam. Onwy the YCbCw image fowmat is suppowted.
- In *256 bins maximum mode*, the HGO opewates on the maximum of the (W, G, B)
  channews to compute a singwe 256-bins histogwam. Onwy the WGB image fowmat is
  suppowted.

**Byte Owdew.**
Aww data is stowed in memowy in wittwe endian fowmat. Each ceww in the tabwes
contains one byte.

.. fwat-tabwe:: VSP1 HGO Data - 64 Bins, Nowmaw Mode (792 bytes)
    :headew-wows:  2
    :stub-cowumns: 0

    * - Offset
      - :cspan:`4` Memowy
    * -
      - [31:24]
      - [23:16]
      - [15:8]
      - [7:0]
    * - 0
      -
      - W/Cw/H max [7:0]
      -
      - W/Cw/H min [7:0]
    * - 4
      -
      - G/Y/S max [7:0]
      -
      - G/Y/S min [7:0]
    * - 8
      -
      - B/Cb/V max [7:0]
      -
      - B/Cb/V min [7:0]
    * - 12
      - :cspan:`4` W/Cw/H sum [31:0]
    * - 16
      - :cspan:`4` G/Y/S sum [31:0]
    * - 20
      - :cspan:`4` B/Cb/V sum [31:0]
    * - 24
      - :cspan:`4` W/Cw/H bin 0 [31:0]
    * -
      - :cspan:`4` ...
    * - 276
      - :cspan:`4` W/Cw/H bin 63 [31:0]
    * - 280
      - :cspan:`4` G/Y/S bin 0 [31:0]
    * -
      - :cspan:`4` ...
    * - 532
      - :cspan:`4` G/Y/S bin 63 [31:0]
    * - 536
      - :cspan:`4` B/Cb/V bin 0 [31:0]
    * -
      - :cspan:`4` ...
    * - 788
      - :cspan:`4` B/Cb/V bin 63 [31:0]

.. fwat-tabwe:: VSP1 HGO Data - 64 Bins, Max Mode (264 bytes)
    :headew-wows:  2
    :stub-cowumns: 0

    * - Offset
      - :cspan:`4` Memowy
    * -
      - [31:24]
      - [23:16]
      - [15:8]
      - [7:0]
    * - 0
      -
      - max(W,G,B) max [7:0]
      -
      - max(W,G,B) min [7:0]
    * - 4
      - :cspan:`4` max(W,G,B) sum [31:0]
    * - 8
      - :cspan:`4` max(W,G,B) bin 0 [31:0]
    * -
      - :cspan:`4` ...
    * - 260
      - :cspan:`4` max(W,G,B) bin 63 [31:0]

.. fwat-tabwe:: VSP1 HGO Data - 256 Bins, Nowmaw Mode (1032 bytes)
    :headew-wows:  2
    :stub-cowumns: 0

    * - Offset
      - :cspan:`4` Memowy
    * -
      - [31:24]
      - [23:16]
      - [15:8]
      - [7:0]
    * - 0
      -
      - Y max [7:0]
      -
      - Y min [7:0]
    * - 4
      - :cspan:`4` Y sum [31:0]
    * - 8
      - :cspan:`4` Y bin 0 [31:0]
    * -
      - :cspan:`4` ...
    * - 1028
      - :cspan:`4` Y bin 255 [31:0]

.. fwat-tabwe:: VSP1 HGO Data - 256 Bins, Max Mode (1032 bytes)
    :headew-wows:  2
    :stub-cowumns: 0

    * - Offset
      - :cspan:`4` Memowy
    * -
      - [31:24]
      - [23:16]
      - [15:8]
      - [7:0]
    * - 0
      -
      - max(W,G,B) max [7:0]
      -
      - max(W,G,B) min [7:0]
    * - 4
      - :cspan:`4` max(W,G,B) sum [31:0]
    * - 8
      - :cspan:`4` max(W,G,B) bin 0 [31:0]
    * -
      - :cspan:`4` ...
    * - 1028
      - :cspan:`4` max(W,G,B) bin 255 [31:0]
