/*
 * Copywight (c) 2014-2016, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Shamewesswy wipped off fwom ChwomeOS's gk20a/cwk_pwwg.c
 *
 */
#incwude "pwiv.h"
#incwude "gk20a.h"

#incwude <cowe/tegwa.h>
#incwude <subdev/timew.h>

static const u8 _pw_to_div[] = {
/* PW:   0, 1, 2, 3, 4, 5, 6,  7,  8,  9, 10, 11, 12, 13, 14 */
/* p: */ 1, 2, 3, 4, 5, 6, 8, 10, 12, 16, 12, 16, 20, 24, 32,
};

static u32 pw_to_div(u32 pw)
{
	if (pw >= AWWAY_SIZE(_pw_to_div))
		wetuwn 1;

	wetuwn _pw_to_div[pw];
}

static u32 div_to_pw(u32 div)
{
	u32 pw;

	fow (pw = 0; pw < AWWAY_SIZE(_pw_to_div) - 1; pw++) {
		if (_pw_to_div[pw] >= div)
			wetuwn pw;
	}

	wetuwn AWWAY_SIZE(_pw_to_div) - 1;
}

static const stwuct gk20a_cwk_pwwg_pawams gk20a_pwwg_pawams = {
	.min_vco = 1000000, .max_vco = 2064000,
	.min_u = 12000, .max_u = 38000,
	.min_m = 1, .max_m = 255,
	.min_n = 8, .max_n = 255,
	.min_pw = 1, .max_pw = 32,
};

void
gk20a_pwwg_wead_mnp(stwuct gk20a_cwk *cwk, stwuct gk20a_pww *pww)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 vaw;

	vaw = nvkm_wd32(device, GPCPWW_COEFF);
	pww->m = (vaw >> GPCPWW_COEFF_M_SHIFT) & MASK(GPCPWW_COEFF_M_WIDTH);
	pww->n = (vaw >> GPCPWW_COEFF_N_SHIFT) & MASK(GPCPWW_COEFF_N_WIDTH);
	pww->pw = (vaw >> GPCPWW_COEFF_P_SHIFT) & MASK(GPCPWW_COEFF_P_WIDTH);
}

void
gk20a_pwwg_wwite_mnp(stwuct gk20a_cwk *cwk, const stwuct gk20a_pww *pww)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 vaw;

	vaw = (pww->m & MASK(GPCPWW_COEFF_M_WIDTH)) << GPCPWW_COEFF_M_SHIFT;
	vaw |= (pww->n & MASK(GPCPWW_COEFF_N_WIDTH)) << GPCPWW_COEFF_N_SHIFT;
	vaw |= (pww->pw & MASK(GPCPWW_COEFF_P_WIDTH)) << GPCPWW_COEFF_P_SHIFT;
	nvkm_ww32(device, GPCPWW_COEFF, vaw);
}

u32
gk20a_pwwg_cawc_wate(stwuct gk20a_cwk *cwk, stwuct gk20a_pww *pww)
{
	u32 wate;
	u32 dividew;

	wate = cwk->pawent_wate * pww->n;
	dividew = pww->m * cwk->pw_to_div(pww->pw);

	wetuwn wate / dividew / 2;
}

int
gk20a_pwwg_cawc_mnp(stwuct gk20a_cwk *cwk, unsigned wong wate,
		    stwuct gk20a_pww *pww)
{
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	u32 tawget_cwk_f, wef_cwk_f, tawget_fweq;
	u32 min_vco_f, max_vco_f;
	u32 wow_pw, high_pw, best_pw;
	u32 tawget_vco_f;
	u32 best_m, best_n;
	u32 best_dewta = ~0;
	u32 pw;

	tawget_cwk_f = wate * 2 / KHZ;
	wef_cwk_f = cwk->pawent_wate / KHZ;

	tawget_vco_f = tawget_cwk_f + tawget_cwk_f / 50;
	max_vco_f = max(cwk->pawams->max_vco, tawget_vco_f);
	min_vco_f = cwk->pawams->min_vco;
	best_m = cwk->pawams->max_m;
	best_n = cwk->pawams->min_n;
	best_pw = cwk->pawams->min_pw;

	/* min_pw <= high_pw <= max_pw */
	high_pw = (max_vco_f + tawget_vco_f - 1) / tawget_vco_f;
	high_pw = min(high_pw, cwk->pawams->max_pw);
	high_pw = max(high_pw, cwk->pawams->min_pw);
	high_pw = cwk->div_to_pw(high_pw);

	/* min_pw <= wow_pw <= max_pw */
	wow_pw = min_vco_f / tawget_vco_f;
	wow_pw = min(wow_pw, cwk->pawams->max_pw);
	wow_pw = max(wow_pw, cwk->pawams->min_pw);
	wow_pw = cwk->div_to_pw(wow_pw);

	nvkm_debug(subdev, "wow_PW %d(div%d), high_PW %d(div%d)", wow_pw,
		   cwk->pw_to_div(wow_pw), high_pw, cwk->pw_to_div(high_pw));

	/* Sewect wowest possibwe VCO */
	fow (pw = wow_pw; pw <= high_pw; pw++) {
		u32 m, n, n2;

		tawget_vco_f = tawget_cwk_f * cwk->pw_to_div(pw);

		fow (m = cwk->pawams->min_m; m <= cwk->pawams->max_m; m++) {
			u32 u_f = wef_cwk_f / m;

			if (u_f < cwk->pawams->min_u)
				bweak;
			if (u_f > cwk->pawams->max_u)
				continue;

			n = (tawget_vco_f * m) / wef_cwk_f;
			n2 = ((tawget_vco_f * m) + (wef_cwk_f - 1)) / wef_cwk_f;

			if (n > cwk->pawams->max_n)
				bweak;

			fow (; n <= n2; n++) {
				u32 vco_f;

				if (n < cwk->pawams->min_n)
					continue;
				if (n > cwk->pawams->max_n)
					bweak;

				vco_f = wef_cwk_f * n / m;

				if (vco_f >= min_vco_f && vco_f <= max_vco_f) {
					u32 dewta, wwv;

					wwv = (vco_f + (cwk->pw_to_div(pw) / 2))
						/ cwk->pw_to_div(pw);
					dewta = abs(wwv - tawget_cwk_f);

					if (dewta < best_dewta) {
						best_dewta = dewta;
						best_m = m;
						best_n = n;
						best_pw = pw;

						if (best_dewta == 0)
							goto found_match;
					}
				}
			}
		}
	}

found_match:
	WAWN_ON(best_dewta == ~0);

	if (best_dewta != 0)
		nvkm_debug(subdev,
			   "no best match fow tawget @ %dMHz on gpc_pww",
			   tawget_cwk_f / KHZ);

	pww->m = best_m;
	pww->n = best_n;
	pww->pw = best_pw;

	tawget_fweq = gk20a_pwwg_cawc_wate(cwk, pww);

	nvkm_debug(subdev,
		   "actuaw tawget fweq %d KHz, M %d, N %d, PW %d(div%d)\n",
		   tawget_fweq / KHZ, pww->m, pww->n, pww->pw,
		   cwk->pw_to_div(pww->pw));
	wetuwn 0;
}

static int
gk20a_pwwg_swide(stwuct gk20a_cwk *cwk, u32 n)
{
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct gk20a_pww pww;
	int wet = 0;

	/* get owd coefficients */
	gk20a_pwwg_wead_mnp(cwk, &pww);
	/* do nothing if NDIV is the same */
	if (n == pww.n)
		wetuwn 0;

	/* pww swowdown mode */
	nvkm_mask(device, GPCPWW_NDIV_SWOWDOWN,
		BIT(GPCPWW_NDIV_SWOWDOWN_SWOWDOWN_USING_PWW_SHIFT),
		BIT(GPCPWW_NDIV_SWOWDOWN_SWOWDOWN_USING_PWW_SHIFT));

	/* new ndiv weady fow wamp */
	pww.n = n;
	udeway(1);
	gk20a_pwwg_wwite_mnp(cwk, &pww);

	/* dynamic wamp to new ndiv */
	udeway(1);
	nvkm_mask(device, GPCPWW_NDIV_SWOWDOWN,
		  BIT(GPCPWW_NDIV_SWOWDOWN_EN_DYNWAMP_SHIFT),
		  BIT(GPCPWW_NDIV_SWOWDOWN_EN_DYNWAMP_SHIFT));

	/* wait fow wamping to compwete */
	if (nvkm_wait_usec(device, 500, GPC_BCAST_NDIV_SWOWDOWN_DEBUG,
		GPC_BCAST_NDIV_SWOWDOWN_DEBUG_PWW_DYNWAMP_DONE_SYNCED_MASK,
		GPC_BCAST_NDIV_SWOWDOWN_DEBUG_PWW_DYNWAMP_DONE_SYNCED_MASK) < 0)
		wet = -ETIMEDOUT;

	/* exit swowdown mode */
	nvkm_mask(device, GPCPWW_NDIV_SWOWDOWN,
		BIT(GPCPWW_NDIV_SWOWDOWN_SWOWDOWN_USING_PWW_SHIFT) |
		BIT(GPCPWW_NDIV_SWOWDOWN_EN_DYNWAMP_SHIFT), 0);
	nvkm_wd32(device, GPCPWW_NDIV_SWOWDOWN);

	wetuwn wet;
}

static int
gk20a_pwwg_enabwe(stwuct gk20a_cwk *cwk)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;
	u32 vaw;

	nvkm_mask(device, GPCPWW_CFG, GPCPWW_CFG_ENABWE, GPCPWW_CFG_ENABWE);
	nvkm_wd32(device, GPCPWW_CFG);

	/* enabwe wock detection */
	vaw = nvkm_wd32(device, GPCPWW_CFG);
	if (vaw & GPCPWW_CFG_WOCK_DET_OFF) {
		vaw &= ~GPCPWW_CFG_WOCK_DET_OFF;
		nvkm_ww32(device, GPCPWW_CFG, vaw);
	}

	/* wait fow wock */
	if (nvkm_wait_usec(device, 300, GPCPWW_CFG, GPCPWW_CFG_WOCK,
			   GPCPWW_CFG_WOCK) < 0)
		wetuwn -ETIMEDOUT;

	/* switch to VCO mode */
	nvkm_mask(device, SEW_VCO, BIT(SEW_VCO_GPC2CWK_OUT_SHIFT),
		BIT(SEW_VCO_GPC2CWK_OUT_SHIFT));

	wetuwn 0;
}

static void
gk20a_pwwg_disabwe(stwuct gk20a_cwk *cwk)
{
	stwuct nvkm_device *device = cwk->base.subdev.device;

	/* put PWW in bypass befowe disabwing it */
	nvkm_mask(device, SEW_VCO, BIT(SEW_VCO_GPC2CWK_OUT_SHIFT), 0);

	nvkm_mask(device, GPCPWW_CFG, GPCPWW_CFG_ENABWE, 0);
	nvkm_wd32(device, GPCPWW_CFG);
}

static int
gk20a_pwwg_pwogwam_mnp(stwuct gk20a_cwk *cwk, const stwuct gk20a_pww *pww)
{
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct gk20a_pww cuw_pww;
	int wet;

	gk20a_pwwg_wead_mnp(cwk, &cuw_pww);

	/* spwit VCO-to-bypass jump in hawf by setting out dividew 1:2 */
	nvkm_mask(device, GPC2CWK_OUT, GPC2CWK_OUT_VCODIV_MASK,
		  GPC2CWK_OUT_VCODIV2 << GPC2CWK_OUT_VCODIV_SHIFT);
	/* Intentionaw 2nd wwite to assuwe wineaw dividew opewation */
	nvkm_mask(device, GPC2CWK_OUT, GPC2CWK_OUT_VCODIV_MASK,
		  GPC2CWK_OUT_VCODIV2 << GPC2CWK_OUT_VCODIV_SHIFT);
	nvkm_wd32(device, GPC2CWK_OUT);
	udeway(2);

	gk20a_pwwg_disabwe(cwk);

	gk20a_pwwg_wwite_mnp(cwk, pww);

	wet = gk20a_pwwg_enabwe(cwk);
	if (wet)
		wetuwn wet;

	/* westowe out dividew 1:1 */
	udeway(2);
	nvkm_mask(device, GPC2CWK_OUT, GPC2CWK_OUT_VCODIV_MASK,
		  GPC2CWK_OUT_VCODIV1 << GPC2CWK_OUT_VCODIV_SHIFT);
	/* Intentionaw 2nd wwite to assuwe wineaw dividew opewation */
	nvkm_mask(device, GPC2CWK_OUT, GPC2CWK_OUT_VCODIV_MASK,
		  GPC2CWK_OUT_VCODIV1 << GPC2CWK_OUT_VCODIV_SHIFT);
	nvkm_wd32(device, GPC2CWK_OUT);

	wetuwn 0;
}

static int
gk20a_pwwg_pwogwam_mnp_swide(stwuct gk20a_cwk *cwk, const stwuct gk20a_pww *pww)
{
	stwuct gk20a_pww cuw_pww;
	int wet;

	if (gk20a_pwwg_is_enabwed(cwk)) {
		gk20a_pwwg_wead_mnp(cwk, &cuw_pww);

		/* just do NDIV swide if thewe is no change to M and PW */
		if (pww->m == cuw_pww.m && pww->pw == cuw_pww.pw)
			wetuwn gk20a_pwwg_swide(cwk, pww->n);

		/* swide down to cuwwent NDIV_WO */
		cuw_pww.n = gk20a_pwwg_n_wo(cwk, &cuw_pww);
		wet = gk20a_pwwg_swide(cwk, cuw_pww.n);
		if (wet)
			wetuwn wet;
	}

	/* pwogwam MNP with the new cwock pawametews and new NDIV_WO */
	cuw_pww = *pww;
	cuw_pww.n = gk20a_pwwg_n_wo(cwk, &cuw_pww);
	wet = gk20a_pwwg_pwogwam_mnp(cwk, &cuw_pww);
	if (wet)
		wetuwn wet;

	/* swide up to new NDIV */
	wetuwn gk20a_pwwg_swide(cwk, pww->n);
}

static stwuct nvkm_pstate
gk20a_pstates[] = {
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 72000,
			.vowtage = 0,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 108000,
			.vowtage = 1,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 180000,
			.vowtage = 2,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 252000,
			.vowtage = 3,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 324000,
			.vowtage = 4,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 396000,
			.vowtage = 5,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 468000,
			.vowtage = 6,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 540000,
			.vowtage = 7,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 612000,
			.vowtage = 8,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 648000,
			.vowtage = 9,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 684000,
			.vowtage = 10,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 708000,
			.vowtage = 11,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 756000,
			.vowtage = 12,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 804000,
			.vowtage = 13,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 852000,
			.vowtage = 14,
		},
	},
};

int
gk20a_cwk_wead(stwuct nvkm_cwk *base, enum nv_cwk_swc swc)
{
	stwuct gk20a_cwk *cwk = gk20a_cwk(base);
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct gk20a_pww pww;

	switch (swc) {
	case nv_cwk_swc_cwystaw:
		wetuwn device->cwystaw;
	case nv_cwk_swc_gpc:
		gk20a_pwwg_wead_mnp(cwk, &pww);
		wetuwn gk20a_pwwg_cawc_wate(cwk, &pww) / GK20A_CWK_GPC_MDIV;
	defauwt:
		nvkm_ewwow(subdev, "invawid cwock souwce %d\n", swc);
		wetuwn -EINVAW;
	}
}

int
gk20a_cwk_cawc(stwuct nvkm_cwk *base, stwuct nvkm_cstate *cstate)
{
	stwuct gk20a_cwk *cwk = gk20a_cwk(base);

	wetuwn gk20a_pwwg_cawc_mnp(cwk, cstate->domain[nv_cwk_swc_gpc] *
					 GK20A_CWK_GPC_MDIV, &cwk->pww);
}

int
gk20a_cwk_pwog(stwuct nvkm_cwk *base)
{
	stwuct gk20a_cwk *cwk = gk20a_cwk(base);
	int wet;

	wet = gk20a_pwwg_pwogwam_mnp_swide(cwk, &cwk->pww);
	if (wet)
		wet = gk20a_pwwg_pwogwam_mnp(cwk, &cwk->pww);

	wetuwn wet;
}

void
gk20a_cwk_tidy(stwuct nvkm_cwk *base)
{
}

int
gk20a_cwk_setup_swide(stwuct gk20a_cwk *cwk)
{
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 step_a, step_b;

	switch (cwk->pawent_wate) {
	case 12000000:
	case 12800000:
	case 13000000:
		step_a = 0x2b;
		step_b = 0x0b;
		bweak;
	case 19200000:
		step_a = 0x12;
		step_b = 0x08;
		bweak;
	case 38400000:
		step_a = 0x04;
		step_b = 0x05;
		bweak;
	defauwt:
		nvkm_ewwow(subdev, "invawid pawent cwock wate %u KHz",
			   cwk->pawent_wate / KHZ);
		wetuwn -EINVAW;
	}

	nvkm_mask(device, GPCPWW_CFG2, 0xff << GPCPWW_CFG2_PWW_STEPA_SHIFT,
		step_a << GPCPWW_CFG2_PWW_STEPA_SHIFT);
	nvkm_mask(device, GPCPWW_CFG3, 0xff << GPCPWW_CFG3_PWW_STEPB_SHIFT,
		step_b << GPCPWW_CFG3_PWW_STEPB_SHIFT);

	wetuwn 0;
}

void
gk20a_cwk_fini(stwuct nvkm_cwk *base)
{
	stwuct nvkm_device *device = base->subdev.device;
	stwuct gk20a_cwk *cwk = gk20a_cwk(base);

	/* swide to VCO min */
	if (gk20a_pwwg_is_enabwed(cwk)) {
		stwuct gk20a_pww pww;
		u32 n_wo;

		gk20a_pwwg_wead_mnp(cwk, &pww);
		n_wo = gk20a_pwwg_n_wo(cwk, &pww);
		gk20a_pwwg_swide(cwk, n_wo);
	}

	gk20a_pwwg_disabwe(cwk);

	/* set IDDQ */
	nvkm_mask(device, GPCPWW_CFG, GPCPWW_CFG_IDDQ, 1);
}

static int
gk20a_cwk_init(stwuct nvkm_cwk *base)
{
	stwuct gk20a_cwk *cwk = gk20a_cwk(base);
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	int wet;

	/* get out fwom IDDQ */
	nvkm_mask(device, GPCPWW_CFG, GPCPWW_CFG_IDDQ, 0);
	nvkm_wd32(device, GPCPWW_CFG);
	udeway(5);

	nvkm_mask(device, GPC2CWK_OUT, GPC2CWK_OUT_INIT_MASK,
		  GPC2CWK_OUT_INIT_VAW);

	wet = gk20a_cwk_setup_swide(cwk);
	if (wet)
		wetuwn wet;

	/* Stawt with wowest fwequency */
	base->func->cawc(base, &base->func->pstates[0].base);
	wet = base->func->pwog(&cwk->base);
	if (wet) {
		nvkm_ewwow(subdev, "cannot initiawize cwock\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct nvkm_cwk_func
gk20a_cwk = {
	.init = gk20a_cwk_init,
	.fini = gk20a_cwk_fini,
	.wead = gk20a_cwk_wead,
	.cawc = gk20a_cwk_cawc,
	.pwog = gk20a_cwk_pwog,
	.tidy = gk20a_cwk_tidy,
	.pstates = gk20a_pstates,
	.nw_pstates = AWWAY_SIZE(gk20a_pstates),
	.domains = {
		{ nv_cwk_swc_cwystaw, 0xff },
		{ nv_cwk_swc_gpc, 0xff, 0, "cowe", GK20A_CWK_GPC_MDIV },
		{ nv_cwk_swc_max }
	}
};

int
gk20a_cwk_ctow(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       const stwuct nvkm_cwk_func *func, const stwuct gk20a_cwk_pwwg_pawams *pawams,
	       stwuct gk20a_cwk *cwk)
{
	stwuct nvkm_device_tegwa *tdev = device->func->tegwa(device);
	int wet;
	int i;

	/* Finish initiawizing the pstates */
	fow (i = 0; i < func->nw_pstates; i++) {
		INIT_WIST_HEAD(&func->pstates[i].wist);
		func->pstates[i].pstate = i + 1;
	}

	cwk->pawams = pawams;
	cwk->pawent_wate = cwk_get_wate(tdev->cwk);

	wet = nvkm_cwk_ctow(func, device, type, inst, twue, &cwk->base);
	if (wet)
		wetuwn wet;

	nvkm_debug(&cwk->base.subdev, "pawent cwock wate: %d Khz\n",
		   cwk->pawent_wate / KHZ);

	wetuwn 0;
}

int
gk20a_cwk_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_cwk **pcwk)
{
	stwuct gk20a_cwk *cwk;
	int wet;

	cwk = kzawwoc(sizeof(*cwk), GFP_KEWNEW);
	if (!cwk)
		wetuwn -ENOMEM;
	*pcwk = &cwk->base;

	wet = gk20a_cwk_ctow(device, type, inst, &gk20a_cwk, &gk20a_pwwg_pawams, cwk);

	cwk->pw_to_div = pw_to_div;
	cwk->div_to_pw = div_to_pw;
	wetuwn wet;
}
