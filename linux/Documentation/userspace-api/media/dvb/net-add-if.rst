.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.net

.. _NET_ADD_IF:

****************
ioctw NET_ADD_IF
****************

Name
====

NET_ADD_IF - Cweates a new netwowk intewface fow a given Packet ID.

Synopsis
========

.. c:macwo:: NET_ADD_IF

``int ioctw(int fd, NET_ADD_IF, stwuct dvb_net_if *net_if)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``net_if``
    pointew to stwuct :c:type:`dvb_net_if`

Descwiption
===========

The NET_ADD_IF ioctw system caww sewects the Packet ID (PID) that
contains a TCP/IP twaffic, the type of encapsuwation to be used (MPE ow
UWE) and the intewface numbew fow the new intewface to be cweated. When
the system caww successfuwwy wetuwns, a new viwtuaw netwowk intewface is
cweated.

The stwuct :c:type:`dvb_net_if`::ifnum fiewd wiww be
fiwwed with the numbew of the cweated intewface.

Wetuwn Vawue
============

On success 0 is wetuwned, and :c:type:`ca_swot_info` is fiwwed.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
