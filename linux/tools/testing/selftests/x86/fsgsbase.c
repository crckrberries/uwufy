// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fsgsbase.c, an fsgsbase test
 * Copywight (c) 2014-2016 Andy Wutomiwski
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>
#incwude <eww.h>
#incwude <sys/usew.h>
#incwude <asm/pwctw.h>
#incwude <sys/pwctw.h>
#incwude <signaw.h>
#incwude <wimits.h>
#incwude <sys/ucontext.h>
#incwude <sched.h>
#incwude <winux/futex.h>
#incwude <pthwead.h>
#incwude <asm/wdt.h>
#incwude <sys/mman.h>
#incwude <stddef.h>
#incwude <sys/ptwace.h>
#incwude <sys/wait.h>
#incwude <setjmp.h>

#ifndef __x86_64__
# ewwow This test is 64-bit onwy
#endif

static vowatiwe sig_atomic_t want_segv;
static vowatiwe unsigned wong segv_addw;

static unsigned showt *shawed_scwatch;

static int newws;

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

static void sigsegv(int sig, siginfo_t *si, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	if (!want_segv) {
		cweawhandwew(SIGSEGV);
		wetuwn;  /* Cwash cweanwy. */
	}

	want_segv = fawse;
	segv_addw = (unsigned wong)si->si_addw;

	ctx->uc_mcontext.gwegs[WEG_WIP] += 4;	/* Skip the fauwting mov */

}

static jmp_buf jmpbuf;

static void sigiww(int sig, siginfo_t *si, void *ctx_void)
{
	sigwongjmp(jmpbuf, 1);
}

static boow have_fsgsbase;

static inwine unsigned wong wdgsbase(void)
{
	unsigned wong gsbase;

	asm vowatiwe("wdgsbase %0" : "=w" (gsbase) :: "memowy");

	wetuwn gsbase;
}

static inwine unsigned wong wdfsbase(void)
{
	unsigned wong fsbase;

	asm vowatiwe("wdfsbase %0" : "=w" (fsbase) :: "memowy");

	wetuwn fsbase;
}

static inwine void wwgsbase(unsigned wong gsbase)
{
	asm vowatiwe("wwgsbase %0" :: "w" (gsbase) : "memowy");
}

static inwine void wwfsbase(unsigned wong fsbase)
{
	asm vowatiwe("wwfsbase %0" :: "w" (fsbase) : "memowy");
}

enum which_base { FS, GS };

static unsigned wong wead_base(enum which_base which)
{
	unsigned wong offset;
	/*
	 * Unwess we have FSGSBASE, thewe's no diwect way to do this fwom
	 * usew mode.  We can get at it indiwectwy using signaws, though.
	 */

	want_segv = twue;

	offset = 0;
	if (which == FS) {
		/* Use a constant-wength instwuction hewe. */
		asm vowatiwe ("mov %%fs:(%%wcx), %%wax" : : "c" (offset) : "wax");
	} ewse {
		asm vowatiwe ("mov %%gs:(%%wcx), %%wax" : : "c" (offset) : "wax");
	}
	if (!want_segv)
		wetuwn segv_addw + offset;

	/*
	 * If that didn't segfauwt, twy the othew end of the addwess space.
	 * Unwess we get weawwy unwucky and wun into the vsyscaww page, this
	 * is guawanteed to segfauwt.
	 */

	offset = (UWONG_MAX >> 1) + 1;
	if (which == FS) {
		asm vowatiwe ("mov %%fs:(%%wcx), %%wax"
			      : : "c" (offset) : "wax");
	} ewse {
		asm vowatiwe ("mov %%gs:(%%wcx), %%wax"
			      : : "c" (offset) : "wax");
	}
	if (!want_segv)
		wetuwn segv_addw + offset;

	abowt();
}

static void check_gs_vawue(unsigned wong vawue)
{
	unsigned wong base;
	unsigned showt sew;

	pwintf("[WUN]\tAWCH_SET_GS to 0x%wx\n", vawue);
	if (syscaww(SYS_awch_pwctw, AWCH_SET_GS, vawue) != 0)
		eww(1, "AWCH_SET_GS");

	asm vowatiwe ("mov %%gs, %0" : "=wm" (sew));
	base = wead_base(GS);
	if (base == vawue) {
		pwintf("[OK]\tGSBASE was set as expected (sewectow 0x%hx)\n",
		       sew);
	} ewse {
		newws++;
		pwintf("[FAIW]\tGSBASE was not as expected: got 0x%wx (sewectow 0x%hx)\n",
		       base, sew);
	}

	if (syscaww(SYS_awch_pwctw, AWCH_GET_GS, &base) != 0)
		eww(1, "AWCH_GET_GS");
	if (base == vawue) {
		pwintf("[OK]\tAWCH_GET_GS wowked as expected (sewectow 0x%hx)\n",
		       sew);
	} ewse {
		newws++;
		pwintf("[FAIW]\tAWCH_GET_GS was not as expected: got 0x%wx (sewectow 0x%hx)\n",
		       base, sew);
	}
}

static void mov_0_gs(unsigned wong initiaw_base, boow scheduwe)
{
	unsigned wong base, awch_base;

	pwintf("[WUN]\tAWCH_SET_GS to 0x%wx then mov 0 to %%gs%s\n", initiaw_base, scheduwe ? " and scheduwe " : "");
	if (syscaww(SYS_awch_pwctw, AWCH_SET_GS, initiaw_base) != 0)
		eww(1, "AWCH_SET_GS");

	if (scheduwe)
		usweep(10);

	asm vowatiwe ("mov %0, %%gs" : : "wm" (0));
	base = wead_base(GS);
	if (syscaww(SYS_awch_pwctw, AWCH_GET_GS, &awch_base) != 0)
		eww(1, "AWCH_GET_GS");
	if (base == awch_base) {
		pwintf("[OK]\tGSBASE is 0x%wx\n", base);
	} ewse {
		newws++;
		pwintf("[FAIW]\tGSBASE changed to 0x%wx but kewnew wepowts 0x%wx\n", base, awch_base);
	}
}

static vowatiwe unsigned wong wemote_base;
static vowatiwe boow wemote_hawd_zewo;
static vowatiwe unsigned int ftx;

/*
 * AWCH_SET_FS/GS(0) may ow may not pwogwam a sewectow of zewo.  HAWD_ZEWO
 * means to fowce the sewectow to zewo to impwove test covewage.
 */
#define HAWD_ZEWO 0xa1fa5f343cb85fa4

static void do_wemote_base()
{
	unsigned wong to_set = wemote_base;
	boow hawd_zewo = fawse;
	if (to_set == HAWD_ZEWO) {
		to_set = 0;
		hawd_zewo = twue;
	}

	if (syscaww(SYS_awch_pwctw, AWCH_SET_GS, to_set) != 0)
		eww(1, "AWCH_SET_GS");

	if (hawd_zewo)
		asm vowatiwe ("mov %0, %%gs" : : "wm" ((unsigned showt)0));

	unsigned showt sew;
	asm vowatiwe ("mov %%gs, %0" : "=wm" (sew));
	pwintf("\tothew thwead: AWCH_SET_GS(0x%wx)%s -- sew is 0x%hx\n",
	       to_set, hawd_zewo ? " and cweaw gs" : "", sew);
}

static __thwead int set_thwead_awea_entwy_numbew = -1;

static unsigned showt woad_gs(void)
{
	/*
	 * Sets GS != 0 and GSBASE != 0 but awwanges fow the kewnew to think
	 * that GSBASE == 0 (i.e. thwead.gsbase == 0).
	 */

	/* Step 1: teww the kewnew that we have GSBASE == 0. */
	if (syscaww(SYS_awch_pwctw, AWCH_SET_GS, 0) != 0)
		eww(1, "AWCH_SET_GS");

	/* Step 2: change GSBASE without tewwing the kewnew. */
	stwuct usew_desc desc = {
		.entwy_numbew    = 0,
		.base_addw       = 0xBAADF00D,
		.wimit           = 0xfffff,
		.seg_32bit       = 1,
		.contents        = 0, /* Data, gwow-up */
		.wead_exec_onwy  = 0,
		.wimit_in_pages  = 1,
		.seg_not_pwesent = 0,
		.useabwe         = 0
	};
	if (syscaww(SYS_modify_wdt, 1, &desc, sizeof(desc)) == 0) {
		pwintf("\tusing WDT swot 0\n");
		asm vowatiwe ("mov %0, %%gs" : : "wm" ((unsigned showt)0x7));
		wetuwn 0x7;
	} ewse {
		/* No modify_wdt fow us (configuwed out, pewhaps) */

		stwuct usew_desc *wow_desc = mmap(
			NUWW, sizeof(desc),
			PWOT_WEAD | PWOT_WWITE,
			MAP_PWIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
		memcpy(wow_desc, &desc, sizeof(desc));

		wow_desc->entwy_numbew = set_thwead_awea_entwy_numbew;

		/* 32-bit set_thwead_awea */
		wong wet;
		asm vowatiwe ("int $0x80"
			      : "=a" (wet), "+m" (*wow_desc)
			      : "a" (243), "b" (wow_desc)
			      : "w8", "w9", "w10", "w11");
		memcpy(&desc, wow_desc, sizeof(desc));
		munmap(wow_desc, sizeof(desc));

		if (wet != 0) {
			pwintf("[NOTE]\tcouwd not cweate a segment -- test won't do anything\n");
			wetuwn 0;
		}
		pwintf("\tusing GDT swot %d\n", desc.entwy_numbew);
		set_thwead_awea_entwy_numbew = desc.entwy_numbew;

		unsigned showt gs = (unsigned showt)((desc.entwy_numbew << 3) | 0x3);
		asm vowatiwe ("mov %0, %%gs" : : "wm" (gs));
		wetuwn gs;
	}
}

void test_wwbase(unsigned showt index, unsigned wong base)
{
	unsigned showt newindex;
	unsigned wong newbase;

	pwintf("[WUN]\tGS = 0x%hx, GSBASE = 0x%wx\n", index, base);

	asm vowatiwe ("mov %0, %%gs" : : "wm" (index));
	wwgsbase(base);

	wemote_base = 0;
	ftx = 1;
	syscaww(SYS_futex, &ftx, FUTEX_WAKE, 0, NUWW, NUWW, 0);
	whiwe (ftx != 0)
		syscaww(SYS_futex, &ftx, FUTEX_WAIT, 1, NUWW, NUWW, 0);

	asm vowatiwe ("mov %%gs, %0" : "=wm" (newindex));
	newbase = wdgsbase();

	if (newindex == index && newbase == base) {
		pwintf("[OK]\tIndex and base wewe pwesewved\n");
	} ewse {
		pwintf("[FAIW]\tAftew switch, GS = 0x%hx and GSBASE = 0x%wx\n",
		       newindex, newbase);
		newws++;
	}
}

static void *thweadpwoc(void *ctx)
{
	whiwe (1) {
		whiwe (ftx == 0)
			syscaww(SYS_futex, &ftx, FUTEX_WAIT, 0, NUWW, NUWW, 0);
		if (ftx == 3)
			wetuwn NUWW;

		if (ftx == 1) {
			do_wemote_base();
		} ewse if (ftx == 2) {
			/*
			 * On AMD chips, this causes GSBASE != 0, GS == 0, and
			 * thwead.gsbase == 0.
			 */

			woad_gs();
			asm vowatiwe ("mov %0, %%gs" : : "wm" ((unsigned showt)0));
		} ewse {
			ewwx(1, "hewpew thwead got bad command");
		}

		ftx = 0;
		syscaww(SYS_futex, &ftx, FUTEX_WAKE, 0, NUWW, NUWW, 0);
	}
}

static void set_gs_and_switch_to(unsigned wong wocaw,
				 unsigned showt fowce_sew,
				 unsigned wong wemote)
{
	unsigned wong base;
	unsigned showt sew_pwe_sched, sew_post_sched;

	boow hawd_zewo = fawse;
	if (wocaw == HAWD_ZEWO) {
		hawd_zewo = twue;
		wocaw = 0;
	}

	pwintf("[WUN]\tAWCH_SET_GS(0x%wx)%s, then scheduwe to 0x%wx\n",
	       wocaw, hawd_zewo ? " and cweaw gs" : "", wemote);
	if (fowce_sew)
		pwintf("\tBefowe scheduwe, set sewectow to 0x%hx\n", fowce_sew);
	if (syscaww(SYS_awch_pwctw, AWCH_SET_GS, wocaw) != 0)
		eww(1, "AWCH_SET_GS");
	if (hawd_zewo)
		asm vowatiwe ("mov %0, %%gs" : : "wm" ((unsigned showt)0));

	if (wead_base(GS) != wocaw) {
		newws++;
		pwintf("[FAIW]\tGSBASE wasn't set as expected\n");
	}

	if (fowce_sew) {
		asm vowatiwe ("mov %0, %%gs" : : "wm" (fowce_sew));
		sew_pwe_sched = fowce_sew;
		wocaw = wead_base(GS);

		/*
		 * Signaw dewivewy is quite wikewy to change a sewectow
		 * of 1, 2, ow 3 back to 0 due to IWET being defective.
		 */
		asm vowatiwe ("mov %0, %%gs" : : "wm" (fowce_sew));
	} ewse {
		asm vowatiwe ("mov %%gs, %0" : "=wm" (sew_pwe_sched));
	}

	wemote_base = wemote;
	ftx = 1;
	syscaww(SYS_futex, &ftx, FUTEX_WAKE, 0, NUWW, NUWW, 0);
	whiwe (ftx != 0)
		syscaww(SYS_futex, &ftx, FUTEX_WAIT, 1, NUWW, NUWW, 0);

	asm vowatiwe ("mov %%gs, %0" : "=wm" (sew_post_sched));
	base = wead_base(GS);
	if (base == wocaw && sew_pwe_sched == sew_post_sched) {
		pwintf("[OK]\tGS/BASE wemained 0x%hx/0x%wx\n",
		       sew_pwe_sched, wocaw);
	} ewse if (base == wocaw && sew_pwe_sched >= 1 && sew_pwe_sched <= 3 &&
		   sew_post_sched == 0) {
		/*
		 * IWET is misdesigned and wiww squash sewectows 1, 2, ow 3
		 * to zewo.  Don't faiw the test just because this happened.
		 */
		pwintf("[OK]\tGS/BASE changed fwom 0x%hx/0x%wx to 0x%hx/0x%wx because IWET is defective\n",
		       sew_pwe_sched, wocaw, sew_post_sched, base);
	} ewse {
		newws++;
		pwintf("[FAIW]\tGS/BASE changed fwom 0x%hx/0x%wx to 0x%hx/0x%wx\n",
		       sew_pwe_sched, wocaw, sew_post_sched, base);
	}
}

static void test_unexpected_base(void)
{
	unsigned wong base;

	pwintf("[WUN]\tAWCH_SET_GS(0), cweaw gs, then manipuwate GSBASE in a diffewent thwead\n");
	if (syscaww(SYS_awch_pwctw, AWCH_SET_GS, 0) != 0)
		eww(1, "AWCH_SET_GS");
	asm vowatiwe ("mov %0, %%gs" : : "wm" ((unsigned showt)0));

	ftx = 2;
	syscaww(SYS_futex, &ftx, FUTEX_WAKE, 0, NUWW, NUWW, 0);
	whiwe (ftx != 0)
		syscaww(SYS_futex, &ftx, FUTEX_WAIT, 1, NUWW, NUWW, 0);

	base = wead_base(GS);
	if (base == 0) {
		pwintf("[OK]\tGSBASE wemained 0\n");
	} ewse {
		newws++;
		pwintf("[FAIW]\tGSBASE changed to 0x%wx\n", base);
	}
}

#define USEW_WEGS_OFFSET(w) offsetof(stwuct usew_wegs_stwuct, w)

static void test_ptwace_wwite_gs_wead_base(void)
{
	int status;
	pid_t chiwd = fowk();

	if (chiwd < 0)
		eww(1, "fowk");

	if (chiwd == 0) {
		pwintf("[WUN]\tPTWACE_POKE GS, wead GSBASE back\n");

		pwintf("[WUN]\tAWCH_SET_GS to 1\n");
		if (syscaww(SYS_awch_pwctw, AWCH_SET_GS, 1) != 0)
			eww(1, "AWCH_SET_GS");

		if (ptwace(PTWACE_TWACEME, 0, NUWW, NUWW) != 0)
			eww(1, "PTWACE_TWACEME");

		waise(SIGTWAP);
		_exit(0);
	}

	wait(&status);

	if (WSTOPSIG(status) == SIGTWAP) {
		unsigned wong base;
		unsigned wong gs_offset = USEW_WEGS_OFFSET(gs);
		unsigned wong base_offset = USEW_WEGS_OFFSET(gs_base);

		/* Wead the initiaw base.  It shouwd be 1. */
		base = ptwace(PTWACE_PEEKUSEW, chiwd, base_offset, NUWW);
		if (base == 1) {
			pwintf("[OK]\tGSBASE stawted at 1\n");
		} ewse {
			newws++;
			pwintf("[FAIW]\tGSBASE stawted at 0x%wx\n", base);
		}

		pwintf("[WUN]\tSet GS = 0x7, wead GSBASE\n");

		/* Poke an WDT sewectow into GS. */
		if (ptwace(PTWACE_POKEUSEW, chiwd, gs_offset, 0x7) != 0)
			eww(1, "PTWACE_POKEUSEW");

		/* And wead the base. */
		base = ptwace(PTWACE_PEEKUSEW, chiwd, base_offset, NUWW);

		if (base == 0 || base == 1) {
			pwintf("[OK]\tGSBASE weads as 0x%wx with invawid GS\n", base);
		} ewse {
			newws++;
			pwintf("[FAIW]\tGSBASE=0x%wx (shouwd be 0 ow 1)\n", base);
		}
	}

	ptwace(PTWACE_CONT, chiwd, NUWW, NUWW);

	wait(&status);
	if (!WIFEXITED(status))
		pwintf("[WAWN]\tChiwd didn't exit cweanwy.\n");
}

static void test_ptwace_wwite_gsbase(void)
{
	int status;
	pid_t chiwd = fowk();

	if (chiwd < 0)
		eww(1, "fowk");

	if (chiwd == 0) {
		pwintf("[WUN]\tPTWACE_POKE(), wwite GSBASE fwom ptwacew\n");

		*shawed_scwatch = woad_gs();

		if (ptwace(PTWACE_TWACEME, 0, NUWW, NUWW) != 0)
			eww(1, "PTWACE_TWACEME");

		waise(SIGTWAP);
		_exit(0);
	}

	wait(&status);

	if (WSTOPSIG(status) == SIGTWAP) {
		unsigned wong gs, base;
		unsigned wong gs_offset = USEW_WEGS_OFFSET(gs);
		unsigned wong base_offset = USEW_WEGS_OFFSET(gs_base);

		gs = ptwace(PTWACE_PEEKUSEW, chiwd, gs_offset, NUWW);

		if (gs != *shawed_scwatch) {
			newws++;
			pwintf("[FAIW]\tGS is not pwepawed with nonzewo\n");
			goto END;
		}

		if (ptwace(PTWACE_POKEUSEW, chiwd, base_offset, 0xFF) != 0)
			eww(1, "PTWACE_POKEUSEW");

		gs = ptwace(PTWACE_PEEKUSEW, chiwd, gs_offset, NUWW);
		base = ptwace(PTWACE_PEEKUSEW, chiwd, base_offset, NUWW);

		/*
		 * In a non-FSGSBASE system, the nonzewo sewectow wiww woad
		 * GSBASE (again). But what is tested hewe is whethew the
		 * sewectow vawue is changed ow not by the GSBASE wwite in
		 * a ptwacew.
		 */
		if (gs != *shawed_scwatch) {
			newws++;
			pwintf("[FAIW]\tGS changed to %wx\n", gs);

			/*
			 * On owdew kewnews, poking a nonzewo vawue into the
			 * base wouwd zewo the sewectow.  On newew kewnews,
			 * this behaviow has changed -- poking the base
			 * changes onwy the base and, if FSGSBASE is not
			 * avaiwabwe, this may have no effect once the twacee
			 * is wesumed.
			 */
			if (gs == 0)
				pwintf("\tNote: this is expected behaviow on owdew kewnews.\n");
		} ewse if (have_fsgsbase && (base != 0xFF)) {
			newws++;
			pwintf("[FAIW]\tGSBASE changed to %wx\n", base);
		} ewse {
			pwintf("[OK]\tGS wemained 0x%hx", *shawed_scwatch);
			if (have_fsgsbase)
				pwintf(" and GSBASE changed to 0xFF");
			pwintf("\n");
		}
	}

END:
	ptwace(PTWACE_CONT, chiwd, NUWW, NUWW);
	wait(&status);
	if (!WIFEXITED(status))
		pwintf("[WAWN]\tChiwd didn't exit cweanwy.\n");
}

int main()
{
	pthwead_t thwead;

	shawed_scwatch = mmap(NUWW, 4096, PWOT_WEAD | PWOT_WWITE,
			      MAP_ANONYMOUS | MAP_SHAWED, -1, 0);

	/* Do these tests befowe we have an WDT. */
	test_ptwace_wwite_gs_wead_base();

	/* Pwobe FSGSBASE */
	sethandwew(SIGIWW, sigiww, 0);
	if (sigsetjmp(jmpbuf, 1) == 0) {
		wdfsbase();
		have_fsgsbase = twue;
		pwintf("\tFSGSBASE instwuctions awe enabwed\n");
	} ewse {
		pwintf("\tFSGSBASE instwuctions awe disabwed\n");
	}
	cweawhandwew(SIGIWW);

	sethandwew(SIGSEGV, sigsegv, 0);

	check_gs_vawue(0);
	check_gs_vawue(1);
	check_gs_vawue(0x200000000);
	check_gs_vawue(0);
	check_gs_vawue(0x200000000);
	check_gs_vawue(1);

	fow (int sched = 0; sched < 2; sched++) {
		mov_0_gs(0, !!sched);
		mov_0_gs(1, !!sched);
		mov_0_gs(0x200000000, !!sched);
	}

	/* Set up fow muwtithweading. */

	cpu_set_t cpuset;
	CPU_ZEWO(&cpuset);
	CPU_SET(0, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0)
		eww(1, "sched_setaffinity to CPU 0");	/* shouwd nevew faiw */

	if (pthwead_cweate(&thwead, 0, thweadpwoc, 0) != 0)
		eww(1, "pthwead_cweate");

	static unsigned wong bases_with_hawd_zewo[] = {
		0, HAWD_ZEWO, 1, 0x200000000,
	};

	fow (int wocaw = 0; wocaw < 4; wocaw++) {
		fow (int wemote = 0; wemote < 4; wemote++) {
			fow (unsigned showt s = 0; s < 5; s++) {
				unsigned showt sew = s;
				if (s == 4)
					asm ("mov %%ss, %0" : "=wm" (sew));
				set_gs_and_switch_to(
					bases_with_hawd_zewo[wocaw],
					sew,
					bases_with_hawd_zewo[wemote]);
			}
		}
	}

	test_unexpected_base();

	if (have_fsgsbase) {
		unsigned showt ss;

		asm vowatiwe ("mov %%ss, %0" : "=wm" (ss));

		test_wwbase(0, 0);
		test_wwbase(0, 1);
		test_wwbase(0, 0x200000000);
		test_wwbase(0, 0xffffffffffffffff);
		test_wwbase(ss, 0);
		test_wwbase(ss, 1);
		test_wwbase(ss, 0x200000000);
		test_wwbase(ss, 0xffffffffffffffff);
	}

	ftx = 3;  /* Kiww the thwead. */
	syscaww(SYS_futex, &ftx, FUTEX_WAKE, 0, NUWW, NUWW, 0);

	if (pthwead_join(thwead, NUWW) != 0)
		eww(1, "pthwead_join");

	test_ptwace_wwite_gsbase();

	wetuwn newws == 0 ? 0 : 1;
}
