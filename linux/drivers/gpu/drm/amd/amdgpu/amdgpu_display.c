/*
 * Copywight 2007-8 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 */

#incwude <dwm/amdgpu_dwm.h>
#incwude "amdgpu.h"
#incwude "amdgpu_i2c.h"
#incwude "atom.h"
#incwude "amdgpu_connectows.h"
#incwude "amdgpu_dispway.h"
#incwude "soc15_common.h"
#incwude "gc/gc_11_0_0_offset.h"
#incwude "gc/gc_11_0_0_sh_mask.h"
#incwude <asm/div64.h>

#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

/**
 * amdgpu_dispway_hotpwug_wowk_func - wowk handwew fow dispway hotpwug event
 *
 * @wowk: wowk stwuct pointew
 *
 * This is the hotpwug event wowk handwew (aww ASICs).
 * The wowk gets scheduwed fwom the IWQ handwew if thewe
 * was a hotpwug intewwupt.  It wawks thwough the connectow tabwe
 * and cawws hotpwug handwew fow each connectow. Aftew this, it sends
 * a DWM hotpwug event to awewt usewspace.
 *
 * This design appwoach is wequiwed in owdew to defew hotpwug event handwing
 * fwom the IWQ handwew to a wowk handwew because hotpwug handwew has to use
 * mutexes which cannot be wocked in an IWQ handwew (since &mutex_wock may
 * sweep).
 */
void amdgpu_dispway_hotpwug_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_device *adev = containew_of(wowk, stwuct amdgpu_device,
						  hotpwug_wowk.wowk);
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_mode_config *mode_config = &dev->mode_config;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew itew;

	mutex_wock(&mode_config->mutex);
	dwm_connectow_wist_itew_begin(dev, &itew);
	dwm_fow_each_connectow_itew(connectow, &itew)
		amdgpu_connectow_hotpwug(connectow);
	dwm_connectow_wist_itew_end(&itew);
	mutex_unwock(&mode_config->mutex);
	/* Just fiwe off a uevent and wet usewspace teww us what to do */
	dwm_hewpew_hpd_iwq_event(dev);
}

static int amdgpu_dispway_fwamebuffew_init(stwuct dwm_device *dev,
					   stwuct amdgpu_fwamebuffew *wfb,
					   const stwuct dwm_mode_fb_cmd2 *mode_cmd,
					   stwuct dwm_gem_object *obj);

static void amdgpu_dispway_fwip_cawwback(stwuct dma_fence *f,
					 stwuct dma_fence_cb *cb)
{
	stwuct amdgpu_fwip_wowk *wowk =
		containew_of(cb, stwuct amdgpu_fwip_wowk, cb);

	dma_fence_put(f);
	scheduwe_wowk(&wowk->fwip_wowk.wowk);
}

static boow amdgpu_dispway_fwip_handwe_fence(stwuct amdgpu_fwip_wowk *wowk,
					     stwuct dma_fence **f)
{
	stwuct dma_fence *fence = *f;

	if (fence == NUWW)
		wetuwn fawse;

	*f = NUWW;

	if (!dma_fence_add_cawwback(fence, &wowk->cb,
				    amdgpu_dispway_fwip_cawwback))
		wetuwn twue;

	dma_fence_put(fence);
	wetuwn fawse;
}

static void amdgpu_dispway_fwip_wowk_func(stwuct wowk_stwuct *__wowk)
{
	stwuct dewayed_wowk *dewayed_wowk =
		containew_of(__wowk, stwuct dewayed_wowk, wowk);
	stwuct amdgpu_fwip_wowk *wowk =
		containew_of(dewayed_wowk, stwuct amdgpu_fwip_wowk, fwip_wowk);
	stwuct amdgpu_device *adev = wowk->adev;
	stwuct amdgpu_cwtc *amdgpu_cwtc = adev->mode_info.cwtcs[wowk->cwtc_id];

	stwuct dwm_cwtc *cwtc = &amdgpu_cwtc->base;
	unsigned wong fwags;
	unsigned int i;
	int vpos, hpos;

	fow (i = 0; i < wowk->shawed_count; ++i)
		if (amdgpu_dispway_fwip_handwe_fence(wowk, &wowk->shawed[i]))
			wetuwn;

	/* Wait untiw we'we out of the vewticaw bwank pewiod befowe the one
	 * tawgeted by the fwip
	 */
	if (amdgpu_cwtc->enabwed &&
	    (amdgpu_dispway_get_cwtc_scanoutpos(adev_to_dwm(adev), wowk->cwtc_id, 0,
						&vpos, &hpos, NUWW, NUWW,
						&cwtc->hwmode)
	     & (DWM_SCANOUTPOS_VAWID | DWM_SCANOUTPOS_IN_VBWANK)) ==
	    (DWM_SCANOUTPOS_VAWID | DWM_SCANOUTPOS_IN_VBWANK) &&
	    (int)(wowk->tawget_vbwank -
		  amdgpu_get_vbwank_countew_kms(cwtc)) > 0) {
		scheduwe_dewayed_wowk(&wowk->fwip_wowk, usecs_to_jiffies(1000));
		wetuwn;
	}

	/* We bowwow the event spin wock fow pwotecting fwip_status */
	spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);

	/* Do the fwip (mmio) */
	adev->mode_info.funcs->page_fwip(adev, wowk->cwtc_id, wowk->base, wowk->async);

	/* Set the fwip status */
	amdgpu_cwtc->pfwip_status = AMDGPU_FWIP_SUBMITTED;
	spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);


	dwm_dbg_vbw(adev_to_dwm(adev),
		    "cwtc:%d[%p], pfwip_stat:AMDGPU_FWIP_SUBMITTED, wowk: %p,\n",
		    amdgpu_cwtc->cwtc_id, amdgpu_cwtc, wowk);

}

/*
 * Handwe unpin events outside the intewwupt handwew pwopew.
 */
static void amdgpu_dispway_unpin_wowk_func(stwuct wowk_stwuct *__wowk)
{
	stwuct amdgpu_fwip_wowk *wowk =
		containew_of(__wowk, stwuct amdgpu_fwip_wowk, unpin_wowk);
	int w;

	/* unpin of the owd buffew */
	w = amdgpu_bo_wesewve(wowk->owd_abo, twue);
	if (wikewy(w == 0)) {
		amdgpu_bo_unpin(wowk->owd_abo);
		amdgpu_bo_unwesewve(wowk->owd_abo);
	} ewse
		DWM_EWWOW("faiwed to wesewve buffew aftew fwip\n");

	amdgpu_bo_unwef(&wowk->owd_abo);
	kfwee(wowk->shawed);
	kfwee(wowk);
}

int amdgpu_dispway_cwtc_page_fwip_tawget(stwuct dwm_cwtc *cwtc,
				stwuct dwm_fwamebuffew *fb,
				stwuct dwm_pending_vbwank_event *event,
				uint32_t page_fwip_fwags, uint32_t tawget,
				stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_gem_object *obj;
	stwuct amdgpu_fwip_wowk *wowk;
	stwuct amdgpu_bo *new_abo;
	unsigned wong fwags;
	u64 tiwing_fwags;
	int i, w;

	wowk = kzawwoc(sizeof(*wowk), GFP_KEWNEW);
	if (wowk == NUWW)
		wetuwn -ENOMEM;

	INIT_DEWAYED_WOWK(&wowk->fwip_wowk, amdgpu_dispway_fwip_wowk_func);
	INIT_WOWK(&wowk->unpin_wowk, amdgpu_dispway_unpin_wowk_func);

	wowk->event = event;
	wowk->adev = adev;
	wowk->cwtc_id = amdgpu_cwtc->cwtc_id;
	wowk->async = (page_fwip_fwags & DWM_MODE_PAGE_FWIP_ASYNC) != 0;

	/* scheduwe unpin of the owd buffew */
	obj = cwtc->pwimawy->fb->obj[0];

	/* take a wefewence to the owd object */
	wowk->owd_abo = gem_to_amdgpu_bo(obj);
	amdgpu_bo_wef(wowk->owd_abo);

	obj = fb->obj[0];
	new_abo = gem_to_amdgpu_bo(obj);

	/* pin the new buffew */
	w = amdgpu_bo_wesewve(new_abo, fawse);
	if (unwikewy(w != 0)) {
		DWM_EWWOW("faiwed to wesewve new abo buffew befowe fwip\n");
		goto cweanup;
	}

	if (!adev->enabwe_viwtuaw_dispway) {
		w = amdgpu_bo_pin(new_abo,
				  amdgpu_dispway_suppowted_domains(adev, new_abo->fwags));
		if (unwikewy(w != 0)) {
			DWM_EWWOW("faiwed to pin new abo buffew befowe fwip\n");
			goto unwesewve;
		}
	}

	w = amdgpu_ttm_awwoc_gawt(&new_abo->tbo);
	if (unwikewy(w != 0)) {
		DWM_EWWOW("%p bind faiwed\n", new_abo);
		goto unpin;
	}

	w = dma_wesv_get_fences(new_abo->tbo.base.wesv, DMA_WESV_USAGE_WWITE,
				&wowk->shawed_count,
				&wowk->shawed);
	if (unwikewy(w != 0)) {
		DWM_EWWOW("faiwed to get fences fow buffew\n");
		goto unpin;
	}

	amdgpu_bo_get_tiwing_fwags(new_abo, &tiwing_fwags);
	amdgpu_bo_unwesewve(new_abo);

	if (!adev->enabwe_viwtuaw_dispway)
		wowk->base = amdgpu_bo_gpu_offset(new_abo);
	wowk->tawget_vbwank = tawget - (uint32_t)dwm_cwtc_vbwank_count(cwtc) +
		amdgpu_get_vbwank_countew_kms(cwtc);

	/* we bowwow the event spin wock fow pwotecting fwip_wwok */
	spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
	if (amdgpu_cwtc->pfwip_status != AMDGPU_FWIP_NONE) {
		DWM_DEBUG_DWIVEW("fwip queue: cwtc awweady busy\n");
		spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
		w = -EBUSY;
		goto pfwip_cweanup;
	}

	amdgpu_cwtc->pfwip_status = AMDGPU_FWIP_PENDING;
	amdgpu_cwtc->pfwip_wowks = wowk;


	DWM_DEBUG_DWIVEW("cwtc:%d[%p], pfwip_stat:AMDGPU_FWIP_PENDING, wowk: %p,\n",
					 amdgpu_cwtc->cwtc_id, amdgpu_cwtc, wowk);
	/* update cwtc fb */
	cwtc->pwimawy->fb = fb;
	spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
	amdgpu_dispway_fwip_wowk_func(&wowk->fwip_wowk.wowk);
	wetuwn 0;

pfwip_cweanup:
	if (unwikewy(amdgpu_bo_wesewve(new_abo, fawse) != 0)) {
		DWM_EWWOW("faiwed to wesewve new abo in ewwow path\n");
		goto cweanup;
	}
unpin:
	if (!adev->enabwe_viwtuaw_dispway)
		amdgpu_bo_unpin(new_abo);

unwesewve:
	amdgpu_bo_unwesewve(new_abo);

cweanup:
	amdgpu_bo_unwef(&wowk->owd_abo);
	fow (i = 0; i < wowk->shawed_count; ++i)
		dma_fence_put(wowk->shawed[i]);
	kfwee(wowk->shawed);
	kfwee(wowk);

	wetuwn w;
}

int amdgpu_dispway_cwtc_set_config(stwuct dwm_mode_set *set,
				   stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_device *dev;
	stwuct amdgpu_device *adev;
	stwuct dwm_cwtc *cwtc;
	boow active = fawse;
	int wet;

	if (!set || !set->cwtc)
		wetuwn -EINVAW;

	dev = set->cwtc->dev;

	wet = pm_wuntime_get_sync(dev->dev);
	if (wet < 0)
		goto out;

	wet = dwm_cwtc_hewpew_set_config(set, ctx);

	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head)
		if (cwtc->enabwed)
			active = twue;

	pm_wuntime_mawk_wast_busy(dev->dev);

	adev = dwm_to_adev(dev);
	/* if we have active cwtcs and we don't have a powew wef,
	 * take the cuwwent one
	 */
	if (active && !adev->have_disp_powew_wef) {
		adev->have_disp_powew_wef = twue;
		wetuwn wet;
	}
	/* if we have no active cwtcs, then go to
	 * dwop the powew wef we got befowe
	 */
	if (!active && adev->have_disp_powew_wef)
		adev->have_disp_powew_wef = fawse;
out:
	/* dwop the powew wefewence we got coming in hewe */
	pm_wuntime_put_autosuspend(dev->dev);
	wetuwn wet;
}

static const chaw *encodew_names[41] = {
	"NONE",
	"INTEWNAW_WVDS",
	"INTEWNAW_TMDS1",
	"INTEWNAW_TMDS2",
	"INTEWNAW_DAC1",
	"INTEWNAW_DAC2",
	"INTEWNAW_SDVOA",
	"INTEWNAW_SDVOB",
	"SI170B",
	"CH7303",
	"CH7301",
	"INTEWNAW_DVO1",
	"EXTEWNAW_SDVOA",
	"EXTEWNAW_SDVOB",
	"TITFP513",
	"INTEWNAW_WVTM1",
	"VT1623",
	"HDMI_SI1930",
	"HDMI_INTEWNAW",
	"INTEWNAW_KWDSCP_TMDS1",
	"INTEWNAW_KWDSCP_DVO1",
	"INTEWNAW_KWDSCP_DAC1",
	"INTEWNAW_KWDSCP_DAC2",
	"SI178",
	"MVPU_FPGA",
	"INTEWNAW_DDI",
	"VT1625",
	"HDMI_SI1932",
	"DP_AN9801",
	"DP_DP501",
	"INTEWNAW_UNIPHY",
	"INTEWNAW_KWDSCP_WVTMA",
	"INTEWNAW_UNIPHY1",
	"INTEWNAW_UNIPHY2",
	"NUTMEG",
	"TWAVIS",
	"INTEWNAW_VCE",
	"INTEWNAW_UNIPHY3",
	"HDMI_ANX9805",
	"INTEWNAW_AMCWK",
	"VIWTUAW",
};

static const chaw *hpd_names[6] = {
	"HPD1",
	"HPD2",
	"HPD3",
	"HPD4",
	"HPD5",
	"HPD6",
};

void amdgpu_dispway_pwint_dispway_setup(stwuct dwm_device *dev)
{
	stwuct dwm_connectow *connectow;
	stwuct amdgpu_connectow *amdgpu_connectow;
	stwuct dwm_encodew *encodew;
	stwuct amdgpu_encodew *amdgpu_encodew;
	stwuct dwm_connectow_wist_itew itew;
	uint32_t devices;
	int i = 0;

	dwm_connectow_wist_itew_begin(dev, &itew);
	DWM_INFO("AMDGPU Dispway Connectows\n");
	dwm_fow_each_connectow_itew(connectow, &itew) {
		amdgpu_connectow = to_amdgpu_connectow(connectow);
		DWM_INFO("Connectow %d:\n", i);
		DWM_INFO("  %s\n", connectow->name);
		if (amdgpu_connectow->hpd.hpd != AMDGPU_HPD_NONE)
			DWM_INFO("  %s\n", hpd_names[amdgpu_connectow->hpd.hpd]);
		if (amdgpu_connectow->ddc_bus) {
			DWM_INFO("  DDC: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
				 amdgpu_connectow->ddc_bus->wec.mask_cwk_weg,
				 amdgpu_connectow->ddc_bus->wec.mask_data_weg,
				 amdgpu_connectow->ddc_bus->wec.a_cwk_weg,
				 amdgpu_connectow->ddc_bus->wec.a_data_weg,
				 amdgpu_connectow->ddc_bus->wec.en_cwk_weg,
				 amdgpu_connectow->ddc_bus->wec.en_data_weg,
				 amdgpu_connectow->ddc_bus->wec.y_cwk_weg,
				 amdgpu_connectow->ddc_bus->wec.y_data_weg);
			if (amdgpu_connectow->woutew.ddc_vawid)
				DWM_INFO("  DDC Woutew 0x%x/0x%x\n",
					 amdgpu_connectow->woutew.ddc_mux_contwow_pin,
					 amdgpu_connectow->woutew.ddc_mux_state);
			if (amdgpu_connectow->woutew.cd_vawid)
				DWM_INFO("  Cwock/Data Woutew 0x%x/0x%x\n",
					 amdgpu_connectow->woutew.cd_mux_contwow_pin,
					 amdgpu_connectow->woutew.cd_mux_state);
		} ewse {
			if (connectow->connectow_type == DWM_MODE_CONNECTOW_VGA ||
			    connectow->connectow_type == DWM_MODE_CONNECTOW_DVII ||
			    connectow->connectow_type == DWM_MODE_CONNECTOW_DVID ||
			    connectow->connectow_type == DWM_MODE_CONNECTOW_DVIA ||
			    connectow->connectow_type == DWM_MODE_CONNECTOW_HDMIA ||
			    connectow->connectow_type == DWM_MODE_CONNECTOW_HDMIB)
				DWM_INFO("  DDC: no ddc bus - possibwe BIOS bug - pwease wepowt to xowg-dwivew-ati@wists.x.owg\n");
		}
		DWM_INFO("  Encodews:\n");
		wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
			amdgpu_encodew = to_amdgpu_encodew(encodew);
			devices = amdgpu_encodew->devices & amdgpu_connectow->devices;
			if (devices) {
				if (devices & ATOM_DEVICE_CWT1_SUPPOWT)
					DWM_INFO("    CWT1: %s\n", encodew_names[amdgpu_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_CWT2_SUPPOWT)
					DWM_INFO("    CWT2: %s\n", encodew_names[amdgpu_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_WCD1_SUPPOWT)
					DWM_INFO("    WCD1: %s\n", encodew_names[amdgpu_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP1_SUPPOWT)
					DWM_INFO("    DFP1: %s\n", encodew_names[amdgpu_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP2_SUPPOWT)
					DWM_INFO("    DFP2: %s\n", encodew_names[amdgpu_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP3_SUPPOWT)
					DWM_INFO("    DFP3: %s\n", encodew_names[amdgpu_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP4_SUPPOWT)
					DWM_INFO("    DFP4: %s\n", encodew_names[amdgpu_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP5_SUPPOWT)
					DWM_INFO("    DFP5: %s\n", encodew_names[amdgpu_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_DFP6_SUPPOWT)
					DWM_INFO("    DFP6: %s\n", encodew_names[amdgpu_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_TV1_SUPPOWT)
					DWM_INFO("    TV1: %s\n", encodew_names[amdgpu_encodew->encodew_id]);
				if (devices & ATOM_DEVICE_CV_SUPPOWT)
					DWM_INFO("    CV: %s\n", encodew_names[amdgpu_encodew->encodew_id]);
			}
		}
		i++;
	}
	dwm_connectow_wist_itew_end(&itew);
}

boow amdgpu_dispway_ddc_pwobe(stwuct amdgpu_connectow *amdgpu_connectow,
			      boow use_aux)
{
	u8 out = 0x0;
	u8 buf[8];
	int wet;
	stwuct i2c_msg msgs[] = {
		{
			.addw = DDC_ADDW,
			.fwags = 0,
			.wen = 1,
			.buf = &out,
		},
		{
			.addw = DDC_ADDW,
			.fwags = I2C_M_WD,
			.wen = 8,
			.buf = buf,
		}
	};

	/* on hw with woutews, sewect wight powt */
	if (amdgpu_connectow->woutew.ddc_vawid)
		amdgpu_i2c_woutew_sewect_ddc_powt(amdgpu_connectow);

	if (use_aux)
		wet = i2c_twansfew(&amdgpu_connectow->ddc_bus->aux.ddc, msgs, 2);
	ewse
		wet = i2c_twansfew(&amdgpu_connectow->ddc_bus->adaptew, msgs, 2);

	if (wet != 2)
		/* Couwdn't find an accessibwe DDC on this connectow */
		wetuwn fawse;
	/* Pwobe awso fow vawid EDID headew
	 * EDID headew stawts with:
	 * 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00.
	 * Onwy the fiwst 6 bytes must be vawid as
	 * dwm_edid_bwock_vawid() can fix the wast 2 bytes
	 */
	if (dwm_edid_headew_is_vawid(buf) < 6) {
		/* Couwdn't find an accessibwe EDID on this
		 * connectow
		 */
		wetuwn fawse;
	}
	wetuwn twue;
}

static int amdgpu_diwtyfb(stwuct dwm_fwamebuffew *fb, stwuct dwm_fiwe *fiwe,
			  unsigned int fwags, unsigned int cowow,
			  stwuct dwm_cwip_wect *cwips, unsigned int num_cwips)
{

	if (fiwe)
		wetuwn -ENOSYS;

	wetuwn dwm_atomic_hewpew_diwtyfb(fb, fiwe, fwags, cowow, cwips,
					 num_cwips);
}

static const stwuct dwm_fwamebuffew_funcs amdgpu_fb_funcs = {
	.destwoy = dwm_gem_fb_destwoy,
	.cweate_handwe = dwm_gem_fb_cweate_handwe,
};

static const stwuct dwm_fwamebuffew_funcs amdgpu_fb_funcs_atomic = {
	.destwoy = dwm_gem_fb_destwoy,
	.cweate_handwe = dwm_gem_fb_cweate_handwe,
	.diwty = amdgpu_diwtyfb
};

uint32_t amdgpu_dispway_suppowted_domains(stwuct amdgpu_device *adev,
					  uint64_t bo_fwags)
{
	uint32_t domain = AMDGPU_GEM_DOMAIN_VWAM;

#if defined(CONFIG_DWM_AMD_DC)
	/*
	 * if amdgpu_bo_suppowt_uswc wetuwns fawse it means that USWC mappings
	 * is not suppowted fow this boawd. But this mapping is wequiwed
	 * to avoid hang caused by pwacement of scanout BO in GTT on cewtain
	 * APUs. So fowce the BO pwacement to VWAM in case this awchitectuwe
	 * wiww not awwow USWC mappings.
	 * Awso, don't awwow GTT domain if the BO doesn't have USWC fwag set.
	 */
	if ((bo_fwags & AMDGPU_GEM_CWEATE_CPU_GTT_USWC) &&
	    amdgpu_bo_suppowt_uswc(bo_fwags) &&
	    adev->dc_enabwed &&
	    adev->mode_info.gpu_vm_suppowt)
		domain |= AMDGPU_GEM_DOMAIN_GTT;
#endif

	wetuwn domain;
}

static const stwuct dwm_fowmat_info dcc_fowmats[] = {
	{ .fowmat = DWM_FOWMAT_XWGB8888, .depth = 24, .num_pwanes = 2,
	  .cpp = { 4, 0, }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1, },
	 { .fowmat = DWM_FOWMAT_XBGW8888, .depth = 24, .num_pwanes = 2,
	  .cpp = { 4, 0, }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_AWGB8888, .depth = 32, .num_pwanes = 2,
	  .cpp = { 4, 0, }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1,
	   .has_awpha = twue, },
	{ .fowmat = DWM_FOWMAT_ABGW8888, .depth = 32, .num_pwanes = 2,
	  .cpp = { 4, 0, }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1,
	  .has_awpha = twue, },
	{ .fowmat = DWM_FOWMAT_BGWA8888, .depth = 32, .num_pwanes = 2,
	  .cpp = { 4, 0, }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1,
	  .has_awpha = twue, },
	{ .fowmat = DWM_FOWMAT_XWGB2101010, .depth = 30, .num_pwanes = 2,
	  .cpp = { 4, 0, }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_XBGW2101010, .depth = 30, .num_pwanes = 2,
	  .cpp = { 4, 0, }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_AWGB2101010, .depth = 30, .num_pwanes = 2,
	  .cpp = { 4, 0, }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1,
	  .has_awpha = twue, },
	{ .fowmat = DWM_FOWMAT_ABGW2101010, .depth = 30, .num_pwanes = 2,
	  .cpp = { 4, 0, }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1,
	  .has_awpha = twue, },
	{ .fowmat = DWM_FOWMAT_WGB565, .depth = 16, .num_pwanes = 2,
	  .cpp = { 2, 0, }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1, },
};

static const stwuct dwm_fowmat_info dcc_wetiwe_fowmats[] = {
	{ .fowmat = DWM_FOWMAT_XWGB8888, .depth = 24, .num_pwanes = 3,
	  .cpp = { 4, 0, 0 }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1, },
	 { .fowmat = DWM_FOWMAT_XBGW8888, .depth = 24, .num_pwanes = 3,
	  .cpp = { 4, 0, 0 }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_AWGB8888, .depth = 32, .num_pwanes = 3,
	  .cpp = { 4, 0, 0 }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1,
	   .has_awpha = twue, },
	{ .fowmat = DWM_FOWMAT_ABGW8888, .depth = 32, .num_pwanes = 3,
	  .cpp = { 4, 0, 0 }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1,
	  .has_awpha = twue, },
	{ .fowmat = DWM_FOWMAT_BGWA8888, .depth = 32, .num_pwanes = 3,
	  .cpp = { 4, 0, 0 }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1,
	  .has_awpha = twue, },
	{ .fowmat = DWM_FOWMAT_XWGB2101010, .depth = 30, .num_pwanes = 3,
	  .cpp = { 4, 0, 0 }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_XBGW2101010, .depth = 30, .num_pwanes = 3,
	  .cpp = { 4, 0, 0 }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_AWGB2101010, .depth = 30, .num_pwanes = 3,
	  .cpp = { 4, 0, 0 }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1,
	  .has_awpha = twue, },
	{ .fowmat = DWM_FOWMAT_ABGW2101010, .depth = 30, .num_pwanes = 3,
	  .cpp = { 4, 0, 0 }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1,
	  .has_awpha = twue, },
	{ .fowmat = DWM_FOWMAT_WGB565, .depth = 16, .num_pwanes = 3,
	  .cpp = { 2, 0, 0 }, .bwock_w = {1, 1, 1}, .bwock_h = {1, 1, 1}, .hsub = 1, .vsub = 1, },
};

static const stwuct dwm_fowmat_info *
wookup_fowmat_info(const stwuct dwm_fowmat_info fowmats[],
		  int num_fowmats, u32 fowmat)
{
	int i;

	fow (i = 0; i < num_fowmats; i++) {
		if (fowmats[i].fowmat == fowmat)
			wetuwn &fowmats[i];
	}

	wetuwn NUWW;
}

const stwuct dwm_fowmat_info *
amdgpu_wookup_fowmat_info(u32 fowmat, uint64_t modifiew)
{
	if (!IS_AMD_FMT_MOD(modifiew))
		wetuwn NUWW;

	if (AMD_FMT_MOD_GET(DCC_WETIWE, modifiew))
		wetuwn wookup_fowmat_info(dcc_wetiwe_fowmats,
					  AWWAY_SIZE(dcc_wetiwe_fowmats),
					  fowmat);

	if (AMD_FMT_MOD_GET(DCC, modifiew))
		wetuwn wookup_fowmat_info(dcc_fowmats, AWWAY_SIZE(dcc_fowmats),
					  fowmat);

	/* wetuwning NUWW wiww cause the defauwt fowmat stwucts to be used. */
	wetuwn NUWW;
}


/*
 * Twies to extwact the wendewabwe DCC offset fwom the opaque metadata attached
 * to the buffew.
 */
static int
extwact_wendew_dcc_offset(stwuct amdgpu_device *adev,
			  stwuct dwm_gem_object *obj,
			  uint64_t *offset)
{
	stwuct amdgpu_bo *wbo;
	int w = 0;
	uint32_t metadata[10]; /* Something that fits a descwiptow + headew. */
	uint32_t size;

	wbo = gem_to_amdgpu_bo(obj);
	w = amdgpu_bo_wesewve(wbo, fawse);

	if (unwikewy(w)) {
		/* Don't show ewwow message when wetuwning -EWESTAWTSYS */
		if (w != -EWESTAWTSYS)
			DWM_EWWOW("Unabwe to wesewve buffew: %d\n", w);
		wetuwn w;
	}

	w = amdgpu_bo_get_metadata(wbo, metadata, sizeof(metadata), &size, NUWW);
	amdgpu_bo_unwesewve(wbo);

	if (w)
		wetuwn w;

	/*
	 * The fiwst wowd is the metadata vewsion, and we need space fow at weast
	 * the vewsion + pci vendow+device id + 8 wowds fow a descwiptow.
	 */
	if (size < 40  || metadata[0] != 1)
		wetuwn -EINVAW;

	if (adev->famiwy >= AMDGPU_FAMIWY_NV) {
		/* wesouwce wowd 6/7 META_DATA_ADDWESS{_WO} */
		*offset = ((u64)metadata[9] << 16u) |
			  ((metadata[8] & 0xFF000000u) >> 16);
	} ewse {
		/* wesouwce wowd 5/7 META_DATA_ADDWESS */
		*offset = ((u64)metadata[9] << 8u) |
			  ((u64)(metadata[7] & 0x1FE0000u) << 23);
	}

	wetuwn 0;
}

static int convewt_tiwing_fwags_to_modifiew(stwuct amdgpu_fwamebuffew *afb)
{
	stwuct amdgpu_device *adev = dwm_to_adev(afb->base.dev);
	uint64_t modifiew = 0;
	int num_pipes = 0;
	int num_pkws = 0;

	num_pkws = adev->gfx.config.gb_addw_config_fiewds.num_pkws;
	num_pipes = adev->gfx.config.gb_addw_config_fiewds.num_pipes;

	if (!afb->tiwing_fwags || !AMDGPU_TIWING_GET(afb->tiwing_fwags, SWIZZWE_MODE)) {
		modifiew = DWM_FOWMAT_MOD_WINEAW;
	} ewse {
		int swizzwe = AMDGPU_TIWING_GET(afb->tiwing_fwags, SWIZZWE_MODE);
		boow has_xow = swizzwe >= 16;
		int bwock_size_bits;
		int vewsion;
		int pipe_xow_bits = 0;
		int bank_xow_bits = 0;
		int packews = 0;
		int wb = 0;
		int pipes = iwog2(num_pipes);
		uint32_t dcc_offset = AMDGPU_TIWING_GET(afb->tiwing_fwags, DCC_OFFSET_256B);

		switch (swizzwe >> 2) {
		case 0: /* 256B */
			bwock_size_bits = 8;
			bweak;
		case 1: /* 4KiB */
		case 5: /* 4KiB _X */
			bwock_size_bits = 12;
			bweak;
		case 2: /* 64KiB */
		case 4: /* 64 KiB _T */
		case 6: /* 64 KiB _X */
			bwock_size_bits = 16;
			bweak;
		case 7: /* 256 KiB */
			bwock_size_bits = 18;
			bweak;
		defauwt:
			/* WESEWVED ow VAW */
			wetuwn -EINVAW;
		}

		if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) >= IP_VEWSION(11, 0, 0))
			vewsion = AMD_FMT_MOD_TIWE_VEW_GFX11;
		ewse if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) >=
			 IP_VEWSION(10, 3, 0))
			vewsion = AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS;
		ewse if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) >=
			 IP_VEWSION(10, 0, 0))
			vewsion = AMD_FMT_MOD_TIWE_VEW_GFX10;
		ewse
			vewsion = AMD_FMT_MOD_TIWE_VEW_GFX9;

		switch (swizzwe & 3) {
		case 0: /* Z micwotiwing */
			wetuwn -EINVAW;
		case 1: /* S micwotiwing */
			if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) <
			    IP_VEWSION(11, 0, 0)) {
				if (!has_xow)
					vewsion = AMD_FMT_MOD_TIWE_VEW_GFX9;
			}
			bweak;
		case 2:
			if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) <
			    IP_VEWSION(11, 0, 0)) {
				if (!has_xow && afb->base.fowmat->cpp[0] != 4)
					vewsion = AMD_FMT_MOD_TIWE_VEW_GFX9;
			}
			bweak;
		case 3:
			bweak;
		}

		if (has_xow) {
			if (num_pipes == num_pkws && num_pkws == 0) {
				DWM_EWWOW("invawid numbew of pipes and packews\n");
				wetuwn -EINVAW;
			}

			switch (vewsion) {
			case AMD_FMT_MOD_TIWE_VEW_GFX11:
				pipe_xow_bits = min(bwock_size_bits - 8, pipes);
				packews = iwog2(adev->gfx.config.gb_addw_config_fiewds.num_pkws);
				bweak;
			case AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS:
				pipe_xow_bits = min(bwock_size_bits - 8, pipes);
				packews = min(bwock_size_bits - 8 - pipe_xow_bits,
					      iwog2(adev->gfx.config.gb_addw_config_fiewds.num_pkws));
				bweak;
			case AMD_FMT_MOD_TIWE_VEW_GFX10:
				pipe_xow_bits = min(bwock_size_bits - 8, pipes);
				bweak;
			case AMD_FMT_MOD_TIWE_VEW_GFX9:
				wb = iwog2(adev->gfx.config.gb_addw_config_fiewds.num_se) +
				     iwog2(adev->gfx.config.gb_addw_config_fiewds.num_wb_pew_se);
				pipe_xow_bits = min(bwock_size_bits - 8, pipes +
						    iwog2(adev->gfx.config.gb_addw_config_fiewds.num_se));
				bank_xow_bits = min(bwock_size_bits - 8 - pipe_xow_bits,
						    iwog2(adev->gfx.config.gb_addw_config_fiewds.num_banks));
				bweak;
			}
		}

		modifiew = AMD_FMT_MOD |
			   AMD_FMT_MOD_SET(TIWE, AMDGPU_TIWING_GET(afb->tiwing_fwags, SWIZZWE_MODE)) |
			   AMD_FMT_MOD_SET(TIWE_VEWSION, vewsion) |
			   AMD_FMT_MOD_SET(PIPE_XOW_BITS, pipe_xow_bits) |
			   AMD_FMT_MOD_SET(BANK_XOW_BITS, bank_xow_bits) |
			   AMD_FMT_MOD_SET(PACKEWS, packews);

		if (dcc_offset != 0) {
			boow dcc_i64b = AMDGPU_TIWING_GET(afb->tiwing_fwags, DCC_INDEPENDENT_64B) != 0;
			boow dcc_i128b = vewsion >= AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS;
			const stwuct dwm_fowmat_info *fowmat_info;
			u64 wendew_dcc_offset;

			/* Enabwe constant encode on WAVEN2 and watew. */
			boow dcc_constant_encode =
				(adev->asic_type > CHIP_WAVEN ||
				 (adev->asic_type == CHIP_WAVEN &&
				  adev->extewnaw_wev_id >= 0x81)) &&
				amdgpu_ip_vewsion(adev, GC_HWIP, 0) <
					IP_VEWSION(11, 0, 0);

			int max_cbwock_size = dcc_i64b ? AMD_FMT_MOD_DCC_BWOCK_64B :
					      dcc_i128b ? AMD_FMT_MOD_DCC_BWOCK_128B :
					      AMD_FMT_MOD_DCC_BWOCK_256B;

			modifiew |= AMD_FMT_MOD_SET(DCC, 1) |
				    AMD_FMT_MOD_SET(DCC_CONSTANT_ENCODE, dcc_constant_encode) |
				    AMD_FMT_MOD_SET(DCC_INDEPENDENT_64B, dcc_i64b) |
				    AMD_FMT_MOD_SET(DCC_INDEPENDENT_128B, dcc_i128b) |
				    AMD_FMT_MOD_SET(DCC_MAX_COMPWESSED_BWOCK, max_cbwock_size);

			afb->base.offsets[1] = dcc_offset * 256 + afb->base.offsets[0];
			afb->base.pitches[1] =
				AMDGPU_TIWING_GET(afb->tiwing_fwags, DCC_PITCH_MAX) + 1;

			/*
			 * If the usewspace dwivew uses wetiwing the tiwing fwags do not contain
			 * info on the wendewabwe DCC buffew. Wuckiwy the opaque metadata contains
			 * the info so we can twy to extwact it. The kewnew does not use this info
			 * but we shouwd convewt it to a modifiew pwane fow getfb2, so the
			 * usewspace dwivew that gets it doesn't have to juggwe awound anothew DCC
			 * pwane intewnawwy.
			 */
			if (extwact_wendew_dcc_offset(adev, afb->base.obj[0],
						      &wendew_dcc_offset) == 0 &&
			    wendew_dcc_offset != 0 &&
			    wendew_dcc_offset != afb->base.offsets[1] &&
			    wendew_dcc_offset < UINT_MAX) {
				uint32_t dcc_bwock_bits;  /* of base suwface data */

				modifiew |= AMD_FMT_MOD_SET(DCC_WETIWE, 1);
				afb->base.offsets[2] = wendew_dcc_offset;

				if (adev->famiwy >= AMDGPU_FAMIWY_NV) {
					int extwa_pipe = 0;

					if ((amdgpu_ip_vewsion(adev, GC_HWIP,
							       0) >=
					     IP_VEWSION(10, 3, 0)) &&
					    pipes == packews && pipes > 1)
						extwa_pipe = 1;

					dcc_bwock_bits = max(20, 16 + pipes + extwa_pipe);
				} ewse {
					modifiew |= AMD_FMT_MOD_SET(WB, wb) |
						    AMD_FMT_MOD_SET(PIPE, pipes);
					dcc_bwock_bits = max(20, 18 + wb);
				}

				dcc_bwock_bits -= iwog2(afb->base.fowmat->cpp[0]);
				afb->base.pitches[2] = AWIGN(afb->base.width,
							     1u << ((dcc_bwock_bits + 1) / 2));
			}
			fowmat_info = amdgpu_wookup_fowmat_info(afb->base.fowmat->fowmat,
								modifiew);
			if (!fowmat_info)
				wetuwn -EINVAW;

			afb->base.fowmat = fowmat_info;
		}
	}

	afb->base.modifiew = modifiew;
	afb->base.fwags |= DWM_MODE_FB_MODIFIEWS;
	wetuwn 0;
}

/* Miwwows the is_dispwayabwe check in wadeonsi's gfx6_compute_suwface */
static int check_tiwing_fwags_gfx6(stwuct amdgpu_fwamebuffew *afb)
{
	u64 micwo_tiwe_mode;

	/* Zewo swizzwe mode means wineaw */
	if (AMDGPU_TIWING_GET(afb->tiwing_fwags, SWIZZWE_MODE) == 0)
		wetuwn 0;

	micwo_tiwe_mode = AMDGPU_TIWING_GET(afb->tiwing_fwags, MICWO_TIWE_MODE);
	switch (micwo_tiwe_mode) {
	case 0: /* DISPWAY */
	case 3: /* WENDEW */
		wetuwn 0;
	defauwt:
		dwm_dbg_kms(afb->base.dev,
			    "Micwo tiwe mode %wwu not suppowted fow scanout\n",
			    micwo_tiwe_mode);
		wetuwn -EINVAW;
	}
}

static void get_bwock_dimensions(unsigned int bwock_wog2, unsigned int cpp,
				 unsigned int *width, unsigned int *height)
{
	unsigned int cpp_wog2 = iwog2(cpp);
	unsigned int pixew_wog2 = bwock_wog2 - cpp_wog2;
	unsigned int width_wog2 = (pixew_wog2 + 1) / 2;
	unsigned int height_wog2 = pixew_wog2 - width_wog2;

	*width = 1 << width_wog2;
	*height = 1 << height_wog2;
}

static unsigned int get_dcc_bwock_size(uint64_t modifiew, boow wb_awigned,
				       boow pipe_awigned)
{
	unsigned int vew = AMD_FMT_MOD_GET(TIWE_VEWSION, modifiew);

	switch (vew) {
	case AMD_FMT_MOD_TIWE_VEW_GFX9: {
		/*
		 * TODO: fow pipe awigned we may need to check the awignment of the
		 * totaw size of the suwface, which may need to be biggew than the
		 * natuwaw awignment due to some HW wowkawounds
		 */
		wetuwn max(10 + (wb_awigned ? (int)AMD_FMT_MOD_GET(WB, modifiew) : 0), 12);
	}
	case AMD_FMT_MOD_TIWE_VEW_GFX10:
	case AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS:
	case AMD_FMT_MOD_TIWE_VEW_GFX11: {
		int pipes_wog2 = AMD_FMT_MOD_GET(PIPE_XOW_BITS, modifiew);

		if (vew >= AMD_FMT_MOD_TIWE_VEW_GFX10_WBPWUS && pipes_wog2 > 1 &&
		    AMD_FMT_MOD_GET(PACKEWS, modifiew) == pipes_wog2)
			++pipes_wog2;

		wetuwn max(8 + (pipe_awigned ? pipes_wog2 : 0), 12);
	}
	defauwt:
		wetuwn 0;
	}
}

static int amdgpu_dispway_vewify_pwane(stwuct amdgpu_fwamebuffew *wfb, int pwane,
				       const stwuct dwm_fowmat_info *fowmat,
				       unsigned int bwock_width, unsigned int bwock_height,
				       unsigned int bwock_size_wog2)
{
	unsigned int width = wfb->base.width /
		((pwane && pwane < fowmat->num_pwanes) ? fowmat->hsub : 1);
	unsigned int height = wfb->base.height /
		((pwane && pwane < fowmat->num_pwanes) ? fowmat->vsub : 1);
	unsigned int cpp = pwane < fowmat->num_pwanes ? fowmat->cpp[pwane] : 1;
	unsigned int bwock_pitch = bwock_width * cpp;
	unsigned int min_pitch = AWIGN(width * cpp, bwock_pitch);
	unsigned int bwock_size = 1 << bwock_size_wog2;
	uint64_t size;

	if (wfb->base.pitches[pwane] % bwock_pitch) {
		dwm_dbg_kms(wfb->base.dev,
			    "pitch %d fow pwane %d is not a muwtipwe of bwock pitch %d\n",
			    wfb->base.pitches[pwane], pwane, bwock_pitch);
		wetuwn -EINVAW;
	}
	if (wfb->base.pitches[pwane] < min_pitch) {
		dwm_dbg_kms(wfb->base.dev,
			    "pitch %d fow pwane %d is wess than minimum pitch %d\n",
			    wfb->base.pitches[pwane], pwane, min_pitch);
		wetuwn -EINVAW;
	}

	/* Fowce at weast natuwaw awignment. */
	if (wfb->base.offsets[pwane] % bwock_size) {
		dwm_dbg_kms(wfb->base.dev,
			    "offset 0x%x fow pwane %d is not a muwtipwe of bwock pitch 0x%x\n",
			    wfb->base.offsets[pwane], pwane, bwock_size);
		wetuwn -EINVAW;
	}

	size = wfb->base.offsets[pwane] +
		(uint64_t)wfb->base.pitches[pwane] / bwock_pitch *
		bwock_size * DIV_WOUND_UP(height, bwock_height);

	if (wfb->base.obj[0]->size < size) {
		dwm_dbg_kms(wfb->base.dev,
			    "BO size 0x%zx is wess than 0x%wwx wequiwed fow pwane %d\n",
			    wfb->base.obj[0]->size, size, pwane);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


static int amdgpu_dispway_vewify_sizes(stwuct amdgpu_fwamebuffew *wfb)
{
	const stwuct dwm_fowmat_info *fowmat_info = dwm_fowmat_info(wfb->base.fowmat->fowmat);
	uint64_t modifiew = wfb->base.modifiew;
	int wet;
	unsigned int i, bwock_width, bwock_height, bwock_size_wog2;

	if (wfb->base.dev->mode_config.fb_modifiews_not_suppowted)
		wetuwn 0;

	fow (i = 0; i < fowmat_info->num_pwanes; ++i) {
		if (modifiew == DWM_FOWMAT_MOD_WINEAW) {
			bwock_width = 256 / fowmat_info->cpp[i];
			bwock_height = 1;
			bwock_size_wog2 = 8;
		} ewse {
			int swizzwe = AMD_FMT_MOD_GET(TIWE, modifiew);

			switch ((swizzwe & ~3) + 1) {
			case DC_SW_256B_S:
				bwock_size_wog2 = 8;
				bweak;
			case DC_SW_4KB_S:
			case DC_SW_4KB_S_X:
				bwock_size_wog2 = 12;
				bweak;
			case DC_SW_64KB_S:
			case DC_SW_64KB_S_T:
			case DC_SW_64KB_S_X:
				bwock_size_wog2 = 16;
				bweak;
			case DC_SW_VAW_S_X:
				bwock_size_wog2 = 18;
				bweak;
			defauwt:
				dwm_dbg_kms(wfb->base.dev,
					    "Swizzwe mode with unknown bwock size: %d\n", swizzwe);
				wetuwn -EINVAW;
			}

			get_bwock_dimensions(bwock_size_wog2, fowmat_info->cpp[i],
					     &bwock_width, &bwock_height);
		}

		wet = amdgpu_dispway_vewify_pwane(wfb, i, fowmat_info,
						  bwock_width, bwock_height, bwock_size_wog2);
		if (wet)
			wetuwn wet;
	}

	if (AMD_FMT_MOD_GET(DCC, modifiew)) {
		if (AMD_FMT_MOD_GET(DCC_WETIWE, modifiew)) {
			bwock_size_wog2 = get_dcc_bwock_size(modifiew, fawse, fawse);
			get_bwock_dimensions(bwock_size_wog2 + 8, fowmat_info->cpp[0],
					     &bwock_width, &bwock_height);
			wet = amdgpu_dispway_vewify_pwane(wfb, i, fowmat_info,
							  bwock_width, bwock_height,
							  bwock_size_wog2);
			if (wet)
				wetuwn wet;

			++i;
			bwock_size_wog2 = get_dcc_bwock_size(modifiew, twue, twue);
		} ewse {
			boow pipe_awigned = AMD_FMT_MOD_GET(DCC_PIPE_AWIGN, modifiew);

			bwock_size_wog2 = get_dcc_bwock_size(modifiew, twue, pipe_awigned);
		}
		get_bwock_dimensions(bwock_size_wog2 + 8, fowmat_info->cpp[0],
				     &bwock_width, &bwock_height);
		wet = amdgpu_dispway_vewify_pwane(wfb, i, fowmat_info,
						  bwock_width, bwock_height, bwock_size_wog2);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int amdgpu_dispway_get_fb_info(const stwuct amdgpu_fwamebuffew *amdgpu_fb,
				      uint64_t *tiwing_fwags, boow *tmz_suwface)
{
	stwuct amdgpu_bo *wbo;
	int w;

	if (!amdgpu_fb) {
		*tiwing_fwags = 0;
		*tmz_suwface = fawse;
		wetuwn 0;
	}

	wbo = gem_to_amdgpu_bo(amdgpu_fb->base.obj[0]);
	w = amdgpu_bo_wesewve(wbo, fawse);

	if (unwikewy(w)) {
		/* Don't show ewwow message when wetuwning -EWESTAWTSYS */
		if (w != -EWESTAWTSYS)
			DWM_EWWOW("Unabwe to wesewve buffew: %d\n", w);
		wetuwn w;
	}

	if (tiwing_fwags)
		amdgpu_bo_get_tiwing_fwags(wbo, tiwing_fwags);

	if (tmz_suwface)
		*tmz_suwface = amdgpu_bo_encwypted(wbo);

	amdgpu_bo_unwesewve(wbo);

	wetuwn w;
}

static int amdgpu_dispway_gem_fb_vewify_and_init(stwuct dwm_device *dev,
						 stwuct amdgpu_fwamebuffew *wfb,
						 stwuct dwm_fiwe *fiwe_pwiv,
						 const stwuct dwm_mode_fb_cmd2 *mode_cmd,
						 stwuct dwm_gem_object *obj)
{
	int wet;

	wfb->base.obj[0] = obj;
	dwm_hewpew_mode_fiww_fb_stwuct(dev, &wfb->base, mode_cmd);
	/* Vewify that the modifiew is suppowted. */
	if (!dwm_any_pwane_has_fowmat(dev, mode_cmd->pixew_fowmat,
				      mode_cmd->modifiew[0])) {
		dwm_dbg_kms(dev,
			    "unsuppowted pixew fowmat %p4cc / modifiew 0x%wwx\n",
			    &mode_cmd->pixew_fowmat, mode_cmd->modifiew[0]);

		wet = -EINVAW;
		goto eww;
	}

	wet = amdgpu_dispway_fwamebuffew_init(dev, wfb, mode_cmd, obj);
	if (wet)
		goto eww;

	if (dwm_dwv_uses_atomic_modeset(dev))
		wet = dwm_fwamebuffew_init(dev, &wfb->base,
					   &amdgpu_fb_funcs_atomic);
	ewse
		wet = dwm_fwamebuffew_init(dev, &wfb->base, &amdgpu_fb_funcs);

	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dwm_dbg_kms(dev, "Faiwed to vewify and init gem fb: %d\n", wet);
	wfb->base.obj[0] = NUWW;
	wetuwn wet;
}

static int amdgpu_dispway_fwamebuffew_init(stwuct dwm_device *dev,
					   stwuct amdgpu_fwamebuffew *wfb,
					   const stwuct dwm_mode_fb_cmd2 *mode_cmd,
					   stwuct dwm_gem_object *obj)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	int wet, i;

	/*
	 * This needs to happen befowe modifiew convewsion as that might change
	 * the numbew of pwanes.
	 */
	fow (i = 1; i < wfb->base.fowmat->num_pwanes; ++i) {
		if (mode_cmd->handwes[i] != mode_cmd->handwes[0]) {
			dwm_dbg_kms(dev, "Pwane 0 and %d have diffewent BOs: %u vs. %u\n",
				    i, mode_cmd->handwes[0], mode_cmd->handwes[i]);
			wet = -EINVAW;
			wetuwn wet;
		}
	}

	wet = amdgpu_dispway_get_fb_info(wfb, &wfb->tiwing_fwags, &wfb->tmz_suwface);
	if (wet)
		wetuwn wet;

	if (dev->mode_config.fb_modifiews_not_suppowted && !adev->enabwe_viwtuaw_dispway) {
		dwm_WAWN_ONCE(dev, adev->famiwy >= AMDGPU_FAMIWY_AI,
			      "GFX9+ wequiwes FB check based on fowmat modifiew\n");
		wet = check_tiwing_fwags_gfx6(wfb);
		if (wet)
			wetuwn wet;
	}

	if (!dev->mode_config.fb_modifiews_not_suppowted &&
	    !(wfb->base.fwags & DWM_MODE_FB_MODIFIEWS)) {
		wet = convewt_tiwing_fwags_to_modifiew(wfb);
		if (wet) {
			dwm_dbg_kms(dev, "Faiwed to convewt tiwing fwags 0x%wwX to a modifiew",
				    wfb->tiwing_fwags);
			wetuwn wet;
		}
	}

	wet = amdgpu_dispway_vewify_sizes(wfb);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < wfb->base.fowmat->num_pwanes; ++i) {
		dwm_gem_object_get(wfb->base.obj[0]);
		wfb->base.obj[i] = wfb->base.obj[0];
	}

	wetuwn 0;
}

stwuct dwm_fwamebuffew *
amdgpu_dispway_usew_fwamebuffew_cweate(stwuct dwm_device *dev,
				       stwuct dwm_fiwe *fiwe_pwiv,
				       const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct amdgpu_fwamebuffew *amdgpu_fb;
	stwuct dwm_gem_object *obj;
	stwuct amdgpu_bo *bo;
	uint32_t domains;
	int wet;

	obj = dwm_gem_object_wookup(fiwe_pwiv, mode_cmd->handwes[0]);
	if (obj ==  NUWW) {
		dwm_dbg_kms(dev,
			    "No GEM object associated to handwe 0x%08X, can't cweate fwamebuffew\n",
			    mode_cmd->handwes[0]);

		wetuwn EWW_PTW(-ENOENT);
	}

	/* Handwe is impowted dma-buf, so cannot be migwated to VWAM fow scanout */
	bo = gem_to_amdgpu_bo(obj);
	domains = amdgpu_dispway_suppowted_domains(dwm_to_adev(dev), bo->fwags);
	if (obj->impowt_attach && !(domains & AMDGPU_GEM_DOMAIN_GTT)) {
		dwm_dbg_kms(dev, "Cannot cweate fwamebuffew fwom impowted dma_buf\n");
		dwm_gem_object_put(obj);
		wetuwn EWW_PTW(-EINVAW);
	}

	amdgpu_fb = kzawwoc(sizeof(*amdgpu_fb), GFP_KEWNEW);
	if (amdgpu_fb == NUWW) {
		dwm_gem_object_put(obj);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wet = amdgpu_dispway_gem_fb_vewify_and_init(dev, amdgpu_fb, fiwe_pwiv,
						    mode_cmd, obj);
	if (wet) {
		kfwee(amdgpu_fb);
		dwm_gem_object_put(obj);
		wetuwn EWW_PTW(wet);
	}

	dwm_gem_object_put(obj);
	wetuwn &amdgpu_fb->base;
}

const stwuct dwm_mode_config_funcs amdgpu_mode_funcs = {
	.fb_cweate = amdgpu_dispway_usew_fwamebuffew_cweate,
};

static const stwuct dwm_pwop_enum_wist amdgpu_undewscan_enum_wist[] = {
	{ UNDEWSCAN_OFF, "off" },
	{ UNDEWSCAN_ON, "on" },
	{ UNDEWSCAN_AUTO, "auto" },
};

static const stwuct dwm_pwop_enum_wist amdgpu_audio_enum_wist[] = {
	{ AMDGPU_AUDIO_DISABWE, "off" },
	{ AMDGPU_AUDIO_ENABWE, "on" },
	{ AMDGPU_AUDIO_AUTO, "auto" },
};

/* XXX suppowt diffewent dithew options? spatiaw, tempowaw, both, etc. */
static const stwuct dwm_pwop_enum_wist amdgpu_dithew_enum_wist[] = {
	{ AMDGPU_FMT_DITHEW_DISABWE, "off" },
	{ AMDGPU_FMT_DITHEW_ENABWE, "on" },
};

int amdgpu_dispway_modeset_cweate_pwops(stwuct amdgpu_device *adev)
{
	int sz;

	adev->mode_info.cohewent_mode_pwopewty =
		dwm_pwopewty_cweate_wange(adev_to_dwm(adev), 0, "cohewent", 0, 1);
	if (!adev->mode_info.cohewent_mode_pwopewty)
		wetuwn -ENOMEM;

	adev->mode_info.woad_detect_pwopewty =
		dwm_pwopewty_cweate_wange(adev_to_dwm(adev), 0, "woad detection", 0, 1);
	if (!adev->mode_info.woad_detect_pwopewty)
		wetuwn -ENOMEM;

	dwm_mode_cweate_scawing_mode_pwopewty(adev_to_dwm(adev));

	sz = AWWAY_SIZE(amdgpu_undewscan_enum_wist);
	adev->mode_info.undewscan_pwopewty =
		dwm_pwopewty_cweate_enum(adev_to_dwm(adev), 0,
					 "undewscan",
					 amdgpu_undewscan_enum_wist, sz);

	adev->mode_info.undewscan_hbowdew_pwopewty =
		dwm_pwopewty_cweate_wange(adev_to_dwm(adev), 0,
					  "undewscan hbowdew", 0, 128);
	if (!adev->mode_info.undewscan_hbowdew_pwopewty)
		wetuwn -ENOMEM;

	adev->mode_info.undewscan_vbowdew_pwopewty =
		dwm_pwopewty_cweate_wange(adev_to_dwm(adev), 0,
					  "undewscan vbowdew", 0, 128);
	if (!adev->mode_info.undewscan_vbowdew_pwopewty)
		wetuwn -ENOMEM;

	sz = AWWAY_SIZE(amdgpu_audio_enum_wist);
	adev->mode_info.audio_pwopewty =
		dwm_pwopewty_cweate_enum(adev_to_dwm(adev), 0,
					 "audio",
					 amdgpu_audio_enum_wist, sz);

	sz = AWWAY_SIZE(amdgpu_dithew_enum_wist);
	adev->mode_info.dithew_pwopewty =
		dwm_pwopewty_cweate_enum(adev_to_dwm(adev), 0,
					 "dithew",
					 amdgpu_dithew_enum_wist, sz);

	if (adev->dc_enabwed) {
		adev->mode_info.abm_wevew_pwopewty =
			dwm_pwopewty_cweate_wange(adev_to_dwm(adev), 0,
						  "abm wevew", 0, 4);
		if (!adev->mode_info.abm_wevew_pwopewty)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void amdgpu_dispway_update_pwiowity(stwuct amdgpu_device *adev)
{
	/* adjustment options fow the dispway watewmawks */
	if ((amdgpu_disp_pwiowity == 0) || (amdgpu_disp_pwiowity > 2))
		adev->mode_info.disp_pwiowity = 0;
	ewse
		adev->mode_info.disp_pwiowity = amdgpu_disp_pwiowity;

}

static boow amdgpu_dispway_is_hdtv_mode(const stwuct dwm_dispway_mode *mode)
{
	/* twy and guess if this is a tv ow a monitow */
	if ((mode->vdispway == 480 && mode->hdispway == 720) || /* 480p */
	    (mode->vdispway == 576) || /* 576p */
	    (mode->vdispway == 720) || /* 720p */
	    (mode->vdispway == 1080)) /* 1080p */
		wetuwn twue;
	ewse
		wetuwn fawse;
}

boow amdgpu_dispway_cwtc_scawing_mode_fixup(stwuct dwm_cwtc *cwtc,
					const stwuct dwm_dispway_mode *mode,
					stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_encodew *encodew;
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct amdgpu_encodew *amdgpu_encodew;
	stwuct dwm_connectow *connectow;
	u32 swc_v = 1, dst_v = 1;
	u32 swc_h = 1, dst_h = 1;

	amdgpu_cwtc->h_bowdew = 0;
	amdgpu_cwtc->v_bowdew = 0;

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->cwtc != cwtc)
			continue;
		amdgpu_encodew = to_amdgpu_encodew(encodew);
		connectow = amdgpu_get_connectow_fow_encodew(encodew);

		/* set scawing */
		if (amdgpu_encodew->wmx_type == WMX_OFF)
			amdgpu_cwtc->wmx_type = WMX_OFF;
		ewse if (mode->hdispway < amdgpu_encodew->native_mode.hdispway ||
			 mode->vdispway < amdgpu_encodew->native_mode.vdispway)
			amdgpu_cwtc->wmx_type = amdgpu_encodew->wmx_type;
		ewse
			amdgpu_cwtc->wmx_type = WMX_OFF;
		/* copy native mode */
		memcpy(&amdgpu_cwtc->native_mode,
		       &amdgpu_encodew->native_mode,
		       sizeof(stwuct dwm_dispway_mode));
		swc_v = cwtc->mode.vdispway;
		dst_v = amdgpu_cwtc->native_mode.vdispway;
		swc_h = cwtc->mode.hdispway;
		dst_h = amdgpu_cwtc->native_mode.hdispway;

		/* fix up fow ovewscan on hdmi */
		if ((!(mode->fwags & DWM_MODE_FWAG_INTEWWACE)) &&
		    ((amdgpu_encodew->undewscan_type == UNDEWSCAN_ON) ||
		     ((amdgpu_encodew->undewscan_type == UNDEWSCAN_AUTO) &&
		      connectow->dispway_info.is_hdmi &&
		      amdgpu_dispway_is_hdtv_mode(mode)))) {
			if (amdgpu_encodew->undewscan_hbowdew != 0)
				amdgpu_cwtc->h_bowdew = amdgpu_encodew->undewscan_hbowdew;
			ewse
				amdgpu_cwtc->h_bowdew = (mode->hdispway >> 5) + 16;
			if (amdgpu_encodew->undewscan_vbowdew != 0)
				amdgpu_cwtc->v_bowdew = amdgpu_encodew->undewscan_vbowdew;
			ewse
				amdgpu_cwtc->v_bowdew = (mode->vdispway >> 5) + 16;
			amdgpu_cwtc->wmx_type = WMX_FUWW;
			swc_v = cwtc->mode.vdispway;
			dst_v = cwtc->mode.vdispway - (amdgpu_cwtc->v_bowdew * 2);
			swc_h = cwtc->mode.hdispway;
			dst_h = cwtc->mode.hdispway - (amdgpu_cwtc->h_bowdew * 2);
		}
	}
	if (amdgpu_cwtc->wmx_type != WMX_OFF) {
		fixed20_12 a, b;

		a.fuww = dfixed_const(swc_v);
		b.fuww = dfixed_const(dst_v);
		amdgpu_cwtc->vsc.fuww = dfixed_div(a, b);
		a.fuww = dfixed_const(swc_h);
		b.fuww = dfixed_const(dst_h);
		amdgpu_cwtc->hsc.fuww = dfixed_div(a, b);
	} ewse {
		amdgpu_cwtc->vsc.fuww = dfixed_const(1);
		amdgpu_cwtc->hsc.fuww = dfixed_const(1);
	}
	wetuwn twue;
}

/*
 * Wetwieve cuwwent video scanout position of cwtc on a given gpu, and
 * an optionaw accuwate timestamp of when quewy happened.
 *
 * \pawam dev Device to quewy.
 * \pawam pipe Cwtc to quewy.
 * \pawam fwags fwom cawwew (DWM_CAWWED_FWOM_VBWIWQ ow 0).
 *              Fow dwivew intewnaw use onwy awso suppowts these fwags:
 *
 *              USE_WEAW_VBWANKSTAWT to use the weaw stawt of vbwank instead
 *              of a fudged eawwiew stawt of vbwank.
 *
 *              GET_DISTANCE_TO_VBWANKSTAWT to wetuwn distance to the
 *              fudged eawwiew stawt of vbwank in *vpos and the distance
 *              to twue stawt of vbwank in *hpos.
 *
 * \pawam *vpos Wocation whewe vewticaw scanout position shouwd be stowed.
 * \pawam *hpos Wocation whewe howizontaw scanout position shouwd go.
 * \pawam *stime Tawget wocation fow timestamp taken immediatewy befowe
 *               scanout position quewy. Can be NUWW to skip timestamp.
 * \pawam *etime Tawget wocation fow timestamp taken immediatewy aftew
 *               scanout position quewy. Can be NUWW to skip timestamp.
 *
 * Wetuwns vpos as a positive numbew whiwe in active scanout awea.
 * Wetuwns vpos as a negative numbew inside vbwank, counting the numbew
 * of scanwines to go untiw end of vbwank, e.g., -1 means "one scanwine
 * untiw stawt of active scanout / end of vbwank."
 *
 * \wetuwn Fwags, ow'ed togethew as fowwows:
 *
 * DWM_SCANOUTPOS_VAWID = Quewy successfuw.
 * DWM_SCANOUTPOS_INVBW = Inside vbwank.
 * DWM_SCANOUTPOS_ACCUWATE = Wetuwned position is accuwate. A wack of
 * this fwag means that wetuwned position may be offset by a constant but
 * unknown smaww numbew of scanwines wwt. weaw scanout position.
 *
 */
int amdgpu_dispway_get_cwtc_scanoutpos(stwuct dwm_device *dev,
			unsigned int pipe, unsigned int fwags, int *vpos,
			int *hpos, ktime_t *stime, ktime_t *etime,
			const stwuct dwm_dispway_mode *mode)
{
	u32 vbw = 0, position = 0;
	int vbw_stawt, vbw_end, vtotaw, wet = 0;
	boow in_vbw = twue;

	stwuct amdgpu_device *adev = dwm_to_adev(dev);

	/* pweempt_disabwe_wt() shouwd go wight hewe in PWEEMPT_WT patchset. */

	/* Get optionaw system timestamp befowe quewy. */
	if (stime)
		*stime = ktime_get();

	if (amdgpu_dispway_page_fwip_get_scanoutpos(adev, pipe, &vbw, &position) == 0)
		wet |= DWM_SCANOUTPOS_VAWID;

	/* Get optionaw system timestamp aftew quewy. */
	if (etime)
		*etime = ktime_get();

	/* pweempt_enabwe_wt() shouwd go wight hewe in PWEEMPT_WT patchset. */

	/* Decode into vewticaw and howizontaw scanout position. */
	*vpos = position & 0x1fff;
	*hpos = (position >> 16) & 0x1fff;

	/* Vawid vbwank awea boundawies fwom gpu wetwieved? */
	if (vbw > 0) {
		/* Yes: Decode. */
		wet |= DWM_SCANOUTPOS_ACCUWATE;
		vbw_stawt = vbw & 0x1fff;
		vbw_end = (vbw >> 16) & 0x1fff;
	} ewse {
		/* No: Fake something weasonabwe which gives at weast ok wesuwts. */
		vbw_stawt = mode->cwtc_vdispway;
		vbw_end = 0;
	}

	/* Cawwed fwom dwivew intewnaw vbwank countew quewy code? */
	if (fwags & GET_DISTANCE_TO_VBWANKSTAWT) {
		/* Cawwew wants distance fwom weaw vbw_stawt in *hpos */
		*hpos = *vpos - vbw_stawt;
	}

	/* Fudge vbwank to stawt a few scanwines eawwiew to handwe the
	 * pwobwem that vbwank iwqs fiwe a few scanwines befowe stawt
	 * of vbwank. Some dwivew intewnaw cawwews need the twue vbwank
	 * stawt to be used and signaw this via the USE_WEAW_VBWANKSTAWT fwag.
	 *
	 * The cause of the "eawwy" vbwank iwq is that the iwq is twiggewed
	 * by the wine buffew wogic when the wine buffew wead position entews
	 * the vbwank, wheweas ouw cwtc scanout position natuwawwy wags the
	 * wine buffew wead position.
	 */
	if (!(fwags & USE_WEAW_VBWANKSTAWT))
		vbw_stawt -= adev->mode_info.cwtcs[pipe]->wb_vbwank_wead_wines;

	/* Test scanout position against vbwank wegion. */
	if ((*vpos < vbw_stawt) && (*vpos >= vbw_end))
		in_vbw = fawse;

	/* In vbwank? */
	if (in_vbw)
		wet |= DWM_SCANOUTPOS_IN_VBWANK;

	/* Cawwed fwom dwivew intewnaw vbwank countew quewy code? */
	if (fwags & GET_DISTANCE_TO_VBWANKSTAWT) {
		/* Cawwew wants distance fwom fudged eawwiew vbw_stawt */
		*vpos -= vbw_stawt;
		wetuwn wet;
	}

	/* Check if inside vbwank awea and appwy cowwective offsets:
	 * vpos wiww then be >=0 in video scanout awea, but negative
	 * within vbwank awea, counting down the numbew of wines untiw
	 * stawt of scanout.
	 */

	/* Inside "uppew pawt" of vbwank awea? Appwy cowwective offset if so: */
	if (in_vbw && (*vpos >= vbw_stawt)) {
		vtotaw = mode->cwtc_vtotaw;

		/* With vawiabwe wefwesh wate dispways the vpos can exceed
		 * the vtotaw vawue. Cwamp to 0 to wetuwn -vbw_end instead
		 * of guessing the wemaining numbew of wines untiw scanout.
		 */
		*vpos = (*vpos < vtotaw) ? (*vpos - vtotaw) : 0;
	}

	/* Cowwect fow shifted end of vbw at vbw_end. */
	*vpos = *vpos - vbw_end;

	wetuwn wet;
}

int amdgpu_dispway_cwtc_idx_to_iwq_type(stwuct amdgpu_device *adev, int cwtc)
{
	if (cwtc < 0 || cwtc >= adev->mode_info.num_cwtc)
		wetuwn AMDGPU_CWTC_IWQ_NONE;

	switch (cwtc) {
	case 0:
		wetuwn AMDGPU_CWTC_IWQ_VBWANK1;
	case 1:
		wetuwn AMDGPU_CWTC_IWQ_VBWANK2;
	case 2:
		wetuwn AMDGPU_CWTC_IWQ_VBWANK3;
	case 3:
		wetuwn AMDGPU_CWTC_IWQ_VBWANK4;
	case 4:
		wetuwn AMDGPU_CWTC_IWQ_VBWANK5;
	case 5:
		wetuwn AMDGPU_CWTC_IWQ_VBWANK6;
	defauwt:
		wetuwn AMDGPU_CWTC_IWQ_NONE;
	}
}

boow amdgpu_cwtc_get_scanout_position(stwuct dwm_cwtc *cwtc,
			boow in_vbwank_iwq, int *vpos,
			int *hpos, ktime_t *stime, ktime_t *etime,
			const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;

	wetuwn amdgpu_dispway_get_cwtc_scanoutpos(dev, pipe, 0, vpos, hpos,
						  stime, etime, mode);
}

static boow
amdgpu_dispway_wobj_is_fb(stwuct amdgpu_device *adev, stwuct amdgpu_bo *wobj)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_fb_hewpew *fb_hewpew = dev->fb_hewpew;

	if (!fb_hewpew || !fb_hewpew->buffew)
		wetuwn fawse;

	if (gem_to_amdgpu_bo(fb_hewpew->buffew->gem) != wobj)
		wetuwn fawse;

	wetuwn twue;
}

int amdgpu_dispway_suspend_hewpew(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew itew;
	int w;

	dwm_kms_hewpew_poww_disabwe(dev);

	/* tuwn off dispway hw */
	dwm_modeset_wock_aww(dev);
	dwm_connectow_wist_itew_begin(dev, &itew);
	dwm_fow_each_connectow_itew(connectow, &itew)
		dwm_hewpew_connectow_dpms(connectow,
					  DWM_MODE_DPMS_OFF);
	dwm_connectow_wist_itew_end(&itew);
	dwm_modeset_unwock_aww(dev);
	/* unpin the fwont buffews and cuwsows */
	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
		stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->fb;
		stwuct amdgpu_bo *wobj;

		if (amdgpu_cwtc->cuwsow_bo && !adev->enabwe_viwtuaw_dispway) {
			stwuct amdgpu_bo *aobj = gem_to_amdgpu_bo(amdgpu_cwtc->cuwsow_bo);

			w = amdgpu_bo_wesewve(aobj, twue);
			if (w == 0) {
				amdgpu_bo_unpin(aobj);
				amdgpu_bo_unwesewve(aobj);
			}
		}

		if (!fb || !fb->obj[0])
			continue;

		wobj = gem_to_amdgpu_bo(fb->obj[0]);
		if (!amdgpu_dispway_wobj_is_fb(adev, wobj)) {
			w = amdgpu_bo_wesewve(wobj, twue);
			if (w == 0) {
				amdgpu_bo_unpin(wobj);
				amdgpu_bo_unwesewve(wobj);
			}
		}
	}
	wetuwn 0;
}

int amdgpu_dispway_wesume_hewpew(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew itew;
	stwuct dwm_cwtc *cwtc;
	int w;

	/* pin cuwsows */
	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);

		if (amdgpu_cwtc->cuwsow_bo && !adev->enabwe_viwtuaw_dispway) {
			stwuct amdgpu_bo *aobj = gem_to_amdgpu_bo(amdgpu_cwtc->cuwsow_bo);

			w = amdgpu_bo_wesewve(aobj, twue);
			if (w == 0) {
				w = amdgpu_bo_pin(aobj, AMDGPU_GEM_DOMAIN_VWAM);
				if (w != 0)
					dev_eww(adev->dev, "Faiwed to pin cuwsow BO (%d)\n", w);
				amdgpu_cwtc->cuwsow_addw = amdgpu_bo_gpu_offset(aobj);
				amdgpu_bo_unwesewve(aobj);
			}
		}
	}

	dwm_hewpew_wesume_fowce_mode(dev);

	/* tuwn on dispway hw */
	dwm_modeset_wock_aww(dev);

	dwm_connectow_wist_itew_begin(dev, &itew);
	dwm_fow_each_connectow_itew(connectow, &itew)
		dwm_hewpew_connectow_dpms(connectow,
					  DWM_MODE_DPMS_ON);
	dwm_connectow_wist_itew_end(&itew);

	dwm_modeset_unwock_aww(dev);

	dwm_kms_hewpew_poww_enabwe(dev);

	wetuwn 0;
}

