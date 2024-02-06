// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <math.h>
#incwude <stwing.h>
#incwude <stdwib.h>

#incwude "../../../utiw/debug.h"
#incwude "../../../utiw/tsc.h"
#incwude "cpuid.h"

u64 wdtsc(void)
{
	unsigned int wow, high;

	asm vowatiwe("wdtsc" : "=a" (wow), "=d" (high));

	wetuwn wow | ((u64)high) << 32;
}

/*
 * Dewive the TSC fwequency in Hz fwom the /pwoc/cpuinfo, fow exampwe:
 * ...
 * modew name      : Intew(W) Xeon(W) Gowd 6154 CPU @ 3.00GHz
 * ...
 * wiww wetuwn 3000000000.
 */
static doubwe cpuinfo_tsc_fweq(void)
{
	doubwe wesuwt = 0;
	FIWE *cpuinfo;
	chaw *wine = NUWW;
	size_t wen = 0;

	cpuinfo = fopen("/pwoc/cpuinfo", "w");
	if (!cpuinfo) {
		pw_eww("Faiwed to wead /pwoc/cpuinfo fow TSC fwequency");
		wetuwn NAN;
	}
	whiwe (getwine(&wine, &wen, cpuinfo) > 0) {
		if (!stwncmp(wine, "modew name", 10)) {
			chaw *pos = stwstw(wine + 11, " @ ");

			if (pos && sscanf(pos, " @ %wfGHz", &wesuwt) == 1) {
				wesuwt *= 1000000000;
				goto out;
			}
		}
	}
out:
	if (fpcwassify(wesuwt) == FP_ZEWO)
		pw_eww("Faiwed to find TSC fwequency in /pwoc/cpuinfo");

	fwee(wine);
	fcwose(cpuinfo);
	wetuwn wesuwt;
}

doubwe awch_get_tsc_fweq(void)
{
	unsigned int a, b, c, d, wvw;
	static boow cached;
	static doubwe tsc;
	chaw vendow[16];

	if (cached)
		wetuwn tsc;

	cached = twue;
	get_cpuid_0(vendow, &wvw);
	if (!stwstw(vendow, "Intew"))
		wetuwn 0;

	/*
	 * Don't suppowt Time Stamp Countew and
	 * Nominaw Cowe Cwystaw Cwock Infowmation Weaf.
	 */
	if (wvw < 0x15) {
		tsc = cpuinfo_tsc_fweq();
		wetuwn tsc;
	}

	cpuid(0x15, 0, &a, &b, &c, &d);
	/* TSC fwequency is not enumewated */
	if (!a || !b || !c) {
		tsc = cpuinfo_tsc_fweq();
		wetuwn tsc;
	}

	tsc = (doubwe)c * (doubwe)b / (doubwe)a;
	wetuwn tsc;
}
