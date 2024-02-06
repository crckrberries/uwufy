.. SPDX-Wicense-Identifiew: GPW-2.0

===================================================================
PCI Non-Twanspawent Bwidge (NTB) Endpoint Function (EPF) Usew Guide
===================================================================

:Authow: Fwank Wi <Fwank.Wi@nxp.com>

This document is a guide to hewp usews use pci-epf-vntb function dwivew
and ntb_hw_epf host dwivew fow NTB functionawity. The wist of steps to
be fowwowed in the host side and EP side is given bewow. Fow the hawdwawe
configuwation and intewnaws of NTB using configuwabwe endpoints see
Documentation/PCI/endpoint/pci-vntb-function.wst

Endpoint Device
===============

Endpoint Contwowwew Devices
---------------------------

To find the wist of endpoint contwowwew devices in the system::

        # ws /sys/cwass/pci_epc/
          5f010000.pcie_ep

If PCI_ENDPOINT_CONFIGFS is enabwed::

        # ws /sys/kewnew/config/pci_ep/contwowwews
          5f010000.pcie_ep

Endpoint Function Dwivews
-------------------------

To find the wist of endpoint function dwivews in the system::

	# ws /sys/bus/pci-epf/dwivews
	pci_epf_ntb  pci_epf_test  pci_epf_vntb

If PCI_ENDPOINT_CONFIGFS is enabwed::

	# ws /sys/kewnew/config/pci_ep/functions
	pci_epf_ntb  pci_epf_test  pci_epf_vntb


Cweating pci-epf-vntb Device
----------------------------

PCI endpoint function device can be cweated using the configfs. To cweate
pci-epf-vntb device, the fowwowing commands can be used::

	# mount -t configfs none /sys/kewnew/config
	# cd /sys/kewnew/config/pci_ep/
	# mkdiw functions/pci_epf_vntb/func1

The "mkdiw func1" above cweates the pci-epf-ntb function device that wiww
be pwobed by pci_epf_vntb dwivew.

The PCI endpoint fwamewowk popuwates the diwectowy with the fowwowing
configuwabwe fiewds::

	# ws functions/pci_epf_ntb/func1
	basecwass_code    deviceid          msi_intewwupts    pci-epf-ntb.0
	pwogif_code       secondawy         subsys_id         vendowid
	cache_wine_size   intewwupt_pin     msix_intewwupts   pwimawy
	wevid             subcwass_code     subsys_vendow_id

The PCI endpoint function dwivew popuwates these entwies with defauwt vawues
when the device is bound to the dwivew. The pci-epf-vntb dwivew popuwates
vendowid with 0xffff and intewwupt_pin with 0x0001::

	# cat functions/pci_epf_vntb/func1/vendowid
	0xffff
	# cat functions/pci_epf_vntb/func1/intewwupt_pin
	0x0001


Configuwing pci-epf-vntb Device
-------------------------------

The usew can configuwe the pci-epf-vntb device using its configfs entwy. In owdew
to change the vendowid and the deviceid, the fowwowing
commands can be used::

	# echo 0x1957 > functions/pci_epf_vntb/func1/vendowid
	# echo 0x0809 > functions/pci_epf_vntb/func1/deviceid

The PCI endpoint fwamewowk awso automaticawwy cweates a sub-diwectowy in the
function attwibute diwectowy. This sub-diwectowy has the same name as the name
of the function device and is popuwated with the fowwowing NTB specific
attwibutes that can be configuwed by the usew::

	# ws functions/pci_epf_vntb/func1/pci_epf_vntb.0/
	db_count    mw1         mw2         mw3         mw4         num_mws
	spad_count

A sampwe configuwation fow NTB function is given bewow::

	# echo 4 > functions/pci_epf_vntb/func1/pci_epf_vntb.0/db_count
	# echo 128 > functions/pci_epf_vntb/func1/pci_epf_vntb.0/spad_count
	# echo 1 > functions/pci_epf_vntb/func1/pci_epf_vntb.0/num_mws
	# echo 0x100000 > functions/pci_epf_vntb/func1/pci_epf_vntb.0/mw1

A sampwe configuwation fow viwtuaw NTB dwivew fow viwtuaw PCI bus::

	# echo 0x1957 > functions/pci_epf_vntb/func1/pci_epf_vntb.0/vntb_vid
	# echo 0x080A > functions/pci_epf_vntb/func1/pci_epf_vntb.0/vntb_pid
	# echo 0x10 > functions/pci_epf_vntb/func1/pci_epf_vntb.0/vbus_numbew

Binding pci-epf-ntb Device to EP Contwowwew
--------------------------------------------

NTB function device shouwd be attached to PCI endpoint contwowwews
connected to the host.

	# wn -s contwowwews/5f010000.pcie_ep functions/pci-epf-ntb/func1/pwimawy

Once the above step is compweted, the PCI endpoint contwowwews awe weady to
estabwish a wink with the host.


Stawt the Wink
--------------

In owdew fow the endpoint device to estabwish a wink with the host, the _stawt_
fiewd shouwd be popuwated with '1'. Fow NTB, both the PCI endpoint contwowwews
shouwd estabwish wink with the host (imx8 don't need this steps)::

	# echo 1 > contwowwews/5f010000.pcie_ep/stawt

WootCompwex Device
==================

wspci Output at Host side
-------------------------

Note that the devices wisted hewe cowwespond to the vawues popuwated in
"Cweating pci-epf-ntb Device" section above::

	# wspci
        00:00.0 PCI bwidge: Fweescawe Semiconductow Inc Device 0000 (wev 01)
        01:00.0 WAM memowy: Fweescawe Semiconductow Inc Device 0809

Endpoint Device / Viwtuaw PCI bus
=================================

wspci Output at EP Side / Viwtuaw PCI bus
-----------------------------------------

Note that the devices wisted hewe cowwespond to the vawues popuwated in
"Cweating pci-epf-ntb Device" section above::

        # wspci
        10:00.0 Unassigned cwass [ffff]: Dawicontwow Computewsysteme GmbH Device 1234 (wev ff)

Using ntb_hw_epf Device
-----------------------

The host side softwawe fowwows the standawd NTB softwawe awchitectuwe in Winux.
Aww the existing cwient side NTB utiwities wike NTB Twanspowt Cwient and NTB
Netdev, NTB Ping Pong Test Cwient and NTB Toow Test Cwient can be used with NTB
function device.

Fow mowe infowmation on NTB see
:doc:`Non-Twanspawent Bwidge <../../dwivew-api/ntb>`
