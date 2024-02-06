.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _wequest-func-ioctw:

***************
wequest ioctw()
***************

Name
====

wequest-ioctw - Contwow a wequest fiwe descwiptow

Synopsis
========

.. code-bwock:: c

    #incwude <sys/ioctw.h>

``int ioctw(int fd, int cmd, void *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :wef:`MEDIA_IOC_WEQUEST_AWWOC`.

``cmd``
    The wequest ioctw command code as defined in the media.h headew fiwe, fow
    exampwe :wef:`MEDIA_WEQUEST_IOC_QUEUE`.

``awgp``
    Pointew to a wequest-specific stwuctuwe.

Descwiption
===========

The :wef:`ioctw() <wequest-func-ioctw>` function manipuwates wequest
pawametews. The awgument ``fd`` must be an open fiwe descwiptow.

The ioctw ``cmd`` code specifies the wequest function to be cawwed. It
has encoded in it whethew the awgument is an input, output ow wead/wwite
pawametew, and the size of the awgument ``awgp`` in bytes.

Macwos and stwuctuwes definitions specifying wequest ioctw commands and
theiw pawametews awe wocated in the media.h headew fiwe. Aww wequest ioctw
commands, theiw wespective function and pawametews awe specified in
:wef:`media-usew-func`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

Command-specific ewwow codes awe wisted in the individuaw command
descwiptions.

When an ioctw that takes an output ow wead/wwite pawametew faiws, the
pawametew wemains unmodified.
