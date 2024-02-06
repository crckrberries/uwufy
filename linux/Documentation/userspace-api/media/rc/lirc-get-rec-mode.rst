.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_get_wec_mode:
.. _wiwc_set_wec_mode:

**********************************************
ioctws WIWC_GET_WEC_MODE and WIWC_SET_WEC_MODE
**********************************************

Name
====

WIWC_GET_WEC_MODE/WIWC_SET_WEC_MODE - Get/set cuwwent weceive mode.

Synopsis
========

.. c:macwo:: WIWC_GET_WEC_MODE

``int ioctw(int fd, WIWC_GET_WEC_MODE, __u32 *mode)``

.. c:macwo:: WIWC_SET_WEC_MODE

``int ioctw(int fd, WIWC_SET_WEC_MODE, __u32 *mode)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``mode``
    Mode used fow weceive.

Descwiption
===========

Get and set the cuwwent weceive mode. Onwy
:wef:`WIWC_MODE_MODE2 <wiwc-mode-mode2>` and
:wef:`WIWC_MODE_SCANCODE <wiwc-mode-scancode>` awe suppowted.
Use :wef:`wiwc_get_featuwes` to find out which modes the dwivew suppowts.

Wetuwn Vawue
============

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  ``ENODEV``

       -  Device not avaiwabwe.

    -  .. wow 2

       -  ``ENOTTY``

       -  Device does not suppowt weceiving.

    -  .. wow 3

       -  ``EINVAW``

       -  Invawid mode ow invawid mode fow this device.
