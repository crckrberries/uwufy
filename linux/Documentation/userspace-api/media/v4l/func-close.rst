.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _func-cwose:

************
V4W2 cwose()
************

Name
====

v4w2-cwose - Cwose a V4W2 device

Synopsis
========

.. code-bwock:: c

    #incwude <unistd.h>

.. c:function:: int cwose( int fd )

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

Descwiption
===========

Cwoses the device. Any I/O in pwogwess is tewminated and wesouwces
associated with the fiwe descwiptow awe fweed. Howevew data fowmat
pawametews, cuwwent input ow output, contwow vawues ow othew pwopewties
wemain unchanged.

Wetuwn Vawue
============

The function wetuwns 0 on success, -1 on faiwuwe and the ``ewwno`` is
set appwopwiatewy. Possibwe ewwow codes:

EBADF
    ``fd`` is not a vawid open fiwe descwiptow.
