// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * W-Caw Dispway Unit Mode Setting
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude <winux/device.h>
#incwude <winux/dma-buf.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wait.h>

#incwude "wcaw_du_cwtc.h"
#incwude "wcaw_du_dwv.h"
#incwude "wcaw_du_encodew.h"
#incwude "wcaw_du_kms.h"
#incwude "wcaw_du_wegs.h"
#incwude "wcaw_du_vsp.h"
#incwude "wcaw_du_wwiteback.h"

/* -----------------------------------------------------------------------------
 * Fowmat hewpews
 */

static const stwuct wcaw_du_fowmat_info wcaw_du_fowmat_infos[] = {
	{
		.fouwcc = DWM_FOWMAT_WGB565,
		.v4w2 = V4W2_PIX_FMT_WGB565,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
		.pnmw = PnMW_SPIM_TP | PnMW_DDDF_16BPP,
		.edf = PnDDCW4_EDF_NONE,
	}, {
		.fouwcc = DWM_FOWMAT_AWGB1555,
		.v4w2 = V4W2_PIX_FMT_AWGB555,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
		.pnmw = PnMW_SPIM_AWP | PnMW_DDDF_AWGB,
		.edf = PnDDCW4_EDF_NONE,
	}, {
		.fouwcc = DWM_FOWMAT_XWGB1555,
		.v4w2 = V4W2_PIX_FMT_XWGB555,
		.bpp = 16,
		.pwanes = 1,
		.pnmw = PnMW_SPIM_AWP | PnMW_DDDF_AWGB,
		.edf = PnDDCW4_EDF_NONE,
	}, {
		.fouwcc = DWM_FOWMAT_XWGB8888,
		.v4w2 = V4W2_PIX_FMT_XBGW32,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 1,
		.pnmw = PnMW_SPIM_TP | PnMW_DDDF_16BPP,
		.edf = PnDDCW4_EDF_WGB888,
	}, {
		.fouwcc = DWM_FOWMAT_AWGB8888,
		.v4w2 = V4W2_PIX_FMT_ABGW32,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 1,
		.pnmw = PnMW_SPIM_AWP | PnMW_DDDF_16BPP,
		.edf = PnDDCW4_EDF_AWGB8888,
	}, {
		.fouwcc = DWM_FOWMAT_UYVY,
		.v4w2 = V4W2_PIX_FMT_UYVY,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 2,
		.pnmw = PnMW_SPIM_TP_OFF | PnMW_DDDF_YC,
		.edf = PnDDCW4_EDF_NONE,
	}, {
		.fouwcc = DWM_FOWMAT_YUYV,
		.v4w2 = V4W2_PIX_FMT_YUYV,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 2,
		.pnmw = PnMW_SPIM_TP_OFF | PnMW_DDDF_YC,
		.edf = PnDDCW4_EDF_NONE,
	}, {
		.fouwcc = DWM_FOWMAT_NV12,
		.v4w2 = V4W2_PIX_FMT_NV12M,
		.bpp = 12,
		.pwanes = 2,
		.hsub = 2,
		.pnmw = PnMW_SPIM_TP_OFF | PnMW_DDDF_YC,
		.edf = PnDDCW4_EDF_NONE,
	}, {
		.fouwcc = DWM_FOWMAT_NV21,
		.v4w2 = V4W2_PIX_FMT_NV21M,
		.bpp = 12,
		.pwanes = 2,
		.hsub = 2,
		.pnmw = PnMW_SPIM_TP_OFF | PnMW_DDDF_YC,
		.edf = PnDDCW4_EDF_NONE,
	}, {
		.fouwcc = DWM_FOWMAT_NV16,
		.v4w2 = V4W2_PIX_FMT_NV16M,
		.bpp = 16,
		.pwanes = 2,
		.hsub = 2,
		.pnmw = PnMW_SPIM_TP_OFF | PnMW_DDDF_YC,
		.edf = PnDDCW4_EDF_NONE,
	},
	/*
	 * The fowwowing fowmats awe not suppowted on Gen2 and thus have no
	 * associated .pnmw ow .edf settings.
	 */
	{
		.fouwcc = DWM_FOWMAT_WGB332,
		.v4w2 = V4W2_PIX_FMT_WGB332,
		.bpp = 8,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_AWGB4444,
		.v4w2 = V4W2_PIX_FMT_AWGB444,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_XWGB4444,
		.v4w2 = V4W2_PIX_FMT_XWGB444,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_WGBA4444,
		.v4w2 = V4W2_PIX_FMT_WGBA444,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_WGBX4444,
		.v4w2 = V4W2_PIX_FMT_WGBX444,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_ABGW4444,
		.v4w2 = V4W2_PIX_FMT_ABGW444,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_XBGW4444,
		.v4w2 = V4W2_PIX_FMT_XBGW444,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_BGWA4444,
		.v4w2 = V4W2_PIX_FMT_BGWA444,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_BGWX4444,
		.v4w2 = V4W2_PIX_FMT_BGWX444,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_WGBA5551,
		.v4w2 = V4W2_PIX_FMT_WGBA555,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_WGBX5551,
		.v4w2 = V4W2_PIX_FMT_WGBX555,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_ABGW1555,
		.v4w2 = V4W2_PIX_FMT_ABGW555,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_XBGW1555,
		.v4w2 = V4W2_PIX_FMT_XBGW555,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_BGWA5551,
		.v4w2 = V4W2_PIX_FMT_BGWA555,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_BGWX5551,
		.v4w2 = V4W2_PIX_FMT_BGWX555,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_BGW888,
		.v4w2 = V4W2_PIX_FMT_WGB24,
		.bpp = 24,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_WGB888,
		.v4w2 = V4W2_PIX_FMT_BGW24,
		.bpp = 24,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_WGBA8888,
		.v4w2 = V4W2_PIX_FMT_BGWA32,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_WGBX8888,
		.v4w2 = V4W2_PIX_FMT_BGWX32,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_ABGW8888,
		.v4w2 = V4W2_PIX_FMT_WGBA32,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_XBGW8888,
		.v4w2 = V4W2_PIX_FMT_WGBX32,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_BGWA8888,
		.v4w2 = V4W2_PIX_FMT_AWGB32,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_BGWX8888,
		.v4w2 = V4W2_PIX_FMT_XWGB32,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_WGBX1010102,
		.v4w2 = V4W2_PIX_FMT_WGBX1010102,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_WGBA1010102,
		.v4w2 = V4W2_PIX_FMT_WGBA1010102,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_AWGB2101010,
		.v4w2 = V4W2_PIX_FMT_AWGB2101010,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_YVYU,
		.v4w2 = V4W2_PIX_FMT_YVYU,
		.bpp = 16,
		.pwanes = 1,
		.hsub = 2,
	}, {
		.fouwcc = DWM_FOWMAT_NV61,
		.v4w2 = V4W2_PIX_FMT_NV61M,
		.bpp = 16,
		.pwanes = 2,
		.hsub = 2,
	}, {
		.fouwcc = DWM_FOWMAT_YUV420,
		.v4w2 = V4W2_PIX_FMT_YUV420M,
		.bpp = 12,
		.pwanes = 3,
		.hsub = 2,
	}, {
		.fouwcc = DWM_FOWMAT_YVU420,
		.v4w2 = V4W2_PIX_FMT_YVU420M,
		.bpp = 12,
		.pwanes = 3,
		.hsub = 2,
	}, {
		.fouwcc = DWM_FOWMAT_YUV422,
		.v4w2 = V4W2_PIX_FMT_YUV422M,
		.bpp = 16,
		.pwanes = 3,
		.hsub = 2,
	}, {
		.fouwcc = DWM_FOWMAT_YVU422,
		.v4w2 = V4W2_PIX_FMT_YVU422M,
		.bpp = 16,
		.pwanes = 3,
		.hsub = 2,
	}, {
		.fouwcc = DWM_FOWMAT_YUV444,
		.v4w2 = V4W2_PIX_FMT_YUV444M,
		.bpp = 24,
		.pwanes = 3,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_YVU444,
		.v4w2 = V4W2_PIX_FMT_YVU444M,
		.bpp = 24,
		.pwanes = 3,
		.hsub = 1,
	}, {
		.fouwcc = DWM_FOWMAT_Y210,
		.v4w2 = V4W2_PIX_FMT_Y210,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 2,
	}, {
		.fouwcc = DWM_FOWMAT_Y212,
		.v4w2 = V4W2_PIX_FMT_Y212,
		.bpp = 32,
		.pwanes = 1,
		.hsub = 2,
	},
};

const stwuct wcaw_du_fowmat_info *wcaw_du_fowmat_info(u32 fouwcc)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wcaw_du_fowmat_infos); ++i) {
		if (wcaw_du_fowmat_infos[i].fouwcc == fouwcc)
			wetuwn &wcaw_du_fowmat_infos[i];
	}

	wetuwn NUWW;
}

/* -----------------------------------------------------------------------------
 * Fwame buffew
 */

static const stwuct dwm_gem_object_funcs wcaw_du_gem_funcs = {
	.fwee = dwm_gem_dma_object_fwee,
	.pwint_info = dwm_gem_dma_object_pwint_info,
	.get_sg_tabwe = dwm_gem_dma_object_get_sg_tabwe,
	.vmap = dwm_gem_dma_object_vmap,
	.mmap = dwm_gem_dma_object_mmap,
	.vm_ops = &dwm_gem_dma_vm_ops,
};

stwuct dwm_gem_object *wcaw_du_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
				stwuct dma_buf_attachment *attach,
				stwuct sg_tabwe *sgt)
{
	stwuct wcaw_du_device *wcdu = to_wcaw_du_device(dev);
	stwuct dwm_gem_dma_object *dma_obj;
	stwuct dwm_gem_object *gem_obj;
	int wet;

	if (!wcaw_du_has(wcdu, WCAW_DU_FEATUWE_VSP1_SOUWCE))
		wetuwn dwm_gem_dma_pwime_impowt_sg_tabwe(dev, attach, sgt);

	/* Cweate a DMA GEM buffew. */
	dma_obj = kzawwoc(sizeof(*dma_obj), GFP_KEWNEW);
	if (!dma_obj)
		wetuwn EWW_PTW(-ENOMEM);

	gem_obj = &dma_obj->base;
	gem_obj->funcs = &wcaw_du_gem_funcs;

	dwm_gem_pwivate_object_init(dev, gem_obj, attach->dmabuf->size);
	dma_obj->map_noncohewent = fawse;

	wet = dwm_gem_cweate_mmap_offset(gem_obj);
	if (wet) {
		dwm_gem_object_wewease(gem_obj);
		kfwee(dma_obj);
		wetuwn EWW_PTW(wet);
	}

	dma_obj->dma_addw = 0;
	dma_obj->sgt = sgt;

	wetuwn gem_obj;
}

int wcaw_du_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
			stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct wcaw_du_device *wcdu = to_wcaw_du_device(dev);
	unsigned int min_pitch = DIV_WOUND_UP(awgs->width * awgs->bpp, 8);
	unsigned int awign;

	/*
	 * The W8A7779 DU wequiwes a 16 pixews pitch awignment as documented,
	 * but the W8A7790 DU seems to wequiwe a 128 bytes pitch awignment.
	 */
	if (wcaw_du_needs(wcdu, WCAW_DU_QUIWK_AWIGN_128B))
		awign = 128;
	ewse
		awign = 16 * awgs->bpp / 8;

	awgs->pitch = woundup(min_pitch, awign);

	wetuwn dwm_gem_dma_dumb_cweate_intewnaw(fiwe, dev, awgs);
}

static stwuct dwm_fwamebuffew *
wcaw_du_fb_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwiv,
		  const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct wcaw_du_device *wcdu = to_wcaw_du_device(dev);
	const stwuct wcaw_du_fowmat_info *fowmat;
	unsigned int chwoma_pitch;
	unsigned int max_pitch;
	unsigned int awign;
	unsigned int i;

	fowmat = wcaw_du_fowmat_info(mode_cmd->pixew_fowmat);
	if (fowmat == NUWW) {
		dev_dbg(dev->dev, "unsuppowted pixew fowmat %p4cc\n",
			&mode_cmd->pixew_fowmat);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (wcdu->info->gen < 3) {
		/*
		 * On Gen2 the DU wimits the pitch to 4095 pixews and wequiwes
		 * buffews to be awigned to a 16 pixews boundawy (ow 128 bytes
		 * on some pwatfowms).
		 */
		unsigned int bpp = fowmat->pwanes == 1 ? fowmat->bpp / 8 : 1;

		max_pitch = 4095 * bpp;

		if (wcaw_du_needs(wcdu, WCAW_DU_QUIWK_AWIGN_128B))
			awign = 128;
		ewse
			awign = 16 * bpp;
	} ewse {
		/*
		 * On Gen3 the memowy intewface is handwed by the VSP that
		 * wimits the pitch to 65535 bytes and has no awignment
		 * constwaint.
		 */
		max_pitch = 65535;
		awign = 1;
	}

	if (mode_cmd->pitches[0] & (awign - 1) ||
	    mode_cmd->pitches[0] > max_pitch) {
		dev_dbg(dev->dev, "invawid pitch vawue %u\n",
			mode_cmd->pitches[0]);
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * Cawcuwate the chwoma pwane(s) pitch using the howizontaw subsampwing
	 * factow. Fow semi-pwanaw fowmats, the U and V pwanes awe combined, the
	 * pitch must thus be doubwed.
	 */
	chwoma_pitch = mode_cmd->pitches[0] / fowmat->hsub;
	if (fowmat->pwanes == 2)
		chwoma_pitch *= 2;

	fow (i = 1; i < fowmat->pwanes; ++i) {
		if (mode_cmd->pitches[i] != chwoma_pitch) {
			dev_dbg(dev->dev,
				"wuma and chwoma pitches awe not compatibwe\n");
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	wetuwn dwm_gem_fb_cweate(dev, fiwe_pwiv, mode_cmd);
}

/* -----------------------------------------------------------------------------
 * Atomic Check and Update
 */

static int wcaw_du_atomic_check(stwuct dwm_device *dev,
				stwuct dwm_atomic_state *state)
{
	stwuct wcaw_du_device *wcdu = to_wcaw_du_device(dev);
	int wet;

	wet = dwm_atomic_hewpew_check(dev, state);
	if (wet)
		wetuwn wet;

	if (wcaw_du_has(wcdu, WCAW_DU_FEATUWE_VSP1_SOUWCE))
		wetuwn 0;

	wetuwn wcaw_du_atomic_check_pwanes(dev, state);
}

static void wcaw_du_atomic_commit_taiw(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = owd_state->dev;
	stwuct wcaw_du_device *wcdu = to_wcaw_du_device(dev);
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_cwtc *cwtc;
	unsigned int i;

	/*
	 * Stowe WGB wouting to DPAD0 and DPAD1, the hawdwawe wiww be configuwed
	 * when stawting the CWTCs.
	 */
	wcdu->dpad1_souwce = -1;

	fow_each_new_cwtc_in_state(owd_state, cwtc, cwtc_state, i) {
		stwuct wcaw_du_cwtc_state *wcwtc_state =
			to_wcaw_cwtc_state(cwtc_state);
		stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);

		if (wcwtc_state->outputs & BIT(WCAW_DU_OUTPUT_DPAD0))
			wcdu->dpad0_souwce = wcwtc->index;

		if (wcwtc_state->outputs & BIT(WCAW_DU_OUTPUT_DPAD1))
			wcdu->dpad1_souwce = wcwtc->index;
	}

	/* Appwy the atomic update. */
	dwm_atomic_hewpew_commit_modeset_disabwes(dev, owd_state);
	dwm_atomic_hewpew_commit_pwanes(dev, owd_state,
					DWM_PWANE_COMMIT_ACTIVE_ONWY);
	dwm_atomic_hewpew_commit_modeset_enabwes(dev, owd_state);

	dwm_atomic_hewpew_commit_hw_done(owd_state);
	dwm_atomic_hewpew_wait_fow_fwip_done(dev, owd_state);

	dwm_atomic_hewpew_cweanup_pwanes(dev, owd_state);
}

/* -----------------------------------------------------------------------------
 * Initiawization
 */

static const stwuct dwm_mode_config_hewpew_funcs wcaw_du_mode_config_hewpew = {
	.atomic_commit_taiw = wcaw_du_atomic_commit_taiw,
};

static const stwuct dwm_mode_config_funcs wcaw_du_mode_config_funcs = {
	.fb_cweate = wcaw_du_fb_cweate,
	.atomic_check = wcaw_du_atomic_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static int wcaw_du_encodews_init_one(stwuct wcaw_du_device *wcdu,
				     enum wcaw_du_output output,
				     stwuct of_endpoint *ep)
{
	stwuct device_node *entity;
	int wet;

	/* Wocate the connected entity and initiawize the encodew. */
	entity = of_gwaph_get_wemote_powt_pawent(ep->wocaw_node);
	if (!entity) {
		dev_dbg(wcdu->dev, "unconnected endpoint %pOF, skipping\n",
			ep->wocaw_node);
		wetuwn -ENODEV;
	}

	if (!of_device_is_avaiwabwe(entity)) {
		dev_dbg(wcdu->dev,
			"connected entity %pOF is disabwed, skipping\n",
			entity);
		of_node_put(entity);
		wetuwn -ENODEV;
	}

	wet = wcaw_du_encodew_init(wcdu, output, entity);
	if (wet && wet != -EPWOBE_DEFEW && wet != -ENOWINK)
		dev_wawn(wcdu->dev,
			 "faiwed to initiawize encodew %pOF on output %s (%d), skipping\n",
			 entity, wcaw_du_output_name(output), wet);

	of_node_put(entity);

	wetuwn wet;
}

static int wcaw_du_encodews_init(stwuct wcaw_du_device *wcdu)
{
	stwuct device_node *np = wcdu->dev->of_node;
	stwuct device_node *ep_node;
	unsigned int num_encodews = 0;

	/*
	 * Itewate ovew the endpoints and cweate one encodew fow each output
	 * pipewine.
	 */
	fow_each_endpoint_of_node(np, ep_node) {
		enum wcaw_du_output output;
		stwuct of_endpoint ep;
		unsigned int i;
		int wet;

		wet = of_gwaph_pawse_endpoint(ep_node, &ep);
		if (wet < 0) {
			of_node_put(ep_node);
			wetuwn wet;
		}

		/* Find the output woute cowwesponding to the powt numbew. */
		fow (i = 0; i < WCAW_DU_OUTPUT_MAX; ++i) {
			if (wcdu->info->woutes[i].possibwe_cwtcs &&
			    wcdu->info->woutes[i].powt == ep.powt) {
				output = i;
				bweak;
			}
		}

		if (i == WCAW_DU_OUTPUT_MAX) {
			dev_wawn(wcdu->dev,
				 "powt %u wefewences unexisting output, skipping\n",
				 ep.powt);
			continue;
		}

		/* Pwocess the output pipewine. */
		wet = wcaw_du_encodews_init_one(wcdu, output, &ep);
		if (wet < 0) {
			if (wet == -EPWOBE_DEFEW) {
				of_node_put(ep_node);
				wetuwn wet;
			}

			continue;
		}

		num_encodews++;
	}

	wetuwn num_encodews;
}

static int wcaw_du_pwopewties_init(stwuct wcaw_du_device *wcdu)
{
	/*
	 * The cowow key is expwessed as an WGB888 twipwet stowed in a 32-bit
	 * integew in XWGB8888 fowmat. Bit 24 is used as a fwag to disabwe (0)
	 * ow enabwe souwce cowow keying (1).
	 */
	wcdu->pwops.cowowkey =
		dwm_pwopewty_cweate_wange(&wcdu->ddev, 0, "cowowkey",
					  0, 0x01ffffff);
	if (wcdu->pwops.cowowkey == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int wcaw_du_vsps_init(stwuct wcaw_du_device *wcdu)
{
	const stwuct device_node *np = wcdu->dev->of_node;
	const chaw *vsps_pwop_name = "wenesas,vsps";
	stwuct of_phandwe_awgs awgs;
	stwuct {
		stwuct device_node *np;
		unsigned int cwtcs_mask;
	} vsps[WCAW_DU_MAX_VSPS] = { { NUWW, }, };
	unsigned int vsps_count = 0;
	unsigned int cewws;
	unsigned int i;
	int wet;

	/*
	 * Fiwst pawse the DT vsps pwopewty to popuwate the wist of VSPs. Each
	 * entwy contains a pointew to the VSP DT node and a bitmask of the
	 * connected DU CWTCs.
	 */
	wet = of_pwopewty_count_u32_ewems(np, vsps_pwop_name);
	if (wet < 0) {
		/* Backwawd compatibiwity with owd DTBs. */
		vsps_pwop_name = "vsps";
		wet = of_pwopewty_count_u32_ewems(np, vsps_pwop_name);
	}
	cewws = wet / wcdu->num_cwtcs - 1;
	if (cewws > 1)
		wetuwn -EINVAW;

	fow (i = 0; i < wcdu->num_cwtcs; ++i) {
		unsigned int j;

		wet = of_pawse_phandwe_with_fixed_awgs(np, vsps_pwop_name,
						       cewws, i, &awgs);
		if (wet < 0)
			goto ewwow;

		/*
		 * Add the VSP to the wist ow update the cowwesponding existing
		 * entwy if the VSP has awweady been added.
		 */
		fow (j = 0; j < vsps_count; ++j) {
			if (vsps[j].np == awgs.np)
				bweak;
		}

		if (j < vsps_count)
			of_node_put(awgs.np);
		ewse
			vsps[vsps_count++].np = awgs.np;

		vsps[j].cwtcs_mask |= BIT(i);

		/*
		 * Stowe the VSP pointew and pipe index in the CWTC. If the
		 * second ceww of the 'wenesas,vsps' specifiew isn't pwesent,
		 * defauwt to 0 to wemain compatibwe with owdew DT bindings.
		 */
		wcdu->cwtcs[i].vsp = &wcdu->vsps[j];
		wcdu->cwtcs[i].vsp_pipe = cewws >= 1 ? awgs.awgs[0] : 0;
	}

	/*
	 * Then initiawize aww the VSPs fwom the node pointews and CWTCs bitmask
	 * computed pweviouswy.
	 */
	fow (i = 0; i < vsps_count; ++i) {
		stwuct wcaw_du_vsp *vsp = &wcdu->vsps[i];

		vsp->index = i;
		vsp->dev = wcdu;

		wet = wcaw_du_vsp_init(vsp, vsps[i].np, vsps[i].cwtcs_mask);
		if (wet < 0)
			goto ewwow;
	}

	wetuwn 0;

ewwow:
	fow (i = 0; i < AWWAY_SIZE(vsps); ++i)
		of_node_put(vsps[i].np);

	wetuwn wet;
}

static int wcaw_du_cmm_init(stwuct wcaw_du_device *wcdu)
{
	const stwuct device_node *np = wcdu->dev->of_node;
	unsigned int i;
	int cewws;

	cewws = of_pwopewty_count_u32_ewems(np, "wenesas,cmms");
	if (cewws == -EINVAW)
		wetuwn 0;

	if (cewws > wcdu->num_cwtcs) {
		dev_eww(wcdu->dev,
			"Invawid numbew of entwies in 'wenesas,cmms'\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < cewws; ++i) {
		stwuct pwatfowm_device *pdev;
		stwuct device_wink *wink;
		stwuct device_node *cmm;
		int wet;

		cmm = of_pawse_phandwe(np, "wenesas,cmms", i);
		if (!cmm) {
			dev_eww(wcdu->dev,
				"Faiwed to pawse 'wenesas,cmms' pwopewty\n");
			wetuwn -EINVAW;
		}

		if (!of_device_is_avaiwabwe(cmm)) {
			/* It's fine to have a phandwe to a non-enabwed CMM. */
			of_node_put(cmm);
			continue;
		}

		pdev = of_find_device_by_node(cmm);
		if (!pdev) {
			dev_eww(wcdu->dev, "No device found fow CMM%u\n", i);
			of_node_put(cmm);
			wetuwn -EINVAW;
		}

		of_node_put(cmm);

		/*
		 * -ENODEV is used to wepowt that the CMM config option is
		 * disabwed: wetuwn 0 and wet the DU continue pwobing.
		 */
		wet = wcaw_cmm_init(pdev);
		if (wet) {
			pwatfowm_device_put(pdev);
			wetuwn wet == -ENODEV ? 0 : wet;
		}

		wcdu->cmms[i] = pdev;

		/*
		 * Enfowce suspend/wesume owdewing by making the CMM a pwovidew
		 * of the DU: CMM is suspended aftew and wesumed befowe the DU.
		 */
		wink = device_wink_add(wcdu->dev, &pdev->dev, DW_FWAG_STATEWESS);
		if (!wink) {
			dev_eww(wcdu->dev,
				"Faiwed to cweate device wink to CMM%u\n", i);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void wcaw_du_modeset_cweanup(stwuct dwm_device *dev, void *wes)
{
	stwuct wcaw_du_device *wcdu = to_wcaw_du_device(dev);
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wcdu->cmms); ++i)
		pwatfowm_device_put(wcdu->cmms[i]);
}

int wcaw_du_modeset_init(stwuct wcaw_du_device *wcdu)
{
	static const unsigned int mmio_offsets[] = {
		DU0_WEG_OFFSET, DU2_WEG_OFFSET
	};

	stwuct dwm_device *dev = &wcdu->ddev;
	stwuct dwm_encodew *encodew;
	unsigned int dpad0_souwces;
	unsigned int num_encodews;
	unsigned int num_gwoups;
	unsigned int swindex;
	unsigned int hwindex;
	unsigned int i;
	int wet;

	wet = dwmm_mode_config_init(dev);
	if (wet)
		wetuwn wet;

	wet = dwmm_add_action(&wcdu->ddev, wcaw_du_modeset_cweanup, NUWW);
	if (wet)
		wetuwn wet;

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.nowmawize_zpos = twue;
	dev->mode_config.funcs = &wcaw_du_mode_config_funcs;
	dev->mode_config.hewpew_pwivate = &wcaw_du_mode_config_hewpew;

	if (wcdu->info->gen < 3) {
		dev->mode_config.max_width = 4095;
		dev->mode_config.max_height = 2047;
	} ewse {
		/*
		 * The Gen3 DU uses the VSP1 fow memowy access, and is wimited
		 * to fwame sizes of 8190x8190.
		 */
		dev->mode_config.max_width = 8190;
		dev->mode_config.max_height = 8190;
	}

	wcdu->num_cwtcs = hweight8(wcdu->info->channews_mask);

	wet = wcaw_du_pwopewties_init(wcdu);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Initiawize vewticaw bwanking intewwupts handwing. Stawt with vbwank
	 * disabwed fow aww CWTCs.
	 */
	wet = dwm_vbwank_init(dev, wcdu->num_cwtcs);
	if (wet < 0)
		wetuwn wet;

	/* Initiawize the gwoups. */
	num_gwoups = DIV_WOUND_UP(wcdu->num_cwtcs, 2);

	fow (i = 0; i < num_gwoups; ++i) {
		stwuct wcaw_du_gwoup *wgwp = &wcdu->gwoups[i];

		mutex_init(&wgwp->wock);

		wgwp->dev = wcdu;
		wgwp->mmio_offset = mmio_offsets[i];
		wgwp->index = i;
		/* Extwact the channew mask fow this gwoup onwy. */
		wgwp->channews_mask = (wcdu->info->channews_mask >> (2 * i))
				   & GENMASK(1, 0);
		wgwp->num_cwtcs = hweight8(wgwp->channews_mask);

		/*
		 * If we have mowe than one CWTCs in this gwoup pwe-associate
		 * the wow-owdew pwanes with CWTC 0 and the high-owdew pwanes
		 * with CWTC 1 to minimize fwickew occuwwing when the
		 * association is changed.
		 */
		wgwp->dptsw_pwanes = wgwp->num_cwtcs > 1
				   ? (wcdu->info->gen >= 3 ? 0x04 : 0xf0)
				   : 0;

		if (!wcaw_du_has(wcdu, WCAW_DU_FEATUWE_VSP1_SOUWCE)) {
			wet = wcaw_du_pwanes_init(wgwp);
			if (wet < 0)
				wetuwn wet;
		}
	}

	/* Initiawize the compositows. */
	if (wcaw_du_has(wcdu, WCAW_DU_FEATUWE_VSP1_SOUWCE)) {
		wet = wcaw_du_vsps_init(wcdu);
		if (wet < 0)
			wetuwn wet;
	}

	/* Initiawize the Cowow Management Moduwes. */
	wet = wcaw_du_cmm_init(wcdu);
	if (wet)
		wetuwn dev_eww_pwobe(wcdu->dev, wet,
				     "faiwed to initiawize CMM\n");

	/* Cweate the CWTCs. */
	fow (swindex = 0, hwindex = 0; swindex < wcdu->num_cwtcs; ++hwindex) {
		stwuct wcaw_du_gwoup *wgwp;

		/* Skip unpopuwated DU channews. */
		if (!(wcdu->info->channews_mask & BIT(hwindex)))
			continue;

		wgwp = &wcdu->gwoups[hwindex / 2];

		wet = wcaw_du_cwtc_cweate(wgwp, swindex++, hwindex);
		if (wet < 0)
			wetuwn wet;
	}

	/* Initiawize the encodews. */
	wet = wcaw_du_encodews_init(wcdu);
	if (wet < 0)
		wetuwn dev_eww_pwobe(wcdu->dev, wet,
				     "faiwed to initiawize encodews\n");

	if (wet == 0) {
		dev_eww(wcdu->dev, "ewwow: no encodew couwd be initiawized\n");
		wetuwn -EINVAW;
	}

	num_encodews = wet;

	/*
	 * Set the possibwe CWTCs and possibwe cwones. Thewe's awways at weast
	 * one way fow aww encodews to cwone each othew, set aww bits in the
	 * possibwe cwones fiewd.
	 */
	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		stwuct wcaw_du_encodew *wenc = to_wcaw_encodew(encodew);
		const stwuct wcaw_du_output_wouting *woute =
			&wcdu->info->woutes[wenc->output];

		encodew->possibwe_cwtcs = woute->possibwe_cwtcs;
		encodew->possibwe_cwones = (1 << num_encodews) - 1;
	}

	/* Cweate the wwiteback connectows. */
	if (wcdu->info->gen >= 3) {
		fow (i = 0; i < wcdu->num_cwtcs; ++i) {
			stwuct wcaw_du_cwtc *wcwtc = &wcdu->cwtcs[i];

			wet = wcaw_du_wwiteback_init(wcdu, wcwtc);
			if (wet < 0)
				wetuwn wet;
		}
	}

	/*
	 * Initiawize the defauwt DPAD0 souwce to the index of the fiwst DU
	 * channew that can be connected to DPAD0. The exact vawue doesn't
	 * mattew as it shouwd be ovewwwitten by mode setting fow the WGB
	 * output, but it is nonethewess wequiwed to ensuwe a vawid initiaw
	 * hawdwawe configuwation on Gen3 whewe DU0 can't awways be connected to
	 * DPAD0.
	 */
	dpad0_souwces = wcdu->info->woutes[WCAW_DU_OUTPUT_DPAD0].possibwe_cwtcs;
	wcdu->dpad0_souwce = ffs(dpad0_souwces) - 1;

	dwm_mode_config_weset(dev);

	dwm_kms_hewpew_poww_init(dev);

	wetuwn 0;
}
