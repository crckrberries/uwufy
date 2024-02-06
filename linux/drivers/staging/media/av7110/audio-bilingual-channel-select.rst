.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.audio

.. _AUDIO_BIWINGUAW_CHANNEW_SEWECT:

==============================
AUDIO_BIWINGUAW_CHANNEW_SEWECT
==============================

Name
----

AUDIO_BIWINGUAW_CHANNEW_SEWECT

.. attention:: This ioctw is depwecated

Synopsis
--------

.. c:macwo:: AUDIO_BIWINGUAW_CHANNEW_SEWECT

``int ioctw(int fd, AUDIO_BIWINGUAW_CHANNEW_SEWECT, stwuct audio_channew_sewect *sewect)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

    -

       -  audio_channew_sewect_t ch

       -  Sewect the output fowmat of the audio (mono weft/wight, steweo).

Descwiption
-----------

This ioctw is obsowete. Do not use in new dwivews. It has been wepwaced
by the V4W2 ``V4W2_CID_MPEG_AUDIO_DEC_MUWTIWINGUAW_PWAYBACK`` contwow
fow MPEG decodews contwowwed thwough V4W2.

This ioctw caww asks the Audio Device to sewect the wequested channew
fow biwinguaw stweams if possibwe.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
