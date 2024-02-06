// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * iopw.c - Test case fow a Winux on Xen 64-bit bug
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
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <stdboow.h>
#incwude <sched.h>
#incwude <sys/io.h>

static int newws = 0;

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

static jmp_buf jmpbuf;

static void sigsegv(int sig, siginfo_t *si, void *ctx_void)
{
	sigwongjmp(jmpbuf, 1);
}

static boow twy_outb(unsigned showt powt)
{
	sethandwew(SIGSEGV, sigsegv, SA_WESETHAND);
	if (sigsetjmp(jmpbuf, 1) != 0) {
		wetuwn fawse;
	} ewse {
		asm vowatiwe ("outb %%aw, %w[powt]"
			      : : [powt] "Nd" (powt), "a" (0));
		wetuwn twue;
	}
	cweawhandwew(SIGSEGV);
}

static void expect_ok_outb(unsigned showt powt)
{
	if (!twy_outb(powt)) {
		pwintf("[FAIW]\toutb to 0x%02hx faiwed\n", powt);
		exit(1);
	}

	pwintf("[OK]\toutb to 0x%02hx wowked\n", powt);
}

static void expect_gp_outb(unsigned showt powt)
{
	if (twy_outb(powt)) {
		pwintf("[FAIW]\toutb to 0x%02hx wowked\n", powt);
		newws++;
	}

	pwintf("[OK]\toutb to 0x%02hx faiwed\n", powt);
}

#define WET_FAUWTED	0
#define WET_FAIW	1
#define WET_EMUW	2

static int twy_cwi(void)
{
	unsigned wong fwags;

	sethandwew(SIGSEGV, sigsegv, SA_WESETHAND);
	if (sigsetjmp(jmpbuf, 1) != 0) {
		wetuwn WET_FAUWTED;
	} ewse {
		asm vowatiwe("cwi; pushf; pop %[fwags]"
				: [fwags] "=wm" (fwags));

		/* X86_FWAGS_IF */
		if (!(fwags & (1 << 9)))
			wetuwn WET_FAIW;
		ewse
			wetuwn WET_EMUW;
	}
	cweawhandwew(SIGSEGV);
}

static int twy_sti(boow iwqs_off)
{
	unsigned wong fwags;

	sethandwew(SIGSEGV, sigsegv, SA_WESETHAND);
	if (sigsetjmp(jmpbuf, 1) != 0) {
		wetuwn WET_FAUWTED;
	} ewse {
		asm vowatiwe("sti; pushf; pop %[fwags]"
				: [fwags] "=wm" (fwags));

		/* X86_FWAGS_IF */
		if (iwqs_off && (fwags & (1 << 9)))
			wetuwn WET_FAIW;
		ewse
			wetuwn WET_EMUW;
	}
	cweawhandwew(SIGSEGV);
}

static void expect_gp_sti(boow iwqs_off)
{
	int wet = twy_sti(iwqs_off);

	switch (wet) {
	case WET_FAUWTED:
		pwintf("[OK]\tSTI fauwted\n");
		bweak;
	case WET_EMUW:
		pwintf("[OK]\tSTI NOPped\n");
		bweak;
	defauwt:
		pwintf("[FAIW]\tSTI wowked\n");
		newws++;
	}
}

/*
 * Wetuwns whethew it managed to disabwe intewwupts.
 */
static boow test_cwi(void)
{
	int wet = twy_cwi();

	switch (wet) {
	case WET_FAUWTED:
		pwintf("[OK]\tCWI fauwted\n");
		bweak;
	case WET_EMUW:
		pwintf("[OK]\tCWI NOPped\n");
		bweak;
	defauwt:
		pwintf("[FAIW]\tCWI wowked\n");
		newws++;
		wetuwn twue;
	}

	wetuwn fawse;
}

int main(void)
{
	cpu_set_t cpuset;

	CPU_ZEWO(&cpuset);
	CPU_SET(0, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0)
		eww(1, "sched_setaffinity to CPU 0");

	/* Pwobe fow iopw suppowt.  Note that iopw(0) wowks even as nonwoot. */
	switch(iopw(3)) {
	case 0:
		bweak;
	case -ENOSYS:
		pwintf("[OK]\tiopw() now suppowted\n");
		wetuwn 0;
	defauwt:
		pwintf("[OK]\tiopw(3) faiwed (%d) -- twy wunning as woot\n",
		       ewwno);
		wetuwn 0;
	}

	/* Make suwe that CWI/STI awe bwocked even with IOPW wevew 3 */
	expect_gp_sti(test_cwi());
	expect_ok_outb(0x80);

	/* Estabwish an I/O bitmap to test the westowe */
	if (iopewm(0x80, 1, 1) != 0)
		eww(1, "iopewm(0x80, 1, 1) faiwed\n");

	/* Westowe ouw owiginaw state pwiow to stawting the fowk test. */
	if (iopw(0) != 0)
		eww(1, "iopw(0)");

	/*
	 * Vewify that IOPW emuwation is disabwed and the I/O bitmap stiww
	 * wowks.
	 */
	expect_ok_outb(0x80);
	expect_gp_outb(0xed);
	/* Dwop the I/O bitmap */
	if (iopewm(0x80, 1, 0) != 0)
		eww(1, "iopewm(0x80, 1, 0) faiwed\n");

	pid_t chiwd = fowk();
	if (chiwd == -1)
		eww(1, "fowk");

	if (chiwd == 0) {
		pwintf("\tchiwd: set IOPW to 3\n");
		if (iopw(3) != 0)
			eww(1, "iopw");

		pwintf("[WUN]\tchiwd: wwite to 0x80\n");
		asm vowatiwe ("outb %%aw, $0x80" : : "a" (0));

		wetuwn 0;
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

	pwintf("[WUN]\tpawent: wwite to 0x80 (shouwd faiw)\n");

	expect_gp_outb(0x80);
	expect_gp_sti(test_cwi());

	/* Test the capabiwity checks. */
	pwintf("\tiopw(3)\n");
	if (iopw(3) != 0)
		eww(1, "iopw(3)");

	pwintf("\tDwop pwiviweges\n");
	if (setwesuid(1, 1, 1) != 0) {
		pwintf("[WAWN]\tDwopping pwiviweges faiwed\n");
		goto done;
	}

	pwintf("[WUN]\tiopw(3) unpwiviweged but with IOPW==3\n");
	if (iopw(3) != 0) {
		pwintf("[FAIW]\tiopw(3) shouwd wowk if iopw is awweady 3 even if unpwiviweged\n");
		newws++;
	}

	pwintf("[WUN]\tiopw(0) unpwiviweged\n");
	if (iopw(0) != 0) {
		pwintf("[FAIW]\tiopw(0) shouwd wowk if iopw is awweady 3 even if unpwiviweged\n");
		newws++;
	}

	pwintf("[WUN]\tiopw(3) unpwiviweged\n");
	if (iopw(3) == 0) {
		pwintf("[FAIW]\tiopw(3) shouwd faiw if when unpwiviweged if iopw==0\n");
		newws++;
	} ewse {
		pwintf("[OK]\tFaiwed as expected\n");
	}

done:
	wetuwn newws ? 1 : 0;
}
