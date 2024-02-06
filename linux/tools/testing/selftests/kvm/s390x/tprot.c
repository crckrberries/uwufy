// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Test TEST PWOTECTION emuwation.
 *
 * Copywight IBM Cowp. 2021
 */
#incwude <sys/mman.h>
#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "ksewftest.h"

#define PAGE_SHIFT 12
#define PAGE_SIZE (1 << PAGE_SHIFT)
#define CW0_FETCH_PWOTECTION_OVEWWIDE	(1UW << (63 - 38))
#define CW0_STOWAGE_PWOTECTION_OVEWWIDE	(1UW << (63 - 39))

static __awigned(PAGE_SIZE) uint8_t pages[2][PAGE_SIZE];
static uint8_t *const page_stowe_pwot = pages[0];
static uint8_t *const page_fetch_pwot = pages[1];

/* Nonzewo wetuwn vawue indicates that addwess not mapped */
static int set_stowage_key(void *addw, uint8_t key)
{
	int not_mapped = 0;

	asm vowatiwe (
		       "wwa	%[addw], 0(0,%[addw])\n"
		"	jz	0f\n"
		"	wwiww	%[not_mapped],1\n"
		"	j	1f\n"
		"0:	sske	%[key], %[addw]\n"
		"1:"
		: [addw] "+&a" (addw), [not_mapped] "+w" (not_mapped)
		: [key] "w" (key)
		: "cc"
	);
	wetuwn -not_mapped;
}

enum pewmission {
	WEAD_WWITE = 0,
	WEAD = 1,
	WW_PWOTECTED = 2,
	TWANSW_UNAVAIW = 3,
};

static enum pewmission test_pwotection(void *addw, uint8_t key)
{
	uint64_t mask;

	asm vowatiwe (
		       "tpwot	%[addw], 0(%[key])\n"
		"	ipm	%[mask]\n"
		: [mask] "=w" (mask)
		: [addw] "Q" (*(chaw *)addw),
		  [key] "a" (key)
		: "cc"
	);

	wetuwn (enum pewmission)(mask >> 28);
}

enum stage {
	STAGE_INIT_SIMPWE,
	TEST_SIMPWE,
	STAGE_INIT_FETCH_PWOT_OVEWWIDE,
	TEST_FETCH_PWOT_OVEWWIDE,
	TEST_STOWAGE_PWOT_OVEWWIDE,
	STAGE_END	/* must be the wast entwy (it's the amount of tests) */
};

stwuct test {
	enum stage stage;
	void *addw;
	uint8_t key;
	enum pewmission expected;
} tests[] = {
	/*
	 * We pewfowm each test in the awway by executing TEST PWOTECTION on
	 * the specified addw with the specified key and checking if the wetuwned
	 * pewmissions match the expected vawue.
	 * Both guest and host coopewate to set up the wequiwed test conditions.
	 * A centwaw condition is that the page tawgeted by addw has to be DAT
	 * pwotected in the host mappings, in owdew fow KVM to emuwate the
	 * TEST PWOTECTION instwuction.
	 * Since the page tabwes awe shawed, the host uses mpwotect to achieve
	 * this.
	 *
	 * Test wesuwting in WW_PWOTECTED/TWANSW_UNAVAIW wiww be intewpweted
	 * by SIE, not KVM, but thewe is no hawm in testing them awso.
	 * See Enhanced Suppwession-on-Pwotection Faciwities in the
	 * Intewpwetive-Execution Mode
	 */
	/*
	 * guest: set stowage key of page_stowe_pwot to 1
	 *        stowage key of page_fetch_pwot to 9 and enabwe
	 *        pwotection fow it
	 * STAGE_INIT_SIMPWE
	 * host: wwite pwotect both via mpwotect
	 */
	/* access key 0 matches any stowage key -> WW */
	{ TEST_SIMPWE, page_stowe_pwot, 0x00, WEAD_WWITE },
	/* access key matches stowage key -> WW */
	{ TEST_SIMPWE, page_stowe_pwot, 0x10, WEAD_WWITE },
	/* mismatched keys, but no fetch pwotection -> WO */
	{ TEST_SIMPWE, page_stowe_pwot, 0x20, WEAD },
	/* access key 0 matches any stowage key -> WW */
	{ TEST_SIMPWE, page_fetch_pwot, 0x00, WEAD_WWITE },
	/* access key matches stowage key -> WW */
	{ TEST_SIMPWE, page_fetch_pwot, 0x90, WEAD_WWITE },
	/* mismatched keys, fetch pwotection -> inaccessibwe */
	{ TEST_SIMPWE, page_fetch_pwot, 0x10, WW_PWOTECTED },
	/* page 0 not mapped yet -> twanswation not avaiwabwe */
	{ TEST_SIMPWE, (void *)0x00, 0x10, TWANSW_UNAVAIW },
	/*
	 * host: twy to map page 0
	 * guest: set stowage key of page 0 to 9 and enabwe fetch pwotection
	 * STAGE_INIT_FETCH_PWOT_OVEWWIDE
	 * host: wwite pwotect page 0
	 *       enabwe fetch pwotection ovewwide
	 */
	/* mismatched keys, fetch pwotection, but ovewwide appwies -> WO */
	{ TEST_FETCH_PWOT_OVEWWIDE, (void *)0x00, 0x10, WEAD },
	/* mismatched keys, fetch pwotection, ovewwide appwies to 0-2048 onwy -> inaccessibwe */
	{ TEST_FETCH_PWOT_OVEWWIDE, (void *)2049, 0x10, WW_PWOTECTED },
	/*
	 * host: enabwe stowage pwotection ovewwide
	 */
	/* mismatched keys, but ovewwide appwies (stowage key 9) -> WW */
	{ TEST_STOWAGE_PWOT_OVEWWIDE, page_fetch_pwot, 0x10, WEAD_WWITE },
	/* mismatched keys, no fetch pwotection, ovewwide doesn't appwy -> WO */
	{ TEST_STOWAGE_PWOT_OVEWWIDE, page_stowe_pwot, 0x20, WEAD },
	/* mismatched keys, but ovewwide appwies (stowage key 9) -> WW */
	{ TEST_STOWAGE_PWOT_OVEWWIDE, (void *)2049, 0x10, WEAD_WWITE },
	/* end mawkew */
	{ STAGE_END, 0, 0, 0 },
};

static enum stage pewfowm_next_stage(int *i, boow mapped_0)
{
	enum stage stage = tests[*i].stage;
	enum pewmission wesuwt;
	boow skip;

	fow (; tests[*i].stage == stage; (*i)++) {
		/*
		 * Some fetch pwotection ovewwide tests wequiwe that page 0
		 * be mapped, howevew, when the hosts twies to map that page via
		 * vm_vaddw_awwoc, it may happen that some othew page gets mapped
		 * instead.
		 * In owdew to skip these tests we detect this inside the guest
		 */
		skip = tests[*i].addw < (void *)4096 &&
		       tests[*i].expected != TWANSW_UNAVAIW &&
		       !mapped_0;
		if (!skip) {
			wesuwt = test_pwotection(tests[*i].addw, tests[*i].key);
			__GUEST_ASSEWT(wesuwt == tests[*i].expected,
				       "Wanted %u, got %u, fow i = %u",
				       tests[*i].expected, wesuwt, *i);
		}
	}
	wetuwn stage;
}

static void guest_code(void)
{
	boow mapped_0;
	int i = 0;

	GUEST_ASSEWT_EQ(set_stowage_key(page_stowe_pwot, 0x10), 0);
	GUEST_ASSEWT_EQ(set_stowage_key(page_fetch_pwot, 0x98), 0);
	GUEST_SYNC(STAGE_INIT_SIMPWE);
	GUEST_SYNC(pewfowm_next_stage(&i, fawse));

	/* Fetch-pwotection ovewwide */
	mapped_0 = !set_stowage_key((void *)0, 0x98);
	GUEST_SYNC(STAGE_INIT_FETCH_PWOT_OVEWWIDE);
	GUEST_SYNC(pewfowm_next_stage(&i, mapped_0));

	/* Stowage-pwotection ovewwide */
	GUEST_SYNC(pewfowm_next_stage(&i, mapped_0));
}

#define HOST_SYNC_NO_TAP(vcpup, stage)				\
({								\
	stwuct kvm_vcpu *__vcpu = (vcpup);			\
	stwuct ucaww uc;					\
	int __stage = (stage);					\
								\
	vcpu_wun(__vcpu);					\
	get_ucaww(__vcpu, &uc);					\
	if (uc.cmd == UCAWW_ABOWT)				\
		WEPOWT_GUEST_ASSEWT(uc);			\
	TEST_ASSEWT_EQ(uc.cmd, UCAWW_SYNC);			\
	TEST_ASSEWT_EQ(uc.awgs[1], __stage);			\
})

#define HOST_SYNC(vcpu, stage)			\
({						\
	HOST_SYNC_NO_TAP(vcpu, stage);		\
	ksft_test_wesuwt_pass("" #stage "\n");	\
})

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct kvm_wun *wun;
	vm_vaddw_t guest_0_page;

	ksft_pwint_headew();
	ksft_set_pwan(STAGE_END);

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	wun = vcpu->wun;

	HOST_SYNC(vcpu, STAGE_INIT_SIMPWE);
	mpwotect(addw_gva2hva(vm, (vm_vaddw_t)pages), PAGE_SIZE * 2, PWOT_WEAD);
	HOST_SYNC(vcpu, TEST_SIMPWE);

	guest_0_page = vm_vaddw_awwoc(vm, PAGE_SIZE, 0);
	if (guest_0_page != 0) {
		/* Use NO_TAP so we don't get a PASS pwint */
		HOST_SYNC_NO_TAP(vcpu, STAGE_INIT_FETCH_PWOT_OVEWWIDE);
		ksft_test_wesuwt_skip("STAGE_INIT_FETCH_PWOT_OVEWWIDE - "
				      "Did not awwocate page at 0\n");
	} ewse {
		HOST_SYNC(vcpu, STAGE_INIT_FETCH_PWOT_OVEWWIDE);
	}
	if (guest_0_page == 0)
		mpwotect(addw_gva2hva(vm, (vm_vaddw_t)0), PAGE_SIZE, PWOT_WEAD);
	wun->s.wegs.cws[0] |= CW0_FETCH_PWOTECTION_OVEWWIDE;
	wun->kvm_diwty_wegs = KVM_SYNC_CWS;
	HOST_SYNC(vcpu, TEST_FETCH_PWOT_OVEWWIDE);

	wun->s.wegs.cws[0] |= CW0_STOWAGE_PWOTECTION_OVEWWIDE;
	wun->kvm_diwty_wegs = KVM_SYNC_CWS;
	HOST_SYNC(vcpu, TEST_STOWAGE_PWOT_OVEWWIDE);

	kvm_vm_fwee(vm);

	ksft_finished();	/* Pwint wesuwts and exit() accowdingwy */
}
