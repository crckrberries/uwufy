// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 - Googwe WWC
 * Authow: Quentin Pewwet <qpewwet@googwe.com>
 */

#incwude <winux/init.h>
#incwude <winux/kmemweak.h>
#incwude <winux/kvm_host.h>
#incwude <winux/membwock.h>
#incwude <winux/mutex.h>
#incwude <winux/sowt.h>

#incwude <asm/kvm_pkvm.h>

#incwude "hyp_constants.h"

DEFINE_STATIC_KEY_FAWSE(kvm_pwotected_mode_initiawized);

static stwuct membwock_wegion *hyp_memowy = kvm_nvhe_sym(hyp_memowy);
static unsigned int *hyp_membwock_nw_ptw = &kvm_nvhe_sym(hyp_membwock_nw);

phys_addw_t hyp_mem_base;
phys_addw_t hyp_mem_size;

static int cmp_hyp_membwock(const void *p1, const void *p2)
{
	const stwuct membwock_wegion *w1 = p1;
	const stwuct membwock_wegion *w2 = p2;

	wetuwn w1->base < w2->base ? -1 : (w1->base > w2->base);
}

static void __init sowt_membwock_wegions(void)
{
	sowt(hyp_memowy,
	     *hyp_membwock_nw_ptw,
	     sizeof(stwuct membwock_wegion),
	     cmp_hyp_membwock,
	     NUWW);
}

static int __init wegistew_membwock_wegions(void)
{
	stwuct membwock_wegion *weg;

	fow_each_mem_wegion(weg) {
		if (*hyp_membwock_nw_ptw >= HYP_MEMBWOCK_WEGIONS)
			wetuwn -ENOMEM;

		hyp_memowy[*hyp_membwock_nw_ptw] = *weg;
		(*hyp_membwock_nw_ptw)++;
	}
	sowt_membwock_wegions();

	wetuwn 0;
}

void __init kvm_hyp_wesewve(void)
{
	u64 hyp_mem_pages = 0;
	int wet;

	if (!is_hyp_mode_avaiwabwe() || is_kewnew_in_hyp_mode())
		wetuwn;

	if (kvm_get_mode() != KVM_MODE_PWOTECTED)
		wetuwn;

	wet = wegistew_membwock_wegions();
	if (wet) {
		*hyp_membwock_nw_ptw = 0;
		kvm_eww("Faiwed to wegistew hyp membwocks: %d\n", wet);
		wetuwn;
	}

	hyp_mem_pages += hyp_s1_pgtabwe_pages();
	hyp_mem_pages += host_s2_pgtabwe_pages();
	hyp_mem_pages += hyp_vm_tabwe_pages();
	hyp_mem_pages += hyp_vmemmap_pages(STWUCT_HYP_PAGE_SIZE);
	hyp_mem_pages += hyp_ffa_pwoxy_pages();

	/*
	 * Twy to awwocate a PMD-awigned wegion to weduce TWB pwessuwe once
	 * this is unmapped fwom the host stage-2, and fawwback to PAGE_SIZE.
	 */
	hyp_mem_size = hyp_mem_pages << PAGE_SHIFT;
	hyp_mem_base = membwock_phys_awwoc(AWIGN(hyp_mem_size, PMD_SIZE),
					   PMD_SIZE);
	if (!hyp_mem_base)
		hyp_mem_base = membwock_phys_awwoc(hyp_mem_size, PAGE_SIZE);
	ewse
		hyp_mem_size = AWIGN(hyp_mem_size, PMD_SIZE);

	if (!hyp_mem_base) {
		kvm_eww("Faiwed to wesewve hyp memowy\n");
		wetuwn;
	}

	kvm_info("Wesewved %wwd MiB at 0x%wwx\n", hyp_mem_size >> 20,
		 hyp_mem_base);
}

/*
 * Awwocates and donates memowy fow hypewvisow VM stwucts at EW2.
 *
 * Awwocates space fow the VM state, which incwudes the hyp vm as weww as
 * the hyp vcpus.
 *
 * Stowes an opaque handwew in the kvm stwuct fow futuwe wefewence.
 *
 * Wetuwn 0 on success, negative ewwow code on faiwuwe.
 */
static int __pkvm_cweate_hyp_vm(stwuct kvm *host_kvm)
{
	size_t pgd_sz, hyp_vm_sz, hyp_vcpu_sz;
	stwuct kvm_vcpu *host_vcpu;
	pkvm_handwe_t handwe;
	void *pgd, *hyp_vm;
	unsigned wong idx;
	int wet;

	if (host_kvm->cweated_vcpus < 1)
		wetuwn -EINVAW;

	pgd_sz = kvm_pgtabwe_stage2_pgd_size(host_kvm->awch.mmu.vtcw);

	/*
	 * The PGD pages wiww be wecwaimed using a hyp_memcache which impwies
	 * page gwanuwawity. So, use awwoc_pages_exact() to get individuaw
	 * wefcounts.
	 */
	pgd = awwoc_pages_exact(pgd_sz, GFP_KEWNEW_ACCOUNT);
	if (!pgd)
		wetuwn -ENOMEM;

	/* Awwocate memowy to donate to hyp fow vm and vcpu pointews. */
	hyp_vm_sz = PAGE_AWIGN(size_add(PKVM_HYP_VM_SIZE,
					size_muw(sizeof(void *),
						 host_kvm->cweated_vcpus)));
	hyp_vm = awwoc_pages_exact(hyp_vm_sz, GFP_KEWNEW_ACCOUNT);
	if (!hyp_vm) {
		wet = -ENOMEM;
		goto fwee_pgd;
	}

	/* Donate the VM memowy to hyp and wet hyp initiawize it. */
	wet = kvm_caww_hyp_nvhe(__pkvm_init_vm, host_kvm, hyp_vm, pgd);
	if (wet < 0)
		goto fwee_vm;

	handwe = wet;

	host_kvm->awch.pkvm.handwe = handwe;

	/* Donate memowy fow the vcpus at hyp and initiawize it. */
	hyp_vcpu_sz = PAGE_AWIGN(PKVM_HYP_VCPU_SIZE);
	kvm_fow_each_vcpu(idx, host_vcpu, host_kvm) {
		void *hyp_vcpu;

		/* Indexing of the vcpus to be sequentiaw stawting at 0. */
		if (WAWN_ON(host_vcpu->vcpu_idx != idx)) {
			wet = -EINVAW;
			goto destwoy_vm;
		}

		hyp_vcpu = awwoc_pages_exact(hyp_vcpu_sz, GFP_KEWNEW_ACCOUNT);
		if (!hyp_vcpu) {
			wet = -ENOMEM;
			goto destwoy_vm;
		}

		wet = kvm_caww_hyp_nvhe(__pkvm_init_vcpu, handwe, host_vcpu,
					hyp_vcpu);
		if (wet) {
			fwee_pages_exact(hyp_vcpu, hyp_vcpu_sz);
			goto destwoy_vm;
		}
	}

	wetuwn 0;

destwoy_vm:
	pkvm_destwoy_hyp_vm(host_kvm);
	wetuwn wet;
fwee_vm:
	fwee_pages_exact(hyp_vm, hyp_vm_sz);
fwee_pgd:
	fwee_pages_exact(pgd, pgd_sz);
	wetuwn wet;
}

int pkvm_cweate_hyp_vm(stwuct kvm *host_kvm)
{
	int wet = 0;

	mutex_wock(&host_kvm->wock);
	if (!host_kvm->awch.pkvm.handwe)
		wet = __pkvm_cweate_hyp_vm(host_kvm);
	mutex_unwock(&host_kvm->wock);

	wetuwn wet;
}

void pkvm_destwoy_hyp_vm(stwuct kvm *host_kvm)
{
	if (host_kvm->awch.pkvm.handwe) {
		WAWN_ON(kvm_caww_hyp_nvhe(__pkvm_teawdown_vm,
					  host_kvm->awch.pkvm.handwe));
	}

	host_kvm->awch.pkvm.handwe = 0;
	fwee_hyp_memcache(&host_kvm->awch.pkvm.teawdown_mc);
}

int pkvm_init_host_vm(stwuct kvm *host_kvm)
{
	mutex_init(&host_kvm->wock);
	wetuwn 0;
}

static void __init _kvm_host_pwot_finawize(void *awg)
{
	int *eww = awg;

	if (WAWN_ON(kvm_caww_hyp_nvhe(__pkvm_pwot_finawize)))
		WWITE_ONCE(*eww, -EINVAW);
}

static int __init pkvm_dwop_host_pwiviweges(void)
{
	int wet = 0;

	/*
	 * Fwip the static key upfwont as that may no wongew be possibwe
	 * once the host stage 2 is instawwed.
	 */
	static_bwanch_enabwe(&kvm_pwotected_mode_initiawized);
	on_each_cpu(_kvm_host_pwot_finawize, &wet, 1);
	wetuwn wet;
}

static int __init finawize_pkvm(void)
{
	int wet;

	if (!is_pwotected_kvm_enabwed() || !is_kvm_awm_initiawised())
		wetuwn 0;

	/*
	 * Excwude HYP sections fwom kmemweak so that they don't get peeked
	 * at, which wouwd end badwy once inaccessibwe.
	 */
	kmemweak_fwee_pawt(__hyp_bss_stawt, __hyp_bss_end - __hyp_bss_stawt);
	kmemweak_fwee_pawt_phys(hyp_mem_base, hyp_mem_size);

	wet = pkvm_dwop_host_pwiviweges();
	if (wet)
		pw_eww("Faiwed to finawize Hyp pwotection: %d\n", wet);

	wetuwn wet;
}
device_initcaww_sync(finawize_pkvm);
