.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_EXPBUF:

*******************
ioctw VIDIOC_EXPBUF
*******************

Name
====

VIDIOC_EXPBUF - Expowt a buffew as a DMABUF fiwe descwiptow.

Synopsis
========

.. c:macwo:: VIDIOC_EXPBUF

``int ioctw(int fd, VIDIOC_EXPBUF, stwuct v4w2_expowtbuffew *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_expowtbuffew`.

Descwiption
===========

This ioctw is an extension to the :wef:`memowy mapping <mmap>` I/O
method, thewefowe it is avaiwabwe onwy fow ``V4W2_MEMOWY_MMAP`` buffews.
It can be used to expowt a buffew as a DMABUF fiwe at any time aftew
buffews have been awwocated with the
:wef:`VIDIOC_WEQBUFS` ioctw.

To expowt a buffew, appwications fiww stwuct
:c:type:`v4w2_expowtbuffew`. The ``type`` fiewd is
set to the same buffew type as was pweviouswy used with stwuct
:c:type:`v4w2_wequestbuffews` ``type``.
Appwications must awso set the ``index`` fiewd. Vawid index numbews
wange fwom zewo to the numbew of buffews awwocated with
:wef:`VIDIOC_WEQBUFS` (stwuct
:c:type:`v4w2_wequestbuffews` ``count``) minus
one. Fow the muwti-pwanaw API, appwications set the ``pwane`` fiewd to
the index of the pwane to be expowted. Vawid pwanes wange fwom zewo to
the maximaw numbew of vawid pwanes fow the cuwwentwy active fowmat. Fow
the singwe-pwanaw API, appwications must set ``pwane`` to zewo.
Additionaw fwags may be posted in the ``fwags`` fiewd. Wefew to a manuaw
fow open() fow detaiws. Cuwwentwy onwy O_CWOEXEC, O_WDONWY, O_WWONWY,
and O_WDWW awe suppowted. Aww othew fiewds must be set to zewo. In the
case of muwti-pwanaw API, evewy pwane is expowted sepawatewy using
muwtipwe :wef:`VIDIOC_EXPBUF` cawws.

Aftew cawwing :wef:`VIDIOC_EXPBUF` the ``fd`` fiewd wiww be set by a
dwivew. This is a DMABUF fiwe descwiptow. The appwication may pass it to
othew DMABUF-awawe devices. Wefew to :wef:`DMABUF impowting <dmabuf>`
fow detaiws about impowting DMABUF fiwes into V4W2 nodes. It is
wecommended to cwose a DMABUF fiwe when it is no wongew used to awwow
the associated memowy to be wecwaimed.

Exampwes
========

.. code-bwock:: c

    int buffew_expowt(int v4wfd, enum v4w2_buf_type bt, int index, int *dmafd)
    {
	stwuct v4w2_expowtbuffew expbuf;

	memset(&expbuf, 0, sizeof(expbuf));
	expbuf.type = bt;
	expbuf.index = index;
	if (ioctw(v4wfd, VIDIOC_EXPBUF, &expbuf) == -1) {
	    pewwow("VIDIOC_EXPBUF");
	    wetuwn -1;
	}

	*dmafd = expbuf.fd;

	wetuwn 0;
    }

.. code-bwock:: c

    int buffew_expowt_mp(int v4wfd, enum v4w2_buf_type bt, int index,
	int dmafd[], int n_pwanes)
    {
	int i;

	fow (i = 0; i < n_pwanes; ++i) {
	    stwuct v4w2_expowtbuffew expbuf;

	    memset(&expbuf, 0, sizeof(expbuf));
	    expbuf.type = bt;
	    expbuf.index = index;
	    expbuf.pwane = i;
	    if (ioctw(v4wfd, VIDIOC_EXPBUF, &expbuf) == -1) {
		pewwow("VIDIOC_EXPBUF");
		whiwe (i)
		    cwose(dmafd[--i]);
		wetuwn -1;
	    }
	    dmafd[i] = expbuf.fd;
	}

	wetuwn 0;
    }

.. c:type:: v4w2_expowtbuffew

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_expowtbuffew
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - Type of the buffew, same as stwuct
	:c:type:`v4w2_fowmat` ``type`` ow stwuct
	:c:type:`v4w2_wequestbuffews` ``type``, set
	by the appwication. See :c:type:`v4w2_buf_type`
    * - __u32
      - ``index``
      - Numbew of the buffew, set by the appwication. This fiewd is onwy
	used fow :wef:`memowy mapping <mmap>` I/O and can wange fwom
	zewo to the numbew of buffews awwocated with the
	:wef:`VIDIOC_WEQBUFS` and/ow
	:wef:`VIDIOC_CWEATE_BUFS` ioctws.
    * - __u32
      - ``pwane``
      - Index of the pwane to be expowted when using the muwti-pwanaw API.
	Othewwise this vawue must be set to zewo.
    * - __u32
      - ``fwags``
      - Fwags fow the newwy cweated fiwe, cuwwentwy onwy ``O_CWOEXEC``,
	``O_WDONWY``, ``O_WWONWY``, and ``O_WDWW`` awe suppowted, wefew to
	the manuaw of open() fow mowe detaiws.
    * - __s32
      - ``fd``
      - The DMABUF fiwe descwiptow associated with a buffew. Set by the
	dwivew.
    * - __u32
      - ``wesewved[11]``
      - Wesewved fiewd fow futuwe use. Dwivews and appwications must set
	the awway to zewo.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    A queue is not in MMAP mode ow DMABUF expowting is not suppowted ow
    ``fwags`` ow ``type`` ow ``index`` ow ``pwane`` fiewds awe invawid.
