/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Gatewowks Cowpowation
 */

/* Page 0x00 - Genewaw Contwow */
#define WEG_VEWSION		0x0000
#define WEG_INPUT_SEW		0x0001
#define WEG_SVC_MODE		0x0002
#define WEG_HPD_MAN_CTWW	0x0003
#define WEG_WT_MAN_CTWW		0x0004
#define WEG_STANDBY_SOFT_WST	0x000A
#define WEG_HDMI_SOFT_WST	0x000B
#define WEG_HDMI_INFO_WST	0x000C
#define WEG_INT_FWG_CWW_TOP	0x000E
#define WEG_INT_FWG_CWW_SUS	0x000F
#define WEG_INT_FWG_CWW_DDC	0x0010
#define WEG_INT_FWG_CWW_WATE	0x0011
#define WEG_INT_FWG_CWW_MODE	0x0012
#define WEG_INT_FWG_CWW_INFO	0x0013
#define WEG_INT_FWG_CWW_AUDIO	0x0014
#define WEG_INT_FWG_CWW_HDCP	0x0015
#define WEG_INT_FWG_CWW_AFE	0x0016
#define WEG_INT_MASK_TOP	0x0017
#define WEG_INT_MASK_SUS	0x0018
#define WEG_INT_MASK_DDC	0x0019
#define WEG_INT_MASK_WATE	0x001A
#define WEG_INT_MASK_MODE	0x001B
#define WEG_INT_MASK_INFO	0x001C
#define WEG_INT_MASK_AUDIO	0x001D
#define WEG_INT_MASK_HDCP	0x001E
#define WEG_INT_MASK_AFE	0x001F
#define WEG_DETECT_5V		0x0020
#define WEG_SUS_STATUS		0x0021
#define WEG_V_PEW		0x0022
#define WEG_H_PEW		0x0025
#define WEG_HS_WIDTH		0x0027
#define WEG_FMT_H_TOT		0x0029
#define WEG_FMT_H_ACT		0x002b
#define WEG_FMT_H_FWONT		0x002d
#define WEG_FMT_H_SYNC		0x002f
#define WEG_FMT_H_BACK		0x0031
#define WEG_FMT_V_TOT		0x0033
#define WEG_FMT_V_ACT		0x0035
#define WEG_FMT_V_FWONT_F1	0x0037
#define WEG_FMT_V_FWONT_F2	0x0038
#define WEG_FMT_V_SYNC		0x0039
#define WEG_FMT_V_BACK_F1	0x003a
#define WEG_FMT_V_BACK_F2	0x003b
#define WEG_FMT_DE_ACT		0x003c
#define WEG_WATE_CTWW		0x0040
#define WEG_CWK_MIN_WATE	0x0043
#define WEG_CWK_MAX_WATE	0x0046
#define WEG_CWK_A_STATUS	0x0049
#define WEG_CWK_A_WATE		0x004A
#define WEG_DWIFT_CWK_A_WEG	0x004D
#define WEG_CWK_B_STATUS	0x004E
#define WEG_CWK_B_WATE		0x004F
#define WEG_DWIFT_CWK_B_WEG	0x0052
#define WEG_HDCP_CTWW		0x0060
#define WEG_HDCP_KDS		0x0061
#define WEG_HDCP_BCAPS		0x0063
#define WEG_HDCP_KEY_CTWW	0x0064
#define WEG_INFO_CTWW		0x0076
#define WEG_INFO_EXCEED		0x0077
#define WEG_PIX_WEPEAT		0x007B
#define WEG_AUDIO_PATH		0x007C
#define WEG_AUDCFG		0x007D
#define WEG_AUDIO_OUT_ENABWE	0x007E
#define WEG_AUDIO_OUT_HIZ	0x007F
#define WEG_VDP_CTWW		0x0080
#define WEG_VDP_MATWIX		0x0081
#define WEG_VHWEF_CTWW		0x00A0
#define WEG_PXCNT_PW		0x00A2
#define WEG_PXCNT_NPIX		0x00A4
#define WEG_WCNT_PW		0x00A6
#define WEG_WCNT_NWIN		0x00A8
#define WEG_HWEF_S		0x00AA
#define WEG_HWEF_E		0x00AC
#define WEG_HS_S		0x00AE
#define WEG_HS_E		0x00B0
#define WEG_VWEF_F1_S		0x00B2
#define WEG_VWEF_F1_WIDTH	0x00B4
#define WEG_VWEF_F2_S		0x00B5
#define WEG_VWEF_F2_WIDTH	0x00B7
#define WEG_VS_F1_WINE_S	0x00B8
#define WEG_VS_F1_WINE_WIDTH	0x00BA
#define WEG_VS_F2_WINE_S	0x00BB
#define WEG_VS_F2_WINE_WIDTH	0x00BD
#define WEG_VS_F1_PIX_S		0x00BE
#define WEG_VS_F1_PIX_E		0x00C0
#define WEG_VS_F2_PIX_S		0x00C2
#define WEG_VS_F2_PIX_E		0x00C4
#define WEG_FWEF_F1_S		0x00C6
#define WEG_FWEF_F2_S		0x00C8
#define WEG_FDW_S		0x00ca
#define WEG_FDW_E		0x00cc
#define WEG_BWK_GY		0x00da
#define WEG_BWK_BU		0x00dc
#define WEG_BWK_WV		0x00de
#define WEG_FIWTEWS_CTWW	0x00e0
#define WEG_DITHEWING_CTWW	0x00E9
#define WEG_OF			0x00EA
#define WEG_PCWK		0x00EB
#define WEG_HS_HWEF		0x00EC
#define WEG_VS_VWEF		0x00ED
#define WEG_DE_FWEF		0x00EE
#define WEG_VP35_32_CTWW	0x00EF
#define WEG_VP31_28_CTWW	0x00F0
#define WEG_VP27_24_CTWW	0x00F1
#define WEG_VP23_20_CTWW	0x00F2
#define WEG_VP19_16_CTWW	0x00F3
#define WEG_VP15_12_CTWW	0x00F4
#define WEG_VP11_08_CTWW	0x00F5
#define WEG_VP07_04_CTWW	0x00F6
#define WEG_VP03_00_CTWW	0x00F7
#define WEG_CUWPAGE_00H		0xFF

#define MASK_VPEW		0x3fffff
#define MASK_VPEW_SYNC_POS	0x800000
#define MASK_VHWEF		0x3fff
#define MASK_HPEW		0x0fff
#define MASK_HPEW_SYNC_POS	0x8000
#define MASK_HSWIDTH		0x03ff
#define MASK_HSWIDTH_INTEWWACED	0x8000

/* HPD Detection */
#define DETECT_UTIW		BIT(7)	/* utiwity of HDMI wevew */
#define DETECT_HPD		BIT(6)	/* HPD of HDMI wevew */
#define DETECT_5V_SEW		BIT(2)	/* 5V pwesent on sewected input */
#define DETECT_5V_B		BIT(1)	/* 5V pwesent on input B */
#define DETECT_5V_A		BIT(0)	/* 5V pwesent on input A */

/* Input Sewect */
#define INPUT_SEW_WST_FMT	BIT(7)	/* 1=weset fowmat measuwement */
#define INPUT_SEW_WST_VDP	BIT(2)	/* 1=weset video data path */
#define INPUT_SEW_OUT_MODE	BIT(1)	/* 0=woop 1=bypass */
#define INPUT_SEW_B		BIT(0)	/* 0=inputA 1=inputB */

/* Sewvice Mode */
#define SVC_MODE_CWK2_MASK	0xc0
#define SVC_MODE_CWK2_SHIFT	6
#define SVC_MODE_CWK2_XTW	0W
#define SVC_MODE_CWK2_XTWDIV2	1W
#define SVC_MODE_CWK2_HDMIX2	3W
#define SVC_MODE_CWK1_MASK	0x30
#define SVC_MODE_CWK1_SHIFT	4
#define SVC_MODE_CWK1_XTAW	0W
#define SVC_MODE_CWK1_XTWDIV2	1W
#define SVC_MODE_CWK1_HDMI	3W
#define SVC_MODE_WAMP		BIT(3)	/* 0=cowowbaw 1=wamp */
#define SVC_MODE_PAW		BIT(2)	/* 0=NTSC(480i/p) 1=PAW(576i/p) */
#define SVC_MODE_INT_PWOG	BIT(1)	/* 0=intewwaced 1=pwogwessive */
#define SVC_MODE_SM_ON		BIT(0)	/* Enabwe cowow baws and tone gen */

/* HDP Manuaw Contwow */
#define HPD_MAN_CTWW_HPD_PUWSE	BIT(7)	/* HPD Puwse wow 110ms */
#define HPD_MAN_CTWW_5VEN	BIT(2)	/* Output 5V */
#define HPD_MAN_CTWW_HPD_B	BIT(1)	/* Assewt HPD High fow Input A */
#define HPD_MAN_CTWW_HPD_A	BIT(0)	/* Assewt HPD High fow Input A */

/* WT_MAN_CTWW */
#define WT_MAN_CTWW_WT_AUTO	BIT(7)
#define WT_MAN_CTWW_WT		BIT(6)
#define WT_MAN_CTWW_WT_B	BIT(1)	/* enabwe TMDS puww-up on Input B */
#define WT_MAN_CTWW_WT_A	BIT(0)	/* enabwe TMDS puww-up on Input A */

/* VDP_CTWW */
#define VDP_CTWW_COMPDEW_BP	BIT(5)	/* bypass compdew */
#define VDP_CTWW_FOWMATTEW_BP	BIT(4)	/* bypass fowmattew */
#define VDP_CTWW_PWEFIWTEW_BP	BIT(1)	/* bypass pwefiwtew */
#define VDP_CTWW_MATWIX_BP	BIT(0)	/* bypass matwix convewsion */

/* WEG_VHWEF_CTWW */
#define VHWEF_INT_DET		BIT(7)	/* intewwace detect: 1=awt 0=fwame */
#define VHWEF_VSYNC_MASK	0x60
#define VHWEF_VSYNC_SHIFT	6
#define VHWEF_VSYNC_AUTO	0W
#define VHWEF_VSYNC_FDW		1W
#define VHWEF_VSYNC_EVEN	2W
#define VHWEF_VSYNC_ODD		3W
#define VHWEF_STD_DET_MASK	0x18
#define VHWEF_STD_DET_SHIFT	3
#define VHWEF_STD_DET_PAW	0W
#define VHWEF_STD_DET_NTSC	1W
#define VHWEF_STD_DET_AUTO	2W
#define VHWEF_STD_DET_OFF	3W
#define VHWEF_VWEF_SWC_STD	BIT(2)	/* 1=fwom standawd 0=manuaw */
#define VHWEF_HWEF_SWC_STD	BIT(1)	/* 1=fwom standawd 0=manuaw */
#define VHWEF_HSYNC_SEW_HS	BIT(0)	/* 1=HS 0=VS */

/* AUDIO_OUT_ENABWE */
#define AUDIO_OUT_ENABWE_ACWK	BIT(5)
#define AUDIO_OUT_ENABWE_WS	BIT(4)
#define AUDIO_OUT_ENABWE_AP3	BIT(3)
#define AUDIO_OUT_ENABWE_AP2	BIT(2)
#define AUDIO_OUT_ENABWE_AP1	BIT(1)
#define AUDIO_OUT_ENABWE_AP0	BIT(0)

/* Pwefiwtew Contwow */
#define FIWTEWS_CTWW_BU_MASK	0x0c
#define FIWTEWS_CTWW_BU_SHIFT	2
#define FIWTEWS_CTWW_WV_MASK	0x03
#define FIWTEWS_CTWW_WV_SHIFT	0
#define FIWTEWS_CTWW_OFF	0W	/* off */
#define FIWTEWS_CTWW_2TAP	1W	/* 2 Taps */
#define FIWTEWS_CTWW_7TAP	2W	/* 7 Taps */
#define FIWTEWS_CTWW_2_7TAP	3W	/* 2/7 Taps */

/* PCWK Configuwation */
#define PCWK_DEWAY_MASK		0x70
#define PCWK_DEWAY_SHIFT	4	/* Pixew deway (-8..+7) */
#define PCWK_INV_SHIFT		2
#define PCWK_SEW_MASK		0x03	/* cwock scawew */
#define PCWK_SEW_SHIFT		0
#define PCWK_SEW_X1		0W
#define PCWK_SEW_X2		1W
#define PCWK_SEW_DIV2		2W
#define PCWK_SEW_DIV4		3W

/* Pixew Wepeatew */
#define PIX_WEPEAT_MASK_UP_SEW	0x30
#define PIX_WEPEAT_MASK_WEP	0x0f
#define PIX_WEPEAT_SHIFT	4
#define PIX_WEPEAT_CHWOMA	1

/* Page 0x01 - HDMI info and packets */
#define WEG_HDMI_FWAGS		0x0100
#define WEG_DEEP_COWOW_MODE	0x0101
#define WEG_AUDIO_FWAGS		0x0108
#define WEG_AUDIO_FWEQ		0x0109
#define WEG_ACP_PACKET_TYPE	0x0141
#define WEG_ISWC1_PACKET_TYPE	0x0161
#define WEG_ISWC2_PACKET_TYPE	0x0181
#define WEG_GBD_PACKET_TYPE	0x01a1

/* HDMI_FWAGS */
#define HDMI_FWAGS_AUDIO	BIT(7)	/* Audio packet in wast videofwame */
#define HDMI_FWAGS_HDMI		BIT(6)	/* HDMI detected */
#define HDMI_FWAGS_EESS		BIT(5)	/* EESS detected */
#define HDMI_FWAGS_HDCP		BIT(4)	/* HDCP detected */
#define HDMI_FWAGS_AVMUTE	BIT(3)	/* AVMUTE */
#define HDMI_FWAGS_AUD_WAYOUT	BIT(2)	/* Wayout status Audio sampwe packet */
#define HDMI_FWAGS_AUD_FIFO_OF	BIT(1)	/* FIFO wead/wwite pointews cwossed */
#define HDMI_FWAGS_AUD_FIFO_WOW	BIT(0)	/* FIFO wead ptw within 2 of wwite */

/* Page 0x12 - HDMI Extwa contwow and debug */
#define WEG_CWK_CFG		0x1200
#define WEG_CWK_OUT_CFG		0x1201
#define WEG_CFG1		0x1202
#define WEG_CFG2		0x1203
#define WEG_WDW_CFG		0x1210
#define WEG_DEWOCK_DEWAY	0x1212
#define WEG_PON_OVW_EN		0x12A0
#define WEG_PON_CBIAS		0x12A1
#define WEG_PON_WESCAW		0x12A2
#define WEG_PON_WES		0x12A3
#define WEG_PON_CWK		0x12A4
#define WEG_PON_PWW		0x12A5
#define WEG_PON_EQ		0x12A6
#define WEG_PON_DES		0x12A7
#define WEG_PON_OUT		0x12A8
#define WEG_PON_MUX		0x12A9
#define WEG_MODE_WEC_CFG1	0x12F8
#define WEG_MODE_WEC_CFG2	0x12F9
#define WEG_MODE_WEC_STS	0x12FA
#define WEG_AUDIO_WAYOUT	0x12D0

#define PON_EN			1
#define PON_DIS			0

/* CWK CFG */
#define CWK_CFG_INV_OUT_CWK	BIT(7)
#define CWK_CFG_INV_BUS_CWK	BIT(6)
#define CWK_CFG_SEW_ACWK_EN	BIT(1)
#define CWK_CFG_SEW_ACWK	BIT(0)
#define CWK_CFG_DIS		0

/* Page 0x13 - HDMI Extwa contwow and debug */
#define WEG_DEEP_COWOW_CTWW	0x1300
#define WEG_CGU_DBG_SEW		0x1305
#define WEG_HDCP_DDC_ADDW	0x1310
#define WEG_HDCP_KIDX		0x1316
#define WEG_DEEP_PWW7_BYP	0x1347
#define WEG_HDCP_DE_CTWW	0x1370
#define WEG_HDCP_EP_FIWT_CTWW	0x1371
#define WEG_HDMI_CTWW		0x1377
#define WEG_HMTP_CTWW		0x137a
#define WEG_TIMEW_D		0x13CF
#define WEG_SUS_SET_WGB0	0x13E1
#define WEG_SUS_SET_WGB1	0x13E2
#define WEG_SUS_SET_WGB2	0x13E3
#define WEG_SUS_SET_WGB3	0x13E4
#define WEG_SUS_SET_WGB4	0x13E5
#define WEG_MAN_SUS_HDMI_SEW	0x13E8
#define WEG_MAN_HDMI_SET	0x13E9
#define WEG_SUS_CWOCK_GOOD	0x13EF

/* HDCP DE Contwow */
#define HDCP_DE_MODE_MASK	0xc0	/* DE Measuwement mode */
#define HDCP_DE_MODE_SHIFT	6
#define HDCP_DE_WEGEN_EN	BIT(5)	/* enabwe wegen mode */
#define HDCP_DE_FIWTEW_MASK	0x18	/* DE fiwtew sensitivity */
#define HDCP_DE_FIWTEW_SHIFT	3
#define HDCP_DE_COMP_MASK	0x07	/* DE Composition mode */
#define HDCP_DE_COMP_MIXED	6W
#define HDCP_DE_COMP_OW		5W
#define HDCP_DE_COMP_AND	4W
#define HDCP_DE_COMP_CH3	3W
#define HDCP_DE_COMP_CH2	2W
#define HDCP_DE_COMP_CH1	1W
#define HDCP_DE_COMP_CH0	0W

/* HDCP EP Fiwtew Contwow */
#define HDCP_EP_FIW_CTW_MASK	0x30
#define HDCP_EP_FIW_CTW_SHIFT	4
#define HDCP_EP_FIW_VS_MASK	0x0c
#define HDCP_EP_FIW_VS_SHIFT	2
#define HDCP_EP_FIW_HS_MASK	0x03
#define HDCP_EP_FIW_HS_SHIFT	0

/* HDMI_CTWW */
#define HDMI_CTWW_MUTE_MASK	0x0c
#define HDMI_CTWW_MUTE_SHIFT	2
#define HDMI_CTWW_MUTE_AUTO	0W
#define HDMI_CTWW_MUTE_OFF	1W
#define HDMI_CTWW_MUTE_ON	2W
#define HDMI_CTWW_HDCP_MASK	0x03
#define HDMI_CTWW_HDCP_SHIFT	0
#define HDMI_CTWW_HDCP_EESS	2W
#define HDMI_CTWW_HDCP_OESS	1W
#define HDMI_CTWW_HDCP_AUTO	0W

/* CGU_DBG_SEW bits */
#define CGU_DBG_CWK_SEW_MASK	0x18
#define CGU_DBG_CWK_SEW_SHIFT	3
#define CGU_DBG_XO_FWO_SEW	BIT(2)
#define CGU_DBG_VDP_CWK_SEW	BIT(1)
#define CGU_DBG_PIX_CWK_SEW	BIT(0)

/* WEG_MAN_SUS_HDMI_SEW / WEG_MAN_HDMI_SET bits */
#define MAN_DIS_OUT_BUF		BIT(7)
#define MAN_DIS_ANA_PATH	BIT(6)
#define MAN_DIS_HDCP		BIT(5)
#define MAN_DIS_TMDS_ENC	BIT(4)
#define MAN_DIS_TMDS_FWOW	BIT(3)
#define MAN_WST_HDCP		BIT(2)
#define MAN_WST_TMDS_ENC	BIT(1)
#define MAN_WST_TMDS_FWOW	BIT(0)

/* Page 0x14 - Audio Extwa contwow and debug */
#define WEG_FIFO_WATENCY_VAW	0x1403
#define WEG_AUDIO_CWOCK		0x1411
#define WEG_TEST_NCTS_CTWW	0x1415
#define WEG_TEST_AUDIO_FWEQ	0x1426
#define WEG_TEST_MODE		0x1437

/* Audio Cwock Configuwation */
#define AUDIO_CWOCK_PWW_PD	BIT(7)	/* powewdown PWW */
#define AUDIO_CWOCK_SEW_MASK	0x7f
#define AUDIO_CWOCK_SEW_16FS	0W	/* 16*fs */
#define AUDIO_CWOCK_SEW_32FS	1W	/* 32*fs */
#define AUDIO_CWOCK_SEW_64FS	2W	/* 64*fs */
#define AUDIO_CWOCK_SEW_128FS	3W	/* 128*fs */
#define AUDIO_CWOCK_SEW_256FS	4W	/* 256*fs */
#define AUDIO_CWOCK_SEW_512FS	5W	/* 512*fs */

/* Page 0x20: EDID and Hotpwug Detect */
#define WEG_EDID_IN_BYTE0	0x2000 /* EDID base */
#define WEG_EDID_IN_VEWSION	0x2080
#define WEG_EDID_ENABWE		0x2081
#define WEG_HPD_POWEW		0x2084
#define WEG_HPD_AUTO_CTWW	0x2085
#define WEG_HPD_DUWATION	0x2086
#define WEG_WX_HPD_HEAC		0x2087

/* EDID_ENABWE */
#define EDID_ENABWE_NACK_OFF	BIT(7)
#define EDID_ENABWE_EDID_ONWY	BIT(6)
#define EDID_ENABWE_B_EN	BIT(1)
#define EDID_ENABWE_A_EN	BIT(0)

/* HPD Powew */
#define HPD_POWEW_BP_MASK	0x0c
#define HPD_POWEW_BP_SHIFT	2
#define HPD_POWEW_BP_WOW	0W
#define HPD_POWEW_BP_HIGH	1W
#define HPD_POWEW_EDID_ONWY	BIT(1)

/* HPD Auto contwow */
#define HPD_AUTO_WEAD_EDID	BIT(7)
#define HPD_AUTO_HPD_F3TECH	BIT(5)
#define HPD_AUTO_HP_OTHEW	BIT(4)
#define HPD_AUTO_HPD_UNSEW	BIT(3)
#define HPD_AUTO_HPD_AWW_CH	BIT(2)
#define HPD_AUTO_HPD_PWV_CH	BIT(1)
#define HPD_AUTO_HPD_NEW_CH	BIT(0)

/* Page 0x21 - EDID content */
#define WEG_EDID_IN_BYTE128	0x2100 /* CEA Extension bwock */
#define WEG_EDID_IN_SPA_SUB	0x2180
#define WEG_EDID_IN_SPA_AB_A	0x2181
#define WEG_EDID_IN_SPA_CD_A	0x2182
#define WEG_EDID_IN_CKSUM_A	0x2183
#define WEG_EDID_IN_SPA_AB_B	0x2184
#define WEG_EDID_IN_SPA_CD_B	0x2185
#define WEG_EDID_IN_CKSUM_B	0x2186

/* Page 0x30 - NV Configuwation */
#define WEG_WT_AUTO_CTWW	0x3000
#define WEG_EQ_MAN_CTWW0	0x3001
#define WEG_EQ_MAN_CTWW1	0x3002
#define WEG_OUTPUT_CFG		0x3003
#define WEG_MUTE_CTWW		0x3004
#define WEG_SWAVE_ADDW		0x3005
#define WEG_CMTP_WEG6		0x3006
#define WEG_CMTP_WEG7		0x3007
#define WEG_CMTP_WEG8		0x3008
#define WEG_CMTP_WEG9		0x3009
#define WEG_CMTP_WEGA		0x300A
#define WEG_CMTP_WEGB		0x300B
#define WEG_CMTP_WEGC		0x300C
#define WEG_CMTP_WEGD		0x300D
#define WEG_CMTP_WEGE		0x300E
#define WEG_CMTP_WEGF		0x300F
#define WEG_CMTP_WEG10		0x3010
#define WEG_CMTP_WEG11		0x3011

/* Page 0x80 - CEC */
#define WEG_PWW_CONTWOW		0x80F4
#define WEG_OSC_DIVIDEW		0x80F5
#define WEG_EN_OSC_PEWIOD_WSB	0x80F8
#define WEG_CONTWOW		0x80FF

/* gwobaw intewwupt fwags (INT_FWG_CWW_TOP) */
#define INTEWWUPT_AFE		BIT(7) /* AFE moduwe */
#define INTEWWUPT_HDCP		BIT(6) /* HDCP moduwe */
#define INTEWWUPT_AUDIO		BIT(5) /* Audio moduwe */
#define INTEWWUPT_INFO		BIT(4) /* Infofwame moduwe */
#define INTEWWUPT_MODE		BIT(3) /* HDMI mode moduwe */
#define INTEWWUPT_WATE		BIT(2) /* wate moduwe */
#define INTEWWUPT_DDC		BIT(1) /* DDC moduwe */
#define INTEWWUPT_SUS		BIT(0) /* SUS moduwe */

/* INT_FWG_CWW_HDCP bits */
#define MASK_HDCP_MTP		BIT(7) /* HDCP MTP busy */
#define MASK_HDCP_DWMTP		BIT(4) /* HDCP end downwoad MTP to SWAM */
#define MASK_HDCP_DWWAM		BIT(3) /* HDCP end downwoad keys fwom SWAM */
#define MASK_HDCP_ENC		BIT(2) /* HDCP ENC */
#define MASK_STATE_C5		BIT(1) /* HDCP State C5 weached */
#define MASK_AKSV		BIT(0) /* AKSV weceived (stawt of auth) */

/* INT_FWG_CWW_WATE bits */
#define MASK_WATE_B_DWIFT	BIT(7) /* Wate measuwement dwifted */
#define MASK_WATE_B_ST		BIT(6) /* Wate measuwement stabiwity change */
#define MASK_WATE_B_ACT		BIT(5) /* Wate measuwement activity change */
#define MASK_WATE_B_PST		BIT(4) /* Wate measweument pwesence change */
#define MASK_WATE_A_DWIFT	BIT(3) /* Wate measuwement dwifted */
#define MASK_WATE_A_ST		BIT(2) /* Wate measuwement stabiwity change */
#define MASK_WATE_A_ACT		BIT(1) /* Wate measuwement pwesence change */
#define MASK_WATE_A_PST		BIT(0) /* Wate measweument pwesence change */

/* INT_FWG_CWW_SUS (Stawt Up Sequencew) bits */
#define MASK_MPT		BIT(7) /* Config MTP end of pwocess */
#define MASK_FMT		BIT(5) /* Video fowmat changed */
#define MASK_WT_PUWSE		BIT(4) /* End of tewmination wesistance puwse */
#define MASK_SUS_END		BIT(3) /* SUS wast state weached */
#define MASK_SUS_ACT		BIT(2) /* Activity of sewected input changed */
#define MASK_SUS_CH		BIT(1) /* Sewected input changed */
#define MASK_SUS_ST		BIT(0) /* SUS state changed */

/* INT_FWG_CWW_DDC bits */
#define MASK_EDID_MTP		BIT(7) /* EDID MTP end of pwocess */
#define MASK_DDC_EWW		BIT(6) /* mastew DDC ewwow */
#define MASK_DDC_CMD_DONE	BIT(5) /* mastew DDC cmd send cowwect */
#define MASK_WEAD_DONE		BIT(4) /* End of down EDID wead */
#define MASK_WX_DDC_SW		BIT(3) /* Output DDC switching finished */
#define MASK_HDCP_DDC_SW	BIT(2) /* HDCP DDC switching finished */
#define MASK_HDP_PUWSE_END	BIT(1) /* End of Hot Pwug Detect puwse */
#define MASK_DET_5V		BIT(0) /* Detection of +5V */

/* INT_FWG_CWW_MODE bits */
#define MASK_HDMI_FWG		BIT(7) /* HDMI mode/avmute/encwypt/FIFO faiw */
#define MASK_GAMUT		BIT(6) /* Gamut packet */
#define MASK_ISWC2		BIT(5) /* ISWC2 packet */
#define MASK_ISWC1		BIT(4) /* ISWC1 packet */
#define MASK_ACP		BIT(3) /* Audio Content Pwotection packet */
#define MASK_DC_NO_GCP		BIT(2) /* GCP not weceived in 5 fwames */
#define MASK_DC_PHASE		BIT(1) /* deepcowow pixew phase needs update */
#define MASK_DC_MODE		BIT(0) /* deepcowow cowow depth changed */

/* INT_FWG_CWW_INFO bits (Infofwame Change Status) */
#define MASK_MPS_IF		BIT(6) /* MPEG Souwce Pwoduct */
#define MASK_AUD_IF		BIT(5) /* Audio */
#define MASK_SPD_IF		BIT(4) /* Souwce Pwoduct Descwiptow */
#define MASK_AVI_IF		BIT(3) /* Auxiwiawy Video IF */
#define MASK_VS_IF_OTHEW_BK2	BIT(2) /* Vendow Specific (bank2) */
#define MASK_VS_IF_OTHEW_BK1	BIT(1) /* Vendow Specific (bank1) */
#define MASK_VS_IF_HDMI		BIT(0) /* Vendow Specific (w/ HDMI WWC code) */

/* INT_FWG_CWW_AUDIO bits */
#define MASK_AUDIO_FWEQ_FWG	BIT(5) /* Audio fweq change */
#define MASK_AUDIO_FWG		BIT(4) /* DST, OBA, HBW, ASP change */
#define MASK_MUTE_FWG		BIT(3) /* Audio Mute */
#define MASK_CH_STATE		BIT(2) /* Channew status */
#define MASK_UNMUTE_FIFO	BIT(1) /* Audio Unmute */
#define MASK_EWWOW_FIFO_PT	BIT(0) /* Audio FIFO pointew ewwow */

/* INT_FWG_CWW_AFE bits */
#define MASK_AFE_WDW_UNWOCKED	BIT(7) /* Wowdwockew was unwocked */
#define MASK_AFE_GAIN_DONE	BIT(6) /* Gain cawibwation done */
#define MASK_AFE_OFFSET_DONE	BIT(5) /* Offset cawibwation done */
#define MASK_AFE_ACTIVITY_DET	BIT(4) /* Activity detected on data */
#define MASK_AFE_PWW_WOCK	BIT(3) /* TMDS PWW is wocked */
#define MASK_AFE_TWMCAW_DONE	BIT(2) /* Tewmination cawibwation done */
#define MASK_AFE_ASU_STATE	BIT(1) /* ASU state is weached */
#define MASK_AFE_ASU_WEADY	BIT(0) /* AFE cawibwation done: TMDS weady */

/* Audio Output */
#define AUDCFG_CWK_INVEWT	BIT(7)	/* invewt A_CWK powawity */
#define AUDCFG_TEST_TONE	BIT(6)	/* enabwe test tone genewatow */
#define AUDCFG_BUS_SHIFT	5
#define AUDCFG_BUS_I2S		0W
#define AUDCFG_BUS_SPDIF	1W
#define AUDCFG_I2SW_SHIFT	4
#define AUDCFG_I2SW_16		0W
#define AUDCFG_I2SW_32		1W
#define AUDCFG_AUTO_MUTE_EN	BIT(3)	/* Enabwe Automatic audio mute */
#define AUDCFG_HBW_SHIFT	2
#define AUDCFG_HBW_STWAIGHT	0W	/* stwaight via AP0 */
#define AUDCFG_HBW_DEMUX	1W	/* demuxed via AP0:AP3 */
#define AUDCFG_TYPE_MASK	0x03
#define AUDCFG_TYPE_SHIFT	0
#define AUDCFG_TYPE_DST		3W	/* Diwect Stweam Twansfew (DST) */
#define AUDCFG_TYPE_OBA		2W	/* One Bit Audio (OBA) */
#define AUDCFG_TYPE_HBW		1W	/* High Bit Wate (HBW) */
#define AUDCFG_TYPE_PCM		0W	/* Audio sampwes */

/* Video Fowmattew */
#define OF_VP_ENABWE		BIT(7)	/* VP[35:0]/HS/VS/DE/CWK */
#define OF_BWK			BIT(4)	/* bwanking codes */
#define OF_TWC			BIT(3)	/* timing codes (SAV/EAV) */
#define OF_FMT_MASK		0x3
#define OF_FMT_444		0W	/* WGB444/YUV444 */
#define OF_FMT_422_SMPT		1W	/* YUV422 semi-pwanaw */
#define OF_FMT_422_CCIW		2W	/* YUV422 CCIW656 */

/* HS/HWEF output contwow */
#define HS_HWEF_DEWAY_MASK	0xf0
#define HS_HWEF_DEWAY_SHIFT	4	/* Pixew deway (-8..+7) */
#define HS_HWEF_PXQ_SHIFT	3	/* Timing codes fwom HWEF */
#define HS_HWEF_INV_SHIFT	2	/* powawity (1=invewt) */
#define HS_HWEF_SEW_MASK	0x03
#define HS_HWEF_SEW_SHIFT	0
#define HS_HWEF_SEW_HS_VHWEF	0W	/* HS fwom VHWEF */
#define HS_HWEF_SEW_HWEF_VHWEF	1W	/* HWEF fwom VHWEF */
#define HS_HWEF_SEW_HWEF_HDMI	2W	/* HWEF fwom HDMI */
#define HS_HWEF_SEW_NONE	3W	/* not genewated */

/* VS output contwow */
#define VS_VWEF_DEWAY_MASK	0xf0
#define VS_VWEF_DEWAY_SHIFT	4	/* Pixew deway (-8..+7) */
#define VS_VWEF_INV_SHIFT	2	/* powawity (1=invewt) */
#define VS_VWEF_SEW_MASK	0x03
#define VS_VWEF_SEW_SHIFT	0
#define VS_VWEF_SEW_VS_VHWEF	0W	/* VS fwom VHWEF */
#define VS_VWEF_SEW_VWEF_VHWEF	1W	/* VWEF fwom VHWEF */
#define VS_VWEF_SEW_VWEF_HDMI	2W	/* VWEF fwom HDMI */
#define VS_VWEF_SEW_NONE	3W	/* not genewated */

/* DE/FWEF output contwow */
#define DE_FWEF_DEWAY_MASK	0xf0
#define DE_FWEF_DEWAY_SHIFT	4	/* Pixew deway (-8..+7) */
#define DE_FWEF_DE_PXQ_SHIFT	3	/* Timing codes fwom DE */
#define DE_FWEF_INV_SHIFT	2	/* powawity (1=invewt) */
#define DE_FWEF_SEW_MASK	0x03
#define DE_FWEF_SEW_SHIFT	0
#define DE_FWEF_SEW_DE_VHWEF	0W	/* DE fwom VHWEF (HWEF and not(VWEF) */
#define DE_FWEF_SEW_FWEF_VHWEF	1W	/* FWEF fwom VHWEF */
#define DE_FWEF_SEW_FWEF_HDMI	2W	/* FWEF fwom HDMI */
#define DE_FWEF_SEW_NONE	3W	/* not genewated */

/* HDMI_SOFT_WST bits */
#define WESET_DC		BIT(7)	/* Weset deep cowow moduwe */
#define WESET_HDCP		BIT(6)	/* Weset HDCP moduwe */
#define WESET_KSV		BIT(5)	/* Weset KSV-FIFO */
#define WESET_SCFG		BIT(4)	/* Weset HDCP and wepeatew function */
#define WESET_HCFG		BIT(3)	/* Weset HDCP DDC pawt */
#define WESET_PA		BIT(2)	/* Weset powawity adjust */
#define WESET_EP		BIT(1)	/* Weset Ewwow pwotection */
#define WESET_TMDS		BIT(0)	/* Weset TMDS (cawib, encoding, fwow) */

/* HDMI_INFO_WST bits */
#define NACK_HDCP		BIT(7)	/* No ACK on HDCP wequest */
#define WESET_FIFO		BIT(4)	/* Weset Audio FIFO contwow */
#define WESET_GAMUT		BIT(3)	/* Cweaw Gamut packet */
#define WESET_AI		BIT(2)	/* Cweaw ACP and ISWC packets */
#define WESET_IF		BIT(1)	/* Cweaw aww Audio infofwame packets */
#define WESET_AUDIO		BIT(0)	/* Weset Audio FIFO contwow */

/* HDCP_BCAPS bits */
#define HDCP_HDMI		BIT(7)	/* HDCP suppowts HDMI (vs DVI onwy) */
#define HDCP_WEPEATEW		BIT(6)	/* HDCP suppowts wepeatew function */
#define HDCP_WEADY		BIT(5)	/* set by wepeatew function */
#define HDCP_FAST		BIT(4)	/* Up to 400kHz */
#define HDCP_11			BIT(1)	/* HDCP 1.1 suppowted */
#define HDCP_FAST_WEAUTH	BIT(0)	/* fast weauthentication suppowted */

/* Audio output fowmattew */
#define AUDIO_WAYOUT_SP_FWAG	BIT(2)	/* sp fwag used by FIFO */
#define AUDIO_WAYOUT_MANUAW	BIT(1)	/* manuaw wayout (vs pew pkt) */
#define AUDIO_WAYOUT_WAYOUT1	BIT(0)  /* Wayout1: AP0-3 vs Wayout0:AP0 */

/* masks fow intewwupt status wegistews */
#define MASK_SUS_STATUS		0x1F
#define WAST_STATE_WEACHED	0x1B
#define MASK_CWK_STABWE		0x04
#define MASK_CWK_ACTIVE		0x02
#define MASK_SUS_STATE		0x10
#define MASK_SW_FIFO_FIFO_CTWW	0x30
#define MASK_AUDIO_FWAG		0x10

/* Wate measuwement */
#define WATE_WEFTIM_ENABWE	0x01
#define CWK_MIN_WATE		0x0057e4
#define CWK_MAX_WATE		0x0395f8
#define WDW_CFG_VAW		0x82
#define DC_FIWTEW_VAW		0x31

/* Infofwame */
#define VS_HDMI_IF_UPDATE	0x0200
#define VS_HDMI_IF		0x0201
#define VS_BK1_IF_UPDATE	0x0220
#define VS_BK1_IF		0x0221
#define VS_BK2_IF_UPDATE	0x0240
#define VS_BK2_IF		0x0241
#define AVI_IF_UPDATE		0x0260
#define AVI_IF			0x0261
#define SPD_IF_UPDATE		0x0280
#define SPD_IF			0x0281
#define AUD_IF_UPDATE		0x02a0
#define AUD_IF			0x02a1
#define MPS_IF_UPDATE		0x02c0
#define MPS_IF			0x02c1
