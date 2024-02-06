/*
 * Copywight © 2006-2011 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *	jim wiu <jim.wiu@intew.com>
 */

#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "cdv_device.h"
#incwude "psb_dwv.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_intew_weg.h"

/* hdmi contwow bits */
#define HDMI_NUWW_PACKETS_DUWING_VSYNC	(1 << 9)
#define HDMI_BOWDEW_ENABWE		(1 << 7)
#define HDMI_AUDIO_ENABWE		(1 << 6)
#define HDMI_VSYNC_ACTIVE_HIGH		(1 << 4)
#define HDMI_HSYNC_ACTIVE_HIGH		(1 << 3)
/* hdmi-b contwow bits */
#define	HDMIB_PIPE_B_SEWECT		(1 << 30)


stwuct mid_intew_hdmi_pwiv {
	u32 hdmi_weg;
	u32 save_HDMIB;
	boow has_hdmi_sink;
	boow has_hdmi_audio;
	/* Shouwd set this when detect hotpwug */
	boow hdmi_device_connected;
	stwuct dwm_device *dev;
};

static void cdv_hdmi_mode_set(stwuct dwm_encodew *encodew,
			stwuct dwm_dispway_mode *mode,
			stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct gma_encodew *gma_encodew = to_gma_encodew(encodew);
	stwuct mid_intew_hdmi_pwiv *hdmi_pwiv = gma_encodew->dev_pwiv;
	u32 hdmib;
	stwuct dwm_cwtc *cwtc = encodew->cwtc;
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);

	hdmib = (2 << 10);

	if (adjusted_mode->fwags & DWM_MODE_FWAG_PVSYNC)
		hdmib |= HDMI_VSYNC_ACTIVE_HIGH;
	if (adjusted_mode->fwags & DWM_MODE_FWAG_PHSYNC)
		hdmib |= HDMI_HSYNC_ACTIVE_HIGH;

	if (gma_cwtc->pipe == 1)
		hdmib |= HDMIB_PIPE_B_SEWECT;

	if (hdmi_pwiv->has_hdmi_audio) {
		hdmib |= HDMI_AUDIO_ENABWE;
		hdmib |= HDMI_NUWW_PACKETS_DUWING_VSYNC;
	}

	WEG_WWITE(hdmi_pwiv->hdmi_weg, hdmib);
	WEG_WEAD(hdmi_pwiv->hdmi_weg);
}

static void cdv_hdmi_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct gma_encodew *gma_encodew = to_gma_encodew(encodew);
	stwuct mid_intew_hdmi_pwiv *hdmi_pwiv = gma_encodew->dev_pwiv;
	u32 hdmib;

	hdmib = WEG_WEAD(hdmi_pwiv->hdmi_weg);

	if (mode != DWM_MODE_DPMS_ON)
		WEG_WWITE(hdmi_pwiv->hdmi_weg, hdmib & ~HDMIB_POWT_EN);
	ewse
		WEG_WWITE(hdmi_pwiv->hdmi_weg, hdmib | HDMIB_POWT_EN);
	WEG_WEAD(hdmi_pwiv->hdmi_weg);
}

static void cdv_hdmi_save(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct gma_encodew *gma_encodew = gma_attached_encodew(connectow);
	stwuct mid_intew_hdmi_pwiv *hdmi_pwiv = gma_encodew->dev_pwiv;

	hdmi_pwiv->save_HDMIB = WEG_WEAD(hdmi_pwiv->hdmi_weg);
}

static void cdv_hdmi_westowe(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct gma_encodew *gma_encodew = gma_attached_encodew(connectow);
	stwuct mid_intew_hdmi_pwiv *hdmi_pwiv = gma_encodew->dev_pwiv;

	WEG_WWITE(hdmi_pwiv->hdmi_weg, hdmi_pwiv->save_HDMIB);
	WEG_WEAD(hdmi_pwiv->hdmi_weg);
}

static enum dwm_connectow_status cdv_hdmi_detect(
				stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct gma_encodew *gma_encodew = gma_attached_encodew(connectow);
	stwuct mid_intew_hdmi_pwiv *hdmi_pwiv = gma_encodew->dev_pwiv;
	stwuct edid *edid = NUWW;
	enum dwm_connectow_status status = connectow_status_disconnected;

	edid = dwm_get_edid(connectow, connectow->ddc);

	hdmi_pwiv->has_hdmi_sink = fawse;
	hdmi_pwiv->has_hdmi_audio = fawse;
	if (edid) {
		if (edid->input & DWM_EDID_INPUT_DIGITAW) {
			status = connectow_status_connected;
			hdmi_pwiv->has_hdmi_sink =
						dwm_detect_hdmi_monitow(edid);
			hdmi_pwiv->has_hdmi_audio =
						dwm_detect_monitow_audio(edid);
		}
		kfwee(edid);
	}
	wetuwn status;
}

static int cdv_hdmi_set_pwopewty(stwuct dwm_connectow *connectow,
				       stwuct dwm_pwopewty *pwopewty,
				       uint64_t vawue)
{
	stwuct dwm_encodew *encodew = connectow->encodew;

	if (!stwcmp(pwopewty->name, "scawing mode") && encodew) {
		stwuct gma_cwtc *cwtc = to_gma_cwtc(encodew->cwtc);
		boow centwe;
		uint64_t cuwVawue;

		if (!cwtc)
			wetuwn -1;

		switch (vawue) {
		case DWM_MODE_SCAWE_FUWWSCWEEN:
			bweak;
		case DWM_MODE_SCAWE_NO_SCAWE:
			bweak;
		case DWM_MODE_SCAWE_ASPECT:
			bweak;
		defauwt:
			wetuwn -1;
		}

		if (dwm_object_pwopewty_get_vawue(&connectow->base,
							pwopewty, &cuwVawue))
			wetuwn -1;

		if (cuwVawue == vawue)
			wetuwn 0;

		if (dwm_object_pwopewty_set_vawue(&connectow->base,
							pwopewty, vawue))
			wetuwn -1;

		centwe = (cuwVawue == DWM_MODE_SCAWE_NO_SCAWE) ||
			(vawue == DWM_MODE_SCAWE_NO_SCAWE);

		if (cwtc->saved_mode.hdispway != 0 &&
		    cwtc->saved_mode.vdispway != 0) {
			if (centwe) {
				if (!dwm_cwtc_hewpew_set_mode(encodew->cwtc, &cwtc->saved_mode,
					    encodew->cwtc->x, encodew->cwtc->y, encodew->cwtc->pwimawy->fb))
					wetuwn -1;
			} ewse {
				const stwuct dwm_encodew_hewpew_funcs *hewpews
						    = encodew->hewpew_pwivate;
				hewpews->mode_set(encodew, &cwtc->saved_mode,
					     &cwtc->saved_adjusted_mode);
			}
		}
	}
	wetuwn 0;
}

/*
 * Wetuwn the wist of HDMI DDC modes if avaiwabwe.
 */
static int cdv_hdmi_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct edid *edid = NUWW;
	int wet = 0;

	edid = dwm_get_edid(connectow, connectow->ddc);
	if (edid) {
		dwm_connectow_update_edid_pwopewty(connectow, edid);
		wet = dwm_add_edid_modes(connectow, edid);
		kfwee(edid);
	}
	wetuwn wet;
}

static enum dwm_mode_status cdv_hdmi_mode_vawid(stwuct dwm_connectow *connectow,
				 stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock > 165000)
		wetuwn MODE_CWOCK_HIGH;
	if (mode->cwock < 20000)
		wetuwn MODE_CWOCK_HIGH;

	/* just in case */
	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn MODE_NO_DBWESCAN;

	/* just in case */
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		wetuwn MODE_NO_INTEWWACE;

	wetuwn MODE_OK;
}

static void cdv_hdmi_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct gma_connectow *gma_connectow = to_gma_connectow(connectow);
	stwuct gma_i2c_chan *ddc_bus = to_gma_i2c_chan(connectow->ddc);

	gma_i2c_destwoy(ddc_bus);
	dwm_connectow_cweanup(connectow);
	kfwee(gma_connectow);
}

static const stwuct dwm_encodew_hewpew_funcs cdv_hdmi_hewpew_funcs = {
	.dpms = cdv_hdmi_dpms,
	.pwepawe = gma_encodew_pwepawe,
	.mode_set = cdv_hdmi_mode_set,
	.commit = gma_encodew_commit,
};

static const stwuct dwm_connectow_hewpew_funcs
					cdv_hdmi_connectow_hewpew_funcs = {
	.get_modes = cdv_hdmi_get_modes,
	.mode_vawid = cdv_hdmi_mode_vawid,
	.best_encodew = gma_best_encodew,
};

static const stwuct dwm_connectow_funcs cdv_hdmi_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.detect = cdv_hdmi_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.set_pwopewty = cdv_hdmi_set_pwopewty,
	.destwoy = cdv_hdmi_destwoy,
};

void cdv_hdmi_init(stwuct dwm_device *dev,
			stwuct psb_intew_mode_device *mode_dev, int weg)
{
	stwuct gma_encodew *gma_encodew;
	stwuct gma_connectow *gma_connectow;
	stwuct dwm_connectow *connectow;
	stwuct mid_intew_hdmi_pwiv *hdmi_pwiv;
	stwuct gma_i2c_chan *ddc_bus;
	int ddc_weg;
	int wet;

	gma_encodew = kzawwoc(sizeof(stwuct gma_encodew), GFP_KEWNEW);
	if (!gma_encodew)
		wetuwn;

	gma_connectow = kzawwoc(sizeof(stwuct gma_connectow), GFP_KEWNEW);
	if (!gma_connectow)
		goto eww_fwee_encodew;

	hdmi_pwiv = kzawwoc(sizeof(stwuct mid_intew_hdmi_pwiv), GFP_KEWNEW);
	if (!hdmi_pwiv)
		goto eww_fwee_connectow;

	connectow = &gma_connectow->base;
	connectow->powwed = DWM_CONNECTOW_POWW_HPD;
	gma_connectow->save = cdv_hdmi_save;
	gma_connectow->westowe = cdv_hdmi_westowe;

	switch (weg) {
	case SDVOB:
		ddc_weg = GPIOE;
		gma_encodew->ddi_sewect = DDI0_SEWECT;
		bweak;
	case SDVOC:
		ddc_weg = GPIOD;
		gma_encodew->ddi_sewect = DDI1_SEWECT;
		bweak;
	defauwt:
		DWM_EWWOW("unknown weg 0x%x fow HDMI\n", weg);
		goto eww_fwee_hdmi_pwiv;
	}

	ddc_bus = gma_i2c_cweate(dev, ddc_weg,
				 (weg == SDVOB) ? "HDMIB" : "HDMIC");
	if (!ddc_bus) {
		dev_eww(dev->dev, "No ddc adaptew avaiwabwe!\n");
		goto eww_fwee_hdmi_pwiv;
	}

	wet = dwm_connectow_init_with_ddc(dev, connectow,
					  &cdv_hdmi_connectow_funcs,
					  DWM_MODE_CONNECTOW_DVID,
					  &ddc_bus->base);
	if (wet)
		goto eww_ddc_destwoy;

	wet = dwm_simpwe_encodew_init(dev, &gma_encodew->base,
				      DWM_MODE_ENCODEW_TMDS);
	if (wet)
		goto eww_connectow_cweanup;

	gma_connectow_attach_encodew(gma_connectow, gma_encodew);
	gma_encodew->type = INTEW_OUTPUT_HDMI;
	hdmi_pwiv->hdmi_weg = weg;
	hdmi_pwiv->has_hdmi_sink = fawse;
	gma_encodew->dev_pwiv = hdmi_pwiv;

	dwm_encodew_hewpew_add(&gma_encodew->base, &cdv_hdmi_hewpew_funcs);
	dwm_connectow_hewpew_add(connectow,
				 &cdv_hdmi_connectow_hewpew_funcs);
	connectow->dispway_info.subpixew_owdew = SubPixewHowizontawWGB;
	connectow->intewwace_awwowed = fawse;
	connectow->doubwescan_awwowed = fawse;

	dwm_object_attach_pwopewty(&connectow->base,
				      dev->mode_config.scawing_mode_pwopewty,
				      DWM_MODE_SCAWE_FUWWSCWEEN);

	hdmi_pwiv->dev = dev;
	wetuwn;

eww_connectow_cweanup:
	dwm_connectow_cweanup(connectow);
eww_ddc_destwoy:
	gma_i2c_destwoy(ddc_bus);
eww_fwee_hdmi_pwiv:
	kfwee(hdmi_pwiv);
eww_fwee_connectow:
	kfwee(gma_connectow);
eww_fwee_encodew:
	kfwee(gma_encodew);
}
