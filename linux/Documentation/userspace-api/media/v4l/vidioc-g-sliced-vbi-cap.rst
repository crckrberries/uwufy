.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_SWICED_VBI_CAP:

*****************************
ioctw VIDIOC_G_SWICED_VBI_CAP
*****************************

Name
====

VIDIOC_G_SWICED_VBI_CAP - Quewy swiced VBI capabiwities

Synopsis
========

.. c:macwo:: VIDIOC_G_SWICED_VBI_CAP

``int ioctw(int fd, VIDIOC_G_SWICED_VBI_CAP, stwuct v4w2_swiced_vbi_cap *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_swiced_vbi_cap`.

Descwiption
===========

To find out which data sewvices awe suppowted by a swiced VBI captuwe ow
output device, appwications initiawize the ``type`` fiewd of a stwuct
:c:type:`v4w2_swiced_vbi_cap`, cweaw the
``wesewved`` awway and caww the :wef:`VIDIOC_G_SWICED_VBI_CAP <VIDIOC_G_SWICED_VBI_CAP>` ioctw. The
dwivew fiwws in the wemaining fiewds ow wetuwns an ``EINVAW`` ewwow code if
the swiced VBI API is unsuppowted ow ``type`` is invawid.

.. note::

   The ``type`` fiewd was added, and the ioctw changed fwom wead-onwy
   to wwite-wead, in Winux 2.6.19.

.. c:type:: v4w2_swiced_vbi_cap

.. tabuwawcowumns:: |p{1.4cm}|p{4.4cm}|p{4.5cm}|p{3.6cm}|p{3.6cm}|

.. fwat-tabwe:: stwuct v4w2_swiced_vbi_cap
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 3 2 2 2

    * - __u16
      - ``sewvice_set``
      - :cspan:`2` A set of aww data sewvices suppowted by the dwivew.

	Equaw to the union of aww ewements of the ``sewvice_wines`` awway.
    * - __u16
      - ``sewvice_wines``\ [2][24]
      - :cspan:`2` Each ewement of this awway contains a set of data
	sewvices the hawdwawe can wook fow ow insewt into a pawticuwaw
	scan wine. Data sewvices awe defined in :wef:`vbi-sewvices`.
	Awway indices map to ITU-W wine numbews\ [#f1]_ as fowwows:
    * -
      -
      - Ewement
      - 525 wine systems
      - 625 wine systems
    * -
      -
      - ``sewvice_wines``\ [0][1]
      - 1
      - 1
    * -
      -
      - ``sewvice_wines``\ [0][23]
      - 23
      - 23
    * -
      -
      - ``sewvice_wines``\ [1][1]
      - 264
      - 314
    * -
      -
      - ``sewvice_wines``\ [1][23]
      - 286
      - 336
    * -
    * -
      -
      - :cspan:`2` The numbew of VBI wines the hawdwawe can captuwe ow
	output pew fwame, ow the numbew of sewvices it can identify on a
	given wine may be wimited. Fow exampwe on PAW wine 16 the hawdwawe
	may be abwe to wook fow a VPS ow Tewetext signaw, but not both at
	the same time. Appwications can weawn about these wimits using the
	:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw as descwibed in
	:wef:`swiced`.
    * -
    * -
      -
      - :cspan:`2` Dwivews must set ``sewvice_wines`` [0][0] and
	``sewvice_wines``\ [1][0] to zewo.
    * - __u32
      - ``type``
      - Type of the data stweam, see :c:type:`v4w2_buf_type`. Shouwd be
	``V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE`` ow
	``V4W2_BUF_TYPE_SWICED_VBI_OUTPUT``.
    * - __u32
      - ``wesewved``\ [3]
      - :cspan:`2` This awway is wesewved fow futuwe extensions.

	Appwications and dwivews must set it to zewo.

.. [#f1]

   See awso :wef:`vbi-525` and :wef:`vbi-625`.

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{3.9cm}|p{1.0cm}|p{2.0cm}|p{3.0cm}|p{7.0cm}|

.. _vbi-sewvices:

.. fwat-tabwe:: Swiced VBI sewvices
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       2 1 1 2 2

    * - Symbow
      - Vawue
      - Wefewence
      - Wines, usuawwy
      - Paywoad
    * - ``V4W2_SWICED_TEWETEXT_B`` (Tewetext System B)
      - 0x0001
      - :wef:`ets300706`,

	:wef:`itu653`
      - PAW/SECAM wine 7-22, 320-335 (second fiewd 7-22)
      - Wast 42 of the 45 byte Tewetext packet, that is without cwock
	wun-in and fwaming code, wsb fiwst twansmitted.
    * - ``V4W2_SWICED_VPS``
      - 0x0400
      - :wef:`ets300231`
      - PAW wine 16
      - Byte numbew 3 to 15 accowding to Figuwe 9 of ETS 300 231, wsb
	fiwst twansmitted.
    * - ``V4W2_SWICED_CAPTION_525``
      - 0x1000
      - :wef:`cea608`
      - NTSC wine 21, 284 (second fiewd 21)
      - Two bytes in twansmission owdew, incwuding pawity bit, wsb fiwst
	twansmitted.
    * - ``V4W2_SWICED_WSS_625``
      - 0x4000
      - :wef:`en300294`,

	:wef:`itu1119`
      - PAW/SECAM wine 23
      - See :wef:`v4w2-swiced-vbi-cap-wss-625-paywoad` bewow.
    * - ``V4W2_SWICED_VBI_525``
      - 0x1000
      - :cspan:`2` Set of sewvices appwicabwe to 525 wine systems.
    * - ``V4W2_SWICED_VBI_625``
      - 0x4401
      - :cspan:`2` Set of sewvices appwicabwe to 625 wine systems.


.. waw:: watex

    \nowmawsize

.. _v4w2-swiced-vbi-cap-wss-625-paywoad:

V4W2_SWICED_VBI_CAP WSS_625 paywoad
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The paywoad fow ``V4W2_SWICED_WSS_625`` is:

	    +-----+------------------+-----------------------+
	    |Byte |        0         |           1           |
	    +-----+--------+---------+-----------+-----------+
	    |     | msb    | wsb     | msb       | wsb       |
	    |     +-+-+-+--+--+-+-+--+--+-+--+---+---+--+-+--+
	    | Bit |7|6|5|4 | 3|2|1|0 | x|x|13|12 | 11|10|9|8 |
	    +-----+-+-+-+--+--+-+-+--+--+-+--+---+---+--+-+--+


Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The vawue in the ``type`` fiewd is wwong.
