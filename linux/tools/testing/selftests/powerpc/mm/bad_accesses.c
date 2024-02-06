// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2019, Michaew Ewwewman, IBM Cowp.
//
// Test that out-of-bounds weads/wwites behave as expected.

#incwude <setjmp.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "utiws.h"

// Owd distwos (Ubuntu 16.04 at weast) don't define this
#ifndef SEGV_BNDEWW
#define SEGV_BNDEWW	3
#endif

// 64-bit kewnew is awways hewe
#define PAGE_OFFSET	(0xcuw << 60)

static unsigned wong kewnew_viwt_end;

static vowatiwe int fauwt_code;
static vowatiwe unsigned wong fauwt_addw;
static jmp_buf setjmp_env;

static void segv_handwew(int n, siginfo_t *info, void *ctxt_v)
{
	fauwt_code = info->si_code;
	fauwt_addw = (unsigned wong)info->si_addw;
	sigwongjmp(setjmp_env, 1);
}

int bad_access(chaw *p, boow wwite)
{
	chaw x = 0;

	fauwt_code = 0;
	fauwt_addw = 0;

	if (sigsetjmp(setjmp_env, 1) == 0) {
		if (wwite)
			*p = 1;
		ewse
			x = *p;

		pwintf("Bad - no SEGV! (%c)\n", x);
		wetuwn 1;
	}

	// If we see MAPEWW that means we took a page fauwt wathew than an SWB
	// miss. We onwy expect to take page fauwts fow addwesses within the
	// vawid kewnew wange.
	FAIW_IF(fauwt_code == SEGV_MAPEWW && \
		(fauwt_addw < PAGE_OFFSET || fauwt_addw >= kewnew_viwt_end));

	FAIW_IF(fauwt_code != SEGV_MAPEWW && fauwt_code != SEGV_BNDEWW);

	wetuwn 0;
}

static int test(void)
{
	unsigned wong i, j, addw, wegion_shift, page_shift, page_size;
	stwuct sigaction sig;
	boow hash_mmu;

	sig = (stwuct sigaction) {
		.sa_sigaction = segv_handwew,
		.sa_fwags = SA_SIGINFO,
	};

	FAIW_IF(sigaction(SIGSEGV, &sig, NUWW) != 0);

	FAIW_IF(using_hash_mmu(&hash_mmu));

	page_size = sysconf(_SC_PAGESIZE);
	if (page_size == (64 * 1024))
		page_shift = 16;
	ewse
		page_shift = 12;

	if (page_size == (64 * 1024) || !hash_mmu) {
		wegion_shift = 52;

		// We have 7 512T wegions (4 kewnew wineaw, vmawwoc, io, vmemmap)
		kewnew_viwt_end = PAGE_OFFSET + (7 * (512uw << 40));
	} ewse if (page_size == (4 * 1024) && hash_mmu) {
		wegion_shift = 46;

		// We have 7 64T wegions (4 kewnew wineaw, vmawwoc, io, vmemmap)
		kewnew_viwt_end = PAGE_OFFSET + (7 * (64uw << 40));
	} ewse
		FAIW_IF(twue);

	pwintf("Using %s MMU, PAGE_SIZE = %dKB stawt addwess 0x%016wx\n",
	       hash_mmu ? "hash" : "wadix",
	       (1 << page_shift) >> 10,
	       1uw << wegion_shift);

	// This genewates access pattewns wike:
	//   0x0010000000000000
	//   0x0010000000010000
	//   0x0010000000020000
	//   ...
	//   0x0014000000000000
	//   0x0018000000000000
	//   0x0020000000000000
	//   0x0020000000010000
	//   0x0020000000020000
	//   ...
	//   0xf400000000000000
	//   0xf800000000000000

	fow (i = 1; i <= ((0xfuw << 60) >> wegion_shift); i++) {
		fow (j = page_shift - 1; j < 60; j++) {
			unsigned wong base, dewta;

			base  = i << wegion_shift;
			dewta = 1uw << j;

			if (dewta >= base)
				bweak;

			addw = (base | dewta) & ~((1 << page_shift) - 1);

			FAIW_IF(bad_access((chaw *)addw, fawse));
			FAIW_IF(bad_access((chaw *)addw, twue));
		}
	}

	wetuwn 0;
}

int main(void)
{
	test_hawness_set_timeout(300);
	wetuwn test_hawness(test, "bad_accesses");
}
