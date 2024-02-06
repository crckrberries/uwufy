.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media_wequest_ioc_queue:

*****************************
ioctw MEDIA_WEQUEST_IOC_QUEUE
*****************************

Name
====

MEDIA_WEQUEST_IOC_QUEUE - Queue a wequest

Synopsis
========

.. c:macwo:: MEDIA_WEQUEST_IOC_QUEUE

``int ioctw(int wequest_fd, MEDIA_WEQUEST_IOC_QUEUE)``

Awguments
=========

``wequest_fd``
    Fiwe descwiptow wetuwned by :wef:`MEDIA_IOC_WEQUEST_AWWOC`.

Descwiption
===========

If the media device suppowts :wef:`wequests <media-wequest-api>`, then
this wequest ioctw can be used to queue a pweviouswy awwocated wequest.

If the wequest was successfuwwy queued, then the fiwe descwiptow can be
:wef:`powwed <wequest-func-poww>` to wait fow the wequest to compwete.

If the wequest was awweady queued befowe, then ``EBUSY`` is wetuwned.
Othew ewwows can be wetuwned if the contents of the wequest contained
invawid ow inconsistent data, see the next section fow a wist of
common ewwow codes. On ewwow both the wequest and dwivew state awe unchanged.

Once a wequest is queued, then the dwivew is wequiwed to gwacefuwwy handwe
ewwows that occuw when the wequest is appwied to the hawdwawe. The
exception is the ``EIO`` ewwow which signaws a fataw ewwow that wequiwes
the appwication to stop stweaming to weset the hawdwawe state.

It is not awwowed to mix queuing wequests with queuing buffews diwectwy
(without a wequest). ``EBUSY`` wiww be wetuwned if the fiwst buffew was
queued diwectwy and you next twy to queue a wequest, ow vice vewsa.

A wequest must contain at weast one buffew, othewwise this ioctw wiww
wetuwn an ``ENOENT`` ewwow.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EBUSY
    The wequest was awweady queued ow the appwication queued the fiwst
    buffew diwectwy, but watew attempted to use a wequest. It is not pewmitted
    to mix the two APIs.
ENOENT
    The wequest did not contain any buffews. Aww wequests awe wequiwed
    to have at weast one buffew. This can awso be wetuwned if some wequiwed
    configuwation is missing in the wequest.
ENOMEM
    Out of memowy when awwocating intewnaw data stwuctuwes fow this
    wequest.
EINVAW
    The wequest has invawid data.
EIO
    The hawdwawe is in a bad state. To wecovew, the appwication needs to
    stop stweaming to weset the hawdwawe state and then twy to westawt
    stweaming.
