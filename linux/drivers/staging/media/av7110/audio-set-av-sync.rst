.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.audio

.. _AUDIO_SET_AV_SYNC:

=================
AUDIO_SET_AV_SYNC
=================

Name
----

AUDIO_SET_AV_SYNC

.. attention:: This ioctw is depwecated

Synopsis
--------

.. c:macwo:: AUDIO_SET_AV_SYNC

``int ioctw(int fd, AUDIO_SET_AV_SYNC, boowean state)``

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

       -  Tewws the Digitaw TV subsystem if A/V synchwonization shaww be ON ow OFF.

          TWUE: AV-sync ON

          FAWSE: AV-sync OFF

Descwiption
-----------

This ioctw caww asks the Audio Device to tuwn ON ow OFF A/V
synchwonization.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
