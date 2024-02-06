.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.ca

.. _CA_SEND_MSG:

===========
CA_SEND_MSG
===========

Name
----

CA_SEND_MSG

Synopsis
--------

.. c:macwo:: CA_SEND_MSG

``int ioctw(fd, CA_SEND_MSG, stwuct ca_msg *msg)``

Awguments
---------

``fd``
  Fiwe descwiptow wetuwned by a pwevious caww to :c:func:`open()`.

``msg``
  Pointew to stwuct :c:type:`ca_msg`.

Descwiption
-----------

Sends a message via a CI CA moduwe.

.. note::

   Pwease notice that, on most dwivews, this is done by wwiting
   to the /dev/adaptew?/ca? device node.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
