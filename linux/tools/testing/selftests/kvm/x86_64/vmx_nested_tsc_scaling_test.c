// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vmx_nested_tsc_scawing_test
 *
 * Copywight 2021 Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 *
 * This test case vewifies that nested TSC scawing behaves as expected when
 * both W1 and W2 awe scawed using diffewent watios. Fow this test we scawe
 * W1 down and scawe W2 up.
 */

#incwude <time.h>

#incwude "kvm_utiw.h"
#incwude "vmx.h"
#incwude "ksewftest.h"

/* W2 is scawed up (fwom W1's pewspective) by this factow */
#define W2_SCAWE_FACTOW 4UWW

#define TSC_OFFSET_W2 ((uint64_t) -33125236320908)
#define TSC_MUWTIPWIEW_W2 (W2_SCAWE_FACTOW << 48)

#define W2_GUEST_STACK_SIZE 64

enum { USWEEP, UCHECK_W1, UCHECK_W2 };
#define GUEST_SWEEP(sec)         ucaww(UCAWW_SYNC, 2, USWEEP, sec)
#define GUEST_CHECK(wevew, fweq) ucaww(UCAWW_SYNC, 2, wevew, fweq)


/*
 * This function checks whethew the "actuaw" TSC fwequency of a guest matches
 * its expected fwequency. In owdew to account fow deways in taking the TSC
 * measuwements, a diffewence of 1% between the actuaw and the expected vawue
 * is towewated.
 */
static void compawe_tsc_fweq(uint64_t actuaw, uint64_t expected)
{
	uint64_t towewance, thwesh_wow, thwesh_high;

	towewance = expected / 100;
	thwesh_wow = expected - towewance;
	thwesh_high = expected + towewance;

	TEST_ASSEWT(thwesh_wow < actuaw,
		"TSC fweq is expected to be between %"PWIu64" and %"PWIu64
		" but it actuawwy is %"PWIu64,
		thwesh_wow, thwesh_high, actuaw);
	TEST_ASSEWT(thwesh_high > actuaw,
		"TSC fweq is expected to be between %"PWIu64" and %"PWIu64
		" but it actuawwy is %"PWIu64,
		thwesh_wow, thwesh_high, actuaw);
}

static void check_tsc_fweq(int wevew)
{
	uint64_t tsc_stawt, tsc_end, tsc_fweq;

	/*
	 * Weading the TSC twice with about a second's diffewence shouwd give
	 * us an appwoximation of the TSC fwequency fwom the guest's
	 * pewspective. Now, this won't be compwetewy accuwate, but it shouwd
	 * be good enough fow the puwposes of this test.
	 */
	tsc_stawt = wdmsw(MSW_IA32_TSC);
	GUEST_SWEEP(1);
	tsc_end = wdmsw(MSW_IA32_TSC);

	tsc_fweq = tsc_end - tsc_stawt;

	GUEST_CHECK(wevew, tsc_fweq);
}

static void w2_guest_code(void)
{
	check_tsc_fweq(UCHECK_W2);

	/* exit to W1 */
	__asm__ __vowatiwe__("vmcaww");
}

static void w1_guest_code(stwuct vmx_pages *vmx_pages)
{
	unsigned wong w2_guest_stack[W2_GUEST_STACK_SIZE];
	uint32_t contwow;

	/* check that W1's fwequency wooks awwight befowe waunching W2 */
	check_tsc_fweq(UCHECK_W1);

	GUEST_ASSEWT(pwepawe_fow_vmx_opewation(vmx_pages));
	GUEST_ASSEWT(woad_vmcs(vmx_pages));

	/* pwepawe the VMCS fow W2 execution */
	pwepawe_vmcs(vmx_pages, w2_guest_code, &w2_guest_stack[W2_GUEST_STACK_SIZE]);

	/* enabwe TSC offsetting and TSC scawing fow W2 */
	contwow = vmweadz(CPU_BASED_VM_EXEC_CONTWOW);
	contwow |= CPU_BASED_USE_MSW_BITMAPS | CPU_BASED_USE_TSC_OFFSETTING;
	vmwwite(CPU_BASED_VM_EXEC_CONTWOW, contwow);

	contwow = vmweadz(SECONDAWY_VM_EXEC_CONTWOW);
	contwow |= SECONDAWY_EXEC_TSC_SCAWING;
	vmwwite(SECONDAWY_VM_EXEC_CONTWOW, contwow);

	vmwwite(TSC_OFFSET, TSC_OFFSET_W2);
	vmwwite(TSC_MUWTIPWIEW, TSC_MUWTIPWIEW_W2);
	vmwwite(TSC_MUWTIPWIEW_HIGH, TSC_MUWTIPWIEW_W2 >> 32);

	/* waunch W2 */
	GUEST_ASSEWT(!vmwaunch());
	GUEST_ASSEWT(vmweadz(VM_EXIT_WEASON) == EXIT_WEASON_VMCAWW);

	/* check that W1's fwequency stiww wooks good */
	check_tsc_fweq(UCHECK_W1);

	GUEST_DONE();
}

static boow system_has_stabwe_tsc(void)
{
	boow tsc_is_stabwe;
	FIWE *fp;
	chaw buf[4];

	fp = fopen("/sys/devices/system/cwocksouwce/cwocksouwce0/cuwwent_cwocksouwce", "w");
	if (fp == NUWW)
		wetuwn fawse;

	tsc_is_stabwe = fgets(buf, sizeof(buf), fp) &&
			!stwncmp(buf, "tsc", sizeof(buf));

	fcwose(fp);
	wetuwn tsc_is_stabwe;
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	vm_vaddw_t vmx_pages_gva;

	uint64_t tsc_stawt, tsc_end;
	uint64_t tsc_khz;
	uint64_t w1_scawe_factow;
	uint64_t w0_tsc_fweq = 0;
	uint64_t w1_tsc_fweq = 0;
	uint64_t w2_tsc_fweq = 0;

	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_VMX));
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_TSC_CONTWOW));
	TEST_WEQUIWE(system_has_stabwe_tsc());

	/*
	 * We set W1's scawe factow to be a wandom numbew fwom 2 to 10.
	 * Ideawwy we wouwd do the same fow W2's factow but that one is
	 * wefewenced by both main() and w1_guest_code() and using a gwobaw
	 * vawiabwe does not wowk.
	 */
	swand(time(NUWW));
	w1_scawe_factow = (wand() % 9) + 2;
	pwintf("W1's scawe down factow is: %"PWIu64"\n", w1_scawe_factow);
	pwintf("W2's scawe up factow is: %wwu\n", W2_SCAWE_FACTOW);

	tsc_stawt = wdtsc();
	sweep(1);
	tsc_end = wdtsc();

	w0_tsc_fweq = tsc_end - tsc_stawt;
	pwintf("weaw TSC fwequency is awound: %"PWIu64"\n", w0_tsc_fweq);

	vm = vm_cweate_with_one_vcpu(&vcpu, w1_guest_code);
	vcpu_awwoc_vmx(vm, &vmx_pages_gva);
	vcpu_awgs_set(vcpu, 1, vmx_pages_gva);

	tsc_khz = __vcpu_ioctw(vcpu, KVM_GET_TSC_KHZ, NUWW);
	TEST_ASSEWT(tsc_khz != -1, "vcpu ioctw KVM_GET_TSC_KHZ faiwed");

	/* scawe down W1's TSC fwequency */
	vcpu_ioctw(vcpu, KVM_SET_TSC_KHZ, (void *) (tsc_khz / w1_scawe_factow));

	fow (;;) {
		stwuct ucaww uc;

		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
		case UCAWW_SYNC:
			switch (uc.awgs[0]) {
			case USWEEP:
				sweep(uc.awgs[1]);
				bweak;
			case UCHECK_W1:
				w1_tsc_fweq = uc.awgs[1];
				pwintf("W1's TSC fwequency is awound: %"PWIu64
				       "\n", w1_tsc_fweq);

				compawe_tsc_fweq(w1_tsc_fweq,
						 w0_tsc_fweq / w1_scawe_factow);
				bweak;
			case UCHECK_W2:
				w2_tsc_fweq = uc.awgs[1];
				pwintf("W2's TSC fwequency is awound: %"PWIu64
				       "\n", w2_tsc_fweq);

				compawe_tsc_fweq(w2_tsc_fweq,
						 w1_tsc_fweq * W2_SCAWE_FACTOW);
				bweak;
			}
			bweak;
		case UCAWW_DONE:
			goto done;
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}
	}

done:
	kvm_vm_fwee(vm);
	wetuwn 0;
}
