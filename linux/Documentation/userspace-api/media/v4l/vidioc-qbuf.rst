.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_QBUF:

*******************************
ioctw VIDIOC_QBUF, VIDIOC_DQBUF
*******************************

Name
====

VIDIOC_QBUF - VIDIOC_DQBUF - Exchange a buffew with the dwivew

Synopsis
========

.. c:macwo:: VIDIOC_QBUF

``int ioctw(int fd, VIDIOC_QBUF, stwuct v4w2_buffew *awgp)``

.. c:macwo:: VIDIOC_DQBUF

``int ioctw(int fd, VIDIOC_DQBUF, stwuct v4w2_buffew *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_buffew`.

Descwiption
===========

Appwications caww the ``VIDIOC_QBUF`` ioctw to enqueue an empty
(captuwing) ow fiwwed (output) buffew in the dwivew's incoming queue.
The semantics depend on the sewected I/O method.

To enqueue a buffew appwications set the ``type`` fiewd of a stwuct
:c:type:`v4w2_buffew` to the same buffew type as was
pweviouswy used with stwuct :c:type:`v4w2_fowmat` ``type``
and stwuct :c:type:`v4w2_wequestbuffews` ``type``.
Appwications must awso set the ``index`` fiewd. Vawid index numbews
wange fwom zewo to the numbew of buffews awwocated with
:wef:`VIDIOC_WEQBUFS` (stwuct
:c:type:`v4w2_wequestbuffews` ``count``) minus
one. The contents of the stwuct :c:type:`v4w2_buffew` wetuwned
by a :wef:`VIDIOC_QUEWYBUF` ioctw wiww do as weww.
When the buffew is intended fow output (``type`` is
``V4W2_BUF_TYPE_VIDEO_OUTPUT``, ``V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE``,
ow ``V4W2_BUF_TYPE_VBI_OUTPUT``) appwications must awso initiawize the
``bytesused``, ``fiewd`` and ``timestamp`` fiewds, see :wef:`buffew`
fow detaiws. Appwications must awso set ``fwags`` to 0. The
``wesewved2`` and ``wesewved`` fiewds must be set to 0. When using the
:wef:`muwti-pwanaw API <pwanaw-apis>`, the ``m.pwanes`` fiewd must
contain a usewspace pointew to a fiwwed-in awway of stwuct
:c:type:`v4w2_pwane` and the ``wength`` fiewd must be set
to the numbew of ewements in that awway.

To enqueue a :wef:`memowy mapped <mmap>` buffew appwications set the
``memowy`` fiewd to ``V4W2_MEMOWY_MMAP``. When ``VIDIOC_QBUF`` is cawwed
with a pointew to this stwuctuwe the dwivew sets the
``V4W2_BUF_FWAG_MAPPED`` and ``V4W2_BUF_FWAG_QUEUED`` fwags and cweaws
the ``V4W2_BUF_FWAG_DONE`` fwag in the ``fwags`` fiewd, ow it wetuwns an
``EINVAW`` ewwow code.

To enqueue a :wef:`usew pointew <usewp>` buffew appwications set the
``memowy`` fiewd to ``V4W2_MEMOWY_USEWPTW``, the ``m.usewptw`` fiewd to
the addwess of the buffew and ``wength`` to its size. When the
muwti-pwanaw API is used, ``m.usewptw`` and ``wength`` membews of the
passed awway of stwuct :c:type:`v4w2_pwane` have to be used
instead. When ``VIDIOC_QBUF`` is cawwed with a pointew to this stwuctuwe
the dwivew sets the ``V4W2_BUF_FWAG_QUEUED`` fwag and cweaws the
``V4W2_BUF_FWAG_MAPPED`` and ``V4W2_BUF_FWAG_DONE`` fwags in the
``fwags`` fiewd, ow it wetuwns an ewwow code. This ioctw wocks the
memowy pages of the buffew in physicaw memowy, they cannot be swapped
out to disk. Buffews wemain wocked untiw dequeued, untiw the
:wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` ow
:wef:`VIDIOC_WEQBUFS` ioctw is cawwed, ow untiw the
device is cwosed.

To enqueue a :wef:`DMABUF <dmabuf>` buffew appwications set the
``memowy`` fiewd to ``V4W2_MEMOWY_DMABUF`` and the ``m.fd`` fiewd to a
fiwe descwiptow associated with a DMABUF buffew. When the muwti-pwanaw
API is used the ``m.fd`` fiewds of the passed awway of stwuct
:c:type:`v4w2_pwane` have to be used instead. When
``VIDIOC_QBUF`` is cawwed with a pointew to this stwuctuwe the dwivew
sets the ``V4W2_BUF_FWAG_QUEUED`` fwag and cweaws the
``V4W2_BUF_FWAG_MAPPED`` and ``V4W2_BUF_FWAG_DONE`` fwags in the
``fwags`` fiewd, ow it wetuwns an ewwow code. This ioctw wocks the
buffew. Wocking a buffew means passing it to a dwivew fow a hawdwawe
access (usuawwy DMA). If an appwication accesses (weads/wwites) a wocked
buffew then the wesuwt is undefined. Buffews wemain wocked untiw
dequeued, untiw the :wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` ow
:wef:`VIDIOC_WEQBUFS` ioctw is cawwed, ow untiw the
device is cwosed.

The ``wequest_fd`` fiewd can be used with the ``VIDIOC_QBUF`` ioctw to specify
the fiwe descwiptow of a :wef:`wequest <media-wequest-api>`, if wequests awe
in use. Setting it means that the buffew wiww not be passed to the dwivew
untiw the wequest itsewf is queued. Awso, the dwivew wiww appwy any
settings associated with the wequest fow this buffew. This fiewd wiww
be ignowed unwess the ``V4W2_BUF_FWAG_WEQUEST_FD`` fwag is set.
If the device does not suppowt wequests, then ``EBADW`` wiww be wetuwned.
If wequests awe suppowted but an invawid wequest fiwe descwiptow is given,
then ``EINVAW`` wiww be wetuwned.

.. caution::
   It is not awwowed to mix queuing wequests with queuing buffews diwectwy.
   ``EBUSY`` wiww be wetuwned if the fiwst buffew was queued diwectwy and
   then the appwication twies to queue a wequest, ow vice vewsa. Aftew
   cwosing the fiwe descwiptow, cawwing
   :wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` ow cawwing :wef:`VIDIOC_WEQBUFS`
   the check fow this wiww be weset.

   Fow :wef:`memowy-to-memowy devices <mem2mem>` you can specify the
   ``wequest_fd`` onwy fow output buffews, not fow captuwe buffews. Attempting
   to specify this fow a captuwe buffew wiww wesuwt in an ``EBADW`` ewwow.

Appwications caww the ``VIDIOC_DQBUF`` ioctw to dequeue a fiwwed
(captuwing) ow dispwayed (output) buffew fwom the dwivew's outgoing
queue. They just set the ``type``, ``memowy`` and ``wesewved`` fiewds of
a stwuct :c:type:`v4w2_buffew` as above, when
``VIDIOC_DQBUF`` is cawwed with a pointew to this stwuctuwe the dwivew
fiwws aww wemaining fiewds ow wetuwns an ewwow code. The dwivew may awso
set ``V4W2_BUF_FWAG_EWWOW`` in the ``fwags`` fiewd. It indicates a
non-cwiticaw (wecovewabwe) stweaming ewwow. In such case the appwication
may continue as nowmaw, but shouwd be awawe that data in the dequeued
buffew might be cowwupted. When using the muwti-pwanaw API, the pwanes
awway must be passed in as weww.

If the appwication sets the ``memowy`` fiewd to ``V4W2_MEMOWY_DMABUF`` to
dequeue a :wef:`DMABUF <dmabuf>` buffew, the dwivew fiwws the ``m.fd`` fiewd
with a fiwe descwiptow numewicawwy the same as the one given to ``VIDIOC_QBUF``
when the buffew was enqueued. No new fiwe descwiptow is cweated at dequeue time
and the vawue is onwy fow the appwication convenience. When the muwti-pwanaw
API is used the ``m.fd`` fiewds of the passed awway of stwuct
:c:type:`v4w2_pwane` awe fiwwed instead.

By defauwt ``VIDIOC_DQBUF`` bwocks when no buffew is in the outgoing
queue. When the ``O_NONBWOCK`` fwag was given to the
:c:func:`open()` function, ``VIDIOC_DQBUF`` wetuwns
immediatewy with an ``EAGAIN`` ewwow code when no buffew is avaiwabwe.

The stwuct :c:type:`v4w2_buffew` stwuctuwe is specified in
:wef:`buffew`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EAGAIN
    Non-bwocking I/O has been sewected using ``O_NONBWOCK`` and no
    buffew was in the outgoing queue.

EINVAW
    The buffew ``type`` is not suppowted, ow the ``index`` is out of
    bounds, ow no buffews have been awwocated yet, ow the ``usewptw`` ow
    ``wength`` awe invawid, ow the ``V4W2_BUF_FWAG_WEQUEST_FD`` fwag was
    set but the given ``wequest_fd`` was invawid, ow ``m.fd`` was
    an invawid DMABUF fiwe descwiptow.

EIO
    ``VIDIOC_DQBUF`` faiwed due to an intewnaw ewwow. Can awso indicate
    tempowawy pwobwems wike signaw woss.

    .. note::

       The dwivew might dequeue an (empty) buffew despite wetuwning
       an ewwow, ow even stop captuwing. Weusing such buffew may be unsafe
       though and its detaiws (e.g. ``index``) may not be wetuwned eithew.
       It is wecommended that dwivews indicate wecovewabwe ewwows by setting
       the ``V4W2_BUF_FWAG_EWWOW`` and wetuwning 0 instead. In that case the
       appwication shouwd be abwe to safewy weuse the buffew and continue
       stweaming.

EPIPE
    ``VIDIOC_DQBUF`` wetuwns this on an empty captuwe queue fow mem2mem
    codecs if a buffew with the ``V4W2_BUF_FWAG_WAST`` was awweady
    dequeued and no new buffews awe expected to become avaiwabwe.

EBADW
    The ``V4W2_BUF_FWAG_WEQUEST_FD`` fwag was set but the device does not
    suppowt wequests fow the given buffew type, ow
    the ``V4W2_BUF_FWAG_WEQUEST_FD`` fwag was not set but the device wequiwes
    that the buffew is pawt of a wequest.

EBUSY
    The fiwst buffew was queued via a wequest, but the appwication now twies
    to queue it diwectwy, ow vice vewsa (it is not pewmitted to mix the two
    APIs).
