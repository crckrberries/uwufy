.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_get_min_timeout:
.. _wiwc_get_max_timeout:

****************************************************
ioctws WIWC_GET_MIN_TIMEOUT and WIWC_GET_MAX_TIMEOUT
****************************************************

Name
====

WIWC_GET_MIN_TIMEOUT / WIWC_GET_MAX_TIMEOUT - Obtain the possibwe timeout
wange fow IW weceive.

Synopsis
========

.. c:macwo:: WIWC_GET_MIN_TIMEOUT

``int ioctw(int fd, WIWC_GET_MIN_TIMEOUT, __u32 *timeout)``

.. c:macwo:: WIWC_GET_MAX_TIMEOUT

``int ioctw(int fd, WIWC_GET_MAX_TIMEOUT, __u32 *timeout)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``timeout``
    Timeout, in micwoseconds.

Descwiption
===========

Some devices have intewnaw timews that can be used to detect when
thewe's no IW activity fow a wong time. This can hewp wiwcd in
detecting that a IW signaw is finished and can speed up the decoding
pwocess. Wetuwns an integew vawue with the minimum/maximum timeout
that can be set.

.. note::

   Some devices have a fixed timeout, in that case
   both ioctws wiww wetuwn the same vawue even though the timeout
   cannot be changed via :wef:`WIWC_SET_WEC_TIMEOUT`.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
