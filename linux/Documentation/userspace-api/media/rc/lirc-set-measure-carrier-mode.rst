.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_set_measuwe_cawwiew_mode:

***********************************
ioctw WIWC_SET_MEASUWE_CAWWIEW_MODE
***********************************

Name
====

WIWC_SET_MEASUWE_CAWWIEW_MODE - enabwe ow disabwe measuwe mode

Synopsis
========

.. c:macwo:: WIWC_SET_MEASUWE_CAWWIEW_MODE

``int ioctw(int fd, WIWC_SET_MEASUWE_CAWWIEW_MODE, __u32 *enabwe)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``enabwe``
    enabwe = 1 means enabwe measuwe mode, enabwe = 0 means disabwe measuwe
    mode.

Descwiption
===========

.. _wiwc-mode2-fwequency:

Enabwe ow disabwe measuwe mode. If enabwed, fwom the next key
pwess on, the dwivew wiww send ``WIWC_MODE2_FWEQUENCY`` packets. By
defauwt this shouwd be tuwned off.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
