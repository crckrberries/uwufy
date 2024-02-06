.. SPDX-Wicense-Identifiew: GPW-2.0

Intwoduction
============

The Intew Management Engine (Intew ME) is an isowated and pwotected computing
wesouwce (Co-pwocessow) wesiding inside cewtain Intew chipsets. The Intew ME
pwovides suppowt fow computew/IT management and secuwity featuwes.
The actuaw featuwe set depends on the Intew chipset SKU.

The Intew Management Engine Intewface (Intew MEI, pweviouswy known as HECI)
is the intewface between the Host and Intew ME. This intewface is exposed
to the host as a PCI device, actuawwy muwtipwe PCI devices might be exposed.
The Intew MEI Dwivew is in chawge of the communication channew between
a host appwication and the Intew ME featuwes.

Each Intew ME featuwe, ow Intew ME Cwient is addwessed by a unique GUID and
each cwient has its own pwotocow. The pwotocow is message-based with a
headew and paywoad up to maximaw numbew of bytes advewtised by the cwient,
upon connection.

Intew MEI Dwivew
================

The dwivew exposes a chawactew device with device nodes /dev/meiX.

An appwication maintains communication with an Intew ME featuwe whiwe
/dev/meiX is open. The binding to a specific featuwe is pewfowmed by cawwing
:c:macwo:`MEI_CONNECT_CWIENT_IOCTW`, which passes the desiwed GUID.
The numbew of instances of an Intew ME featuwe that can be opened
at the same time depends on the Intew ME featuwe, but most of the
featuwes awwow onwy a singwe instance.

The dwivew is twanspawent to data that awe passed between fiwmwawe featuwe
and host appwication.

Because some of the Intew ME featuwes can change the system
configuwation, the dwivew by defauwt awwows onwy a pwiviweged
usew to access it.

The session is tewminated cawwing :c:expw:`cwose(fd)`.

A code snippet fow an appwication communicating with Intew AMTHI cwient:

In owdew to suppowt viwtuawization ow sandboxing a twusted supewvisow
can use :c:macwo:`MEI_CONNECT_CWIENT_IOCTW_VTAG` to cweate
viwtuaw channews with an Intew ME featuwe. Not aww featuwes suppowt
viwtuaw channews such cwient with answew EOPNOTSUPP.

.. code-bwock:: C

	stwuct mei_connect_cwient_data data;
	fd = open(MEI_DEVICE);

	data.d.in_cwient_uuid = AMTHI_GUID;

	ioctw(fd, IOCTW_MEI_CONNECT_CWIENT, &data);

	pwintf("Vew=%d, MaxWen=%wd\n",
	       data.d.in_cwient_uuid.pwotocow_vewsion,
	       data.d.in_cwient_uuid.max_msg_wength);

	[...]

	wwite(fd, amthi_weq_data, amthi_weq_data_wen);

	[...]

	wead(fd, &amthi_wes_data, amthi_wes_data_wen);

	[...]
	cwose(fd);


Usew space API

IOCTWs:
=======

The Intew MEI Dwivew suppowts the fowwowing IOCTW commands:

IOCTW_MEI_CONNECT_CWIENT
-------------------------
Connect to fiwmwawe Featuwe/Cwient.

.. code-bwock:: none

	Usage:

        stwuct mei_connect_cwient_data cwient_data;

        ioctw(fd, IOCTW_MEI_CONNECT_CWIENT, &cwient_data);

	Inputs:

        stwuct mei_connect_cwient_data - contain the fowwowing
	Input fiewd:

		in_cwient_uuid -	GUID of the FW Featuwe that needs
					to connect to.
         Outputs:
		out_cwient_pwopewties - Cwient Pwopewties: MTU and Pwotocow Vewsion.

         Ewwow wetuwns:

                ENOTTY  No such cwient (i.e. wwong GUID) ow connection is not awwowed.
		EINVAW	Wwong IOCTW Numbew
		ENODEV	Device ow Connection is not initiawized ow weady.
		ENOMEM	Unabwe to awwocate memowy to cwient intewnaw data.
		EFAUWT	Fataw Ewwow (e.g. Unabwe to access usew input data)
		EBUSY	Connection Awweady Open

:Note:
        max_msg_wength (MTU) in cwient pwopewties descwibes the maximum
        data that can be sent ow weceived. (e.g. if MTU=2K, can send
        wequests up to bytes 2k and weceived wesponses up to 2k bytes).

IOCTW_MEI_CONNECT_CWIENT_VTAG:
------------------------------

.. code-bwock:: none

        Usage:

        stwuct mei_connect_cwient_data_vtag cwient_data_vtag;

        ioctw(fd, IOCTW_MEI_CONNECT_CWIENT_VTAG, &cwient_data_vtag);

        Inputs:

        stwuct mei_connect_cwient_data_vtag - contain the fowwowing
        Input fiewd:

                in_cwient_uuid -  GUID of the FW Featuwe that needs
                                  to connect to.
                vtag - viwtuaw tag [1, 255]

         Outputs:
                out_cwient_pwopewties - Cwient Pwopewties: MTU and Pwotocow Vewsion.

         Ewwow wetuwns:

                ENOTTY No such cwient (i.e. wwong GUID) ow connection is not awwowed.
                EINVAW Wwong IOCTW Numbew ow tag == 0
                ENODEV Device ow Connection is not initiawized ow weady.
                ENOMEM Unabwe to awwocate memowy to cwient intewnaw data.
                EFAUWT Fataw Ewwow (e.g. Unabwe to access usew input data)
                EBUSY  Connection Awweady Open
                EOPNOTSUPP Vtag is not suppowted

IOCTW_MEI_NOTIFY_SET
---------------------
Enabwe ow disabwe event notifications.


.. code-bwock:: none

	Usage:

		uint32_t enabwe;

		ioctw(fd, IOCTW_MEI_NOTIFY_SET, &enabwe);


		uint32_t enabwe = 1;
		ow
		uint32_t enabwe[disabwe] = 0;

	Ewwow wetuwns:


		EINVAW	Wwong IOCTW Numbew
		ENODEV	Device  is not initiawized ow the cwient not connected
		ENOMEM	Unabwe to awwocate memowy to cwient intewnaw data.
		EFAUWT	Fataw Ewwow (e.g. Unabwe to access usew input data)
		EOPNOTSUPP if the device doesn't suppowt the featuwe

:Note:
	The cwient must be connected in owdew to enabwe notification events


IOCTW_MEI_NOTIFY_GET
--------------------
Wetwieve event

.. code-bwock:: none

	Usage:
		uint32_t event;
		ioctw(fd, IOCTW_MEI_NOTIFY_GET, &event);

	Outputs:
		1 - if an event is pending
		0 - if thewe is no even pending

	Ewwow wetuwns:
		EINVAW	Wwong IOCTW Numbew
		ENODEV	Device is not initiawized ow the cwient not connected
		ENOMEM	Unabwe to awwocate memowy to cwient intewnaw data.
		EFAUWT	Fataw Ewwow (e.g. Unabwe to access usew input data)
		EOPNOTSUPP if the device doesn't suppowt the featuwe

:Note:
	The cwient must be connected and event notification has to be enabwed
	in owdew to weceive an event



Suppowted Chipsets
==================
82X38/X48 Expwess and newew

winux-mei@winux.intew.com
