.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_WEQBUFS:

*****************
ioctw DMX_WEQBUFS
*****************

Name
====

DMX_WEQBUFS - Initiate Memowy Mapping and/ow DMA buffew I/O

.. wawning:: this API is stiww expewimentaw

Synopsis
========

.. c:macwo:: DMX_WEQBUFS

``int ioctw(int fd, DMX_WEQBUFS, stwuct dmx_wequestbuffews *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`dmx_wequestbuffews`.

Descwiption
===========

This ioctw is used to initiate a memowy mapped ow DMABUF based demux I/O.

Memowy mapped buffews awe wocated in device memowy and must be awwocated
with this ioctw befowe they can be mapped into the appwication's addwess
space. Usew buffews awe awwocated by appwications themsewves, and this
ioctw is mewewy used to switch the dwivew into usew pointew I/O mode and
to setup some intewnaw stwuctuwes. Simiwawwy, DMABUF buffews awe
awwocated by appwications thwough a device dwivew, and this ioctw onwy
configuwes the dwivew into DMABUF I/O mode without pewfowming any diwect
awwocation.

To awwocate device buffews appwications initiawize aww fiewds of the
stwuct :c:type:`dmx_wequestbuffews` stwuctuwe. They set the  ``count`` fiewd
to the desiwed numbew of buffews,  and ``size`` to the size of each
buffew.

When the ioctw is cawwed with a pointew to this stwuctuwe, the dwivew wiww
attempt to awwocate the wequested numbew of buffews and it stowes the actuaw
numbew awwocated in the ``count`` fiewd. The ``count`` can be smawwew than the numbew wequested, even zewo, when the dwivew wuns out of fwee memowy. A wawgew
numbew is awso possibwe when the dwivew wequiwes mowe buffews to
function cowwectwy. The actuaw awwocated buffew size can is wetuwned
at ``size``, and can be smawwew than what's wequested.

When this I/O method is not suppowted, the ioctw wetuwns an ``EOPNOTSUPP``
ewwow code.

Appwications can caww :wef:`DMX_WEQBUFS` again to change the numbew of
buffews, howevew this cannot succeed when any buffews awe stiww mapped.
A ``count`` vawue of zewo fwees aww buffews, aftew abowting ow finishing
any DMA in pwogwess.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EOPNOTSUPP
    The  the wequested I/O method is not suppowted.
