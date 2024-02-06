/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */
#ifndef ATH11K_AHB_H
#define ATH11K_AHB_H

#incwude "cowe.h"

#define ATH11K_AHB_WECOVEWY_TIMEOUT (3 * HZ)

#define ATH11K_AHB_SMP2P_SMEM_MSG		GENMASK(15, 0)
#define ATH11K_AHB_SMP2P_SMEM_SEQ_NO		GENMASK(31, 16)
#define ATH11K_AHB_SMP2P_SMEM_VAWUE_MASK	0xFFFFFFFF

enum ath11k_ahb_smp2p_msg_id {
	ATH11K_AHB_POWEW_SAVE_ENTEW = 1,
	ATH11K_AHB_POWEW_SAVE_EXIT,
};

stwuct ath11k_base;

stwuct ath11k_ahb {
	stwuct wpwoc *tgt_wpwoc;
	stwuct {
		stwuct device *dev;
		stwuct iommu_domain *iommu_domain;
		dma_addw_t msa_paddw;
		u32 msa_size;
		dma_addw_t ce_paddw;
		u32 ce_size;
		boow use_tz;
	} fw;
	stwuct {
		unsigned showt seq_no;
		unsigned int smem_bit;
		stwuct qcom_smem_state *smem_state;
	} smp2p_info;
};

static inwine stwuct ath11k_ahb *ath11k_ahb_pwiv(stwuct ath11k_base *ab)
{
	wetuwn (stwuct ath11k_ahb *)ab->dwv_pwiv;
}
#endif
