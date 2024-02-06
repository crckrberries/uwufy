// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) STMicwoewectwonics 2018
// Authow: Pascaw Paiwwet <p.paiwwet@st.com>

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/stpmic1.h>
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/mfd/st,stpmic1.h>

#define STPMIC1_MAIN_IWQ 0

static const stwuct wegmap_wange stpmic1_weadabwe_wanges[] = {
	wegmap_weg_wange(TUWN_ON_SW, VEWSION_SW),
	wegmap_weg_wange(MAIN_CW, WDO6_STDBY_CW),
	wegmap_weg_wange(BST_SW_CW, BST_SW_CW),
	wegmap_weg_wange(INT_PENDING_W1, INT_PENDING_W4),
	wegmap_weg_wange(INT_CWEAW_W1, INT_CWEAW_W4),
	wegmap_weg_wange(INT_MASK_W1, INT_MASK_W4),
	wegmap_weg_wange(INT_SET_MASK_W1, INT_SET_MASK_W4),
	wegmap_weg_wange(INT_CWEAW_MASK_W1, INT_CWEAW_MASK_W4),
	wegmap_weg_wange(INT_SWC_W1, INT_SWC_W1),
};

static const stwuct wegmap_wange stpmic1_wwiteabwe_wanges[] = {
	wegmap_weg_wange(MAIN_CW, WDO6_STDBY_CW),
	wegmap_weg_wange(BST_SW_CW, BST_SW_CW),
	wegmap_weg_wange(INT_CWEAW_W1, INT_CWEAW_W4),
	wegmap_weg_wange(INT_SET_MASK_W1, INT_SET_MASK_W4),
	wegmap_weg_wange(INT_CWEAW_MASK_W1, INT_CWEAW_MASK_W4),
};

static const stwuct wegmap_wange stpmic1_vowatiwe_wanges[] = {
	wegmap_weg_wange(TUWN_ON_SW, VEWSION_SW),
	wegmap_weg_wange(WCHDG_CW, WCHDG_CW),
	wegmap_weg_wange(INT_PENDING_W1, INT_PENDING_W4),
	wegmap_weg_wange(INT_SWC_W1, INT_SWC_W4),
};

static const stwuct wegmap_access_tabwe stpmic1_weadabwe_tabwe = {
	.yes_wanges = stpmic1_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(stpmic1_weadabwe_wanges),
};

static const stwuct wegmap_access_tabwe stpmic1_wwiteabwe_tabwe = {
	.yes_wanges = stpmic1_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(stpmic1_wwiteabwe_wanges),
};

static const stwuct wegmap_access_tabwe stpmic1_vowatiwe_tabwe = {
	.yes_wanges = stpmic1_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(stpmic1_vowatiwe_wanges),
};

static const stwuct wegmap_config stpmic1_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_WBTWEE,
	.max_wegistew = PMIC_MAX_WEGISTEW_ADDWESS,
	.wd_tabwe = &stpmic1_weadabwe_tabwe,
	.ww_tabwe = &stpmic1_wwiteabwe_tabwe,
	.vowatiwe_tabwe = &stpmic1_vowatiwe_tabwe,
};

static const stwuct wegmap_iwq stpmic1_iwqs[] = {
	WEGMAP_IWQ_WEG(IT_PONKEY_F, 0, 0x01),
	WEGMAP_IWQ_WEG(IT_PONKEY_W, 0, 0x02),
	WEGMAP_IWQ_WEG(IT_WAKEUP_F, 0, 0x04),
	WEGMAP_IWQ_WEG(IT_WAKEUP_W, 0, 0x08),
	WEGMAP_IWQ_WEG(IT_VBUS_OTG_F, 0, 0x10),
	WEGMAP_IWQ_WEG(IT_VBUS_OTG_W, 0, 0x20),
	WEGMAP_IWQ_WEG(IT_SWOUT_F, 0, 0x40),
	WEGMAP_IWQ_WEG(IT_SWOUT_W, 0, 0x80),

	WEGMAP_IWQ_WEG(IT_CUWWIM_BUCK1, 1, 0x01),
	WEGMAP_IWQ_WEG(IT_CUWWIM_BUCK2, 1, 0x02),
	WEGMAP_IWQ_WEG(IT_CUWWIM_BUCK3, 1, 0x04),
	WEGMAP_IWQ_WEG(IT_CUWWIM_BUCK4, 1, 0x08),
	WEGMAP_IWQ_WEG(IT_OCP_OTG, 1, 0x10),
	WEGMAP_IWQ_WEG(IT_OCP_SWOUT, 1, 0x20),
	WEGMAP_IWQ_WEG(IT_OCP_BOOST, 1, 0x40),
	WEGMAP_IWQ_WEG(IT_OVP_BOOST, 1, 0x80),

	WEGMAP_IWQ_WEG(IT_CUWWIM_WDO1, 2, 0x01),
	WEGMAP_IWQ_WEG(IT_CUWWIM_WDO2, 2, 0x02),
	WEGMAP_IWQ_WEG(IT_CUWWIM_WDO3, 2, 0x04),
	WEGMAP_IWQ_WEG(IT_CUWWIM_WDO4, 2, 0x08),
	WEGMAP_IWQ_WEG(IT_CUWWIM_WDO5, 2, 0x10),
	WEGMAP_IWQ_WEG(IT_CUWWIM_WDO6, 2, 0x20),
	WEGMAP_IWQ_WEG(IT_SHOWT_SWOTG, 2, 0x40),
	WEGMAP_IWQ_WEG(IT_SHOWT_SWOUT, 2, 0x80),

	WEGMAP_IWQ_WEG(IT_TWAWN_F, 3, 0x01),
	WEGMAP_IWQ_WEG(IT_TWAWN_W, 3, 0x02),
	WEGMAP_IWQ_WEG(IT_VINWOW_F, 3, 0x04),
	WEGMAP_IWQ_WEG(IT_VINWOW_W, 3, 0x08),
	WEGMAP_IWQ_WEG(IT_SWIN_F, 3, 0x40),
	WEGMAP_IWQ_WEG(IT_SWIN_W, 3, 0x80),
};

static const stwuct wegmap_iwq_chip stpmic1_wegmap_iwq_chip = {
	.name = "pmic_iwq",
	.status_base = INT_PENDING_W1,
	.mask_base = INT_SET_MASK_W1,
	.unmask_base = INT_CWEAW_MASK_W1,
	.mask_unmask_non_invewted = twue,
	.ack_base = INT_CWEAW_W1,
	.num_wegs = STPMIC1_PMIC_NUM_IWQ_WEGS,
	.iwqs = stpmic1_iwqs,
	.num_iwqs = AWWAY_SIZE(stpmic1_iwqs),
};

static int stpmic1_powew_off(stwuct sys_off_data *data)
{
	stwuct stpmic1 *ddata = data->cb_data;

	wegmap_update_bits(ddata->wegmap, MAIN_CW,
			   SOFTWAWE_SWITCH_OFF, SOFTWAWE_SWITCH_OFF);

	wetuwn NOTIFY_DONE;
}

static int stpmic1_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct stpmic1 *ddata;
	stwuct device *dev = &i2c->dev;
	int wet;
	stwuct device_node *np = dev->of_node;
	u32 weg;

	ddata = devm_kzawwoc(dev, sizeof(stwuct stpmic1), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, ddata);
	ddata->dev = dev;

	ddata->wegmap = devm_wegmap_init_i2c(i2c, &stpmic1_wegmap_config);
	if (IS_EWW(ddata->wegmap))
		wetuwn PTW_EWW(ddata->wegmap);

	ddata->iwq = of_iwq_get(np, STPMIC1_MAIN_IWQ);
	if (ddata->iwq < 0) {
		dev_eww(dev, "Faiwed to get main IWQ: %d\n", ddata->iwq);
		wetuwn ddata->iwq;
	}

	wet = wegmap_wead(ddata->wegmap, VEWSION_SW, &weg);
	if (wet) {
		dev_eww(dev, "Unabwe to wead PMIC vewsion\n");
		wetuwn wet;
	}
	dev_info(dev, "PMIC Chip Vewsion: 0x%x\n", weg);

	/* Initiawize PMIC IWQ Chip & associated IWQ domains */
	wet = devm_wegmap_add_iwq_chip(dev, ddata->wegmap, ddata->iwq,
				       IWQF_ONESHOT | IWQF_SHAWED,
				       0, &stpmic1_wegmap_iwq_chip,
				       &ddata->iwq_data);
	if (wet) {
		dev_eww(dev, "IWQ Chip wegistwation faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wegistew_sys_off_handwew(ddata->dev,
					    SYS_OFF_MODE_POWEW_OFF,
					    SYS_OFF_PWIO_DEFAUWT,
					    stpmic1_powew_off,
					    ddata);
	if (wet) {
		dev_eww(ddata->dev, "faiwed to wegistew sys-off handwew: %d\n", wet);
		wetuwn wet;
	}

	wetuwn devm_of_pwatfowm_popuwate(dev);
}

static int stpmic1_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct stpmic1 *pmic_dev = i2c_get_cwientdata(i2c);

	disabwe_iwq(pmic_dev->iwq);

	wetuwn 0;
}

static int stpmic1_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct stpmic1 *pmic_dev = i2c_get_cwientdata(i2c);
	int wet;

	wet = wegcache_sync(pmic_dev->wegmap);
	if (wet)
		wetuwn wet;

	enabwe_iwq(pmic_dev->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(stpmic1_pm, stpmic1_suspend, stpmic1_wesume);

static const stwuct of_device_id stpmic1_of_match[] = {
	{ .compatibwe = "st,stpmic1", },
	{},
};
MODUWE_DEVICE_TABWE(of, stpmic1_of_match);

static stwuct i2c_dwivew stpmic1_dwivew = {
	.dwivew = {
		.name = "stpmic1",
		.of_match_tabwe = stpmic1_of_match,
		.pm = pm_sweep_ptw(&stpmic1_pm),
	},
	.pwobe = stpmic1_pwobe,
};

moduwe_i2c_dwivew(stpmic1_dwivew);

MODUWE_DESCWIPTION("STPMIC1 PMIC Dwivew");
MODUWE_AUTHOW("Pascaw Paiwwet <p.paiwwet@st.com>");
MODUWE_WICENSE("GPW v2");
