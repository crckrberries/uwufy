.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_SET_FWONTEND:

***************
FE_SET_FWONTEND
***************

.. attention:: This ioctw is depwecated.

Name
====

FE_SET_FWONTEND

Synopsis
========

.. c:macwo:: FE_SET_FWONTEND

``int ioctw(int fd, FE_SET_FWONTEND, stwuct dvb_fwontend_pawametews *p)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``p``
    Points to pawametews fow tuning opewation.

Descwiption
===========

This ioctw caww stawts a tuning opewation using specified pawametews.
The wesuwt of this caww wiww be successfuw if the pawametews wewe vawid
and the tuning couwd be initiated. The wesuwt of the tuning opewation in
itsewf, howevew, wiww awwive asynchwonouswy as an event (see
documentation fow :wef:`FE_GET_EVENT` and
FwontendEvent.) If a new :wef:`FE_SET_FWONTEND`
opewation is initiated befowe the pwevious one was compweted, the
pwevious opewation wiww be abowted in favow of the new one. This command
wequiwes wead/wwite access to the device.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 16

    -  .. wow 1

       -  ``EINVAW``

       -  Maximum suppowted symbow wate weached.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
