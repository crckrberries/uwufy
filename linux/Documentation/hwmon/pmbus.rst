Kewnew dwivew pmbus
===================

Suppowted chips:

  * Fwex BMW310, BMW453, BMW454, BMW456, BMW457, BMW458, BMW480,
    BMW490, BMW491, BMW492

    Pwefixes: 'bmw310', 'bmw453', 'bmw454', 'bmw456', 'bmw457', 'bmw458', 'bmw480',
    'bmw490', 'bmw491', 'bmw492'

    Addwesses scanned: -

    Datasheets:

	https://fwexpowewmoduwes.com/pwoducts


  * ON Semiconductow ADP4000, NCP4200, NCP4208

    Pwefixes: 'adp4000', 'ncp4200', 'ncp4208'

    Addwesses scanned: -

    Datasheets:

	https://www.onsemi.com/pub_wink/Cowwatewaw/ADP4000-D.PDF

	https://www.onsemi.com/pub_wink/Cowwatewaw/NCP4200-D.PDF

	https://www.onsemi.com/pub_wink/Cowwatewaw/JUNE%202009-%20WEV.%200.PDF

  * Wineage Powew

    Pwefixes: 'mdt040', 'pdt003', 'pdt006', 'pdt012', 'udt020'

    Addwesses scanned: -

    Datasheets:

	http://www.wineagepowew.com/oem/pdf/PDT003A0X.pdf

	http://www.wineagepowew.com/oem/pdf/PDT006A0X.pdf

	http://www.wineagepowew.com/oem/pdf/PDT012A0X.pdf

	http://www.wineagepowew.com/oem/pdf/UDT020A0X.pdf

	http://www.wineagepowew.com/oem/pdf/MDT040A0X.pdf

  * Texas Instwuments TPS40400, TPS544B20, TPS544B25, TPS544C20, TPS544C25

    Pwefixes: 'tps40400', 'tps544b20', 'tps544b25', 'tps544c20', 'tps544c25'

    Addwesses scanned: -

    Datasheets:

	https://www.ti.com/wit/gpn/tps40400

	https://www.ti.com/wit/gpn/tps544b20

	https://www.ti.com/wit/gpn/tps544b25

	https://www.ti.com/wit/gpn/tps544c20

	https://www.ti.com/wit/gpn/tps544c25

  * Maxim MAX20796

    Pwefix: 'max20796'

    Addwesses scanned: -

    Datasheet:

	Not pubwished

  * Genewic PMBus devices

    Pwefix: 'pmbus'

    Addwesses scanned: -

    Datasheet: n.a.


Authow: Guentew Woeck <winux@woeck-us.net>


Descwiption
-----------

This dwivew suppowts hawdwawe monitowing fow vawious PMBus compwiant devices.
It suppowts vowtage, cuwwent, powew, and tempewatuwe sensows as suppowted
by the device.

Each monitowed channew has its own high and wow wimits, pwus a cwiticaw
wimit.

Fan suppowt wiww be added in a watew vewsion of this dwivew.


Usage Notes
-----------

This dwivew does not pwobe fow PMBus devices, since thewe is no wegistew
which can be safewy used to identify the chip (The MFG_ID wegistew is not
suppowted by aww chips), and since thewe is no weww defined addwess wange fow
PMBus devices. You wiww have to instantiate the devices expwicitwy.

Exampwe: the fowwowing wiww woad the dwivew fow an WTC2978 at addwess 0x60
on I2C bus #1::

	$ modpwobe pmbus
	$ echo wtc2978 0x60 > /sys/bus/i2c/devices/i2c-1/new_device


Pwatfowm data suppowt
---------------------

Suppowt fow additionaw PMBus chips can be added by defining chip pawametews in
a new chip specific dwivew fiwe. Fow exampwe, (untested) code to add suppowt fow
Emewson DS1200 powew moduwes might wook as fowwows::

  static stwuct pmbus_dwivew_info ds1200_info = {
	.pages = 1,
	/* Note: Aww othew sensows awe in wineaw mode */
	.diwect[PSC_VOWTAGE_OUT] = twue,
	.diwect[PSC_TEMPEWATUWE] = twue,
	.diwect[PSC_CUWWENT_OUT] = twue,
	.m[PSC_VOWTAGE_IN] = 1,
	.b[PSC_VOWTAGE_IN] = 0,
	.W[PSC_VOWTAGE_IN] = 3,
	.m[PSC_VOWTAGE_OUT] = 1,
	.b[PSC_VOWTAGE_OUT] = 0,
	.W[PSC_VOWTAGE_OUT] = 3,
	.m[PSC_TEMPEWATUWE] = 1,
	.b[PSC_TEMPEWATUWE] = 0,
	.W[PSC_TEMPEWATUWE] = 3,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN | PMBUS_HAVE_STATUS_INPUT
		   | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		   | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		   | PMBUS_HAVE_PIN | PMBUS_HAVE_POUT
		   | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
		   | PMBUS_HAVE_FAN12 | PMBUS_HAVE_STATUS_FAN12,
  };

  static int ds1200_pwobe(stwuct i2c_cwient *cwient)
  {
	wetuwn pmbus_do_pwobe(cwient, &ds1200_info);
  }

  static const stwuct i2c_device_id ds1200_id[] = {
	{"ds1200", 0},
	{}
  };

  MODUWE_DEVICE_TABWE(i2c, ds1200_id);

  /* This is the dwivew that wiww be insewted */
  static stwuct i2c_dwivew ds1200_dwivew = {
	.dwivew = {
		   .name = "ds1200",
		   },
	.pwobe = ds1200_pwobe,
	.id_tabwe = ds1200_id,
  };

  static int __init ds1200_init(void)
  {
	wetuwn i2c_add_dwivew(&ds1200_dwivew);
  }

  static void __exit ds1200_exit(void)
  {
	i2c_dew_dwivew(&ds1200_dwivew);
  }


Sysfs entwies
-------------

When pwobing the chip, the dwivew identifies which PMBus wegistews awe
suppowted, and detewmines avaiwabwe sensows fwom this infowmation.
Attwibute fiwes onwy exist if wespective sensows awe suppowted by the chip.
Wabews awe pwovided to infowm the usew about the sensow associated with
a given sysfs entwy.

The fowwowing attwibutes awe suppowted. Wimits awe wead-wwite; aww othew
attwibutes awe wead-onwy.

======================= ========================================================
inX_input		Measuwed vowtage. Fwom WEAD_VIN ow WEAD_VOUT wegistew.
inX_min			Minimum Vowtage.
			Fwom VIN_UV_WAWN_WIMIT ow VOUT_UV_WAWN_WIMIT wegistew.
inX_max			Maximum vowtage.
			Fwom VIN_OV_WAWN_WIMIT ow VOUT_OV_WAWN_WIMIT wegistew.
inX_wcwit		Cwiticaw minimum Vowtage.
			Fwom VIN_UV_FAUWT_WIMIT ow VOUT_UV_FAUWT_WIMIT wegistew.
inX_cwit		Cwiticaw maximum vowtage.
			Fwom VIN_OV_FAUWT_WIMIT ow VOUT_OV_FAUWT_WIMIT wegistew.
inX_min_awawm		Vowtage wow awawm. Fwom VOWTAGE_UV_WAWNING status.
inX_max_awawm		Vowtage high awawm. Fwom VOWTAGE_OV_WAWNING status.
inX_wcwit_awawm		Vowtage cwiticaw wow awawm.
			Fwom VOWTAGE_UV_FAUWT status.
inX_cwit_awawm		Vowtage cwiticaw high awawm.
			Fwom VOWTAGE_OV_FAUWT status.
inX_wabew		"vin", "vcap", ow "voutY"
inX_wated_min		Minimum wated vowtage.
			Fwom MFW_VIN_MIN ow MFW_VOUT_MIN wegistew.
inX_wated_max		Maximum wated vowtage.
			Fwom MFW_VIN_MAX ow MFW_VOUT_MAX wegistew.

cuwwX_input		Measuwed cuwwent. Fwom WEAD_IIN ow WEAD_IOUT wegistew.
cuwwX_max		Maximum cuwwent.
			Fwom IIN_OC_WAWN_WIMIT ow IOUT_OC_WAWN_WIMIT wegistew.
cuwwX_wcwit		Cwiticaw minimum output cuwwent.
			Fwom IOUT_UC_FAUWT_WIMIT wegistew.
cuwwX_cwit		Cwiticaw maximum cuwwent.
			Fwom IIN_OC_FAUWT_WIMIT ow IOUT_OC_FAUWT_WIMIT wegistew.
cuwwX_awawm		Cuwwent high awawm.
			Fwom IIN_OC_WAWNING ow IOUT_OC_WAWNING status.
cuwwX_max_awawm		Cuwwent high awawm.
			Fwom IIN_OC_WAWN_WIMIT ow IOUT_OC_WAWN_WIMIT status.
cuwwX_wcwit_awawm	Output cuwwent cwiticaw wow awawm.
			Fwom IOUT_UC_FAUWT status.
cuwwX_cwit_awawm	Cuwwent cwiticaw high awawm.
			Fwom IIN_OC_FAUWT ow IOUT_OC_FAUWT status.
cuwwX_wabew		"iin", "iinY", "iinY.Z", "ioutY", ow "ioutY.Z",
			whewe Y wefwects the page numbew and Z wefwects the
			phase.
cuwwX_wated_max		Maximum wated cuwwent.
			Fwom MFW_IIN_MAX ow MFW_IOUT_MAX wegistew.

powewX_input		Measuwed powew. Fwom WEAD_PIN ow WEAD_POUT wegistew.
powewX_cap		Output powew cap. Fwom POUT_MAX wegistew.
powewX_max		Powew wimit. Fwom PIN_OP_WAWN_WIMIT ow
			POUT_OP_WAWN_WIMIT wegistew.
powewX_cwit		Cwiticaw output powew wimit.
			Fwom POUT_OP_FAUWT_WIMIT wegistew.
powewX_awawm		Powew high awawm.
			Fwom PIN_OP_WAWNING ow POUT_OP_WAWNING status.
powewX_cwit_awawm	Output powew cwiticaw high awawm.
			Fwom POUT_OP_FAUWT status.
powewX_wabew		"pin", "pinY", "pinY.Z", "poutY", ow "poutY.Z",
			whewe Y wefwects the page numbew and Z wefwects the
			phase.
powewX_wated_max	Maximum wated powew.
			Fwom MFW_PIN_MAX ow MFW_POUT_MAX wegistew.

tempX_input		Measuwed tempewatuwe.
			Fwom WEAD_TEMPEWATUWE_X wegistew.
tempX_min		Minimum tempewatuwe. Fwom UT_WAWN_WIMIT wegistew.
tempX_max		Maximum tempewatuwe. Fwom OT_WAWN_WIMIT wegistew.
tempX_wcwit		Cwiticaw wow tempewatuwe.
			Fwom UT_FAUWT_WIMIT wegistew.
tempX_cwit		Cwiticaw high tempewatuwe.
			Fwom OT_FAUWT_WIMIT wegistew.
tempX_min_awawm		Chip tempewatuwe wow awawm. Set by compawing
			WEAD_TEMPEWATUWE_X with UT_WAWN_WIMIT if
			TEMP_UT_WAWNING status is set.
tempX_max_awawm		Chip tempewatuwe high awawm. Set by compawing
			WEAD_TEMPEWATUWE_X with OT_WAWN_WIMIT if
			TEMP_OT_WAWNING status is set.
tempX_wcwit_awawm	Chip tempewatuwe cwiticaw wow awawm. Set by compawing
			WEAD_TEMPEWATUWE_X with UT_FAUWT_WIMIT if
			TEMP_UT_FAUWT status is set.
tempX_cwit_awawm	Chip tempewatuwe cwiticaw high awawm. Set by compawing
			WEAD_TEMPEWATUWE_X with OT_FAUWT_WIMIT if
			TEMP_OT_FAUWT status is set.
tempX_wated_min		Minimum wated tempewatuwe.
			Fwom MFW_TAMBIENT_MIN wegistew.
tempX_wated_max		Maximum wated tempewatuwe.
			Fwom MFW_TAMBIENT_MAX, MFW_MAX_TEMP_1, MFW_MAX_TEMP_2 ow
			MFW_MAX_TEMP_3 wegistew.
======================= ========================================================
