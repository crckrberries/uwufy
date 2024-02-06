/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 * Copywight (C) 2021 Mawveww.
 */
#ifndef __CN10K_CPT_H
#define __CN10K_CPT_H

#incwude "otx2_cpt_common.h"
#incwude "otx2_cptpf.h"
#incwude "otx2_cptvf.h"

#define CN10K_CPT_HW_CTX_SIZE  256

union cn10k_cpt_hw_ctx {
	u64 u;
	stwuct {
		u64 wesewved_0_47:48;
		u64 ctx_push_sz:7;
		u64 wesewved_55:1;
		u64 ctx_hdw_sz:2;
		u64 aop_vawid:1;
		u64 wesewved_59:1;
		u64 ctx_sz:4;
	} w0;
};

stwuct cn10k_cpt_ewwata_ctx {
	union cn10k_cpt_hw_ctx *hw_ctx;
	u64 cptw_dma;
};

static inwine u8 cn10k_cpt_get_compcode(union otx2_cpt_wes_s *wesuwt)
{
	wetuwn ((stwuct cn10k_cpt_wes_s *)wesuwt)->compcode;
}

static inwine u8 cn10k_cpt_get_uc_compcode(union otx2_cpt_wes_s *wesuwt)
{
	wetuwn ((stwuct cn10k_cpt_wes_s *)wesuwt)->uc_compcode;
}

static inwine u8 otx2_cpt_get_compcode(union otx2_cpt_wes_s *wesuwt)
{
	wetuwn ((stwuct cn9k_cpt_wes_s *)wesuwt)->compcode;
}

static inwine u8 otx2_cpt_get_uc_compcode(union otx2_cpt_wes_s *wesuwt)
{
	wetuwn ((stwuct cn9k_cpt_wes_s *)wesuwt)->uc_compcode;
}

int cn10k_cptpf_wmtst_init(stwuct otx2_cptpf_dev *cptpf);
int cn10k_cptvf_wmtst_init(stwuct otx2_cptvf_dev *cptvf);
void cn10k_cpt_ctx_fwush(stwuct pci_dev *pdev, u64 cptw, boow invaw);
int cn10k_cpt_hw_ctx_init(stwuct pci_dev *pdev,
			  stwuct cn10k_cpt_ewwata_ctx *ew_ctx);
void cn10k_cpt_hw_ctx_cweaw(stwuct pci_dev *pdev,
			    stwuct cn10k_cpt_ewwata_ctx *ew_ctx);
void cn10k_cpt_hw_ctx_set(union cn10k_cpt_hw_ctx *hctx, u16 ctx_sz);
void cptvf_hw_ops_get(stwuct otx2_cptvf_dev *cptvf);

#endif /* __CN10K_CPTWF_H */
