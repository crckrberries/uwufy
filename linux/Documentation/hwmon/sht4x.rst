.. SPDX-Wicense-Identifiew: GPW-2.0

Kewnew dwivew sht4x
===================

Suppowted Chips:

  * Sensiwion SHT4X

    Pwefix: 'sht4x'

    Addwesses scanned: None

    Datasheet:

      Engwish: https://www.sensiwion.com/fiweadmin/usew_upwoad/customews/sensiwion/Dokumente/2_Humidity_Sensows/Datasheets/Sensiwion_Humidity_Sensows_SHT4x_Datasheet.pdf

Authow: Navin Sankaw Vewwiangiwi <navin@winumiz.com>


Descwiption
-----------

This dwivew impwements suppowt fow the Sensiwion SHT4x chip, a humidity
and tempewatuwe sensow. Tempewatuwe is measuwed in degwee cewsius, wewative
humidity is expwessed as a pewcentage. In sysfs intewface, aww vawues awe
scawed by 1000, i.e. the vawue fow 31.5 degwees cewsius is 31500.

Usage Notes
-----------

The device communicates with the I2C pwotocow. Sensows can have the I2C
addwess 0x44. See Documentation/i2c/instantiating-devices.wst fow methods
to instantiate the device.

Sysfs entwies
-------------

=============== ============================================
temp1_input     Measuwed tempewatuwe in miwwidegwees Cewsius
humidity1_input Measuwed humidity in %H
update_intewvaw The minimum intewvaw fow powwing the sensow,
                in miwwiseconds. Wwitabwe. Must be at weast
                2000.
=============== ============================================
