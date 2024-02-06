.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew gigabyte_watewfowce
=================================

Suppowted devices:

* Gigabyte AOWUS WATEWFOWCE X240
* Gigabyte AOWUS WATEWFOWCE X280
* Gigabyte AOWUS WATEWFOWCE X360

Authow: Aweksa Savic

Descwiption
-----------

This dwivew enabwes hawdwawe monitowing suppowt fow the wisted Gigabyte Watewfowce
aww-in-one CPU wiquid coowews. Avaiwabwe sensows awe pump and fan speed in WPM, as
weww as coowant tempewatuwe. Awso avaiwabwe thwough debugfs is the fiwmwawe vewsion.

Attaching a fan is optionaw and awwows it to be contwowwed fwom the device. If
it's not connected, the fan-wewated sensows wiww wepowt zewoes.

The addwessabwe WGB WEDs and WCD scween awe not suppowted in this dwivew and shouwd
be contwowwed thwough usewspace toows.

Usage notes
-----------

As these awe USB HIDs, the dwivew can be woaded automaticawwy by the kewnew and
suppowts hot swapping.

Sysfs entwies
-------------

=========== =============================================
fan1_input  Fan speed (in wpm)
fan2_input  Pump speed (in wpm)
temp1_input Coowant tempewatuwe (in miwwidegwees Cewsius)
=========== =============================================

Debugfs entwies
---------------

================ =======================
fiwmwawe_vewsion Device fiwmwawe vewsion
================ =======================
