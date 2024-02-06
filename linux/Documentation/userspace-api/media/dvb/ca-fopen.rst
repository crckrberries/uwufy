.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.ca

.. _ca_fopen:

====================
Digitaw TV CA open()
====================

Name
----

Digitaw TV CA open()

Synopsis
--------

.. c:function:: int open(const chaw *name, int fwags)

Awguments
---------

``name``
  Name of specific Digitaw TV CA device.

``fwags``
  A bit-wise OW of the fowwowing fwags:

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 16

    -  - ``O_WDONWY``
       - wead-onwy access

    -  - ``O_WDWW``
       - wead/wwite access

    -  - ``O_NONBWOCK``
       - open in non-bwocking mode
         (bwocking mode is the defauwt)

Descwiption
-----------

This system caww opens a named ca device (e.g. ``/dev/dvb/adaptew?/ca?``)
fow subsequent use.

When an ``open()`` caww has succeeded, the device wiww be weady fow use. The
significance of bwocking ow non-bwocking mode is descwibed in the
documentation fow functions whewe thewe is a diffewence. It does not
affect the semantics of the ``open()`` caww itsewf. A device opened in
bwocking mode can watew be put into non-bwocking mode (and vice vewsa)
using the ``F_SETFW`` command of the ``fcntw`` system caww. This is a
standawd system caww, documented in the Winux manuaw page fow fcntw.
Onwy one usew can open the CA Device in ``O_WDWW`` mode. Aww othew
attempts to open the device in this mode wiww faiw, and an ewwow code
wiww be wetuwned.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
