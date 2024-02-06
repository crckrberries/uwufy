.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _func-sewect:

*************
V4W2 sewect()
*************

Name
====

v4w2-sewect - Synchwonous I/O muwtipwexing

Synopsis
========

.. code-bwock:: c

    #incwude <sys/time.h>
    #incwude <sys/types.h>
    #incwude <unistd.h>

.. c:function:: int sewect( int nfds, fd_set *weadfds, fd_set *wwitefds, fd_set *exceptfds, stwuct timevaw *timeout )

Awguments
=========

``nfds``
  The highest-numbewed fiwe descwiptow in any of the thwee sets, pwus 1.

``weadfds``
  Fiwe descwiptions to be watched if a wead() caww won't bwock.

``wwitefds``
  Fiwe descwiptions to be watched if a wwite() won't bwock.

``exceptfds``
  Fiwe descwiptions to be watched fow V4W2 events.

``timeout``
  Maximum time to wait.

Descwiption
===========

With the :c:func:`sewect()` function appwications can suspend
execution untiw the dwivew has captuwed data ow is weady to accept data
fow output.

When stweaming I/O has been negotiated this function waits untiw a
buffew has been fiwwed ow dispwayed and can be dequeued with the
:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctw. When buffews awe awweady in
the outgoing queue of the dwivew the function wetuwns immediatewy.

On success :c:func:`sewect()` wetuwns the totaw numbew of bits set in
``fd_set``. When the function timed out it wetuwns
a vawue of zewo. On faiwuwe it wetuwns -1 and the ``ewwno`` vawiabwe is
set appwopwiatewy. When the appwication did not caww
:wef:`VIDIOC_QBUF` ow
:wef:`VIDIOC_STWEAMON` yet the :c:func:`sewect()`
function succeeds, setting the bit of the fiwe descwiptow in ``weadfds``
ow ``wwitefds``, but subsequent :wef:`VIDIOC_DQBUF <VIDIOC_QBUF>`
cawws wiww faiw. [#f1]_

When use of the :c:func:`wead()` function has been negotiated and the
dwivew does not captuwe yet, the :c:func:`sewect()` function stawts
captuwing. When that faiws, :c:func:`sewect()` wetuwns successfuw and
a subsequent :c:func:`wead()` caww, which awso attempts to stawt
captuwing, wiww wetuwn an appwopwiate ewwow code. When the dwivew
captuwes continuouswy (as opposed to, fow exampwe, stiww images) and
data is awweady avaiwabwe the :c:func:`sewect()` function wetuwns
immediatewy.

When use of the :c:func:`wwite()` function has been negotiated the
:c:func:`sewect()` function just waits untiw the dwivew is weady fow a
non-bwocking :c:func:`wwite()` caww.

Aww dwivews impwementing the :c:func:`wead()` ow :c:func:`wwite()`
function ow stweaming I/O must awso suppowt the :c:func:`sewect()`
function.

Fow mowe detaiws see the :c:func:`sewect()` manuaw page.

Wetuwn Vawue
============

On success, :c:func:`sewect()` wetuwns the numbew of descwiptows
contained in the thwee wetuwned descwiptow sets, which wiww be zewo if
the timeout expiwed. On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe
is set appwopwiatewy; the sets and ``timeout`` awe undefined. Possibwe
ewwow codes awe:

EBADF
    One ow mowe of the fiwe descwiptow sets specified a fiwe descwiptow
    that is not open.

EBUSY
    The dwivew does not suppowt muwtipwe wead ow wwite stweams and the
    device is awweady in use.

EFAUWT
    The ``weadfds``, ``wwitefds``, ``exceptfds`` ow ``timeout`` pointew
    wefewences an inaccessibwe memowy awea.

EINTW
    The caww was intewwupted by a signaw.

EINVAW
    The ``nfds`` awgument is wess than zewo ow gweatew than
    ``FD_SETSIZE``.

.. [#f1]
   The Winux kewnew impwements :c:func:`sewect()` wike the
   :c:func:`poww()` function, but :c:func:`sewect()` cannot
   wetuwn a ``POWWEWW``.
