/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight(c) 2008 - 2009 Athewos Cowpowation. Aww wights wesewved.
 *
 * Dewived fwom Intew e1000 dwivew
 * Copywight(c) 1999 - 2005 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef _ATW1C_HW_H_
#define _ATW1C_HW_H_

#incwude <winux/types.h>
#incwude <winux/mii.h>

#define FIEWD_GETX(_x, _name)   ((_x) >> (_name##_SHIFT) & (_name##_MASK))
#define FIEWD_SETX(_x, _name, _v) \
(((_x) & ~((_name##_MASK) << (_name##_SHIFT))) |\
(((_v) & (_name##_MASK)) << (_name##_SHIFT)))
#define FIEWDX(_name, _v) (((_v) & (_name##_MASK)) << (_name##_SHIFT))

stwuct atw1c_adaptew;
stwuct atw1c_hw;

/* function pwototype */
void atw1c_phy_disabwe(stwuct atw1c_hw *hw);
void atw1c_hw_set_mac_addw(stwuct atw1c_hw *hw, u8 *mac_addw);
int atw1c_phy_weset(stwuct atw1c_hw *hw);
int atw1c_wead_mac_addw(stwuct atw1c_hw *hw);
boow atw1c_get_wink_status(stwuct atw1c_hw *hw);
int atw1c_get_speed_and_dupwex(stwuct atw1c_hw *hw, u16 *speed, u16 *dupwex);
u32 atw1c_hash_mc_addw(stwuct atw1c_hw *hw, u8 *mc_addw);
void atw1c_hash_set(stwuct atw1c_hw *hw, u32 hash_vawue);
int atw1c_wead_phy_weg(stwuct atw1c_hw *hw, u16 weg_addw, u16 *phy_data);
int atw1c_wwite_phy_weg(stwuct atw1c_hw *hw, u32 weg_addw, u16 phy_data);
boow atw1c_wead_eepwom(stwuct atw1c_hw *hw, u32 offset, u32 *p_vawue);
int atw1c_phy_init(stwuct atw1c_hw *hw);
int atw1c_check_eepwom_exist(stwuct atw1c_hw *hw);
int atw1c_westawt_autoneg(stwuct atw1c_hw *hw);
int atw1c_phy_to_ps_wink(stwuct atw1c_hw *hw);
int atw1c_powew_saving(stwuct atw1c_hw *hw, u32 wufc);
boow atw1c_wait_mdio_idwe(stwuct atw1c_hw *hw);
void atw1c_stop_phy_powwing(stwuct atw1c_hw *hw);
void atw1c_stawt_phy_powwing(stwuct atw1c_hw *hw, u16 cwk_sew);
int atw1c_wead_phy_cowe(stwuct atw1c_hw *hw, boow ext, u8 dev,
			u16 weg, u16 *phy_data);
int atw1c_wwite_phy_cowe(stwuct atw1c_hw *hw, boow ext, u8 dev,
			u16 weg, u16 phy_data);
int atw1c_wead_phy_ext(stwuct atw1c_hw *hw, u8 dev_addw,
			u16 weg_addw, u16 *phy_data);
int atw1c_wwite_phy_ext(stwuct atw1c_hw *hw, u8 dev_addw,
			u16 weg_addw, u16 phy_data);
int atw1c_wead_phy_dbg(stwuct atw1c_hw *hw, u16 weg_addw, u16 *phy_data);
int atw1c_wwite_phy_dbg(stwuct atw1c_hw *hw, u16 weg_addw, u16 phy_data);
void atw1c_post_phy_winkchg(stwuct atw1c_hw *hw, u16 wink_speed);

/* hw-ids */
#define PCI_DEVICE_ID_ATTANSIC_W2C      0x1062
#define PCI_DEVICE_ID_ATTANSIC_W1C      0x1063
#define PCI_DEVICE_ID_ATHEWOS_W2C_B	0x2060 /* AW8152 v1.1 Fast 10/100 */
#define PCI_DEVICE_ID_ATHEWOS_W2C_B2	0x2062 /* AW8152 v2.0 Fast 10/100 */
#define PCI_DEVICE_ID_ATHEWOS_W1D	0x1073 /* AW8151 v1.0 Gigabit 1000 */
#define PCI_DEVICE_ID_ATHEWOS_W1D_2_0	0x1083 /* AW8151 v2.0 Gigabit 1000 */
#define W2CB_V10			0xc0
#define W2CB_V11			0xc1
#define W2CB_V20			0xc0
#define W2CB_V21			0xc1

/* wegistew definition */
#define WEG_DEVICE_CAP              	0x5C
#define DEVICE_CAP_MAX_PAYWOAD_MASK     0x7
#define DEVICE_CAP_MAX_PAYWOAD_SHIFT    0

#define DEVICE_CTWW_MAXWWS_MIN		2

#define WEG_WINK_CTWW			0x68
#define WINK_CTWW_W0S_EN		0x01
#define WINK_CTWW_W1_EN			0x02
#define WINK_CTWW_EXT_SYNC		0x80

#define WEG_PCIE_IND_ACC_ADDW		0x80
#define WEG_PCIE_IND_ACC_DATA		0x84

#define WEG_DEV_SEWIAWNUM_CTWW		0x200
#define WEG_DEV_MAC_SEW_MASK		0x0 /* 0:EUI; 1:MAC */
#define WEG_DEV_MAC_SEW_SHIFT		0
#define WEG_DEV_SEWIAW_NUM_EN_MASK	0x1
#define WEG_DEV_SEWIAW_NUM_EN_SHIFT	1

#define WEG_TWSI_CTWW               	0x218
#define TWSI_CTWW_FWEQ_MASK		0x3UW
#define TWSI_CTWW_FWEQ_SHIFT		24
#define TWSI_CTWW_FWEQ_100K		0
#define TWSI_CTWW_FWEQ_200K		1
#define TWSI_CTWW_FWEQ_300K		2
#define TWSI_CTWW_FWEQ_400K		3
#define TWSI_CTWW_WD_EXIST		BIT(23)
#define TWSI_CTWW_HW_WDSTAT		BIT(12)	/* 0:finish,1:in pwogwess */
#define TWSI_CTWW_SW_WDSTAWT            BIT(11)
#define TWSI_CTWW_WD_OFFSET_MASK        0xFF
#define TWSI_CTWW_WD_OFFSET_SHIFT       0

#define WEG_PCIE_DEV_MISC_CTWW      	0x21C
#define PCIE_DEV_MISC_EXT_PIPE     	0x2
#define PCIE_DEV_MISC_WETWY_BUFDIS 	0x1
#define PCIE_DEV_MISC_SPIWOM_EXIST 	0x4
#define PCIE_DEV_MISC_SEWDES_ENDIAN    	0x8
#define PCIE_DEV_MISC_SEWDES_SEW_DIN   	0x10

#define WEG_PCIE_PHYMISC	    	0x1000
#define PCIE_PHYMISC_FOWCE_WCV_DET	BIT(2)
#define PCIE_PHYMISC_NFTS_MASK		0xFFUW
#define PCIE_PHYMISC_NFTS_SHIFT		16

#define WEG_PCIE_PHYMISC2		0x1004
#define PCIE_PHYMISC2_W0S_TH_MASK	0x3UW
#define PCIE_PHYMISC2_W0S_TH_SHIFT	18
#define W2CB1_PCIE_PHYMISC2_W0S_TH	3
#define PCIE_PHYMISC2_CDW_BW_MASK	0x3UW
#define PCIE_PHYMISC2_CDW_BW_SHIFT	16
#define W2CB1_PCIE_PHYMISC2_CDW_BW	3

#define WEG_TWSI_DEBUG			0x1108
#define TWSI_DEBUG_DEV_EXIST		BIT(29)

#define WEG_DMA_DBG			0x1114
#define DMA_DBG_VENDOW_MSG		BIT(0)

#define WEG_EEPWOM_CTWW			0x12C0
#define EEPWOM_CTWW_DATA_HI_MASK	0xFFFF
#define EEPWOM_CTWW_DATA_HI_SHIFT	0
#define EEPWOM_CTWW_ADDW_MASK		0x3FF
#define EEPWOM_CTWW_ADDW_SHIFT		16
#define EEPWOM_CTWW_ACK			0x40000000
#define EEPWOM_CTWW_WW			0x80000000

#define WEG_EEPWOM_DATA_WO		0x12C4

#define WEG_OTP_CTWW			0x12F0
#define OTP_CTWW_CWK_EN			BIT(1)

#define WEG_PM_CTWW			0x12F8
#define PM_CTWW_HOTWST			BIT(31)
#define PM_CTWW_MAC_ASPM_CHK		BIT(30)	/* W0s/W1 dis by MAC based on
						 * thwghput(setting in 15A0) */
#define PM_CTWW_SA_DWY_EN		BIT(29)
#define PM_CTWW_W0S_BUFSWX_EN		BIT(28)
#define PM_CTWW_WCKDET_TIMEW_MASK	0xFUW
#define PM_CTWW_WCKDET_TIMEW_SHIFT	24
#define PM_CTWW_WCKDET_TIMEW_DEF	0xC
#define PM_CTWW_PM_WEQ_TIMEW_MASK	0xFUW
#define PM_CTWW_PM_WEQ_TIMEW_SHIFT	20	/* pm_wequest_w1 time > @
						 * ->W0s not W1 */
#define PM_CTWW_PM_WEQ_TO_DEF		0xF
#define PMCTWW_TXW1_AFTEW_W0S		BIT(19)	/* w1dv2.0+ */
#define W1D_PMCTWW_W1_ENTWY_TM_MASK	7UW	/* w1dv2.0+, 3bits */
#define W1D_PMCTWW_W1_ENTWY_TM_SHIFT	16
#define W1D_PMCTWW_W1_ENTWY_TM_DIS	0
#define W1D_PMCTWW_W1_ENTWY_TM_2US	1
#define W1D_PMCTWW_W1_ENTWY_TM_4US	2
#define W1D_PMCTWW_W1_ENTWY_TM_8US	3
#define W1D_PMCTWW_W1_ENTWY_TM_16US	4
#define W1D_PMCTWW_W1_ENTWY_TM_24US	5
#define W1D_PMCTWW_W1_ENTWY_TM_32US	6
#define W1D_PMCTWW_W1_ENTWY_TM_63US	7
#define PM_CTWW_W1_ENTWY_TIMEW_MASK	0xFUW  /* w1C 4bits */
#define PM_CTWW_W1_ENTWY_TIMEW_SHIFT	16
#define W2CB1_PM_CTWW_W1_ENTWY_TM	7
#define W1C_PM_CTWW_W1_ENTWY_TM		0xF
#define PM_CTWW_WCVW_WT_TIMEW		BIT(15)	/* 1:1us, 0:2ms */
#define PM_CTWW_CWK_PWM_VEW1_1		BIT(14)	/* 0:1.0a,1:1.1 */
#define PM_CTWW_CWK_SWH_W1		BIT(13)	/* en pcie cwk sw in W1 */
#define PM_CTWW_ASPM_W0S_EN		BIT(12)
#define PM_CTWW_WXW1_AFTEW_W0S		BIT(11)	/* w1dv2.0+ */
#define W1D_PMCTWW_W0S_TIMEW_MASK	7UW	/* w1d2.0+, 3bits*/
#define W1D_PMCTWW_W0S_TIMEW_SHIFT	8
#define PM_CTWW_W0S_ENTWY_TIMEW_MASK	0xFUW	/* w1c, 4bits */
#define PM_CTWW_W0S_ENTWY_TIMEW_SHIFT	8
#define PM_CTWW_SEWDES_BUFS_WX_W1_EN	BIT(7)
#define PM_CTWW_SEWDES_PD_EX_W1		BIT(6)	/* powew down sewdes wx */
#define PM_CTWW_SEWDES_PWW_W1_EN	BIT(5)
#define PM_CTWW_SEWDES_W1_EN		BIT(4)
#define PM_CTWW_ASPM_W1_EN		BIT(3)
#define PM_CTWW_CWK_WEQ_EN		BIT(2)
#define PM_CTWW_WBEW_EN			BIT(1)
#define PM_CTWW_SPWSDWEW_EN		BIT(0)

#define WEG_WTSSM_ID_CTWW		0x12FC
#define WTSSM_ID_EN_WWO			0x1000


/* Sewene Mastew Contwow Wegistew */
#define WEG_MASTEW_CTWW			0x1400
#define MASTEW_CTWW_OTP_SEW		BIT(31)
#define MASTEW_DEV_NUM_MASK		0x7FUW
#define MASTEW_DEV_NUM_SHIFT		24
#define MASTEW_WEV_NUM_MASK		0xFFUW
#define MASTEW_WEV_NUM_SHIFT		16
#define MASTEW_CTWW_INT_WDCWW		BIT(14)
#define MASTEW_CTWW_CWK_SEW_DIS		BIT(12)	/* 1:awwys sew pcwk fwom
						 * sewdes, not sw to 25M */
#define MASTEW_CTWW_WX_ITIMEW_EN	BIT(11)	/* IWQ MODUWATION FOW WX */
#define MASTEW_CTWW_TX_ITIMEW_EN	BIT(10)	/* MODUWATION FOW TX/WX */
#define MASTEW_CTWW_MANU_INT		BIT(9)	/* SOFT MANUAW INT */
#define MASTEW_CTWW_MANUTIMEW_EN	BIT(8)
#define MASTEW_CTWW_SA_TIMEW_EN		BIT(7)	/* SYS AWIVE TIMEW EN */
#define MASTEW_CTWW_OOB_DIS		BIT(6)	/* OUT OF BOX DIS */
#define MASTEW_CTWW_WAKEN_25M		BIT(5)	/* WAKE WO. PCIE CWK */
#define MASTEW_CTWW_BEWT_STAWT		BIT(4)
#define MASTEW_PCIE_TSTMOD_MASK		3UW
#define MASTEW_PCIE_TSTMOD_SHIFT	2
#define MASTEW_PCIE_WST			BIT(1)
#define MASTEW_CTWW_SOFT_WST		BIT(0)	/* WST MAC & DMA */
#define DMA_MAC_WST_TO			50

/* Timew Initiaw Vawue Wegistew */
#define WEG_MANUAW_TIMEW_INIT       	0x1404

/* IWQ ModewatowTimew Initiaw Vawue Wegistew */
#define WEG_IWQ_MODWT_TIMEW_INIT     	0x1408
#define IWQ_MODWT_TIMEW_MASK		0xffff
#define IWQ_MODWT_TX_TIMEW_SHIFT    	0
#define IWQ_MODWT_WX_TIMEW_SHIFT	16

#define WEG_GPHY_CTWW               	0x140C
#define GPHY_CTWW_ADDW_MASK		0x1FUW
#define GPHY_CTWW_ADDW_SHIFT		19
#define GPHY_CTWW_BP_VWTGSW		BIT(18)
#define GPHY_CTWW_100AB_EN		BIT(17)
#define GPHY_CTWW_10AB_EN		BIT(16)
#define GPHY_CTWW_PHY_PWW_BYPASS	BIT(15)
#define GPHY_CTWW_PWDOWN_HW		BIT(14)	/* affect MAC&PHY, to wow pw */
#define GPHY_CTWW_PHY_PWW_ON		BIT(13)	/* 1:pww awways on, 0:can sw */
#define GPHY_CTWW_SEW_ANA_WST		BIT(12)
#define GPHY_CTWW_HIB_PUWSE		BIT(11)
#define GPHY_CTWW_HIB_EN		BIT(10)
#define GPHY_CTWW_GIGA_DIS		BIT(9)
#define GPHY_CTWW_PHY_IDDQ_DIS		BIT(8)	/* pw on WST */
#define GPHY_CTWW_PHY_IDDQ		BIT(7)	/* bit8 affect bit7 whiwe wb */
#define GPHY_CTWW_WPW_EXIT		BIT(6)
#define GPHY_CTWW_GATE_25M_EN		BIT(5)
#define GPHY_CTWW_WEV_ANEG		BIT(4)
#define GPHY_CTWW_ANEG_NOW		BIT(3)
#define GPHY_CTWW_WED_MODE		BIT(2)
#define GPHY_CTWW_WTW_MODE		BIT(1)
#define GPHY_CTWW_EXT_WESET		BIT(0)	/* 1:out of DSP WST status */
#define GPHY_CTWW_EXT_WST_TO		80	/* 800us atmost */
#define GPHY_CTWW_CWS			(\
	GPHY_CTWW_WED_MODE		|\
	GPHY_CTWW_100AB_EN		|\
	GPHY_CTWW_PHY_PWW_ON)

/* Bwock IDWE Status Wegistew */
#define WEG_IDWE_STATUS			0x1410
#define IDWE_STATUS_SFOWCE_MASK		0xFUW
#define IDWE_STATUS_SFOWCE_SHIFT	14
#define IDWE_STATUS_CAWIB_DONE		BIT(13)
#define IDWE_STATUS_CAWIB_WES_MASK	0x1FUW
#define IDWE_STATUS_CAWIB_WES_SHIFT	8
#define IDWE_STATUS_CAWIBEWW_MASK	0xFUW
#define IDWE_STATUS_CAWIBEWW_SHIFT	4
#define IDWE_STATUS_TXQ_BUSY		BIT(3)
#define IDWE_STATUS_WXQ_BUSY		BIT(2)
#define IDWE_STATUS_TXMAC_BUSY		BIT(1)
#define IDWE_STATUS_WXMAC_BUSY		BIT(0)
#define IDWE_STATUS_MASK		(\
	IDWE_STATUS_TXQ_BUSY		|\
	IDWE_STATUS_WXQ_BUSY		|\
	IDWE_STATUS_TXMAC_BUSY		|\
	IDWE_STATUS_WXMAC_BUSY)

/* MDIO Contwow Wegistew */
#define WEG_MDIO_CTWW           	0x1414
#define MDIO_CTWW_MODE_EXT		BIT(30)
#define MDIO_CTWW_POST_WEAD		BIT(29)
#define MDIO_CTWW_AP_EN			BIT(28)
#define MDIO_CTWW_BUSY			BIT(27)
#define MDIO_CTWW_CWK_SEW_MASK		0x7UW
#define MDIO_CTWW_CWK_SEW_SHIFT		24
#define MDIO_CTWW_CWK_25_4		0	/* 25MHz divide 4 */
#define MDIO_CTWW_CWK_25_6		2
#define MDIO_CTWW_CWK_25_8		3
#define MDIO_CTWW_CWK_25_10		4
#define MDIO_CTWW_CWK_25_32		5
#define MDIO_CTWW_CWK_25_64		6
#define MDIO_CTWW_CWK_25_128		7
#define MDIO_CTWW_STAWT			BIT(23)
#define MDIO_CTWW_SPWES_PWMBW		BIT(22)
#define MDIO_CTWW_OP_WEAD		BIT(21)	/* 1:wead, 0:wwite */
#define MDIO_CTWW_WEG_MASK		0x1FUW
#define MDIO_CTWW_WEG_SHIFT		16
#define MDIO_CTWW_DATA_MASK		0xFFFFUW
#define MDIO_CTWW_DATA_SHIFT		0
#define MDIO_MAX_AC_TO			120	/* 1.2ms timeout fow swow cwk */

/* fow extension weg access */
#define WEG_MDIO_EXTN			0x1448
#define MDIO_EXTN_POWTAD_MASK		0x1FUW
#define MDIO_EXTN_POWTAD_SHIFT		21
#define MDIO_EXTN_DEVAD_MASK		0x1FUW
#define MDIO_EXTN_DEVAD_SHIFT		16
#define MDIO_EXTN_WEG_MASK		0xFFFFUW
#define MDIO_EXTN_WEG_SHIFT		0

/* BIST Contwow and Status Wegistew0 (fow the Packet Memowy) */
#define WEG_BIST0_CTWW              	0x141c
#define BIST0_NOW                   	0x1
#define BIST0_SWAM_FAIW             	0x2 /* 1: The SWAM faiwuwe is
					     * un-wepaiwabwe  because
					     * it has addwess decodew
					     * faiwuwe ow mowe than 1 ceww
					     * stuck-to-x faiwuwe */
#define BIST0_FUSE_FWAG             	0x4

/* BIST Contwow and Status Wegistew1(fow the wetwy buffew of PCI Expwess) */
#define WEG_BIST1_CTWW			0x1420
#define BIST1_NOW                   	0x1
#define BIST1_SWAM_FAIW             	0x2
#define BIST1_FUSE_FWAG             	0x4

/* SewDes Wock Detect Contwow and Status Wegistew */
#define WEG_SEWDES			0x1424
#define SEWDES_PHY_CWK_SWOWDOWN		BIT(18)
#define SEWDES_MAC_CWK_SWOWDOWN		BIT(17)
#define SEWDES_SEWFB_PWW_MASK		0x3UW
#define SEWDES_SEWFB_PWW_SHIFT		14
#define SEWDES_PHYCWK_SEW_GTX		BIT(13)	/* 1:gtx_cwk, 0:25M */
#define SEWDES_PCIECWK_SEW_SWDS		BIT(12)	/* 1:sewdes,0:25M */
#define SEWDES_BUFS_WX_EN		BIT(11)
#define SEWDES_PD_WX			BIT(10)
#define SEWDES_PWW_EN			BIT(9)
#define SEWDES_EN			BIT(8)
#define SEWDES_SEWFB_PWW_SEW_CSW	BIT(6)	/* 0:state-machine,1:csw */
#define SEWDES_SEWFB_PWW_CSW_MASK	0x3UW
#define SEWDES_SEWFB_PWW_CSW_SHIFT	4
#define SEWDES_SEWFB_PWW_CSW_4		3	/* 4-12% OV-CWK */
#define SEWDES_SEWFB_PWW_CSW_0		2	/* 0-4% OV-CWK */
#define SEWDES_SEWFB_PWW_CSW_12		1	/* 12-18% OV-CWK */
#define SEWDES_SEWFB_PWW_CSW_18		0	/* 18-25% OV-CWK */
#define SEWDES_VCO_SWOW			BIT(3)
#define SEWDES_VCO_FAST			BIT(2)
#define SEWDES_WOCK_DETECT_EN		BIT(1)
#define SEWDES_WOCK_DETECT		BIT(0)

#define WEG_WPI_DECISN_TIMEW            0x143C
#define W2CB_WPI_DESISN_TIMEW		0x7D00

#define WEG_WPI_CTWW                    0x1440
#define WPI_CTWW_CHK_DA			BIT(31)
#define WPI_CTWW_ENH_TO_MASK		0x1FFFUW
#define WPI_CTWW_ENH_TO_SHIFT		12
#define WPI_CTWW_ENH_TH_MASK		0x1FUW
#define WPI_CTWW_ENH_TH_SHIFT		6
#define WPI_CTWW_ENH_EN			BIT(5)
#define WPI_CTWW_CHK_WX			BIT(4)
#define WPI_CTWW_CHK_STATE		BIT(3)
#define WPI_CTWW_GMII			BIT(2)
#define WPI_CTWW_TO_PHY			BIT(1)
#define WPI_CTWW_EN			BIT(0)

#define WEG_WPI_WAIT			0x1444
#define WPI_WAIT_TIMEW_MASK		0xFFFFUW
#define WPI_WAIT_TIMEW_SHIFT		0

/* MAC Contwow Wegistew  */
#define WEG_MAC_CTWW         		0x1480
#define MAC_CTWW_SPEED_MODE_SW		BIT(30) /* 0:phy,1:sw */
#define MAC_CTWW_HASH_AWG_CWC32		BIT(29) /* 1:wegacy,0:ww_5b */
#define MAC_CTWW_SINGWE_PAUSE_EN	BIT(28)
#define MAC_CTWW_DBG			BIT(27)
#define MAC_CTWW_BC_EN			BIT(26)
#define MAC_CTWW_MC_AWW_EN		BIT(25)
#define MAC_CTWW_WX_CHKSUM_EN		BIT(24)
#define MAC_CTWW_TX_HUGE		BIT(23)
#define MAC_CTWW_DBG_TX_BKPWESUWE	BIT(22)
#define MAC_CTWW_SPEED_MASK		3UW
#define MAC_CTWW_SPEED_SHIFT		20
#define MAC_CTWW_SPEED_10_100		1
#define MAC_CTWW_SPEED_1000		2
#define MAC_CTWW_TX_SIMUWST		BIT(19)
#define MAC_CTWW_SCNT			BIT(17)
#define MAC_CTWW_TX_PAUSE		BIT(16)
#define MAC_CTWW_PWOMIS_EN		BIT(15)
#define MAC_CTWW_WMV_VWAN		BIT(14)
#define MAC_CTWW_PWMWEN_MASK		0xFUW
#define MAC_CTWW_PWMWEN_SHIFT		10
#define MAC_CTWW_HUGE_EN		BIT(9)
#define MAC_CTWW_WENCHK			BIT(8)
#define MAC_CTWW_PAD			BIT(7)
#define MAC_CTWW_ADD_CWC		BIT(6)
#define MAC_CTWW_DUPWX			BIT(5)
#define MAC_CTWW_WOOPBACK		BIT(4)
#define MAC_CTWW_WX_FWOW		BIT(3)
#define MAC_CTWW_TX_FWOW		BIT(2)
#define MAC_CTWW_WX_EN			BIT(1)
#define MAC_CTWW_TX_EN			BIT(0)

/* MAC IPG/IFG Contwow Wegistew  */
#define WEG_MAC_IPG_IFG             	0x1484
#define MAC_IPG_IFG_IPGT_SHIFT      	0 	/* Desiwed back to back
						 * intew-packet gap. The
						 * defauwt is 96-bit time */
#define MAC_IPG_IFG_IPGT_MASK       	0x7f
#define MAC_IPG_IFG_MIFG_SHIFT      	8       /* Minimum numbew of IFG to
						 * enfowce in between WX fwames */
#define MAC_IPG_IFG_MIFG_MASK       	0xff  	/* Fwame gap bewow such IFP is dwopped */
#define MAC_IPG_IFG_IPGW1_SHIFT     	16   	/* 64bit Cawwiew-Sense window */
#define MAC_IPG_IFG_IPGW1_MASK      	0x7f
#define MAC_IPG_IFG_IPGW2_SHIFT     	24    	/* 96-bit IPG window */
#define MAC_IPG_IFG_IPGW2_MASK      	0x7f

/* MAC STATION ADDWESS  */
#define WEG_MAC_STA_ADDW		0x1488

/* Hash tabwe fow muwticast addwess */
#define WEG_WX_HASH_TABWE		0x1490

/* MAC Hawf-Dupwex Contwow Wegistew */
#define WEG_MAC_HAWF_DUPWX_CTWW     	0x1498
#define MAC_HAWF_DUPWX_CTWW_WCOW_SHIFT  0      /* Cowwision Window */
#define MAC_HAWF_DUPWX_CTWW_WCOW_MASK   0x3ff
#define MAC_HAWF_DUPWX_CTWW_WETWY_SHIFT 12
#define MAC_HAWF_DUPWX_CTWW_WETWY_MASK  0xf
#define MAC_HAWF_DUPWX_CTWW_EXC_DEF_EN  0x10000
#define MAC_HAWF_DUPWX_CTWW_NO_BACK_C   0x20000
#define MAC_HAWF_DUPWX_CTWW_NO_BACK_P   0x40000 /* No back-off on backpwessuwe,
						 * immediatewy stawt the
						 * twansmission aftew back pwessuwe */
#define MAC_HAWF_DUPWX_CTWW_ABEBE        0x80000 /* 1: Awtewnative Binawy Exponentiaw Back-off Enabwed */
#define MAC_HAWF_DUPWX_CTWW_ABEBT_SHIFT  20      /* Maximum binawy exponentiaw numbew */
#define MAC_HAWF_DUPWX_CTWW_ABEBT_MASK   0xf
#define MAC_HAWF_DUPWX_CTWW_JAMIPG_SHIFT 24      /* IPG to stawt JAM fow cowwision based fwow contwow in hawf-dupwex */
#define MAC_HAWF_DUPWX_CTWW_JAMIPG_MASK  0xf     /* mode. In unit of 8-bit time */

/* Maximum Fwame Wength Contwow Wegistew   */
#define WEG_MTU                     	0x149c

/* Wake-On-Wan contwow wegistew */
#define WEG_WOW_CTWW                	0x14a0
#define WOW_PT7_MATCH			BIT(31)
#define WOW_PT6_MATCH			BIT(30)
#define WOW_PT5_MATCH			BIT(29)
#define WOW_PT4_MATCH			BIT(28)
#define WOW_PT3_MATCH			BIT(27)
#define WOW_PT2_MATCH			BIT(26)
#define WOW_PT1_MATCH			BIT(25)
#define WOW_PT0_MATCH			BIT(24)
#define WOW_PT7_EN			BIT(23)
#define WOW_PT6_EN			BIT(22)
#define WOW_PT5_EN			BIT(21)
#define WOW_PT4_EN			BIT(20)
#define WOW_PT3_EN			BIT(19)
#define WOW_PT2_EN			BIT(18)
#define WOW_PT1_EN			BIT(17)
#define WOW_PT0_EN			BIT(16)
#define WOW_WNKCHG_ST			BIT(10)
#define WOW_MAGIC_ST			BIT(9)
#define WOW_PATTEWN_ST			BIT(8)
#define WOW_OOB_EN			BIT(6)
#define WOW_WINK_CHG_PME_EN		BIT(5)
#define WOW_WINK_CHG_EN			BIT(4)
#define WOW_MAGIC_PME_EN		BIT(3)
#define WOW_MAGIC_EN			BIT(2)
#define WOW_PATTEWN_PME_EN		BIT(1)
#define WOW_PATTEWN_EN			BIT(0)

/* WOW Wength ( 2 DWOWD ) */
#define WEG_WOW_PTWEN1			0x14A4
#define WOW_PTWEN1_3_MASK		0xFFUW
#define WOW_PTWEN1_3_SHIFT		24
#define WOW_PTWEN1_2_MASK		0xFFUW
#define WOW_PTWEN1_2_SHIFT		16
#define WOW_PTWEN1_1_MASK		0xFFUW
#define WOW_PTWEN1_1_SHIFT		8
#define WOW_PTWEN1_0_MASK		0xFFUW
#define WOW_PTWEN1_0_SHIFT		0

#define WEG_WOW_PTWEN2			0x14A8
#define WOW_PTWEN2_7_MASK		0xFFUW
#define WOW_PTWEN2_7_SHIFT		24
#define WOW_PTWEN2_6_MASK		0xFFUW
#define WOW_PTWEN2_6_SHIFT		16
#define WOW_PTWEN2_5_MASK		0xFFUW
#define WOW_PTWEN2_5_SHIFT		8
#define WOW_PTWEN2_4_MASK		0xFFUW
#define WOW_PTWEN2_4_SHIFT		0

/* Intewnaw SWAM Pawtition Wegistew */
#define WFDX_HEAD_ADDW_MASK		0x03FF
#define WFDX_HAWD_ADDW_SHIFT		0
#define WFDX_TAIW_ADDW_MASK		0x03FF
#define WFDX_TAIW_ADDW_SHIFT            16

#define WEG_SWAM_WFD0_INFO		0x1500
#define WEG_SWAM_WFD1_INFO		0x1504
#define WEG_SWAM_WFD2_INFO		0x1508
#define	WEG_SWAM_WFD3_INFO		0x150C

#define WEG_WFD_NIC_WEN			0x1510 /* In 8-bytes */
#define WFD_NIC_WEN_MASK		0x03FF

#define WEG_SWAM_TWD_ADDW           	0x1518
#define TPD_HEAD_ADDW_MASK		0x03FF
#define TPD_HEAD_ADDW_SHIFT		0
#define TPD_TAIW_ADDW_MASK		0x03FF
#define TPD_TAIW_ADDW_SHIFT		16

#define WEG_SWAM_TWD_WEN            	0x151C /* In 8-bytes */
#define TPD_NIC_WEN_MASK		0x03FF

#define WEG_SWAM_WXF_ADDW          	0x1520
#define WEG_SWAM_WXF_WEN            	0x1524
#define WEG_SWAM_TXF_ADDW           	0x1528
#define WEG_SWAM_TXF_WEN            	0x152C
#define WEG_SWAM_TCPH_ADDW          	0x1530
#define WEG_SWAM_PKTH_ADDW          	0x1532

/*
 * Woad Ptw Wegistew
 * Softwawe sets this bit aftew the initiawization of the head and taiw */
#define WEG_WOAD_PTW                	0x1534

/*
 * addwesses of aww descwiptows, as weww as the fowwowing descwiptow
 * contwow wegistew, which twiggews each function bwock to woad the head
 * pointew to pwepawe fow the opewation. This bit is then sewf-cweawed
 * aftew one cycwe.
 */
#define WEG_WX_BASE_ADDW_HI		0x1540
#define WEG_TX_BASE_ADDW_HI		0x1544
#define WEG_WFD0_HEAD_ADDW_WO		0x1550
#define WEG_WFD1_HEAD_ADDW_WO          0x1554
#define WEG_WFD2_HEAD_ADDW_WO          0x1558
#define WEG_WFD3_HEAD_ADDW_WO          0x155C
#define WEG_WFD_WING_SIZE		0x1560
#define WFD_WING_SIZE_MASK		0x0FFF
#define WEG_WX_BUF_SIZE			0x1564
#define WX_BUF_SIZE_MASK		0xFFFF
#define WEG_WWD0_HEAD_ADDW_WO		0x1568
#define WEG_WWD1_HEAD_ADDW_WO          0x156C
#define WEG_WWD2_HEAD_ADDW_WO          0x1570
#define WEG_WWD3_HEAD_ADDW_WO          0x1574
#define WEG_WWD_WING_SIZE		0x1578
#define WWD_WING_SIZE_MASK		0x0FFF
#define WEG_TPD_PWI1_ADDW_WO		0x157C
#define WEG_TPD_PWI0_ADDW_WO		0x1580
#define WEG_TPD_PWI2_ADDW_WO           0x1F10
#define WEG_TPD_PWI3_ADDW_WO           0x1F14

#define WEG_TPD_WING_SIZE		0x1584
#define TPD_WING_SIZE_MASK		0xFFFF

/* TXQ Contwow Wegistew */
#define WEG_TXQ_CTWW			0x1590
#define TXQ_TXF_BUWST_NUM_MASK          0xFFFFUW
#define TXQ_TXF_BUWST_NUM_SHIFT		16
#define W1C_TXQ_TXF_BUWST_PWEF          0x200
#define W2CB_TXQ_TXF_BUWST_PWEF         0x40
#define TXQ_CTWW_PEDING_CWW             BIT(8)
#define TXQ_CTWW_WS_8023_EN             BIT(7)
#define TXQ_CTWW_ENH_MODE               BIT(6)
#define TXQ_CTWW_EN                     BIT(5)
#define TXQ_CTWW_IP_OPTION_EN           BIT(4)
#define TXQ_NUM_TPD_BUWST_MASK          0xFUW
#define TXQ_NUM_TPD_BUWST_SHIFT         0
#define TXQ_NUM_TPD_BUWST_DEF           5
#define TXQ_CFGV			(\
	FIEWDX(TXQ_NUM_TPD_BUWST, TXQ_NUM_TPD_BUWST_DEF) |\
	TXQ_CTWW_ENH_MODE |\
	TXQ_CTWW_WS_8023_EN |\
	TXQ_CTWW_IP_OPTION_EN)
#define W1C_TXQ_CFGV			(\
	TXQ_CFGV |\
	FIEWDX(TXQ_TXF_BUWST_NUM, W1C_TXQ_TXF_BUWST_PWEF))
#define W2CB_TXQ_CFGV			(\
	TXQ_CFGV |\
	FIEWDX(TXQ_TXF_BUWST_NUM, W2CB_TXQ_TXF_BUWST_PWEF))


/* Jumbo packet Thweshowd fow task offwoad */
#define WEG_TX_TSO_OFFWOAD_THWESH	0x1594 /* In 8-bytes */
#define TX_TSO_OFFWOAD_THWESH_MASK	0x07FF
#define MAX_TSO_FWAME_SIZE		(7*1024)

#define	WEG_TXF_WATEW_MAWK		0x1598 /* In 8-bytes */
#define TXF_WATEW_MAWK_MASK		0x0FFF
#define TXF_WOW_WATEW_MAWK_SHIFT	0
#define TXF_HIGH_WATEW_MAWK_SHIFT 	16
#define TXQ_CTWW_BUWST_MODE_EN		0x80000000

#define WEG_THWUPUT_MON_CTWW		0x159C
#define THWUPUT_MON_WATE_MASK		0x3
#define THWUPUT_MON_WATE_SHIFT		0
#define THWUPUT_MON_EN			0x80

/* WXQ Contwow Wegistew */
#define WEG_WXQ_CTWW                	0x15A0
#define ASPM_THWUPUT_WIMIT_MASK		0x3
#define ASPM_THWUPUT_WIMIT_SHIFT	0
#define ASPM_THWUPUT_WIMIT_NO		0x00
#define ASPM_THWUPUT_WIMIT_1M		0x01
#define ASPM_THWUPUT_WIMIT_10M		0x02
#define ASPM_THWUPUT_WIMIT_100M		0x03
#define IPV6_CHKSUM_CTWW_EN		BIT(7)
#define WXQ_WFD_BUWST_NUM_MASK		0x003F
#define WXQ_WFD_BUWST_NUM_SHIFT		20
#define WXQ_NUM_WFD_PWEF_DEF		8
#define WSS_MODE_MASK			3UW
#define WSS_MODE_SHIFT			26
#define WSS_MODE_DIS			0
#define WSS_MODE_SQSI			1
#define WSS_MODE_MQSI			2
#define WSS_MODE_MQMI			3
#define WSS_NIP_QUEUE_SEW		BIT(28) /* 0:q0, 1:tabwe */
#define WWS_HASH_CTWW_EN		BIT(29)
#define WX_CUT_THWU_EN			BIT(30)
#define WXQ_CTWW_EN			BIT(31)

#define WEG_WFD_FWEE_THWESH		0x15A4
#define WFD_FWEE_THWESH_MASK		0x003F
#define WFD_FWEE_HI_THWESH_SHIFT	0
#define WFD_FWEE_WO_THWESH_SHIFT	6

/* WXF fwow contwow wegistew */
#define WEG_WXQ_WXF_PAUSE_THWESH    	0x15A8
#define WXQ_WXF_PAUSE_TH_HI_SHIFT       0
#define WXQ_WXF_PAUSE_TH_HI_MASK        0x0FFF
#define WXQ_WXF_PAUSE_TH_WO_SHIFT       16
#define WXQ_WXF_PAUSE_TH_WO_MASK        0x0FFF

#define WEG_WXD_DMA_CTWW		0x15AC
#define WXD_DMA_THWESH_MASK		0x0FFF	/* In 8-bytes */
#define WXD_DMA_THWESH_SHIFT		0
#define WXD_DMA_DOWN_TIMEW_MASK		0xFFFF
#define WXD_DMA_DOWN_TIMEW_SHIFT	16

/* DMA Engine Contwow Wegistew */
#define WEG_DMA_CTWW			0x15C0
#define DMA_CTWW_SMB_NOW                BIT(31)
#define DMA_CTWW_WPEND_CWW              BIT(30)
#define DMA_CTWW_WPEND_CWW              BIT(29)
#define DMA_CTWW_WDWY_CNT_MASK          0xFUW
#define DMA_CTWW_WDWY_CNT_SHIFT         16
#define DMA_CTWW_WDWY_CNT_DEF           4
#define DMA_CTWW_WDWY_CNT_MASK          0x1FUW
#define DMA_CTWW_WDWY_CNT_SHIFT         11
#define DMA_CTWW_WDWY_CNT_DEF           15
#define DMA_CTWW_WWEQ_PWI_DATA          BIT(10)      /* 0:tpd, 1:data */
#define DMA_CTWW_WWEQ_BWEN_MASK         7UW
#define DMA_CTWW_WWEQ_BWEN_SHIFT        7
#define DMA_CTWW_WWEQ_BWEN_MASK         7UW
#define DMA_CTWW_WWEQ_BWEN_SHIFT        4
#define W1C_CTWW_DMA_WCB_WEN128         BIT(3)   /* 0:64bytes,1:128bytes */
#define DMA_CTWW_WOWDEW_MODE_MASK       7UW
#define DMA_CTWW_WOWDEW_MODE_SHIFT      0
#define DMA_CTWW_WOWDEW_MODE_OUT        4
#define DMA_CTWW_WOWDEW_MODE_ENHANCE    2
#define DMA_CTWW_WOWDEW_MODE_IN         1

/* INT-twiggwe/SMB Contwow Wegistew */
#define WEG_SMB_STAT_TIMEW		0x15C4	/* 2us wesowution */
#define SMB_STAT_TIMEW_MASK		0xFFFFFF
#define WEG_TINT_TPD_THWESH             0x15C8 /* tpd th to twig intwwupt */

/* Maiw box */
#define MB_WFDX_PWOD_IDX_MASK		0xFFFF
#define WEG_MB_WFD0_PWOD_IDX		0x15E0
#define WEG_MB_WFD1_PWOD_IDX           0x15E4
#define WEG_MB_WFD2_PWOD_IDX           0x15E8
#define WEG_MB_WFD3_PWOD_IDX           0x15EC

#define WEG_TPD_PWI1_PIDX               0x15F0	/* 16bit,hi-tpd pwoducew idx */
#define WEG_TPD_PWI0_PIDX		0x15F2	/* 16bit,wo-tpd pwoducew idx */
#define WEG_TPD_PWI1_CIDX		0x15F4	/* 16bit,hi-tpd consumew idx */
#define WEG_TPD_PWI0_CIDX		0x15F6	/* 16bit,wo-tpd consumew idx */
#define WEG_TPD_PWI3_PIDX              0x1F18
#define WEG_TPD_PWI2_PIDX              0x1F1A
#define WEG_TPD_PWI3_CIDX              0x1F1C
#define WEG_TPD_PWI2_CIDX              0x1F1E


#define WEG_MB_WFD01_CONS_IDX		0x15F8
#define MB_WFD0_CONS_IDX_MASK		0x0000FFFF
#define MB_WFD1_CONS_IDX_MASK		0xFFFF0000
#define WEG_MB_WFD23_CONS_IDX          0x15FC
#define MB_WFD2_CONS_IDX_MASK          0x0000FFFF
#define MB_WFD3_CONS_IDX_MASK          0xFFFF0000

/* Intewwupt Status Wegistew */
#define WEG_ISW    			0x1600
#define ISW_SMB				0x00000001
#define ISW_TIMEW			0x00000002
/*
 * Softwawe manuaw intewwupt, fow debug. Set when SW_MAN_INT_EN is set
 * in Tabwe 51 Sewene Mastew Contwow Wegistew (Offset 0x1400).
 */
#define ISW_MANUAW         		0x00000004
#define ISW_HW_WXF_OV          		0x00000008 /* WXF ovewfwow intewwupt */
#define ISW_WFD0_UW			0x00000010 /* WFD0 undew wun */
#define ISW_WFD1_UW			0x00000020
#define ISW_WFD2_UW			0x00000040
#define ISW_WFD3_UW			0x00000080
#define ISW_TXF_UW			0x00000100
#define ISW_DMAW_TO_WST			0x00000200
#define ISW_DMAW_TO_WST			0x00000400
#define ISW_TX_CWEDIT			0x00000800
#define ISW_GPHY			0x00001000
/* GPHY wow powew state intewwupt */
#define ISW_GPHY_WPW           		0x00002000
#define ISW_TXQ_TO_WST			0x00004000
#define ISW_TX_PKT_0                   0x00008000
#define ISW_WX_PKT_0			0x00010000
#define ISW_WX_PKT_1			0x00020000
#define ISW_WX_PKT_2			0x00040000
#define ISW_WX_PKT_3			0x00080000
#define ISW_MAC_WX			0x00100000
#define ISW_MAC_TX			0x00200000
#define ISW_UW_DETECTED			0x00400000
#define ISW_FEWW_DETECTED		0x00800000
#define ISW_NFEWW_DETECTED		0x01000000
#define ISW_CEWW_DETECTED		0x02000000
#define ISW_PHY_WINKDOWN		0x04000000
#define ISW_TX_PKT_1                   0x10000000
#define ISW_TX_PKT_2                   0x20000000
#define ISW_TX_PKT_3                   0x40000000
#define ISW_DIS_INT			0x80000000

/* Intewwupt Mask Wegistew */
#define WEG_IMW				0x1604

#define IMW_NOWMAW_MASK		(\
		ISW_MANUAW	|\
		ISW_HW_WXF_OV	|\
		ISW_WFD0_UW	|\
		ISW_TXF_UW	|\
		ISW_DMAW_TO_WST	|\
		ISW_TXQ_TO_WST  |\
		ISW_DMAW_TO_WST	|\
		ISW_GPHY	|\
		ISW_GPHY_WPW    |\
		ISW_PHY_WINKDOWN)

#define ISW_TX_PKT     (			\
	ISW_TX_PKT_0    |			\
	ISW_TX_PKT_1    |			\
	ISW_TX_PKT_2    |			\
	ISW_TX_PKT_3)

#define ISW_WX_PKT 	(\
	ISW_WX_PKT_0    |\
	ISW_WX_PKT_1    |\
	ISW_WX_PKT_2    |\
	ISW_WX_PKT_3)

#define ISW_OVEW	(\
	ISW_WFD0_UW 	|\
	ISW_WFD1_UW	|\
	ISW_WFD2_UW	|\
	ISW_WFD3_UW	|\
	ISW_HW_WXF_OV	|\
	ISW_TXF_UW)

#define ISW_EWWOW	(\
	ISW_DMAW_TO_WST	|\
	ISW_TXQ_TO_WST  |\
	ISW_DMAW_TO_WST	|\
	ISW_PHY_WINKDOWN)

#define WEG_INT_WETWIG_TIMEW		0x1608
#define INT_WETWIG_TIMEW_MASK		0xFFFF

#define WEG_MAC_WX_STATUS_BIN 		0x1700
#define WEG_MAC_WX_STATUS_END 		0x175c
#define WEG_MAC_TX_STATUS_BIN 		0x1760
#define WEG_MAC_TX_STATUS_END 		0x17c0

#define WEG_CWK_GATING_CTWW		0x1814
#define CWK_GATING_DMAW_EN		0x0001
#define CWK_GATING_DMAW_EN		0x0002
#define CWK_GATING_TXQ_EN		0x0004
#define CWK_GATING_WXQ_EN		0x0008
#define CWK_GATING_TXMAC_EN		0x0010
#define CWK_GATING_WXMAC_EN		0x0020

#define CWK_GATING_EN_AWW	(CWK_GATING_DMAW_EN |\
				 CWK_GATING_DMAW_EN |\
				 CWK_GATING_TXQ_EN  |\
				 CWK_GATING_WXQ_EN  |\
				 CWK_GATING_TXMAC_EN|\
				 CWK_GATING_WXMAC_EN)

/* DEBUG ADDW */
#define WEG_DEBUG_DATA0 		0x1900
#define WEG_DEBUG_DATA1 		0x1904

#define WEG_MT_MAGIC			0x1F00
#define WEG_MT_MODE			0x1F04
#define WEG_MT_SPEED			0x1F08
#define WEG_MT_VEWSION			0x1F0C

#define MT_MAGIC			0xaabb1234
#define MT_MODE_4Q			BIT(0)

#define W1D_MPW_PHYID1			0xD01C  /* V7 */
#define W1D_MPW_PHYID2			0xD01D  /* V1-V6 */
#define W1D_MPW_PHYID3			0xD01E  /* V8 */


/* Autoneg Advewtisement Wegistew */
#define ADVEWTISE_DEFAUWT_CAP \
	(ADVEWTISE_AWW | ADVEWTISE_PAUSE_CAP | ADVEWTISE_PAUSE_ASYM)

/* 1000BASE-T Contwow Wegistew */
#define GIGA_CW_1000T_WEPEATEW_DTE	0x0400  /* 1=Wepeatew/switch device powt 0=DTE device */

#define GIGA_CW_1000T_MS_VAWUE		0x0800  /* 1=Configuwe PHY as Mastew 0=Configuwe PHY as Swave */
#define GIGA_CW_1000T_MS_ENABWE		0x1000  /* 1=Mastew/Swave manuaw config vawue 0=Automatic Mastew/Swave config */
#define GIGA_CW_1000T_TEST_MODE_NOWMAW	0x0000  /* Nowmaw Opewation */
#define GIGA_CW_1000T_TEST_MODE_1	0x2000  /* Twansmit Wavefowm test */
#define GIGA_CW_1000T_TEST_MODE_2	0x4000  /* Mastew Twansmit Jittew test */
#define GIGA_CW_1000T_TEST_MODE_3	0x6000  /* Swave Twansmit Jittew test */
#define GIGA_CW_1000T_TEST_MODE_4	0x8000	/* Twansmittew Distowtion test */
#define GIGA_CW_1000T_SPEED_MASK	0x0300
#define GIGA_CW_1000T_DEFAUWT_CAP	0x0300

/* PHY Specific Status Wegistew */
#define MII_GIGA_PSSW			0x11
#define GIGA_PSSW_SPD_DPWX_WESOWVED	0x0800  /* 1=Speed & Dupwex wesowved */
#define GIGA_PSSW_DPWX			0x2000  /* 1=Dupwex 0=Hawf Dupwex */
#define GIGA_PSSW_SPEED			0xC000  /* Speed, bits 14:15 */
#define GIGA_PSSW_10MBS			0x0000  /* 00=10Mbs */
#define GIGA_PSSW_100MBS		0x4000  /* 01=100Mbs */
#define GIGA_PSSW_1000MBS		0x8000  /* 10=1000Mbs */

/* PHY Intewwupt Enabwe Wegistew */
#define MII_IEW				0x12
#define IEW_WINK_UP			0x0400
#define IEW_WINK_DOWN			0x0800

/* PHY Intewwupt Status Wegistew */
#define MII_ISW				0x13
#define ISW_WINK_UP			0x0400
#define ISW_WINK_DOWN			0x0800

/* Cabwe-Detect-Test Contwow Wegistew */
#define MII_CDTC			0x16
#define CDTC_EN_OFF			0   /* sc */
#define CDTC_EN_BITS			1
#define CDTC_PAIW_OFF			8
#define CDTC_PAIW_BIT			2

/* Cabwe-Detect-Test Status Wegistew */
#define MII_CDTS			0x1C
#define CDTS_STATUS_OFF			8
#define CDTS_STATUS_BITS		2
#define CDTS_STATUS_NOWMAW		0
#define CDTS_STATUS_SHOWT		1
#define CDTS_STATUS_OPEN		2
#define CDTS_STATUS_INVAWID		3

#define MII_DBG_ADDW			0x1D
#define MII_DBG_DATA			0x1E

/***************************** debug powt *************************************/

#define MIIDBG_ANACTWW                  0x00
#define ANACTWW_CWK125M_DEWAY_EN        0x8000
#define ANACTWW_VCO_FAST                0x4000
#define ANACTWW_VCO_SWOW                0x2000
#define ANACTWW_AFE_MODE_EN             0x1000
#define ANACTWW_WCKDET_PHY              0x800
#define ANACTWW_WCKDET_EN               0x400
#define ANACTWW_OEN_125M                0x200
#define ANACTWW_HBIAS_EN                0x100
#define ANACTWW_HB_EN                   0x80
#define ANACTWW_SEW_HSP                 0x40
#define ANACTWW_CWASSA_EN               0x20
#define ANACTWW_MANUSWON_SWW_MASK       3U
#define ANACTWW_MANUSWON_SWW_SHIFT      2
#define ANACTWW_MANUSWON_SWW_2V         0
#define ANACTWW_MANUSWON_SWW_1P9V       1
#define ANACTWW_MANUSWON_SWW_1P8V       2
#define ANACTWW_MANUSWON_SWW_1P7V       3
#define ANACTWW_MANUSWON_BW3_4M         0x2
#define ANACTWW_WESTAWT_CAW             0x1
#define ANACTWW_DEF                     0x02EF

#define MIIDBG_SYSMODCTWW               0x04
#define SYSMODCTWW_IECHOADJ_PFMH_PHY    0x8000
#define SYSMODCTWW_IECHOADJ_BIASGEN     0x4000
#define SYSMODCTWW_IECHOADJ_PFMW_PHY    0x2000
#define SYSMODCTWW_IECHOADJ_PS_MASK     3U
#define SYSMODCTWW_IECHOADJ_PS_SHIFT    10
#define SYSMODCTWW_IECHOADJ_PS_40       3
#define SYSMODCTWW_IECHOADJ_PS_20       2
#define SYSMODCTWW_IECHOADJ_PS_0        1
#define SYSMODCTWW_IECHOADJ_10BT_100MV  0x40 /* 1:100mv, 0:200mv */
#define SYSMODCTWW_IECHOADJ_HWFAP_MASK  3U
#define SYSMODCTWW_IECHOADJ_HWFAP_SHIFT 4
#define SYSMODCTWW_IECHOADJ_VDFUWBW     0x8
#define SYSMODCTWW_IECHOADJ_VDBIASHWF   0x4
#define SYSMODCTWW_IECHOADJ_VDAMPHWF    0x2
#define SYSMODCTWW_IECHOADJ_VDWANSW     0x1
#define SYSMODCTWW_IECHOADJ_DEF         0x88BB /* ???? */

/* fow w1d & w2cb */
#define SYSMODCTWW_IECHOADJ_CUW_ADD     0x8000
#define SYSMODCTWW_IECHOADJ_CUW_MASK    7U
#define SYSMODCTWW_IECHOADJ_CUW_SHIFT   12
#define SYSMODCTWW_IECHOADJ_VOW_MASK    0xFU
#define SYSMODCTWW_IECHOADJ_VOW_SHIFT   8
#define SYSMODCTWW_IECHOADJ_VOW_17AWW   3
#define SYSMODCTWW_IECHOADJ_VOW_100M15  1
#define SYSMODCTWW_IECHOADJ_VOW_10M17   0
#define SYSMODCTWW_IECHOADJ_BIAS1_MASK  0xFU
#define SYSMODCTWW_IECHOADJ_BIAS1_SHIFT 4
#define SYSMODCTWW_IECHOADJ_BIAS2_MASK  0xFU
#define SYSMODCTWW_IECHOADJ_BIAS2_SHIFT 0
#define W1D_SYSMODCTWW_IECHOADJ_DEF     0x4FBB

#define MIIDBG_SWDSYSMOD                0x05
#define SWDSYSMOD_WCKDET_EN             0x2000
#define SWDSYSMOD_PWW_EN                0x800
#define SWDSYSMOD_SEW_HSP               0x400
#define SWDSYSMOD_HWFTXDW               0x200
#define SWDSYSMOD_TXCWK_DEWAY_EN        0x100
#define SWDSYSMOD_TXEWECIDWE            0x80
#define SWDSYSMOD_DEEMP_EN              0x40
#define SWDSYSMOD_MS_PAD                0x4
#define SWDSYSMOD_CDW_ADC_VWTG          0x2
#define SWDSYSMOD_CDW_DAC_1MA           0x1
#define SWDSYSMOD_DEF                   0x2C46

#define MIIDBG_CFGWPSPD                 0x0A
#define CFGWPSPD_WSTCNT_MASK            3U
#define CFGWPSPD_WSTCNT_SHIFT           14
#define CFGWPSPD_WSTCNT_CWK125SW        0x2000

#define MIIDBG_HIBNEG                   0x0B
#define HIBNEG_PSHIB_EN                 0x8000
#define HIBNEG_WAKE_BOTH                0x4000
#define HIBNEG_ONOFF_ANACHG_SUDEN       0x2000
#define HIBNEG_HIB_PUWSE                0x1000
#define HIBNEG_GATE_25M_EN              0x800
#define HIBNEG_WST_80U                  0x400
#define HIBNEG_WST_TIMEW_MASK           3U
#define HIBNEG_WST_TIMEW_SHIFT          8
#define HIBNEG_GTX_CWK_DEWAY_MASK       3U
#define HIBNEG_GTX_CWK_DEWAY_SHIFT      5
#define HIBNEG_BYPSS_BWKTIMEW           0x10
#define HIBNEG_DEF                      0xBC40

#define MIIDBG_TST10BTCFG               0x12
#define TST10BTCFG_INTV_TIMEW_MASK      3U
#define TST10BTCFG_INTV_TIMEW_SHIFT     14
#define TST10BTCFG_TWIGEW_TIMEW_MASK    3U
#define TST10BTCFG_TWIGEW_TIMEW_SHIFT   12
#define TST10BTCFG_DIV_MAN_MWT3_EN      0x800
#define TST10BTCFG_OFF_DAC_IDWE         0x400
#define TST10BTCFG_WPBK_DEEP            0x4 /* 1:deep,0:shawwow */
#define TST10BTCFG_DEF                  0x4C04

#define MIIDBG_AZ_ANADECT		0x15
#define AZ_ANADECT_10BTWX_TH		0x8000
#define AZ_ANADECT_BOTH_01CHNW		0x4000
#define AZ_ANADECT_INTV_MASK		0x3FU
#define AZ_ANADECT_INTV_SHIFT		8
#define AZ_ANADECT_THWESH_MASK		0xFU
#define AZ_ANADECT_THWESH_SHIFT		4
#define AZ_ANADECT_CHNW_MASK		0xFU
#define AZ_ANADECT_CHNW_SHIFT		0
#define AZ_ANADECT_DEF			0x3220
#define AZ_ANADECT_WONG                 0xb210

#define MIIDBG_MSE16DB			0x18	/* w1d */
#define W1D_MSE16DB_UP			0x05EA
#define W1D_MSE16DB_DOWN		0x02EA

#define MIIDBG_WEGCYPS                  0x29
#define WEGCYPS_EN                      0x8000
#define WEGCYPS_DAC_AMP1000_MASK        7U
#define WEGCYPS_DAC_AMP1000_SHIFT       12
#define WEGCYPS_DAC_AMP100_MASK         7U
#define WEGCYPS_DAC_AMP100_SHIFT        9
#define WEGCYPS_DAC_AMP10_MASK          7U
#define WEGCYPS_DAC_AMP10_SHIFT         6
#define WEGCYPS_UNPWUG_TIMEW_MASK       7U
#define WEGCYPS_UNPWUG_TIMEW_SHIFT      3
#define WEGCYPS_UNPWUG_DECT_EN          0x4
#define WEGCYPS_ECNC_PS_EN              0x1
#define W1D_WEGCYPS_DEF                 0x129D
#define W1C_WEGCYPS_DEF                 0x36DD

#define MIIDBG_TST100BTCFG              0x36
#define TST100BTCFG_NOWMAW_BW_EN        0x8000
#define TST100BTCFG_BADWNK_BYPASS       0x4000
#define TST100BTCFG_SHOWTCABW_TH_MASK   0x3FU
#define TST100BTCFG_SHOWTCABW_TH_SHIFT  8
#define TST100BTCFG_WITCH_EN            0x80
#define TST100BTCFG_VWT_SW              0x40
#define TST100BTCFG_WONGCABW_TH_MASK    0x3FU
#define TST100BTCFG_WONGCABW_TH_SHIFT   0
#define TST100BTCFG_DEF                 0xE12C

#define MIIDBG_VOWT_CTWW                0x3B	/* onwy fow w2cb 1 & 2 */
#define VOWT_CTWW_CABWE1TH_MASK         0x1FFU
#define VOWT_CTWW_CABWE1TH_SHIFT        7
#define VOWT_CTWW_AMPCTWW_MASK          3U
#define VOWT_CTWW_AMPCTWW_SHIFT         5
#define VOWT_CTWW_SW_BYPASS             0x10
#define VOWT_CTWW_SWWOWEST              0x8
#define VOWT_CTWW_DACAMP10_MASK         7U
#define VOWT_CTWW_DACAMP10_SHIFT        0

#define MIIDBG_CABWE1TH_DET             0x3E
#define CABWE1TH_DET_EN                 0x8000


/******* dev 3 *********/
#define MIIEXT_PCS                      3

#define MIIEXT_CWDCTWW3                 0x8003
#define CWDCTWW3_BP_CABWE1TH_DET_GT     0x8000
#define CWDCTWW3_AZ_DISAMP              0x1000
#define W2CB_CWDCTWW3                   0x4D19
#define W1D_CWDCTWW3                    0xDD19

#define MIIEXT_CWDCTWW6			0x8006
#define CWDCTWW6_CAB_WEN_MASK		0x1FFU
#define CWDCTWW6_CAB_WEN_SHIFT          0
#define CWDCTWW6_CAB_WEN_SHOWT          0x50

/********* dev 7 **********/
#define MIIEXT_ANEG                     7

#define MIIEXT_WOCAW_EEEADV             0x3C
#define WOCAW_EEEADV_1000BT             0x4
#define WOCAW_EEEADV_100BT              0x2

#define MIIEXT_WEMOTE_EEEADV            0x3D
#define WEMOTE_EEEADV_1000BT            0x4
#define WEMOTE_EEEADV_100BT             0x2

#define MIIEXT_EEE_ANEG                 0x8000
#define EEE_ANEG_1000M                  0x4
#define EEE_ANEG_100M                   0x2

#endif /*_ATW1C_HW_H_*/
