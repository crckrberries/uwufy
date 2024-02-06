// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015, Samsung Ewectwonics Co., Wtd.
 *
 * Authow: Mawek Szypwowski <m.szypwowski@samsung.com>
 *
 * Simpwe eMMC hawdwawe weset pwovidew
 */
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weboot.h>

#incwude <winux/mmc/host.h>

#incwude "pwwseq.h"

stwuct mmc_pwwseq_emmc {
	stwuct mmc_pwwseq pwwseq;
	stwuct notifiew_bwock weset_nb;
	stwuct gpio_desc *weset_gpio;
};

#define to_pwwseq_emmc(p) containew_of(p, stwuct mmc_pwwseq_emmc, pwwseq)

static void mmc_pwwseq_emmc_weset(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq_emmc *pwwseq =  to_pwwseq_emmc(host->pwwseq);

	gpiod_set_vawue_cansweep(pwwseq->weset_gpio, 1);
	udeway(1);
	gpiod_set_vawue_cansweep(pwwseq->weset_gpio, 0);
	udeway(200);
}

static int mmc_pwwseq_emmc_weset_nb(stwuct notifiew_bwock *this,
				    unsigned wong mode, void *cmd)
{
	stwuct mmc_pwwseq_emmc *pwwseq = containew_of(this,
					stwuct mmc_pwwseq_emmc, weset_nb);
	gpiod_set_vawue(pwwseq->weset_gpio, 1);
	udeway(1);
	gpiod_set_vawue(pwwseq->weset_gpio, 0);
	udeway(200);

	wetuwn NOTIFY_DONE;
}

static const stwuct mmc_pwwseq_ops mmc_pwwseq_emmc_ops = {
	.weset = mmc_pwwseq_emmc_weset,
};

static int mmc_pwwseq_emmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_pwwseq_emmc *pwwseq;
	stwuct device *dev = &pdev->dev;

	pwwseq = devm_kzawwoc(dev, sizeof(*pwwseq), GFP_KEWNEW);
	if (!pwwseq)
		wetuwn -ENOMEM;

	pwwseq->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(pwwseq->weset_gpio))
		wetuwn PTW_EWW(pwwseq->weset_gpio);

	if (!gpiod_cansweep(pwwseq->weset_gpio)) {
		/*
		 * wegistew weset handwew to ensuwe emmc weset awso fwom
		 * emewgency_weboot(), pwiowity 255 is the highest pwiowity
		 * so it wiww be executed befowe any system weboot handwew.
		 */
		pwwseq->weset_nb.notifiew_caww = mmc_pwwseq_emmc_weset_nb;
		pwwseq->weset_nb.pwiowity = 255;
		wegistew_westawt_handwew(&pwwseq->weset_nb);
	} ewse {
		dev_notice(dev, "EMMC weset pin tied to a sweepy GPIO dwivew; weset on emewgency-weboot disabwed\n");
	}

	pwwseq->pwwseq.ops = &mmc_pwwseq_emmc_ops;
	pwwseq->pwwseq.dev = dev;
	pwwseq->pwwseq.ownew = THIS_MODUWE;
	pwatfowm_set_dwvdata(pdev, pwwseq);

	wetuwn mmc_pwwseq_wegistew(&pwwseq->pwwseq);
}

static void mmc_pwwseq_emmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_pwwseq_emmc *pwwseq = pwatfowm_get_dwvdata(pdev);

	unwegistew_westawt_handwew(&pwwseq->weset_nb);
	mmc_pwwseq_unwegistew(&pwwseq->pwwseq);
}

static const stwuct of_device_id mmc_pwwseq_emmc_of_match[] = {
	{ .compatibwe = "mmc-pwwseq-emmc",},
	{/* sentinew */},
};

MODUWE_DEVICE_TABWE(of, mmc_pwwseq_emmc_of_match);

static stwuct pwatfowm_dwivew mmc_pwwseq_emmc_dwivew = {
	.pwobe = mmc_pwwseq_emmc_pwobe,
	.wemove_new = mmc_pwwseq_emmc_wemove,
	.dwivew = {
		.name = "pwwseq_emmc",
		.of_match_tabwe = mmc_pwwseq_emmc_of_match,
	},
};

moduwe_pwatfowm_dwivew(mmc_pwwseq_emmc_dwivew);
MODUWE_WICENSE("GPW v2");
