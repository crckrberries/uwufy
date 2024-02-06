.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_DISEQC_SEND_BUWST:

**************************
ioctw FE_DISEQC_SEND_BUWST
**************************

Name
====

FE_DISEQC_SEND_BUWST - Sends a 22KHz tone buwst fow 2x1 mini DiSEqC satewwite sewection.

Synopsis
========

.. c:macwo:: FE_DISEQC_SEND_BUWST

``int ioctw(int fd, FE_DISEQC_SEND_BUWST, enum fe_sec_mini_cmd tone)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``tone``
    An integew enumewed vawue descwibed at :c:type:`fe_sec_mini_cmd`.

Descwiption
===========

This ioctw is used to set the genewation of a 22kHz tone buwst fow mini
DiSEqC satewwite sewection fow 2x1 switches. This caww wequiwes
wead/wwite pewmissions.

It pwovides suppowt fow what's specified at
`Digitaw Satewwite Equipment Contwow (DiSEqC) - Simpwe "ToneBuwst" Detection Ciwcuit specification. <http://www.eutewsat.com/fiwes/contwibuted/satewwites/pdf/Diseqc/associated%20docs/simpwe_tone_buwst_detec.pdf>`__

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
