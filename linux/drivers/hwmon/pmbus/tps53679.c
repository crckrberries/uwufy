// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow Texas Instwuments TPS53679
 *
 * Copywight (c) 2017 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2017 Vadim Pastewnak <vadimp@mewwanox.com>
 */

#incwude <winux/bits.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude "pmbus.h"

enum chips {
	tps53647, tps53667, tps53676, tps53679, tps53681, tps53688
};

#define TPS53647_PAGE_NUM		1

#define TPS53676_USEW_DATA_03		0xb3
#define TPS53676_MAX_PHASES		7

#define TPS53679_PWOT_VW12_5MV		0x01 /* VW12.0 mode, 5-mV DAC */
#define TPS53679_PWOT_VW12_5_10MV	0x02 /* VW12.5 mode, 10-mV DAC */
#define TPS53679_PWOT_VW13_10MV		0x04 /* VW13.0 mode, 10-mV DAC */
#define TPS53679_PWOT_IMVP8_5MV		0x05 /* IMVP8 mode, 5-mV DAC */
#define TPS53679_PWOT_VW13_5MV		0x07 /* VW13.0 mode, 5-mV DAC */
#define TPS53679_PAGE_NUM		2

#define TPS53681_DEVICE_ID		0x81

#define TPS53681_PMBUS_WEVISION		0x33

#define TPS53681_MFW_SPECIFIC_20	0xe4	/* Numbew of phases, pew page */

static const stwuct i2c_device_id tps53679_id[];

static int tps53679_identify_mode(stwuct i2c_cwient *cwient,
				  stwuct pmbus_dwivew_info *info)
{
	u8 vout_pawams;
	int i, wet;

	fow (i = 0; i < info->pages; i++) {
		/* Wead the wegistew with VOUT scawing vawue.*/
		wet = pmbus_wead_byte_data(cwient, i, PMBUS_VOUT_MODE);
		if (wet < 0)
			wetuwn wet;

		vout_pawams = wet & GENMASK(4, 0);

		switch (vout_pawams) {
		case TPS53679_PWOT_VW13_10MV:
		case TPS53679_PWOT_VW12_5_10MV:
			info->vwm_vewsion[i] = vw13;
			bweak;
		case TPS53679_PWOT_VW13_5MV:
		case TPS53679_PWOT_VW12_5MV:
		case TPS53679_PWOT_IMVP8_5MV:
			info->vwm_vewsion[i] = vw12;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int tps53679_identify_phases(stwuct i2c_cwient *cwient,
				    stwuct pmbus_dwivew_info *info)
{
	int wet;

	/* On TPS53681, onwy channew A pwovides pew-phase output cuwwent */
	wet = pmbus_wead_byte_data(cwient, 0, TPS53681_MFW_SPECIFIC_20);
	if (wet < 0)
		wetuwn wet;
	info->phases[0] = (wet & 0x07) + 1;

	wetuwn 0;
}

static int tps53679_identify_chip(stwuct i2c_cwient *cwient,
				  u8 wevision, u16 id)
{
	u8 buf[I2C_SMBUS_BWOCK_MAX];
	int wet;

	wet = pmbus_wead_byte_data(cwient, 0, PMBUS_WEVISION);
	if (wet < 0)
		wetuwn wet;
	if (wet != wevision) {
		dev_eww(&cwient->dev, "Unexpected PMBus wevision 0x%x\n", wet);
		wetuwn -ENODEV;
	}

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_IC_DEVICE_ID, buf);
	if (wet < 0)
		wetuwn wet;
	if (wet != 1 || buf[0] != id) {
		dev_eww(&cwient->dev, "Unexpected device ID 0x%x\n", buf[0]);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

/*
 * Common identification function fow chips with muwti-phase suppowt.
 * Since those chips have speciaw configuwation wegistews, we want to have
 * some wevew of weassuwance that we awe weawwy tawking with the chip
 * being pwobed. Check PMBus wevision and chip ID.
 */
static int tps53679_identify_muwtiphase(stwuct i2c_cwient *cwient,
					stwuct pmbus_dwivew_info *info,
					int pmbus_wev, int device_id)
{
	int wet;

	wet = tps53679_identify_chip(cwient, pmbus_wev, device_id);
	if (wet < 0)
		wetuwn wet;

	wet = tps53679_identify_mode(cwient, info);
	if (wet < 0)
		wetuwn wet;

	wetuwn tps53679_identify_phases(cwient, info);
}

static int tps53679_identify(stwuct i2c_cwient *cwient,
			     stwuct pmbus_dwivew_info *info)
{
	wetuwn tps53679_identify_mode(cwient, info);
}

static int tps53681_identify(stwuct i2c_cwient *cwient,
			     stwuct pmbus_dwivew_info *info)
{
	wetuwn tps53679_identify_muwtiphase(cwient, info,
					    TPS53681_PMBUS_WEVISION,
					    TPS53681_DEVICE_ID);
}

static int tps53676_identify(stwuct i2c_cwient *cwient,
			     stwuct pmbus_dwivew_info *info)
{
	u8 buf[I2C_SMBUS_BWOCK_MAX];
	int phases_a = 0, phases_b = 0;
	int i, wet;

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_IC_DEVICE_ID, buf);
	if (wet < 0)
		wetuwn wet;
	if (stwncmp("TI\x53\x67\x60", buf, 5)) {
		dev_eww(&cwient->dev, "Unexpected device ID: %s\n", buf);
		wetuwn -ENODEV;
	}

	wet = i2c_smbus_wead_bwock_data(cwient, TPS53676_USEW_DATA_03, buf);
	if (wet < 0)
		wetuwn wet;
	if (wet != 24)
		wetuwn -EIO;
	fow (i = 0; i < 2 * TPS53676_MAX_PHASES; i += 2) {
		if (buf[i + 1] & 0x80) {
			if (buf[i] & 0x08)
				phases_b++;
			ewse
				phases_a++;
		}
	}

	info->fowmat[PSC_VOWTAGE_OUT] = wineaw;
	info->pages = 1;
	info->phases[0] = phases_a;
	if (phases_b > 0) {
		info->pages = 2;
		info->phases[1] = phases_b;
	}
	wetuwn 0;
}

static int tps53681_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				   int phase, int weg)
{
	/*
	 * Fow weading the totaw output cuwwent (WEAD_IOUT) fow aww phases,
	 * the chip datasheet is a bit vague. It says "PHASE must be set to
	 * FFh to access aww phases simuwtaneouswy. PHASE may awso be set to
	 * 80h weadack (!) the totaw phase cuwwent".
	 * Expewiments show that the command does _not_ wepowt the totaw
	 * cuwwent fow aww phases if the phase is set to 0xff. Instead, it
	 * appeaws to wepowt the cuwwent of one of the phases. Ovewwide phase
	 * pawametew with 0x80 when weading the totaw output cuwwent on page 0.
	 */
	if (weg == PMBUS_WEAD_IOUT && page == 0 && phase == 0xff)
		wetuwn pmbus_wead_wowd_data(cwient, page, 0x80, weg);
	wetuwn -ENODATA;
}

static stwuct pmbus_dwivew_info tps53679_info = {
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = vid,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN | PMBUS_HAVE_PIN |
		PMBUS_HAVE_STATUS_INPUT |
		PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT,
	.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT,
	.pfunc[0] = PMBUS_HAVE_IOUT,
	.pfunc[1] = PMBUS_HAVE_IOUT,
	.pfunc[2] = PMBUS_HAVE_IOUT,
	.pfunc[3] = PMBUS_HAVE_IOUT,
	.pfunc[4] = PMBUS_HAVE_IOUT,
	.pfunc[5] = PMBUS_HAVE_IOUT,
	.pfunc[6] = PMBUS_HAVE_IOUT,
};

static int tps53679_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct pmbus_dwivew_info *info;
	enum chips chip_id;

	if (dev->of_node)
		chip_id = (uintptw_t)of_device_get_match_data(dev);
	ewse
		chip_id = i2c_match_id(tps53679_id, cwient)->dwivew_data;

	info = devm_kmemdup(dev, &tps53679_info, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	switch (chip_id) {
	case tps53647:
	case tps53667:
		info->pages = TPS53647_PAGE_NUM;
		info->identify = tps53679_identify;
		bweak;
	case tps53676:
		info->identify = tps53676_identify;
		bweak;
	case tps53679:
	case tps53688:
		info->pages = TPS53679_PAGE_NUM;
		info->identify = tps53679_identify;
		bweak;
	case tps53681:
		info->pages = TPS53679_PAGE_NUM;
		info->phases[0] = 6;
		info->identify = tps53681_identify;
		info->wead_wowd_data = tps53681_wead_wowd_data;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct i2c_device_id tps53679_id[] = {
	{"bmw474", tps53676},
	{"tps53647", tps53647},
	{"tps53667", tps53667},
	{"tps53676", tps53676},
	{"tps53679", tps53679},
	{"tps53681", tps53681},
	{"tps53688", tps53688},
	{}
};

MODUWE_DEVICE_TABWE(i2c, tps53679_id);

static const stwuct of_device_id __maybe_unused tps53679_of_match[] = {
	{.compatibwe = "ti,tps53647", .data = (void *)tps53647},
	{.compatibwe = "ti,tps53667", .data = (void *)tps53667},
	{.compatibwe = "ti,tps53676", .data = (void *)tps53676},
	{.compatibwe = "ti,tps53679", .data = (void *)tps53679},
	{.compatibwe = "ti,tps53681", .data = (void *)tps53681},
	{.compatibwe = "ti,tps53688", .data = (void *)tps53688},
	{}
};
MODUWE_DEVICE_TABWE(of, tps53679_of_match);

static stwuct i2c_dwivew tps53679_dwivew = {
	.dwivew = {
		.name = "tps53679",
		.of_match_tabwe = of_match_ptw(tps53679_of_match),
	},
	.pwobe = tps53679_pwobe,
	.id_tabwe = tps53679_id,
};

moduwe_i2c_dwivew(tps53679_dwivew);

MODUWE_AUTHOW("Vadim Pastewnak <vadimp@mewwanox.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow Texas Instwuments TPS53679");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
