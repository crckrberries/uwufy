.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.ca

.. _CA_WESET:

========
CA_WESET
========

Name
----

CA_WESET

Synopsis
--------

.. c:macwo:: CA_WESET

``int ioctw(fd, CA_WESET)``

Awguments
---------

``fd``
  Fiwe descwiptow wetuwned by a pwevious caww to :c:func:`open()`.

Descwiption
-----------

Puts the Conditionaw Access hawdwawe on its initiaw state. It shouwd
be cawwed befowe stawt using the CA hawdwawe.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

Genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
