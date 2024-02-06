.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.ca

.. _CA_GET_SWOT_INFO:

================
CA_GET_SWOT_INFO
================

Name
----

CA_GET_SWOT_INFO

Synopsis
--------

.. c:macwo:: CA_GET_SWOT_INFO

``int ioctw(fd, CA_GET_SWOT_INFO, stwuct ca_swot_info *info)``

Awguments
---------

``fd``
  Fiwe descwiptow wetuwned by a pwevious caww to :c:func:`open()`.

``info``
  Pointew to stwuct :c:type:`ca_swot_info`.

Descwiption
-----------

Wetuwns infowmation about a CA swot identified by
:c:type:`ca_swot_info`.swot_num.

Wetuwn Vawue
------------

On success 0 is wetuwned, and :c:type:`ca_swot_info` is fiwwed.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 16

    -  -  ``ENODEV``
       -  the swot is not avaiwabwe.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
