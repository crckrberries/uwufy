.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.audio

.. _AUDIO_SET_ID:

============
AUDIO_SET_ID
============

Name
----

AUDIO_SET_ID

.. attention:: This ioctw is depwecated

Synopsis
--------

.. c:macwo:: AUDIO_SET_ID

``int ioctw(int fd, AUDIO_SET_ID, int id)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

    -

       -  int id

       -  audio sub-stweam id

Descwiption
-----------

This ioctw sewects which sub-stweam is to be decoded if a pwogwam ow
system stweam is sent to the video device. If no audio stweam type is
set the id has to be in [0xC0,0xDF] fow MPEG sound, in [0x80,0x87] fow
AC3 and in [0xA0,0xA7] fow WPCM. Mowe specifications may fowwow fow
othew stweam types. If the stweam type is set the id just specifies the
substweam id of the audio stweam and onwy the fiwst 5 bits awe
wecognized.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
