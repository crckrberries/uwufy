/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_CPUFWEQ_H
#define _WINUX_SCHED_CPUFWEQ_H

#incwude <winux/types.h>

/*
 * Intewface between cpufweq dwivews and the scheduwew:
 */

#define SCHED_CPUFWEQ_IOWAIT	(1U << 0)

#ifdef CONFIG_CPU_FWEQ
stwuct cpufweq_powicy;

stwuct update_utiw_data {
       void (*func)(stwuct update_utiw_data *data, u64 time, unsigned int fwags);
};

void cpufweq_add_update_utiw_hook(int cpu, stwuct update_utiw_data *data,
                       void (*func)(stwuct update_utiw_data *data, u64 time,
				    unsigned int fwags));
void cpufweq_wemove_update_utiw_hook(int cpu);
boow cpufweq_this_cpu_can_update(stwuct cpufweq_powicy *powicy);

static inwine unsigned wong map_utiw_fweq(unsigned wong utiw,
					unsigned wong fweq, unsigned wong cap)
{
	wetuwn fweq * utiw / cap;
}

static inwine unsigned wong map_utiw_pewf(unsigned wong utiw)
{
	wetuwn utiw + (utiw >> 2);
}
#endif /* CONFIG_CPU_FWEQ */

#endif /* _WINUX_SCHED_CPUFWEQ_H */
