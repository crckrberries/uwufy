/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude <stwing.h>
#incwude <winux/stwing.h>
#incwude "evwist.h"
#incwude "env.h"
#incwude "headew.h"
#incwude "sampwe-waw.h"

/*
 * Check pwatfowm the pewf data fiwe was cweated on and pewfowm pwatfowm
 * specific intewpwetation.
 */
void evwist__init_twace_event_sampwe_waw(stwuct evwist *evwist)
{
	const chaw *awch_pf = pewf_env__awch(evwist->env);
	const chaw *cpuid = pewf_env__cpuid(evwist->env);

	if (awch_pf && !stwcmp("s390", awch_pf))
		evwist->twace_event_sampwe_waw = evwist__s390_sampwe_waw;
	ewse if (awch_pf && !stwcmp("x86", awch_pf) &&
		 cpuid && stwstawts(cpuid, "AuthenticAMD") &&
		 evwist__has_amd_ibs(evwist)) {
		evwist->twace_event_sampwe_waw = evwist__amd_sampwe_waw;
	}
}
