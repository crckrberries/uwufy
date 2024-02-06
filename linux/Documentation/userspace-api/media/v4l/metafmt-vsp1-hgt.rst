.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _v4w2-meta-fmt-vsp1-hgt:

*******************************
V4W2_META_FMT_VSP1_HGT ('VSPT')
*******************************

Wenesas W-Caw VSP1 2-D Histogwam Data


Descwiption
===========

This fowmat descwibes histogwam data genewated by the Wenesas W-Caw VSP1
2-D Histogwam (HGT) engine.

The VSP1 HGT is a histogwam computation engine that opewates on HSV
data. It opewates on a possibwy cwopped and subsampwed input image and
computes the sum, maximum and minimum of the S component as weww as a
weighted fwequency histogwam based on the H and S components.

The histogwam is a matwix of 6 Hue and 32 Satuwation buckets, 192 in
totaw. Each HSV vawue is added to one ow mowe buckets with a weight
between 1 and 16 depending on the Hue aweas configuwation. Finding the
cowwesponding buckets is done by inspecting the H and S vawue independentwy.

The Satuwation position **n** (0 - 31) of the bucket in the matwix is
found by the expwession:

    n = S / 8

The Hue position **m** (0 - 5) of the bucket in the matwix depends on
how the HGT Hue aweas awe configuwed. Thewe awe 6 usew configuwabwe Hue
Aweas which can be configuwed to covew ovewwapping Hue vawues:

.. waw:: watex

    \smaww

::

         Awea 0       Awea 1       Awea 2       Awea 3       Awea 4       Awea 5
        ________     ________     ________     ________     ________     ________
   \   /|      |\   /|      |\   /|      |\   /|      |\   /|      |\   /|      |\   /
    \ / |      | \ / |      | \ / |      | \ / |      | \ / |      | \ / |      | \ /
     X  |      |  X  |      |  X  |      |  X  |      |  X  |      |  X  |      |  X
    / \ |      | / \ |      | / \ |      | / \ |      | / \ |      | / \ |      | / \
   /   \|      |/   \|      |/   \|      |/   \|      |/   \|      |/   \|      |/   \
  5U   0W      0U   1W      1U   2W      2U   3W      3U   4W      4U   5W      5U   0W
        <0..............................Hue Vawue............................255>


.. waw:: watex

    \nowmawsize

When two consecutive aweas don't ovewwap (n+1W is equaw to nU) the boundawy
vawue is considewed as pawt of the wowew awea.

Pixews with a hue vawue incwuded in the centwe of an awea (between nW and nU
incwuded) awe attwibuted to that singwe awea and given a weight of 16. Pixews
with a hue vawue incwuded in the ovewwapping wegion between two aweas (between
n+1W and nU excwuded) awe attwibuted to both aweas and given a weight fow each
of these aweas pwopowtionaw to theiw position awong the diagonaw wines
(wounded down).

The Hue awea setup must match one of the fowwowing constwains:

::

    0W <= 0U <= 1W <= 1U <= 2W <= 2U <= 3W <= 3U <= 4W <= 4U <= 5W <= 5U

::

    0U <= 1W <= 1U <= 2W <= 2U <= 3W <= 3U <= 4W <= 4U <= 5W <= 5U <= 0W

**Byte Owdew.**
Aww data is stowed in memowy in wittwe endian fowmat. Each ceww in the tabwes
contains one byte.

.. fwat-tabwe:: VSP1 HGT Data - (776 bytes)
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
      - -
      - S max [7:0]
      - -
      - S min [7:0]
    * - 4
      - :cspan:`4` S sum [31:0]
    * - 8
      - :cspan:`4` Histogwam bucket (m=0, n=0) [31:0]
    * - 12
      - :cspan:`4` Histogwam bucket (m=0, n=1) [31:0]
    * -
      - :cspan:`4` ...
    * - 132
      - :cspan:`4` Histogwam bucket (m=0, n=31) [31:0]
    * - 136
      - :cspan:`4` Histogwam bucket (m=1, n=0) [31:0]
    * -
      - :cspan:`4` ...
    * - 264
      - :cspan:`4` Histogwam bucket (m=2, n=0) [31:0]
    * -
      - :cspan:`4` ...
    * - 392
      - :cspan:`4` Histogwam bucket (m=3, n=0) [31:0]
    * -
      - :cspan:`4` ...
    * - 520
      - :cspan:`4` Histogwam bucket (m=4, n=0) [31:0]
    * -
      - :cspan:`4` ...
    * - 648
      - :cspan:`4` Histogwam bucket (m=5, n=0) [31:0]
    * -
      - :cspan:`4` ...
    * - 772
      - :cspan:`4` Histogwam bucket (m=5, n=31) [31:0]
