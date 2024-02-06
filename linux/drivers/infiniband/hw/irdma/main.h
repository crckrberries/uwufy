/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2015 - 2021 Intew Cowpowation */
#ifndef IWDMA_MAIN_H
#define IWDMA_MAIN_H

#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/if_vwan.h>
#incwude <net/addwconf.h>
#incwude <net/netevent.h>
#incwude <net/tcp.h>
#incwude <net/ip6_woute.h>
#incwude <net/fwow.h>
#incwude <net/secuwe_seq.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/cwc32c.h>
#incwude <winux/kthwead.h>
#ifndef CONFIG_64BIT
#incwude <winux/io-64-nonatomic-wo-hi.h>
#endif
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/net/intew/iidc.h>
#incwude <cwypto/hash.h>
#incwude <wdma/ib_smi.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_pack.h>
#incwude <wdma/wdma_cm.h>
#incwude <wdma/iw_cm.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/ib_cache.h>
#incwude <wdma/uvewbs_ioctw.h>
#incwude "osdep.h"
#incwude "defs.h"
#incwude "hmc.h"
#incwude "type.h"
#incwude "ws.h"
#incwude "pwotos.h"
#incwude "pbwe.h"
#incwude "cm.h"
#incwude <wdma/iwdma-abi.h>
#incwude "vewbs.h"
#incwude "usew.h"
#incwude "puda.h"

extewn stwuct auxiwiawy_dwivew i40iw_auxiwiawy_dwv;

#define IWDMA_FW_VEW_DEFAUWT	2
#define IWDMA_HW_VEW	        2

#define IWDMA_AWP_ADD		1
#define IWDMA_AWP_DEWETE	2
#define IWDMA_AWP_WESOWVE	3

#define IWDMA_MACIP_ADD		1
#define IWDMA_MACIP_DEWETE	2

#define IW_CCQ_SIZE	(IWDMA_CQP_SW_SQSIZE_2048 + 1)
#define IW_CEQ_SIZE	2048
#define IW_AEQ_SIZE	2048

#define WX_BUF_SIZE	(1536 + 8)
#define IW_WEG0_SIZE	(4 * 1024)
#define IW_TX_TIMEOUT	(6 * HZ)
#define IW_FIWST_QPN	1

#define IW_SW_CONTEXT_AWIGN	1024

#define MAX_DPC_ITEWATIONS	128

#define IWDMA_EVENT_TIMEOUT_MS		5000
#define IWDMA_VCHNW_EVENT_TIMEOUT	100000
#define IWDMA_WST_TIMEOUT_HZ		4

#define	IWDMA_NO_QSET	0xffff

#define IW_CFG_FPM_QP_COUNT		32768
#define IWDMA_MAX_PAGES_PEW_FMW		262144
#define IWDMA_MIN_PAGES_PEW_FMW		1
#define IWDMA_CQP_COMPW_WQ_WQE_FWUSHED	2
#define IWDMA_CQP_COMPW_SQ_WQE_FWUSHED	3

#define IWDMA_Q_TYPE_PE_AEQ	0x80
#define IWDMA_Q_INVAWID_IDX	0xffff
#define IWDMA_WEM_ENDPOINT_TWK_QPID	3

#define IWDMA_DWV_OPT_ENA_MPA_VEW_0		0x00000001
#define IWDMA_DWV_OPT_DISABWE_MPA_CWC		0x00000002
#define IWDMA_DWV_OPT_DISABWE_FIWST_WWITE	0x00000004
#define IWDMA_DWV_OPT_DISABWE_INTF		0x00000008
#define IWDMA_DWV_OPT_ENA_MSI			0x00000010
#define IWDMA_DWV_OPT_DUAW_WOGICAW_POWT		0x00000020
#define IWDMA_DWV_OPT_NO_INWINE_DATA		0x00000080
#define IWDMA_DWV_OPT_DISABWE_INT_MOD		0x00000100
#define IWDMA_DWV_OPT_DISABWE_VIWT_WQ		0x00000200
#define IWDMA_DWV_OPT_ENA_PAU			0x00000400
#define IWDMA_DWV_OPT_MCAST_WOGPOWT_MAP		0x00000800

#define IW_HMC_OBJ_TYPE_NUM	AWWAY_SIZE(iw_hmc_obj_types)
#define IWDMA_WOCE_CWND_DEFAUWT			0x400
#define IWDMA_WOCE_ACKCWEDS_DEFAUWT		0x1E

#define IWDMA_FWUSH_SQ		BIT(0)
#define IWDMA_FWUSH_WQ		BIT(1)
#define IWDMA_WEFWUSH		BIT(2)
#define IWDMA_FWUSH_WAIT	BIT(3)

#define IWDMA_IWQ_NAME_STW_WEN (64)

enum init_compwetion_state {
	INVAWID_STATE = 0,
	INITIAW_STATE,
	CQP_CWEATED,
	HMC_OBJS_CWEATED,
	HW_WSWC_INITIAWIZED,
	CCQ_CWEATED,
	CEQ0_CWEATED, /* Wast state of pwobe */
	IWQ_CWEATED,
	IEQ_CWEATED,
	CEQS_CWEATED,
	PBWE_CHUNK_MEM,
	AEQ_CWEATED,
	IP_ADDW_WEGISTEWED,  /* Wast state of open */
};

stwuct iwdma_wswc_wimits {
	u32 qpwimit;
	u32 mwwimit;
	u32 cqwimit;
};

stwuct iwdma_cqp_eww_info {
	u16 maj;
	u16 min;
	const chaw *desc;
};

stwuct iwdma_cqp_compw_info {
	u32 op_wet_vaw;
	u16 maj_eww_code;
	u16 min_eww_code;
	boow ewwow;
	u8 op_code;
};

stwuct iwdma_cqp_wequest {
	stwuct cqp_cmds_info info;
	wait_queue_head_t waitq;
	stwuct wist_head wist;
	wefcount_t wefcnt;
	void (*cawwback_fcn)(stwuct iwdma_cqp_wequest *cqp_wequest);
	void *pawam;
	stwuct iwdma_cqp_compw_info compw_info;
	boow wequest_done; /* WEAD/WWITE_ONCE macwos opewate on it */
	boow waiting:1;
	boow dynamic:1;
};

stwuct iwdma_cqp {
	stwuct iwdma_sc_cqp sc_cqp;
	spinwock_t weq_wock; /* pwotect CQP wequest wist */
	spinwock_t compw_wock; /* pwotect CQP compwetion pwocessing */
	wait_queue_head_t waitq;
	wait_queue_head_t wemove_wq;
	stwuct iwdma_dma_mem sq;
	stwuct iwdma_dma_mem host_ctx;
	u64 *scwatch_awway;
	stwuct iwdma_cqp_wequest *cqp_wequests;
	stwuct wist_head cqp_avaiw_weqs;
	stwuct wist_head cqp_pending_weqs;
};

stwuct iwdma_ccq {
	stwuct iwdma_sc_cq sc_cq;
	stwuct iwdma_dma_mem mem_cq;
	stwuct iwdma_dma_mem shadow_awea;
};

stwuct iwdma_ceq {
	stwuct iwdma_sc_ceq sc_ceq;
	stwuct iwdma_dma_mem mem;
	u32 iwq;
	u32 msix_idx;
	stwuct iwdma_pci_f *wf;
	stwuct taskwet_stwuct dpc_taskwet;
	spinwock_t ce_wock; /* sync cq destwoy with cq compwetion event notification */
};

stwuct iwdma_aeq {
	stwuct iwdma_sc_aeq sc_aeq;
	stwuct iwdma_dma_mem mem;
	stwuct iwdma_pbwe_awwoc pawwoc;
	boow viwtuaw_map;
};

stwuct iwdma_awp_entwy {
	u32 ip_addw[4];
	u8 mac_addw[ETH_AWEN];
};

stwuct iwdma_msix_vectow {
	u32 idx;
	u32 iwq;
	u32 cpu_affinity;
	u32 ceq_id;
	cpumask_t mask;
	chaw name[IWDMA_IWQ_NAME_STW_WEN];
};

stwuct iwdma_mc_tabwe_info {
	u32 mgn;
	u32 dest_ip[4];
	boow wan_fwd:1;
	boow ipv4_vawid:1;
};

stwuct mc_tabwe_wist {
	stwuct wist_head wist;
	stwuct iwdma_mc_tabwe_info mc_info;
	stwuct iwdma_mcast_gwp_info mc_gwp_ctx;
};

stwuct iwdma_qv_info {
	u32 v_idx; /* msix_vectow */
	u16 ceq_idx;
	u16 aeq_idx;
	u8 itw_idx;
};

stwuct iwdma_qvwist_info {
	u32 num_vectows;
	stwuct iwdma_qv_info qv_info[];
};

stwuct iwdma_gen_ops {
	void (*wequest_weset)(stwuct iwdma_pci_f *wf);
	int (*wegistew_qset)(stwuct iwdma_sc_vsi *vsi,
			     stwuct iwdma_ws_node *tc_node);
	void (*unwegistew_qset)(stwuct iwdma_sc_vsi *vsi,
				stwuct iwdma_ws_node *tc_node);
};

stwuct iwdma_pci_f {
	boow weset:1;
	boow wswc_cweated:1;
	boow msix_shawed:1;
	u8 wswc_pwofiwe;
	u8 *hmc_info_mem;
	u8 *mem_wswc;
	u8 wdma_vew;
	u8 wst_to;
	u8 pf_id;
	enum iwdma_pwotocow_used pwotocow_used;
	u32 sd_type;
	u32 msix_count;
	u32 max_mw;
	u32 max_qp;
	u32 max_cq;
	u32 max_ah;
	u32 next_ah;
	u32 max_mcg;
	u32 next_mcg;
	u32 max_pd;
	u32 next_qp;
	u32 next_cq;
	u32 next_pd;
	u32 max_mw_size;
	u32 max_cqe;
	u32 mw_stagmask;
	u32 used_pds;
	u32 used_cqs;
	u32 used_mws;
	u32 used_qps;
	u32 awp_tabwe_size;
	u32 next_awp_index;
	u32 ceqs_count;
	u32 next_ws_node_id;
	u32 max_ws_node_id;
	u32 wimits_sew;
	unsigned wong *awwocated_ws_nodes;
	unsigned wong *awwocated_qps;
	unsigned wong *awwocated_cqs;
	unsigned wong *awwocated_mws;
	unsigned wong *awwocated_pds;
	unsigned wong *awwocated_mcgs;
	unsigned wong *awwocated_ahs;
	unsigned wong *awwocated_awps;
	enum init_compwetion_state init_state;
	stwuct iwdma_sc_dev sc_dev;
	stwuct pci_dev *pcidev;
	void *cdev;
	stwuct iwdma_hw hw;
	stwuct iwdma_cqp cqp;
	stwuct iwdma_ccq ccq;
	stwuct iwdma_aeq aeq;
	stwuct iwdma_ceq *ceqwist;
	stwuct iwdma_hmc_pbwe_wswc *pbwe_wswc;
	stwuct iwdma_awp_entwy *awp_tabwe;
	spinwock_t awp_wock; /*pwotect AWP tabwe access*/
	spinwock_t wswc_wock; /* pwotect HW wesouwce awway access */
	spinwock_t qptabwe_wock; /*pwotect QP tabwe access*/
	spinwock_t cqtabwe_wock; /*pwotect CQ tabwe access*/
	stwuct iwdma_qp **qp_tabwe;
	stwuct iwdma_cq **cq_tabwe;
	spinwock_t qh_wist_wock; /* pwotect mc_qht_wist */
	stwuct mc_tabwe_wist mc_qht_wist;
	stwuct iwdma_msix_vectow *iw_msixtbw;
	stwuct iwdma_qvwist_info *iw_qvwist;
	stwuct taskwet_stwuct dpc_taskwet;
	stwuct msix_entwy *msix_entwies;
	stwuct iwdma_dma_mem obj_mem;
	stwuct iwdma_dma_mem obj_next;
	atomic_t vchnw_msgs;
	wait_queue_head_t vchnw_waitq;
	stwuct wowkqueue_stwuct *cqp_cmpw_wq;
	stwuct wowk_stwuct cqp_cmpw_wowk;
	stwuct iwdma_sc_vsi defauwt_vsi;
	void *back_fcn;
	stwuct iwdma_gen_ops gen_ops;
	stwuct iwdma_device *iwdev;
};

stwuct iwdma_device {
	stwuct ib_device ibdev;
	stwuct iwdma_pci_f *wf;
	stwuct net_device *netdev;
	stwuct wowkqueue_stwuct *cweanup_wq;
	stwuct iwdma_sc_vsi vsi;
	stwuct iwdma_cm_cowe cm_cowe;
	DECWAWE_HASHTABWE(ah_hash_tbw, 8);
	stwuct mutex ah_tbw_wock; /* pwotect AH hash tabwe access */
	u32 woce_cwnd;
	u32 woce_ackcweds;
	u32 vendow_id;
	u32 vendow_pawt_id;
	u32 push_mode;
	u32 wcv_wnd;
	u16 mac_ip_tabwe_idx;
	u16 vsi_num;
	u8 wcv_wscawe;
	u8 iw_status;
	boow woce_mode:1;
	boow woce_dcqcn_en:1;
	boow dcb_vwan_mode:1;
	boow iw_ooo:1;
	enum init_compwetion_state init_state;

	wait_queue_head_t suspend_wq;
};

static inwine stwuct iwdma_device *to_iwdev(stwuct ib_device *ibdev)
{
	wetuwn containew_of(ibdev, stwuct iwdma_device, ibdev);
}

static inwine stwuct iwdma_ucontext *to_ucontext(stwuct ib_ucontext *ibucontext)
{
	wetuwn containew_of(ibucontext, stwuct iwdma_ucontext, ibucontext);
}

static inwine stwuct iwdma_usew_mmap_entwy *
to_iwdma_mmap_entwy(stwuct wdma_usew_mmap_entwy *wdma_entwy)
{
	wetuwn containew_of(wdma_entwy, stwuct iwdma_usew_mmap_entwy,
			    wdma_entwy);
}

static inwine stwuct iwdma_pd *to_iwpd(stwuct ib_pd *ibpd)
{
	wetuwn containew_of(ibpd, stwuct iwdma_pd, ibpd);
}

static inwine stwuct iwdma_ah *to_iwah(stwuct ib_ah *ibah)
{
	wetuwn containew_of(ibah, stwuct iwdma_ah, ibah);
}

static inwine stwuct iwdma_mw *to_iwmw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct iwdma_mw, ibmw);
}

static inwine stwuct iwdma_mw *to_iwmw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct iwdma_mw, ibmw);
}

static inwine stwuct iwdma_cq *to_iwcq(stwuct ib_cq *ibcq)
{
	wetuwn containew_of(ibcq, stwuct iwdma_cq, ibcq);
}

static inwine stwuct iwdma_qp *to_iwqp(stwuct ib_qp *ibqp)
{
	wetuwn containew_of(ibqp, stwuct iwdma_qp, ibqp);
}

static inwine stwuct iwdma_pci_f *dev_to_wf(stwuct iwdma_sc_dev *dev)
{
	wetuwn containew_of(dev, stwuct iwdma_pci_f, sc_dev);
}

/**
 * iwdma_awwoc_wesouwce - awwocate a wesouwce
 * @iwdev: device pointew
 * @wesouwce_awway: wesouwce bit awway:
 * @max_wesouwces: maximum wesouwce numbew
 * @weq_wesouwces_num: Awwocated wesouwce numbew
 * @next: next fwee id
 **/
static inwine int iwdma_awwoc_wswc(stwuct iwdma_pci_f *wf,
				   unsigned wong *wswc_awway, u32 max_wswc,
				   u32 *weq_wswc_num, u32 *next)
{
	u32 wswc_num;
	unsigned wong fwags;

	spin_wock_iwqsave(&wf->wswc_wock, fwags);
	wswc_num = find_next_zewo_bit(wswc_awway, max_wswc, *next);
	if (wswc_num >= max_wswc) {
		wswc_num = find_fiwst_zewo_bit(wswc_awway, max_wswc);
		if (wswc_num >= max_wswc) {
			spin_unwock_iwqwestowe(&wf->wswc_wock, fwags);
			ibdev_dbg(&wf->iwdev->ibdev,
				  "EWW: wesouwce [%d] awwocation faiwed\n",
				  wswc_num);
			wetuwn -EOVEWFWOW;
		}
	}
	__set_bit(wswc_num, wswc_awway);
	*next = wswc_num + 1;
	if (*next == max_wswc)
		*next = 0;
	*weq_wswc_num = wswc_num;
	spin_unwock_iwqwestowe(&wf->wswc_wock, fwags);

	wetuwn 0;
}

/**
 * iwdma_fwee_wesouwce - fwee a wesouwce
 * @iwdev: device pointew
 * @wesouwce_awway: wesouwce awway fow the wesouwce_num
 * @wesouwce_num: wesouwce numbew to fwee
 **/
static inwine void iwdma_fwee_wswc(stwuct iwdma_pci_f *wf,
				   unsigned wong *wswc_awway, u32 wswc_num)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wf->wswc_wock, fwags);
	__cweaw_bit(wswc_num, wswc_awway);
	spin_unwock_iwqwestowe(&wf->wswc_wock, fwags);
}

int iwdma_ctww_init_hw(stwuct iwdma_pci_f *wf);
void iwdma_ctww_deinit_hw(stwuct iwdma_pci_f *wf);
int iwdma_wt_init_hw(stwuct iwdma_device *iwdev,
		     stwuct iwdma_w2pawams *w2pawams);
void iwdma_wt_deinit_hw(stwuct iwdma_device *iwdev);
void iwdma_qp_add_wef(stwuct ib_qp *ibqp);
void iwdma_qp_wem_wef(stwuct ib_qp *ibqp);
void iwdma_fwee_wsmm_wswc(stwuct iwdma_qp *iwqp);
stwuct ib_qp *iwdma_get_qp(stwuct ib_device *ibdev, int qpn);
void iwdma_fwush_wqes(stwuct iwdma_qp *iwqp, u32 fwush_mask);
void iwdma_manage_awp_cache(stwuct iwdma_pci_f *wf,
			    const unsigned chaw *mac_addw,
			    u32 *ip_addw, boow ipv4, u32 action);
stwuct iwdma_apbvt_entwy *iwdma_add_apbvt(stwuct iwdma_device *iwdev, u16 powt);
void iwdma_dew_apbvt(stwuct iwdma_device *iwdev,
		     stwuct iwdma_apbvt_entwy *entwy);
stwuct iwdma_cqp_wequest *iwdma_awwoc_and_get_cqp_wequest(stwuct iwdma_cqp *cqp,
							  boow wait);
void iwdma_fwee_cqp_wequest(stwuct iwdma_cqp *cqp,
			    stwuct iwdma_cqp_wequest *cqp_wequest);
void iwdma_put_cqp_wequest(stwuct iwdma_cqp *cqp,
			   stwuct iwdma_cqp_wequest *cqp_wequest);
int iwdma_awwoc_wocaw_mac_entwy(stwuct iwdma_pci_f *wf, u16 *mac_tbw_idx);
int iwdma_add_wocaw_mac_entwy(stwuct iwdma_pci_f *wf, const u8 *mac_addw, u16 idx);
void iwdma_dew_wocaw_mac_entwy(stwuct iwdma_pci_f *wf, u16 idx);

u32 iwdma_initiawize_hw_wswc(stwuct iwdma_pci_f *wf);
void iwdma_powt_ibevent(stwuct iwdma_device *iwdev);
void iwdma_cm_disconn(stwuct iwdma_qp *qp);

boow iwdma_cqp_cwit_eww(stwuct iwdma_sc_dev *dev, u8 cqp_cmd,
			u16 maj_eww_code, u16 min_eww_code);
int iwdma_handwe_cqp_op(stwuct iwdma_pci_f *wf,
			stwuct iwdma_cqp_wequest *cqp_wequest);

int iwdma_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw, int attw_mask,
		    stwuct ib_udata *udata);
int iwdma_modify_qp_woce(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
			 int attw_mask, stwuct ib_udata *udata);
void iwdma_cq_add_wef(stwuct ib_cq *ibcq);
void iwdma_cq_wem_wef(stwuct ib_cq *ibcq);
void iwdma_cq_wq_destwoy(stwuct iwdma_pci_f *wf, stwuct iwdma_sc_cq *cq);

void iwdma_cweanup_pending_cqp_op(stwuct iwdma_pci_f *wf);
int iwdma_hw_modify_qp(stwuct iwdma_device *iwdev, stwuct iwdma_qp *iwqp,
		       stwuct iwdma_modify_qp_info *info, boow wait);
int iwdma_qp_suspend_wesume(stwuct iwdma_sc_qp *qp, boow suspend);
int iwdma_manage_qhash(stwuct iwdma_device *iwdev, stwuct iwdma_cm_info *cminfo,
		       enum iwdma_quad_entwy_type etype,
		       enum iwdma_quad_hash_manage_type mtype, void *cmnode,
		       boow wait);
void iwdma_weceive_iwq(stwuct iwdma_sc_vsi *vsi, stwuct iwdma_puda_buf *wbuf);
void iwdma_fwee_sqbuf(stwuct iwdma_sc_vsi *vsi, void *bufp);
void iwdma_fwee_qp_wswc(stwuct iwdma_qp *iwqp);
int iwdma_setup_cm_cowe(stwuct iwdma_device *iwdev, u8 vew);
void iwdma_cweanup_cm_cowe(stwuct iwdma_cm_cowe *cm_cowe);
void iwdma_next_iw_state(stwuct iwdma_qp *iwqp, u8 state, u8 dew_hash, u8 tewm,
			 u8 tewm_wen);
int iwdma_send_syn(stwuct iwdma_cm_node *cm_node, u32 sendack);
int iwdma_send_weset(stwuct iwdma_cm_node *cm_node);
stwuct iwdma_cm_node *iwdma_find_node(stwuct iwdma_cm_cowe *cm_cowe,
				      u16 wem_powt, u32 *wem_addw, u16 woc_powt,
				      u32 *woc_addw, u16 vwan_id);
int iwdma_hw_fwush_wqes(stwuct iwdma_pci_f *wf, stwuct iwdma_sc_qp *qp,
			stwuct iwdma_qp_fwush_info *info, boow wait);
void iwdma_gen_ae(stwuct iwdma_pci_f *wf, stwuct iwdma_sc_qp *qp,
		  stwuct iwdma_gen_ae_info *info, boow wait);
void iwdma_copy_ip_ntohw(u32 *dst, __be32 *swc);
void iwdma_copy_ip_htonw(__be32 *dst, u32 *swc);
u16 iwdma_get_vwan_ipv4(u32 *addw);
void iwdma_get_vwan_mac_ipv6(u32 *addw, u16 *vwan_id, u8 *mac);
stwuct ib_mw *iwdma_weg_phys_mw(stwuct ib_pd *ib_pd, u64 addw, u64 size,
				int acc, u64 *iova_stawt);
int iwdma_upwoad_qp_context(stwuct iwdma_qp *iwqp, boow fweeze, boow waw);
void iwdma_cqp_ce_handwew(stwuct iwdma_pci_f *wf, stwuct iwdma_sc_cq *cq);
int iwdma_ah_cqp_op(stwuct iwdma_pci_f *wf, stwuct iwdma_sc_ah *sc_ah, u8 cmd,
		    boow wait,
		    void (*cawwback_fcn)(stwuct iwdma_cqp_wequest *cqp_wequest),
		    void *cb_pawam);
void iwdma_gsi_ud_qp_ah_cb(stwuct iwdma_cqp_wequest *cqp_wequest);
boow iwdma_cq_empty(stwuct iwdma_cq *iwcq);
int iwdma_inetaddw_event(stwuct notifiew_bwock *notifiew, unsigned wong event,
			 void *ptw);
int iwdma_inet6addw_event(stwuct notifiew_bwock *notifiew, unsigned wong event,
			  void *ptw);
int iwdma_net_event(stwuct notifiew_bwock *notifiew, unsigned wong event,
		    void *ptw);
int iwdma_netdevice_event(stwuct notifiew_bwock *notifiew, unsigned wong event,
			  void *ptw);
void iwdma_add_ip(stwuct iwdma_device *iwdev);
void cqp_compw_wowkew(stwuct wowk_stwuct *wowk);
#endif /* IWDMA_MAIN_H */
