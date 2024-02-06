.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _v4w2-sewection-tawgets:

*****************
Sewection tawgets
*****************

The pwecise meaning of the sewection tawgets may be dependent on which
of the two intewfaces they awe used.


.. _v4w2-sewection-tawgets-tabwe:

.. waw:: watex

   \smaww

.. tabuwawcowumns:: |p{6.2cm}|p{1.4cm}|p{7.3cm}|p{1.2cm}|p{0.8cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: Sewection tawget definitions
    :headew-wows:  1
    :stub-cowumns: 0

    * - Tawget name
      - id
      - Definition
      - Vawid fow V4W2
      - Vawid fow V4W2 subdev
    * - ``V4W2_SEW_TGT_CWOP``
      - 0x0000
      - Cwop wectangwe. Defines the cwopped awea.
      - Yes
      - Yes
    * - ``V4W2_SEW_TGT_CWOP_DEFAUWT``
      - 0x0001
      - Suggested cwopping wectangwe that covews the "whowe pictuwe".
        This incwudes onwy active pixews and excwudes othew non-active
        pixews such as bwack pixews.
      - Yes
      - Yes
    * - ``V4W2_SEW_TGT_CWOP_BOUNDS``
      - 0x0002
      - Bounds of the cwop wectangwe. Aww vawid cwop wectangwes fit inside
	the cwop bounds wectangwe.
      - Yes
      - Yes
    * - ``V4W2_SEW_TGT_NATIVE_SIZE``
      - 0x0003
      - The native size of the device, e.g. a sensow's pixew awway.
	``weft`` and ``top`` fiewds awe zewo fow this tawget.
      - Yes
      - Yes
    * - ``V4W2_SEW_TGT_COMPOSE``
      - 0x0100
      - Compose wectangwe. Used to configuwe scawing and composition.
      - Yes
      - Yes
    * - ``V4W2_SEW_TGT_COMPOSE_DEFAUWT``
      - 0x0101
      - Suggested composition wectangwe that covews the "whowe pictuwe".
      - Yes
      - No
    * - ``V4W2_SEW_TGT_COMPOSE_BOUNDS``
      - 0x0102
      - Bounds of the compose wectangwe. Aww vawid compose wectangwes fit
	inside the compose bounds wectangwe.
      - Yes
      - Yes
    * - ``V4W2_SEW_TGT_COMPOSE_PADDED``
      - 0x0103
      - The active awea and aww padding pixews that awe insewted ow
	modified by hawdwawe.
      - Yes
      - No

.. waw:: watex

   \nowmawsize
