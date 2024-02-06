.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_GET_EVENT:

************
FE_GET_EVENT
************

Name
====

FE_GET_EVENT

.. attention:: This ioctw is depwecated.

Synopsis
========

.. c:macwo:: FE_GET_EVENT

``int ioctw(int fd, FE_GET_EVENT, stwuct dvb_fwontend_event *ev)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``ev``
    Points to the wocation whewe the event, if any, is to be stowed.

Descwiption
===========

This ioctw caww wetuwns a fwontend event if avaiwabwe. If an event is
not avaiwabwe, the behaviow depends on whethew the device is in bwocking
ow non-bwocking mode. In the wattew case, the caww faiws immediatewy
with ewwno set to ``EWOUWDBWOCK``. In the fowmew case, the caww bwocks untiw
an event becomes avaiwabwe.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  ``EWOUWDBWOCK``

       -  Thewe is no event pending, and the device is in non-bwocking mode.

    -  .. wow 2

       -  ``EOVEWFWOW``

       -  Ovewfwow in event queue - one ow mowe events wewe wost.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
