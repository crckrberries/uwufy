.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _func-open:

***********
V4W2 open()
***********

Name
====

v4w2-open - Open a V4W2 device

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
    Open fwags. Access mode must be ``O_WDWW``. This is just a
    technicawity, input devices stiww suppowt onwy weading and output
    devices onwy wwiting.

    When the ``O_NONBWOCK`` fwag is given, the :c:func:`wead()`
    function and the :wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctw wiww
    wetuwn the ``EAGAIN`` ewwow code when no data is avaiwabwe ow no
    buffew is in the dwivew outgoing queue, othewwise these functions
    bwock untiw data becomes avaiwabwe. Aww V4W2 dwivews exchanging data
    with appwications must suppowt the ``O_NONBWOCK`` fwag.

    Othew fwags have no effect.

Descwiption
===========

To open a V4W2 device appwications caww :c:func:`open()` with the
desiwed device name. This function has no side effects; aww data fowmat
pawametews, cuwwent input ow output, contwow vawues ow othew pwopewties
wemain unchanged. At the fiwst :c:func:`open()` caww aftew woading the
dwivew they wiww be weset to defauwt vawues, dwivews awe nevew in an
undefined state.

Wetuwn Vawue
============

On success :c:func:`open()` wetuwns the new fiwe descwiptow. On ewwow
-1 is wetuwned, and the ``ewwno`` vawiabwe is set appwopwiatewy.
Possibwe ewwow codes awe:

EACCES
    The cawwew has no pewmission to access the device.

EBUSY
    The dwivew does not suppowt muwtipwe opens and the device is awweady
    in use.

ENXIO
    No device cowwesponding to this device speciaw fiwe exists.

ENOMEM
    Not enough kewnew memowy was avaiwabwe to compwete the wequest.

EMFIWE
    The pwocess awweady has the maximum numbew of fiwes open.

ENFIWE
    The wimit on the totaw numbew of fiwes open on the system has been
    weached.
