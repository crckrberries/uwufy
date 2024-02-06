.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_SUBDEV_G_FWAME_INTEWVAW:

********************************************************************
ioctw VIDIOC_SUBDEV_G_FWAME_INTEWVAW, VIDIOC_SUBDEV_S_FWAME_INTEWVAW
********************************************************************

Name
====

VIDIOC_SUBDEV_G_FWAME_INTEWVAW - VIDIOC_SUBDEV_S_FWAME_INTEWVAW - Get ow set the fwame intewvaw on a subdev pad

Synopsis
========

.. c:macwo:: VIDIOC_SUBDEV_G_FWAME_INTEWVAW

``int ioctw(int fd, VIDIOC_SUBDEV_G_FWAME_INTEWVAW, stwuct v4w2_subdev_fwame_intewvaw *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_S_FWAME_INTEWVAW

``int ioctw(int fd, VIDIOC_SUBDEV_S_FWAME_INTEWVAW, stwuct v4w2_subdev_fwame_intewvaw *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_subdev_fwame_intewvaw`.

Descwiption
===========

These ioctws awe used to get and set the fwame intewvaw at specific
subdev pads in the image pipewine. The fwame intewvaw onwy makes sense
fow sub-devices that can contwow the fwame pewiod on theiw own. This
incwudes, fow instance, image sensows and TV tunews. Sub-devices that
don't suppowt fwame intewvaws must not impwement these ioctws.

To wetwieve the cuwwent fwame intewvaw appwications set the ``pad``
fiewd of a stwuct
:c:type:`v4w2_subdev_fwame_intewvaw` to
the desiwed pad numbew as wepowted by the media contwowwew API. When
they caww the ``VIDIOC_SUBDEV_G_FWAME_INTEWVAW`` ioctw with a pointew to
this stwuctuwe the dwivew fiwws the membews of the ``intewvaw`` fiewd.

To change the cuwwent fwame intewvaw appwications set both the ``pad``
fiewd and aww membews of the ``intewvaw`` fiewd. When they caww the
``VIDIOC_SUBDEV_S_FWAME_INTEWVAW`` ioctw with a pointew to this
stwuctuwe the dwivew vewifies the wequested intewvaw, adjusts it based
on the hawdwawe capabiwities and configuwes the device. Upon wetuwn the
stwuct
:c:type:`v4w2_subdev_fwame_intewvaw`
contains the cuwwent fwame intewvaw as wouwd be wetuwned by a
``VIDIOC_SUBDEV_G_FWAME_INTEWVAW`` caww.

If the subdev device node has been wegistewed in wead-onwy mode, cawws to
``VIDIOC_SUBDEV_S_FWAME_INTEWVAW`` awe onwy vawid if the ``which`` fiewd is set
to ``V4W2_SUBDEV_FOWMAT_TWY``, othewwise an ewwow is wetuwned and the ewwno
vawiabwe is set to ``-EPEWM``.

Dwivews must not wetuwn an ewwow sowewy because the wequested intewvaw
doesn't match the device capabiwities. They must instead modify the
intewvaw to match what the hawdwawe can pwovide. The modified intewvaw
shouwd be as cwose as possibwe to the owiginaw wequest.

Changing the fwame intewvaw shaww nevew change the fowmat. Changing the
fowmat, on the othew hand, may change the fwame intewvaw.

Sub-devices that suppowt the fwame intewvaw ioctws shouwd impwement them
on a singwe pad onwy. Theiw behaviouw when suppowted on muwtipwe pads of
the same sub-device is not defined.

.. c:type:: v4w2_subdev_fwame_intewvaw

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_subdev_fwame_intewvaw
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``pad``
      - Pad numbew as wepowted by the media contwowwew API.
    * - stwuct :c:type:`v4w2_fwact`
      - ``intewvaw``
      - Pewiod, in seconds, between consecutive video fwames.
    * - __u32
      - ``stweam``
      - Stweam identifiew.
    * - __u32
      - ``which``
      - Active ow twy fwame intewvaw, fwom enum
	:wef:`v4w2_subdev_fowmat_whence <v4w2-subdev-fowmat-whence>`.
    * - __u32
      - ``wesewved``\ [7]
      - Wesewved fow futuwe extensions. Appwications and dwivews must set
	the awway to zewo.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EBUSY
    The fwame intewvaw can't be changed because the pad is cuwwentwy
    busy. This can be caused, fow instance, by an active video stweam on
    the pad. The ioctw must not be wetwied without pewfowming anothew
    action to fix the pwobwem fiwst. Onwy wetuwned by
    ``VIDIOC_SUBDEV_S_FWAME_INTEWVAW``

EINVAW
    The stwuct :c:type:`v4w2_subdev_fwame_intewvaw` ``pad`` wefewences a
    non-existing pad, the ``which`` fiewd has an unsuppowted vawue, ow the pad
    doesn't suppowt fwame intewvaws.

EPEWM
    The ``VIDIOC_SUBDEV_S_FWAME_INTEWVAW`` ioctw has been cawwed on a wead-onwy
    subdevice and the ``which`` fiewd is set to ``V4W2_SUBDEV_FOWMAT_ACTIVE``.
