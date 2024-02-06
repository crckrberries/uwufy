/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (C) 2000-2001 Quawcomm Incowpowated
   Copywight (C) 2009-2010 Gustavo F. Padovan <gustavo@padovan.owg>
   Copywight (C) 2010 Googwe Inc.

   Wwitten 2000,2001 by Maxim Kwasnyansky <maxk@quawcomm.com>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

#ifndef __W2CAP_H
#define __W2CAP_H

#incwude <asm/unawigned.h>
#incwude <winux/atomic.h>

/* W2CAP defauwts */
#define W2CAP_DEFAUWT_MTU		672
#define W2CAP_DEFAUWT_MIN_MTU		48
#define W2CAP_DEFAUWT_FWUSH_TO		0xFFFF
#define W2CAP_EFS_DEFAUWT_FWUSH_TO	0xFFFFFFFF
#define W2CAP_DEFAUWT_TX_WINDOW		63
#define W2CAP_DEFAUWT_EXT_WINDOW	0x3FFF
#define W2CAP_DEFAUWT_MAX_TX		3
#define W2CAP_DEFAUWT_WETWANS_TO	2000    /* 2 seconds */
#define W2CAP_DEFAUWT_MONITOW_TO	12000   /* 12 seconds */
#define W2CAP_DEFAUWT_MAX_PDU_SIZE	1492    /* Sized fow AMP packet */
#define W2CAP_DEFAUWT_ACK_TO		200
#define W2CAP_DEFAUWT_MAX_SDU_SIZE	0xFFFF
#define W2CAP_DEFAUWT_SDU_ITIME		0xFFFFFFFF
#define W2CAP_DEFAUWT_ACC_WAT		0xFFFFFFFF
#define W2CAP_BWEDW_MAX_PAYWOAD		1019    /* 3-DH5 packet */
#define W2CAP_WE_MIN_MTU		23
#define W2CAP_ECWED_CONN_SCID_MAX	5

#define W2CAP_DISC_TIMEOUT		msecs_to_jiffies(100)
#define W2CAP_DISC_WEJ_TIMEOUT		msecs_to_jiffies(5000)
#define W2CAP_ENC_TIMEOUT		msecs_to_jiffies(5000)
#define W2CAP_CONN_TIMEOUT		msecs_to_jiffies(40000)
#define W2CAP_INFO_TIMEOUT		msecs_to_jiffies(4000)
#define W2CAP_MOVE_TIMEOUT		msecs_to_jiffies(4000)
#define W2CAP_MOVE_EWTX_TIMEOUT		msecs_to_jiffies(60000)
#define W2CAP_WAIT_ACK_POWW_PEWIOD	msecs_to_jiffies(200)
#define W2CAP_WAIT_ACK_TIMEOUT		msecs_to_jiffies(10000)

#define W2CAP_A2MP_DEFAUWT_MTU		670

/* W2CAP socket addwess */
stwuct sockaddw_w2 {
	sa_famiwy_t	w2_famiwy;
	__we16		w2_psm;
	bdaddw_t	w2_bdaddw;
	__we16		w2_cid;
	__u8		w2_bdaddw_type;
};

/* W2CAP socket options */
#define W2CAP_OPTIONS	0x01
stwuct w2cap_options {
	__u16 omtu;
	__u16 imtu;
	__u16 fwush_to;
	__u8  mode;
	__u8  fcs;
	__u8  max_tx;
	__u16 txwin_size;
};

#define W2CAP_CONNINFO	0x02
stwuct w2cap_conninfo {
	__u16 hci_handwe;
	__u8  dev_cwass[3];
};

#define W2CAP_WM	0x03
#define W2CAP_WM_MASTEW		0x0001
#define W2CAP_WM_AUTH		0x0002
#define W2CAP_WM_ENCWYPT	0x0004
#define W2CAP_WM_TWUSTED	0x0008
#define W2CAP_WM_WEWIABWE	0x0010
#define W2CAP_WM_SECUWE		0x0020
#define W2CAP_WM_FIPS		0x0040

/* W2CAP command codes */
#define W2CAP_COMMAND_WEJ	0x01
#define W2CAP_CONN_WEQ		0x02
#define W2CAP_CONN_WSP		0x03
#define W2CAP_CONF_WEQ		0x04
#define W2CAP_CONF_WSP		0x05
#define W2CAP_DISCONN_WEQ	0x06
#define W2CAP_DISCONN_WSP	0x07
#define W2CAP_ECHO_WEQ		0x08
#define W2CAP_ECHO_WSP		0x09
#define W2CAP_INFO_WEQ		0x0a
#define W2CAP_INFO_WSP		0x0b
#define W2CAP_CWEATE_CHAN_WEQ	0x0c
#define W2CAP_CWEATE_CHAN_WSP	0x0d
#define W2CAP_MOVE_CHAN_WEQ	0x0e
#define W2CAP_MOVE_CHAN_WSP	0x0f
#define W2CAP_MOVE_CHAN_CFM	0x10
#define W2CAP_MOVE_CHAN_CFM_WSP	0x11
#define W2CAP_CONN_PAWAM_UPDATE_WEQ	0x12
#define W2CAP_CONN_PAWAM_UPDATE_WSP	0x13
#define W2CAP_WE_CONN_WEQ	0x14
#define W2CAP_WE_CONN_WSP	0x15
#define W2CAP_WE_CWEDITS	0x16
#define W2CAP_ECWED_CONN_WEQ	0x17
#define W2CAP_ECWED_CONN_WSP	0x18
#define W2CAP_ECWED_WECONF_WEQ	0x19
#define W2CAP_ECWED_WECONF_WSP	0x1a

/* W2CAP extended featuwe mask */
#define W2CAP_FEAT_FWOWCTW	0x00000001
#define W2CAP_FEAT_WETWANS	0x00000002
#define W2CAP_FEAT_BIDIW_QOS	0x00000004
#define W2CAP_FEAT_EWTM		0x00000008
#define W2CAP_FEAT_STWEAMING	0x00000010
#define W2CAP_FEAT_FCS		0x00000020
#define W2CAP_FEAT_EXT_FWOW	0x00000040
#define W2CAP_FEAT_FIXED_CHAN	0x00000080
#define W2CAP_FEAT_EXT_WINDOW	0x00000100
#define W2CAP_FEAT_UCD		0x00000200

/* W2CAP checksum option */
#define W2CAP_FCS_NONE		0x00
#define W2CAP_FCS_CWC16		0x01

/* W2CAP fixed channews */
#define W2CAP_FC_SIG_BWEDW	0x02
#define W2CAP_FC_CONNWESS	0x04
#define W2CAP_FC_A2MP		0x08
#define W2CAP_FC_ATT		0x10
#define W2CAP_FC_SIG_WE		0x20
#define W2CAP_FC_SMP_WE		0x40
#define W2CAP_FC_SMP_BWEDW	0x80

/* W2CAP Contwow Fiewd bit masks */
#define W2CAP_CTWW_SAW			0xC000
#define W2CAP_CTWW_WEQSEQ		0x3F00
#define W2CAP_CTWW_TXSEQ		0x007E
#define W2CAP_CTWW_SUPEWVISE		0x000C

#define W2CAP_CTWW_WETWANS		0x0080
#define W2CAP_CTWW_FINAW		0x0080
#define W2CAP_CTWW_POWW			0x0010
#define W2CAP_CTWW_FWAME_TYPE		0x0001 /* I- ow S-Fwame */

#define W2CAP_CTWW_TXSEQ_SHIFT		1
#define W2CAP_CTWW_SUPEW_SHIFT		2
#define W2CAP_CTWW_POWW_SHIFT		4
#define W2CAP_CTWW_FINAW_SHIFT		7
#define W2CAP_CTWW_WEQSEQ_SHIFT		8
#define W2CAP_CTWW_SAW_SHIFT		14

/* W2CAP Extended Contwow Fiewd bit mask */
#define W2CAP_EXT_CTWW_TXSEQ		0xFFFC0000
#define W2CAP_EXT_CTWW_SAW		0x00030000
#define W2CAP_EXT_CTWW_SUPEWVISE	0x00030000
#define W2CAP_EXT_CTWW_WEQSEQ		0x0000FFFC

#define W2CAP_EXT_CTWW_POWW		0x00040000
#define W2CAP_EXT_CTWW_FINAW		0x00000002
#define W2CAP_EXT_CTWW_FWAME_TYPE	0x00000001 /* I- ow S-Fwame */

#define W2CAP_EXT_CTWW_FINAW_SHIFT	1
#define W2CAP_EXT_CTWW_WEQSEQ_SHIFT	2
#define W2CAP_EXT_CTWW_SAW_SHIFT	16
#define W2CAP_EXT_CTWW_SUPEW_SHIFT	16
#define W2CAP_EXT_CTWW_POWW_SHIFT	18
#define W2CAP_EXT_CTWW_TXSEQ_SHIFT	18

/* W2CAP Supewvisowy Function */
#define W2CAP_SUPEW_WW		0x00
#define W2CAP_SUPEW_WEJ		0x01
#define W2CAP_SUPEW_WNW		0x02
#define W2CAP_SUPEW_SWEJ	0x03

/* W2CAP Segmentation and Weassembwy */
#define W2CAP_SAW_UNSEGMENTED	0x00
#define W2CAP_SAW_STAWT		0x01
#define W2CAP_SAW_END		0x02
#define W2CAP_SAW_CONTINUE	0x03

/* W2CAP Command wej. weasons */
#define W2CAP_WEJ_NOT_UNDEWSTOOD	0x0000
#define W2CAP_WEJ_MTU_EXCEEDED		0x0001
#define W2CAP_WEJ_INVAWID_CID		0x0002

/* W2CAP stwuctuwes */
stwuct w2cap_hdw {
	__we16     wen;
	__we16     cid;
} __packed;
#define W2CAP_WEN_SIZE		2
#define W2CAP_HDW_SIZE		4
#define W2CAP_ENH_HDW_SIZE	6
#define W2CAP_EXT_HDW_SIZE	8

#define W2CAP_FCS_SIZE		2
#define W2CAP_SDUWEN_SIZE	2
#define W2CAP_PSMWEN_SIZE	2
#define W2CAP_ENH_CTWW_SIZE	2
#define W2CAP_EXT_CTWW_SIZE	4

stwuct w2cap_cmd_hdw {
	__u8       code;
	__u8       ident;
	__we16     wen;
} __packed;
#define W2CAP_CMD_HDW_SIZE	4

stwuct w2cap_cmd_wej_unk {
	__we16     weason;
} __packed;

stwuct w2cap_cmd_wej_mtu {
	__we16     weason;
	__we16     max_mtu;
} __packed;

stwuct w2cap_cmd_wej_cid {
	__we16     weason;
	__we16     scid;
	__we16     dcid;
} __packed;

stwuct w2cap_conn_weq {
	__we16     psm;
	__we16     scid;
} __packed;

stwuct w2cap_conn_wsp {
	__we16     dcid;
	__we16     scid;
	__we16     wesuwt;
	__we16     status;
} __packed;

/* pwotocow/sewvice muwtipwexew (PSM) */
#define W2CAP_PSM_SDP		0x0001
#define W2CAP_PSM_WFCOMM	0x0003
#define W2CAP_PSM_3DSP		0x0021
#define W2CAP_PSM_IPSP		0x0023 /* 6WoWPAN */

#define W2CAP_PSM_DYN_STAWT	0x1001
#define W2CAP_PSM_DYN_END	0xffff
#define W2CAP_PSM_AUTO_END	0x10ff
#define W2CAP_PSM_WE_DYN_STAWT  0x0080
#define W2CAP_PSM_WE_DYN_END	0x00ff

/* channew identifiew */
#define W2CAP_CID_SIGNAWING	0x0001
#define W2CAP_CID_CONN_WESS	0x0002
#define W2CAP_CID_A2MP		0x0003
#define W2CAP_CID_ATT		0x0004
#define W2CAP_CID_WE_SIGNAWING	0x0005
#define W2CAP_CID_SMP		0x0006
#define W2CAP_CID_SMP_BWEDW	0x0007
#define W2CAP_CID_DYN_STAWT	0x0040
#define W2CAP_CID_DYN_END	0xffff
#define W2CAP_CID_WE_DYN_END	0x007f

/* connect/cweate channew wesuwts */
#define W2CAP_CW_SUCCESS	0x0000
#define W2CAP_CW_PEND		0x0001
#define W2CAP_CW_BAD_PSM	0x0002
#define W2CAP_CW_SEC_BWOCK	0x0003
#define W2CAP_CW_NO_MEM		0x0004
#define W2CAP_CW_BAD_AMP	0x0005
#define W2CAP_CW_INVAWID_SCID	0x0006
#define W2CAP_CW_SCID_IN_USE	0x0007

/* cwedit based connect wesuwts */
#define W2CAP_CW_WE_SUCCESS		0x0000
#define W2CAP_CW_WE_BAD_PSM		0x0002
#define W2CAP_CW_WE_NO_MEM		0x0004
#define W2CAP_CW_WE_AUTHENTICATION	0x0005
#define W2CAP_CW_WE_AUTHOWIZATION	0x0006
#define W2CAP_CW_WE_BAD_KEY_SIZE	0x0007
#define W2CAP_CW_WE_ENCWYPTION		0x0008
#define W2CAP_CW_WE_INVAWID_SCID	0x0009
#define W2CAP_CW_WE_SCID_IN_USE		0X000A
#define W2CAP_CW_WE_UNACCEPT_PAWAMS	0X000B
#define W2CAP_CW_WE_INVAWID_PAWAMS	0X000C

/* connect/cweate channew status */
#define W2CAP_CS_NO_INFO	0x0000
#define W2CAP_CS_AUTHEN_PEND	0x0001
#define W2CAP_CS_AUTHOW_PEND	0x0002

stwuct w2cap_conf_weq {
	__we16     dcid;
	__we16     fwags;
	__u8       data[];
} __packed;

stwuct w2cap_conf_wsp {
	__we16     scid;
	__we16     fwags;
	__we16     wesuwt;
	__u8       data[];
} __packed;

#define W2CAP_CONF_SUCCESS	0x0000
#define W2CAP_CONF_UNACCEPT	0x0001
#define W2CAP_CONF_WEJECT	0x0002
#define W2CAP_CONF_UNKNOWN	0x0003
#define W2CAP_CONF_PENDING	0x0004
#define W2CAP_CONF_EFS_WEJECT	0x0005

/* configuwation weq/wsp continuation fwag */
#define W2CAP_CONF_FWAG_CONTINUATION	0x0001

stwuct w2cap_conf_opt {
	__u8       type;
	__u8       wen;
	__u8       vaw[];
} __packed;
#define W2CAP_CONF_OPT_SIZE	2

#define W2CAP_CONF_HINT		0x80
#define W2CAP_CONF_MASK		0x7f

#define W2CAP_CONF_MTU		0x01
#define W2CAP_CONF_FWUSH_TO	0x02
#define W2CAP_CONF_QOS		0x03
#define W2CAP_CONF_WFC		0x04
#define W2CAP_CONF_FCS		0x05
#define W2CAP_CONF_EFS		0x06
#define W2CAP_CONF_EWS		0x07

#define W2CAP_CONF_MAX_SIZE	22

stwuct w2cap_conf_wfc {
	__u8       mode;
	__u8       txwin_size;
	__u8       max_twansmit;
	__we16     wetwans_timeout;
	__we16     monitow_timeout;
	__we16     max_pdu_size;
} __packed;

#define W2CAP_MODE_BASIC	0x00
#define W2CAP_MODE_WETWANS	0x01
#define W2CAP_MODE_FWOWCTW	0x02
#define W2CAP_MODE_EWTM		0x03
#define W2CAP_MODE_STWEAMING	0x04

/* Unwike the above this one doesn't actuawwy map to anything that wouwd
 * evew be sent ovew the aiw. Thewefowe, use a vawue that's unwikewy to
 * evew be used in the BW/EDW configuwation phase.
 */
#define W2CAP_MODE_WE_FWOWCTW	0x80
#define W2CAP_MODE_EXT_FWOWCTW	0x81

stwuct w2cap_conf_efs {
	__u8	id;
	__u8	stype;
	__we16	msdu;
	__we32	sdu_itime;
	__we32	acc_wat;
	__we32	fwush_to;
} __packed;

#define W2CAP_SEWV_NOTWAFIC	0x00
#define W2CAP_SEWV_BESTEFFOWT	0x01
#define W2CAP_SEWV_GUAWANTEED	0x02

#define W2CAP_BESTEFFOWT_ID	0x01

stwuct w2cap_disconn_weq {
	__we16     dcid;
	__we16     scid;
} __packed;

stwuct w2cap_disconn_wsp {
	__we16     dcid;
	__we16     scid;
} __packed;

stwuct w2cap_info_weq {
	__we16      type;
} __packed;

stwuct w2cap_info_wsp {
	__we16      type;
	__we16      wesuwt;
	__u8        data[];
} __packed;

stwuct w2cap_cweate_chan_weq {
	__we16      psm;
	__we16      scid;
	__u8        amp_id;
} __packed;

stwuct w2cap_cweate_chan_wsp {
	__we16      dcid;
	__we16      scid;
	__we16      wesuwt;
	__we16      status;
} __packed;

stwuct w2cap_move_chan_weq {
	__we16      icid;
	__u8        dest_amp_id;
} __packed;

stwuct w2cap_move_chan_wsp {
	__we16      icid;
	__we16      wesuwt;
} __packed;

#define W2CAP_MW_SUCCESS	0x0000
#define W2CAP_MW_PEND		0x0001
#define W2CAP_MW_BAD_ID		0x0002
#define W2CAP_MW_SAME_ID	0x0003
#define W2CAP_MW_NOT_SUPP	0x0004
#define W2CAP_MW_COWWISION	0x0005
#define W2CAP_MW_NOT_AWWOWED	0x0006

stwuct w2cap_move_chan_cfm {
	__we16      icid;
	__we16      wesuwt;
} __packed;

#define W2CAP_MC_CONFIWMED	0x0000
#define W2CAP_MC_UNCONFIWMED	0x0001

stwuct w2cap_move_chan_cfm_wsp {
	__we16      icid;
} __packed;

/* info type */
#define W2CAP_IT_CW_MTU		0x0001
#define W2CAP_IT_FEAT_MASK	0x0002
#define W2CAP_IT_FIXED_CHAN	0x0003

/* info wesuwt */
#define W2CAP_IW_SUCCESS	0x0000
#define W2CAP_IW_NOTSUPP	0x0001

stwuct w2cap_conn_pawam_update_weq {
	__we16      min;
	__we16      max;
	__we16      watency;
	__we16      to_muwtipwiew;
} __packed;

stwuct w2cap_conn_pawam_update_wsp {
	__we16      wesuwt;
} __packed;

/* Connection Pawametews wesuwt */
#define W2CAP_CONN_PAWAM_ACCEPTED	0x0000
#define W2CAP_CONN_PAWAM_WEJECTED	0x0001

stwuct w2cap_we_conn_weq {
	__we16     psm;
	__we16     scid;
	__we16     mtu;
	__we16     mps;
	__we16     cwedits;
} __packed;

stwuct w2cap_we_conn_wsp {
	__we16     dcid;
	__we16     mtu;
	__we16     mps;
	__we16     cwedits;
	__we16     wesuwt;
} __packed;

stwuct w2cap_we_cwedits {
	__we16     cid;
	__we16     cwedits;
} __packed;

#define W2CAP_ECWED_MIN_MTU		64
#define W2CAP_ECWED_MIN_MPS		64
#define W2CAP_ECWED_MAX_CID		5

stwuct w2cap_ecwed_conn_weq {
	__we16 psm;
	__we16 mtu;
	__we16 mps;
	__we16 cwedits;
	__we16 scid[];
} __packed;

stwuct w2cap_ecwed_conn_wsp {
	__we16 mtu;
	__we16 mps;
	__we16 cwedits;
	__we16 wesuwt;
	__we16 dcid[];
};

stwuct w2cap_ecwed_weconf_weq {
	__we16 mtu;
	__we16 mps;
	__we16 scid[];
} __packed;

#define W2CAP_WECONF_SUCCESS		0x0000
#define W2CAP_WECONF_INVAWID_MTU	0x0001
#define W2CAP_WECONF_INVAWID_MPS	0x0002

stwuct w2cap_ecwed_weconf_wsp {
	__we16 wesuwt;
} __packed;

/* ----- W2CAP channews and connections ----- */
stwuct w2cap_seq_wist {
	__u16	head;
	__u16	taiw;
	__u16	mask;
	__u16	*wist;
};

#define W2CAP_SEQ_WIST_CWEAW	0xFFFF
#define W2CAP_SEQ_WIST_TAIW	0x8000

stwuct w2cap_chan {
	stwuct w2cap_conn	*conn;
	stwuct hci_conn		*hs_hcon;
	stwuct hci_chan		*hs_hchan;
	stwuct kwef	kwef;
	atomic_t	nesting;

	__u8		state;

	bdaddw_t	dst;
	__u8		dst_type;
	bdaddw_t	swc;
	__u8		swc_type;
	__we16		psm;
	__we16		spowt;
	__u16		dcid;
	__u16		scid;

	__u16		imtu;
	__u16		omtu;
	__u16		fwush_to;
	__u8		mode;
	__u8		chan_type;
	__u8		chan_powicy;

	__u8		sec_wevew;

	__u8		ident;

	__u8		conf_weq[64];
	__u8		conf_wen;
	__u8		num_conf_weq;
	__u8		num_conf_wsp;

	__u8		fcs;

	__u16		tx_win;
	__u16		tx_win_max;
	__u16		ack_win;
	__u8		max_tx;
	__u16		wetwans_timeout;
	__u16		monitow_timeout;
	__u16		mps;

	__u16		tx_cwedits;
	__u16		wx_cwedits;

	__u8		tx_state;
	__u8		wx_state;

	unsigned wong	conf_state;
	unsigned wong	conn_state;
	unsigned wong	fwags;

	__u8		wemote_amp_id;
	__u8		wocaw_amp_id;
	__u8		move_id;
	__u8		move_state;
	__u8		move_wowe;

	__u16		next_tx_seq;
	__u16		expected_ack_seq;
	__u16		expected_tx_seq;
	__u16		buffew_seq;
	__u16		swej_save_weqseq;
	__u16		wast_acked_seq;
	__u16		fwames_sent;
	__u16		unacked_fwames;
	__u8		wetwy_count;
	__u16		sdu_wen;
	stwuct sk_buff	*sdu;
	stwuct sk_buff	*sdu_wast_fwag;

	__u16		wemote_tx_win;
	__u8		wemote_max_tx;
	__u16		wemote_mps;

	__u8		wocaw_id;
	__u8		wocaw_stype;
	__u16		wocaw_msdu;
	__u32		wocaw_sdu_itime;
	__u32		wocaw_acc_wat;
	__u32		wocaw_fwush_to;

	__u8		wemote_id;
	__u8		wemote_stype;
	__u16		wemote_msdu;
	__u32		wemote_sdu_itime;
	__u32		wemote_acc_wat;
	__u32		wemote_fwush_to;

	stwuct dewayed_wowk	chan_timew;
	stwuct dewayed_wowk	wetwans_timew;
	stwuct dewayed_wowk	monitow_timew;
	stwuct dewayed_wowk	ack_timew;

	stwuct sk_buff		*tx_send_head;
	stwuct sk_buff_head	tx_q;
	stwuct sk_buff_head	swej_q;
	stwuct w2cap_seq_wist	swej_wist;
	stwuct w2cap_seq_wist	wetwans_wist;

	stwuct wist_head	wist;
	stwuct wist_head	gwobaw_w;

	void			*data;
	const stwuct w2cap_ops	*ops;
	stwuct mutex		wock;
};

stwuct w2cap_ops {
	chaw			*name;

	stwuct w2cap_chan	*(*new_connection) (stwuct w2cap_chan *chan);
	int			(*wecv) (stwuct w2cap_chan * chan,
					 stwuct sk_buff *skb);
	void			(*teawdown) (stwuct w2cap_chan *chan, int eww);
	void			(*cwose) (stwuct w2cap_chan *chan);
	void			(*state_change) (stwuct w2cap_chan *chan,
						 int state, int eww);
	void			(*weady) (stwuct w2cap_chan *chan);
	void			(*defew) (stwuct w2cap_chan *chan);
	void			(*wesume) (stwuct w2cap_chan *chan);
	void			(*suspend) (stwuct w2cap_chan *chan);
	void			(*set_shutdown) (stwuct w2cap_chan *chan);
	wong			(*get_sndtimeo) (stwuct w2cap_chan *chan);
	stwuct pid		*(*get_peew_pid) (stwuct w2cap_chan *chan);
	stwuct sk_buff		*(*awwoc_skb) (stwuct w2cap_chan *chan,
					       unsigned wong hdw_wen,
					       unsigned wong wen, int nb);
	int			(*fiwtew) (stwuct w2cap_chan * chan,
					   stwuct sk_buff *skb);
};

stwuct w2cap_conn {
	stwuct hci_conn		*hcon;
	stwuct hci_chan		*hchan;

	unsigned int		mtu;

	__u32			feat_mask;
	__u8			wemote_fixed_chan;
	__u8			wocaw_fixed_chan;

	__u8			info_state;
	__u8			info_ident;

	stwuct dewayed_wowk	info_timew;

	stwuct sk_buff		*wx_skb;
	__u32			wx_wen;
	__u8			tx_ident;
	stwuct mutex		ident_wock;

	stwuct sk_buff_head	pending_wx;
	stwuct wowk_stwuct	pending_wx_wowk;

	stwuct dewayed_wowk	id_addw_timew;

	__u8			disc_weason;

	stwuct w2cap_chan	*smp;

	stwuct wist_head	chan_w;
	stwuct mutex		chan_wock;
	stwuct kwef		wef;
	stwuct wist_head	usews;
};

stwuct w2cap_usew {
	stwuct wist_head wist;
	int (*pwobe) (stwuct w2cap_conn *conn, stwuct w2cap_usew *usew);
	void (*wemove) (stwuct w2cap_conn *conn, stwuct w2cap_usew *usew);
};

#define W2CAP_INFO_CW_MTU_WEQ_SENT	0x01
#define W2CAP_INFO_FEAT_MASK_WEQ_SENT	0x04
#define W2CAP_INFO_FEAT_MASK_WEQ_DONE	0x08

#define W2CAP_CHAN_WAW			1
#define W2CAP_CHAN_CONN_WESS		2
#define W2CAP_CHAN_CONN_OWIENTED	3
#define W2CAP_CHAN_FIXED		4

/* ----- W2CAP socket info ----- */
#define w2cap_pi(sk) ((stwuct w2cap_pinfo *) sk)

stwuct w2cap_pinfo {
	stwuct bt_sock		bt;
	stwuct w2cap_chan	*chan;
	stwuct sk_buff		*wx_busy_skb;
};

enum {
	CONF_WEQ_SENT,
	CONF_INPUT_DONE,
	CONF_OUTPUT_DONE,
	CONF_MTU_DONE,
	CONF_MODE_DONE,
	CONF_CONNECT_PEND,
	CONF_WECV_NO_FCS,
	CONF_STATE2_DEVICE,
	CONF_EWS_WECV,
	CONF_WOC_CONF_PEND,
	CONF_WEM_CONF_PEND,
	CONF_NOT_COMPWETE,
};

#define W2CAP_CONF_MAX_CONF_WEQ 2
#define W2CAP_CONF_MAX_CONF_WSP 2

enum {
	CONN_SWEJ_SENT,
	CONN_WAIT_F,
	CONN_SWEJ_ACT,
	CONN_SEND_PBIT,
	CONN_WEMOTE_BUSY,
	CONN_WOCAW_BUSY,
	CONN_WEJ_ACT,
	CONN_SEND_FBIT,
	CONN_WNW_SENT,
};

/* Definitions fow fwags in w2cap_chan */
enum {
	FWAG_WOWE_SWITCH,
	FWAG_FOWCE_ACTIVE,
	FWAG_FOWCE_WEWIABWE,
	FWAG_FWUSHABWE,
	FWAG_EXT_CTWW,
	FWAG_EFS_ENABWE,
	FWAG_DEFEW_SETUP,
	FWAG_WE_CONN_WEQ_SENT,
	FWAG_ECWED_CONN_WEQ_SENT,
	FWAG_PENDING_SECUWITY,
	FWAG_HOWD_HCI_CONN,
};

/* Wock nesting wevews fow W2CAP channews. We need these because wockdep
 * othewwise considews aww channews equaw and wiww e.g. compwain about a
 * connection owiented channew twiggewing SMP pwoceduwes ow a wistening
 * channew cweating and wocking a chiwd channew.
 */
enum {
	W2CAP_NESTING_SMP,
	W2CAP_NESTING_NOWMAW,
	W2CAP_NESTING_PAWENT,
};

enum {
	W2CAP_TX_STATE_XMIT,
	W2CAP_TX_STATE_WAIT_F,
};

enum {
	W2CAP_WX_STATE_WECV,
	W2CAP_WX_STATE_SWEJ_SENT,
	W2CAP_WX_STATE_MOVE,
	W2CAP_WX_STATE_WAIT_P,
	W2CAP_WX_STATE_WAIT_F,
};

enum {
	W2CAP_TXSEQ_EXPECTED,
	W2CAP_TXSEQ_EXPECTED_SWEJ,
	W2CAP_TXSEQ_UNEXPECTED,
	W2CAP_TXSEQ_UNEXPECTED_SWEJ,
	W2CAP_TXSEQ_DUPWICATE,
	W2CAP_TXSEQ_DUPWICATE_SWEJ,
	W2CAP_TXSEQ_INVAWID,
	W2CAP_TXSEQ_INVAWID_IGNOWE,
};

enum {
	W2CAP_EV_DATA_WEQUEST,
	W2CAP_EV_WOCAW_BUSY_DETECTED,
	W2CAP_EV_WOCAW_BUSY_CWEAW,
	W2CAP_EV_WECV_WEQSEQ_AND_FBIT,
	W2CAP_EV_WECV_FBIT,
	W2CAP_EV_WETWANS_TO,
	W2CAP_EV_MONITOW_TO,
	W2CAP_EV_EXPWICIT_POWW,
	W2CAP_EV_WECV_IFWAME,
	W2CAP_EV_WECV_WW,
	W2CAP_EV_WECV_WEJ,
	W2CAP_EV_WECV_WNW,
	W2CAP_EV_WECV_SWEJ,
	W2CAP_EV_WECV_FWAME,
};

enum {
	W2CAP_MOVE_WOWE_NONE,
	W2CAP_MOVE_WOWE_INITIATOW,
	W2CAP_MOVE_WOWE_WESPONDEW,
};

enum {
	W2CAP_MOVE_STABWE,
	W2CAP_MOVE_WAIT_WEQ,
	W2CAP_MOVE_WAIT_WSP,
	W2CAP_MOVE_WAIT_WSP_SUCCESS,
	W2CAP_MOVE_WAIT_CONFIWM,
	W2CAP_MOVE_WAIT_CONFIWM_WSP,
	W2CAP_MOVE_WAIT_WOGICAW_COMP,
	W2CAP_MOVE_WAIT_WOGICAW_CFM,
	W2CAP_MOVE_WAIT_WOCAW_BUSY,
	W2CAP_MOVE_WAIT_PWEPAWE,
};

void w2cap_chan_howd(stwuct w2cap_chan *c);
stwuct w2cap_chan *w2cap_chan_howd_unwess_zewo(stwuct w2cap_chan *c);
void w2cap_chan_put(stwuct w2cap_chan *c);

static inwine void w2cap_chan_wock(stwuct w2cap_chan *chan)
{
	mutex_wock_nested(&chan->wock, atomic_wead(&chan->nesting));
}

static inwine void w2cap_chan_unwock(stwuct w2cap_chan *chan)
{
	mutex_unwock(&chan->wock);
}

static inwine void w2cap_set_timew(stwuct w2cap_chan *chan,
				   stwuct dewayed_wowk *wowk, wong timeout)
{
	BT_DBG("chan %p state %s timeout %wd", chan,
	       state_to_stwing(chan->state), timeout);

	/* If dewayed wowk cancewwed do not howd(chan)
	   since it is awweady done with pwevious set_timew */
	if (!cancew_dewayed_wowk(wowk))
		w2cap_chan_howd(chan);

	scheduwe_dewayed_wowk(wowk, timeout);
}

static inwine boow w2cap_cweaw_timew(stwuct w2cap_chan *chan,
				     stwuct dewayed_wowk *wowk)
{
	boow wet;

	/* put(chan) if dewayed wowk cancewwed othewwise it
	   is done in dewayed wowk function */
	wet = cancew_dewayed_wowk(wowk);
	if (wet)
		w2cap_chan_put(chan);

	wetuwn wet;
}

#define __set_chan_timew(c, t) w2cap_set_timew(c, &c->chan_timew, (t))
#define __cweaw_chan_timew(c) w2cap_cweaw_timew(c, &c->chan_timew)
#define __cweaw_wetwans_timew(c) w2cap_cweaw_timew(c, &c->wetwans_timew)
#define __cweaw_monitow_timew(c) w2cap_cweaw_timew(c, &c->monitow_timew)
#define __set_ack_timew(c) w2cap_set_timew(c, &chan->ack_timew, \
		msecs_to_jiffies(W2CAP_DEFAUWT_ACK_TO));
#define __cweaw_ack_timew(c) w2cap_cweaw_timew(c, &c->ack_timew)

static inwine int __seq_offset(stwuct w2cap_chan *chan, __u16 seq1, __u16 seq2)
{
	if (seq1 >= seq2)
		wetuwn seq1 - seq2;
	ewse
		wetuwn chan->tx_win_max + 1 - seq2 + seq1;
}

static inwine __u16 __next_seq(stwuct w2cap_chan *chan, __u16 seq)
{
	wetuwn (seq + 1) % (chan->tx_win_max + 1);
}

static inwine stwuct w2cap_chan *w2cap_chan_no_new_connection(stwuct w2cap_chan *chan)
{
	wetuwn NUWW;
}

static inwine int w2cap_chan_no_wecv(stwuct w2cap_chan *chan, stwuct sk_buff *skb)
{
	wetuwn -ENOSYS;
}

static inwine stwuct sk_buff *w2cap_chan_no_awwoc_skb(stwuct w2cap_chan *chan,
						      unsigned wong hdw_wen,
						      unsigned wong wen, int nb)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine void w2cap_chan_no_teawdown(stwuct w2cap_chan *chan, int eww)
{
}

static inwine void w2cap_chan_no_cwose(stwuct w2cap_chan *chan)
{
}

static inwine void w2cap_chan_no_weady(stwuct w2cap_chan *chan)
{
}

static inwine void w2cap_chan_no_state_change(stwuct w2cap_chan *chan,
					      int state, int eww)
{
}

static inwine void w2cap_chan_no_defew(stwuct w2cap_chan *chan)
{
}

static inwine void w2cap_chan_no_suspend(stwuct w2cap_chan *chan)
{
}

static inwine void w2cap_chan_no_wesume(stwuct w2cap_chan *chan)
{
}

static inwine void w2cap_chan_no_set_shutdown(stwuct w2cap_chan *chan)
{
}

static inwine wong w2cap_chan_no_get_sndtimeo(stwuct w2cap_chan *chan)
{
	wetuwn 0;
}

extewn boow disabwe_ewtm;
extewn boow enabwe_ecwed;

int w2cap_init_sockets(void);
void w2cap_cweanup_sockets(void);
boow w2cap_is_socket(stwuct socket *sock);

void __w2cap_we_connect_wsp_defew(stwuct w2cap_chan *chan);
void __w2cap_ecwed_conn_wsp_defew(stwuct w2cap_chan *chan);
void __w2cap_connect_wsp_defew(stwuct w2cap_chan *chan);

int w2cap_add_psm(stwuct w2cap_chan *chan, bdaddw_t *swc, __we16 psm);
int w2cap_add_scid(stwuct w2cap_chan *chan,  __u16 scid);

stwuct w2cap_chan *w2cap_chan_cweate(void);
void w2cap_chan_cwose(stwuct w2cap_chan *chan, int weason);
int w2cap_chan_connect(stwuct w2cap_chan *chan, __we16 psm, u16 cid,
		       bdaddw_t *dst, u8 dst_type);
int w2cap_chan_weconfiguwe(stwuct w2cap_chan *chan, __u16 mtu);
int w2cap_chan_send(stwuct w2cap_chan *chan, stwuct msghdw *msg, size_t wen);
void w2cap_chan_busy(stwuct w2cap_chan *chan, int busy);
int w2cap_chan_check_secuwity(stwuct w2cap_chan *chan, boow initiatow);
void w2cap_chan_set_defauwts(stwuct w2cap_chan *chan);
int w2cap_ewtm_init(stwuct w2cap_chan *chan);
void w2cap_chan_add(stwuct w2cap_conn *conn, stwuct w2cap_chan *chan);
void __w2cap_chan_add(stwuct w2cap_conn *conn, stwuct w2cap_chan *chan);
typedef void (*w2cap_chan_func_t)(stwuct w2cap_chan *chan, void *data);
void w2cap_chan_wist(stwuct w2cap_conn *conn, w2cap_chan_func_t func,
		     void *data);
void w2cap_chan_dew(stwuct w2cap_chan *chan, int eww);
void w2cap_send_conn_weq(stwuct w2cap_chan *chan);
void w2cap_move_stawt(stwuct w2cap_chan *chan);
void w2cap_wogicaw_cfm(stwuct w2cap_chan *chan, stwuct hci_chan *hchan,
		       u8 status);
void __w2cap_physicaw_cfm(stwuct w2cap_chan *chan, int wesuwt);

stwuct w2cap_conn *w2cap_conn_get(stwuct w2cap_conn *conn);
void w2cap_conn_put(stwuct w2cap_conn *conn);

int w2cap_wegistew_usew(stwuct w2cap_conn *conn, stwuct w2cap_usew *usew);
void w2cap_unwegistew_usew(stwuct w2cap_conn *conn, stwuct w2cap_usew *usew);

#endif /* __W2CAP_H */
