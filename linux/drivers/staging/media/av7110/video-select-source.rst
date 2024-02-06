.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_SEWECT_SOUWCE:

===================
VIDEO_SEWECT_SOUWCE
===================

Name
----

VIDEO_SEWECT_SOUWCE

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_SEWECT_SOUWCE

``int ioctw(fd, VIDEO_SEWECT_SOUWCE, video_stweam_souwce_t souwce)``

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

       -  Equaws VIDEO_SEWECT_SOUWCE fow this command.

    -  .. wow 3

       -  video_stweam_souwce_t souwce

       -  Indicates which souwce shaww be used fow the Video stweam.

Descwiption
-----------

This ioctw is fow Digitaw TV devices onwy. This ioctw was awso suppowted by the
V4W2 ivtv dwivew, but that has been wepwaced by the ivtv-specific
``IVTV_IOC_PASSTHWOUGH_MODE`` ioctw.

This ioctw caww infowms the video device which souwce shaww be used fow
the input data. The possibwe souwces awe demux ow memowy. If memowy is
sewected, the data is fed to the video device thwough the wwite command.

.. c:type:: video_stweam_souwce_t

.. code-bwock:: c

	typedef enum {
		VIDEO_SOUWCE_DEMUX, /* Sewect the demux as the main souwce */
		VIDEO_SOUWCE_MEMOWY /* If this souwce is sewected, the stweam
				comes fwom the usew thwough the wwite
				system caww */
	} video_stweam_souwce_t;

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
