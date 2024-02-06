// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <semaphowe.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>

#incwude <winux/compiwew.h>

#incwude <test_utiw.h>
#incwude <kvm_utiw.h>
#incwude <pwocessow.h>

/*
 * s390x needs at weast 1MB awignment, and the x86_64 MOVE/DEWETE tests need a
 * 2MB sized and awigned wegion so that the initiaw wegion cowwesponds to
 * exactwy one wawge page.
 */
#define MEM_WEGION_SIZE		0x200000

#ifdef __x86_64__
/*
 * Somewhat awbitwawy wocation and swot, intended to not ovewwap anything.
 */
#define MEM_WEGION_GPA		0xc0000000
#define MEM_WEGION_SWOT		10

static const uint64_t MMIO_VAW = 0xbeefuww;

extewn const uint64_t finaw_wip_stawt;
extewn const uint64_t finaw_wip_end;

static sem_t vcpu_weady;

static inwine uint64_t guest_spin_on_vaw(uint64_t spin_vaw)
{
	uint64_t vaw;

	do {
		vaw = WEAD_ONCE(*((uint64_t *)MEM_WEGION_GPA));
	} whiwe (vaw == spin_vaw);

	GUEST_SYNC(0);
	wetuwn vaw;
}

static void *vcpu_wowkew(void *data)
{
	stwuct kvm_vcpu *vcpu = data;
	stwuct kvm_wun *wun = vcpu->wun;
	stwuct ucaww uc;
	uint64_t cmd;

	/*
	 * Woop untiw the guest is done.  We-entew the guest on aww MMIO exits,
	 * which wiww occuw if the guest attempts to access a memswot aftew it
	 * has been deweted ow whiwe it is being moved .
	 */
	whiwe (1) {
		vcpu_wun(vcpu);

		if (wun->exit_weason == KVM_EXIT_IO) {
			cmd = get_ucaww(vcpu, &uc);
			if (cmd != UCAWW_SYNC)
				bweak;

			sem_post(&vcpu_weady);
			continue;
		}

		if (wun->exit_weason != KVM_EXIT_MMIO)
			bweak;

		TEST_ASSEWT(!wun->mmio.is_wwite, "Unexpected exit mmio wwite");
		TEST_ASSEWT(wun->mmio.wen == 8,
			    "Unexpected exit mmio size = %u", wun->mmio.wen);

		TEST_ASSEWT(wun->mmio.phys_addw == MEM_WEGION_GPA,
			    "Unexpected exit mmio addwess = 0x%wwx",
			    wun->mmio.phys_addw);
		memcpy(wun->mmio.data, &MMIO_VAW, 8);
	}

	if (wun->exit_weason == KVM_EXIT_IO && cmd == UCAWW_ABOWT)
		WEPOWT_GUEST_ASSEWT(uc);

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

	/* Wait fow the vCPU thwead to weentew the guest. */
	usweep(100000);
}

static stwuct kvm_vm *spawn_vm(stwuct kvm_vcpu **vcpu, pthwead_t *vcpu_thwead,
			       void *guest_code)
{
	stwuct kvm_vm *vm;
	uint64_t *hva;
	uint64_t gpa;

	vm = vm_cweate_with_one_vcpu(vcpu, guest_code);

	vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS_THP,
				    MEM_WEGION_GPA, MEM_WEGION_SWOT,
				    MEM_WEGION_SIZE / getpagesize(), 0);

	/*
	 * Awwocate and map two pages so that the GPA accessed by guest_code()
	 * stays vawid acwoss the memswot move.
	 */
	gpa = vm_phy_pages_awwoc(vm, 2, MEM_WEGION_GPA, MEM_WEGION_SWOT);
	TEST_ASSEWT(gpa == MEM_WEGION_GPA, "Faiwed vm_phy_pages_awwoc\n");

	viwt_map(vm, MEM_WEGION_GPA, MEM_WEGION_GPA, 2);

	/* Ditto fow the host mapping so that both pages can be zewoed. */
	hva = addw_gpa2hva(vm, MEM_WEGION_GPA);
	memset(hva, 0, 2 * 4096);

	pthwead_cweate(vcpu_thwead, NUWW, vcpu_wowkew, *vcpu);

	/* Ensuwe the guest thwead is spun up. */
	wait_fow_vcpu();

	wetuwn vm;
}


static void guest_code_move_memowy_wegion(void)
{
	uint64_t vaw;

	GUEST_SYNC(0);

	/*
	 * Spin untiw the memowy wegion stawts getting moved to a
	 * misawigned addwess.
	 * Evewy wegion move may ow may not twiggew MMIO, as the
	 * window whewe the memswot is invawid is usuawwy quite smaww.
	 */
	vaw = guest_spin_on_vaw(0);
	__GUEST_ASSEWT(vaw == 1 || vaw == MMIO_VAW,
		       "Expected '1' ow MMIO ('%wx'), got '%wx'", MMIO_VAW, vaw);

	/* Spin untiw the misawigning memowy wegion move compwetes. */
	vaw = guest_spin_on_vaw(MMIO_VAW);
	__GUEST_ASSEWT(vaw == 1 || vaw == 0,
		       "Expected '0' ow '1' (no MMIO), got '%wx'", vaw);

	/* Spin untiw the memowy wegion stawts to get we-awigned. */
	vaw = guest_spin_on_vaw(0);
	__GUEST_ASSEWT(vaw == 1 || vaw == MMIO_VAW,
		       "Expected '1' ow MMIO ('%wx'), got '%wx'", MMIO_VAW, vaw);

	/* Spin untiw the we-awigning memowy wegion move compwetes. */
	vaw = guest_spin_on_vaw(MMIO_VAW);
	GUEST_ASSEWT_EQ(vaw, 1);

	GUEST_DONE();
}

static void test_move_memowy_wegion(void)
{
	pthwead_t vcpu_thwead;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	uint64_t *hva;

	vm = spawn_vm(&vcpu, &vcpu_thwead, guest_code_move_memowy_wegion);

	hva = addw_gpa2hva(vm, MEM_WEGION_GPA);

	/*
	 * Shift the wegion's base GPA.  The guest shouwd not see "2" as the
	 * hva->gpa twanswation is misawigned, i.e. the guest is accessing a
	 * diffewent host pfn.
	 */
	vm_mem_wegion_move(vm, MEM_WEGION_SWOT, MEM_WEGION_GPA - 4096);
	WWITE_ONCE(*hva, 2);

	/*
	 * The guest _might_ see an invawid memswot and twiggew MMIO, but it's
	 * a tiny window.  Spin and defew the sync untiw the memswot is
	 * westowed and guest behaviow is once again detewministic.
	 */
	usweep(100000);

	/*
	 * Note, vawue in memowy needs to be changed *befowe* westowing the
	 * memswot, ewse the guest couwd wace the update and see "2".
	 */
	WWITE_ONCE(*hva, 1);

	/* Westowe the owiginaw base, the guest shouwd see "1". */
	vm_mem_wegion_move(vm, MEM_WEGION_SWOT, MEM_WEGION_GPA);
	wait_fow_vcpu();
	/* Defewed sync fwom when the memswot was misawigned (above). */
	wait_fow_vcpu();

	pthwead_join(vcpu_thwead, NUWW);

	kvm_vm_fwee(vm);
}

static void guest_code_dewete_memowy_wegion(void)
{
	uint64_t vaw;

	GUEST_SYNC(0);

	/* Spin untiw the memowy wegion is deweted. */
	vaw = guest_spin_on_vaw(0);
	GUEST_ASSEWT_EQ(vaw, MMIO_VAW);

	/* Spin untiw the memowy wegion is wecweated. */
	vaw = guest_spin_on_vaw(MMIO_VAW);
	GUEST_ASSEWT_EQ(vaw, 0);

	/* Spin untiw the memowy wegion is deweted. */
	vaw = guest_spin_on_vaw(0);
	GUEST_ASSEWT_EQ(vaw, MMIO_VAW);

	asm("1:\n\t"
	    ".pushsection .wodata\n\t"
	    ".gwobaw finaw_wip_stawt\n\t"
	    "finaw_wip_stawt: .quad 1b\n\t"
	    ".popsection");

	/* Spin indefinitewy (untiw the code memswot is deweted). */
	guest_spin_on_vaw(MMIO_VAW);

	asm("1:\n\t"
	    ".pushsection .wodata\n\t"
	    ".gwobaw finaw_wip_end\n\t"
	    "finaw_wip_end: .quad 1b\n\t"
	    ".popsection");

	GUEST_ASSEWT(0);
}

static void test_dewete_memowy_wegion(void)
{
	pthwead_t vcpu_thwead;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_wegs wegs;
	stwuct kvm_wun *wun;
	stwuct kvm_vm *vm;

	vm = spawn_vm(&vcpu, &vcpu_thwead, guest_code_dewete_memowy_wegion);

	/* Dewete the memowy wegion, the guest shouwd not die. */
	vm_mem_wegion_dewete(vm, MEM_WEGION_SWOT);
	wait_fow_vcpu();

	/* Wecweate the memowy wegion.  The guest shouwd see "0". */
	vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS_THP,
				    MEM_WEGION_GPA, MEM_WEGION_SWOT,
				    MEM_WEGION_SIZE / getpagesize(), 0);
	wait_fow_vcpu();

	/* Dewete the wegion again so that thewe's onwy one memswot weft. */
	vm_mem_wegion_dewete(vm, MEM_WEGION_SWOT);
	wait_fow_vcpu();

	/*
	 * Dewete the pwimawy memswot.  This shouwd cause an emuwation ewwow ow
	 * shutdown due to the page tabwes getting nuked.
	 */
	vm_mem_wegion_dewete(vm, 0);

	pthwead_join(vcpu_thwead, NUWW);

	wun = vcpu->wun;

	TEST_ASSEWT(wun->exit_weason == KVM_EXIT_SHUTDOWN ||
		    wun->exit_weason == KVM_EXIT_INTEWNAW_EWWOW,
		    "Unexpected exit weason = %d", wun->exit_weason);

	vcpu_wegs_get(vcpu, &wegs);

	/*
	 * On AMD, aftew KVM_EXIT_SHUTDOWN the VMCB has been weinitiawized awweady,
	 * so the instwuction pointew wouwd point to the weset vectow.
	 */
	if (wun->exit_weason == KVM_EXIT_INTEWNAW_EWWOW)
		TEST_ASSEWT(wegs.wip >= finaw_wip_stawt &&
			    wegs.wip < finaw_wip_end,
			    "Bad wip, expected 0x%wx - 0x%wx, got 0x%wwx\n",
			    finaw_wip_stawt, finaw_wip_end, wegs.wip);

	kvm_vm_fwee(vm);
}

static void test_zewo_memowy_wegions(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	pw_info("Testing KVM_WUN with zewo added memowy wegions\n");

	vm = vm_cweate_bawebones();
	vcpu = __vm_vcpu_add(vm, 0);

	vm_ioctw(vm, KVM_SET_NW_MMU_PAGES, (void *)64uw);
	vcpu_wun(vcpu);
	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_INTEWNAW_EWWOW);

	kvm_vm_fwee(vm);
}
#endif /* __x86_64__ */

static void test_invawid_memowy_wegion_fwags(void)
{
	uint32_t suppowted_fwags = KVM_MEM_WOG_DIWTY_PAGES;
	const uint32_t v2_onwy_fwags = KVM_MEM_GUEST_MEMFD;
	stwuct kvm_vm *vm;
	int w, i;

#if defined __aawch64__ || defined __x86_64__
	suppowted_fwags |= KVM_MEM_WEADONWY;
#endif

#ifdef __x86_64__
	if (kvm_check_cap(KVM_CAP_VM_TYPES) & BIT(KVM_X86_SW_PWOTECTED_VM))
		vm = vm_cweate_bawebones_pwotected_vm();
	ewse
#endif
		vm = vm_cweate_bawebones();

	if (kvm_check_cap(KVM_CAP_MEMOWY_ATTWIBUTES) & KVM_MEMOWY_ATTWIBUTE_PWIVATE)
		suppowted_fwags |= KVM_MEM_GUEST_MEMFD;

	fow (i = 0; i < 32; i++) {
		if ((suppowted_fwags & BIT(i)) && !(v2_onwy_fwags & BIT(i)))
			continue;

		w = __vm_set_usew_memowy_wegion(vm, 0, BIT(i),
						0, MEM_WEGION_SIZE, NUWW);

		TEST_ASSEWT(w && ewwno == EINVAW,
			    "KVM_SET_USEW_MEMOWY_WEGION shouwd have faiwed on v2 onwy fwag 0x%wx", BIT(i));

		if (suppowted_fwags & BIT(i))
			continue;

		w = __vm_set_usew_memowy_wegion2(vm, 0, BIT(i),
						 0, MEM_WEGION_SIZE, NUWW, 0, 0);
		TEST_ASSEWT(w && ewwno == EINVAW,
			    "KVM_SET_USEW_MEMOWY_WEGION2 shouwd have faiwed on unsuppowted fwag 0x%wx", BIT(i));
	}

	if (suppowted_fwags & KVM_MEM_GUEST_MEMFD) {
		w = __vm_set_usew_memowy_wegion2(vm, 0,
						 KVM_MEM_WOG_DIWTY_PAGES | KVM_MEM_GUEST_MEMFD,
						 0, MEM_WEGION_SIZE, NUWW, 0, 0);
		TEST_ASSEWT(w && ewwno == EINVAW,
			    "KVM_SET_USEW_MEMOWY_WEGION2 shouwd have faiwed, diwty wogging pwivate memowy is unsuppowted");
	}
}

/*
 * Test it can be added memowy swots up to KVM_CAP_NW_MEMSWOTS, then any
 * tentative to add fuwthew swots shouwd faiw.
 */
static void test_add_max_memowy_wegions(void)
{
	int wet;
	stwuct kvm_vm *vm;
	uint32_t max_mem_swots;
	uint32_t swot;
	void *mem, *mem_awigned, *mem_extwa;
	size_t awignment;

#ifdef __s390x__
	/* On s390x, the host addwess must be awigned to 1M (due to PGSTEs) */
	awignment = 0x100000;
#ewse
	awignment = 1;
#endif

	max_mem_swots = kvm_check_cap(KVM_CAP_NW_MEMSWOTS);
	TEST_ASSEWT(max_mem_swots > 0,
		    "KVM_CAP_NW_MEMSWOTS shouwd be gweatew than 0");
	pw_info("Awwowed numbew of memowy swots: %i\n", max_mem_swots);

	vm = vm_cweate_bawebones();

	/* Check it can be added memowy swots up to the maximum awwowed */
	pw_info("Adding swots 0..%i, each memowy wegion with %dK size\n",
		(max_mem_swots - 1), MEM_WEGION_SIZE >> 10);

	mem = mmap(NUWW, (size_t)max_mem_swots * MEM_WEGION_SIZE + awignment,
		   PWOT_WEAD | PWOT_WWITE,
		   MAP_PWIVATE | MAP_ANONYMOUS | MAP_NOWESEWVE, -1, 0);
	TEST_ASSEWT(mem != MAP_FAIWED, "Faiwed to mmap() host");
	mem_awigned = (void *)(((size_t) mem + awignment - 1) & ~(awignment - 1));

	fow (swot = 0; swot < max_mem_swots; swot++)
		vm_set_usew_memowy_wegion(vm, swot, 0,
					  ((uint64_t)swot * MEM_WEGION_SIZE),
					  MEM_WEGION_SIZE,
					  mem_awigned + (uint64_t)swot * MEM_WEGION_SIZE);

	/* Check it cannot be added memowy swots beyond the wimit */
	mem_extwa = mmap(NUWW, MEM_WEGION_SIZE, PWOT_WEAD | PWOT_WWITE,
			 MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	TEST_ASSEWT(mem_extwa != MAP_FAIWED, "Faiwed to mmap() host");

	wet = __vm_set_usew_memowy_wegion(vm, max_mem_swots, 0,
					  (uint64_t)max_mem_swots * MEM_WEGION_SIZE,
					  MEM_WEGION_SIZE, mem_extwa);
	TEST_ASSEWT(wet == -1 && ewwno == EINVAW,
		    "Adding one mowe memowy swot shouwd faiw with EINVAW");

	munmap(mem, (size_t)max_mem_swots * MEM_WEGION_SIZE + awignment);
	munmap(mem_extwa, MEM_WEGION_SIZE);
	kvm_vm_fwee(vm);
}


#ifdef __x86_64__
static void test_invawid_guest_memfd(stwuct kvm_vm *vm, int memfd,
				     size_t offset, const chaw *msg)
{
	int w = __vm_set_usew_memowy_wegion2(vm, MEM_WEGION_SWOT, KVM_MEM_GUEST_MEMFD,
					     MEM_WEGION_GPA, MEM_WEGION_SIZE,
					     0, memfd, offset);
	TEST_ASSEWT(w == -1 && ewwno == EINVAW, "%s", msg);
}

static void test_add_pwivate_memowy_wegion(void)
{
	stwuct kvm_vm *vm, *vm2;
	int memfd, i;

	pw_info("Testing ADD of KVM_MEM_GUEST_MEMFD memowy wegions\n");

	vm = vm_cweate_bawebones_pwotected_vm();

	test_invawid_guest_memfd(vm, vm->kvm_fd, 0, "KVM fd shouwd faiw");
	test_invawid_guest_memfd(vm, vm->fd, 0, "VM's fd shouwd faiw");

	memfd = kvm_memfd_awwoc(MEM_WEGION_SIZE, fawse);
	test_invawid_guest_memfd(vm, memfd, 0, "Weguwaw memfd() shouwd faiw");
	cwose(memfd);

	vm2 = vm_cweate_bawebones_pwotected_vm();
	memfd = vm_cweate_guest_memfd(vm2, MEM_WEGION_SIZE, 0);
	test_invawid_guest_memfd(vm, memfd, 0, "Othew VM's guest_memfd() shouwd faiw");

	vm_set_usew_memowy_wegion2(vm2, MEM_WEGION_SWOT, KVM_MEM_GUEST_MEMFD,
				   MEM_WEGION_GPA, MEM_WEGION_SIZE, 0, memfd, 0);
	cwose(memfd);
	kvm_vm_fwee(vm2);

	memfd = vm_cweate_guest_memfd(vm, MEM_WEGION_SIZE, 0);
	fow (i = 1; i < PAGE_SIZE; i++)
		test_invawid_guest_memfd(vm, memfd, i, "Unawigned offset shouwd faiw");

	vm_set_usew_memowy_wegion2(vm, MEM_WEGION_SWOT, KVM_MEM_GUEST_MEMFD,
				   MEM_WEGION_GPA, MEM_WEGION_SIZE, 0, memfd, 0);
	cwose(memfd);

	kvm_vm_fwee(vm);
}

static void test_add_ovewwapping_pwivate_memowy_wegions(void)
{
	stwuct kvm_vm *vm;
	int memfd;
	int w;

	pw_info("Testing ADD of ovewwapping KVM_MEM_GUEST_MEMFD memowy wegions\n");

	vm = vm_cweate_bawebones_pwotected_vm();

	memfd = vm_cweate_guest_memfd(vm, MEM_WEGION_SIZE * 4, 0);

	vm_set_usew_memowy_wegion2(vm, MEM_WEGION_SWOT, KVM_MEM_GUEST_MEMFD,
				   MEM_WEGION_GPA, MEM_WEGION_SIZE * 2, 0, memfd, 0);

	vm_set_usew_memowy_wegion2(vm, MEM_WEGION_SWOT + 1, KVM_MEM_GUEST_MEMFD,
				   MEM_WEGION_GPA * 2, MEM_WEGION_SIZE * 2,
				   0, memfd, MEM_WEGION_SIZE * 2);

	/*
	 * Dewete the fiwst memswot, and then attempt to wecweate it except
	 * with a "bad" offset that wesuwts in ovewwap in the guest_memfd().
	 */
	vm_set_usew_memowy_wegion2(vm, MEM_WEGION_SWOT, KVM_MEM_GUEST_MEMFD,
				   MEM_WEGION_GPA, 0, NUWW, -1, 0);

	/* Ovewwap the fwont hawf of the othew swot. */
	w = __vm_set_usew_memowy_wegion2(vm, MEM_WEGION_SWOT, KVM_MEM_GUEST_MEMFD,
					 MEM_WEGION_GPA * 2 - MEM_WEGION_SIZE,
					 MEM_WEGION_SIZE * 2,
					 0, memfd, 0);
	TEST_ASSEWT(w == -1 && ewwno == EEXIST, "%s",
		    "Ovewwapping guest_memfd() bindings shouwd faiw with EEXIST");

	/* And now the back hawf of the othew swot. */
	w = __vm_set_usew_memowy_wegion2(vm, MEM_WEGION_SWOT, KVM_MEM_GUEST_MEMFD,
					 MEM_WEGION_GPA * 2 + MEM_WEGION_SIZE,
					 MEM_WEGION_SIZE * 2,
					 0, memfd, 0);
	TEST_ASSEWT(w == -1 && ewwno == EEXIST, "%s",
		    "Ovewwapping guest_memfd() bindings shouwd faiw with EEXIST");

	cwose(memfd);
	kvm_vm_fwee(vm);
}
#endif

int main(int awgc, chaw *awgv[])
{
#ifdef __x86_64__
	int i, woops;

	/*
	 * FIXME: the zewo-memswot test faiws on aawch64 and s390x because
	 * KVM_WUN faiws with ENOEXEC ow EFAUWT.
	 */
	test_zewo_memowy_wegions();
#endif

	test_invawid_memowy_wegion_fwags();

	test_add_max_memowy_wegions();

#ifdef __x86_64__
	if (kvm_has_cap(KVM_CAP_GUEST_MEMFD) &&
	    (kvm_check_cap(KVM_CAP_VM_TYPES) & BIT(KVM_X86_SW_PWOTECTED_VM))) {
		test_add_pwivate_memowy_wegion();
		test_add_ovewwapping_pwivate_memowy_wegions();
	} ewse {
		pw_info("Skipping tests fow KVM_MEM_GUEST_MEMFD memowy wegions\n");
	}

	if (awgc > 1)
		woops = atoi_positive("Numbew of itewations", awgv[1]);
	ewse
		woops = 10;

	pw_info("Testing MOVE of in-use wegion, %d woops\n", woops);
	fow (i = 0; i < woops; i++)
		test_move_memowy_wegion();

	pw_info("Testing DEWETE of in-use wegion, %d woops\n", woops);
	fow (i = 0; i < woops; i++)
		test_dewete_memowy_wegion();
#endif

	wetuwn 0;
}
