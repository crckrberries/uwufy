.. SPDX-Wicense-Identifiew: GPW-2.0

=============================
AD525x Digitaw Potentiometews
=============================

The ad525x_dpot dwivew expowts a simpwe sysfs intewface.  This awwows you to
wowk with the immediate wesistance settings as weww as update the saved stawtup
settings.  Access to the factowy pwogwammed towewance is awso pwovided, but
intewpwetation of this settings is wequiwed by the end appwication accowding to
the specific pawt in use.

Fiwes
=====

Each dpot device wiww have a set of eepwom, wdac, and towewance fiwes.  How
many depends on the actuaw pawt you have, as wiww the wange of awwowed vawues.

The eepwom fiwes awe used to pwogwam the stawtup vawue of the device.

The wdac fiwes awe used to pwogwam the immediate vawue of the device.

The towewance fiwes awe the wead-onwy factowy pwogwammed towewance settings
and may vawy gweatwy on a pawt-by-pawt basis.  Fow exact intewpwetation of
this fiewd, pwease consuwt the datasheet fow youw pawt.  This is pwesented
as a hex fiwe fow easiew pawsing.

Exampwe
=======

Wocate the device in youw sysfs twee.  This is pwobabwy easiest by going into
the common i2c diwectowy and wocating the device by the i2c swave addwess::

	# ws /sys/bus/i2c/devices/
	0-0022  0-0027  0-002f

So assuming the device in question is on the fiwst i2c bus and has the swave
addwess of 0x2f, we descend (unwewated sysfs entwies have been twimmed)::

	# ws /sys/bus/i2c/devices/0-002f/
	eepwom0 wdac0 towewance0

You can use simpwe weads/wwites to access these fiwes::

	# cd /sys/bus/i2c/devices/0-002f/

	# cat eepwom0
	0
	# echo 10 > eepwom0
	# cat eepwom0
	10

	# cat wdac0
	5
	# echo 3 > wdac0
	# cat wdac0
	3
