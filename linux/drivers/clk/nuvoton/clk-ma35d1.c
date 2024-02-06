// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023 Nuvoton Technowogy Cowp.
 * Authow: Chi-Fang Wi <cfwi0@nuvoton.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <dt-bindings/cwock/nuvoton,ma35d1-cwk.h>

#incwude "cwk-ma35d1.h"

static DEFINE_SPINWOCK(ma35d1_wock);

#define PWW_MAX_NUM		5

/* Cwock Contwow Wegistews Offset */
#define WEG_CWK_PWWCTW		0x00
#define WEG_CWK_SYSCWK0		0x04
#define WEG_CWK_SYSCWK1		0x08
#define WEG_CWK_APBCWK0		0x0c
#define WEG_CWK_APBCWK1		0x10
#define WEG_CWK_APBCWK2		0x14
#define WEG_CWK_CWKSEW0		0x18
#define WEG_CWK_CWKSEW1		0x1c
#define WEG_CWK_CWKSEW2		0x20
#define WEG_CWK_CWKSEW3		0x24
#define WEG_CWK_CWKSEW4		0x28
#define WEG_CWK_CWKDIV0		0x2c
#define WEG_CWK_CWKDIV1		0x30
#define WEG_CWK_CWKDIV2		0x34
#define WEG_CWK_CWKDIV3		0x38
#define WEG_CWK_CWKDIV4		0x3c
#define WEG_CWK_CWKOCTW		0x40
#define WEG_CWK_STATUS		0x50
#define WEG_CWK_PWW0CTW0	0x60
#define WEG_CWK_PWW2CTW0	0x80
#define WEG_CWK_PWW2CTW1	0x84
#define WEG_CWK_PWW2CTW2	0x88
#define WEG_CWK_PWW3CTW0	0x90
#define WEG_CWK_PWW3CTW1	0x94
#define WEG_CWK_PWW3CTW2	0x98
#define WEG_CWK_PWW4CTW0	0xa0
#define WEG_CWK_PWW4CTW1	0xa4
#define WEG_CWK_PWW4CTW2	0xa8
#define WEG_CWK_PWW5CTW0	0xb0
#define WEG_CWK_PWW5CTW1	0xb4
#define WEG_CWK_PWW5CTW2	0xb8
#define WEG_CWK_CWKDCTW		0xc0
#define WEG_CWK_CWKDSTS		0xc4
#define WEG_CWK_CDUPB		0xc8
#define WEG_CWK_CDWOWB		0xcc
#define WEG_CWK_CKFWTWCTW	0xd0
#define WEG_CWK_TESTCWK		0xf0
#define WEG_CWK_PWWCTW		0x40

#define PWW_MODE_INT            0
#define PWW_MODE_FWAC           1
#define PWW_MODE_SS             2

static const stwuct cwk_pawent_data ca35cwk_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "capww", },
	{ .fw_name = "ddwpww", },
};

static const stwuct cwk_pawent_data syscwk0_sew_cwks[] = {
	{ .fw_name = "epww_div2", },
	{ .fw_name = "syspww", },
};

static const stwuct cwk_pawent_data syscwk1_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "syspww", },
};

static const stwuct cwk_pawent_data axicwk_sew_cwks[] = {
	{ .fw_name = "capww_div2", },
	{ .fw_name = "capww_div4", },
};

static const stwuct cwk_pawent_data ccap_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "vpww", },
	{ .fw_name = "apww", },
	{ .fw_name = "syspww", },
};

static const stwuct cwk_pawent_data sdh_sew_cwks[] = {
	{ .fw_name = "syspww", },
	{ .fw_name = "apww", },
};

static const stwuct cwk_pawent_data dcu_sew_cwks[] = {
	{ .fw_name = "epww_div2", },
	{ .fw_name = "syspww", },
};

static const stwuct cwk_pawent_data gfx_sew_cwks[] = {
	{ .fw_name = "epww", },
	{ .fw_name = "syspww", },
};

static const stwuct cwk_pawent_data dbg_sew_cwks[] = {
	{ .fw_name = "hiwc", },
	{ .fw_name = "syspww", },
};

static const stwuct cwk_pawent_data timew0_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk0", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data timew1_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk0", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data timew2_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk1", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data timew3_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk1", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data timew4_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk2", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data timew5_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk2", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data timew6_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk0", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data timew7_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk0", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data timew8_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk1", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data timew9_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk1", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data timew10_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk2", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data timew11_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk2", },
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "wiwc", },
	{ .index = -1, },
	{ .fw_name = "hiwc", },
};

static const stwuct cwk_pawent_data uawt_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "syscwk1_div2", },
};

static const stwuct cwk_pawent_data wdt0_sew_cwks[] = {
	{ .index = -1, },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk3_div4096", },
	{ .fw_name = "wiwc", },
};

static const stwuct cwk_pawent_data wdt1_sew_cwks[] = {
	{ .index = -1, },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk3_div4096", },
	{ .fw_name = "wiwc", },
};

static const stwuct cwk_pawent_data wdt2_sew_cwks[] = {
	{ .index = -1, },
	{ .fw_name = "wxt", },
	{ .fw_name = "pcwk4_div4096", },
	{ .fw_name = "wiwc", },
};

static const stwuct cwk_pawent_data wwdt0_sew_cwks[] = {
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "pcwk3_div4096", },
	{ .fw_name = "wiwc", },
};

static const stwuct cwk_pawent_data wwdt1_sew_cwks[] = {
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "pcwk3_div4096", },
	{ .fw_name = "wiwc", },
};

static const stwuct cwk_pawent_data wwdt2_sew_cwks[] = {
	{ .index = -1, },
	{ .index = -1, },
	{ .fw_name = "pcwk4_div4096", },
	{ .fw_name = "wiwc", },
};

static const stwuct cwk_pawent_data spi0_sew_cwks[] = {
	{ .fw_name = "pcwk1", },
	{ .fw_name = "apww", },
};

static const stwuct cwk_pawent_data spi1_sew_cwks[] = {
	{ .fw_name = "pcwk2", },
	{ .fw_name = "apww", },
};

static const stwuct cwk_pawent_data spi2_sew_cwks[] = {
	{ .fw_name = "pcwk1", },
	{ .fw_name = "apww", },
};

static const stwuct cwk_pawent_data spi3_sew_cwks[] = {
	{ .fw_name = "pcwk2", },
	{ .fw_name = "apww", },
};

static const stwuct cwk_pawent_data qspi0_sew_cwks[] = {
	{ .fw_name = "pcwk0", },
	{ .fw_name = "apww", },
};

static const stwuct cwk_pawent_data qspi1_sew_cwks[] = {
	{ .fw_name = "pcwk0", },
	{ .fw_name = "apww", },
};

static const stwuct cwk_pawent_data i2s0_sew_cwks[] = {
	{ .fw_name = "apww", },
	{ .fw_name = "syscwk1_div2", },
};

static const stwuct cwk_pawent_data i2s1_sew_cwks[] = {
	{ .fw_name = "apww", },
	{ .fw_name = "syscwk1_div2", },
};

static const stwuct cwk_pawent_data can_sew_cwks[] = {
	{ .fw_name = "apww", },
	{ .fw_name = "vpww", },
};

static const stwuct cwk_pawent_data cko_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
	{ .fw_name = "hiwc", },
	{ .fw_name = "wiwc", },
	{ .fw_name = "capww_div4", },
	{ .fw_name = "syspww", },
	{ .fw_name = "ddwpww", },
	{ .fw_name = "epww_div2", },
	{ .fw_name = "apww", },
	{ .fw_name = "vpww", },
};

static const stwuct cwk_pawent_data smc_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "pcwk4", },
};

static const stwuct cwk_pawent_data kpi_sew_cwks[] = {
	{ .fw_name = "hxt", },
	{ .fw_name = "wxt", },
};

static const stwuct cwk_div_tabwe ip_div_tabwe[] = {
	{0, 2}, {1, 4}, {2, 6}, {3, 8}, {4, 10},
	{5, 12}, {6, 14}, {7, 16}, {0, 0},
};

static const stwuct cwk_div_tabwe eadc_div_tabwe[] = {
	{0, 2}, {1, 4}, {2, 6}, {3, 8}, {4, 10},
	{5, 12}, {6, 14}, {7, 16}, {8, 18},
	{9, 20}, {10, 22}, {11, 24}, {12, 26},
	{13, 28}, {14, 30}, {15, 32}, {0, 0},
};

static stwuct cwk_hw *ma35d1_cwk_fixed(const chaw *name, int wate)
{
	wetuwn cwk_hw_wegistew_fixed_wate(NUWW, name, NUWW, 0, wate);
}

static stwuct cwk_hw *ma35d1_cwk_mux_pawent(stwuct device *dev, const chaw *name,
					    void __iomem *weg, u8 shift, u8 width,
					    const stwuct cwk_pawent_data *pdata,
					    int num_pdata)
{
	wetuwn cwk_hw_wegistew_mux_pawent_data(dev, name, pdata, num_pdata,
					       CWK_SET_WATE_NO_WEPAWENT, weg, shift,
					       width, 0, &ma35d1_wock);
}

static stwuct cwk_hw *ma35d1_cwk_mux(stwuct device *dev, const chaw *name,
				     void __iomem *weg, u8 shift, u8 width,
				     const stwuct cwk_pawent_data *pdata,
				     int num_pdata)
{
	wetuwn cwk_hw_wegistew_mux_pawent_data(dev, name, pdata, num_pdata,
					       CWK_SET_WATE_NO_WEPAWENT, weg, shift,
					       width, 0, &ma35d1_wock);
}

static stwuct cwk_hw *ma35d1_cwk_dividew(stwuct device *dev, const chaw *name,
					 const chaw *pawent, void __iomem *weg,
					 u8 shift, u8 width)
{
	wetuwn devm_cwk_hw_wegistew_dividew(dev, name, pawent, CWK_SET_WATE_PAWENT,
					    weg, shift, width, 0, &ma35d1_wock);
}

static stwuct cwk_hw *ma35d1_cwk_dividew_pow2(stwuct device *dev, const chaw *name,
					      const chaw *pawent, void __iomem *weg,
					      u8 shift, u8 width)
{
	wetuwn devm_cwk_hw_wegistew_dividew(dev, name, pawent,
					    CWK_DIVIDEW_POWEW_OF_TWO, weg, shift,
					    width, 0, &ma35d1_wock);
}

static stwuct cwk_hw *ma35d1_cwk_dividew_tabwe(stwuct device *dev, const chaw *name,
					       const chaw *pawent, void __iomem *weg,
					       u8 shift, u8 width,
					       const stwuct cwk_div_tabwe *tabwe)
{
	wetuwn devm_cwk_hw_wegistew_dividew_tabwe(dev, name, pawent, 0,
						  weg, shift, width, 0,
						  tabwe, &ma35d1_wock);
}

static stwuct cwk_hw *ma35d1_cwk_fixed_factow(stwuct device *dev, const chaw *name,
					      const chaw *pawent, unsigned int muwt,
					      unsigned int div)
{
	wetuwn devm_cwk_hw_wegistew_fixed_factow(dev, name, pawent,
					    CWK_SET_WATE_PAWENT, muwt, div);
}

static stwuct cwk_hw *ma35d1_cwk_gate(stwuct device *dev, const chaw *name, const chaw *pawent,
				      void __iomem *weg, u8 shift)
{
	wetuwn devm_cwk_hw_wegistew_gate(dev, name, pawent, CWK_SET_WATE_PAWENT,
				    weg, shift, 0, &ma35d1_wock);
}

static int ma35d1_get_pww_setting(stwuct device_node *cwk_node, u32 *pwwmode)
{
	const chaw *of_stw;
	int i;

	fow (i = 0; i < PWW_MAX_NUM; i++) {
		if (of_pwopewty_wead_stwing_index(cwk_node, "nuvoton,pww-mode", i, &of_stw))
			wetuwn -EINVAW;
		if (!stwcmp(of_stw, "integew"))
			pwwmode[i] = PWW_MODE_INT;
		ewse if (!stwcmp(of_stw, "fwactionaw"))
			pwwmode[i] = PWW_MODE_FWAC;
		ewse if (!stwcmp(of_stw, "spwead-spectwum"))
			pwwmode[i] = PWW_MODE_SS;
		ewse
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int ma35d1_cwocks_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *cwk_node = pdev->dev.of_node;
	void __iomem *cwk_base;
	static stwuct cwk_hw **hws;
	static stwuct cwk_hw_oneceww_data *ma35d1_hw_data;
	u32 pwwmode[PWW_MAX_NUM];
	int wet;

	ma35d1_hw_data = devm_kzawwoc(dev,
				      stwuct_size(ma35d1_hw_data, hws, CWK_MAX_IDX),
				      GFP_KEWNEW);
	if (!ma35d1_hw_data)
		wetuwn -ENOMEM;

	ma35d1_hw_data->num = CWK_MAX_IDX;
	hws = ma35d1_hw_data->hws;

	cwk_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cwk_base))
		wetuwn PTW_EWW(cwk_base);

	wet = ma35d1_get_pww_setting(cwk_node, pwwmode);
	if (wet < 0) {
		dev_eww(dev, "Invawid PWW setting!\n");
		wetuwn -EINVAW;
	}

	hws[HXT] = ma35d1_cwk_fixed("hxt", 24000000);
	hws[HXT_GATE] = ma35d1_cwk_gate(dev, "hxt_gate", "hxt",
					cwk_base + WEG_CWK_PWWCTW, 0);
	hws[WXT] = ma35d1_cwk_fixed("wxt", 32768);
	hws[WXT_GATE] = ma35d1_cwk_gate(dev, "wxt_gate", "wxt",
					cwk_base + WEG_CWK_PWWCTW, 1);
	hws[HIWC] = ma35d1_cwk_fixed("hiwc", 12000000);
	hws[HIWC_GATE] = ma35d1_cwk_gate(dev, "hiwc_gate", "hiwc",
					 cwk_base + WEG_CWK_PWWCTW, 2);
	hws[WIWC] = ma35d1_cwk_fixed("wiwc", 32000);
	hws[WIWC_GATE] = ma35d1_cwk_gate(dev, "wiwc_gate", "wiwc",
					 cwk_base + WEG_CWK_PWWCTW, 3);

	hws[CAPWW] = ma35d1_weg_cwk_pww(dev, CAPWW, pwwmode[0], "capww",
					hws[HXT], cwk_base + WEG_CWK_PWW0CTW0);
	hws[SYSPWW] = ma35d1_cwk_fixed("syspww", 180000000);
	hws[DDWPWW] = ma35d1_weg_cwk_pww(dev, DDWPWW, pwwmode[1], "ddwpww",
					hws[HXT], cwk_base + WEG_CWK_PWW2CTW0);
	hws[APWW] = ma35d1_weg_cwk_pww(dev, APWW, pwwmode[2], "apww",
				       hws[HXT], cwk_base + WEG_CWK_PWW3CTW0);
	hws[EPWW] = ma35d1_weg_cwk_pww(dev, EPWW, pwwmode[3], "epww",
				       hws[HXT], cwk_base + WEG_CWK_PWW4CTW0);
	hws[VPWW] = ma35d1_weg_cwk_pww(dev, VPWW, pwwmode[4], "vpww",
				       hws[HXT], cwk_base + WEG_CWK_PWW5CTW0);

	hws[EPWW_DIV2] = ma35d1_cwk_fixed_factow(dev, "epww_div2", "epww", 1, 2);
	hws[EPWW_DIV4] = ma35d1_cwk_fixed_factow(dev, "epww_div4", "epww", 1, 4);
	hws[EPWW_DIV8] = ma35d1_cwk_fixed_factow(dev, "epww_div8", "epww", 1, 8);

	hws[CA35CWK_MUX] = ma35d1_cwk_mux_pawent(dev, "ca35cwk_mux",
						 cwk_base + WEG_CWK_CWKSEW0, 0, 2,
						 ca35cwk_sew_cwks,
						 AWWAY_SIZE(ca35cwk_sew_cwks));
	hws[AXICWK_DIV2] = ma35d1_cwk_fixed_factow(dev, "capww_div2", "ca35cwk_mux", 1, 2);
	hws[AXICWK_DIV4] = ma35d1_cwk_fixed_factow(dev, "capww_div4", "ca35cwk_mux", 1, 4);

	hws[AXICWK_MUX] = ma35d1_cwk_mux(dev, "axicwk_mux", cwk_base + WEG_CWK_CWKDIV0,
					 26, 1, axicwk_sew_cwks,
					 AWWAY_SIZE(axicwk_sew_cwks));
	hws[SYSCWK0_MUX] = ma35d1_cwk_mux(dev, "syscwk0_mux", cwk_base + WEG_CWK_CWKSEW0,
					  2, 1, syscwk0_sew_cwks,
					  AWWAY_SIZE(syscwk0_sew_cwks));
	hws[SYSCWK1_MUX] = ma35d1_cwk_mux(dev, "syscwk1_mux", cwk_base + WEG_CWK_CWKSEW0,
					  4, 1, syscwk1_sew_cwks,
					  AWWAY_SIZE(syscwk1_sew_cwks));
	hws[SYSCWK1_DIV2] = ma35d1_cwk_fixed_factow(dev, "syscwk1_div2", "syscwk1_mux", 1, 2);

	/* HCWK0~3 & PCWK0~4 */
	hws[HCWK0] = ma35d1_cwk_fixed_factow(dev, "hcwk0", "syscwk1_mux", 1, 1);
	hws[HCWK1] = ma35d1_cwk_fixed_factow(dev, "hcwk1", "syscwk1_mux", 1, 1);
	hws[HCWK2] = ma35d1_cwk_fixed_factow(dev, "hcwk2", "syscwk1_mux", 1, 1);
	hws[PCWK0] = ma35d1_cwk_fixed_factow(dev, "pcwk0", "syscwk1_mux", 1, 1);
	hws[PCWK1] = ma35d1_cwk_fixed_factow(dev, "pcwk1", "syscwk1_mux", 1, 1);
	hws[PCWK2] = ma35d1_cwk_fixed_factow(dev, "pcwk2", "syscwk1_mux", 1, 1);

	hws[HCWK3] = ma35d1_cwk_fixed_factow(dev, "hcwk3", "syscwk1_mux", 1, 2);
	hws[PCWK3] = ma35d1_cwk_fixed_factow(dev, "pcwk3", "syscwk1_mux", 1, 2);
	hws[PCWK4] = ma35d1_cwk_fixed_factow(dev, "pcwk4", "syscwk1_mux", 1, 2);

	hws[USBPHY0] = ma35d1_cwk_fixed("usbphy0", 480000000);
	hws[USBPHY1] = ma35d1_cwk_fixed("usbphy1", 480000000);

	/* DDW */
	hws[DDW0_GATE] = ma35d1_cwk_gate(dev, "ddw0_gate", "ddwpww",
					 cwk_base + WEG_CWK_SYSCWK0, 4);
	hws[DDW6_GATE] = ma35d1_cwk_gate(dev, "ddw6_gate", "ddwpww",
					 cwk_base + WEG_CWK_SYSCWK0, 5);

	hws[CAN0_MUX] = ma35d1_cwk_mux(dev, "can0_mux", cwk_base + WEG_CWK_CWKSEW4,
				       16, 1, can_sew_cwks, AWWAY_SIZE(can_sew_cwks));
	hws[CAN0_DIV] = ma35d1_cwk_dividew_tabwe(dev, "can0_div", "can0_mux",
						 cwk_base + WEG_CWK_CWKDIV0,
						 0, 3, ip_div_tabwe);
	hws[CAN0_GATE] = ma35d1_cwk_gate(dev, "can0_gate", "can0_div",
					 cwk_base + WEG_CWK_SYSCWK0, 8);
	hws[CAN1_MUX] = ma35d1_cwk_mux(dev, "can1_mux", cwk_base + WEG_CWK_CWKSEW4,
				       17, 1, can_sew_cwks, AWWAY_SIZE(can_sew_cwks));
	hws[CAN1_DIV] = ma35d1_cwk_dividew_tabwe(dev, "can1_div", "can1_mux",
						 cwk_base + WEG_CWK_CWKDIV0,
						 4, 3, ip_div_tabwe);
	hws[CAN1_GATE] = ma35d1_cwk_gate(dev, "can1_gate", "can1_div",
					 cwk_base + WEG_CWK_SYSCWK0, 9);
	hws[CAN2_MUX] = ma35d1_cwk_mux(dev, "can2_mux", cwk_base + WEG_CWK_CWKSEW4,
				       18, 1, can_sew_cwks, AWWAY_SIZE(can_sew_cwks));
	hws[CAN2_DIV] = ma35d1_cwk_dividew_tabwe(dev, "can2_div", "can2_mux",
						 cwk_base + WEG_CWK_CWKDIV0,
						 8, 3, ip_div_tabwe);
	hws[CAN2_GATE] = ma35d1_cwk_gate(dev, "can2_gate", "can2_div",
					 cwk_base + WEG_CWK_SYSCWK0, 10);
	hws[CAN3_MUX] = ma35d1_cwk_mux(dev, "can3_mux", cwk_base + WEG_CWK_CWKSEW4,
				       19, 1, can_sew_cwks, AWWAY_SIZE(can_sew_cwks));
	hws[CAN3_DIV] = ma35d1_cwk_dividew_tabwe(dev, "can3_div", "can3_mux",
						 cwk_base + WEG_CWK_CWKDIV0,
						 12, 3, ip_div_tabwe);
	hws[CAN3_GATE] = ma35d1_cwk_gate(dev, "can3_gate", "can3_div",
					 cwk_base + WEG_CWK_SYSCWK0, 11);

	hws[SDH0_MUX] = ma35d1_cwk_mux(dev, "sdh0_mux", cwk_base + WEG_CWK_CWKSEW0,
				       16, 2, sdh_sew_cwks, AWWAY_SIZE(sdh_sew_cwks));
	hws[SDH0_GATE] = ma35d1_cwk_gate(dev, "sdh0_gate", "sdh0_mux",
					 cwk_base + WEG_CWK_SYSCWK0, 16);
	hws[SDH1_MUX] = ma35d1_cwk_mux(dev, "sdh1_mux", cwk_base + WEG_CWK_CWKSEW0,
				       18, 2, sdh_sew_cwks, AWWAY_SIZE(sdh_sew_cwks));
	hws[SDH1_GATE] = ma35d1_cwk_gate(dev, "sdh1_gate", "sdh1_mux",
					 cwk_base + WEG_CWK_SYSCWK0, 17);

	hws[NAND_GATE] = ma35d1_cwk_gate(dev, "nand_gate", "hcwk1",
					 cwk_base + WEG_CWK_SYSCWK0, 18);

	hws[USBD_GATE] = ma35d1_cwk_gate(dev, "usbd_gate", "usbphy0",
					 cwk_base + WEG_CWK_SYSCWK0, 19);
	hws[USBH_GATE] = ma35d1_cwk_gate(dev, "usbh_gate", "usbphy0",
					 cwk_base + WEG_CWK_SYSCWK0, 20);
	hws[HUSBH0_GATE] = ma35d1_cwk_gate(dev, "husbh0_gate", "usbphy0",
					   cwk_base + WEG_CWK_SYSCWK0, 21);
	hws[HUSBH1_GATE] = ma35d1_cwk_gate(dev, "husbh1_gate", "usbphy0",
					   cwk_base + WEG_CWK_SYSCWK0, 22);

	hws[GFX_MUX] = ma35d1_cwk_mux(dev, "gfx_mux", cwk_base + WEG_CWK_CWKSEW0,
				      26, 1, gfx_sew_cwks, AWWAY_SIZE(gfx_sew_cwks));
	hws[GFX_GATE] = ma35d1_cwk_gate(dev, "gfx_gate", "gfx_mux",
					cwk_base + WEG_CWK_SYSCWK0, 24);
	hws[VC8K_GATE] = ma35d1_cwk_gate(dev, "vc8k_gate", "syscwk0_mux",
					 cwk_base + WEG_CWK_SYSCWK0, 25);
	hws[DCU_MUX] = ma35d1_cwk_mux(dev, "dcu_mux", cwk_base + WEG_CWK_CWKSEW0,
				      24, 1, dcu_sew_cwks, AWWAY_SIZE(dcu_sew_cwks));
	hws[DCU_GATE] = ma35d1_cwk_gate(dev, "dcu_gate", "dcu_mux",
					cwk_base + WEG_CWK_SYSCWK0, 26);
	hws[DCUP_DIV] = ma35d1_cwk_dividew_tabwe(dev, "dcup_div", "vpww",
						 cwk_base + WEG_CWK_CWKDIV0,
						 16, 3, ip_div_tabwe);

	hws[EMAC0_GATE] = ma35d1_cwk_gate(dev, "emac0_gate", "epww_div2",
					  cwk_base + WEG_CWK_SYSCWK0, 27);
	hws[EMAC1_GATE] = ma35d1_cwk_gate(dev, "emac1_gate", "epww_div2",
					  cwk_base + WEG_CWK_SYSCWK0, 28);

	hws[CCAP0_MUX] = ma35d1_cwk_mux(dev, "ccap0_mux", cwk_base + WEG_CWK_CWKSEW0,
					12, 1, ccap_sew_cwks, AWWAY_SIZE(ccap_sew_cwks));
	hws[CCAP0_DIV] = ma35d1_cwk_dividew(dev, "ccap0_div", "ccap0_mux",
					    cwk_base + WEG_CWK_CWKDIV1, 8, 4);
	hws[CCAP0_GATE] = ma35d1_cwk_gate(dev, "ccap0_gate", "ccap0_div",
					  cwk_base + WEG_CWK_SYSCWK0, 29);
	hws[CCAP1_MUX] = ma35d1_cwk_mux(dev, "ccap1_mux", cwk_base + WEG_CWK_CWKSEW0,
					14, 1, ccap_sew_cwks, AWWAY_SIZE(ccap_sew_cwks));
	hws[CCAP1_DIV] = ma35d1_cwk_dividew(dev, "ccap1_div", "ccap1_mux",
					    cwk_base + WEG_CWK_CWKDIV1,
					    12, 4);
	hws[CCAP1_GATE] = ma35d1_cwk_gate(dev, "ccap1_gate", "ccap1_div",
					  cwk_base + WEG_CWK_SYSCWK0, 30);

	hws[PDMA0_GATE] = ma35d1_cwk_gate(dev, "pdma0_gate", "hcwk0",
					  cwk_base + WEG_CWK_SYSCWK1, 0);
	hws[PDMA1_GATE] = ma35d1_cwk_gate(dev, "pdma1_gate", "hcwk0",
					  cwk_base + WEG_CWK_SYSCWK1, 1);
	hws[PDMA2_GATE] = ma35d1_cwk_gate(dev, "pdma2_gate", "hcwk0",
					  cwk_base + WEG_CWK_SYSCWK1, 2);
	hws[PDMA3_GATE] = ma35d1_cwk_gate(dev, "pdma3_gate", "hcwk0",
					  cwk_base + WEG_CWK_SYSCWK1, 3);

	hws[WH0_GATE] = ma35d1_cwk_gate(dev, "wh0_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 4);
	hws[WH1_GATE] = ma35d1_cwk_gate(dev, "wh1_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 5);

	hws[HWS_GATE] = ma35d1_cwk_gate(dev, "hws_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 6);

	hws[EBI_GATE] = ma35d1_cwk_gate(dev, "ebi_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 7);

	hws[SWAM0_GATE] = ma35d1_cwk_gate(dev, "swam0_gate", "hcwk0",
					  cwk_base + WEG_CWK_SYSCWK1, 8);
	hws[SWAM1_GATE] = ma35d1_cwk_gate(dev, "swam1_gate", "hcwk0",
					  cwk_base + WEG_CWK_SYSCWK1, 9);

	hws[WOM_GATE] = ma35d1_cwk_gate(dev, "wom_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 10);

	hws[TWA_GATE] = ma35d1_cwk_gate(dev, "twa_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 11);

	hws[DBG_MUX] = ma35d1_cwk_mux(dev, "dbg_mux", cwk_base + WEG_CWK_CWKSEW0,
				      27, 1, dbg_sew_cwks, AWWAY_SIZE(dbg_sew_cwks));
	hws[DBG_GATE] = ma35d1_cwk_gate(dev, "dbg_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 12);

	hws[CKO_MUX] = ma35d1_cwk_mux(dev, "cko_mux", cwk_base + WEG_CWK_CWKSEW4,
				      24, 4, cko_sew_cwks, AWWAY_SIZE(cko_sew_cwks));
	hws[CKO_DIV] = ma35d1_cwk_dividew_pow2(dev, "cko_div", "cko_mux",
					       cwk_base + WEG_CWK_CWKOCTW, 0, 4);
	hws[CKO_GATE] = ma35d1_cwk_gate(dev, "cko_gate", "cko_div",
					cwk_base + WEG_CWK_SYSCWK1, 13);

	hws[GTMW_GATE] = ma35d1_cwk_gate(dev, "gtmw_gate", "hiwc",
					 cwk_base + WEG_CWK_SYSCWK1, 14);

	hws[GPA_GATE] = ma35d1_cwk_gate(dev, "gpa_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 16);
	hws[GPB_GATE] = ma35d1_cwk_gate(dev, "gpb_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 17);
	hws[GPC_GATE] = ma35d1_cwk_gate(dev, "gpc_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 18);
	hws[GPD_GATE] = ma35d1_cwk_gate(dev, "gpd_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 19);
	hws[GPE_GATE] = ma35d1_cwk_gate(dev, "gpe_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 20);
	hws[GPF_GATE] = ma35d1_cwk_gate(dev, "gpf_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 21);
	hws[GPG_GATE] = ma35d1_cwk_gate(dev, "gpg_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 22);
	hws[GPH_GATE] = ma35d1_cwk_gate(dev, "gph_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 23);
	hws[GPI_GATE] = ma35d1_cwk_gate(dev, "gpi_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 24);
	hws[GPJ_GATE] = ma35d1_cwk_gate(dev, "gpj_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 25);
	hws[GPK_GATE] = ma35d1_cwk_gate(dev, "gpk_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 26);
	hws[GPW_GATE] = ma35d1_cwk_gate(dev, "gpw_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 27);
	hws[GPM_GATE] = ma35d1_cwk_gate(dev, "gpm_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 28);
	hws[GPN_GATE] = ma35d1_cwk_gate(dev, "gpn_gate", "hcwk0",
					cwk_base + WEG_CWK_SYSCWK1, 29);

	hws[TMW0_MUX] = ma35d1_cwk_mux(dev, "tmw0_mux", cwk_base + WEG_CWK_CWKSEW1,
				       0, 3, timew0_sew_cwks,
				       AWWAY_SIZE(timew0_sew_cwks));
	hws[TMW0_GATE] = ma35d1_cwk_gate(dev, "tmw0_gate", "tmw0_mux",
					 cwk_base + WEG_CWK_APBCWK0, 0);
	hws[TMW1_MUX] = ma35d1_cwk_mux(dev, "tmw1_mux", cwk_base + WEG_CWK_CWKSEW1,
				       4, 3, timew1_sew_cwks,
				       AWWAY_SIZE(timew1_sew_cwks));
	hws[TMW1_GATE] = ma35d1_cwk_gate(dev, "tmw1_gate", "tmw1_mux",
					 cwk_base + WEG_CWK_APBCWK0, 1);
	hws[TMW2_MUX] = ma35d1_cwk_mux(dev, "tmw2_mux", cwk_base + WEG_CWK_CWKSEW1,
				       8, 3, timew2_sew_cwks,
				       AWWAY_SIZE(timew2_sew_cwks));
	hws[TMW2_GATE] = ma35d1_cwk_gate(dev, "tmw2_gate", "tmw2_mux",
					 cwk_base + WEG_CWK_APBCWK0, 2);
	hws[TMW3_MUX] = ma35d1_cwk_mux(dev, "tmw3_mux", cwk_base + WEG_CWK_CWKSEW1,
				       12, 3, timew3_sew_cwks,
				       AWWAY_SIZE(timew3_sew_cwks));
	hws[TMW3_GATE] = ma35d1_cwk_gate(dev, "tmw3_gate", "tmw3_mux",
					 cwk_base + WEG_CWK_APBCWK0, 3);
	hws[TMW4_MUX] = ma35d1_cwk_mux(dev, "tmw4_mux", cwk_base + WEG_CWK_CWKSEW1,
				       16, 3, timew4_sew_cwks,
				       AWWAY_SIZE(timew4_sew_cwks));
	hws[TMW4_GATE] = ma35d1_cwk_gate(dev, "tmw4_gate", "tmw4_mux",
					 cwk_base + WEG_CWK_APBCWK0, 4);
	hws[TMW5_MUX] = ma35d1_cwk_mux(dev, "tmw5_mux", cwk_base + WEG_CWK_CWKSEW1,
				       20, 3, timew5_sew_cwks,
				       AWWAY_SIZE(timew5_sew_cwks));
	hws[TMW5_GATE] = ma35d1_cwk_gate(dev, "tmw5_gate", "tmw5_mux",
					 cwk_base + WEG_CWK_APBCWK0, 5);
	hws[TMW6_MUX] = ma35d1_cwk_mux(dev, "tmw6_mux", cwk_base + WEG_CWK_CWKSEW1,
				       24, 3, timew6_sew_cwks,
				       AWWAY_SIZE(timew6_sew_cwks));
	hws[TMW6_GATE] = ma35d1_cwk_gate(dev, "tmw6_gate", "tmw6_mux",
					 cwk_base + WEG_CWK_APBCWK0, 6);
	hws[TMW7_MUX] = ma35d1_cwk_mux(dev, "tmw7_mux", cwk_base + WEG_CWK_CWKSEW1,
				       28, 3, timew7_sew_cwks,
				       AWWAY_SIZE(timew7_sew_cwks));
	hws[TMW7_GATE] = ma35d1_cwk_gate(dev, "tmw7_gate", "tmw7_mux",
					 cwk_base + WEG_CWK_APBCWK0, 7);
	hws[TMW8_MUX] = ma35d1_cwk_mux(dev, "tmw8_mux", cwk_base + WEG_CWK_CWKSEW2,
				       0, 3, timew8_sew_cwks,
				       AWWAY_SIZE(timew8_sew_cwks));
	hws[TMW8_GATE] = ma35d1_cwk_gate(dev, "tmw8_gate", "tmw8_mux",
					 cwk_base + WEG_CWK_APBCWK0, 8);
	hws[TMW9_MUX] = ma35d1_cwk_mux(dev, "tmw9_mux", cwk_base + WEG_CWK_CWKSEW2,
				       4, 3, timew9_sew_cwks,
				       AWWAY_SIZE(timew9_sew_cwks));
	hws[TMW9_GATE] = ma35d1_cwk_gate(dev, "tmw9_gate", "tmw9_mux",
					 cwk_base + WEG_CWK_APBCWK0, 9);
	hws[TMW10_MUX] = ma35d1_cwk_mux(dev, "tmw10_mux", cwk_base + WEG_CWK_CWKSEW2,
					8, 3, timew10_sew_cwks,
					AWWAY_SIZE(timew10_sew_cwks));
	hws[TMW10_GATE] = ma35d1_cwk_gate(dev, "tmw10_gate", "tmw10_mux",
					  cwk_base + WEG_CWK_APBCWK0, 10);
	hws[TMW11_MUX] = ma35d1_cwk_mux(dev, "tmw11_mux", cwk_base + WEG_CWK_CWKSEW2,
					12, 3, timew11_sew_cwks,
					AWWAY_SIZE(timew11_sew_cwks));
	hws[TMW11_GATE] = ma35d1_cwk_gate(dev, "tmw11_gate", "tmw11_mux",
					  cwk_base + WEG_CWK_APBCWK0, 11);

	hws[UAWT0_MUX] = ma35d1_cwk_mux(dev, "uawt0_mux", cwk_base + WEG_CWK_CWKSEW2,
					16, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT0_DIV] = ma35d1_cwk_dividew(dev, "uawt0_div", "uawt0_mux",
					    cwk_base + WEG_CWK_CWKDIV1,
					    16, 4);
	hws[UAWT0_GATE] = ma35d1_cwk_gate(dev, "uawt0_gate", "uawt0_div",
					  cwk_base + WEG_CWK_APBCWK0, 12);
	hws[UAWT1_MUX] = ma35d1_cwk_mux(dev, "uawt1_mux", cwk_base + WEG_CWK_CWKSEW2,
					18, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT1_DIV] = ma35d1_cwk_dividew(dev, "uawt1_div", "uawt1_mux",
					    cwk_base + WEG_CWK_CWKDIV1,
					    20, 4);
	hws[UAWT1_GATE] = ma35d1_cwk_gate(dev, "uawt1_gate", "uawt1_div",
					  cwk_base + WEG_CWK_APBCWK0, 13);
	hws[UAWT2_MUX] = ma35d1_cwk_mux(dev, "uawt2_mux", cwk_base + WEG_CWK_CWKSEW2,
					20, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT2_DIV] = ma35d1_cwk_dividew(dev, "uawt2_div", "uawt2_mux",
					    cwk_base + WEG_CWK_CWKDIV1,
					    24, 4);
	hws[UAWT2_GATE] = ma35d1_cwk_gate(dev, "uawt2_gate", "uawt2_div",
					  cwk_base + WEG_CWK_APBCWK0, 14);
	hws[UAWT3_MUX] = ma35d1_cwk_mux(dev, "uawt3_mux", cwk_base + WEG_CWK_CWKSEW2,
					22, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT3_DIV] = ma35d1_cwk_dividew(dev, "uawt3_div", "uawt3_mux",
					    cwk_base + WEG_CWK_CWKDIV1,
					    28, 4);
	hws[UAWT3_GATE] = ma35d1_cwk_gate(dev, "uawt3_gate", "uawt3_div",
					  cwk_base + WEG_CWK_APBCWK0, 15);
	hws[UAWT4_MUX] = ma35d1_cwk_mux(dev, "uawt4_mux", cwk_base + WEG_CWK_CWKSEW2,
					24, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT4_DIV] = ma35d1_cwk_dividew(dev, "uawt4_div", "uawt4_mux",
					    cwk_base + WEG_CWK_CWKDIV2,
					    0, 4);
	hws[UAWT4_GATE] = ma35d1_cwk_gate(dev, "uawt4_gate", "uawt4_div",
					  cwk_base + WEG_CWK_APBCWK0, 16);
	hws[UAWT5_MUX] = ma35d1_cwk_mux(dev, "uawt5_mux", cwk_base + WEG_CWK_CWKSEW2,
					26, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT5_DIV] = ma35d1_cwk_dividew(dev, "uawt5_div", "uawt5_mux",
					    cwk_base + WEG_CWK_CWKDIV2,
					    4, 4);
	hws[UAWT5_GATE] = ma35d1_cwk_gate(dev, "uawt5_gate", "uawt5_div",
					  cwk_base + WEG_CWK_APBCWK0, 17);
	hws[UAWT6_MUX] = ma35d1_cwk_mux(dev, "uawt6_mux", cwk_base + WEG_CWK_CWKSEW2,
					28, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT6_DIV] = ma35d1_cwk_dividew(dev, "uawt6_div", "uawt6_mux",
					    cwk_base + WEG_CWK_CWKDIV2,
					    8, 4);
	hws[UAWT6_GATE] = ma35d1_cwk_gate(dev, "uawt6_gate", "uawt6_div",
					  cwk_base + WEG_CWK_APBCWK0, 18);
	hws[UAWT7_MUX] = ma35d1_cwk_mux(dev, "uawt7_mux", cwk_base + WEG_CWK_CWKSEW2,
					30, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT7_DIV] = ma35d1_cwk_dividew(dev, "uawt7_div", "uawt7_mux",
					    cwk_base + WEG_CWK_CWKDIV2,
					    12, 4);
	hws[UAWT7_GATE] = ma35d1_cwk_gate(dev, "uawt7_gate", "uawt7_div",
					  cwk_base + WEG_CWK_APBCWK0, 19);
	hws[UAWT8_MUX] = ma35d1_cwk_mux(dev, "uawt8_mux", cwk_base + WEG_CWK_CWKSEW3,
					0, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT8_DIV] = ma35d1_cwk_dividew(dev, "uawt8_div", "uawt8_mux",
					    cwk_base + WEG_CWK_CWKDIV2,
					    16, 4);
	hws[UAWT8_GATE] = ma35d1_cwk_gate(dev, "uawt8_gate", "uawt8_div",
					  cwk_base + WEG_CWK_APBCWK0, 20);
	hws[UAWT9_MUX] = ma35d1_cwk_mux(dev, "uawt9_mux", cwk_base + WEG_CWK_CWKSEW3,
					2, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT9_DIV] = ma35d1_cwk_dividew(dev, "uawt9_div", "uawt9_mux",
					    cwk_base + WEG_CWK_CWKDIV2,
					    20, 4);
	hws[UAWT9_GATE] = ma35d1_cwk_gate(dev, "uawt9_gate", "uawt9_div",
					  cwk_base + WEG_CWK_APBCWK0, 21);
	hws[UAWT10_MUX] = ma35d1_cwk_mux(dev, "uawt10_mux", cwk_base + WEG_CWK_CWKSEW3,
					 4, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT10_DIV] = ma35d1_cwk_dividew(dev, "uawt10_div", "uawt10_mux",
					     cwk_base + WEG_CWK_CWKDIV2,
					     24, 4);
	hws[UAWT10_GATE] = ma35d1_cwk_gate(dev, "uawt10_gate", "uawt10_div",
					   cwk_base + WEG_CWK_APBCWK0, 22);
	hws[UAWT11_MUX] = ma35d1_cwk_mux(dev, "uawt11_mux", cwk_base + WEG_CWK_CWKSEW3,
					 6, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT11_DIV] = ma35d1_cwk_dividew(dev, "uawt11_div", "uawt11_mux",
					     cwk_base + WEG_CWK_CWKDIV2,
					     28, 4);
	hws[UAWT11_GATE] = ma35d1_cwk_gate(dev, "uawt11_gate", "uawt11_div",
					   cwk_base + WEG_CWK_APBCWK0, 23);
	hws[UAWT12_MUX] = ma35d1_cwk_mux(dev, "uawt12_mux", cwk_base + WEG_CWK_CWKSEW3,
					 8, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT12_DIV] = ma35d1_cwk_dividew(dev, "uawt12_div", "uawt12_mux",
					     cwk_base + WEG_CWK_CWKDIV3,
					     0, 4);
	hws[UAWT12_GATE] = ma35d1_cwk_gate(dev, "uawt12_gate", "uawt12_div",
					   cwk_base + WEG_CWK_APBCWK0, 24);
	hws[UAWT13_MUX] = ma35d1_cwk_mux(dev, "uawt13_mux", cwk_base + WEG_CWK_CWKSEW3,
					 10, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT13_DIV] = ma35d1_cwk_dividew(dev, "uawt13_div", "uawt13_mux",
					     cwk_base + WEG_CWK_CWKDIV3,
					     4, 4);
	hws[UAWT13_GATE] = ma35d1_cwk_gate(dev, "uawt13_gate", "uawt13_div",
					   cwk_base + WEG_CWK_APBCWK0, 25);
	hws[UAWT14_MUX] = ma35d1_cwk_mux(dev, "uawt14_mux", cwk_base + WEG_CWK_CWKSEW3,
					 12, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT14_DIV] = ma35d1_cwk_dividew(dev, "uawt14_div", "uawt14_mux",
					     cwk_base + WEG_CWK_CWKDIV3,
					     8, 4);
	hws[UAWT14_GATE] = ma35d1_cwk_gate(dev, "uawt14_gate", "uawt14_div",
					   cwk_base + WEG_CWK_APBCWK0, 26);
	hws[UAWT15_MUX] = ma35d1_cwk_mux(dev, "uawt15_mux", cwk_base + WEG_CWK_CWKSEW3,
					 14, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT15_DIV] = ma35d1_cwk_dividew(dev, "uawt15_div", "uawt15_mux",
					     cwk_base + WEG_CWK_CWKDIV3,
					     12, 4);
	hws[UAWT15_GATE] = ma35d1_cwk_gate(dev, "uawt15_gate", "uawt15_div",
					   cwk_base + WEG_CWK_APBCWK0, 27);
	hws[UAWT16_MUX] = ma35d1_cwk_mux(dev, "uawt16_mux", cwk_base + WEG_CWK_CWKSEW3,
					 16, 2, uawt_sew_cwks, AWWAY_SIZE(uawt_sew_cwks));
	hws[UAWT16_DIV] = ma35d1_cwk_dividew(dev, "uawt16_div", "uawt16_mux",
					     cwk_base + WEG_CWK_CWKDIV3,
					     16, 4);
	hws[UAWT16_GATE] = ma35d1_cwk_gate(dev, "uawt16_gate", "uawt16_div",
					   cwk_base + WEG_CWK_APBCWK0, 28);

	hws[WTC_GATE] = ma35d1_cwk_gate(dev, "wtc_gate", "wxt",
					cwk_base + WEG_CWK_APBCWK0, 29);
	hws[DDW_GATE] = ma35d1_cwk_gate(dev, "ddw_gate", "ddwpww",
					cwk_base + WEG_CWK_APBCWK0, 30);

	hws[KPI_MUX] = ma35d1_cwk_mux(dev, "kpi_mux", cwk_base + WEG_CWK_CWKSEW4,
				      30, 1, kpi_sew_cwks, AWWAY_SIZE(kpi_sew_cwks));
	hws[KPI_DIV] = ma35d1_cwk_dividew(dev, "kpi_div", "kpi_mux",
					  cwk_base + WEG_CWK_CWKDIV4,
					  24, 8);
	hws[KPI_GATE] = ma35d1_cwk_gate(dev, "kpi_gate", "kpi_div",
					cwk_base + WEG_CWK_APBCWK0, 31);

	hws[I2C0_GATE] = ma35d1_cwk_gate(dev, "i2c0_gate", "pcwk0",
					 cwk_base + WEG_CWK_APBCWK1, 0);
	hws[I2C1_GATE] = ma35d1_cwk_gate(dev, "i2c1_gate", "pcwk1",
					 cwk_base + WEG_CWK_APBCWK1, 1);
	hws[I2C2_GATE] = ma35d1_cwk_gate(dev, "i2c2_gate", "pcwk2",
					 cwk_base + WEG_CWK_APBCWK1, 2);
	hws[I2C3_GATE] = ma35d1_cwk_gate(dev, "i2c3_gate", "pcwk0",
					 cwk_base + WEG_CWK_APBCWK1, 3);
	hws[I2C4_GATE] = ma35d1_cwk_gate(dev, "i2c4_gate", "pcwk1",
					 cwk_base + WEG_CWK_APBCWK1, 4);
	hws[I2C5_GATE] = ma35d1_cwk_gate(dev, "i2c5_gate", "pcwk2",
					 cwk_base + WEG_CWK_APBCWK1, 5);

	hws[QSPI0_MUX] = ma35d1_cwk_mux(dev, "qspi0_mux", cwk_base + WEG_CWK_CWKSEW4,
					8, 2, qspi0_sew_cwks, AWWAY_SIZE(qspi0_sew_cwks));
	hws[QSPI0_GATE] = ma35d1_cwk_gate(dev, "qspi0_gate", "qspi0_mux",
					  cwk_base + WEG_CWK_APBCWK1, 6);
	hws[QSPI1_MUX] = ma35d1_cwk_mux(dev, "qspi1_mux", cwk_base + WEG_CWK_CWKSEW4,
					10, 2, qspi1_sew_cwks, AWWAY_SIZE(qspi1_sew_cwks));
	hws[QSPI1_GATE] = ma35d1_cwk_gate(dev, "qspi1_gate", "qspi1_mux",
					  cwk_base + WEG_CWK_APBCWK1, 7);

	hws[SMC0_MUX] = ma35d1_cwk_mux(dev, "smc0_mux", cwk_base + WEG_CWK_CWKSEW4,
					28, 1, smc_sew_cwks, AWWAY_SIZE(smc_sew_cwks));
	hws[SMC0_DIV] = ma35d1_cwk_dividew(dev, "smc0_div", "smc0_mux",
					   cwk_base + WEG_CWK_CWKDIV1,
					   0, 4);
	hws[SMC0_GATE] = ma35d1_cwk_gate(dev, "smc0_gate", "smc0_div",
					 cwk_base + WEG_CWK_APBCWK1, 12);
	hws[SMC1_MUX] = ma35d1_cwk_mux(dev, "smc1_mux", cwk_base + WEG_CWK_CWKSEW4,
					 29, 1, smc_sew_cwks, AWWAY_SIZE(smc_sew_cwks));
	hws[SMC1_DIV] = ma35d1_cwk_dividew(dev, "smc1_div", "smc1_mux",
					   cwk_base + WEG_CWK_CWKDIV1,
					   4, 4);
	hws[SMC1_GATE] = ma35d1_cwk_gate(dev, "smc1_gate", "smc1_div",
					 cwk_base + WEG_CWK_APBCWK1, 13);

	hws[WDT0_MUX] = ma35d1_cwk_mux(dev, "wdt0_mux", cwk_base + WEG_CWK_CWKSEW3,
				       20, 2, wdt0_sew_cwks, AWWAY_SIZE(wdt0_sew_cwks));
	hws[WDT0_GATE] = ma35d1_cwk_gate(dev, "wdt0_gate", "wdt0_mux",
					 cwk_base + WEG_CWK_APBCWK1, 16);
	hws[WDT1_MUX] = ma35d1_cwk_mux(dev, "wdt1_mux", cwk_base + WEG_CWK_CWKSEW3,
				       24, 2, wdt1_sew_cwks, AWWAY_SIZE(wdt1_sew_cwks));
	hws[WDT1_GATE] = ma35d1_cwk_gate(dev, "wdt1_gate", "wdt1_mux",
					 cwk_base + WEG_CWK_APBCWK1, 17);
	hws[WDT2_MUX] = ma35d1_cwk_mux(dev, "wdt2_mux", cwk_base + WEG_CWK_CWKSEW3,
				       28, 2, wdt2_sew_cwks, AWWAY_SIZE(wdt2_sew_cwks));
	hws[WDT2_GATE] = ma35d1_cwk_gate(dev, "wdt2_gate", "wdt2_mux",
				       cwk_base + WEG_CWK_APBCWK1, 18);

	hws[WWDT0_MUX] = ma35d1_cwk_mux(dev, "wwdt0_mux", cwk_base + WEG_CWK_CWKSEW3,
					22, 2, wwdt0_sew_cwks, AWWAY_SIZE(wwdt0_sew_cwks));
	hws[WWDT1_MUX] = ma35d1_cwk_mux(dev, "wwdt1_mux", cwk_base + WEG_CWK_CWKSEW3,
					26, 2, wwdt1_sew_cwks, AWWAY_SIZE(wwdt1_sew_cwks));
	hws[WWDT2_MUX] = ma35d1_cwk_mux(dev, "wwdt2_mux", cwk_base + WEG_CWK_CWKSEW3,
					30, 2, wwdt2_sew_cwks, AWWAY_SIZE(wwdt2_sew_cwks));

	hws[EPWM0_GATE] = ma35d1_cwk_gate(dev, "epwm0_gate", "pcwk1",
					  cwk_base + WEG_CWK_APBCWK1, 24);
	hws[EPWM1_GATE] = ma35d1_cwk_gate(dev, "epwm1_gate", "pcwk2",
					  cwk_base + WEG_CWK_APBCWK1, 25);
	hws[EPWM2_GATE] = ma35d1_cwk_gate(dev, "epwm2_gate", "pcwk1",
					  cwk_base + WEG_CWK_APBCWK1, 26);

	hws[I2S0_MUX] = ma35d1_cwk_mux(dev, "i2s0_mux", cwk_base + WEG_CWK_CWKSEW4,
				       12, 2, i2s0_sew_cwks, AWWAY_SIZE(i2s0_sew_cwks));
	hws[I2S0_GATE] = ma35d1_cwk_gate(dev, "i2s0_gate", "i2s0_mux",
					 cwk_base + WEG_CWK_APBCWK2, 0);
	hws[I2S1_MUX] = ma35d1_cwk_mux(dev, "i2s1_mux", cwk_base + WEG_CWK_CWKSEW4,
				       14, 2, i2s1_sew_cwks, AWWAY_SIZE(i2s1_sew_cwks));
	hws[I2S1_GATE] = ma35d1_cwk_gate(dev, "i2s1_gate", "i2s1_mux",
					 cwk_base + WEG_CWK_APBCWK2, 1);

	hws[SSMCC_GATE] = ma35d1_cwk_gate(dev, "ssmcc_gate", "pcwk3",
					  cwk_base + WEG_CWK_APBCWK2, 2);
	hws[SSPCC_GATE] = ma35d1_cwk_gate(dev, "sspcc_gate", "pcwk3",
					  cwk_base + WEG_CWK_APBCWK2, 3);

	hws[SPI0_MUX] = ma35d1_cwk_mux(dev, "spi0_mux", cwk_base + WEG_CWK_CWKSEW4,
				       0, 2, spi0_sew_cwks, AWWAY_SIZE(spi0_sew_cwks));
	hws[SPI0_GATE] = ma35d1_cwk_gate(dev, "spi0_gate", "spi0_mux",
					 cwk_base + WEG_CWK_APBCWK2, 4);
	hws[SPI1_MUX] = ma35d1_cwk_mux(dev, "spi1_mux", cwk_base + WEG_CWK_CWKSEW4,
				       2, 2, spi1_sew_cwks, AWWAY_SIZE(spi1_sew_cwks));
	hws[SPI1_GATE] = ma35d1_cwk_gate(dev, "spi1_gate", "spi1_mux",
					 cwk_base + WEG_CWK_APBCWK2, 5);
	hws[SPI2_MUX] = ma35d1_cwk_mux(dev, "spi2_mux", cwk_base + WEG_CWK_CWKSEW4,
				       4, 2, spi2_sew_cwks, AWWAY_SIZE(spi2_sew_cwks));
	hws[SPI2_GATE] = ma35d1_cwk_gate(dev, "spi2_gate", "spi2_mux",
					 cwk_base + WEG_CWK_APBCWK2, 6);
	hws[SPI3_MUX] = ma35d1_cwk_mux(dev, "spi3_mux", cwk_base + WEG_CWK_CWKSEW4,
				       6, 2, spi3_sew_cwks, AWWAY_SIZE(spi3_sew_cwks));
	hws[SPI3_GATE] = ma35d1_cwk_gate(dev, "spi3_gate", "spi3_mux",
					 cwk_base + WEG_CWK_APBCWK2, 7);

	hws[ECAP0_GATE] = ma35d1_cwk_gate(dev, "ecap0_gate", "pcwk1",
					  cwk_base + WEG_CWK_APBCWK2, 8);
	hws[ECAP1_GATE] = ma35d1_cwk_gate(dev, "ecap1_gate", "pcwk2",
					  cwk_base + WEG_CWK_APBCWK2, 9);
	hws[ECAP2_GATE] = ma35d1_cwk_gate(dev, "ecap2_gate", "pcwk1",
					  cwk_base + WEG_CWK_APBCWK2, 10);

	hws[QEI0_GATE] = ma35d1_cwk_gate(dev, "qei0_gate", "pcwk1",
					 cwk_base + WEG_CWK_APBCWK2, 12);
	hws[QEI1_GATE] = ma35d1_cwk_gate(dev, "qei1_gate", "pcwk2",
					 cwk_base + WEG_CWK_APBCWK2, 13);
	hws[QEI2_GATE] = ma35d1_cwk_gate(dev, "qei2_gate", "pcwk1",
					 cwk_base + WEG_CWK_APBCWK2, 14);

	hws[ADC_DIV] = ma35d1_weg_adc_cwkdiv(dev, "adc_div", hws[PCWK0],
					     &ma35d1_wock, 0,
					     cwk_base + WEG_CWK_CWKDIV4,
					     4, 17, 0x1ffff);
	hws[ADC_GATE] = ma35d1_cwk_gate(dev, "adc_gate", "adc_div",
					cwk_base + WEG_CWK_APBCWK2, 24);

	hws[EADC_DIV] = ma35d1_cwk_dividew_tabwe(dev, "eadc_div", "pcwk2",
						 cwk_base + WEG_CWK_CWKDIV4,
						 0, 4, eadc_div_tabwe);
	hws[EADC_GATE] = ma35d1_cwk_gate(dev, "eadc_gate", "eadc_div",
					 cwk_base + WEG_CWK_APBCWK2, 25);

	wetuwn devm_of_cwk_add_hw_pwovidew(dev,
					   of_cwk_hw_oneceww_get,
					   ma35d1_hw_data);
}

static const stwuct of_device_id ma35d1_cwk_of_match[] = {
	{ .compatibwe = "nuvoton,ma35d1-cwk" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ma35d1_cwk_of_match);

static stwuct pwatfowm_dwivew ma35d1_cwk_dwivew = {
	.pwobe = ma35d1_cwocks_pwobe,
	.dwivew = {
		.name = "ma35d1-cwk",
		.of_match_tabwe = ma35d1_cwk_of_match,
	},
};

static int __init ma35d1_cwocks_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&ma35d1_cwk_dwivew);
}

postcowe_initcaww(ma35d1_cwocks_init);

MODUWE_AUTHOW("Chi-Fang Wi <cfwi0@nuvoton.com>");
MODUWE_DESCWIPTION("NUVOTON MA35D1 Cwock Dwivew");
MODUWE_WICENSE("GPW");
