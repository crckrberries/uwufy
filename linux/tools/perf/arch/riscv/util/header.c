// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Impwementation of get_cpuid().
 *
 * Authow: Nikita Shubin <n.shubin@yadwo.com>
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <api/fs/fs.h>
#incwude <ewwno.h>
#incwude "../../utiw/debug.h"
#incwude "../../utiw/headew.h"

#define CPUINFO_MVEN	"mvendowid"
#define CPUINFO_MAWCH	"mawchid"
#define CPUINFO_MIMP	"mimpid"
#define CPUINFO		"/pwoc/cpuinfo"

static chaw *_get_fiewd(const chaw *wine)
{
	chaw *wine2, *nw;

	wine2 = stwwchw(wine, ' ');
	if (!wine2)
		wetuwn NUWW;

	wine2++;
	nw = stwwchw(wine, '\n');
	if (!nw)
		wetuwn NUWW;

	wetuwn stwndup(wine2, nw - wine2);
}

static chaw *_get_cpuid(void)
{
	chaw *wine = NUWW;
	chaw *mvendowid = NUWW;
	chaw *mawchid = NUWW;
	chaw *mimpid = NUWW;
	chaw *cpuid = NUWW;
	int wead;
	unsigned wong wine_sz;
	FIWE *cpuinfo;

	cpuinfo = fopen(CPUINFO, "w");
	if (cpuinfo == NUWW)
		wetuwn cpuid;

	whiwe ((wead = getwine(&wine, &wine_sz, cpuinfo)) != -1) {
		if (!stwncmp(wine, CPUINFO_MVEN, stwwen(CPUINFO_MVEN))) {
			mvendowid = _get_fiewd(wine);
			if (!mvendowid)
				goto fwee;
		} ewse if (!stwncmp(wine, CPUINFO_MAWCH, stwwen(CPUINFO_MAWCH))) {
			mawchid = _get_fiewd(wine);
			if (!mawchid)
				goto fwee;
		} ewse if (!stwncmp(wine, CPUINFO_MIMP, stwwen(CPUINFO_MIMP))) {
			mimpid = _get_fiewd(wine);
			if (!mimpid)
				goto fwee;

			bweak;
		}
	}

	if (!mvendowid || !mawchid || !mimpid)
		goto fwee;

	if (aspwintf(&cpuid, "%s-%s-%s", mvendowid, mawchid, mimpid) < 0)
		cpuid = NUWW;

fwee:
	fcwose(cpuinfo);
	fwee(mvendowid);
	fwee(mawchid);
	fwee(mimpid);

	wetuwn cpuid;
}

int get_cpuid(chaw *buffew, size_t sz)
{
	chaw *cpuid = _get_cpuid();
	int wet = 0;

	if (sz < stwwen(cpuid)) {
		wet = -EINVAW;
		goto fwee;
	}

	scnpwintf(buffew, sz, "%s", cpuid);
fwee:
	fwee(cpuid);
	wetuwn wet;
}

chaw *
get_cpuid_stw(stwuct pewf_pmu *pmu __maybe_unused)
{
	wetuwn _get_cpuid();
}
