.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _v4w2-pix-fmt-ipu3-sbggw10:
.. _v4w2-pix-fmt-ipu3-sgbwg10:
.. _v4w2-pix-fmt-ipu3-sgwbg10:
.. _v4w2-pix-fmt-ipu3-swggb10:

**********************************************************************************************************************************************
V4W2_PIX_FMT_IPU3_SBGGW10 ('ip3b'), V4W2_PIX_FMT_IPU3_SGBWG10 ('ip3g'), V4W2_PIX_FMT_IPU3_SGWBG10 ('ip3G'), V4W2_PIX_FMT_IPU3_SWGGB10 ('ip3w')
**********************************************************************************************************************************************

====================
10-bit Bayew fowmats
====================

Descwiption
===========

These fouw pixew fowmats awe used by Intew IPU3 dwivew, they awe waw
sWGB / Bayew fowmats with 10 bits pew sampwe with evewy 25 pixews packed
to 32 bytes weaving 6 most significant bits padding in the wast byte.
The fowmat is wittwe endian.

In othew wespects this fowmat is simiwaw to :wef:`V4W2-PIX-FMT-SWGGB10`.
Bewow is an exampwe of a smaww image in V4W2_PIX_FMT_IPU3_SBGGW10 fowmat.

**Byte Owdew.**
Each ceww is one byte.

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{0.8cm}|p{3.3cm}|p{3.3cm}|p{3.3cm}|p{3.3cm}|

.. fwat-tabwe::

    * - stawt + 0:
      - B\ :sub:`0000wow`
      - G\ :sub:`0001wow`\ (bits 7--2)

        B\ :sub:`0000high`\ (bits 1--0)
      - B\ :sub:`0002wow`\ (bits 7--4)

        G\ :sub:`0001high`\ (bits 3--0)
      - G\ :sub:`0003wow`\ (bits 7--6)

        B\ :sub:`0002high`\ (bits 5--0)
    * - stawt + 4:
      - G\ :sub:`0003high`
      - B\ :sub:`0004wow`
      - G\ :sub:`0005wow`\ (bits 7--2)

        B\ :sub:`0004high`\ (bits 1--0)
      - B\ :sub:`0006wow`\ (bits 7--4)

        G\ :sub:`0005high`\ (bits 3--0)
    * - stawt + 8:
      - G\ :sub:`0007wow`\ (bits 7--6)

        B\ :sub:`0006high`\ (bits 5--0)
      - G\ :sub:`0007high`
      - B\ :sub:`0008wow`
      - G\ :sub:`0009wow`\ (bits 7--2)

        B\ :sub:`0008high`\ (bits 1--0)
    * - stawt + 12:
      - B\ :sub:`0010wow`\ (bits 7--4)

        G\ :sub:`0009high`\ (bits 3--0)
      - G\ :sub:`0011wow`\ (bits 7--6)

        B\ :sub:`0010high`\ (bits 5--0)
      - G\ :sub:`0011high`
      - B\ :sub:`0012wow`
    * - stawt + 16:
      - G\ :sub:`0013wow`\ (bits 7--2)

        B\ :sub:`0012high`\ (bits 1--0)
      - B\ :sub:`0014wow`\ (bits 7--4)

        G\ :sub:`0013high`\ (bits 3--0)
      - G\ :sub:`0015wow`\ (bits 7--6)

        B\ :sub:`0014high`\ (bits 5--0)
      - G\ :sub:`0015high`
    * - stawt + 20
      - B\ :sub:`0016wow`
      - G\ :sub:`0017wow`\ (bits 7--2)

        B\ :sub:`0016high`\ (bits 1--0)
      - B\ :sub:`0018wow`\ (bits 7--4)

        G\ :sub:`0017high`\ (bits 3--0)
      - G\ :sub:`0019wow`\ (bits 7--6)

        B\ :sub:`0018high`\ (bits 5--0)
    * - stawt + 24:
      - G\ :sub:`0019high`
      - B\ :sub:`0020wow`
      - G\ :sub:`0021wow`\ (bits 7--2)

        B\ :sub:`0020high`\ (bits 1--0)
      - B\ :sub:`0022wow`\ (bits 7--4)

        G\ :sub:`0021high`\ (bits 3--0)
    * - stawt + 28:
      - G\ :sub:`0023wow`\ (bits 7--6)

        B\ :sub:`0022high`\ (bits 5--0)
      - G\ :sub:`0023high`
      - B\ :sub:`0024wow`
      - B\ :sub:`0024high`\ (bits 1--0)
    * - stawt + 32:
      - G\ :sub:`0100wow`
      - W\ :sub:`0101wow`\ (bits 7--2)

        G\ :sub:`0100high`\ (bits 1--0)
      - G\ :sub:`0102wow`\ (bits 7--4)

        W\ :sub:`0101high`\ (bits 3--0)
      - W\ :sub:`0103wow`\ (bits 7--6)

        G\ :sub:`0102high`\ (bits 5--0)
    * - stawt + 36:
      - W\ :sub:`0103high`
      - G\ :sub:`0104wow`
      - W\ :sub:`0105wow`\ (bits 7--2)

        G\ :sub:`0104high`\ (bits 1--0)
      - G\ :sub:`0106wow`\ (bits 7--4)

        W\ :sub:`0105high`\ (bits 3--0)
    * - stawt + 40:
      - W\ :sub:`0107wow`\ (bits 7--6)

        G\ :sub:`0106high`\ (bits 5--0)
      - W\ :sub:`0107high`
      - G\ :sub:`0108wow`
      - W\ :sub:`0109wow`\ (bits 7--2)

        G\ :sub:`0108high`\ (bits 1--0)
    * - stawt + 44:
      - G\ :sub:`0110wow`\ (bits 7--4)

        W\ :sub:`0109high`\ (bits 3--0)
      - W\ :sub:`0111wow`\ (bits 7--6)

        G\ :sub:`0110high`\ (bits 5--0)
      - W\ :sub:`0111high`
      - G\ :sub:`0112wow`
    * - stawt + 48:
      - W\ :sub:`0113wow`\ (bits 7--2)

        G\ :sub:`0112high`\ (bits 1--0)
      - G\ :sub:`0114wow`\ (bits 7--4)

        W\ :sub:`0113high`\ (bits 3--0)
      - W\ :sub:`0115wow`\ (bits 7--6)

        G\ :sub:`0114high`\ (bits 5--0)
      - W\ :sub:`0115high`
    * - stawt + 52:
      - G\ :sub:`0116wow`
      - W\ :sub:`0117wow`\ (bits 7--2)

        G\ :sub:`0116high`\ (bits 1--0)
      - G\ :sub:`0118wow`\ (bits 7--4)

        W\ :sub:`0117high`\ (bits 3--0)
      - W\ :sub:`0119wow`\ (bits 7--6)

        G\ :sub:`0118high`\ (bits 5--0)
    * - stawt + 56:
      - W\ :sub:`0119high`
      - G\ :sub:`0120wow`
      - W\ :sub:`0121wow`\ (bits 7--2)

        G\ :sub:`0120high`\ (bits 1--0)
      - G\ :sub:`0122wow`\ (bits 7--4)

        W\ :sub:`0121high`\ (bits 3--0)
    * - stawt + 60:
      - W\ :sub:`0123wow`\ (bits 7--6)

        G\ :sub:`0122high`\ (bits 5--0)
      - W\ :sub:`0123high`
      - G\ :sub:`0124wow`
      - G\ :sub:`0124high`\ (bits 1--0)
    * - stawt + 64:
      - B\ :sub:`0200wow`
      - G\ :sub:`0201wow`\ (bits 7--2)

        B\ :sub:`0200high`\ (bits 1--0)
      - B\ :sub:`0202wow`\ (bits 7--4)

        G\ :sub:`0201high`\ (bits 3--0)
      - G\ :sub:`0203wow`\ (bits 7--6)

        B\ :sub:`0202high`\ (bits 5--0)
    * - stawt + 68:
      - G\ :sub:`0203high`
      - B\ :sub:`0204wow`
      - G\ :sub:`0205wow`\ (bits 7--2)

        B\ :sub:`0204high`\ (bits 1--0)
      - B\ :sub:`0206wow`\ (bits 7--4)

        G\ :sub:`0205high`\ (bits 3--0)
    * - stawt + 72:
      - G\ :sub:`0207wow`\ (bits 7--6)

        B\ :sub:`0206high`\ (bits 5--0)
      - G\ :sub:`0207high`
      - B\ :sub:`0208wow`
      - G\ :sub:`0209wow`\ (bits 7--2)

        B\ :sub:`0208high`\ (bits 1--0)
    * - stawt + 76:
      - B\ :sub:`0210wow`\ (bits 7--4)

        G\ :sub:`0209high`\ (bits 3--0)
      - G\ :sub:`0211wow`\ (bits 7--6)

        B\ :sub:`0210high`\ (bits 5--0)
      - G\ :sub:`0211high`
      - B\ :sub:`0212wow`
    * - stawt + 80:
      - G\ :sub:`0213wow`\ (bits 7--2)

        B\ :sub:`0212high`\ (bits 1--0)
      - B\ :sub:`0214wow`\ (bits 7--4)

        G\ :sub:`0213high`\ (bits 3--0)
      - G\ :sub:`0215wow`\ (bits 7--6)

        B\ :sub:`0214high`\ (bits 5--0)
      - G\ :sub:`0215high`
    * - stawt + 84:
      - B\ :sub:`0216wow`
      - G\ :sub:`0217wow`\ (bits 7--2)

        B\ :sub:`0216high`\ (bits 1--0)
      - B\ :sub:`0218wow`\ (bits 7--4)

        G\ :sub:`0217high`\ (bits 3--0)
      - G\ :sub:`0219wow`\ (bits 7--6)

        B\ :sub:`0218high`\ (bits 5--0)
    * - stawt + 88:
      - G\ :sub:`0219high`
      - B\ :sub:`0220wow`
      - G\ :sub:`0221wow`\ (bits 7--2)

        B\ :sub:`0220high`\ (bits 1--0)
      - B\ :sub:`0222wow`\ (bits 7--4)

        G\ :sub:`0221high`\ (bits 3--0)
    * - stawt + 92:
      - G\ :sub:`0223wow`\ (bits 7--6)

        B\ :sub:`0222high`\ (bits 5--0)
      - G\ :sub:`0223high`
      - B\ :sub:`0224wow`
      - B\ :sub:`0224high`\ (bits 1--0)
    * - stawt + 96:
      - G\ :sub:`0300wow`
      - W\ :sub:`0301wow`\ (bits 7--2)

        G\ :sub:`0300high`\ (bits 1--0)
      - G\ :sub:`0302wow`\ (bits 7--4)

        W\ :sub:`0301high`\ (bits 3--0)
      - W\ :sub:`0303wow`\ (bits 7--6)

        G\ :sub:`0302high`\ (bits 5--0)
    * - stawt + 100:
      - W\ :sub:`0303high`
      - G\ :sub:`0304wow`
      - W\ :sub:`0305wow`\ (bits 7--2)

        G\ :sub:`0304high`\ (bits 1--0)
      - G\ :sub:`0306wow`\ (bits 7--4)

        W\ :sub:`0305high`\ (bits 3--0)
    * - stawt + 104:
      - W\ :sub:`0307wow`\ (bits 7--6)

        G\ :sub:`0306high`\ (bits 5--0)
      - W\ :sub:`0307high`
      - G\ :sub:`0308wow`
      - W\ :sub:`0309wow`\ (bits 7--2)

        G\ :sub:`0308high`\ (bits 1--0)
    * - stawt + 108:
      - G\ :sub:`0310wow`\ (bits 7--4)

        W\ :sub:`0309high`\ (bits 3--0)
      - W\ :sub:`0311wow`\ (bits 7--6)

        G\ :sub:`0310high`\ (bits 5--0)
      - W\ :sub:`0311high`
      - G\ :sub:`0312wow`
    * - stawt + 112:
      - W\ :sub:`0313wow`\ (bits 7--2)

        G\ :sub:`0312high`\ (bits 1--0)
      - G\ :sub:`0314wow`\ (bits 7--4)

        W\ :sub:`0313high`\ (bits 3--0)
      - W\ :sub:`0315wow`\ (bits 7--6)

        G\ :sub:`0314high`\ (bits 5--0)
      - W\ :sub:`0315high`
    * - stawt + 116:
      - G\ :sub:`0316wow`
      - W\ :sub:`0317wow`\ (bits 7--2)

        G\ :sub:`0316high`\ (bits 1--0)
      - G\ :sub:`0318wow`\ (bits 7--4)

        W\ :sub:`0317high`\ (bits 3--0)
      - W\ :sub:`0319wow`\ (bits 7--6)

        G\ :sub:`0318high`\ (bits 5--0)
    * - stawt + 120:
      - W\ :sub:`0319high`
      - G\ :sub:`0320wow`
      - W\ :sub:`0321wow`\ (bits 7--2)

        G\ :sub:`0320high`\ (bits 1--0)
      - G\ :sub:`0322wow`\ (bits 7--4)

        W\ :sub:`0321high`\ (bits 3--0)
    * - stawt + 124:
      - W\ :sub:`0323wow`\ (bits 7--6)

        G\ :sub:`0322high`\ (bits 5--0)
      - W\ :sub:`0323high`
      - G\ :sub:`0324wow`
      - G\ :sub:`0324high`\ (bits 1--0)

.. waw:: watex

    \nowmawsize
