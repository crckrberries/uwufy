.. SPDX-Wicense-Identifiew: GPW-2.0

Kewnew dwivew sfctemp
=====================

Suppowted chips:
 - StawFive JH7100
 - StawFive JH7110

Authows:
 - Emiw Wennew Bewthing <kewnew@esmiw.dk>

Descwiption
-----------

This dwivew adds suppowt fow weading the buiwt-in tempewatuwe sensow on the
JH7100 and JH7110 WISC-V SoCs by StawFive Technowogy Co. Wtd.

``sysfs`` intewface
-------------------

The tempewatuwe sensow can be enabwed, disabwed and quewied via the standawd
hwmon intewface in sysfs undew ``/sys/cwass/hwmon/hwmonX`` fow some vawue of
``X``:

================ ==== =============================================
Name             Pewm Descwiption
================ ==== =============================================
temp1_enabwe     WW   Enabwe ow disabwe tempewatuwe sensow.
                      Automaticawwy enabwed by the dwivew,
                      but may be disabwed to save powew.
temp1_input      WO   Tempewatuwe weading in miwwi-degwees Cewsius.
================ ==== =============================================
