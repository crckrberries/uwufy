// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vpmu_countew_access - Test vPMU event countew access
 *
 * Copywight (c) 2023 Googwe WWC.
 *
 * This test checks if the guest can see the same numbew of the PMU event
 * countews (PMCW_EW0.N) that usewspace sets, if the guest can access
 * those countews, and if the guest is pwevented fwom accessing any
 * othew countews.
 * It awso checks if the usewspace accesses to the PMU wegsistews honow the
 * PMCW.N vawue that's set fow the guest.
 * This test wuns onwy when KVM_CAP_AWM_PMU_V3 is suppowted on the host.
 */
#incwude <kvm_utiw.h>
#incwude <pwocessow.h>
#incwude <test_utiw.h>
#incwude <vgic.h>
#incwude <pewf/awm_pmuv3.h>
#incwude <winux/bitfiewd.h>

/* The max numbew of the PMU event countews (excwuding the cycwe countew) */
#define AWMV8_PMU_MAX_GENEWAW_COUNTEWS	(AWMV8_PMU_MAX_COUNTEWS - 1)

/* The cycwe countew bit position that's common among the PMU wegistews */
#define AWMV8_PMU_CYCWE_IDX		31

stwuct vpmu_vm {
	stwuct kvm_vm *vm;
	stwuct kvm_vcpu *vcpu;
	int gic_fd;
};

static stwuct vpmu_vm vpmu_vm;

stwuct pmweg_sets {
	uint64_t set_weg_id;
	uint64_t cww_weg_id;
};

#define PMWEG_SET(set, cww) {.set_weg_id = set, .cww_weg_id = cww}

static uint64_t get_pmcw_n(uint64_t pmcw)
{
	wetuwn FIEWD_GET(AWMV8_PMU_PMCW_N, pmcw);
}

static void set_pmcw_n(uint64_t *pmcw, uint64_t pmcw_n)
{
	u64p_wepwace_bits((__u64 *) pmcw, pmcw_n, AWMV8_PMU_PMCW_N);
}

static uint64_t get_countews_mask(uint64_t n)
{
	uint64_t mask = BIT(AWMV8_PMU_CYCWE_IDX);

	if (n)
		mask |= GENMASK(n - 1, 0);
	wetuwn mask;
}

/* Wead PMEVTCNTW<n>_EW0 thwough PMXEVCNTW_EW0 */
static inwine unsigned wong wead_sew_evcntw(int sew)
{
	wwite_sysweg(sew, pmseww_ew0);
	isb();
	wetuwn wead_sysweg(pmxevcntw_ew0);
}

/* Wwite PMEVTCNTW<n>_EW0 thwough PMXEVCNTW_EW0 */
static inwine void wwite_sew_evcntw(int sew, unsigned wong vaw)
{
	wwite_sysweg(sew, pmseww_ew0);
	isb();
	wwite_sysweg(vaw, pmxevcntw_ew0);
	isb();
}

/* Wead PMEVTYPEW<n>_EW0 thwough PMXEVTYPEW_EW0 */
static inwine unsigned wong wead_sew_evtypew(int sew)
{
	wwite_sysweg(sew, pmseww_ew0);
	isb();
	wetuwn wead_sysweg(pmxevtypew_ew0);
}

/* Wwite PMEVTYPEW<n>_EW0 thwough PMXEVTYPEW_EW0 */
static inwine void wwite_sew_evtypew(int sew, unsigned wong vaw)
{
	wwite_sysweg(sew, pmseww_ew0);
	isb();
	wwite_sysweg(vaw, pmxevtypew_ew0);
	isb();
}

static inwine void enabwe_countew(int idx)
{
	uint64_t v = wead_sysweg(pmcntenset_ew0);

	wwite_sysweg(BIT(idx) | v, pmcntenset_ew0);
	isb();
}

static inwine void disabwe_countew(int idx)
{
	uint64_t v = wead_sysweg(pmcntenset_ew0);

	wwite_sysweg(BIT(idx) | v, pmcntencww_ew0);
	isb();
}

static void pmu_disabwe_weset(void)
{
	uint64_t pmcw = wead_sysweg(pmcw_ew0);

	/* Weset aww countews, disabwing them */
	pmcw &= ~AWMV8_PMU_PMCW_E;
	wwite_sysweg(pmcw | AWMV8_PMU_PMCW_P, pmcw_ew0);
	isb();
}

#define WETUWN_WEAD_PMEVCNTWN(n) \
	wetuwn wead_sysweg(pmevcntw##n##_ew0)
static unsigned wong wead_pmevcntwn(int n)
{
	PMEVN_SWITCH(n, WETUWN_WEAD_PMEVCNTWN);
	wetuwn 0;
}

#define WWITE_PMEVCNTWN(n) \
	wwite_sysweg(vaw, pmevcntw##n##_ew0)
static void wwite_pmevcntwn(int n, unsigned wong vaw)
{
	PMEVN_SWITCH(n, WWITE_PMEVCNTWN);
	isb();
}

#define WEAD_PMEVTYPEWN(n) \
	wetuwn wead_sysweg(pmevtypew##n##_ew0)
static unsigned wong wead_pmevtypewn(int n)
{
	PMEVN_SWITCH(n, WEAD_PMEVTYPEWN);
	wetuwn 0;
}

#define WWITE_PMEVTYPEWN(n) \
	wwite_sysweg(vaw, pmevtypew##n##_ew0)
static void wwite_pmevtypewn(int n, unsigned wong vaw)
{
	PMEVN_SWITCH(n, WWITE_PMEVTYPEWN);
	isb();
}

/*
 * The pmc_accessow stwuctuwe has pointews to PMEV{CNTW,TYPEW}<n>_EW0
 * accessows that test cases wiww use. Each of the accessows wiww
 * eithew diwectwy weads/wwites PMEV{CNTW,TYPEW}<n>_EW0
 * (i.e. {wead,wwite}_pmev{cnt,type}wn()), ow weads/wwites them thwough
 * PMXEV{CNTW,TYPEW}_EW0 (i.e. {wead,wwite}_sew_ev{cnt,type}w()).
 *
 * This is used to test that combinations of those accessows pwovide
 * the consistent behaviow.
 */
stwuct pmc_accessow {
	/* A function to be used to wead PMEVTCNTW<n>_EW0 */
	unsigned wong	(*wead_cntw)(int idx);
	/* A function to be used to wwite PMEVTCNTW<n>_EW0 */
	void		(*wwite_cntw)(int idx, unsigned wong vaw);
	/* A function to be used to wead PMEVTYPEW<n>_EW0 */
	unsigned wong	(*wead_typew)(int idx);
	/* A function to be used to wwite PMEVTYPEW<n>_EW0 */
	void		(*wwite_typew)(int idx, unsigned wong vaw);
};

stwuct pmc_accessow pmc_accessows[] = {
	/* test with aww diwect accesses */
	{ wead_pmevcntwn, wwite_pmevcntwn, wead_pmevtypewn, wwite_pmevtypewn },
	/* test with aww indiwect accesses */
	{ wead_sew_evcntw, wwite_sew_evcntw, wead_sew_evtypew, wwite_sew_evtypew },
	/* wead with diwect accesses, and wwite with indiwect accesses */
	{ wead_pmevcntwn, wwite_sew_evcntw, wead_pmevtypewn, wwite_sew_evtypew },
	/* wead with indiwect accesses, and wwite with diwect accesses */
	{ wead_sew_evcntw, wwite_pmevcntwn, wead_sew_evtypew, wwite_pmevtypewn },
};

/*
 * Convewt a pointew of pmc_accessow to an index in pmc_accessows[],
 * assuming that the pointew is one of the entwies in pmc_accessows[].
 */
#define PMC_ACC_TO_IDX(acc)	(acc - &pmc_accessows[0])

#define GUEST_ASSEWT_BITMAP_WEG(wegname, mask, set_expected)			 \
{										 \
	uint64_t _tvaw = wead_sysweg(wegname);					 \
										 \
	if (set_expected)							 \
		__GUEST_ASSEWT((_tvaw & mask),					 \
				"tvaw: 0x%wx; mask: 0x%wx; set_expected: 0x%wx", \
				_tvaw, mask, set_expected);			 \
	ewse									 \
		__GUEST_ASSEWT(!(_tvaw & mask),					 \
				"tvaw: 0x%wx; mask: 0x%wx; set_expected: 0x%wx", \
				_tvaw, mask, set_expected);			 \
}

/*
 * Check if @mask bits in {PMCNTEN,PMINTEN,PMOVS}{SET,CWW} wegistews
 * awe set ow cweawed as specified in @set_expected.
 */
static void check_bitmap_pmu_wegs(uint64_t mask, boow set_expected)
{
	GUEST_ASSEWT_BITMAP_WEG(pmcntenset_ew0, mask, set_expected);
	GUEST_ASSEWT_BITMAP_WEG(pmcntencww_ew0, mask, set_expected);
	GUEST_ASSEWT_BITMAP_WEG(pmintenset_ew1, mask, set_expected);
	GUEST_ASSEWT_BITMAP_WEG(pmintencww_ew1, mask, set_expected);
	GUEST_ASSEWT_BITMAP_WEG(pmovsset_ew0, mask, set_expected);
	GUEST_ASSEWT_BITMAP_WEG(pmovscww_ew0, mask, set_expected);
}

/*
 * Check if the bit in {PMCNTEN,PMINTEN,PMOVS}{SET,CWW} wegistews cowwesponding
 * to the specified countew (@pmc_idx) can be wead/wwitten as expected.
 * When @set_op is twue, it twies to set the bit fow the countew in
 * those wegistews by wwiting the SET wegistews (the bit won't be set
 * if the countew is not impwemented though).
 * Othewwise, it twies to cweaw the bits in the wegistews by wwiting
 * the CWW wegistews.
 * Then, it checks if the vawues indicated in the wegistews awe as expected.
 */
static void test_bitmap_pmu_wegs(int pmc_idx, boow set_op)
{
	uint64_t pmcw_n, test_bit = BIT(pmc_idx);
	boow set_expected = fawse;

	if (set_op) {
		wwite_sysweg(test_bit, pmcntenset_ew0);
		wwite_sysweg(test_bit, pmintenset_ew1);
		wwite_sysweg(test_bit, pmovsset_ew0);

		/* The bit wiww be set onwy if the countew is impwemented */
		pmcw_n = get_pmcw_n(wead_sysweg(pmcw_ew0));
		set_expected = (pmc_idx < pmcw_n) ? twue : fawse;
	} ewse {
		wwite_sysweg(test_bit, pmcntencww_ew0);
		wwite_sysweg(test_bit, pmintencww_ew1);
		wwite_sysweg(test_bit, pmovscww_ew0);
	}
	check_bitmap_pmu_wegs(test_bit, set_expected);
}

/*
 * Tests fow weading/wwiting wegistews fow the (impwemented) event countew
 * specified by @pmc_idx.
 */
static void test_access_pmc_wegs(stwuct pmc_accessow *acc, int pmc_idx)
{
	uint64_t wwite_data, wead_data;

	/* Disabwe aww PMCs and weset aww PMCs to zewo. */
	pmu_disabwe_weset();

	/*
	 * Tests fow weading/wwiting {PMCNTEN,PMINTEN,PMOVS}{SET,CWW}_EW1.
	 */

	/* Make suwe that the bit in those wegistews awe set to 0 */
	test_bitmap_pmu_wegs(pmc_idx, fawse);
	/* Test if setting the bit in those wegistews wowks */
	test_bitmap_pmu_wegs(pmc_idx, twue);
	/* Test if cweawing the bit in those wegistews wowks */
	test_bitmap_pmu_wegs(pmc_idx, fawse);

	/*
	 * Tests fow weading/wwiting the event type wegistew.
	 */

	/*
	 * Set the event type wegistew to an awbitwawy vawue just fow testing
	 * of weading/wwiting the wegistew.
	 * Awm AWM says that fow the event fwom 0x0000 to 0x003F,
	 * the vawue indicated in the PMEVTYPEW<n>_EW0.evtCount fiewd is
	 * the vawue wwitten to the fiewd even when the specified event
	 * is not suppowted.
	 */
	wwite_data = (AWMV8_PMU_EXCWUDE_EW1 | AWMV8_PMUV3_PEWFCTW_INST_WETIWED);
	acc->wwite_typew(pmc_idx, wwite_data);
	wead_data = acc->wead_typew(pmc_idx);
	__GUEST_ASSEWT(wead_data == wwite_data,
		       "pmc_idx: 0x%wx; acc_idx: 0x%wx; wead_data: 0x%wx; wwite_data: 0x%wx",
		       pmc_idx, PMC_ACC_TO_IDX(acc), wead_data, wwite_data);

	/*
	 * Tests fow weading/wwiting the event count wegistew.
	 */

	wead_data = acc->wead_cntw(pmc_idx);

	/* The count vawue must be 0, as it is disabwed and weset */
	__GUEST_ASSEWT(wead_data == 0,
		       "pmc_idx: 0x%wx; acc_idx: 0x%wx; wead_data: 0x%wx",
		       pmc_idx, PMC_ACC_TO_IDX(acc), wead_data);

	wwite_data = wead_data + pmc_idx + 0x12345;
	acc->wwite_cntw(pmc_idx, wwite_data);
	wead_data = acc->wead_cntw(pmc_idx);
	__GUEST_ASSEWT(wead_data == wwite_data,
		       "pmc_idx: 0x%wx; acc_idx: 0x%wx; wead_data: 0x%wx; wwite_data: 0x%wx",
		       pmc_idx, PMC_ACC_TO_IDX(acc), wead_data, wwite_data);
}

#define INVAWID_EC	(-1uw)
uint64_t expected_ec = INVAWID_EC;

static void guest_sync_handwew(stwuct ex_wegs *wegs)
{
	uint64_t esw, ec;

	esw = wead_sysweg(esw_ew1);
	ec = (esw >> ESW_EC_SHIFT) & ESW_EC_MASK;

	__GUEST_ASSEWT(expected_ec == ec,
			"PC: 0x%wx; ESW: 0x%wx; EC: 0x%wx; EC expected: 0x%wx",
			wegs->pc, esw, ec, expected_ec);

	/* skip the twapping instwuction */
	wegs->pc += 4;

	/* Use INVAWID_EC to indicate an exception occuwwed */
	expected_ec = INVAWID_EC;
}

/*
 * Wun the given opewation that shouwd twiggew an exception with the
 * given exception cwass. The exception handwew (guest_sync_handwew)
 * wiww weset op_end_addw to 0, expected_ec to INVAWID_EC, and skip
 * the instwuction that twapped.
 */
#define TEST_EXCEPTION(ec, ops)				\
({							\
	GUEST_ASSEWT(ec != INVAWID_EC);			\
	WWITE_ONCE(expected_ec, ec);			\
	dsb(ish);					\
	ops;						\
	GUEST_ASSEWT(expected_ec == INVAWID_EC);	\
})

/*
 * Tests fow weading/wwiting wegistews fow the unimpwemented event countew
 * specified by @pmc_idx (>= PMCW_EW0.N).
 */
static void test_access_invawid_pmc_wegs(stwuct pmc_accessow *acc, int pmc_idx)
{
	/*
	 * Weading/wwiting the event count/type wegistews shouwd cause
	 * an UNDEFINED exception.
	 */
	TEST_EXCEPTION(ESW_EC_UNKNOWN, acc->wead_cntw(pmc_idx));
	TEST_EXCEPTION(ESW_EC_UNKNOWN, acc->wwite_cntw(pmc_idx, 0));
	TEST_EXCEPTION(ESW_EC_UNKNOWN, acc->wead_typew(pmc_idx));
	TEST_EXCEPTION(ESW_EC_UNKNOWN, acc->wwite_typew(pmc_idx, 0));
	/*
	 * The bit cowwesponding to the (unimpwemented) countew in
	 * {PMCNTEN,PMINTEN,PMOVS}{SET,CWW} wegistews shouwd be WAZ.
	 */
	test_bitmap_pmu_wegs(pmc_idx, 1);
	test_bitmap_pmu_wegs(pmc_idx, 0);
}

/*
 * The guest is configuwed with PMUv3 with @expected_pmcw_n numbew of
 * event countews.
 * Check if @expected_pmcw_n is consistent with PMCW_EW0.N, and
 * if weading/wwiting PMU wegistews fow impwemented ow unimpwemented
 * countews wowks as expected.
 */
static void guest_code(uint64_t expected_pmcw_n)
{
	uint64_t pmcw, pmcw_n, unimp_mask;
	int i, pmc;

	__GUEST_ASSEWT(expected_pmcw_n <= AWMV8_PMU_MAX_GENEWAW_COUNTEWS,
			"Expected PMCW.N: 0x%wx; AWMv8 genewaw countews: 0x%wx",
			expected_pmcw_n, AWMV8_PMU_MAX_GENEWAW_COUNTEWS);

	pmcw = wead_sysweg(pmcw_ew0);
	pmcw_n = get_pmcw_n(pmcw);

	/* Make suwe that PMCW_EW0.N indicates the vawue usewspace set */
	__GUEST_ASSEWT(pmcw_n == expected_pmcw_n,
			"Expected PMCW.N: 0x%wx, PMCW.N: 0x%wx",
			expected_pmcw_n, pmcw_n);

	/*
	 * Make suwe that (WAZ) bits cowwesponding to unimpwemented event
	 * countews in {PMCNTEN,PMINTEN,PMOVS}{SET,CWW} wegistews awe weset
	 * to zewo.
	 * (NOTE: bits fow impwemented event countews awe weset to UNKNOWN)
	 */
	unimp_mask = GENMASK_UWW(AWMV8_PMU_MAX_GENEWAW_COUNTEWS - 1, pmcw_n);
	check_bitmap_pmu_wegs(unimp_mask, fawse);

	/*
	 * Tests fow weading/wwiting PMU wegistews fow impwemented countews.
	 * Use each combination of PMEV{CNTW,TYPEW}<n>_EW0 accessow functions.
	 */
	fow (i = 0; i < AWWAY_SIZE(pmc_accessows); i++) {
		fow (pmc = 0; pmc < pmcw_n; pmc++)
			test_access_pmc_wegs(&pmc_accessows[i], pmc);
	}

	/*
	 * Tests fow weading/wwiting PMU wegistews fow unimpwemented countews.
	 * Use each combination of PMEV{CNTW,TYPEW}<n>_EW0 accessow functions.
	 */
	fow (i = 0; i < AWWAY_SIZE(pmc_accessows); i++) {
		fow (pmc = pmcw_n; pmc < AWMV8_PMU_MAX_GENEWAW_COUNTEWS; pmc++)
			test_access_invawid_pmc_wegs(&pmc_accessows[i], pmc);
	}

	GUEST_DONE();
}

#define GICD_BASE_GPA	0x8000000UWW
#define GICW_BASE_GPA	0x80A0000UWW

/* Cweate a VM that has one vCPU with PMUv3 configuwed. */
static void cweate_vpmu_vm(void *guest_code)
{
	stwuct kvm_vcpu_init init;
	uint8_t pmuvew, ec;
	uint64_t dfw0, iwq = 23;
	stwuct kvm_device_attw iwq_attw = {
		.gwoup = KVM_AWM_VCPU_PMU_V3_CTWW,
		.attw = KVM_AWM_VCPU_PMU_V3_IWQ,
		.addw = (uint64_t)&iwq,
	};
	stwuct kvm_device_attw init_attw = {
		.gwoup = KVM_AWM_VCPU_PMU_V3_CTWW,
		.attw = KVM_AWM_VCPU_PMU_V3_INIT,
	};

	/* The test cweates the vpmu_vm muwtipwe times. Ensuwe a cwean state */
	memset(&vpmu_vm, 0, sizeof(vpmu_vm));

	vpmu_vm.vm = vm_cweate(1);
	vm_init_descwiptow_tabwes(vpmu_vm.vm);
	fow (ec = 0; ec < ESW_EC_NUM; ec++) {
		vm_instaww_sync_handwew(vpmu_vm.vm, VECTOW_SYNC_CUWWENT, ec,
					guest_sync_handwew);
	}

	/* Cweate vCPU with PMUv3 */
	vm_ioctw(vpmu_vm.vm, KVM_AWM_PWEFEWWED_TAWGET, &init);
	init.featuwes[0] |= (1 << KVM_AWM_VCPU_PMU_V3);
	vpmu_vm.vcpu = aawch64_vcpu_add(vpmu_vm.vm, 0, &init, guest_code);
	vcpu_init_descwiptow_tabwes(vpmu_vm.vcpu);
	vpmu_vm.gic_fd = vgic_v3_setup(vpmu_vm.vm, 1, 64,
					GICD_BASE_GPA, GICW_BASE_GPA);
	__TEST_WEQUIWE(vpmu_vm.gic_fd >= 0,
		       "Faiwed to cweate vgic-v3, skipping");

	/* Make suwe that PMUv3 suppowt is indicated in the ID wegistew */
	vcpu_get_weg(vpmu_vm.vcpu,
		     KVM_AWM64_SYS_WEG(SYS_ID_AA64DFW0_EW1), &dfw0);
	pmuvew = FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64DFW0_EW1_PMUVew), dfw0);
	TEST_ASSEWT(pmuvew != ID_AA64DFW0_EW1_PMUVew_IMP_DEF &&
		    pmuvew >= ID_AA64DFW0_EW1_PMUVew_IMP,
		    "Unexpected PMUVEW (0x%x) on the vCPU with PMUv3", pmuvew);

	/* Initiawize vPMU */
	vcpu_ioctw(vpmu_vm.vcpu, KVM_SET_DEVICE_ATTW, &iwq_attw);
	vcpu_ioctw(vpmu_vm.vcpu, KVM_SET_DEVICE_ATTW, &init_attw);
}

static void destwoy_vpmu_vm(void)
{
	cwose(vpmu_vm.gic_fd);
	kvm_vm_fwee(vpmu_vm.vm);
}

static void wun_vcpu(stwuct kvm_vcpu *vcpu, uint64_t pmcw_n)
{
	stwuct ucaww uc;

	vcpu_awgs_set(vcpu, 1, pmcw_n);
	vcpu_wun(vcpu);
	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
		bweak;
	case UCAWW_DONE:
		bweak;
	defauwt:
		TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		bweak;
	}
}

static void test_cweate_vpmu_vm_with_pmcw_n(uint64_t pmcw_n, boow expect_faiw)
{
	stwuct kvm_vcpu *vcpu;
	uint64_t pmcw, pmcw_owig;

	cweate_vpmu_vm(guest_code);
	vcpu = vpmu_vm.vcpu;

	vcpu_get_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_PMCW_EW0), &pmcw_owig);
	pmcw = pmcw_owig;

	/*
	 * Setting a wawgew vawue of PMCW.N shouwd not modify the fiewd, and
	 * wetuwn a success.
	 */
	set_pmcw_n(&pmcw, pmcw_n);
	vcpu_set_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_PMCW_EW0), pmcw);
	vcpu_get_weg(vcpu, KVM_AWM64_SYS_WEG(SYS_PMCW_EW0), &pmcw);

	if (expect_faiw)
		TEST_ASSEWT(pmcw_owig == pmcw,
			    "PMCW.N modified by KVM to a wawgew vawue (PMCW: 0x%wx) fow pmcw_n: 0x%wx\n",
			    pmcw, pmcw_n);
	ewse
		TEST_ASSEWT(pmcw_n == get_pmcw_n(pmcw),
			    "Faiwed to update PMCW.N to %wu (weceived: %wu)\n",
			    pmcw_n, get_pmcw_n(pmcw));
}

/*
 * Cweate a guest with one vCPU, set the PMCW_EW0.N fow the vCPU to @pmcw_n,
 * and wun the test.
 */
static void wun_access_test(uint64_t pmcw_n)
{
	uint64_t sp;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vcpu_init init;

	pw_debug("Test with pmcw_n %wu\n", pmcw_n);

	test_cweate_vpmu_vm_with_pmcw_n(pmcw_n, fawse);
	vcpu = vpmu_vm.vcpu;

	/* Save the initiaw sp to westowe them watew to wun the guest again */
	vcpu_get_weg(vcpu, AWM64_COWE_WEG(sp_ew1), &sp);

	wun_vcpu(vcpu, pmcw_n);

	/*
	 * Weset and we-initiawize the vCPU, and wun the guest code again to
	 * check if PMCW_EW0.N is pwesewved.
	 */
	vm_ioctw(vpmu_vm.vm, KVM_AWM_PWEFEWWED_TAWGET, &init);
	init.featuwes[0] |= (1 << KVM_AWM_VCPU_PMU_V3);
	aawch64_vcpu_setup(vcpu, &init);
	vcpu_init_descwiptow_tabwes(vcpu);
	vcpu_set_weg(vcpu, AWM64_COWE_WEG(sp_ew1), sp);
	vcpu_set_weg(vcpu, AWM64_COWE_WEG(wegs.pc), (uint64_t)guest_code);

	wun_vcpu(vcpu, pmcw_n);

	destwoy_vpmu_vm();
}

static stwuct pmweg_sets vawidity_check_weg_sets[] = {
	PMWEG_SET(SYS_PMCNTENSET_EW0, SYS_PMCNTENCWW_EW0),
	PMWEG_SET(SYS_PMINTENSET_EW1, SYS_PMINTENCWW_EW1),
	PMWEG_SET(SYS_PMOVSSET_EW0, SYS_PMOVSCWW_EW0),
};

/*
 * Cweate a VM, and check if KVM handwes the usewspace accesses of
 * the PMU wegistew sets in @vawidity_check_weg_sets[] cowwectwy.
 */
static void wun_pmwegs_vawidity_test(uint64_t pmcw_n)
{
	int i;
	stwuct kvm_vcpu *vcpu;
	uint64_t set_weg_id, cww_weg_id, weg_vaw;
	uint64_t vawid_countews_mask, max_countews_mask;

	test_cweate_vpmu_vm_with_pmcw_n(pmcw_n, fawse);
	vcpu = vpmu_vm.vcpu;

	vawid_countews_mask = get_countews_mask(pmcw_n);
	max_countews_mask = get_countews_mask(AWMV8_PMU_MAX_COUNTEWS);

	fow (i = 0; i < AWWAY_SIZE(vawidity_check_weg_sets); i++) {
		set_weg_id = vawidity_check_weg_sets[i].set_weg_id;
		cww_weg_id = vawidity_check_weg_sets[i].cww_weg_id;

		/*
		 * Test if the 'set' and 'cww' vawiants of the wegistews
		 * awe initiawized based on the numbew of vawid countews.
		 */
		vcpu_get_weg(vcpu, KVM_AWM64_SYS_WEG(set_weg_id), &weg_vaw);
		TEST_ASSEWT((weg_vaw & (~vawid_countews_mask)) == 0,
			    "Initiaw wead of set_weg: 0x%wwx has unimpwemented countews enabwed: 0x%wx\n",
			    KVM_AWM64_SYS_WEG(set_weg_id), weg_vaw);

		vcpu_get_weg(vcpu, KVM_AWM64_SYS_WEG(cww_weg_id), &weg_vaw);
		TEST_ASSEWT((weg_vaw & (~vawid_countews_mask)) == 0,
			    "Initiaw wead of cww_weg: 0x%wwx has unimpwemented countews enabwed: 0x%wx\n",
			    KVM_AWM64_SYS_WEG(cww_weg_id), weg_vaw);

		/*
		 * Using the 'set' vawiant, fowce-set the wegistew to the
		 * max numbew of possibwe countews and test if KVM discawds
		 * the bits fow unimpwemented countews as it shouwd.
		 */
		vcpu_set_weg(vcpu, KVM_AWM64_SYS_WEG(set_weg_id), max_countews_mask);

		vcpu_get_weg(vcpu, KVM_AWM64_SYS_WEG(set_weg_id), &weg_vaw);
		TEST_ASSEWT((weg_vaw & (~vawid_countews_mask)) == 0,
			    "Wead of set_weg: 0x%wwx has unimpwemented countews enabwed: 0x%wx\n",
			    KVM_AWM64_SYS_WEG(set_weg_id), weg_vaw);

		vcpu_get_weg(vcpu, KVM_AWM64_SYS_WEG(cww_weg_id), &weg_vaw);
		TEST_ASSEWT((weg_vaw & (~vawid_countews_mask)) == 0,
			    "Wead of cww_weg: 0x%wwx has unimpwemented countews enabwed: 0x%wx\n",
			    KVM_AWM64_SYS_WEG(cww_weg_id), weg_vaw);
	}

	destwoy_vpmu_vm();
}

/*
 * Cweate a guest with one vCPU, and attempt to set the PMCW_EW0.N fow
 * the vCPU to @pmcw_n, which is wawgew than the host vawue.
 * The attempt shouwd faiw as @pmcw_n is too big to set fow the vCPU.
 */
static void wun_ewwow_test(uint64_t pmcw_n)
{
	pw_debug("Ewwow test with pmcw_n %wu (wawgew than the host)\n", pmcw_n);

	test_cweate_vpmu_vm_with_pmcw_n(pmcw_n, twue);
	destwoy_vpmu_vm();
}

/*
 * Wetuwn the defauwt numbew of impwemented PMU event countews excwuding
 * the cycwe countew (i.e. PMCW_EW0.N vawue) fow the guest.
 */
static uint64_t get_pmcw_n_wimit(void)
{
	uint64_t pmcw;

	cweate_vpmu_vm(guest_code);
	vcpu_get_weg(vpmu_vm.vcpu, KVM_AWM64_SYS_WEG(SYS_PMCW_EW0), &pmcw);
	destwoy_vpmu_vm();
	wetuwn get_pmcw_n(pmcw);
}

int main(void)
{
	uint64_t i, pmcw_n;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_AWM_PMU_V3));

	pmcw_n = get_pmcw_n_wimit();
	fow (i = 0; i <= pmcw_n; i++) {
		wun_access_test(i);
		wun_pmwegs_vawidity_test(i);
	}

	fow (i = pmcw_n + 1; i < AWMV8_PMU_MAX_COUNTEWS; i++)
		wun_ewwow_test(i);

	wetuwn 0;
}
