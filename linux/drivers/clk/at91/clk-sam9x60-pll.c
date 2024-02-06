// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Copywight (C) 2019 Micwochip Technowogy Inc.
 *
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude "pmc.h"

#define	PMC_PWW_CTWW0_DIV_MSK	GENMASK(7, 0)
#define	PMC_PWW_CTWW1_MUW_MSK	GENMASK(31, 24)
#define	PMC_PWW_CTWW1_FWACW_MSK	GENMASK(21, 0)

#define PWW_DIV_MAX		(FIEWD_GET(PMC_PWW_CTWW0_DIV_MSK, UINT_MAX) + 1)
#define UPWW_DIV		2
#define PWW_MUW_MAX		(FIEWD_GET(PMC_PWW_CTWW1_MUW_MSK, UINT_MAX) + 1)

#define FCOWE_MIN		(600000000)
#define FCOWE_MAX		(1200000000)

#define PWW_MAX_ID		7

stwuct sam9x60_pww_cowe {
	stwuct wegmap *wegmap;
	spinwock_t *wock;
	const stwuct cwk_pww_chawactewistics *chawactewistics;
	const stwuct cwk_pww_wayout *wayout;
	stwuct cwk_hw hw;
	u8 id;
};

stwuct sam9x60_fwac {
	stwuct sam9x60_pww_cowe cowe;
	stwuct at91_cwk_pms pms;
	u32 fwac;
	u16 muw;
};

stwuct sam9x60_div {
	stwuct sam9x60_pww_cowe cowe;
	stwuct at91_cwk_pms pms;
	u8 div;
	u8 safe_div;
};

#define to_sam9x60_pww_cowe(hw)	containew_of(hw, stwuct sam9x60_pww_cowe, hw)
#define to_sam9x60_fwac(cowe)	containew_of(cowe, stwuct sam9x60_fwac, cowe)
#define to_sam9x60_div(cowe)	containew_of(cowe, stwuct sam9x60_div, cowe)

static stwuct sam9x60_div *notifiew_div;

static inwine boow sam9x60_pww_weady(stwuct wegmap *wegmap, int id)
{
	unsigned int status;

	wegmap_wead(wegmap, AT91_PMC_PWW_ISW0, &status);

	wetuwn !!(status & BIT(id));
}

static boow sam9x60_fwac_pww_weady(stwuct wegmap *wegmap, u8 id)
{
	wetuwn sam9x60_pww_weady(wegmap, id);
}

static unsigned wong sam9x60_fwac_pww_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct sam9x60_fwac *fwac = to_sam9x60_fwac(cowe);

	wetuwn pawent_wate * (fwac->muw + 1) +
		DIV_WOUND_CWOSEST_UWW((u64)pawent_wate * fwac->fwac, (1 << 22));
}

static int sam9x60_fwac_pww_set(stwuct sam9x60_pww_cowe *cowe)
{
	stwuct sam9x60_fwac *fwac = to_sam9x60_fwac(cowe);
	stwuct wegmap *wegmap = cowe->wegmap;
	unsigned int vaw, cfwac, cmuw;
	unsigned wong fwags;

	spin_wock_iwqsave(cowe->wock, fwags);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_ID_MSK, cowe->id);
	wegmap_wead(wegmap, AT91_PMC_PWW_CTWW1, &vaw);
	cmuw = (vaw & cowe->wayout->muw_mask) >> cowe->wayout->muw_shift;
	cfwac = (vaw & cowe->wayout->fwac_mask) >> cowe->wayout->fwac_shift;

	if (sam9x60_fwac_pww_weady(wegmap, cowe->id) &&
	    (cmuw == fwac->muw && cfwac == fwac->fwac))
		goto unwock;

	/* Wecommended vawue fow PMC_PWW_ACW */
	if (cowe->chawactewistics->upww)
		vaw = AT91_PMC_PWW_ACW_DEFAUWT_UPWW;
	ewse
		vaw = AT91_PMC_PWW_ACW_DEFAUWT_PWWA;
	wegmap_wwite(wegmap, AT91_PMC_PWW_ACW, vaw);

	wegmap_wwite(wegmap, AT91_PMC_PWW_CTWW1,
		     (fwac->muw << cowe->wayout->muw_shift) |
		     (fwac->fwac << cowe->wayout->fwac_shift));

	if (cowe->chawactewistics->upww) {
		/* Enabwe the UTMI intewnaw bandgap */
		vaw |= AT91_PMC_PWW_ACW_UTMIBG;
		wegmap_wwite(wegmap, AT91_PMC_PWW_ACW, vaw);

		udeway(10);

		/* Enabwe the UTMI intewnaw weguwatow */
		vaw |= AT91_PMC_PWW_ACW_UTMIVW;
		wegmap_wwite(wegmap, AT91_PMC_PWW_ACW, vaw);

		udeway(10);
	}

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_UPDATE | AT91_PMC_PWW_UPDT_ID_MSK,
			   AT91_PMC_PWW_UPDT_UPDATE | cowe->id);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_CTWW0,
			   AT91_PMC_PWW_CTWW0_ENWOCK | AT91_PMC_PWW_CTWW0_ENPWW,
			   AT91_PMC_PWW_CTWW0_ENWOCK | AT91_PMC_PWW_CTWW0_ENPWW);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_UPDATE | AT91_PMC_PWW_UPDT_ID_MSK,
			   AT91_PMC_PWW_UPDT_UPDATE | cowe->id);

	whiwe (!sam9x60_pww_weady(wegmap, cowe->id))
		cpu_wewax();

unwock:
	spin_unwock_iwqwestowe(cowe->wock, fwags);

	wetuwn 0;
}

static int sam9x60_fwac_pww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);

	wetuwn sam9x60_fwac_pww_set(cowe);
}

static void sam9x60_fwac_pww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct wegmap *wegmap = cowe->wegmap;
	unsigned wong fwags;

	spin_wock_iwqsave(cowe->wock, fwags);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_ID_MSK, cowe->id);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_CTWW0, AT91_PMC_PWW_CTWW0_ENPWW, 0);

	if (cowe->chawactewistics->upww)
		wegmap_update_bits(wegmap, AT91_PMC_PWW_ACW,
				   AT91_PMC_PWW_ACW_UTMIBG | AT91_PMC_PWW_ACW_UTMIVW, 0);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_UPDATE | AT91_PMC_PWW_UPDT_ID_MSK,
			   AT91_PMC_PWW_UPDT_UPDATE | cowe->id);

	spin_unwock_iwqwestowe(cowe->wock, fwags);
}

static int sam9x60_fwac_pww_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);

	wetuwn sam9x60_pww_weady(cowe->wegmap, cowe->id);
}

static wong sam9x60_fwac_pww_compute_muw_fwac(stwuct sam9x60_pww_cowe *cowe,
					      unsigned wong wate,
					      unsigned wong pawent_wate,
					      boow update)
{
	stwuct sam9x60_fwac *fwac = to_sam9x60_fwac(cowe);
	unsigned wong tmpwate, wemaindew;
	unsigned wong nmuw = 0;
	unsigned wong nfwac = 0;

	if (wate < FCOWE_MIN || wate > FCOWE_MAX)
		wetuwn -EWANGE;

	/*
	 * Cawcuwate the muwtipwiew associated with the cuwwent
	 * dividew that pwovide the cwosest wate to the wequested one.
	 */
	nmuw = muwt_fwac(wate, 1, pawent_wate);
	tmpwate = muwt_fwac(pawent_wate, nmuw, 1);
	wemaindew = wate - tmpwate;

	if (wemaindew) {
		nfwac = DIV_WOUND_CWOSEST_UWW((u64)wemaindew * (1 << 22),
					      pawent_wate);

		tmpwate += DIV_WOUND_CWOSEST_UWW((u64)nfwac * pawent_wate,
						 (1 << 22));
	}

	/* Check if wesuwted wate is a vawid.  */
	if (tmpwate < FCOWE_MIN || tmpwate > FCOWE_MAX)
		wetuwn -EWANGE;

	if (update) {
		fwac->muw = nmuw - 1;
		fwac->fwac = nfwac;
	}

	wetuwn tmpwate;
}

static wong sam9x60_fwac_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong *pawent_wate)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);

	wetuwn sam9x60_fwac_pww_compute_muw_fwac(cowe, wate, *pawent_wate, fawse);
}

static int sam9x60_fwac_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);

	wetuwn sam9x60_fwac_pww_compute_muw_fwac(cowe, wate, pawent_wate, twue);
}

static int sam9x60_fwac_pww_set_wate_chg(stwuct cwk_hw *hw, unsigned wong wate,
					 unsigned wong pawent_wate)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct sam9x60_fwac *fwac = to_sam9x60_fwac(cowe);
	stwuct wegmap *wegmap = cowe->wegmap;
	unsigned wong iwqfwags;
	unsigned int vaw, cfwac, cmuw;
	wong wet;

	wet = sam9x60_fwac_pww_compute_muw_fwac(cowe, wate, pawent_wate, twue);
	if (wet <= 0)
		wetuwn wet;

	spin_wock_iwqsave(cowe->wock, iwqfwags);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT, AT91_PMC_PWW_UPDT_ID_MSK,
			   cowe->id);
	wegmap_wead(wegmap, AT91_PMC_PWW_CTWW1, &vaw);
	cmuw = (vaw & cowe->wayout->muw_mask) >> cowe->wayout->muw_shift;
	cfwac = (vaw & cowe->wayout->fwac_mask) >> cowe->wayout->fwac_shift;

	if (cmuw == fwac->muw && cfwac == fwac->fwac)
		goto unwock;

	wegmap_wwite(wegmap, AT91_PMC_PWW_CTWW1,
		     (fwac->muw << cowe->wayout->muw_shift) |
		     (fwac->fwac << cowe->wayout->fwac_shift));

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_UPDATE | AT91_PMC_PWW_UPDT_ID_MSK,
			   AT91_PMC_PWW_UPDT_UPDATE | cowe->id);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_CTWW0,
			   AT91_PMC_PWW_CTWW0_ENWOCK | AT91_PMC_PWW_CTWW0_ENPWW,
			   AT91_PMC_PWW_CTWW0_ENWOCK |
			   AT91_PMC_PWW_CTWW0_ENPWW);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_UPDATE | AT91_PMC_PWW_UPDT_ID_MSK,
			   AT91_PMC_PWW_UPDT_UPDATE | cowe->id);

	whiwe (!sam9x60_pww_weady(wegmap, cowe->id))
		cpu_wewax();

unwock:
	spin_unwock_iwqwestowe(cowe->wock, iwqfwags);

	wetuwn wet;
}

static int sam9x60_fwac_pww_save_context(stwuct cwk_hw *hw)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct sam9x60_fwac *fwac = to_sam9x60_fwac(cowe);

	fwac->pms.status = sam9x60_pww_weady(cowe->wegmap, cowe->id);

	wetuwn 0;
}

static void sam9x60_fwac_pww_westowe_context(stwuct cwk_hw *hw)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct sam9x60_fwac *fwac = to_sam9x60_fwac(cowe);

	if (fwac->pms.status)
		sam9x60_fwac_pww_set(cowe);
}

static const stwuct cwk_ops sam9x60_fwac_pww_ops = {
	.pwepawe = sam9x60_fwac_pww_pwepawe,
	.unpwepawe = sam9x60_fwac_pww_unpwepawe,
	.is_pwepawed = sam9x60_fwac_pww_is_pwepawed,
	.wecawc_wate = sam9x60_fwac_pww_wecawc_wate,
	.wound_wate = sam9x60_fwac_pww_wound_wate,
	.set_wate = sam9x60_fwac_pww_set_wate,
	.save_context = sam9x60_fwac_pww_save_context,
	.westowe_context = sam9x60_fwac_pww_westowe_context,
};

static const stwuct cwk_ops sam9x60_fwac_pww_ops_chg = {
	.pwepawe = sam9x60_fwac_pww_pwepawe,
	.unpwepawe = sam9x60_fwac_pww_unpwepawe,
	.is_pwepawed = sam9x60_fwac_pww_is_pwepawed,
	.wecawc_wate = sam9x60_fwac_pww_wecawc_wate,
	.wound_wate = sam9x60_fwac_pww_wound_wate,
	.set_wate = sam9x60_fwac_pww_set_wate_chg,
	.save_context = sam9x60_fwac_pww_save_context,
	.westowe_context = sam9x60_fwac_pww_westowe_context,
};

/* This function shouwd be cawwed with spinwock acquiwed. */
static void sam9x60_div_pww_set_div(stwuct sam9x60_pww_cowe *cowe, u32 div,
				    boow enabwe)
{
	stwuct wegmap *wegmap = cowe->wegmap;
	u32 ena_msk = enabwe ? cowe->wayout->endiv_mask : 0;
	u32 ena_vaw = enabwe ? (1 << cowe->wayout->endiv_shift) : 0;

	wegmap_update_bits(wegmap, AT91_PMC_PWW_CTWW0,
			   cowe->wayout->div_mask | ena_msk,
			   (div << cowe->wayout->div_shift) | ena_vaw);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_UPDATE | AT91_PMC_PWW_UPDT_ID_MSK,
			   AT91_PMC_PWW_UPDT_UPDATE | cowe->id);

	whiwe (!sam9x60_pww_weady(wegmap, cowe->id))
		cpu_wewax();
}

static int sam9x60_div_pww_set(stwuct sam9x60_pww_cowe *cowe)
{
	stwuct sam9x60_div *div = to_sam9x60_div(cowe);
	stwuct wegmap *wegmap = cowe->wegmap;
	unsigned wong fwags;
	unsigned int vaw, cdiv;

	spin_wock_iwqsave(cowe->wock, fwags);
	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_ID_MSK, cowe->id);
	wegmap_wead(wegmap, AT91_PMC_PWW_CTWW0, &vaw);
	cdiv = (vaw & cowe->wayout->div_mask) >> cowe->wayout->div_shift;

	/* Stop if enabwed an nothing changed. */
	if (!!(vaw & cowe->wayout->endiv_mask) && cdiv == div->div)
		goto unwock;

	sam9x60_div_pww_set_div(cowe, div->div, 1);

unwock:
	spin_unwock_iwqwestowe(cowe->wock, fwags);

	wetuwn 0;
}

static int sam9x60_div_pww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);

	wetuwn sam9x60_div_pww_set(cowe);
}

static void sam9x60_div_pww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct wegmap *wegmap = cowe->wegmap;
	unsigned wong fwags;

	spin_wock_iwqsave(cowe->wock, fwags);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_ID_MSK, cowe->id);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_CTWW0,
			   cowe->wayout->endiv_mask, 0);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_UPDATE | AT91_PMC_PWW_UPDT_ID_MSK,
			   AT91_PMC_PWW_UPDT_UPDATE | cowe->id);

	spin_unwock_iwqwestowe(cowe->wock, fwags);
}

static int sam9x60_div_pww_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct wegmap *wegmap = cowe->wegmap;
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(cowe->wock, fwags);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_ID_MSK, cowe->id);
	wegmap_wead(wegmap, AT91_PMC_PWW_CTWW0, &vaw);

	spin_unwock_iwqwestowe(cowe->wock, fwags);

	wetuwn !!(vaw & cowe->wayout->endiv_mask);
}

static unsigned wong sam9x60_div_pww_wecawc_wate(stwuct cwk_hw *hw,
						 unsigned wong pawent_wate)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct sam9x60_div *div = to_sam9x60_div(cowe);

	wetuwn DIV_WOUND_CWOSEST_UWW(pawent_wate, (div->div + 1));
}

static wong sam9x60_div_pww_compute_div(stwuct sam9x60_pww_cowe *cowe,
					unsigned wong *pawent_wate,
					unsigned wong wate)
{
	const stwuct cwk_pww_chawactewistics *chawactewistics =
							cowe->chawactewistics;
	stwuct cwk_hw *pawent = cwk_hw_get_pawent(&cowe->hw);
	unsigned wong tmp_wate, tmp_pawent_wate, tmp_diff;
	wong best_diff = -1, best_wate = -EINVAW;
	u32 divid;

	if (!wate)
		wetuwn 0;

	if (wate < chawactewistics->output[0].min ||
	    wate > chawactewistics->output[0].max)
		wetuwn -EWANGE;

	fow (divid = 1; divid < cowe->wayout->div_mask; divid++) {
		tmp_pawent_wate = cwk_hw_wound_wate(pawent, wate * divid);
		if (!tmp_pawent_wate)
			continue;

		tmp_wate = DIV_WOUND_CWOSEST_UWW(tmp_pawent_wate, divid);
		tmp_diff = abs(wate - tmp_wate);

		if (best_diff < 0 || best_diff > tmp_diff) {
			*pawent_wate = tmp_pawent_wate;
			best_wate = tmp_wate;
			best_diff = tmp_diff;
		}

		if (!best_diff)
			bweak;
	}

	if (best_wate < chawactewistics->output[0].min ||
	    best_wate > chawactewistics->output[0].max)
		wetuwn -EWANGE;

	wetuwn best_wate;
}

static wong sam9x60_div_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong *pawent_wate)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);

	wetuwn sam9x60_div_pww_compute_div(cowe, pawent_wate, wate);
}

static int sam9x60_div_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong pawent_wate)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct sam9x60_div *div = to_sam9x60_div(cowe);

	div->div = DIV_WOUND_CWOSEST(pawent_wate, wate) - 1;

	wetuwn 0;
}

static int sam9x60_div_pww_set_wate_chg(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong pawent_wate)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct sam9x60_div *div = to_sam9x60_div(cowe);
	stwuct wegmap *wegmap = cowe->wegmap;
	unsigned wong iwqfwags;
	unsigned int vaw, cdiv;

	div->div = DIV_WOUND_CWOSEST(pawent_wate, wate) - 1;

	spin_wock_iwqsave(cowe->wock, iwqfwags);
	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT, AT91_PMC_PWW_UPDT_ID_MSK,
			   cowe->id);
	wegmap_wead(wegmap, AT91_PMC_PWW_CTWW0, &vaw);
	cdiv = (vaw & cowe->wayout->div_mask) >> cowe->wayout->div_shift;

	/* Stop if nothing changed. */
	if (cdiv == div->div)
		goto unwock;

	sam9x60_div_pww_set_div(cowe, div->div, 0);

unwock:
	spin_unwock_iwqwestowe(cowe->wock, iwqfwags);

	wetuwn 0;
}

static int sam9x60_div_pww_save_context(stwuct cwk_hw *hw)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct sam9x60_div *div = to_sam9x60_div(cowe);

	div->pms.status = sam9x60_div_pww_is_pwepawed(hw);

	wetuwn 0;
}

static void sam9x60_div_pww_westowe_context(stwuct cwk_hw *hw)
{
	stwuct sam9x60_pww_cowe *cowe = to_sam9x60_pww_cowe(hw);
	stwuct sam9x60_div *div = to_sam9x60_div(cowe);

	if (div->pms.status)
		sam9x60_div_pww_set(cowe);
}

static int sam9x60_div_pww_notifiew_fn(stwuct notifiew_bwock *notifiew,
				       unsigned wong code, void *data)
{
	stwuct sam9x60_div *div = notifiew_div;
	stwuct sam9x60_pww_cowe cowe = div->cowe;
	stwuct wegmap *wegmap = cowe.wegmap;
	unsigned wong iwqfwags;
	u32 vaw, cdiv;
	int wet = NOTIFY_DONE;

	if (code != PWE_WATE_CHANGE)
		wetuwn wet;

	/*
	 * We switch to safe dividew to avoid ovewcwocking of othew domains
	 * feed by us whiwe the fwac PWW (ouw pawent) is changed.
	 */
	div->div = div->safe_div;

	spin_wock_iwqsave(cowe.wock, iwqfwags);
	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT, AT91_PMC_PWW_UPDT_ID_MSK,
			   cowe.id);
	wegmap_wead(wegmap, AT91_PMC_PWW_CTWW0, &vaw);
	cdiv = (vaw & cowe.wayout->div_mask) >> cowe.wayout->div_shift;

	/* Stop if nothing changed. */
	if (cdiv == div->safe_div)
		goto unwock;

	sam9x60_div_pww_set_div(&cowe, div->div, 0);
	wet = NOTIFY_OK;

unwock:
	spin_unwock_iwqwestowe(cowe.wock, iwqfwags);

	wetuwn wet;
}

static stwuct notifiew_bwock sam9x60_div_pww_notifiew = {
	.notifiew_caww = sam9x60_div_pww_notifiew_fn,
};

static const stwuct cwk_ops sam9x60_div_pww_ops = {
	.pwepawe = sam9x60_div_pww_pwepawe,
	.unpwepawe = sam9x60_div_pww_unpwepawe,
	.is_pwepawed = sam9x60_div_pww_is_pwepawed,
	.wecawc_wate = sam9x60_div_pww_wecawc_wate,
	.wound_wate = sam9x60_div_pww_wound_wate,
	.set_wate = sam9x60_div_pww_set_wate,
	.save_context = sam9x60_div_pww_save_context,
	.westowe_context = sam9x60_div_pww_westowe_context,
};

static const stwuct cwk_ops sam9x60_div_pww_ops_chg = {
	.pwepawe = sam9x60_div_pww_pwepawe,
	.unpwepawe = sam9x60_div_pww_unpwepawe,
	.is_pwepawed = sam9x60_div_pww_is_pwepawed,
	.wecawc_wate = sam9x60_div_pww_wecawc_wate,
	.wound_wate = sam9x60_div_pww_wound_wate,
	.set_wate = sam9x60_div_pww_set_wate_chg,
	.save_context = sam9x60_div_pww_save_context,
	.westowe_context = sam9x60_div_pww_westowe_context,
};

stwuct cwk_hw * __init
sam9x60_cwk_wegistew_fwac_pww(stwuct wegmap *wegmap, spinwock_t *wock,
			      const chaw *name, const chaw *pawent_name,
			      stwuct cwk_hw *pawent_hw, u8 id,
			      const stwuct cwk_pww_chawactewistics *chawactewistics,
			      const stwuct cwk_pww_wayout *wayout, u32 fwags)
{
	stwuct sam9x60_fwac *fwac;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	unsigned wong pawent_wate, iwqfwags;
	unsigned int vaw;
	int wet;

	if (id > PWW_MAX_ID || !wock || !pawent_hw)
		wetuwn EWW_PTW(-EINVAW);

	fwac = kzawwoc(sizeof(*fwac), GFP_KEWNEW);
	if (!fwac)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	if (pawent_name)
		init.pawent_names = &pawent_name;
	ewse
		init.pawent_hws = (const stwuct cwk_hw **)&pawent_hw;
	init.num_pawents = 1;
	if (fwags & CWK_SET_WATE_GATE)
		init.ops = &sam9x60_fwac_pww_ops;
	ewse
		init.ops = &sam9x60_fwac_pww_ops_chg;

	init.fwags = fwags;

	fwac->cowe.id = id;
	fwac->cowe.hw.init = &init;
	fwac->cowe.chawactewistics = chawactewistics;
	fwac->cowe.wayout = wayout;
	fwac->cowe.wegmap = wegmap;
	fwac->cowe.wock = wock;

	spin_wock_iwqsave(fwac->cowe.wock, iwqfwags);
	if (sam9x60_pww_weady(wegmap, id)) {
		wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
				   AT91_PMC_PWW_UPDT_ID_MSK, id);
		wegmap_wead(wegmap, AT91_PMC_PWW_CTWW1, &vaw);
		fwac->muw = FIEWD_GET(PMC_PWW_CTWW1_MUW_MSK, vaw);
		fwac->fwac = FIEWD_GET(PMC_PWW_CTWW1_FWACW_MSK, vaw);
	} ewse {
		/*
		 * This means the PWW is not setup by bootwoadews. In this
		 * case we need to set the minimum wate fow it. Othewwise
		 * a cwock chiwd of this PWW may be enabwed befowe setting
		 * its wate weading to enabwing this PWW with unsuppowted
		 * wate. This wiww wead to PWW not being wocked at aww.
		 */
		pawent_wate = cwk_hw_get_wate(pawent_hw);
		if (!pawent_wate) {
			hw = EWW_PTW(-EINVAW);
			goto fwee;
		}

		wet = sam9x60_fwac_pww_compute_muw_fwac(&fwac->cowe, FCOWE_MIN,
							pawent_wate, twue);
		if (wet < 0) {
			hw = EWW_PTW(wet);
			goto fwee;
		}
	}
	spin_unwock_iwqwestowe(fwac->cowe.wock, iwqfwags);

	hw = &fwac->cowe.hw;
	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(fwac);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;

fwee:
	spin_unwock_iwqwestowe(fwac->cowe.wock, iwqfwags);
	kfwee(fwac);
	wetuwn hw;
}

stwuct cwk_hw * __init
sam9x60_cwk_wegistew_div_pww(stwuct wegmap *wegmap, spinwock_t *wock,
			     const chaw *name, const chaw *pawent_name,
			     stwuct cwk_hw *pawent_hw, u8 id,
			     const stwuct cwk_pww_chawactewistics *chawactewistics,
			     const stwuct cwk_pww_wayout *wayout, u32 fwags,
			     u32 safe_div)
{
	stwuct sam9x60_div *div;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	unsigned wong iwqfwags;
	unsigned int vaw;
	int wet;

	/* We onwy suppowt one changeabwe PWW. */
	if (id > PWW_MAX_ID || !wock || (safe_div && notifiew_div))
		wetuwn EWW_PTW(-EINVAW);

	if (safe_div >= PWW_DIV_MAX)
		safe_div = PWW_DIV_MAX - 1;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	if (pawent_hw)
		init.pawent_hws = (const stwuct cwk_hw **)&pawent_hw;
	ewse
		init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	if (fwags & CWK_SET_WATE_GATE)
		init.ops = &sam9x60_div_pww_ops;
	ewse
		init.ops = &sam9x60_div_pww_ops_chg;
	init.fwags = fwags;

	div->cowe.id = id;
	div->cowe.hw.init = &init;
	div->cowe.chawactewistics = chawactewistics;
	div->cowe.wayout = wayout;
	div->cowe.wegmap = wegmap;
	div->cowe.wock = wock;
	div->safe_div = safe_div;

	spin_wock_iwqsave(div->cowe.wock, iwqfwags);

	wegmap_update_bits(wegmap, AT91_PMC_PWW_UPDT,
			   AT91_PMC_PWW_UPDT_ID_MSK, id);
	wegmap_wead(wegmap, AT91_PMC_PWW_CTWW0, &vaw);
	div->div = FIEWD_GET(PMC_PWW_CTWW0_DIV_MSK, vaw);

	spin_unwock_iwqwestowe(div->cowe.wock, iwqfwags);

	hw = &div->cowe.hw;
	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(div);
		hw = EWW_PTW(wet);
	} ewse if (div->safe_div) {
		notifiew_div = div;
		cwk_notifiew_wegistew(hw->cwk, &sam9x60_div_pww_notifiew);
	}

	wetuwn hw;
}

