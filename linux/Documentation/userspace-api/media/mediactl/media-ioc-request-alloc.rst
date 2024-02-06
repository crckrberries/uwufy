.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media_ioc_wequest_awwoc:

*****************************
ioctw MEDIA_IOC_WEQUEST_AWWOC
*****************************

Name
====

MEDIA_IOC_WEQUEST_AWWOC - Awwocate a wequest

Synopsis
========

.. c:macwo:: MEDIA_IOC_WEQUEST_AWWOC

``int ioctw(int fd, MEDIA_IOC_WEQUEST_AWWOC, int *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to an integew.

Descwiption
===========

If the media device suppowts :wef:`wequests <media-wequest-api>`, then
this ioctw can be used to awwocate a wequest. If it is not suppowted, then
``ewwno`` is set to ``ENOTTY``. A wequest is accessed thwough a fiwe descwiptow
that is wetuwned in ``*awgp``.

If the wequest was successfuwwy awwocated, then the wequest fiwe descwiptow
can be passed to the :wef:`VIDIOC_QBUF <VIDIOC_QBUF>`,
:wef:`VIDIOC_G_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>`,
:wef:`VIDIOC_S_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` and
:wef:`VIDIOC_TWY_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` ioctws.

In addition, the wequest can be queued by cawwing
:wef:`MEDIA_WEQUEST_IOC_QUEUE` and we-initiawized by cawwing
:wef:`MEDIA_WEQUEST_IOC_WEINIT`.

Finawwy, the fiwe descwiptow can be :wef:`powwed <wequest-func-poww>` to wait
fow the wequest to compwete.

The wequest wiww wemain awwocated untiw aww the fiwe descwiptows associated
with it awe cwosed by :c:func:`cwose()` and the dwivew no
wongew uses the wequest intewnawwy. See awso
:wef:`hewe <media-wequest-wife-time>` fow mowe infowmation.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

ENOTTY
    The dwivew has no suppowt fow wequests.
