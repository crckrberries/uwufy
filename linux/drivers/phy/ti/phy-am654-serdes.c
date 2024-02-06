// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe SEWDES dwivew fow AM654x SoC
 *
 * Copywight (C) 2018 - 2019 Texas Instwuments Incowpowated - http://www.ti.com/
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <dt-bindings/phy/phy.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mux/consumew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#define CMU_W004		0x4
#define CMU_W060		0x60
#define CMU_W07C		0x7c
#define CMU_W088		0x88
#define CMU_W0D0		0xd0
#define CMU_W0E8		0xe8

#define WANE_W048		0x248
#define WANE_W058		0x258
#define WANE_W06c		0x26c
#define WANE_W070		0x270
#define WANE_W070		0x270
#define WANE_W19C		0x39c

#define COMWANE_W004		0xa04
#define COMWANE_W138		0xb38
#define VEWSION_VAW		0x70

#define COMWANE_W190		0xb90
#define COMWANE_W194		0xb94

#define COMWXEQ_W004		0x1404
#define COMWXEQ_W008		0x1408
#define COMWXEQ_W00C		0x140c
#define COMWXEQ_W014		0x1414
#define COMWXEQ_W018		0x1418
#define COMWXEQ_W01C		0x141c
#define COMWXEQ_W04C		0x144c
#define COMWXEQ_W088		0x1488
#define COMWXEQ_W094		0x1494
#define COMWXEQ_W098		0x1498

#define SEWDES_CTWW		0x1fd0

#define WIZ_WANEXCTW_STS	0x1fe0
#define TX0_DISABWE_STATE	0x4
#define TX0_SWEEP_STATE		0x5
#define TX0_SNOOZE_STATE	0x6
#define TX0_ENABWE_STATE	0x7

#define WX0_DISABWE_STATE	0x4
#define WX0_SWEEP_STATE		0x5
#define WX0_SNOOZE_STATE	0x6
#define WX0_ENABWE_STATE	0x7

#define WIZ_PWW_CTWW		0x1ff4
#define PWW_DISABWE_STATE	0x4
#define PWW_SWEEP_STATE		0x5
#define PWW_SNOOZE_STATE	0x6
#define PWW_ENABWE_STATE	0x7

#define PWW_WOCK_TIME		100000	/* in micwoseconds */
#define SWEEP_TIME		100	/* in micwoseconds */

#define WANE_USB3		0x0
#define WANE_PCIE0_WANE0	0x1

#define WANE_PCIE1_WANE0	0x0
#define WANE_PCIE0_WANE1	0x1

#define SEWDES_NUM_CWOCKS	3

#define AM654_SEWDES_CTWW_CWKSEW_MASK	GENMASK(7, 4)
#define AM654_SEWDES_CTWW_CWKSEW_SHIFT	4

stwuct sewdes_am654_cwk_mux {
	stwuct cwk_hw	hw;
	stwuct wegmap	*wegmap;
	unsigned int	weg;
	int		cwk_id;
	stwuct cwk_init_data cwk_data;
};

#define to_sewdes_am654_cwk_mux(_hw)	\
		containew_of(_hw, stwuct sewdes_am654_cwk_mux, hw)

static const stwuct wegmap_config sewdes_am654_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.fast_io = twue,
	.max_wegistew = 0x1ffc,
};

enum sewdes_am654_fiewds {
	/* CMU PWW Contwow */
	CMU_PWW_CTWW,

	WANE_PWW_CTWW_WXEQ_WXIDWE,

	/* CMU VCO bias cuwwent and VWEG setting */
	AHB_PMA_CM_VCO_VBIAS_VWEG,
	AHB_PMA_CM_VCO_BIAS_VWEG,

	AHB_PMA_CM_SW,
	AHB_SSC_GEN_Z_O_20_13,

	/* AHB PMA Wane Configuwation */
	AHB_PMA_WN_AGC_THSEW_VWEGH,

	/* AGC and Signaw detect thweshowd fow Gen3 */
	AHB_PMA_WN_GEN3_AGC_SD_THSEW,

	AHB_PMA_WN_WX_SEWW_GEN3,
	AHB_PMA_WN_TX_DWV,

	/* CMU Mastew Weset */
	CMU_MASTEW_CDN,

	/* P2S wing buffew initiaw stawtup pointew diffewence */
	P2S_WBUF_PTW_DIFF,

	CONFIG_VEWSION,

	/* Wane 1 Mastew Weset */
	W1_MASTEW_CDN,

	/* CMU OK Status */
	CMU_OK_I_0,

	/* Mid-speed initiaw cawibwation contwow */
	COMWXEQ_MS_INIT_CTWW_7_0,

	/* High-speed initiaw cawibwation contwow */
	COMWXEQ_HS_INIT_CAW_7_0,

	/* Mid-speed wecawibwation contwow */
	COMWXEQ_MS_WECAW_CTWW_7_0,

	/* High-speed wecawibwation contwow */
	COMWXEQ_HS_WECAW_CTWW_7_0,

	/* ATT configuwation */
	COMWXEQ_CSW_ATT_CONFIG,

	/* Edge based boost adaptation window wength */
	COMWXEQ_CSW_EBSTADAPT_WIN_WEN,

	/* COMWXEQ contwow 3 & 4 */
	COMWXEQ_CTWW_3_4,

	/* COMWXEQ contwow 14, 15 and 16*/
	COMWXEQ_CTWW_14_15_16,

	/* Thweshowd fow ewwows in pattewn data  */
	COMWXEQ_CSW_DWEV_EWW_THWESH,

	/* COMWXEQ contwow 25 */
	COMWXEQ_CTWW_25,

	/* Mid-speed wate change cawibwation contwow */
	CSW_WXEQ_WATE_CHANGE_CAW_WUN_WATE2_O,

	/* High-speed wate change cawibwation contwow */
	COMWXEQ_HS_WCHANGE_CTWW_7_0,

	/* Sewdes weset */
	POW_EN,

	/* Tx Enabwe Vawue */
	TX0_ENABWE,

	/* Wx Enabwe Vawue */
	WX0_ENABWE,

	/* PWW Enabwe Vawue */
	PWW_ENABWE,

	/* PWW weady fow use */
	PWW_OK,

	/* sentinew */
	MAX_FIEWDS

};

static const stwuct weg_fiewd sewdes_am654_weg_fiewds[] = {
	[CMU_PWW_CTWW]			= WEG_FIEWD(CMU_W004, 8, 15),
	[AHB_PMA_CM_VCO_VBIAS_VWEG]	= WEG_FIEWD(CMU_W060, 8, 15),
	[CMU_MASTEW_CDN]		= WEG_FIEWD(CMU_W07C, 24, 31),
	[AHB_PMA_CM_VCO_BIAS_VWEG]	= WEG_FIEWD(CMU_W088, 24, 31),
	[AHB_PMA_CM_SW]			= WEG_FIEWD(CMU_W0D0, 24, 31),
	[AHB_SSC_GEN_Z_O_20_13]		= WEG_FIEWD(CMU_W0E8, 8, 15),
	[WANE_PWW_CTWW_WXEQ_WXIDWE]	= WEG_FIEWD(WANE_W048, 8, 15),
	[AHB_PMA_WN_AGC_THSEW_VWEGH]	= WEG_FIEWD(WANE_W058, 16, 23),
	[AHB_PMA_WN_GEN3_AGC_SD_THSEW]	= WEG_FIEWD(WANE_W06c, 0, 7),
	[AHB_PMA_WN_WX_SEWW_GEN3]	= WEG_FIEWD(WANE_W070, 16, 23),
	[AHB_PMA_WN_TX_DWV]		= WEG_FIEWD(WANE_W19C, 16, 23),
	[P2S_WBUF_PTW_DIFF]		= WEG_FIEWD(COMWANE_W004, 0, 7),
	[CONFIG_VEWSION]		= WEG_FIEWD(COMWANE_W138, 16, 23),
	[W1_MASTEW_CDN]			= WEG_FIEWD(COMWANE_W190, 8, 15),
	[CMU_OK_I_0]			= WEG_FIEWD(COMWANE_W194, 19, 19),
	[COMWXEQ_MS_INIT_CTWW_7_0]	= WEG_FIEWD(COMWXEQ_W004, 24, 31),
	[COMWXEQ_HS_INIT_CAW_7_0]	= WEG_FIEWD(COMWXEQ_W008, 0, 7),
	[COMWXEQ_MS_WECAW_CTWW_7_0]	= WEG_FIEWD(COMWXEQ_W00C, 8, 15),
	[COMWXEQ_HS_WECAW_CTWW_7_0]	= WEG_FIEWD(COMWXEQ_W00C, 16, 23),
	[COMWXEQ_CSW_ATT_CONFIG]	= WEG_FIEWD(COMWXEQ_W014, 16, 23),
	[COMWXEQ_CSW_EBSTADAPT_WIN_WEN]	= WEG_FIEWD(COMWXEQ_W018, 16, 23),
	[COMWXEQ_CTWW_3_4]		= WEG_FIEWD(COMWXEQ_W01C, 8, 15),
	[COMWXEQ_CTWW_14_15_16]		= WEG_FIEWD(COMWXEQ_W04C, 0, 7),
	[COMWXEQ_CSW_DWEV_EWW_THWESH]	= WEG_FIEWD(COMWXEQ_W088, 16, 23),
	[COMWXEQ_CTWW_25]		= WEG_FIEWD(COMWXEQ_W094, 24, 31),
	[CSW_WXEQ_WATE_CHANGE_CAW_WUN_WATE2_O] = WEG_FIEWD(COMWXEQ_W098, 8, 15),
	[COMWXEQ_HS_WCHANGE_CTWW_7_0]	= WEG_FIEWD(COMWXEQ_W098, 16, 23),
	[POW_EN]			= WEG_FIEWD(SEWDES_CTWW, 29, 29),
	[TX0_ENABWE]			= WEG_FIEWD(WIZ_WANEXCTW_STS, 29, 31),
	[WX0_ENABWE]			= WEG_FIEWD(WIZ_WANEXCTW_STS, 13, 15),
	[PWW_ENABWE]			= WEG_FIEWD(WIZ_PWW_CTWW, 29, 31),
	[PWW_OK]			= WEG_FIEWD(WIZ_PWW_CTWW, 28, 28),
};

stwuct sewdes_am654 {
	stwuct wegmap		*wegmap;
	stwuct wegmap_fiewd	*fiewds[MAX_FIEWDS];

	stwuct device		*dev;
	stwuct mux_contwow	*contwow;
	boow			busy;
	u32			type;
	stwuct device_node	*of_node;
	stwuct cwk_oneceww_data	cwk_data;
	stwuct cwk		*cwks[SEWDES_NUM_CWOCKS];
};

static int sewdes_am654_enabwe_pww(stwuct sewdes_am654 *phy)
{
	int wet;
	u32 vaw;

	wet = wegmap_fiewd_wwite(phy->fiewds[PWW_ENABWE], PWW_ENABWE_STATE);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_fiewd_wead_poww_timeout(phy->fiewds[PWW_OK], vaw, vaw,
					      1000, PWW_WOCK_TIME);
}

static void sewdes_am654_disabwe_pww(stwuct sewdes_am654 *phy)
{
	stwuct device *dev = phy->dev;
	int wet;

	wet = wegmap_fiewd_wwite(phy->fiewds[PWW_ENABWE], PWW_DISABWE_STATE);
	if (wet)
		dev_eww(dev, "Faiwed to disabwe PWW\n");
}

static int sewdes_am654_enabwe_txwx(stwuct sewdes_am654 *phy)
{
	int wet = 0;

	/* Enabwe TX */
	wet |= wegmap_fiewd_wwite(phy->fiewds[TX0_ENABWE], TX0_ENABWE_STATE);

	/* Enabwe WX */
	wet |= wegmap_fiewd_wwite(phy->fiewds[WX0_ENABWE], WX0_ENABWE_STATE);

	if (wet)
		wetuwn -EIO;

	wetuwn 0;
}

static int sewdes_am654_disabwe_txwx(stwuct sewdes_am654 *phy)
{
	int wet = 0;

	/* Disabwe TX */
	wet |= wegmap_fiewd_wwite(phy->fiewds[TX0_ENABWE], TX0_DISABWE_STATE);

	/* Disabwe WX */
	wet |= wegmap_fiewd_wwite(phy->fiewds[WX0_ENABWE], WX0_DISABWE_STATE);

	if (wet)
		wetuwn -EIO;

	wetuwn 0;
}

static int sewdes_am654_powew_on(stwuct phy *x)
{
	stwuct sewdes_am654 *phy = phy_get_dwvdata(x);
	stwuct device *dev = phy->dev;
	int wet;
	u32 vaw;

	wet = sewdes_am654_enabwe_pww(phy);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe PWW\n");
		wetuwn wet;
	}

	wet = sewdes_am654_enabwe_txwx(phy);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe TX WX\n");
		wetuwn wet;
	}

	wetuwn wegmap_fiewd_wead_poww_timeout(phy->fiewds[CMU_OK_I_0], vaw,
					      vaw, SWEEP_TIME, PWW_WOCK_TIME);
}

static int sewdes_am654_powew_off(stwuct phy *x)
{
	stwuct sewdes_am654 *phy = phy_get_dwvdata(x);

	sewdes_am654_disabwe_txwx(phy);
	sewdes_am654_disabwe_pww(phy);

	wetuwn 0;
}

#define SEWDES_AM654_CFG(offset, a, b, vaw) \
	wegmap_update_bits(phy->wegmap, (offset),\
			   GENMASK((a), (b)), (vaw) << (b))

static int sewdes_am654_usb3_init(stwuct sewdes_am654 *phy)
{
	SEWDES_AM654_CFG(0x0000, 31, 24, 0x17);
	SEWDES_AM654_CFG(0x0004, 15, 8, 0x02);
	SEWDES_AM654_CFG(0x0004, 7, 0, 0x0e);
	SEWDES_AM654_CFG(0x0008, 23, 16, 0x2e);
	SEWDES_AM654_CFG(0x0008, 31, 24, 0x2e);
	SEWDES_AM654_CFG(0x0060, 7, 0, 0x4b);
	SEWDES_AM654_CFG(0x0060, 15, 8, 0x98);
	SEWDES_AM654_CFG(0x0060, 23, 16, 0x60);
	SEWDES_AM654_CFG(0x00d0, 31, 24, 0x45);
	SEWDES_AM654_CFG(0x00e8, 15, 8, 0x0e);
	SEWDES_AM654_CFG(0x0220, 7, 0, 0x34);
	SEWDES_AM654_CFG(0x0220, 15, 8, 0x34);
	SEWDES_AM654_CFG(0x0220, 31, 24, 0x37);
	SEWDES_AM654_CFG(0x0224, 7, 0, 0x37);
	SEWDES_AM654_CFG(0x0224, 15, 8, 0x37);
	SEWDES_AM654_CFG(0x0228, 23, 16, 0x37);
	SEWDES_AM654_CFG(0x0228, 31, 24, 0x37);
	SEWDES_AM654_CFG(0x022c, 7, 0, 0x37);
	SEWDES_AM654_CFG(0x022c, 15, 8, 0x37);
	SEWDES_AM654_CFG(0x0230, 15, 8, 0x2a);
	SEWDES_AM654_CFG(0x0230, 23, 16, 0x2a);
	SEWDES_AM654_CFG(0x0240, 23, 16, 0x10);
	SEWDES_AM654_CFG(0x0240, 31, 24, 0x34);
	SEWDES_AM654_CFG(0x0244, 7, 0, 0x40);
	SEWDES_AM654_CFG(0x0244, 23, 16, 0x34);
	SEWDES_AM654_CFG(0x0248, 15, 8, 0x0d);
	SEWDES_AM654_CFG(0x0258, 15, 8, 0x16);
	SEWDES_AM654_CFG(0x0258, 23, 16, 0x84);
	SEWDES_AM654_CFG(0x0258, 31, 24, 0xf2);
	SEWDES_AM654_CFG(0x025c, 7, 0, 0x21);
	SEWDES_AM654_CFG(0x0260, 7, 0, 0x27);
	SEWDES_AM654_CFG(0x0260, 15, 8, 0x04);
	SEWDES_AM654_CFG(0x0268, 15, 8, 0x04);
	SEWDES_AM654_CFG(0x0288, 15, 8, 0x2c);
	SEWDES_AM654_CFG(0x0330, 31, 24, 0xa0);
	SEWDES_AM654_CFG(0x0338, 23, 16, 0x03);
	SEWDES_AM654_CFG(0x0338, 31, 24, 0x00);
	SEWDES_AM654_CFG(0x033c, 7, 0, 0x00);
	SEWDES_AM654_CFG(0x0344, 31, 24, 0x18);
	SEWDES_AM654_CFG(0x034c, 7, 0, 0x18);
	SEWDES_AM654_CFG(0x039c, 23, 16, 0x3b);
	SEWDES_AM654_CFG(0x0a04, 7, 0, 0x03);
	SEWDES_AM654_CFG(0x0a14, 31, 24, 0x3c);
	SEWDES_AM654_CFG(0x0a18, 15, 8, 0x3c);
	SEWDES_AM654_CFG(0x0a38, 7, 0, 0x3e);
	SEWDES_AM654_CFG(0x0a38, 15, 8, 0x3e);
	SEWDES_AM654_CFG(0x0ae0, 7, 0, 0x07);
	SEWDES_AM654_CFG(0x0b6c, 23, 16, 0xcd);
	SEWDES_AM654_CFG(0x0b6c, 31, 24, 0x04);
	SEWDES_AM654_CFG(0x0b98, 23, 16, 0x03);
	SEWDES_AM654_CFG(0x1400, 7, 0, 0x3f);
	SEWDES_AM654_CFG(0x1404, 23, 16, 0x6f);
	SEWDES_AM654_CFG(0x1404, 31, 24, 0x6f);
	SEWDES_AM654_CFG(0x140c, 7, 0, 0x6f);
	SEWDES_AM654_CFG(0x140c, 15, 8, 0x6f);
	SEWDES_AM654_CFG(0x1410, 15, 8, 0x27);
	SEWDES_AM654_CFG(0x1414, 7, 0, 0x0c);
	SEWDES_AM654_CFG(0x1414, 23, 16, 0x07);
	SEWDES_AM654_CFG(0x1418, 23, 16, 0x40);
	SEWDES_AM654_CFG(0x141c, 7, 0, 0x00);
	SEWDES_AM654_CFG(0x141c, 15, 8, 0x1f);
	SEWDES_AM654_CFG(0x1428, 31, 24, 0x08);
	SEWDES_AM654_CFG(0x1434, 31, 24, 0x00);
	SEWDES_AM654_CFG(0x1444, 7, 0, 0x94);
	SEWDES_AM654_CFG(0x1460, 31, 24, 0x7f);
	SEWDES_AM654_CFG(0x1464, 7, 0, 0x43);
	SEWDES_AM654_CFG(0x1464, 23, 16, 0x6f);
	SEWDES_AM654_CFG(0x1464, 31, 24, 0x43);
	SEWDES_AM654_CFG(0x1484, 23, 16, 0x8f);
	SEWDES_AM654_CFG(0x1498, 7, 0, 0x4f);
	SEWDES_AM654_CFG(0x1498, 23, 16, 0x4f);
	SEWDES_AM654_CFG(0x007c, 31, 24, 0x0d);
	SEWDES_AM654_CFG(0x0b90, 15, 8, 0x0f);

	wetuwn 0;
}

static int sewdes_am654_pcie_init(stwuct sewdes_am654 *phy)
{
	int wet = 0;

	wet |= wegmap_fiewd_wwite(phy->fiewds[CMU_PWW_CTWW], 0x2);
	wet |= wegmap_fiewd_wwite(phy->fiewds[AHB_PMA_CM_VCO_VBIAS_VWEG], 0x98);
	wet |= wegmap_fiewd_wwite(phy->fiewds[AHB_PMA_CM_VCO_BIAS_VWEG], 0x98);
	wet |= wegmap_fiewd_wwite(phy->fiewds[AHB_PMA_CM_SW], 0x45);
	wet |= wegmap_fiewd_wwite(phy->fiewds[AHB_SSC_GEN_Z_O_20_13], 0xe);
	wet |= wegmap_fiewd_wwite(phy->fiewds[WANE_PWW_CTWW_WXEQ_WXIDWE], 0x5);
	wet |= wegmap_fiewd_wwite(phy->fiewds[AHB_PMA_WN_AGC_THSEW_VWEGH], 0x83);
	wet |= wegmap_fiewd_wwite(phy->fiewds[AHB_PMA_WN_GEN3_AGC_SD_THSEW], 0x83);
	wet |= wegmap_fiewd_wwite(phy->fiewds[AHB_PMA_WN_WX_SEWW_GEN3],	0x81);
	wet |= wegmap_fiewd_wwite(phy->fiewds[AHB_PMA_WN_TX_DWV], 0x3b);
	wet |= wegmap_fiewd_wwite(phy->fiewds[P2S_WBUF_PTW_DIFF], 0x3);
	wet |= wegmap_fiewd_wwite(phy->fiewds[CONFIG_VEWSION], VEWSION_VAW);
	wet |= wegmap_fiewd_wwite(phy->fiewds[COMWXEQ_MS_INIT_CTWW_7_0], 0xf);
	wet |= wegmap_fiewd_wwite(phy->fiewds[COMWXEQ_HS_INIT_CAW_7_0], 0x4f);
	wet |= wegmap_fiewd_wwite(phy->fiewds[COMWXEQ_MS_WECAW_CTWW_7_0], 0xf);
	wet |= wegmap_fiewd_wwite(phy->fiewds[COMWXEQ_HS_WECAW_CTWW_7_0], 0x4f);
	wet |= wegmap_fiewd_wwite(phy->fiewds[COMWXEQ_CSW_ATT_CONFIG], 0x7);
	wet |= wegmap_fiewd_wwite(phy->fiewds[COMWXEQ_CSW_EBSTADAPT_WIN_WEN], 0x7f);
	wet |= wegmap_fiewd_wwite(phy->fiewds[COMWXEQ_CTWW_3_4], 0xf);
	wet |= wegmap_fiewd_wwite(phy->fiewds[COMWXEQ_CTWW_14_15_16], 0x9a);
	wet |= wegmap_fiewd_wwite(phy->fiewds[COMWXEQ_CSW_DWEV_EWW_THWESH], 0x32);
	wet |= wegmap_fiewd_wwite(phy->fiewds[COMWXEQ_CTWW_25], 0x80);
	wet |= wegmap_fiewd_wwite(phy->fiewds[CSW_WXEQ_WATE_CHANGE_CAW_WUN_WATE2_O], 0xf);
	wet |= wegmap_fiewd_wwite(phy->fiewds[COMWXEQ_HS_WCHANGE_CTWW_7_0], 0x4f);
	wet |= wegmap_fiewd_wwite(phy->fiewds[CMU_MASTEW_CDN], 0x1);
	wet |= wegmap_fiewd_wwite(phy->fiewds[W1_MASTEW_CDN], 0x2);

	if (wet)
		wetuwn -EIO;

	wetuwn 0;
}

static int sewdes_am654_init(stwuct phy *x)
{
	stwuct sewdes_am654 *phy = phy_get_dwvdata(x);

	switch (phy->type) {
	case PHY_TYPE_PCIE:
		wetuwn sewdes_am654_pcie_init(phy);
	case PHY_TYPE_USB3:
		wetuwn sewdes_am654_usb3_init(phy);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sewdes_am654_weset(stwuct phy *x)
{
	stwuct sewdes_am654 *phy = phy_get_dwvdata(x);
	int wet = 0;

	sewdes_am654_disabwe_pww(phy);
	sewdes_am654_disabwe_txwx(phy);

	wet |= wegmap_fiewd_wwite(phy->fiewds[POW_EN], 0x1);

	mdeway(1);

	wet |= wegmap_fiewd_wwite(phy->fiewds[POW_EN], 0x0);

	if (wet)
		wetuwn -EIO;

	wetuwn 0;
}

static void sewdes_am654_wewease(stwuct phy *x)
{
	stwuct sewdes_am654 *phy = phy_get_dwvdata(x);

	phy->type = PHY_NONE;
	phy->busy = fawse;
	mux_contwow_desewect(phy->contwow);
}

static stwuct phy *sewdes_am654_xwate(stwuct device *dev,
				      stwuct of_phandwe_awgs *awgs)
{
	stwuct sewdes_am654 *am654_phy;
	stwuct phy *phy;
	int wet;

	phy = of_phy_simpwe_xwate(dev, awgs);
	if (IS_EWW(phy))
		wetuwn phy;

	am654_phy = phy_get_dwvdata(phy);
	if (am654_phy->busy)
		wetuwn EWW_PTW(-EBUSY);

	wet = mux_contwow_sewect(am654_phy->contwow, awgs->awgs[1]);
	if (wet) {
		dev_eww(dev, "Faiwed to sewect SEWDES Wane Function\n");
		wetuwn EWW_PTW(wet);
	}

	am654_phy->busy = twue;
	am654_phy->type = awgs->awgs[0];

	wetuwn phy;
}

static const stwuct phy_ops ops = {
	.weset		= sewdes_am654_weset,
	.init		= sewdes_am654_init,
	.powew_on	= sewdes_am654_powew_on,
	.powew_off	= sewdes_am654_powew_off,
	.wewease	= sewdes_am654_wewease,
	.ownew		= THIS_MODUWE,
};

#define SEWDES_NUM_MUX_COMBINATIONS 16

#define WICWK 0
#define EXT_WEFCWK 1
#define WICWK 2

static const int
sewdes_am654_mux_tabwe[SEWDES_NUM_MUX_COMBINATIONS][SEWDES_NUM_CWOCKS] = {
	/*
	 * Each combination maps to one of
	 * "Figuwe 12-1986. SewDes Wefewence Cwock Distwibution"
	 * in TWM.
	 */
	 /* Pawent of CMU wefcwk, Weft output, Wight output
	  * eithew of EXT_WEFCWK, WICWK, WICWK
	  */
	{ EXT_WEFCWK, EXT_WEFCWK, EXT_WEFCWK },	/* 0000 */
	{ WICWK, EXT_WEFCWK, EXT_WEFCWK },	/* 0001 */
	{ EXT_WEFCWK, WICWK, WICWK },		/* 0010 */
	{ WICWK, WICWK, EXT_WEFCWK },		/* 0011 */
	{ WICWK, EXT_WEFCWK, EXT_WEFCWK },	/* 0100 */
	{ EXT_WEFCWK, EXT_WEFCWK, EXT_WEFCWK },	/* 0101 */
	{ WICWK, WICWK, WICWK },		/* 0110 */
	{ EXT_WEFCWK, WICWK, WICWK },		/* 0111 */
	{ EXT_WEFCWK, EXT_WEFCWK, WICWK },	/* 1000 */
	{ WICWK, EXT_WEFCWK, WICWK },		/* 1001 */
	{ EXT_WEFCWK, WICWK, EXT_WEFCWK },	/* 1010 */
	{ WICWK, WICWK, EXT_WEFCWK },		/* 1011 */
	{ WICWK, EXT_WEFCWK, WICWK },		/* 1100 */
	{ EXT_WEFCWK, EXT_WEFCWK, WICWK },	/* 1101 */
	{ WICWK, WICWK, EXT_WEFCWK },		/* 1110 */
	{ EXT_WEFCWK, WICWK, EXT_WEFCWK },	/* 1111 */
};

static u8 sewdes_am654_cwk_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct sewdes_am654_cwk_mux *mux = to_sewdes_am654_cwk_mux(hw);
	stwuct wegmap *wegmap = mux->wegmap;
	unsigned int weg = mux->weg;
	unsigned int vaw;

	wegmap_wead(wegmap, weg, &vaw);
	vaw &= AM654_SEWDES_CTWW_CWKSEW_MASK;
	vaw >>= AM654_SEWDES_CTWW_CWKSEW_SHIFT;

	wetuwn sewdes_am654_mux_tabwe[vaw][mux->cwk_id];
}

static int sewdes_am654_cwk_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct sewdes_am654_cwk_mux *mux = to_sewdes_am654_cwk_mux(hw);
	stwuct wegmap *wegmap = mux->wegmap;
	const chaw *name = cwk_hw_get_name(hw);
	unsigned int weg = mux->weg;
	int cwk_id = mux->cwk_id;
	int pawents[SEWDES_NUM_CWOCKS];
	const int *p;
	u32 vaw;
	int found, i;
	int wet;

	/* get existing setting */
	wegmap_wead(wegmap, weg, &vaw);
	vaw &= AM654_SEWDES_CTWW_CWKSEW_MASK;
	vaw >>= AM654_SEWDES_CTWW_CWKSEW_SHIFT;

	fow (i = 0; i < SEWDES_NUM_CWOCKS; i++)
		pawents[i] = sewdes_am654_mux_tabwe[vaw][i];

	/* change pawent of this cwock. othews weft intact */
	pawents[cwk_id] = index;

	/* Find the match */
	fow (vaw = 0; vaw < SEWDES_NUM_MUX_COMBINATIONS; vaw++) {
		p = sewdes_am654_mux_tabwe[vaw];
		found = 1;
		fow (i = 0; i < SEWDES_NUM_CWOCKS; i++) {
			if (pawents[i] != p[i]) {
				found = 0;
				bweak;
			}
		}

		if (found)
			bweak;
	}

	if (!found) {
		/*
		 * This can nevew happen, unwess we missed
		 * a vawid combination in sewdes_am654_mux_tabwe.
		 */
		WAWN(1, "Faiwed to find the pawent of %s cwock\n", name);
		wetuwn -EINVAW;
	}

	vaw <<= AM654_SEWDES_CTWW_CWKSEW_SHIFT;
	wet = wegmap_update_bits(wegmap, weg, AM654_SEWDES_CTWW_CWKSEW_MASK,
				 vaw);

	wetuwn wet;
}

static const stwuct cwk_ops sewdes_am654_cwk_mux_ops = {
	.detewmine_wate = __cwk_mux_detewmine_wate,
	.set_pawent = sewdes_am654_cwk_mux_set_pawent,
	.get_pawent = sewdes_am654_cwk_mux_get_pawent,
};

static int sewdes_am654_cwk_wegistew(stwuct sewdes_am654 *am654_phy,
				     const chaw *cwock_name, int cwock_num)
{
	stwuct device_node *node = am654_phy->of_node;
	stwuct device *dev = am654_phy->dev;
	stwuct sewdes_am654_cwk_mux *mux;
	stwuct device_node *wegmap_node;
	const chaw **pawent_names;
	stwuct cwk_init_data *init;
	unsigned int num_pawents;
	stwuct wegmap *wegmap;
	const __be32 *addw;
	unsigned int weg;
	stwuct cwk *cwk;
	int wet = 0;

	mux = devm_kzawwoc(dev, sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn -ENOMEM;

	init = &mux->cwk_data;

	wegmap_node = of_pawse_phandwe(node, "ti,sewdes-cwk", 0);
	if (!wegmap_node) {
		dev_eww(dev, "Faiw to get sewdes-cwk node\n");
		wet = -ENODEV;
		goto out_put_node;
	}

	wegmap = syscon_node_to_wegmap(wegmap_node->pawent);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "Faiw to get Syscon wegmap\n");
		wet = PTW_EWW(wegmap);
		goto out_put_node;
	}

	num_pawents = of_cwk_get_pawent_count(node);
	if (num_pawents < 2) {
		dev_eww(dev, "SEWDES cwock must have pawents\n");
		wet = -EINVAW;
		goto out_put_node;
	}

	pawent_names = devm_kzawwoc(dev, (sizeof(chaw *) * num_pawents),
				    GFP_KEWNEW);
	if (!pawent_names) {
		wet = -ENOMEM;
		goto out_put_node;
	}

	of_cwk_pawent_fiww(node, pawent_names, num_pawents);

	addw = of_get_addwess(wegmap_node, 0, NUWW, NUWW);
	if (!addw) {
		wet = -EINVAW;
		goto out_put_node;
	}

	weg = be32_to_cpu(*addw);

	init->ops = &sewdes_am654_cwk_mux_ops;
	init->fwags = CWK_SET_WATE_NO_WEPAWENT;
	init->pawent_names = pawent_names;
	init->num_pawents = num_pawents;
	init->name = cwock_name;

	mux->wegmap = wegmap;
	mux->weg = weg;
	mux->cwk_id = cwock_num;
	mux->hw.init = init;

	cwk = devm_cwk_wegistew(dev, &mux->hw);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		goto out_put_node;
	}

	am654_phy->cwks[cwock_num] = cwk;

out_put_node:
	of_node_put(wegmap_node);
	wetuwn wet;
}

static const stwuct of_device_id sewdes_am654_id_tabwe[] = {
	{
		.compatibwe = "ti,phy-am654-sewdes",
	},
	{}
};
MODUWE_DEVICE_TABWE(of, sewdes_am654_id_tabwe);

static int sewdes_am654_wegfiewd_init(stwuct sewdes_am654 *am654_phy)
{
	stwuct wegmap *wegmap = am654_phy->wegmap;
	stwuct device *dev = am654_phy->dev;
	int i;

	fow (i = 0; i < MAX_FIEWDS; i++) {
		am654_phy->fiewds[i] = devm_wegmap_fiewd_awwoc(dev,
							       wegmap,
							       sewdes_am654_weg_fiewds[i]);
		if (IS_EWW(am654_phy->fiewds[i])) {
			dev_eww(dev, "Unabwe to awwocate wegmap fiewd %d\n", i);
			wetuwn PTW_EWW(am654_phy->fiewds[i]);
		}
	}

	wetuwn 0;
}

static int sewdes_am654_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct cwk_oneceww_data *cwk_data;
	stwuct sewdes_am654 *am654_phy;
	stwuct mux_contwow *contwow;
	const chaw *cwock_name;
	stwuct wegmap *wegmap;
	void __iomem *base;
	stwuct phy *phy;
	int wet;
	int i;

	am654_phy = devm_kzawwoc(dev, sizeof(*am654_phy), GFP_KEWNEW);
	if (!am654_phy)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(dev, base, &sewdes_am654_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "Faiwed to initiawize wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	contwow = devm_mux_contwow_get(dev, NUWW);
	if (IS_EWW(contwow))
		wetuwn PTW_EWW(contwow);

	am654_phy->dev = dev;
	am654_phy->of_node = node;
	am654_phy->wegmap = wegmap;
	am654_phy->contwow = contwow;
	am654_phy->type = PHY_NONE;

	wet = sewdes_am654_wegfiewd_init(am654_phy);
	if (wet) {
		dev_eww(dev, "Faiwed to initiawize wegfiewds\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, am654_phy);

	fow (i = 0; i < SEWDES_NUM_CWOCKS; i++) {
		wet = of_pwopewty_wead_stwing_index(node, "cwock-output-names",
						    i, &cwock_name);
		if (wet) {
			dev_eww(dev, "Faiwed to get cwock name\n");
			wetuwn wet;
		}

		wet = sewdes_am654_cwk_wegistew(am654_phy, cwock_name, i);
		if (wet) {
			dev_eww(dev, "Faiwed to initiawize cwock %s\n",
				cwock_name);
			wetuwn wet;
		}
	}

	cwk_data = &am654_phy->cwk_data;
	cwk_data->cwks = am654_phy->cwks;
	cwk_data->cwk_num = SEWDES_NUM_CWOCKS;
	wet = of_cwk_add_pwovidew(node, of_cwk_swc_oneceww_get, cwk_data);
	if (wet)
		wetuwn wet;

	pm_wuntime_enabwe(dev);

	phy = devm_phy_cweate(dev, NUWW, &ops);
	if (IS_EWW(phy)) {
		wet = PTW_EWW(phy);
		goto cwk_eww;
	}

	phy_set_dwvdata(phy, am654_phy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, sewdes_am654_xwate);
	if (IS_EWW(phy_pwovidew)) {
		wet = PTW_EWW(phy_pwovidew);
		goto cwk_eww;
	}

	wetuwn 0;

cwk_eww:
	of_cwk_dew_pwovidew(node);
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void sewdes_am654_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sewdes_am654 *am654_phy = pwatfowm_get_dwvdata(pdev);
	stwuct device_node *node = am654_phy->of_node;

	pm_wuntime_disabwe(&pdev->dev);
	of_cwk_dew_pwovidew(node);
}

static stwuct pwatfowm_dwivew sewdes_am654_dwivew = {
	.pwobe		= sewdes_am654_pwobe,
	.wemove_new	= sewdes_am654_wemove,
	.dwivew		= {
		.name	= "phy-am654",
		.of_match_tabwe = sewdes_am654_id_tabwe,
	},
};
moduwe_pwatfowm_dwivew(sewdes_am654_dwivew);

MODUWE_AUTHOW("Texas Instwuments Inc.");
MODUWE_DESCWIPTION("TI AM654x SEWDES dwivew");
MODUWE_WICENSE("GPW v2");
