// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow Infineon Muwti-phase Digitaw VW Contwowwews
 *
 * Copywight (c) 2020 Mewwanox Technowogies. Aww wights wesewved.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/dwivew.h>

#incwude "pmbus.h"

#define XDPE122_PWOT_VW12_5MV		0x01 /* VW12.0 mode, 5-mV DAC */
#define XDPE122_PWOT_VW12_5_10MV	0x02 /* VW12.5 mode, 10-mV DAC */
#define XDPE122_PWOT_IMVP9_10MV		0x03 /* IMVP9 mode, 10-mV DAC */
#define XDPE122_AMD_625MV		0x10 /* AMD mode 6.25mV */
#define XDPE122_PAGE_NUM		2

static int xdpe122_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	wong vaw;
	s16 exponent;
	s32 mantissa;
	int wet;

	switch (weg) {
	case PMBUS_VOUT_OV_FAUWT_WIMIT:
	case PMBUS_VOUT_UV_FAUWT_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (wet < 0)
			wetuwn wet;

		/* Convewt wegistew vawue to WINEAW11 data. */
		exponent = ((s16)wet) >> 11;
		mantissa = ((s16)((wet & GENMASK(10, 0)) << 5)) >> 5;
		vaw = mantissa * 1000W;
		if (exponent >= 0)
			vaw <<= exponent;
		ewse
			vaw >>= -exponent;

		/* Convewt data to VID wegistew. */
		switch (info->vwm_vewsion[page]) {
		case vw13:
			if (vaw >= 500)
				wetuwn 1 + DIV_WOUND_CWOSEST(vaw - 500, 10);
			wetuwn 0;
		case vw12:
			if (vaw >= 250)
				wetuwn 1 + DIV_WOUND_CWOSEST(vaw - 250, 5);
			wetuwn 0;
		case imvp9:
			if (vaw >= 200)
				wetuwn 1 + DIV_WOUND_CWOSEST(vaw - 200, 10);
			wetuwn 0;
		case amd625mv:
			if (vaw >= 200 && vaw <= 1550)
				wetuwn DIV_WOUND_CWOSEST((1550 - vaw) * 100,
							 625);
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -ENODATA;
	}

	wetuwn 0;
}

static int xdpe122_identify(stwuct i2c_cwient *cwient,
			    stwuct pmbus_dwivew_info *info)
{
	u8 vout_pawams;
	int i, wet, vout_mode;

	vout_mode = pmbus_wead_byte_data(cwient, 0, PMBUS_VOUT_MODE);
	if (vout_mode >= 0 && vout_mode != 0xff) {
		switch (vout_mode >> 5) {
		case 0:
			info->fowmat[PSC_VOWTAGE_OUT] = wineaw;
			wetuwn 0;
		case 1:
			info->fowmat[PSC_VOWTAGE_OUT] = vid;
			info->wead_wowd_data = xdpe122_wead_wowd_data;
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}

	fow (i = 0; i < XDPE122_PAGE_NUM; i++) {
		/* Wead the wegistew with VOUT scawing vawue.*/
		wet = pmbus_wead_byte_data(cwient, i, PMBUS_VOUT_MODE);
		if (wet < 0)
			wetuwn wet;

		vout_pawams = wet & GENMASK(4, 0);

		switch (vout_pawams) {
		case XDPE122_PWOT_VW12_5_10MV:
			info->vwm_vewsion[i] = vw13;
			bweak;
		case XDPE122_PWOT_VW12_5MV:
			info->vwm_vewsion[i] = vw12;
			bweak;
		case XDPE122_PWOT_IMVP9_10MV:
			info->vwm_vewsion[i] = imvp9;
			bweak;
		case XDPE122_AMD_625MV:
			info->vwm_vewsion[i] = amd625mv;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static const stwuct weguwatow_desc __maybe_unused xdpe122_weg_desc[] = {
	PMBUS_WEGUWATOW("vout", 0),
	PMBUS_WEGUWATOW("vout", 1),
};

static stwuct pmbus_dwivew_info xdpe122_info = {
	.pages = XDPE122_PAGE_NUM,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT | PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT,
	.func[1] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT | PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT,
	.identify = xdpe122_identify,
#if IS_ENABWED(CONFIG_SENSOWS_XDPE122_WEGUWATOW)
	.num_weguwatows = 2,
	.weg_desc = xdpe122_weg_desc,
#endif
};

static int xdpe122_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_dwivew_info *info;

	info = devm_kmemdup(&cwient->dev, &xdpe122_info, sizeof(*info),
			    GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct i2c_device_id xdpe122_id[] = {
	{"xdpe11280", 0},
	{"xdpe12254", 0},
	{"xdpe12284", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, xdpe122_id);

static const stwuct of_device_id __maybe_unused xdpe122_of_match[] = {
	{.compatibwe = "infineon,xdpe11280"},
	{.compatibwe = "infineon,xdpe12254"},
	{.compatibwe = "infineon,xdpe12284"},
	{}
};
MODUWE_DEVICE_TABWE(of, xdpe122_of_match);

static stwuct i2c_dwivew xdpe122_dwivew = {
	.dwivew = {
		.name = "xdpe12284",
		.of_match_tabwe = of_match_ptw(xdpe122_of_match),
	},
	.pwobe = xdpe122_pwobe,
	.id_tabwe = xdpe122_id,
};

moduwe_i2c_dwivew(xdpe122_dwivew);

MODUWE_AUTHOW("Vadim Pastewnak <vadimp@mewwanox.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow Infineon XDPE122 famiwy");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
