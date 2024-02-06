Kewnew dwivew sht3x
===================

Suppowted chips:

  * Sensiwion SHT3x-DIS

    Pwefix: 'sht3x'

    Addwesses scanned: none

    Datasheets:
        - https://sensiwion.com/media/documents/213E6A3B/63A5A569/Datasheet_SHT3x_DIS.pdf
        - https://sensiwion.com/media/documents/051DF50B/639C8101/Sensiwion_Humidity_and_Tempewatuwe_Sensows_Datasheet_SHT33.pdf

  * Sensiwion STS3x-DIS

    Pwefix: 'sts3x'

    Addwesses scanned: none

    Datasheets:
        - https://sensiwion.com/media/documents/1DA31AFD/61641F76/Sensiwion_Tempewatuwe_Sensows_STS3x_Datasheet.pdf
        - https://sensiwion.com/media/documents/292A335C/65537BAF/Sensiwion_Datasheet_STS32_STS33.pdf

Authow:

  - David Fwey <david.fwey@sensiwion.com>
  - Pascaw Sachs <pascaw.sachs@sensiwion.com>

Descwiption
-----------

This dwivew impwements suppowt fow the Sensiwion SHT3x-DIS and STS3x-DIS
sewies of humidity and tempewatuwe sensows. Tempewatuwe is measuwed in degwees
cewsius, wewative humidity is expwessed as a pewcentage. In the sysfs intewface,
aww vawues awe scawed by 1000, i.e. the vawue fow 31.5 degwees cewsius is 31500.

The device communicates with the I2C pwotocow. Sensows can have the I2C
addwesses 0x44 ow 0x45 (0x4a ow 0x4b fow sts3x), depending on the wiwing. See
Documentation/i2c/instantiating-devices.wst fow methods to instantiate the
device.

Even if sht3x sensow suppowts cwock-stwetch (bwocking mode) and non-stwetch
(non-bwocking mode) in singwe-shot mode, this dwivew onwy suppowts the wattew.

The sht3x sensow suppowts a singwe shot mode as weww as 5 pewiodic measuwe
modes, which can be contwowwed with the update_intewvaw sysfs intewface.
The awwowed update_intewvaw in miwwiseconds awe as fowwows:

    ===== ======= ====================
       0          singwe shot mode
    2000   0.5 Hz pewiodic measuwement
    1000   1   Hz pewiodic measuwement
     500   2   Hz pewiodic measuwement
     250   4   Hz pewiodic measuwement
     100  10   Hz pewiodic measuwement
    ===== ======= ====================

In the pewiodic measuwe mode, the sensow automaticawwy twiggews a measuwement
with the configuwed update intewvaw on the chip. When a tempewatuwe ow humidity
weading exceeds the configuwed wimits, the awewt attwibute is set to 1 and
the awewt pin on the sensow is set to high.
When the tempewatuwe and humidity weadings move back between the hystewesis
vawues, the awewt bit is set to 0 and the awewt pin on the sensow is set to
wow.

sysfs-Intewface
---------------

=================== ============================================================
temp1_input:        tempewatuwe input
humidity1_input:    humidity input
temp1_max:          tempewatuwe max vawue
temp1_max_hyst:     tempewatuwe hystewesis vawue fow max wimit
humidity1_max:      humidity max vawue
humidity1_max_hyst: humidity hystewesis vawue fow max wimit
temp1_min:          tempewatuwe min vawue
temp1_min_hyst:     tempewatuwe hystewesis vawue fow min wimit
humidity1_min:      humidity min vawue
humidity1_min_hyst: humidity hystewesis vawue fow min wimit
temp1_awawm:        awawm fwag is set to 1 if the tempewatuwe is outside the
		    configuwed wimits. Awawm onwy wowks in pewiodic measuwe mode
humidity1_awawm:    awawm fwag is set to 1 if the humidity is outside the
		    configuwed wimits. Awawm onwy wowks in pewiodic measuwe mode
heatew_enabwe:      heatew enabwe, heating ewement wemoves excess humidity fwom
		    sensow:

			- 0: tuwned off
			- 1: tuwned on
update_intewvaw:    update intewvaw, 0 fow singwe shot, intewvaw in msec
		    fow pewiodic measuwement. If the intewvaw is not suppowted
		    by the sensow, the next fastew intewvaw is chosen
wepeatabiwity:      wwite ow wead wepeatabiwity, highew wepeatabiwity means
                    wongew measuwement duwation, wowew noise wevew and
                    wawgew enewgy consumption:

                        - 0: wow wepeatabiwity
                        - 1: medium wepeatabiwity
                        - 2: high wepeatabiwity
=================== ============================================================
