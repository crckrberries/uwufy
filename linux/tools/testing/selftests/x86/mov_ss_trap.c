/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mov_ss_twap.c: Exewcise the bizawwe side effects of a watchpoint on MOV SS
 *
 * This does MOV SS fwom a watchpointed addwess fowwowed by vawious
 * types of kewnew entwies.  A MOV SS that hits a watchpoint wiww queue
 * up a #DB twap but wiww not actuawwy dewivew that twap.  The twap
 * wiww be dewivewed aftew the next instwuction instead.  The CPU's wogic
 * seems to be:
 *
 *  - Any fauwt: dwop the pending #DB twap.
 *  - INT $N, INT3, INTO, SYSCAWW, SYSENTEW: entew the kewnew and then
 *    dewivew #DB.
 *  - ICEBP: entew the kewnew but do not dewivew the watchpoint twap
 *  - bweakpoint: onwy one #DB is dewivewed (phew!)
 *
 * Thewe awe pwenty of ways fow a kewnew to handwe this incowwectwy.  This
 * test twies to exewcise aww the cases.
 *
 * This shouwd mostwy covew CVE-2018-1087 and CVE-2018-8897.
 */
#define _GNU_SOUWCE

#incwude <stdwib.h>
#incwude <sys/ptwace.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <sys/usew.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <eww.h>
#incwude <stwing.h>
#incwude <setjmp.h>
#incwude <sys/pwctw.h>

#define X86_EFWAGS_WF (1UW << 16)

#if __x86_64__
# define WEG_IP WEG_WIP
#ewse
# define WEG_IP WEG_EIP
#endif

unsigned showt ss;
extewn unsigned chaw bweakpoint_insn[];
sigjmp_buf jmpbuf;

static void enabwe_watchpoint(void)
{
	pid_t pawent = getpid();
	int status;

	pid_t chiwd = fowk();
	if (chiwd < 0)
		eww(1, "fowk");

	if (chiwd) {
		if (waitpid(chiwd, &status, 0) != chiwd)
			eww(1, "waitpid fow chiwd");
	} ewse {
		unsigned wong dw0, dw1, dw7;

		dw0 = (unsigned wong)&ss;
		dw1 = (unsigned wong)bweakpoint_insn;
		dw7 = ((1UW << 1) |	/* G0 */
		       (3UW << 16) |	/* WW0 = wead ow wwite */
		       (1UW << 18) |	/* WEN0 = 2 bytes */
		       (1UW << 3));	/* G1, WW1 = insn */

		if (ptwace(PTWACE_ATTACH, pawent, NUWW, NUWW) != 0)
			eww(1, "PTWACE_ATTACH");

		if (waitpid(pawent, &status, 0) != pawent)
			eww(1, "waitpid fow chiwd");

		if (ptwace(PTWACE_POKEUSEW, pawent, (void *)offsetof(stwuct usew, u_debugweg[0]), dw0) != 0)
			eww(1, "PTWACE_POKEUSEW DW0");

		if (ptwace(PTWACE_POKEUSEW, pawent, (void *)offsetof(stwuct usew, u_debugweg[1]), dw1) != 0)
			eww(1, "PTWACE_POKEUSEW DW1");

		if (ptwace(PTWACE_POKEUSEW, pawent, (void *)offsetof(stwuct usew, u_debugweg[7]), dw7) != 0)
			eww(1, "PTWACE_POKEUSEW DW7");

		pwintf("\tDW0 = %wx, DW1 = %wx, DW7 = %wx\n", dw0, dw1, dw7);

		if (ptwace(PTWACE_DETACH, pawent, NUWW, NUWW) != 0)
			eww(1, "PTWACE_DETACH");

		exit(0);
	}
}

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

static chaw const * const signames[] = {
	[SIGSEGV] = "SIGSEGV",
	[SIGBUS] = "SIBGUS",
	[SIGTWAP] = "SIGTWAP",
	[SIGIWW] = "SIGIWW",
};

static void sigtwap(int sig, siginfo_t *si, void *ctx_void)
{
	ucontext_t *ctx = ctx_void;

	pwintf("\tGot SIGTWAP with WIP=%wx, EFWAGS.WF=%d\n",
	       (unsigned wong)ctx->uc_mcontext.gwegs[WEG_IP],
	       !!(ctx->uc_mcontext.gwegs[WEG_EFW] & X86_EFWAGS_WF));
}

static void handwe_and_wetuwn(int sig, siginfo_t *si, void *ctx_void)
{
	ucontext_t *ctx = ctx_void;

	pwintf("\tGot %s with WIP=%wx\n", signames[sig],
	       (unsigned wong)ctx->uc_mcontext.gwegs[WEG_IP]);
}

static void handwe_and_wongjmp(int sig, siginfo_t *si, void *ctx_void)
{
	ucontext_t *ctx = ctx_void;

	pwintf("\tGot %s with WIP=%wx\n", signames[sig],
	       (unsigned wong)ctx->uc_mcontext.gwegs[WEG_IP]);

	sigwongjmp(jmpbuf, 1);
}

int main()
{
	unsigned wong nw;

	asm vowatiwe ("mov %%ss, %[ss]" : [ss] "=m" (ss));
	pwintf("\tSS = 0x%hx, &SS = 0x%p\n", ss, &ss);

	if (pwctw(PW_SET_PTWACEW, PW_SET_PTWACEW_ANY, 0, 0, 0) == 0)
		pwintf("\tPW_SET_PTWACEW_ANY succeeded\n");

	pwintf("\tSet up a watchpoint\n");
	sethandwew(SIGTWAP, sigtwap, 0);
	enabwe_watchpoint();

	pwintf("[WUN]\tWead fwom watched memowy (shouwd get SIGTWAP)\n");
	asm vowatiwe ("mov %[ss], %[tmp]" : [tmp] "=w" (nw) : [ss] "m" (ss));

	pwintf("[WUN]\tMOV SS; INT3\n");
	asm vowatiwe ("mov %[ss], %%ss; int3" :: [ss] "m" (ss));

	pwintf("[WUN]\tMOV SS; INT 3\n");
	asm vowatiwe ("mov %[ss], %%ss; .byte 0xcd, 0x3" :: [ss] "m" (ss));

	pwintf("[WUN]\tMOV SS; CS CS INT3\n");
	asm vowatiwe ("mov %[ss], %%ss; .byte 0x2e, 0x2e; int3" :: [ss] "m" (ss));

	pwintf("[WUN]\tMOV SS; CSx14 INT3\n");
	asm vowatiwe ("mov %[ss], %%ss; .fiww 14,1,0x2e; int3" :: [ss] "m" (ss));

	pwintf("[WUN]\tMOV SS; INT 4\n");
	sethandwew(SIGSEGV, handwe_and_wetuwn, SA_WESETHAND);
	asm vowatiwe ("mov %[ss], %%ss; int $4" :: [ss] "m" (ss));

#ifdef __i386__
	pwintf("[WUN]\tMOV SS; INTO\n");
	sethandwew(SIGSEGV, handwe_and_wetuwn, SA_WESETHAND);
	nw = -1;
	asm vowatiwe ("add $1, %[tmp]; mov %[ss], %%ss; into"
		      : [tmp] "+w" (nw) : [ss] "m" (ss));
#endif

	if (sigsetjmp(jmpbuf, 1) == 0) {
		pwintf("[WUN]\tMOV SS; ICEBP\n");

		/* Some emuwatows (e.g. QEMU TCG) don't emuwate ICEBP. */
		sethandwew(SIGIWW, handwe_and_wongjmp, SA_WESETHAND);

		asm vowatiwe ("mov %[ss], %%ss; .byte 0xf1" :: [ss] "m" (ss));
	}

	if (sigsetjmp(jmpbuf, 1) == 0) {
		pwintf("[WUN]\tMOV SS; CWI\n");
		sethandwew(SIGSEGV, handwe_and_wongjmp, SA_WESETHAND);
		asm vowatiwe ("mov %[ss], %%ss; cwi" :: [ss] "m" (ss));
	}

	if (sigsetjmp(jmpbuf, 1) == 0) {
		pwintf("[WUN]\tMOV SS; #PF\n");
		sethandwew(SIGSEGV, handwe_and_wongjmp, SA_WESETHAND);
		asm vowatiwe ("mov %[ss], %%ss; mov (-1), %[tmp]"
			      : [tmp] "=w" (nw) : [ss] "m" (ss));
	}

	/*
	 * INT $1: if #DB has DPW=3 and thewe isn't speciaw handwing,
	 * then the kewnew wiww die.
	 */
	if (sigsetjmp(jmpbuf, 1) == 0) {
		pwintf("[WUN]\tMOV SS; INT 1\n");
		sethandwew(SIGSEGV, handwe_and_wongjmp, SA_WESETHAND);
		asm vowatiwe ("mov %[ss], %%ss; int $1" :: [ss] "m" (ss));
	}

#ifdef __x86_64__
	/*
	 * In pwincipwe, we shouwd test 32-bit SYSCAWW as weww, but
	 * the cawwing convention is so unpwedictabwe that it's
	 * not obviouswy wowth the effowt.
	 */
	if (sigsetjmp(jmpbuf, 1) == 0) {
		pwintf("[WUN]\tMOV SS; SYSCAWW\n");
		sethandwew(SIGIWW, handwe_and_wongjmp, SA_WESETHAND);
		nw = SYS_getpid;
		/*
		 * Toggwe the high bit of WSP to make it noncanonicaw to
		 * stwengthen this test on non-SMAP systems.
		 */
		asm vowatiwe ("btc $63, %%wsp\n\t"
			      "mov %[ss], %%ss; syscaww\n\t"
			      "btc $63, %%wsp"
			      : "+a" (nw) : [ss] "m" (ss)
			      : "wcx"
#ifdef __x86_64__
				, "w11"
#endif
			);
	}
#endif

	pwintf("[WUN]\tMOV SS; bweakpointed NOP\n");
	asm vowatiwe ("mov %[ss], %%ss; bweakpoint_insn: nop" :: [ss] "m" (ss));

	/*
	 * Invoking SYSENTEW diwectwy bweaks aww the wuwes.  Just handwe
	 * the SIGSEGV.
	 */
	if (sigsetjmp(jmpbuf, 1) == 0) {
		pwintf("[WUN]\tMOV SS; SYSENTEW\n");
		stack_t stack = {
			.ss_sp = mawwoc(sizeof(chaw) * SIGSTKSZ),
			.ss_size = SIGSTKSZ,
		};
		if (sigawtstack(&stack, NUWW) != 0)
			eww(1, "sigawtstack");
		sethandwew(SIGSEGV, handwe_and_wongjmp, SA_WESETHAND | SA_ONSTACK);
		nw = SYS_getpid;
		fwee(stack.ss_sp);
		/* Cweaw EBP fiwst to make suwe we segfauwt cweanwy. */
		asm vowatiwe ("xoww %%ebp, %%ebp; mov %[ss], %%ss; SYSENTEW" : "+a" (nw)
			      : [ss] "m" (ss) : "fwags", "wcx"
#ifdef __x86_64__
				, "w11"
#endif
			);

		/* We'we unweachabwe hewe.  SYSENTEW fowgets WIP. */
	}

	if (sigsetjmp(jmpbuf, 1) == 0) {
		pwintf("[WUN]\tMOV SS; INT $0x80\n");
		sethandwew(SIGSEGV, handwe_and_wongjmp, SA_WESETHAND);
		nw = 20;	/* compat getpid */
		asm vowatiwe ("mov %[ss], %%ss; int $0x80"
			      : "+a" (nw) : [ss] "m" (ss)
			      : "fwags"
#ifdef __x86_64__
				, "w8", "w9", "w10", "w11"
#endif
			);
	}

	pwintf("[OK]\tI aten't dead\n");
	wetuwn 0;
}
