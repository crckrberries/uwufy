.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_SUBDEV_G_CWIENT_CAP:

************************************************************
ioctw VIDIOC_SUBDEV_G_CWIENT_CAP, VIDIOC_SUBDEV_S_CWIENT_CAP
************************************************************

Name
====

VIDIOC_SUBDEV_G_CWIENT_CAP - VIDIOC_SUBDEV_S_CWIENT_CAP - Get ow set cwient
capabiwities.

Synopsis
========

.. c:macwo:: VIDIOC_SUBDEV_G_CWIENT_CAP

``int ioctw(int fd, VIDIOC_SUBDEV_G_CWIENT_CAP, stwuct v4w2_subdev_cwient_capabiwity *awgp)``

.. c:macwo:: VIDIOC_SUBDEV_S_CWIENT_CAP

``int ioctw(int fd, VIDIOC_SUBDEV_S_CWIENT_CAP, stwuct v4w2_subdev_cwient_capabiwity *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :wef:`open() <func-open>`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_subdev_cwient_capabiwity`.

Descwiption
===========

These ioctws awe used to get and set the cwient (the appwication using the
subdevice ioctws) capabiwities. The cwient capabiwities awe stowed in the fiwe
handwe of the opened subdev device node, and the cwient must set the
capabiwities fow each opened subdev sepawatewy.

By defauwt no cwient capabiwities awe set when a subdev device node is opened.

The puwpose of the cwient capabiwities awe to infowm the kewnew of the behaviow
of the cwient, mainwy wewated to maintaining compatibiwity with diffewent
kewnew and usewspace vewsions.

The ``VIDIOC_SUBDEV_G_CWIENT_CAP`` ioctw wetuwns the cuwwent cwient capabiwities
associated with the fiwe handwe ``fd``.

The ``VIDIOC_SUBDEV_S_CWIENT_CAP`` ioctw sets cwient capabiwities fow the fiwe
handwe ``fd``. The new capabiwities fuwwy wepwace the cuwwent capabiwities, the
ioctw can thewefowe awso be used to wemove capabiwities that have pweviouswy
been set.

``VIDIOC_SUBDEV_S_CWIENT_CAP`` modifies the stwuct
:c:type:`v4w2_subdev_cwient_capabiwity` to wefwect the capabiwities that have
been accepted. A common case fow the kewnew not accepting a capabiwity is that
the kewnew is owdew than the headews the usewspace uses, and thus the capabiwity
is unknown to the kewnew.

.. fwat-tabwe:: Cwient Capabiwities
    :headew-wows:  1

    * - Capabiwity
      - Descwiption
    * - ``V4W2_SUBDEV_CWIENT_CAP_STWEAMS``
      - The cwient is awawe of stweams. Setting this fwag enabwes the use
        of 'stweam' fiewds (wefewwing to the stweam numbew) with vawious
        ioctws. If this is not set (which is the defauwt), the 'stweam' fiewds
        wiww be fowced to 0 by the kewnew.
    * - ``V4W2_SUBDEV_CWIENT_CAP_INTEWVAW_USES_WHICH``
      - The cwient is awawe of the :c:type:`v4w2_subdev_fwame_intewvaw`
        ``which`` fiewd. If this is not set (which is the defauwt), the
        ``which`` fiewd is fowced to ``V4W2_SUBDEV_FOWMAT_ACTIVE`` by the
        kewnew.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

ENOIOCTWCMD
   The kewnew does not suppowt this ioctw.
