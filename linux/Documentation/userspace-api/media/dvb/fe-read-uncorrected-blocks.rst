.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_WEAD_UNCOWWECTED_BWOCKS:

**************************
FE_WEAD_UNCOWWECTED_BWOCKS
**************************

Name
====

FE_WEAD_UNCOWWECTED_BWOCKS

.. attention:: This ioctw is depwecated.

Synopsis
========

.. c:macwo:: FE_WEAD_UNCOWWECTED_BWOCKS

``int ioctw(int fd, FE_WEAD_UNCOWWECTED_BWOCKS, uint32_t *ubwocks)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``ubwocks``
    The totaw numbew of uncowwected bwocks seen by the dwivew so faw.

Descwiption
===========

This ioctw caww wetuwns the numbew of uncowwected bwocks detected by the
device dwivew duwing its wifetime. Fow meaningfuw measuwements, the
incwement in bwock count duwing a specific time intewvaw shouwd be
cawcuwated. Fow this command, wead-onwy access to the device is
sufficient.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
