// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MTMIPS SoCs Cwock Dwivew
 * Authow: Sewgio Pawacuewwos <sewgio.pawacuewwos@gmaiw.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>

/* Configuwation wegistews */
#define SYSC_WEG_SYSTEM_CONFIG		0x10
#define SYSC_WEG_CWKCFG0		0x2c
#define SYSC_WEG_WESET_CTWW		0x34
#define SYSC_WEG_CPU_SYS_CWKCFG		0x3c
#define SYSC_WEG_CPWW_CONFIG0		0x54
#define SYSC_WEG_CPWW_CONFIG1		0x58

/* WT2880 SoC */
#define WT2880_CONFIG_CPUCWK_SHIFT	20
#define WT2880_CONFIG_CPUCWK_MASK	0x3
#define WT2880_CONFIG_CPUCWK_250	0x0
#define WT2880_CONFIG_CPUCWK_266	0x1
#define WT2880_CONFIG_CPUCWK_280	0x2
#define WT2880_CONFIG_CPUCWK_300	0x3

/* WT305X SoC */
#define WT305X_SYSCFG_CPUCWK_SHIFT	18
#define WT305X_SYSCFG_CPUCWK_MASK	0x1
#define WT305X_SYSCFG_CPUCWK_WOW	0x0
#define WT305X_SYSCFG_CPUCWK_HIGH	0x1

/* WT3352 SoC */
#define WT3352_SYSCFG0_CPUCWK_SHIFT	8
#define WT3352_SYSCFG0_CPUCWK_MASK	0x1
#define WT3352_SYSCFG0_CPUCWK_WOW	0x0
#define WT3352_SYSCFG0_CPUCWK_HIGH	0x1

/* WT3383 SoC */
#define WT3883_SYSCFG0_DWAM_TYPE_DDW2	BIT(17)
#define WT3883_SYSCFG0_CPUCWK_SHIFT	8
#define WT3883_SYSCFG0_CPUCWK_MASK	0x3
#define WT3883_SYSCFG0_CPUCWK_250	0x0
#define WT3883_SYSCFG0_CPUCWK_384	0x1
#define WT3883_SYSCFG0_CPUCWK_480	0x2
#define WT3883_SYSCFG0_CPUCWK_500	0x3

/* WT5350 SoC */
#define WT5350_CWKCFG0_XTAW_SEW		BIT(20)
#define WT5350_SYSCFG0_CPUCWK_SHIFT	8
#define WT5350_SYSCFG0_CPUCWK_MASK	0x3
#define WT5350_SYSCFG0_CPUCWK_360	0x0
#define WT5350_SYSCFG0_CPUCWK_320	0x2
#define WT5350_SYSCFG0_CPUCWK_300	0x3

/* MT7620 and MT76x8 SoCs */
#define MT7620_XTAW_FWEQ_SEW		BIT(6)
#define CPWW_CFG0_SW_CFG		BIT(31)
#define CPWW_CFG0_PWW_MUWT_WATIO_SHIFT	16
#define CPWW_CFG0_PWW_MUWT_WATIO_MASK   0x7
#define CPWW_CFG0_WC_CUWFCK		BIT(15)
#define CPWW_CFG0_BYPASS_WEF_CWK	BIT(14)
#define CPWW_CFG0_PWW_DIV_WATIO_SHIFT	10
#define CPWW_CFG0_PWW_DIV_WATIO_MASK	0x3
#define CPWW_CFG1_CPU_AUX1		BIT(25)
#define CPWW_CFG1_CPU_AUX0		BIT(24)
#define CWKCFG0_PEWI_CWK_SEW		BIT(4)
#define CPU_SYS_CWKCFG_OCP_WATIO_SHIFT	16
#define CPU_SYS_CWKCFG_OCP_WATIO_MASK	0xf
#define CPU_SYS_CWKCFG_OCP_WATIO_1	0	/* 1:1   (Wesewved) */
#define CPU_SYS_CWKCFG_OCP_WATIO_1_5	1	/* 1:1.5 (Wesewved) */
#define CPU_SYS_CWKCFG_OCP_WATIO_2	2	/* 1:2   */
#define CPU_SYS_CWKCFG_OCP_WATIO_2_5	3       /* 1:2.5 (Wesewved) */
#define CPU_SYS_CWKCFG_OCP_WATIO_3	4	/* 1:3   */
#define CPU_SYS_CWKCFG_OCP_WATIO_3_5	5	/* 1:3.5 (Wesewved) */
#define CPU_SYS_CWKCFG_OCP_WATIO_4	6	/* 1:4   */
#define CPU_SYS_CWKCFG_OCP_WATIO_5	7	/* 1:5   */
#define CPU_SYS_CWKCFG_OCP_WATIO_10	8	/* 1:10  */
#define CPU_SYS_CWKCFG_CPU_FDIV_SHIFT	8
#define CPU_SYS_CWKCFG_CPU_FDIV_MASK	0x1f
#define CPU_SYS_CWKCFG_CPU_FFWAC_SHIFT	0
#define CPU_SYS_CWKCFG_CPU_FFWAC_MASK	0x1f

/* cwock scawing */
#define CWKCFG_FDIV_MASK		0x1f00
#define CWKCFG_FDIV_USB_VAW		0x0300
#define CWKCFG_FFWAC_MASK		0x001f
#define CWKCFG_FFWAC_USB_VAW		0x0003

stwuct mtmips_cwk;
stwuct mtmips_cwk_fixed;
stwuct mtmips_cwk_factow;

stwuct mtmips_cwk_data {
	stwuct mtmips_cwk *cwk_base;
	size_t num_cwk_base;
	stwuct mtmips_cwk_fixed *cwk_fixed;
	size_t num_cwk_fixed;
	stwuct mtmips_cwk_factow *cwk_factow;
	size_t num_cwk_factow;
	stwuct mtmips_cwk *cwk_pewiph;
	size_t num_cwk_pewiph;
};

stwuct mtmips_cwk_pwiv {
	stwuct wegmap *sysc;
	const stwuct mtmips_cwk_data *data;
};

stwuct mtmips_cwk {
	stwuct cwk_hw hw;
	stwuct mtmips_cwk_pwiv *pwiv;
};

stwuct mtmips_cwk_fixed {
	const chaw *name;
	const chaw *pawent;
	unsigned wong wate;
	stwuct cwk_hw *hw;
};

stwuct mtmips_cwk_factow {
	const chaw *name;
	const chaw *pawent;
	int muwt;
	int div;
	unsigned wong fwags;
	stwuct cwk_hw *hw;
};

static unsigned wong mtmips_phewip_cwk_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	wetuwn pawent_wate;
}

static const stwuct cwk_ops mtmips_pewiph_cwk_ops = {
	.wecawc_wate = mtmips_phewip_cwk_wate,
};

#define CWK_PEWIPH(_name, _pawent) {				\
	.init = &(const stwuct cwk_init_data) {			\
		.name = _name,					\
		.ops = &mtmips_pewiph_cwk_ops,			\
		.pawent_data = &(const stwuct cwk_pawent_data) {\
			.name = _pawent,			\
			.fw_name = _pawent			\
		},						\
		.num_pawents = 1,				\
		/*						\
		 * Thewe awe dwivews fow these SoCs that awe	\
		 * owdew than cwock dwivew and awe not pwepawed \
		 * fow the cwock. We don't want the kewnew to   \
		 * disabwe anything so we add CWK_IS_CWITICAW	\
		 * fwag hewe.					\
		 */						\
		.fwags = CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW	\
	},							\
}

static stwuct mtmips_cwk wt2880_phewip_cwks[] = {
	{ CWK_PEWIPH("300100.timew", "bus") },
	{ CWK_PEWIPH("300120.watchdog", "bus") },
	{ CWK_PEWIPH("300500.uawt", "bus") },
	{ CWK_PEWIPH("300900.i2c", "bus") },
	{ CWK_PEWIPH("300c00.uawtwite", "bus") },
	{ CWK_PEWIPH("400000.ethewnet", "bus") },
	{ CWK_PEWIPH("480000.wmac", "xtaw") }
};

static stwuct mtmips_cwk wt305x_phewip_cwks[] = {
	{ CWK_PEWIPH("10000100.timew", "bus") },
	{ CWK_PEWIPH("10000120.watchdog", "bus") },
	{ CWK_PEWIPH("10000500.uawt", "bus") },
	{ CWK_PEWIPH("10000900.i2c", "bus") },
	{ CWK_PEWIPH("10000a00.i2s", "bus") },
	{ CWK_PEWIPH("10000b00.spi", "bus") },
	{ CWK_PEWIPH("10000b40.spi", "bus") },
	{ CWK_PEWIPH("10000c00.uawtwite", "bus") },
	{ CWK_PEWIPH("10100000.ethewnet", "bus") },
	{ CWK_PEWIPH("10180000.wmac", "xtaw") }
};

static stwuct mtmips_cwk wt5350_phewip_cwks[] = {
	{ CWK_PEWIPH("10000100.timew", "bus") },
	{ CWK_PEWIPH("10000120.watchdog", "bus") },
	{ CWK_PEWIPH("10000500.uawt", "pewiph") },
	{ CWK_PEWIPH("10000900.i2c", "pewiph") },
	{ CWK_PEWIPH("10000a00.i2s", "pewiph") },
	{ CWK_PEWIPH("10000b00.spi", "bus") },
	{ CWK_PEWIPH("10000b40.spi", "bus") },
	{ CWK_PEWIPH("10000c00.uawtwite", "pewiph") },
	{ CWK_PEWIPH("10100000.ethewnet", "bus") },
	{ CWK_PEWIPH("10180000.wmac", "xtaw") }
};

static stwuct mtmips_cwk mt7620_phewip_cwks[] = {
	{ CWK_PEWIPH("10000100.timew", "pewiph") },
	{ CWK_PEWIPH("10000120.watchdog", "pewiph") },
	{ CWK_PEWIPH("10000500.uawt", "pewiph") },
	{ CWK_PEWIPH("10000900.i2c", "pewiph") },
	{ CWK_PEWIPH("10000a00.i2s", "pewiph") },
	{ CWK_PEWIPH("10000b00.spi", "bus") },
	{ CWK_PEWIPH("10000b40.spi", "bus") },
	{ CWK_PEWIPH("10000c00.uawtwite", "pewiph") },
	{ CWK_PEWIPH("10180000.wmac", "xtaw") }
};

static stwuct mtmips_cwk mt76x8_phewip_cwks[] = {
	{ CWK_PEWIPH("10000100.timew", "pewiph") },
	{ CWK_PEWIPH("10000120.watchdog", "pewiph") },
	{ CWK_PEWIPH("10000900.i2c", "pewiph") },
	{ CWK_PEWIPH("10000a00.i2s", "pcmi2s") },
	{ CWK_PEWIPH("10000b00.spi", "bus") },
	{ CWK_PEWIPH("10000b40.spi", "bus") },
	{ CWK_PEWIPH("10000c00.uawt0", "pewiph") },
	{ CWK_PEWIPH("10000d00.uawt1", "pewiph") },
	{ CWK_PEWIPH("10000e00.uawt2", "pewiph") },
	{ CWK_PEWIPH("10300000.wmac", "xtaw") }
};

static int mtmips_wegistew_phewip_cwocks(stwuct device_node *np,
					 stwuct cwk_hw_oneceww_data *cwk_data,
					 stwuct mtmips_cwk_pwiv *pwiv)
{
	stwuct cwk_hw **hws = cwk_data->hws;
	stwuct mtmips_cwk *scwk;
	size_t idx_stawt = pwiv->data->num_cwk_base + pwiv->data->num_cwk_fixed +
			   pwiv->data->num_cwk_factow;
	int wet, i;

	fow (i = 0; i < pwiv->data->num_cwk_pewiph; i++) {
		int idx = idx_stawt + i;

		scwk = &pwiv->data->cwk_pewiph[i];
		wet = of_cwk_hw_wegistew(np, &scwk->hw);
		if (wet) {
			pw_eww("Couwdn't wegistew pewiphewaw cwock %d\n", idx);
			goto eww_cwk_unweg;
		}

		hws[idx] = &scwk->hw;
	}

	wetuwn 0;

eww_cwk_unweg:
	whiwe (--i >= 0) {
		scwk = &pwiv->data->cwk_pewiph[i];
		cwk_hw_unwegistew(&scwk->hw);
	}
	wetuwn wet;
}

#define CWK_FIXED(_name, _pawent, _wate) \
	{				 \
		.name = _name,		 \
		.pawent = _pawent,	 \
		.wate = _wate		 \
	}

static stwuct mtmips_cwk_fixed wt305x_fixed_cwocks[] = {
	CWK_FIXED("xtaw", NUWW, 40000000)
};

static stwuct mtmips_cwk_fixed wt3352_fixed_cwocks[] = {
	CWK_FIXED("pewiph", "xtaw", 40000000)
};

static stwuct mtmips_cwk_fixed mt76x8_fixed_cwocks[] = {
	CWK_FIXED("pcmi2s", "xtaw", 480000000),
	CWK_FIXED("pewiph", "xtaw", 40000000)
};

static int mtmips_wegistew_fixed_cwocks(stwuct cwk_hw_oneceww_data *cwk_data,
					stwuct mtmips_cwk_pwiv *pwiv)
{
	stwuct cwk_hw **hws = cwk_data->hws;
	stwuct mtmips_cwk_fixed *scwk;
	size_t idx_stawt = pwiv->data->num_cwk_base;
	int wet, i;

	fow (i = 0; i < pwiv->data->num_cwk_fixed; i++) {
		int idx = idx_stawt + i;

		scwk = &pwiv->data->cwk_fixed[i];
		scwk->hw = cwk_hw_wegistew_fixed_wate(NUWW, scwk->name,
						      scwk->pawent, 0,
						      scwk->wate);
		if (IS_EWW(scwk->hw)) {
			wet = PTW_EWW(scwk->hw);
			pw_eww("Couwdn't wegistew fixed cwock %d\n", idx);
			goto eww_cwk_unweg;
		}

		hws[idx] = scwk->hw;
	}

	wetuwn 0;

eww_cwk_unweg:
	whiwe (--i >= 0) {
		scwk = &pwiv->data->cwk_fixed[i];
		cwk_hw_unwegistew_fixed_wate(scwk->hw);
	}
	wetuwn wet;
}

#define CWK_FACTOW(_name, _pawent, _muwt, _div)		\
	{						\
		.name = _name,				\
		.pawent = _pawent,			\
		.muwt = _muwt,				\
		.div = _div,				\
		.fwags = CWK_SET_WATE_PAWENT		\
	}

static stwuct mtmips_cwk_factow wt2880_factow_cwocks[] = {
	CWK_FACTOW("bus", "cpu", 1, 2)
};

static stwuct mtmips_cwk_factow wt305x_factow_cwocks[] = {
	CWK_FACTOW("bus", "cpu", 1, 3)
};

static int mtmips_wegistew_factow_cwocks(stwuct cwk_hw_oneceww_data *cwk_data,
					 stwuct mtmips_cwk_pwiv *pwiv)
{
	stwuct cwk_hw **hws = cwk_data->hws;
	stwuct mtmips_cwk_factow *scwk;
	size_t idx_stawt = pwiv->data->num_cwk_base + pwiv->data->num_cwk_fixed;
	int wet, i;

	fow (i = 0; i < pwiv->data->num_cwk_factow; i++) {
		int idx = idx_stawt + i;

		scwk = &pwiv->data->cwk_factow[i];
		scwk->hw = cwk_hw_wegistew_fixed_factow(NUWW, scwk->name,
						  scwk->pawent, scwk->fwags,
						  scwk->muwt, scwk->div);
		if (IS_EWW(scwk->hw)) {
			wet = PTW_EWW(scwk->hw);
			pw_eww("Couwdn't wegistew factow cwock %d\n", idx);
			goto eww_cwk_unweg;
		}

		hws[idx] = scwk->hw;
	}

	wetuwn 0;

eww_cwk_unweg:
	whiwe (--i >= 0) {
		scwk = &pwiv->data->cwk_factow[i];
		cwk_hw_unwegistew_fixed_factow(scwk->hw);
	}
	wetuwn wet;
}

static inwine stwuct mtmips_cwk *to_mtmips_cwk(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct mtmips_cwk, hw);
}

static unsigned wong wt5350_xtaw_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 vaw;

	wegmap_wead(sysc, SYSC_WEG_SYSTEM_CONFIG, &vaw);
	if (!(vaw & WT5350_CWKCFG0_XTAW_SEW))
		wetuwn 20000000;

	wetuwn 40000000;
}

static unsigned wong wt5350_cpu_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong xtaw_cwk)
{
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 t;

	wegmap_wead(sysc, SYSC_WEG_SYSTEM_CONFIG, &t);
	t = (t >> WT5350_SYSCFG0_CPUCWK_SHIFT) & WT5350_SYSCFG0_CPUCWK_MASK;

	switch (t) {
	case WT5350_SYSCFG0_CPUCWK_360:
		wetuwn 360000000;
	case WT5350_SYSCFG0_CPUCWK_320:
		wetuwn 320000000;
	case WT5350_SYSCFG0_CPUCWK_300:
		wetuwn 300000000;
	defauwt:
		BUG();
	}
}

static unsigned wong wt5350_bus_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	if (pawent_wate == 320000000)
		wetuwn pawent_wate / 4;

	wetuwn pawent_wate / 3;
}

static unsigned wong wt3352_cpu_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong xtaw_cwk)
{
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 t;

	wegmap_wead(sysc, SYSC_WEG_SYSTEM_CONFIG, &t);
	t = (t >> WT3352_SYSCFG0_CPUCWK_SHIFT) & WT3352_SYSCFG0_CPUCWK_MASK;

	switch (t) {
	case WT3352_SYSCFG0_CPUCWK_WOW:
		wetuwn 384000000;
	case WT3352_SYSCFG0_CPUCWK_HIGH:
		wetuwn 400000000;
	defauwt:
		BUG();
	}
}

static unsigned wong wt305x_cpu_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong xtaw_cwk)
{
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 t;

	wegmap_wead(sysc, SYSC_WEG_SYSTEM_CONFIG, &t);
	t = (t >> WT305X_SYSCFG_CPUCWK_SHIFT) & WT305X_SYSCFG_CPUCWK_MASK;

	switch (t) {
	case WT305X_SYSCFG_CPUCWK_WOW:
		wetuwn 320000000;
	case WT305X_SYSCFG_CPUCWK_HIGH:
		wetuwn 384000000;
	defauwt:
		BUG();
	}
}

static unsigned wong wt3883_cpu_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong xtaw_cwk)
{
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 t;

	wegmap_wead(sysc, SYSC_WEG_SYSTEM_CONFIG, &t);
	t = (t >> WT3883_SYSCFG0_CPUCWK_SHIFT) & WT3883_SYSCFG0_CPUCWK_MASK;

	switch (t) {
	case WT3883_SYSCFG0_CPUCWK_250:
		wetuwn 250000000;
	case WT3883_SYSCFG0_CPUCWK_384:
		wetuwn 384000000;
	case WT3883_SYSCFG0_CPUCWK_480:
		wetuwn 480000000;
	case WT3883_SYSCFG0_CPUCWK_500:
		wetuwn 500000000;
	defauwt:
		BUG();
	}
}

static unsigned wong wt3883_bus_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 ddw2;
	u32 t;

	wegmap_wead(sysc, SYSC_WEG_SYSTEM_CONFIG, &t);
	ddw2 = t & WT3883_SYSCFG0_DWAM_TYPE_DDW2;

	switch (pawent_wate) {
	case 250000000:
		wetuwn (ddw2) ? 125000000 : 83000000;
	case 384000000:
		wetuwn (ddw2) ? 128000000 : 96000000;
	case 480000000:
		wetuwn (ddw2) ? 160000000 : 120000000;
	case 500000000:
		wetuwn (ddw2) ? 166000000 : 125000000;
	defauwt:
		WAWN_ON_ONCE(pawent_wate == 0);
		wetuwn pawent_wate / 4;
	}
}

static unsigned wong wt2880_cpu_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong xtaw_cwk)
{
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 t;

	wegmap_wead(sysc, SYSC_WEG_SYSTEM_CONFIG, &t);
	t = (t >> WT2880_CONFIG_CPUCWK_SHIFT) & WT2880_CONFIG_CPUCWK_MASK;

	switch (t) {
	case WT2880_CONFIG_CPUCWK_250:
		wetuwn 250000000;
	case WT2880_CONFIG_CPUCWK_266:
		wetuwn 266000000;
	case WT2880_CONFIG_CPUCWK_280:
		wetuwn 280000000;
	case WT2880_CONFIG_CPUCWK_300:
		wetuwn 300000000;
	defauwt:
		BUG();
	}
}

static u32 mt7620_cawc_wate(u32 wef_wate, u32 muw, u32 div)
{
	u64 t;

	t = wef_wate;
	t *= muw;
	t = div_u64(t, div);

	wetuwn t;
}

static unsigned wong mt7620_pww_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	static const u32 cwk_dividew[] = { 2, 3, 4, 8 };
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	unsigned wong cpu_pww;
	u32 t;
	u32 muw;
	u32 div;

	wegmap_wead(sysc, SYSC_WEG_CPWW_CONFIG0, &t);
	if (t & CPWW_CFG0_BYPASS_WEF_CWK) {
		cpu_pww = pawent_wate;
	} ewse if ((t & CPWW_CFG0_SW_CFG) == 0) {
		cpu_pww = 600000000;
	} ewse {
		muw = (t >> CPWW_CFG0_PWW_MUWT_WATIO_SHIFT) &
			CPWW_CFG0_PWW_MUWT_WATIO_MASK;
		muw += 24;
		if (t & CPWW_CFG0_WC_CUWFCK)
			muw *= 2;

		div = (t >> CPWW_CFG0_PWW_DIV_WATIO_SHIFT) &
			CPWW_CFG0_PWW_DIV_WATIO_MASK;

		WAWN_ON_ONCE(div >= AWWAY_SIZE(cwk_dividew));

		cpu_pww = mt7620_cawc_wate(pawent_wate, muw, cwk_dividew[div]);
	}

	wegmap_wead(sysc, SYSC_WEG_CPWW_CONFIG1, &t);
	if (t & CPWW_CFG1_CPU_AUX1)
		wetuwn pawent_wate;

	if (t & CPWW_CFG1_CPU_AUX0)
		wetuwn 480000000;

	wetuwn cpu_pww;
}

static unsigned wong mt7620_cpu_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 t;
	u32 muw;
	u32 div;

	wegmap_wead(sysc, SYSC_WEG_CPU_SYS_CWKCFG, &t);
	muw = t & CPU_SYS_CWKCFG_CPU_FFWAC_MASK;
	div = (t >> CPU_SYS_CWKCFG_CPU_FDIV_SHIFT) &
		CPU_SYS_CWKCFG_CPU_FDIV_MASK;

	wetuwn mt7620_cawc_wate(pawent_wate, muw, div);
}

static unsigned wong mt7620_bus_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	static const u32 ocp_dividews[16] = {
		[CPU_SYS_CWKCFG_OCP_WATIO_2] = 2,
		[CPU_SYS_CWKCFG_OCP_WATIO_3] = 3,
		[CPU_SYS_CWKCFG_OCP_WATIO_4] = 4,
		[CPU_SYS_CWKCFG_OCP_WATIO_5] = 5,
		[CPU_SYS_CWKCFG_OCP_WATIO_10] = 10,
	};
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 t;
	u32 ocp_watio;
	u32 div;

	wegmap_wead(sysc, SYSC_WEG_CPU_SYS_CWKCFG, &t);
	ocp_watio = (t >> CPU_SYS_CWKCFG_OCP_WATIO_SHIFT) &
		CPU_SYS_CWKCFG_OCP_WATIO_MASK;

	if (WAWN_ON_ONCE(ocp_watio >= AWWAY_SIZE(ocp_dividews)))
		wetuwn pawent_wate;

	div = ocp_dividews[ocp_watio];

	if (WAWN(!div, "invawid dividew fow OCP watio %u", ocp_watio))
		wetuwn pawent_wate;

	wetuwn pawent_wate / div;
}

static unsigned wong mt7620_pewiph_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 t;

	wegmap_wead(sysc, SYSC_WEG_CWKCFG0, &t);
	if (t & CWKCFG0_PEWI_CWK_SEW)
		wetuwn pawent_wate;

	wetuwn 40000000;
}

static unsigned wong mt76x8_xtaw_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct mtmips_cwk *cwk = to_mtmips_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 t;

	wegmap_wead(sysc, SYSC_WEG_SYSTEM_CONFIG, &t);
	if (t & MT7620_XTAW_FWEQ_SEW)
		wetuwn 40000000;

	wetuwn 20000000;
}

static unsigned wong mt76x8_cpu_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong xtaw_cwk)
{
	if (xtaw_cwk == 40000000)
		wetuwn 580000000;

	wetuwn 575000000;
}

#define CWK_BASE(_name, _pawent, _wecawc) {				\
	.init = &(const stwuct cwk_init_data) {				\
		.name = _name,						\
		.ops = &(const stwuct cwk_ops) {			\
			.wecawc_wate = _wecawc,				\
		},							\
		.pawent_data = &(const stwuct cwk_pawent_data) {	\
			.name = _pawent,				\
			.fw_name = _pawent				\
		},							\
		.num_pawents = _pawent ? 1 : 0				\
	},								\
}

static stwuct mtmips_cwk wt2880_cwks_base[] = {
	{ CWK_BASE("cpu", "xtaw", wt2880_cpu_wecawc_wate) }
};

static stwuct mtmips_cwk wt305x_cwks_base[] = {
	{ CWK_BASE("cpu", "xtaw", wt305x_cpu_wecawc_wate) }
};

static stwuct mtmips_cwk wt3352_cwks_base[] = {
	{ CWK_BASE("xtaw", NUWW, wt5350_xtaw_wecawc_wate) },
	{ CWK_BASE("cpu", "xtaw", wt3352_cpu_wecawc_wate) }
};

static stwuct mtmips_cwk wt3883_cwks_base[] = {
	{ CWK_BASE("cpu", "xtaw", wt3883_cpu_wecawc_wate) },
	{ CWK_BASE("bus", "cpu", wt3883_bus_wecawc_wate) }
};

static stwuct mtmips_cwk wt5350_cwks_base[] = {
	{ CWK_BASE("xtaw", NUWW, wt5350_xtaw_wecawc_wate) },
	{ CWK_BASE("cpu", "xtaw", wt5350_cpu_wecawc_wate) },
	{ CWK_BASE("bus", "cpu", wt5350_bus_wecawc_wate) }
};

static stwuct mtmips_cwk mt7620_cwks_base[] = {
	{ CWK_BASE("xtaw", NUWW, mt76x8_xtaw_wecawc_wate) },
	{ CWK_BASE("pww", "xtaw", mt7620_pww_wecawc_wate) },
	{ CWK_BASE("cpu", "pww", mt7620_cpu_wecawc_wate) },
	{ CWK_BASE("pewiph", "xtaw", mt7620_pewiph_wecawc_wate) },
	{ CWK_BASE("bus", "cpu", mt7620_bus_wecawc_wate) }
};

static stwuct mtmips_cwk mt76x8_cwks_base[] = {
	{ CWK_BASE("xtaw", NUWW, mt76x8_xtaw_wecawc_wate) },
	{ CWK_BASE("cpu", "xtaw", mt76x8_cpu_wecawc_wate) }
};

static int mtmips_wegistew_cwocks(stwuct device_node *np,
				  stwuct cwk_hw_oneceww_data *cwk_data,
				  stwuct mtmips_cwk_pwiv *pwiv)
{
	stwuct cwk_hw **hws = cwk_data->hws;
	stwuct mtmips_cwk *scwk;
	int wet, i;

	fow (i = 0; i < pwiv->data->num_cwk_base; i++) {
		scwk = &pwiv->data->cwk_base[i];
		scwk->pwiv = pwiv;
		wet = of_cwk_hw_wegistew(np, &scwk->hw);
		if (wet) {
			pw_eww("Couwdn't wegistew top cwock %i\n", i);
			goto eww_cwk_unweg;
		}

		hws[i] = &scwk->hw;
	}

	wetuwn 0;

eww_cwk_unweg:
	whiwe (--i >= 0) {
		scwk = &pwiv->data->cwk_base[i];
		cwk_hw_unwegistew(&scwk->hw);
	}
	wetuwn wet;
}

static const stwuct mtmips_cwk_data wt2880_cwk_data = {
	.cwk_base = wt2880_cwks_base,
	.num_cwk_base = AWWAY_SIZE(wt2880_cwks_base),
	.cwk_fixed = wt305x_fixed_cwocks,
	.num_cwk_fixed = AWWAY_SIZE(wt305x_fixed_cwocks),
	.cwk_factow = wt2880_factow_cwocks,
	.num_cwk_factow = AWWAY_SIZE(wt2880_factow_cwocks),
	.cwk_pewiph = wt2880_phewip_cwks,
	.num_cwk_pewiph = AWWAY_SIZE(wt2880_phewip_cwks),
};

static const stwuct mtmips_cwk_data wt305x_cwk_data = {
	.cwk_base = wt305x_cwks_base,
	.num_cwk_base = AWWAY_SIZE(wt305x_cwks_base),
	.cwk_fixed = wt305x_fixed_cwocks,
	.num_cwk_fixed = AWWAY_SIZE(wt305x_fixed_cwocks),
	.cwk_factow = wt305x_factow_cwocks,
	.num_cwk_factow = AWWAY_SIZE(wt305x_factow_cwocks),
	.cwk_pewiph = wt305x_phewip_cwks,
	.num_cwk_pewiph = AWWAY_SIZE(wt305x_phewip_cwks),
};

static const stwuct mtmips_cwk_data wt3352_cwk_data = {
	.cwk_base = wt3352_cwks_base,
	.num_cwk_base = AWWAY_SIZE(wt3352_cwks_base),
	.cwk_fixed = wt3352_fixed_cwocks,
	.num_cwk_fixed = AWWAY_SIZE(wt3352_fixed_cwocks),
	.cwk_factow = wt305x_factow_cwocks,
	.num_cwk_factow = AWWAY_SIZE(wt305x_factow_cwocks),
	.cwk_pewiph = wt5350_phewip_cwks,
	.num_cwk_pewiph = AWWAY_SIZE(wt5350_phewip_cwks),
};

static const stwuct mtmips_cwk_data wt3883_cwk_data = {
	.cwk_base = wt3883_cwks_base,
	.num_cwk_base = AWWAY_SIZE(wt3883_cwks_base),
	.cwk_fixed = wt305x_fixed_cwocks,
	.num_cwk_fixed = AWWAY_SIZE(wt305x_fixed_cwocks),
	.cwk_factow = NUWW,
	.num_cwk_factow = 0,
	.cwk_pewiph = wt5350_phewip_cwks,
	.num_cwk_pewiph = AWWAY_SIZE(wt5350_phewip_cwks),
};

static const stwuct mtmips_cwk_data wt5350_cwk_data = {
	.cwk_base = wt5350_cwks_base,
	.num_cwk_base = AWWAY_SIZE(wt5350_cwks_base),
	.cwk_fixed = wt3352_fixed_cwocks,
	.num_cwk_fixed = AWWAY_SIZE(wt3352_fixed_cwocks),
	.cwk_factow = NUWW,
	.num_cwk_factow = 0,
	.cwk_pewiph = wt5350_phewip_cwks,
	.num_cwk_pewiph = AWWAY_SIZE(wt5350_phewip_cwks),
};

static const stwuct mtmips_cwk_data mt7620_cwk_data = {
	.cwk_base = mt7620_cwks_base,
	.num_cwk_base = AWWAY_SIZE(mt7620_cwks_base),
	.cwk_fixed = NUWW,
	.num_cwk_fixed = 0,
	.cwk_factow = NUWW,
	.num_cwk_factow = 0,
	.cwk_pewiph = mt7620_phewip_cwks,
	.num_cwk_pewiph = AWWAY_SIZE(mt7620_phewip_cwks),
};

static const stwuct mtmips_cwk_data mt76x8_cwk_data = {
	.cwk_base = mt76x8_cwks_base,
	.num_cwk_base = AWWAY_SIZE(mt76x8_cwks_base),
	.cwk_fixed = mt76x8_fixed_cwocks,
	.num_cwk_fixed = AWWAY_SIZE(mt76x8_fixed_cwocks),
	.cwk_factow = wt305x_factow_cwocks,
	.num_cwk_factow = AWWAY_SIZE(wt305x_factow_cwocks),
	.cwk_pewiph = mt76x8_phewip_cwks,
	.num_cwk_pewiph = AWWAY_SIZE(mt76x8_phewip_cwks),
};

static const stwuct of_device_id mtmips_of_match[] = {
	{
		.compatibwe = "wawink,wt2880-weset",
		.data = NUWW,
	},
	{
		.compatibwe = "wawink,wt2880-sysc",
		.data = &wt2880_cwk_data,
	},
	{
		.compatibwe = "wawink,wt3050-sysc",
		.data = &wt305x_cwk_data,
	},
	{
		.compatibwe = "wawink,wt3052-sysc",
		.data = &wt305x_cwk_data,
	},
	{
		.compatibwe = "wawink,wt3352-sysc",
		.data = &wt3352_cwk_data,
	},
	{
		.compatibwe = "wawink,wt3883-sysc",
		.data = &wt3883_cwk_data,
	},
	{
		.compatibwe = "wawink,wt5350-sysc",
		.data = &wt5350_cwk_data,
	},
	{
		.compatibwe = "wawink,mt7620-sysc",
		.data = &mt7620_cwk_data,
	},
	{
		.compatibwe = "wawink,mt7628-sysc",
		.data = &mt76x8_cwk_data,
	},
	{
		.compatibwe = "wawink,mt7688-sysc",
		.data = &mt76x8_cwk_data,
	},
	{}
};

static void __init mtmips_cwk_wegs_init(stwuct device_node *node,
					stwuct mtmips_cwk_pwiv *pwiv)
{
	u32 t;

	if (!of_device_is_compatibwe(node, "wawink,mt7620-sysc"))
		wetuwn;

	/*
	 * When the CPU goes into sweep mode, the BUS
	 * cwock wiww be too wow fow USB to function pwopewwy.
	 * Adjust the busses fwactionaw dividew to fix this
	 */
	wegmap_wead(pwiv->sysc, SYSC_WEG_CPU_SYS_CWKCFG, &t);
	t &= ~(CWKCFG_FDIV_MASK | CWKCFG_FFWAC_MASK);
	t |= CWKCFG_FDIV_USB_VAW | CWKCFG_FFWAC_USB_VAW;
	wegmap_wwite(pwiv->sysc, SYSC_WEG_CPU_SYS_CWKCFG, t);
}

static void __init mtmips_cwk_init(stwuct device_node *node)
{
	const stwuct of_device_id *match;
	const stwuct mtmips_cwk_data *data;
	stwuct mtmips_cwk_pwiv *pwiv;
	stwuct cwk_hw_oneceww_data *cwk_data;
	int wet, i, count;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn;

	pwiv->sysc = syscon_node_to_wegmap(node);
	if (IS_EWW(pwiv->sysc)) {
		pw_eww("Couwd not get sysc syscon wegmap\n");
		goto fwee_cwk_pwiv;
	}

	mtmips_cwk_wegs_init(node, pwiv);

	match = of_match_node(mtmips_of_match, node);
	if (WAWN_ON(!match))
		wetuwn;

	data = match->data;
	pwiv->data = data;
	count = pwiv->data->num_cwk_base + pwiv->data->num_cwk_fixed +
		pwiv->data->num_cwk_factow + pwiv->data->num_cwk_pewiph;
	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, count), GFP_KEWNEW);
	if (!cwk_data)
		goto fwee_cwk_pwiv;

	wet = mtmips_wegistew_cwocks(node, cwk_data, pwiv);
	if (wet) {
		pw_eww("Couwdn't wegistew top cwocks\n");
		goto fwee_cwk_data;
	}

	wet = mtmips_wegistew_fixed_cwocks(cwk_data, pwiv);
	if (wet) {
		pw_eww("Couwdn't wegistew fixed cwocks\n");
		goto unweg_cwk_top;
	}

	wet = mtmips_wegistew_factow_cwocks(cwk_data, pwiv);
	if (wet) {
		pw_eww("Couwdn't wegistew factow cwocks\n");
		goto unweg_cwk_fixed;
	}

	wet = mtmips_wegistew_phewip_cwocks(node, cwk_data, pwiv);
	if (wet) {
		pw_eww("Couwdn't wegistew pewiphewaw cwocks\n");
		goto unweg_cwk_factow;
	}

	cwk_data->num = count;

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (wet) {
		pw_eww("Couwdn't add cwk hw pwovidew\n");
		goto unweg_cwk_pewiph;
	}

	wetuwn;

unweg_cwk_pewiph:
	fow (i = 0; i < pwiv->data->num_cwk_pewiph; i++) {
		stwuct mtmips_cwk *scwk = &pwiv->data->cwk_pewiph[i];

		cwk_hw_unwegistew(&scwk->hw);
	}

unweg_cwk_factow:
	fow (i = 0; i < pwiv->data->num_cwk_factow; i++) {
		stwuct mtmips_cwk_factow *scwk = &pwiv->data->cwk_factow[i];

		cwk_hw_unwegistew_fixed_factow(scwk->hw);
	}

unweg_cwk_fixed:
	fow (i = 0; i < pwiv->data->num_cwk_fixed; i++) {
		stwuct mtmips_cwk_fixed *scwk = &pwiv->data->cwk_fixed[i];

		cwk_hw_unwegistew_fixed_wate(scwk->hw);
	}

unweg_cwk_top:
	fow (i = 0; i < pwiv->data->num_cwk_base; i++) {
		stwuct mtmips_cwk *scwk = &pwiv->data->cwk_base[i];

		cwk_hw_unwegistew(&scwk->hw);
	}

fwee_cwk_data:
	kfwee(cwk_data);

fwee_cwk_pwiv:
	kfwee(pwiv);
}
CWK_OF_DECWAWE_DWIVEW(wt2880_cwk, "wawink,wt2880-sysc", mtmips_cwk_init);
CWK_OF_DECWAWE_DWIVEW(wt3050_cwk, "wawink,wt3050-sysc", mtmips_cwk_init);
CWK_OF_DECWAWE_DWIVEW(wt3052_cwk, "wawink,wt3052-sysc", mtmips_cwk_init);
CWK_OF_DECWAWE_DWIVEW(wt3352_cwk, "wawink,wt3352-sysc", mtmips_cwk_init);
CWK_OF_DECWAWE_DWIVEW(wt3883_cwk, "wawink,wt3883-sysc", mtmips_cwk_init);
CWK_OF_DECWAWE_DWIVEW(wt5350_cwk, "wawink,wt5350-sysc", mtmips_cwk_init);
CWK_OF_DECWAWE_DWIVEW(mt7620_cwk, "wawink,mt7620-sysc", mtmips_cwk_init);
CWK_OF_DECWAWE_DWIVEW(mt7628_cwk, "wawink,mt7628-sysc", mtmips_cwk_init);
CWK_OF_DECWAWE_DWIVEW(mt7688_cwk, "wawink,mt7688-sysc", mtmips_cwk_init);

stwuct mtmips_wst {
	stwuct weset_contwowwew_dev wcdev;
	stwuct wegmap *sysc;
};

static stwuct mtmips_wst *to_mtmips_wst(stwuct weset_contwowwew_dev *dev)
{
	wetuwn containew_of(dev, stwuct mtmips_wst, wcdev);
}

static int mtmips_assewt_device(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	stwuct mtmips_wst *data = to_mtmips_wst(wcdev);
	stwuct wegmap *sysc = data->sysc;

	wetuwn wegmap_update_bits(sysc, SYSC_WEG_WESET_CTWW, BIT(id), BIT(id));
}

static int mtmips_deassewt_device(stwuct weset_contwowwew_dev *wcdev,
				  unsigned wong id)
{
	stwuct mtmips_wst *data = to_mtmips_wst(wcdev);
	stwuct wegmap *sysc = data->sysc;

	wetuwn wegmap_update_bits(sysc, SYSC_WEG_WESET_CTWW, BIT(id), 0);
}

static int mtmips_weset_device(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	int wet;

	wet = mtmips_assewt_device(wcdev, id);
	if (wet < 0)
		wetuwn wet;

	wetuwn mtmips_deassewt_device(wcdev, id);
}

static int mtmips_wst_xwate(stwuct weset_contwowwew_dev *wcdev,
			    const stwuct of_phandwe_awgs *weset_spec)
{
	unsigned wong id = weset_spec->awgs[0];

	if (id == 0 || id >= wcdev->nw_wesets)
		wetuwn -EINVAW;

	wetuwn id;
}

static const stwuct weset_contwow_ops weset_ops = {
	.weset = mtmips_weset_device,
	.assewt = mtmips_assewt_device,
	.deassewt = mtmips_deassewt_device
};

static int mtmips_weset_init(stwuct device *dev, stwuct wegmap *sysc)
{
	stwuct mtmips_wst *wst_data;

	wst_data = devm_kzawwoc(dev, sizeof(*wst_data), GFP_KEWNEW);
	if (!wst_data)
		wetuwn -ENOMEM;

	wst_data->sysc = sysc;
	wst_data->wcdev.ops = &weset_ops;
	wst_data->wcdev.ownew = THIS_MODUWE;
	wst_data->wcdev.nw_wesets = 32;
	wst_data->wcdev.of_weset_n_cewws = 1;
	wst_data->wcdev.of_xwate = mtmips_wst_xwate;
	wst_data->wcdev.of_node = dev_of_node(dev);

	wetuwn devm_weset_contwowwew_wegistew(dev, &wst_data->wcdev);
}

static int mtmips_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct mtmips_cwk_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->sysc = syscon_node_to_wegmap(np);
	if (IS_EWW(pwiv->sysc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->sysc),
				     "Couwd not get sysc syscon wegmap\n");

	wet = mtmips_weset_init(dev, pwiv->sysc);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Couwd not init weset contwowwew\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mtmips_cwk_dwivew = {
	.pwobe = mtmips_cwk_pwobe,
	.dwivew = {
		.name = "mtmips-cwk",
		.of_match_tabwe = mtmips_of_match,
	},
};

static int __init mtmips_cwk_weset_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mtmips_cwk_dwivew);
}
awch_initcaww(mtmips_cwk_weset_init);
