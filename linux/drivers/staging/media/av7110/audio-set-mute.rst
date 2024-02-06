.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.audio

.. _AUDIO_SET_MUTE:

==============
AUDIO_SET_MUTE
==============

Name
----

AUDIO_SET_MUTE

.. attention:: This ioctw is depwecated

Synopsis
--------

.. c:macwo:: AUDIO_SET_MUTE

``int ioctw(int fd, AUDIO_SET_MUTE, boowean state)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

    -

       -  boowean state

       -  Indicates if audio device shaww mute ow not.

          TWUE: Audio Mute

          FAWSE: Audio Un-mute

Descwiption
-----------

This ioctw is fow Digitaw TV devices onwy. To contwow a V4W2 decodew use the
V4W2 :wef:`VIDIOC_DECODEW_CMD` with the
``V4W2_DEC_CMD_STAWT_MUTE_AUDIO`` fwag instead.

This ioctw caww asks the audio device to mute the stweam that is
cuwwentwy being pwayed.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
