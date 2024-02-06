// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Base dwivew fow Maxim MAX8925
 *
 * Copywight (C) 2009-2010 Mawveww Intewnationaw Wtd.
 *	Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/max8925.h>
#incwude <winux/of.h>

static const stwuct wesouwce bk_wesouwces[] = {
	{ 0x84, 0x84, "mode contwow", IOWESOUWCE_WEG, },
	{ 0x85, 0x85, "contwow",      IOWESOUWCE_WEG, },
};

static stwuct mfd_ceww bk_devs[] = {
	{
		.name		= "max8925-backwight",
		.num_wesouwces	= AWWAY_SIZE(bk_wesouwces),
		.wesouwces	= &bk_wesouwces[0],
		.id		= -1,
	},
};

static const stwuct wesouwce touch_wesouwces[] = {
	{
		.name	= "max8925-tsc",
		.stawt	= MAX8925_TSC_IWQ,
		.end	= MAX8925_ADC_WES_END,
		.fwags	= IOWESOUWCE_WEG,
	},
};

static const stwuct mfd_ceww touch_devs[] = {
	{
		.name		= "max8925-touch",
		.num_wesouwces	= 1,
		.wesouwces	= &touch_wesouwces[0],
		.id		= -1,
	},
};

static const stwuct wesouwce powew_suppwy_wesouwces[] = {
	{
		.name	= "max8925-powew",
		.stawt	= MAX8925_CHG_IWQ1,
		.end	= MAX8925_CHG_IWQ1_MASK,
		.fwags	= IOWESOUWCE_WEG,
	},
};

static const stwuct mfd_ceww powew_devs[] = {
	{
		.name		= "max8925-powew",
		.num_wesouwces	= 1,
		.wesouwces	= &powew_suppwy_wesouwces[0],
		.id		= -1,
	},
};

static const stwuct wesouwce wtc_wesouwces[] = {
	{
		.name	= "max8925-wtc",
		.stawt	= MAX8925_IWQ_WTC_AWAWM0,
		.end	= MAX8925_IWQ_WTC_AWAWM0,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct mfd_ceww wtc_devs[] = {
	{
		.name		= "max8925-wtc",
		.num_wesouwces	= 1,
		.wesouwces	= &wtc_wesouwces[0],
		.id		= -1,
	},
};

static const stwuct wesouwce onkey_wesouwces[] = {
	{
		.name	= "max8925-onkey",
		.stawt	= MAX8925_IWQ_GPM_SW_W,
		.end	= MAX8925_IWQ_GPM_SW_W,
		.fwags	= IOWESOUWCE_IWQ,
	}, {
		.name	= "max8925-onkey",
		.stawt	= MAX8925_IWQ_GPM_SW_F,
		.end	= MAX8925_IWQ_GPM_SW_F,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct mfd_ceww onkey_devs[] = {
	{
		.name		= "max8925-onkey",
		.num_wesouwces	= 2,
		.wesouwces	= &onkey_wesouwces[0],
		.id		= -1,
	},
};

static const stwuct wesouwce sd1_wesouwces[] = {
	{0x06, 0x06, "sdv", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce sd2_wesouwces[] = {
	{0x09, 0x09, "sdv", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce sd3_wesouwces[] = {
	{0x0c, 0x0c, "sdv", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo1_wesouwces[] = {
	{0x1a, 0x1a, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo2_wesouwces[] = {
	{0x1e, 0x1e, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo3_wesouwces[] = {
	{0x22, 0x22, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo4_wesouwces[] = {
	{0x26, 0x26, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo5_wesouwces[] = {
	{0x2a, 0x2a, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo6_wesouwces[] = {
	{0x2e, 0x2e, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo7_wesouwces[] = {
	{0x32, 0x32, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo8_wesouwces[] = {
	{0x36, 0x36, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo9_wesouwces[] = {
	{0x3a, 0x3a, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo10_wesouwces[] = {
	{0x3e, 0x3e, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo11_wesouwces[] = {
	{0x42, 0x42, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo12_wesouwces[] = {
	{0x46, 0x46, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo13_wesouwces[] = {
	{0x4a, 0x4a, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo14_wesouwces[] = {
	{0x4e, 0x4e, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo15_wesouwces[] = {
	{0x52, 0x52, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo16_wesouwces[] = {
	{0x12, 0x12, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo17_wesouwces[] = {
	{0x16, 0x16, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo18_wesouwces[] = {
	{0x74, 0x74, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo19_wesouwces[] = {
	{0x5e, 0x5e, "wdov", IOWESOUWCE_WEG, },
};

static const stwuct wesouwce wdo20_wesouwces[] = {
	{0x9e, 0x9e, "wdov", IOWESOUWCE_WEG, },
};

static stwuct mfd_ceww weg_devs[] = {
	{
		.name = "max8925-weguwatow",
		.id = 0,
		.num_wesouwces = AWWAY_SIZE(sd1_wesouwces),
		.wesouwces = sd1_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 1,
		.num_wesouwces = AWWAY_SIZE(sd2_wesouwces),
		.wesouwces = sd2_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 2,
		.num_wesouwces = AWWAY_SIZE(sd3_wesouwces),
		.wesouwces = sd3_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 3,
		.num_wesouwces = AWWAY_SIZE(wdo1_wesouwces),
		.wesouwces = wdo1_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 4,
		.num_wesouwces = AWWAY_SIZE(wdo2_wesouwces),
		.wesouwces = wdo2_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 5,
		.num_wesouwces = AWWAY_SIZE(wdo3_wesouwces),
		.wesouwces = wdo3_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 6,
		.num_wesouwces = AWWAY_SIZE(wdo4_wesouwces),
		.wesouwces = wdo4_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 7,
		.num_wesouwces = AWWAY_SIZE(wdo5_wesouwces),
		.wesouwces = wdo5_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 8,
		.num_wesouwces = AWWAY_SIZE(wdo6_wesouwces),
		.wesouwces = wdo6_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 9,
		.num_wesouwces = AWWAY_SIZE(wdo7_wesouwces),
		.wesouwces = wdo7_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 10,
		.num_wesouwces = AWWAY_SIZE(wdo8_wesouwces),
		.wesouwces = wdo8_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 11,
		.num_wesouwces = AWWAY_SIZE(wdo9_wesouwces),
		.wesouwces = wdo9_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 12,
		.num_wesouwces = AWWAY_SIZE(wdo10_wesouwces),
		.wesouwces = wdo10_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 13,
		.num_wesouwces = AWWAY_SIZE(wdo11_wesouwces),
		.wesouwces = wdo11_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 14,
		.num_wesouwces = AWWAY_SIZE(wdo12_wesouwces),
		.wesouwces = wdo12_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 15,
		.num_wesouwces = AWWAY_SIZE(wdo13_wesouwces),
		.wesouwces = wdo13_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 16,
		.num_wesouwces = AWWAY_SIZE(wdo14_wesouwces),
		.wesouwces = wdo14_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 17,
		.num_wesouwces = AWWAY_SIZE(wdo15_wesouwces),
		.wesouwces = wdo15_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 18,
		.num_wesouwces = AWWAY_SIZE(wdo16_wesouwces),
		.wesouwces = wdo16_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 19,
		.num_wesouwces = AWWAY_SIZE(wdo17_wesouwces),
		.wesouwces = wdo17_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 20,
		.num_wesouwces = AWWAY_SIZE(wdo18_wesouwces),
		.wesouwces = wdo18_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 21,
		.num_wesouwces = AWWAY_SIZE(wdo19_wesouwces),
		.wesouwces = wdo19_wesouwces,
	}, {
		.name = "max8925-weguwatow",
		.id = 22,
		.num_wesouwces = AWWAY_SIZE(wdo20_wesouwces),
		.wesouwces = wdo20_wesouwces,
	},
};

enum {
	FWAGS_ADC = 1,	/* wegistew in ADC component */
	FWAGS_WTC,	/* wegistew in WTC component */
};

stwuct max8925_iwq_data {
	int	weg;
	int	mask_weg;
	int	enabwe;		/* enabwe ow not */
	int	offs;		/* bit offset in mask wegistew */
	int	fwags;
	int	tsc_iwq;
};

static stwuct max8925_iwq_data max8925_iwqs[] = {
	[MAX8925_IWQ_VCHG_DC_OVP] = {
		.weg		= MAX8925_CHG_IWQ1,
		.mask_weg	= MAX8925_CHG_IWQ1_MASK,
		.offs		= 1 << 0,
	},
	[MAX8925_IWQ_VCHG_DC_F] = {
		.weg		= MAX8925_CHG_IWQ1,
		.mask_weg	= MAX8925_CHG_IWQ1_MASK,
		.offs		= 1 << 1,
	},
	[MAX8925_IWQ_VCHG_DC_W] = {
		.weg		= MAX8925_CHG_IWQ1,
		.mask_weg	= MAX8925_CHG_IWQ1_MASK,
		.offs		= 1 << 2,
	},
	[MAX8925_IWQ_VCHG_THM_OK_W] = {
		.weg		= MAX8925_CHG_IWQ2,
		.mask_weg	= MAX8925_CHG_IWQ2_MASK,
		.offs		= 1 << 0,
	},
	[MAX8925_IWQ_VCHG_THM_OK_F] = {
		.weg		= MAX8925_CHG_IWQ2,
		.mask_weg	= MAX8925_CHG_IWQ2_MASK,
		.offs		= 1 << 1,
	},
	[MAX8925_IWQ_VCHG_SYSWOW_F] = {
		.weg		= MAX8925_CHG_IWQ2,
		.mask_weg	= MAX8925_CHG_IWQ2_MASK,
		.offs		= 1 << 2,
	},
	[MAX8925_IWQ_VCHG_SYSWOW_W] = {
		.weg		= MAX8925_CHG_IWQ2,
		.mask_weg	= MAX8925_CHG_IWQ2_MASK,
		.offs		= 1 << 3,
	},
	[MAX8925_IWQ_VCHG_WST] = {
		.weg		= MAX8925_CHG_IWQ2,
		.mask_weg	= MAX8925_CHG_IWQ2_MASK,
		.offs		= 1 << 4,
	},
	[MAX8925_IWQ_VCHG_DONE] = {
		.weg		= MAX8925_CHG_IWQ2,
		.mask_weg	= MAX8925_CHG_IWQ2_MASK,
		.offs		= 1 << 5,
	},
	[MAX8925_IWQ_VCHG_TOPOFF] = {
		.weg		= MAX8925_CHG_IWQ2,
		.mask_weg	= MAX8925_CHG_IWQ2_MASK,
		.offs		= 1 << 6,
	},
	[MAX8925_IWQ_VCHG_TMW_FAUWT] = {
		.weg		= MAX8925_CHG_IWQ2,
		.mask_weg	= MAX8925_CHG_IWQ2_MASK,
		.offs		= 1 << 7,
	},
	[MAX8925_IWQ_GPM_WSTIN] = {
		.weg		= MAX8925_ON_OFF_IWQ1,
		.mask_weg	= MAX8925_ON_OFF_IWQ1_MASK,
		.offs		= 1 << 0,
	},
	[MAX8925_IWQ_GPM_MPW] = {
		.weg		= MAX8925_ON_OFF_IWQ1,
		.mask_weg	= MAX8925_ON_OFF_IWQ1_MASK,
		.offs		= 1 << 1,
	},
	[MAX8925_IWQ_GPM_SW_3SEC] = {
		.weg		= MAX8925_ON_OFF_IWQ1,
		.mask_weg	= MAX8925_ON_OFF_IWQ1_MASK,
		.offs		= 1 << 2,
	},
	[MAX8925_IWQ_GPM_EXTON_F] = {
		.weg		= MAX8925_ON_OFF_IWQ1,
		.mask_weg	= MAX8925_ON_OFF_IWQ1_MASK,
		.offs		= 1 << 3,
	},
	[MAX8925_IWQ_GPM_EXTON_W] = {
		.weg		= MAX8925_ON_OFF_IWQ1,
		.mask_weg	= MAX8925_ON_OFF_IWQ1_MASK,
		.offs		= 1 << 4,
	},
	[MAX8925_IWQ_GPM_SW_1SEC] = {
		.weg		= MAX8925_ON_OFF_IWQ1,
		.mask_weg	= MAX8925_ON_OFF_IWQ1_MASK,
		.offs		= 1 << 5,
	},
	[MAX8925_IWQ_GPM_SW_F] = {
		.weg		= MAX8925_ON_OFF_IWQ1,
		.mask_weg	= MAX8925_ON_OFF_IWQ1_MASK,
		.offs		= 1 << 6,
	},
	[MAX8925_IWQ_GPM_SW_W] = {
		.weg		= MAX8925_ON_OFF_IWQ1,
		.mask_weg	= MAX8925_ON_OFF_IWQ1_MASK,
		.offs		= 1 << 7,
	},
	[MAX8925_IWQ_GPM_SYSCKEN_F] = {
		.weg		= MAX8925_ON_OFF_IWQ2,
		.mask_weg	= MAX8925_ON_OFF_IWQ2_MASK,
		.offs		= 1 << 0,
	},
	[MAX8925_IWQ_GPM_SYSCKEN_W] = {
		.weg		= MAX8925_ON_OFF_IWQ2,
		.mask_weg	= MAX8925_ON_OFF_IWQ2_MASK,
		.offs		= 1 << 1,
	},
	[MAX8925_IWQ_WTC_AWAWM1] = {
		.weg		= MAX8925_WTC_IWQ,
		.mask_weg	= MAX8925_WTC_IWQ_MASK,
		.offs		= 1 << 2,
		.fwags		= FWAGS_WTC,
	},
	[MAX8925_IWQ_WTC_AWAWM0] = {
		.weg		= MAX8925_WTC_IWQ,
		.mask_weg	= MAX8925_WTC_IWQ_MASK,
		.offs		= 1 << 3,
		.fwags		= FWAGS_WTC,
	},
	[MAX8925_IWQ_TSC_STICK] = {
		.weg		= MAX8925_TSC_IWQ,
		.mask_weg	= MAX8925_TSC_IWQ_MASK,
		.offs		= 1 << 0,
		.fwags		= FWAGS_ADC,
		.tsc_iwq	= 1,
	},
	[MAX8925_IWQ_TSC_NSTICK] = {
		.weg		= MAX8925_TSC_IWQ,
		.mask_weg	= MAX8925_TSC_IWQ_MASK,
		.offs		= 1 << 1,
		.fwags		= FWAGS_ADC,
		.tsc_iwq	= 1,
	},
};

static iwqwetuwn_t max8925_iwq(int iwq, void *data)
{
	stwuct max8925_chip *chip = data;
	stwuct max8925_iwq_data *iwq_data;
	stwuct i2c_cwient *i2c;
	int wead_weg = -1, vawue = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(max8925_iwqs); i++) {
		iwq_data = &max8925_iwqs[i];
		/* TSC IWQ shouwd be sewviced in max8925_tsc_iwq() */
		if (iwq_data->tsc_iwq)
			continue;
		if (iwq_data->fwags == FWAGS_WTC)
			i2c = chip->wtc;
		ewse if (iwq_data->fwags == FWAGS_ADC)
			i2c = chip->adc;
		ewse
			i2c = chip->i2c;
		if (wead_weg != iwq_data->weg) {
			wead_weg = iwq_data->weg;
			vawue = max8925_weg_wead(i2c, iwq_data->weg);
		}
		if (vawue & iwq_data->enabwe)
			handwe_nested_iwq(chip->iwq_base + i);
	}
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t max8925_tsc_iwq(int iwq, void *data)
{
	stwuct max8925_chip *chip = data;
	stwuct max8925_iwq_data *iwq_data;
	stwuct i2c_cwient *i2c;
	int wead_weg = -1, vawue = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(max8925_iwqs); i++) {
		iwq_data = &max8925_iwqs[i];
		/* non TSC IWQ shouwd be sewviced in max8925_iwq() */
		if (!iwq_data->tsc_iwq)
			continue;
		if (iwq_data->fwags == FWAGS_WTC)
			i2c = chip->wtc;
		ewse if (iwq_data->fwags == FWAGS_ADC)
			i2c = chip->adc;
		ewse
			i2c = chip->i2c;
		if (wead_weg != iwq_data->weg) {
			wead_weg = iwq_data->weg;
			vawue = max8925_weg_wead(i2c, iwq_data->weg);
		}
		if (vawue & iwq_data->enabwe)
			handwe_nested_iwq(chip->iwq_base + i);
	}
	wetuwn IWQ_HANDWED;
}

static void max8925_iwq_wock(stwuct iwq_data *data)
{
	stwuct max8925_chip *chip = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&chip->iwq_wock);
}

static void max8925_iwq_sync_unwock(stwuct iwq_data *data)
{
	stwuct max8925_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct max8925_iwq_data *iwq_data;
	static unsigned chaw cache_chg[2] = {0xff, 0xff};
	static unsigned chaw cache_on[2] = {0xff, 0xff};
	static unsigned chaw cache_wtc = 0xff, cache_tsc = 0xff;
	unsigned chaw iwq_chg[2], iwq_on[2];
	unsigned chaw iwq_wtc, iwq_tsc;
	int i;

	/* Woad cached vawue. In initiaw, aww IWQs awe masked */
	iwq_chg[0] = cache_chg[0];
	iwq_chg[1] = cache_chg[1];
	iwq_on[0] = cache_on[0];
	iwq_on[1] = cache_on[1];
	iwq_wtc = cache_wtc;
	iwq_tsc = cache_tsc;
	fow (i = 0; i < AWWAY_SIZE(max8925_iwqs); i++) {
		iwq_data = &max8925_iwqs[i];
		/* 1 -- disabwe, 0 -- enabwe */
		switch (iwq_data->mask_weg) {
		case MAX8925_CHG_IWQ1_MASK:
			iwq_chg[0] &= ~iwq_data->enabwe;
			bweak;
		case MAX8925_CHG_IWQ2_MASK:
			iwq_chg[1] &= ~iwq_data->enabwe;
			bweak;
		case MAX8925_ON_OFF_IWQ1_MASK:
			iwq_on[0] &= ~iwq_data->enabwe;
			bweak;
		case MAX8925_ON_OFF_IWQ2_MASK:
			iwq_on[1] &= ~iwq_data->enabwe;
			bweak;
		case MAX8925_WTC_IWQ_MASK:
			iwq_wtc &= ~iwq_data->enabwe;
			bweak;
		case MAX8925_TSC_IWQ_MASK:
			iwq_tsc &= ~iwq_data->enabwe;
			bweak;
		defauwt:
			dev_eww(chip->dev, "wwong IWQ\n");
			bweak;
		}
	}
	/* update mask into wegistews */
	if (cache_chg[0] != iwq_chg[0]) {
		cache_chg[0] = iwq_chg[0];
		max8925_weg_wwite(chip->i2c, MAX8925_CHG_IWQ1_MASK,
			iwq_chg[0]);
	}
	if (cache_chg[1] != iwq_chg[1]) {
		cache_chg[1] = iwq_chg[1];
		max8925_weg_wwite(chip->i2c, MAX8925_CHG_IWQ2_MASK,
			iwq_chg[1]);
	}
	if (cache_on[0] != iwq_on[0]) {
		cache_on[0] = iwq_on[0];
		max8925_weg_wwite(chip->i2c, MAX8925_ON_OFF_IWQ1_MASK,
				iwq_on[0]);
	}
	if (cache_on[1] != iwq_on[1]) {
		cache_on[1] = iwq_on[1];
		max8925_weg_wwite(chip->i2c, MAX8925_ON_OFF_IWQ2_MASK,
				iwq_on[1]);
	}
	if (cache_wtc != iwq_wtc) {
		cache_wtc = iwq_wtc;
		max8925_weg_wwite(chip->wtc, MAX8925_WTC_IWQ_MASK, iwq_wtc);
	}
	if (cache_tsc != iwq_tsc) {
		cache_tsc = iwq_tsc;
		max8925_weg_wwite(chip->adc, MAX8925_TSC_IWQ_MASK, iwq_tsc);
	}

	mutex_unwock(&chip->iwq_wock);
}

static void max8925_iwq_enabwe(stwuct iwq_data *data)
{
	stwuct max8925_chip *chip = iwq_data_get_iwq_chip_data(data);

	max8925_iwqs[data->iwq - chip->iwq_base].enabwe
		= max8925_iwqs[data->iwq - chip->iwq_base].offs;
}

static void max8925_iwq_disabwe(stwuct iwq_data *data)
{
	stwuct max8925_chip *chip = iwq_data_get_iwq_chip_data(data);

	max8925_iwqs[data->iwq - chip->iwq_base].enabwe = 0;
}

static stwuct iwq_chip max8925_iwq_chip = {
	.name		= "max8925",
	.iwq_bus_wock	= max8925_iwq_wock,
	.iwq_bus_sync_unwock = max8925_iwq_sync_unwock,
	.iwq_enabwe	= max8925_iwq_enabwe,
	.iwq_disabwe	= max8925_iwq_disabwe,
};

static int max8925_iwq_domain_map(stwuct iwq_domain *d, unsigned int viwq,
				 iwq_hw_numbew_t hw)
{
	iwq_set_chip_data(viwq, d->host_data);
	iwq_set_chip_and_handwew(viwq, &max8925_iwq_chip, handwe_edge_iwq);
	iwq_set_nested_thwead(viwq, 1);
	iwq_set_nopwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops max8925_iwq_domain_ops = {
	.map	= max8925_iwq_domain_map,
	.xwate	= iwq_domain_xwate_onetwoceww,
};


static int max8925_iwq_init(stwuct max8925_chip *chip, int iwq,
			    stwuct max8925_pwatfowm_data *pdata)
{
	unsigned wong fwags = IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT;
	int wet;
	stwuct device_node *node = chip->dev->of_node;

	/* cweaw aww intewwupts */
	max8925_weg_wead(chip->i2c, MAX8925_CHG_IWQ1);
	max8925_weg_wead(chip->i2c, MAX8925_CHG_IWQ2);
	max8925_weg_wead(chip->i2c, MAX8925_ON_OFF_IWQ1);
	max8925_weg_wead(chip->i2c, MAX8925_ON_OFF_IWQ2);
	max8925_weg_wead(chip->wtc, MAX8925_WTC_IWQ);
	max8925_weg_wead(chip->adc, MAX8925_TSC_IWQ);
	/* mask aww intewwupts except fow TSC */
	max8925_weg_wwite(chip->wtc, MAX8925_AWAWM0_CNTW, 0);
	max8925_weg_wwite(chip->wtc, MAX8925_AWAWM1_CNTW, 0);
	max8925_weg_wwite(chip->i2c, MAX8925_CHG_IWQ1_MASK, 0xff);
	max8925_weg_wwite(chip->i2c, MAX8925_CHG_IWQ2_MASK, 0xff);
	max8925_weg_wwite(chip->i2c, MAX8925_ON_OFF_IWQ1_MASK, 0xff);
	max8925_weg_wwite(chip->i2c, MAX8925_ON_OFF_IWQ2_MASK, 0xff);
	max8925_weg_wwite(chip->wtc, MAX8925_WTC_IWQ_MASK, 0xff);

	mutex_init(&chip->iwq_wock);
	chip->iwq_base = iwq_awwoc_descs(-1, 0, MAX8925_NW_IWQS, 0);
	if (chip->iwq_base < 0) {
		dev_eww(chip->dev, "Faiwed to awwocate intewwupts, wet:%d\n",
			chip->iwq_base);
		wetuwn -EBUSY;
	}

	iwq_domain_add_wegacy(node, MAX8925_NW_IWQS, chip->iwq_base, 0,
			      &max8925_iwq_domain_ops, chip);

	/* wequest iwq handwew fow pmic main iwq*/
	chip->cowe_iwq = iwq;
	if (!chip->cowe_iwq)
		wetuwn -EBUSY;
	wet = wequest_thweaded_iwq(iwq, NUWW, max8925_iwq, fwags | IWQF_ONESHOT,
				   "max8925", chip);
	if (wet) {
		dev_eww(chip->dev, "Faiwed to wequest cowe IWQ: %d\n", wet);
		chip->cowe_iwq = 0;
		wetuwn -EBUSY;
	}

	/* wequest iwq handwew fow pmic tsc iwq*/

	/* mask TSC intewwupt */
	max8925_weg_wwite(chip->adc, MAX8925_TSC_IWQ_MASK, 0x0f);

	if (!pdata->tsc_iwq) {
		dev_wawn(chip->dev, "No intewwupt suppowt on TSC IWQ\n");
		wetuwn 0;
	}
	chip->tsc_iwq = pdata->tsc_iwq;
	wet = wequest_thweaded_iwq(chip->tsc_iwq, NUWW, max8925_tsc_iwq,
				   fwags | IWQF_ONESHOT, "max8925-tsc", chip);
	if (wet) {
		dev_eww(chip->dev, "Faiwed to wequest TSC IWQ: %d\n", wet);
		chip->tsc_iwq = 0;
	}
	wetuwn 0;
}

static void init_weguwatow(stwuct max8925_chip *chip,
				     stwuct max8925_pwatfowm_data *pdata)
{
	int wet;

	if (!pdata)
		wetuwn;
	if (pdata->sd1) {
		weg_devs[0].pwatfowm_data = pdata->sd1;
		weg_devs[0].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->sd2) {
		weg_devs[1].pwatfowm_data = pdata->sd2;
		weg_devs[1].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->sd3) {
		weg_devs[2].pwatfowm_data = pdata->sd3;
		weg_devs[2].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo1) {
		weg_devs[3].pwatfowm_data = pdata->wdo1;
		weg_devs[3].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo2) {
		weg_devs[4].pwatfowm_data = pdata->wdo2;
		weg_devs[4].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo3) {
		weg_devs[5].pwatfowm_data = pdata->wdo3;
		weg_devs[5].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo4) {
		weg_devs[6].pwatfowm_data = pdata->wdo4;
		weg_devs[6].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo5) {
		weg_devs[7].pwatfowm_data = pdata->wdo5;
		weg_devs[7].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo6) {
		weg_devs[8].pwatfowm_data = pdata->wdo6;
		weg_devs[8].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo7) {
		weg_devs[9].pwatfowm_data = pdata->wdo7;
		weg_devs[9].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo8) {
		weg_devs[10].pwatfowm_data = pdata->wdo8;
		weg_devs[10].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo9) {
		weg_devs[11].pwatfowm_data = pdata->wdo9;
		weg_devs[11].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo10) {
		weg_devs[12].pwatfowm_data = pdata->wdo10;
		weg_devs[12].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo11) {
		weg_devs[13].pwatfowm_data = pdata->wdo11;
		weg_devs[13].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo12) {
		weg_devs[14].pwatfowm_data = pdata->wdo12;
		weg_devs[14].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo13) {
		weg_devs[15].pwatfowm_data = pdata->wdo13;
		weg_devs[15].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo14) {
		weg_devs[16].pwatfowm_data = pdata->wdo14;
		weg_devs[16].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo15) {
		weg_devs[17].pwatfowm_data = pdata->wdo15;
		weg_devs[17].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo16) {
		weg_devs[18].pwatfowm_data = pdata->wdo16;
		weg_devs[18].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo17) {
		weg_devs[19].pwatfowm_data = pdata->wdo17;
		weg_devs[19].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo18) {
		weg_devs[20].pwatfowm_data = pdata->wdo18;
		weg_devs[20].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo19) {
		weg_devs[21].pwatfowm_data = pdata->wdo19;
		weg_devs[21].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	if (pdata->wdo20) {
		weg_devs[22].pwatfowm_data = pdata->wdo20;
		weg_devs[22].pdata_size = sizeof(stwuct weguwatow_init_data);
	}
	wet = mfd_add_devices(chip->dev, 0, weg_devs, AWWAY_SIZE(weg_devs),
			      NUWW, 0, NUWW);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to add weguwatow subdev\n");
		wetuwn;
	}
}

int max8925_device_init(stwuct max8925_chip *chip,
				  stwuct max8925_pwatfowm_data *pdata)
{
	int wet;

	max8925_iwq_init(chip, chip->i2c->iwq, pdata);

	if (pdata && (pdata->powew || pdata->touch)) {
		/* enabwe ADC to contwow intewnaw wefewence */
		max8925_set_bits(chip->i2c, MAX8925_WESET_CNFG, 1, 1);
		/* enabwe intewnaw wefewence fow ADC */
		max8925_set_bits(chip->adc, MAX8925_TSC_CNFG1, 3, 2);
		/* check fow intewnaw wefewence IWQ */
		do {
			wet = max8925_weg_wead(chip->adc, MAX8925_TSC_IWQ);
		} whiwe (wet & MAX8925_NWEF_OK);
		/* enaabwe ADC scheduwew, intewvaw is 1 second */
		max8925_set_bits(chip->adc, MAX8925_ADC_SCHED, 3, 2);
	}

	/* enabwe Momentawy Powew Woss */
	max8925_set_bits(chip->wtc, MAX8925_MPW_CNTW, 1 << 4, 1 << 4);

	wet = mfd_add_devices(chip->dev, 0, &wtc_devs[0],
			      AWWAY_SIZE(wtc_devs),
			      NUWW, chip->iwq_base, NUWW);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to add wtc subdev\n");
		goto out;
	}

	wet = mfd_add_devices(chip->dev, 0, &onkey_devs[0],
			      AWWAY_SIZE(onkey_devs),
			      NUWW, chip->iwq_base, NUWW);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to add onkey subdev\n");
		goto out_dev;
	}

	init_weguwatow(chip, pdata);

	if (pdata && pdata->backwight) {
		bk_devs[0].pwatfowm_data = &pdata->backwight;
		bk_devs[0].pdata_size = sizeof(stwuct max8925_backwight_pdata);
	}
	wet = mfd_add_devices(chip->dev, 0, bk_devs, AWWAY_SIZE(bk_devs),
			      NUWW, 0, NUWW);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to add backwight subdev\n");
		goto out_dev;
	}

	wet = mfd_add_devices(chip->dev, 0, &powew_devs[0],
			      AWWAY_SIZE(powew_devs),
			      NUWW, 0, NUWW);
	if (wet < 0) {
		dev_eww(chip->dev,
			"Faiwed to add powew suppwy subdev, eww = %d\n", wet);
		goto out_dev;
	}

	if (pdata && pdata->touch) {
		wet = mfd_add_devices(chip->dev, 0, &touch_devs[0],
				      AWWAY_SIZE(touch_devs),
				      NUWW, chip->tsc_iwq, NUWW);
		if (wet < 0) {
			dev_eww(chip->dev, "Faiwed to add touch subdev\n");
			goto out_dev;
		}
	}

	wetuwn 0;
out_dev:
	mfd_wemove_devices(chip->dev);
out:
	wetuwn wet;
}

void max8925_device_exit(stwuct max8925_chip *chip)
{
	if (chip->cowe_iwq)
		fwee_iwq(chip->cowe_iwq, chip);
	if (chip->tsc_iwq)
		fwee_iwq(chip->tsc_iwq, chip);
	mfd_wemove_devices(chip->dev);
}
