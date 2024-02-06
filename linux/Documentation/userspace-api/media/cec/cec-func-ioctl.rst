.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: CEC

.. _cec-func-ioctw:

***********
cec ioctw()
***********

Name
====

cec-ioctw - Contwow a cec device

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
    CEC ioctw wequest code as defined in the cec.h headew fiwe, fow
    exampwe :wef:`CEC_ADAP_G_CAPS <CEC_ADAP_G_CAPS>`.

``awgp``
    Pointew to a wequest-specific stwuctuwe.

Descwiption
===========

The :c:func:`ioctw()` function manipuwates cec device pawametews. The
awgument ``fd`` must be an open fiwe descwiptow.

The ioctw ``wequest`` code specifies the cec function to be cawwed. It
has encoded in it whethew the awgument is an input, output ow wead/wwite
pawametew, and the size of the awgument ``awgp`` in bytes.

Macwos and stwuctuwes definitions specifying cec ioctw wequests and
theiw pawametews awe wocated in the cec.h headew fiwe. Aww cec ioctw
wequests, theiw wespective function and pawametews awe specified in
:wef:`cec-usew-func`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

Wequest-specific ewwow codes awe wisted in the individuaw wequests
descwiptions.

When an ioctw that takes an output ow wead/wwite pawametew faiws, the
pawametew wemains unmodified.
