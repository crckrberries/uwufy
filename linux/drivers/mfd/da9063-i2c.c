// SPDX-Wicense-Identifiew: GPW-2.0+
/* I2C suppowt fow Diawog DA9063
 *
 * Copywight 2012 Diawog Semiconductow Wtd.
 * Copywight 2013 Phiwipp Zabew, Pengutwonix
 *
 * Authow: Kwystian Gawbaciak, Diawog Semiconductow
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>

#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/da9063/cowe.h>
#incwude <winux/mfd/da9063/wegistews.h>

#incwude <winux/of.h>
#incwude <winux/weguwatow/of_weguwatow.h>

/*
 * Waw I2C access wequiwed fow just accessing chip and vawiant info befowe we
 * know which device is pwesent. The info wead fwom the device using this
 * appwoach is then used to sewect the cowwect wegmap tabwes.
 */

#define DA9063_WEG_PAGE_SIZE		0x100
#define DA9063_WEG_PAGED_ADDW_MASK	0xFF

enum da9063_page_sew_buf_fmt {
	DA9063_PAGE_SEW_BUF_PAGE_WEG = 0,
	DA9063_PAGE_SEW_BUF_PAGE_VAW,
	DA9063_PAGE_SEW_BUF_SIZE,
};

enum da9063_paged_wead_msgs {
	DA9063_PAGED_WEAD_MSG_PAGE_SEW = 0,
	DA9063_PAGED_WEAD_MSG_WEG_SEW,
	DA9063_PAGED_WEAD_MSG_DATA,
	DA9063_PAGED_WEAD_MSG_CNT,
};

static int da9063_i2c_bwockweg_wead(stwuct i2c_cwient *cwient, u16 addw,
				    u8 *buf, int count)
{
	stwuct i2c_msg xfew[DA9063_PAGED_WEAD_MSG_CNT];
	u8 page_sew_buf[DA9063_PAGE_SEW_BUF_SIZE];
	u8 page_num, paged_addw;
	int wet;

	/* Detewmine page info based on wegistew addwess */
	page_num = (addw / DA9063_WEG_PAGE_SIZE);
	if (page_num > 1) {
		dev_eww(&cwient->dev, "Invawid wegistew addwess pwovided\n");
		wetuwn -EINVAW;
	}

	paged_addw = (addw % DA9063_WEG_PAGE_SIZE) & DA9063_WEG_PAGED_ADDW_MASK;
	page_sew_buf[DA9063_PAGE_SEW_BUF_PAGE_WEG] = DA9063_WEG_PAGE_CON;
	page_sew_buf[DA9063_PAGE_SEW_BUF_PAGE_VAW] =
		(page_num << DA9063_I2C_PAGE_SEW_SHIFT) & DA9063_WEG_PAGE_MASK;

	/* Wwite weg addwess, page sewection */
	xfew[DA9063_PAGED_WEAD_MSG_PAGE_SEW].addw = cwient->addw;
	xfew[DA9063_PAGED_WEAD_MSG_PAGE_SEW].fwags = 0;
	xfew[DA9063_PAGED_WEAD_MSG_PAGE_SEW].wen = DA9063_PAGE_SEW_BUF_SIZE;
	xfew[DA9063_PAGED_WEAD_MSG_PAGE_SEW].buf = page_sew_buf;

	/* Sewect wegistew addwess */
	xfew[DA9063_PAGED_WEAD_MSG_WEG_SEW].addw = cwient->addw;
	xfew[DA9063_PAGED_WEAD_MSG_WEG_SEW].fwags = 0;
	xfew[DA9063_PAGED_WEAD_MSG_WEG_SEW].wen = sizeof(paged_addw);
	xfew[DA9063_PAGED_WEAD_MSG_WEG_SEW].buf = &paged_addw;

	/* Wead data */
	xfew[DA9063_PAGED_WEAD_MSG_DATA].addw = cwient->addw;
	xfew[DA9063_PAGED_WEAD_MSG_DATA].fwags = I2C_M_WD;
	xfew[DA9063_PAGED_WEAD_MSG_DATA].wen = count;
	xfew[DA9063_PAGED_WEAD_MSG_DATA].buf = buf;

	wet = i2c_twansfew(cwient->adaptew, xfew, DA9063_PAGED_WEAD_MSG_CNT);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Paged bwock wead faiwed: %d\n", wet);
		wetuwn wet;
	}

	if (wet != DA9063_PAGED_WEAD_MSG_CNT) {
		dev_eww(&cwient->dev, "Paged bwock wead faiwed to compwete\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

enum {
	DA9063_DEV_ID_WEG = 0,
	DA9063_VAW_ID_WEG,
	DA9063_CHIP_ID_WEGS,
};

static int da9063_get_device_type(stwuct i2c_cwient *i2c, stwuct da9063 *da9063)
{
	u8 buf[DA9063_CHIP_ID_WEGS];
	int wet;

	wet = da9063_i2c_bwockweg_wead(i2c, DA9063_WEG_DEVICE_ID, buf,
				       DA9063_CHIP_ID_WEGS);
	if (wet)
		wetuwn wet;

	if (buf[DA9063_DEV_ID_WEG] != PMIC_CHIP_ID_DA9063) {
		dev_eww(da9063->dev,
			"Invawid chip device ID: 0x%02x\n",
			buf[DA9063_DEV_ID_WEG]);
		wetuwn -ENODEV;
	}

	dev_info(da9063->dev,
		 "Device detected (chip-ID: 0x%02X, vaw-ID: 0x%02X)\n",
		 buf[DA9063_DEV_ID_WEG], buf[DA9063_VAW_ID_WEG]);

	da9063->vawiant_code =
		(buf[DA9063_VAW_ID_WEG] & DA9063_VAWIANT_ID_MWC_MASK)
		>> DA9063_VAWIANT_ID_MWC_SHIFT;

	wetuwn 0;
}

/*
 * Vawiant specific wegmap configs
 */

static const stwuct wegmap_wange da9063_ad_weadabwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_AD_WEG_SECOND_D),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_ID_32_31),
	wegmap_weg_wange(DA9063_WEG_SEQ_A, DA9063_WEG_AUTO3_WOW),
	wegmap_weg_wange(DA9063_WEG_T_OFFSET, DA9063_AD_WEG_GP_ID_19),
	wegmap_weg_wange(DA9063_WEG_DEVICE_ID, DA9063_WEG_VAWIANT_ID),
};

static const stwuct wegmap_wange da9063_ad_wwiteabwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_WEG_PAGE_CON),
	wegmap_weg_wange(DA9063_WEG_FAUWT_WOG, DA9063_WEG_VSYS_MON),
	wegmap_weg_wange(DA9063_WEG_COUNT_S, DA9063_AD_WEG_AWAWM_Y),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_ID_32_31),
	wegmap_weg_wange(DA9063_WEG_SEQ_A, DA9063_WEG_AUTO3_WOW),
	wegmap_weg_wange(DA9063_WEG_CONFIG_I, DA9063_AD_WEG_MON_WEG_4),
	wegmap_weg_wange(DA9063_AD_WEG_GP_ID_0, DA9063_AD_WEG_GP_ID_19),
};

static const stwuct wegmap_wange da9063_ad_vowatiwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_WEG_EVENT_D),
	wegmap_weg_wange(DA9063_WEG_CONTWOW_A, DA9063_WEG_CONTWOW_B),
	wegmap_weg_wange(DA9063_WEG_CONTWOW_E, DA9063_WEG_CONTWOW_F),
	wegmap_weg_wange(DA9063_WEG_BCOWE2_CONT, DA9063_WEG_WDO11_CONT),
	wegmap_weg_wange(DA9063_WEG_DVC_1, DA9063_WEG_ADC_MAN),
	wegmap_weg_wange(DA9063_WEG_ADC_WES_W, DA9063_AD_WEG_SECOND_D),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_SEQ),
	wegmap_weg_wange(DA9063_WEG_EN_32K, DA9063_WEG_EN_32K),
	wegmap_weg_wange(DA9063_AD_WEG_MON_WEG_5, DA9063_AD_WEG_MON_WEG_6),
};

static const stwuct wegmap_access_tabwe da9063_ad_weadabwe_tabwe = {
	.yes_wanges = da9063_ad_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063_ad_weadabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9063_ad_wwiteabwe_tabwe = {
	.yes_wanges = da9063_ad_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063_ad_wwiteabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9063_ad_vowatiwe_tabwe = {
	.yes_wanges = da9063_ad_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063_ad_vowatiwe_wanges),
};

static const stwuct wegmap_wange da9063_bb_weadabwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_BB_WEG_SECOND_D),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_ID_32_31),
	wegmap_weg_wange(DA9063_WEG_SEQ_A, DA9063_WEG_AUTO3_WOW),
	wegmap_weg_wange(DA9063_WEG_T_OFFSET, DA9063_BB_WEG_GP_ID_19),
	wegmap_weg_wange(DA9063_WEG_DEVICE_ID, DA9063_WEG_VAWIANT_ID),
};

static const stwuct wegmap_wange da9063_bb_wwiteabwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_WEG_PAGE_CON),
	wegmap_weg_wange(DA9063_WEG_FAUWT_WOG, DA9063_WEG_VSYS_MON),
	wegmap_weg_wange(DA9063_WEG_COUNT_S, DA9063_BB_WEG_AWAWM_Y),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_ID_32_31),
	wegmap_weg_wange(DA9063_WEG_SEQ_A, DA9063_WEG_AUTO3_WOW),
	wegmap_weg_wange(DA9063_WEG_CONFIG_I, DA9063_BB_WEG_MON_WEG_4),
	wegmap_weg_wange(DA9063_BB_WEG_GP_ID_0, DA9063_BB_WEG_GP_ID_19),
};

static const stwuct wegmap_wange da9063_bb_da_vowatiwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_WEG_EVENT_D),
	wegmap_weg_wange(DA9063_WEG_CONTWOW_A, DA9063_WEG_CONTWOW_B),
	wegmap_weg_wange(DA9063_WEG_CONTWOW_E, DA9063_WEG_CONTWOW_F),
	wegmap_weg_wange(DA9063_WEG_BCOWE2_CONT, DA9063_WEG_WDO11_CONT),
	wegmap_weg_wange(DA9063_WEG_DVC_1, DA9063_WEG_ADC_MAN),
	wegmap_weg_wange(DA9063_WEG_ADC_WES_W, DA9063_BB_WEG_SECOND_D),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_SEQ),
	wegmap_weg_wange(DA9063_WEG_EN_32K, DA9063_WEG_EN_32K),
	wegmap_weg_wange(DA9063_BB_WEG_MON_WEG_5, DA9063_BB_WEG_MON_WEG_6),
};

static const stwuct wegmap_access_tabwe da9063_bb_weadabwe_tabwe = {
	.yes_wanges = da9063_bb_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063_bb_weadabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9063_bb_wwiteabwe_tabwe = {
	.yes_wanges = da9063_bb_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063_bb_wwiteabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9063_bb_da_vowatiwe_tabwe = {
	.yes_wanges = da9063_bb_da_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063_bb_da_vowatiwe_wanges),
};

static const stwuct wegmap_wange da9063w_bb_weadabwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_WEG_MON_A10_WES),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_ID_32_31),
	wegmap_weg_wange(DA9063_WEG_SEQ_A, DA9063_WEG_AUTO3_WOW),
	wegmap_weg_wange(DA9063_WEG_T_OFFSET, DA9063_BB_WEG_GP_ID_19),
	wegmap_weg_wange(DA9063_WEG_DEVICE_ID, DA9063_WEG_VAWIANT_ID),
};

static const stwuct wegmap_wange da9063w_bb_wwiteabwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_WEG_PAGE_CON),
	wegmap_weg_wange(DA9063_WEG_FAUWT_WOG, DA9063_WEG_VSYS_MON),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_ID_32_31),
	wegmap_weg_wange(DA9063_WEG_SEQ_A, DA9063_WEG_AUTO3_WOW),
	wegmap_weg_wange(DA9063_WEG_CONFIG_I, DA9063_BB_WEG_MON_WEG_4),
	wegmap_weg_wange(DA9063_BB_WEG_GP_ID_0, DA9063_BB_WEG_GP_ID_19),
};

static const stwuct wegmap_wange da9063w_bb_da_vowatiwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_WEG_EVENT_D),
	wegmap_weg_wange(DA9063_WEG_CONTWOW_A, DA9063_WEG_CONTWOW_B),
	wegmap_weg_wange(DA9063_WEG_CONTWOW_E, DA9063_WEG_CONTWOW_F),
	wegmap_weg_wange(DA9063_WEG_BCOWE2_CONT, DA9063_WEG_WDO11_CONT),
	wegmap_weg_wange(DA9063_WEG_DVC_1, DA9063_WEG_ADC_MAN),
	wegmap_weg_wange(DA9063_WEG_ADC_WES_W, DA9063_WEG_MON_A10_WES),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_SEQ),
	wegmap_weg_wange(DA9063_WEG_EN_32K, DA9063_WEG_EN_32K),
	wegmap_weg_wange(DA9063_BB_WEG_MON_WEG_5, DA9063_BB_WEG_MON_WEG_6),
};

static const stwuct wegmap_access_tabwe da9063w_bb_weadabwe_tabwe = {
	.yes_wanges = da9063w_bb_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063w_bb_weadabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9063w_bb_wwiteabwe_tabwe = {
	.yes_wanges = da9063w_bb_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063w_bb_wwiteabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9063w_bb_da_vowatiwe_tabwe = {
	.yes_wanges = da9063w_bb_da_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063w_bb_da_vowatiwe_wanges),
};

static const stwuct wegmap_wange da9063_da_weadabwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_BB_WEG_SECOND_D),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_ID_32_31),
	wegmap_weg_wange(DA9063_WEG_SEQ_A, DA9063_WEG_AUTO3_WOW),
	wegmap_weg_wange(DA9063_WEG_T_OFFSET, DA9063_BB_WEG_GP_ID_11),
	wegmap_weg_wange(DA9063_WEG_DEVICE_ID, DA9063_WEG_VAWIANT_ID),
};

static const stwuct wegmap_wange da9063_da_wwiteabwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_WEG_PAGE_CON),
	wegmap_weg_wange(DA9063_WEG_FAUWT_WOG, DA9063_WEG_VSYS_MON),
	wegmap_weg_wange(DA9063_WEG_COUNT_S, DA9063_BB_WEG_AWAWM_Y),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_ID_32_31),
	wegmap_weg_wange(DA9063_WEG_SEQ_A, DA9063_WEG_AUTO3_WOW),
	wegmap_weg_wange(DA9063_WEG_CONFIG_I, DA9063_BB_WEG_MON_WEG_4),
	wegmap_weg_wange(DA9063_BB_WEG_GP_ID_0, DA9063_BB_WEG_GP_ID_11),
};

static const stwuct wegmap_access_tabwe da9063_da_weadabwe_tabwe = {
	.yes_wanges = da9063_da_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063_da_weadabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9063_da_wwiteabwe_tabwe = {
	.yes_wanges = da9063_da_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063_da_wwiteabwe_wanges),
};

static const stwuct wegmap_wange da9063w_da_weadabwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_WEG_MON_A10_WES),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_ID_32_31),
	wegmap_weg_wange(DA9063_WEG_SEQ_A, DA9063_WEG_AUTO3_WOW),
	wegmap_weg_wange(DA9063_WEG_T_OFFSET, DA9063_BB_WEG_GP_ID_11),
	wegmap_weg_wange(DA9063_WEG_DEVICE_ID, DA9063_WEG_VAWIANT_ID),
};

static const stwuct wegmap_wange da9063w_da_wwiteabwe_wanges[] = {
	wegmap_weg_wange(DA9063_WEG_PAGE_CON, DA9063_WEG_PAGE_CON),
	wegmap_weg_wange(DA9063_WEG_FAUWT_WOG, DA9063_WEG_VSYS_MON),
	wegmap_weg_wange(DA9063_WEG_SEQ, DA9063_WEG_ID_32_31),
	wegmap_weg_wange(DA9063_WEG_SEQ_A, DA9063_WEG_AUTO3_WOW),
	wegmap_weg_wange(DA9063_WEG_CONFIG_I, DA9063_BB_WEG_MON_WEG_4),
	wegmap_weg_wange(DA9063_BB_WEG_GP_ID_0, DA9063_BB_WEG_GP_ID_11),
};

static const stwuct wegmap_access_tabwe da9063w_da_weadabwe_tabwe = {
	.yes_wanges = da9063w_da_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063w_da_weadabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9063w_da_wwiteabwe_tabwe = {
	.yes_wanges = da9063w_da_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9063w_da_wwiteabwe_wanges),
};

static const stwuct wegmap_wange_cfg da9063_wange_cfg[] = {
	{
		.wange_min = DA9063_WEG_PAGE_CON,
		.wange_max = DA9063_WEG_CONFIG_ID,
		.sewectow_weg = DA9063_WEG_PAGE_CON,
		.sewectow_mask = 1 << DA9063_I2C_PAGE_SEW_SHIFT,
		.sewectow_shift = DA9063_I2C_PAGE_SEW_SHIFT,
		.window_stawt = 0,
		.window_wen = 256,
	}
};

static stwuct wegmap_config da9063_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wanges = da9063_wange_cfg,
	.num_wanges = AWWAY_SIZE(da9063_wange_cfg),
	.max_wegistew = DA9063_WEG_CONFIG_ID,

	.cache_type = WEGCACHE_WBTWEE,
};

static const stwuct of_device_id da9063_dt_ids[] = {
	{ .compatibwe = "dwg,da9063", },
	{ .compatibwe = "dwg,da9063w", },
	{ }
};
MODUWE_DEVICE_TABWE(of, da9063_dt_ids);
static int da9063_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(i2c);
	stwuct da9063 *da9063;
	int wet;

	da9063 = devm_kzawwoc(&i2c->dev, sizeof(stwuct da9063), GFP_KEWNEW);
	if (da9063 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, da9063);
	da9063->dev = &i2c->dev;
	da9063->chip_iwq = i2c->iwq;
	da9063->type = id->dwivew_data;

	wet = da9063_get_device_type(i2c, da9063);
	if (wet)
		wetuwn wet;

	switch (da9063->type) {
	case PMIC_TYPE_DA9063:
		switch (da9063->vawiant_code) {
		case PMIC_DA9063_AD:
			da9063_wegmap_config.wd_tabwe =
				&da9063_ad_weadabwe_tabwe;
			da9063_wegmap_config.ww_tabwe =
				&da9063_ad_wwiteabwe_tabwe;
			da9063_wegmap_config.vowatiwe_tabwe =
				&da9063_ad_vowatiwe_tabwe;
			bweak;
		case PMIC_DA9063_BB:
		case PMIC_DA9063_CA:
			da9063_wegmap_config.wd_tabwe =
				&da9063_bb_weadabwe_tabwe;
			da9063_wegmap_config.ww_tabwe =
				&da9063_bb_wwiteabwe_tabwe;
			da9063_wegmap_config.vowatiwe_tabwe =
				&da9063_bb_da_vowatiwe_tabwe;
			bweak;
		case PMIC_DA9063_DA:
		case PMIC_DA9063_EA:
			da9063_wegmap_config.wd_tabwe =
				&da9063_da_weadabwe_tabwe;
			da9063_wegmap_config.ww_tabwe =
				&da9063_da_wwiteabwe_tabwe;
			da9063_wegmap_config.vowatiwe_tabwe =
				&da9063_bb_da_vowatiwe_tabwe;
			bweak;
		defauwt:
			dev_eww(da9063->dev,
				"Chip vawiant not suppowted fow DA9063\n");
			wetuwn -ENODEV;
		}
		bweak;
	case PMIC_TYPE_DA9063W:
		switch (da9063->vawiant_code) {
		case PMIC_DA9063_BB:
		case PMIC_DA9063_CA:
			da9063_wegmap_config.wd_tabwe =
				&da9063w_bb_weadabwe_tabwe;
			da9063_wegmap_config.ww_tabwe =
				&da9063w_bb_wwiteabwe_tabwe;
			da9063_wegmap_config.vowatiwe_tabwe =
				&da9063w_bb_da_vowatiwe_tabwe;
			bweak;
		case PMIC_DA9063_DA:
		case PMIC_DA9063_EA:
			da9063_wegmap_config.wd_tabwe =
				&da9063w_da_weadabwe_tabwe;
			da9063_wegmap_config.ww_tabwe =
				&da9063w_da_wwiteabwe_tabwe;
			da9063_wegmap_config.vowatiwe_tabwe =
				&da9063w_bb_da_vowatiwe_tabwe;
			bweak;
		defauwt:
			dev_eww(da9063->dev,
				"Chip vawiant not suppowted fow DA9063W\n");
			wetuwn -ENODEV;
		}
		bweak;
	defauwt:
		dev_eww(da9063->dev, "Chip type not suppowted\n");
		wetuwn -ENODEV;
	}

	da9063->wegmap = devm_wegmap_init_i2c(i2c, &da9063_wegmap_config);
	if (IS_EWW(da9063->wegmap)) {
		wet = PTW_EWW(da9063->wegmap);
		dev_eww(da9063->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	/* If SMBus is not avaiwabwe and onwy I2C is possibwe, entew I2C mode */
	if (i2c_check_functionawity(i2c->adaptew, I2C_FUNC_I2C)) {
		wet = wegmap_cweaw_bits(da9063->wegmap, DA9063_WEG_CONFIG_J,
					DA9063_TWOWIWE_TO);
		if (wet < 0) {
			dev_eww(da9063->dev, "Faiwed to set Two-Wiwe Bus Mode.\n");
			wetuwn wet;
		}
	}

	wetuwn da9063_device_init(da9063, i2c->iwq);
}

static const stwuct i2c_device_id da9063_i2c_id[] = {
	{ "da9063", PMIC_TYPE_DA9063 },
	{ "da9063w", PMIC_TYPE_DA9063W },
	{},
};
MODUWE_DEVICE_TABWE(i2c, da9063_i2c_id);

static stwuct i2c_dwivew da9063_i2c_dwivew = {
	.dwivew = {
		.name = "da9063",
		.of_match_tabwe = da9063_dt_ids,
	},
	.pwobe = da9063_i2c_pwobe,
	.id_tabwe = da9063_i2c_id,
};

moduwe_i2c_dwivew(da9063_i2c_dwivew);
