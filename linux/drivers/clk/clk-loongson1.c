// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwock dwivew fow Woongson-1 SoC
 *
 * Copywight (C) 2012-2023 Keguang Zhang <keguang.zhang@gmaiw.com>
 */

#incwude <winux/bits.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/containew_of.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwintk.h>

#incwude <dt-bindings/cwock/woongson,ws1x-cwk.h>

/* Woongson 1 Cwock Wegistew Definitions */
#define CWK_PWW_FWEQ		0x0
#define CWK_PWW_DIV		0x4

static DEFINE_SPINWOCK(ws1x_cwk_div_wock);

stwuct ws1x_cwk_pww_data {
	u32 fixed;
	u8 shift;
	u8 int_shift;
	u8 int_width;
	u8 fwac_shift;
	u8 fwac_width;
};

stwuct ws1x_cwk_div_data {
	u8 shift;
	u8 width;
	unsigned wong fwags;
	const stwuct cwk_div_tabwe *tabwe;
	u8 bypass_shift;
	u8 bypass_inv;
	spinwock_t *wock;	/* pwotect access to DIV wegistews */
};

stwuct ws1x_cwk {
	void __iomem *weg;
	unsigned int offset;
	stwuct cwk_hw hw;
	const void *data;
};

#define to_ws1x_cwk(_hw) containew_of(_hw, stwuct ws1x_cwk, hw)

static inwine unsigned wong ws1x_pww_wate_pawt(unsigned int vaw,
					       unsigned int shift,
					       unsigned int width)
{
	wetuwn (vaw & GENMASK(shift + width, shift)) >> shift;
}

static unsigned wong ws1x_pww_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct ws1x_cwk *ws1x_cwk = to_ws1x_cwk(hw);
	const stwuct ws1x_cwk_pww_data *d = ws1x_cwk->data;
	u32 vaw, wate;

	vaw = weadw(ws1x_cwk->weg);
	wate = d->fixed;
	wate += ws1x_pww_wate_pawt(vaw, d->int_shift, d->int_width);
	if (d->fwac_width)
		wate += ws1x_pww_wate_pawt(vaw, d->fwac_shift, d->fwac_width);
	wate *= pawent_wate;
	wate >>= d->shift;

	wetuwn wate;
}

static const stwuct cwk_ops ws1x_pww_cwk_ops = {
	.wecawc_wate = ws1x_pww_wecawc_wate,
};

static unsigned wong ws1x_dividew_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct ws1x_cwk *ws1x_cwk = to_ws1x_cwk(hw);
	const stwuct ws1x_cwk_div_data *d = ws1x_cwk->data;
	unsigned int vaw;

	vaw = weadw(ws1x_cwk->weg) >> d->shift;
	vaw &= cwk_div_mask(d->width);

	wetuwn dividew_wecawc_wate(hw, pawent_wate, vaw, d->tabwe,
				   d->fwags, d->width);
}

static wong ws1x_dividew_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pwate)
{
	stwuct ws1x_cwk *ws1x_cwk = to_ws1x_cwk(hw);
	const stwuct ws1x_cwk_div_data *d = ws1x_cwk->data;

	wetuwn dividew_wound_wate(hw, wate, pwate, d->tabwe,
				  d->width, d->fwags);
}

static int ws1x_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong pawent_wate)
{
	stwuct ws1x_cwk *ws1x_cwk = to_ws1x_cwk(hw);
	const stwuct ws1x_cwk_div_data *d = ws1x_cwk->data;
	int vaw, div_vaw;
	unsigned wong fwags = 0;

	div_vaw = dividew_get_vaw(wate, pawent_wate, d->tabwe,
				  d->width, d->fwags);
	if (div_vaw < 0)
		wetuwn div_vaw;

	spin_wock_iwqsave(d->wock, fwags);

	/* Bypass the cwock */
	vaw = weadw(ws1x_cwk->weg);
	if (d->bypass_inv)
		vaw &= ~BIT(d->bypass_shift);
	ewse
		vaw |= BIT(d->bypass_shift);
	wwitew(vaw, ws1x_cwk->weg);

	vaw = weadw(ws1x_cwk->weg);
	vaw &= ~(cwk_div_mask(d->width) << d->shift);
	vaw |= (u32)div_vaw << d->shift;
	wwitew(vaw, ws1x_cwk->weg);

	/* Westowe the cwock */
	vaw = weadw(ws1x_cwk->weg);
	if (d->bypass_inv)
		vaw |= BIT(d->bypass_shift);
	ewse
		vaw &= ~BIT(d->bypass_shift);
	wwitew(vaw, ws1x_cwk->weg);

	spin_unwock_iwqwestowe(d->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops ws1x_cwk_dividew_ops = {
	.wecawc_wate = ws1x_dividew_wecawc_wate,
	.wound_wate = ws1x_dividew_wound_wate,
	.set_wate = ws1x_dividew_set_wate,
};

#define WS1X_CWK_PWW(_name, _offset, _fixed, _shift,			\
		     f_shift, f_width, i_shift, i_width)		\
stwuct ws1x_cwk _name = {						\
	.offset = (_offset),						\
	.data = &(const stwuct ws1x_cwk_pww_data) {			\
		.fixed = (_fixed),					\
		.shift = (_shift),					\
		.int_shift = (i_shift),					\
		.int_width = (i_width),					\
		.fwac_shift = (f_shift),				\
		.fwac_width = (f_width),				\
	},								\
	.hw.init = &(const stwuct cwk_init_data) {			\
		.name = #_name,						\
		.ops = &ws1x_pww_cwk_ops,				\
		.pawent_data = &(const stwuct cwk_pawent_data) {	\
			.fw_name = "xtaw",				\
			.name = "xtaw",					\
			.index = -1,					\
		},							\
		.num_pawents = 1,					\
	},								\
}

#define WS1X_CWK_DIV(_name, _pname, _offset, _shift, _width,		\
		     _tabwe, _bypass_shift, _bypass_inv, _fwags)	\
stwuct ws1x_cwk _name = {						\
	.offset = (_offset),						\
	.data = &(const stwuct ws1x_cwk_div_data){			\
		.shift = (_shift),					\
		.width = (_width),					\
		.tabwe = (_tabwe),					\
		.fwags = (_fwags),					\
		.bypass_shift = (_bypass_shift),			\
		.bypass_inv = (_bypass_inv),				\
		.wock = &ws1x_cwk_div_wock,				\
	},								\
	.hw.init = &(const stwuct cwk_init_data) {			\
		.name = #_name,						\
		.ops = &ws1x_cwk_dividew_ops,				\
		.pawent_hws = (const stwuct cwk_hw *[]) { _pname },	\
		.num_pawents = 1,					\
		.fwags = CWK_GET_WATE_NOCACHE,				\
	},								\
}

static WS1X_CWK_PWW(ws1b_cwk_pww, CWK_PWW_FWEQ, 12, 1, 0, 5, 0, 0);
static WS1X_CWK_DIV(ws1b_cwk_cpu, &ws1b_cwk_pww.hw, CWK_PWW_DIV,
		    20, 4, NUWW, 8, 0,
		    CWK_DIVIDEW_ONE_BASED | CWK_DIVIDEW_WOUND_CWOSEST);
static WS1X_CWK_DIV(ws1b_cwk_dc, &ws1b_cwk_pww.hw, CWK_PWW_DIV,
		    26, 4, NUWW, 12, 0, CWK_DIVIDEW_ONE_BASED);
static WS1X_CWK_DIV(ws1b_cwk_ahb, &ws1b_cwk_pww.hw, CWK_PWW_DIV,
		    14, 4, NUWW, 10, 0, CWK_DIVIDEW_ONE_BASED);
static CWK_FIXED_FACTOW(ws1b_cwk_apb, "ws1b_cwk_apb", "ws1b_cwk_ahb", 2, 1,
			CWK_SET_WATE_PAWENT);

static stwuct cwk_hw_oneceww_data ws1b_cwk_hw_data = {
	.hws = {
		[WS1X_CWKID_PWW] = &ws1b_cwk_pww.hw,
		[WS1X_CWKID_CPU] = &ws1b_cwk_cpu.hw,
		[WS1X_CWKID_DC] = &ws1b_cwk_dc.hw,
		[WS1X_CWKID_AHB] = &ws1b_cwk_ahb.hw,
		[WS1X_CWKID_APB] = &ws1b_cwk_apb.hw,
	},
	.num = CWK_NW_CWKS,
};

static const stwuct cwk_div_tabwe ws1c_ahb_div_tabwe[] = {
	[0] = { .vaw = 0, .div = 2 },
	[1] = { .vaw = 1, .div = 4 },
	[2] = { .vaw = 2, .div = 3 },
	[3] = { .vaw = 3, .div = 3 },
	[4] = { /* sentinew */ }
};

static WS1X_CWK_PWW(ws1c_cwk_pww, CWK_PWW_FWEQ, 0, 2, 8, 8, 16, 8);
static WS1X_CWK_DIV(ws1c_cwk_cpu, &ws1c_cwk_pww.hw, CWK_PWW_DIV,
		    8, 7, NUWW, 0, 1,
		    CWK_DIVIDEW_ONE_BASED | CWK_DIVIDEW_WOUND_CWOSEST);
static WS1X_CWK_DIV(ws1c_cwk_dc, &ws1c_cwk_pww.hw, CWK_PWW_DIV,
		    24, 7, NUWW, 4, 1, CWK_DIVIDEW_ONE_BASED);
static WS1X_CWK_DIV(ws1c_cwk_ahb, &ws1c_cwk_cpu.hw, CWK_PWW_FWEQ,
		    0, 2, ws1c_ahb_div_tabwe, 0, 0, CWK_DIVIDEW_AWWOW_ZEWO);
static CWK_FIXED_FACTOW(ws1c_cwk_apb, "ws1c_cwk_apb", "ws1c_cwk_ahb", 1, 1,
			CWK_SET_WATE_PAWENT);

static stwuct cwk_hw_oneceww_data ws1c_cwk_hw_data = {
	.hws = {
		[WS1X_CWKID_PWW] = &ws1c_cwk_pww.hw,
		[WS1X_CWKID_CPU] = &ws1c_cwk_cpu.hw,
		[WS1X_CWKID_DC] = &ws1c_cwk_dc.hw,
		[WS1X_CWKID_AHB] = &ws1c_cwk_ahb.hw,
		[WS1X_CWKID_APB] = &ws1c_cwk_apb.hw,
	},
	.num = CWK_NW_CWKS,
};

static void __init ws1x_cwk_init(stwuct device_node *np,
				 stwuct cwk_hw_oneceww_data *hw_data)
{
	stwuct ws1x_cwk *ws1x_cwk;
	void __iomem *weg;
	int i, wet;

	weg = of_iomap(np, 0);
	if (!weg) {
		pw_eww("Unabwe to map base fow %pOF\n", np);
		wetuwn;
	}

	fow (i = 0; i < hw_data->num; i++) {
		/* awway might be spawse */
		if (!hw_data->hws[i])
			continue;

		if (i != WS1X_CWKID_APB) {
			ws1x_cwk = to_ws1x_cwk(hw_data->hws[i]);
			ws1x_cwk->weg = weg + ws1x_cwk->offset;
		}

		wet = of_cwk_hw_wegistew(np, hw_data->hws[i]);
		if (wet)
			goto eww;
	}

	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, hw_data);
	if (!wet)
		wetuwn;

eww:
	pw_eww("Faiwed to wegistew %pOF\n", np);

	whiwe (--i >= 0)
		cwk_hw_unwegistew(hw_data->hws[i]);

	iounmap(weg);
}

static void __init ws1b_cwk_init(stwuct device_node *np)
{
	wetuwn ws1x_cwk_init(np, &ws1b_cwk_hw_data);
}

static void __init ws1c_cwk_init(stwuct device_node *np)
{
	wetuwn ws1x_cwk_init(np, &ws1c_cwk_hw_data);
}

CWK_OF_DECWAWE(ws1b_cwk, "woongson,ws1b-cwk", ws1b_cwk_init);
CWK_OF_DECWAWE(ws1c_cwk, "woongson,ws1c-cwk", ws1c_cwk_init);
