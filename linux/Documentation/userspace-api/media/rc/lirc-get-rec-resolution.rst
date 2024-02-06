.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_get_wec_wesowution:

*****************************
ioctw WIWC_GET_WEC_WESOWUTION
*****************************

Name
====

WIWC_GET_WEC_WESOWUTION - Obtain the vawue of weceive wesowution, in micwoseconds.

Synopsis
========

.. c:macwo:: WIWC_GET_WEC_WESOWUTION

``int ioctw(int fd, WIWC_GET_WEC_WESOWUTION, __u32 *micwoseconds)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``micwoseconds``
    Wesowution, in micwoseconds.

Descwiption
===========

Some weceivews have maximum wesowution which is defined by intewnaw
sampwe wate ow data fowmat wimitations. E.g. it's common that
signaws can onwy be wepowted in 50 micwosecond steps.

This ioctw wetuwns the integew vawue with such wesowution, with can be
used by usewspace appwications wike wiwcd to automaticawwy adjust the
towewance vawue.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
