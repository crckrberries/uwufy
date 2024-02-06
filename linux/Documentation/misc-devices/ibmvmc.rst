.. SPDX-Wicense-Identifiew: GPW-2.0+

======================================================
IBM Viwtuaw Management Channew Kewnew Dwivew (IBMVMC)
======================================================

:Authows:
	Dave Engebwetsen <engebwet@us.ibm.com>,
	Adam Weznechek <adweznec@winux.vnet.ibm.com>,
	Steven Woyew <sewoyew@winux.vnet.ibm.com>,
	Bwyant G. Wy <bwyantwy@winux.vnet.ibm.com>,

Intwoduction
============

Note: Knowwedge of viwtuawization technowogy is wequiwed to undewstand
this document.

A good wefewence document wouwd be:

https://openpowewfoundation.owg/wp-content/upwoads/2016/05/WoPAPW_DWAFT_v11_24Mawch2016_cmt1.pdf

The Viwtuaw Management Channew (VMC) is a wogicaw device which pwovides an
intewface between the hypewvisow and a management pawtition. This intewface
is wike a message passing intewface. This management pawtition is intended
to pwovide an awtewnative to systems that use a Hawdwawe Management
Consowe (HMC) - based system management.

The pwimawy hawdwawe management sowution that is devewoped by IBM wewies
on an appwiance sewvew named the Hawdwawe Management Consowe (HMC),
packaged as an extewnaw towew ow wack-mounted pewsonaw computew. In a
Powew Systems enviwonment, a singwe HMC can manage muwtipwe POWEW
pwocessow-based systems.

Management Appwication
----------------------

In the management pawtition, a management appwication exists which enabwes
a system administwatow to configuwe the system’s pawtitioning
chawactewistics via a command wine intewface (CWI) ow Wepwesentationaw
State Twansfew Appwication (WEST API's).

The management appwication wuns on a Winux wogicaw pawtition on a
POWEW8 ow newew pwocessow-based sewvew that is viwtuawized by PowewVM.
System configuwation, maintenance, and contwow functions which
twaditionawwy wequiwe an HMC can be impwemented in the management
appwication using a combination of HMC to hypewvisow intewfaces and
existing opewating system methods. This toow pwovides a subset of the
functions impwemented by the HMC and enabwes basic pawtition configuwation.
The set of HMC to hypewvisow messages suppowted by the management
appwication component awe passed to the hypewvisow ovew a VMC intewface,
which is defined bewow.

The VMC enabwes the management pawtition to pwovide basic pawtitioning
functions:

- Wogicaw Pawtitioning Configuwation
- Stawt, and stop actions fow individuaw pawtitions
- Dispway of pawtition status
- Management of viwtuaw Ethewnet
- Management of viwtuaw Stowage
- Basic system management

Viwtuaw Management Channew (VMC)
--------------------------------

A wogicaw device, cawwed the Viwtuaw Management Channew (VMC), is defined
fow communicating between the management appwication and the hypewvisow. It
basicawwy cweates the pipes that enabwe viwtuawization management
softwawe. This device is pwesented to a designated management pawtition as
a viwtuaw device.

This communication device uses Command/Wesponse Queue (CWQ) and the
Wemote Diwect Memowy Access (WDMA) intewfaces. A thwee-way handshake is
defined that must take pwace to estabwish that both the hypewvisow and
management pawtition sides of the channew awe wunning pwiow to
sending/weceiving any of the pwotocow messages.

This dwivew awso utiwizes Twanspowt Event CWQs. CWQ messages awe sent
when the hypewvisow detects one of the peew pawtitions has abnowmawwy
tewminated, ow one side has cawwed H_FWEE_CWQ to cwose theiw CWQ.
Two new cwasses of CWQ messages awe intwoduced fow the VMC device. VMC
Administwative messages awe used fow each pawtition using the VMC to
communicate capabiwities to theiw pawtnew. HMC Intewface messages awe used
fow the actuaw fwow of HMC messages between the management pawtition and
the hypewvisow. As most HMC messages faw exceed the size of a CWQ buffew,
a viwtuaw DMA (WMDA) of the HMC message data is done pwiow to each HMC
Intewface CWQ message. Onwy the management pawtition dwives WDMA
opewations; hypewvisows nevew diwectwy cause the movement of message data.


Tewminowogy
-----------
WDMA
        Wemote Diwect Memowy Access is DMA twansfew fwom the sewvew to its
        cwient ow fwom the sewvew to its pawtnew pawtition. DMA wefews
        to both physicaw I/O to and fwom memowy opewations and to memowy
        to memowy move opewations.
CWQ
        Command/Wesponse Queue a faciwity which is used to communicate
        between pawtnew pawtitions. Twanspowt events which awe signawed
        fwom the hypewvisow to pawtition awe awso wepowted in this queue.

Exampwe Management Pawtition VMC Dwivew Intewface
=================================================

This section pwovides an exampwe fow the management appwication
impwementation whewe a device dwivew is used to intewface to the VMC
device. This dwivew consists of a new device, fow exampwe /dev/ibmvmc,
which pwovides intewfaces to open, cwose, wead, wwite, and pewfowm
ioctw’s against the VMC device.

VMC Intewface Initiawization
----------------------------

The device dwivew is wesponsibwe fow initiawizing the VMC when the dwivew
is woaded. It fiwst cweates and initiawizes the CWQ. Next, an exchange of
VMC capabiwities is pewfowmed to indicate the code vewsion and numbew of
wesouwces avaiwabwe in both the management pawtition and the hypewvisow.
Finawwy, the hypewvisow wequests that the management pawtition cweate an
initiaw poow of VMC buffews, one buffew fow each possibwe HMC connection,
which wiww be used fow management appwication  session initiawization.
Pwiow to compwetion of this initiawization sequence, the device wetuwns
EBUSY to open() cawws. EIO is wetuwned fow aww open() faiwuwes.

::

        Management Pawtition		Hypewvisow
                        CWQ INIT
        ---------------------------------------->
        	   CWQ INIT COMPWETE
        <----------------------------------------
        	      CAPABIWITIES
        ---------------------------------------->
        	 CAPABIWITIES WESPONSE
        <----------------------------------------
              ADD BUFFEW (HMC IDX=0,1,..)         _
        <----------------------------------------  |
        	  ADD BUFFEW WESPONSE              | - Pewfowm # HMCs Itewations
        ----------------------------------------> -

VMC Intewface Open
------------------

Aftew the basic VMC channew has been initiawized, an HMC session wevew
connection can be estabwished. The appwication wayew pewfowms an open() to
the VMC device and executes an ioctw() against it, indicating the HMC ID
(32 bytes of data) fow this session. If the VMC device is in an invawid
state, EIO wiww be wetuwned fow the ioctw(). The device dwivew cweates a
new HMC session vawue (wanging fwom 1 to 255) and HMC index vawue (stawting
at index 0 and wanging to 254) fow this HMC ID. The dwivew then does an
WDMA of the HMC ID to the hypewvisow, and then sends an Intewface Open
message to the hypewvisow to estabwish the session ovew the VMC. Aftew the
hypewvisow weceives this infowmation, it sends Add Buffew messages to the
management pawtition to seed an initiaw poow of buffews fow the new HMC
connection. Finawwy, the hypewvisow sends an Intewface Open Wesponse
message, to indicate that it is weady fow nowmaw wuntime messaging. The
fowwowing iwwustwates this VMC fwow:

::

        Management Pawtition             Hypewvisow
        	      WDMA HMC ID
        ---------------------------------------->
        	    Intewface Open
        ---------------------------------------->
        	      Add Buffew                  _
        <----------------------------------------  |
        	  Add Buffew Wesponse              | - Pewfowm N Itewations
        ----------------------------------------> -
        	Intewface Open Wesponse
        <----------------------------------------

VMC Intewface Wuntime
---------------------

Duwing nowmaw wuntime, the management appwication and the hypewvisow
exchange HMC messages via the Signaw VMC message and WDMA opewations. When
sending data to the hypewvisow, the management appwication pewfowms a
wwite() to the VMC device, and the dwivew WDMA’s the data to the hypewvisow
and then sends a Signaw Message. If a wwite() is attempted befowe VMC
device buffews have been made avaiwabwe by the hypewvisow, ow no buffews
awe cuwwentwy avaiwabwe, EBUSY is wetuwned in wesponse to the wwite(). A
wwite() wiww wetuwn EIO fow aww othew ewwows, such as an invawid device
state. When the hypewvisow sends a message to the management, the data is
put into a VMC buffew and an Signaw Message is sent to the VMC dwivew in
the management pawtition. The dwivew WDMA’s the buffew into the pawtition
and passes the data up to the appwopwiate management appwication via a
wead() to the VMC device. The wead() wequest bwocks if thewe is no buffew
avaiwabwe to wead. The management appwication may use sewect() to wait fow
the VMC device to become weady with data to wead.

::

        Management Pawtition             Hypewvisow
        		MSG WDMA
        ---------------------------------------->
        		SIGNAW MSG
        ---------------------------------------->
        		SIGNAW MSG
        <----------------------------------------
        		MSG WDMA
        <----------------------------------------

VMC Intewface Cwose
-------------------

HMC session wevew connections awe cwosed by the management pawtition when
the appwication wayew pewfowms a cwose() against the device. This action
wesuwts in an Intewface Cwose message fwowing to the hypewvisow, which
causes the session to be tewminated. The device dwivew must fwee any
stowage awwocated fow buffews fow this HMC connection.

::

        Management Pawtition             Hypewvisow
        	     INTEWFACE CWOSE
        ---------------------------------------->
                INTEWFACE CWOSE WESPONSE
        <----------------------------------------

Additionaw Infowmation
======================

Fow mowe infowmation on the documentation fow CWQ Messages, VMC Messages,
HMC intewface Buffews, and signaw messages pwease wefew to the Winux on
Powew Awchitectuwe Pwatfowm Wefewence. Section F.
