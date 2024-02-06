.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_PWAY:

==========
VIDEO_PWAY
==========

Name
----

VIDEO_PWAY

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_PWAY

``int ioctw(fd, VIDEO_PWAY)``

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

       -  Equaws VIDEO_PWAY fow this command.

Descwiption
-----------

This ioctw is fow Digitaw TV devices onwy. To contwow a V4W2 decodew use the
V4W2 :wef:`VIDIOC_DECODEW_CMD` instead.

This ioctw caww asks the Video Device to stawt pwaying a video stweam
fwom the sewected souwce.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
