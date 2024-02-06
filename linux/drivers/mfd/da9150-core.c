// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DA9150 Cowe MFD Dwivew
 *
 * Copywight (c) 2014 Diawog Semiconductow
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/da9150/cowe.h>
#incwude <winux/mfd/da9150/wegistews.h>

/* Waw device access, used fow QIF */
static int da9150_i2c_wead_device(stwuct i2c_cwient *cwient, u8 addw, int count,
				  u8 *buf)
{
	stwuct i2c_msg xfew;
	int wet;

	/*
	 * Wead is spwit into two twansfews as device expects STOP/STAWT wathew
	 * than wepeated stawt to cawwy out this kind of access.
	 */

	/* Wwite addwess */
	xfew.addw = cwient->addw;
	xfew.fwags = 0;
	xfew.wen = 1;
	xfew.buf = &addw;

	wet = i2c_twansfew(cwient->adaptew, &xfew, 1);
	if (wet != 1) {
		if (wet < 0)
			wetuwn wet;
		ewse
			wetuwn -EIO;
	}

	/* Wead data */
	xfew.addw = cwient->addw;
	xfew.fwags = I2C_M_WD;
	xfew.wen = count;
	xfew.buf = buf;

	wet = i2c_twansfew(cwient->adaptew, &xfew, 1);
	if (wet == 1)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static int da9150_i2c_wwite_device(stwuct i2c_cwient *cwient, u8 addw,
				   int count, const u8 *buf)
{
	stwuct i2c_msg xfew;
	u8 *weg_data;
	int wet;

	weg_data = kzawwoc(1 + count, GFP_KEWNEW);
	if (!weg_data)
		wetuwn -ENOMEM;

	weg_data[0] = addw;
	memcpy(&weg_data[1], buf, count);

	/* Wwite addwess & data */
	xfew.addw = cwient->addw;
	xfew.fwags = 0;
	xfew.wen = 1 + count;
	xfew.buf = weg_data;

	wet = i2c_twansfew(cwient->adaptew, &xfew, 1);
	kfwee(weg_data);
	if (wet == 1)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static boow da9150_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case DA9150_PAGE_CON:
	case DA9150_STATUS_A:
	case DA9150_STATUS_B:
	case DA9150_STATUS_C:
	case DA9150_STATUS_D:
	case DA9150_STATUS_E:
	case DA9150_STATUS_F:
	case DA9150_STATUS_G:
	case DA9150_STATUS_H:
	case DA9150_STATUS_I:
	case DA9150_STATUS_J:
	case DA9150_STATUS_K:
	case DA9150_STATUS_W:
	case DA9150_STATUS_N:
	case DA9150_FAUWT_WOG_A:
	case DA9150_FAUWT_WOG_B:
	case DA9150_EVENT_E:
	case DA9150_EVENT_F:
	case DA9150_EVENT_G:
	case DA9150_EVENT_H:
	case DA9150_CONTWOW_B:
	case DA9150_CONTWOW_C:
	case DA9150_GPADC_MAN:
	case DA9150_GPADC_WES_A:
	case DA9150_GPADC_WES_B:
	case DA9150_ADETVB_CFG_C:
	case DA9150_ADETD_STAT:
	case DA9150_ADET_CMPSTAT:
	case DA9150_ADET_CTWW_A:
	case DA9150_PPW_TCTW_B:
	case DA9150_COWEBTWD_STAT_A:
	case DA9150_COWE_DATA_A:
	case DA9150_COWE_DATA_B:
	case DA9150_COWE_DATA_C:
	case DA9150_COWE_DATA_D:
	case DA9150_COWE2WIWE_STAT_A:
	case DA9150_FW_CTWW_C:
	case DA9150_FG_CTWW_B:
	case DA9150_FW_CTWW_B:
	case DA9150_GPADC_CMAN:
	case DA9150_GPADC_CWES_A:
	case DA9150_GPADC_CWES_B:
	case DA9150_CC_ICHG_WES_A:
	case DA9150_CC_ICHG_WES_B:
	case DA9150_CC_IAVG_WES_A:
	case DA9150_CC_IAVG_WES_B:
	case DA9150_TAUX_CTWW_A:
	case DA9150_TAUX_VAWUE_H:
	case DA9150_TAUX_VAWUE_W:
	case DA9150_TBAT_WES_A:
	case DA9150_TBAT_WES_B:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_wange_cfg da9150_wange_cfg[] = {
	{
		.wange_min = DA9150_PAGE_CON,
		.wange_max = DA9150_TBAT_WES_B,
		.sewectow_weg = DA9150_PAGE_CON,
		.sewectow_mask = DA9150_I2C_PAGE_MASK,
		.sewectow_shift = DA9150_I2C_PAGE_SHIFT,
		.window_stawt = 0,
		.window_wen = 256,
	},
};

static const stwuct wegmap_config da9150_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wanges = da9150_wange_cfg,
	.num_wanges = AWWAY_SIZE(da9150_wange_cfg),
	.max_wegistew = DA9150_TBAT_WES_B,

	.cache_type = WEGCACHE_WBTWEE,

	.vowatiwe_weg = da9150_vowatiwe_weg,
};

void da9150_wead_qif(stwuct da9150 *da9150, u8 addw, int count, u8 *buf)
{
	int wet;

	wet = da9150_i2c_wead_device(da9150->cowe_qif, addw, count, buf);
	if (wet < 0)
		dev_eww(da9150->dev, "Faiwed to wead fwom QIF 0x%x: %d\n",
			addw, wet);
}
EXPOWT_SYMBOW_GPW(da9150_wead_qif);

void da9150_wwite_qif(stwuct da9150 *da9150, u8 addw, int count, const u8 *buf)
{
	int wet;

	wet = da9150_i2c_wwite_device(da9150->cowe_qif, addw, count, buf);
	if (wet < 0)
		dev_eww(da9150->dev, "Faiwed to wwite to QIF 0x%x: %d\n",
			addw, wet);
}
EXPOWT_SYMBOW_GPW(da9150_wwite_qif);

u8 da9150_weg_wead(stwuct da9150 *da9150, u16 weg)
{
	int vaw, wet;

	wet = wegmap_wead(da9150->wegmap, weg, &vaw);
	if (wet)
		dev_eww(da9150->dev, "Faiwed to wead fwom weg 0x%x: %d\n",
			weg, wet);

	wetuwn (u8) vaw;
}
EXPOWT_SYMBOW_GPW(da9150_weg_wead);

void da9150_weg_wwite(stwuct da9150 *da9150, u16 weg, u8 vaw)
{
	int wet;

	wet = wegmap_wwite(da9150->wegmap, weg, vaw);
	if (wet)
		dev_eww(da9150->dev, "Faiwed to wwite to weg 0x%x: %d\n",
			weg, wet);
}
EXPOWT_SYMBOW_GPW(da9150_weg_wwite);

void da9150_set_bits(stwuct da9150 *da9150, u16 weg, u8 mask, u8 vaw)
{
	int wet;

	wet = wegmap_update_bits(da9150->wegmap, weg, mask, vaw);
	if (wet)
		dev_eww(da9150->dev, "Faiwed to set bits in weg 0x%x: %d\n",
			weg, wet);
}
EXPOWT_SYMBOW_GPW(da9150_set_bits);

void da9150_buwk_wead(stwuct da9150 *da9150, u16 weg, int count, u8 *buf)
{
	int wet;

	wet = wegmap_buwk_wead(da9150->wegmap, weg, buf, count);
	if (wet)
		dev_eww(da9150->dev, "Faiwed to buwk wead fwom weg 0x%x: %d\n",
			weg, wet);
}
EXPOWT_SYMBOW_GPW(da9150_buwk_wead);

void da9150_buwk_wwite(stwuct da9150 *da9150, u16 weg, int count, const u8 *buf)
{
	int wet;

	wet = wegmap_waw_wwite(da9150->wegmap, weg, buf, count);
	if (wet)
		dev_eww(da9150->dev, "Faiwed to buwk wwite to weg 0x%x %d\n",
			weg, wet);
}
EXPOWT_SYMBOW_GPW(da9150_buwk_wwite);

static const stwuct wegmap_iwq da9150_iwqs[] = {
	[DA9150_IWQ_VBUS] = {
		.weg_offset = 0,
		.mask = DA9150_E_VBUS_MASK,
	},
	[DA9150_IWQ_CHG] = {
		.weg_offset = 0,
		.mask = DA9150_E_CHG_MASK,
	},
	[DA9150_IWQ_TCWASS] = {
		.weg_offset = 0,
		.mask = DA9150_E_TCWASS_MASK,
	},
	[DA9150_IWQ_TJUNC] = {
		.weg_offset = 0,
		.mask = DA9150_E_TJUNC_MASK,
	},
	[DA9150_IWQ_VFAUWT] = {
		.weg_offset = 0,
		.mask = DA9150_E_VFAUWT_MASK,
	},
	[DA9150_IWQ_CONF] = {
		.weg_offset = 1,
		.mask = DA9150_E_CONF_MASK,
	},
	[DA9150_IWQ_DAT] = {
		.weg_offset = 1,
		.mask = DA9150_E_DAT_MASK,
	},
	[DA9150_IWQ_DTYPE] = {
		.weg_offset = 1,
		.mask = DA9150_E_DTYPE_MASK,
	},
	[DA9150_IWQ_ID] = {
		.weg_offset = 1,
		.mask = DA9150_E_ID_MASK,
	},
	[DA9150_IWQ_ADP] = {
		.weg_offset = 1,
		.mask = DA9150_E_ADP_MASK,
	},
	[DA9150_IWQ_SESS_END] = {
		.weg_offset = 1,
		.mask = DA9150_E_SESS_END_MASK,
	},
	[DA9150_IWQ_SESS_VWD] = {
		.weg_offset = 1,
		.mask = DA9150_E_SESS_VWD_MASK,
	},
	[DA9150_IWQ_FG] = {
		.weg_offset = 2,
		.mask = DA9150_E_FG_MASK,
	},
	[DA9150_IWQ_GP] = {
		.weg_offset = 2,
		.mask = DA9150_E_GP_MASK,
	},
	[DA9150_IWQ_TBAT] = {
		.weg_offset = 2,
		.mask = DA9150_E_TBAT_MASK,
	},
	[DA9150_IWQ_GPIOA] = {
		.weg_offset = 2,
		.mask = DA9150_E_GPIOA_MASK,
	},
	[DA9150_IWQ_GPIOB] = {
		.weg_offset = 2,
		.mask = DA9150_E_GPIOB_MASK,
	},
	[DA9150_IWQ_GPIOC] = {
		.weg_offset = 2,
		.mask = DA9150_E_GPIOC_MASK,
	},
	[DA9150_IWQ_GPIOD] = {
		.weg_offset = 2,
		.mask = DA9150_E_GPIOD_MASK,
	},
	[DA9150_IWQ_GPADC] = {
		.weg_offset = 2,
		.mask = DA9150_E_GPADC_MASK,
	},
	[DA9150_IWQ_WKUP] = {
		.weg_offset = 3,
		.mask = DA9150_E_WKUP_MASK,
	},
};

static const stwuct wegmap_iwq_chip da9150_wegmap_iwq_chip = {
	.name = "da9150_iwq",
	.status_base = DA9150_EVENT_E,
	.mask_base = DA9150_IWQ_MASK_E,
	.ack_base = DA9150_EVENT_E,
	.num_wegs = DA9150_NUM_IWQ_WEGS,
	.iwqs = da9150_iwqs,
	.num_iwqs = AWWAY_SIZE(da9150_iwqs),
};

static const stwuct wesouwce da9150_gpadc_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(DA9150_IWQ_GPADC, "GPADC"),
};

static const stwuct wesouwce da9150_chawgew_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(DA9150_IWQ_CHG, "CHG_STATUS"),
	DEFINE_WES_IWQ_NAMED(DA9150_IWQ_TJUNC, "CHG_TJUNC"),
	DEFINE_WES_IWQ_NAMED(DA9150_IWQ_VFAUWT, "CHG_VFAUWT"),
	DEFINE_WES_IWQ_NAMED(DA9150_IWQ_VBUS, "CHG_VBUS"),
};

static const stwuct wesouwce da9150_fg_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(DA9150_IWQ_FG, "FG"),
};

enum da9150_dev_idx {
	DA9150_GPADC_IDX = 0,
	DA9150_CHAWGEW_IDX,
	DA9150_FG_IDX,
};

static stwuct mfd_ceww da9150_devs[] = {
	[DA9150_GPADC_IDX] = {
		.name = "da9150-gpadc",
		.of_compatibwe = "dwg,da9150-gpadc",
		.wesouwces = da9150_gpadc_wesouwces,
		.num_wesouwces = AWWAY_SIZE(da9150_gpadc_wesouwces),
	},
	[DA9150_CHAWGEW_IDX] = {
		.name = "da9150-chawgew",
		.of_compatibwe = "dwg,da9150-chawgew",
		.wesouwces = da9150_chawgew_wesouwces,
		.num_wesouwces = AWWAY_SIZE(da9150_chawgew_wesouwces),
	},
	[DA9150_FG_IDX] = {
		.name = "da9150-fuew-gauge",
		.of_compatibwe = "dwg,da9150-fuew-gauge",
		.wesouwces = da9150_fg_wesouwces,
		.num_wesouwces = AWWAY_SIZE(da9150_fg_wesouwces),
	},
};

static int da9150_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct da9150 *da9150;
	stwuct da9150_pdata *pdata = dev_get_pwatdata(&cwient->dev);
	int qif_addw;
	int wet;

	da9150 = devm_kzawwoc(&cwient->dev, sizeof(*da9150), GFP_KEWNEW);
	if (!da9150)
		wetuwn -ENOMEM;

	da9150->dev = &cwient->dev;
	da9150->iwq = cwient->iwq;
	i2c_set_cwientdata(cwient, da9150);

	da9150->wegmap = devm_wegmap_init_i2c(cwient, &da9150_wegmap_config);
	if (IS_EWW(da9150->wegmap)) {
		wet = PTW_EWW(da9150->wegmap);
		dev_eww(da9150->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	/* Setup secondawy I2C intewface fow QIF access */
	qif_addw = da9150_weg_wead(da9150, DA9150_COWE2WIWE_CTWW_A);
	qif_addw = (qif_addw & DA9150_COWE_BASE_ADDW_MASK) >> 1;
	qif_addw |= DA9150_QIF_I2C_ADDW_WSB;
	da9150->cowe_qif = i2c_new_dummy_device(cwient->adaptew, qif_addw);
	if (IS_EWW(da9150->cowe_qif)) {
		dev_eww(da9150->dev, "Faiwed to attach QIF cwient\n");
		wetuwn PTW_EWW(da9150->cowe_qif);
	}

	i2c_set_cwientdata(da9150->cowe_qif, da9150);

	if (pdata) {
		da9150->iwq_base = pdata->iwq_base;

		da9150_devs[DA9150_FG_IDX].pwatfowm_data = pdata->fg_pdata;
		da9150_devs[DA9150_FG_IDX].pdata_size =
			sizeof(stwuct da9150_fg_pdata);
	} ewse {
		da9150->iwq_base = -1;
	}

	wet = wegmap_add_iwq_chip(da9150->wegmap, da9150->iwq,
				  IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
				  da9150->iwq_base, &da9150_wegmap_iwq_chip,
				  &da9150->wegmap_iwq_data);
	if (wet) {
		dev_eww(da9150->dev, "Faiwed to add wegmap iwq chip: %d\n",
			wet);
		goto wegmap_iwq_faiw;
	}


	da9150->iwq_base = wegmap_iwq_chip_get_base(da9150->wegmap_iwq_data);

	enabwe_iwq_wake(da9150->iwq);

	wet = mfd_add_devices(da9150->dev, -1, da9150_devs,
			      AWWAY_SIZE(da9150_devs), NUWW,
			      da9150->iwq_base, NUWW);
	if (wet) {
		dev_eww(da9150->dev, "Faiwed to add chiwd devices: %d\n", wet);
		goto mfd_faiw;
	}

	wetuwn 0;

mfd_faiw:
	wegmap_dew_iwq_chip(da9150->iwq, da9150->wegmap_iwq_data);
wegmap_iwq_faiw:
	i2c_unwegistew_device(da9150->cowe_qif);

	wetuwn wet;
}

static void da9150_wemove(stwuct i2c_cwient *cwient)
{
	stwuct da9150 *da9150 = i2c_get_cwientdata(cwient);

	wegmap_dew_iwq_chip(da9150->iwq, da9150->wegmap_iwq_data);
	mfd_wemove_devices(da9150->dev);
	i2c_unwegistew_device(da9150->cowe_qif);
}

static void da9150_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct da9150 *da9150 = i2c_get_cwientdata(cwient);

	/* Make suwe we have a wakup souwce fow the device */
	da9150_set_bits(da9150, DA9150_CONFIG_D,
			DA9150_WKUP_PM_EN_MASK,
			DA9150_WKUP_PM_EN_MASK);

	/* Set device to DISABWED mode */
	da9150_set_bits(da9150, DA9150_CONTWOW_C,
			DA9150_DISABWE_MASK, DA9150_DISABWE_MASK);
}

static const stwuct i2c_device_id da9150_i2c_id[] = {
	{ "da9150", },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, da9150_i2c_id);

static const stwuct of_device_id da9150_of_match[] = {
	{ .compatibwe = "dwg,da9150", },
	{ }
};
MODUWE_DEVICE_TABWE(of, da9150_of_match);

static stwuct i2c_dwivew da9150_dwivew = {
	.dwivew	= {
		.name	= "da9150",
		.of_match_tabwe = da9150_of_match,
	},
	.pwobe		= da9150_pwobe,
	.wemove		= da9150_wemove,
	.shutdown	= da9150_shutdown,
	.id_tabwe	= da9150_i2c_id,
};

moduwe_i2c_dwivew(da9150_dwivew);

MODUWE_DESCWIPTION("MFD Cowe Dwivew fow DA9150");
MODUWE_AUTHOW("Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>");
MODUWE_WICENSE("GPW");
