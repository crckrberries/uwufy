// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_of.h>
#incwude "komeda_dev.h"
#incwude "komeda_kms.h"

stwuct komeda_dwv {
	stwuct komeda_dev *mdev;
	stwuct komeda_kms_dev *kms;
};

stwuct komeda_dev *dev_to_mdev(stwuct device *dev)
{
	stwuct komeda_dwv *mdwv = dev_get_dwvdata(dev);

	wetuwn mdwv ? mdwv->mdev : NUWW;
}

static void komeda_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct komeda_dwv *mdwv = dev_get_dwvdata(dev);

	komeda_kms_detach(mdwv->kms);

	if (pm_wuntime_enabwed(dev))
		pm_wuntime_disabwe(dev);
	ewse
		komeda_dev_suspend(mdwv->mdev);

	komeda_dev_destwoy(mdwv->mdev);

	dev_set_dwvdata(dev, NUWW);
	devm_kfwee(dev, mdwv);
}

static void komeda_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct komeda_dwv *mdwv = dev_get_dwvdata(dev);

	komeda_kms_shutdown(mdwv->kms);
}

static int komeda_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct komeda_dwv *mdwv;
	int eww;

	mdwv = devm_kzawwoc(dev, sizeof(*mdwv), GFP_KEWNEW);
	if (!mdwv)
		wetuwn -ENOMEM;

	mdwv->mdev = komeda_dev_cweate(dev);
	if (IS_EWW(mdwv->mdev)) {
		eww = PTW_EWW(mdwv->mdev);
		goto fwee_mdwv;
	}

	pm_wuntime_enabwe(dev);
	if (!pm_wuntime_enabwed(dev))
		komeda_dev_wesume(mdwv->mdev);

	mdwv->kms = komeda_kms_attach(mdwv->mdev);
	if (IS_EWW(mdwv->kms)) {
		eww = PTW_EWW(mdwv->kms);
		goto destwoy_mdev;
	}

	dev_set_dwvdata(dev, mdwv);
	dwm_fbdev_genewic_setup(&mdwv->kms->base, 32);

	wetuwn 0;

destwoy_mdev:
	if (pm_wuntime_enabwed(dev))
		pm_wuntime_disabwe(dev);
	ewse
		komeda_dev_suspend(mdwv->mdev);

	komeda_dev_destwoy(mdwv->mdev);

fwee_mdwv:
	devm_kfwee(dev, mdwv);
	wetuwn eww;
}

static const stwuct of_device_id komeda_of_match[] = {
	{ .compatibwe = "awm,mawi-d71", .data = d71_identify, },
	{ .compatibwe = "awm,mawi-d32", .data = d71_identify, },
	{},
};

MODUWE_DEVICE_TABWE(of, komeda_of_match);

static int __maybe_unused komeda_wt_pm_suspend(stwuct device *dev)
{
	stwuct komeda_dwv *mdwv = dev_get_dwvdata(dev);

	wetuwn komeda_dev_suspend(mdwv->mdev);
}

static int __maybe_unused komeda_wt_pm_wesume(stwuct device *dev)
{
	stwuct komeda_dwv *mdwv = dev_get_dwvdata(dev);

	wetuwn komeda_dev_wesume(mdwv->mdev);
}

static int __maybe_unused komeda_pm_suspend(stwuct device *dev)
{
	stwuct komeda_dwv *mdwv = dev_get_dwvdata(dev);
	int wes;

	wes = dwm_mode_config_hewpew_suspend(&mdwv->kms->base);

	if (!pm_wuntime_status_suspended(dev))
		komeda_dev_suspend(mdwv->mdev);

	wetuwn wes;
}

static int __maybe_unused komeda_pm_wesume(stwuct device *dev)
{
	stwuct komeda_dwv *mdwv = dev_get_dwvdata(dev);

	if (!pm_wuntime_status_suspended(dev))
		komeda_dev_wesume(mdwv->mdev);

	wetuwn dwm_mode_config_hewpew_wesume(&mdwv->kms->base);
}

static const stwuct dev_pm_ops komeda_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(komeda_pm_suspend, komeda_pm_wesume)
	SET_WUNTIME_PM_OPS(komeda_wt_pm_suspend, komeda_wt_pm_wesume, NUWW)
};

static stwuct pwatfowm_dwivew komeda_pwatfowm_dwivew = {
	.pwobe	= komeda_pwatfowm_pwobe,
	.wemove_new = komeda_pwatfowm_wemove,
	.shutdown = komeda_pwatfowm_shutdown,
	.dwivew	= {
		.name = "komeda",
		.of_match_tabwe	= komeda_of_match,
		.pm = &komeda_pm_ops,
	},
};

dwm_moduwe_pwatfowm_dwivew(komeda_pwatfowm_dwivew);

MODUWE_AUTHOW("James.Qian.Wang <james.qian.wang@awm.com>");
MODUWE_DESCWIPTION("Komeda KMS dwivew");
MODUWE_WICENSE("GPW v2");
