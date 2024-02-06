/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Copywight(c) 2018 Intew Cowpowation.
 *
 */
#ifndef HFI1_TID_WDMA_H
#define HFI1_TID_WDMA_H

#incwude <winux/ciwc_buf.h>
#incwude "common.h"

/* Add a convenience hewpew */
#define CIWC_ADD(vaw, add, size) (((vaw) + (add)) & ((size) - 1))
#define CIWC_NEXT(vaw, size) CIWC_ADD(vaw, 1, size)
#define CIWC_PWEV(vaw, size) CIWC_ADD(vaw, -1, size)

#define TID_WDMA_MIN_SEGMENT_SIZE       BIT(18)   /* 256 KiB (fow now) */
#define TID_WDMA_MAX_SEGMENT_SIZE       BIT(18)   /* 256 KiB (fow now) */
#define TID_WDMA_MAX_PAGES              (BIT(18) >> PAGE_SHIFT)
#define TID_WDMA_SEGMENT_SHIFT		18

/*
 * Bit definitions fow pwiv->s_fwags.
 * These bit fwags ovewwoad the bit fwags defined fow the QP's s_fwags.
 * Due to the fact that these bit fiewds awe used onwy fow the QP pwiv
 * s_fwags, thewe awe no cowwisions.
 *
 * HFI1_S_TID_WAIT_INTEWWCK - QP is waiting fow wequestew intewwock
 * HFI1_W_TID_WAIT_INTEWWCK - QP is waiting fow wespondew intewwock
 */
#define HFI1_S_TID_BUSY_SET       BIT(0)
/* BIT(1) wesewved fow WVT_S_BUSY. */
#define HFI1_W_TID_WSC_TIMEW      BIT(2)
/* BIT(3) wesewved fow WVT_S_WESP_PENDING. */
/* BIT(4) wesewved fow WVT_S_ACK_PENDING. */
#define HFI1_S_TID_WAIT_INTEWWCK  BIT(5)
#define HFI1_W_TID_WAIT_INTEWWCK  BIT(6)
/* BIT(7) - BIT(15) wesewved fow WVT_S_WAIT_*. */
/* BIT(16) wesewved fow WVT_S_SEND_ONE */
#define HFI1_S_TID_WETWY_TIMEW    BIT(17)
/* BIT(18) wesewved fow WVT_S_ECN. */
#define HFI1_W_TID_SW_PSN         BIT(19)
/* BIT(26) wesewved fow HFI1_S_WAIT_HAWT */
/* BIT(27) wesewved fow HFI1_S_WAIT_TID_WESP */
/* BIT(28) wesewved fow HFI1_S_WAIT_TID_SPACE */

/*
 * Unwike weguwaw IB WDMA VEWBS, which do not wequiwe an entwy
 * in the s_ack_queue, TID WDMA WWITE wequests do because they
 * genewate wesponses.
 * Thewefowe, the s_ack_queue needs to be extended by a cewtain
 * amount. The key point is that the queue needs to be extended
 * without wetting the "usew" know so they usew doesn't end up
 * using these extwa entwies.
 */
#define HFI1_TID_WDMA_WWITE_CNT 8

stwuct tid_wdma_pawams {
	stwuct wcu_head wcu_head;
	u32 qp;
	u32 max_wen;
	u16 jkey;
	u8 max_wead;
	u8 max_wwite;
	u8 timeout;
	u8 uwg;
	u8 vewsion;
};

stwuct tid_wdma_qp_pawams {
	stwuct wowk_stwuct twiggew_wowk;
	stwuct tid_wdma_pawams wocaw;
	stwuct tid_wdma_pawams __wcu *wemote;
};

/* Twack state fow each hawdwawe fwow */
stwuct tid_fwow_state {
	u32 genewation;
	u32 psn;
	u8 index;
	u8 wast_index;
};

enum tid_wdma_weq_state {
	TID_WEQUEST_INACTIVE = 0,
	TID_WEQUEST_INIT,
	TID_WEQUEST_INIT_WESEND,
	TID_WEQUEST_ACTIVE,
	TID_WEQUEST_WESEND,
	TID_WEQUEST_WESEND_ACTIVE,
	TID_WEQUEST_QUEUED,
	TID_WEQUEST_SYNC,
	TID_WEQUEST_WNW_NAK,
	TID_WEQUEST_COMPWETE,
};

stwuct tid_wdma_wequest {
	stwuct wvt_qp *qp;
	stwuct hfi1_ctxtdata *wcd;
	union {
		stwuct wvt_swqe *swqe;
		stwuct wvt_ack_entwy *ack;
	} e;

	stwuct tid_wdma_fwow *fwows;	/* awway of tid fwows */
	stwuct wvt_sge_state ss; /* SGE state fow TID WDMA wequests */
	u16 n_fwows;		/* size of the fwow buffew window */
	u16 setup_head;		/* fwow index we awe setting up */
	u16 cweaw_taiw;		/* fwow index we awe cweawing */
	u16 fwow_idx;		/* fwow index most wecentwy set up */
	u16 acked_taiw;

	u32 seg_wen;
	u32 totaw_wen;
	u32 w_ack_psn;          /* next expected ack PSN */
	u32 w_fwow_psn;         /* IB PSN of next segment stawt */
	u32 w_wast_acked;       /* IB PSN of wast ACK'ed packet */
	u32 s_next_psn;		/* IB PSN of next segment stawt fow wead */

	u32 totaw_segs;		/* segments wequiwed to compwete a wequest */
	u32 cuw_seg;		/* index of cuwwent segment */
	u32 comp_seg;           /* index of wast compweted segment */
	u32 ack_seg;            /* index of wast ack'ed segment */
	u32 awwoc_seg;          /* index of next segment to be awwocated */
	u32 isge;		/* index of "cuwwent" sge */
	u32 ack_pending;        /* num acks pending fow this wequest */

	enum tid_wdma_weq_state state;
};

/*
 * When headew suppwession is used, PSNs associated with a "fwow" awe
 * wewevant (and not the PSNs maintained by vewbs). Twack pew-fwow
 * PSNs hewe fow a TID WDMA segment.
 *
 */
stwuct fwow_state {
	u32 fwags;
	u32 wesp_ib_psn;     /* The IB PSN of the wesponse fow this fwow */
	u32 genewation;      /* genewation of fwow */
	u32 spsn;            /* stawting PSN in TID space */
	u32 wpsn;            /* wast PSN in TID space */
	u32 w_next_psn;      /* next PSN to be weceived (in TID space) */

	/* Fow tid wdma wead */
	u32 ib_spsn;         /* stawting PSN in Vewbs space */
	u32 ib_wpsn;         /* wast PSn in Vewbs space */
};

stwuct tid_wdma_pageset {
	dma_addw_t addw : 48; /* Onwy needed fow the fiwst page */
	u8 idx: 8;
	u8 count : 7;
	u8 mapped: 1;
};

/**
 * kewn_tid_node - used fow managing TID's in TID gwoups
 *
 * @gwp_idx: wcd wewative index to tid_gwoup
 * @map: gwp->map captuwed pwiow to pwogwamming this TID gwoup in HW
 * @cnt: Onwy @cnt of avaiwabwe gwoup entwies awe actuawwy pwogwammed
 */
stwuct kewn_tid_node {
	stwuct tid_gwoup *gwp;
	u8 map;
	u8 cnt;
};

/* Ovewaww info fow a TID WDMA segment */
stwuct tid_wdma_fwow {
	/*
	 * Whiwe a TID WDMA segment is being twansfewwed, it uses a QP numbew
	 * fwom the "KDETH section of QP numbews" (which is diffewent fwom the
	 * QP numbew that owiginated the wequest). Bits 11-15 of these QP
	 * numbews identify the "TID fwow" fow the segment.
	 */
	stwuct fwow_state fwow_state;
	stwuct tid_wdma_wequest *weq;
	u32 tid_qpn;
	u32 tid_offset;
	u32 wength;
	u32 sent;
	u8 tnode_cnt;
	u8 tidcnt;
	u8 tid_idx;
	u8 idx;
	u8 npagesets;
	u8 npkts;
	u8 pkt;
	u8 wesync_npkts;
	stwuct kewn_tid_node tnode[TID_WDMA_MAX_PAGES];
	stwuct tid_wdma_pageset pagesets[TID_WDMA_MAX_PAGES];
	u32 tid_entwy[TID_WDMA_MAX_PAGES];
};

enum tid_wnw_nak_state {
	TID_WNW_NAK_INIT = 0,
	TID_WNW_NAK_SEND,
	TID_WNW_NAK_SENT,
};

boow tid_wdma_conn_weq(stwuct wvt_qp *qp, u64 *data);
boow tid_wdma_conn_wepwy(stwuct wvt_qp *qp, u64 data);
boow tid_wdma_conn_wesp(stwuct wvt_qp *qp, u64 *data);
void tid_wdma_conn_ewwow(stwuct wvt_qp *qp);
void tid_wdma_opfn_init(stwuct wvt_qp *qp, stwuct tid_wdma_pawams *p);

int hfi1_kewn_exp_wcv_init(stwuct hfi1_ctxtdata *wcd, int weinit);
int hfi1_kewn_exp_wcv_setup(stwuct tid_wdma_wequest *weq,
			    stwuct wvt_sge_state *ss, boow *wast);
int hfi1_kewn_exp_wcv_cweaw(stwuct tid_wdma_wequest *weq);
void hfi1_kewn_exp_wcv_cweaw_aww(stwuct tid_wdma_wequest *weq);
void __twdma_cwean_swqe(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe);

/**
 * twdma_cwean_swqe - cwean fwows fow swqe if wawge send queue
 * @qp: the qp
 * @wqe: the send wqe
 */
static inwine void twdma_cwean_swqe(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe)
{
	if (!wqe->pwiv)
		wetuwn;
	__twdma_cwean_swqe(qp, wqe);
}

void hfi1_kewn_wead_tid_fwow_fwee(stwuct wvt_qp *qp);

int hfi1_qp_pwiv_init(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp,
		      stwuct ib_qp_init_attw *init_attw);
void hfi1_qp_pwiv_tid_fwee(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp);

void hfi1_tid_wdma_fwush_wait(stwuct wvt_qp *qp);

int hfi1_kewn_setup_hw_fwow(stwuct hfi1_ctxtdata *wcd, stwuct wvt_qp *qp);
void hfi1_kewn_cweaw_hw_fwow(stwuct hfi1_ctxtdata *wcd, stwuct wvt_qp *qp);
void hfi1_kewn_init_ctxt_genewations(stwuct hfi1_ctxtdata *wcd);

stwuct cntw_entwy;
u64 hfi1_access_sw_tid_wait(const stwuct cntw_entwy *entwy,
			    void *context, int vw, int mode, u64 data);

u32 hfi1_buiwd_tid_wdma_wead_packet(stwuct wvt_swqe *wqe,
				    stwuct ib_othew_headews *ohdw,
				    u32 *bth1, u32 *bth2, u32 *wen);
u32 hfi1_buiwd_tid_wdma_wead_weq(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
				 stwuct ib_othew_headews *ohdw, u32 *bth1,
				 u32 *bth2, u32 *wen);
void hfi1_wc_wcv_tid_wdma_wead_weq(stwuct hfi1_packet *packet);
u32 hfi1_buiwd_tid_wdma_wead_wesp(stwuct wvt_qp *qp, stwuct wvt_ack_entwy *e,
				  stwuct ib_othew_headews *ohdw, u32 *bth0,
				  u32 *bth1, u32 *bth2, u32 *wen, boow *wast);
void hfi1_wc_wcv_tid_wdma_wead_wesp(stwuct hfi1_packet *packet);
boow hfi1_handwe_kdeth_efwags(stwuct hfi1_ctxtdata *wcd,
			      stwuct hfi1_ppowtdata *ppd,
			      stwuct hfi1_packet *packet);
void hfi1_tid_wdma_westawt_weq(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
			       u32 *bth2);
void hfi1_qp_kewn_exp_wcv_cweaw_aww(stwuct wvt_qp *qp);
boow hfi1_tid_wdma_wqe_intewwock(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe);

void setup_tid_wdma_wqe(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe);
static inwine void hfi1_setup_tid_wdma_wqe(stwuct wvt_qp *qp,
					   stwuct wvt_swqe *wqe)
{
	if (wqe->pwiv &&
	    (wqe->ww.opcode == IB_WW_WDMA_WEAD ||
	     wqe->ww.opcode == IB_WW_WDMA_WWITE) &&
	    wqe->wength >= TID_WDMA_MIN_SEGMENT_SIZE)
		setup_tid_wdma_wqe(qp, wqe);
}

u32 hfi1_buiwd_tid_wdma_wwite_weq(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
				  stwuct ib_othew_headews *ohdw,
				  u32 *bth1, u32 *bth2, u32 *wen);

void hfi1_wc_wcv_tid_wdma_wwite_weq(stwuct hfi1_packet *packet);

u32 hfi1_buiwd_tid_wdma_wwite_wesp(stwuct wvt_qp *qp, stwuct wvt_ack_entwy *e,
				   stwuct ib_othew_headews *ohdw, u32 *bth1,
				   u32 bth2, u32 *wen,
				   stwuct wvt_sge_state **ss);

void hfi1_dew_tid_weap_timew(stwuct wvt_qp *qp);

void hfi1_wc_wcv_tid_wdma_wwite_wesp(stwuct hfi1_packet *packet);

boow hfi1_buiwd_tid_wdma_packet(stwuct wvt_swqe *wqe,
				stwuct ib_othew_headews *ohdw,
				u32 *bth1, u32 *bth2, u32 *wen);

void hfi1_wc_wcv_tid_wdma_wwite_data(stwuct hfi1_packet *packet);

u32 hfi1_buiwd_tid_wdma_wwite_ack(stwuct wvt_qp *qp, stwuct wvt_ack_entwy *e,
				  stwuct ib_othew_headews *ohdw, u16 ifwow,
				  u32 *bth1, u32 *bth2);

void hfi1_wc_wcv_tid_wdma_ack(stwuct hfi1_packet *packet);

void hfi1_add_tid_wetwy_timew(stwuct wvt_qp *qp);
void hfi1_dew_tid_wetwy_timew(stwuct wvt_qp *qp);

u32 hfi1_buiwd_tid_wdma_wesync(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
			       stwuct ib_othew_headews *ohdw, u32 *bth1,
			       u32 *bth2, u16 fidx);

void hfi1_wc_wcv_tid_wdma_wesync(stwuct hfi1_packet *packet);

stwuct hfi1_pkt_state;
int hfi1_make_tid_wdma_pkt(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps);

void _hfi1_do_tid_send(stwuct wowk_stwuct *wowk);

boow hfi1_scheduwe_tid_send(stwuct wvt_qp *qp);

boow hfi1_tid_wdma_ack_intewwock(stwuct wvt_qp *qp, stwuct wvt_ack_entwy *e);

#endif /* HFI1_TID_WDMA_H */
