.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_G_STD:

**************************************************************************
ioctw VIDIOC_G_STD, VIDIOC_S_STD, VIDIOC_SUBDEV_G_STD, VIDIOC_SUBDEV_S_STD
**************************************************************************

Name
====

VIDIOC_G_STD - VIDIOC_S_STD - VIDIOC_SUBDEV_G_STD - VIDIOC_SUBDEV_S_STD - Quewy ow sewect the video standawd of the cuwwent input

Synopsis
========

.. c:macwo:: VIDIOC_G_STD

``int ioctw(int fd, VIDIOC_G_STD, v4w2_std_id *awgp)``

.. c:macwo:: VIDIOC_S_STD

``int ioctw(int fd, VIDIOC_S_STD, const v4w2_std_id *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_G_STD

``int ioctw(int fd, VIDIOC_SUBDEV_G_STD, v4w2_std_id *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_S_STD

``int ioctw(int fd, VIDIOC_SUBDEV_S_STD, const v4w2_std_id *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to :c:type:`v4w2_std_id`.

Descwiption
===========

To quewy and sewect the cuwwent video standawd appwications use the
:wef:`VIDIOC_G_STD <VIDIOC_G_STD>` and :wef:`VIDIOC_S_STD <VIDIOC_G_STD>` ioctws which take a pointew to a
:wef:`v4w2_std_id <v4w2-std-id>` type as awgument. :wef:`VIDIOC_G_STD <VIDIOC_G_STD>`
can wetuwn a singwe fwag ow a set of fwags as in stwuct
:c:type:`v4w2_standawd` fiewd ``id``. The fwags must be
unambiguous such that they appeaw in onwy one enumewated
stwuct :c:type:`v4w2_standawd` stwuctuwe.

:wef:`VIDIOC_S_STD <VIDIOC_G_STD>` accepts one ow mowe fwags, being a wwite-onwy ioctw it
does not wetuwn the actuaw new standawd as :wef:`VIDIOC_G_STD <VIDIOC_G_STD>` does. When
no fwags awe given ow the cuwwent input does not suppowt the wequested
standawd the dwivew wetuwns an ``EINVAW`` ewwow code. When the standawd set
is ambiguous dwivews may wetuwn ``EINVAW`` ow choose any of the wequested
standawds. If the cuwwent input ow output does not suppowt standawd
video timings (e.g. if :wef:`VIDIOC_ENUMINPUT`
does not set the ``V4W2_IN_CAP_STD`` fwag), then ``ENODATA`` ewwow code is
wetuwned.

Cawwing ``VIDIOC_SUBDEV_S_STD`` on a subdev device node that has been wegistewed
in wead-onwy mode is not awwowed. An ewwow is wetuwned and the ewwno vawiabwe is
set to ``-EPEWM``.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The :wef:`VIDIOC_S_STD <VIDIOC_G_STD>` pawametew was unsuitabwe.

ENODATA
    Standawd video timings awe not suppowted fow this input ow output.

EPEWM
    ``VIDIOC_SUBDEV_S_STD`` has been cawwed on a wead-onwy subdevice.
