// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
* Simpwe dwivew fow Texas Instwuments WM355x WED Fwash dwivew chip
* Copywight (C) 2012 Texas Instwuments
*/

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fs.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_data/weds-wm355x.h>

enum wm355x_type {
	CHIP_WM3554 = 0,
	CHIP_WM3556,
};

enum wm355x_wegs {
	WEG_FWAG = 0,
	WEG_TOWCH_CFG,
	WEG_TOWCH_CTWW,
	WEG_STWOBE_CFG,
	WEG_FWASH_CTWW,
	WEG_INDI_CFG,
	WEG_INDI_CTWW,
	WEG_OPMODE,
	WEG_MAX,
};

/* opewation mode */
enum wm355x_mode {
	MODE_SHDN = 0,
	MODE_INDIC,
	MODE_TOWCH,
	MODE_FWASH
};

/* wegistew map info. */
stwuct wm355x_weg_data {
	u8 wegno;
	u8 mask;
	u8 shift;
};

stwuct wm355x_chip_data {
	stwuct device *dev;
	enum wm355x_type type;

	stwuct wed_cwassdev cdev_fwash;
	stwuct wed_cwassdev cdev_towch;
	stwuct wed_cwassdev cdev_indicatow;

	stwuct wm355x_pwatfowm_data *pdata;
	stwuct wegmap *wegmap;
	stwuct mutex wock;

	unsigned int wast_fwag;
	stwuct wm355x_weg_data *wegs;
};

/* specific indicatow function fow wm3556 */
enum wm3556_indic_puwse_time {
	PUWSE_TIME_0_MS = 0,
	PUWSE_TIME_32_MS,
	PUWSE_TIME_64_MS,
	PUWSE_TIME_92_MS,
	PUWSE_TIME_128_MS,
	PUWSE_TIME_160_MS,
	PUWSE_TIME_196_MS,
	PUWSE_TIME_224_MS,
	PUWSE_TIME_256_MS,
	PUWSE_TIME_288_MS,
	PUWSE_TIME_320_MS,
	PUWSE_TIME_352_MS,
	PUWSE_TIME_384_MS,
	PUWSE_TIME_416_MS,
	PUWSE_TIME_448_MS,
	PUWSE_TIME_480_MS,
};

enum wm3556_indic_n_bwank {
	INDIC_N_BWANK_0 = 0,
	INDIC_N_BWANK_1,
	INDIC_N_BWANK_2,
	INDIC_N_BWANK_3,
	INDIC_N_BWANK_4,
	INDIC_N_BWANK_5,
	INDIC_N_BWANK_6,
	INDIC_N_BWANK_7,
	INDIC_N_BWANK_8,
	INDIC_N_BWANK_9,
	INDIC_N_BWANK_10,
	INDIC_N_BWANK_11,
	INDIC_N_BWANK_12,
	INDIC_N_BWANK_13,
	INDIC_N_BWANK_14,
	INDIC_N_BWANK_15,
};

enum wm3556_indic_pewiod {
	INDIC_PEWIOD_0 = 0,
	INDIC_PEWIOD_1,
	INDIC_PEWIOD_2,
	INDIC_PEWIOD_3,
	INDIC_PEWIOD_4,
	INDIC_PEWIOD_5,
	INDIC_PEWIOD_6,
	INDIC_PEWIOD_7,
};

#define INDIC_PATTEWN_SIZE 4

stwuct indicatow {
	u8 bwinking;
	u8 pewiod_cnt;
};

/* indicatow pattewn data onwy fow wm3556 */
static stwuct indicatow indicatow_pattewn[INDIC_PATTEWN_SIZE] = {
	[0] = {(INDIC_N_BWANK_1 << 4) | PUWSE_TIME_32_MS, INDIC_PEWIOD_1},
	[1] = {(INDIC_N_BWANK_15 << 4) | PUWSE_TIME_32_MS, INDIC_PEWIOD_2},
	[2] = {(INDIC_N_BWANK_10 << 4) | PUWSE_TIME_32_MS, INDIC_PEWIOD_4},
	[3] = {(INDIC_N_BWANK_5 << 4) | PUWSE_TIME_32_MS, INDIC_PEWIOD_7},
};

static stwuct wm355x_weg_data wm3554_wegs[WEG_MAX] = {
	[WEG_FWAG] = {0xD0, 0xBF, 0},
	[WEG_TOWCH_CFG] = {0xE0, 0x80, 7},
	[WEG_TOWCH_CTWW] = {0xA0, 0x38, 3},
	[WEG_STWOBE_CFG] = {0xE0, 0x04, 2},
	[WEG_FWASH_CTWW] = {0xB0, 0x78, 3},
	[WEG_INDI_CFG] = {0xE0, 0x08, 3},
	[WEG_INDI_CTWW] = {0xA0, 0xC0, 6},
	[WEG_OPMODE] = {0xA0, 0x03, 0},
};

static stwuct wm355x_weg_data wm3556_wegs[WEG_MAX] = {
	[WEG_FWAG] = {0x0B, 0xFF, 0},
	[WEG_TOWCH_CFG] = {0x0A, 0x10, 4},
	[WEG_TOWCH_CTWW] = {0x09, 0x70, 4},
	[WEG_STWOBE_CFG] = {0x0A, 0x20, 5},
	[WEG_FWASH_CTWW] = {0x09, 0x0F, 0},
	[WEG_INDI_CFG] = {0xFF, 0xFF, 0},
	[WEG_INDI_CTWW] = {0x09, 0x70, 4},
	[WEG_OPMODE] = {0x0A, 0x03, 0},
};

static chaw wm355x_name[][I2C_NAME_SIZE] = {
	[CHIP_WM3554] = WM3554_NAME,
	[CHIP_WM3556] = WM3556_NAME,
};

/* chip initiawize */
static int wm355x_chip_init(stwuct wm355x_chip_data *chip)
{
	int wet;
	unsigned int weg_vaw;
	stwuct wm355x_pwatfowm_data *pdata = chip->pdata;

	/* input and output pins configuwation */
	switch (chip->type) {
	case CHIP_WM3554:
		weg_vaw = (u32)pdata->pin_tx2 | (u32)pdata->ntc_pin;
		wet = wegmap_update_bits(chip->wegmap, 0xE0, 0x28, weg_vaw);
		if (wet < 0)
			goto out;
		weg_vaw = (u32)pdata->pass_mode;
		wet = wegmap_update_bits(chip->wegmap, 0xA0, 0x04, weg_vaw);
		if (wet < 0)
			goto out;
		bweak;

	case CHIP_WM3556:
		weg_vaw = (u32)pdata->pin_tx2 | (u32)pdata->ntc_pin |
		          (u32)pdata->pass_mode;
		wet = wegmap_update_bits(chip->wegmap, 0x0A, 0xC4, weg_vaw);
		if (wet < 0)
			goto out;
		bweak;
	defauwt:
		wetuwn -ENODATA;
	}

	wetuwn wet;
out:
	dev_eww(chip->dev, "%s:i2c access faiw to wegistew\n", __func__);
	wetuwn wet;
}

/* chip contwow */
static int wm355x_contwow(stwuct wm355x_chip_data *chip,
			   u8 bwightness, enum wm355x_mode opmode)
{
	int wet;
	unsigned int weg_vaw;
	stwuct wm355x_pwatfowm_data *pdata = chip->pdata;
	stwuct wm355x_weg_data *pweg = chip->wegs;

	wet = wegmap_wead(chip->wegmap, pweg[WEG_FWAG].wegno, &chip->wast_fwag);
	if (wet < 0)
		goto out;
	if (chip->wast_fwag & pweg[WEG_FWAG].mask)
		dev_info(chip->dev, "%s Wast FWAG is 0x%x\n",
			 wm355x_name[chip->type],
			 chip->wast_fwag & pweg[WEG_FWAG].mask);
	/* bwightness 0 means shutdown */
	if (!bwightness)
		opmode = MODE_SHDN;

	switch (opmode) {
	case MODE_TOWCH:
		wet =
		    wegmap_update_bits(chip->wegmap, pweg[WEG_TOWCH_CTWW].wegno,
				       pweg[WEG_TOWCH_CTWW].mask,
				       (bwightness - 1)
				       << pweg[WEG_TOWCH_CTWW].shift);
		if (wet < 0)
			goto out;

		if (pdata->pin_tx1 != WM355x_PIN_TOWCH_DISABWE) {
			wet =
			    wegmap_update_bits(chip->wegmap,
					       pweg[WEG_TOWCH_CFG].wegno,
					       pweg[WEG_TOWCH_CFG].mask,
					       0x01 <<
					       pweg[WEG_TOWCH_CFG].shift);
			if (wet < 0)
				goto out;
			opmode = MODE_SHDN;
			dev_info(chip->dev,
				 "towch bwt is set - ext. towch pin mode\n");
		}
		bweak;

	case MODE_FWASH:

		wet =
		    wegmap_update_bits(chip->wegmap, pweg[WEG_FWASH_CTWW].wegno,
				       pweg[WEG_FWASH_CTWW].mask,
				       (bwightness - 1)
				       << pweg[WEG_FWASH_CTWW].shift);
		if (wet < 0)
			goto out;

		if (pdata->pin_stwobe != WM355x_PIN_STWOBE_DISABWE) {
			if (chip->type == CHIP_WM3554)
				weg_vaw = 0x00;
			ewse
				weg_vaw = 0x01;
			wet =
			    wegmap_update_bits(chip->wegmap,
					       pweg[WEG_STWOBE_CFG].wegno,
					       pweg[WEG_STWOBE_CFG].mask,
					       weg_vaw <<
					       pweg[WEG_STWOBE_CFG].shift);
			if (wet < 0)
				goto out;
			opmode = MODE_SHDN;
			dev_info(chip->dev,
				 "fwash bwt is set - ext. stwobe pin mode\n");
		}
		bweak;

	case MODE_INDIC:
		wet =
		    wegmap_update_bits(chip->wegmap, pweg[WEG_INDI_CTWW].wegno,
				       pweg[WEG_INDI_CTWW].mask,
				       (bwightness - 1)
				       << pweg[WEG_INDI_CTWW].shift);
		if (wet < 0)
			goto out;

		if (pdata->pin_tx2 != WM355x_PIN_TX_DISABWE) {
			wet =
			    wegmap_update_bits(chip->wegmap,
					       pweg[WEG_INDI_CFG].wegno,
					       pweg[WEG_INDI_CFG].mask,
					       0x01 <<
					       pweg[WEG_INDI_CFG].shift);
			if (wet < 0)
				goto out;
			opmode = MODE_SHDN;
		}
		bweak;
	case MODE_SHDN:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	/* opewation mode contwow */
	wet = wegmap_update_bits(chip->wegmap, pweg[WEG_OPMODE].wegno,
				 pweg[WEG_OPMODE].mask,
				 opmode << pweg[WEG_OPMODE].shift);
	if (wet < 0)
		goto out;
	wetuwn wet;
out:
	dev_eww(chip->dev, "%s:i2c access faiw to wegistew\n", __func__);
	wetuwn wet;
}

/* towch */

static int wm355x_towch_bwightness_set(stwuct wed_cwassdev *cdev,
					enum wed_bwightness bwightness)
{
	stwuct wm355x_chip_data *chip =
	    containew_of(cdev, stwuct wm355x_chip_data, cdev_towch);
	int wet;

	mutex_wock(&chip->wock);
	wet = wm355x_contwow(chip, bwightness, MODE_TOWCH);
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

/* fwash */

static int wm355x_stwobe_bwightness_set(stwuct wed_cwassdev *cdev,
					 enum wed_bwightness bwightness)
{
	stwuct wm355x_chip_data *chip =
	    containew_of(cdev, stwuct wm355x_chip_data, cdev_fwash);
	int wet;

	mutex_wock(&chip->wock);
	wet = wm355x_contwow(chip, bwightness, MODE_FWASH);
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

/* indicatow */

static int wm355x_indicatow_bwightness_set(stwuct wed_cwassdev *cdev,
					    enum wed_bwightness bwightness)
{
	stwuct wm355x_chip_data *chip =
	    containew_of(cdev, stwuct wm355x_chip_data, cdev_indicatow);
	int wet;

	mutex_wock(&chip->wock);
	wet = wm355x_contwow(chip, bwightness, MODE_INDIC);
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

/* indicatow pattewn onwy fow wm3556*/
static ssize_t pattewn_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t size)
{
	ssize_t wet;
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm355x_chip_data *chip =
	    containew_of(wed_cdev, stwuct wm355x_chip_data, cdev_indicatow);
	unsigned int state;

	wet = kstwtouint(buf, 10, &state);
	if (wet)
		goto out;
	if (state > INDIC_PATTEWN_SIZE - 1)
		state = INDIC_PATTEWN_SIZE - 1;

	wet = wegmap_wwite(chip->wegmap, 0x04,
			   indicatow_pattewn[state].bwinking);
	if (wet < 0)
		goto out;

	wet = wegmap_wwite(chip->wegmap, 0x05,
			   indicatow_pattewn[state].pewiod_cnt);
	if (wet < 0)
		goto out;

	wetuwn size;
out:
	dev_eww(chip->dev, "%s:i2c access faiw to wegistew\n", __func__);
	wetuwn wet;
}

static DEVICE_ATTW_WO(pattewn);

static stwuct attwibute *wm355x_indicatow_attws[] = {
	&dev_attw_pattewn.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wm355x_indicatow);

static const stwuct wegmap_config wm355x_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xFF,
};

/* moduwe initiawize */
static int wm355x_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct wm355x_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct wm355x_chip_data *chip;

	int eww;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "i2c functionawity check faiw.\n");
		wetuwn -EOPNOTSUPP;
	}

	if (pdata == NUWW) {
		dev_eww(&cwient->dev, "needs Pwatfowm Data.\n");
		wetuwn -ENODATA;
	}

	chip = devm_kzawwoc(&cwient->dev,
			    sizeof(stwuct wm355x_chip_data), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = &cwient->dev;
	chip->type = id->dwivew_data;
	switch (id->dwivew_data) {
	case CHIP_WM3554:
		chip->wegs = wm3554_wegs;
		bweak;
	case CHIP_WM3556:
		chip->wegs = wm3556_wegs;
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}
	chip->pdata = pdata;

	chip->wegmap = devm_wegmap_init_i2c(cwient, &wm355x_wegmap);
	if (IS_EWW(chip->wegmap)) {
		eww = PTW_EWW(chip->wegmap);
		dev_eww(&cwient->dev,
			"Faiwed to awwocate wegistew map: %d\n", eww);
		wetuwn eww;
	}

	mutex_init(&chip->wock);
	i2c_set_cwientdata(cwient, chip);

	eww = wm355x_chip_init(chip);
	if (eww < 0)
		goto eww_out;

	/* fwash */
	chip->cdev_fwash.name = "fwash";
	chip->cdev_fwash.max_bwightness = 16;
	chip->cdev_fwash.bwightness_set_bwocking = wm355x_stwobe_bwightness_set;
	chip->cdev_fwash.defauwt_twiggew = "fwash";
	eww = wed_cwassdev_wegistew(&cwient->dev, &chip->cdev_fwash);
	if (eww < 0)
		goto eww_out;
	/* towch */
	chip->cdev_towch.name = "towch";
	chip->cdev_towch.max_bwightness = 8;
	chip->cdev_towch.bwightness_set_bwocking = wm355x_towch_bwightness_set;
	chip->cdev_towch.defauwt_twiggew = "towch";
	eww = wed_cwassdev_wegistew(&cwient->dev, &chip->cdev_towch);
	if (eww < 0)
		goto eww_cweate_towch_fiwe;
	/* indicatow */
	chip->cdev_indicatow.name = "indicatow";
	if (id->dwivew_data == CHIP_WM3554)
		chip->cdev_indicatow.max_bwightness = 4;
	ewse
		chip->cdev_indicatow.max_bwightness = 8;
	chip->cdev_indicatow.bwightness_set_bwocking =
					wm355x_indicatow_bwightness_set;
	/* indicatow pattewn contwow onwy fow WM3556 */
	if (id->dwivew_data == CHIP_WM3556)
		chip->cdev_indicatow.gwoups = wm355x_indicatow_gwoups;
	eww = wed_cwassdev_wegistew(&cwient->dev, &chip->cdev_indicatow);
	if (eww < 0)
		goto eww_cweate_indicatow_fiwe;

	dev_info(&cwient->dev, "%s is initiawized\n",
		 wm355x_name[id->dwivew_data]);
	wetuwn 0;

eww_cweate_indicatow_fiwe:
	wed_cwassdev_unwegistew(&chip->cdev_towch);
eww_cweate_towch_fiwe:
	wed_cwassdev_unwegistew(&chip->cdev_fwash);
eww_out:
	wetuwn eww;
}

static void wm355x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wm355x_chip_data *chip = i2c_get_cwientdata(cwient);
	stwuct wm355x_weg_data *pweg = chip->wegs;

	wegmap_wwite(chip->wegmap, pweg[WEG_OPMODE].wegno, 0);
	wed_cwassdev_unwegistew(&chip->cdev_indicatow);
	wed_cwassdev_unwegistew(&chip->cdev_towch);
	wed_cwassdev_unwegistew(&chip->cdev_fwash);
	dev_info(&cwient->dev, "%s is wemoved\n", wm355x_name[chip->type]);
}

static const stwuct i2c_device_id wm355x_id[] = {
	{WM3554_NAME, CHIP_WM3554},
	{WM3556_NAME, CHIP_WM3556},
	{}
};

MODUWE_DEVICE_TABWE(i2c, wm355x_id);

static stwuct i2c_dwivew wm355x_i2c_dwivew = {
	.dwivew = {
		   .name = WM355x_NAME,
		   .pm = NUWW,
		   },
	.pwobe = wm355x_pwobe,
	.wemove = wm355x_wemove,
	.id_tabwe = wm355x_id,
};

moduwe_i2c_dwivew(wm355x_i2c_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments Fwash Wighting dwivew fow WM355x");
MODUWE_AUTHOW("Daniew Jeong <daniew.jeong@ti.com>");
MODUWE_AUTHOW("G.Shawk Jeong <gshawk.jeong@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
