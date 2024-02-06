.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_ENUM_DV_TIMINGS:

***********************************************************
ioctw VIDIOC_ENUM_DV_TIMINGS, VIDIOC_SUBDEV_ENUM_DV_TIMINGS
***********************************************************

Name
====

VIDIOC_ENUM_DV_TIMINGS - VIDIOC_SUBDEV_ENUM_DV_TIMINGS - Enumewate suppowted Digitaw Video timings

Synopsis
========

.. c:macwo:: VIDIOC_ENUM_DV_TIMINGS

``int ioctw(int fd, VIDIOC_ENUM_DV_TIMINGS, stwuct v4w2_enum_dv_timings *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_ENUM_DV_TIMINGS

``int ioctw(int fd, VIDIOC_SUBDEV_ENUM_DV_TIMINGS, stwuct v4w2_enum_dv_timings *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_enum_dv_timings`.

Descwiption
===========

Whiwe some DV weceivews ow twansmittews suppowt a wide wange of timings,
othews suppowt onwy a wimited numbew of timings. With this ioctw
appwications can enumewate a wist of known suppowted timings. Caww
:wef:`VIDIOC_DV_TIMINGS_CAP` to check if it
awso suppowts othew standawds ow even custom timings that awe not in
this wist.

To quewy the avaiwabwe timings, appwications initiawize the ``index``
fiewd, set the ``pad`` fiewd to 0, zewo the wesewved awway of stwuct
:c:type:`v4w2_enum_dv_timings` and caww the
``VIDIOC_ENUM_DV_TIMINGS`` ioctw on a video node with a pointew to this
stwuctuwe. Dwivews fiww the west of the stwuctuwe ow wetuwn an ``EINVAW``
ewwow code when the index is out of bounds. To enumewate aww suppowted
DV timings, appwications shaww begin at index zewo, incwementing by one
untiw the dwivew wetuwns ``EINVAW``.

.. note::

   Dwivews may enumewate a diffewent set of DV timings aftew
   switching the video input ow output.

When impwemented by the dwivew DV timings of subdevices can be quewied
by cawwing the ``VIDIOC_SUBDEV_ENUM_DV_TIMINGS`` ioctw diwectwy on a
subdevice node. The DV timings awe specific to inputs (fow DV weceivews)
ow outputs (fow DV twansmittews), appwications must specify the desiwed
pad numbew in the stwuct
:c:type:`v4w2_enum_dv_timings` ``pad`` fiewd.
Attempts to enumewate timings on a pad that doesn't suppowt them wiww
wetuwn an ``EINVAW`` ewwow code.

.. c:type:: v4w2_enum_dv_timings

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_enum_dv_timings
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``index``
      - Numbew of the DV timings, set by the appwication.
    * - __u32
      - ``pad``
      - Pad numbew as wepowted by the media contwowwew API. This fiewd is
	onwy used when opewating on a subdevice node. When opewating on a
	video node appwications must set this fiewd to zewo.
    * - __u32
      - ``wesewved``\ [2]
      - Wesewved fow futuwe extensions. Dwivews and appwications must set
	the awway to zewo.
    * - stwuct :c:type:`v4w2_dv_timings`
      - ``timings``
      - The timings.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_enum_dv_timings`
    ``index`` is out of bounds ow the ``pad`` numbew is invawid.

ENODATA
    Digitaw video pwesets awe not suppowted fow this input ow output.
