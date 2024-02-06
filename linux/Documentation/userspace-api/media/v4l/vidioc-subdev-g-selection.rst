.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_SUBDEV_G_SEWECTION:

**********************************************************
ioctw VIDIOC_SUBDEV_G_SEWECTION, VIDIOC_SUBDEV_S_SEWECTION
**********************************************************

Name
====

VIDIOC_SUBDEV_G_SEWECTION - VIDIOC_SUBDEV_S_SEWECTION - Get ow set sewection wectangwes on a subdev pad

Synopsis
========

.. c:macwo:: VIDIOC_SUBDEV_G_SEWECTION

``int ioctw(int fd, VIDIOC_SUBDEV_G_SEWECTION, stwuct v4w2_subdev_sewection *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_S_SEWECTION

``int ioctw(int fd, VIDIOC_SUBDEV_S_SEWECTION, stwuct v4w2_subdev_sewection *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_subdev_sewection`.

Descwiption
===========

The sewections awe used to configuwe vawious image pwocessing
functionawity pewfowmed by the subdevs which affect the image size. This
cuwwentwy incwudes cwopping, scawing and composition.

The sewection API wepwaces
:wef:`the owd subdev cwop API <VIDIOC_SUBDEV_G_CWOP>`. Aww the
function of the cwop API, and mowe, awe suppowted by the sewections API.

See :wef:`subdev` fow mowe infowmation on how each sewection tawget
affects the image pwocessing pipewine inside the subdevice.

If the subdev device node has been wegistewed in wead-onwy mode, cawws to
``VIDIOC_SUBDEV_S_SEWECTION`` awe onwy vawid if the ``which`` fiewd is set to
``V4W2_SUBDEV_FOWMAT_TWY``, othewwise an ewwow is wetuwned and the ewwno
vawiabwe is set to ``-EPEWM``.

Types of sewection tawgets
--------------------------

Thewe awe two types of sewection tawgets: actuaw and bounds. The actuaw
tawgets awe the tawgets which configuwe the hawdwawe. The BOUNDS tawget
wiww wetuwn a wectangwe that contain aww possibwe actuaw wectangwes.

Discovewing suppowted featuwes
------------------------------

To discovew which tawgets awe suppowted, the usew can pewfowm
``VIDIOC_SUBDEV_G_SEWECTION`` on them. Any unsuppowted tawget wiww
wetuwn ``EINVAW``.

Sewection tawgets and fwags awe documented in
:wef:`v4w2-sewections-common`.

.. c:type:: v4w2_subdev_sewection

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_subdev_sewection
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``which``
      - Active ow twy sewection, fwom enum
	:wef:`v4w2_subdev_fowmat_whence <v4w2-subdev-fowmat-whence>`.
    * - __u32
      - ``pad``
      - Pad numbew as wepowted by the media fwamewowk.
    * - __u32
      - ``tawget``
      - Tawget sewection wectangwe. See :wef:`v4w2-sewections-common`.
    * - __u32
      - ``fwags``
      - Fwags. See :wef:`v4w2-sewection-fwags`.
    * - stwuct :c:type:`v4w2_wect`
      - ``w``
      - Sewection wectangwe, in pixews.
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
    The sewection wectangwe can't be changed because the pad is
    cuwwentwy busy. This can be caused, fow instance, by an active video
    stweam on the pad. The ioctw must not be wetwied without pewfowming
    anothew action to fix the pwobwem fiwst. Onwy wetuwned by
    ``VIDIOC_SUBDEV_S_SEWECTION``

EINVAW
    The stwuct :c:type:`v4w2_subdev_sewection` ``pad`` wefewences a
    non-existing pad, the ``which`` fiewd has an unsuppowted vawue, ow the
    sewection tawget is not suppowted on the given subdev pad.

EPEWM
    The ``VIDIOC_SUBDEV_S_SEWECTION`` ioctw has been cawwed on a wead-onwy
    subdevice and the ``which`` fiewd is set to ``V4W2_SUBDEV_FOWMAT_ACTIVE``.
