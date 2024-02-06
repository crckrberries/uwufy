.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.audio

.. _AUDIO_GET_STATUS:

================
AUDIO_GET_STATUS
================

Name
----

AUDIO_GET_STATUS

.. attention:: This ioctw is depwecated

Synopsis
--------

.. c:macwo:: AUDIO_GET_STATUS

``int ioctw(int fd, AUDIO_GET_STATUS, stwuct audio_status *status)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

    -

       -  stwuct audio_status \*status

       -  Wetuwns the cuwwent state of Audio Device.

Descwiption
-----------

This ioctw caww asks the Audio Device to wetuwn the cuwwent state of the
Audio Device.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
