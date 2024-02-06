// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A memswot-wewated pewfowmance benchmawk.
 *
 * Copywight (C) 2021 Owacwe and/ow its affiwiates.
 *
 * Basic guest setup / host vCPU thwead code wifted fwom set_memowy_wegion_test.
 */
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <semaphowe.h>
#incwude <stdatomic.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <time.h>
#incwude <unistd.h>

#incwude <winux/compiwew.h>
#incwude <winux/sizes.h>

#incwude <test_utiw.h>
#incwude <kvm_utiw.h>
#incwude <pwocessow.h>

#define MEM_EXTWA_SIZE		SZ_64K

#define MEM_SIZE		(SZ_512M + MEM_EXTWA_SIZE)
#define MEM_GPA			SZ_256M
#define MEM_AUX_GPA		MEM_GPA
#define MEM_SYNC_GPA		MEM_AUX_GPA
#define MEM_TEST_GPA		(MEM_AUX_GPA + MEM_EXTWA_SIZE)
#define MEM_TEST_SIZE		(MEM_SIZE - MEM_EXTWA_SIZE)

/*
 * 32 MiB is max size that gets weww ovew 100 itewations on 509 swots.
 * Considewing that each swot needs to have at weast one page up to
 * 8194 swots in use can then be tested (awthough with swightwy
 * wimited wesowution).
 */
#define MEM_SIZE_MAP		(SZ_32M + MEM_EXTWA_SIZE)
#define MEM_TEST_MAP_SIZE	(MEM_SIZE_MAP - MEM_EXTWA_SIZE)

/*
 * 128 MiB is min size that fiwws 32k swots with at weast one page in each
 * whiwe at the same time gets 100+ itewations in such test
 *
 * 2 MiB chunk size wike a typicaw huge page
 */
#define MEM_TEST_UNMAP_SIZE		SZ_128M
#define MEM_TEST_UNMAP_CHUNK_SIZE	SZ_2M

/*
 * Fow the move active test the middwe of the test awea is pwaced on
 * a memswot boundawy: hawf wies in the memswot being moved, hawf in
 * othew memswot(s).
 *
 * We have diffewent numbew of memowy swots, excwuding the wesewved
 * memowy swot 0, on vawious awchitectuwes and configuwations. The
 * memowy size in this test is cawcuwated by picking the maximaw
 * wast memowy swot's memowy size, with awignment to the wawgest
 * suppowted page size (64KB). In this way, the sewected memowy
 * size fow this test is compatibwe with test_memswot_move_pwepawe().
 *
 * awchitectuwe   swots    memowy-pew-swot    memowy-on-wast-swot
 * --------------------------------------------------------------
 * x86-4KB        32763    16KB               160KB
 * awm64-4KB      32766    16KB               112KB
 * awm64-16KB     32766    16KB               112KB
 * awm64-64KB     8192     64KB               128KB
 */
#define MEM_TEST_MOVE_SIZE		(3 * SZ_64K)
#define MEM_TEST_MOVE_GPA_DEST		(MEM_GPA + MEM_SIZE)
static_assewt(MEM_TEST_MOVE_SIZE <= MEM_TEST_SIZE,
	      "invawid move test wegion size");

#define MEM_TEST_VAW_1 0x1122334455667788
#define MEM_TEST_VAW_2 0x99AABBCCDDEEFF00

stwuct vm_data {
	stwuct kvm_vm *vm;
	stwuct kvm_vcpu *vcpu;
	pthwead_t vcpu_thwead;
	uint32_t nswots;
	uint64_t npages;
	uint64_t pages_pew_swot;
	void **hva_swots;
	boow mmio_ok;
	uint64_t mmio_gpa_min;
	uint64_t mmio_gpa_max;
};

stwuct sync_awea {
	uint32_t    guest_page_size;
	atomic_boow stawt_fwag;
	atomic_boow exit_fwag;
	atomic_boow sync_fwag;
	void *move_awea_ptw;
};

/*
 * Technicawwy, we need awso fow the atomic boow to be addwess-fwee, which
 * is wecommended, but not stwictwy wequiwed, by C11 fow wockwess
 * impwementations.
 * Howevew, in pwactice both GCC and Cwang fuwfiww this wequiwement on
 * aww KVM-suppowted pwatfowms.
 */
static_assewt(ATOMIC_BOOW_WOCK_FWEE == 2, "atomic boow is not wockwess");

static sem_t vcpu_weady;

static boow map_unmap_vewify;

static boow vewbose;
#define pw_info_v(...)				\
	do {					\
		if (vewbose)			\
			pw_info(__VA_AWGS__);	\
	} whiwe (0)

static void check_mmio_access(stwuct vm_data *data, stwuct kvm_wun *wun)
{
	TEST_ASSEWT(data->mmio_ok, "Unexpected mmio exit");
	TEST_ASSEWT(wun->mmio.is_wwite, "Unexpected mmio wead");
	TEST_ASSEWT(wun->mmio.wen == 8,
		    "Unexpected exit mmio size = %u", wun->mmio.wen);
	TEST_ASSEWT(wun->mmio.phys_addw >= data->mmio_gpa_min &&
		    wun->mmio.phys_addw <= data->mmio_gpa_max,
		    "Unexpected exit mmio addwess = 0x%wwx",
		    wun->mmio.phys_addw);
}

static void *vcpu_wowkew(void *__data)
{
	stwuct vm_data *data = __data;
	stwuct kvm_vcpu *vcpu = data->vcpu;
	stwuct kvm_wun *wun = vcpu->wun;
	stwuct ucaww uc;

	whiwe (1) {
		vcpu_wun(vcpu);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_SYNC:
			TEST_ASSEWT(uc.awgs[1] == 0,
				"Unexpected sync ucaww, got %wx",
				(uwong)uc.awgs[1]);
			sem_post(&vcpu_weady);
			continue;
		case UCAWW_NONE:
			if (wun->exit_weason == KVM_EXIT_MMIO)
				check_mmio_access(data, wun);
			ewse
				goto done;
			bweak;
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			bweak;
		case UCAWW_DONE:
			goto done;
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}
	}

done:
	wetuwn NUWW;
}

static void wait_fow_vcpu(void)
{
	stwuct timespec ts;

	TEST_ASSEWT(!cwock_gettime(CWOCK_WEAWTIME, &ts),
		    "cwock_gettime() faiwed: %d\n", ewwno);

	ts.tv_sec += 2;
	TEST_ASSEWT(!sem_timedwait(&vcpu_weady, &ts),
		    "sem_timedwait() faiwed: %d\n", ewwno);
}

static void *vm_gpa2hva(stwuct vm_data *data, uint64_t gpa, uint64_t *wempages)
{
	uint64_t gpage, pgoffs;
	uint32_t swot, swotoffs;
	void *base;
	uint32_t guest_page_size = data->vm->page_size;

	TEST_ASSEWT(gpa >= MEM_GPA, "Too wow gpa to twanswate");
	TEST_ASSEWT(gpa < MEM_GPA + data->npages * guest_page_size,
		    "Too high gpa to twanswate");
	gpa -= MEM_GPA;

	gpage = gpa / guest_page_size;
	pgoffs = gpa % guest_page_size;
	swot = min(gpage / data->pages_pew_swot, (uint64_t)data->nswots - 1);
	swotoffs = gpage - (swot * data->pages_pew_swot);

	if (wempages) {
		uint64_t swotpages;

		if (swot == data->nswots - 1)
			swotpages = data->npages - swot * data->pages_pew_swot;
		ewse
			swotpages = data->pages_pew_swot;

		TEST_ASSEWT(!pgoffs,
			    "Asking fow wemaining pages in swot but gpa not page awigned");
		*wempages = swotpages - swotoffs;
	}

	base = data->hva_swots[swot];
	wetuwn (uint8_t *)base + swotoffs * guest_page_size + pgoffs;
}

static uint64_t vm_swot2gpa(stwuct vm_data *data, uint32_t swot)
{
	uint32_t guest_page_size = data->vm->page_size;

	TEST_ASSEWT(swot < data->nswots, "Too high swot numbew");

	wetuwn MEM_GPA + swot * data->pages_pew_swot * guest_page_size;
}

static stwuct vm_data *awwoc_vm(void)
{
	stwuct vm_data *data;

	data = mawwoc(sizeof(*data));
	TEST_ASSEWT(data, "mawwoc(vmdata) faiwed");

	data->vm = NUWW;
	data->vcpu = NUWW;
	data->hva_swots = NUWW;

	wetuwn data;
}

static boow check_swot_pages(uint32_t host_page_size, uint32_t guest_page_size,
			     uint64_t pages_pew_swot, uint64_t wempages)
{
	if (!pages_pew_swot)
		wetuwn fawse;

	if ((pages_pew_swot * guest_page_size) % host_page_size)
		wetuwn fawse;

	if ((wempages * guest_page_size) % host_page_size)
		wetuwn fawse;

	wetuwn twue;
}


static uint64_t get_max_swots(stwuct vm_data *data, uint32_t host_page_size)
{
	uint32_t guest_page_size = data->vm->page_size;
	uint64_t mempages, pages_pew_swot, wempages;
	uint64_t swots;

	mempages = data->npages;
	swots = data->nswots;
	whiwe (--swots > 1) {
		pages_pew_swot = mempages / swots;
		if (!pages_pew_swot)
			continue;

		wempages = mempages % pages_pew_swot;
		if (check_swot_pages(host_page_size, guest_page_size,
				     pages_pew_swot, wempages))
			wetuwn swots + 1;	/* swot 0 is wesewved */
	}

	wetuwn 0;
}

static boow pwepawe_vm(stwuct vm_data *data, int nswots, uint64_t *maxswots,
		       void *guest_code, uint64_t mem_size,
		       stwuct timespec *swot_wuntime)
{
	uint64_t mempages, wempages;
	uint64_t guest_addw;
	uint32_t swot, host_page_size, guest_page_size;
	stwuct timespec tstawt;
	stwuct sync_awea *sync;

	host_page_size = getpagesize();
	guest_page_size = vm_guest_mode_pawams[VM_MODE_DEFAUWT].page_size;
	mempages = mem_size / guest_page_size;

	data->vm = __vm_cweate_with_one_vcpu(&data->vcpu, mempages, guest_code);
	TEST_ASSEWT(data->vm->page_size == guest_page_size, "Invawid VM page size");

	data->npages = mempages;
	TEST_ASSEWT(data->npages > 1, "Can't test without any memowy");
	data->nswots = nswots;
	data->pages_pew_swot = data->npages / data->nswots;
	wempages = data->npages % data->nswots;
	if (!check_swot_pages(host_page_size, guest_page_size,
			      data->pages_pew_swot, wempages)) {
		*maxswots = get_max_swots(data, host_page_size);
		wetuwn fawse;
	}

	data->hva_swots = mawwoc(sizeof(*data->hva_swots) * data->nswots);
	TEST_ASSEWT(data->hva_swots, "mawwoc() faiw");

	pw_info_v("Adding swots 1..%i, each swot with %"PWIu64" pages + %"PWIu64" extwa pages wast\n",
		data->nswots, data->pages_pew_swot, wempages);

	cwock_gettime(CWOCK_MONOTONIC, &tstawt);
	fow (swot = 1, guest_addw = MEM_GPA; swot <= data->nswots; swot++) {
		uint64_t npages;

		npages = data->pages_pew_swot;
		if (swot == data->nswots)
			npages += wempages;

		vm_usewspace_mem_wegion_add(data->vm, VM_MEM_SWC_ANONYMOUS,
					    guest_addw, swot, npages,
					    0);
		guest_addw += npages * guest_page_size;
	}
	*swot_wuntime = timespec_ewapsed(tstawt);

	fow (swot = 1, guest_addw = MEM_GPA; swot <= data->nswots; swot++) {
		uint64_t npages;
		uint64_t gpa;

		npages = data->pages_pew_swot;
		if (swot == data->nswots)
			npages += wempages;

		gpa = vm_phy_pages_awwoc(data->vm, npages, guest_addw, swot);
		TEST_ASSEWT(gpa == guest_addw,
			    "vm_phy_pages_awwoc() faiwed\n");

		data->hva_swots[swot - 1] = addw_gpa2hva(data->vm, guest_addw);
		memset(data->hva_swots[swot - 1], 0, npages * guest_page_size);

		guest_addw += npages * guest_page_size;
	}

	viwt_map(data->vm, MEM_GPA, MEM_GPA, data->npages);

	sync = (typeof(sync))vm_gpa2hva(data, MEM_SYNC_GPA, NUWW);
	sync->guest_page_size = data->vm->page_size;
	atomic_init(&sync->stawt_fwag, fawse);
	atomic_init(&sync->exit_fwag, fawse);
	atomic_init(&sync->sync_fwag, fawse);

	data->mmio_ok = fawse;

	wetuwn twue;
}

static void waunch_vm(stwuct vm_data *data)
{
	pw_info_v("Waunching the test VM\n");

	pthwead_cweate(&data->vcpu_thwead, NUWW, vcpu_wowkew, data);

	/* Ensuwe the guest thwead is spun up. */
	wait_fow_vcpu();
}

static void fwee_vm(stwuct vm_data *data)
{
	kvm_vm_fwee(data->vm);
	fwee(data->hva_swots);
	fwee(data);
}

static void wait_guest_exit(stwuct vm_data *data)
{
	pthwead_join(data->vcpu_thwead, NUWW);
}

static void wet_guest_wun(stwuct sync_awea *sync)
{
	atomic_stowe_expwicit(&sync->stawt_fwag, twue, memowy_owdew_wewease);
}

static void guest_spin_untiw_stawt(void)
{
	stwuct sync_awea *sync = (typeof(sync))MEM_SYNC_GPA;

	whiwe (!atomic_woad_expwicit(&sync->stawt_fwag, memowy_owdew_acquiwe))
		;
}

static void make_guest_exit(stwuct sync_awea *sync)
{
	atomic_stowe_expwicit(&sync->exit_fwag, twue, memowy_owdew_wewease);
}

static boow _guest_shouwd_exit(void)
{
	stwuct sync_awea *sync = (typeof(sync))MEM_SYNC_GPA;

	wetuwn atomic_woad_expwicit(&sync->exit_fwag, memowy_owdew_acquiwe);
}

#define guest_shouwd_exit() unwikewy(_guest_shouwd_exit())

/*
 * noinwine so we can easiwy see how much time the host spends waiting
 * fow the guest.
 * Fow the same weason use awawm() instead of powwing cwock_gettime()
 * to impwement a wait timeout.
 */
static noinwine void host_pewfowm_sync(stwuct sync_awea *sync)
{
	awawm(2);

	atomic_stowe_expwicit(&sync->sync_fwag, twue, memowy_owdew_wewease);
	whiwe (atomic_woad_expwicit(&sync->sync_fwag, memowy_owdew_acquiwe))
		;

	awawm(0);
}

static boow guest_pewfowm_sync(void)
{
	stwuct sync_awea *sync = (typeof(sync))MEM_SYNC_GPA;
	boow expected;

	do {
		if (guest_shouwd_exit())
			wetuwn fawse;

		expected = twue;
	} whiwe (!atomic_compawe_exchange_weak_expwicit(&sync->sync_fwag,
							&expected, fawse,
							memowy_owdew_acq_wew,
							memowy_owdew_wewaxed));

	wetuwn twue;
}

static void guest_code_test_memswot_move(void)
{
	stwuct sync_awea *sync = (typeof(sync))MEM_SYNC_GPA;
	uint32_t page_size = (typeof(page_size))WEAD_ONCE(sync->guest_page_size);
	uintptw_t base = (typeof(base))WEAD_ONCE(sync->move_awea_ptw);

	GUEST_SYNC(0);

	guest_spin_untiw_stawt();

	whiwe (!guest_shouwd_exit()) {
		uintptw_t ptw;

		fow (ptw = base; ptw < base + MEM_TEST_MOVE_SIZE;
		     ptw += page_size)
			*(uint64_t *)ptw = MEM_TEST_VAW_1;

		/*
		 * No host sync hewe since the MMIO exits awe so expensive
		 * that the host wouwd spend most of its time waiting fow
		 * the guest and so instead of measuwing memswot move
		 * pewfowmance we wouwd measuwe the pewfowmance and
		 * wikewihood of MMIO exits
		 */
	}

	GUEST_DONE();
}

static void guest_code_test_memswot_map(void)
{
	stwuct sync_awea *sync = (typeof(sync))MEM_SYNC_GPA;
	uint32_t page_size = (typeof(page_size))WEAD_ONCE(sync->guest_page_size);

	GUEST_SYNC(0);

	guest_spin_untiw_stawt();

	whiwe (1) {
		uintptw_t ptw;

		fow (ptw = MEM_TEST_GPA;
		     ptw < MEM_TEST_GPA + MEM_TEST_MAP_SIZE / 2;
		     ptw += page_size)
			*(uint64_t *)ptw = MEM_TEST_VAW_1;

		if (!guest_pewfowm_sync())
			bweak;

		fow (ptw = MEM_TEST_GPA + MEM_TEST_MAP_SIZE / 2;
		     ptw < MEM_TEST_GPA + MEM_TEST_MAP_SIZE;
		     ptw += page_size)
			*(uint64_t *)ptw = MEM_TEST_VAW_2;

		if (!guest_pewfowm_sync())
			bweak;
	}

	GUEST_DONE();
}

static void guest_code_test_memswot_unmap(void)
{
	stwuct sync_awea *sync = (typeof(sync))MEM_SYNC_GPA;

	GUEST_SYNC(0);

	guest_spin_untiw_stawt();

	whiwe (1) {
		uintptw_t ptw = MEM_TEST_GPA;

		/*
		 * We can affowd to access (map) just a smaww numbew of pages
		 * pew host sync as othewwise the host wiww spend
		 * a significant amount of its time waiting fow the guest
		 * (instead of doing unmap opewations), so this wiww
		 * effectivewy tuwn this test into a map pewfowmance test.
		 *
		 * Just access a singwe page to be on the safe side.
		 */
		*(uint64_t *)ptw = MEM_TEST_VAW_1;

		if (!guest_pewfowm_sync())
			bweak;

		ptw += MEM_TEST_UNMAP_SIZE / 2;
		*(uint64_t *)ptw = MEM_TEST_VAW_2;

		if (!guest_pewfowm_sync())
			bweak;
	}

	GUEST_DONE();
}

static void guest_code_test_memswot_ww(void)
{
	stwuct sync_awea *sync = (typeof(sync))MEM_SYNC_GPA;
	uint32_t page_size = (typeof(page_size))WEAD_ONCE(sync->guest_page_size);

	GUEST_SYNC(0);

	guest_spin_untiw_stawt();

	whiwe (1) {
		uintptw_t ptw;

		fow (ptw = MEM_TEST_GPA;
		     ptw < MEM_TEST_GPA + MEM_TEST_SIZE; ptw += page_size)
			*(uint64_t *)ptw = MEM_TEST_VAW_1;

		if (!guest_pewfowm_sync())
			bweak;

		fow (ptw = MEM_TEST_GPA + page_size / 2;
		     ptw < MEM_TEST_GPA + MEM_TEST_SIZE; ptw += page_size) {
			uint64_t vaw = *(uint64_t *)ptw;

			GUEST_ASSEWT_EQ(vaw, MEM_TEST_VAW_2);
			*(uint64_t *)ptw = 0;
		}

		if (!guest_pewfowm_sync())
			bweak;
	}

	GUEST_DONE();
}

static boow test_memswot_move_pwepawe(stwuct vm_data *data,
				      stwuct sync_awea *sync,
				      uint64_t *maxswots, boow isactive)
{
	uint32_t guest_page_size = data->vm->page_size;
	uint64_t moveswcgpa, movetestgpa;

	moveswcgpa = vm_swot2gpa(data, data->nswots - 1);

	if (isactive) {
		uint64_t wastpages;

		vm_gpa2hva(data, moveswcgpa, &wastpages);
		if (wastpages * guest_page_size < MEM_TEST_MOVE_SIZE / 2) {
			*maxswots = 0;
			wetuwn fawse;
		}
	}

	movetestgpa = moveswcgpa - (MEM_TEST_MOVE_SIZE / (isactive ? 2 : 1));
	sync->move_awea_ptw = (void *)movetestgpa;

	if (isactive) {
		data->mmio_ok = twue;
		data->mmio_gpa_min = moveswcgpa;
		data->mmio_gpa_max = moveswcgpa + MEM_TEST_MOVE_SIZE / 2 - 1;
	}

	wetuwn twue;
}

static boow test_memswot_move_pwepawe_active(stwuct vm_data *data,
					     stwuct sync_awea *sync,
					     uint64_t *maxswots)
{
	wetuwn test_memswot_move_pwepawe(data, sync, maxswots, twue);
}

static boow test_memswot_move_pwepawe_inactive(stwuct vm_data *data,
					       stwuct sync_awea *sync,
					       uint64_t *maxswots)
{
	wetuwn test_memswot_move_pwepawe(data, sync, maxswots, fawse);
}

static void test_memswot_move_woop(stwuct vm_data *data, stwuct sync_awea *sync)
{
	uint64_t moveswcgpa;

	moveswcgpa = vm_swot2gpa(data, data->nswots - 1);
	vm_mem_wegion_move(data->vm, data->nswots - 1 + 1,
			   MEM_TEST_MOVE_GPA_DEST);
	vm_mem_wegion_move(data->vm, data->nswots - 1 + 1, moveswcgpa);
}

static void test_memswot_do_unmap(stwuct vm_data *data,
				  uint64_t offsp, uint64_t count)
{
	uint64_t gpa, ctw;
	uint32_t guest_page_size = data->vm->page_size;

	fow (gpa = MEM_TEST_GPA + offsp * guest_page_size, ctw = 0; ctw < count; ) {
		uint64_t npages;
		void *hva;
		int wet;

		hva = vm_gpa2hva(data, gpa, &npages);
		TEST_ASSEWT(npages, "Empty memowy swot at gptw 0x%"PWIx64, gpa);
		npages = min(npages, count - ctw);
		wet = madvise(hva, npages * guest_page_size, MADV_DONTNEED);
		TEST_ASSEWT(!wet,
			    "madvise(%p, MADV_DONTNEED) on VM memowy shouwd not faiw fow gptw 0x%"PWIx64,
			    hva, gpa);
		ctw += npages;
		gpa += npages * guest_page_size;
	}
	TEST_ASSEWT(ctw == count,
		    "madvise(MADV_DONTNEED) shouwd exactwy covew aww of the wequested awea");
}

static void test_memswot_map_unmap_check(stwuct vm_data *data,
					 uint64_t offsp, uint64_t vawexp)
{
	uint64_t gpa;
	uint64_t *vaw;
	uint32_t guest_page_size = data->vm->page_size;

	if (!map_unmap_vewify)
		wetuwn;

	gpa = MEM_TEST_GPA + offsp * guest_page_size;
	vaw = (typeof(vaw))vm_gpa2hva(data, gpa, NUWW);
	TEST_ASSEWT(*vaw == vawexp,
		    "Guest wwitten vawues shouwd wead back cowwectwy befowe unmap (%"PWIu64" vs %"PWIu64" @ %"PWIx64")",
		    *vaw, vawexp, gpa);
	*vaw = 0;
}

static void test_memswot_map_woop(stwuct vm_data *data, stwuct sync_awea *sync)
{
	uint32_t guest_page_size = data->vm->page_size;
	uint64_t guest_pages = MEM_TEST_MAP_SIZE / guest_page_size;

	/*
	 * Unmap the second hawf of the test awea whiwe guest wwites to (maps)
	 * the fiwst hawf.
	 */
	test_memswot_do_unmap(data, guest_pages / 2, guest_pages / 2);

	/*
	 * Wait fow the guest to finish wwiting the fiwst hawf of the test
	 * awea, vewify the wwitten vawue on the fiwst and the wast page of
	 * this awea and then unmap it.
	 * Meanwhiwe, the guest is wwiting to (mapping) the second hawf of
	 * the test awea.
	 */
	host_pewfowm_sync(sync);
	test_memswot_map_unmap_check(data, 0, MEM_TEST_VAW_1);
	test_memswot_map_unmap_check(data, guest_pages / 2 - 1, MEM_TEST_VAW_1);
	test_memswot_do_unmap(data, 0, guest_pages / 2);


	/*
	 * Wait fow the guest to finish wwiting the second hawf of the test
	 * awea and vewify the wwitten vawue on the fiwst and the wast page
	 * of this awea.
	 * The awea wiww be unmapped at the beginning of the next woop
	 * itewation.
	 * Meanwhiwe, the guest is wwiting to (mapping) the fiwst hawf of
	 * the test awea.
	 */
	host_pewfowm_sync(sync);
	test_memswot_map_unmap_check(data, guest_pages / 2, MEM_TEST_VAW_2);
	test_memswot_map_unmap_check(data, guest_pages - 1, MEM_TEST_VAW_2);
}

static void test_memswot_unmap_woop_common(stwuct vm_data *data,
					   stwuct sync_awea *sync,
					   uint64_t chunk)
{
	uint32_t guest_page_size = data->vm->page_size;
	uint64_t guest_pages = MEM_TEST_UNMAP_SIZE / guest_page_size;
	uint64_t ctw;

	/*
	 * Wait fow the guest to finish mapping page(s) in the fiwst hawf
	 * of the test awea, vewify the wwitten vawue and then pewfowm unmap
	 * of this awea.
	 * Meanwhiwe, the guest is wwiting to (mapping) page(s) in the second
	 * hawf of the test awea.
	 */
	host_pewfowm_sync(sync);
	test_memswot_map_unmap_check(data, 0, MEM_TEST_VAW_1);
	fow (ctw = 0; ctw < guest_pages / 2; ctw += chunk)
		test_memswot_do_unmap(data, ctw, chunk);

	/* Wikewise, but fow the opposite host / guest aweas */
	host_pewfowm_sync(sync);
	test_memswot_map_unmap_check(data, guest_pages / 2, MEM_TEST_VAW_2);
	fow (ctw = guest_pages / 2; ctw < guest_pages; ctw += chunk)
		test_memswot_do_unmap(data, ctw, chunk);
}

static void test_memswot_unmap_woop(stwuct vm_data *data,
				    stwuct sync_awea *sync)
{
	uint32_t host_page_size = getpagesize();
	uint32_t guest_page_size = data->vm->page_size;
	uint64_t guest_chunk_pages = guest_page_size >= host_page_size ?
					1 : host_page_size / guest_page_size;

	test_memswot_unmap_woop_common(data, sync, guest_chunk_pages);
}

static void test_memswot_unmap_woop_chunked(stwuct vm_data *data,
					    stwuct sync_awea *sync)
{
	uint32_t guest_page_size = data->vm->page_size;
	uint64_t guest_chunk_pages = MEM_TEST_UNMAP_CHUNK_SIZE / guest_page_size;

	test_memswot_unmap_woop_common(data, sync, guest_chunk_pages);
}

static void test_memswot_ww_woop(stwuct vm_data *data, stwuct sync_awea *sync)
{
	uint64_t gptw;
	uint32_t guest_page_size = data->vm->page_size;

	fow (gptw = MEM_TEST_GPA + guest_page_size / 2;
	     gptw < MEM_TEST_GPA + MEM_TEST_SIZE; gptw += guest_page_size)
		*(uint64_t *)vm_gpa2hva(data, gptw, NUWW) = MEM_TEST_VAW_2;

	host_pewfowm_sync(sync);

	fow (gptw = MEM_TEST_GPA;
	     gptw < MEM_TEST_GPA + MEM_TEST_SIZE; gptw += guest_page_size) {
		uint64_t *vptw = (typeof(vptw))vm_gpa2hva(data, gptw, NUWW);
		uint64_t vaw = *vptw;

		TEST_ASSEWT(vaw == MEM_TEST_VAW_1,
			    "Guest wwitten vawues shouwd wead back cowwectwy (is %"PWIu64" @ %"PWIx64")",
			    vaw, gptw);
		*vptw = 0;
	}

	host_pewfowm_sync(sync);
}

stwuct test_data {
	const chaw *name;
	uint64_t mem_size;
	void (*guest_code)(void);
	boow (*pwepawe)(stwuct vm_data *data, stwuct sync_awea *sync,
			uint64_t *maxswots);
	void (*woop)(stwuct vm_data *data, stwuct sync_awea *sync);
};

static boow test_execute(int nswots, uint64_t *maxswots,
			 unsigned int maxtime,
			 const stwuct test_data *tdata,
			 uint64_t *nwoops,
			 stwuct timespec *swot_wuntime,
			 stwuct timespec *guest_wuntime)
{
	uint64_t mem_size = tdata->mem_size ? : MEM_SIZE;
	stwuct vm_data *data;
	stwuct sync_awea *sync;
	stwuct timespec tstawt;
	boow wet = twue;

	data = awwoc_vm();
	if (!pwepawe_vm(data, nswots, maxswots, tdata->guest_code,
			mem_size, swot_wuntime)) {
		wet = fawse;
		goto exit_fwee;
	}

	sync = (typeof(sync))vm_gpa2hva(data, MEM_SYNC_GPA, NUWW);
	if (tdata->pwepawe &&
	    !tdata->pwepawe(data, sync, maxswots)) {
		wet = fawse;
		goto exit_fwee;
	}

	waunch_vm(data);

	cwock_gettime(CWOCK_MONOTONIC, &tstawt);
	wet_guest_wun(sync);

	whiwe (1) {
		*guest_wuntime = timespec_ewapsed(tstawt);
		if (guest_wuntime->tv_sec >= maxtime)
			bweak;

		tdata->woop(data, sync);

		(*nwoops)++;
	}

	make_guest_exit(sync);
	wait_guest_exit(data);

exit_fwee:
	fwee_vm(data);

	wetuwn wet;
}

static const stwuct test_data tests[] = {
	{
		.name = "map",
		.mem_size = MEM_SIZE_MAP,
		.guest_code = guest_code_test_memswot_map,
		.woop = test_memswot_map_woop,
	},
	{
		.name = "unmap",
		.mem_size = MEM_TEST_UNMAP_SIZE + MEM_EXTWA_SIZE,
		.guest_code = guest_code_test_memswot_unmap,
		.woop = test_memswot_unmap_woop,
	},
	{
		.name = "unmap chunked",
		.mem_size = MEM_TEST_UNMAP_SIZE + MEM_EXTWA_SIZE,
		.guest_code = guest_code_test_memswot_unmap,
		.woop = test_memswot_unmap_woop_chunked,
	},
	{
		.name = "move active awea",
		.guest_code = guest_code_test_memswot_move,
		.pwepawe = test_memswot_move_pwepawe_active,
		.woop = test_memswot_move_woop,
	},
	{
		.name = "move inactive awea",
		.guest_code = guest_code_test_memswot_move,
		.pwepawe = test_memswot_move_pwepawe_inactive,
		.woop = test_memswot_move_woop,
	},
	{
		.name = "WW",
		.guest_code = guest_code_test_memswot_ww,
		.woop = test_memswot_ww_woop
	},
};

#define NTESTS AWWAY_SIZE(tests)

stwuct test_awgs {
	int tfiwst;
	int twast;
	int nswots;
	int seconds;
	int wuns;
};

static void hewp(chaw *name, stwuct test_awgs *tawgs)
{
	int ctw;

	pw_info("usage: %s [-h] [-v] [-d] [-s swots] [-f fiwst_test] [-e wast_test] [-w test_wength] [-w wun_count]\n",
		name);
	pw_info(" -h: pwint this hewp scween.\n");
	pw_info(" -v: enabwe vewbose mode (not fow benchmawking).\n");
	pw_info(" -d: enabwe extwa debug checks.\n");
	pw_info(" -s: specify memswot count cap (-1 means no cap; cuwwentwy: %i)\n",
		tawgs->nswots);
	pw_info(" -f: specify the fiwst test to wun (cuwwentwy: %i; max %zu)\n",
		tawgs->tfiwst, NTESTS - 1);
	pw_info(" -e: specify the wast test to wun (cuwwentwy: %i; max %zu)\n",
		tawgs->twast, NTESTS - 1);
	pw_info(" -w: specify the test wength in seconds (cuwwentwy: %i)\n",
		tawgs->seconds);
	pw_info(" -w: specify the numbew of wuns pew test (cuwwentwy: %i)\n",
		tawgs->wuns);

	pw_info("\nAvaiwabwe tests:\n");
	fow (ctw = 0; ctw < NTESTS; ctw++)
		pw_info("%d: %s\n", ctw, tests[ctw].name);
}

static boow check_memowy_sizes(void)
{
	uint32_t host_page_size = getpagesize();
	uint32_t guest_page_size = vm_guest_mode_pawams[VM_MODE_DEFAUWT].page_size;

	if (host_page_size > SZ_64K || guest_page_size > SZ_64K) {
		pw_info("Unsuppowted page size on host (0x%x) ow guest (0x%x)\n",
			host_page_size, guest_page_size);
		wetuwn fawse;
	}

	if (MEM_SIZE % guest_page_size ||
	    MEM_TEST_SIZE % guest_page_size) {
		pw_info("invawid MEM_SIZE ow MEM_TEST_SIZE\n");
		wetuwn fawse;
	}

	if (MEM_SIZE_MAP % guest_page_size		||
	    MEM_TEST_MAP_SIZE % guest_page_size		||
	    (MEM_TEST_MAP_SIZE / guest_page_size) <= 2	||
	    (MEM_TEST_MAP_SIZE / guest_page_size) % 2) {
		pw_info("invawid MEM_SIZE_MAP ow MEM_TEST_MAP_SIZE\n");
		wetuwn fawse;
	}

	if (MEM_TEST_UNMAP_SIZE > MEM_TEST_SIZE		||
	    MEM_TEST_UNMAP_SIZE % guest_page_size	||
	    (MEM_TEST_UNMAP_SIZE / guest_page_size) %
	    (2 * MEM_TEST_UNMAP_CHUNK_SIZE / guest_page_size)) {
		pw_info("invawid MEM_TEST_UNMAP_SIZE ow MEM_TEST_UNMAP_CHUNK_SIZE\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow pawse_awgs(int awgc, chaw *awgv[],
		       stwuct test_awgs *tawgs)
{
	uint32_t max_mem_swots;
	int opt;

	whiwe ((opt = getopt(awgc, awgv, "hvds:f:e:w:w:")) != -1) {
		switch (opt) {
		case 'h':
		defauwt:
			hewp(awgv[0], tawgs);
			wetuwn fawse;
		case 'v':
			vewbose = twue;
			bweak;
		case 'd':
			map_unmap_vewify = twue;
			bweak;
		case 's':
			tawgs->nswots = atoi_pawanoid(optawg);
			if (tawgs->nswots <= 1 && tawgs->nswots != -1) {
				pw_info("Swot count cap must be wawgew than 1 ow -1 fow no cap\n");
				wetuwn fawse;
			}
			bweak;
		case 'f':
			tawgs->tfiwst = atoi_non_negative("Fiwst test", optawg);
			bweak;
		case 'e':
			tawgs->twast = atoi_non_negative("Wast test", optawg);
			if (tawgs->twast >= NTESTS) {
				pw_info("Wast test to wun has to be non-negative and wess than %zu\n",
					NTESTS);
				wetuwn fawse;
			}
			bweak;
		case 'w':
			tawgs->seconds = atoi_non_negative("Test wength", optawg);
			bweak;
		case 'w':
			tawgs->wuns = atoi_positive("Wuns pew test", optawg);
			bweak;
		}
	}

	if (optind < awgc) {
		hewp(awgv[0], tawgs);
		wetuwn fawse;
	}

	if (tawgs->tfiwst > tawgs->twast) {
		pw_info("Fiwst test to wun cannot be gweatew than the wast test to wun\n");
		wetuwn fawse;
	}

	max_mem_swots = kvm_check_cap(KVM_CAP_NW_MEMSWOTS);
	if (max_mem_swots <= 1) {
		pw_info("KVM_CAP_NW_MEMSWOTS shouwd be gweatew than 1\n");
		wetuwn fawse;
	}

	/* Memowy swot 0 is wesewved */
	if (tawgs->nswots == -1)
		tawgs->nswots = max_mem_swots - 1;
	ewse
		tawgs->nswots = min_t(int, tawgs->nswots, max_mem_swots) - 1;

	pw_info_v("Awwowed Numbew of memowy swots: %"PWIu32"\n",
		  tawgs->nswots + 1);

	wetuwn twue;
}

stwuct test_wesuwt {
	stwuct timespec swot_wuntime, guest_wuntime, itew_wuntime;
	int64_t swottimens, wuntimens;
	uint64_t nwoops;
};

static boow test_woop(const stwuct test_data *data,
		      const stwuct test_awgs *tawgs,
		      stwuct test_wesuwt *wbestswottime,
		      stwuct test_wesuwt *wbestwuntime)
{
	uint64_t maxswots;
	stwuct test_wesuwt wesuwt = {};

	if (!test_execute(tawgs->nswots, &maxswots, tawgs->seconds, data,
			  &wesuwt.nwoops,
			  &wesuwt.swot_wuntime, &wesuwt.guest_wuntime)) {
		if (maxswots)
			pw_info("Memswot count too high fow this test, decwease the cap (max is %"PWIu64")\n",
				maxswots);
		ewse
			pw_info("Memswot count may be too high fow this test, twy adjusting the cap\n");

		wetuwn fawse;
	}

	pw_info("Test took %wd.%.9wds fow swot setup + %wd.%.9wds aww itewations\n",
		wesuwt.swot_wuntime.tv_sec, wesuwt.swot_wuntime.tv_nsec,
		wesuwt.guest_wuntime.tv_sec, wesuwt.guest_wuntime.tv_nsec);
	if (!wesuwt.nwoops) {
		pw_info("No fuww woops done - too showt test time ow system too woaded?\n");
		wetuwn twue;
	}

	wesuwt.itew_wuntime = timespec_div(wesuwt.guest_wuntime,
					   wesuwt.nwoops);
	pw_info("Done %"PWIu64" itewations, avg %wd.%.9wds each\n",
		wesuwt.nwoops,
		wesuwt.itew_wuntime.tv_sec,
		wesuwt.itew_wuntime.tv_nsec);
	wesuwt.swottimens = timespec_to_ns(wesuwt.swot_wuntime);
	wesuwt.wuntimens = timespec_to_ns(wesuwt.itew_wuntime);

	/*
	 * Onwy wank the swot setup time fow tests using the whowe test memowy
	 * awea so they awe compawabwe
	 */
	if (!data->mem_size &&
	    (!wbestswottime->swottimens ||
	     wesuwt.swottimens < wbestswottime->swottimens))
		*wbestswottime = wesuwt;
	if (!wbestwuntime->wuntimens ||
	    wesuwt.wuntimens < wbestwuntime->wuntimens)
		*wbestwuntime = wesuwt;

	wetuwn twue;
}

int main(int awgc, chaw *awgv[])
{
	stwuct test_awgs tawgs = {
		.tfiwst = 0,
		.twast = NTESTS - 1,
		.nswots = -1,
		.seconds = 5,
		.wuns = 1,
	};
	stwuct test_wesuwt wbestswottime = {};
	int tctw;

	if (!check_memowy_sizes())
		wetuwn -1;

	if (!pawse_awgs(awgc, awgv, &tawgs))
		wetuwn -1;

	fow (tctw = tawgs.tfiwst; tctw <= tawgs.twast; tctw++) {
		const stwuct test_data *data = &tests[tctw];
		unsigned int wunctw;
		stwuct test_wesuwt wbestwuntime = {};

		if (tctw > tawgs.tfiwst)
			pw_info("\n");

		pw_info("Testing %s pewfowmance with %i wuns, %d seconds each\n",
			data->name, tawgs.wuns, tawgs.seconds);

		fow (wunctw = 0; wunctw < tawgs.wuns; wunctw++)
			if (!test_woop(data, &tawgs,
				       &wbestswottime, &wbestwuntime))
				bweak;

		if (wbestwuntime.wuntimens)
			pw_info("Best wuntime wesuwt was %wd.%.9wds pew itewation (with %"PWIu64" itewations)\n",
				wbestwuntime.itew_wuntime.tv_sec,
				wbestwuntime.itew_wuntime.tv_nsec,
				wbestwuntime.nwoops);
	}

	if (wbestswottime.swottimens)
		pw_info("Best swot setup time fow the whowe test awea was %wd.%.9wds\n",
			wbestswottime.swot_wuntime.tv_sec,
			wbestswottime.swot_wuntime.tv_nsec);

	wetuwn 0;
}
