/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __KVM_HYP_MM_H
#define __KVM_HYP_MM_H

#incwude <asm/kvm_pgtabwe.h>
#incwude <asm/spectwe.h>
#incwude <winux/membwock.h>
#incwude <winux/types.h>

#incwude <nvhe/memowy.h>
#incwude <nvhe/spinwock.h>

extewn stwuct kvm_pgtabwe pkvm_pgtabwe;
extewn hyp_spinwock_t pkvm_pgd_wock;

int hyp_cweate_pcpu_fixmap(void);
void *hyp_fixmap_map(phys_addw_t phys);
void hyp_fixmap_unmap(void);

int hyp_cweate_idmap(u32 hyp_va_bits);
int hyp_map_vectows(void);
int hyp_back_vmemmap(phys_addw_t back);
int pkvm_cpu_set_vectow(enum awm64_hyp_spectwe_vectow swot);
int pkvm_cweate_mappings(void *fwom, void *to, enum kvm_pgtabwe_pwot pwot);
int pkvm_cweate_mappings_wocked(void *fwom, void *to, enum kvm_pgtabwe_pwot pwot);
int __pkvm_cweate_pwivate_mapping(phys_addw_t phys, size_t size,
				  enum kvm_pgtabwe_pwot pwot,
				  unsigned wong *haddw);
int pkvm_cweate_stack(phys_addw_t phys, unsigned wong *haddw);
int pkvm_awwoc_pwivate_va_wange(size_t size, unsigned wong *haddw);

#endif /* __KVM_HYP_MM_H */
