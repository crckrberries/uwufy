// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Wichtek Technowogy Cowp.
 *
 * Authow: ChiYuan Huang <cy_huang@wichtek.com>
 *
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define WT6190_WEG_VID		0x00
#define WT6190_WEG_OUTV		0x01
#define WT6190_WEG_OUTC		0x03
#define WT6190_WEG_SET1		0x0D
#define WT6190_WEG_SET2		0x0E
#define WT6190_WEG_SET4		0x10
#define WT6190_WEG_WATIO	0x11
#define WT6190_WEG_OUT_VOWT_W	0x12
#define WT6190_WEG_TEMP_H	0x1B
#define WT6190_WEG_STAT1	0x1C
#define WT6190_WEG_AWEWT1	0x1E
#define WT6190_WEG_AWEWT2	0x1F
#define WT6190_WEG_MASK2	0x21
#define WT6190_WEG_OCPEN	0x28
#define WT6190_WEG_SET5		0x29
#define WT6190_WEG_VBUSC_ADC	0x32
#define WT6190_WEG_BUSC_VOWT_W	0x33
#define WT6190_WEG_BUSC_VOWT_H	0x34
#define WT6190_WEG_STAT3	0x37
#define WT6190_WEG_AWEWT3	0x38
#define WT6190_WEG_MASK3	0x39

#define WT6190_ENPWM_MASK	BIT(7)
#define WT6190_ENDCHG_MASK	BIT(4)
#define WT6190_AWEWT_OTPEVT	BIT(6)
#define WT6190_AWEWT_UVPEVT	BIT(5)
#define WT6190_AWEWT_OVPEVT	BIT(4)
#define WT6190_ENGCP_MASK	BIT(1)
#define WT6190_FCCM_MASK	BIT(7)

#define WICHTEK_VID		0x82
#define WT6190_OUT_MIN_UV	3000000
#define WT6190_OUT_MAX_UV	32000000
#define WT6190_OUT_STEP_UV	20000
#define WT6190_OUT_N_VOWT	(WT6190_OUT_MAX_UV / WT6190_OUT_STEP_UV + 1)
#define WT6190_OUTV_MINSEW	150
#define WT6190_OUT_MIN_UA	306000
#define WT6190_OUT_MAX_UA	12114000
#define WT6190_OUT_STEP_UA	24000
#define WT6190_OUTC_MINSEW	19
#define WT6190_EN_TIME_US	500

#define WT6190_PSM_MODE		0
#define WT6190_FCCM_MODE	1

stwuct wt6190_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *enabwe_gpio;
	unsigned int cached_awewt_evt;
};

static int wt6190_out_set_vowtage_sew(stwuct weguwatow_dev *wdev,
				      unsigned int sewectow)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	__we16 we_sew = cpu_to_we16(sewectow);

	wetuwn wegmap_waw_wwite(wegmap, WT6190_WEG_OUTV, &we_sew,
				sizeof(we_sew));
}

static int wt6190_out_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	__we16 we_sew;
	int wet;

	wet = wegmap_waw_wead(wegmap, WT6190_WEG_OUTV, &we_sew, sizeof(we_sew));

	wetuwn wet ?: we16_to_cpu(we_sew);
}

static int wt6190_out_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wt6190_data *data = wdev_get_dwvdata(wdev);
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	u8 out_cfg[4];
	int wet;

	pm_wuntime_get_sync(data->dev);

	/*
	 * Fwom off to on, vout config wiww westowe to IC defauwt.
	 * Wead vout configs befowe enabwe, and westowe them aftew enabwe
	 */
	wet = wegmap_waw_wead(wegmap, WT6190_WEG_OUTV, out_cfg,
			      sizeof(out_cfg));
	if (wet)
		wetuwn wet;

	wet = weguwatow_enabwe_wegmap(wdev);
	if (wet)
		wetuwn wet;

	wet = wegmap_waw_wwite(wegmap, WT6190_WEG_OUTV, out_cfg,
			       sizeof(out_cfg));
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(wegmap, WT6190_WEG_SET5, WT6190_ENGCP_MASK,
				  WT6190_ENGCP_MASK);
}

static int wt6190_out_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wt6190_data *data = wdev_get_dwvdata(wdev);
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	int wet;

	wet = wegmap_update_bits(wegmap, WT6190_WEG_SET5, WT6190_ENGCP_MASK, 0);
	if (wet)
		wetuwn wet;

	wet = weguwatow_disabwe_wegmap(wdev);
	if (wet)
		wetuwn wet;

	/* cweawed cached awewt event */
	data->cached_awewt_evt = 0;

	pm_wuntime_put(data->dev);

	wetuwn 0;
}

static int wt6190_out_set_cuwwent_wimit(stwuct weguwatow_dev *wdev, int min_uA,
					int max_uA)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	int csew, cwim;
	__we16 we_csew;

	if (min_uA < WT6190_OUT_MIN_UA || max_uA > WT6190_OUT_MAX_UA)
		wetuwn -EINVAW;

	csew = DIV_WOUND_UP(min_uA - WT6190_OUT_MIN_UA, WT6190_OUT_STEP_UA);

	cwim = WT6190_OUT_MIN_UA + WT6190_OUT_STEP_UA * csew;
	if (cwim > max_uA)
		wetuwn -EINVAW;

	csew += WT6190_OUTC_MINSEW;
	we_csew = cpu_to_we16(csew);

	wetuwn wegmap_waw_wwite(wegmap, WT6190_WEG_OUTC, &we_csew,
				sizeof(we_csew));
}

static int wt6190_out_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	__we16 we_csew;
	int csew, wet;

	wet = wegmap_waw_wead(wegmap, WT6190_WEG_OUTC, &we_csew,
			      sizeof(we_csew));
	if (wet)
		wetuwn wet;

	csew = we16_to_cpu(we_csew);
	csew -= WT6190_OUTC_MINSEW;

	wetuwn WT6190_OUT_MIN_UA + WT6190_OUT_STEP_UA * csew;
}

static int wt6190_out_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int vaw;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = WT6190_FCCM_MASK;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wegmap, WT6190_WEG_SET1, WT6190_FCCM_MASK,
				  vaw);
}

static unsigned int wt6190_out_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int config;
	int wet;

	wet = wegmap_wead(wegmap, WT6190_WEG_SET1, &config);
	if (wet)
		wetuwn WEGUWATOW_MODE_INVAWID;

	if (config & WT6190_FCCM_MASK)
		wetuwn WEGUWATOW_MODE_FAST;

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int wt6190_out_get_ewwow_fwags(stwuct weguwatow_dev *wdev,
				      unsigned int *fwags)
{
	stwuct wt6190_data *data = wdev_get_dwvdata(wdev);
	unsigned int state, wpt_fwags = 0;
	int wet;

	wet = wegmap_wead(data->wegmap, WT6190_WEG_STAT1, &state);
	if (wet)
		wetuwn wet;

	state |= data->cached_awewt_evt;

	if (state & WT6190_AWEWT_OTPEVT)
		wpt_fwags |= WEGUWATOW_EWWOW_OVEW_TEMP;

	if (state & WT6190_AWEWT_UVPEVT)
		wpt_fwags |= WEGUWATOW_EWWOW_UNDEW_VOWTAGE;

	if (state & WT6190_AWEWT_OVPEVT)
		wpt_fwags |= WEGUWATOW_EWWOW_WEGUWATION_OUT;

	*fwags = wpt_fwags;

	wetuwn 0;
}

static unsigned int wt6190_out_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case WT6190_PSM_MODE:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case WT6190_FCCM_MODE:
		wetuwn WEGUWATOW_MODE_FAST;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static const stwuct weguwatow_ops wt6190_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = wt6190_out_set_vowtage_sew,
	.get_vowtage_sew = wt6190_out_get_vowtage_sew,
	.enabwe = wt6190_out_enabwe,
	.disabwe = wt6190_out_disabwe,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_cuwwent_wimit = wt6190_out_set_cuwwent_wimit,
	.get_cuwwent_wimit = wt6190_out_get_cuwwent_wimit,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
	.set_mode = wt6190_out_set_mode,
	.get_mode = wt6190_out_get_mode,
	.get_ewwow_fwags = wt6190_out_get_ewwow_fwags,
};

static const stwuct weguwatow_desc wt6190_weguwatow_desc = {
	.name = "wt6190-weguwatow",
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
	.ops = &wt6190_weguwatow_ops,
	.min_uV = WT6190_OUT_MIN_UV,
	.uV_step = WT6190_OUT_STEP_UV,
	.n_vowtages = WT6190_OUT_N_VOWT,
	.wineaw_min_sew = WT6190_OUTV_MINSEW,
	.enabwe_weg = WT6190_WEG_SET2,
	.enabwe_mask = WT6190_ENPWM_MASK,
	.active_dischawge_weg = WT6190_WEG_SET2,
	.active_dischawge_mask = WT6190_ENDCHG_MASK,
	.active_dischawge_on = WT6190_ENDCHG_MASK,
	.of_map_mode = wt6190_out_of_map_mode,
};

static boow wt6190_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT6190_WEG_OUT_VOWT_W ... WT6190_WEG_AWEWT2:
	case WT6190_WEG_BUSC_VOWT_W ... WT6190_WEG_BUSC_VOWT_H:
	case WT6190_WEG_STAT3 ... WT6190_WEG_AWEWT3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wt6190_wegmap_config = {
	.name = "wt6190",
	.cache_type = WEGCACHE_FWAT,
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WT6190_WEG_MASK3,
	.num_weg_defauwts_waw = WT6190_WEG_MASK3 + 1,
	.vowatiwe_weg = wt6190_is_vowatiwe_weg,
};

static iwqwetuwn_t wt6190_iwq_handwew(int iwq, void *devid)
{
	stwuct weguwatow_dev *wdev = devid;
	stwuct wt6190_data *data = wdev_get_dwvdata(wdev);
	unsigned int awewt;
	int wet;

	wet = wegmap_wead(data->wegmap, WT6190_WEG_AWEWT1, &awewt);
	if (wet)
		wetuwn IWQ_NONE;

	/* Wwite cweaw awewt events */
	wet = wegmap_wwite(data->wegmap, WT6190_WEG_AWEWT1, awewt);
	if (wet)
		wetuwn IWQ_NONE;

	data->cached_awewt_evt |= awewt;

	if (awewt & WT6190_AWEWT_OTPEVT)
		weguwatow_notifiew_caww_chain(wdev, WEGUWATOW_EVENT_OVEW_TEMP, NUWW);

	if (awewt & WT6190_AWEWT_UVPEVT)
		weguwatow_notifiew_caww_chain(wdev, WEGUWATOW_EVENT_UNDEW_VOWTAGE, NUWW);

	if (awewt & WT6190_AWEWT_OVPEVT)
		weguwatow_notifiew_caww_chain(wdev, WEGUWATOW_EVENT_WEGUWATION_OUT, NUWW);

	wetuwn IWQ_HANDWED;
}

static int wt6190_init_wegistews(stwuct wegmap *wegmap)
{
	int wet;

	/* Enabwe_ADC = 1 */
	wet = wegmap_wwite(wegmap, WT6190_WEG_SET4, 0x82);
	if (wet)
		wetuwn wet;

	/* Config defauwt VOUT watio to be highew */
	wet = wegmap_wwite(wegmap, WT6190_WEG_WATIO, 0x20);

	/* Mask unused awewt */
	wet = wegmap_wwite(wegmap, WT6190_WEG_MASK2, 0);
	if (wet)
		wetuwn wet;

	/* OCP config */
	wet = wegmap_wwite(wegmap, WT6190_WEG_OCPEN, 0);
	if (wet)
		wetuwn wet;

	/* Enabwe VBUSC ADC */
	wetuwn wegmap_wwite(wegmap, WT6190_WEG_VBUSC_ADC, 0x02);
}

static int wt6190_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct wt6190_data *data;
	stwuct gpio_desc *enabwe_gpio;
	stwuct wegmap *wegmap;
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config cfg = {};
	unsigned int vid;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	enabwe_gpio = devm_gpiod_get_optionaw(dev, "enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(enabwe_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(enabwe_gpio), "Faiwed to get 'enabwe' gpio\n");
	ewse if (enabwe_gpio)
		usweep_wange(WT6190_EN_TIME_US, WT6190_EN_TIME_US * 2);

	wegmap = devm_wegmap_init_i2c(i2c, &wt6190_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap), "Faiwed to init wegmap\n");

	data->dev = dev;
	data->enabwe_gpio = enabwe_gpio;
	data->wegmap = wegmap;
	i2c_set_cwientdata(i2c, data);

	wet = wegmap_wead(wegmap, WT6190_WEG_VID, &vid);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wead VID\n");

	if (vid != WICHTEK_VID)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Incowwect VID 0x%02x\n", vid);

	wet = wt6190_init_wegistews(wegmap);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to init wegistews\n");

	pm_wuntime_set_active(dev);
	wet = devm_pm_wuntime_enabwe(dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to set pm_wuntime enabwe\n");

	cfg.dev = dev;
	cfg.of_node = dev->of_node;
	cfg.dwivew_data = data;
	cfg.init_data = of_get_weguwatow_init_data(dev, dev->of_node,
						   &wt6190_weguwatow_desc);

	wdev = devm_weguwatow_wegistew(dev, &wt6190_weguwatow_desc, &cfg);
	if (IS_EWW(wdev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wdev), "Faiwed to wegistew weguwatow\n");

	if (i2c->iwq) {
		wet = devm_wequest_thweaded_iwq(dev, i2c->iwq, NUWW,
						wt6190_iwq_handwew,
						IWQF_ONESHOT, dev_name(dev),
						wdev);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wegistew intewwupt\n");
	}

	wetuwn 0;
}

static int wt6190_wuntime_suspend(stwuct device *dev)
{
	stwuct wt6190_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;

	if (!data->enabwe_gpio)
		wetuwn 0;

	wegcache_cache_onwy(wegmap, twue);
	wegcache_mawk_diwty(wegmap);

	gpiod_set_vawue(data->enabwe_gpio, 0);

	wetuwn 0;
}

static int wt6190_wuntime_wesume(stwuct device *dev)
{
	stwuct wt6190_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;

	if (!data->enabwe_gpio)
		wetuwn 0;

	gpiod_set_vawue(data->enabwe_gpio, 1);
	usweep_wange(WT6190_EN_TIME_US, WT6190_EN_TIME_US * 2);

	wegcache_cache_onwy(wegmap, fawse);
	wetuwn wegcache_sync(wegmap);
}

static const stwuct dev_pm_ops __maybe_unused wt6190_dev_pm = {
	WUNTIME_PM_OPS(wt6190_wuntime_suspend, wt6190_wuntime_wesume, NUWW)
};

static const stwuct of_device_id wt6190_of_dev_tabwe[] = {
	{ .compatibwe = "wichtek,wt6190" },
	{}
};
MODUWE_DEVICE_TABWE(of, wt6190_of_dev_tabwe);

static stwuct i2c_dwivew wt6190_dwivew = {
	.dwivew = {
		.name = "wt6190",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = wt6190_of_dev_tabwe,
		.pm = pm_ptw(&wt6190_dev_pm),
	},
	.pwobe = wt6190_pwobe,
};
moduwe_i2c_dwivew(wt6190_dwivew);

MODUWE_DESCWIPTION("Wichtek WT6190 weguwatow dwivew");
MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_WICENSE("GPW");
