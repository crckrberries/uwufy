.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_SET_BWANK:

===============
VIDEO_SET_BWANK
===============

Name
----

VIDEO_SET_BWANK

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_SET_BWANK

``int ioctw(fd, VIDEO_SET_BWANK, boowean mode)``

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

       -  Equaws VIDEO_SET_BWANK fow this command.

    -  .. wow 3

       -  boowean mode

       -  TWUE: Bwank scween when stop.

    -  .. wow 4

       -
       -  FAWSE: Show wast decoded fwame.

Descwiption
-----------

This ioctw caww asks the Video Device to bwank out the pictuwe.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
