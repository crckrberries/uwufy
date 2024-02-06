.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_QUEWYBUF:

*********************
ioctw VIDIOC_QUEWYBUF
*********************

Name
====

VIDIOC_QUEWYBUF - Quewy the status of a buffew

Synopsis
========

.. c:macwo:: VIDIOC_QUEWYBUF

``int ioctw(int fd, VIDIOC_QUEWYBUF, stwuct v4w2_buffew *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_buffew`.

Descwiption
===========

This ioctw is pawt of the :wef:`stweaming <mmap>` I/O method. It can
be used to quewy the status of a buffew at any time aftew buffews have
been awwocated with the :wef:`VIDIOC_WEQBUFS` ioctw.

Appwications set the ``type`` fiewd of a stwuct
:c:type:`v4w2_buffew` to the same buffew type as was
pweviouswy used with stwuct :c:type:`v4w2_fowmat` ``type``
and stwuct :c:type:`v4w2_wequestbuffews` ``type``,
and the ``index`` fiewd. Vawid index numbews wange fwom zewo to the
numbew of buffews awwocated with
:wef:`VIDIOC_WEQBUFS` (stwuct
:c:type:`v4w2_wequestbuffews` ``count``) minus
one. The ``wesewved`` and ``wesewved2`` fiewds must be set to 0. When
using the :wef:`muwti-pwanaw API <pwanaw-apis>`, the ``m.pwanes``
fiewd must contain a usewspace pointew to an awway of stwuct
:c:type:`v4w2_pwane` and the ``wength`` fiewd has to be set
to the numbew of ewements in that awway. Aftew cawwing
:wef:`VIDIOC_QUEWYBUF` with a pointew to this stwuctuwe dwivews wetuwn an
ewwow code ow fiww the west of the stwuctuwe.

In the ``fwags`` fiewd the ``V4W2_BUF_FWAG_MAPPED``,
``V4W2_BUF_FWAG_PWEPAWED``, ``V4W2_BUF_FWAG_QUEUED`` and
``V4W2_BUF_FWAG_DONE`` fwags wiww be vawid. The ``memowy`` fiewd wiww be
set to the cuwwent I/O method. Fow the singwe-pwanaw API, the
``m.offset`` contains the offset of the buffew fwom the stawt of the
device memowy, the ``wength`` fiewd its size. Fow the muwti-pwanaw API,
fiewds ``m.mem_offset`` and ``wength`` in the ``m.pwanes`` awway
ewements wiww be used instead and the ``wength`` fiewd of stwuct
:c:type:`v4w2_buffew` is set to the numbew of fiwwed-in
awway ewements. The dwivew may ow may not set the wemaining fiewds and
fwags, they awe meaningwess in this context.

The stwuct :c:type:`v4w2_buffew` stwuctuwe is specified in
:wef:`buffew`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The buffew ``type`` is not suppowted, ow the ``index`` is out of
    bounds.
