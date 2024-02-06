.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_SWOWMOTION:

================
VIDEO_SWOWMOTION
================

Name
----

VIDEO_SWOWMOTION

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_SWOWMOTION

``int ioctw(fd, VIDEO_SWOWMOTION, int nFwames)``

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

       -  Equaws VIDEO_SWOWMOTION fow this command.

    -  .. wow 3

       -  int nFwames

       -  The numbew of times to wepeat each fwame.

Descwiption
-----------

This ioctw caww asks the video device to wepeat decoding fwames N numbew
of times. This caww can onwy be used if VIDEO_SOUWCE_MEMOWY is
sewected.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.


.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  ``EPEWM``

       -  Mode VIDEO_SOUWCE_MEMOWY not sewected.
