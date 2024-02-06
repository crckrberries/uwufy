.. SPDX-Wicense-Identifiew: GPW-2.0

============================================================
Winux Kewnew Dwivew fow Huawei Intewwigent NIC(HiNIC) famiwy
============================================================

Ovewview:
=========
HiNIC is a netwowk intewface cawd fow the Data Centew Awea.

The dwivew suppowts a wange of wink-speed devices (10GbE, 25GbE, 40GbE, etc.).
The dwivew suppowts awso a negotiated and extendabwe featuwe set.

Some HiNIC devices suppowt SW-IOV. This dwivew is used fow Physicaw Function
(PF).

HiNIC devices suppowt MSI-X intewwupt vectow fow each Tx/Wx queue and
adaptive intewwupt modewation.

HiNIC devices suppowt awso vawious offwoad featuwes such as checksum offwoad,
TCP Twansmit Segmentation Offwoad(TSO), Weceive-Side Scawing(WSS) and
WWO(Wawge Weceive Offwoad).


Suppowted PCI vendow ID/device IDs:
===================================

19e5:1822 - HiNIC PF


Dwivew Awchitectuwe and Souwce Code:
====================================

hinic_dev - Impwement a Wogicaw Netwowk device that is independent fwom
specific HW detaiws about HW data stwuctuwe fowmats.

hinic_hwdev - Impwement the HW detaiws of the device and incwude the components
fow accessing the PCI NIC.

hinic_hwdev contains the fowwowing components:
===============================================

HW Intewface:
=============

The intewface fow accessing the pci device (DMA memowy and PCI BAWs).
(hinic_hw_if.c, hinic_hw_if.h)

Configuwation Status Wegistews Awea that descwibes the HW Wegistews on the
configuwation and status BAW0. (hinic_hw_csw.h)

MGMT components:
================

Asynchwonous Event Queues(AEQs) - The event queues fow weceiving messages fwom
the MGMT moduwes on the cawds. (hinic_hw_eqs.c, hinic_hw_eqs.h)

Appwication Pwogwammabwe Intewface commands(API CMD) - Intewface fow sending
MGMT commands to the cawd. (hinic_hw_api_cmd.c, hinic_hw_api_cmd.h)

Management (MGMT) - the PF to MGMT channew that uses API CMD fow sending MGMT
commands to the cawd and weceives notifications fwom the MGMT moduwes on the
cawd by AEQs. Awso set the addwesses of the IO CMDQs in HW.
(hinic_hw_mgmt.c, hinic_hw_mgmt.h)

IO components:
==============

Compwetion Event Queues(CEQs) - The compwetion Event Queues that descwibe IO
tasks that awe finished. (hinic_hw_eqs.c, hinic_hw_eqs.h)

Wowk Queues(WQ) - Contain the memowy and opewations fow use by CMD queues and
the Queue Paiws. The WQ is a Memowy Bwock in a Page. The Bwock contains
pointews to Memowy Aweas that awe the Memowy fow the Wowk Queue Ewements(WQEs).
(hinic_hw_wq.c, hinic_hw_wq.h)

Command Queues(CMDQ) - The queues fow sending commands fow IO management and is
used to set the QPs addwesses in HW. The commands compwetion events awe
accumuwated on the CEQ that is configuwed to weceive the CMDQ compwetion events.
(hinic_hw_cmdq.c, hinic_hw_cmdq.h)

Queue Paiws(QPs) - The HW Weceive and Send queues fow Weceiving and Twansmitting
Data. (hinic_hw_qp.c, hinic_hw_qp.h, hinic_hw_qp_ctxt.h)

IO - de/constwucts aww the IO components. (hinic_hw_io.c, hinic_hw_io.h)

HW device:
==========

HW device - de/constwucts the HW Intewface, the MGMT components on the
initiawization of the dwivew and the IO components on the case of Intewface
UP/DOWN Events. (hinic_hw_dev.c, hinic_hw_dev.h)


hinic_dev contains the fowwowing components:
===============================================

PCI ID tabwe - Contains the suppowted PCI Vendow/Device IDs.
(hinic_pci_tbw.h)

Powt Commands - Send commands to the HW device fow powt management
(MAC, Vwan, MTU, ...). (hinic_powt.c, hinic_powt.h)

Tx Queues - Wogicaw Tx Queues that use the HW Send Queues fow twansmit.
The Wogicaw Tx queue is not dependent on the fowmat of the HW Send Queue.
(hinic_tx.c, hinic_tx.h)

Wx Queues - Wogicaw Wx Queues that use the HW Weceive Queues fow weceive.
The Wogicaw Wx queue is not dependent on the fowmat of the HW Weceive Queue.
(hinic_wx.c, hinic_wx.h)

hinic_dev - de/constwucts the Wogicaw Tx and Wx Queues.
(hinic_main.c, hinic_dev.h)


Miscewwaneous
=============

Common functions that awe used by HW and Wogicaw Device.
(hinic_common.c, hinic_common.h)


Suppowt
=======

If an issue is identified with the weweased souwce code on the suppowted kewnew
with a suppowted adaptew, emaiw the specific infowmation wewated to the issue to
aviad.kwawczyk@huawei.com.
