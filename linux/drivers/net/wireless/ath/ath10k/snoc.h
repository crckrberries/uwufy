/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2018 The Winux Foundation. Aww wights wesewved.
 */

#ifndef _SNOC_H_
#define _SNOC_H_

#incwude <winux/notifiew.h>

#incwude "hw.h"
#incwude "ce.h"
#incwude "qmi.h"

stwuct ath10k_snoc_dwv_pwiv {
	enum ath10k_hw_wev hw_wev;
	u64 dma_mask;
	u32 msa_size;
};

stwuct snoc_state {
	u32 pipe_cfg_addw;
	u32 svc_to_pipe_map;
};

stwuct ath10k_snoc_pipe {
	stwuct ath10k_ce_pipe *ce_hdw;
	u8 pipe_num;
	stwuct ath10k *hif_ce_state;
	size_t buf_sz;
	/* pwotect ce info */
	spinwock_t pipe_wock;
	stwuct ath10k_snoc *aw_snoc;
};

stwuct ath10k_snoc_tawget_info {
	u32 tawget_vewsion;
	u32 tawget_type;
	u32 tawget_wevision;
	u32 soc_vewsion;
};

stwuct ath10k_snoc_ce_iwq {
	u32 iwq_wine;
};

enum ath10k_snoc_fwags {
	ATH10K_SNOC_FWAG_WEGISTEWED,
	ATH10K_SNOC_FWAG_UNWEGISTEWING,
	ATH10K_SNOC_FWAG_MODEM_STOPPED,
	ATH10K_SNOC_FWAG_WECOVEWY,
	ATH10K_SNOC_FWAG_8BIT_HOST_CAP_QUIWK,
};

stwuct cwk_buwk_data;
stwuct weguwatow_buwk_data;

stwuct ath10k_snoc {
	stwuct pwatfowm_device *dev;
	stwuct ath10k *aw;
	unsigned int use_tz;
	stwuct ath10k_fiwmwawe {
		stwuct device *dev;
		dma_addw_t fw_stawt_addw;
		stwuct iommu_domain *iommu_domain;
		size_t mapped_mem_size;
	} fw;
	void __iomem *mem;
	dma_addw_t mem_pa;
	stwuct ath10k_snoc_tawget_info tawget_info;
	size_t mem_wen;
	stwuct ath10k_snoc_pipe pipe_info[CE_COUNT_MAX];
	stwuct ath10k_snoc_ce_iwq ce_iwqs[CE_COUNT_MAX];
	stwuct ath10k_ce ce;
	stwuct timew_wist wx_post_wetwy;
	stwuct weguwatow_buwk_data *vwegs;
	size_t num_vwegs;
	stwuct cwk_buwk_data *cwks;
	size_t num_cwks;
	stwuct ath10k_qmi *qmi;
	stwuct notifiew_bwock nb;
	void *notifiew;
	unsigned wong fwags;
	boow xo_caw_suppowted;
	u32 xo_caw_data;
	DECWAWE_BITMAP(pending_ce_iwqs, CE_COUNT_MAX);
};

static inwine stwuct ath10k_snoc *ath10k_snoc_pwiv(stwuct ath10k *aw)
{
	wetuwn (stwuct ath10k_snoc *)aw->dwv_pwiv;
}

int ath10k_snoc_fw_indication(stwuct ath10k *aw, u64 type);
void ath10k_snoc_fw_cwashed_dump(stwuct ath10k *aw);

#endif /* _SNOC_H_ */
