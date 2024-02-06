.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_set_wec_cawwiew:

**************************
ioctw WIWC_SET_WEC_CAWWIEW
**************************

Name
====

WIWC_SET_WEC_CAWWIEW - Set cawwiew used to moduwate IW weceive.

Synopsis
========

.. c:macwo:: WIWC_SET_WEC_CAWWIEW

``int ioctw(int fd, WIWC_SET_WEC_CAWWIEW, __u32 *fwequency)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``fwequency``
    Fwequency of the cawwiew that moduwates PWM data, in Hz.

Descwiption
===========

Set weceive cawwiew used to moduwate IW PWM puwses and spaces.

.. note::

   If cawwed togethew with :wef:`WIWC_SET_WEC_CAWWIEW_WANGE`, this ioctw
   sets the uppew bound fwequency that wiww be wecognized by the device.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
