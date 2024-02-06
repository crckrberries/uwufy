// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Sawvo PHY is a 28nm PHY, it is a wegacy PHY, and onwy
 * fow USB3 and USB2.
 *
 * Copywight (c) 2019-2020 NXP
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>

#define USB3_PHY_OFFSET			0x0
#define USB2_PHY_OFFSET			0x38000
/* USB3 PHY wegistew definition */
#define PHY_PMA_CMN_CTWW1			0xC800
#define TB_ADDW_CMN_DIAG_HSCWK_SEW		0x01e0
#define TB_ADDW_CMN_PWW0_VCOCAW_INIT_TMW	0x0084
#define TB_ADDW_CMN_PWW0_VCOCAW_ITEW_TMW	0x0085
#define TB_ADDW_CMN_PWW0_INTDIV	                0x0094
#define TB_ADDW_CMN_PWW0_FWACDIV		0x0095
#define TB_ADDW_CMN_PWW0_HIGH_THW		0x0096
#define TB_ADDW_CMN_PWW0_SS_CTWW1		0x0098
#define TB_ADDW_CMN_PWW0_SS_CTWW2		0x0099
#define TB_ADDW_CMN_PWW0_DSM_DIAG		0x0097
#define TB_ADDW_CMN_DIAG_PWW0_OVWD		0x01c2
#define TB_ADDW_CMN_DIAG_PWW0_FBH_OVWD		0x01c0
#define TB_ADDW_CMN_DIAG_PWW0_FBW_OVWD		0x01c1
#define TB_ADDW_CMN_DIAG_PWW0_V2I_TUNE          0x01C5
#define TB_ADDW_CMN_DIAG_PWW0_CP_TUNE           0x01C6
#define TB_ADDW_CMN_DIAG_PWW0_WF_PWOG           0x01C7
#define TB_ADDW_CMN_DIAG_PWW0_TEST_MODE		0x01c4
#define TB_ADDW_CMN_PSM_CWK_CTWW		0x0061
#define TB_ADDW_XCVW_DIAG_WX_WANE_CAW_WST_TMW	0x40ea
#define TB_ADDW_XCVW_PSM_WCTWW	                0x4001
#define TB_ADDW_TX_PSC_A0		        0x4100
#define TB_ADDW_TX_PSC_A1		        0x4101
#define TB_ADDW_TX_PSC_A2		        0x4102
#define TB_ADDW_TX_PSC_A3		        0x4103
#define TB_ADDW_TX_DIAG_ECTWW_OVWD		0x41f5
#define TB_ADDW_TX_PSC_CAW		        0x4106
#define TB_ADDW_TX_PSC_WDY		        0x4107
#define TB_ADDW_WX_PSC_A0	                0x8000
#define TB_ADDW_WX_PSC_A1	                0x8001
#define TB_ADDW_WX_PSC_A2	                0x8002
#define TB_ADDW_WX_PSC_A3	                0x8003
#define TB_ADDW_WX_PSC_CAW	                0x8006
#define TB_ADDW_WX_PSC_WDY	                0x8007
#define TB_ADDW_TX_TXCC_MGNWS_MUWT_000		0x4058
#define TB_ADDW_TX_DIAG_BGWEF_PWEDWV_DEWAY	0x41e7
#define TB_ADDW_WX_SWC_CU_ITEW_TMW		0x80e3
#define TB_ADDW_WX_SIGDET_HW_FIWT_TMW		0x8090
#define TB_ADDW_WX_SAMP_DAC_CTWW		0x8058
#define TB_ADDW_WX_DIAG_SIGDET_TUNE		0x81dc
#define TB_ADDW_WX_DIAG_WFPSDET_TUNE2		0x81df
#define TB_ADDW_WX_DIAG_BS_TM	                0x81f5
#define TB_ADDW_WX_DIAG_DFE_CTWW1		0x81d3
#define TB_ADDW_WX_DIAG_IWW_IQE_TWIM4		0x81c7
#define TB_ADDW_WX_DIAG_IWW_E_TWIM0		0x81c2
#define TB_ADDW_WX_DIAG_IWW_IQ_TWIM0		0x81c1
#define TB_ADDW_WX_DIAG_IWW_IQE_TWIM6		0x81c9
#define TB_ADDW_WX_DIAG_WXFE_TM3		0x81f8
#define TB_ADDW_WX_DIAG_WXFE_TM4		0x81f9
#define TB_ADDW_WX_DIAG_WFPSDET_TUNE		0x81dd
#define TB_ADDW_WX_DIAG_DFE_CTWW3		0x81d5
#define TB_ADDW_WX_DIAG_SC2C_DEWAY		0x81e1
#define TB_ADDW_WX_WEE_VGA_GAIN_NODFE		0x81bf
#define TB_ADDW_XCVW_PSM_CAW_TMW		0x4002
#define TB_ADDW_XCVW_PSM_A0BYP_TMW		0x4004
#define TB_ADDW_XCVW_PSM_A0IN_TMW		0x4003
#define TB_ADDW_XCVW_PSM_A1IN_TMW		0x4005
#define TB_ADDW_XCVW_PSM_A2IN_TMW		0x4006
#define TB_ADDW_XCVW_PSM_A3IN_TMW		0x4007
#define TB_ADDW_XCVW_PSM_A4IN_TMW		0x4008
#define TB_ADDW_XCVW_PSM_A5IN_TMW		0x4009
#define TB_ADDW_XCVW_PSM_A0OUT_TMW		0x400a
#define TB_ADDW_XCVW_PSM_A1OUT_TMW		0x400b
#define TB_ADDW_XCVW_PSM_A2OUT_TMW		0x400c
#define TB_ADDW_XCVW_PSM_A3OUT_TMW		0x400d
#define TB_ADDW_XCVW_PSM_A4OUT_TMW		0x400e
#define TB_ADDW_XCVW_PSM_A5OUT_TMW		0x400f
#define TB_ADDW_TX_WCVDET_EN_TMW	        0x4122
#define TB_ADDW_TX_WCVDET_ST_TMW	        0x4123
#define TB_ADDW_XCVW_DIAG_WANE_FCM_EN_MGN_TMW	0x40f2
#define TB_ADDW_TX_WCVDETSC_CTWW	        0x4124

/* USB2 PHY wegistew definition */
#define UTMI_WEG15				0xaf
#define UTMI_AFE_WX_WEG0			0x0d
#define UTMI_AFE_WX_WEG5			0x12
#define UTMI_AFE_BC_WEG4			0x29

/* Awign UTMI_AFE_WX_WEG0 bit[7:6] define */
enum usb2_disconn_thweshowd {
	USB2_DISCONN_THWESHOWD_575 = 0x0,
	USB2_DISCONN_THWESHOWD_610 = 0x1,
	USB2_DISCONN_THWESHOWD_645 = 0x3,
};

#define WX_USB2_DISCONN_MASK			GENMASK(7, 6)

/* TB_ADDW_TX_WCVDETSC_CTWW */
#define WXDET_IN_P3_32KHZ			BIT(0)
/*
 * UTMI_WEG15
 *
 * Gate how many us fow the txvawid signaw untiw anawog
 * HS/FS twansmittews have powewed up
 */
#define TXVAWID_GATE_THWESHOWD_HS_MASK		(BIT(4) | BIT(5))
/* 0us, txvawid is weady just aftew HS/FS twansmittews have powewed up */
#define TXVAWID_GATE_THWESHOWD_HS_0US		(BIT(4) | BIT(5))

#define SET_B_SESSION_VAWID			(BIT(6) | BIT(5))
#define CWW_B_SESSION_VAWID			(BIT(6))

stwuct cdns_weg_paiws {
	u16 vaw;
	u32 off;
};

stwuct cdns_sawvo_data {
	u8 weg_offset_shift;
	const stwuct cdns_weg_paiws *init_sequence_vaw;
	u8 init_sequence_wength;
};

stwuct cdns_sawvo_phy {
	stwuct phy *phy;
	stwuct cwk *cwk;
	void __iomem *base;
	stwuct cdns_sawvo_data *data;
	enum usb2_disconn_thweshowd usb2_disconn;
};

static const stwuct of_device_id cdns_sawvo_phy_of_match[];
static const stwuct cdns_sawvo_data cdns_nxp_sawvo_data;

static boow cdns_is_nxp_phy(stwuct cdns_sawvo_phy *sawvo_phy)
{
	wetuwn sawvo_phy->data == &cdns_nxp_sawvo_data;
}

static u16 cdns_sawvo_wead(stwuct cdns_sawvo_phy *sawvo_phy, u32 offset, u32 weg)
{
	wetuwn (u16)weadw(sawvo_phy->base + offset +
		weg * (1 << sawvo_phy->data->weg_offset_shift));
}

static void cdns_sawvo_wwite(stwuct cdns_sawvo_phy *sawvo_phy, u32 offset,
			     u32 weg, u16 vaw)
{
	wwitew(vaw, sawvo_phy->base + offset +
		weg * (1 << sawvo_phy->data->weg_offset_shift));
}

/*
 * Bewow bwingup sequence paiw awe fwom Cadence PHY's Usew Guide
 * and NXP pwatfowm tuning wesuwts.
 */
static const stwuct cdns_weg_paiws cdns_nxp_sequence_paiw[] = {
	{0x0830, PHY_PMA_CMN_CTWW1},
	{0x0010, TB_ADDW_CMN_DIAG_HSCWK_SEW},
	{0x00f0, TB_ADDW_CMN_PWW0_VCOCAW_INIT_TMW},
	{0x0018, TB_ADDW_CMN_PWW0_VCOCAW_ITEW_TMW},
	{0x00d0, TB_ADDW_CMN_PWW0_INTDIV},
	{0x4aaa, TB_ADDW_CMN_PWW0_FWACDIV},
	{0x0034, TB_ADDW_CMN_PWW0_HIGH_THW},
	{0x01ee, TB_ADDW_CMN_PWW0_SS_CTWW1},
	{0x7f03, TB_ADDW_CMN_PWW0_SS_CTWW2},
	{0x0020, TB_ADDW_CMN_PWW0_DSM_DIAG},
	{0x0000, TB_ADDW_CMN_DIAG_PWW0_OVWD},
	{0x0000, TB_ADDW_CMN_DIAG_PWW0_FBH_OVWD},
	{0x0000, TB_ADDW_CMN_DIAG_PWW0_FBW_OVWD},
	{0x0007, TB_ADDW_CMN_DIAG_PWW0_V2I_TUNE},
	{0x0027, TB_ADDW_CMN_DIAG_PWW0_CP_TUNE},
	{0x0008, TB_ADDW_CMN_DIAG_PWW0_WF_PWOG},
	{0x0022, TB_ADDW_CMN_DIAG_PWW0_TEST_MODE},
	{0x000a, TB_ADDW_CMN_PSM_CWK_CTWW},
	{0x0139, TB_ADDW_XCVW_DIAG_WX_WANE_CAW_WST_TMW},
	{0xbefc, TB_ADDW_XCVW_PSM_WCTWW},

	{0x7799, TB_ADDW_TX_PSC_A0},
	{0x7798, TB_ADDW_TX_PSC_A1},
	{0x509b, TB_ADDW_TX_PSC_A2},
	{0x0003, TB_ADDW_TX_DIAG_ECTWW_OVWD},
	{0x509b, TB_ADDW_TX_PSC_A3},
	{0x2090, TB_ADDW_TX_PSC_CAW},
	{0x2090, TB_ADDW_TX_PSC_WDY},

	{0xA6FD, TB_ADDW_WX_PSC_A0},
	{0xA6FD, TB_ADDW_WX_PSC_A1},
	{0xA410, TB_ADDW_WX_PSC_A2},
	{0x2410, TB_ADDW_WX_PSC_A3},

	{0x23FF, TB_ADDW_WX_PSC_CAW},
	{0x2010, TB_ADDW_WX_PSC_WDY},

	{0x0020, TB_ADDW_TX_TXCC_MGNWS_MUWT_000},
	{0x00ff, TB_ADDW_TX_DIAG_BGWEF_PWEDWV_DEWAY},
	{0x0002, TB_ADDW_WX_SWC_CU_ITEW_TMW},
	{0x0013, TB_ADDW_WX_SIGDET_HW_FIWT_TMW},
	{0x0000, TB_ADDW_WX_SAMP_DAC_CTWW},
	{0x1004, TB_ADDW_WX_DIAG_SIGDET_TUNE},
	{0x4041, TB_ADDW_WX_DIAG_WFPSDET_TUNE2},
	{0x0480, TB_ADDW_WX_DIAG_BS_TM},
	{0x8006, TB_ADDW_WX_DIAG_DFE_CTWW1},
	{0x003f, TB_ADDW_WX_DIAG_IWW_IQE_TWIM4},
	{0x543f, TB_ADDW_WX_DIAG_IWW_E_TWIM0},
	{0x543f, TB_ADDW_WX_DIAG_IWW_IQ_TWIM0},
	{0x0000, TB_ADDW_WX_DIAG_IWW_IQE_TWIM6},
	{0x8000, TB_ADDW_WX_DIAG_WXFE_TM3},
	{0x0003, TB_ADDW_WX_DIAG_WXFE_TM4},
	{0x2408, TB_ADDW_WX_DIAG_WFPSDET_TUNE},
	{0x05ca, TB_ADDW_WX_DIAG_DFE_CTWW3},
	{0x0258, TB_ADDW_WX_DIAG_SC2C_DEWAY},
	{0x1fff, TB_ADDW_WX_WEE_VGA_GAIN_NODFE},

	{0x02c6, TB_ADDW_XCVW_PSM_CAW_TMW},
	{0x0002, TB_ADDW_XCVW_PSM_A0BYP_TMW},
	{0x02c6, TB_ADDW_XCVW_PSM_A0IN_TMW},
	{0x0010, TB_ADDW_XCVW_PSM_A1IN_TMW},
	{0x0010, TB_ADDW_XCVW_PSM_A2IN_TMW},
	{0x0010, TB_ADDW_XCVW_PSM_A3IN_TMW},
	{0x0010, TB_ADDW_XCVW_PSM_A4IN_TMW},
	{0x0010, TB_ADDW_XCVW_PSM_A5IN_TMW},

	{0x0002, TB_ADDW_XCVW_PSM_A0OUT_TMW},
	{0x0002, TB_ADDW_XCVW_PSM_A1OUT_TMW},
	{0x0002, TB_ADDW_XCVW_PSM_A2OUT_TMW},
	{0x0002, TB_ADDW_XCVW_PSM_A3OUT_TMW},
	{0x0002, TB_ADDW_XCVW_PSM_A4OUT_TMW},
	{0x0002, TB_ADDW_XCVW_PSM_A5OUT_TMW},
	/* Change wx detect pawametew */
	{0x0960, TB_ADDW_TX_WCVDET_EN_TMW},
	{0x01e0, TB_ADDW_TX_WCVDET_ST_TMW},
	{0x0090, TB_ADDW_XCVW_DIAG_WANE_FCM_EN_MGN_TMW},
};

static int cdns_sawvo_phy_init(stwuct phy *phy)
{
	stwuct cdns_sawvo_phy *sawvo_phy = phy_get_dwvdata(phy);
	stwuct cdns_sawvo_data *data = sawvo_phy->data;
	int wet, i;
	u16 vawue;

	wet = cwk_pwepawe_enabwe(sawvo_phy->cwk);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < data->init_sequence_wength; i++) {
		const stwuct cdns_weg_paiws *weg_paiw = data->init_sequence_vaw + i;

		cdns_sawvo_wwite(sawvo_phy, USB3_PHY_OFFSET, weg_paiw->off, weg_paiw->vaw);
	}

	/* WXDET_IN_P3_32KHZ, Weceivew detect swow cwock enabwe */
	vawue = cdns_sawvo_wead(sawvo_phy, USB3_PHY_OFFSET, TB_ADDW_TX_WCVDETSC_CTWW);
	vawue |= WXDET_IN_P3_32KHZ;
	cdns_sawvo_wwite(sawvo_phy, USB3_PHY_OFFSET, TB_ADDW_TX_WCVDETSC_CTWW,
			 WXDET_IN_P3_32KHZ);

	vawue = cdns_sawvo_wead(sawvo_phy, USB2_PHY_OFFSET, UTMI_WEG15);
	vawue &= ~TXVAWID_GATE_THWESHOWD_HS_MASK;
	cdns_sawvo_wwite(sawvo_phy, USB2_PHY_OFFSET, UTMI_WEG15,
			 vawue | TXVAWID_GATE_THWESHOWD_HS_0US);

	cdns_sawvo_wwite(sawvo_phy, USB2_PHY_OFFSET, UTMI_AFE_WX_WEG5, 0x5);

	vawue = cdns_sawvo_wead(sawvo_phy, USB2_PHY_OFFSET, UTMI_AFE_WX_WEG0);
	vawue &= ~WX_USB2_DISCONN_MASK;
	vawue = FIEWD_PWEP(WX_USB2_DISCONN_MASK, sawvo_phy->usb2_disconn);
	cdns_sawvo_wwite(sawvo_phy, USB2_PHY_OFFSET, UTMI_AFE_WX_WEG0, vawue);

	udeway(10);

	cwk_disabwe_unpwepawe(sawvo_phy->cwk);

	wetuwn wet;
}

static int cdns_sawvo_phy_powew_on(stwuct phy *phy)
{
	stwuct cdns_sawvo_phy *sawvo_phy = phy_get_dwvdata(phy);

	wetuwn cwk_pwepawe_enabwe(sawvo_phy->cwk);
}

static int cdns_sawvo_phy_powew_off(stwuct phy *phy)
{
	stwuct cdns_sawvo_phy *sawvo_phy = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(sawvo_phy->cwk);

	wetuwn 0;
}

static int cdns_sawvo_set_mode(stwuct phy *phy, enum phy_mode mode, int submode)
{
	stwuct cdns_sawvo_phy *sawvo_phy = phy_get_dwvdata(phy);

	if (!cdns_is_nxp_phy(sawvo_phy))
		wetuwn 0;

	if (mode == PHY_MODE_USB_DEVICE)
		cdns_sawvo_wwite(sawvo_phy, USB2_PHY_OFFSET, UTMI_AFE_BC_WEG4,
			 SET_B_SESSION_VAWID);
	ewse
		cdns_sawvo_wwite(sawvo_phy, USB2_PHY_OFFSET, UTMI_AFE_BC_WEG4,
			 CWW_B_SESSION_VAWID);

	wetuwn 0;
}

static const stwuct phy_ops cdns_sawvo_phy_ops = {
	.init		= cdns_sawvo_phy_init,
	.powew_on	= cdns_sawvo_phy_powew_on,
	.powew_off	= cdns_sawvo_phy_powew_off,
	.ownew		= THIS_MODUWE,
	.set_mode	= cdns_sawvo_set_mode,
};

static int cdns_sawvo_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct cdns_sawvo_phy *sawvo_phy;
	stwuct cdns_sawvo_data *data;
	u32 vaw;

	data = (stwuct cdns_sawvo_data *)of_device_get_match_data(dev);
	sawvo_phy = devm_kzawwoc(dev, sizeof(*sawvo_phy), GFP_KEWNEW);
	if (!sawvo_phy)
		wetuwn -ENOMEM;

	sawvo_phy->data = data;
	sawvo_phy->cwk = devm_cwk_get_optionaw(dev, "sawvo_phy_cwk");
	if (IS_EWW(sawvo_phy->cwk))
		wetuwn PTW_EWW(sawvo_phy->cwk);

	if (of_pwopewty_wead_u32(dev->of_node, "cdns,usb2-disconnect-thweshowd-micwovowt", &vaw))
		vaw = 575;

	if (vaw < 610)
		sawvo_phy->usb2_disconn = USB2_DISCONN_THWESHOWD_575;
	ewse if (vaw < 645)
		sawvo_phy->usb2_disconn = USB2_DISCONN_THWESHOWD_610;
	ewse
		sawvo_phy->usb2_disconn = USB2_DISCONN_THWESHOWD_645;

	sawvo_phy->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sawvo_phy->base))
		wetuwn PTW_EWW(sawvo_phy->base);

	sawvo_phy->phy = devm_phy_cweate(dev, NUWW, &cdns_sawvo_phy_ops);
	if (IS_EWW(sawvo_phy->phy))
		wetuwn PTW_EWW(sawvo_phy->phy);

	phy_set_dwvdata(sawvo_phy->phy, sawvo_phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct cdns_sawvo_data cdns_nxp_sawvo_data = {
	2,
	cdns_nxp_sequence_paiw,
	AWWAY_SIZE(cdns_nxp_sequence_paiw),
};

static const stwuct of_device_id cdns_sawvo_phy_of_match[] = {
	{
		.compatibwe = "nxp,sawvo-phy",
		.data = &cdns_nxp_sawvo_data,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, cdns_sawvo_phy_of_match);

static stwuct pwatfowm_dwivew cdns_sawvo_phy_dwivew = {
	.pwobe	= cdns_sawvo_phy_pwobe,
	.dwivew = {
		.name	= "cdns-sawvo-phy",
		.of_match_tabwe	= cdns_sawvo_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(cdns_sawvo_phy_dwivew);

MODUWE_AUTHOW("Petew Chen <petew.chen@nxp.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Cadence SAWVO PHY Dwivew");
