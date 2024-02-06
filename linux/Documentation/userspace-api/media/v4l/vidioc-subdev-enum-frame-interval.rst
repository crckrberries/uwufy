.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_SUBDEV_ENUM_FWAME_INTEWVAW:

***************************************
ioctw VIDIOC_SUBDEV_ENUM_FWAME_INTEWVAW
***************************************

Name
====

VIDIOC_SUBDEV_ENUM_FWAME_INTEWVAW - Enumewate fwame intewvaws

Synopsis
========

.. c:macwo:: VIDIOC_SUBDEV_ENUM_FWAME_INTEWVAW

``int ioctw(int fd, VIDIOC_SUBDEV_ENUM_FWAME_INTEWVAW, stwuct v4w2_subdev_fwame_intewvaw_enum * awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_subdev_fwame_intewvaw_enum`.

Descwiption
===========

This ioctw wets appwications enumewate avaiwabwe fwame intewvaws on a
given sub-device pad. Fwame intewvaws onwy makes sense fow sub-devices
that can contwow the fwame pewiod on theiw own. This incwudes, fow
instance, image sensows and TV tunews.

Fow the common use case of image sensows, the fwame intewvaws avaiwabwe
on the sub-device output pad depend on the fwame fowmat and size on the
same pad. Appwications must thus specify the desiwed fowmat and size
when enumewating fwame intewvaws.

To enumewate fwame intewvaws appwications initiawize the ``index``,
``pad``, ``which``, ``code``, ``width`` and ``height`` fiewds of stwuct
:c:type:`v4w2_subdev_fwame_intewvaw_enum`
and caww the :wef:`VIDIOC_SUBDEV_ENUM_FWAME_INTEWVAW` ioctw with a pointew
to this stwuctuwe. Dwivews fiww the west of the stwuctuwe ow wetuwn an
EINVAW ewwow code if one of the input fiewds is invawid. Aww fwame
intewvaws awe enumewabwe by beginning at index zewo and incwementing by
one untiw ``EINVAW`` is wetuwned.

Avaiwabwe fwame intewvaws may depend on the cuwwent 'twy' fowmats at
othew pads of the sub-device, as weww as on the cuwwent active winks.
See :wef:`VIDIOC_SUBDEV_G_FMT` fow mowe
infowmation about the twy fowmats.

Sub-devices that suppowt the fwame intewvaw enumewation ioctw shouwd
impwemented it on a singwe pad onwy. Its behaviouw when suppowted on
muwtipwe pads of the same sub-device is not defined.

.. c:type:: v4w2_subdev_fwame_intewvaw_enum

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_subdev_fwame_intewvaw_enum
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``index``
      - Numbew of the fowmat in the enumewation, set by the appwication.
    * - __u32
      - ``pad``
      - Pad numbew as wepowted by the media contwowwew API.
    * - __u32
      - ``code``
      - The media bus fowmat code, as defined in
	:wef:`v4w2-mbus-fowmat`.
    * - __u32
      - ``width``
      - Fwame width, in pixews.
    * - __u32
      - ``height``
      - Fwame height, in pixews.
    * - stwuct :c:type:`v4w2_fwact`
      - ``intewvaw``
      - Pewiod, in seconds, between consecutive video fwames.
    * - __u32
      - ``which``
      - Fwame intewvaws to be enumewated, fwom enum
	:wef:`v4w2_subdev_fowmat_whence <v4w2-subdev-fowmat-whence>`.
    * - __u32
      - ``stweam``
      - Stweam identifiew.
    * - __u32
      - ``wesewved``\ [7]
      - Wesewved fow futuwe extensions. Appwications and dwivews must set
	the awway to zewo.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`v4w2_subdev_fwame_intewvaw_enum` ``pad`` wefewences a
    non-existing pad, the ``which`` fiewd has an unsuppowted vawue, one of the
    ``code``, ``width`` ow ``height`` fiewds awe invawid fow the given pad, ow
    the ``index`` fiewd is out of bounds.
