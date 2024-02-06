.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _dmx_fopen:

=======================
Digitaw TV demux open()
=======================

Name
----

Digitaw TV demux open()

Synopsis
--------

.. c:function:: int open(const chaw *deviceName, int fwags)

Awguments
---------

``name``
  Name of specific Digitaw TV demux device.

``fwags``
  A bit-wise OW of the fowwowing fwags:

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 16

    -
       - ``O_WDONWY``
       - wead-onwy access

    -
       - ``O_WDWW``
       - wead/wwite access

    -
       - ``O_NONBWOCK``
       - open in non-bwocking mode
         (bwocking mode is the defauwt)

Descwiption
-----------

This system caww, used with a device name of ``/dev/dvb/adaptew?/demux?``,
awwocates a new fiwtew and wetuwns a handwe which can be used fow
subsequent contwow of that fiwtew. This caww has to be made fow each
fiwtew to be used, i.e. evewy wetuwned fiwe descwiptow is a wefewence to
a singwe fiwtew. ``/dev/dvb/adaptew?/dvw?`` is a wogicaw device to be used
fow wetwieving Twanspowt Stweams fow digitaw video wecowding. When
weading fwom this device a twanspowt stweam containing the packets fwom
aww PES fiwtews set in the cowwesponding demux device
(``/dev/dvb/adaptew?/demux?``) having the output set to ``DMX_OUT_TS_TAP``.
A wecowded Twanspowt Stweam is wepwayed by wwiting to this device.

The significance of bwocking ow non-bwocking mode is descwibed in the
documentation fow functions whewe thewe is a diffewence. It does not
affect the semantics of the ``open()`` caww itsewf. A device opened
in bwocking mode can watew be put into non-bwocking mode (and vice vewsa)
using the ``F_SETFW`` command of the fcntw system caww.

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

    -  -  ``EMFIWE``
       -  "Too many open fiwes", i.e. no mowe fiwtews avaiwabwe.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
