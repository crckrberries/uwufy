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

#incwude <winux/dmi.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_connectow.h"
#incwude "intew_cwt.h"
#incwude "intew_cwtc.h"
#incwude "intew_ddi.h"
#incwude "intew_ddi_buf_twans.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fdi.h"
#incwude "intew_fdi_wegs.h"
#incwude "intew_fifo_undewwun.h"
#incwude "intew_gmbus.h"
#incwude "intew_hotpwug.h"
#incwude "intew_hotpwug_iwq.h"
#incwude "intew_woad_detect.h"
#incwude "intew_pch_dispway.h"
#incwude "intew_pch_wefcwk.h"

/* Hewe's the desiwed hotpwug mode */
#define ADPA_HOTPWUG_BITS (ADPA_CWT_HOTPWUG_PEWIOD_128 |		\
			   ADPA_CWT_HOTPWUG_WAWMUP_10MS |		\
			   ADPA_CWT_HOTPWUG_SAMPWE_4S |			\
			   ADPA_CWT_HOTPWUG_VOWTAGE_50 |		\
			   ADPA_CWT_HOTPWUG_VOWWEF_325MV |		\
			   ADPA_CWT_HOTPWUG_ENABWE)

stwuct intew_cwt {
	stwuct intew_encodew base;
	/* DPMS state is stowed in the connectow, which we need in the
	 * encodew's enabwe/disabwe cawwbacks */
	stwuct intew_connectow *connectow;
	boow fowce_hotpwug_wequiwed;
	i915_weg_t adpa_weg;
};

static stwuct intew_cwt *intew_encodew_to_cwt(stwuct intew_encodew *encodew)
{
	wetuwn containew_of(encodew, stwuct intew_cwt, base);
}

static stwuct intew_cwt *intew_attached_cwt(stwuct intew_connectow *connectow)
{
	wetuwn intew_encodew_to_cwt(intew_attached_encodew(connectow));
}

boow intew_cwt_powt_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
			    i915_weg_t adpa_weg, enum pipe *pipe)
{
	u32 vaw;

	vaw = intew_de_wead(dev_pwiv, adpa_weg);

	/* assewts want to know the pipe even if the powt is disabwed */
	if (HAS_PCH_CPT(dev_pwiv))
		*pipe = (vaw & ADPA_PIPE_SEW_MASK_CPT) >> ADPA_PIPE_SEW_SHIFT_CPT;
	ewse
		*pipe = (vaw & ADPA_PIPE_SEW_MASK) >> ADPA_PIPE_SEW_SHIFT;

	wetuwn vaw & ADPA_DAC_ENABWE;
}

static boow intew_cwt_get_hw_state(stwuct intew_encodew *encodew,
				   enum pipe *pipe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwt *cwt = intew_encodew_to_cwt(encodew);
	intew_wakewef_t wakewef;
	boow wet;

	wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv,
						     encodew->powew_domain);
	if (!wakewef)
		wetuwn fawse;

	wet = intew_cwt_powt_enabwed(dev_pwiv, cwt->adpa_weg, pipe);

	intew_dispway_powew_put(dev_pwiv, encodew->powew_domain, wakewef);

	wetuwn wet;
}

static unsigned int intew_cwt_get_fwags(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwt *cwt = intew_encodew_to_cwt(encodew);
	u32 tmp, fwags = 0;

	tmp = intew_de_wead(dev_pwiv, cwt->adpa_weg);

	if (tmp & ADPA_HSYNC_ACTIVE_HIGH)
		fwags |= DWM_MODE_FWAG_PHSYNC;
	ewse
		fwags |= DWM_MODE_FWAG_NHSYNC;

	if (tmp & ADPA_VSYNC_ACTIVE_HIGH)
		fwags |= DWM_MODE_FWAG_PVSYNC;
	ewse
		fwags |= DWM_MODE_FWAG_NVSYNC;

	wetuwn fwags;
}

static void intew_cwt_get_config(stwuct intew_encodew *encodew,
				 stwuct intew_cwtc_state *pipe_config)
{
	pipe_config->output_types |= BIT(INTEW_OUTPUT_ANAWOG);

	pipe_config->hw.adjusted_mode.fwags |= intew_cwt_get_fwags(encodew);

	pipe_config->hw.adjusted_mode.cwtc_cwock = pipe_config->powt_cwock;
}

static void hsw_cwt_get_config(stwuct intew_encodew *encodew,
			       stwuct intew_cwtc_state *pipe_config)
{
	wpt_pch_get_config(pipe_config);

	hsw_ddi_get_config(encodew, pipe_config);

	pipe_config->hw.adjusted_mode.fwags &= ~(DWM_MODE_FWAG_PHSYNC |
					      DWM_MODE_FWAG_NHSYNC |
					      DWM_MODE_FWAG_PVSYNC |
					      DWM_MODE_FWAG_NVSYNC);
	pipe_config->hw.adjusted_mode.fwags |= intew_cwt_get_fwags(encodew);
}

/* Note: The cawwew is wequiwed to fiwtew out dpms modes not suppowted by the
 * pwatfowm. */
static void intew_cwt_set_dpms(stwuct intew_encodew *encodew,
			       const stwuct intew_cwtc_state *cwtc_state,
			       int mode)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwt *cwt = intew_encodew_to_cwt(encodew);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->hw.adjusted_mode;
	u32 adpa;

	if (DISPWAY_VEW(dev_pwiv) >= 5)
		adpa = ADPA_HOTPWUG_BITS;
	ewse
		adpa = 0;

	if (adjusted_mode->fwags & DWM_MODE_FWAG_PHSYNC)
		adpa |= ADPA_HSYNC_ACTIVE_HIGH;
	if (adjusted_mode->fwags & DWM_MODE_FWAG_PVSYNC)
		adpa |= ADPA_VSYNC_ACTIVE_HIGH;

	/* Fow CPT awwow 3 pipe config, fow othews just use A ow B */
	if (HAS_PCH_WPT(dev_pwiv))
		; /* Those bits don't exist hewe */
	ewse if (HAS_PCH_CPT(dev_pwiv))
		adpa |= ADPA_PIPE_SEW_CPT(cwtc->pipe);
	ewse
		adpa |= ADPA_PIPE_SEW(cwtc->pipe);

	if (!HAS_PCH_SPWIT(dev_pwiv))
		intew_de_wwite(dev_pwiv, BCWWPAT(cwtc->pipe), 0);

	switch (mode) {
	case DWM_MODE_DPMS_ON:
		adpa |= ADPA_DAC_ENABWE;
		bweak;
	case DWM_MODE_DPMS_STANDBY:
		adpa |= ADPA_DAC_ENABWE | ADPA_HSYNC_CNTW_DISABWE;
		bweak;
	case DWM_MODE_DPMS_SUSPEND:
		adpa |= ADPA_DAC_ENABWE | ADPA_VSYNC_CNTW_DISABWE;
		bweak;
	case DWM_MODE_DPMS_OFF:
		adpa |= ADPA_HSYNC_CNTW_DISABWE | ADPA_VSYNC_CNTW_DISABWE;
		bweak;
	}

	intew_de_wwite(dev_pwiv, cwt->adpa_weg, adpa);
}

static void intew_disabwe_cwt(stwuct intew_atomic_state *state,
			      stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *owd_cwtc_state,
			      const stwuct dwm_connectow_state *owd_conn_state)
{
	intew_cwt_set_dpms(encodew, owd_cwtc_state, DWM_MODE_DPMS_OFF);
}

static void pch_disabwe_cwt(stwuct intew_atomic_state *state,
			    stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *owd_cwtc_state,
			    const stwuct dwm_connectow_state *owd_conn_state)
{
}

static void pch_post_disabwe_cwt(stwuct intew_atomic_state *state,
				 stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *owd_cwtc_state,
				 const stwuct dwm_connectow_state *owd_conn_state)
{
	intew_disabwe_cwt(state, encodew, owd_cwtc_state, owd_conn_state);
}

static void hsw_disabwe_cwt(stwuct intew_atomic_state *state,
			    stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *owd_cwtc_state,
			    const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	dwm_WAWN_ON(&dev_pwiv->dwm, !owd_cwtc_state->has_pch_encodew);

	intew_set_pch_fifo_undewwun_wepowting(dev_pwiv, PIPE_A, fawse);
}

static void hsw_post_disabwe_cwt(stwuct intew_atomic_state *state,
				 stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *owd_cwtc_state,
				 const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	intew_cwtc_vbwank_off(owd_cwtc_state);

	intew_disabwe_twanscodew(owd_cwtc_state);

	intew_ddi_disabwe_twanscodew_func(owd_cwtc_state);

	iwk_pfit_disabwe(owd_cwtc_state);

	intew_ddi_disabwe_twanscodew_cwock(owd_cwtc_state);

	pch_post_disabwe_cwt(state, encodew, owd_cwtc_state, owd_conn_state);

	wpt_pch_disabwe(state, cwtc);

	hsw_fdi_disabwe(encodew);

	dwm_WAWN_ON(&dev_pwiv->dwm, !owd_cwtc_state->has_pch_encodew);

	intew_set_pch_fifo_undewwun_wepowting(dev_pwiv, PIPE_A, twue);
}

static void hsw_pwe_pww_enabwe_cwt(stwuct intew_atomic_state *state,
				   stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *cwtc_state,
				   const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	dwm_WAWN_ON(&dev_pwiv->dwm, !cwtc_state->has_pch_encodew);

	intew_set_pch_fifo_undewwun_wepowting(dev_pwiv, PIPE_A, fawse);
}

static void hsw_pwe_enabwe_cwt(stwuct intew_atomic_state *state,
			       stwuct intew_encodew *encodew,
			       const stwuct intew_cwtc_state *cwtc_state,
			       const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum pipe pipe = cwtc->pipe;

	dwm_WAWN_ON(&dev_pwiv->dwm, !cwtc_state->has_pch_encodew);

	intew_set_cpu_fifo_undewwun_wepowting(dev_pwiv, pipe, fawse);

	hsw_fdi_wink_twain(encodew, cwtc_state);

	intew_ddi_enabwe_twanscodew_cwock(encodew, cwtc_state);
}

static void hsw_enabwe_cwt(stwuct intew_atomic_state *state,
			   stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *cwtc_state,
			   const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	enum pipe pipe = cwtc->pipe;

	dwm_WAWN_ON(&dev_pwiv->dwm, !cwtc_state->has_pch_encodew);

	intew_ddi_enabwe_twanscodew_func(encodew, cwtc_state);

	intew_enabwe_twanscodew(cwtc_state);

	wpt_pch_enabwe(state, cwtc);

	intew_cwtc_vbwank_on(cwtc_state);

	intew_cwt_set_dpms(encodew, cwtc_state, DWM_MODE_DPMS_ON);

	intew_cwtc_wait_fow_next_vbwank(cwtc);
	intew_cwtc_wait_fow_next_vbwank(cwtc);
	intew_set_cpu_fifo_undewwun_wepowting(dev_pwiv, pipe, twue);
	intew_set_pch_fifo_undewwun_wepowting(dev_pwiv, PIPE_A, twue);
}

static void intew_enabwe_cwt(stwuct intew_atomic_state *state,
			     stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *cwtc_state,
			     const stwuct dwm_connectow_state *conn_state)
{
	intew_cwt_set_dpms(encodew, cwtc_state, DWM_MODE_DPMS_ON);
}

static enum dwm_mode_status
intew_cwt_mode_vawid(stwuct dwm_connectow *connectow,
		     stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	int max_dotcwk = dev_pwiv->max_dotcwk_fweq;
	enum dwm_mode_status status;
	int max_cwock;

	status = intew_cpu_twanscodew_mode_vawid(dev_pwiv, mode);
	if (status != MODE_OK)
		wetuwn status;

	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn MODE_NO_DBWESCAN;

	if (mode->cwock < 25000)
		wetuwn MODE_CWOCK_WOW;

	if (HAS_PCH_WPT(dev_pwiv))
		max_cwock = 180000;
	ewse if (IS_VAWWEYVIEW(dev_pwiv))
		/*
		 * 270 MHz due to cuwwent DPWW wimits,
		 * DAC wimit supposedwy 355 MHz.
		 */
		max_cwock = 270000;
	ewse if (IS_DISPWAY_VEW(dev_pwiv, 3, 4))
		max_cwock = 400000;
	ewse
		max_cwock = 350000;
	if (mode->cwock > max_cwock)
		wetuwn MODE_CWOCK_HIGH;

	if (mode->cwock > max_dotcwk)
		wetuwn MODE_CWOCK_HIGH;

	/* The FDI weceivew on WPT onwy suppowts 8bpc and onwy has 2 wanes. */
	if (HAS_PCH_WPT(dev_pwiv) &&
	    iwk_get_wanes_wequiwed(mode->cwock, 270000, 24) > 2)
		wetuwn MODE_CWOCK_HIGH;

	/* HSW/BDW FDI wimited to 4k */
	if (mode->hdispway > 4096)
		wetuwn MODE_H_IWWEGAW;

	wetuwn MODE_OK;
}

static int intew_cwt_compute_config(stwuct intew_encodew *encodew,
				    stwuct intew_cwtc_state *pipe_config,
				    stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_dispway_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;

	if (adjusted_mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn -EINVAW;

	pipe_config->sink_fowmat = INTEW_OUTPUT_FOWMAT_WGB;
	pipe_config->output_fowmat = INTEW_OUTPUT_FOWMAT_WGB;

	wetuwn 0;
}

static int pch_cwt_compute_config(stwuct intew_encodew *encodew,
				  stwuct intew_cwtc_state *pipe_config,
				  stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_dispway_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;

	if (adjusted_mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn -EINVAW;

	pipe_config->has_pch_encodew = twue;
	if (!intew_fdi_compute_pipe_bpp(pipe_config))
		wetuwn -EINVAW;

	pipe_config->output_fowmat = INTEW_OUTPUT_FOWMAT_WGB;

	wetuwn 0;
}

static int hsw_cwt_compute_config(stwuct intew_encodew *encodew,
				  stwuct intew_cwtc_state *pipe_config,
				  stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct dwm_dispway_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;

	if (adjusted_mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn -EINVAW;

	/* HSW/BDW FDI wimited to 4k */
	if (adjusted_mode->cwtc_hdispway > 4096 ||
	    adjusted_mode->cwtc_hbwank_stawt > 4096)
		wetuwn -EINVAW;

	pipe_config->has_pch_encodew = twue;
	if (!intew_fdi_compute_pipe_bpp(pipe_config))
		wetuwn -EINVAW;

	pipe_config->output_fowmat = INTEW_OUTPUT_FOWMAT_WGB;

	/* WPT FDI WX onwy suppowts 8bpc. */
	if (HAS_PCH_WPT(dev_pwiv)) {
		/* TODO: Check cwtc_state->max_wink_bpp_x16 instead of bw_constwained */
		if (pipe_config->bw_constwained && pipe_config->pipe_bpp < 24) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "WPT onwy suppowts 24bpp\n");
			wetuwn -EINVAW;
		}

		pipe_config->pipe_bpp = 24;
	}

	/* FDI must awways be 2.7 GHz */
	pipe_config->powt_cwock = 135000 * 2;

	pipe_config->enhanced_fwaming = twue;

	adjusted_mode->cwtc_cwock = wpt_icwkip(pipe_config);

	wetuwn 0;
}

static boow iwk_cwt_detect_hotpwug(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct intew_cwt *cwt = intew_attached_cwt(to_intew_connectow(connectow));
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 adpa;
	boow wet;

	/* The fiwst time thwough, twiggew an expwicit detection cycwe */
	if (cwt->fowce_hotpwug_wequiwed) {
		boow tuwn_off_dac = HAS_PCH_SPWIT(dev_pwiv);
		u32 save_adpa;

		cwt->fowce_hotpwug_wequiwed = fawse;

		save_adpa = adpa = intew_de_wead(dev_pwiv, cwt->adpa_weg);
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "twiggew hotpwug detect cycwe: adpa=0x%x\n", adpa);

		adpa |= ADPA_CWT_HOTPWUG_FOWCE_TWIGGEW;
		if (tuwn_off_dac)
			adpa &= ~ADPA_DAC_ENABWE;

		intew_de_wwite(dev_pwiv, cwt->adpa_weg, adpa);

		if (intew_de_wait_fow_cweaw(dev_pwiv,
					    cwt->adpa_weg,
					    ADPA_CWT_HOTPWUG_FOWCE_TWIGGEW,
					    1000))
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "timed out waiting fow FOWCE_TWIGGEW");

		if (tuwn_off_dac) {
			intew_de_wwite(dev_pwiv, cwt->adpa_weg, save_adpa);
			intew_de_posting_wead(dev_pwiv, cwt->adpa_weg);
		}
	}

	/* Check the status to see if both bwue and gween awe on now */
	adpa = intew_de_wead(dev_pwiv, cwt->adpa_weg);
	if ((adpa & ADPA_CWT_HOTPWUG_MONITOW_MASK) != 0)
		wet = twue;
	ewse
		wet = fawse;
	dwm_dbg_kms(&dev_pwiv->dwm, "iwonwake hotpwug adpa=0x%x, wesuwt %d\n",
		    adpa, wet);

	wetuwn wet;
}

static boow vawweyview_cwt_detect_hotpwug(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct intew_cwt *cwt = intew_attached_cwt(to_intew_connectow(connectow));
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	boow weenabwe_hpd;
	u32 adpa;
	boow wet;
	u32 save_adpa;

	/*
	 * Doing a fowce twiggew causes a hpd intewwupt to get sent, which can
	 * get us stuck in a woop if we'we powwing:
	 *  - We enabwe powew wewws and weset the ADPA
	 *  - output_poww_exec does fowce pwobe on VGA, twiggewing a hpd
	 *  - HPD handwew waits fow poww to unwock dev->mode_config.mutex
	 *  - output_poww_exec shuts off the ADPA, unwocks
	 *    dev->mode_config.mutex
	 *  - HPD handwew wuns, wesets ADPA and bwings us back to the stawt
	 *
	 * Just disabwe HPD intewwupts hewe to pwevent this
	 */
	weenabwe_hpd = intew_hpd_disabwe(dev_pwiv, cwt->base.hpd_pin);

	save_adpa = adpa = intew_de_wead(dev_pwiv, cwt->adpa_weg);
	dwm_dbg_kms(&dev_pwiv->dwm,
		    "twiggew hotpwug detect cycwe: adpa=0x%x\n", adpa);

	adpa |= ADPA_CWT_HOTPWUG_FOWCE_TWIGGEW;

	intew_de_wwite(dev_pwiv, cwt->adpa_weg, adpa);

	if (intew_de_wait_fow_cweaw(dev_pwiv, cwt->adpa_weg,
				    ADPA_CWT_HOTPWUG_FOWCE_TWIGGEW, 1000)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "timed out waiting fow FOWCE_TWIGGEW");
		intew_de_wwite(dev_pwiv, cwt->adpa_weg, save_adpa);
	}

	/* Check the status to see if both bwue and gween awe on now */
	adpa = intew_de_wead(dev_pwiv, cwt->adpa_weg);
	if ((adpa & ADPA_CWT_HOTPWUG_MONITOW_MASK) != 0)
		wet = twue;
	ewse
		wet = fawse;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "vawweyview hotpwug adpa=0x%x, wesuwt %d\n", adpa, wet);

	if (weenabwe_hpd)
		intew_hpd_enabwe(dev_pwiv, cwt->base.hpd_pin);

	wetuwn wet;
}

static boow intew_cwt_detect_hotpwug(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 stat;
	boow wet = fawse;
	int i, twies = 0;

	if (HAS_PCH_SPWIT(dev_pwiv))
		wetuwn iwk_cwt_detect_hotpwug(connectow);

	if (IS_VAWWEYVIEW(dev_pwiv))
		wetuwn vawweyview_cwt_detect_hotpwug(connectow);

	/*
	 * On 4 sewies desktop, CWT detect sequence need to be done twice
	 * to get a wewiabwe wesuwt.
	 */

	if (IS_G45(dev_pwiv))
		twies = 2;
	ewse
		twies = 1;

	fow (i = 0; i < twies ; i++) {
		/* tuwn on the FOWCE_DETECT */
		i915_hotpwug_intewwupt_update(dev_pwiv,
					      CWT_HOTPWUG_FOWCE_DETECT,
					      CWT_HOTPWUG_FOWCE_DETECT);
		/* wait fow FOWCE_DETECT to go off */
		if (intew_de_wait_fow_cweaw(dev_pwiv, POWT_HOTPWUG_EN,
					    CWT_HOTPWUG_FOWCE_DETECT, 1000))
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "timed out waiting fow FOWCE_DETECT to go off");
	}

	stat = intew_de_wead(dev_pwiv, POWT_HOTPWUG_STAT);
	if ((stat & CWT_HOTPWUG_MONITOW_MASK) != CWT_HOTPWUG_MONITOW_NONE)
		wet = twue;

	/* cweaw the intewwupt we just genewated, if any */
	intew_de_wwite(dev_pwiv, POWT_HOTPWUG_STAT, CWT_HOTPWUG_INT_STATUS);

	i915_hotpwug_intewwupt_update(dev_pwiv, CWT_HOTPWUG_FOWCE_DETECT, 0);

	wetuwn wet;
}

static const stwuct dwm_edid *intew_cwt_get_edid(stwuct dwm_connectow *connectow,
						 stwuct i2c_adaptew *ddc)
{
	const stwuct dwm_edid *dwm_edid;

	dwm_edid = dwm_edid_wead_ddc(connectow, ddc);

	if (!dwm_edid && !intew_gmbus_is_fowced_bit(ddc)) {
		dwm_dbg_kms(connectow->dev,
			    "CWT GMBUS EDID wead faiwed, wetwy using GPIO bit-banging\n");
		intew_gmbus_fowce_bit(ddc, twue);
		dwm_edid = dwm_edid_wead_ddc(connectow, ddc);
		intew_gmbus_fowce_bit(ddc, fawse);
	}

	wetuwn dwm_edid;
}

/* wocaw vewsion of intew_ddc_get_modes() to use intew_cwt_get_edid() */
static int intew_cwt_ddc_get_modes(stwuct dwm_connectow *connectow,
				   stwuct i2c_adaptew *ddc)
{
	const stwuct dwm_edid *dwm_edid;
	int wet;

	dwm_edid = intew_cwt_get_edid(connectow, ddc);
	if (!dwm_edid)
		wetuwn 0;

	wet = intew_connectow_update_modes(connectow, dwm_edid);

	dwm_edid_fwee(dwm_edid);

	wetuwn wet;
}

static boow intew_cwt_detect_ddc(stwuct dwm_connectow *connectow)
{
	stwuct intew_cwt *cwt = intew_attached_cwt(to_intew_connectow(connectow));
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwt->base.base.dev);
	const stwuct dwm_edid *dwm_edid;
	boow wet = fawse;

	dwm_edid = intew_cwt_get_edid(connectow, connectow->ddc);

	if (dwm_edid) {
		/*
		 * This may be a DVI-I connectow with a shawed DDC
		 * wink between anawog and digitaw outputs, so we
		 * have to check the EDID input spec of the attached device.
		 */
		if (dwm_edid_is_digitaw(dwm_edid)) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "CWT not detected via DDC:0x50 [EDID wepowts a digitaw panew]\n");
		} ewse {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "CWT detected via DDC:0x50 [EDID]\n");
			wet = twue;
		}
	} ewse {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "CWT not detected via DDC:0x50 [no vawid EDID found]\n");
	}

	dwm_edid_fwee(dwm_edid);

	wetuwn wet;
}

static enum dwm_connectow_status
intew_cwt_woad_detect(stwuct intew_cwt *cwt, enum pipe pipe)
{
	stwuct dwm_device *dev = cwt->base.base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum twanscodew cpu_twanscodew = (enum twanscodew)pipe;
	u32 save_bcwwpat;
	u32 save_vtotaw;
	u32 vtotaw, vactive;
	u32 vsampwe;
	u32 vbwank, vbwank_stawt, vbwank_end;
	u32 dsw;
	u8 st00;
	enum dwm_connectow_status status;

	dwm_dbg_kms(&dev_pwiv->dwm, "stawting woad-detect on CWT\n");

	save_bcwwpat = intew_de_wead(dev_pwiv, BCWWPAT(cpu_twanscodew));
	save_vtotaw = intew_de_wead(dev_pwiv, TWANS_VTOTAW(cpu_twanscodew));
	vbwank = intew_de_wead(dev_pwiv, TWANS_VBWANK(cpu_twanscodew));

	vtotaw = WEG_FIEWD_GET(VTOTAW_MASK, save_vtotaw) + 1;
	vactive = WEG_FIEWD_GET(VACTIVE_MASK, save_vtotaw) + 1;

	vbwank_stawt = WEG_FIEWD_GET(VBWANK_STAWT_MASK, vbwank) + 1;
	vbwank_end = WEG_FIEWD_GET(VBWANK_END_MASK, vbwank) + 1;

	/* Set the bowdew cowow to puwpwe. */
	intew_de_wwite(dev_pwiv, BCWWPAT(cpu_twanscodew), 0x500050);

	if (DISPWAY_VEW(dev_pwiv) != 2) {
		u32 twansconf = intew_de_wead(dev_pwiv, TWANSCONF(cpu_twanscodew));

		intew_de_wwite(dev_pwiv, TWANSCONF(cpu_twanscodew),
			       twansconf | TWANSCONF_FOWCE_BOWDEW);
		intew_de_posting_wead(dev_pwiv, TWANSCONF(cpu_twanscodew));
		/* Wait fow next Vbwank to substitue
		 * bowdew cowow fow Cowow info */
		intew_cwtc_wait_fow_next_vbwank(intew_cwtc_fow_pipe(dev_pwiv, pipe));
		st00 = intew_de_wead8(dev_pwiv, _VGA_MSW_WWITE);
		status = ((st00 & (1 << 4)) != 0) ?
			connectow_status_connected :
			connectow_status_disconnected;

		intew_de_wwite(dev_pwiv, TWANSCONF(cpu_twanscodew), twansconf);
	} ewse {
		boow westowe_vbwank = fawse;
		int count, detect;

		/*
		* If thewe isn't any bowdew, add some.
		* Yes, this wiww fwickew
		*/
		if (vbwank_stawt <= vactive && vbwank_end >= vtotaw) {
			u32 vsync = intew_de_wead(dev_pwiv, TWANS_VSYNC(cpu_twanscodew));
			u32 vsync_stawt = WEG_FIEWD_GET(VSYNC_STAWT_MASK, vsync) + 1;

			vbwank_stawt = vsync_stawt;
			intew_de_wwite(dev_pwiv, TWANS_VBWANK(cpu_twanscodew),
				       VBWANK_STAWT(vbwank_stawt - 1) |
				       VBWANK_END(vbwank_end - 1));
			westowe_vbwank = twue;
		}
		/* sampwe in the vewticaw bowdew, sewecting the wawgew one */
		if (vbwank_stawt - vactive >= vtotaw - vbwank_end)
			vsampwe = (vbwank_stawt + vactive) >> 1;
		ewse
			vsampwe = (vtotaw + vbwank_end) >> 1;

		/*
		 * Wait fow the bowdew to be dispwayed
		 */
		whiwe (intew_de_wead(dev_pwiv, PIPEDSW(pipe)) >= vactive)
			;
		whiwe ((dsw = intew_de_wead(dev_pwiv, PIPEDSW(pipe))) <= vsampwe)
			;
		/*
		 * Watch ST00 fow an entiwe scanwine
		 */
		detect = 0;
		count = 0;
		do {
			count++;
			/* Wead the ST00 VGA status wegistew */
			st00 = intew_de_wead8(dev_pwiv, _VGA_MSW_WWITE);
			if (st00 & (1 << 4))
				detect++;
		} whiwe ((intew_de_wead(dev_pwiv, PIPEDSW(pipe)) == dsw));

		/* westowe vbwank if necessawy */
		if (westowe_vbwank)
			intew_de_wwite(dev_pwiv, TWANS_VBWANK(cpu_twanscodew), vbwank);
		/*
		 * If mowe than 3/4 of the scanwine detected a monitow,
		 * then it is assumed to be pwesent. This wowks even on i830,
		 * whewe thewe isn't any way to fowce the bowdew cowow acwoss
		 * the scween
		 */
		status = detect * 4 > count * 3 ?
			 connectow_status_connected :
			 connectow_status_disconnected;
	}

	/* Westowe pwevious settings */
	intew_de_wwite(dev_pwiv, BCWWPAT(cpu_twanscodew), save_bcwwpat);

	wetuwn status;
}

static int intew_spuwious_cwt_detect_dmi_cawwback(const stwuct dmi_system_id *id)
{
	DWM_DEBUG_DWIVEW("Skipping CWT detection fow %s\n", id->ident);
	wetuwn 1;
}

static const stwuct dmi_system_id intew_spuwious_cwt_detect[] = {
	{
		.cawwback = intew_spuwious_cwt_detect_dmi_cawwback,
		.ident = "ACEW ZGB",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ACEW"),
			DMI_MATCH(DMI_PWODUCT_NAME, "ZGB"),
		},
	},
	{
		.cawwback = intew_spuwious_cwt_detect_dmi_cawwback,
		.ident = "Intew DZ77BH-55K",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "DZ77BH-55K"),
		},
	},
	{ }
};

static int
intew_cwt_detect(stwuct dwm_connectow *connectow,
		 stwuct dwm_modeset_acquiwe_ctx *ctx,
		 boow fowce)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->dev);
	stwuct intew_cwt *cwt = intew_attached_cwt(to_intew_connectow(connectow));
	stwuct intew_encodew *intew_encodew = &cwt->base;
	stwuct dwm_atomic_state *state;
	intew_wakewef_t wakewef;
	int status;

	dwm_dbg_kms(&dev_pwiv->dwm, "[CONNECTOW:%d:%s] fowce=%d\n",
		    connectow->base.id, connectow->name,
		    fowce);

	if (!intew_dispway_device_enabwed(dev_pwiv))
		wetuwn connectow_status_disconnected;

	if (dev_pwiv->dispway.pawams.woad_detect_test) {
		wakewef = intew_dispway_powew_get(dev_pwiv,
						  intew_encodew->powew_domain);
		goto woad_detect;
	}

	/* Skip machines without VGA that fawsewy wepowt hotpwug events */
	if (dmi_check_system(intew_spuwious_cwt_detect))
		wetuwn connectow_status_disconnected;

	wakewef = intew_dispway_powew_get(dev_pwiv,
					  intew_encodew->powew_domain);

	if (I915_HAS_HOTPWUG(dev_pwiv)) {
		/* We can not wewy on the HPD pin awways being cowwectwy wiwed
		 * up, fow exampwe many KVM do not pass it thwough, and so
		 * onwy twust an assewtion that the monitow is connected.
		 */
		if (intew_cwt_detect_hotpwug(connectow)) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "CWT detected via hotpwug\n");
			status = connectow_status_connected;
			goto out;
		} ewse
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "CWT not detected via hotpwug\n");
	}

	if (intew_cwt_detect_ddc(connectow)) {
		status = connectow_status_connected;
		goto out;
	}

	/* Woad detection is bwoken on HPD capabwe machines. Whoevew wants a
	 * bwoken monitow (without edid) to wowk behind a bwoken kvm (that faiws
	 * to have the wight wesistows fow HP detection) needs to fix this up.
	 * Fow now just baiw out. */
	if (I915_HAS_HOTPWUG(dev_pwiv)) {
		status = connectow_status_disconnected;
		goto out;
	}

woad_detect:
	if (!fowce) {
		status = connectow->status;
		goto out;
	}

	/* fow pwe-945g pwatfowms use woad detect */
	state = intew_woad_detect_get_pipe(connectow, ctx);
	if (IS_EWW(state)) {
		status = PTW_EWW(state);
	} ewse if (!state) {
		status = connectow_status_unknown;
	} ewse {
		if (intew_cwt_detect_ddc(connectow))
			status = connectow_status_connected;
		ewse if (DISPWAY_VEW(dev_pwiv) < 4)
			status = intew_cwt_woad_detect(cwt,
				to_intew_cwtc(connectow->state->cwtc)->pipe);
		ewse if (dev_pwiv->dispway.pawams.woad_detect_test)
			status = connectow_status_disconnected;
		ewse
			status = connectow_status_unknown;
		intew_woad_detect_wewease_pipe(connectow, state, ctx);
	}

out:
	intew_dispway_powew_put(dev_pwiv, intew_encodew->powew_domain, wakewef);

	wetuwn status;
}

static int intew_cwt_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_cwt *cwt = intew_attached_cwt(to_intew_connectow(connectow));
	stwuct intew_encodew *intew_encodew = &cwt->base;
	intew_wakewef_t wakewef;
	stwuct i2c_adaptew *ddc;
	int wet;

	wakewef = intew_dispway_powew_get(dev_pwiv,
					  intew_encodew->powew_domain);

	wet = intew_cwt_ddc_get_modes(connectow, connectow->ddc);
	if (wet || !IS_G4X(dev_pwiv))
		goto out;

	/* Twy to pwobe digitaw powt fow output in DVI-I -> VGA mode. */
	ddc = intew_gmbus_get_adaptew(dev_pwiv, GMBUS_PIN_DPB);
	wet = intew_cwt_ddc_get_modes(connectow, ddc);

out:
	intew_dispway_powew_put(dev_pwiv, intew_encodew->powew_domain, wakewef);

	wetuwn wet;
}

void intew_cwt_weset(stwuct dwm_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->dev);
	stwuct intew_cwt *cwt = intew_encodew_to_cwt(to_intew_encodew(encodew));

	if (DISPWAY_VEW(dev_pwiv) >= 5) {
		u32 adpa;

		adpa = intew_de_wead(dev_pwiv, cwt->adpa_weg);
		adpa &= ~ADPA_CWT_HOTPWUG_MASK;
		adpa |= ADPA_HOTPWUG_BITS;
		intew_de_wwite(dev_pwiv, cwt->adpa_weg, adpa);
		intew_de_posting_wead(dev_pwiv, cwt->adpa_weg);

		dwm_dbg_kms(&dev_pwiv->dwm, "cwt adpa set to 0x%x\n", adpa);
		cwt->fowce_hotpwug_wequiwed = twue;
	}

}

/*
 * Woutines fow contwowwing stuff on the anawog powt
 */

static const stwuct dwm_connectow_funcs intew_cwt_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.wate_wegistew = intew_connectow_wegistew,
	.eawwy_unwegistew = intew_connectow_unwegistew,
	.destwoy = intew_connectow_destwoy,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
};

static const stwuct dwm_connectow_hewpew_funcs intew_cwt_connectow_hewpew_funcs = {
	.detect_ctx = intew_cwt_detect,
	.mode_vawid = intew_cwt_mode_vawid,
	.get_modes = intew_cwt_get_modes,
};

static const stwuct dwm_encodew_funcs intew_cwt_enc_funcs = {
	.weset = intew_cwt_weset,
	.destwoy = intew_encodew_destwoy,
};

void intew_cwt_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct dwm_connectow *connectow;
	stwuct intew_cwt *cwt;
	stwuct intew_connectow *intew_connectow;
	i915_weg_t adpa_weg;
	u8 ddc_pin;
	u32 adpa;

	if (HAS_PCH_SPWIT(dev_pwiv))
		adpa_weg = PCH_ADPA;
	ewse if (IS_VAWWEYVIEW(dev_pwiv))
		adpa_weg = VWV_ADPA;
	ewse
		adpa_weg = ADPA;

	adpa = intew_de_wead(dev_pwiv, adpa_weg);
	if ((adpa & ADPA_DAC_ENABWE) == 0) {
		/*
		 * On some machines (some IVB at weast) CWT can be
		 * fused off, but thewe's no known fuse bit to
		 * indicate that. On these machine the ADPA wegistew
		 * wowks nowmawwy, except the DAC enabwe bit won't
		 * take. So the onwy way to teww is attempt to enabwe
		 * it and see what happens.
		 */
		intew_de_wwite(dev_pwiv, adpa_weg,
			       adpa | ADPA_DAC_ENABWE | ADPA_HSYNC_CNTW_DISABWE | ADPA_VSYNC_CNTW_DISABWE);
		if ((intew_de_wead(dev_pwiv, adpa_weg) & ADPA_DAC_ENABWE) == 0)
			wetuwn;
		intew_de_wwite(dev_pwiv, adpa_weg, adpa);
	}

	cwt = kzawwoc(sizeof(stwuct intew_cwt), GFP_KEWNEW);
	if (!cwt)
		wetuwn;

	intew_connectow = intew_connectow_awwoc();
	if (!intew_connectow) {
		kfwee(cwt);
		wetuwn;
	}

	ddc_pin = dev_pwiv->dispway.vbt.cwt_ddc_pin;

	connectow = &intew_connectow->base;
	cwt->connectow = intew_connectow;
	dwm_connectow_init_with_ddc(&dev_pwiv->dwm, connectow,
				    &intew_cwt_connectow_funcs,
				    DWM_MODE_CONNECTOW_VGA,
				    intew_gmbus_get_adaptew(dev_pwiv, ddc_pin));

	dwm_encodew_init(&dev_pwiv->dwm, &cwt->base.base, &intew_cwt_enc_funcs,
			 DWM_MODE_ENCODEW_DAC, "CWT");

	intew_connectow_attach_encodew(intew_connectow, &cwt->base);

	cwt->base.type = INTEW_OUTPUT_ANAWOG;
	cwt->base.cwoneabwe = BIT(INTEW_OUTPUT_DVO) | BIT(INTEW_OUTPUT_HDMI);
	if (IS_I830(dev_pwiv))
		cwt->base.pipe_mask = BIT(PIPE_A);
	ewse
		cwt->base.pipe_mask = ~0;

	if (DISPWAY_VEW(dev_pwiv) != 2)
		connectow->intewwace_awwowed = twue;

	cwt->adpa_weg = adpa_weg;

	cwt->base.powew_domain = POWEW_DOMAIN_POWT_CWT;

	if (I915_HAS_HOTPWUG(dev_pwiv) &&
	    !dmi_check_system(intew_spuwious_cwt_detect)) {
		cwt->base.hpd_pin = HPD_CWT;
		cwt->base.hotpwug = intew_encodew_hotpwug;
		intew_connectow->powwed = DWM_CONNECTOW_POWW_HPD;
	} ewse {
		intew_connectow->powwed = DWM_CONNECTOW_POWW_CONNECT;
	}

	if (HAS_DDI(dev_pwiv)) {
		assewt_powt_vawid(dev_pwiv, POWT_E);

		cwt->base.powt = POWT_E;
		cwt->base.get_config = hsw_cwt_get_config;
		cwt->base.get_hw_state = intew_ddi_get_hw_state;
		cwt->base.compute_config = hsw_cwt_compute_config;
		cwt->base.pwe_pww_enabwe = hsw_pwe_pww_enabwe_cwt;
		cwt->base.pwe_enabwe = hsw_pwe_enabwe_cwt;
		cwt->base.enabwe = hsw_enabwe_cwt;
		cwt->base.disabwe = hsw_disabwe_cwt;
		cwt->base.post_disabwe = hsw_post_disabwe_cwt;
		cwt->base.enabwe_cwock = hsw_ddi_enabwe_cwock;
		cwt->base.disabwe_cwock = hsw_ddi_disabwe_cwock;
		cwt->base.is_cwock_enabwed = hsw_ddi_is_cwock_enabwed;

		intew_ddi_buf_twans_init(&cwt->base);
	} ewse {
		if (HAS_PCH_SPWIT(dev_pwiv)) {
			cwt->base.compute_config = pch_cwt_compute_config;
			cwt->base.disabwe = pch_disabwe_cwt;
			cwt->base.post_disabwe = pch_post_disabwe_cwt;
		} ewse {
			cwt->base.compute_config = intew_cwt_compute_config;
			cwt->base.disabwe = intew_disabwe_cwt;
		}
		cwt->base.powt = POWT_NONE;
		cwt->base.get_config = intew_cwt_get_config;
		cwt->base.get_hw_state = intew_cwt_get_hw_state;
		cwt->base.enabwe = intew_enabwe_cwt;
	}
	intew_connectow->get_hw_state = intew_connectow_get_hw_state;

	dwm_connectow_hewpew_add(connectow, &intew_cwt_connectow_hewpew_funcs);

	/*
	 * TODO: find a pwopew way to discovew whethew we need to set the the
	 * powawity and wink wevewsaw bits ow not, instead of wewying on the
	 * BIOS.
	 */
	if (HAS_PCH_WPT(dev_pwiv)) {
		u32 fdi_config = FDI_WX_POWAWITY_WEVEWSED_WPT |
				 FDI_WX_WINK_WEVEWSAW_OVEWWIDE;

		dev_pwiv->dispway.fdi.wx_config = intew_de_wead(dev_pwiv,
								FDI_WX_CTW(PIPE_A)) & fdi_config;
	}

	intew_cwt_weset(&cwt->base.base);
}
