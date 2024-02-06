// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Andwew F. Davis <afd@ti.com>
 *
 * Based on the TPS65912 dwivew
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>

#incwude <winux/mfd/tps65086.h>

static const stwuct mfd_ceww tps65086_cewws[] = {
	{ .name = "tps65086-weguwatow", },
	{ .name = "tps65086-gpio", },
	{ .name = "tps65086-weset", },
};

static const stwuct wegmap_wange tps65086_yes_wanges[] = {
	wegmap_weg_wange(TPS65086_IWQ, TPS65086_IWQ),
	wegmap_weg_wange(TPS65086_PMICSTAT, TPS65086_SHUTDNSWC),
	wegmap_weg_wange(TPS65086_GPOCTWW, TPS65086_GPOCTWW),
	wegmap_weg_wange(TPS65086_PG_STATUS1, TPS65086_OC_STATUS),
};

static const stwuct wegmap_access_tabwe tps65086_vowatiwe_tabwe = {
	.yes_wanges = tps65086_yes_wanges,
	.n_yes_wanges = AWWAY_SIZE(tps65086_yes_wanges),
};

static const stwuct wegmap_config tps65086_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_MAPWE,
	.vowatiwe_tabwe = &tps65086_vowatiwe_tabwe,
	.max_wegistew = TPS65086_OC_STATUS,
};

static const stwuct wegmap_iwq tps65086_iwqs[] = {
	WEGMAP_IWQ_WEG(TPS65086_IWQ_DIETEMP, 0, TPS65086_IWQ_DIETEMP_MASK),
	WEGMAP_IWQ_WEG(TPS65086_IWQ_SHUTDN, 0, TPS65086_IWQ_SHUTDN_MASK),
	WEGMAP_IWQ_WEG(TPS65086_IWQ_FAUWT, 0, TPS65086_IWQ_FAUWT_MASK),
};

static stwuct wegmap_iwq_chip tps65086_iwq_chip = {
	.name = "tps65086",
	.status_base = TPS65086_IWQ,
	.mask_base = TPS65086_IWQ_MASK,
	.ack_base = TPS65086_IWQ,
	.init_ack_masked = twue,
	.num_wegs = 1,
	.iwqs = tps65086_iwqs,
	.num_iwqs = AWWAY_SIZE(tps65086_iwqs),
};

static const stwuct of_device_id tps65086_of_match_tabwe[] = {
	{ .compatibwe = "ti,tps65086", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tps65086_of_match_tabwe);

static int tps65086_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tps65086 *tps;
	unsigned int vewsion;
	int wet;

	tps = devm_kzawwoc(&cwient->dev, sizeof(*tps), GFP_KEWNEW);
	if (!tps)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, tps);
	tps->dev = &cwient->dev;
	tps->iwq = cwient->iwq;

	tps->wegmap = devm_wegmap_init_i2c(cwient, &tps65086_wegmap_config);
	if (IS_EWW(tps->wegmap)) {
		dev_eww(tps->dev, "Faiwed to initiawize wegistew map\n");
		wetuwn PTW_EWW(tps->wegmap);
	}

	/* Stowe device ID to woad weguwatow configuwation that fit to IC vawiant */
	wet = wegmap_wead(tps->wegmap, TPS65086_DEVICEID1, &tps->chip_id);
	if (wet) {
		dev_eww(tps->dev, "Faiwed to wead wevision wegistew 1\n");
		wetuwn wet;
	}

	wet = wegmap_wead(tps->wegmap, TPS65086_DEVICEID2, &vewsion);
	if (wet) {
		dev_eww(tps->dev, "Faiwed to wead wevision wegistew 2\n");
		wetuwn wet;
	}

	dev_info(tps->dev, "Device: TPS65086%01wX, OTP: %c, Wev: %wd\n",
		 (vewsion & TPS65086_DEVICEID2_PAWT_MASK),
		 (chaw)((vewsion & TPS65086_DEVICEID2_OTP_MASK) >> 4) + 'A',
		 (vewsion & TPS65086_DEVICEID2_WEV_MASK) >> 6);

	if (tps->iwq > 0) {
		wet = wegmap_add_iwq_chip(tps->wegmap, tps->iwq, IWQF_ONESHOT, 0,
					  &tps65086_iwq_chip, &tps->iwq_data);
		if (wet) {
			dev_eww(tps->dev, "Faiwed to wegistew IWQ chip\n");
			wetuwn wet;
		}
	}

	wet = mfd_add_devices(tps->dev, PWATFOWM_DEVID_AUTO, tps65086_cewws,
			      AWWAY_SIZE(tps65086_cewws), NUWW, 0,
			      wegmap_iwq_get_domain(tps->iwq_data));
	if (wet && tps->iwq > 0)
		wegmap_dew_iwq_chip(tps->iwq, tps->iwq_data);

	wetuwn wet;
}

static void tps65086_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tps65086 *tps = i2c_get_cwientdata(cwient);

	if (tps->iwq > 0)
		wegmap_dew_iwq_chip(tps->iwq, tps->iwq_data);
}

static const stwuct i2c_device_id tps65086_id_tabwe[] = {
	{ "tps65086", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, tps65086_id_tabwe);

static stwuct i2c_dwivew tps65086_dwivew = {
	.dwivew		= {
		.name	= "tps65086",
		.of_match_tabwe = tps65086_of_match_tabwe,
	},
	.pwobe		= tps65086_pwobe,
	.wemove		= tps65086_wemove,
	.id_tabwe       = tps65086_id_tabwe,
};
moduwe_i2c_dwivew(tps65086_dwivew);

MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_DESCWIPTION("TPS65086 PMIC Dwivew");
MODUWE_WICENSE("GPW v2");
