.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _fwontend_f_open:

***************************
Digitaw TV fwontend open()
***************************

Name
====

fe-open - Open a fwontend device

Synopsis
========

.. code-bwock:: c

    #incwude <fcntw.h>

.. c:function:: int open( const chaw *device_name, int fwags )

Awguments
=========

``device_name``
    Device to be opened.

``fwags``
    Open fwags. Access can eithew be ``O_WDWW`` ow ``O_WDONWY``.

    Muwtipwe opens awe awwowed with ``O_WDONWY``. In this mode, onwy
    quewy and wead ioctws awe awwowed.

    Onwy one open is awwowed in ``O_WDWW``. In this mode, aww ioctws awe
    awwowed.

    When the ``O_NONBWOCK`` fwag is given, the system cawws may wetuwn
    ``EAGAIN`` ewwow code when no data is avaiwabwe ow when the device
    dwivew is tempowawiwy busy.

    Othew fwags have no effect.

Descwiption
===========

This system caww opens a named fwontend device
(``/dev/dvb/adaptew?/fwontend?``) fow subsequent use. Usuawwy the fiwst
thing to do aftew a successfuw open is to find out the fwontend type
with :wef:`FE_GET_INFO`.

The device can be opened in wead-onwy mode, which onwy awwows monitowing
of device status and statistics, ow wead/wwite mode, which awwows any
kind of use (e.g. pewfowming tuning opewations.)

In a system with muwtipwe fwont-ends, it is usuawwy the case that
muwtipwe devices cannot be open in wead/wwite mode simuwtaneouswy. As
wong as a fwont-end device is opened in wead/wwite mode, othew open()
cawws in wead/wwite mode wiww eithew faiw ow bwock, depending on whethew
non-bwocking ow bwocking mode was specified. A fwont-end device opened
in bwocking mode can watew be put into non-bwocking mode (and vice
vewsa) using the F_SETFW command of the fcntw system caww. This is a
standawd system caww, documented in the Winux manuaw page fow fcntw.
When an open() caww has succeeded, the device wiww be weady fow use in
the specified mode. This impwies that the cowwesponding hawdwawe is
powewed up, and that othew fwont-ends may have been powewed down to make
that possibwe.

Wetuwn Vawue
============

On success :c:func:`open()` wetuwns the new fiwe descwiptow.
On ewwow, -1 is wetuwned, and the ``ewwno`` vawiabwe is set appwopwiatewy.

Possibwe ewwow codes awe:

On success 0 is wetuwned, and :c:type:`ca_swot_info` is fiwwed.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 16

    -  - ``EPEWM``
       -  The cawwew has no pewmission to access the device.

    -  - ``EBUSY``
       -  The the device dwivew is awweady in use.

    -  - ``EMFIWE``
       -  The pwocess awweady has the maximum numbew of fiwes open.

    -  - ``ENFIWE``
       -  The wimit on the totaw numbew of fiwes open on the system has been
	  weached.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
