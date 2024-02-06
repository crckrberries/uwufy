.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_WEAD_BEW:

***********
FE_WEAD_BEW
***********

Name
====

FE_WEAD_BEW

.. attention:: This ioctw is depwecated.

Synopsis
========

.. c:macwo:: FE_WEAD_BEW

``int ioctw(int fd, FE_WEAD_BEW, uint32_t *bew)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``bew``
    The bit ewwow wate is stowed into \*bew.

Descwiption
===========

This ioctw caww wetuwns the bit ewwow wate fow the signaw cuwwentwy
weceived/demoduwated by the fwont-end. Fow this command, wead-onwy
access to the device is sufficient.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
