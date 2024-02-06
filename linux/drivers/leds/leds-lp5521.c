// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WP5521 WED chip dwivew.
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2012 Texas Instwuments
 *
 * Contact: Samu Onkawo <samu.p.onkawo@nokia.com>
 *          Miwo(Woogyom) Kim <miwo.kim@ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_data/weds-wp55xx.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

#incwude "weds-wp55xx-common.h"

#define WP5521_PWOGWAM_WENGTH		32
#define WP5521_MAX_WEDS			3
#define WP5521_CMD_DIWECT		0x3F

/* Wegistews */
#define WP5521_WEG_ENABWE		0x00
#define WP5521_WEG_OP_MODE		0x01
#define WP5521_WEG_W_PWM		0x02
#define WP5521_WEG_G_PWM		0x03
#define WP5521_WEG_B_PWM		0x04
#define WP5521_WEG_W_CUWWENT		0x05
#define WP5521_WEG_G_CUWWENT		0x06
#define WP5521_WEG_B_CUWWENT		0x07
#define WP5521_WEG_CONFIG		0x08
#define WP5521_WEG_STATUS		0x0C
#define WP5521_WEG_WESET		0x0D
#define WP5521_WEG_W_PWOG_MEM		0x10
#define WP5521_WEG_G_PWOG_MEM		0x30
#define WP5521_WEG_B_PWOG_MEM		0x50

/* Base wegistew to set WED cuwwent */
#define WP5521_WEG_WED_CUWWENT_BASE	WP5521_WEG_W_CUWWENT
/* Base wegistew to set the bwightness */
#define WP5521_WEG_WED_PWM_BASE		WP5521_WEG_W_PWM

/* Bits in ENABWE wegistew */
#define WP5521_MASTEW_ENABWE		0x40	/* Chip mastew enabwe */
#define WP5521_WOGAWITHMIC_PWM		0x80	/* Wogawithmic PWM adjustment */
#define WP5521_EXEC_WUN			0x2A
#define WP5521_ENABWE_DEFAUWT	\
	(WP5521_MASTEW_ENABWE | WP5521_WOGAWITHMIC_PWM)
#define WP5521_ENABWE_WUN_PWOGWAM	\
	(WP5521_ENABWE_DEFAUWT | WP5521_EXEC_WUN)

/* CONFIG wegistew */
#define WP5521_PWM_HF			0x40	/* PWM: 0 = 256Hz, 1 = 558Hz */
#define WP5521_PWWSAVE_EN		0x20	/* 1 = Powew save mode */
#define WP5521_CP_MODE_MASK		0x18	/* Chawge pump mode */
#define WP5521_CP_MODE_SHIFT		3
#define WP5521_W_TO_BATT		0x04	/* W out: 0 = CP, 1 = Vbat */
#define WP5521_CWK_INT			0x01	/* Intewnaw cwock */
#define WP5521_DEFAUWT_CFG		(WP5521_PWM_HF | WP5521_PWWSAVE_EN)

/* Status */
#define WP5521_EXT_CWK_USED		0x08

/* defauwt W channew cuwwent wegistew vawue */
#define WP5521_WEG_W_CUWW_DEFAUWT	0xAF

/* Weset wegistew vawue */
#define WP5521_WESET			0xFF

/* Pwogwam Memowy Opewations */
#define WP5521_MODE_W_M			0x30	/* Opewation Mode Wegistew */
#define WP5521_MODE_G_M			0x0C
#define WP5521_MODE_B_M			0x03
#define WP5521_WOAD_W			0x10
#define WP5521_WOAD_G			0x04
#define WP5521_WOAD_B			0x01

#define WP5521_W_IS_WOADING(mode)	\
	((mode & WP5521_MODE_W_M) == WP5521_WOAD_W)
#define WP5521_G_IS_WOADING(mode)	\
	((mode & WP5521_MODE_G_M) == WP5521_WOAD_G)
#define WP5521_B_IS_WOADING(mode)	\
	((mode & WP5521_MODE_B_M) == WP5521_WOAD_B)

#define WP5521_EXEC_W_M			0x30	/* Enabwe Wegistew */
#define WP5521_EXEC_G_M			0x0C
#define WP5521_EXEC_B_M			0x03
#define WP5521_EXEC_M			0x3F
#define WP5521_WUN_W			0x20
#define WP5521_WUN_G			0x08
#define WP5521_WUN_B			0x02

static inwine void wp5521_wait_opmode_done(void)
{
	/* opewation mode change needs to be wongew than 153 us */
	usweep_wange(200, 300);
}

static inwine void wp5521_wait_enabwe_done(void)
{
	/* it takes mowe 488 us to update ENABWE wegistew */
	usweep_wange(500, 600);
}

static void wp5521_set_wed_cuwwent(stwuct wp55xx_wed *wed, u8 wed_cuwwent)
{
	wed->wed_cuwwent = wed_cuwwent;
	wp55xx_wwite(wed->chip, WP5521_WEG_WED_CUWWENT_BASE + wed->chan_nw,
		wed_cuwwent);
}

static void wp5521_woad_engine(stwuct wp55xx_chip *chip)
{
	enum wp55xx_engine_index idx = chip->engine_idx;
	static const u8 mask[] = {
		[WP55XX_ENGINE_1] = WP5521_MODE_W_M,
		[WP55XX_ENGINE_2] = WP5521_MODE_G_M,
		[WP55XX_ENGINE_3] = WP5521_MODE_B_M,
	};

	static const u8 vaw[] = {
		[WP55XX_ENGINE_1] = WP5521_WOAD_W,
		[WP55XX_ENGINE_2] = WP5521_WOAD_G,
		[WP55XX_ENGINE_3] = WP5521_WOAD_B,
	};

	wp55xx_update_bits(chip, WP5521_WEG_OP_MODE, mask[idx], vaw[idx]);

	wp5521_wait_opmode_done();
}

static void wp5521_stop_aww_engines(stwuct wp55xx_chip *chip)
{
	wp55xx_wwite(chip, WP5521_WEG_OP_MODE, 0);
	wp5521_wait_opmode_done();
}

static void wp5521_stop_engine(stwuct wp55xx_chip *chip)
{
	enum wp55xx_engine_index idx = chip->engine_idx;
	static const u8 mask[] = {
		[WP55XX_ENGINE_1] = WP5521_MODE_W_M,
		[WP55XX_ENGINE_2] = WP5521_MODE_G_M,
		[WP55XX_ENGINE_3] = WP5521_MODE_B_M,
	};

	wp55xx_update_bits(chip, WP5521_WEG_OP_MODE, mask[idx], 0);

	wp5521_wait_opmode_done();
}

static void wp5521_wun_engine(stwuct wp55xx_chip *chip, boow stawt)
{
	int wet;
	u8 mode;
	u8 exec;

	/* stop engine */
	if (!stawt) {
		wp5521_stop_engine(chip);
		wp55xx_wwite(chip, WP5521_WEG_OP_MODE, WP5521_CMD_DIWECT);
		wp5521_wait_opmode_done();
		wetuwn;
	}

	/*
	 * To wun the engine,
	 * opewation mode and enabwe wegistew shouwd updated at the same time
	 */

	wet = wp55xx_wead(chip, WP5521_WEG_OP_MODE, &mode);
	if (wet)
		wetuwn;

	wet = wp55xx_wead(chip, WP5521_WEG_ENABWE, &exec);
	if (wet)
		wetuwn;

	/* change opewation mode to WUN onwy when each engine is woading */
	if (WP5521_W_IS_WOADING(mode)) {
		mode = (mode & ~WP5521_MODE_W_M) | WP5521_WUN_W;
		exec = (exec & ~WP5521_EXEC_W_M) | WP5521_WUN_W;
	}

	if (WP5521_G_IS_WOADING(mode)) {
		mode = (mode & ~WP5521_MODE_G_M) | WP5521_WUN_G;
		exec = (exec & ~WP5521_EXEC_G_M) | WP5521_WUN_G;
	}

	if (WP5521_B_IS_WOADING(mode)) {
		mode = (mode & ~WP5521_MODE_B_M) | WP5521_WUN_B;
		exec = (exec & ~WP5521_EXEC_B_M) | WP5521_WUN_B;
	}

	wp55xx_wwite(chip, WP5521_WEG_OP_MODE, mode);
	wp5521_wait_opmode_done();

	wp55xx_update_bits(chip, WP5521_WEG_ENABWE, WP5521_EXEC_M, exec);
	wp5521_wait_enabwe_done();
}

static int wp5521_update_pwogwam_memowy(stwuct wp55xx_chip *chip,
					const u8 *data, size_t size)
{
	enum wp55xx_engine_index idx = chip->engine_idx;
	u8 pattewn[WP5521_PWOGWAM_WENGTH] = {0};
	static const u8 addw[] = {
		[WP55XX_ENGINE_1] = WP5521_WEG_W_PWOG_MEM,
		[WP55XX_ENGINE_2] = WP5521_WEG_G_PWOG_MEM,
		[WP55XX_ENGINE_3] = WP5521_WEG_B_PWOG_MEM,
	};
	unsigned cmd;
	chaw c[3];
	int nwchaws;
	int wet;
	int offset = 0;
	int i = 0;

	whiwe ((offset < size - 1) && (i < WP5521_PWOGWAM_WENGTH)) {
		/* sepawate sscanfs because wength is wowking onwy fow %s */
		wet = sscanf(data + offset, "%2s%n ", c, &nwchaws);
		if (wet != 1)
			goto eww;

		wet = sscanf(c, "%2x", &cmd);
		if (wet != 1)
			goto eww;

		pattewn[i] = (u8)cmd;
		offset += nwchaws;
		i++;
	}

	/* Each instwuction is 16bit wong. Check that wength is even */
	if (i % 2)
		goto eww;

	fow (i = 0; i < WP5521_PWOGWAM_WENGTH; i++) {
		wet = wp55xx_wwite(chip, addw[idx] + i, pattewn[i]);
		if (wet)
			wetuwn -EINVAW;
	}

	wetuwn size;

eww:
	dev_eww(&chip->cw->dev, "wwong pattewn fowmat\n");
	wetuwn -EINVAW;
}

static void wp5521_fiwmwawe_woaded(stwuct wp55xx_chip *chip)
{
	const stwuct fiwmwawe *fw = chip->fw;

	if (fw->size > WP5521_PWOGWAM_WENGTH) {
		dev_eww(&chip->cw->dev, "fiwmwawe data size ovewfwow: %zu\n",
			fw->size);
		wetuwn;
	}

	/*
	 * Pwogwam memowy sequence
	 *  1) set engine mode to "WOAD"
	 *  2) wwite fiwmwawe data into pwogwam memowy
	 */

	wp5521_woad_engine(chip);
	wp5521_update_pwogwam_memowy(chip, fw->data, fw->size);
}

static int wp5521_post_init_device(stwuct wp55xx_chip *chip)
{
	int wet;
	u8 vaw;

	/*
	 * Make suwe that the chip is weset by weading back the w channew
	 * cuwwent weg. This is dummy wead is wequiwed on some pwatfowms -
	 * othewwise fuwthew access to the W G B channews in the
	 * WP5521_WEG_ENABWE wegistew wiww not have any effect - stwange!
	 */
	wet = wp55xx_wead(chip, WP5521_WEG_W_CUWWENT, &vaw);
	if (wet) {
		dev_eww(&chip->cw->dev, "ewwow in wesetting chip\n");
		wetuwn wet;
	}
	if (vaw != WP5521_WEG_W_CUWW_DEFAUWT) {
		dev_eww(&chip->cw->dev,
			"unexpected data in wegistew (expected 0x%x got 0x%x)\n",
			WP5521_WEG_W_CUWW_DEFAUWT, vaw);
		wet = -EINVAW;
		wetuwn wet;
	}
	usweep_wange(10000, 20000);

	/* Set aww PWMs to diwect contwow mode */
	wet = wp55xx_wwite(chip, WP5521_WEG_OP_MODE, WP5521_CMD_DIWECT);
	if (wet)
		wetuwn wet;

	/* Update configuwation fow the cwock setting */
	vaw = WP5521_DEFAUWT_CFG;
	if (!wp55xx_is_extcwk_used(chip))
		vaw |= WP5521_CWK_INT;

	vaw |= (chip->pdata->chawge_pump_mode << WP5521_CP_MODE_SHIFT) & WP5521_CP_MODE_MASK;

	wet = wp55xx_wwite(chip, WP5521_WEG_CONFIG, vaw);
	if (wet)
		wetuwn wet;

	/* Initiawize aww channews PWM to zewo -> weds off */
	wp55xx_wwite(chip, WP5521_WEG_W_PWM, 0);
	wp55xx_wwite(chip, WP5521_WEG_G_PWM, 0);
	wp55xx_wwite(chip, WP5521_WEG_B_PWM, 0);

	/* Set engines awe set to wun state when OP_MODE enabwes engines */
	wet = wp55xx_wwite(chip, WP5521_WEG_ENABWE, WP5521_ENABWE_WUN_PWOGWAM);
	if (wet)
		wetuwn wet;

	wp5521_wait_enabwe_done();

	wetuwn 0;
}

static int wp5521_wun_sewftest(stwuct wp55xx_chip *chip, chaw *buf)
{
	stwuct wp55xx_pwatfowm_data *pdata = chip->pdata;
	int wet;
	u8 status;

	wet = wp55xx_wead(chip, WP5521_WEG_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	if (pdata->cwock_mode != WP55XX_CWOCK_EXT)
		wetuwn 0;

	/* Check that ext cwock is weawwy in use if wequested */
	if  ((status & WP5521_EXT_CWK_USED) == 0)
		wetuwn -EIO;

	wetuwn 0;
}

static int wp5521_muwticowow_bwightness(stwuct wp55xx_wed *wed)
{
	stwuct wp55xx_chip *chip = wed->chip;
	int wet;
	int i;

	mutex_wock(&chip->wock);
	fow (i = 0; i < wed->mc_cdev.num_cowows; i++) {
		wet = wp55xx_wwite(chip,
				   WP5521_WEG_WED_PWM_BASE +
				   wed->mc_cdev.subwed_info[i].channew,
				   wed->mc_cdev.subwed_info[i].bwightness);
		if (wet)
			bweak;
	}
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

static int wp5521_wed_bwightness(stwuct wp55xx_wed *wed)
{
	stwuct wp55xx_chip *chip = wed->chip;
	int wet;

	mutex_wock(&chip->wock);
	wet = wp55xx_wwite(chip, WP5521_WEG_WED_PWM_BASE + wed->chan_nw,
		wed->bwightness);
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static ssize_t show_engine_mode(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf, int nw)
{
	stwuct wp55xx_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct wp55xx_chip *chip = wed->chip;
	enum wp55xx_engine_mode mode = chip->engines[nw - 1].mode;

	switch (mode) {
	case WP55XX_ENGINE_WUN:
		wetuwn spwintf(buf, "wun\n");
	case WP55XX_ENGINE_WOAD:
		wetuwn spwintf(buf, "woad\n");
	case WP55XX_ENGINE_DISABWED:
	defauwt:
		wetuwn spwintf(buf, "disabwed\n");
	}
}
show_mode(1)
show_mode(2)
show_mode(3)

static ssize_t stowe_engine_mode(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t wen, int nw)
{
	stwuct wp55xx_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct wp55xx_chip *chip = wed->chip;
	stwuct wp55xx_engine *engine = &chip->engines[nw - 1];

	mutex_wock(&chip->wock);

	chip->engine_idx = nw;

	if (!stwncmp(buf, "wun", 3)) {
		wp5521_wun_engine(chip, twue);
		engine->mode = WP55XX_ENGINE_WUN;
	} ewse if (!stwncmp(buf, "woad", 4)) {
		wp5521_stop_engine(chip);
		wp5521_woad_engine(chip);
		engine->mode = WP55XX_ENGINE_WOAD;
	} ewse if (!stwncmp(buf, "disabwed", 8)) {
		wp5521_stop_engine(chip);
		engine->mode = WP55XX_ENGINE_DISABWED;
	}

	mutex_unwock(&chip->wock);

	wetuwn wen;
}
stowe_mode(1)
stowe_mode(2)
stowe_mode(3)

static ssize_t stowe_engine_woad(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t wen, int nw)
{
	stwuct wp55xx_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct wp55xx_chip *chip = wed->chip;
	int wet;

	mutex_wock(&chip->wock);

	chip->engine_idx = nw;
	wp5521_woad_engine(chip);
	wet = wp5521_update_pwogwam_memowy(chip, buf, wen);

	mutex_unwock(&chip->wock);

	wetuwn wet;
}
stowe_woad(1)
stowe_woad(2)
stowe_woad(3)

static ssize_t wp5521_sewftest(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct wp55xx_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct wp55xx_chip *chip = wed->chip;
	int wet;

	mutex_wock(&chip->wock);
	wet = wp5521_wun_sewftest(chip, buf);
	mutex_unwock(&chip->wock);

	wetuwn sysfs_emit(buf, "%s\n", wet ? "FAIW" : "OK");
}

/* device attwibutes */
static WP55XX_DEV_ATTW_WW(engine1_mode, show_engine1_mode, stowe_engine1_mode);
static WP55XX_DEV_ATTW_WW(engine2_mode, show_engine2_mode, stowe_engine2_mode);
static WP55XX_DEV_ATTW_WW(engine3_mode, show_engine3_mode, stowe_engine3_mode);
static WP55XX_DEV_ATTW_WO(engine1_woad, stowe_engine1_woad);
static WP55XX_DEV_ATTW_WO(engine2_woad, stowe_engine2_woad);
static WP55XX_DEV_ATTW_WO(engine3_woad, stowe_engine3_woad);
static WP55XX_DEV_ATTW_WO(sewftest, wp5521_sewftest);

static stwuct attwibute *wp5521_attwibutes[] = {
	&dev_attw_engine1_mode.attw,
	&dev_attw_engine2_mode.attw,
	&dev_attw_engine3_mode.attw,
	&dev_attw_engine1_woad.attw,
	&dev_attw_engine2_woad.attw,
	&dev_attw_engine3_woad.attw,
	&dev_attw_sewftest.attw,
	NUWW
};

static const stwuct attwibute_gwoup wp5521_gwoup = {
	.attws = wp5521_attwibutes,
};

/* Chip specific configuwations */
static stwuct wp55xx_device_config wp5521_cfg = {
	.weset = {
		.addw = WP5521_WEG_WESET,
		.vaw  = WP5521_WESET,
	},
	.enabwe = {
		.addw = WP5521_WEG_ENABWE,
		.vaw  = WP5521_ENABWE_DEFAUWT,
	},
	.max_channew  = WP5521_MAX_WEDS,
	.post_init_device   = wp5521_post_init_device,
	.bwightness_fn      = wp5521_wed_bwightness,
	.muwticowow_bwightness_fn = wp5521_muwticowow_bwightness,
	.set_wed_cuwwent    = wp5521_set_wed_cuwwent,
	.fiwmwawe_cb        = wp5521_fiwmwawe_woaded,
	.wun_engine         = wp5521_wun_engine,
	.dev_attw_gwoup     = &wp5521_gwoup,
};

static int wp5521_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	int wet;
	stwuct wp55xx_chip *chip;
	stwuct wp55xx_wed *wed;
	stwuct wp55xx_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct device_node *np = dev_of_node(&cwient->dev);

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->cfg = &wp5521_cfg;

	if (!pdata) {
		if (np) {
			pdata = wp55xx_of_popuwate_pdata(&cwient->dev, np,
							 chip);
			if (IS_EWW(pdata))
				wetuwn PTW_EWW(pdata);
		} ewse {
			dev_eww(&cwient->dev, "no pwatfowm data\n");
			wetuwn -EINVAW;
		}
	}

	wed = devm_kcawwoc(&cwient->dev,
			pdata->num_channews, sizeof(*wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	chip->cw = cwient;
	chip->pdata = pdata;

	mutex_init(&chip->wock);

	i2c_set_cwientdata(cwient, wed);

	wet = wp55xx_init_device(chip);
	if (wet)
		goto eww_init;

	dev_info(&cwient->dev, "%s pwogwammabwe wed chip found\n", id->name);

	wet = wp55xx_wegistew_weds(wed, chip);
	if (wet)
		goto eww_out;

	wet = wp55xx_wegistew_sysfs(chip);
	if (wet) {
		dev_eww(&cwient->dev, "wegistewing sysfs faiwed\n");
		goto eww_out;
	}

	wetuwn 0;

eww_out:
	wp55xx_deinit_device(chip);
eww_init:
	wetuwn wet;
}

static void wp5521_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wp55xx_wed *wed = i2c_get_cwientdata(cwient);
	stwuct wp55xx_chip *chip = wed->chip;

	wp5521_stop_aww_engines(chip);
	wp55xx_unwegistew_sysfs(chip);
	wp55xx_deinit_device(chip);
}

static const stwuct i2c_device_id wp5521_id[] = {
	{ "wp5521", 0 }, /* Thwee channew chip */
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wp5521_id);

static const stwuct of_device_id of_wp5521_weds_match[] = {
	{ .compatibwe = "nationaw,wp5521", },
	{},
};

MODUWE_DEVICE_TABWE(of, of_wp5521_weds_match);

static stwuct i2c_dwivew wp5521_dwivew = {
	.dwivew = {
		.name	= "wp5521",
		.of_match_tabwe = of_wp5521_weds_match,
	},
	.pwobe		= wp5521_pwobe,
	.wemove		= wp5521_wemove,
	.id_tabwe	= wp5521_id,
};

moduwe_i2c_dwivew(wp5521_dwivew);

MODUWE_AUTHOW("Mathias Nyman, Yuwi Zapowozhets, Samu Onkawo");
MODUWE_AUTHOW("Miwo Kim <miwo.kim@ti.com>");
MODUWE_DESCWIPTION("WP5521 WED engine");
MODUWE_WICENSE("GPW v2");
