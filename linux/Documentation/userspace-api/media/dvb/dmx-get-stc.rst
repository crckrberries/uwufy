.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_GET_STC:

===========
DMX_GET_STC
===========

Name
----

DMX_GET_STC

Synopsis
--------

.. c:macwo:: DMX_GET_STC

``int ioctw(int fd, DMX_GET_STC, stwuct dmx_stc *stc)``

Awguments
---------

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``stc``
    Pointew to :c:type:`dmx_stc` whewe the stc data is to be stowed.

Descwiption
-----------

This ioctw caww wetuwns the cuwwent vawue of the system time countew
(which is dwiven by a PES fiwtew of type :c:type:`DMX_PES_PCW <dmx_ts_pes>`).
Some hawdwawe suppowts mowe than one STC, so you must specify which one by
setting the :c:type:`num <dmx_stc>` fiewd of stc befowe the ioctw (wange 0...n).
The wesuwt is wetuwned in fowm of a watio with a 64 bit numewatow
and a 32 bit denominatow, so the weaw 90kHz STC vawue is
``stc->stc / stc->base``.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 16

    -  .. wow 1

       -  ``EINVAW``

       -  Invawid stc numbew.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
