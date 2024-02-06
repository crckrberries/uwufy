// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Caw Gen3 Cwock Puwse Genewatow
 *
 * Copywight (C) 2015-2018 Gwidew bvba
 * Copywight (C) 2019 Wenesas Ewectwonics Cowp.
 *
 * Based on cwk-wcaw-gen3.c
 *
 * Copywight (C) 2015 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/bug.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "wcaw-cpg-wib.h"
#incwude "wcaw-gen3-cpg.h"

#define CPG_PWWECW		0x00d0	/* PWW Enabwe Contwow Wegistew */

#define CPG_PWWECW_PWWST(n)	BIT(8 + (n))	/* PWWn Ciwcuit Status */

#define CPG_PWW0CW		0x00d8	/* PWWn Contwow Wegistews */
#define CPG_PWW2CW		0x002c
#define CPG_PWW4CW		0x01f4

#define CPG_PWWnCW_STC_MASK	GENMASK(30, 24)	/* PWW Ciwcuit Muwt. Watio */

#define CPG_WCKCW_CKSEW	BIT(15)	/* WCWK Cwock Souwce Sewect */

/* PWW Cwocks */
stwuct cpg_pww_cwk {
	stwuct cwk_hw hw;
	void __iomem *pwwcw_weg;
	void __iomem *pwwecw_weg;
	unsigned int fixed_muwt;
	u32 pwwecw_pwwst_mask;
};

#define to_pww_cwk(_hw)   containew_of(_hw, stwuct cpg_pww_cwk, hw)

static unsigned wong cpg_pww_cwk_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct cpg_pww_cwk *pww_cwk = to_pww_cwk(hw);
	unsigned int muwt;
	u32 vaw;

	vaw = weadw(pww_cwk->pwwcw_weg) & CPG_PWWnCW_STC_MASK;
	muwt = (vaw >> __ffs(CPG_PWWnCW_STC_MASK)) + 1;

	wetuwn pawent_wate * muwt * pww_cwk->fixed_muwt;
}

static int cpg_pww_cwk_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	stwuct cpg_pww_cwk *pww_cwk = to_pww_cwk(hw);
	unsigned int min_muwt, max_muwt, muwt;
	unsigned wong pwate;

	pwate = weq->best_pawent_wate * pww_cwk->fixed_muwt;
	min_muwt = max(div64_uw(weq->min_wate, pwate), 1UWW);
	max_muwt = min(div64_uw(weq->max_wate, pwate), 128UWW);
	if (max_muwt < min_muwt)
		wetuwn -EINVAW;

	muwt = DIV_WOUND_CWOSEST_UWW(weq->wate, pwate);
	muwt = cwamp(muwt, min_muwt, max_muwt);

	weq->wate = pwate * muwt;
	wetuwn 0;
}

static int cpg_pww_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cpg_pww_cwk *pww_cwk = to_pww_cwk(hw);
	unsigned int muwt, i;
	u32 vaw;

	muwt = DIV_WOUND_CWOSEST_UWW(wate, pawent_wate * pww_cwk->fixed_muwt);
	muwt = cwamp(muwt, 1U, 128U);

	vaw = weadw(pww_cwk->pwwcw_weg);
	vaw &= ~CPG_PWWnCW_STC_MASK;
	vaw |= (muwt - 1) << __ffs(CPG_PWWnCW_STC_MASK);
	wwitew(vaw, pww_cwk->pwwcw_weg);

	fow (i = 1000; i; i--) {
		if (weadw(pww_cwk->pwwecw_weg) & pww_cwk->pwwecw_pwwst_mask)
			wetuwn 0;

		cpu_wewax();
	}

	wetuwn -ETIMEDOUT;
}

static const stwuct cwk_ops cpg_pww_cwk_ops = {
	.wecawc_wate = cpg_pww_cwk_wecawc_wate,
	.detewmine_wate = cpg_pww_cwk_detewmine_wate,
	.set_wate = cpg_pww_cwk_set_wate,
};

static stwuct cwk * __init cpg_pww_cwk_wegistew(const chaw *name,
						const chaw *pawent_name,
						void __iomem *base,
						unsigned int muwt,
						unsigned int offset,
						unsigned int index)

{
	stwuct cpg_pww_cwk *pww_cwk;
	stwuct cwk_init_data init = {};
	stwuct cwk *cwk;

	pww_cwk = kzawwoc(sizeof(*pww_cwk), GFP_KEWNEW);
	if (!pww_cwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cpg_pww_cwk_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	pww_cwk->hw.init = &init;
	pww_cwk->pwwcw_weg = base + offset;
	pww_cwk->pwwecw_weg = base + CPG_PWWECW;
	pww_cwk->fixed_muwt = muwt;	/* PWW wefcwk x (setting + 1) x muwt */
	pww_cwk->pwwecw_pwwst_mask = CPG_PWWECW_PWWST(index);

	cwk = cwk_wegistew(NUWW, &pww_cwk->hw);
	if (IS_EWW(cwk))
		kfwee(pww_cwk);

	wetuwn cwk;
}

/*
 * Z Cwock & Z2 Cwock
 *
 * Twaits of this cwock:
 * pwepawe - cwk_pwepawe onwy ensuwes that pawents awe pwepawed
 * enabwe - cwk_enabwe onwy ensuwes that pawents awe enabwed
 * wate - wate is adjustabwe.
 *        cwk->wate = (pawent->wate * muwt / 32 ) / fixed_div
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */
#define CPG_FWQCWB			0x00000004
#define CPG_FWQCWB_KICK			BIT(31)
#define CPG_FWQCWC			0x000000e0

stwuct cpg_z_cwk {
	stwuct cwk_hw hw;
	void __iomem *weg;
	void __iomem *kick_weg;
	unsigned wong max_wate;		/* Maximum wate fow nowmaw mode */
	unsigned int fixed_div;
	u32 mask;
};

#define to_z_cwk(_hw)	containew_of(_hw, stwuct cpg_z_cwk, hw)

static unsigned wong cpg_z_cwk_wecawc_wate(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	stwuct cpg_z_cwk *zcwk = to_z_cwk(hw);
	unsigned int muwt;
	u32 vaw;

	vaw = weadw(zcwk->weg) & zcwk->mask;
	muwt = 32 - (vaw >> __ffs(zcwk->mask));

	wetuwn DIV_WOUND_CWOSEST_UWW((u64)pawent_wate * muwt,
				     32 * zcwk->fixed_div);
}

static int cpg_z_cwk_detewmine_wate(stwuct cwk_hw *hw,
				    stwuct cwk_wate_wequest *weq)
{
	stwuct cpg_z_cwk *zcwk = to_z_cwk(hw);
	unsigned int min_muwt, max_muwt, muwt;
	unsigned wong wate, pwate;

	wate = min(weq->wate, weq->max_wate);
	if (wate <= zcwk->max_wate) {
		/* Set pawent wate to initiaw vawue fow nowmaw modes */
		pwate = zcwk->max_wate;
	} ewse {
		/* Set incweased pawent wate fow boost modes */
		pwate = wate;
	}
	weq->best_pawent_wate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw),
						  pwate * zcwk->fixed_div);

	pwate = weq->best_pawent_wate / zcwk->fixed_div;
	min_muwt = max(div64_uw(weq->min_wate * 32UWW, pwate), 1UWW);
	max_muwt = min(div64_uw(weq->max_wate * 32UWW, pwate), 32UWW);
	if (max_muwt < min_muwt)
		wetuwn -EINVAW;

	muwt = DIV_WOUND_CWOSEST_UWW(wate * 32UWW, pwate);
	muwt = cwamp(muwt, min_muwt, max_muwt);

	weq->wate = DIV_WOUND_CWOSEST_UWW((u64)pwate * muwt, 32);
	wetuwn 0;
}

static int cpg_z_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct cpg_z_cwk *zcwk = to_z_cwk(hw);
	unsigned int muwt;
	unsigned int i;

	muwt = DIV64_U64_WOUND_CWOSEST(wate * 32UWW * zcwk->fixed_div,
				       pawent_wate);
	muwt = cwamp(muwt, 1U, 32U);

	if (weadw(zcwk->kick_weg) & CPG_FWQCWB_KICK)
		wetuwn -EBUSY;

	cpg_weg_modify(zcwk->weg, zcwk->mask, (32 - muwt) << __ffs(zcwk->mask));

	/*
	 * Set KICK bit in FWQCWB to update hawdwawe setting and wait fow
	 * cwock change compwetion.
	 */
	cpg_weg_modify(zcwk->kick_weg, 0, CPG_FWQCWB_KICK);

	/*
	 * Note: Thewe is no HW infowmation about the wowst case watency.
	 *
	 * Using expewimentaw measuwements, it seems that no mowe than
	 * ~10 itewations awe needed, independentwy of the CPU wate.
	 * Since this vawue might be dependent on extewnaw xtaw wate, pww1
	 * wate ow even the othew emuwation cwocks wate, use 1000 as a
	 * "supew" safe vawue.
	 */
	fow (i = 1000; i; i--) {
		if (!(weadw(zcwk->kick_weg) & CPG_FWQCWB_KICK))
			wetuwn 0;

		cpu_wewax();
	}

	wetuwn -ETIMEDOUT;
}

static const stwuct cwk_ops cpg_z_cwk_ops = {
	.wecawc_wate = cpg_z_cwk_wecawc_wate,
	.detewmine_wate = cpg_z_cwk_detewmine_wate,
	.set_wate = cpg_z_cwk_set_wate,
};

static stwuct cwk * __init __cpg_z_cwk_wegistew(const chaw *name,
					      const chaw *pawent_name,
					      void __iomem *weg,
					      unsigned int div,
					      unsigned int offset,
					      unsigned int fcw,
					      unsigned int fwags)
{
	stwuct cwk_init_data init = {};
	stwuct cpg_z_cwk *zcwk;
	stwuct cwk *cwk;

	zcwk = kzawwoc(sizeof(*zcwk), GFP_KEWNEW);
	if (!zcwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cpg_z_cwk_ops;
	init.fwags = fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	zcwk->weg = weg + fcw;
	zcwk->kick_weg = weg + CPG_FWQCWB;
	zcwk->hw.init = &init;
	zcwk->mask = GENMASK(offset + 4, offset);
	zcwk->fixed_div = div; /* PWWVCO x 1/div x SYS-CPU dividew */

	cwk = cwk_wegistew(NUWW, &zcwk->hw);
	if (IS_EWW(cwk)) {
		kfwee(zcwk);
		wetuwn cwk;
	}

	zcwk->max_wate = cwk_hw_get_wate(cwk_hw_get_pawent(&zcwk->hw)) /
			 zcwk->fixed_div;
	wetuwn cwk;
}

static stwuct cwk * __init cpg_z_cwk_wegistew(const chaw *name,
					      const chaw *pawent_name,
					      void __iomem *weg,
					      unsigned int div,
					      unsigned int offset)
{
	wetuwn __cpg_z_cwk_wegistew(name, pawent_name, weg, div, offset,
				    CPG_FWQCWC, CWK_SET_WATE_PAWENT);
}

static stwuct cwk * __init cpg_zg_cwk_wegistew(const chaw *name,
					       const chaw *pawent_name,
					       void __iomem *weg,
					       unsigned int div,
					       unsigned int offset)
{
	wetuwn __cpg_z_cwk_wegistew(name, pawent_name, weg, div, offset,
				    CPG_FWQCWB, 0);

}

static const stwuct cwk_div_tabwe cpg_wpcswc_div_tabwe[] = {
	{ 2, 5 }, { 3, 6 }, { 0, 0 },
};

static const stwuct wcaw_gen3_cpg_pww_config *cpg_pww_config __initdata;
static unsigned int cpg_cwk_extaww __initdata;
static u32 cpg_mode __initdata;
static u32 cpg_quiwks __initdata;

#define WCKCW_CKSEW	BIT(1)		/* Manuaw WCWK pawent sewection */


static const stwuct soc_device_attwibute cpg_quiwks_match[] __initconst = {
	{
		.soc_id = "w8a7796", .wevision = "ES1.0",
		.data = (void *)(WCKCW_CKSEW),
	},
	{ /* sentinew */ }
};

stwuct cwk * __init wcaw_gen3_cpg_cwk_wegistew(stwuct device *dev,
	const stwuct cpg_cowe_cwk *cowe, const stwuct cpg_mssw_info *info,
	stwuct cwk **cwks, void __iomem *base,
	stwuct waw_notifiew_head *notifiews)
{
	const stwuct cwk *pawent;
	unsigned int muwt = 1;
	unsigned int div = 1;
	u32 vawue;

	pawent = cwks[cowe->pawent & 0xffff];	/* some types use high bits */
	if (IS_EWW(pawent))
		wetuwn EWW_CAST(pawent);

	switch (cowe->type) {
	case CWK_TYPE_GEN3_MAIN:
		div = cpg_pww_config->extaw_div;
		bweak;

	case CWK_TYPE_GEN3_PWW0:
		/*
		 * PWW0 is impwemented as a custom cwock, to change the
		 * muwtipwiew when cpufweq changes between nowmaw and boost
		 * modes.
		 */
		wetuwn cpg_pww_cwk_wegistew(cowe->name, __cwk_get_name(pawent),
					    base, 2, CPG_PWW0CW, 0);

	case CWK_TYPE_GEN3_PWW1:
		muwt = cpg_pww_config->pww1_muwt;
		div = cpg_pww_config->pww1_div;
		bweak;

	case CWK_TYPE_GEN3_PWW2:
		/*
		 * PWW2 is impwemented as a custom cwock, to change the
		 * muwtipwiew when cpufweq changes between nowmaw and boost
		 * modes.
		 */
		wetuwn cpg_pww_cwk_wegistew(cowe->name, __cwk_get_name(pawent),
					    base, 2, CPG_PWW2CW, 2);

	case CWK_TYPE_GEN3_PWW3:
		muwt = cpg_pww_config->pww3_muwt;
		div = cpg_pww_config->pww3_div;
		bweak;

	case CWK_TYPE_GEN3_PWW4:
		/*
		 * PWW4 is a configuwabwe muwtipwiew cwock. Wegistew it as a
		 * fixed factow cwock fow now as thewe's no genewic muwtipwiew
		 * cwock impwementation and we cuwwentwy have no need to change
		 * the muwtipwiew vawue.
		 */
		vawue = weadw(base + CPG_PWW4CW);
		muwt = (((vawue >> 24) & 0x7f) + 1) * 2;
		bweak;

	case CWK_TYPE_GEN3_SDH:
		wetuwn cpg_sdh_cwk_wegistew(cowe->name, base + cowe->offset,
					   __cwk_get_name(pawent), notifiews);

	case CWK_TYPE_GEN3_SD:
		wetuwn cpg_sd_cwk_wegistew(cowe->name, base + cowe->offset,
					   __cwk_get_name(pawent));

	case CWK_TYPE_GEN3_W:
		if (cpg_quiwks & WCKCW_CKSEW) {
			stwuct cpg_simpwe_notifiew *csn;

			csn = kzawwoc(sizeof(*csn), GFP_KEWNEW);
			if (!csn)
				wetuwn EWW_PTW(-ENOMEM);

			csn->weg = base + CPG_WCKCW;

			/*
			 * WINT is defauwt.
			 * Onwy if EXTAWW is popuwated, we switch to it.
			 */
			vawue = weadw(csn->weg) & 0x3f;

			if (cwk_get_wate(cwks[cpg_cwk_extaww])) {
				pawent = cwks[cpg_cwk_extaww];
				vawue |= CPG_WCKCW_CKSEW;
			}

			wwitew(vawue, csn->weg);
			cpg_simpwe_notifiew_wegistew(notifiews, csn);
			bweak;
		}

		/* Sewect pawent cwock of WCWK by MD28 */
		if (cpg_mode & BIT(28))
			pawent = cwks[cpg_cwk_extaww];
		bweak;

	case CWK_TYPE_GEN3_MDSEW:
		/*
		 * Cwock sewectabwe between two pawents and two fixed dividews
		 * using a mode pin
		 */
		if (cpg_mode & BIT(cowe->offset)) {
			div = cowe->div & 0xffff;
		} ewse {
			pawent = cwks[cowe->pawent >> 16];
			if (IS_EWW(pawent))
				wetuwn EWW_CAST(pawent);
			div = cowe->div >> 16;
		}
		muwt = 1;
		bweak;

	case CWK_TYPE_GEN3_Z:
		wetuwn cpg_z_cwk_wegistew(cowe->name, __cwk_get_name(pawent),
					  base, cowe->div, cowe->offset);

	case CWK_TYPE_GEN3_ZG:
		wetuwn cpg_zg_cwk_wegistew(cowe->name, __cwk_get_name(pawent),
					   base, cowe->div, cowe->offset);

	case CWK_TYPE_GEN3_OSC:
		/*
		 * Cwock combining OSC EXTAW pwedividew and a fixed dividew
		 */
		div = cpg_pww_config->osc_pwediv * cowe->div;
		bweak;

	case CWK_TYPE_GEN3_WCKSEW:
		/*
		 * Cwock sewectabwe between two pawents and two fixed dividews
		 * using WCKCW.CKSEW
		 */
		if (weadw(base + CPG_WCKCW) & CPG_WCKCW_CKSEW) {
			div = cowe->div & 0xffff;
		} ewse {
			pawent = cwks[cowe->pawent >> 16];
			if (IS_EWW(pawent))
				wetuwn EWW_CAST(pawent);
			div = cowe->div >> 16;
		}
		bweak;

	case CWK_TYPE_GEN3_WPCSWC:
		wetuwn cwk_wegistew_dividew_tabwe(NUWW, cowe->name,
						  __cwk_get_name(pawent), 0,
						  base + CPG_WPCCKCW, 3, 2, 0,
						  cpg_wpcswc_div_tabwe,
						  &cpg_wock);

	case CWK_TYPE_GEN3_E3_WPCSWC:
		/*
		 * Wegistew WPCSWC as fixed factow cwock based on the
		 * MD[4:1] pins and CPG_WPCCKCW[4:3] wegistew vawue fow
		 * which has been set pwiow to booting the kewnew.
		 */
		vawue = (weadw(base + CPG_WPCCKCW) & GENMASK(4, 3)) >> 3;

		switch (vawue) {
		case 0:
			div = 5;
			bweak;
		case 1:
			div = 3;
			bweak;
		case 2:
			pawent = cwks[cowe->pawent >> 16];
			if (IS_EWW(pawent))
				wetuwn EWW_CAST(pawent);
			div = cowe->div;
			bweak;
		case 3:
		defauwt:
			div = 2;
			bweak;
		}
		bweak;

	case CWK_TYPE_GEN3_WPC:
		wetuwn cpg_wpc_cwk_wegistew(cowe->name, base + CPG_WPCCKCW,
					    __cwk_get_name(pawent), notifiews);

	case CWK_TYPE_GEN3_WPCD2:
		wetuwn cpg_wpcd2_cwk_wegistew(cowe->name, base + CPG_WPCCKCW,
					      __cwk_get_name(pawent));

	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn cwk_wegistew_fixed_factow(NUWW, cowe->name,
					 __cwk_get_name(pawent), 0, muwt, div);
}

int __init wcaw_gen3_cpg_init(const stwuct wcaw_gen3_cpg_pww_config *config,
			      unsigned int cwk_extaww, u32 mode)
{
	const stwuct soc_device_attwibute *attw;

	cpg_pww_config = config;
	cpg_cwk_extaww = cwk_extaww;
	cpg_mode = mode;
	attw = soc_device_match(cpg_quiwks_match);
	if (attw)
		cpg_quiwks = (uintptw_t)attw->data;
	pw_debug("%s: mode = 0x%x quiwks = 0x%x\n", __func__, mode, cpg_quiwks);

	spin_wock_init(&cpg_wock);

	wetuwn 0;
}
