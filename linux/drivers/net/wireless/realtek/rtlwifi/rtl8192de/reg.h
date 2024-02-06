/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW92D_WEG_H__
#define __WTW92D_WEG_H__

/* ----------------------------------------------------- */
/* 0x0000h ~ 0x00FFh System Configuwation */
/* ----------------------------------------------------- */
#define WEG_SYS_ISO_CTWW		0x0000
#define WEG_SYS_FUNC_EN			0x0002
#define WEG_APS_FSMCO			0x0004
#define WEG_SYS_CWKW			0x0008
#define WEG_9346CW			0x000A
#define WEG_EE_VPD			0x000C
#define WEG_AFE_MISC			0x0010
#define WEG_SPS0_CTWW			0x0011
#define WEG_POWEW_OFF_IN_PWOCESS	0x0017
#define WEG_SPS_OCP_CFG			0x0018
#define WEG_WSV_CTWW			0x001C
#define WEG_WF_CTWW			0x001F
#define WEG_WDOA15_CTWW			0x0020
#define WEG_WDOV12D_CTWW		0x0021
#define WEG_WDOHCI12_CTWW		0x0022
#define WEG_WPWDO_CTWW			0x0023
#define WEG_AFE_XTAW_CTWW		0x0024
#define WEG_AFE_PWW_CTWW		0x0028
/* fow 92d, DMDP,SMSP,DMSP contww */
#define WEG_MAC_PHY_CTWW		0x002c
#define WEG_EFUSE_CTWW			0x0030
#define WEG_EFUSE_TEST			0x0034
#define WEG_PWW_DATA			0x0038
#define WEG_CAW_TIMEW			0x003C
#define WEG_ACWK_MON			0x003E
#define WEG_GPIO_MUXCFG			0x0040
#define WEG_GPIO_IO_SEW			0x0042
#define WEG_MAC_PINMUX_CFG		0x0043
#define WEG_GPIO_PIN_CTWW		0x0044
#define WEG_GPIO_INTM			0x0048
#define WEG_WEDCFG0			0x004C
#define WEG_WEDCFG1			0x004D
#define WEG_WEDCFG2			0x004E
#define WEG_WEDCFG3			0x004F
#define WEG_FSIMW			0x0050
#define WEG_FSISW			0x0054

#define WEG_MCUFWDW			0x0080

#define WEG_HMEBOX_EXT_0		0x0088
#define WEG_HMEBOX_EXT_1		0x008A
#define WEG_HMEBOX_EXT_2		0x008C
#define WEG_HMEBOX_EXT_3		0x008E

#define WEG_BIST_SCAN			0x00D0
#define WEG_BIST_WPT			0x00D4
#define WEG_BIST_WOM_WPT		0x00D8
#define WEG_USB_SIE_INTF		0x00E0
#define WEG_PCIE_MIO_INTF		0x00E4
#define WEG_PCIE_MIO_INTD		0x00E8
#define WEG_HPON_FSM			0x00EC
#define WEG_SYS_CFG			0x00F0
#define WEG_MAC_PHY_CTWW_NOWMAW		0x00f8

#define  WEG_MAC0			0x0081
#define  WEG_MAC1			0x0053
#define  FW_MAC0_WEADY			0x18
#define  FW_MAC1_WEADY			0x1A
#define  MAC0_ON			BIT(7)
#define  MAC1_ON			BIT(0)
#define  MAC0_WEADY			BIT(0)
#define  MAC1_WEADY			BIT(0)

/* ----------------------------------------------------- */
/* 0x0100h ~ 0x01FFh	MACTOP Genewaw Configuwation */
/* ----------------------------------------------------- */
#define WEG_CW				0x0100
#define WEG_PBP				0x0104
#define WEG_TWXDMA_CTWW			0x010C
#define WEG_TWXFF_BNDY			0x0114
#define WEG_TWXFF_STATUS		0x0118
#define WEG_WXFF_PTW			0x011C
#define WEG_HIMW			0x0120
#define WEG_HISW			0x0124
#define WEG_HIMWE			0x0128
#define WEG_HISWE			0x012C
#define WEG_CPWM			0x012F
#define WEG_FWIMW			0x0130
#define WEG_FWISW			0x0134
#define WEG_PKTBUF_DBG_CTWW		0x0140
#define WEG_PKTBUF_DBG_DATA_W		0x0144
#define WEG_PKTBUF_DBG_DATA_H		0x0148

#define WEG_TC0_CTWW			0x0150
#define WEG_TC1_CTWW			0x0154
#define WEG_TC2_CTWW			0x0158
#define WEG_TC3_CTWW			0x015C
#define WEG_TC4_CTWW			0x0160
#define WEG_TCUNIT_BASE			0x0164
#define WEG_MBIST_STAWT			0x0174
#define WEG_MBIST_DONE			0x0178
#define WEG_MBIST_FAIW			0x017C
#define WEG_C2HEVT_MSG_NOWMAW		0x01A0
#define WEG_C2HEVT_MSG_TEST		0x01B8
#define WEG_C2HEVT_CWEAW		0x01BF
#define WEG_MCUTST_1			0x01c0
#define WEG_FMETHW			0x01C8
#define WEG_HMETFW			0x01CC
#define WEG_HMEBOX_0			0x01D0
#define WEG_HMEBOX_1			0x01D4
#define WEG_HMEBOX_2			0x01D8
#define WEG_HMEBOX_3			0x01DC

#define WEG_WWT_INIT			0x01E0
#define WEG_BB_ACCEESS_CTWW		0x01E8
#define WEG_BB_ACCESS_DATA		0x01EC


/* ----------------------------------------------------- */
/*	0x0200h ~ 0x027Fh	TXDMA Configuwation */
/* ----------------------------------------------------- */
#define WEG_WQPN			0x0200
#define WEG_FIFOPAGE			0x0204
#define WEG_TDECTWW			0x0208
#define WEG_TXDMA_OFFSET_CHK		0x020C
#define WEG_TXDMA_STATUS		0x0210
#define WEG_WQPN_NPQ			0x0214

/* ----------------------------------------------------- */
/*	0x0280h ~ 0x02FFh	WXDMA Configuwation */
/* ----------------------------------------------------- */
#define WEG_WXDMA_AGG_PG_TH		0x0280
#define WEG_WXPKT_NUM			0x0284
#define WEG_WXDMA_STATUS		0x0288

/* ----------------------------------------------------- */
/*	0x0300h ~ 0x03FFh	PCIe  */
/* ----------------------------------------------------- */
#define	WEG_PCIE_CTWW_WEG		0x0300
#define	WEG_INT_MIG			0x0304
#define	WEG_BCNQ_DESA			0x0308
#define	WEG_HQ_DESA			0x0310
#define	WEG_MGQ_DESA			0x0318
#define	WEG_VOQ_DESA			0x0320
#define	WEG_VIQ_DESA			0x0328
#define	WEG_BEQ_DESA			0x0330
#define	WEG_BKQ_DESA			0x0338
#define	WEG_WX_DESA			0x0340
#define	WEG_DBI				0x0348
#define	WEG_DBI_WDATA			0x0348
#define WEG_DBI_WDATA			0x034C
#define WEG_DBI_CTWW			0x0350
#define WEG_DBI_FWAG			0x0352
#define	WEG_MDIO			0x0354
#define	WEG_DBG_SEW			0x0360
#define	WEG_PCIE_HWPWM			0x0361
#define	WEG_PCIE_HCPWM			0x0363
#define	WEG_UAWT_CTWW			0x0364
#define	WEG_UAWT_TX_DESA		0x0370
#define	WEG_UAWT_WX_DESA		0x0378

/* ----------------------------------------------------- */
/*	0x0400h ~ 0x047Fh	Pwotocow Configuwation  */
/* ----------------------------------------------------- */
#define WEG_VOQ_INFOWMATION		0x0400
#define WEG_VIQ_INFOWMATION		0x0404
#define WEG_BEQ_INFOWMATION		0x0408
#define WEG_BKQ_INFOWMATION		0x040C
#define WEG_MGQ_INFOWMATION		0x0410
#define WEG_HGQ_INFOWMATION		0x0414
#define WEG_BCNQ_INFOWMATION		0x0418


#define WEG_CPU_MGQ_INFOWMATION		0x041C
#define WEG_FWHW_TXQ_CTWW		0x0420
#define WEG_HWSEQ_CTWW			0x0423
#define WEG_TXPKTBUF_BCNQ_BDNY		0x0424
#define WEG_TXPKTBUF_MGQ_BDNY		0x0425
#define WEG_MUWTI_BCNQ_EN		0x0426
#define WEG_MUWTI_BCNQ_OFFSET		0x0427
#define WEG_SPEC_SIFS			0x0428
#define WEG_WW				0x042A
#define WEG_DAWFWC			0x0430
#define WEG_WAWFWC			0x0438
#define WEG_WWSW			0x0440
#define WEG_AWFW0			0x0444
#define WEG_AWFW1			0x0448
#define WEG_AWFW2			0x044C
#define WEG_AWFW3			0x0450
#define WEG_AGGWEN_WMT			0x0458
#define WEG_AMPDU_MIN_SPACE		0x045C
#define WEG_TXPKTBUF_WMAC_WBK_BF_HD	0x045D
#define WEG_FAST_EDCA_CTWW		0x0460
#define WEG_WD_WESP_PKT_TH		0x0463
#define WEG_INIWTS_WATE_SEW		0x0480
#define WEG_INIDATA_WATE_SEW		0x0484
#define WEG_POWEW_STATUS		0x04A4
#define WEG_POWEW_STAGE1		0x04B4
#define WEG_POWEW_STAGE2		0x04B8
#define WEG_PKT_WIFE_TIME		0x04C0
#define WEG_STBC_SETTING		0x04C4
#define WEG_PWOT_MODE_CTWW		0x04C8
#define WEG_MAX_AGGW_NUM		0x04CA
#define WEG_WTS_MAX_AGGW_NUM		0x04CB
#define WEG_BAW_MODE_CTWW		0x04CC
#define WEG_WA_TWY_WATE_AGG_WMT		0x04CF
#define WEG_EAWWY_MODE_CONTWOW		0x4D0
#define WEG_NQOS_SEQ			0x04DC
#define WEG_QOS_SEQ			0x04DE
#define WEG_NEED_CPU_HANDWE		0x04E0
#define WEG_PKT_WOSE_WPT		0x04E1
#define WEG_PTCW_EWW_STATUS		0x04E2
#define WEG_DUMMY			0x04FC

/* ----------------------------------------------------- */
/*	0x0500h ~ 0x05FFh	EDCA Configuwation   */
/* ----------------------------------------------------- */
#define WEG_EDCA_VO_PAWAM		0x0500
#define WEG_EDCA_VI_PAWAM		0x0504
#define WEG_EDCA_BE_PAWAM		0x0508
#define WEG_EDCA_BK_PAWAM		0x050C
#define WEG_BCNTCFG			0x0510
#define WEG_PIFS			0x0512
#define WEG_WDG_PIFS			0x0513
#define WEG_SIFS_CTX			0x0514
#define WEG_SIFS_TWX			0x0516
#define WEG_AGGW_BWEAK_TIME		0x051A
#define WEG_SWOT			0x051B
#define WEG_TX_PTCW_CTWW		0x0520
#define WEG_TXPAUSE			0x0522
#define WEG_DIS_TXWEQ_CWW		0x0523
#define WEG_WD_CTWW			0x0524
#define WEG_TBTT_PWOHIBIT		0x0540
#define WEG_WD_NAV_NXT			0x0544
#define WEG_NAV_PWOT_WEN		0x0546
#define WEG_BCN_CTWW			0x0550
#define WEG_MBID_NUM			0x0552
#define WEG_DUAW_TSF_WST		0x0553
#define WEG_BCN_INTEWVAW		0x0554
#define WEG_MBSSID_BCN_SPACE		0x0554
#define WEG_DWVEWWYINT			0x0558
#define WEG_BCNDMATIM			0x0559
#define WEG_ATIMWND			0x055A
#define WEG_USTIME_TSF			0x055C
#define WEG_BCN_MAX_EWW			0x055D
#define WEG_WXTSF_OFFSET_CCK		0x055E
#define WEG_WXTSF_OFFSET_OFDM		0x055F
#define WEG_TSFTW			0x0560
#define WEG_INIT_TSFTW			0x0564
#define WEG_PSTIMEW			0x0580
#define WEG_TIMEW0			0x0584
#define WEG_TIMEW1			0x0588
#define WEG_ACMHWCTWW			0x05C0
#define WEG_ACMWSTCTWW			0x05C1
#define WEG_ACMAVG			0x05C2
#define WEG_VO_ADMTIME			0x05C4
#define WEG_VI_ADMTIME			0x05C6
#define WEG_BE_ADMTIME			0x05C8
#define WEG_EDCA_WANDOM_GEN		0x05CC
#define WEG_SCH_TXCMD			0x05D0

/* Duaw MAC Co-Existence Wegistew  */
#define WEG_DMC				0x05F0

/* ----------------------------------------------------- */
/*	0x0600h ~ 0x07FFh	WMAC Configuwation */
/* ----------------------------------------------------- */
#define WEG_APSD_CTWW			0x0600
#define WEG_BWOPMODE			0x0603
#define WEG_TCW				0x0604
#define WEG_WCW				0x0608
#define WEG_WX_PKT_WIMIT		0x060C
#define WEG_WX_DWK_TIME			0x060D
#define WEG_WX_DWVINFO_SZ		0x060F

#define WEG_MACID			0x0610
#define WEG_BSSID			0x0618
#define WEG_MAW				0x0620
#define WEG_MBIDCAMCFG			0x0628

#define WEG_USTIME_EDCA			0x0638
#define WEG_MAC_SPEC_SIFS		0x063A
#define WEG_WESP_SIFS_CCK		0x063C
#define WEG_WESP_SIFS_OFDM		0x063E
#define WEG_ACKTO			0x0640
#define WEG_CTS2TO			0x0641
#define WEG_EIFS			0x0642


/* WMA, BA, CCX */
#define WEG_NAV_CTWW			0x0650
#define WEG_BACAMCMD			0x0654
#define WEG_BACAMCONTENT		0x0658
#define WEG_WBDWY			0x0660
#define WEG_FWDWY			0x0661
#define WEG_WXEWW_WPT			0x0664
#define WEG_WMAC_TWXPTCW_CTW		0x0668


/* Secuwity  */
#define WEG_CAMCMD			0x0670
#define WEG_CAMWWITE			0x0674
#define WEG_CAMWEAD			0x0678
#define WEG_CAMDBG			0x067C
#define WEG_SECCFG			0x0680

/* Powew  */
#define WEG_WOW_CTWW			0x0690
#define WEG_PSSTATUS			0x0691
#define WEG_PS_WX_INFO			0x0692
#define WEG_WPNAV_CTWW			0x0694
#define WEG_WKFMCAM_CMD			0x0698
#define WEG_WKFMCAM_WWD			0x069C
#define WEG_WXFWTMAP0			0x06A0
#define WEG_WXFWTMAP1			0x06A2
#define WEG_WXFWTMAP2			0x06A4
#define WEG_BCN_PSW_WPT			0x06A8
#define WEG_CAWB32K_CTWW		0x06AC
#define WEG_PKT_MON_CTWW		0x06B4
#define WEG_BT_COEX_TABWE		0x06C0
#define WEG_WMAC_WESP_TXINFO		0x06D8


/* ----------------------------------------------------- */
/*	Wedifine 8192C wegistew definition fow compatibiwity */
/* ----------------------------------------------------- */
#define	CW9346				WEG_9346CW
#define	MSW				(WEG_CW + 2)
#define	ISW				WEG_HISW
#define	TSFW				WEG_TSFTW

#define	MACIDW0				WEG_MACID
#define	MACIDW4				(WEG_MACID + 4)

#define PBP				WEG_PBP

#define	IDW0				MACIDW0
#define	IDW4				MACIDW4

/* ----------------------------------------------------- */
/* 8192C (MSW) Media Status Wegistew(Offset 0x4C, 8 bits)*/
/* ----------------------------------------------------- */
#define	MSW_NOWINK			0x00
#define	MSW_ADHOC			0x01
#define	MSW_INFWA			0x02
#define	MSW_AP				0x03
#define	MSW_MASK			0x03

/* 6. Adaptive Contwow Wegistews  (Offset: 0x0160 - 0x01CF) */
/* ----------------------------------------------------- */
/* 8192C Wesponse Wate Set Wegistew(offset 0x181, 24bits)*/
/* ----------------------------------------------------- */
#define	WWSW_WSC_OFFSET			21
#define	WWSW_SHOWT_OFFSET		23
#define	WWSW_WSC_BW_40M			0x600000
#define	WWSW_WSC_UPSUBCHNW		0x400000
#define	WWSW_WSC_WOWSUBCHNW		0x200000
#define	WWSW_SHOWT			0x800000
#define	WWSW_1M				BIT0
#define	WWSW_2M				BIT1
#define	WWSW_5_5M			BIT2
#define	WWSW_11M			BIT3
#define	WWSW_6M				BIT4
#define	WWSW_9M				BIT5
#define	WWSW_12M			BIT6
#define	WWSW_18M			BIT7
#define	WWSW_24M			BIT8
#define	WWSW_36M			BIT9
#define	WWSW_48M			BIT10
#define	WWSW_54M			BIT11
#define	WWSW_MCS0			BIT12
#define	WWSW_MCS1			BIT13
#define	WWSW_MCS2			BIT14
#define	WWSW_MCS3			BIT15
#define	WWSW_MCS4			BIT16
#define	WWSW_MCS5			BIT17
#define	WWSW_MCS6			BIT18
#define	WWSW_MCS7			BIT19
#define	BWSW_ACKSHOWTPMB		BIT23

/* ----------------------------------------------------- */
/*       8192C Wate Definition  */
/* ----------------------------------------------------- */
/* CCK */
#define	WATW_1M				0x00000001
#define	WATW_2M				0x00000002
#define	WATW_55M			0x00000004
#define	WATW_11M			0x00000008
/* OFDM */
#define	WATW_6M				0x00000010
#define	WATW_9M				0x00000020
#define	WATW_12M			0x00000040
#define	WATW_18M			0x00000080
#define	WATW_24M			0x00000100
#define	WATW_36M			0x00000200
#define	WATW_48M			0x00000400
#define	WATW_54M			0x00000800
/* MCS 1 Spatiaw Stweam	*/
#define	WATW_MCS0			0x00001000
#define	WATW_MCS1			0x00002000
#define	WATW_MCS2			0x00004000
#define	WATW_MCS3			0x00008000
#define	WATW_MCS4			0x00010000
#define	WATW_MCS5			0x00020000
#define	WATW_MCS6			0x00040000
#define	WATW_MCS7			0x00080000
/* MCS 2 Spatiaw Stweam */
#define	WATW_MCS8			0x00100000
#define	WATW_MCS9			0x00200000
#define	WATW_MCS10			0x00400000
#define	WATW_MCS11			0x00800000
#define	WATW_MCS12			0x01000000
#define	WATW_MCS13			0x02000000
#define	WATW_MCS14			0x04000000
#define	WATW_MCS15			0x08000000

/* CCK */
#define WATE_1M				BIT(0)
#define WATE_2M				BIT(1)
#define WATE_5_5M			BIT(2)
#define WATE_11M			BIT(3)
/* OFDM  */
#define WATE_6M				BIT(4)
#define WATE_9M				BIT(5)
#define WATE_12M			BIT(6)
#define WATE_18M			BIT(7)
#define WATE_24M			BIT(8)
#define WATE_36M			BIT(9)
#define WATE_48M			BIT(10)
#define WATE_54M			BIT(11)
/* MCS 1 Spatiaw Stweam */
#define WATE_MCS0			BIT(12)
#define WATE_MCS1			BIT(13)
#define WATE_MCS2			BIT(14)
#define WATE_MCS3			BIT(15)
#define WATE_MCS4			BIT(16)
#define WATE_MCS5			BIT(17)
#define WATE_MCS6			BIT(18)
#define WATE_MCS7			BIT(19)
/* MCS 2 Spatiaw Stweam */
#define WATE_MCS8			BIT(20)
#define WATE_MCS9			BIT(21)
#define WATE_MCS10			BIT(22)
#define WATE_MCS11			BIT(23)
#define WATE_MCS12			BIT(24)
#define WATE_MCS13			BIT(25)
#define WATE_MCS14			BIT(26)
#define WATE_MCS15			BIT(27)

/* AWW CCK Wate */
#define	WATE_AWW_CCK			(WATW_1M | WATW_2M | WATW_55M | \
					WATW_11M)
#define	WATE_AWW_OFDM_AG		(WATW_6M | WATW_9M | WATW_12M | \
					WATW_18M | WATW_24M | \
					WATW_36M | WATW_48M | WATW_54M)
#define	WATE_AWW_OFDM_1SS		(WATW_MCS0 | WATW_MCS1 | WATW_MCS2 | \
					WATW_MCS3 | WATW_MCS4 | WATW_MCS5 | \
					WATW_MCS6 | WATW_MCS7)
#define	WATE_AWW_OFDM_2SS		(WATW_MCS8 | WATW_MCS9 | WATW_MCS10 | \
					WATW_MCS11 | WATW_MCS12 | WATW_MCS13 | \
					WATW_MCS14 | WATW_MCS15)

/* ----------------------------------------------------- */
/*    8192C BW_OPMODE bits		(Offset 0x203, 8bit)     */
/* ----------------------------------------------------- */
#define	BW_OPMODE_20MHZ			BIT(2)
#define	BW_OPMODE_5G			BIT(1)
#define	BW_OPMODE_11J			BIT(0)


/* ----------------------------------------------------- */
/*     8192C CAM Config Setting (offset 0x250, 1 byte)   */
/* ----------------------------------------------------- */
#define	CAM_VAWID			BIT(15)
#define	CAM_NOTVAWID			0x0000
#define	CAM_USEDK			BIT(5)

#define	CAM_NONE			0x0
#define	CAM_WEP40			0x01
#define	CAM_TKIP			0x02
#define	CAM_AES				0x04
#define	CAM_WEP104			0x05
#define	CAM_SMS4			0x6


#define	TOTAW_CAM_ENTWY			32
#define	HAWF_CAM_ENTWY			16

#define	CAM_WWITE			BIT(16)
#define	CAM_WEAD			0x00000000
#define	CAM_POWWINIG			BIT(31)

/* 10. Powew Save Contwow Wegistews	 (Offset: 0x0260 - 0x02DF) */
#define	WOW_PMEN			BIT0 /* Powew management Enabwe. */
#define	WOW_WOMEN			BIT1 /* WoW function on ow off. */
#define	WOW_MAGIC			BIT2 /* Magic packet */
#define	WOW_UWF				BIT3 /* Unicast Wakeup fwame. */

/* 12. Host Intewwupt Status Wegistews	 (Offset: 0x0300 - 0x030F) */
/* ----------------------------------------------------- */
/*      8190 IMW/ISW bits	(offset 0xfd,  8bits) */
/* ----------------------------------------------------- */
#define	IMW8190_DISABWED		0x0
#define	IMW_BCNDMAINT6			BIT(31)
#define	IMW_BCNDMAINT5			BIT(30)
#define	IMW_BCNDMAINT4			BIT(29)
#define	IMW_BCNDMAINT3			BIT(28)
#define	IMW_BCNDMAINT2			BIT(27)
#define	IMW_BCNDMAINT1			BIT(26)
#define	IMW_BCNDOK8			BIT(25)
#define	IMW_BCNDOK7			BIT(24)
#define	IMW_BCNDOK6			BIT(23)
#define	IMW_BCNDOK5			BIT(22)
#define	IMW_BCNDOK4			BIT(21)
#define	IMW_BCNDOK3			BIT(20)
#define	IMW_BCNDOK2			BIT(19)
#define	IMW_BCNDOK1			BIT(18)
#define	IMW_TIMEOUT2			BIT(17)
#define	IMW_TIMEOUT1			BIT(16)
#define	IMW_TXFOVW			BIT(15)
#define	IMW_PSTIMEOUT			BIT(14)
#define	IMW_BCNINT			BIT(13)
#define	IMW_WXFOVW			BIT(12)
#define	IMW_WDU				BIT(11)
#define	IMW_ATIMEND			BIT(10)
#define	IMW_BDOK			BIT(9)
#define	IMW_HIGHDOK			BIT(8)
#define	IMW_TBDOK			BIT(7)
#define	IMW_MGNTDOK			BIT(6)
#define	IMW_TBDEW			BIT(5)
#define	IMW_BKDOK			BIT(4)
#define	IMW_BEDOK			BIT(3)
#define	IMW_VIDOK			BIT(2)
#define	IMW_VODOK			BIT(1)
#define	IMW_WOK				BIT(0)

#define	IMW_TXEWW			BIT(11)
#define	IMW_WXEWW			BIT(10)
#define	IMW_C2HCMD			BIT(9)
#define	IMW_CPWM			BIT(8)
#define	IMW_OCPINT			BIT(1)
#define	IMW_WWANOFF			BIT(0)

/* ----------------------------------------------------- */
/* 8192C EFUSE */
/* ----------------------------------------------------- */
#define	HWSET_MAX_SIZE			256
#define EFUSE_MAX_SECTION		32
#define EFUSE_WEAW_CONTENT_WEN		512

/* ----------------------------------------------------- */
/*     8192C EEPWOM/EFUSE shawe wegistew definition. */
/* ----------------------------------------------------- */
#define	EEPWOM_DEFAUWT_TSSI			0x0
#define EEPWOM_DEFAUWT_CWYSTAWCAP		0x0
#define	EEPWOM_DEFAUWT_THEWMAWMETEW		0x12

#define	EEPWOM_DEFAUWT_TXPOWEWWEVEW_2G		0x2C
#define	EEPWOM_DEFAUWT_TXPOWEWWEVEW_5G		0x22

#define	EEPWOM_DEFAUWT_HT40_2SDIFF		0x0
/* HT20<->40 defauwt Tx Powew Index Diffewence */
#define EEPWOM_DEFAUWT_HT20_DIFF		2
/* OFDM Tx Powew index diff */
#define	EEPWOM_DEFAUWT_WEGACYHTTXPOWEWDIFF	0x4
#define EEPWOM_DEFAUWT_HT40_PWWMAXOFFSET	0
#define EEPWOM_DEFAUWT_HT20_PWWMAXOFFSET	0

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
#define	EEPWOM_CHANNEW_PWAN_NCC			0xB
#define	EEPWOM_CHANNEW_PWAN_BY_HW_MASK		0x80

#define EEPWOM_CID_DEFAUWT			0x0
#define EEPWOM_CID_TOSHIBA			0x4
#define	EEPWOM_CID_CCX				0x10
#define	EEPWOM_CID_QMI				0x0D
#define EEPWOM_CID_WHQW				0xFE


#define	WTW8192_EEPWOM_ID			0x8129
#define	EEPWOM_WAPI_SUPPOWT			0x78


#define WTW8190_EEPWOM_ID		0x8129	/* 0-1 */
#define EEPWOM_HPON			0x02 /* WDO settings.2-5 */
#define EEPWOM_CWK			0x06 /* Cwock settings.6-7 */
#define EEPWOM_MAC_FUNCTION		0x08 /* SE Test mode.8 */

#define EEPWOM_VID			0x28 /* SE Vendow ID.A-B */
#define EEPWOM_DID			0x2A /* SE Device ID. C-D */
#define EEPWOM_SVID			0x2C /* SE Vendow ID.E-F */
#define EEPWOM_SMID			0x2E /* SE PCI Subsystem ID. 10-11 */

#define EEPWOM_MAC_ADDW			0x16 /* SEMAC Addwess. 12-17 */
#define EEPWOM_MAC_ADDW_MAC0_92D	0x55
#define EEPWOM_MAC_ADDW_MAC1_92D	0x5B

/* 2.4G band Tx powew index setting */
#define EEPWOM_CCK_TX_PWW_INX_2G	0x61
#define EEPWOM_HT40_1S_TX_PWW_INX_2G	0x67
#define EEPWOM_HT40_2S_TX_PWW_INX_DIFF_2G	0x6D
#define EEPWOM_HT20_TX_PWW_INX_DIFF_2G		0x70
#define EEPWOM_OFDM_TX_PWW_INX_DIFF_2G		0x73
#define EEPWOM_HT40_MAX_PWW_OFFSET_2G		0x76
#define EEPWOM_HT20_MAX_PWW_OFFSET_2G		0x79

/*5GW channew 32-64 */
#define EEPWOM_HT40_1S_TX_PWW_INX_5GW		0x7C
#define EEPWOM_HT40_2S_TX_PWW_INX_DIFF_5GW	0x82
#define EEPWOM_HT20_TX_PWW_INX_DIFF_5GW		0x85
#define EEPWOM_OFDM_TX_PWW_INX_DIFF_5GW		0x88
#define EEPWOM_HT40_MAX_PWW_OFFSET_5GW		0x8B
#define EEPWOM_HT20_MAX_PWW_OFFSET_5GW		0x8E

/* 5GM channew 100-140 */
#define EEPWOM_HT40_1S_TX_PWW_INX_5GM		0x91
#define EEPWOM_HT40_2S_TX_PWW_INX_DIFF_5GM	0x97
#define EEPWOM_HT20_TX_PWW_INX_DIFF_5GM		0x9A
#define EEPWOM_OFDM_TX_PWW_INX_DIFF_5GM		0x9D
#define EEPWOM_HT40_MAX_PWW_OFFSET_5GM		0xA0
#define EEPWOM_HT20_MAX_PWW_OFFSET_5GM		0xA3

/* 5GH channew 149-165 */
#define EEPWOM_HT40_1S_TX_PWW_INX_5GH		0xA6
#define EEPWOM_HT40_2S_TX_PWW_INX_DIFF_5GH	0xAC
#define EEPWOM_HT20_TX_PWW_INX_DIFF_5GH		0xAF
#define EEPWOM_OFDM_TX_PWW_INX_DIFF_5GH		0xB2
#define EEPWOM_HT40_MAX_PWW_OFFSET_5GH		0xB5
#define EEPWOM_HT20_MAX_PWW_OFFSET_5GH		0xB8

/* Map of suppowted channews. */
#define EEPWOM_CHANNEW_PWAN			0xBB
#define EEPWOM_IQK_DEWTA			0xBC
#define EEPWOM_WCK_DEWTA			0xBC
#define EEPWOM_XTAW_K				0xBD	/* [7:5] */
#define EEPWOM_TSSI_A_5G			0xBE
#define EEPWOM_TSSI_B_5G			0xBF
#define EEPWOM_TSSI_AB_5G			0xC0
#define EEPWOM_THEWMAW_METEW			0xC3	/* [4:0] */
#define EEPWOM_WF_OPT1				0xC4
#define EEPWOM_WF_OPT2				0xC5
#define EEPWOM_WF_OPT3				0xC6
#define EEPWOM_WF_OPT4				0xC7
#define EEPWOM_WF_OPT5				0xC8
#define EEPWOM_WF_OPT6				0xC9
#define EEPWOM_VEWSION				0xCA
#define EEPWOM_CUSTOMEW_ID			0xCB
#define EEPWOM_WF_OPT7				0xCC

#define EEPWOM_DEF_PAWT_NO			0x3FD    /* Byte */
#define EEPWOME_CHIP_VEWSION_W			0x3FF
#define EEPWOME_CHIP_VEWSION_H			0x3FE

/*
 * Cuwwent IOWEG MAP
 * 0x0000h ~ 0x00FFh   System Configuwation (256 Bytes)
 * 0x0100h ~ 0x01FFh   MACTOP Genewaw Configuwation (256 Bytes)
 * 0x0200h ~ 0x027Fh   TXDMA Configuwation (128 Bytes)
 * 0x0280h ~ 0x02FFh   WXDMA Configuwation (128 Bytes)
 * 0x0300h ~ 0x03FFh   PCIE EMAC Wesewved Wegion (256 Bytes)
 * 0x0400h ~ 0x04FFh   Pwotocow Configuwation (256 Bytes)
 * 0x0500h ~ 0x05FFh   EDCA Configuwation (256 Bytes)
 * 0x0600h ~ 0x07FFh   WMAC Configuwation (512 Bytes)
 * 0x2000h ~ 0x3FFFh   8051 FW Downwoad Wegion (8196 Bytes)
 */

/* ----------------------------------------------------- */
/* 8192C (WCW)	(Offset 0x608, 32 bits) */
/* ----------------------------------------------------- */
#define	WCW_APPFCS				BIT(31)
#define	WCW_APP_MIC				BIT(30)
#define	WCW_APP_ICV				BIT(29)
#define	WCW_APP_PHYST_WXFF			BIT(28)
#define	WCW_APP_BA_SSN				BIT(27)
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
#define	WCW_APWWMGT				BIT(5)
#define	WCW_ADD3				BIT(4)
#define	WCW_AB					BIT(3)
#define	WCW_AM					BIT(2)
#define	WCW_APM					BIT(1)
#define	WCW_AAP					BIT(0)
#define	WCW_MXDMA_OFFSET			8
#define	WCW_FIFO_OFFSET				13

/* ----------------------------------------------------- */
/*       8192C Wegsitew Bit and Content definition	 */
/* ----------------------------------------------------- */
/* ----------------------------------------------------- */
/*	0x0000h ~ 0x00FFh	System Configuwation */
/* ----------------------------------------------------- */

/* SPS0_CTWW */
#define SW18_FPWM				BIT(3)


/* SYS_ISO_CTWW */
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


/* SYS_FUNC_EN */
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

/* APS_FSMCO */
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

/* SYS_CWKW */
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


/* 9346CW */
#define	BOOT_FWOM_EEPWOM			BIT(4)
#define	EEPWOM_EN				BIT(5)

/* AFE_MISC */
#define AFE_BGEN				BIT(0)
#define AFE_MBEN				BIT(1)
#define MAC_ID_EN				BIT(7)

/* WSV_CTWW */
#define WWOCK_AWW				BIT(0)
#define WWOCK_00				BIT(1)
#define WWOCK_04				BIT(2)
#define WWOCK_08				BIT(3)
#define WWOCK_40				BIT(4)
#define W_DIS_PWST_0				BIT(5)
#define W_DIS_PWST_1				BIT(6)
#define WOCK_AWW_EN				BIT(7)

/* WF_CTWW */
#define WF_EN					BIT(0)
#define WF_WSTB					BIT(1)
#define WF_SDMWSTB				BIT(2)



/* WDOA15_CTWW */
#define WDA15_EN				BIT(0)
#define WDA15_STBY				BIT(1)
#define WDA15_OBUF				BIT(2)
#define WDA15_WEG_VOS				BIT(3)
#define _WDA15_VOADJ(x)				(((x) & 0x7) << 4)



/* WDOV12D_CTWW */
#define WDV12_EN				BIT(0)
#define WDV12_SDBY				BIT(1)
#define WPWDO_HSM				BIT(2)
#define WPWDO_WSM_DIS				BIT(3)
#define _WDV12_VADJ(x)				(((x) & 0xF) << 4)


/* AFE_XTAW_CTWW */
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


/* AFE_PWW_CTWW */
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


/* EFUSE_CTWW */
#define AWD_EN					BIT(18)
#define EF_PD					BIT(19)
#define EF_FWAG					BIT(31)

/* EFUSE_TEST  */
#define EF_TWPT					BIT(7)
#define WDOE25_EN				BIT(31)

/* MCUFWDW  */
#define MCUFWDW_EN				BIT(0)
#define MCUFWDW_WDY				BIT(1)
#define FWDW_CHKSUM_WPT				BIT(2)
#define MACINI_WDY				BIT(3)
#define BBINI_WDY				BIT(4)
#define WFINI_WDY				BIT(5)
#define WINTINI_WDY				BIT(6)
#define MAC1_WINTINI_WDY			BIT(11)
#define CPWST					BIT(23)

/*  WEG_SYS_CFG */
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
#define PAD_HWPD_IDN				BIT(22)
#define TWP_VAUX_EN				BIT(23)
#define TWP_BT_EN				BIT(24)
#define BD_PKG_SEW				BIT(25)
#define BD_HCI_SEW				BIT(26)
#define TYPE_ID					BIT(27)

/* WWT_INIT */
#define _WWT_NO_ACTIVE				0x0
#define _WWT_WWITE_ACCESS			0x1
#define _WWT_WEAD_ACCESS			0x2

#define _WWT_INIT_DATA(x)			((x) & 0xFF)
#define _WWT_INIT_ADDW(x)			(((x) & 0xFF) << 8)
#define _WWT_OP(x)				(((x) & 0x3) << 30)
#define _WWT_OP_VAWUE(x)			(((x) >> 30) & 0x3)


/* ----------------------------------------------------- */
/*	0x0400h ~ 0x047Fh	Pwotocow Configuwation	 */
/* ----------------------------------------------------- */
#define	WETWY_WIMIT_SHOWT_SHIFT			8
#define	WETWY_WIMIT_WONG_SHIFT			0


/* ----------------------------------------------------- */
/*	0x0500h ~ 0x05FFh	EDCA Configuwation */
/* ----------------------------------------------------- */
/* EDCA setting */
#define AC_PAWAM_TXOP_WIMIT_OFFSET		16
#define AC_PAWAM_ECW_MAX_OFFSET			12
#define AC_PAWAM_ECW_MIN_OFFSET			8
#define AC_PAWAM_AIFS_OFFSET			0

/* ACMHWCTWW */
#define	ACMHW_HWEN				BIT(0)
#define	ACMHW_BEQEN				BIT(1)
#define	ACMHW_VIQEN				BIT(2)
#define	ACMHW_VOQEN				BIT(3)

/* ----------------------------------------------------- */
/*	0x0600h ~ 0x07FFh	WMAC Configuwation */
/* ----------------------------------------------------- */

/* TCW */
#define TSFWST					BIT(0)
#define DIS_GCWK				BIT(1)
#define PAD_SEW					BIT(2)
#define PWW_ST					BIT(6)
#define PWWBIT_OW_EN				BIT(7)
#define ACWC					BIT(8)
#define CFENDFOWM				BIT(9)
#define ICV					BIT(10)

/* SECCFG */
#define	SCW_TXUSEDK				BIT(0)
#define	SCW_WXUSEDK				BIT(1)
#define	SCW_TXENCENABWE				BIT(2)
#define	SCW_WXENCENABWE				BIT(3)
#define	SCW_SKBYA2				BIT(4)
#define	SCW_NOSKMC				BIT(5)
#define SCW_TXBCUSEDK				BIT(6)
#define SCW_WXBCUSEDK				BIT(7)

/* Genewaw definitions */
#define WAST_ENTWY_OF_TX_PKT_BUFFEW		255
#define WAST_ENTWY_OF_TX_PKT_BUFFEW_DUAW_MAC	127

#define POWWING_WWT_THWESHOWD			20
#define POWWING_WEADY_TIMEOUT_COUNT		1000

/* Min Spacing wewated settings. */
#define	MAX_MSS_DENSITY_2T			0x13
#define	MAX_MSS_DENSITY_1T			0x0A


/* BB-PHY wegistew PMAC 0x100 PHY 0x800 - 0xEFF */
/* 1. PMAC dupwicate wegistew due to connection: */
/*    WF_Mode, TWxWN, NumOf W-STF */
/* 2. 0x800/0x900/0xA00/0xC00/0xD00/0xE00 */
/* 3. WF wegistew 0x00-2E */
/* 4. Bit Mask fow BB/WF wegistew */
/* 5. Othew defintion fow BB/WF W/W */

/* 3. Page8(0x800) */
#define	WFPGA0_WFMOD				0x800

#define	WFPGA0_TXINFO				0x804
#define	WFPGA0_PSDFUNCTION			0x808

#define	WFPGA0_TXGAINSTAGE			0x80c

#define	WFPGA0_WFTIMING1			0x810
#define	WFPGA0_WFTIMING2			0x814

#define	WFPGA0_XA_HSSIPAWAMETEW1		0x820
#define	WFPGA0_XA_HSSIPAWAMETEW2		0x824
#define	WFPGA0_XB_HSSIPAWAMETEW1		0x828
#define	WFPGA0_XB_HSSIPAWAMETEW2		0x82c

#define	WFPGA0_XA_WSSIPAWAMETEW			0x840
#define	WFPGA0_XB_WSSIPAWAMETEW			0x844

#define	WFPGA0_WFWAKEUPPAWAMETEW		0x850
#define	WFPGA0_WFSWEEPUPPAWAMETEW		0x854

#define	WFPGA0_XAB_SWITCHCONTWOW		0x858
#define	WFPGA0_XCD_SWITCHCONTWOW		0x85c

#define	WFPGA0_XA_WFINTEWFACEOE			0x860
#define	WFPGA0_XB_WFINTEWFACEOE			0x864

#define	WFPGA0_XAB_WFINTEWFACESW		0x870
#define	WFPGA0_XCD_WFINTEWFACESW		0x874

#define	WFPGA0_XAB_WFPAWAMETEW			0x878
#define	WFPGA0_XCD_WFPAWAMETEW			0x87c

#define	WFPGA0_ANAWOGPAWAMETEW1			0x880
#define	WFPGA0_ANAWOGPAWAMETEW2			0x884
#define	WFPGA0_ANAWOGPAWAMETEW3			0x888
#define	WFPGA0_ADDAWWOCKEN			0x888
#define	WFPGA0_ANAWOGPAWAMETEW4			0x88c

#define	WFPGA0_XA_WSSIWEADBACK			0x8a0
#define	WFPGA0_XB_WSSIWEADBACK			0x8a4
#define	WFPGA0_XC_WSSIWEADBACK			0x8a8
#define	WFPGA0_XD_WSSIWEADBACK			0x8ac

#define	WFPGA0_PSDWEPOWT			0x8b4
#define	TWANSCEIVEWA_HSPI_WEADBACK		0x8b8
#define	TWANSCEIVEWB_HSPI_WEADBACK		0x8bc
#define	WFPGA0_XAB_WFINTEWFACEWB		0x8e0
#define	WFPGA0_XCD_WFINTEWFACEWB		0x8e4

/* 4. Page9(0x900) */
#define	WFPGA1_WFMOD				0x900

#define	WFPGA1_TXBWOCK				0x904
#define	WFPGA1_DEBUGSEWECT			0x908
#define	WFPGA1_TXINFO				0x90c

/* 5. PageA(0xA00)  */
#define	WCCK0_SYSTEM				0xa00

#define	WCCK0_AFESSTTING			0xa04
#define	WCCK0_CCA				0xa08

#define	WCCK0_WXAGC1				0xa0c
#define	WCCK0_WXAGC2				0xa10

#define	WCCK0_WXHP				0xa14

#define	WCCK0_DSPPAWAMETEW1			0xa18
#define	WCCK0_DSPPAWAMETEW2			0xa1c

#define	WCCK0_TXFIWTEW1				0xa20
#define	WCCK0_TXFIWTEW2				0xa24
#define	WCCK0_DEBUGPOWT				0xa28
#define	WCCK0_FAWSEAWAWMWEPOWT			0xa2c
#define	WCCK0_TWSSIWEPOWT			0xa50
#define	WCCK0_WXWEPOWT				0xa54
#define	WCCK0_FACOUNTEWWOWEW			0xa5c
#define	WCCK0_FACOUNTEWUPPEW			0xa58

/* 6. PageC(0xC00) */
#define	WOFDM0_WSTF				0xc00

#define	WOFDM0_TWXPATHENABWE			0xc04
#define	WOFDM0_TWMUXPAW				0xc08
#define	WOFDM0_TWSWISOWATION			0xc0c

#define	WOFDM0_XAWXAFE				0xc10
#define	WOFDM0_XAWXIQIMBAWANCE			0xc14
#define	WOFDM0_XBWXAFE				0xc18
#define	WOFDM0_XBWXIQIMBAWANCE			0xc1c
#define	WOFDM0_XCWXAFE				0xc20
#define	WOFDM0_XCWXIQIMBAWANCE			0xc24
#define	WOFDM0_XDWXAFE				0xc28
#define	WOFDM0_XDWXIQIMBAWANCE			0xc2c

#define	WOFDM0_WXDETECTOW1			0xc30
#define	WOFDM0_WXDETECTOW2			0xc34
#define	WOFDM0_WXDETECTOW3			0xc38
#define	WOFDM0_WXDETECTOW4			0xc3c

#define	WOFDM0_WXDSP				0xc40
#define	WOFDM0_CFOANDDAGC			0xc44
#define	WOFDM0_CCADWOPTHWESHOWD			0xc48
#define	WOFDM0_ECCATHWESHOWD			0xc4c

#define	WOFDM0_XAAGCCOWE1			0xc50
#define	WOFDM0_XAAGCCOWE2			0xc54
#define	WOFDM0_XBAGCCOWE1			0xc58
#define	WOFDM0_XBAGCCOWE2			0xc5c
#define	WOFDM0_XCAGCCOWE1			0xc60
#define	WOFDM0_XCAGCCOWE2			0xc64
#define	WOFDM0_XDAGCCOWE1			0xc68
#define	WOFDM0_XDAGCCOWE2			0xc6c

#define	WOFDM0_AGCPAWAMETEW1			0xc70
#define	WOFDM0_AGCPAWAMETEW2			0xc74
#define	WOFDM0_AGCWSSITABWE			0xc78
#define	WOFDM0_HTSTFAGC				0xc7c

#define	WOFDM0_XATXIQIMBAWANCE			0xc80
#define	WOFDM0_XATXAFE				0xc84
#define	WOFDM0_XBTXIQIMBAWANCE			0xc88
#define	WOFDM0_XBTXAFE				0xc8c
#define	WOFDM0_XCTXIQIMBAWANCE			0xc90
#define	WOFDM0_XCTXAFE				0xc94
#define	WOFDM0_XDTXIQIMBAWANCE			0xc98
#define	WOFDM0_XDTXAFE				0xc9c

#define	WOFDM0_WXHPPAWAMETEW			0xce0
#define	WOFDM0_TXPSEUDONOISEWGT			0xce4
#define	WOFDM0_FWAMESYNC			0xcf0
#define	WOFDM0_DFSWEPOWT			0xcf4
#define	WOFDM0_TXCOEFF1				0xca4
#define	WOFDM0_TXCOEFF2				0xca8
#define	WOFDM0_TXCOEFF3				0xcac
#define	WOFDM0_TXCOEFF4				0xcb0
#define	WOFDM0_TXCOEFF5				0xcb4
#define	WOFDM0_TXCOEFF6				0xcb8

/* 7. PageD(0xD00) */
#define	WOFDM1_WSTF				0xd00
#define	WOFDM1_TWXPATHENABWE			0xd04

#define	WOFDM1_CFO				0xd08
#define	WOFDM1_CSI1				0xd10
#define	WOFDM1_SBD				0xd14
#define	WOFDM1_CSI2				0xd18
#define	WOFDM1_CFOTWACKING			0xd2c
#define	WOFDM1_TWXMESAUWE1			0xd34
#define	WOFDM1_INTFDET				0xd3c
#define	WOFDM1_PSEUDONOISESTATEAB		0xd50
#define	WOFDM1_PSEUDONOISESTATECD		0xd54
#define	WOFDM1_WXPSEUDONOISEWGT			0xd58

#define	WOFDM_PHYCOUNTEW1			0xda0
#define	WOFDM_PHYCOUNTEW2			0xda4
#define	WOFDM_PHYCOUNTEW3			0xda8

#define	WOFDM_SHOWTCFOAB			0xdac
#define	WOFDM_SHOWTCFOCD			0xdb0
#define	WOFDM_WONGCFOAB				0xdb4
#define	WOFDM_WONGCFOCD				0xdb8
#define	WOFDM_TAIWCFOAB				0xdbc
#define	WOFDM_TAIWCFOCD				0xdc0
#define	WOFDM_PWMEASUWE1			0xdc4
#define	WOFDM_PWMEASUWE2			0xdc8
#define	WOFDM_BWWEPOWT				0xdcc
#define	WOFDM_AGCWEPOWT				0xdd0
#define	WOFDM_WXSNW				0xdd4
#define	WOFDM_WXEVMCSI				0xdd8
#define	WOFDM_SIGWEPOWT				0xddc

/* 8. PageE(0xE00) */
#define	WTXAGC_A_WATE18_06			0xe00
#define	WTXAGC_A_WATE54_24			0xe04
#define	WTXAGC_A_CCK1_MCS32			0xe08
#define	WTXAGC_A_MCS03_MCS00			0xe10
#define	WTXAGC_A_MCS07_MCS04			0xe14
#define	WTXAGC_A_MCS11_MCS08			0xe18
#define	WTXAGC_A_MCS15_MCS12			0xe1c

#define	WTXAGC_B_WATE18_06			0x830
#define	WTXAGC_B_WATE54_24			0x834
#define	WTXAGC_B_CCK1_55_MCS32			0x838
#define	WTXAGC_B_MCS03_MCS00			0x83c
#define	WTXAGC_B_MCS07_MCS04			0x848
#define	WTXAGC_B_MCS11_MCS08			0x84c
#define	WTXAGC_B_MCS15_MCS12			0x868
#define	WTXAGC_B_CCK11_A_CCK2_11		0x86c

/* WW6052 Wegistew definition */
#define	WF_AC					0x00

#define	WF_IQADJ_G1				0x01
#define	WF_IQADJ_G2				0x02
#define	WF_POW_TWSW				0x05

#define	WF_GAIN_WX				0x06
#define	WF_GAIN_TX				0x07

#define	WF_TXM_IDAC				0x08
#define	WF_BS_IQGEN				0x0F

#define	WF_MODE1				0x10
#define	WF_MODE2				0x11

#define	WF_WX_AGC_HP				0x12
#define	WF_TX_AGC				0x13
#define	WF_BIAS					0x14
#define	WF_IPA					0x15
#define	WF_POW_ABIWITY				0x17
#define	WF_MODE_AG				0x18
#define	wfchannew				0x18
#define	WF_CHNWBW				0x18
#define	WF_TOP					0x19

#define	WF_WX_G1				0x1A
#define	WF_WX_G2				0x1B

#define	WF_WX_BB2				0x1C
#define	WF_WX_BB1				0x1D

#define	WF_WCK1					0x1E
#define	WF_WCK2					0x1F

#define	WF_TX_G1				0x20
#define	WF_TX_G2				0x21
#define	WF_TX_G3				0x22

#define	WF_TX_BB1				0x23

#define	WF_T_METEW				0x42

#define	WF_SYN_G1				0x25
#define	WF_SYN_G2				0x26
#define	WF_SYN_G3				0x27
#define	WF_SYN_G4				0x28
#define	WF_SYN_G5				0x29
#define	WF_SYN_G6				0x2A
#define	WF_SYN_G7				0x2B
#define	WF_SYN_G8				0x2C

#define	WF_WCK_OS				0x30

#define	WF_TXPA_G1				0x31
#define	WF_TXPA_G2				0x32
#define	WF_TXPA_G3				0x33

/* Bit Mask */

/* 2. Page8(0x800) */
#define	BWFMOD					0x1
#define	BCCKTXSC				0x30
#define	BCCKEN					0x1000000
#define	BOFDMEN					0x2000000

#define	B3WIWEDATAWENGTH			0x800
#define	B3WIWEADDWESSWENGTH			0x400

#define	BWFSI_WFENV				0x10

#define	BWSSIWEADADDWESS			0x7f800000
#define	BWSSIWEADEDGE				0x80000000
#define	BWSSIWEADBACKDATA			0xfffff
/* 4. PageA(0xA00) */
#define BCCKSIDEBAND				0x10

/* Othew Definition */
#define	BBYTE0					0x1
#define	BBYTE1					0x2
#define	BBYTE2					0x4
#define	BBYTE3					0x8
#define	BWOWD0					0x3
#define	BWOWD1					0xc
#define	BDWOWD					0xf

#endif
