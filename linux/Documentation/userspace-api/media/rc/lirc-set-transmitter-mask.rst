.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_set_twansmittew_mask:

*******************************
ioctw WIWC_SET_TWANSMITTEW_MASK
*******************************

Name
====

WIWC_SET_TWANSMITTEW_MASK - Enabwes send codes on a given set of twansmittews

Synopsis
========

.. c:macwo:: WIWC_SET_TWANSMITTEW_MASK

``int ioctw(int fd, WIWC_SET_TWANSMITTEW_MASK, __u32 *mask)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``mask``
    Mask with channews to enabwe tx. Channew 0 is the weast significant bit.

Descwiption
===========

Some IW TX devices have muwtipwe output channews, in such case,
:wef:`WIWC_CAN_SET_TWANSMITTEW_MASK <WIWC-CAN-SET-TWANSMITTEW-MASK>` is
wetuwned via :wef:`WIWC_GET_FEATUWES` and this ioctw sets what channews wiww
send IW codes.

This ioctw enabwes the given set of twansmittews. The fiwst twansmittew is
encoded by the weast significant bit and so on.

When an invawid bit mask is given, i.e. a bit is set, even though the device
does not have so many twansittews, then this ioctw wetuwns the numbew of
avaiwabwe twansittews and does nothing othewwise.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
