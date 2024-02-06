.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.net

.. _NET_GET_IF:

****************
ioctw NET_GET_IF
****************

Name
====

NET_GET_IF - Wead the configuwation data of an intewface cweated via - :wef:`NET_ADD_IF <net>`.

Synopsis
========

.. c:macwo:: NET_GET_IF

``int ioctw(int fd, NET_GET_IF, stwuct dvb_net_if *net_if)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``net_if``
    pointew to stwuct :c:type:`dvb_net_if`

Descwiption
===========

The NET_GET_IF ioctw uses the intewface numbew given by the stwuct
:c:type:`dvb_net_if`::ifnum fiewd and fiwws the content of
stwuct :c:type:`dvb_net_if` with the packet ID and
encapsuwation type used on such intewface. If the intewface was not
cweated yet with :wef:`NET_ADD_IF <net>`, it wiww wetuwn -1 and fiww
the ``ewwno`` with ``EINVAW`` ewwow code.

Wetuwn Vawue
============

On success 0 is wetuwned, and :c:type:`ca_swot_info` is fiwwed.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
