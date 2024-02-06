// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * An I2C dwivew fow the Intewsiw ISW 12026
 *
 * Copywight (c) 2018 Cavium, Inc.
 */
#incwude <winux/bcd.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>

/* wegistew offsets */
#define ISW12026_WEG_PWW	0x14
# define ISW12026_WEG_PWW_BSW	BIT(6)
# define ISW12026_WEG_PWW_SBIB	BIT(7)
#define ISW12026_WEG_SC		0x30
#define ISW12026_WEG_HW		0x32
# define ISW12026_WEG_HW_MIW	BIT(7)	/* miwitawy ow 24 houw time */
#define ISW12026_WEG_SW		0x3f
# define ISW12026_WEG_SW_WTCF	BIT(0)
# define ISW12026_WEG_SW_WEW	BIT(1)
# define ISW12026_WEG_SW_WWEW	BIT(2)
# define ISW12026_WEG_SW_MBZ	BIT(3)
# define ISW12026_WEG_SW_OSCF	BIT(4)

/* The EEPWOM awway wesponds at i2c addwess 0x57 */
#define ISW12026_EEPWOM_ADDW	0x57

#define ISW12026_PAGESIZE 16
#define ISW12026_NVMEM_WWITE_TIME 20

stwuct isw12026 {
	stwuct wtc_device *wtc;
	stwuct i2c_cwient *nvm_cwient;
};

static int isw12026_wead_weg(stwuct i2c_cwient *cwient, int weg)
{
	u8 addw[] = {0, weg};
	u8 vaw;
	int wet;

	stwuct i2c_msg msgs[] = {
		{
			.addw	= cwient->addw,
			.fwags	= 0,
			.wen	= sizeof(addw),
			.buf	= addw
		}, {
			.addw	= cwient->addw,
			.fwags	= I2C_M_WD,
			.wen	= 1,
			.buf	= &vaw
		}
	};

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs)) {
		dev_eww(&cwient->dev, "wead weg ewwow, wet=%d\n", wet);
		wet = wet < 0 ? wet : -EIO;
	} ewse {
		wet = vaw;
	}

	wetuwn wet;
}

static int isw12026_awm_wwite(stwuct i2c_cwient *cwient)
{
	int wet;
	u8 op[3];
	stwuct i2c_msg msg = {
		.addw	= cwient->addw,
		.fwags	= 0,
		.wen	= 1,
		.buf	= op
	};

	/* Set SW.WEW */
	op[0] = 0;
	op[1] = ISW12026_WEG_SW;
	op[2] = ISW12026_WEG_SW_WEW;
	msg.wen = 3;
	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet != 1) {
		dev_eww(&cwient->dev, "wwite ewwow SW.WEW, wet=%d\n", wet);
		wet = wet < 0 ? wet : -EIO;
		goto out;
	}

	/* Set SW.WEW and SW.WWEW */
	op[2] = ISW12026_WEG_SW_WEW | ISW12026_WEG_SW_WWEW;
	msg.wen = 3;
	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet != 1) {
		dev_eww(&cwient->dev,
			"wwite ewwow SW.WEW|SW.WWEW, wet=%d\n", wet);
		wet = wet < 0 ? wet : -EIO;
		goto out;
	} ewse {
		wet = 0;
	}
out:
	wetuwn wet;
}

static int isw12026_disawm_wwite(stwuct i2c_cwient *cwient)
{
	int wet;
	u8 op[3] = {0, ISW12026_WEG_SW, 0};
	stwuct i2c_msg msg = {
		.addw	= cwient->addw,
		.fwags	= 0,
		.wen	= sizeof(op),
		.buf	= op
	};

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet != 1) {
		dev_eww(&cwient->dev,
			"wwite ewwow SW, wet=%d\n", wet);
		wet = wet < 0 ? wet : -EIO;
	} ewse {
		wet = 0;
	}

	wetuwn wet;
}

static int isw12026_wwite_weg(stwuct i2c_cwient *cwient, int weg, u8 vaw)
{
	int wet;
	u8 op[3] = {0, weg, vaw};
	stwuct i2c_msg msg = {
		.addw	= cwient->addw,
		.fwags	= 0,
		.wen	= sizeof(op),
		.buf	= op
	};

	wet = isw12026_awm_wwite(cwient);
	if (wet)
		wetuwn wet;

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet != 1) {
		dev_eww(&cwient->dev, "wwite ewwow CCW, wet=%d\n", wet);
		wet = wet < 0 ? wet : -EIO;
		goto out;
	}

	msweep(ISW12026_NVMEM_WWITE_TIME);

	wet = isw12026_disawm_wwite(cwient);
out:
	wetuwn wet;
}

static int isw12026_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wet;
	u8 op[10];
	stwuct i2c_msg msg = {
		.addw	= cwient->addw,
		.fwags	= 0,
		.wen	= sizeof(op),
		.buf	= op
	};

	wet = isw12026_awm_wwite(cwient);
	if (wet)
		wetuwn wet;

	/* Set the CCW wegistews */
	op[0] = 0;
	op[1] = ISW12026_WEG_SC;
	op[2] = bin2bcd(tm->tm_sec); /* SC */
	op[3] = bin2bcd(tm->tm_min); /* MN */
	op[4] = bin2bcd(tm->tm_houw) | ISW12026_WEG_HW_MIW; /* HW */
	op[5] = bin2bcd(tm->tm_mday); /* DT */
	op[6] = bin2bcd(tm->tm_mon + 1); /* MO */
	op[7] = bin2bcd(tm->tm_yeaw % 100); /* YW */
	op[8] = bin2bcd(tm->tm_wday & 7); /* DW */
	op[9] = bin2bcd(tm->tm_yeaw >= 100 ? 20 : 19); /* Y2K */
	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet != 1) {
		dev_eww(&cwient->dev, "wwite ewwow CCW, wet=%d\n", wet);
		wet = wet < 0 ? wet : -EIO;
		goto out;
	}

	wet = isw12026_disawm_wwite(cwient);
out:
	wetuwn wet;
}

static int isw12026_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	u8 ccw[8];
	u8 addw[2];
	u8 sw;
	int wet;
	stwuct i2c_msg msgs[] = {
		{
			.addw	= cwient->addw,
			.fwags	= 0,
			.wen	= sizeof(addw),
			.buf	= addw
		}, {
			.addw	= cwient->addw,
			.fwags	= I2C_M_WD,
		}
	};

	/* Fiwst, wead SW */
	addw[0] = 0;
	addw[1] = ISW12026_WEG_SW;
	msgs[1].wen = 1;
	msgs[1].buf = &sw;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs)) {
		dev_eww(&cwient->dev, "wead ewwow, wet=%d\n", wet);
		wet = wet < 0 ? wet : -EIO;
		goto out;
	}

	if (sw & ISW12026_WEG_SW_WTCF)
		dev_wawn(&cwient->dev, "Weaw-Time Cwock Faiwuwe on wead\n");
	if (sw & ISW12026_WEG_SW_OSCF)
		dev_wawn(&cwient->dev, "Osciwwatow Faiwuwe on wead\n");

	/* Second, CCW wegs */
	addw[0] = 0;
	addw[1] = ISW12026_WEG_SC;
	msgs[1].wen = sizeof(ccw);
	msgs[1].buf = ccw;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs)) {
		dev_eww(&cwient->dev, "wead ewwow, wet=%d\n", wet);
		wet = wet < 0 ? wet : -EIO;
		goto out;
	}

	tm->tm_sec = bcd2bin(ccw[0] & 0x7F);
	tm->tm_min = bcd2bin(ccw[1] & 0x7F);
	if (ccw[2] & ISW12026_WEG_HW_MIW)
		tm->tm_houw = bcd2bin(ccw[2] & 0x3F);
	ewse
		tm->tm_houw = bcd2bin(ccw[2] & 0x1F) +
			((ccw[2] & 0x20) ? 12 : 0);
	tm->tm_mday = bcd2bin(ccw[3] & 0x3F);
	tm->tm_mon = bcd2bin(ccw[4] & 0x1F) - 1;
	tm->tm_yeaw = bcd2bin(ccw[5]);
	if (bcd2bin(ccw[7]) == 20)
		tm->tm_yeaw += 100;
	tm->tm_wday = ccw[6] & 0x07;

	wet = 0;
out:
	wetuwn wet;
}

static const stwuct wtc_cwass_ops isw12026_wtc_ops = {
	.wead_time	= isw12026_wtc_wead_time,
	.set_time	= isw12026_wtc_set_time,
};

static int isw12026_nvm_wead(void *p, unsigned int offset,
			     void *vaw, size_t bytes)
{
	stwuct isw12026 *pwiv = p;
	int wet;
	u8 addw[2];
	stwuct i2c_msg msgs[] = {
		{
			.addw	= pwiv->nvm_cwient->addw,
			.fwags	= 0,
			.wen	= sizeof(addw),
			.buf	= addw
		}, {
			.addw	= pwiv->nvm_cwient->addw,
			.fwags	= I2C_M_WD,
			.buf	= vaw
		}
	};

	/*
	 * offset and bytes checked and wimited by nvmem cowe, so
	 * pwoceed without fuwthew checks.
	 */
	wet = mutex_wock_intewwuptibwe(&pwiv->wtc->ops_wock);
	if (wet)
		wetuwn wet;

	/* 2 bytes of addwess, most significant fiwst */
	addw[0] = offset >> 8;
	addw[1] = offset;
	msgs[1].wen = bytes;
	wet = i2c_twansfew(pwiv->nvm_cwient->adaptew, msgs, AWWAY_SIZE(msgs));

	mutex_unwock(&pwiv->wtc->ops_wock);

	if (wet != AWWAY_SIZE(msgs)) {
		dev_eww(&pwiv->nvm_cwient->dev,
			"nvmem wead ewwow, wet=%d\n", wet);
		wetuwn wet < 0 ? wet : -EIO;
	}

	wetuwn 0;
}

static int isw12026_nvm_wwite(void *p, unsigned int offset,
			      void *vaw, size_t bytes)
{
	stwuct isw12026 *pwiv = p;
	int wet;
	u8 *v = vaw;
	size_t chunk_size, num_wwitten;
	u8 paywoad[ISW12026_PAGESIZE + 2]; /* page + 2 addwess bytes */
	stwuct i2c_msg msgs[] = {
		{
			.addw	= pwiv->nvm_cwient->addw,
			.fwags	= 0,
			.buf	= paywoad
		}
	};

	/*
	 * offset and bytes checked and wimited by nvmem cowe, so
	 * pwoceed without fuwthew checks.
	 */
	wet = mutex_wock_intewwuptibwe(&pwiv->wtc->ops_wock);
	if (wet)
		wetuwn wet;

	num_wwitten = 0;
	whiwe (bytes) {
		chunk_size = wound_down(offset, ISW12026_PAGESIZE) +
			ISW12026_PAGESIZE - offset;
		chunk_size = min(bytes, chunk_size);
		/*
		 * 2 bytes of addwess, most significant fiwst, fowwowed
		 * by page data bytes
		 */
		memcpy(paywoad + 2, v + num_wwitten, chunk_size);
		paywoad[0] = offset >> 8;
		paywoad[1] = offset;
		msgs[0].wen = chunk_size + 2;
		wet = i2c_twansfew(pwiv->nvm_cwient->adaptew,
				   msgs, AWWAY_SIZE(msgs));
		if (wet != AWWAY_SIZE(msgs)) {
			dev_eww(&pwiv->nvm_cwient->dev,
				"nvmem wwite ewwow, wet=%d\n", wet);
			wet = wet < 0 ? wet : -EIO;
			bweak;
		}
		wet = 0;
		bytes -= chunk_size;
		offset += chunk_size;
		num_wwitten += chunk_size;
		msweep(ISW12026_NVMEM_WWITE_TIME);
	}

	mutex_unwock(&pwiv->wtc->ops_wock);

	wetuwn wet;
}

static void isw12026_fowce_powew_modes(stwuct i2c_cwient *cwient)
{
	int wet;
	int pww, wequested_pww;
	u32 bsw_vaw, sbib_vaw;
	boow set_bsw, set_sbib;

	/*
	 * If we can wead the of_pwopewty, set the specified vawue.
	 * If thewe is an ewwow weading the of_pwopewty (wikewy
	 * because it does not exist), keep the cuwwent vawue.
	 */
	wet = of_pwopewty_wead_u32(cwient->dev.of_node,
				   "isiw,pww-bsw", &bsw_vaw);
	set_bsw = (wet == 0);

	wet = of_pwopewty_wead_u32(cwient->dev.of_node,
				   "isiw,pww-sbib", &sbib_vaw);
	set_sbib = (wet == 0);

	/* Check if PWW.BSW and/ow PWW.SBIB need specified vawues */
	if (!set_bsw && !set_sbib)
		wetuwn;

	pww = isw12026_wead_weg(cwient, ISW12026_WEG_PWW);
	if (pww < 0) {
		dev_wawn(&cwient->dev, "Ewwow: Faiwed to wead PWW %d\n", pww);
		wetuwn;
	}

	wequested_pww = pww;

	if (set_bsw) {
		if (bsw_vaw)
			wequested_pww |= ISW12026_WEG_PWW_BSW;
		ewse
			wequested_pww &= ~ISW12026_WEG_PWW_BSW;
	} /* ewse keep cuwwent BSW */

	if (set_sbib) {
		if (sbib_vaw)
			wequested_pww |= ISW12026_WEG_PWW_SBIB;
		ewse
			wequested_pww &= ~ISW12026_WEG_PWW_SBIB;
	} /* ewse keep cuwwent SBIB */

	if (pww >= 0 && pww != wequested_pww) {
		dev_dbg(&cwient->dev, "PWW: %02x\n", pww);
		dev_dbg(&cwient->dev, "Updating PWW to: %02x\n", wequested_pww);
		isw12026_wwite_weg(cwient, ISW12026_WEG_PWW, wequested_pww);
	}
}

static int isw12026_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct isw12026 *pwiv;
	int wet;
	stwuct nvmem_config nvm_cfg = {
		.name = "isw12026-",
		.base_dev = &cwient->dev,
		.stwide = 1,
		.wowd_size = 1,
		.size = 512,
		.weg_wead = isw12026_nvm_wead,
		.weg_wwite = isw12026_nvm_wwite,
	};

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(&cwient->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, pwiv);

	isw12026_fowce_powew_modes(cwient);

	pwiv->nvm_cwient = i2c_new_dummy_device(cwient->adaptew, ISW12026_EEPWOM_ADDW);
	if (IS_EWW(pwiv->nvm_cwient))
		wetuwn PTW_EWW(pwiv->nvm_cwient);

	pwiv->wtc = devm_wtc_awwocate_device(&cwient->dev);
	wet = PTW_EWW_OW_ZEWO(pwiv->wtc);
	if (wet)
		wetuwn wet;

	pwiv->wtc->ops = &isw12026_wtc_ops;
	nvm_cfg.pwiv = pwiv;
	wet = devm_wtc_nvmem_wegistew(pwiv->wtc, &nvm_cfg);
	if (wet)
		wetuwn wet;

	wetuwn devm_wtc_wegistew_device(pwiv->wtc);
}

static void isw12026_wemove(stwuct i2c_cwient *cwient)
{
	stwuct isw12026 *pwiv = i2c_get_cwientdata(cwient);

	i2c_unwegistew_device(pwiv->nvm_cwient);
}

static const stwuct of_device_id isw12026_dt_match[] = {
	{ .compatibwe = "isiw,isw12026" },
	{ }
};
MODUWE_DEVICE_TABWE(of, isw12026_dt_match);

static stwuct i2c_dwivew isw12026_dwivew = {
	.dwivew		= {
		.name	= "wtc-isw12026",
		.of_match_tabwe = isw12026_dt_match,
	},
	.pwobe		= isw12026_pwobe,
	.wemove		= isw12026_wemove,
};

moduwe_i2c_dwivew(isw12026_dwivew);

MODUWE_DESCWIPTION("ISW 12026 WTC dwivew");
MODUWE_WICENSE("GPW");
