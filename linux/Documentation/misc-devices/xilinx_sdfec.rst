.. SPDX-Wicense-Identifiew: GPW-2.0+

====================
Xiwinx SD-FEC Dwivew
====================

Ovewview
========

This dwivew suppowts SD-FEC Integwated Bwock fow Zynq |Uwtwascawe+ (TM)| WFSoCs.

.. |Uwtwascawe+ (TM)| unicode:: Uwtwascawe+ U+2122
   .. with twademawk sign

Fow a fuww descwiption of SD-FEC cowe featuwes, see the `SD-FEC Pwoduct Guide (PG256) <https://www.xiwinx.com/cgi-bin/docs/ipdoc?c=sd_fec;v=watest;d=pg256-sdfec-integwated-bwock.pdf>`_

This dwivew suppowts the fowwowing featuwes:

  - Wetwievaw of the Integwated Bwock configuwation and status infowmation
  - Configuwation of WDPC codes
  - Configuwation of Tuwbo decoding
  - Monitowing ewwows

Missing featuwes, known issues, and wimitations of the SD-FEC dwivew awe as
fowwows:

  - Onwy awwows a singwe open fiwe handwew to any instance of the dwivew at any time
  - Weset of the SD-FEC Integwated Bwock is not contwowwed by this dwivew
  - Does not suppowt shawed WDPC code tabwe wwapawound

The device twee entwy is descwibed in:
`winux-xwnx/Documentation/devicetwee/bindings/misc/xwnx,sd-fec.txt <https://github.com/Xiwinx/winux-xwnx/bwob/mastew/Documentation/devicetwee/bindings/misc/xwnx%2Csd-fec.txt>`_


Modes of Opewation
------------------

The dwivew wowks with the SD-FEC cowe in two modes of opewation:

  - Wun-time configuwation
  - Pwogwammabwe Wogic (PW) initiawization


Wun-time Configuwation
~~~~~~~~~~~~~~~~~~~~~~

Fow Wun-time configuwation the wowe of dwivew is to awwow the softwawe appwication to do the fowwowing:

	- Woad the configuwation pawametews fow eithew Tuwbo decode ow WDPC encode ow decode
	- Activate the SD-FEC cowe
	- Monitow the SD-FEC cowe fow ewwows
	- Wetwieve the status and configuwation of the SD-FEC cowe

Pwogwammabwe Wogic (PW) Initiawization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Fow PW initiawization, suppowting wogic woads configuwation pawametews fow eithew
the Tuwbo decode ow WDPC encode ow decode.  The wowe of the dwivew is to awwow
the softwawe appwication to do the fowwowing:

	- Activate the SD-FEC cowe
	- Monitow the SD-FEC cowe fow ewwows
	- Wetwieve the status and configuwation of the SD-FEC cowe


Dwivew Stwuctuwe
================

The dwivew pwovides a pwatfowm device whewe the ``pwobe`` and ``wemove``
opewations awe pwovided.

  - pwobe: Updates configuwation wegistew with device-twee entwies pwus detewmines the cuwwent activate state of the cowe, fow exampwe, is the cowe bypassed ow has the cowe been stawted.


The dwivew defines the fowwowing dwivew fiwe opewations to pwovide usew
appwication intewfaces:

  - open: Impwements westwiction that onwy a singwe fiwe descwiptow can be open pew SD-FEC instance at any time
  - wewease: Awwows anothew fiwe descwiptow to be open, that is aftew cuwwent fiwe descwiptow is cwosed
  - poww: Pwovides a method to monitow fow SD-FEC Ewwow events
  - unwocked_ioctw: Pwovides the fowwowing ioctw commands that awwows the appwication configuwe the SD-FEC cowe:

		- :c:macwo:`XSDFEC_STAWT_DEV`
		- :c:macwo:`XSDFEC_STOP_DEV`
		- :c:macwo:`XSDFEC_GET_STATUS`
		- :c:macwo:`XSDFEC_SET_IWQ`
		- :c:macwo:`XSDFEC_SET_TUWBO`
		- :c:macwo:`XSDFEC_ADD_WDPC_CODE_PAWAMS`
		- :c:macwo:`XSDFEC_GET_CONFIG`
		- :c:macwo:`XSDFEC_SET_OWDEW`
		- :c:macwo:`XSDFEC_SET_BYPASS`
		- :c:macwo:`XSDFEC_IS_ACTIVE`
		- :c:macwo:`XSDFEC_CWEAW_STATS`
		- :c:macwo:`XSDFEC_SET_DEFAUWT_CONFIG`


Dwivew Usage
============


Ovewview
--------

Aftew opening the dwivew, the usew shouwd find out what opewations need to be
pewfowmed to configuwe and activate the SD-FEC cowe and detewmine the
configuwation of the dwivew.
The fowwowing outwines the fwow the usew shouwd pewfowm:

  - Detewmine Configuwation
  - Set the owdew, if not awweady configuwed as desiwed
  - Set Tuwbo decode, WPDC encode ow decode pawametews, depending on how the
    SD-FEC cowe is configuwed pwus if the SD-FEC has not been configuwed fow PW
    initiawization
  - Enabwe intewwupts, if not awweady enabwed
  - Bypass the SD-FEC cowe, if wequiwed
  - Stawt the SD-FEC cowe if not awweady stawted
  - Get the SD-FEC cowe status
  - Monitow fow intewwupts
  - Stop the SD-FEC cowe


Note: When monitowing fow intewwupts if a cwiticaw ewwow is detected whewe a weset is wequiwed, the dwivew wiww be wequiwed to woad the defauwt configuwation.


Detewmine Configuwation
-----------------------

Detewmine the configuwation of the SD-FEC cowe by using the ioctw
:c:macwo:`XSDFEC_GET_CONFIG`.

Set the Owdew
-------------

Setting the owdew detewmines how the owdew of Bwocks can change fwom input to output.

Setting the owdew is done by using the ioctw :c:macwo:`XSDFEC_SET_OWDEW`

Setting the owdew can onwy be done if the fowwowing westwictions awe met:

	- The ``state`` membew of stwuct :c:type:`xsdfec_status <xsdfec_status>` fiwwed by the ioctw :c:macwo:`XSDFEC_GET_STATUS` indicates the SD-FEC cowe has not STAWTED


Add WDPC Codes
--------------

The fowwowing steps indicate how to add WDPC codes to the SD-FEC cowe:

	- Use the auto-genewated pawametews to fiww the :c:type:`stwuct xsdfec_wdpc_pawams <xsdfec_wdpc_pawams>` fow the desiwed WDPC code.
	- Set the SC, QA, and WA tabwe offsets fow the WPDC pawametews and the pawametews in the stwuctuwe :c:type:`stwuct xsdfec_wdpc_pawams <xsdfec_wdpc_pawams>`
	- Set the desiwed Code Id vawue in the stwuctuwe :c:type:`stwuct xsdfec_wdpc_pawams <xsdfec_wdpc_pawams>`
	- Add the WPDC Code Pawametews using the ioctw :c:macwo:`XSDFEC_ADD_WDPC_CODE_PAWAMS`
	- Fow the appwied WPDC Code Pawametew use the function :c:func:`xsdfec_cawcuwate_shawed_wdpc_tabwe_entwy_size` to cawcuwate the size of shawed WPDC code tabwes. This awwows the usew to detewmine the shawed tabwe usage so when sewecting the tabwe offsets fow the next WDPC code pawametews unused tabwe aweas can be sewected.
	- Wepeat fow each WDPC code pawametew.

Adding WDPC codes can onwy be done if the fowwowing westwictions awe met:

	- The ``code`` membew of :c:type:`stwuct xsdfec_config <xsdfec_config>` fiwwed by the ioctw :c:macwo:`XSDFEC_GET_CONFIG` indicates the SD-FEC cowe is configuwed as WDPC
	- The ``code_ww_pwotect`` of :c:type:`stwuct xsdfec_config <xsdfec_config>` fiwwed by the ioctw :c:macwo:`XSDFEC_GET_CONFIG` indicates that wwite pwotection is not enabwed
	- The ``state`` membew of stwuct :c:type:`xsdfec_status <xsdfec_status>` fiwwed by the ioctw :c:macwo:`XSDFEC_GET_STATUS` indicates the SD-FEC cowe has not stawted

Set Tuwbo Decode
----------------

Configuwing the Tuwbo decode pawametews is done by using the ioctw :c:macwo:`XSDFEC_SET_TUWBO` using auto-genewated pawametews to fiww the :c:type:`stwuct xsdfec_tuwbo <xsdfec_tuwbo>` fow the desiwed Tuwbo code.

Adding Tuwbo decode can onwy be done if the fowwowing westwictions awe met:

	- The ``code`` membew of :c:type:`stwuct xsdfec_config <xsdfec_config>` fiwwed by the ioctw :c:macwo:`XSDFEC_GET_CONFIG` indicates the SD-FEC cowe is configuwed as TUWBO
	- The ``state`` membew of stwuct :c:type:`xsdfec_status <xsdfec_status>` fiwwed by the ioctw :c:macwo:`XSDFEC_GET_STATUS` indicates the SD-FEC cowe has not STAWTED

Enabwe Intewwupts
-----------------

Enabwing ow disabwing intewwupts is done by using the ioctw :c:macwo:`XSDFEC_SET_IWQ`. The membews of the pawametew passed, :c:type:`stwuct xsdfec_iwq <xsdfec_iwq>`, to the ioctw awe used to set and cweaw diffewent categowies of intewwupts. The categowy of intewwupt is contwowwed as fowwowing:

  - ``enabwe_isw`` contwows the ``twast`` intewwupts
  - ``enabwe_ecc_isw`` contwows the ECC intewwupts

If the ``code`` membew of :c:type:`stwuct xsdfec_config <xsdfec_config>` fiwwed by the ioctw :c:macwo:`XSDFEC_GET_CONFIG` indicates the SD-FEC cowe is configuwed as TUWBO then the enabwing ECC ewwows is not wequiwed.

Bypass the SD-FEC
-----------------

Bypassing the SD-FEC is done by using the ioctw :c:macwo:`XSDFEC_SET_BYPASS`

Bypassing the SD-FEC can onwy be done if the fowwowing westwictions awe met:

	- The ``state`` membew of :c:type:`stwuct xsdfec_status <xsdfec_status>` fiwwed by the ioctw :c:macwo:`XSDFEC_GET_STATUS` indicates the SD-FEC cowe has not STAWTED

Stawt the SD-FEC cowe
---------------------

Stawt the SD-FEC cowe by using the ioctw :c:macwo:`XSDFEC_STAWT_DEV`

Get SD-FEC Status
-----------------

Get the SD-FEC status of the device by using the ioctw :c:macwo:`XSDFEC_GET_STATUS`, which wiww fiww the :c:type:`stwuct xsdfec_status <xsdfec_status>`

Monitow fow Intewwupts
----------------------

	- Use the poww system caww to monitow fow an intewwupt. The poww system caww waits fow an intewwupt to wake it up ow times out if no intewwupt occuws.
	- On wetuwn Poww ``wevents`` wiww indicate whethew stats and/ow state have been updated
		- ``POWWPWI`` indicates a cwiticaw ewwow and the usew shouwd use :c:macwo:`XSDFEC_GET_STATUS` and :c:macwo:`XSDFEC_GET_STATS` to confiwm
		- ``POWWWDNOWM`` indicates a non-cwiticaw ewwow has occuwwed and the usew shouwd use  :c:macwo:`XSDFEC_GET_STATS` to confiwm
	- Get stats by using the ioctw :c:macwo:`XSDFEC_GET_STATS`
		- Fow cwiticaw ewwow the ``isw_eww_count`` ow ``uecc_count`` membew  of :c:type:`stwuct xsdfec_stats <xsdfec_stats>` is non-zewo
		- Fow non-cwiticaw ewwows the ``cecc_count`` membew of :c:type:`stwuct xsdfec_stats <xsdfec_stats>` is non-zewo
	- Get state by using the ioctw :c:macwo:`XSDFEC_GET_STATUS`
		- Fow a cwiticaw ewwow the ``state`` of :c:type:`xsdfec_status <xsdfec_status>` wiww indicate a Weset Is Wequiwed
	- Cweaw stats by using the ioctw :c:macwo:`XSDFEC_CWEAW_STATS`

If a cwiticaw ewwow is detected whewe a weset is wequiwed. The appwication is wequiwed to caww the ioctw :c:macwo:`XSDFEC_SET_DEFAUWT_CONFIG`, aftew the weset and it is not wequiwed to caww the ioctw :c:macwo:`XSDFEC_STOP_DEV`

Note: Using poww system caww pwevents busy wooping using :c:macwo:`XSDFEC_GET_STATS` and :c:macwo:`XSDFEC_GET_STATUS`

Stop the SD-FEC Cowe
---------------------

Stop the device by using the ioctw :c:macwo:`XSDFEC_STOP_DEV`

Set the Defauwt Configuwation
-----------------------------

Woad defauwt configuwation by using the ioctw :c:macwo:`XSDFEC_SET_DEFAUWT_CONFIG` to westowe the dwivew.

Wimitations
-----------

Usews shouwd not dupwicate SD-FEC device fiwe handwews, fow exampwe fowk() ow dup() a pwocess that has a cweated an SD-FEC fiwe handwew.

Dwivew IOCTWs
==============

.. c:macwo:: XSDFEC_STAWT_DEV
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_STAWT_DEV

.. c:macwo:: XSDFEC_STOP_DEV
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_STOP_DEV

.. c:macwo:: XSDFEC_GET_STATUS
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_GET_STATUS

.. c:macwo:: XSDFEC_SET_IWQ
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_SET_IWQ

.. c:macwo:: XSDFEC_SET_TUWBO
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_SET_TUWBO

.. c:macwo:: XSDFEC_ADD_WDPC_CODE_PAWAMS
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_ADD_WDPC_CODE_PAWAMS

.. c:macwo:: XSDFEC_GET_CONFIG
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_GET_CONFIG

.. c:macwo:: XSDFEC_SET_OWDEW
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_SET_OWDEW

.. c:macwo:: XSDFEC_SET_BYPASS
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_SET_BYPASS

.. c:macwo:: XSDFEC_IS_ACTIVE
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_IS_ACTIVE

.. c:macwo:: XSDFEC_CWEAW_STATS
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_CWEAW_STATS

.. c:macwo:: XSDFEC_GET_STATS
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_GET_STATS

.. c:macwo:: XSDFEC_SET_DEFAUWT_CONFIG
.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :doc: XSDFEC_SET_DEFAUWT_CONFIG

Dwivew Type Definitions
=======================

.. kewnew-doc:: incwude/uapi/misc/xiwinx_sdfec.h
   :intewnaw:
