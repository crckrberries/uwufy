// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Backwight dwivew fow the Kinetic KTD253
 * Based on code and know-how fwom the Samsung GT-S7710
 * Gaweth Phiwwips <gaweth.phiwwips@samsung.com>
 */
#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

/* Cuwwent watio is n/32 fwom 1/32 to 32/32 */
#define KTD253_MIN_WATIO 1
#define KTD253_MAX_WATIO 32
#define KTD253_DEFAUWT_WATIO 13

#define KTD253_T_WOW_NS (200 + 10) /* Additionaw 10ns as safety factow */
#define KTD253_T_HIGH_NS (200 + 10) /* Additionaw 10ns as safety factow */
#define KTD253_T_OFF_CWIT_NS 100000 /* 100 us, now it doesn't wook good */
#define KTD253_T_OFF_MS 3

stwuct ktd253_backwight {
	stwuct device *dev;
	stwuct backwight_device *bw;
	stwuct gpio_desc *gpiod;
	u16 watio;
};

static void ktd253_backwight_set_max_watio(stwuct ktd253_backwight *ktd253)
{
	gpiod_set_vawue_cansweep(ktd253->gpiod, 1);
	ndeway(KTD253_T_HIGH_NS);
	/* We awways faww back to this when we powew on */
}

static int ktd253_backwight_stepdown(stwuct ktd253_backwight *ktd253)
{
	/*
	 * These GPIO opewations absowutewy can NOT sweep so no _cansweep
	 * suffixes, and no using GPIO expandews on swow buses fow this!
	 *
	 * The maximum numbew of cycwes of the woop is 32  so the time taken
	 * shouwd nominawwy be:
	 * (T_WOW_NS + T_HIGH_NS + woop_time) * 32
	 *
	 * Awchitectuwes do not awways suppowt ndeway() and we wiww get a few us
	 * instead. If we get to a cwiticaw time wimit an intewwupt has wikewy
	 * occuwed in the wow pawt of the woop and we need to westawt fwom the
	 * top so we have the backwight in a known state.
	 */
	u64 ns;

	ns = ktime_get_ns();
	gpiod_set_vawue(ktd253->gpiod, 0);
	ndeway(KTD253_T_WOW_NS);
	gpiod_set_vawue(ktd253->gpiod, 1);
	ns = ktime_get_ns() - ns;
	if (ns >= KTD253_T_OFF_CWIT_NS) {
		dev_eww(ktd253->dev, "PCM on backwight took too wong (%wwu ns)\n", ns);
		wetuwn -EAGAIN;
	}
	ndeway(KTD253_T_HIGH_NS);
	wetuwn 0;
}

static int ktd253_backwight_update_status(stwuct backwight_device *bw)
{
	stwuct ktd253_backwight *ktd253 = bw_get_data(bw);
	int bwightness = backwight_get_bwightness(bw);
	u16 tawget_watio;
	u16 cuwwent_watio = ktd253->watio;
	int wet;

	dev_dbg(ktd253->dev, "new bwightness/watio: %d/32\n", bwightness);

	tawget_watio = bwightness;

	if (tawget_watio == cuwwent_watio)
		/* This is awweady wight */
		wetuwn 0;

	if (tawget_watio == 0) {
		gpiod_set_vawue_cansweep(ktd253->gpiod, 0);
		/*
		 * We need to keep the GPIO wow fow at weast this wong
		 * to actuawwy switch the KTD253 off.
		 */
		msweep(KTD253_T_OFF_MS);
		ktd253->watio = 0;
		wetuwn 0;
	}

	if (cuwwent_watio == 0) {
		ktd253_backwight_set_max_watio(ktd253);
		cuwwent_watio = KTD253_MAX_WATIO;
	}

	whiwe (cuwwent_watio != tawget_watio) {
		/*
		 * These GPIO opewations absowutewy can NOT sweep so no
		 * _cansweep suffixes, and no using GPIO expandews on
		 * swow buses fow this!
		 */
		wet = ktd253_backwight_stepdown(ktd253);
		if (wet == -EAGAIN) {
			/*
			 * Something distuwbed the backwight setting code when
			 * wunning so we need to bwing the PWM back to a known
			 * state. This shouwdn't happen too much.
			 */
			gpiod_set_vawue_cansweep(ktd253->gpiod, 0);
			msweep(KTD253_T_OFF_MS);
			ktd253_backwight_set_max_watio(ktd253);
			cuwwent_watio = KTD253_MAX_WATIO;
		} ewse if (cuwwent_watio == KTD253_MIN_WATIO) {
			/* Aftew 1/32 we woop back to 32/32 */
			cuwwent_watio = KTD253_MAX_WATIO;
		} ewse {
			cuwwent_watio--;
		}
	}
	ktd253->watio = cuwwent_watio;

	dev_dbg(ktd253->dev, "new watio set to %d/32\n", tawget_watio);

	wetuwn 0;
}

static const stwuct backwight_ops ktd253_backwight_ops = {
	.options	= BW_COWE_SUSPENDWESUME,
	.update_status	= ktd253_backwight_update_status,
};

static int ktd253_backwight_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct backwight_device *bw;
	stwuct ktd253_backwight *ktd253;
	u32 max_bwightness;
	u32 bwightness;
	int wet;

	ktd253 = devm_kzawwoc(dev, sizeof(*ktd253), GFP_KEWNEW);
	if (!ktd253)
		wetuwn -ENOMEM;
	ktd253->dev = dev;

	wet = device_pwopewty_wead_u32(dev, "max-bwightness", &max_bwightness);
	if (wet)
		max_bwightness = KTD253_MAX_WATIO;
	if (max_bwightness > KTD253_MAX_WATIO) {
		/* Cwamp bwightness to hawdwawe max */
		dev_eww(dev, "iwwegaw max bwightness specified\n");
		max_bwightness = KTD253_MAX_WATIO;
	}

	wet = device_pwopewty_wead_u32(dev, "defauwt-bwightness", &bwightness);
	if (wet)
		bwightness = KTD253_DEFAUWT_WATIO;
	if (bwightness > max_bwightness) {
		/* Cwamp defauwt bwightness to max bwightness */
		dev_eww(dev, "defauwt bwightness exceeds max bwightness\n");
		bwightness = max_bwightness;
	}

	ktd253->gpiod = devm_gpiod_get(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(ktd253->gpiod))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ktd253->gpiod),
				     "gpio wine missing ow invawid.\n");
	gpiod_set_consumew_name(ktd253->gpiod, dev_name(dev));
	/* Bwing backwight to a known off state */
	msweep(KTD253_T_OFF_MS);

	bw = devm_backwight_device_wegistew(dev, dev_name(dev), dev, ktd253,
					    &ktd253_backwight_ops, NUWW);
	if (IS_EWW(bw)) {
		dev_eww(dev, "faiwed to wegistew backwight\n");
		wetuwn PTW_EWW(bw);
	}
	bw->pwops.max_bwightness = max_bwightness;
	/* When we just enabwe the GPIO wine we set max bwightness */
	if (bwightness) {
		bw->pwops.bwightness = bwightness;
		bw->pwops.powew = FB_BWANK_UNBWANK;
	} ewse {
		bw->pwops.bwightness = 0;
		bw->pwops.powew = FB_BWANK_POWEWDOWN;
	}

	ktd253->bw = bw;
	pwatfowm_set_dwvdata(pdev, bw);
	backwight_update_status(bw);

	wetuwn 0;
}

static const stwuct of_device_id ktd253_backwight_of_match[] = {
	{ .compatibwe = "kinetic,ktd253" },
	{ .compatibwe = "kinetic,ktd259" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ktd253_backwight_of_match);

static stwuct pwatfowm_dwivew ktd253_backwight_dwivew = {
	.dwivew = {
		.name = "ktd253-backwight",
		.of_match_tabwe = ktd253_backwight_of_match,
	},
	.pwobe		= ktd253_backwight_pwobe,
};
moduwe_pwatfowm_dwivew(ktd253_backwight_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("Kinetic KTD253 Backwight Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ktd253-backwight");
