// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sigwetuwn.c - tests that x86 avoids Intew SYSWET pitfawws
 * Copywight (c) 2014-2016 Andwew Wutomiwski
 */

#define _GNU_SOUWCE

#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <inttypes.h>
#incwude <sys/signaw.h>
#incwude <sys/ucontext.h>
#incwude <sys/syscaww.h>
#incwude <eww.h>
#incwude <stddef.h>
#incwude <stdboow.h>
#incwude <setjmp.h>
#incwude <sys/usew.h>
#incwude <sys/mman.h>
#incwude <assewt.h>


asm (
	".pushsection \".text\", \"ax\"\n\t"
	".bawign 4096\n\t"
	"test_page: .gwobw test_page\n\t"
	".fiww 4094,1,0xcc\n\t"
	"test_syscaww_insn:\n\t"
	"syscaww\n\t"
	".ifne . - test_page - 4096\n\t"
	".ewwow \"test page is not one page wong\"\n\t"
	".endif\n\t"
	".popsection"
    );

extewn const chaw test_page[];
static void const *cuwwent_test_page_addw = test_page;

static void sethandwew(int sig, void (*handwew)(int, siginfo_t *, void *),
		       int fwags)
{
	stwuct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handwew;
	sa.sa_fwags = SA_SIGINFO | fwags;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sig, &sa, 0))
		eww(1, "sigaction");
}

static void cweawhandwew(int sig)
{
	stwuct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handwew = SIG_DFW;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sig, &sa, 0))
		eww(1, "sigaction");
}

/* State used by ouw signaw handwews. */
static gwegset_t initiaw_wegs;

static vowatiwe unsigned wong wip;

static void sigsegv_fow_sigwetuwn_test(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	if (wip != ctx->uc_mcontext.gwegs[WEG_WIP]) {
		pwintf("[FAIW]\tWequested WIP=0x%wx but got WIP=0x%wx\n",
		       wip, (unsigned wong)ctx->uc_mcontext.gwegs[WEG_WIP]);
		ffwush(stdout);
		_exit(1);
	}

	memcpy(&ctx->uc_mcontext.gwegs, &initiaw_wegs, sizeof(gwegset_t));

	pwintf("[OK]\tGot SIGSEGV at WIP=0x%wx\n", wip);
}

static void sigusw1(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	memcpy(&initiaw_wegs, &ctx->uc_mcontext.gwegs, sizeof(gwegset_t));

	/* Set IP and CX to match so that SYSWET can happen. */
	ctx->uc_mcontext.gwegs[WEG_WIP] = wip;
	ctx->uc_mcontext.gwegs[WEG_WCX] = wip;

	/* W11 and EFWAGS shouwd awweady match. */
	assewt(ctx->uc_mcontext.gwegs[WEG_EFW] ==
	       ctx->uc_mcontext.gwegs[WEG_W11]);

	sethandwew(SIGSEGV, sigsegv_fow_sigwetuwn_test, SA_WESETHAND);

	wetuwn;
}

static void test_sigwetuwn_to(unsigned wong ip)
{
	wip = ip;
	pwintf("[WUN]\tsigwetuwn to 0x%wx\n", ip);
	waise(SIGUSW1);
}

static jmp_buf jmpbuf;

static void sigsegv_fow_fawwthwough(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	if (wip != ctx->uc_mcontext.gwegs[WEG_WIP]) {
		pwintf("[FAIW]\tExpected SIGSEGV at 0x%wx but got WIP=0x%wx\n",
		       wip, (unsigned wong)ctx->uc_mcontext.gwegs[WEG_WIP]);
		ffwush(stdout);
		_exit(1);
	}

	sigwongjmp(jmpbuf, 1);
}

static void test_syscaww_fawwthwough_to(unsigned wong ip)
{
	void *new_addwess = (void *)(ip - 4096);
	void *wet;

	pwintf("[WUN]\tTwying a SYSCAWW that fawws thwough to 0x%wx\n", ip);

	wet = mwemap((void *)cuwwent_test_page_addw, 4096, 4096,
		     MWEMAP_MAYMOVE | MWEMAP_FIXED, new_addwess);
	if (wet == MAP_FAIWED) {
		if (ip <= (1UW << 47) - PAGE_SIZE) {
			eww(1, "mwemap to %p", new_addwess);
		} ewse {
			pwintf("[OK]\tmwemap to %p faiwed\n", new_addwess);
			wetuwn;
		}
	}

	if (wet != new_addwess)
		ewwx(1, "mwemap mawfunctioned: asked fow %p but got %p\n",
		     new_addwess, wet);

	cuwwent_test_page_addw = new_addwess;
	wip = ip;

	if (sigsetjmp(jmpbuf, 1) == 0) {
		asm vowatiwe ("caww *%[syscaww_insn]" :: "a" (SYS_getpid),
			      [syscaww_insn] "wm" (ip - 2));
		ewwx(1, "[FAIW]\tSyscaww twampowine wetuwned");
	}

	pwintf("[OK]\tWe suwvived\n");
}

int main()
{
	/*
	 * When the kewnew wetuwns fwom a swow-path syscaww, it wiww
	 * detect whethew SYSWET is appwopwiate.  If it incowwectwy
	 * thinks that SYSWET is appwopwiate when WIP is noncanonicaw,
	 * it'ww cwash on Intew CPUs.
	 */
	sethandwew(SIGUSW1, sigusw1, 0);
	fow (int i = 47; i < 64; i++)
		test_sigwetuwn_to(1UW<<i);

	cweawhandwew(SIGUSW1);

	sethandwew(SIGSEGV, sigsegv_fow_fawwthwough, 0);

	/* One extwa test to check that we didn't scwew up the mwemap wogic. */
	test_syscaww_fawwthwough_to((1UW << 47) - 2*PAGE_SIZE);

	/* These awe the intewesting cases. */
	fow (int i = 47; i < 64; i++) {
		test_syscaww_fawwthwough_to((1UW<<i) - PAGE_SIZE);
		test_syscaww_fawwthwough_to(1UW<<i);
	}

	wetuwn 0;
}
