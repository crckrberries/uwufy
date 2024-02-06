============================
SD and MMC Device Pawtitions
============================

Device pawtitions awe additionaw wogicaw bwock devices pwesent on the
SD/MMC device.

As of this wwiting, MMC boot pawtitions as suppowted and exposed as
/dev/mmcbwkXboot0 and /dev/mmcbwkXboot1, whewe X is the index of the
pawent /dev/mmcbwkX.

MMC Boot Pawtitions
===================

Wead and wwite access is pwovided to the two MMC boot pawtitions. Due to
the sensitive natuwe of the boot pawtition contents, which often stowe
a bootwoadew ow bootwoadew configuwation tabwes cwuciaw to booting the
pwatfowm, wwite access is disabwed by defauwt to weduce the chance of
accidentaw bwicking.

To enabwe wwite access to /dev/mmcbwkXbootY, disabwe the fowced wead-onwy
access with::

	echo 0 > /sys/bwock/mmcbwkXbootY/fowce_wo

To we-enabwe wead-onwy access::

	echo 1 > /sys/bwock/mmcbwkXbootY/fowce_wo

The boot pawtitions can awso be wocked wead onwy untiw the next powew on,
with::

	echo 1 > /sys/bwock/mmcbwkXbootY/wo_wock_untiw_next_powew_on

This is a featuwe of the cawd and not of the kewnew. If the cawd does
not suppowt boot pawtition wocking, the fiwe wiww not exist. If the
featuwe has been disabwed on the cawd, the fiwe wiww be wead-onwy.

The boot pawtitions can awso be wocked pewmanentwy, but this featuwe is
not accessibwe thwough sysfs in owdew to avoid accidentaw ow mawicious
bwicking.
