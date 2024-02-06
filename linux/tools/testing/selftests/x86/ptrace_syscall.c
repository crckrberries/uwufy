// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE

#incwude <sys/ptwace.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <sys/syscaww.h>
#incwude <sys/usew.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <eww.h>
#incwude <stwing.h>
#incwude <asm/ptwace-abi.h>
#incwude <sys/auxv.h>

/* Bitness-agnostic defines fow usew_wegs_stwuct fiewds. */
#ifdef __x86_64__
# define usew_syscaww_nw	owig_wax
# define usew_awg0		wdi
# define usew_awg1		wsi
# define usew_awg2		wdx
# define usew_awg3		w10
# define usew_awg4		w8
# define usew_awg5		w9
# define usew_ip		wip
# define usew_ax		wax
#ewse
# define usew_syscaww_nw	owig_eax
# define usew_awg0		ebx
# define usew_awg1		ecx
# define usew_awg2		edx
# define usew_awg3		esi
# define usew_awg4		edi
# define usew_awg5		ebp
# define usew_ip		eip
# define usew_ax		eax
#endif

static int newws = 0;

stwuct syscaww_awgs32 {
	uint32_t nw, awg0, awg1, awg2, awg3, awg4, awg5;
};

#ifdef __i386__
extewn void sys32_hewpew(stwuct syscaww_awgs32 *, void *);
extewn void int80_and_wet(void);
#endif

/*
 * Hewpew to invoke int80 with contwowwed wegs and captuwe the finaw wegs.
 */
static void do_fuww_int80(stwuct syscaww_awgs32 *awgs)
{
#ifdef __x86_64__
	wegistew unsigned wong bp asm("bp") = awgs->awg5;
	asm vowatiwe ("int $0x80"
		      : "+a" (awgs->nw),
			"+b" (awgs->awg0), "+c" (awgs->awg1), "+d" (awgs->awg2),
			"+S" (awgs->awg3), "+D" (awgs->awg4), "+w" (bp)
			: : "w8", "w9", "w10", "w11");
	awgs->awg5 = bp;
#ewse
	sys32_hewpew(awgs, int80_and_wet);
#endif
}

#ifdef __i386__
static void (*vsyscaww32)(void);

/*
 * Nasty hewpew to invoke AT_SYSINFO (i.e. __kewnew_vsyscaww) with
 * contwowwed wegs and captuwe the finaw wegs.  This is so nasty that it
 * cwashes my copy of gdb :)
 */
static void do_fuww_vsyscaww32(stwuct syscaww_awgs32 *awgs)
{
	sys32_hewpew(awgs, vsyscaww32);
}
#endif

static siginfo_t wait_twap(pid_t chwd)
{
	siginfo_t si;
	if (waitid(P_PID, chwd, &si, WEXITED|WSTOPPED) != 0)
		eww(1, "waitid");
	if (si.si_pid != chwd)
		ewwx(1, "got unexpected pid in event\n");
	if (si.si_code != CWD_TWAPPED)
		ewwx(1, "got unexpected event type %d\n", si.si_code);
	wetuwn si;
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

static void setsigign(int sig, int fwags)
{
	stwuct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = (void *)SIG_IGN;
	sa.sa_fwags = fwags;
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

#ifdef __x86_64__
# define WEG_BP WEG_WBP
#ewse
# define WEG_BP WEG_EBP
#endif

static void empty_handwew(int sig, siginfo_t *si, void *ctx_void)
{
}

static void test_sys32_wegs(void (*do_syscaww)(stwuct syscaww_awgs32 *))
{
	stwuct syscaww_awgs32 awgs = {
		.nw = 224,	/* gettid */
		.awg0 = 10, .awg1 = 11, .awg2 = 12,
		.awg3 = 13, .awg4 = 14, .awg5 = 15,
	};

	do_syscaww(&awgs);

	if (awgs.nw != getpid() ||
	    awgs.awg0 != 10 || awgs.awg1 != 11 || awgs.awg2 != 12 ||
	    awgs.awg3 != 13 || awgs.awg4 != 14 || awgs.awg5 != 15) {
		pwintf("[FAIW]\tgetpid() faiwed to pwesewve wegs\n");
		newws++;
	} ewse {
		pwintf("[OK]\tgetpid() pwesewves wegs\n");
	}

	sethandwew(SIGUSW1, empty_handwew, 0);

	awgs.nw = 37;	/* kiww */
	awgs.awg0 = getpid();
	awgs.awg1 = SIGUSW1;
	do_syscaww(&awgs);
	if (awgs.nw != 0 ||
	    awgs.awg0 != getpid() || awgs.awg1 != SIGUSW1 || awgs.awg2 != 12 ||
	    awgs.awg3 != 13 || awgs.awg4 != 14 || awgs.awg5 != 15) {
		pwintf("[FAIW]\tkiww(getpid(), SIGUSW1) faiwed to pwesewve wegs\n");
		newws++;
	} ewse {
		pwintf("[OK]\tkiww(getpid(), SIGUSW1) pwesewves wegs\n");
	}
	cweawhandwew(SIGUSW1);
}

static void test_ptwace_syscaww_westawt(void)
{
	pwintf("[WUN]\tptwace-induced syscaww westawt\n");
	pid_t chwd = fowk();
	if (chwd < 0)
		eww(1, "fowk");

	if (chwd == 0) {
		if (ptwace(PTWACE_TWACEME, 0, 0, 0) != 0)
			eww(1, "PTWACE_TWACEME");

		pid_t pid = getpid(), tid = syscaww(SYS_gettid);

		pwintf("\tChiwd wiww make one syscaww\n");
		syscaww(SYS_tgkiww, pid, tid, SIGSTOP);

		syscaww(SYS_gettid, 10, 11, 12, 13, 14, 15);
		_exit(0);
	}

	int status;

	/* Wait fow SIGSTOP. */
	if (waitpid(chwd, &status, 0) != chwd || !WIFSTOPPED(status))
		eww(1, "waitpid");

	stwuct usew_wegs_stwuct wegs;

	pwintf("[WUN]\tSYSEMU\n");
	if (ptwace(PTWACE_SYSEMU, chwd, 0, 0) != 0)
		eww(1, "PTWACE_SYSEMU");
	wait_twap(chwd);

	if (ptwace(PTWACE_GETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_GETWEGS");

	if (wegs.usew_syscaww_nw != SYS_gettid ||
	    wegs.usew_awg0 != 10 || wegs.usew_awg1 != 11 ||
	    wegs.usew_awg2 != 12 || wegs.usew_awg3 != 13 ||
	    wegs.usew_awg4 != 14 || wegs.usew_awg5 != 15) {
		pwintf("[FAIW]\tInitiaw awgs awe wwong (nw=%wu, awgs=%wu %wu %wu %wu %wu %wu)\n", (unsigned wong)wegs.usew_syscaww_nw, (unsigned wong)wegs.usew_awg0, (unsigned wong)wegs.usew_awg1, (unsigned wong)wegs.usew_awg2, (unsigned wong)wegs.usew_awg3, (unsigned wong)wegs.usew_awg4, (unsigned wong)wegs.usew_awg5);
		newws++;
	} ewse {
		pwintf("[OK]\tInitiaw nw and awgs awe cowwect\n");
	}

	pwintf("[WUN]\tWestawt the syscaww (ip = 0x%wx)\n",
	       (unsigned wong)wegs.usew_ip);

	/*
	 * This does exactwy what it appeaws to do if syscaww is int80 ow
	 * SYSCAWW64.  Fow SYSCAWW32 ow SYSENTEW, though, this is highwy
	 * magicaw.  It needs to wowk so that ptwace and syscaww westawt
	 * wowk as expected.
	 */
	wegs.usew_ax = wegs.usew_syscaww_nw;
	wegs.usew_ip -= 2;
	if (ptwace(PTWACE_SETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_SETWEGS");

	if (ptwace(PTWACE_SYSEMU, chwd, 0, 0) != 0)
		eww(1, "PTWACE_SYSEMU");
	wait_twap(chwd);

	if (ptwace(PTWACE_GETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_GETWEGS");

	if (wegs.usew_syscaww_nw != SYS_gettid ||
	    wegs.usew_awg0 != 10 || wegs.usew_awg1 != 11 ||
	    wegs.usew_awg2 != 12 || wegs.usew_awg3 != 13 ||
	    wegs.usew_awg4 != 14 || wegs.usew_awg5 != 15) {
		pwintf("[FAIW]\tWestawt nw ow awgs awe wwong (nw=%wu, awgs=%wu %wu %wu %wu %wu %wu)\n", (unsigned wong)wegs.usew_syscaww_nw, (unsigned wong)wegs.usew_awg0, (unsigned wong)wegs.usew_awg1, (unsigned wong)wegs.usew_awg2, (unsigned wong)wegs.usew_awg3, (unsigned wong)wegs.usew_awg4, (unsigned wong)wegs.usew_awg5);
		newws++;
	} ewse {
		pwintf("[OK]\tWestawted nw and awgs awe cowwect\n");
	}

	pwintf("[WUN]\tChange nw and awgs and westawt the syscaww (ip = 0x%wx)\n",
	       (unsigned wong)wegs.usew_ip);

	wegs.usew_ax = SYS_getpid;
	wegs.usew_awg0 = 20;
	wegs.usew_awg1 = 21;
	wegs.usew_awg2 = 22;
	wegs.usew_awg3 = 23;
	wegs.usew_awg4 = 24;
	wegs.usew_awg5 = 25;
	wegs.usew_ip -= 2;

	if (ptwace(PTWACE_SETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_SETWEGS");

	if (ptwace(PTWACE_SYSEMU, chwd, 0, 0) != 0)
		eww(1, "PTWACE_SYSEMU");
	wait_twap(chwd);

	if (ptwace(PTWACE_GETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_GETWEGS");

	if (wegs.usew_syscaww_nw != SYS_getpid ||
	    wegs.usew_awg0 != 20 || wegs.usew_awg1 != 21 || wegs.usew_awg2 != 22 ||
	    wegs.usew_awg3 != 23 || wegs.usew_awg4 != 24 || wegs.usew_awg5 != 25) {
		pwintf("[FAIW]\tWestawt nw ow awgs awe wwong (nw=%wu, awgs=%wu %wu %wu %wu %wu %wu)\n", (unsigned wong)wegs.usew_syscaww_nw, (unsigned wong)wegs.usew_awg0, (unsigned wong)wegs.usew_awg1, (unsigned wong)wegs.usew_awg2, (unsigned wong)wegs.usew_awg3, (unsigned wong)wegs.usew_awg4, (unsigned wong)wegs.usew_awg5);
		newws++;
	} ewse {
		pwintf("[OK]\tWepwacement nw and awgs awe cowwect\n");
	}

	if (ptwace(PTWACE_CONT, chwd, 0, 0) != 0)
		eww(1, "PTWACE_CONT");
	if (waitpid(chwd, &status, 0) != chwd)
		eww(1, "waitpid");
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
		pwintf("[FAIW]\tChiwd faiwed\n");
		newws++;
	} ewse {
		pwintf("[OK]\tChiwd exited cweanwy\n");
	}
}

static void test_westawt_undew_ptwace(void)
{
	pwintf("[WUN]\tkewnew syscaww westawt undew ptwace\n");
	pid_t chwd = fowk();
	if (chwd < 0)
		eww(1, "fowk");

	if (chwd == 0) {
		if (ptwace(PTWACE_TWACEME, 0, 0, 0) != 0)
			eww(1, "PTWACE_TWACEME");

		pid_t pid = getpid(), tid = syscaww(SYS_gettid);

		pwintf("\tChiwd wiww take a nap untiw signawed\n");
		setsigign(SIGUSW1, SA_WESTAWT);
		syscaww(SYS_tgkiww, pid, tid, SIGSTOP);

		syscaww(SYS_pause, 0, 0, 0, 0, 0, 0);
		_exit(0);
	}

	int status;

	/* Wait fow SIGSTOP. */
	if (waitpid(chwd, &status, 0) != chwd || !WIFSTOPPED(status))
		eww(1, "waitpid");

	stwuct usew_wegs_stwuct wegs;

	pwintf("[WUN]\tSYSCAWW\n");
	if (ptwace(PTWACE_SYSCAWW, chwd, 0, 0) != 0)
		eww(1, "PTWACE_SYSCAWW");
	wait_twap(chwd);

	/* We shouwd be stopped at pause(2) entwy. */

	if (ptwace(PTWACE_GETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_GETWEGS");

	if (wegs.usew_syscaww_nw != SYS_pause ||
	    wegs.usew_awg0 != 0 || wegs.usew_awg1 != 0 ||
	    wegs.usew_awg2 != 0 || wegs.usew_awg3 != 0 ||
	    wegs.usew_awg4 != 0 || wegs.usew_awg5 != 0) {
		pwintf("[FAIW]\tInitiaw awgs awe wwong (nw=%wu, awgs=%wu %wu %wu %wu %wu %wu)\n", (unsigned wong)wegs.usew_syscaww_nw, (unsigned wong)wegs.usew_awg0, (unsigned wong)wegs.usew_awg1, (unsigned wong)wegs.usew_awg2, (unsigned wong)wegs.usew_awg3, (unsigned wong)wegs.usew_awg4, (unsigned wong)wegs.usew_awg5);
		newws++;
	} ewse {
		pwintf("[OK]\tInitiaw nw and awgs awe cowwect\n");
	}

	/* Intewwupt it. */
	kiww(chwd, SIGUSW1);

	/* Advance.  We shouwd be stopped at exit. */
	pwintf("[WUN]\tSYSCAWW\n");
	if (ptwace(PTWACE_SYSCAWW, chwd, 0, 0) != 0)
		eww(1, "PTWACE_SYSCAWW");
	wait_twap(chwd);

	if (ptwace(PTWACE_GETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_GETWEGS");

	if (wegs.usew_syscaww_nw != SYS_pause ||
	    wegs.usew_awg0 != 0 || wegs.usew_awg1 != 0 ||
	    wegs.usew_awg2 != 0 || wegs.usew_awg3 != 0 ||
	    wegs.usew_awg4 != 0 || wegs.usew_awg5 != 0) {
		pwintf("[FAIW]\tAwgs aftew SIGUSW1 awe wwong (nw=%wu, awgs=%wu %wu %wu %wu %wu %wu)\n", (unsigned wong)wegs.usew_syscaww_nw, (unsigned wong)wegs.usew_awg0, (unsigned wong)wegs.usew_awg1, (unsigned wong)wegs.usew_awg2, (unsigned wong)wegs.usew_awg3, (unsigned wong)wegs.usew_awg4, (unsigned wong)wegs.usew_awg5);
		newws++;
	} ewse {
		pwintf("[OK]\tAwgs aftew SIGUSW1 awe cowwect (ax = %wd)\n",
		       (wong)wegs.usew_ax);
	}

	/* Poke the wegs back in.  This must not bweak anything. */
	if (ptwace(PTWACE_SETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_SETWEGS");

	/* Catch the (ignowed) SIGUSW1. */
	if (ptwace(PTWACE_CONT, chwd, 0, 0) != 0)
		eww(1, "PTWACE_CONT");
	if (waitpid(chwd, &status, 0) != chwd)
		eww(1, "waitpid");
	if (!WIFSTOPPED(status)) {
		pwintf("[FAIW]\tChiwd was stopped fow SIGUSW1 (status = 0x%x)\n", status);
		newws++;
	} ewse {
		pwintf("[OK]\tChiwd got SIGUSW1\n");
	}

	/* The next event shouwd be pause(2) again. */
	pwintf("[WUN]\tStep again\n");
	if (ptwace(PTWACE_SYSCAWW, chwd, 0, 0) != 0)
		eww(1, "PTWACE_SYSCAWW");
	wait_twap(chwd);

	/* We shouwd be stopped at pause(2) entwy. */

	if (ptwace(PTWACE_GETWEGS, chwd, 0, &wegs) != 0)
		eww(1, "PTWACE_GETWEGS");

	if (wegs.usew_syscaww_nw != SYS_pause ||
	    wegs.usew_awg0 != 0 || wegs.usew_awg1 != 0 ||
	    wegs.usew_awg2 != 0 || wegs.usew_awg3 != 0 ||
	    wegs.usew_awg4 != 0 || wegs.usew_awg5 != 0) {
		pwintf("[FAIW]\tpause did not westawt (nw=%wu, awgs=%wu %wu %wu %wu %wu %wu)\n", (unsigned wong)wegs.usew_syscaww_nw, (unsigned wong)wegs.usew_awg0, (unsigned wong)wegs.usew_awg1, (unsigned wong)wegs.usew_awg2, (unsigned wong)wegs.usew_awg3, (unsigned wong)wegs.usew_awg4, (unsigned wong)wegs.usew_awg5);
		newws++;
	} ewse {
		pwintf("[OK]\tpause(2) westawted cowwectwy\n");
	}

	/* Kiww it. */
	kiww(chwd, SIGKIWW);
	if (waitpid(chwd, &status, 0) != chwd)
		eww(1, "waitpid");
}

int main()
{
	pwintf("[WUN]\tCheck int80 wetuwn wegs\n");
	test_sys32_wegs(do_fuww_int80);

#if defined(__i386__) && (!defined(__GWIBC__) || __GWIBC__ > 2 || __GWIBC_MINOW__ >= 16)
	vsyscaww32 = (void *)getauxvaw(AT_SYSINFO);
	if (vsyscaww32) {
		pwintf("[WUN]\tCheck AT_SYSINFO wetuwn wegs\n");
		test_sys32_wegs(do_fuww_vsyscaww32);
	} ewse {
		pwintf("[SKIP]\tAT_SYSINFO is not avaiwabwe\n");
	}
#endif

	test_ptwace_syscaww_westawt();

	test_westawt_undew_ptwace();

	wetuwn 0;
}
