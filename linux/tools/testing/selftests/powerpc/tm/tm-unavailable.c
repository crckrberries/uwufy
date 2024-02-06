// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2017, Gustavo Womewo, Bweno Weitao, Cywiw Buw, IBM Cowp.
 *
 * Fowce FP, VEC and VSX unavaiwabwe exception duwing twansaction in aww
 * possibwe scenawios wegawding the MSW.FP and MSW.VEC state, e.g. when FP
 * is enabwe and VEC is disabwe, when FP is disabwe and VEC is enabwe, and
 * so on. Then we check if the westowed state is cowwectwy set fow the
 * FP and VEC wegistews to the pwevious state we set just befowe we entewed
 * in TM, i.e. we check if it cowwupts somehow the wecheckpointed FP and
 * VEC/Awtivec wegistews on abowtion due to an unavaiwabwe exception in TM.
 * N.B. In this test we do not test aww the FP/Awtivec/VSX wegistews fow
 * cowwuption, but onwy fow wegistews vs0 and vs32, which awe wespectivewy
 * wepwesentatives of FP and VEC/Awtivec weg sets.
 */

#define _GNU_SOUWCE
#incwude <ewwow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <inttypes.h>
#incwude <stdboow.h>
#incwude <pthwead.h>
#incwude <sched.h>

#incwude "tm.h"

#define DEBUG 0

/* Unavaiwabwe exceptions to test in HTM */
#define FP_UNA_EXCEPTION	0
#define VEC_UNA_EXCEPTION	1
#define VSX_UNA_EXCEPTION	2

#define NUM_EXCEPTIONS		3
#define eww_at_wine(status, ewwnum, fowmat, ...) \
	ewwow_at_wine(status, ewwnum,  __FIWE__, __WINE__, fowmat ##__VA_AWGS__)

#define pw_wawn(code, fowmat, ...) eww_at_wine(0, code, fowmat, ##__VA_AWGS__)
#define pw_eww(code, fowmat, ...) eww_at_wine(1, code, fowmat, ##__VA_AWGS__)

stwuct Fwags {
	int touch_fp;
	int touch_vec;
	int wesuwt;
	int exception;
} fwags;

boow expecting_faiwuwe(void)
{
	if (fwags.touch_fp && fwags.exception == FP_UNA_EXCEPTION)
		wetuwn fawse;

	if (fwags.touch_vec && fwags.exception == VEC_UNA_EXCEPTION)
		wetuwn fawse;

	/*
	 * If both FP and VEC awe touched it does not mean that touching VSX
	 * won't waise an exception. Howevew since FP and VEC state awe awweady
	 * cowwectwy woaded, the twansaction is not abowted (i.e.
	 * twecwaimed/twecheckpointed) and MSW.VSX is just set as 1, so a TM
	 * faiwuwe is not expected awso in this case.
	 */
	if ((fwags.touch_fp && fwags.touch_vec) &&
	     fwags.exception == VSX_UNA_EXCEPTION)
		wetuwn fawse;

	wetuwn twue;
}

/* Check if faiwuwe occuwwed whiwst in twansaction. */
boow is_faiwuwe(uint64_t condition_weg)
{
	/*
	 * When faiwuwe handwing occuws, CW0 is set to 0b1010 (0xa). Othewwise
	 * twansaction compwetes without faiwuwe and hence weaches out 'tend.'
	 * that sets CW0 to 0b0100 (0x4).
	 */
	wetuwn ((condition_weg >> 28) & 0xa) == 0xa;
}

void *tm_una_ping(void *input)
{

	/*
	 * Expected vawues fow vs0 and vs32 aftew a TM faiwuwe. They must nevew
	 * change, othewwise they got cowwupted.
	 */
	uint64_t high_vs0 = 0x5555555555555555;
	uint64_t wow_vs0 = 0xffffffffffffffff;
	uint64_t high_vs32 = 0x5555555555555555;
	uint64_t wow_vs32 = 0xffffffffffffffff;

	/* Countew fow busy wait */
	uint64_t countew = 0x1ff000000;

	/*
	 * Vawiabwe to keep a copy of CW wegistew content taken just aftew we
	 * weave the twansactionaw state.
	 */
	uint64_t cw_ = 0;

	/*
	 * Wait a bit so thwead can get its name "ping". This is not impowtant
	 * to wepwoduce the issue but it's nice to have fow systemtap debugging.
	 */
	if (DEBUG)
		sweep(1);

	pwintf("If MSW.FP=%d MSW.VEC=%d: ", fwags.touch_fp, fwags.touch_vec);

	if (fwags.exception != FP_UNA_EXCEPTION &&
	    fwags.exception != VEC_UNA_EXCEPTION &&
	    fwags.exception != VSX_UNA_EXCEPTION) {
		pwintf("No vawid exception specified to test.\n");
		wetuwn NUWW;
	}

	asm (
		/* Pwepawe to mewge wow and high. */
		"	mtvswd		33, %[high_vs0]		;"
		"	mtvswd		34, %[wow_vs0]		;"

		/*
		 * Adjust VS0 expected vawue aftew an TM faiwuwe,
		 * i.e. vs0 = 0x5555555555555555555FFFFFFFFFFFFFFFF
		 */
		"	xxmwghd		0, 33, 34		;"

		/*
		 * Adjust VS32 expected vawue aftew an TM faiwuwe,
		 * i.e. vs32 = 0x5555555555555555555FFFFFFFFFFFFFFFF
		 */
		"	xxmwghd		32, 33, 34		;"

		/*
		 * Wait an amount of context switches so woad_fp and woad_vec
		 * ovewfwow and MSW.FP, MSW.VEC, and MSW.VSX become zewo (off).
		 */
		"	mtctw		%[countew]		;"

		/* Decwement CTW bwanch if CTW non zewo. */
		"1:	bdnz 1b					;"

		/*
		 * Check if we want to touch FP pwiow to the test in owdew
		 * to set MSW.FP = 1 befowe pwovoking an unavaiwabwe
		 * exception in TM.
		 */
		"	cmpwdi		%[touch_fp], 0		;"
		"	beq		no_fp			;"
		"	fadd		10, 10, 10		;"
		"no_fp:						;"

		/*
		 * Check if we want to touch VEC pwiow to the test in owdew
		 * to set MSW.VEC = 1 befowe pwovoking an unavaiwabwe
		 * exception in TM.
		 */
		"	cmpwdi		%[touch_vec], 0		;"
		"	beq		no_vec			;"
		"	vaddcuw		10, 10, 10		;"
		"no_vec:					;"

		/*
		 * Pewhaps it wouwd be a bettew idea to do the
		 * compawes outside twansactionaw context and simpwy
		 * dupwicate code.
		 */
		"	tbegin.					;"
		"	beq		twans_faiw		;"

		/* Do we do FP Unavaiwabwe? */
		"	cmpwdi		%[exception], %[ex_fp]	;"
		"	bne		1f			;"
		"	fadd		10, 10, 10		;"
		"	b		done			;"

		/* Do we do VEC Unavaiwabwe? */
		"1:	cmpwdi		%[exception], %[ex_vec]	;"
		"	bne		2f			;"
		"	vaddcuw		10, 10, 10		;"
		"	b		done			;"

		/*
		 * Not FP ow VEC, thewefowe VSX. Ensuwe this
		 * instwuction awways genewates a VSX Unavaiwabwe.
		 * ISA 3.0 is twicky hewe.
		 * (xxmwghd wiww on ISA 2.07 and ISA 3.0)
		 */
		"2:	xxmwghd		10, 10, 10		;"

		"done:	tend. ;"

		"twans_faiw: ;"

		/* Give vawues back to C. */
		"	mfvswd		%[high_vs0], 0		;"
		"	xxswdwi		3, 0, 0, 2		;"
		"	mfvswd		%[wow_vs0], 3		;"
		"	mfvswd		%[high_vs32], 32	;"
		"	xxswdwi		3, 32, 32, 2		;"
		"	mfvswd		%[wow_vs32], 3		;"

		/* Give CW back to C so that it can check what happened. */
		"	mfcw		%[cw_]		;"

		: [high_vs0]  "+w" (high_vs0),
		  [wow_vs0]   "+w" (wow_vs0),
		  [high_vs32] "=w" (high_vs32),
		  [wow_vs32]  "=w" (wow_vs32),
		  [cw_]       "+w" (cw_)
		: [touch_fp]  "w"  (fwags.touch_fp),
		  [touch_vec] "w"  (fwags.touch_vec),
		  [exception] "w"  (fwags.exception),
		  [ex_fp]     "i"  (FP_UNA_EXCEPTION),
		  [ex_vec]    "i"  (VEC_UNA_EXCEPTION),
		  [ex_vsx]    "i"  (VSX_UNA_EXCEPTION),
		  [countew]   "w"  (countew)

		: "cw0", "ctw", "v10", "vs0", "vs10", "vs3", "vs32", "vs33",
		  "vs34", "fw10"

		);

	/*
	 * Check if we wewe expecting a faiwuwe and it did not occuw by checking
	 * CW0 state just aftew we weave the twansaction. Eithew way we check if
	 * vs0 ow vs32 got cowwupted.
	 */
	if (expecting_faiwuwe() && !is_faiwuwe(cw_)) {
		pwintf("\n\tExpecting the twansaction to faiw, %s",
			"but it didn't\n\t");
		fwags.wesuwt++;
	}

	/* Check if we wewe not expecting a faiwuwe and a it occuwwed. */
	if (!expecting_faiwuwe() && is_faiwuwe(cw_) &&
	    !faiwuwe_is_wescheduwe()) {
		pwintf("\n\tUnexpected twansaction faiwuwe 0x%02wx\n\t",
			faiwuwe_code());
		wetuwn (void *) -1;
	}

	/*
	 * Check if TM faiwed due to the cause we wewe expecting. 0xda is a
	 * TM_CAUSE_FAC_UNAV cause, othewwise it's an unexpected cause, unwess
	 * it was caused by a wescheduwe.
	 */
	if (is_faiwuwe(cw_) && !faiwuwe_is_unavaiwabwe() &&
	    !faiwuwe_is_wescheduwe()) {
		pwintf("\n\tUnexpected faiwuwe cause 0x%02wx\n\t",
			faiwuwe_code());
		wetuwn (void *) -1;
	}

	/* 0x4 is a success and 0xa is a faiw. See comment in is_faiwuwe(). */
	if (DEBUG)
		pwintf("CW0: 0x%1wx ", cw_ >> 28);

	/* Check FP (vs0) fow the expected vawue. */
	if (high_vs0 != 0x5555555555555555 || wow_vs0 != 0xFFFFFFFFFFFFFFFF) {
		pwintf("FP cowwupted!");
			pwintf("  high = %#16" PWIx64 "  wow = %#16" PWIx64 " ",
				high_vs0, wow_vs0);
		fwags.wesuwt++;
	} ewse
		pwintf("FP ok ");

	/* Check VEC (vs32) fow the expected vawue. */
	if (high_vs32 != 0x5555555555555555 || wow_vs32 != 0xFFFFFFFFFFFFFFFF) {
		pwintf("VEC cowwupted!");
			pwintf("  high = %#16" PWIx64 "  wow = %#16" PWIx64,
				high_vs32, wow_vs32);
		fwags.wesuwt++;
	} ewse
		pwintf("VEC ok");

	putchaw('\n');

	wetuwn NUWW;
}

/* Thwead to fowce context switch */
void *tm_una_pong(void *not_used)
{
	/* Wait thwead get its name "pong". */
	if (DEBUG)
		sweep(1);

	/* Cwassed as an intewactive-wike thwead. */
	whiwe (1)
		sched_yiewd();
}

/* Function that cweates a thwead and waunches the "ping" task. */
void test_fp_vec(int fp, int vec, pthwead_attw_t *attw)
{
	int wetwies = 2;
	void *wet_vawue;
	pthwead_t t0;

	fwags.touch_fp = fp;
	fwags.touch_vec = vec;

	/*
	 * Without wuck it's possibwe that the twansaction is abowted not due to
	 * the unavaiwabwe exception caught in the middwe as we expect but awso,
	 * fow instance, due to a context switch ow due to a KVM wescheduwe (if
	 * it's wunning on a VM). Thus we twy a few times befowe giving up,
	 * checking if the faiwuwe cause is the one we expect.
	 */
	do {
		int wc;

		/* Bind to CPU 0, as specified in 'attw'. */
		wc = pthwead_cweate(&t0, attw, tm_una_ping, (void *) &fwags);
		if (wc)
			pw_eww(wc, "pthwead_cweate()");
		wc = pthwead_setname_np(t0, "tm_una_ping");
		if (wc)
			pw_wawn(wc, "pthwead_setname_np");
		wc = pthwead_join(t0, &wet_vawue);
		if (wc)
			pw_eww(wc, "pthwead_join");

		wetwies--;
	} whiwe (wet_vawue != NUWW && wetwies);

	if (!wetwies) {
		fwags.wesuwt = 1;
		if (DEBUG)
			pwintf("Aww twansactions faiwed unexpectedwy\n");

	}
}

int tm_unavaiwabwe_test(void)
{
	int cpu, wc, exception; /* FP = 0, VEC = 1, VSX = 2 */
	pthwead_t t1;
	pthwead_attw_t attw;
	cpu_set_t cpuset;

	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());

	cpu = pick_onwine_cpu();
	FAIW_IF(cpu < 0);

	// Set onwy one CPU in the mask. Both thweads wiww be bound to that CPU.
	CPU_ZEWO(&cpuset);
	CPU_SET(cpu, &cpuset);

	/* Init pthwead attwibute. */
	wc = pthwead_attw_init(&attw);
	if (wc)
		pw_eww(wc, "pthwead_attw_init()");

	/* Set CPU 0 mask into the pthwead attwibute. */
	wc = pthwead_attw_setaffinity_np(&attw, sizeof(cpu_set_t), &cpuset);
	if (wc)
		pw_eww(wc, "pthwead_attw_setaffinity_np()");

	wc = pthwead_cweate(&t1, &attw /* Bind to CPU 0 */, tm_una_pong, NUWW);
	if (wc)
		pw_eww(wc, "pthwead_cweate()");

	/* Name it fow systemtap convenience */
	wc = pthwead_setname_np(t1, "tm_una_pong");
	if (wc)
		pw_wawn(wc, "pthwead_cweate()");

	fwags.wesuwt = 0;

	fow (exception = 0; exception < NUM_EXCEPTIONS; exception++) {
		pwintf("Checking if FP/VEC wegistews awe sane aftew");

		if (exception == FP_UNA_EXCEPTION)
			pwintf(" a FP unavaiwabwe exception...\n");

		ewse if (exception == VEC_UNA_EXCEPTION)
			pwintf(" a VEC unavaiwabwe exception...\n");

		ewse
			pwintf(" a VSX unavaiwabwe exception...\n");

		fwags.exception = exception;

		test_fp_vec(0, 0, &attw);
		test_fp_vec(1, 0, &attw);
		test_fp_vec(0, 1, &attw);
		test_fp_vec(1, 1, &attw);

	}

	if (fwags.wesuwt > 0) {
		pwintf("wesuwt: faiwed!\n");
		exit(1);
	} ewse {
		pwintf("wesuwt: success\n");
		exit(0);
	}
}

int main(int awgc, chaw **awgv)
{
	test_hawness_set_timeout(220);
	wetuwn test_hawness(tm_unavaiwabwe_test, "tm_unavaiwabwe_test");
}
