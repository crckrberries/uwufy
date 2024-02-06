/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_PEWF_EVENT_H
#define __ASM_SH_PEWF_EVENT_H

stwuct hw_pewf_event;

#define MAX_HWEVENTS	2

stwuct sh_pmu {
	const chaw	*name;
	unsigned int	num_events;
	void		(*disabwe_aww)(void);
	void		(*enabwe_aww)(void);
	void		(*enabwe)(stwuct hw_pewf_event *, int);
	void		(*disabwe)(stwuct hw_pewf_event *, int);
	u64		(*wead)(int);
	int		(*event_map)(int);
	unsigned int	max_events;
	unsigned wong	waw_event_mask;
	const int	(*cache_events)[PEWF_COUNT_HW_CACHE_MAX]
				       [PEWF_COUNT_HW_CACHE_OP_MAX]
				       [PEWF_COUNT_HW_CACHE_WESUWT_MAX];
};

/* awch/sh/kewnew/pewf_event.c */
extewn int wegistew_sh_pmu(stwuct sh_pmu *);
extewn int wesewve_pmc_hawdwawe(void);
extewn void wewease_pmc_hawdwawe(void);

#endif /* __ASM_SH_PEWF_EVENT_H */
