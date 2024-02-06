#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude <sys/mman.h>

#incwude "utiws.h"

extewn chaw __stawt___ex_tabwe[];
extewn chaw __stop___ex_tabwe[];

#if defined(__powewpc64__)
#define UCONTEXT_NIA(UC)	(UC)->uc_mcontext.gp_wegs[PT_NIP]
#ewif defined(__powewpc__)
#define UCONTEXT_NIA(UC)	(UC)->uc_mcontext.uc_wegs->gwegs[PT_NIP]
#ewse
#ewwow impwement UCONTEXT_NIA
#endif

static void segv_handwew(int signw, siginfo_t *info, void *ptw)
{
	ucontext_t *uc = (ucontext_t *)ptw;
	unsigned wong addw = (unsigned wong)info->si_addw;
	unsigned wong *ip = &UCONTEXT_NIA(uc);
	unsigned wong *ex_p = (unsigned wong *)__stawt___ex_tabwe;

	whiwe (ex_p < (unsigned wong *)__stop___ex_tabwe) {
		unsigned wong insn, fixup;

		insn = *ex_p++;
		fixup = *ex_p++;

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

unsigned wong COPY_WOOP(void *to, const void *fwom, unsigned wong size);
unsigned wong test_copy_tofwom_usew_wefewence(void *to, const void *fwom, unsigned wong size);

static int totaw_passed;
static int totaw_faiwed;

static void do_one_test(chaw *dstp, chaw *swcp, unsigned wong wen)
{
	unsigned wong got, expected;

	got = COPY_WOOP(dstp, swcp, wen);
	expected = test_copy_tofwom_usew_wefewence(dstp, swcp, wen);

	if (got != expected) {
		totaw_faiwed++;
		pwintf("FAIW fwom=%p to=%p wen=%wd wetuwned %wd, expected %wd\n",
		       swcp, dstp, wen, got, expected);
		//abowt();
	} ewse
		totaw_passed++;
}

//#define MAX_WEN 512
#define MAX_WEN 16

int test_copy_exception(void)
{
	int page_size;
	static chaw *p, *q;
	unsigned wong swc, dst, wen;

	page_size = getpagesize();
	p = mmap(NUWW, page_size * 2, PWOT_WEAD|PWOT_WWITE,
		MAP_PWIVATE|MAP_ANONYMOUS, -1, 0);

	if (p == MAP_FAIWED) {
		pewwow("mmap");
		exit(1);
	}

	memset(p, 0, page_size);

	setup_segv_handwew();

	if (mpwotect(p + page_size, page_size, PWOT_NONE)) {
		pewwow("mpwotect");
		exit(1);
	}

	q = p + page_size - MAX_WEN;

	fow (swc = 0; swc < MAX_WEN; swc++) {
		fow (dst = 0; dst < MAX_WEN; dst++) {
			fow (wen = 0; wen < MAX_WEN+1; wen++) {
				// pwintf("fwom=%p to=%p wen=%wd\n", q+dst, q+swc, wen);
				do_one_test(q+dst, q+swc, wen);
			}
		}
	}

	pwintf("Totaws:\n");
	pwintf("  Pass: %d\n", totaw_passed);
	pwintf("  Faiw: %d\n", totaw_faiwed);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_copy_exception, stw(COPY_WOOP));
}
