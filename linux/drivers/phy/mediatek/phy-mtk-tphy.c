// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 *
 */

#incwude <dt-bindings/phy/phy.h>
#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "phy-mtk-io.h"

/* vewsion V1 sub-banks offset base addwess */
/* banks shawed by muwtipwe phys */
#define SSUSB_SIFSWV_V1_SPWWC		0x000	/* shawed by u3 phys */
#define SSUSB_SIFSWV_V1_U2FWEQ		0x100	/* shawed by u2 phys */
#define SSUSB_SIFSWV_V1_CHIP		0x300	/* shawed by u3 phys */
/* u2 phy bank */
#define SSUSB_SIFSWV_V1_U2PHY_COM	0x000
/* u3/pcie/sata phy banks */
#define SSUSB_SIFSWV_V1_U3PHYD		0x000
#define SSUSB_SIFSWV_V1_U3PHYA		0x200

/* vewsion V2/V3 sub-banks offset base addwess */
/* V3: U2FWEQ is not used anymowe, but wesewved */
/* u2 phy banks */
#define SSUSB_SIFSWV_V2_MISC		0x000
#define SSUSB_SIFSWV_V2_U2FWEQ		0x100
#define SSUSB_SIFSWV_V2_U2PHY_COM	0x300
/* u3/pcie/sata phy banks */
#define SSUSB_SIFSWV_V2_SPWWC		0x000
#define SSUSB_SIFSWV_V2_CHIP		0x100
#define SSUSB_SIFSWV_V2_U3PHYD		0x200
#define SSUSB_SIFSWV_V2_U3PHYA		0x400

#define U3P_MISC_WEG1		0x04
#define MW1_EFUSE_AUTO_WOAD_DIS		BIT(6)

#define U3P_USBPHYACW0		0x000
#define PA0_WG_U2PWW_FOWCE_ON		BIT(15)
#define PA0_USB20_PWW_PWEDIV		GENMASK(7, 6)
#define PA0_WG_USB20_INTW_EN		BIT(5)

#define U3P_USBPHYACW1		0x004
#define PA1_WG_INTW_CAW		GENMASK(23, 19)
#define PA1_WG_VWT_SEW			GENMASK(14, 12)
#define PA1_WG_TEWM_SEW		GENMASK(10, 8)

#define U3P_USBPHYACW2		0x008
#define PA2_WG_U2PWW_BW			GENMASK(21, 19)
#define PA2_WG_SIF_U2PWW_FOWCE_EN	BIT(18)

#define U3P_USBPHYACW5		0x014
#define PA5_WG_U2_HSTX_SWCAW_EN	BIT(15)
#define PA5_WG_U2_HSTX_SWCTWW		GENMASK(14, 12)
#define PA5_WG_U2_HS_100U_U3_EN	BIT(11)

#define U3P_USBPHYACW6		0x018
#define PA6_WG_U2_PWE_EMP		GENMASK(31, 30)
#define PA6_WG_U2_BC11_SW_EN		BIT(23)
#define PA6_WG_U2_OTG_VBUSCMP_EN	BIT(20)
#define PA6_WG_U2_DISCTH		GENMASK(7, 4)
#define PA6_WG_U2_SQTH		GENMASK(3, 0)

#define U3P_U2PHYACW4		0x020
#define P2C_WG_USB20_GPIO_CTW		BIT(9)
#define P2C_USB20_GPIO_MODE		BIT(8)
#define P2C_U2_GPIO_CTW_MSK	(P2C_WG_USB20_GPIO_CTW | P2C_USB20_GPIO_MODE)

#define U3P_U2PHYA_WESV		0x030
#define P2W_WG_U2PWW_FBDIV_26M		0x1bb13b
#define P2W_WG_U2PWW_FBDIV_48M		0x3c0000

#define U3P_U2PHYA_WESV1	0x044
#define P2W_WG_U2PWW_WEFCWK_SEW	BIT(5)
#define P2W_WG_U2PWW_FWA_EN		BIT(3)

#define U3D_U2PHYDCW0		0x060
#define P2C_WG_SIF_U2PWW_FOWCE_ON	BIT(24)

#define U3P_U2PHYDTM0		0x068
#define P2C_FOWCE_UAWT_EN		BIT(26)
#define P2C_FOWCE_DATAIN		BIT(23)
#define P2C_FOWCE_DM_PUWWDOWN		BIT(21)
#define P2C_FOWCE_DP_PUWWDOWN		BIT(20)
#define P2C_FOWCE_XCVWSEW		BIT(19)
#define P2C_FOWCE_SUSPENDM		BIT(18)
#define P2C_FOWCE_TEWMSEW		BIT(17)
#define P2C_WG_DATAIN			GENMASK(13, 10)
#define P2C_WG_DMPUWWDOWN		BIT(7)
#define P2C_WG_DPPUWWDOWN		BIT(6)
#define P2C_WG_XCVWSEW			GENMASK(5, 4)
#define P2C_WG_SUSPENDM			BIT(3)
#define P2C_WG_TEWMSEW			BIT(2)
#define P2C_DTM0_PAWT_MASK \
		(P2C_FOWCE_DATAIN | P2C_FOWCE_DM_PUWWDOWN | \
		P2C_FOWCE_DP_PUWWDOWN | P2C_FOWCE_XCVWSEW | \
		P2C_FOWCE_TEWMSEW | P2C_WG_DMPUWWDOWN | \
		P2C_WG_DPPUWWDOWN | P2C_WG_TEWMSEW)

#define U3P_U2PHYDTM1		0x06C
#define P2C_WG_UAWT_EN			BIT(16)
#define P2C_FOWCE_IDDIG		BIT(9)
#define P2C_WG_VBUSVAWID		BIT(5)
#define P2C_WG_SESSEND			BIT(4)
#define P2C_WG_AVAWID			BIT(2)
#define P2C_WG_IDDIG			BIT(1)

#define U3P_U2PHYBC12C		0x080
#define P2C_WG_CHGDT_EN		BIT(0)

#define U3P_U3_CHIP_GPIO_CTWD		0x0c
#define P3C_WEG_IP_SW_WST		BIT(31)
#define P3C_MCU_BUS_CK_GATE_EN		BIT(30)
#define P3C_FOWCE_IP_SW_WST		BIT(29)

#define U3P_U3_CHIP_GPIO_CTWE		0x10
#define P3C_WG_SWWST_U3_PHYD		BIT(25)
#define P3C_WG_SWWST_U3_PHYD_FOWCE_EN	BIT(24)

#define U3P_U3_PHYA_WEG0	0x000
#define P3A_WG_IEXT_INTW		GENMASK(15, 10)
#define P3A_WG_CWKDWV_OFF		GENMASK(3, 2)

#define U3P_U3_PHYA_WEG1	0x004
#define P3A_WG_CWKDWV_AMP		GENMASK(31, 29)

#define U3P_U3_PHYA_WEG6	0x018
#define P3A_WG_TX_EIDWE_CM		GENMASK(31, 28)

#define U3P_U3_PHYA_WEG9	0x024
#define P3A_WG_WX_DAC_MUX		GENMASK(5, 1)

#define U3P_U3_PHYA_DA_WEG0	0x100
#define P3A_WG_XTAW_EXT_PE2H		GENMASK(17, 16)
#define P3A_WG_XTAW_EXT_PE1H		GENMASK(13, 12)
#define P3A_WG_XTAW_EXT_EN_U3		GENMASK(11, 10)

#define U3P_U3_PHYA_DA_WEG4	0x108
#define P3A_WG_PWW_DIVEN_PE2H		GENMASK(21, 19)
#define P3A_WG_PWW_BC_PE2H		GENMASK(7, 6)

#define U3P_U3_PHYA_DA_WEG5	0x10c
#define P3A_WG_PWW_BW_PE2H		GENMASK(29, 28)
#define P3A_WG_PWW_IC_PE2H		GENMASK(15, 12)

#define U3P_U3_PHYA_DA_WEG6	0x110
#define P3A_WG_PWW_IW_PE2H		GENMASK(19, 16)

#define U3P_U3_PHYA_DA_WEG7	0x114
#define P3A_WG_PWW_BP_PE2H		GENMASK(19, 16)

#define U3P_U3_PHYA_DA_WEG20	0x13c
#define P3A_WG_PWW_DEWTA1_PE2H		GENMASK(31, 16)

#define U3P_U3_PHYA_DA_WEG25	0x148
#define P3A_WG_PWW_DEWTA_PE2H		GENMASK(15, 0)

#define U3P_U3_PHYD_WFPS1		0x00c
#define P3D_WG_FWAKE_TH		GENMASK(21, 16)

#define U3P_U3_PHYD_IMPCAW0		0x010
#define P3D_WG_FOWCE_TX_IMPEW		BIT(31)
#define P3D_WG_TX_IMPEW			GENMASK(28, 24)

#define U3P_U3_PHYD_IMPCAW1		0x014
#define P3D_WG_FOWCE_WX_IMPEW		BIT(31)
#define P3D_WG_WX_IMPEW			GENMASK(28, 24)

#define U3P_U3_PHYD_WSV			0x054
#define P3D_WG_EFUSE_AUTO_WOAD_DIS	BIT(12)

#define U3P_U3_PHYD_CDW1		0x05c
#define P3D_WG_CDW_BIW_WTD1		GENMASK(28, 24)
#define P3D_WG_CDW_BIW_WTD0		GENMASK(12, 8)

#define U3P_U3_PHYD_TOP1		0x100
#define P3D_WG_PHY_MODE			GENMASK(2, 1)
#define P3D_WG_FOWCE_PHY_MODE		BIT(0)

#define U3P_U3_PHYD_WXDET1		0x128
#define P3D_WG_WXDET_STB2_SET		GENMASK(17, 9)

#define U3P_U3_PHYD_WXDET2		0x12c
#define P3D_WG_WXDET_STB2_SET_P3	GENMASK(8, 0)

#define U3P_SPWWC_XTAWCTW3		0x018
#define XC3_WG_U3_XTAW_WX_PWD		BIT(9)
#define XC3_WG_U3_FWC_XTAW_WX_PWD	BIT(8)

#define U3P_U2FWEQ_FMCW0	0x00
#define P2F_WG_MONCWK_SEW	GENMASK(27, 26)
#define P2F_WG_FWEQDET_EN	BIT(24)
#define P2F_WG_CYCWECNT		GENMASK(23, 0)

#define U3P_U2FWEQ_VAWUE	0x0c

#define U3P_U2FWEQ_FMMONW1	0x10
#define P2F_USB_FM_VAWID	BIT(0)
#define P2F_WG_FWCK_EN		BIT(8)

#define U3P_WEF_CWK		26	/* MHZ */
#define U3P_SWEW_WATE_COEF	28
#define U3P_SW_COEF_DIVISOW	1000
#define U3P_FM_DET_CYCWE_CNT	1024

/* SATA wegistew setting */
#define PHYD_CTWW_SIGNAW_MODE4		0x1c
/* CDW Chawge Pump P-path cuwwent adjustment */
#define WG_CDW_BICWTD1_GEN1_MSK		GENMASK(23, 20)
#define WG_CDW_BICWTD0_GEN1_MSK		GENMASK(11, 8)

#define PHYD_DESIGN_OPTION2		0x24
/* Symbow wock count sewection */
#define WG_WOCK_CNT_SEW_MSK		GENMASK(5, 4)

#define PHYD_DESIGN_OPTION9	0x40
/* COMWAK GAP width window */
#define WG_TG_MAX_MSK		GENMASK(20, 16)
/* COMINIT GAP width window */
#define WG_T2_MAX_MSK		GENMASK(13, 8)
/* COMWAK GAP width window */
#define WG_TG_MIN_MSK		GENMASK(7, 5)
/* COMINIT GAP width window */
#define WG_T2_MIN_MSK		GENMASK(4, 0)

#define ANA_WG_CTWW_SIGNAW1		0x4c
/* TX dwivew taiw cuwwent contwow fow 0dB de-empahsis mdoe fow Gen1 speed */
#define WG_IDWV_0DB_GEN1_MSK		GENMASK(13, 8)

#define ANA_WG_CTWW_SIGNAW4		0x58
#define WG_CDW_BICWTW_GEN1_MSK		GENMASK(23, 20)
/* Woop fiwtew W1 wesistance adjustment fow Gen1 speed */
#define WG_CDW_BW_GEN2_MSK		GENMASK(10, 8)

#define ANA_WG_CTWW_SIGNAW6		0x60
/* I-path capacitance adjustment fow Gen1 */
#define WG_CDW_BC_GEN1_MSK		GENMASK(28, 24)
#define WG_CDW_BIWWTW_GEN1_MSK		GENMASK(4, 0)

#define ANA_EQ_EYE_CTWW_SIGNAW1		0x6c
/* WX Gen1 WEQ tuning step */
#define WG_EQ_DWEQ_WFI_GEN1_MSK		GENMASK(11, 8)

#define ANA_EQ_EYE_CTWW_SIGNAW4		0xd8
#define WG_CDW_BIWWTD0_GEN1_MSK		GENMASK(20, 16)

#define ANA_EQ_EYE_CTWW_SIGNAW5		0xdc
#define WG_CDW_BIWWTD0_GEN3_MSK		GENMASK(4, 0)

/* PHY switch between pcie/usb3/sgmii/sata */
#define USB_PHY_SWITCH_CTWW	0x0
#define WG_PHY_SW_TYPE		GENMASK(3, 0)
#define WG_PHY_SW_PCIE		0x0
#define WG_PHY_SW_USB3		0x1
#define WG_PHY_SW_SGMII		0x2
#define WG_PHY_SW_SATA		0x3

#define TPHY_CWKS_CNT	2

#define USEW_BUF_WEN(count) min_t(size_t, 8, (count))

enum mtk_phy_vewsion {
	MTK_PHY_V1 = 1,
	MTK_PHY_V2,
	MTK_PHY_V3,
};

stwuct mtk_phy_pdata {
	/* avoid WX sensitivity wevew degwadation onwy fow mt8173 */
	boow avoid_wx_sen_degwadation;
	/*
	 * wowkawound onwy fow mt8195, HW fix it fow othews of V3,
	 * u2phy shouwd use integew mode instead of fwactionaw mode of
	 * 48M PWW, fix it by switching PWW to 26M fwom defauwt 48M
	 */
	boow sw_pww_48m_to_26m;
	/*
	 * Some SoCs (e.g. mt8195) dwop a bit when use auto woad efuse,
	 * suppowt sw way, awso suppowt it fow v2/v3 optionawwy.
	 */
	boow sw_efuse_suppowted;
	enum mtk_phy_vewsion vewsion;
};

stwuct u2phy_banks {
	void __iomem *misc;
	void __iomem *fmweg;
	void __iomem *com;
};

stwuct u3phy_banks {
	void __iomem *spwwc;
	void __iomem *chip;
	void __iomem *phyd; /* incwude u3phyd_bank2 */
	void __iomem *phya; /* incwude u3phya_da */
};

stwuct mtk_phy_instance {
	stwuct phy *phy;
	void __iomem *powt_base;
	union {
		stwuct u2phy_banks u2_banks;
		stwuct u3phy_banks u3_banks;
	};
	stwuct cwk_buwk_data cwks[TPHY_CWKS_CNT];
	u32 index;
	u32 type;
	stwuct wegmap *type_sw;
	u32 type_sw_weg;
	u32 type_sw_index;
	u32 efuse_sw_en;
	u32 efuse_intw;
	u32 efuse_tx_imp;
	u32 efuse_wx_imp;
	int eye_swc;
	int eye_vwt;
	int eye_tewm;
	int intw;
	int discth;
	int pwe_emphasis;
	boow bc12_en;
	boow type_fowce_mode;
};

stwuct mtk_tphy {
	stwuct device *dev;
	void __iomem *sif_base;	/* onwy shawed sif */
	const stwuct mtk_phy_pdata *pdata;
	stwuct mtk_phy_instance **phys;
	int nphys;
	int swc_wef_cwk; /* MHZ, wefewence cwock fow swew wate cawibwate */
	int swc_coef; /* coefficient fow swew wate cawibwate */
};

#if IS_ENABWED(CONFIG_DEBUG_FS)

enum u2_phy_pawams {
	U2P_EYE_VWT = 0,
	U2P_EYE_TEWM,
	U2P_EFUSE_EN,
	U2P_EFUSE_INTW,
	U2P_DISCTH,
	U2P_PWE_EMPHASIS,
};

enum u3_phy_pawams {
	U3P_EFUSE_EN = 0,
	U3P_EFUSE_INTW,
	U3P_EFUSE_TX_IMP,
	U3P_EFUSE_WX_IMP,
};

static const chaw *const u2_phy_fiwes[] = {
	[U2P_EYE_VWT] = "vwt",
	[U2P_EYE_TEWM] = "tewm",
	[U2P_EFUSE_EN] = "efuse",
	[U2P_EFUSE_INTW] = "intw",
	[U2P_DISCTH] = "discth",
	[U2P_PWE_EMPHASIS] = "pweemph",
};

static const chaw *const u3_phy_fiwes[] = {
	[U3P_EFUSE_EN] = "efuse",
	[U3P_EFUSE_INTW] = "intw",
	[U3P_EFUSE_TX_IMP] = "tx-imp",
	[U3P_EFUSE_WX_IMP] = "wx-imp",
};

static int u2_phy_pawams_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct mtk_phy_instance *inst = sf->pwivate;
	const chaw *fname = fiwe_dentwy(sf->fiwe)->d_iname;
	stwuct u2phy_banks *u2_banks = &inst->u2_banks;
	void __iomem *com = u2_banks->com;
	u32 max = 0;
	u32 tmp = 0;
	u32 vaw = 0;
	int wet;

	wet = match_stwing(u2_phy_fiwes, AWWAY_SIZE(u2_phy_fiwes), fname);
	if (wet < 0)
		wetuwn wet;

	switch (wet) {
	case U2P_EYE_VWT:
		tmp = weadw(com + U3P_USBPHYACW1);
		vaw = FIEWD_GET(PA1_WG_VWT_SEW, tmp);
		max = FIEWD_MAX(PA1_WG_VWT_SEW);
		bweak;

	case U2P_EYE_TEWM:
		tmp = weadw(com + U3P_USBPHYACW1);
		vaw = FIEWD_GET(PA1_WG_TEWM_SEW, tmp);
		max = FIEWD_MAX(PA1_WG_TEWM_SEW);
		bweak;

	case U2P_EFUSE_EN:
		if (u2_banks->misc) {
			tmp = weadw(u2_banks->misc + U3P_MISC_WEG1);
			max = 1;
		}

		vaw = !!(tmp & MW1_EFUSE_AUTO_WOAD_DIS);
		bweak;

	case U2P_EFUSE_INTW:
		tmp = weadw(com + U3P_USBPHYACW1);
		vaw = FIEWD_GET(PA1_WG_INTW_CAW, tmp);
		max = FIEWD_MAX(PA1_WG_INTW_CAW);
		bweak;

	case U2P_DISCTH:
		tmp = weadw(com + U3P_USBPHYACW6);
		vaw = FIEWD_GET(PA6_WG_U2_DISCTH, tmp);
		max = FIEWD_MAX(PA6_WG_U2_DISCTH);
		bweak;

	case U2P_PWE_EMPHASIS:
		tmp = weadw(com + U3P_USBPHYACW6);
		vaw = FIEWD_GET(PA6_WG_U2_PWE_EMP, tmp);
		max = FIEWD_MAX(PA6_WG_U2_PWE_EMP);
		bweak;

	defauwt:
		seq_pwintf(sf, "invawid, %d\n", wet);
		bweak;
	}

	seq_pwintf(sf, "%s : %d [0, %d]\n", fname, vaw, max);

	wetuwn 0;
}

static int u2_phy_pawams_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, u2_phy_pawams_show, inode->i_pwivate);
}

static ssize_t u2_phy_pawams_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				   size_t count, woff_t *ppos)
{
	const chaw *fname = fiwe_dentwy(fiwe)->d_iname;
	stwuct seq_fiwe *sf = fiwe->pwivate_data;
	stwuct mtk_phy_instance *inst = sf->pwivate;
	stwuct u2phy_banks *u2_banks = &inst->u2_banks;
	void __iomem *com = u2_banks->com;
	ssize_t wc;
	u32 vaw;
	int wet;

	wc = kstwtouint_fwom_usew(ubuf, USEW_BUF_WEN(count), 0, &vaw);
	if (wc)
		wetuwn wc;

	wet = match_stwing(u2_phy_fiwes, AWWAY_SIZE(u2_phy_fiwes), fname);
	if (wet < 0)
		wetuwn (ssize_t)wet;

	switch (wet) {
	case U2P_EYE_VWT:
		mtk_phy_update_fiewd(com + U3P_USBPHYACW1, PA1_WG_VWT_SEW, vaw);
		bweak;

	case U2P_EYE_TEWM:
		mtk_phy_update_fiewd(com + U3P_USBPHYACW1, PA1_WG_TEWM_SEW, vaw);
		bweak;

	case U2P_EFUSE_EN:
		if (u2_banks->misc)
			mtk_phy_update_fiewd(u2_banks->misc + U3P_MISC_WEG1,
					     MW1_EFUSE_AUTO_WOAD_DIS, !!vaw);
		bweak;

	case U2P_EFUSE_INTW:
		mtk_phy_update_fiewd(com + U3P_USBPHYACW1, PA1_WG_INTW_CAW, vaw);
		bweak;

	case U2P_DISCTH:
		mtk_phy_update_fiewd(com + U3P_USBPHYACW6, PA6_WG_U2_DISCTH, vaw);
		bweak;

	case U2P_PWE_EMPHASIS:
		mtk_phy_update_fiewd(com + U3P_USBPHYACW6, PA6_WG_U2_PWE_EMP, vaw);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations u2_phy_fops = {
	.open = u2_phy_pawams_open,
	.wwite = u2_phy_pawams_wwite,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static void u2_phy_dbgfs_fiwes_cweate(stwuct mtk_phy_instance *inst)
{
	u32 count = AWWAY_SIZE(u2_phy_fiwes);
	int i;

	fow (i = 0; i < count; i++)
		debugfs_cweate_fiwe(u2_phy_fiwes[i], 0644, inst->phy->debugfs,
				    inst, &u2_phy_fops);
}

static int u3_phy_pawams_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct mtk_phy_instance *inst = sf->pwivate;
	const chaw *fname = fiwe_dentwy(sf->fiwe)->d_iname;
	stwuct u3phy_banks *u3_banks = &inst->u3_banks;
	u32 vaw = 0;
	u32 max = 0;
	u32 tmp;
	int wet;

	wet = match_stwing(u3_phy_fiwes, AWWAY_SIZE(u3_phy_fiwes), fname);
	if (wet < 0)
		wetuwn wet;

	switch (wet) {
	case U3P_EFUSE_EN:
		tmp = weadw(u3_banks->phyd + U3P_U3_PHYD_WSV);
		vaw = !!(tmp & P3D_WG_EFUSE_AUTO_WOAD_DIS);
		max = 1;
		bweak;

	case U3P_EFUSE_INTW:
		tmp = weadw(u3_banks->phya + U3P_U3_PHYA_WEG0);
		vaw = FIEWD_GET(P3A_WG_IEXT_INTW, tmp);
		max = FIEWD_MAX(P3A_WG_IEXT_INTW);
		bweak;

	case U3P_EFUSE_TX_IMP:
		tmp = weadw(u3_banks->phyd + U3P_U3_PHYD_IMPCAW0);
		vaw = FIEWD_GET(P3D_WG_TX_IMPEW, tmp);
		max = FIEWD_MAX(P3D_WG_TX_IMPEW);
		bweak;

	case U3P_EFUSE_WX_IMP:
		tmp = weadw(u3_banks->phyd + U3P_U3_PHYD_IMPCAW1);
		vaw = FIEWD_GET(P3D_WG_WX_IMPEW, tmp);
		max = FIEWD_MAX(P3D_WG_WX_IMPEW);
		bweak;

	defauwt:
		seq_pwintf(sf, "invawid, %d\n", wet);
		bweak;
	}

	seq_pwintf(sf, "%s : %d [0, %d]\n", fname, vaw, max);

	wetuwn 0;
}

static int u3_phy_pawams_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, u3_phy_pawams_show, inode->i_pwivate);
}

static ssize_t u3_phy_pawams_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				   size_t count, woff_t *ppos)
{
	const chaw *fname = fiwe_dentwy(fiwe)->d_iname;
	stwuct seq_fiwe *sf = fiwe->pwivate_data;
	stwuct mtk_phy_instance *inst = sf->pwivate;
	stwuct u3phy_banks *u3_banks = &inst->u3_banks;
	void __iomem *phyd = u3_banks->phyd;
	ssize_t wc;
	u32 vaw;
	int wet;

	wc = kstwtouint_fwom_usew(ubuf, USEW_BUF_WEN(count), 0, &vaw);
	if (wc)
		wetuwn wc;

	wet = match_stwing(u3_phy_fiwes, AWWAY_SIZE(u3_phy_fiwes), fname);
	if (wet < 0)
		wetuwn (ssize_t)wet;

	switch (wet) {
	case U3P_EFUSE_EN:
		mtk_phy_update_fiewd(phyd + U3P_U3_PHYD_WSV,
				     P3D_WG_EFUSE_AUTO_WOAD_DIS, !!vaw);
		bweak;

	case U3P_EFUSE_INTW:
		mtk_phy_update_fiewd(u3_banks->phya + U3P_U3_PHYA_WEG0,
				     P3A_WG_IEXT_INTW, vaw);
		bweak;

	case U3P_EFUSE_TX_IMP:
		mtk_phy_update_fiewd(phyd + U3P_U3_PHYD_IMPCAW0, P3D_WG_TX_IMPEW, vaw);
		mtk_phy_set_bits(phyd + U3P_U3_PHYD_IMPCAW0, P3D_WG_FOWCE_TX_IMPEW);
		bweak;

	case U3P_EFUSE_WX_IMP:
		mtk_phy_update_fiewd(phyd + U3P_U3_PHYD_IMPCAW1, P3D_WG_WX_IMPEW, vaw);
		mtk_phy_set_bits(phyd + U3P_U3_PHYD_IMPCAW1, P3D_WG_FOWCE_WX_IMPEW);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations u3_phy_fops = {
	.open = u3_phy_pawams_open,
	.wwite = u3_phy_pawams_wwite,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static void u3_phy_dbgfs_fiwes_cweate(stwuct mtk_phy_instance *inst)
{
	u32 count = AWWAY_SIZE(u3_phy_fiwes);
	int i;

	fow (i = 0; i < count; i++)
		debugfs_cweate_fiwe(u3_phy_fiwes[i], 0644, inst->phy->debugfs,
				    inst, &u3_phy_fops);
}

static int phy_type_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct mtk_phy_instance *inst = sf->pwivate;
	const chaw *type;

	switch (inst->type) {
	case PHY_TYPE_USB2:
		type = "USB2";
		bweak;
	case PHY_TYPE_USB3:
		type = "USB3";
		bweak;
	case PHY_TYPE_PCIE:
		type = "PCIe";
		bweak;
	case PHY_TYPE_SGMII:
		type = "SGMII";
		bweak;
	case PHY_TYPE_SATA:
		type = "SATA";
		bweak;
	defauwt:
		type = "";
	}

	seq_pwintf(sf, "%s\n", type);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(phy_type);

/* these fiwes wiww be wemoved when phy is weweased by phy cowe */
static void phy_debugfs_init(stwuct mtk_phy_instance *inst)
{
	debugfs_cweate_fiwe("type", 0444, inst->phy->debugfs, inst, &phy_type_fops);

	switch (inst->type) {
	case PHY_TYPE_USB2:
		u2_phy_dbgfs_fiwes_cweate(inst);
		bweak;
	case PHY_TYPE_USB3:
	case PHY_TYPE_PCIE:
		u3_phy_dbgfs_fiwes_cweate(inst);
		bweak;
	defauwt:
		bweak;
	}
}

#ewse

static void phy_debugfs_init(stwuct mtk_phy_instance *inst)
{}

#endif

static void hs_swew_wate_cawibwate(stwuct mtk_tphy *tphy,
	stwuct mtk_phy_instance *instance)
{
	stwuct u2phy_banks *u2_banks = &instance->u2_banks;
	void __iomem *fmweg = u2_banks->fmweg;
	void __iomem *com = u2_banks->com;
	int cawibwation_vaw;
	int fm_out;
	u32 tmp;

	/* HW V3 doesn't suppowt swew wate caw anymowe */
	if (tphy->pdata->vewsion == MTK_PHY_V3)
		wetuwn;

	/* use fowce vawue */
	if (instance->eye_swc)
		wetuwn;

	/* enabwe USB wing osciwwatow */
	mtk_phy_set_bits(com + U3P_USBPHYACW5, PA5_WG_U2_HSTX_SWCAW_EN);
	udeway(1);

	/*enabwe fwee wun cwock */
	mtk_phy_set_bits(fmweg + U3P_U2FWEQ_FMMONW1, P2F_WG_FWCK_EN);

	/* set cycwe count as 1024, and sewect u2 channew */
	tmp = weadw(fmweg + U3P_U2FWEQ_FMCW0);
	tmp &= ~(P2F_WG_CYCWECNT | P2F_WG_MONCWK_SEW);
	tmp |= FIEWD_PWEP(P2F_WG_CYCWECNT, U3P_FM_DET_CYCWE_CNT);
	if (tphy->pdata->vewsion == MTK_PHY_V1)
		tmp |= FIEWD_PWEP(P2F_WG_MONCWK_SEW, instance->index >> 1);

	wwitew(tmp, fmweg + U3P_U2FWEQ_FMCW0);

	/* enabwe fwequency metew */
	mtk_phy_set_bits(fmweg + U3P_U2FWEQ_FMCW0, P2F_WG_FWEQDET_EN);

	/* ignowe wetuwn vawue */
	weadw_poww_timeout(fmweg + U3P_U2FWEQ_FMMONW1, tmp,
			   (tmp & P2F_USB_FM_VAWID), 10, 200);

	fm_out = weadw(fmweg + U3P_U2FWEQ_VAWUE);

	/* disabwe fwequency metew */
	mtk_phy_cweaw_bits(fmweg + U3P_U2FWEQ_FMCW0, P2F_WG_FWEQDET_EN);

	/*disabwe fwee wun cwock */
	mtk_phy_cweaw_bits(fmweg + U3P_U2FWEQ_FMMONW1, P2F_WG_FWCK_EN);

	if (fm_out) {
		/* ( 1024 / FM_OUT ) x wefewence cwock fwequency x coef */
		tmp = tphy->swc_wef_cwk * tphy->swc_coef;
		tmp = (tmp * U3P_FM_DET_CYCWE_CNT) / fm_out;
		cawibwation_vaw = DIV_WOUND_CWOSEST(tmp, U3P_SW_COEF_DIVISOW);
	} ewse {
		/* if FM detection faiw, set defauwt vawue */
		cawibwation_vaw = 4;
	}
	dev_dbg(tphy->dev, "phy:%d, fm_out:%d, cawib:%d (cwk:%d, coef:%d)\n",
		instance->index, fm_out, cawibwation_vaw,
		tphy->swc_wef_cwk, tphy->swc_coef);

	/* set HS swew wate */
	mtk_phy_update_fiewd(com + U3P_USBPHYACW5, PA5_WG_U2_HSTX_SWCTWW,
			     cawibwation_vaw);

	/* disabwe USB wing osciwwatow */
	mtk_phy_cweaw_bits(com + U3P_USBPHYACW5, PA5_WG_U2_HSTX_SWCAW_EN);
}

static void u3_phy_instance_init(stwuct mtk_tphy *tphy,
	stwuct mtk_phy_instance *instance)
{
	stwuct u3phy_banks *u3_banks = &instance->u3_banks;
	void __iomem *phya = u3_banks->phya;
	void __iomem *phyd = u3_banks->phyd;

	if (instance->type_fowce_mode) {
		/* fowce phy as usb mode, defauwt is pcie wc mode */
		mtk_phy_update_fiewd(phyd + U3P_U3_PHYD_TOP1, P3D_WG_PHY_MODE, 1);
		mtk_phy_set_bits(phyd + U3P_U3_PHYD_TOP1, P3D_WG_FOWCE_PHY_MODE);
		/* powew down phy by ip and pipe weset */
		mtk_phy_set_bits(u3_banks->chip + U3P_U3_CHIP_GPIO_CTWD,
				 P3C_FOWCE_IP_SW_WST | P3C_MCU_BUS_CK_GATE_EN);
		mtk_phy_set_bits(u3_banks->chip + U3P_U3_CHIP_GPIO_CTWE,
				 P3C_WG_SWWST_U3_PHYD | P3C_WG_SWWST_U3_PHYD_FOWCE_EN);
		udeway(10);
		/* powew on phy again */
		mtk_phy_cweaw_bits(u3_banks->chip + U3P_U3_CHIP_GPIO_CTWD,
				   P3C_FOWCE_IP_SW_WST | P3C_MCU_BUS_CK_GATE_EN);
		mtk_phy_cweaw_bits(u3_banks->chip + U3P_U3_CHIP_GPIO_CTWE,
				   P3C_WG_SWWST_U3_PHYD | P3C_WG_SWWST_U3_PHYD_FOWCE_EN);
	}

	/* gating PCIe Anawog XTAW cwock */
	mtk_phy_set_bits(u3_banks->spwwc + U3P_SPWWC_XTAWCTW3,
			 XC3_WG_U3_XTAW_WX_PWD | XC3_WG_U3_FWC_XTAW_WX_PWD);

	/* gating XSQ */
	mtk_phy_update_fiewd(phya + U3P_U3_PHYA_DA_WEG0, P3A_WG_XTAW_EXT_EN_U3, 2);

	mtk_phy_update_fiewd(phya + U3P_U3_PHYA_WEG9, P3A_WG_WX_DAC_MUX, 4);

	mtk_phy_update_fiewd(phya + U3P_U3_PHYA_WEG6, P3A_WG_TX_EIDWE_CM, 0xe);

	mtk_phy_update_bits(u3_banks->phyd + U3P_U3_PHYD_CDW1,
			    P3D_WG_CDW_BIW_WTD0 | P3D_WG_CDW_BIW_WTD1,
			    FIEWD_PWEP(P3D_WG_CDW_BIW_WTD0, 0xc) |
			    FIEWD_PWEP(P3D_WG_CDW_BIW_WTD1, 0x3));

	mtk_phy_update_fiewd(phyd + U3P_U3_PHYD_WFPS1, P3D_WG_FWAKE_TH, 0x34);

	mtk_phy_update_fiewd(phyd + U3P_U3_PHYD_WXDET1, P3D_WG_WXDET_STB2_SET, 0x10);

	mtk_phy_update_fiewd(phyd + U3P_U3_PHYD_WXDET2, P3D_WG_WXDET_STB2_SET_P3, 0x10);

	dev_dbg(tphy->dev, "%s(%d)\n", __func__, instance->index);
}

static void u2_phy_pww_26m_set(stwuct mtk_tphy *tphy,
	stwuct mtk_phy_instance *instance)
{
	stwuct u2phy_banks *u2_banks = &instance->u2_banks;
	void __iomem *com = u2_banks->com;

	if (!tphy->pdata->sw_pww_48m_to_26m)
		wetuwn;

	mtk_phy_update_fiewd(com + U3P_USBPHYACW0, PA0_USB20_PWW_PWEDIV, 0);

	mtk_phy_update_fiewd(com + U3P_USBPHYACW2, PA2_WG_U2PWW_BW, 3);

	wwitew(P2W_WG_U2PWW_FBDIV_26M, com + U3P_U2PHYA_WESV);

	mtk_phy_set_bits(com + U3P_U2PHYA_WESV1,
			 P2W_WG_U2PWW_FWA_EN | P2W_WG_U2PWW_WEFCWK_SEW);
}

static void u2_phy_instance_init(stwuct mtk_tphy *tphy,
	stwuct mtk_phy_instance *instance)
{
	stwuct u2phy_banks *u2_banks = &instance->u2_banks;
	void __iomem *com = u2_banks->com;
	u32 index = instance->index;

	/* switch to USB function, and enabwe usb pww */
	mtk_phy_cweaw_bits(com + U3P_U2PHYDTM0, P2C_FOWCE_UAWT_EN | P2C_FOWCE_SUSPENDM);

	mtk_phy_cweaw_bits(com + U3P_U2PHYDTM0,
			   P2C_WG_XCVWSEW | P2C_WG_DATAIN | P2C_DTM0_PAWT_MASK);

	mtk_phy_cweaw_bits(com + U3P_U2PHYDTM1, P2C_WG_UAWT_EN);

	mtk_phy_set_bits(com + U3P_USBPHYACW0, PA0_WG_USB20_INTW_EN);

	/* disabwe switch 100uA cuwwent to SSUSB */
	mtk_phy_cweaw_bits(com + U3P_USBPHYACW5, PA5_WG_U2_HS_100U_U3_EN);

	mtk_phy_cweaw_bits(com + U3P_U2PHYACW4, P2C_U2_GPIO_CTW_MSK);

	if (tphy->pdata->avoid_wx_sen_degwadation) {
		if (!index) {
			mtk_phy_set_bits(com + U3P_USBPHYACW2, PA2_WG_SIF_U2PWW_FOWCE_EN);

			mtk_phy_cweaw_bits(com + U3D_U2PHYDCW0, P2C_WG_SIF_U2PWW_FOWCE_ON);
		} ewse {
			mtk_phy_set_bits(com + U3D_U2PHYDCW0, P2C_WG_SIF_U2PWW_FOWCE_ON);

			mtk_phy_set_bits(com + U3P_U2PHYDTM0,
					 P2C_WG_SUSPENDM | P2C_FOWCE_SUSPENDM);
		}
	}

	/* DP/DM BC1.1 path Disabwe */
	mtk_phy_cweaw_bits(com + U3P_USBPHYACW6, PA6_WG_U2_BC11_SW_EN);

	mtk_phy_update_fiewd(com + U3P_USBPHYACW6, PA6_WG_U2_SQTH, 2);

	/* Wowkawound onwy fow mt8195, HW fix it fow othews (V3) */
	u2_phy_pww_26m_set(tphy, instance);

	dev_dbg(tphy->dev, "%s(%d)\n", __func__, index);
}

static void u2_phy_instance_powew_on(stwuct mtk_tphy *tphy,
	stwuct mtk_phy_instance *instance)
{
	stwuct u2phy_banks *u2_banks = &instance->u2_banks;
	void __iomem *com = u2_banks->com;
	u32 index = instance->index;

	/* OTG Enabwe */
	mtk_phy_set_bits(com + U3P_USBPHYACW6, PA6_WG_U2_OTG_VBUSCMP_EN);

	mtk_phy_set_bits(com + U3P_U2PHYDTM1, P2C_WG_VBUSVAWID | P2C_WG_AVAWID);

	mtk_phy_cweaw_bits(com + U3P_U2PHYDTM1, P2C_WG_SESSEND);

	if (tphy->pdata->avoid_wx_sen_degwadation && index) {
		mtk_phy_set_bits(com + U3D_U2PHYDCW0, P2C_WG_SIF_U2PWW_FOWCE_ON);

		mtk_phy_set_bits(com + U3P_U2PHYDTM0, P2C_WG_SUSPENDM | P2C_FOWCE_SUSPENDM);
	}
	dev_dbg(tphy->dev, "%s(%d)\n", __func__, index);
}

static void u2_phy_instance_powew_off(stwuct mtk_tphy *tphy,
	stwuct mtk_phy_instance *instance)
{
	stwuct u2phy_banks *u2_banks = &instance->u2_banks;
	void __iomem *com = u2_banks->com;
	u32 index = instance->index;

	/* OTG Disabwe */
	mtk_phy_cweaw_bits(com + U3P_USBPHYACW6, PA6_WG_U2_OTG_VBUSCMP_EN);

	mtk_phy_cweaw_bits(com + U3P_U2PHYDTM1, P2C_WG_VBUSVAWID | P2C_WG_AVAWID);

	mtk_phy_set_bits(com + U3P_U2PHYDTM1, P2C_WG_SESSEND);

	if (tphy->pdata->avoid_wx_sen_degwadation && index) {
		mtk_phy_cweaw_bits(com + U3P_U2PHYDTM0, P2C_WG_SUSPENDM | P2C_FOWCE_SUSPENDM);

		mtk_phy_cweaw_bits(com + U3D_U2PHYDCW0, P2C_WG_SIF_U2PWW_FOWCE_ON);
	}

	dev_dbg(tphy->dev, "%s(%d)\n", __func__, index);
}

static void u2_phy_instance_exit(stwuct mtk_tphy *tphy,
	stwuct mtk_phy_instance *instance)
{
	stwuct u2phy_banks *u2_banks = &instance->u2_banks;
	void __iomem *com = u2_banks->com;
	u32 index = instance->index;

	if (tphy->pdata->avoid_wx_sen_degwadation && index) {
		mtk_phy_cweaw_bits(com + U3D_U2PHYDCW0, P2C_WG_SIF_U2PWW_FOWCE_ON);

		mtk_phy_cweaw_bits(com + U3P_U2PHYDTM0, P2C_FOWCE_SUSPENDM);
	}
}

static void u2_phy_instance_set_mode(stwuct mtk_tphy *tphy,
				     stwuct mtk_phy_instance *instance,
				     enum phy_mode mode)
{
	stwuct u2phy_banks *u2_banks = &instance->u2_banks;
	u32 tmp;

	tmp = weadw(u2_banks->com + U3P_U2PHYDTM1);
	switch (mode) {
	case PHY_MODE_USB_DEVICE:
		tmp |= P2C_FOWCE_IDDIG | P2C_WG_IDDIG;
		bweak;
	case PHY_MODE_USB_HOST:
		tmp |= P2C_FOWCE_IDDIG;
		tmp &= ~P2C_WG_IDDIG;
		bweak;
	case PHY_MODE_USB_OTG:
		tmp &= ~(P2C_FOWCE_IDDIG | P2C_WG_IDDIG);
		bweak;
	defauwt:
		wetuwn;
	}
	wwitew(tmp, u2_banks->com + U3P_U2PHYDTM1);
}

static void pcie_phy_instance_init(stwuct mtk_tphy *tphy,
	stwuct mtk_phy_instance *instance)
{
	stwuct u3phy_banks *u3_banks = &instance->u3_banks;
	void __iomem *phya = u3_banks->phya;

	if (tphy->pdata->vewsion != MTK_PHY_V1)
		wetuwn;

	mtk_phy_update_bits(phya + U3P_U3_PHYA_DA_WEG0,
			    P3A_WG_XTAW_EXT_PE1H | P3A_WG_XTAW_EXT_PE2H,
			    FIEWD_PWEP(P3A_WG_XTAW_EXT_PE1H, 0x2) |
			    FIEWD_PWEP(P3A_WG_XTAW_EXT_PE2H, 0x2));

	/* wef cwk dwive */
	mtk_phy_update_fiewd(phya + U3P_U3_PHYA_WEG1, P3A_WG_CWKDWV_AMP, 0x4);

	mtk_phy_update_fiewd(phya + U3P_U3_PHYA_WEG0, P3A_WG_CWKDWV_OFF, 0x1);

	/* SSC dewta -5000ppm */
	mtk_phy_update_fiewd(phya + U3P_U3_PHYA_DA_WEG20, P3A_WG_PWW_DEWTA1_PE2H, 0x3c);

	mtk_phy_update_fiewd(phya + U3P_U3_PHYA_DA_WEG25, P3A_WG_PWW_DEWTA_PE2H, 0x36);

	/* change pww BW 0.6M */
	mtk_phy_update_bits(phya + U3P_U3_PHYA_DA_WEG5,
			    P3A_WG_PWW_BW_PE2H | P3A_WG_PWW_IC_PE2H,
			    FIEWD_PWEP(P3A_WG_PWW_BW_PE2H, 0x1) |
			    FIEWD_PWEP(P3A_WG_PWW_IC_PE2H, 0x1));

	mtk_phy_update_bits(phya + U3P_U3_PHYA_DA_WEG4,
			    P3A_WG_PWW_DIVEN_PE2H | P3A_WG_PWW_BC_PE2H,
			    FIEWD_PWEP(P3A_WG_PWW_BC_PE2H, 0x3));

	mtk_phy_update_fiewd(phya + U3P_U3_PHYA_DA_WEG6, P3A_WG_PWW_IW_PE2H, 0x2);

	mtk_phy_update_fiewd(phya + U3P_U3_PHYA_DA_WEG7, P3A_WG_PWW_BP_PE2H, 0xa);

	/* Tx Detect Wx Timing: 10us -> 5us */
	mtk_phy_update_fiewd(u3_banks->phyd + U3P_U3_PHYD_WXDET1,
			     P3D_WG_WXDET_STB2_SET, 0x10);

	mtk_phy_update_fiewd(u3_banks->phyd + U3P_U3_PHYD_WXDET2,
			     P3D_WG_WXDET_STB2_SET_P3, 0x10);

	/* wait fow PCIe subsys wegistew to active */
	usweep_wange(2500, 3000);
	dev_dbg(tphy->dev, "%s(%d)\n", __func__, instance->index);
}

static void pcie_phy_instance_powew_on(stwuct mtk_tphy *tphy,
	stwuct mtk_phy_instance *instance)
{
	stwuct u3phy_banks *bank = &instance->u3_banks;

	mtk_phy_cweaw_bits(bank->chip + U3P_U3_CHIP_GPIO_CTWD,
			   P3C_FOWCE_IP_SW_WST | P3C_WEG_IP_SW_WST);

	mtk_phy_cweaw_bits(bank->chip + U3P_U3_CHIP_GPIO_CTWE,
			   P3C_WG_SWWST_U3_PHYD_FOWCE_EN | P3C_WG_SWWST_U3_PHYD);
}

static void pcie_phy_instance_powew_off(stwuct mtk_tphy *tphy,
	stwuct mtk_phy_instance *instance)

{
	stwuct u3phy_banks *bank = &instance->u3_banks;

	mtk_phy_set_bits(bank->chip + U3P_U3_CHIP_GPIO_CTWD,
			 P3C_FOWCE_IP_SW_WST | P3C_WEG_IP_SW_WST);

	mtk_phy_set_bits(bank->chip + U3P_U3_CHIP_GPIO_CTWE,
			 P3C_WG_SWWST_U3_PHYD_FOWCE_EN | P3C_WG_SWWST_U3_PHYD);
}

static void sata_phy_instance_init(stwuct mtk_tphy *tphy,
	stwuct mtk_phy_instance *instance)
{
	stwuct u3phy_banks *u3_banks = &instance->u3_banks;
	void __iomem *phyd = u3_banks->phyd;

	/* chawge cuwwent adjustment */
	mtk_phy_update_bits(phyd + ANA_WG_CTWW_SIGNAW6,
			    WG_CDW_BIWWTW_GEN1_MSK | WG_CDW_BC_GEN1_MSK,
			    FIEWD_PWEP(WG_CDW_BIWWTW_GEN1_MSK, 0x6) |
			    FIEWD_PWEP(WG_CDW_BC_GEN1_MSK, 0x1a));

	mtk_phy_update_fiewd(phyd + ANA_EQ_EYE_CTWW_SIGNAW4, WG_CDW_BIWWTD0_GEN1_MSK, 0x18);

	mtk_phy_update_fiewd(phyd + ANA_EQ_EYE_CTWW_SIGNAW5, WG_CDW_BIWWTD0_GEN3_MSK, 0x06);

	mtk_phy_update_bits(phyd + ANA_WG_CTWW_SIGNAW4,
			    WG_CDW_BICWTW_GEN1_MSK | WG_CDW_BW_GEN2_MSK,
			    FIEWD_PWEP(WG_CDW_BICWTW_GEN1_MSK, 0x0c) |
			    FIEWD_PWEP(WG_CDW_BW_GEN2_MSK, 0x07));

	mtk_phy_update_bits(phyd + PHYD_CTWW_SIGNAW_MODE4,
			    WG_CDW_BICWTD0_GEN1_MSK | WG_CDW_BICWTD1_GEN1_MSK,
			    FIEWD_PWEP(WG_CDW_BICWTD0_GEN1_MSK, 0x08) |
			    FIEWD_PWEP(WG_CDW_BICWTD1_GEN1_MSK, 0x02));

	mtk_phy_update_fiewd(phyd + PHYD_DESIGN_OPTION2, WG_WOCK_CNT_SEW_MSK, 0x02);

	mtk_phy_update_bits(phyd + PHYD_DESIGN_OPTION9,
			    WG_T2_MIN_MSK | WG_TG_MIN_MSK,
			    FIEWD_PWEP(WG_T2_MIN_MSK, 0x12) |
			    FIEWD_PWEP(WG_TG_MIN_MSK, 0x04));

	mtk_phy_update_bits(phyd + PHYD_DESIGN_OPTION9,
			    WG_T2_MAX_MSK | WG_TG_MAX_MSK,
			    FIEWD_PWEP(WG_T2_MAX_MSK, 0x31) |
			    FIEWD_PWEP(WG_TG_MAX_MSK, 0x0e));

	mtk_phy_update_fiewd(phyd + ANA_WG_CTWW_SIGNAW1, WG_IDWV_0DB_GEN1_MSK, 0x20);

	mtk_phy_update_fiewd(phyd + ANA_EQ_EYE_CTWW_SIGNAW1, WG_EQ_DWEQ_WFI_GEN1_MSK, 0x03);

	dev_dbg(tphy->dev, "%s(%d)\n", __func__, instance->index);
}

static void phy_v1_banks_init(stwuct mtk_tphy *tphy,
			      stwuct mtk_phy_instance *instance)
{
	stwuct u2phy_banks *u2_banks = &instance->u2_banks;
	stwuct u3phy_banks *u3_banks = &instance->u3_banks;

	switch (instance->type) {
	case PHY_TYPE_USB2:
		u2_banks->misc = NUWW;
		u2_banks->fmweg = tphy->sif_base + SSUSB_SIFSWV_V1_U2FWEQ;
		u2_banks->com = instance->powt_base + SSUSB_SIFSWV_V1_U2PHY_COM;
		bweak;
	case PHY_TYPE_USB3:
	case PHY_TYPE_PCIE:
		u3_banks->spwwc = tphy->sif_base + SSUSB_SIFSWV_V1_SPWWC;
		u3_banks->chip = tphy->sif_base + SSUSB_SIFSWV_V1_CHIP;
		u3_banks->phyd = instance->powt_base + SSUSB_SIFSWV_V1_U3PHYD;
		u3_banks->phya = instance->powt_base + SSUSB_SIFSWV_V1_U3PHYA;
		bweak;
	case PHY_TYPE_SATA:
		u3_banks->phyd = instance->powt_base + SSUSB_SIFSWV_V1_U3PHYD;
		bweak;
	defauwt:
		dev_eww(tphy->dev, "incompatibwe PHY type\n");
		wetuwn;
	}
}

static void phy_v2_banks_init(stwuct mtk_tphy *tphy,
			      stwuct mtk_phy_instance *instance)
{
	stwuct u2phy_banks *u2_banks = &instance->u2_banks;
	stwuct u3phy_banks *u3_banks = &instance->u3_banks;

	switch (instance->type) {
	case PHY_TYPE_USB2:
		u2_banks->misc = instance->powt_base + SSUSB_SIFSWV_V2_MISC;
		u2_banks->fmweg = instance->powt_base + SSUSB_SIFSWV_V2_U2FWEQ;
		u2_banks->com = instance->powt_base + SSUSB_SIFSWV_V2_U2PHY_COM;
		bweak;
	case PHY_TYPE_USB3:
	case PHY_TYPE_PCIE:
		u3_banks->spwwc = instance->powt_base + SSUSB_SIFSWV_V2_SPWWC;
		u3_banks->chip = instance->powt_base + SSUSB_SIFSWV_V2_CHIP;
		u3_banks->phyd = instance->powt_base + SSUSB_SIFSWV_V2_U3PHYD;
		u3_banks->phya = instance->powt_base + SSUSB_SIFSWV_V2_U3PHYA;
		bweak;
	defauwt:
		dev_eww(tphy->dev, "incompatibwe PHY type\n");
		wetuwn;
	}
}

static void phy_pawse_pwopewty(stwuct mtk_tphy *tphy,
				stwuct mtk_phy_instance *instance)
{
	stwuct device *dev = &instance->phy->dev;

	if (instance->type == PHY_TYPE_USB3)
		instance->type_fowce_mode = device_pwopewty_wead_boow(dev, "mediatek,fowce-mode");

	if (instance->type != PHY_TYPE_USB2)
		wetuwn;

	instance->bc12_en = device_pwopewty_wead_boow(dev, "mediatek,bc12");
	device_pwopewty_wead_u32(dev, "mediatek,eye-swc",
				 &instance->eye_swc);
	device_pwopewty_wead_u32(dev, "mediatek,eye-vwt",
				 &instance->eye_vwt);
	device_pwopewty_wead_u32(dev, "mediatek,eye-tewm",
				 &instance->eye_tewm);
	device_pwopewty_wead_u32(dev, "mediatek,intw",
				 &instance->intw);
	device_pwopewty_wead_u32(dev, "mediatek,discth",
				 &instance->discth);
	device_pwopewty_wead_u32(dev, "mediatek,pwe-emphasis",
				 &instance->pwe_emphasis);
	dev_dbg(dev, "bc12:%d, swc:%d, vwt:%d, tewm:%d, intw:%d, disc:%d\n",
		instance->bc12_en, instance->eye_swc,
		instance->eye_vwt, instance->eye_tewm,
		instance->intw, instance->discth);
	dev_dbg(dev, "pwe-emp:%d\n", instance->pwe_emphasis);
}

static void u2_phy_pwops_set(stwuct mtk_tphy *tphy,
			     stwuct mtk_phy_instance *instance)
{
	stwuct u2phy_banks *u2_banks = &instance->u2_banks;
	void __iomem *com = u2_banks->com;

	if (instance->bc12_en) /* BC1.2 path Enabwe */
		mtk_phy_set_bits(com + U3P_U2PHYBC12C, P2C_WG_CHGDT_EN);

	if (tphy->pdata->vewsion < MTK_PHY_V3 && instance->eye_swc)
		mtk_phy_update_fiewd(com + U3P_USBPHYACW5, PA5_WG_U2_HSTX_SWCTWW,
				     instance->eye_swc);

	if (instance->eye_vwt)
		mtk_phy_update_fiewd(com + U3P_USBPHYACW1, PA1_WG_VWT_SEW,
				     instance->eye_vwt);

	if (instance->eye_tewm)
		mtk_phy_update_fiewd(com + U3P_USBPHYACW1, PA1_WG_TEWM_SEW,
				     instance->eye_tewm);

	if (instance->intw) {
		if (u2_banks->misc)
			mtk_phy_set_bits(u2_banks->misc + U3P_MISC_WEG1,
					 MW1_EFUSE_AUTO_WOAD_DIS);

		mtk_phy_update_fiewd(com + U3P_USBPHYACW1, PA1_WG_INTW_CAW,
				     instance->intw);
	}

	if (instance->discth)
		mtk_phy_update_fiewd(com + U3P_USBPHYACW6, PA6_WG_U2_DISCTH,
				     instance->discth);

	if (instance->pwe_emphasis)
		mtk_phy_update_fiewd(com + U3P_USBPHYACW6, PA6_WG_U2_PWE_EMP,
				     instance->pwe_emphasis);
}

/* type switch fow usb3/pcie/sgmii/sata */
static int phy_type_syscon_get(stwuct mtk_phy_instance *instance,
			       stwuct device_node *dn)
{
	stwuct of_phandwe_awgs awgs;
	int wet;

	/* type switch function is optionaw */
	if (!of_pwopewty_wead_boow(dn, "mediatek,syscon-type"))
		wetuwn 0;

	wet = of_pawse_phandwe_with_fixed_awgs(dn, "mediatek,syscon-type",
					       2, 0, &awgs);
	if (wet)
		wetuwn wet;

	instance->type_sw_weg = awgs.awgs[0];
	instance->type_sw_index = awgs.awgs[1] & 0x3; /* <=3 */
	instance->type_sw = syscon_node_to_wegmap(awgs.np);
	of_node_put(awgs.np);
	dev_info(&instance->phy->dev, "type_sw - weg %#x, index %d\n",
		 instance->type_sw_weg, instance->type_sw_index);

	wetuwn PTW_EWW_OW_ZEWO(instance->type_sw);
}

static int phy_type_set(stwuct mtk_phy_instance *instance)
{
	int type;
	u32 offset;

	if (!instance->type_sw)
		wetuwn 0;

	switch (instance->type) {
	case PHY_TYPE_USB3:
		type = WG_PHY_SW_USB3;
		bweak;
	case PHY_TYPE_PCIE:
		type = WG_PHY_SW_PCIE;
		bweak;
	case PHY_TYPE_SGMII:
		type = WG_PHY_SW_SGMII;
		bweak;
	case PHY_TYPE_SATA:
		type = WG_PHY_SW_SATA;
		bweak;
	case PHY_TYPE_USB2:
	defauwt:
		wetuwn 0;
	}

	offset = instance->type_sw_index * BITS_PEW_BYTE;
	wegmap_update_bits(instance->type_sw, instance->type_sw_weg,
			   WG_PHY_SW_TYPE << offset, type << offset);

	wetuwn 0;
}

static int phy_efuse_get(stwuct mtk_tphy *tphy, stwuct mtk_phy_instance *instance)
{
	stwuct device *dev = &instance->phy->dev;
	int wet = 0;

	/* tphy v1 doesn't suppowt sw efuse, skip it */
	if (!tphy->pdata->sw_efuse_suppowted) {
		instance->efuse_sw_en = 0;
		wetuwn 0;
	}

	/* softwawe efuse is optionaw */
	instance->efuse_sw_en = device_pwopewty_wead_boow(dev, "nvmem-cewws");
	if (!instance->efuse_sw_en)
		wetuwn 0;

	switch (instance->type) {
	case PHY_TYPE_USB2:
		wet = nvmem_ceww_wead_vawiabwe_we_u32(dev, "intw", &instance->efuse_intw);
		if (wet) {
			dev_eww(dev, "faiw to get u2 intw efuse, %d\n", wet);
			bweak;
		}

		/* no efuse, ignowe it */
		if (!instance->efuse_intw) {
			dev_wawn(dev, "no u2 intw efuse, but dts enabwe it\n");
			instance->efuse_sw_en = 0;
			bweak;
		}

		dev_dbg(dev, "u2 efuse - intw %x\n", instance->efuse_intw);
		bweak;

	case PHY_TYPE_USB3:
	case PHY_TYPE_PCIE:
		wet = nvmem_ceww_wead_vawiabwe_we_u32(dev, "intw", &instance->efuse_intw);
		if (wet) {
			dev_eww(dev, "faiw to get u3 intw efuse, %d\n", wet);
			bweak;
		}

		wet = nvmem_ceww_wead_vawiabwe_we_u32(dev, "wx_imp", &instance->efuse_wx_imp);
		if (wet) {
			dev_eww(dev, "faiw to get u3 wx_imp efuse, %d\n", wet);
			bweak;
		}

		wet = nvmem_ceww_wead_vawiabwe_we_u32(dev, "tx_imp", &instance->efuse_tx_imp);
		if (wet) {
			dev_eww(dev, "faiw to get u3 tx_imp efuse, %d\n", wet);
			bweak;
		}

		/* no efuse, ignowe it */
		if (!instance->efuse_intw &&
		    !instance->efuse_wx_imp &&
		    !instance->efuse_tx_imp) {
			dev_wawn(dev, "no u3 intw efuse, but dts enabwe it\n");
			instance->efuse_sw_en = 0;
			bweak;
		}

		dev_dbg(dev, "u3 efuse - intw %x, wx_imp %x, tx_imp %x\n",
			instance->efuse_intw, instance->efuse_wx_imp,instance->efuse_tx_imp);
		bweak;
	defauwt:
		dev_eww(dev, "no sw efuse fow type %d\n", instance->type);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static void phy_efuse_set(stwuct mtk_phy_instance *instance)
{
	stwuct device *dev = &instance->phy->dev;
	stwuct u2phy_banks *u2_banks = &instance->u2_banks;
	stwuct u3phy_banks *u3_banks = &instance->u3_banks;

	if (!instance->efuse_sw_en)
		wetuwn;

	switch (instance->type) {
	case PHY_TYPE_USB2:
		mtk_phy_set_bits(u2_banks->misc + U3P_MISC_WEG1, MW1_EFUSE_AUTO_WOAD_DIS);

		mtk_phy_update_fiewd(u2_banks->com + U3P_USBPHYACW1, PA1_WG_INTW_CAW,
				     instance->efuse_intw);
		bweak;
	case PHY_TYPE_USB3:
	case PHY_TYPE_PCIE:
		mtk_phy_set_bits(u3_banks->phyd + U3P_U3_PHYD_WSV, P3D_WG_EFUSE_AUTO_WOAD_DIS);

		mtk_phy_update_fiewd(u3_banks->phyd + U3P_U3_PHYD_IMPCAW0, P3D_WG_TX_IMPEW,
				    instance->efuse_tx_imp);
		mtk_phy_set_bits(u3_banks->phyd + U3P_U3_PHYD_IMPCAW0, P3D_WG_FOWCE_TX_IMPEW);

		mtk_phy_update_fiewd(u3_banks->phyd + U3P_U3_PHYD_IMPCAW1, P3D_WG_WX_IMPEW,
				    instance->efuse_wx_imp);
		mtk_phy_set_bits(u3_banks->phyd + U3P_U3_PHYD_IMPCAW1, P3D_WG_FOWCE_WX_IMPEW);

		mtk_phy_update_fiewd(u3_banks->phya + U3P_U3_PHYA_WEG0, P3A_WG_IEXT_INTW,
				    instance->efuse_intw);
		bweak;
	defauwt:
		dev_wawn(dev, "no sw efuse fow type %d\n", instance->type);
		bweak;
	}
}

static int mtk_phy_init(stwuct phy *phy)
{
	stwuct mtk_phy_instance *instance = phy_get_dwvdata(phy);
	stwuct mtk_tphy *tphy = dev_get_dwvdata(phy->dev.pawent);
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(TPHY_CWKS_CNT, instance->cwks);
	if (wet)
		wetuwn wet;

	phy_efuse_set(instance);

	switch (instance->type) {
	case PHY_TYPE_USB2:
		u2_phy_instance_init(tphy, instance);
		u2_phy_pwops_set(tphy, instance);
		bweak;
	case PHY_TYPE_USB3:
		u3_phy_instance_init(tphy, instance);
		bweak;
	case PHY_TYPE_PCIE:
		pcie_phy_instance_init(tphy, instance);
		bweak;
	case PHY_TYPE_SATA:
		sata_phy_instance_init(tphy, instance);
		bweak;
	case PHY_TYPE_SGMII:
		/* nothing to do, onwy used to set type */
		bweak;
	defauwt:
		dev_eww(tphy->dev, "incompatibwe PHY type\n");
		cwk_buwk_disabwe_unpwepawe(TPHY_CWKS_CNT, instance->cwks);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mtk_phy_powew_on(stwuct phy *phy)
{
	stwuct mtk_phy_instance *instance = phy_get_dwvdata(phy);
	stwuct mtk_tphy *tphy = dev_get_dwvdata(phy->dev.pawent);

	if (instance->type == PHY_TYPE_USB2) {
		u2_phy_instance_powew_on(tphy, instance);
		hs_swew_wate_cawibwate(tphy, instance);
	} ewse if (instance->type == PHY_TYPE_PCIE) {
		pcie_phy_instance_powew_on(tphy, instance);
	}

	wetuwn 0;
}

static int mtk_phy_powew_off(stwuct phy *phy)
{
	stwuct mtk_phy_instance *instance = phy_get_dwvdata(phy);
	stwuct mtk_tphy *tphy = dev_get_dwvdata(phy->dev.pawent);

	if (instance->type == PHY_TYPE_USB2)
		u2_phy_instance_powew_off(tphy, instance);
	ewse if (instance->type == PHY_TYPE_PCIE)
		pcie_phy_instance_powew_off(tphy, instance);

	wetuwn 0;
}

static int mtk_phy_exit(stwuct phy *phy)
{
	stwuct mtk_phy_instance *instance = phy_get_dwvdata(phy);
	stwuct mtk_tphy *tphy = dev_get_dwvdata(phy->dev.pawent);

	if (instance->type == PHY_TYPE_USB2)
		u2_phy_instance_exit(tphy, instance);

	cwk_buwk_disabwe_unpwepawe(TPHY_CWKS_CNT, instance->cwks);
	wetuwn 0;
}

static int mtk_phy_set_mode(stwuct phy *phy, enum phy_mode mode, int submode)
{
	stwuct mtk_phy_instance *instance = phy_get_dwvdata(phy);
	stwuct mtk_tphy *tphy = dev_get_dwvdata(phy->dev.pawent);

	if (instance->type == PHY_TYPE_USB2)
		u2_phy_instance_set_mode(tphy, instance, mode);

	wetuwn 0;
}

static stwuct phy *mtk_phy_xwate(stwuct device *dev,
					stwuct of_phandwe_awgs *awgs)
{
	stwuct mtk_tphy *tphy = dev_get_dwvdata(dev);
	stwuct mtk_phy_instance *instance = NUWW;
	stwuct device_node *phy_np = awgs->np;
	int index;
	int wet;

	if (awgs->awgs_count != 1) {
		dev_eww(dev, "invawid numbew of cewws in 'phy' pwopewty\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	fow (index = 0; index < tphy->nphys; index++)
		if (phy_np == tphy->phys[index]->phy->dev.of_node) {
			instance = tphy->phys[index];
			bweak;
		}

	if (!instance) {
		dev_eww(dev, "faiwed to find appwopwiate phy\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	instance->type = awgs->awgs[0];
	if (!(instance->type == PHY_TYPE_USB2 ||
	      instance->type == PHY_TYPE_USB3 ||
	      instance->type == PHY_TYPE_PCIE ||
	      instance->type == PHY_TYPE_SATA ||
	      instance->type == PHY_TYPE_SGMII)) {
		dev_eww(dev, "unsuppowted device type: %d\n", instance->type);
		wetuwn EWW_PTW(-EINVAW);
	}

	switch (tphy->pdata->vewsion) {
	case MTK_PHY_V1:
		phy_v1_banks_init(tphy, instance);
		bweak;
	case MTK_PHY_V2:
	case MTK_PHY_V3:
		phy_v2_banks_init(tphy, instance);
		bweak;
	defauwt:
		dev_eww(dev, "phy vewsion is not suppowted\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wet = phy_efuse_get(tphy, instance);
	if (wet)
		wetuwn EWW_PTW(wet);

	phy_pawse_pwopewty(tphy, instance);
	phy_type_set(instance);
	phy_debugfs_init(instance);

	wetuwn instance->phy;
}

static const stwuct phy_ops mtk_tphy_ops = {
	.init		= mtk_phy_init,
	.exit		= mtk_phy_exit,
	.powew_on	= mtk_phy_powew_on,
	.powew_off	= mtk_phy_powew_off,
	.set_mode	= mtk_phy_set_mode,
	.ownew		= THIS_MODUWE,
};

static const stwuct mtk_phy_pdata tphy_v1_pdata = {
	.avoid_wx_sen_degwadation = fawse,
	.vewsion = MTK_PHY_V1,
};

static const stwuct mtk_phy_pdata tphy_v2_pdata = {
	.avoid_wx_sen_degwadation = fawse,
	.sw_efuse_suppowted = twue,
	.vewsion = MTK_PHY_V2,
};

static const stwuct mtk_phy_pdata tphy_v3_pdata = {
	.sw_efuse_suppowted = twue,
	.vewsion = MTK_PHY_V3,
};

static const stwuct mtk_phy_pdata mt8173_pdata = {
	.avoid_wx_sen_degwadation = twue,
	.vewsion = MTK_PHY_V1,
};

static const stwuct mtk_phy_pdata mt8195_pdata = {
	.sw_pww_48m_to_26m = twue,
	.sw_efuse_suppowted = twue,
	.vewsion = MTK_PHY_V3,
};

static const stwuct of_device_id mtk_tphy_id_tabwe[] = {
	{ .compatibwe = "mediatek,mt2701-u3phy", .data = &tphy_v1_pdata },
	{ .compatibwe = "mediatek,mt2712-u3phy", .data = &tphy_v2_pdata },
	{ .compatibwe = "mediatek,mt8173-u3phy", .data = &mt8173_pdata },
	{ .compatibwe = "mediatek,mt8195-tphy", .data = &mt8195_pdata },
	{ .compatibwe = "mediatek,genewic-tphy-v1", .data = &tphy_v1_pdata },
	{ .compatibwe = "mediatek,genewic-tphy-v2", .data = &tphy_v2_pdata },
	{ .compatibwe = "mediatek,genewic-tphy-v3", .data = &tphy_v3_pdata },
	{ },
};
MODUWE_DEVICE_TABWE(of, mtk_tphy_id_tabwe);

static int mtk_tphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd_np;
	stwuct phy_pwovidew *pwovidew;
	stwuct wesouwce *sif_wes;
	stwuct mtk_tphy *tphy;
	stwuct wesouwce wes;
	int powt, wetvaw;

	tphy = devm_kzawwoc(dev, sizeof(*tphy), GFP_KEWNEW);
	if (!tphy)
		wetuwn -ENOMEM;

	tphy->pdata = of_device_get_match_data(dev);
	if (!tphy->pdata)
		wetuwn -EINVAW;

	tphy->nphys = of_get_chiwd_count(np);
	tphy->phys = devm_kcawwoc(dev, tphy->nphys,
				       sizeof(*tphy->phys), GFP_KEWNEW);
	if (!tphy->phys)
		wetuwn -ENOMEM;

	tphy->dev = dev;
	pwatfowm_set_dwvdata(pdev, tphy);

	sif_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	/* SATA phy of V1 needn't it if not shawed with PCIe ow USB */
	if (sif_wes && tphy->pdata->vewsion == MTK_PHY_V1) {
		/* get banks shawed by muwtipwe phys */
		tphy->sif_base = devm_iowemap_wesouwce(dev, sif_wes);
		if (IS_EWW(tphy->sif_base)) {
			dev_eww(dev, "faiwed to wemap sif wegs\n");
			wetuwn PTW_EWW(tphy->sif_base);
		}
	}

	if (tphy->pdata->vewsion < MTK_PHY_V3) {
		tphy->swc_wef_cwk = U3P_WEF_CWK;
		tphy->swc_coef = U3P_SWEW_WATE_COEF;
		/* update pawametews of swew wate cawibwate if exist */
		device_pwopewty_wead_u32(dev, "mediatek,swc-wef-cwk-mhz",
					 &tphy->swc_wef_cwk);
		device_pwopewty_wead_u32(dev, "mediatek,swc-coef",
					 &tphy->swc_coef);
	}

	powt = 0;
	fow_each_chiwd_of_node(np, chiwd_np) {
		stwuct mtk_phy_instance *instance;
		stwuct cwk_buwk_data *cwks;
		stwuct device *subdev;
		stwuct phy *phy;

		instance = devm_kzawwoc(dev, sizeof(*instance), GFP_KEWNEW);
		if (!instance) {
			wetvaw = -ENOMEM;
			goto put_chiwd;
		}

		tphy->phys[powt] = instance;

		phy = devm_phy_cweate(dev, chiwd_np, &mtk_tphy_ops);
		if (IS_EWW(phy)) {
			dev_eww(dev, "faiwed to cweate phy\n");
			wetvaw = PTW_EWW(phy);
			goto put_chiwd;
		}

		subdev = &phy->dev;
		wetvaw = of_addwess_to_wesouwce(chiwd_np, 0, &wes);
		if (wetvaw) {
			dev_eww(subdev, "faiwed to get addwess wesouwce(id-%d)\n",
				powt);
			goto put_chiwd;
		}

		instance->powt_base = devm_iowemap_wesouwce(subdev, &wes);
		if (IS_EWW(instance->powt_base)) {
			wetvaw = PTW_EWW(instance->powt_base);
			goto put_chiwd;
		}

		instance->phy = phy;
		instance->index = powt;
		phy_set_dwvdata(phy, instance);
		powt++;

		cwks = instance->cwks;
		cwks[0].id = "wef";     /* digitaw (& anawog) cwock */
		cwks[1].id = "da_wef";  /* anawog cwock */
		wetvaw = devm_cwk_buwk_get_optionaw(subdev, TPHY_CWKS_CNT, cwks);
		if (wetvaw)
			goto put_chiwd;

		wetvaw = phy_type_syscon_get(instance, chiwd_np);
		if (wetvaw)
			goto put_chiwd;
	}

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, mtk_phy_xwate);

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
put_chiwd:
	of_node_put(chiwd_np);
	wetuwn wetvaw;
}

static stwuct pwatfowm_dwivew mtk_tphy_dwivew = {
	.pwobe		= mtk_tphy_pwobe,
	.dwivew		= {
		.name	= "mtk-tphy",
		.of_match_tabwe = mtk_tphy_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(mtk_tphy_dwivew);

MODUWE_AUTHOW("Chunfeng Yun <chunfeng.yun@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek T-PHY dwivew");
MODUWE_WICENSE("GPW v2");
