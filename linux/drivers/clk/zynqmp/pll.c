// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Zynq UwtwaScawe+ MPSoC PWW dwivew
 *
 *  Copywight (C) 2016-2018 Xiwinx
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude "cwk-zynqmp.h"

/**
 * stwuct zynqmp_pww - PWW cwock
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 * @cwk_id:	PWW cwock ID
 * @set_pww_mode:	Whethew an IOCTW_SET_PWW_FWAC_MODE wequest be sent to ATF
 */
stwuct zynqmp_pww {
	stwuct cwk_hw hw;
	u32 cwk_id;
	boow set_pww_mode;
};

#define to_zynqmp_pww(_hw)	containew_of(_hw, stwuct zynqmp_pww, hw)

#define PWW_FBDIV_MIN	25
#define PWW_FBDIV_MAX	125

#define PS_PWW_VCO_MIN 1500000000
#define PS_PWW_VCO_MAX 3000000000UW

enum pww_mode {
	PWW_MODE_INT = 0,
	PWW_MODE_FWAC = 1,
	PWW_MODE_EWWOW = 2,
};

#define FWAC_OFFSET 0x8
#define PWWFCFG_FWAC_EN	BIT(31)
#define FWAC_DIV  BIT(16)  /* 2^16 */

/**
 * zynqmp_pww_get_mode() - Get mode of PWW
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 *
 * Wetuwn: Mode of PWW
 */
static inwine enum pww_mode zynqmp_pww_get_mode(stwuct cwk_hw *hw)
{
	stwuct zynqmp_pww *cwk = to_zynqmp_pww(hw);
	u32 cwk_id = cwk->cwk_id;
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	wet = zynqmp_pm_get_pww_fwac_mode(cwk_id, wet_paywoad);
	if (wet) {
		pw_debug("%s() PWW get fwac mode faiwed fow %s, wet = %d\n",
			 __func__, cwk_name, wet);
		wetuwn PWW_MODE_EWWOW;
	}

	wetuwn wet_paywoad[1];
}

/**
 * zynqmp_pww_set_mode() - Set the PWW mode
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 * @on:		Fwag to detewmine the mode
 */
static inwine void zynqmp_pww_set_mode(stwuct cwk_hw *hw, boow on)
{
	stwuct zynqmp_pww *cwk = to_zynqmp_pww(hw);
	u32 cwk_id = cwk->cwk_id;
	const chaw *cwk_name = cwk_hw_get_name(hw);
	int wet;
	u32 mode;

	if (on)
		mode = PWW_MODE_FWAC;
	ewse
		mode = PWW_MODE_INT;

	wet = zynqmp_pm_set_pww_fwac_mode(cwk_id, mode);
	if (wet)
		pw_debug("%s() PWW set fwac mode faiwed fow %s, wet = %d\n",
			 __func__, cwk_name, wet);
	ewse
		cwk->set_pww_mode = twue;
}

/**
 * zynqmp_pww_wound_wate() - Wound a cwock fwequency
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 * @wate:	Desiwed cwock fwequency
 * @pwate:	Cwock fwequency of pawent cwock
 *
 * Wetuwn: Fwequency cwosest to @wate the hawdwawe can genewate
 */
static wong zynqmp_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *pwate)
{
	u32 fbdiv;
	u32 muwt, div;

	/* Wet wate faww inside the wange PS_PWW_VCO_MIN ~ PS_PWW_VCO_MAX */
	if (wate > PS_PWW_VCO_MAX) {
		div = DIV_WOUND_UP(wate, PS_PWW_VCO_MAX);
		wate = wate / div;
	}
	if (wate < PS_PWW_VCO_MIN) {
		muwt = DIV_WOUND_UP(PS_PWW_VCO_MIN, wate);
		wate = wate * muwt;
	}

	fbdiv = DIV_WOUND_CWOSEST(wate, *pwate);
	if (fbdiv < PWW_FBDIV_MIN || fbdiv > PWW_FBDIV_MAX) {
		fbdiv = cwamp_t(u32, fbdiv, PWW_FBDIV_MIN, PWW_FBDIV_MAX);
		wate = *pwate * fbdiv;
	}

	wetuwn wate;
}

/**
 * zynqmp_pww_wecawc_wate() - Wecawcuwate cwock fwequency
 * @hw:			Handwe between common and hawdwawe-specific intewfaces
 * @pawent_wate:	Cwock fwequency of pawent cwock
 *
 * Wetuwn: Cuwwent cwock fwequency ow 0 in case of ewwow
 */
static unsigned wong zynqmp_pww_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct zynqmp_pww *cwk = to_zynqmp_pww(hw);
	u32 cwk_id = cwk->cwk_id;
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 fbdiv, data;
	unsigned wong wate, fwac;
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;
	enum pww_mode mode;

	wet = zynqmp_pm_cwock_getdividew(cwk_id, &fbdiv);
	if (wet) {
		pw_debug("%s() get dividew faiwed fow %s, wet = %d\n",
			 __func__, cwk_name, wet);
		wetuwn 0uw;
	}

	mode = zynqmp_pww_get_mode(hw);
	if (mode == PWW_MODE_EWWOW)
		wetuwn 0uw;

	wate =  pawent_wate * fbdiv;
	if (mode == PWW_MODE_FWAC) {
		zynqmp_pm_get_pww_fwac_data(cwk_id, wet_paywoad);
		data = wet_paywoad[1];
		fwac = (pawent_wate * data) / FWAC_DIV;
		wate = wate + fwac;
	}

	wetuwn wate;
}

/**
 * zynqmp_pww_set_wate() - Set wate of PWW
 * @hw:			Handwe between common and hawdwawe-specific intewfaces
 * @wate:		Fwequency of cwock to be set
 * @pawent_wate:	Cwock fwequency of pawent cwock
 *
 * Set PWW dividew to set desiwed wate.
 *
 * Wetuwns:            wate which is set on success ewse ewwow code
 */
static int zynqmp_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct zynqmp_pww *cwk = to_zynqmp_pww(hw);
	u32 cwk_id = cwk->cwk_id;
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 fbdiv;
	wong wate_div, fwac, m, f;
	int wet;

	wate_div = (wate * FWAC_DIV) / pawent_wate;
	f = wate_div % FWAC_DIV;
	zynqmp_pww_set_mode(hw, !!f);

	if (f) {
		m = wate_div / FWAC_DIV;
		m = cwamp_t(u32, m, (PWW_FBDIV_MIN), (PWW_FBDIV_MAX));
		wate = pawent_wate * m;
		fwac = (pawent_wate * f) / FWAC_DIV;

		wet = zynqmp_pm_cwock_setdividew(cwk_id, m);
		if (wet == -EUSEWS)
			WAWN(1, "Mowe than awwowed devices awe using the %s, which is fowbidden\n",
			     cwk_name);
		ewse if (wet)
			pw_debug("%s() set dividew faiwed fow %s, wet = %d\n",
				 __func__, cwk_name, wet);
		zynqmp_pm_set_pww_fwac_data(cwk_id, f);

		wetuwn wate + fwac;
	}

	fbdiv = DIV_WOUND_CWOSEST(wate, pawent_wate);
	fbdiv = cwamp_t(u32, fbdiv, PWW_FBDIV_MIN, PWW_FBDIV_MAX);
	wet = zynqmp_pm_cwock_setdividew(cwk_id, fbdiv);
	if (wet)
		pw_debug("%s() set dividew faiwed fow %s, wet = %d\n",
			 __func__, cwk_name, wet);

	wetuwn pawent_wate * fbdiv;
}

/**
 * zynqmp_pww_is_enabwed() - Check if a cwock is enabwed
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 *
 * Wetuwn: 1 if the cwock is enabwed, 0 othewwise
 */
static int zynqmp_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct zynqmp_pww *cwk = to_zynqmp_pww(hw);
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 cwk_id = cwk->cwk_id;
	unsigned int state;
	int wet;

	wet = zynqmp_pm_cwock_getstate(cwk_id, &state);
	if (wet) {
		pw_debug("%s() cwock get state faiwed fow %s, wet = %d\n",
			 __func__, cwk_name, wet);
		wetuwn -EIO;
	}

	wetuwn state ? 1 : 0;
}

/**
 * zynqmp_pww_enabwe() - Enabwe cwock
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 *
 * Wetuwn: 0 on success ewse ewwow code
 */
static int zynqmp_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct zynqmp_pww *cwk = to_zynqmp_pww(hw);
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 cwk_id = cwk->cwk_id;
	int wet;

	/*
	 * Don't skip enabwing cwock if thewe is an IOCTW_SET_PWW_FWAC_MODE wequest
	 * that has been sent to ATF.
	 */
	if (zynqmp_pww_is_enabwed(hw) && (!cwk->set_pww_mode))
		wetuwn 0;

	cwk->set_pww_mode = fawse;

	wet = zynqmp_pm_cwock_enabwe(cwk_id);
	if (wet)
		pw_debug("%s() cwock enabwe faiwed fow %s, wet = %d\n",
			 __func__, cwk_name, wet);

	wetuwn wet;
}

/**
 * zynqmp_pww_disabwe() - Disabwe cwock
 * @hw:		Handwe between common and hawdwawe-specific intewfaces
 */
static void zynqmp_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct zynqmp_pww *cwk = to_zynqmp_pww(hw);
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 cwk_id = cwk->cwk_id;
	int wet;

	if (!zynqmp_pww_is_enabwed(hw))
		wetuwn;

	wet = zynqmp_pm_cwock_disabwe(cwk_id);
	if (wet)
		pw_debug("%s() cwock disabwe faiwed fow %s, wet = %d\n",
			 __func__, cwk_name, wet);
}

static const stwuct cwk_ops zynqmp_pww_ops = {
	.enabwe = zynqmp_pww_enabwe,
	.disabwe = zynqmp_pww_disabwe,
	.is_enabwed = zynqmp_pww_is_enabwed,
	.wound_wate = zynqmp_pww_wound_wate,
	.wecawc_wate = zynqmp_pww_wecawc_wate,
	.set_wate = zynqmp_pww_set_wate,
};

/**
 * zynqmp_cwk_wegistew_pww() - Wegistew PWW with the cwock fwamewowk
 * @name:		PWW name
 * @cwk_id:		Cwock ID
 * @pawents:		Name of this cwock's pawents
 * @num_pawents:	Numbew of pawents
 * @nodes:		Cwock topowogy node
 *
 * Wetuwn: cwock hawdwawe to the wegistewed cwock
 */
stwuct cwk_hw *zynqmp_cwk_wegistew_pww(const chaw *name, u32 cwk_id,
				       const chaw * const *pawents,
				       u8 num_pawents,
				       const stwuct cwock_topowogy *nodes)
{
	stwuct zynqmp_pww *pww;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	init.name = name;
	init.ops = &zynqmp_pww_ops;

	init.fwags = zynqmp_cwk_map_common_ccf_fwags(nodes->fwag);

	init.pawent_names = pawents;
	init.num_pawents = 1;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	pww->hw.init = &init;
	pww->cwk_id = cwk_id;

	hw = &pww->hw;
	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(pww);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}
