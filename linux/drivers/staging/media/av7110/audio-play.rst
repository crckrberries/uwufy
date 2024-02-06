.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.audio

.. _AUDIO_PWAY:

==========
AUDIO_PWAY
==========

Name
----

AUDIO_PWAY

.. attention:: This ioctw is depwecated

Synopsis
--------

.. c:macwo:: AUDIO_PWAY

``int ioctw(int fd, AUDIO_PWAY)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

Descwiption
-----------

This ioctw caww asks the Audio Device to stawt pwaying an audio stweam
fwom the sewected souwce.

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
