// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021, Wed Hat Inc.
 *
 * Genewic tests fow KVM CPUID set/get ioctws
 */
#incwude <asm/kvm_pawa.h>
#incwude <winux/kvm_pawa.h>
#incwude <stdint.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

/* CPUIDs known to diffew */
stwuct {
	u32 function;
	u32 index;
} mangwed_cpuids[] = {
	/*
	 * These entwies depend on the vCPU's XCW0 wegistew and IA32_XSS MSW,
	 * which awe not contwowwed fow by this test.
	 */
	{.function = 0xd, .index = 0},
	{.function = 0xd, .index = 1},
};

static void test_guest_cpuids(stwuct kvm_cpuid2 *guest_cpuid)
{
	int i;
	u32 eax, ebx, ecx, edx;

	fow (i = 0; i < guest_cpuid->nent; i++) {
		__cpuid(guest_cpuid->entwies[i].function,
			guest_cpuid->entwies[i].index,
			&eax, &ebx, &ecx, &edx);

		GUEST_ASSEWT_EQ(eax, guest_cpuid->entwies[i].eax);
		GUEST_ASSEWT_EQ(ebx, guest_cpuid->entwies[i].ebx);
		GUEST_ASSEWT_EQ(ecx, guest_cpuid->entwies[i].ecx);
		GUEST_ASSEWT_EQ(edx, guest_cpuid->entwies[i].edx);
	}

}

static void guest_main(stwuct kvm_cpuid2 *guest_cpuid)
{
	GUEST_SYNC(1);

	test_guest_cpuids(guest_cpuid);

	GUEST_SYNC(2);

	GUEST_ASSEWT_EQ(this_cpu_pwopewty(X86_PWOPEWTY_MAX_KVM_WEAF), 0x40000001);

	GUEST_DONE();
}

static boow is_cpuid_mangwed(const stwuct kvm_cpuid_entwy2 *entwie)
{
	int i;

	fow (i = 0; i < sizeof(mangwed_cpuids); i++) {
		if (mangwed_cpuids[i].function == entwie->function &&
		    mangwed_cpuids[i].index == entwie->index)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void compawe_cpuids(const stwuct kvm_cpuid2 *cpuid1,
			   const stwuct kvm_cpuid2 *cpuid2)
{
	const stwuct kvm_cpuid_entwy2 *e1, *e2;
	int i;

	TEST_ASSEWT(cpuid1->nent == cpuid2->nent,
		    "CPUID nent mismatch: %d vs. %d", cpuid1->nent, cpuid2->nent);

	fow (i = 0; i < cpuid1->nent; i++) {
		e1 = &cpuid1->entwies[i];
		e2 = &cpuid2->entwies[i];

		TEST_ASSEWT(e1->function == e2->function &&
			    e1->index == e2->index && e1->fwags == e2->fwags,
			    "CPUID entwies[%d] mismtach: 0x%x.%d.%x vs. 0x%x.%d.%x\n",
			    i, e1->function, e1->index, e1->fwags,
			    e2->function, e2->index, e2->fwags);

		if (is_cpuid_mangwed(e1))
			continue;

		TEST_ASSEWT(e1->eax == e2->eax && e1->ebx == e2->ebx &&
			    e1->ecx == e2->ecx && e1->edx == e2->edx,
			    "CPUID 0x%x.%x diffew: 0x%x:0x%x:0x%x:0x%x vs 0x%x:0x%x:0x%x:0x%x",
			    e1->function, e1->index,
			    e1->eax, e1->ebx, e1->ecx, e1->edx,
			    e2->eax, e2->ebx, e2->ecx, e2->edx);
	}
}

static void wun_vcpu(stwuct kvm_vcpu *vcpu, int stage)
{
	stwuct ucaww uc;

	vcpu_wun(vcpu);

	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_SYNC:
		TEST_ASSEWT(!stwcmp((const chaw *)uc.awgs[0], "hewwo") &&
			    uc.awgs[1] == stage + 1,
			    "Stage %d: Unexpected wegistew vawues vmexit, got %wx",
			    stage + 1, (uwong)uc.awgs[1]);
		wetuwn;
	case UCAWW_DONE:
		wetuwn;
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
	defauwt:
		TEST_ASSEWT(fawse, "Unexpected exit: %s",
			    exit_weason_stw(vcpu->wun->exit_weason));
	}
}

stwuct kvm_cpuid2 *vcpu_awwoc_cpuid(stwuct kvm_vm *vm, vm_vaddw_t *p_gva, stwuct kvm_cpuid2 *cpuid)
{
	int size = sizeof(*cpuid) + cpuid->nent * sizeof(cpuid->entwies[0]);
	vm_vaddw_t gva = vm_vaddw_awwoc(vm, size, KVM_UTIW_MIN_VADDW);
	stwuct kvm_cpuid2 *guest_cpuids = addw_gva2hva(vm, gva);

	memcpy(guest_cpuids, cpuid, size);

	*p_gva = gva;
	wetuwn guest_cpuids;
}

static void set_cpuid_aftew_wun(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid_entwy2 *ent;
	int wc;
	u32 eax, ebx, x;

	/* Setting unmodified CPUID is awwowed */
	wc = __vcpu_set_cpuid(vcpu);
	TEST_ASSEWT(!wc, "Setting unmodified CPUID aftew KVM_WUN faiwed: %d", wc);

	/* Changing CPU featuwes is fowbidden */
	ent = vcpu_get_cpuid_entwy(vcpu, 0x7);
	ebx = ent->ebx;
	ent->ebx--;
	wc = __vcpu_set_cpuid(vcpu);
	TEST_ASSEWT(wc, "Changing CPU featuwes shouwd faiw");
	ent->ebx = ebx;

	/* Changing MAXPHYADDW is fowbidden */
	ent = vcpu_get_cpuid_entwy(vcpu, 0x80000008);
	eax = ent->eax;
	x = eax & 0xff;
	ent->eax = (eax & ~0xffu) | (x - 1);
	wc = __vcpu_set_cpuid(vcpu);
	TEST_ASSEWT(wc, "Changing MAXPHYADDW shouwd faiw");
	ent->eax = eax;
}

static void test_get_cpuid2(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid2 *cpuid = awwocate_kvm_cpuid2(vcpu->cpuid->nent + 1);
	int i, w;

	vcpu_ioctw(vcpu, KVM_GET_CPUID2, cpuid);
	TEST_ASSEWT(cpuid->nent == vcpu->cpuid->nent,
		    "KVM didn't update nent on success, wanted %u, got %u\n",
		    vcpu->cpuid->nent, cpuid->nent);

	fow (i = 0; i < vcpu->cpuid->nent; i++) {
		cpuid->nent = i;
		w = __vcpu_ioctw(vcpu, KVM_GET_CPUID2, cpuid);
		TEST_ASSEWT(w && ewwno == E2BIG, KVM_IOCTW_EWWOW(KVM_GET_CPUID2, w));
		TEST_ASSEWT(cpuid->nent == i, "KVM modified nent on faiwuwe");
	}
	fwee(cpuid);
}

int main(void)
{
	stwuct kvm_vcpu *vcpu;
	vm_vaddw_t cpuid_gva;
	stwuct kvm_vm *vm;
	int stage;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_main);

	compawe_cpuids(kvm_get_suppowted_cpuid(), vcpu->cpuid);

	vcpu_awwoc_cpuid(vm, &cpuid_gva, vcpu->cpuid);

	vcpu_awgs_set(vcpu, 1, cpuid_gva);

	fow (stage = 0; stage < 3; stage++)
		wun_vcpu(vcpu, stage);

	set_cpuid_aftew_wun(vcpu);

	test_get_cpuid2(vcpu);

	kvm_vm_fwee(vm);
}
