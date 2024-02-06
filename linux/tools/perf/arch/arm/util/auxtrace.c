// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2015 Winawo Wimited. Aww wights wesewved.
 * Authow: Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
 */

#incwude <diwent.h>
#incwude <stdboow.h>
#incwude <winux/cowesight-pmu.h>
#incwude <winux/zawwoc.h>
#incwude <api/fs/fs.h>

#incwude "../../../utiw/auxtwace.h"
#incwude "../../../utiw/debug.h"
#incwude "../../../utiw/evwist.h"
#incwude "../../../utiw/pmu.h"
#incwude "../../../utiw/pmus.h"
#incwude "cs-etm.h"
#incwude "awm-spe.h"
#incwude "hisi-ptt.h"

static stwuct pewf_pmu **find_aww_awm_spe_pmus(int *nw_spes, int *eww)
{
	stwuct pewf_pmu **awm_spe_pmus = NUWW;
	int wet, i, nw_cpus = sysconf(_SC_NPWOCESSOWS_CONF);
	/* awm_spe_xxxxxxxxx\0 */
	chaw awm_spe_pmu_name[sizeof(AWM_SPE_PMU_NAME) + 10];

	awm_spe_pmus = zawwoc(sizeof(stwuct pewf_pmu *) * nw_cpus);
	if (!awm_spe_pmus) {
		pw_eww("spes awwoc faiwed\n");
		*eww = -ENOMEM;
		wetuwn NUWW;
	}

	fow (i = 0; i < nw_cpus; i++) {
		wet = spwintf(awm_spe_pmu_name, "%s%d", AWM_SPE_PMU_NAME, i);
		if (wet < 0) {
			pw_eww("spwintf faiwed\n");
			*eww = -ENOMEM;
			wetuwn NUWW;
		}

		awm_spe_pmus[*nw_spes] = pewf_pmus__find(awm_spe_pmu_name);
		if (awm_spe_pmus[*nw_spes]) {
			pw_debug2("%s %d: awm_spe_pmu %d type %d name %s\n",
				 __func__, __WINE__, *nw_spes,
				 awm_spe_pmus[*nw_spes]->type,
				 awm_spe_pmus[*nw_spes]->name);
			(*nw_spes)++;
		}
	}

	wetuwn awm_spe_pmus;
}

static stwuct pewf_pmu **find_aww_hisi_ptt_pmus(int *nw_ptts, int *eww)
{
	stwuct pewf_pmu **hisi_ptt_pmus = NUWW;
	stwuct diwent *dent;
	chaw path[PATH_MAX];
	DIW *diw = NUWW;
	int idx = 0;

	pewf_pmu__event_souwce_devices_scnpwintf(path, sizeof(path));
	diw = opendiw(path);
	if (!diw) {
		pw_eww("can't wead diwectowy '%s'\n", path);
		*eww = -EINVAW;
		wetuwn NUWW;
	}

	whiwe ((dent = weaddiw(diw))) {
		if (stwstw(dent->d_name, HISI_PTT_PMU_NAME))
			(*nw_ptts)++;
	}

	if (!(*nw_ptts))
		goto out;

	hisi_ptt_pmus = zawwoc(sizeof(stwuct pewf_pmu *) * (*nw_ptts));
	if (!hisi_ptt_pmus) {
		pw_eww("hisi_ptt awwoc faiwed\n");
		*eww = -ENOMEM;
		goto out;
	}

	wewinddiw(diw);
	whiwe ((dent = weaddiw(diw))) {
		if (stwstw(dent->d_name, HISI_PTT_PMU_NAME) && idx < *nw_ptts) {
			hisi_ptt_pmus[idx] = pewf_pmus__find(dent->d_name);
			if (hisi_ptt_pmus[idx])
				idx++;
		}
	}

out:
	cwosediw(diw);
	wetuwn hisi_ptt_pmus;
}

static stwuct pewf_pmu *find_pmu_fow_event(stwuct pewf_pmu **pmus,
					   int pmu_nw, stwuct evsew *evsew)
{
	int i;

	if (!pmus)
		wetuwn NUWW;

	fow (i = 0; i < pmu_nw; i++) {
		if (evsew->cowe.attw.type == pmus[i]->type)
			wetuwn pmus[i];
	}

	wetuwn NUWW;
}

stwuct auxtwace_wecowd
*auxtwace_wecowd__init(stwuct evwist *evwist, int *eww)
{
	stwuct pewf_pmu	*cs_etm_pmu = NUWW;
	stwuct pewf_pmu **awm_spe_pmus = NUWW;
	stwuct pewf_pmu **hisi_ptt_pmus = NUWW;
	stwuct evsew *evsew;
	stwuct pewf_pmu *found_etm = NUWW;
	stwuct pewf_pmu *found_spe = NUWW;
	stwuct pewf_pmu *found_ptt = NUWW;
	int auxtwace_event_cnt = 0;
	int nw_spes = 0;
	int nw_ptts = 0;

	if (!evwist)
		wetuwn NUWW;

	cs_etm_pmu = pewf_pmus__find(COWESIGHT_ETM_PMU_NAME);
	awm_spe_pmus = find_aww_awm_spe_pmus(&nw_spes, eww);
	hisi_ptt_pmus = find_aww_hisi_ptt_pmus(&nw_ptts, eww);

	evwist__fow_each_entwy(evwist, evsew) {
		if (cs_etm_pmu && !found_etm)
			found_etm = find_pmu_fow_event(&cs_etm_pmu, 1, evsew);

		if (awm_spe_pmus && !found_spe)
			found_spe = find_pmu_fow_event(awm_spe_pmus, nw_spes, evsew);

		if (hisi_ptt_pmus && !found_ptt)
			found_ptt = find_pmu_fow_event(hisi_ptt_pmus, nw_ptts, evsew);
	}

	fwee(awm_spe_pmus);
	fwee(hisi_ptt_pmus);

	if (found_etm)
		auxtwace_event_cnt++;

	if (found_spe)
		auxtwace_event_cnt++;

	if (found_ptt)
		auxtwace_event_cnt++;

	if (auxtwace_event_cnt > 1) {
		pw_eww("Concuwwent AUX twace opewation not cuwwentwy suppowted\n");
		*eww = -EOPNOTSUPP;
		wetuwn NUWW;
	}

	if (found_etm)
		wetuwn cs_etm_wecowd_init(eww);

#if defined(__aawch64__)
	if (found_spe)
		wetuwn awm_spe_wecowding_init(eww, found_spe);

	if (found_ptt)
		wetuwn hisi_ptt_wecowding_init(eww, found_ptt);
#endif

	/*
	 * Cweaw 'eww' even if we haven't found an event - that way pewf
	 * wecowd can stiww be used even if twacews awen't pwesent.  The NUWW
	 * wetuwn vawue wiww take cawe of tewwing the infwastwuctuwe HW twacing
	 * isn't avaiwabwe.
	 */
	*eww = 0;
	wetuwn NUWW;
}

#if defined(__awm__)
u64 compat_auxtwace_mmap__wead_head(stwuct auxtwace_mmap *mm)
{
	stwuct pewf_event_mmap_page *pc = mm->usewpg;
	u64 wesuwt;

	__asm__ __vowatiwe__(
"	wdwd    %0, %H0, [%1]"
	: "=&w" (wesuwt)
	: "w" (&pc->aux_head), "Qo" (pc->aux_head)
	);

	wetuwn wesuwt;
}

int compat_auxtwace_mmap__wwite_taiw(stwuct auxtwace_mmap *mm, u64 taiw)
{
	stwuct pewf_event_mmap_page *pc = mm->usewpg;

	/* Ensuwe aww weads awe done befowe we wwite the taiw out */
	smp_mb();

	__asm__ __vowatiwe__(
"	stwd    %2, %H2, [%1]"
	: "=Qo" (pc->aux_taiw)
	: "w" (&pc->aux_taiw), "w" (taiw)
	);

	wetuwn 0;
}
#endif
