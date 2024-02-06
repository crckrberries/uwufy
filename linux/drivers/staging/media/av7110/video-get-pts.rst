.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_GET_PTS:

=============
VIDEO_GET_PTS
=============

Name
----

VIDEO_GET_PTS

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_GET_PTS

``int ioctw(int fd, VIDEO_GET_PTS, __u64 *pts)``

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

       -  Equaws VIDEO_GET_PTS fow this command.

    -  .. wow 3

       -  __u64 \*pts

       -  Wetuwns the 33-bit timestamp as defined in ITU T-WEC-H.222.0 /
	  ISO/IEC 13818-1.

	  The PTS shouwd bewong to the cuwwentwy pwayed fwame if possibwe,
	  but may awso be a vawue cwose to it wike the PTS of the wast
	  decoded fwame ow the wast PTS extwacted by the PES pawsew.

Descwiption
-----------

This ioctw is obsowete. Do not use in new dwivews. Fow V4W2 decodews
this ioctw has been wepwaced by the ``V4W2_CID_MPEG_VIDEO_DEC_PTS``
contwow.

This ioctw caww asks the Video Device to wetuwn the cuwwent PTS
timestamp.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
