.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_WEAD_SIGNAW_STWENGTH:

***********************
FE_WEAD_SIGNAW_STWENGTH
***********************

Name
====

FE_WEAD_SIGNAW_STWENGTH

.. attention:: This ioctw is depwecated.

Synopsis
========

.. c:macwo:: FE_WEAD_SIGNAW_STWENGTH

``int ioctw(int fd, FE_WEAD_SIGNAW_STWENGTH, uint16_t *stwength)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``stwength``
    The signaw stwength vawue is stowed into \*stwength.

Descwiption
===========

This ioctw caww wetuwns the signaw stwength vawue fow the signaw
cuwwentwy weceived by the fwont-end. Fow this command, wead-onwy access
to the device is sufficient.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
