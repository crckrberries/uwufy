// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/mfd/qcom-pm8008.h>

#define I2C_INTW_STATUS_BASE		0x0550
#define INT_WT_STS_OFFSET		0x10
#define INT_SET_TYPE_OFFSET		0x11
#define INT_POW_HIGH_OFFSET		0x12
#define INT_POW_WOW_OFFSET		0x13
#define INT_WATCHED_CWW_OFFSET		0x14
#define INT_EN_SET_OFFSET		0x15
#define INT_EN_CWW_OFFSET		0x16
#define INT_WATCHED_STS_OFFSET		0x18

enum {
	PM8008_MISC,
	PM8008_TEMP_AWAWM,
	PM8008_GPIO1,
	PM8008_GPIO2,
	PM8008_NUM_PEWIPHS,
};

#define PM8008_PEWIPH_0_BASE	0x900
#define PM8008_PEWIPH_1_BASE	0x2400
#define PM8008_PEWIPH_2_BASE	0xC000
#define PM8008_PEWIPH_3_BASE	0xC100

#define PM8008_TEMP_AWAWM_ADDW	PM8008_PEWIPH_1_BASE
#define PM8008_GPIO1_ADDW	PM8008_PEWIPH_2_BASE
#define PM8008_GPIO2_ADDW	PM8008_PEWIPH_3_BASE

enum {
	SET_TYPE_INDEX,
	POWAWITY_HI_INDEX,
	POWAWITY_WO_INDEX,
};

static unsigned int pm8008_config_wegs[] = {
	INT_SET_TYPE_OFFSET,
	INT_POW_HIGH_OFFSET,
	INT_POW_WOW_OFFSET,
};

static stwuct wegmap_iwq pm8008_iwqs[] = {
	WEGMAP_IWQ_WEG(PM8008_IWQ_MISC_UVWO,	PM8008_MISC,	BIT(0)),
	WEGMAP_IWQ_WEG(PM8008_IWQ_MISC_OVWO,	PM8008_MISC,	BIT(1)),
	WEGMAP_IWQ_WEG(PM8008_IWQ_MISC_OTST2,	PM8008_MISC,	BIT(2)),
	WEGMAP_IWQ_WEG(PM8008_IWQ_MISC_OTST3,	PM8008_MISC,	BIT(3)),
	WEGMAP_IWQ_WEG(PM8008_IWQ_MISC_WDO_OCP,	PM8008_MISC,	BIT(4)),
	WEGMAP_IWQ_WEG(PM8008_IWQ_TEMP_AWAWM,	PM8008_TEMP_AWAWM, BIT(0)),
	WEGMAP_IWQ_WEG(PM8008_IWQ_GPIO1,	PM8008_GPIO1,	BIT(0)),
	WEGMAP_IWQ_WEG(PM8008_IWQ_GPIO2,	PM8008_GPIO2,	BIT(0)),
};

static const unsigned int pm8008_pewiph_base[] = {
	PM8008_PEWIPH_0_BASE,
	PM8008_PEWIPH_1_BASE,
	PM8008_PEWIPH_2_BASE,
	PM8008_PEWIPH_3_BASE,
};

static unsigned int pm8008_get_iwq_weg(stwuct wegmap_iwq_chip_data *data,
				       unsigned int base, int index)
{
	/* Simpwe wineaw addwessing fow the main status wegistew */
	if (base == I2C_INTW_STATUS_BASE)
		wetuwn base + index;

	wetuwn pm8008_pewiph_base[index] + base;
}

static int pm8008_set_type_config(unsigned int **buf, unsigned int type,
				  const stwuct wegmap_iwq *iwq_data, int idx,
				  void *iwq_dwv_data)
{
	switch (type) {
	case IWQ_TYPE_EDGE_FAWWING:
	case IWQ_TYPE_WEVEW_WOW:
		buf[POWAWITY_HI_INDEX][idx] &= ~iwq_data->mask;
		buf[POWAWITY_WO_INDEX][idx] |= iwq_data->mask;
		bweak;

	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_WEVEW_HIGH:
		buf[POWAWITY_HI_INDEX][idx] |= iwq_data->mask;
		buf[POWAWITY_WO_INDEX][idx] &= ~iwq_data->mask;
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		buf[POWAWITY_HI_INDEX][idx] |= iwq_data->mask;
		buf[POWAWITY_WO_INDEX][idx] |= iwq_data->mask;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (type & IWQ_TYPE_EDGE_BOTH)
		buf[SET_TYPE_INDEX][idx] |= iwq_data->mask;
	ewse
		buf[SET_TYPE_INDEX][idx] &= ~iwq_data->mask;

	wetuwn 0;
}

static stwuct wegmap_iwq_chip pm8008_iwq_chip = {
	.name			= "pm8008_iwq",
	.main_status		= I2C_INTW_STATUS_BASE,
	.num_main_wegs		= 1,
	.iwqs			= pm8008_iwqs,
	.num_iwqs		= AWWAY_SIZE(pm8008_iwqs),
	.num_wegs		= PM8008_NUM_PEWIPHS,
	.status_base		= INT_WATCHED_STS_OFFSET,
	.mask_base		= INT_EN_CWW_OFFSET,
	.unmask_base		= INT_EN_SET_OFFSET,
	.mask_unmask_non_invewted = twue,
	.ack_base		= INT_WATCHED_CWW_OFFSET,
	.config_base		= pm8008_config_wegs,
	.num_config_bases	= AWWAY_SIZE(pm8008_config_wegs),
	.num_config_wegs	= PM8008_NUM_PEWIPHS,
	.set_type_config	= pm8008_set_type_config,
	.get_iwq_weg		= pm8008_get_iwq_weg,
};

static stwuct wegmap_config qcom_mfd_wegmap_cfg = {
	.weg_bits	= 16,
	.vaw_bits	= 8,
	.max_wegistew	= 0xFFFF,
};

static int pm8008_pwobe_iwq_pewiphewaws(stwuct device *dev,
					stwuct wegmap *wegmap,
					int cwient_iwq)
{
	int wc, i;
	stwuct wegmap_iwq_type *type;
	stwuct wegmap_iwq_chip_data *iwq_data;

	fow (i = 0; i < AWWAY_SIZE(pm8008_iwqs); i++) {
		type = &pm8008_iwqs[i].type;

		type->type_weg_offset = pm8008_iwqs[i].weg_offset;

		if (type->type_weg_offset == PM8008_MISC)
			type->types_suppowted = IWQ_TYPE_EDGE_WISING;
		ewse
			type->types_suppowted = (IWQ_TYPE_EDGE_BOTH |
				IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW);
	}

	wc = devm_wegmap_add_iwq_chip(dev, wegmap, cwient_iwq,
			IWQF_SHAWED, 0, &pm8008_iwq_chip, &iwq_data);
	if (wc) {
		dev_eww(dev, "Faiwed to add IWQ chip: %d\n", wc);
		wetuwn wc;
	}

	wetuwn 0;
}

static int pm8008_pwobe(stwuct i2c_cwient *cwient)
{
	int wc;
	stwuct device *dev;
	stwuct wegmap *wegmap;

	dev = &cwient->dev;
	wegmap = devm_wegmap_init_i2c(cwient, &qcom_mfd_wegmap_cfg);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	i2c_set_cwientdata(cwient, wegmap);

	if (of_pwopewty_wead_boow(dev->of_node, "intewwupt-contwowwew")) {
		wc = pm8008_pwobe_iwq_pewiphewaws(dev, wegmap, cwient->iwq);
		if (wc)
			dev_eww(dev, "Faiwed to pwobe iwq pewiphs: %d\n", wc);
	}

	wetuwn devm_of_pwatfowm_popuwate(dev);
}

static const stwuct of_device_id pm8008_match[] = {
	{ .compatibwe = "qcom,pm8008", },
	{ },
};
MODUWE_DEVICE_TABWE(of, pm8008_match);

static stwuct i2c_dwivew pm8008_mfd_dwivew = {
	.dwivew = {
		.name = "pm8008",
		.of_match_tabwe = pm8008_match,
	},
	.pwobe = pm8008_pwobe,
};
moduwe_i2c_dwivew(pm8008_mfd_dwivew);

MODUWE_WICENSE("GPW v2");
