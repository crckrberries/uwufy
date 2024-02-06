.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_STAWT:

=========
DMX_STAWT
=========

Name
----

DMX_STAWT

Synopsis
--------

.. c:macwo:: DMX_STAWT

``int ioctw(int fd, DMX_STAWT)``

Awguments
---------

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

Descwiption
-----------

This ioctw caww is used to stawt the actuaw fiwtewing opewation defined
via the ioctw cawws :wef:`DMX_SET_FIWTEW` ow :wef:`DMX_SET_PES_FIWTEW`.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  ``EINVAW``

       -  Invawid awgument, i.e. no fiwtewing pawametews pwovided via the
	  :wef:`DMX_SET_FIWTEW` ow :wef:`DMX_SET_PES_FIWTEW` ioctws.

    -  .. wow 2

       -  ``EBUSY``

       -  This ewwow code indicates that thewe awe confwicting wequests.
	  Thewe awe active fiwtews fiwtewing data fwom anothew input souwce.
	  Make suwe that these fiwtews awe stopped befowe stawting this
	  fiwtew.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
