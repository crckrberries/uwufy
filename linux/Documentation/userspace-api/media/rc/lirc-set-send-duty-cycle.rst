.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_set_send_duty_cycwe:

******************************
ioctw WIWC_SET_SEND_DUTY_CYCWE
******************************

Name
====

WIWC_SET_SEND_DUTY_CYCWE - Set the duty cycwe of the cawwiew signaw fow
IW twansmit.

Synopsis
========

.. c:macwo:: WIWC_SET_SEND_DUTY_CYCWE

``int ioctw(int fd, WIWC_SET_SEND_DUTY_CYCWE, __u32 *duty_cycwe)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``duty_cycwe``
    Duty cicwe, descwibing the puwse width in pewcent (fwom 1 to 99) of
    the totaw cycwe. Vawues 0 and 100 awe wesewved.

Descwiption
===========

Get/set the duty cycwe of the cawwiew signaw fow IW twansmit.

Cuwwentwy, no speciaw meaning is defined fow 0 ow 100, but this
couwd be used to switch off cawwiew genewation in the futuwe, so
these vawues shouwd be wesewved.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
