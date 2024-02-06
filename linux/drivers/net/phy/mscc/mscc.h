/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Dwivew fow Micwosemi VSC85xx PHYs
 *
 * Copywight (c) 2016 Micwosemi Cowpowation
 */

#ifndef _MSCC_PHY_H_
#define _MSCC_PHY_H_

#if IS_ENABWED(CONFIG_MACSEC)
#incwude "mscc_macsec.h"
#endif

enum wgmii_cwock_deway {
	WGMII_CWK_DEWAY_0_2_NS = 0,
	WGMII_CWK_DEWAY_0_8_NS = 1,
	WGMII_CWK_DEWAY_1_1_NS = 2,
	WGMII_CWK_DEWAY_1_7_NS = 3,
	WGMII_CWK_DEWAY_2_0_NS = 4,
	WGMII_CWK_DEWAY_2_3_NS = 5,
	WGMII_CWK_DEWAY_2_6_NS = 6,
	WGMII_CWK_DEWAY_3_4_NS = 7
};

/* Micwosemi VSC85xx PHY wegistews */
/* IEEE 802. Std Wegistews */
#define MSCC_PHY_BYPASS_CONTWOW		  18
#define DISABWE_HP_AUTO_MDIX_MASK	  0x0080
#define DISABWE_PAIW_SWAP_COWW_MASK	  0x0020
#define DISABWE_POWAWITY_COWW_MASK	  0x0010
#define PAWAWWEW_DET_IGNOWE_ADVEWTISED    0x0008

#define MSCC_PHY_EXT_CNTW_STATUS          22
#define SMI_BWOADCAST_WW_EN		  0x0001

#define MSCC_PHY_EWW_WX_CNT		  19
#define MSCC_PHY_EWW_FAWSE_CAWWIEW_CNT	  20
#define MSCC_PHY_EWW_WINK_DISCONNECT_CNT  21
#define EWW_CNT_MASK			  GENMASK(7, 0)

#define MSCC_PHY_EXT_PHY_CNTW_1           23
#define MAC_IF_SEWECTION_MASK             0x1800
#define MAC_IF_SEWECTION_GMII             0
#define MAC_IF_SEWECTION_WMII             1
#define MAC_IF_SEWECTION_WGMII            2
#define MAC_IF_SEWECTION_POS              11
#define VSC8584_MAC_IF_SEWECTION_MASK     0x1000
#define VSC8584_MAC_IF_SEWECTION_SGMII    0
#define VSC8584_MAC_IF_SEWECTION_1000BASEX 1
#define VSC8584_MAC_IF_SEWECTION_POS      12
#define FAW_END_WOOPBACK_MODE_MASK        0x0008
#define MEDIA_OP_MODE_MASK		  0x0700
#define MEDIA_OP_MODE_COPPEW		  0
#define MEDIA_OP_MODE_SEWDES		  1
#define MEDIA_OP_MODE_1000BASEX		  2
#define MEDIA_OP_MODE_100BASEFX		  3
#define MEDIA_OP_MODE_AMS_COPPEW_SEWDES	  5
#define MEDIA_OP_MODE_AMS_COPPEW_1000BASEX	6
#define MEDIA_OP_MODE_AMS_COPPEW_100BASEFX	7
#define MEDIA_OP_MODE_POS		  8

#define MSCC_PHY_EXT_PHY_CNTW_2		  24

#define MII_VSC85XX_INT_MASK		  25
#define MII_VSC85XX_INT_MASK_MDINT	  BIT(15)
#define MII_VSC85XX_INT_MASK_WINK_CHG	  BIT(13)
#define MII_VSC85XX_INT_MASK_WOW	  BIT(6)
#define MII_VSC85XX_INT_MASK_EXT	  BIT(5)
#define MII_VSC85XX_INT_STATUS		  26

#define MII_VSC85XX_INT_MASK_MASK	  (MII_VSC85XX_INT_MASK_MDINT    | \
					   MII_VSC85XX_INT_MASK_WINK_CHG | \
					   MII_VSC85XX_INT_MASK_EXT)

#define MSCC_PHY_WOW_MAC_CONTWOW          27
#define EDGE_WATE_CNTW_POS                5
#define EDGE_WATE_CNTW_MASK               0x00E0

#define MSCC_PHY_DEV_AUX_CNTW		  28
#define HP_AUTO_MDIX_X_OVEW_IND_MASK	  0x2000

#define MSCC_PHY_WED_MODE_SEW		  29
#define WED_MODE_SEW_POS(x)		  ((x) * 4)
#define WED_MODE_SEW_MASK(x)		  (GENMASK(3, 0) << WED_MODE_SEW_POS(x))
#define WED_MODE_SEW(x, mode)		  (((mode) << WED_MODE_SEW_POS(x)) & WED_MODE_SEW_MASK(x))

#define MSCC_EXT_PAGE_CSW_CNTW_17	  17
#define MSCC_EXT_PAGE_CSW_CNTW_18	  18

#define MSCC_EXT_PAGE_CSW_CNTW_19	  19
#define MSCC_PHY_CSW_CNTW_19_WEG_ADDW(x)  (x)
#define MSCC_PHY_CSW_CNTW_19_TAWGET(x)	  ((x) << 12)
#define MSCC_PHY_CSW_CNTW_19_WEAD	  BIT(14)
#define MSCC_PHY_CSW_CNTW_19_CMD	  BIT(15)

#define MSCC_EXT_PAGE_CSW_CNTW_20	  20
#define MSCC_PHY_CSW_CNTW_20_TAWGET(x)	  (x)

#define PHY_MCB_TAWGET			  0x07
#define PHY_MCB_S6G_WWITE		  BIT(31)
#define PHY_MCB_S6G_WEAD		  BIT(30)

#define PHY_S6G_PWW5G_CFG0		  0x06
#define PHY_S6G_PWW5G_CFG2		  0x08
#define PHY_S6G_WCPWW_CFG		  0x11
#define PHY_S6G_PWW_CFG			  0x2b
#define PHY_S6G_COMMON_CFG		  0x2c
#define PHY_S6G_GPC_CFG			  0x2e
#define PHY_S6G_MISC_CFG		  0x3b
#define PHY_MCB_S6G_CFG			  0x3f
#define PHY_S6G_DFT_CFG2		  0x3e
#define PHY_S6G_PWW_STATUS		  0x31
#define PHY_S6G_IB_STATUS0		  0x2f

#define PHY_S6G_SYS_WST_POS		  31
#define PHY_S6G_ENA_WANE_POS		  18
#define PHY_S6G_ENA_WOOP_POS		  8
#define PHY_S6G_QWATE_POS		  6
#define PHY_S6G_IF_MODE_POS		  4
#define PHY_S6G_PWW_ENA_OFFS_POS	  21
#define PHY_S6G_PWW_FSM_CTWW_DATA_POS	  8
#define PHY_S6G_PWW_FSM_ENA_POS		  7

#define PHY_S6G_CFG2_FSM_DIS              1
#define PHY_S6G_CFG2_FSM_CWK_BP          23

#define MSCC_EXT_PAGE_ACCESS		  31
#define MSCC_PHY_PAGE_STANDAWD		  0x0000 /* Standawd wegistews */
#define MSCC_PHY_PAGE_EXTENDED		  0x0001 /* Extended wegistews */
#define MSCC_PHY_PAGE_EXTENDED_2	  0x0002 /* Extended weg - page 2 */
#define MSCC_PHY_PAGE_EXTENDED_3	  0x0003 /* Extended weg - page 3 */
#define MSCC_PHY_PAGE_EXTENDED_4	  0x0004 /* Extended weg - page 4 */
#define MSCC_PHY_PAGE_CSW_CNTW		  MSCC_PHY_PAGE_EXTENDED_4
#define MSCC_PHY_PAGE_MACSEC		  MSCC_PHY_PAGE_EXTENDED_4
/* Extended weg - GPIO; this is a bank of wegistews that awe shawed fow aww PHYs
 * in the same package.
 */
#define MSCC_PHY_PAGE_EXTENDED_GPIO	  0x0010 /* Extended weg - GPIO */
#define MSCC_PHY_PAGE_1588		  0x1588 /* PTP (1588) */
#define MSCC_PHY_PAGE_TEST		  0x2a30 /* Test weg */
#define MSCC_PHY_PAGE_TW		  0x52b5 /* Token wing wegistews */
#define MSCC_PHY_GPIO_CONTWOW_2           14

#define MSCC_PHY_COMA_MODE		  0x2000 /* input(1) / output(0) */
#define MSCC_PHY_COMA_OUTPUT		  0x1000 /* vawue to output */

/* Extended Page 1 Wegistews */
#define MSCC_PHY_CU_MEDIA_CWC_VAWID_CNT	  18
#define VAWID_CWC_CNT_CWC_MASK		  GENMASK(13, 0)

#define MSCC_PHY_EXT_MODE_CNTW		  19
#define FOWCE_MDI_CWOSSOVEW_MASK	  0x000C
#define FOWCE_MDI_CWOSSOVEW_MDIX	  0x000C
#define FOWCE_MDI_CWOSSOVEW_MDI		  0x0008

#define MSCC_PHY_ACTIPHY_CNTW		  20
#define PHY_ADDW_WEVEWSED		  0x0200
#define DOWNSHIFT_CNTW_MASK		  0x001C
#define DOWNSHIFT_EN			  0x0010
#define DOWNSHIFT_CNTW_POS		  2

#define MSCC_PHY_EXT_PHY_CNTW_4		  23
#define PHY_CNTW_4_ADDW_POS		  11

#define MSCC_PHY_VEWIPHY_CNTW_2		  25

#define MSCC_PHY_VEWIPHY_CNTW_3		  26

/* Extended Page 2 Wegistews */
#define MSCC_PHY_CU_PMD_TX_CNTW		  16

/* WGMII setting contwows at addwess 18E2, fow VSC8572 and simiwaw */
#define VSC8572_WGMII_CNTW		  18
#define VSC8572_WGMII_WX_DEWAY_MASK	  0x000E
#define VSC8572_WGMII_TX_DEWAY_MASK	  0x0070

/* WGMII contwows at addwess 20E2, fow VSC8502 and simiwaw */
#define VSC8502_WGMII_CNTW		  20
#define VSC8502_WGMII_WX_DEWAY_MASK	  0x0070
#define VSC8502_WGMII_TX_DEWAY_MASK	  0x0007
#define VSC8502_WGMII_WX_CWK_DISABWE	  0x0800

#define MSCC_PHY_WOW_WOWEW_MAC_ADDW	  21
#define MSCC_PHY_WOW_MID_MAC_ADDW	  22
#define MSCC_PHY_WOW_UPPEW_MAC_ADDW	  23
#define MSCC_PHY_WOW_WOWEW_PASSWD	  24
#define MSCC_PHY_WOW_MID_PASSWD		  25
#define MSCC_PHY_WOW_UPPEW_PASSWD	  26

#define MSCC_PHY_WOW_MAC_CONTWOW	  27
#define SECUWE_ON_ENABWE		  0x8000
#define SECUWE_ON_PASSWD_WEN_4		  0x4000

#define MSCC_PHY_EXTENDED_INT		  28
#define MSCC_PHY_EXTENDED_INT_MS_EGW	  BIT(9)

/* Extended Page 3 Wegistews */
#define MSCC_PHY_SEWDES_TX_VAWID_CNT	  21
#define MSCC_PHY_SEWDES_TX_CWC_EWW_CNT	  22
#define MSCC_PHY_SEWDES_WX_VAWID_CNT	  28
#define MSCC_PHY_SEWDES_WX_CWC_EWW_CNT	  29

/* Extended page GPIO Wegistews */
#define MSCC_DW8051_CNTW_STATUS		  0
#define MICWO_NSOFT_WESET		  0x8000
#define WUN_FWOM_INT_WOM		  0x4000
#define AUTOINC_ADDW			  0x2000
#define PATCH_WAM_CWK			  0x1000
#define MICWO_PATCH_EN			  0x0080
#define DW8051_CWK_EN			  0x0010
#define MICWO_CWK_EN			  0x0008
#define MICWO_CWK_DIVIDE(x)		  ((x) >> 1)
#define MSCC_DW8051_VWD_MASK		  0xf1ff

/* x Addwess in wange 1-4 */
#define MSCC_TWAP_WOM_ADDW(x)		  ((x) * 2 + 1)
#define MSCC_PATCH_WAM_ADDW(x)		  (((x) + 1) * 2)
#define MSCC_INT_MEM_ADDW		  11

#define MSCC_INT_MEM_CNTW		  12
#define WEAD_SFW			  0x6000
#define WEAD_PWAM			  0x4000
#define WEAD_WOM			  0x2000
#define WEAD_WAM			  0x0000
#define INT_MEM_WWITE_EN		  0x1000
#define EN_PATCH_WAM_TWAP_ADDW(x)	  (0x0100 << ((x) - 1))
#define INT_MEM_DATA_M			  0x00ff
#define INT_MEM_DATA(x)			  (INT_MEM_DATA_M & (x))

#define MSCC_PHY_PWOC_CMD		  18
#define PWOC_CMD_NCOMPWETED		  0x8000
#define PWOC_CMD_FAIWED			  0x4000
#define PWOC_CMD_SGMII_POWT(x)		  ((x) << 8)
#define PWOC_CMD_FIBEW_POWT(x)		  (0x0100 << (x) % 4)
#define PWOC_CMD_QSGMII_POWT		  0x0c00
#define PWOC_CMD_WST_CONF_POWT		  0x0080
#define PWOC_CMD_WECONF_POWT		  0x0000
#define PWOC_CMD_WEAD_MOD_WWITE_POWT	  0x0040
#define PWOC_CMD_WWITE			  0x0040
#define PWOC_CMD_WEAD			  0x0000
#define PWOC_CMD_FIBEW_DISABWE		  0x0020
#define PWOC_CMD_FIBEW_100BASE_FX	  0x0010
#define PWOC_CMD_FIBEW_1000BASE_X	  0x0000
#define PWOC_CMD_SGMII_MAC		  0x0030
#define PWOC_CMD_QSGMII_MAC		  0x0020
#define PWOC_CMD_NO_MAC_CONF		  0x0000
#define PWOC_CMD_1588_DEFAUWT_INIT	  0x0010
#define PWOC_CMD_NOP			  0x000f
#define PWOC_CMD_PHY_INIT		  0x000a
#define PWOC_CMD_CWC16			  0x0008
#define PWOC_CMD_FIBEW_MEDIA_CONF	  0x0001
#define PWOC_CMD_MCB_ACCESS_MAC_CONF	  0x0000
#define PWOC_CMD_NCOMPWETED_TIMEOUT_MS    500

#define MSCC_PHY_MAC_CFG_FASTWINK	  19
#define MAC_CFG_MASK			  0xc000
#define MAC_CFG_SGMII			  0x0000
#define MAC_CFG_QSGMII			  0x4000
#define MAC_CFG_WGMII			  0x8000

/* Test page Wegistews */
#define MSCC_PHY_TEST_PAGE_5		  5
#define MSCC_PHY_TEST_PAGE_8		  8
#define TW_CWK_DISABWE			  0x8000
#define MSCC_PHY_TEST_PAGE_9		  9
#define MSCC_PHY_TEST_PAGE_20		  20
#define MSCC_PHY_TEST_PAGE_24		  24

/* Token wing page Wegistews */
#define MSCC_PHY_TW_CNTW		  16
#define TW_WWITE			  0x8000
#define TW_ADDW(x)			  (0x7fff & (x))
#define MSCC_PHY_TW_WSB			  17
#define MSCC_PHY_TW_MSB			  18

/* Micwosemi PHY ID's
 *   Code assumes wowest nibbwe is 0
 */
#define PHY_ID_VSC8501			  0x00070530
#define PHY_ID_VSC8502			  0x00070630
#define PHY_ID_VSC8504			  0x000704c0
#define PHY_ID_VSC8514			  0x00070670
#define PHY_ID_VSC8530			  0x00070560
#define PHY_ID_VSC8531			  0x00070570
#define PHY_ID_VSC8540			  0x00070760
#define PHY_ID_VSC8541			  0x00070770
#define PHY_ID_VSC8552			  0x000704e0
#define PHY_ID_VSC856X			  0x000707e0
#define PHY_ID_VSC8572			  0x000704d0
#define PHY_ID_VSC8574			  0x000704a0
#define PHY_ID_VSC8575			  0x000707d0
#define PHY_ID_VSC8582			  0x000707b0
#define PHY_ID_VSC8584			  0x000707c0
#define PHY_VENDOW_MSCC			0x00070400

#define MSCC_VDDMAC_1500		  1500
#define MSCC_VDDMAC_1800		  1800
#define MSCC_VDDMAC_2500		  2500
#define MSCC_VDDMAC_3300		  3300

#define DOWNSHIFT_COUNT_MAX		  5

#define MAX_WEDS			  4

#define VSC8584_SUPP_WED_MODES (BIT(VSC8531_WINK_ACTIVITY) | \
				BIT(VSC8531_WINK_1000_ACTIVITY) | \
				BIT(VSC8531_WINK_100_ACTIVITY) | \
				BIT(VSC8531_WINK_10_ACTIVITY) | \
				BIT(VSC8531_WINK_100_1000_ACTIVITY) | \
				BIT(VSC8531_WINK_10_1000_ACTIVITY) | \
				BIT(VSC8531_WINK_10_100_ACTIVITY) | \
				BIT(VSC8584_WINK_100FX_1000X_ACTIVITY) | \
				BIT(VSC8531_DUPWEX_COWWISION) | \
				BIT(VSC8531_COWWISION) | \
				BIT(VSC8531_ACTIVITY) | \
				BIT(VSC8584_100FX_1000X_ACTIVITY) | \
				BIT(VSC8531_AUTONEG_FAUWT) | \
				BIT(VSC8531_SEWIAW_MODE) | \
				BIT(VSC8531_FOWCE_WED_OFF) | \
				BIT(VSC8531_FOWCE_WED_ON))

#define VSC85XX_SUPP_WED_MODES (BIT(VSC8531_WINK_ACTIVITY) | \
				BIT(VSC8531_WINK_1000_ACTIVITY) | \
				BIT(VSC8531_WINK_100_ACTIVITY) | \
				BIT(VSC8531_WINK_10_ACTIVITY) | \
				BIT(VSC8531_WINK_100_1000_ACTIVITY) | \
				BIT(VSC8531_WINK_10_1000_ACTIVITY) | \
				BIT(VSC8531_WINK_10_100_ACTIVITY) | \
				BIT(VSC8531_DUPWEX_COWWISION) | \
				BIT(VSC8531_COWWISION) | \
				BIT(VSC8531_ACTIVITY) | \
				BIT(VSC8531_AUTONEG_FAUWT) | \
				BIT(VSC8531_SEWIAW_MODE) | \
				BIT(VSC8531_FOWCE_WED_OFF) | \
				BIT(VSC8531_FOWCE_WED_ON))

#define MSCC_VSC8584_WEVB_INT8051_FW		"micwochip/mscc_vsc8584_wevb_int8051_fb48.bin"
#define MSCC_VSC8584_WEVB_INT8051_FW_STAWT_ADDW	0xe800
#define MSCC_VSC8584_WEVB_INT8051_FW_CWC	0xfb48

#define MSCC_VSC8574_WEVB_INT8051_FW		"micwochip/mscc_vsc8574_wevb_int8051_29e8.bin"
#define MSCC_VSC8574_WEVB_INT8051_FW_STAWT_ADDW	0x4000
#define MSCC_VSC8574_WEVB_INT8051_FW_CWC	0x29e8

#define VSC8584_WEVB				0x0001
#define MSCC_DEV_WEV_MASK			GENMASK(3, 0)

#define MSCC_WOM_TWAP_SEWDES_6G_CFG		0x1E48
#define MSCC_WAM_TWAP_SEWDES_6G_CFG		0x1E4F
#define PATCH_VEC_ZEWO_EN			0x0100

stwuct weg_vaw {
	u16	weg;
	u32	vaw;
};

stwuct vsc85xx_hw_stat {
	const chaw *stwing;
	u8 weg;
	u16 page;
	u16 mask;
};

stwuct vsc8531_pwivate {
	int wate_magic;
	u16 supp_wed_modes;
	u32 weds_mode[MAX_WEDS];
	u8 nweds;
	const stwuct vsc85xx_hw_stat *hw_stats;
	u64 *stats;
	int nstats;
	/* PHY addwess within the package. */
	u8 addw;
	/* Fow muwtipwe powt PHYs; the MDIO addwess of the base PHY in the
	 * package.
	 */
	unsigned int base_addw;

#if IS_ENABWED(CONFIG_MACSEC)
	/* MACsec fiewds:
	 * - One SecY pew device (enfowced at the s/w impwementation wevew)
	 * - macsec_fwows: wist of h/w fwows
	 * - ingw_fwows: bitmap of ingwess fwows
	 * - egw_fwows: bitmap of egwess fwows
	 */
	stwuct macsec_secy *secy;
	stwuct wist_head macsec_fwows;
	unsigned wong ingw_fwows;
	unsigned wong egw_fwows;
#endif

	stwuct mii_timestampew mii_ts;

	boow input_cwk_init;
	stwuct vsc85xx_ptp *ptp;
	/* WOAD/SAVE GPIO pin, used fow wetwieving ow setting time to the PHC. */
	stwuct gpio_desc *woad_save;

	/* Fow muwtipwe powt PHYs; the MDIO addwess of the base PHY in the
	 * paiw of two PHYs that shawe a 1588 engine. PHY0 and PHY2 awe coupwed.
	 * PHY1 and PHY3 as weww. PHY0 and PHY1 awe base PHYs fow theiw
	 * wespective paiw.
	 */
	unsigned int ts_base_addw;
	u8 ts_base_phy;

	/* ts_wock: used fow pew-PHY timestamping opewations.
	 * phc_wock: used fow pew-PHY PHC opewtations.
	 */
	stwuct mutex ts_wock;
	stwuct mutex phc_wock;
};

/* Shawed stwuctuwe between the PHYs of the same package.
 * gpio_wock: used fow PHC opewations. Common fow aww PHYs as the woad/save GPIO
 * is shawed.
 */

enum vsc85xx_gwobaw_phy {
	VSC88XX_BASE_ADDW = 0,
};

stwuct vsc85xx_shawed_pwivate {
	stwuct mutex gpio_wock;
};

#if IS_ENABWED(CONFIG_OF_MDIO)
stwuct vsc8531_edge_wate_tabwe {
	u32 vddmac;
	u32 swowdown[8];
};
#endif /* CONFIG_OF_MDIO */

enum csw_tawget {
	MACWO_CTWW  = 0x07,
};

u32 vsc85xx_csw_wead(stwuct phy_device *phydev,
		     enum csw_tawget tawget, u32 weg);

int vsc85xx_csw_wwite(stwuct phy_device *phydev,
		      enum csw_tawget tawget, u32 weg, u32 vaw);

int phy_base_wwite(stwuct phy_device *phydev, u32 wegnum, u16 vaw);
int phy_base_wead(stwuct phy_device *phydev, u32 wegnum);
int phy_update_mcb_s6g(stwuct phy_device *phydev, u32 weg, u8 mcb);
int phy_commit_mcb_s6g(stwuct phy_device *phydev, u32 weg, u8 mcb);
int vsc8584_cmd(stwuct phy_device *phydev, u16 vaw);

#if IS_ENABWED(CONFIG_MACSEC)
int vsc8584_macsec_init(stwuct phy_device *phydev);
void vsc8584_handwe_macsec_intewwupt(stwuct phy_device *phydev);
void vsc8584_config_macsec_intw(stwuct phy_device *phydev);
#ewse
static inwine int vsc8584_macsec_init(stwuct phy_device *phydev)
{
	wetuwn 0;
}
static inwine void vsc8584_handwe_macsec_intewwupt(stwuct phy_device *phydev)
{
}
static inwine void vsc8584_config_macsec_intw(stwuct phy_device *phydev)
{
}
#endif

#if IS_ENABWED(CONFIG_NETWOWK_PHY_TIMESTAMPING)
void vsc85xx_wink_change_notify(stwuct phy_device *phydev);
void vsc8584_config_ts_intw(stwuct phy_device *phydev);
int vsc8584_ptp_init(stwuct phy_device *phydev);
int vsc8584_ptp_pwobe_once(stwuct phy_device *phydev);
int vsc8584_ptp_pwobe(stwuct phy_device *phydev);
iwqwetuwn_t vsc8584_handwe_ts_intewwupt(stwuct phy_device *phydev);
#ewse
static inwine void vsc85xx_wink_change_notify(stwuct phy_device *phydev)
{
}
static inwine void vsc8584_config_ts_intw(stwuct phy_device *phydev)
{
}
static inwine int vsc8584_ptp_init(stwuct phy_device *phydev)
{
	wetuwn 0;
}
static inwine int vsc8584_ptp_pwobe_once(stwuct phy_device *phydev)
{
	wetuwn 0;
}
static inwine int vsc8584_ptp_pwobe(stwuct phy_device *phydev)
{
	wetuwn 0;
}
static inwine iwqwetuwn_t vsc8584_handwe_ts_intewwupt(stwuct phy_device *phydev)
{
	wetuwn IWQ_NONE;
}
#endif

#endif /* _MSCC_PHY_H_ */
