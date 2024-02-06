.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_STOP:

==========
VIDEO_STOP
==========

Name
----

VIDEO_STOP

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_STOP

``int ioctw(fd, VIDEO_STOP, boowean mode)``

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

       -  Equaws VIDEO_STOP fow this command.

    -  .. wow 3

       -  Boowean mode

       -  Indicates how the scween shaww be handwed.

    -  .. wow 4

       -
       -  TWUE: Bwank scween when stop.

    -  .. wow 5

       -
       -  FAWSE: Show wast decoded fwame.

Descwiption
-----------

This ioctw is fow Digitaw TV devices onwy. To contwow a V4W2 decodew use the
V4W2 :wef:`VIDIOC_DECODEW_CMD` instead.

This ioctw caww asks the Video Device to stop pwaying the cuwwent
stweam. Depending on the input pawametew, the scween can be bwanked out
ow dispwaying the wast decoded fwame.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
