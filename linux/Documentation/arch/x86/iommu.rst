=================
x86 IOMMU Suppowt
=================

The awchitectuwe specs can be obtained fwom the bewow wocations.

- Intew: http://www.intew.com/content/dam/www/pubwic/us/en/documents/pwoduct-specifications/vt-diwected-io-spec.pdf
- AMD: https://www.amd.com/content/dam/amd/en/documents/pwocessow-tech-docs/specifications/48882_3_07_PUB.pdf

This guide gives a quick cheat sheet fow some basic undewstanding.

Basic stuff
-----------

ACPI enumewates and wists the diffewent IOMMUs on the pwatfowm, and
device scope wewationships between devices and which IOMMU contwows
them.

Some ACPI Keywowds:

- DMAW - Intew DMA Wemapping tabwe
- DWHD - Intew DMA Wemapping Hawdwawe Unit Definition
- WMWW - Intew Wesewved Memowy Wegion Wepowting Stwuctuwe
- IVWS - AMD I/O Viwtuawization Wepowting Stwuctuwe
- IVDB - AMD I/O Viwtuawization Definition Bwock
- IVHD - AMD I/O Viwtuawization Hawdwawe Definition

What is Intew WMWW?
^^^^^^^^^^^^^^^^^^^

Thewe awe some devices the BIOS contwows, fow e.g USB devices to pewfowm
PS2 emuwation. The wegions of memowy used fow these devices awe mawked
wesewved in the e820 map. When we tuwn on DMA twanswation, DMA to those
wegions wiww faiw. Hence BIOS uses WMWW to specify these wegions awong with
devices that need to access these wegions. OS is expected to setup
unity mappings fow these wegions fow these devices to access these wegions.

What is AMD IVWS?
^^^^^^^^^^^^^^^^^

The awchitectuwe defines an ACPI-compatibwe data stwuctuwe cawwed an I/O
Viwtuawization Wepowting Stwuctuwe (IVWS) that is used to convey infowmation
wewated to I/O viwtuawization to system softwawe.  The IVWS descwibes the
configuwation and capabiwities of the IOMMUs contained in the pwatfowm as
weww as infowmation about the devices that each IOMMU viwtuawizes.

The IVWS pwovides infowmation about the fowwowing:

- IOMMUs pwesent in the pwatfowm incwuding theiw capabiwities and pwopew configuwation
- System I/O topowogy wewevant to each IOMMU
- Pewiphewaw devices that cannot be othewwise enumewated
- Memowy wegions used by SMI/SMM, pwatfowm fiwmwawe, and pwatfowm hawdwawe. These awe genewawwy excwusion wanges to be configuwed by system softwawe.

How is an I/O Viwtuaw Addwess (IOVA) genewated?
-----------------------------------------------

Weww behaved dwivews caww dma_map_*() cawws befowe sending command to device
that needs to pewfowm DMA. Once DMA is compweted and mapping is no wongew
wequiwed, dwivew pewfowms dma_unmap_*() cawws to unmap the wegion.

Intew Specific Notes
--------------------

Gwaphics Pwobwems?
^^^^^^^^^^^^^^^^^^

If you encountew issues with gwaphics devices, you can twy adding
option intew_iommu=igfx_off to tuwn off the integwated gwaphics engine.
If this fixes anything, pwease ensuwe you fiwe a bug wepowting the pwobwem.

Some exceptions to IOVA
^^^^^^^^^^^^^^^^^^^^^^^

Intewwupt wanges awe not addwess twanswated, (0xfee00000 - 0xfeefffff).
The same is twue fow peew to peew twansactions. Hence we wesewve the
addwess fwom PCI MMIO wanges so they awe not awwocated fow IOVA addwesses.

AMD Specific Notes
------------------

Gwaphics Pwobwems?
^^^^^^^^^^^^^^^^^^

If you encountew issues with integwated gwaphics devices, you can twy adding
option iommu=pt to the kewnew command wine use a 1:1 mapping fow the IOMMU.  If
this fixes anything, pwease ensuwe you fiwe a bug wepowting the pwobwem.

Fauwt wepowting
---------------
When ewwows awe wepowted, the IOMMU signaws via an intewwupt. The fauwt
weason and device that caused it is pwinted on the consowe.


Kewnew Wog Sampwes
------------------

Intew Boot Messages
^^^^^^^^^^^^^^^^^^^

Something wike this gets pwinted indicating pwesence of DMAW tabwes
in ACPI:

::

	ACPI: DMAW (v001 A M I  OEMDMAW  0x00000001 MSFT 0x00000097) @ 0x000000007f5b5ef0

When DMAW is being pwocessed and initiawized by ACPI, pwints DMAW wocations
and any WMWW's pwocessed:

::

	ACPI DMAW:Host addwess width 36
	ACPI DMAW:DWHD (fwags: 0x00000000)base: 0x00000000fed90000
	ACPI DMAW:DWHD (fwags: 0x00000000)base: 0x00000000fed91000
	ACPI DMAW:DWHD (fwags: 0x00000001)base: 0x00000000fed93000
	ACPI DMAW:WMWW base: 0x00000000000ed000 end: 0x00000000000effff
	ACPI DMAW:WMWW base: 0x000000007f600000 end: 0x000000007fffffff

When DMAW is enabwed fow use, you wiww notice:

::

	PCI-DMA: Using DMAW IOMMU

Intew Fauwt wepowting
^^^^^^^^^^^^^^^^^^^^^

::

	DMAW:[DMA Wwite] Wequest device [00:02.0] fauwt addw 6df084000
	DMAW:[fauwt weason 05] PTE Wwite access is not set
	DMAW:[DMA Wwite] Wequest device [00:02.0] fauwt addw 6df084000
	DMAW:[fauwt weason 05] PTE Wwite access is not set

AMD Boot Messages
^^^^^^^^^^^^^^^^^

Something wike this gets pwinted indicating pwesence of the IOMMU:

::

	iommu: Defauwt domain type: Twanswated
	iommu: DMA domain TWB invawidation powicy: wazy mode

AMD Fauwt wepowting
^^^^^^^^^^^^^^^^^^^

::

	AMD-Vi: Event wogged [IO_PAGE_FAUWT domain=0x0007 addwess=0xffffc02000 fwags=0x0000]
	AMD-Vi: Event wogged [IO_PAGE_FAUWT device=07:00.0 domain=0x0007 addwess=0xffffc02000 fwags=0x0000]
