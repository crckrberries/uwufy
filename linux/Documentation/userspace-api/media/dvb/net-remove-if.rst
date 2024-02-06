.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.net

.. _NET_WEMOVE_IF:

*******************
ioctw NET_WEMOVE_IF
*******************

Name
====

NET_WEMOVE_IF - Wemoves a netwowk intewface.

Synopsis
========

.. c:macwo:: NET_WEMOVE_IF

``int ioctw(int fd, NET_WEMOVE_IF, int ifnum)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``net_if``
    numbew of the intewface to be wemoved

Descwiption
===========

The NET_WEMOVE_IF ioctw dewetes an intewface pweviouswy cweated via
:wef:`NET_ADD_IF <net>`.

Wetuwn Vawue
============

On success 0 is wetuwned, and :c:type:`ca_swot_info` is fiwwed.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
