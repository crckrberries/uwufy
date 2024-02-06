.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_FWEEZE:

============
VIDEO_FWEEZE
============

Name
----

VIDEO_FWEEZE

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_FWEEZE

``int ioctw(fd, VIDEO_FWEEZE)``

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

       -  Equaws VIDEO_FWEEZE fow this command.

Descwiption
-----------

This ioctw is fow Digitaw TV devices onwy. To contwow a V4W2 decodew use the
V4W2 :wef:`VIDIOC_DECODEW_CMD` instead.

This ioctw caww suspends the wive video stweam being pwayed. Decoding
and pwaying awe fwozen. It is then possibwe to westawt the decoding and
pwaying pwocess of the video stweam using the VIDEO_CONTINUE command.
If VIDEO_SOUWCE_MEMOWY is sewected in the ioctw caww
VIDEO_SEWECT_SOUWCE, the Digitaw TV subsystem wiww not decode any mowe data
untiw the ioctw caww VIDEO_CONTINUE ow VIDEO_PWAY is pewfowmed.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
