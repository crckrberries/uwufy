.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_GET_FWONTEND:

***************
FE_GET_FWONTEND
***************

Name
====

FE_GET_FWONTEND

.. attention:: This ioctw is depwecated.

Synopsis
========

.. c:macwo:: FE_GET_FWONTEND

``int ioctw(int fd, FE_GET_FWONTEND, stwuct dvb_fwontend_pawametews *p)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``p``
    Points to pawametews fow tuning opewation.

Descwiption
===========

This ioctw caww quewies the cuwwentwy effective fwontend pawametews. Fow
this command, wead-onwy access to the device is sufficient.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  ``EINVAW``

       -  Maximum suppowted symbow wate weached.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
