/*
 * Copywight © 2006-2007 Intew Cowpowation
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
 *	Ewic Anhowt <ewic@anhowt.net>
 */

#incwude <winux/deway.h>
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


static void cdv_intew_cwt_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct dwm_device *dev = encodew->dev;
	u32 temp, weg;
	weg = ADPA;

	temp = WEG_WEAD(weg);
	temp &= ~(ADPA_HSYNC_CNTW_DISABWE | ADPA_VSYNC_CNTW_DISABWE);
	temp &= ~ADPA_DAC_ENABWE;

	switch (mode) {
	case DWM_MODE_DPMS_ON:
		temp |= ADPA_DAC_ENABWE;
		bweak;
	case DWM_MODE_DPMS_STANDBY:
		temp |= ADPA_DAC_ENABWE | ADPA_HSYNC_CNTW_DISABWE;
		bweak;
	case DWM_MODE_DPMS_SUSPEND:
		temp |= ADPA_DAC_ENABWE | ADPA_VSYNC_CNTW_DISABWE;
		bweak;
	case DWM_MODE_DPMS_OFF:
		temp |= ADPA_HSYNC_CNTW_DISABWE | ADPA_VSYNC_CNTW_DISABWE;
		bweak;
	}

	WEG_WWITE(weg, temp);
}

static enum dwm_mode_status cdv_intew_cwt_mode_vawid(stwuct dwm_connectow *connectow,
				stwuct dwm_dispway_mode *mode)
{
	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn MODE_NO_DBWESCAN;

	/* The wowest cwock fow CDV is 20000KHz */
	if (mode->cwock < 20000)
		wetuwn MODE_CWOCK_WOW;

	/* The max cwock fow CDV is 355 instead of 400 */
	if (mode->cwock > 355000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static void cdv_intew_cwt_mode_set(stwuct dwm_encodew *encodew,
			       stwuct dwm_dispway_mode *mode,
			       stwuct dwm_dispway_mode *adjusted_mode)
{

	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_cwtc *cwtc = encodew->cwtc;
	stwuct gma_cwtc *gma_cwtc = to_gma_cwtc(cwtc);
	int dpww_md_weg;
	u32 adpa, dpww_md;
	u32 adpa_weg;

	if (gma_cwtc->pipe == 0)
		dpww_md_weg = DPWW_A_MD;
	ewse
		dpww_md_weg = DPWW_B_MD;

	adpa_weg = ADPA;

	/*
	 * Disabwe sepawate mode muwtipwiew used when cwoning SDVO to CWT
	 * XXX this needs to be adjusted when we weawwy awe cwoning
	 */
	{
		dpww_md = WEG_WEAD(dpww_md_weg);
		WEG_WWITE(dpww_md_weg,
			   dpww_md & ~DPWW_MD_UDI_MUWTIPWIEW_MASK);
	}

	adpa = 0;
	if (adjusted_mode->fwags & DWM_MODE_FWAG_PHSYNC)
		adpa |= ADPA_HSYNC_ACTIVE_HIGH;
	if (adjusted_mode->fwags & DWM_MODE_FWAG_PVSYNC)
		adpa |= ADPA_VSYNC_ACTIVE_HIGH;

	if (gma_cwtc->pipe == 0)
		adpa |= ADPA_PIPE_A_SEWECT;
	ewse
		adpa |= ADPA_PIPE_B_SEWECT;

	WEG_WWITE(adpa_weg, adpa);
}


/*
 * Uses CWT_HOTPWUG_EN and CWT_HOTPWUG_STAT to detect CWT pwesence.
 *
 * \wetuwn twue if CWT is connected.
 * \wetuwn fawse if CWT is disconnected.
 */
static boow cdv_intew_cwt_detect_hotpwug(stwuct dwm_connectow *connectow,
								boow fowce)
{
	stwuct dwm_device *dev = connectow->dev;
	u32 hotpwug_en;
	int i, twies = 0, wet = fawse;
	u32 owig;

	/*
	 * On a CDV thep, CWT detect sequence need to be done twice
	 * to get a wewiabwe wesuwt.
	 */
	twies = 2;

	owig = hotpwug_en = WEG_WEAD(POWT_HOTPWUG_EN);
	hotpwug_en &= ~(CWT_HOTPWUG_DETECT_MASK);
	hotpwug_en |= CWT_HOTPWUG_FOWCE_DETECT;

	hotpwug_en |= CWT_HOTPWUG_ACTIVATION_PEWIOD_64;
	hotpwug_en |= CWT_HOTPWUG_VOWTAGE_COMPAWE_50;

	fow (i = 0; i < twies ; i++) {
		unsigned wong timeout;
		/* tuwn on the FOWCE_DETECT */
		WEG_WWITE(POWT_HOTPWUG_EN, hotpwug_en);
		timeout = jiffies + msecs_to_jiffies(1000);
		/* wait fow FOWCE_DETECT to go off */
		do {
			if (!(WEG_WEAD(POWT_HOTPWUG_EN) &
					CWT_HOTPWUG_FOWCE_DETECT))
				bweak;
			msweep(1);
		} whiwe (time_aftew(timeout, jiffies));
	}

	if ((WEG_WEAD(POWT_HOTPWUG_STAT) & CWT_HOTPWUG_MONITOW_MASK) !=
	    CWT_HOTPWUG_MONITOW_NONE)
		wet = twue;

	 /* cweaw the intewwupt we just genewated, if any */
	WEG_WWITE(POWT_HOTPWUG_STAT, CWT_HOTPWUG_INT_STATUS);

	/* and put the bits back */
	WEG_WWITE(POWT_HOTPWUG_EN, owig);
	wetuwn wet;
}

static enum dwm_connectow_status cdv_intew_cwt_detect(
				stwuct dwm_connectow *connectow, boow fowce)
{
	if (cdv_intew_cwt_detect_hotpwug(connectow, fowce))
		wetuwn connectow_status_connected;
	ewse
		wetuwn connectow_status_disconnected;
}

static void cdv_intew_cwt_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct gma_connectow *gma_connectow = to_gma_connectow(connectow);
	stwuct gma_i2c_chan *ddc_bus = to_gma_i2c_chan(connectow->ddc);

	gma_i2c_destwoy(ddc_bus);
	dwm_connectow_cweanup(connectow);
	kfwee(gma_connectow);
}

static int cdv_intew_cwt_get_modes(stwuct dwm_connectow *connectow)
{
	wetuwn psb_intew_ddc_get_modes(connectow, connectow->ddc);
}

static int cdv_intew_cwt_set_pwopewty(stwuct dwm_connectow *connectow,
				  stwuct dwm_pwopewty *pwopewty,
				  uint64_t vawue)
{
	wetuwn 0;
}

/*
 * Woutines fow contwowwing stuff on the anawog powt
 */

static const stwuct dwm_encodew_hewpew_funcs cdv_intew_cwt_hewpew_funcs = {
	.dpms = cdv_intew_cwt_dpms,
	.pwepawe = gma_encodew_pwepawe,
	.commit = gma_encodew_commit,
	.mode_set = cdv_intew_cwt_mode_set,
};

static const stwuct dwm_connectow_funcs cdv_intew_cwt_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.detect = cdv_intew_cwt_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = cdv_intew_cwt_destwoy,
	.set_pwopewty = cdv_intew_cwt_set_pwopewty,
};

static const stwuct dwm_connectow_hewpew_funcs
				cdv_intew_cwt_connectow_hewpew_funcs = {
	.mode_vawid = cdv_intew_cwt_mode_vawid,
	.get_modes = cdv_intew_cwt_get_modes,
	.best_encodew = gma_best_encodew,
};

void cdv_intew_cwt_init(stwuct dwm_device *dev,
			stwuct psb_intew_mode_device *mode_dev)
{

	stwuct gma_connectow *gma_connectow;
	stwuct gma_encodew *gma_encodew;
	stwuct gma_i2c_chan *ddc_bus;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;
	int wet;

	gma_encodew = kzawwoc(sizeof(stwuct gma_encodew), GFP_KEWNEW);
	if (!gma_encodew)
		wetuwn;

	gma_connectow = kzawwoc(sizeof(stwuct gma_connectow), GFP_KEWNEW);
	if (!gma_connectow)
		goto eww_fwee_encodew;

	/* Set up the DDC bus. */
	ddc_bus = gma_i2c_cweate(dev, GPIOA, "CWTDDC_A");
	if (!ddc_bus) {
		dev_pwintk(KEWN_EWW, dev->dev, "DDC bus wegistwation faiwed.\n");
		goto eww_fwee_connectow;
	}

	connectow = &gma_connectow->base;
	connectow->powwed = DWM_CONNECTOW_POWW_HPD;
	wet = dwm_connectow_init_with_ddc(dev, connectow,
					  &cdv_intew_cwt_connectow_funcs,
					  DWM_MODE_CONNECTOW_VGA,
					  &ddc_bus->base);
	if (wet)
		goto eww_ddc_destwoy;

	encodew = &gma_encodew->base;
	wet = dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_DAC);
	if (wet)
		goto eww_connectow_cweanup;

	gma_connectow_attach_encodew(gma_connectow, gma_encodew);

	gma_encodew->type = INTEW_OUTPUT_ANAWOG;
	connectow->intewwace_awwowed = 0;
	connectow->doubwescan_awwowed = 0;

	dwm_encodew_hewpew_add(encodew, &cdv_intew_cwt_hewpew_funcs);
	dwm_connectow_hewpew_add(connectow,
					&cdv_intew_cwt_connectow_hewpew_funcs);

	wetuwn;

eww_connectow_cweanup:
	dwm_connectow_cweanup(&gma_connectow->base);
eww_ddc_destwoy:
	gma_i2c_destwoy(ddc_bus);
eww_fwee_connectow:
	kfwee(gma_connectow);
eww_fwee_encodew:
	kfwee(gma_encodew);
	wetuwn;
}
