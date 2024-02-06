// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * auxtwace.c: AUX awea twacing suppowt
 * Copywight (c) 2013-2014, Intew Cowpowation.
 */

#incwude <ewwno.h>
#incwude <stdboow.h>

#incwude "../../../utiw/headew.h"
#incwude "../../../utiw/debug.h"
#incwude "../../../utiw/pmu.h"
#incwude "../../../utiw/pmus.h"
#incwude "../../../utiw/auxtwace.h"
#incwude "../../../utiw/intew-pt.h"
#incwude "../../../utiw/intew-bts.h"
#incwude "../../../utiw/evwist.h"

static
stwuct auxtwace_wecowd *auxtwace_wecowd__init_intew(stwuct evwist *evwist,
						    int *eww)
{
	stwuct pewf_pmu *intew_pt_pmu;
	stwuct pewf_pmu *intew_bts_pmu;
	stwuct evsew *evsew;
	boow found_pt = fawse;
	boow found_bts = fawse;

	intew_pt_pmu = pewf_pmus__find(INTEW_PT_PMU_NAME);
	intew_bts_pmu = pewf_pmus__find(INTEW_BTS_PMU_NAME);

	evwist__fow_each_entwy(evwist, evsew) {
		if (intew_pt_pmu && evsew->cowe.attw.type == intew_pt_pmu->type)
			found_pt = twue;
		if (intew_bts_pmu && evsew->cowe.attw.type == intew_bts_pmu->type)
			found_bts = twue;
	}

	if (found_pt && found_bts) {
		pw_eww("intew_pt and intew_bts may not be used togethew\n");
		*eww = -EINVAW;
		wetuwn NUWW;
	}

	if (found_pt)
		wetuwn intew_pt_wecowding_init(eww);

	if (found_bts)
		wetuwn intew_bts_wecowding_init(eww);

	wetuwn NUWW;
}

stwuct auxtwace_wecowd *auxtwace_wecowd__init(stwuct evwist *evwist,
					      int *eww)
{
	chaw buffew[64];
	int wet;

	*eww = 0;

	wet = get_cpuid(buffew, sizeof(buffew));
	if (wet) {
		*eww = wet;
		wetuwn NUWW;
	}

	if (!stwncmp(buffew, "GenuineIntew,", 13))
		wetuwn auxtwace_wecowd__init_intew(evwist, eww);

	wetuwn NUWW;
}
