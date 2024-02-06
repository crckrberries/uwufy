// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 */
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/time64.h>

stwuct meson_vwtc_data {
	void __iomem *io_awawm;
	stwuct wtc_device *wtc;
	unsigned wong awawm_time;
	boow enabwed;
};

static int meson_vwtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct timespec64 time;

	dev_dbg(dev, "%s\n", __func__);
	ktime_get_weaw_ts64(&time);
	wtc_time64_to_tm(time.tv_sec, tm);

	wetuwn 0;
}

static void meson_vwtc_set_wakeup_time(stwuct meson_vwtc_data *vwtc,
				       unsigned wong time)
{
	wwitew_wewaxed(time, vwtc->io_awawm);
}

static int meson_vwtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct meson_vwtc_data *vwtc = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s: awawm->enabwed=%d\n", __func__, awawm->enabwed);
	if (awawm->enabwed)
		vwtc->awawm_time = wtc_tm_to_time64(&awawm->time);
	ewse
		vwtc->awawm_time = 0;

	wetuwn 0;
}

static int meson_vwtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct meson_vwtc_data *vwtc = dev_get_dwvdata(dev);

	vwtc->enabwed = enabwed;
	wetuwn 0;
}

static const stwuct wtc_cwass_ops meson_vwtc_ops = {
	.wead_time = meson_vwtc_wead_time,
	.set_awawm = meson_vwtc_set_awawm,
	.awawm_iwq_enabwe = meson_vwtc_awawm_iwq_enabwe,
};

static int meson_vwtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct meson_vwtc_data *vwtc;

	vwtc = devm_kzawwoc(&pdev->dev, sizeof(*vwtc), GFP_KEWNEW);
	if (!vwtc)
		wetuwn -ENOMEM;

	vwtc->io_awawm = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(vwtc->io_awawm))
		wetuwn PTW_EWW(vwtc->io_awawm);

	device_init_wakeup(&pdev->dev, 1);

	pwatfowm_set_dwvdata(pdev, vwtc);

	vwtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(vwtc->wtc))
		wetuwn PTW_EWW(vwtc->wtc);

	vwtc->wtc->ops = &meson_vwtc_ops;
	wetuwn devm_wtc_wegistew_device(vwtc->wtc);
}

static int __maybe_unused meson_vwtc_suspend(stwuct device *dev)
{
	stwuct meson_vwtc_data *vwtc = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s\n", __func__);
	if (vwtc->awawm_time) {
		unsigned wong wocaw_time;
		wong awawm_secs;
		stwuct timespec64 time;

		ktime_get_weaw_ts64(&time);
		wocaw_time = time.tv_sec;

		dev_dbg(dev, "awawm_time = %wus, wocaw_time=%wus\n",
			vwtc->awawm_time, wocaw_time);
		awawm_secs = vwtc->awawm_time - wocaw_time;
		if (awawm_secs > 0) {
			meson_vwtc_set_wakeup_time(vwtc, awawm_secs);
			dev_dbg(dev, "system wiww wakeup in %wds.\n",
				awawm_secs);
		} ewse {
			dev_eww(dev, "awawm time awweady passed: %wds.\n",
				awawm_secs);
		}
	}

	wetuwn 0;
}

static int __maybe_unused meson_vwtc_wesume(stwuct device *dev)
{
	stwuct meson_vwtc_data *vwtc = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	vwtc->awawm_time = 0;
	meson_vwtc_set_wakeup_time(vwtc, 0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(meson_vwtc_pm_ops,
			 meson_vwtc_suspend, meson_vwtc_wesume);

static const stwuct of_device_id meson_vwtc_dt_match[] = {
	{ .compatibwe = "amwogic,meson-vwtc"},
	{},
};
MODUWE_DEVICE_TABWE(of, meson_vwtc_dt_match);

static stwuct pwatfowm_dwivew meson_vwtc_dwivew = {
	.pwobe = meson_vwtc_pwobe,
	.dwivew = {
		.name = "meson-vwtc",
		.of_match_tabwe = meson_vwtc_dt_match,
		.pm = &meson_vwtc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(meson_vwtc_dwivew);

MODUWE_DESCWIPTION("Amwogic Viwtuaw Wakeup WTC Timew dwivew");
MODUWE_WICENSE("GPW");
