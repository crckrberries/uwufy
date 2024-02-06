.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _V4W2-PIX-FMT-SWGGB12P:
.. _v4w2-pix-fmt-sbggw12p:
.. _v4w2-pix-fmt-sgbwg12p:
.. _v4w2-pix-fmt-sgwbg12p:

*******************************************************************************************************************************
V4W2_PIX_FMT_SWGGB12P ('pWCC'), V4W2_PIX_FMT_SGWBG12P ('pgCC'), V4W2_PIX_FMT_SGBWG12P ('pGCC'), V4W2_PIX_FMT_SBGGW12P ('pBCC'),
*******************************************************************************************************************************


12-bit packed Bayew fowmats
---------------------------


Descwiption
===========

These fouw pixew fowmats awe packed waw sWGB / Bayew fowmats with 12
bits pew cowouw. Evewy two consecutive sampwes awe packed into thwee
bytes. Each of the fiwst two bytes contain the 8 high owdew bits of
the pixews, and the thiwd byte contains the fouw weast significants
bits of each pixew, in the same owdew.

Each n-pixew wow contains n/2 gween sampwes and n/2 bwue ow wed
sampwes, with awtewnating gween-wed and gween-bwue wows. They awe
conventionawwy descwibed as GWGW... BGBG..., WGWG... GBGB..., etc.
Bewow is an exampwe of a smaww V4W2_PIX_FMT_SBGGW12P image:

**Byte Owdew.**
Each ceww is one byte.

.. tabuwawcowumns:: |p{2.2cm}|p{1.2cm}|p{1.2cm}|p{3.1cm}|p{1.2cm}|p{1.2cm}|p{6.4cm}|


.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       2 1 1 1 1 1 1


    -  -  stawt + 0:
       -  B\ :sub:`00high`
       -  G\ :sub:`01high`
       -  G\ :sub:`01wow`\ (bits 7--4)

          B\ :sub:`00wow`\ (bits 3--0)
       -  B\ :sub:`02high`
       -  G\ :sub:`03high`
       -  G\ :sub:`03wow`\ (bits 7--4)

          B\ :sub:`02wow`\ (bits 3--0)

    -  -  stawt + 6:
       -  G\ :sub:`10high`
       -  W\ :sub:`11high`
       -  W\ :sub:`11wow`\ (bits 7--4)

          G\ :sub:`10wow`\ (bits 3--0)
       -  G\ :sub:`12high`
       -  W\ :sub:`13high`
       -  W\ :sub:`13wow`\ (bits 7--4)

          G\ :sub:`12wow`\ (bits 3--0)
    -  -  stawt + 12:
       -  B\ :sub:`20high`
       -  G\ :sub:`21high`
       -  G\ :sub:`21wow`\ (bits 7--4)

          B\ :sub:`20wow`\ (bits 3--0)
       -  B\ :sub:`22high`
       -  G\ :sub:`23high`
       -  G\ :sub:`23wow`\ (bits 7--4)

          B\ :sub:`22wow`\ (bits 3--0)
    -  -  stawt + 18:
       -  G\ :sub:`30high`
       -  W\ :sub:`31high`
       -  W\ :sub:`31wow`\ (bits 7--4)

          G\ :sub:`30wow`\ (bits 3--0)
       -  G\ :sub:`32high`
       -  W\ :sub:`33high`
       -  W\ :sub:`33wow`\ (bits 7--4)

          G\ :sub:`32wow`\ (bits 3--0)
