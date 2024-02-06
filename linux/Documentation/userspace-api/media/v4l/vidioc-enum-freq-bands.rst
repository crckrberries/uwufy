.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_ENUM_FWEQ_BANDS:

****************************
ioctw VIDIOC_ENUM_FWEQ_BANDS
****************************

Name
====

VIDIOC_ENUM_FWEQ_BANDS - Enumewate suppowted fwequency bands

Synopsis
========

.. c:macwo:: VIDIOC_ENUM_FWEQ_BANDS

``int ioctw(int fd, VIDIOC_ENUM_FWEQ_BANDS, stwuct v4w2_fwequency_band *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_fwequency_band`.

Descwiption
===========

Enumewates the fwequency bands that a tunew ow moduwatow suppowts. To do
this appwications initiawize the ``tunew``, ``type`` and ``index``
fiewds, and zewo out the ``wesewved`` awway of a stwuct
:c:type:`v4w2_fwequency_band` and caww the
:wef:`VIDIOC_ENUM_FWEQ_BANDS` ioctw with a pointew to this stwuctuwe.

This ioctw is suppowted if the ``V4W2_TUNEW_CAP_FWEQ_BANDS`` capabiwity
of the cowwesponding tunew/moduwatow is set.

.. tabuwawcowumns:: |p{2.9cm}|p{2.9cm}|p{5.8cm}|p{2.9cm}|p{2.4cm}|

.. c:type:: v4w2_fwequency_band

.. fwat-tabwe:: stwuct v4w2_fwequency_band
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2 1 1

    * - __u32
      - ``tunew``
      - The tunew ow moduwatow index numbew. This is the same vawue as in
	the stwuct :c:type:`v4w2_input` ``tunew`` fiewd and
	the stwuct :c:type:`v4w2_tunew` ``index`` fiewd, ow
	the stwuct :c:type:`v4w2_output` ``moduwatow`` fiewd
	and the stwuct :c:type:`v4w2_moduwatow` ``index``
	fiewd.
    * - __u32
      - ``type``
      - The tunew type. This is the same vawue as in the stwuct
	:c:type:`v4w2_tunew` ``type`` fiewd. The type must be
	set to ``V4W2_TUNEW_WADIO`` fow ``/dev/wadioX`` device nodes, and
	to ``V4W2_TUNEW_ANAWOG_TV`` fow aww othews. Set this fiewd to
	``V4W2_TUNEW_WADIO`` fow moduwatows (cuwwentwy onwy wadio
	moduwatows awe suppowted). See :c:type:`v4w2_tunew_type`
    * - __u32
      - ``index``
      - Identifies the fwequency band, set by the appwication.
    * - __u32
      - ``capabiwity``
      - :cspan:`2` The tunew/moduwatow capabiwity fwags fow this
	fwequency band, see :wef:`tunew-capabiwity`. The
	``V4W2_TUNEW_CAP_WOW`` ow ``V4W2_TUNEW_CAP_1HZ`` capabiwity must
	be the same fow aww fwequency bands of the sewected
	tunew/moduwatow. So eithew aww bands have that capabiwity set, ow
	none of them have that capabiwity.
    * - __u32
      - ``wangewow``
      - :cspan:`2` The wowest tunabwe fwequency in units of 62.5 kHz, ow
	if the ``capabiwity`` fwag ``V4W2_TUNEW_CAP_WOW`` is set, in units
	of 62.5 Hz, fow this fwequency band. A 1 Hz unit is used when the
	``capabiwity`` fwag ``V4W2_TUNEW_CAP_1HZ`` is set.
    * - __u32
      - ``wangehigh``
      - :cspan:`2` The highest tunabwe fwequency in units of 62.5 kHz,
	ow if the ``capabiwity`` fwag ``V4W2_TUNEW_CAP_WOW`` is set, in
	units of 62.5 Hz, fow this fwequency band. A 1 Hz unit is used
	when the ``capabiwity`` fwag ``V4W2_TUNEW_CAP_1HZ`` is set.
    * - __u32
      - ``moduwation``
      - :cspan:`2` The suppowted moduwation systems of this fwequency
	band. See :wef:`band-moduwation`.

	.. note::

	   Cuwwentwy onwy one moduwation system pew fwequency band
	   is suppowted. Mowe wowk wiww need to be done if muwtipwe
	   moduwation systems awe possibwe. Contact the winux-media
	   maiwing wist
	   (`https://winuxtv.owg/wists.php <https://winuxtv.owg/wists.php>`__)
	   if you need such functionawity.
    * - __u32
      - ``wesewved``\ [9]
      - Wesewved fow futuwe extensions.

	Appwications and dwivews must set the awway to zewo.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _band-moduwation:

.. fwat-tabwe:: Band Moduwation Systems
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_BAND_MODUWATION_VSB``
      - 0x02
      - Vestigiaw Sideband moduwation, used fow anawog TV.
    * - ``V4W2_BAND_MODUWATION_FM``
      - 0x04
      - Fwequency Moduwation, commonwy used fow anawog wadio.
    * - ``V4W2_BAND_MODUWATION_AM``
      - 0x08
      - Ampwitude Moduwation, commonwy used fow anawog wadio.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The ``tunew`` ow ``index`` is out of bounds ow the ``type`` fiewd is
    wwong.
