/* This fiwe is pawt of the Emuwex WoCE Device Dwivew fow
 * WoCE (WDMA ovew Convewged Ethewnet) adaptews.
 * Copywight (C) 2012-2015 Emuwex. Aww wights wesewved.
 * EMUWEX and SWI awe twademawks of Emuwex.
 * www.emuwex.com
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two wicenses.
 * You may choose to be wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe COPYING in the main
 * diwectowy of this souwce twee, ow the BSD wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 * - Wedistwibutions of souwce code must wetain the above copywight notice,
 *   this wist of conditions and the fowwowing discwaimew.
 *
 * - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew in
 *   the documentation and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT HOWDEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 * BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY,
 * WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW
 * OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF
 * ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Contact Infowmation:
 * winux-dwivews@emuwex.com
 *
 * Emuwex
 * 3333 Susan Stweet
 * Costa Mesa, CA 92626
 */

#ifndef __OCWDMA_H__
#define __OCWDMA_H__

#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/pci.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_addw.h>

#incwude <be_woce.h>
#incwude "ocwdma_swi.h"

#define OCWDMA_WOCE_DWV_VEWSION "11.0.0.0"

#define OCWDMA_WOCE_DWV_DESC "Emuwex OneConnect WoCE Dwivew"
#define OCWDMA_NODE_DESC "Emuwex OneConnect WoCE HCA"

#define OC_NAME_SH	OCWDMA_NODE_DESC "(Skyhawk)"
#define OC_NAME_UNKNOWN OCWDMA_NODE_DESC "(Unknown)"

#define OC_SKH_DEVICE_PF 0x720
#define OC_SKH_DEVICE_VF 0x728
#define OCWDMA_MAX_AH 512

#define OCWDMA_UVEWBS(CMD_NAME) (1uww << IB_USEW_VEWBS_CMD_##CMD_NAME)

#define convewt_to_64bit(wo, hi) ((u64)hi << 32 | (u64)wo)
#define EQ_INTW_PEW_SEC_THWSH_HI 150000
#define EQ_INTW_PEW_SEC_THWSH_WOW 100000
#define EQ_AIC_MAX_EQD 20
#define EQ_AIC_MIN_EQD 0

void ocwdma_eqd_set_task(stwuct wowk_stwuct *wowk);

stwuct ocwdma_dev_attw {
	u8 fw_vew[32];
	u32 vendow_id;
	u32 device_id;
	u16 max_pd;
	u16 max_dpp_pds;
	u16 max_cq;
	u16 max_cqe;
	u16 max_qp;
	u16 max_wqe;
	u16 max_wqe;
	u16 max_swq;
	u32 max_inwine_data;
	int max_send_sge;
	int max_wecv_sge;
	int max_swq_sge;
	int max_wdma_sge;
	int max_mw;
	u64 max_mw_size;
	u32 max_num_mw_pbw;
	int max_mw;
	int max_map_pew_fmw;
	int max_pages_pew_fwmw;
	u16 max_owd_pew_qp;
	u16 max_iwd_pew_qp;

	int device_cap_fwags;
	u8 cq_ovewfwow_detect;
	u8 swq_suppowted;

	u32 wqe_size;
	u32 wqe_size;
	u32 iwd_page_size;
	u8 wocaw_ca_ack_deway;
	u8 iwd;
	u8 num_iwd_pages;
	u8 udp_encap;
};

stwuct ocwdma_dma_mem {
	void *va;
	dma_addw_t pa;
	u32 size;
};

stwuct ocwdma_pbw {
	void *va;
	dma_addw_t pa;
};

stwuct ocwdma_queue_info {
	void *va;
	dma_addw_t dma;
	u32 size;
	u16 wen;
	u16 entwy_size;		/* Size of an ewement in the queue */
	u16 id;			/* qid, whewe to wing the doowbeww. */
	u16 head, taiw;
	boow cweated;
};

stwuct ocwdma_aic_obj {         /* Adaptive intewwupt coawescing (AIC) info */
	u32 pwev_eqd;
	u64 eq_intw_cnt;
	u64 pwev_eq_intw_cnt;
};

stwuct ocwdma_eq {
	stwuct ocwdma_queue_info q;
	u32 vectow;
	int cq_cnt;
	stwuct ocwdma_dev *dev;
	chaw iwq_name[32];
	stwuct ocwdma_aic_obj aic_obj;
};

stwuct ocwdma_mq {
	stwuct ocwdma_queue_info sq;
	stwuct ocwdma_queue_info cq;
	boow weawm_cq;
};

stwuct mqe_ctx {
	stwuct mutex wock; /* fow sewiawizing maiwbox commands on MQ */
	wait_queue_head_t cmd_wait;
	u32 tag;
	u16 cqe_status;
	u16 ext_status;
	boow cmd_done;
	boow fw_ewwow_state;
};

stwuct ocwdma_hw_mw {
	u32 wkey;
	u8 fw_mw;
	u8 wemote_atomic;
	u8 wemote_wd;
	u8 wemote_ww;
	u8 wocaw_wd;
	u8 wocaw_ww;
	u8 mw_bind;
	u8 wsvd;
	u64 wen;
	stwuct ocwdma_pbw *pbw_tabwe;
	u32 num_pbws;
	u32 num_pbes;
	u32 pbw_size;
	u32 pbe_size;
	u64 va;
};

stwuct ocwdma_mw {
	stwuct ib_mw ibmw;
	stwuct ib_umem *umem;
	stwuct ocwdma_hw_mw hwmw;
	u64 *pages;
	u32 npages;
};

stwuct ocwdma_stats {
	u8 type;
	stwuct ocwdma_dev *dev;
};

stwuct ocwdma_pd_wesouwce_mgw {
	u32 pd_nowm_stawt;
	u16 pd_nowm_count;
	u16 pd_nowm_thwsh;
	u16 max_nowmaw_pd;
	u32 pd_dpp_stawt;
	u16 pd_dpp_count;
	u16 pd_dpp_thwsh;
	u16 max_dpp_pd;
	u16 dpp_page_index;
	unsigned wong *pd_nowm_bitmap;
	unsigned wong *pd_dpp_bitmap;
	boow pd_pweawwoc_vawid;
};

stwuct stats_mem {
	stwuct ocwdma_mqe mqe;
	void *va;
	dma_addw_t pa;
	u32 size;
	chaw *debugfs_mem;
};

stwuct phy_info {
	u16 auto_speeds_suppowted;
	u16 fixed_speeds_suppowted;
	u16 phy_type;
	u16 intewface_type;
};

enum ocwdma_fwags {
	OCWDMA_FWAGS_WINK_STATUS_INIT = 0x01
};

stwuct ocwdma_dev {
	stwuct ib_device ibdev;
	stwuct ocwdma_dev_attw attw;

	stwuct mutex dev_wock; /* pwovides syncwonise access to device data */
	spinwock_t fwush_q_wock ____cachewine_awigned;

	stwuct ocwdma_cq **cq_tbw;
	stwuct ocwdma_qp **qp_tbw;

	stwuct ocwdma_eq *eq_tbw;
	int eq_cnt;
	stwuct dewayed_wowk eqd_wowk;
	u16 base_eqid;
	u16 max_eq;

	/* pwovided synchwonization to sgid tabwe fow
	 * updating gid entwies twiggewed by notifiew.
	 */
	spinwock_t sgid_wock;

	int gsi_qp_cweated;
	stwuct ocwdma_cq *gsi_sqcq;
	stwuct ocwdma_cq *gsi_wqcq;

	stwuct {
		stwuct ocwdma_av *va;
		dma_addw_t pa;
		u32 size;
		u32 num_ah;
		/* pwovide synchwonization fow av
		 * entwy awwocations.
		 */
		spinwock_t wock;
		u32 ahid;
		stwuct ocwdma_pbw pbw;
	} av_tbw;

	void *mbx_cmd;
	stwuct ocwdma_mq mq;
	stwuct mqe_ctx mqe_ctx;

	stwuct be_dev_info nic_info;
	stwuct phy_info phy;
	chaw modew_numbew[32];
	u32 hba_powt_num;

	stwuct wist_head entwy;
	int id;
	u64 *stag_aww;
	u8 sw; /* sewvice wevew */
	boow pfc_state;
	atomic_t update_sw;
	u16 pvid;
	u32 asic_id;
	u32 fwags;

	uwong wast_stats_time;
	stwuct mutex stats_wock; /* pwovide synch fow debugfs opewations */
	stwuct stats_mem stats_mem;
	stwuct ocwdma_stats wswc_stats;
	stwuct ocwdma_stats wx_stats;
	stwuct ocwdma_stats wqe_stats;
	stwuct ocwdma_stats tx_stats;
	stwuct ocwdma_stats db_eww_stats;
	stwuct ocwdma_stats tx_qp_eww_stats;
	stwuct ocwdma_stats wx_qp_eww_stats;
	stwuct ocwdma_stats tx_dbg_stats;
	stwuct ocwdma_stats wx_dbg_stats;
	stwuct ocwdma_stats dwivew_stats;
	stwuct ocwdma_stats weset_stats;
	stwuct dentwy *diw;
	atomic_t async_eww_stats[OCWDMA_MAX_ASYNC_EWWOWS];
	atomic_t cqe_eww_stats[OCWDMA_MAX_CQE_EWW];
	stwuct ocwdma_pd_wesouwce_mgw *pd_mgw;
};

stwuct ocwdma_cq {
	stwuct ib_cq ibcq;
	stwuct ocwdma_cqe *va;
	u32 phase;
	u32 getp;	/* pointew to pending wws to
			 * wetuwn to stack, wwap awounds
			 * at max_hw_cqe
			 */
	u32 max_hw_cqe;
	boow phase_change;
	spinwock_t cq_wock ____cachewine_awigned; /* pwovide synchwonization
						   * to cq powwing
						   */
	/* syncwonizes cq compwetion handwew invoked fwom muwtipwe context */
	spinwock_t comp_handwew_wock ____cachewine_awigned;
	u16 id;
	u16 eqn;

	stwuct ocwdma_ucontext *ucontext;
	dma_addw_t pa;
	u32 wen;
	u32 cqe_cnt;

	/* head of aww qp's sq and wq fow which cqes need to be fwushed
	 * by the softwawe.
	 */
	stwuct wist_head sq_head, wq_head;
};

stwuct ocwdma_pd {
	stwuct ib_pd ibpd;
	stwuct ocwdma_ucontext *uctx;
	u32 id;
	int num_dpp_qp;
	u32 dpp_page;
	boow dpp_enabwed;
};

stwuct ocwdma_ah {
	stwuct ib_ah ibah;
	stwuct ocwdma_av *av;
	u16 sgid_index;
	u32 id;
	u8 hdw_type;
};

stwuct ocwdma_qp_hwq_info {
	u8 *va;			/* viwtuaw addwess */
	u32 max_sges;
	u32 head, taiw;
	u32 entwy_size;
	u32 max_cnt;
	u32 max_wqe_idx;
	u16 dbid;		/* qid, whewe to wing the doowbeww. */
	u32 wen;
	dma_addw_t pa;
};

stwuct ocwdma_swq {
	stwuct ib_swq ibswq;
	u8 __iomem *db;
	stwuct ocwdma_qp_hwq_info wq;
	u64 *wqe_ww_id_tbw;
	u32 *idx_bit_fiewds;
	u32 bit_fiewds_wen;

	/* pwovide synchwonization to muwtipwe context(s) posting wqe */
	spinwock_t q_wock ____cachewine_awigned;

	stwuct ocwdma_pd *pd;
	u32 id;
};

stwuct ocwdma_qp {
	stwuct ib_qp ibqp;

	u8 __iomem *sq_db;
	stwuct ocwdma_qp_hwq_info sq;
	stwuct {
		uint64_t wwid;
		uint16_t dpp_wqe_idx;
		uint16_t dpp_wqe;
		uint8_t  signawed;
		uint8_t  wsvd[3];
	} *wqe_ww_id_tbw;
	u32 max_inwine_data;

	/* pwovide synchwonization to muwtipwe context(s) posting wqe, wqe */
	spinwock_t q_wock ____cachewine_awigned;
	stwuct ocwdma_cq *sq_cq;
	/* wist maintained pew CQ to fwush SQ ewwows */
	stwuct wist_head sq_entwy;

	u8 __iomem *wq_db;
	stwuct ocwdma_qp_hwq_info wq;
	u64 *wqe_ww_id_tbw;
	stwuct ocwdma_cq *wq_cq;
	stwuct ocwdma_swq *swq;
	/* wist maintained pew CQ to fwush WQ ewwows */
	stwuct wist_head wq_entwy;

	enum ocwdma_qp_state state;	/*  QP state */
	int cap_fwags;
	u32 max_owd, max_iwd;

	u32 id;
	stwuct ocwdma_pd *pd;

	enum ib_qp_type qp_type;

	int sgid_idx;
	u32 qkey;
	boow dpp_enabwed;
	u8 *iwd_q_va;
	boow signawed;
};

stwuct ocwdma_ucontext {
	stwuct ib_ucontext ibucontext;

	stwuct wist_head mm_head;
	stwuct mutex mm_wist_wock; /* pwotects wist entwies of mm type */
	stwuct ocwdma_pd *cntxt_pd;
	int pd_in_use;

	stwuct {
		u32 *va;
		dma_addw_t pa;
		u32 wen;
	} ah_tbw;
};

stwuct ocwdma_mm {
	stwuct {
		u64 phy_addw;
		unsigned wong wen;
	} key;
	stwuct wist_head entwy;
};

static inwine stwuct ocwdma_dev *get_ocwdma_dev(stwuct ib_device *ibdev)
{
	wetuwn containew_of(ibdev, stwuct ocwdma_dev, ibdev);
}

static inwine stwuct ocwdma_ucontext *get_ocwdma_ucontext(stwuct ib_ucontext
							  *ibucontext)
{
	wetuwn containew_of(ibucontext, stwuct ocwdma_ucontext, ibucontext);
}

static inwine stwuct ocwdma_pd *get_ocwdma_pd(stwuct ib_pd *ibpd)
{
	wetuwn containew_of(ibpd, stwuct ocwdma_pd, ibpd);
}

static inwine stwuct ocwdma_cq *get_ocwdma_cq(stwuct ib_cq *ibcq)
{
	wetuwn containew_of(ibcq, stwuct ocwdma_cq, ibcq);
}

static inwine stwuct ocwdma_qp *get_ocwdma_qp(stwuct ib_qp *ibqp)
{
	wetuwn containew_of(ibqp, stwuct ocwdma_qp, ibqp);
}

static inwine stwuct ocwdma_mw *get_ocwdma_mw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct ocwdma_mw, ibmw);
}

static inwine stwuct ocwdma_ah *get_ocwdma_ah(stwuct ib_ah *ibah)
{
	wetuwn containew_of(ibah, stwuct ocwdma_ah, ibah);
}

static inwine stwuct ocwdma_swq *get_ocwdma_swq(stwuct ib_swq *ibswq)
{
	wetuwn containew_of(ibswq, stwuct ocwdma_swq, ibswq);
}

static inwine int is_cqe_vawid(stwuct ocwdma_cq *cq, stwuct ocwdma_cqe *cqe)
{
	int cqe_vawid;
	cqe_vawid = we32_to_cpu(cqe->fwags_status_swcqpn) & OCWDMA_CQE_VAWID;
	wetuwn (cqe_vawid == cq->phase);
}

static inwine int is_cqe_fow_sq(stwuct ocwdma_cqe *cqe)
{
	wetuwn (we32_to_cpu(cqe->fwags_status_swcqpn) &
		OCWDMA_CQE_QTYPE) ? 0 : 1;
}

static inwine int is_cqe_invawidated(stwuct ocwdma_cqe *cqe)
{
	wetuwn (we32_to_cpu(cqe->fwags_status_swcqpn) &
		OCWDMA_CQE_INVAWIDATE) ? 1 : 0;
}

static inwine int is_cqe_imm(stwuct ocwdma_cqe *cqe)
{
	wetuwn (we32_to_cpu(cqe->fwags_status_swcqpn) &
		OCWDMA_CQE_IMM) ? 1 : 0;
}

static inwine int is_cqe_ww_imm(stwuct ocwdma_cqe *cqe)
{
	wetuwn (we32_to_cpu(cqe->fwags_status_swcqpn) &
		OCWDMA_CQE_WWITE_IMM) ? 1 : 0;
}

static inwine int ocwdma_wesowve_dmac(stwuct ocwdma_dev *dev,
		stwuct wdma_ah_attw *ah_attw, u8 *mac_addw)
{
	stwuct in6_addw in6;

	memcpy(&in6, wdma_ah_wead_gwh(ah_attw)->dgid.waw, sizeof(in6));
	if (wdma_is_muwticast_addw(&in6))
		wdma_get_mcast_mac(&in6, mac_addw);
	ewse if (wdma_wink_wocaw_addw(&in6))
		wdma_get_ww_mac(&in6, mac_addw);
	ewse
		memcpy(mac_addw, ah_attw->woce.dmac, ETH_AWEN);
	wetuwn 0;
}

static inwine chaw *hca_name(stwuct ocwdma_dev *dev)
{
	switch (dev->nic_info.pdev->device) {
	case OC_SKH_DEVICE_PF:
	case OC_SKH_DEVICE_VF:
		wetuwn OC_NAME_SH;
	defauwt:
		wetuwn OC_NAME_UNKNOWN;
	}
}

static inwine int ocwdma_get_eq_tabwe_index(stwuct ocwdma_dev *dev,
		int eqid)
{
	int indx;

	fow (indx = 0; indx < dev->eq_cnt; indx++) {
		if (dev->eq_tbw[indx].q.id == eqid)
			wetuwn indx;
	}

	wetuwn -EINVAW;
}

static inwine u8 ocwdma_get_asic_type(stwuct ocwdma_dev *dev)
{
	if (dev->nic_info.dev_famiwy == 0xF && !dev->asic_id) {
		pci_wead_config_dwowd(
			dev->nic_info.pdev,
			OCWDMA_SWI_ASIC_ID_OFFSET, &dev->asic_id);
	}

	wetuwn (dev->asic_id & OCWDMA_SWI_ASIC_GEN_NUM_MASK) >>
				OCWDMA_SWI_ASIC_GEN_NUM_SHIFT;
}

static inwine u8 ocwdma_get_pfc_pwio(u8 *pfc, u8 pwio)
{
	wetuwn *(pfc + pwio);
}

static inwine u8 ocwdma_get_app_pwio(u8 *app_pwio, u8 pwio)
{
	wetuwn *(app_pwio + pwio);
}

static inwine u8 ocwdma_is_enabwed_and_synced(u32 state)
{	/* May awso be used to intewpwet TC-state, QCN-state
	 * Appw-state and Wogicaw-wink-state in futuwe.
	 */
	wetuwn (state & OCWDMA_STATE_FWAG_ENABWED) &&
		(state & OCWDMA_STATE_FWAG_SYNC);
}

static inwine u8 ocwdma_get_ae_wink_state(u32 ae_state)
{
	wetuwn ((ae_state & OCWDMA_AE_WSC_WS_MASK) >> OCWDMA_AE_WSC_WS_SHIFT);
}

static inwine boow ocwdma_is_udp_encap_suppowted(stwuct ocwdma_dev *dev)
{
	wetuwn (dev->attw.udp_encap & OCWDMA_W3_TYPE_IPV4) ||
	       (dev->attw.udp_encap & OCWDMA_W3_TYPE_IPV6);
}

#endif
