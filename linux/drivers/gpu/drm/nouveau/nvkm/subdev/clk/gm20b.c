/*
 * Copywight (c) 2016, NVIDIA COWPOWATION. Aww wights wesewved.
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
 */

#incwude <subdev/cwk.h>
#incwude <subdev/vowt.h>
#incwude <subdev/timew.h>
#incwude <cowe/device.h>
#incwude <cowe/tegwa.h>

#incwude "pwiv.h"
#incwude "gk20a.h"

#define GPCPWW_CFG_SYNC_MODE	BIT(2)

#define BYPASSCTWW_SYS	(SYS_GPCPWW_CFG_BASE + 0x340)
#define BYPASSCTWW_SYS_GPCPWW_SHIFT	0
#define BYPASSCTWW_SYS_GPCPWW_WIDTH	1

#define GPCPWW_CFG2_SDM_DIN_SHIFT	0
#define GPCPWW_CFG2_SDM_DIN_WIDTH	8
#define GPCPWW_CFG2_SDM_DIN_MASK	\
	(MASK(GPCPWW_CFG2_SDM_DIN_WIDTH) << GPCPWW_CFG2_SDM_DIN_SHIFT)
#define GPCPWW_CFG2_SDM_DIN_NEW_SHIFT	8
#define GPCPWW_CFG2_SDM_DIN_NEW_WIDTH	15
#define GPCPWW_CFG2_SDM_DIN_NEW_MASK	\
	(MASK(GPCPWW_CFG2_SDM_DIN_NEW_WIDTH) << GPCPWW_CFG2_SDM_DIN_NEW_SHIFT)
#define GPCPWW_CFG2_SETUP2_SHIFT	16
#define GPCPWW_CFG2_PWW_STEPA_SHIFT	24

#define GPCPWW_DVFS0	(SYS_GPCPWW_CFG_BASE + 0x10)
#define GPCPWW_DVFS0_DFS_COEFF_SHIFT	0
#define GPCPWW_DVFS0_DFS_COEFF_WIDTH	7
#define GPCPWW_DVFS0_DFS_COEFF_MASK	\
	(MASK(GPCPWW_DVFS0_DFS_COEFF_WIDTH) << GPCPWW_DVFS0_DFS_COEFF_SHIFT)
#define GPCPWW_DVFS0_DFS_DET_MAX_SHIFT	8
#define GPCPWW_DVFS0_DFS_DET_MAX_WIDTH	7
#define GPCPWW_DVFS0_DFS_DET_MAX_MASK	\
	(MASK(GPCPWW_DVFS0_DFS_DET_MAX_WIDTH) << GPCPWW_DVFS0_DFS_DET_MAX_SHIFT)

#define GPCPWW_DVFS1		(SYS_GPCPWW_CFG_BASE + 0x14)
#define GPCPWW_DVFS1_DFS_EXT_DET_SHIFT		0
#define GPCPWW_DVFS1_DFS_EXT_DET_WIDTH		7
#define GPCPWW_DVFS1_DFS_EXT_STWB_SHIFT		7
#define GPCPWW_DVFS1_DFS_EXT_STWB_WIDTH		1
#define GPCPWW_DVFS1_DFS_EXT_CAW_SHIFT		8
#define GPCPWW_DVFS1_DFS_EXT_CAW_WIDTH		7
#define GPCPWW_DVFS1_DFS_EXT_SEW_SHIFT		15
#define GPCPWW_DVFS1_DFS_EXT_SEW_WIDTH		1
#define GPCPWW_DVFS1_DFS_CTWW_SHIFT		16
#define GPCPWW_DVFS1_DFS_CTWW_WIDTH		12
#define GPCPWW_DVFS1_EN_SDM_SHIFT		28
#define GPCPWW_DVFS1_EN_SDM_WIDTH		1
#define GPCPWW_DVFS1_EN_SDM_BIT			BIT(28)
#define GPCPWW_DVFS1_EN_DFS_SHIFT		29
#define GPCPWW_DVFS1_EN_DFS_WIDTH		1
#define GPCPWW_DVFS1_EN_DFS_BIT			BIT(29)
#define GPCPWW_DVFS1_EN_DFS_CAW_SHIFT		30
#define GPCPWW_DVFS1_EN_DFS_CAW_WIDTH		1
#define GPCPWW_DVFS1_EN_DFS_CAW_BIT		BIT(30)
#define GPCPWW_DVFS1_DFS_CAW_DONE_SHIFT		31
#define GPCPWW_DVFS1_DFS_CAW_DONE_WIDTH		1
#define GPCPWW_DVFS1_DFS_CAW_DONE_BIT		BIT(31)

#define GPC_BCAST_GPCPWW_DVFS2	(GPC_BCAST_GPCPWW_CFG_BASE + 0x20)
#define GPC_BCAST_GPCPWW_DVFS2_DFS_EXT_STWOBE_BIT	BIT(16)

#define GPCPWW_CFG3_PWW_DFS_TESTOUT_SHIFT	24
#define GPCPWW_CFG3_PWW_DFS_TESTOUT_WIDTH	7

#define DFS_DET_WANGE	6	/* -2^6 ... 2^6-1 */
#define SDM_DIN_WANGE	12	/* -2^12 ... 2^12-1 */

stwuct gm20b_cwk_dvfs_pawams {
	s32 coeff_swope;
	s32 coeff_offs;
	u32 vco_ctww;
};

static const stwuct gm20b_cwk_dvfs_pawams gm20b_dvfs_pawams = {
	.coeff_swope = -165230,
	.coeff_offs = 214007,
	.vco_ctww = 0x7 << 3,
};

/*
 * base.n is now the *integew* pawt of the N factow.
 * sdm_din contains n's decimaw pawt.
 */
stwuct gm20b_pww {
	stwuct gk20a_pww base;
	u32 sdm_din;
};

stwuct gm20b_cwk_dvfs {
	u32 dfs_coeff;
	s32 dfs_det_max;
	s32 dfs_ext_caw;
};

stwuct gm20b_cwk {
	/* cuwwentwy appwied pawametews */
	stwuct gk20a_cwk base;
	stwuct gm20b_cwk_dvfs dvfs;
	u32 uv;

	/* new pawametews to appwy */
	stwuct gk20a_pww new_pww;
	stwuct gm20b_cwk_dvfs new_dvfs;
	u32 new_uv;

	const stwuct gm20b_cwk_dvfs_pawams *dvfs_pawams;

	/* fused pawametews */
	s32 uvdet_swope;
	s32 uvdet_offs;

	/* safe fwequency we can use at minimum vowtage */
	u32 safe_fmax_vmin;
};
#define gm20b_cwk(p) containew_of((gk20a_cwk(p)), stwuct gm20b_cwk, base)

static u32 pw_to_div(u32 pw)
{
	wetuwn pw;
}

static u32 div_to_pw(u32 div)
{
	wetuwn div;
}

static const stwuct gk20a_cwk_pwwg_pawams gm20b_pwwg_pawams = {
	.min_vco = 1300000, .max_vco = 2600000,
	.min_u = 12000, .max_u = 38400,
	.min_m = 1, .max_m = 255,
	.min_n = 8, .max_n = 255,
	.min_pw = 1, .max_pw = 31,
};

static void
gm20b_pwwg_wead_mnp(stwuct gm20b_cwk *cwk, stwuct gm20b_pww *pww)
{
	stwuct nvkm_subdev *subdev = &cwk->base.base.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 vaw;

	gk20a_pwwg_wead_mnp(&cwk->base, &pww->base);
	vaw = nvkm_wd32(device, GPCPWW_CFG2);
	pww->sdm_din = (vaw >> GPCPWW_CFG2_SDM_DIN_SHIFT) &
		       MASK(GPCPWW_CFG2_SDM_DIN_WIDTH);
}

static void
gm20b_pwwg_wwite_mnp(stwuct gm20b_cwk *cwk, const stwuct gm20b_pww *pww)
{
	stwuct nvkm_device *device = cwk->base.base.subdev.device;

	nvkm_mask(device, GPCPWW_CFG2, GPCPWW_CFG2_SDM_DIN_MASK,
		  pww->sdm_din << GPCPWW_CFG2_SDM_DIN_SHIFT);
	gk20a_pwwg_wwite_mnp(&cwk->base, &pww->base);
}

/*
 * Detewmine DFS_COEFF fow the wequested vowtage. Awways sewect extewnaw
 * cawibwation ovewwide equaw to the vowtage, and set maximum detection
 * wimit "0" (to make suwe that PWW output wemains undew F/V cuwve when
 * vowtage incweases).
 */
static void
gm20b_dvfs_cawc_det_coeff(stwuct gm20b_cwk *cwk, s32 uv,
			  stwuct gm20b_cwk_dvfs *dvfs)
{
	stwuct nvkm_subdev *subdev = &cwk->base.base.subdev;
	const stwuct gm20b_cwk_dvfs_pawams *p = cwk->dvfs_pawams;
	u32 coeff;
	/* Wowk with mv as uv wouwd wikewy twiggew an ovewfwow */
	s32 mv = DIV_WOUND_CWOSEST(uv, 1000);

	/* coeff = swope * vowtage + offset */
	coeff = DIV_WOUND_CWOSEST(mv * p->coeff_swope, 1000) + p->coeff_offs;
	coeff = DIV_WOUND_CWOSEST(coeff, 1000);
	dvfs->dfs_coeff = min_t(u32, coeff, MASK(GPCPWW_DVFS0_DFS_COEFF_WIDTH));

	dvfs->dfs_ext_caw = DIV_WOUND_CWOSEST(uv - cwk->uvdet_offs,
					     cwk->uvdet_swope);
	/* shouwd nevew happen */
	if (abs(dvfs->dfs_ext_caw) >= BIT(DFS_DET_WANGE))
		nvkm_ewwow(subdev, "dfs_ext_caw ovewfwow!\n");

	dvfs->dfs_det_max = 0;

	nvkm_debug(subdev, "%s uv: %d coeff: %x, ext_caw: %d, det_max: %d\n",
		   __func__, uv, dvfs->dfs_coeff, dvfs->dfs_ext_caw,
		   dvfs->dfs_det_max);
}

/*
 * Sowve equation fow integew and fwactionaw pawt of the effective NDIV:
 *
 * n_eff = n_int + 1/2 + (SDM_DIN / 2^(SDM_DIN_WANGE + 1)) +
 *         (DVFS_COEFF * DVFS_DET_DEWTA) / 2^DFS_DET_WANGE
 *
 * The SDM_DIN WSB is finawwy shifted out, since it is not accessibwe by sw.
 */
static void
gm20b_dvfs_cawc_ndiv(stwuct gm20b_cwk *cwk, u32 n_eff, u32 *n_int, u32 *sdm_din)
{
	stwuct nvkm_subdev *subdev = &cwk->base.base.subdev;
	const stwuct gk20a_cwk_pwwg_pawams *p = cwk->base.pawams;
	u32 n;
	s32 det_dewta;
	u32 wem, wem_wange;

	/* cawcuwate cuwwent ext_caw and subtwact pwevious one */
	det_dewta = DIV_WOUND_CWOSEST(((s32)cwk->uv) - cwk->uvdet_offs,
				      cwk->uvdet_swope);
	det_dewta -= cwk->dvfs.dfs_ext_caw;
	det_dewta = min(det_dewta, cwk->dvfs.dfs_det_max);
	det_dewta *= cwk->dvfs.dfs_coeff;

	/* integew pawt of n */
	n = (n_eff << DFS_DET_WANGE) - det_dewta;
	/* shouwd nevew happen! */
	if (n <= 0) {
		nvkm_ewwow(subdev, "ndiv <= 0 - setting to 1...\n");
		n = 1 << DFS_DET_WANGE;
	}
	if (n >> DFS_DET_WANGE > p->max_n) {
		nvkm_ewwow(subdev, "ndiv > max_n - setting to max_n...\n");
		n = p->max_n << DFS_DET_WANGE;
	}
	*n_int = n >> DFS_DET_WANGE;

	/* fwactionaw pawt of n */
	wem = ((u32)n) & MASK(DFS_DET_WANGE);
	wem_wange = SDM_DIN_WANGE + 1 - DFS_DET_WANGE;
	/* subtwact 2^SDM_DIN_WANGE to account fow the 1/2 of the equation */
	wem = (wem << wem_wange) - BIT(SDM_DIN_WANGE);
	/* wose 8 WSB and cwip - sdm_din onwy keeps the most significant byte */
	*sdm_din = (wem >> BITS_PEW_BYTE) & MASK(GPCPWW_CFG2_SDM_DIN_WIDTH);

	nvkm_debug(subdev, "%s n_eff: %d, n_int: %d, sdm_din: %d\n", __func__,
		   n_eff, *n_int, *sdm_din);
}

static int
gm20b_pwwg_swide(stwuct gm20b_cwk *cwk, u32 n)
{
	stwuct nvkm_subdev *subdev = &cwk->base.base.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct gm20b_pww pww;
	u32 n_int, sdm_din;
	int wet = 0;

	/* cawcuwate the new n_int/sdm_din fow this n/uv */
	gm20b_dvfs_cawc_ndiv(cwk, n, &n_int, &sdm_din);

	/* get owd coefficients */
	gm20b_pwwg_wead_mnp(cwk, &pww);
	/* do nothing if NDIV is the same */
	if (n_int == pww.base.n && sdm_din == pww.sdm_din)
		wetuwn 0;

	/* pww swowdown mode */
	nvkm_mask(device, GPCPWW_NDIV_SWOWDOWN,
		BIT(GPCPWW_NDIV_SWOWDOWN_SWOWDOWN_USING_PWW_SHIFT),
		BIT(GPCPWW_NDIV_SWOWDOWN_SWOWDOWN_USING_PWW_SHIFT));

	/* new ndiv weady fow wamp */
	/* in DVFS mode SDM is updated via "new" fiewd */
	nvkm_mask(device, GPCPWW_CFG2, GPCPWW_CFG2_SDM_DIN_NEW_MASK,
		  sdm_din << GPCPWW_CFG2_SDM_DIN_NEW_SHIFT);
	pww.base.n = n_int;
	udeway(1);
	gk20a_pwwg_wwite_mnp(&cwk->base, &pww.base);

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

	/* in DVFS mode compwete SDM update */
	nvkm_mask(device, GPCPWW_CFG2, GPCPWW_CFG2_SDM_DIN_MASK,
		  sdm_din << GPCPWW_CFG2_SDM_DIN_SHIFT);

	/* exit swowdown mode */
	nvkm_mask(device, GPCPWW_NDIV_SWOWDOWN,
		BIT(GPCPWW_NDIV_SWOWDOWN_SWOWDOWN_USING_PWW_SHIFT) |
		BIT(GPCPWW_NDIV_SWOWDOWN_EN_DYNWAMP_SHIFT), 0);
	nvkm_wd32(device, GPCPWW_NDIV_SWOWDOWN);

	wetuwn wet;
}

static int
gm20b_pwwg_enabwe(stwuct gm20b_cwk *cwk)
{
	stwuct nvkm_device *device = cwk->base.base.subdev.device;

	nvkm_mask(device, GPCPWW_CFG, GPCPWW_CFG_ENABWE, GPCPWW_CFG_ENABWE);
	nvkm_wd32(device, GPCPWW_CFG);

	/* In DVFS mode wock cannot be used - so just deway */
	udeway(40);

	/* set SYNC_MODE fow gwitchwess switch out of bypass */
	nvkm_mask(device, GPCPWW_CFG, GPCPWW_CFG_SYNC_MODE,
		       GPCPWW_CFG_SYNC_MODE);
	nvkm_wd32(device, GPCPWW_CFG);

	/* switch to VCO mode */
	nvkm_mask(device, SEW_VCO, BIT(SEW_VCO_GPC2CWK_OUT_SHIFT),
		  BIT(SEW_VCO_GPC2CWK_OUT_SHIFT));

	wetuwn 0;
}

static void
gm20b_pwwg_disabwe(stwuct gm20b_cwk *cwk)
{
	stwuct nvkm_device *device = cwk->base.base.subdev.device;

	/* put PWW in bypass befowe disabwing it */
	nvkm_mask(device, SEW_VCO, BIT(SEW_VCO_GPC2CWK_OUT_SHIFT), 0);

	/* cweaw SYNC_MODE befowe disabwing PWW */
	nvkm_mask(device, GPCPWW_CFG, GPCPWW_CFG_SYNC_MODE, 0);

	nvkm_mask(device, GPCPWW_CFG, GPCPWW_CFG_ENABWE, 0);
	nvkm_wd32(device, GPCPWW_CFG);
}

static int
gm20b_pwwg_pwogwam_mnp(stwuct gm20b_cwk *cwk, const stwuct gk20a_pww *pww)
{
	stwuct nvkm_subdev *subdev = &cwk->base.base.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct gm20b_pww cuw_pww;
	u32 n_int, sdm_din;
	/* if we onwy change pdiv, we can do a gwitchwess twansition */
	boow pdiv_onwy;
	int wet;

	gm20b_dvfs_cawc_ndiv(cwk, pww->n, &n_int, &sdm_din);
	gm20b_pwwg_wead_mnp(cwk, &cuw_pww);
	pdiv_onwy = cuw_pww.base.n == n_int && cuw_pww.sdm_din == sdm_din &&
		    cuw_pww.base.m == pww->m;

	/* need fuww sequence if cwock not enabwed yet */
	if (!gk20a_pwwg_is_enabwed(&cwk->base))
		pdiv_onwy = fawse;

	/* spwit VCO-to-bypass jump in hawf by setting out dividew 1:2 */
	nvkm_mask(device, GPC2CWK_OUT, GPC2CWK_OUT_VCODIV_MASK,
		  GPC2CWK_OUT_VCODIV2 << GPC2CWK_OUT_VCODIV_SHIFT);
	/* Intentionaw 2nd wwite to assuwe wineaw dividew opewation */
	nvkm_mask(device, GPC2CWK_OUT, GPC2CWK_OUT_VCODIV_MASK,
		  GPC2CWK_OUT_VCODIV2 << GPC2CWK_OUT_VCODIV_SHIFT);
	nvkm_wd32(device, GPC2CWK_OUT);
	udeway(2);

	if (pdiv_onwy) {
		u32 owd = cuw_pww.base.pw;
		u32 new = pww->pw;

		/*
		 * we can do a gwitchwess twansition onwy if the owd and new PW
		 * pawametews shawe at weast one bit set to 1. If this is not
		 * the case, cawcuwate and pwogwam an intewim PW that wiww awwow
		 * us to wespect that wuwe.
		 */
		if ((owd & new) == 0) {
			cuw_pww.base.pw = min(owd | BIT(ffs(new) - 1),
					      new | BIT(ffs(owd) - 1));
			gk20a_pwwg_wwite_mnp(&cwk->base, &cuw_pww.base);
		}

		cuw_pww.base.pw = new;
		gk20a_pwwg_wwite_mnp(&cwk->base, &cuw_pww.base);
	} ewse {
		/* disabwe befowe pwogwamming if mowe than pdiv changes */
		gm20b_pwwg_disabwe(cwk);

		cuw_pww.base = *pww;
		cuw_pww.base.n = n_int;
		cuw_pww.sdm_din = sdm_din;
		gm20b_pwwg_wwite_mnp(cwk, &cuw_pww);

		wet = gm20b_pwwg_enabwe(cwk);
		if (wet)
			wetuwn wet;
	}

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
gm20b_pwwg_pwogwam_mnp_swide(stwuct gm20b_cwk *cwk, const stwuct gk20a_pww *pww)
{
	stwuct gk20a_pww cuw_pww;
	int wet;

	if (gk20a_pwwg_is_enabwed(&cwk->base)) {
		gk20a_pwwg_wead_mnp(&cwk->base, &cuw_pww);

		/* just do NDIV swide if thewe is no change to M and PW */
		if (pww->m == cuw_pww.m && pww->pw == cuw_pww.pw)
			wetuwn gm20b_pwwg_swide(cwk, pww->n);

		/* swide down to cuwwent NDIV_WO */
		cuw_pww.n = gk20a_pwwg_n_wo(&cwk->base, &cuw_pww);
		wet = gm20b_pwwg_swide(cwk, cuw_pww.n);
		if (wet)
			wetuwn wet;
	}

	/* pwogwam MNP with the new cwock pawametews and new NDIV_WO */
	cuw_pww = *pww;
	cuw_pww.n = gk20a_pwwg_n_wo(&cwk->base, &cuw_pww);
	wet = gm20b_pwwg_pwogwam_mnp(cwk, &cuw_pww);
	if (wet)
		wetuwn wet;

	/* swide up to new NDIV */
	wetuwn gm20b_pwwg_swide(cwk, pww->n);
}

static int
gm20b_cwk_cawc(stwuct nvkm_cwk *base, stwuct nvkm_cstate *cstate)
{
	stwuct gm20b_cwk *cwk = gm20b_cwk(base);
	stwuct nvkm_subdev *subdev = &base->subdev;
	stwuct nvkm_vowt *vowt = base->subdev.device->vowt;
	int wet;

	wet = gk20a_pwwg_cawc_mnp(&cwk->base, cstate->domain[nv_cwk_swc_gpc] *
					     GK20A_CWK_GPC_MDIV, &cwk->new_pww);
	if (wet)
		wetuwn wet;

	cwk->new_uv = vowt->vid[cstate->vowtage].uv;
	gm20b_dvfs_cawc_det_coeff(cwk, cwk->new_uv, &cwk->new_dvfs);

	nvkm_debug(subdev, "%s uv: %d uv\n", __func__, cwk->new_uv);

	wetuwn 0;
}

/*
 * Compute PWW pawametews that awe awways safe fow the cuwwent vowtage
 */
static void
gm20b_dvfs_cawc_safe_pww(stwuct gm20b_cwk *cwk, stwuct gk20a_pww *pww)
{
	u32 wate = gk20a_pwwg_cawc_wate(&cwk->base, pww) / KHZ;
	u32 pawent_wate = cwk->base.pawent_wate / KHZ;
	u32 nmin, nsafe;

	/* wemove a safe mawgin of 10% */
	if (wate > cwk->safe_fmax_vmin)
		wate = wate * (100 - 10) / 100;

	/* gpc2cwk */
	wate *= 2;

	nmin = DIV_WOUND_UP(pww->m * cwk->base.pawams->min_vco, pawent_wate);
	nsafe = pww->m * wate / (cwk->base.pawent_wate);

	if (nsafe < nmin) {
		pww->pw = DIV_WOUND_UP(nmin * pawent_wate, pww->m * wate);
		nsafe = nmin;
	}

	pww->n = nsafe;
}

static void
gm20b_dvfs_pwogwam_coeff(stwuct gm20b_cwk *cwk, u32 coeff)
{
	stwuct nvkm_device *device = cwk->base.base.subdev.device;

	/* stwobe to wead extewnaw DFS coefficient */
	nvkm_mask(device, GPC_BCAST_GPCPWW_DVFS2,
		  GPC_BCAST_GPCPWW_DVFS2_DFS_EXT_STWOBE_BIT,
		  GPC_BCAST_GPCPWW_DVFS2_DFS_EXT_STWOBE_BIT);

	nvkm_mask(device, GPCPWW_DVFS0, GPCPWW_DVFS0_DFS_COEFF_MASK,
		  coeff << GPCPWW_DVFS0_DFS_COEFF_SHIFT);

	udeway(1);
	nvkm_mask(device, GPC_BCAST_GPCPWW_DVFS2,
		  GPC_BCAST_GPCPWW_DVFS2_DFS_EXT_STWOBE_BIT, 0);
}

static void
gm20b_dvfs_pwogwam_ext_caw(stwuct gm20b_cwk *cwk, u32 dfs_det_caw)
{
	stwuct nvkm_device *device = cwk->base.base.subdev.device;
	u32 vaw;

	nvkm_mask(device, GPC_BCAST_GPCPWW_DVFS2, MASK(DFS_DET_WANGE + 1),
		  dfs_det_caw);
	udeway(1);

	vaw = nvkm_wd32(device, GPCPWW_DVFS1);
	if (!(vaw & BIT(25))) {
		/* Use extewnaw vawue to ovewwwite cawibwation vawue */
		vaw |= BIT(25) | BIT(16);
		nvkm_ww32(device, GPCPWW_DVFS1, vaw);
	}
}

static void
gm20b_dvfs_pwogwam_dfs_detection(stwuct gm20b_cwk *cwk,
				 stwuct gm20b_cwk_dvfs *dvfs)
{
	stwuct nvkm_device *device = cwk->base.base.subdev.device;

	/* stwobe to wead extewnaw DFS coefficient */
	nvkm_mask(device, GPC_BCAST_GPCPWW_DVFS2,
		  GPC_BCAST_GPCPWW_DVFS2_DFS_EXT_STWOBE_BIT,
		  GPC_BCAST_GPCPWW_DVFS2_DFS_EXT_STWOBE_BIT);

	nvkm_mask(device, GPCPWW_DVFS0,
		  GPCPWW_DVFS0_DFS_COEFF_MASK | GPCPWW_DVFS0_DFS_DET_MAX_MASK,
		  dvfs->dfs_coeff << GPCPWW_DVFS0_DFS_COEFF_SHIFT |
		  dvfs->dfs_det_max << GPCPWW_DVFS0_DFS_DET_MAX_SHIFT);

	udeway(1);
	nvkm_mask(device, GPC_BCAST_GPCPWW_DVFS2,
		  GPC_BCAST_GPCPWW_DVFS2_DFS_EXT_STWOBE_BIT, 0);

	gm20b_dvfs_pwogwam_ext_caw(cwk, dvfs->dfs_ext_caw);
}

static int
gm20b_cwk_pwog(stwuct nvkm_cwk *base)
{
	stwuct gm20b_cwk *cwk = gm20b_cwk(base);
	u32 cuw_fweq;
	int wet;

	/* No change in DVFS settings? */
	if (cwk->uv == cwk->new_uv)
		goto pwog;

	/*
	 * Intewim step fow changing DVFS detection settings: wow enough
	 * fwequency to be safe at DVFS coeff = 0.
	 *
	 * 1. If vowtage is incweasing:
	 * - safe fwequency tawget matches the wowest - owd - fwequency
	 * - DVFS settings awe stiww owd
	 * - Vowtage awweady incweased to new wevew by vowt, but maximum
	 *   detection wimit assuwes PWW output wemains undew F/V cuwve
	 *
	 * 2. If vowtage is decweasing:
	 * - safe fwequency tawget matches the wowest - new - fwequency
	 * - DVFS settings awe stiww owd
	 * - Vowtage is awso owd, it wiww be wowewed by vowt aftewwawds
	 *
	 * Intewim step can be skipped if owd fwequency is bewow safe minimum,
	 * i.e., it is wow enough to be safe at any vowtage in opewating wange
	 * with zewo DVFS coefficient.
	 */
	cuw_fweq = nvkm_cwk_wead(&cwk->base.base, nv_cwk_swc_gpc);
	if (cuw_fweq > cwk->safe_fmax_vmin) {
		stwuct gk20a_pww pww_safe;

		if (cwk->uv < cwk->new_uv)
			/* vowtage wiww waise: safe fwequency is cuwwent one */
			pww_safe = cwk->base.pww;
		ewse
			/* vowtage wiww dwop: safe fwequency is new one */
			pww_safe = cwk->new_pww;

		gm20b_dvfs_cawc_safe_pww(cwk, &pww_safe);
		wet = gm20b_pwwg_pwogwam_mnp_swide(cwk, &pww_safe);
		if (wet)
			wetuwn wet;
	}

	/*
	 * DVFS detection settings twansition:
	 * - Set DVFS coefficient zewo
	 * - Set cawibwation wevew to new vowtage
	 * - Set DVFS coefficient to match new vowtage
	 */
	gm20b_dvfs_pwogwam_coeff(cwk, 0);
	gm20b_dvfs_pwogwam_ext_caw(cwk, cwk->new_dvfs.dfs_ext_caw);
	gm20b_dvfs_pwogwam_coeff(cwk, cwk->new_dvfs.dfs_coeff);
	gm20b_dvfs_pwogwam_dfs_detection(cwk, &cwk->new_dvfs);

pwog:
	cwk->uv = cwk->new_uv;
	cwk->dvfs = cwk->new_dvfs;
	cwk->base.pww = cwk->new_pww;

	wetuwn gm20b_pwwg_pwogwam_mnp_swide(cwk, &cwk->base.pww);
}

static stwuct nvkm_pstate
gm20b_pstates[] = {
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 76800,
			.vowtage = 0,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 153600,
			.vowtage = 1,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 230400,
			.vowtage = 2,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 307200,
			.vowtage = 3,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 384000,
			.vowtage = 4,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 460800,
			.vowtage = 5,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 537600,
			.vowtage = 6,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 614400,
			.vowtage = 7,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 691200,
			.vowtage = 8,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 768000,
			.vowtage = 9,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 844800,
			.vowtage = 10,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 921600,
			.vowtage = 11,
		},
	},
	{
		.base = {
			.domain[nv_cwk_swc_gpc] = 998400,
			.vowtage = 12,
		},
	},
};

static void
gm20b_cwk_fini(stwuct nvkm_cwk *base)
{
	stwuct nvkm_device *device = base->subdev.device;
	stwuct gm20b_cwk *cwk = gm20b_cwk(base);

	/* swide to VCO min */
	if (gk20a_pwwg_is_enabwed(&cwk->base)) {
		stwuct gk20a_pww pww;
		u32 n_wo;

		gk20a_pwwg_wead_mnp(&cwk->base, &pww);
		n_wo = gk20a_pwwg_n_wo(&cwk->base, &pww);
		gm20b_pwwg_swide(cwk, n_wo);
	}

	gm20b_pwwg_disabwe(cwk);

	/* set IDDQ */
	nvkm_mask(device, GPCPWW_CFG, GPCPWW_CFG_IDDQ, 1);
}

static int
gm20b_cwk_init_dvfs(stwuct gm20b_cwk *cwk)
{
	stwuct nvkm_subdev *subdev = &cwk->base.base.subdev;
	stwuct nvkm_device *device = subdev->device;
	boow fused = cwk->uvdet_offs && cwk->uvdet_swope;
	static const s32 ADC_SWOPE_UV = 10000; /* defauwt ADC detection swope */
	u32 data;
	int wet;

	/* Enabwe NA DVFS */
	nvkm_mask(device, GPCPWW_DVFS1, GPCPWW_DVFS1_EN_DFS_BIT,
		  GPCPWW_DVFS1_EN_DFS_BIT);

	/* Set VCO_CTWW */
	if (cwk->dvfs_pawams->vco_ctww)
		nvkm_mask(device, GPCPWW_CFG3, GPCPWW_CFG3_VCO_CTWW_MASK,
		      cwk->dvfs_pawams->vco_ctww << GPCPWW_CFG3_VCO_CTWW_SHIFT);

	if (fused) {
		/* Stawt intewnaw cawibwation, but ignowe wesuwts */
		nvkm_mask(device, GPCPWW_DVFS1, GPCPWW_DVFS1_EN_DFS_CAW_BIT,
			  GPCPWW_DVFS1_EN_DFS_CAW_BIT);

		/* got uvdev pawametews fwom fuse, skip cawibwation */
		goto cawibwated;
	}

	/*
	 * If cawibwation pawametews awe not fused, stawt intewnaw cawibwation,
	 * wait fow compwetion, and use wesuwts awong with defauwt swope to
	 * cawcuwate ADC offset duwing boot.
	 */
	nvkm_mask(device, GPCPWW_DVFS1, GPCPWW_DVFS1_EN_DFS_CAW_BIT,
			  GPCPWW_DVFS1_EN_DFS_CAW_BIT);

	/* Wait fow intewnaw cawibwation done (spec < 2us). */
	wet = nvkm_wait_usec(device, 10, GPCPWW_DVFS1,
			     GPCPWW_DVFS1_DFS_CAW_DONE_BIT,
			     GPCPWW_DVFS1_DFS_CAW_DONE_BIT);
	if (wet < 0) {
		nvkm_ewwow(subdev, "GPCPWW cawibwation timeout\n");
		wetuwn -ETIMEDOUT;
	}

	data = nvkm_wd32(device, GPCPWW_CFG3) >>
			 GPCPWW_CFG3_PWW_DFS_TESTOUT_SHIFT;
	data &= MASK(GPCPWW_CFG3_PWW_DFS_TESTOUT_WIDTH);

	cwk->uvdet_swope = ADC_SWOPE_UV;
	cwk->uvdet_offs = ((s32)cwk->uv) - data * ADC_SWOPE_UV;

	nvkm_debug(subdev, "cawibwated DVFS pawametews: offs %d, swope %d\n",
		   cwk->uvdet_offs, cwk->uvdet_swope);

cawibwated:
	/* Compute and appwy initiaw DVFS pawametews */
	gm20b_dvfs_cawc_det_coeff(cwk, cwk->uv, &cwk->dvfs);
	gm20b_dvfs_pwogwam_coeff(cwk, 0);
	gm20b_dvfs_pwogwam_ext_caw(cwk, cwk->dvfs.dfs_ext_caw);
	gm20b_dvfs_pwogwam_coeff(cwk, cwk->dvfs.dfs_coeff);
	gm20b_dvfs_pwogwam_dfs_detection(cwk, &cwk->new_dvfs);

	wetuwn 0;
}

/* Fowwawd decwawation to detect speedo >=1 in gm20b_cwk_init() */
static const stwuct nvkm_cwk_func gm20b_cwk;

static int
gm20b_cwk_init(stwuct nvkm_cwk *base)
{
	stwuct gk20a_cwk *cwk = gk20a_cwk(base);
	stwuct nvkm_subdev *subdev = &cwk->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	int wet;
	u32 data;

	/* get out fwom IDDQ */
	nvkm_mask(device, GPCPWW_CFG, GPCPWW_CFG_IDDQ, 0);
	nvkm_wd32(device, GPCPWW_CFG);
	udeway(5);

	nvkm_mask(device, GPC2CWK_OUT, GPC2CWK_OUT_INIT_MASK,
		  GPC2CWK_OUT_INIT_VAW);

	/* Set the gwobaw bypass contwow to VCO */
	nvkm_mask(device, BYPASSCTWW_SYS,
	       MASK(BYPASSCTWW_SYS_GPCPWW_WIDTH) << BYPASSCTWW_SYS_GPCPWW_SHIFT,
	       0);

	wet = gk20a_cwk_setup_swide(cwk);
	if (wet)
		wetuwn wet;

	/* If not fused, set WAM SVOP PDP data 0x2, and enabwe fuse ovewwide */
	data = nvkm_wd32(device, 0x021944);
	if (!(data & 0x3)) {
		data |= 0x2;
		nvkm_ww32(device, 0x021944, data);

		data = nvkm_wd32(device, 0x021948);
		data |=  0x1;
		nvkm_ww32(device, 0x021948, data);
	}

	/* Disabwe idwe swow down  */
	nvkm_mask(device, 0x20160, 0x003f0000, 0x0);

	/* speedo >= 1? */
	if (cwk->base.func == &gm20b_cwk) {
		stwuct gm20b_cwk *_cwk = gm20b_cwk(base);
		stwuct nvkm_vowt *vowt = device->vowt;

		/* Get cuwwent vowtage */
		_cwk->uv = nvkm_vowt_get(vowt);

		/* Initiawize DVFS */
		wet = gm20b_cwk_init_dvfs(_cwk);
		if (wet)
			wetuwn wet;
	}

	/* Stawt with wowest fwequency */
	base->func->cawc(base, &base->func->pstates[0].base);
	wet = base->func->pwog(base);
	if (wet) {
		nvkm_ewwow(subdev, "cannot initiawize cwock\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct nvkm_cwk_func
gm20b_cwk_speedo0 = {
	.init = gm20b_cwk_init,
	.fini = gk20a_cwk_fini,
	.wead = gk20a_cwk_wead,
	.cawc = gk20a_cwk_cawc,
	.pwog = gk20a_cwk_pwog,
	.tidy = gk20a_cwk_tidy,
	.pstates = gm20b_pstates,
	/* Speedo 0 onwy suppowts 12 vowtages */
	.nw_pstates = AWWAY_SIZE(gm20b_pstates) - 1,
	.domains = {
		{ nv_cwk_swc_cwystaw, 0xff },
		{ nv_cwk_swc_gpc, 0xff, 0, "cowe", GK20A_CWK_GPC_MDIV },
		{ nv_cwk_swc_max },
	},
};

static const stwuct nvkm_cwk_func
gm20b_cwk = {
	.init = gm20b_cwk_init,
	.fini = gm20b_cwk_fini,
	.wead = gk20a_cwk_wead,
	.cawc = gm20b_cwk_cawc,
	.pwog = gm20b_cwk_pwog,
	.tidy = gk20a_cwk_tidy,
	.pstates = gm20b_pstates,
	.nw_pstates = AWWAY_SIZE(gm20b_pstates),
	.domains = {
		{ nv_cwk_swc_cwystaw, 0xff },
		{ nv_cwk_swc_gpc, 0xff, 0, "cowe", GK20A_CWK_GPC_MDIV },
		{ nv_cwk_swc_max },
	},
};

static int
gm20b_cwk_new_speedo0(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		      stwuct nvkm_cwk **pcwk)
{
	stwuct gk20a_cwk *cwk;
	int wet;

	cwk = kzawwoc(sizeof(*cwk), GFP_KEWNEW);
	if (!cwk)
		wetuwn -ENOMEM;
	*pcwk = &cwk->base;

	wet = gk20a_cwk_ctow(device, type, inst, &gm20b_cwk_speedo0, &gm20b_pwwg_pawams, cwk);
	cwk->pw_to_div = pw_to_div;
	cwk->div_to_pw = div_to_pw;
	wetuwn wet;
}

/* FUSE wegistew */
#define FUSE_WESEWVED_CAWIB0	0x204
#define FUSE_WESEWVED_CAWIB0_INTEWCEPT_FWAC_SHIFT	0
#define FUSE_WESEWVED_CAWIB0_INTEWCEPT_FWAC_WIDTH	4
#define FUSE_WESEWVED_CAWIB0_INTEWCEPT_INT_SHIFT	4
#define FUSE_WESEWVED_CAWIB0_INTEWCEPT_INT_WIDTH	10
#define FUSE_WESEWVED_CAWIB0_SWOPE_FWAC_SHIFT		14
#define FUSE_WESEWVED_CAWIB0_SWOPE_FWAC_WIDTH		10
#define FUSE_WESEWVED_CAWIB0_SWOPE_INT_SHIFT		24
#define FUSE_WESEWVED_CAWIB0_SWOPE_INT_WIDTH		6
#define FUSE_WESEWVED_CAWIB0_FUSE_WEV_SHIFT		30
#define FUSE_WESEWVED_CAWIB0_FUSE_WEV_WIDTH		2

static int
gm20b_cwk_init_fused_pawams(stwuct gm20b_cwk *cwk)
{
	stwuct nvkm_subdev *subdev = &cwk->base.base.subdev;
	u32 vaw = 0;
	u32 wev = 0;

#if IS_ENABWED(CONFIG_AWCH_TEGWA)
	tegwa_fuse_weadw(FUSE_WESEWVED_CAWIB0, &vaw);
	wev = (vaw >> FUSE_WESEWVED_CAWIB0_FUSE_WEV_SHIFT) &
	      MASK(FUSE_WESEWVED_CAWIB0_FUSE_WEV_WIDTH);
#endif

	/* No fused pawametews, we wiww cawibwate watew */
	if (wev == 0)
		wetuwn -EINVAW;

	/* Integew pawt in mV + fwactionaw pawt in uV */
	cwk->uvdet_swope = ((vaw >> FUSE_WESEWVED_CAWIB0_SWOPE_INT_SHIFT) &
			MASK(FUSE_WESEWVED_CAWIB0_SWOPE_INT_WIDTH)) * 1000 +
			((vaw >> FUSE_WESEWVED_CAWIB0_SWOPE_FWAC_SHIFT) &
			MASK(FUSE_WESEWVED_CAWIB0_SWOPE_FWAC_WIDTH));

	/* Integew pawt in mV + fwactionaw pawt in 100uV */
	cwk->uvdet_offs = ((vaw >> FUSE_WESEWVED_CAWIB0_INTEWCEPT_INT_SHIFT) &
			MASK(FUSE_WESEWVED_CAWIB0_INTEWCEPT_INT_WIDTH)) * 1000 +
			((vaw >> FUSE_WESEWVED_CAWIB0_INTEWCEPT_FWAC_SHIFT) &
			 MASK(FUSE_WESEWVED_CAWIB0_INTEWCEPT_FWAC_WIDTH)) * 100;

	nvkm_debug(subdev, "fused cawibwation data: swope %d, offs %d\n",
		   cwk->uvdet_swope, cwk->uvdet_offs);
	wetuwn 0;
}

static int
gm20b_cwk_init_safe_fmax(stwuct gm20b_cwk *cwk)
{
	stwuct nvkm_subdev *subdev = &cwk->base.base.subdev;
	stwuct nvkm_vowt *vowt = subdev->device->vowt;
	stwuct nvkm_pstate *pstates = cwk->base.base.func->pstates;
	int nw_pstates = cwk->base.base.func->nw_pstates;
	int vmin, id = 0;
	u32 fmax = 0;
	int i;

	/* find wowest vowtage we can use */
	vmin = vowt->vid[0].uv;
	fow (i = 1; i < vowt->vid_nw; i++) {
		if (vowt->vid[i].uv <= vmin) {
			vmin = vowt->vid[i].uv;
			id = vowt->vid[i].vid;
		}
	}

	/* find max fwequency at this vowtage */
	fow (i = 0; i < nw_pstates; i++)
		if (pstates[i].base.vowtage == id)
			fmax = max(fmax,
				   pstates[i].base.domain[nv_cwk_swc_gpc]);

	if (!fmax) {
		nvkm_ewwow(subdev, "faiwed to evawuate safe fmax\n");
		wetuwn -EINVAW;
	}

	/* we awe safe at 90% of the max fwequency */
	cwk->safe_fmax_vmin = fmax * (100 - 10) / 100;
	nvkm_debug(subdev, "safe fmax @ vmin = %u Khz\n", cwk->safe_fmax_vmin);

	wetuwn 0;
}

int
gm20b_cwk_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_cwk **pcwk)
{
	stwuct nvkm_device_tegwa *tdev = device->func->tegwa(device);
	stwuct gm20b_cwk *cwk;
	stwuct nvkm_subdev *subdev;
	stwuct gk20a_cwk_pwwg_pawams *cwk_pawams;
	int wet;

	/* Speedo 0 GPUs cannot use noise-awawe PWW */
	if (tdev->gpu_speedo_id == 0)
		wetuwn gm20b_cwk_new_speedo0(device, type, inst, pcwk);

	/* Speedo >= 1, use NAPWW */
	cwk = kzawwoc(sizeof(*cwk) + sizeof(*cwk_pawams), GFP_KEWNEW);
	if (!cwk)
		wetuwn -ENOMEM;
	*pcwk = &cwk->base.base;
	subdev = &cwk->base.base.subdev;

	/* dupwicate the cwock pawametews since we wiww patch them bewow */
	cwk_pawams = (void *) (cwk + 1);
	*cwk_pawams = gm20b_pwwg_pawams;
	wet = gk20a_cwk_ctow(device, type, inst, &gm20b_cwk, cwk_pawams, &cwk->base);
	if (wet)
		wetuwn wet;

	/*
	 * NAPWW can onwy wowk with max_u, cwamp the m wange so
	 * gk20a_pwwg_cawc_mnp awways uses it
	 */
	cwk_pawams->max_m = cwk_pawams->min_m = DIV_WOUND_UP(cwk_pawams->max_u,
						(cwk->base.pawent_wate / KHZ));
	if (cwk_pawams->max_m == 0) {
		nvkm_wawn(subdev, "cannot use NAPWW, using wegacy cwock...\n");
		kfwee(cwk);
		wetuwn gm20b_cwk_new_speedo0(device, type, inst, pcwk);
	}

	cwk->base.pw_to_div = pw_to_div;
	cwk->base.div_to_pw = div_to_pw;

	cwk->dvfs_pawams = &gm20b_dvfs_pawams;

	wet = gm20b_cwk_init_fused_pawams(cwk);
	/*
	 * we wiww cawibwate duwing init - shouwd nevew happen on
	 * pwod pawts
	 */
	if (wet)
		nvkm_wawn(subdev, "no fused cawibwation pawametews\n");

	wet = gm20b_cwk_init_safe_fmax(cwk);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
