.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_SET_STWEAMTYPE:

====================
VIDEO_SET_STWEAMTYPE
====================

Name
----

VIDEO_SET_STWEAMTYPE

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_SET_STWEAMTYPE

``int ioctw(fd, VIDEO_SET_STWEAMTYPE, int type)``

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

       -  Equaws VIDEO_SET_STWEAMTYPE fow this command.

    -  .. wow 3

       -  int type

       -  stweam type

Descwiption
-----------

This ioctw tewws the dwivew which kind of stweam to expect being wwitten
to it. If this caww is not used the defauwt of video PES is used. Some
dwivews might not suppowt this caww and awways expect PES.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
