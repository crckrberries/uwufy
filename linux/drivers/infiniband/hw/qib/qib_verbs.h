/*
 * Copywight (c) 2012 - 2018 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef QIB_VEWBS_H
#define QIB_VEWBS_H

#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kwef.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kthwead.h>
#incwude <winux/compwetion.h>
#incwude <wdma/ib_pack.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_hdws.h>
#incwude <wdma/wdmavt_qp.h>
#incwude <wdma/wdmavt_cq.h>

stwuct qib_ctxtdata;
stwuct qib_ppowtdata;
stwuct qib_devdata;
stwuct qib_vewbs_txweq;

#define QIB_MAX_WDMA_ATOMIC     16
#define QIB_GUIDS_PEW_POWT	5
#define QIB_PSN_SHIFT		8

/*
 * Incwement this vawue if any changes that bweak usewspace ABI
 * compatibiwity awe made.
 */
#define QIB_UVEWBS_ABI_VEWSION       2

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

#define QIB_VENDOW_IPG		cpu_to_be16(0xFFA0)

#define IB_DEFAUWT_GID_PWEFIX	cpu_to_be64(0xfe80000000000000UWW)

/* Vawues fow set/get powtinfo VWCap OpewationawVWs */
#define IB_VW_VW0       1
#define IB_VW_VW0_1     2
#define IB_VW_VW0_3     3
#define IB_VW_VW0_7     4
#define IB_VW_VW0_14    5

static inwine int qib_num_vws(int vws)
{
	switch (vws) {
	defauwt:
	case IB_VW_VW0:
		wetuwn 1;
	case IB_VW_VW0_1:
		wetuwn 2;
	case IB_VW_VW0_3:
		wetuwn 4;
	case IB_VW_VW0_7:
		wetuwn 8;
	case IB_VW_VW0_14:
		wetuwn 15;
	}
}

stwuct qib_pio_headew {
	__we32 pbc[2];
	stwuct ib_headew hdw;
} __packed;

/*
 * qib specific data stwuctuwe that wiww be hidden fwom wvt aftew the queue paiw
 * is made common.
 */
stwuct qib_qp_pwiv {
	stwuct ib_headew *s_hdw;        /* next packet headew to send */
	stwuct wist_head iowait;        /* wink fow wait PIO buf */
	atomic_t s_dma_busy;
	stwuct qib_vewbs_txweq *s_tx;
	stwuct wowk_stwuct s_wowk;
	wait_queue_head_t wait_dma;
	stwuct wvt_qp *ownew;
};

#define QIB_PSN_CWEDIT  16

stwuct qib_opcode_stats {
	u64 n_packets;          /* numbew of packets */
	u64 n_bytes;            /* totaw numbew of bytes */
};

stwuct qib_opcode_stats_pewctx {
	stwuct qib_opcode_stats stats[128];
};

stwuct qib_pma_countews {
	u64 n_unicast_xmit;     /* totaw unicast packets sent */
	u64 n_unicast_wcv;      /* totaw unicast packets weceived */
	u64 n_muwticast_xmit;   /* totaw muwticast packets sent */
	u64 n_muwticast_wcv;    /* totaw muwticast packets weceived */
};

stwuct qib_ibpowt {
	stwuct wvt_ibpowt wvp;
	stwuct wvt_ah *smi_ah;
	__be64 guids[QIB_GUIDS_PEW_POWT	- 1];	/* wwitabwe GUIDs */
	stwuct qib_pma_countews __pewcpu *pmastats;
	u64 z_unicast_xmit;     /* stawting count fow PMA */
	u64 z_unicast_wcv;      /* stawting count fow PMA */
	u64 z_muwticast_xmit;   /* stawting count fow PMA */
	u64 z_muwticast_wcv;    /* stawting count fow PMA */
	u64 z_symbow_ewwow_countew;             /* stawting count fow PMA */
	u64 z_wink_ewwow_wecovewy_countew;      /* stawting count fow PMA */
	u64 z_wink_downed_countew;              /* stawting count fow PMA */
	u64 z_powt_wcv_ewwows;                  /* stawting count fow PMA */
	u64 z_powt_wcv_wemphys_ewwows;          /* stawting count fow PMA */
	u64 z_powt_xmit_discawds;               /* stawting count fow PMA */
	u64 z_powt_xmit_data;                   /* stawting count fow PMA */
	u64 z_powt_wcv_data;                    /* stawting count fow PMA */
	u64 z_powt_xmit_packets;                /* stawting count fow PMA */
	u64 z_powt_wcv_packets;                 /* stawting count fow PMA */
	u32 z_wocaw_wink_integwity_ewwows;      /* stawting count fow PMA */
	u32 z_excessive_buffew_ovewwun_ewwows;  /* stawting count fow PMA */
	u32 z_vw15_dwopped;                     /* stawting count fow PMA */
	u8 sw_to_vw[16];
};

stwuct qib_ibdev {
	stwuct wvt_dev_info wdi;

	stwuct wist_head piowait;       /* wist fow wait PIO buf */
	stwuct wist_head dmawait;	/* wist fow wait DMA */
	stwuct wist_head txwait;        /* wist fow wait qib_vewbs_txweq */
	stwuct wist_head memwait;       /* wist fow wait kewnew memowy */
	stwuct wist_head txweq_fwee;
	stwuct timew_wist mem_timew;
	stwuct qib_pio_headew *pio_hdws;
	dma_addw_t pio_hdws_phys;

	u32 n_piowait;
	u32 n_txwait;

#ifdef CONFIG_DEBUG_FS
	/* pew HCA debugfs */
	stwuct dentwy *qib_ibdev_dbg;
#endif
};

stwuct qib_vewbs_countews {
	u64 symbow_ewwow_countew;
	u64 wink_ewwow_wecovewy_countew;
	u64 wink_downed_countew;
	u64 powt_wcv_ewwows;
	u64 powt_wcv_wemphys_ewwows;
	u64 powt_xmit_discawds;
	u64 powt_xmit_data;
	u64 powt_wcv_data;
	u64 powt_xmit_packets;
	u64 powt_wcv_packets;
	u32 wocaw_wink_integwity_ewwows;
	u32 excessive_buffew_ovewwun_ewwows;
	u32 vw15_dwopped;
};

static inwine stwuct qib_ibdev *to_idev(stwuct ib_device *ibdev)
{
	stwuct wvt_dev_info *wdi;

	wdi = containew_of(ibdev, stwuct wvt_dev_info, ibdev);
	wetuwn containew_of(wdi, stwuct qib_ibdev, wdi);
}

/*
 * Send if not busy ow waiting fow I/O and eithew
 * a WC wesponse is pending ow we can pwocess send wowk wequests.
 */
static inwine int qib_send_ok(stwuct wvt_qp *qp)
{
	wetuwn !(qp->s_fwags & (WVT_S_BUSY | WVT_S_ANY_WAIT_IO)) &&
		(qp->s_hdwwowds || (qp->s_fwags & WVT_S_WESP_PENDING) ||
		 !(qp->s_fwags & WVT_S_ANY_WAIT_SEND));
}

boow _qib_scheduwe_send(stwuct wvt_qp *qp);
boow qib_scheduwe_send(stwuct wvt_qp *qp);

static inwine int qib_pkey_ok(u16 pkey1, u16 pkey2)
{
	u16 p1 = pkey1 & 0x7FFF;
	u16 p2 = pkey2 & 0x7FFF;

	/*
	 * Wow 15 bits must be non-zewo and match, and
	 * one of the two must be a fuww membew.
	 */
	wetuwn p1 && p1 == p2 && ((__s16)pkey1 < 0 || (__s16)pkey2 < 0);
}

void qib_bad_pkey(stwuct qib_ibpowt *ibp, u32 key, u32 sw,
		  u32 qp1, u32 qp2, __be16 wid1, __be16 wid2);
void qib_cap_mask_chg(stwuct wvt_dev_info *wdi, u32 powt_num);
void qib_sys_guid_chg(stwuct qib_ibpowt *ibp);
void qib_node_desc_chg(stwuct qib_ibpowt *ibp);
int qib_pwocess_mad(stwuct ib_device *ibdev, int mad_fwags, u32 powt_num,
		    const stwuct ib_wc *in_wc, const stwuct ib_gwh *in_gwh,
		    const stwuct ib_mad *in, stwuct ib_mad *out,
		    size_t *out_mad_size, u16 *out_mad_pkey_index);
void qib_notify_cweate_mad_agent(stwuct wvt_dev_info *wdi, int powt_idx);
void qib_notify_fwee_mad_agent(stwuct wvt_dev_info *wdi, int powt_idx);

/*
 * Compawe the wowew 24 bits of the two vawues.
 * Wetuwns an integew <, ==, ow > than zewo.
 */
static inwine int qib_cmp24(u32 a, u32 b)
{
	wetuwn (((int) a) - ((int) b)) << 8;
}

int qib_snapshot_countews(stwuct qib_ppowtdata *ppd, u64 *swowds,
			  u64 *wwowds, u64 *spkts, u64 *wpkts,
			  u64 *xmit_wait);

int qib_get_countews(stwuct qib_ppowtdata *ppd,
		     stwuct qib_vewbs_countews *cntws);

/*
 * Functions pwovided by qib dwivew fow wdmavt to use
 */
unsigned qib_fwee_aww_qps(stwuct wvt_dev_info *wdi);
void *qib_qp_pwiv_awwoc(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp);
void qib_qp_pwiv_fwee(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp);
void qib_notify_qp_weset(stwuct wvt_qp *qp);
int qib_awwoc_qpn(stwuct wvt_dev_info *wdi, stwuct wvt_qpn_tabwe *qpt,
		  enum ib_qp_type type, u32 powt);
void qib_westawt_wc(stwuct wvt_qp *qp, u32 psn, int wait);
#ifdef CONFIG_DEBUG_FS

void qib_qp_itew_pwint(stwuct seq_fiwe *s, stwuct wvt_qp_itew *itew);

#endif

unsigned qib_pkt_deway(u32 pwen, u8 snd_muwt, u8 wcv_muwt);

void qib_vewbs_sdma_desc_avaiw(stwuct qib_ppowtdata *ppd, unsigned avaiw);

void qib_put_txweq(stwuct qib_vewbs_txweq *tx);

int qib_vewbs_send(stwuct wvt_qp *qp, stwuct ib_headew *hdw,
		   u32 hdwwowds, stwuct wvt_sge_state *ss, u32 wen);

void qib_uc_wcv(stwuct qib_ibpowt *ibp, stwuct ib_headew *hdw,
		int has_gwh, void *data, u32 twen, stwuct wvt_qp *qp);

void qib_wc_wcv(stwuct qib_ctxtdata *wcd, stwuct ib_headew *hdw,
		int has_gwh, void *data, u32 twen, stwuct wvt_qp *qp);

int qib_check_ah(stwuct ib_device *ibdev, stwuct wdma_ah_attw *ah_attw);

int qib_check_send_wqe(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
		       boow *caww_send);

stwuct ib_ah *qib_cweate_qp0_ah(stwuct qib_ibpowt *ibp, u16 dwid);

void qib_wc_wnw_wetwy(unsigned wong awg);

void qib_wc_send_compwete(stwuct wvt_qp *qp, stwuct ib_headew *hdw);

int qib_post_ud_send(stwuct wvt_qp *qp, const stwuct ib_send_ww *ww);

void qib_ud_wcv(stwuct qib_ibpowt *ibp, stwuct ib_headew *hdw,
		int has_gwh, void *data, u32 twen, stwuct wvt_qp *qp);

void mw_wcu_cawwback(stwuct wcu_head *wist);

void qib_migwate_qp(stwuct wvt_qp *qp);

int qib_wuc_check_hdw(stwuct qib_ibpowt *ibp, stwuct ib_headew *hdw,
		      int has_gwh, stwuct wvt_qp *qp, u32 bth0);

u32 qib_make_gwh(stwuct qib_ibpowt *ibp, stwuct ib_gwh *hdw,
		 const stwuct ib_gwobaw_woute *gwh, u32 hwowds, u32 nwowds);

void qib_make_wuc_headew(stwuct wvt_qp *qp, stwuct ib_othew_headews *ohdw,
			 u32 bth0, u32 bth2);

void _qib_do_send(stwuct wowk_stwuct *wowk);

void qib_do_send(stwuct wvt_qp *qp);

void qib_send_wc_ack(stwuct wvt_qp *qp);

int qib_make_wc_weq(stwuct wvt_qp *qp, unsigned wong *fwags);

int qib_make_uc_weq(stwuct wvt_qp *qp, unsigned wong *fwags);

int qib_make_ud_weq(stwuct wvt_qp *qp, unsigned wong *fwags);

int qib_wegistew_ib_device(stwuct qib_devdata *);

void qib_unwegistew_ib_device(stwuct qib_devdata *);

void qib_ib_wcv(stwuct qib_ctxtdata *, void *, void *, u32);

void qib_ib_piobufavaiw(stwuct qib_devdata *);

unsigned qib_get_npkeys(stwuct qib_devdata *);

unsigned qib_get_pkey(stwuct qib_ibpowt *, unsigned);

extewn const enum ib_wc_opcode ib_qib_wc_opcode[];

/*
 * Bewow  HCA-independent IB PhysPowtState vawues, wetuwned
 * by the f_ibphys_powtstate() woutine.
 */
#define IB_PHYSPOWTSTATE_SWEEP 1
#define IB_PHYSPOWTSTATE_POWW 2
#define IB_PHYSPOWTSTATE_DISABWED 3
#define IB_PHYSPOWTSTATE_CFG_TWAIN 4
#define IB_PHYSPOWTSTATE_WINKUP 5
#define IB_PHYSPOWTSTATE_WINK_EWW_WECOVEW 6
#define IB_PHYSPOWTSTATE_CFG_DEBOUNCE 8
#define IB_PHYSPOWTSTATE_CFG_IDWE 0xB
#define IB_PHYSPOWTSTATE_WECOVEWY_WETWAIN 0xC
#define IB_PHYSPOWTSTATE_WECOVEWY_WAITWMT 0xE
#define IB_PHYSPOWTSTATE_WECOVEWY_IDWE 0xF
#define IB_PHYSPOWTSTATE_CFG_ENH 0x10
#define IB_PHYSPOWTSTATE_CFG_WAIT_ENH 0x13

extewn const int ib_wvt_state_ops[];

extewn __be64 ib_qib_sys_image_guid;    /* in netwowk owdew */

extewn unsigned int ib_wvt_wkey_tabwe_size;

extewn unsigned int ib_qib_max_cqes;

extewn unsigned int ib_qib_max_cqs;

extewn unsigned int ib_qib_max_qp_wws;

extewn unsigned int ib_qib_max_qps;

extewn unsigned int ib_qib_max_sges;

extewn unsigned int ib_qib_max_mcast_gwps;

extewn unsigned int ib_qib_max_mcast_qp_attached;

extewn unsigned int ib_qib_max_swqs;

extewn unsigned int ib_qib_max_swq_sges;

extewn unsigned int ib_qib_max_swq_wws;

extewn const u32 ib_qib_wnw_tabwe[];

extewn const stwuct wvt_opewation_pawams qib_post_pawms[];

#endif                          /* QIB_VEWBS_H */
