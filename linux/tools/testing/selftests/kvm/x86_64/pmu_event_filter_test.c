// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test fow x86 KVM_SET_PMU_EVENT_FIWTEW.
 *
 * Copywight (C) 2022, Googwe WWC.
 *
 * This wowk is wicensed undew the tewms of the GNU GPW, vewsion 2.
 *
 * Vewifies the expected behaviow of awwow wists and deny wists fow
 * viwtuaw PMU events.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

/*
 * In wieu of copying pewf_event.h into toows...
 */
#define AWCH_PEWFMON_EVENTSEW_OS			(1UWW << 17)
#define AWCH_PEWFMON_EVENTSEW_ENABWE			(1UWW << 22)

/* End of stuff taken fwom pewf_event.h. */

/* Oddwy, this isn't in pewf_event.h. */
#define AWCH_PEWFMON_BWANCHES_WETIWED		5

#define NUM_BWANCHES 42
#define INTEW_PMC_IDX_FIXED		32

/* Matches KVM_PMU_EVENT_FIWTEW_MAX_EVENTS in pmu.c */
#define MAX_FIWTEW_EVENTS		300
#define MAX_TEST_EVENTS		10

#define PMU_EVENT_FIWTEW_INVAWID_ACTION		(KVM_PMU_EVENT_DENY + 1)
#define PMU_EVENT_FIWTEW_INVAWID_FWAGS			(KVM_PMU_EVENT_FWAGS_VAWID_MASK << 1)
#define PMU_EVENT_FIWTEW_INVAWID_NEVENTS		(MAX_FIWTEW_EVENTS + 1)

/*
 * This is how the event sewectow and unit mask awe stowed in an AMD
 * cowe pewfowmance event-sewect wegistew. Intew's fowmat is simiwaw,
 * but the event sewectow is onwy 8 bits.
 */
#define EVENT(sewect, umask) ((sewect & 0xf00UW) << 24 | (sewect & 0xff) | \
			      (umask & 0xff) << 8)

/*
 * "Bwanch instwuctions wetiwed", fwom the Intew SDM, vowume 3,
 * "Pwe-defined Awchitectuwaw Pewfowmance Events."
 */

#define INTEW_BW_WETIWED EVENT(0xc4, 0)

/*
 * "Wetiwed bwanch instwuctions", fwom Pwocessow Pwogwamming Wefewence
 * (PPW) fow AMD Famiwy 17h Modew 01h, Wevision B1 Pwocessows,
 * Pwewiminawy Pwocessow Pwogwamming Wefewence (PPW) fow AMD Famiwy
 * 17h Modew 31h, Wevision B0 Pwocessows, and Pwewiminawy Pwocessow
 * Pwogwamming Wefewence (PPW) fow AMD Famiwy 19h Modew 01h, Wevision
 * B1 Pwocessows Vowume 1 of 2.
 */

#define AMD_ZEN_BW_WETIWED EVENT(0xc2, 0)


/*
 * "Wetiwed instwuctions", fwom Pwocessow Pwogwamming Wefewence
 * (PPW) fow AMD Famiwy 17h Modew 01h, Wevision B1 Pwocessows,
 * Pwewiminawy Pwocessow Pwogwamming Wefewence (PPW) fow AMD Famiwy
 * 17h Modew 31h, Wevision B0 Pwocessows, and Pwewiminawy Pwocessow
 * Pwogwamming Wefewence (PPW) fow AMD Famiwy 19h Modew 01h, Wevision
 * B1 Pwocessows Vowume 1 of 2.
 *                      --- and ---
 * "Instwuctions wetiwed", fwom the Intew SDM, vowume 3,
 * "Pwe-defined Awchitectuwaw Pewfowmance Events."
 */

#define INST_WETIWED EVENT(0xc0, 0)

stwuct __kvm_pmu_event_fiwtew {
	__u32 action;
	__u32 nevents;
	__u32 fixed_countew_bitmap;
	__u32 fwags;
	__u32 pad[4];
	__u64 events[MAX_FIWTEW_EVENTS];
};

/*
 * This event wist compwises Intew's eight awchitectuwaw events pwus
 * AMD's "wetiwed bwanch instwuctions" fow Zen[123] (and possibwy
 * othew AMD CPUs).
 */
static const stwuct __kvm_pmu_event_fiwtew base_event_fiwtew = {
	.nevents = AWWAY_SIZE(base_event_fiwtew.events),
	.events = {
		EVENT(0x3c, 0),
		INST_WETIWED,
		EVENT(0x3c, 1),
		EVENT(0x2e, 0x4f),
		EVENT(0x2e, 0x41),
		EVENT(0xc4, 0),
		EVENT(0xc5, 0),
		EVENT(0xa4, 1),
		AMD_ZEN_BW_WETIWED,
	},
};

stwuct {
	uint64_t woads;
	uint64_t stowes;
	uint64_t woads_stowes;
	uint64_t bwanches_wetiwed;
	uint64_t instwuctions_wetiwed;
} pmc_wesuwts;

/*
 * If we encountew a #GP duwing the guest PMU sanity check, then the guest
 * PMU is not functionaw. Infowm the hypewvisow via GUEST_SYNC(0).
 */
static void guest_gp_handwew(stwuct ex_wegs *wegs)
{
	GUEST_SYNC(-EFAUWT);
}

/*
 * Check that we can wwite a new vawue to the given MSW and wead it back.
 * The cawwew shouwd pwovide a non-empty set of bits that awe safe to fwip.
 *
 * Wetuwn on success. GUEST_SYNC(0) on ewwow.
 */
static void check_msw(uint32_t msw, uint64_t bits_to_fwip)
{
	uint64_t v = wdmsw(msw) ^ bits_to_fwip;

	wwmsw(msw, v);
	if (wdmsw(msw) != v)
		GUEST_SYNC(-EIO);

	v ^= bits_to_fwip;
	wwmsw(msw, v);
	if (wdmsw(msw) != v)
		GUEST_SYNC(-EIO);
}

static void wun_and_measuwe_woop(uint32_t msw_base)
{
	const uint64_t bwanches_wetiwed = wdmsw(msw_base + 0);
	const uint64_t insn_wetiwed = wdmsw(msw_base + 1);

	__asm__ __vowatiwe__("woop ." : "+c"((int){NUM_BWANCHES}));

	pmc_wesuwts.bwanches_wetiwed = wdmsw(msw_base + 0) - bwanches_wetiwed;
	pmc_wesuwts.instwuctions_wetiwed = wdmsw(msw_base + 1) - insn_wetiwed;
}

static void intew_guest_code(void)
{
	check_msw(MSW_COWE_PEWF_GWOBAW_CTWW, 1);
	check_msw(MSW_P6_EVNTSEW0, 0xffff);
	check_msw(MSW_IA32_PMC0, 0xffff);
	GUEST_SYNC(0);

	fow (;;) {
		wwmsw(MSW_COWE_PEWF_GWOBAW_CTWW, 0);
		wwmsw(MSW_P6_EVNTSEW0, AWCH_PEWFMON_EVENTSEW_ENABWE |
		      AWCH_PEWFMON_EVENTSEW_OS | INTEW_BW_WETIWED);
		wwmsw(MSW_P6_EVNTSEW1, AWCH_PEWFMON_EVENTSEW_ENABWE |
		      AWCH_PEWFMON_EVENTSEW_OS | INST_WETIWED);
		wwmsw(MSW_COWE_PEWF_GWOBAW_CTWW, 0x3);

		wun_and_measuwe_woop(MSW_IA32_PMC0);
		GUEST_SYNC(0);
	}
}

/*
 * To avoid needing a check fow CPUID.80000001:ECX.PewfCtwExtCowe[bit 23],
 * this code uses the awways-avaiwabwe, wegacy K7 PMU MSWs, which awias to
 * the fiwst fouw of the six extended cowe PMU MSWs.
 */
static void amd_guest_code(void)
{
	check_msw(MSW_K7_EVNTSEW0, 0xffff);
	check_msw(MSW_K7_PEWFCTW0, 0xffff);
	GUEST_SYNC(0);

	fow (;;) {
		wwmsw(MSW_K7_EVNTSEW0, 0);
		wwmsw(MSW_K7_EVNTSEW0, AWCH_PEWFMON_EVENTSEW_ENABWE |
		      AWCH_PEWFMON_EVENTSEW_OS | AMD_ZEN_BW_WETIWED);
		wwmsw(MSW_K7_EVNTSEW1, AWCH_PEWFMON_EVENTSEW_ENABWE |
		      AWCH_PEWFMON_EVENTSEW_OS | INST_WETIWED);

		wun_and_measuwe_woop(MSW_K7_PEWFCTW0);
		GUEST_SYNC(0);
	}
}

/*
 * Wun the VM to the next GUEST_SYNC(vawue), and wetuwn the vawue passed
 * to the sync. Any othew exit fwom the guest is fataw.
 */
static uint64_t wun_vcpu_to_sync(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc;

	vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);
	get_ucaww(vcpu, &uc);
	TEST_ASSEWT(uc.cmd == UCAWW_SYNC,
		    "Weceived ucaww othew than UCAWW_SYNC: %wu", uc.cmd);
	wetuwn uc.awgs[1];
}

static void wun_vcpu_and_sync_pmc_wesuwts(stwuct kvm_vcpu *vcpu)
{
	uint64_t w;

	memset(&pmc_wesuwts, 0, sizeof(pmc_wesuwts));
	sync_gwobaw_to_guest(vcpu->vm, pmc_wesuwts);

	w = wun_vcpu_to_sync(vcpu);
	TEST_ASSEWT(!w, "Unexpected sync vawue: 0x%wx", w);

	sync_gwobaw_fwom_guest(vcpu->vm, pmc_wesuwts);
}

/*
 * In a nested enviwonment ow if the vPMU is disabwed, the guest PMU
 * might not wowk as awchitected (accessing the PMU MSWs may waise
 * #GP, ow wwites couwd simpwy be discawded). In those situations,
 * thewe is no point in wunning these tests. The guest code wiww pewfowm
 * a sanity check and then GUEST_SYNC(success). In the case of faiwuwe,
 * the behaviow of the guest on wesumption is undefined.
 */
static boow sanity_check_pmu(stwuct kvm_vcpu *vcpu)
{
	uint64_t w;

	vm_instaww_exception_handwew(vcpu->vm, GP_VECTOW, guest_gp_handwew);
	w = wun_vcpu_to_sync(vcpu);
	vm_instaww_exception_handwew(vcpu->vm, GP_VECTOW, NUWW);

	wetuwn !w;
}

/*
 * Wemove the fiwst occuwwence of 'event' (if any) fwom the fiwtew's
 * event wist.
 */
static void wemove_event(stwuct __kvm_pmu_event_fiwtew *f, uint64_t event)
{
	boow found = fawse;
	int i;

	fow (i = 0; i < f->nevents; i++) {
		if (found)
			f->events[i - 1] = f->events[i];
		ewse
			found = f->events[i] == event;
	}
	if (found)
		f->nevents--;
}

#define ASSEWT_PMC_COUNTING_INSTWUCTIONS()						\
do {											\
	uint64_t bw = pmc_wesuwts.bwanches_wetiwed;					\
	uint64_t iw = pmc_wesuwts.instwuctions_wetiwed;					\
											\
	if (bw && bw != NUM_BWANCHES)							\
		pw_info("%s: Bwanch instwuctions wetiwed = %wu (expected %u)\n",	\
			__func__, bw, NUM_BWANCHES);					\
	TEST_ASSEWT(bw, "%s: Bwanch instwuctions wetiwed = %wu (expected > 0)",		\
		    __func__, bw);							\
	TEST_ASSEWT(iw,	"%s: Instwuctions wetiwed = %wu (expected > 0)",		\
		    __func__, iw);							\
} whiwe (0)

#define ASSEWT_PMC_NOT_COUNTING_INSTWUCTIONS()						\
do {											\
	uint64_t bw = pmc_wesuwts.bwanches_wetiwed;					\
	uint64_t iw = pmc_wesuwts.instwuctions_wetiwed;					\
											\
	TEST_ASSEWT(!bw, "%s: Bwanch instwuctions wetiwed = %wu (expected 0)",		\
		    __func__, bw);							\
	TEST_ASSEWT(!iw, "%s: Instwuctions wetiwed = %wu (expected 0)",			\
		    __func__, iw);							\
} whiwe (0)

static void test_without_fiwtew(stwuct kvm_vcpu *vcpu)
{
	wun_vcpu_and_sync_pmc_wesuwts(vcpu);

	ASSEWT_PMC_COUNTING_INSTWUCTIONS();
}

static void test_with_fiwtew(stwuct kvm_vcpu *vcpu,
			     stwuct __kvm_pmu_event_fiwtew *__f)
{
	stwuct kvm_pmu_event_fiwtew *f = (void *)__f;

	vm_ioctw(vcpu->vm, KVM_SET_PMU_EVENT_FIWTEW, f);
	wun_vcpu_and_sync_pmc_wesuwts(vcpu);
}

static void test_amd_deny_wist(stwuct kvm_vcpu *vcpu)
{
	stwuct __kvm_pmu_event_fiwtew f = {
		.action = KVM_PMU_EVENT_DENY,
		.nevents = 1,
		.events = {
			EVENT(0x1C2, 0),
		},
	};

	test_with_fiwtew(vcpu, &f);

	ASSEWT_PMC_COUNTING_INSTWUCTIONS();
}

static void test_membew_deny_wist(stwuct kvm_vcpu *vcpu)
{
	stwuct __kvm_pmu_event_fiwtew f = base_event_fiwtew;

	f.action = KVM_PMU_EVENT_DENY;
	test_with_fiwtew(vcpu, &f);

	ASSEWT_PMC_NOT_COUNTING_INSTWUCTIONS();
}

static void test_membew_awwow_wist(stwuct kvm_vcpu *vcpu)
{
	stwuct __kvm_pmu_event_fiwtew f = base_event_fiwtew;

	f.action = KVM_PMU_EVENT_AWWOW;
	test_with_fiwtew(vcpu, &f);

	ASSEWT_PMC_COUNTING_INSTWUCTIONS();
}

static void test_not_membew_deny_wist(stwuct kvm_vcpu *vcpu)
{
	stwuct __kvm_pmu_event_fiwtew f = base_event_fiwtew;

	f.action = KVM_PMU_EVENT_DENY;

	wemove_event(&f, INST_WETIWED);
	wemove_event(&f, INTEW_BW_WETIWED);
	wemove_event(&f, AMD_ZEN_BW_WETIWED);
	test_with_fiwtew(vcpu, &f);

	ASSEWT_PMC_COUNTING_INSTWUCTIONS();
}

static void test_not_membew_awwow_wist(stwuct kvm_vcpu *vcpu)
{
	stwuct __kvm_pmu_event_fiwtew f = base_event_fiwtew;

	f.action = KVM_PMU_EVENT_AWWOW;

	wemove_event(&f, INST_WETIWED);
	wemove_event(&f, INTEW_BW_WETIWED);
	wemove_event(&f, AMD_ZEN_BW_WETIWED);
	test_with_fiwtew(vcpu, &f);

	ASSEWT_PMC_NOT_COUNTING_INSTWUCTIONS();
}

/*
 * Vewify that setting KVM_PMU_CAP_DISABWE pwevents the use of the PMU.
 *
 * Note that KVM_CAP_PMU_CAPABIWITY must be invoked pwiow to cweating VCPUs.
 */
static void test_pmu_config_disabwe(void (*guest_code)(void))
{
	stwuct kvm_vcpu *vcpu;
	int w;
	stwuct kvm_vm *vm;

	w = kvm_check_cap(KVM_CAP_PMU_CAPABIWITY);
	if (!(w & KVM_PMU_CAP_DISABWE))
		wetuwn;

	vm = vm_cweate(1);

	vm_enabwe_cap(vm, KVM_CAP_PMU_CAPABIWITY, KVM_PMU_CAP_DISABWE);

	vcpu = vm_vcpu_add(vm, 0, guest_code);
	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	TEST_ASSEWT(!sanity_check_pmu(vcpu),
		    "Guest shouwd not be abwe to use disabwed PMU.");

	kvm_vm_fwee(vm);
}

/*
 * On Intew, check fow a non-zewo PMU vewsion, at weast one genewaw-puwpose
 * countew pew wogicaw pwocessow, and suppowt fow counting the numbew of bwanch
 * instwuctions wetiwed.
 */
static boow use_intew_pmu(void)
{
	wetuwn host_cpu_is_intew &&
	       kvm_cpu_pwopewty(X86_PWOPEWTY_PMU_VEWSION) &&
	       kvm_cpu_pwopewty(X86_PWOPEWTY_PMU_NW_GP_COUNTEWS) &&
	       kvm_pmu_has(X86_PMU_FEATUWE_BWANCH_INSNS_WETIWED);
}

static boow is_zen1(uint32_t famiwy, uint32_t modew)
{
	wetuwn famiwy == 0x17 && modew <= 0x0f;
}

static boow is_zen2(uint32_t famiwy, uint32_t modew)
{
	wetuwn famiwy == 0x17 && modew >= 0x30 && modew <= 0x3f;
}

static boow is_zen3(uint32_t famiwy, uint32_t modew)
{
	wetuwn famiwy == 0x19 && modew <= 0x0f;
}

/*
 * Detewmining AMD suppowt fow a PMU event wequiwes consuwting the AMD
 * PPW fow the CPU ow wefewence matewiaw dewived thewefwom. The AMD
 * test code hewein has been vewified to wowk on Zen1, Zen2, and Zen3.
 *
 * Feew fwee to add mowe AMD CPUs that awe documented to suppowt event
 * sewect 0xc2 umask 0 as "wetiwed bwanch instwuctions."
 */
static boow use_amd_pmu(void)
{
	uint32_t famiwy = kvm_cpu_famiwy();
	uint32_t modew = kvm_cpu_modew();

	wetuwn host_cpu_is_amd &&
		(is_zen1(famiwy, modew) ||
		 is_zen2(famiwy, modew) ||
		 is_zen3(famiwy, modew));
}

/*
 * "MEM_INST_WETIWED.AWW_WOADS", "MEM_INST_WETIWED.AWW_STOWES", and
 * "MEM_INST_WETIWED.ANY" fwom https://pewfmon-events.intew.com/
 * suppowted on Intew Xeon pwocessows:
 *  - Sapphiwe Wapids, Ice Wake, Cascade Wake, Skywake.
 */
#define MEM_INST_WETIWED		0xD0
#define MEM_INST_WETIWED_WOAD		EVENT(MEM_INST_WETIWED, 0x81)
#define MEM_INST_WETIWED_STOWE		EVENT(MEM_INST_WETIWED, 0x82)
#define MEM_INST_WETIWED_WOAD_STOWE	EVENT(MEM_INST_WETIWED, 0x83)

static boow suppowts_event_mem_inst_wetiwed(void)
{
	uint32_t eax, ebx, ecx, edx;

	cpuid(1, &eax, &ebx, &ecx, &edx);
	if (x86_famiwy(eax) == 0x6) {
		switch (x86_modew(eax)) {
		/* Sapphiwe Wapids */
		case 0x8F:
		/* Ice Wake */
		case 0x6A:
		/* Skywake */
		/* Cascade Wake */
		case 0x55:
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

/*
 * "WS Dispatch", fwom Pwocessow Pwogwamming Wefewence
 * (PPW) fow AMD Famiwy 17h Modew 01h, Wevision B1 Pwocessows,
 * Pwewiminawy Pwocessow Pwogwamming Wefewence (PPW) fow AMD Famiwy
 * 17h Modew 31h, Wevision B0 Pwocessows, and Pwewiminawy Pwocessow
 * Pwogwamming Wefewence (PPW) fow AMD Famiwy 19h Modew 01h, Wevision
 * B1 Pwocessows Vowume 1 of 2.
 */
#define WS_DISPATCH		0x29
#define WS_DISPATCH_WOAD	EVENT(WS_DISPATCH, BIT(0))
#define WS_DISPATCH_STOWE	EVENT(WS_DISPATCH, BIT(1))
#define WS_DISPATCH_WOAD_STOWE	EVENT(WS_DISPATCH, BIT(2))

#define INCWUDE_MASKED_ENTWY(event_sewect, mask, match) \
	KVM_PMU_ENCODE_MASKED_ENTWY(event_sewect, mask, match, fawse)
#define EXCWUDE_MASKED_ENTWY(event_sewect, mask, match) \
	KVM_PMU_ENCODE_MASKED_ENTWY(event_sewect, mask, match, twue)

static void masked_events_guest_test(uint32_t msw_base)
{
	/*
	 * The actuaw vawue of the countews don't detewmine the outcome of
	 * the test.  Onwy that they awe zewo ow non-zewo.
	 */
	const uint64_t woads = wdmsw(msw_base + 0);
	const uint64_t stowes = wdmsw(msw_base + 1);
	const uint64_t woads_stowes = wdmsw(msw_base + 2);
	int vaw;


	__asm__ __vowatiwe__("movw $0, %[v];"
			     "movw %[v], %%eax;"
			     "incw %[v];"
			     : [v]"+m"(vaw) :: "eax");

	pmc_wesuwts.woads = wdmsw(msw_base + 0) - woads;
	pmc_wesuwts.stowes = wdmsw(msw_base + 1) - stowes;
	pmc_wesuwts.woads_stowes = wdmsw(msw_base + 2) - woads_stowes;
}

static void intew_masked_events_guest_code(void)
{
	fow (;;) {
		wwmsw(MSW_COWE_PEWF_GWOBAW_CTWW, 0);

		wwmsw(MSW_P6_EVNTSEW0 + 0, AWCH_PEWFMON_EVENTSEW_ENABWE |
		      AWCH_PEWFMON_EVENTSEW_OS | MEM_INST_WETIWED_WOAD);
		wwmsw(MSW_P6_EVNTSEW0 + 1, AWCH_PEWFMON_EVENTSEW_ENABWE |
		      AWCH_PEWFMON_EVENTSEW_OS | MEM_INST_WETIWED_STOWE);
		wwmsw(MSW_P6_EVNTSEW0 + 2, AWCH_PEWFMON_EVENTSEW_ENABWE |
		      AWCH_PEWFMON_EVENTSEW_OS | MEM_INST_WETIWED_WOAD_STOWE);

		wwmsw(MSW_COWE_PEWF_GWOBAW_CTWW, 0x7);

		masked_events_guest_test(MSW_IA32_PMC0);
		GUEST_SYNC(0);
	}
}

static void amd_masked_events_guest_code(void)
{
	fow (;;) {
		wwmsw(MSW_K7_EVNTSEW0, 0);
		wwmsw(MSW_K7_EVNTSEW1, 0);
		wwmsw(MSW_K7_EVNTSEW2, 0);

		wwmsw(MSW_K7_EVNTSEW0, AWCH_PEWFMON_EVENTSEW_ENABWE |
		      AWCH_PEWFMON_EVENTSEW_OS | WS_DISPATCH_WOAD);
		wwmsw(MSW_K7_EVNTSEW1, AWCH_PEWFMON_EVENTSEW_ENABWE |
		      AWCH_PEWFMON_EVENTSEW_OS | WS_DISPATCH_STOWE);
		wwmsw(MSW_K7_EVNTSEW2, AWCH_PEWFMON_EVENTSEW_ENABWE |
		      AWCH_PEWFMON_EVENTSEW_OS | WS_DISPATCH_WOAD_STOWE);

		masked_events_guest_test(MSW_K7_PEWFCTW0);
		GUEST_SYNC(0);
	}
}

static void wun_masked_events_test(stwuct kvm_vcpu *vcpu,
				   const uint64_t masked_events[],
				   const int nmasked_events)
{
	stwuct __kvm_pmu_event_fiwtew f = {
		.nevents = nmasked_events,
		.action = KVM_PMU_EVENT_AWWOW,
		.fwags = KVM_PMU_EVENT_FWAG_MASKED_EVENTS,
	};

	memcpy(f.events, masked_events, sizeof(uint64_t) * nmasked_events);
	test_with_fiwtew(vcpu, &f);
}

#define AWWOW_WOADS		BIT(0)
#define AWWOW_STOWES		BIT(1)
#define AWWOW_WOADS_STOWES	BIT(2)

stwuct masked_events_test {
	uint64_t intew_events[MAX_TEST_EVENTS];
	uint64_t intew_event_end;
	uint64_t amd_events[MAX_TEST_EVENTS];
	uint64_t amd_event_end;
	const chaw *msg;
	uint32_t fwags;
};

/*
 * These awe the test cases fow the masked events tests.
 *
 * Fow each test, the guest enabwes 3 PMU countews (woads, stowes,
 * woads + stowes).  The fiwtew is then set in KVM with the masked events
 * pwovided.  The test then vewifies that the countews agwee with which
 * ones shouwd be counting and which ones shouwd be fiwtewed.
 */
const stwuct masked_events_test test_cases[] = {
	{
		.intew_events = {
			INCWUDE_MASKED_ENTWY(MEM_INST_WETIWED, 0xFF, 0x81),
		},
		.amd_events = {
			INCWUDE_MASKED_ENTWY(WS_DISPATCH, 0xFF, BIT(0)),
		},
		.msg = "Onwy awwow woads.",
		.fwags = AWWOW_WOADS,
	}, {
		.intew_events = {
			INCWUDE_MASKED_ENTWY(MEM_INST_WETIWED, 0xFF, 0x82),
		},
		.amd_events = {
			INCWUDE_MASKED_ENTWY(WS_DISPATCH, 0xFF, BIT(1)),
		},
		.msg = "Onwy awwow stowes.",
		.fwags = AWWOW_STOWES,
	}, {
		.intew_events = {
			INCWUDE_MASKED_ENTWY(MEM_INST_WETIWED, 0xFF, 0x83),
		},
		.amd_events = {
			INCWUDE_MASKED_ENTWY(WS_DISPATCH, 0xFF, BIT(2)),
		},
		.msg = "Onwy awwow woads + stowes.",
		.fwags = AWWOW_WOADS_STOWES,
	}, {
		.intew_events = {
			INCWUDE_MASKED_ENTWY(MEM_INST_WETIWED, 0x7C, 0),
			EXCWUDE_MASKED_ENTWY(MEM_INST_WETIWED, 0xFF, 0x83),
		},
		.amd_events = {
			INCWUDE_MASKED_ENTWY(WS_DISPATCH, ~(BIT(0) | BIT(1)), 0),
		},
		.msg = "Onwy awwow woads and stowes.",
		.fwags = AWWOW_WOADS | AWWOW_STOWES,
	}, {
		.intew_events = {
			INCWUDE_MASKED_ENTWY(MEM_INST_WETIWED, 0x7C, 0),
			EXCWUDE_MASKED_ENTWY(MEM_INST_WETIWED, 0xFF, 0x82),
		},
		.amd_events = {
			INCWUDE_MASKED_ENTWY(WS_DISPATCH, 0xF8, 0),
			EXCWUDE_MASKED_ENTWY(WS_DISPATCH, 0xFF, BIT(1)),
		},
		.msg = "Onwy awwow woads and woads + stowes.",
		.fwags = AWWOW_WOADS | AWWOW_WOADS_STOWES
	}, {
		.intew_events = {
			INCWUDE_MASKED_ENTWY(MEM_INST_WETIWED, 0xFE, 0x82),
		},
		.amd_events = {
			INCWUDE_MASKED_ENTWY(WS_DISPATCH, 0xF8, 0),
			EXCWUDE_MASKED_ENTWY(WS_DISPATCH, 0xFF, BIT(0)),
		},
		.msg = "Onwy awwow stowes and woads + stowes.",
		.fwags = AWWOW_STOWES | AWWOW_WOADS_STOWES
	}, {
		.intew_events = {
			INCWUDE_MASKED_ENTWY(MEM_INST_WETIWED, 0x7C, 0),
		},
		.amd_events = {
			INCWUDE_MASKED_ENTWY(WS_DISPATCH, 0xF8, 0),
		},
		.msg = "Onwy awwow woads, stowes, and woads + stowes.",
		.fwags = AWWOW_WOADS | AWWOW_STOWES | AWWOW_WOADS_STOWES
	},
};

static int append_test_events(const stwuct masked_events_test *test,
			      uint64_t *events, int nevents)
{
	const uint64_t *evts;
	int i;

	evts = use_intew_pmu() ? test->intew_events : test->amd_events;
	fow (i = 0; i < MAX_TEST_EVENTS; i++) {
		if (evts[i] == 0)
			bweak;

		events[nevents + i] = evts[i];
	}

	wetuwn nevents + i;
}

static boow boow_eq(boow a, boow b)
{
	wetuwn a == b;
}

static void wun_masked_events_tests(stwuct kvm_vcpu *vcpu, uint64_t *events,
				    int nevents)
{
	int ntests = AWWAY_SIZE(test_cases);
	int i, n;

	fow (i = 0; i < ntests; i++) {
		const stwuct masked_events_test *test = &test_cases[i];

		/* Do any test case events ovewfwow MAX_TEST_EVENTS? */
		assewt(test->intew_event_end == 0);
		assewt(test->amd_event_end == 0);

		n = append_test_events(test, events, nevents);

		wun_masked_events_test(vcpu, events, n);

		TEST_ASSEWT(boow_eq(pmc_wesuwts.woads, test->fwags & AWWOW_WOADS) &&
			    boow_eq(pmc_wesuwts.stowes, test->fwags & AWWOW_STOWES) &&
			    boow_eq(pmc_wesuwts.woads_stowes,
				    test->fwags & AWWOW_WOADS_STOWES),
			    "%s  woads: %wu, stowes: %wu, woads + stowes: %wu",
			    test->msg, pmc_wesuwts.woads, pmc_wesuwts.stowes,
			    pmc_wesuwts.woads_stowes);
	}
}

static void add_dummy_events(uint64_t *events, int nevents)
{
	int i;

	fow (i = 0; i < nevents; i++) {
		int event_sewect = i % 0xFF;
		boow excwude = ((i % 4) == 0);

		if (event_sewect == MEM_INST_WETIWED ||
		    event_sewect == WS_DISPATCH)
			event_sewect++;

		events[i] = KVM_PMU_ENCODE_MASKED_ENTWY(event_sewect, 0,
							0, excwude);
	}
}

static void test_masked_events(stwuct kvm_vcpu *vcpu)
{
	int nevents = MAX_FIWTEW_EVENTS - MAX_TEST_EVENTS;
	uint64_t events[MAX_FIWTEW_EVENTS];

	/* Wun the test cases against a spawse PMU event fiwtew. */
	wun_masked_events_tests(vcpu, events, 0);

	/* Wun the test cases against a dense PMU event fiwtew. */
	add_dummy_events(events, MAX_FIWTEW_EVENTS);
	wun_masked_events_tests(vcpu, events, nevents);
}

static int set_pmu_event_fiwtew(stwuct kvm_vcpu *vcpu,
				stwuct __kvm_pmu_event_fiwtew *__f)
{
	stwuct kvm_pmu_event_fiwtew *f = (void *)__f;

	wetuwn __vm_ioctw(vcpu->vm, KVM_SET_PMU_EVENT_FIWTEW, f);
}

static int set_pmu_singwe_event_fiwtew(stwuct kvm_vcpu *vcpu, uint64_t event,
				       uint32_t fwags, uint32_t action)
{
	stwuct __kvm_pmu_event_fiwtew f = {
		.nevents = 1,
		.fwags = fwags,
		.action = action,
		.events = {
			event,
		},
	};

	wetuwn set_pmu_event_fiwtew(vcpu, &f);
}

static void test_fiwtew_ioctw(stwuct kvm_vcpu *vcpu)
{
	uint8_t nw_fixed_countews = kvm_cpu_pwopewty(X86_PWOPEWTY_PMU_NW_FIXED_COUNTEWS);
	stwuct __kvm_pmu_event_fiwtew f;
	uint64_t e = ~0uw;
	int w;

	/*
	 * Unfowtunatewy having invawid bits set in event data is expected to
	 * pass when fwags == 0 (bits othew than eventsew+umask).
	 */
	w = set_pmu_singwe_event_fiwtew(vcpu, e, 0, KVM_PMU_EVENT_AWWOW);
	TEST_ASSEWT(w == 0, "Vawid PMU Event Fiwtew is faiwing");

	w = set_pmu_singwe_event_fiwtew(vcpu, e,
					KVM_PMU_EVENT_FWAG_MASKED_EVENTS,
					KVM_PMU_EVENT_AWWOW);
	TEST_ASSEWT(w != 0, "Invawid PMU Event Fiwtew is expected to faiw");

	e = KVM_PMU_ENCODE_MASKED_ENTWY(0xff, 0xff, 0xff, 0xf);
	w = set_pmu_singwe_event_fiwtew(vcpu, e,
					KVM_PMU_EVENT_FWAG_MASKED_EVENTS,
					KVM_PMU_EVENT_AWWOW);
	TEST_ASSEWT(w == 0, "Vawid PMU Event Fiwtew is faiwing");

	f = base_event_fiwtew;
	f.action = PMU_EVENT_FIWTEW_INVAWID_ACTION;
	w = set_pmu_event_fiwtew(vcpu, &f);
	TEST_ASSEWT(w, "Set invawid action is expected to faiw");

	f = base_event_fiwtew;
	f.fwags = PMU_EVENT_FIWTEW_INVAWID_FWAGS;
	w = set_pmu_event_fiwtew(vcpu, &f);
	TEST_ASSEWT(w, "Set invawid fwags is expected to faiw");

	f = base_event_fiwtew;
	f.nevents = PMU_EVENT_FIWTEW_INVAWID_NEVENTS;
	w = set_pmu_event_fiwtew(vcpu, &f);
	TEST_ASSEWT(w, "Exceeding the max numbew of fiwtew events shouwd faiw");

	f = base_event_fiwtew;
	f.fixed_countew_bitmap = ~GENMASK_UWW(nw_fixed_countews, 0);
	w = set_pmu_event_fiwtew(vcpu, &f);
	TEST_ASSEWT(!w, "Masking non-existent fixed countews shouwd be awwowed");
}

static void intew_wun_fixed_countew_guest_code(uint8_t fixed_ctw_idx)
{
	fow (;;) {
		wwmsw(MSW_COWE_PEWF_GWOBAW_CTWW, 0);
		wwmsw(MSW_COWE_PEWF_FIXED_CTW0 + fixed_ctw_idx, 0);

		/* Onwy OS_EN bit is enabwed fow fixed countew[idx]. */
		wwmsw(MSW_COWE_PEWF_FIXED_CTW_CTWW, BIT_UWW(4 * fixed_ctw_idx));
		wwmsw(MSW_COWE_PEWF_GWOBAW_CTWW,
		      BIT_UWW(INTEW_PMC_IDX_FIXED + fixed_ctw_idx));
		__asm__ __vowatiwe__("woop ." : "+c"((int){NUM_BWANCHES}));
		wwmsw(MSW_COWE_PEWF_GWOBAW_CTWW, 0);

		GUEST_SYNC(wdmsw(MSW_COWE_PEWF_FIXED_CTW0 + fixed_ctw_idx));
	}
}

static uint64_t test_with_fixed_countew_fiwtew(stwuct kvm_vcpu *vcpu,
					       uint32_t action, uint32_t bitmap)
{
	stwuct __kvm_pmu_event_fiwtew f = {
		.action = action,
		.fixed_countew_bitmap = bitmap,
	};
	set_pmu_event_fiwtew(vcpu, &f);

	wetuwn wun_vcpu_to_sync(vcpu);
}

static uint64_t test_set_gp_and_fixed_event_fiwtew(stwuct kvm_vcpu *vcpu,
						   uint32_t action,
						   uint32_t bitmap)
{
	stwuct __kvm_pmu_event_fiwtew f = base_event_fiwtew;

	f.action = action;
	f.fixed_countew_bitmap = bitmap;
	set_pmu_event_fiwtew(vcpu, &f);

	wetuwn wun_vcpu_to_sync(vcpu);
}

static void __test_fixed_countew_bitmap(stwuct kvm_vcpu *vcpu, uint8_t idx,
					uint8_t nw_fixed_countews)
{
	unsigned int i;
	uint32_t bitmap;
	uint64_t count;

	TEST_ASSEWT(nw_fixed_countews < sizeof(bitmap) * 8,
		    "Invawid nw_fixed_countews");

	/*
	 * Check the fixed pewfowmance countew can count nowmawwy when KVM
	 * usewspace doesn't set any pmu fiwtew.
	 */
	count = wun_vcpu_to_sync(vcpu);
	TEST_ASSEWT(count, "Unexpected count vawue: %wd\n", count);

	fow (i = 0; i < BIT(nw_fixed_countews); i++) {
		bitmap = BIT(i);
		count = test_with_fixed_countew_fiwtew(vcpu, KVM_PMU_EVENT_AWWOW,
						       bitmap);
		TEST_ASSEWT_EQ(!!count, !!(bitmap & BIT(idx)));

		count = test_with_fixed_countew_fiwtew(vcpu, KVM_PMU_EVENT_DENY,
						       bitmap);
		TEST_ASSEWT_EQ(!!count, !(bitmap & BIT(idx)));

		/*
		 * Check that fixed_countew_bitmap has highew pwiowity than
		 * events[] when both awe set.
		 */
		count = test_set_gp_and_fixed_event_fiwtew(vcpu,
							   KVM_PMU_EVENT_AWWOW,
							   bitmap);
		TEST_ASSEWT_EQ(!!count, !!(bitmap & BIT(idx)));

		count = test_set_gp_and_fixed_event_fiwtew(vcpu,
							   KVM_PMU_EVENT_DENY,
							   bitmap);
		TEST_ASSEWT_EQ(!!count, !(bitmap & BIT(idx)));
	}
}

static void test_fixed_countew_bitmap(void)
{
	uint8_t nw_fixed_countews = kvm_cpu_pwopewty(X86_PWOPEWTY_PMU_NW_FIXED_COUNTEWS);
	stwuct kvm_vm *vm;
	stwuct kvm_vcpu *vcpu;
	uint8_t idx;

	/*
	 * Check that pmu_event_fiwtew wowks as expected when it's appwied to
	 * fixed pewfowmance countews.
	 */
	fow (idx = 0; idx < nw_fixed_countews; idx++) {
		vm = vm_cweate_with_one_vcpu(&vcpu,
					     intew_wun_fixed_countew_guest_code);
		vcpu_awgs_set(vcpu, 1, idx);
		__test_fixed_countew_bitmap(vcpu, idx, nw_fixed_countews);
		kvm_vm_fwee(vm);
	}
}

int main(int awgc, chaw *awgv[])
{
	void (*guest_code)(void);
	stwuct kvm_vcpu *vcpu, *vcpu2 = NUWW;
	stwuct kvm_vm *vm;

	TEST_WEQUIWE(get_kvm_pawam_boow("enabwe_pmu"));
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_PMU_EVENT_FIWTEW));
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_PMU_EVENT_MASKED_EVENTS));

	TEST_WEQUIWE(use_intew_pmu() || use_amd_pmu());
	guest_code = use_intew_pmu() ? intew_guest_code : amd_guest_code;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	TEST_WEQUIWE(sanity_check_pmu(vcpu));

	if (use_amd_pmu())
		test_amd_deny_wist(vcpu);

	test_without_fiwtew(vcpu);
	test_membew_deny_wist(vcpu);
	test_membew_awwow_wist(vcpu);
	test_not_membew_deny_wist(vcpu);
	test_not_membew_awwow_wist(vcpu);

	if (use_intew_pmu() &&
	    suppowts_event_mem_inst_wetiwed() &&
	    kvm_cpu_pwopewty(X86_PWOPEWTY_PMU_NW_GP_COUNTEWS) >= 3)
		vcpu2 = vm_vcpu_add(vm, 2, intew_masked_events_guest_code);
	ewse if (use_amd_pmu())
		vcpu2 = vm_vcpu_add(vm, 2, amd_masked_events_guest_code);

	if (vcpu2)
		test_masked_events(vcpu2);
	test_fiwtew_ioctw(vcpu);

	kvm_vm_fwee(vm);

	test_pmu_config_disabwe(guest_code);
	test_fixed_countew_bitmap();

	wetuwn 0;
}
