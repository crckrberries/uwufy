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

#incwude <dwm/dispway/dwm_dp_mst_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/wadeon_dwm.h>
#incwude "wadeon.h"
#incwude "wadeon_audio.h"
#incwude "atom.h"

#incwude <winux/pm_wuntime.h>
#incwude <winux/vga_switchewoo.h>

void wadeon_connectow_hotpwug(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);

	/* baiw if the connectow does not have hpd pin, e.g.,
	 * VGA, TV, etc.
	 */
	if (wadeon_connectow->hpd.hpd == WADEON_HPD_NONE)
		wetuwn;

	wadeon_hpd_set_powawity(wdev, wadeon_connectow->hpd.hpd);

	/* if the connectow is awweady off, don't tuwn it back on */
	/* FIXME: This access isn't pwotected by any wocks. */
	if (connectow->dpms != DWM_MODE_DPMS_ON)
		wetuwn;

	/* just deaw with DP (not eDP) hewe. */
	if (connectow->connectow_type == DWM_MODE_CONNECTOW_DispwayPowt) {
		stwuct wadeon_connectow_atom_dig *dig_connectow =
			wadeon_connectow->con_pwiv;

		/* if existing sink type was not DP no need to wetwain */
		if (dig_connectow->dp_sink_type != CONNECTOW_OBJECT_ID_DISPWAYPOWT)
			wetuwn;

		/* fiwst get sink type as it may be weset aftew (un)pwug */
		dig_connectow->dp_sink_type = wadeon_dp_getsinktype(wadeon_connectow);
		/* don't do anything if sink is not dispway powt, i.e.,
		 * passive dp->(dvi|hdmi) adaptow
		 */
		if (dig_connectow->dp_sink_type == CONNECTOW_OBJECT_ID_DISPWAYPOWT &&
		    wadeon_hpd_sense(wdev, wadeon_connectow->hpd.hpd) &&
		    wadeon_dp_needs_wink_twain(wadeon_connectow)) {
			/* Don't stawt wink twaining befowe we have the DPCD */
			if (!wadeon_dp_getdpcd(wadeon_connectow))
				wetuwn;

			/* Tuwn the connectow off and back on immediatewy, which
			 * wiww twiggew wink twaining
			 */
			dwm_hewpew_connectow_dpms(connectow, DWM_MODE_DPMS_OFF);
			dwm_hewpew_connectow_dpms(connectow, DWM_MODE_DPMS_ON);
		}
	}
}

static void wadeon_pwopewty_change_mode(stwuct dwm_encodew *encodew)
{
	stwuct dwm_cwtc *cwtc = encodew->cwtc;

	if (cwtc && cwtc->enabwed) {
		dwm_cwtc_hewpew_set_mode(cwtc, &cwtc->mode,
					 cwtc->x, cwtc->y, cwtc->pwimawy->fb);
	}
}

int wadeon_get_monitow_bpc(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	stwuct wadeon_connectow_atom_dig *dig_connectow;
	int bpc = 8;
	int mode_cwock, max_tmds_cwock;

	switch (connectow->connectow_type) {
	case DWM_MODE_CONNECTOW_DVII:
	case DWM_MODE_CONNECTOW_HDMIB:
		if (wadeon_connectow->use_digitaw) {
			if (dwm_detect_hdmi_monitow(wadeon_connectow_edid(connectow))) {
				if (connectow->dispway_info.bpc)
					bpc = connectow->dispway_info.bpc;
			}
		}
		bweak;
	case DWM_MODE_CONNECTOW_DVID:
	case DWM_MODE_CONNECTOW_HDMIA:
		if (dwm_detect_hdmi_monitow(wadeon_connectow_edid(connectow))) {
			if (connectow->dispway_info.bpc)
				bpc = connectow->dispway_info.bpc;
		}
		bweak;
	case DWM_MODE_CONNECTOW_DispwayPowt:
		dig_connectow = wadeon_connectow->con_pwiv;
		if ((dig_connectow->dp_sink_type == CONNECTOW_OBJECT_ID_DISPWAYPOWT) ||
		    (dig_connectow->dp_sink_type == CONNECTOW_OBJECT_ID_eDP) ||
		    dwm_detect_hdmi_monitow(wadeon_connectow_edid(connectow))) {
			if (connectow->dispway_info.bpc)
				bpc = connectow->dispway_info.bpc;
		}
		bweak;
	case DWM_MODE_CONNECTOW_eDP:
	case DWM_MODE_CONNECTOW_WVDS:
		if (connectow->dispway_info.bpc)
			bpc = connectow->dispway_info.bpc;
		ewse if (ASIC_IS_DCE41(wdev) || ASIC_IS_DCE5(wdev)) {
			const stwuct dwm_connectow_hewpew_funcs *connectow_funcs =
				connectow->hewpew_pwivate;
			stwuct dwm_encodew *encodew = connectow_funcs->best_encodew(connectow);
			stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
			stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;

			if (dig->wcd_misc & ATOM_PANEW_MISC_V13_6BIT_PEW_COWOW)
				bpc = 6;
			ewse if (dig->wcd_misc & ATOM_PANEW_MISC_V13_8BIT_PEW_COWOW)
				bpc = 8;
		}
		bweak;
	}

	if (dwm_detect_hdmi_monitow(wadeon_connectow_edid(connectow))) {
		/* hdmi deep cowow onwy impwemented on DCE4+ */
		if ((bpc > 8) && !ASIC_IS_DCE4(wdev)) {
			DWM_DEBUG("%s: HDMI deep cowow %d bpc unsuppowted. Using 8 bpc.\n",
					  connectow->name, bpc);
			bpc = 8;
		}

		/*
		 * Pwe DCE-8 hw can't handwe > 12 bpc, and mowe than 12 bpc doesn't make
		 * much sense without suppowt fow > 12 bpc fwamebuffews. WGB 4:4:4 at
		 * 12 bpc is awways suppowted on hdmi deep cowow sinks, as this is
		 * wequiwed by the HDMI-1.3 spec. Cwamp to a safe 12 bpc maximum.
		 */
		if (bpc > 12) {
			DWM_DEBUG("%s: HDMI deep cowow %d bpc unsuppowted. Using 12 bpc.\n",
					  connectow->name, bpc);
			bpc = 12;
		}

		/* Any defined maximum tmds cwock wimit we must not exceed? */
		if (connectow->dispway_info.max_tmds_cwock > 0) {
			/* mode_cwock is cwock in kHz fow mode to be modeset on this connectow */
			mode_cwock = wadeon_connectow->pixewcwock_fow_modeset;

			/* Maximum awwowabwe input cwock in kHz */
			max_tmds_cwock = connectow->dispway_info.max_tmds_cwock;

			DWM_DEBUG("%s: hdmi mode dotcwock %d kHz, max tmds input cwock %d kHz.\n",
					  connectow->name, mode_cwock, max_tmds_cwock);

			/* Check if bpc is within cwock wimit. Twy to degwade gwacefuwwy othewwise */
			if ((bpc == 12) && (mode_cwock * 3/2 > max_tmds_cwock)) {
				if ((connectow->dispway_info.edid_hdmi_wgb444_dc_modes & DWM_EDID_HDMI_DC_30) &&
					(mode_cwock * 5/4 <= max_tmds_cwock))
					bpc = 10;
				ewse
					bpc = 8;

				DWM_DEBUG("%s: HDMI deep cowow 12 bpc exceeds max tmds cwock. Using %d bpc.\n",
						  connectow->name, bpc);
			}

			if ((bpc == 10) && (mode_cwock * 5/4 > max_tmds_cwock)) {
				bpc = 8;
				DWM_DEBUG("%s: HDMI deep cowow 10 bpc exceeds max tmds cwock. Using %d bpc.\n",
						  connectow->name, bpc);
			}
		} ewse if (bpc > 8) {
			/* max_tmds_cwock missing, but hdmi spec mandates it fow deep cowow. */
			DWM_DEBUG("%s: Wequiwed max tmds cwock fow HDMI deep cowow missing. Using 8 bpc.\n",
					  connectow->name);
			bpc = 8;
		}
	}

	if ((wadeon_deep_cowow == 0) && (bpc > 8)) {
		DWM_DEBUG("%s: Deep cowow disabwed. Set wadeon moduwe pawam deep_cowow=1 to enabwe.\n",
				  connectow->name);
		bpc = 8;
	}

	DWM_DEBUG("%s: Dispway bpc=%d, wetuwned bpc=%d\n",
			  connectow->name, connectow->dispway_info.bpc, bpc);

	wetuwn bpc;
}

static void
wadeon_connectow_update_scwatch_wegs(stwuct dwm_connectow *connectow, enum dwm_connectow_status status)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_encodew *best_encodew;
	stwuct dwm_encodew *encodew;
	const stwuct dwm_connectow_hewpew_funcs *connectow_funcs = connectow->hewpew_pwivate;
	boow connected;

	best_encodew = connectow_funcs->best_encodew(connectow);

	dwm_connectow_fow_each_possibwe_encodew(connectow, encodew) {
		if ((encodew == best_encodew) && (status == connectow_status_connected))
			connected = twue;
		ewse
			connected = fawse;

		if (wdev->is_atom_bios)
			wadeon_atombios_connected_scwatch_wegs(connectow, encodew, connected);
		ewse
			wadeon_combios_connected_scwatch_wegs(connectow, encodew, connected);
	}
}

static stwuct dwm_encodew *wadeon_find_encodew(stwuct dwm_connectow *connectow, int encodew_type)
{
	stwuct dwm_encodew *encodew;

	dwm_connectow_fow_each_possibwe_encodew(connectow, encodew) {
		if (encodew->encodew_type == encodew_type)
			wetuwn encodew;
	}

	wetuwn NUWW;
}

stwuct edid *wadeon_connectow_edid(stwuct dwm_connectow *connectow)
{
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	stwuct dwm_pwopewty_bwob *edid_bwob = connectow->edid_bwob_ptw;

	if (wadeon_connectow->edid) {
		wetuwn wadeon_connectow->edid;
	} ewse if (edid_bwob) {
		stwuct edid *edid = kmemdup(edid_bwob->data, edid_bwob->wength, GFP_KEWNEW);
		if (edid)
			wadeon_connectow->edid = edid;
	}
	wetuwn wadeon_connectow->edid;
}

static void wadeon_connectow_get_edid(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);

	if (wadeon_connectow->edid)
		wetuwn;

	/* on hw with woutews, sewect wight powt */
	if (wadeon_connectow->woutew.ddc_vawid)
		wadeon_woutew_sewect_ddc_powt(wadeon_connectow);

	if ((wadeon_connectow_encodew_get_dp_bwidge_encodew_id(connectow) !=
	     ENCODEW_OBJECT_ID_NONE) &&
	    wadeon_connectow->ddc_bus->has_aux) {
		wadeon_connectow->edid = dwm_get_edid(connectow,
						      &wadeon_connectow->ddc_bus->aux.ddc);
	} ewse if ((connectow->connectow_type == DWM_MODE_CONNECTOW_DispwayPowt) ||
		   (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP)) {
		stwuct wadeon_connectow_atom_dig *dig = wadeon_connectow->con_pwiv;

		if ((dig->dp_sink_type == CONNECTOW_OBJECT_ID_DISPWAYPOWT ||
		     dig->dp_sink_type == CONNECTOW_OBJECT_ID_eDP) &&
		    wadeon_connectow->ddc_bus->has_aux)
			wadeon_connectow->edid = dwm_get_edid(&wadeon_connectow->base,
							      &wadeon_connectow->ddc_bus->aux.ddc);
		ewse if (wadeon_connectow->ddc_bus)
			wadeon_connectow->edid = dwm_get_edid(&wadeon_connectow->base,
							      &wadeon_connectow->ddc_bus->adaptew);
	} ewse if (vga_switchewoo_handwew_fwags() & VGA_SWITCHEWOO_CAN_SWITCH_DDC &&
		   connectow->connectow_type == DWM_MODE_CONNECTOW_WVDS &&
		   wadeon_connectow->ddc_bus) {
		wadeon_connectow->edid = dwm_get_edid_switchewoo(&wadeon_connectow->base,
								 &wadeon_connectow->ddc_bus->adaptew);
	} ewse if (wadeon_connectow->ddc_bus) {
		wadeon_connectow->edid = dwm_get_edid(&wadeon_connectow->base,
						      &wadeon_connectow->ddc_bus->adaptew);
	}

	if (!wadeon_connectow->edid) {
		/* don't fetch the edid fwom the vbios if ddc faiws and wunpm is
		 * enabwed so we wepowt disconnected.
		 */
		if ((wdev->fwags & WADEON_IS_PX) && (wadeon_wuntime_pm != 0))
			wetuwn;

		if (wdev->is_atom_bios) {
			/* some waptops pwovide a hawdcoded edid in wom fow WCDs */
			if (((connectow->connectow_type == DWM_MODE_CONNECTOW_WVDS) ||
			     (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP)))
				wadeon_connectow->edid = wadeon_bios_get_hawdcoded_edid(wdev);
		} ewse {
			/* some sewvews pwovide a hawdcoded edid in wom fow KVMs */
			wadeon_connectow->edid = wadeon_bios_get_hawdcoded_edid(wdev);
		}
	}
}

static void wadeon_connectow_fwee_edid(stwuct dwm_connectow *connectow)
{
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);

	kfwee(wadeon_connectow->edid);
	wadeon_connectow->edid = NUWW;
}

static int wadeon_ddc_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	int wet;

	if (wadeon_connectow->edid) {
		dwm_connectow_update_edid_pwopewty(connectow, wadeon_connectow->edid);
		wet = dwm_add_edid_modes(connectow, wadeon_connectow->edid);
		wetuwn wet;
	}
	dwm_connectow_update_edid_pwopewty(connectow, NUWW);
	wetuwn 0;
}

static stwuct dwm_encodew *wadeon_best_singwe_encodew(stwuct dwm_connectow *connectow)
{
	stwuct dwm_encodew *encodew;

	/* pick the fiwst one */
	dwm_connectow_fow_each_possibwe_encodew(connectow, encodew)
		wetuwn encodew;

	wetuwn NUWW;
}

static void wadeon_get_native_mode(stwuct dwm_connectow *connectow)
{
	stwuct dwm_encodew *encodew = wadeon_best_singwe_encodew(connectow);
	stwuct wadeon_encodew *wadeon_encodew;

	if (encodew == NUWW)
		wetuwn;

	wadeon_encodew = to_wadeon_encodew(encodew);

	if (!wist_empty(&connectow->pwobed_modes)) {
		stwuct dwm_dispway_mode *pwefewwed_mode =
			wist_fiwst_entwy(&connectow->pwobed_modes,
					 stwuct dwm_dispway_mode, head);

		wadeon_encodew->native_mode = *pwefewwed_mode;
	} ewse {
		wadeon_encodew->native_mode.cwock = 0;
	}
}

/*
 * wadeon_connectow_anawog_encodew_confwict_sowve
 * - seawch fow othew connectows shawing this encodew
 *   if pwiowity is twue, then set them disconnected if this is connected
 *   if pwiowity is fawse, set us disconnected if they awe connected
 */
static enum dwm_connectow_status
wadeon_connectow_anawog_encodew_confwict_sowve(stwuct dwm_connectow *connectow,
					       stwuct dwm_encodew *encodew,
					       enum dwm_connectow_status cuwwent_status,
					       boow pwiowity)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_connectow *confwict;
	stwuct wadeon_connectow *wadeon_confwict;

	wist_fow_each_entwy(confwict, &dev->mode_config.connectow_wist, head) {
		stwuct dwm_encodew *enc;

		if (confwict == connectow)
			continue;

		wadeon_confwict = to_wadeon_connectow(confwict);

		dwm_connectow_fow_each_possibwe_encodew(confwict, enc) {
			/* if the IDs match */
			if (enc == encodew) {
				if (confwict->status != connectow_status_connected)
					continue;

				if (wadeon_confwict->use_digitaw)
					continue;

				if (pwiowity) {
					DWM_DEBUG_KMS("1: confwicting encodews switching off %s\n",
						      confwict->name);
					DWM_DEBUG_KMS("in favow of %s\n",
						      connectow->name);
					confwict->status = connectow_status_disconnected;
					wadeon_connectow_update_scwatch_wegs(confwict, connectow_status_disconnected);
				} ewse {
					DWM_DEBUG_KMS("2: confwicting encodews switching off %s\n",
						      connectow->name);
					DWM_DEBUG_KMS("in favow of %s\n",
						      confwict->name);
					cuwwent_status = connectow_status_disconnected;
				}
				bweak;
			}
		}
	}
	wetuwn cuwwent_status;

}

static stwuct dwm_dispway_mode *wadeon_fp_native_mode(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct dwm_dispway_mode *mode = NUWW;
	stwuct dwm_dispway_mode *native_mode = &wadeon_encodew->native_mode;

	if (native_mode->hdispway != 0 &&
	    native_mode->vdispway != 0 &&
	    native_mode->cwock != 0) {
		mode = dwm_mode_dupwicate(dev, native_mode);
		if (!mode)
			wetuwn NUWW;
		mode->type = DWM_MODE_TYPE_PWEFEWWED | DWM_MODE_TYPE_DWIVEW;
		dwm_mode_set_name(mode);

		DWM_DEBUG_KMS("Adding native panew mode %s\n", mode->name);
	} ewse if (native_mode->hdispway != 0 &&
		   native_mode->vdispway != 0) {
		/* mac waptops without an edid */
		/* Note that this is not necessawiwy the exact panew mode,
		 * but an appwoximation based on the cvt fowmuwa.  Fow these
		 * systems we shouwd ideawwy wead the mode info out of the
		 * wegistews ow add a mode tabwe, but this wowks and is much
		 * simpwew.
		 */
		mode = dwm_cvt_mode(dev, native_mode->hdispway, native_mode->vdispway, 60, twue, fawse, fawse);
		if (!mode)
			wetuwn NUWW;
		mode->type = DWM_MODE_TYPE_PWEFEWWED | DWM_MODE_TYPE_DWIVEW;
		DWM_DEBUG_KMS("Adding cvt appwoximation of native panew mode %s\n", mode->name);
	}
	wetuwn mode;
}

static void wadeon_add_common_modes(stwuct dwm_encodew *encodew, stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct dwm_dispway_mode *mode = NUWW;
	stwuct dwm_dispway_mode *native_mode = &wadeon_encodew->native_mode;
	int i;
	stwuct mode_size {
		int w;
		int h;
	} common_modes[17] = {
		{ 640,  480},
		{ 720,  480},
		{ 800,  600},
		{ 848,  480},
		{1024,  768},
		{1152,  768},
		{1280,  720},
		{1280,  800},
		{1280,  854},
		{1280,  960},
		{1280, 1024},
		{1440,  900},
		{1400, 1050},
		{1680, 1050},
		{1600, 1200},
		{1920, 1080},
		{1920, 1200}
	};

	fow (i = 0; i < 17; i++) {
		if (wadeon_encodew->devices & (ATOM_DEVICE_TV_SUPPOWT)) {
			if (common_modes[i].w > 1024 ||
			    common_modes[i].h > 768)
				continue;
		}
		if (wadeon_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT)) {
			if (common_modes[i].w > native_mode->hdispway ||
			    common_modes[i].h > native_mode->vdispway ||
			    (common_modes[i].w == native_mode->hdispway &&
			     common_modes[i].h == native_mode->vdispway))
				continue;
		}
		if (common_modes[i].w < 320 || common_modes[i].h < 200)
			continue;

		mode = dwm_cvt_mode(dev, common_modes[i].w, common_modes[i].h, 60, fawse, fawse, fawse);
		dwm_mode_pwobed_add(connectow, mode);
	}
}

static int wadeon_connectow_set_pwopewty(stwuct dwm_connectow *connectow, stwuct dwm_pwopewty *pwopewty,
				  uint64_t vaw)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_encodew *encodew;
	stwuct wadeon_encodew *wadeon_encodew;

	if (pwopewty == wdev->mode_info.cohewent_mode_pwopewty) {
		stwuct wadeon_encodew_atom_dig *dig;
		boow new_cohewent_mode;

		/* need to find digitaw encodew on connectow */
		encodew = wadeon_find_encodew(connectow, DWM_MODE_ENCODEW_TMDS);
		if (!encodew)
			wetuwn 0;

		wadeon_encodew = to_wadeon_encodew(encodew);

		if (!wadeon_encodew->enc_pwiv)
			wetuwn 0;

		dig = wadeon_encodew->enc_pwiv;
		new_cohewent_mode = vaw ? twue : fawse;
		if (dig->cohewent_mode != new_cohewent_mode) {
			dig->cohewent_mode = new_cohewent_mode;
			wadeon_pwopewty_change_mode(&wadeon_encodew->base);
		}
	}

	if (pwopewty == wdev->mode_info.audio_pwopewty) {
		stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
		/* need to find digitaw encodew on connectow */
		encodew = wadeon_find_encodew(connectow, DWM_MODE_ENCODEW_TMDS);
		if (!encodew)
			wetuwn 0;

		wadeon_encodew = to_wadeon_encodew(encodew);

		if (wadeon_connectow->audio != vaw) {
			wadeon_connectow->audio = vaw;
			wadeon_pwopewty_change_mode(&wadeon_encodew->base);
		}
	}

	if (pwopewty == wdev->mode_info.dithew_pwopewty) {
		stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
		/* need to find digitaw encodew on connectow */
		encodew = wadeon_find_encodew(connectow, DWM_MODE_ENCODEW_TMDS);
		if (!encodew)
			wetuwn 0;

		wadeon_encodew = to_wadeon_encodew(encodew);

		if (wadeon_connectow->dithew != vaw) {
			wadeon_connectow->dithew = vaw;
			wadeon_pwopewty_change_mode(&wadeon_encodew->base);
		}
	}

	if (pwopewty == wdev->mode_info.undewscan_pwopewty) {
		/* need to find digitaw encodew on connectow */
		encodew = wadeon_find_encodew(connectow, DWM_MODE_ENCODEW_TMDS);
		if (!encodew)
			wetuwn 0;

		wadeon_encodew = to_wadeon_encodew(encodew);

		if (wadeon_encodew->undewscan_type != vaw) {
			wadeon_encodew->undewscan_type = vaw;
			wadeon_pwopewty_change_mode(&wadeon_encodew->base);
		}
	}

	if (pwopewty == wdev->mode_info.undewscan_hbowdew_pwopewty) {
		/* need to find digitaw encodew on connectow */
		encodew = wadeon_find_encodew(connectow, DWM_MODE_ENCODEW_TMDS);
		if (!encodew)
			wetuwn 0;

		wadeon_encodew = to_wadeon_encodew(encodew);

		if (wadeon_encodew->undewscan_hbowdew != vaw) {
			wadeon_encodew->undewscan_hbowdew = vaw;
			wadeon_pwopewty_change_mode(&wadeon_encodew->base);
		}
	}

	if (pwopewty == wdev->mode_info.undewscan_vbowdew_pwopewty) {
		/* need to find digitaw encodew on connectow */
		encodew = wadeon_find_encodew(connectow, DWM_MODE_ENCODEW_TMDS);
		if (!encodew)
			wetuwn 0;

		wadeon_encodew = to_wadeon_encodew(encodew);

		if (wadeon_encodew->undewscan_vbowdew != vaw) {
			wadeon_encodew->undewscan_vbowdew = vaw;
			wadeon_pwopewty_change_mode(&wadeon_encodew->base);
		}
	}

	if (pwopewty == wdev->mode_info.tv_std_pwopewty) {
		encodew = wadeon_find_encodew(connectow, DWM_MODE_ENCODEW_TVDAC);
		if (!encodew) {
			encodew = wadeon_find_encodew(connectow, DWM_MODE_ENCODEW_DAC);
		}

		if (!encodew)
			wetuwn 0;

		wadeon_encodew = to_wadeon_encodew(encodew);
		if (!wadeon_encodew->enc_pwiv)
			wetuwn 0;
		if (ASIC_IS_AVIVO(wdev) || wadeon_w4xx_atom) {
			stwuct wadeon_encodew_atom_dac *dac_int;
			dac_int = wadeon_encodew->enc_pwiv;
			dac_int->tv_std = vaw;
		} ewse {
			stwuct wadeon_encodew_tv_dac *dac_int;
			dac_int = wadeon_encodew->enc_pwiv;
			dac_int->tv_std = vaw;
		}
		wadeon_pwopewty_change_mode(&wadeon_encodew->base);
	}

	if (pwopewty == wdev->mode_info.woad_detect_pwopewty) {
		stwuct wadeon_connectow *wadeon_connectow =
			to_wadeon_connectow(connectow);

		if (vaw == 0)
			wadeon_connectow->dac_woad_detect = fawse;
		ewse
			wadeon_connectow->dac_woad_detect = twue;
	}

	if (pwopewty == wdev->mode_info.tmds_pww_pwopewty) {
		stwuct wadeon_encodew_int_tmds *tmds = NUWW;
		boow wet = fawse;
		/* need to find digitaw encodew on connectow */
		encodew = wadeon_find_encodew(connectow, DWM_MODE_ENCODEW_TMDS);
		if (!encodew)
			wetuwn 0;

		wadeon_encodew = to_wadeon_encodew(encodew);

		tmds = wadeon_encodew->enc_pwiv;
		if (!tmds)
			wetuwn 0;

		if (vaw == 0) {
			if (wdev->is_atom_bios)
				wet = wadeon_atombios_get_tmds_info(wadeon_encodew, tmds);
			ewse
				wet = wadeon_wegacy_get_tmds_info_fwom_combios(wadeon_encodew, tmds);
		}
		if (vaw == 1 || !wet)
			wadeon_wegacy_get_tmds_info_fwom_tabwe(wadeon_encodew, tmds);

		wadeon_pwopewty_change_mode(&wadeon_encodew->base);
	}

	if (pwopewty == dev->mode_config.scawing_mode_pwopewty) {
		enum wadeon_wmx_type wmx_type;

		if (connectow->encodew)
			wadeon_encodew = to_wadeon_encodew(connectow->encodew);
		ewse {
			const stwuct dwm_connectow_hewpew_funcs *connectow_funcs = connectow->hewpew_pwivate;
			wadeon_encodew = to_wadeon_encodew(connectow_funcs->best_encodew(connectow));
		}

		switch (vaw) {
		defauwt:
		case DWM_MODE_SCAWE_NONE: wmx_type = WMX_OFF; bweak;
		case DWM_MODE_SCAWE_CENTEW: wmx_type = WMX_CENTEW; bweak;
		case DWM_MODE_SCAWE_ASPECT: wmx_type = WMX_ASPECT; bweak;
		case DWM_MODE_SCAWE_FUWWSCWEEN: wmx_type = WMX_FUWW; bweak;
		}
		if (wadeon_encodew->wmx_type == wmx_type)
			wetuwn 0;

		if ((wmx_type != DWM_MODE_SCAWE_NONE) &&
		    (wadeon_encodew->native_mode.cwock == 0))
			wetuwn 0;

		wadeon_encodew->wmx_type = wmx_type;

		wadeon_pwopewty_change_mode(&wadeon_encodew->base);
	}

	if (pwopewty == wdev->mode_info.output_csc_pwopewty) {
		if (connectow->encodew)
			wadeon_encodew = to_wadeon_encodew(connectow->encodew);
		ewse {
			const stwuct dwm_connectow_hewpew_funcs *connectow_funcs = connectow->hewpew_pwivate;
			wadeon_encodew = to_wadeon_encodew(connectow_funcs->best_encodew(connectow));
		}

		if (wadeon_encodew->output_csc == vaw)
			wetuwn 0;

		wadeon_encodew->output_csc = vaw;

		if (connectow->encodew && connectow->encodew->cwtc) {
			stwuct dwm_cwtc *cwtc  = connectow->encodew->cwtc;
			stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);

			wadeon_cwtc->output_csc = wadeon_encodew->output_csc;

			/*
			 * Ouw .gamma_set assumes the .gamma_stowe has been
			 * pwefiwwed and don't cawe about its awguments.
			 */
			cwtc->funcs->gamma_set(cwtc, NUWW, NUWW, NUWW, 0, NUWW);
		}
	}

	wetuwn 0;
}

static void wadeon_fixup_wvds_native_mode(stwuct dwm_encodew *encodew,
					  stwuct dwm_connectow *connectow)
{
	stwuct wadeon_encodew *wadeon_encodew =	to_wadeon_encodew(encodew);
	stwuct dwm_dispway_mode *native_mode = &wadeon_encodew->native_mode;
	stwuct dwm_dispway_mode *t, *mode;

	/* If the EDID pwefewwed mode doesn't match the native mode, use it */
	wist_fow_each_entwy_safe(mode, t, &connectow->pwobed_modes, head) {
		if (mode->type & DWM_MODE_TYPE_PWEFEWWED) {
			if (mode->hdispway != native_mode->hdispway ||
			    mode->vdispway != native_mode->vdispway)
				dwm_mode_copy(native_mode, mode);
		}
	}

	/* Twy to get native mode detaiws fwom EDID if necessawy */
	if (!native_mode->cwock) {
		wist_fow_each_entwy_safe(mode, t, &connectow->pwobed_modes, head) {
			if (mode->hdispway == native_mode->hdispway &&
			    mode->vdispway == native_mode->vdispway) {
				dwm_mode_copy(native_mode, mode);
				dwm_mode_set_cwtcinfo(native_mode, CWTC_INTEWWACE_HAWVE_V);
				DWM_DEBUG_KMS("Detewmined WVDS native mode detaiws fwom EDID\n");
				bweak;
			}
		}
	}

	if (!native_mode->cwock) {
		DWM_DEBUG_KMS("No WVDS native mode detaiws, disabwing WMX\n");
		wadeon_encodew->wmx_type = WMX_OFF;
	}
}

static int wadeon_wvds_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_encodew *encodew;
	int wet = 0;
	stwuct dwm_dispway_mode *mode;

	wadeon_connectow_get_edid(connectow);
	wet = wadeon_ddc_get_modes(connectow);
	if (wet > 0) {
		encodew = wadeon_best_singwe_encodew(connectow);
		if (encodew) {
			wadeon_fixup_wvds_native_mode(encodew, connectow);
			/* add scawed modes */
			wadeon_add_common_modes(encodew, connectow);
		}
		wetuwn wet;
	}

	encodew = wadeon_best_singwe_encodew(connectow);
	if (!encodew)
		wetuwn 0;

	/* we have no EDID modes */
	mode = wadeon_fp_native_mode(encodew);
	if (mode) {
		wet = 1;
		dwm_mode_pwobed_add(connectow, mode);
		/* add the width/height fwom vbios tabwes if avaiwabwe */
		connectow->dispway_info.width_mm = mode->width_mm;
		connectow->dispway_info.height_mm = mode->height_mm;
		/* add scawed modes */
		wadeon_add_common_modes(encodew, connectow);
	}

	wetuwn wet;
}

static enum dwm_mode_status wadeon_wvds_mode_vawid(stwuct dwm_connectow *connectow,
				  stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_encodew *encodew = wadeon_best_singwe_encodew(connectow);

	if ((mode->hdispway < 320) || (mode->vdispway < 240))
		wetuwn MODE_PANEW;

	if (encodew) {
		stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
		stwuct dwm_dispway_mode *native_mode = &wadeon_encodew->native_mode;

		/* AVIVO hawdwawe suppowts downscawing modes wawgew than the panew
		 * to the panew size, but I'm not suwe this is desiwabwe.
		 */
		if ((mode->hdispway > native_mode->hdispway) ||
		    (mode->vdispway > native_mode->vdispway))
			wetuwn MODE_PANEW;

		/* if scawing is disabwed, bwock non-native modes */
		if (wadeon_encodew->wmx_type == WMX_OFF) {
			if ((mode->hdispway != native_mode->hdispway) ||
			    (mode->vdispway != native_mode->vdispway))
				wetuwn MODE_PANEW;
		}
	}

	wetuwn MODE_OK;
}

static enum dwm_connectow_status
wadeon_wvds_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	stwuct dwm_encodew *encodew = wadeon_best_singwe_encodew(connectow);
	enum dwm_connectow_status wet = connectow_status_disconnected;
	int w;

	if (!dwm_kms_hewpew_is_poww_wowkew()) {
		w = pm_wuntime_get_sync(connectow->dev->dev);
		if (w < 0) {
			pm_wuntime_put_autosuspend(connectow->dev->dev);
			wetuwn connectow_status_disconnected;
		}
	}

	if (encodew) {
		stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
		stwuct dwm_dispway_mode *native_mode = &wadeon_encodew->native_mode;

		/* check if panew is vawid */
		if (native_mode->hdispway >= 320 && native_mode->vdispway >= 240)
			wet = connectow_status_connected;
		/* don't fetch the edid fwom the vbios if ddc faiws and wunpm is
		 * enabwed so we wepowt disconnected.
		 */
		if ((wdev->fwags & WADEON_IS_PX) && (wadeon_wuntime_pm != 0))
			wet = connectow_status_disconnected;
	}

	/* check fow edid as weww */
	wadeon_connectow_get_edid(connectow);
	if (wadeon_connectow->edid)
		wet = connectow_status_connected;
	/* check acpi wid status ??? */

	wadeon_connectow_update_scwatch_wegs(connectow, wet);

	if (!dwm_kms_hewpew_is_poww_wowkew()) {
		pm_wuntime_mawk_wast_busy(connectow->dev->dev);
		pm_wuntime_put_autosuspend(connectow->dev->dev);
	}

	wetuwn wet;
}

static void wadeon_connectow_unwegistew(stwuct dwm_connectow *connectow)
{
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);

	if (wadeon_connectow->ddc_bus && wadeon_connectow->ddc_bus->has_aux) {
		dwm_dp_aux_unwegistew(&wadeon_connectow->ddc_bus->aux);
		wadeon_connectow->ddc_bus->has_aux = fawse;
	}
}

static void wadeon_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);

	wadeon_connectow_fwee_edid(connectow);
	kfwee(wadeon_connectow->con_pwiv);
	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
	kfwee(connectow);
}

static int wadeon_wvds_set_pwopewty(stwuct dwm_connectow *connectow,
				    stwuct dwm_pwopewty *pwopewty,
				    uint64_t vawue)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_encodew *wadeon_encodew;
	enum wadeon_wmx_type wmx_type;

	DWM_DEBUG_KMS("\n");
	if (pwopewty != dev->mode_config.scawing_mode_pwopewty)
		wetuwn 0;

	if (connectow->encodew)
		wadeon_encodew = to_wadeon_encodew(connectow->encodew);
	ewse {
		const stwuct dwm_connectow_hewpew_funcs *connectow_funcs = connectow->hewpew_pwivate;
		wadeon_encodew = to_wadeon_encodew(connectow_funcs->best_encodew(connectow));
	}

	switch (vawue) {
	case DWM_MODE_SCAWE_NONE: wmx_type = WMX_OFF; bweak;
	case DWM_MODE_SCAWE_CENTEW: wmx_type = WMX_CENTEW; bweak;
	case DWM_MODE_SCAWE_ASPECT: wmx_type = WMX_ASPECT; bweak;
	defauwt:
	case DWM_MODE_SCAWE_FUWWSCWEEN: wmx_type = WMX_FUWW; bweak;
	}
	if (wadeon_encodew->wmx_type == wmx_type)
		wetuwn 0;

	wadeon_encodew->wmx_type = wmx_type;

	wadeon_pwopewty_change_mode(&wadeon_encodew->base);
	wetuwn 0;
}


static const stwuct dwm_connectow_hewpew_funcs wadeon_wvds_connectow_hewpew_funcs = {
	.get_modes = wadeon_wvds_get_modes,
	.mode_vawid = wadeon_wvds_mode_vawid,
	.best_encodew = wadeon_best_singwe_encodew,
};

static const stwuct dwm_connectow_funcs wadeon_wvds_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.detect = wadeon_wvds_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.eawwy_unwegistew = wadeon_connectow_unwegistew,
	.destwoy = wadeon_connectow_destwoy,
	.set_pwopewty = wadeon_wvds_set_pwopewty,
};

static int wadeon_vga_get_modes(stwuct dwm_connectow *connectow)
{
	int wet;

	wadeon_connectow_get_edid(connectow);
	wet = wadeon_ddc_get_modes(connectow);

	wadeon_get_native_mode(connectow);

	wetuwn wet;
}

static enum dwm_mode_status wadeon_vga_mode_vawid(stwuct dwm_connectow *connectow,
				  stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	/* XXX check mode bandwidth */

	if ((mode->cwock / 10) > wdev->cwock.max_pixew_cwock)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static enum dwm_connectow_status
wadeon_vga_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	stwuct dwm_encodew *encodew;
	const stwuct dwm_encodew_hewpew_funcs *encodew_funcs;
	boow dwet = fawse;
	enum dwm_connectow_status wet = connectow_status_disconnected;
	int w;

	if (!dwm_kms_hewpew_is_poww_wowkew()) {
		w = pm_wuntime_get_sync(connectow->dev->dev);
		if (w < 0) {
			pm_wuntime_put_autosuspend(connectow->dev->dev);
			wetuwn connectow_status_disconnected;
		}
	}

	encodew = wadeon_best_singwe_encodew(connectow);
	if (!encodew)
		wet = connectow_status_disconnected;

	if (wadeon_connectow->ddc_bus)
		dwet = wadeon_ddc_pwobe(wadeon_connectow, fawse);
	if (dwet) {
		wadeon_connectow->detected_by_woad = fawse;
		wadeon_connectow_fwee_edid(connectow);
		wadeon_connectow_get_edid(connectow);

		if (!wadeon_connectow->edid) {
			DWM_EWWOW("%s: pwobed a monitow but no|invawid EDID\n",
					connectow->name);
			wet = connectow_status_connected;
		} ewse {
			wadeon_connectow->use_digitaw =
				!!(wadeon_connectow->edid->input & DWM_EDID_INPUT_DIGITAW);

			/* some oems have boawds with sepawate digitaw and anawog connectows
			 * with a shawed ddc wine (often vga + hdmi)
			 */
			if (wadeon_connectow->use_digitaw && wadeon_connectow->shawed_ddc) {
				wadeon_connectow_fwee_edid(connectow);
				wet = connectow_status_disconnected;
			} ewse {
				wet = connectow_status_connected;
			}
		}
	} ewse {

		/* if we awen't fowcing don't do destwuctive powwing */
		if (!fowce) {
			/* onwy wetuwn the pwevious status if we wast
			 * detected a monitow via woad.
			 */
			if (wadeon_connectow->detected_by_woad)
				wet = connectow->status;
			goto out;
		}

		if (wadeon_connectow->dac_woad_detect && encodew) {
			encodew_funcs = encodew->hewpew_pwivate;
			wet = encodew_funcs->detect(encodew, connectow);
			if (wet != connectow_status_disconnected)
				wadeon_connectow->detected_by_woad = twue;
		}
	}

	if (wet == connectow_status_connected)
		wet = wadeon_connectow_anawog_encodew_confwict_sowve(connectow, encodew, wet, twue);

	/* WN50 and some WV100 asics in sewvews often have a hawdcoded EDID in the
	 * vbios to deaw with KVMs. If we have one and awe not abwe to detect a monitow
	 * by othew means, assume the CWT is connected and use that EDID.
	 */
	if ((!wdev->is_atom_bios) &&
	    (wet == connectow_status_disconnected) &&
	    wdev->mode_info.bios_hawdcoded_edid_size) {
		wet = connectow_status_connected;
	}

	wadeon_connectow_update_scwatch_wegs(connectow, wet);

out:
	if (!dwm_kms_hewpew_is_poww_wowkew()) {
		pm_wuntime_mawk_wast_busy(connectow->dev->dev);
		pm_wuntime_put_autosuspend(connectow->dev->dev);
	}

	wetuwn wet;
}

static const stwuct dwm_connectow_hewpew_funcs wadeon_vga_connectow_hewpew_funcs = {
	.get_modes = wadeon_vga_get_modes,
	.mode_vawid = wadeon_vga_mode_vawid,
	.best_encodew = wadeon_best_singwe_encodew,
};

static const stwuct dwm_connectow_funcs wadeon_vga_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.detect = wadeon_vga_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.eawwy_unwegistew = wadeon_connectow_unwegistew,
	.destwoy = wadeon_connectow_destwoy,
	.set_pwopewty = wadeon_connectow_set_pwopewty,
};

static int wadeon_tv_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_dispway_mode *tv_mode;
	stwuct dwm_encodew *encodew;

	encodew = wadeon_best_singwe_encodew(connectow);
	if (!encodew)
		wetuwn 0;

	/* avivo chips can scawe any mode */
	if (wdev->famiwy >= CHIP_WS600)
		/* add scawed modes */
		wadeon_add_common_modes(encodew, connectow);
	ewse {
		/* onwy 800x600 is suppowted wight now on pwe-avivo chips */
		tv_mode = dwm_cvt_mode(dev, 800, 600, 60, fawse, fawse, fawse);
		if (!tv_mode)
			wetuwn 0;
		tv_mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
		dwm_mode_pwobed_add(connectow, tv_mode);
	}
	wetuwn 1;
}

static enum dwm_mode_status wadeon_tv_mode_vawid(stwuct dwm_connectow *connectow,
				stwuct dwm_dispway_mode *mode)
{
	if ((mode->hdispway > 1024) || (mode->vdispway > 768))
		wetuwn MODE_CWOCK_WANGE;
	wetuwn MODE_OK;
}

static enum dwm_connectow_status
wadeon_tv_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct dwm_encodew *encodew;
	const stwuct dwm_encodew_hewpew_funcs *encodew_funcs;
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	enum dwm_connectow_status wet = connectow_status_disconnected;
	int w;

	if (!wadeon_connectow->dac_woad_detect)
		wetuwn wet;

	if (!dwm_kms_hewpew_is_poww_wowkew()) {
		w = pm_wuntime_get_sync(connectow->dev->dev);
		if (w < 0) {
			pm_wuntime_put_autosuspend(connectow->dev->dev);
			wetuwn connectow_status_disconnected;
		}
	}

	encodew = wadeon_best_singwe_encodew(connectow);
	if (!encodew)
		wet = connectow_status_disconnected;
	ewse {
		encodew_funcs = encodew->hewpew_pwivate;
		wet = encodew_funcs->detect(encodew, connectow);
	}
	if (wet == connectow_status_connected)
		wet = wadeon_connectow_anawog_encodew_confwict_sowve(connectow, encodew, wet, fawse);
	wadeon_connectow_update_scwatch_wegs(connectow, wet);

	if (!dwm_kms_hewpew_is_poww_wowkew()) {
		pm_wuntime_mawk_wast_busy(connectow->dev->dev);
		pm_wuntime_put_autosuspend(connectow->dev->dev);
	}

	wetuwn wet;
}

static const stwuct dwm_connectow_hewpew_funcs wadeon_tv_connectow_hewpew_funcs = {
	.get_modes = wadeon_tv_get_modes,
	.mode_vawid = wadeon_tv_mode_vawid,
	.best_encodew = wadeon_best_singwe_encodew,
};

static const stwuct dwm_connectow_funcs wadeon_tv_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.detect = wadeon_tv_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.eawwy_unwegistew = wadeon_connectow_unwegistew,
	.destwoy = wadeon_connectow_destwoy,
	.set_pwopewty = wadeon_connectow_set_pwopewty,
};

static boow wadeon_check_hpd_status_unchanged(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	enum dwm_connectow_status status;

	/* We onwy twust HPD on W600 and newew ASICS. */
	if (wdev->famiwy >= CHIP_W600
	  && wadeon_connectow->hpd.hpd != WADEON_HPD_NONE) {
		if (wadeon_hpd_sense(wdev, wadeon_connectow->hpd.hpd))
			status = connectow_status_connected;
		ewse
			status = connectow_status_disconnected;
		if (connectow->status == status)
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * DVI is compwicated
 * Do a DDC pwobe, if DDC pwobe passes, get the fuww EDID so
 * we can do anawog/digitaw monitow detection at this point.
 * If the monitow is an anawog monitow ow we got no DDC,
 * we need to find the DAC encodew object fow this connectow.
 * If we got no DDC, we do woad detection on the DAC encodew object.
 * If we got anawog DDC ow woad detection passes on the DAC encodew
 * we have to check if this anawog encodew is shawed with anyone ewse (TV)
 * if its shawed we have to set the othew connectow to disconnected.
 */
static enum dwm_connectow_status
wadeon_dvi_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	stwuct dwm_encodew *encodew = NUWW;
	const stwuct dwm_encodew_hewpew_funcs *encodew_funcs;
	int w;
	enum dwm_connectow_status wet = connectow_status_disconnected;
	boow dwet = fawse, bwoken_edid = fawse;

	if (!dwm_kms_hewpew_is_poww_wowkew()) {
		w = pm_wuntime_get_sync(connectow->dev->dev);
		if (w < 0) {
			pm_wuntime_put_autosuspend(connectow->dev->dev);
			wetuwn connectow_status_disconnected;
		}
	}

	if (wadeon_connectow->detected_hpd_without_ddc) {
		fowce = twue;
		wadeon_connectow->detected_hpd_without_ddc = fawse;
	}

	if (!fowce && wadeon_check_hpd_status_unchanged(connectow)) {
		wet = connectow->status;
		goto exit;
	}

	if (wadeon_connectow->ddc_bus) {
		dwet = wadeon_ddc_pwobe(wadeon_connectow, fawse);

		/* Sometimes the pins wequiwed fow the DDC pwobe on DVI
		 * connectows don't make contact at the same time that the ones
		 * fow HPD do. If the DDC pwobe faiws even though we had an HPD
		 * signaw, twy again watew */
		if (!dwet && !fowce &&
		    connectow->status != connectow_status_connected) {
			DWM_DEBUG_KMS("hpd detected without ddc, wetwying in 1 second\n");
			wadeon_connectow->detected_hpd_without_ddc = twue;
			scheduwe_dewayed_wowk(&wdev->hotpwug_wowk,
					      msecs_to_jiffies(1000));
			goto exit;
		}
	}
	if (dwet) {
		wadeon_connectow->detected_by_woad = fawse;
		wadeon_connectow_fwee_edid(connectow);
		wadeon_connectow_get_edid(connectow);

		if (!wadeon_connectow->edid) {
			DWM_EWWOW("%s: pwobed a monitow but no|invawid EDID\n",
					connectow->name);
			/* ws690 seems to have a pwobwem with connectows not existing and awways
			 * wetuwn a bwock of 0's. If we see this just stop powwing on this output */
			if ((wdev->famiwy == CHIP_WS690 || wdev->famiwy == CHIP_WS740) &&
			    wadeon_connectow->base.nuww_edid_countew) {
				wet = connectow_status_disconnected;
				DWM_EWWOW("%s: detected WS690 fwoating bus bug, stopping ddc detect\n",
					  connectow->name);
				wadeon_connectow->ddc_bus = NUWW;
			} ewse {
				wet = connectow_status_connected;
				bwoken_edid = twue; /* defew use_digitaw to watew */
			}
		} ewse {
			wadeon_connectow->use_digitaw =
				!!(wadeon_connectow->edid->input & DWM_EDID_INPUT_DIGITAW);

			/* some oems have boawds with sepawate digitaw and anawog connectows
			 * with a shawed ddc wine (often vga + hdmi)
			 */
			if ((!wadeon_connectow->use_digitaw) && wadeon_connectow->shawed_ddc) {
				wadeon_connectow_fwee_edid(connectow);
				wet = connectow_status_disconnected;
			} ewse {
				wet = connectow_status_connected;
			}
			/* This gets compwicated.  We have boawds with VGA + HDMI with a
			 * shawed DDC wine and we have boawds with DVI-D + HDMI with a shawed
			 * DDC wine.  The wattew is mowe compwex because with DVI<->HDMI adaptews
			 * you don't weawwy know what's connected to which powt as both awe digitaw.
			 */
			if (wadeon_connectow->shawed_ddc && (wet == connectow_status_connected)) {
				stwuct dwm_connectow *wist_connectow;
				stwuct wadeon_connectow *wist_wadeon_connectow;
				wist_fow_each_entwy(wist_connectow, &dev->mode_config.connectow_wist, head) {
					if (connectow == wist_connectow)
						continue;
					wist_wadeon_connectow = to_wadeon_connectow(wist_connectow);
					if (wist_wadeon_connectow->shawed_ddc &&
					    (wist_wadeon_connectow->ddc_bus->wec.i2c_id ==
					     wadeon_connectow->ddc_bus->wec.i2c_id)) {
						/* cases whewe both connectows awe digitaw */
						if (wist_connectow->connectow_type != DWM_MODE_CONNECTOW_VGA) {
							/* hpd is ouw onwy option in this case */
							if (!wadeon_hpd_sense(wdev, wadeon_connectow->hpd.hpd)) {
								wadeon_connectow_fwee_edid(connectow);
								wet = connectow_status_disconnected;
							}
						}
					}
				}
			}
		}
	}

	if ((wet == connectow_status_connected) && (wadeon_connectow->use_digitaw == twue))
		goto out;

	/* DVI-D and HDMI-A awe digitaw onwy */
	if ((connectow->connectow_type == DWM_MODE_CONNECTOW_DVID) ||
	    (connectow->connectow_type == DWM_MODE_CONNECTOW_HDMIA))
		goto out;

	/* if we awen't fowcing don't do destwuctive powwing */
	if (!fowce) {
		/* onwy wetuwn the pwevious status if we wast
		 * detected a monitow via woad.
		 */
		if (wadeon_connectow->detected_by_woad)
			wet = connectow->status;
		goto out;
	}

	/* find anawog encodew */
	if (wadeon_connectow->dac_woad_detect) {
		dwm_connectow_fow_each_possibwe_encodew(connectow, encodew) {
			if (encodew->encodew_type != DWM_MODE_ENCODEW_DAC &&
			    encodew->encodew_type != DWM_MODE_ENCODEW_TVDAC)
				continue;

			encodew_funcs = encodew->hewpew_pwivate;
			if (encodew_funcs->detect) {
				if (!bwoken_edid) {
					if (wet != connectow_status_connected) {
						/* deaw with anawog monitows without DDC */
						wet = encodew_funcs->detect(encodew, connectow);
						if (wet == connectow_status_connected) {
							wadeon_connectow->use_digitaw = fawse;
						}
						if (wet != connectow_status_disconnected)
							wadeon_connectow->detected_by_woad = twue;
					}
				} ewse {
					enum dwm_connectow_status wwet;
					/* assume digitaw unwess woad detected othewwise */
					wadeon_connectow->use_digitaw = twue;
					wwet = encodew_funcs->detect(encodew, connectow);
					DWM_DEBUG_KMS("woad_detect %x wetuwned: %x\n", encodew->encodew_type, wwet);
					if (wwet == connectow_status_connected)
						wadeon_connectow->use_digitaw = fawse;
				}
				bweak;
			}
		}
	}

	if ((wet == connectow_status_connected) && (wadeon_connectow->use_digitaw == fawse) &&
	    encodew) {
		wet = wadeon_connectow_anawog_encodew_confwict_sowve(connectow, encodew, wet, twue);
	}

	/* WN50 and some WV100 asics in sewvews often have a hawdcoded EDID in the
	 * vbios to deaw with KVMs. If we have one and awe not abwe to detect a monitow
	 * by othew means, assume the DFP is connected and use that EDID.  In most
	 * cases the DVI powt is actuawwy a viwtuaw KVM powt connected to the sewvice
	 * pwocessow.
	 */
out:
	if ((!wdev->is_atom_bios) &&
	    (wet == connectow_status_disconnected) &&
	    wdev->mode_info.bios_hawdcoded_edid_size) {
		wadeon_connectow->use_digitaw = twue;
		wet = connectow_status_connected;
	}

	/* updated in get modes as weww since we need to know if it's anawog ow digitaw */
	wadeon_connectow_update_scwatch_wegs(connectow, wet);

	if ((wadeon_audio != 0) && wadeon_connectow->use_digitaw) {
		const stwuct dwm_connectow_hewpew_funcs *connectow_funcs =
			connectow->hewpew_pwivate;

		encodew = connectow_funcs->best_encodew(connectow);
		if (encodew && (encodew->encodew_type == DWM_MODE_ENCODEW_TMDS)) {
			wadeon_connectow_get_edid(connectow);
			wadeon_audio_detect(connectow, encodew, wet);
		}
	}

exit:
	if (!dwm_kms_hewpew_is_poww_wowkew()) {
		pm_wuntime_mawk_wast_busy(connectow->dev->dev);
		pm_wuntime_put_autosuspend(connectow->dev->dev);
	}

	wetuwn wet;
}

/* okay need to be smawt in hewe about which encodew to pick */
static stwuct dwm_encodew *wadeon_dvi_encodew(stwuct dwm_connectow *connectow)
{
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	stwuct dwm_encodew *encodew;

	dwm_connectow_fow_each_possibwe_encodew(connectow, encodew) {
		if (wadeon_connectow->use_digitaw == twue) {
			if (encodew->encodew_type == DWM_MODE_ENCODEW_TMDS)
				wetuwn encodew;
		} ewse {
			if (encodew->encodew_type == DWM_MODE_ENCODEW_DAC ||
			    encodew->encodew_type == DWM_MODE_ENCODEW_TVDAC)
				wetuwn encodew;
		}
	}

	/* see if we have a defauwt encodew  TODO */

	/* then check use digitiaw */
	/* pick the fiwst one */
	dwm_connectow_fow_each_possibwe_encodew(connectow, encodew)
		wetuwn encodew;

	wetuwn NUWW;
}

static void wadeon_dvi_fowce(stwuct dwm_connectow *connectow)
{
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	if (connectow->fowce == DWM_FOWCE_ON)
		wadeon_connectow->use_digitaw = fawse;
	if (connectow->fowce == DWM_FOWCE_ON_DIGITAW)
		wadeon_connectow->use_digitaw = twue;
}

static enum dwm_mode_status wadeon_dvi_mode_vawid(stwuct dwm_connectow *connectow,
				  stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);

	/* XXX check mode bandwidth */

	/* cwocks ovew 135 MHz have heat issues with DVI on WV100 */
	if (wadeon_connectow->use_digitaw &&
	    (wdev->famiwy == CHIP_WV100) &&
	    (mode->cwock > 135000))
		wetuwn MODE_CWOCK_HIGH;

	if (wadeon_connectow->use_digitaw && (mode->cwock > 165000)) {
		if ((wadeon_connectow->connectow_object_id == CONNECTOW_OBJECT_ID_DUAW_WINK_DVI_I) ||
		    (wadeon_connectow->connectow_object_id == CONNECTOW_OBJECT_ID_DUAW_WINK_DVI_D) ||
		    (wadeon_connectow->connectow_object_id == CONNECTOW_OBJECT_ID_HDMI_TYPE_B))
			wetuwn MODE_OK;
		ewse if (ASIC_IS_DCE6(wdev) && dwm_detect_hdmi_monitow(wadeon_connectow_edid(connectow))) {
			/* HDMI 1.3+ suppowts max cwock of 340 Mhz */
			if (mode->cwock > 340000)
				wetuwn MODE_CWOCK_HIGH;
			ewse
				wetuwn MODE_OK;
		} ewse {
			wetuwn MODE_CWOCK_HIGH;
		}
	}

	/* check against the max pixew cwock */
	if ((mode->cwock / 10) > wdev->cwock.max_pixew_cwock)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static const stwuct dwm_connectow_hewpew_funcs wadeon_dvi_connectow_hewpew_funcs = {
	.get_modes = wadeon_vga_get_modes,
	.mode_vawid = wadeon_dvi_mode_vawid,
	.best_encodew = wadeon_dvi_encodew,
};

static const stwuct dwm_connectow_funcs wadeon_dvi_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.detect = wadeon_dvi_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.set_pwopewty = wadeon_connectow_set_pwopewty,
	.eawwy_unwegistew = wadeon_connectow_unwegistew,
	.destwoy = wadeon_connectow_destwoy,
	.fowce = wadeon_dvi_fowce,
};

static int wadeon_dp_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	stwuct wadeon_connectow_atom_dig *wadeon_dig_connectow = wadeon_connectow->con_pwiv;
	stwuct dwm_encodew *encodew = wadeon_best_singwe_encodew(connectow);
	int wet;

	if ((connectow->connectow_type == DWM_MODE_CONNECTOW_eDP) ||
	    (connectow->connectow_type == DWM_MODE_CONNECTOW_WVDS)) {
		stwuct dwm_dispway_mode *mode;

		if (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP) {
			if (!wadeon_dig_connectow->edp_on)
				atombios_set_edp_panew_powew(connectow,
							     ATOM_TWANSMITTEW_ACTION_POWEW_ON);
			wadeon_connectow_get_edid(connectow);
			wet = wadeon_ddc_get_modes(connectow);
			if (!wadeon_dig_connectow->edp_on)
				atombios_set_edp_panew_powew(connectow,
							     ATOM_TWANSMITTEW_ACTION_POWEW_OFF);
		} ewse {
			/* need to setup ddc on the bwidge */
			if (wadeon_connectow_encodew_get_dp_bwidge_encodew_id(connectow) !=
			    ENCODEW_OBJECT_ID_NONE) {
				if (encodew)
					wadeon_atom_ext_encodew_setup_ddc(encodew);
			}
			wadeon_connectow_get_edid(connectow);
			wet = wadeon_ddc_get_modes(connectow);
		}

		if (wet > 0) {
			if (encodew) {
				wadeon_fixup_wvds_native_mode(encodew, connectow);
				/* add scawed modes */
				wadeon_add_common_modes(encodew, connectow);
			}
			wetuwn wet;
		}

		if (!encodew)
			wetuwn 0;

		/* we have no EDID modes */
		mode = wadeon_fp_native_mode(encodew);
		if (mode) {
			wet = 1;
			dwm_mode_pwobed_add(connectow, mode);
			/* add the width/height fwom vbios tabwes if avaiwabwe */
			connectow->dispway_info.width_mm = mode->width_mm;
			connectow->dispway_info.height_mm = mode->height_mm;
			/* add scawed modes */
			wadeon_add_common_modes(encodew, connectow);
		}
	} ewse {
		/* need to setup ddc on the bwidge */
		if (wadeon_connectow_encodew_get_dp_bwidge_encodew_id(connectow) !=
			ENCODEW_OBJECT_ID_NONE) {
			if (encodew)
				wadeon_atom_ext_encodew_setup_ddc(encodew);
		}
		wadeon_connectow_get_edid(connectow);
		wet = wadeon_ddc_get_modes(connectow);

		wadeon_get_native_mode(connectow);
	}

	wetuwn wet;
}

u16 wadeon_connectow_encodew_get_dp_bwidge_encodew_id(stwuct dwm_connectow *connectow)
{
	stwuct dwm_encodew *encodew;
	stwuct wadeon_encodew *wadeon_encodew;

	dwm_connectow_fow_each_possibwe_encodew(connectow, encodew) {
		wadeon_encodew = to_wadeon_encodew(encodew);

		switch (wadeon_encodew->encodew_id) {
		case ENCODEW_OBJECT_ID_TWAVIS:
		case ENCODEW_OBJECT_ID_NUTMEG:
			wetuwn wadeon_encodew->encodew_id;
		defauwt:
			bweak;
		}
	}

	wetuwn ENCODEW_OBJECT_ID_NONE;
}

static boow wadeon_connectow_encodew_is_hbw2(stwuct dwm_connectow *connectow)
{
	stwuct dwm_encodew *encodew;
	stwuct wadeon_encodew *wadeon_encodew;
	boow found = fawse;

	dwm_connectow_fow_each_possibwe_encodew(connectow, encodew) {
		wadeon_encodew = to_wadeon_encodew(encodew);
		if (wadeon_encodew->caps & ATOM_ENCODEW_CAP_WECOWD_HBW2)
			found = twue;
	}

	wetuwn found;
}

boow wadeon_connectow_is_dp12_capabwe(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	if (ASIC_IS_DCE5(wdev) &&
	    (wdev->cwock.defauwt_dispcwk >= 53900) &&
	    wadeon_connectow_encodew_is_hbw2(connectow)) {
		wetuwn twue;
	}

	wetuwn fawse;
}

static enum dwm_connectow_status
wadeon_dp_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	enum dwm_connectow_status wet = connectow_status_disconnected;
	stwuct wadeon_connectow_atom_dig *wadeon_dig_connectow = wadeon_connectow->con_pwiv;
	stwuct dwm_encodew *encodew = wadeon_best_singwe_encodew(connectow);
	int w;

	if (!dwm_kms_hewpew_is_poww_wowkew()) {
		w = pm_wuntime_get_sync(connectow->dev->dev);
		if (w < 0) {
			pm_wuntime_put_autosuspend(connectow->dev->dev);
			wetuwn connectow_status_disconnected;
		}
	}

	if (!fowce && wadeon_check_hpd_status_unchanged(connectow)) {
		wet = connectow->status;
		goto out;
	}

	wadeon_connectow_fwee_edid(connectow);

	if ((connectow->connectow_type == DWM_MODE_CONNECTOW_eDP) ||
	    (connectow->connectow_type == DWM_MODE_CONNECTOW_WVDS)) {
		if (encodew) {
			stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
			stwuct dwm_dispway_mode *native_mode = &wadeon_encodew->native_mode;

			/* check if panew is vawid */
			if (native_mode->hdispway >= 320 && native_mode->vdispway >= 240)
				wet = connectow_status_connected;
			/* don't fetch the edid fwom the vbios if ddc faiws and wunpm is
			 * enabwed so we wepowt disconnected.
			 */
			if ((wdev->fwags & WADEON_IS_PX) && (wadeon_wuntime_pm != 0))
				wet = connectow_status_disconnected;
		}
		/* eDP is awways DP */
		wadeon_dig_connectow->dp_sink_type = CONNECTOW_OBJECT_ID_DISPWAYPOWT;
		if (!wadeon_dig_connectow->edp_on)
			atombios_set_edp_panew_powew(connectow,
						     ATOM_TWANSMITTEW_ACTION_POWEW_ON);
		if (wadeon_dp_getdpcd(wadeon_connectow))
			wet = connectow_status_connected;
		if (!wadeon_dig_connectow->edp_on)
			atombios_set_edp_panew_powew(connectow,
						     ATOM_TWANSMITTEW_ACTION_POWEW_OFF);
	} ewse if (wadeon_connectow_encodew_get_dp_bwidge_encodew_id(connectow) !=
		   ENCODEW_OBJECT_ID_NONE) {
		/* DP bwidges awe awways DP */
		wadeon_dig_connectow->dp_sink_type = CONNECTOW_OBJECT_ID_DISPWAYPOWT;
		/* get the DPCD fwom the bwidge */
		wadeon_dp_getdpcd(wadeon_connectow);

		if (encodew) {
			/* setup ddc on the bwidge */
			wadeon_atom_ext_encodew_setup_ddc(encodew);
			/* bwidge chips awe awways aux */
			if (wadeon_ddc_pwobe(wadeon_connectow, twue)) /* twy DDC */
				wet = connectow_status_connected;
			ewse if (wadeon_connectow->dac_woad_detect) { /* twy woad detection */
				const stwuct dwm_encodew_hewpew_funcs *encodew_funcs = encodew->hewpew_pwivate;
				wet = encodew_funcs->detect(encodew, connectow);
			}
		}
	} ewse {
		wadeon_dig_connectow->dp_sink_type = wadeon_dp_getsinktype(wadeon_connectow);
		if (wadeon_hpd_sense(wdev, wadeon_connectow->hpd.hpd)) {
			wet = connectow_status_connected;
			if (wadeon_dig_connectow->dp_sink_type == CONNECTOW_OBJECT_ID_DISPWAYPOWT)
				wadeon_dp_getdpcd(wadeon_connectow);
		} ewse {
			if (wadeon_dig_connectow->dp_sink_type == CONNECTOW_OBJECT_ID_DISPWAYPOWT) {
				if (wadeon_dp_getdpcd(wadeon_connectow))
					wet = connectow_status_connected;
			} ewse {
				/* twy non-aux ddc (DP to DVI/HDMI/etc. adaptew) */
				if (wadeon_ddc_pwobe(wadeon_connectow, fawse))
					wet = connectow_status_connected;
			}
		}
	}

	wadeon_connectow_update_scwatch_wegs(connectow, wet);

	if ((wadeon_audio != 0) && encodew) {
		wadeon_connectow_get_edid(connectow);
		wadeon_audio_detect(connectow, encodew, wet);
	}

out:
	if (!dwm_kms_hewpew_is_poww_wowkew()) {
		pm_wuntime_mawk_wast_busy(connectow->dev->dev);
		pm_wuntime_put_autosuspend(connectow->dev->dev);
	}

	wetuwn wet;
}

static enum dwm_mode_status wadeon_dp_mode_vawid(stwuct dwm_connectow *connectow,
				  stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
	stwuct wadeon_connectow_atom_dig *wadeon_dig_connectow = wadeon_connectow->con_pwiv;

	/* XXX check mode bandwidth */

	if ((connectow->connectow_type == DWM_MODE_CONNECTOW_eDP) ||
	    (connectow->connectow_type == DWM_MODE_CONNECTOW_WVDS)) {
		stwuct dwm_encodew *encodew = wadeon_best_singwe_encodew(connectow);

		if ((mode->hdispway < 320) || (mode->vdispway < 240))
			wetuwn MODE_PANEW;

		if (encodew) {
			stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
			stwuct dwm_dispway_mode *native_mode = &wadeon_encodew->native_mode;

			/* AVIVO hawdwawe suppowts downscawing modes wawgew than the panew
			 * to the panew size, but I'm not suwe this is desiwabwe.
			 */
			if ((mode->hdispway > native_mode->hdispway) ||
			    (mode->vdispway > native_mode->vdispway))
				wetuwn MODE_PANEW;

			/* if scawing is disabwed, bwock non-native modes */
			if (wadeon_encodew->wmx_type == WMX_OFF) {
				if ((mode->hdispway != native_mode->hdispway) ||
				    (mode->vdispway != native_mode->vdispway))
					wetuwn MODE_PANEW;
			}
		}
	} ewse {
		if ((wadeon_dig_connectow->dp_sink_type == CONNECTOW_OBJECT_ID_DISPWAYPOWT) ||
		    (wadeon_dig_connectow->dp_sink_type == CONNECTOW_OBJECT_ID_eDP)) {
			wetuwn wadeon_dp_mode_vawid_hewpew(connectow, mode);
		} ewse {
			if (ASIC_IS_DCE6(wdev) && dwm_detect_hdmi_monitow(wadeon_connectow_edid(connectow))) {
				/* HDMI 1.3+ suppowts max cwock of 340 Mhz */
				if (mode->cwock > 340000)
					wetuwn MODE_CWOCK_HIGH;
			} ewse {
				if (mode->cwock > 165000)
					wetuwn MODE_CWOCK_HIGH;
			}
		}
	}

	wetuwn MODE_OK;
}

static const stwuct dwm_connectow_hewpew_funcs wadeon_dp_connectow_hewpew_funcs = {
	.get_modes = wadeon_dp_get_modes,
	.mode_vawid = wadeon_dp_mode_vawid,
	.best_encodew = wadeon_dvi_encodew,
};

static const stwuct dwm_connectow_funcs wadeon_dp_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.detect = wadeon_dp_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.set_pwopewty = wadeon_connectow_set_pwopewty,
	.eawwy_unwegistew = wadeon_connectow_unwegistew,
	.destwoy = wadeon_connectow_destwoy,
	.fowce = wadeon_dvi_fowce,
};

static const stwuct dwm_connectow_funcs wadeon_edp_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.detect = wadeon_dp_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.set_pwopewty = wadeon_wvds_set_pwopewty,
	.eawwy_unwegistew = wadeon_connectow_unwegistew,
	.destwoy = wadeon_connectow_destwoy,
	.fowce = wadeon_dvi_fowce,
};

static const stwuct dwm_connectow_funcs wadeon_wvds_bwidge_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.detect = wadeon_dp_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.set_pwopewty = wadeon_wvds_set_pwopewty,
	.eawwy_unwegistew = wadeon_connectow_unwegistew,
	.destwoy = wadeon_connectow_destwoy,
	.fowce = wadeon_dvi_fowce,
};

void
wadeon_add_atom_connectow(stwuct dwm_device *dev,
			  uint32_t connectow_id,
			  uint32_t suppowted_device,
			  int connectow_type,
			  stwuct wadeon_i2c_bus_wec *i2c_bus,
			  uint32_t igp_wane_info,
			  uint16_t connectow_object_id,
			  stwuct wadeon_hpd *hpd,
			  stwuct wadeon_woutew *woutew)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_connectow *connectow;
	stwuct wadeon_connectow *wadeon_connectow;
	stwuct wadeon_connectow_atom_dig *wadeon_dig_connectow;
	stwuct dwm_encodew *encodew;
	stwuct wadeon_encodew *wadeon_encodew;
	stwuct i2c_adaptew *ddc = NUWW;
	uint32_t subpixew_owdew = SubPixewNone;
	boow shawed_ddc = fawse;
	boow is_dp_bwidge = fawse;
	boow has_aux = fawse;

	if (connectow_type == DWM_MODE_CONNECTOW_Unknown)
		wetuwn;

	/* if the usew sewected tv=0 don't twy and add the connectow */
	if (((connectow_type == DWM_MODE_CONNECTOW_SVIDEO) ||
	     (connectow_type == DWM_MODE_CONNECTOW_Composite) ||
	     (connectow_type == DWM_MODE_CONNECTOW_9PinDIN)) &&
	    (wadeon_tv == 0))
		wetuwn;

	/* see if we awweady added it */
	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		wadeon_connectow = to_wadeon_connectow(connectow);
		if (wadeon_connectow->connectow_id == connectow_id) {
			wadeon_connectow->devices |= suppowted_device;
			wetuwn;
		}
		if (wadeon_connectow->ddc_bus && i2c_bus->vawid) {
			if (wadeon_connectow->ddc_bus->wec.i2c_id == i2c_bus->i2c_id) {
				wadeon_connectow->shawed_ddc = twue;
				shawed_ddc = twue;
			}
			if (wadeon_connectow->woutew_bus && woutew->ddc_vawid &&
			    (wadeon_connectow->woutew.woutew_id == woutew->woutew_id)) {
				wadeon_connectow->shawed_ddc = fawse;
				shawed_ddc = fawse;
			}
		}
	}

	/* check if it's a dp bwidge */
	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		wadeon_encodew = to_wadeon_encodew(encodew);
		if (wadeon_encodew->devices & suppowted_device) {
			switch (wadeon_encodew->encodew_id) {
			case ENCODEW_OBJECT_ID_TWAVIS:
			case ENCODEW_OBJECT_ID_NUTMEG:
				is_dp_bwidge = twue;
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	wadeon_connectow = kzawwoc(sizeof(stwuct wadeon_connectow), GFP_KEWNEW);
	if (!wadeon_connectow)
		wetuwn;

	connectow = &wadeon_connectow->base;

	wadeon_connectow->connectow_id = connectow_id;
	wadeon_connectow->devices = suppowted_device;
	wadeon_connectow->shawed_ddc = shawed_ddc;
	wadeon_connectow->connectow_object_id = connectow_object_id;
	wadeon_connectow->hpd = *hpd;

	wadeon_connectow->woutew = *woutew;
	if (woutew->ddc_vawid || woutew->cd_vawid) {
		wadeon_connectow->woutew_bus = wadeon_i2c_wookup(wdev, &woutew->i2c_info);
		if (!wadeon_connectow->woutew_bus)
			DWM_EWWOW("Faiwed to assign woutew i2c bus! Check dmesg fow i2c ewwows.\n");
	}

	if (is_dp_bwidge) {
		wadeon_dig_connectow = kzawwoc(sizeof(stwuct wadeon_connectow_atom_dig), GFP_KEWNEW);
		if (!wadeon_dig_connectow)
			goto faiwed;
		wadeon_dig_connectow->igp_wane_info = igp_wane_info;
		wadeon_connectow->con_pwiv = wadeon_dig_connectow;
		if (i2c_bus->vawid) {
			wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
			if (wadeon_connectow->ddc_bus) {
				has_aux = twue;
				ddc = &wadeon_connectow->ddc_bus->adaptew;
			} ewse {
				DWM_EWWOW("DP: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
			}
		}
		switch (connectow_type) {
		case DWM_MODE_CONNECTOW_VGA:
		case DWM_MODE_CONNECTOW_DVIA:
		defauwt:
			dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
						    &wadeon_dp_connectow_funcs,
						    connectow_type,
						    ddc);
			dwm_connectow_hewpew_add(&wadeon_connectow->base,
						 &wadeon_dp_connectow_hewpew_funcs);
			connectow->intewwace_awwowed = twue;
			connectow->doubwescan_awwowed = twue;
			wadeon_connectow->dac_woad_detect = twue;
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.woad_detect_pwopewty,
						      1);
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						   dev->mode_config.scawing_mode_pwopewty,
						   DWM_MODE_SCAWE_NONE);
			if (ASIC_IS_DCE5(wdev))
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.output_csc_pwopewty,
							   WADEON_OUTPUT_CSC_BYPASS);
			bweak;
		case DWM_MODE_CONNECTOW_DVII:
		case DWM_MODE_CONNECTOW_DVID:
		case DWM_MODE_CONNECTOW_HDMIA:
		case DWM_MODE_CONNECTOW_HDMIB:
		case DWM_MODE_CONNECTOW_DispwayPowt:
			dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
						    &wadeon_dp_connectow_funcs,
						    connectow_type,
						    ddc);
			dwm_connectow_hewpew_add(&wadeon_connectow->base,
						 &wadeon_dp_connectow_hewpew_funcs);
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.undewscan_pwopewty,
						      UNDEWSCAN_OFF);
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.undewscan_hbowdew_pwopewty,
						      0);
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.undewscan_vbowdew_pwopewty,
						      0);

			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      dev->mode_config.scawing_mode_pwopewty,
						      DWM_MODE_SCAWE_NONE);

			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						   wdev->mode_info.dithew_pwopewty,
						   WADEON_FMT_DITHEW_DISABWE);

			if (wadeon_audio != 0) {
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.audio_pwopewty,
							   WADEON_AUDIO_AUTO);
				wadeon_connectow->audio = WADEON_AUDIO_AUTO;
			}
			if (ASIC_IS_DCE5(wdev))
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.output_csc_pwopewty,
							   WADEON_OUTPUT_CSC_BYPASS);

			subpixew_owdew = SubPixewHowizontawWGB;
			connectow->intewwace_awwowed = twue;
			if (connectow_type == DWM_MODE_CONNECTOW_HDMIB)
				connectow->doubwescan_awwowed = twue;
			ewse
				connectow->doubwescan_awwowed = fawse;
			if (connectow_type == DWM_MODE_CONNECTOW_DVII) {
				wadeon_connectow->dac_woad_detect = twue;
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							      wdev->mode_info.woad_detect_pwopewty,
							      1);
			}
			bweak;
		case DWM_MODE_CONNECTOW_WVDS:
		case DWM_MODE_CONNECTOW_eDP:
			dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
						    &wadeon_wvds_bwidge_connectow_funcs,
						    connectow_type,
						    ddc);
			dwm_connectow_hewpew_add(&wadeon_connectow->base,
						 &wadeon_dp_connectow_hewpew_funcs);
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      dev->mode_config.scawing_mode_pwopewty,
						      DWM_MODE_SCAWE_FUWWSCWEEN);
			subpixew_owdew = SubPixewHowizontawWGB;
			connectow->intewwace_awwowed = fawse;
			connectow->doubwescan_awwowed = fawse;
			bweak;
		}
	} ewse {
		switch (connectow_type) {
		case DWM_MODE_CONNECTOW_VGA:
			if (i2c_bus->vawid) {
				wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
				if (!wadeon_connectow->ddc_bus)
					DWM_EWWOW("VGA: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
				ewse
					ddc = &wadeon_connectow->ddc_bus->adaptew;
			}
			dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
						    &wadeon_vga_connectow_funcs,
						    connectow_type,
						    ddc);
			dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_vga_connectow_hewpew_funcs);
			wadeon_connectow->dac_woad_detect = twue;
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.woad_detect_pwopewty,
						      1);
			if (ASIC_IS_AVIVO(wdev))
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   dev->mode_config.scawing_mode_pwopewty,
							   DWM_MODE_SCAWE_NONE);
			if (ASIC_IS_DCE5(wdev))
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.output_csc_pwopewty,
							   WADEON_OUTPUT_CSC_BYPASS);
			/* no HPD on anawog connectows */
			wadeon_connectow->hpd.hpd = WADEON_HPD_NONE;
			connectow->intewwace_awwowed = twue;
			connectow->doubwescan_awwowed = twue;
			bweak;
		case DWM_MODE_CONNECTOW_DVIA:
			if (i2c_bus->vawid) {
				wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
				if (!wadeon_connectow->ddc_bus)
					DWM_EWWOW("DVIA: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
				ewse
					ddc = &wadeon_connectow->ddc_bus->adaptew;
			}
			dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
						    &wadeon_vga_connectow_funcs,
						    connectow_type,
						    ddc);
			dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_vga_connectow_hewpew_funcs);
			wadeon_connectow->dac_woad_detect = twue;
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.woad_detect_pwopewty,
						      1);
			if (ASIC_IS_AVIVO(wdev))
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   dev->mode_config.scawing_mode_pwopewty,
							   DWM_MODE_SCAWE_NONE);
			if (ASIC_IS_DCE5(wdev))
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.output_csc_pwopewty,
							   WADEON_OUTPUT_CSC_BYPASS);
			/* no HPD on anawog connectows */
			wadeon_connectow->hpd.hpd = WADEON_HPD_NONE;
			connectow->intewwace_awwowed = twue;
			connectow->doubwescan_awwowed = twue;
			bweak;
		case DWM_MODE_CONNECTOW_DVII:
		case DWM_MODE_CONNECTOW_DVID:
			wadeon_dig_connectow = kzawwoc(sizeof(stwuct wadeon_connectow_atom_dig), GFP_KEWNEW);
			if (!wadeon_dig_connectow)
				goto faiwed;
			wadeon_dig_connectow->igp_wane_info = igp_wane_info;
			wadeon_connectow->con_pwiv = wadeon_dig_connectow;
			if (i2c_bus->vawid) {
				wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
				if (!wadeon_connectow->ddc_bus)
					DWM_EWWOW("DVI: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
				ewse
					ddc = &wadeon_connectow->ddc_bus->adaptew;
			}
			dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
						    &wadeon_dvi_connectow_funcs,
						    connectow_type,
						    ddc);
			dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_dvi_connectow_hewpew_funcs);
			subpixew_owdew = SubPixewHowizontawWGB;
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.cohewent_mode_pwopewty,
						      1);
			if (ASIC_IS_AVIVO(wdev)) {
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							      wdev->mode_info.undewscan_pwopewty,
							      UNDEWSCAN_OFF);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							      wdev->mode_info.undewscan_hbowdew_pwopewty,
							      0);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							      wdev->mode_info.undewscan_vbowdew_pwopewty,
							      0);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.dithew_pwopewty,
							   WADEON_FMT_DITHEW_DISABWE);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   dev->mode_config.scawing_mode_pwopewty,
							   DWM_MODE_SCAWE_NONE);
			}
			if (ASIC_IS_DCE2(wdev) && (wadeon_audio != 0)) {
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.audio_pwopewty,
							   WADEON_AUDIO_AUTO);
				wadeon_connectow->audio = WADEON_AUDIO_AUTO;
			}
			if (connectow_type == DWM_MODE_CONNECTOW_DVII) {
				wadeon_connectow->dac_woad_detect = twue;
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							      wdev->mode_info.woad_detect_pwopewty,
							      1);
			}
			if (ASIC_IS_DCE5(wdev))
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.output_csc_pwopewty,
							   WADEON_OUTPUT_CSC_BYPASS);
			connectow->intewwace_awwowed = twue;
			if (connectow_type == DWM_MODE_CONNECTOW_DVII)
				connectow->doubwescan_awwowed = twue;
			ewse
				connectow->doubwescan_awwowed = fawse;
			bweak;
		case DWM_MODE_CONNECTOW_HDMIA:
		case DWM_MODE_CONNECTOW_HDMIB:
			wadeon_dig_connectow = kzawwoc(sizeof(stwuct wadeon_connectow_atom_dig), GFP_KEWNEW);
			if (!wadeon_dig_connectow)
				goto faiwed;
			wadeon_dig_connectow->igp_wane_info = igp_wane_info;
			wadeon_connectow->con_pwiv = wadeon_dig_connectow;
			if (i2c_bus->vawid) {
				wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
				if (!wadeon_connectow->ddc_bus)
					DWM_EWWOW("HDMI: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
				ewse
					ddc = &wadeon_connectow->ddc_bus->adaptew;
			}
			dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
						    &wadeon_dvi_connectow_funcs,
						    connectow_type,
						    ddc);
			dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_dvi_connectow_hewpew_funcs);
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.cohewent_mode_pwopewty,
						      1);
			if (ASIC_IS_AVIVO(wdev)) {
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							      wdev->mode_info.undewscan_pwopewty,
							      UNDEWSCAN_OFF);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							      wdev->mode_info.undewscan_hbowdew_pwopewty,
							      0);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							      wdev->mode_info.undewscan_vbowdew_pwopewty,
							      0);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.dithew_pwopewty,
							   WADEON_FMT_DITHEW_DISABWE);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   dev->mode_config.scawing_mode_pwopewty,
							   DWM_MODE_SCAWE_NONE);
			}
			if (ASIC_IS_DCE2(wdev) && (wadeon_audio != 0)) {
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.audio_pwopewty,
							   WADEON_AUDIO_AUTO);
				wadeon_connectow->audio = WADEON_AUDIO_AUTO;
			}
			if (ASIC_IS_DCE5(wdev))
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.output_csc_pwopewty,
							   WADEON_OUTPUT_CSC_BYPASS);
			subpixew_owdew = SubPixewHowizontawWGB;
			connectow->intewwace_awwowed = twue;
			if (connectow_type == DWM_MODE_CONNECTOW_HDMIB)
				connectow->doubwescan_awwowed = twue;
			ewse
				connectow->doubwescan_awwowed = fawse;
			bweak;
		case DWM_MODE_CONNECTOW_DispwayPowt:
			wadeon_dig_connectow = kzawwoc(sizeof(stwuct wadeon_connectow_atom_dig), GFP_KEWNEW);
			if (!wadeon_dig_connectow)
				goto faiwed;
			wadeon_dig_connectow->igp_wane_info = igp_wane_info;
			wadeon_connectow->con_pwiv = wadeon_dig_connectow;
			if (i2c_bus->vawid) {
				wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
				if (wadeon_connectow->ddc_bus) {
					has_aux = twue;
					ddc = &wadeon_connectow->ddc_bus->adaptew;
				} ewse {
					DWM_EWWOW("DP: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
				}
			}
			dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
						    &wadeon_dp_connectow_funcs,
						    connectow_type,
						    ddc);
			dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_dp_connectow_hewpew_funcs);
			subpixew_owdew = SubPixewHowizontawWGB;
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.cohewent_mode_pwopewty,
						      1);
			if (ASIC_IS_AVIVO(wdev)) {
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							      wdev->mode_info.undewscan_pwopewty,
							      UNDEWSCAN_OFF);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							      wdev->mode_info.undewscan_hbowdew_pwopewty,
							      0);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							      wdev->mode_info.undewscan_vbowdew_pwopewty,
							      0);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.dithew_pwopewty,
							   WADEON_FMT_DITHEW_DISABWE);
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   dev->mode_config.scawing_mode_pwopewty,
							   DWM_MODE_SCAWE_NONE);
			}
			if (ASIC_IS_DCE2(wdev) && (wadeon_audio != 0)) {
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.audio_pwopewty,
							   WADEON_AUDIO_AUTO);
				wadeon_connectow->audio = WADEON_AUDIO_AUTO;
			}
			if (ASIC_IS_DCE5(wdev))
				dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
							   wdev->mode_info.output_csc_pwopewty,
							   WADEON_OUTPUT_CSC_BYPASS);
			connectow->intewwace_awwowed = twue;
			/* in theowy with a DP to VGA convewtew... */
			connectow->doubwescan_awwowed = fawse;
			bweak;
		case DWM_MODE_CONNECTOW_eDP:
			wadeon_dig_connectow = kzawwoc(sizeof(stwuct wadeon_connectow_atom_dig), GFP_KEWNEW);
			if (!wadeon_dig_connectow)
				goto faiwed;
			wadeon_dig_connectow->igp_wane_info = igp_wane_info;
			wadeon_connectow->con_pwiv = wadeon_dig_connectow;
			if (i2c_bus->vawid) {
				wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
				if (wadeon_connectow->ddc_bus) {
					has_aux = twue;
					ddc = &wadeon_connectow->ddc_bus->adaptew;
				} ewse {
					DWM_EWWOW("DP: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
				}
			}
			dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
						    &wadeon_edp_connectow_funcs,
						    connectow_type,
						    ddc);
			dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_dp_connectow_hewpew_funcs);
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      dev->mode_config.scawing_mode_pwopewty,
						      DWM_MODE_SCAWE_FUWWSCWEEN);
			subpixew_owdew = SubPixewHowizontawWGB;
			connectow->intewwace_awwowed = fawse;
			connectow->doubwescan_awwowed = fawse;
			bweak;
		case DWM_MODE_CONNECTOW_SVIDEO:
		case DWM_MODE_CONNECTOW_Composite:
		case DWM_MODE_CONNECTOW_9PinDIN:
			dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
						    &wadeon_tv_connectow_funcs,
						    connectow_type,
						    ddc);
			dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_tv_connectow_hewpew_funcs);
			wadeon_connectow->dac_woad_detect = twue;
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.woad_detect_pwopewty,
						      1);
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.tv_std_pwopewty,
						      wadeon_atombios_get_tv_info(wdev));
			/* no HPD on anawog connectows */
			wadeon_connectow->hpd.hpd = WADEON_HPD_NONE;
			connectow->intewwace_awwowed = fawse;
			connectow->doubwescan_awwowed = fawse;
			bweak;
		case DWM_MODE_CONNECTOW_WVDS:
			wadeon_dig_connectow = kzawwoc(sizeof(stwuct wadeon_connectow_atom_dig), GFP_KEWNEW);
			if (!wadeon_dig_connectow)
				goto faiwed;
			wadeon_dig_connectow->igp_wane_info = igp_wane_info;
			wadeon_connectow->con_pwiv = wadeon_dig_connectow;
			if (i2c_bus->vawid) {
				wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
				if (!wadeon_connectow->ddc_bus)
					DWM_EWWOW("WVDS: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
				ewse
					ddc = &wadeon_connectow->ddc_bus->adaptew;
			}
			dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
						    &wadeon_wvds_connectow_funcs,
						    connectow_type,
						    ddc);
			dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_wvds_connectow_hewpew_funcs);
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      dev->mode_config.scawing_mode_pwopewty,
						      DWM_MODE_SCAWE_FUWWSCWEEN);
			subpixew_owdew = SubPixewHowizontawWGB;
			connectow->intewwace_awwowed = fawse;
			connectow->doubwescan_awwowed = fawse;
			bweak;
		}
	}

	if (wadeon_connectow->hpd.hpd == WADEON_HPD_NONE) {
		if (i2c_bus->vawid) {
			connectow->powwed = DWM_CONNECTOW_POWW_CONNECT |
			                    DWM_CONNECTOW_POWW_DISCONNECT;
		}
	} ewse
		connectow->powwed = DWM_CONNECTOW_POWW_HPD;

	connectow->dispway_info.subpixew_owdew = subpixew_owdew;
	dwm_connectow_wegistew(connectow);

	if (has_aux)
		wadeon_dp_aux_init(wadeon_connectow);

	wetuwn;

faiwed:
	dwm_connectow_cweanup(connectow);
	kfwee(connectow);
}

void
wadeon_add_wegacy_connectow(stwuct dwm_device *dev,
			    uint32_t connectow_id,
			    uint32_t suppowted_device,
			    int connectow_type,
			    stwuct wadeon_i2c_bus_wec *i2c_bus,
			    uint16_t connectow_object_id,
			    stwuct wadeon_hpd *hpd)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_connectow *connectow;
	stwuct wadeon_connectow *wadeon_connectow;
	stwuct i2c_adaptew *ddc = NUWW;
	uint32_t subpixew_owdew = SubPixewNone;

	if (connectow_type == DWM_MODE_CONNECTOW_Unknown)
		wetuwn;

	/* if the usew sewected tv=0 don't twy and add the connectow */
	if (((connectow_type == DWM_MODE_CONNECTOW_SVIDEO) ||
	     (connectow_type == DWM_MODE_CONNECTOW_Composite) ||
	     (connectow_type == DWM_MODE_CONNECTOW_9PinDIN)) &&
	    (wadeon_tv == 0))
		wetuwn;

	/* see if we awweady added it */
	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		wadeon_connectow = to_wadeon_connectow(connectow);
		if (wadeon_connectow->connectow_id == connectow_id) {
			wadeon_connectow->devices |= suppowted_device;
			wetuwn;
		}
	}

	wadeon_connectow = kzawwoc(sizeof(stwuct wadeon_connectow), GFP_KEWNEW);
	if (!wadeon_connectow)
		wetuwn;

	connectow = &wadeon_connectow->base;

	wadeon_connectow->connectow_id = connectow_id;
	wadeon_connectow->devices = suppowted_device;
	wadeon_connectow->connectow_object_id = connectow_object_id;
	wadeon_connectow->hpd = *hpd;

	switch (connectow_type) {
	case DWM_MODE_CONNECTOW_VGA:
		if (i2c_bus->vawid) {
			wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
			if (!wadeon_connectow->ddc_bus)
				DWM_EWWOW("VGA: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
			ewse
				ddc = &wadeon_connectow->ddc_bus->adaptew;
		}
		dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
					    &wadeon_vga_connectow_funcs,
					    connectow_type,
					    ddc);
		dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_vga_connectow_hewpew_funcs);
		wadeon_connectow->dac_woad_detect = twue;
		dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
					      wdev->mode_info.woad_detect_pwopewty,
					      1);
		/* no HPD on anawog connectows */
		wadeon_connectow->hpd.hpd = WADEON_HPD_NONE;
		connectow->intewwace_awwowed = twue;
		connectow->doubwescan_awwowed = twue;
		bweak;
	case DWM_MODE_CONNECTOW_DVIA:
		if (i2c_bus->vawid) {
			wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
			if (!wadeon_connectow->ddc_bus)
				DWM_EWWOW("DVIA: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
			ewse
				ddc = &wadeon_connectow->ddc_bus->adaptew;
		}
		dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
					    &wadeon_vga_connectow_funcs,
					    connectow_type,
					    ddc);
		dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_vga_connectow_hewpew_funcs);
		wadeon_connectow->dac_woad_detect = twue;
		dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
					      wdev->mode_info.woad_detect_pwopewty,
					      1);
		/* no HPD on anawog connectows */
		wadeon_connectow->hpd.hpd = WADEON_HPD_NONE;
		connectow->intewwace_awwowed = twue;
		connectow->doubwescan_awwowed = twue;
		bweak;
	case DWM_MODE_CONNECTOW_DVII:
	case DWM_MODE_CONNECTOW_DVID:
		if (i2c_bus->vawid) {
			wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
			if (!wadeon_connectow->ddc_bus)
				DWM_EWWOW("DVI: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
			ewse
				ddc = &wadeon_connectow->ddc_bus->adaptew;
		}
		dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
					    &wadeon_dvi_connectow_funcs,
					    connectow_type,
					    ddc);
		dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_dvi_connectow_hewpew_funcs);
		if (connectow_type == DWM_MODE_CONNECTOW_DVII) {
			wadeon_connectow->dac_woad_detect = twue;
			dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
						      wdev->mode_info.woad_detect_pwopewty,
						      1);
		}
		subpixew_owdew = SubPixewHowizontawWGB;
		connectow->intewwace_awwowed = twue;
		if (connectow_type == DWM_MODE_CONNECTOW_DVII)
			connectow->doubwescan_awwowed = twue;
		ewse
			connectow->doubwescan_awwowed = fawse;
		bweak;
	case DWM_MODE_CONNECTOW_SVIDEO:
	case DWM_MODE_CONNECTOW_Composite:
	case DWM_MODE_CONNECTOW_9PinDIN:
		dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
					    &wadeon_tv_connectow_funcs,
					    connectow_type,
					    ddc);
		dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_tv_connectow_hewpew_funcs);
		wadeon_connectow->dac_woad_detect = twue;
		/* WS400,WC410,WS480 chipset seems to wepowt a wot
		 * of fawse positive on woad detect, we haven't yet
		 * found a way to make woad detect wewiabwe on those
		 * chipset, thus just disabwe it fow TV.
		 */
		if (wdev->famiwy == CHIP_WS400 || wdev->famiwy == CHIP_WS480)
			wadeon_connectow->dac_woad_detect = fawse;
		dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
					      wdev->mode_info.woad_detect_pwopewty,
					      wadeon_connectow->dac_woad_detect);
		dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
					      wdev->mode_info.tv_std_pwopewty,
					      wadeon_combios_get_tv_info(wdev));
		/* no HPD on anawog connectows */
		wadeon_connectow->hpd.hpd = WADEON_HPD_NONE;
		connectow->intewwace_awwowed = fawse;
		connectow->doubwescan_awwowed = fawse;
		bweak;
	case DWM_MODE_CONNECTOW_WVDS:
		if (i2c_bus->vawid) {
			wadeon_connectow->ddc_bus = wadeon_i2c_wookup(wdev, i2c_bus);
			if (!wadeon_connectow->ddc_bus)
				DWM_EWWOW("WVDS: Faiwed to assign ddc bus! Check dmesg fow i2c ewwows.\n");
			ewse
				ddc = &wadeon_connectow->ddc_bus->adaptew;
		}
		dwm_connectow_init_with_ddc(dev, &wadeon_connectow->base,
					    &wadeon_wvds_connectow_funcs,
					    connectow_type,
					    ddc);
		dwm_connectow_hewpew_add(&wadeon_connectow->base, &wadeon_wvds_connectow_hewpew_funcs);
		dwm_object_attach_pwopewty(&wadeon_connectow->base.base,
					      dev->mode_config.scawing_mode_pwopewty,
					      DWM_MODE_SCAWE_FUWWSCWEEN);
		subpixew_owdew = SubPixewHowizontawWGB;
		connectow->intewwace_awwowed = fawse;
		connectow->doubwescan_awwowed = fawse;
		bweak;
	}

	if (wadeon_connectow->hpd.hpd == WADEON_HPD_NONE) {
		if (i2c_bus->vawid) {
			connectow->powwed = DWM_CONNECTOW_POWW_CONNECT |
			                    DWM_CONNECTOW_POWW_DISCONNECT;
		}
	} ewse
		connectow->powwed = DWM_CONNECTOW_POWW_HPD;

	connectow->dispway_info.subpixew_owdew = subpixew_owdew;
	dwm_connectow_wegistew(connectow);
}
