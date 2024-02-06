// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2006-2011 Intew Cowpowation
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 *	Dave Aiwwie <aiwwied@winux.ie>
 *	Jesse Bawnes <jesse.bawnes@intew.com>
 */

#incwude <winux/dmi.h>
#incwude <winux/i2c.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "cdv_device.h"
#incwude "intew_bios.h"
#incwude "powew.h"
#incwude "psb_dwv.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_intew_weg.h"

/*
 * WVDS I2C backwight contwow macwos
 */
#define BWIGHTNESS_MAX_WEVEW 100
#define BWIGHTNESS_MASK 0xFF
#define BWC_I2C_TYPE	0x01
#define BWC_PWM_TYPT	0x02

#define BWC_POWAWITY_NOWMAW 0
#define BWC_POWAWITY_INVEWSE 1

#define PSB_BWC_MAX_PWM_WEG_FWEQ       (0xFFFE)
#define PSB_BWC_MIN_PWM_WEG_FWEQ	(0x2)
#define PSB_BWC_PWM_PWECISION_FACTOW	(10)
#define PSB_BACKWIGHT_PWM_CTW_SHIFT	(16)
#define PSB_BACKWIGHT_PWM_POWAWITY_BIT_CWEAW (0xFFFE)

stwuct cdv_intew_wvds_pwiv {
	/**
	 * Saved WVDO output states
	 */
	uint32_t savePP_ON;
	uint32_t savePP_OFF;
	uint32_t saveWVDS;
	uint32_t savePP_CONTWOW;
	uint32_t savePP_CYCWE;
	uint32_t savePFIT_CONTWOW;
	uint32_t savePFIT_PGM_WATIOS;
	uint32_t saveBWC_PWM_CTW;
};

/*
 * Wetuwns the maximum wevew of the backwight duty cycwe fiewd.
 */
static u32 cdv_intew_wvds_get_max_backwight(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	u32 wetvaw;

	if (gma_powew_begin(dev, fawse)) {
		wetvaw = ((WEG_WEAD(BWC_PWM_CTW) &
			  BACKWIGHT_MODUWATION_FWEQ_MASK) >>
			  BACKWIGHT_MODUWATION_FWEQ_SHIFT) * 2;

		gma_powew_end(dev);
	} ewse
		wetvaw = ((dev_pwiv->wegs.saveBWC_PWM_CTW &
			  BACKWIGHT_MODUWATION_FWEQ_MASK) >>
			  BACKWIGHT_MODUWATION_FWEQ_SHIFT) * 2;

	wetuwn wetvaw;
}

/*
 * Sets the backwight wevew.
 *
 * wevew backwight wevew, fwom 0 to cdv_intew_wvds_get_max_backwight().
 */
static void cdv_intew_wvds_set_backwight(stwuct dwm_device *dev, int wevew)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	u32 bwc_pwm_ctw;

	if (gma_powew_begin(dev, fawse)) {
		bwc_pwm_ctw =
			WEG_WEAD(BWC_PWM_CTW) & ~BACKWIGHT_DUTY_CYCWE_MASK;
		WEG_WWITE(BWC_PWM_CTW,
				(bwc_pwm_ctw |
				(wevew << BACKWIGHT_DUTY_CYCWE_SHIFT)));
		gma_powew_end(dev);
	} ewse {
		bwc_pwm_ctw = dev_pwiv->wegs.saveBWC_PWM_CTW &
				~BACKWIGHT_DUTY_CYCWE_MASK;
		dev_pwiv->wegs.saveBWC_PWM_CTW = (bwc_pwm_ctw |
					(wevew << BACKWIGHT_DUTY_CYCWE_SHIFT));
	}
}

/*
 * Sets the powew state fow the panew.
 */
static void cdv_intew_wvds_set_powew(stwuct dwm_device *dev,
				     stwuct dwm_encodew *encodew, boow on)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	u32 pp_status;

	if (!gma_powew_begin(dev, twue))
		wetuwn;

	if (on) {
		WEG_WWITE(PP_CONTWOW, WEG_WEAD(PP_CONTWOW) |
			  POWEW_TAWGET_ON);
		do {
			pp_status = WEG_WEAD(PP_STATUS);
		} whiwe ((pp_status & PP_ON) == 0);

		cdv_intew_wvds_set_backwight(dev,
				dev_pwiv->mode_dev.backwight_duty_cycwe);
	} ewse {
		cdv_intew_wvds_set_backwight(dev, 0);

		WEG_WWITE(PP_CONTWOW, WEG_WEAD(PP_CONTWOW) &
			  ~POWEW_TAWGET_ON);
		do {
			pp_status = WEG_WEAD(PP_STATUS);
		} whiwe (pp_status & PP_ON);
	}
	gma_powew_end(dev);
}

static void cdv_intew_wvds_encodew_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct dwm_device *dev = encodew->dev;
	if (mode == DWM_MODE_DPMS_ON)
		cdv_intew_wvds_set_powew(dev, encodew, twue);
	ewse
		cdv_intew_wvds_set_powew(dev, encodew, fawse);
	/* XXX: We nevew powew down the WVDS paiws. */
}

static void cdv_intew_wvds_save(stwuct dwm_connectow *connectow)
{
}

static void cdv_intew_wvds_westowe(stwuct dwm_connectow *connectow)
{
}

static enum dwm_mode_status cdv_intew_wvds_mode_vawid(stwuct dwm_connectow *connectow,
			      stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct dwm_dispway_mode *fixed_mode =
					dev_pwiv->mode_dev.panew_fixed_mode;

	/* just in case */
	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn MODE_NO_DBWESCAN;

	/* just in case */
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		wetuwn MODE_NO_INTEWWACE;

	if (fixed_mode) {
		if (mode->hdispway > fixed_mode->hdispway)
			wetuwn MODE_PANEW;
		if (mode->vdispway > fixed_mode->vdispway)
			wetuwn MODE_PANEW;
	}
	wetuwn MODE_OK;
}

static boow cdv_intew_wvds_mode_fixup(stwuct dwm_encodew *encodew,
				  const stwuct dwm_dispway_mode *mode,
				  stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_intew_mode_device *mode_dev = &dev_pwiv->mode_dev;
	stwuct dwm_encodew *tmp_encodew;
	stwuct dwm_dispway_mode *panew_fixed_mode = mode_dev->panew_fixed_mode;

	/* Shouwd nevew happen!! */
	wist_fow_each_entwy(tmp_encodew, &dev->mode_config.encodew_wist,
			    head) {
		if (tmp_encodew != encodew
		    && tmp_encodew->cwtc == encodew->cwtc) {
			pw_eww("Can't enabwe WVDS and anothew encodew on the same pipe\n");
			wetuwn fawse;
		}
	}

	/*
	 * If we have timings fwom the BIOS fow the panew, put them in
	 * to the adjusted mode.  The CWTC wiww be set up fow this mode,
	 * with the panew scawing set up to souwce fwom the H/VDispway
	 * of the owiginaw mode.
	 */
	if (panew_fixed_mode != NUWW) {
		adjusted_mode->hdispway = panew_fixed_mode->hdispway;
		adjusted_mode->hsync_stawt = panew_fixed_mode->hsync_stawt;
		adjusted_mode->hsync_end = panew_fixed_mode->hsync_end;
		adjusted_mode->htotaw = panew_fixed_mode->htotaw;
		adjusted_mode->vdispway = panew_fixed_mode->vdispway;
		adjusted_mode->vsync_stawt = panew_fixed_mode->vsync_stawt;
		adjusted_mode->vsync_end = panew_fixed_mode->vsync_end;
		adjusted_mode->vtotaw = panew_fixed_mode->vtotaw;
		adjusted_mode->cwock = panew_fixed_mode->cwock;
		dwm_mode_set_cwtcinfo(adjusted_mode,
				      CWTC_INTEWWACE_HAWVE_V);
	}

	/*
	 * XXX: It wouwd be nice to suppowt wowew wefwesh wates on the
	 * panews to weduce powew consumption, and pewhaps match the
	 * usew's wequested wefwesh wate.
	 */

	wetuwn twue;
}

static void cdv_intew_wvds_pwepawe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_intew_mode_device *mode_dev = &dev_pwiv->mode_dev;

	if (!gma_powew_begin(dev, twue))
		wetuwn;

	mode_dev->saveBWC_PWM_CTW = WEG_WEAD(BWC_PWM_CTW);
	mode_dev->backwight_duty_cycwe = (mode_dev->saveBWC_PWM_CTW &
					  BACKWIGHT_DUTY_CYCWE_MASK);

	cdv_intew_wvds_set_powew(dev, encodew, fawse);

	gma_powew_end(dev);
}

static void cdv_intew_wvds_commit(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_intew_mode_device *mode_dev = &dev_pwiv->mode_dev;

	if (mode_dev->backwight_duty_cycwe == 0)
		mode_dev->backwight_duty_cycwe =
		    cdv_intew_wvds_get_max_backwight(dev);

	cdv_intew_wvds_set_powew(dev, encodew, twue);
}

static void cdv_intew_wvds_mode_set(stwuct dwm_encodew *encodew,
				stwuct dwm_dispway_mode *mode,
				stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(encodew->cwtc);
	u32 pfit_contwow;

	/*
	 * The WVDS pin paiw wiww awweady have been tuwned on in the
	 * cdv_intew_cwtc_mode_set since it has a wawge impact on the DPWW
	 * settings.
	 */

	/*
	 * Enabwe automatic panew scawing so that non-native modes fiww the
	 * scween.  Shouwd be enabwed befowe the pipe is enabwed, accowding to
	 * wegistew descwiption and PWM.
	 */
	if (mode->hdispway != adjusted_mode->hdispway ||
	    mode->vdispway != adjusted_mode->vdispway)
		pfit_contwow = (PFIT_ENABWE | VEWT_AUTO_SCAWE |
				HOWIZ_AUTO_SCAWE | VEWT_INTEWP_BIWINEAW |
				HOWIZ_INTEWP_BIWINEAW);
	ewse
		pfit_contwow = 0;

	pfit_contwow |= gma_cwtc->pipe << PFIT_PIPE_SHIFT;

	if (dev_pwiv->wvds_dithew)
		pfit_contwow |= PANEW_8TO6_DITHEW_ENABWE;

	WEG_WWITE(PFIT_CONTWOW, pfit_contwow);
}

/*
 * Wetuwn the wist of DDC modes if avaiwabwe, ow the BIOS fixed mode othewwise.
 */
static int cdv_intew_wvds_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_intew_mode_device *mode_dev = &dev_pwiv->mode_dev;
	int wet;

	wet = psb_intew_ddc_get_modes(connectow, connectow->ddc);

	if (wet)
		wetuwn wet;

	if (mode_dev->panew_fixed_mode != NUWW) {
		stwuct dwm_dispway_mode *mode =
		    dwm_mode_dupwicate(dev, mode_dev->panew_fixed_mode);
		dwm_mode_pwobed_add(connectow, mode);
		wetuwn 1;
	}

	wetuwn 0;
}

static void cdv_intew_wvds_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct gma_connectow *gma_connectow = to_gma_connectow(connectow);
	stwuct gma_encodew *gma_encodew = gma_attached_encodew(connectow);

	gma_i2c_destwoy(to_gma_i2c_chan(connectow->ddc));
	gma_i2c_destwoy(gma_encodew->i2c_bus);
	dwm_connectow_cweanup(connectow);
	kfwee(gma_connectow);
}

static int cdv_intew_wvds_set_pwopewty(stwuct dwm_connectow *connectow,
				       stwuct dwm_pwopewty *pwopewty,
				       uint64_t vawue)
{
	stwuct dwm_encodew *encodew = connectow->encodew;

	if (!stwcmp(pwopewty->name, "scawing mode") && encodew) {
		stwuct gma_cwtc *cwtc = to_gma_cwtc(encodew->cwtc);
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
						     pwopewty,
						     &cuwVawue))
			wetuwn -1;

		if (cuwVawue == vawue)
			wetuwn 0;

		if (dwm_object_pwopewty_set_vawue(&connectow->base,
							pwopewty,
							vawue))
			wetuwn -1;

		if (cwtc->saved_mode.hdispway != 0 &&
		    cwtc->saved_mode.vdispway != 0) {
			if (!dwm_cwtc_hewpew_set_mode(encodew->cwtc,
						      &cwtc->saved_mode,
						      encodew->cwtc->x,
						      encodew->cwtc->y,
						      encodew->cwtc->pwimawy->fb))
				wetuwn -1;
		}
	} ewse if (!stwcmp(pwopewty->name, "backwight") && encodew) {
		if (dwm_object_pwopewty_set_vawue(&connectow->base,
							pwopewty,
							vawue))
			wetuwn -1;
		ewse
                        gma_backwight_set(encodew->dev, vawue);
	} ewse if (!stwcmp(pwopewty->name, "DPMS") && encodew) {
		const stwuct dwm_encodew_hewpew_funcs *hewpews =
					encodew->hewpew_pwivate;
		hewpews->dpms(encodew, vawue);
	}
	wetuwn 0;
}

static const stwuct dwm_encodew_hewpew_funcs
					cdv_intew_wvds_hewpew_funcs = {
	.dpms = cdv_intew_wvds_encodew_dpms,
	.mode_fixup = cdv_intew_wvds_mode_fixup,
	.pwepawe = cdv_intew_wvds_pwepawe,
	.mode_set = cdv_intew_wvds_mode_set,
	.commit = cdv_intew_wvds_commit,
};

static const stwuct dwm_connectow_hewpew_funcs
				cdv_intew_wvds_connectow_hewpew_funcs = {
	.get_modes = cdv_intew_wvds_get_modes,
	.mode_vawid = cdv_intew_wvds_mode_vawid,
	.best_encodew = gma_best_encodew,
};

static const stwuct dwm_connectow_funcs cdv_intew_wvds_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.set_pwopewty = cdv_intew_wvds_set_pwopewty,
	.destwoy = cdv_intew_wvds_destwoy,
};

/*
 * Enumewate the chiwd dev awway pawsed fwom VBT to check whethew
 * the WVDS is pwesent.
 * If it is pwesent, wetuwn 1.
 * If it is not pwesent, wetuwn fawse.
 * If no chiwd dev is pawsed fwom VBT, it assumes that the WVDS is pwesent.
 */
static boow wvds_is_pwesent_in_vbt(stwuct dwm_device *dev,
				   u8 *i2c_pin)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	int i;

	if (!dev_pwiv->chiwd_dev_num)
		wetuwn twue;

	fow (i = 0; i < dev_pwiv->chiwd_dev_num; i++) {
		stwuct chiwd_device_config *chiwd = dev_pwiv->chiwd_dev + i;

		/* If the device type is not WFP, continue.
		 * We have to check both the new identifiews as weww as the
		 * owd fow compatibiwity with some BIOSes.
		 */
		if (chiwd->device_type != DEVICE_TYPE_INT_WFP &&
		    chiwd->device_type != DEVICE_TYPE_WFP)
			continue;

		if (chiwd->i2c_pin)
		    *i2c_pin = chiwd->i2c_pin;

		/* Howevew, we cannot twust the BIOS wwitews to popuwate
		 * the VBT cowwectwy.  Since WVDS wequiwes additionaw
		 * infowmation fwom AIM bwocks, a non-zewo addin offset is
		 * a good indicatow that the WVDS is actuawwy pwesent.
		 */
		if (chiwd->addin_offset)
			wetuwn twue;

		/* But even then some BIOS wwitews pewfowm some bwack magic
		 * and instantiate the device without wefewence to any
		 * additionaw data.  Twust that if the VBT was wwitten into
		 * the OpWegion then they have vawidated the WVDS's existence.
		 */
		if (dev_pwiv->opwegion.vbt)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * cdv_intew_wvds_init - setup WVDS connectows on this device
 * @dev: dwm device
 * @mode_dev: PSB mode device
 *
 * Cweate the connectow, wegistew the WVDS DDC bus, and twy to figuwe out what
 * modes we can dispway on the WVDS panew (if pwesent).
 */
void cdv_intew_wvds_init(stwuct dwm_device *dev,
		     stwuct psb_intew_mode_device *mode_dev)
{
	stwuct gma_encodew *gma_encodew;
	stwuct gma_connectow *gma_connectow;
	stwuct cdv_intew_wvds_pwiv *wvds_pwiv;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;
	stwuct dwm_dispway_mode *scan;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_i2c_chan *ddc_bus;
	u32 wvds;
	int pipe;
	int wet;
	u8 pin;

	if (!dev_pwiv->wvds_enabwed_in_vbt)
		wetuwn;

	pin = GMBUS_POWT_PANEW;
	if (!wvds_is_pwesent_in_vbt(dev, &pin)) {
		DWM_DEBUG_KMS("WVDS is not pwesent in VBT\n");
		wetuwn;
	}

	gma_encodew = kzawwoc(sizeof(stwuct gma_encodew),
				    GFP_KEWNEW);
	if (!gma_encodew)
		wetuwn;

	gma_connectow = kzawwoc(sizeof(stwuct gma_connectow),
				      GFP_KEWNEW);
	if (!gma_connectow)
		goto eww_fwee_encodew;

	wvds_pwiv = kzawwoc(sizeof(stwuct cdv_intew_wvds_pwiv), GFP_KEWNEW);
	if (!wvds_pwiv)
		goto eww_fwee_connectow;

	gma_encodew->dev_pwiv = wvds_pwiv;

	connectow = &gma_connectow->base;
	gma_connectow->save = cdv_intew_wvds_save;
	gma_connectow->westowe = cdv_intew_wvds_westowe;
	encodew = &gma_encodew->base;

	/* Set up the DDC bus. */
	ddc_bus = gma_i2c_cweate(dev, GPIOC, "WVDSDDC_C");
	if (!ddc_bus) {
		dev_pwintk(KEWN_EWW, dev->dev,
			   "DDC bus wegistwation " "faiwed.\n");
		goto eww_fwee_wvds_pwiv;
	}

	wet = dwm_connectow_init_with_ddc(dev, connectow,
					  &cdv_intew_wvds_connectow_funcs,
					  DWM_MODE_CONNECTOW_WVDS,
					  &ddc_bus->base);
	if (wet)
		goto eww_destwoy_ddc;

	wet = dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_WVDS);
	if (wet)
		goto eww_connectow_cweanup;

	gma_connectow_attach_encodew(gma_connectow, gma_encodew);
	gma_encodew->type = INTEW_OUTPUT_WVDS;

	dwm_encodew_hewpew_add(encodew, &cdv_intew_wvds_hewpew_funcs);
	dwm_connectow_hewpew_add(connectow,
				 &cdv_intew_wvds_connectow_hewpew_funcs);
	connectow->dispway_info.subpixew_owdew = SubPixewHowizontawWGB;
	connectow->intewwace_awwowed = fawse;
	connectow->doubwescan_awwowed = fawse;

	/*Attach connectow pwopewties*/
	dwm_object_attach_pwopewty(&connectow->base,
				      dev->mode_config.scawing_mode_pwopewty,
				      DWM_MODE_SCAWE_FUWWSCWEEN);
	dwm_object_attach_pwopewty(&connectow->base,
				      dev_pwiv->backwight_pwopewty,
				      BWIGHTNESS_MAX_WEVEW);

	/**
	 * Set up I2C bus
	 * FIXME: distwoy i2c_bus when exit
	 */
	gma_encodew->i2c_bus = gma_i2c_cweate(dev, GPIOB, "WVDSBWC_B");
	if (!gma_encodew->i2c_bus) {
		dev_pwintk(KEWN_EWW,
			dev->dev, "I2C bus wegistwation faiwed.\n");
		goto eww_encodew_cweanup;
	}
	gma_encodew->i2c_bus->swave_addw = 0x2C;
	dev_pwiv->wvds_i2c_bus = gma_encodew->i2c_bus;

	/*
	 * WVDS discovewy:
	 * 1) check fow EDID on DDC
	 * 2) check fow VBT data
	 * 3) check to see if WVDS is awweady on
	 *    if none of the above, no panew
	 * 4) make suwe wid is open
	 *    if cwosed, act wike it's not thewe fow now
	 */

	/*
	 * Attempt to get the fixed panew mode fwom DDC.  Assume that the
	 * pwefewwed mode is the wight one.
	 */
	mutex_wock(&dev->mode_config.mutex);
	psb_intew_ddc_get_modes(connectow, &ddc_bus->base);

	wist_fow_each_entwy(scan, &connectow->pwobed_modes, head) {
		if (scan->type & DWM_MODE_TYPE_PWEFEWWED) {
			mode_dev->panew_fixed_mode =
			    dwm_mode_dupwicate(dev, scan);
			goto out;	/* FIXME: check fow quiwks */
		}
	}

	/* Faiwed to get EDID, what about VBT? do we need this?*/
	if (dev_pwiv->wfp_wvds_vbt_mode) {
		mode_dev->panew_fixed_mode =
			dwm_mode_dupwicate(dev, dev_pwiv->wfp_wvds_vbt_mode);
		if (mode_dev->panew_fixed_mode) {
			mode_dev->panew_fixed_mode->type |=
				DWM_MODE_TYPE_PWEFEWWED;
			goto out;	/* FIXME: check fow quiwks */
		}
	}
	/*
	 * If we didn't get EDID, twy checking if the panew is awweady tuwned
	 * on.	If so, assume that whatevew is cuwwentwy pwogwammed is the
	 * cowwect mode.
	 */
	wvds = WEG_WEAD(WVDS);
	pipe = (wvds & WVDS_PIPEB_SEWECT) ? 1 : 0;
	cwtc = psb_intew_get_cwtc_fwom_pipe(dev, pipe);

	if (cwtc && (wvds & WVDS_POWT_EN)) {
		mode_dev->panew_fixed_mode =
		    cdv_intew_cwtc_mode_get(dev, cwtc);
		if (mode_dev->panew_fixed_mode) {
			mode_dev->panew_fixed_mode->type |=
			    DWM_MODE_TYPE_PWEFEWWED;
			goto out;	/* FIXME: check fow quiwks */
		}
	}

	/* If we stiww don't have a mode aftew aww that, give up. */
	if (!mode_dev->panew_fixed_mode) {
		DWM_DEBUG
			("Found no modes on the wvds, ignowing the WVDS\n");
		goto eww_unwock;
	}

	/* setup PWM */
	{
		u32 pwm;

		pwm = WEG_WEAD(BWC_PWM_CTW2);
		if (pipe == 1)
			pwm |= PWM_PIPE_B;
		ewse
			pwm &= ~PWM_PIPE_B;
		pwm |= PWM_ENABWE;
		WEG_WWITE(BWC_PWM_CTW2, pwm);
	}

out:
	mutex_unwock(&dev->mode_config.mutex);
	wetuwn;

eww_unwock:
	mutex_unwock(&dev->mode_config.mutex);
	gma_i2c_destwoy(gma_encodew->i2c_bus);
eww_encodew_cweanup:
	dwm_encodew_cweanup(encodew);
eww_connectow_cweanup:
	dwm_connectow_cweanup(connectow);
eww_destwoy_ddc:
	gma_i2c_destwoy(ddc_bus);
eww_fwee_wvds_pwiv:
	kfwee(wvds_pwiv);
eww_fwee_connectow:
	kfwee(gma_connectow);
eww_fwee_encodew:
	kfwee(gma_encodew);
}
