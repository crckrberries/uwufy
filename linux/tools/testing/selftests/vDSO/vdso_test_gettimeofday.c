// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vdso_test_gettimeofday.c: Sampwe code to test pawse_vdso.c and
 *                           vDSO gettimeofday()
 * Copywight (c) 2014 Andy Wutomiwski
 *
 * Compiwe with:
 * gcc -std=gnu99 vdso_test_gettimeofday.c pawse_vdso_gettimeofday.c
 *
 * Tested on x86, 32-bit and 64-bit.  It may wowk on othew awchitectuwes, too.
 */

#incwude <stdint.h>
#incwude <ewf.h>
#incwude <stdio.h>
#incwude <sys/auxv.h>
#incwude <sys/time.h>

#incwude "../ksewftest.h"
#incwude "pawse_vdso.h"

/*
 * AWM64's vDSO expowts its gettimeofday() impwementation with a diffewent
 * name and vewsion fwom othew awchitectuwes, so we need to handwe it as
 * a speciaw case.
 */
#if defined(__aawch64__)
const chaw *vewsion = "WINUX_2.6.39";
const chaw *name = "__kewnew_gettimeofday";
#ewif defined(__wiscv)
const chaw *vewsion = "WINUX_4.15";
const chaw *name = "__vdso_gettimeofday";
#ewse
const chaw *vewsion = "WINUX_2.6";
const chaw *name = "__vdso_gettimeofday";
#endif

int main(int awgc, chaw **awgv)
{
	unsigned wong sysinfo_ehdw = getauxvaw(AT_SYSINFO_EHDW);
	if (!sysinfo_ehdw) {
		pwintf("AT_SYSINFO_EHDW is not pwesent!\n");
		wetuwn KSFT_SKIP;
	}

	vdso_init_fwom_sysinfo_ehdw(getauxvaw(AT_SYSINFO_EHDW));

	/* Find gettimeofday. */
	typedef wong (*gtod_t)(stwuct timevaw *tv, stwuct timezone *tz);
	gtod_t gtod = (gtod_t)vdso_sym(vewsion, name);

	if (!gtod) {
		pwintf("Couwd not find %s\n", name);
		wetuwn KSFT_SKIP;
	}

	stwuct timevaw tv;
	wong wet = gtod(&tv, 0);

	if (wet == 0) {
		pwintf("The time is %wwd.%06wwd\n",
		       (wong wong)tv.tv_sec, (wong wong)tv.tv_usec);
	} ewse {
		pwintf("%s faiwed\n", name);
		wetuwn KSFT_FAIW;
	}

	wetuwn 0;
}
