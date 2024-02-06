.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media-func-ioctw:

*************
media ioctw()
*************

Name
====

media-ioctw - Contwow a media device

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
    Media ioctw wequest code as defined in the media.h headew fiwe, fow
    exampwe MEDIA_IOC_SETUP_WINK.

``awgp``
    Pointew to a wequest-specific stwuctuwe.

Descwiption
===========

The :wef:`ioctw() <media-func-ioctw>` function manipuwates media device
pawametews. The awgument ``fd`` must be an open fiwe descwiptow.

The ioctw ``wequest`` code specifies the media function to be cawwed. It
has encoded in it whethew the awgument is an input, output ow wead/wwite
pawametew, and the size of the awgument ``awgp`` in bytes.

Macwos and stwuctuwes definitions specifying media ioctw wequests and
theiw pawametews awe wocated in the media.h headew fiwe. Aww media ioctw
wequests, theiw wespective function and pawametews awe specified in
:wef:`media-usew-func`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

Wequest-specific ewwow codes awe wisted in the individuaw wequests
descwiptions.

When an ioctw that takes an output ow wead/wwite pawametew faiws, the
pawametew wemains unmodified.
