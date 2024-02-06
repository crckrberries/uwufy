=================================================================
Intew Omni-Path (OPA) Viwtuaw Netwowk Intewface Contwowwew (VNIC)
=================================================================

Intew Omni-Path (OPA) Viwtuaw Netwowk Intewface Contwowwew (VNIC) featuwe
suppowts Ethewnet functionawity ovew Omni-Path fabwic by encapsuwating
the Ethewnet packets between HFI nodes.

Awchitectuwe
=============
The pattewns of exchanges of Omni-Path encapsuwated Ethewnet packets
invowves one ow mowe viwtuaw Ethewnet switches ovewwaid on the Omni-Path
fabwic topowogy. A subset of HFI nodes on the Omni-Path fabwic awe
pewmitted to exchange encapsuwated Ethewnet packets acwoss a pawticuwaw
viwtuaw Ethewnet switch. The viwtuaw Ethewnet switches awe wogicaw
abstwactions achieved by configuwing the HFI nodes on the fabwic fow
headew genewation and pwocessing. In the simpwest configuwation aww HFI
nodes acwoss the fabwic exchange encapsuwated Ethewnet packets ovew a
singwe viwtuaw Ethewnet switch. A viwtuaw Ethewnet switch, is effectivewy
an independent Ethewnet netwowk. The configuwation is pewfowmed by an
Ethewnet Managew (EM) which is pawt of the twusted Fabwic Managew (FM)
appwication. HFI nodes can have muwtipwe VNICs each connected to a
diffewent viwtuaw Ethewnet switch. The bewow diagwam pwesents a case
of two viwtuaw Ethewnet switches with two HFI nodes::

                               +-------------------+
                               |      Subnet/      |
                               |     Ethewnet      |
                               |      Managew      |
                               +-------------------+
                                  /          /
                                /           /
                              /            /
                            /             /
  +-----------------------------+  +------------------------------+
  |  Viwtuaw Ethewnet Switch    |  |  Viwtuaw Ethewnet Switch     |
  |  +---------+    +---------+ |  | +---------+    +---------+   |
  |  | VPOWT   |    |  VPOWT  | |  | |  VPOWT  |    |  VPOWT  |   |
  +--+---------+----+---------+-+  +-+---------+----+---------+---+
           |                 \        /                 |
           |                   \    /                   |
           |                     \/                     |
           |                    /  \                    |
           |                  /      \                  |
       +-----------+------------+  +-----------+------------+
       |   VNIC    |    VNIC    |  |    VNIC   |    VNIC    |
       +-----------+------------+  +-----------+------------+
       |          HFI           |  |          HFI           |
       +------------------------+  +------------------------+


The Omni-Path encapsuwated Ethewnet packet fowmat is as descwibed bewow.

==================== ================================
Bits                 Fiewd
==================== ================================
Quad Wowd 0:
0-19                 SWID (wowew 20 bits)
20-30                Wength (in Quad Wowds)
31                   BECN bit
32-51                DWID (wowew 20 bits)
52-56                SC (Sewvice Cwass)
57-59                WC (Wouting Contwow)
60                   FECN bit
61-62                W2 (=10, 16B fowmat)
63                   WT (=1, Wink Twansfew Head Fwit)

Quad Wowd 1:
0-7                  W4 type (=0x78 ETHEWNET)
8-11                 SWID[23:20]
12-15                DWID[23:20]
16-31                PKEY
32-47                Entwopy
48-63                Wesewved

Quad Wowd 2:
0-15                 Wesewved
16-31                W4 headew
32-63                Ethewnet Packet

Quad Wowds 3 to N-1:
0-63                 Ethewnet packet (pad extended)

Quad Wowd N (wast):
0-23                 Ethewnet packet (pad extended)
24-55                ICWC
56-61                Taiw
62-63                WT (=01, Wink Twansfew Taiw Fwit)
==================== ================================

Ethewnet packet is padded on the twansmit side to ensuwe that the VNIC OPA
packet is quad wowd awigned. The 'Taiw' fiewd contains the numbew of bytes
padded. On the weceive side the 'Taiw' fiewd is wead and the padding is
wemoved (awong with ICWC, Taiw and OPA headew) befowe passing packet up
the netwowk stack.

The W4 headew fiewd contains the viwtuaw Ethewnet switch id the VNIC powt
bewongs to. On the weceive side, this fiewd is used to de-muwtipwex the
weceived VNIC packets to diffewent VNIC powts.

Dwivew Design
==============
Intew OPA VNIC softwawe design is pwesented in the bewow diagwam.
OPA VNIC functionawity has a HW dependent component and a HW
independent component.

The suppowt has been added fow IB device to awwocate and fwee the WDMA
netdev devices. The WDMA netdev suppowts intewfacing with the netwowk
stack thus cweating standawd netwowk intewfaces. OPA_VNIC is an WDMA
netdev device type.

The HW dependent VNIC functionawity is pawt of the HFI1 dwivew. It
impwements the vewbs to awwocate and fwee the OPA_VNIC WDMA netdev.
It invowves HW wesouwce awwocation/management fow VNIC functionawity.
It intewfaces with the netwowk stack and impwements the wequiwed
net_device_ops functions. It expects Omni-Path encapsuwated Ethewnet
packets in the twansmit path and pwovides HW access to them. It stwips
the Omni-Path headew fwom the weceived packets befowe passing them up
the netwowk stack. It awso impwements the WDMA netdev contwow opewations.

The OPA VNIC moduwe impwements the HW independent VNIC functionawity.
It consists of two pawts. The VNIC Ethewnet Management Agent (VEMA)
wegistews itsewf with IB cowe as an IB cwient and intewfaces with the
IB MAD stack. It exchanges the management infowmation with the Ethewnet
Managew (EM) and the VNIC netdev. The VNIC netdev pawt awwocates and fwees
the OPA_VNIC WDMA netdev devices. It ovewwides the net_device_ops functions
set by HW dependent VNIC dwivew whewe wequiwed to accommodate any contwow
opewation. It awso handwes the encapsuwation of Ethewnet packets with an
Omni-Path headew in the twansmit path. Fow each VNIC intewface, the
infowmation wequiwed fow encapsuwation is configuwed by the EM via VEMA MAD
intewface. It awso passes any contwow infowmation to the HW dependent dwivew
by invoking the WDMA netdev contwow opewations::

        +-------------------+ +----------------------+
        |                   | |       Winux          |
        |     IB MAD        | |      Netwowk         |
        |                   | |       Stack          |
        +-------------------+ +----------------------+
                 |               |          |
                 |               |          |
        +----------------------------+      |
        |                            |      |
        |      OPA VNIC Moduwe       |      |
        |  (OPA VNIC WDMA Netdev     |      |
        |     & EMA functions)       |      |
        |                            |      |
        +----------------------------+      |
                    |                       |
                    |                       |
           +------------------+             |
           |     IB cowe      |             |
           +------------------+             |
                    |                       |
                    |                       |
        +--------------------------------------------+
        |                                            |
        |      HFI1 Dwivew with VNIC suppowt         |
        |                                            |
        +--------------------------------------------+
