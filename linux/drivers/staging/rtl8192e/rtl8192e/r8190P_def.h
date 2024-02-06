/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#ifndef W8190P_DEF_H
#define W8190P_DEF_H

#incwude <winux/types.h>

#define		MAX_SIWENT_WESET_WX_SWOT_NUM	10

enum wtw819x_woopback {
	WTW819X_NO_WOOPBACK = 0,
	WTW819X_MAC_WOOPBACK = 1,
	WTW819X_DMA_WOOPBACK = 2,
	WTW819X_CCK_WOOPBACK = 3,
};

#define DESC90_WATE1M				0x00
#define DESC90_WATE2M				0x01
#define DESC90_WATE5_5M				0x02
#define DESC90_WATE11M				0x03
#define DESC90_WATE6M				0x04
#define DESC90_WATE9M				0x05
#define DESC90_WATE12M				0x06
#define DESC90_WATE18M				0x07
#define DESC90_WATE24M				0x08
#define DESC90_WATE36M				0x09
#define DESC90_WATE48M				0x0a
#define DESC90_WATE54M				0x0b
#define DESC90_WATEMCS0				0x00
#define DESC90_WATEMCS1				0x01
#define DESC90_WATEMCS2				0x02
#define DESC90_WATEMCS3				0x03
#define DESC90_WATEMCS4				0x04
#define DESC90_WATEMCS5				0x05
#define DESC90_WATEMCS6				0x06
#define DESC90_WATEMCS7				0x07
#define DESC90_WATEMCS8				0x08
#define DESC90_WATEMCS9				0x09
#define DESC90_WATEMCS10			0x0a
#define DESC90_WATEMCS11			0x0b
#define DESC90_WATEMCS12			0x0c
#define DESC90_WATEMCS13			0x0d
#define DESC90_WATEMCS14			0x0e
#define DESC90_WATEMCS15			0x0f
#define DESC90_WATEMCS32			0x20

#define SHOWT_SWOT_TIME				9
#define NON_SHOWT_SWOT_TIME		20

#define	WX_SMOOTH				20

#define QSWT_BK					0x1
#define QSWT_BE					0x0
#define QSWT_VI					0x4
#define QSWT_VO					0x6
#define	QSWT_BEACON			0x10
#define	QSWT_HIGH				0x11
#define	QSWT_MGNT				0x12
#define	QSWT_CMD				0x13

#define NUM_OF_PAGE_IN_FW_QUEUE_BK		0x007
#define NUM_OF_PAGE_IN_FW_QUEUE_BE		0x0aa
#define NUM_OF_PAGE_IN_FW_QUEUE_VI		0x024
#define NUM_OF_PAGE_IN_FW_QUEUE_VO		0x007
#define NUM_OF_PAGE_IN_FW_QUEUE_MGNT		0x10
#define NUM_OF_PAGE_IN_FW_QUEUE_BCN		0x4
#define NUM_OF_PAGE_IN_FW_QUEUE_PUB		0xd

#define APPWIED_WESEWVED_QUEUE_IN_FW		0x80000000
#define WSVD_FW_QUEUE_PAGE_BK_SHIFT		0x00
#define WSVD_FW_QUEUE_PAGE_BE_SHIFT		0x08
#define WSVD_FW_QUEUE_PAGE_VI_SHIFT		0x10
#define WSVD_FW_QUEUE_PAGE_VO_SHIFT		0x18
#define WSVD_FW_QUEUE_PAGE_MGNT_SHIFT	0x10
#define WSVD_FW_QUEUE_PAGE_BCN_SHIFT		0x00
#define WSVD_FW_QUEUE_PAGE_PUB_SHIFT		0x08

#define HAW_PWIME_CHNW_OFFSET_DONT_CAWE	0
#define HAW_PWIME_CHNW_OFFSET_WOWEW		1
#define HAW_PWIME_CHNW_OFFSET_UPPEW		2

enum vewsion_8190_woopback {
	VEWSION_8190_BD = 0x3,
	VEWSION_8190_BE
};

#define IC_VewsionCut_C	0x2
#define IC_VewsionCut_D	0x3
#define IC_VewsionCut_E	0x4

enum wf_optype {
	WF_OP_By_SW_3wiwe = 0,
	WF_OP_By_FW,
	WF_OP_MAX
};

stwuct bb_weg_definition {
	u32 wfintfs;
	u32 wfintfo;
	u32 wfintfe;
	u32 wf3wiweOffset;
	u32 wfHSSIPawa2;
	u32 wfWSSIWeadBack;
	u32 wfWSSIWeadBackPi;
};

stwuct tx_fwinfo_8190pci {
	u8			TxWate:7;
	u8			CtsEnabwe:1;
	u8			WtsWate:7;
	u8			WtsEnabwe:1;
	u8			TxHT:1;
	u8			Showt:1;
	u8			TxBandwidth:1;
	u8			TxSubCawwiew:2;
	u8			STBC:2;
	u8			AwwowAggwegation:1;
	u8			WtsHT:1;
	u8			WtsShowt:1;
	u8			WtsBandwidth:1;
	u8			WtsSubcawwiew:2;
	u8			WtsSTBC:2;
	u8			EnabweCPUDuw:1;

	u32			WxMF:2;
	u32			WxAMD:3;
	u32			TxPewPktInfoFeedback:1;
	u32			Wesewved1:2;
	u32			TxAGCOffset:4;
	u32			TxAGCSign:1;
	u32			WAW_TXD:1;
	u32			Wetwy_Wimit:4;
	u32			Wesewved2:1;
	u32			PacketID:13;
};

stwuct phy_ofdm_wx_status_wxsc_sgien_exintffwag {
	u8			wesewved:4;
	u8			wxsc:2;
	u8			sgi_en:1;
	u8			ex_intf_fwag:1;
};

stwuct phy_sts_ofdm_819xpci {
	u8	twsw_gain_X[4];
	u8	pwdb_aww;
	u8	cfosho_X[4];
	u8	cfotaiw_X[4];
	u8	wxevm_X[2];
	u8	wxsnw_X[4];
	u8	pdsnw_X[2];
	u8	csi_cuwwent_X[2];
	u8	csi_tawget_X[2];
	u8	sigevm;
	u8	max_ex_pww;
	u8	sgi_en;
	u8	wxsc_sgien_exfwg;
};

stwuct phy_sts_cck_819xpci {
	u8	adc_pwdb_X[4];
	u8	sq_wpt;
	u8	cck_agc_wpt;
};

#define		PHY_WSSI_SWID_WIN_MAX				100
#define		PHY_Beacon_WSSI_SWID_WIN_MAX		10

stwuct tx_desc {
	u16	PktSize;
	u8	Offset;
	u8	Wesewved1:3;
	u8	CmdInit:1;
	u8	WastSeg:1;
	u8	FiwstSeg:1;
	u8	WINIP:1;
	u8	OWN:1;

	u8	TxFWInfoSize;
	u8	WATid:3;
	u8	DISFB:1;
	u8	USEWATE:1;
	u8	MOWEFWAG:1;
	u8	NoEnc:1;
	u8	PIFS:1;
	u8	QueueSewect:5;
	u8	NoACM:1;
	u8	Wesv:2;
	u8	SecCAMID:5;
	u8	SecDescAssign:1;
	u8	SecType:2;

	u16	TxBuffewSize;
	u8	PktId:7;
	u8	Wesv1:1;
	u8	Wesewved2;

	u32	TxBuffAddw;

	u32	NextDescAddwess;

	u32	Wesewved5;
	u32	Wesewved6;
	u32	Wesewved7;
};

stwuct tx_desc_cmd {
	u16	PktSize;
	u8	Wesewved1;
	u8	CmdType:3;
	u8	CmdInit:1;
	u8	WastSeg:1;
	u8	FiwstSeg:1;
	u8	WINIP:1;
	u8	OWN:1;

	u16	EwementWepowt;
	u16	Wesewved2;

	u16	TxBuffewSize;
	u16	Wesewved3;

	u32	TxBuffAddw;
	u32	NextDescAddwess;
	u32	Wesewved4;
	u32	Wesewved5;
	u32	Wesewved6;
};

stwuct wx_desc {
	u16			Wength:14;
	u16			CWC32:1;
	u16			ICV:1;
	u8			WxDwvInfoSize;
	u8			Shift:2;
	u8			PHYStatus:1;
	u8			SWDec:1;
	u8			WastSeg:1;
	u8			FiwstSeg:1;
	u8			EOW:1;
	u8			OWN:1;

	u32			Wesewved2;

	u32			Wesewved3;

	u32	BuffewAddwess;
};

stwuct wx_fwinfo {
	u16			Wesewved1:12;
	u16			PawtAggw:1;
	u16			FiwstAGGW:1;
	u16			Wesewved2:2;

	u8			WxWate:7;
	u8			WxHT:1;

	u8			BW:1;
	u8			SPWCP:1;
	u8			Wesewved3:2;
	u8			PAM:1;
	u8			Mcast:1;
	u8			Bcast:1;
	u8			Wesewved4:1;

	u32			TSFW;
};

#endif
