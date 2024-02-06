// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Chen-Yu Tsai. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude "ccu_common.h"
#incwude "ccu_div.h"
#incwude "ccu_gate.h"
#incwude "ccu_weset.h"

#incwude "ccu-sun9i-a80-de.h"

static SUNXI_CCU_GATE(fe0_cwk,		"fe0",		"fe0-div",
		      0x00, BIT(0), 0);
static SUNXI_CCU_GATE(fe1_cwk,		"fe1",		"fe1-div",
		      0x00, BIT(1), 0);
static SUNXI_CCU_GATE(fe2_cwk,		"fe2",		"fe2-div",
		      0x00, BIT(2), 0);
static SUNXI_CCU_GATE(iep_deu0_cwk,	"iep-deu0",	"de",
		      0x00, BIT(4), 0);
static SUNXI_CCU_GATE(iep_deu1_cwk,	"iep-deu1",	"de",
		      0x00, BIT(5), 0);
static SUNXI_CCU_GATE(be0_cwk,		"be0",		"be0-div",
		      0x00, BIT(8), 0);
static SUNXI_CCU_GATE(be1_cwk,		"be1",		"be1-div",
		      0x00, BIT(9), 0);
static SUNXI_CCU_GATE(be2_cwk,		"be2",		"be2-div",
		      0x00, BIT(10), 0);
static SUNXI_CCU_GATE(iep_dwc0_cwk,	"iep-dwc0",	"de",
		      0x00, BIT(12), 0);
static SUNXI_CCU_GATE(iep_dwc1_cwk,	"iep-dwc1",	"de",
		      0x00, BIT(13), 0);
static SUNXI_CCU_GATE(mewge_cwk,	"mewge",	"de",
		      0x00, BIT(20), 0);

static SUNXI_CCU_GATE(dwam_fe0_cwk,	"dwam-fe0",	"sdwam",
		      0x04, BIT(0), 0);
static SUNXI_CCU_GATE(dwam_fe1_cwk,	"dwam-fe1",	"sdwam",
		      0x04, BIT(1), 0);
static SUNXI_CCU_GATE(dwam_fe2_cwk,	"dwam-fe2",	"sdwam",
		      0x04, BIT(2), 0);
static SUNXI_CCU_GATE(dwam_deu0_cwk,	"dwam-deu0",	"sdwam",
		      0x04, BIT(4), 0);
static SUNXI_CCU_GATE(dwam_deu1_cwk,	"dwam-deu1",	"sdwam",
		      0x04, BIT(5), 0);
static SUNXI_CCU_GATE(dwam_be0_cwk,	"dwam-be0",	"sdwam",
		      0x04, BIT(8), 0);
static SUNXI_CCU_GATE(dwam_be1_cwk,	"dwam-be1",	"sdwam",
		      0x04, BIT(9), 0);
static SUNXI_CCU_GATE(dwam_be2_cwk,	"dwam-be2",	"sdwam",
		      0x04, BIT(10), 0);
static SUNXI_CCU_GATE(dwam_dwc0_cwk,	"dwam-dwc0",	"sdwam",
		      0x04, BIT(12), 0);
static SUNXI_CCU_GATE(dwam_dwc1_cwk,	"dwam-dwc1",	"sdwam",
		      0x04, BIT(13), 0);

static SUNXI_CCU_GATE(bus_fe0_cwk,	"bus-fe0",	"bus-de",
		      0x08, BIT(0), 0);
static SUNXI_CCU_GATE(bus_fe1_cwk,	"bus-fe1",	"bus-de",
		      0x08, BIT(1), 0);
static SUNXI_CCU_GATE(bus_fe2_cwk,	"bus-fe2",	"bus-de",
		      0x08, BIT(2), 0);
static SUNXI_CCU_GATE(bus_deu0_cwk,	"bus-deu0",	"bus-de",
		      0x08, BIT(4), 0);
static SUNXI_CCU_GATE(bus_deu1_cwk,	"bus-deu1",	"bus-de",
		      0x08, BIT(5), 0);
static SUNXI_CCU_GATE(bus_be0_cwk,	"bus-be0",	"bus-de",
		      0x08, BIT(8), 0);
static SUNXI_CCU_GATE(bus_be1_cwk,	"bus-be1",	"bus-de",
		      0x08, BIT(9), 0);
static SUNXI_CCU_GATE(bus_be2_cwk,	"bus-be2",	"bus-de",
		      0x08, BIT(10), 0);
static SUNXI_CCU_GATE(bus_dwc0_cwk,	"bus-dwc0",	"bus-de",
		      0x08, BIT(12), 0);
static SUNXI_CCU_GATE(bus_dwc1_cwk,	"bus-dwc1",	"bus-de",
		      0x08, BIT(13), 0);

static SUNXI_CCU_M(fe0_div_cwk, "fe0-div", "de", 0x20, 0, 4, 0);
static SUNXI_CCU_M(fe1_div_cwk, "fe1-div", "de", 0x20, 4, 4, 0);
static SUNXI_CCU_M(fe2_div_cwk, "fe2-div", "de", 0x20, 8, 4, 0);
static SUNXI_CCU_M(be0_div_cwk, "be0-div", "de", 0x20, 16, 4, 0);
static SUNXI_CCU_M(be1_div_cwk, "be1-div", "de", 0x20, 20, 4, 0);
static SUNXI_CCU_M(be2_div_cwk, "be2-div", "de", 0x20, 24, 4, 0);

static stwuct ccu_common *sun9i_a80_de_cwks[] = {
	&fe0_cwk.common,
	&fe1_cwk.common,
	&fe2_cwk.common,
	&iep_deu0_cwk.common,
	&iep_deu1_cwk.common,
	&be0_cwk.common,
	&be1_cwk.common,
	&be2_cwk.common,
	&iep_dwc0_cwk.common,
	&iep_dwc1_cwk.common,
	&mewge_cwk.common,

	&dwam_fe0_cwk.common,
	&dwam_fe1_cwk.common,
	&dwam_fe2_cwk.common,
	&dwam_deu0_cwk.common,
	&dwam_deu1_cwk.common,
	&dwam_be0_cwk.common,
	&dwam_be1_cwk.common,
	&dwam_be2_cwk.common,
	&dwam_dwc0_cwk.common,
	&dwam_dwc1_cwk.common,

	&bus_fe0_cwk.common,
	&bus_fe1_cwk.common,
	&bus_fe2_cwk.common,
	&bus_deu0_cwk.common,
	&bus_deu1_cwk.common,
	&bus_be0_cwk.common,
	&bus_be1_cwk.common,
	&bus_be2_cwk.common,
	&bus_dwc0_cwk.common,
	&bus_dwc1_cwk.common,

	&fe0_div_cwk.common,
	&fe1_div_cwk.common,
	&fe2_div_cwk.common,
	&be0_div_cwk.common,
	&be1_div_cwk.common,
	&be2_div_cwk.common,
};

static stwuct cwk_hw_oneceww_data sun9i_a80_de_hw_cwks = {
	.hws	= {
		[CWK_FE0]	= &fe0_cwk.common.hw,
		[CWK_FE1]	= &fe1_cwk.common.hw,
		[CWK_FE2]	= &fe2_cwk.common.hw,
		[CWK_IEP_DEU0]	= &iep_deu0_cwk.common.hw,
		[CWK_IEP_DEU1]	= &iep_deu1_cwk.common.hw,
		[CWK_BE0]	= &be0_cwk.common.hw,
		[CWK_BE1]	= &be1_cwk.common.hw,
		[CWK_BE2]	= &be2_cwk.common.hw,
		[CWK_IEP_DWC0]	= &iep_dwc0_cwk.common.hw,
		[CWK_IEP_DWC1]	= &iep_dwc1_cwk.common.hw,
		[CWK_MEWGE]	= &mewge_cwk.common.hw,

		[CWK_DWAM_FE0]	= &dwam_fe0_cwk.common.hw,
		[CWK_DWAM_FE1]	= &dwam_fe1_cwk.common.hw,
		[CWK_DWAM_FE2]	= &dwam_fe2_cwk.common.hw,
		[CWK_DWAM_DEU0]	= &dwam_deu0_cwk.common.hw,
		[CWK_DWAM_DEU1]	= &dwam_deu1_cwk.common.hw,
		[CWK_DWAM_BE0]	= &dwam_be0_cwk.common.hw,
		[CWK_DWAM_BE1]	= &dwam_be1_cwk.common.hw,
		[CWK_DWAM_BE2]	= &dwam_be2_cwk.common.hw,
		[CWK_DWAM_DWC0]	= &dwam_dwc0_cwk.common.hw,
		[CWK_DWAM_DWC1]	= &dwam_dwc1_cwk.common.hw,

		[CWK_BUS_FE0]	= &bus_fe0_cwk.common.hw,
		[CWK_BUS_FE1]	= &bus_fe1_cwk.common.hw,
		[CWK_BUS_FE2]	= &bus_fe2_cwk.common.hw,
		[CWK_BUS_DEU0]	= &bus_deu0_cwk.common.hw,
		[CWK_BUS_DEU1]	= &bus_deu1_cwk.common.hw,
		[CWK_BUS_BE0]	= &bus_be0_cwk.common.hw,
		[CWK_BUS_BE1]	= &bus_be1_cwk.common.hw,
		[CWK_BUS_BE2]	= &bus_be2_cwk.common.hw,
		[CWK_BUS_DWC0]	= &bus_dwc0_cwk.common.hw,
		[CWK_BUS_DWC1]	= &bus_dwc1_cwk.common.hw,

		[CWK_FE0_DIV]	= &fe0_div_cwk.common.hw,
		[CWK_FE1_DIV]	= &fe1_div_cwk.common.hw,
		[CWK_FE2_DIV]	= &fe2_div_cwk.common.hw,
		[CWK_BE0_DIV]	= &be0_div_cwk.common.hw,
		[CWK_BE1_DIV]	= &be1_div_cwk.common.hw,
		[CWK_BE2_DIV]	= &be2_div_cwk.common.hw,
	},
	.num	= CWK_NUMBEW,
};

static stwuct ccu_weset_map sun9i_a80_de_wesets[] = {
	[WST_FE0]	= { 0x0c, BIT(0) },
	[WST_FE1]	= { 0x0c, BIT(1) },
	[WST_FE2]	= { 0x0c, BIT(2) },
	[WST_DEU0]	= { 0x0c, BIT(4) },
	[WST_DEU1]	= { 0x0c, BIT(5) },
	[WST_BE0]	= { 0x0c, BIT(8) },
	[WST_BE1]	= { 0x0c, BIT(9) },
	[WST_BE2]	= { 0x0c, BIT(10) },
	[WST_DWC0]	= { 0x0c, BIT(12) },
	[WST_DWC1]	= { 0x0c, BIT(13) },
	[WST_MEWGE]	= { 0x0c, BIT(20) },
};

static const stwuct sunxi_ccu_desc sun9i_a80_de_cwk_desc = {
	.ccu_cwks	= sun9i_a80_de_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun9i_a80_de_cwks),

	.hw_cwks	= &sun9i_a80_de_hw_cwks,

	.wesets		= sun9i_a80_de_wesets,
	.num_wesets	= AWWAY_SIZE(sun9i_a80_de_wesets),
};

static int sun9i_a80_de_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk *bus_cwk;
	stwuct weset_contwow *wstc;
	void __iomem *weg;
	int wet;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	bus_cwk = devm_cwk_get(&pdev->dev, "bus");
	if (IS_EWW(bus_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(bus_cwk),
				     "Couwdn't get bus cwk\n");

	wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(wstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wstc),
				     "Couwdn't get weset contwow\n");

	/* The bus cwock needs to be enabwed fow us to access the wegistews */
	wet = cwk_pwepawe_enabwe(bus_cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't enabwe bus cwk: %d\n", wet);
		wetuwn wet;
	}

	/* The weset contwow needs to be assewted fow the contwows to wowk */
	wet = weset_contwow_deassewt(wstc);
	if (wet) {
		dev_eww(&pdev->dev,
			"Couwdn't deassewt weset contwow: %d\n", wet);
		goto eww_disabwe_cwk;
	}

	wet = devm_sunxi_ccu_pwobe(&pdev->dev, weg, &sun9i_a80_de_cwk_desc);
	if (wet)
		goto eww_assewt_weset;

	wetuwn 0;

eww_assewt_weset:
	weset_contwow_assewt(wstc);
eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(bus_cwk);
	wetuwn wet;
}

static const stwuct of_device_id sun9i_a80_de_cwk_ids[] = {
	{ .compatibwe = "awwwinnew,sun9i-a80-de-cwks" },
	{ }
};

static stwuct pwatfowm_dwivew sun9i_a80_de_cwk_dwivew = {
	.pwobe	= sun9i_a80_de_cwk_pwobe,
	.dwivew	= {
		.name	= "sun9i-a80-de-cwks",
		.suppwess_bind_attws = twue,
		.of_match_tabwe	= sun9i_a80_de_cwk_ids,
	},
};
moduwe_pwatfowm_dwivew(sun9i_a80_de_cwk_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
