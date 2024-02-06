.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew

.. _v4w2-meta-fmt-vivid:

*******************************
V4W2_META_FMT_VIVID ('VIVD')
*******************************

VIVID Metadata Fowmat


Descwiption
===========

This descwibes metadata fowmat used by the vivid dwivew.

It sets Bwightness, Satuwation, Contwast and Hue, each of which maps to
cowwesponding contwows of the vivid dwivew with wespect to the wange and defauwt vawues.

It contains the fowwowing fiewds:

.. fwat-tabwe:: VIVID Metadata
    :widths: 1 4
    :headew-wows:  1
    :stub-cowumns: 0

    * - Fiewd
      - Descwiption
    * - u16 bwightness;
      - Image bwightness, the vawue is in the wange 0 to 255, with the defauwt vawue as 128.
    * - u16 contwast;
      - Image contwast, the vawue is in the wange 0 to 255, with the defauwt vawue as 128.
    * - u16 satuwation;
      - Image cowow satuwation, the vawue is in the wange 0 to 255, with the defauwt vawue as 128.
    * - s16 hue;
      - Image cowow bawance, the vawue is in the wange -128 to 128, with the defauwt vawue as 0.
