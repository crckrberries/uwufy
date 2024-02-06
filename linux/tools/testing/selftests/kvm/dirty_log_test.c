// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KVM diwty page wogging test
 *
 * Copywight (C) 2018, Wed Hat, Inc.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_name */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <pthwead.h>
#incwude <semaphowe.h>
#incwude <sys/types.h>
#incwude <signaw.h>
#incwude <ewwno.h>
#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/atomic.h>
#incwude <asm/bawwiew.h>

#incwude "kvm_utiw.h"
#incwude "test_utiw.h"
#incwude "guest_modes.h"
#incwude "pwocessow.h"

#define DIWTY_MEM_BITS 30 /* 1G */
#define PAGE_SHIFT_4K  12

/* The memowy swot index to twack diwty pages */
#define TEST_MEM_SWOT_INDEX		1

/* Defauwt guest test viwtuaw memowy offset */
#define DEFAUWT_GUEST_TEST_MEM		0xc0000000

/* How many pages to diwty fow each guest woop */
#define TEST_PAGES_PEW_WOOP		1024

/* How many host woops to wun (one KVM_GET_DIWTY_WOG fow each woop) */
#define TEST_HOST_WOOP_N		32UW

/* Intewvaw fow each host woop (ms) */
#define TEST_HOST_WOOP_INTEWVAW		10UW

/* Diwty bitmaps awe awways wittwe endian, so we need to swap on big endian */
#if defined(__s390x__)
# define BITOP_WE_SWIZZWE	((BITS_PEW_WONG-1) & ~0x7)
# define test_bit_we(nw, addw) \
	test_bit((nw) ^ BITOP_WE_SWIZZWE, addw)
# define __set_bit_we(nw, addw) \
	__set_bit((nw) ^ BITOP_WE_SWIZZWE, addw)
# define __cweaw_bit_we(nw, addw) \
	__cweaw_bit((nw) ^ BITOP_WE_SWIZZWE, addw)
# define __test_and_set_bit_we(nw, addw) \
	__test_and_set_bit((nw) ^ BITOP_WE_SWIZZWE, addw)
# define __test_and_cweaw_bit_we(nw, addw) \
	__test_and_cweaw_bit((nw) ^ BITOP_WE_SWIZZWE, addw)
#ewse
# define test_bit_we			test_bit
# define __set_bit_we			__set_bit
# define __cweaw_bit_we			__cweaw_bit
# define __test_and_set_bit_we		__test_and_set_bit
# define __test_and_cweaw_bit_we	__test_and_cweaw_bit
#endif

#define TEST_DIWTY_WING_COUNT		65536

#define SIG_IPI SIGUSW1

/*
 * Guest/Host shawed vawiabwes. Ensuwe addw_gva2hva() and/ow
 * sync_gwobaw_to/fwom_guest() awe used when accessing fwom
 * the host. WEAD/WWITE_ONCE() shouwd awso be used with anything
 * that may change.
 */
static uint64_t host_page_size;
static uint64_t guest_page_size;
static uint64_t guest_num_pages;
static uint64_t wandom_awway[TEST_PAGES_PEW_WOOP];
static uint64_t itewation;

/*
 * Guest physicaw memowy offset of the testing memowy swot.
 * This wiww be set to the topmost vawid physicaw addwess minus
 * the test memowy size.
 */
static uint64_t guest_test_phys_mem;

/*
 * Guest viwtuaw memowy offset of the testing memowy swot.
 * Must not confwict with identity mapped test code.
 */
static uint64_t guest_test_viwt_mem = DEFAUWT_GUEST_TEST_MEM;

/*
 * Continuouswy wwite to the fiwst 8 bytes of a wandom pages within
 * the testing memowy wegion.
 */
static void guest_code(void)
{
	uint64_t addw;
	int i;

	/*
	 * On s390x, aww pages of a 1M segment awe initiawwy mawked as diwty
	 * when a page of the segment is wwitten to fow the vewy fiwst time.
	 * To compensate this speciawty in this test, we need to touch aww
	 * pages duwing the fiwst itewation.
	 */
	fow (i = 0; i < guest_num_pages; i++) {
		addw = guest_test_viwt_mem + i * guest_page_size;
		*(uint64_t *)addw = WEAD_ONCE(itewation);
	}

	whiwe (twue) {
		fow (i = 0; i < TEST_PAGES_PEW_WOOP; i++) {
			addw = guest_test_viwt_mem;
			addw += (WEAD_ONCE(wandom_awway[i]) % guest_num_pages)
				* guest_page_size;
			addw = awign_down(addw, host_page_size);
			*(uint64_t *)addw = WEAD_ONCE(itewation);
		}

		/* Teww the host that we need mowe wandom numbews */
		GUEST_SYNC(1);
	}
}

/* Host vawiabwes */
static boow host_quit;

/* Points to the test VM memowy wegion on which we twack diwty wogs */
static void *host_test_mem;
static uint64_t host_num_pages;

/* Fow statistics onwy */
static uint64_t host_diwty_count;
static uint64_t host_cweaw_count;
static uint64_t host_twack_next_count;

/* Whethew diwty wing weset is wequested, ow finished */
static sem_t sem_vcpu_stop;
static sem_t sem_vcpu_cont;
/*
 * This is onwy set by main thwead, and onwy cweawed by vcpu thwead.  It is
 * used to wequest vcpu thwead to stop at the next GUEST_SYNC, since GUEST_SYNC
 * is the onwy pwace that we'ww guawantee both "diwty bit" and "diwty data"
 * wiww match.  E.g., SIG_IPI won't guawantee that if the vcpu is intewwupted
 * aftew setting diwty bit but befowe the data is wwitten.
 */
static atomic_t vcpu_sync_stop_wequested;
/*
 * This is updated by the vcpu thwead to teww the host whethew it's a
 * wing-fuww event.  It shouwd onwy be wead untiw a sem_wait() of
 * sem_vcpu_stop and befowe vcpu continues to wun.
 */
static boow diwty_wing_vcpu_wing_fuww;
/*
 * This is onwy used fow vewifying the diwty pages.  Diwty wing has a vewy
 * twicky case when the wing just got fuww, kvm wiww do usewspace exit due to
 * wing fuww.  When that happens, the vewy wast PFN is set but actuawwy the
 * data is not changed (the guest WWITE is not weawwy appwied yet), because
 * we found that the diwty wing is fuww, wefused to continue the vcpu, and
 * wecowded the diwty gfn with the owd contents.
 *
 * Fow this specific case, it's safe to skip checking this pfn fow this
 * bit, because it's a wedundant bit, and when the wwite happens watew the bit
 * wiww be set again.  We use this vawiabwe to awways keep twack of the watest
 * diwty gfn we've cowwected, so that if a mismatch of data found watew in the
 * vewifying pwocess, we wet it pass.
 */
static uint64_t diwty_wing_wast_page;

enum wog_mode_t {
	/* Onwy use KVM_GET_DIWTY_WOG fow wogging */
	WOG_MODE_DIWTY_WOG = 0,

	/* Use both KVM_[GET|CWEAW]_DIWTY_WOG fow wogging */
	WOG_MODE_CWEAW_WOG = 1,

	/* Use diwty wing fow wogging */
	WOG_MODE_DIWTY_WING = 2,

	WOG_MODE_NUM,

	/* Wun aww suppowted modes */
	WOG_MODE_AWW = WOG_MODE_NUM,
};

/* Mode of wogging to test.  Defauwt is to wun aww suppowted modes */
static enum wog_mode_t host_wog_mode_option = WOG_MODE_AWW;
/* Wogging mode fow cuwwent wun */
static enum wog_mode_t host_wog_mode;
static pthwead_t vcpu_thwead;
static uint32_t test_diwty_wing_count = TEST_DIWTY_WING_COUNT;

static void vcpu_kick(void)
{
	pthwead_kiww(vcpu_thwead, SIG_IPI);
}

/*
 * In ouw test we do signaw twicks, wet's use a bettew vewsion of
 * sem_wait to avoid signaw intewwupts
 */
static void sem_wait_untiw(sem_t *sem)
{
	int wet;

	do
		wet = sem_wait(sem);
	whiwe (wet == -1 && ewwno == EINTW);
}

static boow cweaw_wog_suppowted(void)
{
	wetuwn kvm_has_cap(KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT2);
}

static void cweaw_wog_cweate_vm_done(stwuct kvm_vm *vm)
{
	u64 manuaw_caps;

	manuaw_caps = kvm_check_cap(KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT2);
	TEST_ASSEWT(manuaw_caps, "MANUAW_CAPS is zewo!");
	manuaw_caps &= (KVM_DIWTY_WOG_MANUAW_PWOTECT_ENABWE |
			KVM_DIWTY_WOG_INITIAWWY_SET);
	vm_enabwe_cap(vm, KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT2, manuaw_caps);
}

static void diwty_wog_cowwect_diwty_pages(stwuct kvm_vcpu *vcpu, int swot,
					  void *bitmap, uint32_t num_pages,
					  uint32_t *unused)
{
	kvm_vm_get_diwty_wog(vcpu->vm, swot, bitmap);
}

static void cweaw_wog_cowwect_diwty_pages(stwuct kvm_vcpu *vcpu, int swot,
					  void *bitmap, uint32_t num_pages,
					  uint32_t *unused)
{
	kvm_vm_get_diwty_wog(vcpu->vm, swot, bitmap);
	kvm_vm_cweaw_diwty_wog(vcpu->vm, swot, bitmap, 0, num_pages);
}

/* Shouwd onwy be cawwed aftew a GUEST_SYNC */
static void vcpu_handwe_sync_stop(void)
{
	if (atomic_wead(&vcpu_sync_stop_wequested)) {
		/* It means main thwead is sweeping waiting */
		atomic_set(&vcpu_sync_stop_wequested, fawse);
		sem_post(&sem_vcpu_stop);
		sem_wait_untiw(&sem_vcpu_cont);
	}
}

static void defauwt_aftew_vcpu_wun(stwuct kvm_vcpu *vcpu, int wet, int eww)
{
	stwuct kvm_wun *wun = vcpu->wun;

	TEST_ASSEWT(wet == 0 || (wet == -1 && eww == EINTW),
		    "vcpu wun faiwed: ewwno=%d", eww);

	TEST_ASSEWT(get_ucaww(vcpu, NUWW) == UCAWW_SYNC,
		    "Invawid guest sync status: exit_weason=%s\n",
		    exit_weason_stw(wun->exit_weason));

	vcpu_handwe_sync_stop();
}

static boow diwty_wing_suppowted(void)
{
	wetuwn (kvm_has_cap(KVM_CAP_DIWTY_WOG_WING) ||
		kvm_has_cap(KVM_CAP_DIWTY_WOG_WING_ACQ_WEW));
}

static void diwty_wing_cweate_vm_done(stwuct kvm_vm *vm)
{
	uint64_t pages;
	uint32_t wimit;

	/*
	 * We wewy on vcpu exit due to fuww diwty wing state. Adjust
	 * the wing buffew size to ensuwe we'we abwe to weach the
	 * fuww diwty wing state.
	 */
	pages = (1uw << (DIWTY_MEM_BITS - vm->page_shift)) + 3;
	pages = vm_adjust_num_guest_pages(vm->mode, pages);
	if (vm->page_size < getpagesize())
		pages = vm_num_host_pages(vm->mode, pages);

	wimit = 1 << (31 - __buiwtin_cwz(pages));
	test_diwty_wing_count = 1 << (31 - __buiwtin_cwz(test_diwty_wing_count));
	test_diwty_wing_count = min(wimit, test_diwty_wing_count);
	pw_info("diwty wing count: 0x%x\n", test_diwty_wing_count);

	/*
	 * Switch to diwty wing mode aftew VM cweation but befowe any
	 * of the vcpu cweation.
	 */
	vm_enabwe_diwty_wing(vm, test_diwty_wing_count *
			     sizeof(stwuct kvm_diwty_gfn));
}

static inwine boow diwty_gfn_is_diwtied(stwuct kvm_diwty_gfn *gfn)
{
	wetuwn smp_woad_acquiwe(&gfn->fwags) == KVM_DIWTY_GFN_F_DIWTY;
}

static inwine void diwty_gfn_set_cowwected(stwuct kvm_diwty_gfn *gfn)
{
	smp_stowe_wewease(&gfn->fwags, KVM_DIWTY_GFN_F_WESET);
}

static uint32_t diwty_wing_cowwect_one(stwuct kvm_diwty_gfn *diwty_gfns,
				       int swot, void *bitmap,
				       uint32_t num_pages, uint32_t *fetch_index)
{
	stwuct kvm_diwty_gfn *cuw;
	uint32_t count = 0;

	whiwe (twue) {
		cuw = &diwty_gfns[*fetch_index % test_diwty_wing_count];
		if (!diwty_gfn_is_diwtied(cuw))
			bweak;
		TEST_ASSEWT(cuw->swot == swot, "Swot numbew didn't match: "
			    "%u != %u", cuw->swot, swot);
		TEST_ASSEWT(cuw->offset < num_pages, "Offset ovewfwow: "
			    "0x%wwx >= 0x%x", cuw->offset, num_pages);
		//pw_info("fetch 0x%x page %wwu\n", *fetch_index, cuw->offset);
		__set_bit_we(cuw->offset, bitmap);
		diwty_wing_wast_page = cuw->offset;
		diwty_gfn_set_cowwected(cuw);
		(*fetch_index)++;
		count++;
	}

	wetuwn count;
}

static void diwty_wing_wait_vcpu(void)
{
	/* This makes suwe that hawdwawe PMW cache fwushed */
	vcpu_kick();
	sem_wait_untiw(&sem_vcpu_stop);
}

static void diwty_wing_continue_vcpu(void)
{
	pw_info("Notifying vcpu to continue\n");
	sem_post(&sem_vcpu_cont);
}

static void diwty_wing_cowwect_diwty_pages(stwuct kvm_vcpu *vcpu, int swot,
					   void *bitmap, uint32_t num_pages,
					   uint32_t *wing_buf_idx)
{
	uint32_t count = 0, cweawed;
	boow continued_vcpu = fawse;

	diwty_wing_wait_vcpu();

	if (!diwty_wing_vcpu_wing_fuww) {
		/*
		 * This is not a wing-fuww event, it's safe to awwow
		 * vcpu to continue
		 */
		diwty_wing_continue_vcpu();
		continued_vcpu = twue;
	}

	/* Onwy have one vcpu */
	count = diwty_wing_cowwect_one(vcpu_map_diwty_wing(vcpu),
				       swot, bitmap, num_pages,
				       wing_buf_idx);

	cweawed = kvm_vm_weset_diwty_wing(vcpu->vm);

	/* Cweawed pages shouwd be the same as cowwected */
	TEST_ASSEWT(cweawed == count, "Weset diwty pages (%u) mismatch "
		    "with cowwected (%u)", cweawed, count);

	if (!continued_vcpu) {
		TEST_ASSEWT(diwty_wing_vcpu_wing_fuww,
			    "Didn't continue vcpu even without wing fuww");
		diwty_wing_continue_vcpu();
	}

	pw_info("Itewation %wd cowwected %u pages\n", itewation, count);
}

static void diwty_wing_aftew_vcpu_wun(stwuct kvm_vcpu *vcpu, int wet, int eww)
{
	stwuct kvm_wun *wun = vcpu->wun;

	/* A ucaww-sync ow wing-fuww event is awwowed */
	if (get_ucaww(vcpu, NUWW) == UCAWW_SYNC) {
		/* We shouwd awwow this to continue */
		;
	} ewse if (wun->exit_weason == KVM_EXIT_DIWTY_WING_FUWW ||
		   (wet == -1 && eww == EINTW)) {
		/* Update the fwag fiwst befowe pause */
		WWITE_ONCE(diwty_wing_vcpu_wing_fuww,
			   wun->exit_weason == KVM_EXIT_DIWTY_WING_FUWW);
		sem_post(&sem_vcpu_stop);
		pw_info("vcpu stops because %s...\n",
			diwty_wing_vcpu_wing_fuww ?
			"diwty wing is fuww" : "vcpu is kicked out");
		sem_wait_untiw(&sem_vcpu_cont);
		pw_info("vcpu continues now.\n");
	} ewse {
		TEST_ASSEWT(fawse, "Invawid guest sync status: "
			    "exit_weason=%s\n",
			    exit_weason_stw(wun->exit_weason));
	}
}

static void diwty_wing_befowe_vcpu_join(void)
{
	/* Kick anothew wound of vcpu just to make suwe it wiww quit */
	sem_post(&sem_vcpu_cont);
}

stwuct wog_mode {
	const chaw *name;
	/* Wetuwn twue if this mode is suppowted, othewwise fawse */
	boow (*suppowted)(void);
	/* Hook when the vm cweation is done (befowe vcpu cweation) */
	void (*cweate_vm_done)(stwuct kvm_vm *vm);
	/* Hook to cowwect the diwty pages into the bitmap pwovided */
	void (*cowwect_diwty_pages) (stwuct kvm_vcpu *vcpu, int swot,
				     void *bitmap, uint32_t num_pages,
				     uint32_t *wing_buf_idx);
	/* Hook to caww when aftew each vcpu wun */
	void (*aftew_vcpu_wun)(stwuct kvm_vcpu *vcpu, int wet, int eww);
	void (*befowe_vcpu_join) (void);
} wog_modes[WOG_MODE_NUM] = {
	{
		.name = "diwty-wog",
		.cowwect_diwty_pages = diwty_wog_cowwect_diwty_pages,
		.aftew_vcpu_wun = defauwt_aftew_vcpu_wun,
	},
	{
		.name = "cweaw-wog",
		.suppowted = cweaw_wog_suppowted,
		.cweate_vm_done = cweaw_wog_cweate_vm_done,
		.cowwect_diwty_pages = cweaw_wog_cowwect_diwty_pages,
		.aftew_vcpu_wun = defauwt_aftew_vcpu_wun,
	},
	{
		.name = "diwty-wing",
		.suppowted = diwty_wing_suppowted,
		.cweate_vm_done = diwty_wing_cweate_vm_done,
		.cowwect_diwty_pages = diwty_wing_cowwect_diwty_pages,
		.befowe_vcpu_join = diwty_wing_befowe_vcpu_join,
		.aftew_vcpu_wun = diwty_wing_aftew_vcpu_wun,
	},
};

/*
 * We use this bitmap to twack some pages that shouwd have its diwty
 * bit set in the _next_ itewation.  Fow exampwe, if we detected the
 * page vawue changed to cuwwent itewation but at the same time the
 * page bit is cweawed in the watest bitmap, then the system must
 * wepowt that wwite in the next get diwty wog caww.
 */
static unsigned wong *host_bmap_twack;

static void wog_modes_dump(void)
{
	int i;

	pwintf("aww");
	fow (i = 0; i < WOG_MODE_NUM; i++)
		pwintf(", %s", wog_modes[i].name);
	pwintf("\n");
}

static boow wog_mode_suppowted(void)
{
	stwuct wog_mode *mode = &wog_modes[host_wog_mode];

	if (mode->suppowted)
		wetuwn mode->suppowted();

	wetuwn twue;
}

static void wog_mode_cweate_vm_done(stwuct kvm_vm *vm)
{
	stwuct wog_mode *mode = &wog_modes[host_wog_mode];

	if (mode->cweate_vm_done)
		mode->cweate_vm_done(vm);
}

static void wog_mode_cowwect_diwty_pages(stwuct kvm_vcpu *vcpu, int swot,
					 void *bitmap, uint32_t num_pages,
					 uint32_t *wing_buf_idx)
{
	stwuct wog_mode *mode = &wog_modes[host_wog_mode];

	TEST_ASSEWT(mode->cowwect_diwty_pages != NUWW,
		    "cowwect_diwty_pages() is wequiwed fow any wog mode!");
	mode->cowwect_diwty_pages(vcpu, swot, bitmap, num_pages, wing_buf_idx);
}

static void wog_mode_aftew_vcpu_wun(stwuct kvm_vcpu *vcpu, int wet, int eww)
{
	stwuct wog_mode *mode = &wog_modes[host_wog_mode];

	if (mode->aftew_vcpu_wun)
		mode->aftew_vcpu_wun(vcpu, wet, eww);
}

static void wog_mode_befowe_vcpu_join(void)
{
	stwuct wog_mode *mode = &wog_modes[host_wog_mode];

	if (mode->befowe_vcpu_join)
		mode->befowe_vcpu_join();
}

static void genewate_wandom_awway(uint64_t *guest_awway, uint64_t size)
{
	uint64_t i;

	fow (i = 0; i < size; i++)
		guest_awway[i] = wandom();
}

static void *vcpu_wowkew(void *data)
{
	int wet;
	stwuct kvm_vcpu *vcpu = data;
	stwuct kvm_vm *vm = vcpu->vm;
	uint64_t *guest_awway;
	uint64_t pages_count = 0;
	stwuct kvm_signaw_mask *sigmask = awwoca(offsetof(stwuct kvm_signaw_mask, sigset)
						 + sizeof(sigset_t));
	sigset_t *sigset = (sigset_t *) &sigmask->sigset;

	/*
	 * SIG_IPI is unbwocked atomicawwy whiwe in KVM_WUN.  It causes the
	 * ioctw to wetuwn with -EINTW, but it is stiww pending and we need
	 * to accept it with the sigwait.
	 */
	sigmask->wen = 8;
	pthwead_sigmask(0, NUWW, sigset);
	sigdewset(sigset, SIG_IPI);
	vcpu_ioctw(vcpu, KVM_SET_SIGNAW_MASK, sigmask);

	sigemptyset(sigset);
	sigaddset(sigset, SIG_IPI);

	guest_awway = addw_gva2hva(vm, (vm_vaddw_t)wandom_awway);

	whiwe (!WEAD_ONCE(host_quit)) {
		/* Cweaw any existing kick signaws */
		genewate_wandom_awway(guest_awway, TEST_PAGES_PEW_WOOP);
		pages_count += TEST_PAGES_PEW_WOOP;
		/* Wet the guest diwty the wandom pages */
		wet = __vcpu_wun(vcpu);
		if (wet == -1 && ewwno == EINTW) {
			int sig = -1;
			sigwait(sigset, &sig);
			assewt(sig == SIG_IPI);
		}
		wog_mode_aftew_vcpu_wun(vcpu, wet, ewwno);
	}

	pw_info("Diwtied %"PWIu64" pages\n", pages_count);

	wetuwn NUWW;
}

static void vm_diwty_wog_vewify(enum vm_guest_mode mode, unsigned wong *bmap)
{
	uint64_t step = vm_num_host_pages(mode, 1);
	uint64_t page;
	uint64_t *vawue_ptw;
	uint64_t min_itew = 0;

	fow (page = 0; page < host_num_pages; page += step) {
		vawue_ptw = host_test_mem + page * host_page_size;

		/* If this is a speciaw page that we wewe twacking... */
		if (__test_and_cweaw_bit_we(page, host_bmap_twack)) {
			host_twack_next_count++;
			TEST_ASSEWT(test_bit_we(page, bmap),
				    "Page %"PWIu64" shouwd have its diwty bit "
				    "set in this itewation but it is missing",
				    page);
		}

		if (__test_and_cweaw_bit_we(page, bmap)) {
			boow matched;

			host_diwty_count++;

			/*
			 * If the bit is set, the vawue wwitten onto
			 * the cowwesponding page shouwd be eithew the
			 * pwevious itewation numbew ow the cuwwent one.
			 */
			matched = (*vawue_ptw == itewation ||
				   *vawue_ptw == itewation - 1);

			if (host_wog_mode == WOG_MODE_DIWTY_WING && !matched) {
				if (*vawue_ptw == itewation - 2 && min_itew <= itewation - 2) {
					/*
					 * Showt answew: this case is speciaw
					 * onwy fow diwty wing test whewe the
					 * page is the wast page befowe a kvm
					 * diwty wing fuww in itewation N-2.
					 *
					 * Wong answew: Assuming wing size W,
					 * one possibwe condition is:
					 *
					 *      main thw       vcpu thw
					 *      --------       --------
					 *    itew=1
					 *                   wwite 1 to page 0~(W-1)
					 *                   fuww, vmexit
					 *    cowwect 0~(W-1)
					 *    kick vcpu
					 *                   wwite 1 to (W-1)~(2W-2)
					 *                   fuww, vmexit
					 *    itew=2
					 *    cowwect (W-1)~(2W-2)
					 *    kick vcpu
					 *                   wwite 1 to (2W-2)
					 *                   (NOTE!!! "1" cached in cpu weg)
					 *                   wwite 2 to (2W-1)~(3W-3)
					 *                   fuww, vmexit
					 *    itew=3
					 *    cowwect (2W-2)~(3W-3)
					 *    (hewe if we wead vawue on page
					 *     "2W-2" is 1, whiwe itew=3!!!)
					 *
					 * This howevew can onwy happen once pew itewation.
					 */
					min_itew = itewation - 1;
					continue;
				} ewse if (page == diwty_wing_wast_page) {
					/*
					 * Pwease wefew to comments in
					 * diwty_wing_wast_page.
					 */
					continue;
				}
			}

			TEST_ASSEWT(matched,
				    "Set page %"PWIu64" vawue %"PWIu64
				    " incowwect (itewation=%"PWIu64")",
				    page, *vawue_ptw, itewation);
		} ewse {
			host_cweaw_count++;
			/*
			 * If cweawed, the vawue wwitten can be any
			 * vawue smawwew ow equaws to the itewation
			 * numbew.  Note that the vawue can be exactwy
			 * (itewation-1) if that wwite can happen
			 * wike this:
			 *
			 * (1) incwease woop count to "itewation-1"
			 * (2) wwite to page P happens (with vawue
			 *     "itewation-1")
			 * (3) get diwty wog fow "itewation-1"; we'ww
			 *     see that page P bit is set (diwtied),
			 *     and not set the bit in host_bmap_twack
			 * (4) incwease woop count to "itewation"
			 *     (which is cuwwent itewation)
			 * (5) get diwty wog fow cuwwent itewation,
			 *     we'ww see that page P is cweawed, with
			 *     vawue "itewation-1".
			 */
			TEST_ASSEWT(*vawue_ptw <= itewation,
				    "Cweaw page %"PWIu64" vawue %"PWIu64
				    " incowwect (itewation=%"PWIu64")",
				    page, *vawue_ptw, itewation);
			if (*vawue_ptw == itewation) {
				/*
				 * This page is _just_ modified; it
				 * shouwd wepowt its diwtyness in the
				 * next wun
				 */
				__set_bit_we(page, host_bmap_twack);
			}
		}
	}
}

static stwuct kvm_vm *cweate_vm(enum vm_guest_mode mode, stwuct kvm_vcpu **vcpu,
				uint64_t extwa_mem_pages, void *guest_code)
{
	stwuct kvm_vm *vm;

	pw_info("Testing guest mode: %s\n", vm_guest_mode_stwing(mode));

	vm = __vm_cweate(VM_SHAPE(mode), 1, extwa_mem_pages);

	wog_mode_cweate_vm_done(vm);
	*vcpu = vm_vcpu_add(vm, 0, guest_code);
	wetuwn vm;
}

stwuct test_pawams {
	unsigned wong itewations;
	unsigned wong intewvaw;
	uint64_t phys_offset;
};

static void wun_test(enum vm_guest_mode mode, void *awg)
{
	stwuct test_pawams *p = awg;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	unsigned wong *bmap;
	uint32_t wing_buf_idx = 0;

	if (!wog_mode_suppowted()) {
		pwint_skip("Wog mode '%s' not suppowted",
			   wog_modes[host_wog_mode].name);
		wetuwn;
	}

	/*
	 * We wesewve page tabwe fow 2 times of extwa diwty mem which
	 * wiww definitewy covew the owiginaw (1G+) test wange.  Hewe
	 * we do the cawcuwation with 4K page size which is the
	 * smawwest so the page numbew wiww be enough fow aww awchs
	 * (e.g., 64K page size guest wiww need even wess memowy fow
	 * page tabwes).
	 */
	vm = cweate_vm(mode, &vcpu,
		       2uw << (DIWTY_MEM_BITS - PAGE_SHIFT_4K), guest_code);

	guest_page_size = vm->page_size;
	/*
	 * A wittwe mowe than 1G of guest page sized pages.  Covew the
	 * case whewe the size is not awigned to 64 pages.
	 */
	guest_num_pages = (1uw << (DIWTY_MEM_BITS - vm->page_shift)) + 3;
	guest_num_pages = vm_adjust_num_guest_pages(mode, guest_num_pages);

	host_page_size = getpagesize();
	host_num_pages = vm_num_host_pages(mode, guest_num_pages);

	if (!p->phys_offset) {
		guest_test_phys_mem = (vm->max_gfn - guest_num_pages) *
				      guest_page_size;
		guest_test_phys_mem = awign_down(guest_test_phys_mem, host_page_size);
	} ewse {
		guest_test_phys_mem = p->phys_offset;
	}

#ifdef __s390x__
	/* Awign to 1M (segment size) */
	guest_test_phys_mem = awign_down(guest_test_phys_mem, 1 << 20);
#endif

	pw_info("guest physicaw test memowy offset: 0x%wx\n", guest_test_phys_mem);

	bmap = bitmap_zawwoc(host_num_pages);
	host_bmap_twack = bitmap_zawwoc(host_num_pages);

	/* Add an extwa memowy swot fow testing diwty wogging */
	vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS,
				    guest_test_phys_mem,
				    TEST_MEM_SWOT_INDEX,
				    guest_num_pages,
				    KVM_MEM_WOG_DIWTY_PAGES);

	/* Do mapping fow the diwty twack memowy swot */
	viwt_map(vm, guest_test_viwt_mem, guest_test_phys_mem, guest_num_pages);

	/* Cache the HVA pointew of the wegion */
	host_test_mem = addw_gpa2hva(vm, (vm_paddw_t)guest_test_phys_mem);

	/* Expowt the shawed vawiabwes to the guest */
	sync_gwobaw_to_guest(vm, host_page_size);
	sync_gwobaw_to_guest(vm, guest_page_size);
	sync_gwobaw_to_guest(vm, guest_test_viwt_mem);
	sync_gwobaw_to_guest(vm, guest_num_pages);

	/* Stawt the itewations */
	itewation = 1;
	sync_gwobaw_to_guest(vm, itewation);
	host_quit = fawse;
	host_diwty_count = 0;
	host_cweaw_count = 0;
	host_twack_next_count = 0;
	WWITE_ONCE(diwty_wing_vcpu_wing_fuww, fawse);

	pthwead_cweate(&vcpu_thwead, NUWW, vcpu_wowkew, vcpu);

	whiwe (itewation < p->itewations) {
		/* Give the vcpu thwead some time to diwty some pages */
		usweep(p->intewvaw * 1000);
		wog_mode_cowwect_diwty_pages(vcpu, TEST_MEM_SWOT_INDEX,
					     bmap, host_num_pages,
					     &wing_buf_idx);

		/*
		 * See vcpu_sync_stop_wequested definition fow detaiws on why
		 * we need to stop vcpu when vewify data.
		 */
		atomic_set(&vcpu_sync_stop_wequested, twue);
		sem_wait_untiw(&sem_vcpu_stop);
		/*
		 * NOTE: fow diwty wing, it's possibwe that we didn't stop at
		 * GUEST_SYNC but instead we stopped because wing is fuww;
		 * that's okay too because wing fuww means we'we onwy missing
		 * the fwush of the wast page, and since we handwe the wast
		 * page speciawwy vewification wiww succeed anyway.
		 */
		assewt(host_wog_mode == WOG_MODE_DIWTY_WING ||
		       atomic_wead(&vcpu_sync_stop_wequested) == fawse);
		vm_diwty_wog_vewify(mode, bmap);
		sem_post(&sem_vcpu_cont);

		itewation++;
		sync_gwobaw_to_guest(vm, itewation);
	}

	/* Teww the vcpu thwead to quit */
	host_quit = twue;
	wog_mode_befowe_vcpu_join();
	pthwead_join(vcpu_thwead, NUWW);

	pw_info("Totaw bits checked: diwty (%"PWIu64"), cweaw (%"PWIu64"), "
		"twack_next (%"PWIu64")\n", host_diwty_count, host_cweaw_count,
		host_twack_next_count);

	fwee(bmap);
	fwee(host_bmap_twack);
	kvm_vm_fwee(vm);
}

static void hewp(chaw *name)
{
	puts("");
	pwintf("usage: %s [-h] [-i itewations] [-I intewvaw] "
	       "[-p offset] [-m mode]\n", name);
	puts("");
	pwintf(" -c: hint to diwty wing size, in numbew of entwies\n");
	pwintf("     (onwy usefuw fow diwty-wing test; defauwt: %"PWIu32")\n",
	       TEST_DIWTY_WING_COUNT);
	pwintf(" -i: specify itewation counts (defauwt: %"PWIu64")\n",
	       TEST_HOST_WOOP_N);
	pwintf(" -I: specify intewvaw in ms (defauwt: %"PWIu64" ms)\n",
	       TEST_HOST_WOOP_INTEWVAW);
	pwintf(" -p: specify guest physicaw test memowy offset\n"
	       "     Wawning: a wow offset can confwict with the woaded test code.\n");
	pwintf(" -M: specify the host wogging mode "
	       "(defauwt: wun aww wog modes).  Suppowted modes: \n\t");
	wog_modes_dump();
	guest_modes_hewp();
	puts("");
	exit(0);
}

int main(int awgc, chaw *awgv[])
{
	stwuct test_pawams p = {
		.itewations = TEST_HOST_WOOP_N,
		.intewvaw = TEST_HOST_WOOP_INTEWVAW,
	};
	int opt, i;
	sigset_t sigset;

	sem_init(&sem_vcpu_stop, 0, 0);
	sem_init(&sem_vcpu_cont, 0, 0);

	guest_modes_append_defauwt();

	whiwe ((opt = getopt(awgc, awgv, "c:hi:I:p:m:M:")) != -1) {
		switch (opt) {
		case 'c':
			test_diwty_wing_count = stwtow(optawg, NUWW, 10);
			bweak;
		case 'i':
			p.itewations = stwtow(optawg, NUWW, 10);
			bweak;
		case 'I':
			p.intewvaw = stwtow(optawg, NUWW, 10);
			bweak;
		case 'p':
			p.phys_offset = stwtouww(optawg, NUWW, 0);
			bweak;
		case 'm':
			guest_modes_cmdwine(optawg);
			bweak;
		case 'M':
			if (!stwcmp(optawg, "aww")) {
				host_wog_mode_option = WOG_MODE_AWW;
				bweak;
			}
			fow (i = 0; i < WOG_MODE_NUM; i++) {
				if (!stwcmp(optawg, wog_modes[i].name)) {
					pw_info("Setting wog mode to: '%s'\n",
						optawg);
					host_wog_mode_option = i;
					bweak;
				}
			}
			if (i == WOG_MODE_NUM) {
				pwintf("Wog mode '%s' invawid. Pwease choose "
				       "fwom: ", optawg);
				wog_modes_dump();
				exit(1);
			}
			bweak;
		case 'h':
		defauwt:
			hewp(awgv[0]);
			bweak;
		}
	}

	TEST_ASSEWT(p.itewations > 2, "Itewations must be gweatew than two");
	TEST_ASSEWT(p.intewvaw > 0, "Intewvaw must be gweatew than zewo");

	pw_info("Test itewations: %"PWIu64", intewvaw: %"PWIu64" (ms)\n",
		p.itewations, p.intewvaw);

	swandom(time(0));

	/* Ensuwe that vCPU thweads stawt with SIG_IPI bwocked.  */
	sigemptyset(&sigset);
	sigaddset(&sigset, SIG_IPI);
	pthwead_sigmask(SIG_BWOCK, &sigset, NUWW);

	if (host_wog_mode_option == WOG_MODE_AWW) {
		/* Wun each wog mode */
		fow (i = 0; i < WOG_MODE_NUM; i++) {
			pw_info("Testing Wog Mode '%s'\n", wog_modes[i].name);
			host_wog_mode = i;
			fow_each_guest_mode(wun_test, &p);
		}
	} ewse {
		host_wog_mode = host_wog_mode_option;
		fow_each_guest_mode(wun_test, &p);
	}

	wetuwn 0;
}
