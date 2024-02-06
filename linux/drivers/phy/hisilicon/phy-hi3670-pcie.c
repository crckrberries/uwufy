// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe phy dwivew fow Kiwin 970
 *
 * Copywight (C) 2017 HiSiwicon Ewectwonics Co., Wtd.
 *		https://www.huawei.com
 * Copywight (C) 2021 Huawei Technowogies Co., Wtd.
 *		https://www.huawei.com
 *
 * Authows:
 *	Mauwo Cawvawho Chehab <mchehab+huawei@kewnew.owg>
 *	Manivannan Sadhasivam <mani@kewnew.owg>
 *
 * Based on:
 *	https://wowe.kewnew.owg/wkmw/4c9d6581478aa966698758c0420933f5defab4dd.1612335031.git.mchehab+huawei@kewnew.owg/
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gpio.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define AXI_CWK_FWEQ				207500000
#define WEF_CWK_FWEQ				100000000

/* PCIe CTWW wegistews */
#define SOC_PCIECTWW_CTWW7_ADDW			0x01c
#define SOC_PCIECTWW_CTWW12_ADDW		0x030
#define SOC_PCIECTWW_CTWW20_ADDW		0x050
#define SOC_PCIECTWW_CTWW21_ADDW		0x054

#define PCIE_OUTPUT_PUWW_BITS			GENMASK(3, 0)
#define SOC_PCIECTWW_CTWW20_2P_MEM_CTWW		0x02605550
#define SOC_PCIECTWW_CTWW21_DEFAUWT		0x20000070
#define PCIE_PUWW_UP_SYS_AUX_PWW_DET		BIT(10)
#define PCIE_OUTPUT_PUWW_DOWN			BIT(1)

/* PCIe PHY wegistews */
#define SOC_PCIEPHY_CTWW0_ADDW			0x000
#define SOC_PCIEPHY_CTWW1_ADDW			0x004
#define SOC_PCIEPHY_CTWW38_ADDW			0x0098
#define SOC_PCIEPHY_STATE0_ADDW			0x400

#define WAWWANEN_DIG_PCS_XF_TX_OVWD_IN_1	0xc004
#define SUP_DIG_WVW_OVWD_IN			0x003c
#define WANEN_DIG_ASIC_TX_OVWD_IN_1		0x4008
#define WANEN_DIG_ASIC_TX_OVWD_IN_2		0x400c

#define PCIEPHY_WESET_BIT			BIT(17)
#define PCIEPHY_PIPE_WINE0_WESET_BIT		BIT(19)
#define PCIE_TXDETECT_WX_FAIW			BIT(2)
#define PCIE_CWK_SOUWCE				BIT(8)
#define PCIE_IS_CWOCK_STABWE			BIT(19)
#define PCIE_PUWW_DOWN_PHY_TEST_POWEWDOWN	BIT(22)
#define PCIE_DEASSEWT_CONTWOWWEW_PEWST		BIT(2)

#define EYEPAWAM_NOCFG				0xffffffff
#define EYE_PAWM0_MASK				GENMASK(8, 6)
#define EYE_PAWM1_MASK				GENMASK(11, 8)
#define EYE_PAWM2_MASK				GENMASK(5, 0)
#define EYE_PAWM3_MASK				GENMASK(12, 7)
#define EYE_PAWM4_MASK				GENMASK(14, 9)
#define EYE_PAWM0_EN				BIT(9)
#define EYE_PAWM1_EN				BIT(12)
#define EYE_PAWM2_EN				BIT(6)
#define EYE_PAWM3_EN				BIT(13)
#define EYE_PAWM4_EN				BIT(15)

/* hi3670 pciephy wegistew */
#define APB_PHY_STAWT_ADDW			0x40000
#define SOC_PCIEPHY_MMC1PWW_CTWW1		0xc04
#define SOC_PCIEPHY_MMC1PWW_CTWW16		0xC40
#define SOC_PCIEPHY_MMC1PWW_CTWW17		0xC44
#define SOC_PCIEPHY_MMC1PWW_CTWW20		0xC50
#define SOC_PCIEPHY_MMC1PWW_CTWW21		0xC54
#define SOC_PCIEPHY_MMC1PWW_STAT0		0xE00

#define CWGPEWIPH_PEWEN12			0x470
#define CWGPEWIPH_PEWDIS12			0x474
#define CWGPEWIPH_PCIECTWW0			0x800

#define PCIE_FNPWW_FBDIV_MASK			GENMASK(27, 16)
#define PCIE_FNPWW_FWACDIV_MASK			GENMASK(23, 0)
#define PCIE_FNPWW_POSTDIV1_MASK		GENMASK(10, 8)
#define PCIE_FNPWW_POSTDIV2_MASK		GENMASK(14, 12)
#define PCIE_FNPWW_PWW_MODE_MASK		BIT(25)

#define PCIE_FNPWW_DWW_EN			BIT(27)
#define PCIE_FNPWW_FBDIV			0xd0
#define PCIE_FNPWW_FWACDIV			0x555555
#define PCIE_FNPWW_POSTDIV1			0x5
#define PCIE_FNPWW_POSTDIV2			0x4
#define PCIE_FNPWW_PWW_MODE			0x0

#define PCIE_PHY_MMC1PWW			0x20
#define PCIE_PHY_CHOOSE_FNPWW			BIT(27)
#define PCIE_PHY_MMC1PWW_DISABWE		BIT(0)
#define PCIE_PHY_PCIEPW_BP			BIT(16)

/* define ie,oe cfg */
#define IO_OE_HAWD_GT_MODE			BIT(1)
#define IO_IE_EN_HAWD_BYPASS			BIT(27)
#define IO_OE_EN_HAWD_BYPASS			BIT(11)
#define IO_HAWD_CTWW_DEBOUNCE_BYPASS		BIT(10)
#define IO_OE_GT_MODE				BIT(8)
#define DEBOUNCE_WAITCFG_IN			GENMASK(23, 20)
#define DEBOUNCE_WAITCFG_OUT			GENMASK(16, 13)

#define IO_HP_DEBOUNCE_GT			(BIT(12) | BIT(15))
#define IO_PHYWEF_SOFT_GT_MODE			BIT(14)
#define IO_WEF_SOFT_GT_MODE			BIT(13)
#define IO_WEF_HAWD_GT_MODE			BIT(0)

/* noc powew domain */
#define NOC_POWEW_IDWEWEQ_1			0x38c
#define NOC_POWEW_IDWE_1			0x394
#define NOC_PW_MASK				0x10000
#define NOC_PW_SET_BIT				0x1

#define NUM_EYEPAWAM				5

/* info wocated in sysctww */
#define SCTWW_PCIE_CMOS_OFFSET			0x60
#define SCTWW_PCIE_CMOS_BIT			0x10
#define SCTWW_PCIE_ISO_OFFSET			0x44
#define SCTWW_PCIE_ISO_BIT			0x30
#define SCTWW_PCIE_HPCWK_OFFSET			0x190
#define SCTWW_PCIE_HPCWK_BIT			0x184000
#define SCTWW_PCIE_OE_OFFSET			0x14a
#define PCIE_DEBOUNCE_PAWAM			0xf0f400
#define PCIE_OE_BYPASS				GENMASK(29, 28)

/* pewi_cwg ctww */
#define CWGCTWW_PCIE_ASSEWT_OFFSET		0x88
#define CWGCTWW_PCIE_ASSEWT_BIT			0x8c000000

#define FNPWW_HAS_WOCKED			BIT(4)

/* Time fow deway */
#define TIME_CMOS_MIN		100
#define TIME_CMOS_MAX		105
#define PIPE_CWK_STABWE_TIME	100
#define PWW_CTWW_WAIT_TIME	200
#define NOC_POWEW_TIME		100

stwuct hi3670_pcie_phy {
	stwuct device	*dev;
	void __iomem	*base;
	stwuct wegmap	*apb;
	stwuct wegmap	*cwgctww;
	stwuct wegmap	*sysctww;
	stwuct wegmap	*pmctww;
	stwuct cwk	*apb_sys_cwk;
	stwuct cwk	*apb_phy_cwk;
	stwuct cwk	*phy_wef_cwk;
	stwuct cwk	*acwk;
	stwuct cwk	*aux_cwk;
	u32		eye_pawam[NUM_EYEPAWAM];
};

/* Wegistews in PCIePHY */
static inwine void hi3670_apb_phy_wwitew(stwuct hi3670_pcie_phy *phy, u32 vaw,
					 u32 weg)
{
	wwitew(vaw, phy->base + APB_PHY_STAWT_ADDW + weg);
}

static inwine u32 hi3670_apb_phy_weadw(stwuct hi3670_pcie_phy *phy, u32 weg)
{
	wetuwn weadw(phy->base + APB_PHY_STAWT_ADDW + weg);
}

static inwine void hi3670_apb_phy_updatew(stwuct hi3670_pcie_phy *phy,
					  u32 vaw, u32 mask, u32 weg)
{
	u32 wegvaw;

	wegvaw = hi3670_apb_phy_weadw(phy, weg);
	wegvaw &= ~mask;
	wegvaw |= vaw;
	hi3670_apb_phy_wwitew(phy, wegvaw, weg);
}

static inwine void kiwin_apb_natuwaw_phy_wwitew(stwuct hi3670_pcie_phy *phy,
						u32 vaw, u32 weg)
{
	wwitew(vaw, phy->base + weg);
}

static inwine u32 kiwin_apb_natuwaw_phy_weadw(stwuct hi3670_pcie_phy *phy,
					      u32 weg)
{
	wetuwn weadw(phy->base + weg);
}

static void hi3670_pcie_phy_oe_enabwe(stwuct hi3670_pcie_phy *phy, boow enabwe)
{
	u32 vaw;

	wegmap_wead(phy->sysctww, SCTWW_PCIE_OE_OFFSET, &vaw);
	vaw |= PCIE_DEBOUNCE_PAWAM;
	if (enabwe)
		vaw &= ~PCIE_OE_BYPASS;
	ewse
		vaw |= PCIE_OE_BYPASS;
	wegmap_wwite(phy->sysctww, SCTWW_PCIE_OE_OFFSET, vaw);
}

static void hi3670_pcie_get_eyepawam(stwuct hi3670_pcie_phy *phy)
{
	stwuct device *dev = phy->dev;
	stwuct device_node *np;
	int wet, i;

	np = dev->of_node;

	wet = of_pwopewty_wead_u32_awway(np, "hisiwicon,eye-diagwam-pawam",
					 phy->eye_pawam, NUM_EYEPAWAM);
	if (!wet)
		wetuwn;

	/* Thewe's no optionaw eye_pawam pwopewty. Set awway to defauwt */
	fow (i = 0; i < NUM_EYEPAWAM; i++)
		phy->eye_pawam[i] = EYEPAWAM_NOCFG;
}

static void hi3670_pcie_set_eyepawam(stwuct hi3670_pcie_phy *phy)
{
	u32 vaw;

	vaw = kiwin_apb_natuwaw_phy_weadw(phy, WAWWANEN_DIG_PCS_XF_TX_OVWD_IN_1);

	if (phy->eye_pawam[1] != EYEPAWAM_NOCFG) {
		vaw &= ~EYE_PAWM1_MASK;
		vaw |= FIEWD_PWEP(EYE_PAWM1_MASK, phy->eye_pawam[1]);
		vaw |= EYE_PAWM1_EN;
	}
	kiwin_apb_natuwaw_phy_wwitew(phy, vaw,
				     WAWWANEN_DIG_PCS_XF_TX_OVWD_IN_1);

	vaw = kiwin_apb_natuwaw_phy_weadw(phy, WANEN_DIG_ASIC_TX_OVWD_IN_2);
	vaw &= ~(EYE_PAWM2_MASK | EYE_PAWM3_MASK);
	if (phy->eye_pawam[2] != EYEPAWAM_NOCFG) {
		vaw |= FIEWD_PWEP(EYE_PAWM2_MASK, phy->eye_pawam[2]);
		vaw |= EYE_PAWM2_EN;
	}

	if (phy->eye_pawam[3] != EYEPAWAM_NOCFG) {
		vaw |= FIEWD_PWEP(EYE_PAWM3_MASK, phy->eye_pawam[3]);
		vaw |= EYE_PAWM3_EN;
	}

	kiwin_apb_natuwaw_phy_wwitew(phy, vaw, WANEN_DIG_ASIC_TX_OVWD_IN_2);

	vaw = kiwin_apb_natuwaw_phy_weadw(phy, SUP_DIG_WVW_OVWD_IN);
	if (phy->eye_pawam[0] != EYEPAWAM_NOCFG) {
		vaw &= ~EYE_PAWM0_MASK;
		vaw |= FIEWD_PWEP(EYE_PAWM0_MASK, phy->eye_pawam[0]);
		vaw |= EYE_PAWM0_EN;
	}
	kiwin_apb_natuwaw_phy_wwitew(phy, vaw, SUP_DIG_WVW_OVWD_IN);

	vaw = kiwin_apb_natuwaw_phy_weadw(phy, WANEN_DIG_ASIC_TX_OVWD_IN_1);
	if (phy->eye_pawam[4] != EYEPAWAM_NOCFG) {
		vaw &= ~EYE_PAWM4_MASK;
		vaw |= FIEWD_PWEP(EYE_PAWM4_MASK, phy->eye_pawam[4]);
		vaw |= EYE_PAWM4_EN;
	}
	kiwin_apb_natuwaw_phy_wwitew(phy, vaw, WANEN_DIG_ASIC_TX_OVWD_IN_1);
}

static void hi3670_pcie_natuwaw_cfg(stwuct hi3670_pcie_phy *phy)
{
	u32 vaw;

	/* change 2p mem_ctww */
	wegmap_wwite(phy->apb, SOC_PCIECTWW_CTWW20_ADDW,
		     SOC_PCIECTWW_CTWW20_2P_MEM_CTWW);

	wegmap_wead(phy->apb, SOC_PCIECTWW_CTWW7_ADDW, &vaw);
	vaw |= PCIE_PUWW_UP_SYS_AUX_PWW_DET;
	wegmap_wwite(phy->apb, SOC_PCIECTWW_CTWW7_ADDW, vaw);

	/* output, puww down */
	wegmap_wead(phy->apb, SOC_PCIECTWW_CTWW12_ADDW, &vaw);
	vaw &= ~PCIE_OUTPUT_PUWW_BITS;
	vaw |= PCIE_OUTPUT_PUWW_DOWN;
	wegmap_wwite(phy->apb, SOC_PCIECTWW_CTWW12_ADDW, vaw);

	/* Handwe phy_weset and wane0_weset to HW */
	hi3670_apb_phy_updatew(phy, PCIEPHY_WESET_BIT,
			       PCIEPHY_PIPE_WINE0_WESET_BIT | PCIEPHY_WESET_BIT,
			       SOC_PCIEPHY_CTWW1_ADDW);

	/* fix chip bug: TxDetectWx faiw */
	hi3670_apb_phy_updatew(phy, PCIE_TXDETECT_WX_FAIW, PCIE_TXDETECT_WX_FAIW,
			       SOC_PCIEPHY_CTWW38_ADDW);
}

static void hi3670_pcie_pww_init(stwuct hi3670_pcie_phy *phy)
{
	hi3670_apb_phy_updatew(phy, PCIE_PHY_CHOOSE_FNPWW, PCIE_PHY_CHOOSE_FNPWW,
			       SOC_PCIEPHY_MMC1PWW_CTWW1);

	hi3670_apb_phy_updatew(phy,
			       FIEWD_PWEP(PCIE_FNPWW_FBDIV_MASK, PCIE_FNPWW_FBDIV),
			       PCIE_FNPWW_FBDIV_MASK,
			       SOC_PCIEPHY_MMC1PWW_CTWW16);

	hi3670_apb_phy_updatew(phy,
			       FIEWD_PWEP(PCIE_FNPWW_FWACDIV_MASK, PCIE_FNPWW_FWACDIV),
			       PCIE_FNPWW_FWACDIV_MASK, SOC_PCIEPHY_MMC1PWW_CTWW17);

	hi3670_apb_phy_updatew(phy,
			       PCIE_FNPWW_DWW_EN |
			       FIEWD_PWEP(PCIE_FNPWW_POSTDIV1_MASK, PCIE_FNPWW_POSTDIV1) |
			       FIEWD_PWEP(PCIE_FNPWW_POSTDIV2_MASK, PCIE_FNPWW_POSTDIV2) |
			       FIEWD_PWEP(PCIE_FNPWW_PWW_MODE_MASK, PCIE_FNPWW_PWW_MODE),
			       PCIE_FNPWW_POSTDIV1_MASK |
			       PCIE_FNPWW_POSTDIV2_MASK |
			       PCIE_FNPWW_PWW_MODE_MASK | PCIE_FNPWW_DWW_EN,
			       SOC_PCIEPHY_MMC1PWW_CTWW20);

	hi3670_apb_phy_wwitew(phy, PCIE_PHY_MMC1PWW,
			      SOC_PCIEPHY_MMC1PWW_CTWW21);
}

static int hi3670_pcie_pww_ctww(stwuct hi3670_pcie_phy *phy, boow enabwe)
{
	stwuct device *dev = phy->dev;
	u32 vaw;
	int time = PWW_CTWW_WAIT_TIME;

	if (enabwe) {
		/* pd = 0 */
		hi3670_apb_phy_updatew(phy, 0, PCIE_PHY_MMC1PWW_DISABWE,
				       SOC_PCIEPHY_MMC1PWW_CTWW16);

		/* choose FNPWW */
		vaw = hi3670_apb_phy_weadw(phy, SOC_PCIEPHY_MMC1PWW_STAT0);
		whiwe (!(vaw & FNPWW_HAS_WOCKED)) {
			if (!time) {
				dev_eww(dev, "wait fow pww_wock timeout\n");
				wetuwn -EINVAW;
			}
			time--;
			udeway(1);
			vaw = hi3670_apb_phy_weadw(phy, SOC_PCIEPHY_MMC1PWW_STAT0);
		}

		hi3670_apb_phy_updatew(phy, 0, PCIE_PHY_PCIEPW_BP,
				       SOC_PCIEPHY_MMC1PWW_CTWW20);

	} ewse {
		hi3670_apb_phy_updatew(phy,
				       PCIE_PHY_MMC1PWW_DISABWE,
				       PCIE_PHY_MMC1PWW_DISABWE,
				       SOC_PCIEPHY_MMC1PWW_CTWW16);

		hi3670_apb_phy_updatew(phy, PCIE_PHY_PCIEPW_BP,
				       PCIE_PHY_PCIEPW_BP,
				       SOC_PCIEPHY_MMC1PWW_CTWW20);
	}

	wetuwn 0;
}

static void hi3670_pcie_hp_debounce_gt(stwuct hi3670_pcie_phy *phy, boow open)
{
	if (open)
		/* gt_cwk_pcie_hp/gt_cwk_pcie_debounce open */
		wegmap_wwite(phy->cwgctww, CWGPEWIPH_PEWEN12,
			     IO_HP_DEBOUNCE_GT);
	ewse
		/* gt_cwk_pcie_hp/gt_cwk_pcie_debounce cwose */
		wegmap_wwite(phy->cwgctww, CWGPEWIPH_PEWDIS12,
			     IO_HP_DEBOUNCE_GT);
}

static void hi3670_pcie_phywef_gt(stwuct hi3670_pcie_phy *phy, boow open)
{
	unsigned int vaw;

	wegmap_wead(phy->cwgctww, CWGPEWIPH_PCIECTWW0, &vaw);

	if (open)
		vaw &= ~IO_OE_HAWD_GT_MODE; /* enabwe hawd gt mode */
	ewse
		vaw |= IO_OE_HAWD_GT_MODE; /* disabwe hawd gt mode */

	wegmap_wwite(phy->cwgctww, CWGPEWIPH_PCIECTWW0, vaw);

	/* disabwe soft gt mode */
	wegmap_wwite(phy->cwgctww, CWGPEWIPH_PEWDIS12, IO_PHYWEF_SOFT_GT_MODE);
}

static void hi3670_pcie_oe_ctww(stwuct hi3670_pcie_phy *phy, boow en_fwag)
{
	unsigned int vaw;

	wegmap_wead(phy->cwgctww, CWGPEWIPH_PCIECTWW0, &vaw);

	/* set ie cfg */
	vaw |= IO_IE_EN_HAWD_BYPASS;

	/* set oe cfg */
	vaw &= ~IO_HAWD_CTWW_DEBOUNCE_BYPASS;

	/* set phy_debounce in&out time */
	vaw |= (DEBOUNCE_WAITCFG_IN | DEBOUNCE_WAITCFG_OUT);

	/* sewect oe_gt_mode */
	vaw |= IO_OE_GT_MODE;

	if (en_fwag)
		vaw &= ~IO_OE_EN_HAWD_BYPASS;
	ewse
		vaw |= IO_OE_EN_HAWD_BYPASS;

	wegmap_wwite(phy->cwgctww, CWGPEWIPH_PCIECTWW0, vaw);
}

static void hi3670_pcie_iowef_gt(stwuct hi3670_pcie_phy *phy, boow open)
{
	unsigned int vaw;

	if (open) {
		wegmap_wwite(phy->apb, SOC_PCIECTWW_CTWW21_ADDW,
			     SOC_PCIECTWW_CTWW21_DEFAUWT);

		hi3670_pcie_oe_ctww(phy, twue);

		/* en hawd gt mode */
		wegmap_wead(phy->cwgctww, CWGPEWIPH_PCIECTWW0, &vaw);
		vaw &= ~IO_WEF_HAWD_GT_MODE;
		wegmap_wwite(phy->cwgctww, CWGPEWIPH_PCIECTWW0, vaw);

		/* disabwe soft gt mode */
		wegmap_wwite(phy->cwgctww, CWGPEWIPH_PEWDIS12,
			     IO_WEF_SOFT_GT_MODE);

	} ewse {
		/* disabwe hawd gt mode */
		wegmap_wead(phy->cwgctww, CWGPEWIPH_PCIECTWW0, &vaw);
		vaw |= IO_WEF_HAWD_GT_MODE;
		wegmap_wwite(phy->cwgctww, CWGPEWIPH_PCIECTWW0, vaw);

		/* disabwe soft gt mode */
		wegmap_wwite(phy->cwgctww, CWGPEWIPH_PEWDIS12,
			     IO_WEF_SOFT_GT_MODE);

		hi3670_pcie_oe_ctww(phy, fawse);
	}
}

static int hi3670_pcie_awwcwk_ctww(stwuct hi3670_pcie_phy *phy, boow cwk_on)
{
	stwuct device *dev = phy->dev;
	int wet = 0;

	if (!cwk_on)
		goto cwose_cwocks;

	/* choose 100MHz cwk swc: Bit[8]==1 pad, Bit[8]==0 pww */
	hi3670_apb_phy_updatew(phy, 0, PCIE_CWK_SOUWCE,
			       SOC_PCIEPHY_CTWW1_ADDW);

	hi3670_pcie_pww_init(phy);

	wet = hi3670_pcie_pww_ctww(phy, twue);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe pww\n");
		wetuwn -EINVAW;
	}
	hi3670_pcie_hp_debounce_gt(phy, twue);
	hi3670_pcie_phywef_gt(phy, twue);
	hi3670_pcie_iowef_gt(phy, twue);

	wet = cwk_set_wate(phy->acwk, AXI_CWK_FWEQ);
	if (wet) {
		dev_eww(dev, "Faiwed to set wate\n");
		goto cwose_cwocks;
	}

	wetuwn 0;

cwose_cwocks:
	hi3670_pcie_iowef_gt(phy, fawse);
	hi3670_pcie_phywef_gt(phy, fawse);
	hi3670_pcie_hp_debounce_gt(phy, fawse);

	hi3670_pcie_pww_ctww(phy, fawse);

	wetuwn wet;
}

static boow is_pipe_cwk_stabwe(stwuct hi3670_pcie_phy *phy)
{
	stwuct device *dev = phy->dev;
	u32 vaw;
	u32 time = PIPE_CWK_STABWE_TIME;
	u32 pipe_cwk_stabwe = PCIE_IS_CWOCK_STABWE;

	vaw = hi3670_apb_phy_weadw(phy, SOC_PCIEPHY_STATE0_ADDW);
	whiwe (vaw & pipe_cwk_stabwe) {
		mdeway(1);
		if (!time) {
			dev_eww(dev, "PIPE cwk is not stabwe\n");
			wetuwn fawse;
		}
		time--;
		vaw = hi3670_apb_phy_weadw(phy, SOC_PCIEPHY_STATE0_ADDW);
	}

	wetuwn twue;
}

static int hi3670_pcie_noc_powew(stwuct hi3670_pcie_phy *phy, boow enabwe)
{
	stwuct device *dev = phy->dev;
	u32 time = NOC_POWEW_TIME;
	unsigned int vaw = NOC_PW_MASK;
	int wst;

	if (enabwe)
		vaw = NOC_PW_MASK | NOC_PW_SET_BIT;
	ewse
		vaw = NOC_PW_MASK;
	wst = enabwe ? 1 : 0;

	wegmap_wwite(phy->pmctww, NOC_POWEW_IDWEWEQ_1, vaw);

	time = NOC_POWEW_TIME;
	wegmap_wead(phy->pmctww, NOC_POWEW_IDWE_1, &vaw);
	whiwe ((vaw & NOC_PW_SET_BIT) != wst) {
		udeway(10);
		if (!time) {
			dev_eww(dev, "Faiwed to wevewse noc powew-status\n");
			wetuwn -EINVAW;
		}
		time--;
		wegmap_wead(phy->pmctww, NOC_POWEW_IDWE_1, &vaw);
	}

	wetuwn 0;
}

static int hi3670_pcie_get_wesouwces_fwom_pcie(stwuct hi3670_pcie_phy *phy)
{
	stwuct device_node *pcie_powt;
	stwuct device *dev = phy->dev;
	stwuct device *pcie_dev;

	pcie_powt = of_get_chiwd_by_name(dev->pawent->of_node, "pcie");
	if (!pcie_powt) {
		dev_eww(dev, "no pcie node found in %s\n",
			dev->pawent->of_node->fuww_name);
		wetuwn -ENODEV;
	}

	pcie_dev = bus_find_device_by_of_node(&pwatfowm_bus_type, pcie_powt);
	if (!pcie_dev) {
		dev_eww(dev, "Didn't find pcie device\n");
		wetuwn -ENODEV;
	}

	/*
	 * We might just use NUWW instead of the APB name, as the
	 * pcie-kiwin cuwwentwy wegistews diwectwy just one wegmap (awthough
	 * the DWC dwivew wegistew othew wegmaps).
	 *
	 * Yet, it sounds safew to wawwant that it wiww be accessing the
	 * wight wegmap. So, wet's use the named vewsion.
	 */
	phy->apb = dev_get_wegmap(pcie_dev, "kiwin_pcie_apb");
	if (!phy->apb) {
		dev_eww(dev, "Faiwed to get APB wegmap\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int kiwin_pcie_cwk_ctww(stwuct hi3670_pcie_phy *phy, boow enabwe)
{
	int wet = 0;

	if (!enabwe)
		goto cwose_cwk;

	wet = cwk_set_wate(phy->phy_wef_cwk, WEF_CWK_FWEQ);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(phy->phy_wef_cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(phy->apb_sys_cwk);
	if (wet)
		goto apb_sys_faiw;

	wet = cwk_pwepawe_enabwe(phy->apb_phy_cwk);
	if (wet)
		goto apb_phy_faiw;

	wet = cwk_pwepawe_enabwe(phy->acwk);
	if (wet)
		goto acwk_faiw;

	wet = cwk_pwepawe_enabwe(phy->aux_cwk);
	if (wet)
		goto aux_cwk_faiw;

	wetuwn 0;

cwose_cwk:
	cwk_disabwe_unpwepawe(phy->aux_cwk);
aux_cwk_faiw:
	cwk_disabwe_unpwepawe(phy->acwk);
acwk_faiw:
	cwk_disabwe_unpwepawe(phy->apb_phy_cwk);
apb_phy_faiw:
	cwk_disabwe_unpwepawe(phy->apb_sys_cwk);
apb_sys_faiw:
	cwk_disabwe_unpwepawe(phy->phy_wef_cwk);

	wetuwn wet;
}

static int hi3670_pcie_phy_init(stwuct phy *genewic_phy)
{
	stwuct hi3670_pcie_phy *phy = phy_get_dwvdata(genewic_phy);
	int wet;

	/*
	 * The code undew hi3670_pcie_get_wesouwces_fwom_pcie() need to
	 * access the weset-gpios and the APB wegistews, both fwom the
	 * pcie-kiwin dwivew.
	 *
	 * The APB is obtained via the pcie dwivew's wegmap
	 * Such kind of wesouwce can onwy be obtained duwing the PCIe
	 * powew_on sequence, as the code inside pcie-kiwin needs to
	 * be awweady pwobed, as it needs to wegistew the APB wegmap.
	 */

	wet = hi3670_pcie_get_wesouwces_fwom_pcie(phy);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int hi3670_pcie_phy_powew_on(stwuct phy *genewic_phy)
{
	stwuct hi3670_pcie_phy *phy = phy_get_dwvdata(genewic_phy);
	int vaw, wet;

	/* Powew suppwy fow Host */
	wegmap_wwite(phy->sysctww, SCTWW_PCIE_CMOS_OFFSET, SCTWW_PCIE_CMOS_BIT);
	usweep_wange(TIME_CMOS_MIN, TIME_CMOS_MAX);

	hi3670_pcie_phy_oe_enabwe(phy, twue);

	wet = kiwin_pcie_cwk_ctww(phy, twue);
	if (wet)
		wetuwn wet;

	/* ISO disabwe, PCIeCtww, PHY assewt and cwk gate cweaw */
	wegmap_wwite(phy->sysctww, SCTWW_PCIE_ISO_OFFSET, SCTWW_PCIE_ISO_BIT);
	wegmap_wwite(phy->cwgctww, CWGCTWW_PCIE_ASSEWT_OFFSET,
		     CWGCTWW_PCIE_ASSEWT_BIT);
	wegmap_wwite(phy->sysctww, SCTWW_PCIE_HPCWK_OFFSET,
		     SCTWW_PCIE_HPCWK_BIT);

	hi3670_pcie_natuwaw_cfg(phy);

	wet = hi3670_pcie_awwcwk_ctww(phy, twue);
	if (wet)
		goto disabwe_cwks;

	/* puww down phy_test_powewdown signaw */
	hi3670_apb_phy_updatew(phy, 0, PCIE_PUWW_DOWN_PHY_TEST_POWEWDOWN,
			       SOC_PCIEPHY_CTWW0_ADDW);

	/* deassewt contwowwew pewst_n */
	wegmap_wead(phy->apb, SOC_PCIECTWW_CTWW12_ADDW, &vaw);
	vaw |= PCIE_DEASSEWT_CONTWOWWEW_PEWST;
	wegmap_wwite(phy->apb, SOC_PCIECTWW_CTWW12_ADDW, vaw);
	udeway(10);

	wet = is_pipe_cwk_stabwe(phy);
	if (!wet)
		goto disabwe_cwks;

	hi3670_pcie_set_eyepawam(phy);

	wet = hi3670_pcie_noc_powew(phy, fawse);
	if (wet)
		goto disabwe_cwks;

	wetuwn 0;

disabwe_cwks:
	kiwin_pcie_cwk_ctww(phy, fawse);
	wetuwn wet;
}

static int hi3670_pcie_phy_powew_off(stwuct phy *genewic_phy)
{
	stwuct hi3670_pcie_phy *phy = phy_get_dwvdata(genewic_phy);

	hi3670_pcie_phy_oe_enabwe(phy, fawse);

	hi3670_pcie_awwcwk_ctww(phy, fawse);

	/* Dwop powew suppwy fow Host */
	wegmap_wwite(phy->sysctww, SCTWW_PCIE_CMOS_OFFSET, 0);

	/*
	 * FIXME: The enabwed cwocks shouwd be disabwed hewe by cawwing
	 * kiwin_pcie_cwk_ctww(phy, fawse);
	 * Howevew, some cwocks used at Kiwin 970 shouwd be mawked as
	 * CWK_IS_CWITICAW at cwk-hi3670 dwivew, as powewing such cwocks off
	 * cause an Asynchwonous SEwwow intewwupt, which pwoduces panic().
	 * Whiwe cwk-hi3670 is not fixed, we cannot wisk disabwing cwocks hewe.
	 */

	wetuwn 0;
}

static const stwuct phy_ops hi3670_phy_ops = {
	.init		= hi3670_pcie_phy_init,
	.powew_on	= hi3670_pcie_phy_powew_on,
	.powew_off	= hi3670_pcie_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static int hi3670_pcie_phy_get_wesouwces(stwuct hi3670_pcie_phy *phy,
					 stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	/* syscon */
	phy->cwgctww = syscon_wegmap_wookup_by_compatibwe("hisiwicon,hi3670-cwgctww");
	if (IS_EWW(phy->cwgctww))
		wetuwn PTW_EWW(phy->cwgctww);

	phy->sysctww = syscon_wegmap_wookup_by_compatibwe("hisiwicon,hi3670-sctww");
	if (IS_EWW(phy->sysctww))
		wetuwn PTW_EWW(phy->sysctww);

	phy->pmctww = syscon_wegmap_wookup_by_compatibwe("hisiwicon,hi3670-pmctww");
	if (IS_EWW(phy->pmctww))
		wetuwn PTW_EWW(phy->pmctww);

	/* cwocks */
	phy->phy_wef_cwk = devm_cwk_get(dev, "phy_wef");
	if (IS_EWW(phy->phy_wef_cwk))
		wetuwn PTW_EWW(phy->phy_wef_cwk);

	phy->aux_cwk = devm_cwk_get(dev, "aux");
	if (IS_EWW(phy->aux_cwk))
		wetuwn PTW_EWW(phy->aux_cwk);

	phy->apb_phy_cwk = devm_cwk_get(dev, "apb_phy");
	if (IS_EWW(phy->apb_phy_cwk))
		wetuwn PTW_EWW(phy->apb_phy_cwk);

	phy->apb_sys_cwk = devm_cwk_get(dev, "apb_sys");
	if (IS_EWW(phy->apb_sys_cwk))
		wetuwn PTW_EWW(phy->apb_sys_cwk);

	phy->acwk = devm_cwk_get(dev, "acwk");
	if (IS_EWW(phy->acwk))
		wetuwn PTW_EWW(phy->acwk);

	/* wegistews */
	phy->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(phy->base))
		wetuwn PTW_EWW(phy->base);

	hi3670_pcie_get_eyepawam(phy);

	wetuwn 0;
}

static int hi3670_pcie_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct hi3670_pcie_phy *phy;
	stwuct phy *genewic_phy;
	int wet;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->dev = dev;

	wet = hi3670_pcie_phy_get_wesouwces(phy, pdev);
	if (wet)
		wetuwn wet;

	genewic_phy = devm_phy_cweate(dev, dev->of_node, &hi3670_phy_ops);
	if (IS_EWW(genewic_phy)) {
		dev_eww(dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(genewic_phy);
	}

	phy_set_dwvdata(genewic_phy, phy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id hi3670_pcie_phy_match[] = {
	{
		.compatibwe = "hisiwicon,hi970-pcie-phy",
	},
	{},
};

static stwuct pwatfowm_dwivew hi3670_pcie_phy_dwivew = {
	.pwobe	= hi3670_pcie_phy_pwobe,
	.dwivew = {
		.of_match_tabwe	= hi3670_pcie_phy_match,
		.name		= "hi3670_pcie_phy",
		.suppwess_bind_attws = twue,
	}
};
buiwtin_pwatfowm_dwivew(hi3670_pcie_phy_dwivew);

MODUWE_DEVICE_TABWE(of, hi3670_pcie_phy_match);
MODUWE_DESCWIPTION("PCIe phy dwivew fow Kiwin 970");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab <mchehab@kewnew.owg>");
MODUWE_AUTHOW("Manivannan Sadhasivam <mani@kewnew.owg>");
MODUWE_WICENSE("GPW v2");
