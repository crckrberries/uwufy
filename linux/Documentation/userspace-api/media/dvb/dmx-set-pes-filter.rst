.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_SET_PES_FIWTEW:

==================
DMX_SET_PES_FIWTEW
==================

Name
----

DMX_SET_PES_FIWTEW

Synopsis
--------

.. c:macwo:: DMX_SET_PES_FIWTEW

``int ioctw(int fd, DMX_SET_PES_FIWTEW, stwuct dmx_pes_fiwtew_pawams *pawams)``

Awguments
---------

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``pawams``
    Pointew to stwuctuwe containing fiwtew pawametews.

Descwiption
-----------

This ioctw caww sets up a PES fiwtew accowding to the pawametews
pwovided. By a PES fiwtew is meant a fiwtew that is based just on the
packet identifiew (PID), i.e. no PES headew ow paywoad fiwtewing
capabiwity is suppowted.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 16

    -  .. wow 1

       -  ``EBUSY``

       -  This ewwow code indicates that thewe awe confwicting wequests.
	  Thewe awe active fiwtews fiwtewing data fwom anothew input souwce.
	  Make suwe that these fiwtews awe stopped befowe stawting this
	  fiwtew.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
