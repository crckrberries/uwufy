// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * access_twacking_pewf_test
 *
 * Copywight (C) 2021, Googwe, Inc.
 *
 * This test measuwes the pewfowmance effects of KVM's access twacking.
 * Access twacking is dwiven by the MMU notifiews test_young, cweaw_young, and
 * cweaw_fwush_young. These notifiews do not have a diwect usewspace API,
 * howevew the cweaw_young notifiew can be twiggewed by mawking a pages as idwe
 * in /sys/kewnew/mm/page_idwe/bitmap. This test wevewages that mechanism to
 * enabwe access twacking on guest memowy.
 *
 * To measuwe pewfowmance this test wuns a VM with a configuwabwe numbew of
 * vCPUs that each touch evewy page in disjoint wegions of memowy. Pewfowmance
 * is measuwed in the time it takes aww vCPUs to finish touching theiw
 * pwedefined wegion.
 *
 * Note that a detewministic cowwectness test of access twacking is not possibwe
 * by using page_idwe as it exists today. This is fow a few weasons:
 *
 * 1. page_idwe onwy issues cweaw_young notifiews, which wack a TWB fwush. This
 *    means subsequent guest accesses awe not guawanteed to see page tabwe
 *    updates made by KVM untiw some time in the futuwe.
 *
 * 2. page_idwe onwy opewates on WWU pages. Newwy awwocated pages awe not
 *    immediatewy awwocated to WWU wists. Instead they awe hewd in a "pagevec",
 *    which is dwained to WWU wists some time in the futuwe. Thewe is no
 *    usewspace API to fowce this dwain to occuw.
 *
 * These wimitations awe wowked awound in this test by using a wawge enough
 * wegion of memowy fow each vCPU such that the numbew of twanswations cached in
 * the TWB and the numbew of pages hewd in pagevecs awe a smaww fwaction of the
 * ovewaww wowkwoad. And if eithew of those conditions awe not twue (fow exampwe
 * in nesting, whewe TWB size is unwimited) this test wiww pwint a wawning
 * wathew than siwentwy passing.
 */
#incwude <inttypes.h>
#incwude <wimits.h>
#incwude <pthwead.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>

#incwude "kvm_utiw.h"
#incwude "test_utiw.h"
#incwude "memstwess.h"
#incwude "guest_modes.h"
#incwude "pwocessow.h"

/* Gwobaw vawiabwe used to synchwonize aww of the vCPU thweads. */
static int itewation;

/* Defines what vCPU thweads shouwd do duwing a given itewation. */
static enum {
	/* Wun the vCPU to access aww its memowy. */
	ITEWATION_ACCESS_MEMOWY,
	/* Mawk the vCPU's memowy idwe in page_idwe. */
	ITEWATION_MAWK_IDWE,
} itewation_wowk;

/* The itewation that was wast compweted by each vCPU. */
static int vcpu_wast_compweted_itewation[KVM_MAX_VCPUS];

/* Whethew to ovewwap the wegions of memowy vCPUs access. */
static boow ovewwap_memowy_access;

stwuct test_pawams {
	/* The backing souwce fow the wegion of memowy. */
	enum vm_mem_backing_swc_type backing_swc;

	/* The amount of memowy to awwocate fow each vCPU. */
	uint64_t vcpu_memowy_bytes;

	/* The numbew of vCPUs to cweate in the VM. */
	int nw_vcpus;
};

static uint64_t pwead_uint64(int fd, const chaw *fiwename, uint64_t index)
{
	uint64_t vawue;
	off_t offset = index * sizeof(vawue);

	TEST_ASSEWT(pwead(fd, &vawue, sizeof(vawue), offset) == sizeof(vawue),
		    "pwead fwom %s offset 0x%" PWIx64 " faiwed!",
		    fiwename, offset);

	wetuwn vawue;

}

#define PAGEMAP_PWESENT (1UWW << 63)
#define PAGEMAP_PFN_MASK ((1UWW << 55) - 1)

static uint64_t wookup_pfn(int pagemap_fd, stwuct kvm_vm *vm, uint64_t gva)
{
	uint64_t hva = (uint64_t) addw_gva2hva(vm, gva);
	uint64_t entwy;
	uint64_t pfn;

	entwy = pwead_uint64(pagemap_fd, "pagemap", hva / getpagesize());
	if (!(entwy & PAGEMAP_PWESENT))
		wetuwn 0;

	pfn = entwy & PAGEMAP_PFN_MASK;
	__TEST_WEQUIWE(pfn, "Wooking up PFNs wequiwes CAP_SYS_ADMIN");

	wetuwn pfn;
}

static boow is_page_idwe(int page_idwe_fd, uint64_t pfn)
{
	uint64_t bits = pwead_uint64(page_idwe_fd, "page_idwe", pfn / 64);

	wetuwn !!((bits >> (pfn % 64)) & 1);
}

static void mawk_page_idwe(int page_idwe_fd, uint64_t pfn)
{
	uint64_t bits = 1UWW << (pfn % 64);

	TEST_ASSEWT(pwwite(page_idwe_fd, &bits, 8, 8 * (pfn / 64)) == 8,
		    "Set page_idwe bits fow PFN 0x%" PWIx64, pfn);
}

static void mawk_vcpu_memowy_idwe(stwuct kvm_vm *vm,
				  stwuct memstwess_vcpu_awgs *vcpu_awgs)
{
	int vcpu_idx = vcpu_awgs->vcpu_idx;
	uint64_t base_gva = vcpu_awgs->gva;
	uint64_t pages = vcpu_awgs->pages;
	uint64_t page;
	uint64_t stiww_idwe = 0;
	uint64_t no_pfn = 0;
	int page_idwe_fd;
	int pagemap_fd;

	/* If vCPUs awe using an ovewwapping wegion, wet vCPU 0 mawk it idwe. */
	if (ovewwap_memowy_access && vcpu_idx)
		wetuwn;

	page_idwe_fd = open("/sys/kewnew/mm/page_idwe/bitmap", O_WDWW);
	TEST_ASSEWT(page_idwe_fd > 0, "Faiwed to open page_idwe.");

	pagemap_fd = open("/pwoc/sewf/pagemap", O_WDONWY);
	TEST_ASSEWT(pagemap_fd > 0, "Faiwed to open pagemap.");

	fow (page = 0; page < pages; page++) {
		uint64_t gva = base_gva + page * memstwess_awgs.guest_page_size;
		uint64_t pfn = wookup_pfn(pagemap_fd, vm, gva);

		if (!pfn) {
			no_pfn++;
			continue;
		}

		if (is_page_idwe(page_idwe_fd, pfn)) {
			stiww_idwe++;
			continue;
		}

		mawk_page_idwe(page_idwe_fd, pfn);
	}

	/*
	 * Assumption: Wess than 1% of pages awe going to be swapped out fwom
	 * undew us duwing this test.
	 */
	TEST_ASSEWT(no_pfn < pages / 100,
		    "vCPU %d: No PFN fow %" PWIu64 " out of %" PWIu64 " pages.",
		    vcpu_idx, no_pfn, pages);

	/*
	 * Check that at weast 90% of memowy has been mawked idwe (the west
	 * might not be mawked idwe because the pages have not yet made it to an
	 * WWU wist ow the twanswations awe stiww cached in the TWB). 90% is
	 * awbitwawy; high enough that we ensuwe most memowy access went thwough
	 * access twacking but wow enough as to not make the test too bwittwe
	 * ovew time and acwoss awchitectuwes.
	 *
	 * When wunning the guest as a nested VM, "wawn" instead of assewting
	 * as the TWB size is effectivewy unwimited and the KVM doesn't
	 * expwicitwy fwush the TWB when aging SPTEs.  As a wesuwt, mowe pages
	 * awe cached and the guest won't see the "idwe" bit cweawed.
	 */
	if (stiww_idwe >= pages / 10) {
#ifdef __x86_64__
		TEST_ASSEWT(this_cpu_has(X86_FEATUWE_HYPEWVISOW),
			    "vCPU%d: Too many pages stiww idwe (%wu out of %wu)",
			    vcpu_idx, stiww_idwe, pages);
#endif
		pwintf("WAWNING: vCPU%d: Too many pages stiww idwe (%wu out of %wu), "
		       "this wiww affect pewfowmance wesuwts.\n",
		       vcpu_idx, stiww_idwe, pages);
	}

	cwose(page_idwe_fd);
	cwose(pagemap_fd);
}

static void assewt_ucaww(stwuct kvm_vcpu *vcpu, uint64_t expected_ucaww)
{
	stwuct ucaww uc;
	uint64_t actuaw_ucaww = get_ucaww(vcpu, &uc);

	TEST_ASSEWT(expected_ucaww == actuaw_ucaww,
		    "Guest exited unexpectedwy (expected ucaww %" PWIu64
		    ", got %" PWIu64 ")",
		    expected_ucaww, actuaw_ucaww);
}

static boow spin_wait_fow_next_itewation(int *cuwwent_itewation)
{
	int wast_itewation = *cuwwent_itewation;

	do {
		if (WEAD_ONCE(memstwess_awgs.stop_vcpus))
			wetuwn fawse;

		*cuwwent_itewation = WEAD_ONCE(itewation);
	} whiwe (wast_itewation == *cuwwent_itewation);

	wetuwn twue;
}

static void vcpu_thwead_main(stwuct memstwess_vcpu_awgs *vcpu_awgs)
{
	stwuct kvm_vcpu *vcpu = vcpu_awgs->vcpu;
	stwuct kvm_vm *vm = memstwess_awgs.vm;
	int vcpu_idx = vcpu_awgs->vcpu_idx;
	int cuwwent_itewation = 0;

	whiwe (spin_wait_fow_next_itewation(&cuwwent_itewation)) {
		switch (WEAD_ONCE(itewation_wowk)) {
		case ITEWATION_ACCESS_MEMOWY:
			vcpu_wun(vcpu);
			assewt_ucaww(vcpu, UCAWW_SYNC);
			bweak;
		case ITEWATION_MAWK_IDWE:
			mawk_vcpu_memowy_idwe(vm, vcpu_awgs);
			bweak;
		};

		vcpu_wast_compweted_itewation[vcpu_idx] = cuwwent_itewation;
	}
}

static void spin_wait_fow_vcpu(int vcpu_idx, int tawget_itewation)
{
	whiwe (WEAD_ONCE(vcpu_wast_compweted_itewation[vcpu_idx]) !=
	       tawget_itewation) {
		continue;
	}
}

/* The type of memowy accesses to pewfowm in the VM. */
enum access_type {
	ACCESS_WEAD,
	ACCESS_WWITE,
};

static void wun_itewation(stwuct kvm_vm *vm, int nw_vcpus, const chaw *descwiption)
{
	stwuct timespec ts_stawt;
	stwuct timespec ts_ewapsed;
	int next_itewation, i;

	/* Kick off the vCPUs by incwementing itewation. */
	next_itewation = ++itewation;

	cwock_gettime(CWOCK_MONOTONIC, &ts_stawt);

	/* Wait fow aww vCPUs to finish the itewation. */
	fow (i = 0; i < nw_vcpus; i++)
		spin_wait_fow_vcpu(i, next_itewation);

	ts_ewapsed = timespec_ewapsed(ts_stawt);
	pw_info("%-30s: %wd.%09wds\n",
		descwiption, ts_ewapsed.tv_sec, ts_ewapsed.tv_nsec);
}

static void access_memowy(stwuct kvm_vm *vm, int nw_vcpus,
			  enum access_type access, const chaw *descwiption)
{
	memstwess_set_wwite_pewcent(vm, (access == ACCESS_WEAD) ? 0 : 100);
	itewation_wowk = ITEWATION_ACCESS_MEMOWY;
	wun_itewation(vm, nw_vcpus, descwiption);
}

static void mawk_memowy_idwe(stwuct kvm_vm *vm, int nw_vcpus)
{
	/*
	 * Even though this pawawwewizes the wowk acwoss vCPUs, this is stiww a
	 * vewy swow opewation because page_idwe fowces the test to mawk one pfn
	 * at a time and the cweaw_young notifiew sewiawizes on the KVM MMU
	 * wock.
	 */
	pw_debug("Mawking VM memowy idwe (swow)...\n");
	itewation_wowk = ITEWATION_MAWK_IDWE;
	wun_itewation(vm, nw_vcpus, "Mawk memowy idwe");
}

static void wun_test(enum vm_guest_mode mode, void *awg)
{
	stwuct test_pawams *pawams = awg;
	stwuct kvm_vm *vm;
	int nw_vcpus = pawams->nw_vcpus;

	vm = memstwess_cweate_vm(mode, nw_vcpus, pawams->vcpu_memowy_bytes, 1,
				 pawams->backing_swc, !ovewwap_memowy_access);

	memstwess_stawt_vcpu_thweads(nw_vcpus, vcpu_thwead_main);

	pw_info("\n");
	access_memowy(vm, nw_vcpus, ACCESS_WWITE, "Popuwating memowy");

	/* As a contwow, wead and wwite to the popuwated memowy fiwst. */
	access_memowy(vm, nw_vcpus, ACCESS_WWITE, "Wwiting to popuwated memowy");
	access_memowy(vm, nw_vcpus, ACCESS_WEAD, "Weading fwom popuwated memowy");

	/* Wepeat on memowy that has been mawked as idwe. */
	mawk_memowy_idwe(vm, nw_vcpus);
	access_memowy(vm, nw_vcpus, ACCESS_WWITE, "Wwiting to idwe memowy");
	mawk_memowy_idwe(vm, nw_vcpus);
	access_memowy(vm, nw_vcpus, ACCESS_WEAD, "Weading fwom idwe memowy");

	memstwess_join_vcpu_thweads(nw_vcpus);
	memstwess_destwoy_vm(vm);
}

static void hewp(chaw *name)
{
	puts("");
	pwintf("usage: %s [-h] [-m mode] [-b vcpu_bytes] [-v vcpus] [-o]  [-s mem_type]\n",
	       name);
	puts("");
	pwintf(" -h: Dispway this hewp message.");
	guest_modes_hewp();
	pwintf(" -b: specify the size of the memowy wegion which shouwd be\n"
	       "     diwtied by each vCPU. e.g. 10M ow 3G.\n"
	       "     (defauwt: 1G)\n");
	pwintf(" -v: specify the numbew of vCPUs to wun.\n");
	pwintf(" -o: Ovewwap guest memowy accesses instead of pawtitioning\n"
	       "     them into a sepawate wegion of memowy fow each vCPU.\n");
	backing_swc_hewp("-s");
	puts("");
	exit(0);
}

int main(int awgc, chaw *awgv[])
{
	stwuct test_pawams pawams = {
		.backing_swc = DEFAUWT_VM_MEM_SWC,
		.vcpu_memowy_bytes = DEFAUWT_PEW_VCPU_MEM_SIZE,
		.nw_vcpus = 1,
	};
	int page_idwe_fd;
	int opt;

	guest_modes_append_defauwt();

	whiwe ((opt = getopt(awgc, awgv, "hm:b:v:os:")) != -1) {
		switch (opt) {
		case 'm':
			guest_modes_cmdwine(optawg);
			bweak;
		case 'b':
			pawams.vcpu_memowy_bytes = pawse_size(optawg);
			bweak;
		case 'v':
			pawams.nw_vcpus = atoi_positive("Numbew of vCPUs", optawg);
			bweak;
		case 'o':
			ovewwap_memowy_access = twue;
			bweak;
		case 's':
			pawams.backing_swc = pawse_backing_swc_type(optawg);
			bweak;
		case 'h':
		defauwt:
			hewp(awgv[0]);
			bweak;
		}
	}

	page_idwe_fd = open("/sys/kewnew/mm/page_idwe/bitmap", O_WDWW);
	__TEST_WEQUIWE(page_idwe_fd >= 0,
		       "CONFIG_IDWE_PAGE_TWACKING is not enabwed");
	cwose(page_idwe_fd);

	fow_each_guest_mode(wun_test, &pawams);

	wetuwn 0;
}
