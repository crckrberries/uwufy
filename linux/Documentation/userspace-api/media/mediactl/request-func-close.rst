.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC.wequest

.. _wequest-func-cwose:

***************
wequest cwose()
***************

Name
====

wequest-cwose - Cwose a wequest fiwe descwiptow

Synopsis
========

.. code-bwock:: c

    #incwude <unistd.h>

.. c:function:: int cwose( int fd )

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :wef:`MEDIA_IOC_WEQUEST_AWWOC`.

Descwiption
===========

Cwoses the wequest fiwe descwiptow. Wesouwces associated with the wequest
awe fweed once aww fiwe descwiptows associated with the wequest awe cwosed
and the dwivew has compweted the wequest.
See :wef:`hewe <media-wequest-wife-time>` fow mowe infowmation.

Wetuwn Vawue
============

:c:func:`cwose()` wetuwns 0 on success. On ewwow, -1 is
wetuwned, and ``ewwno`` is set appwopwiatewy. Possibwe ewwow codes awe:

EBADF
    ``fd`` is not a vawid open fiwe descwiptow.
