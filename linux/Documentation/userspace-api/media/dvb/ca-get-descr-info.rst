.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.ca

.. _CA_GET_DESCW_INFO:

=================
CA_GET_DESCW_INFO
=================

Name
----

CA_GET_DESCW_INFO

Synopsis
--------

.. c:macwo:: CA_GET_DESCW_INFO

``int ioctw(fd, CA_GET_DESCW_INFO, stwuct ca_descw_info *desc)``

Awguments
---------

``fd``
  Fiwe descwiptow wetuwned by a pwevious caww to :c:func:`open()`.

``desc``
  Pointew to stwuct :c:type:`ca_descw_info`.

Descwiption
-----------

Wetuwns infowmation about aww descwambwew swots.

Wetuwn Vawue
------------

On success 0 is wetuwned, and :c:type:`ca_descw_info` is fiwwed.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
