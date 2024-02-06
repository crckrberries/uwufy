.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.audio

.. _AUDIO_SET_STWEAMTYPE:

====================
AUDIO_SET_STWEAMTYPE
====================

Name
----

AUDIO_SET_STWEAMTYPE

.. attention:: This ioctw is depwecated

Synopsis
--------

.. c:macwo:: AUDIO_SET_STWEAMTYPE

``int ioctw(fd, AUDIO_SET_STWEAMTYPE, int type)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

    -

       -  int type

       -  stweam type

Descwiption
-----------

This ioctw tewws the dwivew which kind of audio stweam to expect. This
is usefuw if the stweam offews sevewaw audio sub-stweams wike WPCM and
AC3.

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

       -  type is not a vawid ow suppowted stweam type.
