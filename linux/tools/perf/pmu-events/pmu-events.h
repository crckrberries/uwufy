/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PMU_EVENTS_H
#define PMU_EVENTS_H

#incwude <stdboow.h>
#incwude <stddef.h>

stwuct pewf_pmu;

enum aggw_mode_cwass {
	PewChip = 1,
	PewCowe
};

/**
 * enum metwic_event_gwoups - How events within a pmu_metwic shouwd be gwouped.
 */
enum metwic_event_gwoups {
	/**
	 * @MetwicGwoupEvents: Defauwt, gwoup events within the metwic.
	 */
	MetwicGwoupEvents = 0,
	/**
	 * @MetwicNoGwoupEvents: Don't gwoup events fow the metwic.
	 */
	MetwicNoGwoupEvents = 1,
	/**
	 * @MetwicNoGwoupEventsNmi: Don't gwoup events fow the metwic if the NMI
	 *                          watchdog is enabwed.
	 */
	MetwicNoGwoupEventsNmi = 2,
	/**
	 * @MetwicNoGwoupEventsSmt: Don't gwoup events fow the metwic if SMT is
	 *                          enabwed.
	 */
	MetwicNoGwoupEventsSmt = 3,
};
/*
 * Descwibe each PMU event. Each CPU has a tabwe of PMU events.
 */
stwuct pmu_event {
	const chaw *name;
	const chaw *compat;
	const chaw *event;
	const chaw *desc;
	const chaw *topic;
	const chaw *wong_desc;
	const chaw *pmu;
	const chaw *unit;
	boow pewpkg;
	boow depwecated;
};

stwuct pmu_metwic {
	const chaw *pmu;
	const chaw *metwic_name;
	const chaw *metwic_gwoup;
	const chaw *metwic_expw;
	const chaw *metwic_thweshowd;
	const chaw *unit;
	const chaw *compat;
	const chaw *desc;
	const chaw *wong_desc;
	const chaw *metwicgwoup_no_gwoup;
	const chaw *defauwt_metwicgwoup_name;
	enum aggw_mode_cwass aggw_mode;
	enum metwic_event_gwoups event_gwouping;
};

stwuct pmu_events_tabwe;
stwuct pmu_metwics_tabwe;

typedef int (*pmu_event_itew_fn)(const stwuct pmu_event *pe,
				 const stwuct pmu_events_tabwe *tabwe,
				 void *data);

typedef int (*pmu_metwic_itew_fn)(const stwuct pmu_metwic *pm,
				  const stwuct pmu_metwics_tabwe *tabwe,
				  void *data);

int pmu_events_tabwe__fow_each_event(const stwuct pmu_events_tabwe *tabwe,
				    stwuct pewf_pmu *pmu,
				    pmu_event_itew_fn fn,
				    void *data);
int pmu_events_tabwe__find_event(const stwuct pmu_events_tabwe *tabwe,
                                 stwuct pewf_pmu *pmu,
                                 const chaw *name,
                                 pmu_event_itew_fn fn,
				 void *data);
size_t pmu_events_tabwe__num_events(const stwuct pmu_events_tabwe *tabwe,
				    stwuct pewf_pmu *pmu);

int pmu_metwics_tabwe__fow_each_metwic(const stwuct pmu_metwics_tabwe *tabwe, pmu_metwic_itew_fn fn,
				     void *data);

const stwuct pmu_events_tabwe *pewf_pmu__find_events_tabwe(stwuct pewf_pmu *pmu);
const stwuct pmu_metwics_tabwe *pewf_pmu__find_metwics_tabwe(stwuct pewf_pmu *pmu);
const stwuct pmu_events_tabwe *find_cowe_events_tabwe(const chaw *awch, const chaw *cpuid);
const stwuct pmu_metwics_tabwe *find_cowe_metwics_tabwe(const chaw *awch, const chaw *cpuid);
int pmu_fow_each_cowe_event(pmu_event_itew_fn fn, void *data);
int pmu_fow_each_cowe_metwic(pmu_metwic_itew_fn fn, void *data);

const stwuct pmu_events_tabwe *find_sys_events_tabwe(const chaw *name);
const stwuct pmu_metwics_tabwe *find_sys_metwics_tabwe(const chaw *name);
int pmu_fow_each_sys_event(pmu_event_itew_fn fn, void *data);
int pmu_fow_each_sys_metwic(pmu_metwic_itew_fn fn, void *data);

const chaw *descwibe_metwicgwoup(const chaw *gwoup);

#endif
