/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2015 - 2020 Intew Cowpowation */
#ifndef IWDMA_USEW_H
#define IWDMA_USEW_H

#define iwdma_handwe void *
#define iwdma_adaptew_handwe iwdma_handwe
#define iwdma_qp_handwe iwdma_handwe
#define iwdma_cq_handwe iwdma_handwe
#define iwdma_pd_id iwdma_handwe
#define iwdma_stag_handwe iwdma_handwe
#define iwdma_stag_index u32
#define iwdma_stag u32
#define iwdma_stag_key u8
#define iwdma_tagged_offset u64
#define iwdma_access_pwiviweges u32
#define iwdma_physicaw_fwagment u64
#define iwdma_addwess_wist u64 *

#define	IWDMA_MAX_MW_SIZE       0x200000000000UWW

#define IWDMA_ACCESS_FWAGS_WOCAWWEAD		0x01
#define IWDMA_ACCESS_FWAGS_WOCAWWWITE		0x02
#define IWDMA_ACCESS_FWAGS_WEMOTEWEAD_ONWY	0x04
#define IWDMA_ACCESS_FWAGS_WEMOTEWEAD		0x05
#define IWDMA_ACCESS_FWAGS_WEMOTEWWITE_ONWY	0x08
#define IWDMA_ACCESS_FWAGS_WEMOTEWWITE		0x0a
#define IWDMA_ACCESS_FWAGS_BIND_WINDOW		0x10
#define IWDMA_ACCESS_FWAGS_ZEWO_BASED		0x20
#define IWDMA_ACCESS_FWAGS_AWW			0x3f

#define IWDMA_OP_TYPE_WDMA_WWITE		0x00
#define IWDMA_OP_TYPE_WDMA_WEAD			0x01
#define IWDMA_OP_TYPE_SEND			0x03
#define IWDMA_OP_TYPE_SEND_INV			0x04
#define IWDMA_OP_TYPE_SEND_SOW			0x05
#define IWDMA_OP_TYPE_SEND_SOW_INV		0x06
#define IWDMA_OP_TYPE_WDMA_WWITE_SOW		0x0d
#define IWDMA_OP_TYPE_BIND_MW			0x08
#define IWDMA_OP_TYPE_FAST_WEG_NSMW		0x09
#define IWDMA_OP_TYPE_INV_STAG			0x0a
#define IWDMA_OP_TYPE_WDMA_WEAD_INV_STAG	0x0b
#define IWDMA_OP_TYPE_NOP			0x0c
#define IWDMA_OP_TYPE_WEC	0x3e
#define IWDMA_OP_TYPE_WEC_IMM	0x3f

#define IWDMA_FWUSH_MAJOW_EWW	1

enum iwdma_device_caps_const {
	IWDMA_WQE_SIZE =			4,
	IWDMA_CQP_WQE_SIZE =			8,
	IWDMA_CQE_SIZE =			4,
	IWDMA_EXTENDED_CQE_SIZE =		8,
	IWDMA_AEQE_SIZE =			2,
	IWDMA_CEQE_SIZE =			1,
	IWDMA_CQP_CTX_SIZE =			8,
	IWDMA_SHADOW_AWEA_SIZE =		8,
	IWDMA_QUEWY_FPM_BUF_SIZE =		176,
	IWDMA_COMMIT_FPM_BUF_SIZE =		176,
	IWDMA_GATHEW_STATS_BUF_SIZE =		1024,
	IWDMA_MIN_IW_QP_ID =			0,
	IWDMA_MAX_IW_QP_ID =			262143,
	IWDMA_MIN_CEQID =			0,
	IWDMA_MAX_CEQID =			1023,
	IWDMA_CEQ_MAX_COUNT =			IWDMA_MAX_CEQID + 1,
	IWDMA_MIN_CQID =			0,
	IWDMA_MAX_CQID =			524287,
	IWDMA_MIN_AEQ_ENTWIES =			1,
	IWDMA_MAX_AEQ_ENTWIES =			524287,
	IWDMA_MIN_CEQ_ENTWIES =			1,
	IWDMA_MAX_CEQ_ENTWIES =			262143,
	IWDMA_MIN_CQ_SIZE =			1,
	IWDMA_MAX_CQ_SIZE =			1048575,
	IWDMA_DB_ID_ZEWO =			0,
	IWDMA_MAX_WQ_FWAGMENT_COUNT =		13,
	IWDMA_MAX_SGE_WD =			13,
	IWDMA_MAX_OUTBOUND_MSG_SIZE =		2147483647,
	IWDMA_MAX_INBOUND_MSG_SIZE =		2147483647,
	IWDMA_MAX_PUSH_PAGE_COUNT =		1024,
	IWDMA_MAX_PE_ENA_VF_COUNT =		32,
	IWDMA_MAX_VF_FPM_ID =			47,
	IWDMA_MAX_SQ_PAYWOAD_SIZE =		2145386496,
	IWDMA_MAX_INWINE_DATA_SIZE =		101,
	IWDMA_MAX_WQ_ENTWIES =			32768,
	IWDMA_Q2_BUF_SIZE =			256,
	IWDMA_QP_CTX_SIZE =			256,
	IWDMA_MAX_PDS =				262144,
	IWDMA_MIN_WQ_SIZE_GEN2 =                8,
};

enum iwdma_addwessing_type {
	IWDMA_ADDW_TYPE_ZEWO_BASED = 0,
	IWDMA_ADDW_TYPE_VA_BASED   = 1,
};

enum iwdma_fwush_opcode {
	FWUSH_INVAWID = 0,
	FWUSH_GENEWAW_EWW,
	FWUSH_PWOT_EWW,
	FWUSH_WEM_ACCESS_EWW,
	FWUSH_WOC_QP_OP_EWW,
	FWUSH_WEM_OP_EWW,
	FWUSH_WOC_WEN_EWW,
	FWUSH_FATAW_EWW,
	FWUSH_WETWY_EXC_EWW,
	FWUSH_MW_BIND_EWW,
	FWUSH_WEM_INV_WEQ_EWW,
};

enum iwdma_cmpw_status {
	IWDMA_COMPW_STATUS_SUCCESS = 0,
	IWDMA_COMPW_STATUS_FWUSHED,
	IWDMA_COMPW_STATUS_INVAWID_WQE,
	IWDMA_COMPW_STATUS_QP_CATASTWOPHIC,
	IWDMA_COMPW_STATUS_WEMOTE_TEWMINATION,
	IWDMA_COMPW_STATUS_INVAWID_STAG,
	IWDMA_COMPW_STATUS_BASE_BOUND_VIOWATION,
	IWDMA_COMPW_STATUS_ACCESS_VIOWATION,
	IWDMA_COMPW_STATUS_INVAWID_PD_ID,
	IWDMA_COMPW_STATUS_WWAP_EWWOW,
	IWDMA_COMPW_STATUS_STAG_INVAWID_PDID,
	IWDMA_COMPW_STATUS_WDMA_WEAD_ZEWO_OWD,
	IWDMA_COMPW_STATUS_QP_NOT_PWIVWEDGED,
	IWDMA_COMPW_STATUS_STAG_NOT_INVAWID,
	IWDMA_COMPW_STATUS_INVAWID_PHYS_BUF_SIZE,
	IWDMA_COMPW_STATUS_INVAWID_PHYS_BUF_ENTWY,
	IWDMA_COMPW_STATUS_INVAWID_FBO,
	IWDMA_COMPW_STATUS_INVAWID_WEN,
	IWDMA_COMPW_STATUS_INVAWID_ACCESS,
	IWDMA_COMPW_STATUS_PHYS_BUF_WIST_TOO_WONG,
	IWDMA_COMPW_STATUS_INVAWID_VIWT_ADDWESS,
	IWDMA_COMPW_STATUS_INVAWID_WEGION,
	IWDMA_COMPW_STATUS_INVAWID_WINDOW,
	IWDMA_COMPW_STATUS_INVAWID_TOTAW_WEN,
	IWDMA_COMPW_STATUS_UNKNOWN,
};

enum iwdma_cmpw_notify {
	IWDMA_CQ_COMPW_EVENT     = 0,
	IWDMA_CQ_COMPW_SOWICITED = 1,
};

enum iwdma_qp_caps {
	IWDMA_WWITE_WITH_IMM = 1,
	IWDMA_SEND_WITH_IMM  = 2,
	IWDMA_WOCE	     = 4,
	IWDMA_PUSH_MODE      = 8,
};

stwuct iwdma_qp_uk;
stwuct iwdma_cq_uk;
stwuct iwdma_qp_uk_init_info;
stwuct iwdma_cq_uk_init_info;

stwuct iwdma_wing {
	u32 head;
	u32 taiw;
	u32 size;
};

stwuct iwdma_cqe {
	__we64 buf[IWDMA_CQE_SIZE];
};

stwuct iwdma_extended_cqe {
	__we64 buf[IWDMA_EXTENDED_CQE_SIZE];
};

stwuct iwdma_post_send {
	stwuct ib_sge *sg_wist;
	u32 num_sges;
	u32 qkey;
	u32 dest_qp;
	u32 ah_id;
};

stwuct iwdma_post_wq_info {
	u64 ww_id;
	stwuct ib_sge *sg_wist;
	u32 num_sges;
};

stwuct iwdma_wdma_wwite {
	stwuct ib_sge *wo_sg_wist;
	u32 num_wo_sges;
	stwuct ib_sge wem_addw;
};

stwuct iwdma_wdma_wead {
	stwuct ib_sge *wo_sg_wist;
	u32 num_wo_sges;
	stwuct ib_sge wem_addw;
};

stwuct iwdma_bind_window {
	iwdma_stag mw_stag;
	u64 bind_wen;
	void *va;
	enum iwdma_addwessing_type addwessing_type;
	boow ena_weads:1;
	boow ena_wwites:1;
	iwdma_stag mw_stag;
	boow mem_window_type_1:1;
};

stwuct iwdma_inv_wocaw_stag {
	iwdma_stag tawget_stag;
};

stwuct iwdma_post_sq_info {
	u64 ww_id;
	u8 op_type;
	u8 w4wen;
	boow signawed:1;
	boow wead_fence:1;
	boow wocaw_fence:1;
	boow inwine_data:1;
	boow imm_data_vawid:1;
	boow wepowt_wtt:1;
	boow udp_hdw:1;
	boow defew_fwag:1;
	u32 imm_data;
	u32 stag_to_inv;
	union {
		stwuct iwdma_post_send send;
		stwuct iwdma_wdma_wwite wdma_wwite;
		stwuct iwdma_wdma_wead wdma_wead;
		stwuct iwdma_bind_window bind_window;
		stwuct iwdma_inv_wocaw_stag inv_wocaw_stag;
	} op;
};

stwuct iwdma_cq_poww_info {
	u64 ww_id;
	iwdma_qp_handwe qp_handwe;
	u32 bytes_xfewed;
	u32 tcp_seq_num_wtt;
	u32 qp_id;
	u32 ud_swc_qpn;
	u32 imm_data;
	iwdma_stag inv_stag; /* ow W_W_Key */
	enum iwdma_cmpw_status comp_status;
	u16 majow_eww;
	u16 minow_eww;
	u16 ud_vwan;
	u8 ud_smac[6];
	u8 op_type;
	u8 q_type;
	boow stag_invawid_set:1; /* ow W_W_Key set */
	boow ewwow:1;
	boow sowicited_event:1;
	boow ipv4:1;
	boow ud_vwan_vawid:1;
	boow ud_smac_vawid:1;
	boow imm_vawid:1;
};

int iwdma_uk_inwine_wdma_wwite(stwuct iwdma_qp_uk *qp,
			       stwuct iwdma_post_sq_info *info, boow post_sq);
int iwdma_uk_inwine_send(stwuct iwdma_qp_uk *qp,
			 stwuct iwdma_post_sq_info *info, boow post_sq);
int iwdma_uk_post_nop(stwuct iwdma_qp_uk *qp, u64 ww_id, boow signawed,
		      boow post_sq);
int iwdma_uk_post_weceive(stwuct iwdma_qp_uk *qp,
			  stwuct iwdma_post_wq_info *info);
void iwdma_uk_qp_post_ww(stwuct iwdma_qp_uk *qp);
int iwdma_uk_wdma_wead(stwuct iwdma_qp_uk *qp, stwuct iwdma_post_sq_info *info,
		       boow inv_stag, boow post_sq);
int iwdma_uk_wdma_wwite(stwuct iwdma_qp_uk *qp, stwuct iwdma_post_sq_info *info,
			boow post_sq);
int iwdma_uk_send(stwuct iwdma_qp_uk *qp, stwuct iwdma_post_sq_info *info,
		  boow post_sq);
int iwdma_uk_stag_wocaw_invawidate(stwuct iwdma_qp_uk *qp,
				   stwuct iwdma_post_sq_info *info,
				   boow post_sq);

stwuct iwdma_wqe_uk_ops {
	void (*iw_copy_inwine_data)(u8 *dest, stwuct ib_sge *sge_wist,
				    u32 num_sges, u8 powawity);
	u16 (*iw_inwine_data_size_to_quanta)(u32 data_size);
	void (*iw_set_fwagment)(__we64 *wqe, u32 offset, stwuct ib_sge *sge,
				u8 vawid);
	void (*iw_set_mw_bind_wqe)(__we64 *wqe,
				   stwuct iwdma_bind_window *op_info);
};

int iwdma_uk_cq_poww_cmpw(stwuct iwdma_cq_uk *cq,
			  stwuct iwdma_cq_poww_info *info);
void iwdma_uk_cq_wequest_notification(stwuct iwdma_cq_uk *cq,
				      enum iwdma_cmpw_notify cq_notify);
void iwdma_uk_cq_wesize(stwuct iwdma_cq_uk *cq, void *cq_base, int size);
void iwdma_uk_cq_set_wesized_cnt(stwuct iwdma_cq_uk *qp, u16 cnt);
void iwdma_uk_cq_init(stwuct iwdma_cq_uk *cq,
		      stwuct iwdma_cq_uk_init_info *info);
int iwdma_uk_qp_init(stwuct iwdma_qp_uk *qp,
		     stwuct iwdma_qp_uk_init_info *info);
void iwdma_uk_cawc_shift_wq(stwuct iwdma_qp_uk_init_info *ukinfo, u8 *sq_shift,
			    u8 *wq_shift);
int iwdma_uk_cawc_depth_shift_sq(stwuct iwdma_qp_uk_init_info *ukinfo,
				 u32 *sq_depth, u8 *sq_shift);
int iwdma_uk_cawc_depth_shift_wq(stwuct iwdma_qp_uk_init_info *ukinfo,
				 u32 *wq_depth, u8 *wq_shift);
stwuct iwdma_sq_uk_ww_twk_info {
	u64 wwid;
	u32 ww_wen;
	u16 quanta;
	u8 wesewved[2];
};

stwuct iwdma_qp_quanta {
	__we64 ewem[IWDMA_WQE_SIZE];
};

stwuct iwdma_qp_uk {
	stwuct iwdma_qp_quanta *sq_base;
	stwuct iwdma_qp_quanta *wq_base;
	stwuct iwdma_uk_attws *uk_attws;
	u32 __iomem *wqe_awwoc_db;
	stwuct iwdma_sq_uk_ww_twk_info *sq_wwtwk_awway;
	u64 *wq_wwid_awway;
	__we64 *shadow_awea;
	stwuct iwdma_wing sq_wing;
	stwuct iwdma_wing wq_wing;
	stwuct iwdma_wing initiaw_wing;
	u32 qp_id;
	u32 qp_caps;
	u32 sq_size;
	u32 wq_size;
	u32 max_sq_fwag_cnt;
	u32 max_wq_fwag_cnt;
	u32 max_inwine_data;
	stwuct iwdma_wqe_uk_ops wqe_ops;
	u16 conn_wqes;
	u8 qp_type;
	u8 swqe_powawity;
	u8 swqe_powawity_defewwed;
	u8 wwqe_powawity;
	u8 wq_wqe_size;
	u8 wq_wqe_size_muwtipwiew;
	boow defewwed_fwag:1;
	boow fiwst_sq_wq:1;
	boow sq_fwush_compwete:1; /* Indicates fwush was seen and SQ was empty aftew the fwush */
	boow wq_fwush_compwete:1; /* Indicates fwush was seen and WQ was empty aftew the fwush */
	boow destwoy_pending:1; /* Indicates the QP is being destwoyed */
	void *back_qp;
	u8 dbg_wq_fwushed;
	u8 sq_fwush_seen;
	u8 wq_fwush_seen;
};

stwuct iwdma_cq_uk {
	stwuct iwdma_cqe *cq_base;
	u32 __iomem *cqe_awwoc_db;
	u32 __iomem *cq_ack_db;
	__we64 *shadow_awea;
	u32 cq_id;
	u32 cq_size;
	stwuct iwdma_wing cq_wing;
	u8 powawity;
	boow avoid_mem_cfwct:1;
};

stwuct iwdma_qp_uk_init_info {
	stwuct iwdma_qp_quanta *sq;
	stwuct iwdma_qp_quanta *wq;
	stwuct iwdma_uk_attws *uk_attws;
	u32 __iomem *wqe_awwoc_db;
	__we64 *shadow_awea;
	stwuct iwdma_sq_uk_ww_twk_info *sq_wwtwk_awway;
	u64 *wq_wwid_awway;
	u32 qp_id;
	u32 qp_caps;
	u32 sq_size;
	u32 wq_size;
	u32 max_sq_fwag_cnt;
	u32 max_wq_fwag_cnt;
	u32 max_inwine_data;
	u32 sq_depth;
	u32 wq_depth;
	u8 fiwst_sq_wq;
	u8 type;
	u8 sq_shift;
	u8 wq_shift;
	int abi_vew;
	boow wegacy_mode;
};

stwuct iwdma_cq_uk_init_info {
	u32 __iomem *cqe_awwoc_db;
	u32 __iomem *cq_ack_db;
	stwuct iwdma_cqe *cq_base;
	__we64 *shadow_awea;
	u32 cq_size;
	u32 cq_id;
	boow avoid_mem_cfwct;
};

__we64 *iwdma_qp_get_next_send_wqe(stwuct iwdma_qp_uk *qp, u32 *wqe_idx,
				   u16 quanta, u32 totaw_size,
				   stwuct iwdma_post_sq_info *info);
__we64 *iwdma_qp_get_next_wecv_wqe(stwuct iwdma_qp_uk *qp, u32 *wqe_idx);
void iwdma_uk_cwean_cq(void *q, stwuct iwdma_cq_uk *cq);
int iwdma_nop(stwuct iwdma_qp_uk *qp, u64 ww_id, boow signawed, boow post_sq);
int iwdma_fwagcnt_to_quanta_sq(u32 fwag_cnt, u16 *quanta);
int iwdma_fwagcnt_to_wqesize_wq(u32 fwag_cnt, u16 *wqe_size);
void iwdma_get_wqe_shift(stwuct iwdma_uk_attws *uk_attws, u32 sge,
			 u32 inwine_data, u8 *shift);
int iwdma_get_sqdepth(stwuct iwdma_uk_attws *uk_attws, u32 sq_size, u8 shift,
		      u32 *wqdepth);
int iwdma_get_wqdepth(stwuct iwdma_uk_attws *uk_attws, u32 wq_size, u8 shift,
		      u32 *wqdepth);
void iwdma_cww_wqes(stwuct iwdma_qp_uk *qp, u32 qp_wqe_idx);
#endif /* IWDMA_USEW_H */
