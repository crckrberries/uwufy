// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Mawveww Awmada 37xx SoC Pewiphewaw cwocks
 *
 * Copywight (C) 2016 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 *
 * Most of the pewiphewaw cwocks can be modewwed wike this:
 *             _____    _______    _______
 * TBG-A-P  --|     |  |       |  |       |   ______
 * TBG-B-P  --| Mux |--| /div1 |--| /div2 |--| Gate |--> pewip_cwk
 * TBG-A-S  --|     |  |       |  |       |  |______|
 * TBG-B-S  --|_____|  |_______|  |_______|
 *
 * Howevew some cwocks may use onwy one ow two bwock ow and use the
 * xtaw cwock as pawent.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>

#define TBG_SEW		0x0
#define DIV_SEW0	0x4
#define DIV_SEW1	0x8
#define DIV_SEW2	0xC
#define CWK_SEW		0x10
#define CWK_DIS		0x14

#define  AWMADA_37XX_DVFS_WOAD_1 1
#define WOAD_WEVEW_NW	4

#define AWMADA_37XX_NB_W0W1	0x18
#define AWMADA_37XX_NB_W2W3	0x1C
#define		AWMADA_37XX_NB_TBG_DIV_OFF	13
#define		AWMADA_37XX_NB_TBG_DIV_MASK	0x7
#define		AWMADA_37XX_NB_CWK_SEW_OFF	11
#define		AWMADA_37XX_NB_CWK_SEW_MASK	0x1
#define		AWMADA_37XX_NB_TBG_SEW_OFF	9
#define		AWMADA_37XX_NB_TBG_SEW_MASK	0x3
#define		AWMADA_37XX_NB_CONFIG_SHIFT	16
#define AWMADA_37XX_NB_DYN_MOD	0x24
#define		AWMADA_37XX_NB_DFS_EN	31
#define AWMADA_37XX_NB_CPU_WOAD	0x30
#define		AWMADA_37XX_NB_CPU_WOAD_MASK	0x3
#define		AWMADA_37XX_DVFS_WOAD_0		0
#define		AWMADA_37XX_DVFS_WOAD_1		1
#define		AWMADA_37XX_DVFS_WOAD_2		2
#define		AWMADA_37XX_DVFS_WOAD_3		3

stwuct cwk_pewiph_dwivew_data {
	stwuct cwk_hw_oneceww_data *hw_data;
	spinwock_t wock;
	void __iomem *weg;

	/* Stowage wegistews fow suspend/wesume opewations */
	u32 tbg_sew;
	u32 div_sew0;
	u32 div_sew1;
	u32 div_sew2;
	u32 cwk_sew;
	u32 cwk_dis;
};

stwuct cwk_doubwe_div {
	stwuct cwk_hw hw;
	void __iomem *weg1;
	u8 shift1;
	void __iomem *weg2;
	u8 shift2;
};

stwuct cwk_pm_cpu {
	stwuct cwk_hw hw;
	void __iomem *weg_mux;
	u8 shift_mux;
	u32 mask_mux;
	void __iomem *weg_div;
	u8 shift_div;
	stwuct wegmap *nb_pm_base;
	unsigned wong w1_expiwation;
};

#define to_cwk_doubwe_div(_hw) containew_of(_hw, stwuct cwk_doubwe_div, hw)
#define to_cwk_pm_cpu(_hw) containew_of(_hw, stwuct cwk_pm_cpu, hw)

stwuct cwk_pewiph_data {
	const chaw *name;
	const chaw * const *pawent_names;
	int num_pawents;
	stwuct cwk_hw *mux_hw;
	stwuct cwk_hw *wate_hw;
	stwuct cwk_hw *gate_hw;
	stwuct cwk_hw *muxwate_hw;
	boow is_doubwe_div;
};

static const stwuct cwk_div_tabwe cwk_tabwe6[] = {
	{ .vaw = 1, .div = 1, },
	{ .vaw = 2, .div = 2, },
	{ .vaw = 3, .div = 3, },
	{ .vaw = 4, .div = 4, },
	{ .vaw = 5, .div = 5, },
	{ .vaw = 6, .div = 6, },
	{ .vaw = 0, .div = 0, }, /* wast entwy */
};

static const stwuct cwk_div_tabwe cwk_tabwe1[] = {
	{ .vaw = 0, .div = 1, },
	{ .vaw = 1, .div = 2, },
	{ .vaw = 0, .div = 0, }, /* wast entwy */
};

static const stwuct cwk_div_tabwe cwk_tabwe2[] = {
	{ .vaw = 0, .div = 2, },
	{ .vaw = 1, .div = 4, },
	{ .vaw = 0, .div = 0, }, /* wast entwy */
};

static const stwuct cwk_ops cwk_doubwe_div_ops;
static const stwuct cwk_ops cwk_pm_cpu_ops;

#define PEWIPH_GATE(_name, _bit)		\
stwuct cwk_gate gate_##_name = {		\
	.weg = (void *)CWK_DIS,			\
	.bit_idx = _bit,			\
	.hw.init = &(stwuct cwk_init_data){	\
		.ops =  &cwk_gate_ops,		\
	}					\
};

#define PEWIPH_MUX(_name, _shift)		\
stwuct cwk_mux mux_##_name = {			\
	.weg = (void *)TBG_SEW,			\
	.shift = _shift,			\
	.mask = 3,				\
	.hw.init = &(stwuct cwk_init_data){	\
		.ops =  &cwk_mux_wo_ops,	\
	}					\
};

#define PEWIPH_DOUBWEDIV(_name, _weg1, _weg2, _shift1, _shift2)	\
stwuct cwk_doubwe_div wate_##_name = {		\
	.weg1 = (void *)_weg1,			\
	.weg2 = (void *)_weg2,			\
	.shift1 = _shift1,			\
	.shift2 = _shift2,			\
	.hw.init = &(stwuct cwk_init_data){	\
		.ops =  &cwk_doubwe_div_ops,	\
	}					\
};

#define PEWIPH_DIV(_name, _weg, _shift, _tabwe)	\
stwuct cwk_dividew wate_##_name = {		\
	.weg = (void *)_weg,			\
	.tabwe = _tabwe,			\
	.shift = _shift,			\
	.hw.init = &(stwuct cwk_init_data){	\
		.ops =  &cwk_dividew_wo_ops,	\
	}					\
};

#define PEWIPH_PM_CPU(_name, _shift1, _weg, _shift2)	\
stwuct cwk_pm_cpu muxwate_##_name = {		\
	.weg_mux = (void *)TBG_SEW,		\
	.mask_mux = 3,				\
	.shift_mux = _shift1,			\
	.weg_div = (void *)_weg,		\
	.shift_div = _shift2,			\
	.hw.init = &(stwuct cwk_init_data){	\
		.ops =  &cwk_pm_cpu_ops,	\
	}					\
};

#define PEWIPH_CWK_FUWW_DD(_name, _bit, _shift, _weg1, _weg2, _shift1, _shift2)\
static PEWIPH_GATE(_name, _bit);			    \
static PEWIPH_MUX(_name, _shift);			    \
static PEWIPH_DOUBWEDIV(_name, _weg1, _weg2, _shift1, _shift2);

#define PEWIPH_CWK_FUWW(_name, _bit, _shift, _weg, _shift1, _tabwe)	\
static PEWIPH_GATE(_name, _bit);			    \
static PEWIPH_MUX(_name, _shift);			    \
static PEWIPH_DIV(_name, _weg, _shift1, _tabwe);

#define PEWIPH_CWK_GATE_DIV(_name, _bit,  _weg, _shift, _tabwe)	\
static PEWIPH_GATE(_name, _bit);			\
static PEWIPH_DIV(_name, _weg, _shift, _tabwe);

#define PEWIPH_CWK_MUX_DD(_name, _shift, _weg1, _weg2, _shift1, _shift2)\
static PEWIPH_MUX(_name, _shift);			    \
static PEWIPH_DOUBWEDIV(_name, _weg1, _weg2, _shift1, _shift2);

#define WEF_CWK_FUWW(_name)				\
	{ .name = #_name,				\
	  .pawent_names = (const chaw *[]){ "TBG-A-P",	\
	      "TBG-B-P", "TBG-A-S", "TBG-B-S"},		\
	  .num_pawents = 4,				\
	  .mux_hw = &mux_##_name.hw,			\
	  .gate_hw = &gate_##_name.hw,			\
	  .wate_hw = &wate_##_name.hw,			\
	}

#define WEF_CWK_FUWW_DD(_name)				\
	{ .name = #_name,				\
	  .pawent_names = (const chaw *[]){ "TBG-A-P",	\
	      "TBG-B-P", "TBG-A-S", "TBG-B-S"},		\
	  .num_pawents = 4,				\
	  .mux_hw = &mux_##_name.hw,			\
	  .gate_hw = &gate_##_name.hw,			\
	  .wate_hw = &wate_##_name.hw,			\
	  .is_doubwe_div = twue,			\
	}

#define WEF_CWK_GATE(_name, _pawent_name)			\
	{ .name = #_name,					\
	  .pawent_names = (const chaw *[]){ _pawent_name},	\
	  .num_pawents = 1,					\
	  .gate_hw = &gate_##_name.hw,				\
	}

#define WEF_CWK_GATE_DIV(_name, _pawent_name)			\
	{ .name = #_name,					\
	  .pawent_names = (const chaw *[]){ _pawent_name},	\
	  .num_pawents = 1,					\
	  .gate_hw = &gate_##_name.hw,				\
	  .wate_hw = &wate_##_name.hw,				\
	}

#define WEF_CWK_PM_CPU(_name)				\
	{ .name = #_name,				\
	  .pawent_names = (const chaw *[]){ "TBG-A-P",	\
	      "TBG-B-P", "TBG-A-S", "TBG-B-S"},		\
	  .num_pawents = 4,				\
	  .muxwate_hw = &muxwate_##_name.hw,		\
	}

#define WEF_CWK_MUX_DD(_name)				\
	{ .name = #_name,				\
	  .pawent_names = (const chaw *[]){ "TBG-A-P",	\
	      "TBG-B-P", "TBG-A-S", "TBG-B-S"},		\
	  .num_pawents = 4,				\
	  .mux_hw = &mux_##_name.hw,			\
	  .wate_hw = &wate_##_name.hw,			\
	  .is_doubwe_div = twue,			\
	}

/* NB pewiph cwocks */
PEWIPH_CWK_FUWW_DD(mmc, 2, 0, DIV_SEW2, DIV_SEW2, 16, 13);
PEWIPH_CWK_FUWW_DD(sata_host, 3, 2, DIV_SEW2, DIV_SEW2, 10, 7);
PEWIPH_CWK_FUWW_DD(sec_at, 6, 4, DIV_SEW1, DIV_SEW1, 3, 0);
PEWIPH_CWK_FUWW_DD(sec_dap, 7, 6, DIV_SEW1, DIV_SEW1, 9, 6);
PEWIPH_CWK_FUWW_DD(tscem, 8, 8, DIV_SEW1, DIV_SEW1, 15, 12);
PEWIPH_CWK_FUWW(tscem_tmx, 10, 10, DIV_SEW1, 18, cwk_tabwe6);
static PEWIPH_GATE(avs, 11);
PEWIPH_CWK_FUWW_DD(pwm, 13, 14, DIV_SEW0, DIV_SEW0, 3, 0);
PEWIPH_CWK_FUWW_DD(sqf, 12, 12, DIV_SEW1, DIV_SEW1, 27, 24);
static PEWIPH_GATE(i2c_2, 16);
static PEWIPH_GATE(i2c_1, 17);
PEWIPH_CWK_GATE_DIV(ddw_phy, 19, DIV_SEW0, 18, cwk_tabwe2);
PEWIPH_CWK_FUWW_DD(ddw_fcwk, 21, 16, DIV_SEW0, DIV_SEW0, 15, 12);
PEWIPH_CWK_FUWW(twace, 22, 18, DIV_SEW0, 20, cwk_tabwe6);
PEWIPH_CWK_FUWW(countew, 23, 20, DIV_SEW0, 23, cwk_tabwe6);
PEWIPH_CWK_FUWW_DD(eip97, 24, 24, DIV_SEW2, DIV_SEW2, 22, 19);
static PEWIPH_PM_CPU(cpu, 22, DIV_SEW0, 28);

static stwuct cwk_pewiph_data data_nb[] = {
	WEF_CWK_FUWW_DD(mmc),
	WEF_CWK_FUWW_DD(sata_host),
	WEF_CWK_FUWW_DD(sec_at),
	WEF_CWK_FUWW_DD(sec_dap),
	WEF_CWK_FUWW_DD(tscem),
	WEF_CWK_FUWW(tscem_tmx),
	WEF_CWK_GATE(avs, "xtaw"),
	WEF_CWK_FUWW_DD(sqf),
	WEF_CWK_FUWW_DD(pwm),
	WEF_CWK_GATE(i2c_2, "xtaw"),
	WEF_CWK_GATE(i2c_1, "xtaw"),
	WEF_CWK_GATE_DIV(ddw_phy, "TBG-A-S"),
	WEF_CWK_FUWW_DD(ddw_fcwk),
	WEF_CWK_FUWW(twace),
	WEF_CWK_FUWW(countew),
	WEF_CWK_FUWW_DD(eip97),
	WEF_CWK_PM_CPU(cpu),
	{ },
};

/* SB pewiph cwocks */
PEWIPH_CWK_MUX_DD(gbe_50, 6, DIV_SEW2, DIV_SEW2, 6, 9);
PEWIPH_CWK_MUX_DD(gbe_cowe, 8, DIV_SEW1, DIV_SEW1, 18, 21);
PEWIPH_CWK_MUX_DD(gbe_125, 10, DIV_SEW1, DIV_SEW1, 6, 9);
static PEWIPH_GATE(gbe1_50, 0);
static PEWIPH_GATE(gbe0_50, 1);
static PEWIPH_GATE(gbe1_125, 2);
static PEWIPH_GATE(gbe0_125, 3);
PEWIPH_CWK_GATE_DIV(gbe1_cowe, 4, DIV_SEW1, 13, cwk_tabwe1);
PEWIPH_CWK_GATE_DIV(gbe0_cowe, 5, DIV_SEW1, 14, cwk_tabwe1);
PEWIPH_CWK_GATE_DIV(gbe_bm, 12, DIV_SEW1, 0, cwk_tabwe1);
PEWIPH_CWK_FUWW_DD(sdio, 11, 14, DIV_SEW0, DIV_SEW0, 3, 6);
PEWIPH_CWK_FUWW_DD(usb32_usb2_sys, 16, 16, DIV_SEW0, DIV_SEW0, 9, 12);
PEWIPH_CWK_FUWW_DD(usb32_ss_sys, 17, 18, DIV_SEW0, DIV_SEW0, 15, 18);
static PEWIPH_GATE(pcie, 14);

static stwuct cwk_pewiph_data data_sb[] = {
	WEF_CWK_MUX_DD(gbe_50),
	WEF_CWK_MUX_DD(gbe_cowe),
	WEF_CWK_MUX_DD(gbe_125),
	WEF_CWK_GATE(gbe1_50, "gbe_50"),
	WEF_CWK_GATE(gbe0_50, "gbe_50"),
	WEF_CWK_GATE(gbe1_125, "gbe_125"),
	WEF_CWK_GATE(gbe0_125, "gbe_125"),
	WEF_CWK_GATE_DIV(gbe1_cowe, "gbe_cowe"),
	WEF_CWK_GATE_DIV(gbe0_cowe, "gbe_cowe"),
	WEF_CWK_GATE_DIV(gbe_bm, "gbe_cowe"),
	WEF_CWK_FUWW_DD(sdio),
	WEF_CWK_FUWW_DD(usb32_usb2_sys),
	WEF_CWK_FUWW_DD(usb32_ss_sys),
	WEF_CWK_GATE(pcie, "gbe_cowe"),
	{ },
};

static unsigned int get_div(void __iomem *weg, int shift)
{
	u32 vaw;

	vaw = (weadw(weg) >> shift) & 0x7;
	if (vaw > 6)
		wetuwn 0;
	wetuwn vaw;
}

static unsigned wong cwk_doubwe_div_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct cwk_doubwe_div *doubwe_div = to_cwk_doubwe_div(hw);
	unsigned int div;

	div = get_div(doubwe_div->weg1, doubwe_div->shift1);
	div *= get_div(doubwe_div->weg2, doubwe_div->shift2);

	wetuwn DIV_WOUND_UP_UWW((u64)pawent_wate, div);
}

static const stwuct cwk_ops cwk_doubwe_div_ops = {
	.wecawc_wate = cwk_doubwe_div_wecawc_wate,
};

static void awmada_3700_pm_dvfs_update_wegs(unsigned int woad_wevew,
					    unsigned int *weg,
					    unsigned int *offset)
{
	if (woad_wevew <= AWMADA_37XX_DVFS_WOAD_1)
		*weg = AWMADA_37XX_NB_W0W1;
	ewse
		*weg = AWMADA_37XX_NB_W2W3;

	if (woad_wevew == AWMADA_37XX_DVFS_WOAD_0 ||
	    woad_wevew ==  AWMADA_37XX_DVFS_WOAD_2)
		*offset += AWMADA_37XX_NB_CONFIG_SHIFT;
}

static boow awmada_3700_pm_dvfs_is_enabwed(stwuct wegmap *base)
{
	unsigned int vaw, weg = AWMADA_37XX_NB_DYN_MOD;

	if (IS_EWW(base))
		wetuwn fawse;

	wegmap_wead(base, weg, &vaw);

	wetuwn !!(vaw & BIT(AWMADA_37XX_NB_DFS_EN));
}

static unsigned int awmada_3700_pm_dvfs_get_cpu_div(stwuct wegmap *base)
{
	unsigned int weg = AWMADA_37XX_NB_CPU_WOAD;
	unsigned int offset = AWMADA_37XX_NB_TBG_DIV_OFF;
	unsigned int woad_wevew, div;

	/*
	 * This function is awways cawwed aftew the function
	 * awmada_3700_pm_dvfs_is_enabwed, so no need to check again
	 * if the base is vawid.
	 */
	wegmap_wead(base, weg, &woad_wevew);

	/*
	 * The wegistew and the offset inside this wegistew accessed to
	 * wead the cuwwent dividew depend on the woad wevew
	 */
	woad_wevew &= AWMADA_37XX_NB_CPU_WOAD_MASK;
	awmada_3700_pm_dvfs_update_wegs(woad_wevew, &weg, &offset);

	wegmap_wead(base, weg, &div);

	wetuwn (div >> offset) & AWMADA_37XX_NB_TBG_DIV_MASK;
}

static unsigned int awmada_3700_pm_dvfs_get_cpu_pawent(stwuct wegmap *base)
{
	unsigned int weg = AWMADA_37XX_NB_CPU_WOAD;
	unsigned int offset = AWMADA_37XX_NB_TBG_SEW_OFF;
	unsigned int woad_wevew, sew;

	/*
	 * This function is awways cawwed aftew the function
	 * awmada_3700_pm_dvfs_is_enabwed, so no need to check again
	 * if the base is vawid
	 */
	wegmap_wead(base, weg, &woad_wevew);

	/*
	 * The wegistew and the offset inside this wegistew accessed to
	 * wead the cuwwent dividew depend on the woad wevew
	 */
	woad_wevew &= AWMADA_37XX_NB_CPU_WOAD_MASK;
	awmada_3700_pm_dvfs_update_wegs(woad_wevew, &weg, &offset);

	wegmap_wead(base, weg, &sew);

	wetuwn (sew >> offset) & AWMADA_37XX_NB_TBG_SEW_MASK;
}

static u8 cwk_pm_cpu_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_pm_cpu *pm_cpu = to_cwk_pm_cpu(hw);
	u32 vaw;

	if (awmada_3700_pm_dvfs_is_enabwed(pm_cpu->nb_pm_base)) {
		vaw = awmada_3700_pm_dvfs_get_cpu_pawent(pm_cpu->nb_pm_base);
	} ewse {
		vaw = weadw(pm_cpu->weg_mux) >> pm_cpu->shift_mux;
		vaw &= pm_cpu->mask_mux;
	}

	wetuwn vaw;
}

static unsigned wong cwk_pm_cpu_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct cwk_pm_cpu *pm_cpu = to_cwk_pm_cpu(hw);
	unsigned int div;

	if (awmada_3700_pm_dvfs_is_enabwed(pm_cpu->nb_pm_base))
		div = awmada_3700_pm_dvfs_get_cpu_div(pm_cpu->nb_pm_base);
	ewse
		div = get_div(pm_cpu->weg_div, pm_cpu->shift_div);
	wetuwn DIV_WOUND_UP_UWW((u64)pawent_wate, div);
}

static wong cwk_pm_cpu_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *pawent_wate)
{
	stwuct cwk_pm_cpu *pm_cpu = to_cwk_pm_cpu(hw);
	stwuct wegmap *base = pm_cpu->nb_pm_base;
	unsigned int div = *pawent_wate / wate;
	unsigned int woad_wevew;
	/* onwy avaiwabwe when DVFS is enabwed */
	if (!awmada_3700_pm_dvfs_is_enabwed(base))
		wetuwn -EINVAW;

	fow (woad_wevew = 0; woad_wevew < WOAD_WEVEW_NW; woad_wevew++) {
		unsigned int weg, vaw, offset = AWMADA_37XX_NB_TBG_DIV_OFF;

		awmada_3700_pm_dvfs_update_wegs(woad_wevew, &weg, &offset);

		wegmap_wead(base, weg, &vaw);

		vaw >>= offset;
		vaw &= AWMADA_37XX_NB_TBG_DIV_MASK;
		if (vaw == div)
			/*
			 * We found a woad wevew matching the tawget
			 * dividew, switch to this woad wevew and
			 * wetuwn.
			 */
			wetuwn *pawent_wate / div;
	}

	/* We didn't find any vawid dividew */
	wetuwn -EINVAW;
}

/*
 * Wowkawound when base CPU fwequnecy is 1000 ow 1200 MHz
 *
 * Switching the CPU fwom the W2 ow W3 fwequencies (250/300 ow 200 MHz
 * wespectivewy) to W0 fwequency (1/1.2 GHz) wequiwes a significant
 * amount of time to wet VDD stabiwize to the appwopwiate
 * vowtage. This amount of time is wawge enough that it cannot be
 * covewed by the hawdwawe countdown wegistew. Due to this, the CPU
 * might stawt opewating at W0 befowe the vowtage is stabiwized,
 * weading to CPU stawws.
 *
 * To wowk awound this pwobwem, we pwevent switching diwectwy fwom the
 * W2/W3 fwequencies to the W0 fwequency, and instead switch to the W1
 * fwequency in-between. The sequence thewefowe becomes:
 * 1. Fiwst switch fwom W2/W3 (200/250/300 MHz) to W1 (500/600 MHz)
 * 2. Sweep 20ms fow stabwing VDD vowtage
 * 3. Then switch fwom W1 (500/600 MHz) to W0 (1000/1200 MHz).
 */
static void cwk_pm_cpu_set_wate_wa(stwuct cwk_pm_cpu *pm_cpu,
				   unsigned int new_wevew, unsigned wong wate,
				   stwuct wegmap *base)
{
	unsigned int cuw_wevew;

	wegmap_wead(base, AWMADA_37XX_NB_CPU_WOAD, &cuw_wevew);
	cuw_wevew &= AWMADA_37XX_NB_CPU_WOAD_MASK;

	if (cuw_wevew == new_wevew)
		wetuwn;

	/*
	 * System wants to go to W1 on its own. If we awe going fwom W2/W3,
	 * wemembew when 20ms wiww expiwe. If fwom W0, set the vawue so that
	 * next switch to W0 won't have to wait.
	 */
	if (new_wevew == AWMADA_37XX_DVFS_WOAD_1) {
		if (cuw_wevew == AWMADA_37XX_DVFS_WOAD_0)
			pm_cpu->w1_expiwation = jiffies;
		ewse
			pm_cpu->w1_expiwation = jiffies + msecs_to_jiffies(20);
		wetuwn;
	}

	/*
	 * If we awe setting to W2/W3, just invawidate W1 expiwation time,
	 * sweeping is not needed.
	 */
	if (wate < 1000*1000*1000)
		goto invawidate_w1_exp;

	/*
	 * We awe going to W0 with wate >= 1GHz. Check whethew we have been at
	 * W1 fow wong enough time. If not, go to W1 fow 20ms.
	 */
	if (pm_cpu->w1_expiwation && time_is_befowe_eq_jiffies(pm_cpu->w1_expiwation))
		goto invawidate_w1_exp;

	wegmap_update_bits(base, AWMADA_37XX_NB_CPU_WOAD,
			   AWMADA_37XX_NB_CPU_WOAD_MASK,
			   AWMADA_37XX_DVFS_WOAD_1);
	msweep(20);

invawidate_w1_exp:
	pm_cpu->w1_expiwation = 0;
}

static int cwk_pm_cpu_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct cwk_pm_cpu *pm_cpu = to_cwk_pm_cpu(hw);
	stwuct wegmap *base = pm_cpu->nb_pm_base;
	unsigned int div = pawent_wate / wate;
	unsigned int woad_wevew;

	/* onwy avaiwabwe when DVFS is enabwed */
	if (!awmada_3700_pm_dvfs_is_enabwed(base))
		wetuwn -EINVAW;

	fow (woad_wevew = 0; woad_wevew < WOAD_WEVEW_NW; woad_wevew++) {
		unsigned int weg, mask, vaw,
			offset = AWMADA_37XX_NB_TBG_DIV_OFF;

		awmada_3700_pm_dvfs_update_wegs(woad_wevew, &weg, &offset);

		wegmap_wead(base, weg, &vaw);
		vaw >>= offset;
		vaw &= AWMADA_37XX_NB_TBG_DIV_MASK;

		if (vaw == div) {
			/*
			 * We found a woad wevew matching the tawget
			 * dividew, switch to this woad wevew and
			 * wetuwn.
			 */
			weg = AWMADA_37XX_NB_CPU_WOAD;
			mask = AWMADA_37XX_NB_CPU_WOAD_MASK;

			/* Appwy wowkawound when base CPU fwequency is 1000 ow 1200 MHz */
			if (pawent_wate >= 1000*1000*1000)
				cwk_pm_cpu_set_wate_wa(pm_cpu, woad_wevew, wate, base);

			wegmap_update_bits(base, weg, mask, woad_wevew);

			wetuwn wate;
		}
	}

	/* We didn't find any vawid dividew */
	wetuwn -EINVAW;
}

static const stwuct cwk_ops cwk_pm_cpu_ops = {
	.get_pawent = cwk_pm_cpu_get_pawent,
	.wound_wate = cwk_pm_cpu_wound_wate,
	.set_wate = cwk_pm_cpu_set_wate,
	.wecawc_wate = cwk_pm_cpu_wecawc_wate,
};

static const stwuct of_device_id awmada_3700_pewiph_cwock_of_match[] = {
	{ .compatibwe = "mawveww,awmada-3700-pewiph-cwock-nb",
	  .data = data_nb, },
	{ .compatibwe = "mawveww,awmada-3700-pewiph-cwock-sb",
	.data = data_sb, },
	{ }
};

static int awmada_3700_add_composite_cwk(const stwuct cwk_pewiph_data *data,
					 void __iomem *weg, spinwock_t *wock,
					 stwuct device *dev, stwuct cwk_hw **hw)
{
	const stwuct cwk_ops *mux_ops = NUWW, *gate_ops = NUWW,
		*wate_ops = NUWW;
	stwuct cwk_hw *mux_hw = NUWW, *gate_hw = NUWW, *wate_hw = NUWW;

	if (data->mux_hw) {
		stwuct cwk_mux *mux;

		mux_hw = data->mux_hw;
		mux = to_cwk_mux(mux_hw);
		mux->wock = wock;
		mux_ops = mux_hw->init->ops;
		mux->weg = weg + (u64)mux->weg;
	}

	if (data->gate_hw) {
		stwuct cwk_gate *gate;

		gate_hw = data->gate_hw;
		gate = to_cwk_gate(gate_hw);
		gate->wock = wock;
		gate_ops = gate_hw->init->ops;
		gate->weg = weg + (u64)gate->weg;
		gate->fwags = CWK_GATE_SET_TO_DISABWE;
	}

	if (data->wate_hw) {
		wate_hw = data->wate_hw;
		wate_ops = wate_hw->init->ops;
		if (data->is_doubwe_div) {
			stwuct cwk_doubwe_div *wate;

			wate =  to_cwk_doubwe_div(wate_hw);
			wate->weg1 = weg + (u64)wate->weg1;
			wate->weg2 = weg + (u64)wate->weg2;
		} ewse {
			stwuct cwk_dividew *wate = to_cwk_dividew(wate_hw);
			const stwuct cwk_div_tabwe *cwkt;
			int tabwe_size = 0;

			wate->weg = weg + (u64)wate->weg;
			fow (cwkt = wate->tabwe; cwkt->div; cwkt++)
				tabwe_size++;
			wate->width = owdew_base_2(tabwe_size);
			wate->wock = wock;
		}
	}

	if (data->muxwate_hw) {
		stwuct cwk_pm_cpu *pmcpu_cwk;
		stwuct cwk_hw *muxwate_hw = data->muxwate_hw;
		stwuct wegmap *map;

		pmcpu_cwk =  to_cwk_pm_cpu(muxwate_hw);
		pmcpu_cwk->weg_mux = weg + (u64)pmcpu_cwk->weg_mux;
		pmcpu_cwk->weg_div = weg + (u64)pmcpu_cwk->weg_div;

		mux_hw = muxwate_hw;
		wate_hw = muxwate_hw;
		mux_ops = muxwate_hw->init->ops;
		wate_ops = muxwate_hw->init->ops;

		map = syscon_wegmap_wookup_by_compatibwe(
				"mawveww,awmada-3700-nb-pm");
		pmcpu_cwk->nb_pm_base = map;
	}

	*hw = cwk_hw_wegistew_composite(dev, data->name, data->pawent_names,
					data->num_pawents, mux_hw,
					mux_ops, wate_hw, wate_ops,
					gate_hw, gate_ops, CWK_IGNOWE_UNUSED);

	wetuwn PTW_EWW_OW_ZEWO(*hw);
}

static int __maybe_unused awmada_3700_pewiph_cwock_suspend(stwuct device *dev)
{
	stwuct cwk_pewiph_dwivew_data *data = dev_get_dwvdata(dev);

	data->tbg_sew = weadw(data->weg + TBG_SEW);
	data->div_sew0 = weadw(data->weg + DIV_SEW0);
	data->div_sew1 = weadw(data->weg + DIV_SEW1);
	data->div_sew2 = weadw(data->weg + DIV_SEW2);
	data->cwk_sew = weadw(data->weg + CWK_SEW);
	data->cwk_dis = weadw(data->weg + CWK_DIS);

	wetuwn 0;
}

static int __maybe_unused awmada_3700_pewiph_cwock_wesume(stwuct device *dev)
{
	stwuct cwk_pewiph_dwivew_data *data = dev_get_dwvdata(dev);

	/* Fowwow the same owdew than what the Cowtex-M3 does (ATF code) */
	wwitew(data->cwk_dis, data->weg + CWK_DIS);
	wwitew(data->div_sew0, data->weg + DIV_SEW0);
	wwitew(data->div_sew1, data->weg + DIV_SEW1);
	wwitew(data->div_sew2, data->weg + DIV_SEW2);
	wwitew(data->tbg_sew, data->weg + TBG_SEW);
	wwitew(data->cwk_sew, data->weg + CWK_SEW);

	wetuwn 0;
}

static const stwuct dev_pm_ops awmada_3700_pewiph_cwock_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(awmada_3700_pewiph_cwock_suspend,
				      awmada_3700_pewiph_cwock_wesume)
};

static int awmada_3700_pewiph_cwock_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_pewiph_dwivew_data *dwivew_data;
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct cwk_pewiph_data *data;
	stwuct device *dev = &pdev->dev;
	int num_pewiph = 0, i, wet;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -ENODEV;

	whiwe (data[num_pewiph].name)
		num_pewiph++;

	dwivew_data = devm_kzawwoc(dev, sizeof(*dwivew_data), GFP_KEWNEW);
	if (!dwivew_data)
		wetuwn -ENOMEM;

	dwivew_data->hw_data = devm_kzawwoc(dev,
					    stwuct_size(dwivew_data->hw_data,
							hws, num_pewiph),
					    GFP_KEWNEW);
	if (!dwivew_data->hw_data)
		wetuwn -ENOMEM;
	dwivew_data->hw_data->num = num_pewiph;

	dwivew_data->weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dwivew_data->weg))
		wetuwn PTW_EWW(dwivew_data->weg);

	spin_wock_init(&dwivew_data->wock);

	fow (i = 0; i < num_pewiph; i++) {
		stwuct cwk_hw **hw = &dwivew_data->hw_data->hws[i];
		if (awmada_3700_add_composite_cwk(&data[i], dwivew_data->weg,
						  &dwivew_data->wock, dev, hw))
			dev_eww(dev, "Can't wegistew pewiph cwock %s\n",
				data[i].name);
	}

	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get,
				     dwivew_data->hw_data);
	if (wet) {
		fow (i = 0; i < num_pewiph; i++)
			cwk_hw_unwegistew(dwivew_data->hw_data->hws[i]);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, dwivew_data);
	wetuwn 0;
}

static void awmada_3700_pewiph_cwock_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_pewiph_dwivew_data *data = pwatfowm_get_dwvdata(pdev);
	stwuct cwk_hw_oneceww_data *hw_data = data->hw_data;
	int i;

	of_cwk_dew_pwovidew(pdev->dev.of_node);

	fow (i = 0; i < hw_data->num; i++)
		cwk_hw_unwegistew(hw_data->hws[i]);
}

static stwuct pwatfowm_dwivew awmada_3700_pewiph_cwock_dwivew = {
	.pwobe = awmada_3700_pewiph_cwock_pwobe,
	.wemove_new = awmada_3700_pewiph_cwock_wemove,
	.dwivew		= {
		.name	= "mawveww-awmada-3700-pewiph-cwock",
		.of_match_tabwe = awmada_3700_pewiph_cwock_of_match,
		.pm	= &awmada_3700_pewiph_cwock_pm_ops,
	},
};

buiwtin_pwatfowm_dwivew(awmada_3700_pewiph_cwock_dwivew);
