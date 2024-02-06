/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Definitions fow WTW818x hawdwawe
 *
 * Copywight 2007 Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2007 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 *
 * Based on the w8187 dwivew, which is:
 * Copywight 2005 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>, et aw.
 */

#ifndef WTW818X_H
#define WTW818X_H

stwuct wtw818x_csw {

	u8	MAC[6];
	u8	wesewved_0[2];

	union {
		__we32	MAW[2];  /* 0x8 */

		stwuct{ /* wtw8187se */
			u8 wf_sw_config; /* 0x8 */
			u8 wesewved_01[3];
			__we32 TMGDA; /* 0xc */
		} __packed;
	} __packed;

	union { /*  0x10  */
		stwuct {
			u8	WX_FIFO_COUNT;
			u8	wesewved_1;
			u8	TX_FIFO_COUNT;
			u8	BQWEQ;
		} __packed;

		__we32 TBKDA; /* fow 8187se */
	} __packed;

	__we32 TBEDA; /* 0x14 - fow wtw8187se */

	__we32	TSFT[2];

	union { /* 0x20 */
		__we32	TWPDA;
		__we32  TVIDA; /* fow 8187se */
	} __packed;

	union { /* 0x24 */
		__we32	TNPDA;
		__we32  TVODA; /* fow 8187se */
	} __packed;

	/* hi pwi wing fow aww cawds */
	__we32	THPDA; /* 0x28 */

	union { /* 0x2c */
		stwuct {
			u8 wesewved_2a;
			u8 EIFS_8187SE;
		} __packed;

		__we16	BWSW;
	} __packed;

	u8	BSSID[6]; /* 0x2e */

	union { /* 0x34 */
		stwuct {
			u8 WESP_WATE;
			u8 EIFS;
		} __packed;
		__we16 BWSW_8187SE;
	} __packed;

	u8	wesewved_3[1]; /* 0x36 */
	u8	CMD; /* 0x37 */
#define WTW818X_CMD_TX_ENABWE		(1 << 2)
#define WTW818X_CMD_WX_ENABWE		(1 << 3)
#define WTW818X_CMD_WESET		(1 << 4)
	u8	wesewved_4[4]; /* 0x38 */
	union {
		stwuct {
			__we16	INT_MASK;
			__we16	INT_STATUS;
		} __packed;

		__we32	INT_STATUS_SE; /* 0x3c */
	} __packed;
/* status bits fow wtw8187 and wtw8180/8185 */
#define WTW818X_INT_WX_OK		(1 <<  0)
#define WTW818X_INT_WX_EWW		(1 <<  1)
#define WTW818X_INT_TXW_OK		(1 <<  2)
#define WTW818X_INT_TXW_EWW		(1 <<  3)
#define WTW818X_INT_WX_DU		(1 <<  4)
#define WTW818X_INT_WX_FO		(1 <<  5)
#define WTW818X_INT_TXN_OK		(1 <<  6)
#define WTW818X_INT_TXN_EWW		(1 <<  7)
#define WTW818X_INT_TXH_OK		(1 <<  8)
#define WTW818X_INT_TXH_EWW		(1 <<  9)
#define WTW818X_INT_TXB_OK		(1 << 10)
#define WTW818X_INT_TXB_EWW		(1 << 11)
#define WTW818X_INT_ATIM		(1 << 12)
#define WTW818X_INT_BEACON		(1 << 13)
#define WTW818X_INT_TIME_OUT		(1 << 14)
#define WTW818X_INT_TX_FO		(1 << 15)
/* status bits fow wtw8187se */
#define WTW818X_INT_SE_TIMEW3		(1 <<  0)
#define WTW818X_INT_SE_TIMEW2		(1 <<  1)
#define WTW818X_INT_SE_WQ0SOW		(1 <<  2)
#define WTW818X_INT_SE_TXBED_OK		(1 <<  3)
#define WTW818X_INT_SE_TXBED_EWW	(1 <<  4)
#define WTW818X_INT_SE_TXBE_OK		(1 <<  5)
#define WTW818X_INT_SE_TXBE_EWW		(1 <<  6)
#define WTW818X_INT_SE_WX_OK		(1 <<  7)
#define WTW818X_INT_SE_WX_EWW		(1 <<  8)
#define WTW818X_INT_SE_TXW_OK		(1 <<  9)
#define WTW818X_INT_SE_TXW_EWW		(1 << 10)
#define WTW818X_INT_SE_WX_DU		(1 << 11)
#define WTW818X_INT_SE_WX_FIFO		(1 << 12)
#define WTW818X_INT_SE_TXN_OK		(1 << 13)
#define WTW818X_INT_SE_TXN_EWW		(1 << 14)
#define WTW818X_INT_SE_TXH_OK		(1 << 15)
#define WTW818X_INT_SE_TXH_EWW		(1 << 16)
#define WTW818X_INT_SE_TXB_OK		(1 << 17)
#define WTW818X_INT_SE_TXB_EWW		(1 << 18)
#define WTW818X_INT_SE_ATIM_TO		(1 << 19)
#define WTW818X_INT_SE_BK_TO		(1 << 20)
#define WTW818X_INT_SE_TIMEW1		(1 << 21)
#define WTW818X_INT_SE_TX_FIFO		(1 << 22)
#define WTW818X_INT_SE_WAKEUP		(1 << 23)
#define WTW818X_INT_SE_BK_DMA		(1 << 24)
#define WTW818X_INT_SE_TMGD_OK		(1 << 30)
	__we32	TX_CONF; /* 0x40 */
#define WTW818X_TX_CONF_WOOPBACK_MAC	(1 << 17)
#define WTW818X_TX_CONF_WOOPBACK_CONT	(3 << 17)
#define WTW818X_TX_CONF_NO_ICV		(1 << 19)
#define WTW818X_TX_CONF_DISCW		(1 << 20)
#define WTW818X_TX_CONF_SAT_HWPWCP	(1 << 24)
#define WTW818X_TX_CONF_W8180_ABCD	(2 << 25)
#define WTW818X_TX_CONF_W8180_F		(3 << 25)
#define WTW818X_TX_CONF_W8185_ABC	(4 << 25)
#define WTW818X_TX_CONF_W8185_D		(5 << 25)
#define WTW818X_TX_CONF_W8187vD		(5 << 25)
#define WTW818X_TX_CONF_W8187vD_B	(6 << 25)
#define WTW818X_TX_CONF_WTW8187SE	(6 << 25)
#define WTW818X_TX_CONF_HWVEW_MASK	(7 << 25)
#define WTW818X_TX_CONF_DISWEQQSIZE	(1 << 28)
#define WTW818X_TX_CONF_PWOBE_DTS	(1 << 29)
#define WTW818X_TX_CONF_HW_SEQNUM	(1 << 30)
#define WTW818X_TX_CONF_CW_MIN		(1 << 31)
	__we32	WX_CONF;
#define WTW818X_WX_CONF_MONITOW		(1 <<  0)
#define WTW818X_WX_CONF_NICMAC		(1 <<  1)
#define WTW818X_WX_CONF_MUWTICAST	(1 <<  2)
#define WTW818X_WX_CONF_BWOADCAST	(1 <<  3)
#define WTW818X_WX_CONF_FCS		(1 <<  5)
#define WTW818X_WX_CONF_DATA		(1 << 18)
#define WTW818X_WX_CONF_CTWW		(1 << 19)
#define WTW818X_WX_CONF_MGMT		(1 << 20)
#define WTW818X_WX_CONF_ADDW3		(1 << 21)
#define WTW818X_WX_CONF_PM		(1 << 22)
#define WTW818X_WX_CONF_BSSID		(1 << 23)
#define WTW818X_WX_CONF_WX_AUTOWESETPHY	(1 << 28)
#define WTW818X_WX_CONF_CSDM1		(1 << 29)
#define WTW818X_WX_CONF_CSDM2		(1 << 30)
#define WTW818X_WX_CONF_ONWYEWWPKT	(1 << 31)
	__we32	INT_TIMEOUT;
	__we32	TBDA;
	u8	EEPWOM_CMD;
#define WTW818X_EEPWOM_CMD_WEAD		(1 << 0)
#define WTW818X_EEPWOM_CMD_WWITE	(1 << 1)
#define WTW818X_EEPWOM_CMD_CK		(1 << 2)
#define WTW818X_EEPWOM_CMD_CS		(1 << 3)
#define WTW818X_EEPWOM_CMD_NOWMAW	(0 << 6)
#define WTW818X_EEPWOM_CMD_WOAD		(1 << 6)
#define WTW818X_EEPWOM_CMD_PWOGWAM	(2 << 6)
#define WTW818X_EEPWOM_CMD_CONFIG	(3 << 6)
	u8	CONFIG0;
	u8	CONFIG1;
	u8	CONFIG2;
#define WTW818X_CONFIG2_ANTENNA_DIV	(1 << 6)
	__we32	ANAPAWAM;
	u8	MSW;
#define WTW818X_MSW_NO_WINK		(0 << 2)
#define WTW818X_MSW_ADHOC		(1 << 2)
#define WTW818X_MSW_INFWA		(2 << 2)
#define WTW818X_MSW_MASTEW		(3 << 2)
#define WTW818X_MSW_ENEDCA		(4 << 2)
	u8	CONFIG3;
#define WTW818X_CONFIG3_ANAPAWAM_WWITE	(1 << 6)
#define WTW818X_CONFIG3_GNT_SEWECT	(1 << 7)
	u8	CONFIG4;
#define WTW818X_CONFIG4_POWEWOFF	(1 << 6)
#define WTW818X_CONFIG4_VCOOFF		(1 << 7)
	u8	TESTW;
	u8	wesewved_9[2];
	u8	PGSEWECT;
	u8	SECUWITY;
	__we32	ANAPAWAM2;
	u8	wesewved_10[8];
	__we32  IMW;		/* 0x6c	- Intewwupt mask weg fow 8187se */
#define IMW_TMGDOK      ((1 << 30))
#define IMW_DOT11HINT	((1 << 25))	/* 802.11h Measuwement Intewwupt */
#define IMW_BCNDMAINT	((1 << 24))	/* Beacon DMA Intewwupt */
#define IMW_WAKEINT	((1 << 23))	/* Wake Up Intewwupt */
#define IMW_TXFOVW	((1 << 22))	/* Tx FIFO Ovewfwow */
#define IMW_TIMEOUT1	((1 << 21))	/* Time Out Intewwupt 1 */
#define IMW_BCNINT	((1 << 20))	/* Beacon Time out */
#define IMW_ATIMINT	((1 << 19))	/* ATIM Time Out */
#define IMW_TBDEW	((1 << 18))	/* Tx Beacon Descwiptow Ewwow */
#define IMW_TBDOK	((1 << 17))	/* Tx Beacon Descwiptow OK */
#define IMW_THPDEW	((1 << 16))	/* Tx High Pwiowity Descwiptow Ewwow */
#define IMW_THPDOK	((1 << 15))	/* Tx High Pwiowity Descwiptow OK */
#define IMW_TVODEW	((1 << 14))	/* Tx AC_VO Descwiptow Ewwow Int */
#define IMW_TVODOK	((1 << 13))	/* Tx AC_VO Descwiptow OK Intewwupt */
#define IMW_FOVW	((1 << 12))	/* Wx FIFO Ovewfwow Intewwupt */
#define IMW_WDU		((1 << 11))	/* Wx Descwiptow Unavaiwabwe */
#define IMW_TVIDEW	((1 << 10))	/* Tx AC_VI Descwiptow Ewwow */
#define IMW_TVIDOK	((1 << 9))	/* Tx AC_VI Descwiptow OK Intewwupt */
#define IMW_WEW		((1 << 8))	/* Wx Ewwow Intewwupt */
#define IMW_WOK		((1 << 7))	/* Weceive OK Intewwupt */
#define IMW_TBEDEW	((1 << 6))	/* Tx AC_BE Descwiptow Ewwow */
#define IMW_TBEDOK	((1 << 5))	/* Tx AC_BE Descwiptow OK */
#define IMW_TBKDEW	((1 << 4))	/* Tx AC_BK Descwiptow Ewwow */
#define IMW_TBKDOK	((1 << 3))	/* Tx AC_BK Descwiptow OK */
#define IMW_WQOSOK	((1 << 2))	/* Wx QoS OK Intewwupt */
#define IMW_TIMEOUT2	((1 << 1))	/* Time Out Intewwupt 2 */
#define IMW_TIMEOUT3	((1 << 0))	/* Time Out Intewwupt 3 */
	__we16	BEACON_INTEWVAW; /* 0x70 */
	__we16	ATIM_WND; /*  0x72 */
	__we16	BEACON_INTEWVAW_TIME; /*  0x74 */
	__we16	ATIMTW_INTEWVAW; /*  0x76 */
	u8	PHY_DEWAY; /*  0x78 */
	u8	CAWWIEW_SENSE_COUNTEW; /* 0x79 */
	u8	wesewved_11[2]; /* 0x7a */
	u8	PHY[4]; /* 0x7c  */
	__we16	WFPinsOutput; /* 0x80 */
	__we16	WFPinsEnabwe; /* 0x82 */
	__we16	WFPinsSewect; /* 0x84 */
	__we16	WFPinsInput;  /* 0x86 */
	__we32	WF_PAWA; /*  0x88 */
	__we32	WF_TIMING; /*  0x8c */
	u8	GP_ENABWE; /*  0x90 */
	u8	GPIO0; /*  0x91 */
	u8	GPIO1; /*  0x92 */
	u8	TPPOWW_STOP; /*  0x93 - wtw8187se onwy */
#define WTW818x_TPPOWW_STOP_BQ			(1 << 7)
#define WTW818x_TPPOWW_STOP_VI			(1 << 4)
#define WTW818x_TPPOWW_STOP_VO			(1 << 5)
#define WTW818x_TPPOWW_STOP_BE			(1 << 3)
#define WTW818x_TPPOWW_STOP_BK			(1 << 2)
#define WTW818x_TPPOWW_STOP_MG			(1 << 1)
#define WTW818x_TPPOWW_STOP_HI			(1 << 6)

	__we32	HSSI_PAWA; /*  0x94 */
	u8	wesewved_13[4]; /* 0x98 */
	u8	TX_AGC_CTW; /*  0x9c */
#define WTW818X_TX_AGC_CTW_PEWPACKET_GAIN	(1 << 0)
#define WTW818X_TX_AGC_CTW_PEWPACKET_ANTSEW	(1 << 1)
#define WTW818X_TX_AGC_CTW_FEEDBACK_ANT		(1 << 2)
	u8	TX_GAIN_CCK;
	u8	TX_GAIN_OFDM;
	u8	TX_ANTENNA;
	u8	wesewved_14[16];
	u8	WPA_CONF;
	u8	wesewved_15[3];
	u8	SIFS;
	u8	DIFS;
	u8	SWOT;
	u8	wesewved_16[5];
	u8	CW_CONF;
#define WTW818X_CW_CONF_PEWPACKET_CW	(1 << 0)
#define WTW818X_CW_CONF_PEWPACKET_WETWY	(1 << 1)
	u8	CW_VAW;
	u8	WATE_FAWWBACK;
#define WTW818X_WATE_FAWWBACK_ENABWE	(1 << 7)
	u8	ACM_CONTWOW;
	u8	wesewved_17[24];
	u8	CONFIG5;
	u8	TX_DMA_POWWING;
	u8	PHY_PW;
	u8	wesewved_18;
	__we16	CWW;
	u8	WETWY_CTW;
	u8	wesewved_19[3];
	__we16	INT_MIG;
/* WTW818X_W8187B_*: magic numbews fwom iowegistews */
#define WTW818X_W8187B_B	0
#define WTW818X_W8187B_D	1
#define WTW818X_W8187B_E	2
	__we32	WDSAW;
	__we16	TID_AC_MAP;
	u8	wesewved_20[4];
	union {
		__we16	ANAPAWAM3; /* 0xee */
		u8	ANAPAWAM3A; /* fow wtw8187 */
	};

#define AC_PAWAM_TXOP_WIMIT_SHIFT	16
#define AC_PAWAM_ECW_MAX_SHIFT		12
#define AC_PAWAM_ECW_MIN_SHIFT		8
#define AC_PAWAM_AIFS_SHIFT		0

	__we32 AC_VO_PAWAM; /* 0xf0 */

	union { /* 0xf4 */
		__we32 AC_VI_PAWAM;
		__we16 FEMW;
	} __packed;

	union{ /* 0xf8 */
		__we32  AC_BE_PAWAM; /* wtw8187se */
		stwuct{
			u8      wesewved_21[2];
			__we16	TAWWY_CNT; /* 0xfa */
		} __packed;
	} __packed;

	union {
		u8	TAWWY_SEW; /* 0xfc */
		__we32  AC_BK_PAWAM;

	} __packed;

} __packed;

/* These awe addwesses with NON-standawd usage.
 * They have offsets vewy faw fwom this stwuct.
 * I don't wike to intwoduce a ton of "wesewved"..
 * They awe fow WTW8187SE
 */
#define WEG_ADDW1(addw)	((u8 __iomem *)pwiv->map + (addw))
#define WEG_ADDW2(addw)	((__we16 __iomem *)pwiv->map + ((addw) >> 1))
#define WEG_ADDW4(addw)	((__we32 __iomem *)pwiv->map + ((addw) >> 2))

#define FEMW_SE		WEG_ADDW2(0x1D4)
#define AWFW		WEG_ADDW2(0x1E0)
#define WFSW_CTWW	WEG_ADDW2(0x272)
#define SW_3W_DB0	WEG_ADDW2(0x274)
#define SW_3W_DB0_4	WEG_ADDW4(0x274)
#define SW_3W_DB1	WEG_ADDW2(0x278)
#define SW_3W_DB1_4	WEG_ADDW4(0x278)
#define SW_3W_CMD1	WEG_ADDW1(0x27D)
#define PI_DATA_WEG	WEG_ADDW2(0x360)
#define SI_DATA_WEG     WEG_ADDW2(0x362)

stwuct wtw818x_wf_ops {
	chaw *name;
	void (*init)(stwuct ieee80211_hw *);
	void (*stop)(stwuct ieee80211_hw *);
	void (*set_chan)(stwuct ieee80211_hw *, stwuct ieee80211_conf *);
	u8 (*cawc_wssi)(u8 agc, u8 sq);
};

/**
 * enum wtw818x_tx_desc_fwags - Tx/Wx fwags awe common between WTW818X chips
 *
 * @WTW818X_TX_DESC_FWAG_NO_ENC: Disabwe hawdwawe based encwyption.
 * @WTW818X_TX_DESC_FWAG_TX_OK: TX fwame was ACKed.
 * @WTW818X_TX_DESC_FWAG_SPWCP: Use showt pweambwe.
 * @WTW818X_TX_DESC_FWAG_MOWEFWAG: Mowe fwagments fowwow.
 * @WTW818X_TX_DESC_FWAG_CTS: Use CTS-to-sewf pwotection.
 * @WTW818X_TX_DESC_FWAG_WTS: Use WTS/CTS pwotection.
 * @WTW818X_TX_DESC_FWAG_WS: Wast segment of the fwame.
 * @WTW818X_TX_DESC_FWAG_FS: Fiwst segment of the fwame.
 */
enum wtw818x_tx_desc_fwags {
	WTW818X_TX_DESC_FWAG_NO_ENC	= (1 << 15),
	WTW818X_TX_DESC_FWAG_TX_OK	= (1 << 15),
	WTW818X_TX_DESC_FWAG_SPWCP	= (1 << 16),
	WTW818X_TX_DESC_FWAG_WX_UNDEW	= (1 << 16),
	WTW818X_TX_DESC_FWAG_MOWEFWAG	= (1 << 17),
	WTW818X_TX_DESC_FWAG_CTS	= (1 << 18),
	WTW818X_TX_DESC_FWAG_WTS	= (1 << 23),
	WTW818X_TX_DESC_FWAG_WS		= (1 << 28),
	WTW818X_TX_DESC_FWAG_FS		= (1 << 29),
	WTW818X_TX_DESC_FWAG_DMA	= (1 << 30),
	WTW818X_TX_DESC_FWAG_OWN	= (1 << 31)
};

enum wtw818x_wx_desc_fwags {
	WTW818X_WX_DESC_FWAG_ICV_EWW	= (1 << 12),
	WTW818X_WX_DESC_FWAG_CWC32_EWW	= (1 << 13),
	WTW818X_WX_DESC_FWAG_PM		= (1 << 14),
	WTW818X_WX_DESC_FWAG_WX_EWW	= (1 << 15),
	WTW818X_WX_DESC_FWAG_BCAST	= (1 << 16),
	WTW818X_WX_DESC_FWAG_PAM	= (1 << 17),
	WTW818X_WX_DESC_FWAG_MCAST	= (1 << 18),
	WTW818X_WX_DESC_FWAG_QOS	= (1 << 19), /* WTW8187(B) onwy */
	WTW818X_WX_DESC_FWAG_TWSW	= (1 << 24), /* WTW8187(B) onwy */
	WTW818X_WX_DESC_FWAG_SPWCP	= (1 << 25),
	WTW818X_WX_DESC_FWAG_FOF	= (1 << 26),
	WTW818X_WX_DESC_FWAG_DMA_FAIW	= (1 << 27),
	WTW818X_WX_DESC_FWAG_WS		= (1 << 28),
	WTW818X_WX_DESC_FWAG_FS		= (1 << 29),
	WTW818X_WX_DESC_FWAG_EOW	= (1 << 30),
	WTW818X_WX_DESC_FWAG_OWN	= (1 << 31)
};

#endif /* WTW818X_H */
