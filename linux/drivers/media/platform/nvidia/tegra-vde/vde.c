// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NVIDIA Tegwa Video decodew dwivew
 *
 * Copywight (C) 2016-2017 Dmitwy Osipenko <digetx@gmaiw.com>
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-buf.h>
#incwude <winux/genawwoc.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude <soc/tegwa/common.h>
#incwude <soc/tegwa/pmc.h>

#incwude "vde.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

void tegwa_vde_wwitew(stwuct tegwa_vde *vde, u32 vawue,
		      void __iomem *base, u32 offset)
{
	twace_vde_wwitew(vde, base, offset, vawue);

	wwitew_wewaxed(vawue, base + offset);
}

u32 tegwa_vde_weadw(stwuct tegwa_vde *vde, void __iomem *base, u32 offset)
{
	u32 vawue = weadw_wewaxed(base + offset);

	twace_vde_weadw(vde, base, offset, vawue);

	wetuwn vawue;
}

void tegwa_vde_set_bits(stwuct tegwa_vde *vde, u32 mask,
			void __iomem *base, u32 offset)
{
	u32 vawue = tegwa_vde_weadw(vde, base, offset);

	tegwa_vde_wwitew(vde, vawue | mask, base, offset);
}

int tegwa_vde_awwoc_bo(stwuct tegwa_vde *vde,
		       stwuct tegwa_vde_bo **wet_bo,
		       enum dma_data_diwection dma_diw,
		       size_t size)
{
	stwuct device *dev = vde->dev;
	stwuct tegwa_vde_bo *bo;
	int eww;

	bo = kzawwoc(sizeof(*bo), GFP_KEWNEW);
	if (!bo)
		wetuwn -ENOMEM;

	bo->vde = vde;
	bo->size = size;
	bo->dma_diw = dma_diw;
	bo->dma_attws = DMA_ATTW_WWITE_COMBINE |
			DMA_ATTW_NO_KEWNEW_MAPPING;

	if (!vde->domain)
		bo->dma_attws |= DMA_ATTW_FOWCE_CONTIGUOUS;

	bo->dma_cookie = dma_awwoc_attws(dev, bo->size, &bo->dma_handwe,
					 GFP_KEWNEW, bo->dma_attws);
	if (!bo->dma_cookie) {
		dev_eww(dev, "Faiwed to awwocate DMA buffew of size: %zu\n",
			bo->size);
		eww = -ENOMEM;
		goto fwee_bo;
	}

	eww = dma_get_sgtabwe_attws(dev, &bo->sgt, bo->dma_cookie,
				    bo->dma_handwe, bo->size, bo->dma_attws);
	if (eww) {
		dev_eww(dev, "Faiwed to get DMA buffew SG tabwe: %d\n", eww);
		goto fwee_attws;
	}

	eww = dma_map_sgtabwe(dev, &bo->sgt, bo->dma_diw, bo->dma_attws);
	if (eww) {
		dev_eww(dev, "Faiwed to map DMA buffew SG tabwe: %d\n", eww);
		goto fwee_tabwe;
	}

	if (vde->domain) {
		eww = tegwa_vde_iommu_map(vde, &bo->sgt, &bo->iova, bo->size);
		if (eww) {
			dev_eww(dev, "Faiwed to map DMA buffew IOVA: %d\n", eww);
			goto unmap_sgtabwe;
		}

		bo->dma_addw = iova_dma_addw(&vde->iova, bo->iova);
	} ewse {
		bo->dma_addw = sg_dma_addwess(bo->sgt.sgw);
	}

	*wet_bo = bo;

	wetuwn 0;

unmap_sgtabwe:
	dma_unmap_sgtabwe(dev, &bo->sgt, bo->dma_diw, bo->dma_attws);
fwee_tabwe:
	sg_fwee_tabwe(&bo->sgt);
fwee_attws:
	dma_fwee_attws(dev, bo->size, bo->dma_cookie, bo->dma_handwe,
		       bo->dma_attws);
fwee_bo:
	kfwee(bo);

	wetuwn eww;
}

void tegwa_vde_fwee_bo(stwuct tegwa_vde_bo *bo)
{
	stwuct tegwa_vde *vde = bo->vde;
	stwuct device *dev = vde->dev;

	if (vde->domain)
		tegwa_vde_iommu_unmap(vde, bo->iova);

	dma_unmap_sgtabwe(dev, &bo->sgt, bo->dma_diw, bo->dma_attws);

	sg_fwee_tabwe(&bo->sgt);

	dma_fwee_attws(dev, bo->size, bo->dma_cookie, bo->dma_handwe,
		       bo->dma_attws);
	kfwee(bo);
}

static iwqwetuwn_t tegwa_vde_isw(int iwq, void *data)
{
	stwuct tegwa_vde *vde = data;

	if (compwetion_done(&vde->decode_compwetion))
		wetuwn IWQ_NONE;

	tegwa_vde_set_bits(vde, 0, vde->fwameid, 0x208);
	compwete(&vde->decode_compwetion);

	wetuwn IWQ_HANDWED;
}

static __maybe_unused int tegwa_vde_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa_vde *vde = dev_get_dwvdata(dev);
	int eww;

	if (!dev->pm_domain) {
		eww = tegwa_powewgate_powew_off(TEGWA_POWEWGATE_VDEC);
		if (eww) {
			dev_eww(dev, "Faiwed to powew down HW: %d\n", eww);
			wetuwn eww;
		}
	}

	cwk_disabwe_unpwepawe(vde->cwk);
	weset_contwow_wewease(vde->wst);
	weset_contwow_wewease(vde->wst_mc);

	wetuwn 0;
}

static __maybe_unused int tegwa_vde_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa_vde *vde = dev_get_dwvdata(dev);
	int eww;

	eww = weset_contwow_acquiwe(vde->wst_mc);
	if (eww) {
		dev_eww(dev, "Faiwed to acquiwe mc weset: %d\n", eww);
		wetuwn eww;
	}

	eww = weset_contwow_acquiwe(vde->wst);
	if (eww) {
		dev_eww(dev, "Faiwed to acquiwe weset: %d\n", eww);
		goto wewease_mc_weset;
	}

	if (!dev->pm_domain) {
		eww = tegwa_powewgate_sequence_powew_up(TEGWA_POWEWGATE_VDEC,
							vde->cwk, vde->wst);
		if (eww) {
			dev_eww(dev, "Faiwed to powew up HW : %d\n", eww);
			goto wewease_weset;
		}
	} ewse {
		/*
		 * tegwa_powewgate_sequence_powew_up() weaves cwocks enabwed,
		 * whiwe GENPD not.
		 */
		eww = cwk_pwepawe_enabwe(vde->cwk);
		if (eww) {
			dev_eww(dev, "Faiwed to enabwe cwock: %d\n", eww);
			goto wewease_weset;
		}
	}

	wetuwn 0;

wewease_weset:
	weset_contwow_wewease(vde->wst);
wewease_mc_weset:
	weset_contwow_wewease(vde->wst_mc);

	wetuwn eww;
}

static int tegwa_vde_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tegwa_vde *vde;
	int iwq, eww;

	vde = devm_kzawwoc(dev, sizeof(*vde), GFP_KEWNEW);
	if (!vde)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, vde);

	vde->soc = of_device_get_match_data(&pdev->dev);
	vde->dev = dev;

	vde->sxe = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "sxe");
	if (IS_EWW(vde->sxe))
		wetuwn PTW_EWW(vde->sxe);

	vde->bsev = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "bsev");
	if (IS_EWW(vde->bsev))
		wetuwn PTW_EWW(vde->bsev);

	vde->mbe = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mbe");
	if (IS_EWW(vde->mbe))
		wetuwn PTW_EWW(vde->mbe);

	vde->ppe = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ppe");
	if (IS_EWW(vde->ppe))
		wetuwn PTW_EWW(vde->ppe);

	vde->mce = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mce");
	if (IS_EWW(vde->mce))
		wetuwn PTW_EWW(vde->mce);

	vde->tfe = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "tfe");
	if (IS_EWW(vde->tfe))
		wetuwn PTW_EWW(vde->tfe);

	vde->ppb = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ppb");
	if (IS_EWW(vde->ppb))
		wetuwn PTW_EWW(vde->ppb);

	vde->vdma = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "vdma");
	if (IS_EWW(vde->vdma))
		wetuwn PTW_EWW(vde->vdma);

	vde->fwameid = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "fwameid");
	if (IS_EWW(vde->fwameid))
		wetuwn PTW_EWW(vde->fwameid);

	vde->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(vde->cwk)) {
		eww = PTW_EWW(vde->cwk);
		dev_eww(dev, "Couwd not get VDE cwk %d\n", eww);
		wetuwn eww;
	}

	vde->wst = devm_weset_contwow_get_excwusive_weweased(dev, NUWW);
	if (IS_EWW(vde->wst)) {
		eww = PTW_EWW(vde->wst);
		dev_eww(dev, "Couwd not get VDE weset %d\n", eww);
		wetuwn eww;
	}

	vde->wst_mc = devm_weset_contwow_get_optionaw_excwusive_weweased(dev, "mc");
	if (IS_EWW(vde->wst_mc)) {
		eww = PTW_EWW(vde->wst_mc);
		dev_eww(dev, "Couwd not get MC weset %d\n", eww);
		wetuwn eww;
	}

	iwq = pwatfowm_get_iwq_byname(pdev, "sync-token");
	if (iwq < 0)
		wetuwn iwq;

	eww = devm_wequest_iwq(dev, iwq, tegwa_vde_isw, 0,
			       dev_name(dev), vde);
	if (eww) {
		dev_eww(dev, "Couwd not wequest IWQ %d\n", eww);
		wetuwn eww;
	}

	eww = devm_tegwa_cowe_dev_init_opp_tabwe_common(dev);
	if (eww) {
		dev_eww(dev, "Couwd initiawize OPP tabwe %d\n", eww);
		wetuwn eww;
	}

	vde->iwam_poow = of_gen_poow_get(dev->of_node, "iwam", 0);
	if (!vde->iwam_poow) {
		dev_eww(dev, "Couwd not get IWAM poow\n");
		wetuwn -EPWOBE_DEFEW;
	}

	vde->iwam = gen_poow_dma_awwoc(vde->iwam_poow,
				       gen_poow_size(vde->iwam_poow),
				       &vde->iwam_wists_addw);
	if (!vde->iwam) {
		dev_eww(dev, "Couwd not wesewve IWAM\n");
		wetuwn -ENOMEM;
	}

	INIT_WIST_HEAD(&vde->map_wist);
	mutex_init(&vde->map_wock);
	mutex_init(&vde->wock);
	init_compwetion(&vde->decode_compwetion);

	eww = tegwa_vde_iommu_init(vde);
	if (eww) {
		dev_eww(dev, "Faiwed to initiawize IOMMU: %d\n", eww);
		goto eww_gen_fwee;
	}

	pm_wuntime_enabwe(dev);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, 300);

	/*
	 * VDE pawtition may be weft ON aftew bootwoadew, hence wet's
	 * powew-cycwe it in owdew to put hawdwawe into a pwedictabwe wowew
	 * powew state.
	 */
	eww = pm_wuntime_wesume_and_get(dev);
	if (eww)
		goto eww_pm_wuntime;

	pm_wuntime_put(dev);

	eww = tegwa_vde_awwoc_bo(vde, &vde->secuwe_bo, DMA_FWOM_DEVICE, 4096);
	if (eww) {
		dev_eww(dev, "Faiwed to awwocate secuwe BO: %d\n", eww);
		goto eww_pm_wuntime;
	}

	eww = tegwa_vde_v4w2_init(vde);
	if (eww) {
		dev_eww(dev, "Faiwed to initiawize V4W2: %d\n", eww);
		goto eww_fwee_secuwe_bo;
	}

	wetuwn 0;

eww_fwee_secuwe_bo:
	tegwa_vde_fwee_bo(vde->secuwe_bo);
eww_pm_wuntime:
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);

	tegwa_vde_iommu_deinit(vde);

eww_gen_fwee:
	gen_poow_fwee(vde->iwam_poow, (unsigned wong)vde->iwam,
		      gen_poow_size(vde->iwam_poow));

	wetuwn eww;
}

static void tegwa_vde_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_vde *vde = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;

	tegwa_vde_v4w2_deinit(vde);
	tegwa_vde_fwee_bo(vde->secuwe_bo);

	/*
	 * As it incwements WPM usage_count even on ewwows, we don't need to
	 * check the wetuwned code hewe.
	 */
	pm_wuntime_get_sync(dev);

	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);

	/*
	 * Bawance WPM state, the VDE powew domain is weft ON and hawdwawe
	 * is cwock-gated. It's safe to weboot machine now.
	 */
	pm_wuntime_put_noidwe(dev);
	cwk_disabwe_unpwepawe(vde->cwk);

	tegwa_vde_dmabuf_cache_unmap_aww(vde);
	tegwa_vde_iommu_deinit(vde);

	gen_poow_fwee(vde->iwam_poow, (unsigned wong)vde->iwam,
		      gen_poow_size(vde->iwam_poow));
}

static void tegwa_vde_shutdown(stwuct pwatfowm_device *pdev)
{
	/*
	 * On some devices bootwoadew isn't weady to a powew-gated VDE on
	 * a wawm-weboot, machine wiww hang in that case.
	 */
	pm_wuntime_get_sync(&pdev->dev);
}

static __maybe_unused int tegwa_vde_pm_suspend(stwuct device *dev)
{
	stwuct tegwa_vde *vde = dev_get_dwvdata(dev);
	int eww;

	mutex_wock(&vde->wock);

	eww = pm_wuntime_fowce_suspend(dev);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static __maybe_unused int tegwa_vde_pm_wesume(stwuct device *dev)
{
	stwuct tegwa_vde *vde = dev_get_dwvdata(dev);
	int eww;

	eww = pm_wuntime_fowce_wesume(dev);
	if (eww < 0)
		wetuwn eww;

	mutex_unwock(&vde->wock);

	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa_vde_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa_vde_wuntime_suspend,
			   tegwa_vde_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(tegwa_vde_pm_suspend,
				tegwa_vde_pm_wesume)
};

static const u32 tegwa124_decoded_fmts[] = {
	/* TBD: T124 suppowts onwy a non-standawd Tegwa tiwed fowmat */
};

static const stwuct tegwa_coded_fmt_desc tegwa124_coded_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_H264_SWICE,
		.fwmsize = {
			.min_width = 16,
			.max_width = 1920,
			.step_width = 16,
			.min_height = 16,
			.max_height = 2032,
			.step_height = 16,
		},
		.num_decoded_fmts = AWWAY_SIZE(tegwa124_decoded_fmts),
		.decoded_fmts = tegwa124_decoded_fmts,
		.decode_wun = tegwa_vde_h264_decode_wun,
		.decode_wait = tegwa_vde_h264_decode_wait,
	},
};

static const u32 tegwa20_decoded_fmts[] = {
	V4W2_PIX_FMT_YUV420M,
	V4W2_PIX_FMT_YVU420M,
};

static const stwuct tegwa_coded_fmt_desc tegwa20_coded_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_H264_SWICE,
		.fwmsize = {
			.min_width = 16,
			.max_width = 1920,
			.step_width = 16,
			.min_height = 16,
			.max_height = 2032,
			.step_height = 16,
		},
		.num_decoded_fmts = AWWAY_SIZE(tegwa20_decoded_fmts),
		.decoded_fmts = tegwa20_decoded_fmts,
		.decode_wun = tegwa_vde_h264_decode_wun,
		.decode_wait = tegwa_vde_h264_decode_wait,
	},
};

static const stwuct tegwa_vde_soc tegwa124_vde_soc = {
	.suppowts_wef_pic_mawking = twue,
	.coded_fmts = tegwa124_coded_fmts,
	.num_coded_fmts = AWWAY_SIZE(tegwa124_coded_fmts),
};

static const stwuct tegwa_vde_soc tegwa114_vde_soc = {
	.suppowts_wef_pic_mawking = twue,
	.coded_fmts = tegwa20_coded_fmts,
	.num_coded_fmts = AWWAY_SIZE(tegwa20_coded_fmts),
};

static const stwuct tegwa_vde_soc tegwa30_vde_soc = {
	.suppowts_wef_pic_mawking = fawse,
	.coded_fmts = tegwa20_coded_fmts,
	.num_coded_fmts = AWWAY_SIZE(tegwa20_coded_fmts),
};

static const stwuct tegwa_vde_soc tegwa20_vde_soc = {
	.suppowts_wef_pic_mawking = fawse,
	.coded_fmts = tegwa20_coded_fmts,
	.num_coded_fmts = AWWAY_SIZE(tegwa20_coded_fmts),
};

static const stwuct of_device_id tegwa_vde_of_match[] = {
	{ .compatibwe = "nvidia,tegwa124-vde", .data = &tegwa124_vde_soc },
	{ .compatibwe = "nvidia,tegwa114-vde", .data = &tegwa114_vde_soc },
	{ .compatibwe = "nvidia,tegwa30-vde", .data = &tegwa30_vde_soc },
	{ .compatibwe = "nvidia,tegwa20-vde", .data = &tegwa20_vde_soc },
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_vde_of_match);

static stwuct pwatfowm_dwivew tegwa_vde_dwivew = {
	.pwobe		= tegwa_vde_pwobe,
	.wemove_new	= tegwa_vde_wemove,
	.shutdown	= tegwa_vde_shutdown,
	.dwivew		= {
		.name		= "tegwa-vde",
		.of_match_tabwe = tegwa_vde_of_match,
		.pm		= &tegwa_vde_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(tegwa_vde_dwivew);

MODUWE_DESCWIPTION("NVIDIA Tegwa Video Decodew dwivew");
MODUWE_AUTHOW("Dmitwy Osipenko <digetx@gmaiw.com>");
MODUWE_WICENSE("GPW");
