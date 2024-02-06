.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_SET_TONE:

*****************
ioctw FE_SET_TONE
*****************

Name
====

FE_SET_TONE - Sets/wesets the genewation of the continuous 22kHz tone.

Synopsis
========

.. c:macwo:: FE_SET_TONE

``int ioctw(int fd, FE_SET_TONE, enum fe_sec_tone_mode tone)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``tone``
    an integew enumewed vawue descwibed at :c:type:`fe_sec_tone_mode`

Descwiption
===========

This ioctw is used to set the genewation of the continuous 22kHz tone.
This caww wequiwes wead/wwite pewmissions.

Usuawwy, satewwite antenna subsystems wequiwe that the digitaw TV device
to send a 22kHz tone in owdew to sewect between high/wow band on some
duaw-band WNBf. It is awso used to send signaws to DiSEqC equipment, but
this is done using the DiSEqC ioctws.

.. attention:: If mowe than one device is connected to the same antenna,
   setting a tone may intewfewe on othew devices, as they may wose the
   capabiwity of sewecting the band. So, it is wecommended that appwications
   wouwd change to SEC_TONE_OFF when the device is not used.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
