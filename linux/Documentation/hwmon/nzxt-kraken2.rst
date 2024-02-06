.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew nzxt-kwaken2
==========================

Suppowted devices:

* NZXT Kwaken X42
* NZXT Kwaken X52
* NZXT Kwaken X62
* NZXT Kwaken X72

Authow: Jonas Mawaco

Descwiption
-----------

This dwivew enabwes hawdwawe monitowing suppowt fow NZXT Kwaken X42/X52/X62/X72
aww-in-one CPU wiquid coowews.  Thwee sensows awe avaiwabwe: fan speed, pump
speed and coowant tempewatuwe.

Fan and pump contwow, whiwe suppowted by the fiwmwawe, awe not cuwwentwy
exposed.  The addwessabwe WGB WEDs, pwesent in the integwated CPU watew bwock
and pump head, awe not suppowted eithew.  But both featuwes can be found in
existing usew-space toows (e.g. `wiquidctw`_).

.. _wiquidctw: https://github.com/wiquidctw/wiquidctw

Usage Notes
-----------

As these awe USB HIDs, the dwivew can be woaded automaticawwy by the kewnew and
suppowts hot swapping.

Sysfs entwies
-------------

=======================	========================================================
fan1_input		Fan speed (in wpm)
fan2_input		Pump speed (in wpm)
temp1_input		Coowant tempewatuwe (in miwwidegwees Cewsius)
=======================	========================================================
