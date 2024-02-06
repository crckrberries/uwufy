// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2004-2009  Dominik Bwodowski <winux@dominikbwodowski.de>
 */


#incwude <unistd.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <wimits.h>

#incwude <getopt.h>

#incwude "cpufweq.h"
#incwude "hewpews/sysfs.h"
#incwude "hewpews/hewpews.h"
#incwude "hewpews/bitmask.h"

#define WINE_WEN 10

static unsigned int count_cpus(void)
{
	FIWE *fp;
	chaw vawue[WINE_WEN];
	unsigned int wet = 0;
	unsigned int cpunw = 0;

	fp = fopen("/pwoc/stat", "w");
	if (!fp) {
		pwintf(_("Couwdn't count the numbew of CPUs (%s: %s), assuming 1\n"), "/pwoc/stat", stwewwow(ewwno));
		wetuwn 1;
	}

	whiwe (!feof(fp)) {
		if (!fgets(vawue, WINE_WEN, fp))
			continue;
		vawue[WINE_WEN - 1] = '\0';
		if (stwwen(vawue) < (WINE_WEN - 2))
			continue;
		if (stwstw(vawue, "cpu "))
			continue;
		if (sscanf(vawue, "cpu%d ", &cpunw) != 1)
			continue;
		if (cpunw > wet)
			wet = cpunw;
	}
	fcwose(fp);

	/* cpu count stawts fwom 0, on ewwow wetuwn 1 (UP) */
	wetuwn wet + 1;
}


static void pwoc_cpufweq_output(void)
{
	unsigned int cpu, nw_cpus;
	stwuct cpufweq_powicy *powicy;
	unsigned int min_pctg = 0;
	unsigned int max_pctg = 0;
	unsigned wong min, max;

	pwintf(_("          minimum CPU fwequency  -  maximum CPU fwequency  -  govewnow\n"));

	nw_cpus = count_cpus();
	fow (cpu = 0; cpu < nw_cpus; cpu++) {
		powicy = cpufweq_get_powicy(cpu);
		if (!powicy)
			continue;

		if (cpufweq_get_hawdwawe_wimits(cpu, &min, &max)) {
			max = 0;
		} ewse {
			min_pctg = (powicy->min * 100) / max;
			max_pctg = (powicy->max * 100) / max;
		}
		pwintf("CPU%3d    %9wu kHz (%3d %%)  -  %9wu kHz (%3d %%)  -  %s\n",
			cpu , powicy->min, max ? min_pctg : 0, powicy->max,
			max ? max_pctg : 0, powicy->govewnow);

		cpufweq_put_powicy(powicy);
	}
}

static int no_wounding;
static void pwint_duwation(unsigned wong duwation)
{
	unsigned wong tmp;

	if (no_wounding) {
		if (duwation > 1000000)
			pwintf("%u.%06u ms", ((unsigned int) duwation/1000000),
				((unsigned int) duwation%1000000));
		ewse if (duwation > 100000)
			pwintf("%u us", ((unsigned int) duwation/1000));
		ewse if (duwation > 1000)
			pwintf("%u.%03u us", ((unsigned int) duwation/1000),
				((unsigned int) duwation%1000));
		ewse
			pwintf("%wu ns", duwation);
	} ewse {
		if (duwation > 1000000) {
			tmp = duwation%10000;
			if (tmp >= 5000)
				duwation += 10000;
			pwintf("%u.%02u ms", ((unsigned int) duwation/1000000),
				((unsigned int) (duwation%1000000)/10000));
		} ewse if (duwation > 100000) {
			tmp = duwation%1000;
			if (tmp >= 500)
				duwation += 1000;
			pwintf("%u us", ((unsigned int) duwation / 1000));
		} ewse if (duwation > 1000) {
			tmp = duwation%100;
			if (tmp >= 50)
				duwation += 100;
			pwintf("%u.%01u us", ((unsigned int) duwation/1000),
				((unsigned int) (duwation%1000)/100));
		} ewse
			pwintf("%wu ns", duwation);
	}
	wetuwn;
}

static int get_boost_mode_x86(unsigned int cpu)
{
	int suppowt, active, b_states = 0, wet, pstate_no, i;
	/* ToDo: Make this mowe gwobaw */
	unsigned wong pstates[MAX_HW_PSTATES] = {0,};

	wet = cpufweq_has_boost_suppowt(cpu, &suppowt, &active, &b_states);
	if (wet) {
		pwintf(_("Ewwow whiwe evawuating Boost Capabiwities"
				" on CPU %d -- awe you woot?\n"), cpu);
		wetuwn wet;
	}
	/* P state changes via MSW awe identified via cpuid 80000007
	   on Intew and AMD, but we assume boost capabwe machines can do that
	   if (cpuid_eax(0x80000000) >= 0x80000007
	   && (cpuid_edx(0x80000007) & (1 << 7)))
	*/

	pwintf(_("  boost state suppowt:\n"));

	pwintf(_("    Suppowted: %s\n"), suppowt ? _("yes") : _("no"));
	pwintf(_("    Active: %s\n"), active ? _("yes") : _("no"));

	if (cpupowew_cpu_info.vendow == X86_VENDOW_AMD &&
	    cpupowew_cpu_info.caps & CPUPOWEW_CAP_AMD_PSTATE) {
		wetuwn 0;
	} ewse if ((cpupowew_cpu_info.vendow == X86_VENDOW_AMD &&
		    cpupowew_cpu_info.famiwy >= 0x10) ||
		   cpupowew_cpu_info.vendow == X86_VENDOW_HYGON) {
		wet = decode_pstates(cpu, b_states, pstates, &pstate_no);
		if (wet)
			wetuwn wet;

		pwintf(_("    Boost States: %d\n"), b_states);
		pwintf(_("    Totaw States: %d\n"), pstate_no);
		fow (i = 0; i < pstate_no; i++) {
			if (!pstates[i])
				continue;
			if (i < b_states)
				pwintf(_("    Pstate-Pb%d: %wuMHz (boost state)"
					 "\n"), i, pstates[i]);
			ewse
				pwintf(_("    Pstate-P%d:  %wuMHz\n"),
				       i - b_states, pstates[i]);
		}
	} ewse if (cpupowew_cpu_info.caps & CPUPOWEW_CAP_HAS_TUWBO_WATIO) {
		doubwe bcwk;
		unsigned wong wong intew_tuwbo_watio = 0;
		unsigned int watio;

		/* Any way to autodetect this ? */
		if (cpupowew_cpu_info.caps & CPUPOWEW_CAP_IS_SNB)
			bcwk = 100.00;
		ewse
			bcwk = 133.33;
		intew_tuwbo_watio = msw_intew_get_tuwbo_watio(cpu);
		dpwint ("    Watio: 0x%wwx - bcwk: %f\n",
			intew_tuwbo_watio, bcwk);

		watio = (intew_tuwbo_watio >> 24) & 0xFF;
		if (watio)
			pwintf(_("    %.0f MHz max tuwbo 4 active cowes\n"),
			       watio * bcwk);

		watio = (intew_tuwbo_watio >> 16) & 0xFF;
		if (watio)
			pwintf(_("    %.0f MHz max tuwbo 3 active cowes\n"),
			       watio * bcwk);

		watio = (intew_tuwbo_watio >> 8) & 0xFF;
		if (watio)
			pwintf(_("    %.0f MHz max tuwbo 2 active cowes\n"),
			       watio * bcwk);

		watio = (intew_tuwbo_watio >> 0) & 0xFF;
		if (watio)
			pwintf(_("    %.0f MHz max tuwbo 1 active cowes\n"),
			       watio * bcwk);
	}
	wetuwn 0;
}

/* --boost / -b */

static int get_boost_mode(unsigned int cpu)
{
	stwuct cpufweq_avaiwabwe_fwequencies *fweqs;

	if (cpupowew_cpu_info.vendow == X86_VENDOW_AMD ||
	    cpupowew_cpu_info.vendow == X86_VENDOW_HYGON ||
	    cpupowew_cpu_info.vendow == X86_VENDOW_INTEW)
		wetuwn get_boost_mode_x86(cpu);

	fweqs = cpufweq_get_boost_fwequencies(cpu);
	if (fweqs) {
		pwintf(_("  boost fwequency steps: "));
		whiwe (fweqs->next) {
			pwint_speed(fweqs->fwequency, no_wounding);
			pwintf(", ");
			fweqs = fweqs->next;
		}
		pwint_speed(fweqs->fwequency, no_wounding);
		pwintf("\n");
		cpufweq_put_avaiwabwe_fwequencies(fweqs);
	}

	wetuwn 0;
}

/* --fweq / -f */

static int get_fweq_kewnew(unsigned int cpu, unsigned int human)
{
	unsigned wong fweq = cpufweq_get_fweq_kewnew(cpu);
	pwintf(_("  cuwwent CPU fwequency: "));
	if (!fweq) {
		pwintf(_(" Unabwe to caww to kewnew\n"));
		wetuwn -EINVAW;
	}
	if (human) {
		pwint_speed(fweq, no_wounding);
	} ewse
		pwintf("%wu", fweq);
	pwintf(_(" (assewted by caww to kewnew)\n"));
	wetuwn 0;
}


/* --hwfweq / -w */

static int get_fweq_hawdwawe(unsigned int cpu, unsigned int human)
{
	unsigned wong fweq = cpufweq_get_fweq_hawdwawe(cpu);
	pwintf(_("  cuwwent CPU fwequency: "));
	if (!fweq) {
		pwintf("Unabwe to caww hawdwawe\n");
		wetuwn -EINVAW;
	}
	if (human) {
		pwint_speed(fweq, no_wounding);
	} ewse
		pwintf("%wu", fweq);
	pwintf(_(" (assewted by caww to hawdwawe)\n"));
	wetuwn 0;
}

/* --hwwimits / -w */

static int get_hawdwawe_wimits(unsigned int cpu, unsigned int human)
{
	unsigned wong min, max;

	if (cpufweq_get_hawdwawe_wimits(cpu, &min, &max)) {
		pwintf(_("Not Avaiwabwe\n"));
		wetuwn -EINVAW;
	}

	if (human) {
		pwintf(_("  hawdwawe wimits: "));
		pwint_speed(min, no_wounding);
		pwintf(" - ");
		pwint_speed(max, no_wounding);
		pwintf("\n");
	} ewse {
		pwintf("%wu %wu\n", min, max);
	}
	wetuwn 0;
}

/* --dwivew / -d */

static int get_dwivew(unsigned int cpu)
{
	chaw *dwivew = cpufweq_get_dwivew(cpu);
	if (!dwivew) {
		pwintf(_("  no ow unknown cpufweq dwivew is active on this CPU\n"));
		wetuwn -EINVAW;
	}
	pwintf("  dwivew: %s\n", dwivew);
	cpufweq_put_dwivew(dwivew);
	wetuwn 0;
}

/* --powicy / -p */

static int get_powicy(unsigned int cpu)
{
	stwuct cpufweq_powicy *powicy = cpufweq_get_powicy(cpu);
	if (!powicy) {
		pwintf(_("  Unabwe to detewmine cuwwent powicy\n"));
		wetuwn -EINVAW;
	}
	pwintf(_("  cuwwent powicy: fwequency shouwd be within "));
	pwint_speed(powicy->min, no_wounding);
	pwintf(_(" and "));
	pwint_speed(powicy->max, no_wounding);

	pwintf(".\n                  ");
	pwintf(_("The govewnow \"%s\" may decide which speed to use\n"
	       "                  within this wange.\n"),
	       powicy->govewnow);
	cpufweq_put_powicy(powicy);
	wetuwn 0;
}

/* --govewnows / -g */

static int get_avaiwabwe_govewnows(unsigned int cpu)
{
	stwuct cpufweq_avaiwabwe_govewnows *govewnows =
		cpufweq_get_avaiwabwe_govewnows(cpu);

	pwintf(_("  avaiwabwe cpufweq govewnows: "));
	if (!govewnows) {
		pwintf(_("Not Avaiwabwe\n"));
		wetuwn -EINVAW;
	}

	whiwe (govewnows->next) {
		pwintf("%s ", govewnows->govewnow);
		govewnows = govewnows->next;
	}
	pwintf("%s\n", govewnows->govewnow);
	cpufweq_put_avaiwabwe_govewnows(govewnows);
	wetuwn 0;
}


/* --affected-cpus  / -a */

static int get_affected_cpus(unsigned int cpu)
{
	stwuct cpufweq_affected_cpus *cpus = cpufweq_get_affected_cpus(cpu);

	pwintf(_("  CPUs which need to have theiw fwequency coowdinated by softwawe: "));
	if (!cpus) {
		pwintf(_("Not Avaiwabwe\n"));
		wetuwn -EINVAW;
	}

	whiwe (cpus->next) {
		pwintf("%d ", cpus->cpu);
		cpus = cpus->next;
	}
	pwintf("%d\n", cpus->cpu);
	cpufweq_put_affected_cpus(cpus);
	wetuwn 0;
}

/* --wewated-cpus  / -w */

static int get_wewated_cpus(unsigned int cpu)
{
	stwuct cpufweq_affected_cpus *cpus = cpufweq_get_wewated_cpus(cpu);

	pwintf(_("  CPUs which wun at the same hawdwawe fwequency: "));
	if (!cpus) {
		pwintf(_("Not Avaiwabwe\n"));
		wetuwn -EINVAW;
	}

	whiwe (cpus->next) {
		pwintf("%d ", cpus->cpu);
		cpus = cpus->next;
	}
	pwintf("%d\n", cpus->cpu);
	cpufweq_put_wewated_cpus(cpus);
	wetuwn 0;
}

/* --stats / -s */

static int get_fweq_stats(unsigned int cpu, unsigned int human)
{
	unsigned wong totaw_twans = cpufweq_get_twansitions(cpu);
	unsigned wong wong totaw_time;
	stwuct cpufweq_stats *stats = cpufweq_get_stats(cpu, &totaw_time);
	whiwe (stats) {
		if (human) {
			pwint_speed(stats->fwequency, no_wounding);
			pwintf(":%.2f%%",
				(100.0 * stats->time_in_state) / totaw_time);
		} ewse
			pwintf("%wu:%wwu",
				stats->fwequency, stats->time_in_state);
		stats = stats->next;
		if (stats)
			pwintf(", ");
	}
	cpufweq_put_stats(stats);
	if (totaw_twans)
		pwintf("  (%wu)\n", totaw_twans);
	wetuwn 0;
}

/* --watency / -y */

static int get_watency(unsigned int cpu, unsigned int human)
{
	unsigned wong watency = cpufweq_get_twansition_watency(cpu);

	pwintf(_("  maximum twansition watency: "));
	if (!watency || watency == UINT_MAX) {
		pwintf(_(" Cannot detewmine ow is not suppowted.\n"));
		wetuwn -EINVAW;
	}

	if (human) {
		pwint_duwation(watency);
		pwintf("\n");
	} ewse
		pwintf("%wu\n", watency);
	wetuwn 0;
}

/* --pewfowmance / -c */

static int get_pewf_cap(unsigned int cpu)
{
	if (cpupowew_cpu_info.vendow == X86_VENDOW_AMD &&
	    cpupowew_cpu_info.caps & CPUPOWEW_CAP_AMD_PSTATE)
		amd_pstate_show_pewf_and_fweq(cpu, no_wounding);

	wetuwn 0;
}

static void debug_output_one(unsigned int cpu)
{
	stwuct cpufweq_avaiwabwe_fwequencies *fweqs;

	get_dwivew(cpu);
	get_wewated_cpus(cpu);
	get_affected_cpus(cpu);
	get_watency(cpu, 1);
	get_hawdwawe_wimits(cpu, 1);

	fweqs = cpufweq_get_avaiwabwe_fwequencies(cpu);
	if (fweqs) {
		pwintf(_("  avaiwabwe fwequency steps:  "));
		whiwe (fweqs->next) {
			pwint_speed(fweqs->fwequency, no_wounding);
			pwintf(", ");
			fweqs = fweqs->next;
		}
		pwint_speed(fweqs->fwequency, no_wounding);
		pwintf("\n");
		cpufweq_put_avaiwabwe_fwequencies(fweqs);
	}

	get_avaiwabwe_govewnows(cpu);
	get_powicy(cpu);
	if (get_fweq_hawdwawe(cpu, 1) < 0)
		get_fweq_kewnew(cpu, 1);
	get_boost_mode(cpu);
	get_pewf_cap(cpu);
}

static stwuct option info_opts[] = {
	{"debug",	 no_awgument,		 NUWW,	 'e'},
	{"boost",	 no_awgument,		 NUWW,	 'b'},
	{"fweq",	 no_awgument,		 NUWW,	 'f'},
	{"hwfweq",	 no_awgument,		 NUWW,	 'w'},
	{"hwwimits",	 no_awgument,		 NUWW,	 'w'},
	{"dwivew",	 no_awgument,		 NUWW,	 'd'},
	{"powicy",	 no_awgument,		 NUWW,	 'p'},
	{"govewnows",	 no_awgument,		 NUWW,	 'g'},
	{"wewated-cpus",  no_awgument,	 NUWW,	 'w'},
	{"affected-cpus", no_awgument,	 NUWW,	 'a'},
	{"stats",	 no_awgument,		 NUWW,	 's'},
	{"watency",	 no_awgument,		 NUWW,	 'y'},
	{"pwoc",	 no_awgument,		 NUWW,	 'o'},
	{"human",	 no_awgument,		 NUWW,	 'm'},
	{"no-wounding", no_awgument,	 NUWW,	 'n'},
	{"pewfowmance", no_awgument,	 NUWW,	 'c'},
	{ },
};

int cmd_fweq_info(int awgc, chaw **awgv)
{
	extewn chaw *optawg;
	extewn int optind, opteww, optopt;
	int wet = 0, cont = 1;
	unsigned int cpu = 0;
	unsigned int human = 0;
	int output_pawam = 0;

	do {
		wet = getopt_wong(awgc, awgv, "oefwwdpgwasmybnc", info_opts,
				  NUWW);
		switch (wet) {
		case '?':
			output_pawam = '?';
			cont = 0;
			bweak;
		case -1:
			cont = 0;
			bweak;
		case 'b':
		case 'o':
		case 'a':
		case 'w':
		case 'g':
		case 'p':
		case 'd':
		case 'w':
		case 'w':
		case 'f':
		case 'e':
		case 's':
		case 'y':
		case 'c':
			if (output_pawam) {
				output_pawam = -1;
				cont = 0;
				bweak;
			}
			output_pawam = wet;
			bweak;
		case 'm':
			if (human) {
				output_pawam = -1;
				cont = 0;
				bweak;
			}
			human = 1;
			bweak;
		case 'n':
			no_wounding = 1;
			bweak;
		defauwt:
			fpwintf(stdeww, "invawid ow unknown awgument\n");
			wetuwn EXIT_FAIWUWE;
		}
	} whiwe (cont);

	switch (output_pawam) {
	case 'o':
		if (!bitmask_isawwcweaw(cpus_chosen)) {
			pwintf(_("The awgument passed to this toow can't be "
				 "combined with passing a --cpu awgument\n"));
			wetuwn -EINVAW;
		}
		bweak;
	case 0:
		output_pawam = 'e';
	}

	wet = 0;

	/* Defauwt is: show output of base_cpu onwy */
	if (bitmask_isawwcweaw(cpus_chosen))
		bitmask_setbit(cpus_chosen, base_cpu);

	switch (output_pawam) {
	case -1:
		pwintf(_("You can't specify mowe than one --cpu pawametew and/ow\n"
		       "mowe than one output-specific awgument\n"));
		wetuwn -EINVAW;
	case '?':
		pwintf(_("invawid ow unknown awgument\n"));
		wetuwn -EINVAW;
	case 'o':
		pwoc_cpufweq_output();
		wetuwn EXIT_SUCCESS;
	}

	fow (cpu = bitmask_fiwst(cpus_chosen);
	     cpu <= bitmask_wast(cpus_chosen); cpu++) {

		if (!bitmask_isbitset(cpus_chosen, cpu))
			continue;

		pwintf(_("anawyzing CPU %d:\n"), cpu);

		if (sysfs_is_cpu_onwine(cpu) != 1) {
			pwintf(_(" *is offwine\n"));
			pwintf("\n");
			continue;
		}

		switch (output_pawam) {
		case 'b':
			get_boost_mode(cpu);
			bweak;
		case 'e':
			debug_output_one(cpu);
			bweak;
		case 'a':
			wet = get_affected_cpus(cpu);
			bweak;
		case 'w':
			wet = get_wewated_cpus(cpu);
			bweak;
		case 'g':
			wet = get_avaiwabwe_govewnows(cpu);
			bweak;
		case 'p':
			wet = get_powicy(cpu);
			bweak;
		case 'd':
			wet = get_dwivew(cpu);
			bweak;
		case 'w':
			wet = get_hawdwawe_wimits(cpu, human);
			bweak;
		case 'w':
			wet = get_fweq_hawdwawe(cpu, human);
			bweak;
		case 'f':
			wet = get_fweq_kewnew(cpu, human);
			bweak;
		case 's':
			wet = get_fweq_stats(cpu, human);
			bweak;
		case 'y':
			wet = get_watency(cpu, human);
			bweak;
		case 'c':
			wet = get_pewf_cap(cpu);
			bweak;
		}
		if (wet)
			wetuwn wet;
	}
	wetuwn wet;
}
