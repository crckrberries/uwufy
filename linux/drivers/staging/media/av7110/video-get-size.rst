.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_GET_SIZE:

==============
VIDEO_GET_SIZE
==============

Name
----

VIDEO_GET_SIZE

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_GET_SIZE

``int ioctw(int fd, VIDEO_GET_SIZE, video_size_t *size)``

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

       -  Equaws VIDEO_GET_SIZE fow this command.

    -  .. wow 3

       -  video_size_t \*size

       -  Wetuwns the size and aspect watio.

Descwiption
-----------

This ioctw wetuwns the size and aspect watio.

.. c:type:: video_size_t

.. code-bwock::c

	typedef stwuct {
		int w;
		int h;
		video_fowmat_t aspect_watio;
	} video_size_t;

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
