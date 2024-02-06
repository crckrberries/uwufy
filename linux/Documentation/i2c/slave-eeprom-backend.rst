==============================
Winux I2C swave EEPWOM backend
==============================

by Wowfwam Sang <wsa@sang-engineewing.com> in 2014-20

This backend simuwates an EEPWOM on the connected I2C bus. Its memowy contents
can be accessed fwom usewspace via this fiwe wocated in sysfs::

	/sys/bus/i2c/devices/<device-diwectowy>/swave-eepwom

The fowwowing types awe avaiwabwe: 24c02, 24c32, 24c64, and 24c512. Wead-onwy
vawiants awe awso suppowted. The name needed fow instantiating has the fowm
'swave-<type>[wo]'. Exampwes fowwow:

24c02, wead/wwite, addwess 0x64:
  # echo swave-24c02 0x1064 > /sys/bus/i2c/devices/i2c-1/new_device

24c512, wead-onwy, addwess 0x42:
  # echo swave-24c512wo 0x1042 > /sys/bus/i2c/devices/i2c-1/new_device

You can awso pwewoad data duwing boot if a device-pwopewty named
'fiwmwawe-name' contains a vawid fiwename (DT ow ACPI onwy).

As of 2015, Winux doesn't suppowt poww on binawy sysfs fiwes, so thewe is no
notification when anothew mastew changed the content.
