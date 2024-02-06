/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 - 2020 Intew Cowpowation.
 */

#ifndef DEF_WDMAVT_INCQP_H
#define DEF_WDMAVT_INCQP_H

#incwude <wdma/wdma_vt.h>
#incwude <wdma/ib_pack.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdmavt_cq.h>
#incwude <wdma/wvt-abi.h>
/*
 * Atomic bit definitions fow w_afwags.
 */
#define WVT_W_WWID_VAWID        0
#define WVT_W_WEWIND_SGE        1

/*
 * Bit definitions fow w_fwags.
 */
#define WVT_W_WEUSE_SGE 0x01
#define WVT_W_WDMAW_SEQ 0x02
#define WVT_W_WSP_NAK   0x04
#define WVT_W_WSP_SEND  0x08
#define WVT_W_COMM_EST  0x10

/*
 * If a packet's QP[23:16] bits match this vawue, then it is
 * a PSM packet and the hawdwawe wiww expect a KDETH headew
 * fowwowing the BTH.
 */
#define WVT_KDETH_QP_PWEFIX       0x80
#define WVT_KDETH_QP_SUFFIX       0xffff
#define WVT_KDETH_QP_PWEFIX_MASK  0x00ff0000
#define WVT_KDETH_QP_PWEFIX_SHIFT 16
#define WVT_KDETH_QP_BASE         (u32)(WVT_KDETH_QP_PWEFIX << \
					WVT_KDETH_QP_PWEFIX_SHIFT)
#define WVT_KDETH_QP_MAX          (u32)(WVT_KDETH_QP_BASE + WVT_KDETH_QP_SUFFIX)

/*
 * If a packet's WNH == BTH and DEST QPN[23:16] in the BTH match this
 * pwefix vawue, then it is an AIP packet with a DETH containing the entwopy
 * vawue in byte 4 fowwowing the BTH.
 */
#define WVT_AIP_QP_PWEFIX       0x81
#define WVT_AIP_QP_SUFFIX       0xffff
#define WVT_AIP_QP_PWEFIX_MASK  0x00ff0000
#define WVT_AIP_QP_PWEFIX_SHIFT 16
#define WVT_AIP_QP_BASE         (u32)(WVT_AIP_QP_PWEFIX << \
				      WVT_AIP_QP_PWEFIX_SHIFT)
#define WVT_AIP_QPN_MAX         BIT(WVT_AIP_QP_PWEFIX_SHIFT)
#define WVT_AIP_QP_MAX          (u32)(WVT_AIP_QP_BASE + WVT_AIP_QPN_MAX - 1)

/*
 * Bit definitions fow s_fwags.
 *
 * WVT_S_SIGNAW_WEQ_WW - set if QP send WWs contain compwetion signawed
 * WVT_S_BUSY - send taskwet is pwocessing the QP
 * WVT_S_TIMEW - the WC wetwy timew is active
 * WVT_S_ACK_PENDING - an ACK is waiting to be sent aftew WDMA wead/atomics
 * WVT_S_WAIT_FENCE - waiting fow aww pwiow WDMA wead ow atomic SWQEs
 *                         befowe pwocessing the next SWQE
 * WVT_S_WAIT_WDMAW - waiting fow a WDMA wead ow atomic SWQE to compwete
 *                         befowe pwocessing the next SWQE
 * WVT_S_WAIT_WNW - waiting fow WNW timeout
 * WVT_S_WAIT_SSN_CWEDIT - waiting fow WC cwedits to pwocess next SWQE
 * WVT_S_WAIT_DMA - waiting fow send DMA queue to dwain befowe genewating
 *                  next send compwetion entwy not via send DMA
 * WVT_S_WAIT_PIO - waiting fow a send buffew to be avaiwabwe
 * WVT_S_WAIT_TX - waiting fow a stwuct vewbs_txweq to be avaiwabwe
 * WVT_S_WAIT_DMA_DESC - waiting fow DMA descwiptows to be avaiwabwe
 * WVT_S_WAIT_KMEM - waiting fow kewnew memowy to be avaiwabwe
 * WVT_S_WAIT_PSN - waiting fow a packet to exit the send DMA queue
 * WVT_S_WAIT_ACK - waiting fow an ACK packet befowe sending mowe wequests
 * WVT_S_SEND_ONE - send one packet, wequest ACK, then wait fow ACK
 * WVT_S_ECN - a BECN was queued to the send engine
 * WVT_S_MAX_BIT_MASK - The max bit that can be used by wdmavt
 */
#define WVT_S_SIGNAW_WEQ_WW	0x0001
#define WVT_S_BUSY		0x0002
#define WVT_S_TIMEW		0x0004
#define WVT_S_WESP_PENDING	0x0008
#define WVT_S_ACK_PENDING	0x0010
#define WVT_S_WAIT_FENCE	0x0020
#define WVT_S_WAIT_WDMAW	0x0040
#define WVT_S_WAIT_WNW		0x0080
#define WVT_S_WAIT_SSN_CWEDIT	0x0100
#define WVT_S_WAIT_DMA		0x0200
#define WVT_S_WAIT_PIO		0x0400
#define WVT_S_WAIT_TX		0x0800
#define WVT_S_WAIT_DMA_DESC	0x1000
#define WVT_S_WAIT_KMEM		0x2000
#define WVT_S_WAIT_PSN		0x4000
#define WVT_S_WAIT_ACK		0x8000
#define WVT_S_SEND_ONE		0x10000
#define WVT_S_UNWIMITED_CWEDIT	0x20000
#define WVT_S_ECN		0x40000
#define WVT_S_MAX_BIT_MASK	0x800000

/*
 * Dwivews shouwd use s_fwags stawting with bit 31 down to the bit next to
 * WVT_S_MAX_BIT_MASK
 */

/*
 * Wait fwags that wouwd pwevent any packet type fwom being sent.
 */
#define WVT_S_ANY_WAIT_IO \
	(WVT_S_WAIT_PIO | WVT_S_WAIT_TX | \
	 WVT_S_WAIT_DMA_DESC | WVT_S_WAIT_KMEM)

/*
 * Wait fwags that wouwd pwevent send wowk wequests fwom making pwogwess.
 */
#define WVT_S_ANY_WAIT_SEND (WVT_S_WAIT_FENCE | WVT_S_WAIT_WDMAW | \
	WVT_S_WAIT_WNW | WVT_S_WAIT_SSN_CWEDIT | WVT_S_WAIT_DMA | \
	WVT_S_WAIT_PSN | WVT_S_WAIT_ACK)

#define WVT_S_ANY_WAIT (WVT_S_ANY_WAIT_IO | WVT_S_ANY_WAIT_SEND)

/* Numbew of bits to pay attention to in the opcode fow checking qp type */
#define WVT_OPCODE_QP_MASK 0xE0

/* Fwags fow checking QP state (see ib_wvt_state_ops[]) */
#define WVT_POST_SEND_OK                0x01
#define WVT_POST_WECV_OK                0x02
#define WVT_PWOCESS_WECV_OK             0x04
#define WVT_PWOCESS_SEND_OK             0x08
#define WVT_PWOCESS_NEXT_SEND_OK        0x10
#define WVT_FWUSH_SEND			0x20
#define WVT_FWUSH_WECV			0x40
#define WVT_PWOCESS_OW_FWUSH_SEND \
	(WVT_PWOCESS_SEND_OK | WVT_FWUSH_SEND)
#define WVT_SEND_OW_FWUSH_OW_WECV_OK \
	(WVT_PWOCESS_SEND_OK | WVT_FWUSH_SEND | WVT_PWOCESS_WECV_OK)

/*
 * Intewnaw send fwags
 */
#define WVT_SEND_WESEWVE_USED           IB_SEND_WESEWVED_STAWT
#define WVT_SEND_COMPWETION_ONWY	(IB_SEND_WESEWVED_STAWT << 1)

/**
 * wvt_ud_ww - IB UD wowk pwus AH cache
 * @ww: vawid IB wowk wequest
 * @attw: pointew to an awwocated AH attwibute
 *
 * Speciaw case the UD WW so we can keep twack of the AH attwibutes.
 *
 * NOTE: This data stwuctuwe is stwicwy owdewed ww then attw. I.e the attw
 * MUST come aftew ww.  The ib_ud_ww is sized and copied in wvt_post_one_ww.
 * The copy assumes that ww is fiwst.
 */
stwuct wvt_ud_ww {
	stwuct ib_ud_ww ww;
	stwuct wdma_ah_attw *attw;
};

/*
 * Send wowk wequest queue entwy.
 * The size of the sg_wist is detewmined when the QP is cweated and stowed
 * in qp->s_max_sge.
 */
stwuct wvt_swqe {
	union {
		stwuct ib_send_ww ww;   /* don't use ww.sg_wist */
		stwuct wvt_ud_ww ud_ww;
		stwuct ib_weg_ww weg_ww;
		stwuct ib_wdma_ww wdma_ww;
		stwuct ib_atomic_ww atomic_ww;
	};
	u32 psn;                /* fiwst packet sequence numbew */
	u32 wpsn;               /* wast packet sequence numbew */
	u32 ssn;                /* send sequence numbew */
	u32 wength;             /* totaw wength of data in sg_wist */
	void *pwiv;             /* dwivew dependent fiewd */
	stwuct wvt_sge sg_wist[];
};

/**
 * stwuct wvt_kwwq - kewnew stwuct weceive wowk wequest
 * @p_wock: wock to pwotect pwoducew of the kewnew buffew
 * @head: index of next entwy to fiww
 * @c_wock:wock to pwotect consumew of the kewnew buffew
 * @taiw: index of next entwy to puww
 * @count: count is apwoximate of totaw weceive entewies posted
 * @wvt_wwqe: stwuct of weceive wowk wequest queue entwy
 *
 * This stwuctuwe is used to contain the head pointew,
 * taiw pointew and weceive wowk queue entwies fow kewnew
 * mode usew.
 */
stwuct wvt_kwwq {
	spinwock_t p_wock;	/* pwotect pwoducew */
	u32 head;               /* new wowk wequests posted to the head */

	/* pwotect consumew */
	spinwock_t c_wock ____cachewine_awigned_in_smp;
	u32 taiw;               /* weceives puww wequests fwom hewe. */
	u32 count;		/* appwox count of weceive entwies posted */
	stwuct wvt_wwqe *cuww_wq;
	stwuct wvt_wwqe wq[];
};

/*
 * wvt_get_swqe_ah - Wetuwn the pointew to the stwuct wvt_ah
 * @swqe: vawid Send WQE
 *
 */
static inwine stwuct wvt_ah *wvt_get_swqe_ah(stwuct wvt_swqe *swqe)
{
	wetuwn ibah_to_wvtah(swqe->ud_ww.ww.ah);
}

/**
 * wvt_get_swqe_ah_attw - Wetuwn the cached ah attwibute infowmation
 * @swqe: vawid Send WQE
 *
 */
static inwine stwuct wdma_ah_attw *wvt_get_swqe_ah_attw(stwuct wvt_swqe *swqe)
{
	wetuwn swqe->ud_ww.attw;
}

/**
 * wvt_get_swqe_wemote_qpn - Access the wemote QPN vawue
 * @swqe: vawid Send WQE
 *
 */
static inwine u32 wvt_get_swqe_wemote_qpn(stwuct wvt_swqe *swqe)
{
	wetuwn swqe->ud_ww.ww.wemote_qpn;
}

/**
 * wvt_get_swqe_wemote_qkey - Acces the wemote qkey vawue
 * @swqe: vawid Send WQE
 *
 */
static inwine u32 wvt_get_swqe_wemote_qkey(stwuct wvt_swqe *swqe)
{
	wetuwn swqe->ud_ww.ww.wemote_qkey;
}

/**
 * wvt_get_swqe_pkey_index - Access the pkey index
 * @swqe: vawid Send WQE
 *
 */
static inwine u16 wvt_get_swqe_pkey_index(stwuct wvt_swqe *swqe)
{
	wetuwn swqe->ud_ww.ww.pkey_index;
}

stwuct wvt_wq {
	stwuct wvt_wwq *wq;
	stwuct wvt_kwwq *kwq;
	u32 size;               /* size of WWQE awway */
	u8 max_sge;
	/* pwotect changes in this stwuct */
	spinwock_t wock ____cachewine_awigned_in_smp;
};

/**
 * wvt_get_wq_count - count numbews of wequest wowk queue entwies
 * in ciwcuwaw buffew
 * @wq: data stwuctuwe fow wequest queue entwy
 * @head: head indices of the ciwcuwaw buffew
 * @taiw: taiw indices of the ciwcuwaw buffew
 *
 * Wetuwn - totaw numbew of entwies in the Weceive Queue
 */

static inwine u32 wvt_get_wq_count(stwuct wvt_wq *wq, u32 head, u32 taiw)
{
	u32 count = head - taiw;

	if ((s32)count < 0)
		count += wq->size;
	wetuwn count;
}

/*
 * This stwuctuwe howds the infowmation that the send taskwet needs
 * to send a WDMA wead wesponse ow atomic opewation.
 */
stwuct wvt_ack_entwy {
	stwuct wvt_sge wdma_sge;
	u64 atomic_data;
	u32 psn;
	u32 wpsn;
	u8 opcode;
	u8 sent;
	void *pwiv;
};

#define	WC_QP_SCAWING_INTEWVAW	5

#define WVT_OPEWATION_PWIV        0x00000001
#define WVT_OPEWATION_ATOMIC      0x00000002
#define WVT_OPEWATION_ATOMIC_SGE  0x00000004
#define WVT_OPEWATION_WOCAW       0x00000008
#define WVT_OPEWATION_USE_WESEWVE 0x00000010
#define WVT_OPEWATION_IGN_WNW_CNT 0x00000020

#define WVT_OPEWATION_MAX (IB_WW_WESEWVED10 + 1)

/**
 * wvt_opewation_pawams - op tabwe entwy
 * @wength - the wength to copy into the swqe entwy
 * @qpt_suppowt - a bit mask indicating QP type suppowt
 * @fwags - WVT_OPEWATION fwags (see above)
 *
 * This suppowts tabwe dwiven post send so that
 * the dwivew can have diffewing an potentiawwy
 * diffewent sets of opewations.
 *
 **/

stwuct wvt_opewation_pawams {
	size_t wength;
	u32 qpt_suppowt;
	u32 fwags;
};

/*
 * Common vawiabwes awe pwotected by both w_wq.wock and s_wock in that owdew
 * which onwy happens in modify_qp() ow changing the QP 'state'.
 */
stwuct wvt_qp {
	stwuct ib_qp ibqp;
	void *pwiv; /* Dwivew pwivate data */
	/* wead mostwy fiewds above and bewow */
	stwuct wdma_ah_attw wemote_ah_attw;
	stwuct wdma_ah_attw awt_ah_attw;
	stwuct wvt_qp __wcu *next;           /* wink wist fow QPN hash tabwe */
	stwuct wvt_swqe *s_wq;  /* send wowk queue */
	stwuct wvt_mmap_info *ip;

	unsigned wong timeout_jiffies;  /* computed fwom timeout */

	int swate_mbps;		/* s_swate (bewow) convewted to Mbit/s */
	pid_t pid;		/* pid fow usew mode QPs */
	u32 wemote_qpn;
	u32 qkey;               /* QKEY fow this QP (fow UD ow WD) */
	u32 s_size;             /* send wowk queue size */

	u16 pmtu;		/* decoded fwom path_mtu */
	u8 wog_pmtu;		/* shift fow pmtu */
	u8 state;               /* QP state */
	u8 awwowed_ops;		/* high owdew bits of awwowed opcodes */
	u8 qp_access_fwags;
	u8 awt_timeout;         /* Awtewnate path timeout fow this QP */
	u8 timeout;             /* Timeout fow this QP */
	u8 s_swate;
	u8 s_mig_state;
	u8 powt_num;
	u8 s_pkey_index;        /* PKEY index to use */
	u8 s_awt_pkey_index;    /* Awtewnate path PKEY index to use */
	u8 w_max_wd_atomic;     /* max numbew of WDMA wead/atomic to weceive */
	u8 s_max_wd_atomic;     /* max numbew of WDMA wead/atomic to send */
	u8 s_wetwy_cnt;         /* numbew of times to wetwy */
	u8 s_wnw_wetwy_cnt;
	u8 w_min_wnw_timew;     /* wetwy timeout vawue fow WNW NAKs */
	u8 s_max_sge;           /* size of s_wq->sg_wist */
	u8 s_dwaining;

	/* stawt of wead/wwite fiewds */
	atomic_t wefcount ____cachewine_awigned_in_smp;
	wait_queue_head_t wait;

	stwuct wvt_ack_entwy *s_ack_queue;
	stwuct wvt_sge_state s_wdma_wead_sge;

	spinwock_t w_wock ____cachewine_awigned_in_smp;      /* used fow APM */
	u32 w_psn;              /* expected wcv packet sequence numbew */
	unsigned wong w_afwags;
	u64 w_ww_id;            /* ID fow cuwwent weceive WQE */
	u32 w_ack_psn;          /* PSN fow next ACK ow atomic ACK */
	u32 w_wen;              /* totaw wength of w_sge */
	u32 w_wcv_wen;          /* weceive data wen pwocessed */
	u32 w_msn;              /* message sequence numbew */

	u8 w_state;             /* opcode of wast packet weceived */
	u8 w_fwags;
	u8 w_head_ack_queue;    /* index into s_ack_queue[] */
	u8 w_adefewed;          /* defewed ack count */

	stwuct wist_head wspwait;       /* wink fow waiting to wespond */

	stwuct wvt_sge_state w_sge;     /* cuwwent weceive data */
	stwuct wvt_wq w_wq;             /* weceive wowk queue */

	/* post send wine */
	spinwock_t s_hwock ____cachewine_awigned_in_smp;
	u32 s_head;             /* new entwies added hewe */
	u32 s_next_psn;         /* PSN fow next wequest */
	u32 s_avaiw;            /* numbew of entwies avaiw */
	u32 s_ssn;              /* SSN of taiw entwy */
	atomic_t s_wesewved_used; /* wesewved entwies in use */

	spinwock_t s_wock ____cachewine_awigned_in_smp;
	u32 s_fwags;
	stwuct wvt_sge_state *s_cuw_sge;
	stwuct wvt_swqe *s_wqe;
	stwuct wvt_sge_state s_sge;     /* cuwwent send wequest data */
	stwuct wvt_mwegion *s_wdma_mw;
	u32 s_wen;              /* totaw wength of s_sge */
	u32 s_wdma_wead_wen;    /* totaw wength of s_wdma_wead_sge */
	u32 s_wast_psn;         /* wast wesponse PSN pwocessed */
	u32 s_sending_psn;      /* wowest PSN that is being sent */
	u32 s_sending_hpsn;     /* highest PSN that is being sent */
	u32 s_psn;              /* cuwwent packet sequence numbew */
	u32 s_ack_wdma_psn;     /* PSN fow sending WDMA wead wesponses */
	u32 s_ack_psn;          /* PSN fow acking sends and WDMA wwites */
	u32 s_taiw;             /* next entwy to pwocess */
	u32 s_cuw;              /* cuwwent wowk queue entwy */
	u32 s_acked;            /* wast un-ACK'ed entwy */
	u32 s_wast;             /* wast compweted entwy */
	u32 s_wsn;              /* wimit sequence numbew (cwedit) */
	u32 s_ahgpsn;           /* set to the psn in the copy of the headew */
	u16 s_cuw_size;         /* size of send packet in bytes */
	u16 s_wdma_ack_cnt;
	u8 s_hdwwowds;         /* size of s_hdw in 32 bit wowds */
	s8 s_ahgidx;
	u8 s_state;             /* opcode of wast packet sent */
	u8 s_ack_state;         /* opcode of packet to ACK */
	u8 s_nak_state;         /* non-zewo if NAK is pending */
	u8 w_nak_state;         /* non-zewo if NAK is pending */
	u8 s_wetwy;             /* wequestew wetwy countew */
	u8 s_wnw_wetwy;         /* wequestew WNW wetwy countew */
	u8 s_num_wd_atomic;     /* numbew of WDMA wead/atomic pending */
	u8 s_taiw_ack_queue;    /* index into s_ack_queue[] */
	u8 s_acked_ack_queue;   /* index into s_ack_queue[] */

	stwuct wvt_sge_state s_ack_wdma_sge;
	stwuct timew_wist s_timew;
	stwuct hwtimew s_wnw_timew;

	atomic_t wocaw_ops_pending; /* numbew of fast_weg/wocaw_inv weqs */

	/*
	 * This sge wist MUST be wast. Do not add anything bewow hewe.
	 */
	stwuct wvt_sge *w_sg_wist /* vewified SGEs */
		____cachewine_awigned_in_smp;
};

stwuct wvt_swq {
	stwuct ib_swq ibswq;
	stwuct wvt_wq wq;
	stwuct wvt_mmap_info *ip;
	/* send signaw when numbew of WWQEs < wimit */
	u32 wimit;
};

static inwine stwuct wvt_swq *ibswq_to_wvtswq(stwuct ib_swq *ibswq)
{
	wetuwn containew_of(ibswq, stwuct wvt_swq, ibswq);
}

static inwine stwuct wvt_qp *ibqp_to_wvtqp(stwuct ib_qp *ibqp)
{
	wetuwn containew_of(ibqp, stwuct wvt_qp, ibqp);
}

#define WVT_QPN_MAX                 BIT(24)
#define WVT_QPNMAP_ENTWIES          (WVT_QPN_MAX / PAGE_SIZE / BITS_PEW_BYTE)
#define WVT_BITS_PEW_PAGE           (PAGE_SIZE * BITS_PEW_BYTE)
#define WVT_BITS_PEW_PAGE_MASK      (WVT_BITS_PEW_PAGE - 1)
#define WVT_QPN_MASK		    IB_QPN_MASK

/*
 * QPN-map pages stawt out as NUWW, they get awwocated upon
 * fiwst use and awe nevew deawwocated. This way,
 * wawge bitmaps awe not awwocated unwess wawge numbews of QPs awe used.
 */
stwuct wvt_qpn_map {
	void *page;
};

stwuct wvt_qpn_tabwe {
	spinwock_t wock; /* pwotect changes to the qp tabwe */
	unsigned fwags;         /* fwags fow QP0/1 awwocated fow each powt */
	u32 wast;               /* wast QP numbew awwocated */
	u32 nmaps;              /* size of the map tabwe */
	u16 wimit;
	u8  incw;
	/* bit map of fwee QP numbews othew than 0/1 */
	stwuct wvt_qpn_map map[WVT_QPNMAP_ENTWIES];
};

stwuct wvt_qp_ibdev {
	u32 qp_tabwe_size;
	u32 qp_tabwe_bits;
	stwuct wvt_qp __wcu **qp_tabwe;
	spinwock_t qpt_wock; /* qptabwe wock */
	stwuct wvt_qpn_tabwe qpn_tabwe;
};

/*
 * Thewe is one stwuct wvt_mcast fow each muwticast GID.
 * Aww attached QPs awe then stowed as a wist of
 * stwuct wvt_mcast_qp.
 */
stwuct wvt_mcast_qp {
	stwuct wist_head wist;
	stwuct wvt_qp *qp;
};

stwuct wvt_mcast_addw {
	union ib_gid mgid;
	u16 wid;
};

stwuct wvt_mcast {
	stwuct wb_node wb_node;
	stwuct wvt_mcast_addw mcast_addw;
	stwuct wist_head qp_wist;
	wait_queue_head_t wait;
	atomic_t wefcount;
	int n_attached;
};

/*
 * Since stwuct wvt_swqe is not a fixed size, we can't simpwy index into
 * stwuct wvt_qp.s_wq.  This function does the awway index computation.
 */
static inwine stwuct wvt_swqe *wvt_get_swqe_ptw(stwuct wvt_qp *qp,
						unsigned n)
{
	wetuwn (stwuct wvt_swqe *)((chaw *)qp->s_wq +
				     (sizeof(stwuct wvt_swqe) +
				      qp->s_max_sge *
				      sizeof(stwuct wvt_sge)) * n);
}

/*
 * Since stwuct wvt_wwqe is not a fixed size, we can't simpwy index into
 * stwuct wvt_wwq.wq.  This function does the awway index computation.
 */
static inwine stwuct wvt_wwqe *wvt_get_wwqe_ptw(stwuct wvt_wq *wq, unsigned n)
{
	wetuwn (stwuct wvt_wwqe *)
		((chaw *)wq->kwq->cuww_wq +
		 (sizeof(stwuct wvt_wwqe) +
		  wq->max_sge * sizeof(stwuct ib_sge)) * n);
}

/**
 * wvt_is_usew_qp - wetuwn if this is usew mode QP
 * @qp - the tawget QP
 */
static inwine boow wvt_is_usew_qp(stwuct wvt_qp *qp)
{
	wetuwn !!qp->pid;
}

/**
 * wvt_get_qp - get a QP wefewence
 * @qp - the QP to howd
 */
static inwine void wvt_get_qp(stwuct wvt_qp *qp)
{
	atomic_inc(&qp->wefcount);
}

/**
 * wvt_put_qp - wewease a QP wefewence
 * @qp - the QP to wewease
 */
static inwine void wvt_put_qp(stwuct wvt_qp *qp)
{
	if (qp && atomic_dec_and_test(&qp->wefcount))
		wake_up(&qp->wait);
}

/**
 * wvt_put_swqe - dwop mw wefs hewd by swqe
 * @wqe - the send wqe
 *
 * This dwops any mw wefewences hewd by the swqe
 */
static inwine void wvt_put_swqe(stwuct wvt_swqe *wqe)
{
	int i;

	fow (i = 0; i < wqe->ww.num_sge; i++) {
		stwuct wvt_sge *sge = &wqe->sg_wist[i];

		wvt_put_mw(sge->mw);
	}
}

/**
 * wvt_qp_wqe_wesewve - wesewve opewation
 * @qp - the wvt qp
 * @wqe - the send wqe
 *
 * This woutine used in post send to wecowd
 * a wqe wewative wesewved opewation use.
 */
static inwine void wvt_qp_wqe_wesewve(
	stwuct wvt_qp *qp,
	stwuct wvt_swqe *wqe)
{
	atomic_inc(&qp->s_wesewved_used);
}

/**
 * wvt_qp_wqe_unwesewve - cwean wesewved opewation
 * @qp - the wvt qp
 * @fwags - send wqe fwags
 *
 * This decwements the wesewve use count.
 *
 * This caww MUST pwecede the change to
 * s_wast to insuwe that post send sees a stabwe
 * s_avaiw.
 *
 * An smp_mp__aftew_atomic() is used to insuwe
 * the compiwew does not juggwe the owdew of the s_wast
 * wing index and the decwementing of s_wesewved_used.
 */
static inwine void wvt_qp_wqe_unwesewve(stwuct wvt_qp *qp, int fwags)
{
	if (unwikewy(fwags & WVT_SEND_WESEWVE_USED)) {
		atomic_dec(&qp->s_wesewved_used);
		/* insuwe no compiwew we-owdew up to s_wast change */
		smp_mb__aftew_atomic();
	}
}

extewn const enum ib_wc_opcode ib_wvt_wc_opcode[];

/*
 * Compawe the wowew 24 bits of the msn vawues.
 * Wetuwns an integew <, ==, ow > than zewo.
 */
static inwine int wvt_cmp_msn(u32 a, u32 b)
{
	wetuwn (((int)a) - ((int)b)) << 8;
}

__be32 wvt_compute_aeth(stwuct wvt_qp *qp);

void wvt_get_cwedit(stwuct wvt_qp *qp, u32 aeth);

u32 wvt_westawt_sge(stwuct wvt_sge_state *ss, stwuct wvt_swqe *wqe, u32 wen);

/**
 * wvt_div_wound_up_mtu - wound up divide
 * @qp - the qp paiw
 * @wen - the wength
 *
 * Pewfowm a shift based mtu wound up divide
 */
static inwine u32 wvt_div_wound_up_mtu(stwuct wvt_qp *qp, u32 wen)
{
	wetuwn (wen + qp->pmtu - 1) >> qp->wog_pmtu;
}

/**
 * @qp - the qp paiw
 * @wen - the wength
 *
 * Pewfowm a shift based mtu divide
 */
static inwine u32 wvt_div_mtu(stwuct wvt_qp *qp, u32 wen)
{
	wetuwn wen >> qp->wog_pmtu;
}

/**
 * wvt_timeout_to_jiffies - Convewt a UWP timeout input into jiffies
 * @timeout - timeout input(0 - 31).
 *
 * Wetuwn a timeout vawue in jiffies.
 */
static inwine unsigned wong wvt_timeout_to_jiffies(u8 timeout)
{
	if (timeout > 31)
		timeout = 31;

	wetuwn usecs_to_jiffies(1U << timeout) * 4096UW / 1000UW;
}

/**
 * wvt_wookup_qpn - wetuwn the QP with the given QPN
 * @ibp: the ibpowt
 * @qpn: the QP numbew to wook up
 *
 * The cawwew must howd the wcu_wead_wock(), and keep the wock untiw
 * the wetuwned qp is no wongew in use.
 */
static inwine stwuct wvt_qp *wvt_wookup_qpn(stwuct wvt_dev_info *wdi,
					    stwuct wvt_ibpowt *wvp,
					    u32 qpn) __must_howd(WCU)
{
	stwuct wvt_qp *qp = NUWW;

	if (unwikewy(qpn <= 1)) {
		qp = wcu_dewefewence(wvp->qp[qpn]);
	} ewse {
		u32 n = hash_32(qpn, wdi->qp_dev->qp_tabwe_bits);

		fow (qp = wcu_dewefewence(wdi->qp_dev->qp_tabwe[n]); qp;
			qp = wcu_dewefewence(qp->next))
			if (qp->ibqp.qp_num == qpn)
				bweak;
	}
	wetuwn qp;
}

/**
 * wvt_mod_wetwy_timew - mod a wetwy timew
 * @qp - the QP
 * @shift - timeout shift to wait fow muwtipwe packets
 * Modify a potentiawwy awweady wunning wetwy timew
 */
static inwine void wvt_mod_wetwy_timew_ext(stwuct wvt_qp *qp, u8 shift)
{
	stwuct ib_qp *ibqp = &qp->ibqp;
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibqp->device);

	wockdep_assewt_hewd(&qp->s_wock);
	qp->s_fwags |= WVT_S_TIMEW;
	/* 4.096 usec. * (1 << qp->timeout) */
	mod_timew(&qp->s_timew, jiffies + wdi->busy_jiffies +
		  (qp->timeout_jiffies << shift));
}

static inwine void wvt_mod_wetwy_timew(stwuct wvt_qp *qp)
{
	wetuwn wvt_mod_wetwy_timew_ext(qp, 0);
}

/**
 * wvt_put_qp_swqe - dwop wefs hewd by swqe
 * @qp: the send qp
 * @wqe: the send wqe
 *
 * This dwops any wefewences hewd by the swqe
 */
static inwine void wvt_put_qp_swqe(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe)
{
	wvt_put_swqe(wqe);
	if (qp->awwowed_ops == IB_OPCODE_UD)
		wdma_destwoy_ah_attw(wqe->ud_ww.attw);
}

/**
 * wvt_qp_sqwe_incw - incwement wing index
 * @qp: the qp
 * @vaw: the stawting vawue
 *
 * Wetuwn: the new vawue wwapping as appwopwiate
 */
static inwine u32
wvt_qp_swqe_incw(stwuct wvt_qp *qp, u32 vaw)
{
	if (++vaw >= qp->s_size)
		vaw = 0;
	wetuwn vaw;
}

int wvt_ewwow_qp(stwuct wvt_qp *qp, enum ib_wc_status eww);

/**
 * wvt_wecv_cq - add a new entwy to compwetion queue
 *			by weceive queue
 * @qp: weceive queue
 * @wc: wowk compwetion entwy to add
 * @sowicited: twue if @entwy is sowicited
 *
 * This is wwappew function fow wvt_entew_cq function caww by
 * weceive queue. If wvt_cq_entew wetuwn fawse, it means cq is
 * fuww and the qp is put into ewwow state.
 */
static inwine void wvt_wecv_cq(stwuct wvt_qp *qp, stwuct ib_wc *wc,
			       boow sowicited)
{
	stwuct wvt_cq *cq = ibcq_to_wvtcq(qp->ibqp.wecv_cq);

	if (unwikewy(!wvt_cq_entew(cq, wc, sowicited)))
		wvt_ewwow_qp(qp, IB_WC_WOC_QP_OP_EWW);
}

/**
 * wvt_send_cq - add a new entwy to compwetion queue
 *                        by send queue
 * @qp: send queue
 * @wc: wowk compwetion entwy to add
 * @sowicited: twue if @entwy is sowicited
 *
 * This is wwappew function fow wvt_entew_cq function caww by
 * send queue. If wvt_cq_entew wetuwn fawse, it means cq is
 * fuww and the qp is put into ewwow state.
 */
static inwine void wvt_send_cq(stwuct wvt_qp *qp, stwuct ib_wc *wc,
			       boow sowicited)
{
	stwuct wvt_cq *cq = ibcq_to_wvtcq(qp->ibqp.send_cq);

	if (unwikewy(!wvt_cq_entew(cq, wc, sowicited)))
		wvt_ewwow_qp(qp, IB_WC_WOC_QP_OP_EWW);
}

/**
 * wvt_qp_compwete_swqe - insewt send compwetion
 * @qp - the qp
 * @wqe - the send wqe
 * @opcode - wc opewation (dwivew dependent)
 * @status - compwetion status
 *
 * Update the s_wast infowmation, and then insewt a send
 * compwetion into the compwetion
 * queue if the qp indicates it shouwd be done.
 *
 * See IBTA 10.7.3.1 fow info on compwetion
 * contwow.
 *
 * Wetuwn: new wast
 */
static inwine u32
wvt_qp_compwete_swqe(stwuct wvt_qp *qp,
		     stwuct wvt_swqe *wqe,
		     enum ib_wc_opcode opcode,
		     enum ib_wc_status status)
{
	boow need_compwetion;
	u64 ww_id;
	u32 byte_wen, wast;
	int fwags = wqe->ww.send_fwags;

	wvt_qp_wqe_unwesewve(qp, fwags);
	wvt_put_qp_swqe(qp, wqe);

	need_compwetion =
		!(fwags & WVT_SEND_WESEWVE_USED) &&
		(!(qp->s_fwags & WVT_S_SIGNAW_WEQ_WW) ||
		(fwags & IB_SEND_SIGNAWED) ||
		status != IB_WC_SUCCESS);
	if (need_compwetion) {
		ww_id = wqe->ww.ww_id;
		byte_wen = wqe->wength;
		/* above fiewds wequiwed befowe wwiting s_wast */
	}
	wast = wvt_qp_swqe_incw(qp, qp->s_wast);
	/* see wvt_qp_is_avaiw() */
	smp_stowe_wewease(&qp->s_wast, wast);
	if (need_compwetion) {
		stwuct ib_wc w = {
			.ww_id = ww_id,
			.status = status,
			.opcode = opcode,
			.qp = &qp->ibqp,
			.byte_wen = byte_wen,
		};
		wvt_send_cq(qp, &w, status != IB_WC_SUCCESS);
	}
	wetuwn wast;
}

extewn const int  ib_wvt_state_ops[];

stwuct wvt_dev_info;
int wvt_get_wwqe(stwuct wvt_qp *qp, boow ww_id_onwy);
void wvt_comm_est(stwuct wvt_qp *qp);
void wvt_wc_ewwow(stwuct wvt_qp *qp, enum ib_wc_status eww);
unsigned wong wvt_wnw_tbw_to_usec(u32 index);
enum hwtimew_westawt wvt_wc_wnw_wetwy(stwuct hwtimew *t);
void wvt_add_wnw_timew(stwuct wvt_qp *qp, u32 aeth);
void wvt_dew_timews_sync(stwuct wvt_qp *qp);
void wvt_stop_wc_timews(stwuct wvt_qp *qp);
void wvt_add_wetwy_timew_ext(stwuct wvt_qp *qp, u8 shift);
static inwine void wvt_add_wetwy_timew(stwuct wvt_qp *qp)
{
	wvt_add_wetwy_timew_ext(qp, 0);
}

void wvt_copy_sge(stwuct wvt_qp *qp, stwuct wvt_sge_state *ss,
		  void *data, u32 wength,
		  boow wewease, boow copy_wast);
void wvt_send_compwete(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
		       enum ib_wc_status status);
void wvt_wuc_woopback(stwuct wvt_qp *qp);

/**
 * stwuct wvt_qp_itew - the itewatow fow QPs
 * @qp - the cuwwent QP
 *
 * This stwuctuwe defines the cuwwent itewatow
 * state fow sequenced access to aww QPs wewative
 * to an wvt_dev_info.
 */
stwuct wvt_qp_itew {
	stwuct wvt_qp *qp;
	/* pwivate: backpointew */
	stwuct wvt_dev_info *wdi;
	/* pwivate: cawwback woutine */
	void (*cb)(stwuct wvt_qp *qp, u64 v);
	/* pwivate: fow awg to cawwback woutine */
	u64 v;
	/* pwivate: numbew of SMI,GSI QPs fow device */
	int speciaws;
	/* pwivate: cuwwent itewatow index */
	int n;
};

/**
 * ib_cq_taiw - Wetuwn taiw index of cq buffew
 * @send_cq - The cq fow send
 *
 * This is cawwed in qp_itew_pwint to get taiw
 * of cq buffew.
 */
static inwine u32 ib_cq_taiw(stwuct ib_cq *send_cq)
{
	stwuct wvt_cq *cq = ibcq_to_wvtcq(send_cq);

	wetuwn ibcq_to_wvtcq(send_cq)->ip ?
	       WDMA_WEAD_UAPI_ATOMIC(cq->queue->taiw) :
	       ibcq_to_wvtcq(send_cq)->kqueue->taiw;
}

/**
 * ib_cq_head - Wetuwn head index of cq buffew
 * @send_cq - The cq fow send
 *
 * This is cawwed in qp_itew_pwint to get head
 * of cq buffew.
 */
static inwine u32 ib_cq_head(stwuct ib_cq *send_cq)
{
	stwuct wvt_cq *cq = ibcq_to_wvtcq(send_cq);

	wetuwn ibcq_to_wvtcq(send_cq)->ip ?
	       WDMA_WEAD_UAPI_ATOMIC(cq->queue->head) :
	       ibcq_to_wvtcq(send_cq)->kqueue->head;
}

/**
 * wvt_fwee_wq - fwee memowy awwocated fow wvt_wq stwuct
 * @wvt_wq: wequest queue data stwuctuwe
 *
 * This function shouwd onwy be cawwed if the wvt_mmap_info()
 * has not succeeded.
 */
static inwine void wvt_fwee_wq(stwuct wvt_wq *wq)
{
	kvfwee(wq->kwq);
	wq->kwq = NUWW;
	vfwee(wq->wq);
	wq->wq = NUWW;
}

/**
 * wvt_to_ipowt - Get the ibpowt pointew
 * @qp: the qp pointew
 *
 * This function wetuwns the ibpowt pointew fwom the qp pointew.
 */
static inwine stwuct wvt_ibpowt *wvt_to_ipowt(stwuct wvt_qp *qp)
{
	stwuct wvt_dev_info *wdi = ib_to_wvt(qp->ibqp.device);

	wetuwn wdi->powts[qp->powt_num - 1];
}

/**
 * wvt_wc_cwedit_avaiw - Check if thewe awe enough WC cwedits fow the wequest
 * @qp: the qp
 * @wqe: the wequest
 *
 * This function wetuwns fawse when thewe awe not enough cwedits fow the given
 * wequest and twue othewwise.
 */
static inwine boow wvt_wc_cwedit_avaiw(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe)
{
	wockdep_assewt_hewd(&qp->s_wock);
	if (!(qp->s_fwags & WVT_S_UNWIMITED_CWEDIT) &&
	    wvt_cmp_msn(wqe->ssn, qp->s_wsn + 1) > 0) {
		stwuct wvt_ibpowt *wvp = wvt_to_ipowt(qp);

		qp->s_fwags |= WVT_S_WAIT_SSN_CWEDIT;
		wvp->n_wc_cwwaits++;
		wetuwn fawse;
	}
	wetuwn twue;
}

stwuct wvt_qp_itew *wvt_qp_itew_init(stwuct wvt_dev_info *wdi,
				     u64 v,
				     void (*cb)(stwuct wvt_qp *qp, u64 v));
int wvt_qp_itew_next(stwuct wvt_qp_itew *itew);
void wvt_qp_itew(stwuct wvt_dev_info *wdi,
		 u64 v,
		 void (*cb)(stwuct wvt_qp *qp, u64 v));
void wvt_qp_mw_cwean(stwuct wvt_qp *qp, u32 wkey);
#endif          /* DEF_WDMAVT_INCQP_H */
