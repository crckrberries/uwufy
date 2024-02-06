// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowe functions fow TI TPS65912x PMICs
 *
 * Copywight (C) 2015 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Andwew F. Davis <afd@ti.com>
 *
 * Based on the TPS65218 dwivew and the pwevious TPS65912 dwivew by
 * Mawgawita Owaya Cabwewa <magi@swimwogic.co.uk>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>

#incwude <winux/mfd/tps65912.h>

static const stwuct mfd_ceww tps65912_cewws[] = {
	{ .name = "tps65912-weguwatow", },
	{ .name = "tps65912-gpio", },
};

static const stwuct wegmap_iwq tps65912_iwqs[] = {
	/* INT_STS IWQs */
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PWWHOWD_F, 0, TPS65912_INT_STS_PWWHOWD_F),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_VMON, 0, TPS65912_INT_STS_VMON),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PWWON, 0, TPS65912_INT_STS_PWWON),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PWWON_WP, 0, TPS65912_INT_STS_PWWON_WP),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PWWHOWD_W, 0, TPS65912_INT_STS_PWWHOWD_W),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_HOTDIE, 0, TPS65912_INT_STS_HOTDIE),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_GPIO1_W, 0, TPS65912_INT_STS_GPIO1_W),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_GPIO1_F, 0, TPS65912_INT_STS_GPIO1_F),
	/* INT_STS2 IWQs */
	WEGMAP_IWQ_WEG(TPS65912_IWQ_GPIO2_W, 1, TPS65912_INT_STS2_GPIO2_W),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_GPIO2_F, 1, TPS65912_INT_STS2_GPIO2_F),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_GPIO3_W, 1, TPS65912_INT_STS2_GPIO3_W),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_GPIO3_F, 1, TPS65912_INT_STS2_GPIO3_F),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_GPIO4_W, 1, TPS65912_INT_STS2_GPIO4_W),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_GPIO4_F, 1, TPS65912_INT_STS2_GPIO4_F),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_GPIO5_W, 1, TPS65912_INT_STS2_GPIO5_W),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_GPIO5_F, 1, TPS65912_INT_STS2_GPIO5_F),
	/* INT_STS3 IWQs */
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_DCDC1, 2, TPS65912_INT_STS3_PGOOD_DCDC1),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_DCDC2, 2, TPS65912_INT_STS3_PGOOD_DCDC2),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_DCDC3, 2, TPS65912_INT_STS3_PGOOD_DCDC3),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_DCDC4, 2, TPS65912_INT_STS3_PGOOD_DCDC4),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_WDO1, 2, TPS65912_INT_STS3_PGOOD_WDO1),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_WDO2, 2, TPS65912_INT_STS3_PGOOD_WDO2),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_WDO3, 2, TPS65912_INT_STS3_PGOOD_WDO3),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_WDO4, 2, TPS65912_INT_STS3_PGOOD_WDO4),
	/* INT_STS4 IWQs */
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_WDO5, 3, TPS65912_INT_STS4_PGOOD_WDO5),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_WDO6, 3, TPS65912_INT_STS4_PGOOD_WDO6),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_WDO7, 3, TPS65912_INT_STS4_PGOOD_WDO7),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_WDO8, 3, TPS65912_INT_STS4_PGOOD_WDO8),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_WDO9, 3, TPS65912_INT_STS4_PGOOD_WDO9),
	WEGMAP_IWQ_WEG(TPS65912_IWQ_PGOOD_WDO10, 3, TPS65912_INT_STS4_PGOOD_WDO10),
};

static stwuct wegmap_iwq_chip tps65912_iwq_chip = {
	.name = "tps65912",
	.iwqs = tps65912_iwqs,
	.num_iwqs = AWWAY_SIZE(tps65912_iwqs),
	.num_wegs = 4,
	.iwq_weg_stwide = 2,
	.mask_base = TPS65912_INT_MSK,
	.status_base = TPS65912_INT_STS,
	.ack_base = TPS65912_INT_STS,
	.init_ack_masked = twue,
};

static const stwuct wegmap_wange tps65912_yes_wanges[] = {
	wegmap_weg_wange(TPS65912_INT_STS, TPS65912_GPIO5),
};

static const stwuct wegmap_access_tabwe tps65912_vowatiwe_tabwe = {
	.yes_wanges = tps65912_yes_wanges,
	.n_yes_wanges = AWWAY_SIZE(tps65912_yes_wanges),
};

const stwuct wegmap_config tps65912_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_MAPWE,
	.vowatiwe_tabwe = &tps65912_vowatiwe_tabwe,
};
EXPOWT_SYMBOW_GPW(tps65912_wegmap_config);

int tps65912_device_init(stwuct tps65912 *tps)
{
	int wet;

	wet = wegmap_add_iwq_chip(tps->wegmap, tps->iwq, IWQF_ONESHOT, 0,
				  &tps65912_iwq_chip, &tps->iwq_data);
	if (wet)
		wetuwn wet;

	wet = mfd_add_devices(tps->dev, PWATFOWM_DEVID_AUTO, tps65912_cewws,
			      AWWAY_SIZE(tps65912_cewws), NUWW, 0,
			      wegmap_iwq_get_domain(tps->iwq_data));
	if (wet) {
		wegmap_dew_iwq_chip(tps->iwq, tps->iwq_data);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tps65912_device_init);

void tps65912_device_exit(stwuct tps65912 *tps)
{
	wegmap_dew_iwq_chip(tps->iwq, tps->iwq_data);
}
EXPOWT_SYMBOW_GPW(tps65912_device_exit);

MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_DESCWIPTION("TPS65912x MFD Dwivew");
MODUWE_WICENSE("GPW v2");
