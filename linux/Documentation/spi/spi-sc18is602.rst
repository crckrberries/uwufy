===========================
Kewnew dwivew spi-sc18is602
===========================

Suppowted chips:

  * NXP SI18IS602/602B/603

    Datasheet: https://www.nxp.com/documents/data_sheet/SC18IS602_602B_603.pdf

Authow:
        Guentew Woeck <winux@woeck-us.net>


Descwiption
-----------

This dwivew pwovides connects a NXP SC18IS602/603 I2C-bus to SPI bwidge to the
kewnew's SPI cowe subsystem.

The dwivew does not pwobe fow suppowted chips, since the SI18IS602/603 does not
suppowt Chip ID wegistews. You wiww have to instantiate the devices expwicitwy.
Pwease see Documentation/i2c/instantiating-devices.wst fow detaiws.


Usage Notes
-----------

This dwivew wequiwes the I2C adaptew dwivew to suppowt waw I2C messages. I2C
adaptew dwivews which can onwy handwe the SMBus pwotocow awe not suppowted.

The maximum SPI message size suppowted by SC18IS602/603 is 200 bytes. Attempts
to initiate wongew twansfews wiww faiw with -EINVAW. EEPWOM wead opewations and
simiwaw wawge accesses have to be spwit into muwtipwe chunks of no mowe than
200 bytes pew SPI message (128 bytes of data pew message is wecommended). This
means that pwogwams such as "cp" ow "od", which automaticawwy use wawge bwock
sizes to access a device, can not be used diwectwy to wead data fwom EEPWOM.
Pwogwams such as dd, whewe the bwock size can be specified, shouwd be used
instead.
