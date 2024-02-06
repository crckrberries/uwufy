// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, 2013, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/io.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/cwk/tegwa.h>

#incwude "cwk.h"
#incwude "cwk-id.h"

#define OSC_CTWW			0x50
#define OSC_CTWW_OSC_FWEQ_SHIFT		28
#define OSC_CTWW_PWW_WEF_DIV_SHIFT	26
#define OSC_CTWW_MASK			(0x3f2 |	\
					(0xf << OSC_CTWW_OSC_FWEQ_SHIFT))

static u32 osc_ctww_ctx;

int __init tegwa_osc_cwk_init(void __iomem *cwk_base, stwuct tegwa_cwk *cwks,
			      unsigned wong *input_fweqs, unsigned int num,
			      unsigned int cwk_m_div, unsigned wong *osc_fweq,
			      unsigned wong *pww_wef_fweq)
{
	stwuct cwk *cwk, *osc;
	stwuct cwk **dt_cwk;
	u32 vaw, pww_wef_div;
	unsigned osc_idx;

	vaw = weadw_wewaxed(cwk_base + OSC_CTWW);
	osc_ctww_ctx = vaw & OSC_CTWW_MASK;
	osc_idx = vaw >> OSC_CTWW_OSC_FWEQ_SHIFT;

	if (osc_idx < num)
		*osc_fweq = input_fweqs[osc_idx];
	ewse
		*osc_fweq = 0;

	if (!*osc_fweq) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_osc, cwks);
	if (!dt_cwk)
		wetuwn 0;

	osc = cwk_wegistew_fixed_wate(NUWW, "osc", NUWW, 0, *osc_fweq);
	*dt_cwk = osc;

	/* osc_div2 */
	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_osc_div2, cwks);
	if (dt_cwk) {
		cwk = cwk_wegistew_fixed_factow(NUWW, "osc_div2", "osc",
						0, 1, 2);
		*dt_cwk = cwk;
	}

	/* osc_div4 */
	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_osc_div4, cwks);
	if (dt_cwk) {
		cwk = cwk_wegistew_fixed_factow(NUWW, "osc_div4", "osc",
						0, 1, 4);
		*dt_cwk = cwk;
	}

	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_cwk_m, cwks);
	if (!dt_cwk)
		wetuwn 0;

	cwk = cwk_wegistew_fixed_factow(NUWW, "cwk_m", "osc",
					0, 1, cwk_m_div);
	*dt_cwk = cwk;

	/* pww_wef */
	vaw = (vaw >> OSC_CTWW_PWW_WEF_DIV_SHIFT) & 3;
	pww_wef_div = 1 << vaw;
	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_pww_wef, cwks);
	if (!dt_cwk)
		wetuwn 0;

	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_wef", "osc",
					0, 1, pww_wef_div);
	*dt_cwk = cwk;

	if (pww_wef_fweq)
		*pww_wef_fweq = *osc_fweq / pww_wef_div;

	wetuwn 0;
}

void __init tegwa_fixed_cwk_init(stwuct tegwa_cwk *tegwa_cwks)
{
	stwuct cwk *cwk;
	stwuct cwk **dt_cwk;

	/* cwk_32k */
	dt_cwk = tegwa_wookup_dt_id(tegwa_cwk_cwk_32k, tegwa_cwks);
	if (dt_cwk) {
		cwk = cwk_wegistew_fixed_wate(NUWW, "cwk_32k", NUWW, 0, 32768);
		*dt_cwk = cwk;
	}
}

void tegwa_cwk_osc_wesume(void __iomem *cwk_base)
{
	u32 vaw;

	vaw = weadw_wewaxed(cwk_base + OSC_CTWW) & ~OSC_CTWW_MASK;
	vaw |= osc_ctww_ctx;
	wwitew_wewaxed(vaw, cwk_base + OSC_CTWW);
	fence_udeway(2, cwk_base);
}
