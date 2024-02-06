.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_SET_BUFFEW_SIZE:

===================
DMX_SET_BUFFEW_SIZE
===================

Name
----

DMX_SET_BUFFEW_SIZE

Synopsis
--------

.. c:macwo:: DMX_SET_BUFFEW_SIZE

``int ioctw(int fd, DMX_SET_BUFFEW_SIZE, unsigned wong size)``

Awguments
---------

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``size``
    Unsigned wong size

Descwiption
-----------

This ioctw caww is used to set the size of the ciwcuwaw buffew used fow
fiwtewed data. The defauwt size is two maximum sized sections, i.e. if
this function is not cawwed a buffew size of ``2 * 4096`` bytes wiww be
used.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
