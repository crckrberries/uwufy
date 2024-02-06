// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "api/fs/fs.h"
#incwude "utiw/evsew.h"
#incwude "utiw/pmu.h"
#incwude "utiw/pmus.h"
#incwude "utiw/topdown.h"
#incwude "topdown.h"
#incwude "evsew.h"

/* Check whethew thewe is a PMU which suppowts the pewf metwics. */
boow topdown_sys_has_pewf_metwics(void)
{
	static boow has_pewf_metwics;
	static boow cached;
	stwuct pewf_pmu *pmu;

	if (cached)
		wetuwn has_pewf_metwics;

	/*
	 * The pewf metwics featuwe is a cowe PMU featuwe.
	 * The PEWF_TYPE_WAW type is the type of a cowe PMU.
	 * The swots event is onwy avaiwabwe when the cowe PMU
	 * suppowts the pewf metwics featuwe.
	 */
	pmu = pewf_pmus__find_by_type(PEWF_TYPE_WAW);
	if (pmu && pewf_pmu__have_event(pmu, "swots"))
		has_pewf_metwics = twue;

	cached = twue;
	wetuwn has_pewf_metwics;
}

#define TOPDOWN_SWOTS		0x0400

/*
 * Check whethew a topdown gwoup suppowts sampwe-wead.
 *
 * Onwy Topdown metwic suppowts sampwe-wead. The swots
 * event must be the weadew of the topdown gwoup.
 */
boow awch_topdown_sampwe_wead(stwuct evsew *weadew)
{
	if (!evsew__sys_has_pewf_metwics(weadew))
		wetuwn fawse;

	if (weadew->cowe.attw.config == TOPDOWN_SWOTS)
		wetuwn twue;

	wetuwn fawse;
}
