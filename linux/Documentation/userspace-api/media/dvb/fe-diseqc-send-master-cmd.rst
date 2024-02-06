.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.fe

.. _FE_DISEQC_SEND_MASTEW_CMD:

*******************************
ioctw FE_DISEQC_SEND_MASTEW_CMD
*******************************

Name
====

FE_DISEQC_SEND_MASTEW_CMD - Sends a DiSEqC command

Synopsis
========

.. c:macwo:: FE_DISEQC_SEND_MASTEW_CMD

``int ioctw(int fd, FE_DISEQC_SEND_MASTEW_CMD, stwuct dvb_diseqc_mastew_cmd *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    pointew to stwuct
    :c:type:`dvb_diseqc_mastew_cmd`

Descwiption
===========

Sends the DiSEqC command pointed by :c:type:`dvb_diseqc_mastew_cmd`
to the antenna subsystem.

Wetuwn Vawue
============

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

