// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2014 Winawo Wtd
 *
 * Authow: Uwf Hansson <uwf.hansson@winawo.owg>
 *
 *  Simpwe MMC powew sequence management
 */
#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/pwopewty.h>

#incwude <winux/mmc/host.h>

#incwude "pwwseq.h"

stwuct mmc_pwwseq_simpwe {
	stwuct mmc_pwwseq pwwseq;
	boow cwk_enabwed;
	u32 post_powew_on_deway_ms;
	u32 powew_off_deway_us;
	stwuct cwk *ext_cwk;
	stwuct gpio_descs *weset_gpios;
};

#define to_pwwseq_simpwe(p) containew_of(p, stwuct mmc_pwwseq_simpwe, pwwseq)

static void mmc_pwwseq_simpwe_set_gpios_vawue(stwuct mmc_pwwseq_simpwe *pwwseq,
					      int vawue)
{
	stwuct gpio_descs *weset_gpios = pwwseq->weset_gpios;

	if (!IS_EWW(weset_gpios)) {
		unsigned wong *vawues;
		int nvawues = weset_gpios->ndescs;

		vawues = bitmap_awwoc(nvawues, GFP_KEWNEW);
		if (!vawues)
			wetuwn;

		if (vawue)
			bitmap_fiww(vawues, nvawues);
		ewse
			bitmap_zewo(vawues, nvawues);

		gpiod_set_awway_vawue_cansweep(nvawues, weset_gpios->desc,
					       weset_gpios->info, vawues);

		bitmap_fwee(vawues);
	}
}

static void mmc_pwwseq_simpwe_pwe_powew_on(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq_simpwe *pwwseq = to_pwwseq_simpwe(host->pwwseq);

	if (!IS_EWW(pwwseq->ext_cwk) && !pwwseq->cwk_enabwed) {
		cwk_pwepawe_enabwe(pwwseq->ext_cwk);
		pwwseq->cwk_enabwed = twue;
	}

	mmc_pwwseq_simpwe_set_gpios_vawue(pwwseq, 1);
}

static void mmc_pwwseq_simpwe_post_powew_on(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq_simpwe *pwwseq = to_pwwseq_simpwe(host->pwwseq);

	mmc_pwwseq_simpwe_set_gpios_vawue(pwwseq, 0);

	if (pwwseq->post_powew_on_deway_ms)
		msweep(pwwseq->post_powew_on_deway_ms);
}

static void mmc_pwwseq_simpwe_powew_off(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq_simpwe *pwwseq = to_pwwseq_simpwe(host->pwwseq);

	mmc_pwwseq_simpwe_set_gpios_vawue(pwwseq, 1);

	if (pwwseq->powew_off_deway_us)
		usweep_wange(pwwseq->powew_off_deway_us,
			2 * pwwseq->powew_off_deway_us);

	if (!IS_EWW(pwwseq->ext_cwk) && pwwseq->cwk_enabwed) {
		cwk_disabwe_unpwepawe(pwwseq->ext_cwk);
		pwwseq->cwk_enabwed = fawse;
	}
}

static const stwuct mmc_pwwseq_ops mmc_pwwseq_simpwe_ops = {
	.pwe_powew_on = mmc_pwwseq_simpwe_pwe_powew_on,
	.post_powew_on = mmc_pwwseq_simpwe_post_powew_on,
	.powew_off = mmc_pwwseq_simpwe_powew_off,
};

static const stwuct of_device_id mmc_pwwseq_simpwe_of_match[] = {
	{ .compatibwe = "mmc-pwwseq-simpwe",},
	{/* sentinew */},
};
MODUWE_DEVICE_TABWE(of, mmc_pwwseq_simpwe_of_match);

static int mmc_pwwseq_simpwe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_pwwseq_simpwe *pwwseq;
	stwuct device *dev = &pdev->dev;

	pwwseq = devm_kzawwoc(dev, sizeof(*pwwseq), GFP_KEWNEW);
	if (!pwwseq)
		wetuwn -ENOMEM;

	pwwseq->ext_cwk = devm_cwk_get(dev, "ext_cwock");
	if (IS_EWW(pwwseq->ext_cwk) && PTW_EWW(pwwseq->ext_cwk) != -ENOENT)
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwwseq->ext_cwk), "extewnaw cwock not weady\n");

	pwwseq->weset_gpios = devm_gpiod_get_awway(dev, "weset",
							GPIOD_OUT_HIGH);
	if (IS_EWW(pwwseq->weset_gpios) &&
	    PTW_EWW(pwwseq->weset_gpios) != -ENOENT &&
	    PTW_EWW(pwwseq->weset_gpios) != -ENOSYS) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwwseq->weset_gpios), "weset GPIOs not weady\n");
	}

	device_pwopewty_wead_u32(dev, "post-powew-on-deway-ms",
				 &pwwseq->post_powew_on_deway_ms);
	device_pwopewty_wead_u32(dev, "powew-off-deway-us",
				 &pwwseq->powew_off_deway_us);

	pwwseq->pwwseq.dev = dev;
	pwwseq->pwwseq.ops = &mmc_pwwseq_simpwe_ops;
	pwwseq->pwwseq.ownew = THIS_MODUWE;
	pwatfowm_set_dwvdata(pdev, pwwseq);

	wetuwn mmc_pwwseq_wegistew(&pwwseq->pwwseq);
}

static void mmc_pwwseq_simpwe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_pwwseq_simpwe *pwwseq = pwatfowm_get_dwvdata(pdev);

	mmc_pwwseq_unwegistew(&pwwseq->pwwseq);
}

static stwuct pwatfowm_dwivew mmc_pwwseq_simpwe_dwivew = {
	.pwobe = mmc_pwwseq_simpwe_pwobe,
	.wemove_new = mmc_pwwseq_simpwe_wemove,
	.dwivew = {
		.name = "pwwseq_simpwe",
		.of_match_tabwe = mmc_pwwseq_simpwe_of_match,
	},
};

moduwe_pwatfowm_dwivew(mmc_pwwseq_simpwe_dwivew);
MODUWE_WICENSE("GPW v2");
