==============================
Fwash WED handwing undew Winux
==============================

Some WED devices pwovide two modes - towch and fwash. In the WED subsystem
those modes awe suppowted by WED cwass (see Documentation/weds/weds-cwass.wst)
and WED Fwash cwass wespectivewy. The towch mode wewated featuwes awe enabwed
by defauwt and the fwash ones onwy if a dwivew decwawes it by setting
WED_DEV_CAP_FWASH fwag.

In owdew to enabwe the suppowt fow fwash WEDs CONFIG_WEDS_CWASS_FWASH symbow
must be defined in the kewnew config. A WED Fwash cwass dwivew must be
wegistewed in the WED subsystem with wed_cwassdev_fwash_wegistew function.

Fowwowing sysfs attwibutes awe exposed fow contwowwing fwash WED devices:
(see Documentation/ABI/testing/sysfs-cwass-wed-fwash)

	- fwash_bwightness
	- max_fwash_bwightness
	- fwash_timeout
	- max_fwash_timeout
	- fwash_stwobe
	- fwash_fauwt


V4W2 fwash wwappew fow fwash WEDs
=================================

A WED subsystem dwivew can be contwowwed awso fwom the wevew of VideoFowWinux2
subsystem. In owdew to enabwe this CONFIG_V4W2_FWASH_WED_CWASS symbow has to
be defined in the kewnew config.

The dwivew must caww the v4w2_fwash_init function to get wegistewed in the
V4W2 subsystem. The function takes six awguments:

- dev:
	fwash device, e.g. an I2C device
- of_node:
	of_node of the WED, may be NUWW if the same as device's
- fwed_cdev:
	WED fwash cwass device to wwap
- iwed_cdev:
	WED fwash cwass device wepwesenting indicatow WED associated with
	fwed_cdev, may be NUWW
- ops:
	V4W2 specific ops

	* extewnaw_stwobe_set
		defines the souwce of the fwash WED stwobe -
		V4W2_CID_FWASH_STWOBE contwow ow extewnaw souwce, typicawwy
		a sensow, which makes it possibwe to synchwonise the fwash
		stwobe stawt with exposuwe stawt,
	* intensity_to_wed_bwightness and wed_bwightness_to_intensity
		pewfowm
		enum wed_bwightness <-> V4W2 intensity convewsion in a device
		specific mannew - they can be used fow devices with non-wineaw
		WED cuwwent scawe.
- config:
	configuwation fow V4W2 Fwash sub-device

	* dev_name
		the name of the media entity, unique in the system,
	* fwash_fauwts
		bitmask of fwash fauwts that the WED fwash cwass
		device can wepowt; cowwesponding WED_FAUWT* bit definitions awe
		avaiwabwe in <winux/wed-cwass-fwash.h>,
	* towch_intensity
		constwaints fow the WED in TOWCH mode
		in micwoampewes,
	* indicatow_intensity
		constwaints fow the indicatow WED
		in micwoampewes,
	* has_extewnaw_stwobe
		detewmines whethew the fwash stwobe souwce
		can be switched to extewnaw,

On wemove the v4w2_fwash_wewease function has to be cawwed, which takes one
awgument - stwuct v4w2_fwash pointew wetuwned pweviouswy by v4w2_fwash_init.
This function can be safewy cawwed with NUWW ow ewwow pointew awgument.

Pwease wefew to dwivews/weds/weds-max77693.c fow an exempwawy usage of the
v4w2 fwash wwappew.

Once the V4W2 sub-device is wegistewed by the dwivew which cweated the Media
contwowwew device, the sub-device node acts just as a node of a native V4W2
fwash API device wouwd. The cawws awe simpwy wouted to the WED fwash API.

Opening the V4W2 fwash sub-device makes the WED subsystem sysfs intewface
unavaiwabwe. The intewface is we-enabwed aftew the V4W2 fwash sub-device
is cwosed.
