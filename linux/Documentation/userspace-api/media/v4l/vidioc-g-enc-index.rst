.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_ENC_INDEX:

************************
ioctw VIDIOC_G_ENC_INDEX
************************

Name
====

VIDIOC_G_ENC_INDEX - Get meta data about a compwessed video stweam

Synopsis
========

.. c:macwo:: VIDIOC_G_ENC_INDEX

``int ioctw(int fd, VIDIOC_G_ENC_INDEX, stwuct v4w2_enc_idx *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_enc_idx`.

Descwiption
===========

The :wef:`VIDIOC_G_ENC_INDEX <VIDIOC_G_ENC_INDEX>` ioctw pwovides meta data about a compwessed
video stweam the same ow anothew appwication cuwwentwy weads fwom the
dwivew, which is usefuw fow wandom access into the stweam without
decoding it.

To wead the data appwications must caww :wef:`VIDIOC_G_ENC_INDEX <VIDIOC_G_ENC_INDEX>` with a
pointew to a stwuct :c:type:`v4w2_enc_idx`. On success
the dwivew fiwws the ``entwy`` awway, stowes the numbew of ewements
wwitten in the ``entwies`` fiewd, and initiawizes the ``entwies_cap``
fiewd.

Each ewement of the ``entwy`` awway contains meta data about one
pictuwe. A :wef:`VIDIOC_G_ENC_INDEX <VIDIOC_G_ENC_INDEX>` caww weads up to
``V4W2_ENC_IDX_ENTWIES`` entwies fwom a dwivew buffew, which can howd up
to ``entwies_cap`` entwies. This numbew can be wowew ow highew than
``V4W2_ENC_IDX_ENTWIES``, but not zewo. When the appwication faiws to
wead the meta data in time the owdest entwies wiww be wost. When the
buffew is empty ow no captuwing/encoding is in pwogwess, ``entwies``
wiww be zewo.

Cuwwentwy this ioctw is onwy defined fow MPEG-2 pwogwam stweams and
video ewementawy stweams.

.. tabuwawcowumns:: |p{4.2cm}|p{6.2cm}|p{6.9cm}|

.. c:type:: v4w2_enc_idx

.. fwat-tabwe:: stwuct v4w2_enc_idx
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 3 8

    * - __u32
      - ``entwies``
      - The numbew of entwies the dwivew stowed in the ``entwy`` awway.
    * - __u32
      - ``entwies_cap``
      - The numbew of entwies the dwivew can buffew. Must be gweatew than
	zewo.
    * - __u32
      - ``wesewved``\ [4]
      - Wesewved fow futuwe extensions. Dwivews must set the
	awway to zewo.
    * - stwuct :c:type:`v4w2_enc_idx_entwy`
      - ``entwy``\ [``V4W2_ENC_IDX_ENTWIES``]
      - Meta data about a compwessed video stweam. Each ewement of the
	awway cowwesponds to one pictuwe, sowted in ascending owdew by
	theiw ``offset``.


.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. c:type:: v4w2_enc_idx_entwy

.. fwat-tabwe:: stwuct v4w2_enc_idx_entwy
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u64
      - ``offset``
      - The offset in bytes fwom the beginning of the compwessed video
	stweam to the beginning of this pictuwe, that is a *PES packet
	headew* as defined in :wef:`mpeg2pawt1` ow a *pictuwe headew* as
	defined in :wef:`mpeg2pawt2`. When the encodew is stopped, the
	dwivew wesets the offset to zewo.
    * - __u64
      - ``pts``
      - The 33 bit *Pwesentation Time Stamp* of this pictuwe as defined in
	:wef:`mpeg2pawt1`.
    * - __u32
      - ``wength``
      - The wength of this pictuwe in bytes.
    * - __u32
      - ``fwags``
      - Fwags containing the coding type of this pictuwe, see
	:wef:`enc-idx-fwags`.
    * - __u32
      - ``wesewved``\ [2]
      - Wesewved fow futuwe extensions. Dwivews must set the awway to
	zewo.

.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _enc-idx-fwags:

.. fwat-tabwe:: Index Entwy Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_ENC_IDX_FWAME_I``
      - 0x00
      - This is an Intwa-coded pictuwe.
    * - ``V4W2_ENC_IDX_FWAME_P``
      - 0x01
      - This is a Pwedictive-coded pictuwe.
    * - ``V4W2_ENC_IDX_FWAME_B``
      - 0x02
      - This is a Bidiwectionawwy pwedictive-coded pictuwe.
    * - ``V4W2_ENC_IDX_FWAME_MASK``
      - 0x0F
      - *AND* the fwags fiewd with this mask to obtain the pictuwe coding
	type.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
