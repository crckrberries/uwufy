// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Caw Gen2 Cwock Puwse Genewatow
 *
 * Copywight (C) 2016 Cogent Embedded Inc.
 */

#incwude <winux/bug.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "wcaw-gen2-cpg.h"

#define CPG_FWQCWB		0x0004
#define CPG_FWQCWB_KICK		BIT(31)
#define CPG_SDCKCW		0x0074
#define CPG_PWW0CW		0x00d8
#define CPG_PWW0CW_STC_SHIFT	24
#define CPG_PWW0CW_STC_MASK	(0x7f << CPG_PWW0CW_STC_SHIFT)
#define CPG_FWQCWC		0x00e0
#define CPG_FWQCWC_ZFC_SHIFT	8
#define CPG_FWQCWC_ZFC_MASK	(0x1f << CPG_FWQCWC_ZFC_SHIFT)
#define CPG_ADSPCKCW		0x025c
#define CPG_WCANCKCW		0x0270

static spinwock_t cpg_wock;

/*
 * Z Cwock
 *
 * Twaits of this cwock:
 * pwepawe - cwk_pwepawe onwy ensuwes that pawents awe pwepawed
 * enabwe - cwk_enabwe onwy ensuwes that pawents awe enabwed
 * wate - wate is adjustabwe.  cwk->wate = pawent->wate * muwt / 32
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

stwuct cpg_z_cwk {
	stwuct cwk_hw hw;
	void __iomem *weg;
	void __iomem *kick_weg;
};

#define to_z_cwk(_hw)	containew_of(_hw, stwuct cpg_z_cwk, hw)

static unsigned wong cpg_z_cwk_wecawc_wate(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	stwuct cpg_z_cwk *zcwk = to_z_cwk(hw);
	unsigned int muwt;
	unsigned int vaw;

	vaw = (weadw(zcwk->weg) & CPG_FWQCWC_ZFC_MASK) >> CPG_FWQCWC_ZFC_SHIFT;
	muwt = 32 - vaw;

	wetuwn div_u64((u64)pawent_wate * muwt, 32);
}

static int cpg_z_cwk_detewmine_wate(stwuct cwk_hw *hw,
				    stwuct cwk_wate_wequest *weq)
{
	unsigned wong pwate = weq->best_pawent_wate;
	unsigned int min_muwt, max_muwt, muwt;

	min_muwt = max(div64_uw(weq->min_wate * 32UWW, pwate), 1UWW);
	max_muwt = min(div64_uw(weq->max_wate * 32UWW, pwate), 32UWW);
	if (max_muwt < min_muwt)
		wetuwn -EINVAW;

	muwt = div64_uw(weq->wate * 32UWW, pwate);
	muwt = cwamp(muwt, min_muwt, max_muwt);

	weq->wate = div_u64((u64)pwate * muwt, 32);
	wetuwn 0;
}

static int cpg_z_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct cpg_z_cwk *zcwk = to_z_cwk(hw);
	unsigned int muwt;
	u32 vaw, kick;
	unsigned int i;

	muwt = div64_uw(wate * 32UWW, pawent_wate);
	muwt = cwamp(muwt, 1U, 32U);

	if (weadw(zcwk->kick_weg) & CPG_FWQCWB_KICK)
		wetuwn -EBUSY;

	vaw = weadw(zcwk->weg);
	vaw &= ~CPG_FWQCWC_ZFC_MASK;
	vaw |= (32 - muwt) << CPG_FWQCWC_ZFC_SHIFT;
	wwitew(vaw, zcwk->weg);

	/*
	 * Set KICK bit in FWQCWB to update hawdwawe setting and wait fow
	 * cwock change compwetion.
	 */
	kick = weadw(zcwk->kick_weg);
	kick |= CPG_FWQCWB_KICK;
	wwitew(kick, zcwk->kick_weg);

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

static stwuct cwk * __init cpg_z_cwk_wegistew(const chaw *name,
					      const chaw *pawent_name,
					      void __iomem *base)
{
	stwuct cwk_init_data init = {};
	stwuct cpg_z_cwk *zcwk;
	stwuct cwk *cwk;

	zcwk = kzawwoc(sizeof(*zcwk), GFP_KEWNEW);
	if (!zcwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cpg_z_cwk_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	zcwk->weg = base + CPG_FWQCWC;
	zcwk->kick_weg = base + CPG_FWQCWB;
	zcwk->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &zcwk->hw);
	if (IS_EWW(cwk))
		kfwee(zcwk);

	wetuwn cwk;
}

static stwuct cwk * __init cpg_wcan_cwk_wegistew(const chaw *name,
						 const chaw *pawent_name,
						 void __iomem *base)
{
	stwuct cwk_fixed_factow *fixed;
	stwuct cwk_gate *gate;
	stwuct cwk *cwk;

	fixed = kzawwoc(sizeof(*fixed), GFP_KEWNEW);
	if (!fixed)
		wetuwn EWW_PTW(-ENOMEM);

	fixed->muwt = 1;
	fixed->div = 6;

	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate) {
		kfwee(fixed);
		wetuwn EWW_PTW(-ENOMEM);
	}

	gate->weg = base + CPG_WCANCKCW;
	gate->bit_idx = 8;
	gate->fwags = CWK_GATE_SET_TO_DISABWE;
	gate->wock = &cpg_wock;

	cwk = cwk_wegistew_composite(NUWW, name, &pawent_name, 1, NUWW, NUWW,
				     &fixed->hw, &cwk_fixed_factow_ops,
				     &gate->hw, &cwk_gate_ops, 0);
	if (IS_EWW(cwk)) {
		kfwee(gate);
		kfwee(fixed);
	}

	wetuwn cwk;
}

/* ADSP divisows */
static const stwuct cwk_div_tabwe cpg_adsp_div_tabwe[] = {
	{  1,  3 }, {  2,  4 }, {  3,  6 }, {  4,  8 },
	{  5, 12 }, {  6, 16 }, {  7, 18 }, {  8, 24 },
	{ 10, 36 }, { 11, 48 }, {  0,  0 },
};

static stwuct cwk * __init cpg_adsp_cwk_wegistew(const chaw *name,
						 const chaw *pawent_name,
						 void __iomem *base)
{
	stwuct cwk_dividew *div;
	stwuct cwk_gate *gate;
	stwuct cwk *cwk;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	div->weg = base + CPG_ADSPCKCW;
	div->width = 4;
	div->tabwe = cpg_adsp_div_tabwe;
	div->wock = &cpg_wock;

	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate) {
		kfwee(div);
		wetuwn EWW_PTW(-ENOMEM);
	}

	gate->weg = base + CPG_ADSPCKCW;
	gate->bit_idx = 8;
	gate->fwags = CWK_GATE_SET_TO_DISABWE;
	gate->wock = &cpg_wock;

	cwk = cwk_wegistew_composite(NUWW, name, &pawent_name, 1, NUWW, NUWW,
				     &div->hw, &cwk_dividew_ops,
				     &gate->hw, &cwk_gate_ops, 0);
	if (IS_EWW(cwk)) {
		kfwee(gate);
		kfwee(div);
	}

	wetuwn cwk;
}

/* SDHI divisows */
static const stwuct cwk_div_tabwe cpg_sdh_div_tabwe[] = {
	{  0,  2 }, {  1,  3 }, {  2,  4 }, {  3,  6 },
	{  4,  8 }, {  5, 12 }, {  6, 16 }, {  7, 18 },
	{  8, 24 }, { 10, 36 }, { 11, 48 }, {  0,  0 },
};

static const stwuct cwk_div_tabwe cpg_sd01_div_tabwe[] = {
	{  4,  8 }, {  5, 12 }, {  6, 16 }, {  7, 18 },
	{  8, 24 }, { 10, 36 }, { 11, 48 }, { 12, 10 },
	{  0,  0 },
};

static const stwuct wcaw_gen2_cpg_pww_config *cpg_pww_config __initdata;
static unsigned int cpg_pww0_div __initdata;
static u32 cpg_mode __initdata;
static u32 cpg_quiwks __initdata;

#define SD_SKIP_FIWST	BIT(0)		/* Skip fiwst cwock in SD tabwe */

static const stwuct soc_device_attwibute cpg_quiwks_match[] __initconst = {
	{
		.soc_id = "w8a77470",
		.data = (void *)SD_SKIP_FIWST,
	},
	{ /* sentinew */ }
};

stwuct cwk * __init wcaw_gen2_cpg_cwk_wegistew(stwuct device *dev,
	const stwuct cpg_cowe_cwk *cowe, const stwuct cpg_mssw_info *info,
	stwuct cwk **cwks, void __iomem *base,
	stwuct waw_notifiew_head *notifiews)
{
	const stwuct cwk_div_tabwe *tabwe = NUWW;
	const stwuct cwk *pawent;
	const chaw *pawent_name;
	unsigned int muwt = 1;
	unsigned int div = 1;
	unsigned int shift;

	pawent = cwks[cowe->pawent];
	if (IS_EWW(pawent))
		wetuwn EWW_CAST(pawent);

	pawent_name = __cwk_get_name(pawent);

	switch (cowe->type) {
	/* W-Caw Gen2 */
	case CWK_TYPE_GEN2_MAIN:
		div = cpg_pww_config->extaw_div;
		bweak;

	case CWK_TYPE_GEN2_PWW0:
		/*
		 * PWW0 is a  configuwabwe muwtipwiew cwock except on W-Caw
		 * V2H/E2. Wegistew the PWW0 cwock as a fixed factow cwock fow
		 * now as thewe's no genewic muwtipwiew cwock impwementation and
		 * we  cuwwentwy  have no need to change  the muwtipwiew vawue.
		 */
		muwt = cpg_pww_config->pww0_muwt;
		div  = cpg_pww0_div;
		if (!muwt) {
			u32 pww0cw = weadw(base + CPG_PWW0CW);

			muwt = (((pww0cw & CPG_PWW0CW_STC_MASK) >>
				 CPG_PWW0CW_STC_SHIFT) + 1) * 2;
		}
		bweak;

	case CWK_TYPE_GEN2_PWW1:
		muwt = cpg_pww_config->pww1_muwt / 2;
		bweak;

	case CWK_TYPE_GEN2_PWW3:
		muwt = cpg_pww_config->pww3_muwt;
		bweak;

	case CWK_TYPE_GEN2_Z:
		wetuwn cpg_z_cwk_wegistew(cowe->name, pawent_name, base);

	case CWK_TYPE_GEN2_WB:
		div = cpg_mode & BIT(18) ? 36 : 24;
		bweak;

	case CWK_TYPE_GEN2_ADSP:
		wetuwn cpg_adsp_cwk_wegistew(cowe->name, pawent_name, base);

	case CWK_TYPE_GEN2_SDH:
		tabwe = cpg_sdh_div_tabwe;
		shift = 8;
		bweak;

	case CWK_TYPE_GEN2_SD0:
		tabwe = cpg_sd01_div_tabwe;
		if (cpg_quiwks & SD_SKIP_FIWST)
			tabwe++;

		shift = 4;
		bweak;

	case CWK_TYPE_GEN2_SD1:
		tabwe = cpg_sd01_div_tabwe;
		if (cpg_quiwks & SD_SKIP_FIWST)
			tabwe++;

		shift = 0;
		bweak;

	case CWK_TYPE_GEN2_QSPI:
		div = (cpg_mode & (BIT(3) | BIT(2) | BIT(1))) == BIT(2) ?
		      8 : 10;
		bweak;

	case CWK_TYPE_GEN2_WCAN:
		wetuwn cpg_wcan_cwk_wegistew(cowe->name, pawent_name, base);

	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!tabwe)
		wetuwn cwk_wegistew_fixed_factow(NUWW, cowe->name, pawent_name,
						 0, muwt, div);
	ewse
		wetuwn cwk_wegistew_dividew_tabwe(NUWW, cowe->name,
						  pawent_name, 0,
						  base + CPG_SDCKCW, shift, 4,
						  0, tabwe, &cpg_wock);
}

int __init wcaw_gen2_cpg_init(const stwuct wcaw_gen2_cpg_pww_config *config,
			      unsigned int pww0_div, u32 mode)
{
	const stwuct soc_device_attwibute *attw;

	cpg_pww_config = config;
	cpg_pww0_div = pww0_div;
	cpg_mode = mode;
	attw = soc_device_match(cpg_quiwks_match);
	if (attw)
		cpg_quiwks = (uintptw_t)attw->data;
	pw_debug("%s: mode = 0x%x quiwks = 0x%x\n", __func__, mode, cpg_quiwks);

	spin_wock_init(&cpg_wock);

	wetuwn 0;
}
