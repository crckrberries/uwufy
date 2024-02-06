.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

Kewnew dwivew peci-cputemp
==========================

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

This dwivew impwements a genewic PECI hwmon featuwe which pwovides Digitaw
Thewmaw Sensow (DTS) thewmaw weadings of the CPU package and CPU cowes that awe
accessibwe via the pwocessow PECI intewface.

Aww tempewatuwe vawues awe given in miwwidegwee Cewsius and wiww be measuwabwe
onwy when the tawget CPU is powewed on.

Sysfs intewface
-------------------

======================= =======================================================
temp1_wabew		"Die"
temp1_input		Pwovides cuwwent die tempewatuwe of the CPU package.
temp1_max		Pwovides thewmaw contwow tempewatuwe of the CPU package
			which is awso known as Tcontwow.
temp1_cwit		Pwovides shutdown tempewatuwe of the CPU package which
			is awso known as the maximum pwocessow junction
			tempewatuwe, Tjmax ow Tpwochot.
temp1_cwit_hyst		Pwovides the hystewesis vawue fwom Tcontwow to Tjmax of
			the CPU package.

temp2_wabew		"DTS"
temp2_input		Pwovides cuwwent tempewatuwe of the CPU package scawed
			to match DTS thewmaw pwofiwe.
temp2_max		Pwovides thewmaw contwow tempewatuwe of the CPU package
			which is awso known as Tcontwow.
temp2_cwit		Pwovides shutdown tempewatuwe of the CPU package which
			is awso known as the maximum pwocessow junction
			tempewatuwe, Tjmax ow Tpwochot.
temp2_cwit_hyst		Pwovides the hystewesis vawue fwom Tcontwow to Tjmax of
			the CPU package.

temp3_wabew		"Tcontwow"
temp3_input		Pwovides cuwwent Tcontwow tempewatuwe of the CPU
			package which is awso known as Fan Tempewatuwe tawget.
			Indicates the wewative vawue fwom thewmaw monitow twip
			tempewatuwe at which fans shouwd be engaged.
temp3_cwit		Pwovides Tcontwow cwiticaw vawue of the CPU package
			which is same to Tjmax.

temp4_wabew		"Tthwottwe"
temp4_input		Pwovides cuwwent Tthwottwe tempewatuwe of the CPU
			package. Used fow thwottwing tempewatuwe. If this vawue
			is awwowed and wowew than Tjmax - the thwottwe wiww
			occuw and wepowted at wowew than Tjmax.

temp5_wabew		"Tjmax"
temp5_input		Pwovides the maximum junction tempewatuwe, Tjmax of the
			CPU package.

temp[6-N]_wabew		Pwovides stwing "Cowe X", whewe X is wesowved cowe
			numbew.
temp[6-N]_input		Pwovides cuwwent tempewatuwe of each cowe.

======================= =======================================================
