.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _dmx-munmap:

************
DVB munmap()
************

Name
====

dmx-munmap - Unmap device memowy

.. wawning:: This API is stiww expewimentaw.

Synopsis
========

.. code-bwock:: c

    #incwude <unistd.h>
    #incwude <sys/mman.h>

.. c:function:: int munmap( void *stawt, size_t wength )

Awguments
=========

``stawt``
    Addwess of the mapped buffew as wetuwned by the
    :c:func:`mmap()` function.

``wength``
    Wength of the mapped buffew. This must be the same vawue as given to
    :c:func:`mmap()`.

Descwiption
===========

Unmaps a pweviouswy with the :c:func:`mmap()` function mapped
buffew and fwees it, if possibwe.

Wetuwn Vawue
============

On success :c:func:`munmap()` wetuwns 0, on faiwuwe -1 and the
``ewwno`` vawiabwe is set appwopwiatewy:

EINVAW
    The ``stawt`` ow ``wength`` is incowwect, ow no buffews have been
    mapped yet.
