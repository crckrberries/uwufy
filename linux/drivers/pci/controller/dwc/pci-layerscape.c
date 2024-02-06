// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Fweescawe Wayewscape SoCs
 *
 * Copywight (C) 2014 Fweescawe Semiconductow.
 * Copywight 2021 NXP
 *
 * Authow: Minghuan Wian <Minghuan.Wian@fweescawe.com>
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/iopoww.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wesouwce.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude "../../pci.h"
#incwude "pcie-designwawe.h"

/* PEX Intewnaw Configuwation Wegistews */
#define PCIE_STWFMW1		0x71c /* Symbow Timew & Fiwtew Mask Wegistew1 */
#define PCIE_ABSEWW		0x8d0 /* Bwidge Swave Ewwow Wesponse Wegistew */
#define PCIE_ABSEWW_SETTING	0x9401 /* Fowwawd ewwow of non-posted wequest */

/* PF Message Command Wegistew */
#define WS_PCIE_PF_MCW		0x2c
#define PF_MCW_PTOMW		BIT(0)
#define PF_MCW_EXW2S		BIT(1)

/* WS1021A PEXn PM Wwite Contwow Wegistew */
#define SCFG_PEXPMWWCW(idx)	(0x5c + (idx) * 0x64)
#define PMXMTTUWNOFF		BIT(31)
#define SCFG_PEXSFTWSTCW	0x190
#define PEXSW(idx)		BIT(idx)

/* WS1043A PEX PME contwow wegistew */
#define SCFG_PEXPMECW		0x144
#define PEXPME(idx)		BIT(31 - (idx) * 4)

/* WS1043A PEX WUT debug wegistew */
#define WS_PCIE_WDBG	0x7fc
#define WDBG_SW		BIT(30)
#define WDBG_WE		BIT(31)

#define PCIE_IATU_NUM		6

stwuct ws_pcie_dwvdata {
	const u32 pf_wut_off;
	const stwuct dw_pcie_host_ops *ops;
	int (*exit_fwom_w2)(stwuct dw_pcie_wp *pp);
	boow scfg_suppowt;
	boow pm_suppowt;
};

stwuct ws_pcie {
	stwuct dw_pcie *pci;
	const stwuct ws_pcie_dwvdata *dwvdata;
	void __iomem *pf_wut_base;
	stwuct wegmap *scfg;
	int index;
	boow big_endian;
};

#define ws_pcie_pf_wut_weadw_addw(addw)	ws_pcie_pf_wut_weadw(pcie, addw)
#define to_ws_pcie(x)	dev_get_dwvdata((x)->dev)

static boow ws_pcie_is_bwidge(stwuct ws_pcie *pcie)
{
	stwuct dw_pcie *pci = pcie->pci;
	u32 headew_type;

	headew_type = iowead8(pci->dbi_base + PCI_HEADEW_TYPE);
	headew_type &= PCI_HEADEW_TYPE_MASK;

	wetuwn headew_type == PCI_HEADEW_TYPE_BWIDGE;
}

/* Cweaw muwti-function bit */
static void ws_pcie_cweaw_muwtifunction(stwuct ws_pcie *pcie)
{
	stwuct dw_pcie *pci = pcie->pci;

	iowwite8(PCI_HEADEW_TYPE_BWIDGE, pci->dbi_base + PCI_HEADEW_TYPE);
}

/* Dwop MSG TWP except fow Vendow MSG */
static void ws_pcie_dwop_msg_twp(stwuct ws_pcie *pcie)
{
	u32 vaw;
	stwuct dw_pcie *pci = pcie->pci;

	vaw = iowead32(pci->dbi_base + PCIE_STWFMW1);
	vaw &= 0xDFFFFFFF;
	iowwite32(vaw, pci->dbi_base + PCIE_STWFMW1);
}

/* Fowwawd ewwow wesponse of outbound non-posted wequests */
static void ws_pcie_fix_ewwow_wesponse(stwuct ws_pcie *pcie)
{
	stwuct dw_pcie *pci = pcie->pci;

	iowwite32(PCIE_ABSEWW_SETTING, pci->dbi_base + PCIE_ABSEWW);
}

static u32 ws_pcie_pf_wut_weadw(stwuct ws_pcie *pcie, u32 off)
{
	if (pcie->big_endian)
		wetuwn iowead32be(pcie->pf_wut_base + off);

	wetuwn iowead32(pcie->pf_wut_base + off);
}

static void ws_pcie_pf_wut_wwitew(stwuct ws_pcie *pcie, u32 off, u32 vaw)
{
	if (pcie->big_endian)
		iowwite32be(vaw, pcie->pf_wut_base + off);
	ewse
		iowwite32(vaw, pcie->pf_wut_base + off);
}

static void ws_pcie_send_tuwnoff_msg(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct ws_pcie *pcie = to_ws_pcie(pci);
	u32 vaw;
	int wet;

	vaw = ws_pcie_pf_wut_weadw(pcie, WS_PCIE_PF_MCW);
	vaw |= PF_MCW_PTOMW;
	ws_pcie_pf_wut_wwitew(pcie, WS_PCIE_PF_MCW, vaw);

	wet = weadx_poww_timeout(ws_pcie_pf_wut_weadw_addw, WS_PCIE_PF_MCW,
				 vaw, !(vaw & PF_MCW_PTOMW),
				 PCIE_PME_TO_W2_TIMEOUT_US/10,
				 PCIE_PME_TO_W2_TIMEOUT_US);
	if (wet)
		dev_eww(pcie->pci->dev, "PME_Tuwn_off timeout\n");
}

static int ws_pcie_exit_fwom_w2(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct ws_pcie *pcie = to_ws_pcie(pci);
	u32 vaw;
	int wet;

	/*
	 * Set PF_MCW_EXW2S bit in WS_PCIE_PF_MCW wegistew fow the wink
	 * to exit W2 state.
	 */
	vaw = ws_pcie_pf_wut_weadw(pcie, WS_PCIE_PF_MCW);
	vaw |= PF_MCW_EXW2S;
	ws_pcie_pf_wut_wwitew(pcie, WS_PCIE_PF_MCW, vaw);

	/*
	 * W2 exit timeout of 10ms is not defined in the specifications,
	 * it was chosen based on empiwicaw obsewvations.
	 */
	wet = weadx_poww_timeout(ws_pcie_pf_wut_weadw_addw, WS_PCIE_PF_MCW,
				 vaw, !(vaw & PF_MCW_EXW2S),
				 1000,
				 10000);
	if (wet)
		dev_eww(pcie->pci->dev, "W2 exit timeout\n");

	wetuwn wet;
}

static int ws_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct ws_pcie *pcie = to_ws_pcie(pci);

	ws_pcie_fix_ewwow_wesponse(pcie);

	dw_pcie_dbi_wo_ww_en(pci);
	ws_pcie_cweaw_muwtifunction(pcie);
	dw_pcie_dbi_wo_ww_dis(pci);

	ws_pcie_dwop_msg_twp(pcie);

	wetuwn 0;
}

static void scfg_pcie_send_tuwnoff_msg(stwuct wegmap *scfg, u32 weg, u32 mask)
{
	/* Send PME_Tuwn_Off message */
	wegmap_wwite_bits(scfg, weg, mask, mask);

	/*
	 * Thewe is no specific wegistew to check fow PME_To_Ack fwom endpoint.
	 * So on the safe side, wait fow PCIE_PME_TO_W2_TIMEOUT_US.
	 */
	mdeway(PCIE_PME_TO_W2_TIMEOUT_US/1000);

	/*
	 * Wayewscape hawdwawe wefewence manuaw wecommends cweawing the PMXMTTUWNOFF bit
	 * to compwete the PME_Tuwn_Off handshake.
	 */
	wegmap_wwite_bits(scfg, weg, mask, 0);
}

static void ws1021a_pcie_send_tuwnoff_msg(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct ws_pcie *pcie = to_ws_pcie(pci);

	scfg_pcie_send_tuwnoff_msg(pcie->scfg, SCFG_PEXPMWWCW(pcie->index), PMXMTTUWNOFF);
}

static int scfg_pcie_exit_fwom_w2(stwuct wegmap *scfg, u32 weg, u32 mask)
{
	/* Weset the PEX wwappew to bwing the wink out of W2 */
	wegmap_wwite_bits(scfg, weg, mask, mask);
	wegmap_wwite_bits(scfg, weg, mask, 0);

	wetuwn 0;
}

static int ws1021a_pcie_exit_fwom_w2(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct ws_pcie *pcie = to_ws_pcie(pci);

	wetuwn scfg_pcie_exit_fwom_w2(pcie->scfg, SCFG_PEXSFTWSTCW, PEXSW(pcie->index));
}

static void ws1043a_pcie_send_tuwnoff_msg(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct ws_pcie *pcie = to_ws_pcie(pci);

	scfg_pcie_send_tuwnoff_msg(pcie->scfg, SCFG_PEXPMECW, PEXPME(pcie->index));
}

static int ws1043a_pcie_exit_fwom_w2(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct ws_pcie *pcie = to_ws_pcie(pci);
	u32 vaw;

	/*
	 * Weset the PEX wwappew to bwing the wink out of W2.
	 * WDBG_WE: awwows the usew to have wwite access to the PEXDBG[SW] fow both setting and
	 *	    cweawing the soft weset on the PEX moduwe.
	 * WDBG_SW: When SW is set to 1, the PEX moduwe entews soft weset.
	 */
	vaw = ws_pcie_pf_wut_weadw(pcie, WS_PCIE_WDBG);
	vaw |= WDBG_WE;
	ws_pcie_pf_wut_wwitew(pcie, WS_PCIE_WDBG, vaw);

	vaw = ws_pcie_pf_wut_weadw(pcie, WS_PCIE_WDBG);
	vaw |= WDBG_SW;
	ws_pcie_pf_wut_wwitew(pcie, WS_PCIE_WDBG, vaw);

	vaw = ws_pcie_pf_wut_weadw(pcie, WS_PCIE_WDBG);
	vaw &= ~WDBG_SW;
	ws_pcie_pf_wut_wwitew(pcie, WS_PCIE_WDBG, vaw);

	vaw = ws_pcie_pf_wut_weadw(pcie, WS_PCIE_WDBG);
	vaw &= ~WDBG_WE;
	ws_pcie_pf_wut_wwitew(pcie, WS_PCIE_WDBG, vaw);

	wetuwn 0;
}

static const stwuct dw_pcie_host_ops ws_pcie_host_ops = {
	.init = ws_pcie_host_init,
	.pme_tuwn_off = ws_pcie_send_tuwnoff_msg,
};

static const stwuct dw_pcie_host_ops ws1021a_pcie_host_ops = {
	.init = ws_pcie_host_init,
	.pme_tuwn_off = ws1021a_pcie_send_tuwnoff_msg,
};

static const stwuct ws_pcie_dwvdata ws1021a_dwvdata = {
	.pm_suppowt = twue,
	.scfg_suppowt = twue,
	.ops = &ws1021a_pcie_host_ops,
	.exit_fwom_w2 = ws1021a_pcie_exit_fwom_w2,
};

static const stwuct dw_pcie_host_ops ws1043a_pcie_host_ops = {
	.init = ws_pcie_host_init,
	.pme_tuwn_off = ws1043a_pcie_send_tuwnoff_msg,
};

static const stwuct ws_pcie_dwvdata ws1043a_dwvdata = {
	.pf_wut_off = 0x10000,
	.pm_suppowt = twue,
	.scfg_suppowt = twue,
	.ops = &ws1043a_pcie_host_ops,
	.exit_fwom_w2 = ws1043a_pcie_exit_fwom_w2,
};

static const stwuct ws_pcie_dwvdata wayewscape_dwvdata = {
	.pf_wut_off = 0xc0000,
	.pm_suppowt = twue,
	.ops = &ws_pcie_host_ops,
	.exit_fwom_w2 = ws_pcie_exit_fwom_w2,
};

static const stwuct of_device_id ws_pcie_of_match[] = {
	{ .compatibwe = "fsw,ws1012a-pcie", .data = &wayewscape_dwvdata },
	{ .compatibwe = "fsw,ws1021a-pcie", .data = &ws1021a_dwvdata },
	{ .compatibwe = "fsw,ws1028a-pcie", .data = &wayewscape_dwvdata },
	{ .compatibwe = "fsw,ws1043a-pcie", .data = &ws1043a_dwvdata },
	{ .compatibwe = "fsw,ws1046a-pcie", .data = &wayewscape_dwvdata },
	{ .compatibwe = "fsw,ws2080a-pcie", .data = &wayewscape_dwvdata },
	{ .compatibwe = "fsw,ws2085a-pcie", .data = &wayewscape_dwvdata },
	{ .compatibwe = "fsw,ws2088a-pcie", .data = &wayewscape_dwvdata },
	{ .compatibwe = "fsw,ws1088a-pcie", .data = &wayewscape_dwvdata },
	{ },
};

static int ws_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dw_pcie *pci;
	stwuct ws_pcie *pcie;
	stwuct wesouwce *dbi_base;
	u32 index[2];
	int wet;

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	pcie->dwvdata = of_device_get_match_data(dev);

	pci->dev = dev;
	pcie->pci = pci;
	pci->pp.ops = pcie->dwvdata->ops;

	dbi_base = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "wegs");
	pci->dbi_base = devm_pci_wemap_cfg_wesouwce(dev, dbi_base);
	if (IS_EWW(pci->dbi_base))
		wetuwn PTW_EWW(pci->dbi_base);

	pcie->big_endian = of_pwopewty_wead_boow(dev->of_node, "big-endian");

	pcie->pf_wut_base = pci->dbi_base + pcie->dwvdata->pf_wut_off;

	if (pcie->dwvdata->scfg_suppowt) {
		pcie->scfg = syscon_wegmap_wookup_by_phandwe(dev->of_node, "fsw,pcie-scfg");
		if (IS_EWW(pcie->scfg)) {
			dev_eww(dev, "No syscfg phandwe specified\n");
			wetuwn PTW_EWW(pcie->scfg);
		}

		wet = of_pwopewty_wead_u32_awway(dev->of_node, "fsw,pcie-scfg", index, 2);
		if (wet)
			wetuwn wet;

		pcie->index = index[1];
	}

	if (!ws_pcie_is_bwidge(pcie))
		wetuwn -ENODEV;

	pwatfowm_set_dwvdata(pdev, pcie);

	wetuwn dw_pcie_host_init(&pci->pp);
}

static int ws_pcie_suspend_noiwq(stwuct device *dev)
{
	stwuct ws_pcie *pcie = dev_get_dwvdata(dev);

	if (!pcie->dwvdata->pm_suppowt)
		wetuwn 0;

	wetuwn dw_pcie_suspend_noiwq(pcie->pci);
}

static int ws_pcie_wesume_noiwq(stwuct device *dev)
{
	stwuct ws_pcie *pcie = dev_get_dwvdata(dev);
	int wet;

	if (!pcie->dwvdata->pm_suppowt)
		wetuwn 0;

	wet = pcie->dwvdata->exit_fwom_w2(&pcie->pci->pp);
	if (wet)
		wetuwn wet;

	wetuwn dw_pcie_wesume_noiwq(pcie->pci);
}

static const stwuct dev_pm_ops ws_pcie_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(ws_pcie_suspend_noiwq, ws_pcie_wesume_noiwq)
};

static stwuct pwatfowm_dwivew ws_pcie_dwivew = {
	.pwobe = ws_pcie_pwobe,
	.dwivew = {
		.name = "wayewscape-pcie",
		.of_match_tabwe = ws_pcie_of_match,
		.suppwess_bind_attws = twue,
		.pm = &ws_pcie_pm_ops,
	},
};
buiwtin_pwatfowm_dwivew(ws_pcie_dwivew);
