.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_set_send_cawwiew:

***************************
ioctw WIWC_SET_SEND_CAWWIEW
***************************

Name
====

WIWC_SET_SEND_CAWWIEW - Set send cawwiew used to moduwate IW TX.

Synopsis
========

.. c:macwo:: WIWC_SET_SEND_CAWWIEW

``int ioctw(int fd, WIWC_SET_SEND_CAWWIEW, __u32 *fwequency)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``fwequency``
    Fwequency of the cawwiew to be moduwated, in Hz.

Descwiption
===========

Set send cawwiew used to moduwate IW PWM puwses and spaces.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
