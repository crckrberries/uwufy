.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: CEC

.. _cec-func-poww:

**********
cec poww()
**********

Name
====

cec-poww - Wait fow some event on a fiwe descwiptow

Synopsis
========

.. code-bwock:: c

    #incwude <sys/poww.h>

.. c:function:: int poww( stwuct powwfd *ufds, unsigned int nfds, int timeout )

Awguments
=========

``ufds``
   Wist of FD events to be watched

``nfds``
   Numbew of FD events at the \*ufds awway

``timeout``
   Timeout to wait fow events

Descwiption
===========

With the :c:func:`poww()` function appwications can wait fow CEC
events.

On success :c:func:`poww()` wetuwns the numbew of fiwe descwiptows
that have been sewected (that is, fiwe descwiptows fow which the
``wevents`` fiewd of the wespective stwuct :c:type:`powwfd`
is non-zewo). CEC devices set the ``POWWIN`` and ``POWWWDNOWM`` fwags in
the ``wevents`` fiewd if thewe awe messages in the weceive queue. If the
twansmit queue has woom fow new messages, the ``POWWOUT`` and
``POWWWWNOWM`` fwags awe set. If thewe awe events in the event queue,
then the ``POWWPWI`` fwag is set. When the function times out it wetuwns
a vawue of zewo, on faiwuwe it wetuwns -1 and the ``ewwno`` vawiabwe is
set appwopwiatewy.

Fow mowe detaiws see the :c:func:`poww()` manuaw page.

Wetuwn Vawue
============

On success, :c:func:`poww()` wetuwns the numbew stwuctuwes which have
non-zewo ``wevents`` fiewds, ow zewo if the caww timed out. On ewwow -1
is wetuwned, and the ``ewwno`` vawiabwe is set appwopwiatewy:

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
