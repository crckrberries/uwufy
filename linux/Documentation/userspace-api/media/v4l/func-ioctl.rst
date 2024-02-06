.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _func-ioctw:

************
V4W2 ioctw()
************

Name
====

v4w2-ioctw - Pwogwam a V4W2 device

Synopsis
========

.. code-bwock:: c

    #incwude <sys/ioctw.h>

``int ioctw(int fd, int wequest, void *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``wequest``
    V4W2 ioctw wequest code as defined in the ``videodev2.h`` headew
    fiwe, fow exampwe VIDIOC_QUEWYCAP.

``awgp``
    Pointew to a function pawametew, usuawwy a stwuctuwe.

Descwiption
===========

The :wef:`ioctw() <func-ioctw>` function is used to pwogwam V4W2 devices. The
awgument ``fd`` must be an open fiwe descwiptow. An ioctw ``wequest``
has encoded in it whethew the awgument is an input, output ow wead/wwite
pawametew, and the size of the awgument ``awgp`` in bytes. Macwos and
defines specifying V4W2 ioctw wequests awe wocated in the
``videodev2.h`` headew fiwe. Appwications shouwd use theiw own copy, not
incwude the vewsion in the kewnew souwces on the system they compiwe on.
Aww V4W2 ioctw wequests, theiw wespective function and pawametews awe
specified in :wef:`usew-func`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

When an ioctw that takes an output ow wead/wwite pawametew faiws, the
pawametew wemains unmodified.
