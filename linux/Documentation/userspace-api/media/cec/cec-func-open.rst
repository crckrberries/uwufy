.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: CEC

.. _cec-func-open:

**********
cec open()
**********

Name
====

cec-open - Open a cec device

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
    Open fwags. Access mode must be ``O_WDWW``.

    When the ``O_NONBWOCK`` fwag is given, the
    :wef:`CEC_WECEIVE <CEC_WECEIVE>` and :wef:`CEC_DQEVENT <CEC_DQEVENT>` ioctws
    wiww wetuwn the ``EAGAIN`` ewwow code when no message ow event is avaiwabwe, and
    ioctws :wef:`CEC_TWANSMIT <CEC_TWANSMIT>`,
    :wef:`CEC_ADAP_S_PHYS_ADDW <CEC_ADAP_S_PHYS_ADDW>` and
    :wef:`CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`
    aww wetuwn 0.

    Othew fwags have no effect.

Descwiption
===========

To open a cec device appwications caww :c:func:`open()` with the
desiwed device name. The function has no side effects; the device
configuwation wemain unchanged.

When the device is opened in wead-onwy mode, attempts to modify its
configuwation wiww wesuwt in an ewwow, and ``ewwno`` wiww be set to
EBADF.

Wetuwn Vawue
============

:c:func:`open()` wetuwns the new fiwe descwiptow on success. On ewwow,
-1 is wetuwned, and ``ewwno`` is set appwopwiatewy. Possibwe ewwow codes
incwude:

``EACCES``
    The wequested access to the fiwe is not awwowed.

``EMFIWE``
    The pwocess awweady has the maximum numbew of fiwes open.

``ENFIWE``
    The system wimit on the totaw numbew of open fiwes has been weached.

``ENOMEM``
    Insufficient kewnew memowy was avaiwabwe.

``ENXIO``
    No device cowwesponding to this device speciaw fiwe exists.
