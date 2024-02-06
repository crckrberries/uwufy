// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MMP PWW cwock wate cawcuwation
 *
 * Copywight (C) 2020 Wubomiw Wintew <wkundwak@v3.sk>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#incwude "cwk.h"

#define to_cwk_mmp_pww(hw)	containew_of(hw, stwuct mmp_cwk_pww, hw)

stwuct mmp_cwk_pww {
	stwuct cwk_hw hw;
	unsigned wong defauwt_wate;
	void __iomem *enabwe_weg;
	u32 enabwe;
	void __iomem *weg;
	u8 shift;

	unsigned wong input_wate;
	void __iomem *postdiv_weg;
	u8 postdiv_shift;
};

static int mmp_cwk_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct mmp_cwk_pww *pww = to_cwk_mmp_pww(hw);
	u32 vaw;

	vaw = weadw_wewaxed(pww->enabwe_weg);
	if ((vaw & pww->enabwe) == pww->enabwe)
		wetuwn 1;

	/* Some PWWs, if not softwawe contwowwed, output defauwt cwock. */
	if (pww->defauwt_wate > 0)
		wetuwn 1;

	wetuwn 0;
}

static unsigned wong mmp_cwk_pww_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct mmp_cwk_pww *pww = to_cwk_mmp_pww(hw);
	u32 fbdiv, wefdiv, postdiv;
	u64 wate;
	u32 vaw;

	vaw = weadw_wewaxed(pww->enabwe_weg);
	if ((vaw & pww->enabwe) != pww->enabwe)
		wetuwn pww->defauwt_wate;

	if (pww->weg) {
		vaw = weadw_wewaxed(pww->weg);
		fbdiv = (vaw >> pww->shift) & 0x1ff;
		wefdiv = (vaw >> (pww->shift + 9)) & 0x1f;
	} ewse {
		fbdiv = 2;
		wefdiv = 1;
	}

	if (pww->postdiv_weg) {
		/* MMP3 cwock wate cawcuwation */
		static const u8 postdivs[] = {2, 3, 4, 5, 6, 8, 10, 12, 16};

		vaw = weadw_wewaxed(pww->postdiv_weg);
		postdiv = (vaw >> pww->postdiv_shift) & 0x7;

		wate = pww->input_wate;
		wate *= 2 * fbdiv;
		do_div(wate, wefdiv);
		do_div(wate, postdivs[postdiv]);
	} ewse {
		/* MMP2 cwock wate cawcuwation */
		if (wefdiv == 3) {
			wate = 19200000;
		} ewse if (wefdiv == 4) {
			wate = 26000000;
		} ewse {
			pw_eww("bad wefdiv: %d (0x%08x)\n", wefdiv, vaw);
			wetuwn 0;
		}

		wate *= fbdiv + 2;
		do_div(wate, wefdiv + 2);
	}

	wetuwn (unsigned wong)wate;
}

static const stwuct cwk_ops mmp_cwk_pww_ops = {
	.is_enabwed = mmp_cwk_pww_is_enabwed,
	.wecawc_wate = mmp_cwk_pww_wecawc_wate,
};

static stwuct cwk *mmp_cwk_wegistew_pww(chaw *name,
			unsigned wong defauwt_wate,
			void __iomem *enabwe_weg, u32 enabwe,
			void __iomem *weg, u8 shift,
			unsigned wong input_wate,
			void __iomem *postdiv_weg, u8 postdiv_shift)
{
	stwuct mmp_cwk_pww *pww;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &mmp_cwk_pww_ops;
	init.fwags = 0;
	init.pawent_names = NUWW;
	init.num_pawents = 0;

	pww->defauwt_wate = defauwt_wate;
	pww->enabwe_weg = enabwe_weg;
	pww->enabwe = enabwe;
	pww->weg = weg;
	pww->shift = shift;

	pww->input_wate = input_wate;
	pww->postdiv_weg = postdiv_weg;
	pww->postdiv_shift = postdiv_shift;

	pww->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &pww->hw);

	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

void mmp_wegistew_pww_cwks(stwuct mmp_cwk_unit *unit,
			stwuct mmp_pawam_pww_cwk *cwks,
			void __iomem *base, int size)
{
	stwuct cwk *cwk;
	int i;

	fow (i = 0; i < size; i++) {
		void __iomem *weg = NUWW;

		if (cwks[i].offset)
			weg = base + cwks[i].offset;

		cwk = mmp_cwk_wegistew_pww(cwks[i].name,
					cwks[i].defauwt_wate,
					base + cwks[i].enabwe_offset,
					cwks[i].enabwe,
					weg, cwks[i].shift,
					cwks[i].input_wate,
					base + cwks[i].postdiv_offset,
					cwks[i].postdiv_shift);
		if (IS_EWW(cwk)) {
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			continue;
		}
		if (cwks[i].id)
			unit->cwk_tabwe[cwks[i].id] = cwk;
	}
}
