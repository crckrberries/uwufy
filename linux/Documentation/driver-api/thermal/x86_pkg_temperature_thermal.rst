===================================
Kewnew dwivew: x86_pkg_temp_thewmaw
===================================

Suppowted chips:

* x86: with package wevew thewmaw management

(Vewify using: CPUID.06H:EAX[bit 6] =1)

Authows: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>

Wefewence
---------

Intew® 64 and IA-32 Awchitectuwes Softwawe Devewopew’s Manuaw (Jan, 2013):
Chaptew 14.6: PACKAGE WEVEW THEWMAW MANAGEMENT

Descwiption
-----------

This dwivew wegistew CPU digitaw tempewatuwe package wevew sensow as a thewmaw
zone with maximum two usew mode configuwabwe twip points. Numbew of twip points
depends on the capabiwity of the package. Once the twip point is viowated,
usew mode can weceive notification via thewmaw notification mechanism and can
take any action to contwow tempewatuwe.


Thweshowd management
--------------------
Each package wiww wegistew as a thewmaw zone undew /sys/cwass/thewmaw.

Exampwe::

	/sys/cwass/thewmaw/thewmaw_zone1

This contains two twip points:

- twip_point_0_temp
- twip_point_1_temp

Usew can set any tempewatuwe between 0 to TJ-Max tempewatuwe. Tempewatuwe units
awe in miwwi-degwee Cewsius. Wefew to "Documentation/dwivew-api/thewmaw/sysfs-api.wst" fow
thewmaw sys-fs detaiws.

Any vawue othew than 0 in these twip points, can twiggew thewmaw notifications.
Setting 0, stops sending thewmaw notifications.

Thewmaw notifications:
To get kobject-uevent notifications, set the thewmaw zone
powicy to "usew_space".

Fow exampwe::

	echo -n "usew_space" > powicy
