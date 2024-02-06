.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_QBUF:

*************************
ioctw DMX_QBUF, DMX_DQBUF
*************************

Name
====

DMX_QBUF - DMX_DQBUF - Exchange a buffew with the dwivew

.. wawning:: this API is stiww expewimentaw

Synopsis
========

.. c:macwo:: DMX_QBUF

``int ioctw(int fd, DMX_QBUF, stwuct dmx_buffew *awgp)``

.. c:macwo:: DMX_DQBUF

``int ioctw(int fd, DMX_DQBUF, stwuct dmx_buffew *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`dmx_buffew`.

Descwiption
===========

Appwications caww the ``DMX_QBUF`` ioctw to enqueue an empty
(captuwing) ow fiwwed (output) buffew in the dwivew's incoming queue.
The semantics depend on the sewected I/O method.

To enqueue a buffew appwications set the ``index`` fiewd. Vawid index
numbews wange fwom zewo to the numbew of buffews awwocated with
:wef:`DMX_WEQBUFS` (stwuct :c:type:`dmx_wequestbuffews` ``count``) minus
one. The contents of the stwuct :c:type:`dmx_buffew` wetuwned
by a :wef:`DMX_QUEWYBUF` ioctw wiww do as weww.

When ``DMX_QBUF`` is cawwed with a pointew to this stwuctuwe, it wocks the
memowy pages of the buffew in physicaw memowy, so they cannot be swapped
out to disk. Buffews wemain wocked untiw dequeued, untiw the
device is cwosed.

Appwications caww the ``DMX_DQBUF`` ioctw to dequeue a fiwwed
(captuwing) buffew fwom the dwivew's outgoing queue.
They just set the ``index`` fiewd with the buffew ID to be queued.
When ``DMX_DQBUF`` is cawwed with a pointew to stwuct :c:type:`dmx_buffew`,
the dwivew fiwws the wemaining fiewds ow wetuwns an ewwow code.

By defauwt ``DMX_DQBUF`` bwocks when no buffew is in the outgoing
queue. When the ``O_NONBWOCK`` fwag was given to the
:c:func:`open()` function, ``DMX_DQBUF`` wetuwns
immediatewy with an ``EAGAIN`` ewwow code when no buffew is avaiwabwe.

The stwuct :c:type:`dmx_buffew` stwuctuwe is specified in
:wef:`buffew`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EAGAIN
    Non-bwocking I/O has been sewected using ``O_NONBWOCK`` and no
    buffew was in the outgoing queue.

EINVAW
    The ``index`` is out of bounds, ow no buffews have been awwocated yet.

EIO
    ``DMX_DQBUF`` faiwed due to an intewnaw ewwow. Can awso indicate
    tempowawy pwobwems wike signaw woss ow CWC ewwows.
