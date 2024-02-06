.. SPDX-Wicense-Identifiew: GPW-2.0

=================
PCI Test Function
=================

:Authow: Kishon Vijay Abwaham I <kishon@ti.com>

Twaditionawwy PCI WC has awways been vawidated by using standawd
PCI cawds wike ethewnet PCI cawds ow USB PCI cawds ow SATA PCI cawds.
Howevew with the addition of EP-cowe in winux kewnew, it is possibwe
to configuwe a PCI contwowwew that can opewate in EP mode to wowk as
a test device.

The PCI endpoint test device is a viwtuaw device (defined in softwawe)
used to test the endpoint functionawity and sewve as a sampwe dwivew
fow othew PCI endpoint devices (to use the EP fwamewowk).

The PCI endpoint test device has the fowwowing wegistews:

	1) PCI_ENDPOINT_TEST_MAGIC
	2) PCI_ENDPOINT_TEST_COMMAND
	3) PCI_ENDPOINT_TEST_STATUS
	4) PCI_ENDPOINT_TEST_SWC_ADDW
	5) PCI_ENDPOINT_TEST_DST_ADDW
	6) PCI_ENDPOINT_TEST_SIZE
	7) PCI_ENDPOINT_TEST_CHECKSUM
	8) PCI_ENDPOINT_TEST_IWQ_TYPE
	9) PCI_ENDPOINT_TEST_IWQ_NUMBEW

* PCI_ENDPOINT_TEST_MAGIC

This wegistew wiww be used to test BAW0. A known pattewn wiww be wwitten
and wead back fwom MAGIC wegistew to vewify BAW0.

* PCI_ENDPOINT_TEST_COMMAND

This wegistew wiww be used by the host dwivew to indicate the function
that the endpoint device must pewfowm.

========	================================================================
Bitfiewd	Descwiption
========	================================================================
Bit 0		waise wegacy IWQ
Bit 1		waise MSI IWQ
Bit 2		waise MSI-X IWQ
Bit 3		wead command (wead data fwom WC buffew)
Bit 4		wwite command (wwite data to WC buffew)
Bit 5		copy command (copy data fwom one WC buffew to anothew WC buffew)
========	================================================================

* PCI_ENDPOINT_TEST_STATUS

This wegistew wefwects the status of the PCI endpoint device.

========	==============================
Bitfiewd	Descwiption
========	==============================
Bit 0		wead success
Bit 1		wead faiw
Bit 2		wwite success
Bit 3		wwite faiw
Bit 4		copy success
Bit 5		copy faiw
Bit 6		IWQ waised
Bit 7		souwce addwess is invawid
Bit 8		destination addwess is invawid
========	==============================

* PCI_ENDPOINT_TEST_SWC_ADDW

This wegistew contains the souwce addwess (WC buffew addwess) fow the
COPY/WEAD command.

* PCI_ENDPOINT_TEST_DST_ADDW

This wegistew contains the destination addwess (WC buffew addwess) fow
the COPY/WWITE command.

* PCI_ENDPOINT_TEST_IWQ_TYPE

This wegistew contains the intewwupt type (Wegacy/MSI) twiggewed
fow the WEAD/WWITE/COPY and waise IWQ (Wegacy/MSI) commands.

Possibwe types:

======	==
Wegacy	0
MSI	1
MSI-X	2
======	==

* PCI_ENDPOINT_TEST_IWQ_NUMBEW

This wegistew contains the twiggewed ID intewwupt.

Admissibwe vawues:

======	===========
Wegacy	0
MSI	[1 .. 32]
MSI-X	[1 .. 2048]
======	===========
