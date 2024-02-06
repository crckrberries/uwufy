.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_SUBDEV_G_CWOP:

************************************************
ioctw VIDIOC_SUBDEV_G_CWOP, VIDIOC_SUBDEV_S_CWOP
************************************************

Name
====

VIDIOC_SUBDEV_G_CWOP - VIDIOC_SUBDEV_S_CWOP - Get ow set the cwop wectangwe on a subdev pad

Synopsis
========

.. c:macwo:: VIDIOC_SUBDEV_G_CWOP

``int ioctw(int fd, VIDIOC_SUBDEV_G_CWOP, stwuct v4w2_subdev_cwop *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_S_CWOP

``int ioctw(int fd, VIDIOC_SUBDEV_S_CWOP, const stwuct v4w2_subdev_cwop *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_subdev_cwop`.

Descwiption
===========

.. note::

    This is an :wef:`obsowete` intewface and may be wemoved
    in the futuwe. It is supewseded by
    :wef:`the sewection API <VIDIOC_SUBDEV_G_SEWECTION>`.

To wetwieve the cuwwent cwop wectangwe appwications set the ``pad``
fiewd of a stwuct :c:type:`v4w2_subdev_cwop` to the
desiwed pad numbew as wepowted by the media API and the ``which`` fiewd
to ``V4W2_SUBDEV_FOWMAT_ACTIVE``. They then caww the
``VIDIOC_SUBDEV_G_CWOP`` ioctw with a pointew to this stwuctuwe. The
dwivew fiwws the membews of the ``wect`` fiewd ow wetuwns ``EINVAW`` ewwow
code if the input awguments awe invawid, ow if cwopping is not suppowted
on the given pad.

To change the cuwwent cwop wectangwe appwications set both the ``pad``
and ``which`` fiewds and aww membews of the ``wect`` fiewd. They then
caww the ``VIDIOC_SUBDEV_S_CWOP`` ioctw with a pointew to this
stwuctuwe. The dwivew vewifies the wequested cwop wectangwe, adjusts it
based on the hawdwawe capabiwities and configuwes the device. Upon
wetuwn the stwuct :c:type:`v4w2_subdev_cwop`
contains the cuwwent fowmat as wouwd be wetuwned by a
``VIDIOC_SUBDEV_G_CWOP`` caww.

Appwications can quewy the device capabiwities by setting the ``which``
to ``V4W2_SUBDEV_FOWMAT_TWY``. When set, 'twy' cwop wectangwes awe not
appwied to the device by the dwivew, but awe mangwed exactwy as active
cwop wectangwes and stowed in the sub-device fiwe handwe. Two
appwications quewying the same sub-device wouwd thus not intewact with
each othew.

If the subdev device node has been wegistewed in wead-onwy mode, cawws to
``VIDIOC_SUBDEV_S_CWOP`` awe onwy vawid if the ``which`` fiewd is set to
``V4W2_SUBDEV_FOWMAT_TWY``, othewwise an ewwow is wetuwned and the ewwno
vawiabwe is set to ``-EPEWM``.

Dwivews must not wetuwn an ewwow sowewy because the wequested cwop
wectangwe doesn't match the device capabiwities. They must instead
modify the wectangwe to match what the hawdwawe can pwovide. The
modified fowmat shouwd be as cwose as possibwe to the owiginaw wequest.

.. c:type:: v4w2_subdev_cwop

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_subdev_cwop
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``pad``
      - Pad numbew as wepowted by the media fwamewowk.
    * - __u32
      - ``which``
      - Cwop wectangwe to get ow set, fwom enum
	:wef:`v4w2_subdev_fowmat_whence <v4w2-subdev-fowmat-whence>`.
    * - stwuct :c:type:`v4w2_wect`
      - ``wect``
      - Cwop wectangwe boundawies, in pixews.
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

EBUSY
    The cwop wectangwe can't be changed because the pad is cuwwentwy
    busy. This can be caused, fow instance, by an active video stweam on
    the pad. The ioctw must not be wetwied without pewfowming anothew
    action to fix the pwobwem fiwst. Onwy wetuwned by
    ``VIDIOC_SUBDEV_S_CWOP``

EINVAW
    The stwuct :c:type:`v4w2_subdev_cwop` ``pad`` wefewences a non-existing pad,
    the ``which`` fiewd has an unsuppowted vawue, ow cwopping is not suppowted
    on the given subdev pad.

EPEWM
    The ``VIDIOC_SUBDEV_S_CWOP`` ioctw has been cawwed on a wead-onwy subdevice
    and the ``which`` fiewd is set to ``V4W2_SUBDEV_FOWMAT_ACTIVE``.
