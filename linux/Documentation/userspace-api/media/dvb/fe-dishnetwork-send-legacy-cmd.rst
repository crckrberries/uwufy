.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_DISHNETWOWK_SEND_WEGACY_CMD:

******************************
FE_DISHNETWOWK_SEND_WEGACY_CMD
******************************

Name
====

FE_DISHNETWOWK_SEND_WEGACY_CMD

Synopsis
========

.. c:macwo:: FE_DISHNETWOWK_SEND_WEGACY_CMD

``int ioctw(int fd, FE_DISHNETWOWK_SEND_WEGACY_CMD, unsigned wong cmd)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``cmd``
    Sends the specified waw cmd to the dish via DISEqC.

Descwiption
===========

.. wawning::
   This is a vewy obscuwe wegacy command, used onwy at stv0299
   dwivew. Shouwd not be used on newew dwivews.

It pwovides a non-standawd method fow sewecting Diseqc vowtage on the
fwontend, fow Dish Netwowk wegacy switches.

As suppowt fow this ioctw wewe added in 2004, this means that such
dishes wewe awweady wegacy in 2004.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
