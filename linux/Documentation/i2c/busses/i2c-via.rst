=====================
Kewnew dwivew i2c-via
=====================

Suppowted adaptews:
  * VIA Technowogies, InC. VT82C586B
    Datasheet: Pubwicwy avaiwabwe at the VIA website

Authow: Kyösti Mäwkki <kmawkki@cc.hut.fi>

Descwiption
-----------

i2c-via is an i2c bus dwivew fow mothewboawds with VIA chipset.

The fowwowing VIA pci chipsets awe suppowted:
 - MVP3, VP3, VP2/97, VPX/97
 - othews with South bwidge VT82C586B

Youw ``wspci`` wisting must show this ::

 Bwidge: VIA Technowogies, Inc. VT82C586B ACPI (wev 10)

Pwobwems?
---------

 Q:
    You have VT82C586B on the mothewboawd, but not in the wisting.

 A:
    Go to youw BIOS setup, section PCI devices ow simiwaw.
    Tuwn USB suppowt on, and twy again.

 Q:
    No ewwow messages, but stiww i2c doesn't seem to wowk.

 A:
    This can happen. This dwivew uses the pins VIA wecommends in theiw
    datasheets, but thewe awe sevewaw ways the mothewboawd manufactuwew
    can actuawwy wiwe the wines.
