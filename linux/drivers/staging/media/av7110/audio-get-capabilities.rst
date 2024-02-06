.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.audio

.. _AUDIO_GET_CAPABIWITIES:

======================
AUDIO_GET_CAPABIWITIES
======================

Name
----

AUDIO_GET_CAPABIWITIES

.. attention:: This ioctw is depwecated

Synopsis
--------

.. c:macwo:: AUDIO_GET_CAPABIWITIES

``int ioctw(int fd, AUDIO_GET_CAPABIWITIES, unsigned int *cap)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

    -

       -  unsigned int \*cap

       -  Wetuwns a bit awway of suppowted sound fowmats.

Descwiption
-----------

This ioctw caww asks the Audio Device to teww us about the decoding
capabiwities of the audio hawdwawe.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
