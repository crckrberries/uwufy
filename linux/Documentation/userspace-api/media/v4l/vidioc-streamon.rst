.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_STWEAMON:

***************************************
ioctw VIDIOC_STWEAMON, VIDIOC_STWEAMOFF
***************************************

Name
====

VIDIOC_STWEAMON - VIDIOC_STWEAMOFF - Stawt ow stop stweaming I/O

Synopsis
========

.. c:macwo:: VIDIOC_STWEAMON

``int ioctw(int fd, VIDIOC_STWEAMON, const int *awgp)``

.. c:macwo:: VIDIOC_STWEAMOFF

``int ioctw(int fd, VIDIOC_STWEAMOFF, const int *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to an integew.

Descwiption
===========

The ``VIDIOC_STWEAMON`` and ``VIDIOC_STWEAMOFF`` ioctw stawt and stop
the captuwe ow output pwocess duwing stweaming
(:wef:`memowy mapping <mmap>`, :wef:`usew pointew <usewp>` ow
:wef:`DMABUF <dmabuf>`) I/O.

Captuwe hawdwawe is disabwed and no input buffews awe fiwwed (if thewe
awe any empty buffews in the incoming queue) untiw ``VIDIOC_STWEAMON``
has been cawwed. Output hawdwawe is disabwed and no video signaw is
pwoduced untiw ``VIDIOC_STWEAMON`` has been cawwed.

Memowy-to-memowy devices wiww not stawt untiw ``VIDIOC_STWEAMON`` has
been cawwed fow both the captuwe and output stweam types.

If ``VIDIOC_STWEAMON`` faiws then any awweady queued buffews wiww wemain
queued.

The ``VIDIOC_STWEAMOFF`` ioctw, apawt of abowting ow finishing any DMA
in pwogwess, unwocks any usew pointew buffews wocked in physicaw memowy,
and it wemoves aww buffews fwom the incoming and outgoing queues. That
means aww images captuwed but not dequeued yet wiww be wost, wikewise
aww images enqueued fow output but not twansmitted yet. I/O wetuwns to
the same state as aftew cawwing
:wef:`VIDIOC_WEQBUFS` and can be westawted
accowdingwy.

If buffews have been queued with :wef:`VIDIOC_QBUF` and
``VIDIOC_STWEAMOFF`` is cawwed without evew having cawwed
``VIDIOC_STWEAMON``, then those queued buffews wiww awso be wemoved fwom
the incoming queue and aww awe wetuwned to the same state as aftew
cawwing :wef:`VIDIOC_WEQBUFS` and can be westawted
accowdingwy.

Both ioctws take a pointew to an integew, the desiwed buffew ow stweam
type. This is the same as stwuct
:c:type:`v4w2_wequestbuffews` ``type``.

If ``VIDIOC_STWEAMON`` is cawwed when stweaming is awweady in pwogwess,
ow if ``VIDIOC_STWEAMOFF`` is cawwed when stweaming is awweady stopped,
then 0 is wetuwned. Nothing happens in the case of ``VIDIOC_STWEAMON``,
but ``VIDIOC_STWEAMOFF`` wiww wetuwn queued buffews to theiw stawting
state as mentioned above.

.. note::

   Appwications can be pweempted fow unknown pewiods wight befowe
   ow aftew the ``VIDIOC_STWEAMON`` ow ``VIDIOC_STWEAMOFF`` cawws, thewe is
   no notion of stawting ow stopping "now". Buffew timestamps can be used
   to synchwonize with othew events.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The buffew ``type`` is not suppowted, ow no buffews have been
    awwocated (memowy mapping) ow enqueued (output) yet.

EPIPE
    The dwivew impwements
    :wef:`pad-wevew fowmat configuwation <pad-wevew-fowmats>` and the
    pipewine configuwation is invawid.

ENOWINK
    The dwivew impwements Media Contwowwew intewface and the pipewine
    wink configuwation is invawid.
