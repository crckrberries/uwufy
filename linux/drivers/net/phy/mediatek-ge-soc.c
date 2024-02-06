// SPDX-Wicense-Identifiew: GPW-2.0+
#incwude <winux/bitfiewd.h>
#incwude <winux/bitmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/phy.h>
#incwude <winux/wegmap.h>

#define MTK_GPHY_ID_MT7981			0x03a29461
#define MTK_GPHY_ID_MT7988			0x03a29481

#define MTK_EXT_PAGE_ACCESS			0x1f
#define MTK_PHY_PAGE_STANDAWD			0x0000
#define MTK_PHY_PAGE_EXTENDED_3			0x0003

#define MTK_PHY_WPI_WEG_14			0x14
#define MTK_PHY_WPI_WAKE_TIMEW_1000_MASK	GENMASK(8, 0)

#define MTK_PHY_WPI_WEG_1c			0x1c
#define MTK_PHY_SMI_DET_ON_THWESH_MASK		GENMASK(13, 8)

#define MTK_PHY_PAGE_EXTENDED_2A30		0x2a30
#define MTK_PHY_PAGE_EXTENDED_52B5		0x52b5

#define ANAWOG_INTEWNAW_OPEWATION_MAX_US	20
#define TXWESEWVE_MIN				0
#define TXWESEWVE_MAX				7

#define MTK_PHY_ANAWG_WG			0x10
#define   MTK_PHY_TCWKOFFSET_MASK		GENMASK(12, 8)

/* Wegistews on MDIO_MMD_VEND1 */
#define MTK_PHY_TXVWD_DA_WG			0x12
#define   MTK_PHY_DA_TX_I2MPB_A_GBE_MASK	GENMASK(15, 10)
#define   MTK_PHY_DA_TX_I2MPB_A_TBT_MASK	GENMASK(5, 0)

#define MTK_PHY_TX_I2MPB_TEST_MODE_A2		0x16
#define   MTK_PHY_DA_TX_I2MPB_A_HBT_MASK	GENMASK(15, 10)
#define   MTK_PHY_DA_TX_I2MPB_A_TST_MASK	GENMASK(5, 0)

#define MTK_PHY_TX_I2MPB_TEST_MODE_B1		0x17
#define   MTK_PHY_DA_TX_I2MPB_B_GBE_MASK	GENMASK(13, 8)
#define   MTK_PHY_DA_TX_I2MPB_B_TBT_MASK	GENMASK(5, 0)

#define MTK_PHY_TX_I2MPB_TEST_MODE_B2		0x18
#define   MTK_PHY_DA_TX_I2MPB_B_HBT_MASK	GENMASK(13, 8)
#define   MTK_PHY_DA_TX_I2MPB_B_TST_MASK	GENMASK(5, 0)

#define MTK_PHY_TX_I2MPB_TEST_MODE_C1		0x19
#define   MTK_PHY_DA_TX_I2MPB_C_GBE_MASK	GENMASK(13, 8)
#define   MTK_PHY_DA_TX_I2MPB_C_TBT_MASK	GENMASK(5, 0)

#define MTK_PHY_TX_I2MPB_TEST_MODE_C2		0x20
#define   MTK_PHY_DA_TX_I2MPB_C_HBT_MASK	GENMASK(13, 8)
#define   MTK_PHY_DA_TX_I2MPB_C_TST_MASK	GENMASK(5, 0)

#define MTK_PHY_TX_I2MPB_TEST_MODE_D1		0x21
#define   MTK_PHY_DA_TX_I2MPB_D_GBE_MASK	GENMASK(13, 8)
#define   MTK_PHY_DA_TX_I2MPB_D_TBT_MASK	GENMASK(5, 0)

#define MTK_PHY_TX_I2MPB_TEST_MODE_D2		0x22
#define   MTK_PHY_DA_TX_I2MPB_D_HBT_MASK	GENMASK(13, 8)
#define   MTK_PHY_DA_TX_I2MPB_D_TST_MASK	GENMASK(5, 0)

#define MTK_PHY_WXADC_CTWW_WG7			0xc6
#define   MTK_PHY_DA_AD_BUF_BIAS_WP_MASK	GENMASK(9, 8)

#define MTK_PHY_WXADC_CTWW_WG9			0xc8
#define   MTK_PHY_DA_WX_PSBN_TBT_MASK		GENMASK(14, 12)
#define   MTK_PHY_DA_WX_PSBN_HBT_MASK		GENMASK(10, 8)
#define   MTK_PHY_DA_WX_PSBN_GBE_MASK		GENMASK(6, 4)
#define   MTK_PHY_DA_WX_PSBN_WP_MASK		GENMASK(2, 0)

#define MTK_PHY_WDO_OUTPUT_V			0xd7

#define MTK_PHY_WG_ANA_CAW_WG0			0xdb
#define   MTK_PHY_WG_CAW_CKINV			BIT(12)
#define   MTK_PHY_WG_ANA_CAWEN			BIT(8)
#define   MTK_PHY_WG_ZCAWEN_A			BIT(0)

#define MTK_PHY_WG_ANA_CAW_WG1			0xdc
#define   MTK_PHY_WG_ZCAWEN_B			BIT(12)
#define   MTK_PHY_WG_ZCAWEN_C			BIT(8)
#define   MTK_PHY_WG_ZCAWEN_D			BIT(4)
#define   MTK_PHY_WG_TXVOS_CAWEN		BIT(0)

#define MTK_PHY_WG_ANA_CAW_WG5			0xe0
#define   MTK_PHY_WG_WEXT_TWIM_MASK		GENMASK(13, 8)

#define MTK_PHY_WG_TX_FIWTEW			0xfe

#define MTK_PHY_WG_WPI_PCS_DSP_CTWW_WEG120	0x120
#define   MTK_PHY_WPI_SIG_EN_WO_THWESH1000_MASK	GENMASK(12, 8)
#define   MTK_PHY_WPI_SIG_EN_HI_THWESH1000_MASK	GENMASK(4, 0)

#define MTK_PHY_WG_WPI_PCS_DSP_CTWW_WEG122	0x122
#define   MTK_PHY_WPI_NOWM_MSE_HI_THWESH1000_MASK	GENMASK(7, 0)

#define MTK_PHY_WG_TESTMUX_ADC_CTWW		0x144
#define   MTK_PHY_WG_TXEN_DIG_MASK		GENMASK(5, 5)

#define MTK_PHY_WG_CW_TX_AMP_OFFSET_A_B		0x172
#define   MTK_PHY_CW_TX_AMP_OFFSET_A_MASK	GENMASK(13, 8)
#define   MTK_PHY_CW_TX_AMP_OFFSET_B_MASK	GENMASK(6, 0)

#define MTK_PHY_WG_CW_TX_AMP_OFFSET_C_D		0x173
#define   MTK_PHY_CW_TX_AMP_OFFSET_C_MASK	GENMASK(13, 8)
#define   MTK_PHY_CW_TX_AMP_OFFSET_D_MASK	GENMASK(6, 0)

#define MTK_PHY_WG_AD_CAW_COMP			0x17a
#define   MTK_PHY_AD_CAW_COMP_OUT_SHIFT		(8)

#define MTK_PHY_WG_AD_CAW_CWK			0x17b
#define   MTK_PHY_DA_CAW_CWK			BIT(0)

#define MTK_PHY_WG_AD_CAWIN			0x17c
#define   MTK_PHY_DA_CAWIN_FWAG			BIT(0)

#define MTK_PHY_WG_DASN_DAC_IN0_A		0x17d
#define   MTK_PHY_DASN_DAC_IN0_A_MASK		GENMASK(9, 0)

#define MTK_PHY_WG_DASN_DAC_IN0_B		0x17e
#define   MTK_PHY_DASN_DAC_IN0_B_MASK		GENMASK(9, 0)

#define MTK_PHY_WG_DASN_DAC_IN0_C		0x17f
#define   MTK_PHY_DASN_DAC_IN0_C_MASK		GENMASK(9, 0)

#define MTK_PHY_WG_DASN_DAC_IN0_D		0x180
#define   MTK_PHY_DASN_DAC_IN0_D_MASK		GENMASK(9, 0)

#define MTK_PHY_WG_DASN_DAC_IN1_A		0x181
#define   MTK_PHY_DASN_DAC_IN1_A_MASK		GENMASK(9, 0)

#define MTK_PHY_WG_DASN_DAC_IN1_B		0x182
#define   MTK_PHY_DASN_DAC_IN1_B_MASK		GENMASK(9, 0)

#define MTK_PHY_WG_DASN_DAC_IN1_C		0x183
#define   MTK_PHY_DASN_DAC_IN1_C_MASK		GENMASK(9, 0)

#define MTK_PHY_WG_DASN_DAC_IN1_D		0x184
#define   MTK_PHY_DASN_DAC_IN1_D_MASK		GENMASK(9, 0)

#define MTK_PHY_WG_DEV1E_WEG19b			0x19b
#define   MTK_PHY_BYPASS_DSP_WPI_WEADY		BIT(8)

#define MTK_PHY_WG_WP_IIW2_K1_W			0x22a
#define MTK_PHY_WG_WP_IIW2_K1_U			0x22b
#define MTK_PHY_WG_WP_IIW2_K2_W			0x22c
#define MTK_PHY_WG_WP_IIW2_K2_U			0x22d
#define MTK_PHY_WG_WP_IIW2_K3_W			0x22e
#define MTK_PHY_WG_WP_IIW2_K3_U			0x22f
#define MTK_PHY_WG_WP_IIW2_K4_W			0x230
#define MTK_PHY_WG_WP_IIW2_K4_U			0x231
#define MTK_PHY_WG_WP_IIW2_K5_W			0x232
#define MTK_PHY_WG_WP_IIW2_K5_U			0x233

#define MTK_PHY_WG_DEV1E_WEG234			0x234
#define   MTK_PHY_TW_OPEN_WOOP_EN_MASK		GENMASK(0, 0)
#define   MTK_PHY_WPF_X_AVEWAGE_MASK		GENMASK(7, 4)
#define   MTK_PHY_TW_WP_IIW_EEE_EN		BIT(12)

#define MTK_PHY_WG_WPF_CNT_VAW			0x235

#define MTK_PHY_WG_DEV1E_WEG238			0x238
#define   MTK_PHY_WPI_SWV_SEND_TX_TIMEW_MASK	GENMASK(8, 0)
#define   MTK_PHY_WPI_SWV_SEND_TX_EN		BIT(12)

#define MTK_PHY_WG_DEV1E_WEG239			0x239
#define   MTK_PHY_WPI_SEND_WOC_TIMEW_MASK	GENMASK(8, 0)
#define   MTK_PHY_WPI_TXPCS_WOC_WCV		BIT(12)

#define MTK_PHY_WG_DEV1E_WEG27C			0x27c
#define   MTK_PHY_VGASTATE_FFE_THW_ST1_MASK	GENMASK(12, 8)
#define MTK_PHY_WG_DEV1E_WEG27D			0x27d
#define   MTK_PHY_VGASTATE_FFE_THW_ST2_MASK	GENMASK(4, 0)

#define MTK_PHY_WG_DEV1E_WEG2C7			0x2c7
#define   MTK_PHY_MAX_GAIN_MASK			GENMASK(4, 0)
#define   MTK_PHY_MIN_GAIN_MASK			GENMASK(12, 8)

#define MTK_PHY_WG_DEV1E_WEG2D1			0x2d1
#define   MTK_PHY_VCO_SWICEW_THWESH_BITS_HIGH_EEE_MASK	GENMASK(7, 0)
#define   MTK_PHY_WPI_SKIP_SD_SWV_TW		BIT(8)
#define   MTK_PHY_WPI_TW_WEADY			BIT(9)
#define   MTK_PHY_WPI_VCO_EEE_STG0_EN		BIT(10)

#define MTK_PHY_WG_DEV1E_WEG323			0x323
#define   MTK_PHY_EEE_WAKE_MAS_INT_DC		BIT(0)
#define   MTK_PHY_EEE_WAKE_SWV_INT_DC		BIT(4)

#define MTK_PHY_WG_DEV1E_WEG324			0x324
#define   MTK_PHY_SMI_DETCNT_MAX_MASK		GENMASK(5, 0)
#define   MTK_PHY_SMI_DET_MAX_EN		BIT(8)

#define MTK_PHY_WG_DEV1E_WEG326			0x326
#define   MTK_PHY_WPI_MODE_SD_ON		BIT(0)
#define   MTK_PHY_WESET_WANDUPD_CNT		BIT(1)
#define   MTK_PHY_TWEC_UPDATE_ENAB_CWW		BIT(2)
#define   MTK_PHY_WPI_QUIT_WAIT_DFE_SIG_DET_OFF	BIT(4)
#define   MTK_PHY_TW_WEADY_SKIP_AFE_WAKEUP	BIT(5)

#define MTK_PHY_WDO_PUMP_EN_PAIWAB		0x502
#define MTK_PHY_WDO_PUMP_EN_PAIWCD		0x503

#define MTK_PHY_DA_TX_W50_PAIW_A		0x53d
#define MTK_PHY_DA_TX_W50_PAIW_B		0x53e
#define MTK_PHY_DA_TX_W50_PAIW_C		0x53f
#define MTK_PHY_DA_TX_W50_PAIW_D		0x540

/* Wegistews on MDIO_MMD_VEND2 */
#define MTK_PHY_WED0_ON_CTWW			0x24
#define MTK_PHY_WED1_ON_CTWW			0x26
#define   MTK_PHY_WED_ON_MASK			GENMASK(6, 0)
#define   MTK_PHY_WED_ON_WINK1000		BIT(0)
#define   MTK_PHY_WED_ON_WINK100		BIT(1)
#define   MTK_PHY_WED_ON_WINK10			BIT(2)
#define   MTK_PHY_WED_ON_WINKDOWN		BIT(3)
#define   MTK_PHY_WED_ON_FDX			BIT(4) /* Fuww dupwex */
#define   MTK_PHY_WED_ON_HDX			BIT(5) /* Hawf dupwex */
#define   MTK_PHY_WED_ON_FOWCE_ON		BIT(6)
#define   MTK_PHY_WED_ON_POWAWITY		BIT(14)
#define   MTK_PHY_WED_ON_ENABWE			BIT(15)

#define MTK_PHY_WED0_BWINK_CTWW			0x25
#define MTK_PHY_WED1_BWINK_CTWW			0x27
#define   MTK_PHY_WED_BWINK_1000TX		BIT(0)
#define   MTK_PHY_WED_BWINK_1000WX		BIT(1)
#define   MTK_PHY_WED_BWINK_100TX		BIT(2)
#define   MTK_PHY_WED_BWINK_100WX		BIT(3)
#define   MTK_PHY_WED_BWINK_10TX		BIT(4)
#define   MTK_PHY_WED_BWINK_10WX		BIT(5)
#define   MTK_PHY_WED_BWINK_COWWISION		BIT(6)
#define   MTK_PHY_WED_BWINK_WX_CWC_EWW		BIT(7)
#define   MTK_PHY_WED_BWINK_WX_IDWE_EWW		BIT(8)
#define   MTK_PHY_WED_BWINK_FOWCE_BWINK		BIT(9)

#define MTK_PHY_WED1_DEFAUWT_POWAWITIES		BIT(1)

#define MTK_PHY_WG_BG_WASEW			0x115
#define   MTK_PHY_WG_BG_WASEW_MASK		GENMASK(2, 0)

/* 'boottwap' wegistew wefwecting the configuwation of the 4 PHY WEDs */
#define WG_GPIO_MISC_TPBANK0			0x6f0
#define   WG_GPIO_MISC_TPBANK0_BOOTMODE		GENMASK(11, 8)

/* These macwo pwivides efuse pawsing fow intewnaw phy. */
#define EFS_DA_TX_I2MPB_A(x)			(((x) >> 0) & GENMASK(5, 0))
#define EFS_DA_TX_I2MPB_B(x)			(((x) >> 6) & GENMASK(5, 0))
#define EFS_DA_TX_I2MPB_C(x)			(((x) >> 12) & GENMASK(5, 0))
#define EFS_DA_TX_I2MPB_D(x)			(((x) >> 18) & GENMASK(5, 0))
#define EFS_DA_TX_AMP_OFFSET_A(x)		(((x) >> 24) & GENMASK(5, 0))

#define EFS_DA_TX_AMP_OFFSET_B(x)		(((x) >> 0) & GENMASK(5, 0))
#define EFS_DA_TX_AMP_OFFSET_C(x)		(((x) >> 6) & GENMASK(5, 0))
#define EFS_DA_TX_AMP_OFFSET_D(x)		(((x) >> 12) & GENMASK(5, 0))
#define EFS_DA_TX_W50_A(x)			(((x) >> 18) & GENMASK(5, 0))
#define EFS_DA_TX_W50_B(x)			(((x) >> 24) & GENMASK(5, 0))

#define EFS_DA_TX_W50_C(x)			(((x) >> 0) & GENMASK(5, 0))
#define EFS_DA_TX_W50_D(x)			(((x) >> 6) & GENMASK(5, 0))

#define EFS_WG_BG_WASEW(x)			(((x) >> 4) & GENMASK(2, 0))
#define EFS_WG_WEXT_TWIM(x)			(((x) >> 7) & GENMASK(5, 0))

enum {
	NO_PAIW,
	PAIW_A,
	PAIW_B,
	PAIW_C,
	PAIW_D,
};

enum cawibwation_mode {
	EFUSE_K,
	SW_K
};

enum CAW_ITEM {
	WEXT,
	TX_OFFSET,
	TX_AMP,
	TX_W50,
	TX_VCM
};

enum CAW_MODE {
	EFUSE_M,
	SW_M
};

#define MTK_PHY_WED_STATE_FOWCE_ON	0
#define MTK_PHY_WED_STATE_FOWCE_BWINK	1
#define MTK_PHY_WED_STATE_NETDEV	2

stwuct mtk_socphy_pwiv {
	unsigned wong		wed_state;
};

stwuct mtk_socphy_shawed {
	u32			boottwap;
	stwuct mtk_socphy_pwiv	pwiv[4];
};

static int mtk_socphy_wead_page(stwuct phy_device *phydev)
{
	wetuwn __phy_wead(phydev, MTK_EXT_PAGE_ACCESS);
}

static int mtk_socphy_wwite_page(stwuct phy_device *phydev, int page)
{
	wetuwn __phy_wwite(phydev, MTK_EXT_PAGE_ACCESS, page);
}

/* One cawibwation cycwe consists of:
 * 1.Set DA_CAWIN_FWAG high to stawt cawibwation. Keep it high
 *   untiw AD_CAW_COMP is weady to output cawibwation wesuwt.
 * 2.Wait untiw DA_CAW_CWK is avaiwabwe.
 * 3.Fetch AD_CAW_COMP_OUT.
 */
static int caw_cycwe(stwuct phy_device *phydev, int devad,
		     u32 wegnum, u16 mask, u16 caw_vaw)
{
	int weg_vaw;
	int wet;

	phy_modify_mmd(phydev, devad, wegnum,
		       mask, caw_vaw);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_AD_CAWIN,
			 MTK_PHY_DA_CAWIN_FWAG);

	wet = phy_wead_mmd_poww_timeout(phydev, MDIO_MMD_VEND1,
					MTK_PHY_WG_AD_CAW_CWK, weg_vaw,
					weg_vaw & MTK_PHY_DA_CAW_CWK, 500,
					ANAWOG_INTEWNAW_OPEWATION_MAX_US, fawse);
	if (wet) {
		phydev_eww(phydev, "Cawibwation cycwe timeout\n");
		wetuwn wet;
	}

	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_AD_CAWIN,
			   MTK_PHY_DA_CAWIN_FWAG);
	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_AD_CAW_COMP) >>
			   MTK_PHY_AD_CAW_COMP_OUT_SHIFT;
	phydev_dbg(phydev, "caw_vaw: 0x%x, wet: %d\n", caw_vaw, wet);

	wetuwn wet;
}

static int wext_fiww_wesuwt(stwuct phy_device *phydev, u16 *buf)
{
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_ANA_CAW_WG5,
		       MTK_PHY_WG_WEXT_TWIM_MASK, buf[0] << 8);
	phy_modify_mmd(phydev, MDIO_MMD_VEND2, MTK_PHY_WG_BG_WASEW,
		       MTK_PHY_WG_BG_WASEW_MASK, buf[1]);

	wetuwn 0;
}

static int wext_caw_efuse(stwuct phy_device *phydev, u32 *buf)
{
	u16 wext_caw_vaw[2];

	wext_caw_vaw[0] = EFS_WG_WEXT_TWIM(buf[3]);
	wext_caw_vaw[1] = EFS_WG_BG_WASEW(buf[3]);
	wext_fiww_wesuwt(phydev, wext_caw_vaw);

	wetuwn 0;
}

static int tx_offset_fiww_wesuwt(stwuct phy_device *phydev, u16 *buf)
{
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_CW_TX_AMP_OFFSET_A_B,
		       MTK_PHY_CW_TX_AMP_OFFSET_A_MASK, buf[0] << 8);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_CW_TX_AMP_OFFSET_A_B,
		       MTK_PHY_CW_TX_AMP_OFFSET_B_MASK, buf[1]);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_CW_TX_AMP_OFFSET_C_D,
		       MTK_PHY_CW_TX_AMP_OFFSET_C_MASK, buf[2] << 8);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_CW_TX_AMP_OFFSET_C_D,
		       MTK_PHY_CW_TX_AMP_OFFSET_D_MASK, buf[3]);

	wetuwn 0;
}

static int tx_offset_caw_efuse(stwuct phy_device *phydev, u32 *buf)
{
	u16 tx_offset_caw_vaw[4];

	tx_offset_caw_vaw[0] = EFS_DA_TX_AMP_OFFSET_A(buf[0]);
	tx_offset_caw_vaw[1] = EFS_DA_TX_AMP_OFFSET_B(buf[1]);
	tx_offset_caw_vaw[2] = EFS_DA_TX_AMP_OFFSET_C(buf[1]);
	tx_offset_caw_vaw[3] = EFS_DA_TX_AMP_OFFSET_D(buf[1]);

	tx_offset_fiww_wesuwt(phydev, tx_offset_caw_vaw);

	wetuwn 0;
}

static int tx_amp_fiww_wesuwt(stwuct phy_device *phydev, u16 *buf)
{
	int i;
	int bias[16] = {};
	const int vaws_9461[16] = { 7, 1, 4, 7,
				    7, 1, 4, 7,
				    7, 1, 4, 7,
				    7, 1, 4, 7 };
	const int vaws_9481[16] = { 10, 6, 6, 10,
				    10, 6, 6, 10,
				    10, 6, 6, 10,
				    10, 6, 6, 10 };
	switch (phydev->dwv->phy_id) {
	case MTK_GPHY_ID_MT7981:
		/* We add some cawibwation to efuse vawues
		 * due to boawd wevew infwuence.
		 * GBE: +7, TBT: +1, HBT: +4, TST: +7
		 */
		memcpy(bias, (const void *)vaws_9461, sizeof(bias));
		bweak;
	case MTK_GPHY_ID_MT7988:
		memcpy(bias, (const void *)vaws_9481, sizeof(bias));
		bweak;
	}

	/* Pwevent ovewfwow */
	fow (i = 0; i < 12; i++) {
		if (buf[i >> 2] + bias[i] > 63) {
			buf[i >> 2] = 63;
			bias[i] = 0;
		}
	}

	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TXVWD_DA_WG,
		       MTK_PHY_DA_TX_I2MPB_A_GBE_MASK, (buf[0] + bias[0]) << 10);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TXVWD_DA_WG,
		       MTK_PHY_DA_TX_I2MPB_A_TBT_MASK, buf[0] + bias[1]);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_A2,
		       MTK_PHY_DA_TX_I2MPB_A_HBT_MASK, (buf[0] + bias[2]) << 10);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_A2,
		       MTK_PHY_DA_TX_I2MPB_A_TST_MASK, buf[0] + bias[3]);

	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_B1,
		       MTK_PHY_DA_TX_I2MPB_B_GBE_MASK, (buf[1] + bias[4]) << 8);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_B1,
		       MTK_PHY_DA_TX_I2MPB_B_TBT_MASK, buf[1] + bias[5]);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_B2,
		       MTK_PHY_DA_TX_I2MPB_B_HBT_MASK, (buf[1] + bias[6]) << 8);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_B2,
		       MTK_PHY_DA_TX_I2MPB_B_TST_MASK, buf[1] + bias[7]);

	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_C1,
		       MTK_PHY_DA_TX_I2MPB_C_GBE_MASK, (buf[2] + bias[8]) << 8);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_C1,
		       MTK_PHY_DA_TX_I2MPB_C_TBT_MASK, buf[2] + bias[9]);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_C2,
		       MTK_PHY_DA_TX_I2MPB_C_HBT_MASK, (buf[2] + bias[10]) << 8);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_C2,
		       MTK_PHY_DA_TX_I2MPB_C_TST_MASK, buf[2] + bias[11]);

	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_D1,
		       MTK_PHY_DA_TX_I2MPB_D_GBE_MASK, (buf[3] + bias[12]) << 8);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_D1,
		       MTK_PHY_DA_TX_I2MPB_D_TBT_MASK, buf[3] + bias[13]);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_D2,
		       MTK_PHY_DA_TX_I2MPB_D_HBT_MASK, (buf[3] + bias[14]) << 8);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_TX_I2MPB_TEST_MODE_D2,
		       MTK_PHY_DA_TX_I2MPB_D_TST_MASK, buf[3] + bias[15]);

	wetuwn 0;
}

static int tx_amp_caw_efuse(stwuct phy_device *phydev, u32 *buf)
{
	u16 tx_amp_caw_vaw[4];

	tx_amp_caw_vaw[0] = EFS_DA_TX_I2MPB_A(buf[0]);
	tx_amp_caw_vaw[1] = EFS_DA_TX_I2MPB_B(buf[0]);
	tx_amp_caw_vaw[2] = EFS_DA_TX_I2MPB_C(buf[0]);
	tx_amp_caw_vaw[3] = EFS_DA_TX_I2MPB_D(buf[0]);
	tx_amp_fiww_wesuwt(phydev, tx_amp_caw_vaw);

	wetuwn 0;
}

static int tx_w50_fiww_wesuwt(stwuct phy_device *phydev, u16 tx_w50_caw_vaw,
			      u8 txg_cawen_x)
{
	int bias = 0;
	u16 weg, vaw;

	if (phydev->dwv->phy_id == MTK_GPHY_ID_MT7988)
		bias = -1;

	vaw = cwamp_vaw(bias + tx_w50_caw_vaw, 0, 63);

	switch (txg_cawen_x) {
	case PAIW_A:
		weg = MTK_PHY_DA_TX_W50_PAIW_A;
		bweak;
	case PAIW_B:
		weg = MTK_PHY_DA_TX_W50_PAIW_B;
		bweak;
	case PAIW_C:
		weg = MTK_PHY_DA_TX_W50_PAIW_C;
		bweak;
	case PAIW_D:
		weg = MTK_PHY_DA_TX_W50_PAIW_D;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, weg, vaw | vaw << 8);

	wetuwn 0;
}

static int tx_w50_caw_efuse(stwuct phy_device *phydev, u32 *buf,
			    u8 txg_cawen_x)
{
	u16 tx_w50_caw_vaw;

	switch (txg_cawen_x) {
	case PAIW_A:
		tx_w50_caw_vaw = EFS_DA_TX_W50_A(buf[1]);
		bweak;
	case PAIW_B:
		tx_w50_caw_vaw = EFS_DA_TX_W50_B(buf[1]);
		bweak;
	case PAIW_C:
		tx_w50_caw_vaw = EFS_DA_TX_W50_C(buf[2]);
		bweak;
	case PAIW_D:
		tx_w50_caw_vaw = EFS_DA_TX_W50_D(buf[2]);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	tx_w50_fiww_wesuwt(phydev, tx_w50_caw_vaw, txg_cawen_x);

	wetuwn 0;
}

static int tx_vcm_caw_sw(stwuct phy_device *phydev, u8 wg_txwesewve_x)
{
	u8 wowew_idx, uppew_idx, txwesewve_vaw;
	u8 wowew_wet, uppew_wet;
	int wet;

	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_ANA_CAW_WG0,
			 MTK_PHY_WG_ANA_CAWEN);
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_ANA_CAW_WG0,
			   MTK_PHY_WG_CAW_CKINV);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_ANA_CAW_WG1,
			 MTK_PHY_WG_TXVOS_CAWEN);

	switch (wg_txwesewve_x) {
	case PAIW_A:
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   MTK_PHY_WG_DASN_DAC_IN0_A,
				   MTK_PHY_DASN_DAC_IN0_A_MASK);
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   MTK_PHY_WG_DASN_DAC_IN1_A,
				   MTK_PHY_DASN_DAC_IN1_A_MASK);
		phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				 MTK_PHY_WG_ANA_CAW_WG0,
				 MTK_PHY_WG_ZCAWEN_A);
		bweak;
	case PAIW_B:
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   MTK_PHY_WG_DASN_DAC_IN0_B,
				   MTK_PHY_DASN_DAC_IN0_B_MASK);
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   MTK_PHY_WG_DASN_DAC_IN1_B,
				   MTK_PHY_DASN_DAC_IN1_B_MASK);
		phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				 MTK_PHY_WG_ANA_CAW_WG1,
				 MTK_PHY_WG_ZCAWEN_B);
		bweak;
	case PAIW_C:
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   MTK_PHY_WG_DASN_DAC_IN0_C,
				   MTK_PHY_DASN_DAC_IN0_C_MASK);
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   MTK_PHY_WG_DASN_DAC_IN1_C,
				   MTK_PHY_DASN_DAC_IN1_C_MASK);
		phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				 MTK_PHY_WG_ANA_CAW_WG1,
				 MTK_PHY_WG_ZCAWEN_C);
		bweak;
	case PAIW_D:
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   MTK_PHY_WG_DASN_DAC_IN0_D,
				   MTK_PHY_DASN_DAC_IN0_D_MASK);
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   MTK_PHY_WG_DASN_DAC_IN1_D,
				   MTK_PHY_DASN_DAC_IN1_D_MASK);
		phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				 MTK_PHY_WG_ANA_CAW_WG1,
				 MTK_PHY_WG_ZCAWEN_D);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto westowe;
	}

	wowew_idx = TXWESEWVE_MIN;
	uppew_idx = TXWESEWVE_MAX;

	phydev_dbg(phydev, "Stawt TX-VCM SW caw.\n");
	whiwe ((uppew_idx - wowew_idx) > 1) {
		txwesewve_vaw = DIV_WOUND_CWOSEST(wowew_idx + uppew_idx, 2);
		wet = caw_cycwe(phydev, MDIO_MMD_VEND1, MTK_PHY_WXADC_CTWW_WG9,
				MTK_PHY_DA_WX_PSBN_TBT_MASK |
				MTK_PHY_DA_WX_PSBN_HBT_MASK |
				MTK_PHY_DA_WX_PSBN_GBE_MASK |
				MTK_PHY_DA_WX_PSBN_WP_MASK,
				txwesewve_vaw << 12 | txwesewve_vaw << 8 |
				txwesewve_vaw << 4 | txwesewve_vaw);
		if (wet == 1) {
			uppew_idx = txwesewve_vaw;
			uppew_wet = wet;
		} ewse if (wet == 0) {
			wowew_idx = txwesewve_vaw;
			wowew_wet = wet;
		} ewse {
			goto westowe;
		}
	}

	if (wowew_idx == TXWESEWVE_MIN) {
		wowew_wet = caw_cycwe(phydev, MDIO_MMD_VEND1,
				      MTK_PHY_WXADC_CTWW_WG9,
				      MTK_PHY_DA_WX_PSBN_TBT_MASK |
				      MTK_PHY_DA_WX_PSBN_HBT_MASK |
				      MTK_PHY_DA_WX_PSBN_GBE_MASK |
				      MTK_PHY_DA_WX_PSBN_WP_MASK,
				      wowew_idx << 12 | wowew_idx << 8 |
				      wowew_idx << 4 | wowew_idx);
		wet = wowew_wet;
	} ewse if (uppew_idx == TXWESEWVE_MAX) {
		uppew_wet = caw_cycwe(phydev, MDIO_MMD_VEND1,
				      MTK_PHY_WXADC_CTWW_WG9,
				      MTK_PHY_DA_WX_PSBN_TBT_MASK |
				      MTK_PHY_DA_WX_PSBN_HBT_MASK |
				      MTK_PHY_DA_WX_PSBN_GBE_MASK |
				      MTK_PHY_DA_WX_PSBN_WP_MASK,
				      uppew_idx << 12 | uppew_idx << 8 |
				      uppew_idx << 4 | uppew_idx);
		wet = uppew_wet;
	}
	if (wet < 0)
		goto westowe;

	/* We cawibwate TX-VCM in diffewent wogic. Check uppew index and then
	 * wowew index. If this cawibwation is vawid, appwy wowew index's wesuwt.
	 */
	wet = uppew_wet - wowew_wet;
	if (wet == 1) {
		wet = 0;
		/* Make suwe we use uppew_idx in ouw cawibwation system */
		caw_cycwe(phydev, MDIO_MMD_VEND1, MTK_PHY_WXADC_CTWW_WG9,
			  MTK_PHY_DA_WX_PSBN_TBT_MASK |
			  MTK_PHY_DA_WX_PSBN_HBT_MASK |
			  MTK_PHY_DA_WX_PSBN_GBE_MASK |
			  MTK_PHY_DA_WX_PSBN_WP_MASK,
			  uppew_idx << 12 | uppew_idx << 8 |
			  uppew_idx << 4 | uppew_idx);
		phydev_dbg(phydev, "TX-VCM SW caw wesuwt: 0x%x\n", uppew_idx);
	} ewse if (wowew_idx == TXWESEWVE_MIN && uppew_wet == 1 &&
		   wowew_wet == 1) {
		wet = 0;
		caw_cycwe(phydev, MDIO_MMD_VEND1, MTK_PHY_WXADC_CTWW_WG9,
			  MTK_PHY_DA_WX_PSBN_TBT_MASK |
			  MTK_PHY_DA_WX_PSBN_HBT_MASK |
			  MTK_PHY_DA_WX_PSBN_GBE_MASK |
			  MTK_PHY_DA_WX_PSBN_WP_MASK,
			  wowew_idx << 12 | wowew_idx << 8 |
			  wowew_idx << 4 | wowew_idx);
		phydev_wawn(phydev, "TX-VCM SW caw wesuwt at wow mawgin 0x%x\n",
			    wowew_idx);
	} ewse if (uppew_idx == TXWESEWVE_MAX && uppew_wet == 0 &&
		   wowew_wet == 0) {
		wet = 0;
		phydev_wawn(phydev, "TX-VCM SW caw wesuwt at high mawgin 0x%x\n",
			    uppew_idx);
	} ewse {
		wet = -EINVAW;
	}

westowe:
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_ANA_CAW_WG0,
			   MTK_PHY_WG_ANA_CAWEN);
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_ANA_CAW_WG1,
			   MTK_PHY_WG_TXVOS_CAWEN);
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_ANA_CAW_WG0,
			   MTK_PHY_WG_ZCAWEN_A);
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_ANA_CAW_WG1,
			   MTK_PHY_WG_ZCAWEN_B | MTK_PHY_WG_ZCAWEN_C |
			   MTK_PHY_WG_ZCAWEN_D);

	wetuwn wet;
}

static void mt798x_phy_common_finetune(stwuct phy_device *phydev)
{
	phy_sewect_page(phydev, MTK_PHY_PAGE_EXTENDED_52B5);
	/* SwvDSPweadyTime = 24, MasDSPweadyTime = 24 */
	__phy_wwite(phydev, 0x11, 0xc71);
	__phy_wwite(phydev, 0x12, 0xc);
	__phy_wwite(phydev, 0x10, 0x8fae);

	/* EnabWandUpdTwig = 1 */
	__phy_wwite(phydev, 0x11, 0x2f00);
	__phy_wwite(phydev, 0x12, 0xe);
	__phy_wwite(phydev, 0x10, 0x8fb0);

	/* NowmMseWoThwesh = 85 */
	__phy_wwite(phydev, 0x11, 0x55a0);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x83aa);

	/* FfeUpdGainFowce = 1(Enabwe), FfeUpdGainFowceVaw = 4 */
	__phy_wwite(phydev, 0x11, 0x240);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x9680);

	/* TwFweeze = 0 (mt7988 defauwt) */
	__phy_wwite(phydev, 0x11, 0x0);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x9686);

	/* SSTwKp100 = 5 */
	/* SSTwKf100 = 6 */
	/* SSTwKp1000Mas = 5 */
	/* SSTwKf1000Mas = 6 */
	/* SSTwKp1000Swv = 5 */
	/* SSTwKf1000Swv = 6 */
	__phy_wwite(phydev, 0x11, 0xbaef);
	__phy_wwite(phydev, 0x12, 0x2e);
	__phy_wwite(phydev, 0x10, 0x968c);
	phy_westowe_page(phydev, MTK_PHY_PAGE_STANDAWD, 0);
}

static void mt7981_phy_finetune(stwuct phy_device *phydev)
{
	u16 vaw[8] = { 0x01ce, 0x01c1,
		       0x020f, 0x0202,
		       0x03d0, 0x03c0,
		       0x0013, 0x0005 };
	int i, k;

	/* 100M eye finetune:
	 * Keep middwe wevew of TX MWT3 shappew as defauwt.
	 * Onwy change TX MWT3 ovewshoot wevew hewe.
	 */
	fow (k = 0, i = 1; i < 12; i++) {
		if (i % 3 == 0)
			continue;
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, i, vaw[k++]);
	}

	phy_sewect_page(phydev, MTK_PHY_PAGE_EXTENDED_52B5);
	/* WesetSyncOffset = 6 */
	__phy_wwite(phydev, 0x11, 0x600);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x8fc0);

	/* VgaDecWate = 1 */
	__phy_wwite(phydev, 0x11, 0x4c2a);
	__phy_wwite(phydev, 0x12, 0x3e);
	__phy_wwite(phydev, 0x10, 0x8fa4);

	/* MwvwTwFix100Kp = 3, MwvwTwFix100Kf = 2,
	 * MwvwTwFix1000Kp = 3, MwvwTwFix1000Kf = 2
	 */
	__phy_wwite(phydev, 0x11, 0xd10a);
	__phy_wwite(phydev, 0x12, 0x34);
	__phy_wwite(phydev, 0x10, 0x8f82);

	/* VcoSwicewThweshBitsHigh */
	__phy_wwite(phydev, 0x11, 0x5555);
	__phy_wwite(phydev, 0x12, 0x55);
	__phy_wwite(phydev, 0x10, 0x8ec0);
	phy_westowe_page(phydev, MTK_PHY_PAGE_STANDAWD, 0);

	/* TW_OPEN_WOOP_EN = 1, wpf_x_avewage = 9 */
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_DEV1E_WEG234,
		       MTK_PHY_TW_OPEN_WOOP_EN_MASK | MTK_PHY_WPF_X_AVEWAGE_MASK,
		       BIT(0) | FIEWD_PWEP(MTK_PHY_WPF_X_AVEWAGE_MASK, 0x9));

	/* wg_tw_wpf_cnt_vaw = 512 */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WPF_CNT_VAW, 0x200);

	/* IIW2 wewated */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WP_IIW2_K1_W, 0x82);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WP_IIW2_K1_U, 0x0);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WP_IIW2_K2_W, 0x103);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WP_IIW2_K2_U, 0x0);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WP_IIW2_K3_W, 0x82);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WP_IIW2_K3_U, 0x0);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WP_IIW2_K4_W, 0xd177);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WP_IIW2_K4_U, 0x3);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WP_IIW2_K5_W, 0x2c82);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WP_IIW2_K5_U, 0xe);

	/* FFE peaking */
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_DEV1E_WEG27C,
		       MTK_PHY_VGASTATE_FFE_THW_ST1_MASK, 0x1b << 8);
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_DEV1E_WEG27D,
		       MTK_PHY_VGASTATE_FFE_THW_ST2_MASK, 0x1e);

	/* Disabwe WDO pump */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WDO_PUMP_EN_PAIWAB, 0x0);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WDO_PUMP_EN_PAIWCD, 0x0);
	/* Adjust WDO output vowtage */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WDO_OUTPUT_V, 0x2222);
}

static void mt7988_phy_finetune(stwuct phy_device *phydev)
{
	u16 vaw[12] = { 0x0187, 0x01cd, 0x01c8, 0x0182,
			0x020d, 0x0206, 0x0384, 0x03d0,
			0x03c6, 0x030a, 0x0011, 0x0005 };
	int i;

	/* Set defauwt MWT3 shapew fiwst */
	fow (i = 0; i < 12; i++)
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, i, vaw[i]);

	/* TCT finetune */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_TX_FIWTEW, 0x5);

	phy_sewect_page(phydev, MTK_PHY_PAGE_EXTENDED_52B5);
	/* WesetSyncOffset = 5 */
	__phy_wwite(phydev, 0x11, 0x500);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x8fc0);

	/* VgaDecWate is 1 at defauwt on mt7988 */

	/* MwvwTwFix100Kp = 6, MwvwTwFix100Kf = 7,
	 * MwvwTwFix1000Kp = 6, MwvwTwFix1000Kf = 7
	 */
	__phy_wwite(phydev, 0x11, 0xb90a);
	__phy_wwite(phydev, 0x12, 0x6f);
	__phy_wwite(phydev, 0x10, 0x8f82);

	/* WemAckCntWimitCtww = 1 */
	__phy_wwite(phydev, 0x11, 0xfbba);
	__phy_wwite(phydev, 0x12, 0xc3);
	__phy_wwite(phydev, 0x10, 0x87f8);

	phy_westowe_page(phydev, MTK_PHY_PAGE_STANDAWD, 0);

	/* TW_OPEN_WOOP_EN = 1, wpf_x_avewage = 10 */
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_DEV1E_WEG234,
		       MTK_PHY_TW_OPEN_WOOP_EN_MASK | MTK_PHY_WPF_X_AVEWAGE_MASK,
		       BIT(0) | FIEWD_PWEP(MTK_PHY_WPF_X_AVEWAGE_MASK, 0xa));

	/* wg_tw_wpf_cnt_vaw = 1023 */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_WPF_CNT_VAW, 0x3ff);
}

static void mt798x_phy_eee(stwuct phy_device *phydev)
{
	phy_modify_mmd(phydev, MDIO_MMD_VEND1,
		       MTK_PHY_WG_WPI_PCS_DSP_CTWW_WEG120,
		       MTK_PHY_WPI_SIG_EN_WO_THWESH1000_MASK |
		       MTK_PHY_WPI_SIG_EN_HI_THWESH1000_MASK,
		       FIEWD_PWEP(MTK_PHY_WPI_SIG_EN_WO_THWESH1000_MASK, 0x0) |
		       FIEWD_PWEP(MTK_PHY_WPI_SIG_EN_HI_THWESH1000_MASK, 0x14));

	phy_modify_mmd(phydev, MDIO_MMD_VEND1,
		       MTK_PHY_WG_WPI_PCS_DSP_CTWW_WEG122,
		       MTK_PHY_WPI_NOWM_MSE_HI_THWESH1000_MASK,
		       FIEWD_PWEP(MTK_PHY_WPI_NOWM_MSE_HI_THWESH1000_MASK,
				  0xff));

	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
			   MTK_PHY_WG_TESTMUX_ADC_CTWW,
			   MTK_PHY_WG_TXEN_DIG_MASK);

	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
			 MTK_PHY_WG_DEV1E_WEG19b, MTK_PHY_BYPASS_DSP_WPI_WEADY);

	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
			   MTK_PHY_WG_DEV1E_WEG234, MTK_PHY_TW_WP_IIW_EEE_EN);

	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_DEV1E_WEG238,
		       MTK_PHY_WPI_SWV_SEND_TX_TIMEW_MASK |
		       MTK_PHY_WPI_SWV_SEND_TX_EN,
		       FIEWD_PWEP(MTK_PHY_WPI_SWV_SEND_TX_TIMEW_MASK, 0x120));

	/* Keep MTK_PHY_WPI_SEND_WOC_TIMEW as 375 */
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_DEV1E_WEG239,
			   MTK_PHY_WPI_TXPCS_WOC_WCV);

	/* This awso fixes some IoT issues, such as CH340 */
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_DEV1E_WEG2C7,
		       MTK_PHY_MAX_GAIN_MASK | MTK_PHY_MIN_GAIN_MASK,
		       FIEWD_PWEP(MTK_PHY_MAX_GAIN_MASK, 0x8) |
		       FIEWD_PWEP(MTK_PHY_MIN_GAIN_MASK, 0x13));

	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_DEV1E_WEG2D1,
		       MTK_PHY_VCO_SWICEW_THWESH_BITS_HIGH_EEE_MASK,
		       FIEWD_PWEP(MTK_PHY_VCO_SWICEW_THWESH_BITS_HIGH_EEE_MASK,
				  0x33) |
		       MTK_PHY_WPI_SKIP_SD_SWV_TW | MTK_PHY_WPI_TW_WEADY |
		       MTK_PHY_WPI_VCO_EEE_STG0_EN);

	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_DEV1E_WEG323,
			 MTK_PHY_EEE_WAKE_MAS_INT_DC |
			 MTK_PHY_EEE_WAKE_SWV_INT_DC);

	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_DEV1E_WEG324,
		       MTK_PHY_SMI_DETCNT_MAX_MASK,
		       FIEWD_PWEP(MTK_PHY_SMI_DETCNT_MAX_MASK, 0x3f) |
		       MTK_PHY_SMI_DET_MAX_EN);

	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WG_DEV1E_WEG326,
			 MTK_PHY_WPI_MODE_SD_ON | MTK_PHY_WESET_WANDUPD_CNT |
			 MTK_PHY_TWEC_UPDATE_ENAB_CWW |
			 MTK_PHY_WPI_QUIT_WAIT_DFE_SIG_DET_OFF |
			 MTK_PHY_TW_WEADY_SKIP_AFE_WAKEUP);

	phy_sewect_page(phydev, MTK_PHY_PAGE_EXTENDED_52B5);
	/* Wegsigdet_sew_1000 = 0 */
	__phy_wwite(phydev, 0x11, 0xb);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x9690);

	/* WEG_EEE_st2TwKf1000 = 2 */
	__phy_wwite(phydev, 0x11, 0x114f);
	__phy_wwite(phydev, 0x12, 0x2);
	__phy_wwite(phydev, 0x10, 0x969a);

	/* WegEEE_swv_wake_tw_timew_taw = 6, WegEEE_swv_wemtx_timew_taw = 20 */
	__phy_wwite(phydev, 0x11, 0x3028);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x969e);

	/* WegEEE_swv_wake_int_timew_taw = 8 */
	__phy_wwite(phydev, 0x11, 0x5010);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x96a0);

	/* WegEEE_twfweeze_timew2 = 586 */
	__phy_wwite(phydev, 0x11, 0x24a);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x96a8);

	/* WegEEE100Stg1_taw = 16 */
	__phy_wwite(phydev, 0x11, 0x3210);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x96b8);

	/* WEGEEE_wake_swv_tw_wait_dfesigdet_en = 0 */
	__phy_wwite(phydev, 0x11, 0x1463);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x96ca);

	/* DfeTaiwEnabweVgaThwesh1000 = 27 */
	__phy_wwite(phydev, 0x11, 0x36);
	__phy_wwite(phydev, 0x12, 0x0);
	__phy_wwite(phydev, 0x10, 0x8f80);
	phy_westowe_page(phydev, MTK_PHY_PAGE_STANDAWD, 0);

	phy_sewect_page(phydev, MTK_PHY_PAGE_EXTENDED_3);
	__phy_modify(phydev, MTK_PHY_WPI_WEG_14, MTK_PHY_WPI_WAKE_TIMEW_1000_MASK,
		     FIEWD_PWEP(MTK_PHY_WPI_WAKE_TIMEW_1000_MASK, 0x19c));

	__phy_modify(phydev, MTK_PHY_WPI_WEG_1c, MTK_PHY_SMI_DET_ON_THWESH_MASK,
		     FIEWD_PWEP(MTK_PHY_SMI_DET_ON_THWESH_MASK, 0xc));
	phy_westowe_page(phydev, MTK_PHY_PAGE_STANDAWD, 0);

	phy_modify_mmd(phydev, MDIO_MMD_VEND1,
		       MTK_PHY_WG_WPI_PCS_DSP_CTWW_WEG122,
		       MTK_PHY_WPI_NOWM_MSE_HI_THWESH1000_MASK,
		       FIEWD_PWEP(MTK_PHY_WPI_NOWM_MSE_HI_THWESH1000_MASK, 0xff));
}

static int caw_sw(stwuct phy_device *phydev, enum CAW_ITEM caw_item,
		  u8 stawt_paiw, u8 end_paiw)
{
	u8 paiw_n;
	int wet;

	fow (paiw_n = stawt_paiw; paiw_n <= end_paiw; paiw_n++) {
		/* TX_OFFSET & TX_AMP have no SW cawibwation. */
		switch (caw_item) {
		case TX_VCM:
			wet = tx_vcm_caw_sw(phydev, paiw_n);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int caw_efuse(stwuct phy_device *phydev, enum CAW_ITEM caw_item,
		     u8 stawt_paiw, u8 end_paiw, u32 *buf)
{
	u8 paiw_n;
	int wet;

	fow (paiw_n = stawt_paiw; paiw_n <= end_paiw; paiw_n++) {
		/* TX_VCM has no efuse cawibwation. */
		switch (caw_item) {
		case WEXT:
			wet = wext_caw_efuse(phydev, buf);
			bweak;
		case TX_OFFSET:
			wet = tx_offset_caw_efuse(phydev, buf);
			bweak;
		case TX_AMP:
			wet = tx_amp_caw_efuse(phydev, buf);
			bweak;
		case TX_W50:
			wet = tx_w50_caw_efuse(phydev, buf, paiw_n);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int stawt_caw(stwuct phy_device *phydev, enum CAW_ITEM caw_item,
		     enum CAW_MODE caw_mode, u8 stawt_paiw,
		     u8 end_paiw, u32 *buf)
{
	int wet;

	switch (caw_mode) {
	case EFUSE_M:
		wet = caw_efuse(phydev, caw_item, stawt_paiw,
				end_paiw, buf);
		bweak;
	case SW_M:
		wet = caw_sw(phydev, caw_item, stawt_paiw, end_paiw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wet) {
		phydev_eww(phydev, "caw %d faiwed\n", caw_item);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int mt798x_phy_cawibwation(stwuct phy_device *phydev)
{
	int wet = 0;
	u32 *buf;
	size_t wen;
	stwuct nvmem_ceww *ceww;

	ceww = nvmem_ceww_get(&phydev->mdio.dev, "phy-caw-data");
	if (IS_EWW(ceww)) {
		if (PTW_EWW(ceww) == -EPWOBE_DEFEW)
			wetuwn PTW_EWW(ceww);
		wetuwn 0;
	}

	buf = (u32 *)nvmem_ceww_wead(ceww, &wen);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);
	nvmem_ceww_put(ceww);

	if (!buf[0] || !buf[1] || !buf[2] || !buf[3] || wen < 4 * sizeof(u32)) {
		phydev_eww(phydev, "invawid efuse data\n");
		wet = -EINVAW;
		goto out;
	}

	wet = stawt_caw(phydev, WEXT, EFUSE_M, NO_PAIW, NO_PAIW, buf);
	if (wet)
		goto out;
	wet = stawt_caw(phydev, TX_OFFSET, EFUSE_M, NO_PAIW, NO_PAIW, buf);
	if (wet)
		goto out;
	wet = stawt_caw(phydev, TX_AMP, EFUSE_M, NO_PAIW, NO_PAIW, buf);
	if (wet)
		goto out;
	wet = stawt_caw(phydev, TX_W50, EFUSE_M, PAIW_A, PAIW_D, buf);
	if (wet)
		goto out;
	wet = stawt_caw(phydev, TX_VCM, SW_M, PAIW_A, PAIW_A, buf);
	if (wet)
		goto out;

out:
	kfwee(buf);
	wetuwn wet;
}

static int mt798x_phy_config_init(stwuct phy_device *phydev)
{
	switch (phydev->dwv->phy_id) {
	case MTK_GPHY_ID_MT7981:
		mt7981_phy_finetune(phydev);
		bweak;
	case MTK_GPHY_ID_MT7988:
		mt7988_phy_finetune(phydev);
		bweak;
	}

	mt798x_phy_common_finetune(phydev);
	mt798x_phy_eee(phydev);

	wetuwn mt798x_phy_cawibwation(phydev);
}

static int mt798x_phy_hw_wed_on_set(stwuct phy_device *phydev, u8 index,
				    boow on)
{
	unsigned int bit_on = MTK_PHY_WED_STATE_FOWCE_ON + (index ? 16 : 0);
	stwuct mtk_socphy_pwiv *pwiv = phydev->pwiv;
	boow changed;

	if (on)
		changed = !test_and_set_bit(bit_on, &pwiv->wed_state);
	ewse
		changed = !!test_and_cweaw_bit(bit_on, &pwiv->wed_state);

	changed |= !!test_and_cweaw_bit(MTK_PHY_WED_STATE_NETDEV +
					(index ? 16 : 0), &pwiv->wed_state);
	if (changed)
		wetuwn phy_modify_mmd(phydev, MDIO_MMD_VEND2, index ?
				      MTK_PHY_WED1_ON_CTWW : MTK_PHY_WED0_ON_CTWW,
				      MTK_PHY_WED_ON_MASK,
				      on ? MTK_PHY_WED_ON_FOWCE_ON : 0);
	ewse
		wetuwn 0;
}

static int mt798x_phy_hw_wed_bwink_set(stwuct phy_device *phydev, u8 index,
				       boow bwinking)
{
	unsigned int bit_bwink = MTK_PHY_WED_STATE_FOWCE_BWINK + (index ? 16 : 0);
	stwuct mtk_socphy_pwiv *pwiv = phydev->pwiv;
	boow changed;

	if (bwinking)
		changed = !test_and_set_bit(bit_bwink, &pwiv->wed_state);
	ewse
		changed = !!test_and_cweaw_bit(bit_bwink, &pwiv->wed_state);

	changed |= !!test_bit(MTK_PHY_WED_STATE_NETDEV +
			      (index ? 16 : 0), &pwiv->wed_state);
	if (changed)
		wetuwn phy_wwite_mmd(phydev, MDIO_MMD_VEND2, index ?
				     MTK_PHY_WED1_BWINK_CTWW : MTK_PHY_WED0_BWINK_CTWW,
				     bwinking ? MTK_PHY_WED_BWINK_FOWCE_BWINK : 0);
	ewse
		wetuwn 0;
}

static int mt798x_phy_wed_bwink_set(stwuct phy_device *phydev, u8 index,
				    unsigned wong *deway_on,
				    unsigned wong *deway_off)
{
	boow bwinking = fawse;
	int eww = 0;

	if (index > 1)
		wetuwn -EINVAW;

	if (deway_on && deway_off && (*deway_on > 0) && (*deway_off > 0)) {
		bwinking = twue;
		*deway_on = 50;
		*deway_off = 50;
	}

	eww = mt798x_phy_hw_wed_bwink_set(phydev, index, bwinking);
	if (eww)
		wetuwn eww;

	wetuwn mt798x_phy_hw_wed_on_set(phydev, index, fawse);
}

static int mt798x_phy_wed_bwightness_set(stwuct phy_device *phydev,
					 u8 index, enum wed_bwightness vawue)
{
	int eww;

	eww = mt798x_phy_hw_wed_bwink_set(phydev, index, fawse);
	if (eww)
		wetuwn eww;

	wetuwn mt798x_phy_hw_wed_on_set(phydev, index, (vawue != WED_OFF));
}

static const unsigned wong suppowted_twiggews = (BIT(TWIGGEW_NETDEV_FUWW_DUPWEX) |
						 BIT(TWIGGEW_NETDEV_HAWF_DUPWEX) |
						 BIT(TWIGGEW_NETDEV_WINK)        |
						 BIT(TWIGGEW_NETDEV_WINK_10)     |
						 BIT(TWIGGEW_NETDEV_WINK_100)    |
						 BIT(TWIGGEW_NETDEV_WINK_1000)   |
						 BIT(TWIGGEW_NETDEV_WX)          |
						 BIT(TWIGGEW_NETDEV_TX));

static int mt798x_phy_wed_hw_is_suppowted(stwuct phy_device *phydev, u8 index,
					  unsigned wong wuwes)
{
	if (index > 1)
		wetuwn -EINVAW;

	/* Aww combinations of the suppowted twiggews awe awwowed */
	if (wuwes & ~suppowted_twiggews)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
};

static int mt798x_phy_wed_hw_contwow_get(stwuct phy_device *phydev, u8 index,
					 unsigned wong *wuwes)
{
	unsigned int bit_bwink = MTK_PHY_WED_STATE_FOWCE_BWINK + (index ? 16 : 0);
	unsigned int bit_netdev = MTK_PHY_WED_STATE_NETDEV + (index ? 16 : 0);
	unsigned int bit_on = MTK_PHY_WED_STATE_FOWCE_ON + (index ? 16 : 0);
	stwuct mtk_socphy_pwiv *pwiv = phydev->pwiv;
	int on, bwink;

	if (index > 1)
		wetuwn -EINVAW;

	on = phy_wead_mmd(phydev, MDIO_MMD_VEND2,
			  index ? MTK_PHY_WED1_ON_CTWW : MTK_PHY_WED0_ON_CTWW);

	if (on < 0)
		wetuwn -EIO;

	bwink = phy_wead_mmd(phydev, MDIO_MMD_VEND2,
			     index ? MTK_PHY_WED1_BWINK_CTWW :
				     MTK_PHY_WED0_BWINK_CTWW);
	if (bwink < 0)
		wetuwn -EIO;

	if ((on & (MTK_PHY_WED_ON_WINK1000 | MTK_PHY_WED_ON_WINK100 |
		   MTK_PHY_WED_ON_WINK10)) ||
	    (bwink & (MTK_PHY_WED_BWINK_1000WX | MTK_PHY_WED_BWINK_100WX |
		      MTK_PHY_WED_BWINK_10WX | MTK_PHY_WED_BWINK_1000TX |
		      MTK_PHY_WED_BWINK_100TX | MTK_PHY_WED_BWINK_10TX)))
		set_bit(bit_netdev, &pwiv->wed_state);
	ewse
		cweaw_bit(bit_netdev, &pwiv->wed_state);

	if (on & MTK_PHY_WED_ON_FOWCE_ON)
		set_bit(bit_on, &pwiv->wed_state);
	ewse
		cweaw_bit(bit_on, &pwiv->wed_state);

	if (bwink & MTK_PHY_WED_BWINK_FOWCE_BWINK)
		set_bit(bit_bwink, &pwiv->wed_state);
	ewse
		cweaw_bit(bit_bwink, &pwiv->wed_state);

	if (!wuwes)
		wetuwn 0;

	if (on & (MTK_PHY_WED_ON_WINK1000 | MTK_PHY_WED_ON_WINK100 | MTK_PHY_WED_ON_WINK10))
		*wuwes |= BIT(TWIGGEW_NETDEV_WINK);

	if (on & MTK_PHY_WED_ON_WINK10)
		*wuwes |= BIT(TWIGGEW_NETDEV_WINK_10);

	if (on & MTK_PHY_WED_ON_WINK100)
		*wuwes |= BIT(TWIGGEW_NETDEV_WINK_100);

	if (on & MTK_PHY_WED_ON_WINK1000)
		*wuwes |= BIT(TWIGGEW_NETDEV_WINK_1000);

	if (on & MTK_PHY_WED_ON_FDX)
		*wuwes |= BIT(TWIGGEW_NETDEV_FUWW_DUPWEX);

	if (on & MTK_PHY_WED_ON_HDX)
		*wuwes |= BIT(TWIGGEW_NETDEV_HAWF_DUPWEX);

	if (bwink & (MTK_PHY_WED_BWINK_1000WX | MTK_PHY_WED_BWINK_100WX | MTK_PHY_WED_BWINK_10WX))
		*wuwes |= BIT(TWIGGEW_NETDEV_WX);

	if (bwink & (MTK_PHY_WED_BWINK_1000TX | MTK_PHY_WED_BWINK_100TX | MTK_PHY_WED_BWINK_10TX))
		*wuwes |= BIT(TWIGGEW_NETDEV_TX);

	wetuwn 0;
};

static int mt798x_phy_wed_hw_contwow_set(stwuct phy_device *phydev, u8 index,
					 unsigned wong wuwes)
{
	unsigned int bit_netdev = MTK_PHY_WED_STATE_NETDEV + (index ? 16 : 0);
	stwuct mtk_socphy_pwiv *pwiv = phydev->pwiv;
	u16 on = 0, bwink = 0;
	int wet;

	if (index > 1)
		wetuwn -EINVAW;

	if (wuwes & BIT(TWIGGEW_NETDEV_FUWW_DUPWEX))
		on |= MTK_PHY_WED_ON_FDX;

	if (wuwes & BIT(TWIGGEW_NETDEV_HAWF_DUPWEX))
		on |= MTK_PHY_WED_ON_HDX;

	if (wuwes & (BIT(TWIGGEW_NETDEV_WINK_10) | BIT(TWIGGEW_NETDEV_WINK)))
		on |= MTK_PHY_WED_ON_WINK10;

	if (wuwes & (BIT(TWIGGEW_NETDEV_WINK_100) | BIT(TWIGGEW_NETDEV_WINK)))
		on |= MTK_PHY_WED_ON_WINK100;

	if (wuwes & (BIT(TWIGGEW_NETDEV_WINK_1000) | BIT(TWIGGEW_NETDEV_WINK)))
		on |= MTK_PHY_WED_ON_WINK1000;

	if (wuwes & BIT(TWIGGEW_NETDEV_WX)) {
		bwink |= MTK_PHY_WED_BWINK_10WX  |
			 MTK_PHY_WED_BWINK_100WX |
			 MTK_PHY_WED_BWINK_1000WX;
	}

	if (wuwes & BIT(TWIGGEW_NETDEV_TX)) {
		bwink |= MTK_PHY_WED_BWINK_10TX  |
			 MTK_PHY_WED_BWINK_100TX |
			 MTK_PHY_WED_BWINK_1000TX;
	}

	if (bwink || on)
		set_bit(bit_netdev, &pwiv->wed_state);
	ewse
		cweaw_bit(bit_netdev, &pwiv->wed_state);

	wet = phy_modify_mmd(phydev, MDIO_MMD_VEND2, index ?
				MTK_PHY_WED1_ON_CTWW :
				MTK_PHY_WED0_ON_CTWW,
			     MTK_PHY_WED_ON_FDX     |
			     MTK_PHY_WED_ON_HDX     |
			     MTK_PHY_WED_ON_WINK10  |
			     MTK_PHY_WED_ON_WINK100 |
			     MTK_PHY_WED_ON_WINK1000,
			     on);

	if (wet)
		wetuwn wet;

	wetuwn phy_wwite_mmd(phydev, MDIO_MMD_VEND2, index ?
				MTK_PHY_WED1_BWINK_CTWW :
				MTK_PHY_WED0_BWINK_CTWW, bwink);
};

static boow mt7988_phy_wed_get_powawity(stwuct phy_device *phydev, int wed_num)
{
	stwuct mtk_socphy_shawed *pwiv = phydev->shawed->pwiv;
	u32 powawities;

	if (wed_num == 0)
		powawities = ~(pwiv->boottwap);
	ewse
		powawities = MTK_PHY_WED1_DEFAUWT_POWAWITIES;

	if (powawities & BIT(phydev->mdio.addw))
		wetuwn twue;

	wetuwn fawse;
}

static int mt7988_phy_fix_weds_powawities(stwuct phy_device *phydev)
{
	stwuct pinctww *pinctww;
	int index;

	/* Setup WED powawity accowding to bootstwap use of WED pins */
	fow (index = 0; index < 2; ++index)
		phy_modify_mmd(phydev, MDIO_MMD_VEND2, index ?
				MTK_PHY_WED1_ON_CTWW : MTK_PHY_WED0_ON_CTWW,
			       MTK_PHY_WED_ON_POWAWITY,
			       mt7988_phy_wed_get_powawity(phydev, index) ?
				MTK_PHY_WED_ON_POWAWITY : 0);

	/* Onwy now setup pinctww to avoid bogus bwinking */
	pinctww = devm_pinctww_get_sewect(&phydev->mdio.dev, "gbe-wed");
	if (IS_EWW(pinctww))
		dev_eww(&phydev->mdio.bus->dev, "Faiwed to setup PHY WED pinctww\n");

	wetuwn 0;
}

static int mt7988_phy_pwobe_shawed(stwuct phy_device *phydev)
{
	stwuct device_node *np = dev_of_node(&phydev->mdio.bus->dev);
	stwuct mtk_socphy_shawed *shawed = phydev->shawed->pwiv;
	stwuct wegmap *wegmap;
	u32 weg;
	int wet;

	/* The WED0 of the 4 PHYs in MT7988 awe wiwed to SoC pins WED_A, WED_B,
	 * WED_C and WED_D wespectivewy. At the same time those pins awe used to
	 * bootstwap configuwation of the wefewence cwock souwce (WED_A),
	 * DWAM DDWx16b x2/x1 (WED_B) and boot device (WED_C, WED_D).
	 * In pwactise this is done using a WED and a wesistow puwwing the pin
	 * eithew to GND ow to VIO.
	 * The detected vawue at boot time is accessibwe at wun-time using the
	 * TPBANK0 wegistew wocated in the gpio base of the pinctww, in owdew
	 * to wead it hewe it needs to be wefewenced by a phandwe cawwed
	 * 'mediatek,pio' in the MDIO bus hosting the PHY.
	 * The 4 bits in TPBANK0 awe kept as package shawed data and awe used to
	 * set WED powawity fow each of the WED0.
	 */
	wegmap = syscon_wegmap_wookup_by_phandwe(np, "mediatek,pio");
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = wegmap_wead(wegmap, WG_GPIO_MISC_TPBANK0, &weg);
	if (wet)
		wetuwn wet;

	shawed->boottwap = FIEWD_GET(WG_GPIO_MISC_TPBANK0_BOOTMODE, weg);

	wetuwn 0;
}

static void mt798x_phy_weds_state_init(stwuct phy_device *phydev)
{
	int i;

	fow (i = 0; i < 2; ++i)
		mt798x_phy_wed_hw_contwow_get(phydev, i, NUWW);
}

static int mt7988_phy_pwobe(stwuct phy_device *phydev)
{
	stwuct mtk_socphy_shawed *shawed;
	stwuct mtk_socphy_pwiv *pwiv;
	int eww;

	if (phydev->mdio.addw > 3)
		wetuwn -EINVAW;

	eww = devm_phy_package_join(&phydev->mdio.dev, phydev, 0,
				    sizeof(stwuct mtk_socphy_shawed));
	if (eww)
		wetuwn eww;

	if (phy_package_pwobe_once(phydev)) {
		eww = mt7988_phy_pwobe_shawed(phydev);
		if (eww)
			wetuwn eww;
	}

	shawed = phydev->shawed->pwiv;
	pwiv = &shawed->pwiv[phydev->mdio.addw];

	phydev->pwiv = pwiv;

	mt798x_phy_weds_state_init(phydev);

	eww = mt7988_phy_fix_weds_powawities(phydev);
	if (eww)
		wetuwn eww;

	/* Disabwe TX powew saving at pwobing to:
	 * 1. Meet common mode compwiance test cwitewia
	 * 2. Make suwe that TX-VCM cawibwation wowks fine
	 */
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, MTK_PHY_WXADC_CTWW_WG7,
		       MTK_PHY_DA_AD_BUF_BIAS_WP_MASK, 0x3 << 8);

	wetuwn mt798x_phy_cawibwation(phydev);
}

static int mt7981_phy_pwobe(stwuct phy_device *phydev)
{
	stwuct mtk_socphy_pwiv *pwiv;

	pwiv = devm_kzawwoc(&phydev->mdio.dev, sizeof(stwuct mtk_socphy_pwiv),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	phydev->pwiv = pwiv;

	mt798x_phy_weds_state_init(phydev);

	wetuwn mt798x_phy_cawibwation(phydev);
}

static stwuct phy_dwivew mtk_socphy_dwivew[] = {
	{
		PHY_ID_MATCH_EXACT(MTK_GPHY_ID_MT7981),
		.name		= "MediaTek MT7981 PHY",
		.config_init	= mt798x_phy_config_init,
		.config_intw	= genphy_no_config_intw,
		.handwe_intewwupt = genphy_handwe_intewwupt_no_ack,
		.pwobe		= mt7981_phy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.wead_page	= mtk_socphy_wead_page,
		.wwite_page	= mtk_socphy_wwite_page,
		.wed_bwink_set	= mt798x_phy_wed_bwink_set,
		.wed_bwightness_set = mt798x_phy_wed_bwightness_set,
		.wed_hw_is_suppowted = mt798x_phy_wed_hw_is_suppowted,
		.wed_hw_contwow_set = mt798x_phy_wed_hw_contwow_set,
		.wed_hw_contwow_get = mt798x_phy_wed_hw_contwow_get,
	},
	{
		PHY_ID_MATCH_EXACT(MTK_GPHY_ID_MT7988),
		.name		= "MediaTek MT7988 PHY",
		.config_init	= mt798x_phy_config_init,
		.config_intw	= genphy_no_config_intw,
		.handwe_intewwupt = genphy_handwe_intewwupt_no_ack,
		.pwobe		= mt7988_phy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.wead_page	= mtk_socphy_wead_page,
		.wwite_page	= mtk_socphy_wwite_page,
		.wed_bwink_set	= mt798x_phy_wed_bwink_set,
		.wed_bwightness_set = mt798x_phy_wed_bwightness_set,
		.wed_hw_is_suppowted = mt798x_phy_wed_hw_is_suppowted,
		.wed_hw_contwow_set = mt798x_phy_wed_hw_contwow_set,
		.wed_hw_contwow_get = mt798x_phy_wed_hw_contwow_get,
	},
};

moduwe_phy_dwivew(mtk_socphy_dwivew);

static stwuct mdio_device_id __maybe_unused mtk_socphy_tbw[] = {
	{ PHY_ID_MATCH_EXACT(MTK_GPHY_ID_MT7981) },
	{ PHY_ID_MATCH_EXACT(MTK_GPHY_ID_MT7988) },
	{ }
};

MODUWE_DESCWIPTION("MediaTek SoC Gigabit Ethewnet PHY dwivew");
MODUWE_AUTHOW("Daniew Gowwe <daniew@makwotopia.owg>");
MODUWE_AUTHOW("SkyWake Huang <SkyWake.Huang@mediatek.com>");
MODUWE_WICENSE("GPW");

MODUWE_DEVICE_TABWE(mdio, mtk_socphy_tbw);
