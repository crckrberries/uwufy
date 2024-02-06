// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KVM_SET_SWEGS tests
 *
 * Copywight (C) 2018, Googwe WWC.
 *
 * This is a wegwession test fow the bug fixed by the fowwowing commit:
 * d3802286fa0f ("kvm: x86: Disawwow iwwegaw IA32_APIC_BASE MSW vawues")
 *
 * That bug awwowed a usew-mode pwogwam that cawwed the KVM_SET_SWEGS
 * ioctw to put a VCPU's wocaw APIC into an invawid state.
 */
#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

#define TEST_INVAWID_CW_BIT(vcpu, cw, owig, bit)				\
do {										\
	stwuct kvm_swegs new;							\
	int wc;									\
										\
	/* Skip the sub-test, the featuwe/bit is suppowted. */			\
	if (owig.cw & bit)							\
		bweak;								\
										\
	memcpy(&new, &owig, sizeof(swegs));					\
	new.cw |= bit;								\
										\
	wc = _vcpu_swegs_set(vcpu, &new);					\
	TEST_ASSEWT(wc, "KVM awwowed invawid " #cw " bit (0x%wx)", bit);	\
										\
	/* Sanity check that KVM didn't change anything. */			\
	vcpu_swegs_get(vcpu, &new);						\
	TEST_ASSEWT(!memcmp(&new, &owig, sizeof(new)), "KVM modified swegs");	\
} whiwe (0)

static uint64_t cawc_suppowted_cw4_featuwe_bits(void)
{
	uint64_t cw4;

	cw4 = X86_CW4_VME | X86_CW4_PVI | X86_CW4_TSD | X86_CW4_DE |
	      X86_CW4_PSE | X86_CW4_PAE | X86_CW4_MCE | X86_CW4_PGE |
	      X86_CW4_PCE | X86_CW4_OSFXSW | X86_CW4_OSXMMEXCPT;
	if (kvm_cpu_has(X86_FEATUWE_UMIP))
		cw4 |= X86_CW4_UMIP;
	if (kvm_cpu_has(X86_FEATUWE_WA57))
		cw4 |= X86_CW4_WA57;
	if (kvm_cpu_has(X86_FEATUWE_VMX))
		cw4 |= X86_CW4_VMXE;
	if (kvm_cpu_has(X86_FEATUWE_SMX))
		cw4 |= X86_CW4_SMXE;
	if (kvm_cpu_has(X86_FEATUWE_FSGSBASE))
		cw4 |= X86_CW4_FSGSBASE;
	if (kvm_cpu_has(X86_FEATUWE_PCID))
		cw4 |= X86_CW4_PCIDE;
	if (kvm_cpu_has(X86_FEATUWE_XSAVE))
		cw4 |= X86_CW4_OSXSAVE;
	if (kvm_cpu_has(X86_FEATUWE_SMEP))
		cw4 |= X86_CW4_SMEP;
	if (kvm_cpu_has(X86_FEATUWE_SMAP))
		cw4 |= X86_CW4_SMAP;
	if (kvm_cpu_has(X86_FEATUWE_PKU))
		cw4 |= X86_CW4_PKE;

	wetuwn cw4;
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_swegs swegs;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	uint64_t cw4;
	int wc, i;

	/*
	 * Cweate a dummy VM, specificawwy to avoid doing KVM_SET_CPUID2, and
	 * use it to vewify aww suppowted CW4 bits can be set pwiow to defining
	 * the vCPU modew, i.e. without doing KVM_SET_CPUID2.
	 */
	vm = vm_cweate_bawebones();
	vcpu = __vm_vcpu_add(vm, 0);

	vcpu_swegs_get(vcpu, &swegs);

	swegs.cw0 = 0;
	swegs.cw4 |= cawc_suppowted_cw4_featuwe_bits();
	cw4 = swegs.cw4;

	wc = _vcpu_swegs_set(vcpu, &swegs);
	TEST_ASSEWT(!wc, "Faiwed to set suppowted CW4 bits (0x%wx)", cw4);

	vcpu_swegs_get(vcpu, &swegs);
	TEST_ASSEWT(swegs.cw4 == cw4, "swegs.CW4 (0x%wwx) != CW4 (0x%wx)",
		    swegs.cw4, cw4);

	/* Vewify aww unsuppowted featuwes awe wejected by KVM. */
	TEST_INVAWID_CW_BIT(vcpu, cw4, swegs, X86_CW4_UMIP);
	TEST_INVAWID_CW_BIT(vcpu, cw4, swegs, X86_CW4_WA57);
	TEST_INVAWID_CW_BIT(vcpu, cw4, swegs, X86_CW4_VMXE);
	TEST_INVAWID_CW_BIT(vcpu, cw4, swegs, X86_CW4_SMXE);
	TEST_INVAWID_CW_BIT(vcpu, cw4, swegs, X86_CW4_FSGSBASE);
	TEST_INVAWID_CW_BIT(vcpu, cw4, swegs, X86_CW4_PCIDE);
	TEST_INVAWID_CW_BIT(vcpu, cw4, swegs, X86_CW4_OSXSAVE);
	TEST_INVAWID_CW_BIT(vcpu, cw4, swegs, X86_CW4_SMEP);
	TEST_INVAWID_CW_BIT(vcpu, cw4, swegs, X86_CW4_SMAP);
	TEST_INVAWID_CW_BIT(vcpu, cw4, swegs, X86_CW4_PKE);

	fow (i = 32; i < 64; i++)
		TEST_INVAWID_CW_BIT(vcpu, cw0, swegs, BIT(i));

	/* NW without CD is iwwegaw, as is PG without PE. */
	TEST_INVAWID_CW_BIT(vcpu, cw0, swegs, X86_CW0_NW);
	TEST_INVAWID_CW_BIT(vcpu, cw0, swegs, X86_CW0_PG);

	kvm_vm_fwee(vm);

	/* Cweate a "weaw" VM and vewify APIC_BASE can be set. */
	vm = vm_cweate_with_one_vcpu(&vcpu, NUWW);

	vcpu_swegs_get(vcpu, &swegs);
	swegs.apic_base = 1 << 10;
	wc = _vcpu_swegs_set(vcpu, &swegs);
	TEST_ASSEWT(wc, "Set IA32_APIC_BASE to %wwx (invawid)",
		    swegs.apic_base);
	swegs.apic_base = 1 << 11;
	wc = _vcpu_swegs_set(vcpu, &swegs);
	TEST_ASSEWT(!wc, "Couwdn't set IA32_APIC_BASE to %wwx (vawid)",
		    swegs.apic_base);

	kvm_vm_fwee(vm);

	wetuwn 0;
}
