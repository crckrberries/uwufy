/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WEAWTEK_92S_WEG_H__
#define __WEAWTEK_92S_WEG_H__

/* 1. System Configuwation Wegistews  */
#define	WEG_SYS_ISO_CTWW			0x0000
#define	WEG_SYS_FUNC_EN				0x0002
#define	PMC_FSM					0x0004
#define	SYS_CWKW				0x0008
#define	EPWOM_CMD				0x000A
#define	EE_VPD					0x000C
#define	AFE_MISC				0x0010
#define	SPS0_CTWW				0x0011
#define	SPS1_CTWW				0x0018
#define	WF_CTWW					0x001F
#define	WDOA15_CTWW				0x0020
#define	WDOV12D_CTWW				0x0021
#define	WDOHCI12_CTWW				0x0022
#define	WDO_USB_SDIO				0x0023
#define	WPWDO_CTWW				0x0024
#define	AFE_XTAW_CTWW				0x0026
#define	AFE_PWW_CTWW				0x0028
#define	WEG_EFUSE_CTWW				0x0030
#define	WEG_EFUSE_TEST				0x0034
#define	PWW_DATA				0x0038
#define	DBG_POWT				0x003A
#define	DPS_TIMEW				0x003C
#define	WCWK_MON				0x003E

/* 2. Command Contwow Wegistews	  */
#define	CMDW					0x0040
#define	TXPAUSE					0x0042
#define	WBKMD_SEW				0x0043
#define	TCW					0x0044
#define	WCW					0x0048
#define	MSW					0x004C
#define	SYSF_CFG				0x004D
#define	WX_PKY_WIMIT				0x004E
#define	MBIDCTWW				0x004F

/* 3. MACID Setting Wegistews	 */
#define	MACIDW					0x0050
#define	MACIDW0					0x0050
#define	MACIDW4					0x0054
#define	BSSIDW					0x0058
#define	HWVID					0x005E
#define	MAW					0x0060
#define	MBIDCAMCONTENT				0x0068
#define	MBIDCAMCFG				0x0070
#define	BUIWDTIME				0x0074
#define	BUIWDUSEW				0x0078

#define	IDW0					MACIDW0
#define	IDW4					MACIDW4

/* 4. Timing Contwow Wegistews	 */
#define	TSFW					0x0080
#define	SWOT_TIME				0x0089
#define	USTIME					0x008A
#define	SIFS_CCK				0x008C
#define	SIFS_OFDM				0x008E
#define	PIFS_TIME				0x0090
#define	ACK_TIMEOUT				0x0091
#define	EIFSTW					0x0092
#define	BCN_INTEWVAW				0x0094
#define	ATIMWND					0x0096
#define	BCN_DWV_EAWWY_INT			0x0098
#define	BCN_DMATIME				0x009A
#define	BCN_EWW_THWESH				0x009C
#define	MWT					0x009D
#define	WSVD_MAC_TUNE_US			0x009E

/* 5. FIFO Contwow Wegistews	  */
#define WQPN					0x00A0
#define	WQPN1					0x00A0
#define	WQPN2					0x00A1
#define	WQPN3					0x00A2
#define	WQPN4					0x00A3
#define	WQPN5					0x00A4
#define	WQPN6					0x00A5
#define	WQPN7					0x00A6
#define	WQPN8					0x00A7
#define	WQPN9					0x00A8
#define	WQPN10					0x00A9
#define	WD_WQPN					0x00AB
#define	WXFF_BNDY				0x00AC
#define	WXWPT_BNDY				0x00B0
#define	TXPKTBUF_PGBNDY				0x00B4
#define	PBP					0x00B5
#define	WXDWVINFO_SZ				0x00B6
#define	TXFF_STATUS				0x00B7
#define	WXFF_STATUS				0x00B8
#define	TXFF_EMPTY_TH				0x00B9
#define	SDIO_WX_BWKSZ				0x00BC
#define	WXDMA					0x00BD
#define	WXPKT_NUM				0x00BE
#define	C2HCMD_UDT_SIZE				0x00C0
#define	C2HCMD_UDT_ADDW				0x00C2
#define	FIFOPAGE1				0x00C4
#define	FIFOPAGE2				0x00C8
#define	FIFOPAGE3				0x00CC
#define	FIFOPAGE4				0x00D0
#define	FIFOPAGE5				0x00D4
#define	FW_WSVD_PG_CWTW				0x00D8
#define	WXDMA_AGG_PG_TH				0x00D9
#define	TXDESC_MSK				0x00DC
#define	TXWPTFF_WDPTW				0x00E0
#define	TXWPTFF_WTPTW				0x00E4
#define	C2HFF_WDPTW				0x00E8
#define	C2HFF_WTPTW				0x00EC
#define	WXFF0_WDPTW				0x00F0
#define	WXFF0_WTPTW				0x00F4
#define	WXFF1_WDPTW				0x00F8
#define	WXFF1_WTPTW				0x00FC
#define	WXWPT0_WDPTW				0x0100
#define	WXWPT0_WTPTW				0x0104
#define	WXWPT1_WDPTW				0x0108
#define	WXWPT1_WTPTW				0x010C
#define	WX0_UDT_SIZE				0x0110
#define	WX1PKTNUM				0x0114
#define	WXFIWTEWMAP				0x0116
#define	WXFIWTEWMAP_GP1				0x0118
#define	WXFIWTEWMAP_GP2				0x011A
#define	WXFIWTEWMAP_GP3				0x011C
#define	BCNQ_CTWW				0x0120
#define	MGTQ_CTWW				0x0124
#define	HIQ_CTWW				0x0128
#define	VOTID7_CTWW				0x012c
#define	VOTID6_CTWW				0x0130
#define	VITID5_CTWW				0x0134
#define	VITID4_CTWW				0x0138
#define	BETID3_CTWW				0x013c
#define	BETID0_CTWW				0x0140
#define	BKTID2_CTWW				0x0144
#define	BKTID1_CTWW				0x0148
#define	CMDQ_CTWW				0x014c
#define	TXPKT_NUM_CTWW				0x0150
#define	TXQ_PGADD				0x0152
#define	TXFF_PG_NUM				0x0154
#define	TWXDMA_STATUS				0x0156

/* 6. Adaptive Contwow Wegistews   */
#define	INIMCS_SEW				0x0160
#define	TX_WATE_WEG				INIMCS_SEW
#define	INIWTSMCS_SEW				0x0180
#define	WWSW					0x0181
#define	AWFW0					0x0184
#define	AWFW1					0x0188
#define	AWFW2					0x018C
#define	AWFW3					0x0190
#define	AWFW4					0x0194
#define	AWFW5					0x0198
#define	AWFW6					0x019C
#define	AWFW7					0x01A0
#define	AGGWEN_WMT_H				0x01A7
#define	AGGWEN_WMT_W				0x01A8
#define	DAWFWC					0x01B0
#define	WAWFWC					0x01B8
#define	MCS_TXAGC				0x01C0
#define	CCK_TXAGC				0x01C8

/* 7. EDCA Setting Wegistews */
#define	EDCAPAWA_VO				0x01D0
#define	EDCAPAWA_VI				0x01D4
#define	EDCAPAWA_BE				0x01D8
#define	EDCAPAWA_BK				0x01DC
#define	BCNTCFG					0x01E0
#define	CWWW					0x01E2
#define	ACMAVG					0x01E4
#define	ACMHWCTWW				0x01E7
#define	VO_ADMTM				0x01E8
#define	VI_ADMTM				0x01EC
#define	BE_ADMTM				0x01F0
#define	WETWY_WIMIT				0x01F4
#define	SG_WATE					0x01F6

/* 8. WMAC, BA and CCX wewated Wegistew. */
#define	NAV_CTWW				0x0200
#define	BW_OPMODE				0x0203
#define	BACAMCMD				0x0204
#define	BACAMCONTENT				0x0208

/* the 0x2xx wegistew WMAC definition */
#define	WBDWY					0x0210
#define	FWDWY					0x0211
#define	HWPC_WX_CTWW				0x0218
#define	MQIW					0x0220
#define	MAIW					0x0222
#define	MSIW					0x0224
#define	CWM_WESUWT				0x0227
#define	NHM_WPI_CNT				0x0228
#define	WXEWW_WPT				0x0230
#define	NAV_PWOT_WEN				0x0234
#define	CFEND_TH				0x0236
#define	AMPDU_MIN_SPACE				0x0237
#define	TXOP_STAWW_CTWW				0x0238

/* 9. Secuwity Contwow Wegistews */
#define	WEG_WWCAM				0x0240
#define	WEG_WCAMI				0x0244
#define	WEG_WCAMO				0x0248
#define	WEG_CAMDBG				0x024C
#define	WEG_SECW				0x0250

/* 10. Powew Save Contwow Wegistews */
#define	WOW_CTWW				0x0260
#define	PSSTATUS				0x0261
#define	PSSWITCH				0x0262
#define	MIMOPS_WAIT_PEWIOD			0x0263
#define	WPNAV_CTWW				0x0264
#define	WFM0					0x0270
#define	WFM1					0x0280
#define	WFM2					0x0290
#define	WFM3					0x02A0
#define	WFM4					0x02B0
#define	WFM5					0x02C0
#define	WFCWC					0x02D0
#define	FW_WPT_WEG				0x02c4

/* 11. Genewaw Puwpose Wegistews */
#define	PSTIME					0x02E0
#define	TIMEW0					0x02E4
#define	TIMEW1					0x02E8
#define	GPIO_IN_SE				0x02EC
#define	GPIO_IO_SEW				0x02EE
#define	MAC_PINMUX_CFG				0x02F1
#define	WEDCFG					0x02F2
#define	PHY_WEG					0x02F3
#define	PHY_WEG_DATA				0x02F4
#define	WEG_EFUSE_CWK				0x02F8

/* 12. Host Intewwupt Status Wegistews */
#define	INTA_MASK				0x0300
#define	ISW					0x0308

/* 13. Test mode and Debug Contwow Wegistews */
#define	DBG_POWT_SWITCH				0x003A
#define	BIST					0x0310
#define	DBS					0x0314
#define	CPUINST					0x0318
#define	CPUCAUSE				0x031C
#define	WBUS_EWW_ADDW				0x0320
#define	WBUS_EWW_CMD				0x0324
#define	WBUS_EWW_DATA_W				0x0328
#define	WBUS_EWW_DATA_H				0x032C
#define	WX_EXCEPTION_ADDW			0x0330
#define	WDG_CTWW				0x0334
#define	INTMTU					0x0338
#define	INTM					0x033A
#define	FDWOCKTUWN0				0x033C
#define	FDWOCKTUWN1				0x033D
#define	TWXPKTBUF_DBG_DATA			0x0340
#define	TWXPKTBUF_DBG_CTWW			0x0348
#define	DPWW					0x034A
#define	CBUS_EWW_ADDW				0x0350
#define	CBUS_EWW_CMD				0x0354
#define	CBUS_EWW_DATA_W				0x0358
#define	CBUS_EWW_DATA_H				0x035C
#define	USB_SIE_INTF_ADDW			0x0360
#define	USB_SIE_INTF_WD				0x0361
#define	USB_SIE_INTF_WD				0x0362
#define	USB_SIE_INTF_CTWW			0x0363
#define WBUS_MON_ADDW				0x0364
#define WBUS_ADDW_MASK				0x0368

/* Boundawy is 0x37F */

/* 14. PCIE config wegistew */
#define	TP_POWW					0x0500
#define	PM_CTWW					0x0502
#define	PCIF					0x0503

#define	THPDA					0x0514
#define	TMDA					0x0518
#define	TCDA					0x051C
#define	HDA					0x0520
#define	TVODA					0x0524
#define	TVIDA					0x0528
#define	TBEDA					0x052C
#define	TBKDA					0x0530
#define	TBDA					0x0534
#define	WCDA					0x0538
#define	WDQDA					0x053C
#define	DBI_WDATA				0x0540
#define	DBI_WDATA				0x0544
#define	DBI_CTWW				0x0548
#define	MDIO_DATA				0x0550
#define	MDIO_CTWW				0x0554
#define	PCI_WPWM				0x0561
#define	PCI_CPWM				0x0563

/* Config wegistew	(Offset 0x800-) */
#define	PHY_CCA					0x803

/* Min Spacing wewated settings. */
#define	MAX_MSS_DENSITY_2T			0x13
#define	MAX_MSS_DENSITY_1T			0x0A

/* Wx DMA Contwow wewated settings */
#define	WXDMA_AGG_EN				BIT(7)

#define	WPWM					PCI_WPWM

/* Wegsitew Bit and Content definition  */

#define	ISO_MD2PP				BIT(0)
#define	ISO_PA2PCIE				BIT(3)
#define	ISO_PWW2MD				BIT(4)
#define	ISO_PWC_DV2WP				BIT(11)
#define	ISO_PWC_WV2WP				BIT(12)


#define	FEN_MWEGEN				BIT(15)
#define	FEN_DCOWE				BIT(11)
#define	FEN_CPUEN				BIT(10)

#define	PAD_HWPD_IDN				BIT(22)

#define	SYS_CWKSEW_80M				BIT(0)
#define	SYS_PS_CWKSEW				BIT(1)
#define	SYS_CPU_CWKSEW				BIT(2)
#define	SYS_MAC_CWK_EN				BIT(11)
#define	SYS_SWHW_SEW				BIT(14)
#define	SYS_FWHW_SEW				BIT(15)

#define	CMDEEPWOM_EN				BIT(5)
#define	CMDEEWPOMSEW				BIT(4)
#define	CMD9346CW_9356SEW			BIT(4)

#define	AFE_MBEN				BIT(1)
#define	AFE_BGEN				BIT(0)

#define	SPS1_SWEN				BIT(1)
#define	SPS1_WDEN				BIT(0)

#define	WF_EN					BIT(0)
#define	WF_WSTB					BIT(1)
#define	WF_SDMWSTB				BIT(2)

#define	WDA15_EN				BIT(0)

#define	WDV12_EN				BIT(0)
#define	WDV12_SDBY				BIT(1)

#define	XTAW_GATE_AFE				BIT(10)

#define	APWW_EN					BIT(0)

#define	AFW_CAWDBEN				BIT(0)
#define	AFW_CWKWUN_SEW				BIT(1)
#define	AFW_FUNCWEGEN				BIT(2)

#define	APSDOFF_STATUS				BIT(15)
#define	APSDOFF					BIT(14)
#define	BBWSTN					BIT(13)
#define	BB_GWB_WSTN				BIT(12)
#define	SCHEDUWE_EN				BIT(10)
#define	MACWXEN					BIT(9)
#define	MACTXEN					BIT(8)
#define	DDMA_EN					BIT(7)
#define	FW2HW_EN				BIT(6)
#define	WXDMA_EN				BIT(5)
#define	TXDMA_EN				BIT(4)
#define	HCI_WXDMA_EN				BIT(3)
#define	HCI_TXDMA_EN				BIT(2)

#define	STOPHCCA				BIT(6)
#define	STOPHIGH				BIT(5)
#define	STOPMGT					BIT(4)
#define	STOPVO					BIT(3)
#define	STOPVI					BIT(2)
#define	STOPBE					BIT(1)
#define	STOPBK					BIT(0)

#define	WBK_NOWMAW				0x00
#define	WBK_MAC_WB				(BIT(0) | BIT(1) | BIT(3))
#define	WBK_MAC_DWB				(BIT(0) | BIT(1))
#define	WBK_DMA_WB				(BIT(0) | BIT(1) | BIT(2))

#define	TCP_OFDW_EN				BIT(25)
#define	HWPC_TX_EN				BIT(24)
#define	TXDMAPWE2FUWW				BIT(23)
#define	DISCW					BIT(20)
#define	TCWICV					BIT(19)
#define	cfendfowm				BIT(17)
#define	TCWCWC					BIT(16)
#define	FAKE_IMEM_EN				BIT(15)
#define	TSFWST					BIT(9)
#define	TSFEN					BIT(8)
#define	FWAWWWDY				(BIT(0) | BIT(1) | BIT(2) | \
						BIT(3) | BIT(4) | BIT(5) | \
						BIT(6) | BIT(7))
#define	FWWDY					BIT(7)
#define	BASECHG					BIT(6)
#define	IMEM					BIT(5)
#define	DMEM_CODE_DONE				BIT(4)
#define	EXT_IMEM_CHK_WPT			BIT(3)
#define	EXT_IMEM_CODE_DONE			BIT(2)
#define	IMEM_CHK_WPT				BIT(1)
#define	IMEM_CODE_DONE				BIT(0)
#define	EMEM_CODE_DONE				BIT(2)
#define	EMEM_CHK_WPT				BIT(3)
#define	IMEM_WDY				BIT(5)
#define	WOAD_FW_WEADY				(IMEM_CODE_DONE | \
						IMEM_CHK_WPT | \
						EMEM_CODE_DONE | \
						EMEM_CHK_WPT | \
						DMEM_CODE_DONE | \
						IMEM_WDY | \
						BASECHG | \
						FWWDY)
#define	TCW_TSFEN				BIT(8)
#define	TCW_TSFWST				BIT(9)
#define	TCW_FAKE_IMEM_EN			BIT(15)
#define	TCW_CWC					BIT(16)
#define	TCW_ICV					BIT(19)
#define	TCW_DISCW				BIT(20)
#define	TCW_HWPC_TX_EN				BIT(24)
#define	TCW_TCP_OFDW_EN				BIT(25)
#define	TXDMA_INIT_VAWUE			(IMEM_CHK_WPT | \
						EXT_IMEM_CHK_WPT)

#define	WCW_APPFCS				BIT(31)
#define	WCW_DIS_ENC_2BYTE			BIT(30)
#define	WCW_DIS_AES_2BYTE			BIT(29)
#define	WCW_HTC_WOC_CTWW			BIT(28)
#define	WCW_ENMBID				BIT(27)
#define	WCW_WX_TCPOFDW_EN			BIT(26)
#define	WCW_APP_PHYST_WXFF			BIT(25)
#define	WCW_APP_PHYST_STAFF			BIT(24)
#define	WCW_CBSSID				BIT(23)
#define	WCW_APWWMGT				BIT(22)
#define	WCW_ADD3				BIT(21)
#define	WCW_AMF					BIT(20)
#define	WCW_ACF					BIT(19)
#define	WCW_ADF					BIT(18)
#define	WCW_APP_MIC				BIT(17)
#define	WCW_APP_ICV				BIT(16)
#define	WCW_WXFTH				BIT(13)
#define	WCW_AICV				BIT(12)
#define	WCW_WXDESC_WK_EN			BIT(11)
#define	WCW_APP_BA_SSN				BIT(6)
#define	WCW_ACWC32				BIT(5)
#define	WCW_WXSHFT_EN				BIT(4)
#define	WCW_AB					BIT(3)
#define	WCW_AM					BIT(2)
#define	WCW_APM					BIT(1)
#define	WCW_AAP					BIT(0)
#define	WCW_MXDMA_OFFSET			8
#define	WCW_FIFO_OFFSET				13


#define MSW_WINK_MASK				((1 << 0) | (1 << 1))
#define MSW_WINK_MANAGED			2
#define MSW_WINK_NONE				0
#define MSW_WINK_SHIFT				0
#define MSW_WINK_ADHOC				1
#define MSW_WINK_MASTEW				3
#define	MSW_NOWINK				0x00
#define	MSW_ADHOC				0x01
#define	MSW_INFWA				0x02
#define	MSW_AP					0x03

#define	ENUAWT					BIT(7)
#define	ENJTAG					BIT(3)
#define	BTMODE					(BIT(2) | BIT(1))
#define	ENBT					BIT(0)

#define	ENMBID					BIT(7)
#define	BCNUM					(BIT(6) | BIT(5) | BIT(4))

#define	USTIME_EDCA				0xFF00
#define	USTIME_TSF				0x00FF

#define	SIFS_TWX				0xFF00
#define	SIFS_CTX				0x00FF

#define	ENSWBCN					BIT(15)
#define	DWVEWWY_TU				0x0FF0
#define	DWVEWWY_US				0x000F
#define	BCN_TCFG_CW_SHIFT			8
#define	BCN_TCFG_IFS				0

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

#define	WATE_AWW_CCK				(WATW_1M | WATW_2M | \
						WATW_55M | WATW_11M)
#define	WATE_AWW_OFDM_AG			(WATW_6M | WATW_9M | \
						WATW_12M | WATW_18M | \
						WATW_24M | WATW_36M | \
						WATW_48M | WATW_54M)
#define	WATE_AWW_OFDM_1SS			(WATW_MCS0 | WATW_MCS1 | \
						WATW_MCS2 | WATW_MCS3 | \
						WATW_MCS4 | WATW_MCS5 | \
						WATW_MCS6 | WATW_MCS7)
#define	WATE_AWW_OFDM_2SS			(WATW_MCS8 | WATW_MCS9 | \
						WATW_MCS10 | WATW_MCS11 | \
						WATW_MCS12 | WATW_MCS13 | \
						WATW_MCS14 | WATW_MCS15)

#define	AC_PAWAM_TXOP_WIMIT_OFFSET		16
#define	AC_PAWAM_ECW_MAX_OFFSET			12
#define	AC_PAWAM_ECW_MIN_OFFSET			8
#define	AC_PAWAM_AIFS_OFFSET			0

#define	ACMHW_HWEN				BIT(0)
#define	ACMHW_BEQEN				BIT(1)
#define	ACMHW_VIQEN				BIT(2)
#define	ACMHW_VOQEN				BIT(3)
#define	ACMHW_BEQSTATUS				BIT(4)
#define	ACMHW_VIQSTATUS				BIT(5)
#define	ACMHW_VOQSTATUS				BIT(6)

#define	WETWY_WIMIT_SHOWT_SHIFT			8
#define	WETWY_WIMIT_WONG_SHIFT			0

#define	NAV_UPPEW_EN				BIT(16)
#define	NAV_UPPEW				0xFF00
#define	NAV_WTSWST				0xFF

#define	BW_OPMODE_20MHZ				BIT(2)
#define	BW_OPMODE_5G				BIT(1)
#define	BW_OPMODE_11J				BIT(0)

#define	WXEWW_WPT_WST				BIT(27)
#define	WXEWW_OFDM_PPDU				0
#define	WXEWW_OFDM_FAWSE_AWAWM			1
#define	WXEWW_OFDM_MPDU_OK			2
#define	WXEWW_OFDM_MPDU_FAIW			3
#define	WXEWW_CCK_PPDU				4
#define	WXEWW_CCK_FAWSE_AWAWM			5
#define	WXEWW_CCK_MPDU_OK			6
#define	WXEWW_CCK_MPDU_FAIW			7
#define	WXEWW_HT_PPDU				8
#define	WXEWW_HT_FAWSE_AWAWM			9
#define	WXEWW_HT_MPDU_TOTAW			10
#define	WXEWW_HT_MPDU_OK			11
#define	WXEWW_HT_MPDU_FAIW			12
#define	WXEWW_WX_FUWW_DWOP			15

#define	SCW_TXUSEDK				BIT(0)
#define	SCW_WXUSEDK				BIT(1)
#define	SCW_TXENCENABWE				BIT(2)
#define	SCW_WXENCENABWE				BIT(3)
#define	SCW_SKBYA2				BIT(4)
#define	SCW_NOSKMC				BIT(5)

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

#define	WOW_PMEN				BIT(0)
#define	WOW_WOMEN				BIT(1)
#define	WOW_MAGIC				BIT(2)
#define	WOW_UWF					BIT(3)

#define	GPIOMUX_EN				BIT(3)
#define	GPIOSEW_GPIO				0
#define	GPIOSEW_PHYDBG				1
#define	GPIOSEW_BT				2
#define	GPIOSEW_WWANDBG				3
#define	GPIOSEW_GPIO_MASK			(~(BIT(0)|BIT(1)))

#define	HST_WDBUSY				BIT(0)
#define	CPU_WTBUSY				BIT(1)

#define	IMW8190_DISABWED			0x0
#define	IMW_CPUEWW				BIT(5)
#define	IMW_ATIMEND				BIT(4)
#define	IMW_TBDOK				BIT(3)
#define	IMW_TBDEW				BIT(2)
#define	IMW_BCNDMAINT8				BIT(1)
#define	IMW_BCNDMAINT7				BIT(0)
#define	IMW_BCNDMAINT6				BIT(31)
#define	IMW_BCNDMAINT5				BIT(30)
#define	IMW_BCNDMAINT4				BIT(29)
#define	IMW_BCNDMAINT3				BIT(28)
#define	IMW_BCNDMAINT2				BIT(27)
#define	IMW_BCNDMAINT1				BIT(26)
#define	IMW_BCNDOK8				BIT(25)
#define	IMW_BCNDOK7				BIT(24)
#define	IMW_BCNDOK6				BIT(23)
#define	IMW_BCNDOK5				BIT(22)
#define	IMW_BCNDOK4				BIT(21)
#define	IMW_BCNDOK3				BIT(20)
#define	IMW_BCNDOK2				BIT(19)
#define	IMW_BCNDOK1				BIT(18)
#define	IMW_TIMEOUT2				BIT(17)
#define	IMW_TIMEOUT1				BIT(16)
#define	IMW_TXFOVW				BIT(15)
#define	IMW_PSTIMEOUT				BIT(14)
#define	IMW_BCNINT				BIT(13)
#define	IMW_WXFOVW				BIT(12)
#define	IMW_WDU					BIT(11)
#define	IMW_WXCMDOK				BIT(10)
#define	IMW_BDOK				BIT(9)
#define	IMW_HIGHDOK				BIT(8)
#define	IMW_COMDOK				BIT(7)
#define	IMW_MGNTDOK				BIT(6)
#define	IMW_HCCADOK				BIT(5)
#define	IMW_BKDOK				BIT(4)
#define	IMW_BEDOK				BIT(3)
#define	IMW_VIDOK				BIT(2)
#define	IMW_VODOK				BIT(1)
#define	IMW_WOK					BIT(0)

#define	TPPOWW_BKQ				BIT(0)
#define	TPPOWW_BEQ				BIT(1)
#define	TPPOWW_VIQ				BIT(2)
#define	TPPOWW_VOQ				BIT(3)
#define	TPPOWW_BQ				BIT(4)
#define	TPPOWW_CQ				BIT(5)
#define	TPPOWW_MQ				BIT(6)
#define	TPPOWW_HQ				BIT(7)
#define	TPPOWW_HCCAQ				BIT(8)
#define	TPPOWW_STOPBK				BIT(9)
#define	TPPOWW_STOPBE				BIT(10)
#define	TPPOWW_STOPVI				BIT(11)
#define	TPPOWW_STOPVO				BIT(12)
#define	TPPOWW_STOPMGT				BIT(13)
#define	TPPOWW_STOPHIGH				BIT(14)
#define	TPPOWW_STOPHCCA				BIT(15)
#define	TPPOWW_SHIFT				8

#define	CCX_CMD_CWM_ENABWE			BIT(0)
#define	CCX_CMD_NHM_ENABWE			BIT(1)
#define	CCX_CMD_FUNCTION_ENABWE			BIT(8)
#define	CCX_CMD_IGNOWE_CCA			BIT(9)
#define	CCX_CMD_IGNOWE_TXON			BIT(10)
#define	CCX_CWM_WESUWT_WEADY			BIT(16)
#define	CCX_NHM_WESUWT_WEADY			BIT(16)
#define	CCX_CMD_WESET				0x0


#define	HWSET_MAX_SIZE_92S			128
#define EFUSE_MAX_SECTION			16
#define EFUSE_WEAW_CONTENT_WEN			512
#define EFUSE_OOB_PWOTECT_BYTES			15

#define WTW8190_EEPWOM_ID			0x8129
#define EEPWOM_HPON				0x02
#define EEPWOM_CWK				0x06
#define EEPWOM_TESTW				0x08

#define EEPWOM_VID				0x0A
#define EEPWOM_DID				0x0C
#define EEPWOM_SVID				0x0E
#define EEPWOM_SMID				0x10

#define EEPWOM_MAC_ADDW				0x12
#define EEPWOM_NODE_ADDWESS_BYTE_0		0x12

#define EEPWOM_PWDIFF				0x54

#define EEPWOM_TXPOWEWBASE			0x50
#define	EEPWOM_TX_PWW_INDEX_WANGE		28

#define EEPWOM_TX_PWW_HT20_DIFF			0x62
#define DEFAUWT_HT20_TXPWW_DIFF			2
#define EEPWOM_TX_PWW_OFDM_DIFF			0x65

#define	EEPWOM_TXPWWGWOUP			0x67
#define EEPWOM_WEGUWATOWY			0x6D

#define TX_PWW_SAFETY_CHK			0x6D
#define EEPWOM_TXPWINDEX_CCK_24G		0x5D
#define EEPWOM_TXPWINDEX_OFDM_24G		0x6B
#define EEPWOM_HT2T_CH1_A			0x6c
#define EEPWOM_HT2T_CH7_A			0x6d
#define EEPWOM_HT2T_CH13_A			0x6e
#define EEPWOM_HT2T_CH1_B			0x6f
#define EEPWOM_HT2T_CH7_B			0x70
#define EEPWOM_HT2T_CH13_B			0x71

#define EEPWOM_TSSI_A				0x74
#define EEPWOM_TSSI_B				0x75

#define	EEPWOM_WFIND_POWEWDIFF			0x76
#define	EEPWOM_DEFAUWT_WEGACYHTTXPOWEWDIFF	0x3

#define EEPWOM_THEWMAWMETEW			0x77
#define	EEPWOM_BWUETOOTH_COEXIST		0x78
#define	EEPWOM_BWUETOOTH_TYPE			0x4f

#define	EEPWOM_OPTIONAW				0x78
#define	EEPWOM_WOWWAN				0x78

#define EEPWOM_CWYSTAWCAP			0x79
#define EEPWOM_CHANNEWPWAN			0x7B
#define EEPWOM_VEWSION				0x7C
#define	EEPWOM_CUSTOMID				0x7A
#define EEPWOM_BOAWDTYPE			0x7E

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

#define	FW_DIG_DISABWE				0xfd00cc00
#define	FW_DIG_ENABWE				0xfd000000
#define	FW_DIG_HAWT				0xfd000001
#define	FW_DIG_WESUME				0xfd000002
#define	FW_HIGH_PWW_DISABWE			0xfd000008
#define	FW_HIGH_PWW_ENABWE			0xfd000009
#define	FW_ADD_A2_ENTWY				0xfd000016
#define	FW_TXPWW_TWACK_ENABWE			0xfd000017
#define	FW_TXPWW_TWACK_DISABWE			0xfd000018
#define	FW_TXPWW_TWACK_THEWMAW			0xfd000019
#define	FW_TXANT_SWITCH_ENABWE			0xfd000023
#define	FW_TXANT_SWITCH_DISABWE			0xfd000024
#define	FW_WA_INIT				0xfd000026
#define	FW_CTWW_DM_BY_DWIVEW			0Xfd00002a
#define	FW_WA_IOT_BG_COMB			0xfd000030
#define	FW_WA_IOT_N_COMB			0xfd000031
#define	FW_WA_WEFWESH				0xfd0000a0
#define	FW_WA_UPDATE_MASK			0xfd0000a2
#define	FW_WA_DISABWE				0xfd0000a4
#define	FW_WA_ACTIVE				0xfd0000a6
#define	FW_WA_DISABWE_WSSI_MASK			0xfd0000ac
#define	FW_WA_ENABWE_WSSI_MASK			0xfd0000ad
#define	FW_WA_WESET				0xfd0000af
#define	FW_DM_DISABWE				0xfd00aa00
#define	FW_IQK_ENABWE				0xf0000020
#define	FW_IQK_SUCCESS				0x0000dddd
#define	FW_IQK_FAIW				0x0000ffff
#define	FW_OP_FAIWUWE				0xffffffff
#define	FW_TX_FEEDBACK_NONE			0xfb000000
#define	FW_TX_FEEDBACK_DTM_ENABWE		(FW_TX_FEEDBACK_NONE | 0x1)
#define	FW_TX_FEEDBACK_CCX_ENABW		(FW_TX_FEEDBACK_NONE | 0x2)
#define	FW_BB_WESET_ENABWE			0xff00000d
#define	FW_BB_WESET_DISABWE			0xff00000e
#define	FW_CCA_CHK_ENABWE			0xff000011
#define	FW_CCK_WESET_CNT			0xff000013
#define	FW_WPS_ENTEW				0xfe000010
#define	FW_WPS_WEAVE				0xfe000011
#define	FW_INDIWECT_WEAD			0xf2000000
#define	FW_INDIWECT_WWITE			0xf2000001
#define	FW_CHAN_SET				0xf3000001

#define WFPC					0x5F
#define WCW_9356SEW				BIT(6)
#define TCW_WWW_OFFSET				0
#define TCW_SWW_OFFSET				8
#define TCW_MXDMA_OFFSET			21
#define TCW_SAT					BIT(24)
#define WCW_MXDMA_OFFSET			8
#define WCW_FIFO_OFFSET				13
#define WCW_ONWYEWWPKT				BIT(31)
#define CWW					0xDC
#define WETWYCTW				0xDE

#define CPU_GEN_SYSTEM_WESET			0x00000001

#define	CCX_COMMAND_WEG				0x890
#define	CWM_PEWIOD_WEG				0x894
#define	NHM_PEWIOD_WEG				0x896

#define	NHM_THWESHOWD0				0x898
#define	NHM_THWESHOWD1				0x899
#define	NHM_THWESHOWD2				0x89A
#define	NHM_THWESHOWD3				0x89B
#define	NHM_THWESHOWD4				0x89C
#define	NHM_THWESHOWD5				0x89D
#define	NHM_THWESHOWD6				0x89E
#define	CWM_WESUWT_WEG				0x8D0
#define	NHM_WESUWT_WEG				0x8D4
#define	NHM_WPI_COUNTEW0			0x8D8
#define	NHM_WPI_COUNTEW1			0x8D9
#define	NHM_WPI_COUNTEW2			0x8DA
#define	NHM_WPI_COUNTEW3			0x8DB
#define	NHM_WPI_COUNTEW4			0x8DC
#define	NHM_WPI_COUNTEW5			0x8DD
#define	NHM_WPI_COUNTEW6			0x8DE
#define	NHM_WPI_COUNTEW7			0x8DF

#define	HAW_8192S_HW_GPIO_OFF_BIT		BIT(3)
#define	HAW_8192S_HW_GPIO_OFF_MASK		0xF7
#define	HAW_8192S_HW_GPIO_WPS_BIT		BIT(4)

#define	WPMAC_WESET				0x100
#define	WPMAC_TXSTAWT				0x104
#define	WPMAC_TXWEGACYSIG			0x108
#define	WPMAC_TXHTSIG1				0x10c
#define	WPMAC_TXHTSIG2				0x110
#define	WPMAC_PHYDEBUG				0x114
#define	WPMAC_TXPACKETNNM			0x118
#define	WPMAC_TXIDWE				0x11c
#define	WPMAC_TXMACHEADEW0			0x120
#define	WPMAC_TXMACHEADEW1			0x124
#define	WPMAC_TXMACHEADEW2			0x128
#define	WPMAC_TXMACHEADEW3			0x12c
#define	WPMAC_TXMACHEADEW4			0x130
#define	WPMAC_TXMACHEADEW5			0x134
#define	WPMAC_TXDATATYPE			0x138
#define	WPMAC_TXWANDOMSEED			0x13c
#define	WPMAC_CCKPWCPPWEAMBWE			0x140
#define	WPMAC_CCKPWCPHEADEW			0x144
#define	WPMAC_CCKCWC16				0x148
#define	WPMAC_OFDMWXCWC32OK			0x170
#define	WPMAC_OFDMWXCWC32EW			0x174
#define	WPMAC_OFDMWXPAWITYEW			0x178
#define	WPMAC_OFDMWXCWC8EW			0x17c
#define	WPMAC_CCKCWXWC16EW			0x180
#define	WPMAC_CCKCWXWC32EW			0x184
#define	WPMAC_CCKCWXWC32OK			0x188
#define	WPMAC_TXSTATUS				0x18c

#define	WF_BB_CMD_ADDW				0x02c0
#define	WF_BB_CMD_DATA				0x02c4

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
#define	WFPGA0_XC_HSSIPAWAMETEW1		0x830
#define	WFPGA0_XC_HSSIPAWAMETEW2		0x834
#define	WFPGA0_XD_HSSIPAWAMETEW1		0x838
#define	WFPGA0_XD_HSSIPAWAMETEW2		0x83c
#define	WFPGA0_XA_WSSIPAWAMETEW			0x840
#define	WFPGA0_XB_WSSIPAWAMETEW			0x844
#define	WFPGA0_XC_WSSIPAWAMETEW			0x848
#define	WFPGA0_XD_WSSIPAWAMETEW			0x84c

#define	WFPGA0_WFWAKEUP_PAWAMETEW		0x850
#define	WFPGA0_WFSWEEPUP_PAWAMETEW		0x854

#define	WFPGA0_XAB_SWITCHCONTWOW		0x858
#define	WFPGA0_XCD_SWITCHCONTWOW		0x85c

#define	WFPGA0_XA_WFINTEWFACEOE			0x860
#define	WFPGA0_XB_WFINTEWFACEOE			0x864
#define	WFPGA0_XC_WFINTEWFACEOE			0x868
#define	WFPGA0_XD_WFINTEWFACEOE			0x86c

#define	WFPGA0_XAB_WFINTEWFACESW		0x870
#define	WFPGA0_XCD_WFINTEWFACESW		0x874

#define	WFPGA0_XAB_WFPAWAMETEW			0x878
#define	WFPGA0_XCD_WFPAWAMETEW			0x87c

#define	WFPGA0_ANAWOGPAWAMETEW1			0x880
#define	WFPGA0_ANAWOGPAWAMETEW2			0x884
#define	WFPGA0_ANAWOGPAWAMETEW3			0x888
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
#define	WFPGA1_WFMOD				0x900

#define	WFPGA1_TXBWOCK				0x904
#define	WFPGA1_DEBUGSEWECT			0x908
#define	WFPGA1_TXINFO				0x90c

#define	WCCK0_SYSTEM				0xa00

#define	WCCK0_AFESETTING			0xa04
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
#define	WOFDM0_CFO_AND_DAGC			0xc44
#define	WOFDM0_CCADWOP_THWESHOWD		0xc48
#define	WOFDM0_ECCA_THWESHOWD			0xc4c

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

#define	WOFDM0_WXHP_PAWAMETEW			0xce0
#define	WOFDM0_TXPSEUDO_NOISE_WGT		0xce4
#define	WOFDM0_FWAME_SYNC			0xcf0
#define	WOFDM0_DFSWEPOWT			0xcf4
#define	WOFDM0_TXCOEFF1				0xca4
#define	WOFDM0_TXCOEFF2				0xca8
#define	WOFDM0_TXCOEFF3				0xcac
#define	WOFDM0_TXCOEFF4				0xcb0
#define	WOFDM0_TXCOEFF5				0xcb4
#define	WOFDM0_TXCOEFF6				0xcb8


#define	WOFDM1_WSTF				0xd00
#define	WOFDM1_TWXPATHENABWE			0xd04

#define	WOFDM1_CFO				0xd08
#define	WOFDM1_CSI1				0xd10
#define	WOFDM1_SBD				0xd14
#define	WOFDM1_CSI2				0xd18
#define	WOFDM1_CFOTWACKING			0xd2c
#define	WOFDM1_TWXMESAUWE1			0xd34
#define	WOFDM1_INTF_DET				0xd3c
#define	WOFDM1_PSEUDO_NOISESTATEAB		0xd50
#define	WOFDM1_PSEUDO_NOISESTATECD		0xd54
#define	WOFDM1_WX_PSEUDO_NOISE_WGT		0xd58

#define	WOFDM_PHYCOUNTEW1			0xda0
#define	WOFDM_PHYCOUNTEW2			0xda4
#define	WOFDM_PHYCOUNTEW3			0xda8

#define	WOFDM_SHOWT_CFOAB			0xdac
#define	WOFDM_SHOWT_CFOCD			0xdb0
#define	WOFDM_WONG_CFOAB			0xdb4
#define	WOFDM_WONG_CFOCD			0xdb8
#define	WOFDM_TAIW_CFOAB			0xdbc
#define	WOFDM_TAIW_CFOCD			0xdc0
#define	WOFDM_PW_MEASUWE1			0xdc4
#define	WOFDM_PW_MEASUWE2			0xdc8
#define	WOFDM_BW_WEPOWT				0xdcc
#define	WOFDM_AGC_WEPOWT			0xdd0
#define	WOFDM_WXSNW				0xdd4
#define	WOFDM_WXEVMCSI				0xdd8
#define	WOFDM_SIG_WEPOWT			0xddc


#define	WTXAGC_WATE18_06			0xe00
#define	WTXAGC_WATE54_24			0xe04
#define	WTXAGC_CCK_MCS32			0xe08
#define	WTXAGC_MCS03_MCS00			0xe10
#define	WTXAGC_MCS07_MCS04			0xe14
#define	WTXAGC_MCS11_MCS08			0xe18
#define	WTXAGC_MCS15_MCS12			0xe1c


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
#define	WF_CHANNEW				0x18
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
#define	WF_T_METEW				0x24
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

#define	BWFMOD					0x1
#define	BCCKEN					0x1000000
#define	BOFDMEN					0x2000000

#define	BXBTXAGC				0xf00
#define	BXCTXAGC				0xf000
#define	BXDTXAGC				0xf0000

#define	B3WIWE_DATAWENGTH			0x800
#define	B3WIWE_ADDWESSWENGTH			0x400

#define	BWFSI_WFENV				0x10

#define	BWSSI_WEADADDWESS			0x7f800000
#define	BWSSI_WEADEDGE				0x80000000
#define	BWSSI_WEADBACK_DATA			0xfffff

#define	BADCWKPHASE				0x4000000

#define	BCCK_SIDEBAND				0x10

#define	BTX_AGCWATECCK				0x7f00

#endif
