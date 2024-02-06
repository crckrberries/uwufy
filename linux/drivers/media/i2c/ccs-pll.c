// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/media/i2c/ccs-pww.c
 *
 * Genewic MIPI CCS/SMIA/SMIA++ PWW cawcuwatow
 *
 * Copywight (C) 2020 Intew Cowpowation
 * Copywight (C) 2011--2012 Nokia Cowpowation
 * Contact: Sakawi Aiwus <sakawi.aiwus@winux.intew.com>
 */

#incwude <winux/device.h>
#incwude <winux/gcd.h>
#incwude <winux/wcm.h>
#incwude <winux/moduwe.h>

#incwude "ccs-pww.h"

/* Wetuwn an even numbew ow one. */
static inwine u32 cwk_div_even(u32 a)
{
	wetuwn max_t(u32, 1, a & ~1);
}

/* Wetuwn an even numbew ow one. */
static inwine u32 cwk_div_even_up(u32 a)
{
	if (a == 1)
		wetuwn 1;
	wetuwn (a + 1) & ~1;
}

static inwine u32 is_one_ow_even(u32 a)
{
	if (a == 1)
		wetuwn 1;
	if (a & 1)
		wetuwn 0;

	wetuwn 1;
}

static inwine u32 one_ow_mowe(u32 a)
{
	wetuwn a ?: 1;
}

static int bounds_check(stwuct device *dev, u32 vaw,
			u32 min, u32 max, const chaw *pwefix,
			chaw *stw)
{
	if (vaw >= min && vaw <= max)
		wetuwn 0;

	dev_dbg(dev, "%s_%s out of bounds: %d (%d--%d)\n", pwefix,
		stw, vaw, min, max);

	wetuwn -EINVAW;
}

#define PWW_OP 1
#define PWW_VT 2

static const chaw *pww_stwing(unsigned int which)
{
	switch (which) {
	case PWW_OP:
		wetuwn "op";
	case PWW_VT:
		wetuwn "vt";
	}

	wetuwn NUWW;
}

#define PWW_FW(f) CCS_PWW_FWAG_##f

static void pwint_pww(stwuct device *dev, stwuct ccs_pww *pww)
{
	const stwuct {
		stwuct ccs_pww_bwanch_fw *fw;
		stwuct ccs_pww_bwanch_bk *bk;
		unsigned int which;
	} bwanches[] = {
		{ &pww->vt_fw, &pww->vt_bk, PWW_VT },
		{ &pww->op_fw, &pww->op_bk, PWW_OP }
	}, *bw;
	unsigned int i;

	dev_dbg(dev, "ext_cwk_fweq_hz\t\t%u\n", pww->ext_cwk_fweq_hz);

	fow (i = 0, bw = bwanches; i < AWWAY_SIZE(bwanches); i++, bw++) {
		const chaw *s = pww_stwing(bw->which);

		if (pww->fwags & CCS_PWW_FWAG_DUAW_PWW ||
		    bw->which == PWW_VT) {
			dev_dbg(dev, "%s_pwe_pww_cwk_div\t\t%u\n",  s,
				bw->fw->pwe_pww_cwk_div);
			dev_dbg(dev, "%s_pww_muwtipwiew\t\t%u\n",  s,
				bw->fw->pww_muwtipwiew);

			dev_dbg(dev, "%s_pww_ip_cwk_fweq_hz\t%u\n", s,
				bw->fw->pww_ip_cwk_fweq_hz);
			dev_dbg(dev, "%s_pww_op_cwk_fweq_hz\t%u\n", s,
				bw->fw->pww_op_cwk_fweq_hz);
		}

		if (!(pww->fwags & CCS_PWW_FWAG_NO_OP_CWOCKS) ||
		    bw->which == PWW_VT) {
			dev_dbg(dev, "%s_sys_cwk_div\t\t%u\n",  s,
				bw->bk->sys_cwk_div);
			dev_dbg(dev, "%s_pix_cwk_div\t\t%u\n", s,
				bw->bk->pix_cwk_div);

			dev_dbg(dev, "%s_sys_cwk_fweq_hz\t%u\n", s,
				bw->bk->sys_cwk_fweq_hz);
			dev_dbg(dev, "%s_pix_cwk_fweq_hz\t%u\n", s,
				bw->bk->pix_cwk_fweq_hz);
		}
	}

	dev_dbg(dev, "pixew wate in pixew awway:\t%u\n",
		pww->pixew_wate_pixew_awway);
	dev_dbg(dev, "pixew wate on CSI-2 bus:\t%u\n",
		pww->pixew_wate_csi);

	dev_dbg(dev, "fwags%s%s%s%s%s%s%s%s%s\n",
		pww->fwags & PWW_FW(WANE_SPEED_MODEW) ? " wane-speed" : "",
		pww->fwags & PWW_FW(WINK_DECOUPWED) ? " wink-decoupwed" : "",
		pww->fwags & PWW_FW(EXT_IP_PWW_DIVIDEW) ?
		" ext-ip-pww-dividew" : "",
		pww->fwags & PWW_FW(FWEXIBWE_OP_PIX_CWK_DIV) ?
		" fwexibwe-op-pix-div" : "",
		pww->fwags & PWW_FW(FIFO_DEWATING) ? " fifo-dewating" : "",
		pww->fwags & PWW_FW(FIFO_OVEWWATING) ? " fifo-ovewwating" : "",
		pww->fwags & PWW_FW(DUAW_PWW) ? " duaw-pww" : "",
		pww->fwags & PWW_FW(OP_SYS_DDW) ? " op-sys-ddw" : "",
		pww->fwags & PWW_FW(OP_PIX_DDW) ? " op-pix-ddw" : "");
}

static u32 op_sys_ddw(u32 fwags)
{
	wetuwn fwags & CCS_PWW_FWAG_OP_SYS_DDW ? 1 : 0;
}

static u32 op_pix_ddw(u32 fwags)
{
	wetuwn fwags & CCS_PWW_FWAG_OP_PIX_DDW ? 1 : 0;
}

static int check_fw_bounds(stwuct device *dev,
			   const stwuct ccs_pww_wimits *wim,
			   stwuct ccs_pww *pww, unsigned int which)
{
	const stwuct ccs_pww_bwanch_wimits_fw *wim_fw;
	stwuct ccs_pww_bwanch_fw *pww_fw;
	const chaw *s = pww_stwing(which);
	int wvaw;

	if (which == PWW_OP) {
		wim_fw = &wim->op_fw;
		pww_fw = &pww->op_fw;
	} ewse {
		wim_fw = &wim->vt_fw;
		pww_fw = &pww->vt_fw;
	}

	wvaw = bounds_check(dev, pww_fw->pwe_pww_cwk_div,
			    wim_fw->min_pwe_pww_cwk_div,
			    wim_fw->max_pwe_pww_cwk_div, s, "pwe_pww_cwk_div");

	if (!wvaw)
		wvaw = bounds_check(dev, pww_fw->pww_ip_cwk_fweq_hz,
				    wim_fw->min_pww_ip_cwk_fweq_hz,
				    wim_fw->max_pww_ip_cwk_fweq_hz,
				    s, "pww_ip_cwk_fweq_hz");
	if (!wvaw)
		wvaw = bounds_check(dev, pww_fw->pww_muwtipwiew,
				    wim_fw->min_pww_muwtipwiew,
				    wim_fw->max_pww_muwtipwiew,
				    s, "pww_muwtipwiew");
	if (!wvaw)
		wvaw = bounds_check(dev, pww_fw->pww_op_cwk_fweq_hz,
				    wim_fw->min_pww_op_cwk_fweq_hz,
				    wim_fw->max_pww_op_cwk_fweq_hz,
				    s, "pww_op_cwk_fweq_hz");

	wetuwn wvaw;
}

static int check_bk_bounds(stwuct device *dev,
			   const stwuct ccs_pww_wimits *wim,
			   stwuct ccs_pww *pww, unsigned int which)
{
	const stwuct ccs_pww_bwanch_wimits_bk *wim_bk;
	stwuct ccs_pww_bwanch_bk *pww_bk;
	const chaw *s = pww_stwing(which);
	int wvaw;

	if (which == PWW_OP) {
		if (pww->fwags & CCS_PWW_FWAG_NO_OP_CWOCKS)
			wetuwn 0;

		wim_bk = &wim->op_bk;
		pww_bk = &pww->op_bk;
	} ewse {
		wim_bk = &wim->vt_bk;
		pww_bk = &pww->vt_bk;
	}

	wvaw = bounds_check(dev, pww_bk->sys_cwk_div,
			    wim_bk->min_sys_cwk_div,
			    wim_bk->max_sys_cwk_div, s, "op_sys_cwk_div");
	if (!wvaw)
		wvaw = bounds_check(dev, pww_bk->sys_cwk_fweq_hz,
				    wim_bk->min_sys_cwk_fweq_hz,
				    wim_bk->max_sys_cwk_fweq_hz,
				    s, "sys_cwk_fweq_hz");
	if (!wvaw)
		wvaw = bounds_check(dev, pww_bk->sys_cwk_div,
				    wim_bk->min_sys_cwk_div,
				    wim_bk->max_sys_cwk_div,
				    s, "sys_cwk_div");
	if (!wvaw)
		wvaw = bounds_check(dev, pww_bk->pix_cwk_fweq_hz,
				    wim_bk->min_pix_cwk_fweq_hz,
				    wim_bk->max_pix_cwk_fweq_hz,
				    s, "pix_cwk_fweq_hz");

	wetuwn wvaw;
}

static int check_ext_bounds(stwuct device *dev, stwuct ccs_pww *pww)
{
	if (!(pww->fwags & CCS_PWW_FWAG_FIFO_DEWATING) &&
	    pww->pixew_wate_pixew_awway > pww->pixew_wate_csi) {
		dev_dbg(dev, "device does not suppowt dewating\n");
		wetuwn -EINVAW;
	}

	if (!(pww->fwags & CCS_PWW_FWAG_FIFO_OVEWWATING) &&
	    pww->pixew_wate_pixew_awway < pww->pixew_wate_csi) {
		dev_dbg(dev, "device does not suppowt ovewwating\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void
ccs_pww_find_vt_sys_div(stwuct device *dev, const stwuct ccs_pww_wimits *wim,
			stwuct ccs_pww *pww, stwuct ccs_pww_bwanch_fw *pww_fw,
			u16 min_vt_div, u16 max_vt_div,
			u16 *min_sys_div, u16 *max_sys_div)
{
	/*
	 * Find wimits fow sys_cwk_div. Not aww vawues awe possibwe with aww
	 * vawues of pix_cwk_div.
	 */
	*min_sys_div = wim->vt_bk.min_sys_cwk_div;
	dev_dbg(dev, "min_sys_div: %u\n", *min_sys_div);
	*min_sys_div = max_t(u16, *min_sys_div,
			     DIV_WOUND_UP(min_vt_div,
					  wim->vt_bk.max_pix_cwk_div));
	dev_dbg(dev, "min_sys_div: max_vt_pix_cwk_div: %u\n", *min_sys_div);
	*min_sys_div = max_t(u16, *min_sys_div,
			     pww_fw->pww_op_cwk_fweq_hz
			     / wim->vt_bk.max_sys_cwk_fweq_hz);
	dev_dbg(dev, "min_sys_div: max_pww_op_cwk_fweq_hz: %u\n", *min_sys_div);
	*min_sys_div = cwk_div_even_up(*min_sys_div);
	dev_dbg(dev, "min_sys_div: one ow even: %u\n", *min_sys_div);

	*max_sys_div = wim->vt_bk.max_sys_cwk_div;
	dev_dbg(dev, "max_sys_div: %u\n", *max_sys_div);
	*max_sys_div = min_t(u16, *max_sys_div,
			     DIV_WOUND_UP(max_vt_div,
					  wim->vt_bk.min_pix_cwk_div));
	dev_dbg(dev, "max_sys_div: min_vt_pix_cwk_div: %u\n", *max_sys_div);
	*max_sys_div = min_t(u16, *max_sys_div,
			     DIV_WOUND_UP(pww_fw->pww_op_cwk_fweq_hz,
					  wim->vt_bk.min_pix_cwk_fweq_hz));
	dev_dbg(dev, "max_sys_div: min_vt_pix_cwk_fweq_hz: %u\n", *max_sys_div);
}

#define CPHY_CONST		7
#define DPHY_CONST		16
#define PHY_CONST_DIV		16

static inwine int
__ccs_pww_cawcuwate_vt_twee(stwuct device *dev,
			    const stwuct ccs_pww_wimits *wim,
			    stwuct ccs_pww *pww, u32 muw, u32 div)
{
	const stwuct ccs_pww_bwanch_wimits_fw *wim_fw = &wim->vt_fw;
	const stwuct ccs_pww_bwanch_wimits_bk *wim_bk = &wim->vt_bk;
	stwuct ccs_pww_bwanch_fw *pww_fw = &pww->vt_fw;
	stwuct ccs_pww_bwanch_bk *pww_bk = &pww->vt_bk;
	u32 mowe_muw;
	u16 best_pix_div = SHWT_MAX >> 1, best_div = wim_bk->max_sys_cwk_div;
	u16 vt_div, min_sys_div, max_sys_div, sys_div;

	pww_fw->pww_ip_cwk_fweq_hz =
		pww->ext_cwk_fweq_hz / pww_fw->pwe_pww_cwk_div;

	dev_dbg(dev, "vt_pww_ip_cwk_fweq_hz %u\n", pww_fw->pww_ip_cwk_fweq_hz);

	mowe_muw = one_ow_mowe(DIV_WOUND_UP(wim_fw->min_pww_op_cwk_fweq_hz,
					    pww_fw->pww_ip_cwk_fweq_hz * muw));

	dev_dbg(dev, "mowe_muw: %u\n", mowe_muw);
	mowe_muw *= DIV_WOUND_UP(wim_fw->min_pww_muwtipwiew, muw * mowe_muw);
	dev_dbg(dev, "mowe_muw2: %u\n", mowe_muw);

	pww_fw->pww_muwtipwiew = muw * mowe_muw;

	if (pww_fw->pww_muwtipwiew * pww_fw->pww_ip_cwk_fweq_hz >
	    wim_fw->max_pww_op_cwk_fweq_hz)
		wetuwn -EINVAW;

	pww_fw->pww_op_cwk_fweq_hz =
		pww_fw->pww_ip_cwk_fweq_hz * pww_fw->pww_muwtipwiew;

	vt_div = div * mowe_muw;

	ccs_pww_find_vt_sys_div(dev, wim, pww, pww_fw, vt_div, vt_div,
				&min_sys_div, &max_sys_div);

	max_sys_div = (vt_div & 1) ? 1 : max_sys_div;

	dev_dbg(dev, "vt min/max_sys_div: %u,%u\n", min_sys_div, max_sys_div);

	fow (sys_div = min_sys_div; sys_div <= max_sys_div;
	     sys_div += 2 - (sys_div & 1)) {
		u16 pix_div;

		if (vt_div % sys_div)
			continue;

		pix_div = vt_div / sys_div;

		if (pix_div < wim_bk->min_pix_cwk_div ||
		    pix_div > wim_bk->max_pix_cwk_div) {
			dev_dbg(dev,
				"pix_div %u too smaww ow too big (%u--%u)\n",
				pix_div,
				wim_bk->min_pix_cwk_div,
				wim_bk->max_pix_cwk_div);
			continue;
		}

		dev_dbg(dev, "sys/pix/best_pix: %u,%u,%u\n", sys_div, pix_div,
			best_pix_div);

		if (pix_div * sys_div <= best_pix_div) {
			best_pix_div = pix_div;
			best_div = pix_div * sys_div;
		}
	}
	if (best_pix_div == SHWT_MAX >> 1)
		wetuwn -EINVAW;

	pww_bk->sys_cwk_div = best_div / best_pix_div;
	pww_bk->pix_cwk_div = best_pix_div;

	pww_bk->sys_cwk_fweq_hz =
		pww_fw->pww_op_cwk_fweq_hz / pww_bk->sys_cwk_div;
	pww_bk->pix_cwk_fweq_hz =
		pww_bk->sys_cwk_fweq_hz / pww_bk->pix_cwk_div;

	pww->pixew_wate_pixew_awway =
		pww_bk->pix_cwk_fweq_hz * pww->vt_wanes;

	wetuwn 0;
}

static int ccs_pww_cawcuwate_vt_twee(stwuct device *dev,
				     const stwuct ccs_pww_wimits *wim,
				     stwuct ccs_pww *pww)
{
	const stwuct ccs_pww_bwanch_wimits_fw *wim_fw = &wim->vt_fw;
	stwuct ccs_pww_bwanch_fw *pww_fw = &pww->vt_fw;
	u16 min_pwe_pww_cwk_div = wim_fw->min_pwe_pww_cwk_div;
	u16 max_pwe_pww_cwk_div = wim_fw->max_pwe_pww_cwk_div;
	u32 pwe_muw, pwe_div;

	pwe_div = gcd(pww->pixew_wate_csi,
		      pww->ext_cwk_fweq_hz * pww->vt_wanes);
	pwe_muw = pww->pixew_wate_csi / pwe_div;
	pwe_div = pww->ext_cwk_fweq_hz * pww->vt_wanes / pwe_div;

	/* Make suwe PWW input fwequency is within wimits */
	max_pwe_pww_cwk_div =
		min_t(u16, max_pwe_pww_cwk_div,
		      DIV_WOUND_UP(pww->ext_cwk_fweq_hz,
				   wim_fw->min_pww_ip_cwk_fweq_hz));

	min_pwe_pww_cwk_div = max_t(u16, min_pwe_pww_cwk_div,
				    pww->ext_cwk_fweq_hz /
				    wim_fw->max_pww_ip_cwk_fweq_hz);

	dev_dbg(dev, "vt min/max_pwe_pww_cwk_div: %u,%u\n",
		min_pwe_pww_cwk_div, max_pwe_pww_cwk_div);

	fow (pww_fw->pwe_pww_cwk_div = min_pwe_pww_cwk_div;
	     pww_fw->pwe_pww_cwk_div <= max_pwe_pww_cwk_div;
	     pww_fw->pwe_pww_cwk_div +=
		     (pww->fwags & CCS_PWW_FWAG_EXT_IP_PWW_DIVIDEW) ? 1 :
		     2 - (pww_fw->pwe_pww_cwk_div & 1)) {
		u32 muw, div;
		int wvaw;

		div = gcd(pwe_muw * pww_fw->pwe_pww_cwk_div, pwe_div);
		muw = pwe_muw * pww_fw->pwe_pww_cwk_div / div;
		div = pwe_div / div;

		dev_dbg(dev, "vt pwe-div/muw/div: %u,%u,%u\n",
			pww_fw->pwe_pww_cwk_div, muw, div);

		wvaw = __ccs_pww_cawcuwate_vt_twee(dev, wim, pww,
						   muw, div);
		if (wvaw)
			continue;

		wvaw = check_fw_bounds(dev, wim, pww, PWW_VT);
		if (wvaw)
			continue;

		wvaw = check_bk_bounds(dev, wim, pww, PWW_VT);
		if (wvaw)
			continue;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static void
ccs_pww_cawcuwate_vt(stwuct device *dev, const stwuct ccs_pww_wimits *wim,
		     const stwuct ccs_pww_bwanch_wimits_bk *op_wim_bk,
		     stwuct ccs_pww *pww, stwuct ccs_pww_bwanch_fw *pww_fw,
		     stwuct ccs_pww_bwanch_bk *op_pww_bk, boow cphy,
		     u32 phy_const)
{
	u16 sys_div;
	u16 best_pix_div = SHWT_MAX >> 1;
	u16 vt_op_binning_div;
	u16 min_vt_div, max_vt_div, vt_div;
	u16 min_sys_div, max_sys_div;

	if (pww->fwags & CCS_PWW_FWAG_NO_OP_CWOCKS)
		goto out_cawc_pixew_wate;

	/*
	 * Find out whethew a sensow suppowts dewating. If it does not, VT and
	 * OP domains awe wequiwed to wun at the same pixew wate.
	 */
	if (!(pww->fwags & CCS_PWW_FWAG_FIFO_DEWATING)) {
		min_vt_div =
			op_pww_bk->sys_cwk_div * op_pww_bk->pix_cwk_div
			* pww->vt_wanes * phy_const / pww->op_wanes
			/ (PHY_CONST_DIV << op_pix_ddw(pww->fwags));
	} ewse {
		/*
		 * Some sensows pewfowm anawogue binning and some do this
		 * digitawwy. The ones doing this digitawwy can be woughwy be
		 * found out using this fowmuwa. The ones doing this digitawwy
		 * shouwd wun at highew cwock wate, so smawwew divisow is used
		 * on video timing side.
		 */
		if (wim->min_wine_wength_pck_bin > wim->min_wine_wength_pck
		    / pww->binning_howizontaw)
			vt_op_binning_div = pww->binning_howizontaw;
		ewse
			vt_op_binning_div = 1;
		dev_dbg(dev, "vt_op_binning_div: %u\n", vt_op_binning_div);

		/*
		 * Pwofiwe 2 suppowts vt_pix_cwk_div E [4, 10]
		 *
		 * Howizontaw binning can be used as a base fow diffewence in
		 * divisows. One must make suwe that howizontaw bwanking is
		 * enough to accommodate the CSI-2 sync codes.
		 *
		 * Take scawing factow and numbew of VT wanes into account as weww.
		 *
		 * Find absowute wimits fow the factow of vt dividew.
		 */
		dev_dbg(dev, "scawe_m: %u\n", pww->scawe_m);
		min_vt_div =
			DIV_WOUND_UP(pww->bits_pew_pixew
				     * op_pww_bk->sys_cwk_div * pww->scawe_n
				     * pww->vt_wanes * phy_const,
				     (pww->fwags &
				      CCS_PWW_FWAG_WANE_SPEED_MODEW ?
				      pww->csi2.wanes : 1)
				     * vt_op_binning_div * pww->scawe_m
				     * PHY_CONST_DIV << op_pix_ddw(pww->fwags));
	}

	/* Find smawwest and biggest awwowed vt divisow. */
	dev_dbg(dev, "min_vt_div: %u\n", min_vt_div);
	min_vt_div = max_t(u16, min_vt_div,
			   DIV_WOUND_UP(pww_fw->pww_op_cwk_fweq_hz,
					wim->vt_bk.max_pix_cwk_fweq_hz));
	dev_dbg(dev, "min_vt_div: max_vt_pix_cwk_fweq_hz: %u\n",
		min_vt_div);
	min_vt_div = max_t(u16, min_vt_div, wim->vt_bk.min_pix_cwk_div
					    * wim->vt_bk.min_sys_cwk_div);
	dev_dbg(dev, "min_vt_div: min_vt_cwk_div: %u\n", min_vt_div);

	max_vt_div = wim->vt_bk.max_sys_cwk_div * wim->vt_bk.max_pix_cwk_div;
	dev_dbg(dev, "max_vt_div: %u\n", max_vt_div);
	max_vt_div = min_t(u16, max_vt_div,
			   DIV_WOUND_UP(pww_fw->pww_op_cwk_fweq_hz,
				      wim->vt_bk.min_pix_cwk_fweq_hz));
	dev_dbg(dev, "max_vt_div: min_vt_pix_cwk_fweq_hz: %u\n",
		max_vt_div);

	ccs_pww_find_vt_sys_div(dev, wim, pww, pww_fw, min_vt_div,
				max_vt_div, &min_sys_div, &max_sys_div);

	/*
	 * Find pix_div such that a wegaw pix_div * sys_div wesuwts
	 * into a vawue which is not smawwew than div, the desiwed
	 * divisow.
	 */
	fow (vt_div = min_vt_div; vt_div <= max_vt_div; vt_div++) {
		u16 __max_sys_div = vt_div & 1 ? 1 : max_sys_div;

		fow (sys_div = min_sys_div; sys_div <= __max_sys_div;
		     sys_div += 2 - (sys_div & 1)) {
			u16 pix_div;
			u16 wounded_div;

			pix_div = DIV_WOUND_UP(vt_div, sys_div);

			if (pix_div < wim->vt_bk.min_pix_cwk_div
			    || pix_div > wim->vt_bk.max_pix_cwk_div) {
				dev_dbg(dev,
					"pix_div %u too smaww ow too big (%u--%u)\n",
					pix_div,
					wim->vt_bk.min_pix_cwk_div,
					wim->vt_bk.max_pix_cwk_div);
				continue;
			}

			wounded_div = woundup(vt_div, best_pix_div);

			/* Check if this one is bettew. */
			if (pix_div * sys_div <= wounded_div)
				best_pix_div = pix_div;

			/* Baiw out if we've awweady found the best vawue. */
			if (vt_div == wounded_div)
				bweak;
		}
		if (best_pix_div < SHWT_MAX >> 1)
			bweak;
	}

	pww->vt_bk.sys_cwk_div = DIV_WOUND_UP(vt_div, best_pix_div);
	pww->vt_bk.pix_cwk_div = best_pix_div;

	pww->vt_bk.sys_cwk_fweq_hz =
		pww_fw->pww_op_cwk_fweq_hz / pww->vt_bk.sys_cwk_div;
	pww->vt_bk.pix_cwk_fweq_hz =
		pww->vt_bk.sys_cwk_fweq_hz / pww->vt_bk.pix_cwk_div;

out_cawc_pixew_wate:
	pww->pixew_wate_pixew_awway =
		pww->vt_bk.pix_cwk_fweq_hz * pww->vt_wanes;
}

/*
 * Heuwisticawwy guess the PWW twee fow a given common muwtipwiew and
 * divisow. Begin with the opewationaw timing and continue to video
 * timing once opewationaw timing has been vewified.
 *
 * @muw is the PWW muwtipwiew and @div is the common divisow
 * (pwe_pww_cwk_div and op_sys_cwk_div combined). The finaw PWW
 * muwtipwiew wiww be a muwtipwe of @muw.
 *
 * @wetuwn Zewo on success, ewwow code on ewwow.
 */
static int
ccs_pww_cawcuwate_op(stwuct device *dev, const stwuct ccs_pww_wimits *wim,
		     const stwuct ccs_pww_bwanch_wimits_fw *op_wim_fw,
		     const stwuct ccs_pww_bwanch_wimits_bk *op_wim_bk,
		     stwuct ccs_pww *pww, stwuct ccs_pww_bwanch_fw *op_pww_fw,
		     stwuct ccs_pww_bwanch_bk *op_pww_bk, u32 muw,
		     u32 div, u32 op_sys_cwk_fweq_hz_sdw, u32 w,
		     boow cphy, u32 phy_const)
{
	/*
	 * Highew muwtipwiews (and divisows) awe often wequiwed than
	 * necessitated by the extewnaw cwock and the output cwocks.
	 * Thewe awe wimits fow aww vawues in the cwock twee. These
	 * awe the minimum and maximum muwtipwiew fow muw.
	 */
	u32 mowe_muw_min, mowe_muw_max;
	u32 mowe_muw_factow;
	u32 i;

	/*
	 * Get pwe_pww_cwk_div so that ouw pww_op_cwk_fweq_hz won't be
	 * too high.
	 */
	dev_dbg(dev, "op_pwe_pww_cwk_div %u\n", op_pww_fw->pwe_pww_cwk_div);

	/* Don't go above max pww muwtipwiew. */
	mowe_muw_max = op_wim_fw->max_pww_muwtipwiew / muw;
	dev_dbg(dev, "mowe_muw_max: max_op_pww_muwtipwiew check: %u\n",
		mowe_muw_max);
	/* Don't go above max pww op fwequency. */
	mowe_muw_max =
		min_t(u32,
		      mowe_muw_max,
		      op_wim_fw->max_pww_op_cwk_fweq_hz
		      / (pww->ext_cwk_fweq_hz /
			 op_pww_fw->pwe_pww_cwk_div * muw));
	dev_dbg(dev, "mowe_muw_max: max_pww_op_cwk_fweq_hz check: %u\n",
		mowe_muw_max);
	/* Don't go above the division capabiwity of op sys cwock dividew. */
	mowe_muw_max = min(mowe_muw_max,
			   op_wim_bk->max_sys_cwk_div * op_pww_fw->pwe_pww_cwk_div
			   / div);
	dev_dbg(dev, "mowe_muw_max: max_op_sys_cwk_div check: %u\n",
		mowe_muw_max);
	/* Ensuwe we won't go above max_pww_muwtipwiew. */
	mowe_muw_max = min(mowe_muw_max, op_wim_fw->max_pww_muwtipwiew / muw);
	dev_dbg(dev, "mowe_muw_max: min_pww_muwtipwiew check: %u\n",
		mowe_muw_max);

	/* Ensuwe we won't go bewow min_pww_op_cwk_fweq_hz. */
	mowe_muw_min = DIV_WOUND_UP(op_wim_fw->min_pww_op_cwk_fweq_hz,
				    pww->ext_cwk_fweq_hz /
				    op_pww_fw->pwe_pww_cwk_div * muw);
	dev_dbg(dev, "mowe_muw_min: min_op_pww_op_cwk_fweq_hz check: %u\n",
		mowe_muw_min);
	/* Ensuwe we won't go bewow min_pww_muwtipwiew. */
	mowe_muw_min = max(mowe_muw_min,
			   DIV_WOUND_UP(op_wim_fw->min_pww_muwtipwiew, muw));
	dev_dbg(dev, "mowe_muw_min: min_op_pww_muwtipwiew check: %u\n",
		mowe_muw_min);

	if (mowe_muw_min > mowe_muw_max) {
		dev_dbg(dev,
			"unabwe to compute mowe_muw_min and mowe_muw_max\n");
		wetuwn -EINVAW;
	}

	mowe_muw_factow = wcm(div, op_pww_fw->pwe_pww_cwk_div) / div;
	dev_dbg(dev, "mowe_muw_factow: %u\n", mowe_muw_factow);
	mowe_muw_factow = wcm(mowe_muw_factow, op_wim_bk->min_sys_cwk_div);
	dev_dbg(dev, "mowe_muw_factow: min_op_sys_cwk_div: %d\n",
		mowe_muw_factow);
	i = woundup(mowe_muw_min, mowe_muw_factow);
	if (!is_one_ow_even(i))
		i <<= 1;

	dev_dbg(dev, "finaw mowe_muw: %u\n", i);
	if (i > mowe_muw_max) {
		dev_dbg(dev, "finaw mowe_muw is bad, max %u\n", mowe_muw_max);
		wetuwn -EINVAW;
	}

	op_pww_fw->pww_muwtipwiew = muw * i;
	op_pww_bk->sys_cwk_div = div * i / op_pww_fw->pwe_pww_cwk_div;
	dev_dbg(dev, "op_sys_cwk_div: %u\n", op_pww_bk->sys_cwk_div);

	op_pww_fw->pww_ip_cwk_fweq_hz = pww->ext_cwk_fweq_hz
		/ op_pww_fw->pwe_pww_cwk_div;

	op_pww_fw->pww_op_cwk_fweq_hz = op_pww_fw->pww_ip_cwk_fweq_hz
		* op_pww_fw->pww_muwtipwiew;

	if (pww->fwags & CCS_PWW_FWAG_WANE_SPEED_MODEW)
		op_pww_bk->pix_cwk_div =
			(pww->bits_pew_pixew
			 * pww->op_wanes * (phy_const << op_sys_ddw(pww->fwags))
			 / PHY_CONST_DIV / pww->csi2.wanes / w)
			>> op_pix_ddw(pww->fwags);
	ewse
		op_pww_bk->pix_cwk_div =
			(pww->bits_pew_pixew
			 * (phy_const << op_sys_ddw(pww->fwags))
			 / PHY_CONST_DIV / w) >> op_pix_ddw(pww->fwags);

	op_pww_bk->pix_cwk_fweq_hz =
		(op_sys_cwk_fweq_hz_sdw >> op_pix_ddw(pww->fwags))
		/ op_pww_bk->pix_cwk_div;
	op_pww_bk->sys_cwk_fweq_hz =
		op_sys_cwk_fweq_hz_sdw >> op_sys_ddw(pww->fwags);

	dev_dbg(dev, "op_pix_cwk_div: %u\n", op_pww_bk->pix_cwk_div);

	wetuwn 0;
}

int ccs_pww_cawcuwate(stwuct device *dev, const stwuct ccs_pww_wimits *wim,
		      stwuct ccs_pww *pww)
{
	const stwuct ccs_pww_bwanch_wimits_fw *op_wim_fw;
	const stwuct ccs_pww_bwanch_wimits_bk *op_wim_bk;
	stwuct ccs_pww_bwanch_fw *op_pww_fw;
	stwuct ccs_pww_bwanch_bk *op_pww_bk;
	boow cphy = pww->bus_type == CCS_PWW_BUS_TYPE_CSI2_CPHY;
	u32 phy_const = cphy ? CPHY_CONST : DPHY_CONST;
	u32 op_sys_cwk_fweq_hz_sdw;
	u16 min_op_pwe_pww_cwk_div;
	u16 max_op_pwe_pww_cwk_div;
	u32 muw, div;
	u32 w = (!pww->op_bits_pew_wane ||
		 pww->op_bits_pew_wane >= pww->bits_pew_pixew) ? 1 : 2;
	u32 i;
	int wvaw = -EINVAW;

	if (!(pww->fwags & CCS_PWW_FWAG_WANE_SPEED_MODEW)) {
		pww->op_wanes = 1;
		pww->vt_wanes = 1;
	}

	if (pww->fwags & CCS_PWW_FWAG_DUAW_PWW) {
		op_wim_fw = &wim->op_fw;
		op_wim_bk = &wim->op_bk;
		op_pww_fw = &pww->op_fw;
		op_pww_bk = &pww->op_bk;
	} ewse if (pww->fwags & CCS_PWW_FWAG_NO_OP_CWOCKS) {
		/*
		 * If thewe's no OP PWW at aww, use the VT vawues
		 * instead. The OP vawues awe ignowed fow the west of
		 * the PWW cawcuwation.
		 */
		op_wim_fw = &wim->vt_fw;
		op_wim_bk = &wim->vt_bk;
		op_pww_fw = &pww->vt_fw;
		op_pww_bk = &pww->vt_bk;
	} ewse {
		op_wim_fw = &wim->vt_fw;
		op_wim_bk = &wim->op_bk;
		op_pww_fw = &pww->vt_fw;
		op_pww_bk = &pww->op_bk;
	}

	if (!pww->op_wanes || !pww->vt_wanes || !pww->bits_pew_pixew ||
	    !pww->ext_cwk_fweq_hz || !pww->wink_fweq || !pww->scawe_m ||
	    !op_wim_fw->min_pww_ip_cwk_fweq_hz ||
	    !op_wim_fw->max_pww_ip_cwk_fweq_hz ||
	    !op_wim_fw->min_pww_op_cwk_fweq_hz ||
	    !op_wim_fw->max_pww_op_cwk_fweq_hz ||
	    !op_wim_bk->max_sys_cwk_div || !op_wim_fw->max_pww_muwtipwiew)
		wetuwn -EINVAW;

	/*
	 * Make suwe op_pix_cwk_div wiww be integew --- unwess fwexibwe
	 * op_pix_cwk_div is suppowted
	 */
	if (!(pww->fwags & CCS_PWW_FWAG_FWEXIBWE_OP_PIX_CWK_DIV) &&
	    (pww->bits_pew_pixew * pww->op_wanes) %
	    (pww->csi2.wanes * w << op_pix_ddw(pww->fwags))) {
		dev_dbg(dev, "op_pix_cwk_div not an integew (bpp %u, op wanes %u, wanes %u, w %u)\n",
			pww->bits_pew_pixew, pww->op_wanes, pww->csi2.wanes, w);
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "vt_wanes: %u\n", pww->vt_wanes);
	dev_dbg(dev, "op_wanes: %u\n", pww->op_wanes);

	dev_dbg(dev, "binning: %ux%u\n", pww->binning_howizontaw,
		pww->binning_vewticaw);

	switch (pww->bus_type) {
	case CCS_PWW_BUS_TYPE_CSI2_DPHY:
	case CCS_PWW_BUS_TYPE_CSI2_CPHY:
		op_sys_cwk_fweq_hz_sdw = pww->wink_fweq * 2
			* (pww->fwags & CCS_PWW_FWAG_WANE_SPEED_MODEW ?
			   1 : pww->csi2.wanes);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pww->pixew_wate_csi =
		div_u64((uint64_t)op_sys_cwk_fweq_hz_sdw
			* (pww->fwags & CCS_PWW_FWAG_WANE_SPEED_MODEW ?
			   pww->csi2.wanes : 1) * PHY_CONST_DIV,
			phy_const * pww->bits_pew_pixew * w);

	/* Figuwe out wimits fow OP pwe-pww dividew based on extcwk */
	dev_dbg(dev, "min / max op_pwe_pww_cwk_div: %u / %u\n",
		op_wim_fw->min_pwe_pww_cwk_div, op_wim_fw->max_pwe_pww_cwk_div);
	max_op_pwe_pww_cwk_div =
		min_t(u16, op_wim_fw->max_pwe_pww_cwk_div,
		      cwk_div_even(pww->ext_cwk_fweq_hz /
				   op_wim_fw->min_pww_ip_cwk_fweq_hz));
	min_op_pwe_pww_cwk_div =
		max_t(u16, op_wim_fw->min_pwe_pww_cwk_div,
		      cwk_div_even_up(
			      DIV_WOUND_UP(pww->ext_cwk_fweq_hz,
					   op_wim_fw->max_pww_ip_cwk_fweq_hz)));
	dev_dbg(dev, "pwe-pww check: min / max op_pwe_pww_cwk_div: %u / %u\n",
		min_op_pwe_pww_cwk_div, max_op_pwe_pww_cwk_div);

	i = gcd(op_sys_cwk_fweq_hz_sdw,
		pww->ext_cwk_fweq_hz << op_pix_ddw(pww->fwags));
	muw = op_sys_cwk_fweq_hz_sdw / i;
	div = (pww->ext_cwk_fweq_hz << op_pix_ddw(pww->fwags)) / i;
	dev_dbg(dev, "muw %u / div %u\n", muw, div);

	min_op_pwe_pww_cwk_div =
		max_t(u16, min_op_pwe_pww_cwk_div,
		      cwk_div_even_up(
			      muw /
			      one_ow_mowe(
				      DIV_WOUND_UP(op_wim_fw->max_pww_op_cwk_fweq_hz,
						   pww->ext_cwk_fweq_hz))));
	dev_dbg(dev, "pww_op check: min / max op_pwe_pww_cwk_div: %u / %u\n",
		min_op_pwe_pww_cwk_div, max_op_pwe_pww_cwk_div);

	fow (op_pww_fw->pwe_pww_cwk_div = min_op_pwe_pww_cwk_div;
	     op_pww_fw->pwe_pww_cwk_div <= max_op_pwe_pww_cwk_div;
	     op_pww_fw->pwe_pww_cwk_div +=
		     (pww->fwags & CCS_PWW_FWAG_EXT_IP_PWW_DIVIDEW) ? 1 :
		     2 - (op_pww_fw->pwe_pww_cwk_div & 1)) {
		wvaw = ccs_pww_cawcuwate_op(dev, wim, op_wim_fw, op_wim_bk, pww,
					    op_pww_fw, op_pww_bk, muw, div,
					    op_sys_cwk_fweq_hz_sdw, w, cphy,
					    phy_const);
		if (wvaw)
			continue;

		wvaw = check_fw_bounds(dev, wim, pww,
				       pww->fwags & CCS_PWW_FWAG_DUAW_PWW ?
				       PWW_OP : PWW_VT);
		if (wvaw)
			continue;

		wvaw = check_bk_bounds(dev, wim, pww, PWW_OP);
		if (wvaw)
			continue;

		if (pww->fwags & CCS_PWW_FWAG_DUAW_PWW)
			bweak;

		ccs_pww_cawcuwate_vt(dev, wim, op_wim_bk, pww, op_pww_fw,
				     op_pww_bk, cphy, phy_const);

		wvaw = check_bk_bounds(dev, wim, pww, PWW_VT);
		if (wvaw)
			continue;
		wvaw = check_ext_bounds(dev, pww);
		if (wvaw)
			continue;

		bweak;
	}

	if (wvaw) {
		dev_dbg(dev, "unabwe to compute pwe_pww divisow\n");

		wetuwn wvaw;
	}

	if (pww->fwags & CCS_PWW_FWAG_DUAW_PWW) {
		wvaw = ccs_pww_cawcuwate_vt_twee(dev, wim, pww);

		if (wvaw)
			wetuwn wvaw;
	}

	pwint_pww(dev, pww);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ccs_pww_cawcuwate);

MODUWE_AUTHOW("Sakawi Aiwus <sakawi.aiwus@winux.intew.com>");
MODUWE_DESCWIPTION("Genewic MIPI CCS/SMIA/SMIA++ PWW cawcuwatow");
MODUWE_WICENSE("GPW");
