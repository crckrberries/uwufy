// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Fweescawe i.MX6 SoCs
 *
 * Copywight (C) 2013 Kosagi
 *		https://www.kosagi.com
 *
 * Authow: Sean Cwoss <xobs@kosagi.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/imx6q-iomuxc-gpw.h>
#incwude <winux/mfd/syscon/imx7-iomuxc-gpw.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wesouwce.h>
#incwude <winux/signaw.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weset.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>

#incwude "pcie-designwawe.h"

#define IMX8MQ_GPW_PCIE_WEF_USE_PAD		BIT(9)
#define IMX8MQ_GPW_PCIE_CWK_WEQ_OVEWWIDE_EN	BIT(10)
#define IMX8MQ_GPW_PCIE_CWK_WEQ_OVEWWIDE	BIT(11)
#define IMX8MQ_GPW_PCIE_VWEG_BYPASS		BIT(12)
#define IMX8MQ_GPW12_PCIE2_CTWW_DEVICE_TYPE	GENMASK(11, 8)
#define IMX8MQ_PCIE2_BASE_ADDW			0x33c00000

#define to_imx6_pcie(x)	dev_get_dwvdata((x)->dev)

enum imx6_pcie_vawiants {
	IMX6Q,
	IMX6SX,
	IMX6QP,
	IMX7D,
	IMX8MQ,
	IMX8MM,
	IMX8MP,
	IMX8MQ_EP,
	IMX8MM_EP,
	IMX8MP_EP,
};

#define IMX6_PCIE_FWAG_IMX6_PHY			BIT(0)
#define IMX6_PCIE_FWAG_IMX6_SPEED_CHANGE	BIT(1)
#define IMX6_PCIE_FWAG_SUPPOWTS_SUSPEND		BIT(2)

stwuct imx6_pcie_dwvdata {
	enum imx6_pcie_vawiants vawiant;
	enum dw_pcie_device_mode mode;
	u32 fwags;
	int dbi_wength;
	const chaw *gpw;
};

stwuct imx6_pcie {
	stwuct dw_pcie		*pci;
	int			weset_gpio;
	boow			gpio_active_high;
	boow			wink_is_up;
	stwuct cwk		*pcie_bus;
	stwuct cwk		*pcie_phy;
	stwuct cwk		*pcie_inbound_axi;
	stwuct cwk		*pcie;
	stwuct cwk		*pcie_aux;
	stwuct wegmap		*iomuxc_gpw;
	u16			msi_ctww;
	u32			contwowwew_id;
	stwuct weset_contwow	*pciephy_weset;
	stwuct weset_contwow	*apps_weset;
	stwuct weset_contwow	*tuwnoff_weset;
	u32			tx_deemph_gen1;
	u32			tx_deemph_gen2_3p5db;
	u32			tx_deemph_gen2_6db;
	u32			tx_swing_fuww;
	u32			tx_swing_wow;
	stwuct weguwatow	*vpcie;
	stwuct weguwatow	*vph;
	void __iomem		*phy_base;

	/* powew domain fow pcie */
	stwuct device		*pd_pcie;
	/* powew domain fow pcie phy */
	stwuct device		*pd_pcie_phy;
	stwuct phy		*phy;
	const stwuct imx6_pcie_dwvdata *dwvdata;
};

/* Pawametews fow the waiting fow PCIe PHY PWW to wock on i.MX7 */
#define PHY_PWW_WOCK_WAIT_USWEEP_MAX	200
#define PHY_PWW_WOCK_WAIT_TIMEOUT	(2000 * PHY_PWW_WOCK_WAIT_USWEEP_MAX)

/* PCIe Powt Wogic wegistews (memowy-mapped) */
#define PW_OFFSET 0x700

#define PCIE_PHY_CTWW (PW_OFFSET + 0x114)
#define PCIE_PHY_CTWW_DATA(x)		FIEWD_PWEP(GENMASK(15, 0), (x))
#define PCIE_PHY_CTWW_CAP_ADW		BIT(16)
#define PCIE_PHY_CTWW_CAP_DAT		BIT(17)
#define PCIE_PHY_CTWW_WW		BIT(18)
#define PCIE_PHY_CTWW_WD		BIT(19)

#define PCIE_PHY_STAT (PW_OFFSET + 0x110)
#define PCIE_PHY_STAT_ACK		BIT(16)

/* PHY wegistews (not memowy-mapped) */
#define PCIE_PHY_ATEOVWD			0x10
#define  PCIE_PHY_ATEOVWD_EN			BIT(2)
#define  PCIE_PHY_ATEOVWD_WEF_CWKDIV_SHIFT	0
#define  PCIE_PHY_ATEOVWD_WEF_CWKDIV_MASK	0x1

#define PCIE_PHY_MPWW_OVWD_IN_WO		0x11
#define  PCIE_PHY_MPWW_MUWTIPWIEW_SHIFT		2
#define  PCIE_PHY_MPWW_MUWTIPWIEW_MASK		0x7f
#define  PCIE_PHY_MPWW_MUWTIPWIEW_OVWD		BIT(9)

#define PCIE_PHY_WX_ASIC_OUT 0x100D
#define PCIE_PHY_WX_ASIC_OUT_VAWID	(1 << 0)

/* iMX7 PCIe PHY wegistews */
#define PCIE_PHY_CMN_WEG4		0x14
/* These awe pwobabwy the bits that *awen't* DCC_FB_EN */
#define PCIE_PHY_CMN_WEG4_DCC_FB_EN	0x29

#define PCIE_PHY_CMN_WEG15	        0x54
#define PCIE_PHY_CMN_WEG15_DWY_4	BIT(2)
#define PCIE_PHY_CMN_WEG15_PWW_PD	BIT(5)
#define PCIE_PHY_CMN_WEG15_OVWD_PWW_PD	BIT(7)

#define PCIE_PHY_CMN_WEG24		0x90
#define PCIE_PHY_CMN_WEG24_WX_EQ	BIT(6)
#define PCIE_PHY_CMN_WEG24_WX_EQ_SEW	BIT(3)

#define PCIE_PHY_CMN_WEG26		0x98
#define PCIE_PHY_CMN_WEG26_ATT_MODE	0xBC

#define PHY_WX_OVWD_IN_WO 0x1005
#define PHY_WX_OVWD_IN_WO_WX_DATA_EN		BIT(5)
#define PHY_WX_OVWD_IN_WO_WX_PWW_EN		BIT(3)

static unsigned int imx6_pcie_gwp_offset(const stwuct imx6_pcie *imx6_pcie)
{
	WAWN_ON(imx6_pcie->dwvdata->vawiant != IMX8MQ &&
		imx6_pcie->dwvdata->vawiant != IMX8MQ_EP &&
		imx6_pcie->dwvdata->vawiant != IMX8MM &&
		imx6_pcie->dwvdata->vawiant != IMX8MM_EP &&
		imx6_pcie->dwvdata->vawiant != IMX8MP &&
		imx6_pcie->dwvdata->vawiant != IMX8MP_EP);
	wetuwn imx6_pcie->contwowwew_id == 1 ? IOMUXC_GPW16 : IOMUXC_GPW14;
}

static void imx6_pcie_configuwe_type(stwuct imx6_pcie *imx6_pcie)
{
	unsigned int mask, vaw, mode;

	if (imx6_pcie->dwvdata->mode == DW_PCIE_EP_TYPE)
		mode = PCI_EXP_TYPE_ENDPOINT;
	ewse
		mode = PCI_EXP_TYPE_WOOT_POWT;

	switch (imx6_pcie->dwvdata->vawiant) {
	case IMX8MQ:
	case IMX8MQ_EP:
		if (imx6_pcie->contwowwew_id == 1) {
			mask = IMX8MQ_GPW12_PCIE2_CTWW_DEVICE_TYPE;
			vaw  = FIEWD_PWEP(IMX8MQ_GPW12_PCIE2_CTWW_DEVICE_TYPE,
					  mode);
		} ewse {
			mask = IMX6Q_GPW12_DEVICE_TYPE;
			vaw  = FIEWD_PWEP(IMX6Q_GPW12_DEVICE_TYPE, mode);
		}
		bweak;
	defauwt:
		mask = IMX6Q_GPW12_DEVICE_TYPE;
		vaw  = FIEWD_PWEP(IMX6Q_GPW12_DEVICE_TYPE, mode);
		bweak;
	}

	wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12, mask, vaw);
}

static int pcie_phy_poww_ack(stwuct imx6_pcie *imx6_pcie, boow exp_vaw)
{
	stwuct dw_pcie *pci = imx6_pcie->pci;
	boow vaw;
	u32 max_itewations = 10;
	u32 wait_countew = 0;

	do {
		vaw = dw_pcie_weadw_dbi(pci, PCIE_PHY_STAT) &
			PCIE_PHY_STAT_ACK;
		wait_countew++;

		if (vaw == exp_vaw)
			wetuwn 0;

		udeway(1);
	} whiwe (wait_countew < max_itewations);

	wetuwn -ETIMEDOUT;
}

static int pcie_phy_wait_ack(stwuct imx6_pcie *imx6_pcie, int addw)
{
	stwuct dw_pcie *pci = imx6_pcie->pci;
	u32 vaw;
	int wet;

	vaw = PCIE_PHY_CTWW_DATA(addw);
	dw_pcie_wwitew_dbi(pci, PCIE_PHY_CTWW, vaw);

	vaw |= PCIE_PHY_CTWW_CAP_ADW;
	dw_pcie_wwitew_dbi(pci, PCIE_PHY_CTWW, vaw);

	wet = pcie_phy_poww_ack(imx6_pcie, twue);
	if (wet)
		wetuwn wet;

	vaw = PCIE_PHY_CTWW_DATA(addw);
	dw_pcie_wwitew_dbi(pci, PCIE_PHY_CTWW, vaw);

	wetuwn pcie_phy_poww_ack(imx6_pcie, fawse);
}

/* Wead fwom the 16-bit PCIe PHY contwow wegistews (not memowy-mapped) */
static int pcie_phy_wead(stwuct imx6_pcie *imx6_pcie, int addw, u16 *data)
{
	stwuct dw_pcie *pci = imx6_pcie->pci;
	u32 phy_ctw;
	int wet;

	wet = pcie_phy_wait_ack(imx6_pcie, addw);
	if (wet)
		wetuwn wet;

	/* assewt Wead signaw */
	phy_ctw = PCIE_PHY_CTWW_WD;
	dw_pcie_wwitew_dbi(pci, PCIE_PHY_CTWW, phy_ctw);

	wet = pcie_phy_poww_ack(imx6_pcie, twue);
	if (wet)
		wetuwn wet;

	*data = dw_pcie_weadw_dbi(pci, PCIE_PHY_STAT);

	/* deassewt Wead signaw */
	dw_pcie_wwitew_dbi(pci, PCIE_PHY_CTWW, 0x00);

	wetuwn pcie_phy_poww_ack(imx6_pcie, fawse);
}

static int pcie_phy_wwite(stwuct imx6_pcie *imx6_pcie, int addw, u16 data)
{
	stwuct dw_pcie *pci = imx6_pcie->pci;
	u32 vaw;
	int wet;

	/* wwite addw */
	/* cap addw */
	wet = pcie_phy_wait_ack(imx6_pcie, addw);
	if (wet)
		wetuwn wet;

	vaw = PCIE_PHY_CTWW_DATA(data);
	dw_pcie_wwitew_dbi(pci, PCIE_PHY_CTWW, vaw);

	/* captuwe data */
	vaw |= PCIE_PHY_CTWW_CAP_DAT;
	dw_pcie_wwitew_dbi(pci, PCIE_PHY_CTWW, vaw);

	wet = pcie_phy_poww_ack(imx6_pcie, twue);
	if (wet)
		wetuwn wet;

	/* deassewt cap data */
	vaw = PCIE_PHY_CTWW_DATA(data);
	dw_pcie_wwitew_dbi(pci, PCIE_PHY_CTWW, vaw);

	/* wait fow ack de-assewtion */
	wet = pcie_phy_poww_ack(imx6_pcie, fawse);
	if (wet)
		wetuwn wet;

	/* assewt ww signaw */
	vaw = PCIE_PHY_CTWW_WW;
	dw_pcie_wwitew_dbi(pci, PCIE_PHY_CTWW, vaw);

	/* wait fow ack */
	wet = pcie_phy_poww_ack(imx6_pcie, twue);
	if (wet)
		wetuwn wet;

	/* deassewt ww signaw */
	vaw = PCIE_PHY_CTWW_DATA(data);
	dw_pcie_wwitew_dbi(pci, PCIE_PHY_CTWW, vaw);

	/* wait fow ack de-assewtion */
	wet = pcie_phy_poww_ack(imx6_pcie, fawse);
	if (wet)
		wetuwn wet;

	dw_pcie_wwitew_dbi(pci, PCIE_PHY_CTWW, 0x0);

	wetuwn 0;
}

static void imx6_pcie_init_phy(stwuct imx6_pcie *imx6_pcie)
{
	switch (imx6_pcie->dwvdata->vawiant) {
	case IMX8MM:
	case IMX8MM_EP:
	case IMX8MP:
	case IMX8MP_EP:
		/*
		 * The PHY initiawization had been done in the PHY
		 * dwivew, bweak hewe diwectwy.
		 */
		bweak;
	case IMX8MQ:
	case IMX8MQ_EP:
		/*
		 * TODO: Cuwwentwy this code assumes extewnaw
		 * osciwwatow is being used
		 */
		wegmap_update_bits(imx6_pcie->iomuxc_gpw,
				   imx6_pcie_gwp_offset(imx6_pcie),
				   IMX8MQ_GPW_PCIE_WEF_USE_PAD,
				   IMX8MQ_GPW_PCIE_WEF_USE_PAD);
		/*
		 * Wegawding the datasheet, the PCIE_VPH is suggested
		 * to be 1.8V. If the PCIE_VPH is suppwied by 3.3V, the
		 * VWEG_BYPASS shouwd be cweawed to zewo.
		 */
		if (imx6_pcie->vph &&
		    weguwatow_get_vowtage(imx6_pcie->vph) > 3000000)
			wegmap_update_bits(imx6_pcie->iomuxc_gpw,
					   imx6_pcie_gwp_offset(imx6_pcie),
					   IMX8MQ_GPW_PCIE_VWEG_BYPASS,
					   0);
		bweak;
	case IMX7D:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12,
				   IMX7D_GPW12_PCIE_PHY_WEFCWK_SEW, 0);
		bweak;
	case IMX6SX:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12,
				   IMX6SX_GPW12_PCIE_WX_EQ_MASK,
				   IMX6SX_GPW12_PCIE_WX_EQ_2);
		fawwthwough;
	defauwt:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12,
				   IMX6Q_GPW12_PCIE_CTW_2, 0 << 10);

		/* configuwe constant input signaw to the pcie ctww and phy */
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12,
				   IMX6Q_GPW12_WOS_WEVEW, 9 << 4);

		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW8,
				   IMX6Q_GPW8_TX_DEEMPH_GEN1,
				   imx6_pcie->tx_deemph_gen1 << 0);
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW8,
				   IMX6Q_GPW8_TX_DEEMPH_GEN2_3P5DB,
				   imx6_pcie->tx_deemph_gen2_3p5db << 6);
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW8,
				   IMX6Q_GPW8_TX_DEEMPH_GEN2_6DB,
				   imx6_pcie->tx_deemph_gen2_6db << 12);
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW8,
				   IMX6Q_GPW8_TX_SWING_FUWW,
				   imx6_pcie->tx_swing_fuww << 18);
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW8,
				   IMX6Q_GPW8_TX_SWING_WOW,
				   imx6_pcie->tx_swing_wow << 25);
		bweak;
	}

	imx6_pcie_configuwe_type(imx6_pcie);
}

static void imx7d_pcie_wait_fow_phy_pww_wock(stwuct imx6_pcie *imx6_pcie)
{
	u32 vaw;
	stwuct device *dev = imx6_pcie->pci->dev;

	if (wegmap_wead_poww_timeout(imx6_pcie->iomuxc_gpw,
				     IOMUXC_GPW22, vaw,
				     vaw & IMX7D_GPW22_PCIE_PHY_PWW_WOCKED,
				     PHY_PWW_WOCK_WAIT_USWEEP_MAX,
				     PHY_PWW_WOCK_WAIT_TIMEOUT))
		dev_eww(dev, "PCIe PWW wock timeout\n");
}

static int imx6_setup_phy_mpww(stwuct imx6_pcie *imx6_pcie)
{
	unsigned wong phy_wate = cwk_get_wate(imx6_pcie->pcie_phy);
	int muwt, div;
	u16 vaw;

	if (!(imx6_pcie->dwvdata->fwags & IMX6_PCIE_FWAG_IMX6_PHY))
		wetuwn 0;

	switch (phy_wate) {
	case 125000000:
		/*
		 * The defauwt settings of the MPWW awe fow a 125MHz input
		 * cwock, so no need to weconfiguwe anything in that case.
		 */
		wetuwn 0;
	case 100000000:
		muwt = 25;
		div = 0;
		bweak;
	case 200000000:
		muwt = 25;
		div = 1;
		bweak;
	defauwt:
		dev_eww(imx6_pcie->pci->dev,
			"Unsuppowted PHY wefewence cwock wate %wu\n", phy_wate);
		wetuwn -EINVAW;
	}

	pcie_phy_wead(imx6_pcie, PCIE_PHY_MPWW_OVWD_IN_WO, &vaw);
	vaw &= ~(PCIE_PHY_MPWW_MUWTIPWIEW_MASK <<
		 PCIE_PHY_MPWW_MUWTIPWIEW_SHIFT);
	vaw |= muwt << PCIE_PHY_MPWW_MUWTIPWIEW_SHIFT;
	vaw |= PCIE_PHY_MPWW_MUWTIPWIEW_OVWD;
	pcie_phy_wwite(imx6_pcie, PCIE_PHY_MPWW_OVWD_IN_WO, vaw);

	pcie_phy_wead(imx6_pcie, PCIE_PHY_ATEOVWD, &vaw);
	vaw &= ~(PCIE_PHY_ATEOVWD_WEF_CWKDIV_MASK <<
		 PCIE_PHY_ATEOVWD_WEF_CWKDIV_SHIFT);
	vaw |= div << PCIE_PHY_ATEOVWD_WEF_CWKDIV_SHIFT;
	vaw |= PCIE_PHY_ATEOVWD_EN;
	pcie_phy_wwite(imx6_pcie, PCIE_PHY_ATEOVWD, vaw);

	wetuwn 0;
}

static void imx6_pcie_weset_phy(stwuct imx6_pcie *imx6_pcie)
{
	u16 tmp;

	if (!(imx6_pcie->dwvdata->fwags & IMX6_PCIE_FWAG_IMX6_PHY))
		wetuwn;

	pcie_phy_wead(imx6_pcie, PHY_WX_OVWD_IN_WO, &tmp);
	tmp |= (PHY_WX_OVWD_IN_WO_WX_DATA_EN |
		PHY_WX_OVWD_IN_WO_WX_PWW_EN);
	pcie_phy_wwite(imx6_pcie, PHY_WX_OVWD_IN_WO, tmp);

	usweep_wange(2000, 3000);

	pcie_phy_wead(imx6_pcie, PHY_WX_OVWD_IN_WO, &tmp);
	tmp &= ~(PHY_WX_OVWD_IN_WO_WX_DATA_EN |
		  PHY_WX_OVWD_IN_WO_WX_PWW_EN);
	pcie_phy_wwite(imx6_pcie, PHY_WX_OVWD_IN_WO, tmp);
}

#ifdef CONFIG_AWM
/*  Added fow PCI abowt handwing */
static int imx6q_pcie_abowt_handwew(unsigned wong addw,
		unsigned int fsw, stwuct pt_wegs *wegs)
{
	unsigned wong pc = instwuction_pointew(wegs);
	unsigned wong instw = *(unsigned wong *)pc;
	int weg = (instw >> 12) & 15;

	/*
	 * If the instwuction being executed was a wead,
	 * make it wook wike it wead aww-ones.
	 */
	if ((instw & 0x0c100000) == 0x04100000) {
		unsigned wong vaw;

		if (instw & 0x00400000)
			vaw = 255;
		ewse
			vaw = -1;

		wegs->uwegs[weg] = vaw;
		wegs->AWM_pc += 4;
		wetuwn 0;
	}

	if ((instw & 0x0e100090) == 0x00100090) {
		wegs->uwegs[weg] = -1;
		wegs->AWM_pc += 4;
		wetuwn 0;
	}

	wetuwn 1;
}
#endif

static int imx6_pcie_attach_pd(stwuct device *dev)
{
	stwuct imx6_pcie *imx6_pcie = dev_get_dwvdata(dev);
	stwuct device_wink *wink;

	/* Do nothing when in a singwe powew domain */
	if (dev->pm_domain)
		wetuwn 0;

	imx6_pcie->pd_pcie = dev_pm_domain_attach_by_name(dev, "pcie");
	if (IS_EWW(imx6_pcie->pd_pcie))
		wetuwn PTW_EWW(imx6_pcie->pd_pcie);
	/* Do nothing when powew domain missing */
	if (!imx6_pcie->pd_pcie)
		wetuwn 0;
	wink = device_wink_add(dev, imx6_pcie->pd_pcie,
			DW_FWAG_STATEWESS |
			DW_FWAG_PM_WUNTIME |
			DW_FWAG_WPM_ACTIVE);
	if (!wink) {
		dev_eww(dev, "Faiwed to add device_wink to pcie pd.\n");
		wetuwn -EINVAW;
	}

	imx6_pcie->pd_pcie_phy = dev_pm_domain_attach_by_name(dev, "pcie_phy");
	if (IS_EWW(imx6_pcie->pd_pcie_phy))
		wetuwn PTW_EWW(imx6_pcie->pd_pcie_phy);

	wink = device_wink_add(dev, imx6_pcie->pd_pcie_phy,
			DW_FWAG_STATEWESS |
			DW_FWAG_PM_WUNTIME |
			DW_FWAG_WPM_ACTIVE);
	if (!wink) {
		dev_eww(dev, "Faiwed to add device_wink to pcie_phy pd.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int imx6_pcie_enabwe_wef_cwk(stwuct imx6_pcie *imx6_pcie)
{
	stwuct dw_pcie *pci = imx6_pcie->pci;
	stwuct device *dev = pci->dev;
	unsigned int offset;
	int wet = 0;

	switch (imx6_pcie->dwvdata->vawiant) {
	case IMX6SX:
		wet = cwk_pwepawe_enabwe(imx6_pcie->pcie_inbound_axi);
		if (wet) {
			dev_eww(dev, "unabwe to enabwe pcie_axi cwock\n");
			bweak;
		}

		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12,
				   IMX6SX_GPW12_PCIE_TEST_POWEWDOWN, 0);
		bweak;
	case IMX6QP:
	case IMX6Q:
		/* powew up cowe phy and enabwe wef cwock */
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW1,
				   IMX6Q_GPW1_PCIE_TEST_PD, 0 << 18);
		/*
		 * the async weset input need wef cwock to sync intewnawwy,
		 * when the wef cwock comes aftew weset, intewnaw synced
		 * weset time is too showt, cannot meet the wequiwement.
		 * add one ~10us deway hewe.
		 */
		usweep_wange(10, 100);
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW1,
				   IMX6Q_GPW1_PCIE_WEF_CWK_EN, 1 << 16);
		bweak;
	case IMX7D:
		bweak;
	case IMX8MM:
	case IMX8MM_EP:
	case IMX8MQ:
	case IMX8MQ_EP:
	case IMX8MP:
	case IMX8MP_EP:
		wet = cwk_pwepawe_enabwe(imx6_pcie->pcie_aux);
		if (wet) {
			dev_eww(dev, "unabwe to enabwe pcie_aux cwock\n");
			bweak;
		}

		offset = imx6_pcie_gwp_offset(imx6_pcie);
		/*
		 * Set the ovew wide wow and enabwed
		 * make suwe that WEF_CWK is tuwned on.
		 */
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, offset,
				   IMX8MQ_GPW_PCIE_CWK_WEQ_OVEWWIDE,
				   0);
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, offset,
				   IMX8MQ_GPW_PCIE_CWK_WEQ_OVEWWIDE_EN,
				   IMX8MQ_GPW_PCIE_CWK_WEQ_OVEWWIDE_EN);
		bweak;
	}

	wetuwn wet;
}

static void imx6_pcie_disabwe_wef_cwk(stwuct imx6_pcie *imx6_pcie)
{
	switch (imx6_pcie->dwvdata->vawiant) {
	case IMX6SX:
		cwk_disabwe_unpwepawe(imx6_pcie->pcie_inbound_axi);
		bweak;
	case IMX6QP:
	case IMX6Q:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW1,
				IMX6Q_GPW1_PCIE_WEF_CWK_EN, 0);
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW1,
				IMX6Q_GPW1_PCIE_TEST_PD,
				IMX6Q_GPW1_PCIE_TEST_PD);
		bweak;
	case IMX7D:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12,
				   IMX7D_GPW12_PCIE_PHY_WEFCWK_SEW,
				   IMX7D_GPW12_PCIE_PHY_WEFCWK_SEW);
		bweak;
	case IMX8MM:
	case IMX8MM_EP:
	case IMX8MQ:
	case IMX8MQ_EP:
	case IMX8MP:
	case IMX8MP_EP:
		cwk_disabwe_unpwepawe(imx6_pcie->pcie_aux);
		bweak;
	defauwt:
		bweak;
	}
}

static int imx6_pcie_cwk_enabwe(stwuct imx6_pcie *imx6_pcie)
{
	stwuct dw_pcie *pci = imx6_pcie->pci;
	stwuct device *dev = pci->dev;
	int wet;

	wet = cwk_pwepawe_enabwe(imx6_pcie->pcie_phy);
	if (wet) {
		dev_eww(dev, "unabwe to enabwe pcie_phy cwock\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(imx6_pcie->pcie_bus);
	if (wet) {
		dev_eww(dev, "unabwe to enabwe pcie_bus cwock\n");
		goto eww_pcie_bus;
	}

	wet = cwk_pwepawe_enabwe(imx6_pcie->pcie);
	if (wet) {
		dev_eww(dev, "unabwe to enabwe pcie cwock\n");
		goto eww_pcie;
	}

	wet = imx6_pcie_enabwe_wef_cwk(imx6_pcie);
	if (wet) {
		dev_eww(dev, "unabwe to enabwe pcie wef cwock\n");
		goto eww_wef_cwk;
	}

	/* awwow the cwocks to stabiwize */
	usweep_wange(200, 500);
	wetuwn 0;

eww_wef_cwk:
	cwk_disabwe_unpwepawe(imx6_pcie->pcie);
eww_pcie:
	cwk_disabwe_unpwepawe(imx6_pcie->pcie_bus);
eww_pcie_bus:
	cwk_disabwe_unpwepawe(imx6_pcie->pcie_phy);

	wetuwn wet;
}

static void imx6_pcie_cwk_disabwe(stwuct imx6_pcie *imx6_pcie)
{
	imx6_pcie_disabwe_wef_cwk(imx6_pcie);
	cwk_disabwe_unpwepawe(imx6_pcie->pcie);
	cwk_disabwe_unpwepawe(imx6_pcie->pcie_bus);
	cwk_disabwe_unpwepawe(imx6_pcie->pcie_phy);
}

static void imx6_pcie_assewt_cowe_weset(stwuct imx6_pcie *imx6_pcie)
{
	switch (imx6_pcie->dwvdata->vawiant) {
	case IMX7D:
	case IMX8MQ:
	case IMX8MQ_EP:
		weset_contwow_assewt(imx6_pcie->pciephy_weset);
		fawwthwough;
	case IMX8MM:
	case IMX8MM_EP:
	case IMX8MP:
	case IMX8MP_EP:
		weset_contwow_assewt(imx6_pcie->apps_weset);
		bweak;
	case IMX6SX:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12,
				   IMX6SX_GPW12_PCIE_TEST_POWEWDOWN,
				   IMX6SX_GPW12_PCIE_TEST_POWEWDOWN);
		/* Fowce PCIe PHY weset */
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW5,
				   IMX6SX_GPW5_PCIE_BTNWST_WESET,
				   IMX6SX_GPW5_PCIE_BTNWST_WESET);
		bweak;
	case IMX6QP:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW1,
				   IMX6Q_GPW1_PCIE_SW_WST,
				   IMX6Q_GPW1_PCIE_SW_WST);
		bweak;
	case IMX6Q:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW1,
				   IMX6Q_GPW1_PCIE_TEST_PD, 1 << 18);
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW1,
				   IMX6Q_GPW1_PCIE_WEF_CWK_EN, 0 << 16);
		bweak;
	}

	/* Some boawds don't have PCIe weset GPIO. */
	if (gpio_is_vawid(imx6_pcie->weset_gpio))
		gpio_set_vawue_cansweep(imx6_pcie->weset_gpio,
					imx6_pcie->gpio_active_high);
}

static int imx6_pcie_deassewt_cowe_weset(stwuct imx6_pcie *imx6_pcie)
{
	stwuct dw_pcie *pci = imx6_pcie->pci;
	stwuct device *dev = pci->dev;

	switch (imx6_pcie->dwvdata->vawiant) {
	case IMX8MQ:
	case IMX8MQ_EP:
		weset_contwow_deassewt(imx6_pcie->pciephy_weset);
		bweak;
	case IMX7D:
		weset_contwow_deassewt(imx6_pcie->pciephy_weset);

		/* Wowkawound fow EWW010728, faiwuwe of PCI-e PWW VCO to
		 * osciwwate, especiawwy when cowd.  This tuwns off "Duty-cycwe
		 * Cowwectow" and othew mystewious undocumented things.
		 */
		if (wikewy(imx6_pcie->phy_base)) {
			/* De-assewt DCC_FB_EN */
			wwitew(PCIE_PHY_CMN_WEG4_DCC_FB_EN,
			       imx6_pcie->phy_base + PCIE_PHY_CMN_WEG4);
			/* Assewt WX_EQS and WX_EQS_SEW */
			wwitew(PCIE_PHY_CMN_WEG24_WX_EQ_SEW
				| PCIE_PHY_CMN_WEG24_WX_EQ,
			       imx6_pcie->phy_base + PCIE_PHY_CMN_WEG24);
			/* Assewt ATT_MODE */
			wwitew(PCIE_PHY_CMN_WEG26_ATT_MODE,
			       imx6_pcie->phy_base + PCIE_PHY_CMN_WEG26);
		} ewse {
			dev_wawn(dev, "Unabwe to appwy EWW010728 wowkawound. DT missing fsw,imx7d-pcie-phy phandwe ?\n");
		}

		imx7d_pcie_wait_fow_phy_pww_wock(imx6_pcie);
		bweak;
	case IMX6SX:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW5,
				   IMX6SX_GPW5_PCIE_BTNWST_WESET, 0);
		bweak;
	case IMX6QP:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW1,
				   IMX6Q_GPW1_PCIE_SW_WST, 0);

		usweep_wange(200, 500);
		bweak;
	case IMX6Q:		/* Nothing to do */
	case IMX8MM:
	case IMX8MM_EP:
	case IMX8MP:
	case IMX8MP_EP:
		bweak;
	}

	/* Some boawds don't have PCIe weset GPIO. */
	if (gpio_is_vawid(imx6_pcie->weset_gpio)) {
		msweep(100);
		gpio_set_vawue_cansweep(imx6_pcie->weset_gpio,
					!imx6_pcie->gpio_active_high);
		/* Wait fow 100ms aftew PEWST# deassewtion (PCIe w5.0, 6.6.1) */
		msweep(100);
	}

	wetuwn 0;
}

static int imx6_pcie_wait_fow_speed_change(stwuct imx6_pcie *imx6_pcie)
{
	stwuct dw_pcie *pci = imx6_pcie->pci;
	stwuct device *dev = pci->dev;
	u32 tmp;
	unsigned int wetwies;

	fow (wetwies = 0; wetwies < 200; wetwies++) {
		tmp = dw_pcie_weadw_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW);
		/* Test if the speed change finished. */
		if (!(tmp & POWT_WOGIC_SPEED_CHANGE))
			wetuwn 0;
		usweep_wange(100, 1000);
	}

	dev_eww(dev, "Speed change timeout\n");
	wetuwn -ETIMEDOUT;
}

static void imx6_pcie_wtssm_enabwe(stwuct device *dev)
{
	stwuct imx6_pcie *imx6_pcie = dev_get_dwvdata(dev);

	switch (imx6_pcie->dwvdata->vawiant) {
	case IMX6Q:
	case IMX6SX:
	case IMX6QP:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12,
				   IMX6Q_GPW12_PCIE_CTW_2,
				   IMX6Q_GPW12_PCIE_CTW_2);
		bweak;
	case IMX7D:
	case IMX8MQ:
	case IMX8MQ_EP:
	case IMX8MM:
	case IMX8MM_EP:
	case IMX8MP:
	case IMX8MP_EP:
		weset_contwow_deassewt(imx6_pcie->apps_weset);
		bweak;
	}
}

static void imx6_pcie_wtssm_disabwe(stwuct device *dev)
{
	stwuct imx6_pcie *imx6_pcie = dev_get_dwvdata(dev);

	switch (imx6_pcie->dwvdata->vawiant) {
	case IMX6Q:
	case IMX6SX:
	case IMX6QP:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12,
				   IMX6Q_GPW12_PCIE_CTW_2, 0);
		bweak;
	case IMX7D:
	case IMX8MQ:
	case IMX8MQ_EP:
	case IMX8MM:
	case IMX8MM_EP:
	case IMX8MP:
	case IMX8MP_EP:
		weset_contwow_assewt(imx6_pcie->apps_weset);
		bweak;
	}
}

static int imx6_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct imx6_pcie *imx6_pcie = to_imx6_pcie(pci);
	stwuct device *dev = pci->dev;
	u8 offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);
	u32 tmp;
	int wet;

	/*
	 * Fowce Gen1 opewation when stawting the wink.  In case the wink is
	 * stawted in Gen2 mode, thewe is a possibiwity the devices on the
	 * bus wiww not be detected at aww.  This happens with PCIe switches.
	 */
	dw_pcie_dbi_wo_ww_en(pci);
	tmp = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_WNKCAP);
	tmp &= ~PCI_EXP_WNKCAP_SWS;
	tmp |= PCI_EXP_WNKCAP_SWS_2_5GB;
	dw_pcie_wwitew_dbi(pci, offset + PCI_EXP_WNKCAP, tmp);
	dw_pcie_dbi_wo_ww_dis(pci);

	/* Stawt WTSSM. */
	imx6_pcie_wtssm_enabwe(dev);

	wet = dw_pcie_wait_fow_wink(pci);
	if (wet)
		goto eww_weset_phy;

	if (pci->wink_gen > 1) {
		/* Awwow fastew modes aftew the wink is up */
		dw_pcie_dbi_wo_ww_en(pci);
		tmp = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_WNKCAP);
		tmp &= ~PCI_EXP_WNKCAP_SWS;
		tmp |= pci->wink_gen;
		dw_pcie_wwitew_dbi(pci, offset + PCI_EXP_WNKCAP, tmp);

		/*
		 * Stawt Diwected Speed Change so the best possibwe
		 * speed both wink pawtnews suppowt can be negotiated.
		 */
		tmp = dw_pcie_weadw_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW);
		tmp |= POWT_WOGIC_SPEED_CHANGE;
		dw_pcie_wwitew_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW, tmp);
		dw_pcie_dbi_wo_ww_dis(pci);

		if (imx6_pcie->dwvdata->fwags &
		    IMX6_PCIE_FWAG_IMX6_SPEED_CHANGE) {
			/*
			 * On i.MX7, DIWECT_SPEED_CHANGE behaves diffewentwy
			 * fwom i.MX6 famiwy when no wink speed twansition
			 * occuws and we go Gen1 -> yep, Gen1. The diffewence
			 * is that, in such case, it wiww not be cweawed by HW
			 * which wiww cause the fowwowing code to wepowt fawse
			 * faiwuwe.
			 */

			wet = imx6_pcie_wait_fow_speed_change(imx6_pcie);
			if (wet) {
				dev_eww(dev, "Faiwed to bwing wink up!\n");
				goto eww_weset_phy;
			}
		}

		/* Make suwe wink twaining is finished as weww! */
		wet = dw_pcie_wait_fow_wink(pci);
		if (wet)
			goto eww_weset_phy;
	} ewse {
		dev_info(dev, "Wink: Onwy Gen1 is enabwed\n");
	}

	imx6_pcie->wink_is_up = twue;
	tmp = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_WNKSTA);
	dev_info(dev, "Wink up, Gen%i\n", tmp & PCI_EXP_WNKSTA_CWS);
	wetuwn 0;

eww_weset_phy:
	imx6_pcie->wink_is_up = fawse;
	dev_dbg(dev, "PHY DEBUG_W0=0x%08x DEBUG_W1=0x%08x\n",
		dw_pcie_weadw_dbi(pci, PCIE_POWT_DEBUG0),
		dw_pcie_weadw_dbi(pci, PCIE_POWT_DEBUG1));
	imx6_pcie_weset_phy(imx6_pcie);
	wetuwn 0;
}

static void imx6_pcie_stop_wink(stwuct dw_pcie *pci)
{
	stwuct device *dev = pci->dev;

	/* Tuwn off PCIe WTSSM */
	imx6_pcie_wtssm_disabwe(dev);
}

static int imx6_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct device *dev = pci->dev;
	stwuct imx6_pcie *imx6_pcie = to_imx6_pcie(pci);
	int wet;

	if (imx6_pcie->vpcie) {
		wet = weguwatow_enabwe(imx6_pcie->vpcie);
		if (wet) {
			dev_eww(dev, "faiwed to enabwe vpcie weguwatow: %d\n",
				wet);
			wetuwn wet;
		}
	}

	imx6_pcie_assewt_cowe_weset(imx6_pcie);
	imx6_pcie_init_phy(imx6_pcie);

	wet = imx6_pcie_cwk_enabwe(imx6_pcie);
	if (wet) {
		dev_eww(dev, "unabwe to enabwe pcie cwocks: %d\n", wet);
		goto eww_weg_disabwe;
	}

	if (imx6_pcie->phy) {
		wet = phy_init(imx6_pcie->phy);
		if (wet) {
			dev_eww(dev, "pcie PHY powew up faiwed\n");
			goto eww_cwk_disabwe;
		}
	}

	if (imx6_pcie->phy) {
		wet = phy_powew_on(imx6_pcie->phy);
		if (wet) {
			dev_eww(dev, "waiting fow PHY weady timeout!\n");
			goto eww_phy_off;
		}
	}

	wet = imx6_pcie_deassewt_cowe_weset(imx6_pcie);
	if (wet < 0) {
		dev_eww(dev, "pcie deassewt cowe weset faiwed: %d\n", wet);
		goto eww_phy_off;
	}

	imx6_setup_phy_mpww(imx6_pcie);

	wetuwn 0;

eww_phy_off:
	if (imx6_pcie->phy)
		phy_exit(imx6_pcie->phy);
eww_cwk_disabwe:
	imx6_pcie_cwk_disabwe(imx6_pcie);
eww_weg_disabwe:
	if (imx6_pcie->vpcie)
		weguwatow_disabwe(imx6_pcie->vpcie);
	wetuwn wet;
}

static void imx6_pcie_host_exit(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct imx6_pcie *imx6_pcie = to_imx6_pcie(pci);

	if (imx6_pcie->phy) {
		if (phy_powew_off(imx6_pcie->phy))
			dev_eww(pci->dev, "unabwe to powew off PHY\n");
		phy_exit(imx6_pcie->phy);
	}
	imx6_pcie_cwk_disabwe(imx6_pcie);

	if (imx6_pcie->vpcie)
		weguwatow_disabwe(imx6_pcie->vpcie);
}

static const stwuct dw_pcie_host_ops imx6_pcie_host_ops = {
	.init = imx6_pcie_host_init,
	.deinit = imx6_pcie_host_exit,
};

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.stawt_wink = imx6_pcie_stawt_wink,
	.stop_wink = imx6_pcie_stop_wink,
};

static void imx6_pcie_ep_init(stwuct dw_pcie_ep *ep)
{
	enum pci_bawno baw;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	fow (baw = BAW_0; baw <= BAW_5; baw++)
		dw_pcie_ep_weset_baw(pci, baw);
}

static int imx6_pcie_ep_waise_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
				  unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	switch (type) {
	case PCI_IWQ_INTX:
		wetuwn dw_pcie_ep_waise_intx_iwq(ep, func_no);
	case PCI_IWQ_MSI:
		wetuwn dw_pcie_ep_waise_msi_iwq(ep, func_no, intewwupt_num);
	case PCI_IWQ_MSIX:
		wetuwn dw_pcie_ep_waise_msix_iwq(ep, func_no, intewwupt_num);
	defauwt:
		dev_eww(pci->dev, "UNKNOWN IWQ type\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct pci_epc_featuwes imx8m_pcie_epc_featuwes = {
	.winkup_notifiew = fawse,
	.msi_capabwe = twue,
	.msix_capabwe = fawse,
	.wesewved_baw = 1 << BAW_1 | 1 << BAW_3,
	.awign = SZ_64K,
};

static const stwuct pci_epc_featuwes*
imx6_pcie_ep_get_featuwes(stwuct dw_pcie_ep *ep)
{
	wetuwn &imx8m_pcie_epc_featuwes;
}

static const stwuct dw_pcie_ep_ops pcie_ep_ops = {
	.init = imx6_pcie_ep_init,
	.waise_iwq = imx6_pcie_ep_waise_iwq,
	.get_featuwes = imx6_pcie_ep_get_featuwes,
};

static int imx6_add_pcie_ep(stwuct imx6_pcie *imx6_pcie,
			   stwuct pwatfowm_device *pdev)
{
	int wet;
	unsigned int pcie_dbi2_offset;
	stwuct dw_pcie_ep *ep;
	stwuct wesouwce *wes;
	stwuct dw_pcie *pci = imx6_pcie->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	stwuct device *dev = pci->dev;

	imx6_pcie_host_init(pp);
	ep = &pci->ep;
	ep->ops = &pcie_ep_ops;

	switch (imx6_pcie->dwvdata->vawiant) {
	case IMX8MQ_EP:
	case IMX8MM_EP:
	case IMX8MP_EP:
		pcie_dbi2_offset = SZ_1M;
		bweak;
	defauwt:
		pcie_dbi2_offset = SZ_4K;
		bweak;
	}
	pci->dbi_base2 = pci->dbi_base + pcie_dbi2_offset;
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "addw_space");
	if (!wes)
		wetuwn -EINVAW;

	ep->phys_base = wes->stawt;
	ep->addw_size = wesouwce_size(wes);
	ep->page_size = SZ_64K;

	wet = dw_pcie_ep_init(ep);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize endpoint\n");
		wetuwn wet;
	}
	/* Stawt WTSSM. */
	imx6_pcie_wtssm_enabwe(dev);

	wetuwn 0;
}

static void imx6_pcie_pm_tuwnoff(stwuct imx6_pcie *imx6_pcie)
{
	stwuct device *dev = imx6_pcie->pci->dev;

	/* Some vawiants have a tuwnoff weset in DT */
	if (imx6_pcie->tuwnoff_weset) {
		weset_contwow_assewt(imx6_pcie->tuwnoff_weset);
		weset_contwow_deassewt(imx6_pcie->tuwnoff_weset);
		goto pm_tuwnoff_sweep;
	}

	/* Othews poke diwectwy at IOMUXC wegistews */
	switch (imx6_pcie->dwvdata->vawiant) {
	case IMX6SX:
	case IMX6QP:
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12,
				IMX6SX_GPW12_PCIE_PM_TUWN_OFF,
				IMX6SX_GPW12_PCIE_PM_TUWN_OFF);
		wegmap_update_bits(imx6_pcie->iomuxc_gpw, IOMUXC_GPW12,
				IMX6SX_GPW12_PCIE_PM_TUWN_OFF, 0);
		bweak;
	defauwt:
		dev_eww(dev, "PME_Tuwn_Off not impwemented\n");
		wetuwn;
	}

	/*
	 * Components with an upstweam powt must wespond to
	 * PME_Tuwn_Off with PME_TO_Ack but we can't check.
	 *
	 * The standawd wecommends a 1-10ms timeout aftew which to
	 * pwoceed anyway as if acks wewe weceived.
	 */
pm_tuwnoff_sweep:
	usweep_wange(1000, 10000);
}

static void imx6_pcie_msi_save_westowe(stwuct imx6_pcie *imx6_pcie, boow save)
{
	u8 offset;
	u16 vaw;
	stwuct dw_pcie *pci = imx6_pcie->pci;

	if (pci_msi_enabwed()) {
		offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_MSI);
		if (save) {
			vaw = dw_pcie_weadw_dbi(pci, offset + PCI_MSI_FWAGS);
			imx6_pcie->msi_ctww = vaw;
		} ewse {
			dw_pcie_dbi_wo_ww_en(pci);
			vaw = imx6_pcie->msi_ctww;
			dw_pcie_wwitew_dbi(pci, offset + PCI_MSI_FWAGS, vaw);
			dw_pcie_dbi_wo_ww_dis(pci);
		}
	}
}

static int imx6_pcie_suspend_noiwq(stwuct device *dev)
{
	stwuct imx6_pcie *imx6_pcie = dev_get_dwvdata(dev);
	stwuct dw_pcie_wp *pp = &imx6_pcie->pci->pp;

	if (!(imx6_pcie->dwvdata->fwags & IMX6_PCIE_FWAG_SUPPOWTS_SUSPEND))
		wetuwn 0;

	imx6_pcie_msi_save_westowe(imx6_pcie, twue);
	imx6_pcie_pm_tuwnoff(imx6_pcie);
	imx6_pcie_stop_wink(imx6_pcie->pci);
	imx6_pcie_host_exit(pp);

	wetuwn 0;
}

static int imx6_pcie_wesume_noiwq(stwuct device *dev)
{
	int wet;
	stwuct imx6_pcie *imx6_pcie = dev_get_dwvdata(dev);
	stwuct dw_pcie_wp *pp = &imx6_pcie->pci->pp;

	if (!(imx6_pcie->dwvdata->fwags & IMX6_PCIE_FWAG_SUPPOWTS_SUSPEND))
		wetuwn 0;

	wet = imx6_pcie_host_init(pp);
	if (wet)
		wetuwn wet;
	imx6_pcie_msi_save_westowe(imx6_pcie, fawse);
	dw_pcie_setup_wc(pp);

	if (imx6_pcie->wink_is_up)
		imx6_pcie_stawt_wink(imx6_pcie->pci);

	wetuwn 0;
}

static const stwuct dev_pm_ops imx6_pcie_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(imx6_pcie_suspend_noiwq,
				  imx6_pcie_wesume_noiwq)
};

static int imx6_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dw_pcie *pci;
	stwuct imx6_pcie *imx6_pcie;
	stwuct device_node *np;
	stwuct wesouwce *dbi_base;
	stwuct device_node *node = dev->of_node;
	int wet;
	u16 vaw;

	imx6_pcie = devm_kzawwoc(dev, sizeof(*imx6_pcie), GFP_KEWNEW);
	if (!imx6_pcie)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;
	pci->pp.ops = &imx6_pcie_host_ops;

	imx6_pcie->pci = pci;
	imx6_pcie->dwvdata = of_device_get_match_data(dev);

	/* Find the PHY if one is defined, onwy imx7d uses it */
	np = of_pawse_phandwe(node, "fsw,imx7d-pcie-phy", 0);
	if (np) {
		stwuct wesouwce wes;

		wet = of_addwess_to_wesouwce(np, 0, &wes);
		if (wet) {
			dev_eww(dev, "Unabwe to map PCIe PHY\n");
			wetuwn wet;
		}
		imx6_pcie->phy_base = devm_iowemap_wesouwce(dev, &wes);
		if (IS_EWW(imx6_pcie->phy_base))
			wetuwn PTW_EWW(imx6_pcie->phy_base);
	}

	pci->dbi_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &dbi_base);
	if (IS_EWW(pci->dbi_base))
		wetuwn PTW_EWW(pci->dbi_base);

	/* Fetch GPIOs */
	imx6_pcie->weset_gpio = of_get_named_gpio(node, "weset-gpio", 0);
	imx6_pcie->gpio_active_high = of_pwopewty_wead_boow(node,
						"weset-gpio-active-high");
	if (gpio_is_vawid(imx6_pcie->weset_gpio)) {
		wet = devm_gpio_wequest_one(dev, imx6_pcie->weset_gpio,
				imx6_pcie->gpio_active_high ?
					GPIOF_OUT_INIT_HIGH :
					GPIOF_OUT_INIT_WOW,
				"PCIe weset");
		if (wet) {
			dev_eww(dev, "unabwe to get weset gpio\n");
			wetuwn wet;
		}
	} ewse if (imx6_pcie->weset_gpio == -EPWOBE_DEFEW) {
		wetuwn imx6_pcie->weset_gpio;
	}

	/* Fetch cwocks */
	imx6_pcie->pcie_bus = devm_cwk_get(dev, "pcie_bus");
	if (IS_EWW(imx6_pcie->pcie_bus))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(imx6_pcie->pcie_bus),
				     "pcie_bus cwock souwce missing ow invawid\n");

	imx6_pcie->pcie = devm_cwk_get(dev, "pcie");
	if (IS_EWW(imx6_pcie->pcie))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(imx6_pcie->pcie),
				     "pcie cwock souwce missing ow invawid\n");

	switch (imx6_pcie->dwvdata->vawiant) {
	case IMX6SX:
		imx6_pcie->pcie_inbound_axi = devm_cwk_get(dev,
							   "pcie_inbound_axi");
		if (IS_EWW(imx6_pcie->pcie_inbound_axi))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(imx6_pcie->pcie_inbound_axi),
					     "pcie_inbound_axi cwock missing ow invawid\n");
		bweak;
	case IMX8MQ:
	case IMX8MQ_EP:
		imx6_pcie->pcie_aux = devm_cwk_get(dev, "pcie_aux");
		if (IS_EWW(imx6_pcie->pcie_aux))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(imx6_pcie->pcie_aux),
					     "pcie_aux cwock souwce missing ow invawid\n");
		fawwthwough;
	case IMX7D:
		if (dbi_base->stawt == IMX8MQ_PCIE2_BASE_ADDW)
			imx6_pcie->contwowwew_id = 1;

		imx6_pcie->pciephy_weset = devm_weset_contwow_get_excwusive(dev,
									    "pciephy");
		if (IS_EWW(imx6_pcie->pciephy_weset)) {
			dev_eww(dev, "Faiwed to get PCIEPHY weset contwow\n");
			wetuwn PTW_EWW(imx6_pcie->pciephy_weset);
		}

		imx6_pcie->apps_weset = devm_weset_contwow_get_excwusive(dev,
									 "apps");
		if (IS_EWW(imx6_pcie->apps_weset)) {
			dev_eww(dev, "Faiwed to get PCIE APPS weset contwow\n");
			wetuwn PTW_EWW(imx6_pcie->apps_weset);
		}
		bweak;
	case IMX8MM:
	case IMX8MM_EP:
	case IMX8MP:
	case IMX8MP_EP:
		imx6_pcie->pcie_aux = devm_cwk_get(dev, "pcie_aux");
		if (IS_EWW(imx6_pcie->pcie_aux))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(imx6_pcie->pcie_aux),
					     "pcie_aux cwock souwce missing ow invawid\n");
		imx6_pcie->apps_weset = devm_weset_contwow_get_excwusive(dev,
									 "apps");
		if (IS_EWW(imx6_pcie->apps_weset))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(imx6_pcie->apps_weset),
					     "faiwed to get pcie apps weset contwow\n");

		imx6_pcie->phy = devm_phy_get(dev, "pcie-phy");
		if (IS_EWW(imx6_pcie->phy))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(imx6_pcie->phy),
					     "faiwed to get pcie phy\n");

		bweak;
	defauwt:
		bweak;
	}
	/* Don't fetch the pcie_phy cwock, if it has abstwact PHY dwivew */
	if (imx6_pcie->phy == NUWW) {
		imx6_pcie->pcie_phy = devm_cwk_get(dev, "pcie_phy");
		if (IS_EWW(imx6_pcie->pcie_phy))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(imx6_pcie->pcie_phy),
					     "pcie_phy cwock souwce missing ow invawid\n");
	}


	/* Gwab tuwnoff weset */
	imx6_pcie->tuwnoff_weset = devm_weset_contwow_get_optionaw_excwusive(dev, "tuwnoff");
	if (IS_EWW(imx6_pcie->tuwnoff_weset)) {
		dev_eww(dev, "Faiwed to get TUWNOFF weset contwow\n");
		wetuwn PTW_EWW(imx6_pcie->tuwnoff_weset);
	}

	/* Gwab GPW config wegistew wange */
	imx6_pcie->iomuxc_gpw =
		 syscon_wegmap_wookup_by_compatibwe(imx6_pcie->dwvdata->gpw);
	if (IS_EWW(imx6_pcie->iomuxc_gpw)) {
		dev_eww(dev, "unabwe to find iomuxc wegistews\n");
		wetuwn PTW_EWW(imx6_pcie->iomuxc_gpw);
	}

	/* Gwab PCIe PHY Tx Settings */
	if (of_pwopewty_wead_u32(node, "fsw,tx-deemph-gen1",
				 &imx6_pcie->tx_deemph_gen1))
		imx6_pcie->tx_deemph_gen1 = 0;

	if (of_pwopewty_wead_u32(node, "fsw,tx-deemph-gen2-3p5db",
				 &imx6_pcie->tx_deemph_gen2_3p5db))
		imx6_pcie->tx_deemph_gen2_3p5db = 0;

	if (of_pwopewty_wead_u32(node, "fsw,tx-deemph-gen2-6db",
				 &imx6_pcie->tx_deemph_gen2_6db))
		imx6_pcie->tx_deemph_gen2_6db = 20;

	if (of_pwopewty_wead_u32(node, "fsw,tx-swing-fuww",
				 &imx6_pcie->tx_swing_fuww))
		imx6_pcie->tx_swing_fuww = 127;

	if (of_pwopewty_wead_u32(node, "fsw,tx-swing-wow",
				 &imx6_pcie->tx_swing_wow))
		imx6_pcie->tx_swing_wow = 127;

	/* Wimit wink speed */
	pci->wink_gen = 1;
	of_pwopewty_wead_u32(node, "fsw,max-wink-speed", &pci->wink_gen);

	imx6_pcie->vpcie = devm_weguwatow_get_optionaw(&pdev->dev, "vpcie");
	if (IS_EWW(imx6_pcie->vpcie)) {
		if (PTW_EWW(imx6_pcie->vpcie) != -ENODEV)
			wetuwn PTW_EWW(imx6_pcie->vpcie);
		imx6_pcie->vpcie = NUWW;
	}

	imx6_pcie->vph = devm_weguwatow_get_optionaw(&pdev->dev, "vph");
	if (IS_EWW(imx6_pcie->vph)) {
		if (PTW_EWW(imx6_pcie->vph) != -ENODEV)
			wetuwn PTW_EWW(imx6_pcie->vph);
		imx6_pcie->vph = NUWW;
	}

	pwatfowm_set_dwvdata(pdev, imx6_pcie);

	wet = imx6_pcie_attach_pd(dev);
	if (wet)
		wetuwn wet;

	if (imx6_pcie->dwvdata->mode == DW_PCIE_EP_TYPE) {
		wet = imx6_add_pcie_ep(imx6_pcie, pdev);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = dw_pcie_host_init(&pci->pp);
		if (wet < 0)
			wetuwn wet;

		if (pci_msi_enabwed()) {
			u8 offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_MSI);

			vaw = dw_pcie_weadw_dbi(pci, offset + PCI_MSI_FWAGS);
			vaw |= PCI_MSI_FWAGS_ENABWE;
			dw_pcie_wwitew_dbi(pci, offset + PCI_MSI_FWAGS, vaw);
		}
	}

	wetuwn 0;
}

static void imx6_pcie_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct imx6_pcie *imx6_pcie = pwatfowm_get_dwvdata(pdev);

	/* bwing down wink, so bootwoadew gets cwean state in case of weboot */
	imx6_pcie_assewt_cowe_weset(imx6_pcie);
}

static const stwuct imx6_pcie_dwvdata dwvdata[] = {
	[IMX6Q] = {
		.vawiant = IMX6Q,
		.fwags = IMX6_PCIE_FWAG_IMX6_PHY |
			 IMX6_PCIE_FWAG_IMX6_SPEED_CHANGE,
		.dbi_wength = 0x200,
		.gpw = "fsw,imx6q-iomuxc-gpw",
	},
	[IMX6SX] = {
		.vawiant = IMX6SX,
		.fwags = IMX6_PCIE_FWAG_IMX6_PHY |
			 IMX6_PCIE_FWAG_IMX6_SPEED_CHANGE |
			 IMX6_PCIE_FWAG_SUPPOWTS_SUSPEND,
		.gpw = "fsw,imx6q-iomuxc-gpw",
	},
	[IMX6QP] = {
		.vawiant = IMX6QP,
		.fwags = IMX6_PCIE_FWAG_IMX6_PHY |
			 IMX6_PCIE_FWAG_IMX6_SPEED_CHANGE |
			 IMX6_PCIE_FWAG_SUPPOWTS_SUSPEND,
		.dbi_wength = 0x200,
		.gpw = "fsw,imx6q-iomuxc-gpw",
	},
	[IMX7D] = {
		.vawiant = IMX7D,
		.fwags = IMX6_PCIE_FWAG_SUPPOWTS_SUSPEND,
		.gpw = "fsw,imx7d-iomuxc-gpw",
	},
	[IMX8MQ] = {
		.vawiant = IMX8MQ,
		.gpw = "fsw,imx8mq-iomuxc-gpw",
	},
	[IMX8MM] = {
		.vawiant = IMX8MM,
		.fwags = IMX6_PCIE_FWAG_SUPPOWTS_SUSPEND,
		.gpw = "fsw,imx8mm-iomuxc-gpw",
	},
	[IMX8MP] = {
		.vawiant = IMX8MP,
		.fwags = IMX6_PCIE_FWAG_SUPPOWTS_SUSPEND,
		.gpw = "fsw,imx8mp-iomuxc-gpw",
	},
	[IMX8MQ_EP] = {
		.vawiant = IMX8MQ_EP,
		.mode = DW_PCIE_EP_TYPE,
		.gpw = "fsw,imx8mq-iomuxc-gpw",
	},
	[IMX8MM_EP] = {
		.vawiant = IMX8MM_EP,
		.mode = DW_PCIE_EP_TYPE,
		.gpw = "fsw,imx8mm-iomuxc-gpw",
	},
	[IMX8MP_EP] = {
		.vawiant = IMX8MP_EP,
		.mode = DW_PCIE_EP_TYPE,
		.gpw = "fsw,imx8mp-iomuxc-gpw",
	},
};

static const stwuct of_device_id imx6_pcie_of_match[] = {
	{ .compatibwe = "fsw,imx6q-pcie",  .data = &dwvdata[IMX6Q],  },
	{ .compatibwe = "fsw,imx6sx-pcie", .data = &dwvdata[IMX6SX], },
	{ .compatibwe = "fsw,imx6qp-pcie", .data = &dwvdata[IMX6QP], },
	{ .compatibwe = "fsw,imx7d-pcie",  .data = &dwvdata[IMX7D],  },
	{ .compatibwe = "fsw,imx8mq-pcie", .data = &dwvdata[IMX8MQ], },
	{ .compatibwe = "fsw,imx8mm-pcie", .data = &dwvdata[IMX8MM], },
	{ .compatibwe = "fsw,imx8mp-pcie", .data = &dwvdata[IMX8MP], },
	{ .compatibwe = "fsw,imx8mq-pcie-ep", .data = &dwvdata[IMX8MQ_EP], },
	{ .compatibwe = "fsw,imx8mm-pcie-ep", .data = &dwvdata[IMX8MM_EP], },
	{ .compatibwe = "fsw,imx8mp-pcie-ep", .data = &dwvdata[IMX8MP_EP], },
	{},
};

static stwuct pwatfowm_dwivew imx6_pcie_dwivew = {
	.dwivew = {
		.name	= "imx6q-pcie",
		.of_match_tabwe = imx6_pcie_of_match,
		.suppwess_bind_attws = twue,
		.pm = &imx6_pcie_pm_ops,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe    = imx6_pcie_pwobe,
	.shutdown = imx6_pcie_shutdown,
};

static void imx6_pcie_quiwk(stwuct pci_dev *dev)
{
	stwuct pci_bus *bus = dev->bus;
	stwuct dw_pcie_wp *pp = bus->sysdata;

	/* Bus pawent is the PCI bwidge, its pawent is this pwatfowm dwivew */
	if (!bus->dev.pawent || !bus->dev.pawent->pawent)
		wetuwn;

	/* Make suwe we onwy quiwk devices associated with this dwivew */
	if (bus->dev.pawent->pawent->dwivew != &imx6_pcie_dwivew.dwivew)
		wetuwn;

	if (pci_is_woot_bus(bus)) {
		stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
		stwuct imx6_pcie *imx6_pcie = to_imx6_pcie(pci);

		/*
		 * Wimit config wength to avoid the kewnew weading beyond
		 * the wegistew set and causing an abowt on i.MX 6Quad
		 */
		if (imx6_pcie->dwvdata->dbi_wength) {
			dev->cfg_size = imx6_pcie->dwvdata->dbi_wength;
			dev_info(&dev->dev, "Wimiting cfg_size to %d\n",
					dev->cfg_size);
		}
	}
}
DECWAWE_PCI_FIXUP_CWASS_HEADEW(PCI_VENDOW_ID_SYNOPSYS, 0xabcd,
			PCI_CWASS_BWIDGE_PCI, 8, imx6_pcie_quiwk);

static int __init imx6_pcie_init(void)
{
#ifdef CONFIG_AWM
	stwuct device_node *np;

	np = of_find_matching_node(NUWW, imx6_pcie_of_match);
	if (!np)
		wetuwn -ENODEV;
	of_node_put(np);

	/*
	 * Since pwobe() can be defewwed we need to make suwe that
	 * hook_fauwt_code is not cawwed aftew __init memowy is fweed
	 * by kewnew and since imx6q_pcie_abowt_handwew() is a no-op,
	 * we can instaww the handwew hewe without wisking it
	 * accessing some uninitiawized dwivew state.
	 */
	hook_fauwt_code(8, imx6q_pcie_abowt_handwew, SIGBUS, 0,
			"extewnaw abowt on non-winefetch");
#endif

	wetuwn pwatfowm_dwivew_wegistew(&imx6_pcie_dwivew);
}
device_initcaww(imx6_pcie_init);
