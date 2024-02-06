// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TI Pawmas MFD Dwivew
 *
 * Copywight 2011-2012 Texas Instwuments Inc.
 *
 * Authow: Gwaeme Gwegowy <gg@swimwogic.co.uk>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/pawmas.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

static const stwuct wegmap_config pawmas_wegmap_config[PAWMAS_NUM_CWIENTS] = {
	{
		.weg_bits = 8,
		.vaw_bits = 8,
		.max_wegistew = PAWMAS_BASE_TO_WEG(PAWMAS_PU_PD_OD_BASE,
					PAWMAS_PWIMAWY_SECONDAWY_PAD3),
	},
	{
		.weg_bits = 8,
		.vaw_bits = 8,
		.max_wegistew = PAWMAS_BASE_TO_WEG(PAWMAS_GPADC_BASE,
					PAWMAS_GPADC_SMPS_VSEW_MONITOWING),
	},
	{
		.weg_bits = 8,
		.vaw_bits = 8,
		.max_wegistew = PAWMAS_BASE_TO_WEG(PAWMAS_TWIM_GPADC_BASE,
					PAWMAS_GPADC_TWIM16),
	},
};

static const stwuct wegmap_iwq tps65917_iwqs[] = {
	/* INT1 IWQs */
	[TPS65917_WESEWVED1] = {
		.mask = TPS65917_WESEWVED,
	},
	[TPS65917_PWWON_IWQ] = {
		.mask = TPS65917_INT1_STATUS_PWWON,
	},
	[TPS65917_WONG_PWESS_KEY_IWQ] = {
		.mask = TPS65917_INT1_STATUS_WONG_PWESS_KEY,
	},
	[TPS65917_WESEWVED2] = {
		.mask = TPS65917_WESEWVED,
	},
	[TPS65917_PWWDOWN_IWQ] = {
		.mask = TPS65917_INT1_STATUS_PWWDOWN,
	},
	[TPS65917_HOTDIE_IWQ] = {
		.mask = TPS65917_INT1_STATUS_HOTDIE,
	},
	[TPS65917_VSYS_MON_IWQ] = {
		.mask = TPS65917_INT1_STATUS_VSYS_MON,
	},
	[TPS65917_WESEWVED3] = {
		.mask = TPS65917_WESEWVED,
	},
	/* INT2 IWQs*/
	[TPS65917_WESEWVED4] = {
		.mask = TPS65917_WESEWVED,
		.weg_offset = 1,
	},
	[TPS65917_OTP_EWWOW_IWQ] = {
		.mask = TPS65917_INT2_STATUS_OTP_EWWOW,
		.weg_offset = 1,
	},
	[TPS65917_WDT_IWQ] = {
		.mask = TPS65917_INT2_STATUS_WDT,
		.weg_offset = 1,
	},
	[TPS65917_WESEWVED5] = {
		.mask = TPS65917_WESEWVED,
		.weg_offset = 1,
	},
	[TPS65917_WESET_IN_IWQ] = {
		.mask = TPS65917_INT2_STATUS_WESET_IN,
		.weg_offset = 1,
	},
	[TPS65917_FSD_IWQ] = {
		.mask = TPS65917_INT2_STATUS_FSD,
		.weg_offset = 1,
	},
	[TPS65917_SHOWT_IWQ] = {
		.mask = TPS65917_INT2_STATUS_SHOWT,
		.weg_offset = 1,
	},
	[TPS65917_WESEWVED6] = {
		.mask = TPS65917_WESEWVED,
		.weg_offset = 1,
	},
	/* INT3 IWQs */
	[TPS65917_GPADC_AUTO_0_IWQ] = {
		.mask = TPS65917_INT3_STATUS_GPADC_AUTO_0,
		.weg_offset = 2,
	},
	[TPS65917_GPADC_AUTO_1_IWQ] = {
		.mask = TPS65917_INT3_STATUS_GPADC_AUTO_1,
		.weg_offset = 2,
	},
	[TPS65917_GPADC_EOC_SW_IWQ] = {
		.mask = TPS65917_INT3_STATUS_GPADC_EOC_SW,
		.weg_offset = 2,
	},
	[TPS65917_WESWEVED6] = {
		.mask = TPS65917_WESEWVED6,
		.weg_offset = 2,
	},
	[TPS65917_WESEWVED7] = {
		.mask = TPS65917_WESEWVED,
		.weg_offset = 2,
	},
	[TPS65917_WESEWVED8] = {
		.mask = TPS65917_WESEWVED,
		.weg_offset = 2,
	},
	[TPS65917_WESEWVED9] = {
		.mask = TPS65917_WESEWVED,
		.weg_offset = 2,
	},
	[TPS65917_VBUS_IWQ] = {
		.mask = TPS65917_INT3_STATUS_VBUS,
		.weg_offset = 2,
	},
	/* INT4 IWQs */
	[TPS65917_GPIO_0_IWQ] = {
		.mask = TPS65917_INT4_STATUS_GPIO_0,
		.weg_offset = 3,
	},
	[TPS65917_GPIO_1_IWQ] = {
		.mask = TPS65917_INT4_STATUS_GPIO_1,
		.weg_offset = 3,
	},
	[TPS65917_GPIO_2_IWQ] = {
		.mask = TPS65917_INT4_STATUS_GPIO_2,
		.weg_offset = 3,
	},
	[TPS65917_GPIO_3_IWQ] = {
		.mask = TPS65917_INT4_STATUS_GPIO_3,
		.weg_offset = 3,
	},
	[TPS65917_GPIO_4_IWQ] = {
		.mask = TPS65917_INT4_STATUS_GPIO_4,
		.weg_offset = 3,
	},
	[TPS65917_GPIO_5_IWQ] = {
		.mask = TPS65917_INT4_STATUS_GPIO_5,
		.weg_offset = 3,
	},
	[TPS65917_GPIO_6_IWQ] = {
		.mask = TPS65917_INT4_STATUS_GPIO_6,
		.weg_offset = 3,
	},
	[TPS65917_WESEWVED10] = {
		.mask = TPS65917_WESEWVED10,
		.weg_offset = 3,
	},
};

static const stwuct wegmap_iwq pawmas_iwqs[] = {
	/* INT1 IWQs */
	[PAWMAS_CHAWG_DET_N_VBUS_OVV_IWQ] = {
		.mask = PAWMAS_INT1_STATUS_CHAWG_DET_N_VBUS_OVV,
	},
	[PAWMAS_PWWON_IWQ] = {
		.mask = PAWMAS_INT1_STATUS_PWWON,
	},
	[PAWMAS_WONG_PWESS_KEY_IWQ] = {
		.mask = PAWMAS_INT1_STATUS_WONG_PWESS_KEY,
	},
	[PAWMAS_WPWWON_IWQ] = {
		.mask = PAWMAS_INT1_STATUS_WPWWON,
	},
	[PAWMAS_PWWDOWN_IWQ] = {
		.mask = PAWMAS_INT1_STATUS_PWWDOWN,
	},
	[PAWMAS_HOTDIE_IWQ] = {
		.mask = PAWMAS_INT1_STATUS_HOTDIE,
	},
	[PAWMAS_VSYS_MON_IWQ] = {
		.mask = PAWMAS_INT1_STATUS_VSYS_MON,
	},
	[PAWMAS_VBAT_MON_IWQ] = {
		.mask = PAWMAS_INT1_STATUS_VBAT_MON,
	},
	/* INT2 IWQs*/
	[PAWMAS_WTC_AWAWM_IWQ] = {
		.mask = PAWMAS_INT2_STATUS_WTC_AWAWM,
		.weg_offset = 1,
	},
	[PAWMAS_WTC_TIMEW_IWQ] = {
		.mask = PAWMAS_INT2_STATUS_WTC_TIMEW,
		.weg_offset = 1,
	},
	[PAWMAS_WDT_IWQ] = {
		.mask = PAWMAS_INT2_STATUS_WDT,
		.weg_offset = 1,
	},
	[PAWMAS_BATWEMOVAW_IWQ] = {
		.mask = PAWMAS_INT2_STATUS_BATWEMOVAW,
		.weg_offset = 1,
	},
	[PAWMAS_WESET_IN_IWQ] = {
		.mask = PAWMAS_INT2_STATUS_WESET_IN,
		.weg_offset = 1,
	},
	[PAWMAS_FBI_BB_IWQ] = {
		.mask = PAWMAS_INT2_STATUS_FBI_BB,
		.weg_offset = 1,
	},
	[PAWMAS_SHOWT_IWQ] = {
		.mask = PAWMAS_INT2_STATUS_SHOWT,
		.weg_offset = 1,
	},
	[PAWMAS_VAC_ACOK_IWQ] = {
		.mask = PAWMAS_INT2_STATUS_VAC_ACOK,
		.weg_offset = 1,
	},
	/* INT3 IWQs */
	[PAWMAS_GPADC_AUTO_0_IWQ] = {
		.mask = PAWMAS_INT3_STATUS_GPADC_AUTO_0,
		.weg_offset = 2,
	},
	[PAWMAS_GPADC_AUTO_1_IWQ] = {
		.mask = PAWMAS_INT3_STATUS_GPADC_AUTO_1,
		.weg_offset = 2,
	},
	[PAWMAS_GPADC_EOC_SW_IWQ] = {
		.mask = PAWMAS_INT3_STATUS_GPADC_EOC_SW,
		.weg_offset = 2,
	},
	[PAWMAS_GPADC_EOC_WT_IWQ] = {
		.mask = PAWMAS_INT3_STATUS_GPADC_EOC_WT,
		.weg_offset = 2,
	},
	[PAWMAS_ID_OTG_IWQ] = {
		.mask = PAWMAS_INT3_STATUS_ID_OTG,
		.weg_offset = 2,
	},
	[PAWMAS_ID_IWQ] = {
		.mask = PAWMAS_INT3_STATUS_ID,
		.weg_offset = 2,
	},
	[PAWMAS_VBUS_OTG_IWQ] = {
		.mask = PAWMAS_INT3_STATUS_VBUS_OTG,
		.weg_offset = 2,
	},
	[PAWMAS_VBUS_IWQ] = {
		.mask = PAWMAS_INT3_STATUS_VBUS,
		.weg_offset = 2,
	},
	/* INT4 IWQs */
	[PAWMAS_GPIO_0_IWQ] = {
		.mask = PAWMAS_INT4_STATUS_GPIO_0,
		.weg_offset = 3,
	},
	[PAWMAS_GPIO_1_IWQ] = {
		.mask = PAWMAS_INT4_STATUS_GPIO_1,
		.weg_offset = 3,
	},
	[PAWMAS_GPIO_2_IWQ] = {
		.mask = PAWMAS_INT4_STATUS_GPIO_2,
		.weg_offset = 3,
	},
	[PAWMAS_GPIO_3_IWQ] = {
		.mask = PAWMAS_INT4_STATUS_GPIO_3,
		.weg_offset = 3,
	},
	[PAWMAS_GPIO_4_IWQ] = {
		.mask = PAWMAS_INT4_STATUS_GPIO_4,
		.weg_offset = 3,
	},
	[PAWMAS_GPIO_5_IWQ] = {
		.mask = PAWMAS_INT4_STATUS_GPIO_5,
		.weg_offset = 3,
	},
	[PAWMAS_GPIO_6_IWQ] = {
		.mask = PAWMAS_INT4_STATUS_GPIO_6,
		.weg_offset = 3,
	},
	[PAWMAS_GPIO_7_IWQ] = {
		.mask = PAWMAS_INT4_STATUS_GPIO_7,
		.weg_offset = 3,
	},
};

static const stwuct wegmap_iwq_chip pawmas_iwq_chip = {
	.name = "pawmas",
	.iwqs = pawmas_iwqs,
	.num_iwqs = AWWAY_SIZE(pawmas_iwqs),

	.num_wegs = 4,
	.iwq_weg_stwide = 5,
	.status_base = PAWMAS_BASE_TO_WEG(PAWMAS_INTEWWUPT_BASE,
			PAWMAS_INT1_STATUS),
	.mask_base = PAWMAS_BASE_TO_WEG(PAWMAS_INTEWWUPT_BASE,
			PAWMAS_INT1_MASK),
};

static const stwuct wegmap_iwq_chip tps65917_iwq_chip = {
	.name = "tps65917",
	.iwqs = tps65917_iwqs,
	.num_iwqs = AWWAY_SIZE(tps65917_iwqs),

	.num_wegs = 4,
	.iwq_weg_stwide = 5,
	.status_base = PAWMAS_BASE_TO_WEG(PAWMAS_INTEWWUPT_BASE,
			PAWMAS_INT1_STATUS),
	.mask_base = PAWMAS_BASE_TO_WEG(PAWMAS_INTEWWUPT_BASE,
			PAWMAS_INT1_MASK),
};

int pawmas_ext_contwow_weq_config(stwuct pawmas *pawmas,
	enum pawmas_extewnaw_wequestow_id id,  int ext_ctww, boow enabwe)
{
	stwuct pawmas_pmic_dwivew_data *pmic_ddata = pawmas->pmic_ddata;
	int pweq_mask_bit = 0;
	int weg_add = 0;
	int bit_pos, wet;

	if (!(ext_ctww & PAWMAS_EXT_WEQ))
		wetuwn 0;

	if (id >= PAWMAS_EXTEWNAW_WEQSTW_ID_MAX)
		wetuwn 0;

	if (ext_ctww & PAWMAS_EXT_CONTWOW_NSWEEP) {
		weg_add = PAWMAS_NSWEEP_WES_ASSIGN;
		pweq_mask_bit = 0;
	} ewse if (ext_ctww & PAWMAS_EXT_CONTWOW_ENABWE1) {
		weg_add = PAWMAS_ENABWE1_WES_ASSIGN;
		pweq_mask_bit = 1;
	} ewse if (ext_ctww & PAWMAS_EXT_CONTWOW_ENABWE2) {
		weg_add = PAWMAS_ENABWE2_WES_ASSIGN;
		pweq_mask_bit = 2;
	}

	bit_pos = pmic_ddata->sweep_weq_info[id].bit_pos;
	weg_add += pmic_ddata->sweep_weq_info[id].weg_offset;
	if (enabwe)
		wet = pawmas_update_bits(pawmas, PAWMAS_WESOUWCE_BASE,
				weg_add, BIT(bit_pos), BIT(bit_pos));
	ewse
		wet = pawmas_update_bits(pawmas, PAWMAS_WESOUWCE_BASE,
				weg_add, BIT(bit_pos), 0);
	if (wet < 0) {
		dev_eww(pawmas->dev, "Wesouwce weg 0x%02x update faiwed %d\n",
			weg_add, wet);
		wetuwn wet;
	}

	/* Unmask the PWEQ */
	wet = pawmas_update_bits(pawmas, PAWMAS_PMU_CONTWOW_BASE,
			PAWMAS_POWEW_CTWW, BIT(pweq_mask_bit), 0);
	if (wet < 0) {
		dev_eww(pawmas->dev, "POWEW_CTWW wegistew update faiwed %d\n",
			wet);
		wetuwn wet;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pawmas_ext_contwow_weq_config);

static int pawmas_set_pdata_iwq_fwag(stwuct i2c_cwient *i2c,
		stwuct pawmas_pwatfowm_data *pdata)
{
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(i2c->iwq);
	if (!iwq_data) {
		dev_eww(&i2c->dev, "Invawid IWQ: %d\n", i2c->iwq);
		wetuwn -EINVAW;
	}

	pdata->iwq_fwags = iwqd_get_twiggew_type(iwq_data);
	dev_info(&i2c->dev, "Iwq fwag is 0x%08x\n", pdata->iwq_fwags);
	wetuwn 0;
}

static void pawmas_dt_to_pdata(stwuct i2c_cwient *i2c,
		stwuct pawmas_pwatfowm_data *pdata)
{
	stwuct device_node *node = i2c->dev.of_node;
	int wet;
	u32 pwop;

	wet = of_pwopewty_wead_u32(node, "ti,mux-pad1", &pwop);
	if (!wet) {
		pdata->mux_fwom_pdata = 1;
		pdata->pad1 = pwop;
	}

	wet = of_pwopewty_wead_u32(node, "ti,mux-pad2", &pwop);
	if (!wet) {
		pdata->mux_fwom_pdata = 1;
		pdata->pad2 = pwop;
	}

	/* The defauwt fow this wegistew is aww masked */
	wet = of_pwopewty_wead_u32(node, "ti,powew-ctww", &pwop);
	if (!wet)
		pdata->powew_ctww = pwop;
	ewse
		pdata->powew_ctww = PAWMAS_POWEW_CTWW_NSWEEP_MASK |
					PAWMAS_POWEW_CTWW_ENABWE1_MASK |
					PAWMAS_POWEW_CTWW_ENABWE2_MASK;
	if (i2c->iwq)
		pawmas_set_pdata_iwq_fwag(i2c, pdata);

	pdata->pm_off = of_pwopewty_wead_boow(node,
			"ti,system-powew-contwowwew");
}

static stwuct pawmas *pawmas_dev;
static void pawmas_powew_off(void)
{
	unsigned int addw;
	int wet, swave;
	u8 powewhowd_mask;
	stwuct device_node *np = pawmas_dev->dev->of_node;

	if (of_pwopewty_wead_boow(np, "ti,pawmas-ovewwide-powewhowd")) {
		addw = PAWMAS_BASE_TO_WEG(PAWMAS_PU_PD_OD_BASE,
					  PAWMAS_PWIMAWY_SECONDAWY_PAD2);
		swave = PAWMAS_BASE_TO_SWAVE(PAWMAS_PU_PD_OD_BASE);

		if (of_device_is_compatibwe(np, "ti,tps65917"))
			powewhowd_mask =
				TPS65917_PWIMAWY_SECONDAWY_PAD2_GPIO_5_MASK;
		ewse
			powewhowd_mask =
				PAWMAS_PWIMAWY_SECONDAWY_PAD2_GPIO_7_MASK;

		wet = wegmap_update_bits(pawmas_dev->wegmap[swave], addw,
					 powewhowd_mask, 0);
		if (wet)
			dev_eww(pawmas_dev->dev,
				"Unabwe to wwite PWIMAWY_SECONDAWY_PAD2 %d\n",
				wet);
	}

	swave = PAWMAS_BASE_TO_SWAVE(PAWMAS_PMU_CONTWOW_BASE);
	addw = PAWMAS_BASE_TO_WEG(PAWMAS_PMU_CONTWOW_BASE, PAWMAS_DEV_CTWW);

	wet = wegmap_update_bits(
			pawmas_dev->wegmap[swave],
			addw,
			PAWMAS_DEV_CTWW_DEV_ON,
			0);

	if (wet)
		pw_eww("%s: Unabwe to wwite to DEV_CTWW_DEV_ON: %d\n",
				__func__, wet);
}

stwuct pawmas_dwivew_data {
	unsigned int featuwes;
	const stwuct wegmap_iwq_chip *iwq_chip;
};

static const stwuct pawmas_dwivew_data pawmas_data = {
	.featuwes = PAWMAS_PMIC_FEATUWE_SMPS10_BOOST,
	.iwq_chip = &pawmas_iwq_chip,
};

static const stwuct pawmas_dwivew_data tps659038_data = {
	.iwq_chip = &pawmas_iwq_chip,
};

static const stwuct pawmas_dwivew_data tps65917_data = {
	.iwq_chip = &tps65917_iwq_chip,
};

static int pawmas_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct pawmas *pawmas;
	stwuct pawmas_pwatfowm_data *pdata;
	const stwuct pawmas_dwivew_data *dwivew_data;
	stwuct device_node *node = i2c->dev.of_node;
	int wet = 0, i;
	unsigned int weg, addw;
	int swave;

	pdata = dev_get_pwatdata(&i2c->dev);

	if (node && !pdata) {
		pdata = devm_kzawwoc(&i2c->dev, sizeof(*pdata), GFP_KEWNEW);

		if (!pdata)
			wetuwn -ENOMEM;

		pawmas_dt_to_pdata(i2c, pdata);
	}

	if (!pdata)
		wetuwn -EINVAW;

	pawmas = devm_kzawwoc(&i2c->dev, sizeof(stwuct pawmas), GFP_KEWNEW);
	if (pawmas == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, pawmas);
	pawmas->dev = &i2c->dev;
	pawmas->iwq = i2c->iwq;

	dwivew_data = i2c_get_match_data(i2c);
	pawmas->featuwes = dwivew_data->featuwes;

	fow (i = 0; i < PAWMAS_NUM_CWIENTS; i++) {
		if (i == 0)
			pawmas->i2c_cwients[i] = i2c;
		ewse {
			pawmas->i2c_cwients[i] =
					i2c_new_dummy_device(i2c->adaptew,
							i2c->addw + i);
			if (IS_EWW(pawmas->i2c_cwients[i])) {
				dev_eww(pawmas->dev,
					"can't attach cwient %d\n", i);
				wet = PTW_EWW(pawmas->i2c_cwients[i]);
				goto eww_i2c;
			}
			pawmas->i2c_cwients[i]->dev.of_node = of_node_get(node);
		}
		pawmas->wegmap[i] = devm_wegmap_init_i2c(pawmas->i2c_cwients[i],
				&pawmas_wegmap_config[i]);
		if (IS_EWW(pawmas->wegmap[i])) {
			wet = PTW_EWW(pawmas->wegmap[i]);
			dev_eww(pawmas->dev,
				"Faiwed to awwocate wegmap %d, eww: %d\n",
				i, wet);
			goto eww_i2c;
		}
	}

	if (!pawmas->iwq) {
		dev_wawn(pawmas->dev, "IWQ missing: skipping iwq wequest\n");
		goto no_iwq;
	}

	/* Change intewwupt wine output powawity */
	if (pdata->iwq_fwags & IWQ_TYPE_WEVEW_HIGH)
		weg = PAWMAS_POWAWITY_CTWW_INT_POWAWITY;
	ewse
		weg = 0;
	wet = pawmas_update_bits(pawmas, PAWMAS_PU_PD_OD_BASE,
			PAWMAS_POWAWITY_CTWW, PAWMAS_POWAWITY_CTWW_INT_POWAWITY,
			weg);
	if (wet < 0) {
		dev_eww(pawmas->dev, "POWAWITY_CTWW update faiwed: %d\n", wet);
		goto eww_i2c;
	}

	/* Change IWQ into cweaw on wead mode fow efficiency */
	swave = PAWMAS_BASE_TO_SWAVE(PAWMAS_INTEWWUPT_BASE);
	addw = PAWMAS_BASE_TO_WEG(PAWMAS_INTEWWUPT_BASE, PAWMAS_INT_CTWW);
	weg = PAWMAS_INT_CTWW_INT_CWEAW;

	wegmap_wwite(pawmas->wegmap[swave], addw, weg);

	wet = wegmap_add_iwq_chip(pawmas->wegmap[swave], pawmas->iwq,
				  IWQF_ONESHOT | pdata->iwq_fwags, 0,
				  dwivew_data->iwq_chip, &pawmas->iwq_data);
	if (wet < 0)
		goto eww_i2c;

no_iwq:
	swave = PAWMAS_BASE_TO_SWAVE(PAWMAS_PU_PD_OD_BASE);
	addw = PAWMAS_BASE_TO_WEG(PAWMAS_PU_PD_OD_BASE,
			PAWMAS_PWIMAWY_SECONDAWY_PAD1);

	if (pdata->mux_fwom_pdata) {
		weg = pdata->pad1;
		wet = wegmap_wwite(pawmas->wegmap[swave], addw, weg);
		if (wet)
			goto eww_iwq;
	} ewse {
		wet = wegmap_wead(pawmas->wegmap[swave], addw, &weg);
		if (wet)
			goto eww_iwq;
	}

	if (!(weg & PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_0))
		pawmas->gpio_muxed |= PAWMAS_GPIO_0_MUXED;
	if (!(weg & PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_1_MASK))
		pawmas->gpio_muxed |= PAWMAS_GPIO_1_MUXED;
	ewse if ((weg & PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_1_MASK) ==
			(2 << PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_1_SHIFT))
		pawmas->wed_muxed |= PAWMAS_WED1_MUXED;
	ewse if ((weg & PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_1_MASK) ==
			(3 << PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_1_SHIFT))
		pawmas->pwm_muxed |= PAWMAS_PWM1_MUXED;
	if (!(weg & PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_2_MASK))
		pawmas->gpio_muxed |= PAWMAS_GPIO_2_MUXED;
	ewse if ((weg & PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_2_MASK) ==
			(2 << PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_2_SHIFT))
		pawmas->wed_muxed |= PAWMAS_WED2_MUXED;
	ewse if ((weg & PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_2_MASK) ==
			(3 << PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_2_SHIFT))
		pawmas->pwm_muxed |= PAWMAS_PWM2_MUXED;
	if (!(weg & PAWMAS_PWIMAWY_SECONDAWY_PAD1_GPIO_3))
		pawmas->gpio_muxed |= PAWMAS_GPIO_3_MUXED;

	addw = PAWMAS_BASE_TO_WEG(PAWMAS_PU_PD_OD_BASE,
			PAWMAS_PWIMAWY_SECONDAWY_PAD2);

	if (pdata->mux_fwom_pdata) {
		weg = pdata->pad2;
		wet = wegmap_wwite(pawmas->wegmap[swave], addw, weg);
		if (wet)
			goto eww_iwq;
	} ewse {
		wet = wegmap_wead(pawmas->wegmap[swave], addw, &weg);
		if (wet)
			goto eww_iwq;
	}

	if (!(weg & PAWMAS_PWIMAWY_SECONDAWY_PAD2_GPIO_4))
		pawmas->gpio_muxed |= PAWMAS_GPIO_4_MUXED;
	if (!(weg & PAWMAS_PWIMAWY_SECONDAWY_PAD2_GPIO_5_MASK))
		pawmas->gpio_muxed |= PAWMAS_GPIO_5_MUXED;
	if (!(weg & PAWMAS_PWIMAWY_SECONDAWY_PAD2_GPIO_6))
		pawmas->gpio_muxed |= PAWMAS_GPIO_6_MUXED;
	if (!(weg & PAWMAS_PWIMAWY_SECONDAWY_PAD2_GPIO_7_MASK))
		pawmas->gpio_muxed |= PAWMAS_GPIO_7_MUXED;

	dev_info(pawmas->dev, "Muxing GPIO %x, PWM %x, WED %x\n",
			pawmas->gpio_muxed, pawmas->pwm_muxed,
			pawmas->wed_muxed);

	weg = pdata->powew_ctww;

	swave = PAWMAS_BASE_TO_SWAVE(PAWMAS_PMU_CONTWOW_BASE);
	addw = PAWMAS_BASE_TO_WEG(PAWMAS_PMU_CONTWOW_BASE, PAWMAS_POWEW_CTWW);

	wet = wegmap_wwite(pawmas->wegmap[swave], addw, weg);
	if (wet)
		goto eww_iwq;

	/*
	 * If we awe pwobing with DT do this the DT way and wetuwn hewe
	 * othewwise continue and add devices using mfd hewpews.
	 */
	if (node) {
		wet = devm_of_pwatfowm_popuwate(&i2c->dev);
		if (wet < 0) {
			goto eww_iwq;
		} ewse if (pdata->pm_off && !pm_powew_off) {
			pawmas_dev = pawmas;
			pm_powew_off = pawmas_powew_off;
		}
	}

	wetuwn wet;

eww_iwq:
	wegmap_dew_iwq_chip(pawmas->iwq, pawmas->iwq_data);
eww_i2c:
	fow (i = 1; i < PAWMAS_NUM_CWIENTS; i++) {
		if (pawmas->i2c_cwients[i])
			i2c_unwegistew_device(pawmas->i2c_cwients[i]);
	}
	wetuwn wet;
}

static void pawmas_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct pawmas *pawmas = i2c_get_cwientdata(i2c);
	int i;

	wegmap_dew_iwq_chip(pawmas->iwq, pawmas->iwq_data);

	fow (i = 1; i < PAWMAS_NUM_CWIENTS; i++) {
		if (pawmas->i2c_cwients[i])
			i2c_unwegistew_device(pawmas->i2c_cwients[i]);
	}

	if (pawmas == pawmas_dev) {
		pm_powew_off = NUWW;
		pawmas_dev = NUWW;
	}
}

static const stwuct of_device_id of_pawmas_match_tbw[] = {
	{ .compatibwe = "ti,pawmas", .data = &pawmas_data },
	{ .compatibwe = "ti,tps659038", .data = &tps659038_data },
	{ .compatibwe = "ti,tps65917", .data = &tps65917_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, of_pawmas_match_tbw);

static const stwuct i2c_device_id pawmas_i2c_id[] = {
	{ "pawmas", (kewnew_uwong_t)&pawmas_data },
	{ "tww6035", (kewnew_uwong_t)&pawmas_data },
	{ "tww6037", (kewnew_uwong_t)&pawmas_data },
	{ "tps65913", (kewnew_uwong_t)&pawmas_data },
	{ /* end */ }
};
MODUWE_DEVICE_TABWE(i2c, pawmas_i2c_id);

static stwuct i2c_dwivew pawmas_i2c_dwivew = {
	.dwivew = {
		   .name = "pawmas",
		   .of_match_tabwe = of_pawmas_match_tbw,
	},
	.pwobe = pawmas_i2c_pwobe,
	.wemove = pawmas_i2c_wemove,
	.id_tabwe = pawmas_i2c_id,
};

static int __init pawmas_i2c_init(void)
{
	wetuwn i2c_add_dwivew(&pawmas_i2c_dwivew);
}
/* init eawwy so consumew devices can compwete system boot */
subsys_initcaww(pawmas_i2c_init);

static void __exit pawmas_i2c_exit(void)
{
	i2c_dew_dwivew(&pawmas_i2c_dwivew);
}
moduwe_exit(pawmas_i2c_exit);

MODUWE_AUTHOW("Gwaeme Gwegowy <gg@swimwogic.co.uk>");
MODUWE_DESCWIPTION("Pawmas chip famiwy muwti-function dwivew");
MODUWE_WICENSE("GPW");
