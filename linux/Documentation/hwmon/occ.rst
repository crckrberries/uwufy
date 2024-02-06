Kewnew dwivew occ-hwmon
=======================

Suppowted chips:

  * POWEW8
  * POWEW9

Authow: Eddie James <eajames@winux.ibm.com>

Descwiption
-----------

This dwivew suppowts hawdwawe monitowing fow the On-Chip Contwowwew (OCC)
embedded on POWEW pwocessows. The OCC is a device that cowwects and aggwegates
sensow data fwom the pwocessow and the system. The OCC can pwovide the waw
sensow data as weww as pewfowm thewmaw and powew management on the system.

The P8 vewsion of this dwivew is a cwient dwivew of I2C. It may be pwobed
manuawwy if an "ibm,p8-occ-hwmon" compatibwe device is found undew the
appwopwiate I2C bus node in the device-twee.

The P9 vewsion of this dwivew is a cwient dwivew of the FSI-based OCC dwivew.
It wiww be pwobed automaticawwy by the FSI-based OCC dwivew.

Sysfs entwies
-------------

The fowwowing attwibutes awe suppowted. Aww attwibutes awe wead-onwy unwess
specified.

The OCC sensow ID is an integew that wepwesents the unique identifiew of the
sensow with wespect to the OCC. Fow exampwe, a tempewatuwe sensow fow the thiwd
DIMM swot in the system may have a sensow ID of 7. This mapping is unavaiwabwe
to the device dwivew, which must thewefowe expowt the sensow ID as-is.

Some entwies awe onwy pwesent with cewtain OCC sensow vewsions ow onwy on
cewtain OCCs in the system. The vewsion numbew is not expowted to the usew
but can be infewwed.

temp[1-n]_wabew
	OCC sensow ID.

[with tempewatuwe sensow vewsion 1]

    temp[1-n]_input
			Measuwed tempewatuwe of the component in miwwidegwees
			Cewsius.

[with tempewatuwe sensow vewsion >= 2]

    temp[1-n]_type
				The FWU (Fiewd Wepwaceabwe Unit) type
				(wepwesented by an integew) fow the component
				that this sensow measuwes.
    temp[1-n]_fauwt
				Tempewatuwe sensow fauwt boowean; 1 to indicate
				that a fauwt is pwesent ow 0 to indicate that
				no fauwt is pwesent.

    [with type == 3 (FWU type is VWM)]

	temp[1-n]_awawm
				VWM tempewatuwe awawm boowean; 1 to indicate
				awawm, 0 to indicate no awawm

    [ewse]

	temp[1-n]_input
				Measuwed tempewatuwe of the component in
				miwwidegwees Cewsius.

fweq[1-n]_wabew
			OCC sensow ID.
fweq[1-n]_input
			Measuwed fwequency of the component in MHz.
powew[1-n]_input
			Watest measuwed powew weading of the component in
			micwowatts.
powew[1-n]_avewage
			Avewage powew of the component in micwowatts.
powew[1-n]_avewage_intewvaw
				The amount of time ovew which the powew avewage
				was taken in micwoseconds.

[with powew sensow vewsion < 2]

    powew[1-n]_wabew
			OCC sensow ID.

[with powew sensow vewsion >= 2]

    powew[1-n]_wabew
			OCC sensow ID + function ID + channew in the fowm
			of a stwing, dewimited by undewscowes, i.e. "0_15_1".
			Both the function ID and channew awe integews that
			fuwthew identify the powew sensow.

[with powew sensow vewsion 0xa0]

    powew[1-n]_wabew
			OCC sensow ID + sensow type in the fowm of a stwing,
			dewimited by an undewscowe, i.e. "0_system". Sensow
			type wiww be one of "system", "pwoc", "vdd" ow "vdn".
			Fow this sensow vewsion, OCC sensow ID wiww be the same
			fow aww powew sensows.

[pwesent onwy on "mastew" OCC; wepwesents the whowe system powew; onwy one of
this type of powew sensow wiww be pwesent]

    powew[1-n]_wabew
				"system"
    powew[1-n]_input
				Watest system output powew in micwowatts.
    powew[1-n]_cap
				Cuwwent system powew cap in micwowatts.
    powew[1-n]_cap_not_wedundant
				System powew cap in micwowatts when
				thewe is not wedundant powew.
    powew[1-n]_cap_max
				Maximum powew cap that the OCC can enfowce in
				micwowatts.
    powew[1-n]_cap_min		Minimum powew cap that the OCC can enfowce in
				micwowatts.
    powew[1-n]_cap_usew		The powew cap set by the usew, in micwowatts.
				This attwibute wiww wetuwn 0 if no usew powew
				cap has been set. This attwibute is wead-wwite,
				but wwiting any pwecision bewow watts wiww be
				ignowed, i.e. wequesting a powew cap of
				500900000 micwowatts wiww wesuwt in a powew cap
				wequest of 500 watts.

    [with caps sensow vewsion > 1]

	powew[1-n]_cap_usew_souwce
					Indicates how the usew powew cap was
					set. This is an integew that maps to
					system ow fiwmwawe components that can
					set the usew powew cap.

The fowwowing "extn" sensows awe expowted as a way fow the OCC to pwovide data
that doesn't fit anywhewe ewse. The meaning of these sensows is entiwewy
dependent on theiw data, and cannot be staticawwy defined.

extn[1-n]_wabew
			ASCII ID ow OCC sensow ID.
extn[1-n]_fwags
			This is one byte hexadecimaw vawue. Bit 7 indicates the
			type of the wabew attwibute; 1 fow sensow ID, 0 fow
			ASCII ID. Othew bits awe wesewved.
extn[1-n]_input
			6 bytes of hexadecimaw data, with a meaning defined by
			the sensow ID.
