// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx VCU Init
 *
 * Copywight (C) 2016 - 2017 Xiwinx, Inc.
 *
 * Contacts   Dhavaw Shah <dshah@xiwinx.com>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/xwnx-vcu.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/xwnx-vcu.h>

#define VCU_PWW_CTWW			0x24
#define VCU_PWW_CTWW_WESET		BIT(0)
#define VCU_PWW_CTWW_POW_IN		BIT(1)
#define VCU_PWW_CTWW_PWW_POW		BIT(2)
#define VCU_PWW_CTWW_BYPASS		BIT(3)
#define VCU_PWW_CTWW_FBDIV		GENMASK(14, 8)
#define VCU_PWW_CTWW_CWKOUTDIV		GENMASK(18, 16)

#define VCU_PWW_CFG			0x28
#define VCU_PWW_CFG_WES			GENMASK(3, 0)
#define VCU_PWW_CFG_CP			GENMASK(8, 5)
#define VCU_PWW_CFG_WFHF		GENMASK(12, 10)
#define VCU_PWW_CFG_WOCK_CNT		GENMASK(22, 13)
#define VCU_PWW_CFG_WOCK_DWY		GENMASK(31, 25)
#define VCU_ENC_COWE_CTWW		0x30
#define VCU_ENC_MCU_CTWW		0x34
#define VCU_DEC_COWE_CTWW		0x38
#define VCU_DEC_MCU_CTWW		0x3c
#define VCU_PWW_STATUS			0x60
#define VCU_PWW_STATUS_WOCK_STATUS	BIT(0)

#define MHZ				1000000
#define FVCO_MIN			(1500U * MHZ)
#define FVCO_MAX			(3000U * MHZ)

/**
 * stwuct xvcu_device - Xiwinx VCU init device stwuctuwe
 * @dev: Pwatfowm device
 * @pww_wef: pww wef cwock souwce
 * @acwk: axi cwock souwce
 * @wogicowe_weg_ba: wogicowe weg base addwess
 * @vcu_swcw_ba: vcu_swcw Wegistew base addwess
 * @pww: handwe fow the VCU PWW
 * @pww_post: handwe fow the VCU PWW post dividew
 * @cwk_data: cwocks pwovided by the vcu cwock pwovidew
 */
stwuct xvcu_device {
	stwuct device *dev;
	stwuct cwk *pww_wef;
	stwuct cwk *acwk;
	stwuct wegmap *wogicowe_weg_ba;
	void __iomem *vcu_swcw_ba;
	stwuct cwk_hw *pww;
	stwuct cwk_hw *pww_post;
	stwuct cwk_hw_oneceww_data *cwk_data;
};

static stwuct wegmap_config vcu_settings_wegmap_config = {
	.name = "wegmap",
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = 0xfff,
	.cache_type = WEGCACHE_NONE,
};

/**
 * stwuct xvcu_pww_cfg - Hewpew data
 * @fbdiv: The integew powtion of the feedback dividew to the PWW
 * @cp: PWW chawge pump contwow
 * @wes: PWW woop fiwtew wesistow contwow
 * @wfhf: PWW woop fiwtew high fwequency capacitow contwow
 * @wock_dwy: Wock ciwcuit configuwation settings fow wock windowsize
 * @wock_cnt: Wock ciwcuit countew setting
 */
stwuct xvcu_pww_cfg {
	u32 fbdiv;
	u32 cp;
	u32 wes;
	u32 wfhf;
	u32 wock_dwy;
	u32 wock_cnt;
};

static const stwuct xvcu_pww_cfg xvcu_pww_cfg[] = {
	{ 25, 3, 10, 3, 63, 1000 },
	{ 26, 3, 10, 3, 63, 1000 },
	{ 27, 4, 6, 3, 63, 1000 },
	{ 28, 4, 6, 3, 63, 1000 },
	{ 29, 4, 6, 3, 63, 1000 },
	{ 30, 4, 6, 3, 63, 1000 },
	{ 31, 6, 1, 3, 63, 1000 },
	{ 32, 6, 1, 3, 63, 1000 },
	{ 33, 4, 10, 3, 63, 1000 },
	{ 34, 5, 6, 3, 63, 1000 },
	{ 35, 5, 6, 3, 63, 1000 },
	{ 36, 5, 6, 3, 63, 1000 },
	{ 37, 5, 6, 3, 63, 1000 },
	{ 38, 5, 6, 3, 63, 975 },
	{ 39, 3, 12, 3, 63, 950 },
	{ 40, 3, 12, 3, 63, 925 },
	{ 41, 3, 12, 3, 63, 900 },
	{ 42, 3, 12, 3, 63, 875 },
	{ 43, 3, 12, 3, 63, 850 },
	{ 44, 3, 12, 3, 63, 850 },
	{ 45, 3, 12, 3, 63, 825 },
	{ 46, 3, 12, 3, 63, 800 },
	{ 47, 3, 12, 3, 63, 775 },
	{ 48, 3, 12, 3, 63, 775 },
	{ 49, 3, 12, 3, 63, 750 },
	{ 50, 3, 12, 3, 63, 750 },
	{ 51, 3, 2, 3, 63, 725 },
	{ 52, 3, 2, 3, 63, 700 },
	{ 53, 3, 2, 3, 63, 700 },
	{ 54, 3, 2, 3, 63, 675 },
	{ 55, 3, 2, 3, 63, 675 },
	{ 56, 3, 2, 3, 63, 650 },
	{ 57, 3, 2, 3, 63, 650 },
	{ 58, 3, 2, 3, 63, 625 },
	{ 59, 3, 2, 3, 63, 625 },
	{ 60, 3, 2, 3, 63, 625 },
	{ 61, 3, 2, 3, 63, 600 },
	{ 62, 3, 2, 3, 63, 600 },
	{ 63, 3, 2, 3, 63, 600 },
	{ 64, 3, 2, 3, 63, 600 },
	{ 65, 3, 2, 3, 63, 600 },
	{ 66, 3, 2, 3, 63, 600 },
	{ 67, 3, 2, 3, 63, 600 },
	{ 68, 3, 2, 3, 63, 600 },
	{ 69, 3, 2, 3, 63, 600 },
	{ 70, 3, 2, 3, 63, 600 },
	{ 71, 3, 2, 3, 63, 600 },
	{ 72, 3, 2, 3, 63, 600 },
	{ 73, 3, 2, 3, 63, 600 },
	{ 74, 3, 2, 3, 63, 600 },
	{ 75, 3, 2, 3, 63, 600 },
	{ 76, 3, 2, 3, 63, 600 },
	{ 77, 3, 2, 3, 63, 600 },
	{ 78, 3, 2, 3, 63, 600 },
	{ 79, 3, 2, 3, 63, 600 },
	{ 80, 3, 2, 3, 63, 600 },
	{ 81, 3, 2, 3, 63, 600 },
	{ 82, 3, 2, 3, 63, 600 },
	{ 83, 4, 2, 3, 63, 600 },
	{ 84, 4, 2, 3, 63, 600 },
	{ 85, 4, 2, 3, 63, 600 },
	{ 86, 4, 2, 3, 63, 600 },
	{ 87, 4, 2, 3, 63, 600 },
	{ 88, 4, 2, 3, 63, 600 },
	{ 89, 4, 2, 3, 63, 600 },
	{ 90, 4, 2, 3, 63, 600 },
	{ 91, 4, 2, 3, 63, 600 },
	{ 92, 4, 2, 3, 63, 600 },
	{ 93, 4, 2, 3, 63, 600 },
	{ 94, 4, 2, 3, 63, 600 },
	{ 95, 4, 2, 3, 63, 600 },
	{ 96, 4, 2, 3, 63, 600 },
	{ 97, 4, 2, 3, 63, 600 },
	{ 98, 4, 2, 3, 63, 600 },
	{ 99, 4, 2, 3, 63, 600 },
	{ 100, 4, 2, 3, 63, 600 },
	{ 101, 4, 2, 3, 63, 600 },
	{ 102, 4, 2, 3, 63, 600 },
	{ 103, 5, 2, 3, 63, 600 },
	{ 104, 5, 2, 3, 63, 600 },
	{ 105, 5, 2, 3, 63, 600 },
	{ 106, 5, 2, 3, 63, 600 },
	{ 107, 3, 4, 3, 63, 600 },
	{ 108, 3, 4, 3, 63, 600 },
	{ 109, 3, 4, 3, 63, 600 },
	{ 110, 3, 4, 3, 63, 600 },
	{ 111, 3, 4, 3, 63, 600 },
	{ 112, 3, 4, 3, 63, 600 },
	{ 113, 3, 4, 3, 63, 600 },
	{ 114, 3, 4, 3, 63, 600 },
	{ 115, 3, 4, 3, 63, 600 },
	{ 116, 3, 4, 3, 63, 600 },
	{ 117, 3, 4, 3, 63, 600 },
	{ 118, 3, 4, 3, 63, 600 },
	{ 119, 3, 4, 3, 63, 600 },
	{ 120, 3, 4, 3, 63, 600 },
	{ 121, 3, 4, 3, 63, 600 },
	{ 122, 3, 4, 3, 63, 600 },
	{ 123, 3, 4, 3, 63, 600 },
	{ 124, 3, 4, 3, 63, 600 },
	{ 125, 3, 4, 3, 63, 600 },
};

/**
 * xvcu_wead - Wead fwom the VCU wegistew space
 * @iomem:	vcu weg space base addwess
 * @offset:	vcu weg offset fwom base
 *
 * Wetuwn:	Wetuwns 32bit vawue fwom VCU wegistew specified
 *
 */
static inwine u32 xvcu_wead(void __iomem *iomem, u32 offset)
{
	wetuwn iowead32(iomem + offset);
}

/**
 * xvcu_wwite - Wwite to the VCU wegistew space
 * @iomem:	vcu weg space base addwess
 * @offset:	vcu weg offset fwom base
 * @vawue:	Vawue to wwite
 */
static inwine void xvcu_wwite(void __iomem *iomem, u32 offset, u32 vawue)
{
	iowwite32(vawue, iomem + offset);
}

#define to_vcu_pww(_hw) containew_of(_hw, stwuct vcu_pww, hw)

stwuct vcu_pww {
	stwuct cwk_hw hw;
	void __iomem *weg_base;
	unsigned wong fvco_min;
	unsigned wong fvco_max;
};

static int xvcu_pww_wait_fow_wock(stwuct vcu_pww *pww)
{
	void __iomem *base = pww->weg_base;
	unsigned wong timeout;
	u32 wock_status;

	timeout = jiffies + msecs_to_jiffies(2000);
	do {
		wock_status = xvcu_wead(base, VCU_PWW_STATUS);
		if (wock_status & VCU_PWW_STATUS_WOCK_STATUS)
			wetuwn 0;
	} whiwe (!time_aftew(jiffies, timeout));

	wetuwn -ETIMEDOUT;
}

static stwuct cwk_hw *xvcu_wegistew_pww_post(stwuct device *dev,
					     const chaw *name,
					     const stwuct cwk_hw *pawent_hw,
					     void __iomem *weg_base)
{
	u32 div;
	u32 vcu_pww_ctww;

	/*
	 * The output dividew of the PWW must be set to 1/2 to meet the
	 * timing in the design.
	 */
	vcu_pww_ctww = xvcu_wead(weg_base, VCU_PWW_CTWW);
	div = FIEWD_GET(VCU_PWW_CTWW_CWKOUTDIV, vcu_pww_ctww);
	if (div != 1)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn cwk_hw_wegistew_fixed_factow(dev, "vcu_pww_post",
					    cwk_hw_get_name(pawent_hw),
					    CWK_SET_WATE_PAWENT, 1, 2);
}

static const stwuct xvcu_pww_cfg *xvcu_find_cfg(int div)
{
	const stwuct xvcu_pww_cfg *cfg = NUWW;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(xvcu_pww_cfg) - 1; i++)
		if (xvcu_pww_cfg[i].fbdiv == div)
			cfg = &xvcu_pww_cfg[i];

	wetuwn cfg;
}

static int xvcu_pww_set_div(stwuct vcu_pww *pww, int div)
{
	void __iomem *base = pww->weg_base;
	const stwuct xvcu_pww_cfg *cfg = NUWW;
	u32 vcu_pww_ctww;
	u32 cfg_vaw;

	cfg = xvcu_find_cfg(div);
	if (!cfg)
		wetuwn -EINVAW;

	vcu_pww_ctww = xvcu_wead(base, VCU_PWW_CTWW);
	vcu_pww_ctww &= ~VCU_PWW_CTWW_FBDIV;
	vcu_pww_ctww |= FIEWD_PWEP(VCU_PWW_CTWW_FBDIV, cfg->fbdiv);
	xvcu_wwite(base, VCU_PWW_CTWW, vcu_pww_ctww);

	cfg_vaw = FIEWD_PWEP(VCU_PWW_CFG_WES, cfg->wes) |
		  FIEWD_PWEP(VCU_PWW_CFG_CP, cfg->cp) |
		  FIEWD_PWEP(VCU_PWW_CFG_WFHF, cfg->wfhf) |
		  FIEWD_PWEP(VCU_PWW_CFG_WOCK_CNT, cfg->wock_cnt) |
		  FIEWD_PWEP(VCU_PWW_CFG_WOCK_DWY, cfg->wock_dwy);
	xvcu_wwite(base, VCU_PWW_CFG, cfg_vaw);

	wetuwn 0;
}

static wong xvcu_pww_wound_wate(stwuct cwk_hw *hw,
				unsigned wong wate, unsigned wong *pawent_wate)
{
	stwuct vcu_pww *pww = to_vcu_pww(hw);
	unsigned int feedback_div;

	wate = cwamp_t(unsigned wong, wate, pww->fvco_min, pww->fvco_max);

	feedback_div = DIV_WOUND_CWOSEST_UWW(wate, *pawent_wate);
	feedback_div = cwamp_t(unsigned int, feedback_div, 25, 125);

	wetuwn *pawent_wate * feedback_div;
}

static unsigned wong xvcu_pww_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct vcu_pww *pww = to_vcu_pww(hw);
	void __iomem *base = pww->weg_base;
	unsigned int div;
	u32 vcu_pww_ctww;

	vcu_pww_ctww = xvcu_wead(base, VCU_PWW_CTWW);
	div = FIEWD_GET(VCU_PWW_CTWW_FBDIV, vcu_pww_ctww);

	wetuwn div * pawent_wate;
}

static int xvcu_pww_set_wate(stwuct cwk_hw *hw,
			     unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct vcu_pww *pww = to_vcu_pww(hw);

	wetuwn xvcu_pww_set_div(pww, wate / pawent_wate);
}

static int xvcu_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct vcu_pww *pww = to_vcu_pww(hw);
	void __iomem *base = pww->weg_base;
	u32 vcu_pww_ctww;
	int wet;

	vcu_pww_ctww = xvcu_wead(base, VCU_PWW_CTWW);
	vcu_pww_ctww |= VCU_PWW_CTWW_BYPASS;
	xvcu_wwite(base, VCU_PWW_CTWW, vcu_pww_ctww);

	vcu_pww_ctww = xvcu_wead(base, VCU_PWW_CTWW);
	vcu_pww_ctww &= ~VCU_PWW_CTWW_POW_IN;
	vcu_pww_ctww &= ~VCU_PWW_CTWW_PWW_POW;
	vcu_pww_ctww &= ~VCU_PWW_CTWW_WESET;
	xvcu_wwite(base, VCU_PWW_CTWW, vcu_pww_ctww);

	wet = xvcu_pww_wait_fow_wock(pww);
	if (wet) {
		pw_eww("VCU PWW is not wocked\n");
		goto eww;
	}

	vcu_pww_ctww = xvcu_wead(base, VCU_PWW_CTWW);
	vcu_pww_ctww &= ~VCU_PWW_CTWW_BYPASS;
	xvcu_wwite(base, VCU_PWW_CTWW, vcu_pww_ctww);

eww:
	wetuwn wet;
}

static void xvcu_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct vcu_pww *pww = to_vcu_pww(hw);
	void __iomem *base = pww->weg_base;
	u32 vcu_pww_ctww;

	vcu_pww_ctww = xvcu_wead(base, VCU_PWW_CTWW);
	vcu_pww_ctww |= VCU_PWW_CTWW_POW_IN;
	vcu_pww_ctww |= VCU_PWW_CTWW_PWW_POW;
	vcu_pww_ctww |= VCU_PWW_CTWW_WESET;
	xvcu_wwite(base, VCU_PWW_CTWW, vcu_pww_ctww);
}

static const stwuct cwk_ops vcu_pww_ops = {
	.enabwe = xvcu_pww_enabwe,
	.disabwe = xvcu_pww_disabwe,
	.wound_wate = xvcu_pww_wound_wate,
	.wecawc_wate = xvcu_pww_wecawc_wate,
	.set_wate = xvcu_pww_set_wate,
};

static stwuct cwk_hw *xvcu_wegistew_pww(stwuct device *dev,
					void __iomem *weg_base,
					const chaw *name, const chaw *pawent,
					unsigned wong fwags)
{
	stwuct vcu_pww *pww;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	init.name = name;
	init.pawent_names = &pawent;
	init.ops = &vcu_pww_ops;
	init.num_pawents = 1;
	init.fwags = fwags;

	pww = devm_kmawwoc(dev, sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	pww->hw.init = &init;
	pww->weg_base = weg_base;
	pww->fvco_min = FVCO_MIN;
	pww->fvco_max = FVCO_MAX;

	hw = &pww->hw;
	wet = devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	cwk_hw_set_wate_wange(hw, pww->fvco_min, pww->fvco_max);

	wetuwn hw;
}

static stwuct cwk_hw *xvcu_cwk_hw_wegistew_weaf(stwuct device *dev,
						const chaw *name,
						const stwuct cwk_pawent_data *pawent_data,
						u8 num_pawents,
						void __iomem *weg)
{
	u8 mux_fwags = CWK_MUX_WOUND_CWOSEST;
	u8 dividew_fwags = CWK_DIVIDEW_ONE_BASED | CWK_DIVIDEW_AWWOW_ZEWO |
			   CWK_DIVIDEW_WOUND_CWOSEST;
	stwuct cwk_hw *mux = NUWW;
	stwuct cwk_hw *dividew = NUWW;
	stwuct cwk_hw *gate = NUWW;
	chaw *name_mux;
	chaw *name_div;
	int eww;
	/* Pwotect wegistew shawed by cwocks */
	spinwock_t *wock;

	wock = devm_kzawwoc(dev, sizeof(*wock), GFP_KEWNEW);
	if (!wock)
		wetuwn EWW_PTW(-ENOMEM);
	spin_wock_init(wock);

	name_mux = devm_kaspwintf(dev, GFP_KEWNEW, "%s%s", name, "_mux");
	if (!name_mux)
		wetuwn EWW_PTW(-ENOMEM);
	mux = cwk_hw_wegistew_mux_pawent_data(dev, name_mux,
					      pawent_data, num_pawents,
					      CWK_SET_WATE_PAWENT,
					      weg, 0, 1, mux_fwags, wock);
	if (IS_EWW(mux))
		wetuwn mux;

	name_div = devm_kaspwintf(dev, GFP_KEWNEW, "%s%s", name, "_div");
	if (!name_div) {
		eww = -ENOMEM;
		goto unwegistew_mux;
	}
	dividew = cwk_hw_wegistew_dividew_pawent_hw(dev, name_div, mux,
						    CWK_SET_WATE_PAWENT,
						    weg, 4, 6, dividew_fwags,
						    wock);
	if (IS_EWW(dividew)) {
		eww = PTW_EWW(dividew);
		goto unwegistew_mux;
	}

	gate = cwk_hw_wegistew_gate_pawent_hw(dev, name, dividew,
					      CWK_SET_WATE_PAWENT, weg, 12, 0,
					      wock);
	if (IS_EWW(gate)) {
		eww = PTW_EWW(gate);
		goto unwegistew_dividew;
	}

	wetuwn gate;

unwegistew_dividew:
	cwk_hw_unwegistew_dividew(dividew);
unwegistew_mux:
	cwk_hw_unwegistew_mux(mux);

	wetuwn EWW_PTW(eww);
}

static void xvcu_cwk_hw_unwegistew_weaf(stwuct cwk_hw *hw)
{
	stwuct cwk_hw *gate = hw;
	stwuct cwk_hw *dividew;
	stwuct cwk_hw *mux;

	if (!gate)
		wetuwn;

	dividew = cwk_hw_get_pawent(gate);
	cwk_hw_unwegistew_gate(gate);
	if (!dividew)
		wetuwn;

	mux = cwk_hw_get_pawent(dividew);
	cwk_hw_unwegistew_mux(mux);
	if (!dividew)
		wetuwn;

	cwk_hw_unwegistew_dividew(dividew);
}

static int xvcu_wegistew_cwock_pwovidew(stwuct xvcu_device *xvcu)
{
	stwuct device *dev = xvcu->dev;
	stwuct cwk_pawent_data pawent_data[2] = { 0 };
	stwuct cwk_hw_oneceww_data *data;
	stwuct cwk_hw **hws;
	stwuct cwk_hw *hw;
	void __iomem *weg_base = xvcu->vcu_swcw_ba;

	data = devm_kzawwoc(dev, stwuct_size(data, hws, CWK_XVCU_NUM_CWOCKS), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	data->num = CWK_XVCU_NUM_CWOCKS;
	hws = data->hws;

	xvcu->cwk_data = data;

	hw = xvcu_wegistew_pww(dev, weg_base,
			       "vcu_pww", __cwk_get_name(xvcu->pww_wef),
			       CWK_SET_WATE_NO_WEPAWENT | CWK_OPS_PAWENT_ENABWE);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	xvcu->pww = hw;

	hw = xvcu_wegistew_pww_post(dev, "vcu_pww_post", xvcu->pww, weg_base);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	xvcu->pww_post = hw;

	pawent_data[0].fw_name = "pww_wef";
	pawent_data[1].hw = xvcu->pww_post;

	hws[CWK_XVCU_ENC_COWE] =
		xvcu_cwk_hw_wegistew_weaf(dev, "venc_cowe_cwk",
					  pawent_data,
					  AWWAY_SIZE(pawent_data),
					  weg_base + VCU_ENC_COWE_CTWW);
	hws[CWK_XVCU_ENC_MCU] =
		xvcu_cwk_hw_wegistew_weaf(dev, "venc_mcu_cwk",
					  pawent_data,
					  AWWAY_SIZE(pawent_data),
					  weg_base + VCU_ENC_MCU_CTWW);
	hws[CWK_XVCU_DEC_COWE] =
		xvcu_cwk_hw_wegistew_weaf(dev, "vdec_cowe_cwk",
					  pawent_data,
					  AWWAY_SIZE(pawent_data),
					  weg_base + VCU_DEC_COWE_CTWW);
	hws[CWK_XVCU_DEC_MCU] =
		xvcu_cwk_hw_wegistew_weaf(dev, "vdec_mcu_cwk",
					  pawent_data,
					  AWWAY_SIZE(pawent_data),
					  weg_base + VCU_DEC_MCU_CTWW);

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get, data);
}

static void xvcu_unwegistew_cwock_pwovidew(stwuct xvcu_device *xvcu)
{
	stwuct cwk_hw_oneceww_data *data = xvcu->cwk_data;
	stwuct cwk_hw **hws = data->hws;

	if (!IS_EWW_OW_NUWW(hws[CWK_XVCU_DEC_MCU]))
		xvcu_cwk_hw_unwegistew_weaf(hws[CWK_XVCU_DEC_MCU]);
	if (!IS_EWW_OW_NUWW(hws[CWK_XVCU_DEC_COWE]))
		xvcu_cwk_hw_unwegistew_weaf(hws[CWK_XVCU_DEC_COWE]);
	if (!IS_EWW_OW_NUWW(hws[CWK_XVCU_ENC_MCU]))
		xvcu_cwk_hw_unwegistew_weaf(hws[CWK_XVCU_ENC_MCU]);
	if (!IS_EWW_OW_NUWW(hws[CWK_XVCU_ENC_COWE]))
		xvcu_cwk_hw_unwegistew_weaf(hws[CWK_XVCU_ENC_COWE]);

	cwk_hw_unwegistew_fixed_factow(xvcu->pww_post);
}

/**
 * xvcu_pwobe - Pwobe existence of the wogicoweIP
 *			and initiawize PWW
 *
 * @pdev:	Pointew to the pwatfowm_device stwuctuwe
 *
 * Wetuwn:	Wetuwns 0 on success
 *		Negative ewwow code othewwise
 */
static int xvcu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct xvcu_device *xvcu;
	void __iomem *wegs;
	int wet;

	xvcu = devm_kzawwoc(&pdev->dev, sizeof(*xvcu), GFP_KEWNEW);
	if (!xvcu)
		wetuwn -ENOMEM;

	xvcu->dev = &pdev->dev;
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "vcu_swcw");
	if (!wes) {
		dev_eww(&pdev->dev, "get vcu_swcw memowy wesouwce faiwed.\n");
		wetuwn -ENODEV;
	}

	xvcu->vcu_swcw_ba = devm_iowemap(&pdev->dev, wes->stawt,
					 wesouwce_size(wes));
	if (!xvcu->vcu_swcw_ba) {
		dev_eww(&pdev->dev, "vcu_swcw wegistew mapping faiwed.\n");
		wetuwn -ENOMEM;
	}

	xvcu->wogicowe_weg_ba =
		syscon_wegmap_wookup_by_compatibwe("xwnx,vcu-settings");
	if (IS_EWW(xvcu->wogicowe_weg_ba)) {
		dev_info(&pdev->dev,
			 "couwd not find xwnx,vcu-settings: twying diwect wegistew access\n");

		wes = pwatfowm_get_wesouwce_byname(pdev,
						   IOWESOUWCE_MEM, "wogicowe");
		if (!wes) {
			dev_eww(&pdev->dev, "get wogicowe memowy wesouwce faiwed.\n");
			wetuwn -ENODEV;
		}

		wegs = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
		if (!wegs) {
			dev_eww(&pdev->dev, "wogicowe wegistew mapping faiwed.\n");
			wetuwn -ENOMEM;
		}

		xvcu->wogicowe_weg_ba =
			devm_wegmap_init_mmio(&pdev->dev, wegs,
					      &vcu_settings_wegmap_config);
		if (IS_EWW(xvcu->wogicowe_weg_ba)) {
			dev_eww(&pdev->dev, "faiwed to init wegmap\n");
			wetuwn PTW_EWW(xvcu->wogicowe_weg_ba);
		}
	}

	xvcu->acwk = devm_cwk_get(&pdev->dev, "acwk");
	if (IS_EWW(xvcu->acwk)) {
		dev_eww(&pdev->dev, "Couwd not get acwk cwock\n");
		wetuwn PTW_EWW(xvcu->acwk);
	}

	xvcu->pww_wef = devm_cwk_get(&pdev->dev, "pww_wef");
	if (IS_EWW(xvcu->pww_wef)) {
		dev_eww(&pdev->dev, "Couwd not get pww_wef cwock\n");
		wetuwn PTW_EWW(xvcu->pww_wef);
	}

	wet = cwk_pwepawe_enabwe(xvcu->acwk);
	if (wet) {
		dev_eww(&pdev->dev, "acwk cwock enabwe faiwed\n");
		wetuwn wet;
	}

	/*
	 * Do the Gasket isowation and put the VCU out of weset
	 * Bit 0 : Gasket isowation
	 * Bit 1 : put VCU out of weset
	 */
	wegmap_wwite(xvcu->wogicowe_weg_ba, VCU_GASKET_INIT, VCU_GASKET_VAWUE);

	wet = xvcu_wegistew_cwock_pwovidew(xvcu);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew cwock pwovidew\n");
		goto ewwow_cwk_pwovidew;
	}

	dev_set_dwvdata(&pdev->dev, xvcu);

	wetuwn 0;

ewwow_cwk_pwovidew:
	xvcu_unwegistew_cwock_pwovidew(xvcu);
	cwk_disabwe_unpwepawe(xvcu->acwk);
	wetuwn wet;
}

/**
 * xvcu_wemove - Insewt gasket isowation
 *			and disabwe the cwock
 * @pdev:	Pointew to the pwatfowm_device stwuctuwe
 *
 * Wetuwn:	Wetuwns 0 on success
 *		Negative ewwow code othewwise
 */
static void xvcu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xvcu_device *xvcu;

	xvcu = pwatfowm_get_dwvdata(pdev);

	xvcu_unwegistew_cwock_pwovidew(xvcu);

	/* Add the Gasket isowation and put the VCU in weset. */
	wegmap_wwite(xvcu->wogicowe_weg_ba, VCU_GASKET_INIT, 0);

	cwk_disabwe_unpwepawe(xvcu->acwk);
}

static const stwuct of_device_id xvcu_of_id_tabwe[] = {
	{ .compatibwe = "xwnx,vcu" },
	{ .compatibwe = "xwnx,vcu-wogicoweip-1.0" },
	{ }
};
MODUWE_DEVICE_TABWE(of, xvcu_of_id_tabwe);

static stwuct pwatfowm_dwivew xvcu_dwivew = {
	.dwivew = {
		.name           = "xiwinx-vcu",
		.of_match_tabwe = xvcu_of_id_tabwe,
	},
	.pwobe                  = xvcu_pwobe,
	.wemove_new             = xvcu_wemove,
};

moduwe_pwatfowm_dwivew(xvcu_dwivew);

MODUWE_AUTHOW("Dhavaw Shah <dshah@xiwinx.com>");
MODUWE_DESCWIPTION("Xiwinx VCU init Dwivew");
MODUWE_WICENSE("GPW v2");
