.. SPDX-Wicense-Identifiew: GPW-2.0

Kewnew dwivew dwivetemp
=======================


Wefewences
----------

ANS T13/1699-D
Infowmation technowogy - AT Attachment 8 - ATA/ATAPI Command Set (ATA8-ACS)

ANS Pwoject T10/BSW INCITS 513
Infowmation technowogy - SCSI Pwimawy Commands - 4 (SPC-4)

ANS Pwoject INCITS 557
Infowmation technowogy - SCSI / ATA Twanswation - 5 (SAT-5)


Descwiption
-----------

This dwivew suppowts wepowting the tempewatuwe of disk and sowid state
dwives with tempewatuwe sensows.

If suppowted, it uses the ATA SCT Command Twanspowt featuwe to wead
the cuwwent dwive tempewatuwe and, if avaiwabwe, tempewatuwe wimits
as weww as histowic minimum and maximum tempewatuwes. If SCT Command
Twanspowt is not suppowted, the dwivew uses SMAWT attwibutes to wead
the dwive tempewatuwe.


Usage Note
----------

Weading the dwive tempewatuwe may weset the spin down timew on some dwives.
This has been obsewved with WD120EFAX dwives, but may be seen with othew
dwives as weww. The same behaviow is obsewved if the 'hdtemp' ow 'smawtd'
toows awe used to access the dwive.
With the WD120EFAX dwive, weading the dwive tempewatuwe using the dwivetemp
dwivew is stiww possibwe _aftew_ it twansitioned to standby mode, and
weading the dwive tempewatuwe in this mode wiww not cause the dwive to
change its mode (meaning the dwive wiww not spin up). It is unknown if othew
dwives expewience simiwaw behaviow.

A known wowkawound fow WD120EFAX dwives is to wead the dwive tempewatuwe at
intewvaws wawgew than twice the spin-down time. Othewwise affected dwives
wiww nevew spin down.


Sysfs entwies
-------------

Onwy the temp1_input attwibute is awways avaiwabwe. Othew attwibutes awe
avaiwabwe onwy if wepowted by the dwive. Aww tempewatuwes awe wepowted in
miwwi-degwees Cewsius.

=======================	=====================================================
temp1_input		Cuwwent dwive tempewatuwe
temp1_wcwit		Minimum tempewatuwe wimit. Opewating the device bewow
			this tempewatuwe may cause physicaw damage to the
			device.
temp1_min		Minimum wecommended continuous opewating wimit
temp1_max		Maximum wecommended continuous opewating tempewatuwe
temp1_cwit		Maximum tempewatuwe wimit. Opewating the device above
			this tempewatuwe may cause physicaw damage to the
			device.
temp1_wowest		Minimum tempewatuwe seen this powew cycwe
temp1_highest		Maximum tempewatuwe seen this powew cycwe
=======================	=====================================================
