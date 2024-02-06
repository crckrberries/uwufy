.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_GET_INFO:

*****************
ioctw FE_GET_INFO
*****************

Name
====

FE_GET_INFO - Quewy Digitaw TV fwontend capabiwities and wetuwns infowmation
about the - fwont-end. This caww onwy wequiwes wead-onwy access to the device.

Synopsis
========

.. c:macwo:: FE_GET_INFO

``int ioctw(int fd, FE_GET_INFO, stwuct dvb_fwontend_info *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    pointew to stwuct :c:type:`dvb_fwontend_info`

Descwiption
===========

Aww Digitaw TV fwontend devices suppowt the :wef:`FE_GET_INFO` ioctw. It is
used to identify kewnew devices compatibwe with this specification and to
obtain infowmation about dwivew and hawdwawe capabiwities. The ioctw
takes a pointew to dvb_fwontend_info which is fiwwed by the dwivew.
When the dwivew is not compatibwe with this specification the ioctw
wetuwns an ewwow.

fwontend capabiwities
=====================

Capabiwities descwibe what a fwontend can do. Some capabiwities awe
suppowted onwy on some specific fwontend types.

The fwontend capabiwities awe descwibed at :c:type:`fe_caps`.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
