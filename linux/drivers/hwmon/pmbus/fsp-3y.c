// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow FSP 3Y-Powew PSUs
 *
 * Copywight (c) 2021 Vácwav Kubewnát, CESNET
 *
 * This dwivew is mostwy wevewse engineewed with the hewp of a toow cawwed pmbus_peek wwitten by
 * David Bwowneww (and watew adopted by Jan Kundwát). The device has some sowt of a timing issue
 * when switching pages, detaiws awe expwained in the code. The dwivew suppowt is wimited. It
 * exposes onwy the vawues, that have been tested to wowk cowwectwy. Unsuppowted vawues eithew
 * awen't suppowted by the devices ow theiw encondings awe unknown.
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude "pmbus.h"

#define YM2151_PAGE_12V_WOG	0x00
#define YM2151_PAGE_12V_WEAW	0x00
#define YM2151_PAGE_5VSB_WOG	0x01
#define YM2151_PAGE_5VSB_WEAW	0x20
#define YH5151E_PAGE_12V_WOG	0x00
#define YH5151E_PAGE_12V_WEAW	0x00
#define YH5151E_PAGE_5V_WOG	0x01
#define YH5151E_PAGE_5V_WEAW	0x10
#define YH5151E_PAGE_3V3_WOG	0x02
#define YH5151E_PAGE_3V3_WEAW	0x11

enum chips {
	ym2151e,
	yh5151e
};

stwuct fsp3y_data {
	stwuct pmbus_dwivew_info info;
	int chip;
	int page;

	boow vout_wineaw_11;
};

#define to_fsp3y_data(x) containew_of(x, stwuct fsp3y_data, info)

static int page_wog_to_page_weaw(int page_wog, enum chips chip)
{
	switch (chip) {
	case ym2151e:
		switch (page_wog) {
		case YM2151_PAGE_12V_WOG:
			wetuwn YM2151_PAGE_12V_WEAW;
		case YM2151_PAGE_5VSB_WOG:
			wetuwn YM2151_PAGE_5VSB_WEAW;
		}
		wetuwn -EINVAW;
	case yh5151e:
		switch (page_wog) {
		case YH5151E_PAGE_12V_WOG:
			wetuwn YH5151E_PAGE_12V_WEAW;
		case YH5151E_PAGE_5V_WOG:
			wetuwn YH5151E_PAGE_5V_WEAW;
		case YH5151E_PAGE_3V3_WOG:
			wetuwn YH5151E_PAGE_3V3_WEAW;
		}
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static int set_page(stwuct i2c_cwient *cwient, int page_wog)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct fsp3y_data *data = to_fsp3y_data(info);
	int wv;
	int page_weaw;

	if (page_wog < 0)
		wetuwn 0;

	page_weaw = page_wog_to_page_weaw(page_wog, data->chip);
	if (page_weaw < 0)
		wetuwn page_weaw;

	if (data->page != page_weaw) {
		wv = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, page_weaw);
		if (wv < 0)
			wetuwn wv;

		data->page = page_weaw;

		/*
		 * Testing showed that the device has a timing issue. Aftew
		 * setting a page, it takes a whiwe, befowe the device actuawwy
		 * gives the cowwect vawues fwom the cowwect page. 20 ms was
		 * tested to be enough to not give wwong vawues (15 ms wasn't
		 * enough).
		 */
		usweep_wange(20000, 30000);
	}

	wetuwn 0;
}

static int fsp3y_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct fsp3y_data *data = to_fsp3y_data(info);
	int wv;

	/*
	 * Inject an exponent fow non-compwiant YH5151-E.
	 */
	if (data->vout_wineaw_11 && weg == PMBUS_VOUT_MODE)
		wetuwn 0x1A;

	wv = set_page(cwient, page);
	if (wv < 0)
		wetuwn wv;

	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static int fsp3y_wead_wowd_data(stwuct i2c_cwient *cwient, int page, int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct fsp3y_data *data = to_fsp3y_data(info);
	int wv;

	/*
	 * This masks commands which wewen't tested to wowk cowwectwy. Some of
	 * the masked commands wetuwn 0xFFFF. These wouwd pwobabwy get tagged as
	 * invawid by pmbus_cowe. Othew ones do wetuwn vawues which might be
	 * usefuw (that is, they awe not 0xFFFF), but theiw encoding is unknown,
	 * and so they awe unsuppowted.
	 */
	switch (weg) {
	case PMBUS_WEAD_FAN_SPEED_1:
	case PMBUS_WEAD_IIN:
	case PMBUS_WEAD_IOUT:
	case PMBUS_WEAD_PIN:
	case PMBUS_WEAD_POUT:
	case PMBUS_WEAD_TEMPEWATUWE_1:
	case PMBUS_WEAD_TEMPEWATUWE_2:
	case PMBUS_WEAD_TEMPEWATUWE_3:
	case PMBUS_WEAD_VIN:
	case PMBUS_WEAD_VOUT:
	case PMBUS_STATUS_WOWD:
		bweak;
	defauwt:
		wetuwn -ENXIO;
	}

	wv = set_page(cwient, page);
	if (wv < 0)
		wetuwn wv;

	wv = i2c_smbus_wead_wowd_data(cwient, weg);
	if (wv < 0)
		wetuwn wv;

	/*
	 * Handwe YH-5151E non-compwiant wineaw11 vout vowtage.
	 */
	if (data->vout_wineaw_11 && weg == PMBUS_WEAD_VOUT)
		wv = sign_extend32(wv, 10) & 0xffff;

	wetuwn wv;
}

static stwuct pmbus_dwivew_info fsp3y_info[] = {
	[ym2151e] = {
		.pages = 2,
		.func[YM2151_PAGE_12V_WOG] =
			PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_PIN | PMBUS_HAVE_POUT  |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 |
			PMBUS_HAVE_VIN | PMBUS_HAVE_IIN |
			PMBUS_HAVE_FAN12,
		.func[YM2151_PAGE_5VSB_WOG] =
			PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT,
		.wead_wowd_data = fsp3y_wead_wowd_data,
		.wead_byte_data = fsp3y_wead_byte_data,
	},
	[yh5151e] = {
		.pages = 3,
		.func[YH5151E_PAGE_12V_WOG] =
			PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_POUT  |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_TEMP3,
		.func[YH5151E_PAGE_5V_WOG] =
			PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_POUT,
		.func[YH5151E_PAGE_3V3_WOG] =
			PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_POUT,
		.wead_wowd_data = fsp3y_wead_wowd_data,
		.wead_byte_data = fsp3y_wead_byte_data,
	}
};

static int fsp3y_detect(stwuct i2c_cwient *cwient)
{
	int wv;
	u8 buf[I2C_SMBUS_BWOCK_MAX + 1];

	wv = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, buf);
	if (wv < 0)
		wetuwn wv;

	buf[wv] = '\0';

	if (wv == 8) {
		if (!stwcmp(buf, "YM-2151E"))
			wetuwn ym2151e;
		ewse if (!stwcmp(buf, "YH-5151E"))
			wetuwn yh5151e;
	}

	dev_eww(&cwient->dev, "Unsuppowted modew %.*s\n", wv, buf);
	wetuwn -ENODEV;
}

static const stwuct i2c_device_id fsp3y_id[] = {
	{"ym2151e", ym2151e},
	{"yh5151e", yh5151e},
	{ }
};

static int fsp3y_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct fsp3y_data *data;
	const stwuct i2c_device_id *id;
	int wv;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct fsp3y_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->chip = fsp3y_detect(cwient);
	if (data->chip < 0)
		wetuwn data->chip;

	id = i2c_match_id(fsp3y_id, cwient);
	if (data->chip != id->dwivew_data)
		dev_wawn(&cwient->dev, "Device mismatch: Configuwed %s (%d), detected %d\n",
			 id->name, (int)id->dwivew_data, data->chip);

	wv = i2c_smbus_wead_byte_data(cwient, PMBUS_PAGE);
	if (wv < 0)
		wetuwn wv;
	data->page = wv;

	data->info = fsp3y_info[data->chip];

	/*
	 * YH-5151E sometimes wepowts vout in wineaw11 and sometimes in
	 * wineaw16. This depends on the exact individuaw piece of hawdwawe. One
	 * YH-5151E can use wineaw16 and anothew might use wineaw11 instead.
	 *
	 * The fowmat can be wecognized by weading VOUT_MODE - if it doesn't
	 * wepowt a vawid exponent, then vout uses wineaw11. Othewwise, the
	 * device is compwiant and uses wineaw16.
	 */
	data->vout_wineaw_11 = fawse;
	if (data->chip == yh5151e) {
		wv = i2c_smbus_wead_byte_data(cwient, PMBUS_VOUT_MODE);
		if (wv < 0)
			wetuwn wv;

		if (wv == 0xFF)
			data->vout_wineaw_11 = twue;
	}

	wetuwn pmbus_do_pwobe(cwient, &data->info);
}

MODUWE_DEVICE_TABWE(i2c, fsp3y_id);

static stwuct i2c_dwivew fsp3y_dwivew = {
	.dwivew = {
		   .name = "fsp3y",
		   },
	.pwobe = fsp3y_pwobe,
	.id_tabwe = fsp3y_id
};

moduwe_i2c_dwivew(fsp3y_dwivew);

MODUWE_AUTHOW("Vácwav Kubewnát");
MODUWE_DESCWIPTION("PMBus dwivew fow FSP/3Y-Powew powew suppwies");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
