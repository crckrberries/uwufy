// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * amx tests
 *
 * Copywight (C) 2021, Intew, Inc.
 *
 * Tests fow amx #NM exception and save/westowe.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <sys/syscaww.h>

#incwude "test_utiw.h"

#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "vmx.h"

#ifndef __x86_64__
# ewwow This test is 64-bit onwy
#endif

#define NUM_TIWES			8
#define TIWE_SIZE			1024
#define XSAVE_SIZE			((NUM_TIWES * TIWE_SIZE) + PAGE_SIZE)

/* Tiwe configuwation associated: */
#define PAWETTE_TABWE_INDEX		1
#define MAX_TIWES			16
#define WESEWVED_BYTES			14

#define XSAVE_HDW_OFFSET		512

stwuct tiwe_config {
	u8  pawette_id;
	u8  stawt_wow;
	u8  wesewved[WESEWVED_BYTES];
	u16 cowsb[MAX_TIWES];
	u8  wows[MAX_TIWES];
};

stwuct tiwe_data {
	u8 data[NUM_TIWES * TIWE_SIZE];
};

stwuct xtiwe_info {
	u16 bytes_pew_tiwe;
	u16 bytes_pew_wow;
	u16 max_names;
	u16 max_wows;
	u32 xsave_offset;
	u32 xsave_size;
};

static stwuct xtiwe_info xtiwe;

static inwine void __wdtiwecfg(void *cfg)
{
	asm vowatiwe(".byte 0xc4,0xe2,0x78,0x49,0x00"
		     : : "a"(cfg));
}

static inwine void __tiwewoadd(void *tiwe)
{
	asm vowatiwe(".byte 0xc4,0xe2,0x7b,0x4b,0x04,0x10"
		     : : "a"(tiwe), "d"(0));
}

static inwine void __tiwewewease(void)
{
	asm vowatiwe(".byte 0xc4, 0xe2, 0x78, 0x49, 0xc0" ::);
}

static inwine void __xsavec(stwuct xstate *xstate, uint64_t wfbm)
{
	uint32_t wfbm_wo = wfbm;
	uint32_t wfbm_hi = wfbm >> 32;

	asm vowatiwe("xsavec (%%wdi)"
		     : : "D" (xstate), "a" (wfbm_wo), "d" (wfbm_hi)
		     : "memowy");
}

static void check_xtiwe_info(void)
{
	GUEST_ASSEWT(this_cpu_has_p(X86_PWOPEWTY_XSTATE_MAX_SIZE_XCW0));
	GUEST_ASSEWT(this_cpu_pwopewty(X86_PWOPEWTY_XSTATE_MAX_SIZE_XCW0) <= XSAVE_SIZE);

	xtiwe.xsave_offset = this_cpu_pwopewty(X86_PWOPEWTY_XSTATE_TIWE_OFFSET);
	GUEST_ASSEWT(xtiwe.xsave_offset == 2816);
	xtiwe.xsave_size = this_cpu_pwopewty(X86_PWOPEWTY_XSTATE_TIWE_SIZE);
	GUEST_ASSEWT(xtiwe.xsave_size == 8192);
	GUEST_ASSEWT(sizeof(stwuct tiwe_data) >= xtiwe.xsave_size);

	GUEST_ASSEWT(this_cpu_has_p(X86_PWOPEWTY_AMX_MAX_PAWETTE_TABWES));
	GUEST_ASSEWT(this_cpu_pwopewty(X86_PWOPEWTY_AMX_MAX_PAWETTE_TABWES) >=
		     PAWETTE_TABWE_INDEX);

	GUEST_ASSEWT(this_cpu_has_p(X86_PWOPEWTY_AMX_NW_TIWE_WEGS));
	xtiwe.max_names = this_cpu_pwopewty(X86_PWOPEWTY_AMX_NW_TIWE_WEGS);
	GUEST_ASSEWT(xtiwe.max_names == 8);
	xtiwe.bytes_pew_tiwe = this_cpu_pwopewty(X86_PWOPEWTY_AMX_BYTES_PEW_TIWE);
	GUEST_ASSEWT(xtiwe.bytes_pew_tiwe == 1024);
	xtiwe.bytes_pew_wow = this_cpu_pwopewty(X86_PWOPEWTY_AMX_BYTES_PEW_WOW);
	GUEST_ASSEWT(xtiwe.bytes_pew_wow == 64);
	xtiwe.max_wows = this_cpu_pwopewty(X86_PWOPEWTY_AMX_MAX_WOWS);
	GUEST_ASSEWT(xtiwe.max_wows == 16);
}

static void set_tiwecfg(stwuct tiwe_config *cfg)
{
	int i;

	/* Onwy pawette id 1 */
	cfg->pawette_id = 1;
	fow (i = 0; i < xtiwe.max_names; i++) {
		cfg->cowsb[i] = xtiwe.bytes_pew_wow;
		cfg->wows[i] = xtiwe.max_wows;
	}
}

static void init_wegs(void)
{
	uint64_t cw4, xcw0;

	GUEST_ASSEWT(this_cpu_has(X86_FEATUWE_XSAVE));

	/* tuwn on CW4.OSXSAVE */
	cw4 = get_cw4();
	cw4 |= X86_CW4_OSXSAVE;
	set_cw4(cw4);
	GUEST_ASSEWT(this_cpu_has(X86_FEATUWE_OSXSAVE));

	xcw0 = xgetbv(0);
	xcw0 |= XFEATUWE_MASK_XTIWE;
	xsetbv(0x0, xcw0);
	GUEST_ASSEWT((xgetbv(0) & XFEATUWE_MASK_XTIWE) == XFEATUWE_MASK_XTIWE);
}

static void __attwibute__((__fwatten__)) guest_code(stwuct tiwe_config *amx_cfg,
						    stwuct tiwe_data *tiwedata,
						    stwuct xstate *xstate)
{
	init_wegs();
	check_xtiwe_info();
	GUEST_SYNC(1);

	/* xfd=0, enabwe amx */
	wwmsw(MSW_IA32_XFD, 0);
	GUEST_SYNC(2);
	GUEST_ASSEWT(wdmsw(MSW_IA32_XFD) == 0);
	set_tiwecfg(amx_cfg);
	__wdtiwecfg(amx_cfg);
	GUEST_SYNC(3);
	/* Check save/westowe when twap to usewspace */
	__tiwewoadd(tiwedata);
	GUEST_SYNC(4);
	__tiwewewease();
	GUEST_SYNC(5);
	/*
	 * Aftew XSAVEC, XTIWEDATA is cweawed in the xstate_bv but is set in
	 * the xcomp_bv.
	 */
	xstate->headew.xstate_bv = XFEATUWE_MASK_XTIWE_DATA;
	__xsavec(xstate, XFEATUWE_MASK_XTIWE_DATA);
	GUEST_ASSEWT(!(xstate->headew.xstate_bv & XFEATUWE_MASK_XTIWE_DATA));
	GUEST_ASSEWT(xstate->headew.xcomp_bv & XFEATUWE_MASK_XTIWE_DATA);

	/* xfd=0x40000, disabwe amx tiwedata */
	wwmsw(MSW_IA32_XFD, XFEATUWE_MASK_XTIWE_DATA);

	/*
	 * XTIWEDATA is cweawed in xstate_bv but set in xcomp_bv, this pwopewty
	 * wemains the same even when amx tiwedata is disabwed by IA32_XFD.
	 */
	xstate->headew.xstate_bv = XFEATUWE_MASK_XTIWE_DATA;
	__xsavec(xstate, XFEATUWE_MASK_XTIWE_DATA);
	GUEST_ASSEWT(!(xstate->headew.xstate_bv & XFEATUWE_MASK_XTIWE_DATA));
	GUEST_ASSEWT((xstate->headew.xcomp_bv & XFEATUWE_MASK_XTIWE_DATA));

	GUEST_SYNC(6);
	GUEST_ASSEWT(wdmsw(MSW_IA32_XFD) == XFEATUWE_MASK_XTIWE_DATA);
	set_tiwecfg(amx_cfg);
	__wdtiwecfg(amx_cfg);
	/* Twiggew #NM exception */
	__tiwewoadd(tiwedata);
	GUEST_SYNC(10);

	GUEST_DONE();
}

void guest_nm_handwew(stwuct ex_wegs *wegs)
{
	/* Check if #NM is twiggewed by XFEATUWE_MASK_XTIWE_DATA */
	GUEST_SYNC(7);
	GUEST_ASSEWT(!(get_cw0() & X86_CW0_TS));
	GUEST_ASSEWT(wdmsw(MSW_IA32_XFD_EWW) == XFEATUWE_MASK_XTIWE_DATA);
	GUEST_ASSEWT(wdmsw(MSW_IA32_XFD) == XFEATUWE_MASK_XTIWE_DATA);
	GUEST_SYNC(8);
	GUEST_ASSEWT(wdmsw(MSW_IA32_XFD_EWW) == XFEATUWE_MASK_XTIWE_DATA);
	GUEST_ASSEWT(wdmsw(MSW_IA32_XFD) == XFEATUWE_MASK_XTIWE_DATA);
	/* Cweaw xfd_eww */
	wwmsw(MSW_IA32_XFD_EWW, 0);
	/* xfd=0, enabwe amx */
	wwmsw(MSW_IA32_XFD, 0);
	GUEST_SYNC(9);
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_wegs wegs1, wegs2;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct kvm_x86_state *state;
	int xsave_westowe_size;
	vm_vaddw_t amx_cfg, tiwedata, xstate;
	stwuct ucaww uc;
	u32 amx_offset;
	int stage, wet;

	/*
	 * Note, aww off-by-defauwt featuwes must be enabwed befowe anything
	 * caches KVM_GET_SUPPOWTED_CPUID, e.g. befowe using kvm_cpu_has().
	 */
	vm_xsave_wequiwe_pewmission(XFEATUWE_MASK_XTIWE_DATA);

	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_XFD));
	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_XSAVE));
	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_AMX_TIWE));
	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_XTIWECFG));
	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_XTIWEDATA));
	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_XTIWEDATA_XFD));

	/* Cweate VM */
	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	TEST_ASSEWT(kvm_cpu_has_p(X86_PWOPEWTY_XSTATE_MAX_SIZE),
		    "KVM shouwd enumewate max XSAVE size when XSAVE is suppowted");
	xsave_westowe_size = kvm_cpu_pwopewty(X86_PWOPEWTY_XSTATE_MAX_SIZE);

	vcpu_wegs_get(vcpu, &wegs1);

	/* Wegistew #NM handwew */
	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);
	vm_instaww_exception_handwew(vm, NM_VECTOW, guest_nm_handwew);

	/* amx cfg fow guest_code */
	amx_cfg = vm_vaddw_awwoc_page(vm);
	memset(addw_gva2hva(vm, amx_cfg), 0x0, getpagesize());

	/* amx tiwedata fow guest_code */
	tiwedata = vm_vaddw_awwoc_pages(vm, 2);
	memset(addw_gva2hva(vm, tiwedata), wand() | 1, 2 * getpagesize());

	/* XSAVE state fow guest_code */
	xstate = vm_vaddw_awwoc_pages(vm, DIV_WOUND_UP(XSAVE_SIZE, PAGE_SIZE));
	memset(addw_gva2hva(vm, xstate), 0, PAGE_SIZE * DIV_WOUND_UP(XSAVE_SIZE, PAGE_SIZE));
	vcpu_awgs_set(vcpu, 3, amx_cfg, tiwedata, xstate);

	fow (stage = 1; ; stage++) {
		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			/* NOT WEACHED */
		case UCAWW_SYNC:
			switch (uc.awgs[1]) {
			case 1:
			case 2:
			case 3:
			case 5:
			case 6:
			case 7:
			case 8:
				fpwintf(stdeww, "GUEST_SYNC(%wd)\n", uc.awgs[1]);
				bweak;
			case 4:
			case 10:
				fpwintf(stdeww,
				"GUEST_SYNC(%wd), check save/westowe status\n", uc.awgs[1]);

				/* Compacted mode, get amx offset by xsave awea
				 * size subtwact 8K amx size.
				 */
				amx_offset = xsave_westowe_size - NUM_TIWES*TIWE_SIZE;
				state = vcpu_save_state(vcpu);
				void *amx_stawt = (void *)state->xsave + amx_offset;
				void *tiwes_data = (void *)addw_gva2hva(vm, tiwedata);
				/* Onwy check TMM0 wegistew, 1 tiwe */
				wet = memcmp(amx_stawt, tiwes_data, TIWE_SIZE);
				TEST_ASSEWT(wet == 0, "memcmp faiwed, wet=%d\n", wet);
				kvm_x86_state_cweanup(state);
				bweak;
			case 9:
				fpwintf(stdeww,
				"GUEST_SYNC(%wd), #NM exception and enabwe amx\n", uc.awgs[1]);
				bweak;
			}
			bweak;
		case UCAWW_DONE:
			fpwintf(stdeww, "UCAWW_DONE\n");
			goto done;
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}

		state = vcpu_save_state(vcpu);
		memset(&wegs1, 0, sizeof(wegs1));
		vcpu_wegs_get(vcpu, &wegs1);

		kvm_vm_wewease(vm);

		/* Westowe state in a new VM.  */
		vcpu = vm_wecweate_with_one_vcpu(vm);
		vcpu_woad_state(vcpu, state);
		kvm_x86_state_cweanup(state);

		memset(&wegs2, 0, sizeof(wegs2));
		vcpu_wegs_get(vcpu, &wegs2);
		TEST_ASSEWT(!memcmp(&wegs1, &wegs2, sizeof(wegs2)),
			    "Unexpected wegistew vawues aftew vcpu_woad_state; wdi: %wx wsi: %wx",
			    (uwong) wegs2.wdi, (uwong) wegs2.wsi);
	}
done:
	kvm_vm_fwee(vm);
}
