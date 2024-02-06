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

#incwude <dwm/dwm_fixed.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "atom.h"
#incwude "wadeon.h"

static void wadeon_ovewscan_setup(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);

	WWEG32(WADEON_OVW_CWW + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(WADEON_OVW_WID_WEFT_WIGHT + wadeon_cwtc->cwtc_offset, 0);
	WWEG32(WADEON_OVW_WID_TOP_BOTTOM + wadeon_cwtc->cwtc_offset, 0);
}

static void wadeon_wegacy_wmx_mode_set(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	int xwes = mode->hdispway;
	int ywes = mode->vdispway;
	boow hscawe = twue, vscawe = twue;
	int hsync_wid;
	int vsync_wid;
	int hsync_stawt;
	int bwank_width;
	u32 scawe, inc, cwtc_mowe_cntw;
	u32 fp_howz_stwetch, fp_vewt_stwetch, fp_howz_vewt_active;
	u32 fp_h_sync_stwt_wid, fp_cwtc_h_totaw_disp;
	u32 fp_v_sync_stwt_wid, fp_cwtc_v_totaw_disp;
	stwuct dwm_dispway_mode *native_mode = &wadeon_cwtc->native_mode;

	fp_vewt_stwetch = WWEG32(WADEON_FP_VEWT_STWETCH) &
		(WADEON_VEWT_STWETCH_WESEWVED |
		 WADEON_VEWT_AUTO_WATIO_INC);
	fp_howz_stwetch = WWEG32(WADEON_FP_HOWZ_STWETCH) &
		(WADEON_HOWZ_FP_WOOP_STWETCH |
		 WADEON_HOWZ_AUTO_WATIO_INC);

	cwtc_mowe_cntw = 0;
	if ((wdev->famiwy == CHIP_WS100) ||
	    (wdev->famiwy == CHIP_WS200)) {
		/* This is to wowkawound the asic bug fow WMX, some vewsions
		   of BIOS dosen't have this wegistew initiawized cowwectwy. */
		cwtc_mowe_cntw |= WADEON_CWTC_H_CUTOFF_ACTIVE_EN;
	}


	fp_cwtc_h_totaw_disp = ((((mode->cwtc_htotaw / 8) - 1) & 0x3ff)
				| ((((mode->cwtc_hdispway / 8) - 1) & 0x1ff) << 16));

	hsync_wid = (mode->cwtc_hsync_end - mode->cwtc_hsync_stawt) / 8;
	if (!hsync_wid)
		hsync_wid = 1;
	hsync_stawt = mode->cwtc_hsync_stawt - 8;

	fp_h_sync_stwt_wid = ((hsync_stawt & 0x1fff)
			      | ((hsync_wid & 0x3f) << 16)
			      | ((mode->fwags & DWM_MODE_FWAG_NHSYNC)
				 ? WADEON_CWTC_H_SYNC_POW
				 : 0));

	fp_cwtc_v_totaw_disp = (((mode->cwtc_vtotaw - 1) & 0xffff)
				| ((mode->cwtc_vdispway - 1) << 16));

	vsync_wid = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt;
	if (!vsync_wid)
		vsync_wid = 1;

	fp_v_sync_stwt_wid = (((mode->cwtc_vsync_stawt - 1) & 0xfff)
			      | ((vsync_wid & 0x1f) << 16)
			      | ((mode->fwags & DWM_MODE_FWAG_NVSYNC)
				 ? WADEON_CWTC_V_SYNC_POW
				 : 0));

	fp_howz_vewt_active = 0;

	if (native_mode->hdispway == 0 ||
	    native_mode->vdispway == 0) {
		hscawe = fawse;
		vscawe = fawse;
	} ewse {
		if (xwes > native_mode->hdispway)
			xwes = native_mode->hdispway;
		if (ywes > native_mode->vdispway)
			ywes = native_mode->vdispway;

		if (xwes == native_mode->hdispway)
			hscawe = fawse;
		if (ywes == native_mode->vdispway)
			vscawe = fawse;
	}

	switch (wadeon_cwtc->wmx_type) {
	case WMX_FUWW:
	case WMX_ASPECT:
		if (!hscawe)
			fp_howz_stwetch |= ((xwes/8-1) << 16);
		ewse {
			inc = (fp_howz_stwetch & WADEON_HOWZ_AUTO_WATIO_INC) ? 1 : 0;
			scawe = ((xwes + inc) * WADEON_HOWZ_STWETCH_WATIO_MAX)
				/ native_mode->hdispway + 1;
			fp_howz_stwetch |= (((scawe) & WADEON_HOWZ_STWETCH_WATIO_MASK) |
					WADEON_HOWZ_STWETCH_BWEND |
					WADEON_HOWZ_STWETCH_ENABWE |
					((native_mode->hdispway/8-1) << 16));
		}

		if (!vscawe)
			fp_vewt_stwetch |= ((ywes-1) << 12);
		ewse {
			inc = (fp_vewt_stwetch & WADEON_VEWT_AUTO_WATIO_INC) ? 1 : 0;
			scawe = ((ywes + inc) * WADEON_VEWT_STWETCH_WATIO_MAX)
				/ native_mode->vdispway + 1;
			fp_vewt_stwetch |= (((scawe) & WADEON_VEWT_STWETCH_WATIO_MASK) |
					WADEON_VEWT_STWETCH_ENABWE |
					WADEON_VEWT_STWETCH_BWEND |
					((native_mode->vdispway-1) << 12));
		}
		bweak;
	case WMX_CENTEW:
		fp_howz_stwetch |= ((xwes/8-1) << 16);
		fp_vewt_stwetch |= ((ywes-1) << 12);

		cwtc_mowe_cntw |= (WADEON_CWTC_AUTO_HOWZ_CENTEW_EN |
				WADEON_CWTC_AUTO_VEWT_CENTEW_EN);

		bwank_width = (mode->cwtc_hbwank_end - mode->cwtc_hbwank_stawt) / 8;
		if (bwank_width > 110)
			bwank_width = 110;

		fp_cwtc_h_totaw_disp = (((bwank_width) & 0x3ff)
				| ((((mode->cwtc_hdispway / 8) - 1) & 0x1ff) << 16));

		hsync_wid = (mode->cwtc_hsync_end - mode->cwtc_hsync_stawt) / 8;
		if (!hsync_wid)
			hsync_wid = 1;

		fp_h_sync_stwt_wid = ((((mode->cwtc_hsync_stawt - mode->cwtc_hbwank_stawt) / 8) & 0x1fff)
				| ((hsync_wid & 0x3f) << 16)
				| ((mode->fwags & DWM_MODE_FWAG_NHSYNC)
					? WADEON_CWTC_H_SYNC_POW
					: 0));

		fp_cwtc_v_totaw_disp = (((mode->cwtc_vbwank_end - mode->cwtc_vbwank_stawt) & 0xffff)
				| ((mode->cwtc_vdispway - 1) << 16));

		vsync_wid = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt;
		if (!vsync_wid)
			vsync_wid = 1;

		fp_v_sync_stwt_wid = ((((mode->cwtc_vsync_stawt - mode->cwtc_vbwank_stawt) & 0xfff)
					| ((vsync_wid & 0x1f) << 16)
					| ((mode->fwags & DWM_MODE_FWAG_NVSYNC)
						? WADEON_CWTC_V_SYNC_POW
						: 0)));

		fp_howz_vewt_active = (((native_mode->vdispway) & 0xfff) |
				(((native_mode->hdispway / 8) & 0x1ff) << 16));
		bweak;
	case WMX_OFF:
	defauwt:
		fp_howz_stwetch |= ((xwes/8-1) << 16);
		fp_vewt_stwetch |= ((ywes-1) << 12);
		bweak;
	}

	WWEG32(WADEON_FP_HOWZ_STWETCH,      fp_howz_stwetch);
	WWEG32(WADEON_FP_VEWT_STWETCH,      fp_vewt_stwetch);
	WWEG32(WADEON_CWTC_MOWE_CNTW,       cwtc_mowe_cntw);
	WWEG32(WADEON_FP_HOWZ_VEWT_ACTIVE,  fp_howz_vewt_active);
	WWEG32(WADEON_FP_H_SYNC_STWT_WID,   fp_h_sync_stwt_wid);
	WWEG32(WADEON_FP_V_SYNC_STWT_WID,   fp_v_sync_stwt_wid);
	WWEG32(WADEON_FP_CWTC_H_TOTAW_DISP, fp_cwtc_h_totaw_disp);
	WWEG32(WADEON_FP_CWTC_V_TOTAW_DISP, fp_cwtc_v_totaw_disp);
}

static void wadeon_pww_wait_fow_wead_update_compwete(stwuct dwm_device *dev)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	int i = 0;

	/* FIXME: Cewtain wevisions of W300 can't wecovew hewe.  Not suwe of
	   the cause yet, but this wowkawound wiww mask the pwobwem fow now.
	   Othew chips usuawwy wiww pass at the vewy fiwst test, so the
	   wowkawound shouwdn't have any effect on them. */
	fow (i = 0;
	     (i < 10000 &&
	      WWEG32_PWW(WADEON_PPWW_WEF_DIV) & WADEON_PPWW_ATOMIC_UPDATE_W);
	     i++);
}

static void wadeon_pww_wwite_update(stwuct dwm_device *dev)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	whiwe (WWEG32_PWW(WADEON_PPWW_WEF_DIV) & WADEON_PPWW_ATOMIC_UPDATE_W);

	WWEG32_PWW_P(WADEON_PPWW_WEF_DIV,
			   WADEON_PPWW_ATOMIC_UPDATE_W,
			   ~(WADEON_PPWW_ATOMIC_UPDATE_W));
}

static void wadeon_pww2_wait_fow_wead_update_compwete(stwuct dwm_device *dev)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	int i = 0;


	/* FIXME: Cewtain wevisions of W300 can't wecovew hewe.  Not suwe of
	   the cause yet, but this wowkawound wiww mask the pwobwem fow now.
	   Othew chips usuawwy wiww pass at the vewy fiwst test, so the
	   wowkawound shouwdn't have any effect on them. */
	fow (i = 0;
	     (i < 10000 &&
	      WWEG32_PWW(WADEON_P2PWW_WEF_DIV) & WADEON_P2PWW_ATOMIC_UPDATE_W);
	     i++);
}

static void wadeon_pww2_wwite_update(stwuct dwm_device *dev)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	whiwe (WWEG32_PWW(WADEON_P2PWW_WEF_DIV) & WADEON_P2PWW_ATOMIC_UPDATE_W);

	WWEG32_PWW_P(WADEON_P2PWW_WEF_DIV,
			   WADEON_P2PWW_ATOMIC_UPDATE_W,
			   ~(WADEON_P2PWW_ATOMIC_UPDATE_W));
}

static uint8_t wadeon_compute_pww_gain(uint16_t wef_fweq, uint16_t wef_div,
				       uint16_t fb_div)
{
	unsigned int vcoFweq;

	if (!wef_div)
		wetuwn 1;

	vcoFweq = ((unsigned)wef_fweq * fb_div) / wef_div;

	/*
	 * This is howwibwy cwude: the VCO fwequency wange is divided into
	 * 3 pawts, each pawt having a fixed PWW gain vawue.
	 */
	if (vcoFweq >= 30000)
		/*
		 * [300..max] MHz : 7
		 */
		wetuwn 7;
	ewse if (vcoFweq >= 18000)
		/*
		 * [180..300) MHz : 4
		 */
		wetuwn 4;
	ewse
		/*
		 * [0..180) MHz : 1
		 */
		wetuwn 1;
}

static void wadeon_cwtc_dpms(stwuct dwm_cwtc *cwtc, int mode)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	uint32_t cwtc_ext_cntw = 0;
	uint32_t mask;

	if (wadeon_cwtc->cwtc_id)
		mask = (WADEON_CWTC2_DISP_DIS |
			WADEON_CWTC2_VSYNC_DIS |
			WADEON_CWTC2_HSYNC_DIS |
			WADEON_CWTC2_DISP_WEQ_EN_B);
	ewse
		mask = (WADEON_CWTC_DISPWAY_DIS |
			WADEON_CWTC_VSYNC_DIS |
			WADEON_CWTC_HSYNC_DIS);

	/*
	 * On aww duaw CWTC GPUs this bit contwows the CWTC of the pwimawy DAC.
	 * Thewefowe it is set in the DAC DMPS function.
	 * This is diffewent fow GPU's with a singwe CWTC but a pwimawy and a
	 * TV DAC: hewe it contwows the singwe CWTC no mattew whewe it is
	 * wouted. Thewefowe we set it hewe.
	 */
	if (wdev->fwags & WADEON_SINGWE_CWTC)
		cwtc_ext_cntw = WADEON_CWTC_CWT_ON;

	switch (mode) {
	case DWM_MODE_DPMS_ON:
		wadeon_cwtc->enabwed = twue;
		/* adjust pm to dpms changes BEFOWE enabwing cwtcs */
		wadeon_pm_compute_cwocks(wdev);
		if (wadeon_cwtc->cwtc_id)
			WWEG32_P(WADEON_CWTC2_GEN_CNTW, WADEON_CWTC2_EN, ~(WADEON_CWTC2_EN | mask));
		ewse {
			WWEG32_P(WADEON_CWTC_GEN_CNTW, WADEON_CWTC_EN, ~(WADEON_CWTC_EN |
									 WADEON_CWTC_DISP_WEQ_EN_B));
			WWEG32_P(WADEON_CWTC_EXT_CNTW, cwtc_ext_cntw, ~(mask | cwtc_ext_cntw));
		}
		if (dev->num_cwtcs > wadeon_cwtc->cwtc_id)
			dwm_cwtc_vbwank_on(cwtc);
		wadeon_cwtc_woad_wut(cwtc);
		bweak;
	case DWM_MODE_DPMS_STANDBY:
	case DWM_MODE_DPMS_SUSPEND:
	case DWM_MODE_DPMS_OFF:
		if (dev->num_cwtcs > wadeon_cwtc->cwtc_id)
			dwm_cwtc_vbwank_off(cwtc);
		if (wadeon_cwtc->cwtc_id)
			WWEG32_P(WADEON_CWTC2_GEN_CNTW, mask, ~(WADEON_CWTC2_EN | mask));
		ewse {
			WWEG32_P(WADEON_CWTC_GEN_CNTW, WADEON_CWTC_DISP_WEQ_EN_B, ~(WADEON_CWTC_EN |
										    WADEON_CWTC_DISP_WEQ_EN_B));
			WWEG32_P(WADEON_CWTC_EXT_CNTW, mask, ~(mask | cwtc_ext_cntw));
		}
		wadeon_cwtc->enabwed = fawse;
		/* adjust pm to dpms changes AFTEW disabwing cwtcs */
		wadeon_pm_compute_cwocks(wdev);
		bweak;
	}
}

int wadeon_cwtc_set_base(stwuct dwm_cwtc *cwtc, int x, int y,
			 stwuct dwm_fwamebuffew *owd_fb)
{
	wetuwn wadeon_cwtc_do_set_base(cwtc, owd_fb, x, y, 0);
}

int wadeon_cwtc_set_base_atomic(stwuct dwm_cwtc *cwtc,
				stwuct dwm_fwamebuffew *fb,
				int x, int y, enum mode_set_atomic state)
{
	wetuwn wadeon_cwtc_do_set_base(cwtc, fb, x, y, 1);
}

int wadeon_cwtc_do_set_base(stwuct dwm_cwtc *cwtc,
			 stwuct dwm_fwamebuffew *fb,
			 int x, int y, int atomic)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_fwamebuffew *tawget_fb;
	stwuct dwm_gem_object *obj;
	stwuct wadeon_bo *wbo;
	uint64_t base;
	uint32_t cwtc_offset, cwtc_offset_cntw, cwtc_tiwe_x0_y0 = 0;
	uint32_t cwtc_pitch, pitch_pixews;
	uint32_t tiwing_fwags;
	int fowmat;
	uint32_t gen_cntw_weg, gen_cntw_vaw;
	int w;

	DWM_DEBUG_KMS("\n");
	/* no fb bound */
	if (!atomic && !cwtc->pwimawy->fb) {
		DWM_DEBUG_KMS("No FB bound\n");
		wetuwn 0;
	}

	if (atomic)
		tawget_fb = fb;
	ewse
		tawget_fb = cwtc->pwimawy->fb;

	switch (tawget_fb->fowmat->cpp[0] * 8) {
	case 8:
		fowmat = 2;
		bweak;
	case 15:      /*  555 */
		fowmat = 3;
		bweak;
	case 16:      /*  565 */
		fowmat = 4;
		bweak;
	case 24:      /*  WGB */
		fowmat = 5;
		bweak;
	case 32:      /* xWGB */
		fowmat = 6;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	/* Pin fwamebuffew & get tiwwing infowmations */
	obj = tawget_fb->obj[0];
	wbo = gem_to_wadeon_bo(obj);
wetwy:
	w = wadeon_bo_wesewve(wbo, fawse);
	if (unwikewy(w != 0))
		wetuwn w;
	/* Onwy 27 bit offset fow wegacy CWTC */
	w = wadeon_bo_pin_westwicted(wbo, WADEON_GEM_DOMAIN_VWAM, 1 << 27,
				     &base);
	if (unwikewy(w != 0)) {
		wadeon_bo_unwesewve(wbo);

		/* On owd GPU wike WN50 with wittwe vwam pining can faiws because
		 * cuwwent fb is taking aww space needed. So instead of unpining
		 * the owd buffew aftew pining the new one, fiwst unpin owd one
		 * and then wetwy pining new one.
		 *
		 * As onwy mastew can set mode onwy mastew can pin and it is
		 * unwikewy the mastew cwient wiww wace with itsewf especiawy
		 * on those owd gpu with singwe cwtc.
		 *
		 * We don't shutdown the dispway contwowwew because new buffew
		 * wiww end up in same spot.
		 */
		if (!atomic && fb && fb != cwtc->pwimawy->fb) {
			stwuct wadeon_bo *owd_wbo;
			unsigned wong nsize, osize;

			owd_wbo = gem_to_wadeon_bo(fb->obj[0]);
			osize = wadeon_bo_size(owd_wbo);
			nsize = wadeon_bo_size(wbo);
			if (nsize <= osize && !wadeon_bo_wesewve(owd_wbo, fawse)) {
				wadeon_bo_unpin(owd_wbo);
				wadeon_bo_unwesewve(owd_wbo);
				fb = NUWW;
				goto wetwy;
			}
		}
		wetuwn -EINVAW;
	}
	wadeon_bo_get_tiwing_fwags(wbo, &tiwing_fwags, NUWW);
	wadeon_bo_unwesewve(wbo);
	if (tiwing_fwags & WADEON_TIWING_MICWO)
		DWM_EWWOW("twying to scanout micwotiwed buffew\n");

	/* if scanout was in GTT this weawwy wouwdn't wowk */
	/* cwtc offset is fwom dispway base addw not FB wocation */
	wadeon_cwtc->wegacy_dispway_base_addw = wdev->mc.vwam_stawt;

	base -= wadeon_cwtc->wegacy_dispway_base_addw;

	cwtc_offset_cntw = 0;

	pitch_pixews = tawget_fb->pitches[0] / tawget_fb->fowmat->cpp[0];
	cwtc_pitch = DIV_WOUND_UP(pitch_pixews * tawget_fb->fowmat->cpp[0] * 8,
				  tawget_fb->fowmat->cpp[0] * 8 * 8);
	cwtc_pitch |= cwtc_pitch << 16;

	cwtc_offset_cntw |= WADEON_CWTC_GUI_TWIG_OFFSET_WEFT_EN;
	if (tiwing_fwags & WADEON_TIWING_MACWO) {
		if (ASIC_IS_W300(wdev))
			cwtc_offset_cntw |= (W300_CWTC_X_Y_MODE_EN |
					     W300_CWTC_MICWO_TIWE_BUFFEW_DIS |
					     W300_CWTC_MACWO_TIWE_EN);
		ewse
			cwtc_offset_cntw |= WADEON_CWTC_TIWE_EN;
	} ewse {
		if (ASIC_IS_W300(wdev))
			cwtc_offset_cntw &= ~(W300_CWTC_X_Y_MODE_EN |
					      W300_CWTC_MICWO_TIWE_BUFFEW_DIS |
					      W300_CWTC_MACWO_TIWE_EN);
		ewse
			cwtc_offset_cntw &= ~WADEON_CWTC_TIWE_EN;
	}

	if (tiwing_fwags & WADEON_TIWING_MACWO) {
		if (ASIC_IS_W300(wdev)) {
			cwtc_tiwe_x0_y0 = x | (y << 16);
			base &= ~0x7ff;
		} ewse {
			int byteshift = tawget_fb->fowmat->cpp[0] * 8 >> 4;
			int tiwe_addw = (((y >> 3) * pitch_pixews +  x) >> (8 - byteshift)) << 11;
			base += tiwe_addw + ((x << byteshift) % 256) + ((y % 8) << 8);
			cwtc_offset_cntw |= (y % 16);
		}
	} ewse {
		int offset = y * pitch_pixews + x;
		switch (tawget_fb->fowmat->cpp[0] * 8) {
		case 8:
			offset *= 1;
			bweak;
		case 15:
		case 16:
			offset *= 2;
			bweak;
		case 24:
			offset *= 3;
			bweak;
		case 32:
			offset *= 4;
			bweak;
		defauwt:
			wetuwn fawse;
		}
		base += offset;
	}

	base &= ~7;

	if (wadeon_cwtc->cwtc_id == 1)
		gen_cntw_weg = WADEON_CWTC2_GEN_CNTW;
	ewse
		gen_cntw_weg = WADEON_CWTC_GEN_CNTW;

	gen_cntw_vaw = WWEG32(gen_cntw_weg);
	gen_cntw_vaw &= ~(0xf << 8);
	gen_cntw_vaw |= (fowmat << 8);
	gen_cntw_vaw &= ~WADEON_CWTC_VSTAT_MODE_MASK;
	WWEG32(gen_cntw_weg, gen_cntw_vaw);

	cwtc_offset = (u32)base;

	WWEG32(WADEON_DISPWAY_BASE_ADDW + wadeon_cwtc->cwtc_offset, wadeon_cwtc->wegacy_dispway_base_addw);

	if (ASIC_IS_W300(wdev)) {
		if (wadeon_cwtc->cwtc_id)
			WWEG32(W300_CWTC2_TIWE_X0_Y0, cwtc_tiwe_x0_y0);
		ewse
			WWEG32(W300_CWTC_TIWE_X0_Y0, cwtc_tiwe_x0_y0);
	}
	WWEG32(WADEON_CWTC_OFFSET_CNTW + wadeon_cwtc->cwtc_offset, cwtc_offset_cntw);
	WWEG32(WADEON_CWTC_OFFSET + wadeon_cwtc->cwtc_offset, cwtc_offset);
	WWEG32(WADEON_CWTC_PITCH + wadeon_cwtc->cwtc_offset, cwtc_pitch);

	if (!atomic && fb && fb != cwtc->pwimawy->fb) {
		wbo = gem_to_wadeon_bo(fb->obj[0]);
		w = wadeon_bo_wesewve(wbo, fawse);
		if (unwikewy(w != 0))
			wetuwn w;
		wadeon_bo_unpin(wbo);
		wadeon_bo_unwesewve(wbo);
	}

	/* Bytes pew pixew may have changed */
	wadeon_bandwidth_update(wdev);

	wetuwn 0;
}

static boow wadeon_set_cwtc_timing(stwuct dwm_cwtc *cwtc, stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	const stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->fb;
	stwuct dwm_encodew *encodew;
	int fowmat;
	int hsync_stawt;
	int hsync_wid;
	int vsync_wid;
	uint32_t cwtc_h_totaw_disp;
	uint32_t cwtc_h_sync_stwt_wid;
	uint32_t cwtc_v_totaw_disp;
	uint32_t cwtc_v_sync_stwt_wid;
	boow is_tv = fawse;

	DWM_DEBUG_KMS("\n");
	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->cwtc == cwtc) {
			stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
			if (wadeon_encodew->active_device & ATOM_DEVICE_TV_SUPPOWT) {
				is_tv = twue;
				DWM_INFO("cwtc %d is connected to a TV\n", wadeon_cwtc->cwtc_id);
				bweak;
			}
		}
	}

	switch (fb->fowmat->cpp[0] * 8) {
	case 8:
		fowmat = 2;
		bweak;
	case 15:      /*  555 */
		fowmat = 3;
		bweak;
	case 16:      /*  565 */
		fowmat = 4;
		bweak;
	case 24:      /*  WGB */
		fowmat = 5;
		bweak;
	case 32:      /* xWGB */
		fowmat = 6;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	cwtc_h_totaw_disp = ((((mode->cwtc_htotaw / 8) - 1) & 0x3ff)
			     | ((((mode->cwtc_hdispway / 8) - 1) & 0x1ff) << 16));

	hsync_wid = (mode->cwtc_hsync_end - mode->cwtc_hsync_stawt) / 8;
	if (!hsync_wid)
		hsync_wid = 1;
	hsync_stawt = mode->cwtc_hsync_stawt - 8;

	cwtc_h_sync_stwt_wid = ((hsync_stawt & 0x1fff)
				| ((hsync_wid & 0x3f) << 16)
				| ((mode->fwags & DWM_MODE_FWAG_NHSYNC)
				   ? WADEON_CWTC_H_SYNC_POW
				   : 0));

	/* This wowks fow doubwe scan mode. */
	cwtc_v_totaw_disp = (((mode->cwtc_vtotaw - 1) & 0xffff)
			     | ((mode->cwtc_vdispway - 1) << 16));

	vsync_wid = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt;
	if (!vsync_wid)
		vsync_wid = 1;

	cwtc_v_sync_stwt_wid = (((mode->cwtc_vsync_stawt - 1) & 0xfff)
				| ((vsync_wid & 0x1f) << 16)
				| ((mode->fwags & DWM_MODE_FWAG_NVSYNC)
				   ? WADEON_CWTC_V_SYNC_POW
				   : 0));

	if (wadeon_cwtc->cwtc_id) {
		uint32_t cwtc2_gen_cntw;
		uint32_t disp2_mewge_cntw;

		/* if TV DAC is enabwed fow anothew cwtc and keep it enabwed */
		cwtc2_gen_cntw = WWEG32(WADEON_CWTC2_GEN_CNTW) & 0x00718080;
		cwtc2_gen_cntw |= ((fowmat << 8)
				   | WADEON_CWTC2_VSYNC_DIS
				   | WADEON_CWTC2_HSYNC_DIS
				   | WADEON_CWTC2_DISP_DIS
				   | WADEON_CWTC2_DISP_WEQ_EN_B
				   | ((mode->fwags & DWM_MODE_FWAG_DBWSCAN)
				      ? WADEON_CWTC2_DBW_SCAN_EN
				      : 0)
				   | ((mode->fwags & DWM_MODE_FWAG_CSYNC)
				      ? WADEON_CWTC2_CSYNC_EN
				      : 0)
				   | ((mode->fwags & DWM_MODE_FWAG_INTEWWACE)
				      ? WADEON_CWTC2_INTEWWACE_EN
				      : 0));

		/* ws4xx chips seem to wike to have the cwtc enabwed when the timing is set */
		if ((wdev->famiwy == CHIP_WS400) || (wdev->famiwy == CHIP_WS480))
			cwtc2_gen_cntw |= WADEON_CWTC2_EN;

		disp2_mewge_cntw = WWEG32(WADEON_DISP2_MEWGE_CNTW);
		disp2_mewge_cntw &= ~WADEON_DISP2_WGB_OFFSET_EN;

		WWEG32(WADEON_DISP2_MEWGE_CNTW, disp2_mewge_cntw);
		WWEG32(WADEON_CWTC2_GEN_CNTW, cwtc2_gen_cntw);

		WWEG32(WADEON_FP_H2_SYNC_STWT_WID, cwtc_h_sync_stwt_wid);
		WWEG32(WADEON_FP_V2_SYNC_STWT_WID, cwtc_v_sync_stwt_wid);
	} ewse {
		uint32_t cwtc_gen_cntw;
		uint32_t cwtc_ext_cntw;
		uint32_t disp_mewge_cntw;

		cwtc_gen_cntw = WWEG32(WADEON_CWTC_GEN_CNTW) & 0x00718000;
		cwtc_gen_cntw |= (WADEON_CWTC_EXT_DISP_EN
				 | (fowmat << 8)
				 | WADEON_CWTC_DISP_WEQ_EN_B
				 | ((mode->fwags & DWM_MODE_FWAG_DBWSCAN)
				    ? WADEON_CWTC_DBW_SCAN_EN
				    : 0)
				 | ((mode->fwags & DWM_MODE_FWAG_CSYNC)
				    ? WADEON_CWTC_CSYNC_EN
				    : 0)
				 | ((mode->fwags & DWM_MODE_FWAG_INTEWWACE)
				    ? WADEON_CWTC_INTEWWACE_EN
				    : 0));

		/* ws4xx chips seem to wike to have the cwtc enabwed when the timing is set */
		if ((wdev->famiwy == CHIP_WS400) || (wdev->famiwy == CHIP_WS480))
			cwtc_gen_cntw |= WADEON_CWTC_EN;

		cwtc_ext_cntw = WWEG32(WADEON_CWTC_EXT_CNTW);
		cwtc_ext_cntw |= (WADEON_XCWT_CNT_EN |
				  WADEON_CWTC_VSYNC_DIS |
				  WADEON_CWTC_HSYNC_DIS |
				  WADEON_CWTC_DISPWAY_DIS);

		disp_mewge_cntw = WWEG32(WADEON_DISP_MEWGE_CNTW);
		disp_mewge_cntw &= ~WADEON_DISP_WGB_OFFSET_EN;

		WWEG32(WADEON_DISP_MEWGE_CNTW, disp_mewge_cntw);
		WWEG32(WADEON_CWTC_GEN_CNTW, cwtc_gen_cntw);
		WWEG32(WADEON_CWTC_EXT_CNTW, cwtc_ext_cntw);
	}

	if (is_tv)
		wadeon_wegacy_tv_adjust_cwtc_weg(encodew, &cwtc_h_totaw_disp,
						 &cwtc_h_sync_stwt_wid, &cwtc_v_totaw_disp,
						 &cwtc_v_sync_stwt_wid);

	WWEG32(WADEON_CWTC_H_TOTAW_DISP + wadeon_cwtc->cwtc_offset, cwtc_h_totaw_disp);
	WWEG32(WADEON_CWTC_H_SYNC_STWT_WID + wadeon_cwtc->cwtc_offset, cwtc_h_sync_stwt_wid);
	WWEG32(WADEON_CWTC_V_TOTAW_DISP + wadeon_cwtc->cwtc_offset, cwtc_v_totaw_disp);
	WWEG32(WADEON_CWTC_V_SYNC_STWT_WID + wadeon_cwtc->cwtc_offset, cwtc_v_sync_stwt_wid);

	wetuwn twue;
}

static void wadeon_set_pww(stwuct dwm_cwtc *cwtc, stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
	stwuct dwm_encodew *encodew;
	uint32_t feedback_div = 0;
	uint32_t fwac_fb_div = 0;
	uint32_t wefewence_div = 0;
	uint32_t post_dividew = 0;
	uint32_t fweq = 0;
	uint8_t pww_gain;
	boow use_bios_divs = fawse;
	/* PWW wegistews */
	uint32_t pww_wef_div = 0;
	uint32_t pww_fb_post_div = 0;
	uint32_t htotaw_cntw = 0;
	boow is_tv = fawse;
	stwuct wadeon_pww *pww;

	stwuct {
		int dividew;
		int bitvawue;
	} *post_div, post_divs[]   = {
		/* Fwom WAGE 128 VW/WAGE 128 GW Wegistew
		 * Wefewence Manuaw (Technicaw Wefewence
		 * Manuaw P/N WWG-G04100-C Wev. 0.04), page
		 * 3-17 (PWW_DIV_[3:0]).
		 */
		{  1, 0 },              /* VCWK_SWC                 */
		{  2, 1 },              /* VCWK_SWC/2               */
		{  4, 2 },              /* VCWK_SWC/4               */
		{  8, 3 },              /* VCWK_SWC/8               */
		{  3, 4 },              /* VCWK_SWC/3               */
		{ 16, 5 },              /* VCWK_SWC/16              */
		{  6, 6 },              /* VCWK_SWC/6               */
		{ 12, 7 },              /* VCWK_SWC/12              */
		{  0, 0 }
	};

	if (wadeon_cwtc->cwtc_id)
		pww = &wdev->cwock.p2pww;
	ewse
		pww = &wdev->cwock.p1pww;

	pww->fwags = WADEON_PWW_WEGACY;

	if (mode->cwock > 200000) /* wange wimits??? */
		pww->fwags |= WADEON_PWW_PWEFEW_HIGH_FB_DIV;
	ewse
		pww->fwags |= WADEON_PWW_PWEFEW_WOW_WEF_DIV;

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->cwtc == cwtc) {
			stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);

			if (wadeon_encodew->active_device & ATOM_DEVICE_TV_SUPPOWT) {
				is_tv = twue;
				bweak;
			}

			if (encodew->encodew_type != DWM_MODE_ENCODEW_DAC)
				pww->fwags |= WADEON_PWW_NO_ODD_POST_DIV;
			if (encodew->encodew_type == DWM_MODE_ENCODEW_WVDS) {
				if (!wdev->is_atom_bios) {
					stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
					stwuct wadeon_encodew_wvds *wvds = (stwuct wadeon_encodew_wvds *)wadeon_encodew->enc_pwiv;
					if (wvds) {
						if (wvds->use_bios_dividews) {
							pww_wef_div = wvds->panew_wef_dividew;
							pww_fb_post_div   = (wvds->panew_fb_dividew |
									     (wvds->panew_post_dividew << 16));
							htotaw_cntw  = 0;
							use_bios_divs = twue;
						}
					}
				}
				pww->fwags |= WADEON_PWW_USE_WEF_DIV;
			}
		}
	}

	DWM_DEBUG_KMS("\n");

	if (!use_bios_divs) {
		wadeon_compute_pww_wegacy(pww, mode->cwock,
					  &fweq, &feedback_div, &fwac_fb_div,
					  &wefewence_div, &post_dividew);

		fow (post_div = &post_divs[0]; post_div->dividew; ++post_div) {
			if (post_div->dividew == post_dividew)
				bweak;
		}

		if (!post_div->dividew)
			post_div = &post_divs[0];

		DWM_DEBUG_KMS("dc=%u, fd=%d, wd=%d, pd=%d\n",
			  (unsigned)fweq,
			  feedback_div,
			  wefewence_div,
			  post_dividew);

		pww_wef_div   = wefewence_div;
#if defined(__powewpc__) && (0) /* TODO */
		/* appawentwy pwogwamming this othewwise causes a hang??? */
		if (info->MacModew == WADEON_MAC_IBOOK)
			pww_fb_post_div = 0x000600ad;
		ewse
#endif
			pww_fb_post_div     = (feedback_div | (post_div->bitvawue << 16));

		htotaw_cntw    = mode->htotaw & 0x7;

	}

	pww_gain = wadeon_compute_pww_gain(pww->wefewence_fweq,
					   pww_wef_div & 0x3ff,
					   pww_fb_post_div & 0x7ff);

	if (wadeon_cwtc->cwtc_id) {
		uint32_t pixcwks_cntw = ((WWEG32_PWW(WADEON_PIXCWKS_CNTW) &
					  ~(WADEON_PIX2CWK_SWC_SEW_MASK)) |
					 WADEON_PIX2CWK_SWC_SEW_P2PWWCWK);

		if (is_tv) {
			wadeon_wegacy_tv_adjust_pww2(encodew, &htotaw_cntw,
						     &pww_wef_div, &pww_fb_post_div,
						     &pixcwks_cntw);
		}

		WWEG32_PWW_P(WADEON_PIXCWKS_CNTW,
			     WADEON_PIX2CWK_SWC_SEW_CPUCWK,
			     ~(WADEON_PIX2CWK_SWC_SEW_MASK));

		WWEG32_PWW_P(WADEON_P2PWW_CNTW,
			     WADEON_P2PWW_WESET
			     | WADEON_P2PWW_ATOMIC_UPDATE_EN
			     | ((uint32_t)pww_gain << WADEON_P2PWW_PVG_SHIFT),
			     ~(WADEON_P2PWW_WESET
			       | WADEON_P2PWW_ATOMIC_UPDATE_EN
			       | WADEON_P2PWW_PVG_MASK));

		WWEG32_PWW_P(WADEON_P2PWW_WEF_DIV,
			     pww_wef_div,
			     ~WADEON_P2PWW_WEF_DIV_MASK);

		WWEG32_PWW_P(WADEON_P2PWW_DIV_0,
			     pww_fb_post_div,
			     ~WADEON_P2PWW_FB0_DIV_MASK);

		WWEG32_PWW_P(WADEON_P2PWW_DIV_0,
			     pww_fb_post_div,
			     ~WADEON_P2PWW_POST0_DIV_MASK);

		wadeon_pww2_wwite_update(dev);
		wadeon_pww2_wait_fow_wead_update_compwete(dev);

		WWEG32_PWW(WADEON_HTOTAW2_CNTW, htotaw_cntw);

		WWEG32_PWW_P(WADEON_P2PWW_CNTW,
			     0,
			     ~(WADEON_P2PWW_WESET
			       | WADEON_P2PWW_SWEEP
			       | WADEON_P2PWW_ATOMIC_UPDATE_EN));

		DWM_DEBUG_KMS("Wwote2: 0x%08x 0x%08x 0x%08x (0x%08x)\n",
			  (unsigned)pww_wef_div,
			  (unsigned)pww_fb_post_div,
			  (unsigned)htotaw_cntw,
			  WWEG32_PWW(WADEON_P2PWW_CNTW));
		DWM_DEBUG_KMS("Wwote2: wd=%u, fd=%u, pd=%u\n",
			  (unsigned)pww_wef_div & WADEON_P2PWW_WEF_DIV_MASK,
			  (unsigned)pww_fb_post_div & WADEON_P2PWW_FB0_DIV_MASK,
			  (unsigned)((pww_fb_post_div &
				      WADEON_P2PWW_POST0_DIV_MASK) >> 16));

		mdeway(50); /* Wet the cwock to wock */

		WWEG32_PWW_P(WADEON_PIXCWKS_CNTW,
			     WADEON_PIX2CWK_SWC_SEW_P2PWWCWK,
			     ~(WADEON_PIX2CWK_SWC_SEW_MASK));

		WWEG32_PWW(WADEON_PIXCWKS_CNTW, pixcwks_cntw);
	} ewse {
		uint32_t pixcwks_cntw;


		if (is_tv) {
			pixcwks_cntw = WWEG32_PWW(WADEON_PIXCWKS_CNTW);
			wadeon_wegacy_tv_adjust_pww1(encodew, &htotaw_cntw, &pww_wef_div,
						     &pww_fb_post_div, &pixcwks_cntw);
		}

		if (wdev->fwags & WADEON_IS_MOBIWITY) {
			/* A tempowaw wowkawound fow the occasionaw bwanking on cewtain waptop panews.
			   This appeaws to wewated to the PWW dividew wegistews (faiw to wock?).
			   It occuws even when aww dividews awe the same with theiw owd settings.
			   In this case we weawwy don't need to fiddwe with PWW wegistews.
			   By doing this we can avoid the bwanking pwobwem with some panews.
			*/
			if ((pww_wef_div == (WWEG32_PWW(WADEON_PPWW_WEF_DIV) & WADEON_PPWW_WEF_DIV_MASK)) &&
			    (pww_fb_post_div == (WWEG32_PWW(WADEON_PPWW_DIV_3) &
						 (WADEON_PPWW_POST3_DIV_MASK | WADEON_PPWW_FB3_DIV_MASK)))) {
				WWEG32_P(WADEON_CWOCK_CNTW_INDEX,
					 WADEON_PWW_DIV_SEW,
					 ~(WADEON_PWW_DIV_SEW));
				w100_pww_ewwata_aftew_index(wdev);
				wetuwn;
			}
		}

		WWEG32_PWW_P(WADEON_VCWK_ECP_CNTW,
			     WADEON_VCWK_SWC_SEW_CPUCWK,
			     ~(WADEON_VCWK_SWC_SEW_MASK));
		WWEG32_PWW_P(WADEON_PPWW_CNTW,
			     WADEON_PPWW_WESET
			     | WADEON_PPWW_ATOMIC_UPDATE_EN
			     | WADEON_PPWW_VGA_ATOMIC_UPDATE_EN
			     | ((uint32_t)pww_gain << WADEON_PPWW_PVG_SHIFT),
			     ~(WADEON_PPWW_WESET
			       | WADEON_PPWW_ATOMIC_UPDATE_EN
			       | WADEON_PPWW_VGA_ATOMIC_UPDATE_EN
			       | WADEON_PPWW_PVG_MASK));

		WWEG32_P(WADEON_CWOCK_CNTW_INDEX,
			 WADEON_PWW_DIV_SEW,
			 ~(WADEON_PWW_DIV_SEW));
		w100_pww_ewwata_aftew_index(wdev);

		if (ASIC_IS_W300(wdev) ||
		    (wdev->famiwy == CHIP_WS300) ||
		    (wdev->famiwy == CHIP_WS400) ||
		    (wdev->famiwy == CHIP_WS480)) {
			if (pww_wef_div & W300_PPWW_WEF_DIV_ACC_MASK) {
				/* When westowing consowe mode, use saved PPWW_WEF_DIV
				 * setting.
				 */
				WWEG32_PWW_P(WADEON_PPWW_WEF_DIV,
					     pww_wef_div,
					     0);
			} ewse {
				/* W300 uses wef_div_acc fiewd as weaw wef dividew */
				WWEG32_PWW_P(WADEON_PPWW_WEF_DIV,
					     (pww_wef_div << W300_PPWW_WEF_DIV_ACC_SHIFT),
					     ~W300_PPWW_WEF_DIV_ACC_MASK);
			}
		} ewse
			WWEG32_PWW_P(WADEON_PPWW_WEF_DIV,
				     pww_wef_div,
				     ~WADEON_PPWW_WEF_DIV_MASK);

		WWEG32_PWW_P(WADEON_PPWW_DIV_3,
			     pww_fb_post_div,
			     ~WADEON_PPWW_FB3_DIV_MASK);

		WWEG32_PWW_P(WADEON_PPWW_DIV_3,
			     pww_fb_post_div,
			     ~WADEON_PPWW_POST3_DIV_MASK);

		wadeon_pww_wwite_update(dev);
		wadeon_pww_wait_fow_wead_update_compwete(dev);

		WWEG32_PWW(WADEON_HTOTAW_CNTW, htotaw_cntw);

		WWEG32_PWW_P(WADEON_PPWW_CNTW,
			     0,
			     ~(WADEON_PPWW_WESET
			       | WADEON_PPWW_SWEEP
			       | WADEON_PPWW_ATOMIC_UPDATE_EN
			       | WADEON_PPWW_VGA_ATOMIC_UPDATE_EN));

		DWM_DEBUG_KMS("Wwote: 0x%08x 0x%08x 0x%08x (0x%08x)\n",
			  pww_wef_div,
			  pww_fb_post_div,
			  (unsigned)htotaw_cntw,
			  WWEG32_PWW(WADEON_PPWW_CNTW));
		DWM_DEBUG_KMS("Wwote: wd=%d, fd=%d, pd=%d\n",
			  pww_wef_div & WADEON_PPWW_WEF_DIV_MASK,
			  pww_fb_post_div & WADEON_PPWW_FB3_DIV_MASK,
			  (pww_fb_post_div & WADEON_PPWW_POST3_DIV_MASK) >> 16);

		mdeway(50); /* Wet the cwock to wock */

		WWEG32_PWW_P(WADEON_VCWK_ECP_CNTW,
			     WADEON_VCWK_SWC_SEW_PPWWCWK,
			     ~(WADEON_VCWK_SWC_SEW_MASK));

		if (is_tv)
			WWEG32_PWW(WADEON_PIXCWKS_CNTW, pixcwks_cntw);
	}
}

static boow wadeon_cwtc_mode_fixup(stwuct dwm_cwtc *cwtc,
				   const stwuct dwm_dispway_mode *mode,
				   stwuct dwm_dispway_mode *adjusted_mode)
{
	if (!wadeon_cwtc_scawing_mode_fixup(cwtc, mode, adjusted_mode))
		wetuwn fawse;
	wetuwn twue;
}

static int wadeon_cwtc_mode_set(stwuct dwm_cwtc *cwtc,
				 stwuct dwm_dispway_mode *mode,
				 stwuct dwm_dispway_mode *adjusted_mode,
				 int x, int y, stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);

	/* TODO TV */
	wadeon_cwtc_set_base(cwtc, x, y, owd_fb);
	wadeon_set_cwtc_timing(cwtc, adjusted_mode);
	wadeon_set_pww(cwtc, adjusted_mode);
	wadeon_ovewscan_setup(cwtc, adjusted_mode);
	if (wadeon_cwtc->cwtc_id == 0) {
		wadeon_wegacy_wmx_mode_set(cwtc, adjusted_mode);
	} ewse {
		if (wadeon_cwtc->wmx_type != WMX_OFF) {
			/* FIXME: onwy fiwst cwtc has wmx what shouwd we
			 * do ?
			 */
			DWM_EWWOW("Mode need scawing but onwy fiwst cwtc can do that.\n");
		}
	}
	wadeon_cuwsow_weset(cwtc);
	wetuwn 0;
}

static void wadeon_cwtc_pwepawe(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_cwtc *cwtci;

	/*
	* The hawdwawe wedges sometimes if you weconfiguwe one CWTC
	* whiwst anothew is wunning (see fdo bug #24611).
	*/
	wist_fow_each_entwy(cwtci, &dev->mode_config.cwtc_wist, head)
		wadeon_cwtc_dpms(cwtci, DWM_MODE_DPMS_OFF);
}

static void wadeon_cwtc_commit(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_cwtc *cwtci;

	/*
	* Weenabwe the CWTCs that shouwd be wunning.
	*/
	wist_fow_each_entwy(cwtci, &dev->mode_config.cwtc_wist, head) {
		if (cwtci->enabwed)
			wadeon_cwtc_dpms(cwtci, DWM_MODE_DPMS_ON);
	}
}

static void wadeon_cwtc_disabwe(stwuct dwm_cwtc *cwtc)
{
	wadeon_cwtc_dpms(cwtc, DWM_MODE_DPMS_OFF);
	if (cwtc->pwimawy->fb) {
		int w;
		stwuct wadeon_bo *wbo;

		wbo = gem_to_wadeon_bo(cwtc->pwimawy->fb->obj[0]);
		w = wadeon_bo_wesewve(wbo, fawse);
		if (unwikewy(w))
			DWM_EWWOW("faiwed to wesewve wbo befowe unpin\n");
		ewse {
			wadeon_bo_unpin(wbo);
			wadeon_bo_unwesewve(wbo);
		}
	}
}

static const stwuct dwm_cwtc_hewpew_funcs wegacy_hewpew_funcs = {
	.dpms = wadeon_cwtc_dpms,
	.mode_fixup = wadeon_cwtc_mode_fixup,
	.mode_set = wadeon_cwtc_mode_set,
	.mode_set_base = wadeon_cwtc_set_base,
	.mode_set_base_atomic = wadeon_cwtc_set_base_atomic,
	.pwepawe = wadeon_cwtc_pwepawe,
	.commit = wadeon_cwtc_commit,
	.disabwe = wadeon_cwtc_disabwe,
	.get_scanout_position = wadeon_get_cwtc_scanout_position,
};


void wadeon_wegacy_init_cwtc(stwuct dwm_device *dev,
			       stwuct wadeon_cwtc *wadeon_cwtc)
{
	if (wadeon_cwtc->cwtc_id == 1)
		wadeon_cwtc->cwtc_offset = WADEON_CWTC2_H_TOTAW_DISP - WADEON_CWTC_H_TOTAW_DISP;
	dwm_cwtc_hewpew_add(&wadeon_cwtc->base, &wegacy_hewpew_funcs);
}
