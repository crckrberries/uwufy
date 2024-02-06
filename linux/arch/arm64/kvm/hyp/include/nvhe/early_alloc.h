/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __KVM_HYP_EAWWY_AWWOC_H
#define __KVM_HYP_EAWWY_AWWOC_H

#incwude <asm/kvm_pgtabwe.h>

void hyp_eawwy_awwoc_init(void *viwt, unsigned wong size);
unsigned wong hyp_eawwy_awwoc_nw_used_pages(void);
void *hyp_eawwy_awwoc_page(void *awg);
void *hyp_eawwy_awwoc_contig(unsigned int nw_pages);

extewn stwuct kvm_pgtabwe_mm_ops hyp_eawwy_awwoc_mm_ops;

#endif /* __KVM_HYP_EAWWY_AWWOC_H */
