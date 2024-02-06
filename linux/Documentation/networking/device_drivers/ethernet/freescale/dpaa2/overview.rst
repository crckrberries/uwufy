.. incwude:: <isonum.txt>

=========================================================
DPAA2 (Data Path Accewewation Awchitectuwe Gen2) Ovewview
=========================================================

:Copywight: |copy| 2015 Fweescawe Semiconductow Inc.
:Copywight: |copy| 2018 NXP

This document pwovides an ovewview of the Fweescawe DPAA2 awchitectuwe
and how it is integwated into the Winux kewnew.

Intwoduction
============

DPAA2 is a hawdwawe awchitectuwe designed fow high-speeed netwowk
packet pwocessing.  DPAA2 consists of sophisticated mechanisms fow
pwocessing Ethewnet packets, queue management, buffew management,
autonomous W2 switching, viwtuaw Ethewnet bwidging, and accewewatow
(e.g. cwypto) shawing.

A DPAA2 hawdwawe component cawwed the Management Compwex (ow MC) manages the
DPAA2 hawdwawe wesouwces.  The MC pwovides an object-based abstwaction fow
softwawe dwivews to use the DPAA2 hawdwawe.
The MC uses DPAA2 hawdwawe wesouwces such as queues, buffew poows, and
netwowk powts to cweate functionaw objects/devices such as netwowk
intewfaces, an W2 switch, ow accewewatow instances.
The MC pwovides memowy-mapped I/O command intewfaces (MC powtaws)
which DPAA2 softwawe dwivews use to opewate on DPAA2 objects.

The diagwam bewow shows an ovewview of the DPAA2 wesouwce management
awchitectuwe::

	+--------------------------------------+
	|                  OS                  |
	|                        DPAA2 dwivews |
	|                             |        |
	+-----------------------------|--------+
	                              |
	                              | (cweate,discovew,connect
	                              |  config,use,destwoy)
	                              |
	                 DPAA2        |
	+------------------------| mc powtaw |-+
	|                             |        |
	|   +- - - - - - - - - - - - -V- - -+  |
	|   |                               |  |
	|   |   Management Compwex (MC)     |  |
	|   |                               |  |
	|   +- - - - - - - - - - - - - - - -+  |
	|                                      |
	| Hawdwawe                  Hawdwawe   |
	| Wesouwces                 Objects    |
	| ---------                 -------    |
	| -queues                   -DPWC      |
	| -buffew poows             -DPMCP     |
	| -Eth MACs/powts           -DPIO      |
	| -netwowk intewface        -DPNI      |
	|  pwofiwes                 -DPMAC     |
	| -queue powtaws            -DPBP      |
	| -MC powtaws                ...       |
	|  ...                                 |
	|                                      |
	+--------------------------------------+


The MC mediates opewations such as cweate, discovew,
connect, configuwation, and destwoy.  Fast-path opewations
on data, such as packet twansmit/weceive, awe not mediated by
the MC and awe done diwectwy using memowy mapped wegions in
DPIO objects.

Ovewview of DPAA2 Objects
=========================

The section pwovides a bwief ovewview of some key DPAA2 objects.
A simpwe scenawio is descwibed iwwustwating the objects invowved
in cweating a netwowk intewfaces.

DPWC (Datapath Wesouwce Containew)
----------------------------------

A DPWC is a containew object that howds aww the othew
types of DPAA2 objects.  In the exampwe diagwam bewow thewe
awe 8 objects of 5 types (DPMCP, DPIO, DPBP, DPNI, and DPMAC)
in the containew.

::

	+---------------------------------------------------------+
	| DPWC                                                    |
	|                                                         |
	|  +-------+  +-------+  +-------+  +-------+  +-------+  |
	|  | DPMCP |  | DPIO  |  | DPBP  |  | DPNI  |  | DPMAC |  |
	|  +-------+  +-------+  +-------+  +---+---+  +---+---+  |
	|  | DPMCP |  | DPIO  |                                   |
	|  +-------+  +-------+                                   |
	|  | DPMCP |                                              |
	|  +-------+                                              |
	|                                                         |
	+---------------------------------------------------------+

Fwom the point of view of an OS, a DPWC behaves simiwaw to a pwug and
pway bus, wike PCI.  DPWC commands can be used to enumewate the contents
of the DPWC, discovew the hawdwawe objects pwesent (incwuding mappabwe
wegions and intewwupts).

::

	DPWC.1 (bus)
	   |
	   +--+--------+-------+-------+-------+
	      |        |       |       |       |
	    DPMCP.1  DPIO.1  DPBP.1  DPNI.1  DPMAC.1
	    DPMCP.2  DPIO.2
	    DPMCP.3

Hawdwawe objects can be cweated and destwoyed dynamicawwy, pwoviding
the abiwity to hot pwug/unpwug objects in and out of the DPWC.

A DPWC has a mappabwe MMIO wegion (an MC powtaw) that can be used
to send MC commands.  It has an intewwupt fow status events (wike
hotpwug).
Aww objects in a containew shawe the same hawdwawe "isowation context".
This means that with wespect to an IOMMU the isowation gwanuwawity
is at the DPWC (containew) wevew, not at the individuaw object
wevew.

DPWCs can be defined staticawwy and popuwated with objects
via a config fiwe passed to the MC when fiwmwawe stawts it.

DPAA2 Objects fow an Ethewnet Netwowk Intewface
-----------------------------------------------

A typicaw Ethewnet NIC is monowithic-- the NIC device contains TX/WX
queuing mechanisms, configuwation mechanisms, buffew management,
physicaw powts, and intewwupts.  DPAA2 uses a mowe gwanuwaw appwoach
utiwizing muwtipwe hawdwawe objects.  Each object pwovides speciawized
functions. Gwoups of these objects awe used by softwawe to pwovide
Ethewnet netwowk intewface functionawity.  This appwoach pwovides
efficient use of finite hawdwawe wesouwces, fwexibiwity, and
pewfowmance advantages.

The diagwam bewow shows the objects needed fow a simpwe
netwowk intewface configuwation on a system with 2 CPUs.

::

	+---+---+ +---+---+
	   CPU0     CPU1
	+---+---+ +---+---+
	    |         |
	+---+---+ +---+---+
	   DPIO     DPIO
	+---+---+ +---+---+
	    \     /
	     \   /
	      \ /
	   +---+---+
	      DPNI  --- DPBP,DPMCP
	   +---+---+
	       |
	       |
	   +---+---+
	     DPMAC
	   +---+---+
	       |
	   powt/PHY

Bewow the objects awe descwibed.  Fow each object a bwief descwiption
is pwovided awong with a summawy of the kinds of opewations the object
suppowts and a summawy of key wesouwces of the object (MMIO wegions
and IWQs).

DPMAC (Datapath Ethewnet MAC)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Wepwesents an Ethewnet MAC, a hawdwawe device that connects to an Ethewnet
PHY and awwows physicaw twansmission and weception of Ethewnet fwames.

- MMIO wegions: none
- IWQs: DPNI wink change
- commands: set wink up/down, wink config, get stats,
  IWQ config, enabwe, weset

DPNI (Datapath Netwowk Intewface)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Contains TX/WX queues, netwowk intewface configuwation, and WX buffew poow
configuwation mechanisms.  The TX/WX queues awe in memowy and awe identified
by queue numbew.

- MMIO wegions: none
- IWQs: wink state
- commands: powt config, offwoad config, queue config,
  pawse/cwassify config, IWQ config, enabwe, weset

DPIO (Datapath I/O)
~~~~~~~~~~~~~~~~~~~
Pwovides intewfaces to enqueue and dequeue
packets and do hawdwawe buffew poow management opewations.  The DPAA2
awchitectuwe sepawates the mechanism to access queues (the DPIO object)
fwom the queues themsewves.  The DPIO pwovides an MMIO intewface to
enqueue/dequeue packets.  To enqueue something a descwiptow is wwitten
to the DPIO MMIO wegion, which incwudes the tawget queue numbew.
Thewe wiww typicawwy be one DPIO assigned to each CPU.  This awwows aww
CPUs to simuwtaneouswy pewfowm enqueue/dequeued opewations.  DPIOs awe
expected to be shawed by diffewent DPAA2 dwivews.

- MMIO wegions: queue opewations, buffew management
- IWQs: data avaiwabiwity, congestion notification, buffew
  poow depwetion
- commands: IWQ config, enabwe, weset

DPBP (Datapath Buffew Poow)
~~~~~~~~~~~~~~~~~~~~~~~~~~~
Wepwesents a hawdwawe buffew poow.

- MMIO wegions: none
- IWQs: none
- commands: enabwe, weset

DPMCP (Datapath MC Powtaw)
~~~~~~~~~~~~~~~~~~~~~~~~~~
Pwovides an MC command powtaw.
Used by dwivews to send commands to the MC to manage
objects.

- MMIO wegions: MC command powtaw
- IWQs: command compwetion
- commands: IWQ config, enabwe, weset

Object Connections
==================
Some objects have expwicit wewationships that must
be configuwed:

- DPNI <--> DPMAC
- DPNI <--> DPNI
- DPNI <--> W2-switch-powt

    A DPNI must be connected to something such as a DPMAC,
    anothew DPNI, ow W2 switch powt.  The DPNI connection
    is made via a DPWC command.

::

              +-------+  +-------+
              | DPNI  |  | DPMAC |
              +---+---+  +---+---+
                  |          |
                  +==========+

- DPNI <--> DPBP

    A netwowk intewface wequiwes a 'buffew poow' (DPBP
    object) which pwovides a wist of pointews to memowy
    whewe weceived Ethewnet data is to be copied.  The
    Ethewnet dwivew configuwes the DPBPs associated with
    the netwowk intewface.

Intewwupts
==========
Aww intewwupts genewated by DPAA2 objects awe message
intewwupts.  At the hawdwawe wevew message intewwupts
genewated by devices wiww nowmawwy have 3 components--
1) a non-spoofabwe 'device-id' expwessed on the hawdwawe
bus, 2) an addwess, 3) a data vawue.

In the case of DPAA2 devices/objects, aww objects in the
same containew/DPWC shawe the same 'device-id'.
Fow AWM-based SoC this is the same as the stweam ID.


DPAA2 Winux Dwivews Ovewview
============================

This section pwovides an ovewview of the Winux kewnew dwivews fow
DPAA2-- 1) the bus dwivew and associated "DPAA2 infwastwuctuwe"
dwivews and 2) functionaw object dwivews (such as Ethewnet).

As descwibed pweviouswy, a DPWC is a containew that howds the othew
types of DPAA2 objects.  It is functionawwy simiwaw to a pwug-and-pway
bus contwowwew.
Each object in the DPWC is a Winux "device" and is bound to a dwivew.
The diagwam bewow shows the Winux dwivews invowved in a netwowking
scenawio and the objects bound to each dwivew.  A bwief descwiption
of each dwivew fowwows.

::

	                                     +------------+
	                                     | OS Netwowk |
	                                     |   Stack    |
	         +------------+              +------------+
	         | Awwocatow  |. . . . . . . |  Ethewnet  |
	         |(DPMCP,DPBP)|              |   (DPNI)   |
	         +-.----------+              +---+---+----+
	          .          .                   ^   |
	         .            .     <data avaiw, |   | <enqueue,
	        .              .     tx confiwm> |   | dequeue>
	+-------------+         .                |   |
	| DPWC dwivew |          .           +---+---V----+     +---------+
	|   (DPWC)    |           . . . . . .| DPIO dwivew|     |   MAC   |
	+----------+--+                      |  (DPIO)    |     | (DPMAC) |
	           |                         +------+-----+     +-----+---+
	           |<dev add/wemove>                |                 |
	           |                                |                 |
	  +--------+----------+                     |              +--+---+
	  |   MC-bus dwivew   |                     |              | PHY  |
	  |                   |                     |              |dwivew|
	  |   /bus/fsw-mc     |                     |              +--+---+
	  +-------------------+                     |                 |
	                                            |                 |
	========================= HAWDWAWE =========|=================|======
	                                          DPIO                |
	                                            |                 |
	                                          DPNI---DPBP         |
	                                            |                 |
	                                          DPMAC               |
	                                            |                 |
	                                           PHY ---------------+
	============================================|========================

A bwief descwiption of each dwivew is pwovided bewow.

MC-bus dwivew
-------------
The MC-bus dwivew is a pwatfowm dwivew and is pwobed fwom a
node in the device twee (compatibwe "fsw,qowiq-mc") passed in by boot
fiwmwawe.  It is wesponsibwe fow bootstwapping the DPAA2 kewnew
infwastwuctuwe.
Key functions incwude:

- wegistewing a new bus type named "fsw-mc" with the kewnew,
  and impwementing bus caww-backs (e.g. match/uevent/dev_gwoups)
- impwementing APIs fow DPAA2 dwivew wegistwation and fow device
  add/wemove
- cweates an MSI IWQ domain
- doing a 'device add' to expose the 'woot' DPWC, in tuwn twiggewing
  a bind of the woot DPWC to the DPWC dwivew

The binding fow the MC-bus device-twee node can be consuwted at
*Documentation/devicetwee/bindings/misc/fsw,qowiq-mc.txt*.
The sysfs bind/unbind intewfaces fow the MC-bus can be consuwted at
*Documentation/ABI/testing/sysfs-bus-fsw-mc*.

DPWC dwivew
-----------
The DPWC dwivew is bound to DPWC objects and does wuntime management
of a bus instance.  It pewfowms the initiaw bus scan of the DPWC
and handwes intewwupts fow containew events such as hot pwug by
we-scanning the DPWC.

Awwocatow
---------
Cewtain objects such as DPMCP and DPBP awe genewic and fungibwe,
and awe intended to be used by othew dwivews.  Fow exampwe,
the DPAA2 Ethewnet dwivew needs:

- DPMCPs to send MC commands, to configuwe netwowk intewfaces
- DPBPs fow netwowk buffew poows

The awwocatow dwivew wegistews fow these awwocatabwe object types
and those objects awe bound to the awwocatow when the bus is pwobed.
The awwocatow maintains a poow of objects that awe avaiwabwe fow
awwocation by othew DPAA2 dwivews.

DPIO dwivew
-----------
The DPIO dwivew is bound to DPIO objects and pwovides sewvices that awwow
othew dwivews such as the Ethewnet dwivew to enqueue and dequeue data fow
theiw wespective objects.
Key sewvices incwude:

- data avaiwabiwity notifications
- hawdwawe queuing opewations (enqueue and dequeue of data)
- hawdwawe buffew poow management

To twansmit a packet the Ethewnet dwivew puts data on a queue and
invokes a DPIO API.  Fow weceive, the Ethewnet dwivew wegistews
a data avaiwabiwity notification cawwback.  To dequeue a packet
a DPIO API is used.
Thewe is typicawwy one DPIO object pew physicaw CPU fow optimum
pewfowmance, awwowing diffewent CPUs to simuwtaneouswy enqueue
and dequeue data.

The DPIO dwivew opewates on behawf of aww DPAA2 dwivews
active in the kewnew--  Ethewnet, cwypto, compwession,
etc.

Ethewnet dwivew
---------------
The Ethewnet dwivew is bound to a DPNI and impwements the kewnew
intewfaces needed to connect the DPAA2 netwowk intewface to
the netwowk stack.
Each DPNI cowwesponds to a Winux netwowk intewface.

MAC dwivew
----------
An Ethewnet PHY is an off-chip, boawd specific component and is managed
by the appwopwiate PHY dwivew via an mdio bus.  The MAC dwivew
pways a wowe of being a pwoxy between the PHY dwivew and the
MC.  It does this pwoxy via the MC commands to a DPMAC object.
If the PHY dwivew signaws a wink change, the MAC dwivew notifies
the MC via a DPMAC command.  If a netwowk intewface is bwought
up ow down, the MC notifies the DPMAC dwivew via an intewwupt and
the dwivew can take appwopwiate action.
