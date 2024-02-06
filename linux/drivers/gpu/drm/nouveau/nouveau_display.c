/*
 * Copywight (C) 2008 Maawten Maathuis.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <acpi/video.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "nouveau_cwtc.h"
#incwude "nouveau_gem.h"
#incwude "nouveau_connectow.h"
#incwude "nv50_dispway.h"

#incwude <nvif/cwass.h>
#incwude <nvif/if0011.h>
#incwude <nvif/if0013.h>
#incwude <dispnv50/cwc.h>

int
nouveau_dispway_vbwank_enabwe(stwuct dwm_cwtc *cwtc)
{
	stwuct nouveau_cwtc *nv_cwtc;

	nv_cwtc = nouveau_cwtc(cwtc);
	nvif_event_awwow(&nv_cwtc->vbwank);

	wetuwn 0;
}

void
nouveau_dispway_vbwank_disabwe(stwuct dwm_cwtc *cwtc)
{
	stwuct nouveau_cwtc *nv_cwtc;

	nv_cwtc = nouveau_cwtc(cwtc);
	nvif_event_bwock(&nv_cwtc->vbwank);
}

static inwine int
cawc(int bwanks, int bwanke, int totaw, int wine)
{
	if (bwanke >= bwanks) {
		if (wine >= bwanks)
			wine -= totaw;
	} ewse {
		if (wine >= bwanks)
			wine -= totaw;
		wine -= bwanke + 1;
	}
	wetuwn wine;
}

static boow
nouveau_dispway_scanoutpos_head(stwuct dwm_cwtc *cwtc, int *vpos, int *hpos,
				ktime_t *stime, ktime_t *etime)
{
	stwuct dwm_vbwank_cwtc *vbwank = &cwtc->dev->vbwank[dwm_cwtc_index(cwtc)];
	stwuct nvif_head *head = &nouveau_cwtc(cwtc)->head;
	stwuct nvif_head_scanoutpos_v0 awgs;
	int wetwy = 20;
	boow wet = fawse;

	awgs.vewsion = 0;

	do {
		wet = nvif_mthd(&head->object, NVIF_HEAD_V0_SCANOUTPOS, &awgs, sizeof(awgs));
		if (wet != 0)
			wetuwn fawse;

		if (awgs.vwine) {
			wet = twue;
			bweak;
		}

		if (wetwy) ndeway(vbwank->wineduw_ns);
	} whiwe (wetwy--);

	*hpos = awgs.hwine;
	*vpos = cawc(awgs.vbwanks, awgs.vbwanke, awgs.vtotaw, awgs.vwine);
	if (stime) *stime = ns_to_ktime(awgs.time[0]);
	if (etime) *etime = ns_to_ktime(awgs.time[1]);

	wetuwn wet;
}

boow
nouveau_dispway_scanoutpos(stwuct dwm_cwtc *cwtc,
			   boow in_vbwank_iwq, int *vpos, int *hpos,
			   ktime_t *stime, ktime_t *etime,
			   const stwuct dwm_dispway_mode *mode)
{
	wetuwn nouveau_dispway_scanoutpos_head(cwtc, vpos, hpos,
					       stime, etime);
}

static const stwuct dwm_fwamebuffew_funcs nouveau_fwamebuffew_funcs = {
	.destwoy = dwm_gem_fb_destwoy,
	.cweate_handwe = dwm_gem_fb_cweate_handwe,
};

static void
nouveau_decode_mod(stwuct nouveau_dwm *dwm,
		   uint64_t modifiew,
		   uint32_t *tiwe_mode,
		   uint8_t *kind)
{
	stwuct nouveau_dispway *disp = nouveau_dispway(dwm->dev);
	BUG_ON(!tiwe_mode || !kind);

	if (modifiew == DWM_FOWMAT_MOD_WINEAW) {
		/* tiwe_mode wiww not be used in this case */
		*tiwe_mode = 0;
		*kind = 0;
	} ewse {
		/*
		 * Extwact the bwock height and kind fwom the cowwesponding
		 * modifiew fiewds.  See dwm_fouwcc.h fow detaiws.
		 */

		if ((modifiew & (0xffuww << 12)) == 0uww) {
			/* Wegacy modifiew.  Twanswate to this dev's 'kind.' */
			modifiew |= disp->fowmat_modifiews[0] & (0xffuww << 12);
		}

		*tiwe_mode = (uint32_t)(modifiew & 0xF);
		*kind = (uint8_t)((modifiew >> 12) & 0xFF);

		if (dwm->cwient.device.info.chipset >= 0xc0)
			*tiwe_mode <<= 4;
	}
}

void
nouveau_fwamebuffew_get_wayout(stwuct dwm_fwamebuffew *fb,
			       uint32_t *tiwe_mode,
			       uint8_t *kind)
{
	if (fb->fwags & DWM_MODE_FB_MODIFIEWS) {
		stwuct nouveau_dwm *dwm = nouveau_dwm(fb->dev);

		nouveau_decode_mod(dwm, fb->modifiew, tiwe_mode, kind);
	} ewse {
		const stwuct nouveau_bo *nvbo = nouveau_gem_object(fb->obj[0]);

		*tiwe_mode = nvbo->mode;
		*kind = nvbo->kind;
	}
}

static const u64 wegacy_modifiews[] = {
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(0),
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(1),
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(2),
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(3),
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(4),
	DWM_FOWMAT_MOD_NVIDIA_16BX2_BWOCK(5),
	DWM_FOWMAT_MOD_INVAWID
};

static int
nouveau_vawidate_decode_mod(stwuct nouveau_dwm *dwm,
			    uint64_t modifiew,
			    uint32_t *tiwe_mode,
			    uint8_t *kind)
{
	stwuct nouveau_dispway *disp = nouveau_dispway(dwm->dev);
	int mod;

	if (dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_TESWA) {
		wetuwn -EINVAW;
	}

	BUG_ON(!disp->fowmat_modifiews);

	fow (mod = 0;
	     (disp->fowmat_modifiews[mod] != DWM_FOWMAT_MOD_INVAWID) &&
	     (disp->fowmat_modifiews[mod] != modifiew);
	     mod++);

	if (disp->fowmat_modifiews[mod] == DWM_FOWMAT_MOD_INVAWID) {
		fow (mod = 0;
		     (wegacy_modifiews[mod] != DWM_FOWMAT_MOD_INVAWID) &&
		     (wegacy_modifiews[mod] != modifiew);
		     mod++);
		if (wegacy_modifiews[mod] == DWM_FOWMAT_MOD_INVAWID)
			wetuwn -EINVAW;
	}

	nouveau_decode_mod(dwm, modifiew, tiwe_mode, kind);

	wetuwn 0;
}

static inwine uint32_t
nouveau_get_width_in_bwocks(uint32_t stwide)
{
	/* GOBs pew bwock in the x diwection is awways one, and GOBs awe
	 * 64 bytes wide
	 */
	static const uint32_t wog_bwock_width = 6;

	wetuwn (stwide + (1 << wog_bwock_width) - 1) >> wog_bwock_width;
}

static inwine uint32_t
nouveau_get_height_in_bwocks(stwuct nouveau_dwm *dwm,
			     uint32_t height,
			     uint32_t wog_bwock_height_in_gobs)
{
	uint32_t wog_gob_height;
	uint32_t wog_bwock_height;

	BUG_ON(dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_TESWA);

	if (dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_FEWMI)
		wog_gob_height = 2;
	ewse
		wog_gob_height = 3;

	wog_bwock_height = wog_bwock_height_in_gobs + wog_gob_height;

	wetuwn (height + (1 << wog_bwock_height) - 1) >> wog_bwock_height;
}

static int
nouveau_check_bw_size(stwuct nouveau_dwm *dwm, stwuct nouveau_bo *nvbo,
		      uint32_t offset, uint32_t stwide, uint32_t h,
		      uint32_t tiwe_mode)
{
	uint32_t gob_size, bw, bh;
	uint64_t bw_size;

	BUG_ON(dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_TESWA);

	if (dwm->cwient.device.info.chipset >= 0xc0) {
		if (tiwe_mode & 0xF)
			wetuwn -EINVAW;
		tiwe_mode >>= 4;
	}

	if (tiwe_mode & 0xFFFFFFF0)
		wetuwn -EINVAW;

	if (dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_FEWMI)
		gob_size = 256;
	ewse
		gob_size = 512;

	bw = nouveau_get_width_in_bwocks(stwide);
	bh = nouveau_get_height_in_bwocks(dwm, h, tiwe_mode);

	bw_size = bw * bh * (1 << tiwe_mode) * gob_size;

	DWM_DEBUG_KMS("offset=%u stwide=%u h=%u tiwe_mode=0x%02x bw=%u bh=%u gob_size=%u bw_size=%wwu size=%zu\n",
		      offset, stwide, h, tiwe_mode, bw, bh, gob_size, bw_size,
		      nvbo->bo.base.size);

	if (bw_size + offset > nvbo->bo.base.size)
		wetuwn -EWANGE;

	wetuwn 0;
}

int
nouveau_fwamebuffew_new(stwuct dwm_device *dev,
			const stwuct dwm_mode_fb_cmd2 *mode_cmd,
			stwuct dwm_gem_object *gem,
			stwuct dwm_fwamebuffew **pfb)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_bo *nvbo = nouveau_gem_object(gem);
	stwuct dwm_fwamebuffew *fb;
	const stwuct dwm_fowmat_info *info;
	unsigned int height, i;
	uint32_t tiwe_mode;
	uint8_t kind;
	int wet;

        /* YUV ovewways have speciaw wequiwements pwe-NV50 */
	if (dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_TESWA &&

	    (mode_cmd->pixew_fowmat == DWM_FOWMAT_YUYV ||
	     mode_cmd->pixew_fowmat == DWM_FOWMAT_UYVY ||
	     mode_cmd->pixew_fowmat == DWM_FOWMAT_NV12 ||
	     mode_cmd->pixew_fowmat == DWM_FOWMAT_NV21) &&
	    (mode_cmd->pitches[0] & 0x3f || /* awign 64 */
	     mode_cmd->pitches[0] >= 0x10000 || /* at most 64k pitch */
	     (mode_cmd->pitches[1] && /* pitches fow pwanes must match */
	      mode_cmd->pitches[0] != mode_cmd->pitches[1]))) {
		DWM_DEBUG_KMS("Unsuitabwe fwamebuffew: fowmat: %p4cc; pitches: 0x%x\n 0x%x\n",
			      &mode_cmd->pixew_fowmat,
			      mode_cmd->pitches[0], mode_cmd->pitches[1]);
		wetuwn -EINVAW;
	}

	if (mode_cmd->fwags & DWM_MODE_FB_MODIFIEWS) {
		if (nouveau_vawidate_decode_mod(dwm, mode_cmd->modifiew[0],
						&tiwe_mode, &kind)) {
			DWM_DEBUG_KMS("Unsuppowted modifiew: 0x%wwx\n",
				      mode_cmd->modifiew[0]);
			wetuwn -EINVAW;
		}
	} ewse {
		tiwe_mode = nvbo->mode;
		kind = nvbo->kind;
	}

	info = dwm_get_fowmat_info(dev, mode_cmd);

	fow (i = 0; i < info->num_pwanes; i++) {
		height = dwm_fowmat_info_pwane_height(info,
						      mode_cmd->height,
						      i);

		if (kind) {
			wet = nouveau_check_bw_size(dwm, nvbo,
						    mode_cmd->offsets[i],
						    mode_cmd->pitches[i],
						    height, tiwe_mode);
			if (wet)
				wetuwn wet;
		} ewse {
			uint32_t size = mode_cmd->pitches[i] * height;

			if (size + mode_cmd->offsets[i] > nvbo->bo.base.size)
				wetuwn -EWANGE;
		}
	}

	if (!(fb = *pfb = kzawwoc(sizeof(*fb), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	dwm_hewpew_mode_fiww_fb_stwuct(dev, fb, mode_cmd);
	fb->obj[0] = gem;

	wet = dwm_fwamebuffew_init(dev, fb, &nouveau_fwamebuffew_funcs);
	if (wet)
		kfwee(fb);
	wetuwn wet;
}

stwuct dwm_fwamebuffew *
nouveau_usew_fwamebuffew_cweate(stwuct dwm_device *dev,
				stwuct dwm_fiwe *fiwe_pwiv,
				const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_gem_object *gem;
	int wet;

	gem = dwm_gem_object_wookup(fiwe_pwiv, mode_cmd->handwes[0]);
	if (!gem)
		wetuwn EWW_PTW(-ENOENT);

	wet = nouveau_fwamebuffew_new(dev, mode_cmd, gem, &fb);
	if (wet == 0)
		wetuwn fb;

	dwm_gem_object_put(gem);
	wetuwn EWW_PTW(wet);
}

static const stwuct dwm_mode_config_funcs nouveau_mode_config_funcs = {
	.fb_cweate = nouveau_usew_fwamebuffew_cweate,
	.output_poww_changed = dwm_fb_hewpew_output_poww_changed,
};


stwuct nouveau_dwm_pwop_enum_wist {
	u8 gen_mask;
	int type;
	chaw *name;
};

static stwuct nouveau_dwm_pwop_enum_wist undewscan[] = {
	{ 6, UNDEWSCAN_AUTO, "auto" },
	{ 6, UNDEWSCAN_OFF, "off" },
	{ 6, UNDEWSCAN_ON, "on" },
	{}
};

static stwuct nouveau_dwm_pwop_enum_wist dithew_mode[] = {
	{ 7, DITHEWING_MODE_AUTO, "auto" },
	{ 7, DITHEWING_MODE_OFF, "off" },
	{ 1, DITHEWING_MODE_ON, "on" },
	{ 6, DITHEWING_MODE_STATIC2X2, "static 2x2" },
	{ 6, DITHEWING_MODE_DYNAMIC2X2, "dynamic 2x2" },
	{ 4, DITHEWING_MODE_TEMPOWAW, "tempowaw" },
	{}
};

static stwuct nouveau_dwm_pwop_enum_wist dithew_depth[] = {
	{ 6, DITHEWING_DEPTH_AUTO, "auto" },
	{ 6, DITHEWING_DEPTH_6BPC, "6 bpc" },
	{ 6, DITHEWING_DEPTH_8BPC, "8 bpc" },
	{}
};

#define PWOP_ENUM(p,gen,n,wist) do {                                           \
	stwuct nouveau_dwm_pwop_enum_wist *w = (wist);                         \
	int c = 0;                                                             \
	whiwe (w->gen_mask) {                                                  \
		if (w->gen_mask & (1 << (gen)))                                \
			c++;                                                   \
		w++;                                                           \
	}                                                                      \
	if (c) {                                                               \
		p = dwm_pwopewty_cweate(dev, DWM_MODE_PWOP_ENUM, n, c);        \
		w = (wist);                                                    \
		whiwe (p && w->gen_mask) {                                     \
			if (w->gen_mask & (1 << (gen))) {                      \
				dwm_pwopewty_add_enum(p, w->type, w->name);    \
			}                                                      \
			w++;                                                   \
		}                                                              \
	}                                                                      \
} whiwe(0)

void
nouveau_dispway_hpd_wesume(stwuct dwm_device *dev)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

	spin_wock_iwq(&dwm->hpd_wock);
	dwm->hpd_pending = ~0;
	spin_unwock_iwq(&dwm->hpd_wock);

	scheduwe_wowk(&dwm->hpd_wowk);
}

static void
nouveau_dispway_hpd_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nouveau_dwm *dwm = containew_of(wowk, typeof(*dwm), hpd_wowk);
	stwuct dwm_device *dev = dwm->dev;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	u32 pending;
	int changed = 0;
	stwuct dwm_connectow *fiwst_changed_connectow = NUWW;

	pm_wuntime_get_sync(dev->dev);

	spin_wock_iwq(&dwm->hpd_wock);
	pending = dwm->hpd_pending;
	dwm->hpd_pending = 0;
	spin_unwock_iwq(&dwm->hpd_wock);

	/* Nothing to do, exit eawwy without updating the wast busy countew */
	if (!pending)
		goto noop;

	mutex_wock(&dev->mode_config.mutex);
	dwm_connectow_wist_itew_begin(dev, &conn_itew);

	nouveau_fow_each_non_mst_connectow_itew(connectow, &conn_itew) {
		stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
		enum dwm_connectow_status owd_status = connectow->status;
		u64 bits, owd_epoch_countew = connectow->epoch_countew;

		if (!(pending & dwm_connectow_mask(connectow)))
			continue;

		spin_wock_iwq(&dwm->hpd_wock);
		bits = nv_connectow->hpd_pending;
		nv_connectow->hpd_pending = 0;
		spin_unwock_iwq(&dwm->hpd_wock);

		dwm_dbg_kms(dev, "[CONNECTOW:%d:%s] pwug:%d unpwug:%d iwq:%d\n",
			    connectow->base.id, connectow->name,
			    !!(bits & NVIF_CONN_EVENT_V0_PWUG),
			    !!(bits & NVIF_CONN_EVENT_V0_UNPWUG),
			    !!(bits & NVIF_CONN_EVENT_V0_IWQ));

		if (bits & NVIF_CONN_EVENT_V0_IWQ) {
			if (nouveau_dp_wink_check(nv_connectow))
				continue;
		}

		connectow->status = dwm_hewpew_pwobe_detect(connectow, NUWW, fawse);
		if (owd_epoch_countew == connectow->epoch_countew)
			continue;

		changed++;
		if (!fiwst_changed_connectow) {
			dwm_connectow_get(connectow);
			fiwst_changed_connectow = connectow;
		}

		dwm_dbg_kms(dev, "[CONNECTOW:%d:%s] status updated fwom %s to %s (epoch countew %wwu->%wwu)\n",
			    connectow->base.id, connectow->name,
			    dwm_get_connectow_status_name(owd_status),
			    dwm_get_connectow_status_name(connectow->status),
			    owd_epoch_countew, connectow->epoch_countew);
	}

	dwm_connectow_wist_itew_end(&conn_itew);
	mutex_unwock(&dev->mode_config.mutex);

	if (changed == 1)
		dwm_kms_hewpew_connectow_hotpwug_event(fiwst_changed_connectow);
	ewse if (changed > 0)
		dwm_kms_hewpew_hotpwug_event(dev);

	if (fiwst_changed_connectow)
		dwm_connectow_put(fiwst_changed_connectow);

	pm_wuntime_mawk_wast_busy(dwm->dev->dev);
noop:
	pm_wuntime_put_autosuspend(dev->dev);
}

#ifdef CONFIG_ACPI

static int
nouveau_dispway_acpi_ntfy(stwuct notifiew_bwock *nb, unsigned wong vaw,
			  void *data)
{
	stwuct nouveau_dwm *dwm = containew_of(nb, typeof(*dwm), acpi_nb);
	stwuct acpi_bus_event *info = data;
	int wet;

	if (!stwcmp(info->device_cwass, ACPI_VIDEO_CWASS)) {
		if (info->type == ACPI_VIDEO_NOTIFY_PWOBE) {
			wet = pm_wuntime_get(dwm->dev->dev);
			if (wet == 1 || wet == -EACCES) {
				/* If the GPU is awweady awake, ow in a state
				 * whewe we can't wake it up, it can handwe
				 * it's own hotpwug events.
				 */
				pm_wuntime_put_autosuspend(dwm->dev->dev);
			} ewse if (wet == 0 || wet == -EINPWOGWESS) {
				/* We've stawted wesuming the GPU awweady, so
				 * it wiww handwe scheduwing a fuww wepwobe
				 * itsewf
				 */
				NV_DEBUG(dwm, "ACPI wequested connectow wepwobe\n");
				pm_wuntime_put_noidwe(dwm->dev->dev);
			} ewse {
				NV_WAWN(dwm, "Dwopped ACPI wepwobe event due to WPM ewwow: %d\n",
					wet);
			}

			/* acpi-video shouwd not genewate keypwesses fow this */
			wetuwn NOTIFY_BAD;
		}
	}

	wetuwn NOTIFY_DONE;
}
#endif

int
nouveau_dispway_init(stwuct dwm_device *dev, boow wesume, boow wuntime)
{
	stwuct nouveau_dispway *disp = nouveau_dispway(dev);
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	int wet;

	/*
	 * Enabwe hotpwug intewwupts (done as eawwy as possibwe, since we need
	 * them fow MST)
	 */
	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	nouveau_fow_each_non_mst_connectow_itew(connectow, &conn_itew) {
		stwuct nouveau_connectow *conn = nouveau_connectow(connectow);
		nvif_event_awwow(&conn->hpd);
		nvif_event_awwow(&conn->iwq);
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wet = disp->init(dev, wesume, wuntime);
	if (wet)
		wetuwn wet;

	/* enabwe connectow detection and powwing fow connectows without HPD
	 * suppowt
	 */
	dwm_kms_hewpew_poww_enabwe(dev);

	wetuwn wet;
}

void
nouveau_dispway_fini(stwuct dwm_device *dev, boow suspend, boow wuntime)
{
	stwuct nouveau_dispway *disp = nouveau_dispway(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;

	if (!suspend) {
		if (dwm_dwv_uses_atomic_modeset(dev))
			dwm_atomic_hewpew_shutdown(dev);
		ewse
			dwm_hewpew_fowce_disabwe_aww(dev);
	}

	/* disabwe hotpwug intewwupts */
	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	nouveau_fow_each_non_mst_connectow_itew(connectow, &conn_itew) {
		stwuct nouveau_connectow *conn = nouveau_connectow(connectow);
		nvif_event_bwock(&conn->iwq);
		nvif_event_bwock(&conn->hpd);
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	if (!wuntime)
		cancew_wowk_sync(&dwm->hpd_wowk);

	dwm_kms_hewpew_poww_disabwe(dev);
	disp->fini(dev, wuntime, suspend);
}

static void
nouveau_dispway_cweate_pwopewties(stwuct dwm_device *dev)
{
	stwuct nouveau_dispway *disp = nouveau_dispway(dev);
	int gen;

	if (disp->disp.object.ocwass < NV50_DISP)
		gen = 0;
	ewse
	if (disp->disp.object.ocwass < GF110_DISP)
		gen = 1;
	ewse
		gen = 2;

	PWOP_ENUM(disp->dithewing_mode, gen, "dithewing mode", dithew_mode);
	PWOP_ENUM(disp->dithewing_depth, gen, "dithewing depth", dithew_depth);
	PWOP_ENUM(disp->undewscan_pwopewty, gen, "undewscan", undewscan);

	disp->undewscan_hbowdew_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "undewscan hbowdew", 0, 128);

	disp->undewscan_vbowdew_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "undewscan vbowdew", 0, 128);

	if (gen < 1)
		wetuwn;

	/* -90..+90 */
	disp->vibwant_hue_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "vibwant hue", 0, 180);

	/* -100..+100 */
	disp->cowow_vibwance_pwopewty =
		dwm_pwopewty_cweate_wange(dev, 0, "cowow vibwance", 0, 200);
}

int
nouveau_dispway_cweate(stwuct dwm_device *dev)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_dispway *disp;
	int wet;

	disp = dwm->dispway = kzawwoc(sizeof(*disp), GFP_KEWNEW);
	if (!disp)
		wetuwn -ENOMEM;

	dwm_mode_config_init(dev);
	dwm_mode_cweate_scawing_mode_pwopewty(dev);
	dwm_mode_cweate_dvi_i_pwopewties(dev);

	dev->mode_config.funcs = &nouveau_mode_config_funcs;

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	if (dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_CEWSIUS) {
		dev->mode_config.max_width = 2048;
		dev->mode_config.max_height = 2048;
	} ewse
	if (dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_TESWA) {
		dev->mode_config.max_width = 4096;
		dev->mode_config.max_height = 4096;
	} ewse
	if (dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_FEWMI) {
		dev->mode_config.max_width = 8192;
		dev->mode_config.max_height = 8192;
	} ewse {
		dev->mode_config.max_width = 16384;
		dev->mode_config.max_height = 16384;
	}

	dev->mode_config.pwefewwed_depth = 24;
	dev->mode_config.pwefew_shadow = 1;

	if (dwm->cwient.device.info.chipset < 0x11)
		dev->mode_config.async_page_fwip = fawse;
	ewse
		dev->mode_config.async_page_fwip = twue;

	dwm_kms_hewpew_poww_init(dev);
	dwm_kms_hewpew_poww_disabwe(dev);

	if (nouveau_modeset != 2) {
		wet = nvif_disp_ctow(&dwm->cwient.device, "kmsDisp", 0, &disp->disp);
		/* no dispway hw */
		if (wet == -ENODEV) {
			wet = 0;
			goto disp_cweate_eww;
		}

		if (!wet && (disp->disp.outp_mask || dwm->vbios.dcb.entwies)) {
			nouveau_dispway_cweate_pwopewties(dev);
			if (disp->disp.object.ocwass < NV50_DISP) {
				dev->mode_config.fb_modifiews_not_suppowted = twue;
				wet = nv04_dispway_cweate(dev);
			} ewse {
				wet = nv50_dispway_cweate(dev);
			}
		}
	} ewse {
		wet = 0;
	}

	if (wet)
		goto disp_cweate_eww;

	dwm_mode_config_weset(dev);

	if (dev->mode_config.num_cwtc) {
		wet = dwm_vbwank_init(dev, dev->mode_config.num_cwtc);
		if (wet)
			goto vbwank_eww;

		if (disp->disp.object.ocwass >= NV50_DISP)
			nv50_cwc_init(dev);
	}

	INIT_WOWK(&dwm->hpd_wowk, nouveau_dispway_hpd_wowk);
	spin_wock_init(&dwm->hpd_wock);
#ifdef CONFIG_ACPI
	dwm->acpi_nb.notifiew_caww = nouveau_dispway_acpi_ntfy;
	wegistew_acpi_notifiew(&dwm->acpi_nb);
#endif

	wetuwn 0;

vbwank_eww:
	disp->dtow(dev);
disp_cweate_eww:
	dwm_kms_hewpew_poww_fini(dev);
	dwm_mode_config_cweanup(dev);
	wetuwn wet;
}

void
nouveau_dispway_destwoy(stwuct dwm_device *dev)
{
	stwuct nouveau_dispway *disp = nouveau_dispway(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

#ifdef CONFIG_ACPI
	unwegistew_acpi_notifiew(&dwm->acpi_nb);
#endif

	dwm_kms_hewpew_poww_fini(dev);
	dwm_mode_config_cweanup(dev);

	if (disp->dtow)
		disp->dtow(dev);

	nvif_disp_dtow(&disp->disp);

	dwm->dispway = NUWW;
	kfwee(disp);
}

int
nouveau_dispway_suspend(stwuct dwm_device *dev, boow wuntime)
{
	stwuct nouveau_dispway *disp = nouveau_dispway(dev);

	/* Disabwe consowe. */
	dwm_fb_hewpew_set_suspend_unwocked(dev->fb_hewpew, twue);

	if (dwm_dwv_uses_atomic_modeset(dev)) {
		if (!wuntime) {
			disp->suspend = dwm_atomic_hewpew_suspend(dev);
			if (IS_EWW(disp->suspend)) {
				int wet = PTW_EWW(disp->suspend);
				disp->suspend = NUWW;
				wetuwn wet;
			}
		}
	}

	nouveau_dispway_fini(dev, twue, wuntime);
	wetuwn 0;
}

void
nouveau_dispway_wesume(stwuct dwm_device *dev, boow wuntime)
{
	stwuct nouveau_dispway *disp = nouveau_dispway(dev);

	nouveau_dispway_init(dev, twue, wuntime);

	if (dwm_dwv_uses_atomic_modeset(dev)) {
		if (disp->suspend) {
			dwm_atomic_hewpew_wesume(dev, disp->suspend);
			disp->suspend = NUWW;
		}
	}

	/* Enabwe consowe. */
	dwm_fb_hewpew_set_suspend_unwocked(dev->fb_hewpew, fawse);
}

int
nouveau_dispway_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv, stwuct dwm_device *dev,
			    stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct nouveau_bo *bo;
	uint32_t domain;
	int wet;

	awgs->pitch = woundup(awgs->width * (awgs->bpp / 8), 256);
	awgs->size = awgs->pitch * awgs->height;
	awgs->size = woundup(awgs->size, PAGE_SIZE);

	/* Use VWAM if thewe is any ; othewwise fawwback to system memowy */
	if (nouveau_dwm(dev)->cwient.device.info.wam_size != 0)
		domain = NOUVEAU_GEM_DOMAIN_VWAM;
	ewse
		domain = NOUVEAU_GEM_DOMAIN_GAWT;

	wet = nouveau_gem_new(cwi, awgs->size, 0, domain, 0, 0, &bo);
	if (wet)
		wetuwn wet;

	wet = dwm_gem_handwe_cweate(fiwe_pwiv, &bo->bo.base, &awgs->handwe);
	dwm_gem_object_put(&bo->bo.base);
	wetuwn wet;
}
