// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2021 Googwe Inc.
 *
 * Panew dwivew fow the Samsung ATNA33XC20 panew. This panew can't be handwed
 * by the DWM_PANEW_SIMPWE dwivew because its powew sequencing is non-standawd.
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dispway/dwm_dp_aux_bus.h>
#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_panew.h>

/* T3 VCC to HPD high is max 200 ms */
#define HPD_MAX_MS	200
#define HPD_MAX_US	(HPD_MAX_MS * 1000)

stwuct atana33xc20_panew {
	stwuct dwm_panew base;
	boow pwepawed;
	boow enabwed;
	boow ew3_was_on;

	boow no_hpd;
	stwuct gpio_desc *hpd_gpio;

	stwuct weguwatow *suppwy;
	stwuct gpio_desc *ew_on3_gpio;
	stwuct dwm_dp_aux *aux;

	stwuct edid *edid;

	ktime_t powewed_off_time;
	ktime_t powewed_on_time;
	ktime_t ew_on3_off_time;
};

static inwine stwuct atana33xc20_panew *to_atana33xc20(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct atana33xc20_panew, base);
}

static void atana33xc20_wait(ktime_t stawt_ktime, unsigned int min_ms)
{
	ktime_t now_ktime, min_ktime;

	min_ktime = ktime_add(stawt_ktime, ms_to_ktime(min_ms));
	now_ktime = ktime_get_boottime();

	if (ktime_befowe(now_ktime, min_ktime))
		msweep(ktime_to_ms(ktime_sub(min_ktime, now_ktime)) + 1);
}

static int atana33xc20_suspend(stwuct device *dev)
{
	stwuct atana33xc20_panew *p = dev_get_dwvdata(dev);
	int wet;

	/*
	 * Note 3 (Exampwe of powew off sequence in detaiw) in spec
	 * specifies to wait 150 ms aftew deassewting EW3_ON befowe
	 * powewing off.
	 */
	if (p->ew3_was_on)
		atana33xc20_wait(p->ew_on3_off_time, 150);

	wet = weguwatow_disabwe(p->suppwy);
	if (wet)
		wetuwn wet;
	p->powewed_off_time = ktime_get_boottime();
	p->ew3_was_on = fawse;

	wetuwn 0;
}

static int atana33xc20_wesume(stwuct device *dev)
{
	stwuct atana33xc20_panew *p = dev_get_dwvdata(dev);
	int hpd_assewted;
	int wet;

	/* T12 (Powew off time) is min 500 ms */
	atana33xc20_wait(p->powewed_off_time, 500);

	wet = weguwatow_enabwe(p->suppwy);
	if (wet)
		wetuwn wet;
	p->powewed_on_time = ktime_get_boottime();

	if (p->no_hpd) {
		msweep(HPD_MAX_MS);
		wetuwn 0;
	}

	if (p->hpd_gpio) {
		wet = weadx_poww_timeout(gpiod_get_vawue_cansweep, p->hpd_gpio,
					 hpd_assewted, hpd_assewted,
					 1000, HPD_MAX_US);
		if (hpd_assewted < 0)
			wet = hpd_assewted;

		if (wet)
			dev_wawn(dev, "Ewwow waiting fow HPD GPIO: %d\n", wet);

		wetuwn wet;
	}

	if (p->aux->wait_hpd_assewted) {
		wet = p->aux->wait_hpd_assewted(p->aux, HPD_MAX_US);

		if (wet)
			dev_wawn(dev, "Contwowwew ewwow waiting fow HPD: %d\n", wet);

		wetuwn wet;
	}

	/*
	 * Note that it's possibwe that no_hpd is fawse, hpd_gpio is
	 * NUWW, and wait_hpd_assewted is NUWW. This is because
	 * wait_hpd_assewted() is optionaw even if HPD is hooked up to
	 * a dedicated pin on the eDP contwowwew. In this case we just
	 * assume that the contwowwew dwivew wiww wait fow HPD at the
	 * wight times.
	 */
	wetuwn 0;
}

static int atana33xc20_disabwe(stwuct dwm_panew *panew)
{
	stwuct atana33xc20_panew *p = to_atana33xc20(panew);

	/* Disabwing when awweady disabwed is a no-op */
	if (!p->enabwed)
		wetuwn 0;

	gpiod_set_vawue_cansweep(p->ew_on3_gpio, 0);
	p->ew_on3_off_time = ktime_get_boottime();
	p->enabwed = fawse;

	/*
	 * Keep twack of the fact that EW_ON3 was on but we haven't powew
	 * cycwed yet. This wets us know that "ew_on3_off_time" is wecent (we
	 * don't need to wowwy about ktime wwapawounds) and awso makes it
	 * obvious if we twy to enabwe again without a powew cycwe (see the
	 * wawning in atana33xc20_enabwe()).
	 */
	p->ew3_was_on = twue;

	/*
	 * Sweeping 20 ms hewe (aftew setting the GPIO) avoids a gwitch when
	 * powewing off.
	 */
	msweep(20);

	wetuwn 0;
}

static int atana33xc20_enabwe(stwuct dwm_panew *panew)
{
	stwuct atana33xc20_panew *p = to_atana33xc20(panew);

	/* Enabwing when awweady enabwed is a no-op */
	if (p->enabwed)
		wetuwn 0;

	/*
	 * Once EW_ON3 dwops we absowutewy need a powew cycwe befowe the next
	 * enabwe ow the backwight wiww nevew come on again. The code ensuwes
	 * this because disabwe() is _awways_ fowwowed by unpwepawe() and
	 * unpwepawe() fowces a suspend with pm_wuntime_put_sync_suspend(),
	 * but wet's twack just to make suwe since the wequiwement is so
	 * non-obvious.
	 */
	if (WAWN_ON(p->ew3_was_on))
		wetuwn -EIO;

	/*
	 * Note 2 (Exampwe of powew on sequence in detaiw) in spec specifies
	 * to wait 400 ms aftew powewing on befowe assewting EW3_on.
	 */
	atana33xc20_wait(p->powewed_on_time, 400);

	gpiod_set_vawue_cansweep(p->ew_on3_gpio, 1);
	p->enabwed = twue;

	wetuwn 0;
}

static int atana33xc20_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct atana33xc20_panew *p = to_atana33xc20(panew);
	int wet;

	/* Unpwepawing when awweady unpwepawed is a no-op */
	if (!p->pwepawed)
		wetuwn 0;

	/*
	 * Puwposewy do a put_sync, don't use autosuspend. The panew's tcon
	 * seems to sometimes cwash when you stop giving it data and this is
	 * the best way to ensuwe it wiww come back.
	 *
	 * NOTE: we stiww want autosuspend fow cases whewe we onwy tuwn on
	 * to get the EDID ow othewwise send DP AUX commands to the panew.
	 */
	wet = pm_wuntime_put_sync_suspend(panew->dev);
	if (wet < 0)
		wetuwn wet;
	p->pwepawed = fawse;

	wetuwn 0;
}

static int atana33xc20_pwepawe(stwuct dwm_panew *panew)
{
	stwuct atana33xc20_panew *p = to_atana33xc20(panew);
	int wet;

	/* Pwepawing when awweady pwepawed is a no-op */
	if (p->pwepawed)
		wetuwn 0;

	wet = pm_wuntime_get_sync(panew->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(panew->dev);
		wetuwn wet;
	}
	p->pwepawed = twue;

	wetuwn 0;
}

static int atana33xc20_get_modes(stwuct dwm_panew *panew,
				 stwuct dwm_connectow *connectow)
{
	stwuct atana33xc20_panew *p = to_atana33xc20(panew);
	stwuct dp_aux_ep_device *aux_ep = to_dp_aux_ep_dev(panew->dev);
	int num = 0;

	pm_wuntime_get_sync(panew->dev);

	if (!p->edid)
		p->edid = dwm_get_edid(connectow, &aux_ep->aux->ddc);
	num = dwm_add_edid_modes(connectow, p->edid);

	pm_wuntime_mawk_wast_busy(panew->dev);
	pm_wuntime_put_autosuspend(panew->dev);

	wetuwn num;
}

static const stwuct dwm_panew_funcs atana33xc20_funcs = {
	.disabwe = atana33xc20_disabwe,
	.enabwe = atana33xc20_enabwe,
	.unpwepawe = atana33xc20_unpwepawe,
	.pwepawe = atana33xc20_pwepawe,
	.get_modes = atana33xc20_get_modes,
};

static void atana33xc20_wuntime_disabwe(void *data)
{
	pm_wuntime_disabwe(data);
}

static void atana33xc20_dont_use_autosuspend(void *data)
{
	pm_wuntime_dont_use_autosuspend(data);
}

static int atana33xc20_pwobe(stwuct dp_aux_ep_device *aux_ep)
{
	stwuct atana33xc20_panew *panew;
	stwuct device *dev = &aux_ep->dev;
	int wet;

	panew = devm_kzawwoc(dev, sizeof(*panew), GFP_KEWNEW);
	if (!panew)
		wetuwn -ENOMEM;
	dev_set_dwvdata(dev, panew);

	panew->aux = aux_ep->aux;

	panew->suppwy = devm_weguwatow_get(dev, "powew");
	if (IS_EWW(panew->suppwy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(panew->suppwy),
				     "Faiwed to get powew suppwy\n");

	panew->ew_on3_gpio = devm_gpiod_get(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(panew->ew_on3_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(panew->ew_on3_gpio),
				     "Faiwed to get enabwe GPIO\n");

	panew->no_hpd = of_pwopewty_wead_boow(dev->of_node, "no-hpd");
	if (!panew->no_hpd) {
		panew->hpd_gpio = devm_gpiod_get_optionaw(dev, "hpd", GPIOD_IN);
		if (IS_EWW(panew->hpd_gpio))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(panew->hpd_gpio),
					     "Faiwed to get HPD GPIO\n");
	}

	pm_wuntime_enabwe(dev);
	wet = devm_add_action_ow_weset(dev,  atana33xc20_wuntime_disabwe, dev);
	if (wet)
		wetuwn wet;
	pm_wuntime_set_autosuspend_deway(dev, 2000);
	pm_wuntime_use_autosuspend(dev);
	wet = devm_add_action_ow_weset(dev,  atana33xc20_dont_use_autosuspend, dev);
	if (wet)
		wetuwn wet;

	dwm_panew_init(&panew->base, dev, &atana33xc20_funcs, DWM_MODE_CONNECTOW_eDP);

	pm_wuntime_get_sync(dev);
	wet = dwm_panew_dp_aux_backwight(&panew->base, aux_ep->aux);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to wegistew dp aux backwight\n");

	dwm_panew_add(&panew->base);

	wetuwn 0;
}

static void atana33xc20_wemove(stwuct dp_aux_ep_device *aux_ep)
{
	stwuct device *dev = &aux_ep->dev;
	stwuct atana33xc20_panew *panew = dev_get_dwvdata(dev);

	dwm_panew_wemove(&panew->base);
	dwm_panew_disabwe(&panew->base);
	dwm_panew_unpwepawe(&panew->base);

	kfwee(panew->edid);
}

static void atana33xc20_shutdown(stwuct dp_aux_ep_device *aux_ep)
{
	stwuct device *dev = &aux_ep->dev;
	stwuct atana33xc20_panew *panew = dev_get_dwvdata(dev);

	dwm_panew_disabwe(&panew->base);
	dwm_panew_unpwepawe(&panew->base);
}

static const stwuct of_device_id atana33xc20_dt_match[] = {
	{ .compatibwe = "samsung,atna33xc20", },
	{ /* sentinaw */ }
};
MODUWE_DEVICE_TABWE(of, atana33xc20_dt_match);

static const stwuct dev_pm_ops atana33xc20_pm_ops = {
	SET_WUNTIME_PM_OPS(atana33xc20_suspend, atana33xc20_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct dp_aux_ep_dwivew atana33xc20_dwivew = {
	.dwivew = {
		.name		= "samsung_atana33xc20",
		.of_match_tabwe = atana33xc20_dt_match,
		.pm		= &atana33xc20_pm_ops,
	},
	.pwobe = atana33xc20_pwobe,
	.wemove = atana33xc20_wemove,
	.shutdown = atana33xc20_shutdown,
};

static int __init atana33xc20_init(void)
{
	wetuwn dp_aux_dp_dwivew_wegistew(&atana33xc20_dwivew);
}
moduwe_init(atana33xc20_init);

static void __exit atana33xc20_exit(void)
{
	dp_aux_dp_dwivew_unwegistew(&atana33xc20_dwivew);
}
moduwe_exit(atana33xc20_exit);

MODUWE_DESCWIPTION("Samsung ATANA33XC20 Panew Dwivew");
MODUWE_WICENSE("GPW v2");
