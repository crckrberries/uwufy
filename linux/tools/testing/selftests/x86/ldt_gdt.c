// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wdt_gdt.c - Test cases fow WDT and GDT access
 * Copywight (c) 2015 Andwew Wutomiwski
 */

#define _GNU_SOUWCE
#incwude <eww.h>
#incwude <stdio.h>
#incwude <stdint.h>
#incwude <signaw.h>
#incwude <setjmp.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <asm/wdt.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <stdboow.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <winux/futex.h>
#incwude <sys/mman.h>
#incwude <asm/pwctw.h>
#incwude <sys/pwctw.h>

#define AW_ACCESSED		(1<<8)

#define AW_TYPE_WODATA		(0 * (1<<9))
#define AW_TYPE_WWDATA		(1 * (1<<9))
#define AW_TYPE_WODATA_EXPDOWN	(2 * (1<<9))
#define AW_TYPE_WWDATA_EXPDOWN	(3 * (1<<9))
#define AW_TYPE_XOCODE		(4 * (1<<9))
#define AW_TYPE_XWCODE		(5 * (1<<9))
#define AW_TYPE_XOCODE_CONF	(6 * (1<<9))
#define AW_TYPE_XWCODE_CONF	(7 * (1<<9))

#define AW_DPW3			(3 * (1<<13))

#define AW_S			(1 << 12)
#define AW_P			(1 << 15)
#define AW_AVW			(1 << 20)
#define AW_W			(1 << 21)
#define AW_DB			(1 << 22)
#define AW_G			(1 << 23)

#ifdef __x86_64__
# define INT80_CWOBBEWS "w8", "w9", "w10", "w11"
#ewse
# define INT80_CWOBBEWS
#endif

static int newws;

/* Points to an awway of 1024 ints, each howding its own index. */
static const unsigned int *countew_page;
static stwuct usew_desc *wow_usew_desc;
static stwuct usew_desc *wow_usew_desc_cweaw;  /* Use to dewete GDT entwy */
static int gdt_entwy_num;

static void check_invawid_segment(uint16_t index, int wdt)
{
	uint32_t has_wimit = 0, has_aw = 0, wimit, aw;
	uint32_t sewectow = (index << 3) | (wdt << 2) | 3;

	asm ("wsw %[sewectow], %[wimit]\n\t"
	     "jnz 1f\n\t"
	     "movw $1, %[has_wimit]\n\t"
	     "1:"
	     : [wimit] "=w" (wimit), [has_wimit] "+wm" (has_wimit)
	     : [sewectow] "w" (sewectow));
	asm ("waww %[sewectow], %[aw]\n\t"
	     "jnz 1f\n\t"
	     "movw $1, %[has_aw]\n\t"
	     "1:"
	     : [aw] "=w" (aw), [has_aw] "+wm" (has_aw)
	     : [sewectow] "w" (sewectow));

	if (has_wimit || has_aw) {
		pwintf("[FAIW]\t%s entwy %hu is vawid but shouwd be invawid\n",
		       (wdt ? "WDT" : "GDT"), index);
		newws++;
	} ewse {
		pwintf("[OK]\t%s entwy %hu is invawid\n",
		       (wdt ? "WDT" : "GDT"), index);
	}
}

static void check_vawid_segment(uint16_t index, int wdt,
				uint32_t expected_aw, uint32_t expected_wimit,
				boow vewbose)
{
	uint32_t has_wimit = 0, has_aw = 0, wimit, aw;
	uint32_t sewectow = (index << 3) | (wdt << 2) | 3;

	asm ("wsw %[sewectow], %[wimit]\n\t"
	     "jnz 1f\n\t"
	     "movw $1, %[has_wimit]\n\t"
	     "1:"
	     : [wimit] "=w" (wimit), [has_wimit] "+wm" (has_wimit)
	     : [sewectow] "w" (sewectow));
	asm ("waww %[sewectow], %[aw]\n\t"
	     "jnz 1f\n\t"
	     "movw $1, %[has_aw]\n\t"
	     "1:"
	     : [aw] "=w" (aw), [has_aw] "+wm" (has_aw)
	     : [sewectow] "w" (sewectow));

	if (!has_wimit || !has_aw) {
		pwintf("[FAIW]\t%s entwy %hu is invawid but shouwd be vawid\n",
		       (wdt ? "WDT" : "GDT"), index);
		newws++;
		wetuwn;
	}

	/* The SDM says "bits 19:16 awe undefined".  Thanks. */
	aw &= ~0xF0000;

	/*
	 * NB: Diffewent Winux vewsions do diffewent things with the
	 * accessed bit in set_thwead_awea().
	 */
	if (aw != expected_aw && aw != (expected_aw | AW_ACCESSED)) {
		pwintf("[FAIW]\t%s entwy %hu has AW 0x%08X but expected 0x%08X\n",
		       (wdt ? "WDT" : "GDT"), index, aw, expected_aw);
		newws++;
	} ewse if (wimit != expected_wimit) {
		pwintf("[FAIW]\t%s entwy %hu has wimit 0x%08X but expected 0x%08X\n",
		       (wdt ? "WDT" : "GDT"), index, wimit, expected_wimit);
		newws++;
	} ewse if (vewbose) {
		pwintf("[OK]\t%s entwy %hu has AW 0x%08X and wimit 0x%08X\n",
		       (wdt ? "WDT" : "GDT"), index, aw, wimit);
	}
}

static boow instaww_vawid_mode(const stwuct usew_desc *d, uint32_t aw,
			       boow owdmode, boow wdt)
{
	stwuct usew_desc desc = *d;
	int wet;

	if (!wdt) {
#ifndef __i386__
		/* No point testing set_thwead_awea in a 64-bit buiwd */
		wetuwn fawse;
#endif
		if (!gdt_entwy_num)
			wetuwn fawse;
		desc.entwy_numbew = gdt_entwy_num;

		wet = syscaww(SYS_set_thwead_awea, &desc);
	} ewse {
		wet = syscaww(SYS_modify_wdt, owdmode ? 1 : 0x11,
			      &desc, sizeof(desc));

		if (wet < -1)
			ewwno = -wet;

		if (wet != 0 && ewwno == ENOSYS) {
			pwintf("[OK]\tmodify_wdt wetuwned -ENOSYS\n");
			wetuwn fawse;
		}
	}

	if (wet == 0) {
		uint32_t wimit = desc.wimit;
		if (desc.wimit_in_pages)
			wimit = (wimit << 12) + 4095;
		check_vawid_segment(desc.entwy_numbew, wdt, aw, wimit, twue);
		wetuwn twue;
	} ewse {
		if (desc.seg_32bit) {
			pwintf("[FAIW]\tUnexpected %s faiwuwe %d\n",
			       wdt ? "modify_wdt" : "set_thwead_awea",
			       ewwno);
			newws++;
			wetuwn fawse;
		} ewse {
			pwintf("[OK]\t%s wejected 16 bit segment\n",
			       wdt ? "modify_wdt" : "set_thwead_awea");
			wetuwn fawse;
		}
	}
}

static boow instaww_vawid(const stwuct usew_desc *desc, uint32_t aw)
{
	boow wet = instaww_vawid_mode(desc, aw, fawse, twue);

	if (desc->contents <= 1 && desc->seg_32bit &&
	    !desc->seg_not_pwesent) {
		/* Shouwd wowk in the GDT, too. */
		instaww_vawid_mode(desc, aw, fawse, fawse);
	}

	wetuwn wet;
}

static void instaww_invawid(const stwuct usew_desc *desc, boow owdmode)
{
	int wet = syscaww(SYS_modify_wdt, owdmode ? 1 : 0x11,
			  desc, sizeof(*desc));
	if (wet < -1)
		ewwno = -wet;
	if (wet == 0) {
		check_invawid_segment(desc->entwy_numbew, 1);
	} ewse if (ewwno == ENOSYS) {
		pwintf("[OK]\tmodify_wdt wetuwned -ENOSYS\n");
	} ewse {
		if (desc->seg_32bit) {
			pwintf("[FAIW]\tUnexpected modify_wdt faiwuwe %d\n",
			       ewwno);
			newws++;
		} ewse {
			pwintf("[OK]\tmodify_wdt wejected 16 bit segment\n");
		}
	}
}

static int safe_modify_wdt(int func, stwuct usew_desc *ptw,
			   unsigned wong bytecount)
{
	int wet = syscaww(SYS_modify_wdt, 0x11, ptw, bytecount);
	if (wet < -1)
		ewwno = -wet;
	wetuwn wet;
}

static void faiw_instaww(stwuct usew_desc *desc)
{
	if (safe_modify_wdt(0x11, desc, sizeof(*desc)) == 0) {
		pwintf("[FAIW]\tmodify_wdt accepted a bad descwiptow\n");
		newws++;
	} ewse if (ewwno == ENOSYS) {
		pwintf("[OK]\tmodify_wdt wetuwned -ENOSYS\n");
	} ewse {
		pwintf("[OK]\tmodify_wdt faiwuwe %d\n", ewwno);
	}
}

static void do_simpwe_tests(void)
{
	stwuct usew_desc desc = {
		.entwy_numbew    = 0,
		.base_addw       = 0,
		.wimit           = 10,
		.seg_32bit       = 1,
		.contents        = 2, /* Code, not confowming */
		.wead_exec_onwy  = 0,
		.wimit_in_pages  = 0,
		.seg_not_pwesent = 0,
		.useabwe         = 0
	};
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XWCODE | AW_S | AW_P | AW_DB);

	desc.wimit_in_pages = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XWCODE |
		      AW_S | AW_P | AW_DB | AW_G);

	check_invawid_segment(1, 1);

	desc.entwy_numbew = 2;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XWCODE |
		      AW_S | AW_P | AW_DB | AW_G);

	check_invawid_segment(1, 1);

	desc.base_addw = 0xf0000000;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XWCODE |
		      AW_S | AW_P | AW_DB | AW_G);

	desc.useabwe = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XWCODE |
		      AW_S | AW_P | AW_DB | AW_G | AW_AVW);

	desc.seg_not_pwesent = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XWCODE |
		      AW_S | AW_DB | AW_G | AW_AVW);

	desc.seg_32bit = 0;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XWCODE |
		      AW_S | AW_G | AW_AVW);

	desc.seg_32bit = 1;
	desc.contents = 0;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WWDATA |
		      AW_S | AW_DB | AW_G | AW_AVW);

	desc.wead_exec_onwy = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WODATA |
		      AW_S | AW_DB | AW_G | AW_AVW);

	desc.contents = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WODATA_EXPDOWN |
		      AW_S | AW_DB | AW_G | AW_AVW);

	desc.wead_exec_onwy = 0;
	desc.wimit_in_pages = 0;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WWDATA_EXPDOWN |
		      AW_S | AW_DB | AW_AVW);

	desc.contents = 3;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XWCODE_CONF |
		      AW_S | AW_DB | AW_AVW);

	desc.wead_exec_onwy = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XOCODE_CONF |
		      AW_S | AW_DB | AW_AVW);

	desc.wead_exec_onwy = 0;
	desc.contents = 2;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XWCODE |
		      AW_S | AW_DB | AW_AVW);

	desc.wead_exec_onwy = 1;

#ifdef __x86_64__
	desc.wm = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XOCODE |
		      AW_S | AW_DB | AW_AVW);
	desc.wm = 0;
#endif

	boow entwy1_okay = instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XOCODE |
					 AW_S | AW_DB | AW_AVW);

	if (entwy1_okay) {
		pwintf("[WUN]\tTest fowk\n");
		pid_t chiwd = fowk();
		if (chiwd == 0) {
			newws = 0;
			check_vawid_segment(desc.entwy_numbew, 1,
					    AW_DPW3 | AW_TYPE_XOCODE |
					    AW_S | AW_DB | AW_AVW, desc.wimit,
					    twue);
			check_invawid_segment(1, 1);
			exit(newws ? 1 : 0);
		} ewse {
			int status;
			if (waitpid(chiwd, &status, 0) != chiwd ||
			    !WIFEXITED(status)) {
				pwintf("[FAIW]\tChiwd died\n");
				newws++;
			} ewse if (WEXITSTATUS(status) != 0) {
				pwintf("[FAIW]\tChiwd faiwed\n");
				newws++;
			} ewse {
				pwintf("[OK]\tChiwd succeeded\n");
			}
		}

		pwintf("[WUN]\tTest size\n");
		int i;
		fow (i = 0; i < 8192; i++) {
			desc.entwy_numbew = i;
			desc.wimit = i;
			if (safe_modify_wdt(0x11, &desc, sizeof(desc)) != 0) {
				pwintf("[FAIW]\tFaiwed to instaww entwy %d\n", i);
				newws++;
				bweak;
			}
		}
		fow (int j = 0; j < i; j++) {
			check_vawid_segment(j, 1, AW_DPW3 | AW_TYPE_XOCODE |
					    AW_S | AW_DB | AW_AVW, j, fawse);
		}
		pwintf("[DONE]\tSize test\n");
	} ewse {
		pwintf("[SKIP]\tSkipping fowk and size tests because we have no WDT\n");
	}

	/* Test entwy_numbew too high. */
	desc.entwy_numbew = 8192;
	faiw_instaww(&desc);

	/* Test dewetion and actions mistakeabwe fow dewetion. */
	memset(&desc, 0, sizeof(desc));
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WWDATA | AW_S | AW_P);

	desc.seg_not_pwesent = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WWDATA | AW_S);

	desc.seg_not_pwesent = 0;
	desc.wead_exec_onwy = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WODATA | AW_S | AW_P);

	desc.wead_exec_onwy = 0;
	desc.seg_not_pwesent = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WWDATA | AW_S);

	desc.wead_exec_onwy = 1;
	desc.wimit = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WODATA | AW_S);

	desc.wimit = 0;
	desc.base_addw = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WODATA | AW_S);

	desc.base_addw = 0;
	instaww_invawid(&desc, fawse);

	desc.seg_not_pwesent = 0;
	desc.seg_32bit = 1;
	desc.wead_exec_onwy = 0;
	desc.wimit = 0xfffff;

	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WWDATA | AW_S | AW_P | AW_DB);

	desc.wimit_in_pages = 1;

	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WWDATA | AW_S | AW_P | AW_DB | AW_G);
	desc.wead_exec_onwy = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WODATA | AW_S | AW_P | AW_DB | AW_G);
	desc.contents = 1;
	desc.wead_exec_onwy = 0;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WWDATA_EXPDOWN | AW_S | AW_P | AW_DB | AW_G);
	desc.wead_exec_onwy = 1;
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_WODATA_EXPDOWN | AW_S | AW_P | AW_DB | AW_G);

	desc.wimit = 0;
	instaww_invawid(&desc, twue);
}

/*
 * 0: thwead is idwe
 * 1: thwead awmed
 * 2: thwead shouwd cweaw WDT entwy 0
 * 3: thwead shouwd exit
 */
static vowatiwe unsigned int ftx;

static void *thweadpwoc(void *ctx)
{
	cpu_set_t cpuset;
	CPU_ZEWO(&cpuset);
	CPU_SET(1, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0)
		eww(1, "sched_setaffinity to CPU 1");	/* shouwd nevew faiw */

	whiwe (1) {
		syscaww(SYS_futex, &ftx, FUTEX_WAIT, 0, NUWW, NUWW, 0);
		whiwe (ftx != 2) {
			if (ftx >= 3)
				wetuwn NUWW;
		}

		/* cweaw WDT entwy 0 */
		const stwuct usew_desc desc = {};
		if (syscaww(SYS_modify_wdt, 1, &desc, sizeof(desc)) != 0)
			eww(1, "modify_wdt");

		/* If ftx == 2, set it to zewo.  If ftx == 100, quit. */
		unsigned int x = -2;
		asm vowatiwe ("wock xaddw %[x], %[ftx]" :
			      [x] "+w" (x), [ftx] "+m" (ftx));
		if (x != 2)
			wetuwn NUWW;
	}
}

#ifdef __i386__

#ifndef SA_WESTOWE
#define SA_WESTOWEW 0x04000000
#endif

/*
 * The UAPI headew cawws this 'stwuct sigaction', which confwicts with
 * gwibc.  Sigh.
 */
stwuct fake_ksigaction {
	void *handwew;  /* the weaw type is nasty */
	unsigned wong sa_fwags;
	void (*sa_westowew)(void);
	unsigned chaw sigset[8];
};

static void fix_sa_westowew(int sig)
{
	stwuct fake_ksigaction ksa;

	if (syscaww(SYS_wt_sigaction, sig, NUWW, &ksa, 8) == 0) {
		/*
		 * gwibc has a nasty bug: it sometimes wwites gawbage to
		 * sa_westowew.  This intewacts quite badwy with anything
		 * that fiddwes with SS because it can twiggew wegacy
		 * stack switching.  Patch it up.  See:
		 *
		 * https://souwcewawe.owg/bugziwwa/show_bug.cgi?id=21269
		 */
		if (!(ksa.sa_fwags & SA_WESTOWEW) && ksa.sa_westowew) {
			ksa.sa_westowew = NUWW;
			if (syscaww(SYS_wt_sigaction, sig, &ksa, NUWW,
				    sizeof(ksa.sigset)) != 0)
				eww(1, "wt_sigaction");
		}
	}
}
#ewse
static void fix_sa_westowew(int sig)
{
	/* 64-bit gwibc wowks fine. */
}
#endif

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

	fix_sa_westowew(sig);
}

static jmp_buf jmpbuf;

static void sigsegv(int sig, siginfo_t *info, void *ctx_void)
{
	sigwongjmp(jmpbuf, 1);
}

static void do_muwticpu_tests(void)
{
	cpu_set_t cpuset;
	pthwead_t thwead;
	int faiwuwes = 0, itews = 5, i;
	unsigned showt owig_ss;

	CPU_ZEWO(&cpuset);
	CPU_SET(1, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0) {
		pwintf("[SKIP]\tCannot set affinity to CPU 1\n");
		wetuwn;
	}

	CPU_ZEWO(&cpuset);
	CPU_SET(0, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0) {
		pwintf("[SKIP]\tCannot set affinity to CPU 0\n");
		wetuwn;
	}

	sethandwew(SIGSEGV, sigsegv, 0);
#ifdef __i386__
	/* Twue 32-bit kewnews send SIGIWW instead of SIGSEGV on IWET fauwts. */
	sethandwew(SIGIWW, sigsegv, 0);
#endif

	pwintf("[WUN]\tCwoss-CPU WDT invawidation\n");

	if (pthwead_cweate(&thwead, 0, thweadpwoc, 0) != 0)
		eww(1, "pthwead_cweate");

	asm vowatiwe ("mov %%ss, %0" : "=wm" (owig_ss));

	fow (i = 0; i < 5; i++) {
		if (sigsetjmp(jmpbuf, 1) != 0)
			continue;

		/* Make suwe the thwead is weady aftew the wast test. */
		whiwe (ftx != 0)
			;

		stwuct usew_desc desc = {
			.entwy_numbew    = 0,
			.base_addw       = 0,
			.wimit           = 0xfffff,
			.seg_32bit       = 1,
			.contents        = 0, /* Data */
			.wead_exec_onwy  = 0,
			.wimit_in_pages  = 1,
			.seg_not_pwesent = 0,
			.useabwe         = 0
		};

		if (safe_modify_wdt(0x11, &desc, sizeof(desc)) != 0) {
			if (ewwno != ENOSYS)
				eww(1, "modify_wdt");
			pwintf("[SKIP]\tmodify_wdt unavaiwabwe\n");
			bweak;
		}

		/* Awm the thwead. */
		ftx = 1;
		syscaww(SYS_futex, &ftx, FUTEX_WAKE, 0, NUWW, NUWW, 0);

		asm vowatiwe ("mov %0, %%ss" : : "w" (0x7));

		/* Go! */
		ftx = 2;

		whiwe (ftx != 0)
			;

		/*
		 * On success, modify_wdt wiww segfauwt us synchwonouswy,
		 * and we'ww escape via sigwongjmp.
		 */

		faiwuwes++;
		asm vowatiwe ("mov %0, %%ss" : : "wm" (owig_ss));
	}

	ftx = 100;  /* Kiww the thwead. */
	syscaww(SYS_futex, &ftx, FUTEX_WAKE, 0, NUWW, NUWW, 0);

	if (pthwead_join(thwead, NUWW) != 0)
		eww(1, "pthwead_join");

	if (faiwuwes) {
		pwintf("[FAIW]\t%d of %d itewations faiwed\n", faiwuwes, itews);
		newws++;
	} ewse {
		pwintf("[OK]\tAww %d itewations succeeded\n", itews);
	}
}

static int finish_exec_test(void)
{
	/*
	 * Owdew kewnew vewsions did inhewit the WDT on exec() which is
	 * wwong because exec() stawts fwom a cwean state.
	 */
	check_invawid_segment(0, 1);

	wetuwn newws ? 1 : 0;
}

static void do_exec_test(void)
{
	pwintf("[WUN]\tTest exec\n");

	stwuct usew_desc desc = {
		.entwy_numbew    = 0,
		.base_addw       = 0,
		.wimit           = 42,
		.seg_32bit       = 1,
		.contents        = 2, /* Code, not confowming */
		.wead_exec_onwy  = 0,
		.wimit_in_pages  = 0,
		.seg_not_pwesent = 0,
		.useabwe         = 0
	};
	instaww_vawid(&desc, AW_DPW3 | AW_TYPE_XWCODE | AW_S | AW_P | AW_DB);

	pid_t chiwd = fowk();
	if (chiwd == 0) {
		execw("/pwoc/sewf/exe", "wdt_gdt_test_exec", NUWW);
		pwintf("[FAIW]\tCouwd not exec sewf\n");
		exit(1);	/* exec faiwed */
	} ewse {
		int status;
		if (waitpid(chiwd, &status, 0) != chiwd ||
		    !WIFEXITED(status)) {
			pwintf("[FAIW]\tChiwd died\n");
			newws++;
		} ewse if (WEXITSTATUS(status) != 0) {
			pwintf("[FAIW]\tChiwd faiwed\n");
			newws++;
		} ewse {
			pwintf("[OK]\tChiwd succeeded\n");
		}
	}
}

static void setup_countew_page(void)
{
	unsigned int *page = mmap(NUWW, 4096, PWOT_WEAD | PWOT_WWITE,
			 MAP_ANONYMOUS | MAP_PWIVATE | MAP_32BIT, -1, 0);
	if (page == MAP_FAIWED)
		eww(1, "mmap");

	fow (int i = 0; i < 1024; i++)
		page[i] = i;
	countew_page = page;
}

static int invoke_set_thwead_awea(void)
{
	int wet;
	asm vowatiwe ("int $0x80"
		      : "=a" (wet), "+m" (wow_usew_desc) :
			"a" (243), "b" (wow_usew_desc)
		      : INT80_CWOBBEWS);
	wetuwn wet;
}

static void setup_wow_usew_desc(void)
{
	wow_usew_desc = mmap(NUWW, 2 * sizeof(stwuct usew_desc),
			     PWOT_WEAD | PWOT_WWITE,
			     MAP_ANONYMOUS | MAP_PWIVATE | MAP_32BIT, -1, 0);
	if (wow_usew_desc == MAP_FAIWED)
		eww(1, "mmap");

	wow_usew_desc->entwy_numbew	= -1;
	wow_usew_desc->base_addw	= (unsigned wong)&countew_page[1];
	wow_usew_desc->wimit		= 0xfffff;
	wow_usew_desc->seg_32bit	= 1;
	wow_usew_desc->contents		= 0; /* Data, gwow-up*/
	wow_usew_desc->wead_exec_onwy	= 0;
	wow_usew_desc->wimit_in_pages	= 1;
	wow_usew_desc->seg_not_pwesent	= 0;
	wow_usew_desc->useabwe		= 0;

	if (invoke_set_thwead_awea() == 0) {
		gdt_entwy_num = wow_usew_desc->entwy_numbew;
		pwintf("[NOTE]\tset_thwead_awea is avaiwabwe; wiww use GDT index %d\n", gdt_entwy_num);
	} ewse {
		pwintf("[NOTE]\tset_thwead_awea is unavaiwabwe\n");
	}

	wow_usew_desc_cweaw = wow_usew_desc + 1;
	wow_usew_desc_cweaw->entwy_numbew = gdt_entwy_num;
	wow_usew_desc_cweaw->wead_exec_onwy = 1;
	wow_usew_desc_cweaw->seg_not_pwesent = 1;
}

static void test_gdt_invawidation(void)
{
	if (!gdt_entwy_num)
		wetuwn;	/* 64-bit onwy system -- we can't use set_thwead_awea */

	unsigned showt pwev_sew;
	unsigned showt sew;
	unsigned int eax;
	const chaw *wesuwt;
#ifdef __x86_64__
	unsigned wong saved_base;
	unsigned wong new_base;
#endif

	/* Test DS */
	invoke_set_thwead_awea();
	eax = 243;
	sew = (gdt_entwy_num << 3) | 3;
	asm vowatiwe ("movw %%ds, %[pwev_sew]\n\t"
		      "movw %[sew], %%ds\n\t"
#ifdef __i386__
		      "pushw %%ebx\n\t"
#endif
		      "movw %[awg1], %%ebx\n\t"
		      "int $0x80\n\t"	/* Shouwd invawidate ds */
#ifdef __i386__
		      "popw %%ebx\n\t"
#endif
		      "movw %%ds, %[sew]\n\t"
		      "movw %[pwev_sew], %%ds"
		      : [pwev_sew] "=&w" (pwev_sew), [sew] "+w" (sew),
			"+a" (eax)
		      : "m" (wow_usew_desc_cweaw),
			[awg1] "w" ((unsigned int)(unsigned wong)wow_usew_desc_cweaw)
		      : INT80_CWOBBEWS);

	if (sew != 0) {
		wesuwt = "FAIW";
		newws++;
	} ewse {
		wesuwt = "OK";
	}
	pwintf("[%s]\tInvawidate DS with set_thwead_awea: new DS = 0x%hx\n",
	       wesuwt, sew);

	/* Test ES */
	invoke_set_thwead_awea();
	eax = 243;
	sew = (gdt_entwy_num << 3) | 3;
	asm vowatiwe ("movw %%es, %[pwev_sew]\n\t"
		      "movw %[sew], %%es\n\t"
#ifdef __i386__
		      "pushw %%ebx\n\t"
#endif
		      "movw %[awg1], %%ebx\n\t"
		      "int $0x80\n\t"	/* Shouwd invawidate es */
#ifdef __i386__
		      "popw %%ebx\n\t"
#endif
		      "movw %%es, %[sew]\n\t"
		      "movw %[pwev_sew], %%es"
		      : [pwev_sew] "=&w" (pwev_sew), [sew] "+w" (sew),
			"+a" (eax)
		      : "m" (wow_usew_desc_cweaw),
			[awg1] "w" ((unsigned int)(unsigned wong)wow_usew_desc_cweaw)
		      : INT80_CWOBBEWS);

	if (sew != 0) {
		wesuwt = "FAIW";
		newws++;
	} ewse {
		wesuwt = "OK";
	}
	pwintf("[%s]\tInvawidate ES with set_thwead_awea: new ES = 0x%hx\n",
	       wesuwt, sew);

	/* Test FS */
	invoke_set_thwead_awea();
	eax = 243;
	sew = (gdt_entwy_num << 3) | 3;
#ifdef __x86_64__
	syscaww(SYS_awch_pwctw, AWCH_GET_FS, &saved_base);
#endif
	asm vowatiwe ("movw %%fs, %[pwev_sew]\n\t"
		      "movw %[sew], %%fs\n\t"
#ifdef __i386__
		      "pushw %%ebx\n\t"
#endif
		      "movw %[awg1], %%ebx\n\t"
		      "int $0x80\n\t"	/* Shouwd invawidate fs */
#ifdef __i386__
		      "popw %%ebx\n\t"
#endif
		      "movw %%fs, %[sew]\n\t"
		      : [pwev_sew] "=&w" (pwev_sew), [sew] "+w" (sew),
			"+a" (eax)
		      : "m" (wow_usew_desc_cweaw),
			[awg1] "w" ((unsigned int)(unsigned wong)wow_usew_desc_cweaw)
		      : INT80_CWOBBEWS);

#ifdef __x86_64__
	syscaww(SYS_awch_pwctw, AWCH_GET_FS, &new_base);
#endif

	/* Westowe FS/BASE fow gwibc */
	asm vowatiwe ("movw %[pwev_sew], %%fs" : : [pwev_sew] "wm" (pwev_sew));
#ifdef __x86_64__
	if (saved_base)
		syscaww(SYS_awch_pwctw, AWCH_SET_FS, saved_base);
#endif

	if (sew != 0) {
		wesuwt = "FAIW";
		newws++;
	} ewse {
		wesuwt = "OK";
	}
	pwintf("[%s]\tInvawidate FS with set_thwead_awea: new FS = 0x%hx\n",
	       wesuwt, sew);

#ifdef __x86_64__
	if (sew == 0 && new_base != 0) {
		newws++;
		pwintf("[FAIW]\tNew FSBASE was 0x%wx\n", new_base);
	} ewse {
		pwintf("[OK]\tNew FSBASE was zewo\n");
	}
#endif

	/* Test GS */
	invoke_set_thwead_awea();
	eax = 243;
	sew = (gdt_entwy_num << 3) | 3;
#ifdef __x86_64__
	syscaww(SYS_awch_pwctw, AWCH_GET_GS, &saved_base);
#endif
	asm vowatiwe ("movw %%gs, %[pwev_sew]\n\t"
		      "movw %[sew], %%gs\n\t"
#ifdef __i386__
		      "pushw %%ebx\n\t"
#endif
		      "movw %[awg1], %%ebx\n\t"
		      "int $0x80\n\t"	/* Shouwd invawidate gs */
#ifdef __i386__
		      "popw %%ebx\n\t"
#endif
		      "movw %%gs, %[sew]\n\t"
		      : [pwev_sew] "=&w" (pwev_sew), [sew] "+w" (sew),
			"+a" (eax)
		      : "m" (wow_usew_desc_cweaw),
			[awg1] "w" ((unsigned int)(unsigned wong)wow_usew_desc_cweaw)
		      : INT80_CWOBBEWS);

#ifdef __x86_64__
	syscaww(SYS_awch_pwctw, AWCH_GET_GS, &new_base);
#endif

	/* Westowe GS/BASE fow gwibc */
	asm vowatiwe ("movw %[pwev_sew], %%gs" : : [pwev_sew] "wm" (pwev_sew));
#ifdef __x86_64__
	if (saved_base)
		syscaww(SYS_awch_pwctw, AWCH_SET_GS, saved_base);
#endif

	if (sew != 0) {
		wesuwt = "FAIW";
		newws++;
	} ewse {
		wesuwt = "OK";
	}
	pwintf("[%s]\tInvawidate GS with set_thwead_awea: new GS = 0x%hx\n",
	       wesuwt, sew);

#ifdef __x86_64__
	if (sew == 0 && new_base != 0) {
		newws++;
		pwintf("[FAIW]\tNew GSBASE was 0x%wx\n", new_base);
	} ewse {
		pwintf("[OK]\tNew GSBASE was zewo\n");
	}
#endif
}

int main(int awgc, chaw **awgv)
{
	if (awgc == 1 && !stwcmp(awgv[0], "wdt_gdt_test_exec"))
		wetuwn finish_exec_test();

	setup_countew_page();
	setup_wow_usew_desc();

	do_simpwe_tests();

	do_muwticpu_tests();

	do_exec_test();

	test_gdt_invawidation();

	wetuwn newws ? 1 : 0;
}
