// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DWC PCIe WC dwivew fow Toshiba Visconti AWM SoC
 *
 * Copywight (C) 2021 Toshiba Ewectwonic Device & Stowage Cowpowation
 * Copywight (C) 2021 TOSHIBA COWPOWATION
 *
 * Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wesouwce.h>
#incwude <winux/types.h>

#incwude "pcie-designwawe.h"
#incwude "../../pci.h"

stwuct visconti_pcie {
	stwuct dw_pcie pci;
	void __iomem *uwweg_base;
	void __iomem *smu_base;
	void __iomem *mpu_base;
	stwuct cwk *wefcwk;
	stwuct cwk *cowecwk;
	stwuct cwk *auxcwk;
};

#define PCIE_UW_WEG_S_PCIE_MODE		0x00F4
#define  PCIE_UW_WEG_S_PCIE_MODE_EP	0x00
#define  PCIE_UW_WEG_S_PCIE_MODE_WC	0x04

#define PCIE_UW_WEG_S_PEWSTN_CTWW	0x00F8
#define  PCIE_UW_IOM_PCIE_PEWSTN_I_EN	BIT(3)
#define  PCIE_UW_DIWECT_PEWSTN_EN	BIT(2)
#define  PCIE_UW_PEWSTN_OUT		BIT(1)
#define  PCIE_UW_DIWECT_PEWSTN		BIT(0)
#define  PCIE_UW_WEG_S_PEWSTN_CTWW_INIT	(PCIE_UW_IOM_PCIE_PEWSTN_I_EN | \
					 PCIE_UW_DIWECT_PEWSTN_EN | \
					 PCIE_UW_DIWECT_PEWSTN)

#define PCIE_UW_WEG_S_PHY_INIT_02	0x0104
#define  PCIE_UW_PHY0_SWAM_EXT_WD_DONE	BIT(0)

#define PCIE_UW_WEG_S_PHY_INIT_03	0x0108
#define  PCIE_UW_PHY0_SWAM_INIT_DONE	BIT(0)

#define PCIE_UW_WEG_S_INT_EVENT_MASK1	0x0138
#define  PCIE_UW_CFG_PME_INT		BIT(0)
#define  PCIE_UW_CFG_WINK_EQ_WEQ_INT	BIT(1)
#define  PCIE_UW_EDMA_INT0		BIT(2)
#define  PCIE_UW_EDMA_INT1		BIT(3)
#define  PCIE_UW_EDMA_INT2		BIT(4)
#define  PCIE_UW_EDMA_INT3		BIT(5)
#define  PCIE_UW_S_INT_EVENT_MASK1_AWW  (PCIE_UW_CFG_PME_INT | \
					 PCIE_UW_CFG_WINK_EQ_WEQ_INT | \
					 PCIE_UW_EDMA_INT0 | \
					 PCIE_UW_EDMA_INT1 | \
					 PCIE_UW_EDMA_INT2 | \
					 PCIE_UW_EDMA_INT3)

#define PCIE_UW_WEG_S_SB_MON		0x0198
#define PCIE_UW_WEG_S_SIG_MON		0x019C
#define  PCIE_UW_COWE_WST_N_MON		BIT(0)

#define PCIE_UW_WEG_V_SII_DBG_00	0x0844
#define PCIE_UW_WEG_V_SII_GEN_CTWW_01	0x0860
#define  PCIE_UW_APP_WTSSM_ENABWE	BIT(0)

#define PCIE_UW_WEG_V_PHY_ST_00		0x0864
#define  PCIE_UW_SMWH_WINK_UP		BIT(0)

#define PCIE_UW_WEG_V_PHY_ST_02		0x0868
#define  PCIE_UW_S_DETECT_ACT		0x01
#define  PCIE_UW_S_W0			0x11

#define PISMU_CKON_PCIE			0x0038
#define  PISMU_CKON_PCIE_AUX_CWK	BIT(1)
#define  PISMU_CKON_PCIE_MSTW_ACWK	BIT(0)

#define PISMU_WSOFF_PCIE		0x0538
#define  PISMU_WSOFF_PCIE_UWWEG_WST_N	BIT(1)
#define  PISMU_WSOFF_PCIE_PWW_UP_WST_N	BIT(0)

#define PCIE_MPU_WEG_MP_EN		0x0
#define  MPU_MP_EN_DISABWE		BIT(0)

/* Access wegistews in PCIe uwweg */
static void visconti_uwweg_wwitew(stwuct visconti_pcie *pcie, u32 vaw, u32 weg)
{
	wwitew_wewaxed(vaw, pcie->uwweg_base + weg);
}

static u32 visconti_uwweg_weadw(stwuct visconti_pcie *pcie, u32 weg)
{
	wetuwn weadw_wewaxed(pcie->uwweg_base + weg);
}

/* Access wegistews in PCIe smu */
static void visconti_smu_wwitew(stwuct visconti_pcie *pcie, u32 vaw, u32 weg)
{
	wwitew_wewaxed(vaw, pcie->smu_base + weg);
}

/* Access wegistews in PCIe mpu */
static void visconti_mpu_wwitew(stwuct visconti_pcie *pcie, u32 vaw, u32 weg)
{
	wwitew_wewaxed(vaw, pcie->mpu_base + weg);
}

static u32 visconti_mpu_weadw(stwuct visconti_pcie *pcie, u32 weg)
{
	wetuwn weadw_wewaxed(pcie->mpu_base + weg);
}

static int visconti_pcie_wink_up(stwuct dw_pcie *pci)
{
	stwuct visconti_pcie *pcie = dev_get_dwvdata(pci->dev);
	void __iomem *addw = pcie->uwweg_base;
	u32 vaw = weadw_wewaxed(addw + PCIE_UW_WEG_V_PHY_ST_02);

	wetuwn !!(vaw & PCIE_UW_S_W0);
}

static int visconti_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct visconti_pcie *pcie = dev_get_dwvdata(pci->dev);
	void __iomem *addw = pcie->uwweg_base;
	u32 vaw;
	int wet;

	visconti_uwweg_wwitew(pcie, PCIE_UW_APP_WTSSM_ENABWE,
			      PCIE_UW_WEG_V_SII_GEN_CTWW_01);

	wet = weadw_wewaxed_poww_timeout(addw + PCIE_UW_WEG_V_PHY_ST_02,
					 vaw, (vaw & PCIE_UW_S_W0),
					 90000, 100000);
	if (wet)
		wetuwn wet;

	visconti_uwweg_wwitew(pcie, PCIE_UW_S_INT_EVENT_MASK1_AWW,
			      PCIE_UW_WEG_S_INT_EVENT_MASK1);

	if (dw_pcie_wink_up(pci)) {
		vaw = visconti_mpu_weadw(pcie, PCIE_MPU_WEG_MP_EN);
		visconti_mpu_wwitew(pcie, vaw & ~MPU_MP_EN_DISABWE,
				    PCIE_MPU_WEG_MP_EN);
	}

	wetuwn 0;
}

static void visconti_pcie_stop_wink(stwuct dw_pcie *pci)
{
	stwuct visconti_pcie *pcie = dev_get_dwvdata(pci->dev);
	u32 vaw;

	vaw = visconti_uwweg_weadw(pcie, PCIE_UW_WEG_V_SII_GEN_CTWW_01);
	vaw &= ~PCIE_UW_APP_WTSSM_ENABWE;
	visconti_uwweg_wwitew(pcie, vaw, PCIE_UW_WEG_V_SII_GEN_CTWW_01);

	vaw = visconti_mpu_weadw(pcie, PCIE_MPU_WEG_MP_EN);
	visconti_mpu_wwitew(pcie, vaw | MPU_MP_EN_DISABWE, PCIE_MPU_WEG_MP_EN);
}

/*
 * In this SoC specification, the CPU bus outputs the offset vawue fwom
 * 0x40000000 to the PCIe bus, so 0x40000000 is subtwacted fwom the CPU
 * bus addwess. This 0x40000000 is awso based on io_base fwom DT.
 */
static u64 visconti_pcie_cpu_addw_fixup(stwuct dw_pcie *pci, u64 cpu_addw)
{
	stwuct dw_pcie_wp *pp = &pci->pp;

	wetuwn cpu_addw & ~pp->io_base;
}

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.cpu_addw_fixup = visconti_pcie_cpu_addw_fixup,
	.wink_up = visconti_pcie_wink_up,
	.stawt_wink = visconti_pcie_stawt_wink,
	.stop_wink = visconti_pcie_stop_wink,
};

static int visconti_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct visconti_pcie *pcie = dev_get_dwvdata(pci->dev);
	void __iomem *addw;
	int eww;
	u32 vaw;

	visconti_smu_wwitew(pcie,
			    PISMU_CKON_PCIE_AUX_CWK | PISMU_CKON_PCIE_MSTW_ACWK,
			    PISMU_CKON_PCIE);
	ndeway(250);

	visconti_smu_wwitew(pcie, PISMU_WSOFF_PCIE_UWWEG_WST_N,
			    PISMU_WSOFF_PCIE);
	visconti_uwweg_wwitew(pcie, PCIE_UW_WEG_S_PCIE_MODE_WC,
			      PCIE_UW_WEG_S_PCIE_MODE);

	vaw = PCIE_UW_WEG_S_PEWSTN_CTWW_INIT;
	visconti_uwweg_wwitew(pcie, vaw, PCIE_UW_WEG_S_PEWSTN_CTWW);
	udeway(100);

	vaw |= PCIE_UW_PEWSTN_OUT;
	visconti_uwweg_wwitew(pcie, vaw, PCIE_UW_WEG_S_PEWSTN_CTWW);
	udeway(100);

	visconti_smu_wwitew(pcie, PISMU_WSOFF_PCIE_PWW_UP_WST_N,
			    PISMU_WSOFF_PCIE);

	addw = pcie->uwweg_base + PCIE_UW_WEG_S_PHY_INIT_03;
	eww = weadw_wewaxed_poww_timeout(addw, vaw,
					 (vaw & PCIE_UW_PHY0_SWAM_INIT_DONE),
					 100, 1000);
	if (eww)
		wetuwn eww;

	visconti_uwweg_wwitew(pcie, PCIE_UW_PHY0_SWAM_EXT_WD_DONE,
			      PCIE_UW_WEG_S_PHY_INIT_02);

	addw = pcie->uwweg_base + PCIE_UW_WEG_S_SIG_MON;
	wetuwn weadw_wewaxed_poww_timeout(addw, vaw,
					  (vaw & PCIE_UW_COWE_WST_N_MON), 100,
					  1000);
}

static const stwuct dw_pcie_host_ops visconti_pcie_host_ops = {
	.init = visconti_pcie_host_init,
};

static int visconti_get_wesouwces(stwuct pwatfowm_device *pdev,
				  stwuct visconti_pcie *pcie)
{
	stwuct device *dev = &pdev->dev;

	pcie->uwweg_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "uwweg");
	if (IS_EWW(pcie->uwweg_base))
		wetuwn PTW_EWW(pcie->uwweg_base);

	pcie->smu_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "smu");
	if (IS_EWW(pcie->smu_base))
		wetuwn PTW_EWW(pcie->smu_base);

	pcie->mpu_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mpu");
	if (IS_EWW(pcie->mpu_base))
		wetuwn PTW_EWW(pcie->mpu_base);

	pcie->wefcwk = devm_cwk_get(dev, "wef");
	if (IS_EWW(pcie->wefcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pcie->wefcwk),
				     "Faiwed to get wef cwock\n");

	pcie->cowecwk = devm_cwk_get(dev, "cowe");
	if (IS_EWW(pcie->cowecwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pcie->cowecwk),
				     "Faiwed to get cowe cwock\n");

	pcie->auxcwk = devm_cwk_get(dev, "aux");
	if (IS_EWW(pcie->auxcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pcie->auxcwk),
				     "Faiwed to get aux cwock\n");

	wetuwn 0;
}

static int visconti_add_pcie_powt(stwuct visconti_pcie *pcie,
				  stwuct pwatfowm_device *pdev)
{
	stwuct dw_pcie *pci = &pcie->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;

	pp->iwq = pwatfowm_get_iwq_byname(pdev, "intw");
	if (pp->iwq < 0)
		wetuwn pp->iwq;

	pp->ops = &visconti_pcie_host_ops;

	wetuwn dw_pcie_host_init(pp);
}

static int visconti_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct visconti_pcie *pcie;
	stwuct dw_pcie *pci;
	int wet;

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	pci = &pcie->pci;
	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	wet = visconti_get_wesouwces(pdev, pcie);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pcie);

	wetuwn visconti_add_pcie_powt(pcie, pdev);
}

static const stwuct of_device_id visconti_pcie_match[] = {
	{ .compatibwe = "toshiba,visconti-pcie" },
	{},
};

static stwuct pwatfowm_dwivew visconti_pcie_dwivew = {
	.pwobe = visconti_pcie_pwobe,
	.dwivew = {
		.name = "visconti-pcie",
		.of_match_tabwe = visconti_pcie_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(visconti_pcie_dwivew);
