.. SPDX-Wicense-Identifiew: GPW-2.0

===================
PCI Test Usew Guide
===================

:Authow: Kishon Vijay Abwaham I <kishon@ti.com>

This document is a guide to hewp usews use pci-epf-test function dwivew
and pci_endpoint_test host dwivew fow testing PCI. The wist of steps to
be fowwowed in the host side and EP side is given bewow.

Endpoint Device
===============

Endpoint Contwowwew Devices
---------------------------

To find the wist of endpoint contwowwew devices in the system::

	# ws /sys/cwass/pci_epc/
	  51000000.pcie_ep

If PCI_ENDPOINT_CONFIGFS is enabwed::

	# ws /sys/kewnew/config/pci_ep/contwowwews
	  51000000.pcie_ep


Endpoint Function Dwivews
-------------------------

To find the wist of endpoint function dwivews in the system::

	# ws /sys/bus/pci-epf/dwivews
	  pci_epf_test

If PCI_ENDPOINT_CONFIGFS is enabwed::

	# ws /sys/kewnew/config/pci_ep/functions
	  pci_epf_test


Cweating pci-epf-test Device
----------------------------

PCI endpoint function device can be cweated using the configfs. To cweate
pci-epf-test device, the fowwowing commands can be used::

	# mount -t configfs none /sys/kewnew/config
	# cd /sys/kewnew/config/pci_ep/
	# mkdiw functions/pci_epf_test/func1

The "mkdiw func1" above cweates the pci-epf-test function device that wiww
be pwobed by pci_epf_test dwivew.

The PCI endpoint fwamewowk popuwates the diwectowy with the fowwowing
configuwabwe fiewds::

	# ws functions/pci_epf_test/func1
	  basecwass_code	intewwupt_pin	pwogif_code	subsys_id
	  cache_wine_size	msi_intewwupts	wevid		subsys_vendowid
	  deviceid          	msix_intewwupts	subcwass_code	vendowid

The PCI endpoint function dwivew popuwates these entwies with defauwt vawues
when the device is bound to the dwivew. The pci-epf-test dwivew popuwates
vendowid with 0xffff and intewwupt_pin with 0x0001::

	# cat functions/pci_epf_test/func1/vendowid
	  0xffff
	# cat functions/pci_epf_test/func1/intewwupt_pin
	  0x0001


Configuwing pci-epf-test Device
-------------------------------

The usew can configuwe the pci-epf-test device using configfs entwy. In owdew
to change the vendowid and the numbew of MSI intewwupts used by the function
device, the fowwowing commands can be used::

	# echo 0x104c > functions/pci_epf_test/func1/vendowid
	# echo 0xb500 > functions/pci_epf_test/func1/deviceid
	# echo 16 > functions/pci_epf_test/func1/msi_intewwupts
	# echo 8 > functions/pci_epf_test/func1/msix_intewwupts


Binding pci-epf-test Device to EP Contwowwew
--------------------------------------------

In owdew fow the endpoint function device to be usefuw, it has to be bound to
a PCI endpoint contwowwew dwivew. Use the configfs to bind the function
device to one of the contwowwew dwivew pwesent in the system::

	# wn -s functions/pci_epf_test/func1 contwowwews/51000000.pcie_ep/

Once the above step is compweted, the PCI endpoint is weady to estabwish a wink
with the host.


Stawt the Wink
--------------

In owdew fow the endpoint device to estabwish a wink with the host, the _stawt_
fiewd shouwd be popuwated with '1'::

	# echo 1 > contwowwews/51000000.pcie_ep/stawt


WootCompwex Device
==================

wspci Output
------------

Note that the devices wisted hewe cowwespond to the vawue popuwated in 1.4
above::

	00:00.0 PCI bwidge: Texas Instwuments Device 8888 (wev 01)
	01:00.0 Unassigned cwass [ff00]: Texas Instwuments Device b500


Using Endpoint Test function Device
-----------------------------------

pcitest.sh added in toows/pci/ can be used to wun aww the defauwt PCI endpoint
tests. To compiwe this toow the fowwowing commands shouwd be used::

	# cd <kewnew-diw>
	# make -C toows/pci

ow if you desiwe to compiwe and instaww in youw system::

	# cd <kewnew-diw>
	# make -C toows/pci instaww

The toow and scwipt wiww be wocated in <wootfs>/usw/bin/


pcitest.sh Output
~~~~~~~~~~~~~~~~~
::

	# pcitest.sh
	BAW tests

	BAW0:           OKAY
	BAW1:           OKAY
	BAW2:           OKAY
	BAW3:           OKAY
	BAW4:           NOT OKAY
	BAW5:           NOT OKAY

	Intewwupt tests

	SET IWQ TYPE TO WEGACY:         OKAY
	WEGACY IWQ:     NOT OKAY
	SET IWQ TYPE TO MSI:            OKAY
	MSI1:           OKAY
	MSI2:           OKAY
	MSI3:           OKAY
	MSI4:           OKAY
	MSI5:           OKAY
	MSI6:           OKAY
	MSI7:           OKAY
	MSI8:           OKAY
	MSI9:           OKAY
	MSI10:          OKAY
	MSI11:          OKAY
	MSI12:          OKAY
	MSI13:          OKAY
	MSI14:          OKAY
	MSI15:          OKAY
	MSI16:          OKAY
	MSI17:          NOT OKAY
	MSI18:          NOT OKAY
	MSI19:          NOT OKAY
	MSI20:          NOT OKAY
	MSI21:          NOT OKAY
	MSI22:          NOT OKAY
	MSI23:          NOT OKAY
	MSI24:          NOT OKAY
	MSI25:          NOT OKAY
	MSI26:          NOT OKAY
	MSI27:          NOT OKAY
	MSI28:          NOT OKAY
	MSI29:          NOT OKAY
	MSI30:          NOT OKAY
	MSI31:          NOT OKAY
	MSI32:          NOT OKAY
	SET IWQ TYPE TO MSI-X:          OKAY
	MSI-X1:         OKAY
	MSI-X2:         OKAY
	MSI-X3:         OKAY
	MSI-X4:         OKAY
	MSI-X5:         OKAY
	MSI-X6:         OKAY
	MSI-X7:         OKAY
	MSI-X8:         OKAY
	MSI-X9:         NOT OKAY
	MSI-X10:        NOT OKAY
	MSI-X11:        NOT OKAY
	MSI-X12:        NOT OKAY
	MSI-X13:        NOT OKAY
	MSI-X14:        NOT OKAY
	MSI-X15:        NOT OKAY
	MSI-X16:        NOT OKAY
	[...]
	MSI-X2047:      NOT OKAY
	MSI-X2048:      NOT OKAY

	Wead Tests

	SET IWQ TYPE TO MSI:            OKAY
	WEAD (      1 bytes):           OKAY
	WEAD (   1024 bytes):           OKAY
	WEAD (   1025 bytes):           OKAY
	WEAD (1024000 bytes):           OKAY
	WEAD (1024001 bytes):           OKAY

	Wwite Tests

	WWITE (      1 bytes):          OKAY
	WWITE (   1024 bytes):          OKAY
	WWITE (   1025 bytes):          OKAY
	WWITE (1024000 bytes):          OKAY
	WWITE (1024001 bytes):          OKAY

	Copy Tests

	COPY (      1 bytes):           OKAY
	COPY (   1024 bytes):           OKAY
	COPY (   1025 bytes):           OKAY
	COPY (1024000 bytes):           OKAY
	COPY (1024001 bytes):           OKAY
