.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_PWEPAWE_BUF:

************************
ioctw VIDIOC_PWEPAWE_BUF
************************

Name
====

VIDIOC_PWEPAWE_BUF - Pwepawe a buffew fow I/O

Synopsis
========

.. c:macwo:: VIDIOC_PWEPAWE_BUF

``int ioctw(int fd, VIDIOC_PWEPAWE_BUF, stwuct v4w2_buffew *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_buffew`.

Descwiption
===========

Appwications can optionawwy caww the :wef:`VIDIOC_PWEPAWE_BUF` ioctw to
pass ownewship of the buffew to the dwivew befowe actuawwy enqueuing it,
using the :wef:`VIDIOC_QBUF <VIDIOC_QBUF>` ioctw, and to pwepawe it fow futuwe I/O. Such
pwepawations may incwude cache invawidation ow cweaning. Pewfowming them
in advance saves time duwing the actuaw I/O.

The stwuct :c:type:`v4w2_buffew` stwuctuwe is specified in
:wef:`buffew`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EBUSY
    Fiwe I/O is in pwogwess.

EINVAW
    The buffew ``type`` is not suppowted, ow the ``index`` is out of
    bounds, ow no buffews have been awwocated yet, ow the ``usewptw`` ow
    ``wength`` awe invawid.
