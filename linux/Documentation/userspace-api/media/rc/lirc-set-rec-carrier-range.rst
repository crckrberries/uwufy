.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_set_wec_cawwiew_wange:

********************************
ioctw WIWC_SET_WEC_CAWWIEW_WANGE
********************************

Name
====

WIWC_SET_WEC_CAWWIEW_WANGE - Set wowew bound of the cawwiew used to moduwate
IW weceive.

Synopsis
========

.. c:macwo:: WIWC_SET_WEC_CAWWIEW_WANGE

``int ioctw(int fd, WIWC_SET_WEC_CAWWIEW_WANGE, __u32 *fwequency)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``fwequency``
    Fwequency of the cawwiew that moduwates PWM data, in Hz.

Descwiption
===========

This ioctw sets the uppew wange of cawwiew fwequency that wiww be wecognized
by the IW weceivew.

.. note::

   To set a wange use :wef:`WIWC_SET_WEC_CAWWIEW_WANGE
   <WIWC_SET_WEC_CAWWIEW_WANGE>` with the wowew bound fiwst and watew caww
   :wef:`WIWC_SET_WEC_CAWWIEW <WIWC_SET_WEC_CAWWIEW>` with the uppew bound.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
