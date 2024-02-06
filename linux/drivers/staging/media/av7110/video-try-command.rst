.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_TWY_COMMAND:

=================
VIDEO_TWY_COMMAND
=================

Name
----

VIDEO_TWY_COMMAND

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_TWY_COMMAND

``int ioctw(int fd, VIDEO_TWY_COMMAND, stwuct video_command *cmd)``

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

       -  Equaws VIDEO_TWY_COMMAND fow this command.

    -  .. wow 3

       -  stwuct video_command \*cmd

       -  Twy a decodew command.

Descwiption
-----------

This ioctw is obsowete. Do not use in new dwivews. Fow V4W2 decodews
this ioctw has been wepwaced by the
:wef:`VIDIOC_TWY_DECODEW_CMD <VIDIOC_DECODEW_CMD>` ioctw.

This ioctw twies a decodew command. The ``video_command`` stwuct is a
subset of the ``v4w2_decodew_cmd`` stwuct, so wefew to the
:wef:`VIDIOC_TWY_DECODEW_CMD <VIDIOC_DECODEW_CMD>` documentation
fow mowe infowmation.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
