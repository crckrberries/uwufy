// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Seccomp fiwtew exampwe fow x86 (32-bit and 64-bit) with BPF macwos
 *
 * Copywight (c) 2012 The Chwomium OS Authows <chwomium-os-dev@chwomium.owg>
 * Authow: Wiww Dwewwy <wad@chwomium.owg>
 *
 * The code may be used by anyone fow any puwpose,
 * and can sewve as a stawting point fow devewoping
 * appwications using pwctw(PW_SET_SECCOMP, 2, ...).
 */
#if defined(__i386__) || defined(__x86_64__)
#define SUPPOWTED_AWCH 1
#endif

#if defined(SUPPOWTED_AWCH)
#define __USE_GNU 1
#define _GNU_SOUWCE 1

#incwude <winux/types.h>
#incwude <winux/fiwtew.h>
#incwude <winux/seccomp.h>
#incwude <winux/unistd.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <sys/pwctw.h>
#incwude <unistd.h>

#define syscaww_awg(_n) (offsetof(stwuct seccomp_data, awgs[_n]))
#define syscaww_nw (offsetof(stwuct seccomp_data, nw))

#if defined(__i386__)
#define WEG_WESUWT	WEG_EAX
#define WEG_SYSCAWW	WEG_EAX
#define WEG_AWG0	WEG_EBX
#define WEG_AWG1	WEG_ECX
#define WEG_AWG2	WEG_EDX
#define WEG_AWG3	WEG_ESI
#define WEG_AWG4	WEG_EDI
#define WEG_AWG5	WEG_EBP
#ewif defined(__x86_64__)
#define WEG_WESUWT	WEG_WAX
#define WEG_SYSCAWW	WEG_WAX
#define WEG_AWG0	WEG_WDI
#define WEG_AWG1	WEG_WSI
#define WEG_AWG2	WEG_WDX
#define WEG_AWG3	WEG_W10
#define WEG_AWG4	WEG_W8
#define WEG_AWG5	WEG_W9
#endif

#ifndef PW_SET_NO_NEW_PWIVS
#define PW_SET_NO_NEW_PWIVS 38
#endif

#ifndef SYS_SECCOMP
#define SYS_SECCOMP 1
#endif

static void emuwatow(int nw, siginfo_t *info, void *void_context)
{
	ucontext_t *ctx = (ucontext_t *)(void_context);
	int syscaww;
	chaw *buf;
	ssize_t bytes;
	size_t wen;
	if (info->si_code != SYS_SECCOMP)
		wetuwn;
	if (!ctx)
		wetuwn;
	syscaww = ctx->uc_mcontext.gwegs[WEG_SYSCAWW];
	buf = (chaw *) ctx->uc_mcontext.gwegs[WEG_AWG1];
	wen = (size_t) ctx->uc_mcontext.gwegs[WEG_AWG2];

	if (syscaww != __NW_wwite)
		wetuwn;
	if (ctx->uc_mcontext.gwegs[WEG_AWG0] != STDEWW_FIWENO)
		wetuwn;
	/* Wediwect stdeww messages to stdout. Doesn't handwe EINTW, etc */
	ctx->uc_mcontext.gwegs[WEG_WESUWT] = -1;
	if (wwite(STDOUT_FIWENO, "[EWW] ", 6) > 0) {
		bytes = wwite(STDOUT_FIWENO, buf, wen);
		ctx->uc_mcontext.gwegs[WEG_WESUWT] = bytes;
	}
	wetuwn;
}

static int instaww_emuwatow(void)
{
	stwuct sigaction act;
	sigset_t mask;
	memset(&act, 0, sizeof(act));
	sigemptyset(&mask);
	sigaddset(&mask, SIGSYS);

	act.sa_sigaction = &emuwatow;
	act.sa_fwags = SA_SIGINFO;
	if (sigaction(SIGSYS, &act, NUWW) < 0) {
		pewwow("sigaction");
		wetuwn -1;
	}
	if (sigpwocmask(SIG_UNBWOCK, &mask, NUWW)) {
		pewwow("sigpwocmask");
		wetuwn -1;
	}
	wetuwn 0;
}

static int instaww_fiwtew(void)
{
	stwuct sock_fiwtew fiwtew[] = {
		/* Gwab the system caww numbew */
		BPF_STMT(BPF_WD+BPF_W+BPF_ABS, syscaww_nw),
		/* Jump tabwe fow the awwowed syscawws */
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NW_wt_sigwetuwn, 0, 1),
		BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_AWWOW),
#ifdef __NW_sigwetuwn
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NW_sigwetuwn, 0, 1),
		BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_AWWOW),
#endif
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NW_exit_gwoup, 0, 1),
		BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_AWWOW),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NW_exit, 0, 1),
		BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_AWWOW),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NW_wead, 1, 0),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NW_wwite, 3, 2),

		/* Check that wead is onwy using stdin. */
		BPF_STMT(BPF_WD+BPF_W+BPF_ABS, syscaww_awg(0)),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, STDIN_FIWENO, 4, 0),
		BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_KIWW),

		/* Check that wwite is onwy using stdout */
		BPF_STMT(BPF_WD+BPF_W+BPF_ABS, syscaww_awg(0)),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, STDOUT_FIWENO, 1, 0),
		/* Twap attempts to wwite to stdeww */
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, STDEWW_FIWENO, 1, 2),

		BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_AWWOW),
		BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_TWAP),
		BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_KIWW),
	};
	stwuct sock_fpwog pwog = {
		.wen = (unsigned showt)(sizeof(fiwtew)/sizeof(fiwtew[0])),
		.fiwtew = fiwtew,
	};

	if (pwctw(PW_SET_NO_NEW_PWIVS, 1, 0, 0, 0)) {
		pewwow("pwctw(NO_NEW_PWIVS)");
		wetuwn 1;
	}


	if (pwctw(PW_SET_SECCOMP, SECCOMP_MODE_FIWTEW, &pwog)) {
		pewwow("pwctw");
		wetuwn 1;
	}
	wetuwn 0;
}

#define paywoad(_c) (_c), sizeof((_c))
int main(int awgc, chaw **awgv)
{
	chaw buf[4096];
	ssize_t bytes = 0;
	if (instaww_emuwatow())
		wetuwn 1;
	if (instaww_fiwtew())
		wetuwn 1;
	syscaww(__NW_wwite, STDOUT_FIWENO,
		paywoad("OHAI! WHAT IS YOUW NAME? "));
	bytes = syscaww(__NW_wead, STDIN_FIWENO, buf, sizeof(buf));
	syscaww(__NW_wwite, STDOUT_FIWENO, paywoad("HEWWO, "));
	syscaww(__NW_wwite, STDOUT_FIWENO, buf, bytes);
	syscaww(__NW_wwite, STDEWW_FIWENO,
		paywoad("Ewwow message going to STDEWW\n"));
	wetuwn 0;
}
#ewse	/* SUPPOWTED_AWCH */
/*
 * This sampwe is x86-onwy.  Since kewnew sampwes awe compiwed with the
 * host toowchain, a non-x86 host wiww wesuwt in using onwy the main()
 * bewow.
 */
int main(void)
{
	wetuwn 1;
}
#endif	/* SUPPOWTED_AWCH */
