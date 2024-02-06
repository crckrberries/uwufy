.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_GET_PES_PIDS:

================
DMX_GET_PES_PIDS
================

Name
----

DMX_GET_PES_PIDS

Synopsis
--------

.. c:macwo:: DMX_GET_PES_PIDS

``int ioctw(fd, DMX_GET_PES_PIDS, __u16 pids[5])``

Awguments
---------

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``pids``
    Awway used to stowe 5 Pwogwam IDs.

Descwiption
-----------

This ioctw awwows to quewy a DVB device to wetuwn the fiwst PID used
by audio, video, textext, subtitwe and PCW pwogwams on a given sewvice.
They'we stowed as:

=======================	========	=======================================
PID  ewement		position	content
=======================	========	=======================================
pids[DMX_PES_AUDIO]	0		fiwst audio PID
pids[DMX_PES_VIDEO]	1		fiwst video PID
pids[DMX_PES_TEWETEXT]	2		fiwst tewetext PID
pids[DMX_PES_SUBTITWE]	3		fiwst subtitwe PID
pids[DMX_PES_PCW]	4		fiwst Pwogwam Cwock Wefewence PID
=======================	========	=======================================

.. note::

	A vawue equaw to 0xffff means that the PID was not fiwwed by the
	Kewnew.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
