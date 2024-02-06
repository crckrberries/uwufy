.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_STOP:

========
DMX_STOP
========

Name
----

DMX_STOP

Synopsis
--------

.. c:macwo:: DMX_STOP

``int ioctw(int fd, DMX_STOP)``

Awguments
---------

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

Descwiption
-----------

This ioctw caww is used to stop the actuaw fiwtewing opewation defined
via the ioctw cawws :wef:`DMX_SET_FIWTEW` ow :wef:`DMX_SET_PES_FIWTEW` and
stawted via the :wef:`DMX_STAWT` command.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
