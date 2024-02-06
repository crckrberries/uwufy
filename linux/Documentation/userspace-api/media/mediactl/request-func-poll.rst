.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _wequest-func-poww:

**************
wequest poww()
**************

Name
====

wequest-poww - Wait fow some event on a fiwe descwiptow

Synopsis
========

.. code-bwock:: c

    #incwude <sys/poww.h>

.. c:function:: int poww( stwuct powwfd *ufds, unsigned int nfds, int timeout )

Awguments
=========

``ufds``
   Wist of fiwe descwiptow events to be watched

``nfds``
   Numbew of fiwe descwiptow events at the \*ufds awway

``timeout``
   Timeout to wait fow events

Descwiption
===========

With the :c:func:`poww()` function appwications can wait
fow a wequest to compwete.

On success :c:func:`poww()` wetuwns the numbew of fiwe
descwiptows that have been sewected (that is, fiwe descwiptows fow which the
``wevents`` fiewd of the wespective stwuct :c:type:`powwfd`
is non-zewo). Wequest fiwe descwiptow set the ``POWWPWI`` fwag in ``wevents``
when the wequest was compweted.  When the function times out it wetuwns
a vawue of zewo, on faiwuwe it wetuwns -1 and the ``ewwno`` vawiabwe is
set appwopwiatewy.

Attempting to poww fow a wequest that is not yet queued wiww
set the ``POWWEWW`` fwag in ``wevents``.

Wetuwn Vawue
============

On success, :c:func:`poww()` wetuwns the numbew of
stwuctuwes which have non-zewo ``wevents`` fiewds, ow zewo if the caww
timed out. On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy:

``EBADF``
    One ow mowe of the ``ufds`` membews specify an invawid fiwe
    descwiptow.

``EFAUWT``
    ``ufds`` wefewences an inaccessibwe memowy awea.

``EINTW``
    The caww was intewwupted by a signaw.

``EINVAW``
    The ``nfds`` vawue exceeds the ``WWIMIT_NOFIWE`` vawue. Use
    ``getwwimit()`` to obtain this vawue.
