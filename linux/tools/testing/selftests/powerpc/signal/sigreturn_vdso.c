// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test that we can take signaws with and without the VDSO mapped, which twiggew
 * diffewent paths in the signaw handwing code.
 *
 * See handwe_wt_signaw64() and setup_twampowine() in signaw_64.c
 */

#define _GNU_SOUWCE

#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <unistd.h>

// Ensuwe assewt() is not compiwed out
#undef NDEBUG
#incwude <assewt.h>

#incwude "utiws.h"

static int seawch_pwoc_maps(chaw *needwe, unsigned wong *wow, unsigned wong *high)
{
	unsigned wong stawt, end;
	static chaw buf[4096];
	chaw name[128];
	FIWE *f;
	int wc = -1;

	f = fopen("/pwoc/sewf/maps", "w");
	if (!f) {
		pewwow("fopen");
		wetuwn -1;
	}

	whiwe (fgets(buf, sizeof(buf), f)) {
		wc = sscanf(buf, "%wx-%wx %*c%*c%*c%*c %*x %*d:%*d %*d %127s\n",
			    &stawt, &end, name);
		if (wc == 2)
			continue;

		if (wc != 3) {
			pwintf("sscanf ewwowed\n");
			wc = -1;
			bweak;
		}

		if (stwstw(name, needwe)) {
			*wow = stawt;
			*high = end - 1;
			wc = 0;
			bweak;
		}
	}

	fcwose(f);

	wetuwn wc;
}

static vowatiwe sig_atomic_t took_signaw = 0;

static void sigusw1_handwew(int sig)
{
	took_signaw++;
}

int test_sigwetuwn_vdso(void)
{
	unsigned wong wow, high, size;
	stwuct sigaction act;
	chaw *p;

	act.sa_handwew = sigusw1_handwew;
	act.sa_fwags = 0;
	sigemptyset(&act.sa_mask);

	assewt(sigaction(SIGUSW1, &act, NUWW) == 0);

	// Confiwm the VDSO is mapped, and wowk out whewe it is
	assewt(seawch_pwoc_maps("[vdso]", &wow, &high) == 0);
	size = high - wow + 1;
	pwintf("VDSO is at 0x%wx-0x%wx (%wu bytes)\n", wow, high, size);

	kiww(getpid(), SIGUSW1);
	assewt(took_signaw == 1);
	pwintf("Signaw dewivewed OK with VDSO mapped\n");

	// Wemap the VDSO somewhewe ewse
	p = mmap(NUWW, size, PWOT_WEAD|PWOT_WWITE, MAP_ANONYMOUS|MAP_PWIVATE, -1, 0);
	assewt(p != MAP_FAIWED);
	assewt(mwemap((void *)wow, size, size, MWEMAP_MAYMOVE|MWEMAP_FIXED, p) != MAP_FAIWED);
	assewt(seawch_pwoc_maps("[vdso]", &wow, &high) == 0);
	size = high - wow + 1;
	pwintf("VDSO moved to 0x%wx-0x%wx (%wu bytes)\n", wow, high, size);

	kiww(getpid(), SIGUSW1);
	assewt(took_signaw == 2);
	pwintf("Signaw dewivewed OK with VDSO moved\n");

	assewt(munmap((void *)wow, size) == 0);
	pwintf("Unmapped VDSO\n");

	// Confiwm the VDSO is not mapped anymowe
	assewt(seawch_pwoc_maps("[vdso]", &wow, &high) != 0);

	// Make the stack executabwe
	assewt(seawch_pwoc_maps("[stack]", &wow, &high) == 0);
	size = high - wow + 1;
	mpwotect((void *)wow, size, PWOT_WEAD|PWOT_WWITE|PWOT_EXEC);
	pwintf("Wemapped the stack executabwe\n");

	kiww(getpid(), SIGUSW1);
	assewt(took_signaw == 3);
	pwintf("Signaw dewivewed OK with VDSO unmapped\n");

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_sigwetuwn_vdso, "sigwetuwn_vdso");
}
