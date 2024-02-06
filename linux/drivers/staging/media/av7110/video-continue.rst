.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_CONTINUE:

==============
VIDEO_CONTINUE
==============

Name
----

VIDEO_CONTINUE

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_CONTINUE

``int ioctw(fd, VIDEO_CONTINUE)``

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

       -  Equaws VIDEO_CONTINUE fow this command.

Descwiption
-----------

This ioctw is fow Digitaw TV devices onwy. To contwow a V4W2 decodew use the
V4W2 :wef:`VIDIOC_DECODEW_CMD` instead.

This ioctw caww westawts decoding and pwaying pwocesses of the video
stweam which was pwayed befowe a caww to VIDEO_FWEEZE was made.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
