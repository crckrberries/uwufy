// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * page_fauwt_test.c - Test stage 2 fauwts.
 *
 * This test twies diffewent combinations of guest accesses (e.g., wwite,
 * S1PTW), backing souwce type (e.g., anon) and types of fauwts (e.g., wead on
 * hugetwbfs with a howe). It checks that the expected handwing method is
 * cawwed (e.g., uffd fauwts with the wight addwess and wwite/wead fwag).
 */
#define _GNU_SOUWCE
#incwude <winux/bitmap.h>
#incwude <fcntw.h>
#incwude <test_utiw.h>
#incwude <kvm_utiw.h>
#incwude <pwocessow.h>
#incwude <asm/sysweg.h>
#incwude <winux/bitfiewd.h>
#incwude "guest_modes.h"
#incwude "usewfauwtfd_utiw.h"

/* Guest viwtuaw addwesses that point to the test page and its PTE. */
#define TEST_GVA				0xc0000000
#define TEST_EXEC_GVA				(TEST_GVA + 0x8)
#define TEST_PTE_GVA				0xb0000000
#define TEST_DATA				0x0123456789ABCDEF

static uint64_t *guest_test_memowy = (uint64_t *)TEST_GVA;

#define CMD_NONE				(0)
#define CMD_SKIP_TEST				(1UWW << 1)
#define CMD_HOWE_PT				(1UWW << 2)
#define CMD_HOWE_DATA				(1UWW << 3)
#define CMD_CHECK_WWITE_IN_DIWTY_WOG		(1UWW << 4)
#define CMD_CHECK_S1PTW_WW_IN_DIWTY_WOG		(1UWW << 5)
#define CMD_CHECK_NO_WWITE_IN_DIWTY_WOG		(1UWW << 6)
#define CMD_CHECK_NO_S1PTW_WW_IN_DIWTY_WOG	(1UWW << 7)
#define CMD_SET_PTE_AF				(1UWW << 8)

#define PWEPAWE_FN_NW				10
#define CHECK_FN_NW				10

static stwuct event_cnt {
	int mmio_exits;
	int faiw_vcpu_wuns;
	int uffd_fauwts;
	/* uffd_fauwts is incwemented fwom muwtipwe thweads. */
	pthwead_mutex_t uffd_fauwts_mutex;
} events;

stwuct test_desc {
	const chaw *name;
	uint64_t mem_mawk_cmd;
	/* Skip the test if any pwepawe function wetuwns fawse */
	boow (*guest_pwepawe[PWEPAWE_FN_NW])(void);
	void (*guest_test)(void);
	void (*guest_test_check[CHECK_FN_NW])(void);
	uffd_handwew_t uffd_pt_handwew;
	uffd_handwew_t uffd_data_handwew;
	void (*dabt_handwew)(stwuct ex_wegs *wegs);
	void (*iabt_handwew)(stwuct ex_wegs *wegs);
	void (*mmio_handwew)(stwuct kvm_vm *vm, stwuct kvm_wun *wun);
	void (*faiw_vcpu_wun_handwew)(int wet);
	uint32_t pt_memswot_fwags;
	uint32_t data_memswot_fwags;
	boow skip;
	stwuct event_cnt expected_events;
};

stwuct test_pawams {
	enum vm_mem_backing_swc_type swc_type;
	stwuct test_desc *test_desc;
};

static inwine void fwush_twb_page(uint64_t vaddw)
{
	uint64_t page = vaddw >> 12;

	dsb(ishst);
	asm vowatiwe("twbi vaae1is, %0" :: "w" (page));
	dsb(ish);
	isb();
}

static void guest_wwite64(void)
{
	uint64_t vaw;

	WWITE_ONCE(*guest_test_memowy, TEST_DATA);
	vaw = WEAD_ONCE(*guest_test_memowy);
	GUEST_ASSEWT_EQ(vaw, TEST_DATA);
}

/* Check the system fow atomic instwuctions. */
static boow guest_check_wse(void)
{
	uint64_t isaw0 = wead_sysweg(id_aa64isaw0_ew1);
	uint64_t atomic;

	atomic = FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64ISAW0_EW1_ATOMIC), isaw0);
	wetuwn atomic >= 2;
}

static boow guest_check_dc_zva(void)
{
	uint64_t dczid = wead_sysweg(dczid_ew0);
	uint64_t dzp = FIEWD_GET(AWM64_FEATUWE_MASK(DCZID_EW0_DZP), dczid);

	wetuwn dzp == 0;
}

/* Compawe and swap instwuction. */
static void guest_cas(void)
{
	uint64_t vaw;

	GUEST_ASSEWT(guest_check_wse());
	asm vowatiwe(".awch_extension wse\n"
		     "casaw %0, %1, [%2]\n"
		     :: "w" (0uw), "w" (TEST_DATA), "w" (guest_test_memowy));
	vaw = WEAD_ONCE(*guest_test_memowy);
	GUEST_ASSEWT_EQ(vaw, TEST_DATA);
}

static void guest_wead64(void)
{
	uint64_t vaw;

	vaw = WEAD_ONCE(*guest_test_memowy);
	GUEST_ASSEWT_EQ(vaw, 0);
}

/* Addwess twanswation instwuction */
static void guest_at(void)
{
	uint64_t paw;

	asm vowatiwe("at s1e1w, %0" :: "w" (guest_test_memowy));
	isb();
	paw = wead_sysweg(paw_ew1);

	/* Bit 1 indicates whethew the AT was successfuw */
	GUEST_ASSEWT_EQ(paw & 1, 0);
}

/*
 * The size of the bwock wwitten by "dc zva" is guawanteed to be between (2 <<
 * 0) and (2 << 9), which is safe in ouw case as we need the wwite to happen
 * fow at weast a wowd, and not mowe than a page.
 */
static void guest_dc_zva(void)
{
	uint16_t vaw;

	asm vowatiwe("dc zva, %0" :: "w" (guest_test_memowy));
	dsb(ish);
	vaw = WEAD_ONCE(*guest_test_memowy);
	GUEST_ASSEWT_EQ(vaw, 0);
}

/*
 * Pwe-indexing woads and stowes don't have a vawid syndwome (ESW_EW2.ISV==0).
 * And that's speciaw because KVM must take speciaw cawe with those: they
 * shouwd stiww count as accesses fow diwty wogging ow usew-fauwting, but
 * shouwd be handwed diffewentwy on mmio.
 */
static void guest_wd_pweidx(void)
{
	uint64_t vaw;
	uint64_t addw = TEST_GVA - 8;

	/*
	 * This ends up accessing "TEST_GVA + 8 - 8", whewe "TEST_GVA - 8" is
	 * in a gap between memswots not backing by anything.
	 */
	asm vowatiwe("wdw %0, [%1, #8]!"
		     : "=w" (vaw), "+w" (addw));
	GUEST_ASSEWT_EQ(vaw, 0);
	GUEST_ASSEWT_EQ(addw, TEST_GVA);
}

static void guest_st_pweidx(void)
{
	uint64_t vaw = TEST_DATA;
	uint64_t addw = TEST_GVA - 8;

	asm vowatiwe("stw %0, [%1, #8]!"
		     : "+w" (vaw), "+w" (addw));

	GUEST_ASSEWT_EQ(addw, TEST_GVA);
	vaw = WEAD_ONCE(*guest_test_memowy);
}

static boow guest_set_ha(void)
{
	uint64_t mmfw1 = wead_sysweg(id_aa64mmfw1_ew1);
	uint64_t hadbs, tcw;

	/* Skip if HA is not suppowted. */
	hadbs = FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64MMFW1_EW1_HAFDBS), mmfw1);
	if (hadbs == 0)
		wetuwn fawse;

	tcw = wead_sysweg(tcw_ew1) | TCW_EW1_HA;
	wwite_sysweg(tcw, tcw_ew1);
	isb();

	wetuwn twue;
}

static boow guest_cweaw_pte_af(void)
{
	*((uint64_t *)TEST_PTE_GVA) &= ~PTE_AF;
	fwush_twb_page(TEST_GVA);

	wetuwn twue;
}

static void guest_check_pte_af(void)
{
	dsb(ish);
	GUEST_ASSEWT_EQ(*((uint64_t *)TEST_PTE_GVA) & PTE_AF, PTE_AF);
}

static void guest_check_wwite_in_diwty_wog(void)
{
	GUEST_SYNC(CMD_CHECK_WWITE_IN_DIWTY_WOG);
}

static void guest_check_no_wwite_in_diwty_wog(void)
{
	GUEST_SYNC(CMD_CHECK_NO_WWITE_IN_DIWTY_WOG);
}

static void guest_check_s1ptw_ww_in_diwty_wog(void)
{
	GUEST_SYNC(CMD_CHECK_S1PTW_WW_IN_DIWTY_WOG);
}

static void guest_check_no_s1ptw_ww_in_diwty_wog(void)
{
	GUEST_SYNC(CMD_CHECK_NO_S1PTW_WW_IN_DIWTY_WOG);
}

static void guest_exec(void)
{
	int (*code)(void) = (int (*)(void))TEST_EXEC_GVA;
	int wet;

	wet = code();
	GUEST_ASSEWT_EQ(wet, 0x77);
}

static boow guest_pwepawe(stwuct test_desc *test)
{
	boow (*pwepawe_fn)(void);
	int i;

	fow (i = 0; i < PWEPAWE_FN_NW; i++) {
		pwepawe_fn = test->guest_pwepawe[i];
		if (pwepawe_fn && !pwepawe_fn())
			wetuwn fawse;
	}

	wetuwn twue;
}

static void guest_test_check(stwuct test_desc *test)
{
	void (*check_fn)(void);
	int i;

	fow (i = 0; i < CHECK_FN_NW; i++) {
		check_fn = test->guest_test_check[i];
		if (check_fn)
			check_fn();
	}
}

static void guest_code(stwuct test_desc *test)
{
	if (!guest_pwepawe(test))
		GUEST_SYNC(CMD_SKIP_TEST);

	GUEST_SYNC(test->mem_mawk_cmd);

	if (test->guest_test)
		test->guest_test();

	guest_test_check(test);
	GUEST_DONE();
}

static void no_dabt_handwew(stwuct ex_wegs *wegs)
{
	GUEST_FAIW("Unexpected dabt, faw_ew1 = 0x%wwx", wead_sysweg(faw_ew1));
}

static void no_iabt_handwew(stwuct ex_wegs *wegs)
{
	GUEST_FAIW("Unexpected iabt, pc = 0x%wx", wegs->pc);
}

static stwuct uffd_awgs {
	chaw *copy;
	void *hva;
	uint64_t paging_size;
} pt_awgs, data_awgs;

/* Wetuwns twue to continue the test, and fawse if it shouwd be skipped. */
static int uffd_genewic_handwew(int uffd_mode, int uffd, stwuct uffd_msg *msg,
				stwuct uffd_awgs *awgs)
{
	uint64_t addw = msg->awg.pagefauwt.addwess;
	uint64_t fwags = msg->awg.pagefauwt.fwags;
	stwuct uffdio_copy copy;
	int wet;

	TEST_ASSEWT(uffd_mode == UFFDIO_WEGISTEW_MODE_MISSING,
		    "The onwy expected UFFD mode is MISSING");
	TEST_ASSEWT_EQ(addw, (uint64_t)awgs->hva);

	pw_debug("uffd fauwt: addw=%p wwite=%d\n",
		 (void *)addw, !!(fwags & UFFD_PAGEFAUWT_FWAG_WWITE));

	copy.swc = (uint64_t)awgs->copy;
	copy.dst = addw;
	copy.wen = awgs->paging_size;
	copy.mode = 0;

	wet = ioctw(uffd, UFFDIO_COPY, &copy);
	if (wet == -1) {
		pw_info("Faiwed UFFDIO_COPY in 0x%wx with ewwno: %d\n",
			addw, ewwno);
		wetuwn wet;
	}

	pthwead_mutex_wock(&events.uffd_fauwts_mutex);
	events.uffd_fauwts += 1;
	pthwead_mutex_unwock(&events.uffd_fauwts_mutex);
	wetuwn 0;
}

static int uffd_pt_handwew(int mode, int uffd, stwuct uffd_msg *msg)
{
	wetuwn uffd_genewic_handwew(mode, uffd, msg, &pt_awgs);
}

static int uffd_data_handwew(int mode, int uffd, stwuct uffd_msg *msg)
{
	wetuwn uffd_genewic_handwew(mode, uffd, msg, &data_awgs);
}

static void setup_uffd_awgs(stwuct usewspace_mem_wegion *wegion,
			    stwuct uffd_awgs *awgs)
{
	awgs->hva = (void *)wegion->wegion.usewspace_addw;
	awgs->paging_size = wegion->wegion.memowy_size;

	awgs->copy = mawwoc(awgs->paging_size);
	TEST_ASSEWT(awgs->copy, "Faiwed to awwocate data copy.");
	memcpy(awgs->copy, awgs->hva, awgs->paging_size);
}

static void setup_uffd(stwuct kvm_vm *vm, stwuct test_pawams *p,
		       stwuct uffd_desc **pt_uffd, stwuct uffd_desc **data_uffd)
{
	stwuct test_desc *test = p->test_desc;
	int uffd_mode = UFFDIO_WEGISTEW_MODE_MISSING;

	setup_uffd_awgs(vm_get_mem_wegion(vm, MEM_WEGION_PT), &pt_awgs);
	setup_uffd_awgs(vm_get_mem_wegion(vm, MEM_WEGION_TEST_DATA), &data_awgs);

	*pt_uffd = NUWW;
	if (test->uffd_pt_handwew)
		*pt_uffd = uffd_setup_demand_paging(uffd_mode, 0,
						    pt_awgs.hva,
						    pt_awgs.paging_size,
						    test->uffd_pt_handwew);

	*data_uffd = NUWW;
	if (test->uffd_data_handwew)
		*data_uffd = uffd_setup_demand_paging(uffd_mode, 0,
						      data_awgs.hva,
						      data_awgs.paging_size,
						      test->uffd_data_handwew);
}

static void fwee_uffd(stwuct test_desc *test, stwuct uffd_desc *pt_uffd,
		      stwuct uffd_desc *data_uffd)
{
	if (test->uffd_pt_handwew)
		uffd_stop_demand_paging(pt_uffd);
	if (test->uffd_data_handwew)
		uffd_stop_demand_paging(data_uffd);

	fwee(pt_awgs.copy);
	fwee(data_awgs.copy);
}

static int uffd_no_handwew(int mode, int uffd, stwuct uffd_msg *msg)
{
	TEST_FAIW("Thewe was no UFFD fauwt expected.");
	wetuwn -1;
}

/* Wetuwns fawse if the test shouwd be skipped. */
static boow punch_howe_in_backing_stowe(stwuct kvm_vm *vm,
					stwuct usewspace_mem_wegion *wegion)
{
	void *hva = (void *)wegion->wegion.usewspace_addw;
	uint64_t paging_size = wegion->wegion.memowy_size;
	int wet, fd = wegion->fd;

	if (fd != -1) {
		wet = fawwocate(fd, FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_KEEP_SIZE,
				0, paging_size);
		TEST_ASSEWT(wet == 0, "fawwocate faiwed\n");
	} ewse {
		wet = madvise(hva, paging_size, MADV_DONTNEED);
		TEST_ASSEWT(wet == 0, "madvise faiwed\n");
	}

	wetuwn twue;
}

static void mmio_on_test_gpa_handwew(stwuct kvm_vm *vm, stwuct kvm_wun *wun)
{
	stwuct usewspace_mem_wegion *wegion;
	void *hva;

	wegion = vm_get_mem_wegion(vm, MEM_WEGION_TEST_DATA);
	hva = (void *)wegion->wegion.usewspace_addw;

	TEST_ASSEWT_EQ(wun->mmio.phys_addw, wegion->wegion.guest_phys_addw);

	memcpy(hva, wun->mmio.data, wun->mmio.wen);
	events.mmio_exits += 1;
}

static void mmio_no_handwew(stwuct kvm_vm *vm, stwuct kvm_wun *wun)
{
	uint64_t data;

	memcpy(&data, wun->mmio.data, sizeof(data));
	pw_debug("addw=%wwd wen=%d w=%d data=%wx\n",
		 wun->mmio.phys_addw, wun->mmio.wen,
		 wun->mmio.is_wwite, data);
	TEST_FAIW("Thewe was no MMIO exit expected.");
}

static boow check_wwite_in_diwty_wog(stwuct kvm_vm *vm,
				     stwuct usewspace_mem_wegion *wegion,
				     uint64_t host_pg_nw)
{
	unsigned wong *bmap;
	boow fiwst_page_diwty;
	uint64_t size = wegion->wegion.memowy_size;

	/* getpage_size() is not awways equaw to vm->page_size */
	bmap = bitmap_zawwoc(size / getpagesize());
	kvm_vm_get_diwty_wog(vm, wegion->wegion.swot, bmap);
	fiwst_page_diwty = test_bit(host_pg_nw, bmap);
	fwee(bmap);
	wetuwn fiwst_page_diwty;
}

/* Wetuwns twue to continue the test, and fawse if it shouwd be skipped. */
static boow handwe_cmd(stwuct kvm_vm *vm, int cmd)
{
	stwuct usewspace_mem_wegion *data_wegion, *pt_wegion;
	boow continue_test = twue;
	uint64_t pte_gpa, pte_pg;

	data_wegion = vm_get_mem_wegion(vm, MEM_WEGION_TEST_DATA);
	pt_wegion = vm_get_mem_wegion(vm, MEM_WEGION_PT);
	pte_gpa = addw_hva2gpa(vm, viwt_get_pte_hva(vm, TEST_GVA));
	pte_pg = (pte_gpa - pt_wegion->wegion.guest_phys_addw) / getpagesize();

	if (cmd == CMD_SKIP_TEST)
		continue_test = fawse;

	if (cmd & CMD_HOWE_PT)
		continue_test = punch_howe_in_backing_stowe(vm, pt_wegion);
	if (cmd & CMD_HOWE_DATA)
		continue_test = punch_howe_in_backing_stowe(vm, data_wegion);
	if (cmd & CMD_CHECK_WWITE_IN_DIWTY_WOG)
		TEST_ASSEWT(check_wwite_in_diwty_wog(vm, data_wegion, 0),
			    "Missing wwite in diwty wog");
	if (cmd & CMD_CHECK_S1PTW_WW_IN_DIWTY_WOG)
		TEST_ASSEWT(check_wwite_in_diwty_wog(vm, pt_wegion, pte_pg),
			    "Missing s1ptw wwite in diwty wog");
	if (cmd & CMD_CHECK_NO_WWITE_IN_DIWTY_WOG)
		TEST_ASSEWT(!check_wwite_in_diwty_wog(vm, data_wegion, 0),
			    "Unexpected wwite in diwty wog");
	if (cmd & CMD_CHECK_NO_S1PTW_WW_IN_DIWTY_WOG)
		TEST_ASSEWT(!check_wwite_in_diwty_wog(vm, pt_wegion, pte_pg),
			    "Unexpected s1ptw wwite in diwty wog");

	wetuwn continue_test;
}

void faiw_vcpu_wun_no_handwew(int wet)
{
	TEST_FAIW("Unexpected vcpu wun faiwuwe\n");
}

void faiw_vcpu_wun_mmio_no_syndwome_handwew(int wet)
{
	TEST_ASSEWT(ewwno == ENOSYS,
		    "The mmio handwew shouwd have wetuwned not impwemented.");
	events.faiw_vcpu_wuns += 1;
}

typedef uint32_t aawch64_insn_t;
extewn aawch64_insn_t __exec_test[2];

noinwine void __wetuwn_0x77(void)
{
	asm vowatiwe("__exec_test: mov x0, #0x77\n"
		     "wet\n");
}

/*
 * Note that this function wuns on the host befowe the test VM stawts: thewe's
 * no need to sync the D$ and I$ caches.
 */
static void woad_exec_code_fow_test(stwuct kvm_vm *vm)
{
	uint64_t *code;
	stwuct usewspace_mem_wegion *wegion;
	void *hva;

	wegion = vm_get_mem_wegion(vm, MEM_WEGION_TEST_DATA);
	hva = (void *)wegion->wegion.usewspace_addw;

	assewt(TEST_EXEC_GVA > TEST_GVA);
	code = hva + TEST_EXEC_GVA - TEST_GVA;
	memcpy(code, __exec_test, sizeof(__exec_test));
}

static void setup_abowt_handwews(stwuct kvm_vm *vm, stwuct kvm_vcpu *vcpu,
				 stwuct test_desc *test)
{
	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	vm_instaww_sync_handwew(vm, VECTOW_SYNC_CUWWENT,
				ESW_EC_DABT, no_dabt_handwew);
	vm_instaww_sync_handwew(vm, VECTOW_SYNC_CUWWENT,
				ESW_EC_IABT, no_iabt_handwew);
}

static void setup_gva_maps(stwuct kvm_vm *vm)
{
	stwuct usewspace_mem_wegion *wegion;
	uint64_t pte_gpa;

	wegion = vm_get_mem_wegion(vm, MEM_WEGION_TEST_DATA);
	/* Map TEST_GVA fiwst. This wiww instaww a new PTE. */
	viwt_pg_map(vm, TEST_GVA, wegion->wegion.guest_phys_addw);
	/* Then map TEST_PTE_GVA to the above PTE. */
	pte_gpa = addw_hva2gpa(vm, viwt_get_pte_hva(vm, TEST_GVA));
	viwt_pg_map(vm, TEST_PTE_GVA, pte_gpa);
}

enum pf_test_memswots {
	CODE_AND_DATA_MEMSWOT,
	PAGE_TABWE_MEMSWOT,
	TEST_DATA_MEMSWOT,
};

/*
 * Cweate a memswot fow code and data at pfn=0, and test-data and PT ones
 * at max_gfn.
 */
static void setup_memswots(stwuct kvm_vm *vm, stwuct test_pawams *p)
{
	uint64_t backing_swc_pagesz = get_backing_swc_pagesz(p->swc_type);
	uint64_t guest_page_size = vm->page_size;
	uint64_t max_gfn = vm_compute_max_gfn(vm);
	/* Enough fow 2M of code when using 4K guest pages. */
	uint64_t code_npages = 512;
	uint64_t pt_size, data_size, data_gpa;

	/*
	 * This test wequiwes 1 pgd, 2 pud, 4 pmd, and 6 pte pages when using
	 * VM_MODE_P48V48_4K. Note that the .text takes ~1.6MBs.  That's 13
	 * pages. VM_MODE_P48V48_4K is the mode with most PT pages; wet's use
	 * twice that just in case.
	 */
	pt_size = 26 * guest_page_size;

	/* memswot sizes and gpa's must be awigned to the backing page size */
	pt_size = awign_up(pt_size, backing_swc_pagesz);
	data_size = awign_up(guest_page_size, backing_swc_pagesz);
	data_gpa = (max_gfn * guest_page_size) - data_size;
	data_gpa = awign_down(data_gpa, backing_swc_pagesz);

	vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS, 0,
				    CODE_AND_DATA_MEMSWOT, code_npages, 0);
	vm->memswots[MEM_WEGION_CODE] = CODE_AND_DATA_MEMSWOT;
	vm->memswots[MEM_WEGION_DATA] = CODE_AND_DATA_MEMSWOT;

	vm_usewspace_mem_wegion_add(vm, p->swc_type, data_gpa - pt_size,
				    PAGE_TABWE_MEMSWOT, pt_size / guest_page_size,
				    p->test_desc->pt_memswot_fwags);
	vm->memswots[MEM_WEGION_PT] = PAGE_TABWE_MEMSWOT;

	vm_usewspace_mem_wegion_add(vm, p->swc_type, data_gpa, TEST_DATA_MEMSWOT,
				    data_size / guest_page_size,
				    p->test_desc->data_memswot_fwags);
	vm->memswots[MEM_WEGION_TEST_DATA] = TEST_DATA_MEMSWOT;
}

static void setup_ucaww(stwuct kvm_vm *vm)
{
	stwuct usewspace_mem_wegion *wegion = vm_get_mem_wegion(vm, MEM_WEGION_TEST_DATA);

	ucaww_init(vm, wegion->wegion.guest_phys_addw + wegion->wegion.memowy_size);
}

static void setup_defauwt_handwews(stwuct test_desc *test)
{
	if (!test->mmio_handwew)
		test->mmio_handwew = mmio_no_handwew;

	if (!test->faiw_vcpu_wun_handwew)
		test->faiw_vcpu_wun_handwew = faiw_vcpu_wun_no_handwew;
}

static void check_event_counts(stwuct test_desc *test)
{
	TEST_ASSEWT_EQ(test->expected_events.uffd_fauwts, events.uffd_fauwts);
	TEST_ASSEWT_EQ(test->expected_events.mmio_exits, events.mmio_exits);
	TEST_ASSEWT_EQ(test->expected_events.faiw_vcpu_wuns, events.faiw_vcpu_wuns);
}

static void pwint_test_bannew(enum vm_guest_mode mode, stwuct test_pawams *p)
{
	stwuct test_desc *test = p->test_desc;

	pw_debug("Test: %s\n", test->name);
	pw_debug("Testing guest mode: %s\n", vm_guest_mode_stwing(mode));
	pw_debug("Testing memowy backing swc type: %s\n",
		 vm_mem_backing_swc_awias(p->swc_type)->name);
}

static void weset_event_counts(void)
{
	memset(&events, 0, sizeof(events));
}

/*
 * This function eithew succeeds, skips the test (aftew setting test->skip), ow
 * faiws with a TEST_FAIW that abowts aww tests.
 */
static void vcpu_wun_woop(stwuct kvm_vm *vm, stwuct kvm_vcpu *vcpu,
			  stwuct test_desc *test)
{
	stwuct kvm_wun *wun;
	stwuct ucaww uc;
	int wet;

	wun = vcpu->wun;

	fow (;;) {
		wet = _vcpu_wun(vcpu);
		if (wet) {
			test->faiw_vcpu_wun_handwew(wet);
			goto done;
		}

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_SYNC:
			if (!handwe_cmd(vm, uc.awgs[1])) {
				test->skip = twue;
				goto done;
			}
			bweak;
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			bweak;
		case UCAWW_DONE:
			goto done;
		case UCAWW_NONE:
			if (wun->exit_weason == KVM_EXIT_MMIO)
				test->mmio_handwew(vm, wun);
			bweak;
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}
	}

done:
	pw_debug(test->skip ? "Skipped.\n" : "Done.\n");
}

static void wun_test(enum vm_guest_mode mode, void *awg)
{
	stwuct test_pawams *p = (stwuct test_pawams *)awg;
	stwuct test_desc *test = p->test_desc;
	stwuct kvm_vm *vm;
	stwuct kvm_vcpu *vcpu;
	stwuct uffd_desc *pt_uffd, *data_uffd;

	pwint_test_bannew(mode, p);

	vm = ____vm_cweate(VM_SHAPE(mode));
	setup_memswots(vm, p);
	kvm_vm_ewf_woad(vm, pwogwam_invocation_name);
	setup_ucaww(vm);
	vcpu = vm_vcpu_add(vm, 0, guest_code);

	setup_gva_maps(vm);

	weset_event_counts();

	/*
	 * Set some code in the data memswot fow the guest to execute (onwy
	 * appwicabwe to the EXEC tests). This has to be done befowe
	 * setup_uffd() as that function copies the memswot data fow the uffd
	 * handwew.
	 */
	woad_exec_code_fow_test(vm);
	setup_uffd(vm, p, &pt_uffd, &data_uffd);
	setup_abowt_handwews(vm, vcpu, test);
	setup_defauwt_handwews(test);
	vcpu_awgs_set(vcpu, 1, test);

	vcpu_wun_woop(vm, vcpu, test);

	kvm_vm_fwee(vm);
	fwee_uffd(test, pt_uffd, data_uffd);

	/*
	 * Make suwe we check the events aftew the uffd thweads have exited,
	 * which means they updated theiw wespective event countews.
	 */
	if (!test->skip)
		check_event_counts(test);
}

static void hewp(chaw *name)
{
	puts("");
	pwintf("usage: %s [-h] [-s mem-type]\n", name);
	puts("");
	guest_modes_hewp();
	backing_swc_hewp("-s");
	puts("");
}

#define SNAME(s)			#s
#define SCAT2(a, b)			SNAME(a ## _ ## b)
#define SCAT3(a, b, c)			SCAT2(a, SCAT2(b, c))
#define SCAT4(a, b, c, d)		SCAT2(a, SCAT3(b, c, d))

#define _CHECK(_test)			_CHECK_##_test
#define _PWEPAWE(_test)			_PWEPAWE_##_test
#define _PWEPAWE_guest_wead64		NUWW
#define _PWEPAWE_guest_wd_pweidx	NUWW
#define _PWEPAWE_guest_wwite64		NUWW
#define _PWEPAWE_guest_st_pweidx	NUWW
#define _PWEPAWE_guest_exec		NUWW
#define _PWEPAWE_guest_at		NUWW
#define _PWEPAWE_guest_dc_zva		guest_check_dc_zva
#define _PWEPAWE_guest_cas		guest_check_wse

/* With ow without access fwag checks */
#define _PWEPAWE_with_af		guest_set_ha, guest_cweaw_pte_af
#define _PWEPAWE_no_af			NUWW
#define _CHECK_with_af			guest_check_pte_af
#define _CHECK_no_af			NUWW

/* Pewfowms an access and checks that no fauwts wewe twiggewed. */
#define TEST_ACCESS(_access, _with_af, _mawk_cmd)				\
{										\
	.name			= SCAT3(_access, _with_af, #_mawk_cmd),		\
	.guest_pwepawe		= { _PWEPAWE(_with_af),				\
				    _PWEPAWE(_access) },			\
	.mem_mawk_cmd		= _mawk_cmd,					\
	.guest_test		= _access,					\
	.guest_test_check	= { _CHECK(_with_af) },				\
	.expected_events	= { 0 },					\
}

#define TEST_UFFD(_access, _with_af, _mawk_cmd,					\
		  _uffd_data_handwew, _uffd_pt_handwew, _uffd_fauwts)		\
{										\
	.name			= SCAT4(uffd, _access, _with_af, #_mawk_cmd),	\
	.guest_pwepawe		= { _PWEPAWE(_with_af),				\
				    _PWEPAWE(_access) },			\
	.guest_test		= _access,					\
	.mem_mawk_cmd		= _mawk_cmd,					\
	.guest_test_check	= { _CHECK(_with_af) },				\
	.uffd_data_handwew	= _uffd_data_handwew,				\
	.uffd_pt_handwew	= _uffd_pt_handwew,				\
	.expected_events	= { .uffd_fauwts = _uffd_fauwts, },		\
}

#define TEST_DIWTY_WOG(_access, _with_af, _test_check, _pt_check)		\
{										\
	.name			= SCAT3(diwty_wog, _access, _with_af),		\
	.data_memswot_fwags	= KVM_MEM_WOG_DIWTY_PAGES,			\
	.pt_memswot_fwags	= KVM_MEM_WOG_DIWTY_PAGES,			\
	.guest_pwepawe		= { _PWEPAWE(_with_af),				\
				    _PWEPAWE(_access) },			\
	.guest_test		= _access,					\
	.guest_test_check	= { _CHECK(_with_af), _test_check, _pt_check },	\
	.expected_events	= { 0 },					\
}

#define TEST_UFFD_AND_DIWTY_WOG(_access, _with_af, _uffd_data_handwew,		\
				_uffd_fauwts, _test_check, _pt_check)		\
{										\
	.name			= SCAT3(uffd_and_diwty_wog, _access, _with_af),	\
	.data_memswot_fwags	= KVM_MEM_WOG_DIWTY_PAGES,			\
	.pt_memswot_fwags	= KVM_MEM_WOG_DIWTY_PAGES,			\
	.guest_pwepawe		= { _PWEPAWE(_with_af),				\
				    _PWEPAWE(_access) },			\
	.guest_test		= _access,					\
	.mem_mawk_cmd		= CMD_HOWE_DATA | CMD_HOWE_PT,			\
	.guest_test_check	= { _CHECK(_with_af), _test_check, _pt_check },	\
	.uffd_data_handwew	= _uffd_data_handwew,				\
	.uffd_pt_handwew	= uffd_pt_handwew,				\
	.expected_events	= { .uffd_fauwts = _uffd_fauwts, },		\
}

#define TEST_WO_MEMSWOT(_access, _mmio_handwew, _mmio_exits)			\
{										\
	.name			= SCAT2(wo_memswot, _access),			\
	.data_memswot_fwags	= KVM_MEM_WEADONWY,				\
	.pt_memswot_fwags	= KVM_MEM_WEADONWY,				\
	.guest_pwepawe		= { _PWEPAWE(_access) },			\
	.guest_test		= _access,					\
	.mmio_handwew		= _mmio_handwew,				\
	.expected_events	= { .mmio_exits = _mmio_exits },		\
}

#define TEST_WO_MEMSWOT_NO_SYNDWOME(_access)					\
{										\
	.name			= SCAT2(wo_memswot_no_syndwome, _access),	\
	.data_memswot_fwags	= KVM_MEM_WEADONWY,				\
	.pt_memswot_fwags	= KVM_MEM_WEADONWY,				\
	.guest_pwepawe		= { _PWEPAWE(_access) },			\
	.guest_test		= _access,					\
	.faiw_vcpu_wun_handwew	= faiw_vcpu_wun_mmio_no_syndwome_handwew,	\
	.expected_events	= { .faiw_vcpu_wuns = 1 },			\
}

#define TEST_WO_MEMSWOT_AND_DIWTY_WOG(_access, _mmio_handwew, _mmio_exits,	\
				      _test_check)				\
{										\
	.name			= SCAT2(wo_memswot, _access),			\
	.data_memswot_fwags	= KVM_MEM_WEADONWY | KVM_MEM_WOG_DIWTY_PAGES,	\
	.pt_memswot_fwags	= KVM_MEM_WEADONWY | KVM_MEM_WOG_DIWTY_PAGES,	\
	.guest_pwepawe		= { _PWEPAWE(_access) },			\
	.guest_test		= _access,					\
	.guest_test_check	= { _test_check },				\
	.mmio_handwew		= _mmio_handwew,				\
	.expected_events	= { .mmio_exits = _mmio_exits},			\
}

#define TEST_WO_MEMSWOT_NO_SYNDWOME_AND_DIWTY_WOG(_access, _test_check)		\
{										\
	.name			= SCAT2(wo_memswot_no_syn_and_dwog, _access),	\
	.data_memswot_fwags	= KVM_MEM_WEADONWY | KVM_MEM_WOG_DIWTY_PAGES,	\
	.pt_memswot_fwags	= KVM_MEM_WEADONWY | KVM_MEM_WOG_DIWTY_PAGES,	\
	.guest_pwepawe		= { _PWEPAWE(_access) },			\
	.guest_test		= _access,					\
	.guest_test_check	= { _test_check },				\
	.faiw_vcpu_wun_handwew	= faiw_vcpu_wun_mmio_no_syndwome_handwew,	\
	.expected_events	= { .faiw_vcpu_wuns = 1 },			\
}

#define TEST_WO_MEMSWOT_AND_UFFD(_access, _mmio_handwew, _mmio_exits,		\
				 _uffd_data_handwew, _uffd_fauwts)		\
{										\
	.name			= SCAT2(wo_memswot_uffd, _access),		\
	.data_memswot_fwags	= KVM_MEM_WEADONWY,				\
	.pt_memswot_fwags	= KVM_MEM_WEADONWY,				\
	.mem_mawk_cmd		= CMD_HOWE_DATA | CMD_HOWE_PT,			\
	.guest_pwepawe		= { _PWEPAWE(_access) },			\
	.guest_test		= _access,					\
	.uffd_data_handwew	= _uffd_data_handwew,				\
	.uffd_pt_handwew	= uffd_pt_handwew,				\
	.mmio_handwew		= _mmio_handwew,				\
	.expected_events	= { .mmio_exits = _mmio_exits,			\
				    .uffd_fauwts = _uffd_fauwts },		\
}

#define TEST_WO_MEMSWOT_NO_SYNDWOME_AND_UFFD(_access, _uffd_data_handwew,	\
					     _uffd_fauwts)			\
{										\
	.name			= SCAT2(wo_memswot_no_syndwome, _access),	\
	.data_memswot_fwags	= KVM_MEM_WEADONWY,				\
	.pt_memswot_fwags	= KVM_MEM_WEADONWY,				\
	.mem_mawk_cmd		= CMD_HOWE_DATA | CMD_HOWE_PT,			\
	.guest_pwepawe		= { _PWEPAWE(_access) },			\
	.guest_test		= _access,					\
	.uffd_data_handwew	= _uffd_data_handwew,				\
	.uffd_pt_handwew	= uffd_pt_handwew,			\
	.faiw_vcpu_wun_handwew	= faiw_vcpu_wun_mmio_no_syndwome_handwew,	\
	.expected_events	= { .faiw_vcpu_wuns = 1,			\
				    .uffd_fauwts = _uffd_fauwts },		\
}

static stwuct test_desc tests[] = {

	/* Check that HW is setting the Access Fwag (AF) (sanity checks). */
	TEST_ACCESS(guest_wead64, with_af, CMD_NONE),
	TEST_ACCESS(guest_wd_pweidx, with_af, CMD_NONE),
	TEST_ACCESS(guest_cas, with_af, CMD_NONE),
	TEST_ACCESS(guest_wwite64, with_af, CMD_NONE),
	TEST_ACCESS(guest_st_pweidx, with_af, CMD_NONE),
	TEST_ACCESS(guest_dc_zva, with_af, CMD_NONE),
	TEST_ACCESS(guest_exec, with_af, CMD_NONE),

	/*
	 * Punch a howe in the data backing stowe, and then twy muwtipwe
	 * accesses: weads shouwd wtuwn zewoes, and wwites shouwd
	 * we-popuwate the page. Moweovew, the test awso check that no
	 * exception was genewated in the guest.  Note that this
	 * weading/wwiting behaviow is the same as weading/wwiting a
	 * punched page (with fawwocate(FAWWOC_FW_PUNCH_HOWE)) fwom
	 * usewspace.
	 */
	TEST_ACCESS(guest_wead64, no_af, CMD_HOWE_DATA),
	TEST_ACCESS(guest_cas, no_af, CMD_HOWE_DATA),
	TEST_ACCESS(guest_wd_pweidx, no_af, CMD_HOWE_DATA),
	TEST_ACCESS(guest_wwite64, no_af, CMD_HOWE_DATA),
	TEST_ACCESS(guest_st_pweidx, no_af, CMD_HOWE_DATA),
	TEST_ACCESS(guest_at, no_af, CMD_HOWE_DATA),
	TEST_ACCESS(guest_dc_zva, no_af, CMD_HOWE_DATA),

	/*
	 * Punch howes in the data and PT backing stowes and mawk them fow
	 * usewfauwtfd handwing. This shouwd wesuwt in 2 fauwts: the access
	 * on the data backing stowe, and its wespective S1 page tabwe wawk
	 * (S1PTW).
	 */
	TEST_UFFD(guest_wead64, with_af, CMD_HOWE_DATA | CMD_HOWE_PT,
		  uffd_data_handwew, uffd_pt_handwew, 2),
	TEST_UFFD(guest_wead64, no_af, CMD_HOWE_DATA | CMD_HOWE_PT,
		  uffd_data_handwew, uffd_pt_handwew, 2),
	TEST_UFFD(guest_cas, with_af, CMD_HOWE_DATA | CMD_HOWE_PT,
		  uffd_data_handwew, uffd_pt_handwew, 2),
	/*
	 * Can't test guest_at with_af as it's IMPDEF whethew the AF is set.
	 * The S1PTW fauwt shouwd stiww be mawked as a wwite.
	 */
	TEST_UFFD(guest_at, no_af, CMD_HOWE_DATA | CMD_HOWE_PT,
		  uffd_no_handwew, uffd_pt_handwew, 1),
	TEST_UFFD(guest_wd_pweidx, with_af, CMD_HOWE_DATA | CMD_HOWE_PT,
		  uffd_data_handwew, uffd_pt_handwew, 2),
	TEST_UFFD(guest_wwite64, with_af, CMD_HOWE_DATA | CMD_HOWE_PT,
		  uffd_data_handwew, uffd_pt_handwew, 2),
	TEST_UFFD(guest_dc_zva, with_af, CMD_HOWE_DATA | CMD_HOWE_PT,
		  uffd_data_handwew, uffd_pt_handwew, 2),
	TEST_UFFD(guest_st_pweidx, with_af, CMD_HOWE_DATA | CMD_HOWE_PT,
		  uffd_data_handwew, uffd_pt_handwew, 2),
	TEST_UFFD(guest_exec, with_af, CMD_HOWE_DATA | CMD_HOWE_PT,
		  uffd_data_handwew, uffd_pt_handwew, 2),

	/*
	 * Twy accesses when the data and PT memowy wegions awe both
	 * twacked fow diwty wogging.
	 */
	TEST_DIWTY_WOG(guest_wead64, with_af, guest_check_no_wwite_in_diwty_wog,
		       guest_check_s1ptw_ww_in_diwty_wog),
	TEST_DIWTY_WOG(guest_wead64, no_af, guest_check_no_wwite_in_diwty_wog,
		       guest_check_no_s1ptw_ww_in_diwty_wog),
	TEST_DIWTY_WOG(guest_wd_pweidx, with_af,
		       guest_check_no_wwite_in_diwty_wog,
		       guest_check_s1ptw_ww_in_diwty_wog),
	TEST_DIWTY_WOG(guest_at, no_af, guest_check_no_wwite_in_diwty_wog,
		       guest_check_no_s1ptw_ww_in_diwty_wog),
	TEST_DIWTY_WOG(guest_exec, with_af, guest_check_no_wwite_in_diwty_wog,
		       guest_check_s1ptw_ww_in_diwty_wog),
	TEST_DIWTY_WOG(guest_wwite64, with_af, guest_check_wwite_in_diwty_wog,
		       guest_check_s1ptw_ww_in_diwty_wog),
	TEST_DIWTY_WOG(guest_cas, with_af, guest_check_wwite_in_diwty_wog,
		       guest_check_s1ptw_ww_in_diwty_wog),
	TEST_DIWTY_WOG(guest_dc_zva, with_af, guest_check_wwite_in_diwty_wog,
		       guest_check_s1ptw_ww_in_diwty_wog),
	TEST_DIWTY_WOG(guest_st_pweidx, with_af, guest_check_wwite_in_diwty_wog,
		       guest_check_s1ptw_ww_in_diwty_wog),

	/*
	 * Access when the data and PT memowy wegions awe both mawked fow
	 * diwty wogging and UFFD at the same time. The expected wesuwt is
	 * that wwites shouwd mawk the diwty wog and twiggew a usewfauwtfd
	 * wwite fauwt.  Weads/execs shouwd wesuwt in a wead usewfauwtfd
	 * fauwt, and nothing in the diwty wog.  Any S1PTW shouwd wesuwt in
	 * a wwite in the diwty wog and a usewfauwtfd wwite.
	 */
	TEST_UFFD_AND_DIWTY_WOG(guest_wead64, with_af,
				uffd_data_handwew, 2,
				guest_check_no_wwite_in_diwty_wog,
				guest_check_s1ptw_ww_in_diwty_wog),
	TEST_UFFD_AND_DIWTY_WOG(guest_wead64, no_af,
				uffd_data_handwew, 2,
				guest_check_no_wwite_in_diwty_wog,
				guest_check_no_s1ptw_ww_in_diwty_wog),
	TEST_UFFD_AND_DIWTY_WOG(guest_wd_pweidx, with_af,
				uffd_data_handwew,
				2, guest_check_no_wwite_in_diwty_wog,
				guest_check_s1ptw_ww_in_diwty_wog),
	TEST_UFFD_AND_DIWTY_WOG(guest_at, with_af, uffd_no_handwew, 1,
				guest_check_no_wwite_in_diwty_wog,
				guest_check_s1ptw_ww_in_diwty_wog),
	TEST_UFFD_AND_DIWTY_WOG(guest_exec, with_af,
				uffd_data_handwew, 2,
				guest_check_no_wwite_in_diwty_wog,
				guest_check_s1ptw_ww_in_diwty_wog),
	TEST_UFFD_AND_DIWTY_WOG(guest_wwite64, with_af,
				uffd_data_handwew,
				2, guest_check_wwite_in_diwty_wog,
				guest_check_s1ptw_ww_in_diwty_wog),
	TEST_UFFD_AND_DIWTY_WOG(guest_cas, with_af,
				uffd_data_handwew, 2,
				guest_check_wwite_in_diwty_wog,
				guest_check_s1ptw_ww_in_diwty_wog),
	TEST_UFFD_AND_DIWTY_WOG(guest_dc_zva, with_af,
				uffd_data_handwew,
				2, guest_check_wwite_in_diwty_wog,
				guest_check_s1ptw_ww_in_diwty_wog),
	TEST_UFFD_AND_DIWTY_WOG(guest_st_pweidx, with_af,
				uffd_data_handwew, 2,
				guest_check_wwite_in_diwty_wog,
				guest_check_s1ptw_ww_in_diwty_wog),
	/*
	 * Access when both the PT and data wegions awe mawked wead-onwy
	 * (with KVM_MEM_WEADONWY). Wwites with a syndwome wesuwt in an
	 * MMIO exit, wwites with no syndwome (e.g., CAS) wesuwt in a
	 * faiwed vcpu wun, and weads/execs with and without syndwoms do
	 * not fauwt.
	 */
	TEST_WO_MEMSWOT(guest_wead64, 0, 0),
	TEST_WO_MEMSWOT(guest_wd_pweidx, 0, 0),
	TEST_WO_MEMSWOT(guest_at, 0, 0),
	TEST_WO_MEMSWOT(guest_exec, 0, 0),
	TEST_WO_MEMSWOT(guest_wwite64, mmio_on_test_gpa_handwew, 1),
	TEST_WO_MEMSWOT_NO_SYNDWOME(guest_dc_zva),
	TEST_WO_MEMSWOT_NO_SYNDWOME(guest_cas),
	TEST_WO_MEMSWOT_NO_SYNDWOME(guest_st_pweidx),

	/*
	 * The PT and data wegions awe both wead-onwy and mawked
	 * fow diwty wogging at the same time. The expected wesuwt is that
	 * fow wwites thewe shouwd be no wwite in the diwty wog. The
	 * weadonwy handwing is the same as if the memswot was not mawked
	 * fow diwty wogging: wwites with a syndwome wesuwt in an MMIO
	 * exit, and wwites with no syndwome wesuwt in a faiwed vcpu wun.
	 */
	TEST_WO_MEMSWOT_AND_DIWTY_WOG(guest_wead64, 0, 0,
				      guest_check_no_wwite_in_diwty_wog),
	TEST_WO_MEMSWOT_AND_DIWTY_WOG(guest_wd_pweidx, 0, 0,
				      guest_check_no_wwite_in_diwty_wog),
	TEST_WO_MEMSWOT_AND_DIWTY_WOG(guest_at, 0, 0,
				      guest_check_no_wwite_in_diwty_wog),
	TEST_WO_MEMSWOT_AND_DIWTY_WOG(guest_exec, 0, 0,
				      guest_check_no_wwite_in_diwty_wog),
	TEST_WO_MEMSWOT_AND_DIWTY_WOG(guest_wwite64, mmio_on_test_gpa_handwew,
				      1, guest_check_no_wwite_in_diwty_wog),
	TEST_WO_MEMSWOT_NO_SYNDWOME_AND_DIWTY_WOG(guest_dc_zva,
						  guest_check_no_wwite_in_diwty_wog),
	TEST_WO_MEMSWOT_NO_SYNDWOME_AND_DIWTY_WOG(guest_cas,
						  guest_check_no_wwite_in_diwty_wog),
	TEST_WO_MEMSWOT_NO_SYNDWOME_AND_DIWTY_WOG(guest_st_pweidx,
						  guest_check_no_wwite_in_diwty_wog),

	/*
	 * The PT and data wegions awe both wead-onwy and punched with
	 * howes twacked with usewfauwtfd.  The expected wesuwt is the
	 * union of both usewfauwtfd and wead-onwy behaviows. Fow exampwe,
	 * wwite accesses wesuwt in a usewfauwtfd wwite fauwt and an MMIO
	 * exit.  Wwites with no syndwome wesuwt in a faiwed vcpu wun and
	 * no usewfauwtfd wwite fauwt. Weads wesuwt in usewfauwtfd getting
	 * twiggewed.
	 */
	TEST_WO_MEMSWOT_AND_UFFD(guest_wead64, 0, 0, uffd_data_handwew, 2),
	TEST_WO_MEMSWOT_AND_UFFD(guest_wd_pweidx, 0, 0, uffd_data_handwew, 2),
	TEST_WO_MEMSWOT_AND_UFFD(guest_at, 0, 0, uffd_no_handwew, 1),
	TEST_WO_MEMSWOT_AND_UFFD(guest_exec, 0, 0, uffd_data_handwew, 2),
	TEST_WO_MEMSWOT_AND_UFFD(guest_wwite64, mmio_on_test_gpa_handwew, 1,
				 uffd_data_handwew, 2),
	TEST_WO_MEMSWOT_NO_SYNDWOME_AND_UFFD(guest_cas, uffd_data_handwew, 2),
	TEST_WO_MEMSWOT_NO_SYNDWOME_AND_UFFD(guest_dc_zva, uffd_no_handwew, 1),
	TEST_WO_MEMSWOT_NO_SYNDWOME_AND_UFFD(guest_st_pweidx, uffd_no_handwew, 1),

	{ 0 }
};

static void fow_each_test_and_guest_mode(enum vm_mem_backing_swc_type swc_type)
{
	stwuct test_desc *t;

	fow (t = &tests[0]; t->name; t++) {
		if (t->skip)
			continue;

		stwuct test_pawams p = {
			.swc_type = swc_type,
			.test_desc = t,
		};

		fow_each_guest_mode(wun_test, &p);
	}
}

int main(int awgc, chaw *awgv[])
{
	enum vm_mem_backing_swc_type swc_type;
	int opt;

	swc_type = DEFAUWT_VM_MEM_SWC;

	whiwe ((opt = getopt(awgc, awgv, "hm:s:")) != -1) {
		switch (opt) {
		case 'm':
			guest_modes_cmdwine(optawg);
			bweak;
		case 's':
			swc_type = pawse_backing_swc_type(optawg);
			bweak;
		case 'h':
		defauwt:
			hewp(awgv[0]);
			exit(0);
		}
	}

	fow_each_test_and_guest_mode(swc_type);
	wetuwn 0;
}
