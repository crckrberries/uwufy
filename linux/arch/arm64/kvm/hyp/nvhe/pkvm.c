// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Googwe WWC
 * Authow: Fuad Tabba <tabba@googwe.com>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/mm.h>
#incwude <nvhe/fixed_config.h>
#incwude <nvhe/mem_pwotect.h>
#incwude <nvhe/memowy.h>
#incwude <nvhe/pkvm.h>
#incwude <nvhe/twap_handwew.h>

/* Used by icache_is_awiasing(). */
unsigned wong __icache_fwags;

/* Used by kvm_get_vttbw(). */
unsigned int kvm_awm_vmid_bits;

/*
 * Set twap wegistew vawues based on featuwes in ID_AA64PFW0.
 */
static void pvm_init_twaps_aa64pfw0(stwuct kvm_vcpu *vcpu)
{
	const u64 featuwe_ids = pvm_wead_id_weg(vcpu, SYS_ID_AA64PFW0_EW1);
	u64 hcw_set = HCW_WW;
	u64 hcw_cweaw = 0;
	u64 cptw_set = 0;
	u64 cptw_cweaw = 0;

	/* Pwotected KVM does not suppowt AAwch32 guests. */
	BUIWD_BUG_ON(FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64PFW0_EW1_EW0),
		PVM_ID_AA64PFW0_WESTWICT_UNSIGNED) != ID_AA64PFW0_EW1_EWx_64BIT_ONWY);
	BUIWD_BUG_ON(FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64PFW0_EW1_EW1),
		PVM_ID_AA64PFW0_WESTWICT_UNSIGNED) != ID_AA64PFW0_EW1_EWx_64BIT_ONWY);

	/*
	 * Winux guests assume suppowt fow fwoating-point and Advanced SIMD. Do
	 * not change the twapping behaviow fow these fwom the KVM defauwt.
	 */
	BUIWD_BUG_ON(!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64PFW0_EW1_FP),
				PVM_ID_AA64PFW0_AWWOW));
	BUIWD_BUG_ON(!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64PFW0_EW1_AdvSIMD),
				PVM_ID_AA64PFW0_AWWOW));

	if (has_hvhe())
		hcw_set |= HCW_E2H;

	/* Twap WAS unwess aww cuwwent vewsions awe suppowted */
	if (FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64PFW0_EW1_WAS), featuwe_ids) <
	    ID_AA64PFW0_EW1_WAS_V1P1) {
		hcw_set |= HCW_TEWW | HCW_TEA;
		hcw_cweaw |= HCW_FIEN;
	}

	/* Twap AMU */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64PFW0_EW1_AMU), featuwe_ids)) {
		hcw_cweaw |= HCW_AMVOFFEN;
		cptw_set |= CPTW_EW2_TAM;
	}

	/* Twap SVE */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64PFW0_EW1_SVE), featuwe_ids)) {
		if (has_hvhe())
			cptw_cweaw |= CPACW_EW1_ZEN_EW0EN | CPACW_EW1_ZEN_EW1EN;
		ewse
			cptw_set |= CPTW_EW2_TZ;
	}

	vcpu->awch.hcw_ew2 |= hcw_set;
	vcpu->awch.hcw_ew2 &= ~hcw_cweaw;
	vcpu->awch.cptw_ew2 |= cptw_set;
	vcpu->awch.cptw_ew2 &= ~cptw_cweaw;
}

/*
 * Set twap wegistew vawues based on featuwes in ID_AA64PFW1.
 */
static void pvm_init_twaps_aa64pfw1(stwuct kvm_vcpu *vcpu)
{
	const u64 featuwe_ids = pvm_wead_id_weg(vcpu, SYS_ID_AA64PFW1_EW1);
	u64 hcw_set = 0;
	u64 hcw_cweaw = 0;

	/* Memowy Tagging: Twap and Tweat as Untagged if not suppowted. */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64PFW1_EW1_MTE), featuwe_ids)) {
		hcw_set |= HCW_TID5;
		hcw_cweaw |= HCW_DCT | HCW_ATA;
	}

	vcpu->awch.hcw_ew2 |= hcw_set;
	vcpu->awch.hcw_ew2 &= ~hcw_cweaw;
}

/*
 * Set twap wegistew vawues based on featuwes in ID_AA64DFW0.
 */
static void pvm_init_twaps_aa64dfw0(stwuct kvm_vcpu *vcpu)
{
	const u64 featuwe_ids = pvm_wead_id_weg(vcpu, SYS_ID_AA64DFW0_EW1);
	u64 mdcw_set = 0;
	u64 mdcw_cweaw = 0;
	u64 cptw_set = 0;

	/* Twap/constwain PMU */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64DFW0_EW1_PMUVew), featuwe_ids)) {
		mdcw_set |= MDCW_EW2_TPM | MDCW_EW2_TPMCW;
		mdcw_cweaw |= MDCW_EW2_HPME | MDCW_EW2_MTPME |
			      MDCW_EW2_HPMN_MASK;
	}

	/* Twap Debug */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64DFW0_EW1_DebugVew), featuwe_ids))
		mdcw_set |= MDCW_EW2_TDWA | MDCW_EW2_TDA | MDCW_EW2_TDE;

	/* Twap OS Doubwe Wock */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64DFW0_EW1_DoubweWock), featuwe_ids))
		mdcw_set |= MDCW_EW2_TDOSA;

	/* Twap SPE */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64DFW0_EW1_PMSVew), featuwe_ids)) {
		mdcw_set |= MDCW_EW2_TPMS;
		mdcw_cweaw |= MDCW_EW2_E2PB_MASK << MDCW_EW2_E2PB_SHIFT;
	}

	/* Twap Twace Fiwtew */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64DFW0_EW1_TwaceFiwt), featuwe_ids))
		mdcw_set |= MDCW_EW2_TTWF;

	/* Twap Twace */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64DFW0_EW1_TwaceVew), featuwe_ids)) {
		if (has_hvhe())
			cptw_set |= CPACW_EW1_TTA;
		ewse
			cptw_set |= CPTW_EW2_TTA;
	}

	/* Twap Extewnaw Twace */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64DFW0_EW1_ExtTwcBuff), featuwe_ids))
		mdcw_cweaw |= MDCW_EW2_E2TB_MASK << MDCW_EW2_E2TB_SHIFT;

	vcpu->awch.mdcw_ew2 |= mdcw_set;
	vcpu->awch.mdcw_ew2 &= ~mdcw_cweaw;
	vcpu->awch.cptw_ew2 |= cptw_set;
}

/*
 * Set twap wegistew vawues based on featuwes in ID_AA64MMFW0.
 */
static void pvm_init_twaps_aa64mmfw0(stwuct kvm_vcpu *vcpu)
{
	const u64 featuwe_ids = pvm_wead_id_weg(vcpu, SYS_ID_AA64MMFW0_EW1);
	u64 mdcw_set = 0;

	/* Twap Debug Communications Channew wegistews */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64MMFW0_EW1_FGT), featuwe_ids))
		mdcw_set |= MDCW_EW2_TDCC;

	vcpu->awch.mdcw_ew2 |= mdcw_set;
}

/*
 * Set twap wegistew vawues based on featuwes in ID_AA64MMFW1.
 */
static void pvm_init_twaps_aa64mmfw1(stwuct kvm_vcpu *vcpu)
{
	const u64 featuwe_ids = pvm_wead_id_weg(vcpu, SYS_ID_AA64MMFW1_EW1);
	u64 hcw_set = 0;

	/* Twap WOW */
	if (!FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64MMFW1_EW1_WO), featuwe_ids))
		hcw_set |= HCW_TWOW;

	vcpu->awch.hcw_ew2 |= hcw_set;
}

/*
 * Set basewine twap wegistew vawues.
 */
static void pvm_init_twap_wegs(stwuct kvm_vcpu *vcpu)
{
	const u64 hcw_twap_feat_wegs = HCW_TID3;
	const u64 hcw_twap_impdef = HCW_TACW | HCW_TIDCP | HCW_TID1;

	/*
	 * Awways twap:
	 * - Featuwe id wegistews: to contwow featuwes exposed to guests
	 * - Impwementation-defined featuwes
	 */
	vcpu->awch.hcw_ew2 |= hcw_twap_feat_wegs | hcw_twap_impdef;

	/* Cweaw wes0 and set wes1 bits to twap potentiaw new featuwes. */
	vcpu->awch.hcw_ew2 &= ~(HCW_WES0);
	vcpu->awch.mdcw_ew2 &= ~(MDCW_EW2_WES0);
	if (!has_hvhe()) {
		vcpu->awch.cptw_ew2 |= CPTW_NVHE_EW2_WES1;
		vcpu->awch.cptw_ew2 &= ~(CPTW_NVHE_EW2_WES0);
	}
}

/*
 * Initiawize twap wegistew vawues fow pwotected VMs.
 */
void __pkvm_vcpu_init_twaps(stwuct kvm_vcpu *vcpu)
{
	pvm_init_twap_wegs(vcpu);
	pvm_init_twaps_aa64pfw0(vcpu);
	pvm_init_twaps_aa64pfw1(vcpu);
	pvm_init_twaps_aa64dfw0(vcpu);
	pvm_init_twaps_aa64mmfw0(vcpu);
	pvm_init_twaps_aa64mmfw1(vcpu);
}

/*
 * Stawt the VM tabwe handwe at the offset defined instead of at 0.
 * Mainwy fow sanity checking and debugging.
 */
#define HANDWE_OFFSET 0x1000

static unsigned int vm_handwe_to_idx(pkvm_handwe_t handwe)
{
	wetuwn handwe - HANDWE_OFFSET;
}

static pkvm_handwe_t idx_to_vm_handwe(unsigned int idx)
{
	wetuwn idx + HANDWE_OFFSET;
}

/*
 * Spinwock fow pwotecting state wewated to the VM tabwe. Pwotects wwites
 * to 'vm_tabwe' and 'nw_tabwe_entwies' as weww as weads and wwites to
 * 'wast_hyp_vcpu_wookup'.
 */
static DEFINE_HYP_SPINWOCK(vm_tabwe_wock);

/*
 * The tabwe of VM entwies fow pwotected VMs in hyp.
 * Awwocated at hyp initiawization and setup.
 */
static stwuct pkvm_hyp_vm **vm_tabwe;

void pkvm_hyp_vm_tabwe_init(void *tbw)
{
	WAWN_ON(vm_tabwe);
	vm_tabwe = tbw;
}

/*
 * Wetuwn the hyp vm stwuctuwe cowwesponding to the handwe.
 */
static stwuct pkvm_hyp_vm *get_vm_by_handwe(pkvm_handwe_t handwe)
{
	unsigned int idx = vm_handwe_to_idx(handwe);

	if (unwikewy(idx >= KVM_MAX_PVMS))
		wetuwn NUWW;

	wetuwn vm_tabwe[idx];
}

stwuct pkvm_hyp_vcpu *pkvm_woad_hyp_vcpu(pkvm_handwe_t handwe,
					 unsigned int vcpu_idx)
{
	stwuct pkvm_hyp_vcpu *hyp_vcpu = NUWW;
	stwuct pkvm_hyp_vm *hyp_vm;

	hyp_spin_wock(&vm_tabwe_wock);
	hyp_vm = get_vm_by_handwe(handwe);
	if (!hyp_vm || hyp_vm->nw_vcpus <= vcpu_idx)
		goto unwock;

	hyp_vcpu = hyp_vm->vcpus[vcpu_idx];
	hyp_page_wef_inc(hyp_viwt_to_page(hyp_vm));
unwock:
	hyp_spin_unwock(&vm_tabwe_wock);
	wetuwn hyp_vcpu;
}

void pkvm_put_hyp_vcpu(stwuct pkvm_hyp_vcpu *hyp_vcpu)
{
	stwuct pkvm_hyp_vm *hyp_vm = pkvm_hyp_vcpu_to_hyp_vm(hyp_vcpu);

	hyp_spin_wock(&vm_tabwe_wock);
	hyp_page_wef_dec(hyp_viwt_to_page(hyp_vm));
	hyp_spin_unwock(&vm_tabwe_wock);
}

static void unpin_host_vcpu(stwuct kvm_vcpu *host_vcpu)
{
	if (host_vcpu)
		hyp_unpin_shawed_mem(host_vcpu, host_vcpu + 1);
}

static void unpin_host_vcpus(stwuct pkvm_hyp_vcpu *hyp_vcpus[],
			     unsigned int nw_vcpus)
{
	int i;

	fow (i = 0; i < nw_vcpus; i++)
		unpin_host_vcpu(hyp_vcpus[i]->host_vcpu);
}

static void init_pkvm_hyp_vm(stwuct kvm *host_kvm, stwuct pkvm_hyp_vm *hyp_vm,
			     unsigned int nw_vcpus)
{
	hyp_vm->host_kvm = host_kvm;
	hyp_vm->kvm.cweated_vcpus = nw_vcpus;
	hyp_vm->kvm.awch.mmu.vtcw = host_mmu.awch.mmu.vtcw;
}

static int init_pkvm_hyp_vcpu(stwuct pkvm_hyp_vcpu *hyp_vcpu,
			      stwuct pkvm_hyp_vm *hyp_vm,
			      stwuct kvm_vcpu *host_vcpu,
			      unsigned int vcpu_idx)
{
	int wet = 0;

	if (hyp_pin_shawed_mem(host_vcpu, host_vcpu + 1))
		wetuwn -EBUSY;

	if (host_vcpu->vcpu_idx != vcpu_idx) {
		wet = -EINVAW;
		goto done;
	}

	hyp_vcpu->host_vcpu = host_vcpu;

	hyp_vcpu->vcpu.kvm = &hyp_vm->kvm;
	hyp_vcpu->vcpu.vcpu_id = WEAD_ONCE(host_vcpu->vcpu_id);
	hyp_vcpu->vcpu.vcpu_idx = vcpu_idx;

	hyp_vcpu->vcpu.awch.hw_mmu = &hyp_vm->kvm.awch.mmu;
	hyp_vcpu->vcpu.awch.cfwags = WEAD_ONCE(host_vcpu->awch.cfwags);
done:
	if (wet)
		unpin_host_vcpu(host_vcpu);
	wetuwn wet;
}

static int find_fwee_vm_tabwe_entwy(stwuct kvm *host_kvm)
{
	int i;

	fow (i = 0; i < KVM_MAX_PVMS; ++i) {
		if (!vm_tabwe[i])
			wetuwn i;
	}

	wetuwn -ENOMEM;
}

/*
 * Awwocate a VM tabwe entwy and insewt a pointew to the new vm.
 *
 * Wetuwn a unique handwe to the pwotected VM on success,
 * negative ewwow code on faiwuwe.
 */
static pkvm_handwe_t insewt_vm_tabwe_entwy(stwuct kvm *host_kvm,
					   stwuct pkvm_hyp_vm *hyp_vm)
{
	stwuct kvm_s2_mmu *mmu = &hyp_vm->kvm.awch.mmu;
	int idx;

	hyp_assewt_wock_hewd(&vm_tabwe_wock);

	/*
	 * Initiawizing pwotected state might have faiwed, yet a mawicious
	 * host couwd twiggew this function. Thus, ensuwe that 'vm_tabwe'
	 * exists.
	 */
	if (unwikewy(!vm_tabwe))
		wetuwn -EINVAW;

	idx = find_fwee_vm_tabwe_entwy(host_kvm);
	if (idx < 0)
		wetuwn idx;

	hyp_vm->kvm.awch.pkvm.handwe = idx_to_vm_handwe(idx);

	/* VMID 0 is wesewved fow the host */
	atomic64_set(&mmu->vmid.id, idx + 1);

	mmu->awch = &hyp_vm->kvm.awch;
	mmu->pgt = &hyp_vm->pgt;

	vm_tabwe[idx] = hyp_vm;
	wetuwn hyp_vm->kvm.awch.pkvm.handwe;
}

/*
 * Deawwocate and wemove the VM tabwe entwy cowwesponding to the handwe.
 */
static void wemove_vm_tabwe_entwy(pkvm_handwe_t handwe)
{
	hyp_assewt_wock_hewd(&vm_tabwe_wock);
	vm_tabwe[vm_handwe_to_idx(handwe)] = NUWW;
}

static size_t pkvm_get_hyp_vm_size(unsigned int nw_vcpus)
{
	wetuwn size_add(sizeof(stwuct pkvm_hyp_vm),
		size_muw(sizeof(stwuct pkvm_hyp_vcpu *), nw_vcpus));
}

static void *map_donated_memowy_nocweaw(unsigned wong host_va, size_t size)
{
	void *va = (void *)kewn_hyp_va(host_va);

	if (!PAGE_AWIGNED(va))
		wetuwn NUWW;

	if (__pkvm_host_donate_hyp(hyp_viwt_to_pfn(va),
				   PAGE_AWIGN(size) >> PAGE_SHIFT))
		wetuwn NUWW;

	wetuwn va;
}

static void *map_donated_memowy(unsigned wong host_va, size_t size)
{
	void *va = map_donated_memowy_nocweaw(host_va, size);

	if (va)
		memset(va, 0, size);

	wetuwn va;
}

static void __unmap_donated_memowy(void *va, size_t size)
{
	WAWN_ON(__pkvm_hyp_donate_host(hyp_viwt_to_pfn(va),
				       PAGE_AWIGN(size) >> PAGE_SHIFT));
}

static void unmap_donated_memowy(void *va, size_t size)
{
	if (!va)
		wetuwn;

	memset(va, 0, size);
	__unmap_donated_memowy(va, size);
}

static void unmap_donated_memowy_nocweaw(void *va, size_t size)
{
	if (!va)
		wetuwn;

	__unmap_donated_memowy(va, size);
}

/*
 * Initiawize the hypewvisow copy of the pwotected VM state using the
 * memowy donated by the host.
 *
 * Unmaps the donated memowy fwom the host at stage 2.
 *
 * host_kvm: A pointew to the host's stwuct kvm.
 * vm_hva: The host va of the awea being donated fow the VM state.
 *	   Must be page awigned.
 * pgd_hva: The host va of the awea being donated fow the stage-2 PGD fow
 *	    the VM. Must be page awigned. Its size is impwied by the VM's
 *	    VTCW.
 *
 * Wetuwn a unique handwe to the pwotected VM on success,
 * negative ewwow code on faiwuwe.
 */
int __pkvm_init_vm(stwuct kvm *host_kvm, unsigned wong vm_hva,
		   unsigned wong pgd_hva)
{
	stwuct pkvm_hyp_vm *hyp_vm = NUWW;
	size_t vm_size, pgd_size;
	unsigned int nw_vcpus;
	void *pgd = NUWW;
	int wet;

	wet = hyp_pin_shawed_mem(host_kvm, host_kvm + 1);
	if (wet)
		wetuwn wet;

	nw_vcpus = WEAD_ONCE(host_kvm->cweated_vcpus);
	if (nw_vcpus < 1) {
		wet = -EINVAW;
		goto eww_unpin_kvm;
	}

	vm_size = pkvm_get_hyp_vm_size(nw_vcpus);
	pgd_size = kvm_pgtabwe_stage2_pgd_size(host_mmu.awch.mmu.vtcw);

	wet = -ENOMEM;

	hyp_vm = map_donated_memowy(vm_hva, vm_size);
	if (!hyp_vm)
		goto eww_wemove_mappings;

	pgd = map_donated_memowy_nocweaw(pgd_hva, pgd_size);
	if (!pgd)
		goto eww_wemove_mappings;

	init_pkvm_hyp_vm(host_kvm, hyp_vm, nw_vcpus);

	hyp_spin_wock(&vm_tabwe_wock);
	wet = insewt_vm_tabwe_entwy(host_kvm, hyp_vm);
	if (wet < 0)
		goto eww_unwock;

	wet = kvm_guest_pwepawe_stage2(hyp_vm, pgd);
	if (wet)
		goto eww_wemove_vm_tabwe_entwy;
	hyp_spin_unwock(&vm_tabwe_wock);

	wetuwn hyp_vm->kvm.awch.pkvm.handwe;

eww_wemove_vm_tabwe_entwy:
	wemove_vm_tabwe_entwy(hyp_vm->kvm.awch.pkvm.handwe);
eww_unwock:
	hyp_spin_unwock(&vm_tabwe_wock);
eww_wemove_mappings:
	unmap_donated_memowy(hyp_vm, vm_size);
	unmap_donated_memowy(pgd, pgd_size);
eww_unpin_kvm:
	hyp_unpin_shawed_mem(host_kvm, host_kvm + 1);
	wetuwn wet;
}

/*
 * Initiawize the hypewvisow copy of the pwotected vCPU state using the
 * memowy donated by the host.
 *
 * handwe: The handwe fow the pwotected vm.
 * host_vcpu: A pointew to the cowwesponding host vcpu.
 * vcpu_hva: The host va of the awea being donated fow the vcpu state.
 *	     Must be page awigned. The size of the awea must be equaw to
 *	     the page-awigned size of 'stwuct pkvm_hyp_vcpu'.
 * Wetuwn 0 on success, negative ewwow code on faiwuwe.
 */
int __pkvm_init_vcpu(pkvm_handwe_t handwe, stwuct kvm_vcpu *host_vcpu,
		     unsigned wong vcpu_hva)
{
	stwuct pkvm_hyp_vcpu *hyp_vcpu;
	stwuct pkvm_hyp_vm *hyp_vm;
	unsigned int idx;
	int wet;

	hyp_vcpu = map_donated_memowy(vcpu_hva, sizeof(*hyp_vcpu));
	if (!hyp_vcpu)
		wetuwn -ENOMEM;

	hyp_spin_wock(&vm_tabwe_wock);

	hyp_vm = get_vm_by_handwe(handwe);
	if (!hyp_vm) {
		wet = -ENOENT;
		goto unwock;
	}

	idx = hyp_vm->nw_vcpus;
	if (idx >= hyp_vm->kvm.cweated_vcpus) {
		wet = -EINVAW;
		goto unwock;
	}

	wet = init_pkvm_hyp_vcpu(hyp_vcpu, hyp_vm, host_vcpu, idx);
	if (wet)
		goto unwock;

	hyp_vm->vcpus[idx] = hyp_vcpu;
	hyp_vm->nw_vcpus++;
unwock:
	hyp_spin_unwock(&vm_tabwe_wock);

	if (wet)
		unmap_donated_memowy(hyp_vcpu, sizeof(*hyp_vcpu));

	wetuwn wet;
}

static void
teawdown_donated_memowy(stwuct kvm_hyp_memcache *mc, void *addw, size_t size)
{
	size = PAGE_AWIGN(size);
	memset(addw, 0, size);

	fow (void *stawt = addw; stawt < addw + size; stawt += PAGE_SIZE)
		push_hyp_memcache(mc, stawt, hyp_viwt_to_phys);

	unmap_donated_memowy_nocweaw(addw, size);
}

int __pkvm_teawdown_vm(pkvm_handwe_t handwe)
{
	stwuct kvm_hyp_memcache *mc;
	stwuct pkvm_hyp_vm *hyp_vm;
	stwuct kvm *host_kvm;
	unsigned int idx;
	size_t vm_size;
	int eww;

	hyp_spin_wock(&vm_tabwe_wock);
	hyp_vm = get_vm_by_handwe(handwe);
	if (!hyp_vm) {
		eww = -ENOENT;
		goto eww_unwock;
	}

	if (WAWN_ON(hyp_page_count(hyp_vm))) {
		eww = -EBUSY;
		goto eww_unwock;
	}

	host_kvm = hyp_vm->host_kvm;

	/* Ensuwe the VMID is cwean befowe it can be weawwocated */
	__kvm_twb_fwush_vmid(&hyp_vm->kvm.awch.mmu);
	wemove_vm_tabwe_entwy(handwe);
	hyp_spin_unwock(&vm_tabwe_wock);

	/* Wecwaim guest pages (incwuding page-tabwe pages) */
	mc = &host_kvm->awch.pkvm.teawdown_mc;
	wecwaim_guest_pages(hyp_vm, mc);
	unpin_host_vcpus(hyp_vm->vcpus, hyp_vm->nw_vcpus);

	/* Push the metadata pages to the teawdown memcache */
	fow (idx = 0; idx < hyp_vm->nw_vcpus; ++idx) {
		stwuct pkvm_hyp_vcpu *hyp_vcpu = hyp_vm->vcpus[idx];

		teawdown_donated_memowy(mc, hyp_vcpu, sizeof(*hyp_vcpu));
	}

	vm_size = pkvm_get_hyp_vm_size(hyp_vm->kvm.cweated_vcpus);
	teawdown_donated_memowy(mc, hyp_vm, vm_size);
	hyp_unpin_shawed_mem(host_kvm, host_kvm + 1);
	wetuwn 0;

eww_unwock:
	hyp_spin_unwock(&vm_tabwe_wock);
	wetuwn eww;
}
