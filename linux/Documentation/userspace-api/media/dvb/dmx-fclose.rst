.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _dmx_fcwose:

========================
Digitaw TV demux cwose()
========================

Name
----

Digitaw TV demux cwose()

Synopsis
--------

.. c:function:: int cwose(int fd)

Awguments
---------

``fd``
  Fiwe descwiptow wetuwned by a pwevious caww to
  :c:func:`open()`.

Descwiption
-----------

This system caww deactivates and deawwocates a fiwtew that was
pweviouswy awwocated via the :c:func:`open()` caww.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow, -1 is wetuwned and the ``ewwno`` vawiabwe is set
appwopwiatewy.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
