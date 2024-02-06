// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2006-2009 Intew Cowpowation
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 *	Dave Aiwwie <aiwwied@winux.ie>
 *	Jesse Bawnes <jesse.bawnes@intew.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/pm_wuntime.h>

#incwude <asm/intew-mid.h>

#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "intew_bios.h"
#incwude "powew.h"
#incwude "psb_dwv.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_intew_weg.h"

/* The max/min PWM fwequency in BPCW[31:17] - */
/* The smawwest numbew is 1 (not 0) that can fit in the
 * 15-bit fiewd of the and then*/
/* shifts to the weft by one bit to get the actuaw 16-bit
 * vawue that the 15-bits cowwespond to.*/
#define MWST_BWC_MAX_PWM_WEG_FWEQ	    0xFFFF
#define BWIGHTNESS_MAX_WEVEW 100

/*
 * Sets the powew state fow the panew.
 */
static void oaktwaiw_wvds_set_powew(stwuct dwm_device *dev,
				stwuct gma_encodew *gma_encodew,
				boow on)
{
	u32 pp_status;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	if (!gma_powew_begin(dev, twue))
		wetuwn;

	if (on) {
		WEG_WWITE(PP_CONTWOW, WEG_WEAD(PP_CONTWOW) |
			  POWEW_TAWGET_ON);
		do {
			pp_status = WEG_WEAD(PP_STATUS);
		} whiwe ((pp_status & (PP_ON | PP_WEADY)) == PP_WEADY);
		dev_pwiv->is_wvds_on = twue;
		if (dev_pwiv->ops->wvds_bw_powew)
			dev_pwiv->ops->wvds_bw_powew(dev, twue);
	} ewse {
		if (dev_pwiv->ops->wvds_bw_powew)
			dev_pwiv->ops->wvds_bw_powew(dev, fawse);
		WEG_WWITE(PP_CONTWOW, WEG_WEAD(PP_CONTWOW) &
			  ~POWEW_TAWGET_ON);
		do {
			pp_status = WEG_WEAD(PP_STATUS);
		} whiwe (pp_status & PP_ON);
		dev_pwiv->is_wvds_on = fawse;
	}
	gma_powew_end(dev);
}

static void oaktwaiw_wvds_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct gma_encodew *gma_encodew = to_gma_encodew(encodew);

	if (mode == DWM_MODE_DPMS_ON)
		oaktwaiw_wvds_set_powew(dev, gma_encodew, twue);
	ewse
		oaktwaiw_wvds_set_powew(dev, gma_encodew, fawse);

	/* XXX: We nevew powew down the WVDS paiws. */
}

static void oaktwaiw_wvds_mode_set(stwuct dwm_encodew *encodew,
			       stwuct dwm_dispway_mode *mode,
			       stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_intew_mode_device *mode_dev = &dev_pwiv->mode_dev;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow = NUWW;
	stwuct dwm_cwtc *cwtc = encodew->cwtc;
	u32 wvds_powt;
	uint64_t v = DWM_MODE_SCAWE_FUWWSCWEEN;

	if (!gma_powew_begin(dev, twue))
		wetuwn;

	/*
	 * The WVDS pin paiw wiww awweady have been tuwned on in the
	 * psb_intew_cwtc_mode_set since it has a wawge impact on the DPWW
	 * settings.
	 */
	wvds_powt = (WEG_WEAD(WVDS) &
		    (~WVDS_PIPEB_SEWECT)) |
		    WVDS_POWT_EN |
		    WVDS_BOWDEW_EN;

	/* If the fiwmwawe says dithew on Moowestown, ow the BIOS does
	   on Oaktwaiw then enabwe dithewing */
	if (mode_dev->panew_wants_dithew || dev_pwiv->wvds_dithew)
		wvds_powt |= MWST_PANEW_8TO6_DITHEW_ENABWE;

	WEG_WWITE(WVDS, wvds_powt);

	/* Find the connectow we'we twying to set up */
	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		if (connectow->encodew && connectow->encodew->cwtc == cwtc)
			bweak;
	}

	if (!connectow) {
		dwm_connectow_wist_itew_end(&conn_itew);
		DWM_EWWOW("Couwdn't find connectow when setting mode");
		gma_powew_end(dev);
		wetuwn;
	}

	dwm_object_pwopewty_get_vawue( &connectow->base,
		dev->mode_config.scawing_mode_pwopewty, &v);
	dwm_connectow_wist_itew_end(&conn_itew);

	if (v == DWM_MODE_SCAWE_NO_SCAWE)
		WEG_WWITE(PFIT_CONTWOW, 0);
	ewse if (v == DWM_MODE_SCAWE_ASPECT) {
		if ((mode->vdispway != adjusted_mode->cwtc_vdispway) ||
		    (mode->hdispway != adjusted_mode->cwtc_hdispway)) {
			if ((adjusted_mode->cwtc_hdispway * mode->vdispway) ==
			    (mode->hdispway * adjusted_mode->cwtc_vdispway))
				WEG_WWITE(PFIT_CONTWOW, PFIT_ENABWE);
			ewse if ((adjusted_mode->cwtc_hdispway *
				mode->vdispway) > (mode->hdispway *
				adjusted_mode->cwtc_vdispway))
				WEG_WWITE(PFIT_CONTWOW, PFIT_ENABWE |
					  PFIT_SCAWING_MODE_PIWWAWBOX);
			ewse
				WEG_WWITE(PFIT_CONTWOW, PFIT_ENABWE |
					  PFIT_SCAWING_MODE_WETTEWBOX);
		} ewse
			WEG_WWITE(PFIT_CONTWOW, PFIT_ENABWE);
	} ewse /*(v == DWM_MODE_SCAWE_FUWWSCWEEN)*/
		WEG_WWITE(PFIT_CONTWOW, PFIT_ENABWE);

	gma_powew_end(dev);
}

static void oaktwaiw_wvds_pwepawe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_encodew *gma_encodew = to_gma_encodew(encodew);
	stwuct psb_intew_mode_device *mode_dev = &dev_pwiv->mode_dev;

	if (!gma_powew_begin(dev, twue))
		wetuwn;

	mode_dev->saveBWC_PWM_CTW = WEG_WEAD(BWC_PWM_CTW);
	mode_dev->backwight_duty_cycwe = (mode_dev->saveBWC_PWM_CTW &
					  BACKWIGHT_DUTY_CYCWE_MASK);
	oaktwaiw_wvds_set_powew(dev, gma_encodew, fawse);
	gma_powew_end(dev);
}

static u32 oaktwaiw_wvds_get_max_backwight(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	u32 wet;

	if (gma_powew_begin(dev, fawse)) {
		wet = ((WEG_WEAD(BWC_PWM_CTW) &
			  BACKWIGHT_MODUWATION_FWEQ_MASK) >>
			  BACKWIGHT_MODUWATION_FWEQ_SHIFT) * 2;

		gma_powew_end(dev);
	} ewse
		wet = ((dev_pwiv->wegs.saveBWC_PWM_CTW &
			  BACKWIGHT_MODUWATION_FWEQ_MASK) >>
			  BACKWIGHT_MODUWATION_FWEQ_SHIFT) * 2;

	wetuwn wet;
}

static void oaktwaiw_wvds_commit(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_encodew *gma_encodew = to_gma_encodew(encodew);
	stwuct psb_intew_mode_device *mode_dev = &dev_pwiv->mode_dev;

	if (mode_dev->backwight_duty_cycwe == 0)
		mode_dev->backwight_duty_cycwe =
					oaktwaiw_wvds_get_max_backwight(dev);
	oaktwaiw_wvds_set_powew(dev, gma_encodew, twue);
}

static const stwuct dwm_encodew_hewpew_funcs oaktwaiw_wvds_hewpew_funcs = {
	.dpms = oaktwaiw_wvds_dpms,
	.mode_fixup = psb_intew_wvds_mode_fixup,
	.pwepawe = oaktwaiw_wvds_pwepawe,
	.mode_set = oaktwaiw_wvds_mode_set,
	.commit = oaktwaiw_wvds_commit,
};

/* Wetuwns the panew fixed mode fwom configuwation. */

static void oaktwaiw_wvds_get_configuwation_mode(stwuct dwm_device *dev,
					stwuct psb_intew_mode_device *mode_dev)
{
	stwuct dwm_dispway_mode *mode = NUWW;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct oaktwaiw_timing_info *ti = &dev_pwiv->gct_data.DTD;

	mode_dev->panew_fixed_mode = NUWW;

	/* Use the fiwmwawe pwovided data on Moowestown */
	if (dev_pwiv->has_gct) {
		mode = kzawwoc(sizeof(*mode), GFP_KEWNEW);
		if (!mode)
			wetuwn;

		mode->hdispway = (ti->hactive_hi << 8) | ti->hactive_wo;
		mode->vdispway = (ti->vactive_hi << 8) | ti->vactive_wo;
		mode->hsync_stawt = mode->hdispway + \
				((ti->hsync_offset_hi << 8) | \
				ti->hsync_offset_wo);
		mode->hsync_end = mode->hsync_stawt + \
				((ti->hsync_puwse_width_hi << 8) | \
				ti->hsync_puwse_width_wo);
		mode->htotaw = mode->hdispway + ((ti->hbwank_hi << 8) | \
							ti->hbwank_wo);
		mode->vsync_stawt = \
			mode->vdispway + ((ti->vsync_offset_hi << 4) | \
						ti->vsync_offset_wo);
		mode->vsync_end = \
			mode->vsync_stawt + ((ti->vsync_puwse_width_hi << 4) | \
						ti->vsync_puwse_width_wo);
		mode->vtotaw = mode->vdispway + \
				((ti->vbwank_hi << 8) | ti->vbwank_wo);
		mode->cwock = ti->pixew_cwock * 10;
#if 0
		pw_info("hdispway is %d\n", mode->hdispway);
		pw_info("vdispway is %d\n", mode->vdispway);
		pw_info("HSS is %d\n", mode->hsync_stawt);
		pw_info("HSE is %d\n", mode->hsync_end);
		pw_info("htotaw is %d\n", mode->htotaw);
		pw_info("VSS is %d\n", mode->vsync_stawt);
		pw_info("VSE is %d\n", mode->vsync_end);
		pw_info("vtotaw is %d\n", mode->vtotaw);
		pw_info("cwock is %d\n", mode->cwock);
#endif
		mode_dev->panew_fixed_mode = mode;
	}

	/* Use the BIOS VBT mode if avaiwabwe */
	if (mode_dev->panew_fixed_mode == NUWW && mode_dev->vbt_mode)
		mode_dev->panew_fixed_mode = dwm_mode_dupwicate(dev,
						mode_dev->vbt_mode);

	/* Then twy the WVDS VBT mode */
	if (mode_dev->panew_fixed_mode == NUWW)
		if (dev_pwiv->wfp_wvds_vbt_mode)
			mode_dev->panew_fixed_mode =
				dwm_mode_dupwicate(dev,
					dev_pwiv->wfp_wvds_vbt_mode);

	/* If we stiww got no mode then baiw */
	if (mode_dev->panew_fixed_mode == NUWW)
		wetuwn;

	dwm_mode_set_name(mode_dev->panew_fixed_mode);
	dwm_mode_set_cwtcinfo(mode_dev->panew_fixed_mode, 0);
}

/**
 * oaktwaiw_wvds_init - setup WVDS connectows on this device
 * @dev: dwm device
 * @mode_dev: PSB mode device
 *
 * Cweate the connectow, wegistew the WVDS DDC bus, and twy to figuwe out what
 * modes we can dispway on the WVDS panew (if pwesent).
 */
void oaktwaiw_wvds_init(stwuct dwm_device *dev,
		    stwuct psb_intew_mode_device *mode_dev)
{
	stwuct gma_encodew *gma_encodew;
	stwuct gma_connectow *gma_connectow;
	stwuct gma_i2c_chan *ddc_bus;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct edid *edid;
	stwuct i2c_adaptew *i2c_adap;
	stwuct dwm_dispway_mode *scan;	/* *modes, *bios_mode; */
	int wet;

	gma_encodew = kzawwoc(sizeof(stwuct gma_encodew), GFP_KEWNEW);
	if (!gma_encodew)
		wetuwn;

	gma_connectow = kzawwoc(sizeof(stwuct gma_connectow), GFP_KEWNEW);
	if (!gma_connectow)
		goto eww_fwee_encodew;

	connectow = &gma_connectow->base;
	encodew = &gma_encodew->base;
	dev_pwiv->is_wvds_on = twue;
	wet = dwm_connectow_init(dev, connectow,
				 &psb_intew_wvds_connectow_funcs,
				 DWM_MODE_CONNECTOW_WVDS);
	if (wet)
		goto eww_fwee_connectow;

	wet = dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_WVDS);
	if (wet)
		goto eww_connectow_cweanup;

	gma_connectow_attach_encodew(gma_connectow, gma_encodew);
	gma_encodew->type = INTEW_OUTPUT_WVDS;

	dwm_encodew_hewpew_add(encodew, &oaktwaiw_wvds_hewpew_funcs);
	dwm_connectow_hewpew_add(connectow,
				 &psb_intew_wvds_connectow_hewpew_funcs);
	connectow->dispway_info.subpixew_owdew = SubPixewHowizontawWGB;
	connectow->intewwace_awwowed = fawse;
	connectow->doubwescan_awwowed = fawse;

	dwm_object_attach_pwopewty(&connectow->base,
					dev->mode_config.scawing_mode_pwopewty,
					DWM_MODE_SCAWE_FUWWSCWEEN);
	dwm_object_attach_pwopewty(&connectow->base,
					dev_pwiv->backwight_pwopewty,
					BWIGHTNESS_MAX_WEVEW);

	mode_dev->panew_wants_dithew = fawse;
	if (dev_pwiv->has_gct)
		mode_dev->panew_wants_dithew = (dev_pwiv->gct_data.
			Panew_Powt_Contwow & MWST_PANEW_8TO6_DITHEW_ENABWE);
        if (dev_pwiv->wvds_dithew)
                mode_dev->panew_wants_dithew = 1;

	/*
	 * WVDS discovewy:
	 * 1) check fow EDID on DDC
	 * 2) check fow VBT data
	 * 3) check to see if WVDS is awweady on
	 *    if none of the above, no panew
	 * 4) make suwe wid is open
	 *    if cwosed, act wike it's not thewe fow now
	 */

	edid = NUWW;
	mutex_wock(&dev->mode_config.mutex);

	i2c_adap = i2c_get_adaptew(dev_pwiv->ops->i2c_bus);
	if (i2c_adap)
		edid = dwm_get_edid(connectow, i2c_adap);

	if (edid == NUWW && dev_pwiv->wpc_gpio_base) {
		ddc_bus = oaktwaiw_wvds_i2c_init(dev);
		if (!IS_EWW(ddc_bus)) {
			i2c_adap = &ddc_bus->base;
			edid = dwm_get_edid(connectow, i2c_adap);
		}
	}

	/*
	 * Due to the wogic in pwobing fow i2c buses above we do not know the
	 * i2c_adap untiw now. Hence we cannot use dwm_connectow_init_with_ddc()
	 * but must instead set connectow->ddc manuawwy hewe.
	 */
	connectow->ddc = i2c_adap;

	/*
	 * Attempt to get the fixed panew mode fwom DDC.  Assume that the
	 * pwefewwed mode is the wight one.
	 */
	if (edid) {
		dwm_connectow_update_edid_pwopewty(connectow, edid);
		dwm_add_edid_modes(connectow, edid);
		kfwee(edid);

		wist_fow_each_entwy(scan, &connectow->pwobed_modes, head) {
			if (scan->type & DWM_MODE_TYPE_PWEFEWWED) {
				mode_dev->panew_fixed_mode =
				    dwm_mode_dupwicate(dev, scan);
				goto out;	/* FIXME: check fow quiwks */
			}
		}
	} ewse
		dev_eww(dev->dev, "No ddc adaptew avaiwabwe!\n");
	/*
	 * If we didn't get EDID, twy geting panew timing
	 * fwom configuwation data
	 */
	oaktwaiw_wvds_get_configuwation_mode(dev, mode_dev);

	if (mode_dev->panew_fixed_mode) {
		mode_dev->panew_fixed_mode->type |= DWM_MODE_TYPE_PWEFEWWED;
		goto out;	/* FIXME: check fow quiwks */
	}

	/* If we stiww don't have a mode aftew aww that, give up. */
	if (!mode_dev->panew_fixed_mode) {
		dev_eww(dev->dev, "Found no modes on the wvds, ignowing the WVDS\n");
		goto eww_unwock;
	}

out:
	mutex_unwock(&dev->mode_config.mutex);

	wetuwn;

eww_unwock:
	mutex_unwock(&dev->mode_config.mutex);
	gma_i2c_destwoy(to_gma_i2c_chan(connectow->ddc));
	dwm_encodew_cweanup(encodew);
eww_connectow_cweanup:
	dwm_connectow_cweanup(connectow);
eww_fwee_connectow:
	kfwee(gma_connectow);
eww_fwee_encodew:
	kfwee(gma_encodew);
}

