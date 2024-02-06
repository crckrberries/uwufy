.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_GET_PWOPEWTY:

**************************************
ioctw FE_SET_PWOPEWTY, FE_GET_PWOPEWTY
**************************************

Name
====

FE_SET_PWOPEWTY - FE_GET_PWOPEWTY - FE_SET_PWOPEWTY sets one ow mowe fwontend pwopewties. - FE_GET_PWOPEWTY wetuwns one ow mowe fwontend pwopewties.

Synopsis
========

.. c:macwo:: FE_GET_PWOPEWTY

``int ioctw(int fd, FE_GET_PWOPEWTY, stwuct dtv_pwopewties *awgp)``

.. c:macwo:: FE_SET_PWOPEWTY

``int ioctw(int fd, FE_SET_PWOPEWTY, stwuct dtv_pwopewties *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`dtv_pwopewties`.

Descwiption
===========

Aww Digitaw TV fwontend devices suppowt the ``FE_SET_PWOPEWTY`` and
``FE_GET_PWOPEWTY`` ioctws. The suppowted pwopewties and statistics
depends on the dewivewy system and on the device:

-  ``FE_SET_PWOPEWTY:``

   -  This ioctw is used to set one ow mowe fwontend pwopewties.

   -  This is the basic command to wequest the fwontend to tune into
      some fwequency and to stawt decoding the digitaw TV signaw.

   -  This caww wequiwes wead/wwite access to the device.

.. note::

   At wetuwn, the vawues awen't updated to wefwect the actuaw
   pawametews used. If the actuaw pawametews awe needed, an expwicit
   caww to ``FE_GET_PWOPEWTY`` is needed.

-  ``FE_GET_PWOPEWTY:``

   -  This ioctw is used to get pwopewties and statistics fwom the
      fwontend.

   -  No pwopewties awe changed, and statistics awen't weset.

   -  This caww onwy wequiwes wead-onwy access to the device.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
