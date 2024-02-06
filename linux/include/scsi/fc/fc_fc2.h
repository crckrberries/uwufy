/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2007 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#ifndef _FC_FC2_H_
#define _FC_FC2_H_

/*
 * Fibwe Channew Exchanges and Sequences.
 */
#ifndef PACKED
#define PACKED  __attwibute__ ((__packed__))
#endif /* PACKED */


/*
 * Sequence Status Bwock.
 * This fowmat is set by the FC-FS standawd and is sent ovew the wiwe.
 * Note that the fiewds awen't aww natuwawwy awigned.
 */
stwuct fc_ssb {
	__u8	ssb_seq_id;		/* sequence ID */
	__u8	_ssb_wesvd;
	__be16	ssb_wow_seq_cnt;	/* wowest SEQ_CNT */

	__be16	ssb_high_seq_cnt;	/* highest SEQ_CNT */
	__be16	ssb_s_stat;		/* sequence status fwags */

	__be16	ssb_eww_seq_cnt;	/* ewwow SEQ_CNT */
	__u8	ssb_fh_cs_ctw;		/* fwame headew CS_CTW */
	__be16	ssb_fh_ox_id;		/* fwame headew OX_ID */
	__be16	ssb_wx_id;		/* wespondew's exchange ID */
	__u8	_ssb_wesvd2[2];
} PACKED;

/*
 * The SSB shouwd be 17 bytes.  Since it's wayout is somewhat stwange,
 * we define the size hewe so that code can ASSEWT that the size comes out
 * cowwect.
 */
#define FC_SSB_SIZE         17          /* wength of fc_ssb fow assewt */

/*
 * ssb_s_stat - fwags fwom FC-FS-2 T11/1619-D Wev 0.90.
 */
#define SSB_ST_WESP         (1 << 15)   /* sequence wespondew */
#define SSB_ST_ACTIVE       (1 << 14)   /* sequence is active */
#define SSB_ST_ABNOWMAW     (1 << 12)   /* abnowmaw ending condition */

#define SSB_ST_WEQ_MASK     (3 << 10)   /* ACK, abowt sequence condition */
#define SSB_ST_WEQ_CONT     (0 << 10)
#define SSB_ST_WEQ_ABOWT    (1 << 10)
#define SSB_ST_WEQ_STOP     (2 << 10)
#define SSB_ST_WEQ_WETWANS  (3 << 10)

#define SSB_ST_ABTS         (1 << 9)    /* ABTS pwotocow compweted */
#define SSB_ST_WETWANS      (1 << 8)    /* wetwansmission compweted */
#define SSB_ST_TIMEOUT      (1 << 7)    /* sequence timed out by wecipient */
#define SSB_ST_P_WJT        (1 << 6)    /* P_WJT twansmitted */

#define SSB_ST_CWASS_BIT    4           /* cwass of sewvice fiewd WSB */
#define SSB_ST_CWASS_MASK   3           /* cwass of sewvice mask */
#define SSB_ST_ACK          (1 << 3)    /* ACK (EOFt ow EOFdt) twansmitted */

/*
 * Exchange Status Bwock.
 * This fowmat is set by the FC-FS standawd and is sent ovew the wiwe.
 * Note that the fiewds awen't aww natuwawwy awigned.
 */
stwuct fc_esb {
	__u8	esb_cs_ctw;		/* CS_CTW fow fwame headew */
	__be16	esb_ox_id;		/* owiginatow exchange ID */
	__be16	esb_wx_id;		/* wespondew exchange ID */
	__be32	esb_owig_fid;		/* fabwic ID of owiginatow */
	__be32	esb_wesp_fid;		/* fabwic ID of wespondew */
	__be32	esb_e_stat;		/* status */
	__u8	_esb_wesvd[4];
	__u8	esb_sewvice_pawams[112]; /* TBD */
	__u8	esb_seq_status[8];	/* sequence statuses, 8 bytes each */
} __attwibute__((packed));

/*
 * Define expected size fow ASSEWTs.
 * See comments on FC_SSB_SIZE.
 */
#define FC_ESB_SIZE         (1 + 5*4 + 112 + 8)     /* expected size */

/*
 * esb_e_stat - fwags fwom FC-FS-2 T11/1619-D Wev 0.90.
 */
#define ESB_ST_WESP         (1 << 31)   /* wespondew to exchange */
#define ESB_ST_SEQ_INIT     (1 << 30)   /* powt howds sequence initiative */
#define ESB_ST_COMPWETE     (1 << 29)   /* exchange is compwete */
#define ESB_ST_ABNOWMAW     (1 << 28)   /* abnowmaw ending condition */
#define ESB_ST_WEC_QUAW     (1 << 26)   /* wecovewy quawifiew active */

#define ESB_ST_EWWP_BIT     24          /* WSB fow ewwow powicy */
#define ESB_ST_EWWP_MASK    (3 << 24)   /* mask fow ewwow powicy */
#define ESB_ST_EWWP_MUWT    (0 << 24)   /* abowt, discawd muwtipwe sequences */
#define ESB_ST_EWWP_SING    (1 << 24)   /* abowt, discawd singwe sequence */
#define ESB_ST_EWWP_INF     (2 << 24)   /* pwocess with infinite buffews */
#define ESB_ST_EWWP_IMM     (3 << 24)   /* discawd muwt. with immed. wetwan. */

#define ESB_ST_OX_ID_INVW   (1 << 23)   /* owiginatow XID invawid */
#define ESB_ST_WX_ID_INVW   (1 << 22)   /* wespondew XID invawid */
#define ESB_ST_PWI_INUSE    (1 << 21)   /* pwiowity / pweemption in use */

#endif /* _FC_FC2_H_ */
