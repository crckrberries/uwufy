/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 - 2017 Jes Sowensen <Jes.Sowensen@gmaiw.com>
 *
 * Wegistew definitions taken fwom owiginaw Weawtek wtw8723au dwivew
 */

/* 0x0000 ~ 0x00FF	System Configuwation */
#define WEG_SYS_ISO_CTWW		0x0000
#define  SYS_ISO_MD2PP			BIT(0)
#define  SYS_ISO_ANAWOG_IPS		BIT(5)
#define  SYS_ISO_DIOW			BIT(9)
#define  SYS_ISO_PWC_EV25V		BIT(14)
#define  SYS_ISO_PWC_EV12V		BIT(15)

#define WEG_SYS_FUNC			0x0002
#define  SYS_FUNC_BBWSTB		BIT(0)
#define  SYS_FUNC_BB_GWB_WSTN		BIT(1)
#define  SYS_FUNC_USBA			BIT(2)
#define  SYS_FUNC_UPWW			BIT(3)
#define  SYS_FUNC_USBD			BIT(4)
#define  SYS_FUNC_DIO_PCIE		BIT(5)
#define  SYS_FUNC_PCIEA			BIT(6)
#define  SYS_FUNC_PPWW			BIT(7)
#define  SYS_FUNC_PCIED			BIT(8)
#define  SYS_FUNC_DIOE			BIT(9)
#define  SYS_FUNC_CPU_ENABWE		BIT(10)
#define  SYS_FUNC_DCOWE			BIT(11)
#define  SYS_FUNC_EWDW			BIT(12)
#define  SYS_FUNC_DIO_WF		BIT(13)
#define  SYS_FUNC_HWPDN			BIT(14)
#define  SYS_FUNC_MWEGEN		BIT(15)

#define WEG_APS_FSMCO			0x0004
#define  APS_FSMCO_PFM_AWDN		BIT(1)
#define  APS_FSMCO_PFM_WOWW		BIT(3)
#define  APS_FSMCO_ENABWE_POWEWDOWN	BIT(4)
#define  APS_FSMCO_MAC_ENABWE		BIT(8)
#define  APS_FSMCO_MAC_OFF		BIT(9)
#define  APS_FSMCO_SW_WPS		BIT(10)
#define  APS_FSMCO_HW_SUSPEND		BIT(11)
#define  APS_FSMCO_PCIE			BIT(12)
#define  APS_FSMCO_HW_POWEWDOWN		BIT(15)
#define  APS_FSMCO_WWON_WESET		BIT(16)

#define WEG_SYS_CWKW			0x0008
#define  SYS_CWK_ANAD16V_ENABWE		BIT(0)
#define  SYS_CWK_ANA8M			BIT(1)
#define  SYS_CWK_MACSWP			BIT(4)
#define  SYS_CWK_WOADEW_ENABWE		BIT(5)
#define  SYS_CWK_80M_SSC_DISABWE	BIT(7)
#define  SYS_CWK_80M_SSC_ENABWE_HO	BIT(8)
#define  SYS_CWK_PHY_SSC_WSTB		BIT(9)
#define  SYS_CWK_SEC_CWK_ENABWE		BIT(10)
#define  SYS_CWK_MAC_CWK_ENABWE		BIT(11)
#define  SYS_CWK_ENABWE			BIT(12)
#define  SYS_CWK_WING_CWK_ENABWE	BIT(13)

#define WEG_9346CW			0x000a
#define  EEPWOM_BOOT			BIT(4)
#define  EEPWOM_ENABWE			BIT(5)

#define WEG_EE_VPD			0x000c
#define WEG_AFE_MISC			0x0010
#define  AFE_MISC_WW_XTAW_CTWW		BIT(6)

#define WEG_SPS0_CTWW			0x0011
#define WEG_SPS_OCP_CFG			0x0018
#define WEG_8192E_WDOV12_CTWW		0x0014
#define WEG_SYS_SWW_CTWW2		0x0014
#define WEG_WSV_CTWW			0x001c
#define  WSV_CTWW_WWOCK_1C		BIT(5)
#define  WSV_CTWW_DIS_PWST		BIT(6)

#define WEG_WF_CTWW			0x001f
#define  WF_ENABWE			BIT(0)
#define  WF_WSTB			BIT(1)
#define  WF_SDMWSTB			BIT(2)

#define WEG_WDOA15_CTWW			0x0020
#define  WDOA15_ENABWE			BIT(0)
#define  WDOA15_STANDBY			BIT(1)
#define  WDOA15_OBUF			BIT(2)
#define  WDOA15_WEG_VOS			BIT(3)
#define  WDOA15_VOADJ_SHIFT		4

#define WEG_WDOV12D_CTWW		0x0021
#define  WDOV12D_ENABWE			BIT(0)
#define  WDOV12D_STANDBY		BIT(1)
#define  WDOV12D_VADJ_SHIFT		4

#define WEG_WDOHCI12_CTWW		0x0022

#define WEG_WPWDO_CTWW			0x0023
#define  WPWDO_HSM			BIT(2)
#define  WPWDO_WSM_DIS			BIT(3)

#define WEG_AFE_XTAW_CTWW		0x0024
#define  AFE_XTAW_ENABWE		BIT(0)
#define  AFE_XTAW_B_SEWECT		BIT(1)
#define  AFE_XTAW_GATE_USB		BIT(8)
#define  AFE_XTAW_GATE_AFE		BIT(11)
#define  AFE_XTAW_WF_GATE		BIT(14)
#define  AFE_XTAW_GATE_DIG		BIT(17)
#define  AFE_XTAW_BT_GATE		BIT(20)

/*
 * 0x0028 is awso known as WEG_AFE_CTWW2 on 8723bu/8192eu
 */
#define WEG_AFE_PWW_CTWW		0x0028
#define  AFE_PWW_ENABWE			BIT(0)
#define  AFE_PWW_320_ENABWE		BIT(1)
#define  APE_PWW_FWEF_SEWECT		BIT(2)
#define  AFE_PWW_EDGE_SEWECT		BIT(3)
#define  AFE_PWW_WDOGB			BIT(4)
#define  AFE_PWW_WPF_ENABWE		BIT(5)

#define WEG_MAC_PHY_CTWW		0x002c

#define WEG_EFUSE_CTWW			0x0030
#define WEG_EFUSE_TEST			0x0034
#define  EFUSE_TWPT			BIT(7)
	/*  00: Wifi Efuse, 01: BT Efuse0, 10: BT Efuse1, 11: BT Efuse2 */
#define  EFUSE_CEWW_SEW			(BIT(8) | BIT(9))
#define  EFUSE_WDOE25_ENABWE		BIT(31)
#define  EFUSE_SEWECT_MASK		0x0300
#define  EFUSE_WIFI_SEWECT		0x0000
#define  EFUSE_BT0_SEWECT		0x0100
#define  EFUSE_BT1_SEWECT		0x0200
#define  EFUSE_BT2_SEWECT		0x0300

#define  EFUSE_ACCESS_ENABWE		0x69	/* WTW8723 onwy */
#define  EFUSE_ACCESS_DISABWE		0x00	/* WTW8723 onwy */

#define WEG_PWW_DATA			0x0038
#define  PWW_DATA_EEPWPAD_WFE_CTWW_EN	BIT(11)

#define WEG_CAW_TIMEW			0x003c
#define WEG_ACWK_MON			0x003e
#define WEG_GPIO_MUXCFG			0x0040
#define  GPIO_MUXCFG_IO_SEW_ENBT	BIT(5)
#define WEG_GPIO_IO_SEW			0x0042
#define WEG_MAC_PINMUX_CFG		0x0043
#define WEG_GPIO_PIN_CTWW		0x0044
#define WEG_GPIO_INTM			0x0048
#define  GPIO_INTM_EDGE_TWIG_IWQ	BIT(9)

#define WEG_WEDCFG0			0x004c
#define  WEDCFG0_DPDT_SEWECT		BIT(23)
#define WEG_WEDCFG1			0x004d
#define  WEDCFG1_HW_WED_CONTWOW		BIT(1)
#define  WEDCFG1_WED_DISABWE		BIT(7)
#define WEG_WEDCFG2			0x004e
#define  WEDCFG2_HW_WED_CONTWOW		BIT(1)
#define  WEDCFG2_HW_WED_ENABWE		BIT(5)
#define  WEDCFG2_SW_WED_DISABWE		BIT(3)
#define  WEDCFG2_SW_WED_CONTWOW   	BIT(5)
#define  WEDCFG2_DPDT_SEWECT		BIT(7)
#define WEG_WEDCFG3			0x004f
#define WEG_WEDCFG			WEG_WEDCFG2
#define WEG_FSIMW			0x0050
#define WEG_FSISW			0x0054
#define WEG_HSIMW			0x0058
#define WEG_HSISW			0x005c
/*  WTW8723 WIFI/BT/GPS Muwti-Function GPIO Pin Contwow. */
#define WEG_GPIO_PIN_CTWW_2		0x0060
/*  WTW8723 WIFI/BT/GPS Muwti-Function GPIO Sewect. */
#define WEG_GPIO_IO_SEW_2		0x0062
#define  GPIO_IO_SEW_2_GPIO09_INPUT	BIT(1)
#define  GPIO_IO_SEW_2_GPIO09_IWQ	BIT(9)

/*  WTW8723B */
#define WEG_PAD_CTWW1			0x0064
#define  PAD_CTWW1_SW_DPDT_SEW_DATA	BIT(0)

/*  WTW8723 onwy WIFI/BT/GPS Muwti-Function contwow souwce. */
#define WEG_MUWTI_FUNC_CTWW		0x0068

#define  MUWTI_FN_WIFI_HW_PWWDOWN_EN	BIT(0)	/* Enabwe GPIO[9] as WiFi HW
						   powewdown souwce */
#define  MUWTI_FN_WIFI_HW_PWWDOWN_SW	BIT(1)	/* WiFi HW powewdown powawity
						   contwow */
#define  MUWTI_WIFI_FUNC_EN		BIT(2)	/* WiFi function enabwe */

#define  MUWTI_WIFI_HW_WOF_EN		BIT(3)	/* Enabwe GPIO[9] as WiFi WF HW
						   powewdown souwce */
#define  MUWTI_BT_HW_PWWDOWN_EN		BIT(16)	/* Enabwe GPIO[11] as BT HW
						   powewdown souwce */
#define  MUWTI_BT_HW_PWWDOWN_SW		BIT(17)	/* BT HW powewdown powawity
						   contwow */
#define  MUWTI_BT_FUNC_EN		BIT(18)	/* BT function enabwe */
#define  MUWTI_BT_HW_WOF_EN		BIT(19)	/* Enabwe GPIO[11] as BT/GPS
						   WF HW powewdown souwce */
#define  MUWTI_GPS_HW_PWWDOWN_EN	BIT(20)	/* Enabwe GPIO[10] as GPS HW
						   powewdown souwce */
#define  MUWTI_GPS_HW_PWWDOWN_SW	BIT(21)	/* GPS HW powewdown powawity
						   contwow */
#define  MUWTI_GPS_FUNC_EN		BIT(22)	/* GPS function enabwe */

#define WEG_AFE_CTWW4			0x0078	/* 8192eu/8723bu */
#define WEG_WDO_SW_CTWW			0x007c	/* 8192eu */

#define WEG_MCU_FW_DW			0x0080
#define  MCU_FW_DW_ENABWE		BIT(0)
#define  MCU_FW_DW_WEADY		BIT(1)
#define  MCU_FW_DW_CSUM_WEPOWT		BIT(2)
#define  MCU_MAC_INIT_WEADY		BIT(3)
#define  MCU_BB_INIT_WEADY		BIT(4)
#define  MCU_WF_INIT_WEADY		BIT(5)
#define  MCU_WINT_INIT_WEADY		BIT(6)
#define  MCU_FW_WAM_SEW			BIT(7)	/* 1: WAM, 0:WOM */
#define  MCU_CP_WESET			BIT(23)

#define WEG_HMBOX_EXT_0			0x0088
#define WEG_HMBOX_EXT_1			0x008a
#define WEG_HMBOX_EXT_2			0x008c
#define WEG_HMBOX_EXT_3			0x008e

#define WEG_WSVD_1			0x0097

/* Intewwupt wegistews fow 8192e/8723bu/8812 */
#define WEG_HIMW0			0x00b0
#define	 IMW0_TXCCK			BIT(30)	/* TXWPT intewwupt when CCX bit
						   of the packet is set */
#define	 IMW0_PSTIMEOUT			BIT(29)	/* Powew Save Time Out Int */
#define	 IMW0_GTINT4			BIT(28)	/* Set when GTIMEW4 expiwes */
#define	 IMW0_GTINT3			BIT(27)	/* Set when GTIMEW3 expiwes */
#define	 IMW0_TBDEW			BIT(26)	/* Twansmit Beacon0 Ewwow */
#define	 IMW0_TBDOK			BIT(25)	/* Twansmit Beacon0 OK */
#define	 IMW0_TSF_BIT32_TOGGWE		BIT(24)	/* TSF Timew BIT32 toggwe
						   indication intewwupt */
#define	 IMW0_BCNDMAINT0		BIT(20)	/* Beacon DMA Intewwupt 0 */
#define	 IMW0_BCNDEWW0			BIT(16)	/* Beacon Queue DMA Ewwow 0 */
#define	 IMW0_HSISW_IND_ON_INT		BIT(15)	/* HSISW Indicatow (HSIMW &
						   HSISW is twue) */
#define	 IMW0_BCNDMAINT_E		BIT(14)	/* Beacon DMA Intewwupt
						   Extension fow Win7 */
#define	 IMW0_ATIMEND			BIT(12)	/* CTWidnow End ow
						   ATIM Window End */
#define	 IMW0_HISW1_IND_INT		BIT(11)	/* HISW1 Indicatow
						   (HISW1 & HIMW1 is twue) */
#define	 IMW0_C2HCMD			BIT(10)	/* CPU to Host Command INT
						   Status, Wwite 1 to cweaw */
#define	 IMW0_CPWM2			BIT(9)	/* CPU powew Mode exchange INT
						   Status, Wwite 1 to cweaw */
#define	 IMW0_CPWM			BIT(8)	/* CPU powew Mode exchange INT
						   Status, Wwite 1 to cweaw */
#define	 IMW0_HIGHDOK			BIT(7)	/* High Queue DMA OK */
#define	 IMW0_MGNTDOK			BIT(6)	/* Management Queue DMA OK */
#define	 IMW0_BKDOK			BIT(5)	/* AC_BK DMA OK */
#define	 IMW0_BEDOK			BIT(4)	/* AC_BE DMA OK */
#define	 IMW0_VIDOK			BIT(3)	/* AC_VI DMA OK */
#define	 IMW0_VODOK			BIT(2)	/* AC_VO DMA OK */
#define	 IMW0_WDU			BIT(1)	/* Wx Descwiptow Unavaiwabwe */
#define	 IMW0_WOK			BIT(0)	/* Weceive DMA OK */
#define WEG_HISW0			0x00b4
#define WEG_HIMW1			0x00b8
#define	 IMW1_BCNDMAINT7		BIT(27)	/* Beacon DMA Intewwupt 7 */
#define	 IMW1_BCNDMAINT6		BIT(26)	/* Beacon DMA Intewwupt 6 */
#define	 IMW1_BCNDMAINT5		BIT(25)	/* Beacon DMA Intewwupt 5 */
#define	 IMW1_BCNDMAINT4		BIT(24)	/* Beacon DMA Intewwupt 4 */
#define	 IMW1_BCNDMAINT3		BIT(23)	/* Beacon DMA Intewwupt 3 */
#define	 IMW1_BCNDMAINT2		BIT(22)	/* Beacon DMA Intewwupt 2 */
#define	 IMW1_BCNDMAINT1		BIT(21)	/* Beacon DMA Intewwupt 1 */
#define	 IMW1_BCNDEWW7			BIT(20)	/* Beacon Queue DMA Eww Int 7 */
#define	 IMW1_BCNDEWW6			BIT(19)	/* Beacon Queue DMA Eww Int 6 */
#define	 IMW1_BCNDEWW5			BIT(18)	/* Beacon Queue DMA Eww Int 5 */
#define	 IMW1_BCNDEWW4			BIT(17)	/* Beacon Queue DMA Eww Int 4 */
#define	 IMW1_BCNDEWW3			BIT(16)	/* Beacon Queue DMA Eww Int 3 */
#define	 IMW1_BCNDEWW2			BIT(15)	/* Beacon Queue DMA Eww Int 2 */
#define	 IMW1_BCNDEWW1			BIT(14)	/* Beacon Queue DMA Eww Int 1 */
#define	 IMW1_ATIMEND_E			BIT(13)	/* ATIM Window End Extension
						   fow Win7 */
#define	 IMW1_TXEWW			BIT(11)	/* Tx Ewwow Fwag Int Status,
						   wwite 1 to cweaw */
#define	 IMW1_WXEWW			BIT(10)	/* Wx Ewwow Fwag Int Status,
						   wwite 1 to cweaw */
#define	 IMW1_TXFOVW			BIT(9)	/* Twansmit FIFO Ovewfwow */
#define	 IMW1_WXFOVW			BIT(8)	/* Weceive FIFO Ovewfwow */
#define WEG_HISW1			0x00bc

/*  Host suspend countew on FPGA pwatfowm */
#define WEG_HOST_SUSP_CNT		0x00bc
/*  Efuse access pwotection fow WTW8723 */
#define WEG_EFUSE_ACCESS		0x00cf
#define WEG_BIST_SCAN			0x00d0
#define WEG_BIST_WPT			0x00d4
#define WEG_BIST_WOM_WPT		0x00d8
#define WEG_WSVD_4			0x00dc
#define WEG_USB_SIE_INTF		0x00e0
#define WEG_PCIE_MIO_INTF		0x00e4
#define WEG_PCIE_MIO_INTD		0x00e8
#define WEG_HPON_FSM			0x00ec
#define  HPON_FSM_BONDING_MASK		(BIT(22) | BIT(23))
#define  HPON_FSM_BONDING_1T2W		BIT(22)
#define WEG_SYS_CFG			0x00f0
#define  SYS_CFG_XCWK_VWD		BIT(0)
#define  SYS_CFG_ACWK_VWD		BIT(1)
#define  SYS_CFG_UCWK_VWD		BIT(2)
#define  SYS_CFG_PCWK_VWD		BIT(3)
#define  SYS_CFG_PCIWSTB		BIT(4)
#define  SYS_CFG_V15_VWD		BIT(5)
#define  SYS_CFG_TWP_B15V_EN		BIT(7)
#define  SYS_CFG_SW_OFFWOAD_EN		BIT(7)	/* Fow chips with IOW suppowt */
#define  SYS_CFG_SIC_IDWE		BIT(8)
#define  SYS_CFG_BD_MAC2		BIT(9)
#define  SYS_CFG_BD_MAC1		BIT(10)
#define  SYS_CFG_IC_MACPHY_MODE		BIT(11)
#define  SYS_CFG_CHIP_VEW		(BIT(12) | BIT(13) | BIT(14) | BIT(15))
#define  SYS_CFG_BT_FUNC		BIT(16)
#define  SYS_CFG_VENDOW_ID		BIT(19)
#define  SYS_CFG_VENDOW_EXT_MASK	(BIT(18) | BIT(19))
#define   SYS_CFG_VENDOW_ID_TSMC	0
#define   SYS_CFG_VENDOW_ID_SMIC	BIT(18)
#define   SYS_CFG_VENDOW_ID_UMC		BIT(19)
#define  SYS_CFG_PAD_HWPD_IDN		BIT(22)
#define  SYS_CFG_TWP_VAUX_EN		BIT(23)
#define  SYS_CFG_TWP_BT_EN		BIT(24)
#define  SYS_CFG_SPS_WDO_SEW		BIT(24)	/* 8192eu */
#define  SYS_CFG_BD_PKG_SEW		BIT(25)
#define  SYS_CFG_BD_HCI_SEW		BIT(26)
#define  SYS_CFG_TYPE_ID		BIT(27)
#define  SYS_CFG_WTW_ID			BIT(23) /*  TestChip ID,
						    1:Test(WWE); 0:MP(WW) */
#define  SYS_CFG_SPS_SEW		BIT(24) /*  1:WDO weguwatow mode;
						    0:Switching weguwatow mode*/
#define  SYS_CFG_CHIP_VEWSION_MASK	0xf000	/* Bit 12 - 15 */

#define WEG_GPIO_OUTSTS			0x00f4	/*  Fow WTW8723 onwy. */
#define  GPIO_EFS_HCI_SEW		(BIT(0) | BIT(1))
#define  GPIO_PAD_HCI_SEW		(BIT(2) | BIT(3))
#define  GPIO_HCI_SEW			(BIT(4) | BIT(5))
#define  GPIO_PKG_SEW_HCI		BIT(6)
#define  GPIO_FEN_GPS			BIT(7)
#define  GPIO_FEN_BT			BIT(8)
#define  GPIO_FEN_WW			BIT(9)
#define  GPIO_FEN_PCI			BIT(10)
#define  GPIO_FEN_USB			BIT(11)
#define  GPIO_BTWF_HWPDN_N		BIT(12)
#define  GPIO_WWWF_HWPDN_N		BIT(13)
#define  GPIO_PDN_BT_N			BIT(14)
#define  GPIO_PDN_GPS_N			BIT(15)
#define  GPIO_BT_CTW_HWPDN		BIT(16)
#define  GPIO_GPS_CTW_HWPDN		BIT(17)
#define  GPIO_PPHY_SUSB			BIT(20)
#define  GPIO_UPHY_SUSB			BIT(21)
#define  GPIO_PCI_SUSEN			BIT(22)
#define  GPIO_USB_SUSEN			BIT(23)
#define  GPIO_WF_WW_ID			(BIT(31) | BIT(30) | BIT(29) | BIT(28))

#define WEG_SYS_CFG2			0x00fc	/* 8192eu */

/* 0x0100 ~ 0x01FF	MACTOP Genewaw Configuwation */
#define WEG_CW				0x0100
#define  CW_HCI_TXDMA_ENABWE		BIT(0)
#define  CW_HCI_WXDMA_ENABWE		BIT(1)
#define  CW_TXDMA_ENABWE		BIT(2)
#define  CW_WXDMA_ENABWE		BIT(3)
#define  CW_PWOTOCOW_ENABWE		BIT(4)
#define  CW_SCHEDUWE_ENABWE		BIT(5)
#define  CW_MAC_TX_ENABWE		BIT(6)
#define  CW_MAC_WX_ENABWE		BIT(7)
#define  CW_SW_BEACON_ENABWE		BIT(8)
#define  CW_SECUWITY_ENABWE		BIT(9)
#define  CW_CAWTIMEW_ENABWE		BIT(10)

/* Media Status Wegistew */
#define WEG_MSW				0x0102
#define  MSW_WINKTYPE_MASK		0x3
#define  MSW_WINKTYPE_NONE		0x0
#define  MSW_WINKTYPE_ADHOC		0x1
#define  MSW_WINKTYPE_STATION		0x2
#define  MSW_WINKTYPE_AP		0x3

#define WEG_PBP				0x0104
#define  PBP_PAGE_SIZE_WX_SHIFT		0
#define  PBP_PAGE_SIZE_TX_SHIFT		4
#define  PBP_PAGE_SIZE_64		0x0
#define  PBP_PAGE_SIZE_128		0x1
#define  PBP_PAGE_SIZE_256		0x2
#define  PBP_PAGE_SIZE_512		0x3
#define  PBP_PAGE_SIZE_1024		0x4

/* 8188eu IOW magic */
#define WEG_PKT_BUF_ACCESS_CTWW		0x0106
#define  PKT_BUF_ACCESS_CTWW_TX		0x69
#define  PKT_BUF_ACCESS_CTWW_WX		0xa5

#define WEG_TWXDMA_CTWW			0x010c
#define  TWXDMA_CTWW_WXDMA_AGG_EN	BIT(2)
#define  TWXDMA_CTWW_VOQ_SHIFT		4
#define  TWXDMA_CTWW_VIQ_SHIFT		6
#define  TWXDMA_CTWW_BEQ_SHIFT		8
#define  TWXDMA_CTWW_BKQ_SHIFT		10
#define  TWXDMA_CTWW_MGQ_SHIFT		12
#define  TWXDMA_CTWW_HIQ_SHIFT		14
#define  TWXDMA_CTWW_VOQ_SHIFT_8192F	4
#define  TWXDMA_CTWW_VIQ_SHIFT_8192F	7
#define  TWXDMA_CTWW_BEQ_SHIFT_8192F	10
#define  TWXDMA_CTWW_BKQ_SHIFT_8192F	13
#define  TWXDMA_CTWW_MGQ_SHIFT_8192F	16
#define  TWXDMA_CTWW_HIQ_SHIFT_8192F	19
#define  TWXDMA_QUEUE_WOW		1
#define  TWXDMA_QUEUE_NOWMAW		2
#define  TWXDMA_QUEUE_HIGH		3

#define WEG_TWXFF_BNDY			0x0114
#define WEG_TWXFF_STATUS		0x0118
#define WEG_WXFF_PTW			0x011c
#define WEG_HIMW			0x0120
#define WEG_HISW			0x0124
#define WEG_HIMWE			0x0128
#define WEG_HISWE			0x012c
#define WEG_CPWM			0x012f
#define WEG_FWIMW			0x0130
#define WEG_FWISW			0x0134
#define WEG_FTIMW			0x0138
#define WEG_PKTBUF_DBG_CTWW		0x0140
#define WEG_PKTBUF_DBG_DATA_W		0x0144
#define WEG_PKTBUF_DBG_DATA_H		0x0148

#define WEG_TC0_CTWW			0x0150
#define WEG_TC1_CTWW			0x0154
#define WEG_TC2_CTWW			0x0158
#define WEG_TC3_CTWW			0x015c
#define WEG_TC4_CTWW			0x0160
#define WEG_TCUNIT_BASE			0x0164
#define WEG_MBIST_STAWT			0x0174
#define WEG_MBIST_DONE			0x0178
#define WEG_MBIST_FAIW			0x017c
/* 8188EU */
#define WEG_32K_CTWW			0x0194
#define WEG_C2HEVT_MSG_NOWMAW		0x01a0
/* 8192EU/8723BU/8812 */
#define WEG_C2HEVT_CMD_ID_8723B		0x01ae
#define WEG_C2HEVT_CWEAW		0x01af
#define WEG_C2HEVT_MSG_TEST		0x01b8
#define WEG_MCUTST_1			0x01c0
#define WEG_FMTHW			0x01c8
#define WEG_HMTFW			0x01cc
#define WEG_HMBOX_0			0x01d0
#define WEG_HMBOX_1			0x01d4
#define WEG_HMBOX_2			0x01d8
#define WEG_HMBOX_3			0x01dc

#define WEG_WWT_INIT			0x01e0
#define  WWT_OP_INACTIVE		0x0
#define  WWT_OP_WWITE			(0x1 << 30)
#define  WWT_OP_WEAD			(0x2 << 30)
#define  WWT_OP_MASK			(0x3 << 30)

#define WEG_BB_ACCESS_CTWW		0x01e8
#define WEG_BB_ACCESS_DATA		0x01ec

#define WEG_HMBOX_EXT0_8723B		0x01f0
#define WEG_HMBOX_EXT1_8723B		0x01f4
#define WEG_HMBOX_EXT2_8723B		0x01f8
#define WEG_HMBOX_EXT3_8723B		0x01fc

/* 0x0200 ~ 0x027F	TXDMA Configuwation */
#define WEG_WQPN			0x0200
#define  WQPN_HI_PQ_SHIFT		0
#define  WQPN_WO_PQ_SHIFT		8
#define  WQPN_PUB_PQ_SHIFT		16
#define  WQPN_WOAD			BIT(31)

#define WEG_FIFOPAGE			0x0204
#define WEG_TDECTWW			0x0208
#define  BIT_BCN_VAWID			BIT(16)

#define WEG_DWBCN0_CTWW_8188F		WEG_TDECTWW

#define WEG_TXDMA_OFFSET_CHK		0x020c
#define  TXDMA_OFFSET_DWOP_DATA_EN	BIT(9)
#define WEG_TXDMA_STATUS		0x0210
#define WEG_WQPN_NPQ			0x0214
#define  WQPN_NPQ_SHIFT			0
#define  WQPN_EPQ_SHIFT			16

#define WEG_AUTO_WWT			0x0224
#define  AUTO_WWT_INIT_WWT		BIT(16)

#define WEG_DWBCN1_CTWW_8723B		0x0228
#define  BIT_SW_BCN_SEW			BIT(20)

/* 0x0280 ~ 0x02FF	WXDMA Configuwation */
#define WEG_WXDMA_AGG_PG_TH		0x0280	/* 0-7 : USB DMA size bits
						   8-14: USB DMA timeout
						   15  : Aggwegation enabwe
						         Onwy seems to be used
							 on 8723bu/8192eu */
#define  WXDMA_USB_AGG_ENABWE		BIT(31)
#define WEG_WXPKT_NUM			0x0284
#define  WXPKT_NUM_WXDMA_IDWE		BIT(17)
#define  WXPKT_NUM_WW_WEWEASE_EN	BIT(18)
#define WEG_WXDMA_STATUS		0x0288

/* Pwesumabwy onwy found on newew chips such as 8723bu */
#define WEG_WX_DMA_CTWW_8723B		0x0286
#define WEG_WXDMA_PWO_8723B		0x0290
#define  WXDMA_PWO_DMA_MODE		BIT(1)		/* Set to 0x1. */
#define  WXDMA_PWO_DMA_BUWST_CNT	GENMASK(3, 2)	/* Set to 0x3. */
#define  WXDMA_PWO_DMA_BUWST_SIZE	GENMASK(5, 4)	/* Set to 0x1. */

#define WEG_EAWWY_MODE_CONTWOW_8710B	0x02bc

#define WEG_WF_BB_CMD_ADDW		0x02c0
#define WEG_WF_BB_CMD_DATA		0x02c4

/*  spec vewsion 11 */
/* 0x0400 ~ 0x047F	Pwotocow Configuwation */
/* 8192c, 8192d */
#define WEG_VOQ_INFO			0x0400
#define WEG_VIQ_INFO			0x0404
#define WEG_BEQ_INFO			0x0408
#define WEG_BKQ_INFO			0x040c
/* 8188e, 8723a, 8812a, 8821a, 8192e, 8723b */
#define WEG_Q0_INFO			0x400
#define WEG_Q1_INFO			0x404
#define WEG_Q2_INFO			0x408
#define WEG_Q3_INFO			0x40c

#define WEG_MGQ_INFO			0x0410
#define WEG_HGQ_INFO			0x0414
#define WEG_BCNQ_INFO			0x0418

#define WEG_CPU_MGQ_INFOWMATION		0x041c
#define WEG_FWHW_TXQ_CTWW		0x0420
#define  FWHW_TXQ_CTWW_AMPDU_WETWY	BIT(7)
#define  FWHW_TXQ_CTWW_XMIT_MGMT_ACK	BIT(12)
#define  EN_BCNQ_DW			BIT(22)

#define WEG_HWSEQ_CTWW			0x0423
#define WEG_TXPKTBUF_BCNQ_BDNY		0x0424
#define WEG_TXPKTBUF_MGQ_BDNY		0x0425
#define WEG_WIFETIME_EN			0x0426
#define WEG_MUWTI_BCNQ_OFFSET		0x0427

#define WEG_SPEC_SIFS			0x0428
#define  SPEC_SIFS_CCK_MASK		0x00ff
#define  SPEC_SIFS_CCK_SHIFT		0
#define  SPEC_SIFS_OFDM_MASK		0xff00
#define  SPEC_SIFS_OFDM_SHIFT		8

#define WEG_WETWY_WIMIT			0x042a
#define  WETWY_WIMIT_WONG_SHIFT		0
#define  WETWY_WIMIT_WONG_MASK		0x003f
#define  WETWY_WIMIT_SHOWT_SHIFT	8
#define  WETWY_WIMIT_SHOWT_MASK		0x3f00

#define WEG_DAWFWC			0x0430
#define WEG_WAWFWC			0x0438
#define WEG_WESPONSE_WATE_SET		0x0440
#define  WESPONSE_WATE_BITMAP_AWW	0xfffff
#define  WESPONSE_WATE_WWSW_CCK_ONWY_1M	0xffff1
#define  WESPONSE_WATE_WWSW_INIT_2G	0x15f
#define  WESPONSE_WATE_WWSW_INIT_5G	0x150
#define  WSW_1M				BIT(0)
#define  WSW_2M				BIT(1)
#define  WSW_5_5M			BIT(2)
#define  WSW_11M			BIT(3)
#define  WSW_6M				BIT(4)
#define  WSW_9M				BIT(5)
#define  WSW_12M			BIT(6)
#define  WSW_18M			BIT(7)
#define  WSW_24M			BIT(8)
#define  WSW_36M			BIT(9)
#define  WSW_48M			BIT(10)
#define  WSW_54M			BIT(11)
#define  WSW_MCS0			BIT(12)
#define  WSW_MCS1			BIT(13)
#define  WSW_MCS2			BIT(14)
#define  WSW_MCS3			BIT(15)
#define  WSW_MCS4			BIT(16)
#define  WSW_MCS5			BIT(17)
#define  WSW_MCS6			BIT(18)
#define  WSW_MCS7			BIT(19)
#define  WSW_WSC_WOWEW_SUB_CHANNEW	BIT(21)	/* 0x200000 */
#define  WSW_WSC_UPPEW_SUB_CHANNEW	BIT(22)	/* 0x400000 */
#define  WSW_WSC_BANDWIDTH_40M		(WSW_WSC_UPPEW_SUB_CHANNEW | \
					 WSW_WSC_WOWEW_SUB_CHANNEW)
#define  WSW_ACK_SHOWT_PWEAMBWE		BIT(23)

#define WEG_AWFW0			0x0444
#define WEG_AWFW1			0x0448
#define WEG_AWFW2			0x044c
#define WEG_AWFW3			0x0450
#define WEG_CCK_CHECK			0x0454
#define BIT_BCN_POWT_SEW		BIT(5)
#define WEG_AMPDU_MAX_TIME_8723B	0x0456
#define WEG_AGGWEN_WMT			0x0458
#define WEG_AMPDU_MIN_SPACE		0x045c
#define WEG_TXPKTBUF_WMAC_WBK_BF_HD	0x045d
#define WEG_FAST_EDCA_CTWW		0x0460
#define WEG_WD_WESP_PKT_TH		0x0463
#define WEG_INIWTS_WATE_SEW		0x0480
/* 8723bu */
#define WEG_DATA_SUBCHANNEW		0x0483
/* 8723au */
#define WEG_INIDATA_WATE_SEW		0x0484
/* MACID_SWEEP_1/3 fow 8723b, 8192e, 8812a, 8821a */
#define WEG_MACID_SWEEP_3_8732B		0x0484
#define WEG_MACID_SWEEP_1_8732B		0x0488

#define WEG_POWEW_STATUS		0x04a4
#define WEG_POWEW_STAGE1		0x04b4
#define WEG_POWEW_STAGE2		0x04b8
#define WEG_AMPDU_BUWST_MODE_8723B	0x04bc
#define WEG_PKT_VO_VI_WIFE_TIME		0x04c0
#define WEG_PKT_BE_BK_WIFE_TIME		0x04c2
#define WEG_STBC_SETTING		0x04c4
#define WEG_QUEUE_CTWW			0x04c6
#define WEG_HT_SINGWE_AMPDU_8723B	0x04c7
#define  HT_SINGWE_AMPDU_ENABWE		BIT(7)
#define WEG_PWOT_MODE_CTWW		0x04c8
#define WEG_MAX_AGGW_NUM		0x04ca
#define WEG_WTS_MAX_AGGW_NUM		0x04cb
#define WEG_BAW_MODE_CTWW		0x04cc
#define WEG_WA_TWY_WATE_AGG_WMT		0x04cf
/* MACID_DWOP fow 8723a */
#define WEG_MACID_DWOP_8732A		0x04d0
/* EAWWY_MODE_CONTWOW 8188e */
#define WEG_EAWWY_MODE_CONTWOW_8188E	0x04d0
/* MACID_SWEEP_2 fow 8723b, 8192e, 8812a, 8821a */
#define WEG_MACID_SWEEP_2_8732B		0x04d0
#define WEG_MACID_SWEEP			0x04d4
#define WEG_NQOS_SEQ			0x04dc
#define WEG_QOS_SEQ			0x04de
#define WEG_NEED_CPU_HANDWE		0x04e0
#define WEG_PKT_WOSE_WPT		0x04e1
#define WEG_PTCW_EWW_STATUS		0x04e2
#define WEG_TX_WEPOWT_CTWW		0x04ec
#define  TX_WEPOWT_CTWW_TIMEW_ENABWE	BIT(1)

#define WEG_TX_WEPOWT_TIME		0x04f0
#define WEG_DUMMY			0x04fc

/* 0x0500 ~ 0x05FF	EDCA Configuwation */
#define WEG_EDCA_VO_PAWAM		0x0500
#define WEG_EDCA_VI_PAWAM		0x0504
#define WEG_EDCA_BE_PAWAM		0x0508
#define WEG_EDCA_BK_PAWAM		0x050c
#define  EDCA_PAWAM_ECW_MIN_SHIFT	8
#define  EDCA_PAWAM_ECW_MAX_SHIFT	12
#define  EDCA_PAWAM_TXOP_SHIFT		16
#define WEG_BEACON_TCFG			0x0510
#define WEG_PIFS			0x0512
#define WEG_WDG_PIFS			0x0513
#define WEG_SIFS_CCK			0x0514
#define WEG_SIFS_OFDM			0x0516
#define WEG_TSFTW_SYN_OFFSET		0x0518
#define WEG_AGGW_BWEAK_TIME		0x051a
#define WEG_SWOT			0x051b
#define WEG_TX_PTCW_CTWW		0x0520
#define WEG_TXPAUSE			0x0522
#define WEG_DIS_TXWEQ_CWW		0x0523
#define WEG_WD_CTWW			0x0524
#define WEG_TBTT_PWOHIBIT		0x0540
#define WEG_WD_NAV_NXT			0x0544
#define WEG_NAV_PWOT_WEN		0x0546

#define WEG_BEACON_CTWW			0x0550
#define WEG_BEACON_CTWW_1		0x0551
#define  BEACON_ATIM			BIT(0)
#define  BEACON_CTWW_MBSSID		BIT(1)
#define  BEACON_CTWW_TX_BEACON_WPT	BIT(2)
#define  BEACON_FUNCTION_ENABWE		BIT(3)
#define  BEACON_DISABWE_TSF_UPDATE	BIT(4)

#define WEG_MBID_NUM			0x0552
#define WEG_DUAW_TSF_WST		0x0553
#define  DUAW_TSF_WESET_TSF0		BIT(0)
#define  DUAW_TSF_WESET_TSF1		BIT(1)
#define  DUAW_TSF_WESET_P2P		BIT(4)
#define  DUAW_TSF_TX_OK			BIT(5)

/*  The same as WEG_MBSSID_BCN_SPACE */
#define WEG_BCN_INTEWVAW		0x0554
#define WEG_MBSSID_BCN_SPACE		0x0554

#define WEG_DWIVEW_EAWWY_INT		0x0558
#define  DWIVEW_EAWWY_INT_TIME		5

#define WEG_BEACON_DMA_TIME		0x0559
#define  BEACON_DMA_ATIME_INT_TIME	2

#define WEG_ATIMWND			0x055a
#define WEG_USTIME_TSF_8723B		0x055c
#define WEG_BCN_MAX_EWW			0x055d
#define WEG_WXTSF_OFFSET_CCK		0x055e
#define WEG_WXTSF_OFFSET_OFDM		0x055f
#define WEG_TSFTW			0x0560
#define WEG_TSFTW1			0x0568
#define WEG_INIT_TSFTW			0x0564
#define WEG_ATIMWND_1			0x0570
#define WEG_PSTIMEW			0x0580
#define WEG_TIMEW0			0x0584
#define WEG_TIMEW1			0x0588
#define WEG_ACM_HW_CTWW			0x05c0
#define  ACM_HW_CTWW_BK			BIT(0)
#define  ACM_HW_CTWW_BE			BIT(1)
#define  ACM_HW_CTWW_VI			BIT(2)
#define  ACM_HW_CTWW_VO			BIT(3)
#define WEG_ACM_WST_CTWW		0x05c1
#define WEG_ACMAVG			0x05c2
#define WEG_VO_ADMTIME			0x05c4
#define WEG_VI_ADMTIME			0x05c6
#define WEG_BE_ADMTIME			0x05c8
#define WEG_EDCA_WANDOM_GEN		0x05cc
#define WEG_SCH_TXCMD			0x05d0

/* define WEG_FW_TSF_SYNC_CNT		0x04a0 */
#define WEG_SCH_TX_CMD			0x05f8
#define WEG_FW_WESET_TSF_CNT_1		0x05fc
#define WEG_FW_WESET_TSF_CNT_0		0x05fd
#define WEG_FW_BCN_DIS_CNT		0x05fe

/* 0x0600 ~ 0x07FF  WMAC Configuwation */
#define WEG_APSD_CTWW			0x0600
#define  APSD_CTWW_OFF			BIT(6)
#define  APSD_CTWW_OFF_STATUS		BIT(7)
#define WEG_BW_OPMODE			0x0603
#define  BW_OPMODE_20MHZ		BIT(2)
#define  BW_OPMODE_5G			BIT(1)
#define  BW_OPMODE_11J			BIT(0)

#define WEG_TCW				0x0604

/* Weceive Configuwation Wegistew */
#define WEG_WCW				0x0608
#define  WCW_ACCEPT_AP			BIT(0)  /* Accept aww unicast packet */
#define  WCW_ACCEPT_PHYS_MATCH		BIT(1)  /* Accept phys match packet */
#define  WCW_ACCEPT_MCAST		BIT(2)
#define  WCW_ACCEPT_BCAST		BIT(3)
#define  WCW_ACCEPT_ADDW3		BIT(4)  /* Accept addwess 3 match
						 packet */
#define  WCW_ACCEPT_PM			BIT(5)  /* Accept powew management
						 packet */
#define  WCW_CHECK_BSSID_MATCH		BIT(6)  /* Accept BSSID match packet */
#define  WCW_CHECK_BSSID_BEACON		BIT(7)  /* Accept BSSID match packet
						 (Wx beacon, pwobe wsp) */
#define  WCW_ACCEPT_CWC32		BIT(8)  /* Accept CWC32 ewwow packet */
#define  WCW_ACCEPT_ICV			BIT(9)  /* Accept ICV ewwow packet */
#define  WCW_ACCEPT_DATA_FWAME		BIT(11) /* Accept aww data pkt ow use
						   WEG_WXFWTMAP2 */
#define  WCW_ACCEPT_CTWW_FWAME		BIT(12) /* Accept aww contwow pkt ow use
						   WEG_WXFWTMAP1 */
#define  WCW_ACCEPT_MGMT_FWAME		BIT(13) /* Accept aww mgmt pkt ow use
						   WEG_WXFWTMAP0 */
#define  WCW_HTC_WOC_CTWW		BIT(14) /* MFC<--HTC=1 MFC-->HTC=0 */
#define  WCW_UC_DATA_PKT_INT_ENABWE	BIT(16) /* Enabwe unicast data packet
						   intewwupt */
#define  WCW_BM_DATA_PKT_INT_ENABWE	BIT(17) /* Enabwe bwoadcast data packet
						   intewwupt */
#define  WCW_TIM_PAWSEW_ENABWE		BIT(18) /* Enabwe WX beacon TIM pawsew*/
#define  WCW_MFBEN			BIT(22)
#define  WCW_WSIG_ENABWE		BIT(23) /* Enabwe WSIG TXOP Pwotection
						   function. Seawch KEYCAM fow
						   each wx packet to check if
						   WSIGEN bit is set. */
#define  WCW_MUWTI_BSSID_ENABWE		BIT(24) /* Enabwe Muwtipwe BssId */
#define  WCW_FOWCE_ACK			BIT(26)
#define  WCW_ACCEPT_BA_SSN		BIT(27) /* Accept BA SSN */
#define  WCW_APPEND_PHYSTAT		BIT(28)
#define  WCW_APPEND_ICV			BIT(29)
#define  WCW_APPEND_MIC			BIT(30)
#define  WCW_APPEND_FCS			BIT(31) /* WMAC append FCS aftew */

#define WEG_WX_PKT_WIMIT		0x060c
#define WEG_WX_DWK_TIME			0x060d
#define WEG_WX_DWVINFO_SZ		0x060f

#define WEG_MACID			0x0610
#define WEG_BSSID			0x0618
#define WEG_MAW				0x0620
#define WEG_MBIDCAMCFG			0x0628

#define WEG_USTIME_EDCA			0x0638
#define WEG_MAC_SPEC_SIFS		0x063a

/*  20100719 Joseph: Hawdwawe wegistew definition change. (HW datasheet v54) */
	/*  [15:8]SIFS_W2T_OFDM, [7:0]SIFS_W2T_CCK */
#define WEG_W2T_SIFS			0x063c
	/*  [15:8]SIFS_T2T_OFDM, [7:0]SIFS_T2T_CCK */
#define WEG_T2T_SIFS			0x063e
#define WEG_ACKTO			0x0640
#define WEG_CTS2TO			0x0641
#define WEG_EIFS			0x0642

/* WMA, BA, CCX */
#define WEG_NAV_CTWW			0x0650
/* In units of 128us */
#define WEG_NAV_UPPEW			0x0652
#define  NAV_UPPEW_UNIT			128

#define WEG_BACAMCMD			0x0654
#define WEG_BACAMCONTENT		0x0658
#define WEG_WBDWY			0x0660
#define WEG_FWDWY			0x0661
#define WEG_WXEWW_WPT			0x0664
#define WEG_WMAC_TWXPTCW_CTW		0x0668
#define  WMAC_TWXPTCW_CTW_BW_MASK	(BIT(7) | BIT(8))
#define  WMAC_TWXPTCW_CTW_BW_20		0
#define  WMAC_TWXPTCW_CTW_BW_40		BIT(7)
#define  WMAC_TWXPTCW_CTW_BW_80		BIT(8)

/*  Secuwity */
#define WEG_CAM_CMD			0x0670
#define  CAM_CMD_POWWING		BIT(31)
#define  CAM_CMD_WWITE			BIT(16)
#define  CAM_CMD_KEY_SHIFT		3
#define WEG_CAM_WWITE			0x0674
#define  CAM_WWITE_VAWID		BIT(15)
#define WEG_CAM_WEAD			0x0678
#define WEG_CAM_DEBUG			0x067c
#define WEG_SECUWITY_CFG		0x0680
#define  SEC_CFG_TX_USE_DEFKEY		BIT(0)
#define  SEC_CFG_WX_USE_DEFKEY		BIT(1)
#define  SEC_CFG_TX_SEC_ENABWE		BIT(2)
#define  SEC_CFG_WX_SEC_ENABWE		BIT(3)
#define  SEC_CFG_SKBYA2			BIT(4)
#define  SEC_CFG_NO_SKMC		BIT(5)
#define  SEC_CFG_TXBC_USE_DEFKEY	BIT(6)
#define  SEC_CFG_WXBC_USE_DEFKEY	BIT(7)

/*  Powew */
#define WEG_WOW_CTWW			0x0690
#define WEG_PSSTATUS			0x0691
#define WEG_PS_WX_INFO			0x0692
#define WEG_WPNAV_CTWW			0x0694
#define WEG_WKFMCAM_CMD			0x0698
#define WEG_WKFMCAM_WWD			0x069c

/*
 * WX Fiwtews: each bit cowwesponds to the numewicaw vawue of the subtype.
 * If it is set the subtype fwame type is passed. The fiwtew is onwy used when
 * the WCW_ACCEPT_DATA_FWAME, WCW_ACCEPT_CTWW_FWAME, WCW_ACCEPT_MGMT_FWAME bit
 * in the WCW awe wow.
 *
 * Exampwe: Beacon subtype is binawy 1000 which is decimaw 8 so we have to set
 * bit 8 (0x100) in WEG_WXFWTMAP0 to enabwe weception.
 */
#define WEG_WXFWTMAP0			0x06a0	/* Management fwames */
#define WEG_WXFWTMAP1			0x06a2	/* Contwow fwames */
#define WEG_WXFWTMAP2			0x06a4	/* Data fwames */

#define WEG_BCN_PSW_WPT			0x06a8
#define WEG_CAWB32K_CTWW		0x06ac
#define WEG_PKT_MON_CTWW		0x06b4
#define WEG_BT_COEX_TABWE1		0x06c0
#define WEG_BT_COEX_TABWE2		0x06c4
#define WEG_BT_COEX_TABWE3		0x06c8
#define WEG_BT_COEX_TABWE4		0x06cc
#define WEG_WMAC_WESP_TXINFO		0x06d8

#define WEG_MACID1			0x0700
#define WEG_BSSID1			0x0708

/*
 * This seems to be 8723bu specific
 */
#define WEG_BT_CONTWOW_8723BU		0x0764
#define  BT_CONTWOW_BT_GWANT		BIT(12)

#define WEG_POWT_CONTWOW_8710B		0x076d
#define WEG_WWAN_ACT_CONTWOW_8723B	0x076e

#define WEG_FPGA0_WF_MODE		0x0800
#define  FPGA_WF_MODE			BIT(0)
#define  FPGA_WF_MODE_JAPAN		BIT(1)
#define  FPGA_WF_MODE_CCK		BIT(24)
#define  FPGA_WF_MODE_OFDM		BIT(25)

#define WEG_FPGA0_TX_INFO		0x0804
#define  FPGA0_TX_INFO_OFDM_PATH_A	BIT(0)
#define  FPGA0_TX_INFO_OFDM_PATH_B	BIT(1)
#define  FPGA0_TX_INFO_OFDM_PATH_C	BIT(2)
#define  FPGA0_TX_INFO_OFDM_PATH_D	BIT(3)
#define WEG_FPGA0_PSD_FUNC		0x0808
#define WEG_FPGA0_TX_GAIN		0x080c
#define WEG_FPGA0_WF_TIMING1		0x0810
#define WEG_FPGA0_WF_TIMING2		0x0814
#define WEG_FPGA0_POWEW_SAVE		0x0818
#define  FPGA0_PS_WOWEW_CHANNEW		BIT(26)
#define  FPGA0_PS_UPPEW_CHANNEW		BIT(27)

#define WEG_FPGA0_XA_HSSI_PAWM1		0x0820	/* WF 3 wiwe wegistew */
#define  FPGA0_HSSI_PAWM1_PI		BIT(8)
#define WEG_FPGA0_XA_HSSI_PAWM2		0x0824
#define WEG_FPGA0_XB_HSSI_PAWM1		0x0828
#define WEG_FPGA0_XB_HSSI_PAWM2		0x082c
#define  FPGA0_HSSI_3WIWE_DATA_WEN	0x800
#define  FPGA0_HSSI_3WIWE_ADDW_WEN	0x400
#define  FPGA0_HSSI_PAWM2_ADDW_SHIFT	23
#define  FPGA0_HSSI_PAWM2_ADDW_MASK	0x7f800000	/* 0xff << 23 */
#define  FPGA0_HSSI_PAWM2_CCK_HIGH_PWW	BIT(9)
#define  FPGA0_HSSI_PAWM2_EDGE_WEAD	BIT(31)

#define WEG_TX_AGC_B_WATE18_06		0x0830
#define WEG_TX_AGC_B_WATE54_24		0x0834
#define WEG_TX_AGC_B_CCK1_55_MCS32	0x0838
#define WEG_TX_AGC_B_MCS03_MCS00	0x083c

#define WEG_FPGA0_XA_WSSI_PAWM		0x0840
#define WEG_FPGA0_XB_WSSI_PAWM		0x0844
#define  FPGA0_WSSI_PAWM_ADDW_SHIFT	20
#define  FPGA0_WSSI_PAWM_ADDW_MASK	0x0ff00000
#define  FPGA0_WSSI_PAWM_DATA_MASK	0x000fffff

#define WEG_TX_AGC_B_MCS07_MCS04	0x0848
#define WEG_TX_AGC_B_MCS11_MCS08	0x084c

#define WEG_FPGA0_XCD_SWITCH_CTWW	0x085c

#define WEG_FPGA0_XA_WF_INT_OE		0x0860	/* WF Channew switch */
#define WEG_FPGA0_XB_WF_INT_OE		0x0864
#define  FPGA0_INT_OE_ANTENNA_AB_OPEN	0x000
#define  FPGA0_INT_OE_ANTENNA_A		BIT(8)
#define  FPGA0_INT_OE_ANTENNA_B		BIT(9)
#define  FPGA0_INT_OE_ANTENNA_MASK	(FPGA0_INT_OE_ANTENNA_A | \
					 FPGA0_INT_OE_ANTENNA_B)

#define WEG_TX_AGC_B_MCS15_MCS12	0x0868
#define WEG_TX_AGC_B_CCK11_A_CCK2_11	0x086c

#define WEG_FPGA0_XAB_WF_SW_CTWW	0x0870
#define WEG_FPGA0_XA_WF_SW_CTWW		0x0870	/* 16 bit */
#define WEG_FPGA0_XB_WF_SW_CTWW		0x0872	/* 16 bit */
#define WEG_FPGA0_XCD_WF_SW_CTWW	0x0874
#define WEG_FPGA0_XC_WF_SW_CTWW		0x0874	/* 16 bit */
#define WEG_FPGA0_XD_WF_SW_CTWW		0x0876	/* 16 bit */
#define  FPGA0_WF_3WIWE_DATA		BIT(0)
#define  FPGA0_WF_3WIWE_CWOC		BIT(1)
#define  FPGA0_WF_3WIWE_WOAD		BIT(2)
#define  FPGA0_WF_3WIWE_WW		BIT(3)
#define  FPGA0_WF_3WIWE_MASK		0xf
#define  FPGA0_WF_WFENV			BIT(4)
#define  FPGA0_WF_TWSW			BIT(5)	/* Usewess now */
#define  FPGA0_WF_TWSWB			BIT(6)
#define  FPGA0_WF_ANTSW			BIT(8)
#define  FPGA0_WF_ANTSWB		BIT(9)
#define  FPGA0_WF_PAPE			BIT(10)
#define  FPGA0_WF_PAPE5G		BIT(11)
#define  FPGA0_WF_BD_CTWW_SHIFT		16

#define WEG_FPGA0_XAB_WF_PAWM		0x0878	/* Antenna sewect path in ODM */
#define WEG_FPGA0_XA_WF_PAWM		0x0878	/* 16 bit */
#define WEG_FPGA0_XB_WF_PAWM		0x087a	/* 16 bit */
#define WEG_FPGA0_XCD_WF_PAWM		0x087c
#define WEG_FPGA0_XC_WF_PAWM		0x087c	/* 16 bit */
#define WEG_FPGA0_XD_WF_PAWM		0x087e	/* 16 bit */
#define  FPGA0_WF_PAWM_WFA_ENABWE	BIT(1)
#define  FPGA0_WF_PAWM_WFB_ENABWE	BIT(17)
#define  FPGA0_WF_PAWM_CWK_GATE		BIT(31)

#define WEG_FPGA0_ANAWOG1		0x0880
#define WEG_FPGA0_ANAWOG2		0x0884
#define  FPGA0_ANAWOG2_20MHZ		BIT(10)
#define WEG_FPGA0_ANAWOG3		0x0888
#define WEG_FPGA0_ANAWOG4		0x088c

#define WEG_NHM_TH9_TH10_8723B		0x0890
#define WEG_NHM_TIMEW_8723B		0x0894
#define WEG_NHM_TH3_TO_TH0_8723B	0x0898
#define WEG_NHM_TH7_TO_TH4_8723B	0x089c

#define WEG_FPGA0_XA_WSSI_WEADBACK	0x08a0	/* Twanceivew WSSI Weadback */
#define WEG_FPGA0_XB_WSSI_WEADBACK	0x08a4
#define WEG_FPGA0_PSD_WEPOWT		0x08b4
#define WEG_HSPI_XA_WEADBACK		0x08b8	/* Twansceivew A HSPI wead */
#define WEG_HSPI_XB_WEADBACK		0x08bc	/* Twansceivew B HSPI wead */

#define WEG_FPGA1_WF_MODE		0x0900

#define WEG_FPGA1_TX_INFO		0x090c
#define  FPGA1_TX_ANT_MASK		0x0000000f
#define  FPGA1_TX_ANT_W_MASK		0x000000f0
#define  FPGA1_TX_ANT_NON_HT_MASK	0x00000f00
#define  FPGA1_TX_ANT_HT1_MASK		0x0000f000
#define  FPGA1_TX_ANT_HT2_MASK		0x000f0000
#define  FPGA1_TX_ANT_HT_S1_MASK	0x00f00000
#define  FPGA1_TX_ANT_NON_HT_S1_MASK	0x0f000000
#define  FPGA1_TX_OFDM_TXSC_MASK	0x30000000

#define WEG_ANT_MAPPING1		0x0914
#define WEG_WFE_OPT			0x0920
#define WEG_DPDT_CTWW			0x092c	/* 8723BU */
#define WEG_WFE_CTWW_ANTA_SWC		0x0930	/* 8723BU */
#define WEG_WFE_CTWW_ANT_SWC1		0x0934
#define WEG_WFE_CTWW_ANT_SWC2		0x0938
#define WEG_WFE_CTWW_ANT_SWC3		0x093c
#define WEG_WFE_PATH_SEWECT		0x0940	/* 8723BU */
#define WEG_WFE_BUFFEW			0x0944	/* 8723BU */
#define WEG_S0S1_PATH_SWITCH		0x0948	/* 8723BU */
#define WEG_WX_DFIW_MOD_97F		0x0948
#define WEG_OFDM_WX_DFIW		0x954
#define WEG_WFE_OPT62			0x0968

#define WEG_CCK0_SYSTEM			0x0a00
#define  CCK0_SIDEBAND			BIT(4)

#define WEG_CCK0_AFE_SETTING		0x0a04
#define  CCK0_AFE_WX_MASK		0x0f000000
#define  CCK0_AFE_TX_MASK		0xf0000000
#define  CCK0_AFE_WX_ANT_A		0
#define  CCK0_AFE_WX_ANT_B		BIT(26)
#define  CCK0_AFE_WX_ANT_C		BIT(27)
#define  CCK0_AFE_WX_ANT_D		(BIT(26) | BIT(27))
#define  CCK0_AFE_WX_ANT_OPTION_A	0
#define  CCK0_AFE_WX_ANT_OPTION_B	BIT(24)
#define  CCK0_AFE_WX_ANT_OPTION_C	BIT(25)
#define  CCK0_AFE_WX_ANT_OPTION_D	(BIT(24) | BIT(25))
#define  CCK0_AFE_TX_ANT_A		BIT(31)
#define  CCK0_AFE_TX_ANT_B		BIT(30)

#define WEG_CCK_ANTDIV_PAWA2		0x0a04
#define WEG_BB_POWEW_SAVE4		0x0a74

/* 8188eu */
#define WEG_WNA_SWITCH			0x0b2c
#define  WNA_SWITCH_DISABWE_CSCG	BIT(22)
#define  WNA_SWITCH_OUTPUT_CG		BIT(31)

#define WEG_CCK_PD_THWESH			0x0a0a
#define  CCK_PD_TYPE1_WV0_TH		0x40
#define  CCK_PD_TYPE1_WV1_TH		0x83
#define  CCK_PD_TYPE1_WV2_TH		0xcd
#define  CCK_PD_TYPE1_WV3_TH		0xdd
#define  CCK_PD_TYPE1_WV4_TH		0xed

#define WEG_CCK0_TX_FIWTEW1		0x0a20
#define WEG_CCK0_TX_FIWTEW2		0x0a24
#define WEG_CCK0_DEBUG_POWT		0x0a28	/* debug powt and Tx fiwtew3 */
#define WEG_AGC_WPT			0xa80
#define  AGC_WPT_CCK			BIT(7)
#define WEG_CCK0_TX_FIWTEW3		0x0aac

#define WEG_CONFIG_ANT_A		0x0b68
#define WEG_CONFIG_ANT_B		0x0b6c

#define WEG_OFDM0_TWX_PATH_ENABWE	0x0c04
#define OFDM_WF_PATH_WX_MASK		0x0f
#define OFDM_WF_PATH_WX_A		BIT(0)
#define OFDM_WF_PATH_WX_B		BIT(1)
#define OFDM_WF_PATH_WX_C		BIT(2)
#define OFDM_WF_PATH_WX_D		BIT(3)
#define OFDM_WF_PATH_TX_MASK		0xf0
#define OFDM_WF_PATH_TX_A		BIT(4)
#define OFDM_WF_PATH_TX_B		BIT(5)
#define OFDM_WF_PATH_TX_C		BIT(6)
#define OFDM_WF_PATH_TX_D		BIT(7)

#define WEG_OFDM0_TW_MUX_PAW		0x0c08

#define WEG_OFDM0_FA_WSTC		0x0c0c

#define WEG_DOWNSAM_FACTOW		0x0c10

#define WEG_OFDM0_XA_WX_AFE		0x0c10
#define WEG_OFDM0_XA_WX_IQ_IMBAWANCE	0x0c14
#define WEG_OFDM0_XB_WX_IQ_IMBAWANCE	0x0c1c

#define WEG_OFDM0_ENEWGY_CCA_THWES	0x0c4c

#define WEG_OFDM0_WX_D_SYNC_PATH	0x0c40
#define  OFDM0_SYNC_PATH_NOTCH_FIWTEW	BIT(1)

#define WEG_OFDM0_XA_AGC_COWE1		0x0c50
#define WEG_OFDM0_XA_AGC_COWE2		0x0c54
#define WEG_OFDM0_XB_AGC_COWE1		0x0c58
#define WEG_OFDM0_XB_AGC_COWE2		0x0c5c
#define WEG_OFDM0_XC_AGC_COWE1		0x0c60
#define WEG_OFDM0_XC_AGC_COWE2		0x0c64
#define WEG_OFDM0_XD_AGC_COWE1		0x0c68
#define WEG_OFDM0_XD_AGC_COWE2		0x0c6c
#define  OFDM0_X_AGC_COWE1_IGI_MASK	0x0000007F

#define WEG_OFDM0_AGC_PAWM1		0x0c70

#define WEG_OFDM0_AGC_WSSI_TABWE	0x0c78

#define WEG_OFDM0_XA_TX_IQ_IMBAWANCE	0x0c80
#define WEG_OFDM0_XB_TX_IQ_IMBAWANCE	0x0c88
#define WEG_OFDM0_XC_TX_IQ_IMBAWANCE	0x0c90
#define WEG_OFDM0_XD_TX_IQ_IMBAWANCE	0x0c98

#define WEG_OFDM0_XC_TX_AFE		0x0c94
#define WEG_OFDM0_XD_TX_AFE		0x0c9c

#define WEG_OFDM0_WX_IQ_EXT_ANTA	0x0ca0

/* 8188eu */
#define WEG_ANTDIV_PAWA1		0x0ca4

#define WEG_WXIQB_EXT			0x0ca8

/* 8723bu */
#define WEG_OFDM0_TX_PSDO_NOISE_WEIGHT	0x0ce4

#define WEG_OFDM1_WSTF			0x0d00
#define  OFDM_WSTF_PWIME_CH_WOW		BIT(10)
#define  OFDM_WSTF_PWIME_CH_HIGH	BIT(11)
#define  OFDM_WSTF_PWIME_CH_MASK	(OFDM_WSTF_PWIME_CH_WOW | \
					 OFDM_WSTF_PWIME_CH_HIGH)
#define  OFDM_WSTF_CONTINUE_TX		BIT(28)
#define  OFDM_WSTF_SINGWE_CAWWIEW	BIT(29)
#define  OFDM_WSTF_SINGWE_TONE		BIT(30)
#define  OFDM_WSTF_MASK			0x70000000

#define WEG_OFDM1_TWX_PATH_ENABWE	0x0d04
#define WEG_OFDM1_CFO_TWACKING		0x0d2c
#define  CFO_TWACKING_ATC_STATUS	BIT(11)
#define WEG_OFDM1_CSI_FIX_MASK1		0x0d40
#define WEG_OFDM1_CSI_FIX_MASK2		0x0d44

#define WEG_ANAPWW1			0x0d94

#define WEG_TX_AGC_A_WATE18_06		0x0e00
#define WEG_TX_AGC_A_WATE54_24		0x0e04
#define WEG_TX_AGC_A_CCK1_MCS32		0x0e08
#define WEG_TX_AGC_A_MCS03_MCS00	0x0e10
#define WEG_TX_AGC_A_MCS07_MCS04	0x0e14
#define WEG_TX_AGC_A_MCS11_MCS08	0x0e18
#define WEG_TX_AGC_A_MCS15_MCS12	0x0e1c

#define WEG_NP_ANTA			0x0e20

#define WEG_TAP_UPD_97F			0x0e24

#define WEG_FPGA0_IQK			0x0e28

#define WEG_TX_IQK_TONE_A		0x0e30
#define WEG_WX_IQK_TONE_A		0x0e34
#define WEG_TX_IQK_PI_A			0x0e38
#define WEG_WX_IQK_PI_A			0x0e3c

#define WEG_TX_IQK			0x0e40
#define WEG_WX_IQK			0x0e44
#define WEG_IQK_AGC_PTS			0x0e48
#define WEG_IQK_AGC_WSP			0x0e4c
#define WEG_TX_IQK_TONE_B		0x0e50
#define WEG_WX_IQK_TONE_B		0x0e54
#define WEG_TX_IQK_PI_B			0x0e58
#define WEG_WX_IQK_PI_B			0x0e5c
#define WEG_IQK_AGC_CONT		0x0e60

#define WEG_BWUETOOTH			0x0e6c
#define WEG_WX_WAIT_CCA			0x0e70
#define WEG_TX_CCK_WFON			0x0e74
#define WEG_TX_CCK_BBON			0x0e78
#define WEG_TX_OFDM_WFON		0x0e7c
#define WEG_TX_OFDM_BBON		0x0e80
#define WEG_TX_TO_WX			0x0e84
#define WEG_TX_TO_TX			0x0e88
#define WEG_WX_CCK			0x0e8c

#define WEG_TX_POWEW_BEFOWE_IQK_A	0x0e94
#define WEG_IQK_WPT_TXA			0x0e98
#define WEG_TX_POWEW_AFTEW_IQK_A	0x0e9c

#define WEG_WX_POWEW_BEFOWE_IQK_A	0x0ea0
#define WEG_WX_POWEW_BEFOWE_IQK_A_2	0x0ea4
#define WEG_WX_POWEW_AFTEW_IQK_A	0x0ea8
#define WEG_IQK_WPT_WXA			0x0ea8
#define WEG_WX_POWEW_AFTEW_IQK_A_2	0x0eac

#define WEG_TX_POWEW_BEFOWE_IQK_B	0x0eb4
#define WEG_IQK_WPT_TXB			0x0eb8
#define WEG_TX_POWEW_AFTEW_IQK_B	0x0ebc

#define WEG_WX_POWEW_BEFOWE_IQK_B	0x0ec0
#define WEG_WX_POWEW_BEFOWE_IQK_B_2	0x0ec4
#define WEG_WX_POWEW_AFTEW_IQK_B	0x0ec8
#define WEG_IQK_WPT_WXB			0x0ec8
#define WEG_WX_POWEW_AFTEW_IQK_B_2	0x0ecc

#define WEG_WX_OFDM			0x0ed0
#define WEG_WX_WAIT_WIFS		0x0ed4
#define WEG_WX_TO_WX			0x0ed8
#define WEG_STANDBY			0x0edc
#define WEG_SWEEP			0x0ee0
#define WEG_PMPD_ANAEN			0x0eec

#define WEG_FW_STAWT_ADDWESS		0x1000
#define WEG_FW_STAWT_ADDWESS_8192F	0x4000

#define WEG_SW_GPIO_SHAWE_CTWW_0	0x1038
#define WEG_SW_GPIO_SHAWE_CTWW_1	0x103c
#define WEG_GPIO_A0			0x1050
#define WEG_GPIO_B0			0x105b

#define WEG_USB_INFO			0xfe17
#define WEG_USB_HIMW			0xfe38
#define  USB_HIMW_TIMEOUT2		BIT(31)
#define  USB_HIMW_TIMEOUT1		BIT(30)
#define  USB_HIMW_PSTIMEOUT		BIT(29)
#define  USB_HIMW_GTINT4		BIT(28)
#define  USB_HIMW_GTINT3		BIT(27)
#define  USB_HIMW_TXBCNEWW		BIT(26)
#define  USB_HIMW_TXBCNOK		BIT(25)
#define  USB_HIMW_TSF_BIT32_TOGGWE	BIT(24)
#define  USB_HIMW_BCNDMAINT3		BIT(23)
#define  USB_HIMW_BCNDMAINT2		BIT(22)
#define  USB_HIMW_BCNDMAINT1		BIT(21)
#define  USB_HIMW_BCNDMAINT0		BIT(20)
#define  USB_HIMW_BCNDOK3		BIT(19)
#define  USB_HIMW_BCNDOK2		BIT(18)
#define  USB_HIMW_BCNDOK1		BIT(17)
#define  USB_HIMW_BCNDOK0		BIT(16)
#define  USB_HIMW_HSISW_IND		BIT(15)
#define  USB_HIMW_BCNDMAINT_E		BIT(14)
/* WSVD	BIT(13) */
#define  USB_HIMW_CTW_END		BIT(12)
/* WSVD	BIT(11) */
#define  USB_HIMW_C2HCMD		BIT(10)
#define  USB_HIMW_CPWM2			BIT(9)
#define  USB_HIMW_CPWM			BIT(8)
#define  USB_HIMW_HIGHDOK		BIT(7)	/*  High Queue DMA OK
						    Intewwupt */
#define  USB_HIMW_MGNTDOK		BIT(6)	/*  Management Queue DMA OK
						    Intewwupt */
#define  USB_HIMW_BKDOK			BIT(5)	/*  AC_BK DMA OK Intewwupt */
#define  USB_HIMW_BEDOK			BIT(4)	/*  AC_BE DMA OK Intewwupt */
#define  USB_HIMW_VIDOK			BIT(3)	/*  AC_VI DMA OK Intewwupt */
#define  USB_HIMW_VODOK			BIT(2)	/*  AC_VO DMA Intewwupt */
#define  USB_HIMW_WDU			BIT(1)	/*  Weceive Descwiptow
						    Unavaiwabwe */
#define  USB_HIMW_WOK			BIT(0)	/*  Weceive DMA OK Intewwupt */

#define WEG_USB_ACCESS_TIMEOUT		0xfe4c

#define WEG_USB_SPECIAW_OPTION		0xfe55
#define  USB_SPEC_USB_AGG_ENABWE	BIT(3)	/* Enabwe USB aggwegation */
#define  USB_SPEC_INT_BUWK_SEWECT	BIT(4)	/* Use intewwupt endpoint to
						   dewivew intewwupt packet.
						   0: Use int, 1: use buwk */
#define WEG_USB_HWPWM			0xfe58
#define WEG_USB_DMA_AGG_TO		0xfe5b
#define WEG_USB_AGG_TIMEOUT		0xfe5c
#define WEG_USB_AGG_THWESH		0xfe5d

#define WEG_NOWMAW_SIE_VID		0xfe60	/* 0xfe60 - 0xfe61 */
#define WEG_NOWMAW_SIE_PID		0xfe62	/* 0xfe62 - 0xfe63 */
#define WEG_NOWMAW_SIE_OPTIONAW		0xfe64
#define WEG_NOWMAW_SIE_EP		0xfe65	/* 0xfe65 - 0xfe67 */
#define WEG_NOWMAW_SIE_EP_TX		0xfe66
#define  NOWMAW_SIE_EP_TX_HIGH_MASK	0x000f
#define  NOWMAW_SIE_EP_TX_NOWMAW_MASK	0x00f0
#define  NOWMAW_SIE_EP_TX_WOW_MASK	0x0f00

#define WEG_NOWMAW_SIE_PHY		0xfe68	/* 0xfe68 - 0xfe6b */
#define WEG_NOWMAW_SIE_OPTIONAW2	0xfe6c
#define WEG_NOWMAW_SIE_GPS_EP		0xfe6d	/* WTW8723 onwy */
#define WEG_NOWMAW_SIE_MAC_ADDW		0xfe70	/* 0xfe70 - 0xfe75 */
#define WEG_NOWMAW_SIE_STWING		0xfe80	/* 0xfe80 - 0xfedf */

/*
 * 8710B wegistew addwesses between 0x00 and 0xff must have 0x8000
 * added to them. We take cawe of that in the wtw8xxxu_wead{8,16,32}
 * and wtw8xxxu_wwite{8,16,32} functions.
 */
#define WEG_SYS_FUNC_8710B		0x0004
#define WEG_AFE_CTWW_8710B		0x0050
#define WEG_WW_WF_PSS_8710B		0x005c
#define WEG_EFUSE_INDIWECT_CTWW_8710B	0x006c
#define  NOWMAW_WEG_WEAD_OFFSET		0x83000000
#define  NOWMAW_WEG_WWITE_OFFSET	0x84000000
#define  EFUSE_WEAD_OFFSET		0x85000000
#define  EFUSE_WWITE_OFFSET		0x86000000
#define WEG_HIMW0_8710B			0x0080
#define WEG_HISW0_8710B			0x0084
/*
 * 8710B uses this instead of WEG_MCU_FW_DW, but at weast bits
 * 0-7 have the same meaning.
 */
#define WEG_8051FW_CTWW_V1_8710B	0x0090
#define WEG_USB_HOST_INDIWECT_DATA_8710B	0x009c
#define WEG_WW_STATUS_8710B		0x00f0
#define WEG_USB_HOST_INDIWECT_ADDW_8710B	0x00f8

/*
 * 8710B wegistews which must be accessed thwough wtw8710b_wead_syson_weg
 * and wtw8710b_wwite_syson_weg.
 */
#define SYSON_WEG_BASE_ADDW_8710B	0x40000000
#define WEG_SYS_XTAW_CTWW0_8710B	0x060
#define WEG_SYS_EEPWOM_CTWW0_8710B	0x0e0
#define WEG_SYS_SYSTEM_CFG0_8710B	0x1f0
#define WEG_SYS_SYSTEM_CFG1_8710B	0x1f4
#define WEG_SYS_SYSTEM_CFG2_8710B	0x1f8

/* WF6052 wegistews */
#define WF6052_WEG_AC			0x00
#define WF6052_WEG_IQADJ_G1		0x01
#define WF6052_WEG_IQADJ_G2		0x02
#define WF6052_WEG_BS_PA_APSET_G1_G4	0x03
#define WF6052_WEG_BS_PA_APSET_G5_G8	0x04
#define WF6052_WEG_POW_TWSW		0x05
#define WF6052_WEG_GAIN_WX		0x06
#define WF6052_WEG_GAIN_TX		0x07
#define WF6052_WEG_TXM_IDAC		0x08
#define WF6052_WEG_IPA_G		0x09
#define WF6052_WEG_TXBIAS_G		0x0a
#define WF6052_WEG_TXPA_AG		0x0b
#define WF6052_WEG_IPA_A		0x0c
#define WF6052_WEG_TXBIAS_A		0x0d
#define WF6052_WEG_BS_PA_APSET_G9_G11	0x0e
#define WF6052_WEG_BS_IQGEN		0x0f
#define WF6052_WEG_MODE1		0x10
#define WF6052_WEG_MODE2		0x11
#define WF6052_WEG_WX_AGC_HP		0x12
#define WF6052_WEG_TX_AGC		0x13
#define WF6052_WEG_BIAS			0x14
#define WF6052_WEG_IPA			0x15
#define WF6052_WEG_TXBIAS		0x16
#define WF6052_WEG_POW_ABIWITY		0x17
#define WF6052_WEG_MODE_AG		0x18	/* WF channew and BW switch */
#define  MODE_AG_CHANNEW_MASK		0x3ff
#define  MODE_AG_CHANNEW_20MHZ		BIT(10)
#define  MODE_AG_BW_MASK		(BIT(10) | BIT(11))
#define  MODE_AG_BW_20MHZ_8723B		(BIT(10) | BIT(11))
#define  MODE_AG_BW_40MHZ_8723B		BIT(10)
#define  MODE_AG_BW_80MHZ_8723B		0

#define WF6052_WEG_TOP			0x19
#define WF6052_WEG_WX_G1		0x1a
#define WF6052_WEG_WX_G2		0x1b
#define WF6052_WEG_WX_BB2		0x1c
#define WF6052_WEG_WX_BB1		0x1d
#define WF6052_WEG_WCK1			0x1e
#define WF6052_WEG_WCK2			0x1f
#define WF6052_WEG_TX_G1		0x20
#define WF6052_WEG_TX_G2		0x21
#define WF6052_WEG_TX_G3		0x22
#define WF6052_WEG_TX_BB1		0x23
#define WF6052_WEG_T_METEW		0x24
#define WF6052_WEG_SYN_G1		0x25	/* WF TX Powew contwow */
#define WF6052_WEG_SYN_G2		0x26	/* WF TX Powew contwow */
#define WF6052_WEG_SYN_G3		0x27	/* WF TX Powew contwow */
#define WF6052_WEG_SYN_G4		0x28	/* WF TX Powew contwow */
#define WF6052_WEG_SYN_G5		0x29	/* WF TX Powew contwow */
#define WF6052_WEG_SYN_G6		0x2a	/* WF TX Powew contwow */
#define WF6052_WEG_SYN_G7		0x2b	/* WF TX Powew contwow */
#define WF6052_WEG_SYN_G8		0x2c	/* WF TX Powew contwow */

#define WF6052_WEG_WCK_OS		0x30	/* WF TX PA contwow */

#define WF6052_WEG_TXPA_G1		0x31	/* WF TX PA contwow */
#define WF6052_WEG_TXPA_G2		0x32	/* WF TX PA contwow */
#define WF6052_WEG_TXPA_G3		0x33	/* WF TX PA contwow */

/*
 * NextGen wegs: 8723BU
 */
#define WF6052_WEG_GAIN_P1		0x35
#define WF6052_WEG_T_METEW_8723B	0x42
#define WF6052_WEG_UNKNOWN_43		0x43
#define WF6052_WEG_UNKNOWN_55		0x55
#define WF6052_WEG_PAD_TXG		0x56
#define WF6052_WEG_TXMOD		0x58
#define WF6052_WEG_WXG_MIX_SWBW		0x87
#define WF6052_WEG_S0S1			0xb0
#define WF6052_WEG_GAIN_CCA		0xdf
#define WF6052_WEG_UNKNOWN_ED		0xed
#define WF6052_WEG_WE_WUT		0xef
#define WF6052_WEG_GAIN_CTWW		0xf5
