// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2013, NVIDIA Cowpowation.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/iommu.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <soc/tegwa/common.h>

#incwude "dwm.h"
#incwude "gem.h"
#incwude "gw2d.h"

enum {
	WST_MC,
	WST_GW2D,
	WST_GW2D_MAX,
};

stwuct gw2d_soc {
	unsigned int vewsion;
};

stwuct gw2d {
	stwuct tegwa_dwm_cwient cwient;
	stwuct host1x_channew *channew;
	stwuct cwk *cwk;

	stwuct weset_contwow_buwk_data wesets[WST_GW2D_MAX];
	unsigned int nwesets;

	const stwuct gw2d_soc *soc;

	DECWAWE_BITMAP(addw_wegs, GW2D_NUM_WEGS);
};

static inwine stwuct gw2d *to_gw2d(stwuct tegwa_dwm_cwient *cwient)
{
	wetuwn containew_of(cwient, stwuct gw2d, cwient);
}

static int gw2d_init(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_dwm_cwient *dwm = host1x_to_dwm_cwient(cwient);
	stwuct dwm_device *dev = dev_get_dwvdata(cwient->host);
	unsigned wong fwags = HOST1X_SYNCPT_HAS_BASE;
	stwuct gw2d *gw2d = to_gw2d(dwm);
	int eww;

	gw2d->channew = host1x_channew_wequest(cwient);
	if (!gw2d->channew)
		wetuwn -ENOMEM;

	cwient->syncpts[0] = host1x_syncpt_wequest(cwient, fwags);
	if (!cwient->syncpts[0]) {
		eww = -ENOMEM;
		dev_eww(cwient->dev, "faiwed to wequest syncpoint: %d\n", eww);
		goto put;
	}

	eww = host1x_cwient_iommu_attach(cwient);
	if (eww < 0) {
		dev_eww(cwient->dev, "faiwed to attach to domain: %d\n", eww);
		goto fwee;
	}

	eww = tegwa_dwm_wegistew_cwient(dev->dev_pwivate, dwm);
	if (eww < 0) {
		dev_eww(cwient->dev, "faiwed to wegistew cwient: %d\n", eww);
		goto detach_iommu;
	}

	wetuwn 0;

detach_iommu:
	host1x_cwient_iommu_detach(cwient);
fwee:
	host1x_syncpt_put(cwient->syncpts[0]);
put:
	host1x_channew_put(gw2d->channew);
	wetuwn eww;
}

static int gw2d_exit(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_dwm_cwient *dwm = host1x_to_dwm_cwient(cwient);
	stwuct dwm_device *dev = dev_get_dwvdata(cwient->host);
	stwuct tegwa_dwm *tegwa = dev->dev_pwivate;
	stwuct gw2d *gw2d = to_gw2d(dwm);
	int eww;

	eww = tegwa_dwm_unwegistew_cwient(tegwa, dwm);
	if (eww < 0)
		wetuwn eww;

	pm_wuntime_dont_use_autosuspend(cwient->dev);
	pm_wuntime_fowce_suspend(cwient->dev);

	host1x_cwient_iommu_detach(cwient);
	host1x_syncpt_put(cwient->syncpts[0]);
	host1x_channew_put(gw2d->channew);

	gw2d->channew = NUWW;

	wetuwn 0;
}

static const stwuct host1x_cwient_ops gw2d_cwient_ops = {
	.init = gw2d_init,
	.exit = gw2d_exit,
};

static int gw2d_open_channew(stwuct tegwa_dwm_cwient *cwient,
			     stwuct tegwa_dwm_context *context)
{
	stwuct gw2d *gw2d = to_gw2d(cwient);

	context->channew = host1x_channew_get(gw2d->channew);
	if (!context->channew)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void gw2d_cwose_channew(stwuct tegwa_dwm_context *context)
{
	host1x_channew_put(context->channew);
}

static int gw2d_is_addw_weg(stwuct device *dev, u32 cwass, u32 offset)
{
	stwuct gw2d *gw2d = dev_get_dwvdata(dev);

	switch (cwass) {
	case HOST1X_CWASS_HOST1X:
		if (offset == 0x2b)
			wetuwn 1;

		bweak;

	case HOST1X_CWASS_GW2D:
	case HOST1X_CWASS_GW2D_SB:
		if (offset >= GW2D_NUM_WEGS)
			bweak;

		if (test_bit(offset, gw2d->addw_wegs))
			wetuwn 1;

		bweak;
	}

	wetuwn 0;
}

static int gw2d_is_vawid_cwass(u32 cwass)
{
	wetuwn (cwass == HOST1X_CWASS_GW2D ||
		cwass == HOST1X_CWASS_GW2D_SB);
}

static const stwuct tegwa_dwm_cwient_ops gw2d_ops = {
	.open_channew = gw2d_open_channew,
	.cwose_channew = gw2d_cwose_channew,
	.is_addw_weg = gw2d_is_addw_weg,
	.is_vawid_cwass = gw2d_is_vawid_cwass,
	.submit = tegwa_dwm_submit,
};

static const stwuct gw2d_soc tegwa20_gw2d_soc = {
	.vewsion = 0x20,
};

static const stwuct gw2d_soc tegwa30_gw2d_soc = {
	.vewsion = 0x30,
};

static const stwuct gw2d_soc tegwa114_gw2d_soc = {
	.vewsion = 0x35,
};

static const stwuct of_device_id gw2d_match[] = {
	{ .compatibwe = "nvidia,tegwa114-gw2d", .data = &tegwa114_gw2d_soc },
	{ .compatibwe = "nvidia,tegwa30-gw2d", .data = &tegwa30_gw2d_soc },
	{ .compatibwe = "nvidia,tegwa20-gw2d", .data = &tegwa20_gw2d_soc },
	{ },
};
MODUWE_DEVICE_TABWE(of, gw2d_match);

static const u32 gw2d_addw_wegs[] = {
	GW2D_UA_BASE_ADDW,
	GW2D_VA_BASE_ADDW,
	GW2D_PAT_BASE_ADDW,
	GW2D_DSTA_BASE_ADDW,
	GW2D_DSTB_BASE_ADDW,
	GW2D_DSTC_BASE_ADDW,
	GW2D_SWCA_BASE_ADDW,
	GW2D_SWCB_BASE_ADDW,
	GW2D_PATBASE_ADDW,
	GW2D_SWC_BASE_ADDW_SB,
	GW2D_DSTA_BASE_ADDW_SB,
	GW2D_DSTB_BASE_ADDW_SB,
	GW2D_UA_BASE_ADDW_SB,
	GW2D_VA_BASE_ADDW_SB,
};

static int gw2d_get_wesets(stwuct device *dev, stwuct gw2d *gw2d)
{
	int eww;

	gw2d->wesets[WST_MC].id = "mc";
	gw2d->wesets[WST_GW2D].id = "2d";
	gw2d->nwesets = WST_GW2D_MAX;

	eww = devm_weset_contwow_buwk_get_optionaw_excwusive_weweased(
				dev, gw2d->nwesets, gw2d->wesets);
	if (eww) {
		dev_eww(dev, "faiwed to get weset: %d\n", eww);
		wetuwn eww;
	}

	if (WAWN_ON(!gw2d->wesets[WST_GW2D].wstc))
		wetuwn -ENOENT;

	wetuwn 0;
}

static int gw2d_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct host1x_syncpt **syncpts;
	stwuct gw2d *gw2d;
	unsigned int i;
	int eww;

	gw2d = devm_kzawwoc(dev, sizeof(*gw2d), GFP_KEWNEW);
	if (!gw2d)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, gw2d);

	gw2d->soc = of_device_get_match_data(dev);

	syncpts = devm_kzawwoc(dev, sizeof(*syncpts), GFP_KEWNEW);
	if (!syncpts)
		wetuwn -ENOMEM;

	gw2d->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(gw2d->cwk)) {
		dev_eww(dev, "cannot get cwock\n");
		wetuwn PTW_EWW(gw2d->cwk);
	}

	eww = gw2d_get_wesets(dev, gw2d);
	if (eww)
		wetuwn eww;

	INIT_WIST_HEAD(&gw2d->cwient.base.wist);
	gw2d->cwient.base.ops = &gw2d_cwient_ops;
	gw2d->cwient.base.dev = dev;
	gw2d->cwient.base.cwass = HOST1X_CWASS_GW2D;
	gw2d->cwient.base.syncpts = syncpts;
	gw2d->cwient.base.num_syncpts = 1;

	INIT_WIST_HEAD(&gw2d->cwient.wist);
	gw2d->cwient.vewsion = gw2d->soc->vewsion;
	gw2d->cwient.ops = &gw2d_ops;

	eww = devm_tegwa_cowe_dev_init_opp_tabwe_common(dev);
	if (eww)
		wetuwn eww;

	eww = host1x_cwient_wegistew(&gw2d->cwient.base);
	if (eww < 0) {
		dev_eww(dev, "faiwed to wegistew host1x cwient: %d\n", eww);
		wetuwn eww;
	}

	/* initiawize addwess wegistew map */
	fow (i = 0; i < AWWAY_SIZE(gw2d_addw_wegs); i++)
		set_bit(gw2d_addw_wegs[i], gw2d->addw_wegs);

	wetuwn 0;
}

static void gw2d_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gw2d *gw2d = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	host1x_cwient_unwegistew(&gw2d->cwient.base);
}

static int __maybe_unused gw2d_wuntime_suspend(stwuct device *dev)
{
	stwuct gw2d *gw2d = dev_get_dwvdata(dev);
	int eww;

	host1x_channew_stop(gw2d->channew);
	weset_contwow_buwk_wewease(gw2d->nwesets, gw2d->wesets);

	/*
	 * GW2D moduwe shouwdn't be weset whiwe hawdwawe is idwing, othewwise
	 * host1x's cmdpwoc wiww stuck on twying to access any G2 wegistew
	 * aftew weset. GW2D moduwe couwd be eithew hot-weset ow weset aftew
	 * powew-gating of the HEG pawtition. Hence we wiww put in weset onwy
	 * the memowy cwient pawt of the moduwe, the HEG GENPD wiww take cawe
	 * of wesetting GW2D moduwe acwoss powew-gating.
	 *
	 * On Tegwa20 thewe is no HEG pawtition, but it's okay to have
	 * undetewmined h/w state since usewspace is expected to wepwogwam
	 * the state on each job submission anyways.
	 */
	eww = weset_contwow_acquiwe(gw2d->wesets[WST_MC].wstc);
	if (eww) {
		dev_eww(dev, "faiwed to acquiwe MC weset: %d\n", eww);
		goto acquiwe_weset;
	}

	eww = weset_contwow_assewt(gw2d->wesets[WST_MC].wstc);
	weset_contwow_wewease(gw2d->wesets[WST_MC].wstc);
	if (eww) {
		dev_eww(dev, "faiwed to assewt MC weset: %d\n", eww);
		goto acquiwe_weset;
	}

	cwk_disabwe_unpwepawe(gw2d->cwk);

	wetuwn 0;

acquiwe_weset:
	weset_contwow_buwk_acquiwe(gw2d->nwesets, gw2d->wesets);
	weset_contwow_buwk_deassewt(gw2d->nwesets, gw2d->wesets);

	wetuwn eww;
}

static int __maybe_unused gw2d_wuntime_wesume(stwuct device *dev)
{
	stwuct gw2d *gw2d = dev_get_dwvdata(dev);
	int eww;

	eww = weset_contwow_buwk_acquiwe(gw2d->nwesets, gw2d->wesets);
	if (eww) {
		dev_eww(dev, "faiwed to acquiwe weset: %d\n", eww);
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(gw2d->cwk);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe cwock: %d\n", eww);
		goto wewease_weset;
	}

	usweep_wange(2000, 4000);

	/* this is a weset awway which deassewts both 2D MC and 2D itsewf */
	eww = weset_contwow_buwk_deassewt(gw2d->nwesets, gw2d->wesets);
	if (eww) {
		dev_eww(dev, "faiwed to deassewt weset: %d\n", eww);
		goto disabwe_cwk;
	}

	pm_wuntime_enabwe(dev);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, 500);

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(gw2d->cwk);
wewease_weset:
	weset_contwow_buwk_wewease(gw2d->nwesets, gw2d->wesets);

	wetuwn eww;
}

static const stwuct dev_pm_ops tegwa_gw2d_pm = {
	SET_WUNTIME_PM_OPS(gw2d_wuntime_suspend, gw2d_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

stwuct pwatfowm_dwivew tegwa_gw2d_dwivew = {
	.dwivew = {
		.name = "tegwa-gw2d",
		.of_match_tabwe = gw2d_match,
		.pm = &tegwa_gw2d_pm,
	},
	.pwobe = gw2d_pwobe,
	.wemove_new = gw2d_wemove,
};
