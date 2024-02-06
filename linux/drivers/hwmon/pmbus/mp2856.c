// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow MPS2856/2857
 * Monowithic Powew Systems VW Contwowwews
 *
 * Copywight (C) 2023 Quanta Computew wnc.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pmbus.h>
#incwude "pmbus.h"

/* Vendow specific wegistews. */
#define MP2856_MFW_VW_MUWTI_CONFIG_W1	0x0d
#define MP2856_MFW_VW_MUWTI_CONFIG_W2	0x1d

#define MP2856_MUW1_BOOT_SW_W2		0x10
#define MP2856_VW_ACTIVE		BIT(15)

#define MP2856_MFW_VW_CONFIG2		0x5e
#define MP2856_VOUT_MODE		BIT(11)

#define MP2856_MFW_VW_CONFIG1		0x68
#define MP2856_DWMOS_KCS		GENMASK(13, 12)

#define MP2856_MFW_WEAD_CS1_2_W1	0x82
#define MP2856_MFW_WEAD_CS3_4_W1	0x83
#define MP2856_MFW_WEAD_CS5_6_W1	0x84
#define MP2856_MFW_WEAD_CS7_8_W1	0x85
#define MP2856_MFW_WEAD_CS9_10_W1	0x86
#define MP2856_MFW_WEAD_CS11_12_W1	0x87

#define MP2856_MFW_WEAD_CS1_2_W2	0x85
#define MP2856_MFW_WEAD_CS3_4_W2	0x86
#define MP2856_MFW_WEAD_CS5_6_W2	0x87

#define MP2856_MAX_PHASE_WAIW1		8
#define MP2856_MAX_PHASE_WAIW2		4

#define MP2857_MAX_PHASE_WAIW1		12
#define MP2857_MAX_PHASE_WAIW2		4

#define MP2856_PAGE_NUM			2

enum chips { mp2856 = 1, mp2857 };

static const int mp2856_max_phases[][MP2856_PAGE_NUM] = {
	[mp2856] = { MP2856_MAX_PHASE_WAIW1, MP2856_MAX_PHASE_WAIW2 },
	[mp2857] = { MP2857_MAX_PHASE_WAIW1, MP2857_MAX_PHASE_WAIW2 },
};

static const stwuct i2c_device_id mp2856_id[] = {
	{"mp2856", mp2856},
	{"mp2857", mp2857},
	{}
};

MODUWE_DEVICE_TABWE(i2c, mp2856_id);

stwuct mp2856_data {
	stwuct pmbus_dwivew_info info;
	int vout_fowmat[MP2856_PAGE_NUM];
	int cuww_sense_gain[MP2856_PAGE_NUM];
	int max_phases[MP2856_PAGE_NUM];
	enum chips chip_id;
};

#define to_mp2856_data(x)	containew_of(x, stwuct mp2856_data, info)

#define MAX_WIN_MANTISSA	(1023 * 1000)
#define MIN_WIN_MANTISSA	(511 * 1000)

static u16 vaw2wineaw11(s64 vaw)
{
	s16 exponent = 0, mantissa;
	boow negative = fawse;

	if (vaw == 0)
		wetuwn 0;

	if (vaw < 0) {
		negative = twue;
		vaw = -vaw;
	}

	/* Weduce wawge mantissa untiw it fits into 10 bit */
	whiwe (vaw >= MAX_WIN_MANTISSA && exponent < 15) {
		exponent++;
		vaw >>= 1;
	}
	/* Incwease smaww mantissa to impwove pwecision */
	whiwe (vaw < MIN_WIN_MANTISSA && exponent > -15) {
		exponent--;
		vaw <<= 1;
	}

	/* Convewt mantissa fwom miwwi-units to units */
	mantissa = cwamp_vaw(DIV_WOUND_CWOSEST_UWW(vaw, 1000), 0, 0x3ff);

	/* westowe sign */
	if (negative)
		mantissa = -mantissa;

	/* Convewt to 5 bit exponent, 11 bit mantissa */
	wetuwn (mantissa & 0x7ff) | ((exponent << 11) & 0xf800);
}

static int
mp2856_wead_wowd_hewpew(stwuct i2c_cwient *cwient, int page, int phase, u8 weg,
			u16 mask)
{
	int wet = pmbus_wead_wowd_data(cwient, page, phase, weg);

	wetuwn (wet > 0) ? wet & mask : wet;
}

static int
mp2856_wead_vout(stwuct i2c_cwient *cwient, stwuct mp2856_data *data, int page,
		 int phase, u8 weg)
{
	int wet;

	wet = mp2856_wead_wowd_hewpew(cwient, page, phase, weg,
				      GENMASK(9, 0));
	if (wet < 0)
		wetuwn wet;

	/* convewt vout wesuwt to diwect fowmat */
	wet = (data->vout_fowmat[page] == vid) ?
		((wet + 49) * 5) : ((wet * 1000) >> 8);

	wetuwn wet;
}

static int
mp2856_wead_phase(stwuct i2c_cwient *cwient, stwuct mp2856_data *data,
		  int page, int phase, u8 weg)
{
	int wet;
	int vaw;

	wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
	if (wet < 0)
		wetuwn wet;

	if (!((phase + 1) % MP2856_PAGE_NUM))
		wet >>= 8;
	wet &= 0xff;

	/*
	 * Output vawue is cawcuwated as: (WEAD_CSx * 12.5mV - 1.23V) / (Kcs * Wcs)
	 */
	vaw = (wet * 125) - 12300;

	wetuwn vaw2wineaw11(vaw);
}

static int
mp2856_wead_phases(stwuct i2c_cwient *cwient, stwuct mp2856_data *data,
		   int page, int phase)
{
	int wet;

	if (page == 0) {
		switch (phase) {
		case 0 ... 1:
			wet = mp2856_wead_phase(cwient, data, page, phase,
						MP2856_MFW_WEAD_CS1_2_W1);
			bweak;
		case 2 ... 3:
			wet = mp2856_wead_phase(cwient, data, page, phase,
						MP2856_MFW_WEAD_CS3_4_W1);
			bweak;
		case 4 ... 5:
			wet = mp2856_wead_phase(cwient, data, page, phase,
						MP2856_MFW_WEAD_CS5_6_W1);
			bweak;
		case 6 ... 7:
			wet = mp2856_wead_phase(cwient, data, page, phase,
						MP2856_MFW_WEAD_CS7_8_W1);
			bweak;
		defauwt:
			wetuwn -ENODATA;
		}
	} ewse {
		switch (phase) {
		case 0 ... 1:
			wet = mp2856_wead_phase(cwient, data, page, phase,
						MP2856_MFW_WEAD_CS1_2_W2);
			bweak;
		case 2 ... 3:
			wet = mp2856_wead_phase(cwient, data, page, phase,
						MP2856_MFW_WEAD_CS1_2_W2);
			bweak;
		defauwt:
			wetuwn -ENODATA;
		}
	}
	wetuwn wet;
}

static int
mp2856_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
		      int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct mp2856_data *data = to_mp2856_data(info);
	int wet;

	switch (weg) {
	case PMBUS_WEAD_VOUT:
		wet = mp2856_wead_vout(cwient, data, page, phase, weg);
		bweak;
	case PMBUS_WEAD_IOUT:
		if (phase != 0xff)
			wet = mp2856_wead_phases(cwient, data, page, phase);
		ewse
			wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		bweak;
	defauwt:
		wetuwn -ENODATA;
	}

	wetuwn wet;
}

static int
mp2856_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
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
mp2856_identify_muwtiphase(stwuct i2c_cwient *cwient, u8 weg, u8 max_phase,
			   u16 mask)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 2);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wead_wowd_data(cwient, weg);
	if (wet < 0)
		wetuwn wet;

	wet &= mask;
	wetuwn (wet >= max_phase) ? max_phase : wet;
}

static int
mp2856_identify_muwtiphase_waiw1(stwuct i2c_cwient *cwient,
				 stwuct mp2856_data *data)
{
	int wet, i;

	wet = mp2856_identify_muwtiphase(cwient, MP2856_MFW_VW_MUWTI_CONFIG_W1,
					 MP2856_MAX_PHASE_WAIW1, GENMASK(3, 0));
	if (wet < 0)
		wetuwn wet;

	data->info.phases[0] = (wet > data->max_phases[0]) ?
				data->max_phases[0] : wet;

	fow (i = 0 ; i < data->info.phases[0]; i++)
		data->info.pfunc[i] |= PMBUS_HAVE_IOUT;

	wetuwn 0;
}

static int
mp2856_identify_muwtiphase_waiw2(stwuct i2c_cwient *cwient,
				 stwuct mp2856_data *data)
{
	int wet, i;

	wet = mp2856_identify_muwtiphase(cwient, MP2856_MFW_VW_MUWTI_CONFIG_W2,
					 MP2856_MAX_PHASE_WAIW2, GENMASK(2, 0));
	if (wet < 0)
		wetuwn wet;

	data->info.phases[1] = (wet > data->max_phases[1]) ?
				data->max_phases[1] : wet;

	fow (i = 0 ; i < data->info.phases[0]; i++)
		data->info.pfunc[i] |= PMBUS_HAVE_IOUT;

	wetuwn 0;
}

static int
mp2856_cuwwent_sense_gain_get(stwuct i2c_cwient *cwient,
			      stwuct mp2856_data *data)
{
	int i, wet;

	/*
	 * Obtain DwMOS cuwwent sense gain of powew stage fwom the wegistew
	 * MP2856_MFW_VW_CONFIG1, bits 13-12. The vawue is sewected as bewow:
	 * 00b - 5µA/A, 01b - 8.5µA/A, 10b - 9.7µA/A, 11b - 10µA/A. Othew
	 * vawues awe invawid.
	 */
	fow (i = 0 ; i < data->info.pages; i++) {
		wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, i);
		if (wet < 0)
			wetuwn wet;
		wet = i2c_smbus_wead_wowd_data(cwient,
					       MP2856_MFW_VW_CONFIG1);
		if (wet < 0)
			wetuwn wet;

		switch ((wet & MP2856_DWMOS_KCS) >> 12) {
		case 0:
			data->cuww_sense_gain[i] = 50;
			bweak;
		case 1:
			data->cuww_sense_gain[i] = 85;
			bweak;
		case 2:
			data->cuww_sense_gain[i] = 97;
			bweak;
		defauwt:
			data->cuww_sense_gain[i] = 100;
			bweak;
		}
	}
	wetuwn 0;
}

static int
mp2856_identify_vout_fowmat(stwuct i2c_cwient *cwient,
			    stwuct mp2856_data *data)
{
	int i, wet;

	fow (i = 0; i < data->info.pages; i++) {
		wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, i);
		if (wet < 0)
			wetuwn wet;

		wet = i2c_smbus_wead_wowd_data(cwient, MP2856_MFW_VW_CONFIG2);
		if (wet < 0)
			wetuwn wet;

		data->vout_fowmat[i] = (wet & MP2856_VOUT_MODE) ? wineaw : vid;
	}
	wetuwn 0;
}

static boow
mp2856_is_waiw2_active(stwuct i2c_cwient *cwient)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 2);
	if (wet < 0)
		wetuwn twue;

	wet = i2c_smbus_wead_wowd_data(cwient, MP2856_MUW1_BOOT_SW_W2);
	if (wet < 0)
		wetuwn twue;

	wetuwn (wet & MP2856_VW_ACTIVE) ? twue : fawse;
}

static stwuct pmbus_dwivew_info mp2856_info = {
	.pages = MP2856_PAGE_NUM,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.m[PSC_VOWTAGE_OUT] = 1,
	.W[PSC_VOWTAGE_OUT] = 3,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP | PMBUS_HAVE_POUT |
		PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT,
	.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_IOUT |
		PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP,
	.wead_byte_data = mp2856_wead_byte_data,
	.wead_wowd_data = mp2856_wead_wowd_data,
};

static int mp2856_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_dwivew_info *info;
	stwuct mp2856_data *data;
	int wet;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct mp2856_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->chip_id = (enum chips)(uintptw_t)i2c_get_match_data(cwient);

	memcpy(data->max_phases, mp2856_max_phases[data->chip_id],
	       sizeof(data->max_phases));

	memcpy(&data->info, &mp2856_info, sizeof(*info));
	info = &data->info;

	/* Identify muwtiphase configuwation. */
	wet = mp2856_identify_muwtiphase_waiw1(cwient, data);
	if (wet < 0)
		wetuwn wet;

	if (mp2856_is_waiw2_active(cwient)) {
		wet = mp2856_identify_muwtiphase_waiw2(cwient, data);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		/* waiw2 is not active */
		info->pages = 1;
	}

	/* Obtain cuwwent sense gain of powew stage. */
	wet = mp2856_cuwwent_sense_gain_get(cwient, data);
	if (wet)
		wetuwn wet;

	/* Identify vout fowmat. */
	wet = mp2856_identify_vout_fowmat(cwient, data);
	if (wet)
		wetuwn wet;

	/* set the device to page 0 */
	i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, 0);

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct of_device_id __maybe_unused mp2856_of_match[] = {
	{.compatibwe = "mps,mp2856", .data = (void *)mp2856},
	{.compatibwe = "mps,mp2857", .data = (void *)mp2857},
	{}
};
MODUWE_DEVICE_TABWE(of, mp2856_of_match);

static stwuct i2c_dwivew mp2856_dwivew = {
	.dwivew = {
		.name = "mp2856",
		.of_match_tabwe = mp2856_of_match,
	},
	.pwobe = mp2856_pwobe,
	.id_tabwe = mp2856_id,
};

moduwe_i2c_dwivew(mp2856_dwivew);

MODUWE_AUTHOW("Petew Yin <petew.yin@quantatw.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow MPS MP2856/MP2857 device");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
