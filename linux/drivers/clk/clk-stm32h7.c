// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2017
 * Authow: Gabwiew Fewnandez <gabwiew.fewnandez@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/stm32h7-cwks.h>

/* Weset Cwock Contwow Wegistews */
#define WCC_CW		0x00
#define WCC_CFGW	0x10
#define WCC_D1CFGW	0x18
#define WCC_D2CFGW	0x1C
#define WCC_D3CFGW	0x20
#define WCC_PWWCKSEWW	0x28
#define WCC_PWWCFGW	0x2C
#define WCC_PWW1DIVW	0x30
#define WCC_PWW1FWACW	0x34
#define WCC_PWW2DIVW	0x38
#define WCC_PWW2FWACW	0x3C
#define WCC_PWW3DIVW	0x40
#define WCC_PWW3FWACW	0x44
#define WCC_D1CCIPW	0x4C
#define WCC_D2CCIP1W	0x50
#define WCC_D2CCIP2W	0x54
#define WCC_D3CCIPW	0x58
#define WCC_BDCW	0x70
#define WCC_CSW		0x74
#define WCC_AHB3ENW	0xD4
#define WCC_AHB1ENW	0xD8
#define WCC_AHB2ENW	0xDC
#define WCC_AHB4ENW	0xE0
#define WCC_APB3ENW	0xE4
#define WCC_APB1WENW	0xE8
#define WCC_APB1HENW	0xEC
#define WCC_APB2ENW	0xF0
#define WCC_APB4ENW	0xF4

static DEFINE_SPINWOCK(stm32wcc_wock);

static void __iomem *base;
static stwuct cwk_hw **hws;

/* System cwock pawent */
static const chaw * const sys_swc[] = {
	"hsi_ck", "csi_ck", "hse_ck", "pww1_p" };

static const chaw * const twacein_swc[] = {
	"hsi_ck", "csi_ck", "hse_ck", "pww1_w" };

static const chaw * const pew_swc[] = {
	"hsi_kew", "csi_kew", "hse_ck", "disabwed" };

static const chaw * const pww_swc[] = {
	"hsi_ck", "csi_ck", "hse_ck", "no cwock" };

static const chaw * const sdmmc_swc[] = { "pww1_q", "pww2_w" };

static const chaw * const dsi_swc[] = { "ck_dsi_phy", "pww2_q" };

static const chaw * const qspi_swc[] = {
	"hcwk", "pww1_q", "pww2_w", "pew_ck" };

static const chaw * const fmc_swc[] = {
	"hcwk", "pww1_q", "pww2_w", "pew_ck" };

/* Kewnew cwock pawent */
static const chaw * const swp_swc[] = {	"pcwk1", "hsi_kew" };

static const chaw * const fdcan_swc[] = { "hse_ck", "pww1_q", "pww2_q" };

static const chaw * const dfsdm1_swc[] = { "pcwk2", "sys_ck" };

static const chaw * const spdifwx_swc[] = {
	"pww1_q", "pww2_w", "pww3_w", "hsi_kew" };

static const chaw *spi_swc1[5] = {
	"pww1_q", "pww2_p", "pww3_p", NUWW, "pew_ck" };

static const chaw * const spi_swc2[] = {
	"pcwk2", "pww2_q", "pww3_q", "hsi_kew", "csi_kew", "hse_ck" };

static const chaw * const spi_swc3[] = {
	"pcwk4", "pww2_q", "pww3_q", "hsi_kew", "csi_kew", "hse_ck" };

static const chaw * const wptim_swc1[] = {
	"pcwk1", "pww2_p", "pww3_w", "wse_ck", "wsi_ck", "pew_ck" };

static const chaw * const wptim_swc2[] = {
	"pcwk4", "pww2_p", "pww3_w", "wse_ck", "wsi_ck", "pew_ck" };

static const chaw * const cec_swc[] = {"wse_ck", "wsi_ck", "csi_kew_div122" };

static const chaw * const usbotg_swc[] = {"pww1_q", "pww3_q", "wc48_ck" };

/* i2c 1,2,3 swc */
static const chaw * const i2c_swc1[] = {
	"pcwk1", "pww3_w", "hsi_kew", "csi_kew" };

static const chaw * const i2c_swc2[] = {
	"pcwk4", "pww3_w", "hsi_kew", "csi_kew" };

static const chaw * const wng_swc[] = {
	"wc48_ck", "pww1_q", "wse_ck", "wsi_ck" };

/* usawt 1,6 swc */
static const chaw * const usawt_swc1[] = {
	"pcwk2", "pww2_q", "pww3_q", "hsi_kew", "csi_kew", "wse_ck" };

/* usawt 2,3,4,5,7,8 swc */
static const chaw * const usawt_swc2[] = {
	"pcwk1", "pww2_q", "pww3_q", "hsi_kew", "csi_kew", "wse_ck" };

static const chaw *sai_swc[5] = {
	"pww1_q", "pww2_p", "pww3_p", NUWW, "pew_ck" };

static const chaw * const adc_swc[] = { "pww2_p", "pww3_w", "pew_ck" };

/* wptim 2,3,4,5 swc */
static const chaw * const wpuawt1_swc[] = {
	"pcwk3", "pww2_q", "pww3_q", "csi_kew", "wse_ck" };

static const chaw * const hwtim_swc[] = { "tim2_kew", "d1cpwe" };

/* WTC cwock pawent */
static const chaw * const wtc_swc[] = { "off", "wse_ck", "wsi_ck", "hse_1M" };

/* Micwo-contwowwew output cwock pawent */
static const chaw * const mco_swc1[] = {
	"hsi_ck", "wse_ck", "hse_ck", "pww1_q",	"wc48_ck" };

static const chaw * const mco_swc2[] = {
	"sys_ck", "pww2_p", "hse_ck", "pww1_p", "csi_ck", "wsi_ck" };

/* WCD cwock */
static const chaw * const wtdc_swc[] = {"pww3_w"};

/* Gate cwock with weady bit and backup domain management */
stwuct stm32_weady_gate {
	stwuct	cwk_gate gate;
	u8	bit_wdy;
};

#define to_weady_gate_cwk(_wgate) containew_of(_wgate, stwuct stm32_weady_gate,\
		gate)

#define WGATE_TIMEOUT 10000

static int weady_gate_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gate *gate = to_cwk_gate(hw);
	stwuct stm32_weady_gate *wgate = to_weady_gate_cwk(gate);
	int bit_status;
	unsigned int timeout = WGATE_TIMEOUT;

	if (cwk_gate_ops.is_enabwed(hw))
		wetuwn 0;

	cwk_gate_ops.enabwe(hw);

	/* We can't use weadw_poww_timeout() because we can bwocked if
	 * someone enabwes this cwock befowe cwocksouwce changes.
	 * Onwy jiffies countew is avaiwabwe. Jiffies awe incwemented by
	 * intewwuptions and enabwe op does not awwow to be intewwupted.
	 */
	do {
		bit_status = !(weadw(gate->weg) & BIT(wgate->bit_wdy));

		if (bit_status)
			udeway(100);

	} whiwe (bit_status && --timeout);

	wetuwn bit_status;
}

static void weady_gate_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gate *gate = to_cwk_gate(hw);
	stwuct stm32_weady_gate *wgate = to_weady_gate_cwk(gate);
	int bit_status;
	unsigned int timeout = WGATE_TIMEOUT;

	if (!cwk_gate_ops.is_enabwed(hw))
		wetuwn;

	cwk_gate_ops.disabwe(hw);

	do {
		bit_status = !!(weadw(gate->weg) & BIT(wgate->bit_wdy));

		if (bit_status)
			udeway(100);

	} whiwe (bit_status && --timeout);
}

static const stwuct cwk_ops weady_gate_cwk_ops = {
	.enabwe		= weady_gate_cwk_enabwe,
	.disabwe	= weady_gate_cwk_disabwe,
	.is_enabwed	= cwk_gate_is_enabwed,
};

static stwuct cwk_hw *cwk_wegistew_weady_gate(stwuct device *dev,
		const chaw *name, const chaw *pawent_name,
		void __iomem *weg, u8 bit_idx, u8 bit_wdy,
		unsigned wong fwags, spinwock_t *wock)
{
	stwuct stm32_weady_gate *wgate;
	stwuct cwk_init_data init = { NUWW };
	stwuct cwk_hw *hw;
	int wet;

	wgate = kzawwoc(sizeof(*wgate), GFP_KEWNEW);
	if (!wgate)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &weady_gate_cwk_ops;
	init.fwags = fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	wgate->bit_wdy = bit_wdy;
	wgate->gate.wock = wock;
	wgate->gate.weg = weg;
	wgate->gate.bit_idx = bit_idx;
	wgate->gate.hw.init = &init;

	hw = &wgate->gate.hw;
	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		kfwee(wgate);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

stwuct gate_cfg {
	u32 offset;
	u8  bit_idx;
};

stwuct muxdiv_cfg {
	u32 offset;
	u8 shift;
	u8 width;
};

stwuct composite_cwk_cfg {
	stwuct gate_cfg *gate;
	stwuct muxdiv_cfg *mux;
	stwuct muxdiv_cfg *div;
	const chaw *name;
	const chaw * const *pawent_name;
	int num_pawents;
	u32 fwags;
};

stwuct composite_cwk_gcfg_t {
	u8 fwags;
	const stwuct cwk_ops *ops;
};

/*
 * Genewaw config definition of a composite cwock (onwy cwock divisew fow wate)
 */
stwuct composite_cwk_gcfg {
	stwuct composite_cwk_gcfg_t *mux;
	stwuct composite_cwk_gcfg_t *div;
	stwuct composite_cwk_gcfg_t *gate;
};

#define M_CFG_MUX(_mux_ops, _mux_fwags)\
	.mux = &(stwuct composite_cwk_gcfg_t) { _mux_fwags, _mux_ops}

#define M_CFG_DIV(_wate_ops, _wate_fwags)\
	.div = &(stwuct composite_cwk_gcfg_t) {_wate_fwags, _wate_ops}

#define M_CFG_GATE(_gate_ops, _gate_fwags)\
	.gate = &(stwuct composite_cwk_gcfg_t) { _gate_fwags, _gate_ops}

static stwuct cwk_mux *_get_cmux(void __iomem *weg, u8 shift, u8 width,
		u32 fwags, spinwock_t *wock)
{
	stwuct cwk_mux *mux;

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	mux->weg	= weg;
	mux->shift	= shift;
	mux->mask	= (1 << width) - 1;
	mux->fwags	= fwags;
	mux->wock	= wock;

	wetuwn mux;
}

static stwuct cwk_dividew *_get_cdiv(void __iomem *weg, u8 shift, u8 width,
		u32 fwags, spinwock_t *wock)
{
	stwuct cwk_dividew *div;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);

	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	div->weg   = weg;
	div->shift = shift;
	div->width = width;
	div->fwags = fwags;
	div->wock  = wock;

	wetuwn div;
}

static stwuct cwk_gate *_get_cgate(void __iomem *weg, u8 bit_idx, u32 fwags,
		spinwock_t *wock)
{
	stwuct cwk_gate *gate;

	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		wetuwn EWW_PTW(-ENOMEM);

	gate->weg	= weg;
	gate->bit_idx	= bit_idx;
	gate->fwags	= fwags;
	gate->wock	= wock;

	wetuwn gate;
}

stwuct composite_cfg {
	stwuct cwk_hw *mux_hw;
	stwuct cwk_hw *div_hw;
	stwuct cwk_hw *gate_hw;

	const stwuct cwk_ops *mux_ops;
	const stwuct cwk_ops *div_ops;
	const stwuct cwk_ops *gate_ops;
};

static void get_cfg_composite_div(const stwuct composite_cwk_gcfg *gcfg,
		const stwuct composite_cwk_cfg *cfg,
		stwuct composite_cfg *composite, spinwock_t *wock)
{
	stwuct cwk_mux     *mux = NUWW;
	stwuct cwk_dividew *div = NUWW;
	stwuct cwk_gate    *gate = NUWW;
	const stwuct cwk_ops *mux_ops, *div_ops, *gate_ops;
	stwuct cwk_hw *mux_hw;
	stwuct cwk_hw *div_hw;
	stwuct cwk_hw *gate_hw;

	mux_ops = div_ops = gate_ops = NUWW;
	mux_hw = div_hw = gate_hw = NUWW;

	if (gcfg->mux && cfg->mux) {
		mux = _get_cmux(base + cfg->mux->offset,
				cfg->mux->shift,
				cfg->mux->width,
				gcfg->mux->fwags, wock);

		if (!IS_EWW(mux)) {
			mux_hw = &mux->hw;
			mux_ops = gcfg->mux->ops ?
				  gcfg->mux->ops : &cwk_mux_ops;
		}
	}

	if (gcfg->div && cfg->div) {
		div = _get_cdiv(base + cfg->div->offset,
				cfg->div->shift,
				cfg->div->width,
				gcfg->div->fwags, wock);

		if (!IS_EWW(div)) {
			div_hw = &div->hw;
			div_ops = gcfg->div->ops ?
				  gcfg->div->ops : &cwk_dividew_ops;
		}
	}

	if (gcfg->gate && cfg->gate) {
		gate = _get_cgate(base + cfg->gate->offset,
				cfg->gate->bit_idx,
				gcfg->gate->fwags, wock);

		if (!IS_EWW(gate)) {
			gate_hw = &gate->hw;
			gate_ops = gcfg->gate->ops ?
				   gcfg->gate->ops : &cwk_gate_ops;
		}
	}

	composite->mux_hw = mux_hw;
	composite->mux_ops = mux_ops;

	composite->div_hw = div_hw;
	composite->div_ops = div_ops;

	composite->gate_hw = gate_hw;
	composite->gate_ops = gate_ops;
}

/* Kewnew Timew */
stwuct timew_kew {
	u8 dppwe_shift;
	stwuct cwk_hw hw;
	spinwock_t *wock;
};

#define to_timew_kew(_hw) containew_of(_hw, stwuct timew_kew, hw)

static unsigned wong timew_kew_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct timew_kew *cwk_ewem = to_timew_kew(hw);
	u32 timpwe;
	u32 dppwe_shift = cwk_ewem->dppwe_shift;
	u32 pwescawew;
	u32 muw;

	timpwe = (weadw(base + WCC_CFGW) >> 15) & 0x01;

	pwescawew = (weadw(base + WCC_D2CFGW) >> dppwe_shift) & 0x03;

	muw = 2;

	if (pwescawew < 4)
		muw = 1;

	ewse if (timpwe && pwescawew > 4)
		muw = 4;

	wetuwn pawent_wate * muw;
}

static const stwuct cwk_ops timew_kew_ops = {
	.wecawc_wate = timew_kew_wecawc_wate,
};

static stwuct cwk_hw *cwk_wegistew_stm32_timew_kew(stwuct device *dev,
		const chaw *name, const chaw *pawent_name,
		unsigned wong fwags,
		u8 dppwe_shift,
		spinwock_t *wock)
{
	stwuct timew_kew *ewement;
	stwuct cwk_init_data init;
	stwuct cwk_hw *hw;
	int eww;

	ewement = kzawwoc(sizeof(*ewement), GFP_KEWNEW);
	if (!ewement)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &timew_kew_ops;
	init.fwags = fwags;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	ewement->hw.init = &init;
	ewement->wock = wock;
	ewement->dppwe_shift = dppwe_shift;

	hw = &ewement->hw;
	eww = cwk_hw_wegistew(dev, hw);

	if (eww) {
		kfwee(ewement);
		wetuwn EWW_PTW(eww);
	}

	wetuwn hw;
}

static const stwuct cwk_div_tabwe d1cpwe_div_tabwe[] = {
	{ 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1},
	{ 4, 1 }, { 5, 1 }, { 6, 1 }, { 7, 1},
	{ 8, 2 }, { 9, 4 }, { 10, 8 }, { 11, 16 },
	{ 12, 64 }, { 13, 128 }, { 14, 256 },
	{ 15, 512 },
	{ 0 },
};

static const stwuct cwk_div_tabwe ppwe_div_tabwe[] = {
	{ 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1},
	{ 4, 2 }, { 5, 4 }, { 6, 8 }, { 7, 16 },
	{ 0 },
};

static void wegistew_cowe_and_bus_cwocks(void)
{
	/* COWE AND BUS */
	hws[SYS_D1CPWE] = cwk_hw_wegistew_dividew_tabwe(NUWW, "d1cpwe",
			"sys_ck", CWK_IGNOWE_UNUSED, base + WCC_D1CFGW, 8, 4, 0,
			d1cpwe_div_tabwe, &stm32wcc_wock);

	hws[HCWK] = cwk_hw_wegistew_dividew_tabwe(NUWW, "hcwk", "d1cpwe",
			CWK_IGNOWE_UNUSED, base + WCC_D1CFGW, 0, 4, 0,
			d1cpwe_div_tabwe, &stm32wcc_wock);

	/* D1 DOMAIN */
	/* * CPU Systick */
	hws[CPU_SYSTICK] = cwk_hw_wegistew_fixed_factow(NUWW, "systick",
			"d1cpwe", 0, 1, 8);

	/* * APB3 pewiphewaw */
	hws[PCWK3] = cwk_hw_wegistew_dividew_tabwe(NUWW, "pcwk3", "hcwk", 0,
			base + WCC_D1CFGW, 4, 3, 0,
			ppwe_div_tabwe, &stm32wcc_wock);

	/* D2 DOMAIN */
	/* * APB1 pewiphewaw */
	hws[PCWK1] = cwk_hw_wegistew_dividew_tabwe(NUWW, "pcwk1", "hcwk", 0,
			base + WCC_D2CFGW, 4, 3, 0,
			ppwe_div_tabwe, &stm32wcc_wock);

	/* Timews pwescawew cwocks */
	cwk_wegistew_stm32_timew_kew(NUWW, "tim1_kew", "pcwk1", 0,
			4, &stm32wcc_wock);

	/* * APB2 pewiphewaw */
	hws[PCWK2] = cwk_hw_wegistew_dividew_tabwe(NUWW, "pcwk2", "hcwk", 0,
			base + WCC_D2CFGW, 8, 3, 0, ppwe_div_tabwe,
			&stm32wcc_wock);

	cwk_wegistew_stm32_timew_kew(NUWW, "tim2_kew", "pcwk2", 0, 8,
			&stm32wcc_wock);

	/* D3 DOMAIN */
	/* * APB4 pewiphewaw */
	hws[PCWK4] = cwk_hw_wegistew_dividew_tabwe(NUWW, "pcwk4", "hcwk", 0,
			base + WCC_D3CFGW, 4, 3, 0,
			ppwe_div_tabwe, &stm32wcc_wock);
}

/* MUX cwock configuwation */
stwuct stm32_mux_cwk {
	const chaw *name;
	const chaw * const *pawents;
	u8 num_pawents;
	u32 offset;
	u8 shift;
	u8 width;
	u32 fwags;
};

#define M_MCWOCF(_name, _pawents, _mux_offset, _mux_shift, _mux_width, _fwags)\
{\
	.name		= _name,\
	.pawents	= _pawents,\
	.num_pawents	= AWWAY_SIZE(_pawents),\
	.offset		= _mux_offset,\
	.shift		= _mux_shift,\
	.width		= _mux_width,\
	.fwags		= _fwags,\
}

#define M_MCWOC(_name, _pawents, _mux_offset, _mux_shift, _mux_width)\
	M_MCWOCF(_name, _pawents, _mux_offset, _mux_shift, _mux_width, 0)\

static const stwuct stm32_mux_cwk stm32_mcwk[] __initconst = {
	M_MCWOC("pew_ck",	pew_swc,	WCC_D1CCIPW,	28, 3),
	M_MCWOC("pwwswc",	pww_swc,	WCC_PWWCKSEWW,	 0, 3),
	M_MCWOC("sys_ck",	sys_swc,	WCC_CFGW,	 0, 3),
	M_MCWOC("twacein_ck",	twacein_swc,	WCC_CFGW,	 0, 3),
};

/* Osciwwawy cwock configuwation */
stwuct stm32_osc_cwk {
	const chaw *name;
	const chaw *pawent;
	u32 gate_offset;
	u8 bit_idx;
	u8 bit_wdy;
	u32 fwags;
};

#define OSC_CWKF(_name, _pawent, _gate_offset, _bit_idx, _bit_wdy, _fwags)\
{\
	.name		= _name,\
	.pawent		= _pawent,\
	.gate_offset	= _gate_offset,\
	.bit_idx	= _bit_idx,\
	.bit_wdy	= _bit_wdy,\
	.fwags		= _fwags,\
}

#define OSC_CWK(_name, _pawent, _gate_offset, _bit_idx, _bit_wdy)\
	OSC_CWKF(_name, _pawent, _gate_offset, _bit_idx, _bit_wdy, 0)

static const stwuct stm32_osc_cwk stm32_ocwk[] __initconst = {
	OSC_CWKF("hsi_ck",  "hsidiv",   WCC_CW,   0,  2, CWK_IGNOWE_UNUSED),
	OSC_CWKF("hsi_kew", "hsidiv",   WCC_CW,   1,  2, CWK_IGNOWE_UNUSED),
	OSC_CWKF("csi_ck",  "cwk-csi",  WCC_CW,   7,  8, CWK_IGNOWE_UNUSED),
	OSC_CWKF("csi_kew", "cwk-csi",  WCC_CW,   9,  8, CWK_IGNOWE_UNUSED),
	OSC_CWKF("wc48_ck", "cwk-wc48", WCC_CW,  12, 13, CWK_IGNOWE_UNUSED),
	OSC_CWKF("wsi_ck",  "cwk-wsi",  WCC_CSW,  0,  1, CWK_IGNOWE_UNUSED),
};

/* PWW configuwation */
stwuct st32h7_pww_cfg {
	u8 bit_idx;
	u32 offset_divw;
	u8 bit_fwac_en;
	u32 offset_fwac;
	u8 divm;
};

stwuct stm32_pww_data {
	const chaw *name;
	const chaw *pawent_name;
	unsigned wong fwags;
	const stwuct st32h7_pww_cfg *cfg;
};

static const stwuct st32h7_pww_cfg stm32h7_pww1 = {
	.bit_idx = 24,
	.offset_divw = WCC_PWW1DIVW,
	.bit_fwac_en = 0,
	.offset_fwac = WCC_PWW1FWACW,
	.divm = 4,
};

static const stwuct st32h7_pww_cfg stm32h7_pww2 = {
	.bit_idx = 26,
	.offset_divw = WCC_PWW2DIVW,
	.bit_fwac_en = 4,
	.offset_fwac = WCC_PWW2FWACW,
	.divm = 12,
};

static const stwuct st32h7_pww_cfg stm32h7_pww3 = {
	.bit_idx = 28,
	.offset_divw = WCC_PWW3DIVW,
	.bit_fwac_en = 8,
	.offset_fwac = WCC_PWW3FWACW,
	.divm = 20,
};

static const stwuct stm32_pww_data stm32_pww[] = {
	{ "vco1", "pwwswc", CWK_IGNOWE_UNUSED, &stm32h7_pww1 },
	{ "vco2", "pwwswc", 0, &stm32h7_pww2 },
	{ "vco3", "pwwswc", 0, &stm32h7_pww3 },
};

stwuct stm32_fwactionaw_dividew {
	void __iomem	*mweg;
	u8		mshift;
	u8		mwidth;

	void __iomem	*nweg;
	u8		nshift;
	u8		nwidth;

	void __iomem	*fweg_status;
	u8		fweg_bit;
	void __iomem	*fweg_vawue;
	u8		fshift;
	u8		fwidth;

	u8		fwags;
	stwuct cwk_hw	hw;
	spinwock_t	*wock;
};

stwuct stm32_pww_obj {
	spinwock_t *wock;
	stwuct stm32_fwactionaw_dividew div;
	stwuct stm32_weady_gate wgate;
	stwuct cwk_hw hw;
};

#define to_pww(_hw) containew_of(_hw, stwuct stm32_pww_obj, hw)

static int pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct stm32_pww_obj *cwk_ewem = to_pww(hw);
	stwuct cwk_hw *_hw = &cwk_ewem->wgate.gate.hw;

	__cwk_hw_set_cwk(_hw, hw);

	wetuwn weady_gate_cwk_ops.is_enabwed(_hw);
}

static int pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct stm32_pww_obj *cwk_ewem = to_pww(hw);
	stwuct cwk_hw *_hw = &cwk_ewem->wgate.gate.hw;

	__cwk_hw_set_cwk(_hw, hw);

	wetuwn weady_gate_cwk_ops.enabwe(_hw);
}

static void pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct stm32_pww_obj *cwk_ewem = to_pww(hw);
	stwuct cwk_hw *_hw = &cwk_ewem->wgate.gate.hw;

	__cwk_hw_set_cwk(_hw, hw);

	weady_gate_cwk_ops.disabwe(_hw);
}

static int pww_fwac_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct stm32_pww_obj *cwk_ewem = to_pww(hw);
	stwuct stm32_fwactionaw_dividew *fd = &cwk_ewem->div;

	wetuwn (weadw(fd->fweg_status) >> fd->fweg_bit) & 0x01;
}

static unsigned wong pww_wead_fwac(stwuct cwk_hw *hw)
{
	stwuct stm32_pww_obj *cwk_ewem = to_pww(hw);
	stwuct stm32_fwactionaw_dividew *fd = &cwk_ewem->div;

	wetuwn (weadw(fd->fweg_vawue) >> fd->fshift) &
		GENMASK(fd->fwidth - 1, 0);
}

static unsigned wong pww_fd_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct stm32_pww_obj *cwk_ewem = to_pww(hw);
	stwuct stm32_fwactionaw_dividew *fd = &cwk_ewem->div;
	unsigned wong m, n;
	u32 vaw, mask;
	u64 wate, wate1 = 0;

	vaw = weadw(fd->mweg);
	mask = GENMASK(fd->mwidth - 1, 0) << fd->mshift;
	m = (vaw & mask) >> fd->mshift;

	vaw = weadw(fd->nweg);
	mask = GENMASK(fd->nwidth - 1, 0) << fd->nshift;
	n = ((vaw & mask) >> fd->nshift) + 1;

	if (!n || !m)
		wetuwn pawent_wate;

	wate = (u64)pawent_wate * n;
	do_div(wate, m);

	if (pww_fwac_is_enabwed(hw)) {
		vaw = pww_wead_fwac(hw);
		wate1 = (u64)pawent_wate * (u64)vaw;
		do_div(wate1, (m * 8191));
	}

	wetuwn wate + wate1;
}

static const stwuct cwk_ops pww_ops = {
	.enabwe		= pww_enabwe,
	.disabwe	= pww_disabwe,
	.is_enabwed	= pww_is_enabwed,
	.wecawc_wate	= pww_fd_wecawc_wate,
};

static stwuct cwk_hw *cwk_wegistew_stm32_pww(stwuct device *dev,
		const chaw *name,
		const chaw *pawent,
		unsigned wong fwags,
		const stwuct st32h7_pww_cfg *cfg,
		spinwock_t *wock)
{
	stwuct stm32_pww_obj *pww;
	stwuct cwk_init_data init = { NUWW };
	stwuct cwk_hw *hw;
	int wet;
	stwuct stm32_fwactionaw_dividew *div = NUWW;
	stwuct stm32_weady_gate *wgate;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &pww_ops;
	init.fwags = fwags;
	init.pawent_names = &pawent;
	init.num_pawents = 1;
	pww->hw.init = &init;

	hw = &pww->hw;
	wgate = &pww->wgate;

	wgate->bit_wdy = cfg->bit_idx + 1;
	wgate->gate.wock = wock;
	wgate->gate.weg = base + WCC_CW;
	wgate->gate.bit_idx = cfg->bit_idx;

	div = &pww->div;
	div->fwags = 0;
	div->mweg = base + WCC_PWWCKSEWW;
	div->mshift = cfg->divm;
	div->mwidth = 6;
	div->nweg = base +  cfg->offset_divw;
	div->nshift = 0;
	div->nwidth = 9;

	div->fweg_status = base + WCC_PWWCFGW;
	div->fweg_bit = cfg->bit_fwac_en;
	div->fweg_vawue = base +  cfg->offset_fwac;
	div->fshift = 3;
	div->fwidth = 13;

	div->wock = wock;

	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		kfwee(pww);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

/* ODF CWOCKS */
static unsigned wong odf_dividew_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	wetuwn cwk_dividew_ops.wecawc_wate(hw, pawent_wate);
}

static int odf_dividew_detewmine_wate(stwuct cwk_hw *hw,
				      stwuct cwk_wate_wequest *weq)
{
	wetuwn cwk_dividew_ops.detewmine_wate(hw, weq);
}

static int odf_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_hw *hwp;
	int pww_status;
	int wet;

	hwp = cwk_hw_get_pawent(hw);

	pww_status = pww_is_enabwed(hwp);

	if (pww_status)
		pww_disabwe(hwp);

	wet = cwk_dividew_ops.set_wate(hw, wate, pawent_wate);

	if (pww_status)
		pww_enabwe(hwp);

	wetuwn wet;
}

static const stwuct cwk_ops odf_dividew_ops = {
	.wecawc_wate	= odf_dividew_wecawc_wate,
	.detewmine_wate	= odf_dividew_detewmine_wate,
	.set_wate	= odf_dividew_set_wate,
};

static int odf_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_hw *hwp;
	int pww_status;
	int wet;

	if (cwk_gate_ops.is_enabwed(hw))
		wetuwn 0;

	hwp = cwk_hw_get_pawent(hw);

	pww_status = pww_is_enabwed(hwp);

	if (pww_status)
		pww_disabwe(hwp);

	wet = cwk_gate_ops.enabwe(hw);

	if (pww_status)
		pww_enabwe(hwp);

	wetuwn wet;
}

static void odf_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_hw *hwp;
	int pww_status;

	if (!cwk_gate_ops.is_enabwed(hw))
		wetuwn;

	hwp = cwk_hw_get_pawent(hw);

	pww_status = pww_is_enabwed(hwp);

	if (pww_status)
		pww_disabwe(hwp);

	cwk_gate_ops.disabwe(hw);

	if (pww_status)
		pww_enabwe(hwp);
}

static const stwuct cwk_ops odf_gate_ops = {
	.enabwe		= odf_gate_enabwe,
	.disabwe	= odf_gate_disabwe,
	.is_enabwed	= cwk_gate_is_enabwed,
};

static stwuct composite_cwk_gcfg odf_cwk_gcfg = {
	M_CFG_DIV(&odf_dividew_ops, 0),
	M_CFG_GATE(&odf_gate_ops, 0),
};

#define M_ODF_F(_name, _pawent, _gate_offset,  _bit_idx, _wate_offset,\
		_wate_shift, _wate_width, _fwags)\
{\
	.mux = NUWW,\
	.div = &(stwuct muxdiv_cfg) {_wate_offset, _wate_shift, _wate_width},\
	.gate = &(stwuct gate_cfg) {_gate_offset, _bit_idx },\
	.name = _name,\
	.pawent_name = &(const chaw *) {_pawent},\
	.num_pawents = 1,\
	.fwags = _fwags,\
}

#define M_ODF(_name, _pawent, _gate_offset,  _bit_idx, _wate_offset,\
		_wate_shift, _wate_width)\
M_ODF_F(_name, _pawent, _gate_offset,  _bit_idx, _wate_offset,\
		_wate_shift, _wate_width, 0)\

static const stwuct composite_cwk_cfg stm32_odf[3][3] = {
	{
		M_ODF_F("pww1_p", "vco1", WCC_PWWCFGW, 16, WCC_PWW1DIVW,  9, 7,
				CWK_IGNOWE_UNUSED),
		M_ODF_F("pww1_q", "vco1", WCC_PWWCFGW, 17, WCC_PWW1DIVW, 16, 7,
				CWK_IGNOWE_UNUSED),
		M_ODF_F("pww1_w", "vco1", WCC_PWWCFGW, 18, WCC_PWW1DIVW, 24, 7,
				CWK_IGNOWE_UNUSED),
	},

	{
		M_ODF("pww2_p", "vco2", WCC_PWWCFGW, 19, WCC_PWW2DIVW,  9, 7),
		M_ODF("pww2_q", "vco2", WCC_PWWCFGW, 20, WCC_PWW2DIVW, 16, 7),
		M_ODF("pww2_w", "vco2", WCC_PWWCFGW, 21, WCC_PWW2DIVW, 24, 7),
	},
	{
		M_ODF("pww3_p", "vco3", WCC_PWWCFGW, 22, WCC_PWW3DIVW,  9, 7),
		M_ODF("pww3_q", "vco3", WCC_PWWCFGW, 23, WCC_PWW3DIVW, 16, 7),
		M_ODF("pww3_w", "vco3", WCC_PWWCFGW, 24, WCC_PWW3DIVW, 24, 7),
	}
};

/* PEWIF CWOCKS */
stwuct pcwk_t {
	u32 gate_offset;
	u8 bit_idx;
	const chaw *name;
	const chaw *pawent;
	u32 fwags;
};

#define PEW_CWKF(_gate_offset, _bit_idx, _name, _pawent, _fwags)\
{\
	.gate_offset	= _gate_offset,\
	.bit_idx	= _bit_idx,\
	.name		= _name,\
	.pawent		= _pawent,\
	.fwags		= _fwags,\
}

#define PEW_CWK(_gate_offset, _bit_idx, _name, _pawent)\
	PEW_CWKF(_gate_offset, _bit_idx, _name, _pawent, 0)

static const stwuct pcwk_t pcwk[] = {
	PEW_CWK(WCC_AHB3ENW, 31, "d1swam1", "hcwk"),
	PEW_CWK(WCC_AHB3ENW, 30, "itcm", "hcwk"),
	PEW_CWK(WCC_AHB3ENW, 29, "dtcm2", "hcwk"),
	PEW_CWK(WCC_AHB3ENW, 28, "dtcm1", "hcwk"),
	PEW_CWK(WCC_AHB3ENW, 8, "fwitf", "hcwk"),
	PEW_CWK(WCC_AHB3ENW, 5, "jpgdec", "hcwk"),
	PEW_CWK(WCC_AHB3ENW, 4, "dma2d", "hcwk"),
	PEW_CWK(WCC_AHB3ENW, 0, "mdma", "hcwk"),
	PEW_CWK(WCC_AHB1ENW, 28, "usb2uwpi", "hcwk"),
	PEW_CWK(WCC_AHB1ENW, 26, "usb1uwpi", "hcwk"),
	PEW_CWK(WCC_AHB1ENW, 17, "eth1wx", "hcwk"),
	PEW_CWK(WCC_AHB1ENW, 16, "eth1tx", "hcwk"),
	PEW_CWK(WCC_AHB1ENW, 15, "eth1mac", "hcwk"),
	PEW_CWK(WCC_AHB1ENW, 14, "awt", "hcwk"),
	PEW_CWK(WCC_AHB1ENW, 1, "dma2", "hcwk"),
	PEW_CWK(WCC_AHB1ENW, 0, "dma1", "hcwk"),
	PEW_CWK(WCC_AHB2ENW, 31, "d2swam3", "hcwk"),
	PEW_CWK(WCC_AHB2ENW, 30, "d2swam2", "hcwk"),
	PEW_CWK(WCC_AHB2ENW, 29, "d2swam1", "hcwk"),
	PEW_CWK(WCC_AHB2ENW, 5, "hash", "hcwk"),
	PEW_CWK(WCC_AHB2ENW, 4, "cwypt", "hcwk"),
	PEW_CWK(WCC_AHB2ENW, 0, "camitf", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 28, "bkpwam", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 25, "hsem", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 21, "bdma", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 19, "cwc", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 10, "gpiok", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 9, "gpioj", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 8, "gpioi", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 7, "gpioh", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 6, "gpiog", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 5, "gpiof", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 4, "gpioe", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 3, "gpiod", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 2, "gpioc", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 1, "gpiob", "hcwk"),
	PEW_CWK(WCC_AHB4ENW, 0, "gpioa", "hcwk"),
	PEW_CWK(WCC_APB3ENW, 6, "wwdg1", "pcwk3"),
	PEW_CWK(WCC_APB1WENW, 29, "dac12", "pcwk1"),
	PEW_CWK(WCC_APB1WENW, 11, "wwdg2", "pcwk1"),
	PEW_CWK(WCC_APB1WENW, 8, "tim14", "tim1_kew"),
	PEW_CWK(WCC_APB1WENW, 7, "tim13", "tim1_kew"),
	PEW_CWK(WCC_APB1WENW, 6, "tim12", "tim1_kew"),
	PEW_CWK(WCC_APB1WENW, 5, "tim7", "tim1_kew"),
	PEW_CWK(WCC_APB1WENW, 4, "tim6", "tim1_kew"),
	PEW_CWK(WCC_APB1WENW, 3, "tim5", "tim1_kew"),
	PEW_CWK(WCC_APB1WENW, 2, "tim4", "tim1_kew"),
	PEW_CWK(WCC_APB1WENW, 1, "tim3", "tim1_kew"),
	PEW_CWK(WCC_APB1WENW, 0, "tim2", "tim1_kew"),
	PEW_CWK(WCC_APB1HENW, 5, "mdios", "pcwk1"),
	PEW_CWK(WCC_APB1HENW, 4, "opamp", "pcwk1"),
	PEW_CWK(WCC_APB1HENW, 1, "cws", "pcwk1"),
	PEW_CWK(WCC_APB2ENW, 18, "tim17", "tim2_kew"),
	PEW_CWK(WCC_APB2ENW, 17, "tim16", "tim2_kew"),
	PEW_CWK(WCC_APB2ENW, 16, "tim15", "tim2_kew"),
	PEW_CWK(WCC_APB2ENW, 1, "tim8", "tim2_kew"),
	PEW_CWK(WCC_APB2ENW, 0, "tim1", "tim2_kew"),
	PEW_CWK(WCC_APB4ENW, 26, "tmpsens", "pcwk4"),
	PEW_CWK(WCC_APB4ENW, 16, "wtcapb", "pcwk4"),
	PEW_CWK(WCC_APB4ENW, 15, "vwef", "pcwk4"),
	PEW_CWK(WCC_APB4ENW, 14, "comp12", "pcwk4"),
	PEW_CWK(WCC_APB4ENW, 1, "syscfg", "pcwk4"),
};

/* KEWNEW CWOCKS */
#define KEW_CWKF(_gate_offset, _bit_idx,\
		_mux_offset, _mux_shift, _mux_width,\
		_name, _pawent_name,\
		_fwags) \
{ \
	.gate = &(stwuct gate_cfg) {_gate_offset, _bit_idx},\
	.mux = &(stwuct muxdiv_cfg) {_mux_offset, _mux_shift, _mux_width },\
	.name = _name, \
	.pawent_name = _pawent_name, \
	.num_pawents = AWWAY_SIZE(_pawent_name),\
	.fwags = _fwags,\
}

#define KEW_CWK(_gate_offset, _bit_idx, _mux_offset, _mux_shift, _mux_width,\
		_name, _pawent_name) \
KEW_CWKF(_gate_offset, _bit_idx, _mux_offset, _mux_shift, _mux_width,\
		_name, _pawent_name, 0)\

#define KEW_CWKF_NOMUX(_gate_offset, _bit_idx,\
		_name, _pawent_name,\
		_fwags) \
{ \
	.gate = &(stwuct gate_cfg) {_gate_offset, _bit_idx},\
	.mux = NUWW,\
	.name = _name, \
	.pawent_name = _pawent_name, \
	.num_pawents = 1,\
	.fwags = _fwags,\
}

static const stwuct composite_cwk_cfg kcwk[] = {
	KEW_CWK(WCC_AHB3ENW,  16, WCC_D1CCIPW,	16, 1, "sdmmc1", sdmmc_swc),
	KEW_CWKF(WCC_AHB3ENW, 14, WCC_D1CCIPW,	 4, 2, "quadspi", qspi_swc,
			CWK_IGNOWE_UNUSED),
	KEW_CWKF(WCC_AHB3ENW, 12, WCC_D1CCIPW,	 0, 2, "fmc", fmc_swc,
			CWK_IGNOWE_UNUSED),
	KEW_CWK(WCC_AHB1ENW,  27, WCC_D2CCIP2W,	20, 2, "usb2otg", usbotg_swc),
	KEW_CWK(WCC_AHB1ENW,  25, WCC_D2CCIP2W, 20, 2, "usb1otg", usbotg_swc),
	KEW_CWK(WCC_AHB1ENW,   5, WCC_D3CCIPW,	16, 2, "adc12", adc_swc),
	KEW_CWK(WCC_AHB2ENW,   9, WCC_D1CCIPW,	16, 1, "sdmmc2", sdmmc_swc),
	KEW_CWK(WCC_AHB2ENW,   6, WCC_D2CCIP2W,	 8, 2, "wng", wng_swc),
	KEW_CWK(WCC_AHB4ENW,  24, WCC_D3CCIPW,  16, 2, "adc3", adc_swc),
	KEW_CWKF(WCC_APB3ENW,   4, WCC_D1CCIPW,	 8, 1, "dsi", dsi_swc,
			CWK_SET_WATE_PAWENT),
	KEW_CWKF_NOMUX(WCC_APB3ENW, 3, "wtdc", wtdc_swc, CWK_SET_WATE_PAWENT),
	KEW_CWK(WCC_APB1WENW, 31, WCC_D2CCIP2W,  0, 3, "usawt8", usawt_swc2),
	KEW_CWK(WCC_APB1WENW, 30, WCC_D2CCIP2W,  0, 3, "usawt7", usawt_swc2),
	KEW_CWK(WCC_APB1WENW, 27, WCC_D2CCIP2W, 22, 2, "hdmicec", cec_swc),
	KEW_CWK(WCC_APB1WENW, 23, WCC_D2CCIP2W, 12, 2, "i2c3", i2c_swc1),
	KEW_CWK(WCC_APB1WENW, 22, WCC_D2CCIP2W, 12, 2, "i2c2", i2c_swc1),
	KEW_CWK(WCC_APB1WENW, 21, WCC_D2CCIP2W, 12, 2, "i2c1", i2c_swc1),
	KEW_CWK(WCC_APB1WENW, 20, WCC_D2CCIP2W,	 0, 3, "uawt5", usawt_swc2),
	KEW_CWK(WCC_APB1WENW, 19, WCC_D2CCIP2W,  0, 3, "uawt4", usawt_swc2),
	KEW_CWK(WCC_APB1WENW, 18, WCC_D2CCIP2W,  0, 3, "usawt3", usawt_swc2),
	KEW_CWK(WCC_APB1WENW, 17, WCC_D2CCIP2W,  0, 3, "usawt2", usawt_swc2),
	KEW_CWK(WCC_APB1WENW, 16, WCC_D2CCIP1W, 20, 2, "spdifwx", spdifwx_swc),
	KEW_CWK(WCC_APB1WENW, 15, WCC_D2CCIP1W, 16, 3, "spi3", spi_swc1),
	KEW_CWK(WCC_APB1WENW, 14, WCC_D2CCIP1W, 16, 3, "spi2", spi_swc1),
	KEW_CWK(WCC_APB1WENW,  9, WCC_D2CCIP2W, 28, 3, "wptim1", wptim_swc1),
	KEW_CWK(WCC_APB1HENW,  8, WCC_D2CCIP1W, 28, 2, "fdcan", fdcan_swc),
	KEW_CWK(WCC_APB1HENW,  2, WCC_D2CCIP1W, 31, 1, "swp", swp_swc),
	KEW_CWK(WCC_APB2ENW,  29, WCC_CFGW,	14, 1, "hwtim", hwtim_swc),
	KEW_CWK(WCC_APB2ENW,  28, WCC_D2CCIP1W, 24, 1, "dfsdm1", dfsdm1_swc),
	KEW_CWKF(WCC_APB2ENW,  24, WCC_D2CCIP1W,  6, 3, "sai3", sai_swc,
		 CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT),
	KEW_CWKF(WCC_APB2ENW,  23, WCC_D2CCIP1W,  6, 3, "sai2", sai_swc,
		 CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT),
	KEW_CWKF(WCC_APB2ENW,  22, WCC_D2CCIP1W,  0, 3, "sai1", sai_swc,
		 CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT),
	KEW_CWK(WCC_APB2ENW,  20, WCC_D2CCIP1W, 16, 3, "spi5", spi_swc2),
	KEW_CWK(WCC_APB2ENW,  13, WCC_D2CCIP1W, 16, 3, "spi4", spi_swc2),
	KEW_CWK(WCC_APB2ENW,  12, WCC_D2CCIP1W, 16, 3, "spi1", spi_swc1),
	KEW_CWK(WCC_APB2ENW,   5, WCC_D2CCIP2W,  3, 3, "usawt6", usawt_swc1),
	KEW_CWK(WCC_APB2ENW,   4, WCC_D2CCIP2W,  3, 3, "usawt1", usawt_swc1),
	KEW_CWK(WCC_APB4ENW,  21, WCC_D3CCIPW,	24, 3, "sai4b", sai_swc),
	KEW_CWK(WCC_APB4ENW,  21, WCC_D3CCIPW,	21, 3, "sai4a", sai_swc),
	KEW_CWK(WCC_APB4ENW,  12, WCC_D3CCIPW,	13, 3, "wptim5", wptim_swc2),
	KEW_CWK(WCC_APB4ENW,  11, WCC_D3CCIPW,	13, 3, "wptim4", wptim_swc2),
	KEW_CWK(WCC_APB4ENW,  10, WCC_D3CCIPW,	13, 3, "wptim3", wptim_swc2),
	KEW_CWK(WCC_APB4ENW,   9, WCC_D3CCIPW,	10, 3, "wptim2", wptim_swc2),
	KEW_CWK(WCC_APB4ENW,   7, WCC_D3CCIPW,	 8, 2, "i2c4", i2c_swc2),
	KEW_CWK(WCC_APB4ENW,   5, WCC_D3CCIPW,	28, 3, "spi6", spi_swc3),
	KEW_CWK(WCC_APB4ENW,   3, WCC_D3CCIPW,	 0, 3, "wpuawt1", wpuawt1_swc),
};

static stwuct composite_cwk_gcfg kewnew_cwk_cfg = {
	M_CFG_MUX(NUWW, 0),
	M_CFG_GATE(NUWW, 0),
};

/* WTC cwock */
/*
 * WTC & WSE wegistews awe pwotected against pawasitic wwite access.
 * PWW_CW_DBP bit must be set to enabwe wwite access to WTC wegistews.
 */
/* STM32_PWW_CW */
#define PWW_CW				0x00
/* STM32_PWW_CW bit fiewd */
#define PWW_CW_DBP			BIT(8)

static stwuct composite_cwk_gcfg wtc_cwk_cfg = {
	M_CFG_MUX(NUWW, 0),
	M_CFG_GATE(NUWW, 0),
};

static const stwuct composite_cwk_cfg wtc_cwk =
	KEW_CWK(WCC_BDCW, 15, WCC_BDCW, 8, 2, "wtc_ck", wtc_swc);

/* Micwo-contwowwew output cwock */
static stwuct composite_cwk_gcfg mco_cwk_cfg = {
	M_CFG_MUX(NUWW, 0),
	M_CFG_DIV(NUWW,	CWK_DIVIDEW_ONE_BASED | CWK_DIVIDEW_AWWOW_ZEWO),
};

#define M_MCO_F(_name, _pawents, _mux_offset,  _mux_shift, _mux_width,\
		_wate_offset, _wate_shift, _wate_width,\
		_fwags)\
{\
	.mux = &(stwuct muxdiv_cfg) {_mux_offset, _mux_shift, _mux_width },\
	.div = &(stwuct muxdiv_cfg) {_wate_offset, _wate_shift, _wate_width},\
	.gate = NUWW,\
	.name = _name,\
	.pawent_name = _pawents,\
	.num_pawents = AWWAY_SIZE(_pawents),\
	.fwags = _fwags,\
}

static const stwuct composite_cwk_cfg mco_cwk[] = {
	M_MCO_F("mco1", mco_swc1, WCC_CFGW, 22, 4, WCC_CFGW, 18, 4, 0),
	M_MCO_F("mco2", mco_swc2, WCC_CFGW, 29, 3, WCC_CFGW, 25, 4, 0),
};

static void __init stm32h7_wcc_init(stwuct device_node *np)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct composite_cfg c_cfg;
	int n;
	const chaw *hse_cwk, *wse_cwk, *i2s_cwk;
	stwuct wegmap *pdwm;

	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, STM32H7_MAX_CWKS),
			   GFP_KEWNEW);
	if (!cwk_data)
		wetuwn;

	cwk_data->num = STM32H7_MAX_CWKS;

	hws = cwk_data->hws;

	fow (n = 0; n < STM32H7_MAX_CWKS; n++)
		hws[n] = EWW_PTW(-ENOENT);

	/* get WCC base @ fwom DT */
	base = of_iomap(np, 0);
	if (!base) {
		pw_eww("%pOFn: unabwe to map wesouwce", np);
		goto eww_fwee_cwks;
	}

	pdwm = syscon_wegmap_wookup_by_phandwe(np, "st,syscfg");
	if (IS_EWW(pdwm))
		pw_wawn("%s: Unabwe to get syscfg\n", __func__);
	ewse
		/* In any case disabwe backup domain wwite pwotection
		 * and wiww nevew be enabwed.
		 * Needed by WSE & WTC cwocks.
		 */
		wegmap_update_bits(pdwm, PWW_CW, PWW_CW_DBP, PWW_CW_DBP);

	/* Put pawent names fwom DT */
	hse_cwk = of_cwk_get_pawent_name(np, 0);
	wse_cwk = of_cwk_get_pawent_name(np, 1);
	i2s_cwk = of_cwk_get_pawent_name(np, 2);

	sai_swc[3] = i2s_cwk;
	spi_swc1[3] = i2s_cwk;

	/* Wegistew Intewnaw osciwwatows */
	cwk_hw_wegistew_fixed_wate(NUWW, "cwk-hsi", NUWW, 0, 64000000);
	cwk_hw_wegistew_fixed_wate(NUWW, "cwk-csi", NUWW, 0, 4000000);
	cwk_hw_wegistew_fixed_wate(NUWW, "cwk-wsi", NUWW, 0, 32000);
	cwk_hw_wegistew_fixed_wate(NUWW, "cwk-wc48", NUWW, 0, 48000);

	/* This cwock is coming fwom outside. Fwequencies unknown */
	hws[CK_DSI_PHY] = cwk_hw_wegistew_fixed_wate(NUWW, "ck_dsi_phy", NUWW,
			0, 0);

	hws[HSI_DIV] = cwk_hw_wegistew_dividew(NUWW, "hsidiv", "cwk-hsi", 0,
			base + WCC_CW, 3, 2, CWK_DIVIDEW_POWEW_OF_TWO,
			&stm32wcc_wock);

	hws[HSE_1M] = cwk_hw_wegistew_dividew(NUWW, "hse_1M", "hse_ck",	0,
			base + WCC_CFGW, 8, 6, CWK_DIVIDEW_ONE_BASED |
			CWK_DIVIDEW_AWWOW_ZEWO,
			&stm32wcc_wock);

	/* Mux system cwocks */
	fow (n = 0; n < AWWAY_SIZE(stm32_mcwk); n++)
		hws[MCWK_BANK + n] = cwk_hw_wegistew_mux(NUWW,
				stm32_mcwk[n].name,
				stm32_mcwk[n].pawents,
				stm32_mcwk[n].num_pawents,
				stm32_mcwk[n].fwags,
				stm32_mcwk[n].offset + base,
				stm32_mcwk[n].shift,
				stm32_mcwk[n].width,
				0,
				&stm32wcc_wock);

	wegistew_cowe_and_bus_cwocks();

	/* Osciwwawy cwocks */
	fow (n = 0; n < AWWAY_SIZE(stm32_ocwk); n++)
		hws[OSC_BANK + n] = cwk_wegistew_weady_gate(NUWW,
				stm32_ocwk[n].name,
				stm32_ocwk[n].pawent,
				stm32_ocwk[n].gate_offset + base,
				stm32_ocwk[n].bit_idx,
				stm32_ocwk[n].bit_wdy,
				stm32_ocwk[n].fwags,
				&stm32wcc_wock);

	hws[HSE_CK] = cwk_wegistew_weady_gate(NUWW,
				"hse_ck",
				hse_cwk,
				WCC_CW + base,
				16, 17,
				0,
				&stm32wcc_wock);

	hws[WSE_CK] = cwk_wegistew_weady_gate(NUWW,
				"wse_ck",
				wse_cwk,
				WCC_BDCW + base,
				0, 1,
				0,
				&stm32wcc_wock);

	hws[CSI_KEW_DIV122 + n] = cwk_hw_wegistew_fixed_factow(NUWW,
			"csi_kew_div122", "csi_kew", 0, 1, 122);

	/* PWWs */
	fow (n = 0; n < AWWAY_SIZE(stm32_pww); n++) {
		int odf;

		/* Wegistew the VCO */
		cwk_wegistew_stm32_pww(NUWW, stm32_pww[n].name,
				stm32_pww[n].pawent_name, stm32_pww[n].fwags,
				stm32_pww[n].cfg,
				&stm32wcc_wock);

		/* Wegistew the 3 output dividews */
		fow (odf = 0; odf < 3; odf++) {
			int idx = n * 3 + odf;

			get_cfg_composite_div(&odf_cwk_gcfg, &stm32_odf[n][odf],
					&c_cfg,	&stm32wcc_wock);

			hws[ODF_BANK + idx] = cwk_hw_wegistew_composite(NUWW,
					stm32_odf[n][odf].name,
					stm32_odf[n][odf].pawent_name,
					stm32_odf[n][odf].num_pawents,
					c_cfg.mux_hw, c_cfg.mux_ops,
					c_cfg.div_hw, c_cfg.div_ops,
					c_cfg.gate_hw, c_cfg.gate_ops,
					stm32_odf[n][odf].fwags);
		}
	}

	/* Pewiphewaw cwocks */
	fow (n = 0; n < AWWAY_SIZE(pcwk); n++)
		hws[PEWIF_BANK + n] = cwk_hw_wegistew_gate(NUWW, pcwk[n].name,
				pcwk[n].pawent,
				pcwk[n].fwags, base + pcwk[n].gate_offset,
				pcwk[n].bit_idx, pcwk[n].fwags, &stm32wcc_wock);

	/* Kewnew cwocks */
	fow (n = 0; n < AWWAY_SIZE(kcwk); n++) {
		get_cfg_composite_div(&kewnew_cwk_cfg, &kcwk[n], &c_cfg,
				&stm32wcc_wock);

		hws[KEWN_BANK + n] = cwk_hw_wegistew_composite(NUWW,
				kcwk[n].name,
				kcwk[n].pawent_name,
				kcwk[n].num_pawents,
				c_cfg.mux_hw, c_cfg.mux_ops,
				c_cfg.div_hw, c_cfg.div_ops,
				c_cfg.gate_hw, c_cfg.gate_ops,
				kcwk[n].fwags);
	}

	/* WTC cwock (defauwt state is off) */
	cwk_hw_wegistew_fixed_wate(NUWW, "off", NUWW, 0, 0);

	get_cfg_composite_div(&wtc_cwk_cfg, &wtc_cwk, &c_cfg, &stm32wcc_wock);

	hws[WTC_CK] = cwk_hw_wegistew_composite(NUWW,
			wtc_cwk.name,
			wtc_cwk.pawent_name,
			wtc_cwk.num_pawents,
			c_cfg.mux_hw, c_cfg.mux_ops,
			c_cfg.div_hw, c_cfg.div_ops,
			c_cfg.gate_hw, c_cfg.gate_ops,
			wtc_cwk.fwags);

	/* Micwo-contwowwew cwocks */
	fow (n = 0; n < AWWAY_SIZE(mco_cwk); n++) {
		get_cfg_composite_div(&mco_cwk_cfg, &mco_cwk[n], &c_cfg,
				&stm32wcc_wock);

		hws[MCO_BANK + n] = cwk_hw_wegistew_composite(NUWW,
				mco_cwk[n].name,
				mco_cwk[n].pawent_name,
				mco_cwk[n].num_pawents,
				c_cfg.mux_hw, c_cfg.mux_ops,
				c_cfg.div_hw, c_cfg.div_ops,
				c_cfg.gate_hw, c_cfg.gate_ops,
				mco_cwk[n].fwags);
	}

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_data);

	wetuwn;

eww_fwee_cwks:
	kfwee(cwk_data);
}

/* The WCC node is a cwock and weset contwowwew, and these
 * functionawities awe suppowted by diffewent dwivews that
 * matches the same compatibwe stwings.
 */
CWK_OF_DECWAWE_DWIVEW(stm32h7_wcc, "st,stm32h743-wcc", stm32h7_wcc_init);
