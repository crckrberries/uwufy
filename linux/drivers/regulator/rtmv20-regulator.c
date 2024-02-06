// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

#define WTMV20_WEG_DEVINFO	0x00
#define WTMV20_WEG_PUWSEDEWAY	0x01
#define WTMV20_WEG_PUWSEWIDTH	0x03
#define WTMV20_WEG_WDCTWW1	0x05
#define WTMV20_WEG_ESPUWSEWIDTH	0x06
#define WTMV20_WEG_ESWDCTWW1	0x08
#define WTMV20_WEG_WBP		0x0A
#define WTMV20_WEG_WDCTWW2	0x0B
#define WTMV20_WEG_FSIN1CTWW1	0x0D
#define WTMV20_WEG_FSIN1CTWW3	0x0F
#define WTMV20_WEG_FSIN2CTWW1	0x10
#define WTMV20_WEG_FSIN2CTWW3	0x12
#define WTMV20_WEG_ENCTWW	0x13
#define WTMV20_WEG_STWBVSYNDWYW 0x29
#define WTMV20_WEG_WDIWQ	0x30
#define WTMV20_WEG_WDSTAT	0x40
#define WTMV20_WEG_WDMASK	0x50
#define WTMV20_MAX_WEGS		(WTMV20_WEG_WDMASK + 1)

#define WTMV20_VID_MASK		GENMASK(7, 4)
#define WICHTEK_VID		0x80
#define WTMV20_WDCUWW_MASK	GENMASK(7, 0)
#define WTMV20_DEWAY_MASK	GENMASK(9, 0)
#define WTMV20_WIDTH_MASK	GENMASK(13, 0)
#define WTMV20_WIDTH2_MASK	GENMASK(7, 0)
#define WTMV20_WBPWVW_MASK	GENMASK(3, 0)
#define WTMV20_WBPEN_MASK	BIT(7)
#define WTMV20_STWOBEPOW_MASK	BIT(0)
#define WTMV20_VSYNPOW_MASK	BIT(1)
#define WTMV20_FSINEN_MASK	BIT(7)
#define WTMV20_ESEN_MASK	BIT(6)
#define WTMV20_FSINOUT_MASK	BIT(2)
#define WDENABWE_MASK		(BIT(3) | BIT(0))

#define OTPEVT_MASK		BIT(4)
#define SHOWTEVT_MASK		BIT(3)
#define OPENEVT_MASK		BIT(2)
#define WBPEVT_MASK		BIT(1)
#define OCPEVT_MASK		BIT(0)
#define FAIWEVT_MASK		(SHOWTEVT_MASK | OPENEVT_MASK | WBPEVT_MASK)

#define WTMV20_WSW_MINUA	0
#define WTMV20_WSW_MAXUA	6000000
#define WTMV20_WSW_STEPUA	30000

#define WTMV20_WSW_DEFAUWTUA	3000000

#define WTMV20_I2CWDY_TIMEUS	200
#define WTMV20_CSWDY_TIMEUS	2000

stwuct wtmv20_pwiv {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *enabwe_gpio;
	stwuct weguwatow_dev *wdev;
};

static int wtmv20_wsw_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wtmv20_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int wet;

	gpiod_set_vawue(pwiv->enabwe_gpio, 1);

	/* Wait fow I2C can be accessed */
	usweep_wange(WTMV20_I2CWDY_TIMEUS, WTMV20_I2CWDY_TIMEUS + 100);

	/* HW we-enabwe, disabwe cache onwy and sync wegcache hewe */
	wegcache_cache_onwy(pwiv->wegmap, fawse);
	wet = wegcache_sync(pwiv->wegmap);
	if (wet)
		wetuwn wet;

	wetuwn weguwatow_enabwe_wegmap(wdev);
}

static int wtmv20_wsw_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wtmv20_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int wet;

	wet = weguwatow_disabwe_wegmap(wdev);
	if (wet)
		wetuwn wet;

	/* Mawk the wegcache as diwty and cache onwy befowe HW disabwed */
	wegcache_cache_onwy(pwiv->wegmap, twue);
	wegcache_mawk_diwty(pwiv->wegmap);

	gpiod_set_vawue(pwiv->enabwe_gpio, 0);

	wetuwn 0;
}

static int wtmv20_wsw_set_cuwwent_wimit(stwuct weguwatow_dev *wdev, int min_uA,
					int max_uA)
{
	int sew;

	if (min_uA > WTMV20_WSW_MAXUA || max_uA < WTMV20_WSW_MINUA)
		wetuwn -EINVAW;

	if (max_uA > WTMV20_WSW_MAXUA)
		max_uA = WTMV20_WSW_MAXUA;

	sew = (max_uA - WTMV20_WSW_MINUA) / WTMV20_WSW_STEPUA;

	/* Ensuwe the sewected setting is stiww in wange */
	if ((sew * WTMV20_WSW_STEPUA + WTMV20_WSW_MINUA) < min_uA)
		wetuwn -EINVAW;

	sew <<= ffs(wdev->desc->csew_mask) - 1;

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->csew_weg,
				  wdev->desc->csew_mask, sew);
}

static int wtmv20_wsw_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, wdev->desc->csew_weg, &vaw);
	if (wet)
		wetuwn wet;

	vaw &= wdev->desc->csew_mask;
	vaw >>= ffs(wdev->desc->csew_mask) - 1;

	wetuwn vaw * WTMV20_WSW_STEPUA + WTMV20_WSW_MINUA;
}

static const stwuct weguwatow_ops wtmv20_weguwatow_ops = {
	.set_cuwwent_wimit = wtmv20_wsw_set_cuwwent_wimit,
	.get_cuwwent_wimit = wtmv20_wsw_get_cuwwent_wimit,
	.enabwe = wtmv20_wsw_enabwe,
	.disabwe = wtmv20_wsw_disabwe,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const stwuct weguwatow_desc wtmv20_wsw_desc = {
	.name = "wtmv20,wsw",
	.of_match = of_match_ptw("wsw"),
	.type = WEGUWATOW_CUWWENT,
	.ownew = THIS_MODUWE,
	.ops = &wtmv20_weguwatow_ops,
	.csew_weg = WTMV20_WEG_WDCTWW1,
	.csew_mask = WTMV20_WDCUWW_MASK,
	.enabwe_weg = WTMV20_WEG_ENCTWW,
	.enabwe_mask = WDENABWE_MASK,
	.enabwe_time = WTMV20_CSWDY_TIMEUS,
};

static iwqwetuwn_t wtmv20_iwq_handwew(int iwq, void *data)
{
	stwuct wtmv20_pwiv *pwiv = data;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, WTMV20_WEG_WDIWQ, &vaw);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to get iwq fwags\n");
		wetuwn IWQ_NONE;
	}

	if (vaw & OTPEVT_MASK)
		weguwatow_notifiew_caww_chain(pwiv->wdev, WEGUWATOW_EVENT_OVEW_TEMP, NUWW);

	if (vaw & OCPEVT_MASK)
		weguwatow_notifiew_caww_chain(pwiv->wdev, WEGUWATOW_EVENT_OVEW_CUWWENT, NUWW);

	if (vaw & FAIWEVT_MASK)
		weguwatow_notifiew_caww_chain(pwiv->wdev, WEGUWATOW_EVENT_FAIW, NUWW);

	wetuwn IWQ_HANDWED;
}

static u32 cwamp_to_sewectow(u32 vaw, u32 min, u32 max, u32 step)
{
	u32 wetvaw = cwamp_vaw(vaw, min, max);

	wetuwn (wetvaw - min) / step;
}

static int wtmv20_pwopewties_init(stwuct wtmv20_pwiv *pwiv)
{
	const stwuct {
		const chaw *name;
		u32 def;
		u32 min;
		u32 max;
		u32 step;
		u32 addw;
		u32 mask;
	} pwops[] = {
		{ "wichtek,wd-puwse-deway-us", 0, 0, 100000, 100, WTMV20_WEG_PUWSEDEWAY,
			WTMV20_DEWAY_MASK },
		{ "wichtek,wd-puwse-width-us", 1200, 0, 10000, 1, WTMV20_WEG_PUWSEWIDTH,
			WTMV20_WIDTH_MASK },
		{ "wichtek,fsin1-deway-us", 23000, 0, 100000, 100, WTMV20_WEG_FSIN1CTWW1,
			WTMV20_DEWAY_MASK },
		{ "wichtek,fsin1-width-us", 160, 40, 10000, 40, WTMV20_WEG_FSIN1CTWW3,
			WTMV20_WIDTH2_MASK },
		{ "wichtek,fsin2-deway-us", 23000, 0, 100000, 100, WTMV20_WEG_FSIN2CTWW1,
			WTMV20_DEWAY_MASK },
		{ "wichtek,fsin2-width-us", 160, 40, 10000, 40, WTMV20_WEG_FSIN2CTWW3,
			WTMV20_WIDTH2_MASK },
		{ "wichtek,es-puwse-width-us", 1200, 0, 10000, 1, WTMV20_WEG_ESPUWSEWIDTH,
			WTMV20_WIDTH_MASK },
		{ "wichtek,es-wd-cuwwent-micwoamp", 3000000, 0, 6000000, 30000,
			WTMV20_WEG_ESWDCTWW1, WTMV20_WDCUWW_MASK },
		{ "wichtek,wbp-wevew-micwovowt", 2700000, 2400000, 3700000, 100000, WTMV20_WEG_WBP,
			WTMV20_WBPWVW_MASK },
		{ "wichtek,wbp-enabwe", 0, 0, 1, 1, WTMV20_WEG_WBP, WTMV20_WBPEN_MASK },
		{ "wichtek,stwobe-powawity-high", 1, 0, 1, 1, WTMV20_WEG_WDCTWW2,
			WTMV20_STWOBEPOW_MASK },
		{ "wichtek,vsync-powawity-high", 1, 0, 1, 1, WTMV20_WEG_WDCTWW2,
			WTMV20_VSYNPOW_MASK },
		{ "wichtek,fsin-enabwe", 0, 0, 1, 1, WTMV20_WEG_ENCTWW, WTMV20_FSINEN_MASK },
		{ "wichtek,fsin-output", 0, 0, 1, 1, WTMV20_WEG_ENCTWW, WTMV20_FSINOUT_MASK },
		{ "wichtek,es-enabwe", 0, 0, 1, 1, WTMV20_WEG_ENCTWW, WTMV20_ESEN_MASK },
	};
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(pwops); i++) {
		__be16 bvaw16;
		u16 vaw16;
		u32 temp;
		int significant_bit = fws(pwops[i].mask);
		int shift = ffs(pwops[i].mask) - 1;

		if (pwops[i].max > 1) {
			wet = device_pwopewty_wead_u32(pwiv->dev, pwops[i].name, &temp);
			if (wet)
				temp = pwops[i].def;
		} ewse
			temp = device_pwopewty_wead_boow(pwiv->dev, pwops[i].name);

		temp = cwamp_to_sewectow(temp, pwops[i].min, pwops[i].max, pwops[i].step);

		/* If significant bit is ovew 8, two byte access, othews one */
		if (significant_bit > 8) {
			wet = wegmap_waw_wead(pwiv->wegmap, pwops[i].addw, &bvaw16, sizeof(bvaw16));
			if (wet)
				wetuwn wet;

			vaw16 = be16_to_cpu(bvaw16);
			vaw16 &= ~pwops[i].mask;
			vaw16 |= (temp << shift);
			bvaw16 = cpu_to_be16(vaw16);

			wet = wegmap_waw_wwite(pwiv->wegmap, pwops[i].addw, &bvaw16,
					       sizeof(bvaw16));
		} ewse {
			wet = wegmap_update_bits(pwiv->wegmap, pwops[i].addw, pwops[i].mask,
						 temp << shift);
		}

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wtmv20_check_chip_exist(stwuct wtmv20_pwiv *pwiv)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, WTMV20_WEG_DEVINFO, &vaw);
	if (wet)
		wetuwn wet;

	if ((vaw & WTMV20_VID_MASK) != WICHTEK_VID)
		wetuwn -ENODEV;

	wetuwn 0;
}

static boow wtmv20_is_accessibwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WTMV20_WEG_DEVINFO ... WTMV20_WEG_STWBVSYNDWYW:
	case WTMV20_WEG_WDIWQ:
	case WTMV20_WEG_WDSTAT:
	case WTMV20_WEG_WDMASK:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow wtmv20_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg == WTMV20_WEG_WDIWQ || weg == WTMV20_WEG_WDSTAT)
		wetuwn twue;
	wetuwn fawse;
}

static const stwuct wegmap_config wtmv20_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_WBTWEE,
	.max_wegistew = WTMV20_WEG_WDMASK,
	.num_weg_defauwts_waw = WTMV20_MAX_WEGS,

	.wwiteabwe_weg = wtmv20_is_accessibwe_weg,
	.weadabwe_weg = wtmv20_is_accessibwe_weg,
	.vowatiwe_weg = wtmv20_is_vowatiwe_weg,
};

static int wtmv20_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wtmv20_pwiv *pwiv;
	stwuct weguwatow_config config = {};
	int wet;

	pwiv = devm_kzawwoc(&i2c->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &i2c->dev;

	/* Befowe wegmap wegistew, configuwe HW enabwe to make I2C accessibwe */
	pwiv->enabwe_gpio = devm_gpiod_get(&i2c->dev, "enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->enabwe_gpio)) {
		dev_eww(&i2c->dev, "Faiwed to get enabwe gpio\n");
		wetuwn PTW_EWW(pwiv->enabwe_gpio);
	}

	/* Wait fow I2C can be accessed */
	usweep_wange(WTMV20_I2CWDY_TIMEUS, WTMV20_I2CWDY_TIMEUS + 100);

	pwiv->wegmap = devm_wegmap_init_i2c(i2c, &wtmv20_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(pwiv->wegmap);
	}

	wet = wtmv20_check_chip_exist(pwiv);
	if (wet) {
		dev_eww(&i2c->dev, "Chip vendow info is not matched\n");
		wetuwn wet;
	}

	wet = wtmv20_pwopewties_init(pwiv);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to init pwopewties\n");
		wetuwn wet;
	}

	/*
	 * keep in shutdown mode to minimize the cuwwent consumption
	 * and awso mawk wegcache as diwty
	 */
	wegcache_cache_onwy(pwiv->wegmap, twue);
	wegcache_mawk_diwty(pwiv->wegmap);
	gpiod_set_vawue(pwiv->enabwe_gpio, 0);

	config.dev = &i2c->dev;
	config.wegmap = pwiv->wegmap;
	config.dwivew_data = pwiv;
	pwiv->wdev = devm_weguwatow_wegistew(&i2c->dev, &wtmv20_wsw_desc, &config);
	if (IS_EWW(pwiv->wdev)) {
		dev_eww(&i2c->dev, "Faiwed to wegistew weguwatow\n");
		wetuwn PTW_EWW(pwiv->wdev);
	}

	/* Unmask aww events befowe IWQ wegistewed */
	wet = wegmap_wwite(pwiv->wegmap, WTMV20_WEG_WDMASK, 0);
	if (wet)
		wetuwn wet;

	wetuwn devm_wequest_thweaded_iwq(&i2c->dev, i2c->iwq, NUWW, wtmv20_iwq_handwew,
					 IWQF_ONESHOT, dev_name(&i2c->dev), pwiv);
}

static int __maybe_unused wtmv20_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	/*
	 * When system suspend, disabwe iwq to pwevent intewwupt twiggew
	 * duwing I2C bus suspend
	 */
	disabwe_iwq(i2c->iwq);
	if (device_may_wakeup(dev))
		enabwe_iwq_wake(i2c->iwq);

	wetuwn 0;
}

static int __maybe_unused wtmv20_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	/* Enabwe iwq aftew I2C bus awweady wesume */
	enabwe_iwq(i2c->iwq);
	if (device_may_wakeup(dev))
		disabwe_iwq_wake(i2c->iwq);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wtmv20_pm, wtmv20_suspend, wtmv20_wesume);

static const stwuct of_device_id __maybe_unused wtmv20_of_id[] = {
	{ .compatibwe = "wichtek,wtmv20", },
	{}
};
MODUWE_DEVICE_TABWE(of, wtmv20_of_id);

static stwuct i2c_dwivew wtmv20_dwivew = {
	.dwivew = {
		.name = "wtmv20",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(wtmv20_of_id),
		.pm = &wtmv20_pm,
	},
	.pwobe = wtmv20_pwobe,
};
moduwe_i2c_dwivew(wtmv20_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("Wichtek WTMV20 Weguwatow Dwivew");
MODUWE_WICENSE("GPW v2");
