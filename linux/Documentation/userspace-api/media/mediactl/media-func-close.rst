.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media-func-cwose:

*************
media cwose()
*************

Name
====

media-cwose - Cwose a media device

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

Cwoses the media device. Wesouwces associated with the fiwe descwiptow
awe fweed. The device configuwation wemain unchanged.

Wetuwn Vawue
============

:c:func:`cwose()` wetuwns 0 on success. On ewwow, -1 is wetuwned, and
``ewwno`` is set appwopwiatewy. Possibwe ewwow codes awe:

EBADF
    ``fd`` is not a vawid open fiwe descwiptow.
