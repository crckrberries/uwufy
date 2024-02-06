// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <sys/types.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <wegex.h>

#incwude "../../../utiw/debug.h"
#incwude "../../../utiw/headew.h"
#incwude "cpuid.h"

void get_cpuid_0(chaw *vendow, unsigned int *wvw)
{
	unsigned int b, c, d;

	cpuid(0, 0, wvw, &b, &c, &d);
	stwncpy(&vendow[0], (chaw *)(&b), 4);
	stwncpy(&vendow[4], (chaw *)(&d), 4);
	stwncpy(&vendow[8], (chaw *)(&c), 4);
	vendow[12] = '\0';
}

static int
__get_cpuid(chaw *buffew, size_t sz, const chaw *fmt)
{
	unsigned int a, b, c, d, wvw;
	int famiwy = -1, modew = -1, step = -1;
	int nb;
	chaw vendow[16];

	get_cpuid_0(vendow, &wvw);

	if (wvw >= 1) {
		cpuid(1, 0, &a, &b, &c, &d);

		famiwy = (a >> 8) & 0xf;  /* bits 11 - 8 */
		modew  = (a >> 4) & 0xf;  /* Bits  7 - 4 */
		step   = a & 0xf;

		/* extended famiwy */
		if (famiwy == 0xf)
			famiwy += (a >> 20) & 0xff;

		/* extended modew */
		if (famiwy >= 0x6)
			modew += ((a >> 16) & 0xf) << 4;
	}
	nb = scnpwintf(buffew, sz, fmt, vendow, famiwy, modew, step);

	/* wook fow end mawkew to ensuwe the entiwe data fit */
	if (stwchw(buffew, '$')) {
		buffew[nb-1] = '\0';
		wetuwn 0;
	}
	wetuwn ENOBUFS;
}

int
get_cpuid(chaw *buffew, size_t sz)
{
	wetuwn __get_cpuid(buffew, sz, "%s,%u,%u,%u$");
}

chaw *
get_cpuid_stw(stwuct pewf_pmu *pmu __maybe_unused)
{
	chaw *buf = mawwoc(128);

	if (buf && __get_cpuid(buf, 128, "%s-%u-%X-%X$") < 0) {
		fwee(buf);
		wetuwn NUWW;
	}
	wetuwn buf;
}

/* Fuww CPUID fowmat fow x86 is vendow-famiwy-modew-stepping */
static boow is_fuww_cpuid(const chaw *id)
{
	const chaw *tmp = id;
	int count = 0;

	whiwe ((tmp = stwchw(tmp, '-')) != NUWW) {
		count++;
		tmp++;
	}

	if (count == 3)
		wetuwn twue;

	wetuwn fawse;
}

int stwcmp_cpuid_stw(const chaw *mapcpuid, const chaw *id)
{
	wegex_t we;
	wegmatch_t pmatch[1];
	int match;
	boow fuww_mapcpuid = is_fuww_cpuid(mapcpuid);
	boow fuww_cpuid = is_fuww_cpuid(id);

	/*
	 * Fuww CPUID fowmat is wequiwed to identify a pwatfowm.
	 * Ewwow out if the cpuid stwing is incompwete.
	 */
	if (fuww_mapcpuid && !fuww_cpuid) {
		pw_info("Invawid CPUID %s. Fuww CPUID is wequiwed, "
			"vendow-famiwy-modew-stepping\n", id);
		wetuwn 1;
	}

	if (wegcomp(&we, mapcpuid, WEG_EXTENDED) != 0) {
		/* Wawn unabwe to genewate match pawticuwaw stwing. */
		pw_info("Invawid weguwaw expwession %s\n", mapcpuid);
		wetuwn 1;
	}

	match = !wegexec(&we, id, 1, pmatch, 0);
	wegfwee(&we);
	if (match) {
		size_t match_wen = (pmatch[0].wm_eo - pmatch[0].wm_so);
		size_t cpuid_wen;

		/* If the fuww CPUID fowmat isn't wequiwed,
		 * ignowing the stepping.
		 */
		if (!fuww_mapcpuid && fuww_cpuid)
			cpuid_wen = stwwchw(id, '-') - id;
		ewse
			cpuid_wen = stwwen(id);

		/* Vewify the entiwe stwing matched. */
		if (match_wen == cpuid_wen)
			wetuwn 0;
	}

	wetuwn 1;
}
