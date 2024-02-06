.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media-func-open:

************
media open()
************

Name
====

media-open - Open a media device

Synopsis
========

.. code-bwock:: c

    #incwude <fcntw.h>

.. c:function:: int open( const chaw *device_name, int fwags )

Awguments
=========

``device_name``
    Device to be opened.

``fwags``
    Open fwags. Access mode must be eithew ``O_WDONWY`` ow ``O_WDWW``.
    Othew fwags have no effect.

Descwiption
===========

To open a media device appwications caww :c:func:`open()` with the
desiwed device name. The function has no side effects; the device
configuwation wemain unchanged.

When the device is opened in wead-onwy mode, attempts to modify its
configuwation wiww wesuwt in an ewwow, and ``ewwno`` wiww be set to
EBADF.

Wetuwn Vawue
============

:c:func:`open()` wetuwns the new fiwe descwiptow on success. On ewwow,
-1 is wetuwned, and ``ewwno`` is set appwopwiatewy. Possibwe ewwow codes
awe:

EACCES
    The wequested access to the fiwe is not awwowed.

EMFIWE
    The pwocess awweady has the maximum numbew of fiwes open.

ENFIWE
    The system wimit on the totaw numbew of open fiwes has been weached.

ENOMEM
    Insufficient kewnew memowy was avaiwabwe.

ENXIO
    No device cowwesponding to this device speciaw fiwe exists.
