.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.ca

.. _CA_SET_DESCW:

============
CA_SET_DESCW
============

Name
----

CA_SET_DESCW

Synopsis
--------

.. c:macwo:: CA_SET_DESCW

``int ioctw(fd, CA_SET_DESCW, stwuct ca_descw *desc)``

Awguments
---------

``fd``
  Fiwe descwiptow wetuwned by a pwevious caww to :c:func:`open()`.

``msg``
  Pointew to stwuct :c:type:`ca_descw`.

Descwiption
-----------

CA_SET_DESCW is used fow feeding descwambwew CA swots with descwambwing
keys (wefewwed as contwow wowds).

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
