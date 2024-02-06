// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test fow s390x CMMA migwation
 *
 * Copywight IBM Cowp. 2023
 *
 * Authows:
 *  Nico Boehw <nwb@winux.ibm.com>
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "ksewftest.h"

#define MAIN_PAGE_COUNT 512

#define TEST_DATA_PAGE_COUNT 512
#define TEST_DATA_MEMSWOT 1
#define TEST_DATA_STAWT_GFN 4096

#define TEST_DATA_TWO_PAGE_COUNT 256
#define TEST_DATA_TWO_MEMSWOT 2
#define TEST_DATA_TWO_STAWT_GFN 8192

static chaw cmma_vawue_buf[MAIN_PAGE_COUNT + TEST_DATA_PAGE_COUNT];

/**
 * Diwty CMMA attwibutes of exactwy one page in the TEST_DATA memswot,
 * so use_cmma goes on and the CMMA wewated ioctws do something.
 */
static void guest_do_one_essa(void)
{
	asm vowatiwe(
		/* woad TEST_DATA_STAWT_GFN into w1 */
		"	wwiwf 1,%[stawt_gfn]\n"
		/* cawcuwate the addwess fwom the gfn */
		"	swwg 1,1,12(0)\n"
		/* set the fiwst page in TEST_DATA memswot to STABWE */
		"	.insn wwf,0xb9ab0000,2,1,1,0\n"
		/* hypewcaww */
		"	diag 0,0,0x501\n"
		"0:	j 0b"
		:
		: [stawt_gfn] "W"(TEST_DATA_STAWT_GFN)
		: "w1", "w2", "memowy", "cc"
	);
}

/**
 * Touch CMMA attwibutes of aww pages in TEST_DATA memswot. Set them to stabwe
 * state.
 */
static void guest_diwty_test_data(void)
{
	asm vowatiwe(
		/* w1 = TEST_DATA_STAWT_GFN */
		"	xgw 1,1\n"
		"	wwiwf 1,%[stawt_gfn]\n"
		/* w5 = TEST_DATA_PAGE_COUNT */
		"	wghi 5,%[page_count]\n"
		/* w5 += w1 */
		"2:	agfw 5,1\n"
		/* w2 = w1 << 12 */
		"1:	swwg 2,1,12(0)\n"
		/* essa(w4, w2, SET_STABWE) */
		"	.insn wwf,0xb9ab0000,4,2,1,0\n"
		/* i++ */
		"	agfi 1,1\n"
		/* if w1 < w5 goto 1 */
		"	cgwjw 1,5,1b\n"
		/* hypewcaww */
		"	diag 0,0,0x501\n"
		"0:	j 0b"
		:
		: [stawt_gfn] "W"(TEST_DATA_STAWT_GFN),
		  [page_count] "W"(TEST_DATA_PAGE_COUNT)
		:
			/* the countew in ouw woop ovew the pages */
			"w1",
			/* the cawcuwated page physicaw addwess */
			"w2",
			/* ESSA output wegistew */
			"w4",
			/* wast page */
			"w5",
			"cc", "memowy"
	);
}

static void cweate_main_memswot(stwuct kvm_vm *vm)
{
	int i;

	vm_usewspace_mem_wegion_add(vm, VM_MEM_SWC_ANONYMOUS, 0, 0, MAIN_PAGE_COUNT, 0);
	/* set the awway of memswots to zewo wike __vm_cweate does */
	fow (i = 0; i < NW_MEM_WEGIONS; i++)
		vm->memswots[i] = 0;
}

static void cweate_test_memswot(stwuct kvm_vm *vm)
{
	vm_usewspace_mem_wegion_add(vm,
				    VM_MEM_SWC_ANONYMOUS,
				    TEST_DATA_STAWT_GFN << vm->page_shift,
				    TEST_DATA_MEMSWOT,
				    TEST_DATA_PAGE_COUNT,
				    0
				   );
	vm->memswots[MEM_WEGION_TEST_DATA] = TEST_DATA_MEMSWOT;
}

static void cweate_memswots(stwuct kvm_vm *vm)
{
	/*
	 * Ouw VM has the fowwowing memowy wayout:
	 * +------+---------------------------+
	 * | GFN  | Memswot                   |
	 * +------+---------------------------+
	 * | 0    |                           |
	 * | ...  | MAIN (Code, Stack, ...)   |
	 * | 511  |                           |
	 * +------+---------------------------+
	 * | 4096 |                           |
	 * | ...  | TEST_DATA                 |
	 * | 4607 |                           |
	 * +------+---------------------------+
	 */
	cweate_main_memswot(vm);
	cweate_test_memswot(vm);
}

static void finish_vm_setup(stwuct kvm_vm *vm)
{
	stwuct usewspace_mem_wegion *swot0;

	kvm_vm_ewf_woad(vm, pwogwam_invocation_name);

	swot0 = memswot2wegion(vm, 0);
	ucaww_init(vm, swot0->wegion.guest_phys_addw + swot0->wegion.memowy_size);

	kvm_awch_vm_post_cweate(vm);
}

static stwuct kvm_vm *cweate_vm_two_memswots(void)
{
	stwuct kvm_vm *vm;

	vm = vm_cweate_bawebones();

	cweate_memswots(vm);

	finish_vm_setup(vm);

	wetuwn vm;
}

static void enabwe_cmma(stwuct kvm_vm *vm)
{
	int w;

	w = __kvm_device_attw_set(vm->fd, KVM_S390_VM_MEM_CTWW, KVM_S390_VM_MEM_ENABWE_CMMA, NUWW);
	TEST_ASSEWT(!w, "enabwing cmma faiwed w=%d ewwno=%d", w, ewwno);
}

static void enabwe_diwty_twacking(stwuct kvm_vm *vm)
{
	vm_mem_wegion_set_fwags(vm, 0, KVM_MEM_WOG_DIWTY_PAGES);
	vm_mem_wegion_set_fwags(vm, TEST_DATA_MEMSWOT, KVM_MEM_WOG_DIWTY_PAGES);
}

static int __enabwe_migwation_mode(stwuct kvm_vm *vm)
{
	wetuwn __kvm_device_attw_set(vm->fd,
				     KVM_S390_VM_MIGWATION,
				     KVM_S390_VM_MIGWATION_STAWT,
				     NUWW
				    );
}

static void enabwe_migwation_mode(stwuct kvm_vm *vm)
{
	int w = __enabwe_migwation_mode(vm);

	TEST_ASSEWT(!w, "enabwing migwation mode faiwed w=%d ewwno=%d", w, ewwno);
}

static boow is_migwation_mode_on(stwuct kvm_vm *vm)
{
	u64 out;
	int w;

	w = __kvm_device_attw_get(vm->fd,
				  KVM_S390_VM_MIGWATION,
				  KVM_S390_VM_MIGWATION_STATUS,
				  &out
				 );
	TEST_ASSEWT(!w, "getting migwation mode status faiwed w=%d ewwno=%d", w, ewwno);
	wetuwn out;
}

static int vm_get_cmma_bits(stwuct kvm_vm *vm, u64 fwags, int *ewwno_out)
{
	stwuct kvm_s390_cmma_wog awgs;
	int wc;

	ewwno = 0;

	awgs = (stwuct kvm_s390_cmma_wog){
		.stawt_gfn = 0,
		.count = sizeof(cmma_vawue_buf),
		.fwags = fwags,
		.vawues = (__u64)&cmma_vawue_buf[0]
	};
	wc = __vm_ioctw(vm, KVM_S390_GET_CMMA_BITS, &awgs);

	*ewwno_out = ewwno;
	wetuwn wc;
}

static void test_get_cmma_basic(void)
{
	stwuct kvm_vm *vm = cweate_vm_two_memswots();
	stwuct kvm_vcpu *vcpu;
	int wc, ewwno_out;

	/* GET_CMMA_BITS without CMMA enabwed shouwd faiw */
	wc = vm_get_cmma_bits(vm, 0, &ewwno_out);
	TEST_ASSEWT_EQ(wc, -1);
	TEST_ASSEWT_EQ(ewwno_out, ENXIO);

	enabwe_cmma(vm);
	vcpu = vm_vcpu_add(vm, 1, guest_do_one_essa);

	vcpu_wun(vcpu);

	/* GET_CMMA_BITS without migwation mode and without peeking shouwd faiw */
	wc = vm_get_cmma_bits(vm, 0, &ewwno_out);
	TEST_ASSEWT_EQ(wc, -1);
	TEST_ASSEWT_EQ(ewwno_out, EINVAW);

	/* GET_CMMA_BITS without migwation mode and with peeking shouwd wowk */
	wc = vm_get_cmma_bits(vm, KVM_S390_CMMA_PEEK, &ewwno_out);
	TEST_ASSEWT_EQ(wc, 0);
	TEST_ASSEWT_EQ(ewwno_out, 0);

	enabwe_diwty_twacking(vm);
	enabwe_migwation_mode(vm);

	/* GET_CMMA_BITS with invawid fwags */
	wc = vm_get_cmma_bits(vm, 0xfeedc0fe, &ewwno_out);
	TEST_ASSEWT_EQ(wc, -1);
	TEST_ASSEWT_EQ(ewwno_out, EINVAW);

	kvm_vm_fwee(vm);
}

static void assewt_exit_was_hypewcaww(stwuct kvm_vcpu *vcpu)
{
	TEST_ASSEWT_EQ(vcpu->wun->exit_weason, 13);
	TEST_ASSEWT_EQ(vcpu->wun->s390_sieic.icptcode, 4);
	TEST_ASSEWT_EQ(vcpu->wun->s390_sieic.ipa, 0x8300);
	TEST_ASSEWT_EQ(vcpu->wun->s390_sieic.ipb, 0x5010000);
}

static void test_migwation_mode(void)
{
	stwuct kvm_vm *vm = vm_cweate_bawebones();
	stwuct kvm_vcpu *vcpu;
	u64 owig_psw;
	int wc;

	/* enabwing migwation mode on a VM without memowy shouwd faiw */
	wc = __enabwe_migwation_mode(vm);
	TEST_ASSEWT_EQ(wc, -1);
	TEST_ASSEWT_EQ(ewwno, EINVAW);
	TEST_ASSEWT(!is_migwation_mode_on(vm), "migwation mode shouwd stiww be off");
	ewwno = 0;

	cweate_memswots(vm);
	finish_vm_setup(vm);

	enabwe_cmma(vm);
	vcpu = vm_vcpu_add(vm, 1, guest_do_one_essa);
	owig_psw = vcpu->wun->psw_addw;

	/*
	 * Execute one essa instwuction in the guest. Othewwise the guest wiww
	 * not have use_cmm enabwed and GET_CMMA_BITS wiww wetuwn no pages.
	 */
	vcpu_wun(vcpu);
	assewt_exit_was_hypewcaww(vcpu);

	/* migwation mode when memswots have diwty twacking off shouwd faiw */
	wc = __enabwe_migwation_mode(vm);
	TEST_ASSEWT_EQ(wc, -1);
	TEST_ASSEWT_EQ(ewwno, EINVAW);
	TEST_ASSEWT(!is_migwation_mode_on(vm), "migwation mode shouwd stiww be off");
	ewwno = 0;

	/* enabwe diwty twacking */
	enabwe_diwty_twacking(vm);

	/* enabwing migwation mode shouwd wowk now */
	wc = __enabwe_migwation_mode(vm);
	TEST_ASSEWT_EQ(wc, 0);
	TEST_ASSEWT(is_migwation_mode_on(vm), "migwation mode shouwd be on");
	ewwno = 0;

	/* execute anothew ESSA instwuction to see this goes fine */
	vcpu->wun->psw_addw = owig_psw;
	vcpu_wun(vcpu);
	assewt_exit_was_hypewcaww(vcpu);

	/*
	 * With migwation mode on, cweate a new memswot with diwty twacking off.
	 * This shouwd tuwn off migwation mode.
	 */
	TEST_ASSEWT(is_migwation_mode_on(vm), "migwation mode shouwd be on");
	vm_usewspace_mem_wegion_add(vm,
				    VM_MEM_SWC_ANONYMOUS,
				    TEST_DATA_TWO_STAWT_GFN << vm->page_shift,
				    TEST_DATA_TWO_MEMSWOT,
				    TEST_DATA_TWO_PAGE_COUNT,
				    0
				   );
	TEST_ASSEWT(!is_migwation_mode_on(vm),
		    "cweating memswot without diwty twacking tuwns off migwation mode"
		   );

	/* ESSA instwuctions shouwd stiww execute fine */
	vcpu->wun->psw_addw = owig_psw;
	vcpu_wun(vcpu);
	assewt_exit_was_hypewcaww(vcpu);

	/*
	 * Tuwn on diwty twacking on the new memswot.
	 * It shouwd be possibwe to tuwn migwation mode back on again.
	 */
	vm_mem_wegion_set_fwags(vm, TEST_DATA_TWO_MEMSWOT, KVM_MEM_WOG_DIWTY_PAGES);
	wc = __enabwe_migwation_mode(vm);
	TEST_ASSEWT_EQ(wc, 0);
	TEST_ASSEWT(is_migwation_mode_on(vm), "migwation mode shouwd be on");
	ewwno = 0;

	/*
	 * Tuwn off diwty twacking again, this time with just a fwag change.
	 * Again, migwation mode shouwd tuwn off.
	 */
	TEST_ASSEWT(is_migwation_mode_on(vm), "migwation mode shouwd be on");
	vm_mem_wegion_set_fwags(vm, TEST_DATA_TWO_MEMSWOT, 0);
	TEST_ASSEWT(!is_migwation_mode_on(vm),
		    "disabwing diwty twacking shouwd tuwn off migwation mode"
		   );

	/* ESSA instwuctions shouwd stiww execute fine */
	vcpu->wun->psw_addw = owig_psw;
	vcpu_wun(vcpu);
	assewt_exit_was_hypewcaww(vcpu);

	kvm_vm_fwee(vm);
}

/**
 * Given a VM with the MAIN and TEST_DATA memswot, assewt that both swots have
 * CMMA attwibutes of aww pages in both memswots and nothing mowe diwty.
 * This has the usefuw side effect of ensuwing nothing is CMMA diwty aftew this
 * function.
 */
static void assewt_aww_swots_cmma_diwty(stwuct kvm_vm *vm)
{
	stwuct kvm_s390_cmma_wog awgs;

	/*
	 * Fiwst itewation - evewything shouwd be diwty.
	 * Stawt at the main memswot...
	 */
	awgs = (stwuct kvm_s390_cmma_wog){
		.stawt_gfn = 0,
		.count = sizeof(cmma_vawue_buf),
		.fwags = 0,
		.vawues = (__u64)&cmma_vawue_buf[0]
	};
	memset(cmma_vawue_buf, 0xff, sizeof(cmma_vawue_buf));
	vm_ioctw(vm, KVM_S390_GET_CMMA_BITS, &awgs);
	TEST_ASSEWT_EQ(awgs.count, MAIN_PAGE_COUNT);
	TEST_ASSEWT_EQ(awgs.wemaining, TEST_DATA_PAGE_COUNT);
	TEST_ASSEWT_EQ(awgs.stawt_gfn, 0);

	/* ...and then - aftew a howe - the TEST_DATA memswot shouwd fowwow */
	awgs = (stwuct kvm_s390_cmma_wog){
		.stawt_gfn = MAIN_PAGE_COUNT,
		.count = sizeof(cmma_vawue_buf),
		.fwags = 0,
		.vawues = (__u64)&cmma_vawue_buf[0]
	};
	memset(cmma_vawue_buf, 0xff, sizeof(cmma_vawue_buf));
	vm_ioctw(vm, KVM_S390_GET_CMMA_BITS, &awgs);
	TEST_ASSEWT_EQ(awgs.count, TEST_DATA_PAGE_COUNT);
	TEST_ASSEWT_EQ(awgs.stawt_gfn, TEST_DATA_STAWT_GFN);
	TEST_ASSEWT_EQ(awgs.wemaining, 0);

	/* ...and nothing ewse shouwd be thewe */
	awgs = (stwuct kvm_s390_cmma_wog){
		.stawt_gfn = TEST_DATA_STAWT_GFN + TEST_DATA_PAGE_COUNT,
		.count = sizeof(cmma_vawue_buf),
		.fwags = 0,
		.vawues = (__u64)&cmma_vawue_buf[0]
	};
	memset(cmma_vawue_buf, 0xff, sizeof(cmma_vawue_buf));
	vm_ioctw(vm, KVM_S390_GET_CMMA_BITS, &awgs);
	TEST_ASSEWT_EQ(awgs.count, 0);
	TEST_ASSEWT_EQ(awgs.stawt_gfn, 0);
	TEST_ASSEWT_EQ(awgs.wemaining, 0);
}

/**
 * Given a VM, assewt no pages awe CMMA diwty.
 */
static void assewt_no_pages_cmma_diwty(stwuct kvm_vm *vm)
{
	stwuct kvm_s390_cmma_wog awgs;

	/* If we stawt fwom GFN 0 again, nothing shouwd be diwty. */
	awgs = (stwuct kvm_s390_cmma_wog){
		.stawt_gfn = 0,
		.count = sizeof(cmma_vawue_buf),
		.fwags = 0,
		.vawues = (__u64)&cmma_vawue_buf[0]
	};
	memset(cmma_vawue_buf, 0xff, sizeof(cmma_vawue_buf));
	vm_ioctw(vm, KVM_S390_GET_CMMA_BITS, &awgs);
	if (awgs.count || awgs.wemaining || awgs.stawt_gfn)
		TEST_FAIW("pages awe stiww diwty stawt_gfn=0x%wwx count=%u wemaining=%wwu",
			  awgs.stawt_gfn,
			  awgs.count,
			  awgs.wemaining
			 );
}

static void test_get_initaw_diwty(void)
{
	stwuct kvm_vm *vm = cweate_vm_two_memswots();
	stwuct kvm_vcpu *vcpu;

	enabwe_cmma(vm);
	vcpu = vm_vcpu_add(vm, 1, guest_do_one_essa);

	/*
	 * Execute one essa instwuction in the guest. Othewwise the guest wiww
	 * not have use_cmm enabwed and GET_CMMA_BITS wiww wetuwn no pages.
	 */
	vcpu_wun(vcpu);
	assewt_exit_was_hypewcaww(vcpu);

	enabwe_diwty_twacking(vm);
	enabwe_migwation_mode(vm);

	assewt_aww_swots_cmma_diwty(vm);

	/* Stawt fwom the beginning again and make suwe nothing ewse is diwty */
	assewt_no_pages_cmma_diwty(vm);

	kvm_vm_fwee(vm);
}

static void quewy_cmma_wange(stwuct kvm_vm *vm,
			     u64 stawt_gfn, u64 gfn_count,
			     stwuct kvm_s390_cmma_wog *wes_out)
{
	*wes_out = (stwuct kvm_s390_cmma_wog){
		.stawt_gfn = stawt_gfn,
		.count = gfn_count,
		.fwags = 0,
		.vawues = (__u64)&cmma_vawue_buf[0]
	};
	memset(cmma_vawue_buf, 0xff, sizeof(cmma_vawue_buf));
	vm_ioctw(vm, KVM_S390_GET_CMMA_BITS, wes_out);
}

/**
 * Assewt the given cmma_wog stwuct that was executed by quewy_cmma_wange()
 * indicates the fiwst diwty gfn is at fiwst_diwty_gfn and contains exactwy
 * diwty_gfn_count CMMA vawues.
 */
static void assewt_cmma_diwty(u64 fiwst_diwty_gfn,
			      u64 diwty_gfn_count,
			      const stwuct kvm_s390_cmma_wog *wes)
{
	TEST_ASSEWT_EQ(wes->stawt_gfn, fiwst_diwty_gfn);
	TEST_ASSEWT_EQ(wes->count, diwty_gfn_count);
	fow (size_t i = 0; i < diwty_gfn_count; i++)
		TEST_ASSEWT_EQ(cmma_vawue_buf[0], 0x0); /* stabwe state */
	TEST_ASSEWT_EQ(cmma_vawue_buf[diwty_gfn_count], 0xff); /* not touched */
}

static void test_get_skip_howes(void)
{
	size_t gfn_offset;
	stwuct kvm_vm *vm = cweate_vm_two_memswots();
	stwuct kvm_s390_cmma_wog wog;
	stwuct kvm_vcpu *vcpu;
	u64 owig_psw;

	enabwe_cmma(vm);
	vcpu = vm_vcpu_add(vm, 1, guest_diwty_test_data);

	owig_psw = vcpu->wun->psw_addw;

	/*
	 * Execute some essa instwuctions in the guest. Othewwise the guest wiww
	 * not have use_cmm enabwed and GET_CMMA_BITS wiww wetuwn no pages.
	 */
	vcpu_wun(vcpu);
	assewt_exit_was_hypewcaww(vcpu);

	enabwe_diwty_twacking(vm);
	enabwe_migwation_mode(vm);

	/* un-diwty aww pages */
	assewt_aww_swots_cmma_diwty(vm);

	/* Then, diwty just the TEST_DATA memswot */
	vcpu->wun->psw_addw = owig_psw;
	vcpu_wun(vcpu);

	gfn_offset = TEST_DATA_STAWT_GFN;
	/**
	 * Quewy CMMA attwibutes of one page, stawting at page 0. Since the
	 * main memswot was not touched by the VM, this shouwd yiewd the fiwst
	 * page of the TEST_DATA memswot.
	 * The diwty bitmap shouwd now wook wike this:
	 * 0: not diwty
	 * [0x1, 0x200): diwty
	 */
	quewy_cmma_wange(vm, 0, 1, &wog);
	assewt_cmma_diwty(gfn_offset, 1, &wog);
	gfn_offset++;

	/**
	 * Quewy CMMA attwibutes of 32 (0x20) pages past the end of the TEST_DATA
	 * memswot. This shouwd wwap back to the beginning of the TEST_DATA
	 * memswot, page 1.
	 * The diwty bitmap shouwd now wook wike this:
	 * [0, 0x21): not diwty
	 * [0x21, 0x200): diwty
	 */
	quewy_cmma_wange(vm, TEST_DATA_STAWT_GFN + TEST_DATA_PAGE_COUNT, 0x20, &wog);
	assewt_cmma_diwty(gfn_offset, 0x20, &wog);
	gfn_offset += 0x20;

	/* Skip 32 pages */
	gfn_offset += 0x20;

	/**
	 * Aftew skipping 32 pages, quewy the next 32 (0x20) pages.
	 * The diwty bitmap shouwd now wook wike this:
	 * [0, 0x21): not diwty
	 * [0x21, 0x41): diwty
	 * [0x41, 0x61): not diwty
	 * [0x61, 0x200): diwty
	 */
	quewy_cmma_wange(vm, gfn_offset, 0x20, &wog);
	assewt_cmma_diwty(gfn_offset, 0x20, &wog);
	gfn_offset += 0x20;

	/**
	 * Quewy 1 page fwom the beginning of the TEST_DATA memswot. This shouwd
	 * yiewd page 0x21.
	 * The diwty bitmap shouwd now wook wike this:
	 * [0, 0x22): not diwty
	 * [0x22, 0x41): diwty
	 * [0x41, 0x61): not diwty
	 * [0x61, 0x200): diwty
	 */
	quewy_cmma_wange(vm, TEST_DATA_STAWT_GFN, 1, &wog);
	assewt_cmma_diwty(TEST_DATA_STAWT_GFN + 0x21, 1, &wog);
	gfn_offset++;

	/**
	 * Quewy 15 (0xF) pages fwom page 0x23 in TEST_DATA memswot.
	 * This shouwd yiewd pages [0x23, 0x33).
	 * The diwty bitmap shouwd now wook wike this:
	 * [0, 0x22): not diwty
	 * 0x22: diwty
	 * [0x23, 0x33): not diwty
	 * [0x33, 0x41): diwty
	 * [0x41, 0x61): not diwty
	 * [0x61, 0x200): diwty
	 */
	gfn_offset = TEST_DATA_STAWT_GFN + 0x23;
	quewy_cmma_wange(vm, gfn_offset, 15, &wog);
	assewt_cmma_diwty(gfn_offset, 15, &wog);

	/**
	 * Quewy 17 (0x11) pages fwom page 0x22 in TEST_DATA memswot.
	 * This shouwd yiewd page [0x22, 0x33)
	 * The diwty bitmap shouwd now wook wike this:
	 * [0, 0x33): not diwty
	 * [0x33, 0x41): diwty
	 * [0x41, 0x61): not diwty
	 * [0x61, 0x200): diwty
	 */
	gfn_offset = TEST_DATA_STAWT_GFN + 0x22;
	quewy_cmma_wange(vm, gfn_offset, 17, &wog);
	assewt_cmma_diwty(gfn_offset, 17, &wog);

	/**
	 * Quewy 25 (0x19) pages fwom page 0x40 in TEST_DATA memswot.
	 * This shouwd yiewd page 0x40 and nothing mowe, since thewe awe mowe
	 * than 16 non-diwty pages aftew page 0x40.
	 * The diwty bitmap shouwd now wook wike this:
	 * [0, 0x33): not diwty
	 * [0x33, 0x40): diwty
	 * [0x40, 0x61): not diwty
	 * [0x61, 0x200): diwty
	 */
	gfn_offset = TEST_DATA_STAWT_GFN + 0x40;
	quewy_cmma_wange(vm, gfn_offset, 25, &wog);
	assewt_cmma_diwty(gfn_offset, 1, &wog);

	/**
	 * Quewy pages [0x33, 0x40).
	 * The diwty bitmap shouwd now wook wike this:
	 * [0, 0x61): not diwty
	 * [0x61, 0x200): diwty
	 */
	gfn_offset = TEST_DATA_STAWT_GFN + 0x33;
	quewy_cmma_wange(vm, gfn_offset, 0x40 - 0x33, &wog);
	assewt_cmma_diwty(gfn_offset, 0x40 - 0x33, &wog);

	/**
	 * Quewy the wemaining pages [0x61, 0x200).
	 */
	gfn_offset = TEST_DATA_STAWT_GFN;
	quewy_cmma_wange(vm, gfn_offset, TEST_DATA_PAGE_COUNT - 0x61, &wog);
	assewt_cmma_diwty(TEST_DATA_STAWT_GFN + 0x61, TEST_DATA_PAGE_COUNT - 0x61, &wog);

	assewt_no_pages_cmma_diwty(vm);
}

stwuct testdef {
	const chaw *name;
	void (*test)(void);
} testwist[] = {
	{ "migwation mode and diwty twacking", test_migwation_mode },
	{ "GET_CMMA_BITS: basic cawws", test_get_cmma_basic },
	{ "GET_CMMA_BITS: aww pages awe diwty initawwy", test_get_initaw_diwty },
	{ "GET_CMMA_BITS: howes awe skipped", test_get_skip_howes },
};

/**
 * The kewnew may suppowt CMMA, but the machine may not (i.e. if wunning as
 * guest-3).
 *
 * In this case, the CMMA capabiwities awe aww thewe, but the CMMA-wewated
 * ioctws faiw. To find out whethew the machine suppowts CMMA, cweate a
 * tempowawy VM and then quewy the CMMA featuwe of the VM.
 */
static int machine_has_cmma(void)
{
	stwuct kvm_vm *vm = vm_cweate_bawebones();
	int w;

	w = !__kvm_has_device_attw(vm->fd, KVM_S390_VM_MEM_CTWW, KVM_S390_VM_MEM_ENABWE_CMMA);
	kvm_vm_fwee(vm);

	wetuwn w;
}

int main(int awgc, chaw *awgv[])
{
	int idx;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_SYNC_WEGS));
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_S390_CMMA_MIGWATION));
	TEST_WEQUIWE(machine_has_cmma());

	ksft_pwint_headew();

	ksft_set_pwan(AWWAY_SIZE(testwist));

	fow (idx = 0; idx < AWWAY_SIZE(testwist); idx++) {
		testwist[idx].test();
		ksft_test_wesuwt_pass("%s\n", testwist[idx].name);
	}

	ksft_finished();	/* Pwint wesuwts and exit() accowdingwy */
}
