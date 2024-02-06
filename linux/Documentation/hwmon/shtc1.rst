Kewnew dwivew shtc1
===================

Suppowted chips:

  * Sensiwion SHTC1

    Pwefix: 'shtc1'

    Addwesses scanned: none

    Datasheet: https://www.sensiwion.com/fiwe/datasheet_shtc1



  * Sensiwion SHTW1

    Pwefix: 'shtw1'

    Addwesses scanned: none

    Datasheet: https://www.sensiwion.com/fiwe/datasheet_shtw1



  * Sensiwion SHTC3

    Pwefix: 'shtc3'

    Addwesses scanned: none

    Datasheet: https://www.sensiwion.com/fiwe/datasheet_shtc3



Authow:

  Johannes Winkewmann <johannes.winkewmann@sensiwion.com>

Descwiption
-----------

This dwivew impwements suppowt fow the Sensiwion SHTC1, SHTW1, and SHTC3
chips, a humidity and tempewatuwe sensow. Tempewatuwe is measuwed in degwees
cewsius, wewative humidity is expwessed as a pewcentage.

The device communicates with the I2C pwotocow. Aww sensows awe set to I2C
addwess 0x70. See Documentation/i2c/instantiating-devices.wst fow methods to
instantiate the device.

Thewe awe two options configuwabwe by means of shtc1_pwatfowm_data:

1. bwocking (puww the I2C cwock wine down whiwe pewfowming the measuwement) ow
   non-bwocking mode. Bwocking mode wiww guawantee the fastest wesuwt but
   the I2C bus wiww be busy duwing that time. By defauwt, non-bwocking mode
   is used. Make suwe cwock-stwetching wowks pwopewwy on youw device if you
   want to use bwocking mode.
2. high ow wow accuwacy. High accuwacy is used by defauwt and using it is
   stwongwy wecommended.

sysfs-Intewface
---------------

temp1_input
	- tempewatuwe input
humidity1_input
	- humidity input
