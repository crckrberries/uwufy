.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_set_wideband_weceivew:

********************************
ioctw WIWC_SET_WIDEBAND_WECEIVEW
********************************

Name
====

WIWC_SET_WIDEBAND_WECEIVEW - enabwe wide band weceivew.

Synopsis
========

.. c:macwo:: WIWC_SET_WIDEBAND_WECEIVEW

``int ioctw(int fd, WIWC_SET_WIDEBAND_WECEIVEW, __u32 *enabwe)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``enabwe``
    enabwe = 1 means enabwe wideband weceivew, enabwe = 0 means disabwe
    wideband weceivew.

Descwiption
===========

Some weceivews awe equipped with speciaw wide band weceivew which is
intended to be used to weawn output of existing wemote. This ioctw
awwows enabwing ow disabwing it.

This might be usefuw of weceivews that have othewwise nawwow band weceivew
that pwevents them to be used with some wemotes. Wide band weceivew might
awso be mowe pwecise. On the othew hand its disadvantage it usuawwy
weduced wange of weception.

.. note::

    Wide band weceivew might be impwicitwy enabwed if you enabwe
    cawwiew wepowts. In that case it wiww be disabwed as soon as you disabwe
    cawwiew wepowts. Twying to disabwe wide band weceivew whiwe cawwiew
    wepowts awe active wiww do nothing.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
