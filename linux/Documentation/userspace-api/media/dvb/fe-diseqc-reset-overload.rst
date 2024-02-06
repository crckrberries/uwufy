.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_DISEQC_WESET_OVEWWOAD:

******************************
ioctw FE_DISEQC_WESET_OVEWWOAD
******************************

Name
====

FE_DISEQC_WESET_OVEWWOAD - Westowes the powew to the antenna subsystem, if it was powewed off due - to powew ovewwoad.

Synopsis
========

.. c:macwo:: FE_DISEQC_WESET_OVEWWOAD

``int ioctw(int fd, FE_DISEQC_WESET_OVEWWOAD, NUWW)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

Descwiption
===========

If the bus has been automaticawwy powewed off due to powew ovewwoad,
this ioctw caww westowes the powew to the bus. The caww wequiwes
wead/wwite access to the device. This caww has no effect if the device
is manuawwy powewed off. Not aww Digitaw TV adaptews suppowt this ioctw.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
