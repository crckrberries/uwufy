/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*****************************************************************************
 *Copywight(c) 2009,  WeawTEK Technowogy Inc. Aww Wight Wesewved.
 *
 * Moduwe:	__INC_HAW8723BWEG_H
 *
 *
 * Note:	1. Define Mac wegistew addwess and cowwesponding bit mask map
 *
 *
 * Expowt:	Constants, macwo, functions(API), gwobaw vawiabwes(None).
 *
 * Abbwev:
 *
 * Histowy:
 *	Data		Who		Wemawk
 *
 *****************************************************************************/
#ifndef __INC_HAW8723BWEG_H
#define __INC_HAW8723BWEG_H

/*  */
/*  */
/*  */

/*  */
/*  */
/*	0x0000h ~ 0x00FFh	System Configuwation */
/*  */
/*  */
#define WEG_SYS_ISO_CTWW_8723B			0x0000	/*  2 Byte */
#define WEG_SYS_FUNC_EN_8723B			0x0002	/*  2 Byte */
#define WEG_APS_FSMCO_8723B			0x0004	/*  4 Byte */
#define WEG_SYS_CWKW_8723B			0x0008	/*  2 Byte */
#define WEG_9346CW_8723B			0x000A	/*  2 Byte */
#define WEG_EE_VPD_8723B			0x000C	/*  2 Byte */
#define WEG_AFE_MISC_8723B			0x0010	/*  1 Byte */
#define WEG_SPS0_CTWW_8723B			0x0011	/*  7 Byte */
#define WEG_SPS_OCP_CFG_8723B			0x0018	/*  4 Byte */
#define WEG_WSV_CTWW_8723B			0x001C	/*  3 Byte */
#define WEG_WF_CTWW_8723B			0x001F	/*  1 Byte */
#define WEG_WPWDO_CTWW_8723B			0x0023	/*  1 Byte */
#define WEG_AFE_XTAW_CTWW_8723B			0x0024	/*  4 Byte */
#define WEG_AFE_PWW_CTWW_8723B			0x0028	/*  4 Byte */
#define WEG_MAC_PWW_CTWW_EXT_8723B		0x002c	/*  4 Byte */
#define WEG_EFUSE_CTWW_8723B			0x0030
#define WEG_EFUSE_TEST_8723B			0x0034
#define WEG_PWW_DATA_8723B			0x0038
#define WEG_CAW_TIMEW_8723B			0x003C
#define WEG_ACWK_MON_8723B			0x003E
#define WEG_GPIO_MUXCFG_8723B			0x0040
#define WEG_GPIO_IO_SEW_8723B			0x0042
#define WEG_MAC_PINMUX_CFG_8723B		0x0043
#define WEG_GPIO_PIN_CTWW_8723B			0x0044
#define WEG_GPIO_INTM_8723B			0x0048
#define WEG_WEDCFG0_8723B			0x004C
#define WEG_WEDCFG1_8723B			0x004D
#define WEG_WEDCFG2_8723B			0x004E
#define WEG_WEDCFG3_8723B			0x004F
#define WEG_FSIMW_8723B				0x0050
#define WEG_FSISW_8723B				0x0054
#define WEG_HSIMW_8723B				0x0058
#define WEG_HSISW_8723B				0x005c
#define WEG_GPIO_EXT_CTWW			0x0060
#define WEG_MUWTI_FUNC_CTWW_8723B		0x0068
#define WEG_GPIO_STATUS_8723B			0x006C
#define WEG_SDIO_CTWW_8723B			0x0070
#define WEG_OPT_CTWW_8723B			0x0074
#define WEG_AFE_XTAW_CTWW_EXT_8723B		0x0078
#define WEG_MCUFWDW_8723B			0x0080
#define WEG_BT_PATCH_STATUS_8723B		0x0088
#define WEG_HIMW0_8723B				0x00B0
#define WEG_HISW0_8723B				0x00B4
#define WEG_HIMW1_8723B				0x00B8
#define WEG_HISW1_8723B				0x00BC
#define WEG_PMC_DBG_CTWW2_8723B			0x00CC
#define	WEG_EFUSE_BUWN_GNT_8723B		0x00CF
#define WEG_HPON_FSM_8723B			0x00EC
#define WEG_SYS_CFG_8723B			0x00F0
#define WEG_SYS_CFG1_8723B			0x00FC
#define WEG_WOM_VEWSION				0x00FD

/*  */
/*  */
/*	0x0100h ~ 0x01FFh	MACTOP Genewaw Configuwation */
/*  */
/*  */
#define WEG_CW_8723B				0x0100
#define WEG_PBP_8723B				0x0104
#define WEG_PKT_BUFF_ACCESS_CTWW_8723B		0x0106
#define WEG_TWXDMA_CTWW_8723B			0x010C
#define WEG_TWXFF_BNDY_8723B			0x0114
#define WEG_TWXFF_STATUS_8723B			0x0118
#define WEG_WXFF_PTW_8723B			0x011C
#define WEG_CPWM_8723B				0x012F
#define WEG_FWIMW_8723B				0x0130
#define WEG_FWISW_8723B				0x0134
#define WEG_FTIMW_8723B				0x0138
#define WEG_PKTBUF_DBG_CTWW_8723B		0x0140
#define WEG_WXPKTBUF_CTWW_8723B			0x0142
#define WEG_PKTBUF_DBG_DATA_W_8723B		0x0144
#define WEG_PKTBUF_DBG_DATA_H_8723B		0x0148

#define WEG_TC0_CTWW_8723B			0x0150
#define WEG_TC1_CTWW_8723B			0x0154
#define WEG_TC2_CTWW_8723B			0x0158
#define WEG_TC3_CTWW_8723B			0x015C
#define WEG_TC4_CTWW_8723B			0x0160
#define WEG_TCUNIT_BASE_8723B			0x0164
#define WEG_WSVD3_8723B				0x0168
#define WEG_C2HEVT_MSG_NOWMAW_8723B		0x01A0
#define WEG_C2HEVT_CMD_SEQ_88XX			0x01A1
#define WEG_C2HEVT_CMD_CONTENT_88XX		0x01A2
#define WEG_C2HEVT_CMD_WEN_88XX			0x01AE
#define WEG_C2HEVT_CWEAW_8723B			0x01AF
#define WEG_MCUTST_1_8723B			0x01C0
#define WEG_MCUTST_WOWWAN_8723B			0x01C7
#define WEG_FMETHW_8723B			0x01C8
#define WEG_HMETFW_8723B			0x01CC
#define WEG_HMEBOX_0_8723B			0x01D0
#define WEG_HMEBOX_1_8723B			0x01D4
#define WEG_HMEBOX_2_8723B			0x01D8
#define WEG_HMEBOX_3_8723B			0x01DC
#define WEG_WWT_INIT_8723B			0x01E0
#define WEG_HMEBOX_EXT0_8723B			0x01F0
#define WEG_HMEBOX_EXT1_8723B			0x01F4
#define WEG_HMEBOX_EXT2_8723B			0x01F8
#define WEG_HMEBOX_EXT3_8723B			0x01FC

/*  */
/*  */
/*	0x0200h ~ 0x027Fh	TXDMA Configuwation */
/*  */
/*  */
#define WEG_WQPN_8723B				0x0200
#define WEG_FIFOPAGE_8723B			0x0204
#define WEG_DWBCN0_CTWW_8723B			WEG_TDECTWW
#define WEG_TXDMA_OFFSET_CHK_8723B		0x020C
#define WEG_TXDMA_STATUS_8723B			0x0210
#define WEG_WQPN_NPQ_8723B			0x0214
#define WEG_DWBCN1_CTWW_8723B			0x0228

/*  */
/*  */
/*	0x0280h ~ 0x02FFh	WXDMA Configuwation */
/*  */
/*  */
#define WEG_WXDMA_AGG_PG_TH_8723B		0x0280
#define WEG_FW_UPD_WDPTW_8723B			0x0284 /*  FW shaww update this wegistew befowe FW wwite WXPKT_WEWEASE_POWW to 1 */
#define WEG_WXDMA_CONTWOW_8723B			0x0286 /*  Contwow the WX DMA. */
#define WEG_WXPKT_NUM_8723B			0x0287 /*  The numbew of packets in WXPKTBUF. */
#define WEG_WXDMA_STATUS_8723B			0x0288
#define WEG_WXDMA_PWO_8723B			0x0290
#define WEG_EAWWY_MODE_CONTWOW_8723B		0x02BC
#define WEG_WSVD5_8723B				0x02F0
#define WEG_WSVD6_8723B				0x02F4

/*  */
/*  */
/*	0x0300h ~ 0x03FFh	PCIe */
/*  */
/*  */
#define	WEG_PCIE_CTWW_WEG_8723B			0x0300
#define	WEG_INT_MIG_8723B			0x0304	/*  Intewwupt Migwation */
#define	WEG_BCNQ_DESA_8723B			0x0308	/*  TX Beacon Descwiptow Addwess */
#define	WEG_HQ_DESA_8723B			0x0310	/*  TX High Queue Descwiptow Addwess */
#define	WEG_MGQ_DESA_8723B			0x0318	/*  TX Manage Queue Descwiptow Addwess */
#define	WEG_VOQ_DESA_8723B			0x0320	/*  TX VO Queue Descwiptow Addwess */
#define	WEG_VIQ_DESA_8723B			0x0328	/*  TX VI Queue Descwiptow Addwess */
#define	WEG_BEQ_DESA_8723B			0x0330	/*  TX BE Queue Descwiptow Addwess */
#define	WEG_BKQ_DESA_8723B			0x0338	/*  TX BK Queue Descwiptow Addwess */
#define	WEG_WX_DESA_8723B			0x0340	/*  WX Queue	Descwiptow Addwess */
#define	WEG_DBI_WDATA_8723B			0x0348	/*  DBI Wwite Data */
#define	WEG_DBI_WDATA_8723B			0x034C	/*  DBI Wead Data */
#define	WEG_DBI_ADDW_8723B			0x0350	/*  DBI Addwess */
#define	WEG_DBI_FWAG_8723B			0x0352	/*  DBI Wead/Wwite Fwag */
#define	WEG_MDIO_WDATA_8723B			0x0354	/*  MDIO fow Wwite PCIE PHY */
#define	WEG_MDIO_WDATA_8723B			0x0356	/*  MDIO fow Weads PCIE PHY */
#define	WEG_MDIO_CTW_8723B			0x0358	/*  MDIO fow Contwow */
#define	WEG_DBG_SEW_8723B			0x0360	/*  Debug Sewection Wegistew */
#define	WEG_PCIE_HWPWM_8723B			0x0361	/* PCIe WPWM */
#define	WEG_PCIE_HCPWM_8723B			0x0363	/* PCIe CPWM */
#define	WEG_PCIE_MUWTIFET_CTWW_8723B		0x036A	/* PCIE Muwti-Fethc Contwow */

/*  spec vewsion 11 */
/*  */
/*  */
/*	0x0400h ~ 0x047Fh	Pwotocow Configuwation */
/*  */
/*  */
#define WEG_VOQ_INFOWMATION_8723B		0x0400
#define WEG_VIQ_INFOWMATION_8723B		0x0404
#define WEG_BEQ_INFOWMATION_8723B		0x0408
#define WEG_BKQ_INFOWMATION_8723B		0x040C
#define WEG_MGQ_INFOWMATION_8723B		0x0410
#define WEG_HGQ_INFOWMATION_8723B		0x0414
#define WEG_BCNQ_INFOWMATION_8723B		0x0418
#define WEG_TXPKT_EMPTY_8723B			0x041A

#define WEG_FWHW_TXQ_CTWW_8723B			0x0420
#define WEG_HWSEQ_CTWW_8723B			0x0423
#define WEG_TXPKTBUF_BCNQ_BDNY_8723B		0x0424
#define WEG_TXPKTBUF_MGQ_BDNY_8723B		0x0425
#define WEG_WIFECTWW_CTWW_8723B			0x0426
#define WEG_MUWTI_BCNQ_OFFSET_8723B		0x0427
#define WEG_SPEC_SIFS_8723B			0x0428
#define WEG_WW_8723B				0x042A
#define WEG_TXBF_CTWW_8723B			0x042C
#define WEG_DAWFWC_8723B			0x0430
#define WEG_WAWFWC_8723B			0x0438
#define WEG_WWSW_8723B				0x0440
#define WEG_AWFW0_8723B				0x0444
#define WEG_AWFW1_8723B				0x044C
#define WEG_CCK_CHECK_8723B			0x0454
#define WEG_AMPDU_MAX_TIME_8723B		0x0456
#define WEG_TXPKTBUF_BCNQ_BDNY1_8723B		0x0457

#define WEG_AMPDU_MAX_WENGTH_8723B		0x0458
#define WEG_TXPKTBUF_WMAC_WBK_BF_HD_8723B	0x045D
#define WEG_NDPA_OPT_CTWW_8723B			0x045F
#define WEG_FAST_EDCA_CTWW_8723B		0x0460
#define WEG_WD_WESP_PKT_TH_8723B		0x0463
#define WEG_DATA_SC_8723B			0x0483
#define WEG_TXWPT_STAWT_OFFSET			0x04AC
#define WEG_POWEW_STAGE1_8723B			0x04B4
#define WEG_POWEW_STAGE2_8723B			0x04B8
#define WEG_AMPDU_BUWST_MODE_8723B		0x04BC
#define WEG_PKT_VO_VI_WIFE_TIME_8723B		0x04C0
#define WEG_PKT_BE_BK_WIFE_TIME_8723B		0x04C2
#define WEG_STBC_SETTING_8723B			0x04C4
#define WEG_HT_SINGWE_AMPDU_8723B		0x04C7
#define WEG_PWOT_MODE_CTWW_8723B		0x04C8
#define WEG_MAX_AGGW_NUM_8723B			0x04CA
#define WEG_WTS_MAX_AGGW_NUM_8723B		0x04CB
#define WEG_BAW_MODE_CTWW_8723B			0x04CC
#define WEG_WA_TWY_WATE_AGG_WMT_8723B		0x04CF
#define WEG_MACID_PKT_DWOP0_8723B		0x04D0
#define WEG_MACID_PKT_SWEEP_8723B		0x04D4

/*  */
/*  */
/*	0x0500h ~ 0x05FFh	EDCA Configuwation */
/*  */
/*  */
#define WEG_EDCA_VO_PAWAM_8723B			0x0500
#define WEG_EDCA_VI_PAWAM_8723B			0x0504
#define WEG_EDCA_BE_PAWAM_8723B			0x0508
#define WEG_EDCA_BK_PAWAM_8723B			0x050C
#define WEG_BCNTCFG_8723B			0x0510
#define WEG_PIFS_8723B				0x0512
#define WEG_WDG_PIFS_8723B			0x0513
#define WEG_SIFS_CTX_8723B			0x0514
#define WEG_SIFS_TWX_8723B			0x0516
#define WEG_AGGW_BWEAK_TIME_8723B		0x051A
#define WEG_SWOT_8723B				0x051B
#define WEG_TX_PTCW_CTWW_8723B			0x0520
#define WEG_TXPAUSE_8723B			0x0522
#define WEG_DIS_TXWEQ_CWW_8723B			0x0523
#define WEG_WD_CTWW_8723B			0x0524
/*  */
/*  Fowmat fow offset 540h-542h: */
/*	[3:0]:	TBTT pwohibit setup in unit of 32us. The time fow HW getting beacon content befowe TBTT. */
/*	[7:4]:	Wesewved. */
/*	[19:8]:	TBTT pwohibit howd in unit of 32us. The time fow HW howding to send the beacon packet. */
/*	[23:20]: Wesewved */
/*  Descwiption: */
/* 	              | */
/*      |<--Setup--|--Howd------------>| */
/* 	--------------|---------------------- */
/*                 | */
/*                TBTT */
/*  Note: We cannot update beacon content to HW ow send any AC packets duwing the time between Setup and Howd. */
/*  Descwibed by Designew Tim and Bwuce, 2011-01-14. */
/*  */
#define WEG_TBTT_PWOHIBIT_8723B			0x0540
#define WEG_WD_NAV_NXT_8723B			0x0544
#define WEG_NAV_PWOT_WEN_8723B			0x0546
#define WEG_BCN_CTWW_8723B			0x0550
#define WEG_BCN_CTWW_1_8723B			0x0551
#define WEG_MBID_NUM_8723B			0x0552
#define WEG_DUAW_TSF_WST_8723B			0x0553
#define WEG_BCN_INTEWVAW_8723B			0x0554
#define WEG_DWVEWWYINT_8723B			0x0558
#define WEG_BCNDMATIM_8723B			0x0559
#define WEG_ATIMWND_8723B			0x055A
#define WEG_USTIME_TSF_8723B			0x055C
#define WEG_BCN_MAX_EWW_8723B			0x055D
#define WEG_WXTSF_OFFSET_CCK_8723B		0x055E
#define WEG_WXTSF_OFFSET_OFDM_8723B		0x055F
#define WEG_TSFTW_8723B				0x0560
#define WEG_CTWND_8723B				0x0572
#define WEG_SECONDAWY_CCA_CTWW_8723B		0x0577
#define WEG_PSTIMEW_8723B			0x0580
#define WEG_TIMEW0_8723B			0x0584
#define WEG_TIMEW1_8723B			0x0588
#define WEG_ACMHWCTWW_8723B			0x05C0
#define WEG_SCH_TXCMD_8723B			0x05F8

/*	0x0600h ~ 0x07FFh	WMAC Configuwation */
#define WEG_MAC_CW_8723B			0x0600
#define WEG_TCW_8723B				0x0604
#define WEG_WCW_8723B				0x0608
#define WEG_WX_PKT_WIMIT_8723B			0x060C
#define WEG_WX_DWK_TIME_8723B			0x060D
#define WEG_WX_DWVINFO_SZ_8723B			0x060F

#define WEG_MACID_8723B				0x0610
#define WEG_BSSID_8723B				0x0618
#define WEG_MAW_8723B				0x0620
#define WEG_MBIDCAMCFG_8723B			0x0628

#define WEG_USTIME_EDCA_8723B			0x0638
#define WEG_MAC_SPEC_SIFS_8723B			0x063A
#define WEG_WESP_SIFP_CCK_8723B			0x063C
#define WEG_WESP_SIFS_OFDM_8723B		0x063E
#define WEG_ACKTO_8723B				0x0640
#define WEG_CTS2TO_8723B			0x0641
#define WEG_EIFS_8723B				0x0642

#define WEG_NAV_UPPEW_8723B			0x0652	/*  unit of 128 */
#define WEG_TWXPTCW_CTW_8723B			0x0668

/*  Secuwity */
#define WEG_CAMCMD_8723B			0x0670
#define WEG_CAMWWITE_8723B			0x0674
#define WEG_CAMWEAD_8723B			0x0678
#define WEG_CAMDBG_8723B			0x067C
#define WEG_SECCFG_8723B			0x0680

/*  Powew */
#define WEG_WOW_CTWW_8723B			0x0690
#define WEG_PS_WX_INFO_8723B			0x0692
#define WEG_UAPSD_TID_8723B			0x0693
#define WEG_WKFMCAM_CMD_8723B			0x0698
#define WEG_WKFMCAM_NUM_8723B			0x0698
#define WEG_WKFMCAM_WWD_8723B			0x069C
#define WEG_WXFWTMAP0_8723B			0x06A0
#define WEG_WXFWTMAP1_8723B			0x06A2
#define WEG_WXFWTMAP2_8723B			0x06A4
#define WEG_BCN_PSW_WPT_8723B			0x06A8
#define WEG_BT_COEX_TABWE_8723B			0x06C0
#define WEG_BFMEW0_INFO_8723B			0x06E4
#define WEG_BFMEW1_INFO_8723B			0x06EC
#define WEG_CSI_WPT_PAWAM_BW20_8723B		0x06F4
#define WEG_CSI_WPT_PAWAM_BW40_8723B		0x06F8
#define WEG_CSI_WPT_PAWAM_BW80_8723B		0x06FC

/*  Hawdwawe Powt 2 */
#define WEG_MACID1_8723B			0x0700
#define WEG_BSSID1_8723B			0x0708
#define WEG_BFMEE_SEW_8723B			0x0714
#define WEG_SND_PTCW_CTWW_8723B			0x0718

/*	Wedifine 8192C wegistew definition fow compatibiwity */

/*  TODO: use these definition when using WEG_xxx naming wuwe. */
/*  NOTE: DO NOT Wemove these definition. Use watew. */
#define	EFUSE_CTWW_8723B	WEG_EFUSE_CTWW_8723B	/*  E-Fuse Contwow. */
#define	EFUSE_TEST_8723B	WEG_EFUSE_TEST_8723B	/*  E-Fuse Test. */
#define	MSW_8723B		(WEG_CW_8723B + 2)	/*  Media Status wegistew */
#define	ISW_8723B		WEG_HISW0_8723B
#define	TSFW_8723B		WEG_TSFTW_8723B		/*  Timing Sync Function Timew Wegistew. */

#define PBP_8723B		WEG_PBP_8723B

/*  Wedifine MACID wegistew, to compatibwe pwiow ICs. */
#define	IDW0_8723B		WEG_MACID_8723B		/*  MAC ID Wegistew, Offset 0x0050-0x0053 */
#define	IDW4_8723B		(WEG_MACID_8723B + 4)	/*  MAC ID Wegistew, Offset 0x0054-0x0055 */

/*  9. Secuwity Contwow Wegistews	(Offset:) */
#define	WWCAM_8723B		WEG_CAMCMD_8723B	/* IN 8190 Data Sheet is cawwed CAMcmd */
#define	WCAMI_8723B		WEG_CAMWWITE_8723B	/*  Softwawe wwite CAM input content */
#define	WCAMO_8723B		WEG_CAMWEAD_8723B	/*  Softwawe wead/wwite CAM config */
#define	CAMDBG_8723B		WEG_CAMDBG_8723B
#define	SECW_8723B		WEG_SECCFG_8723B	/* Secuwity Configuwation Wegistew */

/*        8195 IMW/ISW bits		(offset 0xB0,  8bits) */
#define	IMW_DISABWED_8723B		0
/*  IMW DW0(0x00B0-00B3) Bit 0-31 */
#define	IMW_TIMEW2_8723B		BIT31	/*  Timeout intewwupt 2 */
#define	IMW_TIMEW1_8723B		BIT30	/*  Timeout intewwupt 1 */
#define	IMW_PSTIMEOUT_8723B		BIT29	/*  Powew Save Time Out Intewwupt */
#define	IMW_GTINT4_8723B		BIT28	/*  When GTIMEW4 expiwes, this bit is set to 1 */
#define	IMW_GTINT3_8723B		BIT27	/*  When GTIMEW3 expiwes, this bit is set to 1 */
#define	IMW_TXBCN0EWW_8723B		BIT26	/*  Twansmit Beacon0 Ewwow */
#define	IMW_TXBCN0OK_8723B		BIT25	/*  Twansmit Beacon0 OK */
#define	IMW_TSF_BIT32_TOGGWE_8723B	BIT24	/*  TSF Timew BIT32 toggwe indication intewwupt */
#define	IMW_BCNDMAINT0_8723B		BIT20	/*  Beacon DMA Intewwupt 0 */
#define	IMW_BCNDEWW0_8723B		BIT16	/*  Beacon Queue DMA OK0 */
#define	IMW_HSISW_IND_ON_INT_8723B	BIT15	/*  HSISW Indicatow (HSIMW & HSISW is twue, this bit is set to 1) */
#define	IMW_BCNDMAINT_E_8723B		BIT14	/*  Beacon DMA Intewwupt Extension fow Win7 */
#define	IMW_ATIMEND_8723B		BIT12	/*  CTWidnow End ow ATIM Window End */
#define	IMW_C2HCMD_8723B		BIT10	/*  CPU to Host Command INT Status, Wwite 1 cweaw */
#define	IMW_CPWM2_8723B			BIT9	/*  CPU powew Mode exchange INT Status, Wwite 1 cweaw */
#define	IMW_CPWM_8723B			BIT8	/*  CPU powew Mode exchange INT Status, Wwite 1 cweaw */
#define	IMW_HIGHDOK_8723B		BIT7	/*  High Queue DMA OK */
#define	IMW_MGNTDOK_8723B		BIT6	/*  Management Queue DMA OK */
#define	IMW_BKDOK_8723B			BIT5	/*  AC_BK DMA OK */
#define	IMW_BEDOK_8723B			BIT4	/*  AC_BE DMA OK */
#define	IMW_VIDOK_8723B			BIT3	/*  AC_VI DMA OK */
#define	IMW_VODOK_8723B			BIT2	/*  AC_VO DMA OK */
#define	IMW_WDU_8723B			BIT1	/*  Wx Descwiptow Unavaiwabwe */
#define	IMW_WOK_8723B			BIT0	/*  Weceive DMA OK */

/*  IMW DW1(0x00B4-00B7) Bit 0-31 */
#define	IMW_BCNDMAINT7_8723B		BIT27	/*  Beacon DMA Intewwupt 7 */
#define	IMW_BCNDMAINT6_8723B		BIT26	/*  Beacon DMA Intewwupt 6 */
#define	IMW_BCNDMAINT5_8723B		BIT25	/*  Beacon DMA Intewwupt 5 */
#define	IMW_BCNDMAINT4_8723B		BIT24	/*  Beacon DMA Intewwupt 4 */
#define	IMW_BCNDMAINT3_8723B		BIT23	/*  Beacon DMA Intewwupt 3 */
#define	IMW_BCNDMAINT2_8723B		BIT22	/*  Beacon DMA Intewwupt 2 */
#define	IMW_BCNDMAINT1_8723B		BIT21	/*  Beacon DMA Intewwupt 1 */
#define	IMW_BCNDOK7_8723B		BIT20	/*  Beacon Queue DMA OK Intewwupt 7 */
#define	IMW_BCNDOK6_8723B		BIT19	/*  Beacon Queue DMA OK Intewwupt 6 */
#define	IMW_BCNDOK5_8723B		BIT18	/*  Beacon Queue DMA OK Intewwupt 5 */
#define	IMW_BCNDOK4_8723B		BIT17	/*  Beacon Queue DMA OK Intewwupt 4 */
#define	IMW_BCNDOK3_8723B		BIT16	/*  Beacon Queue DMA OK Intewwupt 3 */
#define	IMW_BCNDOK2_8723B		BIT15	/*  Beacon Queue DMA OK Intewwupt 2 */
#define	IMW_BCNDOK1_8723B		BIT14	/*  Beacon Queue DMA OK Intewwupt 1 */
#define	IMW_ATIMEND_E_8723B		BIT13	/*  ATIM Window End Extension fow Win7 */
#define	IMW_TXEWW_8723B			BIT11	/*  Tx Ewwow Fwag Intewwupt Status, wwite 1 cweaw. */
#define	IMW_WXEWW_8723B			BIT10	/*  Wx Ewwow Fwag INT Status, Wwite 1 cweaw */
#define	IMW_TXFOVW_8723B		BIT9	/*  Twansmit FIFO Ovewfwow */
#define	IMW_WXFOVW_8723B		BIT8	/*  Weceive FIFO Ovewfwow */

/* 2 ACMHWCTWW 0x05C0 */
#define	ACMHW_HWEN_8723B		BIT(0)
#define	ACMHW_VOQEN_8723B		BIT(1)
#define	ACMHW_VIQEN_8723B		BIT(2)
#define	ACMHW_BEQEN_8723B		BIT(3)
#define	ACMHW_VOQSTATUS_8723B		BIT(5)
#define	ACMHW_VIQSTATUS_8723B		BIT(6)
#define	ACMHW_BEQSTATUS_8723B		BIT(7)

/*        8195 (WCW) Weceive Configuwation Wegistew	(Offset 0x608, 32 bits) */
#define	WCW_TCPOFWD_EN			BIT25	/*  Enabwe TCP checksum offwoad */

#endif /*  #ifndef __INC_HAW8723BWEG_H */
