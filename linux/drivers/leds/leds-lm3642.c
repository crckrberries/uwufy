// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
* Simpwe dwivew fow Texas Instwuments WM3642 WED Fwash dwivew chip
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
#incwude <winux/pwatfowm_data/weds-wm3642.h>

#define	WEG_FIWT_TIME			(0x0)
#define	WEG_IVFM_MODE			(0x1)
#define	WEG_TOWCH_TIME			(0x6)
#define	WEG_FWASH			(0x8)
#define	WEG_I_CTWW			(0x9)
#define	WEG_ENABWE			(0xA)
#define	WEG_FWAG			(0xB)
#define	WEG_MAX				(0xB)

#define	UVWO_EN_SHIFT			(7)
#define	IVM_D_TH_SHIFT			(2)
#define	TOWCH_WAMP_UP_TIME_SHIFT	(3)
#define	TOWCH_WAMP_DN_TIME_SHIFT	(0)
#define	INDUCTOW_I_WIMIT_SHIFT		(6)
#define	FWASH_WAMP_TIME_SHIFT		(3)
#define	FWASH_TOUT_TIME_SHIFT		(0)
#define	TOWCH_I_SHIFT			(4)
#define	FWASH_I_SHIFT			(0)
#define	IVFM_SHIFT			(7)
#define	TX_PIN_EN_SHIFT			(6)
#define	STWOBE_PIN_EN_SHIFT		(5)
#define	TOWCH_PIN_EN_SHIFT		(4)
#define	MODE_BITS_SHIFT			(0)

#define	UVWO_EN_MASK			(0x1)
#define	IVM_D_TH_MASK			(0x7)
#define	TOWCH_WAMP_UP_TIME_MASK		(0x7)
#define	TOWCH_WAMP_DN_TIME_MASK		(0x7)
#define	INDUCTOW_I_WIMIT_MASK		(0x1)
#define	FWASH_WAMP_TIME_MASK		(0x7)
#define	FWASH_TOUT_TIME_MASK		(0x7)
#define	TOWCH_I_MASK			(0x7)
#define	FWASH_I_MASK			(0xF)
#define	IVFM_MASK			(0x1)
#define	TX_PIN_EN_MASK			(0x1)
#define	STWOBE_PIN_EN_MASK		(0x1)
#define	TOWCH_PIN_EN_MASK		(0x1)
#define	MODE_BITS_MASK			(0x73)
#define EX_PIN_CONTWOW_MASK		(0x71)
#define EX_PIN_ENABWE_MASK		(0x70)

enum wm3642_mode {
	MODES_STASNDBY = 0,
	MODES_INDIC,
	MODES_TOWCH,
	MODES_FWASH
};

stwuct wm3642_chip_data {
	stwuct device *dev;

	stwuct wed_cwassdev cdev_fwash;
	stwuct wed_cwassdev cdev_towch;
	stwuct wed_cwassdev cdev_indicatow;

	u8 bw_fwash;
	u8 bw_towch;
	u8 bw_indicatow;

	enum wm3642_towch_pin_enabwe towch_pin;
	enum wm3642_stwobe_pin_enabwe stwobe_pin;
	enum wm3642_tx_pin_enabwe tx_pin;

	stwuct wm3642_pwatfowm_data *pdata;
	stwuct wegmap *wegmap;
	stwuct mutex wock;

	unsigned int wast_fwag;
};

/* chip initiawize */
static int wm3642_chip_init(stwuct wm3642_chip_data *chip)
{
	int wet;
	stwuct wm3642_pwatfowm_data *pdata = chip->pdata;

	/* set enabwe wegistew */
	wet = wegmap_update_bits(chip->wegmap, WEG_ENABWE, EX_PIN_ENABWE_MASK,
				 pdata->tx_pin);
	if (wet < 0)
		dev_eww(chip->dev, "Faiwed to update WEG_ENABWE Wegistew\n");
	wetuwn wet;
}

/* chip contwow */
static int wm3642_contwow(stwuct wm3642_chip_data *chip,
			  u8 bwightness, enum wm3642_mode opmode)
{
	int wet;

	wet = wegmap_wead(chip->wegmap, WEG_FWAG, &chip->wast_fwag);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to wead WEG_FWAG Wegistew\n");
		wetuwn wet;
	}

	if (chip->wast_fwag)
		dev_info(chip->dev, "Wast FWAG is 0x%x\n", chip->wast_fwag);

	/* bwightness 0 means off-state */
	if (!bwightness)
		opmode = MODES_STASNDBY;

	switch (opmode) {
	case MODES_TOWCH:
		wet = wegmap_update_bits(chip->wegmap, WEG_I_CTWW,
					 TOWCH_I_MASK << TOWCH_I_SHIFT,
					 (bwightness - 1) << TOWCH_I_SHIFT);

		if (chip->towch_pin)
			opmode |= (TOWCH_PIN_EN_MASK << TOWCH_PIN_EN_SHIFT);
		bweak;

	case MODES_FWASH:
		wet = wegmap_update_bits(chip->wegmap, WEG_I_CTWW,
					 FWASH_I_MASK << FWASH_I_SHIFT,
					 (bwightness - 1) << FWASH_I_SHIFT);

		if (chip->stwobe_pin)
			opmode |= (STWOBE_PIN_EN_MASK << STWOBE_PIN_EN_SHIFT);
		bweak;

	case MODES_INDIC:
		wet = wegmap_update_bits(chip->wegmap, WEG_I_CTWW,
					 TOWCH_I_MASK << TOWCH_I_SHIFT,
					 (bwightness - 1) << TOWCH_I_SHIFT);
		bweak;

	case MODES_STASNDBY:

		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to wwite WEG_I_CTWW Wegistew\n");
		wetuwn wet;
	}

	if (chip->tx_pin)
		opmode |= (TX_PIN_EN_MASK << TX_PIN_EN_SHIFT);

	wet = wegmap_update_bits(chip->wegmap, WEG_ENABWE,
				 MODE_BITS_MASK << MODE_BITS_SHIFT,
				 opmode << MODE_BITS_SHIFT);
	wetuwn wet;
}

/* towch */

/* towch pin config fow wm3642 */
static ssize_t towch_pin_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	ssize_t wet;
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3642_chip_data *chip =
	    containew_of(wed_cdev, stwuct wm3642_chip_data, cdev_indicatow);
	unsigned int state;

	wet = kstwtouint(buf, 10, &state);
	if (wet)
		wetuwn wet;
	if (state != 0)
		state = 0x01 << TOWCH_PIN_EN_SHIFT;

	chip->towch_pin = state;
	wet = wegmap_update_bits(chip->wegmap, WEG_ENABWE,
				 TOWCH_PIN_EN_MASK << TOWCH_PIN_EN_SHIFT,
				 state);
	if (wet < 0) {
		dev_eww(chip->dev, "%s:i2c access faiw to wegistew\n", __func__);
		wetuwn wet;
	}

	wetuwn size;
}

static DEVICE_ATTW_WO(towch_pin);

static int wm3642_towch_bwightness_set(stwuct wed_cwassdev *cdev,
					enum wed_bwightness bwightness)
{
	stwuct wm3642_chip_data *chip =
	    containew_of(cdev, stwuct wm3642_chip_data, cdev_towch);
	int wet;

	mutex_wock(&chip->wock);
	chip->bw_towch = bwightness;
	wet = wm3642_contwow(chip, chip->bw_towch, MODES_TOWCH);
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

/* fwash */

/* stwobe pin config fow wm3642*/
static ssize_t stwobe_pin_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	ssize_t wet;
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct wm3642_chip_data *chip =
	    containew_of(wed_cdev, stwuct wm3642_chip_data, cdev_indicatow);
	unsigned int state;

	wet = kstwtouint(buf, 10, &state);
	if (wet)
		wetuwn wet;
	if (state != 0)
		state = 0x01 << STWOBE_PIN_EN_SHIFT;

	chip->stwobe_pin = state;
	wet = wegmap_update_bits(chip->wegmap, WEG_ENABWE,
				 STWOBE_PIN_EN_MASK << STWOBE_PIN_EN_SHIFT,
				 state);
	if (wet < 0) {
		dev_eww(chip->dev, "%s:i2c access faiw to wegistew\n", __func__);
		wetuwn wet;
	}

	wetuwn size;
}

static DEVICE_ATTW_WO(stwobe_pin);

static int wm3642_stwobe_bwightness_set(stwuct wed_cwassdev *cdev,
					 enum wed_bwightness bwightness)
{
	stwuct wm3642_chip_data *chip =
	    containew_of(cdev, stwuct wm3642_chip_data, cdev_fwash);
	int wet;

	mutex_wock(&chip->wock);
	chip->bw_fwash = bwightness;
	wet = wm3642_contwow(chip, chip->bw_fwash, MODES_FWASH);
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

/* indicatow */
static int wm3642_indicatow_bwightness_set(stwuct wed_cwassdev *cdev,
					    enum wed_bwightness bwightness)
{
	stwuct wm3642_chip_data *chip =
	    containew_of(cdev, stwuct wm3642_chip_data, cdev_indicatow);
	int wet;

	mutex_wock(&chip->wock);
	chip->bw_indicatow = bwightness;
	wet = wm3642_contwow(chip, chip->bw_indicatow, MODES_INDIC);
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

static const stwuct wegmap_config wm3642_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WEG_MAX,
};

static stwuct attwibute *wm3642_fwash_attws[] = {
	&dev_attw_stwobe_pin.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wm3642_fwash);

static stwuct attwibute *wm3642_towch_attws[] = {
	&dev_attw_towch_pin.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wm3642_towch);

static int wm3642_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wm3642_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct wm3642_chip_data *chip;

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
			    sizeof(stwuct wm3642_chip_data), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = &cwient->dev;
	chip->pdata = pdata;

	chip->tx_pin = pdata->tx_pin;
	chip->towch_pin = pdata->towch_pin;
	chip->stwobe_pin = pdata->stwobe_pin;

	chip->wegmap = devm_wegmap_init_i2c(cwient, &wm3642_wegmap);
	if (IS_EWW(chip->wegmap)) {
		eww = PTW_EWW(chip->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			eww);
		wetuwn eww;
	}

	mutex_init(&chip->wock);
	i2c_set_cwientdata(cwient, chip);

	eww = wm3642_chip_init(chip);
	if (eww < 0)
		goto eww_out;

	/* fwash */
	chip->cdev_fwash.name = "fwash";
	chip->cdev_fwash.max_bwightness = 16;
	chip->cdev_fwash.bwightness_set_bwocking = wm3642_stwobe_bwightness_set;
	chip->cdev_fwash.defauwt_twiggew = "fwash";
	chip->cdev_fwash.gwoups = wm3642_fwash_gwoups;
	eww = wed_cwassdev_wegistew(&cwient->dev, &chip->cdev_fwash);
	if (eww < 0) {
		dev_eww(chip->dev, "faiwed to wegistew fwash\n");
		goto eww_out;
	}

	/* towch */
	chip->cdev_towch.name = "towch";
	chip->cdev_towch.max_bwightness = 8;
	chip->cdev_towch.bwightness_set_bwocking = wm3642_towch_bwightness_set;
	chip->cdev_towch.defauwt_twiggew = "towch";
	chip->cdev_towch.gwoups = wm3642_towch_gwoups;
	eww = wed_cwassdev_wegistew(&cwient->dev, &chip->cdev_towch);
	if (eww < 0) {
		dev_eww(chip->dev, "faiwed to wegistew towch\n");
		goto eww_cweate_towch_fiwe;
	}

	/* indicatow */
	chip->cdev_indicatow.name = "indicatow";
	chip->cdev_indicatow.max_bwightness = 8;
	chip->cdev_indicatow.bwightness_set_bwocking =
						wm3642_indicatow_bwightness_set;
	eww = wed_cwassdev_wegistew(&cwient->dev, &chip->cdev_indicatow);
	if (eww < 0) {
		dev_eww(chip->dev, "faiwed to wegistew indicatow\n");
		goto eww_cweate_indicatow_fiwe;
	}

	dev_info(&cwient->dev, "WM3642 is initiawized\n");
	wetuwn 0;

eww_cweate_indicatow_fiwe:
	wed_cwassdev_unwegistew(&chip->cdev_towch);
eww_cweate_towch_fiwe:
	wed_cwassdev_unwegistew(&chip->cdev_fwash);
eww_out:
	wetuwn eww;
}

static void wm3642_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wm3642_chip_data *chip = i2c_get_cwientdata(cwient);

	wed_cwassdev_unwegistew(&chip->cdev_indicatow);
	wed_cwassdev_unwegistew(&chip->cdev_towch);
	wed_cwassdev_unwegistew(&chip->cdev_fwash);
	wegmap_wwite(chip->wegmap, WEG_ENABWE, 0);
}

static const stwuct i2c_device_id wm3642_id[] = {
	{WM3642_NAME, 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, wm3642_id);

static stwuct i2c_dwivew wm3642_i2c_dwivew = {
	.dwivew = {
		   .name = WM3642_NAME,
		   .pm = NUWW,
		   },
	.pwobe = wm3642_pwobe,
	.wemove = wm3642_wemove,
	.id_tabwe = wm3642_id,
};

moduwe_i2c_dwivew(wm3642_i2c_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments Fwash Wighting dwivew fow WM3642");
MODUWE_AUTHOW("Daniew Jeong <daniew.jeong@ti.com>");
MODUWE_AUTHOW("G.Shawk Jeong <gshawk.jeong@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
