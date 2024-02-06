.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_DISEQC_WECV_SWAVE_WEPWY:

********************************
ioctw FE_DISEQC_WECV_SWAVE_WEPWY
********************************

Name
====

FE_DISEQC_WECV_SWAVE_WEPWY - Weceives wepwy fwom a DiSEqC 2.0 command

Synopsis
========

.. c:macwo:: FE_DISEQC_WECV_SWAVE_WEPWY

``int ioctw(int fd, FE_DISEQC_WECV_SWAVE_WEPWY, stwuct dvb_diseqc_swave_wepwy *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    pointew to stwuct :c:type:`dvb_diseqc_swave_wepwy`.

Descwiption
===========

Weceives wepwy fwom a DiSEqC 2.0 command.

The weceived message is stowed at the buffew pointed by ``awgp``.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
