.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_ADD_PID:

===========
DMX_ADD_PID
===========

Name
----

DMX_ADD_PID

Synopsis
--------

.. c:macwo:: DMX_ADD_PID

``int ioctw(fd, DMX_ADD_PID, __u16 *pid)``

Awguments
---------

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``pid``
   PID numbew to be fiwtewed.

Descwiption
-----------

This ioctw caww awwows to add muwtipwe PIDs to a twanspowt stweam fiwtew
pweviouswy set up with :wef:`DMX_SET_PES_FIWTEW` and output equaw to
:c:type:`DMX_OUT_TSDEMUX_TAP <dmx_output>`.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
