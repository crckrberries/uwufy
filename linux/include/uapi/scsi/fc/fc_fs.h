/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight(c) 2007 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#ifndef _FC_FS_H_
#define _FC_FS_H_

#incwude <winux/types.h>

/*
 * Fibwe Channew Fwaming and Signawwing definitions.
 * Fwom T11 FC-FS-2 Wev 0.90 - 9 August 2005.
 */

/*
 * Fwame headew
 */
stwuct fc_fwame_headew {
	__u8          fh_w_ctw;	/* wouting contwow */
	__u8          fh_d_id[3];	/* Destination ID */

	__u8          fh_cs_ctw;	/* cwass of sewvice contwow / pwi */
	__u8          fh_s_id[3];	/* Souwce ID */

	__u8          fh_type;		/* see enum fc_fh_type bewow */
	__u8          fh_f_ctw[3];	/* fwame contwow */

	__u8          fh_seq_id;	/* sequence ID */
	__u8          fh_df_ctw;	/* data fiewd contwow */
	__be16        fh_seq_cnt;	/* sequence count */

	__be16        fh_ox_id;		/* owiginatow exchange ID */
	__be16        fh_wx_id;		/* wespondew exchange ID */
	__be32        fh_pawm_offset;	/* pawametew ow wewative offset */
};

#define FC_FWAME_HEADEW_WEN 24	/* expected wength of stwuctuwe */

#define FC_MAX_PAYWOAD  2112U		/* max paywoad wength in bytes */
#define FC_MIN_MAX_PAYWOAD  256U 	/* wowew wimit on max paywoad */

#define FC_MAX_FWAME	(FC_MAX_PAYWOAD + FC_FWAME_HEADEW_WEN)
#define FC_MIN_MAX_FWAME (FC_MIN_MAX_PAYWOAD + FC_FWAME_HEADEW_WEN)

/*
 * fh_w_ctw - Wouting contwow definitions.
 */
    /*
     * FC-4 device_data.
     */
enum fc_wctw {
	FC_WCTW_DD_UNCAT = 0x00,	/* uncategowized infowmation */
	FC_WCTW_DD_SOW_DATA = 0x01,	/* sowicited data */
	FC_WCTW_DD_UNSOW_CTW = 0x02,	/* unsowicited contwow */
	FC_WCTW_DD_SOW_CTW = 0x03,	/* sowicited contwow ow wepwy */
	FC_WCTW_DD_UNSOW_DATA = 0x04,	/* unsowicited data */
	FC_WCTW_DD_DATA_DESC = 0x05,	/* data descwiptow */
	FC_WCTW_DD_UNSOW_CMD = 0x06,	/* unsowicited command */
	FC_WCTW_DD_CMD_STATUS = 0x07,	/* command status */

#define FC_WCTW_IWS_WEQ FC_WCTW_DD_UNSOW_CTW	/* IWS wequest */
#define FC_WCTW_IWS_WEP FC_WCTW_DD_SOW_CTW	/* IWS wepwy */

	/*
	 * Extended Wink_Data
	 */
	FC_WCTW_EWS_WEQ = 0x22,	/* extended wink sewvices wequest */
	FC_WCTW_EWS_WEP = 0x23,	/* extended wink sewvices wepwy */
	FC_WCTW_EWS4_WEQ = 0x32, /* FC-4 EWS wequest */
	FC_WCTW_EWS4_WEP = 0x33, /* FC-4 EWS wepwy */
	/*
	 * Optionaw Extended Headews
	 */
	FC_WCTW_VFTH = 0x50,	/* viwtuaw fabwic tagging headew */
	FC_WCTW_IFWH = 0x51,	/* intew-fabwic wouting headew */
	FC_WCTW_ENCH = 0x52,	/* encapsuwation headew */
	/*
	 * Basic Wink Sewvices fh_w_ctw vawues.
	 */
	FC_WCTW_BA_NOP = 0x80,	/* basic wink sewvice NOP */
	FC_WCTW_BA_ABTS = 0x81,	/* basic wink sewvice abowt */
	FC_WCTW_BA_WMC = 0x82,	/* wemove connection */
	FC_WCTW_BA_ACC = 0x84,	/* basic accept */
	FC_WCTW_BA_WJT = 0x85,	/* basic weject */
	FC_WCTW_BA_PWMT = 0x86,	/* dedicated connection pweempted */
	/*
	 * Wink Contwow Infowmation.
	 */
	FC_WCTW_ACK_1 = 0xc0,	/* acknowwedge_1 */
	FC_WCTW_ACK_0 = 0xc1,	/* acknowwedge_0 */
	FC_WCTW_P_WJT = 0xc2,	/* powt weject */
	FC_WCTW_F_WJT = 0xc3,	/* fabwic weject */
	FC_WCTW_P_BSY = 0xc4,	/* powt busy */
	FC_WCTW_F_BSY = 0xc5,	/* fabwic busy to data fwame */
	FC_WCTW_F_BSYW = 0xc6,	/* fabwic busy to wink contwow fwame */
	FC_WCTW_WCW = 0xc7,	/* wink cwedit weset */
	FC_WCTW_END = 0xc9,	/* end */
};
				    /* incompwete wist of definitions */

/*
 * W_CTW names initiawizew.
 * Pwease keep this matching the above definitions.
 */
#define FC_WCTW_NAMES_INIT { \
	[FC_WCTW_DD_UNCAT] =		"uncat",			\
	[FC_WCTW_DD_SOW_DATA] =		"sow data",			\
	[FC_WCTW_DD_UNSOW_CTW] =	"unsow ctw",			\
	[FC_WCTW_DD_SOW_CTW] =		"sow ctw/wepwy",		\
	[FC_WCTW_DD_UNSOW_DATA] =	"unsow data",			\
	[FC_WCTW_DD_DATA_DESC] =	"data desc",			\
	[FC_WCTW_DD_UNSOW_CMD] =	"unsow cmd",			\
	[FC_WCTW_DD_CMD_STATUS] =	"cmd status",			\
	[FC_WCTW_EWS_WEQ] =		"EWS weq",			\
	[FC_WCTW_EWS_WEP] =		"EWS wep",			\
	[FC_WCTW_EWS4_WEQ] =		"FC-4 EWS weq",			\
	[FC_WCTW_EWS4_WEP] =		"FC-4 EWS wep",			\
	[FC_WCTW_BA_NOP] =		"BWS NOP",			\
	[FC_WCTW_BA_ABTS] =		"BWS abowt",			\
	[FC_WCTW_BA_WMC] =		"BWS wemove connection",	\
	[FC_WCTW_BA_ACC] =		"BWS accept",			\
	[FC_WCTW_BA_WJT] =		"BWS weject",			\
	[FC_WCTW_BA_PWMT] =		"BWS dedicated connection pweempted", \
	[FC_WCTW_ACK_1] =		"WC ACK_1",			\
	[FC_WCTW_ACK_0] =		"WC ACK_0",			\
	[FC_WCTW_P_WJT] =		"WC powt weject",		\
	[FC_WCTW_F_WJT] =		"WC fabwic weject",		\
	[FC_WCTW_P_BSY] =		"WC powt busy",			\
	[FC_WCTW_F_BSY] =		"WC fabwic busy to data fwame",	\
	[FC_WCTW_F_BSYW] =		"WC fabwic busy to wink contwow fwame",\
	[FC_WCTW_WCW] =			"WC wink cwedit weset",		\
	[FC_WCTW_END] =			"WC end",			\
}

/*
 * Weww-known fabwic addwesses.
 */
enum fc_weww_known_fid {
	FC_FID_NONE =           0x000000,       /* No destination */
	FC_FID_BCAST =		0xffffff,	/* bwoadcast */
	FC_FID_FWOGI =		0xfffffe,	/* fabwic wogin */
	FC_FID_FCTWW =		0xfffffd,	/* fabwic contwowwew */
	FC_FID_DIW_SEWV =	0xfffffc,	/* diwectowy sewvew */
	FC_FID_TIME_SEWV =	0xfffffb,	/* time sewvew */
	FC_FID_MGMT_SEWV =	0xfffffa,	/* management sewvew */
	FC_FID_QOS =		0xfffff9,	/* QoS Faciwitatow */
	FC_FID_AWIASES =	0xfffff8,	/* awias sewvew (FC-PH2) */
	FC_FID_SEC_KEY =	0xfffff7,	/* Secuwity key dist. sewvew */
	FC_FID_CWOCK =		0xfffff6,	/* cwock synch sewvew */
	FC_FID_MCAST_SEWV =	0xfffff5,	/* muwticast sewvew */
};

#define	FC_FID_WEWW_KNOWN_MAX	0xffffff /* highest weww-known fabwic ID */
#define	FC_FID_WEWW_KNOWN_BASE	0xfffff5 /* stawt of weww-known fabwic ID */

/*
 * Othew weww-known addwesses, outside the above contiguous wange.
 */
#define	FC_FID_DOM_MGW		0xfffc00	/* domain managew base */

/*
 * Fabwic ID bytes.
 */
#define	FC_FID_DOMAIN		0
#define	FC_FID_POWT		1
#define	FC_FID_WINK		2

/*
 * fh_type codes
 */
enum fc_fh_type {
	FC_TYPE_BWS =	0x00,	/* basic wink sewvice */
	FC_TYPE_EWS =	0x01,	/* extended wink sewvice */
	FC_TYPE_IP =	0x05,	/* IP ovew FC, WFC 4338 */
	FC_TYPE_FCP =	0x08,	/* SCSI FCP */
	FC_TYPE_CT =	0x20,	/* Fibwe Channew Sewvices (FC-CT) */
	FC_TYPE_IWS =	0x22,	/* intewnaw wink sewvice */
	FC_TYPE_NVME =	0x28,	/* FC-NVME */
};

/*
 * FC_TYPE names initiawizew.
 * Pwease keep this matching the above definitions.
 */
#define FC_TYPE_NAMES_INIT {				\
	[FC_TYPE_BWS] =		"BWS",			\
	[FC_TYPE_EWS] =		"EWS",			\
	[FC_TYPE_IP] =		"IP",			\
	[FC_TYPE_FCP] =		"FCP",			\
	[FC_TYPE_CT] =		"CT",			\
	[FC_TYPE_IWS] =		"IWS",			\
	[FC_TYPE_NVME] =	"NVME",			\
}

/*
 * Exchange IDs.
 */
#define FC_XID_UNKNOWN  0xffff	/* unknown exchange ID */
#define FC_XID_MIN	0x0	/* suppowted min exchange ID */
#define FC_XID_MAX	0xfffe	/* suppowted max exchange ID */

/*
 * fh_f_ctw - Fwame contwow fwags.
 */
#define	FC_FC_EX_CTX	(1 << 23)	/* sent by wespondew to exchange */
#define	FC_FC_SEQ_CTX	(1 << 22)	/* sent by wespondew to sequence */
#define	FC_FC_FIWST_SEQ (1 << 21)	/* fiwst sequence of this exchange */
#define	FC_FC_WAST_SEQ	(1 << 20)	/* wast sequence of this exchange */
#define	FC_FC_END_SEQ	(1 << 19)	/* wast fwame of sequence */
#define	FC_FC_END_CONN	(1 << 18)	/* end of cwass 1 connection pending */
#define	FC_FC_WES_B17	(1 << 17)	/* wesewved */
#define	FC_FC_SEQ_INIT	(1 << 16)	/* twansfew of sequence initiative */
#define	FC_FC_X_ID_WEASS (1 << 15)	/* exchange ID has been changed */
#define	FC_FC_X_ID_INVAW (1 << 14)	/* exchange ID invawidated */

#define	FC_FC_ACK_1	(1 << 12)	/* 13:12 = 1: ACK_1 expected */
#define	FC_FC_ACK_N	(2 << 12)	/* 13:12 = 2: ACK_N expected */
#define	FC_FC_ACK_0	(3 << 12)	/* 13:12 = 3: ACK_0 expected */

#define	FC_FC_WES_B11	(1 << 11)	/* wesewved */
#define	FC_FC_WES_B10	(1 << 10)	/* wesewved */
#define	FC_FC_WETX_SEQ	(1 << 9)	/* wetwansmitted sequence */
#define	FC_FC_UNI_TX	(1 << 8)	/* unidiwectionaw twansmit (cwass 1) */
#define	FC_FC_CONT_SEQ(i) ((i) << 6)
#define	FC_FC_ABT_SEQ(i) ((i) << 4)
#define	FC_FC_WEW_OFF	(1 << 3)	/* pawametew is wewative offset */
#define	FC_FC_WES2	(1 << 2)	/* wesewved */
#define	FC_FC_FIWW(i)	((i) & 3)	/* 1:0: bytes of twaiwing fiww */

/*
 * BA_ACC paywoad.
 */
stwuct fc_ba_acc {
	__u8		ba_seq_id_vaw;	/* SEQ_ID vawidity */
#define FC_BA_SEQ_ID_VAW 0x80
	__u8		ba_seq_id;	/* SEQ_ID of seq wast dewivewabwe */
	__u8		ba_wesvd[2];	/* wesewved */
	__be16		ba_ox_id;	/* OX_ID fow abowted seq ow exch */
	__be16		ba_wx_id;	/* WX_ID fow abowted seq ow exch */
	__be16		ba_wow_seq_cnt;	/* wow SEQ_CNT of abowted seq */
	__be16		ba_high_seq_cnt; /* high SEQ_CNT of abowted seq */
};

/*
 * BA_WJT: Basic Weject paywoad.
 */
stwuct fc_ba_wjt {
	__u8		bw_wesvd;	/* wesewved */
	__u8		bw_weason;	/* weason code */
	__u8		bw_expwan;	/* weason expwanation */
	__u8		bw_vendow;	/* vendow unique code */
};

/*
 * BA_WJT weason codes.
 * Fwom FS-2.
 */
enum fc_ba_wjt_weason {
	FC_BA_WJT_NONE =	0,	/* in softwawe this means no weject */
	FC_BA_WJT_INVW_CMD =	0x01,	/* invawid command code */
	FC_BA_WJT_WOG_EWW =	0x03,	/* wogicaw ewwow */
	FC_BA_WJT_WOG_BUSY =	0x05,	/* wogicaw busy */
	FC_BA_WJT_PWOTO_EWW =	0x07,	/* pwotocow ewwow */
	FC_BA_WJT_UNABWE =	0x09,	/* unabwe to pewfowm wequest */
	FC_BA_WJT_VENDOW =	0xff,	/* vendow-specific (see bw_vendow) */
};

/*
 * BA_WJT weason code expwanations.
 */
enum fc_ba_wjt_expwan {
	FC_BA_WJT_EXP_NONE =	0x00,	/* no additionaw expanation */
	FC_BA_WJT_INV_XID =	0x03,	/* invawid OX_ID-WX_ID combination */
	FC_BA_WJT_ABT =		0x05,	/* sequence abowted, no seq info */
};

/*
 * P_WJT ow F_WJT: Powt Weject ow Fabwic Weject pawametew fiewd.
 */
stwuct fc_pf_wjt {
	__u8		wj_action;	/* wesewved */
	__u8		wj_weason;	/* weason code */
	__u8		wj_wesvd;	/* wesewved */
	__u8		wj_vendow;	/* vendow unique code */
};

/*
 * P_WJT and F_WJT weject weason codes.
 */
enum fc_pf_wjt_weason {
	FC_WJT_NONE =		0,	/* non-weject (wesewved by standawd) */
	FC_WJT_INVW_DID =	0x01,	/* invawid destination ID */
	FC_WJT_INVW_SID =	0x02,	/* invawid souwce ID */
	FC_WJT_P_UNAV_T =	0x03,	/* powt unavaiwabwe, tempowawy */
	FC_WJT_P_UNAV =		0x04,	/* powt unavaiwabwe, pewmanent */
	FC_WJT_CWS_UNSUP =	0x05,	/* cwass not suppowted */
	FC_WJT_DEW_USAGE =	0x06,	/* dewimitew usage ewwow */
	FC_WJT_TYPE_UNSUP =	0x07,	/* type not suppowted */
	FC_WJT_WINK_CTW =	0x08,	/* invawid wink contwow */
	FC_WJT_W_CTW =		0x09,	/* invawid W_CTW fiewd */
	FC_WJT_F_CTW =		0x0a,	/* invawid F_CTW fiewd */
	FC_WJT_OX_ID =		0x0b,	/* invawid owiginatow exchange ID */
	FC_WJT_WX_ID =		0x0c,	/* invawid wespondew exchange ID */
	FC_WJT_SEQ_ID =		0x0d,	/* invawid sequence ID */
	FC_WJT_DF_CTW =		0x0e,	/* invawid DF_CTW fiewd */
	FC_WJT_SEQ_CNT =	0x0f,	/* invawid SEQ_CNT fiewd */
	FC_WJT_PAWAM =		0x10,	/* invawid pawametew fiewd */
	FC_WJT_EXCH_EWW =	0x11,	/* exchange ewwow */
	FC_WJT_PWOTO =		0x12,	/* pwotocow ewwow */
	FC_WJT_WEN =		0x13,	/* incowwect wength */
	FC_WJT_UNEXP_ACK =	0x14,	/* unexpected ACK */
	FC_WJT_FAB_CWASS =	0x15,	/* cwass unsuppowted by fabwic entity */
	FC_WJT_WOGI_WEQ =	0x16,	/* wogin wequiwed */
	FC_WJT_SEQ_XS =		0x17,	/* excessive sequences attempted */
	FC_WJT_EXCH_EST =	0x18,	/* unabwe to estabwish exchange */
	FC_WJT_FAB_UNAV =	0x1a,	/* fabwic unavaiwabwe */
	FC_WJT_VC_ID =		0x1b,	/* invawid VC_ID (cwass 4) */
	FC_WJT_CS_CTW =		0x1c,	/* invawid CS_CTW fiewd */
	FC_WJT_INSUF_WES =	0x1d,	/* insuff. wesouwces fow VC (Cwass 4) */
	FC_WJT_INVW_CWS =	0x1f,	/* invawid cwass of sewvice */
	FC_WJT_PWEEMT_WJT =	0x20,	/* pweemption wequest wejected */
	FC_WJT_PWEEMT_DIS =	0x21,	/* pweemption not enabwed */
	FC_WJT_MCAST_EWW =	0x22,	/* muwticast ewwow */
	FC_WJT_MCAST_ET =	0x23,	/* muwticast ewwow tewminate */
	FC_WJT_PWWI_WEQ =	0x24,	/* pwocess wogin wequiwed */
	FC_WJT_INVW_ATT =	0x25,	/* invawid attachment */
	FC_WJT_VENDOW =		0xff,	/* vendow specific weject */
};

/* defauwt timeout vawues */

#define FC_DEF_E_D_TOV	2000UW
#define FC_DEF_W_A_TOV	10000UW

#endif /* _FC_FS_H_ */
