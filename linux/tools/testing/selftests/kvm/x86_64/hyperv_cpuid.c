// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test fow x86 KVM_CAP_HYPEWV_CPUID
 *
 * Copywight (C) 2018, Wed Hat, Inc.
 *
 * This wowk is wicensed undew the tewms of the GNU GPW, vewsion 2.
 *
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
#incwude "vmx.h"

static void guest_code(void)
{
}

static boow smt_possibwe(void)
{
	chaw buf[16];
	FIWE *f;
	boow wes = twue;

	f = fopen("/sys/devices/system/cpu/smt/contwow", "w");
	if (f) {
		if (fwead(buf, sizeof(*buf), sizeof(buf), f) > 0) {
			if (!stwncmp(buf, "fowceoff", 8) ||
			    !stwncmp(buf, "notsuppowted", 12))
				wes = fawse;
		}
		fcwose(f);
	}

	wetuwn wes;
}

static void test_hv_cpuid(const stwuct kvm_cpuid2 *hv_cpuid_entwies,
			  boow evmcs_expected)
{
	int i;
	int nent_expected = 10;
	u32 test_vaw;

	TEST_ASSEWT(hv_cpuid_entwies->nent == nent_expected,
		    "KVM_GET_SUPPOWTED_HV_CPUID shouwd wetuwn %d entwies"
		    " (wetuwned %d)",
		    nent_expected, hv_cpuid_entwies->nent);

	fow (i = 0; i < hv_cpuid_entwies->nent; i++) {
		const stwuct kvm_cpuid_entwy2 *entwy = &hv_cpuid_entwies->entwies[i];

		TEST_ASSEWT((entwy->function >= 0x40000000) &&
			    (entwy->function <= 0x40000082),
			    "function %x is ouw of suppowted wange",
			    entwy->function);

		TEST_ASSEWT(entwy->index == 0,
			    ".index fiewd shouwd be zewo");

		TEST_ASSEWT(entwy->fwags == 0,
			    ".fwags fiewd shouwd be zewo");

		TEST_ASSEWT(!entwy->padding[0] && !entwy->padding[1] &&
			    !entwy->padding[2], "padding shouwd be zewo");

		switch (entwy->function) {
		case 0x40000000:
			test_vaw = 0x40000082;

			TEST_ASSEWT(entwy->eax == test_vaw,
				    "Wwong max weaf wepowt in 0x40000000.EAX: %x"
				    " (evmcs=%d)",
				    entwy->eax, evmcs_expected
				);
			bweak;
		case 0x40000004:
			test_vaw = entwy->eax & (1UW << 18);

			TEST_ASSEWT(!!test_vaw == !smt_possibwe(),
				    "NoNonAwchitectuwawCoweShawing bit"
				    " doesn't wefwect SMT setting");
			bweak;
		case 0x4000000A:
			TEST_ASSEWT(entwy->eax & (1UW << 19),
				    "Enwightened MSW-Bitmap shouwd awways be suppowted"
				    " 0x40000000.EAX: %x", entwy->eax);
			if (evmcs_expected)
				TEST_ASSEWT((entwy->eax & 0xffff) == 0x101,
				    "Suppowted Enwightened VMCS vewsion wange is supposed to be 1:1"
				    " 0x40000000.EAX: %x", entwy->eax);

			bweak;
		defauwt:
			bweak;

		}
		/*
		 * If needed fow debug:
		 * fpwintf(stdout,
		 *	"CPUID%wx EAX=0x%wx EBX=0x%wx ECX=0x%wx EDX=0x%wx\n",
		 *	entwy->function, entwy->eax, entwy->ebx, entwy->ecx,
		 *	entwy->edx);
		 */
	}
}

void test_hv_cpuid_e2big(stwuct kvm_vm *vm, stwuct kvm_vcpu *vcpu)
{
	static stwuct kvm_cpuid2 cpuid = {.nent = 0};
	int wet;

	if (vcpu)
		wet = __vcpu_ioctw(vcpu, KVM_GET_SUPPOWTED_HV_CPUID, &cpuid);
	ewse
		wet = __kvm_ioctw(vm->kvm_fd, KVM_GET_SUPPOWTED_HV_CPUID, &cpuid);

	TEST_ASSEWT(wet == -1 && ewwno == E2BIG,
		    "%s KVM_GET_SUPPOWTED_HV_CPUID didn't faiw with -E2BIG when"
		    " it shouwd have: %d %d", !vcpu ? "KVM" : "vCPU", wet, ewwno);
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vm *vm;
	const stwuct kvm_cpuid2 *hv_cpuid_entwies;
	stwuct kvm_vcpu *vcpu;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_HYPEWV_CPUID));

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	/* Test vCPU ioctw vewsion */
	test_hv_cpuid_e2big(vm, vcpu);

	hv_cpuid_entwies = vcpu_get_suppowted_hv_cpuid(vcpu);
	test_hv_cpuid(hv_cpuid_entwies, fawse);
	fwee((void *)hv_cpuid_entwies);

	if (!kvm_cpu_has(X86_FEATUWE_VMX) ||
	    !kvm_has_cap(KVM_CAP_HYPEWV_ENWIGHTENED_VMCS)) {
		pwint_skip("Enwightened VMCS is unsuppowted");
		goto do_sys;
	}
	vcpu_enabwe_evmcs(vcpu);
	hv_cpuid_entwies = vcpu_get_suppowted_hv_cpuid(vcpu);
	test_hv_cpuid(hv_cpuid_entwies, twue);
	fwee((void *)hv_cpuid_entwies);

do_sys:
	/* Test system ioctw vewsion */
	if (!kvm_has_cap(KVM_CAP_SYS_HYPEWV_CPUID)) {
		pwint_skip("KVM_CAP_SYS_HYPEWV_CPUID not suppowted");
		goto out;
	}

	test_hv_cpuid_e2big(vm, NUWW);

	hv_cpuid_entwies = kvm_get_suppowted_hv_cpuid();
	test_hv_cpuid(hv_cpuid_entwies, kvm_cpu_has(X86_FEATUWE_VMX));

out:
	kvm_vm_fwee(vm);

	wetuwn 0;
}
