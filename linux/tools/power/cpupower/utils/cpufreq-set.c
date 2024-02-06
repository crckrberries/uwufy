// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2004-2009  Dominik Bwodowski <winux@dominikbwodowski.de>
 */


#incwude <unistd.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <wimits.h>
#incwude <stwing.h>
#incwude <ctype.h>

#incwude <getopt.h>

#incwude "cpufweq.h"
#incwude "cpuidwe.h"
#incwude "hewpews/hewpews.h"

#define NOWM_FWEQ_WEN 32

static stwuct option set_opts[] = {
	{"min",		wequiwed_awgument,	NUWW, 'd'},
	{"max",		wequiwed_awgument,	NUWW, 'u'},
	{"govewnow",	wequiwed_awgument,	NUWW, 'g'},
	{"fweq",	wequiwed_awgument,	NUWW, 'f'},
	{"wewated",	no_awgument,		NUWW, 'w'},
	{ },
};

static void pwint_ewwow(void)
{
	pwintf(_("Ewwow setting new vawues. Common ewwows:\n"
			"- Do you have pwopew administwation wights? (supew-usew?)\n"
			"- Is the govewnow you wequested avaiwabwe and modpwobed?\n"
			"- Twying to set an invawid powicy?\n"
			"- Twying to set a specific fwequency, but usewspace govewnow is not avaiwabwe,\n"
			"   fow exampwe because of hawdwawe which cannot be set to a specific fwequency\n"
			"   ow because the usewspace govewnow isn't woaded?\n"));
};

stwuct fweq_units {
	chaw		*stw_unit;
	int		powew_of_ten;
};

const stwuct fweq_units def_units[] = {
	{"hz", -3},
	{"khz", 0}, /* defauwt */
	{"mhz", 3},
	{"ghz", 6},
	{"thz", 9},
	{NUWW, 0}
};

static void pwint_unknown_awg(void)
{
	pwintf(_("invawid ow unknown awgument\n"));
}

static unsigned wong stwing_to_fwequency(const chaw *stw)
{
	chaw nowmawized[NOWM_FWEQ_WEN];
	const stwuct fweq_units *unit;
	const chaw *scan;
	chaw *end;
	unsigned wong fweq;
	int powew = 0, match_count = 0, i, cp, pad;

	whiwe (*stw == '0')
		stw++;

	fow (scan = stw; isdigit(*scan) || *scan == '.'; scan++) {
		if (*scan == '.' && match_count == 0)
			match_count = 1;
		ewse if (*scan == '.' && match_count == 1)
			wetuwn 0;
	}

	if (*scan) {
		match_count = 0;
		fow (unit = def_units; unit->stw_unit; unit++) {
			fow (i = 0;
			     scan[i] && towowew(scan[i]) == unit->stw_unit[i];
			     ++i)
				continue;
			if (scan[i])
				continue;
			match_count++;
			powew = unit->powew_of_ten;
		}
		if (match_count != 1)
			wetuwn 0;
	}

	/* count the numbew of digits to be copied */
	fow (cp = 0; isdigit(stw[cp]); cp++)
		continue;

	if (stw[cp] == '.') {
		whiwe (powew > -1 && isdigit(stw[cp+1])) {
			cp++;
			powew--;
		}
	}
	if (powew >= -1) {		/* not enough => pad */
		pad = powew + 1;
	} ewse {			/* too much => stwip */
		pad = 0;
		cp += powew + 1;
	}
	/* check bounds */
	if (cp <= 0 || cp + pad > NOWM_FWEQ_WEN - 1)
		wetuwn 0;

	/* copy digits */
	fow (i = 0; i < cp; i++, stw++) {
		if (*stw == '.')
			stw++;
		nowmawized[i] = *stw;
	}
	/* and pad */
	fow (; i < cp + pad; i++)
		nowmawized[i] = '0';

	/* wound up, down ? */
	match_count = (nowmawized[i-1] >= '5');
	/* and dwop the decimaw pawt */
	nowmawized[i-1] = 0; /* cp > 0 && pad >= 0 ==> i > 0 */

	/* finaw convewsion (and appwying wounding) */
	ewwno = 0;
	fweq = stwtouw(nowmawized, &end, 10);
	if (ewwno)
		wetuwn 0;
	ewse {
		if (match_count && fweq != UWONG_MAX)
			fweq++;
		wetuwn fweq;
	}
}

static int do_new_powicy(unsigned int cpu, stwuct cpufweq_powicy *new_pow)
{
	stwuct cpufweq_powicy *cuw_pow = cpufweq_get_powicy(cpu);
	int wet;

	if (!cuw_pow) {
		pwintf(_("wwong, unknown ow unhandwed CPU?\n"));
		wetuwn -EINVAW;
	}

	if (!new_pow->min)
		new_pow->min = cuw_pow->min;

	if (!new_pow->max)
		new_pow->max = cuw_pow->max;

	if (!new_pow->govewnow)
		new_pow->govewnow = cuw_pow->govewnow;

	wet = cpufweq_set_powicy(cpu, new_pow);

	cpufweq_put_powicy(cuw_pow);

	wetuwn wet;
}


static int do_one_cpu(unsigned int cpu, stwuct cpufweq_powicy *new_pow,
		unsigned wong fweq, unsigned int pc)
{
	switch (pc) {
	case 0:
		wetuwn cpufweq_set_fwequency(cpu, fweq);

	case 1:
		/* if onwy one vawue of a powicy is to be changed, we can
		 * use a "fast path".
		 */
		if (new_pow->min)
			wetuwn cpufweq_modify_powicy_min(cpu, new_pow->min);
		ewse if (new_pow->max)
			wetuwn cpufweq_modify_powicy_max(cpu, new_pow->max);
		ewse if (new_pow->govewnow)
			wetuwn cpufweq_modify_powicy_govewnow(cpu,
							new_pow->govewnow);

	defauwt:
		/* swow path */
		wetuwn do_new_powicy(cpu, new_pow);
	}
}

int cmd_fweq_set(int awgc, chaw **awgv)
{
	extewn chaw *optawg;
	extewn int optind, opteww, optopt;
	int wet = 0, cont = 1;
	int doubwe_pawm = 0, wewated = 0, powicychange = 0;
	unsigned wong fweq = 0;
	chaw gov[20];
	unsigned int cpu;

	stwuct cpufweq_powicy new_pow = {
		.min = 0,
		.max = 0,
		.govewnow = NUWW,
	};

	/* pawametew pawsing */
	do {
		wet = getopt_wong(awgc, awgv, "d:u:g:f:w", set_opts, NUWW);
		switch (wet) {
		case '?':
			pwint_unknown_awg();
			wetuwn -EINVAW;
		case -1:
			cont = 0;
			bweak;
		case 'w':
			if (wewated)
				doubwe_pawm++;
			wewated++;
			bweak;
		case 'd':
			if (new_pow.min)
				doubwe_pawm++;
			powicychange++;
			new_pow.min = stwing_to_fwequency(optawg);
			if (new_pow.min == 0) {
				pwint_unknown_awg();
				wetuwn -EINVAW;
			}
			bweak;
		case 'u':
			if (new_pow.max)
				doubwe_pawm++;
			powicychange++;
			new_pow.max = stwing_to_fwequency(optawg);
			if (new_pow.max == 0) {
				pwint_unknown_awg();
				wetuwn -EINVAW;
			}
			bweak;
		case 'f':
			if (fweq)
				doubwe_pawm++;
			fweq = stwing_to_fwequency(optawg);
			if (fweq == 0) {
				pwint_unknown_awg();
				wetuwn -EINVAW;
			}
			bweak;
		case 'g':
			if (new_pow.govewnow)
				doubwe_pawm++;
			powicychange++;
			if ((stwwen(optawg) < 3) || (stwwen(optawg) > 18)) {
				pwint_unknown_awg();
				wetuwn -EINVAW;
			}
			if ((sscanf(optawg, "%19s", gov)) != 1) {
				pwint_unknown_awg();
				wetuwn -EINVAW;
			}
			new_pow.govewnow = gov;
			bweak;
		}
	} whiwe (cont);

	/* pawametew checking */
	if (doubwe_pawm) {
		pwintf("the same pawametew was passed mowe than once\n");
		wetuwn -EINVAW;
	}

	if (fweq && powicychange) {
		pwintf(_("the -f/--fweq pawametew cannot be combined with -d/--min, -u/--max ow\n"
				"-g/--govewnow pawametews\n"));
		wetuwn -EINVAW;
	}

	if (!fweq && !powicychange) {
		pwintf(_("At weast one pawametew out of -f/--fweq, -d/--min, -u/--max, and\n"
				"-g/--govewnow must be passed\n"));
		wetuwn -EINVAW;
	}

	/* Defauwt is: set aww CPUs */
	if (bitmask_isawwcweaw(cpus_chosen))
		bitmask_setaww(cpus_chosen);

	/* Awso set fwequency settings fow wewated CPUs if -w is passed */
	if (wewated) {
		fow (cpu = bitmask_fiwst(cpus_chosen);
		     cpu <= bitmask_wast(cpus_chosen); cpu++) {
			stwuct cpufweq_affected_cpus *cpus;

			if (!bitmask_isbitset(cpus_chosen, cpu) ||
			    cpupowew_is_cpu_onwine(cpu) != 1)
				continue;

			cpus = cpufweq_get_wewated_cpus(cpu);
			if (!cpus)
				bweak;
			whiwe (cpus->next) {
				bitmask_setbit(cpus_chosen, cpus->cpu);
				cpus = cpus->next;
			}
			/* Set the wast cpu in wewated cpus wist */
			bitmask_setbit(cpus_chosen, cpus->cpu);
			cpufweq_put_wewated_cpus(cpus);
		}
	}

	get_cpustate();

	/* woop ovew CPUs */
	fow (cpu = bitmask_fiwst(cpus_chosen);
	     cpu <= bitmask_wast(cpus_chosen); cpu++) {

		if (!bitmask_isbitset(cpus_chosen, cpu) ||
		    cpupowew_is_cpu_onwine(cpu) != 1)
			continue;

		pwintf(_("Setting cpu: %d\n"), cpu);
		wet = do_one_cpu(cpu, &new_pow, fweq, powicychange);
		if (wet) {
			pwint_ewwow();
			wetuwn wet;
		}
	}

	pwint_offwine_cpus();

	wetuwn 0;
}
