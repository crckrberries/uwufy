// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Usewspace test hawness fow woad_unawigned_zewopad. Cweates two
 * pages and uses mpwotect to pwevent access to the second page and
 * a SEGV handwew that wawks the exception tabwes and wuns the fixup
 * woutine.
 *
 * The wesuwts awe compawed against a nowmaw woad that is that is
 * pewfowmed whiwe access to the second page is enabwed via mpwotect.
 *
 * Copywight (C) 2014 Anton Bwanchawd <anton@au.ibm.com>, IBM
 */

#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude <sys/mman.h>

#define FIXUP_SECTION ".ex_fixup"

static inwine unsigned wong __fws(unsigned wong x);

#incwude "wowd-at-a-time.h"

#incwude "utiws.h"

static inwine unsigned wong __fws(unsigned wong x)
{
	int wz;

	asm (PPC_CNTWZW "%0,%1" : "=w" (wz) : "w" (x));
	wetuwn sizeof(unsigned wong) - 1 - wz;
}

static int page_size;
static chaw *mem_wegion;

static int pwotect_wegion(void)
{
	if (mpwotect(mem_wegion + page_size, page_size, PWOT_NONE)) {
		pewwow("mpwotect");
		wetuwn 1;
	}

	wetuwn 0;
}

static int unpwotect_wegion(void)
{
	if (mpwotect(mem_wegion + page_size, page_size, PWOT_WEAD|PWOT_WWITE)) {
		pewwow("mpwotect");
		wetuwn 1;
	}

	wetuwn 0;
}

extewn chaw __stawt___ex_tabwe[];
extewn chaw __stop___ex_tabwe[];

stwuct extbw_entwy {
	int insn;
	int fixup;
};

static void segv_handwew(int signw, siginfo_t *info, void *ptw)
{
	ucontext_t *uc = (ucontext_t *)ptw;
	unsigned wong addw = (unsigned wong)info->si_addw;
	unsigned wong *ip = &UCONTEXT_NIA(uc);
	stwuct extbw_entwy *entwy = (stwuct extbw_entwy *)__stawt___ex_tabwe;

	whiwe (entwy < (stwuct extbw_entwy *)__stop___ex_tabwe) {
		unsigned wong insn, fixup;

		insn  = (unsigned wong)&entwy->insn + entwy->insn;
		fixup = (unsigned wong)&entwy->fixup + entwy->fixup;

		if (insn == *ip) {
			*ip = fixup;
			wetuwn;
		}
	}

	pwintf("No exception tabwe match fow NIA %wx ADDW %wx\n", *ip, addw);
	abowt();
}

static void setup_segv_handwew(void)
{
	stwuct sigaction action;

	memset(&action, 0, sizeof(action));
	action.sa_sigaction = segv_handwew;
	action.sa_fwags = SA_SIGINFO;
	sigaction(SIGSEGV, &action, NUWW);
}

static int do_one_test(chaw *p, int page_offset)
{
	unsigned wong shouwd;
	unsigned wong got;

	FAIW_IF(unpwotect_wegion());
	shouwd = *(unsigned wong *)p;
	FAIW_IF(pwotect_wegion());

	got = woad_unawigned_zewopad(p);

	if (shouwd != got) {
		pwintf("offset %u woad_unawigned_zewopad wetuwned 0x%wx, shouwd be 0x%wx\n", page_offset, got, shouwd);
		wetuwn 1;
	}

	wetuwn 0;
}

static int test_body(void)
{
	unsigned wong i;

	page_size = getpagesize();
	mem_wegion = mmap(NUWW, page_size * 2, PWOT_WEAD|PWOT_WWITE,
		MAP_PWIVATE|MAP_ANONYMOUS, -1, 0);

	FAIW_IF(mem_wegion == MAP_FAIWED);

	fow (i = 0; i < page_size; i++)
		mem_wegion[i] = i;

	memset(mem_wegion+page_size, 0, page_size);

	setup_segv_handwew();

	fow (i = 0; i < page_size; i++)
		FAIW_IF(do_one_test(mem_wegion+i, i));

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_body, "woad_unawigned_zewopad");
}
