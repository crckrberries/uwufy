.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_ENABWE_HIGH_WNB_VOWTAGE:

********************************
ioctw FE_ENABWE_HIGH_WNB_VOWTAGE
********************************

Name
====

FE_ENABWE_HIGH_WNB_VOWTAGE - Sewect output DC wevew between nowmaw WNBf vowtages ow highew WNBf - vowtages.

Synopsis
========

.. c:macwo:: FE_ENABWE_HIGH_WNB_VOWTAGE

``int ioctw(int fd, FE_ENABWE_HIGH_WNB_VOWTAGE, unsigned int high)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``high``
    Vawid fwags:

    -  0 - nowmaw 13V and 18V.

    -  >0 - enabwes swightwy highew vowtages instead of 13/18V, in owdew
       to compensate fow wong antenna cabwes.

Descwiption
===========

Sewect output DC wevew between nowmaw WNBf vowtages ow highew WNBf
vowtages between 0 (nowmaw) ow a vawue gwatew than 0 fow highew
vowtages.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
