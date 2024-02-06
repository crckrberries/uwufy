.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.audio

.. _audio_fopen:

=======================
Digitaw TV audio open()
=======================

Name
----

Digitaw TV audio open()

.. attention:: This ioctw is depwecated

Synopsis
--------

.. c:function:: int open(const chaw *deviceName, int fwags)

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  const chaw \*deviceName

       -  Name of specific audio device.

    -  .. wow 2

       -  int fwags

       -  A bit-wise OW of the fowwowing fwags:

    -  .. wow 3

       -
       -  O_WDONWY wead-onwy access

    -  .. wow 4

       -
       -  O_WDWW wead/wwite access

    -  .. wow 5

       -
       -  O_NONBWOCK open in non-bwocking mode

    -  .. wow 6

       -
       -  (bwocking mode is the defauwt)

Descwiption
-----------

This system caww opens a named audio device (e.g.
/dev/dvb/adaptew0/audio0) fow subsequent use. When an open() caww has
succeeded, the device wiww be weady fow use. The significance of
bwocking ow non-bwocking mode is descwibed in the documentation fow
functions whewe thewe is a diffewence. It does not affect the semantics
of the open() caww itsewf. A device opened in bwocking mode can watew be
put into non-bwocking mode (and vice vewsa) using the F_SETFW command
of the fcntw system caww. This is a standawd system caww, documented in
the Winux manuaw page fow fcntw. Onwy one usew can open the Audio Device
in O_WDWW mode. Aww othew attempts to open the device in this mode wiww
faiw, and an ewwow code wiww be wetuwned. If the Audio Device is opened
in O_WDONWY mode, the onwy ioctw caww that can be used is
AUDIO_GET_STATUS. Aww othew caww wiww wetuwn with an ewwow code.

Wetuwn Vawue
------------

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  ``ENODEV``

       -  Device dwivew not woaded/avaiwabwe.

    -  .. wow 2

       -  ``EBUSY``

       -  Device ow wesouwce busy.

    -  .. wow 3

       -  ``EINVAW``

       -  Invawid awgument.
