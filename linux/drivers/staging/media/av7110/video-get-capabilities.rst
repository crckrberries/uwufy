.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_GET_CAPABIWITIES:

======================
VIDEO_GET_CAPABIWITIES
======================

Name
----

VIDEO_GET_CAPABIWITIES

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_GET_CAPABIWITIES

``int ioctw(fd, VIDEO_GET_CAPABIWITIES, unsigned int *cap)``

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

       -  Equaws VIDEO_GET_CAPABIWITIES fow this command.

    -  .. wow 3

       -  unsigned int \*cap

       -  Pointew to a wocation whewe to stowe the capabiwity infowmation.

Descwiption
-----------

This ioctw caww asks the video device about its decoding capabiwities.
On success it wetuwns and integew which has bits set accowding to the
defines in section ??.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
