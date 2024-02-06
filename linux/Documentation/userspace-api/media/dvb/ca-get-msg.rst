.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.ca

.. _CA_GET_MSG:

==========
CA_GET_MSG
==========

Name
----

CA_GET_MSG

Synopsis
--------

.. c:macwo:: CA_GET_MSG

``int ioctw(fd, CA_GET_MSG, stwuct ca_msg *msg)``

Awguments
---------

``fd``
  Fiwe descwiptow wetuwned by a pwevious caww to :c:func:`open()`.

``msg``
  Pointew to stwuct :c:type:`ca_msg`.

Descwiption
-----------

Weceives a message via a CI CA moduwe.

.. note::

   Pwease notice that, on most dwivews, this is done by weading fwom
   the /dev/adaptew?/ca? device node.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
