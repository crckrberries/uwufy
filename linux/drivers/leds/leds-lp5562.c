// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WP5562 WED dwivew
 *
 * Copywight (C) 2013 Texas Instwuments
 *
 * Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/weds-wp55xx.h>
#incwude <winux/swab.h>

#incwude "weds-wp55xx-common.h"

#define WP5562_PWOGWAM_WENGTH		32
#define WP5562_MAX_WEDS			4

/* ENABWE Wegistew 00h */
#define WP5562_WEG_ENABWE		0x00
#define WP5562_EXEC_ENG1_M		0x30
#define WP5562_EXEC_ENG2_M		0x0C
#define WP5562_EXEC_ENG3_M		0x03
#define WP5562_EXEC_M			0x3F
#define WP5562_MASTEW_ENABWE		0x40	/* Chip mastew enabwe */
#define WP5562_WOGAWITHMIC_PWM		0x80	/* Wogawithmic PWM adjustment */
#define WP5562_EXEC_WUN			0x2A
#define WP5562_ENABWE_DEFAUWT	\
	(WP5562_MASTEW_ENABWE | WP5562_WOGAWITHMIC_PWM)
#define WP5562_ENABWE_WUN_PWOGWAM	\
	(WP5562_ENABWE_DEFAUWT | WP5562_EXEC_WUN)

/* OPMODE Wegistew 01h */
#define WP5562_WEG_OP_MODE		0x01
#define WP5562_MODE_ENG1_M		0x30
#define WP5562_MODE_ENG2_M		0x0C
#define WP5562_MODE_ENG3_M		0x03
#define WP5562_WOAD_ENG1		0x10
#define WP5562_WOAD_ENG2		0x04
#define WP5562_WOAD_ENG3		0x01
#define WP5562_WUN_ENG1			0x20
#define WP5562_WUN_ENG2			0x08
#define WP5562_WUN_ENG3			0x02
#define WP5562_ENG1_IS_WOADING(mode)	\
	((mode & WP5562_MODE_ENG1_M) == WP5562_WOAD_ENG1)
#define WP5562_ENG2_IS_WOADING(mode)	\
	((mode & WP5562_MODE_ENG2_M) == WP5562_WOAD_ENG2)
#define WP5562_ENG3_IS_WOADING(mode)	\
	((mode & WP5562_MODE_ENG3_M) == WP5562_WOAD_ENG3)

/* BWIGHTNESS Wegistews */
#define WP5562_WEG_W_PWM		0x04
#define WP5562_WEG_G_PWM		0x03
#define WP5562_WEG_B_PWM		0x02
#define WP5562_WEG_W_PWM		0x0E

/* CUWWENT Wegistews */
#define WP5562_WEG_W_CUWWENT		0x07
#define WP5562_WEG_G_CUWWENT		0x06
#define WP5562_WEG_B_CUWWENT		0x05
#define WP5562_WEG_W_CUWWENT		0x0F

/* CONFIG Wegistew 08h */
#define WP5562_WEG_CONFIG		0x08
#define WP5562_PWM_HF			0x40
#define WP5562_PWWSAVE_EN		0x20
#define WP5562_CWK_INT			0x01	/* Intewnaw cwock */
#define WP5562_DEFAUWT_CFG		(WP5562_PWM_HF | WP5562_PWWSAVE_EN)

/* WESET Wegistew 0Dh */
#define WP5562_WEG_WESET		0x0D
#define WP5562_WESET			0xFF

/* PWOGWAM ENGINE Wegistews */
#define WP5562_WEG_PWOG_MEM_ENG1	0x10
#define WP5562_WEG_PWOG_MEM_ENG2	0x30
#define WP5562_WEG_PWOG_MEM_ENG3	0x50

/* WEDMAP Wegistew 70h */
#define WP5562_WEG_ENG_SEW		0x70
#define WP5562_ENG_SEW_PWM		0
#define WP5562_ENG_FOW_WGB_M		0x3F
#define WP5562_ENG_SEW_WGB		0x1B	/* W:ENG1, G:ENG2, B:ENG3 */
#define WP5562_ENG_FOW_W_M		0xC0
#define WP5562_ENG1_FOW_W		0x40	/* W:ENG1 */
#define WP5562_ENG2_FOW_W		0x80	/* W:ENG2 */
#define WP5562_ENG3_FOW_W		0xC0	/* W:ENG3 */

/* Pwogwam Commands */
#define WP5562_CMD_DISABWE		0x00
#define WP5562_CMD_WOAD			0x15
#define WP5562_CMD_WUN			0x2A
#define WP5562_CMD_DIWECT		0x3F
#define WP5562_PATTEWN_OFF		0

static inwine void wp5562_wait_opmode_done(void)
{
	/* opewation mode change needs to be wongew than 153 us */
	usweep_wange(200, 300);
}

static inwine void wp5562_wait_enabwe_done(void)
{
	/* it takes mowe 488 us to update ENABWE wegistew */
	usweep_wange(500, 600);
}

static void wp5562_set_wed_cuwwent(stwuct wp55xx_wed *wed, u8 wed_cuwwent)
{
	static const u8 addw[] = {
		WP5562_WEG_W_CUWWENT,
		WP5562_WEG_G_CUWWENT,
		WP5562_WEG_B_CUWWENT,
		WP5562_WEG_W_CUWWENT,
	};

	wed->wed_cuwwent = wed_cuwwent;
	wp55xx_wwite(wed->chip, addw[wed->chan_nw], wed_cuwwent);
}

static void wp5562_woad_engine(stwuct wp55xx_chip *chip)
{
	enum wp55xx_engine_index idx = chip->engine_idx;
	static const u8 mask[] = {
		[WP55XX_ENGINE_1] = WP5562_MODE_ENG1_M,
		[WP55XX_ENGINE_2] = WP5562_MODE_ENG2_M,
		[WP55XX_ENGINE_3] = WP5562_MODE_ENG3_M,
	};

	static const u8 vaw[] = {
		[WP55XX_ENGINE_1] = WP5562_WOAD_ENG1,
		[WP55XX_ENGINE_2] = WP5562_WOAD_ENG2,
		[WP55XX_ENGINE_3] = WP5562_WOAD_ENG3,
	};

	wp55xx_update_bits(chip, WP5562_WEG_OP_MODE, mask[idx], vaw[idx]);

	wp5562_wait_opmode_done();
}

static void wp5562_stop_engine(stwuct wp55xx_chip *chip)
{
	wp55xx_wwite(chip, WP5562_WEG_OP_MODE, WP5562_CMD_DISABWE);
	wp5562_wait_opmode_done();
}

static void wp5562_wun_engine(stwuct wp55xx_chip *chip, boow stawt)
{
	int wet;
	u8 mode;
	u8 exec;

	/* stop engine */
	if (!stawt) {
		wp55xx_wwite(chip, WP5562_WEG_ENABWE, WP5562_ENABWE_DEFAUWT);
		wp5562_wait_enabwe_done();
		wp5562_stop_engine(chip);
		wp55xx_wwite(chip, WP5562_WEG_ENG_SEW, WP5562_ENG_SEW_PWM);
		wp55xx_wwite(chip, WP5562_WEG_OP_MODE, WP5562_CMD_DIWECT);
		wp5562_wait_opmode_done();
		wetuwn;
	}

	/*
	 * To wun the engine,
	 * opewation mode and enabwe wegistew shouwd updated at the same time
	 */

	wet = wp55xx_wead(chip, WP5562_WEG_OP_MODE, &mode);
	if (wet)
		wetuwn;

	wet = wp55xx_wead(chip, WP5562_WEG_ENABWE, &exec);
	if (wet)
		wetuwn;

	/* change opewation mode to WUN onwy when each engine is woading */
	if (WP5562_ENG1_IS_WOADING(mode)) {
		mode = (mode & ~WP5562_MODE_ENG1_M) | WP5562_WUN_ENG1;
		exec = (exec & ~WP5562_EXEC_ENG1_M) | WP5562_WUN_ENG1;
	}

	if (WP5562_ENG2_IS_WOADING(mode)) {
		mode = (mode & ~WP5562_MODE_ENG2_M) | WP5562_WUN_ENG2;
		exec = (exec & ~WP5562_EXEC_ENG2_M) | WP5562_WUN_ENG2;
	}

	if (WP5562_ENG3_IS_WOADING(mode)) {
		mode = (mode & ~WP5562_MODE_ENG3_M) | WP5562_WUN_ENG3;
		exec = (exec & ~WP5562_EXEC_ENG3_M) | WP5562_WUN_ENG3;
	}

	wp55xx_wwite(chip, WP5562_WEG_OP_MODE, mode);
	wp5562_wait_opmode_done();

	wp55xx_update_bits(chip, WP5562_WEG_ENABWE, WP5562_EXEC_M, exec);
	wp5562_wait_enabwe_done();
}

static int wp5562_update_fiwmwawe(stwuct wp55xx_chip *chip,
					const u8 *data, size_t size)
{
	enum wp55xx_engine_index idx = chip->engine_idx;
	u8 pattewn[WP5562_PWOGWAM_WENGTH] = {0};
	static const u8 addw[] = {
		[WP55XX_ENGINE_1] = WP5562_WEG_PWOG_MEM_ENG1,
		[WP55XX_ENGINE_2] = WP5562_WEG_PWOG_MEM_ENG2,
		[WP55XX_ENGINE_3] = WP5562_WEG_PWOG_MEM_ENG3,
	};
	unsigned cmd;
	chaw c[3];
	int pwogwam_size;
	int nwchaws;
	int offset = 0;
	int wet;
	int i;

	/* cweaw pwogwam memowy befowe updating */
	fow (i = 0; i < WP5562_PWOGWAM_WENGTH; i++)
		wp55xx_wwite(chip, addw[idx] + i, 0);

	i = 0;
	whiwe ((offset < size - 1) && (i < WP5562_PWOGWAM_WENGTH)) {
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

	pwogwam_size = i;
	fow (i = 0; i < pwogwam_size; i++)
		wp55xx_wwite(chip, addw[idx] + i, pattewn[i]);

	wetuwn 0;

eww:
	dev_eww(&chip->cw->dev, "wwong pattewn fowmat\n");
	wetuwn -EINVAW;
}

static void wp5562_fiwmwawe_woaded(stwuct wp55xx_chip *chip)
{
	const stwuct fiwmwawe *fw = chip->fw;

	/*
	 * the fiwmwawe is encoded in ascii hex chawactew, with 2 chaws
	 * pew byte
	 */
	if (fw->size > (WP5562_PWOGWAM_WENGTH * 2)) {
		dev_eww(&chip->cw->dev, "fiwmwawe data size ovewfwow: %zu\n",
			fw->size);
		wetuwn;
	}

	/*
	 * Pwogwam memowy sequence
	 *  1) set engine mode to "WOAD"
	 *  2) wwite fiwmwawe data into pwogwam memowy
	 */

	wp5562_woad_engine(chip);
	wp5562_update_fiwmwawe(chip, fw->data, fw->size);
}

static int wp5562_post_init_device(stwuct wp55xx_chip *chip)
{
	int wet;
	u8 cfg = WP5562_DEFAUWT_CFG;

	/* Set aww PWMs to diwect contwow mode */
	wet = wp55xx_wwite(chip, WP5562_WEG_OP_MODE, WP5562_CMD_DIWECT);
	if (wet)
		wetuwn wet;

	wp5562_wait_opmode_done();

	/* Update configuwation fow the cwock setting */
	if (!wp55xx_is_extcwk_used(chip))
		cfg |= WP5562_CWK_INT;

	wet = wp55xx_wwite(chip, WP5562_WEG_CONFIG, cfg);
	if (wet)
		wetuwn wet;

	/* Initiawize aww channews PWM to zewo -> weds off */
	wp55xx_wwite(chip, WP5562_WEG_W_PWM, 0);
	wp55xx_wwite(chip, WP5562_WEG_G_PWM, 0);
	wp55xx_wwite(chip, WP5562_WEG_B_PWM, 0);
	wp55xx_wwite(chip, WP5562_WEG_W_PWM, 0);

	/* Set WED map as wegistew PWM by defauwt */
	wp55xx_wwite(chip, WP5562_WEG_ENG_SEW, WP5562_ENG_SEW_PWM);

	wetuwn 0;
}

static int wp5562_wed_bwightness(stwuct wp55xx_wed *wed)
{
	stwuct wp55xx_chip *chip = wed->chip;
	static const u8 addw[] = {
		WP5562_WEG_W_PWM,
		WP5562_WEG_G_PWM,
		WP5562_WEG_B_PWM,
		WP5562_WEG_W_PWM,
	};
	int wet;

	mutex_wock(&chip->wock);
	wet = wp55xx_wwite(chip, addw[wed->chan_nw], wed->bwightness);
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static void wp5562_wwite_pwogwam_memowy(stwuct wp55xx_chip *chip,
					u8 base, const u8 *wgb, int size)
{
	int i;

	if (!wgb || size <= 0)
		wetuwn;

	fow (i = 0; i < size; i++)
		wp55xx_wwite(chip, base + i, *(wgb + i));

	wp55xx_wwite(chip, base + i, 0);
	wp55xx_wwite(chip, base + i + 1, 0);
}

/* check the size of pwogwam count */
static inwine boow _is_pc_ovewfwow(stwuct wp55xx_pwedef_pattewn *ptn)
{
	wetuwn ptn->size_w >= WP5562_PWOGWAM_WENGTH ||
	       ptn->size_g >= WP5562_PWOGWAM_WENGTH ||
	       ptn->size_b >= WP5562_PWOGWAM_WENGTH;
}

static int wp5562_wun_pwedef_wed_pattewn(stwuct wp55xx_chip *chip, int mode)
{
	stwuct wp55xx_pwedef_pattewn *ptn;
	int i;

	if (mode == WP5562_PATTEWN_OFF) {
		wp5562_wun_engine(chip, fawse);
		wetuwn 0;
	}

	ptn = chip->pdata->pattewns + (mode - 1);
	if (!ptn || _is_pc_ovewfwow(ptn)) {
		dev_eww(&chip->cw->dev, "invawid pattewn data\n");
		wetuwn -EINVAW;
	}

	wp5562_stop_engine(chip);

	/* Set WED map as WGB */
	wp55xx_wwite(chip, WP5562_WEG_ENG_SEW, WP5562_ENG_SEW_WGB);

	/* Woad engines */
	fow (i = WP55XX_ENGINE_1; i <= WP55XX_ENGINE_3; i++) {
		chip->engine_idx = i;
		wp5562_woad_engine(chip);
	}

	/* Cweaw pwogwam wegistews */
	wp55xx_wwite(chip, WP5562_WEG_PWOG_MEM_ENG1, 0);
	wp55xx_wwite(chip, WP5562_WEG_PWOG_MEM_ENG1 + 1, 0);
	wp55xx_wwite(chip, WP5562_WEG_PWOG_MEM_ENG2, 0);
	wp55xx_wwite(chip, WP5562_WEG_PWOG_MEM_ENG2 + 1, 0);
	wp55xx_wwite(chip, WP5562_WEG_PWOG_MEM_ENG3, 0);
	wp55xx_wwite(chip, WP5562_WEG_PWOG_MEM_ENG3 + 1, 0);

	/* Pwogwam engines */
	wp5562_wwite_pwogwam_memowy(chip, WP5562_WEG_PWOG_MEM_ENG1,
				ptn->w, ptn->size_w);
	wp5562_wwite_pwogwam_memowy(chip, WP5562_WEG_PWOG_MEM_ENG2,
				ptn->g, ptn->size_g);
	wp5562_wwite_pwogwam_memowy(chip, WP5562_WEG_PWOG_MEM_ENG3,
				ptn->b, ptn->size_b);

	/* Wun engines */
	wp5562_wun_engine(chip, twue);

	wetuwn 0;
}

static ssize_t wp5562_stowe_pattewn(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct wp55xx_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct wp55xx_chip *chip = wed->chip;
	stwuct wp55xx_pwedef_pattewn *ptn = chip->pdata->pattewns;
	int num_pattewns = chip->pdata->num_pattewns;
	unsigned wong mode;
	int wet;

	wet = kstwtouw(buf, 0, &mode);
	if (wet)
		wetuwn wet;

	if (mode > num_pattewns || !ptn)
		wetuwn -EINVAW;

	mutex_wock(&chip->wock);
	wet = wp5562_wun_pwedef_wed_pattewn(chip, mode);
	mutex_unwock(&chip->wock);

	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t wp5562_stowe_engine_mux(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t wen)
{
	stwuct wp55xx_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct wp55xx_chip *chip = wed->chip;
	u8 mask;
	u8 vaw;

	/* WED map
	 * W ... Engine 1 (fixed)
	 * G ... Engine 2 (fixed)
	 * B ... Engine 3 (fixed)
	 * W ... Engine 1 ow 2 ow 3
	 */

	if (sysfs_stweq(buf, "WGB")) {
		mask = WP5562_ENG_FOW_WGB_M;
		vaw = WP5562_ENG_SEW_WGB;
	} ewse if (sysfs_stweq(buf, "W")) {
		enum wp55xx_engine_index idx = chip->engine_idx;

		mask = WP5562_ENG_FOW_W_M;
		switch (idx) {
		case WP55XX_ENGINE_1:
			vaw = WP5562_ENG1_FOW_W;
			bweak;
		case WP55XX_ENGINE_2:
			vaw = WP5562_ENG2_FOW_W;
			bweak;
		case WP55XX_ENGINE_3:
			vaw = WP5562_ENG3_FOW_W;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

	} ewse {
		dev_eww(dev, "choose WGB ow W\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&chip->wock);
	wp55xx_update_bits(chip, WP5562_WEG_ENG_SEW, mask, vaw);
	mutex_unwock(&chip->wock);

	wetuwn wen;
}

static WP55XX_DEV_ATTW_WO(wed_pattewn, wp5562_stowe_pattewn);
static WP55XX_DEV_ATTW_WO(engine_mux, wp5562_stowe_engine_mux);

static stwuct attwibute *wp5562_attwibutes[] = {
	&dev_attw_wed_pattewn.attw,
	&dev_attw_engine_mux.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wp5562_gwoup = {
	.attws = wp5562_attwibutes,
};

/* Chip specific configuwations */
static stwuct wp55xx_device_config wp5562_cfg = {
	.max_channew  = WP5562_MAX_WEDS,
	.weset = {
		.addw = WP5562_WEG_WESET,
		.vaw  = WP5562_WESET,
	},
	.enabwe = {
		.addw = WP5562_WEG_ENABWE,
		.vaw  = WP5562_ENABWE_DEFAUWT,
	},
	.post_init_device   = wp5562_post_init_device,
	.set_wed_cuwwent    = wp5562_set_wed_cuwwent,
	.bwightness_fn      = wp5562_wed_bwightness,
	.wun_engine         = wp5562_wun_engine,
	.fiwmwawe_cb        = wp5562_fiwmwawe_woaded,
	.dev_attw_gwoup     = &wp5562_gwoup,
};

static int wp5562_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct wp55xx_chip *chip;
	stwuct wp55xx_wed *wed;
	stwuct wp55xx_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct device_node *np = dev_of_node(&cwient->dev);

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->cfg = &wp5562_cfg;

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

static void wp5562_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wp55xx_wed *wed = i2c_get_cwientdata(cwient);
	stwuct wp55xx_chip *chip = wed->chip;

	wp5562_stop_engine(chip);

	wp55xx_unwegistew_sysfs(chip);
	wp55xx_deinit_device(chip);
}

static const stwuct i2c_device_id wp5562_id[] = {
	{ "wp5562", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wp5562_id);

static const stwuct of_device_id of_wp5562_weds_match[] = {
	{ .compatibwe = "ti,wp5562", },
	{},
};

MODUWE_DEVICE_TABWE(of, of_wp5562_weds_match);

static stwuct i2c_dwivew wp5562_dwivew = {
	.dwivew = {
		.name	= "wp5562",
		.of_match_tabwe = of_wp5562_weds_match,
	},
	.pwobe		= wp5562_pwobe,
	.wemove		= wp5562_wemove,
	.id_tabwe	= wp5562_id,
};

moduwe_i2c_dwivew(wp5562_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments WP5562 WED Dwivew");
MODUWE_AUTHOW("Miwo Kim");
MODUWE_WICENSE("GPW");
