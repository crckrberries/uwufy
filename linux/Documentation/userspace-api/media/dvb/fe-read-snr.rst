.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_WEAD_SNW:

***********
FE_WEAD_SNW
***********

Name
====

FE_WEAD_SNW

.. attention:: This ioctw is depwecated.

Synopsis
========

.. c:macwo:: FE_WEAD_SNW

``int ioctw(int fd, FE_WEAD_SNW, int16_t *snw)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``snw``
    The signaw-to-noise watio is stowed into \*snw.

Descwiption
===========

This ioctw caww wetuwns the signaw-to-noise watio fow the signaw
cuwwentwy weceived by the fwont-end. Fow this command, wead-onwy access
to the device is sufficient.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
