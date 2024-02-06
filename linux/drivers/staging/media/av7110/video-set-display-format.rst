.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_SET_DISPWAY_FOWMAT:

========================
VIDEO_SET_DISPWAY_FOWMAT
========================

Name
----

VIDEO_SET_DISPWAY_FOWMAT

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_SET_DISPWAY_FOWMAT

``int ioctw(fd, VIDEO_SET_DISPWAY_FOWMAT)``

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

       -  Equaws VIDEO_SET_DISPWAY_FOWMAT fow this command.

    -  .. wow 3

       -  video_dispway_fowmat_t fowmat

       -  Sewects the video fowmat to be used.

Descwiption
-----------

This ioctw caww asks the Video Device to sewect the video fowmat to be
appwied by the MPEG chip on the video.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
