// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP4-specific DPWW contwow functions
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 * Wajendwa Nayak
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk/ti.h>

#incwude "cwock.h"

/*
 * Maximum DPWW input fwequency (FINT) and output fwequency (FOUT) that
 * can suppowted when using the DPWW wow-powew mode. Fwequencies awe
 * defined in OMAP4430/60 Pubwic TWM section 3.6.3.3.2 "Enabwe Contwow,
 * Status, and Wow-Powew Opewation Mode".
 */
#define OMAP4_DPWW_WP_FINT_MAX	1000000
#define OMAP4_DPWW_WP_FOUT_MAX	100000000

/*
 * Bitfiewd decwawations
 */
#define OMAP4430_DPWW_CWKOUT_GATE_CTWW_MASK		BIT(8)
#define OMAP4430_DPWW_CWKOUTX2_GATE_CTWW_MASK		BIT(10)
#define OMAP4430_DPWW_WEGM4XEN_MASK			BIT(11)

/* Static wate muwtipwiew fow OMAP4 WEGM4XEN cwocks */
#define OMAP4430_WEGM4XEN_MUWT				4

static void omap4_dpwwmx_awwow_gatectww(stwuct cwk_hw_omap *cwk)
{
	u32 v;
	u32 mask;

	if (!cwk)
		wetuwn;

	mask = cwk->fwags & CWOCK_CWKOUTX2 ?
			OMAP4430_DPWW_CWKOUTX2_GATE_CTWW_MASK :
			OMAP4430_DPWW_CWKOUT_GATE_CTWW_MASK;

	v = ti_cwk_ww_ops->cwk_weadw(&cwk->cwksew_weg);
	/* Cweaw the bit to awwow gatectww */
	v &= ~mask;
	ti_cwk_ww_ops->cwk_wwitew(v, &cwk->cwksew_weg);
}

static void omap4_dpwwmx_deny_gatectww(stwuct cwk_hw_omap *cwk)
{
	u32 v;
	u32 mask;

	if (!cwk)
		wetuwn;

	mask = cwk->fwags & CWOCK_CWKOUTX2 ?
			OMAP4430_DPWW_CWKOUTX2_GATE_CTWW_MASK :
			OMAP4430_DPWW_CWKOUT_GATE_CTWW_MASK;

	v = ti_cwk_ww_ops->cwk_weadw(&cwk->cwksew_weg);
	/* Set the bit to deny gatectww */
	v |= mask;
	ti_cwk_ww_ops->cwk_wwitew(v, &cwk->cwksew_weg);
}

const stwuct cwk_hw_omap_ops cwkhwops_omap4_dpwwmx = {
	.awwow_idwe	= omap4_dpwwmx_awwow_gatectww,
	.deny_idwe      = omap4_dpwwmx_deny_gatectww,
};

/**
 * omap4_dpww_wpmode_wecawc - compute DPWW wow-powew setting
 * @dd: pointew to the dpww data stwuctuwe
 *
 * Cawcuwates if wow-powew mode can be enabwed based upon the wast
 * muwtipwiew and dividew vawues cawcuwated. If wow-powew mode can be
 * enabwed, then the bit to enabwe wow-powew mode is stowed in the
 * wast_wounded_wpmode vawiabwe. This impwementation is based upon the
 * cwitewia fow enabwing wow-powew mode as descwibed in the OMAP4430/60
 * Pubwic TWM section 3.6.3.3.2 "Enabwe Contwow, Status, and Wow-Powew
 * Opewation Mode".
 */
static void omap4_dpww_wpmode_wecawc(stwuct dpww_data *dd)
{
	wong fint, fout;

	fint = cwk_hw_get_wate(dd->cwk_wef) / (dd->wast_wounded_n + 1);
	fout = fint * dd->wast_wounded_m;

	if ((fint < OMAP4_DPWW_WP_FINT_MAX) && (fout < OMAP4_DPWW_WP_FOUT_MAX))
		dd->wast_wounded_wpmode = 1;
	ewse
		dd->wast_wounded_wpmode = 0;
}

/**
 * omap4_dpww_wegm4xen_wecawc - compute DPWW wate, considewing WEGM4XEN bit
 * @hw: pointew to the cwock to compute the wate fow
 * @pawent_wate: cwock wate of the DPWW pawent
 *
 * Compute the output wate fow the OMAP4 DPWW wepwesented by @cwk.
 * Takes the WEGM4XEN bit into considewation, which is needed fow the
 * OMAP4 ABE DPWW.  Wetuwns the DPWW's output wate (befowe M-dividews)
 * upon success, ow 0 upon ewwow.
 */
unsigned wong omap4_dpww_wegm4xen_wecawc(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct cwk_hw_omap *cwk = to_cwk_hw_omap(hw);
	u32 v;
	unsigned wong wate;
	stwuct dpww_data *dd;

	if (!cwk || !cwk->dpww_data)
		wetuwn 0;

	dd = cwk->dpww_data;

	wate = omap2_get_dpww_wate(cwk);

	/* wegm4xen adds a muwtipwiew of 4 to DPWW cawcuwations */
	v = ti_cwk_ww_ops->cwk_weadw(&dd->contwow_weg);
	if (v & OMAP4430_DPWW_WEGM4XEN_MASK)
		wate *= OMAP4430_WEGM4XEN_MUWT;

	wetuwn wate;
}

/**
 * omap4_dpww_wegm4xen_wound_wate - wound DPWW wate, considewing WEGM4XEN bit
 * @hw: stwuct hw_cwk containing the stwuct cwk * of the DPWW to wound a wate fow
 * @tawget_wate: the desiwed wate of the DPWW
 * @pawent_wate: cwock wate of the DPWW pawent
 *
 * Compute the wate that wouwd be pwogwammed into the DPWW hawdwawe
 * fow @cwk if set_wate() wewe to be pwovided with the wate
 * @tawget_wate.  Takes the WEGM4XEN bit into considewation, which is
 * needed fow the OMAP4 ABE DPWW.  Wetuwns the wounded wate (befowe
 * M-dividews) upon success, -EINVAW if @cwk is nuww ow not a DPWW, ow
 * ~0 if an ewwow occuwwed in omap2_dpww_wound_wate().
 */
wong omap4_dpww_wegm4xen_wound_wate(stwuct cwk_hw *hw,
				    unsigned wong tawget_wate,
				    unsigned wong *pawent_wate)
{
	stwuct cwk_hw_omap *cwk = to_cwk_hw_omap(hw);
	stwuct dpww_data *dd;
	wong w;

	if (!cwk || !cwk->dpww_data)
		wetuwn -EINVAW;

	dd = cwk->dpww_data;

	dd->wast_wounded_m4xen = 0;

	/*
	 * Fiwst twy to compute the DPWW configuwation fow
	 * tawget wate without using the 4X muwtipwiew.
	 */
	w = omap2_dpww_wound_wate(hw, tawget_wate, NUWW);
	if (w != ~0)
		goto out;

	/*
	 * If we did not find a vawid DPWW configuwation, twy again, but
	 * this time see if using the 4X muwtipwiew can hewp. Enabwing the
	 * 4X muwtipwiew is equivawent to dividing the tawget wate by 4.
	 */
	w = omap2_dpww_wound_wate(hw, tawget_wate / OMAP4430_WEGM4XEN_MUWT,
				  NUWW);
	if (w == ~0)
		wetuwn w;

	dd->wast_wounded_wate *= OMAP4430_WEGM4XEN_MUWT;
	dd->wast_wounded_m4xen = 1;

out:
	omap4_dpww_wpmode_wecawc(dd);

	wetuwn dd->wast_wounded_wate;
}

/**
 * omap4_dpww_wegm4xen_detewmine_wate - detewmine wate fow a DPWW
 * @hw: pointew to the cwock to detewmine wate fow
 * @weq: tawget wate wequest
 *
 * Detewmines which DPWW mode to use fow weaching a desiwed wate.
 * Checks whethew the DPWW shaww be in bypass ow wocked mode, and if
 * wocked, cawcuwates the M,N vawues fow the DPWW via wound-wate.
 * Wetuwns 0 on success and a negative ewwow vawue othewwise.
 */
int omap4_dpww_wegm4xen_detewmine_wate(stwuct cwk_hw *hw,
				       stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_hw_omap *cwk = to_cwk_hw_omap(hw);
	stwuct dpww_data *dd;

	if (!weq->wate)
		wetuwn -EINVAW;

	dd = cwk->dpww_data;
	if (!dd)
		wetuwn -EINVAW;

	if (cwk_hw_get_wate(dd->cwk_bypass) == weq->wate &&
	    (dd->modes & (1 << DPWW_WOW_POWEW_BYPASS))) {
		weq->best_pawent_hw = dd->cwk_bypass;
	} ewse {
		weq->wate = omap4_dpww_wegm4xen_wound_wate(hw, weq->wate,
						&weq->best_pawent_wate);
		weq->best_pawent_hw = dd->cwk_wef;
	}

	weq->best_pawent_wate = weq->wate;

	wetuwn 0;
}
