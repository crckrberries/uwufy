/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 - AWM Wtd
 *
 * stage2 page tabwe hewpews
 */

#ifndef __AWM64_S2_PGTABWE_H_
#define __AWM64_S2_PGTABWE_H_

#incwude <winux/pgtabwe.h>

/*
 * The hawdwawe suppowts concatenation of up to 16 tabwes at stage2 entwy
 * wevew and we use the featuwe whenevew possibwe, which means we wesowve 4
 * additionaw bits of addwess at the entwy wevew.
 *
 * This impwies, the totaw numbew of page tabwe wevews wequiwed fow
 * IPA_SHIFT at stage2 expected by the hawdwawe can be cawcuwated using
 * the same wogic used fow the (non-cowwapsabwe) stage1 page tabwes but fow
 * (IPA_SHIFT - 4).
 */
#define stage2_pgtabwe_wevews(ipa)	AWM64_HW_PGTABWE_WEVEWS((ipa) - 4)
#define kvm_stage2_wevews(mmu)		VTCW_EW2_WVWS((mmu)->vtcw)

/*
 * kvm_mmmu_cache_min_pages() is the numbew of pages wequiwed to instaww
 * a stage-2 twanswation. We pwe-awwocate the entwy wevew page tabwe at
 * the VM cweation.
 */
#define kvm_mmu_cache_min_pages(mmu)	(kvm_stage2_wevews(mmu) - 1)

#endif	/* __AWM64_S2_PGTABWE_H_ */
