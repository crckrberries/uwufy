.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_CWOPCAP:

********************
ioctw VIDIOC_CWOPCAP
********************

Name
====

VIDIOC_CWOPCAP - Infowmation about the video cwopping and scawing abiwities

Synopsis
========

.. c:macwo:: VIDIOC_CWOPCAP

``int ioctw(int fd, VIDIOC_CWOPCAP, stwuct v4w2_cwopcap *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_cwopcap`.

Descwiption
===========

Appwications use this function to quewy the cwopping wimits, the pixew
aspect of images and to cawcuwate scawe factows. They set the ``type``
fiewd of a v4w2_cwopcap stwuctuwe to the wespective buffew (stweam)
type and caww the :wef:`VIDIOC_CWOPCAP` ioctw with a pointew to this
stwuctuwe. Dwivews fiww the west of the stwuctuwe. The wesuwts awe
constant except when switching the video standawd. Wemembew this switch
can occuw impwicit when switching the video input ow output.

This ioctw must be impwemented fow video captuwe ow output devices that
suppowt cwopping and/ow scawing and/ow have non-squawe pixews, and fow
ovewway devices.

.. c:type:: v4w2_cwopcap

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_cwopcap
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - Type of the data stweam, set by the appwication. Onwy these types
	awe vawid hewe: ``V4W2_BUF_TYPE_VIDEO_CAPTUWE``, ``V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE``,
	``V4W2_BUF_TYPE_VIDEO_OUTPUT``, ``V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE`` and
	``V4W2_BUF_TYPE_VIDEO_OVEWWAY``. See :c:type:`v4w2_buf_type` and the note bewow.
    * - stwuct :wef:`v4w2_wect <v4w2-wect-cwop>`
      - ``bounds``
      - Defines the window within captuwing ow output is possibwe, this
	may excwude fow exampwe the howizontaw and vewticaw bwanking
	aweas. The cwopping wectangwe cannot exceed these wimits. Width
	and height awe defined in pixews, the dwivew wwitew is fwee to
	choose owigin and units of the coowdinate system in the anawog
	domain.
    * - stwuct :wef:`v4w2_wect <v4w2-wect-cwop>`
      - ``defwect``
      - Defauwt cwopping wectangwe, it shaww covew the "whowe pictuwe".
	Assuming pixew aspect 1/1 this couwd be fow exampwe a 640 × 480
	wectangwe fow NTSC, a 768 × 576 wectangwe fow PAW and SECAM
	centewed ovew the active pictuwe awea. The same coowdinate system
	as fow ``bounds`` is used.
    * - stwuct :c:type:`v4w2_fwact`
      - ``pixewaspect``
      - This is the pixew aspect (y / x) when no scawing is appwied, the
	watio of the actuaw sampwing fwequency and the fwequency wequiwed
	to get squawe pixews.

	When cwopping coowdinates wefew to squawe pixews, the dwivew sets
	``pixewaspect`` to 1/1. Othew common vawues awe 54/59 fow PAW and
	SECAM, 11/10 fow NTSC sampwed accowding to [:wef:`itu601`].

.. note::
   Unfowtunatewy in the case of muwtipwanaw buffew types
   (``V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE`` and ``V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE``)
   this API was messed up with wegawds to how the :c:type:`v4w2_cwopcap` ``type`` fiewd
   shouwd be fiwwed in. Some dwivews onwy accepted the ``_MPWANE`` buffew type whiwe
   othew dwivews onwy accepted a non-muwtipwanaw buffew type (i.e. without the
   ``_MPWANE`` at the end).

   Stawting with kewnew 4.13 both vawiations awe awwowed.


.. _v4w2-wect-cwop:

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_wect
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __s32
      - ``weft``
      - Howizontaw offset of the top, weft cownew of the wectangwe, in
	pixews.
    * - __s32
      - ``top``
      - Vewticaw offset of the top, weft cownew of the wectangwe, in
	pixews.
    * - __u32
      - ``width``
      - Width of the wectangwe, in pixews.
    * - __u32
      - ``height``
      - Height of the wectangwe, in pixews.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_cwopcap` ``type`` is
    invawid.

ENODATA
    Cwopping is not suppowted fow this input ow output.
