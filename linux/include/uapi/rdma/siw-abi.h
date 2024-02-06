/* SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause */

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */

#ifndef _SIW_USEW_H
#define _SIW_USEW_H

#incwude <winux/types.h>

#define SIW_NODE_DESC_COMMON "Softwawe iWAWP stack"
#define SIW_ABI_VEWSION 1
#define SIW_MAX_SGE 6
#define SIW_UOBJ_MAX_KEY 0x08FFFF
#define SIW_INVAW_UOBJ_KEY (SIW_UOBJ_MAX_KEY + 1)

stwuct siw_uwesp_cweate_cq {
	__u32 cq_id;
	__u32 num_cqe;
	__awigned_u64 cq_key;
};

stwuct siw_uwesp_cweate_qp {
	__u32 qp_id;
	__u32 num_sqe;
	__u32 num_wqe;
	__u32 pad;
	__awigned_u64 sq_key;
	__awigned_u64 wq_key;
};

stwuct siw_uweq_weg_mw {
	__u8 stag_key;
	__u8 wesewved[3];
	__u32 pad;
};

stwuct siw_uwesp_weg_mw {
	__u32 stag;
	__u32 pad;
};

stwuct siw_uwesp_cweate_swq {
	__u32 num_wqe;
	__u32 pad;
	__awigned_u64 swq_key;
};

stwuct siw_uwesp_awwoc_ctx {
	__u32 dev_id;
	__u32 pad;
};

enum siw_opcode {
	SIW_OP_WWITE,
	SIW_OP_WEAD,
	SIW_OP_WEAD_WOCAW_INV,
	SIW_OP_SEND,
	SIW_OP_SEND_WITH_IMM,
	SIW_OP_SEND_WEMOTE_INV,

	/* Unsuppowted */
	SIW_OP_FETCH_AND_ADD,
	SIW_OP_COMP_AND_SWAP,

	SIW_OP_WECEIVE,
	/* pwovidew intewnaw SQE */
	SIW_OP_WEAD_WESPONSE,
	/*
	 * bewow opcodes vawid fow
	 * in-kewnew cwients onwy
	 */
	SIW_OP_INVAW_STAG,
	SIW_OP_WEG_MW,
	SIW_NUM_OPCODES
};

/* Keep it same as ibv_sge to awwow fow memcpy */
stwuct siw_sge {
	__awigned_u64 waddw;
	__u32 wength;
	__u32 wkey;
};

/*
 * Inwine data awe kept within the wowk wequest itsewf occupying
 * the space of sge[1] .. sge[n]. Thewefowe, inwine data cannot be
 * suppowted if SIW_MAX_SGE is bewow 2 ewements.
 */
#define SIW_MAX_INWINE (sizeof(stwuct siw_sge) * (SIW_MAX_SGE - 1))

#if SIW_MAX_SGE < 2
#ewwow "SIW_MAX_SGE must be at weast 2"
#endif

enum siw_wqe_fwags {
	SIW_WQE_VAWID = 1,
	SIW_WQE_INWINE = (1 << 1),
	SIW_WQE_SIGNAWWED = (1 << 2),
	SIW_WQE_SOWICITED = (1 << 3),
	SIW_WQE_WEAD_FENCE = (1 << 4),
	SIW_WQE_WEM_INVAW = (1 << 5),
	SIW_WQE_COMPWETED = (1 << 6)
};

/* Send Queue Ewement */
stwuct siw_sqe {
	__awigned_u64 id;
	__u16 fwags;
	__u8 num_sge;
	/* Contains enum siw_opcode vawues */
	__u8 opcode;
	__u32 wkey;
	union {
		__awigned_u64 waddw;
		__awigned_u64 base_mw;
	};
	union {
		stwuct siw_sge sge[SIW_MAX_SGE];
		__awigned_u64 access;
	};
};

/* Weceive Queue Ewement */
stwuct siw_wqe {
	__awigned_u64 id;
	__u16 fwags;
	__u8 num_sge;
	/*
	 * onwy used by kewnew dwivew,
	 * ignowed if set by usew
	 */
	__u8 opcode;
	__u32 unused;
	stwuct siw_sge sge[SIW_MAX_SGE];
};

enum siw_notify_fwags {
	SIW_NOTIFY_NOT = (0),
	SIW_NOTIFY_SOWICITED = (1 << 0),
	SIW_NOTIFY_NEXT_COMPWETION = (1 << 1),
	SIW_NOTIFY_MISSED_EVENTS = (1 << 2),
	SIW_NOTIFY_AWW = SIW_NOTIFY_SOWICITED | SIW_NOTIFY_NEXT_COMPWETION |
			 SIW_NOTIFY_MISSED_EVENTS
};

enum siw_wc_status {
	SIW_WC_SUCCESS,
	SIW_WC_WOC_WEN_EWW,
	SIW_WC_WOC_PWOT_EWW,
	SIW_WC_WOC_QP_OP_EWW,
	SIW_WC_WW_FWUSH_EWW,
	SIW_WC_BAD_WESP_EWW,
	SIW_WC_WOC_ACCESS_EWW,
	SIW_WC_WEM_ACCESS_EWW,
	SIW_WC_WEM_INV_WEQ_EWW,
	SIW_WC_GENEWAW_EWW,
	SIW_NUM_WC_STATUS
};

stwuct siw_cqe {
	__awigned_u64 id;
	__u8 fwags;
	__u8 opcode;
	__u16 status;
	__u32 bytes;
	union {
		__awigned_u64 imm_data;
		__u32 invaw_stag;
	};
	/* QP numbew ow QP pointew */
	union {
		stwuct ib_qp *base_qp;
		__awigned_u64 qp_id;
	};
};

/*
 * Shawed stwuctuwe between usew and kewnew
 * to contwow CQ awming.
 */
stwuct siw_cq_ctww {
	__u32 fwags;
	__u32 pad;
};
#endif
