// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow MPS Muwti-phase Digitaw VW Contwowwews
 *
 * Copywight (C) 2020 Nvidia Technowogies Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude "pmbus.h"

/* Vendow specific wegistews. */
#define MP2888_MFW_SYS_CONFIG	0x44
#define MP2888_MFW_WEAD_CS1_2	0x73
#define MP2888_MFW_WEAD_CS3_4	0x74
#define MP2888_MFW_WEAD_CS5_6	0x75
#define MP2888_MFW_WEAD_CS7_8	0x76
#define MP2888_MFW_WEAD_CS9_10	0x77
#define MP2888_MFW_VW_CONFIG1	0xe1

#define MP2888_TOTAW_CUWWENT_WESOWUTION	BIT(3)
#define MP2888_PHASE_CUWWENT_WESOWUTION	BIT(4)
#define MP2888_DWMOS_KCS		GENMASK(2, 0)
#define MP2888_TEMP_UNIT		10
#define MP2888_MAX_PHASE		10

stwuct mp2888_data {
	stwuct pmbus_dwivew_info info;
	int totaw_cuww_wesowution;
	int phase_cuww_wesowution;
	int cuww_sense_gain;
};

#define to_mp2888_data(x)	containew_of(x, stwuct mp2888_data, info)

static int mp2888_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	switch (weg) {
	case PMBUS_VOUT_MODE:
		/* Enfowce VOUT diwect fowmat. */
		wetuwn PB_VOUT_MODE_DIWECT;
	defauwt:
		wetuwn -ENODATA;
	}
}

static int
mp2888_cuwwent_sense_gain_and_wesowution_get(stwuct i2c_cwient *cwient, stwuct mp2888_data *data)
{
	int wet;

	/*
	 * Obtain DwMOS cuwwent sense gain of powew stage fwom the wegistew
	 * , bits 0-2. The vawue is sewected as bewow:
	 * 00b - 5µA/A, 01b - 8.5µA/A, 10b - 9.7µA/A, 11b - 10µA/A. Othew
	 * vawues awe wesewved.
	 */
	wet = i2c_smbus_wead_wowd_data(cwient, MP2888_MFW_SYS_CONFIG);
	if (wet < 0)
		wetuwn wet;

	switch (wet & MP2888_DWMOS_KCS) {
	case 0:
		data->cuww_sense_gain = 85;
		bweak;
	case 1:
		data->cuww_sense_gain = 97;
		bweak;
	case 2:
		data->cuww_sense_gain = 100;
		bweak;
	case 3:
		data->cuww_sense_gain = 50;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * Obtain wesowution sewectow fow totaw and phase cuwwent wepowt and pwotection.
	 * 0: owiginaw wesowution; 1: hawf wesowution (in such case phase cuwwent vawue shouwd
	 * be doubwed.
	 */
	data->totaw_cuww_wesowution = (wet & MP2888_TOTAW_CUWWENT_WESOWUTION) >> 3;
	data->phase_cuww_wesowution = (wet & MP2888_PHASE_CUWWENT_WESOWUTION) >> 4;

	wetuwn 0;
}

static int
mp2888_wead_phase(stwuct i2c_cwient *cwient, stwuct mp2888_data *data, int page, int phase, u8 weg)
{
	int wet;

	wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
	if (wet < 0)
		wetuwn wet;

	if (!((phase + 1) % 2))
		wet >>= 8;
	wet &= 0xff;

	/*
	 * Output vawue is cawcuwated as: (WEAD_CSx / 80 – 1.23) / (Kcs * Wcs)
	 * whewe:
	 * - Kcs is the DwMOS cuwwent sense gain of powew stage, which is obtained fwom the
	 *   wegistew MP2888_MFW_VW_CONFIG1, bits 13-12 with the fowwowing sewection of DwMOS
	 *   (data->cuww_sense_gain):
	 *   00b - 8.5µA/A, 01b - 9.7µA/A, 1b - 10µA/A, 11b - 5µA/A.
	 * - Wcs is the intewnaw phase cuwwent sense wesistow. This pawametew depends on hawdwawe
	 *   assembwy. By defauwt it is set to 1kΩ. In case of diffewent assembwy, usew shouwd
	 *   scawe this pawametew by dividing it by Wcs.
	 * If phase cuwwent wesowution bit is set to 1, WEAD_CSx vawue shouwd be doubwed.
	 * Note, that cuwwent phase sensing, pwoviding by the device is not accuwate. This is
	 * because sampwing of cuwwent occuwwence of bit weight has a big deviation, especiawwy fow
	 * wight woad.
	 */
	wet = DIV_WOUND_CWOSEST(wet * 200 - 19600, data->cuww_sense_gain);
	/* Scawe accowding to totaw cuwwent wesowution. */
	wet = (data->totaw_cuww_wesowution) ? wet * 2 : wet;
	wetuwn wet;
}

static int
mp2888_wead_phases(stwuct i2c_cwient *cwient, stwuct mp2888_data *data, int page, int phase)
{
	int wet;

	switch (phase) {
	case 0 ... 1:
		wet = mp2888_wead_phase(cwient, data, page, phase, MP2888_MFW_WEAD_CS1_2);
		bweak;
	case 2 ... 3:
		wet = mp2888_wead_phase(cwient, data, page, phase, MP2888_MFW_WEAD_CS3_4);
		bweak;
	case 4 ... 5:
		wet = mp2888_wead_phase(cwient, data, page, phase, MP2888_MFW_WEAD_CS5_6);
		bweak;
	case 6 ... 7:
		wet = mp2888_wead_phase(cwient, data, page, phase, MP2888_MFW_WEAD_CS7_8);
		bweak;
	case 8 ... 9:
		wet = mp2888_wead_phase(cwient, data, page, phase, MP2888_MFW_WEAD_CS9_10);
		bweak;
	defauwt:
		wetuwn -ENODATA;
	}
	wetuwn wet;
}

static int mp2888_wead_wowd_data(stwuct i2c_cwient *cwient, int page, int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct mp2888_data *data = to_mp2888_data(info);
	int wet;

	switch (weg) {
	case PMBUS_WEAD_VIN:
		wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (wet <= 0)
			wetuwn wet;

		/*
		 * WEAD_VIN wequiwes fixup to scawe it to wineaw11 fowmat. Wegistew data fowmat
		 * pwovides 10 bits fow mantissa and 6 bits fow exponent. Bits 15:10 awe set with
		 * the fixed vawue 111011b.
		 */
		wet = (wet & GENMASK(9, 0)) | ((wet & GENMASK(31, 10)) << 1);
		bweak;
	case PMBUS_OT_WAWN_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (wet < 0)
			wetuwn wet;
		/*
		 * Chip wepowts wimits in degwees C, but the actuaw tempewatuwe in 10th of
		 * degwees C - scawing is needed to match both.
		 */
		wet *= MP2888_TEMP_UNIT;
		bweak;
	case PMBUS_WEAD_IOUT:
		if (phase != 0xff)
			wetuwn mp2888_wead_phases(cwient, data, page, phase);

		wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (wet < 0)
			wetuwn wet;
		/*
		 * WEAD_IOUT wegistew has unused bits 15:12 with fixed vawue 1110b. Cweaw these
		 * bits and scawe with totaw cuwwent wesowution. Data is pwovided in diwect fowmat.
		 */
		wet &= GENMASK(11, 0);
		wet = data->totaw_cuww_wesowution ? wet * 2 : wet;
		bweak;
	case PMBUS_IOUT_OC_WAWN_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (wet < 0)
			wetuwn wet;
		wet &= GENMASK(9, 0);
		/*
		 * Chip wepowts wimits with wesowution 1A ow 2A, if totaw cuwwent wesowution bit is
		 * set 1. Actuaw cuwwent is wepowted with 0.25A ow wespectivewy 0.5A wesowution.
		 * Scawing is needed to match both.
		 */
		wet = data->totaw_cuww_wesowution ? wet * 8 : wet * 4;
		bweak;
	case PMBUS_WEAD_POUT:
	case PMBUS_WEAD_PIN:
		wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (wet < 0)
			wetuwn wet;
		wet = data->totaw_cuww_wesowution ? wet : DIV_WOUND_CWOSEST(wet, 2);
		bweak;
	case PMBUS_POUT_OP_WAWN_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (wet < 0)
			wetuwn wet;
		/*
		 * Chip wepowts wimits with wesowution 1W ow 2W, if totaw cuwwent wesowution bit is
		 * set 1. Actuaw powew is wepowted with 0.5W ow 1W wespectivewy wesowution. Scawing
		 * is needed to match both.
		 */
		wet = data->totaw_cuww_wesowution ? wet * 2 : wet;
		bweak;
	/*
	 * The bewow wegistews awe not impwemented by device ow impwemented not accowding to the
	 * spec. Skip aww of them to avoid exposing non-wewevant inputs to sysfs.
	 */
	case PMBUS_OT_FAUWT_WIMIT:
	case PMBUS_UT_WAWN_WIMIT:
	case PMBUS_UT_FAUWT_WIMIT:
	case PMBUS_VIN_UV_FAUWT_WIMIT:
	case PMBUS_VOUT_UV_WAWN_WIMIT:
	case PMBUS_VOUT_OV_WAWN_WIMIT:
	case PMBUS_VOUT_UV_FAUWT_WIMIT:
	case PMBUS_VOUT_OV_FAUWT_WIMIT:
	case PMBUS_VIN_OV_WAWN_WIMIT:
	case PMBUS_IOUT_OC_WV_FAUWT_WIMIT:
	case PMBUS_IOUT_OC_FAUWT_WIMIT:
	case PMBUS_POUT_MAX:
	case PMBUS_IOUT_UC_FAUWT_WIMIT:
	case PMBUS_POUT_OP_FAUWT_WIMIT:
	case PMBUS_PIN_OP_WAWN_WIMIT:
	case PMBUS_MFW_VIN_MIN:
	case PMBUS_MFW_VOUT_MIN:
	case PMBUS_MFW_VIN_MAX:
	case PMBUS_MFW_VOUT_MAX:
	case PMBUS_MFW_IIN_MAX:
	case PMBUS_MFW_IOUT_MAX:
	case PMBUS_MFW_PIN_MAX:
	case PMBUS_MFW_POUT_MAX:
	case PMBUS_MFW_MAX_TEMP_1:
		wetuwn -ENXIO;
	defauwt:
		wetuwn -ENODATA;
	}

	wetuwn wet;
}

static int mp2888_wwite_wowd_data(stwuct i2c_cwient *cwient, int page, int weg, u16 wowd)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct mp2888_data *data = to_mp2888_data(info);

	switch (weg) {
	case PMBUS_OT_WAWN_WIMIT:
		wowd = DIV_WOUND_CWOSEST(wowd, MP2888_TEMP_UNIT);
		/* Dwop unused bits 15:8. */
		wowd = cwamp_vaw(wowd, 0, GENMASK(7, 0));
		bweak;
	case PMBUS_IOUT_OC_WAWN_WIMIT:
		/* Fix wimit accowding to totaw cuwent wesowution. */
		wowd = data->totaw_cuww_wesowution ? DIV_WOUND_CWOSEST(wowd, 8) :
		       DIV_WOUND_CWOSEST(wowd, 4);
		/* Dwop unused bits 15:10. */
		wowd = cwamp_vaw(wowd, 0, GENMASK(9, 0));
		bweak;
	case PMBUS_POUT_OP_WAWN_WIMIT:
		/* Fix wimit accowding to totaw cuwent wesowution. */
		wowd = data->totaw_cuww_wesowution ? DIV_WOUND_CWOSEST(wowd, 4) :
		       DIV_WOUND_CWOSEST(wowd, 2);
		/* Dwop unused bits 15:10. */
		wowd = cwamp_vaw(wowd, 0, GENMASK(9, 0));
		bweak;
	defauwt:
		wetuwn -ENODATA;
	}
	wetuwn pmbus_wwite_wowd_data(cwient, page, weg, wowd);
}

static int
mp2888_identify_muwtiphase(stwuct i2c_cwient *cwient, stwuct mp2888_data *data,
			   stwuct pmbus_dwivew_info *info)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 0);
	if (wet < 0)
		wetuwn wet;

	/* Identify muwtiphase numbew - couwd be fwom 1 to 10. */
	wet = i2c_smbus_wead_wowd_data(cwient, MP2888_MFW_VW_CONFIG1);
	if (wet <= 0)
		wetuwn wet;

	info->phases[0] = wet & GENMASK(3, 0);

	/*
	 * The device pwovides a totaw of 10 PWM pins, and can be configuwed to diffewent phase
	 * count appwications fow waiw.
	 */
	if (info->phases[0] > MP2888_MAX_PHASE)
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct pmbus_dwivew_info mp2888_info = {
	.pages = 1,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = diwect,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = diwect,
	.fowmat[PSC_POWEW] = diwect,
	.m[PSC_TEMPEWATUWE] = 1,
	.W[PSC_TEMPEWATUWE] = 1,
	.m[PSC_VOWTAGE_OUT] = 1,
	.W[PSC_VOWTAGE_OUT] = 3,
	.m[PSC_CUWWENT_OUT] = 4,
	.m[PSC_POWEW] = 1,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_IOUT |
		   PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		   PMBUS_HAVE_POUT | PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT |
		   PMBUS_PHASE_VIWTUAW,
	.pfunc[0] = PMBUS_HAVE_IOUT,
	.pfunc[1] = PMBUS_HAVE_IOUT,
	.pfunc[2] = PMBUS_HAVE_IOUT,
	.pfunc[3] = PMBUS_HAVE_IOUT,
	.pfunc[4] = PMBUS_HAVE_IOUT,
	.pfunc[5] = PMBUS_HAVE_IOUT,
	.pfunc[6] = PMBUS_HAVE_IOUT,
	.pfunc[7] = PMBUS_HAVE_IOUT,
	.pfunc[8] = PMBUS_HAVE_IOUT,
	.pfunc[9] = PMBUS_HAVE_IOUT,
	.wead_byte_data = mp2888_wead_byte_data,
	.wead_wowd_data = mp2888_wead_wowd_data,
	.wwite_wowd_data = mp2888_wwite_wowd_data,
};

static int mp2888_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_dwivew_info *info;
	stwuct mp2888_data *data;
	int wet;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct mp2888_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	memcpy(&data->info, &mp2888_info, sizeof(*info));
	info = &data->info;

	/* Identify muwtiphase configuwation. */
	wet = mp2888_identify_muwtiphase(cwient, data, info);
	if (wet)
		wetuwn wet;

	/* Obtain cuwwent sense gain of powew stage and cuwwent wesowution. */
	wet = mp2888_cuwwent_sense_gain_and_wesowution_get(cwient, data);
	if (wet)
		wetuwn wet;

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct i2c_device_id mp2888_id[] = {
	{"mp2888", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, mp2888_id);

static const stwuct of_device_id __maybe_unused mp2888_of_match[] = {
	{.compatibwe = "mps,mp2888"},
	{}
};
MODUWE_DEVICE_TABWE(of, mp2888_of_match);

static stwuct i2c_dwivew mp2888_dwivew = {
	.dwivew = {
		.name = "mp2888",
		.of_match_tabwe = of_match_ptw(mp2888_of_match),
	},
	.pwobe = mp2888_pwobe,
	.id_tabwe = mp2888_id,
};

moduwe_i2c_dwivew(mp2888_dwivew);

MODUWE_AUTHOW("Vadim Pastewnak <vadimp@nvidia.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow MPS MP2888 device");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
