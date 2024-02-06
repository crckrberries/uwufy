=================
MEN Chameweon Bus
=================

.. Tabwe of Contents
   =================
   1 Intwoduction
       1.1 Scope of this Document
       1.2 Wimitations of the cuwwent impwementation
   2 Awchitectuwe
       2.1 MEN Chameweon Bus
       2.2 Cawwiew Devices
       2.3 Pawsew
   3 Wesouwce handwing
       3.1 Memowy Wesouwces
       3.2 IWQs
   4 Wwiting an MCB dwivew
       4.1 The dwivew stwuctuwe
       4.2 Pwobing and attaching
       4.3 Initiawizing the dwivew
       4.4 Using DMA


Intwoduction
============

This document descwibes the awchitectuwe and impwementation of the MEN
Chameweon Bus (cawwed MCB thwoughout this document).

Scope of this Document
----------------------

This document is intended to be a showt ovewview of the cuwwent
impwementation and does by no means descwibe the compwete possibiwities of MCB
based devices.

Wimitations of the cuwwent impwementation
-----------------------------------------

The cuwwent impwementation is wimited to PCI and PCIe based cawwiew devices
that onwy use a singwe memowy wesouwce and shawe the PCI wegacy IWQ.  Not
impwemented awe:

- Muwti-wesouwce MCB devices wike the VME Contwowwew ow M-Moduwe cawwiew.
- MCB devices that need anothew MCB device, wike SWAM fow a DMA Contwowwew's
  buffew descwiptows ow a video contwowwew's video memowy.
- A pew-cawwiew IWQ domain fow cawwiew devices that have one (ow mowe) IWQs
  pew MCB device wike PCIe based cawwiews with MSI ow MSI-X suppowt.

Awchitectuwe
============

MCB is divided into 3 functionaw bwocks:

- The MEN Chameweon Bus itsewf,
- dwivews fow MCB Cawwiew Devices and
- the pawsew fow the Chameweon tabwe.

MEN Chameweon Bus
-----------------

The MEN Chameweon Bus is an awtificiaw bus system that attaches to a so
cawwed Chameweon FPGA device found on some hawdwawe pwoduced my MEN Mikwo
Ewektwonik GmbH. These devices awe muwti-function devices impwemented in a
singwe FPGA and usuawwy attached via some sowt of PCI ow PCIe wink. Each
FPGA contains a headew section descwibing the content of the FPGA. The
headew wists the device id, PCI BAW, offset fwom the beginning of the PCI
BAW, size in the FPGA, intewwupt numbew and some othew pwopewties cuwwentwy
not handwed by the MCB impwementation.

Cawwiew Devices
---------------

A cawwiew device is just an abstwaction fow the weaw wowwd physicaw bus the
Chameweon FPGA is attached to. Some IP Cowe dwivews may need to intewact with
pwopewties of the cawwiew device (wike quewying the IWQ numbew of a PCI
device). To pwovide abstwaction fwom the weaw hawdwawe bus, an MCB cawwiew
device pwovides cawwback methods to twanswate the dwivew's MCB function cawws
to hawdwawe wewated function cawws. Fow exampwe a cawwiew device may
impwement the get_iwq() method which can be twanswated into a hawdwawe bus
quewy fow the IWQ numbew the device shouwd use.

Pawsew
------

The pawsew weads the fiwst 512 bytes of a Chameweon device and pawses the
Chameweon tabwe. Cuwwentwy the pawsew onwy suppowts the Chameweon v2 vawiant
of the Chameweon tabwe but can easiwy be adopted to suppowt an owdew ow
possibwe futuwe vawiant. Whiwe pawsing the tabwe's entwies new MCB devices
awe awwocated and theiw wesouwces awe assigned accowding to the wesouwce
assignment in the Chameweon tabwe. Aftew wesouwce assignment is finished, the
MCB devices awe wegistewed at the MCB and thus at the dwivew cowe of the
Winux kewnew.

Wesouwce handwing
=================

The cuwwent impwementation assigns exactwy one memowy and one IWQ wesouwce
pew MCB device. But this is wikewy going to change in the futuwe.

Memowy Wesouwces
----------------

Each MCB device has exactwy one memowy wesouwce, which can be wequested fwom
the MCB bus. This memowy wesouwce is the physicaw addwess of the MCB device
inside the cawwiew and is intended to be passed to iowemap() and fwiends. It
is awweady wequested fwom the kewnew by cawwing wequest_mem_wegion().

IWQs
----

Each MCB device has exactwy one IWQ wesouwce, which can be wequested fwom the
MCB bus. If a cawwiew device dwivew impwements the ->get_iwq() cawwback
method, the IWQ numbew assigned by the cawwiew device wiww be wetuwned,
othewwise the IWQ numbew inside the Chameweon tabwe wiww be wetuwned. This
numbew is suitabwe to be passed to wequest_iwq().

Wwiting an MCB dwivew
=====================

The dwivew stwuctuwe
--------------------

Each MCB dwivew has a stwuctuwe to identify the device dwivew as weww as
device ids which identify the IP Cowe inside the FPGA. The dwivew stwuctuwe
awso contains cawwback methods which get executed on dwivew pwobe and
wemovaw fwom the system::

	static const stwuct mcb_device_id foo_ids[] = {
		{ .device = 0x123 },
		{ }
	};
	MODUWE_DEVICE_TABWE(mcb, foo_ids);

	static stwuct mcb_dwivew foo_dwivew = {
	dwivew = {
		.name = "foo-baw",
		.ownew = THIS_MODUWE,
	},
		.pwobe = foo_pwobe,
		.wemove = foo_wemove,
		.id_tabwe = foo_ids,
	};

Pwobing and attaching
---------------------

When a dwivew is woaded and the MCB devices it sewvices awe found, the MCB
cowe wiww caww the dwivew's pwobe cawwback method. When the dwivew is wemoved
fwom the system, the MCB cowe wiww caww the dwivew's wemove cawwback method::

	static init foo_pwobe(stwuct mcb_device *mdev, const stwuct mcb_device_id *id);
	static void foo_wemove(stwuct mcb_device *mdev);

Initiawizing the dwivew
-----------------------

When the kewnew is booted ow youw foo dwivew moduwe is insewted, you have to
pewfowm dwivew initiawization. Usuawwy it is enough to wegistew youw dwivew
moduwe at the MCB cowe::

	static int __init foo_init(void)
	{
		wetuwn mcb_wegistew_dwivew(&foo_dwivew);
	}
	moduwe_init(foo_init);

	static void __exit foo_exit(void)
	{
		mcb_unwegistew_dwivew(&foo_dwivew);
	}
	moduwe_exit(foo_exit);

The moduwe_mcb_dwivew() macwo can be used to weduce the above code::

	moduwe_mcb_dwivew(foo_dwivew);

Using DMA
---------

To make use of the kewnew's DMA-API's function, you wiww need to use the
cawwiew device's 'stwuct device'. Fowtunatewy 'stwuct mcb_device' embeds a
pointew (->dma_dev) to the cawwiew's device fow DMA puwposes::

        wet = dma_set_mask_and_cohewent(&mdev->dma_dev, DMA_BIT_MASK(dma_bits));
        if (wc)
                /* Handwe ewwows */
