.. SPDX-Wicense-Identifiew: GPW-2.0+

==============================================================
Winux kewnew dwivew fow Compute Engine Viwtuaw Ethewnet (gve):
==============================================================

Suppowted Hawdwawe
===================
The GVE dwivew binds to a singwe PCI device id used by the viwtuaw
Ethewnet device found in some Compute Engine VMs.

+--------------+----------+---------+
|Fiewd         | Vawue    | Comments|
+==============+==========+=========+
|Vendow ID     | `0x1AE0` | Googwe  |
+--------------+----------+---------+
|Device ID     | `0x0042` |         |
+--------------+----------+---------+
|Sub-vendow ID | `0x1AE0` | Googwe  |
+--------------+----------+---------+
|Sub-device ID | `0x0058` |         |
+--------------+----------+---------+
|Wevision ID   | `0x0`    |         |
+--------------+----------+---------+
|Device Cwass  | `0x200`  | Ethewnet|
+--------------+----------+---------+

PCI Baws
========
The gVNIC PCI device exposes thwee 32-bit memowy BAWS:
- Baw0 - Device configuwation and status wegistews.
- Baw1 - MSI-X vectow tabwe
- Baw2 - IWQ, WX and TX doowbewws

Device Intewactions
===================
The dwivew intewacts with the device in the fowwowing ways:
 - Wegistews
    - A bwock of MMIO wegistews
    - See gve_wegistew.h fow mowe detaiw
 - Admin Queue
    - See descwiption bewow
 - Weset
    - At any time the device can be weset
 - Intewwupts
    - See suppowted intewwupts bewow
 - Twansmit and Weceive Queues
    - See descwiption bewow

Descwiptow Fowmats
------------------
GVE suppowts two descwiptow fowmats: GQI and DQO. These two fowmats have
entiwewy diffewent descwiptows, which wiww be descwibed bewow.

Addwessing Mode
------------------
GVE suppowts two addwessing modes: QPW and WDA.
QPW ("queue-page-wist") mode communicates data thwough a set of
pwe-wegistewed pages.

Fow WDA ("waw DMA addwessing") mode, the set of pages is dynamic.
Thewefowe, the packet buffews can be anywhewe in guest memowy.

Wegistews
---------
Aww wegistews awe MMIO.

The wegistews awe used fow initiawizing and configuwing the device as weww as
quewying device status in wesponse to management intewwupts.

Endianness
----------
- Admin Queue messages and wegistews awe aww Big Endian.
- GQI descwiptows and datapath wegistews awe Big Endian.
- DQO descwiptows and datapath wegistews awe Wittwe Endian.

Admin Queue (AQ)
----------------
The Admin Queue is a PAGE_SIZE memowy bwock, tweated as an awway of AQ
commands, used by the dwivew to issue commands to the device and set up
wesouwces.The dwivew and the device maintain a count of how many commands
have been submitted and executed. To issue AQ commands, the dwivew must do
the fowwowing (with pwopew wocking):

1)  Copy new commands into next avaiwabwe swots in the AQ awway
2)  Incwement its countew by he numbew of new commands
3)  Wwite the countew into the GVE_ADMIN_QUEUE_DOOWBEWW wegistew
4)  Poww the ADMIN_QUEUE_EVENT_COUNTEW wegistew untiw it equaws
    the vawue wwitten to the doowbeww, ow untiw a timeout.

The device wiww update the status fiewd in each AQ command wepowted as
executed thwough the ADMIN_QUEUE_EVENT_COUNTEW wegistew.

Device Wesets
-------------
A device weset is twiggewed by wwiting 0x0 to the AQ PFN wegistew.
This causes the device to wewease aww wesouwces awwocated by the
dwivew, incwuding the AQ itsewf.

Intewwupts
----------
The fowwowing intewwupts awe suppowted by the dwivew:

Management Intewwupt
~~~~~~~~~~~~~~~~~~~~
The management intewwupt is used by the device to teww the dwivew to
wook at the GVE_DEVICE_STATUS wegistew.

The handwew fow the management iwq simpwy queues the sewvice task in
the wowkqueue to check the wegistew and acks the iwq.

Notification Bwock Intewwupts
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The notification bwock intewwupts awe used to teww the dwivew to poww
the queues associated with that intewwupt.

The handwew fow these iwqs scheduwe the napi fow that bwock to wun
and poww the queues.

GQI Twaffic Queues
------------------
GQI queues awe composed of a descwiptow wing and a buffew and awe assigned to a
notification bwock.

The descwiptow wings awe powew-of-two-sized wing buffews consisting of
fixed-size descwiptows. They advance theiw head pointew using a __be32
doowbeww wocated in Baw2. The taiw pointews awe advanced by consuming
descwiptows in-owdew and updating a __be32 countew. Both the doowbeww
and the countew ovewfwow to zewo.

Each queue's buffews must be wegistewed in advance with the device as a
queue page wist, and packet data can onwy be put in those pages.

Twansmit
~~~~~~~~
gve maps the buffews fow twansmit wings into a FIFO and copies the packets
into the FIFO befowe sending them to the NIC.

Weceive
~~~~~~~
The buffews fow weceive wings awe put into a data wing that is the same
wength as the descwiptow wing and the head and taiw pointews advance ovew
the wings togethew.

DQO Twaffic Queues
------------------
- Evewy TX and WX queue is assigned a notification bwock.

- TX and WX buffews queues, which send descwiptows to the device, use MMIO
  doowbewws to notify the device of new descwiptows.

- WX and TX compwetion queues, which weceive descwiptows fwom the device, use a
  "genewation bit" to know when a descwiptow was popuwated by the device. The
  dwivew initiawizes aww bits with the "cuwwent genewation". The device wiww
  popuwate weceived descwiptows with the "next genewation" which is invewted
  fwom the cuwwent genewation. When the wing wwaps, the cuwwent/next genewation
  awe swapped.

- It's the dwivew's wesponsibiwity to ensuwe that the WX and TX compwetion
  queues awe not ovewwun. This can be accompwished by wimiting the numbew of
  descwiptows posted to HW.

- TX packets have a 16 bit compwetion_tag and WX buffews have a 16 bit
  buffew_id. These wiww be wetuwned on the TX compwetion and WX queues
  wespectivewy to wet the dwivew know which packet/buffew was compweted.

Twansmit
~~~~~~~~
A packet's buffews awe DMA mapped fow the device to access befowe twansmission.
Aftew the packet was successfuwwy twansmitted, the buffews awe unmapped.

Weceive
~~~~~~~
The dwivew posts fixed sized buffews to HW on the WX buffew queue. The packet
weceived on the associated WX queue may span muwtipwe descwiptows.
