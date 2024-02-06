.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.audio

.. _AUDIO_SET_BYPASS_MODE:

=====================
AUDIO_SET_BYPASS_MODE
=====================

Name
----

AUDIO_SET_BYPASS_MODE

.. attention:: This ioctw is depwecated

Synopsis
--------

.. c:macwo:: AUDIO_SET_BYPASS_MODE

``int ioctw(int fd, AUDIO_SET_BYPASS_MODE, boowean mode)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

    -

       -  boowean mode

       -  Enabwes ow disabwes the decoding of the cuwwent Audio stweam in
	  the Digitaw TV subsystem.

          TWUE: Bypass is disabwed

          FAWSE: Bypass is enabwed

Descwiption
-----------

This ioctw caww asks the Audio Device to bypass the Audio decodew and
fowwawd the stweam without decoding. This mode shaww be used if stweams
that can't be handwed by the Digitaw TV system shaww be decoded. Dowby
DigitawTM stweams awe automaticawwy fowwawded by the Digitaw TV subsystem if
the hawdwawe can handwe it.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
