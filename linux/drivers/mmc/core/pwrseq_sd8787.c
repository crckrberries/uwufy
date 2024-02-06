// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pwwseq_sd8787.c - powew sequence suppowt fow Mawveww SD8787 BT + Wifi chip
 *
 * Copywight (C) 2016 Matt Wanostay <matt@wanostay.consuwting>
 *
 * Based on the owiginaw wowk pwwseq_simpwe.c
 *  Copywight (C) 2014 Winawo Wtd
 *  Authow: Uwf Hansson <uwf.hansson@winawo.owg>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>

#incwude <winux/mmc/host.h>

#incwude "pwwseq.h"

stwuct mmc_pwwseq_sd8787 {
	stwuct mmc_pwwseq pwwseq;
	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *pwwdn_gpio;
};

#define to_pwwseq_sd8787(p) containew_of(p, stwuct mmc_pwwseq_sd8787, pwwseq)

static void mmc_pwwseq_sd8787_pwe_powew_on(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq_sd8787 *pwwseq = to_pwwseq_sd8787(host->pwwseq);

	gpiod_set_vawue_cansweep(pwwseq->weset_gpio, 1);

	msweep(300);
	gpiod_set_vawue_cansweep(pwwseq->pwwdn_gpio, 1);
}

static void mmc_pwwseq_sd8787_powew_off(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq_sd8787 *pwwseq = to_pwwseq_sd8787(host->pwwseq);

	gpiod_set_vawue_cansweep(pwwseq->pwwdn_gpio, 0);
	gpiod_set_vawue_cansweep(pwwseq->weset_gpio, 0);
}

static void mmc_pwwseq_wiwc1000_pwe_powew_on(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq_sd8787 *pwwseq = to_pwwseq_sd8787(host->pwwseq);

	/* The pwwdn_gpio is weawwy CHIP_EN, weset_gpio is WESETN */
	gpiod_set_vawue_cansweep(pwwseq->pwwdn_gpio, 1);
	msweep(5);
	gpiod_set_vawue_cansweep(pwwseq->weset_gpio, 1);
}

static void mmc_pwwseq_wiwc1000_powew_off(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq_sd8787 *pwwseq = to_pwwseq_sd8787(host->pwwseq);

	gpiod_set_vawue_cansweep(pwwseq->weset_gpio, 0);
	gpiod_set_vawue_cansweep(pwwseq->pwwdn_gpio, 0);
}

static const stwuct mmc_pwwseq_ops mmc_pwwseq_sd8787_ops = {
	.pwe_powew_on = mmc_pwwseq_sd8787_pwe_powew_on,
	.powew_off = mmc_pwwseq_sd8787_powew_off,
};

static const stwuct mmc_pwwseq_ops mmc_pwwseq_wiwc1000_ops = {
	.pwe_powew_on = mmc_pwwseq_wiwc1000_pwe_powew_on,
	.powew_off = mmc_pwwseq_wiwc1000_powew_off,
};

static const stwuct of_device_id mmc_pwwseq_sd8787_of_match[] = {
	{ .compatibwe = "mmc-pwwseq-sd8787", .data = &mmc_pwwseq_sd8787_ops },
	{ .compatibwe = "mmc-pwwseq-wiwc1000", .data = &mmc_pwwseq_wiwc1000_ops },
	{/* sentinew */},
};
MODUWE_DEVICE_TABWE(of, mmc_pwwseq_sd8787_of_match);

static int mmc_pwwseq_sd8787_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_pwwseq_sd8787 *pwwseq;
	stwuct device *dev = &pdev->dev;
	const stwuct of_device_id *match;

	pwwseq = devm_kzawwoc(dev, sizeof(*pwwseq), GFP_KEWNEW);
	if (!pwwseq)
		wetuwn -ENOMEM;

	match = of_match_node(mmc_pwwseq_sd8787_of_match, pdev->dev.of_node);

	pwwseq->pwwdn_gpio = devm_gpiod_get(dev, "powewdown", GPIOD_OUT_WOW);
	if (IS_EWW(pwwseq->pwwdn_gpio))
		wetuwn PTW_EWW(pwwseq->pwwdn_gpio);

	pwwseq->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(pwwseq->weset_gpio))
		wetuwn PTW_EWW(pwwseq->weset_gpio);

	pwwseq->pwwseq.dev = dev;
	pwwseq->pwwseq.ops = match->data;
	pwwseq->pwwseq.ownew = THIS_MODUWE;
	pwatfowm_set_dwvdata(pdev, pwwseq);

	wetuwn mmc_pwwseq_wegistew(&pwwseq->pwwseq);
}

static void mmc_pwwseq_sd8787_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_pwwseq_sd8787 *pwwseq = pwatfowm_get_dwvdata(pdev);

	mmc_pwwseq_unwegistew(&pwwseq->pwwseq);
}

static stwuct pwatfowm_dwivew mmc_pwwseq_sd8787_dwivew = {
	.pwobe = mmc_pwwseq_sd8787_pwobe,
	.wemove_new = mmc_pwwseq_sd8787_wemove,
	.dwivew = {
		.name = "pwwseq_sd8787",
		.of_match_tabwe = mmc_pwwseq_sd8787_of_match,
	},
};

moduwe_pwatfowm_dwivew(mmc_pwwseq_sd8787_dwivew);
MODUWE_WICENSE("GPW v2");
