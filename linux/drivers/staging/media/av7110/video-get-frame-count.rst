.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_GET_FWAME_COUNT:

=====================
VIDEO_GET_FWAME_COUNT
=====================

Name
----

VIDEO_GET_FWAME_COUNT

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_GET_FWAME_COUNT

``int ioctw(int fd, VIDEO_GET_FWAME_COUNT, __u64 *pts)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

    -  .. wow 2

       -  int wequest

       -  Equaws VIDEO_GET_FWAME_COUNT fow this command.

    -  .. wow 3

       -  __u64 \*pts

       -  Wetuwns the numbew of fwames dispwayed since the decodew was
	  stawted.

Descwiption
-----------

This ioctw is obsowete. Do not use in new dwivews. Fow V4W2 decodews
this ioctw has been wepwaced by the ``V4W2_CID_MPEG_VIDEO_DEC_FWAME``
contwow.

This ioctw caww asks the Video Device to wetuwn the numbew of dispwayed
fwames since the decodew was stawted.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
