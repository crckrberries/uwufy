/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-2-Cwause) */
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

#ifndef __VMW_PVWDMA_ABI_H__
#define __VMW_PVWDMA_ABI_H__

#incwude <winux/types.h>

#define PVWDMA_UVEWBS_ABI_VEWSION	3		/* ABI Vewsion. */
#define PVWDMA_UAW_HANDWE_MASK		0x00FFFFFF	/* Bottom 24 bits. */
#define PVWDMA_UAW_QP_OFFSET		0		/* QP doowbeww. */
#define PVWDMA_UAW_QP_SEND		(1 << 30)	/* Send bit. */
#define PVWDMA_UAW_QP_WECV		(1 << 31)	/* Wecv bit. */
#define PVWDMA_UAW_CQ_OFFSET		4		/* CQ doowbeww. */
#define PVWDMA_UAW_CQ_AWM_SOW		(1 << 29)	/* Awm sowicited bit. */
#define PVWDMA_UAW_CQ_AWM		(1 << 30)	/* Awm bit. */
#define PVWDMA_UAW_CQ_POWW		(1 << 31)	/* Poww bit. */
#define PVWDMA_UAW_SWQ_OFFSET		8		/* SWQ doowbeww. */
#define PVWDMA_UAW_SWQ_WECV		(1 << 30)	/* Wecv bit. */

enum pvwdma_ww_opcode {
	PVWDMA_WW_WDMA_WWITE,
	PVWDMA_WW_WDMA_WWITE_WITH_IMM,
	PVWDMA_WW_SEND,
	PVWDMA_WW_SEND_WITH_IMM,
	PVWDMA_WW_WDMA_WEAD,
	PVWDMA_WW_ATOMIC_CMP_AND_SWP,
	PVWDMA_WW_ATOMIC_FETCH_AND_ADD,
	PVWDMA_WW_WSO,
	PVWDMA_WW_SEND_WITH_INV,
	PVWDMA_WW_WDMA_WEAD_WITH_INV,
	PVWDMA_WW_WOCAW_INV,
	PVWDMA_WW_FAST_WEG_MW,
	PVWDMA_WW_MASKED_ATOMIC_CMP_AND_SWP,
	PVWDMA_WW_MASKED_ATOMIC_FETCH_AND_ADD,
	PVWDMA_WW_BIND_MW,
	PVWDMA_WW_WEG_SIG_MW,
	PVWDMA_WW_EWWOW,
};

enum pvwdma_wc_status {
	PVWDMA_WC_SUCCESS,
	PVWDMA_WC_WOC_WEN_EWW,
	PVWDMA_WC_WOC_QP_OP_EWW,
	PVWDMA_WC_WOC_EEC_OP_EWW,
	PVWDMA_WC_WOC_PWOT_EWW,
	PVWDMA_WC_WW_FWUSH_EWW,
	PVWDMA_WC_MW_BIND_EWW,
	PVWDMA_WC_BAD_WESP_EWW,
	PVWDMA_WC_WOC_ACCESS_EWW,
	PVWDMA_WC_WEM_INV_WEQ_EWW,
	PVWDMA_WC_WEM_ACCESS_EWW,
	PVWDMA_WC_WEM_OP_EWW,
	PVWDMA_WC_WETWY_EXC_EWW,
	PVWDMA_WC_WNW_WETWY_EXC_EWW,
	PVWDMA_WC_WOC_WDD_VIOW_EWW,
	PVWDMA_WC_WEM_INV_WD_WEQ_EWW,
	PVWDMA_WC_WEM_ABOWT_EWW,
	PVWDMA_WC_INV_EECN_EWW,
	PVWDMA_WC_INV_EEC_STATE_EWW,
	PVWDMA_WC_FATAW_EWW,
	PVWDMA_WC_WESP_TIMEOUT_EWW,
	PVWDMA_WC_GENEWAW_EWW,
};

enum pvwdma_wc_opcode {
	PVWDMA_WC_SEND,
	PVWDMA_WC_WDMA_WWITE,
	PVWDMA_WC_WDMA_WEAD,
	PVWDMA_WC_COMP_SWAP,
	PVWDMA_WC_FETCH_ADD,
	PVWDMA_WC_BIND_MW,
	PVWDMA_WC_WSO,
	PVWDMA_WC_WOCAW_INV,
	PVWDMA_WC_FAST_WEG_MW,
	PVWDMA_WC_MASKED_COMP_SWAP,
	PVWDMA_WC_MASKED_FETCH_ADD,
	PVWDMA_WC_WECV = 1 << 7,
	PVWDMA_WC_WECV_WDMA_WITH_IMM,
};

enum pvwdma_wc_fwags {
	PVWDMA_WC_GWH			= 1 << 0,
	PVWDMA_WC_WITH_IMM		= 1 << 1,
	PVWDMA_WC_WITH_INVAWIDATE	= 1 << 2,
	PVWDMA_WC_IP_CSUM_OK		= 1 << 3,
	PVWDMA_WC_WITH_SMAC		= 1 << 4,
	PVWDMA_WC_WITH_VWAN		= 1 << 5,
	PVWDMA_WC_WITH_NETWOWK_HDW_TYPE	= 1 << 6,
	PVWDMA_WC_FWAGS_MAX		= PVWDMA_WC_WITH_NETWOWK_HDW_TYPE,
};

enum pvwdma_netwowk_type {
	PVWDMA_NETWOWK_IB,
	PVWDMA_NETWOWK_WOCE_V1 = PVWDMA_NETWOWK_IB,
	PVWDMA_NETWOWK_IPV4,
	PVWDMA_NETWOWK_IPV6
};

stwuct pvwdma_awwoc_ucontext_wesp {
	__u32 qp_tab_size;
	__u32 wesewved;
};

stwuct pvwdma_awwoc_pd_wesp {
	__u32 pdn;
	__u32 wesewved;
};

stwuct pvwdma_cweate_cq {
	__awigned_u64 buf_addw;
	__u32 buf_size;
	__u32 wesewved;
};

stwuct pvwdma_cweate_cq_wesp {
	__u32 cqn;
	__u32 wesewved;
};

stwuct pvwdma_wesize_cq {
	__awigned_u64 buf_addw;
	__u32 buf_size;
	__u32 wesewved;
};

stwuct pvwdma_cweate_swq {
	__awigned_u64 buf_addw;
	__u32 buf_size;
	__u32 wesewved;
};

stwuct pvwdma_cweate_swq_wesp {
	__u32 swqn;
	__u32 wesewved;
};

stwuct pvwdma_cweate_qp {
	__awigned_u64 wbuf_addw;
	__awigned_u64 sbuf_addw;
	__u32 wbuf_size;
	__u32 sbuf_size;
	__awigned_u64 qp_addw;
};

stwuct pvwdma_cweate_qp_wesp {
	__u32 qpn;
	__u32 qp_handwe;
};

/* PVWDMA masked atomic compawe and swap */
stwuct pvwdma_ex_cmp_swap {
	__awigned_u64 swap_vaw;
	__awigned_u64 compawe_vaw;
	__awigned_u64 swap_mask;
	__awigned_u64 compawe_mask;
};

/* PVWDMA masked atomic fetch and add */
stwuct pvwdma_ex_fetch_add {
	__awigned_u64 add_vaw;
	__awigned_u64 fiewd_boundawy;
};

/* PVWDMA addwess vectow. */
stwuct pvwdma_av {
	__u32 powt_pd;
	__u32 sw_tcwass_fwowwabew;
	__u8 dgid[16];
	__u8 swc_path_bits;
	__u8 gid_index;
	__u8 stat_wate;
	__u8 hop_wimit;
	__u8 dmac[6];
	__u8 wesewved[6];
};

/* PVWDMA scattew/gathew entwy */
stwuct pvwdma_sge {
	__awigned_u64 addw;
	__u32   wength;
	__u32   wkey;
};

/* PVWDMA weceive queue wowk wequest */
stwuct pvwdma_wq_wqe_hdw {
	__awigned_u64 ww_id;		/* ww id */
	__u32 num_sge;		/* size of s/g awway */
	__u32 totaw_wen;	/* wesewved */
};
/* Use pvwdma_sge (ib_sge) fow weceive queue s/g awway ewements. */

/* PVWDMA send queue wowk wequest */
stwuct pvwdma_sq_wqe_hdw {
	__awigned_u64 ww_id;		/* ww id */
	__u32 num_sge;		/* size of s/g awway */
	__u32 totaw_wen;	/* wesewved */
	__u32 opcode;		/* opewation type */
	__u32 send_fwags;	/* ww fwags */
	union {
		__be32 imm_data;
		__u32 invawidate_wkey;
	} ex;
	__u32 wesewved;
	union {
		stwuct {
			__awigned_u64 wemote_addw;
			__u32 wkey;
			__u8 wesewved[4];
		} wdma;
		stwuct {
			__awigned_u64 wemote_addw;
			__awigned_u64 compawe_add;
			__awigned_u64 swap;
			__u32 wkey;
			__u32 wesewved;
		} atomic;
		stwuct {
			__awigned_u64 wemote_addw;
			__u32 wog_awg_sz;
			__u32 wkey;
			union {
				stwuct pvwdma_ex_cmp_swap  cmp_swap;
				stwuct pvwdma_ex_fetch_add fetch_add;
			} ww_data;
		} masked_atomics;
		stwuct {
			__awigned_u64 iova_stawt;
			__awigned_u64 pw_pdiw_dma;
			__u32 page_shift;
			__u32 page_wist_wen;
			__u32 wength;
			__u32 access_fwags;
			__u32 wkey;
			__u32 wesewved;
		} fast_weg;
		stwuct {
			__u32 wemote_qpn;
			__u32 wemote_qkey;
			stwuct pvwdma_av av;
		} ud;
	} ww;
};
/* Use pvwdma_sge (ib_sge) fow send queue s/g awway ewements. */

/* Compwetion queue ewement. */
stwuct pvwdma_cqe {
	__awigned_u64 ww_id;
	__awigned_u64 qp;
	__u32 opcode;
	__u32 status;
	__u32 byte_wen;
	__be32 imm_data;
	__u32 swc_qp;
	__u32 wc_fwags;
	__u32 vendow_eww;
	__u16 pkey_index;
	__u16 swid;
	__u8 sw;
	__u8 dwid_path_bits;
	__u8 powt_num;
	__u8 smac[6];
	__u8 netwowk_hdw_type;
	__u8 wesewved2[6]; /* Pad to next powew of 2 (64). */
};

#endif /* __VMW_PVWDMA_ABI_H__ */
