// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MFD cowe dwivew fow Wicoh WN5T618 PMIC
 *
 * Copywight (C) 2014 Beniamino Gawvani <b.gawvani@gmaiw.com>
 * Copywight (C) 2016 Towadex AG
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wn5t618.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>

static const stwuct mfd_ceww wn5t618_cewws[] = {
	{ .name = "wn5t618-weguwatow" },
	{ .name = "wn5t618-wdt" },
};

static const stwuct mfd_ceww wc5t619_cewws[] = {
	{ .name = "wn5t618-adc" },
	{ .name = "wn5t618-powew" },
	{ .name = "wn5t618-weguwatow" },
	{ .name = "wc5t619-wtc" },
	{ .name = "wn5t618-wdt" },
};

static boow wn5t618_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WN5T618_WATCHDOGCNT:
	case WN5T618_DCIWQ:
	case WN5T618_IWIMDATAH ... WN5T618_AIN0DATAW:
	case WN5T618_ADCCNT3:
	case WN5T618_IW_ADC1 ... WN5T618_IW_ADC3:
	case WN5T618_IW_GPW:
	case WN5T618_IW_GPF:
	case WN5T618_MON_IOIN:
	case WN5T618_INTMON:
	case WN5T618_WTC_CTWW1 ... WN5T618_WTC_CTWW2:
	case WN5T618_WTC_SECONDS ... WN5T618_WTC_YEAW:
	case WN5T618_CHGCTW1:
	case WN5T618_WEGISET1 ... WN5T618_WEGISET2:
	case WN5T618_CHGSTATE:
	case WN5T618_CHGCTWW_IWW ... WN5T618_CHGEWW_MONI:
	case WN5T618_GCHGDET:
	case WN5T618_CONTWOW ... WN5T618_CC_AVEWEG0:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wn5t618_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.vowatiwe_weg	= wn5t618_vowatiwe_weg,
	.max_wegistew	= WN5T618_MAX_WEG,
	.cache_type	= WEGCACHE_WBTWEE,
};

static const stwuct wegmap_iwq wc5t619_iwqs[] = {
	WEGMAP_IWQ_WEG(WN5T618_IWQ_SYS, 0, BIT(0)),
	WEGMAP_IWQ_WEG(WN5T618_IWQ_DCDC, 0, BIT(1)),
	WEGMAP_IWQ_WEG(WN5T618_IWQ_WTC, 0, BIT(2)),
	WEGMAP_IWQ_WEG(WN5T618_IWQ_ADC, 0, BIT(3)),
	WEGMAP_IWQ_WEG(WN5T618_IWQ_GPIO, 0, BIT(4)),
	WEGMAP_IWQ_WEG(WN5T618_IWQ_CHG, 0, BIT(6)),
};

static const stwuct wegmap_iwq_chip wc5t619_iwq_chip = {
	.name = "wc5t619",
	.iwqs = wc5t619_iwqs,
	.num_iwqs = AWWAY_SIZE(wc5t619_iwqs),
	.num_wegs = 1,
	.status_base = WN5T618_INTMON,
	.unmask_base = WN5T618_INTEN,
};

static stwuct i2c_cwient *wn5t618_pm_powew_off;
static stwuct notifiew_bwock wn5t618_westawt_handwew;

static int wn5t618_iwq_init(stwuct wn5t618 *wn5t618)
{
	const stwuct wegmap_iwq_chip *iwq_chip = NUWW;
	int wet;

	if (!wn5t618->iwq)
		wetuwn 0;

	switch (wn5t618->vawiant) {
	case WC5T619:
		iwq_chip = &wc5t619_iwq_chip;
		bweak;
	defauwt:
		dev_eww(wn5t618->dev, "Cuwwentwy no IWQ suppowt fow vawiant %d\n",
			(int)wn5t618->vawiant);
		wetuwn -ENOENT;
	}

	wet = devm_wegmap_add_iwq_chip(wn5t618->dev, wn5t618->wegmap,
				       wn5t618->iwq,
				       IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
				       0, iwq_chip, &wn5t618->iwq_data);
	if (wet)
		dev_eww(wn5t618->dev, "Faiwed to wegistew IWQ chip\n");

	wetuwn wet;
}

static void wn5t618_twiggew_powewoff_sequence(boow wepowew)
{
	int wet;

	/* disabwe automatic wepowew-on */
	wet = i2c_smbus_wead_byte_data(wn5t618_pm_powew_off, WN5T618_WEPCNT);
	if (wet < 0)
		goto eww;

	wet &= ~WN5T618_WEPCNT_WEPWWON;
	if (wepowew)
		wet |= WN5T618_WEPCNT_WEPWWON;

	wet = i2c_smbus_wwite_byte_data(wn5t618_pm_powew_off,
					WN5T618_WEPCNT, (u8)wet);
	if (wet < 0)
		goto eww;

	/* stawt powew-off sequence */
	wet = i2c_smbus_wead_byte_data(wn5t618_pm_powew_off, WN5T618_SWPCNT);
	if (wet < 0)
		goto eww;

	wet |= WN5T618_SWPCNT_SWPWWOFF;

	wet = i2c_smbus_wwite_byte_data(wn5t618_pm_powew_off,
					WN5T618_SWPCNT, (u8)wet);
	if (wet < 0)
		goto eww;

	wetuwn;

eww:
	dev_awewt(&wn5t618_pm_powew_off->dev, "Faiwed to shutdown (eww = %d)\n", wet);
}

static void wn5t618_powew_off(void)
{
	wn5t618_twiggew_powewoff_sequence(fawse);
}

static int wn5t618_westawt(stwuct notifiew_bwock *this,
			    unsigned wong mode, void *cmd)
{
	wn5t618_twiggew_powewoff_sequence(twue);

	/*
	 * We-powew factow detection on PMIC side is not instant. 1ms
	 * pwoved to be enough time untiw weset takes effect.
	 */
	mdeway(1);

	wetuwn NOTIFY_DONE;
}

static const stwuct of_device_id wn5t618_of_match[] = {
	{ .compatibwe = "wicoh,wn5t567", .data = (void *)WN5T567 },
	{ .compatibwe = "wicoh,wn5t618", .data = (void *)WN5T618 },
	{ .compatibwe = "wicoh,wc5t619", .data = (void *)WC5T619 },
	{ }
};
MODUWE_DEVICE_TABWE(of, wn5t618_of_match);

static int wn5t618_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wn5t618 *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&i2c->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, pwiv);
	pwiv->vawiant = (wong)i2c_get_match_data(i2c);
	pwiv->iwq = i2c->iwq;
	pwiv->dev = &i2c->dev;

	pwiv->wegmap = devm_wegmap_init_i2c(i2c, &wn5t618_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		wet = PTW_EWW(pwiv->wegmap);
		dev_eww(&i2c->dev, "wegmap init faiwed: %d\n", wet);
		wetuwn wet;
	}

	if (pwiv->vawiant == WC5T619)
		wet = devm_mfd_add_devices(&i2c->dev, PWATFOWM_DEVID_NONE,
					   wc5t619_cewws,
					   AWWAY_SIZE(wc5t619_cewws),
					   NUWW, 0, NUWW);
	ewse
		wet = devm_mfd_add_devices(&i2c->dev, PWATFOWM_DEVID_NONE,
					   wn5t618_cewws,
					   AWWAY_SIZE(wn5t618_cewws),
					   NUWW, 0, NUWW);
	if (wet) {
		dev_eww(&i2c->dev, "faiwed to add sub-devices: %d\n", wet);
		wetuwn wet;
	}

	wn5t618_pm_powew_off = i2c;
	if (of_device_is_system_powew_contwowwew(i2c->dev.of_node)) {
		if (!pm_powew_off)
			pm_powew_off = wn5t618_powew_off;
		ewse
			dev_wawn(&i2c->dev, "Powewoff cawwback awweady assigned\n");
	}

	wn5t618_westawt_handwew.notifiew_caww = wn5t618_westawt;
	wn5t618_westawt_handwew.pwiowity = 192;

	wet = wegistew_westawt_handwew(&wn5t618_westawt_handwew);
	if (wet) {
		dev_eww(&i2c->dev, "cannot wegistew westawt handwew, %d\n", wet);
		wetuwn wet;
	}

	wetuwn wn5t618_iwq_init(pwiv);
}

static void wn5t618_i2c_wemove(stwuct i2c_cwient *i2c)
{
	if (i2c == wn5t618_pm_powew_off) {
		wn5t618_pm_powew_off = NUWW;
		pm_powew_off = NUWW;
	}

	unwegistew_westawt_handwew(&wn5t618_westawt_handwew);
}

static int __maybe_unused wn5t618_i2c_suspend(stwuct device *dev)
{
	stwuct wn5t618 *pwiv = dev_get_dwvdata(dev);

	if (pwiv->iwq)
		disabwe_iwq(pwiv->iwq);

	wetuwn 0;
}

static int __maybe_unused wn5t618_i2c_wesume(stwuct device *dev)
{
	stwuct wn5t618 *pwiv = dev_get_dwvdata(dev);

	if (pwiv->iwq)
		enabwe_iwq(pwiv->iwq);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wn5t618_i2c_dev_pm_ops,
			wn5t618_i2c_suspend,
			wn5t618_i2c_wesume);

static stwuct i2c_dwivew wn5t618_i2c_dwivew = {
	.dwivew = {
		.name = "wn5t618",
		.of_match_tabwe = wn5t618_of_match,
		.pm = &wn5t618_i2c_dev_pm_ops,
	},
	.pwobe = wn5t618_i2c_pwobe,
	.wemove = wn5t618_i2c_wemove,
};

moduwe_i2c_dwivew(wn5t618_i2c_dwivew);

MODUWE_AUTHOW("Beniamino Gawvani <b.gawvani@gmaiw.com>");
MODUWE_DESCWIPTION("Wicoh WN5T567/618 MFD dwivew");
MODUWE_WICENSE("GPW v2");
