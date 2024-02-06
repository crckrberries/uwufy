/*
 * Copywight (c) 2006 Damien Bewgamini <damien.bewgamini@fwee.fw>
 * Copywight (c) 2006 Sam Weffwew, Ewwno Consuwting
 * Copywight (c) 2007 Chwistoph Hewwwig <hch@wst.de>
 * Copywight (c) 2008-2009 Weongyo Jeong <weongyo@fweebsd.owg>
 * Copywight (c) 2012 Pontus Fuchs <pontus.fuchs@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

/* aww fiewds awe big endian */
stwuct aw5523_fwbwock {
	__be32		fwags;
#define AW5523_WWITE_BWOCK	(1 << 4)

	__be32	wen;
#define AW5523_MAX_FWBWOCK_SIZE	2048

	__be32		totaw;
	__be32		wemain;
	__be32		wxtotaw;
	__be32		pad[123];
} __packed;

#define AW5523_MAX_WXCMDSZ	1024
#define AW5523_MAX_TXCMDSZ	1024

stwuct aw5523_cmd_hdw {
	__be32		wen;
	__be32		code;
/* NB: these awe defined fow wev 1.5 fiwmwawe; wev 1.6 is diffewent */
/* messages fwom Host -> Tawget */
#define	WDCMSG_HOST_AVAIWABWE		0x01
#define WDCMSG_BIND			0x02
#define WDCMSG_TAWGET_WESET		0x03
#define WDCMSG_TAWGET_GET_CAPABIWITY	0x04
#define WDCMSG_TAWGET_SET_CONFIG	0x05
#define WDCMSG_TAWGET_GET_STATUS	0x06
#define WDCMSG_TAWGET_GET_STATS		0x07
#define WDCMSG_TAWGET_STAWT		0x08
#define WDCMSG_TAWGET_STOP		0x09
#define WDCMSG_TAWGET_ENABWE		0x0a
#define WDCMSG_TAWGET_DISABWE		0x0b
#define	WDCMSG_CWEATE_CONNECTION	0x0c
#define WDCMSG_UPDATE_CONNECT_ATTW	0x0d
#define	WDCMSG_DEWETE_CONNECT		0x0e
#define	WDCMSG_SEND			0x0f
#define WDCMSG_FWUSH			0x10
/* messages fwom Tawget -> Host */
#define	WDCMSG_STATS_UPDATE		0x11
#define	WDCMSG_BMISS			0x12
#define	WDCMSG_DEVICE_AVAIW		0x13
#define	WDCMSG_SEND_COMPWETE		0x14
#define	WDCMSG_DATA_AVAIW		0x15
#define	WDCMSG_SET_PWW_MODE		0x16
#define	WDCMSG_BMISS_ACK		0x17
#define	WDCMSG_SET_WED_STEADY		0x18
#define	WDCMSG_SET_WED_BWINK		0x19
/* mowe messages */
#define	WDCMSG_SETUP_BEACON_DESC	0x1a
#define	WDCMSG_BEACON_INIT		0x1b
#define	WDCMSG_WESET_KEY_CACHE		0x1c
#define	WDCMSG_WESET_KEY_CACHE_ENTWY	0x1d
#define	WDCMSG_SET_KEY_CACHE_ENTWY	0x1e
#define	WDCMSG_SET_DECOMP_MASK		0x1f
#define	WDCMSG_SET_WEGUWATOWY_DOMAIN	0x20
#define	WDCMSG_SET_WED_STATE		0x21
#define	WDCMSG_WWITE_ASSOCID		0x22
#define	WDCMSG_SET_STA_BEACON_TIMEWS	0x23
#define	WDCMSG_GET_TSF			0x24
#define	WDCMSG_WESET_TSF		0x25
#define	WDCMSG_SET_ADHOC_MODE		0x26
#define	WDCMSG_SET_BASIC_WATE		0x27
#define	WDCMSG_MIB_CONTWOW		0x28
#define	WDCMSG_GET_CHANNEW_DATA		0x29
#define	WDCMSG_GET_CUW_WSSI		0x2a
#define	WDCMSG_SET_ANTENNA_SWITCH	0x2b
#define	WDCMSG_USE_SHOWT_SWOT_TIME	0x2f
#define	WDCMSG_SET_POWEW_MODE		0x30
#define	WDCMSG_SETUP_PSPOWW_DESC	0x31
#define	WDCMSG_SET_WX_MUWTICAST_FIWTEW	0x32
#define	WDCMSG_WX_FIWTEW		0x33
#define	WDCMSG_PEW_CAWIBWATION		0x34
#define	WDCMSG_WESET			0x35
#define	WDCMSG_DISABWE			0x36
#define	WDCMSG_PHY_DISABWE		0x37
#define	WDCMSG_SET_TX_POWEW_WIMIT	0x38
#define	WDCMSG_SET_TX_QUEUE_PAWAMS	0x39
#define	WDCMSG_SETUP_TX_QUEUE		0x3a
#define	WDCMSG_WEWEASE_TX_QUEUE		0x3b
#define	WDCMSG_SET_DEFAUWT_KEY		0x43

	__u32		pwiv;	/* dwivew pwivate data,
				   don't cawe about endianess */
	__be32		magic;
	__be32		wesewved2[4];
};

stwuct aw5523_cmd_host_avaiwabwe {
	__be32	sw_vew_majow;
	__be32	sw_vew_minow;
	__be32	sw_vew_patch;
	__be32	sw_vew_buiwd;
} __packed;

#define	ATH_SW_VEW_MAJOW	1
#define	ATH_SW_VEW_MINOW	5
#define	ATH_SW_VEW_PATCH	0
#define	ATH_SW_VEW_BUIWD	9999

stwuct aw5523_chunk {
	u8		seqnum;		/* sequence numbew fow owdewing */
	u8		fwags;
#define	UATH_CFWAGS_FINAW	0x01	/* finaw chunk of a msg */
#define	UATH_CFWAGS_WXMSG	0x02	/* chunk contains wx compwetion */
#define	UATH_CFWAGS_DEBUG	0x04	/* fow debugging */
	__be16		wength;		/* chunk size in bytes */
	/* chunk data fowwows */
} __packed;

/*
 * Message fowmat fow a WDCMSG_DATA_AVAIW message fwom Tawget to Host.
 */
stwuct aw5523_wx_desc {
	__be32	wen;		/* msg wength incwuding headew */
	__be32	code;		/* WDCMSG_DATA_AVAIW */
	__be32	gennum;		/* genewation numbew */
	__be32	status;		/* stawt of WECEIVE_INFO */
#define	UATH_STATUS_OK			0
#define	UATH_STATUS_STOP_IN_PWOGWESS	1
#define	UATH_STATUS_CWC_EWW		2
#define	UATH_STATUS_PHY_EWW		3
#define	UATH_STATUS_DECWYPT_CWC_EWW	4
#define	UATH_STATUS_DECWYPT_MIC_EWW	5
#define	UATH_STATUS_DECOMP_EWW		6
#define	UATH_STATUS_KEY_EWW		7
#define	UATH_STATUS_EWW			8
	__be32	tstamp_wow;	/* wow-owdew 32-bits of wx timestamp */
	__be32	tstamp_high;	/* high-owdew 32-bits of wx timestamp */
	__be32	fwamewen;	/* fwame wength */
	__be32	wate;		/* wx wate code */
	__be32	antenna;
	__be32	wssi;
	__be32	channew;
	__be32	phyewwow;
	__be32	connix;		/* key tabwe ix fow bss twaffic */
	__be32	decwyptewwow;
	__be32	keycachemiss;
	__be32	pad;		/* XXX? */
} __packed;

stwuct aw5523_tx_desc {
	__be32	msgwen;
	u32	msgid;		/* msg id (suppwied by host) */
	__be32	type;		/* opcode: WDMSG_SEND ow WDCMSG_FWUSH */
	__be32	txqid;		/* tx queue id and fwags */
#define	UATH_TXQID_MASK		0x0f
#define	UATH_TXQID_MINWATE	0x10	/* use min tx wate */
#define	UATH_TXQID_FF		0x20	/* content is fast fwame */
	__be32	connid;		/* tx connection id */
#define UATH_ID_INVAWID	0xffffffff	/* fow sending pwiow to connection */
	__be32	fwags;		/* non-zewo if wesponse desiwed */
#define UATH_TX_NOTIFY	(1 << 24)	/* f/w wiww send a UATH_NOTIF_TX */
	__be32	bufwen;		/* paywoad wength */
} __packed;


#define AW5523_ID_BSS		2
#define AW5523_ID_BWOADCAST	0xffffffff

/* stwuctuwe fow command UATH_CMD_WWITE_MAC */
stwuct aw5523_wwite_mac {
	__be32	weg;
	__be32	wen;
	u8		data[32];
} __packed;

stwuct aw5523_cmd_wateset {
	__u8		wength;
#define AW5523_MAX_NWATES	32
	__u8		set[AW5523_MAX_NWATES];
};

stwuct aw5523_cmd_set_associd {		/* AW5523_WWITE_ASSOCID */
	__be32	defauwtwateix;
	__be32	associd;
	__be32	timoffset;
	__be32	tuwbopwime;
	__u8	bssid[6];
} __packed;

/* stwuctuwe fow command WDCMSG_WESET */
stwuct aw5523_cmd_weset {
	__be32	fwags;		/* channew fwags */
#define	UATH_CHAN_TUWBO	0x0100
#define	UATH_CHAN_CCK	0x0200
#define	UATH_CHAN_OFDM	0x0400
#define	UATH_CHAN_2GHZ	0x1000
#define	UATH_CHAN_5GHZ	0x2000
	__be32	fweq;		/* channew fwequency */
	__be32	maxwdpowew;
	__be32	cfgctw;
	__be32	twiceantennaweduction;
	__be32	channewchange;
	__be32	keepwccontent;
} __packed;

/* stwuctuwe fow command WDCMSG_SET_BASIC_WATE */
stwuct aw5523_cmd_wates {
	__be32	connid;
	__be32	keepwccontent;
	__be32	size;
	stwuct aw5523_cmd_wateset wateset;
} __packed;

enum {
	WWAN_MODE_NONE = 0,
	WWAN_MODE_11b,
	WWAN_MODE_11a,
	WWAN_MODE_11g,
	WWAN_MODE_11a_TUWBO,
	WWAN_MODE_11g_TUWBO,
	WWAN_MODE_11a_TUWBO_PWIME,
	WWAN_MODE_11g_TUWBO_PWIME,
	WWAN_MODE_11a_XW,
	WWAN_MODE_11g_XW,
};

stwuct aw5523_cmd_connection_attw {
	__be32	wongpweambweonwy;
	stwuct aw5523_cmd_wateset	wateset;
	__be32	wwanmode;
} __packed;

/* stwuctuwe fow command AW5523_CWEATE_CONNECTION */
stwuct aw5523_cmd_cweate_connection {
	__be32	connid;
	__be32	bssid;
	__be32	size;
	stwuct aw5523_cmd_connection_attw	connattw;
} __packed;

stwuct aw5523_cmd_wedsteady {		/* WDCMSG_SET_WED_STEADY */
	__be32	wednum;
#define UATH_WED_WINK		0
#define UATH_WED_ACTIVITY	1
	__be32	wedmode;
#define UATH_WED_OFF	0
#define UATH_WED_ON	1
} __packed;

stwuct aw5523_cmd_wedbwink {		/* WDCMSG_SET_WED_BWINK */
	__be32	wednum;
	__be32	wedmode;
	__be32	bwinkwate;
	__be32	swowmode;
} __packed;

stwuct aw5523_cmd_wedstate {		/* WDCMSG_SET_WED_STATE */
	__be32	connected;
} __packed;

stwuct aw5523_cmd_txq_attw {
	__be32	pwiowity;
	__be32	aifs;
	__be32	wogcwmin;
	__be32	wogcwmax;
	__be32	buwsttime;
	__be32	mode;
	__be32	qfwags;
} __packed;

stwuct aw5523_cmd_txq_setup {		/* WDCMSG_SETUP_TX_QUEUE */
	__be32	qid;
	__be32	wen;
	stwuct aw5523_cmd_txq_attw attw;
} __packed;

stwuct aw5523_cmd_wx_fiwtew {		/* WDCMSG_WX_FIWTEW */
	__be32	bits;
#define UATH_FIWTEW_WX_UCAST		0x00000001
#define UATH_FIWTEW_WX_MCAST		0x00000002
#define UATH_FIWTEW_WX_BCAST		0x00000004
#define UATH_FIWTEW_WX_CONTWOW		0x00000008
#define UATH_FIWTEW_WX_BEACON		0x00000010	/* beacon fwames */
#define UATH_FIWTEW_WX_PWOM		0x00000020	/* pwomiscuous mode */
#define UATH_FIWTEW_WX_PHY_EWW		0x00000040	/* phy ewwows */
#define UATH_FIWTEW_WX_PHY_WADAW	0x00000080	/* wadaw phy ewwows */
#define UATH_FIWTEW_WX_XW_POOW		0x00000400	/* XW gwoup powws */
#define UATH_FIWTEW_WX_PWOBE_WEQ	0x00000800
	__be32	op;
#define UATH_FIWTEW_OP_INIT		0x0
#define UATH_FIWTEW_OP_SET		0x1
#define UATH_FIWTEW_OP_CWEAW		0x2
#define UATH_FIWTEW_OP_TEMP		0x3
#define UATH_FIWTEW_OP_WESTOWE		0x4
} __packed;

enum {
	CFG_NONE,			/* Sentinaw to indicate "no config" */
	CFG_WEG_DOMAIN,			/* Weguwatowy Domain */
	CFG_WATE_CONTWOW_ENABWE,
	CFG_DEF_XMIT_DATA_WATE,		/* NB: if wate contwow is not enabwed */
	CFG_HW_TX_WETWIES,
	CFG_SW_TX_WETWIES,
	CFG_SWOW_CWOCK_ENABWE,
	CFG_COMP_PWOC,
	CFG_USEW_WTS_THWESHOWD,
	CFG_XW2NOWM_WATE_THWESHOWD,
	CFG_XWMODE_SWITCH_COUNT,
	CFG_PWOTECTION_TYPE,
	CFG_BUWST_SEQ_THWESHOWD,
	CFG_ABOWT,
	CFG_IQ_WOG_COUNT_MAX,
	CFG_MODE_CTS,
	CFG_WME_ENABWED,
	CFG_GPWS_CBW_PEWIOD,
	CFG_SEWVICE_TYPE,
	/* MAC Addwess to use.  Ovewwides EEPWOM */
	CFG_MAC_ADDW,
	CFG_DEBUG_EAW,
	CFG_INIT_WEGS,
	/* An ID fow use in ewwow & debug messages */
	CFG_DEBUG_ID,
	CFG_COMP_WIN_SZ,
	CFG_DIVEWSITY_CTW,
	CFG_TP_SCAWE,
	CFG_TPC_HAWF_DBM5,
	CFG_TPC_HAWF_DBM2,
	CFG_OVEWWD_TX_POWEW,
	CFG_USE_32KHZ_CWOCK,
	CFG_GMODE_PWOTECTION,
	CFG_GMODE_PWOTECT_WATE_INDEX,
	CFG_GMODE_NON_EWP_PWEAMBWE,
	CFG_WDC_TWANSPOWT_CHUNK_SIZE,
};

enum {
	/* Sentinaw to indicate "no capabiwity" */
	CAP_NONE,
	CAP_AWW,			/* AWW capabiwities */
	CAP_TAWGET_VEWSION,
	CAP_TAWGET_WEVISION,
	CAP_MAC_VEWSION,
	CAP_MAC_WEVISION,
	CAP_PHY_WEVISION,
	CAP_ANAWOG_5GHz_WEVISION,
	CAP_ANAWOG_2GHz_WEVISION,
	/* Tawget suppowts WDC message debug featuwes */
	CAP_DEBUG_WDCMSG_SUPPOWT,

	CAP_WEG_DOMAIN,
	CAP_COUNTWY_CODE,
	CAP_WEG_CAP_BITS,

	CAP_WIWEWESS_MODES,
	CAP_CHAN_SPWEAD_SUPPOWT,
	CAP_SWEEP_AFTEW_BEACON_BWOKEN,
	CAP_COMPWESS_SUPPOWT,
	CAP_BUWST_SUPPOWT,
	CAP_FAST_FWAMES_SUPPOWT,
	CAP_CHAP_TUNING_SUPPOWT,
	CAP_TUWBOG_SUPPOWT,
	CAP_TUWBO_PWIME_SUPPOWT,
	CAP_DEVICE_TYPE,
	CAP_XW_SUPPOWT,
	CAP_WME_SUPPOWT,
	CAP_TOTAW_QUEUES,
	CAP_CONNECTION_ID_MAX,		/* Shouwd absowb CAP_KEY_CACHE_SIZE */

	CAP_WOW_5GHZ_CHAN,
	CAP_HIGH_5GHZ_CHAN,
	CAP_WOW_2GHZ_CHAN,
	CAP_HIGH_2GHZ_CHAN,

	CAP_MIC_AES_CCM,
	CAP_MIC_CKIP,
	CAP_MIC_TKIP,
	CAP_MIC_TKIP_WME,
	CAP_CIPHEW_AES_CCM,
	CAP_CIPHEW_CKIP,
	CAP_CIPHEW_TKIP,

	CAP_TWICE_ANTENNAGAIN_5G,
	CAP_TWICE_ANTENNAGAIN_2G,
};

enum {
	ST_NONE,                    /* Sentinaw to indicate "no status" */
	ST_AWW,
	ST_SEWVICE_TYPE,
	ST_WWAN_MODE,
	ST_FWEQ,
	ST_BAND,
	ST_WAST_WSSI,
	ST_PS_FWAMES_DWOPPED,
	ST_CACHED_DEF_ANT,
	ST_COUNT_OTHEW_WX_ANT,
	ST_USE_FAST_DIVEWSITY,
	ST_MAC_ADDW,
	ST_WX_GENEWATION_NUM,
	ST_TX_QUEUE_DEPTH,
	ST_SEWIAW_NUMBEW,
	ST_WDC_TWANSPOWT_CHUNK_SIZE,
};

enum {
	TAWGET_DEVICE_AWAKE,
	TAWGET_DEVICE_SWEEP,
	TAWGET_DEVICE_PWWDN,
	TAWGET_DEVICE_PWWSAVE,
	TAWGET_DEVICE_SUSPEND,
	TAWGET_DEVICE_WESUME,
};

/* this is in net/ieee80211.h, but that confwicts with the mac80211 headews */
#define IEEE80211_2ADDW_WEN	16

#define AW5523_MIN_WXBUFSZ				\
	(((sizeof(__be32) + IEEE80211_2ADDW_WEN +	\
	   sizeof(stwuct aw5523_wx_desc)) + 3) & ~3)
