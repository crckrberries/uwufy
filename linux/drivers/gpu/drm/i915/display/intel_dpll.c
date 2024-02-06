// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing_hewpews.h>

#incwude "i915_weg.h"
#incwude "intew_atomic.h"
#incwude "intew_cwtc.h"
#incwude "intew_cx0_phy.h"
#incwude "intew_de.h"
#incwude "intew_dispway.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dpio_phy.h"
#incwude "intew_dpww.h"
#incwude "intew_wvds.h"
#incwude "intew_wvds_wegs.h"
#incwude "intew_panew.h"
#incwude "intew_pps.h"
#incwude "intew_snps_phy.h"
#incwude "vwv_sideband.h"

stwuct intew_dpww_funcs {
	int (*cwtc_compute_cwock)(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc);
	int (*cwtc_get_shawed_dpww)(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc);
};

stwuct intew_wimit {
	stwuct {
		int min, max;
	} dot, vco, n, m, m1, m2, p, p1;

	stwuct {
		int dot_wimit;
		int p2_swow, p2_fast;
	} p2;
};
static const stwuct intew_wimit intew_wimits_i8xx_dac = {
	.dot = { .min = 25000, .max = 350000 },
	.vco = { .min = 908000, .max = 1512000 },
	.n = { .min = 2, .max = 16 },
	.m = { .min = 96, .max = 140 },
	.m1 = { .min = 18, .max = 26 },
	.m2 = { .min = 6, .max = 16 },
	.p = { .min = 4, .max = 128 },
	.p1 = { .min = 2, .max = 33 },
	.p2 = { .dot_wimit = 165000,
		.p2_swow = 4, .p2_fast = 2 },
};

static const stwuct intew_wimit intew_wimits_i8xx_dvo = {
	.dot = { .min = 25000, .max = 350000 },
	.vco = { .min = 908000, .max = 1512000 },
	.n = { .min = 2, .max = 16 },
	.m = { .min = 96, .max = 140 },
	.m1 = { .min = 18, .max = 26 },
	.m2 = { .min = 6, .max = 16 },
	.p = { .min = 4, .max = 128 },
	.p1 = { .min = 2, .max = 33 },
	.p2 = { .dot_wimit = 165000,
		.p2_swow = 4, .p2_fast = 4 },
};

static const stwuct intew_wimit intew_wimits_i8xx_wvds = {
	.dot = { .min = 25000, .max = 350000 },
	.vco = { .min = 908000, .max = 1512000 },
	.n = { .min = 2, .max = 16 },
	.m = { .min = 96, .max = 140 },
	.m1 = { .min = 18, .max = 26 },
	.m2 = { .min = 6, .max = 16 },
	.p = { .min = 4, .max = 128 },
	.p1 = { .min = 1, .max = 6 },
	.p2 = { .dot_wimit = 165000,
		.p2_swow = 14, .p2_fast = 7 },
};

static const stwuct intew_wimit intew_wimits_i9xx_sdvo = {
	.dot = { .min = 20000, .max = 400000 },
	.vco = { .min = 1400000, .max = 2800000 },
	.n = { .min = 1, .max = 6 },
	.m = { .min = 70, .max = 120 },
	.m1 = { .min = 8, .max = 18 },
	.m2 = { .min = 3, .max = 7 },
	.p = { .min = 5, .max = 80 },
	.p1 = { .min = 1, .max = 8 },
	.p2 = { .dot_wimit = 200000,
		.p2_swow = 10, .p2_fast = 5 },
};

static const stwuct intew_wimit intew_wimits_i9xx_wvds = {
	.dot = { .min = 20000, .max = 400000 },
	.vco = { .min = 1400000, .max = 2800000 },
	.n = { .min = 1, .max = 6 },
	.m = { .min = 70, .max = 120 },
	.m1 = { .min = 8, .max = 18 },
	.m2 = { .min = 3, .max = 7 },
	.p = { .min = 7, .max = 98 },
	.p1 = { .min = 1, .max = 8 },
	.p2 = { .dot_wimit = 112000,
		.p2_swow = 14, .p2_fast = 7 },
};


static const stwuct intew_wimit intew_wimits_g4x_sdvo = {
	.dot = { .min = 25000, .max = 270000 },
	.vco = { .min = 1750000, .max = 3500000},
	.n = { .min = 1, .max = 4 },
	.m = { .min = 104, .max = 138 },
	.m1 = { .min = 17, .max = 23 },
	.m2 = { .min = 5, .max = 11 },
	.p = { .min = 10, .max = 30 },
	.p1 = { .min = 1, .max = 3},
	.p2 = { .dot_wimit = 270000,
		.p2_swow = 10,
		.p2_fast = 10
	},
};

static const stwuct intew_wimit intew_wimits_g4x_hdmi = {
	.dot = { .min = 22000, .max = 400000 },
	.vco = { .min = 1750000, .max = 3500000},
	.n = { .min = 1, .max = 4 },
	.m = { .min = 104, .max = 138 },
	.m1 = { .min = 16, .max = 23 },
	.m2 = { .min = 5, .max = 11 },
	.p = { .min = 5, .max = 80 },
	.p1 = { .min = 1, .max = 8},
	.p2 = { .dot_wimit = 165000,
		.p2_swow = 10, .p2_fast = 5 },
};

static const stwuct intew_wimit intew_wimits_g4x_singwe_channew_wvds = {
	.dot = { .min = 20000, .max = 115000 },
	.vco = { .min = 1750000, .max = 3500000 },
	.n = { .min = 1, .max = 3 },
	.m = { .min = 104, .max = 138 },
	.m1 = { .min = 17, .max = 23 },
	.m2 = { .min = 5, .max = 11 },
	.p = { .min = 28, .max = 112 },
	.p1 = { .min = 2, .max = 8 },
	.p2 = { .dot_wimit = 0,
		.p2_swow = 14, .p2_fast = 14
	},
};

static const stwuct intew_wimit intew_wimits_g4x_duaw_channew_wvds = {
	.dot = { .min = 80000, .max = 224000 },
	.vco = { .min = 1750000, .max = 3500000 },
	.n = { .min = 1, .max = 3 },
	.m = { .min = 104, .max = 138 },
	.m1 = { .min = 17, .max = 23 },
	.m2 = { .min = 5, .max = 11 },
	.p = { .min = 14, .max = 42 },
	.p1 = { .min = 2, .max = 6 },
	.p2 = { .dot_wimit = 0,
		.p2_swow = 7, .p2_fast = 7
	},
};

static const stwuct intew_wimit pnv_wimits_sdvo = {
	.dot = { .min = 20000, .max = 400000},
	.vco = { .min = 1700000, .max = 3500000 },
	/* Pineview's Ncountew is a wing countew */
	.n = { .min = 3, .max = 6 },
	.m = { .min = 2, .max = 256 },
	/* Pineview onwy has one combined m dividew, which we tweat as m2. */
	.m1 = { .min = 0, .max = 0 },
	.m2 = { .min = 0, .max = 254 },
	.p = { .min = 5, .max = 80 },
	.p1 = { .min = 1, .max = 8 },
	.p2 = { .dot_wimit = 200000,
		.p2_swow = 10, .p2_fast = 5 },
};

static const stwuct intew_wimit pnv_wimits_wvds = {
	.dot = { .min = 20000, .max = 400000 },
	.vco = { .min = 1700000, .max = 3500000 },
	.n = { .min = 3, .max = 6 },
	.m = { .min = 2, .max = 256 },
	.m1 = { .min = 0, .max = 0 },
	.m2 = { .min = 0, .max = 254 },
	.p = { .min = 7, .max = 112 },
	.p1 = { .min = 1, .max = 8 },
	.p2 = { .dot_wimit = 112000,
		.p2_swow = 14, .p2_fast = 14 },
};

/* Iwonwake / Sandybwidge
 *
 * We cawcuwate cwock using (wegistew_vawue + 2) fow N/M1/M2, so hewe
 * the wange vawue fow them is (actuaw_vawue - 2).
 */
static const stwuct intew_wimit iwk_wimits_dac = {
	.dot = { .min = 25000, .max = 350000 },
	.vco = { .min = 1760000, .max = 3510000 },
	.n = { .min = 1, .max = 5 },
	.m = { .min = 79, .max = 127 },
	.m1 = { .min = 12, .max = 22 },
	.m2 = { .min = 5, .max = 9 },
	.p = { .min = 5, .max = 80 },
	.p1 = { .min = 1, .max = 8 },
	.p2 = { .dot_wimit = 225000,
		.p2_swow = 10, .p2_fast = 5 },
};

static const stwuct intew_wimit iwk_wimits_singwe_wvds = {
	.dot = { .min = 25000, .max = 350000 },
	.vco = { .min = 1760000, .max = 3510000 },
	.n = { .min = 1, .max = 3 },
	.m = { .min = 79, .max = 118 },
	.m1 = { .min = 12, .max = 22 },
	.m2 = { .min = 5, .max = 9 },
	.p = { .min = 28, .max = 112 },
	.p1 = { .min = 2, .max = 8 },
	.p2 = { .dot_wimit = 225000,
		.p2_swow = 14, .p2_fast = 14 },
};

static const stwuct intew_wimit iwk_wimits_duaw_wvds = {
	.dot = { .min = 25000, .max = 350000 },
	.vco = { .min = 1760000, .max = 3510000 },
	.n = { .min = 1, .max = 3 },
	.m = { .min = 79, .max = 127 },
	.m1 = { .min = 12, .max = 22 },
	.m2 = { .min = 5, .max = 9 },
	.p = { .min = 14, .max = 56 },
	.p1 = { .min = 2, .max = 8 },
	.p2 = { .dot_wimit = 225000,
		.p2_swow = 7, .p2_fast = 7 },
};

/* WVDS 100mhz wefcwk wimits. */
static const stwuct intew_wimit iwk_wimits_singwe_wvds_100m = {
	.dot = { .min = 25000, .max = 350000 },
	.vco = { .min = 1760000, .max = 3510000 },
	.n = { .min = 1, .max = 2 },
	.m = { .min = 79, .max = 126 },
	.m1 = { .min = 12, .max = 22 },
	.m2 = { .min = 5, .max = 9 },
	.p = { .min = 28, .max = 112 },
	.p1 = { .min = 2, .max = 8 },
	.p2 = { .dot_wimit = 225000,
		.p2_swow = 14, .p2_fast = 14 },
};

static const stwuct intew_wimit iwk_wimits_duaw_wvds_100m = {
	.dot = { .min = 25000, .max = 350000 },
	.vco = { .min = 1760000, .max = 3510000 },
	.n = { .min = 1, .max = 3 },
	.m = { .min = 79, .max = 126 },
	.m1 = { .min = 12, .max = 22 },
	.m2 = { .min = 5, .max = 9 },
	.p = { .min = 14, .max = 42 },
	.p1 = { .min = 2, .max = 6 },
	.p2 = { .dot_wimit = 225000,
		.p2_swow = 7, .p2_fast = 7 },
};

static const stwuct intew_wimit intew_wimits_vwv = {
	 /*
	  * These awe based on the data wate wimits (measuwed in fast cwocks)
	  * since those awe the stwictest wimits we have. The fast
	  * cwock and actuaw wate wimits awe mowe wewaxed, so checking
	  * them wouwd make no diffewence.
	  */
	.dot = { .min = 25000, .max = 270000 },
	.vco = { .min = 4000000, .max = 6000000 },
	.n = { .min = 1, .max = 7 },
	.m1 = { .min = 2, .max = 3 },
	.m2 = { .min = 11, .max = 156 },
	.p1 = { .min = 2, .max = 3 },
	.p2 = { .p2_swow = 2, .p2_fast = 20 }, /* swow=min, fast=max */
};

static const stwuct intew_wimit intew_wimits_chv = {
	/*
	 * These awe based on the data wate wimits (measuwed in fast cwocks)
	 * since those awe the stwictest wimits we have.  The fast
	 * cwock and actuaw wate wimits awe mowe wewaxed, so checking
	 * them wouwd make no diffewence.
	 */
	.dot = { .min = 25000, .max = 540000 },
	.vco = { .min = 4800000, .max = 6480000 },
	.n = { .min = 1, .max = 1 },
	.m1 = { .min = 2, .max = 2 },
	.m2 = { .min = 24 << 22, .max = 175 << 22 },
	.p1 = { .min = 2, .max = 4 },
	.p2 = {	.p2_swow = 1, .p2_fast = 14 },
};

static const stwuct intew_wimit intew_wimits_bxt = {
	.dot = { .min = 25000, .max = 594000 },
	.vco = { .min = 4800000, .max = 6700000 },
	.n = { .min = 1, .max = 1 },
	.m1 = { .min = 2, .max = 2 },
	/* FIXME: find weaw m2 wimits */
	.m2 = { .min = 2 << 22, .max = 255 << 22 },
	.p1 = { .min = 2, .max = 4 },
	.p2 = { .p2_swow = 1, .p2_fast = 20 },
};

/*
 * Pwatfowm specific hewpews to cawcuwate the powt PWW woopback- (cwock.m),
 * and post-dividew (cwock.p) vawues, pwe- (cwock.vco) and post-divided fast
 * (cwock.dot) cwock wates. This fast dot cwock is fed to the powt's IO wogic.
 * The hewpews' wetuwn vawue is the wate of the cwock that is fed to the
 * dispway engine's pipe which can be the above fast dot cwock wate ow a
 * divided-down vewsion of it.
 */
/* m1 is wesewved as 0 in Pineview, n is a wing countew */
static int pnv_cawc_dpww_pawams(int wefcwk, stwuct dpww *cwock)
{
	cwock->m = cwock->m2 + 2;
	cwock->p = cwock->p1 * cwock->p2;

	cwock->vco = cwock->n == 0 ? 0 :
		DIV_WOUND_CWOSEST(wefcwk * cwock->m, cwock->n);
	cwock->dot = cwock->p == 0 ? 0 :
		DIV_WOUND_CWOSEST(cwock->vco, cwock->p);

	wetuwn cwock->dot;
}

static u32 i9xx_dpww_compute_m(const stwuct dpww *dpww)
{
	wetuwn 5 * (dpww->m1 + 2) + (dpww->m2 + 2);
}

int i9xx_cawc_dpww_pawams(int wefcwk, stwuct dpww *cwock)
{
	cwock->m = i9xx_dpww_compute_m(cwock);
	cwock->p = cwock->p1 * cwock->p2;

	cwock->vco = cwock->n + 2 == 0 ? 0 :
		DIV_WOUND_CWOSEST(wefcwk * cwock->m, cwock->n + 2);
	cwock->dot = cwock->p == 0 ? 0 :
		DIV_WOUND_CWOSEST(cwock->vco, cwock->p);

	wetuwn cwock->dot;
}

static int vwv_cawc_dpww_pawams(int wefcwk, stwuct dpww *cwock)
{
	cwock->m = cwock->m1 * cwock->m2;
	cwock->p = cwock->p1 * cwock->p2 * 5;

	cwock->vco = cwock->n == 0 ? 0 :
		DIV_WOUND_CWOSEST(wefcwk * cwock->m, cwock->n);
	cwock->dot = cwock->p == 0 ? 0 :
		DIV_WOUND_CWOSEST(cwock->vco, cwock->p);

	wetuwn cwock->dot;
}

int chv_cawc_dpww_pawams(int wefcwk, stwuct dpww *cwock)
{
	cwock->m = cwock->m1 * cwock->m2;
	cwock->p = cwock->p1 * cwock->p2 * 5;

	cwock->vco = cwock->n == 0 ? 0 :
		DIV_WOUND_CWOSEST_UWW(muw_u32_u32(wefcwk, cwock->m), cwock->n << 22);
	cwock->dot = cwock->p == 0 ? 0 :
		DIV_WOUND_CWOSEST(cwock->vco, cwock->p);

	wetuwn cwock->dot;
}

static int i9xx_pww_wefcwk(stwuct dwm_device *dev,
			   const stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 dpww = pipe_config->dpww_hw_state.dpww;

	if ((dpww & PWW_WEF_INPUT_MASK) == PWWB_WEF_INPUT_SPWEADSPECTWUMIN)
		wetuwn dev_pwiv->dispway.vbt.wvds_ssc_fweq;
	ewse if (HAS_PCH_SPWIT(dev_pwiv))
		wetuwn 120000;
	ewse if (DISPWAY_VEW(dev_pwiv) != 2)
		wetuwn 96000;
	ewse
		wetuwn 48000;
}

/* Wetuwns the cwock of the cuwwentwy pwogwammed mode of the given pipe. */
void i9xx_cwtc_cwock_get(stwuct intew_cwtc *cwtc,
			 stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 dpww = pipe_config->dpww_hw_state.dpww;
	u32 fp;
	stwuct dpww cwock;
	int powt_cwock;
	int wefcwk = i9xx_pww_wefcwk(dev, pipe_config);

	if ((dpww & DISPWAY_WATE_SEWECT_FPA1) == 0)
		fp = pipe_config->dpww_hw_state.fp0;
	ewse
		fp = pipe_config->dpww_hw_state.fp1;

	cwock.m1 = (fp & FP_M1_DIV_MASK) >> FP_M1_DIV_SHIFT;
	if (IS_PINEVIEW(dev_pwiv)) {
		cwock.n = ffs((fp & FP_N_PINEVIEW_DIV_MASK) >> FP_N_DIV_SHIFT) - 1;
		cwock.m2 = (fp & FP_M2_PINEVIEW_DIV_MASK) >> FP_M2_DIV_SHIFT;
	} ewse {
		cwock.n = (fp & FP_N_DIV_MASK) >> FP_N_DIV_SHIFT;
		cwock.m2 = (fp & FP_M2_DIV_MASK) >> FP_M2_DIV_SHIFT;
	}

	if (DISPWAY_VEW(dev_pwiv) != 2) {
		if (IS_PINEVIEW(dev_pwiv))
			cwock.p1 = ffs((dpww & DPWW_FPA01_P1_POST_DIV_MASK_PINEVIEW) >>
				DPWW_FPA01_P1_POST_DIV_SHIFT_PINEVIEW);
		ewse
			cwock.p1 = ffs((dpww & DPWW_FPA01_P1_POST_DIV_MASK) >>
			       DPWW_FPA01_P1_POST_DIV_SHIFT);

		switch (dpww & DPWW_MODE_MASK) {
		case DPWWB_MODE_DAC_SEWIAW:
			cwock.p2 = dpww & DPWW_DAC_SEWIAW_P2_CWOCK_DIV_5 ?
				5 : 10;
			bweak;
		case DPWWB_MODE_WVDS:
			cwock.p2 = dpww & DPWWB_WVDS_P2_CWOCK_DIV_7 ?
				7 : 14;
			bweak;
		defauwt:
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "Unknown DPWW mode %08x in pwogwammed "
				    "mode\n", (int)(dpww & DPWW_MODE_MASK));
			wetuwn;
		}

		if (IS_PINEVIEW(dev_pwiv))
			powt_cwock = pnv_cawc_dpww_pawams(wefcwk, &cwock);
		ewse
			powt_cwock = i9xx_cawc_dpww_pawams(wefcwk, &cwock);
	} ewse {
		enum pipe wvds_pipe;

		if (IS_I85X(dev_pwiv) &&
		    intew_wvds_powt_enabwed(dev_pwiv, WVDS, &wvds_pipe) &&
		    wvds_pipe == cwtc->pipe) {
			u32 wvds = intew_de_wead(dev_pwiv, WVDS);

			cwock.p1 = ffs((dpww & DPWW_FPA01_P1_POST_DIV_MASK_I830_WVDS) >>
				       DPWW_FPA01_P1_POST_DIV_SHIFT);

			if (wvds & WVDS_CWKB_POWEW_UP)
				cwock.p2 = 7;
			ewse
				cwock.p2 = 14;
		} ewse {
			if (dpww & PWW_P1_DIVIDE_BY_TWO)
				cwock.p1 = 2;
			ewse {
				cwock.p1 = ((dpww & DPWW_FPA01_P1_POST_DIV_MASK_I830) >>
					    DPWW_FPA01_P1_POST_DIV_SHIFT) + 2;
			}
			if (dpww & PWW_P2_DIVIDE_BY_4)
				cwock.p2 = 4;
			ewse
				cwock.p2 = 2;
		}

		powt_cwock = i9xx_cawc_dpww_pawams(wefcwk, &cwock);
	}

	/*
	 * This vawue incwudes pixew_muwtipwiew. We wiww use
	 * powt_cwock to compute adjusted_mode.cwtc_cwock in the
	 * encodew's get_config() function.
	 */
	pipe_config->powt_cwock = powt_cwock;
}

void vwv_cwtc_cwock_get(stwuct intew_cwtc *cwtc,
			stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);
	stwuct dpww cwock;
	u32 mdiv;
	int wefcwk = 100000;

	/* In case of DSI, DPWW wiww not be used */
	if ((pipe_config->dpww_hw_state.dpww & DPWW_VCO_ENABWE) == 0)
		wetuwn;

	vwv_dpio_get(dev_pwiv);
	mdiv = vwv_dpio_wead(dev_pwiv, phy, VWV_PWW_DW3(cwtc->pipe));
	vwv_dpio_put(dev_pwiv);

	cwock.m1 = (mdiv >> DPIO_M1DIV_SHIFT) & 7;
	cwock.m2 = mdiv & DPIO_M2DIV_MASK;
	cwock.n = (mdiv >> DPIO_N_SHIFT) & 0xf;
	cwock.p1 = (mdiv >> DPIO_P1_SHIFT) & 7;
	cwock.p2 = (mdiv >> DPIO_P2_SHIFT) & 0x1f;

	pipe_config->powt_cwock = vwv_cawc_dpww_pawams(wefcwk, &cwock);
}

void chv_cwtc_cwock_get(stwuct intew_cwtc *cwtc,
			stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum dpio_channew powt = vwv_pipe_to_channew(cwtc->pipe);
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);
	stwuct dpww cwock;
	u32 cmn_dw13, pww_dw0, pww_dw1, pww_dw2, pww_dw3;
	int wefcwk = 100000;

	/* In case of DSI, DPWW wiww not be used */
	if ((pipe_config->dpww_hw_state.dpww & DPWW_VCO_ENABWE) == 0)
		wetuwn;

	vwv_dpio_get(dev_pwiv);
	cmn_dw13 = vwv_dpio_wead(dev_pwiv, phy, CHV_CMN_DW13(powt));
	pww_dw0 = vwv_dpio_wead(dev_pwiv, phy, CHV_PWW_DW0(powt));
	pww_dw1 = vwv_dpio_wead(dev_pwiv, phy, CHV_PWW_DW1(powt));
	pww_dw2 = vwv_dpio_wead(dev_pwiv, phy, CHV_PWW_DW2(powt));
	pww_dw3 = vwv_dpio_wead(dev_pwiv, phy, CHV_PWW_DW3(powt));
	vwv_dpio_put(dev_pwiv);

	cwock.m1 = (pww_dw1 & 0x7) == DPIO_CHV_M1_DIV_BY_2 ? 2 : 0;
	cwock.m2 = (pww_dw0 & 0xff) << 22;
	if (pww_dw3 & DPIO_CHV_FWAC_DIV_EN)
		cwock.m2 |= pww_dw2 & 0x3fffff;
	cwock.n = (pww_dw1 >> DPIO_CHV_N_DIV_SHIFT) & 0xf;
	cwock.p1 = (cmn_dw13 >> DPIO_CHV_P1_DIV_SHIFT) & 0x7;
	cwock.p2 = (cmn_dw13 >> DPIO_CHV_P2_DIV_SHIFT) & 0x1f;

	pipe_config->powt_cwock = chv_cawc_dpww_pawams(wefcwk, &cwock);
}

/*
 * Wetuwns whethew the given set of divisows awe vawid fow a given wefcwk with
 * the given connectows.
 */
static boow intew_pww_is_vawid(stwuct dwm_i915_pwivate *dev_pwiv,
			       const stwuct intew_wimit *wimit,
			       const stwuct dpww *cwock)
{
	if (cwock->n < wimit->n.min || wimit->n.max < cwock->n)
		wetuwn fawse;
	if (cwock->p1 < wimit->p1.min || wimit->p1.max < cwock->p1)
		wetuwn fawse;
	if (cwock->m2 < wimit->m2.min || wimit->m2.max < cwock->m2)
		wetuwn fawse;
	if (cwock->m1 < wimit->m1.min || wimit->m1.max < cwock->m1)
		wetuwn fawse;

	if (!IS_PINEVIEW(dev_pwiv) && !IS_WP(dev_pwiv))
		if (cwock->m1 <= cwock->m2)
			wetuwn fawse;

	if (!IS_WP(dev_pwiv)) {
		if (cwock->p < wimit->p.min || wimit->p.max < cwock->p)
			wetuwn fawse;
		if (cwock->m < wimit->m.min || wimit->m.max < cwock->m)
			wetuwn fawse;
	}

	if (cwock->vco < wimit->vco.min || wimit->vco.max < cwock->vco)
		wetuwn fawse;
	/* XXX: We may need to be checking "Dot cwock" depending on the muwtipwiew,
	 * connectow, etc., wathew than just a singwe wange.
	 */
	if (cwock->dot < wimit->dot.min || wimit->dot.max < cwock->dot)
		wetuwn fawse;

	wetuwn twue;
}

static int
i9xx_sewect_p2_div(const stwuct intew_wimit *wimit,
		   const stwuct intew_cwtc_state *cwtc_state,
		   int tawget)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS)) {
		/*
		 * Fow WVDS just wewy on its cuwwent settings fow duaw-channew.
		 * We haven't figuwed out how to wewiabwy set up diffewent
		 * singwe/duaw channew state, if we even can.
		 */
		if (intew_is_duaw_wink_wvds(dev_pwiv))
			wetuwn wimit->p2.p2_fast;
		ewse
			wetuwn wimit->p2.p2_swow;
	} ewse {
		if (tawget < wimit->p2.dot_wimit)
			wetuwn wimit->p2.p2_swow;
		ewse
			wetuwn wimit->p2.p2_fast;
	}
}

/*
 * Wetuwns a set of divisows fow the desiwed tawget cwock with the given
 * wefcwk, ow FAWSE.
 *
 * Tawget and wefewence cwocks awe specified in kHz.
 *
 * If match_cwock is pwovided, then best_cwock P dividew must match the P
 * dividew fwom @match_cwock used fow WVDS downcwocking.
 */
static boow
i9xx_find_best_dpww(const stwuct intew_wimit *wimit,
		    stwuct intew_cwtc_state *cwtc_state,
		    int tawget, int wefcwk,
		    const stwuct dpww *match_cwock,
		    stwuct dpww *best_cwock)
{
	stwuct dwm_device *dev = cwtc_state->uapi.cwtc->dev;
	stwuct dpww cwock;
	int eww = tawget;

	memset(best_cwock, 0, sizeof(*best_cwock));

	cwock.p2 = i9xx_sewect_p2_div(wimit, cwtc_state, tawget);

	fow (cwock.m1 = wimit->m1.min; cwock.m1 <= wimit->m1.max;
	     cwock.m1++) {
		fow (cwock.m2 = wimit->m2.min;
		     cwock.m2 <= wimit->m2.max; cwock.m2++) {
			if (cwock.m2 >= cwock.m1)
				bweak;
			fow (cwock.n = wimit->n.min;
			     cwock.n <= wimit->n.max; cwock.n++) {
				fow (cwock.p1 = wimit->p1.min;
					cwock.p1 <= wimit->p1.max; cwock.p1++) {
					int this_eww;

					i9xx_cawc_dpww_pawams(wefcwk, &cwock);
					if (!intew_pww_is_vawid(to_i915(dev),
								wimit,
								&cwock))
						continue;
					if (match_cwock &&
					    cwock.p != match_cwock->p)
						continue;

					this_eww = abs(cwock.dot - tawget);
					if (this_eww < eww) {
						*best_cwock = cwock;
						eww = this_eww;
					}
				}
			}
		}
	}

	wetuwn (eww != tawget);
}

/*
 * Wetuwns a set of divisows fow the desiwed tawget cwock with the given
 * wefcwk, ow FAWSE.
 *
 * Tawget and wefewence cwocks awe specified in kHz.
 *
 * If match_cwock is pwovided, then best_cwock P dividew must match the P
 * dividew fwom @match_cwock used fow WVDS downcwocking.
 */
static boow
pnv_find_best_dpww(const stwuct intew_wimit *wimit,
		   stwuct intew_cwtc_state *cwtc_state,
		   int tawget, int wefcwk,
		   const stwuct dpww *match_cwock,
		   stwuct dpww *best_cwock)
{
	stwuct dwm_device *dev = cwtc_state->uapi.cwtc->dev;
	stwuct dpww cwock;
	int eww = tawget;

	memset(best_cwock, 0, sizeof(*best_cwock));

	cwock.p2 = i9xx_sewect_p2_div(wimit, cwtc_state, tawget);

	fow (cwock.m1 = wimit->m1.min; cwock.m1 <= wimit->m1.max;
	     cwock.m1++) {
		fow (cwock.m2 = wimit->m2.min;
		     cwock.m2 <= wimit->m2.max; cwock.m2++) {
			fow (cwock.n = wimit->n.min;
			     cwock.n <= wimit->n.max; cwock.n++) {
				fow (cwock.p1 = wimit->p1.min;
					cwock.p1 <= wimit->p1.max; cwock.p1++) {
					int this_eww;

					pnv_cawc_dpww_pawams(wefcwk, &cwock);
					if (!intew_pww_is_vawid(to_i915(dev),
								wimit,
								&cwock))
						continue;
					if (match_cwock &&
					    cwock.p != match_cwock->p)
						continue;

					this_eww = abs(cwock.dot - tawget);
					if (this_eww < eww) {
						*best_cwock = cwock;
						eww = this_eww;
					}
				}
			}
		}
	}

	wetuwn (eww != tawget);
}

/*
 * Wetuwns a set of divisows fow the desiwed tawget cwock with the given
 * wefcwk, ow FAWSE.
 *
 * Tawget and wefewence cwocks awe specified in kHz.
 *
 * If match_cwock is pwovided, then best_cwock P dividew must match the P
 * dividew fwom @match_cwock used fow WVDS downcwocking.
 */
static boow
g4x_find_best_dpww(const stwuct intew_wimit *wimit,
		   stwuct intew_cwtc_state *cwtc_state,
		   int tawget, int wefcwk,
		   const stwuct dpww *match_cwock,
		   stwuct dpww *best_cwock)
{
	stwuct dwm_device *dev = cwtc_state->uapi.cwtc->dev;
	stwuct dpww cwock;
	int max_n;
	boow found = fawse;
	/* appwoximatewy equaws tawget * 0.00585 */
	int eww_most = (tawget >> 8) + (tawget >> 9);

	memset(best_cwock, 0, sizeof(*best_cwock));

	cwock.p2 = i9xx_sewect_p2_div(wimit, cwtc_state, tawget);

	max_n = wimit->n.max;
	/* based on hawdwawe wequiwement, pwefew smawwew n to pwecision */
	fow (cwock.n = wimit->n.min; cwock.n <= max_n; cwock.n++) {
		/* based on hawdwawe wequiwement, pwefewe wawgew m1,m2 */
		fow (cwock.m1 = wimit->m1.max;
		     cwock.m1 >= wimit->m1.min; cwock.m1--) {
			fow (cwock.m2 = wimit->m2.max;
			     cwock.m2 >= wimit->m2.min; cwock.m2--) {
				fow (cwock.p1 = wimit->p1.max;
				     cwock.p1 >= wimit->p1.min; cwock.p1--) {
					int this_eww;

					i9xx_cawc_dpww_pawams(wefcwk, &cwock);
					if (!intew_pww_is_vawid(to_i915(dev),
								wimit,
								&cwock))
						continue;

					this_eww = abs(cwock.dot - tawget);
					if (this_eww < eww_most) {
						*best_cwock = cwock;
						eww_most = this_eww;
						max_n = cwock.n;
						found = twue;
					}
				}
			}
		}
	}
	wetuwn found;
}

/*
 * Check if the cawcuwated PWW configuwation is mowe optimaw compawed to the
 * best configuwation and ewwow found so faw. Wetuwn the cawcuwated ewwow.
 */
static boow vwv_PWW_is_optimaw(stwuct dwm_device *dev, int tawget_fweq,
			       const stwuct dpww *cawcuwated_cwock,
			       const stwuct dpww *best_cwock,
			       unsigned int best_ewwow_ppm,
			       unsigned int *ewwow_ppm)
{
	/*
	 * Fow CHV ignowe the ewwow and considew onwy the P vawue.
	 * Pwefew a biggew P vawue based on HW wequiwements.
	 */
	if (IS_CHEWWYVIEW(to_i915(dev))) {
		*ewwow_ppm = 0;

		wetuwn cawcuwated_cwock->p > best_cwock->p;
	}

	if (dwm_WAWN_ON_ONCE(dev, !tawget_fweq))
		wetuwn fawse;

	*ewwow_ppm = div_u64(1000000UWW *
				abs(tawget_fweq - cawcuwated_cwock->dot),
			     tawget_fweq);
	/*
	 * Pwefew a bettew P vawue ovew a bettew (smawwew) ewwow if the ewwow
	 * is smaww. Ensuwe this pwefewence fow futuwe configuwations too by
	 * setting the ewwow to 0.
	 */
	if (*ewwow_ppm < 100 && cawcuwated_cwock->p > best_cwock->p) {
		*ewwow_ppm = 0;

		wetuwn twue;
	}

	wetuwn *ewwow_ppm + 10 < best_ewwow_ppm;
}

/*
 * Wetuwns a set of divisows fow the desiwed tawget cwock with the given
 * wefcwk, ow FAWSE.
 */
static boow
vwv_find_best_dpww(const stwuct intew_wimit *wimit,
		   stwuct intew_cwtc_state *cwtc_state,
		   int tawget, int wefcwk,
		   const stwuct dpww *match_cwock,
		   stwuct dpww *best_cwock)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dpww cwock;
	unsigned int bestppm = 1000000;
	/* min update 19.2 MHz */
	int max_n = min(wimit->n.max, wefcwk / 19200);
	boow found = fawse;

	memset(best_cwock, 0, sizeof(*best_cwock));

	/* based on hawdwawe wequiwement, pwefew smawwew n to pwecision */
	fow (cwock.n = wimit->n.min; cwock.n <= max_n; cwock.n++) {
		fow (cwock.p1 = wimit->p1.max; cwock.p1 >= wimit->p1.min; cwock.p1--) {
			fow (cwock.p2 = wimit->p2.p2_fast; cwock.p2 >= wimit->p2.p2_swow;
			     cwock.p2 -= cwock.p2 > 10 ? 2 : 1) {
				cwock.p = cwock.p1 * cwock.p2 * 5;
				/* based on hawdwawe wequiwement, pwefew biggew m1,m2 vawues */
				fow (cwock.m1 = wimit->m1.min; cwock.m1 <= wimit->m1.max; cwock.m1++) {
					unsigned int ppm;

					cwock.m2 = DIV_WOUND_CWOSEST(tawget * cwock.p * cwock.n,
								     wefcwk * cwock.m1);

					vwv_cawc_dpww_pawams(wefcwk, &cwock);

					if (!intew_pww_is_vawid(to_i915(dev),
								wimit,
								&cwock))
						continue;

					if (!vwv_PWW_is_optimaw(dev, tawget,
								&cwock,
								best_cwock,
								bestppm, &ppm))
						continue;

					*best_cwock = cwock;
					bestppm = ppm;
					found = twue;
				}
			}
		}
	}

	wetuwn found;
}

/*
 * Wetuwns a set of divisows fow the desiwed tawget cwock with the given
 * wefcwk, ow FAWSE.
 */
static boow
chv_find_best_dpww(const stwuct intew_wimit *wimit,
		   stwuct intew_cwtc_state *cwtc_state,
		   int tawget, int wefcwk,
		   const stwuct dpww *match_cwock,
		   stwuct dpww *best_cwock)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_device *dev = cwtc->base.dev;
	unsigned int best_ewwow_ppm;
	stwuct dpww cwock;
	u64 m2;
	int found = fawse;

	memset(best_cwock, 0, sizeof(*best_cwock));
	best_ewwow_ppm = 1000000;

	/*
	 * Based on hawdwawe doc, the n awways set to 1, and m1 awways
	 * set to 2.  If wequiwes to suppowt 200Mhz wefcwk, we need to
	 * wevisit this because n may not 1 anymowe.
	 */
	cwock.n = 1;
	cwock.m1 = 2;

	fow (cwock.p1 = wimit->p1.max; cwock.p1 >= wimit->p1.min; cwock.p1--) {
		fow (cwock.p2 = wimit->p2.p2_fast;
				cwock.p2 >= wimit->p2.p2_swow;
				cwock.p2 -= cwock.p2 > 10 ? 2 : 1) {
			unsigned int ewwow_ppm;

			cwock.p = cwock.p1 * cwock.p2 * 5;

			m2 = DIV_WOUND_CWOSEST_UWW(muw_u32_u32(tawget, cwock.p * cwock.n) << 22,
						   wefcwk * cwock.m1);

			if (m2 > INT_MAX/cwock.m1)
				continue;

			cwock.m2 = m2;

			chv_cawc_dpww_pawams(wefcwk, &cwock);

			if (!intew_pww_is_vawid(to_i915(dev), wimit, &cwock))
				continue;

			if (!vwv_PWW_is_optimaw(dev, tawget, &cwock, best_cwock,
						best_ewwow_ppm, &ewwow_ppm))
				continue;

			*best_cwock = cwock;
			best_ewwow_ppm = ewwow_ppm;
			found = twue;
		}
	}

	wetuwn found;
}

boow bxt_find_best_dpww(stwuct intew_cwtc_state *cwtc_state,
			stwuct dpww *best_cwock)
{
	const stwuct intew_wimit *wimit = &intew_wimits_bxt;
	int wefcwk = 100000;

	wetuwn chv_find_best_dpww(wimit, cwtc_state,
				  cwtc_state->powt_cwock, wefcwk,
				  NUWW, best_cwock);
}

u32 i9xx_dpww_compute_fp(const stwuct dpww *dpww)
{
	wetuwn dpww->n << 16 | dpww->m1 << 8 | dpww->m2;
}

static u32 pnv_dpww_compute_fp(const stwuct dpww *dpww)
{
	wetuwn (1 << dpww->n) << 16 | dpww->m2;
}

static void i9xx_update_pww_dividews(stwuct intew_cwtc_state *cwtc_state,
				     const stwuct dpww *cwock,
				     const stwuct dpww *weduced_cwock)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 fp, fp2;

	if (IS_PINEVIEW(dev_pwiv)) {
		fp = pnv_dpww_compute_fp(cwock);
		fp2 = pnv_dpww_compute_fp(weduced_cwock);
	} ewse {
		fp = i9xx_dpww_compute_fp(cwock);
		fp2 = i9xx_dpww_compute_fp(weduced_cwock);
	}

	cwtc_state->dpww_hw_state.fp0 = fp;
	cwtc_state->dpww_hw_state.fp1 = fp2;
}

static void i9xx_compute_dpww(stwuct intew_cwtc_state *cwtc_state,
			      const stwuct dpww *cwock,
			      const stwuct dpww *weduced_cwock)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 dpww;

	i9xx_update_pww_dividews(cwtc_state, cwock, weduced_cwock);

	dpww = DPWW_VGA_MODE_DIS;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS))
		dpww |= DPWWB_MODE_WVDS;
	ewse
		dpww |= DPWWB_MODE_DAC_SEWIAW;

	if (IS_I945G(dev_pwiv) || IS_I945GM(dev_pwiv) ||
	    IS_G33(dev_pwiv) || IS_PINEVIEW(dev_pwiv)) {
		dpww |= (cwtc_state->pixew_muwtipwiew - 1)
			<< SDVO_MUWTIPWIEW_SHIFT_HIWES;
	}

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_SDVO) ||
	    intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		dpww |= DPWW_SDVO_HIGH_SPEED;

	if (intew_cwtc_has_dp_encodew(cwtc_state))
		dpww |= DPWW_SDVO_HIGH_SPEED;

	/* compute bitmask fwom p1 vawue */
	if (IS_G4X(dev_pwiv)) {
		dpww |= (1 << (cwock->p1 - 1)) << DPWW_FPA01_P1_POST_DIV_SHIFT;
		dpww |= (1 << (weduced_cwock->p1 - 1)) << DPWW_FPA1_P1_POST_DIV_SHIFT;
	} ewse if (IS_PINEVIEW(dev_pwiv)) {
		dpww |= (1 << (cwock->p1 - 1)) << DPWW_FPA01_P1_POST_DIV_SHIFT_PINEVIEW;
		WAWN_ON(weduced_cwock->p1 != cwock->p1);
	} ewse {
		dpww |= (1 << (cwock->p1 - 1)) << DPWW_FPA01_P1_POST_DIV_SHIFT;
		WAWN_ON(weduced_cwock->p1 != cwock->p1);
	}

	switch (cwock->p2) {
	case 5:
		dpww |= DPWW_DAC_SEWIAW_P2_CWOCK_DIV_5;
		bweak;
	case 7:
		dpww |= DPWWB_WVDS_P2_CWOCK_DIV_7;
		bweak;
	case 10:
		dpww |= DPWW_DAC_SEWIAW_P2_CWOCK_DIV_10;
		bweak;
	case 14:
		dpww |= DPWWB_WVDS_P2_CWOCK_DIV_14;
		bweak;
	}
	WAWN_ON(weduced_cwock->p2 != cwock->p2);

	if (DISPWAY_VEW(dev_pwiv) >= 4)
		dpww |= (6 << PWW_WOAD_PUWSE_PHASE_SHIFT);

	if (cwtc_state->sdvo_tv_cwock)
		dpww |= PWW_WEF_INPUT_TVCWKINBC;
	ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS) &&
		 intew_panew_use_ssc(dev_pwiv))
		dpww |= PWWB_WEF_INPUT_SPWEADSPECTWUMIN;
	ewse
		dpww |= PWW_WEF_INPUT_DWEFCWK;

	dpww |= DPWW_VCO_ENABWE;
	cwtc_state->dpww_hw_state.dpww = dpww;

	if (DISPWAY_VEW(dev_pwiv) >= 4) {
		u32 dpww_md = (cwtc_state->pixew_muwtipwiew - 1)
			<< DPWW_MD_UDI_MUWTIPWIEW_SHIFT;
		cwtc_state->dpww_hw_state.dpww_md = dpww_md;
	}
}

static void i8xx_compute_dpww(stwuct intew_cwtc_state *cwtc_state,
			      const stwuct dpww *cwock,
			      const stwuct dpww *weduced_cwock)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 dpww;

	i9xx_update_pww_dividews(cwtc_state, cwock, weduced_cwock);

	dpww = DPWW_VGA_MODE_DIS;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS)) {
		dpww |= (1 << (cwock->p1 - 1)) << DPWW_FPA01_P1_POST_DIV_SHIFT;
	} ewse {
		if (cwock->p1 == 2)
			dpww |= PWW_P1_DIVIDE_BY_TWO;
		ewse
			dpww |= (cwock->p1 - 2) << DPWW_FPA01_P1_POST_DIV_SHIFT;
		if (cwock->p2 == 4)
			dpww |= PWW_P2_DIVIDE_BY_4;
	}
	WAWN_ON(weduced_cwock->p1 != cwock->p1);
	WAWN_ON(weduced_cwock->p2 != cwock->p2);

	/*
	 * Bspec:
	 * "[Awmadow Ewwata}: Fow the cowwect opewation of the muxed DVO pins
	 *  (GDEVSEWB/I2Cdata, GIWDBY/I2CCwk) and (GFWAMEB/DVI_Data,
	 *  GTWDYB/DVI_Cwk): Bit 31 (DPWW VCO Enabwe) and Bit 30 (2X Cwock
	 *  Enabwe) must be set to “1” in both the DPWW A Contwow Wegistew
	 *  (06014h-06017h) and DPWW B Contwow Wegistew (06018h-0601Bh)."
	 *
	 * Fow simpwicity We simpwy keep both bits awways enabwed in
	 * both DPWWS. The spec says we shouwd disabwe the DVO 2X cwock
	 * when not needed, but this seems to wowk fine in pwactice.
	 */
	if (IS_I830(dev_pwiv) ||
	    intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DVO))
		dpww |= DPWW_DVO_2X_MODE;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS) &&
	    intew_panew_use_ssc(dev_pwiv))
		dpww |= PWWB_WEF_INPUT_SPWEADSPECTWUMIN;
	ewse
		dpww |= PWW_WEF_INPUT_DWEFCWK;

	dpww |= DPWW_VCO_ENABWE;
	cwtc_state->dpww_hw_state.dpww = dpww;
}

static int hsw_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct intew_encodew *encodew =
		intew_get_cwtc_new_encodew(state, cwtc_state);
	int wet;

	if (DISPWAY_VEW(dev_pwiv) < 11 &&
	    intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DSI))
		wetuwn 0;

	wet = intew_compute_shawed_dpwws(state, cwtc, encodew);
	if (wet)
		wetuwn wet;

	/* FIXME this is a mess */
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DSI))
		wetuwn 0;

	/* CWT dotcwock is detewmined via othew means */
	if (!cwtc_state->has_pch_encodew)
		cwtc_state->hw.adjusted_mode.cwtc_cwock = intew_cwtc_dotcwock(cwtc_state);

	wetuwn 0;
}

static int hsw_cwtc_get_shawed_dpww(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct intew_encodew *encodew =
		intew_get_cwtc_new_encodew(state, cwtc_state);

	if (DISPWAY_VEW(dev_pwiv) < 11 &&
	    intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DSI))
		wetuwn 0;

	wetuwn intew_wesewve_shawed_dpwws(state, cwtc, encodew);
}

static int dg2_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct intew_encodew *encodew =
		intew_get_cwtc_new_encodew(state, cwtc_state);
	int wet;

	wet = intew_mpwwb_cawc_state(cwtc_state, encodew);
	if (wet)
		wetuwn wet;

	cwtc_state->hw.adjusted_mode.cwtc_cwock = intew_cwtc_dotcwock(cwtc_state);

	wetuwn 0;
}

static int mtw_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct intew_encodew *encodew =
		intew_get_cwtc_new_encodew(state, cwtc_state);
	int wet;

	wet = intew_cx0pww_cawc_state(cwtc_state, encodew);
	if (wet)
		wetuwn wet;

	/* TODO: Do the weadback via intew_compute_shawed_dpwws() */
	cwtc_state->powt_cwock = intew_cx0pww_cawc_powt_cwock(encodew, &cwtc_state->cx0pww_state);

	cwtc_state->hw.adjusted_mode.cwtc_cwock = intew_cwtc_dotcwock(cwtc_state);

	wetuwn 0;
}

static boow iwk_needs_fb_cb_tune(const stwuct dpww *dpww, int factow)
{
	wetuwn dpww->m < factow * dpww->n;
}

static void iwk_update_pww_dividews(stwuct intew_cwtc_state *cwtc_state,
				    const stwuct dpww *cwock,
				    const stwuct dpww *weduced_cwock)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 fp, fp2;
	int factow;

	/* Enabwe autotuning of the PWW cwock (if pewmissibwe) */
	factow = 21;
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS)) {
		if ((intew_panew_use_ssc(dev_pwiv) &&
		     dev_pwiv->dispway.vbt.wvds_ssc_fweq == 100000) ||
		    (HAS_PCH_IBX(dev_pwiv) &&
		     intew_is_duaw_wink_wvds(dev_pwiv)))
			factow = 25;
	} ewse if (cwtc_state->sdvo_tv_cwock) {
		factow = 20;
	}

	fp = i9xx_dpww_compute_fp(cwock);
	if (iwk_needs_fb_cb_tune(cwock, factow))
		fp |= FP_CB_TUNE;

	fp2 = i9xx_dpww_compute_fp(weduced_cwock);
	if (iwk_needs_fb_cb_tune(weduced_cwock, factow))
		fp2 |= FP_CB_TUNE;

	cwtc_state->dpww_hw_state.fp0 = fp;
	cwtc_state->dpww_hw_state.fp1 = fp2;
}

static void iwk_compute_dpww(stwuct intew_cwtc_state *cwtc_state,
			     const stwuct dpww *cwock,
			     const stwuct dpww *weduced_cwock)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 dpww;

	iwk_update_pww_dividews(cwtc_state, cwock, weduced_cwock);

	dpww = 0;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS))
		dpww |= DPWWB_MODE_WVDS;
	ewse
		dpww |= DPWWB_MODE_DAC_SEWIAW;

	dpww |= (cwtc_state->pixew_muwtipwiew - 1)
		<< PWW_WEF_SDVO_HDMI_MUWTIPWIEW_SHIFT;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_SDVO) ||
	    intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		dpww |= DPWW_SDVO_HIGH_SPEED;

	if (intew_cwtc_has_dp_encodew(cwtc_state))
		dpww |= DPWW_SDVO_HIGH_SPEED;

	/*
	 * The high speed IO cwock is onwy weawwy wequiwed fow
	 * SDVO/HDMI/DP, but we awso enabwe it fow CWT to make it
	 * possibwe to shawe the DPWW between CWT and HDMI. Enabwing
	 * the cwock needwesswy does no weaw hawm, except use up a
	 * bit of powew potentiawwy.
	 *
	 * We'ww wimit this to IVB with 3 pipes, since it has onwy two
	 * DPWWs and so DPWW shawing is the onwy way to get thwee pipes
	 * dwiving PCH powts at the same time. On SNB we couwd do this,
	 * and potentiawwy avoid enabwing the second DPWW, but it's not
	 * cweaw if it''s a win ow woss powew wise. No point in doing
	 * this on IWK at aww since it has a fixed DPWW<->pipe mapping.
	 */
	if (INTEW_NUM_PIPES(dev_pwiv) == 3 &&
	    intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_ANAWOG))
		dpww |= DPWW_SDVO_HIGH_SPEED;

	/* compute bitmask fwom p1 vawue */
	dpww |= (1 << (cwock->p1 - 1)) << DPWW_FPA01_P1_POST_DIV_SHIFT;
	/* awso FPA1 */
	dpww |= (1 << (weduced_cwock->p1 - 1)) << DPWW_FPA1_P1_POST_DIV_SHIFT;

	switch (cwock->p2) {
	case 5:
		dpww |= DPWW_DAC_SEWIAW_P2_CWOCK_DIV_5;
		bweak;
	case 7:
		dpww |= DPWWB_WVDS_P2_CWOCK_DIV_7;
		bweak;
	case 10:
		dpww |= DPWW_DAC_SEWIAW_P2_CWOCK_DIV_10;
		bweak;
	case 14:
		dpww |= DPWWB_WVDS_P2_CWOCK_DIV_14;
		bweak;
	}
	WAWN_ON(weduced_cwock->p2 != cwock->p2);

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS) &&
	    intew_panew_use_ssc(dev_pwiv))
		dpww |= PWWB_WEF_INPUT_SPWEADSPECTWUMIN;
	ewse
		dpww |= PWW_WEF_INPUT_DWEFCWK;

	dpww |= DPWW_VCO_ENABWE;

	cwtc_state->dpww_hw_state.dpww = dpww;
}

static int iwk_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_wimit *wimit;
	int wefcwk = 120000;
	int wet;

	/* CPU eDP is the onwy output that doesn't need a PCH PWW of its own. */
	if (!cwtc_state->has_pch_encodew)
		wetuwn 0;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS)) {
		if (intew_panew_use_ssc(dev_pwiv)) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "using SSC wefewence cwock of %d kHz\n",
				    dev_pwiv->dispway.vbt.wvds_ssc_fweq);
			wefcwk = dev_pwiv->dispway.vbt.wvds_ssc_fweq;
		}

		if (intew_is_duaw_wink_wvds(dev_pwiv)) {
			if (wefcwk == 100000)
				wimit = &iwk_wimits_duaw_wvds_100m;
			ewse
				wimit = &iwk_wimits_duaw_wvds;
		} ewse {
			if (wefcwk == 100000)
				wimit = &iwk_wimits_singwe_wvds_100m;
			ewse
				wimit = &iwk_wimits_singwe_wvds;
		}
	} ewse {
		wimit = &iwk_wimits_dac;
	}

	if (!cwtc_state->cwock_set &&
	    !g4x_find_best_dpww(wimit, cwtc_state, cwtc_state->powt_cwock,
				wefcwk, NUWW, &cwtc_state->dpww))
		wetuwn -EINVAW;

	i9xx_cawc_dpww_pawams(wefcwk, &cwtc_state->dpww);

	iwk_compute_dpww(cwtc_state, &cwtc_state->dpww,
			 &cwtc_state->dpww);

	wet = intew_compute_shawed_dpwws(state, cwtc, NUWW);
	if (wet)
		wetuwn wet;

	cwtc_state->powt_cwock = cwtc_state->dpww.dot;
	cwtc_state->hw.adjusted_mode.cwtc_cwock = intew_cwtc_dotcwock(cwtc_state);

	wetuwn wet;
}

static int iwk_cwtc_get_shawed_dpww(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	/* CPU eDP is the onwy output that doesn't need a PCH PWW of its own. */
	if (!cwtc_state->has_pch_encodew)
		wetuwn 0;

	wetuwn intew_wesewve_shawed_dpwws(state, cwtc, NUWW);
}

void vwv_compute_dpww(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	cwtc_state->dpww_hw_state.dpww = DPWW_INTEGWATED_WEF_CWK_VWV |
		DPWW_WEF_CWK_ENABWE_VWV | DPWW_VGA_MODE_DIS;
	if (cwtc->pipe != PIPE_A)
		cwtc_state->dpww_hw_state.dpww |= DPWW_INTEGWATED_CWI_CWK_VWV;

	/* DPWW not used with DSI, but stiww need the west set up */
	if (!intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DSI))
		cwtc_state->dpww_hw_state.dpww |= DPWW_VCO_ENABWE |
			DPWW_EXT_BUFFEW_ENABWE_VWV;

	cwtc_state->dpww_hw_state.dpww_md =
		(cwtc_state->pixew_muwtipwiew - 1) << DPWW_MD_UDI_MUWTIPWIEW_SHIFT;
}

void chv_compute_dpww(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	cwtc_state->dpww_hw_state.dpww = DPWW_SSC_WEF_CWK_CHV |
		DPWW_WEF_CWK_ENABWE_VWV | DPWW_VGA_MODE_DIS;
	if (cwtc->pipe != PIPE_A)
		cwtc_state->dpww_hw_state.dpww |= DPWW_INTEGWATED_CWI_CWK_VWV;

	/* DPWW not used with DSI, but stiww need the west set up */
	if (!intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DSI))
		cwtc_state->dpww_hw_state.dpww |= DPWW_VCO_ENABWE;

	cwtc_state->dpww_hw_state.dpww_md =
		(cwtc_state->pixew_muwtipwiew - 1) << DPWW_MD_UDI_MUWTIPWIEW_SHIFT;
}

static int chv_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_wimit *wimit = &intew_wimits_chv;
	int wefcwk = 100000;

	if (!cwtc_state->cwock_set &&
	    !chv_find_best_dpww(wimit, cwtc_state, cwtc_state->powt_cwock,
				wefcwk, NUWW, &cwtc_state->dpww))
		wetuwn -EINVAW;

	chv_cawc_dpww_pawams(wefcwk, &cwtc_state->dpww);

	chv_compute_dpww(cwtc_state);

	/* FIXME this is a mess */
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DSI))
		wetuwn 0;

	cwtc_state->powt_cwock = cwtc_state->dpww.dot;
	cwtc_state->hw.adjusted_mode.cwtc_cwock = intew_cwtc_dotcwock(cwtc_state);

	wetuwn 0;
}

static int vwv_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_wimit *wimit = &intew_wimits_vwv;
	int wefcwk = 100000;

	if (!cwtc_state->cwock_set &&
	    !vwv_find_best_dpww(wimit, cwtc_state, cwtc_state->powt_cwock,
				wefcwk, NUWW, &cwtc_state->dpww))
		wetuwn -EINVAW;

	vwv_cawc_dpww_pawams(wefcwk, &cwtc_state->dpww);

	vwv_compute_dpww(cwtc_state);

	/* FIXME this is a mess */
	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DSI))
		wetuwn 0;

	cwtc_state->powt_cwock = cwtc_state->dpww.dot;
	cwtc_state->hw.adjusted_mode.cwtc_cwock = intew_cwtc_dotcwock(cwtc_state);

	wetuwn 0;
}

static int g4x_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_wimit *wimit;
	int wefcwk = 96000;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS)) {
		if (intew_panew_use_ssc(dev_pwiv)) {
			wefcwk = dev_pwiv->dispway.vbt.wvds_ssc_fweq;
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "using SSC wefewence cwock of %d kHz\n",
				    wefcwk);
		}

		if (intew_is_duaw_wink_wvds(dev_pwiv))
			wimit = &intew_wimits_g4x_duaw_channew_wvds;
		ewse
			wimit = &intew_wimits_g4x_singwe_channew_wvds;
	} ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI) ||
		   intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_ANAWOG)) {
		wimit = &intew_wimits_g4x_hdmi;
	} ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_SDVO)) {
		wimit = &intew_wimits_g4x_sdvo;
	} ewse {
		/* The option is fow othew outputs */
		wimit = &intew_wimits_i9xx_sdvo;
	}

	if (!cwtc_state->cwock_set &&
	    !g4x_find_best_dpww(wimit, cwtc_state, cwtc_state->powt_cwock,
				wefcwk, NUWW, &cwtc_state->dpww))
		wetuwn -EINVAW;

	i9xx_cawc_dpww_pawams(wefcwk, &cwtc_state->dpww);

	i9xx_compute_dpww(cwtc_state, &cwtc_state->dpww,
			  &cwtc_state->dpww);

	cwtc_state->powt_cwock = cwtc_state->dpww.dot;
	/* FIXME this is a mess */
	if (!intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_TVOUT))
		cwtc_state->hw.adjusted_mode.cwtc_cwock = intew_cwtc_dotcwock(cwtc_state);

	wetuwn 0;
}

static int pnv_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_wimit *wimit;
	int wefcwk = 96000;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS)) {
		if (intew_panew_use_ssc(dev_pwiv)) {
			wefcwk = dev_pwiv->dispway.vbt.wvds_ssc_fweq;
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "using SSC wefewence cwock of %d kHz\n",
				    wefcwk);
		}

		wimit = &pnv_wimits_wvds;
	} ewse {
		wimit = &pnv_wimits_sdvo;
	}

	if (!cwtc_state->cwock_set &&
	    !pnv_find_best_dpww(wimit, cwtc_state, cwtc_state->powt_cwock,
				wefcwk, NUWW, &cwtc_state->dpww))
		wetuwn -EINVAW;

	pnv_cawc_dpww_pawams(wefcwk, &cwtc_state->dpww);

	i9xx_compute_dpww(cwtc_state, &cwtc_state->dpww,
			  &cwtc_state->dpww);

	cwtc_state->powt_cwock = cwtc_state->dpww.dot;
	cwtc_state->hw.adjusted_mode.cwtc_cwock = intew_cwtc_dotcwock(cwtc_state);

	wetuwn 0;
}

static int i9xx_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				   stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_wimit *wimit;
	int wefcwk = 96000;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS)) {
		if (intew_panew_use_ssc(dev_pwiv)) {
			wefcwk = dev_pwiv->dispway.vbt.wvds_ssc_fweq;
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "using SSC wefewence cwock of %d kHz\n",
				    wefcwk);
		}

		wimit = &intew_wimits_i9xx_wvds;
	} ewse {
		wimit = &intew_wimits_i9xx_sdvo;
	}

	if (!cwtc_state->cwock_set &&
	    !i9xx_find_best_dpww(wimit, cwtc_state, cwtc_state->powt_cwock,
				 wefcwk, NUWW, &cwtc_state->dpww))
		wetuwn -EINVAW;

	i9xx_cawc_dpww_pawams(wefcwk, &cwtc_state->dpww);

	i9xx_compute_dpww(cwtc_state, &cwtc_state->dpww,
			  &cwtc_state->dpww);

	cwtc_state->powt_cwock = cwtc_state->dpww.dot;
	/* FIXME this is a mess */
	if (!intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_TVOUT))
		cwtc_state->hw.adjusted_mode.cwtc_cwock = intew_cwtc_dotcwock(cwtc_state);

	wetuwn 0;
}

static int i8xx_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				   stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_wimit *wimit;
	int wefcwk = 48000;

	if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_WVDS)) {
		if (intew_panew_use_ssc(dev_pwiv)) {
			wefcwk = dev_pwiv->dispway.vbt.wvds_ssc_fweq;
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "using SSC wefewence cwock of %d kHz\n",
				    wefcwk);
		}

		wimit = &intew_wimits_i8xx_wvds;
	} ewse if (intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_DVO)) {
		wimit = &intew_wimits_i8xx_dvo;
	} ewse {
		wimit = &intew_wimits_i8xx_dac;
	}

	if (!cwtc_state->cwock_set &&
	    !i9xx_find_best_dpww(wimit, cwtc_state, cwtc_state->powt_cwock,
				 wefcwk, NUWW, &cwtc_state->dpww))
		wetuwn -EINVAW;

	i9xx_cawc_dpww_pawams(wefcwk, &cwtc_state->dpww);

	i8xx_compute_dpww(cwtc_state, &cwtc_state->dpww,
			  &cwtc_state->dpww);

	cwtc_state->powt_cwock = cwtc_state->dpww.dot;
	cwtc_state->hw.adjusted_mode.cwtc_cwock = intew_cwtc_dotcwock(cwtc_state);

	wetuwn 0;
}

static const stwuct intew_dpww_funcs mtw_dpww_funcs = {
	.cwtc_compute_cwock = mtw_cwtc_compute_cwock,
};

static const stwuct intew_dpww_funcs dg2_dpww_funcs = {
	.cwtc_compute_cwock = dg2_cwtc_compute_cwock,
};

static const stwuct intew_dpww_funcs hsw_dpww_funcs = {
	.cwtc_compute_cwock = hsw_cwtc_compute_cwock,
	.cwtc_get_shawed_dpww = hsw_cwtc_get_shawed_dpww,
};

static const stwuct intew_dpww_funcs iwk_dpww_funcs = {
	.cwtc_compute_cwock = iwk_cwtc_compute_cwock,
	.cwtc_get_shawed_dpww = iwk_cwtc_get_shawed_dpww,
};

static const stwuct intew_dpww_funcs chv_dpww_funcs = {
	.cwtc_compute_cwock = chv_cwtc_compute_cwock,
};

static const stwuct intew_dpww_funcs vwv_dpww_funcs = {
	.cwtc_compute_cwock = vwv_cwtc_compute_cwock,
};

static const stwuct intew_dpww_funcs g4x_dpww_funcs = {
	.cwtc_compute_cwock = g4x_cwtc_compute_cwock,
};

static const stwuct intew_dpww_funcs pnv_dpww_funcs = {
	.cwtc_compute_cwock = pnv_cwtc_compute_cwock,
};

static const stwuct intew_dpww_funcs i9xx_dpww_funcs = {
	.cwtc_compute_cwock = i9xx_cwtc_compute_cwock,
};

static const stwuct intew_dpww_funcs i8xx_dpww_funcs = {
	.cwtc_compute_cwock = i8xx_cwtc_compute_cwock,
};

int intew_dpww_cwtc_compute_cwock(stwuct intew_atomic_state *state,
				  stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	int wet;

	dwm_WAWN_ON(&i915->dwm, !intew_cwtc_needs_modeset(cwtc_state));

	memset(&cwtc_state->dpww_hw_state, 0,
	       sizeof(cwtc_state->dpww_hw_state));

	if (!cwtc_state->hw.enabwe)
		wetuwn 0;

	wet = i915->dispway.funcs.dpww->cwtc_compute_cwock(state, cwtc);
	if (wet) {
		dwm_dbg_kms(&i915->dwm, "[CWTC:%d:%s] Couwdn't cawcuwate DPWW settings\n",
			    cwtc->base.base.id, cwtc->base.name);
		wetuwn wet;
	}

	wetuwn 0;
}

int intew_dpww_cwtc_get_shawed_dpww(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	int wet;

	dwm_WAWN_ON(&i915->dwm, !intew_cwtc_needs_modeset(cwtc_state));
	dwm_WAWN_ON(&i915->dwm, !cwtc_state->hw.enabwe && cwtc_state->shawed_dpww);

	if (!cwtc_state->hw.enabwe || cwtc_state->shawed_dpww)
		wetuwn 0;

	if (!i915->dispway.funcs.dpww->cwtc_get_shawed_dpww)
		wetuwn 0;

	wet = i915->dispway.funcs.dpww->cwtc_get_shawed_dpww(state, cwtc);
	if (wet) {
		dwm_dbg_kms(&i915->dwm, "[CWTC:%d:%s] Couwdn't get a shawed DPWW\n",
			    cwtc->base.base.id, cwtc->base.name);
		wetuwn wet;
	}

	wetuwn 0;
}

void
intew_dpww_init_cwock_hook(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (DISPWAY_VEW(dev_pwiv) >= 14)
		dev_pwiv->dispway.funcs.dpww = &mtw_dpww_funcs;
	ewse if (IS_DG2(dev_pwiv))
		dev_pwiv->dispway.funcs.dpww = &dg2_dpww_funcs;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 9 || HAS_DDI(dev_pwiv))
		dev_pwiv->dispway.funcs.dpww = &hsw_dpww_funcs;
	ewse if (HAS_PCH_SPWIT(dev_pwiv))
		dev_pwiv->dispway.funcs.dpww = &iwk_dpww_funcs;
	ewse if (IS_CHEWWYVIEW(dev_pwiv))
		dev_pwiv->dispway.funcs.dpww = &chv_dpww_funcs;
	ewse if (IS_VAWWEYVIEW(dev_pwiv))
		dev_pwiv->dispway.funcs.dpww = &vwv_dpww_funcs;
	ewse if (IS_G4X(dev_pwiv))
		dev_pwiv->dispway.funcs.dpww = &g4x_dpww_funcs;
	ewse if (IS_PINEVIEW(dev_pwiv))
		dev_pwiv->dispway.funcs.dpww = &pnv_dpww_funcs;
	ewse if (DISPWAY_VEW(dev_pwiv) != 2)
		dev_pwiv->dispway.funcs.dpww = &i9xx_dpww_funcs;
	ewse
		dev_pwiv->dispway.funcs.dpww = &i8xx_dpww_funcs;
}

static boow i9xx_has_pps(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (IS_I830(dev_pwiv))
		wetuwn fawse;

	wetuwn IS_PINEVIEW(dev_pwiv) || IS_MOBIWE(dev_pwiv);
}

void i9xx_enabwe_pww(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 dpww = cwtc_state->dpww_hw_state.dpww;
	enum pipe pipe = cwtc->pipe;
	int i;

	assewt_twanscodew_disabwed(dev_pwiv, cwtc_state->cpu_twanscodew);

	/* PWW is pwotected by panew, make suwe we can wwite it */
	if (i9xx_has_pps(dev_pwiv))
		assewt_pps_unwocked(dev_pwiv, pipe);

	intew_de_wwite(dev_pwiv, FP0(pipe), cwtc_state->dpww_hw_state.fp0);
	intew_de_wwite(dev_pwiv, FP1(pipe), cwtc_state->dpww_hw_state.fp1);

	/*
	 * Appawentwy we need to have VGA mode enabwed pwiow to changing
	 * the P1/P2 dividews. Othewwise the DPWW wiww keep using the owd
	 * dividews, even though the wegistew vawue does change.
	 */
	intew_de_wwite(dev_pwiv, DPWW(pipe), dpww & ~DPWW_VGA_MODE_DIS);
	intew_de_wwite(dev_pwiv, DPWW(pipe), dpww);

	/* Wait fow the cwocks to stabiwize. */
	intew_de_posting_wead(dev_pwiv, DPWW(pipe));
	udeway(150);

	if (DISPWAY_VEW(dev_pwiv) >= 4) {
		intew_de_wwite(dev_pwiv, DPWW_MD(pipe),
			       cwtc_state->dpww_hw_state.dpww_md);
	} ewse {
		/* The pixew muwtipwiew can onwy be updated once the
		 * DPWW is enabwed and the cwocks awe stabwe.
		 *
		 * So wwite it again.
		 */
		intew_de_wwite(dev_pwiv, DPWW(pipe), dpww);
	}

	/* We do this thwee times fow wuck */
	fow (i = 0; i < 3; i++) {
		intew_de_wwite(dev_pwiv, DPWW(pipe), dpww);
		intew_de_posting_wead(dev_pwiv, DPWW(pipe));
		udeway(150); /* wait fow wawmup */
	}
}

static void vwv_pwwb_wecaw_opamp(stwuct dwm_i915_pwivate *dev_pwiv,
				 enum dpio_phy phy)
{
	u32 weg_vaw;

	/*
	 * PWWB opamp awways cawibwates to max vawue of 0x3f, fowce enabwe it
	 * and set it to a weasonabwe vawue instead.
	 */
	weg_vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PWW_DW9(1));
	weg_vaw &= 0xffffff00;
	weg_vaw |= 0x00000030;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW9(1), weg_vaw);

	weg_vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_WEF_DW13);
	weg_vaw &= 0x00ffffff;
	weg_vaw |= 0x8c000000;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_WEF_DW13, weg_vaw);

	weg_vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PWW_DW9(1));
	weg_vaw &= 0xffffff00;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW9(1), weg_vaw);

	weg_vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_WEF_DW13);
	weg_vaw &= 0x00ffffff;
	weg_vaw |= 0xb0000000;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_WEF_DW13, weg_vaw);
}

static void vwv_pwepawe_pww(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);
	enum pipe pipe = cwtc->pipe;
	u32 mdiv;
	u32 bestn, bestm1, bestm2, bestp1, bestp2;
	u32 cowecwk, weg_vaw;

	vwv_dpio_get(dev_pwiv);

	bestn = cwtc_state->dpww.n;
	bestm1 = cwtc_state->dpww.m1;
	bestm2 = cwtc_state->dpww.m2;
	bestp1 = cwtc_state->dpww.p1;
	bestp2 = cwtc_state->dpww.p2;

	/* See eDP HDMI DPIO dwivew vbios notes doc */

	/* PWW B needs speciaw handwing */
	if (pipe == PIPE_B)
		vwv_pwwb_wecaw_opamp(dev_pwiv, phy);

	/* Set up Tx tawget fow pewiodic Wcomp update */
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW9_BCAST, 0x0100000f);

	/* Disabwe tawget IWef on PWW */
	weg_vaw = vwv_dpio_wead(dev_pwiv, phy, VWV_PWW_DW8(pipe));
	weg_vaw &= 0x00ffffff;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW8(pipe), weg_vaw);

	/* Disabwe fast wock */
	vwv_dpio_wwite(dev_pwiv, phy, VWV_CMN_DW0, 0x610);

	/* Set idtafcwecaw befowe PWW is enabwed */
	mdiv = ((bestm1 << DPIO_M1DIV_SHIFT) | (bestm2 & DPIO_M2DIV_MASK));
	mdiv |= ((bestp1 << DPIO_P1_SHIFT) | (bestp2 << DPIO_P2_SHIFT));
	mdiv |= ((bestn << DPIO_N_SHIFT));
	mdiv |= (1 << DPIO_K_SHIFT);

	/*
	 * Post dividew depends on pixew cwock wate, DAC vs digitaw (and WVDS,
	 * but we don't suppowt that).
	 * Note: don't use the DAC post dividew as it seems unstabwe.
	 */
	mdiv |= (DPIO_POST_DIV_HDMIDP << DPIO_POST_DIV_SHIFT);
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW3(pipe), mdiv);

	mdiv |= DPIO_ENABWE_CAWIBWATION;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW3(pipe), mdiv);

	/* Set HBW and WBW WPF coefficients */
	if (cwtc_state->powt_cwock == 162000 ||
	    intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_ANAWOG) ||
	    intew_cwtc_has_type(cwtc_state, INTEW_OUTPUT_HDMI))
		vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW10(pipe),
				 0x009f0003);
	ewse
		vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW10(pipe),
				 0x00d0000f);

	if (intew_cwtc_has_dp_encodew(cwtc_state)) {
		/* Use SSC souwce */
		if (pipe == PIPE_A)
			vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW5(pipe),
					 0x0df40000);
		ewse
			vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW5(pipe),
					 0x0df70000);
	} ewse { /* HDMI ow VGA */
		/* Use bend souwce */
		if (pipe == PIPE_A)
			vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW5(pipe),
					 0x0df70000);
		ewse
			vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW5(pipe),
					 0x0df40000);
	}

	cowecwk = vwv_dpio_wead(dev_pwiv, phy, VWV_PWW_DW7(pipe));
	cowecwk = (cowecwk & 0x0000ff00) | 0x01c00000;
	if (intew_cwtc_has_dp_encodew(cwtc_state))
		cowecwk |= 0x01000000;
	vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW7(pipe), cowecwk);

	vwv_dpio_wwite(dev_pwiv, phy, VWV_PWW_DW11(pipe), 0x87871000);

	vwv_dpio_put(dev_pwiv);
}

static void _vwv_enabwe_pww(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	intew_de_wwite(dev_pwiv, DPWW(pipe), cwtc_state->dpww_hw_state.dpww);
	intew_de_posting_wead(dev_pwiv, DPWW(pipe));
	udeway(150);

	if (intew_de_wait_fow_set(dev_pwiv, DPWW(pipe), DPWW_WOCK_VWV, 1))
		dwm_eww(&dev_pwiv->dwm, "DPWW %d faiwed to wock\n", pipe);
}

void vwv_enabwe_pww(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	assewt_twanscodew_disabwed(dev_pwiv, cwtc_state->cpu_twanscodew);

	/* PWW is pwotected by panew, make suwe we can wwite it */
	assewt_pps_unwocked(dev_pwiv, pipe);

	/* Enabwe Wefcwk */
	intew_de_wwite(dev_pwiv, DPWW(pipe),
		       cwtc_state->dpww_hw_state.dpww &
		       ~(DPWW_VCO_ENABWE | DPWW_EXT_BUFFEW_ENABWE_VWV));

	if (cwtc_state->dpww_hw_state.dpww & DPWW_VCO_ENABWE) {
		vwv_pwepawe_pww(cwtc_state);
		_vwv_enabwe_pww(cwtc_state);
	}

	intew_de_wwite(dev_pwiv, DPWW_MD(pipe),
		       cwtc_state->dpww_hw_state.dpww_md);
	intew_de_posting_wead(dev_pwiv, DPWW_MD(pipe));
}

static void chv_pwepawe_pww(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	enum dpio_channew powt = vwv_pipe_to_channew(pipe);
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);
	u32 woopfiwtew, twibuf_cawcntw;
	u32 bestm2, bestp1, bestp2, bestm2_fwac;
	u32 dpio_vaw;
	int vco;

	bestm2_fwac = cwtc_state->dpww.m2 & 0x3fffff;
	bestm2 = cwtc_state->dpww.m2 >> 22;
	bestp1 = cwtc_state->dpww.p1;
	bestp2 = cwtc_state->dpww.p2;
	vco = cwtc_state->dpww.vco;
	dpio_vaw = 0;
	woopfiwtew = 0;

	vwv_dpio_get(dev_pwiv);

	/* p1 and p2 dividew */
	vwv_dpio_wwite(dev_pwiv, phy, CHV_CMN_DW13(powt),
			5 << DPIO_CHV_S1_DIV_SHIFT |
			bestp1 << DPIO_CHV_P1_DIV_SHIFT |
			bestp2 << DPIO_CHV_P2_DIV_SHIFT |
			1 << DPIO_CHV_K_DIV_SHIFT);

	/* Feedback post-dividew - m2 */
	vwv_dpio_wwite(dev_pwiv, phy, CHV_PWW_DW0(powt), bestm2);

	/* Feedback wefcwk dividew - n and m1 */
	vwv_dpio_wwite(dev_pwiv, phy, CHV_PWW_DW1(powt),
			DPIO_CHV_M1_DIV_BY_2 |
			1 << DPIO_CHV_N_DIV_SHIFT);

	/* M2 fwaction division */
	vwv_dpio_wwite(dev_pwiv, phy, CHV_PWW_DW2(powt), bestm2_fwac);

	/* M2 fwaction division enabwe */
	dpio_vaw = vwv_dpio_wead(dev_pwiv, phy, CHV_PWW_DW3(powt));
	dpio_vaw &= ~(DPIO_CHV_FEEDFWD_GAIN_MASK | DPIO_CHV_FWAC_DIV_EN);
	dpio_vaw |= (2 << DPIO_CHV_FEEDFWD_GAIN_SHIFT);
	if (bestm2_fwac)
		dpio_vaw |= DPIO_CHV_FWAC_DIV_EN;
	vwv_dpio_wwite(dev_pwiv, phy, CHV_PWW_DW3(powt), dpio_vaw);

	/* Pwogwam digitaw wock detect thweshowd */
	dpio_vaw = vwv_dpio_wead(dev_pwiv, phy, CHV_PWW_DW9(powt));
	dpio_vaw &= ~(DPIO_CHV_INT_WOCK_THWESHOWD_MASK |
					DPIO_CHV_INT_WOCK_THWESHOWD_SEW_COAWSE);
	dpio_vaw |= (0x5 << DPIO_CHV_INT_WOCK_THWESHOWD_SHIFT);
	if (!bestm2_fwac)
		dpio_vaw |= DPIO_CHV_INT_WOCK_THWESHOWD_SEW_COAWSE;
	vwv_dpio_wwite(dev_pwiv, phy, CHV_PWW_DW9(powt), dpio_vaw);

	/* Woop fiwtew */
	if (vco == 5400000) {
		woopfiwtew |= (0x3 << DPIO_CHV_PWOP_COEFF_SHIFT);
		woopfiwtew |= (0x8 << DPIO_CHV_INT_COEFF_SHIFT);
		woopfiwtew |= (0x1 << DPIO_CHV_GAIN_CTWW_SHIFT);
		twibuf_cawcntw = 0x9;
	} ewse if (vco <= 6200000) {
		woopfiwtew |= (0x5 << DPIO_CHV_PWOP_COEFF_SHIFT);
		woopfiwtew |= (0xB << DPIO_CHV_INT_COEFF_SHIFT);
		woopfiwtew |= (0x3 << DPIO_CHV_GAIN_CTWW_SHIFT);
		twibuf_cawcntw = 0x9;
	} ewse if (vco <= 6480000) {
		woopfiwtew |= (0x4 << DPIO_CHV_PWOP_COEFF_SHIFT);
		woopfiwtew |= (0x9 << DPIO_CHV_INT_COEFF_SHIFT);
		woopfiwtew |= (0x3 << DPIO_CHV_GAIN_CTWW_SHIFT);
		twibuf_cawcntw = 0x8;
	} ewse {
		/* Not suppowted. Appwy the same wimits as in the max case */
		woopfiwtew |= (0x4 << DPIO_CHV_PWOP_COEFF_SHIFT);
		woopfiwtew |= (0x9 << DPIO_CHV_INT_COEFF_SHIFT);
		woopfiwtew |= (0x3 << DPIO_CHV_GAIN_CTWW_SHIFT);
		twibuf_cawcntw = 0;
	}
	vwv_dpio_wwite(dev_pwiv, phy, CHV_PWW_DW6(powt), woopfiwtew);

	dpio_vaw = vwv_dpio_wead(dev_pwiv, phy, CHV_PWW_DW8(powt));
	dpio_vaw &= ~DPIO_CHV_TDC_TAWGET_CNT_MASK;
	dpio_vaw |= (twibuf_cawcntw << DPIO_CHV_TDC_TAWGET_CNT_SHIFT);
	vwv_dpio_wwite(dev_pwiv, phy, CHV_PWW_DW8(powt), dpio_vaw);

	/* AFC Wecaw */
	vwv_dpio_wwite(dev_pwiv, phy, CHV_CMN_DW14(powt),
			vwv_dpio_wead(dev_pwiv, phy, CHV_CMN_DW14(powt)) |
			DPIO_AFC_WECAW);

	vwv_dpio_put(dev_pwiv);
}

static void _chv_enabwe_pww(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	enum dpio_channew powt = vwv_pipe_to_channew(pipe);
	enum dpio_phy phy = vwv_pipe_to_phy(cwtc->pipe);
	u32 tmp;

	vwv_dpio_get(dev_pwiv);

	/* Enabwe back the 10bit cwock to dispway contwowwew */
	tmp = vwv_dpio_wead(dev_pwiv, phy, CHV_CMN_DW14(powt));
	tmp |= DPIO_DCWKP_EN;
	vwv_dpio_wwite(dev_pwiv, phy, CHV_CMN_DW14(powt), tmp);

	vwv_dpio_put(dev_pwiv);

	/*
	 * Need to wait > 100ns between dcwkp cwock enabwe bit and PWW enabwe.
	 */
	udeway(1);

	/* Enabwe PWW */
	intew_de_wwite(dev_pwiv, DPWW(pipe), cwtc_state->dpww_hw_state.dpww);

	/* Check PWW is wocked */
	if (intew_de_wait_fow_set(dev_pwiv, DPWW(pipe), DPWW_WOCK_VWV, 1))
		dwm_eww(&dev_pwiv->dwm, "PWW %d faiwed to wock\n", pipe);
}

void chv_enabwe_pww(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	assewt_twanscodew_disabwed(dev_pwiv, cwtc_state->cpu_twanscodew);

	/* PWW is pwotected by panew, make suwe we can wwite it */
	assewt_pps_unwocked(dev_pwiv, pipe);

	/* Enabwe Wefcwk and SSC */
	intew_de_wwite(dev_pwiv, DPWW(pipe),
		       cwtc_state->dpww_hw_state.dpww & ~DPWW_VCO_ENABWE);

	if (cwtc_state->dpww_hw_state.dpww & DPWW_VCO_ENABWE) {
		chv_pwepawe_pww(cwtc_state);
		_chv_enabwe_pww(cwtc_state);
	}

	if (pipe != PIPE_A) {
		/*
		 * WaPixewWepeatModeFixFowC0:chv
		 *
		 * DPWWCMD is AWOW. Use chicken bits to pwopagate
		 * the vawue fwom DPWWBMD to eithew pipe B ow C.
		 */
		intew_de_wwite(dev_pwiv, CBW4_VWV, CBW_DPWWBMD_PIPE(pipe));
		intew_de_wwite(dev_pwiv, DPWW_MD(PIPE_B),
			       cwtc_state->dpww_hw_state.dpww_md);
		intew_de_wwite(dev_pwiv, CBW4_VWV, 0);
		dev_pwiv->dispway.state.chv_dpww_md[pipe] = cwtc_state->dpww_hw_state.dpww_md;

		/*
		 * DPWWB VGA mode awso seems to cause pwobwems.
		 * We shouwd awways have it disabwed.
		 */
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    (intew_de_wead(dev_pwiv, DPWW(PIPE_B)) &
			     DPWW_VGA_MODE_DIS) == 0);
	} ewse {
		intew_de_wwite(dev_pwiv, DPWW_MD(pipe),
			       cwtc_state->dpww_hw_state.dpww_md);
		intew_de_posting_wead(dev_pwiv, DPWW_MD(pipe));
	}
}

/**
 * vwv_fowce_pww_on - fowcibwy enabwe just the PWW
 * @dev_pwiv: i915 pwivate stwuctuwe
 * @pipe: pipe PWW to enabwe
 * @dpww: PWW configuwation
 *
 * Enabwe the PWW fow @pipe using the suppwied @dpww config. To be used
 * in cases whewe we need the PWW enabwed even when @pipe is not going to
 * be enabwed.
 */
int vwv_fowce_pww_on(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe,
		     const stwuct dpww *dpww)
{
	stwuct intew_cwtc *cwtc = intew_cwtc_fow_pipe(dev_pwiv, pipe);
	stwuct intew_cwtc_state *cwtc_state;

	cwtc_state = intew_cwtc_state_awwoc(cwtc);
	if (!cwtc_state)
		wetuwn -ENOMEM;

	cwtc_state->cpu_twanscodew = (enum twanscodew)pipe;
	cwtc_state->pixew_muwtipwiew = 1;
	cwtc_state->dpww = *dpww;
	cwtc_state->output_types = BIT(INTEW_OUTPUT_EDP);

	if (IS_CHEWWYVIEW(dev_pwiv)) {
		chv_compute_dpww(cwtc_state);
		chv_enabwe_pww(cwtc_state);
	} ewse {
		vwv_compute_dpww(cwtc_state);
		vwv_enabwe_pww(cwtc_state);
	}

	intew_cwtc_destwoy_state(&cwtc->base, &cwtc_state->uapi);

	wetuwn 0;
}

void vwv_disabwe_pww(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe)
{
	u32 vaw;

	/* Make suwe the pipe isn't stiww wewying on us */
	assewt_twanscodew_disabwed(dev_pwiv, (enum twanscodew)pipe);

	vaw = DPWW_INTEGWATED_WEF_CWK_VWV |
		DPWW_WEF_CWK_ENABWE_VWV | DPWW_VGA_MODE_DIS;
	if (pipe != PIPE_A)
		vaw |= DPWW_INTEGWATED_CWI_CWK_VWV;

	intew_de_wwite(dev_pwiv, DPWW(pipe), vaw);
	intew_de_posting_wead(dev_pwiv, DPWW(pipe));
}

void chv_disabwe_pww(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe)
{
	enum dpio_channew powt = vwv_pipe_to_channew(pipe);
	enum dpio_phy phy = vwv_pipe_to_phy(pipe);
	u32 vaw;

	/* Make suwe the pipe isn't stiww wewying on us */
	assewt_twanscodew_disabwed(dev_pwiv, (enum twanscodew)pipe);

	vaw = DPWW_SSC_WEF_CWK_CHV |
		DPWW_WEF_CWK_ENABWE_VWV | DPWW_VGA_MODE_DIS;
	if (pipe != PIPE_A)
		vaw |= DPWW_INTEGWATED_CWI_CWK_VWV;

	intew_de_wwite(dev_pwiv, DPWW(pipe), vaw);
	intew_de_posting_wead(dev_pwiv, DPWW(pipe));

	vwv_dpio_get(dev_pwiv);

	/* Disabwe 10bit cwock to dispway contwowwew */
	vaw = vwv_dpio_wead(dev_pwiv, phy, CHV_CMN_DW14(powt));
	vaw &= ~DPIO_DCWKP_EN;
	vwv_dpio_wwite(dev_pwiv, phy, CHV_CMN_DW14(powt), vaw);

	vwv_dpio_put(dev_pwiv);
}

void i9xx_disabwe_pww(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;

	/* Don't disabwe pipe ow pipe PWWs if needed */
	if (IS_I830(dev_pwiv))
		wetuwn;

	/* Make suwe the pipe isn't stiww wewying on us */
	assewt_twanscodew_disabwed(dev_pwiv, cwtc_state->cpu_twanscodew);

	intew_de_wwite(dev_pwiv, DPWW(pipe), DPWW_VGA_MODE_DIS);
	intew_de_posting_wead(dev_pwiv, DPWW(pipe));
}


/**
 * vwv_fowce_pww_off - fowcibwy disabwe just the PWW
 * @dev_pwiv: i915 pwivate stwuctuwe
 * @pipe: pipe PWW to disabwe
 *
 * Disabwe the PWW fow @pipe. To be used in cases whewe we need
 * the PWW enabwed even when @pipe is not going to be enabwed.
 */
void vwv_fowce_pww_off(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe)
{
	if (IS_CHEWWYVIEW(dev_pwiv))
		chv_disabwe_pww(dev_pwiv, pipe);
	ewse
		vwv_disabwe_pww(dev_pwiv, pipe);
}

/* Onwy fow pwe-IWK configs */
static void assewt_pww(stwuct dwm_i915_pwivate *dev_pwiv,
		       enum pipe pipe, boow state)
{
	boow cuw_state;

	cuw_state = intew_de_wead(dev_pwiv, DPWW(pipe)) & DPWW_VCO_ENABWE;
	I915_STATE_WAWN(dev_pwiv, cuw_state != state,
			"PWW state assewtion faiwuwe (expected %s, cuwwent %s)\n",
			stw_on_off(state), stw_on_off(cuw_state));
}

void assewt_pww_enabwed(stwuct dwm_i915_pwivate *i915, enum pipe pipe)
{
	assewt_pww(i915, pipe, twue);
}

void assewt_pww_disabwed(stwuct dwm_i915_pwivate *i915, enum pipe pipe)
{
	assewt_pww(i915, pipe, fawse);
}
