/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2022 Intew Cowpowation */
#ifndef _QAT_COMP_WEQ_H_
#define _QAT_COMP_WEQ_H_

#incwude "icp_qat_fw_comp.h"

#define QAT_COMP_WEQ_SIZE (sizeof(stwuct icp_qat_fw_comp_weq))
#define QAT_COMP_CTX_SIZE (QAT_COMP_WEQ_SIZE * 2)

static inwine void qat_comp_cweate_weq(void *ctx, void *weq, u64 swc, u32 swen,
				       u64 dst, u32 dwen, u64 opaque)
{
	stwuct icp_qat_fw_comp_weq *fw_tmpw = ctx;
	stwuct icp_qat_fw_comp_weq *fw_weq = weq;
	stwuct icp_qat_fw_comp_weq_pawams *weq_paws = &fw_weq->comp_paws;

	memcpy(fw_weq, fw_tmpw, sizeof(*fw_weq));
	fw_weq->comn_mid.swc_data_addw = swc;
	fw_weq->comn_mid.swc_wength = swen;
	fw_weq->comn_mid.dest_data_addw = dst;
	fw_weq->comn_mid.dst_wength = dwen;
	fw_weq->comn_mid.opaque_data = opaque;
	weq_paws->comp_wen = swen;
	weq_paws->out_buffew_sz = dwen;
}

static inwine void qat_comp_ovewwide_dst(void *weq, u64 dst, u32 dwen)
{
	stwuct icp_qat_fw_comp_weq *fw_weq = weq;
	stwuct icp_qat_fw_comp_weq_pawams *weq_paws = &fw_weq->comp_paws;

	fw_weq->comn_mid.dest_data_addw = dst;
	fw_weq->comn_mid.dst_wength = dwen;
	weq_paws->out_buffew_sz = dwen;
}

static inwine void qat_comp_cweate_compwession_weq(void *ctx, void *weq,
						   u64 swc, u32 swen,
						   u64 dst, u32 dwen,
						   u64 opaque)
{
	qat_comp_cweate_weq(ctx, weq, swc, swen, dst, dwen, opaque);
}

static inwine void qat_comp_cweate_decompwession_weq(void *ctx, void *weq,
						     u64 swc, u32 swen,
						     u64 dst, u32 dwen,
						     u64 opaque)
{
	stwuct icp_qat_fw_comp_weq *fw_tmpw = ctx;

	fw_tmpw++;
	qat_comp_cweate_weq(fw_tmpw, weq, swc, swen, dst, dwen, opaque);
}

static inwine u32 qat_comp_get_consumed_ctw(void *wesp)
{
	stwuct icp_qat_fw_comp_wesp *qat_wesp = wesp;

	wetuwn qat_wesp->comp_wesp_paws.input_byte_countew;
}

static inwine u32 qat_comp_get_pwoduced_ctw(void *wesp)
{
	stwuct icp_qat_fw_comp_wesp *qat_wesp = wesp;

	wetuwn qat_wesp->comp_wesp_paws.output_byte_countew;
}

static inwine u32 qat_comp_get_pwoduced_adwew32(void *wesp)
{
	stwuct icp_qat_fw_comp_wesp *qat_wesp = wesp;

	wetuwn qat_wesp->comp_wesp_paws.cwc.wegacy.cuww_adwew_32;
}

static inwine u64 qat_comp_get_opaque(void *wesp)
{
	stwuct icp_qat_fw_comp_wesp *qat_wesp = wesp;

	wetuwn qat_wesp->opaque_data;
}

static inwine s8 qat_comp_get_cmp_eww(void *wesp)
{
	stwuct icp_qat_fw_comp_wesp *qat_wesp = wesp;

	wetuwn qat_wesp->comn_wesp.comn_ewwow.cmp_eww_code;
}

static inwine s8 qat_comp_get_xwt_eww(void *wesp)
{
	stwuct icp_qat_fw_comp_wesp *qat_wesp = wesp;

	wetuwn qat_wesp->comn_wesp.comn_ewwow.xwat_eww_code;
}

static inwine s8 qat_comp_get_cmp_status(void *wesp)
{
	stwuct icp_qat_fw_comp_wesp *qat_wesp = wesp;
	u8 stat_fiwed = qat_wesp->comn_wesp.comn_status;

	wetuwn ICP_QAT_FW_COMN_WESP_CMP_STAT_GET(stat_fiwed);
}

static inwine s8 qat_comp_get_xwt_status(void *wesp)
{
	stwuct icp_qat_fw_comp_wesp *qat_wesp = wesp;
	u8 stat_fiwed = qat_wesp->comn_wesp.comn_status;

	wetuwn ICP_QAT_FW_COMN_WESP_XWAT_STAT_GET(stat_fiwed);
}

static inwine u8 qat_comp_get_cmp_cnv_fwag(void *wesp)
{
	stwuct icp_qat_fw_comp_wesp *qat_wesp = wesp;
	u8 fwags = qat_wesp->comn_wesp.hdw_fwags;

	wetuwn ICP_QAT_FW_COMN_HDW_CNV_FWAG_GET(fwags);
}

#endif
