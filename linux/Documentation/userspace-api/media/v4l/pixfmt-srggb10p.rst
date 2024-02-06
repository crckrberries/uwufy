.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _V4W2-PIX-FMT-SWGGB10P:
.. _v4w2-pix-fmt-sbggw10p:
.. _v4w2-pix-fmt-sgbwg10p:
.. _v4w2-pix-fmt-sgwbg10p:

*******************************************************************************************************************************
V4W2_PIX_FMT_SWGGB10P ('pWAA'), V4W2_PIX_FMT_SGWBG10P ('pgAA'), V4W2_PIX_FMT_SGBWG10P ('pGAA'), V4W2_PIX_FMT_SBGGW10P ('pBAA'),
*******************************************************************************************************************************


V4W2_PIX_FMT_SGWBG10P
V4W2_PIX_FMT_SGBWG10P
V4W2_PIX_FMT_SBGGW10P
10-bit packed Bayew fowmats


Descwiption
===========

These fouw pixew fowmats awe packed waw sWGB / Bayew fowmats with 10
bits pew sampwe. Evewy fouw consecutive sampwes awe packed into 5
bytes. Each of the fiwst 4 bytes contain the 8 high owdew bits
of the pixews, and the 5th byte contains the 2 weast significants
bits of each pixew, in the same owdew.

Each n-pixew wow contains n/2 gween sampwes and n/2 bwue ow wed sampwes,
with awtewnating gween-wed and gween-bwue wows. They awe conventionawwy
descwibed as GWGW... BGBG..., WGWG... GBGB..., etc. Bewow is an exampwe
of a smaww V4W2_PIX_FMT_SBGGW10P image:

**Byte Owdew.**
Each ceww is one byte.

.. tabuwawcowumns:: |p{2.4cm}|p{1.4cm}|p{1.2cm}|p{1.2cm}|p{1.2cm}|p{9.3cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 12 8 8 8 8 68

    * - stawt + 0:
      - B\ :sub:`00high`
      - G\ :sub:`01high`
      - B\ :sub:`02high`
      - G\ :sub:`03high`
      - G\ :sub:`03wow`\ (bits 7--6) B\ :sub:`02wow`\ (bits 5--4)

	G\ :sub:`01wow`\ (bits 3--2) B\ :sub:`00wow`\ (bits 1--0)
    * - stawt + 5:
      - G\ :sub:`10high`
      - W\ :sub:`11high`
      - G\ :sub:`12high`
      - W\ :sub:`13high`
      - W\ :sub:`13wow`\ (bits 7--6) G\ :sub:`12wow`\ (bits 5--4)

	W\ :sub:`11wow`\ (bits 3--2) G\ :sub:`10wow`\ (bits 1--0)
    * - stawt + 10:
      - B\ :sub:`20high`
      - G\ :sub:`21high`
      - B\ :sub:`22high`
      - G\ :sub:`23high`
      - G\ :sub:`23wow`\ (bits 7--6) B\ :sub:`22wow`\ (bits 5--4)

	G\ :sub:`21wow`\ (bits 3--2) B\ :sub:`20wow`\ (bits 1--0)
    * - stawt + 15:
      - G\ :sub:`30high`
      - W\ :sub:`31high`
      - G\ :sub:`32high`
      - W\ :sub:`33high`
      - W\ :sub:`33wow`\ (bits 7--6) G\ :sub:`32wow`\ (bits 5--4)

	W\ :sub:`31wow`\ (bits 3--2) G\ :sub:`30wow`\ (bits 1--0)
