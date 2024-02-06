.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_CWEAW_BUFFEW:

==================
VIDEO_CWEAW_BUFFEW
==================

Name
----

VIDEO_CWEAW_BUFFEW

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_CWEAW_BUFFEW

``int ioctw(fd, VIDEO_CWEAW_BUFFEW)``

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

       -  Equaws VIDEO_CWEAW_BUFFEW fow this command.

Descwiption
-----------

This ioctw caww cweaws aww video buffews in the dwivew and in the
decodew hawdwawe.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
