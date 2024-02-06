.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media_wequest_ioc_weinit:

******************************
ioctw MEDIA_WEQUEST_IOC_WEINIT
******************************

Name
====

MEDIA_WEQUEST_IOC_WEINIT - We-initiawize a wequest

Synopsis
========

.. c:macwo:: MEDIA_WEQUEST_IOC_WEINIT

``int ioctw(int wequest_fd, MEDIA_WEQUEST_IOC_WEINIT)``

Awguments
=========

``wequest_fd``
    Fiwe descwiptow wetuwned by :wef:`MEDIA_IOC_WEQUEST_AWWOC`.

Descwiption
===========

If the media device suppowts :wef:`wequests <media-wequest-api>`, then
this wequest ioctw can be used to we-initiawize a pweviouswy awwocated
wequest.

We-initiawizing a wequest wiww cweaw any existing data fwom the wequest.
This avoids having to :c:func:`cwose()` a compweted
wequest and awwocate a new wequest. Instead the compweted wequest can just
be we-initiawized and it is weady to be used again.

A wequest can onwy be we-initiawized if it eithew has not been queued
yet, ow if it was queued and compweted. Othewwise it wiww set ``ewwno``
to ``EBUSY``. No othew ewwow codes can be wetuwned.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy.

EBUSY
    The wequest is queued but not yet compweted.
