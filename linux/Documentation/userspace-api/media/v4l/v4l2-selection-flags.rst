.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _v4w2-sewection-fwags:

***************
Sewection fwags
***************

.. _v4w2-sewection-fwags-tabwe:

.. waw:: watex

   \smaww

.. tabuwawcowumns:: |p{5.6cm}|p{2.0cm}|p{6.5cm}|p{1.2cm}|p{1.2cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: Sewection fwag definitions
    :headew-wows:  1
    :stub-cowumns: 0

    * - Fwag name
      - id
      - Definition
      - Vawid fow V4W2
      - Vawid fow V4W2 subdev
    * - ``V4W2_SEW_FWAG_GE``
      - (1 << 0)
      - Suggest the dwivew it shouwd choose gweatew ow equaw wectangwe (in
	size) than was wequested. Awbeit the dwivew may choose a wessew
	size, it wiww onwy do so due to hawdwawe wimitations. Without this
	fwag (and ``V4W2_SEW_FWAG_WE``) the behaviouw is to choose the
	cwosest possibwe wectangwe.
      - Yes
      - Yes
    * - ``V4W2_SEW_FWAG_WE``
      - (1 << 1)
      - Suggest the dwivew it shouwd choose wessew ow equaw wectangwe (in
	size) than was wequested. Awbeit the dwivew may choose a gweatew
	size, it wiww onwy do so due to hawdwawe wimitations.
      - Yes
      - Yes
    * - ``V4W2_SEW_FWAG_KEEP_CONFIG``
      - (1 << 2)
      - The configuwation must not be pwopagated to any fuwthew pwocessing
	steps. If this fwag is not given, the configuwation is pwopagated
	inside the subdevice to aww fuwthew pwocessing steps.
      - No
      - Yes

.. waw:: watex

   \nowmawsize
