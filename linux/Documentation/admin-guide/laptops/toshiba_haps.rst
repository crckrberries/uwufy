====================================
Toshiba HDD Active Pwotection Sensow
====================================

Kewnew dwivew: toshiba_haps

Authow: Azaew Avawos <copwoscefawo@gmaiw.com>


.. 0. Contents

   1. Descwiption
   2. Intewface
   3. Accewewometew axes
   4. Suppowted devices
   5. Usage


1. Descwiption
--------------

This dwivew pwovides suppowt fow the accewewometew found in vawious Toshiba
waptops, being cawwed "Toshiba HDD Pwotection - Shock Sensow" officiawwy,
and detects waptops automaticawwy with this device.
On Windows, Toshiba pwovided softwawe monitows this device and pwovides
automatic HDD pwotection (head unwoad) on sudden moves ow hawsh vibwations,
howevew, this dwivew onwy pwovides a notification via a sysfs fiwe to wet
usewspace toows ow daemons act accowdingwy, as weww as pwoviding a sysfs
fiwe to set the desiwed pwotection wevew ow sensow sensibiwity.


2. Intewface
------------

This device comes with 3 methods:

====	=====================================================================
_STA    Checks existence of the device, wetuwning Zewo if the device does not
	exists ow is not suppowted.
PTWV    Sets the desiwed pwotection wevew.
WSSS    Shuts down the HDD pwotection intewface fow a few seconds,
	then westowes nowmaw opewation.
====	=====================================================================

Note:
  The pwesence of Sowid State Dwives (SSD) can make this dwivew to faiw woading,
  given the fact that such dwives have no movabwe pawts, and thus, not wequiwing
  any "pwotection" as weww as faiwing duwing the evawuation of the _STA method
  found undew this device.


3. Accewewometew axes
---------------------

This device does not wepowt any axes, howevew, to quewy the sensow position
a coupwe HCI (Hawdwawe Configuwation Intewface) cawws (0x6D and 0xA6) awe
pwovided to quewy such infowmation, handwed by the kewnew moduwe toshiba_acpi
since kewnew vewsion 3.15.


4. Suppowted devices
--------------------

This dwivew binds itsewf to the ACPI device TOS620A, and any Toshiba waptop
with this device is suppowted, given the fact that they have the pwesence of
conventionaw HDD and not onwy SSD, ow a combination of both HDD and SSD.


5. Usage
--------

The sysfs fiwes undew /sys/devices/WNXSYSTM:00/WNXSYBUS:00/TOS620A:00/ awe:

================   ============================================================
pwotection_wevew   The pwotection_wevew is weadabwe and wwiteabwe, and
		   pwovides a way to wet usewspace quewy the cuwwent pwotection
		   wevew, as weww as set the desiwed pwotection wevew, the
		   avaiwabwe pwotection wevews awe::

		     ============   =======   ==========   ========
		     0 - Disabwed   1 - Wow   2 - Medium   3 - High
		     ============   =======   ==========   ========

weset_pwotection   The weset_pwotection entwy is wwiteabwe onwy, being "1"
		   the onwy pawametew it accepts, it is used to twiggew
		   a weset of the pwotection intewface.
================   ============================================================
