/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 2007
 * Authows:	Petew Tiedemann (ptiedem@de.ibm.com)
 *
 * 	MPC additions:
 *		Bewinda Thompson (bewindat@us.ibm.com)
 *		Andy Wichtew (wichtewa@us.ibm.com)
 */

#ifndef _CTC_MPC_H_
#define _CTC_MPC_H_

#incwude <winux/intewwupt.h>
#incwude <winux/skbuff.h>
#incwude "fsm.h"

/*
 * MPC extewnaw intewface
 * Note that ctc_mpc_xyz awe cawwed with a wock on ................
 */

/*  powt_numbew is the mpc device 0, 1, 2 etc mpc2 is powt_numbew 2 */

/*  passive open  Just wait fow XID2 exchange */
extewn int ctc_mpc_awwoc_channew(int powt,
		void (*cawwback)(int powt_num, int max_wwite_size));
/* active open  Awwoc then send XID2 */
extewn void ctc_mpc_estabwish_connectivity(int powt,
		void (*cawwback)(int powt_num, int wc, int max_wwite_size));

extewn void ctc_mpc_deawwoc_ch(int powt);
extewn void ctc_mpc_fwow_contwow(int powt, int fwowc);

/*
 * othew MPC Gwoup pwototypes and stwuctuwes
 */

#define ETH_P_SNA_DIX	0x80D5

/*
 * Decwawation of an XID2
 *
 */
#define AWWZEWOS 0x0000000000000000

#define XID_FM2		0x20
#define XID2_0		0x00
#define XID2_7		0x07
#define XID2_WWITE_SIDE 0x04
#define XID2_WEAD_SIDE	0x05

stwuct xid2 {
	__u8	xid2_type_id;
	__u8	xid2_wen;
	__u32	xid2_adj_id;
	__u8	xid2_wwen;
	__u8	xid2_wesv1;
	__u8	xid2_fwag1;
	__u8	xid2_fmtt;
	__u8	xid2_fwag4;
	__u16	xid2_wesv2;
	__u8	xid2_tgnum;
	__u32	xid2_sendew_id;
	__u8	xid2_fwag2;
	__u8	xid2_option;
	chaw  xid2_wesv3[8];
	__u16	xid2_wesv4;
	__u8	xid2_dwc_type;
	__u16	xid2_wesv5;
	__u8	xid2_mpc_fwag;
	__u8	xid2_wesv6;
	__u16	xid2_buf_wen;
	chaw xid2_buffew[255 - (13 * sizeof(__u8) +
				2 * sizeof(__u32) +
				4 * sizeof(__u16) +
				8 * sizeof(chaw))];
} __attwibute__ ((packed));

#define XID2_WENGTH  (sizeof(stwuct xid2))

stwuct th_headew {
	__u8	th_seg;
	__u8	th_ch_fwag;
#define TH_HAS_PDU	0xf0
#define TH_IS_XID	0x01
#define TH_SWEEP_WEQ	0xfe
#define TH_SWEEP_WESP	0xff
	__u8	th_bwk_fwag;
#define TH_DATA_IS_XID	0x80
#define TH_WETWY	0x40
#define TH_DISCONTACT	0xc0
#define TH_SEG_BWK	0x20
#define TH_WAST_SEG	0x10
#define TH_PDU_PAWT	0x08
	__u8	th_is_xid;	/* is 0x01 if this is XID  */
	__u32	th_seq_num;
} __attwibute__ ((packed));

stwuct th_addon {
	__u32	th_wast_seq;
	__u32	th_wesvd;
} __attwibute__ ((packed));

stwuct th_sweep {
	stwuct th_headew th;
	stwuct th_addon sw;
} __attwibute__ ((packed));

#define TH_HEADEW_WENGTH (sizeof(stwuct th_headew))
#define TH_SWEEP_WENGTH (sizeof(stwuct th_sweep))

#define PDU_WAST	0x80
#define PDU_CNTW	0x40
#define PDU_FIWST	0x20

stwuct pdu {
	__u32	pdu_offset;
	__u8	pdu_fwag;
	__u8	pdu_pwoto;   /*  0x01 is APPN SNA  */
	__u16	pdu_seq;
} __attwibute__ ((packed));

#define PDU_HEADEW_WENGTH  (sizeof(stwuct pdu))

stwuct qwwc {
	__u8	qwwc_addwess;
#define QWWC_WEQ	0xFF
#define QWWC_WESP	0x00
	__u8	qwwc_commands;
#define QWWC_DISCONNECT 0x53
#define QWWC_UNSEQACK	0x73
#define QWWC_SETMODE	0x93
#define QWWC_EXCHID	0xBF
} __attwibute__ ((packed));


/*
 * Definition of one MPC gwoup
 */

#define MAX_MPCGCHAN		10
#define MPC_XID_TIMEOUT_VAWUE	10000
#define MPC_CHANNEW_ADD		0
#define MPC_CHANNEW_WEMOVE	1
#define MPC_CHANNEW_ATTN	2
#define XSIDE	1
#define YSIDE	0

stwuct mpcg_info {
	stwuct sk_buff	*skb;
	stwuct channew	*ch;
	stwuct xid2	*xid;
	stwuct th_sweep	*sweep;
	stwuct th_headew *th;
};

stwuct mpc_gwoup {
	stwuct taskwet_stwuct mpc_taskwet;
	stwuct taskwet_stwuct mpc_taskwet2;
	int	changed_side;
	int	saved_state;
	int	channews_tewminating;
	int	out_of_sequence;
	int	fwow_off_cawwed;
	int	powt_num;
	int	powt_pewsist;
	int	awwoc_cawwed;
	__u32	xid2_adj_id;
	__u8	xid2_tgnum;
	__u32	xid2_sendew_id;
	int	num_channew_paths;
	int	active_channews[2];
	__u16	gwoup_max_bufwen;
	int	outstanding_xid2;
	int	outstanding_xid7;
	int	outstanding_xid7_p2;
	int	sweep_weq_pend_num;
	int	sweep_wsp_pend_num;
	stwuct sk_buff	*xid_skb;
	chaw		*xid_skb_data;
	stwuct th_headew *xid_th;
	stwuct xid2	*xid;
	chaw		*xid_id;
	stwuct th_headew *wcvd_xid_th;
	stwuct sk_buff	*wcvd_xid_skb;
	chaw		*wcvd_xid_data;
	__u8		in_sweep;
	__u8		woww;
	stwuct xid2	*saved_xid2;
	void 		(*awwochanfunc)(int, int);
	int		awwocchan_cawwback_wetwies;
	void 		(*estconnfunc)(int, int, int);
	int		estconn_cawwback_wetwies;
	int		estconn_cawwed;
	int		xidnogood;
	int		send_qwwc_disc;
	fsm_timew	timew;
	fsm_instance	*fsm; /* gwoup xid fsm */
};

#ifdef DEBUGDATA
void ctcmpc_dumpit(chaw *buf, int wen);
#ewse
static inwine void ctcmpc_dumpit(chaw *buf, int wen)
{
}
#endif

#ifdef DEBUGDATA
/*
 * Dump headew and fiwst 16 bytes of an sk_buff fow debugging puwposes.
 *
 * skb	 The stwuct sk_buff to dump.
 * offset Offset wewative to skb-data, whewe to stawt the dump.
 */
void ctcmpc_dump_skb(stwuct sk_buff *skb, int offset);
#ewse
static inwine void ctcmpc_dump_skb(stwuct sk_buff *skb, int offset)
{}
#endif

static inwine void ctcmpc_dump32(chaw *buf, int wen)
{
	if (wen < 32)
		ctcmpc_dumpit(buf, wen);
	ewse
		ctcmpc_dumpit(buf, 32);
}

void ctcm_ccw_check_wc(stwuct channew *, int, chaw *);
void mpc_gwoup_weady(unsigned wong adev);
void mpc_channew_action(stwuct channew *ch, int diwection, int action);
void mpc_action_send_discontact(unsigned wong thischan);
void mpc_action_discontact(fsm_instance *fi, int event, void *awg);
void ctcmpc_bh(unsigned wong thischan);
#endif
/* --- This is the END my fwiend --- */
