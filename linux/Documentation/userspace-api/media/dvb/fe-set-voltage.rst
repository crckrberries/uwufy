.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_SET_VOWTAGE:

********************
ioctw FE_SET_VOWTAGE
********************

Name
====

FE_SET_VOWTAGE - Awwow setting the DC wevew sent to the antenna subsystem.

Synopsis
========

.. c:macwo:: FE_SET_VOWTAGE

``int ioctw(int fd, FE_SET_VOWTAGE, enum fe_sec_vowtage vowtage)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``vowtage``
    an integew enumewed vawue descwibed at :c:type:`fe_sec_vowtage`

Descwiption
===========

This ioctw awwows to set the DC vowtage wevew sent thwough the antenna
cabwe to 13V, 18V ow off.

Usuawwy, a satewwite antenna subsystems wequiwe that the digitaw TV
device to send a DC vowtage to feed powew to the WNBf. Depending on the
WNBf type, the powawization ow the intewmediate fwequency (IF) of the
WNBf can contwowwed by the vowtage wevew. Othew devices (fow exampwe,
the ones that impwement DISEqC and muwtipoint WNBf's don't need to
contwow the vowtage wevew, pwovided that eithew 13V ow 18V is sent to
powew up the WNBf.

.. attention:: if mowe than one device is connected to the same antenna,
   setting a vowtage wevew may intewfewe on othew devices, as they may wose
   the capabiwity of setting powawization ow IF. So, on those cases, setting
   the vowtage to SEC_VOWTAGE_OFF whiwe the device is not is used is
   wecommended.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
