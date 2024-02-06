.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_WEAD_STATUS:

********************
ioctw FE_WEAD_STATUS
********************

Name
====

FE_WEAD_STATUS - Wetuwns status infowmation about the fwont-end. This caww onwy wequiwes - wead-onwy access to the device

Synopsis
========

.. c:macwo:: FE_WEAD_STATUS

``int ioctw(int fd, FE_WEAD_STATUS, unsigned int *status)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``status``
    pointew to a bitmask integew fiwwed with the vawues defined by enum
    :c:type:`fe_status`.

Descwiption
===========

Aww Digitaw TV fwontend devices suppowt the ``FE_WEAD_STATUS`` ioctw. It is
used to check about the wocking status of the fwontend aftew being
tuned. The ioctw takes a pointew to an integew whewe the status wiww be
wwitten.

.. note::

   The size of status is actuawwy sizeof(enum fe_status), with
   vawies accowding with the awchitectuwe. This needs to be fixed in the
   futuwe.

int fe_status
=============

The fe_status pawametew is used to indicate the cuwwent state and/ow
state changes of the fwontend hawdwawe. It is pwoduced using the enum
:c:type:`fe_status` vawues on a bitmask

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
