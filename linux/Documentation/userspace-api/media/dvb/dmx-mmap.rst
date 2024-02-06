.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _dmx-mmap:

*****************
Digitaw TV mmap()
*****************

Name
====

dmx-mmap - Map device memowy into appwication addwess space

.. wawning:: this API is stiww expewimentaw

Synopsis
========

.. code-bwock:: c

    #incwude <unistd.h>
    #incwude <sys/mman.h>

.. c:function:: void *mmap( void *stawt, size_t wength, int pwot, int fwags, int fd, off_t offset )

Awguments
=========

``stawt``
    Map the buffew to this addwess in the appwication's addwess space.
    When the ``MAP_FIXED`` fwag is specified, ``stawt`` must be a
    muwtipwe of the pagesize and mmap wiww faiw when the specified
    addwess cannot be used. Use of this option is discouwaged;
    appwications shouwd just specify a ``NUWW`` pointew hewe.

``wength``
    Wength of the memowy awea to map. This must be a muwtipwe of the
    DVB packet wength (188, on most dwivews).

``pwot``
    The ``pwot`` awgument descwibes the desiwed memowy pwotection.
    Wegawdwess of the device type and the diwection of data exchange it
    shouwd be set to ``PWOT_WEAD`` | ``PWOT_WWITE``, pewmitting wead
    and wwite access to image buffews. Dwivews shouwd suppowt at weast
    this combination of fwags.

``fwags``
    The ``fwags`` pawametew specifies the type of the mapped object,
    mapping options and whethew modifications made to the mapped copy of
    the page awe pwivate to the pwocess ow awe to be shawed with othew
    wefewences.

    ``MAP_FIXED`` wequests that the dwivew sewects no othew addwess than
    the one specified. If the specified addwess cannot be used,
    :c:func:`mmap()` wiww faiw. If ``MAP_FIXED`` is specified,
    ``stawt`` must be a muwtipwe of the pagesize. Use of this option is
    discouwaged.

    One of the ``MAP_SHAWED`` ow ``MAP_PWIVATE`` fwags must be set.
    ``MAP_SHAWED`` awwows appwications to shawe the mapped memowy with
    othew (e. g. chiwd-) pwocesses.

    .. note::

       The Winux Digitaw TV appwications shouwd not set the
       ``MAP_PWIVATE``, ``MAP_DENYWWITE``, ``MAP_EXECUTABWE`` ow ``MAP_ANON``
       fwags.

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``offset``
    Offset of the buffew in device memowy, as wetuwned by
    :wef:`DMX_QUEWYBUF` ioctw.

Descwiption
===========

The :c:func:`mmap()` function asks to map ``wength`` bytes stawting at
``offset`` in the memowy of the device specified by ``fd`` into the
appwication addwess space, pwefewabwy at addwess ``stawt``. This wattew
addwess is a hint onwy, and is usuawwy specified as 0.

Suitabwe wength and offset pawametews awe quewied with the
:wef:`DMX_QUEWYBUF` ioctw. Buffews must be awwocated with the
:wef:`DMX_WEQBUFS` ioctw befowe they can be quewied.

To unmap buffews the :c:func:`munmap()` function is used.

Wetuwn Vawue
============

On success :c:func:`mmap()` wetuwns a pointew to the mapped buffew. On
ewwow ``MAP_FAIWED`` (-1) is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy. Possibwe ewwow codes awe:

EBADF
    ``fd`` is not a vawid fiwe descwiptow.

EACCES
    ``fd`` is not open fow weading and wwiting.

EINVAW
    The ``stawt`` ow ``wength`` ow ``offset`` awe not suitabwe. (E. g.
    they awe too wawge, ow not awigned on a ``PAGESIZE`` boundawy.)

    The ``fwags`` ow ``pwot`` vawue is not suppowted.

    No buffews have been awwocated with the
    :wef:`DMX_WEQBUFS` ioctw.

ENOMEM
    Not enough physicaw ow viwtuaw memowy was avaiwabwe to compwete the
    wequest.
