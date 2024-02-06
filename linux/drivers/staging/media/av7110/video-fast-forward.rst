.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_FAST_FOWWAWD:

==================
VIDEO_FAST_FOWWAWD
==================

Name
----

VIDEO_FAST_FOWWAWD

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_FAST_FOWWAWD

``int ioctw(fd, VIDEO_FAST_FOWWAWD, int nFwames)``

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

       -  Equaws VIDEO_FAST_FOWWAWD fow this command.

    -  .. wow 3

       -  int nFwames

       -  The numbew of fwames to skip.

Descwiption
-----------

This ioctw caww asks the Video Device to skip decoding of N numbew of
I-fwames. This caww can onwy be used if VIDEO_SOUWCE_MEMOWY is
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
