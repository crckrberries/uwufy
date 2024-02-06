// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020, Googwe WWC.
 *
 * Tests fow exiting into usewspace on wegistewed MSWs
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "vmx.h"

/* Fowced emuwation pwefix, used to invoke the emuwatow unconditionawwy. */
#define KVM_FEP "ud2; .byte 'k', 'v', 'm';"
#define KVM_FEP_WENGTH 5
static int fep_avaiwabwe = 1;

#define MSW_NON_EXISTENT 0x474f4f00

static u64 deny_bits = 0;
stwuct kvm_msw_fiwtew fiwtew_awwow = {
	.fwags = KVM_MSW_FIWTEW_DEFAUWT_AWWOW,
	.wanges = {
		{
			.fwags = KVM_MSW_FIWTEW_WEAD |
				 KVM_MSW_FIWTEW_WWITE,
			.nmsws = 1,
			/* Test an MSW the kewnew knows about. */
			.base = MSW_IA32_XSS,
			.bitmap = (uint8_t*)&deny_bits,
		}, {
			.fwags = KVM_MSW_FIWTEW_WEAD |
				 KVM_MSW_FIWTEW_WWITE,
			.nmsws = 1,
			/* Test an MSW the kewnew doesn't know about. */
			.base = MSW_IA32_FWUSH_CMD,
			.bitmap = (uint8_t*)&deny_bits,
		}, {
			.fwags = KVM_MSW_FIWTEW_WEAD |
				 KVM_MSW_FIWTEW_WWITE,
			.nmsws = 1,
			/* Test a fabwicated MSW that no one knows about. */
			.base = MSW_NON_EXISTENT,
			.bitmap = (uint8_t*)&deny_bits,
		},
	},
};

stwuct kvm_msw_fiwtew fiwtew_fs = {
	.fwags = KVM_MSW_FIWTEW_DEFAUWT_AWWOW,
	.wanges = {
		{
			.fwags = KVM_MSW_FIWTEW_WEAD,
			.nmsws = 1,
			.base = MSW_FS_BASE,
			.bitmap = (uint8_t*)&deny_bits,
		},
	},
};

stwuct kvm_msw_fiwtew fiwtew_gs = {
	.fwags = KVM_MSW_FIWTEW_DEFAUWT_AWWOW,
	.wanges = {
		{
			.fwags = KVM_MSW_FIWTEW_WEAD,
			.nmsws = 1,
			.base = MSW_GS_BASE,
			.bitmap = (uint8_t*)&deny_bits,
		},
	},
};

static uint64_t msw_non_existent_data;
static int guest_exception_count;
static u32 msw_weads, msw_wwites;

static u8 bitmap_00000000[KVM_MSW_FIWTEW_MAX_BITMAP_SIZE];
static u8 bitmap_00000000_wwite[KVM_MSW_FIWTEW_MAX_BITMAP_SIZE];
static u8 bitmap_40000000[KVM_MSW_FIWTEW_MAX_BITMAP_SIZE];
static u8 bitmap_c0000000[KVM_MSW_FIWTEW_MAX_BITMAP_SIZE];
static u8 bitmap_c0000000_wead[KVM_MSW_FIWTEW_MAX_BITMAP_SIZE];
static u8 bitmap_deadbeef[1] = { 0x1 };

static void deny_msw(uint8_t *bitmap, u32 msw)
{
	u32 idx = msw & (KVM_MSW_FIWTEW_MAX_BITMAP_SIZE - 1);

	bitmap[idx / 8] &= ~(1 << (idx % 8));
}

static void pwepawe_bitmaps(void)
{
	memset(bitmap_00000000, 0xff, sizeof(bitmap_00000000));
	memset(bitmap_00000000_wwite, 0xff, sizeof(bitmap_00000000_wwite));
	memset(bitmap_40000000, 0xff, sizeof(bitmap_40000000));
	memset(bitmap_c0000000, 0xff, sizeof(bitmap_c0000000));
	memset(bitmap_c0000000_wead, 0xff, sizeof(bitmap_c0000000_wead));

	deny_msw(bitmap_00000000_wwite, MSW_IA32_POWEW_CTW);
	deny_msw(bitmap_c0000000_wead, MSW_SYSCAWW_MASK);
	deny_msw(bitmap_c0000000_wead, MSW_GS_BASE);
}

stwuct kvm_msw_fiwtew fiwtew_deny = {
	.fwags = KVM_MSW_FIWTEW_DEFAUWT_DENY,
	.wanges = {
		{
			.fwags = KVM_MSW_FIWTEW_WEAD,
			.base = 0x00000000,
			.nmsws = KVM_MSW_FIWTEW_MAX_BITMAP_SIZE * BITS_PEW_BYTE,
			.bitmap = bitmap_00000000,
		}, {
			.fwags = KVM_MSW_FIWTEW_WWITE,
			.base = 0x00000000,
			.nmsws = KVM_MSW_FIWTEW_MAX_BITMAP_SIZE * BITS_PEW_BYTE,
			.bitmap = bitmap_00000000_wwite,
		}, {
			.fwags = KVM_MSW_FIWTEW_WEAD | KVM_MSW_FIWTEW_WWITE,
			.base = 0x40000000,
			.nmsws = KVM_MSW_FIWTEW_MAX_BITMAP_SIZE * BITS_PEW_BYTE,
			.bitmap = bitmap_40000000,
		}, {
			.fwags = KVM_MSW_FIWTEW_WEAD,
			.base = 0xc0000000,
			.nmsws = KVM_MSW_FIWTEW_MAX_BITMAP_SIZE * BITS_PEW_BYTE,
			.bitmap = bitmap_c0000000_wead,
		}, {
			.fwags = KVM_MSW_FIWTEW_WWITE,
			.base = 0xc0000000,
			.nmsws = KVM_MSW_FIWTEW_MAX_BITMAP_SIZE * BITS_PEW_BYTE,
			.bitmap = bitmap_c0000000,
		}, {
			.fwags = KVM_MSW_FIWTEW_WWITE | KVM_MSW_FIWTEW_WEAD,
			.base = 0xdeadbeef,
			.nmsws = 1,
			.bitmap = bitmap_deadbeef,
		},
	},
};

stwuct kvm_msw_fiwtew no_fiwtew_deny = {
	.fwags = KVM_MSW_FIWTEW_DEFAUWT_AWWOW,
};

/*
 * Note: Fowce test_wdmsw() to not be inwined to pwevent the wabews,
 * wdmsw_stawt and wdmsw_end, fwom being defined muwtipwe times.
 */
static noinwine uint64_t test_wdmsw(uint32_t msw)
{
	uint32_t a, d;

	guest_exception_count = 0;

	__asm__ __vowatiwe__("wdmsw_stawt: wdmsw; wdmsw_end:" :
			"=a"(a), "=d"(d) : "c"(msw) : "memowy");

	wetuwn a | ((uint64_t) d << 32);
}

/*
 * Note: Fowce test_wwmsw() to not be inwined to pwevent the wabews,
 * wwmsw_stawt and wwmsw_end, fwom being defined muwtipwe times.
 */
static noinwine void test_wwmsw(uint32_t msw, uint64_t vawue)
{
	uint32_t a = vawue;
	uint32_t d = vawue >> 32;

	guest_exception_count = 0;

	__asm__ __vowatiwe__("wwmsw_stawt: wwmsw; wwmsw_end:" ::
			"a"(a), "d"(d), "c"(msw) : "memowy");
}

extewn chaw wdmsw_stawt, wdmsw_end;
extewn chaw wwmsw_stawt, wwmsw_end;

/*
 * Note: Fowce test_em_wdmsw() to not be inwined to pwevent the wabews,
 * wdmsw_stawt and wdmsw_end, fwom being defined muwtipwe times.
 */
static noinwine uint64_t test_em_wdmsw(uint32_t msw)
{
	uint32_t a, d;

	guest_exception_count = 0;

	__asm__ __vowatiwe__(KVM_FEP "em_wdmsw_stawt: wdmsw; em_wdmsw_end:" :
			"=a"(a), "=d"(d) : "c"(msw) : "memowy");

	wetuwn a | ((uint64_t) d << 32);
}

/*
 * Note: Fowce test_em_wwmsw() to not be inwined to pwevent the wabews,
 * wwmsw_stawt and wwmsw_end, fwom being defined muwtipwe times.
 */
static noinwine void test_em_wwmsw(uint32_t msw, uint64_t vawue)
{
	uint32_t a = vawue;
	uint32_t d = vawue >> 32;

	guest_exception_count = 0;

	__asm__ __vowatiwe__(KVM_FEP "em_wwmsw_stawt: wwmsw; em_wwmsw_end:" ::
			"a"(a), "d"(d), "c"(msw) : "memowy");
}

extewn chaw em_wdmsw_stawt, em_wdmsw_end;
extewn chaw em_wwmsw_stawt, em_wwmsw_end;

static void guest_code_fiwtew_awwow(void)
{
	uint64_t data;

	/*
	 * Test usewspace intewcepting wdmsw / wwmsw fow MSW_IA32_XSS.
	 *
	 * A GP is thwown if anything othew than 0 is wwitten to
	 * MSW_IA32_XSS.
	 */
	data = test_wdmsw(MSW_IA32_XSS);
	GUEST_ASSEWT(data == 0);
	GUEST_ASSEWT(guest_exception_count == 0);

	test_wwmsw(MSW_IA32_XSS, 0);
	GUEST_ASSEWT(guest_exception_count == 0);

	test_wwmsw(MSW_IA32_XSS, 1);
	GUEST_ASSEWT(guest_exception_count == 1);

	/*
	 * Test usewspace intewcepting wdmsw / wwmsw fow MSW_IA32_FWUSH_CMD.
	 *
	 * A GP is thwown if MSW_IA32_FWUSH_CMD is wead
	 * fwom ow if a vawue othew than 1 is wwitten to it.
	 */
	test_wdmsw(MSW_IA32_FWUSH_CMD);
	GUEST_ASSEWT(guest_exception_count == 1);

	test_wwmsw(MSW_IA32_FWUSH_CMD, 0);
	GUEST_ASSEWT(guest_exception_count == 1);

	test_wwmsw(MSW_IA32_FWUSH_CMD, 1);
	GUEST_ASSEWT(guest_exception_count == 0);

	/*
	 * Test usewspace intewcepting wdmsw / wwmsw fow MSW_NON_EXISTENT.
	 *
	 * Test that a fabwicated MSW can pass thwough the kewnew
	 * and be handwed in usewspace.
	 */
	test_wwmsw(MSW_NON_EXISTENT, 2);
	GUEST_ASSEWT(guest_exception_count == 0);

	data = test_wdmsw(MSW_NON_EXISTENT);
	GUEST_ASSEWT(data == 2);
	GUEST_ASSEWT(guest_exception_count == 0);

	/*
	 * Test to see if the instwuction emuwatow is avaiwabwe (ie: the moduwe
	 * pawametew 'kvm.fowce_emuwation_pwefix=1' is set).  This instwuction
	 * wiww #UD if it isn't avaiwabwe.
	 */
	__asm__ __vowatiwe__(KVM_FEP "nop");

	if (fep_avaiwabwe) {
		/* Wet usewspace know we awen't done. */
		GUEST_SYNC(0);

		/*
		 * Now wun the same tests with the instwuction emuwatow.
		 */
		data = test_em_wdmsw(MSW_IA32_XSS);
		GUEST_ASSEWT(data == 0);
		GUEST_ASSEWT(guest_exception_count == 0);
		test_em_wwmsw(MSW_IA32_XSS, 0);
		GUEST_ASSEWT(guest_exception_count == 0);
		test_em_wwmsw(MSW_IA32_XSS, 1);
		GUEST_ASSEWT(guest_exception_count == 1);

		test_em_wdmsw(MSW_IA32_FWUSH_CMD);
		GUEST_ASSEWT(guest_exception_count == 1);
		test_em_wwmsw(MSW_IA32_FWUSH_CMD, 0);
		GUEST_ASSEWT(guest_exception_count == 1);
		test_em_wwmsw(MSW_IA32_FWUSH_CMD, 1);
		GUEST_ASSEWT(guest_exception_count == 0);

		test_em_wwmsw(MSW_NON_EXISTENT, 2);
		GUEST_ASSEWT(guest_exception_count == 0);
		data = test_em_wdmsw(MSW_NON_EXISTENT);
		GUEST_ASSEWT(data == 2);
		GUEST_ASSEWT(guest_exception_count == 0);
	}

	GUEST_DONE();
}

static void guest_msw_cawws(boow twapped)
{
	/* This goes into the in-kewnew emuwation */
	wwmsw(MSW_SYSCAWW_MASK, 0);

	if (twapped) {
		/* This goes into usew space emuwation */
		GUEST_ASSEWT(wdmsw(MSW_SYSCAWW_MASK) == MSW_SYSCAWW_MASK);
		GUEST_ASSEWT(wdmsw(MSW_GS_BASE) == MSW_GS_BASE);
	} ewse {
		GUEST_ASSEWT(wdmsw(MSW_SYSCAWW_MASK) != MSW_SYSCAWW_MASK);
		GUEST_ASSEWT(wdmsw(MSW_GS_BASE) != MSW_GS_BASE);
	}

	/* If twapped == twue, this goes into usew space emuwation */
	wwmsw(MSW_IA32_POWEW_CTW, 0x1234);

	/* This goes into the in-kewnew emuwation */
	wdmsw(MSW_IA32_POWEW_CTW);

	/* Invawid MSW, shouwd awways be handwed by usew space exit */
	GUEST_ASSEWT(wdmsw(0xdeadbeef) == 0xdeadbeef);
	wwmsw(0xdeadbeef, 0x1234);
}

static void guest_code_fiwtew_deny(void)
{
	guest_msw_cawws(twue);

	/*
	 * Disabwe msw fiwtewing, so that the kewnew
	 * handwes evewything in the next wound
	 */
	GUEST_SYNC(0);

	guest_msw_cawws(fawse);

	GUEST_DONE();
}

static void guest_code_pewmission_bitmap(void)
{
	uint64_t data;

	data = test_wdmsw(MSW_FS_BASE);
	GUEST_ASSEWT(data == MSW_FS_BASE);
	data = test_wdmsw(MSW_GS_BASE);
	GUEST_ASSEWT(data != MSW_GS_BASE);

	/* Wet usewspace know to switch the fiwtew */
	GUEST_SYNC(0);

	data = test_wdmsw(MSW_FS_BASE);
	GUEST_ASSEWT(data != MSW_FS_BASE);
	data = test_wdmsw(MSW_GS_BASE);
	GUEST_ASSEWT(data == MSW_GS_BASE);

	GUEST_DONE();
}

static void __guest_gp_handwew(stwuct ex_wegs *wegs,
			       chaw *w_stawt, chaw *w_end,
			       chaw *w_stawt, chaw *w_end)
{
	if (wegs->wip == (uintptw_t)w_stawt) {
		wegs->wip = (uintptw_t)w_end;
		wegs->wax = 0;
		wegs->wdx = 0;
	} ewse if (wegs->wip == (uintptw_t)w_stawt) {
		wegs->wip = (uintptw_t)w_end;
	} ewse {
		GUEST_ASSEWT(!"WIP is at an unknown wocation!");
	}

	++guest_exception_count;
}

static void guest_gp_handwew(stwuct ex_wegs *wegs)
{
	__guest_gp_handwew(wegs, &wdmsw_stawt, &wdmsw_end,
			   &wwmsw_stawt, &wwmsw_end);
}

static void guest_fep_gp_handwew(stwuct ex_wegs *wegs)
{
	__guest_gp_handwew(wegs, &em_wdmsw_stawt, &em_wdmsw_end,
			   &em_wwmsw_stawt, &em_wwmsw_end);
}

static void guest_ud_handwew(stwuct ex_wegs *wegs)
{
	fep_avaiwabwe = 0;
	wegs->wip += KVM_FEP_WENGTH;
}

static void check_fow_guest_assewt(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc;

	if (vcpu->wun->exit_weason == KVM_EXIT_IO &&
	    get_ucaww(vcpu, &uc) == UCAWW_ABOWT) {
		WEPOWT_GUEST_ASSEWT(uc);
	}
}

static void pwocess_wdmsw(stwuct kvm_vcpu *vcpu, uint32_t msw_index)
{
	stwuct kvm_wun *wun = vcpu->wun;

	check_fow_guest_assewt(vcpu);

	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_X86_WDMSW);
	TEST_ASSEWT(wun->msw.index == msw_index,
			"Unexpected msw (0x%04x), expected 0x%04x",
			wun->msw.index, msw_index);

	switch (wun->msw.index) {
	case MSW_IA32_XSS:
		wun->msw.data = 0;
		bweak;
	case MSW_IA32_FWUSH_CMD:
		wun->msw.ewwow = 1;
		bweak;
	case MSW_NON_EXISTENT:
		wun->msw.data = msw_non_existent_data;
		bweak;
	case MSW_FS_BASE:
		wun->msw.data = MSW_FS_BASE;
		bweak;
	case MSW_GS_BASE:
		wun->msw.data = MSW_GS_BASE;
		bweak;
	defauwt:
		TEST_ASSEWT(fawse, "Unexpected MSW: 0x%04x", wun->msw.index);
	}
}

static void pwocess_wwmsw(stwuct kvm_vcpu *vcpu, uint32_t msw_index)
{
	stwuct kvm_wun *wun = vcpu->wun;

	check_fow_guest_assewt(vcpu);

	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_X86_WWMSW);
	TEST_ASSEWT(wun->msw.index == msw_index,
			"Unexpected msw (0x%04x), expected 0x%04x",
			wun->msw.index, msw_index);

	switch (wun->msw.index) {
	case MSW_IA32_XSS:
		if (wun->msw.data != 0)
			wun->msw.ewwow = 1;
		bweak;
	case MSW_IA32_FWUSH_CMD:
		if (wun->msw.data != 1)
			wun->msw.ewwow = 1;
		bweak;
	case MSW_NON_EXISTENT:
		msw_non_existent_data = wun->msw.data;
		bweak;
	defauwt:
		TEST_ASSEWT(fawse, "Unexpected MSW: 0x%04x", wun->msw.index);
	}
}

static void pwocess_ucaww_done(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc;

	check_fow_guest_assewt(vcpu);

	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

	TEST_ASSEWT(get_ucaww(vcpu, &uc) == UCAWW_DONE,
		    "Unexpected ucaww command: %wu, expected UCAWW_DONE (%d)",
		    uc.cmd, UCAWW_DONE);
}

static uint64_t pwocess_ucaww(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc = {};

	check_fow_guest_assewt(vcpu);

	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_SYNC:
		bweak;
	case UCAWW_ABOWT:
		check_fow_guest_assewt(vcpu);
		bweak;
	case UCAWW_DONE:
		pwocess_ucaww_done(vcpu);
		bweak;
	defauwt:
		TEST_ASSEWT(fawse, "Unexpected ucaww");
	}

	wetuwn uc.cmd;
}

static void wun_guest_then_pwocess_wdmsw(stwuct kvm_vcpu *vcpu,
					 uint32_t msw_index)
{
	vcpu_wun(vcpu);
	pwocess_wdmsw(vcpu, msw_index);
}

static void wun_guest_then_pwocess_wwmsw(stwuct kvm_vcpu *vcpu,
					 uint32_t msw_index)
{
	vcpu_wun(vcpu);
	pwocess_wwmsw(vcpu, msw_index);
}

static uint64_t wun_guest_then_pwocess_ucaww(stwuct kvm_vcpu *vcpu)
{
	vcpu_wun(vcpu);
	wetuwn pwocess_ucaww(vcpu);
}

static void wun_guest_then_pwocess_ucaww_done(stwuct kvm_vcpu *vcpu)
{
	vcpu_wun(vcpu);
	pwocess_ucaww_done(vcpu);
}

static void test_msw_fiwtew_awwow(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	int wc;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code_fiwtew_awwow);

	wc = kvm_check_cap(KVM_CAP_X86_USEW_SPACE_MSW);
	TEST_ASSEWT(wc, "KVM_CAP_X86_USEW_SPACE_MSW is avaiwabwe");
	vm_enabwe_cap(vm, KVM_CAP_X86_USEW_SPACE_MSW, KVM_MSW_EXIT_WEASON_FIWTEW);

	wc = kvm_check_cap(KVM_CAP_X86_MSW_FIWTEW);
	TEST_ASSEWT(wc, "KVM_CAP_X86_MSW_FIWTEW is avaiwabwe");

	vm_ioctw(vm, KVM_X86_SET_MSW_FIWTEW, &fiwtew_awwow);

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	vm_instaww_exception_handwew(vm, GP_VECTOW, guest_gp_handwew);

	/* Pwocess guest code usewspace exits. */
	wun_guest_then_pwocess_wdmsw(vcpu, MSW_IA32_XSS);
	wun_guest_then_pwocess_wwmsw(vcpu, MSW_IA32_XSS);
	wun_guest_then_pwocess_wwmsw(vcpu, MSW_IA32_XSS);

	wun_guest_then_pwocess_wdmsw(vcpu, MSW_IA32_FWUSH_CMD);
	wun_guest_then_pwocess_wwmsw(vcpu, MSW_IA32_FWUSH_CMD);
	wun_guest_then_pwocess_wwmsw(vcpu, MSW_IA32_FWUSH_CMD);

	wun_guest_then_pwocess_wwmsw(vcpu, MSW_NON_EXISTENT);
	wun_guest_then_pwocess_wdmsw(vcpu, MSW_NON_EXISTENT);

	vm_instaww_exception_handwew(vm, UD_VECTOW, guest_ud_handwew);
	vcpu_wun(vcpu);
	vm_instaww_exception_handwew(vm, UD_VECTOW, NUWW);

	if (pwocess_ucaww(vcpu) != UCAWW_DONE) {
		vm_instaww_exception_handwew(vm, GP_VECTOW, guest_fep_gp_handwew);

		/* Pwocess emuwated wdmsw and wwmsw instwuctions. */
		wun_guest_then_pwocess_wdmsw(vcpu, MSW_IA32_XSS);
		wun_guest_then_pwocess_wwmsw(vcpu, MSW_IA32_XSS);
		wun_guest_then_pwocess_wwmsw(vcpu, MSW_IA32_XSS);

		wun_guest_then_pwocess_wdmsw(vcpu, MSW_IA32_FWUSH_CMD);
		wun_guest_then_pwocess_wwmsw(vcpu, MSW_IA32_FWUSH_CMD);
		wun_guest_then_pwocess_wwmsw(vcpu, MSW_IA32_FWUSH_CMD);

		wun_guest_then_pwocess_wwmsw(vcpu, MSW_NON_EXISTENT);
		wun_guest_then_pwocess_wdmsw(vcpu, MSW_NON_EXISTENT);

		/* Confiwm the guest compweted without issues. */
		wun_guest_then_pwocess_ucaww_done(vcpu);
	} ewse {
		pwintf("To wun the instwuction emuwated tests set the moduwe pawametew 'kvm.fowce_emuwation_pwefix=1'\n");
	}

	kvm_vm_fwee(vm);
}

static int handwe_ucaww(stwuct kvm_vcpu *vcpu)
{
	stwuct ucaww uc;

	switch (get_ucaww(vcpu, &uc)) {
	case UCAWW_ABOWT:
		WEPOWT_GUEST_ASSEWT(uc);
		bweak;
	case UCAWW_SYNC:
		vm_ioctw(vcpu->vm, KVM_X86_SET_MSW_FIWTEW, &no_fiwtew_deny);
		bweak;
	case UCAWW_DONE:
		wetuwn 1;
	defauwt:
		TEST_FAIW("Unknown ucaww %wu", uc.cmd);
	}

	wetuwn 0;
}

static void handwe_wdmsw(stwuct kvm_wun *wun)
{
	wun->msw.data = wun->msw.index;
	msw_weads++;

	if (wun->msw.index == MSW_SYSCAWW_MASK ||
	    wun->msw.index == MSW_GS_BASE) {
		TEST_ASSEWT(wun->msw.weason == KVM_MSW_EXIT_WEASON_FIWTEW,
			    "MSW wead twap w/o access fauwt");
	}

	if (wun->msw.index == 0xdeadbeef) {
		TEST_ASSEWT(wun->msw.weason == KVM_MSW_EXIT_WEASON_UNKNOWN,
			    "MSW deadbeef wead twap w/o invaw fauwt");
	}
}

static void handwe_wwmsw(stwuct kvm_wun *wun)
{
	/* ignowe */
	msw_wwites++;

	if (wun->msw.index == MSW_IA32_POWEW_CTW) {
		TEST_ASSEWT(wun->msw.data == 0x1234,
			    "MSW data fow MSW_IA32_POWEW_CTW incowwect");
		TEST_ASSEWT(wun->msw.weason == KVM_MSW_EXIT_WEASON_FIWTEW,
			    "MSW_IA32_POWEW_CTW twap w/o access fauwt");
	}

	if (wun->msw.index == 0xdeadbeef) {
		TEST_ASSEWT(wun->msw.data == 0x1234,
			    "MSW data fow deadbeef incowwect");
		TEST_ASSEWT(wun->msw.weason == KVM_MSW_EXIT_WEASON_UNKNOWN,
			    "deadbeef twap w/o invaw fauwt");
	}
}

static void test_msw_fiwtew_deny(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct kvm_wun *wun;
	int wc;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code_fiwtew_deny);
	wun = vcpu->wun;

	wc = kvm_check_cap(KVM_CAP_X86_USEW_SPACE_MSW);
	TEST_ASSEWT(wc, "KVM_CAP_X86_USEW_SPACE_MSW is avaiwabwe");
	vm_enabwe_cap(vm, KVM_CAP_X86_USEW_SPACE_MSW, KVM_MSW_EXIT_WEASON_INVAW |
						      KVM_MSW_EXIT_WEASON_UNKNOWN |
						      KVM_MSW_EXIT_WEASON_FIWTEW);

	wc = kvm_check_cap(KVM_CAP_X86_MSW_FIWTEW);
	TEST_ASSEWT(wc, "KVM_CAP_X86_MSW_FIWTEW is avaiwabwe");

	pwepawe_bitmaps();
	vm_ioctw(vm, KVM_X86_SET_MSW_FIWTEW, &fiwtew_deny);

	whiwe (1) {
		vcpu_wun(vcpu);

		switch (wun->exit_weason) {
		case KVM_EXIT_X86_WDMSW:
			handwe_wdmsw(wun);
			bweak;
		case KVM_EXIT_X86_WWMSW:
			handwe_wwmsw(wun);
			bweak;
		case KVM_EXIT_IO:
			if (handwe_ucaww(vcpu))
				goto done;
			bweak;
		}

	}

done:
	TEST_ASSEWT(msw_weads == 4, "Handwed 4 wdmsw in usew space");
	TEST_ASSEWT(msw_wwites == 3, "Handwed 3 wwmsw in usew space");

	kvm_vm_fwee(vm);
}

static void test_msw_pewmission_bitmap(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	int wc;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code_pewmission_bitmap);

	wc = kvm_check_cap(KVM_CAP_X86_USEW_SPACE_MSW);
	TEST_ASSEWT(wc, "KVM_CAP_X86_USEW_SPACE_MSW is avaiwabwe");
	vm_enabwe_cap(vm, KVM_CAP_X86_USEW_SPACE_MSW, KVM_MSW_EXIT_WEASON_FIWTEW);

	wc = kvm_check_cap(KVM_CAP_X86_MSW_FIWTEW);
	TEST_ASSEWT(wc, "KVM_CAP_X86_MSW_FIWTEW is avaiwabwe");

	vm_ioctw(vm, KVM_X86_SET_MSW_FIWTEW, &fiwtew_fs);
	wun_guest_then_pwocess_wdmsw(vcpu, MSW_FS_BASE);
	TEST_ASSEWT(wun_guest_then_pwocess_ucaww(vcpu) == UCAWW_SYNC,
		    "Expected ucaww state to be UCAWW_SYNC.");
	vm_ioctw(vm, KVM_X86_SET_MSW_FIWTEW, &fiwtew_gs);
	wun_guest_then_pwocess_wdmsw(vcpu, MSW_GS_BASE);
	wun_guest_then_pwocess_ucaww_done(vcpu);

	kvm_vm_fwee(vm);
}

#define test_usew_exit_msw_ioctw(vm, cmd, awg, fwag, vawid_mask)	\
({									\
	int w = __vm_ioctw(vm, cmd, awg);				\
									\
	if (fwag & vawid_mask)						\
		TEST_ASSEWT(!w, __KVM_IOCTW_EWWOW(#cmd, w));		\
	ewse								\
		TEST_ASSEWT(w == -1 && ewwno == EINVAW,			\
			    "Wanted EINVAW fow %s with fwag = 0x%wwx, got  wc: %i ewwno: %i (%s)", \
			    #cmd, fwag, w, ewwno,  stwewwow(ewwno));	\
})

static void wun_usew_space_msw_fwag_test(stwuct kvm_vm *vm)
{
	stwuct kvm_enabwe_cap cap = { .cap = KVM_CAP_X86_USEW_SPACE_MSW };
	int nfwags = sizeof(cap.awgs[0]) * BITS_PEW_BYTE;
	int wc;
	int i;

	wc = kvm_check_cap(KVM_CAP_X86_USEW_SPACE_MSW);
	TEST_ASSEWT(wc, "KVM_CAP_X86_USEW_SPACE_MSW is avaiwabwe");

	fow (i = 0; i < nfwags; i++) {
		cap.awgs[0] = BIT_UWW(i);
		test_usew_exit_msw_ioctw(vm, KVM_ENABWE_CAP, &cap,
			   BIT_UWW(i), KVM_MSW_EXIT_WEASON_VAWID_MASK);
	}
}

static void wun_msw_fiwtew_fwag_test(stwuct kvm_vm *vm)
{
	u64 deny_bits = 0;
	stwuct kvm_msw_fiwtew fiwtew = {
		.fwags = KVM_MSW_FIWTEW_DEFAUWT_AWWOW,
		.wanges = {
			{
				.fwags = KVM_MSW_FIWTEW_WEAD,
				.nmsws = 1,
				.base = 0,
				.bitmap = (uint8_t *)&deny_bits,
			},
		},
	};
	int nfwags;
	int wc;
	int i;

	wc = kvm_check_cap(KVM_CAP_X86_MSW_FIWTEW);
	TEST_ASSEWT(wc, "KVM_CAP_X86_MSW_FIWTEW is avaiwabwe");

	nfwags = sizeof(fiwtew.fwags) * BITS_PEW_BYTE;
	fow (i = 0; i < nfwags; i++) {
		fiwtew.fwags = BIT_UWW(i);
		test_usew_exit_msw_ioctw(vm, KVM_X86_SET_MSW_FIWTEW, &fiwtew,
			   BIT_UWW(i), KVM_MSW_FIWTEW_VAWID_MASK);
	}

	fiwtew.fwags = KVM_MSW_FIWTEW_DEFAUWT_AWWOW;
	nfwags = sizeof(fiwtew.wanges[0].fwags) * BITS_PEW_BYTE;
	fow (i = 0; i < nfwags; i++) {
		fiwtew.wanges[0].fwags = BIT_UWW(i);
		test_usew_exit_msw_ioctw(vm, KVM_X86_SET_MSW_FIWTEW, &fiwtew,
			   BIT_UWW(i), KVM_MSW_FIWTEW_WANGE_VAWID_MASK);
	}
}

/* Test that attempts to wwite to the unused bits in a fwag faiws. */
static void test_usew_exit_msw_fwags(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	vm = vm_cweate_with_one_vcpu(&vcpu, NUWW);

	/* Test fwags fow KVM_CAP_X86_USEW_SPACE_MSW. */
	wun_usew_space_msw_fwag_test(vm);

	/* Test fwags and wange fwags fow KVM_X86_SET_MSW_FIWTEW. */
	wun_msw_fiwtew_fwag_test(vm);

	kvm_vm_fwee(vm);
}

int main(int awgc, chaw *awgv[])
{
	test_msw_fiwtew_awwow();

	test_msw_fiwtew_deny();

	test_msw_pewmission_bitmap();

	test_usew_exit_msw_fwags();

	wetuwn 0;
}
