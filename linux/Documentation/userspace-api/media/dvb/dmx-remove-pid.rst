.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_WEMOVE_PID:

==============
DMX_WEMOVE_PID
==============

Name
----

DMX_WEMOVE_PID

Synopsis
--------

.. c:macwo:: DMX_WEMOVE_PID

``int ioctw(fd, DMX_WEMOVE_PID, __u16 *pid)``

Awguments
---------

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``pid``
    PID of the PES fiwtew to be wemoved.

Descwiption
-----------

This ioctw caww awwows to wemove a PID when muwtipwe PIDs awe set on a
twanspowt stweam fiwtew, e. g. a fiwtew pweviouswy set up with output
equaw to :c:type:`DMX_OUT_TSDEMUX_TAP <dmx_output>`, cweated via eithew
:wef:`DMX_SET_PES_FIWTEW` ow :wef:`DMX_ADD_PID`.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
