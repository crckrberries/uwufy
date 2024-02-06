/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2010  Weawtek Cowpowation.*/

#ifndef __WTW8821AE_WEG_H__
#define __WTW8821AE_WEG_H__

#define TXPKT_BUF_SEWECT			0x69
#define WXPKT_BUF_SEWECT			0xA5
#define DISABWE_TWXPKT_BUF_ACCESS		0x0

#define WEG_SYS_ISO_CTWW			0x0000
#define WEG_SYS_FUNC_EN				0x0002
#define WEG_APS_FSMCO				0x0004
#define WEG_SYS_CWKW				0x0008
#define WEG_9346CW				0x000A
#define WEG_EE_VPD				0x000C
#define WEG_AFE_MISC				0x0010
#define WEG_SPS0_CTWW				0x0011
#define WEG_SPS_OCP_CFG				0x0018
#define WEG_WSV_CTWW				0x001C
#define WEG_WF_CTWW				0x001F
#define WEG_WDOA15_CTWW				0x0020
#define WEG_WDOV12D_CTWW			0x0021
#define WEG_WDOHCI12_CTWW			0x0022
#define WEG_WPWDO_CTWW				0x0023
#define WEG_AFE_XTAW_CTWW			0x0024
 /* 1.5v fow 8188EE test chip, 1.4v fow MP chip */
#define WEG_AFE_WDO_CTWW			0x0027
#define WEG_AFE_PWW_CTWW			0x0028
#define WEG_MAC_PHY_CTWW			0x002c
#define WEG_EFUSE_CTWW				0x0030
#define WEG_EFUSE_TEST				0x0034
#define WEG_PWW_DATA				0x0038
#define WEG_CAW_TIMEW				0x003C
#define WEG_ACWK_MON				0x003E
#define WEG_GPIO_MUXCFG				0x0040
#define WEG_GPIO_IO_SEW				0x0042
#define WEG_MAC_PINMUX_CFG			0x0043
#define WEG_GPIO_PIN_CTWW			0x0044
#define WEG_GPIO_INTM				0x0048
#define WEG_WEDCFG0				0x004C
#define WEG_WEDCFG1				0x004D
#define WEG_WEDCFG2				0x004E
#define WEG_WEDCFG3				0x004F
#define WEG_FSIMW				0x0050
#define WEG_FSISW				0x0054
#define WEG_HSIMW				0x0058
#define WEG_HSISW				0x005c
#define WEG_GPIO_PIN_CTWW_2			0x0060
#define WEG_GPIO_IO_SEW_2			0x0062
#define WEG_MUWTI_FUNC_CTWW			0x0068
#define WEG_GPIO_OUTPUT				0x006c
#define WEG_OPT_CTWW				0x0074
#define WEG_AFE_XTAW_CTWW_EXT			0x0078
#define WEG_XCK_OUT_CTWW			0x007c
#define WEG_MCUFWDW				0x0080
#define WEG_WOW_EVENT				0x0081
#define WEG_MCUTSTCFG				0x0084

#define WEG_HIMW				0x00B0
#define WEG_HISW				0x00B4
#define WEG_HIMWE				0x00B8
#define WEG_HISWE				0x00BC

#define WEG_PMC_DBG_CTWW2			0x00CC

#define WEG_EFUSE_ACCESS			0x00CF

#define WEG_BIST_SCAN				0x00D0
#define WEG_BIST_WPT				0x00D4
#define WEG_BIST_WOM_WPT			0x00D8
#define WEG_USB_SIE_INTF			0x00E0
#define WEG_PCIE_MIO_INTF			0x00E4
#define WEG_PCIE_MIO_INTD			0x00E8
#define WEG_HPON_FSM				0x00EC
#define WEG_SYS_CFG				0x00F0
#define WEG_GPIO_OUTSTS				0x00F4
#define WEG_MAC_PHY_CTWW_NOWMAW			0x00F8
#define WEG_SYS_CFG1				0x00FC
#define WEG_WOM_VEWSION				0x00FD

#define WEG_CW					0x0100
#define WEG_PBP					0x0104
#define WEG_PKT_BUFF_ACCESS_CTWW		0x0106
#define WEG_TWXDMA_CTWW				0x010C
#define WEG_TWXFF_BNDY				0x0114
#define WEG_TWXFF_STATUS			0x0118
#define WEG_WXFF_PTW				0x011C

#define WEG_CPWM				0x012F
#define WEG_FWIMW				0x0130
#define WEG_FWISW				0x0134
#define WEG_FTISW				0x013C
#define WEG_PKTBUF_DBG_CTWW			0x0140
#define WEG_PKTBUF_DBG_DATA_W			0x0144
#define WEG_PKTBUF_DBG_DATA_H			0x0148
#define WEG_WXPKTBUF_CTWW			(WEG_PKTBUF_DBG_CTWW+2)

#define WEG_TC0_CTWW				0x0150
#define WEG_TC1_CTWW				0x0154
#define WEG_TC2_CTWW				0x0158
#define WEG_TC3_CTWW				0x015C
#define WEG_TC4_CTWW				0x0160
#define WEG_TCUNIT_BASE				0x0164
#define WEG_MBIST_STAWT				0x0174
#define WEG_MBIST_DONE				0x0178
#define WEG_MBIST_FAIW				0x017C
#define WEG_32K_CTWW				0x0194
#define WEG_C2HEVT_MSG_NOWMAW			0x01A0
#define WEG_C2HEVT_CWEAW			0x01AF
#define WEG_C2HEVT_MSG_TEST			0x01B8
#define WEG_MCUTST_1				0x01c0
#define WEG_MCUTST_WOWWAN			0x01C7
#define WEG_FMETHW				0x01C8
#define WEG_HMETFW				0x01CC
#define WEG_HMEBOX_0				0x01D0
#define WEG_HMEBOX_1				0x01D4
#define WEG_HMEBOX_2				0x01D8
#define WEG_HMEBOX_3				0x01DC

#define WEG_WWT_INIT				0x01E0
#define WEG_BB_ACCEESS_CTWW			0x01E8
#define WEG_BB_ACCESS_DATA			0x01EC

#define WEG_HMEBOX_EXT_0			0x01F0
#define WEG_HMEBOX_EXT_1			0x01F4
#define WEG_HMEBOX_EXT_2			0x01F8
#define WEG_HMEBOX_EXT_3			0x01FC

#define WEG_WQPN				0x0200
#define WEG_FIFOPAGE				0x0204
#define WEG_TDECTWW				0x0208
#define WEG_TXDMA_OFFSET_CHK			0x020C
#define WEG_TXDMA_STATUS			0x0210
#define WEG_WQPN_NPQ				0x0214

#define WEG_WXDMA_AGG_PG_TH			0x0280
 /* FW shaww update this wegistew befowe FW wwite WXPKT_WEWEASE_POWW to 1 */
#define WEG_FW_UPD_WDPTW			0x0284
 /* Contwow the WX DMA.*/
#define WEG_WXDMA_CONTWOW			0x0286
/* The numbew of packets in WXPKTBUF.	*/
#define WEG_WXPKT_NUM				0x0287

#define	WEG_PCIE_CTWW_WEG			0x0300
#define	WEG_INT_MIG				0x0304
#define	WEG_BCNQ_DESA				0x0308
#define	WEG_HQ_DESA				0x0310
#define	WEG_MGQ_DESA				0x0318
#define	WEG_VOQ_DESA				0x0320
#define	WEG_VIQ_DESA				0x0328
#define	WEG_BEQ_DESA				0x0330
#define	WEG_BKQ_DESA				0x0338
#define	WEG_WX_DESA				0x0340

#define	WEG_DBI_WDATA				0x0348
#define	WEG_DBI_WDATA				0x034C
#define	WEG_DBI_CTWW				0x0350
#define	WEG_DBI_ADDW				0x0350
#define	WEG_DBI_FWAG				0x0352
#define	WEG_MDIO_WDATA				0x0354
#define	WEG_MDIO_WDATA				0x0356
#define	WEG_MDIO_CTW				0x0358
#define	WEG_DBG_SEW				0x0360
#define	WEG_PCIE_HWPWM				0x0361
#define	WEG_PCIE_HCPWM				0x0363
#define	WEG_UAWT_CTWW				0x0364
#define	WEG_WATCH_DOG				0x0368
#define	WEG_UAWT_TX_DESA			0x0370
#define	WEG_UAWT_WX_DESA			0x0378

#define	WEG_HDAQ_DESA_NODEF			0x0000
#define	WEG_CMDQ_DESA_NODEF			0x0000

#define WEG_VOQ_INFOWMATION			0x0400
#define WEG_VIQ_INFOWMATION			0x0404
#define WEG_BEQ_INFOWMATION			0x0408
#define WEG_BKQ_INFOWMATION			0x040C
#define WEG_MGQ_INFOWMATION			0x0410
#define WEG_HGQ_INFOWMATION			0x0414
#define WEG_BCNQ_INFOWMATION			0x0418
#define WEG_TXPKT_EMPTY				0x041A

#define WEG_CPU_MGQ_INFOWMATION			0x041C
#define WEG_FWHW_TXQ_CTWW			0x0420
#define WEG_HWSEQ_CTWW				0x0423
#define WEG_TXPKTBUF_BCNQ_BDNY			0x0424
#define WEG_TXPKTBUF_MGQ_BDNY			0x0425
#define WEG_MUWTI_BCNQ_EN			0x0426
#define WEG_MUWTI_BCNQ_OFFSET			0x0427
#define WEG_SPEC_SIFS				0x0428
#define WEG_WW					0x042A
#define WEG_DAWFWC				0x0430
#define WEG_WAWFWC				0x0438
#define WEG_WWSW				0x0440
#define WEG_AWFW0				0x0444
#define WEG_AWFW1				0x044C
#define WEG_CCK_CHECK				0x0454
#define WEG_AMPDU_MAX_TIME			0x0456
#define WEG_AGGWEN_WMT				0x0458
#define WEG_AMPDU_MIN_SPACE			0x045C
#define WEG_TXPKTBUF_WMAC_WBK_BF_HD		0x045D
#define WEG_FAST_EDCA_CTWW			0x0460
#define WEG_WD_WESP_PKT_TH			0x0463
#define WEG_INIWTS_WATE_SEW			0x0480
#define WEG_INIDATA_WATE_SEW			0x0484
#define WEG_AWFW2				0x048C
#define WEG_AWFW3				0x0494
#define WEG_POWEW_STATUS			0x04A4
#define WEG_POWEW_STAGE1			0x04B4
#define WEG_POWEW_STAGE2			0x04B8
#define WEG_PKT_WIFE_TIME			0x04C0
#define WEG_STBC_SETTING			0x04C4
#define WEG_HT_SINGWE_AMPDU			0x04C7
#define WEG_PWOT_MODE_CTWW			0x04C8
#define WEG_MAX_AGGW_NUM			0x04CA
#define WEG_BAW_MODE_CTWW			0x04CC
#define WEG_WA_TWY_WATE_AGG_WMT			0x04CF
#define WEG_EAWWY_MODE_CONTWOW			0x04D0
#define WEG_NQOS_SEQ				0x04DC
#define WEG_QOS_SEQ				0x04DE
#define WEG_NEED_CPU_HANDWE			0x04E0
#define WEG_PKT_WOSE_WPT			0x04E1
#define WEG_PTCW_EWW_STATUS			0x04E2
#define WEG_TX_WPT_CTWW				0x04EC
#define WEG_TX_WPT_TIME				0x04F0
#define WEG_DUMMY				0x04FC

#define WEG_EDCA_VO_PAWAM			0x0500
#define WEG_EDCA_VI_PAWAM			0x0504
#define WEG_EDCA_BE_PAWAM			0x0508
#define WEG_EDCA_BK_PAWAM			0x050C
#define WEG_BCNTCFG				0x0510
#define WEG_PIFS				0x0512
#define WEG_WDG_PIFS				0x0513
#define WEG_SIFS_CTX				0x0514
#define WEG_SIFS_TWX				0x0516
#define WEG_AGGW_BWEAK_TIME			0x051A
#define WEG_SWOT				0x051B
#define WEG_TX_PTCW_CTWW			0x0520
#define WEG_TXPAUSE				0x0522
#define WEG_DIS_TXWEQ_CWW			0x0523
#define WEG_WD_CTWW				0x0524
#define WEG_TBTT_PWOHIBIT			0x0540
#define WEG_WD_NAV_NXT				0x0544
#define WEG_NAV_PWOT_WEN			0x0546
#define WEG_BCN_CTWW				0x0550
#define WEG_MBID_NUM				0x0552
#define WEG_DUAW_TSF_WST			0x0553
#define WEG_BCN_INTEWVAW			0x0554
#define WEG_MBSSID_BCN_SPACE			0x0554
#define WEG_DWVEWWYINT				0x0558
#define WEG_BCNDMATIM				0x0559
#define WEG_ATIMWND				0x055A
#define WEG_USTIME_TSF				0x055C
#define WEG_BCN_MAX_EWW				0x055D
#define WEG_WXTSF_OFFSET_CCK			0x055E
#define WEG_WXTSF_OFFSET_OFDM			0x055F
#define WEG_TSFTW				0x0560
#define WEG_INIT_TSFTW				0x0564
#define WEG_SECONDAWY_CCA_CTWW			0x0577
#define WEG_PSTIMEW				0x0580
#define WEG_TIMEW0				0x0584
#define WEG_TIMEW1				0x0588
#define WEG_ACMHWCTWW				0x05C0
#define WEG_ACMWSTCTWW				0x05C1
#define WEG_ACMAVG				0x05C2
#define WEG_VO_ADMTIME				0x05C4
#define WEG_VI_ADMTIME				0x05C6
#define WEG_BE_ADMTIME				0x05C8
#define WEG_EDCA_WANDOM_GEN			0x05CC
#define WEG_NOA_DESC_SEW			0x05CF
#define WEG_NOA_DESC_DUWATION			0x05E0
#define WEG_NOA_DESC_INTEWVAW			0x05E4
#define WEG_NOA_DESC_STAWT			0x05E8
#define WEG_NOA_DESC_COUNT			0x05EC
#define WEG_SCH_TXCMD				0x05F8

#define WEG_APSD_CTWW				0x0600
#define WEG_BWOPMODE				0x0603
#define WEG_TCW					0x0604
#define WEG_WCW					0x0608
#define WEG_WX_PKT_WIMIT			0x060C
#define WEG_WX_DWK_TIME				0x060D
#define WEG_WX_DWVINFO_SZ			0x060F

#define WEG_MACID				0x0610
#define WEG_BSSID				0x0618
#define WEG_MAW					0x0620
#define WEG_MBIDCAMCFG				0x0628

#define WEG_USTIME_EDCA				0x0638
#define WEG_MAC_SPEC_SIFS			0x063A
#define WEG_WESP_SIFS_CCK			0x063C
#define WEG_WESP_SIFS_OFDM			0x063E
#define WEG_ACKTO				0x0640
#define WEG_CTS2TO				0x0641
#define WEG_EIFS				0x0642

#define WEG_NAV_CTWW				0x0650
#define WEG_NAV_UPPEW				0x0652
#define WEG_BACAMCMD				0x0654
#define WEG_BACAMCONTENT			0x0658
#define WEG_WBDWY				0x0660
#define WEG_FWDWY				0x0661
#define WEG_WXEWW_WPT				0x0664
#define WEG_TWXPTCW_CTW				0x0668

#define WEG_CAMCMD				0x0670
#define WEG_CAMWWITE				0x0674
#define WEG_CAMWEAD				0x0678
#define WEG_CAMDBG				0x067C
#define WEG_SECCFG				0x0680

#define WEG_WOW_CTWW				0x0690
#define WEG_PSSTATUS				0x0691
#define WEG_PS_WX_INFO				0x0692
#define WEG_UAPSD_TID				0x0693
#define WEG_WPNAV_CTWW				0x0694
#define WEG_WKFMCAM_NUM				0x0698
#define WEG_WKFMCAM_WWD				0x069C
#define WEG_WXFWTMAP0				0x06A0
#define WEG_WXFWTMAP1				0x06A2
#define WEG_WXFWTMAP2				0x06A4
#define WEG_BCN_PSW_WPT				0x06A8
#define WEG_CAWB32K_CTWW			0x06AC
#define WEG_PKT_MON_CTWW			0x06B4
#define WEG_BT_COEX_TABWE			0x06C0
#define WEG_WMAC_WESP_TXINFO			0x06D8

#define WEG_USB_INFO				0xFE17
#define WEG_USB_SPECIAW_OPTION			0xFE55
#define WEG_USB_DMA_AGG_TO			0xFE5B
#define WEG_USB_AGG_TO				0xFE5C
#define WEG_USB_AGG_TH				0xFE5D

#define WEG_TEST_USB_TXQS			0xFE48
#define WEG_TEST_SIE_VID			0xFE60
#define WEG_TEST_SIE_PID			0xFE62
#define WEG_TEST_SIE_OPTIONAW			0xFE64
#define WEG_TEST_SIE_CHIWP_K			0xFE65
#define WEG_TEST_SIE_PHY			0xFE66
#define WEG_TEST_SIE_MAC_ADDW			0xFE70
#define WEG_TEST_SIE_STWING			0xFE80

#define WEG_NOWMAW_SIE_VID			0xFE60
#define WEG_NOWMAW_SIE_PID			0xFE62
#define WEG_NOWMAW_SIE_OPTIONAW			0xFE64
#define WEG_NOWMAW_SIE_EP			0xFE65
#define WEG_NOWMAW_SIE_PHY			0xFE68
#define WEG_NOWMAW_SIE_MAC_ADDW			0xFE70
#define WEG_NOWMAW_SIE_STWING			0xFE80

#define	CW9346					WEG_9346CW
#define	MSW					(WEG_CW + 2)
#define	ISW					WEG_HISW
#define	TSFW					WEG_TSFTW

#define	MACIDW0					WEG_MACID
#define	MACIDW4					(WEG_MACID + 4)

#define PBP					WEG_PBP

#define	IDW0					MACIDW0
#define	IDW4					MACIDW4

#define	UNUSED_WEGISTEW				0x1BF
#define	DCAM					UNUSED_WEGISTEW
#define	PSW					UNUSED_WEGISTEW
#define BBADDW					UNUSED_WEGISTEW
#define	PHYDATAW				UNUSED_WEGISTEW

#define	INVAWID_BBWF_VAWUE			0x12345678

#define	MAX_MSS_DENSITY_2T			0x13
#define	MAX_MSS_DENSITY_1T			0x0A

#define	CMDEEPWOM_EN				BIT(5)
#define	CMDEEPWOM_SEW				BIT(4)
#define	CMD9346CW_9356SEW			BIT(4)
#define	AUTOWOAD_EEPWOM			(CMDEEPWOM_EN|CMDEEPWOM_SEW)
#define	AUTOWOAD_EFUSE			CMDEEPWOM_EN

#define	GPIOSEW_GPIO				0
#define	GPIOSEW_ENBT				BIT(5)

#define	GPIO_IN				WEG_GPIO_PIN_CTWW
#define	GPIO_OUT			(WEG_GPIO_PIN_CTWW+1)
#define	GPIO_IO_SEW			(WEG_GPIO_PIN_CTWW+2)
#define	GPIO_MOD			(WEG_GPIO_PIN_CTWW+3)

/*    8723/8188E Host System Intewwupt Mask Wegistew (offset 0x58, 32 byte) */
#define	HSIMW_GPIO12_0_INT_EN			BIT(0)
#define	HSIMW_SPS_OCP_INT_EN			BIT(5)
#define	HSIMW_WON_INT_EN			BIT(6)
#define	HSIMW_PDN_INT_EN			BIT(7)
#define	HSIMW_GPIO9_INT_EN			BIT(25)

/* 8723/8188E Host System Intewwupt Status Wegistew (offset 0x5C, 32 byte) */
#define	HSISW_GPIO12_0_INT			BIT(0)
#define	HSISW_SPS_OCP_INT			BIT(5)
#define	HSISW_WON_INT_EN			BIT(6)
#define	HSISW_PDNINT				BIT(7)
#define	HSISW_GPIO9_INT				BIT(25)

#define	MSW_NOWINK				0x00
#define	MSW_ADHOC				0x01
#define	MSW_INFWA				0x02
#define	MSW_AP					0x03
#define MSW_MASK				0x03

#define	WWSW_WSC_OFFSET				21
#define	WWSW_SHOWT_OFFSET			23
#define	WWSW_WSC_BW_40M				0x600000
#define	WWSW_WSC_UPSUBCHNW			0x400000
#define	WWSW_WSC_WOWSUBCHNW			0x200000
#define	WWSW_SHOWT				0x800000
#define	WWSW_1M					BIT(0)
#define	WWSW_2M					BIT(1)
#define	WWSW_5_5M				BIT(2)
#define	WWSW_11M				BIT(3)
#define	WWSW_6M					BIT(4)
#define	WWSW_9M					BIT(5)
#define	WWSW_12M				BIT(6)
#define	WWSW_18M				BIT(7)
#define	WWSW_24M				BIT(8)
#define	WWSW_36M				BIT(9)
#define	WWSW_48M				BIT(10)
#define	WWSW_54M				BIT(11)
#define	WWSW_MCS0				BIT(12)
#define	WWSW_MCS1				BIT(13)
#define	WWSW_MCS2				BIT(14)
#define	WWSW_MCS3				BIT(15)
#define	WWSW_MCS4				BIT(16)
#define	WWSW_MCS5				BIT(17)
#define	WWSW_MCS6				BIT(18)
#define	WWSW_MCS7				BIT(19)
#define	BWSW_ACKSHOWTPMB			BIT(23)

#define	WATW_1M					0x00000001
#define	WATW_2M					0x00000002
#define	WATW_55M				0x00000004
#define	WATW_11M				0x00000008
#define	WATW_6M					0x00000010
#define	WATW_9M					0x00000020
#define	WATW_12M				0x00000040
#define	WATW_18M				0x00000080
#define	WATW_24M				0x00000100
#define	WATW_36M				0x00000200
#define	WATW_48M				0x00000400
#define	WATW_54M				0x00000800
#define	WATW_MCS0				0x00001000
#define	WATW_MCS1				0x00002000
#define	WATW_MCS2				0x00004000
#define	WATW_MCS3				0x00008000
#define	WATW_MCS4				0x00010000
#define	WATW_MCS5				0x00020000
#define	WATW_MCS6				0x00040000
#define	WATW_MCS7				0x00080000
#define	WATW_MCS8				0x00100000
#define	WATW_MCS9				0x00200000
#define	WATW_MCS10				0x00400000
#define	WATW_MCS11				0x00800000
#define	WATW_MCS12				0x01000000
#define	WATW_MCS13				0x02000000
#define	WATW_MCS14				0x04000000
#define	WATW_MCS15				0x08000000

#define WATE_1M					BIT(0)
#define WATE_2M					BIT(1)
#define WATE_5_5M				BIT(2)
#define WATE_11M				BIT(3)
#define WATE_6M					BIT(4)
#define WATE_9M					BIT(5)
#define WATE_12M				BIT(6)
#define WATE_18M				BIT(7)
#define WATE_24M				BIT(8)
#define WATE_36M				BIT(9)
#define WATE_48M				BIT(10)
#define WATE_54M				BIT(11)
#define WATE_MCS0				BIT(12)
#define WATE_MCS1				BIT(13)
#define WATE_MCS2				BIT(14)
#define WATE_MCS3				BIT(15)
#define WATE_MCS4				BIT(16)
#define WATE_MCS5				BIT(17)
#define WATE_MCS6				BIT(18)
#define WATE_MCS7				BIT(19)
#define WATE_MCS8				BIT(20)
#define WATE_MCS9				BIT(21)
#define WATE_MCS10				BIT(22)
#define WATE_MCS11				BIT(23)
#define WATE_MCS12				BIT(24)
#define WATE_MCS13				BIT(25)
#define WATE_MCS14				BIT(26)
#define WATE_MCS15				BIT(27)

#define	WATE_AWW_CCK		(WATW_1M | WATW_2M | WATW_55M | WATW_11M)
#define	WATE_AWW_OFDM_AG	(WATW_6M | WATW_9M | WATW_12M | WATW_18M |\
				WATW_24M | WATW_36M | WATW_48M | WATW_54M)
#define	WATE_AWW_OFDM_1SS	(WATW_MCS0 | WATW_MCS1 | WATW_MCS2 |\
				WATW_MCS3 | WATW_MCS4 | WATW_MCS5 |\
				WATW_MCS6 | WATW_MCS7)
#define	WATE_AWW_OFDM_2SS	(WATW_MCS8 | WATW_MCS9 | WATW_MCS10 |\
				WATW_MCS11 | WATW_MCS12 | WATW_MCS13 |\
				WATW_MCS14 | WATW_MCS15)

#define	BW_OPMODE_20MHZ				BIT(2)
#define	BW_OPMODE_5G				BIT(1)
#define	BW_OPMODE_11J				BIT(0)

#define	CAM_VAWID				BIT(15)
#define	CAM_NOTVAWID				0x0000
#define	CAM_USEDK				BIT(5)

#define	CAM_NONE				0x0
#define	CAM_WEP40				0x01
#define	CAM_TKIP				0x02
#define	CAM_AES					0x04
#define	CAM_WEP104				0x05

#define	TOTAW_CAM_ENTWY				32
#define	HAWF_CAM_ENTWY				16

#define	CAM_WWITE				BIT(16)
#define	CAM_WEAD				0x00000000
#define	CAM_POWWINIG				BIT(31)

#define	SCW_USEDK				0x01
#define	SCW_TXSEC_ENABWE			0x02
#define	SCW_WXSEC_ENABWE			0x04

#define	WOW_PMEN				BIT(0)
#define	WOW_WOMEN				BIT(1)
#define	WOW_MAGIC				BIT(2)
#define	WOW_UWF					BIT(3)

/*********************************************
*       8188 IMW/ISW bits
**********************************************/
#define	IMW_DISABWED				0x0
/* IMW DW0(0x0060-0063) Bit 0-31 */
/* TXWPT intewwupt when CCX bit of the packet is set	*/
#define	IMW_TXCCK				BIT(30)
/* Powew Save Time Out Intewwupt */
#define	IMW_PSTIMEOUT				BIT(29)
/* When GTIMEW4 expiwes, this bit is set to 1	*/
#define	IMW_GTINT4				BIT(28)
/* When GTIMEW3 expiwes, this bit is set to 1	*/
#define	IMW_GTINT3				BIT(27)
/* Twansmit Beacon0 Ewwow			*/
#define	IMW_TBDEW				BIT(26)
/* Twansmit Beacon0 OK			*/
#define	IMW_TBDOK				BIT(25)
/* TSF Timew BIT32 toggwe indication intewwupt		*/
#define	IMW_TSF_BIT32_TOGGWE			BIT(24)
/* Beacon DMA Intewwupt 0			*/
#define	IMW_BCNDMAINT0				BIT(20)
/* Beacon Queue DMA OK0			*/
#define	IMW_BCNDOK0				BIT(16)
/* HSISW Indicatow (HSIMW & HSISW is twue, this bit is set to 1) */
#define	IMW_HSISW_IND_ON_INT			BIT(15)
/* Beacon DMA Intewwupt Extension fow Win7			*/
#define	IMW_BCNDMAINT_E				BIT(14)
/* CTWidnow End ow ATIM Window End */
#define	IMW_ATIMEND				BIT(12)
/* HISW1 Indicatow (HISW1 & HIMW1 is twue, this bit is set to 1)*/
#define	IMW_HISW1_IND_INT			BIT(11)
/* CPU to Host Command INT Status, Wwite 1 cweaw	*/
#define	IMW_C2HCMD				BIT(10)
/* CPU powew Mode exchange INT Status, Wwite 1 cweaw	*/
#define	IMW_CPWM2				BIT(9)
/* CPU powew Mode exchange INT Status, Wwite 1 cweaw	*/
#define	IMW_CPWM				BIT(8)
/* High Queue DMA OK	*/
#define	IMW_HIGHDOK				BIT(7)
/* Management Queue DMA OK	*/
#define	IMW_MGNTDOK				BIT(6)
/* AC_BK DMA OK		*/
#define	IMW_BKDOK				BIT(5)
/* AC_BE DMA OK	*/
#define	IMW_BEDOK				BIT(4)
/* AC_VI DMA OK	*/
#define	IMW_VIDOK				BIT(3)
/* AC_VO DMA OK	*/
#define	IMW_VODOK				BIT(2)
/* Wx Descwiptow Unavaiwabwe	*/
#define	IMW_WDU					BIT(1)
#define	IMW_WOK					BIT(0)	/* Weceive DMA OK */

/* IMW DW1(0x00B4-00B7) Bit 0-31 */
/* Beacon DMA Intewwupt 7	*/
#define	IMW_BCNDMAINT7				BIT(27)
/* Beacon DMA Intewwupt 6		*/
#define	IMW_BCNDMAINT6				BIT(26)
/* Beacon DMA Intewwupt 5		*/
#define	IMW_BCNDMAINT5				BIT(25)
/* Beacon DMA Intewwupt 4		*/
#define	IMW_BCNDMAINT4				BIT(24)
/* Beacon DMA Intewwupt 3		*/
#define	IMW_BCNDMAINT3				BIT(23)
/* Beacon DMA Intewwupt 2		*/
#define	IMW_BCNDMAINT2				BIT(22)
/* Beacon DMA Intewwupt 1		*/
#define	IMW_BCNDMAINT1				BIT(21)
/* Beacon Queue DMA OK Intewwup 7 */
#define	IMW_BCNDOK7				BIT(20)
/* Beacon Queue DMA OK Intewwup 6 */
#define	IMW_BCNDOK6				BIT(19)
/* Beacon Queue DMA OK Intewwup 5 */
#define	IMW_BCNDOK5				BIT(18)
/* Beacon Queue DMA OK Intewwup 4 */
#define	IMW_BCNDOK4				BIT(17)
/* Beacon Queue DMA OK Intewwup 3 */
#define	IMW_BCNDOK3				BIT(16)
/* Beacon Queue DMA OK Intewwup 2 */
#define	IMW_BCNDOK2				BIT(15)
/* Beacon Queue DMA OK Intewwup 1 */
#define	IMW_BCNDOK1				BIT(14)
/* ATIM Window End Extension fow Win7 */
#define	IMW_ATIMEND_E				BIT(13)
/* Tx Ewwow Fwag Intewwupt Status, wwite 1 cweaw. */
#define	IMW_TXEWW				BIT(11)
/* Wx Ewwow Fwag INT Status, Wwite 1 cweaw */
#define	IMW_WXEWW				BIT(10)
/* Twansmit FIFO Ovewfwow */
#define	IMW_TXFOVW				BIT(9)
/* Weceive FIFO Ovewfwow */
#define	IMW_WXFOVW				BIT(8)

#define	HWSET_MAX_SIZE				512
#define   EFUSE_MAX_SECTION			64
#define   EFUSE_WEAW_CONTENT_WEN		256
/* PG data excwude headew, dummy 7 bytes fwome CP test and wesewved 1byte.*/
#define		EFUSE_OOB_PWOTECT_BYTES		18

#define	EEPWOM_DEFAUWT_TSSI			0x0
#define EEPWOM_DEFAUWT_TXPOWEWDIFF		0x0
#define EEPWOM_DEFAUWT_CWYSTAWCAP		0x5
#define EEPWOM_DEFAUWT_BOAWDTYPE		0x02
#define EEPWOM_DEFAUWT_TXPOWEW			0x1010
#define	EEPWOM_DEFAUWT_HT2T_TXPWW		0x10

#define	EEPWOM_DEFAUWT_WEGACYHTTXPOWEWDIFF	0x3
#define	EEPWOM_DEFAUWT_THEWMAWMETEW		0x18
#define	EEPWOM_DEFAUWT_ANTTXPOWEWDIFF		0x0
#define	EEPWOM_DEFAUWT_TXPWDIFF_CWYSTAWCAP	0x5
#define	EEPWOM_DEFAUWT_TXPOWEWWEVEW		0x22
#define	EEPWOM_DEFAUWT_HT40_2SDIFF		0x0
#define EEPWOM_DEFAUWT_HT20_DIFF		2
#define	EEPWOM_DEFAUWT_WEGACYHTTXPOWEWDIFF	0x3
#define EEPWOM_DEFAUWT_HT40_PWWMAXOFFSET	0
#define EEPWOM_DEFAUWT_HT20_PWWMAXOFFSET	0

#define WF_OPTION1				0x79
#define WF_OPTION2				0x7A
#define WF_OPTION3				0x7B
#define WF_OPTION4				0xC3

#define EEPWOM_DEFAUWT_PID			0x1234
#define EEPWOM_DEFAUWT_VID			0x5678
#define EEPWOM_DEFAUWT_CUSTOMEWID		0xAB
#define EEPWOM_DEFAUWT_SUBCUSTOMEWID		0xCD
#define EEPWOM_DEFAUWT_VEWSION			0

#define	EEPWOM_CHANNEW_PWAN_FCC			0x0
#define	EEPWOM_CHANNEW_PWAN_IC			0x1
#define	EEPWOM_CHANNEW_PWAN_ETSI		0x2
#define	EEPWOM_CHANNEW_PWAN_SPAIN		0x3
#define	EEPWOM_CHANNEW_PWAN_FWANCE		0x4
#define	EEPWOM_CHANNEW_PWAN_MKK			0x5
#define	EEPWOM_CHANNEW_PWAN_MKK1		0x6
#define	EEPWOM_CHANNEW_PWAN_ISWAEW		0x7
#define	EEPWOM_CHANNEW_PWAN_TEWEC		0x8
#define	EEPWOM_CHANNEW_PWAN_GWOBAW_DOMAIN	0x9
#define	EEPWOM_CHANNEW_PWAN_WOWWD_WIDE_13	0xA
#define	EEPWOM_CHANNEW_PWAN_NCC			0XB
#define	EEPWOM_CHANNEW_PWAN_BY_HW_MASK		0x80

#define EEPWOM_CID_DEFAUWT			0x0
#define EEPWOM_CID_TOSHIBA			0x4
#define	EEPWOM_CID_CCX				0x10
#define	EEPWOM_CID_QMI				0x0D
#define EEPWOM_CID_WHQW				0xFE

#define	WTW_EEPWOM_ID				0x8129

#define EEPWOM_HPON				0x02
#define EEPWOM_CWK				0x06
#define EEPWOM_TESTW				0x08

#define EEPWOM_TXPOWEWCCK			0x10
#define	EEPWOM_TXPOWEWHT40_1S			0x16
#define EEPWOM_TXPOWEWHT20DIFF			0x1B
#define EEPWOM_TXPOWEW_OFDMDIFF			0x1B

#define	EEPWOM_TX_PWW_INX			0x10

#define	EEPWOM_CHANNEWPWAN			0XB8
#define	EEPWOM_XTAW_8821AE			0XB9
#define	EEPWOM_THEWMAW_METEW			0XBA
#define	EEPWOM_IQK_WCK_88E			0XBB

#define	EEPWOM_WF_BOAWD_OPTION			0xC1
#define	EEPWOM_WF_FEATUWE_OPTION_88E		0xC2
#define	EEPWOM_WF_BT_SETTING			0xC3
#define	EEPWOM_VEWSION				0xC4
#define	EEPWOM_CUSTOMEW_ID			0xC5
#define	EEPWOM_WF_ANTENNA_OPT_88E		0xC9
#define	EEPWOM_WFE_OPTION			0xCA

#define	EEPWOM_MAC_ADDW				0xD0
#define EEPWOM_VID				0xD6
#define EEPWOM_DID				0xD8
#define EEPWOM_SVID				0xDA
#define EEPWOM_SMID				0xDC

#define	STOPBECON				BIT(6)
#define	STOPHIGHT				BIT(5)
#define	STOPMGT					BIT(4)
#define	STOPVO					BIT(3)
#define	STOPVI					BIT(2)
#define	STOPBE					BIT(1)
#define	STOPBK					BIT(0)

#define	WCW_APPFCS				BIT(31)
#define	WCW_APP_MIC				BIT(30)
#define	WCW_APP_ICV				BIT(29)
#define	WCW_APP_PHYST_WXFF			BIT(28)
#define	WCW_APP_BA_SSN				BIT(27)
#define	WCW_NONQOS_VHT				BIT(26)
#define	WCW_ENMBID				BIT(24)
#define	WCW_WSIGEN				BIT(23)
#define	WCW_MFBEN				BIT(22)
#define	WCW_HTC_WOC_CTWW			BIT(14)
#define	WCW_AMF					BIT(13)
#define	WCW_ACF					BIT(12)
#define	WCW_ADF					BIT(11)
#define	WCW_AICV				BIT(9)
#define	WCW_ACWC32				BIT(8)
#define	WCW_CBSSID_BCN				BIT(7)
#define	WCW_CBSSID_DATA				BIT(6)
#define	WCW_CBSSID				WCW_CBSSID_DATA
#define	WCW_APWWMGT				BIT(5)
#define	WCW_ADD3				BIT(4)
#define	WCW_AB					BIT(3)
#define	WCW_AM					BIT(2)
#define	WCW_APM					BIT(1)
#define	WCW_AAP					BIT(0)
#define	WCW_MXDMA_OFFSET			8
#define	WCW_FIFO_OFFSET				13

#define WSV_CTWW				0x001C
#define WD_CTWW					0x0524

#define WEG_USB_INFO				0xFE17
#define WEG_USB_SPECIAW_OPTION			0xFE55
#define WEG_USB_DMA_AGG_TO			0xFE5B
#define WEG_USB_AGG_TO				0xFE5C
#define WEG_USB_AGG_TH				0xFE5D

#define WEG_USB_VID				0xFE60
#define WEG_USB_PID				0xFE62
#define WEG_USB_OPTIONAW			0xFE64
#define WEG_USB_CHIWP_K				0xFE65
#define WEG_USB_PHY				0xFE66
#define WEG_USB_MAC_ADDW			0xFE70
#define WEG_USB_HWPWM				0xFE58
#define WEG_USB_HCPWM				0xFE57

#define SW18_FPWM				BIT(3)

#define ISO_MD2PP				BIT(0)
#define ISO_UA2USB				BIT(1)
#define ISO_UD2COWE				BIT(2)
#define ISO_PA2PCIE				BIT(3)
#define ISO_PD2COWE				BIT(4)
#define ISO_IP2MAC				BIT(5)
#define ISO_DIOP				BIT(6)
#define ISO_DIOE				BIT(7)
#define ISO_EB2COWE				BIT(8)
#define ISO_DIOW				BIT(9)

#define PWC_EV25V				BIT(14)
#define PWC_EV12V				BIT(15)

#define FEN_BBWSTB				BIT(0)
#define FEN_BB_GWB_WSTN				BIT(1)
#define FEN_USBA				BIT(2)
#define FEN_UPWW				BIT(3)
#define FEN_USBD				BIT(4)
#define FEN_DIO_PCIE				BIT(5)
#define FEN_PCIEA				BIT(6)
#define FEN_PPWW				BIT(7)
#define FEN_PCIED				BIT(8)
#define FEN_DIOE				BIT(9)
#define FEN_CPUEN				BIT(10)
#define FEN_DCOWE				BIT(11)
#define FEN_EWDW				BIT(12)
#define FEN_DIO_WF				BIT(13)
#define FEN_HWPDN				BIT(14)
#define FEN_MWEGEN				BIT(15)

#define PFM_WDAWW				BIT(0)
#define PFM_AWDN				BIT(1)
#define PFM_WDKP				BIT(2)
#define PFM_WOWW				BIT(3)
#define ENPDN					BIT(4)
#define PDN_PW					BIT(5)
#define APFM_ONMAC				BIT(8)
#define APFM_OFF				BIT(9)
#define APFM_WSM				BIT(10)
#define AFSM_HSUS				BIT(11)
#define AFSM_PCIE				BIT(12)
#define APDM_MAC				BIT(13)
#define APDM_HOST				BIT(14)
#define APDM_HPDN				BIT(15)
#define WDY_MACON				BIT(16)
#define SUS_HOST				BIT(17)
#define WOP_AWD					BIT(20)
#define WOP_PWW					BIT(21)
#define WOP_SPS					BIT(22)
#define SOP_MWST				BIT(25)
#define SOP_FUSE				BIT(26)
#define SOP_ABG					BIT(27)
#define SOP_AMB					BIT(28)
#define SOP_WCK					BIT(29)
#define SOP_A8M					BIT(30)
#define XOP_BTCK				BIT(31)

#define ANAD16V_EN				BIT(0)
#define ANA8M					BIT(1)
#define MACSWP					BIT(4)
#define WOADEW_CWK_EN				BIT(5)
#define _80M_SSC_DIS				BIT(7)
#define _80M_SSC_EN_HO				BIT(8)
#define PHY_SSC_WSTB				BIT(9)
#define SEC_CWK_EN				BIT(10)
#define MAC_CWK_EN				BIT(11)
#define SYS_CWK_EN				BIT(12)
#define WING_CWK_EN				BIT(13)

#define	BOOT_FWOM_EEPWOM			BIT(4)
#define	EEPWOM_EN				BIT(5)

#define AFE_BGEN				BIT(0)
#define AFE_MBEN				BIT(1)
#define MAC_ID_EN				BIT(7)

#define WWOCK_AWW				BIT(0)
#define WWOCK_00				BIT(1)
#define WWOCK_04				BIT(2)
#define WWOCK_08				BIT(3)
#define WWOCK_40				BIT(4)
#define W_DIS_PWST_0				BIT(5)
#define W_DIS_PWST_1				BIT(6)
#define WOCK_AWW_EN				BIT(7)

#define WF_EN					BIT(0)
#define WF_WSTB					BIT(1)
#define WF_SDMWSTB				BIT(2)

#define WDA15_EN				BIT(0)
#define WDA15_STBY				BIT(1)
#define WDA15_OBUF				BIT(2)
#define WDA15_WEG_VOS				BIT(3)
#define _WDA15_VOADJ(x)				(((x) & 0x7) << 4)

#define WDV12_EN				BIT(0)
#define WDV12_SDBY				BIT(1)
#define WPWDO_HSM				BIT(2)
#define WPWDO_WSM_DIS				BIT(3)
#define _WDV12_VADJ(x)				(((x) & 0xF) << 4)

#define XTAW_EN					BIT(0)
#define XTAW_BSEW				BIT(1)
#define _XTAW_BOSC(x)				(((x) & 0x3) << 2)
#define _XTAW_CADJ(x)				(((x) & 0xF) << 4)
#define XTAW_GATE_USB				BIT(8)
#define _XTAW_USB_DWV(x)			(((x) & 0x3) << 9)
#define XTAW_GATE_AFE				BIT(11)
#define _XTAW_AFE_DWV(x)			(((x) & 0x3) << 12)
#define XTAW_WF_GATE				BIT(14)
#define _XTAW_WF_DWV(x)				(((x) & 0x3) << 15)
#define XTAW_GATE_DIG				BIT(17)
#define _XTAW_DIG_DWV(x)			(((x) & 0x3) << 18)
#define XTAW_BT_GATE				BIT(20)
#define _XTAW_BT_DWV(x)				(((x) & 0x3) << 21)
#define _XTAW_GPIO(x)				(((x) & 0x7) << 23)

#define CKDWY_AFE				BIT(26)
#define CKDWY_USB				BIT(27)
#define CKDWY_DIG				BIT(28)
#define CKDWY_BT				BIT(29)

#define APWW_EN					BIT(0)
#define APWW_320_EN				BIT(1)
#define APWW_FWEF_SEW				BIT(2)
#define APWW_EDGE_SEW				BIT(3)
#define APWW_WDOGB				BIT(4)
#define APWW_WPFEN				BIT(5)

#define APWW_WEF_CWK_13MHZ			0x1
#define APWW_WEF_CWK_19_2MHZ			0x2
#define APWW_WEF_CWK_20MHZ			0x3
#define APWW_WEF_CWK_25MHZ			0x4
#define APWW_WEF_CWK_26MHZ			0x5
#define APWW_WEF_CWK_38_4MHZ			0x6
#define APWW_WEF_CWK_40MHZ			0x7

#define APWW_320EN				BIT(14)
#define APWW_80EN				BIT(15)
#define APWW_1MEN				BIT(24)

#define AWD_EN					BIT(18)
#define EF_PD					BIT(19)
#define EF_FWAG					BIT(31)

#define EF_TWPT					BIT(7)
#define WDOE25_EN				BIT(31)

#define WSM_EN					BIT(0)
#define TIMEW_EN				BIT(4)

#define TWSW0EN					BIT(2)
#define TWSW1EN					BIT(3)
#define EWOM_EN					BIT(4)
#define ENBT					BIT(5)
#define ENUAWT					BIT(8)
#define UAWT_910				BIT(9)
#define ENPMAC					BIT(10)
#define SIC_SWWST				BIT(11)
#define ENSIC					BIT(12)
#define SIC_23					BIT(13)
#define ENHDP					BIT(14)
#define SIC_WBK					BIT(15)

#define WED0PW					BIT(4)
#define WED1PW					BIT(12)
#define WED0DIS					BIT(7)

#define MCUFWDW_EN				BIT(0)
#define MCUFWDW_WDY				BIT(1)
#define FWDW_CHKSUM_WPT				BIT(2)
#define MACINI_WDY				BIT(3)
#define BBINI_WDY				BIT(4)
#define WFINI_WDY				BIT(5)
#define WINTINI_WDY				BIT(6)
#define CPWST					BIT(23)

#define XCWK_VWD				BIT(0)
#define ACWK_VWD				BIT(1)
#define UCWK_VWD				BIT(2)
#define PCWK_VWD				BIT(3)
#define PCIWSTB					BIT(4)
#define V15_VWD					BIT(5)
#define TWP_B15V_EN				BIT(7)
#define SIC_IDWE				BIT(8)
#define BD_MAC2					BIT(9)
#define BD_MAC1					BIT(10)
#define IC_MACPHY_MODE				BIT(11)
#define VENDOW_ID				BIT(19)
#define PAD_HWPD_IDN				BIT(22)
#define TWP_VAUX_EN				BIT(23)
#define TWP_BT_EN				BIT(24)
#define BD_PKG_SEW				BIT(25)
#define BD_HCI_SEW				BIT(26)
#define TYPE_ID					BIT(27)

#define CHIP_VEW_WTW_MASK			0xF000
#define CHIP_VEW_WTW_SHIFT			12

#define WEG_WBMODE				(WEG_CW + 3)

#define HCI_TXDMA_EN				BIT(0)
#define HCI_WXDMA_EN				BIT(1)
#define TXDMA_EN				BIT(2)
#define WXDMA_EN				BIT(3)
#define PWOTOCOW_EN				BIT(4)
#define SCHEDUWE_EN				BIT(5)
#define MACTXEN					BIT(6)
#define MACWXEN					BIT(7)
#define ENSWBCN					BIT(8)
#define ENSEC					BIT(9)

#define _NETTYPE(x)				(((x) & 0x3) << 16)
#define MASK_NETTYPE				0x30000
#define NT_NO_WINK				0x0
#define NT_WINK_AD_HOC				0x1
#define NT_WINK_AP				0x2
#define NT_AS_AP				0x3

#define _WBMODE(x)				(((x) & 0xF) << 24)
#define MASK_WBMODE				0xF000000
#define WOOPBACK_NOWMAW				0x0
#define WOOPBACK_IMMEDIATEWY			0XB
#define WOOPBACK_MAC_DEWAY			0x3
#define WOOPBACK_PHY				0x1
#define WOOPBACK_DMA				0x7

#define GET_WX_PAGE_SIZE(vawue)		((vawue) & 0xF)
#define GET_TX_PAGE_SIZE(vawue)		(((vawue) & 0xF0) >> 4)
#define _PSWX_MASK				0xF
#define _PSTX_MASK				0xF0
#define _PSWX(x)				(x)
#define _PSTX(x)				((x) << 4)

#define PBP_64					0x0
#define PBP_128					0x1
#define PBP_256					0x2
#define PBP_512					0x3
#define PBP_1024				0x4

#define WXDMA_AWBBW_EN				BIT(0)
#define WXSHFT_EN				BIT(1)
#define WXDMA_AGG_EN				BIT(2)
#define QS_VO_QUEUE				BIT(8)
#define QS_VI_QUEUE				BIT(9)
#define QS_BE_QUEUE				BIT(10)
#define QS_BK_QUEUE				BIT(11)
#define QS_MANAGEW_QUEUE			BIT(12)
#define QS_HIGH_QUEUE				BIT(13)

#define HQSEW_VOQ				BIT(0)
#define HQSEW_VIQ				BIT(1)
#define HQSEW_BEQ				BIT(2)
#define HQSEW_BKQ				BIT(3)
#define HQSEW_MGTQ				BIT(4)
#define HQSEW_HIQ				BIT(5)

#define _TXDMA_HIQ_MAP(x)			(((x)&0x3) << 14)
#define _TXDMA_MGQ_MAP(x)			(((x)&0x3) << 12)
#define _TXDMA_BKQ_MAP(x)			(((x)&0x3) << 10)
#define _TXDMA_BEQ_MAP(x)			(((x)&0x3) << 8)
#define _TXDMA_VIQ_MAP(x)			(((x)&0x3) << 6)
#define _TXDMA_VOQ_MAP(x)			(((x)&0x3) << 4)

#define QUEUE_WOW				1
#define QUEUE_NOWMAW				2
#define QUEUE_HIGH				3

#define _WWT_NO_ACTIVE				0x0
#define _WWT_WWITE_ACCESS			0x1
#define _WWT_WEAD_ACCESS			0x2

#define _WWT_INIT_DATA(x)			((x) & 0xFF)
#define _WWT_INIT_ADDW(x)			(((x) & 0xFF) << 8)
#define _WWT_OP(x)				(((x) & 0x3) << 30)
#define _WWT_OP_VAWUE(x)			(((x) >> 30) & 0x3)

#define BB_WWITE_WEAD_MASK			(BIT(31) | BIT(30))
#define BB_WWITE_EN				BIT(30)
#define BB_WEAD_EN				BIT(31)

#define _HPQ(x)				((x) & 0xFF)
#define _WPQ(x)				(((x) & 0xFF) << 8)
#define _PUBQ(x)			(((x) & 0xFF) << 16)
#define _NPQ(x)				((x) & 0xFF)

#define HPQ_PUBWIC_DIS				BIT(24)
#define WPQ_PUBWIC_DIS				BIT(25)
#define WD_WQPN					BIT(31)

#define BCN_VAWID				BIT(16)
#define BCN_HEAD(x)			(((x) & 0xFF) << 8)
#define	BCN_HEAD_MASK				0xFF00

#define BWK_DESC_NUM_SHIFT			4
#define BWK_DESC_NUM_MASK			0xF

#define DWOP_DATA_EN				BIT(9)

#define EN_AMPDU_WTY_NEW			BIT(7)

#define _INIWTSMCS_SEW(x)			((x) & 0x3F)

#define _SPEC_SIFS_CCK(x)			((x) & 0xFF)
#define _SPEC_SIFS_OFDM(x)			(((x) & 0xFF) << 8)

#define WATE_WEG_BITMAP_AWW			0xFFFFF

#define _WWSC_BITMAP(x)				((x) & 0xFFFFF)

#define _WWSW_WSC(x)				(((x) & 0x3) << 21)
#define WWSW_WSC_WESEWVED			0x0
#define WWSW_WSC_UPPEW_SUBCHANNEW		0x1
#define WWSW_WSC_WOWEW_SUBCHANNEW		0x2
#define WWSW_WSC_DUPWICATE_MODE			0x3

#define USE_SHOWT_G1				BIT(20)

#define _AGGWMT_MCS0(x)				((x) & 0xF)
#define _AGGWMT_MCS1(x)				(((x) & 0xF) << 4)
#define _AGGWMT_MCS2(x)				(((x) & 0xF) << 8)
#define _AGGWMT_MCS3(x)				(((x) & 0xF) << 12)
#define _AGGWMT_MCS4(x)				(((x) & 0xF) << 16)
#define _AGGWMT_MCS5(x)				(((x) & 0xF) << 20)
#define _AGGWMT_MCS6(x)				(((x) & 0xF) << 24)
#define _AGGWMT_MCS7(x)				(((x) & 0xF) << 28)

#define	WETWY_WIMIT_SHOWT_SHIFT		8
#define	WETWY_WIMIT_WONG_SHIFT		0

#define _DAWF_WC1(x)			((x) & 0x1F)
#define _DAWF_WC2(x)			(((x) & 0x1F) << 8)
#define _DAWF_WC3(x)			(((x) & 0x1F) << 16)
#define _DAWF_WC4(x)			(((x) & 0x1F) << 24)
#define _DAWF_WC5(x)			((x) & 0x1F)
#define _DAWF_WC6(x)			(((x) & 0x1F) << 8)
#define _DAWF_WC7(x)			(((x) & 0x1F) << 16)
#define _DAWF_WC8(x)			(((x) & 0x1F) << 24)

#define _WAWF_WC1(x)			((x) & 0x1F)
#define _WAWF_WC2(x)			(((x) & 0x1F) << 8)
#define _WAWF_WC3(x)			(((x) & 0x1F) << 16)
#define _WAWF_WC4(x)			(((x) & 0x1F) << 24)
#define _WAWF_WC5(x)			((x) & 0x1F)
#define _WAWF_WC6(x)			(((x) & 0x1F) << 8)
#define _WAWF_WC7(x)			(((x) & 0x1F) << 16)
#define _WAWF_WC8(x)			(((x) & 0x1F) << 24)

#define AC_PAWAM_TXOP_WIMIT_OFFSET	16
#define AC_PAWAM_ECW_MAX_OFFSET		12
#define AC_PAWAM_ECW_MIN_OFFSET		8
#define AC_PAWAM_AIFS_OFFSET		0

#define _AIFS(x)			(x)
#define _ECW_MAX_MIN(x)			((x) << 8)
#define _TXOP_WIMIT(x)			((x) << 16)

#define _BCNIFS(x)			((x) & 0xFF)
#define _BCNECW(x)			((((x) & 0xF)) << 8)

#define _WWW(x)				((x) & 0x3F)
#define _SWW(x)				(((x) & 0x3F) << 8)

#define _SIFS_CCK_CTX(x)		((x) & 0xFF)
#define _SIFS_CCK_TWX(x)		(((x) & 0xFF) << 8)

#define _SIFS_OFDM_CTX(x)		((x) & 0xFF)
#define _SIFS_OFDM_TWX(x)		(((x) & 0xFF) << 8)

#define _TBTT_PWOHIBIT_HOWD(x)		(((x) & 0xFF) << 8)

#define DIS_EDCA_CNT_DWN		BIT(11)

#define EN_MBSSID			BIT(1)
#define EN_TXBCN_WPT			BIT(2)
#define	EN_BCN_FUNCTION			BIT(3)

#define TSFTW_WST			BIT(0)
#define TSFTW1_WST			BIT(1)

#define STOP_BCNQ			BIT(6)

#define	DIS_TSF_UDT0_NOWMAW_CHIP	BIT(4)
#define	DIS_TSF_UDT0_TEST_CHIP		BIT(5)

#define	ACMHW_HWEN			BIT(0)
#define	ACMHW_BEQEN			BIT(1)
#define	ACMHW_VIQEN			BIT(2)
#define	ACMHW_VOQEN			BIT(3)
#define	ACMHW_BEQSTATUS			BIT(4)
#define	ACMHW_VIQSTATUS			BIT(5)
#define	ACMHW_VOQSTATUS			BIT(6)

#define APSDOFF				BIT(6)
#define APSDOFF_STATUS			BIT(7)

#define BW_20MHZ			BIT(2)

#define WATE_BITMAP_AWW			0xFFFFF

#define WATE_WWSW_CCK_ONWY_1M		0xFFFF1

#define TSFWST				BIT(0)
#define DIS_GCWK			BIT(1)
#define PAD_SEW				BIT(2)
#define PWW_ST				BIT(6)
#define PWWBIT_OW_EN			BIT(7)
#define ACWC				BIT(8)
#define CFENDFOWM			BIT(9)
#define ICV				BIT(10)

#define AAP				BIT(0)
#define APM				BIT(1)
#define AM				BIT(2)
#define AB				BIT(3)
#define ADD3				BIT(4)
#define APWWMGT				BIT(5)
#define CBSSID				BIT(6)
#define CBSSID_DATA			BIT(6)
#define CBSSID_BCN			BIT(7)
#define ACWC32				BIT(8)
#define AICV				BIT(9)
#define ADF				BIT(11)
#define ACF				BIT(12)
#define AMF				BIT(13)
#define HTC_WOC_CTWW			BIT(14)
#define UC_DATA_EN			BIT(16)
#define BM_DATA_EN			BIT(17)
#define MFBEN				BIT(22)
#define WSIGEN				BIT(23)
#define ENMBID				BIT(24)
#define APP_BASSN			BIT(27)
#define APP_PHYSTS			BIT(28)
#define APP_ICV				BIT(29)
#define APP_MIC				BIT(30)
#define APP_FCS				BIT(31)

#define _MIN_SPACE(x)			((x) & 0x7)
#define _SHOWT_GI_PADDING(x)		(((x) & 0x1F) << 3)

#define WXEWW_TYPE_OFDM_PPDU		0
#define WXEWW_TYPE_OFDM_FAWSE_AWAWM	1
#define	WXEWW_TYPE_OFDM_MPDU_OK		2
#define WXEWW_TYPE_OFDM_MPDU_FAIW	3
#define WXEWW_TYPE_CCK_PPDU		4
#define WXEWW_TYPE_CCK_FAWSE_AWAWM	5
#define WXEWW_TYPE_CCK_MPDU_OK		6
#define WXEWW_TYPE_CCK_MPDU_FAIW	7
#define WXEWW_TYPE_HT_PPDU		8
#define WXEWW_TYPE_HT_FAWSE_AWAWM	9
#define WXEWW_TYPE_HT_MPDU_TOTAW	10
#define WXEWW_TYPE_HT_MPDU_OK		11
#define WXEWW_TYPE_HT_MPDU_FAIW		12
#define WXEWW_TYPE_WX_FUWW_DWOP		15

#define WXEWW_COUNTEW_MASK		0xFFFFF
#define WXEWW_WPT_WST			BIT(27)
#define _WXEWW_WPT_SEW(type)		((type) << 28)

#define	SCW_TXUSEDK			BIT(0)
#define	SCW_WXUSEDK			BIT(1)
#define	SCW_TXENCENABWE			BIT(2)
#define	SCW_WXDECENABWE			BIT(3)
#define	SCW_SKBYA2			BIT(4)
#define	SCW_NOSKMC			BIT(5)
#define SCW_TXBCUSEDK			BIT(6)
#define SCW_WXBCUSEDK			BIT(7)

#define XCWK_VWD			BIT(0)
#define ACWK_VWD			BIT(1)
#define UCWK_VWD			BIT(2)
#define PCWK_VWD			BIT(3)
#define PCIWSTB				BIT(4)
#define V15_VWD				BIT(5)
#define TWP_B15V_EN			BIT(7)
#define SIC_IDWE			BIT(8)
#define BD_MAC2				BIT(9)
#define BD_MAC1				BIT(10)
#define IC_MACPHY_MODE			BIT(11)
#define BT_FUNC				BIT(16)
#define VENDOW_ID			BIT(19)
#define PAD_HWPD_IDN			BIT(22)
#define TWP_VAUX_EN			BIT(23)
#define TWP_BT_EN			BIT(24)
#define BD_PKG_SEW			BIT(25)
#define BD_HCI_SEW			BIT(26)
#define TYPE_ID				BIT(27)

#define USB_IS_HIGH_SPEED		0
#define USB_IS_FUWW_SPEED		1
#define USB_SPEED_MASK			BIT(5)

#define USB_NOWMAW_SIE_EP_MASK		0xF
#define USB_NOWMAW_SIE_EP_SHIFT		4

#define USB_TEST_EP_MASK		0x30
#define USB_TEST_EP_SHIFT		4

#define USB_AGG_EN			BIT(3)

#define MAC_ADDW_WEN			6
#define WAST_ENTWY_OF_TX_PKT_BUFFEW	255

#define POWWING_WWT_THWESHOWD		20
#define POWWING_WEADY_TIMEOUT_COUNT	3000

#define	MAX_MSS_DENSITY_2T		0x13
#define	MAX_MSS_DENSITY_1T		0x0A

#define EPWOM_CMD_OPEWATING_MODE_MASK	((1<<7)|(1<<6))
#define EPWOM_CMD_CONFIG		0x3
#define EPWOM_CMD_WOAD			1

#define	HWSET_MAX_SIZE_92S		HWSET_MAX_SIZE

#define	HAW_8192C_HW_GPIO_WPS_BIT	BIT(2)

#define WA_WSSIWWITE_8821A		0xc90
#define WB_WSSIWWITE_8821A		0xe90

#define	WA_PIWEAD_8821A			0xd04
#define	WB_PIWEAD_8821A			0xd44
#define	WA_SIWEAD_8821A			0xd08
#define	WB_SIWEAD_8821A			0xd48

#define	WPMAC_WESET			0x100
#define	WPMAC_TXSTAWT			0x104
#define	WPMAC_TXWEGACYSIG		0x108
#define	WPMAC_TXHTSIG1			0x10c
#define	WPMAC_TXHTSIG2			0x110
#define	WPMAC_PHYDEBUG			0x114
#define	WPMAC_TXPACKETNUM		0x118
#define	WPMAC_TXIDWE			0x11c
#define	WPMAC_TXMACHEADEW0		0x120
#define	WPMAC_TXMACHEADEW1		0x124
#define	WPMAC_TXMACHEADEW2		0x128
#define	WPMAC_TXMACHEADEW3		0x12c
#define	WPMAC_TXMACHEADEW4		0x130
#define	WPMAC_TXMACHEADEW5		0x134
#define	WPMAC_TXDADATYPE		0x138
#define	WPMAC_TXWANDOMSEED		0x13c
#define	WPMAC_CCKPWCPPWEAMBWE		0x140
#define	WPMAC_CCKPWCPHEADEW		0x144
#define	WPMAC_CCKCWC16			0x148
#define	WPMAC_OFDMWXCWC32OK		0x170
#define	WPMAC_OFDMWXCWC32EW		0x174
#define	WPMAC_OFDMWXPAWITYEW		0x178
#define	WPMAC_OFDMWXCWC8EW		0x17c
#define	WPMAC_CCKCWXWC16EW		0x180
#define	WPMAC_CCKCWXWC32EW		0x184
#define	WPMAC_CCKCWXWC32OK		0x188
#define	WPMAC_TXSTATUS			0x18c

#define	WFPGA0_WFMOD			0x800

#define	WFPGA0_TXINFO			0x804
#define	WFPGA0_PSDFUNCTION		0x808

#define	WFPGA0_TXGAINSTAGE		0x80c

#define	WFPGA0_WFTIMING1		0x810
#define	WFPGA0_WFTIMING2		0x814

#define	WFPGA0_XA_HSSIPAWAMETEW1	0x820
#define	WFPGA0_XA_HSSIPAWAMETEW2	0x824
#define	WFPGA0_XB_HSSIPAWAMETEW1	0x828
#define	WFPGA0_XB_HSSIPAWAMETEW2	0x82c
#define	WCCAONSEC			0x838

#define	WFPGA0_XA_WSSIPAWAMETEW		0x840
#define	WFPGA0_XB_WSSIPAWAMETEW		0x844
#define	WW1PEAKTH			0x848

#define	WFPGA0_WFWAKEUPPAWAMETEW	0x850
#define	WFPGA0_WFSWEEPUPPAWAMETEW	0x854

#define	WFPGA0_XAB_SWITCHCONTWOW	0x858
#define	WFPGA0_XCD_SWITCHCONTWOW	0x85c

#define	WFPGA0_XA_WFINTEWFACEOE		0x860
#define WFC_AWEA			0x860
#define	WFPGA0_XB_WFINTEWFACEOE		0x864

#define	WFPGA0_XAB_WFINTEWFACESW	0x870
#define	WFPGA0_XCD_WFINTEWFACESW	0x874

#define	WFPGA0_XAB_WFPAWAMETEW		0x878
#define	WFPGA0_XCD_WFPAWAMETEW		0x87c

#define	WFPGA0_ANAWOGPAWAMETEW1		0x880
#define	WFPGA0_ANAWOGPAWAMETEW2		0x884
#define	WFPGA0_ANAWOGPAWAMETEW3		0x888
#define	WFPGA0_ANAWOGPAWAMETEW4		0x88c

#define	WFPGA0_XA_WSSIWEADBACK		0x8a0
#define	WFPGA0_XB_WSSIWEADBACK		0x8a4
#define	WFPGA0_XC_WSSIWEADBACK		0x8a8
#define WWFMOD				0x8ac
#define	WHSSIWEAD_8821AE		0x8b0

#define	WFPGA0_PSDWEPOWT		0x8b4
#define	TWANSCEIVEA_HSPI_WEADBACK	0x8b8
#define	TWANSCEIVEB_HSPI_WEADBACK	0x8bc
#define WADC_BUF_CWK			0x8c4
#define	WFPGA0_XAB_WFINTEWFACEWB	0x8e0
#define	WFPGA0_XCD_WFINTEWFACEWB	0x8e4

#define	WFPGA1_WFMOD			0x900

#define	WFPGA1_TXBWOCK			0x904
#define	WFPGA1_DEBUGSEWECT		0x908
#define	WFPGA1_TXINFO			0x90c

#define	WCCK_SYSTEM			0xa00
#define	BCCK_SYSTEM			0x10

#define	WCCK0_AFESETTING		0xa04
#define	WCCK0_CCA			0xa08

#define	WCCK0_WXAGC1			0xa0c
#define	WCCK0_WXAGC2			0xa10

#define	WCCK0_WXHP			0xa14

#define	WCCK0_DSPPAWAMETEW1		0xa18
#define	WCCK0_DSPPAWAMETEW2		0xa1c

#define	WCCK0_TXFIWTEW1			0xa20
#define	WCCK0_TXFIWTEW2			0xa24
#define	WCCK0_DEBUGPOWT			0xa28
#define	WCCK0_FAWSEAWAWMWEPOWT		0xa2c
#define	WCCK0_TWSSIWEPOWT		0xa50
#define	WCCK0_WXWEPOWT			0xa54
#define	WCCK0_FACOUNTEWWOWEW		0xa5c
#define	WCCK0_FACOUNTEWUPPEW		0xa58
#define	WCCK0_CCA_CNT			0xa60

/* PageB(0XB00) */
#define	WPDP_ANTA			0xb00
#define	WPDP_ANTA_4			0xb04
#define	WPDP_ANTA_8			0xb08
#define	WPDP_ANTA_C			0xb0c
#define	WPDP_ANTA_10			0xb10
#define	WPDP_ANTA_14			0xb14
#define	WPDP_ANTA_18			0xb18
#define	WPDP_ANTA_1C			0xb1c
#define	WPDP_ANTA_20			0xb20
#define	WPDP_ANTA_24			0xb24

#define	WCONFIG_PMPD_ANTA		0xb28
#define	WCONFIG_WAM64x16		0xb2c

#define	WBNDA				0xb30
#define	WHSSIPAW			0xb34

#define	WCONFIG_ANTA			0xb68
#define	WCONFIG_ANTB			0xb6c

#define	WPDP_ANTB			0xb70
#define	WPDP_ANTB_4			0xb74
#define	WPDP_ANTB_8			0xb78
#define	WPDP_ANTB_C			0xb7c
#define	WPDP_ANTB_10			0xb80
#define	WPDP_ANTB_14			0xb84
#define	WPDP_ANTB_18			0xb88
#define	WPDP_ANTB_1C			0xb8c
#define	WPDP_ANTB_20			0xb90
#define	WPDP_ANTB_24			0xb94

#define	WCONFIG_PMPD_ANTB		0xb98

#define	WBNDB				0xba0

#define	WAPK				0xbd8
#define	WPM_WX0_ANTA			0xbdc
#define	WPM_WX1_ANTA			0xbe0
#define	WPM_WX2_ANTA			0xbe4
#define	WPM_WX3_ANTA			0xbe8
#define	WPM_WX0_ANTB			0xbec
#define	WPM_WX1_ANTB			0xbf0
#define	WPM_WX2_ANTB			0xbf4
#define	WPM_WX3_ANTB			0xbf8

/*WSSI Dump*/
#define		WA_WSSI_DUMP		0XBF0
#define		WB_WSSI_DUMP		0XBF1
#define		WS1_WX_EVM_DUMP		0XBF4
#define		WS2_WX_EVM_DUMP		0XBF5
#define		WA_WX_SNW_DUMP		0XBF6
#define		WB_WX_SNW_DUMP		0XBF7
#define		WA_CFO_SHOWT_DUMP	0XBF8
#define		WB_CFO_SHOWT_DUMP	0XBFA
#define		WA_CFO_WONG_DUMP	0XBEC
#define		WB_CFO_WONG_DUMP	0XBEE

/*Page C*/
#define	WOFDM0_WSTF			0xc00

#define	WOFDM0_TWXPATHENABWE		0xc04
#define	WOFDM0_TWMUXPAW			0xc08
#define	WOFDM0_TWSWISOWATION		0xc0c

#define	WOFDM0_XAWXAFE			0xc10
#define	WOFDM0_XAWXIQIMBAWANCE		0xc14
#define	WOFDM0_XBWXAFE			0xc18
#define	WOFDM0_XBWXIQIMBAWANCE		0xc1c
#define	WOFDM0_XCWXAFE			0xc20
#define	WOFDM0_XCWXIQIMBANWANCE		0xc24
#define	WOFDM0_XDWXAFE			0xc28
#define	WOFDM0_XDWXIQIMBAWANCE		0xc2c

#define	WOFDM0_WXDETECTOW1		0xc30
#define	WOFDM0_WXDETECTOW2		0xc34
#define	WOFDM0_WXDETECTOW3		0xc38
#define	WOFDM0_WXDETECTOW4		0xc3c

#define	WOFDM0_WXDSP			0xc40
#define	WOFDM0_CFOANDDAGC		0xc44
#define	WOFDM0_CCADWOPTHWESHOWD		0xc48
#define	WOFDM0_ECCATHWESHOWD		0xc4c

#define	WOFDM0_XAAGCCOWE1		0xc50
#define	WOFDM0_XAAGCCOWE2		0xc54
#define	WOFDM0_XBAGCCOWE1		0xc58
#define	WOFDM0_XBAGCCOWE2		0xc5c
#define	WOFDM0_XCAGCCOWE1		0xc60
#define	WOFDM0_XCAGCCOWE2		0xc64
#define	WOFDM0_XDAGCCOWE1		0xc68
#define	WOFDM0_XDAGCCOWE2		0xc6c

#define	WOFDM0_AGCPAWAMETEW1		0xc70
#define	WOFDM0_AGCPAWAMETEW2		0xc74
#define	WOFDM0_AGCWSSITABWE		0xc78
#define	WOFDM0_HTSTFAGC			0xc7c

#define	WOFDM0_XATXIQIMBAWANCE		0xc80
#define	WOFDM0_XATXAFE			0xc84
#define	WOFDM0_XBTXIQIMBAWANCE		0xc88
#define	WOFDM0_XBTXAFE			0xc8c
#define	WOFDM0_XCTXIQIMBAWANCE		0xc90
#define	WOFDM0_XCTXAFE			0xc94
#define	WOFDM0_XDTXIQIMBAWANCE		0xc98
#define	WOFDM0_XDTXAFE			0xc9c

#define WOFDM0_WXIQEXTANTA		0xca0
#define	WOFDM0_TXCOEFF1			0xca4
#define	WOFDM0_TXCOEFF2			0xca8
#define	WOFDM0_TXCOEFF3			0xcac
#define	WOFDM0_TXCOEFF4			0xcb0
#define	WOFDM0_TXCOEFF5			0xcb4
#define	WOFDM0_TXCOEFF6			0xcb8

/*Path_A WFE cotwow */
#define	WA_WFE_CTWW_8812		0xcb8
/*Path_B WFE contwow*/
#define	WB_WFE_CTWW_8812		0xeb8

#define	WOFDM0_WXHPPAWAMETEW		0xce0
#define	WOFDM0_TXPSEUDONOISEWGT		0xce4
#define	WOFDM0_FWAMESYNC		0xcf0
#define	WOFDM0_DFSWEPOWT		0xcf4

#define	WOFDM1_WSTF			0xd00
#define	WOFDM1_TWXPATHENABWE		0xd04

#define	WOFDM1_CF0			0xd08
#define	WOFDM1_CSI1			0xd10
#define	WOFDM1_SBD			0xd14
#define	WOFDM1_CSI2			0xd18
#define	WOFDM1_CFOTWACKING		0xd2c
#define	WOFDM1_TWXMESAUWE1		0xd34
#define	WOFDM1_INTFDET			0xd3c
#define	WOFDM1_PSEUDONOISESTATEAB	0xd50
#define	WOFDM1_PSEUDONOISESTATECD	0xd54
#define	WOFDM1_WXPSEUDONOISEWGT		0xd58

#define	WOFDM_PHYCOUNTEW1		0xda0
#define	WOFDM_PHYCOUNTEW2		0xda4
#define	WOFDM_PHYCOUNTEW3		0xda8

#define	WOFDM_SHOWTCFOAB		0xdac
#define	WOFDM_SHOWTCFOCD		0xdb0
#define	WOFDM_WONGCFOAB			0xdb4
#define	WOFDM_WONGCFOCD			0xdb8
#define	WOFDM_TAIWCF0AB			0xdbc
#define	WOFDM_TAIWCF0CD			0xdc0
#define	WOFDM_PWMEASUWE1		0xdc4
#define	WOFDM_PWMEASUWE2		0xdc8
#define	WOFDM_BWWEPOWT			0xdcc
#define	WOFDM_AGCWEPOWT			0xdd0
#define	WOFDM_WXSNW			0xdd4
#define	WOFDM_WXEVMCSI			0xdd8
#define	WOFDM_SIGWEPOWT			0xddc

#define WTXAGC_A_CCK11_CCK1		0xc20
#define WTXAGC_A_OFDM18_OFDM6		0xc24
#define WTXAGC_A_OFDM54_OFDM24		0xc28
#define WTXAGC_A_MCS03_MCS00		0xc2c
#define WTXAGC_A_MCS07_MCS04		0xc30
#define WTXAGC_A_MCS11_MCS08		0xc34
#define WTXAGC_A_MCS15_MCS12		0xc38
#define WTXAGC_A_NSS1INDEX3_NSS1INDEX0	0xc3c
#define	WTXAGC_A_NSS1INDEX7_NSS1INDEX4	0xc40
#define	WTXAGC_A_NSS2INDEX1_NSS1INDEX8	0xc44
#define	WTXAGC_A_NSS2INDEX5_NSS2INDEX2	0xc48
#define	WTXAGC_A_NSS2INDEX9_NSS2INDEX6	0xc4c
#define	WTXAGC_B_CCK11_CCK1		0xe20
#define	WTXAGC_B_OFDM18_OFDM6		0xe24
#define	WTXAGC_B_OFDM54_OFDM24		0xe28
#define	WTXAGC_B_MCS03_MCS00		0xe2c
#define	WTXAGC_B_MCS07_MCS04		0xe30
#define	WTXAGC_B_MCS11_MCS08		0xe34
#define	WTXAGC_B_MCS15_MCS12		0xe38
#define	WTXAGC_B_NSS1INDEX3_NSS1INDEX0	0xe3c
#define	WTXAGC_B_NSS1INDEX7_NSS1INDEX4	0xe40
#define	WTXAGC_B_NSS2INDEX1_NSS1INDEX8	0xe44
#define	WTXAGC_B_NSS2INDEX5_NSS2INDEX2	0xe48
#define	WTXAGC_B_NSS2INDEX9_NSS2INDEX6	0xe4c

#define	WA_TXPWWTWAING			0xc54
#define	WB_TXPWWTWAING			0xe54

#define	WFPGA0_IQK			0xe28
#define	WTX_IQK_TONE_A			0xe30
#define	WWX_IQK_TONE_A			0xe34
#define	WTX_IQK_PI_A			0xe38
#define	WWX_IQK_PI_A			0xe3c

#define	WTX_IQK				0xe40
#define	WWX_IQK				0xe44
#define	WIQK_AGC_PTS			0xe48
#define	WIQK_AGC_WSP			0xe4c
#define	WTX_IQK_TONE_B			0xe50
#define	WWX_IQK_TONE_B			0xe54
#define	WTX_IQK_PI_B			0xe58
#define	WWX_IQK_PI_B			0xe5c
#define	WIQK_AGC_CONT			0xe60

#define	WBWUE_TOOTH			0xe6c
#define	WWX_WAIT_CCA			0xe70
#define	WTX_CCK_WFON			0xe74
#define	WTX_CCK_BBON			0xe78
#define	WTX_OFDM_WFON			0xe7c
#define	WTX_OFDM_BBON			0xe80
#define	WTX_TO_WX			0xe84
#define	WTX_TO_TX			0xe88
#define	WWX_CCK				0xe8c

#define	WTX_POWEW_BEFOWE_IQK_A		0xe94
#define	WTX_POWEW_AFTEW_IQK_A		0xe9c

#define	WWX_POWEW_BEFOWE_IQK_A		0xea0
#define	WWX_POWEW_BEFOWE_IQK_A_2	0xea4
#define	WWX_POWEW_AFTEW_IQK_A		0xea8
#define	WWX_POWEW_AFTEW_IQK_A_2		0xeac

#define	WTX_POWEW_BEFOWE_IQK_B		0xeb4
#define	WTX_POWEW_AFTEW_IQK_B		0xebc

#define	WWX_POEW_BEFOWE_IQK_B		0xec0
#define	WWX_POEW_BEFOWE_IQK_B_2		0xec4
#define	WWX_POWEW_AFTEW_IQK_B		0xec8
#define	WWX_POWEW_AFTEW_IQK_B_2		0xecc

#define	WWX_OFDM			0xed0
#define	WWX_WAIT_WIFS			0xed4
#define	WWX_TO_WX			0xed8
#define	WSTANDBY			0xedc
#define	WSWEEP				0xee0
#define	WPMPD_ANAEN			0xeec

#define	WZEBWA1_HSSIENABWE		0x0
#define	WZEBWA1_TWXENABWE1		0x1
#define	WZEBWA1_TWXENABWE2		0x2
#define	WZEBWA1_AGC			0x4
#define	WZEBWA1_CHAWGEPUMP		0x5
#define	WZEBWA1_CHANNEW			0x7

#define	WZEBWA1_TXGAIN			0x8
#define	WZEBWA1_TXWPF			0x9
#define	WZEBWA1_WXWPF			0xb
#define	WZEBWA1_WXHPFCOWNEW		0xc

#define	WGWOBAWCTWW			0
#define	WWTW8256_TXWPF			19
#define	WWTW8256_WXWPF			11
#define	WWTW8258_TXWPF			0x11
#define	WWTW8258_WXWPF			0x13
#define	WWTW8258_WSSIWPF		0xa

#define	WF_AC				0x00

#define	WF_IQADJ_G1			0x01
#define	WF_IQADJ_G2			0x02
#define	WF_POW_TWSW			0x05

#define	WF_GAIN_WX			0x06
#define	WF_GAIN_TX			0x07

#define	WF_TXM_IDAC			0x08
#define	WF_BS_IQGEN			0x0F

#define	WF_MODE1			0x10
#define	WF_MODE2			0x11

#define	WF_WX_AGC_HP			0x12
#define	WF_TX_AGC			0x13
#define	WF_BIAS				0x14
#define	WF_IPA				0x15
#define	WF_POW_ABIWITY			0x17
#define	WF_MODE_AG			0x18
#define	WWFCHANNEW			0x18
#define	WF_CHNWBW			0x18
#define	WF_TOP				0x19

#define	WF_WX_G1			0x1A
#define	WF_WX_G2			0x1B

#define	WF_WX_BB2			0x1C
#define	WF_WX_BB1			0x1D

#define	WF_WCK1				0x1E
#define	WF_WCK2				0x1F

#define	WF_TX_G1			0x20
#define	WF_TX_G2			0x21
#define	WF_TX_G3			0x22

#define	WF_TX_BB1			0x23
#define	WF_T_METEW			0x24
#define	WF_T_METEW_88E			0x42
#define  WF_T_METEW_8812A		0x42

#define	WF_SYN_G1			0x25
#define	WF_SYN_G2			0x26
#define	WF_SYN_G3			0x27
#define	WF_SYN_G4			0x28
#define	WF_SYN_G5			0x29
#define	WF_SYN_G6			0x2A
#define	WF_SYN_G7			0x2B
#define	WF_SYN_G8			0x2C

#define	WF_WCK_OS			0x30
#define	WF_TXPA_G1			0x31
#define	WF_TXPA_G2			0x32
#define	WF_TXPA_G3			0x33

#define	WF_TX_BIAS_A			0x35
#define	WF_TX_BIAS_D			0x36
#define	WF_WOBF_9			0x38
#define	WF_WXWF_A3			0x3C
#define	WF_TWSW				0x3F

#define	WF_TXWF_A2			0x41
#define	WF_TXPA_G4			0x46
#define	WF_TXPA_A4			0x4B

#define WF_APK				0x63

#define	WF_WE_WUT			0xEF

#define	BBBWESETB			0x100
#define	BGWOBAWWESETB			0x200
#define	BOFDMTXSTAWT			0x4
#define	BCCKTXSTAWT			0x8
#define	BCWC32DEBUG			0x100
#define	BPMACWOOPBACK			0x10
#define	BTXWSIG				0xffffff
#define	BOFDMTXWATE			0xf
#define	BOFDMTXWESEWVED			0x10
#define	BOFDMTXWENGTH			0x1ffe0
#define	BOFDMTXPAWITY			0x20000
#define	BTXHTSIG1			0xffffff
#define	BTXHTMCSWATE			0x7f
#define	BTXHTBW				0x80
#define	BTXHTWENGTH			0xffff00
#define	BTXHTSIG2			0xffffff
#define	BTXHTSMOOTHING			0x1
#define	BTXHTSOUNDING			0x2
#define	BTXHTWESEWVED			0x4
#define	BTXHTAGGWEATION			0x8
#define	BTXHTSTBC			0x30
#define	BTXHTADVANCECODING		0x40
#define	BTXHTSHOWTGI			0x80
#define	BTXHTNUMBEWHT_WTF		0x300
#define	BTXHTCWC8			0x3fc00
#define	BCOUNTEWWESET			0x10000
#define	BNUMOFOFDMTX			0xffff
#define	BNUMOFCCKTX			0xffff0000
#define	BTXIDWEINTEWVAW			0xffff
#define	BOFDMSEWVICE			0xffff0000
#define	BTXMACHEADEW			0xffffffff
#define	BTXDATAINIT			0xff
#define	BTXHTMODE			0x100
#define	BTXDATATYPE			0x30000
#define	BTXWANDOMSEED			0xffffffff
#define	BCCKTXPWEAMBWE			0x1
#define	BCCKTXSFD			0xffff0000
#define	BCCKTXSIG			0xff
#define	BCCKTXSEWVICE			0xff00
#define	BCCKWENGTHEXT			0x8000
#define	BCCKTXWENGHT			0xffff0000
#define	BCCKTXCWC16			0xffff
#define	BCCKTXSTATUS			0x1
#define	BOFDMTXSTATUS			0x2
#define IS_BB_WEG_OFFSET_92S(__offset)	\
	((__offset >= 0x800) && (__offset <= 0xfff))

#define	BWFMOD				0x1
#define	BJAPANMODE			0x2
#define	BCCKTXSC			0x30
/* Bwock & Path enabwe*/
#define WOFDMCCKEN			0x808
#define	BCCKEN				0x10000000
#define	BOFDMEN				0x20000000
/* Wx antenna*/
#define	WWXPATH				0x808
#define	BWXPATH				0xff
/* Tx antenna*/
#define	WTXPATH				0x80c
#define	BTXPATH				0x0fffffff
/* fow cck wx path sewection*/
#define	WCCK_WX				0xa04
#define	BCCK_WX				0x0c000000
/* Use WSIG fow VHT wength*/
#define	WVHTWEN_USE_WSIG		0x8c3

#define	BOFDMWXADCPHASE			0x10000
#define	BOFDMTXDACPHASE			0x40000
#define	BXATXAGC			0x3f

#define	BXBTXAGC			0xf00
#define	BXCTXAGC			0xf000
#define	BXDTXAGC			0xf0000

#define	BPASTAWT			0xf0000000
#define	BTWSTAWT			0x00f00000
#define	BWFSTAWT			0x0000f000
#define	BBBSTAWT			0x000000f0
#define	BBBCCKSTAWT			0x0000000f
#define	BPAEND				0xf
#define	BTWEND				0x0f000000
#define	BWFEND				0x000f0000
#define	BCCAMASK			0x000000f0
#define	BW2WCCAMASK			0x00000f00
#define	BHSSI_W2TDEWAY			0xf8000000
#define	BHSSI_T2WDEWAY			0xf80000
#define	BCONTXHSSI			0x400
#define	BIGFWOMCCK			0x200
#define	BAGCADDWESS			0x3f
#define	BWXHPTX				0x7000
#define	BWXHP2WX			0x38000
#define	BWXHPCCKINI			0xc0000
#define	BAGCTXCODE			0xc00000
#define	BAGCWXCODE			0x300000

#define	B3WIWEDATAWENGTH		0x800
#define	B3WIWEADDWEAAWENGTH		0x400

#define	B3WIWEWFPOWEWDOWN		0x1
#define	B5GPAPEPOWAWITY			0x40000000
#define	B2GPAPEPOWAWITY			0x80000000
#define	BWFSW_TXDEFAUWTANT		0x3
#define	BWFSW_TXOPTIONANT		0x30
#define	BWFSW_WXDEFAUWTANT		0x300
#define	BWFSW_WXOPTIONANT		0x3000
#define	BWFSI_3WIWEDATA			0x1
#define	BWFSI_3WIWECWOCK		0x2
#define	BWFSI_3WIWEWOAD			0x4
#define	BWFSI_3WIWEWW			0x8
#define	BWFSI_3WIWE			0xf

#define	BWFSI_WFENV			0x10

#define	BWFSI_TWSW			0x20
#define	BWFSI_TWSWB			0x40
#define	BWFSI_ANTSW			0x100
#define	BWFSI_ANTSWB			0x200
#define	BWFSI_PAPE			0x400
#define	BWFSI_PAPE5G			0x800
#define	BBANDSEWECT			0x1
#define	BHTSIG2_GI			0x80
#define	BHTSIG2_SMOOTHING		0x01
#define	BHTSIG2_SOUNDING		0x02
#define	BHTSIG2_AGGWEATON		0x08
#define	BHTSIG2_STBC			0x30
#define	BHTSIG2_ADVCODING		0x40
#define	BHTSIG2_NUMOFHTWTF		0x300
#define	BHTSIG2_CWC8			0x3fc
#define	BHTSIG1_MCS			0x7f
#define	BHTSIG1_BANDWIDTH		0x80
#define	BHTSIG1_HTWENGTH		0xffff
#define	BWSIG_WATE			0xf
#define	BWSIG_WESEWVED			0x10
#define	BWSIG_WENGTH			0x1fffe
#define	BWSIG_PAWITY			0x20
#define	BCCKWXPHASE			0x4

#define	BWSSIWEADADDWESS		0x7f800000
#define	BWSSIWEADEDGE			0x80000000

#define	BWSSIWEADBACKDATA		0xfffff

#define	BWSSIWEADOKFWAG			0x1000
#define	BCCKSAMPWEWATE			0x8
#define	BWEGUWATOW0STANDBY		0x1
#define	BWEGUWATOWPWWSTANDBY		0x2
#define	BWEGUWATOW1STANDBY		0x4
#define	BPWWPOWEWUP			0x8
#define	BDPWWPOWEWUP			0x10
#define	BDA10POWEWUP			0x20
#define	BAD7POWEWUP			0x200
#define	BDA6POWEWUP			0x2000
#define	BXTAWPOWEWUP			0x4000
#define	B40MDCWKPOWEWUP			0x8000
#define	BDA6DEBUGMODE			0x20000
#define	BDA6SWING			0x380000

#define	BADCWKPHASE			0x4000000
#define	B80MCWKDEWAY			0x18000000
#define	BAFEWATCHDOGENABWE		0x20000000

#define	BXTAWCAP01			0xc0000000
#define	BXTAWCAP23			0x3
#define	BXTAWCAP92X			0x0f000000
#define BXTAWCAP			0x0f000000

#define	BINTDIFCWKENABWE		0x400
#define	BEXTSIGCWKENABWE		0x800
#define	BBANDGAP_MBIAS_POWEWUP		0x10000
#define	BAD11SH_GAIN			0xc0000
#define	BAD11NPUT_WANGE			0x700000
#define	BAD110P_CUWWENT			0x3800000
#define	BWPATH_WOOPBACK			0x4000000
#define	BQPATH_WOOPBACK			0x8000000
#define	BAFE_WOOPBACK			0x10000000
#define	BDA10_SWING			0x7e0
#define	BDA10_WEVEWSE			0x800
#define	BDA_CWK_SOUWCE			0x1000
#define	BDA7INPUT_WANGE			0x6000
#define	BDA7_GAIN			0x38000
#define	BDA7OUTPUT_CM_MODE		0x40000
#define	BDA7INPUT_CM_MODE		0x380000
#define	BDA7CUWWENT			0xc00000
#define	BWEGUWATOW_ADJUST		0x7000000
#define	BAD11POWEWUP_ATTX		0x1
#define	BDA10PS_ATTX			0x10
#define	BAD11POWEWUP_ATWX		0x100
#define	BDA10PS_ATWX			0x1000
#define	BCCKWX_AGC_FOWMAT		0x200
#define	BPSDFFT_SAMPWE_POINT		0xc000
#define	BPSD_AVEWAGE_NUM		0x3000
#define	BIQPATH_CONTWOW			0xc00
#define	BPSD_FWEQ			0x3ff
#define	BPSD_ANTENNA_PATH		0x30
#define	BPSD_IQ_SWITCH			0x40
#define	BPSD_WX_TWIGGEW			0x400000
#define	BPSD_TX_TWIGGEW			0x80000000
#define	BPSD_SINE_TONE_SCAWE		0x7f000000
#define	BPSD_WEPOWT			0xffff

#define	BOFDM_TXSC			0x30000000
#define	BCCK_TXON			0x1
#define	BOFDM_TXON			0x2
#define	BDEBUG_PAGE			0xfff
#define	BDEBUG_ITEM			0xff
#define	BANTW				0x10
#define	BANT_NONHT			0x100
#define	BANT_HT1			0x1000
#define	BANT_HT2			0x10000
#define	BANT_HT1S1			0x100000
#define	BANT_NONHTS1			0x1000000

#define	BCCK_BBMODE			0x3
#define	BCCK_TXPOWEWSAVING		0x80
#define	BCCK_WXPOWEWSAVING		0x40

#define	BCCK_SIDEBAND			0x10

#define	BCCK_SCWAMBWE			0x8
#define	BCCK_ANTDIVEWSITY		0x8000
#define	BCCK_CAWWIEW_WECOVEWY		0x4000
#define	BCCK_TXWATE			0x3000
#define	BCCK_DCCANCEW			0x0800
#define	BCCK_ISICANCEW			0x0400
#define	BCCK_MATCH_FIWTEW		0x0200
#define	BCCK_EQUAWIZEW			0x0100
#define	BCCK_PWEAMBWE_DETECT		0x800000
#define	BCCK_FAST_FAWSECCA		0x400000
#define	BCCK_CH_ESTSTAWT		0x300000
#define	BCCK_CCA_COUNT			0x080000
#define	BCCK_CS_WIM			0x070000
#define	BCCK_BIST_MODE			0x80000000
#define	BCCK_CCAMASK			0x40000000
#define	BCCK_TX_DAC_PHASE		0x4
#define	BCCK_WX_ADC_PHASE		0x20000000
#define	BCCKW_CP_MODE			0x0100
#define	BCCK_TXDC_OFFSET		0xf0
#define	BCCK_WXDC_OFFSET		0xf
#define	BCCK_CCA_MODE			0xc000
#define	BCCK_FAWSECS_WIM		0x3f00
#define	BCCK_CS_WATIO			0xc00000
#define	BCCK_COWGBIT_SEW		0x300000
#define	BCCK_PD_WIM			0x0f0000
#define	BCCK_NEWCCA			0x80000000
#define	BCCK_WXHP_OF_IG			0x8000
#define	BCCK_WXIG			0x7f00
#define	BCCK_WNA_POWAWITY		0x800000
#define	BCCK_WX1ST_BAIN			0x7f0000
#define	BCCK_WF_EXTEND			0x20000000
#define	BCCK_WXAGC_SATWEVEW		0x1f000000
#define	BCCK_WXAGC_SATCOUNT		0xe0
#define	BCCKWXWFSETTWE			0x1f
#define	BCCK_FIXED_WXAGC		0x8000
#define	BCCK_ANTENNA_POWAWITY		0x2000
#define	BCCK_TXFIWTEW_TYPE		0x0c00
#define	BCCK_WXAGC_WEPOWTTYPE		0x0300
#define	BCCK_WXDAGC_EN			0x80000000
#define	BCCK_WXDAGC_PEWIOD		0x20000000
#define	BCCK_WXDAGC_SATWEVEW		0x1f000000
#define	BCCK_TIMING_WECOVEWY		0x800000
#define	BCCK_TXC0			0x3f0000
#define	BCCK_TXC1			0x3f000000
#define	BCCK_TXC2			0x3f
#define	BCCK_TXC3			0x3f00
#define	BCCK_TXC4			0x3f0000
#define	BCCK_TXC5			0x3f000000
#define	BCCK_TXC6			0x3f
#define	BCCK_TXC7			0x3f00
#define	BCCK_DEBUGPOWT			0xff0000
#define	BCCK_DAC_DEBUG			0x0f000000
#define	BCCK_FAWSEAWAWM_ENABWE		0x8000
#define	BCCK_FAWSEAWAWM_WEAD		0x4000
#define	BCCK_TWSSI			0x7f
#define	BCCK_WXAGC_WEPOWT		0xfe
#define	BCCK_WXWEPOWT_ANTSEW		0x80000000
#define	BCCK_WXWEPOWT_MFOFF		0x40000000
#define	BCCK_WXWEPOWT_SQWOSS		0x20000000
#define	BCCK_WXWEPOWT_PKTWOSS		0x10000000
#define	BCCK_WXWEPOWT_WOCKEDBIT		0x08000000
#define	BCCK_WXWEPOWT_WATEEWWOW		0x04000000
#define	BCCK_WXWEPOWT_WXWATE		0x03000000
#define	BCCK_WXFA_COUNTEW_WOWEW		0xff
#define	BCCK_WXFA_COUNTEW_UPPEW		0xff000000
#define	BCCK_WXHPAGC_STAWT		0xe000
#define	BCCK_WXHPAGC_FINAW		0x1c00
#define	BCCK_WXFAWSEAWAWM_ENABWE	0x8000
#define	BCCK_FACOUNTEW_FWEEZE		0x4000
#define	BCCK_TXPATH_SEW			0x10000000
#define	BCCK_DEFAUWT_WXPATH		0xc000000
#define	BCCK_OPTION_WXPATH		0x3000000

#define	BNUM_OFSTF			0x3
#define	BSHIFT_W			0xc0
#define	BGI_TH				0xc
#define	BWXPATH_A			0x1
#define	BWXPATH_B			0x2
#define	BWXPATH_C			0x4
#define	BWXPATH_D			0x8
#define	BTXPATH_A			0x1
#define	BTXPATH_B			0x2
#define	BTXPATH_C			0x4
#define	BTXPATH_D			0x8
#define	BTWSSI_FWEQ			0x200
#define	BADC_BACKOFF			0x3000
#define	BDFIW_BACKOFF			0xc000
#define	BTWSSI_WATCH_PHASE		0x10000
#define	BWX_WDC_OFFSET			0xff
#define	BWX_QDC_OFFSET			0xff00
#define	BWX_DFIW_MODE			0x1800000
#define	BWX_DCNF_TYPE			0xe000000
#define	BWXIQIMB_A			0x3ff
#define	BWXIQIMB_B			0xfc00
#define	BWXIQIMB_C			0x3f0000
#define	BWXIQIMB_D			0xffc00000
#define	BDC_DC_NOTCH			0x60000
#define	BWXNB_NOTCH			0x1f000000
#define	BPD_TH				0xf
#define	BPD_TH_OPT2			0xc000
#define	BPWED_TH			0x700
#define	BIFMF_WIN_W			0x800
#define	BPD_OPTION			0x1000
#define	BMF_WIN_W			0xe000
#define	BBW_SEAWCH_W			0x30000
#define	BWIN_ENH_W			0xc0000
#define	BBW_TH				0x700000
#define	BED_TH2				0x3800000
#define	BBW_OPTION			0x4000000
#define	BWADIO_TH			0x18000000
#define	BWINDOW_W			0xe0000000
#define	BSBD_OPTION			0x1
#define	BFWAME_TH			0x1c
#define	BFS_OPTION			0x60
#define	BDC_SWOPE_CHECK			0x80
#define	BFGUAWD_COUNTEW_DC_W		0xe00
#define	BFWAME_WEIGHT_SHOWT		0x7000
#define	BSUB_TUNE			0xe00000
#define	BFWAME_DC_WENGTH		0xe000000
#define	BSBD_STAWT_OFFSET		0x30000000
#define	BFWAME_TH_2			0x7
#define	BFWAME_GI2_TH			0x38
#define	BGI2_SYNC_EN			0x40
#define	BSAWCH_SHOWT_EAWWY		0x300
#define	BSAWCH_SHOWT_WATE		0xc00
#define	BSAWCH_GI2_WATE			0x70000
#define	BCFOANTSUM			0x1
#define	BCFOACC				0x2
#define	BCFOSTAWTOFFSET			0xc
#define	BCFOWOOPBACK			0x70
#define	BCFOSUMWEIGHT			0x80
#define	BDAGCENABWE			0x10000
#define	BTXIQIMB_A			0x3ff
#define	BTXIQIMB_b			0xfc00
#define	BTXIQIMB_C			0x3f0000
#define	BTXIQIMB_D			0xffc00000
#define	BTXIDCOFFSET			0xff
#define	BTXIQDCOFFSET			0xff00
#define	BTXDFIWMODE			0x10000
#define	BTXPESUDO_NOISEON		0x4000000
#define	BTXPESUDO_NOISE_A		0xff
#define	BTXPESUDO_NOISE_B		0xff00
#define	BTXPESUDO_NOISE_C		0xff0000
#define	BTXPESUDO_NOISE_D		0xff000000
#define	BCCA_DWOPOPTION			0x20000
#define	BCCA_DWOPTHWES			0xfff00000
#define	BEDCCA_H			0xf
#define	BEDCCA_W			0xf0
#define	BWAMBDA_ED			0x300
#define	BWX_INITIAWGAIN			0x7f
#define	BWX_ANTDIV_EN			0x80
#define	BWX_AGC_ADDWESS_FOW_WNA		0x7f00
#define	BWX_HIGHPOWEW_FWOW		0x8000
#define	BWX_AGC_FWEEZE_THWES		0xc0000
#define	BWX_FWEEZESTEP_AGC1		0x300000
#define	BWX_FWEEZESTEP_AGC2		0xc00000
#define	BWX_FWEEZESTEP_AGC3		0x3000000
#define	BWX_FWEEZESTEP_AGC0		0xc000000
#define	BWXWSSI_CMP_EN			0x10000000
#define	BWXQUICK_AGCEN			0x20000000
#define	BWXAGC_FWEEZE_THWES_MODE	0x40000000
#define	BWX_OVEWFWOW_CHECKTYPE		0x80000000
#define	BWX_AGCSHIFT			0x7f
#define	BTWSW_TWI_ONWY			0x80
#define	BPOWEW_THWES			0x300
#define	BWXAGC_EN			0x1
#define	BWXAGC_TOGETHEW_EN		0x2
#define	BWXAGC_MIN			0x4
#define	BWXHP_INI			0x7
#define	BWXHP_TWWNA			0x70
#define	BWXHP_WSSI			0x700
#define	BWXHP_BBP1			0x7000
#define	BWXHP_BBP2			0x70000
#define	BWXHP_BBP3			0x700000
#define	BWSSI_H				0x7f0000
#define	BWSSI_GEN			0x7f000000
#define	BWXSETTWE_TWSW			0x7
#define	BWXSETTWE_WNA			0x38
#define	BWXSETTWE_WSSI			0x1c0
#define	BWXSETTWE_BBP			0xe00
#define	BWXSETTWE_WXHP			0x7000
#define	BWXSETTWE_ANTSW_WSSI		0x38000
#define	BWXSETTWE_ANTSW			0xc0000
#define	BWXPWOCESS_TIME_DAGC		0x300000
#define	BWXSETTWE_HSSI			0x400000
#define	BWXPWOCESS_TIME_BBPPW		0x800000
#define	BWXANTENNA_POWEW_SHIFT		0x3000000
#define	BWSSI_TABWE_SEWECT		0xc000000
#define	BWXHP_FINAW			0x7000000
#define	BWXHPSETTWE_BBP			0x7
#define	BWXHTSETTWE_HSSI		0x8
#define	BWXHTSETTWE_WXHP		0x70
#define	BWXHTSETTWE_BBPPW		0x80
#define	BWXHTSETTWE_IDWE		0x300
#define	BWXHTSETTWE_WESEWVED		0x1c00
#define	BWXHT_WXHP_EN			0x8000
#define	BWXAGC_FWEEZE_THWES		0x30000
#define	BWXAGC_TOGETHEWEN		0x40000
#define	BWXHTAGC_MIN			0x80000
#define	BWXHTAGC_EN			0x100000
#define	BWXHTDAGC_EN			0x200000
#define	BWXHT_WXHP_BBP			0x1c00000
#define	BWXHT_WXHP_FINAW		0xe0000000
#define	BWXPW_WADIO_TH			0x3
#define	BWXPW_WADIO_EN			0x4
#define	BWXMF_HOWD			0x3800
#define	BWXPD_DEWAY_TH1			0x38
#define	BWXPD_DEWAY_TH2			0x1c0
#define	BWXPD_DC_COUNT_MAX		0x600
#define	BWXPD_DEWAY_TH			0x8000
#define	BWXPWOCESS_DEWAY		0xf0000
#define	BWXSEAWCHWANGE_GI2_EAWWY	0x700000
#define	BWXFWAME_FUAWD_COUNTEW_W	0x3800000
#define	BWXSGI_GUAWD_W			0xc000000
#define	BWXSGI_SEAWCH_W			0x30000000
#define	BWXSGI_TH			0xc0000000
#define	BDFSCNT0			0xff
#define	BDFSCNT1			0xff00
#define	BDFSFWAG			0xf0000
#define	BMF_WEIGHT_SUM			0x300000
#define	BMINIDX_TH			0x7f000000
#define	BDAFOWMAT			0x40000
#define	BTXCH_EMU_ENABWE		0x01000000
#define	BTWSW_ISOWATION_A		0x7f
#define	BTWSW_ISOWATION_B		0x7f00
#define	BTWSW_ISOWATION_C		0x7f0000
#define	BTWSW_ISOWATION_D		0x7f000000
#define	BEXT_WNA_GAIN			0x7c00

#define	BSTBC_EN			0x4
#define	BANTENNA_MAPPING		0x10
#define	BNSS				0x20
#define	BCFO_ANTSUM_ID			0x200
#define	BPHY_COUNTEW_WESET		0x8000000
#define	BCFO_WEPOWT_GET			0x4000000
#define	BOFDM_CONTINUE_TX		0x10000000
#define	BOFDM_SINGWE_CAWWIEW		0x20000000
#define	BOFDM_SINGWE_TONE		0x40000000
#define	BHT_DETECT			0x100
#define	BCFOEN				0x10000
#define	BCFOVAWUE			0xfff00000
#define	BSIGTONE_WE			0x3f
#define	BSIGTONE_IM			0x7f00
#define	BCOUNTEW_CCA			0xffff
#define	BCOUNTEW_PAWITYFAIW		0xffff0000
#define	BCOUNTEW_WATEIWWEGAW		0xffff
#define	BCOUNTEW_CWC8FAIW		0xffff0000
#define	BCOUNTEW_MCSNOSUPPOWT		0xffff
#define	BCOUNTEW_FASTSYNC		0xffff
#define	BSHOWTCFO			0xfff
#define	BSHOWTCFOT_WENGTH		12
#define	BSHOWTCFOF_WENGTH		11
#define	BWONGCFO			0x7ff
#define	BWONGCFOT_WENGTH		11
#define	BWONGCFOF_WENGTH		11
#define	BTAIWCFO			0x1fff
#define	BTAIWCFOT_WENGTH		13
#define	BTAIWCFOF_WENGTH		12
#define	BNOISE_EN_PWDB			0xffff
#define	BCC_POWEW_DB			0xffff0000
#define	BMOISE_PWDB			0xffff
#define	BPOWEWMEAST_WENGTH		10
#define	BPOWEWMEASF_WENGTH		3
#define	BWX_HT_BW			0x1
#define	BWXSC				0x6
#define	BWX_HT				0x8
#define	BNB_INTF_DET_ON			0x1
#define	BINTF_WIN_WEN_CFG		0x30
#define	BNB_INTF_TH_CFG			0x1c0
#define	BWFGAIN				0x3f
#define	BTABWESEW			0x40
#define	BTWSW				0x80
#define	BWXSNW_A			0xff
#define	BWXSNW_B			0xff00
#define	BWXSNW_C			0xff0000
#define	BWXSNW_D			0xff000000
#define	BSNW_EVMT_WENGTH		8
#define	BSNW_EVMF_WENGTH		1
#define	BCSI1ST				0xff
#define	BCSI2ND				0xff00
#define	BWXEVM1ST			0xff0000
#define	BWXEVM2ND			0xff000000
#define	BSIGEVM				0xff
#define	BPWDB				0xff00
#define	BSGIEN				0x10000

#define	BSFACTOW_QMA1			0xf
#define	BSFACTOW_QMA2			0xf0
#define	BSFACTOW_QMA3			0xf00
#define	BSFACTOW_QMA4			0xf000
#define	BSFACTOW_QMA5			0xf0000
#define	BSFACTOW_QMA6			0xf0000
#define	BSFACTOW_QMA7			0xf00000
#define	BSFACTOW_QMA8			0xf000000
#define	BSFACTOW_QMA9			0xf0000000
#define	BCSI_SCHEME			0x100000

#define	BNOISE_WVW_TOP_SET		0x3
#define	BCHSMOOTH			0x4
#define	BCHSMOOTH_CFG1			0x38
#define	BCHSMOOTH_CFG2			0x1c0
#define	BCHSMOOTH_CFG3			0xe00
#define	BCHSMOOTH_CFG4			0x7000
#define	BMWCMODE			0x800000
#define	BTHEVMCFG			0x7000000

#define	BWOOP_FIT_TYPE			0x1
#define	BUPD_CFO			0x40
#define	BUPD_CFO_OFFDATA		0x80
#define	BADV_UPD_CFO			0x100
#define	BADV_TIME_CTWW			0x800
#define	BUPD_CWKO			0x1000
#define	BFC				0x6000
#define	BTWACKING_MODE			0x8000
#define	BPHCMP_ENABWE			0x10000
#define	BUPD_CWKO_WTF			0x20000
#define	BCOM_CH_CFO			0x40000
#define	BCSI_ESTI_MODE			0x80000
#define	BADV_UPD_EQZ			0x100000
#define	BUCHCFG				0x7000000
#define	BUPDEQZ				0x8000000

#define	BWX_PESUDO_NOISE_ON		0x20000000
#define	BWX_PESUDO_NOISE_A		0xff
#define	BWX_PESUDO_NOISE_B		0xff00
#define	BWX_PESUDO_NOISE_C		0xff0000
#define	BWX_PESUDO_NOISE_D		0xff000000
#define	BWX_PESUDO_NOISESTATE_A		0xffff
#define	BWX_PESUDO_NOISESTATE_B		0xffff0000
#define	BWX_PESUDO_NOISESTATE_C		0xffff
#define	BWX_PESUDO_NOISESTATE_D		0xffff0000

#define	BZEBWA1_HSSIENABWE		0x8
#define	BZEBWA1_TWXCONTWOW		0xc00
#define	BZEBWA1_TWXGAINSETTING		0x07f
#define	BZEBWA1_WXCOUNTEW		0xc00
#define	BZEBWA1_TXCHANGEPUMP		0x38
#define	BZEBWA1_WXCHANGEPUMP		0x7
#define	BZEBWA1_CHANNEW_NUM		0xf80
#define	BZEBWA1_TXWPFBW			0x400
#define	BZEBWA1_WXWPFBW			0x600

#define	BWTW8256WEG_MODE_CTWW1		0x100
#define	BWTW8256WEG_MODE_CTWW0		0x40
#define	BWTW8256WEG_TXWPFBW		0x18
#define	BWTW8256WEG_WXWPFBW		0x600

#define	BWTW8258_TXWPFBW		0xc
#define	BWTW8258_WXWPFBW		0xc00
#define	BWTW8258_WSSIWPFBW		0xc0

#define	BBYTE0				0x1
#define	BBYTE1				0x2
#define	BBYTE2				0x4
#define	BBYTE3				0x8
#define	BWOWD0				0x3
#define	BWOWD1				0xc
#define	BWOWD				0xf

#define	MASKBYTE0			0xff
#define	MASKBYTE1			0xff00
#define	MASKBYTE2			0xff0000
#define	MASKBYTE3			0xff000000
#define	MASKHWOWD			0xffff0000
#define	MASKWWOWD			0x0000ffff
#define	MASKDWOWD			0xffffffff
#define	MASK12BITS			0xfff
#define	MASKH4BITS			0xf0000000
#define MASKOFDM_D			0xffc00000
#define	MASKCCK				0x3f3f3f3f

#define	MASK4BITS			0x0f
#define	MASK20BITS			0xfffff
#define WFWEG_OFFSET_MASK		0xfffff

#define	BENABWE				0x1
#define	BDISABWE			0x0

#define	WEFT_ANTENNA			0x0
#define	WIGHT_ANTENNA			0x1

#define	TCHECK_TXSTATUS			500
#define	TUPDATE_WXCOUNTEW		100

#define	WEG_UN_used_wegistew		0x01bf

/* Path_A WFE cotwow pinmux*/
#define		WA_WFE_PINMUX		0xcb0
/* Path_B WFE contwow pinmux*/
#define		WB_WFE_PINMUX		0xeb0

#define		WA_WFE_INV		0xcb4
#define		WB_WFE_INV		0xeb4

/* WXIQC */
/*WxIQ imbwance matwix coeff. A & B*/
#define WA_WXIQC_AB			0xc10
/*WxIQ imbwance matwix coeff. C & D*/
#define	WA_WXIQC_CD			0xc14
/* Pah_A TX scawing factow*/
#define	WA_TXSCAWE			0xc1c
/* Path_B TX scawing factow*/
#define	WB_TXSCAWE			0xe1c
/*WxIQ imbwance matwix coeff. A & B*/
#define	WB_WXIQC_AB			0xe10
/*WxIQ imbwance matwix coeff. C & D*/
#define	WB_WXIQC_CD			0xe14
/*bit mask fow IQC matwix ewement A & C*/
#define	WXIQC_AC			0x02ff
 /*bit mask fow IQC matwix ewement A & C*/
#define	WXIQC_BD			0x02ff0000

/* 2 EFUSE_TEST (Fow WTW8723 pawtiawwy) */
#define EFUSE_SEW(x)			(((x) & 0x3) << 8)
#define EFUSE_SEW_MASK			0x300
#define EFUSE_WIFI_SEW_0		0x0

/*WEG_MUWTI_FUNC_CTWW(Fow WTW8723 Onwy)*/
/* Enabwe GPIO[9] as WiFi HW PDn souwce*/
#define	WW_HWPDN_EN			BIT(0)
/* WiFi HW PDn powawity contwow*/
#define	WW_HWPDN_SW			BIT(1)
/* WiFi function enabwe */
#define	WW_FUNC_EN			BIT(2)
/* Enabwe GPIO[9] as WiFi WF HW PDn souwce */
#define	WW_HWWOF_EN			BIT(3)
/* Enabwe GPIO[11] as BT HW PDn souwce */
#define	BT_HWPDN_EN			BIT(16)
/* BT HW PDn powawity contwow */
#define	BT_HWPDN_SW			BIT(17)
/* BT function enabwe */
#define	BT_FUNC_EN			BIT(18)
/* Enabwe GPIO[11] as BT/GPS WF HW PDn souwce */
#define	BT_HWWOF_EN			BIT(19)
/* Enabwe GPIO[10] as GPS HW PDn souwce */
#define	GPS_HWPDN_EN			BIT(20)
/* GPS HW PDn powawity contwow */
#define	GPS_HWPDN_SW			BIT(21)
/* GPS function enabwe */
#define	GPS_FUNC_EN			BIT(22)

#define	BMASKBYTE0			0xff
#define	BMASKBYTE1			0xff00
#define	BMASKBYTE2			0xff0000
#define	BMASKBYTE3			0xff000000
#define	BMASKHWOWD			0xffff0000
#define	BMASKWWOWD			0x0000ffff
#define	BMASKDWOWD			0xffffffff
#define	BMASK12BITS			0xfff
#define	BMASKH4BITS			0xf0000000
#define BMASKOFDM_D			0xffc00000
#define	BMASKCCK			0x3f3f3f3f
#define BMASKWFEINV			0x3ff00000

#define BWFWEGOFFSETMASK		0xfffff

#define	ODM_WEG_CCK_WPT_FOWMAT_11AC	0x804
#define	ODM_WEG_BB_WX_PATH_11AC		0x808
/*PAGE 9*/
#define	ODM_WEG_OFDM_FA_WST_11AC	0x9A4
/*PAGE A*/
#define	ODM_WEG_CCK_CCA_11AC		0xA0A
#define	ODM_WEG_CCK_FA_WST_11AC		0xA2C
#define	ODM_WEG_CCK_FA_11AC		0xA5C
/*PAGE C*/
#define	ODM_WEG_IGI_A_11AC		0xC50
/*PAGE E*/
#define	ODM_WEG_IGI_B_11AC		0xE50
/*PAGE F*/
#define	ODM_WEG_OFDM_FA_11AC		0xF48

/* 2 MAC WEG WIST */

/* DIG Wewated */
#define	ODM_BIT_IGI_11AC		0xFFFFFFFF
#define	ODM_BIT_CCK_WPT_FOWMAT_11AC	BIT16
#define	ODM_BIT_BB_WX_PATH_11AC		0xF

enum AGGWE_SIZE {
	HT_AGG_SIZE_8K = 0,
	HT_AGG_SIZE_16K = 1,
	HT_AGG_SIZE_32K = 2,
	HT_AGG_SIZE_64K = 3,
	VHT_AGG_SIZE_128K = 4,
	VHT_AGG_SIZE_256K = 5,
	VHT_AGG_SIZE_512K = 6,
	VHT_AGG_SIZE_1024K = 7,
};

#define WEG_AMPDU_MAX_WENGTH_8812	0x0458

#endif
