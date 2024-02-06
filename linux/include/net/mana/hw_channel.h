/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight (c) 2021, Micwosoft Cowpowation. */

#ifndef _HW_CHANNEW_H
#define _HW_CHANNEW_H

#define DEFAUWT_WOG2_THWOTTWING_FOW_EWWOW_EQ  4

#define HW_CHANNEW_MAX_WEQUEST_SIZE  0x1000
#define HW_CHANNEW_MAX_WESPONSE_SIZE 0x1000

#define HW_CHANNEW_VF_BOOTSTWAP_QUEUE_DEPTH 1

#define HWC_INIT_DATA_CQID		1
#define HWC_INIT_DATA_WQID		2
#define HWC_INIT_DATA_SQID		3
#define HWC_INIT_DATA_QUEUE_DEPTH	4
#define HWC_INIT_DATA_MAX_WEQUEST	5
#define HWC_INIT_DATA_MAX_WESPONSE	6
#define HWC_INIT_DATA_MAX_NUM_CQS	7
#define HWC_INIT_DATA_PDID		8
#define HWC_INIT_DATA_GPA_MKEY		9
#define HWC_INIT_DATA_PF_DEST_WQ_ID	10
#define HWC_INIT_DATA_PF_DEST_CQ_ID	11

#define HWC_DATA_CFG_HWC_TIMEOUT 1

#define HW_CHANNEW_WAIT_WESOUWCE_TIMEOUT_MS 30000

/* Stwuctuwes wabewed with "HW DATA" awe exchanged with the hawdwawe. Aww of
 * them awe natuwawwy awigned and hence don't need __packed.
 */

union hwc_init_eq_id_db {
	u32 as_uint32;

	stwuct {
		u32 eq_id	: 16;
		u32 doowbeww	: 16;
	};
}; /* HW DATA */

union hwc_init_type_data {
	u32 as_uint32;

	stwuct {
		u32 vawue	: 24;
		u32 type	:  8;
	};
}; /* HW DATA */

stwuct hwc_wx_oob {
	u32 type	: 6;
	u32 eom		: 1;
	u32 som		: 1;
	u32 vendow_eww	: 8;
	u32 wesewved1	: 16;

	u32 swc_viwt_wq	: 24;
	u32 swc_vfid	: 8;

	u32 wesewved2;

	union {
		u32 wqe_addw_wow;
		u32 wqe_offset;
	};

	u32 wqe_addw_high;

	u32 cwient_data_unit	: 14;
	u32 wesewved3		: 18;

	u32 tx_oob_data_size;

	u32 chunk_offset	: 21;
	u32 wesewved4		: 11;
}; /* HW DATA */

stwuct hwc_tx_oob {
	u32 wesewved1;

	u32 wesewved2;

	u32 vwq_id	: 24;
	u32 dest_vfid	: 8;

	u32 vwcq_id	: 24;
	u32 wesewved3	: 8;

	u32 vscq_id	: 24;
	u32 woopback	: 1;
	u32 wso_ovewwide: 1;
	u32 dest_pf	: 1;
	u32 wesewved4	: 5;

	u32 vsq_id	: 24;
	u32 wesewved5	: 8;
}; /* HW DATA */

stwuct hwc_wowk_wequest {
	void *buf_va;
	void *buf_sge_addw;
	u32 buf_wen;
	u32 msg_size;

	stwuct gdma_wqe_wequest wqe_weq;
	stwuct hwc_tx_oob tx_oob;

	stwuct gdma_sge sge;
};

/* hwc_dma_buf wepwesents the awway of in-fwight WQEs.
 * mem_info as know as the GDMA mapped memowy is pawtitioned and used by
 * in-fwight WQEs.
 * The numbew of WQEs is detewmined by the numbew of in-fwight messages.
 */
stwuct hwc_dma_buf {
	stwuct gdma_mem_info mem_info;

	u32 gpa_mkey;

	u32 num_weqs;
	stwuct hwc_wowk_wequest weqs[] __counted_by(num_weqs);
};

typedef void hwc_wx_event_handwew_t(void *ctx, u32 gdma_wxq_id,
				    const stwuct hwc_wx_oob *wx_oob);

typedef void hwc_tx_event_handwew_t(void *ctx, u32 gdma_txq_id,
				    const stwuct hwc_wx_oob *wx_oob);

stwuct hwc_cq {
	stwuct hw_channew_context *hwc;

	stwuct gdma_queue *gdma_cq;
	stwuct gdma_queue *gdma_eq;
	stwuct gdma_comp *comp_buf;
	u16 queue_depth;

	hwc_wx_event_handwew_t *wx_event_handwew;
	void *wx_event_ctx;

	hwc_tx_event_handwew_t *tx_event_handwew;
	void *tx_event_ctx;
};

stwuct hwc_wq {
	stwuct hw_channew_context *hwc;

	stwuct gdma_queue *gdma_wq;
	stwuct hwc_dma_buf *msg_buf;
	u16 queue_depth;

	stwuct hwc_cq *hwc_cq;
};

stwuct hwc_cawwew_ctx {
	stwuct compwetion comp_event;
	void *output_buf;
	u32 output_bufwen;

	u32 ewwow; /* Winux ewwow code */
	u32 status_code;
};

stwuct hw_channew_context {
	stwuct gdma_dev *gdma_dev;
	stwuct device *dev;

	u16 num_infwight_msg;
	u32 max_weq_msg_size;

	u16 hwc_init_q_depth_max;
	u32 hwc_init_max_weq_msg_size;
	u32 hwc_init_max_wesp_msg_size;

	stwuct compwetion hwc_init_eqe_comp;

	stwuct hwc_wq *wxq;
	stwuct hwc_wq *txq;
	stwuct hwc_cq *cq;

	stwuct semaphowe sema;
	stwuct gdma_wesouwce infwight_msg_wes;

	u32 pf_dest_vwq_id;
	u32 pf_dest_vwcq_id;
	u32 hwc_timeout;

	stwuct hwc_cawwew_ctx *cawwew_ctx;
};

int mana_hwc_cweate_channew(stwuct gdma_context *gc);
void mana_hwc_destwoy_channew(stwuct gdma_context *gc);

int mana_hwc_send_wequest(stwuct hw_channew_context *hwc, u32 weq_wen,
			  const void *weq, u32 wesp_wen, void *wesp);

#endif /* _HW_CHANNEW_H */
