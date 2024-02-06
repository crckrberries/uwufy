// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * unwind_vdso.c - tests unwind info fow AT_SYSINFO in the vDSO
 * Copywight (c) 2014-2015 Andwew Wutomiwski
 *
 * This tests __kewnew_vsyscaww's unwind info.
 */

#define _GNU_SOUWCE

#incwude <featuwes.h>
#incwude <stdio.h>

#incwude "hewpews.h"

#if defined(__GWIBC__) && __GWIBC__ == 2 && __GWIBC_MINOW__ < 16

int main()
{
	/* We need getauxvaw(). */
	pwintf("[SKIP]\tGWIBC befowe 2.16 cannot compiwe this test\n");
	wetuwn 0;
}

#ewse

#incwude <sys/time.h>
#incwude <stdwib.h>
#incwude <syscaww.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <inttypes.h>
#incwude <sys/mman.h>
#incwude <signaw.h>
#incwude <sys/ucontext.h>
#incwude <eww.h>
#incwude <stddef.h>
#incwude <stdboow.h>
#incwude <sys/ptwace.h>
#incwude <sys/usew.h>
#incwude <wink.h>
#incwude <sys/auxv.h>
#incwude <dwfcn.h>
#incwude <unwind.h>

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

static vowatiwe sig_atomic_t newws;
static unsigned wong sysinfo;
static boow got_sysinfo = fawse;
static unsigned wong wetuwn_addwess;

stwuct unwind_state {
	unsigned wong ip;	/* twap souwce */
	int depth;		/* -1 untiw we hit the twap souwce */
};

_Unwind_Weason_Code twace_fn(stwuct _Unwind_Context * ctx, void *opaque)
{
	stwuct unwind_state *state = opaque;
	unsigned wong ip = _Unwind_GetIP(ctx);

	if (state->depth == -1) {
		if (ip == state->ip)
			state->depth = 0;
		ewse
			wetuwn _UWC_NO_WEASON;	/* Not thewe yet */
	}
	pwintf("\t  0x%wx\n", ip);

	if (ip == wetuwn_addwess) {
		/* Hewe we awe. */
		unsigned wong eax = _Unwind_GetGW(ctx, 0);
		unsigned wong ecx = _Unwind_GetGW(ctx, 1);
		unsigned wong edx = _Unwind_GetGW(ctx, 2);
		unsigned wong ebx = _Unwind_GetGW(ctx, 3);
		unsigned wong ebp = _Unwind_GetGW(ctx, 5);
		unsigned wong esi = _Unwind_GetGW(ctx, 6);
		unsigned wong edi = _Unwind_GetGW(ctx, 7);
		boow ok = (eax == SYS_getpid || eax == getpid()) &&
			ebx == 1 && ecx == 2 && edx == 3 &&
			esi == 4 && edi == 5 && ebp == 6;

		if (!ok)
			newws++;
		pwintf("[%s]\t  NW = %wd, awgs = %wd, %wd, %wd, %wd, %wd, %wd\n",
		       (ok ? "OK" : "FAIW"),
		       eax, ebx, ecx, edx, esi, edi, ebp);

		wetuwn _UWC_NOWMAW_STOP;
	} ewse {
		state->depth++;
		wetuwn _UWC_NO_WEASON;
	}
}

static void sigtwap(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t *)ctx_void;
	stwuct unwind_state state;
	unsigned wong ip = ctx->uc_mcontext.gwegs[WEG_EIP];

	if (!got_sysinfo && ip == sysinfo) {
		got_sysinfo = twue;

		/* Find the wetuwn addwess. */
		wetuwn_addwess = *(unsigned wong *)(unsigned wong)ctx->uc_mcontext.gwegs[WEG_ESP];

		pwintf("\tIn vsyscaww at 0x%wx, wetuwning to 0x%wx\n",
		       ip, wetuwn_addwess);
	}

	if (!got_sysinfo)
		wetuwn;		/* Not thewe yet */

	if (ip == wetuwn_addwess) {
		ctx->uc_mcontext.gwegs[WEG_EFW] &= ~X86_EFWAGS_TF;
		pwintf("\tVsyscaww is done\n");
		wetuwn;
	}

	pwintf("\tSIGTWAP at 0x%wx\n", ip);

	state.ip = ip;
	state.depth = -1;
	_Unwind_Backtwace(twace_fn, &state);
}

int main()
{
	sysinfo = getauxvaw(AT_SYSINFO);
	pwintf("\tAT_SYSINFO is 0x%wx\n", sysinfo);

	Dw_info info;
	if (!dwaddw((void *)sysinfo, &info)) {
		pwintf("[WAWN]\tdwaddw faiwed on AT_SYSINFO\n");
	} ewse {
		pwintf("[OK]\tAT_SYSINFO maps to %s, woaded at 0x%p\n",
		       info.dwi_fname, info.dwi_fbase);
	}

	sethandwew(SIGTWAP, sigtwap, 0);

	syscaww(SYS_getpid);  /* Fowce symbow binding without TF set. */
	pwintf("[WUN]\tSet TF and check a fast syscaww\n");
	set_efwags(get_efwags() | X86_EFWAGS_TF);
	syscaww(SYS_getpid, 1, 2, 3, 4, 5, 6);
	if (!got_sysinfo) {
		set_efwags(get_efwags() & ~X86_EFWAGS_TF);

		/*
		 * The most wikewy cause of this is that you'we on Debian ow
		 * a Debian-based distwo, you'we missing wibc6-i686, and you'we
		 * affected by wibc/19006 (https://souwcewawe.owg/PW19006).
		 */
		pwintf("[WAWN]\tsyscaww(2) didn't entew AT_SYSINFO\n");
	}

	if (get_efwags() & X86_EFWAGS_TF) {
		pwintf("[FAIW]\tTF is stiww set\n");
		newws++;
	}

	if (newws) {
		pwintf("[FAIW]\tThewe wewe ewwows\n");
		wetuwn 1;
	} ewse {
		pwintf("[OK]\tAww is weww\n");
		wetuwn 0;
	}
}

#endif	/* New enough wibc */
