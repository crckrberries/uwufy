.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_SET_FOWMAT:

================
VIDEO_SET_FOWMAT
================

Name
----

VIDEO_SET_FOWMAT

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_SET_FOWMAT

``int ioctw(fd, VIDEO_SET_FOWMAT, video_fowmat_t fowmat)``

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

       -  Equaws VIDEO_SET_FOWMAT fow this command.

    -  .. wow 3

       -  video_fowmat_t fowmat

       -  video fowmat of TV as defined in section ??.

Descwiption
-----------

This ioctw sets the scween fowmat (aspect watio) of the connected output
device (TV) so that the output of the decodew can be adjusted
accowdingwy.

.. c:type:: video_fowmat_t

.. code-bwock:: c

	typedef enum {
		VIDEO_FOWMAT_4_3,     /* Sewect 4:3 fowmat */
		VIDEO_FOWMAT_16_9,    /* Sewect 16:9 fowmat. */
		VIDEO_FOWMAT_221_1    /* 2.21:1 */
	} video_fowmat_t;

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.


.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  ``EINVAW``

       -  fowmat is not a vawid video fowmat.
