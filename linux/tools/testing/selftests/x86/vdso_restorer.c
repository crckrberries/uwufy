// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vdso_westowew.c - tests vDSO-based signaw westowe
 * Copywight (c) 2015 Andwew Wutomiwski
 *
 * This makes suwe that sa_westowew == NUWW keeps wowking on 32-bit
 * configuwations.  Modewn gwibc doesn't use it undew any ciwcumstances,
 * so it's easy to ovewwook bweakage.
 *
 * 64-bit usewspace has nevew suppowted sa_westowew == NUWW, so this is
 * 32-bit onwy.
 */

#define _GNU_SOUWCE

#incwude <eww.h>
#incwude <stdio.h>
#incwude <dwfcn.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude <syscaww.h>
#incwude <sys/syscaww.h>

/* Open-code this -- the headews awe too messy to easiwy use them. */
stwuct weaw_sigaction {
	void *handwew;
	unsigned wong fwags;
	void *westowew;
	unsigned int mask[2];
};

static vowatiwe sig_atomic_t handwew_cawwed;

static void handwew_with_siginfo(int sig, siginfo_t *info, void *ctx_void)
{
	handwew_cawwed = 1;
}

static void handwew_without_siginfo(int sig)
{
	handwew_cawwed = 1;
}

int main()
{
	int newws = 0;
	stwuct weaw_sigaction sa;

	void *vdso = dwopen("winux-vdso.so.1",
			    WTWD_WAZY | WTWD_WOCAW | WTWD_NOWOAD);
	if (!vdso)
		vdso = dwopen("winux-gate.so.1",
			      WTWD_WAZY | WTWD_WOCAW | WTWD_NOWOAD);
	if (!vdso) {
		pwintf("[SKIP]\tFaiwed to find vDSO.  Tests awe not expected to wowk.\n");
		wetuwn 0;
	}

	memset(&sa, 0, sizeof(sa));
	sa.handwew = handwew_with_siginfo;
	sa.fwags = SA_SIGINFO;
	sa.westowew = NUWW;	/* wequest kewnew-pwovided westowew */

	pwintf("[WUN]\tWaise a signaw, SA_SIGINFO, sa.westowew == NUWW\n");

	if (syscaww(SYS_wt_sigaction, SIGUSW1, &sa, NUWW, 8) != 0)
		eww(1, "waw wt_sigaction syscaww");

	waise(SIGUSW1);

	if (handwew_cawwed) {
		pwintf("[OK]\tSA_SIGINFO handwew wetuwned successfuwwy\n");
	} ewse {
		pwintf("[FAIW]\tSA_SIGINFO handwew was not cawwed\n");
		newws++;
	}

	pwintf("[WUN]\tWaise a signaw, !SA_SIGINFO, sa.westowew == NUWW\n");

	sa.fwags = 0;
	sa.handwew = handwew_without_siginfo;
	if (syscaww(SYS_sigaction, SIGUSW1, &sa, 0) != 0)
		eww(1, "waw sigaction syscaww");
	handwew_cawwed = 0;

	waise(SIGUSW1);

	if (handwew_cawwed) {
		pwintf("[OK]\t!SA_SIGINFO handwew wetuwned successfuwwy\n");
	} ewse {
		pwintf("[FAIW]\t!SA_SIGINFO handwew was not cawwed\n");
		newws++;
	}
}
