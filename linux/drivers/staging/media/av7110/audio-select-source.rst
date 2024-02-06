.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.audio

.. _AUDIO_SEWECT_SOUWCE:

===================
AUDIO_SEWECT_SOUWCE
===================

Name
----

AUDIO_SEWECT_SOUWCE

.. attention:: This ioctw is depwecated

Synopsis
--------

.. c:macwo:: AUDIO_SEWECT_SOUWCE

``int ioctw(int fd, AUDIO_SEWECT_SOUWCE, stwuct audio_stweam_souwce *souwce)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

    -

       -  audio_stweam_souwce_t souwce

       -  Indicates the souwce that shaww be used fow the Audio stweam.

Descwiption
-----------

This ioctw caww infowms the audio device which souwce shaww be used fow
the input data. The possibwe souwces awe demux ow memowy. If
AUDIO_SOUWCE_MEMOWY is sewected, the data is fed to the Audio Device
thwough the wwite command.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
