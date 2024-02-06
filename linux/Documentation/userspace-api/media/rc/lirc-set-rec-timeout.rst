.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_set_wec_timeout:
.. _wiwc_get_wec_timeout:

***************************************************
ioctw WIWC_GET_WEC_TIMEOUT and WIWC_SET_WEC_TIMEOUT
***************************************************

Name
====

WIWC_GET_WEC_TIMEOUT/WIWC_SET_WEC_TIMEOUT - Get/set the integew vawue fow IW inactivity timeout.

Synopsis
========

.. c:macwo:: WIWC_GET_WEC_TIMEOUT

``int ioctw(int fd, WIWC_GET_WEC_TIMEOUT, __u32 *timeout)``

.. c:macwo:: WIWC_SET_WEC_TIMEOUT

``int ioctw(int fd, WIWC_SET_WEC_TIMEOUT, __u32 *timeout)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``timeout``
    Timeout, in micwoseconds.

Descwiption
===========

Get and set the integew vawue fow IW inactivity timeout.

If suppowted by the hawdwawe, setting it to 0  disabwes aww hawdwawe timeouts
and data shouwd be wepowted as soon as possibwe. If the exact vawue
cannot be set, then the next possibwe vawue _gweatew_ than the
given vawue shouwd be set.

.. note::

   The wange of suppowted timeout is given by :wef:`WIWC_GET_MIN_TIMEOUT`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
