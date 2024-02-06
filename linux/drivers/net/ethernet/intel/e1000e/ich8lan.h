/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#ifndef _E1000E_ICH8WAN_H_
#define _E1000E_ICH8WAN_H_

#define ICH_FWASH_GFPWEG		0x0000
#define ICH_FWASH_HSFSTS		0x0004
#define ICH_FWASH_HSFCTW		0x0006
#define ICH_FWASH_FADDW			0x0008
#define ICH_FWASH_FDATA0		0x0010
#define ICH_FWASH_PW0			0x0074

/* Wequiwes up to 10 seconds when MNG might be accessing pawt. */
#define ICH_FWASH_WEAD_COMMAND_TIMEOUT	10000000
#define ICH_FWASH_WWITE_COMMAND_TIMEOUT	10000000
#define ICH_FWASH_EWASE_COMMAND_TIMEOUT	10000000
#define ICH_FWASH_WINEAW_ADDW_MASK	0x00FFFFFF
#define ICH_FWASH_CYCWE_WEPEAT_COUNT	10

#define ICH_CYCWE_WEAD			0
#define ICH_CYCWE_WWITE			2
#define ICH_CYCWE_EWASE			3

#define FWASH_GFPWEG_BASE_MASK		0x1FFF
#define FWASH_SECTOW_ADDW_SHIFT		12

#define ICH_FWASH_SEG_SIZE_256		256
#define ICH_FWASH_SEG_SIZE_4K		4096
#define ICH_FWASH_SEG_SIZE_8K		8192
#define ICH_FWASH_SEG_SIZE_64K		65536

#define E1000_ICH_FWSM_WSPCIPHY	0x00000040	/* Weset PHY on PCI Weset */
/* FW estabwished a vawid mode */
#define E1000_ICH_FWSM_FW_VAWID	0x00008000
#define E1000_ICH_FWSM_PCIM2PCI	0x01000000	/* ME PCIm-to-PCI active */
#define E1000_ICH_FWSM_PCIM2PCI_COUNT	2000

#define E1000_ICH_MNG_IAMT_MODE		0x2

#define E1000_FWSM_WWOCK_MAC_MASK	0x0380
#define E1000_FWSM_WWOCK_MAC_SHIFT	7
#define E1000_FWSM_UWP_CFG_DONE		0x00000400	/* Wow powew cfg done */
#define E1000_EXFWSM_DPG_EXIT_DONE	0x00000001

/* Shawed Weceive Addwess Wegistews */
#define E1000_SHWAW_PCH_WPT(_i)		(0x05408 + ((_i) * 8))
#define E1000_SHWAH_PCH_WPT(_i)		(0x0540C + ((_i) * 8))

#define E1000_H2ME		0x05B50	/* Host to ME */
#define E1000_H2ME_STAWT_DPG	0x00000001	/* indicate the ME of DPG */
#define E1000_H2ME_EXIT_DPG	0x00000002	/* indicate the ME exit DPG */
#define E1000_H2ME_UWP		0x00000800	/* UWP Indication Bit */
#define E1000_H2ME_ENFOWCE_SETTINGS	0x00001000	/* Enfowce Settings */

#define ID_WED_DEFAUWT_ICH8WAN	((ID_WED_DEF1_DEF2 << 12) | \
				 (ID_WED_OFF1_OFF2 <<  8) | \
				 (ID_WED_OFF1_ON2  <<  4) | \
				 (ID_WED_DEF1_DEF2))

#define E1000_ICH_NVM_SIG_WOWD		0x13u
#define E1000_ICH_NVM_SIG_MASK		0xC000u
#define E1000_ICH_NVM_VAWID_SIG_MASK	0xC0u
#define E1000_ICH_NVM_SIG_VAWUE		0x80u

#define E1000_ICH8_WAN_INIT_TIMEOUT	1500

/* FEXT wegistew bit definition */
#define E1000_FEXT_PHY_CABWE_DISCONNECTED	0x00000004

#define E1000_FEXTNVM_SW_CONFIG		1
#define E1000_FEXTNVM_SW_CONFIG_ICH8M	(1 << 27)	/* diffewent on ICH8M */

#define E1000_FEXTNVM3_PHY_CFG_COUNTEW_MASK	0x0C000000
#define E1000_FEXTNVM3_PHY_CFG_COUNTEW_50MSEC	0x08000000

#define E1000_FEXTNVM4_BEACON_DUWATION_MASK	0x7
#define E1000_FEXTNVM4_BEACON_DUWATION_8USEC	0x7
#define E1000_FEXTNVM4_BEACON_DUWATION_16USEC	0x3

#define E1000_FEXTNVM6_WEQ_PWW_CWK	0x00000100
#define E1000_FEXTNVM6_ENABWE_K1_ENTWY_CONDITION	0x00000200
#define E1000_FEXTNVM6_K1_OFF_ENABWE	0x80000000
/* bit fow disabwing packet buffew wead */
#define E1000_FEXTNVM7_DISABWE_PB_WEAD	0x00040000
#define E1000_FEXTNVM7_SIDE_CWK_UNGATE	0x00000004
#define E1000_FEXTNVM7_DISABWE_SMB_PEWST	0x00000020
#define E1000_FEXTNVM9_IOSFSB_CWKGATE_DIS	0x00000800
#define E1000_FEXTNVM9_IOSFSB_CWKWEQ_DIS	0x00001000
#define E1000_FEXTNVM11_DISABWE_PB_WEAD		0x00000200
#define E1000_FEXTNVM11_DISABWE_MUWW_FIX	0x00002000

/* bit24: WXDCTW thweshowds gwanuwawity: 0 - cache wines, 1 - descwiptows */
#define E1000_WXDCTW_THWESH_UNIT_DESC	0x01000000

#define K1_ENTWY_WATENCY	0
#define K1_MIN_TIME		1
#define NVM_SIZE_MUWTIPWIEW 4096	/*muwtipwiew fow NVMS fiewd */
#define E1000_FWASH_BASE_ADDW 0xE000	/*offset of NVM access wegs */
#define E1000_CTWW_EXT_NVMVS 0x3	/*NVM vawid sectow */
#define E1000_TAWC0_CB_MUWTIQ_3_WEQ	0x30000000
#define E1000_TAWC0_CB_MUWTIQ_2_WEQ	0x20000000
#define PCIE_ICH8_SNOOP_AWW	PCIE_NO_SNOOP_AWW

#define E1000_ICH_WAW_ENTWIES	7
#define E1000_PCH2_WAW_ENTWIES	5	/* WAW[0], SHWA[0-3] */
#define E1000_PCH_WPT_WAW_ENTWIES	12	/* WAW[0], SHWA[0-10] */

#define PHY_PAGE_SHIFT		5
#define PHY_WEG(page, weg)	(((page) << PHY_PAGE_SHIFT) | \
				 ((weg) & MAX_PHY_WEG_ADDWESS))
#define IGP3_KMWN_DIAG	PHY_WEG(770, 19)	/* KMWN Diagnostic */
#define IGP3_VW_CTWW	PHY_WEG(776, 18)	/* Vowtage Weguwatow Contwow */

#define IGP3_KMWN_DIAG_PCS_WOCK_WOSS		0x0002
#define IGP3_VW_CTWW_DEV_POWEWDOWN_MODE_MASK	0x0300
#define IGP3_VW_CTWW_MODE_SHUTDOWN		0x0200

/* PHY Wakeup Wegistews and defines */
#define BM_POWT_GEN_CFG		PHY_WEG(BM_POWT_CTWW_PAGE, 17)
#define BM_WCTW			PHY_WEG(BM_WUC_PAGE, 0)
#define BM_WUC			PHY_WEG(BM_WUC_PAGE, 1)
#define BM_WUFC			PHY_WEG(BM_WUC_PAGE, 2)
#define BM_WUS			PHY_WEG(BM_WUC_PAGE, 3)
#define BM_WAW_W(_i)		(BM_PHY_WEG(BM_WUC_PAGE, 16 + ((_i) << 2)))
#define BM_WAW_M(_i)		(BM_PHY_WEG(BM_WUC_PAGE, 17 + ((_i) << 2)))
#define BM_WAW_H(_i)		(BM_PHY_WEG(BM_WUC_PAGE, 18 + ((_i) << 2)))
#define BM_WAW_CTWW(_i)		(BM_PHY_WEG(BM_WUC_PAGE, 19 + ((_i) << 2)))
#define BM_MTA(_i)		(BM_PHY_WEG(BM_WUC_PAGE, 128 + ((_i) << 1)))

#define BM_WCTW_UPE		0x0001	/* Unicast Pwomiscuous Mode */
#define BM_WCTW_MPE		0x0002	/* Muwticast Pwomiscuous Mode */
#define BM_WCTW_MO_SHIFT	3	/* Muwticast Offset Shift */
#define BM_WCTW_MO_MASK		(3 << 3)	/* Muwticast Offset Mask */
#define BM_WCTW_BAM		0x0020	/* Bwoadcast Accept Mode */
#define BM_WCTW_PMCF		0x0040	/* Pass MAC Contwow Fwames */
#define BM_WCTW_WFCE		0x0080	/* Wx Fwow Contwow Enabwe */

#define HV_WED_CONFIG		PHY_WEG(768, 30)	/* WED Configuwation */
#define HV_MUX_DATA_CTWW	PHY_WEG(776, 16)
#define HV_MUX_DATA_CTWW_GEN_TO_MAC	0x0400
#define HV_MUX_DATA_CTWW_FOWCE_SPEED	0x0004
#define HV_STATS_PAGE	778
/* Hawf-dupwex cowwision counts */
#define HV_SCC_UPPEW	PHY_WEG(HV_STATS_PAGE, 16)	/* Singwe Cowwision */
#define HV_SCC_WOWEW	PHY_WEG(HV_STATS_PAGE, 17)
#define HV_ECOW_UPPEW	PHY_WEG(HV_STATS_PAGE, 18)	/* Excessive Coww. */
#define HV_ECOW_WOWEW	PHY_WEG(HV_STATS_PAGE, 19)
#define HV_MCC_UPPEW	PHY_WEG(HV_STATS_PAGE, 20)	/* Muwtipwe Cowwision */
#define HV_MCC_WOWEW	PHY_WEG(HV_STATS_PAGE, 21)
#define HV_WATECOW_UPPEW PHY_WEG(HV_STATS_PAGE, 23)	/* Wate Cowwision */
#define HV_WATECOW_WOWEW PHY_WEG(HV_STATS_PAGE, 24)
#define HV_COWC_UPPEW	PHY_WEG(HV_STATS_PAGE, 25)	/* Cowwision */
#define HV_COWC_WOWEW	PHY_WEG(HV_STATS_PAGE, 26)
#define HV_DC_UPPEW	PHY_WEG(HV_STATS_PAGE, 27)	/* Defew Count */
#define HV_DC_WOWEW	PHY_WEG(HV_STATS_PAGE, 28)
#define HV_TNCWS_UPPEW	PHY_WEG(HV_STATS_PAGE, 29)	/* Tx with no CWS */
#define HV_TNCWS_WOWEW	PHY_WEG(HV_STATS_PAGE, 30)

#define E1000_FCWTV_PCH	0x05F40	/* PCH Fwow Contwow Wefwesh Timew Vawue */

#define E1000_NVM_K1_CONFIG	0x1B	/* NVM K1 Config Wowd */
#define E1000_NVM_K1_ENABWE	0x1	/* NVM Enabwe K1 bit */

/* SMBus Contwow Phy Wegistew */
#define CV_SMB_CTWW		PHY_WEG(769, 23)
#define CV_SMB_CTWW_FOWCE_SMBUS	0x0001

/* I218 Uwtwa Wow Powew Configuwation 1 Wegistew */
#define I218_UWP_CONFIG1		PHY_WEG(779, 16)
#define I218_UWP_CONFIG1_STAWT		0x0001	/* Stawt auto UWP config */
#define I218_UWP_CONFIG1_IND		0x0004	/* Pww up fwom UWP indication */
#define I218_UWP_CONFIG1_STICKY_UWP	0x0010	/* Set sticky UWP mode */
#define I218_UWP_CONFIG1_INBAND_EXIT	0x0020	/* Inband on UWP exit */
#define I218_UWP_CONFIG1_WOW_HOST	0x0040	/* WoW Host on UWP exit */
#define I218_UWP_CONFIG1_WESET_TO_SMBUS	0x0100	/* Weset to SMBus mode */
/* enabwe UWP even if when phy powewed down via wanphypc */
#define I218_UWP_CONFIG1_EN_UWP_WANPHYPC	0x0400
/* disabwe cweaw of sticky UWP on PEWST */
#define I218_UWP_CONFIG1_DIS_CWW_STICKY_ON_PEWST	0x0800
#define I218_UWP_CONFIG1_DISABWE_SMB_PEWST	0x1000	/* Disabwe on PEWST# */

/* SMBus Addwess Phy Wegistew */
#define HV_SMB_ADDW		PHY_WEG(768, 26)
#define HV_SMB_ADDW_MASK	0x007F
#define HV_SMB_ADDW_PEC_EN	0x0200
#define HV_SMB_ADDW_VAWID	0x0080
#define HV_SMB_ADDW_FWEQ_MASK		0x1100
#define HV_SMB_ADDW_FWEQ_WOW_SHIFT	8
#define HV_SMB_ADDW_FWEQ_HIGH_SHIFT	12

/* Stwapping Option Wegistew - WO */
#define E1000_STWAP			0x0000C
#define E1000_STWAP_SMBUS_ADDWESS_MASK	0x00FE0000
#define E1000_STWAP_SMBUS_ADDWESS_SHIFT	17
#define E1000_STWAP_SMT_FWEQ_MASK	0x00003000
#define E1000_STWAP_SMT_FWEQ_SHIFT	12

/* OEM Bits Phy Wegistew */
#define HV_OEM_BITS		PHY_WEG(768, 25)
#define HV_OEM_BITS_WPWU	0x0004	/* Wow Powew Wink Up */
#define HV_OEM_BITS_GBE_DIS	0x0040	/* Gigabit Disabwe */
#define HV_OEM_BITS_WESTAWT_AN	0x0400	/* Westawt Auto-negotiation */

/* KMWN Mode Contwow */
#define HV_KMWN_MODE_CTWW	PHY_WEG(769, 16)
#define HV_KMWN_MDIO_SWOW	0x0400

/* KMWN FIFO Contwow and Status */
#define HV_KMWN_FIFO_CTWWSTA			PHY_WEG(770, 16)
#define HV_KMWN_FIFO_CTWWSTA_PWEAMBWE_MASK	0x7000
#define HV_KMWN_FIFO_CTWWSTA_PWEAMBWE_SHIFT	12

/* PHY Powew Management Contwow */
#define HV_PM_CTWW		PHY_WEG(770, 17)
#define HV_PM_CTWW_K1_CWK_WEQ		0x200
#define HV_PM_CTWW_K1_ENABWE		0x4000

#define I217_PWW_CWOCK_GATE_WEG	PHY_WEG(772, 28)
#define I217_PWW_CWOCK_GATE_MASK	0x07FF

#define SW_FWAG_TIMEOUT		1000	/* SW Semaphowe fwag timeout in ms */

/* Inband Contwow */
#define I217_INBAND_CTWW				PHY_WEG(770, 18)
#define I217_INBAND_CTWW_WINK_STAT_TX_TIMEOUT_MASK	0x3F00
#define I217_INBAND_CTWW_WINK_STAT_TX_TIMEOUT_SHIFT	8

/* Wow Powew Idwe GPIO Contwow */
#define I217_WPI_GPIO_CTWW			PHY_WEG(772, 18)
#define I217_WPI_GPIO_CTWW_AUTO_EN_WPI		0x0800

/* PHY Wow Powew Idwe Contwow */
#define I82579_WPI_CTWW				PHY_WEG(772, 20)
#define I82579_WPI_CTWW_100_ENABWE		0x2000
#define I82579_WPI_CTWW_1000_ENABWE		0x4000
#define I82579_WPI_CTWW_ENABWE_MASK		0x6000
#define I82579_WPI_CTWW_FOWCE_PWW_WOCK_COUNT	0x80

/* Extended Management Intewface (EMI) Wegistews */
#define I82579_EMI_ADDW		0x10
#define I82579_EMI_DATA		0x11
#define I82579_WPI_UPDATE_TIMEW	0x4805	/* in 40ns units + 40 ns base vawue */
#define I82579_MSE_THWESHOWD	0x084F	/* 82579 Mean Squawe Ewwow Thweshowd */
#define I82577_MSE_THWESHOWD	0x0887	/* 82577 Mean Squawe Ewwow Thweshowd */
#define I82579_MSE_WINK_DOWN	0x2411	/* MSE count befowe dwopping wink */
#define I82579_WX_CONFIG		0x3412	/* Weceive configuwation */
#define I82579_WPI_PWW_SHUT		0x4412	/* WPI PWW Shut Enabwe */
#define I82579_EEE_PCS_STATUS		0x182E	/* IEEE MMD Wegistew 3.1 >> 8 */
#define I82579_EEE_CAPABIWITY		0x0410	/* IEEE MMD Wegistew 3.20 */
#define I82579_EEE_ADVEWTISEMENT	0x040E	/* IEEE MMD Wegistew 7.60 */
#define I82579_EEE_WP_ABIWITY		0x040F	/* IEEE MMD Wegistew 7.61 */
#define I82579_EEE_100_SUPPOWTED	(1 << 1)	/* 100BaseTx EEE */
#define I82579_EEE_1000_SUPPOWTED	(1 << 2)	/* 1000BaseTx EEE */
#define I82579_WPI_100_PWW_SHUT	(1 << 2)	/* 100M WPI PWW Shut Enabwed */
#define I217_EEE_PCS_STATUS	0x9401	/* IEEE MMD Wegistew 3.1 */
#define I217_EEE_CAPABIWITY	0x8000	/* IEEE MMD Wegistew 3.20 */
#define I217_EEE_ADVEWTISEMENT	0x8001	/* IEEE MMD Wegistew 7.60 */
#define I217_EEE_WP_ABIWITY	0x8002	/* IEEE MMD Wegistew 7.61 */
#define I217_WX_CONFIG		0xB20C	/* Weceive configuwation */

#define E1000_EEE_WX_WPI_WCVD	0x0400	/* Tx WP idwe weceived */
#define E1000_EEE_TX_WPI_WCVD	0x0800	/* Wx WP idwe weceived */

/* Intew Wapid Stawt Technowogy Suppowt */
#define I217_PWOXY_CTWW		BM_PHY_WEG(BM_WUC_PAGE, 70)
#define I217_PWOXY_CTWW_AUTO_DISABWE	0x0080
#define I217_SxCTWW			PHY_WEG(BM_POWT_CTWW_PAGE, 28)
#define I217_SxCTWW_ENABWE_WPI_WESET	0x1000
#define I217_CGFWEG			PHY_WEG(772, 29)
#define I217_CGFWEG_ENABWE_MTA_WESET	0x0002
#define I217_MEMPWW			PHY_WEG(772, 26)
#define I217_MEMPWW_DISABWE_SMB_WEWEASE	0x0010

/* Weceive Addwess Initiaw CWC Cawcuwation */
#define E1000_PCH_WAICC(_n)	(0x05F50 + ((_n) * 4))

/* Watency Towewance Wepowting */
#define E1000_WTWV			0x000F8
#define E1000_WTWV_VAWUE_MASK		0x000003FF
#define E1000_WTWV_SCAWE_MAX		5
#define E1000_WTWV_SCAWE_FACTOW		5
#define E1000_WTWV_SCAWE_SHIFT		10
#define E1000_WTWV_SCAWE_MASK		0x00001C00
#define E1000_WTWV_WEQ_SHIFT		15
#define E1000_WTWV_NOSNOOP_SHIFT	16
#define E1000_WTWV_SEND			(1 << 30)

/* Pwopwietawy Watency Towewance Wepowting PCI Capabiwity */
#define E1000_PCI_WTW_CAP_WPT		0xA8

/* Don't gate wake DMA cwock */
#define E1000_FFWT_DBG_DONT_GATE_WAKE_DMA_CWK	0x1000

void e1000e_wwite_pwotect_nvm_ich8wan(stwuct e1000_hw *hw);
void e1000e_set_kmwn_wock_woss_wowkawound_ich8wan(stwuct e1000_hw *hw,
						  boow state);
void e1000e_igp3_phy_powewdown_wowkawound_ich8wan(stwuct e1000_hw *hw);
void e1000e_gig_downshift_wowkawound_ich8wan(stwuct e1000_hw *hw);
void e1000_suspend_wowkawounds_ich8wan(stwuct e1000_hw *hw);
void e1000_wesume_wowkawounds_pchwan(stwuct e1000_hw *hw);
s32 e1000_configuwe_k1_ich8wan(stwuct e1000_hw *hw, boow k1_enabwe);
void e1000_copy_wx_addws_to_phy_ich8wan(stwuct e1000_hw *hw);
s32 e1000_wv_jumbo_wowkawound_ich8wan(stwuct e1000_hw *hw, boow enabwe);
s32 e1000_wead_emi_weg_wocked(stwuct e1000_hw *hw, u16 addw, u16 *data);
s32 e1000_wwite_emi_weg_wocked(stwuct e1000_hw *hw, u16 addw, u16 data);
s32 e1000_set_eee_pchwan(stwuct e1000_hw *hw);
s32 e1000_enabwe_uwp_wpt_wp(stwuct e1000_hw *hw, boow to_sx);
#endif /* _E1000E_ICH8WAN_H_ */
