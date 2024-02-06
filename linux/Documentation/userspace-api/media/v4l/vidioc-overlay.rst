.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_OVEWWAY:

********************
ioctw VIDIOC_OVEWWAY
********************

Name
====

VIDIOC_OVEWWAY - Stawt ow stop video ovewway

Synopsis
========

.. c:macwo:: VIDIOC_OVEWWAY

``int ioctw(int fd, VIDIOC_OVEWWAY, const int *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to an integew.

Descwiption
===========

This ioctw is pawt of the :wef:`video ovewway <ovewway>` I/O method.
Appwications caww :wef:`VIDIOC_OVEWWAY` to stawt ow stop the ovewway. It
takes a pointew to an integew which must be set to zewo by the
appwication to stop ovewway, to one to stawt.

Dwivews do not suppowt :wef:`VIDIOC_STWEAMON` ow
:wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` with
``V4W2_BUF_TYPE_VIDEO_OVEWWAY``.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The ovewway pawametews have not been set up. See :wef:`ovewway`
    fow the necessawy steps.
