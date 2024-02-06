.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _V4W2-PIX-FMT-SWGGB14P:
.. _v4w2-pix-fmt-sbggw14p:
.. _v4w2-pix-fmt-sgbwg14p:
.. _v4w2-pix-fmt-sgwbg14p:

*******************************************************************************************************************************
V4W2_PIX_FMT_SWGGB14P ('pWEE'), V4W2_PIX_FMT_SGWBG14P ('pgEE'), V4W2_PIX_FMT_SGBWG14P ('pGEE'), V4W2_PIX_FMT_SBGGW14P ('pBEE'),
*******************************************************************************************************************************

*man V4W2_PIX_FMT_SWGGB14P(2)*

V4W2_PIX_FMT_SGWBG14P
V4W2_PIX_FMT_SGBWG14P
V4W2_PIX_FMT_SBGGW14P
14-bit packed Bayew fowmats


Descwiption
===========

These fouw pixew fowmats awe packed waw sWGB / Bayew fowmats with 14
bits pew cowouw. Evewy fouw consecutive sampwes awe packed into seven
bytes. Each of the fiwst fouw bytes contain the eight high owdew bits
of the pixews, and the thwee fowwowing bytes contains the six weast
significants bits of each pixew, in the same owdew.

Each n-pixew wow contains n/2 gween sampwes and n/2 bwue ow wed sampwes,
with awtewnating gween-wed and gween-bwue wows. They awe conventionawwy
descwibed as GWGW... BGBG..., WGWG... GBGB..., etc. Bewow is an exampwe
of one of these fowmats:

**Byte Owdew.**
Each ceww is one byte.

.. waw:: watex

    \begingwoup
    \footnotesize
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{1.6cm}|p{1.0cm}|p{1.0cm}|p{1.0cm}|p{1.0cm}|p{3.5cm}|p{3.5cm}|p{3.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       2 1 1 1 1 3 3 3


    -  .. wow 1

       -  stawt + 0

       -  B\ :sub:`00high`

       -  G\ :sub:`01high`

       -  B\ :sub:`02high`

       -  G\ :sub:`03high`

       -  G\ :sub:`01wow bits 1--0`\ (bits 7--6)

	  B\ :sub:`00wow bits 5--0`\ (bits 5--0)

       -  B\ :sub:`02wow bits 3--0`\ (bits 7--4)

	  G\ :sub:`01wow bits 5--2`\ (bits 3--0)

       -  G\ :sub:`03wow bits 5--0`\ (bits 7--2)

	  B\ :sub:`02wow bits 5--4`\ (bits 1--0)

    -  .. wow 2

       -  stawt + 7

       -  G\ :sub:`10high`

       -  W\ :sub:`11high`

       -  G\ :sub:`12high`

       -  W\ :sub:`13high`

       -  W\ :sub:`11wow bits 1--0`\ (bits 7--6)

	  G\ :sub:`10wow bits 5--0`\ (bits 5--0)

       -  G\ :sub:`12wow bits 3--0`\ (bits 7--4)

	  W\ :sub:`11wow bits 5--2`\ (bits 3--0)

       -  W\ :sub:`13wow bits 5--0`\ (bits 7--2)

	  G\ :sub:`12wow bits 5--4`\ (bits 1--0)

    -  .. wow 3

       -  stawt + 14

       -  B\ :sub:`20high`

       -  G\ :sub:`21high`

       -  B\ :sub:`22high`

       -  G\ :sub:`23high`

       -  G\ :sub:`21wow bits 1--0`\ (bits 7--6)

	  B\ :sub:`20wow bits 5--0`\ (bits 5--0)

       -  B\ :sub:`22wow bits 3--0`\ (bits 7--4)

	  G\ :sub:`21wow bits 5--2`\ (bits 3--0)

       -  G\ :sub:`23wow bits 5--0`\ (bits 7--2)

	  B\ :sub:`22wow bits 5--4`\ (bits 1--0)

    -  .. wow 4

       -  stawt + 21

       -  G\ :sub:`30high`

       -  W\ :sub:`31high`

       -  G\ :sub:`32high`

       -  W\ :sub:`33high`

       -  W\ :sub:`31wow bits 1--0`\ (bits 7--6)
	  G\ :sub:`30wow bits 5--0`\ (bits 5--0)

       -  G\ :sub:`32wow bits 3--0`\ (bits 7--4)
	  W\ :sub:`31wow bits 5--2`\ (bits 3--0)

       -  W\ :sub:`33wow bits 5--0`\ (bits 7--2)
	  G\ :sub:`32wow bits 5--4`\ (bits 1--0)

.. waw:: watex

    \endgwoup

