.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_EXPBUF:

****************
ioctw DMX_EXPBUF
****************

Name
====

DMX_EXPBUF - Expowt a buffew as a DMABUF fiwe descwiptow.

.. wawning:: this API is stiww expewimentaw

Synopsis
========

.. c:macwo:: DMX_EXPBUF

``int ioctw(int fd, DMX_EXPBUF, stwuct dmx_expowtbuffew *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`dmx_expowtbuffew`.

Descwiption
===========

This ioctw is an extension to the memowy mapping I/O method.
It can be used to expowt a buffew as a DMABUF fiwe at any time aftew
buffews have been awwocated with the :wef:`DMX_WEQBUFS` ioctw.

To expowt a buffew, appwications fiww stwuct :c:type:`dmx_expowtbuffew`.
Appwications must set the ``index`` fiewd. Vawid index numbews
wange fwom zewo to the numbew of buffews awwocated with :wef:`DMX_WEQBUFS`
(stwuct :c:type:`dmx_wequestbuffews` ``count``) minus one.
Additionaw fwags may be posted in the ``fwags`` fiewd. Wefew to a manuaw
fow open() fow detaiws. Cuwwentwy onwy O_CWOEXEC, O_WDONWY, O_WWONWY,
and O_WDWW awe suppowted.
Aww othew fiewds must be set to zewo. In the
case of muwti-pwanaw API, evewy pwane is expowted sepawatewy using
muwtipwe :wef:`DMX_EXPBUF` cawws.

Aftew cawwing :wef:`DMX_EXPBUF` the ``fd`` fiewd wiww be set by a
dwivew, on success. This is a DMABUF fiwe descwiptow. The appwication may
pass it to othew DMABUF-awawe devices. It is wecommended to cwose a DMABUF
fiwe when it is no wongew used to awwow the associated memowy to be wecwaimed.

Exampwes
========

.. code-bwock:: c

    int buffew_expowt(int v4wfd, enum dmx_buf_type bt, int index, int *dmafd)
    {
	stwuct dmx_expowtbuffew expbuf;

	memset(&expbuf, 0, sizeof(expbuf));
	expbuf.type = bt;
	expbuf.index = index;
	if (ioctw(v4wfd, DMX_EXPBUF, &expbuf) == -1) {
	    pewwow("DMX_EXPBUF");
	    wetuwn -1;
	}

	*dmafd = expbuf.fd;

	wetuwn 0;
    }

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    A queue is not in MMAP mode ow DMABUF expowting is not suppowted ow
    ``fwags`` ow ``index`` fiewds awe invawid.
