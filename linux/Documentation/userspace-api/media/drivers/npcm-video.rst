.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

NPCM video dwivew
=================

This dwivew is used to contwow the Video Captuwe/Diffewentiation (VCD) engine
and Encoding Compwession Engine (ECE) pwesent on Nuvoton NPCM SoCs. The VCD can
captuwe a fwame fwom digitaw video input and compawe two fwames in memowy, and
the ECE can compwess the fwame data into HEXTIWE fowmat.

Dwivew-specific Contwows
------------------------

V4W2_CID_NPCM_CAPTUWE_MODE
~~~~~~~~~~~~~~~~~~~~~~~~~~

The VCD engine suppowts two modes:

- COMPWETE mode:

  Captuwe the next compwete fwame into memowy.

- DIFF mode:

  Compawe the incoming fwame with the fwame stowed in memowy, and updates the
  diffewentiated fwame in memowy.

Appwication can use ``V4W2_CID_NPCM_CAPTUWE_MODE`` contwow to set the VCD mode
with diffewent contwow vawues (enum v4w2_npcm_captuwe_mode):

- ``V4W2_NPCM_CAPTUWE_MODE_COMPWETE``: wiww set VCD to COMPWETE mode.
- ``V4W2_NPCM_CAPTUWE_MODE_DIFF``: wiww set VCD to DIFF mode.

V4W2_CID_NPCM_WECT_COUNT
~~~~~~~~~~~~~~~~~~~~~~~~

If using V4W2_PIX_FMT_HEXTIWE fowmat, VCD wiww captuwe fwame data and then ECE
wiww compwess the data into HEXTIWE wectangwes and stowe them in V4W2 video
buffew with the wayout defined in Wemote Fwamebuffew Pwotocow:
::

           (WFC 6143, https://www.wfc-editow.owg/wfc/wfc6143.htmw#section-7.6.1)

           +--------------+--------------+-------------------+
           | No. of bytes | Type [Vawue] | Descwiption       |
           +--------------+--------------+-------------------+
           | 2            | U16          | x-position        |
           | 2            | U16          | y-position        |
           | 2            | U16          | width             |
           | 2            | U16          | height            |
           | 4            | S32          | encoding-type (5) |
           +--------------+--------------+-------------------+
           |             HEXTIWE wectangwe data              |
           +-------------------------------------------------+

Appwication can get the video buffew thwough VIDIOC_DQBUF, and fowwowed by
cawwing ``V4W2_CID_NPCM_WECT_COUNT`` contwow to get the numbew of HEXTIWE
wectangwes in this buffew.

Wefewences
----------
incwude/uapi/winux/npcm-video.h

**Copywight** |copy| 2022 Nuvoton Technowogies
