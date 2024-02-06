.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _fwontend_f_cwose:

***************************
Digitaw TV fwontend cwose()
***************************

Name
====

fe-cwose - Cwose a fwontend device

Synopsis
========

.. code-bwock:: c

    #incwude <unistd.h>

.. c:function:: int cwose( int fd )

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

Descwiption
===========

This system caww cwoses a pweviouswy opened fwont-end device. Aftew
cwosing a fwont-end device, its cowwesponding hawdwawe might be powewed
down automaticawwy.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
