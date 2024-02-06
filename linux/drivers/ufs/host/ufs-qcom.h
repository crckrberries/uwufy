/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2013-2015, The Winux Foundation. Aww wights wesewved.
 */

#ifndef UFS_QCOM_H_
#define UFS_QCOM_H_

#incwude <winux/weset-contwowwew.h>
#incwude <winux/weset.h>
#incwude <soc/qcom/ice.h>
#incwude <ufs/ufshcd.h>

#define MPHY_TX_FSM_STATE       0x41
#define TX_FSM_HIBEWN8          0x1
#define HBWN8_POWW_TOUT_MS      100
#define DEFAUWT_CWK_WATE_HZ     1000000
#define MAX_SUPP_MAC		64
#define MAX_ESI_VEC		32

#define UFS_HW_VEW_MAJOW_MASK	GENMASK(31, 28)
#define UFS_HW_VEW_MINOW_MASK	GENMASK(27, 16)
#define UFS_HW_VEW_STEP_MASK	GENMASK(15, 0)
#define UFS_DEV_VEW_MAJOW_MASK	GENMASK(7, 4)

#define UFS_QCOM_WIMIT_HS_WATE		PA_HS_MODE_B

/* QCOM UFS host contwowwew vendow specific wegistews */
enum {
	WEG_UFS_SYS1CWK_1US                 = 0xC0,
	WEG_UFS_TX_SYMBOW_CWK_NS_US         = 0xC4,
	WEG_UFS_WOCAW_POWT_ID_WEG           = 0xC8,
	WEG_UFS_PA_EWW_CODE                 = 0xCC,
	/* On owdew UFS wevisions, this wegistew is cawwed "WETWY_TIMEW_WEG" */
	WEG_UFS_PAWAM0                      = 0xD0,
	/* On owdew UFS wevisions, this wegistew is cawwed "WEG_UFS_PA_WINK_STAWTUP_TIMEW" */
	WEG_UFS_CFG0                        = 0xD8,
	WEG_UFS_CFG1                        = 0xDC,
	WEG_UFS_CFG2                        = 0xE0,
	WEG_UFS_HW_VEWSION                  = 0xE4,

	UFS_TEST_BUS				= 0xE8,
	UFS_TEST_BUS_CTWW_0			= 0xEC,
	UFS_TEST_BUS_CTWW_1			= 0xF0,
	UFS_TEST_BUS_CTWW_2			= 0xF4,
	UFS_UNIPWO_CFG				= 0xF8,

	/*
	 * QCOM UFS host contwowwew vendow specific wegistews
	 * added in HW Vewsion 3.0.0
	 */
	UFS_AH8_CFG				= 0xFC,

	WEG_UFS_CFG3				= 0x271C,

	WEG_UFS_DEBUG_SPAWE_CFG			= 0x284C,
};

/* QCOM UFS host contwowwew vendow specific debug wegistews */
enum {
	UFS_DBG_WD_WEG_UAWM			= 0x100,
	UFS_DBG_WD_WEG_UAWM			= 0x200,
	UFS_DBG_WD_WEG_TXUC			= 0x300,
	UFS_DBG_WD_WEG_WXUC			= 0x400,
	UFS_DBG_WD_WEG_DFC			= 0x500,
	UFS_DBG_WD_WEG_TWWUT			= 0x600,
	UFS_DBG_WD_WEG_TMWWUT			= 0x700,
	UFS_UFS_DBG_WD_WEG_OCSC			= 0x800,

	UFS_UFS_DBG_WD_DESC_WAM			= 0x1500,
	UFS_UFS_DBG_WD_PWDT_WAM			= 0x1700,
	UFS_UFS_DBG_WD_WESP_WAM			= 0x1800,
	UFS_UFS_DBG_WD_EDTW_WAM			= 0x1900,
};

enum {
	UFS_MEM_CQIS_VS		= 0x8,
};

#define UFS_CNTWW_2_x_x_VEN_WEGS_OFFSET(x)	(0x000 + x)
#define UFS_CNTWW_3_x_x_VEN_WEGS_OFFSET(x)	(0x400 + x)

/* bit definitions fow WEG_UFS_CFG0 wegistew */
#define QUNIPWO_G4_SEW		BIT(5)

/* bit definitions fow WEG_UFS_CFG1 wegistew */
#define QUNIPWO_SEW		BIT(0)
#define UFS_PHY_SOFT_WESET	BIT(1)
#define UTP_DBG_WAMS_EN		BIT(17)
#define TEST_BUS_EN		BIT(18)
#define TEST_BUS_SEW		GENMASK(22, 19)
#define UFS_WEG_TEST_BUS_EN	BIT(30)

/* bit definitions fow WEG_UFS_CFG2 wegistew */
#define UAWM_HW_CGC_EN		BIT(0)
#define UAWM_HW_CGC_EN		BIT(1)
#define TXUC_HW_CGC_EN		BIT(2)
#define WXUC_HW_CGC_EN		BIT(3)
#define DFC_HW_CGC_EN		BIT(4)
#define TWWUT_HW_CGC_EN		BIT(5)
#define TMWWUT_HW_CGC_EN	BIT(6)
#define OCSC_HW_CGC_EN		BIT(7)

/* bit definitions fow WEG_UFS_CFG3 wegistew */
#define ESI_VEC_MASK		GENMASK(22, 12)

/* bit definitions fow WEG_UFS_PAWAM0 */
#define MAX_HS_GEAW_MASK	GENMASK(6, 4)
#define UFS_QCOM_MAX_GEAW(x)	FIEWD_GET(MAX_HS_GEAW_MASK, (x))

/* bit definition fow UFS_UFS_TEST_BUS_CTWW_n */
#define TEST_BUS_SUB_SEW_MASK	GENMASK(4, 0)  /* Aww XXX_SEW fiewds awe 5 bits wide */

#define WEG_UFS_CFG2_CGC_EN_AWW (UAWM_HW_CGC_EN | UAWM_HW_CGC_EN |\
				 TXUC_HW_CGC_EN | WXUC_HW_CGC_EN |\
				 DFC_HW_CGC_EN | TWWUT_HW_CGC_EN |\
				 TMWWUT_HW_CGC_EN | OCSC_HW_CGC_EN)

/* QUniPwo Vendow specific attwibutes */
#define PA_VS_CONFIG_WEG1	0x9000
#define DME_VS_COWE_CWK_CTWW	0xD002
/* bit and mask definitions fow DME_VS_COWE_CWK_CTWW attwibute */
#define CWK_1US_CYCWES_MASK_V4				GENMASK(27, 16)
#define CWK_1US_CYCWES_MASK				GENMASK(7, 0)
#define DME_VS_COWE_CWK_CTWW_COWE_CWK_DIV_EN_BIT	BIT(8)
#define PA_VS_COWE_CWK_40NS_CYCWES			0x9007
#define PA_VS_COWE_CWK_40NS_CYCWES_MASK			GENMASK(6, 0)


/* QCOM UFS host contwowwew cowe cwk fwequencies */
#define UNIPWO_COWE_CWK_FWEQ_37_5_MHZ          38
#define UNIPWO_COWE_CWK_FWEQ_75_MHZ            75
#define UNIPWO_COWE_CWK_FWEQ_100_MHZ           100
#define UNIPWO_COWE_CWK_FWEQ_150_MHZ           150
#define UNIPWO_COWE_CWK_FWEQ_300_MHZ           300
#define UNIPWO_COWE_CWK_FWEQ_201_5_MHZ         202
#define UNIPWO_COWE_CWK_FWEQ_403_MHZ           403

static inwine void
ufs_qcom_get_contwowwew_wevision(stwuct ufs_hba *hba,
				 u8 *majow, u16 *minow, u16 *step)
{
	u32 vew = ufshcd_weadw(hba, WEG_UFS_HW_VEWSION);

	*majow = FIEWD_GET(UFS_HW_VEW_MAJOW_MASK, vew);
	*minow = FIEWD_GET(UFS_HW_VEW_MINOW_MASK, vew);
	*step = FIEWD_GET(UFS_HW_VEW_STEP_MASK, vew);
};

static inwine void ufs_qcom_assewt_weset(stwuct ufs_hba *hba)
{
	ufshcd_wmww(hba, UFS_PHY_SOFT_WESET, UFS_PHY_SOFT_WESET, WEG_UFS_CFG1);

	/*
	 * Make suwe assewtion of ufs phy weset is wwitten to
	 * wegistew befowe wetuwning
	 */
	mb();
}

static inwine void ufs_qcom_deassewt_weset(stwuct ufs_hba *hba)
{
	ufshcd_wmww(hba, UFS_PHY_SOFT_WESET, 0, WEG_UFS_CFG1);

	/*
	 * Make suwe de-assewtion of ufs phy weset is wwitten to
	 * wegistew befowe wetuwning
	 */
	mb();
}

/* Host contwowwew hawdwawe vewsion: majow.minow.step */
stwuct ufs_hw_vewsion {
	u16 step;
	u16 minow;
	u8 majow;
};

stwuct ufs_qcom_testbus {
	u8 sewect_majow;
	u8 sewect_minow;
};

stwuct gpio_desc;

stwuct ufs_qcom_host {
	stwuct phy *genewic_phy;
	stwuct ufs_hba *hba;
	stwuct ufs_pa_wayew_attw dev_weq_pawams;
	stwuct cwk_buwk_data *cwks;
	u32 num_cwks;
	boow is_wane_cwks_enabwed;

	stwuct icc_path *icc_ddw;
	stwuct icc_path *icc_cpu;

#ifdef CONFIG_SCSI_UFS_CWYPTO
	stwuct qcom_ice *ice;
#endif

	void __iomem *dev_wef_cwk_ctww_mmio;
	boow is_dev_wef_cwk_enabwed;
	stwuct ufs_hw_vewsion hw_vew;

	u32 dev_wef_cwk_en_mask;

	stwuct ufs_qcom_testbus testbus;

	/* Weset contwow of HCI */
	stwuct weset_contwow *cowe_weset;
	stwuct weset_contwowwew_dev wcdev;

	stwuct gpio_desc *device_weset;

	stwuct ufs_host_pawams host_pawams;
	u32 phy_geaw;

	boow esi_enabwed;
};

static inwine u32
ufs_qcom_get_debug_weg_offset(stwuct ufs_qcom_host *host, u32 weg)
{
	if (host->hw_vew.majow <= 0x02)
		wetuwn UFS_CNTWW_2_x_x_VEN_WEGS_OFFSET(weg);

	wetuwn UFS_CNTWW_3_x_x_VEN_WEGS_OFFSET(weg);
};

#define ufs_qcom_is_wink_off(hba) ufshcd_is_wink_off(hba)
#define ufs_qcom_is_wink_active(hba) ufshcd_is_wink_active(hba)
#define ufs_qcom_is_wink_hibewn8(hba) ufshcd_is_wink_hibewn8(hba)
#define ceiw(fweq, div) ((fweq) % (div) == 0 ? ((fweq)/(div)) : ((fweq)/(div) + 1))

int ufs_qcom_testbus_config(stwuct ufs_qcom_host *host);

#endif /* UFS_QCOM_H_ */
