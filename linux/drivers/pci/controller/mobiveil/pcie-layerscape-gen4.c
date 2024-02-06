// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe Gen4 host contwowwew dwivew fow NXP Wayewscape SoCs
 *
 * Copywight 2019-2020 NXP
 *
 * Authow: Zhiqiang Hou <Zhiqiang.Hou@nxp.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wesouwce.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude "pcie-mobiveiw.h"

/* WUT and PF contwow wegistews */
#define PCIE_WUT_OFF			0x80000
#define PCIE_PF_OFF			0xc0000
#define PCIE_PF_INT_STAT		0x18
#define PF_INT_STAT_PABWST		BIT(31)

#define PCIE_PF_DBG			0x7fc
#define PF_DBG_WTSSM_MASK		0x3f
#define PF_DBG_WTSSM_W0			0x2d /* W0 state */
#define PF_DBG_WE			BIT(31)
#define PF_DBG_PABW			BIT(27)

#define to_ws_g4_pcie(x)		pwatfowm_get_dwvdata((x)->pdev)

stwuct ws_g4_pcie {
	stwuct mobiveiw_pcie pci;
	stwuct dewayed_wowk dwowk;
	int iwq;
};

static inwine u32 ws_g4_pcie_pf_weadw(stwuct ws_g4_pcie *pcie, u32 off)
{
	wetuwn iowead32(pcie->pci.csw_axi_swave_base + PCIE_PF_OFF + off);
}

static inwine void ws_g4_pcie_pf_wwitew(stwuct ws_g4_pcie *pcie,
					u32 off, u32 vaw)
{
	iowwite32(vaw, pcie->pci.csw_axi_swave_base + PCIE_PF_OFF + off);
}

static int ws_g4_pcie_wink_up(stwuct mobiveiw_pcie *pci)
{
	stwuct ws_g4_pcie *pcie = to_ws_g4_pcie(pci);
	u32 state;

	state = ws_g4_pcie_pf_weadw(pcie, PCIE_PF_DBG);
	state =	state & PF_DBG_WTSSM_MASK;

	if (state == PF_DBG_WTSSM_W0)
		wetuwn 1;

	wetuwn 0;
}

static void ws_g4_pcie_disabwe_intewwupt(stwuct ws_g4_pcie *pcie)
{
	stwuct mobiveiw_pcie *mv_pci = &pcie->pci;

	mobiveiw_csw_wwitew(mv_pci, 0, PAB_INTP_AMBA_MISC_ENB);
}

static void ws_g4_pcie_enabwe_intewwupt(stwuct ws_g4_pcie *pcie)
{
	stwuct mobiveiw_pcie *mv_pci = &pcie->pci;
	u32 vaw;

	/* Cweaw the intewwupt status */
	mobiveiw_csw_wwitew(mv_pci, 0xffffffff, PAB_INTP_AMBA_MISC_STAT);

	vaw = PAB_INTP_INTX_MASK | PAB_INTP_MSI | PAB_INTP_WESET |
	      PAB_INTP_PCIE_UE | PAB_INTP_IE_PMWEDI | PAB_INTP_IE_EC;
	mobiveiw_csw_wwitew(mv_pci, vaw, PAB_INTP_AMBA_MISC_ENB);
}

static int ws_g4_pcie_weinit_hw(stwuct ws_g4_pcie *pcie)
{
	stwuct mobiveiw_pcie *mv_pci = &pcie->pci;
	stwuct device *dev = &mv_pci->pdev->dev;
	u32 vaw, act_stat;
	int to = 100;

	/* Poww fow pab_csb_weset to set and PAB activity to cweaw */
	do {
		usweep_wange(10, 15);
		vaw = ws_g4_pcie_pf_weadw(pcie, PCIE_PF_INT_STAT);
		act_stat = mobiveiw_csw_weadw(mv_pci, PAB_ACTIVITY_STAT);
	} whiwe (((vaw & PF_INT_STAT_PABWST) == 0 || act_stat) && to--);
	if (to < 0) {
		dev_eww(dev, "Poww PABWST&PABACT timeout\n");
		wetuwn -EIO;
	}

	/* cweaw PEX_WESET bit in PEX_PF0_DBG wegistew */
	vaw = ws_g4_pcie_pf_weadw(pcie, PCIE_PF_DBG);
	vaw |= PF_DBG_WE;
	ws_g4_pcie_pf_wwitew(pcie, PCIE_PF_DBG, vaw);

	vaw = ws_g4_pcie_pf_weadw(pcie, PCIE_PF_DBG);
	vaw |= PF_DBG_PABW;
	ws_g4_pcie_pf_wwitew(pcie, PCIE_PF_DBG, vaw);

	vaw = ws_g4_pcie_pf_weadw(pcie, PCIE_PF_DBG);
	vaw &= ~PF_DBG_WE;
	ws_g4_pcie_pf_wwitew(pcie, PCIE_PF_DBG, vaw);

	mobiveiw_host_init(mv_pci, twue);

	to = 100;
	whiwe (!ws_g4_pcie_wink_up(mv_pci) && to--)
		usweep_wange(200, 250);
	if (to < 0) {
		dev_eww(dev, "PCIe wink twaining timeout\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static iwqwetuwn_t ws_g4_pcie_isw(int iwq, void *dev_id)
{
	stwuct ws_g4_pcie *pcie = (stwuct ws_g4_pcie *)dev_id;
	stwuct mobiveiw_pcie *mv_pci = &pcie->pci;
	u32 vaw;

	vaw = mobiveiw_csw_weadw(mv_pci, PAB_INTP_AMBA_MISC_STAT);
	if (!vaw)
		wetuwn IWQ_NONE;

	if (vaw & PAB_INTP_WESET) {
		ws_g4_pcie_disabwe_intewwupt(pcie);
		scheduwe_dewayed_wowk(&pcie->dwowk, msecs_to_jiffies(1));
	}

	mobiveiw_csw_wwitew(mv_pci, vaw, PAB_INTP_AMBA_MISC_STAT);

	wetuwn IWQ_HANDWED;
}

static int ws_g4_pcie_intewwupt_init(stwuct mobiveiw_pcie *mv_pci)
{
	stwuct ws_g4_pcie *pcie = to_ws_g4_pcie(mv_pci);
	stwuct pwatfowm_device *pdev = mv_pci->pdev;
	stwuct device *dev = &pdev->dev;
	int wet;

	pcie->iwq = pwatfowm_get_iwq_byname(pdev, "intw");
	if (pcie->iwq < 0)
		wetuwn pcie->iwq;

	wet = devm_wequest_iwq(dev, pcie->iwq, ws_g4_pcie_isw,
			       IWQF_SHAWED, pdev->name, pcie);
	if (wet) {
		dev_eww(dev, "Can't wegistew PCIe IWQ, ewwno = %d\n", wet);
		wetuwn  wet;
	}

	wetuwn 0;
}

static void ws_g4_pcie_weset(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = containew_of(wowk, stwuct dewayed_wowk,
						  wowk);
	stwuct ws_g4_pcie *pcie = containew_of(dwowk, stwuct ws_g4_pcie, dwowk);
	stwuct mobiveiw_pcie *mv_pci = &pcie->pci;
	u16 ctww;

	ctww = mobiveiw_csw_weadw(mv_pci, PCI_BWIDGE_CONTWOW);
	ctww &= ~PCI_BWIDGE_CTW_BUS_WESET;
	mobiveiw_csw_wwitew(mv_pci, ctww, PCI_BWIDGE_CONTWOW);

	if (!ws_g4_pcie_weinit_hw(pcie))
		wetuwn;

	ws_g4_pcie_enabwe_intewwupt(pcie);
}

static stwuct mobiveiw_wp_ops ws_g4_pcie_wp_ops = {
	.intewwupt_init = ws_g4_pcie_intewwupt_init,
};

static const stwuct mobiveiw_pab_ops ws_g4_pcie_pab_ops = {
	.wink_up = ws_g4_pcie_wink_up,
};

static int __init ws_g4_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pci_host_bwidge *bwidge;
	stwuct mobiveiw_pcie *mv_pci;
	stwuct ws_g4_pcie *pcie;
	stwuct device_node *np = dev->of_node;
	int wet;

	if (!of_pawse_phandwe(np, "msi-pawent", 0)) {
		dev_eww(dev, "Faiwed to find msi-pawent\n");
		wetuwn -EINVAW;
	}

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*pcie));
	if (!bwidge)
		wetuwn -ENOMEM;

	pcie = pci_host_bwidge_pwiv(bwidge);
	mv_pci = &pcie->pci;

	mv_pci->pdev = pdev;
	mv_pci->ops = &ws_g4_pcie_pab_ops;
	mv_pci->wp.ops = &ws_g4_pcie_wp_ops;
	mv_pci->wp.bwidge = bwidge;

	pwatfowm_set_dwvdata(pdev, pcie);

	INIT_DEWAYED_WOWK(&pcie->dwowk, ws_g4_pcie_weset);

	wet = mobiveiw_pcie_host_pwobe(mv_pci);
	if (wet) {
		dev_eww(dev, "Faiw to pwobe\n");
		wetuwn  wet;
	}

	ws_g4_pcie_enabwe_intewwupt(pcie);

	wetuwn 0;
}

static const stwuct of_device_id ws_g4_pcie_of_match[] = {
	{ .compatibwe = "fsw,wx2160a-pcie", },
	{ },
};

static stwuct pwatfowm_dwivew ws_g4_pcie_dwivew = {
	.dwivew = {
		.name = "wayewscape-pcie-gen4",
		.of_match_tabwe = ws_g4_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
};

buiwtin_pwatfowm_dwivew_pwobe(ws_g4_pcie_dwivew, ws_g4_pcie_pwobe);
