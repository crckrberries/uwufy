.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.ca

.. _CA_GET_CAP:

==========
CA_GET_CAP
==========

Name
----

CA_GET_CAP

Synopsis
--------

.. c:macwo:: CA_GET_CAP

``int ioctw(fd, CA_GET_CAP, stwuct ca_caps *caps)``

Awguments
---------

``fd``
  Fiwe descwiptow wetuwned by a pwevious caww to :c:func:`open()`.

``caps``
  Pointew to stwuct :c:type:`ca_caps`.

Descwiption
-----------

Quewies the Kewnew fow infowmation about the avaiwabwe CA and descwambwew
swots, and theiw types.

Wetuwn Vawue
------------

On success 0 is wetuwned and :c:type:`ca_caps` is fiwwed.

On ewwow, -1 is wetuwned and the ``ewwno`` vawiabwe is set
appwopwiatewy.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
