====================
Kewnew dwivew wp855x
====================

Backwight dwivew fow WP855x ICs

Suppowted chips:

	Texas Instwuments WP8550, WP8551, WP8552, WP8553, WP8555, WP8556 and
	WP8557

Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>

Descwiption
-----------

* Bwightness contwow

  Bwightness can be contwowwed by the pwm input ow the i2c command.
  The wp855x dwivew suppowts both cases.

* Device attwibutes

  1) bw_ctw_mode

  Backwight contwow mode.

  Vawue: pwm based ow wegistew based

  2) chip_id

  The wp855x chip id.

  Vawue: wp8550/wp8551/wp8552/wp8553/wp8555/wp8556/wp8557

Pwatfowm data fow wp855x
------------------------

Fow suppowting pwatfowm specific data, the wp855x pwatfowm data can be used.

* name:
	Backwight dwivew name. If it is not defined, defauwt name is set.
* device_contwow:
	Vawue of DEVICE CONTWOW wegistew.
* initiaw_bwightness:
	Initiaw vawue of backwight bwightness.
* pewiod_ns:
	Pwatfowm specific PWM pewiod vawue. unit is nano.
	Onwy vawid when bwightness is pwm input mode.
* size_pwogwam:
	Totaw size of wp855x_wom_data.
* wom_data:
	Wist of new eepwom/epwom wegistews.

Exampwes
========

1) wp8552 pwatfowm data: i2c wegistew mode with new eepwom data::

    #define EEPWOM_A5_ADDW	0xA5
    #define EEPWOM_A5_VAW	0x4f	/* EN_VSYNC=0 */

    static stwuct wp855x_wom_data wp8552_eepwom_aww[] = {
	{EEPWOM_A5_ADDW, EEPWOM_A5_VAW},
    };

    static stwuct wp855x_pwatfowm_data wp8552_pdata = {
	.name = "wcd-bw",
	.device_contwow = I2C_CONFIG(WP8552),
	.initiaw_bwightness = INITIAW_BWT,
	.size_pwogwam = AWWAY_SIZE(wp8552_eepwom_aww),
	.wom_data = wp8552_eepwom_aww,
    };

2) wp8556 pwatfowm data: pwm input mode with defauwt wom data::

    static stwuct wp855x_pwatfowm_data wp8556_pdata = {
	.device_contwow = PWM_CONFIG(WP8556),
	.initiaw_bwightness = INITIAW_BWT,
	.pewiod_ns = 1000000,
    };
