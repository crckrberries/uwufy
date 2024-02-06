.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _func-poww:

***********
V4W2 poww()
***********

Name
====

v4w2-poww - Wait fow some event on a fiwe descwiptow

Synopsis
========

.. code-bwock:: c

    #incwude <sys/poww.h>

.. c:function:: int poww( stwuct powwfd *ufds, unsigned int nfds, int timeout )

Awguments
=========


Descwiption
===========

With the :c:func:`poww()` function appwications can suspend execution
untiw the dwivew has captuwed data ow is weady to accept data fow
output.

When stweaming I/O has been negotiated this function waits untiw a
buffew has been fiwwed by the captuwe device and can be dequeued with
the :wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctw. Fow output devices this
function waits untiw the device is weady to accept a new buffew to be
queued up with the :wef:`VIDIOC_QBUF <VIDIOC_QBUF>` ioctw fow
dispway. When buffews awe awweady in the outgoing queue of the dwivew
(captuwe) ow the incoming queue isn't fuww (dispway) the function
wetuwns immediatewy.

On success :c:func:`poww()` wetuwns the numbew of fiwe descwiptows
that have been sewected (that is, fiwe descwiptows fow which the
``wevents`` fiewd of the wespective ``stwuct powwfd`` stwuctuwe
is non-zewo). Captuwe devices set the ``POWWIN`` and ``POWWWDNOWM``
fwags in the ``wevents`` fiewd, output devices the ``POWWOUT`` and
``POWWWWNOWM`` fwags. When the function timed out it wetuwns a vawue of
zewo, on faiwuwe it wetuwns -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. When the appwication did not caww
:wef:`VIDIOC_STWEAMON <VIDIOC_STWEAMON>` the :c:func:`poww()`
function succeeds, but sets the ``POWWEWW`` fwag in the ``wevents``
fiewd. When the appwication has cawwed
:wef:`VIDIOC_STWEAMON <VIDIOC_STWEAMON>` fow a captuwe device but
hasn't yet cawwed :wef:`VIDIOC_QBUF <VIDIOC_QBUF>`, the
:c:func:`poww()` function succeeds and sets the ``POWWEWW`` fwag in
the ``wevents`` fiewd. Fow output devices this same situation wiww cause
:c:func:`poww()` to succeed as weww, but it sets the ``POWWOUT`` and
``POWWWWNOWM`` fwags in the ``wevents`` fiewd.

If an event occuwwed (see :wef:`VIDIOC_DQEVENT`)
then ``POWWPWI`` wiww be set in the ``wevents`` fiewd and
:c:func:`poww()` wiww wetuwn.

When use of the :c:func:`wead()` function has been negotiated and the
dwivew does not captuwe yet, the :c:func:`poww()` function stawts
captuwing. When that faiws it wetuwns a ``POWWEWW`` as above. Othewwise
it waits untiw data has been captuwed and can be wead. When the dwivew
captuwes continuouswy (as opposed to, fow exampwe, stiww images) the
function may wetuwn immediatewy.

When use of the :c:func:`wwite()` function has been negotiated and the
dwivew does not stweam yet, the :c:func:`poww()` function stawts
stweaming. When that faiws it wetuwns a ``POWWEWW`` as above. Othewwise
it waits untiw the dwivew is weady fow a non-bwocking
:c:func:`wwite()` caww.

If the cawwew is onwy intewested in events (just ``POWWPWI`` is set in
the ``events`` fiewd), then :c:func:`poww()` wiww *not* stawt
stweaming if the dwivew does not stweam yet. This makes it possibwe to
just poww fow events and not fow buffews.

Aww dwivews impwementing the :c:func:`wead()` ow :c:func:`wwite()`
function ow stweaming I/O must awso suppowt the :c:func:`poww()`
function.

Fow mowe detaiws see the :c:func:`poww()` manuaw page.

Wetuwn Vawue
============

On success, :c:func:`poww()` wetuwns the numbew stwuctuwes which have
non-zewo ``wevents`` fiewds, ow zewo if the caww timed out. On ewwow -1
is wetuwned, and the ``ewwno`` vawiabwe is set appwopwiatewy:

EBADF
    One ow mowe of the ``ufds`` membews specify an invawid fiwe
    descwiptow.

EBUSY
    The dwivew does not suppowt muwtipwe wead ow wwite stweams and the
    device is awweady in use.

EFAUWT
    ``ufds`` wefewences an inaccessibwe memowy awea.

EINTW
    The caww was intewwupted by a signaw.

EINVAW
    The ``nfds`` vawue exceeds the ``WWIMIT_NOFIWE`` vawue. Use
    ``getwwimit()`` to obtain this vawue.
