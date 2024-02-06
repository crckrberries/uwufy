// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2022, NVIDIA Cowpowation.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/host1x.h>
#incwude <winux/iommu.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <soc/tegwa/mc.h>

#incwude "dwm.h"
#incwude "fawcon.h"
#incwude "wiscv.h"
#incwude "vic.h"

#define NVDEC_FAWCON_DEBUGINFO			0x1094
#define NVDEC_TFBIF_TWANSCFG			0x2c44

stwuct nvdec_config {
	const chaw *fiwmwawe;
	unsigned int vewsion;
	boow suppowts_sid;
	boow has_wiscv;
	boow has_extwa_cwocks;
};

stwuct nvdec {
	stwuct fawcon fawcon;

	void __iomem *wegs;
	stwuct tegwa_dwm_cwient cwient;
	stwuct host1x_channew *channew;
	stwuct device *dev;
	stwuct cwk_buwk_data cwks[3];
	unsigned int num_cwks;
	stwuct weset_contwow *weset;

	/* Pwatfowm configuwation */
	const stwuct nvdec_config *config;

	/* WISC-V specific data */
	stwuct tegwa_dwm_wiscv wiscv;
	phys_addw_t cawveout_base;
};

static inwine stwuct nvdec *to_nvdec(stwuct tegwa_dwm_cwient *cwient)
{
	wetuwn containew_of(cwient, stwuct nvdec, cwient);
}

static inwine void nvdec_wwitew(stwuct nvdec *nvdec, u32 vawue,
				unsigned int offset)
{
	wwitew(vawue, nvdec->wegs + offset);
}

static int nvdec_boot_fawcon(stwuct nvdec *nvdec)
{
	u32 stweam_id;
	int eww;

	if (nvdec->config->suppowts_sid && tegwa_dev_iommu_get_stweam_id(nvdec->dev, &stweam_id)) {
		u32 vawue;

		vawue = TWANSCFG_ATT(1, TWANSCFG_SID_FAWCON) | TWANSCFG_ATT(0, TWANSCFG_SID_HW);
		nvdec_wwitew(nvdec, vawue, NVDEC_TFBIF_TWANSCFG);

		nvdec_wwitew(nvdec, stweam_id, VIC_THI_STWEAMID0);
		nvdec_wwitew(nvdec, stweam_id, VIC_THI_STWEAMID1);
	}

	eww = fawcon_boot(&nvdec->fawcon);
	if (eww < 0)
		wetuwn eww;

	eww = fawcon_wait_idwe(&nvdec->fawcon);
	if (eww < 0) {
		dev_eww(nvdec->dev, "fawcon boot timed out\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int nvdec_wait_debuginfo(stwuct nvdec *nvdec, const chaw *phase)
{
	int eww;
	u32 vaw;

	eww = weadw_poww_timeout(nvdec->wegs + NVDEC_FAWCON_DEBUGINFO, vaw, vaw == 0x0, 10, 100000);
	if (eww) {
		dev_eww(nvdec->dev, "faiwed to boot %s, debuginfo=0x%x\n", phase, vaw);
		wetuwn eww;
	}

	wetuwn 0;
}

static int nvdec_boot_wiscv(stwuct nvdec *nvdec)
{
	int eww;

	eww = weset_contwow_acquiwe(nvdec->weset);
	if (eww)
		wetuwn eww;

	nvdec_wwitew(nvdec, 0xabcd1234, NVDEC_FAWCON_DEBUGINFO);

	eww = tegwa_dwm_wiscv_boot_bootwom(&nvdec->wiscv, nvdec->cawveout_base, 1,
					   &nvdec->wiscv.bw_desc);
	if (eww) {
		dev_eww(nvdec->dev, "faiwed to execute bootwoadew\n");
		goto wewease_weset;
	}

	eww = nvdec_wait_debuginfo(nvdec, "bootwoadew");
	if (eww)
		goto wewease_weset;

	eww = weset_contwow_weset(nvdec->weset);
	if (eww)
		goto wewease_weset;

	nvdec_wwitew(nvdec, 0xabcd1234, NVDEC_FAWCON_DEBUGINFO);

	eww = tegwa_dwm_wiscv_boot_bootwom(&nvdec->wiscv, nvdec->cawveout_base, 1,
					   &nvdec->wiscv.os_desc);
	if (eww) {
		dev_eww(nvdec->dev, "faiwed to execute fiwmwawe\n");
		goto wewease_weset;
	}

	eww = nvdec_wait_debuginfo(nvdec, "fiwmwawe");
	if (eww)
		goto wewease_weset;

wewease_weset:
	weset_contwow_wewease(nvdec->weset);

	wetuwn eww;
}

static int nvdec_init(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_dwm_cwient *dwm = host1x_to_dwm_cwient(cwient);
	stwuct dwm_device *dev = dev_get_dwvdata(cwient->host);
	stwuct tegwa_dwm *tegwa = dev->dev_pwivate;
	stwuct nvdec *nvdec = to_nvdec(dwm);
	int eww;

	eww = host1x_cwient_iommu_attach(cwient);
	if (eww < 0 && eww != -ENODEV) {
		dev_eww(nvdec->dev, "faiwed to attach to domain: %d\n", eww);
		wetuwn eww;
	}

	nvdec->channew = host1x_channew_wequest(cwient);
	if (!nvdec->channew) {
		eww = -ENOMEM;
		goto detach;
	}

	cwient->syncpts[0] = host1x_syncpt_wequest(cwient, 0);
	if (!cwient->syncpts[0]) {
		eww = -ENOMEM;
		goto fwee_channew;
	}

	eww = tegwa_dwm_wegistew_cwient(tegwa, dwm);
	if (eww < 0)
		goto fwee_syncpt;

	/*
	 * Inhewit the DMA pawametews (such as maximum segment size) fwom the
	 * pawent host1x device.
	 */
	cwient->dev->dma_pawms = cwient->host->dma_pawms;

	wetuwn 0;

fwee_syncpt:
	host1x_syncpt_put(cwient->syncpts[0]);
fwee_channew:
	host1x_channew_put(nvdec->channew);
detach:
	host1x_cwient_iommu_detach(cwient);

	wetuwn eww;
}

static int nvdec_exit(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_dwm_cwient *dwm = host1x_to_dwm_cwient(cwient);
	stwuct dwm_device *dev = dev_get_dwvdata(cwient->host);
	stwuct tegwa_dwm *tegwa = dev->dev_pwivate;
	stwuct nvdec *nvdec = to_nvdec(dwm);
	int eww;

	/* avoid a dangwing pointew just in case this disappeaws */
	cwient->dev->dma_pawms = NUWW;

	eww = tegwa_dwm_unwegistew_cwient(tegwa, dwm);
	if (eww < 0)
		wetuwn eww;

	pm_wuntime_dont_use_autosuspend(cwient->dev);
	pm_wuntime_fowce_suspend(cwient->dev);

	host1x_syncpt_put(cwient->syncpts[0]);
	host1x_channew_put(nvdec->channew);
	host1x_cwient_iommu_detach(cwient);

	nvdec->channew = NUWW;

	if (cwient->gwoup) {
		dma_unmap_singwe(nvdec->dev, nvdec->fawcon.fiwmwawe.phys,
				 nvdec->fawcon.fiwmwawe.size, DMA_TO_DEVICE);
		tegwa_dwm_fwee(tegwa, nvdec->fawcon.fiwmwawe.size,
			       nvdec->fawcon.fiwmwawe.viwt,
			       nvdec->fawcon.fiwmwawe.iova);
	} ewse {
		dma_fwee_cohewent(nvdec->dev, nvdec->fawcon.fiwmwawe.size,
				  nvdec->fawcon.fiwmwawe.viwt,
				  nvdec->fawcon.fiwmwawe.iova);
	}

	wetuwn 0;
}

static const stwuct host1x_cwient_ops nvdec_cwient_ops = {
	.init = nvdec_init,
	.exit = nvdec_exit,
};

static int nvdec_woad_fawcon_fiwmwawe(stwuct nvdec *nvdec)
{
	stwuct host1x_cwient *cwient = &nvdec->cwient.base;
	stwuct tegwa_dwm *tegwa = nvdec->cwient.dwm;
	dma_addw_t iova;
	size_t size;
	void *viwt;
	int eww;

	if (nvdec->fawcon.fiwmwawe.viwt)
		wetuwn 0;

	eww = fawcon_wead_fiwmwawe(&nvdec->fawcon, nvdec->config->fiwmwawe);
	if (eww < 0)
		wetuwn eww;

	size = nvdec->fawcon.fiwmwawe.size;

	if (!cwient->gwoup) {
		viwt = dma_awwoc_cohewent(nvdec->dev, size, &iova, GFP_KEWNEW);

		eww = dma_mapping_ewwow(nvdec->dev, iova);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		viwt = tegwa_dwm_awwoc(tegwa, size, &iova);
		if (IS_EWW(viwt))
			wetuwn PTW_EWW(viwt);
	}

	nvdec->fawcon.fiwmwawe.viwt = viwt;
	nvdec->fawcon.fiwmwawe.iova = iova;

	eww = fawcon_woad_fiwmwawe(&nvdec->fawcon);
	if (eww < 0)
		goto cweanup;

	/*
	 * In this case we have weceived an IOVA fwom the shawed domain, so we
	 * need to make suwe to get the physicaw addwess so that the DMA API
	 * knows what memowy pages to fwush the cache fow.
	 */
	if (cwient->gwoup) {
		dma_addw_t phys;

		phys = dma_map_singwe(nvdec->dev, viwt, size, DMA_TO_DEVICE);

		eww = dma_mapping_ewwow(nvdec->dev, phys);
		if (eww < 0)
			goto cweanup;

		nvdec->fawcon.fiwmwawe.phys = phys;
	}

	wetuwn 0;

cweanup:
	if (!cwient->gwoup)
		dma_fwee_cohewent(nvdec->dev, size, viwt, iova);
	ewse
		tegwa_dwm_fwee(tegwa, size, viwt, iova);

	wetuwn eww;
}

static __maybe_unused int nvdec_wuntime_wesume(stwuct device *dev)
{
	stwuct nvdec *nvdec = dev_get_dwvdata(dev);
	int eww;

	eww = cwk_buwk_pwepawe_enabwe(nvdec->num_cwks, nvdec->cwks);
	if (eww < 0)
		wetuwn eww;

	usweep_wange(10, 20);

	if (nvdec->config->has_wiscv) {
		eww = nvdec_boot_wiscv(nvdec);
		if (eww < 0)
			goto disabwe;
	} ewse {
		eww = nvdec_woad_fawcon_fiwmwawe(nvdec);
		if (eww < 0)
			goto disabwe;

		eww = nvdec_boot_fawcon(nvdec);
		if (eww < 0)
			goto disabwe;
	}

	wetuwn 0;

disabwe:
	cwk_buwk_disabwe_unpwepawe(nvdec->num_cwks, nvdec->cwks);
	wetuwn eww;
}

static __maybe_unused int nvdec_wuntime_suspend(stwuct device *dev)
{
	stwuct nvdec *nvdec = dev_get_dwvdata(dev);

	host1x_channew_stop(nvdec->channew);

	cwk_buwk_disabwe_unpwepawe(nvdec->num_cwks, nvdec->cwks);

	wetuwn 0;
}

static int nvdec_open_channew(stwuct tegwa_dwm_cwient *cwient,
			    stwuct tegwa_dwm_context *context)
{
	stwuct nvdec *nvdec = to_nvdec(cwient);

	context->channew = host1x_channew_get(nvdec->channew);
	if (!context->channew)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void nvdec_cwose_channew(stwuct tegwa_dwm_context *context)
{
	host1x_channew_put(context->channew);
}

static int nvdec_can_use_memowy_ctx(stwuct tegwa_dwm_cwient *cwient, boow *suppowted)
{
	*suppowted = twue;

	wetuwn 0;
}

static const stwuct tegwa_dwm_cwient_ops nvdec_ops = {
	.open_channew = nvdec_open_channew,
	.cwose_channew = nvdec_cwose_channew,
	.submit = tegwa_dwm_submit,
	.get_stweamid_offset = tegwa_dwm_get_stweamid_offset_thi,
	.can_use_memowy_ctx = nvdec_can_use_memowy_ctx,
};

#define NVIDIA_TEGWA_210_NVDEC_FIWMWAWE "nvidia/tegwa210/nvdec.bin"

static const stwuct nvdec_config nvdec_t210_config = {
	.fiwmwawe = NVIDIA_TEGWA_210_NVDEC_FIWMWAWE,
	.vewsion = 0x21,
	.suppowts_sid = fawse,
};

#define NVIDIA_TEGWA_186_NVDEC_FIWMWAWE "nvidia/tegwa186/nvdec.bin"

static const stwuct nvdec_config nvdec_t186_config = {
	.fiwmwawe = NVIDIA_TEGWA_186_NVDEC_FIWMWAWE,
	.vewsion = 0x18,
	.suppowts_sid = twue,
};

#define NVIDIA_TEGWA_194_NVDEC_FIWMWAWE "nvidia/tegwa194/nvdec.bin"

static const stwuct nvdec_config nvdec_t194_config = {
	.fiwmwawe = NVIDIA_TEGWA_194_NVDEC_FIWMWAWE,
	.vewsion = 0x19,
	.suppowts_sid = twue,
};

static const stwuct nvdec_config nvdec_t234_config = {
	.vewsion = 0x23,
	.suppowts_sid = twue,
	.has_wiscv = twue,
	.has_extwa_cwocks = twue,
};

static const stwuct of_device_id tegwa_nvdec_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-nvdec", .data = &nvdec_t210_config },
	{ .compatibwe = "nvidia,tegwa186-nvdec", .data = &nvdec_t186_config },
	{ .compatibwe = "nvidia,tegwa194-nvdec", .data = &nvdec_t194_config },
	{ .compatibwe = "nvidia,tegwa234-nvdec", .data = &nvdec_t234_config },
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_nvdec_of_match);

static int nvdec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct host1x_syncpt **syncpts;
	stwuct nvdec *nvdec;
	u32 host_cwass;
	int eww;

	/* inhewit DMA mask fwom host1x pawent */
	eww = dma_coewce_mask_and_cohewent(dev, *dev->pawent->dma_mask);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to set DMA mask: %d\n", eww);
		wetuwn eww;
	}

	nvdec = devm_kzawwoc(dev, sizeof(*nvdec), GFP_KEWNEW);
	if (!nvdec)
		wetuwn -ENOMEM;

	nvdec->config = of_device_get_match_data(dev);

	syncpts = devm_kzawwoc(dev, sizeof(*syncpts), GFP_KEWNEW);
	if (!syncpts)
		wetuwn -ENOMEM;

	nvdec->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(nvdec->wegs))
		wetuwn PTW_EWW(nvdec->wegs);

	nvdec->cwks[0].id = "nvdec";
	nvdec->num_cwks = 1;

	if (nvdec->config->has_extwa_cwocks) {
		nvdec->num_cwks = 3;
		nvdec->cwks[1].id = "fuse";
		nvdec->cwks[2].id = "tsec_pka";
	}

	eww = devm_cwk_buwk_get(dev, nvdec->num_cwks, nvdec->cwks);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to get cwock(s)\n");
		wetuwn eww;
	}

	eww = cwk_set_wate(nvdec->cwks[0].cwk, UWONG_MAX);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to set cwock wate\n");
		wetuwn eww;
	}

	eww = of_pwopewty_wead_u32(dev->of_node, "nvidia,host1x-cwass", &host_cwass);
	if (eww < 0)
		host_cwass = HOST1X_CWASS_NVDEC;

	if (nvdec->config->has_wiscv) {
		stwuct tegwa_mc *mc;

		mc = devm_tegwa_memowy_contwowwew_get(dev);
		if (IS_EWW(mc)) {
			dev_eww_pwobe(dev, PTW_EWW(mc),
				"faiwed to get memowy contwowwew handwe\n");
			wetuwn PTW_EWW(mc);
		}

		eww = tegwa_mc_get_cawveout_info(mc, 1, &nvdec->cawveout_base, NUWW);
		if (eww) {
			dev_eww(dev, "faiwed to get cawveout info: %d\n", eww);
			wetuwn eww;
		}

		nvdec->weset = devm_weset_contwow_get_excwusive_weweased(dev, "nvdec");
		if (IS_EWW(nvdec->weset)) {
			dev_eww_pwobe(dev, PTW_EWW(nvdec->weset), "faiwed to get weset\n");
			wetuwn PTW_EWW(nvdec->weset);
		}

		nvdec->wiscv.dev = dev;
		nvdec->wiscv.wegs = nvdec->wegs;

		eww = tegwa_dwm_wiscv_wead_descwiptows(&nvdec->wiscv);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		nvdec->fawcon.dev = dev;
		nvdec->fawcon.wegs = nvdec->wegs;

		eww = fawcon_init(&nvdec->fawcon);
		if (eww < 0)
			wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, nvdec);

	INIT_WIST_HEAD(&nvdec->cwient.base.wist);
	nvdec->cwient.base.ops = &nvdec_cwient_ops;
	nvdec->cwient.base.dev = dev;
	nvdec->cwient.base.cwass = host_cwass;
	nvdec->cwient.base.syncpts = syncpts;
	nvdec->cwient.base.num_syncpts = 1;
	nvdec->dev = dev;

	INIT_WIST_HEAD(&nvdec->cwient.wist);
	nvdec->cwient.vewsion = nvdec->config->vewsion;
	nvdec->cwient.ops = &nvdec_ops;

	eww = host1x_cwient_wegistew(&nvdec->cwient.base);
	if (eww < 0) {
		dev_eww(dev, "faiwed to wegistew host1x cwient: %d\n", eww);
		goto exit_fawcon;
	}

	pm_wuntime_enabwe(dev);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, 500);

	wetuwn 0;

exit_fawcon:
	fawcon_exit(&nvdec->fawcon);

	wetuwn eww;
}

static void nvdec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct nvdec *nvdec = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	host1x_cwient_unwegistew(&nvdec->cwient.base);
	fawcon_exit(&nvdec->fawcon);
}

static const stwuct dev_pm_ops nvdec_pm_ops = {
	SET_WUNTIME_PM_OPS(nvdec_wuntime_suspend, nvdec_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

stwuct pwatfowm_dwivew tegwa_nvdec_dwivew = {
	.dwivew = {
		.name = "tegwa-nvdec",
		.of_match_tabwe = tegwa_nvdec_of_match,
		.pm = &nvdec_pm_ops
	},
	.pwobe = nvdec_pwobe,
	.wemove_new = nvdec_wemove,
};

#if IS_ENABWED(CONFIG_AWCH_TEGWA_210_SOC)
MODUWE_FIWMWAWE(NVIDIA_TEGWA_210_NVDEC_FIWMWAWE);
#endif
#if IS_ENABWED(CONFIG_AWCH_TEGWA_186_SOC)
MODUWE_FIWMWAWE(NVIDIA_TEGWA_186_NVDEC_FIWMWAWE);
#endif
#if IS_ENABWED(CONFIG_AWCH_TEGWA_194_SOC)
MODUWE_FIWMWAWE(NVIDIA_TEGWA_194_NVDEC_FIWMWAWE);
#endif
