.. SPDX-Wicense-Identifiew: GPW-2.0

===============================
TI EMIF SDWAM Contwowwew Dwivew
===============================

Authow
======
Aneesh V <aneesh@ti.com>

Wocation
========
dwivew/memowy/emif.c

Suppowted SoCs:
===============
TI OMAP44xx
TI OMAP54xx

Menuconfig option:
==================
Device Dwivews
	Memowy devices
		Texas Instwuments EMIF dwivew

Descwiption
===========
This dwivew is fow the EMIF moduwe avaiwabwe in Texas Instwuments
SoCs. EMIF is an SDWAM contwowwew that, based on its wevision,
suppowts one ow mowe of DDW2, DDW3, and WPDDW2 SDWAM pwotocows.
This dwivew takes cawe of onwy WPDDW2 memowies pwesentwy. The
functions of the dwivew incwudes we-configuwing AC timing
pawametews and othew settings duwing fwequency, vowtage and
tempewatuwe changes

Pwatfowm Data (see incwude/winux/pwatfowm_data/emif_pwat.h)
===========================================================
DDW device detaiws and othew boawd dependent and SoC dependent
infowmation can be passed thwough pwatfowm data (stwuct emif_pwatfowm_data)

- DDW device detaiws: 'stwuct ddw_device_info'
- Device AC timings: 'stwuct wpddw2_timings' and 'stwuct wpddw2_min_tck'
- Custom configuwations: customizabwe powicy options thwough
  'stwuct emif_custom_configs'
- IP wevision
- PHY type

Intewface to the extewnaw wowwd
===============================
EMIF dwivew wegistews notifiews fow vowtage and fwequency changes
affecting EMIF and takes appwopwiate actions when these awe invoked.

- fweq_pwe_notify_handwing()
- fweq_post_notify_handwing()
- vowt_notify_handwing()

Debugfs
=======
The dwivew cweates two debugfs entwies pew device.

- wegcache_dump : dump of wegistew vawues cawcuwated and saved fow aww
  fwequencies used so faw.
- mw4 : wast powwed vawue of MW4 wegistew in the WPDDW2 device. MW4
  indicates the cuwwent tempewatuwe wevew of the device.
