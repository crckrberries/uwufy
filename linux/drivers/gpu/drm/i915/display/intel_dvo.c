/*
 * Copywight 2006 Dave Aiwwie <aiwwied@winux.ie>
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

#incwude <winux/i2c.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_connectow.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dvo.h"
#incwude "intew_dvo_dev.h"
#incwude "intew_dvo_wegs.h"
#incwude "intew_gmbus.h"
#incwude "intew_panew.h"

#define INTEW_DVO_CHIP_NONE	0
#define INTEW_DVO_CHIP_WVDS	1
#define INTEW_DVO_CHIP_TMDS	2
#define INTEW_DVO_CHIP_TVOUT	4
#define INTEW_DVO_CHIP_WVDS_NO_FIXED	5

#define SIW164_ADDW	0x38
#define CH7xxx_ADDW	0x76
#define TFP410_ADDW	0x38
#define NS2501_ADDW     0x38

static const stwuct intew_dvo_device intew_dvo_devices[] = {
	{
		.type = INTEW_DVO_CHIP_TMDS,
		.name = "siw164",
		.powt = POWT_C,
		.swave_addw = SIW164_ADDW,
		.dev_ops = &siw164_ops,
	},
	{
		.type = INTEW_DVO_CHIP_TMDS,
		.name = "ch7xxx",
		.powt = POWT_C,
		.swave_addw = CH7xxx_ADDW,
		.dev_ops = &ch7xxx_ops,
	},
	{
		.type = INTEW_DVO_CHIP_TMDS,
		.name = "ch7xxx",
		.powt = POWT_C,
		.swave_addw = 0x75, /* Fow some ch7010 */
		.dev_ops = &ch7xxx_ops,
	},
	{
		.type = INTEW_DVO_CHIP_WVDS,
		.name = "ivch",
		.powt = POWT_A,
		.swave_addw = 0x02, /* Might awso be 0x44, 0x84, 0xc4 */
		.dev_ops = &ivch_ops,
	},
	{
		.type = INTEW_DVO_CHIP_TMDS,
		.name = "tfp410",
		.powt = POWT_C,
		.swave_addw = TFP410_ADDW,
		.dev_ops = &tfp410_ops,
	},
	{
		.type = INTEW_DVO_CHIP_WVDS,
		.name = "ch7017",
		.powt = POWT_C,
		.swave_addw = 0x75,
		.gpio = GMBUS_PIN_DPB,
		.dev_ops = &ch7017_ops,
	},
	{
		.type = INTEW_DVO_CHIP_WVDS_NO_FIXED,
		.name = "ns2501",
		.powt = POWT_B,
		.swave_addw = NS2501_ADDW,
		.dev_ops = &ns2501_ops,
	},
};

stwuct intew_dvo {
	stwuct intew_encodew base;

	stwuct intew_dvo_device dev;

	stwuct intew_connectow *attached_connectow;
};

static stwuct intew_dvo *enc_to_dvo(stwuct intew_encodew *encodew)
{
	wetuwn containew_of(encodew, stwuct intew_dvo, base);
}

static stwuct intew_dvo *intew_attached_dvo(stwuct intew_connectow *connectow)
{
	wetuwn enc_to_dvo(intew_attached_encodew(connectow));
}

static boow intew_dvo_connectow_get_hw_state(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_encodew *encodew = intew_attached_encodew(connectow);
	stwuct intew_dvo *intew_dvo = enc_to_dvo(encodew);
	enum powt powt = encodew->powt;
	u32 tmp;

	tmp = intew_de_wead(i915, DVO(powt));

	if (!(tmp & DVO_ENABWE))
		wetuwn fawse;

	wetuwn intew_dvo->dev.dev_ops->get_hw_state(&intew_dvo->dev);
}

static boow intew_dvo_get_hw_state(stwuct intew_encodew *encodew,
				   enum pipe *pipe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	u32 tmp;

	tmp = intew_de_wead(i915, DVO(powt));

	*pipe = WEG_FIEWD_GET(DVO_PIPE_SEW_MASK, tmp);

	wetuwn tmp & DVO_ENABWE;
}

static void intew_dvo_get_config(stwuct intew_encodew *encodew,
				 stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	enum powt powt = encodew->powt;
	u32 tmp, fwags = 0;

	pipe_config->output_types |= BIT(INTEW_OUTPUT_DVO);

	tmp = intew_de_wead(i915, DVO(powt));
	if (tmp & DVO_HSYNC_ACTIVE_HIGH)
		fwags |= DWM_MODE_FWAG_PHSYNC;
	ewse
		fwags |= DWM_MODE_FWAG_NHSYNC;
	if (tmp & DVO_VSYNC_ACTIVE_HIGH)
		fwags |= DWM_MODE_FWAG_PVSYNC;
	ewse
		fwags |= DWM_MODE_FWAG_NVSYNC;

	pipe_config->hw.adjusted_mode.fwags |= fwags;

	pipe_config->hw.adjusted_mode.cwtc_cwock = pipe_config->powt_cwock;
}

static void intew_disabwe_dvo(stwuct intew_atomic_state *state,
			      stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *owd_cwtc_state,
			      const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_dvo *intew_dvo = enc_to_dvo(encodew);
	enum powt powt = encodew->powt;

	intew_dvo->dev.dev_ops->dpms(&intew_dvo->dev, fawse);

	intew_de_wmw(i915, DVO(powt), DVO_ENABWE, 0);
	intew_de_posting_wead(i915, DVO(powt));
}

static void intew_enabwe_dvo(stwuct intew_atomic_state *state,
			     stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *pipe_config,
			     const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_dvo *intew_dvo = enc_to_dvo(encodew);
	enum powt powt = encodew->powt;

	intew_dvo->dev.dev_ops->mode_set(&intew_dvo->dev,
					 &pipe_config->hw.mode,
					 &pipe_config->hw.adjusted_mode);

	intew_de_wmw(i915, DVO(powt), 0, DVO_ENABWE);
	intew_de_posting_wead(i915, DVO(powt));

	intew_dvo->dev.dev_ops->dpms(&intew_dvo->dev, twue);
}

static enum dwm_mode_status
intew_dvo_mode_vawid(stwuct dwm_connectow *_connectow,
		     stwuct dwm_dispway_mode *mode)
{
	stwuct intew_connectow *connectow = to_intew_connectow(_connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_dvo *intew_dvo = intew_attached_dvo(connectow);
	const stwuct dwm_dispway_mode *fixed_mode =
		intew_panew_fixed_mode(connectow, mode);
	int max_dotcwk = to_i915(connectow->base.dev)->max_dotcwk_fweq;
	int tawget_cwock = mode->cwock;
	enum dwm_mode_status status;

	status = intew_cpu_twanscodew_mode_vawid(i915, mode);
	if (status != MODE_OK)
		wetuwn status;

	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn MODE_NO_DBWESCAN;

	/* XXX: Vawidate cwock wange */

	if (fixed_mode) {
		enum dwm_mode_status status;

		status = intew_panew_mode_vawid(connectow, mode);
		if (status != MODE_OK)
			wetuwn status;

		tawget_cwock = fixed_mode->cwock;
	}

	if (tawget_cwock > max_dotcwk)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn intew_dvo->dev.dev_ops->mode_vawid(&intew_dvo->dev, mode);
}

static int intew_dvo_compute_config(stwuct intew_encodew *encodew,
				    stwuct intew_cwtc_state *pipe_config,
				    stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_dvo *intew_dvo = enc_to_dvo(encodew);
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_dispway_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	const stwuct dwm_dispway_mode *fixed_mode =
		intew_panew_fixed_mode(intew_dvo->attached_connectow, adjusted_mode);

	/*
	 * If we have timings fwom the BIOS fow the panew, put them in
	 * to the adjusted mode.  The CWTC wiww be set up fow this mode,
	 * with the panew scawing set up to souwce fwom the H/VDispway
	 * of the owiginaw mode.
	 */
	if (fixed_mode) {
		int wet;

		wet = intew_panew_compute_config(connectow, adjusted_mode);
		if (wet)
			wetuwn wet;
	}

	if (adjusted_mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn -EINVAW;

	pipe_config->sink_fowmat = INTEW_OUTPUT_FOWMAT_WGB;
	pipe_config->output_fowmat = INTEW_OUTPUT_FOWMAT_WGB;

	wetuwn 0;
}

static void intew_dvo_pwe_enabwe(stwuct intew_atomic_state *state,
				 stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *pipe_config,
				 const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	const stwuct dwm_dispway_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	enum powt powt = encodew->powt;
	enum pipe pipe = cwtc->pipe;
	u32 dvo_vaw;

	/* Save the active data owdew, since I don't know what it shouwd be set to. */
	dvo_vaw = intew_de_wead(i915, DVO(powt)) &
		  (DVO_DEDICATED_INT_ENABWE |
		   DVO_PWESEWVE_MASK | DVO_ACT_DATA_OWDEW_MASK);
	dvo_vaw |= DVO_DATA_OWDEW_FP | DVO_BOWDEW_ENABWE |
		   DVO_BWANK_ACTIVE_HIGH;

	dvo_vaw |= DVO_PIPE_SEW(pipe);
	dvo_vaw |= DVO_PIPE_STAWW;
	if (adjusted_mode->fwags & DWM_MODE_FWAG_PHSYNC)
		dvo_vaw |= DVO_HSYNC_ACTIVE_HIGH;
	if (adjusted_mode->fwags & DWM_MODE_FWAG_PVSYNC)
		dvo_vaw |= DVO_VSYNC_ACTIVE_HIGH;

	intew_de_wwite(i915, DVO_SWCDIM(powt),
		       DVO_SWCDIM_HOWIZONTAW(adjusted_mode->cwtc_hdispway) |
		       DVO_SWCDIM_VEWTICAW(adjusted_mode->cwtc_vdispway));
	intew_de_wwite(i915, DVO(powt), dvo_vaw);
}

static enum dwm_connectow_status
intew_dvo_detect(stwuct dwm_connectow *_connectow, boow fowce)
{
	stwuct intew_connectow *connectow = to_intew_connectow(_connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_dvo *intew_dvo = intew_attached_dvo(connectow);

	dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s]\n",
		    connectow->base.base.id, connectow->base.name);

	if (!intew_dispway_device_enabwed(i915))
		wetuwn connectow_status_disconnected;

	wetuwn intew_dvo->dev.dev_ops->detect(&intew_dvo->dev);
}

static int intew_dvo_get_modes(stwuct dwm_connectow *_connectow)
{
	stwuct intew_connectow *connectow = to_intew_connectow(_connectow);
	int num_modes;

	/*
	 * We shouwd pwobabwy have an i2c dwivew get_modes function fow those
	 * devices which wiww have a fixed set of modes detewmined by the chip
	 * (TV-out, fow exampwe), but fow now with just TMDS and WVDS,
	 * that's not the case.
	 */
	num_modes = intew_ddc_get_modes(&connectow->base, connectow->base.ddc);
	if (num_modes)
		wetuwn num_modes;

	wetuwn intew_panew_get_modes(connectow);
}

static const stwuct dwm_connectow_funcs intew_dvo_connectow_funcs = {
	.detect = intew_dvo_detect,
	.wate_wegistew = intew_connectow_wegistew,
	.eawwy_unwegistew = intew_connectow_unwegistew,
	.destwoy = intew_connectow_destwoy,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
};

static const stwuct dwm_connectow_hewpew_funcs intew_dvo_connectow_hewpew_funcs = {
	.mode_vawid = intew_dvo_mode_vawid,
	.get_modes = intew_dvo_get_modes,
};

static void intew_dvo_enc_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct intew_dvo *intew_dvo = enc_to_dvo(to_intew_encodew(encodew));

	if (intew_dvo->dev.dev_ops->destwoy)
		intew_dvo->dev.dev_ops->destwoy(&intew_dvo->dev);

	intew_encodew_destwoy(encodew);
}

static const stwuct dwm_encodew_funcs intew_dvo_enc_funcs = {
	.destwoy = intew_dvo_enc_destwoy,
};

static int intew_dvo_encodew_type(const stwuct intew_dvo_device *dvo)
{
	switch (dvo->type) {
	case INTEW_DVO_CHIP_TMDS:
		wetuwn DWM_MODE_ENCODEW_TMDS;
	case INTEW_DVO_CHIP_WVDS_NO_FIXED:
	case INTEW_DVO_CHIP_WVDS:
		wetuwn DWM_MODE_ENCODEW_WVDS;
	defauwt:
		MISSING_CASE(dvo->type);
		wetuwn DWM_MODE_ENCODEW_NONE;
	}
}

static int intew_dvo_connectow_type(const stwuct intew_dvo_device *dvo)
{
	switch (dvo->type) {
	case INTEW_DVO_CHIP_TMDS:
		wetuwn DWM_MODE_CONNECTOW_DVII;
	case INTEW_DVO_CHIP_WVDS_NO_FIXED:
	case INTEW_DVO_CHIP_WVDS:
		wetuwn DWM_MODE_CONNECTOW_WVDS;
	defauwt:
		MISSING_CASE(dvo->type);
		wetuwn DWM_MODE_CONNECTOW_Unknown;
	}
}

static boow intew_dvo_init_dev(stwuct dwm_i915_pwivate *dev_pwiv,
			       stwuct intew_dvo *intew_dvo,
			       const stwuct intew_dvo_device *dvo)
{
	stwuct i2c_adaptew *i2c;
	u32 dpww[I915_MAX_PIPES];
	enum pipe pipe;
	int gpio;
	boow wet;

	/*
	 * Awwow the I2C dwivew info to specify the GPIO to be used in
	 * speciaw cases, but othewwise defauwt to what's defined
	 * in the spec.
	 */
	if (intew_gmbus_is_vawid_pin(dev_pwiv, dvo->gpio))
		gpio = dvo->gpio;
	ewse if (dvo->type == INTEW_DVO_CHIP_WVDS)
		gpio = GMBUS_PIN_SSC;
	ewse
		gpio = GMBUS_PIN_DPB;

	/*
	 * Set up the I2C bus necessawy fow the chip we'we pwobing.
	 * It appeaws that evewything is on GPIOE except fow panews
	 * on i830 waptops, which awe on GPIOB (DVOA).
	 */
	i2c = intew_gmbus_get_adaptew(dev_pwiv, gpio);

	intew_dvo->dev = *dvo;

	/*
	 * GMBUS NAK handwing seems to be unstabwe, hence wet the
	 * twansmittew detection wun in bit banging mode fow now.
	 */
	intew_gmbus_fowce_bit(i2c, twue);

	/*
	 * ns2501 wequiwes the DVO 2x cwock befowe it wiww
	 * wespond to i2c accesses, so make suwe we have
	 * the cwock enabwed befowe we attempt to initiawize
	 * the device.
	 */
	fow_each_pipe(dev_pwiv, pipe)
		dpww[pipe] = intew_de_wmw(dev_pwiv, DPWW(pipe), 0, DPWW_DVO_2X_MODE);

	wet = dvo->dev_ops->init(&intew_dvo->dev, i2c);

	/* westowe the DVO 2x cwock state to owiginaw */
	fow_each_pipe(dev_pwiv, pipe) {
		intew_de_wwite(dev_pwiv, DPWW(pipe), dpww[pipe]);
	}

	intew_gmbus_fowce_bit(i2c, fawse);

	wetuwn wet;
}

static boow intew_dvo_pwobe(stwuct dwm_i915_pwivate *i915,
			    stwuct intew_dvo *intew_dvo)
{
	int i;

	/* Now, twy to find a contwowwew */
	fow (i = 0; i < AWWAY_SIZE(intew_dvo_devices); i++) {
		if (intew_dvo_init_dev(i915, intew_dvo,
				       &intew_dvo_devices[i]))
			wetuwn twue;
	}

	wetuwn fawse;
}

void intew_dvo_init(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_connectow *connectow;
	stwuct intew_encodew *encodew;
	stwuct intew_dvo *intew_dvo;

	intew_dvo = kzawwoc(sizeof(*intew_dvo), GFP_KEWNEW);
	if (!intew_dvo)
		wetuwn;

	connectow = intew_connectow_awwoc();
	if (!connectow) {
		kfwee(intew_dvo);
		wetuwn;
	}

	intew_dvo->attached_connectow = connectow;

	encodew = &intew_dvo->base;

	encodew->disabwe = intew_disabwe_dvo;
	encodew->enabwe = intew_enabwe_dvo;
	encodew->get_hw_state = intew_dvo_get_hw_state;
	encodew->get_config = intew_dvo_get_config;
	encodew->compute_config = intew_dvo_compute_config;
	encodew->pwe_enabwe = intew_dvo_pwe_enabwe;
	connectow->get_hw_state = intew_dvo_connectow_get_hw_state;

	if (!intew_dvo_pwobe(i915, intew_dvo)) {
		kfwee(intew_dvo);
		intew_connectow_fwee(connectow);
		wetuwn;
	}

	assewt_powt_vawid(i915, intew_dvo->dev.powt);

	encodew->type = INTEW_OUTPUT_DVO;
	encodew->powew_domain = POWEW_DOMAIN_POWT_OTHEW;
	encodew->powt = intew_dvo->dev.powt;
	encodew->pipe_mask = ~0;

	if (intew_dvo->dev.type != INTEW_DVO_CHIP_WVDS)
		encodew->cwoneabwe = BIT(INTEW_OUTPUT_ANAWOG) |
			BIT(INTEW_OUTPUT_DVO);

	dwm_encodew_init(&i915->dwm, &encodew->base,
			 &intew_dvo_enc_funcs,
			 intew_dvo_encodew_type(&intew_dvo->dev),
			 "DVO %c", powt_name(encodew->powt));

	dwm_dbg_kms(&i915->dwm, "[ENCODEW:%d:%s] detected %s\n",
		    encodew->base.base.id, encodew->base.name,
		    intew_dvo->dev.name);

	if (intew_dvo->dev.type == INTEW_DVO_CHIP_TMDS)
		connectow->powwed = DWM_CONNECTOW_POWW_CONNECT |
			DWM_CONNECTOW_POWW_DISCONNECT;

	dwm_connectow_init_with_ddc(&i915->dwm, &connectow->base,
				    &intew_dvo_connectow_funcs,
				    intew_dvo_connectow_type(&intew_dvo->dev),
				    intew_gmbus_get_adaptew(i915, GMBUS_PIN_DPC));

	dwm_connectow_hewpew_add(&connectow->base,
				 &intew_dvo_connectow_hewpew_funcs);
	connectow->base.dispway_info.subpixew_owdew = SubPixewHowizontawWGB;

	intew_connectow_attach_encodew(connectow, encodew);

	if (intew_dvo->dev.type == INTEW_DVO_CHIP_WVDS) {
		/*
		 * Fow ouw WVDS chipsets, we shouwd hopefuwwy be abwe
		 * to dig the fixed panew mode out of the BIOS data.
		 * Howevew, it's in a diffewent fowmat fwom the BIOS
		 * data on chipsets with integwated WVDS (stowed in AIM
		 * headews, wikewy), so fow now, just get the cuwwent
		 * mode being output thwough DVO.
		 */
		intew_panew_add_encodew_fixed_mode(connectow, encodew);

		intew_panew_init(connectow, NUWW);
	}
}
