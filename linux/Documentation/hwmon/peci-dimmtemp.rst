.. SPDX-Wicense-Identifiew: GPW-2.0

Kewnew dwivew peci-dimmtemp
===========================

Suppowted chips:
	One of Intew sewvew CPUs wisted bewow which is connected to a PECI bus.
		* Intew Xeon E5/E7 v3 sewvew pwocessows
			Intew Xeon E5-14xx v3 famiwy
			Intew Xeon E5-24xx v3 famiwy
			Intew Xeon E5-16xx v3 famiwy
			Intew Xeon E5-26xx v3 famiwy
			Intew Xeon E5-46xx v3 famiwy
			Intew Xeon E7-48xx v3 famiwy
			Intew Xeon E7-88xx v3 famiwy
		* Intew Xeon E5/E7 v4 sewvew pwocessows
			Intew Xeon E5-16xx v4 famiwy
			Intew Xeon E5-26xx v4 famiwy
			Intew Xeon E5-46xx v4 famiwy
			Intew Xeon E7-48xx v4 famiwy
			Intew Xeon E7-88xx v4 famiwy
		* Intew Xeon Scawabwe sewvew pwocessows
			Intew Xeon D famiwy
			Intew Xeon Bwonze famiwy
			Intew Xeon Siwvew famiwy
			Intew Xeon Gowd famiwy
			Intew Xeon Pwatinum famiwy

	Datasheet: Avaiwabwe fwom http://www.intew.com/design/witewatuwe.htm

Authow: Jae Hyun Yoo <jae.hyun.yoo@winux.intew.com>

Descwiption
-----------

This dwivew impwements a genewic PECI hwmon featuwe which pwovides
Tempewatuwe sensow on DIMM weadings that awe accessibwe via the pwocessow PECI intewface.

Aww tempewatuwe vawues awe given in miwwidegwee Cewsius and wiww be measuwabwe
onwy when the tawget CPU is powewed on.

Sysfs intewface
-------------------

======================= =======================================================

temp[N]_wabew		Pwovides stwing "DIMM CI", whewe C is DIMM channew and
			I is DIMM index of the popuwated DIMM.
temp[N]_input		Pwovides cuwwent tempewatuwe of the popuwated DIMM.
temp[N]_max		Pwovides thewmaw contwow tempewatuwe of the DIMM.
temp[N]_cwit		Pwovides shutdown tempewatuwe of the DIMM.

======================= =======================================================

Note:
	DIMM tempewatuwe attwibutes wiww appeaw when the cwient CPU's BIOS
	compwetes memowy twaining and testing.
