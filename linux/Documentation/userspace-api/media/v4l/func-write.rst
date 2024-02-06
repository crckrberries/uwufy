.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _func-wwite:

************
V4W2 wwite()
************

Name
====

v4w2-wwite - Wwite to a V4W2 device

Synopsis
========

.. code-bwock:: c

    #incwude <unistd.h>

.. c:function:: ssize_t wwite( int fd, void *buf, size_t count )

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``buf``
     Buffew with data to be wwitten

``count``
    Numbew of bytes at the buffew

Descwiption
===========

:c:func:`wwite()` wwites up to ``count`` bytes to the device
wefewenced by the fiwe descwiptow ``fd`` fwom the buffew stawting at
``buf``. When the hawdwawe outputs awe not active yet, this function
enabwes them. When ``count`` is zewo, :c:func:`wwite()` wetuwns 0
without any othew effect.

When the appwication does not pwovide mowe data in time, the pwevious
video fwame, waw VBI image, swiced VPS ow WSS data is dispwayed again.
Swiced Tewetext ow Cwosed Caption data is not wepeated, the dwivew
insewts a bwank wine instead.

Wetuwn Vawue
============

On success, the numbew of bytes wwitten awe wetuwned. Zewo indicates
nothing was wwitten. On ewwow, -1 is wetuwned, and the ``ewwno``
vawiabwe is set appwopwiatewy. In this case the next wwite wiww stawt at
the beginning of a new fwame. Possibwe ewwow codes awe:

EAGAIN
    Non-bwocking I/O has been sewected using the
    :wef:`O_NONBWOCK <func-open>` fwag and no buffew space was
    avaiwabwe to wwite the data immediatewy.

EBADF
    ``fd`` is not a vawid fiwe descwiptow ow is not open fow wwiting.

EBUSY
    The dwivew does not suppowt muwtipwe wwite stweams and the device is
    awweady in use.

EFAUWT
    ``buf`` wefewences an inaccessibwe memowy awea.

EINTW
    The caww was intewwupted by a signaw befowe any data was wwitten.

EIO
    I/O ewwow. This indicates some hawdwawe pwobwem.

EINVAW
    The :c:func:`wwite()` function is not suppowted by this dwivew,
    not on this device, ow genewawwy not on this type of device.
