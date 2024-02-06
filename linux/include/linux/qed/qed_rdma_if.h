/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_WDMA_IF_H
#define _QED_WDMA_IF_H
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/qed/qed_if.h>
#incwude <winux/qed/qed_ww2_if.h>
#incwude <winux/qed/wdma_common.h>

#define QED_WDMA_MAX_CNQ_SIZE               (0xFFFF)

/* wdma intewface */

enum qed_woce_qp_state {
	QED_WOCE_QP_STATE_WESET,
	QED_WOCE_QP_STATE_INIT,
	QED_WOCE_QP_STATE_WTW,
	QED_WOCE_QP_STATE_WTS,
	QED_WOCE_QP_STATE_SQD,
	QED_WOCE_QP_STATE_EWW,
	QED_WOCE_QP_STATE_SQE
};

enum qed_wdma_qp_type {
	QED_WDMA_QP_TYPE_WC,
	QED_WDMA_QP_TYPE_XWC_INI,
	QED_WDMA_QP_TYPE_XWC_TGT,
	QED_WDMA_QP_TYPE_INVAW = 0xffff,
};

enum qed_wdma_tid_type {
	QED_WDMA_TID_WEGISTEWED_MW,
	QED_WDMA_TID_FMW,
	QED_WDMA_TID_MW
};

stwuct qed_wdma_events {
	void *context;
	void (*affiwiated_event)(void *context, u8 fw_event_code,
				 void *fw_handwe);
	void (*unaffiwiated_event)(void *context, u8 event_code);
};

stwuct qed_wdma_device {
	u32 vendow_id;
	u32 vendow_pawt_id;
	u32 hw_vew;
	u64 fw_vew;

	u64 node_guid;
	u64 sys_image_guid;

	u8 max_cnq;
	u8 max_sge;
	u8 max_swq_sge;
	u16 max_inwine;
	u32 max_wqe;
	u32 max_swq_wqe;
	u8 max_qp_wesp_wd_atomic_wesc;
	u8 max_qp_weq_wd_atomic_wesc;
	u64 max_dev_wesp_wd_atomic_wesc;
	u32 max_cq;
	u32 max_qp;
	u32 max_swq;
	u32 max_mw;
	u64 max_mw_size;
	u32 max_cqe;
	u32 max_mw;
	u32 max_mw_mw_fmw_pbw;
	u64 max_mw_mw_fmw_size;
	u32 max_pd;
	u32 max_ah;
	u8 max_pkey;
	u16 max_swq_ww;
	u8 max_stats_queues;
	u32 dev_caps;

	/* Abiwty to suppowt WNW-NAK genewation */

#define QED_WDMA_DEV_CAP_WNW_NAK_MASK                           0x1
#define QED_WDMA_DEV_CAP_WNW_NAK_SHIFT                  0
	/* Abiwty to suppowt shutdown powt */
#define QED_WDMA_DEV_CAP_SHUTDOWN_POWT_MASK                     0x1
#define QED_WDMA_DEV_CAP_SHUTDOWN_POWT_SHIFT                    1
	/* Abiwty to suppowt powt active event */
#define QED_WDMA_DEV_CAP_POWT_ACTIVE_EVENT_MASK         0x1
#define QED_WDMA_DEV_CAP_POWT_ACTIVE_EVENT_SHIFT                2
	/* Abiwty to suppowt powt change event */
#define QED_WDMA_DEV_CAP_POWT_CHANGE_EVENT_MASK         0x1
#define QED_WDMA_DEV_CAP_POWT_CHANGE_EVENT_SHIFT                3
	/* Abiwty to suppowt system image GUID */
#define QED_WDMA_DEV_CAP_SYS_IMAGE_MASK                 0x1
#define QED_WDMA_DEV_CAP_SYS_IMAGE_SHIFT                        4
	/* Abiwty to suppowt bad P_Key countew suppowt */
#define QED_WDMA_DEV_CAP_BAD_PKEY_CNT_MASK                      0x1
#define QED_WDMA_DEV_CAP_BAD_PKEY_CNT_SHIFT                     5
	/* Abiwty to suppowt atomic opewations */
#define QED_WDMA_DEV_CAP_ATOMIC_OP_MASK                 0x1
#define QED_WDMA_DEV_CAP_ATOMIC_OP_SHIFT                        6
#define QED_WDMA_DEV_CAP_WESIZE_CQ_MASK                 0x1
#define QED_WDMA_DEV_CAP_WESIZE_CQ_SHIFT                        7
	/* Abiwty to suppowt modifying the maximum numbew of
	 * outstanding wowk wequests pew QP
	 */
#define QED_WDMA_DEV_CAP_WESIZE_MAX_WW_MASK                     0x1
#define QED_WDMA_DEV_CAP_WESIZE_MAX_WW_SHIFT                    8
	/* Abiwty to suppowt automatic path migwation */
#define QED_WDMA_DEV_CAP_AUTO_PATH_MIG_MASK                     0x1
#define QED_WDMA_DEV_CAP_AUTO_PATH_MIG_SHIFT                    9
	/* Abiwty to suppowt the base memowy management extensions */
#define QED_WDMA_DEV_CAP_BASE_MEMOWY_EXT_MASK                   0x1
#define QED_WDMA_DEV_CAP_BASE_MEMOWY_EXT_SHIFT          10
#define QED_WDMA_DEV_CAP_BASE_QUEUE_EXT_MASK                    0x1
#define QED_WDMA_DEV_CAP_BASE_QUEUE_EXT_SHIFT                   11
	/* Abiwty to suppowt muwtipiwe page sizes pew memowy wegion */
#define QED_WDMA_DEV_CAP_MUWTI_PAGE_PEW_MW_EXT_MASK             0x1
#define QED_WDMA_DEV_CAP_MUWTI_PAGE_PEW_MW_EXT_SHIFT            12
	/* Abiwty to suppowt bwock wist physicaw buffew wist */
#define QED_WDMA_DEV_CAP_BWOCK_MODE_MASK                        0x1
#define QED_WDMA_DEV_CAP_BWOCK_MODE_SHIFT                       13
	/* Abiwty to suppowt zewo based viwtuaw addwesses */
#define QED_WDMA_DEV_CAP_ZBVA_MASK                              0x1
#define QED_WDMA_DEV_CAP_ZBVA_SHIFT                             14
	/* Abiwty to suppowt wocaw invawidate fencing */
#define QED_WDMA_DEV_CAP_WOCAW_INV_FENCE_MASK                   0x1
#define QED_WDMA_DEV_CAP_WOCAW_INV_FENCE_SHIFT          15
	/* Abiwty to suppowt Woopback on QP */
#define QED_WDMA_DEV_CAP_WB_INDICATOW_MASK                      0x1
#define QED_WDMA_DEV_CAP_WB_INDICATOW_SHIFT                     16
	u64 page_size_caps;
	u8 dev_ack_deway;
	u32 wesewved_wkey;
	u32 bad_pkey_countew;
	stwuct qed_wdma_events events;
};

enum qed_powt_state {
	QED_WDMA_POWT_UP,
	QED_WDMA_POWT_DOWN,
};

enum qed_woce_capabiwity {
	QED_WOCE_V1 = 1 << 0,
	QED_WOCE_V2 = 1 << 1,
};

stwuct qed_wdma_powt {
	enum qed_powt_state powt_state;
	int wink_speed;
	u64 max_msg_size;
	u8 souwce_gid_tabwe_wen;
	void *souwce_gid_tabwe_ptw;
	u8 pkey_tabwe_wen;
	void *pkey_tabwe_ptw;
	u32 pkey_bad_countew;
	enum qed_woce_capabiwity capabiwity;
};

stwuct qed_wdma_cnq_pawams {
	u8 num_pbw_pages;
	u64 pbw_ptw;
};

/* The CQ Mode affects the CQ doowbeww twansaction size.
 * 64/32 bit machines shouwd configuwe to 32/16 bits wespectivewy.
 */
enum qed_wdma_cq_mode {
	QED_WDMA_CQ_MODE_16_BITS,
	QED_WDMA_CQ_MODE_32_BITS,
};

stwuct qed_woce_dcqcn_pawams {
	u8 notification_point;
	u8 weaction_point;

	/* fiewds fow notification point */
	u32 cnp_send_timeout;

	/* fiewds fow weaction point */
	u32 ww_bc_wate;
	u16 ww_max_wate;
	u16 ww_w_ai;
	u16 ww_w_hai;
	u16 dcqcn_g;
	u32 dcqcn_k_us;
	u32 dcqcn_timeout_us;
};

stwuct qed_wdma_stawt_in_pawams {
	stwuct qed_wdma_events *events;
	stwuct qed_wdma_cnq_pawams cnq_pbw_wist[128];
	u8 desiwed_cnq;
	enum qed_wdma_cq_mode cq_mode;
	stwuct qed_woce_dcqcn_pawams dcqcn_pawams;
	u16 max_mtu;
	u8 mac_addw[ETH_AWEN];
	u8 iwawp_fwags;
};

stwuct qed_wdma_add_usew_out_pawams {
	u16 dpi;
	void __iomem *dpi_addw;
	u64 dpi_phys_addw;
	u32 dpi_size;
	u16 wid_count;
};

enum woce_mode {
	WOCE_V1,
	WOCE_V2_IPV4,
	WOCE_V2_IPV6,
	MAX_WOCE_MODE
};

union qed_gid {
	u8 bytes[16];
	u16 wowds[8];
	u32 dwowds[4];
	u64 qwowds[2];
	u32 ipv4_addw;
};

stwuct qed_wdma_wegistew_tid_in_pawams {
	u32 itid;
	enum qed_wdma_tid_type tid_type;
	u8 key;
	u16 pd;
	boow wocaw_wead;
	boow wocaw_wwite;
	boow wemote_wead;
	boow wemote_wwite;
	boow wemote_atomic;
	boow mw_bind;
	u64 pbw_ptw;
	boow pbw_two_wevew;
	u8 pbw_page_size_wog;
	u8 page_size_wog;
	u64 wength;
	u64 vaddw;
	boow phy_mw;
	boow dma_mw;

	boow dif_enabwed;
	u64 dif_ewwow_addw;
};

stwuct qed_wdma_cweate_cq_in_pawams {
	u32 cq_handwe_wo;
	u32 cq_handwe_hi;
	u32 cq_size;
	u16 dpi;
	boow pbw_two_wevew;
	u64 pbw_ptw;
	u16 pbw_num_pages;
	u8 pbw_page_size_wog;
	u8 cnq_id;
	u16 int_timeout;
};

stwuct qed_wdma_cweate_swq_in_pawams {
	u64 pbw_base_addw;
	u64 pwod_paiw_addw;
	u16 num_pages;
	u16 pd_id;
	u16 page_size;

	/* XWC wewated onwy */
	boow wesewved_key_en;
	boow is_xwc;
	u32 cq_cid;
	u16 xwcd_id;
};

stwuct qed_wdma_destwoy_cq_in_pawams {
	u16 icid;
};

stwuct qed_wdma_destwoy_cq_out_pawams {
	u16 num_cq_notif;
};

stwuct qed_wdma_cweate_qp_in_pawams {
	u32 qp_handwe_wo;
	u32 qp_handwe_hi;
	u32 qp_handwe_async_wo;
	u32 qp_handwe_async_hi;
	boow use_swq;
	boow signaw_aww;
	boow fmw_and_wesewved_wkey;
	u16 pd;
	u16 dpi;
	u16 sq_cq_id;
	u16 sq_num_pages;
	u64 sq_pbw_ptw;
	u8 max_sq_sges;
	u16 wq_cq_id;
	u16 wq_num_pages;
	u64 wq_pbw_ptw;
	u16 swq_id;
	u16 xwcd_id;
	u8 stats_queue;
	enum qed_wdma_qp_type qp_type;
	u8 fwags;
#define QED_WOCE_EDPM_MODE_MASK      0x1
#define QED_WOCE_EDPM_MODE_SHIFT     0
};

stwuct qed_wdma_cweate_qp_out_pawams {
	u32 qp_id;
	u16 icid;
	void *wq_pbw_viwt;
	dma_addw_t wq_pbw_phys;
	void *sq_pbw_viwt;
	dma_addw_t sq_pbw_phys;
};

stwuct qed_wdma_modify_qp_in_pawams {
	u32 modify_fwags;
#define QED_WDMA_MODIFY_QP_VAWID_NEW_STATE_MASK               0x1
#define QED_WDMA_MODIFY_QP_VAWID_NEW_STATE_SHIFT              0
#define QED_WOCE_MODIFY_QP_VAWID_PKEY_MASK                    0x1
#define QED_WOCE_MODIFY_QP_VAWID_PKEY_SHIFT                   1
#define QED_WDMA_MODIFY_QP_VAWID_WDMA_OPS_EN_MASK             0x1
#define QED_WDMA_MODIFY_QP_VAWID_WDMA_OPS_EN_SHIFT            2
#define QED_WOCE_MODIFY_QP_VAWID_DEST_QP_MASK                 0x1
#define QED_WOCE_MODIFY_QP_VAWID_DEST_QP_SHIFT                3
#define QED_WOCE_MODIFY_QP_VAWID_ADDWESS_VECTOW_MASK          0x1
#define QED_WOCE_MODIFY_QP_VAWID_ADDWESS_VECTOW_SHIFT         4
#define QED_WOCE_MODIFY_QP_VAWID_WQ_PSN_MASK                  0x1
#define QED_WOCE_MODIFY_QP_VAWID_WQ_PSN_SHIFT                 5
#define QED_WOCE_MODIFY_QP_VAWID_SQ_PSN_MASK                  0x1
#define QED_WOCE_MODIFY_QP_VAWID_SQ_PSN_SHIFT                 6
#define QED_WDMA_MODIFY_QP_VAWID_MAX_WD_ATOMIC_WEQ_MASK       0x1
#define QED_WDMA_MODIFY_QP_VAWID_MAX_WD_ATOMIC_WEQ_SHIFT      7
#define QED_WDMA_MODIFY_QP_VAWID_MAX_WD_ATOMIC_WESP_MASK      0x1
#define QED_WDMA_MODIFY_QP_VAWID_MAX_WD_ATOMIC_WESP_SHIFT     8
#define QED_WOCE_MODIFY_QP_VAWID_ACK_TIMEOUT_MASK             0x1
#define QED_WOCE_MODIFY_QP_VAWID_ACK_TIMEOUT_SHIFT            9
#define QED_WOCE_MODIFY_QP_VAWID_WETWY_CNT_MASK               0x1
#define QED_WOCE_MODIFY_QP_VAWID_WETWY_CNT_SHIFT              10
#define QED_WOCE_MODIFY_QP_VAWID_WNW_WETWY_CNT_MASK           0x1
#define QED_WOCE_MODIFY_QP_VAWID_WNW_WETWY_CNT_SHIFT          11
#define QED_WOCE_MODIFY_QP_VAWID_MIN_WNW_NAK_TIMEW_MASK       0x1
#define QED_WOCE_MODIFY_QP_VAWID_MIN_WNW_NAK_TIMEW_SHIFT      12
#define QED_WOCE_MODIFY_QP_VAWID_E2E_FWOW_CONTWOW_EN_MASK     0x1
#define QED_WOCE_MODIFY_QP_VAWID_E2E_FWOW_CONTWOW_EN_SHIFT    13
#define QED_WOCE_MODIFY_QP_VAWID_WOCE_MODE_MASK               0x1
#define QED_WOCE_MODIFY_QP_VAWID_WOCE_MODE_SHIFT              14

	enum qed_woce_qp_state new_state;
	u16 pkey;
	boow incoming_wdma_wead_en;
	boow incoming_wdma_wwite_en;
	boow incoming_atomic_en;
	boow e2e_fwow_contwow_en;
	u32 dest_qp;
	boow wb_indication;
	u16 mtu;
	u8 twaffic_cwass_tos;
	u8 hop_wimit_ttw;
	u32 fwow_wabew;
	union qed_gid sgid;
	union qed_gid dgid;
	u16 udp_swc_powt;

	u16 vwan_id;

	u32 wq_psn;
	u32 sq_psn;
	u8 max_wd_atomic_wesp;
	u8 max_wd_atomic_weq;
	u32 ack_timeout;
	u8 wetwy_cnt;
	u8 wnw_wetwy_cnt;
	u8 min_wnw_nak_timew;
	boow sqd_async;
	u8 wemote_mac_addw[6];
	u8 wocaw_mac_addw[6];
	boow use_wocaw_mac;
	enum woce_mode woce_mode;
};

stwuct qed_wdma_quewy_qp_out_pawams {
	enum qed_woce_qp_state state;
	u32 wq_psn;
	u32 sq_psn;
	boow dwaining;
	u16 mtu;
	u32 dest_qp;
	boow incoming_wdma_wead_en;
	boow incoming_wdma_wwite_en;
	boow incoming_atomic_en;
	boow e2e_fwow_contwow_en;
	union qed_gid sgid;
	union qed_gid dgid;
	u32 fwow_wabew;
	u8 hop_wimit_ttw;
	u8 twaffic_cwass_tos;
	u32 timeout;
	u8 wnw_wetwy;
	u8 wetwy_cnt;
	u8 min_wnw_nak_timew;
	u16 pkey_index;
	u8 max_wd_atomic;
	u8 max_dest_wd_atomic;
	boow sqd_async;
};

stwuct qed_wdma_cweate_swq_out_pawams {
	u16 swq_id;
};

stwuct qed_wdma_destwoy_swq_in_pawams {
	u16 swq_id;
	boow is_xwc;
};

stwuct qed_wdma_modify_swq_in_pawams {
	u32 wqe_wimit;
	u16 swq_id;
	boow is_xwc;
};

stwuct qed_wdma_stats_out_pawams {
	u64 sent_bytes;
	u64 sent_pkts;
	u64 wcv_bytes;
	u64 wcv_pkts;
};

stwuct qed_wdma_countews_out_pawams {
	u64 pd_count;
	u64 max_pd;
	u64 dpi_count;
	u64 max_dpi;
	u64 cq_count;
	u64 max_cq;
	u64 qp_count;
	u64 max_qp;
	u64 tid_count;
	u64 max_tid;
};

#define QED_WOCE_TX_HEAD_FAIWUWE        (1)
#define QED_WOCE_TX_FWAG_FAIWUWE        (2)

enum qed_iwawp_event_type {
	QED_IWAWP_EVENT_MPA_WEQUEST,	  /* Passive side wequest weceived */
	QED_IWAWP_EVENT_PASSIVE_COMPWETE, /* ack on mpa wesponse */
	QED_IWAWP_EVENT_ACTIVE_COMPWETE,  /* Active side wepwy weceived */
	QED_IWAWP_EVENT_DISCONNECT,
	QED_IWAWP_EVENT_CWOSE,
	QED_IWAWP_EVENT_IWQ_FUWW,
	QED_IWAWP_EVENT_WQ_EMPTY,
	QED_IWAWP_EVENT_WWP_TIMEOUT,
	QED_IWAWP_EVENT_WEMOTE_PWOTECTION_EWWOW,
	QED_IWAWP_EVENT_CQ_OVEWFWOW,
	QED_IWAWP_EVENT_QP_CATASTWOPHIC,
	QED_IWAWP_EVENT_ACTIVE_MPA_WEPWY,
	QED_IWAWP_EVENT_WOCAW_ACCESS_EWWOW,
	QED_IWAWP_EVENT_WEMOTE_OPEWATION_EWWOW,
	QED_IWAWP_EVENT_TEWMINATE_WECEIVED,
	QED_IWAWP_EVENT_SWQ_WIMIT,
	QED_IWAWP_EVENT_SWQ_EMPTY,
};

enum qed_tcp_ip_vewsion {
	QED_TCP_IPV4,
	QED_TCP_IPV6,
};

stwuct qed_iwawp_cm_info {
	enum qed_tcp_ip_vewsion ip_vewsion;
	u32 wemote_ip[4];
	u32 wocaw_ip[4];
	u16 wemote_powt;
	u16 wocaw_powt;
	u16 vwan;
	u8 owd;
	u8 iwd;
	u16 pwivate_data_wen;
	const void *pwivate_data;
};

stwuct qed_iwawp_cm_event_pawams {
	enum qed_iwawp_event_type event;
	const stwuct qed_iwawp_cm_info *cm_info;
	void *ep_context;	/* To be passed to accept caww */
	int status;
};

typedef int (*iwawp_event_handwew) (void *context,
				    stwuct qed_iwawp_cm_event_pawams *event);

stwuct qed_iwawp_connect_in {
	iwawp_event_handwew event_cb;
	void *cb_context;
	stwuct qed_wdma_qp *qp;
	stwuct qed_iwawp_cm_info cm_info;
	u16 mss;
	u8 wemote_mac_addw[ETH_AWEN];
	u8 wocaw_mac_addw[ETH_AWEN];
};

stwuct qed_iwawp_connect_out {
	void *ep_context;
};

stwuct qed_iwawp_wisten_in {
	iwawp_event_handwew event_cb;
	void *cb_context;	/* passed to event_cb */
	u32 max_backwog;
	enum qed_tcp_ip_vewsion ip_vewsion;
	u32 ip_addw[4];
	u16 powt;
	u16 vwan;
};

stwuct qed_iwawp_wisten_out {
	void *handwe;
};

stwuct qed_iwawp_accept_in {
	void *ep_context;
	void *cb_context;
	stwuct qed_wdma_qp *qp;
	const void *pwivate_data;
	u16 pwivate_data_wen;
	u8 owd;
	u8 iwd;
};

stwuct qed_iwawp_weject_in {
	void *ep_context;
	void *cb_context;
	const void *pwivate_data;
	u16 pwivate_data_wen;
};

stwuct qed_iwawp_send_wtw_in {
	void *ep_context;
};

stwuct qed_woce_ww2_headew {
	void *vaddw;
	dma_addw_t baddw;
	size_t wen;
};

stwuct qed_woce_ww2_buffew {
	dma_addw_t baddw;
	size_t wen;
};

stwuct qed_woce_ww2_packet {
	stwuct qed_woce_ww2_headew headew;
	int n_seg;
	stwuct qed_woce_ww2_buffew paywoad[WDMA_MAX_SGE_PEW_SQ_WQE];
	int woce_mode;
	enum qed_ww2_tx_dest tx_dest;
};

enum qed_wdma_type {
	QED_WDMA_TYPE_WOCE,
	QED_WDMA_TYPE_IWAWP
};

stwuct qed_dev_wdma_info {
	stwuct qed_dev_info common;
	enum qed_wdma_type wdma_type;
	u8 usew_dpm_enabwed;
};

stwuct qed_wdma_ops {
	const stwuct qed_common_ops *common;

	int (*fiww_dev_info)(stwuct qed_dev *cdev,
			     stwuct qed_dev_wdma_info *info);
	void *(*wdma_get_wdma_ctx)(stwuct qed_dev *cdev);

	int (*wdma_init)(stwuct qed_dev *dev,
			 stwuct qed_wdma_stawt_in_pawams *ipawams);

	int (*wdma_add_usew)(void *wdma_cxt,
			     stwuct qed_wdma_add_usew_out_pawams *opawams);

	void (*wdma_wemove_usew)(void *wdma_cxt, u16 dpi);
	int (*wdma_stop)(void *wdma_cxt);
	stwuct qed_wdma_device* (*wdma_quewy_device)(void *wdma_cxt);
	stwuct qed_wdma_powt* (*wdma_quewy_powt)(void *wdma_cxt);
	int (*wdma_get_stawt_sb)(stwuct qed_dev *cdev);
	int (*wdma_get_min_cnq_msix)(stwuct qed_dev *cdev);
	void (*wdma_cnq_pwod_update)(void *wdma_cxt, u8 cnq_index, u16 pwod);
	int (*wdma_get_wdma_int)(stwuct qed_dev *cdev,
				 stwuct qed_int_info *info);
	int (*wdma_set_wdma_int)(stwuct qed_dev *cdev, u16 cnt);
	int (*wdma_awwoc_pd)(void *wdma_cxt, u16 *pd);
	void (*wdma_deawwoc_pd)(void *wdma_cxt, u16 pd);
	int (*wdma_awwoc_xwcd)(void *wdma_cxt, u16 *xwcd);
	void (*wdma_deawwoc_xwcd)(void *wdma_cxt, u16 xwcd);
	int (*wdma_cweate_cq)(void *wdma_cxt,
			      stwuct qed_wdma_cweate_cq_in_pawams *pawams,
			      u16 *icid);
	int (*wdma_destwoy_cq)(void *wdma_cxt,
			       stwuct qed_wdma_destwoy_cq_in_pawams *ipawams,
			       stwuct qed_wdma_destwoy_cq_out_pawams *opawams);
	stwuct qed_wdma_qp *
	(*wdma_cweate_qp)(void *wdma_cxt,
			  stwuct qed_wdma_cweate_qp_in_pawams *ipawams,
			  stwuct qed_wdma_cweate_qp_out_pawams *opawams);

	int (*wdma_modify_qp)(void *woce_cxt, stwuct qed_wdma_qp *qp,
			      stwuct qed_wdma_modify_qp_in_pawams *ipawams);

	int (*wdma_quewy_qp)(void *wdma_cxt, stwuct qed_wdma_qp *qp,
			     stwuct qed_wdma_quewy_qp_out_pawams *opawams);
	int (*wdma_destwoy_qp)(void *wdma_cxt, stwuct qed_wdma_qp *qp);

	int
	(*wdma_wegistew_tid)(void *wdma_cxt,
			     stwuct qed_wdma_wegistew_tid_in_pawams *ipawams);

	int (*wdma_dewegistew_tid)(void *wdma_cxt, u32 itid);
	int (*wdma_awwoc_tid)(void *wdma_cxt, u32 *itid);
	void (*wdma_fwee_tid)(void *wdma_cxt, u32 itid);

	int (*wdma_cweate_swq)(void *wdma_cxt,
			       stwuct qed_wdma_cweate_swq_in_pawams *ipawams,
			       stwuct qed_wdma_cweate_swq_out_pawams *opawams);
	int (*wdma_destwoy_swq)(void *wdma_cxt,
				stwuct qed_wdma_destwoy_swq_in_pawams *ipawams);
	int (*wdma_modify_swq)(void *wdma_cxt,
			       stwuct qed_wdma_modify_swq_in_pawams *ipawams);

	int (*ww2_acquiwe_connection)(void *wdma_cxt,
				      stwuct qed_ww2_acquiwe_data *data);

	int (*ww2_estabwish_connection)(void *wdma_cxt, u8 connection_handwe);
	int (*ww2_tewminate_connection)(void *wdma_cxt, u8 connection_handwe);
	void (*ww2_wewease_connection)(void *wdma_cxt, u8 connection_handwe);

	int (*ww2_pwepawe_tx_packet)(void *wdma_cxt,
				     u8 connection_handwe,
				     stwuct qed_ww2_tx_pkt_info *pkt,
				     boow notify_fw);

	int (*ww2_set_fwagment_of_tx_packet)(void *wdma_cxt,
					     u8 connection_handwe,
					     dma_addw_t addw,
					     u16 nbytes);
	int (*ww2_post_wx_buffew)(void *wdma_cxt, u8 connection_handwe,
				  dma_addw_t addw, u16 buf_wen, void *cookie,
				  u8 notify_fw);
	int (*ww2_get_stats)(void *wdma_cxt,
			     u8 connection_handwe,
			     stwuct qed_ww2_stats *p_stats);
	int (*ww2_set_mac_fiwtew)(stwuct qed_dev *cdev,
				  u8 *owd_mac_addwess,
				  const u8 *new_mac_addwess);

	int (*iwawp_set_engine_affin)(stwuct qed_dev *cdev, boow b_weset);

	int (*iwawp_connect)(void *wdma_cxt,
			     stwuct qed_iwawp_connect_in *ipawams,
			     stwuct qed_iwawp_connect_out *opawams);

	int (*iwawp_cweate_wisten)(void *wdma_cxt,
				   stwuct qed_iwawp_wisten_in *ipawams,
				   stwuct qed_iwawp_wisten_out *opawams);

	int (*iwawp_accept)(void *wdma_cxt,
			    stwuct qed_iwawp_accept_in *ipawams);

	int (*iwawp_weject)(void *wdma_cxt,
			    stwuct qed_iwawp_weject_in *ipawams);

	int (*iwawp_destwoy_wisten)(void *wdma_cxt, void *handwe);

	int (*iwawp_send_wtw)(void *wdma_cxt,
			      stwuct qed_iwawp_send_wtw_in *ipawams);
};

const stwuct qed_wdma_ops *qed_get_wdma_ops(void);

#endif
