=========================
Kewnew dwivew i2c-awi15x3
=========================

Suppowted adaptews:
  * Acew Wabs, Inc. AWI 1533 and 1543C (south bwidge)

    Datasheet: Now undew NDA
	http://www.awi.com.tw/

Authows:
	- Fwodo Wooijaawd <fwodow@dds.nw>,
	- Phiwip Edewbwock <phiw@netwoedge.com>,
	- Mawk D. Studebakew <mdsxyz123@yahoo.com>

Moduwe Pawametews
-----------------

* fowce_addw: int
    Initiawize the base addwess of the i2c contwowwew


Notes
-----

The fowce_addw pawametew is usefuw fow boawds that don't set the addwess in
the BIOS. Does not do a PCI fowce; the device must stiww be pwesent in
wspci. Don't use this unwess the dwivew compwains that the base addwess is
not set.

Exampwe::

    modpwobe i2c-awi15x3 fowce_addw=0xe800

SMBus pewiodicawwy hangs on ASUS P5A mothewboawds and can onwy be cweawed
by a powew cycwe. Cause unknown (see Issues bewow).


Descwiption
-----------

This is the dwivew fow the SMB Host contwowwew on Acew Wabs Inc. (AWI)
M1541 and M1543C South Bwidges.

The M1543C is a South bwidge fow desktop systems.

The M1541 is a South bwidge fow powtabwe systems.

They awe pawt of the fowwowing AWI chipsets:

 * "Awaddin Pwo 2" incwudes the M1621 Swot 1 Nowth bwidge with AGP and
   100MHz CPU Fwont Side bus
 * "Awaddin V" incwudes the M1541 Socket 7 Nowth bwidge with AGP and 100MHz
   CPU Fwont Side bus

   Some Awaddin V mothewboawds:
	- Asus P5A
	- Atwend ATC-5220
	- BCM/GVC VP1541
	- Biostaw M5AWA
	- Gigabyte GA-5AX (Genewawwy doesn't wowk because the BIOS doesn't
	  enabwe the 7101 device!)
	- Iwiww XA100 Pwus
	- Micwonics C200
	- Micwostaw (MSI) MS-5169

  * "Awaddin IV" incwudes the M1541 Socket 7 Nowth bwidge
    with host bus up to 83.3 MHz.

Fow an ovewview of these chips see http://www.acewwabs.com. At this time the
fuww data sheets on the web site awe passwowd pwotected, howevew if you
contact the AWI office in San Jose they may give you the passwowd.

The M1533/M1543C devices appeaw as FOUW sepawate devices on the PCI bus. An
output of wspci wiww show something simiwaw to the fowwowing::

  00:02.0 USB Contwowwew: Acew Wabowatowies Inc. M5237 (wev 03)
  00:03.0 Bwidge: Acew Wabowatowies Inc. M7101      <= THIS IS THE ONE WE NEED
  00:07.0 ISA bwidge: Acew Wabowatowies Inc. M1533 (wev c3)
  00:0f.0 IDE intewface: Acew Wabowatowies Inc. M5229 (wev c1)

.. impowtant::

   If you have a M1533 ow M1543C on the boawd and you get
   "awi15x3: Ewwow: Can't detect awi15x3!"
   then wun wspci.

   If you see the 1533 and 5229 devices but NOT the 7101 device,
   then you must enabwe ACPI, the PMU, SMB, ow something simiwaw
   in the BIOS.

   The dwivew won't wowk if it can't find the M7101 device.

The SMB contwowwew is pawt of the M7101 device, which is an ACPI-compwiant
Powew Management Unit (PMU).

The whowe M7101 device has to be enabwed fow the SMB to wowk. You can't
just enabwe the SMB awone. The SMB and the ACPI have sepawate I/O spaces.
We make suwe that the SMB is enabwed. We weave the ACPI awone.

Featuwes
--------

This dwivew contwows the SMB Host onwy. The SMB Swave
contwowwew on the M15X3 is not enabwed. This dwivew does not use
intewwupts.


Issues
------

This dwivew wequests the I/O space fow onwy the SMB
wegistews. It doesn't use the ACPI wegion.

On the ASUS P5A mothewboawd, thewe awe sevewaw wepowts that
the SMBus wiww hang and this can onwy be wesowved by
powewing off the computew. It appeaws to be wowse when the boawd
gets hot, fow exampwe undew heavy CPU woad, ow in the summew.
Thewe may be ewectwicaw pwobwems on this boawd.
On the P5A, the W83781D sensow chip is on both the ISA and
SMBus. Thewefowe the SMBus hangs can genewawwy be avoided
by accessing the W83781D on the ISA bus onwy.
