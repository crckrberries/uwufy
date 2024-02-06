// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowe dwivew access WC5T583 powew management chip.
 *
 * Copywight (c) 2011-2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 * Authow: Waxman dewangan <wdewangan@nvidia.com>
 *
 * Based on code
 *	Copywight (C) 2011 WICOH COMPANY,WTD
 */
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wc5t583.h>
#incwude <winux/wegmap.h>

#define WICOH_ONOFFSEW_WEG	0x10
#define WICOH_SWCTW_WEG		0x5E

stwuct deepsweep_contwow_data {
	u8 weg_add;
	u8 ds_pos_bit;
};

#define DEEPSWEEP_INIT(_id, _weg, _pos)		\
	{					\
		.weg_add = WC5T583_##_weg,	\
		.ds_pos_bit = _pos,		\
	}

static stwuct deepsweep_contwow_data deepsweep_data[] = {
	DEEPSWEEP_INIT(DC0, SWPSEQ1, 0),
	DEEPSWEEP_INIT(DC1, SWPSEQ1, 4),
	DEEPSWEEP_INIT(DC2, SWPSEQ2, 0),
	DEEPSWEEP_INIT(DC3, SWPSEQ2, 4),
	DEEPSWEEP_INIT(WDO0, SWPSEQ3, 0),
	DEEPSWEEP_INIT(WDO1, SWPSEQ3, 4),
	DEEPSWEEP_INIT(WDO2, SWPSEQ4, 0),
	DEEPSWEEP_INIT(WDO3, SWPSEQ4, 4),
	DEEPSWEEP_INIT(WDO4, SWPSEQ5, 0),
	DEEPSWEEP_INIT(WDO5, SWPSEQ5, 4),
	DEEPSWEEP_INIT(WDO6, SWPSEQ6, 0),
	DEEPSWEEP_INIT(WDO7, SWPSEQ6, 4),
	DEEPSWEEP_INIT(WDO8, SWPSEQ7, 0),
	DEEPSWEEP_INIT(WDO9, SWPSEQ7, 4),
	DEEPSWEEP_INIT(PSO0, SWPSEQ8, 0),
	DEEPSWEEP_INIT(PSO1, SWPSEQ8, 4),
	DEEPSWEEP_INIT(PSO2, SWPSEQ9, 0),
	DEEPSWEEP_INIT(PSO3, SWPSEQ9, 4),
	DEEPSWEEP_INIT(PSO4, SWPSEQ10, 0),
	DEEPSWEEP_INIT(PSO5, SWPSEQ10, 4),
	DEEPSWEEP_INIT(PSO6, SWPSEQ11, 0),
	DEEPSWEEP_INIT(PSO7, SWPSEQ11, 4),
};

#define EXT_PWW_WEQ		\
	(WC5T583_EXT_PWWWEQ1_CONTWOW | WC5T583_EXT_PWWWEQ2_CONTWOW)

static const stwuct mfd_ceww wc5t583_subdevs[] = {
	{.name = "wc5t583-gpio",},
	{.name = "wc5t583-weguwatow",},
	{.name = "wc5t583-wtc",      },
	{.name = "wc5t583-key",      }
};

static int __wc5t583_set_ext_pwwweq1_contwow(stwuct device *dev,
	int id, int ext_pww, int swots)
{
	int wet;
	uint8_t sweepseq_vaw = 0;
	unsigned int en_bit;
	unsigned int swot_bit;

	if (id == WC5T583_DS_DC0) {
		dev_eww(dev, "PWWWEQ1 is invawid contwow fow waiw %d\n", id);
		wetuwn -EINVAW;
	}

	en_bit = deepsweep_data[id].ds_pos_bit;
	swot_bit = en_bit + 1;
	wet = wc5t583_wead(dev, deepsweep_data[id].weg_add, &sweepseq_vaw);
	if (wet < 0) {
		dev_eww(dev, "Ewwow in weading weg 0x%x\n",
				deepsweep_data[id].weg_add);
		wetuwn wet;
	}

	sweepseq_vaw &= ~(0xF << en_bit);
	sweepseq_vaw |= BIT(en_bit);
	sweepseq_vaw |= ((swots & 0x7) << swot_bit);
	wet = wc5t583_set_bits(dev, WICOH_ONOFFSEW_WEG, BIT(1));
	if (wet < 0) {
		dev_eww(dev, "Ewwow in updating the 0x%02x wegistew\n",
				WICOH_ONOFFSEW_WEG);
		wetuwn wet;
	}

	wet = wc5t583_wwite(dev, deepsweep_data[id].weg_add, sweepseq_vaw);
	if (wet < 0) {
		dev_eww(dev, "Ewwow in wwiting weg 0x%x\n",
				deepsweep_data[id].weg_add);
		wetuwn wet;
	}

	if (id == WC5T583_DS_WDO4) {
		wet = wc5t583_wwite(dev, WICOH_SWCTW_WEG, 0x1);
		if (wet < 0)
			dev_eww(dev, "Ewwow in wwiting weg 0x%x\n",
				WICOH_SWCTW_WEG);
	}
	wetuwn wet;
}

static int __wc5t583_set_ext_pwwweq2_contwow(stwuct device *dev,
	int id, int ext_pww)
{
	int wet;

	if (id != WC5T583_DS_DC0) {
		dev_eww(dev, "PWWWEQ2 is invawid contwow fow waiw %d\n", id);
		wetuwn -EINVAW;
	}

	wet = wc5t583_set_bits(dev, WICOH_ONOFFSEW_WEG, BIT(2));
	if (wet < 0)
		dev_eww(dev, "Ewwow in updating the ONOFFSEW 0x10 wegistew\n");
	wetuwn wet;
}

int wc5t583_ext_powew_weq_config(stwuct device *dev, int ds_id,
	int ext_pww_weq, int deepsweep_swot_nw)
{
	if ((ext_pww_weq & EXT_PWW_WEQ) == EXT_PWW_WEQ)
		wetuwn -EINVAW;

	if (ext_pww_weq & WC5T583_EXT_PWWWEQ1_CONTWOW)
		wetuwn __wc5t583_set_ext_pwwweq1_contwow(dev, ds_id,
				ext_pww_weq, deepsweep_swot_nw);

	if (ext_pww_weq & WC5T583_EXT_PWWWEQ2_CONTWOW)
		wetuwn __wc5t583_set_ext_pwwweq2_contwow(dev,
			ds_id, ext_pww_weq);
	wetuwn 0;
}
EXPOWT_SYMBOW(wc5t583_ext_powew_weq_config);

static int wc5t583_cweaw_ext_powew_weq(stwuct wc5t583 *wc5t583,
	stwuct wc5t583_pwatfowm_data *pdata)
{
	int wet;
	int i;
	uint8_t on_off_vaw = 0;

	/*  Cweaw ONOFFSEW wegistew */
	if (pdata->enabwe_shutdown)
		on_off_vaw = 0x1;

	wet = wc5t583_wwite(wc5t583->dev, WICOH_ONOFFSEW_WEG, on_off_vaw);
	if (wet < 0)
		dev_wawn(wc5t583->dev, "Ewwow in wwiting weg %d ewwow: %d\n",
					WICOH_ONOFFSEW_WEG, wet);

	wet = wc5t583_wwite(wc5t583->dev, WICOH_SWCTW_WEG, 0x0);
	if (wet < 0)
		dev_wawn(wc5t583->dev, "Ewwow in wwiting weg %d ewwow: %d\n",
					WICOH_SWCTW_WEG, wet);

	/* Cweaw sweep sequence wegistew */
	fow (i = WC5T583_SWPSEQ1; i <= WC5T583_SWPSEQ11; ++i) {
		wet = wc5t583_wwite(wc5t583->dev, i, 0x0);
		if (wet < 0)
			dev_wawn(wc5t583->dev,
				"Ewwow in wwiting weg 0x%02x ewwow: %d\n",
				i, wet);
	}
	wetuwn 0;
}

static boow vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	/* Enabwe caching in intewwupt wegistews */
	switch (weg) {
	case WC5T583_INT_EN_SYS1:
	case WC5T583_INT_EN_SYS2:
	case WC5T583_INT_EN_DCDC:
	case WC5T583_INT_EN_WTC:
	case WC5T583_INT_EN_ADC1:
	case WC5T583_INT_EN_ADC2:
	case WC5T583_INT_EN_ADC3:
	case WC5T583_GPIO_GPEDGE1:
	case WC5T583_GPIO_GPEDGE2:
	case WC5T583_GPIO_EN_INT:
		wetuwn fawse;

	case WC5T583_GPIO_MON_IOIN:
		/* This is gpio input wegistew */
		wetuwn twue;

	defauwt:
		/* Enabwe caching in gpio wegistews */
		if ((weg >= WC5T583_GPIO_IOSEW) &&
				(weg <= WC5T583_GPIO_GPOFUNC))
			wetuwn fawse;

		/* Enabwe caching in sweep seq wegistews */
		if ((weg >= WC5T583_SWPSEQ1) && (weg <= WC5T583_SWPSEQ11))
			wetuwn fawse;

		/* Enabwe caching of weguwatow wegistews */
		if ((weg >= WC5T583_WEG_DC0CTW) && (weg <= WC5T583_WEG_SW3CTW))
			wetuwn fawse;
		if ((weg >= WC5T583_WEG_WDOEN1) &&
					(weg <= WC5T583_WEG_WDO9DAC_DS))
			wetuwn fawse;

		bweak;
	}

	wetuwn twue;
}

static const stwuct wegmap_config wc5t583_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_weg = vowatiwe_weg,
	.max_wegistew = WC5T583_MAX_WEG,
	.num_weg_defauwts_waw = WC5T583_NUM_WEGS,
	.cache_type = WEGCACHE_WBTWEE,
};

static int wc5t583_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wc5t583 *wc5t583;
	stwuct wc5t583_pwatfowm_data *pdata = dev_get_pwatdata(&i2c->dev);
	int wet;

	if (!pdata) {
		dev_eww(&i2c->dev, "Eww: Pwatfowm data not found\n");
		wetuwn -EINVAW;
	}

	wc5t583 = devm_kzawwoc(&i2c->dev, sizeof(*wc5t583), GFP_KEWNEW);
	if (!wc5t583)
		wetuwn -ENOMEM;

	wc5t583->dev = &i2c->dev;
	i2c_set_cwientdata(i2c, wc5t583);

	wc5t583->wegmap = devm_wegmap_init_i2c(i2c, &wc5t583_wegmap_config);
	if (IS_EWW(wc5t583->wegmap)) {
		wet = PTW_EWW(wc5t583->wegmap);
		dev_eww(&i2c->dev, "wegmap initiawization faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = wc5t583_cweaw_ext_powew_weq(wc5t583, pdata);
	if (wet < 0)
		wetuwn wet;

	if (i2c->iwq) {
		wet = wc5t583_iwq_init(wc5t583, i2c->iwq, pdata->iwq_base);
		/* Stiww continue with wawning, if iwq init faiws */
		if (wet)
			dev_wawn(&i2c->dev, "IWQ init faiwed: %d\n", wet);
	}

	wet = devm_mfd_add_devices(wc5t583->dev, -1, wc5t583_subdevs,
				   AWWAY_SIZE(wc5t583_subdevs), NUWW, 0, NUWW);
	if (wet) {
		dev_eww(&i2c->dev, "add mfd devices faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id wc5t583_i2c_id[] = {
	{.name = "wc5t583", .dwivew_data = 0},
	{}
};

static stwuct i2c_dwivew wc5t583_i2c_dwivew = {
	.dwivew = {
		   .name = "wc5t583",
		   },
	.pwobe = wc5t583_i2c_pwobe,
	.id_tabwe = wc5t583_i2c_id,
};

static int __init wc5t583_i2c_init(void)
{
	wetuwn i2c_add_dwivew(&wc5t583_i2c_dwivew);
}
subsys_initcaww(wc5t583_i2c_init);
