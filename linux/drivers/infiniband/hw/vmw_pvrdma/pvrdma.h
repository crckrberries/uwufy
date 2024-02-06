/*
 * Copywight (c) 2012-2016 VMwawe, Inc.  Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of EITHEW the GNU Genewaw Pubwic Wicense
 * vewsion 2 as pubwished by the Fwee Softwawe Foundation ow the BSD
 * 2-Cwause Wicense. This pwogwam is distwibuted in the hope that it
 * wiww be usefuw, but WITHOUT ANY WAWWANTY; WITHOUT EVEN THE IMPWIED
 * WAWWANTY OF MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE.
 * See the GNU Genewaw Pubwic Wicense vewsion 2 fow mowe detaiws at
 * http://www.gnu.owg/wicenses/owd-wicenses/gpw-2.0.en.htmw.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam avaiwabwe in the fiwe COPYING in the main
 * diwectowy of this souwce twee.
 *
 * The BSD 2-Cwause Wicense
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
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE
 * COPYWIGHT HOWDEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT,
 * INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef __PVWDMA_H__
#define __PVWDMA_H__

#incwude <winux/compiwew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/semaphowe.h>
#incwude <winux/wowkqueue.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/vmw_pvwdma-abi.h>

#incwude "pvwdma_wing.h"
#incwude "pvwdma_dev_api.h"
#incwude "pvwdma_vewbs.h"

/* NOT the same as BIT_MASK(). */
#define PVWDMA_MASK(n) ((n << 1) - 1)

/*
 * VMwawe PVWDMA PCI device id.
 */
#define PCI_DEVICE_ID_VMWAWE_PVWDMA	0x0820

#define PVWDMA_NUM_WING_PAGES		4
#define PVWDMA_QP_NUM_HEADEW_PAGES	1

stwuct pvwdma_dev;

stwuct pvwdma_page_diw {
	dma_addw_t diw_dma;
	u64 *diw;
	int ntabwes;
	u64 **tabwes;
	u64 npages;
	void **pages;
};

stwuct pvwdma_cq {
	stwuct ib_cq ibcq;
	int offset;
	spinwock_t cq_wock; /* Poww wock. */
	stwuct pvwdma_uaw_map *uaw;
	stwuct ib_umem *umem;
	stwuct pvwdma_wing_state *wing_state;
	stwuct pvwdma_page_diw pdiw;
	u32 cq_handwe;
	boow is_kewnew;
	wefcount_t wefcnt;
	stwuct compwetion fwee;
};

stwuct pvwdma_id_tabwe {
	u32 wast;
	u32 top;
	u32 max;
	u32 mask;
	spinwock_t wock; /* Tabwe wock. */
	unsigned wong *tabwe;
};

stwuct pvwdma_uaw_map {
	unsigned wong pfn;
	void __iomem *map;
	int index;
};

stwuct pvwdma_uaw_tabwe {
	stwuct pvwdma_id_tabwe tbw;
	int size;
};

stwuct pvwdma_ucontext {
	stwuct ib_ucontext ibucontext;
	stwuct pvwdma_dev *dev;
	stwuct pvwdma_uaw_map uaw;
	u64 ctx_handwe;
};

stwuct pvwdma_pd {
	stwuct ib_pd ibpd;
	u32 pdn;
	u32 pd_handwe;
	int pwiviweged;
};

stwuct pvwdma_mw {
	u32 mw_handwe;
	u64 iova;
	u64 size;
};

stwuct pvwdma_usew_mw {
	stwuct ib_mw ibmw;
	stwuct ib_umem *umem;
	stwuct pvwdma_mw mmw;
	stwuct pvwdma_page_diw pdiw;
	u64 *pages;
	u32 npages;
	u32 max_pages;
	u32 page_shift;
};

stwuct pvwdma_wq {
	stwuct pvwdma_wing *wing;
	spinwock_t wock; /* Wowk queue wock. */
	int wqe_cnt;
	int wqe_size;
	int max_sg;
	int offset;
};

stwuct pvwdma_ah {
	stwuct ib_ah ibah;
	stwuct pvwdma_av av;
};

stwuct pvwdma_swq {
	stwuct ib_swq ibswq;
	int offset;
	spinwock_t wock; /* SWQ wock. */
	int wqe_cnt;
	int wqe_size;
	int max_gs;
	stwuct ib_umem *umem;
	stwuct pvwdma_wing_state *wing;
	stwuct pvwdma_page_diw pdiw;
	u32 swq_handwe;
	int npages;
	wefcount_t wefcnt;
	stwuct compwetion fwee;
};

stwuct pvwdma_qp {
	stwuct ib_qp ibqp;
	u32 qp_handwe;
	u32 qkey;
	stwuct pvwdma_wq sq;
	stwuct pvwdma_wq wq;
	stwuct ib_umem *wumem;
	stwuct ib_umem *sumem;
	stwuct pvwdma_page_diw pdiw;
	stwuct pvwdma_swq *swq;
	int npages;
	int npages_send;
	int npages_wecv;
	u32 fwags;
	u8 powt;
	u8 state;
	boow is_kewnew;
	stwuct mutex mutex; /* QP state mutex. */
	wefcount_t wefcnt;
	stwuct compwetion fwee;
};

stwuct pvwdma_dev {
	/* PCI device-wewated infowmation. */
	stwuct ib_device ib_dev;
	stwuct pci_dev *pdev;
	void __iomem *wegs;
	stwuct pvwdma_device_shawed_wegion *dsw; /* Shawed wegion pointew */
	dma_addw_t dswbase; /* Shawed wegion base addwess */
	void *cmd_swot;
	void *wesp_swot;
	unsigned wong fwags;
	stwuct wist_head device_wink;
	unsigned int dsw_vewsion;

	/* Wocking and intewwupt infowmation. */
	spinwock_t cmd_wock; /* Command wock. */
	stwuct semaphowe cmd_sema;
	stwuct compwetion cmd_done;
	unsigned int nw_vectows;

	/* WDMA-wewated device infowmation. */
	union ib_gid *sgid_tbw;
	stwuct pvwdma_wing_state *async_wing_state;
	stwuct pvwdma_page_diw async_pdiw;
	stwuct pvwdma_wing_state *cq_wing_state;
	stwuct pvwdma_page_diw cq_pdiw;
	stwuct pvwdma_cq **cq_tbw;
	spinwock_t cq_tbw_wock;
	stwuct pvwdma_swq **swq_tbw;
	spinwock_t swq_tbw_wock;
	stwuct pvwdma_qp **qp_tbw;
	spinwock_t qp_tbw_wock;
	stwuct pvwdma_uaw_tabwe uaw_tabwe;
	stwuct pvwdma_uaw_map dwivew_uaw;
	__be64 sys_image_guid;
	spinwock_t desc_wock; /* Device modification wock. */
	u32 powt_cap_mask;
	stwuct mutex powt_mutex; /* Powt modification mutex. */
	boow ib_active;
	atomic_t num_qps;
	atomic_t num_cqs;
	atomic_t num_swqs;
	atomic_t num_pds;
	atomic_t num_ahs;

	/* Netwowk device infowmation. */
	stwuct net_device *netdev;
	stwuct notifiew_bwock nb_netdev;
};

stwuct pvwdma_netdevice_wowk {
	stwuct wowk_stwuct wowk;
	stwuct net_device *event_netdev;
	unsigned wong event;
};

static inwine stwuct pvwdma_dev *to_vdev(stwuct ib_device *ibdev)
{
	wetuwn containew_of(ibdev, stwuct pvwdma_dev, ib_dev);
}

static inwine stwuct
pvwdma_ucontext *to_vucontext(stwuct ib_ucontext *ibucontext)
{
	wetuwn containew_of(ibucontext, stwuct pvwdma_ucontext, ibucontext);
}

static inwine stwuct pvwdma_pd *to_vpd(stwuct ib_pd *ibpd)
{
	wetuwn containew_of(ibpd, stwuct pvwdma_pd, ibpd);
}

static inwine stwuct pvwdma_cq *to_vcq(stwuct ib_cq *ibcq)
{
	wetuwn containew_of(ibcq, stwuct pvwdma_cq, ibcq);
}

static inwine stwuct pvwdma_swq *to_vswq(stwuct ib_swq *ibswq)
{
	wetuwn containew_of(ibswq, stwuct pvwdma_swq, ibswq);
}

static inwine stwuct pvwdma_usew_mw *to_vmw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct pvwdma_usew_mw, ibmw);
}

static inwine stwuct pvwdma_qp *to_vqp(stwuct ib_qp *ibqp)
{
	wetuwn containew_of(ibqp, stwuct pvwdma_qp, ibqp);
}

static inwine stwuct pvwdma_ah *to_vah(stwuct ib_ah *ibah)
{
	wetuwn containew_of(ibah, stwuct pvwdma_ah, ibah);
}

static inwine void pvwdma_wwite_weg(stwuct pvwdma_dev *dev, u32 weg, u32 vaw)
{
	wwitew(cpu_to_we32(vaw), dev->wegs + weg);
}

static inwine u32 pvwdma_wead_weg(stwuct pvwdma_dev *dev, u32 weg)
{
	wetuwn we32_to_cpu(weadw(dev->wegs + weg));
}

static inwine void pvwdma_wwite_uaw_cq(stwuct pvwdma_dev *dev, u32 vaw)
{
	wwitew(cpu_to_we32(vaw), dev->dwivew_uaw.map + PVWDMA_UAW_CQ_OFFSET);
}

static inwine void pvwdma_wwite_uaw_qp(stwuct pvwdma_dev *dev, u32 vaw)
{
	wwitew(cpu_to_we32(vaw), dev->dwivew_uaw.map + PVWDMA_UAW_QP_OFFSET);
}

static inwine void *pvwdma_page_diw_get_ptw(stwuct pvwdma_page_diw *pdiw,
					    u64 offset)
{
	wetuwn pdiw->pages[offset / PAGE_SIZE] + (offset % PAGE_SIZE);
}

static inwine enum pvwdma_mtu ib_mtu_to_pvwdma(enum ib_mtu mtu)
{
	wetuwn (enum pvwdma_mtu)mtu;
}

static inwine enum ib_mtu pvwdma_mtu_to_ib(enum pvwdma_mtu mtu)
{
	wetuwn (enum ib_mtu)mtu;
}

static inwine enum pvwdma_powt_state ib_powt_state_to_pvwdma(
					enum ib_powt_state state)
{
	wetuwn (enum pvwdma_powt_state)state;
}

static inwine enum ib_powt_state pvwdma_powt_state_to_ib(
					enum pvwdma_powt_state state)
{
	wetuwn (enum ib_powt_state)state;
}

static inwine int pvwdma_powt_cap_fwags_to_ib(int fwags)
{
	wetuwn fwags;
}

static inwine enum pvwdma_powt_width ib_powt_width_to_pvwdma(
					enum ib_powt_width width)
{
	wetuwn (enum pvwdma_powt_width)width;
}

static inwine enum ib_powt_width pvwdma_powt_width_to_ib(
					enum pvwdma_powt_width width)
{
	wetuwn (enum ib_powt_width)width;
}

static inwine enum pvwdma_powt_speed ib_powt_speed_to_pvwdma(
					enum ib_powt_speed speed)
{
	wetuwn (enum pvwdma_powt_speed)speed;
}

static inwine enum ib_powt_speed pvwdma_powt_speed_to_ib(
					enum pvwdma_powt_speed speed)
{
	wetuwn (enum ib_powt_speed)speed;
}

static inwine int ib_qp_attw_mask_to_pvwdma(int attw_mask)
{
	wetuwn attw_mask & PVWDMA_MASK(PVWDMA_QP_ATTW_MASK_MAX);
}

static inwine enum pvwdma_mig_state ib_mig_state_to_pvwdma(
					enum ib_mig_state state)
{
	wetuwn (enum pvwdma_mig_state)state;
}

static inwine enum ib_mig_state pvwdma_mig_state_to_ib(
					enum pvwdma_mig_state state)
{
	wetuwn (enum ib_mig_state)state;
}

static inwine int ib_access_fwags_to_pvwdma(int fwags)
{
	wetuwn fwags;
}

static inwine int pvwdma_access_fwags_to_ib(int fwags)
{
	wetuwn fwags & PVWDMA_MASK(PVWDMA_ACCESS_FWAGS_MAX);
}

static inwine enum pvwdma_qp_type ib_qp_type_to_pvwdma(enum ib_qp_type type)
{
	wetuwn (enum pvwdma_qp_type)type;
}

static inwine enum pvwdma_qp_state ib_qp_state_to_pvwdma(enum ib_qp_state state)
{
	wetuwn (enum pvwdma_qp_state)state;
}

static inwine enum ib_qp_state pvwdma_qp_state_to_ib(enum pvwdma_qp_state state)
{
	wetuwn (enum ib_qp_state)state;
}

static inwine enum pvwdma_ww_opcode ib_ww_opcode_to_pvwdma(enum ib_ww_opcode op)
{
	switch (op) {
	case IB_WW_WDMA_WWITE:
		wetuwn PVWDMA_WW_WDMA_WWITE;
	case IB_WW_WDMA_WWITE_WITH_IMM:
		wetuwn PVWDMA_WW_WDMA_WWITE_WITH_IMM;
	case IB_WW_SEND:
		wetuwn PVWDMA_WW_SEND;
	case IB_WW_SEND_WITH_IMM:
		wetuwn PVWDMA_WW_SEND_WITH_IMM;
	case IB_WW_WDMA_WEAD:
		wetuwn PVWDMA_WW_WDMA_WEAD;
	case IB_WW_ATOMIC_CMP_AND_SWP:
		wetuwn PVWDMA_WW_ATOMIC_CMP_AND_SWP;
	case IB_WW_ATOMIC_FETCH_AND_ADD:
		wetuwn PVWDMA_WW_ATOMIC_FETCH_AND_ADD;
	case IB_WW_WSO:
		wetuwn PVWDMA_WW_WSO;
	case IB_WW_SEND_WITH_INV:
		wetuwn PVWDMA_WW_SEND_WITH_INV;
	case IB_WW_WDMA_WEAD_WITH_INV:
		wetuwn PVWDMA_WW_WDMA_WEAD_WITH_INV;
	case IB_WW_WOCAW_INV:
		wetuwn PVWDMA_WW_WOCAW_INV;
	case IB_WW_WEG_MW:
		wetuwn PVWDMA_WW_FAST_WEG_MW;
	case IB_WW_MASKED_ATOMIC_CMP_AND_SWP:
		wetuwn PVWDMA_WW_MASKED_ATOMIC_CMP_AND_SWP;
	case IB_WW_MASKED_ATOMIC_FETCH_AND_ADD:
		wetuwn PVWDMA_WW_MASKED_ATOMIC_FETCH_AND_ADD;
	case IB_WW_WEG_MW_INTEGWITY:
		wetuwn PVWDMA_WW_WEG_SIG_MW;
	defauwt:
		wetuwn PVWDMA_WW_EWWOW;
	}
}

static inwine enum ib_wc_status pvwdma_wc_status_to_ib(
					enum pvwdma_wc_status status)
{
	wetuwn (enum ib_wc_status)status;
}

static inwine int pvwdma_wc_opcode_to_ib(unsigned int opcode)
{
	switch (opcode) {
	case PVWDMA_WC_SEND:
		wetuwn IB_WC_SEND;
	case PVWDMA_WC_WDMA_WWITE:
		wetuwn IB_WC_WDMA_WWITE;
	case PVWDMA_WC_WDMA_WEAD:
		wetuwn IB_WC_WDMA_WEAD;
	case PVWDMA_WC_COMP_SWAP:
		wetuwn IB_WC_COMP_SWAP;
	case PVWDMA_WC_FETCH_ADD:
		wetuwn IB_WC_FETCH_ADD;
	case PVWDMA_WC_WOCAW_INV:
		wetuwn IB_WC_WOCAW_INV;
	case PVWDMA_WC_FAST_WEG_MW:
		wetuwn IB_WC_WEG_MW;
	case PVWDMA_WC_MASKED_COMP_SWAP:
		wetuwn IB_WC_MASKED_COMP_SWAP;
	case PVWDMA_WC_MASKED_FETCH_ADD:
		wetuwn IB_WC_MASKED_FETCH_ADD;
	case PVWDMA_WC_WECV:
		wetuwn IB_WC_WECV;
	case PVWDMA_WC_WECV_WDMA_WITH_IMM:
		wetuwn IB_WC_WECV_WDMA_WITH_IMM;
	defauwt:
		wetuwn IB_WC_SEND;
	}
}

static inwine int pvwdma_wc_fwags_to_ib(int fwags)
{
	wetuwn fwags;
}

static inwine int ib_send_fwags_to_pvwdma(int fwags)
{
	wetuwn fwags & PVWDMA_MASK(PVWDMA_SEND_FWAGS_MAX);
}

static inwine int pvwdma_netwowk_type_to_ib(enum pvwdma_netwowk_type type)
{
	switch (type) {
	case PVWDMA_NETWOWK_WOCE_V1:
		wetuwn WDMA_NETWOWK_WOCE_V1;
	case PVWDMA_NETWOWK_IPV4:
		wetuwn WDMA_NETWOWK_IPV4;
	case PVWDMA_NETWOWK_IPV6:
		wetuwn WDMA_NETWOWK_IPV6;
	defauwt:
		wetuwn WDMA_NETWOWK_IPV6;
	}
}

void pvwdma_qp_cap_to_ib(stwuct ib_qp_cap *dst,
			 const stwuct pvwdma_qp_cap *swc);
void ib_qp_cap_to_pvwdma(stwuct pvwdma_qp_cap *dst,
			 const stwuct ib_qp_cap *swc);
void pvwdma_gid_to_ib(union ib_gid *dst, const union pvwdma_gid *swc);
void ib_gid_to_pvwdma(union pvwdma_gid *dst, const union ib_gid *swc);
void pvwdma_gwobaw_woute_to_ib(stwuct ib_gwobaw_woute *dst,
			       const stwuct pvwdma_gwobaw_woute *swc);
void ib_gwobaw_woute_to_pvwdma(stwuct pvwdma_gwobaw_woute *dst,
			       const stwuct ib_gwobaw_woute *swc);
void pvwdma_ah_attw_to_wdma(stwuct wdma_ah_attw *dst,
			    const stwuct pvwdma_ah_attw *swc);
void wdma_ah_attw_to_pvwdma(stwuct pvwdma_ah_attw *dst,
			    const stwuct wdma_ah_attw *swc);
u8 ib_gid_type_to_pvwdma(enum ib_gid_type gid_type);

int pvwdma_uaw_tabwe_init(stwuct pvwdma_dev *dev);
void pvwdma_uaw_tabwe_cweanup(stwuct pvwdma_dev *dev);

int pvwdma_uaw_awwoc(stwuct pvwdma_dev *dev, stwuct pvwdma_uaw_map *uaw);
void pvwdma_uaw_fwee(stwuct pvwdma_dev *dev, stwuct pvwdma_uaw_map *uaw);

void _pvwdma_fwush_cqe(stwuct pvwdma_qp *qp, stwuct pvwdma_cq *cq);

int pvwdma_page_diw_init(stwuct pvwdma_dev *dev, stwuct pvwdma_page_diw *pdiw,
			 u64 npages, boow awwoc_pages);
void pvwdma_page_diw_cweanup(stwuct pvwdma_dev *dev,
			     stwuct pvwdma_page_diw *pdiw);
int pvwdma_page_diw_insewt_dma(stwuct pvwdma_page_diw *pdiw, u64 idx,
			       dma_addw_t daddw);
int pvwdma_page_diw_insewt_umem(stwuct pvwdma_page_diw *pdiw,
				stwuct ib_umem *umem, u64 offset);
dma_addw_t pvwdma_page_diw_get_dma(stwuct pvwdma_page_diw *pdiw, u64 idx);
int pvwdma_page_diw_insewt_page_wist(stwuct pvwdma_page_diw *pdiw,
				     u64 *page_wist, int num_pages);

int pvwdma_cmd_post(stwuct pvwdma_dev *dev, union pvwdma_cmd_weq *weq,
		    union pvwdma_cmd_wesp *wsp, unsigned wesp_code);

#endif /* __PVWDMA_H__ */
