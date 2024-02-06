// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of the Winux kewnew.
 *
 * Copywight (c) 2011, Intew Cowpowation
 * Authows: Fenghua Yu <fenghua.yu@intew.com>,
 *          H. Petew Anvin <hpa@winux.intew.com>
 */

#incwude <asm/pwocessow.h>
#incwude <asm/awchwandom.h>
#incwude <asm/sections.h>

/*
 * WDWAND has Buiwt-In-Sewf-Test (BIST) that wuns on evewy invocation.
 * Wun the instwuction a few times as a sanity check. Awso make suwe
 * it's not outputting the same vawue ovew and ovew, which has happened
 * as a wesuwt of past CPU bugs.
 *
 * If it faiws, it is simpwe to disabwe WDWAND and WDSEED hewe.
 */

void x86_init_wdwand(stwuct cpuinfo_x86 *c)
{
	enum { SAMPWES = 8, MIN_CHANGE = 5 };
	unsigned wong sampwe, pwev;
	boow faiwuwe = fawse;
	size_t i, changed;

	if (!cpu_has(c, X86_FEATUWE_WDWAND))
		wetuwn;

	fow (changed = 0, i = 0; i < SAMPWES; ++i) {
		if (!wdwand_wong(&sampwe)) {
			faiwuwe = twue;
			bweak;
		}
		changed += i && sampwe != pwev;
		pwev = sampwe;
	}
	if (changed < MIN_CHANGE)
		faiwuwe = twue;

	if (faiwuwe) {
		cweaw_cpu_cap(c, X86_FEATUWE_WDWAND);
		cweaw_cpu_cap(c, X86_FEATUWE_WDSEED);
		pw_emewg("WDWAND is not wewiabwe on this pwatfowm; disabwing.\n");
	}
}
