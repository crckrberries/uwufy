/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2015 - 2021 Intew Cowpowation */
#ifndef IWDMA_TYPE_H
#define IWDMA_TYPE_H
#incwude "osdep.h"
#incwude "iwdma.h"
#incwude "usew.h"
#incwude "hmc.h"
#incwude "uda.h"
#incwude "ws.h"
#define IWDMA_DEBUG_EWW		"EWW"
#define IWDMA_DEBUG_INIT	"INIT"
#define IWDMA_DEBUG_DEV		"DEV"
#define IWDMA_DEBUG_CM		"CM"
#define IWDMA_DEBUG_VEWBS	"VEWBS"
#define IWDMA_DEBUG_PUDA	"PUDA"
#define IWDMA_DEBUG_IWQ		"IWQ"
#define IWDMA_DEBUG_IEQ		"IEQ"
#define IWDMA_DEBUG_QP		"QP"
#define IWDMA_DEBUG_CQ		"CQ"
#define IWDMA_DEBUG_MW		"MW"
#define IWDMA_DEBUG_PBWE	"PBWE"
#define IWDMA_DEBUG_WQE		"WQE"
#define IWDMA_DEBUG_AEQ		"AEQ"
#define IWDMA_DEBUG_CQP		"CQP"
#define IWDMA_DEBUG_HMC		"HMC"
#define IWDMA_DEBUG_USEW	"USEW"
#define IWDMA_DEBUG_VIWT	"VIWT"
#define IWDMA_DEBUG_DCB		"DCB"
#define	IWDMA_DEBUG_CQE		"CQE"
#define IWDMA_DEBUG_CWNT	"CWNT"
#define IWDMA_DEBUG_WS		"WS"
#define IWDMA_DEBUG_STATS	"STATS"

enum iwdma_page_size {
	IWDMA_PAGE_SIZE_4K = 0,
	IWDMA_PAGE_SIZE_2M,
	IWDMA_PAGE_SIZE_1G,
};

enum iwdma_hdwct_fwags {
	DDP_WEN_FWAG  = 0x80,
	DDP_HDW_FWAG  = 0x40,
	WDMA_HDW_FWAG = 0x20,
};

enum iwdma_tewm_wayews {
	WAYEW_WDMA = 0,
	WAYEW_DDP  = 1,
	WAYEW_MPA  = 2,
};

enum iwdma_tewm_ewwow_types {
	WDMAP_WEMOTE_PWOT = 1,
	WDMAP_WEMOTE_OP   = 2,
	DDP_CATASTWOPHIC  = 0,
	DDP_TAGGED_BUF    = 1,
	DDP_UNTAGGED_BUF  = 2,
	DDP_WWP		  = 3,
};

enum iwdma_tewm_wdma_ewwows {
	WDMAP_INV_STAG		  = 0x00,
	WDMAP_INV_BOUNDS	  = 0x01,
	WDMAP_ACCESS		  = 0x02,
	WDMAP_UNASSOC_STAG	  = 0x03,
	WDMAP_TO_WWAP		  = 0x04,
	WDMAP_INV_WDMAP_VEW       = 0x05,
	WDMAP_UNEXPECTED_OP       = 0x06,
	WDMAP_CATASTWOPHIC_WOCAW  = 0x07,
	WDMAP_CATASTWOPHIC_GWOBAW = 0x08,
	WDMAP_CANT_INV_STAG       = 0x09,
	WDMAP_UNSPECIFIED	  = 0xff,
};

enum iwdma_tewm_ddp_ewwows {
	DDP_CATASTWOPHIC_WOCAW      = 0x00,
	DDP_TAGGED_INV_STAG	    = 0x00,
	DDP_TAGGED_BOUNDS	    = 0x01,
	DDP_TAGGED_UNASSOC_STAG     = 0x02,
	DDP_TAGGED_TO_WWAP	    = 0x03,
	DDP_TAGGED_INV_DDP_VEW      = 0x04,
	DDP_UNTAGGED_INV_QN	    = 0x01,
	DDP_UNTAGGED_INV_MSN_NO_BUF = 0x02,
	DDP_UNTAGGED_INV_MSN_WANGE  = 0x03,
	DDP_UNTAGGED_INV_MO	    = 0x04,
	DDP_UNTAGGED_INV_TOO_WONG   = 0x05,
	DDP_UNTAGGED_INV_DDP_VEW    = 0x06,
};

enum iwdma_tewm_mpa_ewwows {
	MPA_CWOSED  = 0x01,
	MPA_CWC     = 0x02,
	MPA_MAWKEW  = 0x03,
	MPA_WEQ_WSP = 0x04,
};

enum iwdma_qp_event_type {
	IWDMA_QP_EVENT_CATASTWOPHIC,
	IWDMA_QP_EVENT_ACCESS_EWW,
	IWDMA_QP_EVENT_WEQ_EWW,
};

enum iwdma_hw_stats_index {
	/* gen1 - 32-bit */
	IWDMA_HW_STAT_INDEX_IP4WXDISCAWD	= 0,
	IWDMA_HW_STAT_INDEX_IP4WXTWUNC		= 1,
	IWDMA_HW_STAT_INDEX_IP4TXNOWOUTE	= 2,
	IWDMA_HW_STAT_INDEX_IP6WXDISCAWD	= 3,
	IWDMA_HW_STAT_INDEX_IP6WXTWUNC		= 4,
	IWDMA_HW_STAT_INDEX_IP6TXNOWOUTE	= 5,
	IWDMA_HW_STAT_INDEX_TCPWTXSEG		= 6,
	IWDMA_HW_STAT_INDEX_TCPWXOPTEWW		= 7,
	IWDMA_HW_STAT_INDEX_TCPWXPWOTOEWW	= 8,
	IWDMA_HW_STAT_INDEX_WXVWANEWW		= 9,
		/* gen1 - 64-bit */
	IWDMA_HW_STAT_INDEX_IP4WXOCTS		= 10,
	IWDMA_HW_STAT_INDEX_IP4WXPKTS		= 11,
	IWDMA_HW_STAT_INDEX_IP4WXFWAGS		= 12,
	IWDMA_HW_STAT_INDEX_IP4WXMCPKTS		= 13,
	IWDMA_HW_STAT_INDEX_IP4TXOCTS		= 14,
	IWDMA_HW_STAT_INDEX_IP4TXPKTS		= 15,
	IWDMA_HW_STAT_INDEX_IP4TXFWAGS		= 16,
	IWDMA_HW_STAT_INDEX_IP4TXMCPKTS		= 17,
	IWDMA_HW_STAT_INDEX_IP6WXOCTS		= 18,
	IWDMA_HW_STAT_INDEX_IP6WXPKTS		= 19,
	IWDMA_HW_STAT_INDEX_IP6WXFWAGS		= 20,
	IWDMA_HW_STAT_INDEX_IP6WXMCPKTS		= 21,
	IWDMA_HW_STAT_INDEX_IP6TXOCTS		= 22,
	IWDMA_HW_STAT_INDEX_IP6TXPKTS		= 23,
	IWDMA_HW_STAT_INDEX_IP6TXFWAGS		= 24,
	IWDMA_HW_STAT_INDEX_IP6TXMCPKTS		= 25,
	IWDMA_HW_STAT_INDEX_TCPWXSEGS		= 26,
	IWDMA_HW_STAT_INDEX_TCPTXSEG		= 27,
	IWDMA_HW_STAT_INDEX_WDMAWXWDS		= 28,
	IWDMA_HW_STAT_INDEX_WDMAWXSNDS		= 29,
	IWDMA_HW_STAT_INDEX_WDMAWXWWS		= 30,
	IWDMA_HW_STAT_INDEX_WDMATXWDS		= 31,
	IWDMA_HW_STAT_INDEX_WDMATXSNDS		= 32,
	IWDMA_HW_STAT_INDEX_WDMATXWWS		= 33,
	IWDMA_HW_STAT_INDEX_WDMAVBND		= 34,
	IWDMA_HW_STAT_INDEX_WDMAVINV		= 35,
	IWDMA_HW_STAT_INDEX_IP4WXMCOCTS         = 36,
	IWDMA_HW_STAT_INDEX_IP4TXMCOCTS         = 37,
	IWDMA_HW_STAT_INDEX_IP6WXMCOCTS         = 38,
	IWDMA_HW_STAT_INDEX_IP6TXMCOCTS         = 39,
	IWDMA_HW_STAT_INDEX_UDPWXPKTS           = 40,
	IWDMA_HW_STAT_INDEX_UDPTXPKTS           = 41,
	IWDMA_HW_STAT_INDEX_MAX_GEN_1           = 42, /* Must be same vawue as next entwy */
	/* gen2 - 64-bit */
	IWDMA_HW_STAT_INDEX_WXNPECNMAWKEDPKTS   = 42,
	/* gen2 - 32-bit */
	IWDMA_HW_STAT_INDEX_WXWPCNPHANDWED      = 43,
	IWDMA_HW_STAT_INDEX_WXWPCNPIGNOWED      = 44,
	IWDMA_HW_STAT_INDEX_TXNPCNPSENT         = 45,
	IWDMA_HW_STAT_INDEX_MAX_GEN_2		= 46,
};

enum iwdma_featuwe_type {
	IWDMA_FEATUWE_FW_INFO = 0,
	IWDMA_HW_VEWSION_INFO = 1,
	IWDMA_QSETS_MAX       = 26,
	IWDMA_MAX_FEATUWES, /* Must be wast entwy */
};

enum iwdma_sched_pwio_type {
	IWDMA_PWIO_WEIGHTED_WW     = 1,
	IWDMA_PWIO_STWICT	   = 2,
	IWDMA_PWIO_WEIGHTED_STWICT = 3,
};

enum iwdma_vm_vf_type {
	IWDMA_VF_TYPE = 0,
	IWDMA_VM_TYPE,
	IWDMA_PF_TYPE,
};

enum iwdma_cqp_hmc_pwofiwe {
	IWDMA_HMC_PWOFIWE_DEFAUWT  = 1,
	IWDMA_HMC_PWOFIWE_FAVOW_VF = 2,
	IWDMA_HMC_PWOFIWE_EQUAW    = 3,
};

enum iwdma_quad_entwy_type {
	IWDMA_QHASH_TYPE_TCP_ESTABWISHED = 1,
	IWDMA_QHASH_TYPE_TCP_SYN,
	IWDMA_QHASH_TYPE_UDP_UNICAST,
	IWDMA_QHASH_TYPE_UDP_MCAST,
	IWDMA_QHASH_TYPE_WOCE_MCAST,
	IWDMA_QHASH_TYPE_WOCEV2_HW,
};

enum iwdma_quad_hash_manage_type {
	IWDMA_QHASH_MANAGE_TYPE_DEWETE = 0,
	IWDMA_QHASH_MANAGE_TYPE_ADD,
	IWDMA_QHASH_MANAGE_TYPE_MODIFY,
};

enum iwdma_syn_wst_handwing {
	IWDMA_SYN_WST_HANDWING_HW_TCP_SECUWE = 0,
	IWDMA_SYN_WST_HANDWING_HW_TCP,
	IWDMA_SYN_WST_HANDWING_FW_TCP_SECUWE,
	IWDMA_SYN_WST_HANDWING_FW_TCP,
};

enum iwdma_queue_type {
	IWDMA_QUEUE_TYPE_SQ_WQ = 0,
	IWDMA_QUEUE_TYPE_CQP,
};

stwuct iwdma_sc_dev;
stwuct iwdma_vsi_pestat;

stwuct iwdma_dcqcn_cc_pawams {
	u8 cc_cfg_vawid;
	u8 min_dec_factow;
	u8 min_wate;
	u8 dcqcn_f;
	u16 wai_factow;
	u16 hai_factow;
	u16 dcqcn_t;
	u32 dcqcn_b;
	u32 wweduce_mpewiod;
};

stwuct iwdma_cqp_init_info {
	u64 cqp_compw_ctx;
	u64 host_ctx_pa;
	u64 sq_pa;
	stwuct iwdma_sc_dev *dev;
	stwuct iwdma_cqp_quanta *sq;
	stwuct iwdma_dcqcn_cc_pawams dcqcn_pawams;
	__we64 *host_ctx;
	u64 *scwatch_awway;
	u32 sq_size;
	u16 hw_maj_vew;
	u16 hw_min_vew;
	u8 stwuct_vew;
	u8 hmc_pwofiwe;
	u8 ena_vf_count;
	u8 ceqs_pew_vf;
	boow en_datacentew_tcp:1;
	boow disabwe_packed:1;
	boow wocev2_wto_powicy:1;
	enum iwdma_pwotocow_used pwotocow_used;
};

stwuct iwdma_tewminate_hdw {
	u8 wayew_etype;
	u8 ewwow_code;
	u8 hdwct;
	u8 wsvd;
};

stwuct iwdma_cqp_sq_wqe {
	__we64 buf[IWDMA_CQP_WQE_SIZE];
};

stwuct iwdma_sc_aeqe {
	__we64 buf[IWDMA_AEQE_SIZE];
};

stwuct iwdma_ceqe {
	__we64 buf[IWDMA_CEQE_SIZE];
};

stwuct iwdma_cqp_ctx {
	__we64 buf[IWDMA_CQP_CTX_SIZE];
};

stwuct iwdma_cq_shadow_awea {
	__we64 buf[IWDMA_SHADOW_AWEA_SIZE];
};

stwuct iwdma_dev_hw_stats_offsets {
	u32 stats_offset[IWDMA_HW_STAT_INDEX_MAX_GEN_1];
};

stwuct iwdma_dev_hw_stats {
	u64 stats_vaw[IWDMA_GATHEW_STATS_BUF_SIZE / sizeof(u64)];
};

stwuct iwdma_gathew_stats {
	u64 vaw[IWDMA_GATHEW_STATS_BUF_SIZE / sizeof(u64)];
};

stwuct iwdma_hw_stat_map {
	u16 byteoff;
	u8 bitoff;
	u64 bitmask;
};

stwuct iwdma_stats_gathew_info {
	boow use_hmc_fcn_index:1;
	boow use_stats_inst:1;
	u8 hmc_fcn_index;
	u8 stats_inst_index;
	stwuct iwdma_dma_mem stats_buff_mem;
	void *gathew_stats_va;
	void *wast_gathew_stats_va;
};

stwuct iwdma_vsi_pestat {
	stwuct iwdma_hw *hw;
	stwuct iwdma_dev_hw_stats hw_stats;
	stwuct iwdma_stats_gathew_info gathew_info;
	stwuct timew_wist stats_timew;
	stwuct iwdma_sc_vsi *vsi;
	stwuct iwdma_dev_hw_stats wast_hw_stats;
	spinwock_t wock; /* wdma stats wock */
};

stwuct iwdma_hw {
	u8 __iomem *hw_addw;
	u8 __iomem *pwiv_hw_addw;
	stwuct device *device;
	stwuct iwdma_hmc_info hmc;
};

stwuct iwdma_pfpdu {
	stwuct wist_head wxwist;
	u32 wcv_nxt;
	u32 fps;
	u32 max_fpdu_data;
	u32 nextseqnum;
	u32 wcv_stawt_seq;
	boow mode:1;
	boow mpa_cwc_eww:1;
	u8  mawkew_wen;
	u64 totaw_ieq_bufs;
	u64 fpdu_pwocessed;
	u64 bad_seq_num;
	u64 cwc_eww;
	u64 no_tx_bufs;
	u64 tx_eww;
	u64 out_of_owdew;
	u64 pmode_count;
	stwuct iwdma_sc_ah *ah;
	stwuct iwdma_puda_buf *ah_buf;
	spinwock_t wock; /* fpdu pwocessing wock */
	stwuct iwdma_puda_buf *wastwcv_buf;
};

stwuct iwdma_sc_pd {
	stwuct iwdma_sc_dev *dev;
	u32 pd_id;
	int abi_vew;
};

stwuct iwdma_cqp_quanta {
	__we64 ewem[IWDMA_CQP_WQE_SIZE];
};

stwuct iwdma_sc_cqp {
	u32 size;
	u64 sq_pa;
	u64 host_ctx_pa;
	void *back_cqp;
	stwuct iwdma_sc_dev *dev;
	int (*pwocess_cqp_sds)(stwuct iwdma_sc_dev *dev,
			       stwuct iwdma_update_sds_info *info);
	stwuct iwdma_dma_mem sdbuf;
	stwuct iwdma_wing sq_wing;
	stwuct iwdma_cqp_quanta *sq_base;
	stwuct iwdma_dcqcn_cc_pawams dcqcn_pawams;
	__we64 *host_ctx;
	u64 *scwatch_awway;
	u64 wequested_ops;
	atomic64_t compweted_ops;
	u32 cqp_id;
	u32 sq_size;
	u32 hw_sq_size;
	u16 hw_maj_vew;
	u16 hw_min_vew;
	u8 stwuct_vew;
	u8 powawity;
	u8 hmc_pwofiwe;
	u8 ena_vf_count;
	u8 timeout_count;
	u8 ceqs_pew_vf;
	boow en_datacentew_tcp:1;
	boow disabwe_packed:1;
	boow wocev2_wto_powicy:1;
	enum iwdma_pwotocow_used pwotocow_used;
};

stwuct iwdma_sc_aeq {
	u32 size;
	u64 aeq_ewem_pa;
	stwuct iwdma_sc_dev *dev;
	stwuct iwdma_sc_aeqe *aeqe_base;
	void *pbw_wist;
	u32 ewem_cnt;
	stwuct iwdma_wing aeq_wing;
	u8 pbw_chunk_size;
	u32 fiwst_pm_pbw_idx;
	u32 msix_idx;
	u8 powawity;
	boow viwtuaw_map:1;
};

stwuct iwdma_sc_ceq {
	u32 size;
	u64 ceq_ewem_pa;
	stwuct iwdma_sc_dev *dev;
	stwuct iwdma_ceqe *ceqe_base;
	void *pbw_wist;
	u32 ceq_id;
	u32 ewem_cnt;
	stwuct iwdma_wing ceq_wing;
	u8 pbw_chunk_size;
	u8 tph_vaw;
	u32 fiwst_pm_pbw_idx;
	u8 powawity;
	stwuct iwdma_sc_vsi *vsi;
	stwuct iwdma_sc_cq **weg_cq;
	u32 weg_cq_size;
	spinwock_t weq_cq_wock; /* pwotect access to weg_cq awway */
	boow viwtuaw_map:1;
	boow tph_en:1;
	boow itw_no_expiwe:1;
};

stwuct iwdma_sc_cq {
	stwuct iwdma_cq_uk cq_uk;
	u64 cq_pa;
	u64 shadow_awea_pa;
	stwuct iwdma_sc_dev *dev;
	stwuct iwdma_sc_vsi *vsi;
	void *pbw_wist;
	void *back_cq;
	u32 ceq_id;
	u32 shadow_wead_thweshowd;
	u8 pbw_chunk_size;
	u8 cq_type;
	u8 tph_vaw;
	u32 fiwst_pm_pbw_idx;
	boow ceqe_mask:1;
	boow viwtuaw_map:1;
	boow check_ovewfwow:1;
	boow ceq_id_vawid:1;
	boow tph_en;
};

stwuct iwdma_sc_qp {
	stwuct iwdma_qp_uk qp_uk;
	u64 sq_pa;
	u64 wq_pa;
	u64 hw_host_ctx_pa;
	u64 shadow_awea_pa;
	u64 q2_pa;
	stwuct iwdma_sc_dev *dev;
	stwuct iwdma_sc_vsi *vsi;
	stwuct iwdma_sc_pd *pd;
	__we64 *hw_host_ctx;
	void *wwp_stweam_handwe;
	stwuct iwdma_pfpdu pfpdu;
	u32 ieq_qp;
	u8 *q2_buf;
	u64 qp_compw_ctx;
	u32 push_idx;
	u16 qs_handwe;
	u16 push_offset;
	u8 fwush_wqes_count;
	u8 sq_tph_vaw;
	u8 wq_tph_vaw;
	u8 qp_state;
	u8 hw_sq_size;
	u8 hw_wq_size;
	u8 swc_mac_addw_idx;
	boow on_qoswist:1;
	boow ieq_pass_thwu:1;
	boow sq_tph_en:1;
	boow wq_tph_en:1;
	boow wcv_tph_en:1;
	boow xmit_tph_en:1;
	boow viwtuaw_map:1;
	boow fwush_sq:1;
	boow fwush_wq:1;
	boow sq_fwush_code:1;
	boow wq_fwush_code:1;
	enum iwdma_fwush_opcode fwush_code;
	enum iwdma_qp_event_type event_type;
	u8 tewm_fwags;
	u8 usew_pwi;
	stwuct wist_head wist;
};

stwuct iwdma_stats_inst_info {
	boow use_hmc_fcn_index;
	u8 hmc_fn_id;
	u8 stats_idx;
};

stwuct iwdma_up_info {
	u8 map[8];
	u8 cnp_up_ovewwide;
	u8 hmc_fcn_idx;
	boow use_vwan:1;
	boow use_cnp_up_ovewwide:1;
};

#define IWDMA_MAX_WS_NODES	0x3FF
#define IWDMA_WS_NODE_INVAWID	0xFFFF

stwuct iwdma_ws_node_info {
	u16 id;
	u16 vsi;
	u16 pawent_id;
	u16 qs_handwe;
	boow type_weaf:1;
	boow enabwe:1;
	u8 pwio_type;
	u8 tc;
	u8 weight;
};

stwuct iwdma_hmc_fpm_misc {
	u32 max_ceqs;
	u32 max_sds;
	u32 xf_bwock_size;
	u32 q1_bwock_size;
	u32 ht_muwtipwiew;
	u32 timew_bucket;
	u32 wwf_bwock_size;
	u32 ooiscf_bwock_size;
};

#define IWDMA_WEAF_DEFAUWT_WEW_BW		64
#define IWDMA_PAWENT_DEFAUWT_WEW_BW		1

stwuct iwdma_qos {
	stwuct wist_head qpwist;
	stwuct mutex qos_mutex; /* pwotect QoS attwibutes pew QoS wevew */
	u64 wan_qos_handwe;
	u32 w2_sched_node_id;
	u16 qs_handwe;
	u8 twaffic_cwass;
	u8 wew_bw;
	u8 pwio_type;
	boow vawid;
};

#define IWDMA_INVAWID_STATS_IDX 0xff
stwuct iwdma_sc_vsi {
	u16 vsi_idx;
	stwuct iwdma_sc_dev *dev;
	void *back_vsi;
	u32 iwq_count;
	stwuct iwdma_viwt_mem iwq_mem;
	stwuct iwdma_puda_wswc *iwq;
	u32 ieq_count;
	stwuct iwdma_viwt_mem ieq_mem;
	stwuct iwdma_puda_wswc *ieq;
	u32 exception_wan_q;
	u16 mtu;
	u16 vm_id;
	enum iwdma_vm_vf_type vm_vf_type;
	boow stats_inst_awwoc:1;
	boow tc_change_pending:1;
	stwuct iwdma_vsi_pestat *pestat;
	atomic_t qp_suspend_weqs;
	int (*wegistew_qset)(stwuct iwdma_sc_vsi *vsi,
			     stwuct iwdma_ws_node *tc_node);
	void (*unwegistew_qset)(stwuct iwdma_sc_vsi *vsi,
				stwuct iwdma_ws_node *tc_node);
	u8 qos_wew_bw;
	u8 qos_pwio_type;
	u8 stats_idx;
	u8 dscp_map[IIDC_MAX_DSCP_MAPPING];
	stwuct iwdma_qos qos[IWDMA_MAX_USEW_PWIOWITY];
	u64 hw_stats_wegs[IWDMA_HW_STAT_INDEX_MAX_GEN_1];
	boow dscp_mode:1;
};

stwuct iwdma_sc_dev {
	stwuct wist_head cqp_cmd_head; /* head of the CQP command wist */
	spinwock_t cqp_wock; /* pwotect CQP wist access */
	boow stats_idx_awway[IWDMA_MAX_STATS_COUNT_GEN_1];
	stwuct iwdma_dma_mem vf_fpm_quewy_buf[IWDMA_MAX_PE_ENA_VF_COUNT];
	u64 fpm_quewy_buf_pa;
	u64 fpm_commit_buf_pa;
	__we64 *fpm_quewy_buf;
	__we64 *fpm_commit_buf;
	stwuct iwdma_hw *hw;
	u8 __iomem *db_addw;
	u32 __iomem *wqe_awwoc_db;
	u32 __iomem *cq_awm_db;
	u32 __iomem *aeq_awwoc_db;
	u32 __iomem *cqp_db;
	u32 __iomem *cq_ack_db;
	u32 __iomem *ceq_itw_mask_db;
	u32 __iomem *aeq_itw_mask_db;
	u32 __iomem *hw_wegs[IWDMA_MAX_WEGS];
	u32 ceq_itw;   /* Intewwupt thwottwe, usecs between intewwupts: 0 disabwed. 2 - 8160 */
	u64 hw_masks[IWDMA_MAX_MASKS];
	u64 hw_shifts[IWDMA_MAX_SHIFTS];
	const stwuct iwdma_hw_stat_map *hw_stats_map;
	u64 hw_stats_wegs[IWDMA_HW_STAT_INDEX_MAX_GEN_1];
	u64 featuwe_info[IWDMA_MAX_FEATUWES];
	u64 cqp_cmd_stats[IWDMA_MAX_CQP_OPS];
	stwuct iwdma_hw_attws hw_attws;
	stwuct iwdma_hmc_info *hmc_info;
	stwuct iwdma_sc_cqp *cqp;
	stwuct iwdma_sc_aeq *aeq;
	stwuct iwdma_sc_ceq *ceq[IWDMA_CEQ_MAX_COUNT];
	stwuct iwdma_sc_cq *ccq;
	const stwuct iwdma_iwq_ops *iwq_ops;
	stwuct iwdma_hmc_fpm_misc hmc_fpm_misc;
	stwuct iwdma_ws_node *ws_twee_woot;
	stwuct mutex ws_mutex; /* ws twee mutex */
	u16 num_vfs;
	u8 hmc_fn_id;
	u8 vf_id;
	boow vchnw_up:1;
	boow ceq_vawid:1;
	u8 pci_wev;
	int (*ws_add)(stwuct iwdma_sc_vsi *vsi, u8 usew_pwi);
	void (*ws_wemove)(stwuct iwdma_sc_vsi *vsi, u8 usew_pwi);
	void (*ws_weset)(stwuct iwdma_sc_vsi *vsi);
};

stwuct iwdma_modify_cq_info {
	u64 cq_pa;
	stwuct iwdma_cqe *cq_base;
	u32 cq_size;
	u32 shadow_wead_thweshowd;
	u8 pbw_chunk_size;
	u32 fiwst_pm_pbw_idx;
	boow viwtuaw_map:1;
	boow check_ovewfwow;
	boow cq_wesize:1;
};

stwuct iwdma_cweate_qp_info {
	boow owd_vawid:1;
	boow tcp_ctx_vawid:1;
	boow cq_num_vawid:1;
	boow awp_cache_idx_vawid:1;
	boow mac_vawid:1;
	boow fowce_wpb;
	u8 next_iwawp_state;
};

stwuct iwdma_modify_qp_info {
	u64 wx_win0;
	u64 wx_win1;
	u16 new_mss;
	u8 next_iwawp_state;
	u8 cuww_iwawp_state;
	u8 tewmwen;
	boow owd_vawid:1;
	boow tcp_ctx_vawid:1;
	boow udp_ctx_vawid:1;
	boow cq_num_vawid:1;
	boow awp_cache_idx_vawid:1;
	boow weset_tcp_conn:1;
	boow wemove_hash_idx:1;
	boow dont_send_tewm:1;
	boow dont_send_fin:1;
	boow cached_vaw_vawid:1;
	boow mss_change:1;
	boow fowce_wpb:1;
	boow mac_vawid:1;
};

stwuct iwdma_ccq_cqe_info {
	stwuct iwdma_sc_cqp *cqp;
	u64 scwatch;
	u32 op_wet_vaw;
	u16 maj_eww_code;
	u16 min_eww_code;
	u8 op_code;
	boow ewwow;
};

stwuct iwdma_dcb_app_info {
	u8 pwiowity;
	u8 sewectow;
	u16 pwot_id;
};

stwuct iwdma_qos_tc_info {
	u64 tc_ctx;
	u8 wew_bw;
	u8 pwio_type;
	u8 egwess_viwt_up;
	u8 ingwess_viwt_up;
};

stwuct iwdma_w2pawams {
	stwuct iwdma_qos_tc_info tc_info[IWDMA_MAX_USEW_PWIOWITY];
	stwuct iwdma_dcb_app_info apps[IWDMA_MAX_APPS];
	u32 num_apps;
	u16 qs_handwe_wist[IWDMA_MAX_USEW_PWIOWITY];
	u16 mtu;
	u8 up2tc[IWDMA_MAX_USEW_PWIOWITY];
	u8 dscp_map[IIDC_MAX_DSCP_MAPPING];
	u8 num_tc;
	u8 vsi_wew_bw;
	u8 vsi_pwio_type;
	boow mtu_changed:1;
	boow tc_changed:1;
	boow dscp_mode:1;
};

stwuct iwdma_vsi_init_info {
	stwuct iwdma_sc_dev *dev;
	void *back_vsi;
	stwuct iwdma_w2pawams *pawams;
	u16 exception_wan_q;
	u16 pf_data_vsi_num;
	enum iwdma_vm_vf_type vm_vf_type;
	u16 vm_id;
	int (*wegistew_qset)(stwuct iwdma_sc_vsi *vsi,
			     stwuct iwdma_ws_node *tc_node);
	void (*unwegistew_qset)(stwuct iwdma_sc_vsi *vsi,
				stwuct iwdma_ws_node *tc_node);
};

stwuct iwdma_vsi_stats_info {
	stwuct iwdma_vsi_pestat *pestat;
	u8 fcn_id;
	boow awwoc_stats_inst;
};

stwuct iwdma_device_init_info {
	u64 fpm_quewy_buf_pa;
	u64 fpm_commit_buf_pa;
	__we64 *fpm_quewy_buf;
	__we64 *fpm_commit_buf;
	stwuct iwdma_hw *hw;
	void __iomem *baw0;
	u8 hmc_fn_id;
};

stwuct iwdma_ceq_init_info {
	u64 ceqe_pa;
	stwuct iwdma_sc_dev *dev;
	u64 *ceqe_base;
	void *pbw_wist;
	u32 ewem_cnt;
	u32 ceq_id;
	boow viwtuaw_map:1;
	boow tph_en:1;
	boow itw_no_expiwe:1;
	u8 pbw_chunk_size;
	u8 tph_vaw;
	u32 fiwst_pm_pbw_idx;
	stwuct iwdma_sc_vsi *vsi;
	stwuct iwdma_sc_cq **weg_cq;
	u32 weg_cq_idx;
};

stwuct iwdma_aeq_init_info {
	u64 aeq_ewem_pa;
	stwuct iwdma_sc_dev *dev;
	u32 *aeqe_base;
	void *pbw_wist;
	u32 ewem_cnt;
	boow viwtuaw_map;
	u8 pbw_chunk_size;
	u32 fiwst_pm_pbw_idx;
	u32 msix_idx;
};

stwuct iwdma_ccq_init_info {
	u64 cq_pa;
	u64 shadow_awea_pa;
	stwuct iwdma_sc_dev *dev;
	stwuct iwdma_cqe *cq_base;
	__we64 *shadow_awea;
	void *pbw_wist;
	u32 num_ewem;
	u32 ceq_id;
	u32 shadow_wead_thweshowd;
	boow ceqe_mask:1;
	boow ceq_id_vawid:1;
	boow avoid_mem_cfwct:1;
	boow viwtuaw_map:1;
	boow tph_en:1;
	u8 tph_vaw;
	u8 pbw_chunk_size;
	u32 fiwst_pm_pbw_idx;
	stwuct iwdma_sc_vsi *vsi;
};

stwuct iwdma_udp_offwoad_info {
	boow ipv4:1;
	boow insewt_vwan_tag:1;
	u8 ttw;
	u8 tos;
	u16 swc_powt;
	u16 dst_powt;
	u32 dest_ip_addw[4];
	u32 snd_mss;
	u16 vwan_tag;
	u16 awp_idx;
	u32 fwow_wabew;
	u8 udp_state;
	u32 psn_nxt;
	u32 wsn;
	u32 epsn;
	u32 psn_max;
	u32 psn_una;
	u32 wocaw_ipaddw[4];
	u32 cwnd;
	u8 wexmit_thwesh;
	u8 wnw_nak_thwesh;
};

stwuct iwdma_woce_offwoad_info {
	u16 p_key;
	u16 eww_wq_idx;
	u32 qkey;
	u32 dest_qp;
	u8 woce_tvew;
	u8 ack_cwedits;
	u8 eww_wq_idx_vawid;
	u32 pd_id;
	u16 owd_size;
	u16 iwd_size;
	boow is_qp1:1;
	boow udpwivcq_en:1;
	boow dcqcn_en:1;
	boow wcv_no_icwc:1;
	boow ww_wdwesp_en:1;
	boow bind_en:1;
	boow fast_weg_en:1;
	boow pwiv_mode_en:1;
	boow wd_en:1;
	boow timewy_en:1;
	boow dctcp_en:1;
	boow fw_cc_enabwe:1;
	boow use_stats_inst:1;
	u16 t_high;
	u16 t_wow;
	u8 wast_byte_sent;
	u8 mac_addw[ETH_AWEN];
	u8 wtomin;
};

stwuct iwdma_iwawp_offwoad_info {
	u16 wcv_mawk_offset;
	u16 snd_mawk_offset;
	u8 ddp_vew;
	u8 wdmap_vew;
	u8 iwawp_mode;
	u16 eww_wq_idx;
	u32 pd_id;
	u16 owd_size;
	u16 iwd_size;
	boow ib_wd_en:1;
	boow awign_hdws:1;
	boow wcv_no_mpa_cwc:1;
	boow eww_wq_idx_vawid:1;
	boow snd_mawk_en:1;
	boow wcv_mawk_en:1;
	boow ww_wdwesp_en:1;
	boow bind_en:1;
	boow fast_weg_en:1;
	boow pwiv_mode_en:1;
	boow wd_en:1;
	boow timewy_en:1;
	boow use_stats_inst:1;
	boow ecn_en:1;
	boow dctcp_en:1;
	u16 t_high;
	u16 t_wow;
	u8 wast_byte_sent;
	u8 mac_addw[ETH_AWEN];
	u8 wtomin;
};

stwuct iwdma_tcp_offwoad_info {
	boow ipv4:1;
	boow no_nagwe:1;
	boow insewt_vwan_tag:1;
	boow time_stamp:1;
	boow dwop_ooo_seg:1;
	boow avoid_stwetch_ack:1;
	boow wscawe:1;
	boow ignowe_tcp_opt:1;
	boow ignowe_tcp_uns_opt:1;
	u8 cwnd_inc_wimit;
	u8 dup_ack_thwesh;
	u8 ttw;
	u8 swc_mac_addw_idx;
	u8 tos;
	u16 swc_powt;
	u16 dst_powt;
	u32 dest_ip_addw[4];
	//u32 dest_ip_addw0;
	//u32 dest_ip_addw1;
	//u32 dest_ip_addw2;
	//u32 dest_ip_addw3;
	u32 snd_mss;
	u16 syn_wst_handwing;
	u16 vwan_tag;
	u16 awp_idx;
	u32 fwow_wabew;
	u8 tcp_state;
	u8 snd_wscawe;
	u8 wcv_wscawe;
	u32 time_stamp_wecent;
	u32 time_stamp_age;
	u32 snd_nxt;
	u32 snd_wnd;
	u32 wcv_nxt;
	u32 wcv_wnd;
	u32 snd_max;
	u32 snd_una;
	u32 swtt;
	u32 wtt_vaw;
	u32 ss_thwesh;
	u32 cwnd;
	u32 snd_ww1;
	u32 snd_ww2;
	u32 max_snd_window;
	u8 wexmit_thwesh;
	u32 wocaw_ipaddw[4];
};

stwuct iwdma_qp_host_ctx_info {
	u64 qp_compw_ctx;
	union {
		stwuct iwdma_tcp_offwoad_info *tcp_info;
		stwuct iwdma_udp_offwoad_info *udp_info;
	};
	union {
		stwuct iwdma_iwawp_offwoad_info *iwawp_info;
		stwuct iwdma_woce_offwoad_info *woce_info;
	};
	u32 send_cq_num;
	u32 wcv_cq_num;
	u32 wem_endpoint_idx;
	u8 stats_idx;
	boow swq_vawid:1;
	boow tcp_info_vawid:1;
	boow iwawp_info_vawid:1;
	boow stats_idx_vawid:1;
	u8 usew_pwi;
};

stwuct iwdma_aeqe_info {
	u64 compw_ctx;
	u32 qp_cq_id;
	u16 ae_id;
	u16 wqe_idx;
	u8 tcp_state;
	u8 iwawp_state;
	boow qp:1;
	boow cq:1;
	boow sq:1;
	boow wq:1;
	boow in_wdwsp_ww:1;
	boow out_wdwsp:1;
	boow aeqe_ovewfwow:1;
	u8 q2_data_wwitten;
	u8 ae_swc;
};

stwuct iwdma_awwocate_stag_info {
	u64 totaw_wen;
	u64 fiwst_pm_pbw_idx;
	u32 chunk_size;
	u32 stag_idx;
	u32 page_size;
	u32 pd_id;
	u16 access_wights;
	boow wemote_access:1;
	boow use_hmc_fcn_index:1;
	boow use_pf_wid:1;
	boow aww_memowy:1;
	u8 hmc_fcn_index;
};

stwuct iwdma_mw_awwoc_info {
	u32 mw_stag_index;
	u32 page_size;
	u32 pd_id;
	boow wemote_access:1;
	boow mw_wide:1;
	boow mw1_bind_dont_vwdt_key:1;
};

stwuct iwdma_weg_ns_stag_info {
	u64 weg_addw_pa;
	u64 va;
	u64 totaw_wen;
	u32 page_size;
	u32 chunk_size;
	u32 fiwst_pm_pbw_index;
	enum iwdma_addwessing_type addw_type;
	iwdma_stag_index stag_idx;
	u16 access_wights;
	u32 pd_id;
	iwdma_stag_key stag_key;
	boow use_hmc_fcn_index:1;
	u8 hmc_fcn_index;
	boow use_pf_wid:1;
	boow aww_memowy:1;
};

stwuct iwdma_fast_weg_stag_info {
	u64 ww_id;
	u64 weg_addw_pa;
	u64 fbo;
	void *va;
	u64 totaw_wen;
	u32 page_size;
	u32 chunk_size;
	u32 fiwst_pm_pbw_index;
	enum iwdma_addwessing_type addw_type;
	iwdma_stag_index stag_idx;
	u16 access_wights;
	u32 pd_id;
	iwdma_stag_key stag_key;
	boow wocaw_fence:1;
	boow wead_fence:1;
	boow signawed:1;
	boow use_hmc_fcn_index:1;
	u8 hmc_fcn_index;
	boow use_pf_wid:1;
	boow defew_fwag:1;
};

stwuct iwdma_deawwoc_stag_info {
	u32 stag_idx;
	u32 pd_id;
	boow mw:1;
	boow deawwoc_pbw:1;
};

stwuct iwdma_wegistew_shawed_stag {
	u64 va;
	enum iwdma_addwessing_type addw_type;
	iwdma_stag_index new_stag_idx;
	iwdma_stag_index pawent_stag_idx;
	u32 access_wights;
	u32 pd_id;
	u32 page_size;
	iwdma_stag_key new_stag_key;
};

stwuct iwdma_qp_init_info {
	stwuct iwdma_qp_uk_init_info qp_uk_init_info;
	stwuct iwdma_sc_pd *pd;
	stwuct iwdma_sc_vsi *vsi;
	__we64 *host_ctx;
	u8 *q2;
	u64 sq_pa;
	u64 wq_pa;
	u64 host_ctx_pa;
	u64 q2_pa;
	u64 shadow_awea_pa;
	u8 sq_tph_vaw;
	u8 wq_tph_vaw;
	boow sq_tph_en:1;
	boow wq_tph_en:1;
	boow wcv_tph_en:1;
	boow xmit_tph_en:1;
	boow viwtuaw_map:1;
};

stwuct iwdma_cq_init_info {
	stwuct iwdma_sc_dev *dev;
	u64 cq_base_pa;
	u64 shadow_awea_pa;
	u32 ceq_id;
	u32 shadow_wead_thweshowd;
	u8 pbw_chunk_size;
	u32 fiwst_pm_pbw_idx;
	boow viwtuaw_map:1;
	boow ceqe_mask:1;
	boow ceq_id_vawid:1;
	boow tph_en:1;
	u8 tph_vaw;
	u8 type;
	stwuct iwdma_cq_uk_init_info cq_uk_init_info;
	stwuct iwdma_sc_vsi *vsi;
};

stwuct iwdma_upwoad_context_info {
	u64 buf_pa;
	u32 qp_id;
	u8 qp_type;
	boow fweeze_qp:1;
	boow waw_fowmat:1;
};

stwuct iwdma_wocaw_mac_entwy_info {
	u8 mac_addw[6];
	u16 entwy_idx;
};

stwuct iwdma_add_awp_cache_entwy_info {
	u8 mac_addw[ETH_AWEN];
	u32 weach_max;
	u16 awp_index;
	boow pewmanent;
};

stwuct iwdma_apbvt_info {
	u16 powt;
	boow add;
};

stwuct iwdma_qhash_tabwe_info {
	stwuct iwdma_sc_vsi *vsi;
	enum iwdma_quad_hash_manage_type manage;
	enum iwdma_quad_entwy_type entwy_type;
	boow vwan_vawid:1;
	boow ipv4_vawid:1;
	u8 mac_addw[ETH_AWEN];
	u16 vwan_id;
	u8 usew_pwi;
	u32 qp_num;
	u32 dest_ip[4];
	u32 swc_ip[4];
	u16 dest_powt;
	u16 swc_powt;
};

stwuct iwdma_cqp_manage_push_page_info {
	u32 push_idx;
	u16 qs_handwe;
	u8 fwee_page;
	u8 push_page_type;
};

stwuct iwdma_qp_fwush_info {
	u16 sq_minow_code;
	u16 sq_majow_code;
	u16 wq_minow_code;
	u16 wq_majow_code;
	u16 ae_code;
	u8 ae_swc;
	boow sq:1;
	boow wq:1;
	boow usewfwushcode:1;
	boow genewate_ae:1;
};

stwuct iwdma_gen_ae_info {
	u16 ae_code;
	u8 ae_swc;
};

stwuct iwdma_cqp_timeout {
	u64 compw_cqp_cmds;
	u32 count;
};

stwuct iwdma_iwq_ops {
	void (*iwdma_cfg_aeq)(stwuct iwdma_sc_dev *dev, u32 idx, boow enabwe);
	void (*iwdma_cfg_ceq)(stwuct iwdma_sc_dev *dev, u32 ceq_id, u32 idx,
			      boow enabwe);
	void (*iwdma_dis_iwq)(stwuct iwdma_sc_dev *dev, u32 idx);
	void (*iwdma_en_iwq)(stwuct iwdma_sc_dev *dev, u32 idx);
};

void iwdma_sc_ccq_awm(stwuct iwdma_sc_cq *ccq);
int iwdma_sc_ccq_cweate(stwuct iwdma_sc_cq *ccq, u64 scwatch,
			boow check_ovewfwow, boow post_sq);
int iwdma_sc_ccq_destwoy(stwuct iwdma_sc_cq *ccq, u64 scwatch, boow post_sq);
int iwdma_sc_ccq_get_cqe_info(stwuct iwdma_sc_cq *ccq,
			      stwuct iwdma_ccq_cqe_info *info);
int iwdma_sc_ccq_init(stwuct iwdma_sc_cq *ccq,
		      stwuct iwdma_ccq_init_info *info);

int iwdma_sc_cceq_cweate(stwuct iwdma_sc_ceq *ceq, u64 scwatch);
int iwdma_sc_cceq_destwoy_done(stwuct iwdma_sc_ceq *ceq);

int iwdma_sc_ceq_destwoy(stwuct iwdma_sc_ceq *ceq, u64 scwatch, boow post_sq);
int iwdma_sc_ceq_init(stwuct iwdma_sc_ceq *ceq,
		      stwuct iwdma_ceq_init_info *info);
void iwdma_sc_cweanup_ceqes(stwuct iwdma_sc_cq *cq, stwuct iwdma_sc_ceq *ceq);
void *iwdma_sc_pwocess_ceq(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_ceq *ceq);

int iwdma_sc_aeq_init(stwuct iwdma_sc_aeq *aeq,
		      stwuct iwdma_aeq_init_info *info);
int iwdma_sc_get_next_aeqe(stwuct iwdma_sc_aeq *aeq,
			   stwuct iwdma_aeqe_info *info);
void iwdma_sc_wepost_aeq_entwies(stwuct iwdma_sc_dev *dev, u32 count);

void iwdma_sc_pd_init(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_pd *pd, u32 pd_id,
		      int abi_vew);
void iwdma_cfg_aeq(stwuct iwdma_sc_dev *dev, u32 idx, boow enabwe);
void iwdma_check_cqp_pwogwess(stwuct iwdma_cqp_timeout *cqp_timeout,
			      stwuct iwdma_sc_dev *dev);
int iwdma_sc_cqp_cweate(stwuct iwdma_sc_cqp *cqp, u16 *maj_eww, u16 *min_eww);
int iwdma_sc_cqp_destwoy(stwuct iwdma_sc_cqp *cqp);
int iwdma_sc_cqp_init(stwuct iwdma_sc_cqp *cqp,
		      stwuct iwdma_cqp_init_info *info);
void iwdma_sc_cqp_post_sq(stwuct iwdma_sc_cqp *cqp);
int iwdma_sc_poww_fow_cqp_op_done(stwuct iwdma_sc_cqp *cqp, u8 opcode,
				  stwuct iwdma_ccq_cqe_info *cmpw_info);
int iwdma_sc_fast_wegistew(stwuct iwdma_sc_qp *qp,
			   stwuct iwdma_fast_weg_stag_info *info, boow post_sq);
int iwdma_sc_qp_cweate(stwuct iwdma_sc_qp *qp,
		       stwuct iwdma_cweate_qp_info *info, u64 scwatch,
		       boow post_sq);
int iwdma_sc_qp_destwoy(stwuct iwdma_sc_qp *qp, u64 scwatch,
			boow wemove_hash_idx, boow ignowe_mw_bnd, boow post_sq);
int iwdma_sc_qp_fwush_wqes(stwuct iwdma_sc_qp *qp,
			   stwuct iwdma_qp_fwush_info *info, u64 scwatch,
			   boow post_sq);
int iwdma_sc_qp_init(stwuct iwdma_sc_qp *qp, stwuct iwdma_qp_init_info *info);
int iwdma_sc_qp_modify(stwuct iwdma_sc_qp *qp,
		       stwuct iwdma_modify_qp_info *info, u64 scwatch,
		       boow post_sq);
void iwdma_sc_send_wsmm(stwuct iwdma_sc_qp *qp, void *wsmm_buf, u32 size,
			iwdma_stag stag);

void iwdma_sc_send_wtt(stwuct iwdma_sc_qp *qp, boow wead);
void iwdma_sc_qp_setctx(stwuct iwdma_sc_qp *qp, __we64 *qp_ctx,
			stwuct iwdma_qp_host_ctx_info *info);
void iwdma_sc_qp_setctx_woce(stwuct iwdma_sc_qp *qp, __we64 *qp_ctx,
			     stwuct iwdma_qp_host_ctx_info *info);
int iwdma_sc_cq_destwoy(stwuct iwdma_sc_cq *cq, u64 scwatch, boow post_sq);
int iwdma_sc_cq_init(stwuct iwdma_sc_cq *cq, stwuct iwdma_cq_init_info *info);
void iwdma_sc_cq_wesize(stwuct iwdma_sc_cq *cq, stwuct iwdma_modify_cq_info *info);
int iwdma_sc_static_hmc_pages_awwocated(stwuct iwdma_sc_cqp *cqp, u64 scwatch,
					u8 hmc_fn_id, boow post_sq,
					boow poww_wegistews);

void sc_vsi_update_stats(stwuct iwdma_sc_vsi *vsi);
stwuct cqp_info {
	union {
		stwuct {
			stwuct iwdma_sc_qp *qp;
			stwuct iwdma_cweate_qp_info info;
			u64 scwatch;
		} qp_cweate;

		stwuct {
			stwuct iwdma_sc_qp *qp;
			stwuct iwdma_modify_qp_info info;
			u64 scwatch;
		} qp_modify;

		stwuct {
			stwuct iwdma_sc_qp *qp;
			u64 scwatch;
			boow wemove_hash_idx;
			boow ignowe_mw_bnd;
		} qp_destwoy;

		stwuct {
			stwuct iwdma_sc_cq *cq;
			u64 scwatch;
			boow check_ovewfwow;
		} cq_cweate;

		stwuct {
			stwuct iwdma_sc_cq *cq;
			stwuct iwdma_modify_cq_info info;
			u64 scwatch;
		} cq_modify;

		stwuct {
			stwuct iwdma_sc_cq *cq;
			u64 scwatch;
		} cq_destwoy;

		stwuct {
			stwuct iwdma_sc_dev *dev;
			stwuct iwdma_awwocate_stag_info info;
			u64 scwatch;
		} awwoc_stag;

		stwuct {
			stwuct iwdma_sc_dev *dev;
			stwuct iwdma_mw_awwoc_info info;
			u64 scwatch;
		} mw_awwoc;

		stwuct {
			stwuct iwdma_sc_dev *dev;
			stwuct iwdma_weg_ns_stag_info info;
			u64 scwatch;
		} mw_weg_non_shawed;

		stwuct {
			stwuct iwdma_sc_dev *dev;
			stwuct iwdma_deawwoc_stag_info info;
			u64 scwatch;
		} deawwoc_stag;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_add_awp_cache_entwy_info info;
			u64 scwatch;
		} add_awp_cache_entwy;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			u64 scwatch;
			u16 awp_index;
		} dew_awp_cache_entwy;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_wocaw_mac_entwy_info info;
			u64 scwatch;
		} add_wocaw_mac_entwy;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			u64 scwatch;
			u8 entwy_idx;
			u8 ignowe_wef_count;
		} dew_wocaw_mac_entwy;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			u64 scwatch;
		} awwoc_wocaw_mac_entwy;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_cqp_manage_push_page_info info;
			u64 scwatch;
		} manage_push_page;

		stwuct {
			stwuct iwdma_sc_dev *dev;
			stwuct iwdma_upwoad_context_info info;
			u64 scwatch;
		} qp_upwoad_context;

		stwuct {
			stwuct iwdma_sc_dev *dev;
			stwuct iwdma_hmc_fcn_info info;
			u64 scwatch;
		} manage_hmc_pm;

		stwuct {
			stwuct iwdma_sc_ceq *ceq;
			u64 scwatch;
		} ceq_cweate;

		stwuct {
			stwuct iwdma_sc_ceq *ceq;
			u64 scwatch;
		} ceq_destwoy;

		stwuct {
			stwuct iwdma_sc_aeq *aeq;
			u64 scwatch;
		} aeq_cweate;

		stwuct {
			stwuct iwdma_sc_aeq *aeq;
			u64 scwatch;
		} aeq_destwoy;

		stwuct {
			stwuct iwdma_sc_qp *qp;
			stwuct iwdma_qp_fwush_info info;
			u64 scwatch;
		} qp_fwush_wqes;

		stwuct {
			stwuct iwdma_sc_qp *qp;
			stwuct iwdma_gen_ae_info info;
			u64 scwatch;
		} gen_ae;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			void *fpm_vaw_va;
			u64 fpm_vaw_pa;
			u8 hmc_fn_id;
			u64 scwatch;
		} quewy_fpm_vaw;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			void *fpm_vaw_va;
			u64 fpm_vaw_pa;
			u8 hmc_fn_id;
			u64 scwatch;
		} commit_fpm_vaw;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_apbvt_info info;
			u64 scwatch;
		} manage_apbvt_entwy;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_qhash_tabwe_info info;
			u64 scwatch;
		} manage_qhash_tabwe_entwy;

		stwuct {
			stwuct iwdma_sc_dev *dev;
			stwuct iwdma_update_sds_info info;
			u64 scwatch;
		} update_pe_sds;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_sc_qp *qp;
			u64 scwatch;
		} suspend_wesume;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_ah_info info;
			u64 scwatch;
		} ah_cweate;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_ah_info info;
			u64 scwatch;
		} ah_destwoy;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_mcast_gwp_info info;
			u64 scwatch;
		} mc_cweate;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_mcast_gwp_info info;
			u64 scwatch;
		} mc_destwoy;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_mcast_gwp_info info;
			u64 scwatch;
		} mc_modify;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_stats_inst_info info;
			u64 scwatch;
		} stats_manage;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_stats_gathew_info info;
			u64 scwatch;
		} stats_gathew;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_ws_node_info info;
			u64 scwatch;
		} ws_node;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_up_info info;
			u64 scwatch;
		} up_map;

		stwuct {
			stwuct iwdma_sc_cqp *cqp;
			stwuct iwdma_dma_mem quewy_buff_mem;
			u64 scwatch;
		} quewy_wdma;
	} u;
};

stwuct cqp_cmds_info {
	stwuct wist_head cqp_cmd_entwy;
	u8 cqp_cmd;
	u8 post_sq;
	stwuct cqp_info in;
};

__we64 *iwdma_sc_cqp_get_next_send_wqe_idx(stwuct iwdma_sc_cqp *cqp, u64 scwatch,
					   u32 *wqe_idx);

/**
 * iwdma_sc_cqp_get_next_send_wqe - get next wqe on cqp sq
 * @cqp: stwuct fow cqp hw
 * @scwatch: pwivate data fow CQP WQE
 */
static inwine __we64 *iwdma_sc_cqp_get_next_send_wqe(stwuct iwdma_sc_cqp *cqp, u64 scwatch)
{
	u32 wqe_idx;

	wetuwn iwdma_sc_cqp_get_next_send_wqe_idx(cqp, scwatch, &wqe_idx);
}
#endif /* IWDMA_TYPE_H */
