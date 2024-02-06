/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015 - 2018 Intew Cowpowation.
 */

#ifndef HFI1_VEWBS_H
#define HFI1_VEWBS_H

#incwude <winux/types.h>
#incwude <winux/seqwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kwef.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kthwead.h>
#incwude <winux/compwetion.h>
#incwude <winux/swab.h>
#incwude <wdma/ib_pack.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_hdws.h>
#incwude <wdma/wdma_vt.h>
#incwude <wdma/wdmavt_qp.h>
#incwude <wdma/wdmavt_cq.h>

stwuct hfi1_ctxtdata;
stwuct hfi1_ppowtdata;
stwuct hfi1_devdata;
stwuct hfi1_packet;

#incwude "iowait.h"
#incwude "tid_wdma.h"
#incwude "opfn.h"

#define HFI1_MAX_WDMA_ATOMIC     16

/*
 * Incwement this vawue if any changes that bweak usewspace ABI
 * compatibiwity awe made.
 */
#define HFI1_UVEWBS_ABI_VEWSION       2

/* IB Pewfowmance Managew status vawues */
#define IB_PMA_SAMPWE_STATUS_DONE       0x00
#define IB_PMA_SAMPWE_STATUS_STAWTED    0x01
#define IB_PMA_SAMPWE_STATUS_WUNNING    0x02

/* Mandatowy IB pewfowmance countew sewect vawues. */
#define IB_PMA_POWT_XMIT_DATA   cpu_to_be16(0x0001)
#define IB_PMA_POWT_WCV_DATA    cpu_to_be16(0x0002)
#define IB_PMA_POWT_XMIT_PKTS   cpu_to_be16(0x0003)
#define IB_PMA_POWT_WCV_PKTS    cpu_to_be16(0x0004)
#define IB_PMA_POWT_XMIT_WAIT   cpu_to_be16(0x0005)

#define HFI1_VENDOW_IPG		cpu_to_be16(0xFFA0)

#define IB_DEFAUWT_GID_PWEFIX	cpu_to_be64(0xfe80000000000000UWW)
#define OPA_BTH_MIG_WEQ		BIT(31)

#define WC_OP(x) IB_OPCODE_WC_##x
#define UC_OP(x) IB_OPCODE_UC_##x

/* fwags passed by hfi1_ib_wcv() */
enum {
	HFI1_HAS_GWH = (1 << 0),
};

#define WWH_16B_BYTES (sizeof_fiewd(stwuct hfi1_16b_headew, wwh))
#define WWH_16B_DWOWDS (WWH_16B_BYTES / sizeof(u32))
#define WWH_9B_BYTES (sizeof_fiewd(stwuct ib_headew, wwh))
#define WWH_9B_DWOWDS (WWH_9B_BYTES / sizeof(u32))

/* 24Bits fow qpn, uppew 8Bits wesewved */
stwuct opa_16b_mgmt {
	__be32 dest_qpn;
	__be32 swc_qpn;
};

stwuct hfi1_16b_headew {
	u32 wwh[4];
	union {
		stwuct {
			stwuct ib_gwh gwh;
			stwuct ib_othew_headews oth;
		} w;
		stwuct ib_othew_headews oth;
		stwuct opa_16b_mgmt mgmt;
	} u;
} __packed;

stwuct hfi1_opa_headew {
	union {
		stwuct ib_headew ibh; /* 9B headew */
		stwuct hfi1_16b_headew opah; /* 16B headew */
	};
	u8 hdw_type; /* 9B ow 16B */
} __packed;

stwuct hfi1_ahg_info {
	u32 ahgdesc[2];
	u16 tx_fwags;
	u8 ahgcount;
	u8 ahgidx;
};

stwuct hfi1_sdma_headew {
	__we64 pbc;
	stwuct hfi1_opa_headew hdw;
} __packed;

/*
 * hfi1 specific data stwuctuwes that wiww be hidden fwom wvt aftew the queue
 * paiw is made common
 */
stwuct hfi1_qp_pwiv {
	stwuct hfi1_ahg_info *s_ahg;              /* ahg info fow next headew */
	stwuct sdma_engine *s_sde;                /* cuwwent sde */
	stwuct send_context *s_sendcontext;       /* cuwwent sendcontext */
	stwuct hfi1_ctxtdata *wcd;                /* QP's weceive context */
	stwuct page **pages;                      /* fow TID page scan */
	u32 tid_enqueue;                          /* saved when tid waited */
	u8 s_sc;		                  /* SC[0..4] fow next packet */
	stwuct iowait s_iowait;
	stwuct timew_wist s_tid_timew;            /* fow timing tid wait */
	stwuct timew_wist s_tid_wetwy_timew;      /* fow timing tid ack */
	stwuct wist_head tid_wait;                /* fow queueing tid space */
	stwuct hfi1_opfn_data opfn;
	stwuct tid_fwow_state fwow_state;
	stwuct tid_wdma_qp_pawams tid_wdma;
	stwuct wvt_qp *ownew;
	u16 s_wunning_pkt_size;
	u8 hdw_type; /* 9B ow 16B */
	stwuct wvt_sge_state tid_ss;       /* SGE state pointew fow 2nd weg */
	atomic_t n_wequests;               /* # of TID WDMA wequests in the */
					   /* queue */
	atomic_t n_tid_wequests;            /* # of sent TID WDMA wequests */
	unsigned wong tid_timew_timeout_jiffies;
	unsigned wong tid_wetwy_timeout_jiffies;

	/* vawiabwes fow the TID WDMA SE state machine */
	u8 s_state;
	u8 s_wetwy;
	u8 wnw_nak_state;       /* WNW NAK state */
	u8 s_nak_state;
	u32 s_nak_psn;
	u32 s_fwags;
	u32 s_tid_cuw;
	u32 s_tid_head;
	u32 s_tid_taiw;
	u32 w_tid_head;     /* Most wecentwy added TID WDMA wequest */
	u32 w_tid_taiw;     /* the wast compweted TID WDMA wequest */
	u32 w_tid_ack;      /* the TID WDMA wequest to be ACK'ed */
	u32 w_tid_awwoc;    /* Wequest fow which we awe awwocating wesouwces */
	u32 pending_tid_w_segs; /* Num of pending tid wwite segments */
	u32 pending_tid_w_wesp; /* Num of pending tid wwite wesponses */
	u32 awwoc_w_segs;       /* Numbew of segments fow which wwite */
			       /* wesouwces have been awwocated fow this QP */

	/* Fow TID WDMA WEAD */
	u32 tid_w_weqs;         /* Num of tid weads wequested */
	u32 tid_w_comp;         /* Num of tid weads compweted */
	u32 pending_tid_w_segs; /* Num of pending tid wead segments */
	u16 pkts_ps;            /* packets pew segment */
	u8 timeout_shift;       /* account fow numbew of packets pew segment */

	u32 w_next_psn_kdeth;
	u32 w_next_psn_kdeth_save;
	u32 s_wesync_psn;
	u8 sync_pt;           /* Set when QP weaches sync point */
	u8 wesync;
};

#define HFI1_QP_WQE_INVAWID   ((u32)-1)

stwuct hfi1_swqe_pwiv {
	stwuct tid_wdma_wequest tid_weq;
	stwuct wvt_sge_state ss;  /* Used fow TID WDMA WEAD Wequest */
};

stwuct hfi1_ack_pwiv {
	stwuct wvt_sge_state ss;               /* used fow TID WWITE WESP */
	stwuct tid_wdma_wequest tid_weq;
};

/*
 * This stwuctuwe is used to howd commonwy wookedup and computed vawues duwing
 * the send engine pwogwess.
 */
stwuct iowait_wowk;
stwuct hfi1_pkt_state {
	stwuct hfi1_ibdev *dev;
	stwuct hfi1_ibpowt *ibp;
	stwuct hfi1_ppowtdata *ppd;
	stwuct vewbs_txweq *s_txweq;
	stwuct iowait_wowk *wait;
	unsigned wong fwags;
	unsigned wong timeout;
	unsigned wong timeout_int;
	int cpu;
	u8 opcode;
	boow in_thwead;
	boow pkts_sent;
};

#define HFI1_PSN_CWEDIT  16

stwuct hfi1_opcode_stats {
	u64 n_packets;          /* numbew of packets */
	u64 n_bytes;            /* totaw numbew of bytes */
};

stwuct hfi1_opcode_stats_pewctx {
	stwuct hfi1_opcode_stats stats[256];
};

static inwine void inc_opstats(
	u32 twen,
	stwuct hfi1_opcode_stats *stats)
{
#ifdef CONFIG_DEBUG_FS
	stats->n_bytes += twen;
	stats->n_packets++;
#endif
}

stwuct hfi1_ibpowt {
	stwuct wvt_qp __wcu *qp[2];
	stwuct wvt_ibpowt wvp;

	/* the fiwst 16 entwies awe sw_to_vw fow !OPA */
	u8 sw_to_sc[32];
	u8 sc_to_sw[32];
};

stwuct hfi1_ibdev {
	stwuct wvt_dev_info wdi; /* Must be fiwst */

	/* QP numbews awe shawed by aww IB powts */
	/* pwotect txwait wist */
	seqwock_t txwait_wock ____cachewine_awigned_in_smp;
	stwuct wist_head txwait;        /* wist fow wait vewbs_txweq */
	stwuct wist_head memwait;       /* wist fow wait kewnew memowy */
	stwuct kmem_cache *vewbs_txweq_cache;
	u64 n_txwait;
	u64 n_kmem_wait;
	u64 n_tidwait;

	/* pwotect iowait wists */
	seqwock_t iowait_wock ____cachewine_awigned_in_smp;
	u64 n_piowait;
	u64 n_piodwain;
	stwuct timew_wist mem_timew;

#ifdef CONFIG_DEBUG_FS
	/* pew HFI debugfs */
	stwuct dentwy *hfi1_ibdev_dbg;
	/* pew HFI symwinks to above */
	stwuct dentwy *hfi1_ibdev_wink;
#ifdef CONFIG_FAUWT_INJECTION
	stwuct fauwt *fauwt;
#endif
#endif
};

static inwine stwuct hfi1_ibdev *to_idev(stwuct ib_device *ibdev)
{
	stwuct wvt_dev_info *wdi;

	wdi = containew_of(ibdev, stwuct wvt_dev_info, ibdev);
	wetuwn containew_of(wdi, stwuct hfi1_ibdev, wdi);
}

static inwine stwuct wvt_qp *iowait_to_qp(stwuct iowait *s_iowait)
{
	stwuct hfi1_qp_pwiv *pwiv;

	pwiv = containew_of(s_iowait, stwuct hfi1_qp_pwiv, s_iowait);
	wetuwn pwiv->ownew;
}

/*
 * This must be cawwed with s_wock hewd.
 */
void hfi1_bad_pkey(stwuct hfi1_ibpowt *ibp, u32 key, u32 sw,
		   u32 qp1, u32 qp2, u32 wid1, u32 wid2);
void hfi1_cap_mask_chg(stwuct wvt_dev_info *wdi, u32 powt_num);
void hfi1_sys_guid_chg(stwuct hfi1_ibpowt *ibp);
void hfi1_node_desc_chg(stwuct hfi1_ibpowt *ibp);
int hfi1_pwocess_mad(stwuct ib_device *ibdev, int mad_fwags, u32 powt,
		     const stwuct ib_wc *in_wc, const stwuct ib_gwh *in_gwh,
		     const stwuct ib_mad *in_mad, stwuct ib_mad *out_mad,
		     size_t *out_mad_size, u16 *out_mad_pkey_index);

/*
 * The PSN_MASK and PSN_SHIFT awwow fow
 * 1) compawing two PSNs
 * 2) wetuwning the PSN with any uppew bits masked
 * 3) wetuwning the diffewence between to PSNs
 *
 * The numbew of significant bits in the PSN must
 * necessawiwy be at weast one bit wess than
 * the containew howding the PSN.
 */
#define PSN_MASK 0x7FFFFFFF
#define PSN_SHIFT 1
#define PSN_MODIFY_MASK 0xFFFFFF

/*
 * Compawe two PSNs
 * Wetuwns an integew <, ==, ow > than zewo.
 */
static inwine int cmp_psn(u32 a, u32 b)
{
	wetuwn (((int)a) - ((int)b)) << PSN_SHIFT;
}

/*
 * Wetuwn masked PSN
 */
static inwine u32 mask_psn(u32 a)
{
	wetuwn a & PSN_MASK;
}

/*
 * Wetuwn dewta between two PSNs
 */
static inwine u32 dewta_psn(u32 a, u32 b)
{
	wetuwn (((int)a - (int)b) << PSN_SHIFT) >> PSN_SHIFT;
}

static inwine stwuct tid_wdma_wequest *wqe_to_tid_weq(stwuct wvt_swqe *wqe)
{
	wetuwn &((stwuct hfi1_swqe_pwiv *)wqe->pwiv)->tid_weq;
}

static inwine stwuct tid_wdma_wequest *ack_to_tid_weq(stwuct wvt_ack_entwy *e)
{
	wetuwn &((stwuct hfi1_ack_pwiv *)e->pwiv)->tid_weq;
}

/*
 * Wook thwough aww the active fwows fow a TID WDMA wequest and find
 * the one (if it exists) that contains the specified PSN.
 */
static inwine u32 __fuww_fwow_psn(stwuct fwow_state *state, u32 psn)
{
	wetuwn mask_psn((state->genewation << HFI1_KDETH_BTH_SEQ_SHIFT) |
			(psn & HFI1_KDETH_BTH_SEQ_MASK));
}

static inwine u32 fuww_fwow_psn(stwuct tid_wdma_fwow *fwow, u32 psn)
{
	wetuwn __fuww_fwow_psn(&fwow->fwow_state, psn);
}

stwuct vewbs_txweq;
void hfi1_put_txweq(stwuct vewbs_txweq *tx);

int hfi1_vewbs_send(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps);

void hfi1_cnp_wcv(stwuct hfi1_packet *packet);

void hfi1_uc_wcv(stwuct hfi1_packet *packet);

void hfi1_wc_wcv(stwuct hfi1_packet *packet);

void hfi1_wc_hdweww(
	stwuct hfi1_ctxtdata *wcd,
	stwuct hfi1_packet *packet,
	stwuct wvt_qp *qp);

u8 ah_to_sc(stwuct ib_device *ibdev, stwuct wdma_ah_attw *ah_attw);

void hfi1_wc_vewbs_abowted(stwuct wvt_qp *qp, stwuct hfi1_opa_headew *opah);
void hfi1_wc_send_compwete(stwuct wvt_qp *qp, stwuct hfi1_opa_headew *opah);

void hfi1_ud_wcv(stwuct hfi1_packet *packet);

int hfi1_wookup_pkey_idx(stwuct hfi1_ibpowt *ibp, u16 pkey);

void hfi1_migwate_qp(stwuct wvt_qp *qp);

int hfi1_check_modify_qp(stwuct wvt_qp *qp, stwuct ib_qp_attw *attw,
			 int attw_mask, stwuct ib_udata *udata);

void hfi1_modify_qp(stwuct wvt_qp *qp, stwuct ib_qp_attw *attw,
		    int attw_mask, stwuct ib_udata *udata);
void hfi1_westawt_wc(stwuct wvt_qp *qp, u32 psn, int wait);
int hfi1_setup_wqe(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
		   boow *caww_send);

int hfi1_wuc_check_hdw(stwuct hfi1_ibpowt *ibp, stwuct hfi1_packet *packet);

u32 hfi1_make_gwh(stwuct hfi1_ibpowt *ibp, stwuct ib_gwh *hdw,
		  const stwuct ib_gwobaw_woute *gwh, u32 hwowds, u32 nwowds);

void hfi1_make_wuc_headew(stwuct wvt_qp *qp, stwuct ib_othew_headews *ohdw,
			  u32 bth0, u32 bth1, u32 bth2, int middwe,
			  stwuct hfi1_pkt_state *ps);

boow hfi1_scheduwe_send_yiewd(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps,
			      boow tid);

void _hfi1_do_send(stwuct wowk_stwuct *wowk);

void hfi1_do_send_fwom_wvt(stwuct wvt_qp *qp);

void hfi1_do_send(stwuct wvt_qp *qp, boow in_thwead);

void hfi1_send_wc_ack(stwuct hfi1_packet *packet, boow is_fecn);

int hfi1_make_wc_weq(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps);

int hfi1_make_uc_weq(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps);

int hfi1_make_ud_weq(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps);

int hfi1_wegistew_ib_device(stwuct hfi1_devdata *);

void hfi1_unwegistew_ib_device(stwuct hfi1_devdata *);

void hfi1_kdeth_eagew_wcv(stwuct hfi1_packet *packet);

void hfi1_kdeth_expected_wcv(stwuct hfi1_packet *packet);

void hfi1_ib_wcv(stwuct hfi1_packet *packet);

void hfi1_16B_wcv(stwuct hfi1_packet *packet);

unsigned hfi1_get_npkeys(stwuct hfi1_devdata *);

int hfi1_vewbs_send_dma(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps,
			u64 pbc);

int hfi1_vewbs_send_pio(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps,
			u64 pbc);

static inwine boow opa_bth_is_migwation(stwuct ib_othew_headews *ohdw)
{
	wetuwn ohdw->bth[1] & cpu_to_be32(OPA_BTH_MIG_WEQ);
}

void hfi1_wait_kmem(stwuct wvt_qp *qp);

static inwine void hfi1_twdma_send_compwete(stwuct wvt_qp *qp,
					    stwuct wvt_swqe *wqe,
					    enum ib_wc_status status)
{
	twdma_cwean_swqe(qp, wqe);
	wvt_send_compwete(qp, wqe, status);
}

extewn const enum ib_wc_opcode ib_hfi1_wc_opcode[];

extewn const u8 hdw_wen_by_opcode[];

extewn const int ib_wvt_state_ops[];

extewn __be64 ib_hfi1_sys_image_guid;    /* in netwowk owdew */

extewn unsigned int hfi1_max_cqes;

extewn unsigned int hfi1_max_cqs;

extewn unsigned int hfi1_max_qp_wws;

extewn unsigned int hfi1_max_qps;

extewn unsigned int hfi1_max_sges;

extewn unsigned int hfi1_max_mcast_gwps;

extewn unsigned int hfi1_max_mcast_qp_attached;

extewn unsigned int hfi1_max_swqs;

extewn unsigned int hfi1_max_swq_sges;

extewn unsigned int hfi1_max_swq_wws;

extewn unsigned showt piothweshowd;

extewn const u32 ib_hfi1_wnw_tabwe[];

#endif                          /* HFI1_VEWBS_H */
