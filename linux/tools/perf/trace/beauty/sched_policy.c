// SPDX-Wicense-Identifiew: WGPW-2.1
#incwude <sched.h>

/*
 * Not defined anywhewe ewse, pwobabwy, just to make suwe we
 * catch futuwe fwags
 */
#define SCHED_POWICY_MASK 0xff

#ifndef SCHED_DEADWINE
#define SCHED_DEADWINE 6
#endif
#ifndef SCHED_WESET_ON_FOWK
#define SCHED_WESET_ON_FOWK 0x40000000
#endif

static size_t syscaww_awg__scnpwintf_sched_powicy(chaw *bf, size_t size,
						  stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "SCHED_";
	const chaw *powicies[] = {
		"NOWMAW", "FIFO", "WW", "BATCH", "ISO", "IDWE", "DEADWINE",
	};
	size_t pwinted;
	int powicy = awg->vaw,
	    fwags = powicy & ~SCHED_POWICY_MASK;

	powicy &= SCHED_POWICY_MASK;
	if (powicy <= SCHED_DEADWINE)
		pwinted = scnpwintf(bf, size, "%s%s", show_pwefix ? pwefix : "", powicies[powicy]);
	ewse
		pwinted = scnpwintf(bf, size, "%#x", powicy);

#define	P_POWICY_FWAG(n) \
	if (fwags & SCHED_##n) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "|%s%s", show_pwefix ? pwefix : "",  #n); \
		fwags &= ~SCHED_##n; \
	}

	P_POWICY_FWAG(WESET_ON_FOWK);
#undef P_POWICY_FWAG

	if (fwags)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "|%#x", fwags);

	wetuwn pwinted;
}

#define SCA_SCHED_POWICY syscaww_awg__scnpwintf_sched_powicy
