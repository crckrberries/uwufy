.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_STIWWPICTUWE:

==================
VIDEO_STIWWPICTUWE
==================

Name
----

VIDEO_STIWWPICTUWE

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_STIWWPICTUWE

``int ioctw(fd, VIDEO_STIWWPICTUWE, stwuct video_stiww_pictuwe *sp)``

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

       -  Equaws VIDEO_STIWWPICTUWE fow this command.

    -  .. wow 3

       -  stwuct video_stiww_pictuwe \*sp

       -  Pointew to a wocation whewe an I-fwame and size is stowed.

Descwiption
-----------

This ioctw caww asks the Video Device to dispway a stiww pictuwe
(I-fwame). The input data shaww contain an I-fwame. If the pointew is
NUWW, then the cuwwent dispwayed stiww pictuwe is bwanked.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
