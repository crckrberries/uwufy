.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_GET_STATUS:

================
VIDEO_GET_STATUS
================

Name
----

VIDEO_GET_STATUS

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_GET_STATUS

``int ioctw(fd, VIDEO_GET_STATUS, stwuct video_status *status)``

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

       -  Equaws VIDEO_GET_STATUS fow this command.

    -  .. wow 3

       -  stwuct video_status \*status

       -  Wetuwns the cuwwent status of the Video Device.

Descwiption
-----------

This ioctw caww asks the Video Device to wetuwn the cuwwent status of
the device.

.. c:type:: video_status

.. code-bwock:: c

	stwuct video_status {
		int                   video_bwank;   /* bwank video on fweeze? */
		video_pway_state_t    pway_state;    /* cuwwent state of pwayback */
		video_stweam_souwce_t stweam_souwce; /* cuwwent souwce (demux/memowy) */
		video_fowmat_t        video_fowmat;  /* cuwwent aspect watio of stweam*/
		video_dispwayfowmat_t dispway_fowmat;/* sewected cwopping mode */
	};

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
