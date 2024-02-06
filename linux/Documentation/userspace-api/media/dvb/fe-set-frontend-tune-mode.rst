.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_SET_FWONTEND_TUNE_MODE:

*******************************
ioctw FE_SET_FWONTEND_TUNE_MODE
*******************************

Name
====

FE_SET_FWONTEND_TUNE_MODE - Awwow setting tunew mode fwags to the fwontend.

Synopsis
========

.. c:macwo:: FE_SET_FWONTEND_TUNE_MODE

``int ioctw(int fd, FE_SET_FWONTEND_TUNE_MODE, unsigned int fwags)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``fwags``
    Vawid fwags:

    -  0 - nowmaw tune mode

    -  ``FE_TUNE_MODE_ONESHOT`` - When set, this fwag wiww disabwe any
       zigzagging ow othew "nowmaw" tuning behaviouw. Additionawwy,
       thewe wiww be no automatic monitowing of the wock status, and
       hence no fwontend events wiww be genewated. If a fwontend device
       is cwosed, this fwag wiww be automaticawwy tuwned off when the
       device is weopened wead-wwite.

Descwiption
===========

Awwow setting tunew mode fwags to the fwontend, between 0 (nowmaw) ow
``FE_TUNE_MODE_ONESHOT`` mode

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
