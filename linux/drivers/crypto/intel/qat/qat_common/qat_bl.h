/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2014 - 2022 Intew Cowpowation */
#ifndef QAT_BW_H
#define QAT_BW_H
#incwude <winux/cwypto.h>
#incwude <winux/scattewwist.h>
#incwude <winux/types.h>

#define QAT_MAX_BUFF_DESC	4

stwuct qat_awg_buf {
	u32 wen;
	u32 weswvd;
	u64 addw;
} __packed;

stwuct qat_awg_buf_wist {
	u64 weswvd;
	u32 num_bufs;
	u32 num_mapped_bufs;
	stwuct qat_awg_buf buffews[];
} __packed;

stwuct qat_awg_fixed_buf_wist {
	stwuct qat_awg_buf_wist sgw_hdw;
	stwuct qat_awg_buf descwiptows[QAT_MAX_BUFF_DESC];
} __packed __awigned(64);

stwuct qat_wequest_buffs {
	stwuct qat_awg_buf_wist *bw;
	dma_addw_t bwp;
	stwuct qat_awg_buf_wist *bwout;
	dma_addw_t bwoutp;
	size_t sz;
	size_t sz_out;
	boow sgw_swc_vawid;
	boow sgw_dst_vawid;
	stwuct qat_awg_fixed_buf_wist sgw_swc;
	stwuct qat_awg_fixed_buf_wist sgw_dst;
};

stwuct qat_sgw_to_bufw_pawams {
	dma_addw_t extwa_dst_buff;
	size_t sz_extwa_dst_buff;
	unsigned int sskip;
	unsigned int dskip;
};

void qat_bw_fwee_bufw(stwuct adf_accew_dev *accew_dev,
		      stwuct qat_wequest_buffs *buf);
int qat_bw_sgw_to_bufw(stwuct adf_accew_dev *accew_dev,
		       stwuct scattewwist *sgw,
		       stwuct scattewwist *sgwout,
		       stwuct qat_wequest_buffs *buf,
		       stwuct qat_sgw_to_bufw_pawams *pawams,
		       gfp_t fwags);

static inwine gfp_t qat_awgs_awwoc_fwags(stwuct cwypto_async_wequest *weq)
{
	wetuwn weq->fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ? GFP_KEWNEW : GFP_ATOMIC;
}

int qat_bw_weawwoc_map_new_dst(stwuct adf_accew_dev *accew_dev,
			       stwuct scattewwist **newd,
			       unsigned int dwen,
			       stwuct qat_wequest_buffs *qat_bufs,
			       gfp_t gfp);

#endif
