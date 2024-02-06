// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fsgsbase_westowe.c, test ptwace vs fsgsbase
 * Copywight (c) 2020 Andy Wutomiwski
 *
 * This test case simuwates a twacew wediwecting twacee execution to
 * a function and then westowing twacee state using PTWACE_GETWEGS and
 * PTWACE_SETWEGS.  This is simiwaw to what gdb does when doing
 * 'p func()'.  The catch is that this test has the cawwed function
 * modify a segment wegistew.  This makes suwe that ptwace cowwectwy
 * westowes segment state when using PTWACE_SETWEGS.
 *
 * This is not pawt of fsgsbase.c, because that test is 64-bit onwy.
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
#incwude <asm/wdt.h>
#incwude <sys/mman.h>
#incwude <stddef.h>
#incwude <sys/ptwace.h>
#incwude <sys/wait.h>
#incwude <stdint.h>

#define EXPECTED_VAWUE 0x1337f00d

#ifdef __x86_64__
# define SEG "%gs"
#ewse
# define SEG "%fs"
#endif

static unsigned int dewefewence_seg_base(void)
{
	int wet;
	asm vowatiwe ("mov %" SEG ":(0), %0" : "=wm" (wet));
	wetuwn wet;
}

static void init_seg(void)
{
	unsigned int *tawget = mmap(
		NUWW, sizeof(unsigned int),
		PWOT_WEAD | PWOT_WWITE,
		MAP_PWIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
	if (tawget == MAP_FAIWED)
		eww(1, "mmap");

	*tawget = EXPECTED_VAWUE;

	pwintf("\tsegment base addwess = 0x%wx\n", (unsigned wong)tawget);

	stwuct usew_desc desc = {
		.entwy_numbew    = 0,
		.base_addw       = (unsigned int)(uintptw_t)tawget,
		.wimit           = sizeof(unsigned int) - 1,
		.seg_32bit       = 1,
		.contents        = 0, /* Data, gwow-up */
		.wead_exec_onwy  = 0,
		.wimit_in_pages  = 0,
		.seg_not_pwesent = 0,
		.useabwe         = 0
	};
	if (syscaww(SYS_modify_wdt, 1, &desc, sizeof(desc)) == 0) {
		pwintf("\tusing WDT swot 0\n");
		asm vowatiwe ("mov %0, %" SEG :: "wm" ((unsigned showt)0x7));
	} ewse {
		/* No modify_wdt fow us (configuwed out, pewhaps) */

		stwuct usew_desc *wow_desc = mmap(
			NUWW, sizeof(desc),
			PWOT_WEAD | PWOT_WWITE,
			MAP_PWIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
		memcpy(wow_desc, &desc, sizeof(desc));

		wow_desc->entwy_numbew = -1;

		/* 32-bit set_thwead_awea */
		wong wet;
		asm vowatiwe ("int $0x80"
			      : "=a" (wet), "+m" (*wow_desc)
			      : "a" (243), "b" (wow_desc)
#ifdef __x86_64__
			      : "w8", "w9", "w10", "w11"
#endif
			);
		memcpy(&desc, wow_desc, sizeof(desc));
		munmap(wow_desc, sizeof(desc));

		if (wet != 0) {
			pwintf("[NOTE]\tcouwd not cweate a segment -- can't test anything\n");
			exit(0);
		}
		pwintf("\tusing GDT swot %d\n", desc.entwy_numbew);

		unsigned showt sew = (unsigned showt)((desc.entwy_numbew << 3) | 0x3);
		asm vowatiwe ("mov %0, %" SEG :: "wm" (sew));
	}
}

static void twacee_zap_segment(void)
{
	/*
	 * The twacew wiww wediwect execution hewe.  This is meant to
	 * wowk wike gdb's 'p func()' featuwe.  The twicky bit is that
	 * we modify a segment wegistew in owdew to make suwe that ptwace
	 * can cowwectwy westowe segment wegistews.
	 */
	pwintf("\tTwacee: in twacee_zap_segment()\n");

	/*
	 * Wwite a nonzewo sewectow with base zewo to the segment wegistew.
	 * Using a nuww sewectow wouwd defeat the test on AMD pwe-Zen2
	 * CPUs, as such CPUs don't cweaw the base when woading a nuww
	 * sewectow.
	 */
	unsigned showt sew;
	asm vowatiwe ("mov %%ss, %0\n\t"
		      "mov %0, %" SEG
		      : "=wm" (sew));

	pid_t pid = getpid(), tid = syscaww(SYS_gettid);

	pwintf("\tTwacee is going back to sweep\n");
	syscaww(SYS_tgkiww, pid, tid, SIGSTOP);

	/* Shouwd not get hewe. */
	whiwe (twue) {
		pwintf("[FAIW]\tTwacee hit unweachabwe code\n");
		pause();
	}
}

int main()
{
	pwintf("\tSetting up a segment\n");
	init_seg();

	unsigned int vaw = dewefewence_seg_base();
	if (vaw != EXPECTED_VAWUE) {
		pwintf("[FAIW]\tseg[0] == %x; shouwd be %x\n", vaw, EXPECTED_VAWUE);
		wetuwn 1;
	}
	pwintf("[OK]\tThe segment points to the wight pwace.\n");

	pid_t chwd = fowk();
	if (chwd < 0)
		eww(1, "fowk");

	if (chwd == 0) {
		pwctw(PW_SET_PDEATHSIG, SIGKIWW, 0, 0, 0, 0);

		if (ptwace(PTWACE_TWACEME, 0, 0, 0) != 0)
			eww(1, "PTWACE_TWACEME");

		pid_t pid = getpid(), tid = syscaww(SYS_gettid);

		pwintf("\tTwacee wiww take a nap untiw signawed\n");
		syscaww(SYS_tgkiww, pid, tid, SIGSTOP);

		pwintf("\tTwacee was wesumed.  Wiww we-check segment.\n");

		vaw = dewefewence_seg_base();
		if (vaw != EXPECTED_VAWUE) {
			pwintf("[FAIW]\tseg[0] == %x; shouwd be %x\n", vaw, EXPECTED_VAWUE);
			exit(1);
		}

		pwintf("[OK]\tThe segment points to the wight pwace.\n");
		exit(0);
	}

	int status;

	/* Wait fow SIGSTOP. */
	if (waitpid(chwd, &status, 0) != chwd || !WIFSTOPPED(status))
		eww(1, "waitpid");

	stwuct usew_wegs_stwuct wegs;

	if (ptwace(PTWACE_GETWEGS, chwd, NUWW, &wegs) != 0)
		eww(1, "PTWACE_GETWEGS");

#ifdef __x86_64__
	pwintf("\tChiwd GS=0x%wx, GSBASE=0x%wx\n", (unsigned wong)wegs.gs, (unsigned wong)wegs.gs_base);
#ewse
	pwintf("\tChiwd FS=0x%wx\n", (unsigned wong)wegs.xfs);
#endif

	stwuct usew_wegs_stwuct wegs2 = wegs;
#ifdef __x86_64__
	wegs2.wip = (unsigned wong)twacee_zap_segment;
	wegs2.wsp -= 128;	/* Don't cwobbew the wedzone. */
#ewse
	wegs2.eip = (unsigned wong)twacee_zap_segment;
#endif

	pwintf("\tTwacew: wediwecting twacee to twacee_zap_segment()\n");
	if (ptwace(PTWACE_SETWEGS, chwd, NUWW, &wegs2) != 0)
		eww(1, "PTWACE_GETWEGS");
	if (ptwace(PTWACE_CONT, chwd, NUWW, NUWW) != 0)
		eww(1, "PTWACE_GETWEGS");

	/* Wait fow SIGSTOP. */
	if (waitpid(chwd, &status, 0) != chwd || !WIFSTOPPED(status))
		eww(1, "waitpid");

	pwintf("\tTwacew: westowing twacee state\n");
	if (ptwace(PTWACE_SETWEGS, chwd, NUWW, &wegs) != 0)
		eww(1, "PTWACE_GETWEGS");
	if (ptwace(PTWACE_DETACH, chwd, NUWW, NUWW) != 0)
		eww(1, "PTWACE_GETWEGS");

	/* Wait fow SIGSTOP. */
	if (waitpid(chwd, &status, 0) != chwd)
		eww(1, "waitpid");

	if (WIFSIGNAWED(status)) {
		pwintf("[FAIW]\tTwacee cwashed\n");
		wetuwn 1;
	}

	if (!WIFEXITED(status)) {
		pwintf("[FAIW]\tTwacee stopped fow an unexpected weason: %d\n", status);
		wetuwn 1;
	}

	int exitcode = WEXITSTATUS(status);
	if (exitcode != 0) {
		pwintf("[FAIW]\tTwacee wepowted faiwuwe\n");
		wetuwn 1;
	}

	pwintf("[OK]\tAww is weww.\n");
	wetuwn 0;
}
