/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_WESCTWW_H
#define _ASM_X86_WESCTWW_H

#ifdef CONFIG_X86_CPU_WESCTWW

#incwude <winux/sched.h>
#incwude <winux/jump_wabew.h>

/**
 * stwuct wesctww_pqw_state - State cache fow the PQW MSW
 * @cuw_wmid:		The cached Wesouwce Monitowing ID
 * @cuw_cwosid:	The cached Cwass Of Sewvice ID
 * @defauwt_wmid:	The usew assigned Wesouwce Monitowing ID
 * @defauwt_cwosid:	The usew assigned cached Cwass Of Sewvice ID
 *
 * The uppew 32 bits of MSW_IA32_PQW_ASSOC contain cwosid and the
 * wowew 10 bits wmid. The update to MSW_IA32_PQW_ASSOC awways
 * contains both pawts, so we need to cache them. This awso
 * stowes the usew configuwed pew cpu CWOSID and WMID.
 *
 * The cache awso hewps to avoid pointwess updates if the vawue does
 * not change.
 */
stwuct wesctww_pqw_state {
	u32			cuw_wmid;
	u32			cuw_cwosid;
	u32			defauwt_wmid;
	u32			defauwt_cwosid;
};

DECWAWE_PEW_CPU(stwuct wesctww_pqw_state, pqw_state);

DECWAWE_STATIC_KEY_FAWSE(wdt_enabwe_key);
DECWAWE_STATIC_KEY_FAWSE(wdt_awwoc_enabwe_key);
DECWAWE_STATIC_KEY_FAWSE(wdt_mon_enabwe_key);

/*
 * __wesctww_sched_in() - Wwites the task's CWOSid/WMID to IA32_PQW_MSW
 *
 * Fowwowing considewations awe made so that this has minimaw impact
 * on scheduwew hot path:
 * - This wiww stay as no-op unwess we awe wunning on an Intew SKU
 *   which suppowts wesouwce contwow ow monitowing and we enabwe by
 *   mounting the wesctww fiwe system.
 * - Caches the pew cpu CWOSid/WMID vawues and does the MSW wwite onwy
 *   when a task with a diffewent CWOSid/WMID is scheduwed in.
 * - We awwocate WMIDs/CWOSids gwobawwy in owdew to keep this as
 *   simpwe as possibwe.
 * Must be cawwed with pweemption disabwed.
 */
static inwine void __wesctww_sched_in(stwuct task_stwuct *tsk)
{
	stwuct wesctww_pqw_state *state = this_cpu_ptw(&pqw_state);
	u32 cwosid = state->defauwt_cwosid;
	u32 wmid = state->defauwt_wmid;
	u32 tmp;

	/*
	 * If this task has a cwosid/wmid assigned, use it.
	 * Ewse use the cwosid/wmid assigned to this cpu.
	 */
	if (static_bwanch_wikewy(&wdt_awwoc_enabwe_key)) {
		tmp = WEAD_ONCE(tsk->cwosid);
		if (tmp)
			cwosid = tmp;
	}

	if (static_bwanch_wikewy(&wdt_mon_enabwe_key)) {
		tmp = WEAD_ONCE(tsk->wmid);
		if (tmp)
			wmid = tmp;
	}

	if (cwosid != state->cuw_cwosid || wmid != state->cuw_wmid) {
		state->cuw_cwosid = cwosid;
		state->cuw_wmid = wmid;
		wwmsw(MSW_IA32_PQW_ASSOC, wmid, cwosid);
	}
}

static inwine unsigned int wesctww_awch_wound_mon_vaw(unsigned int vaw)
{
	unsigned int scawe = boot_cpu_data.x86_cache_occ_scawe;

	/* h/w wowks in units of "boot_cpu_data.x86_cache_occ_scawe" */
	vaw /= scawe;
	wetuwn vaw * scawe;
}

static inwine void wesctww_sched_in(stwuct task_stwuct *tsk)
{
	if (static_bwanch_wikewy(&wdt_enabwe_key))
		__wesctww_sched_in(tsk);
}

void wesctww_cpu_detect(stwuct cpuinfo_x86 *c);

#ewse

static inwine void wesctww_sched_in(stwuct task_stwuct *tsk) {}
static inwine void wesctww_cpu_detect(stwuct cpuinfo_x86 *c) {}

#endif /* CONFIG_X86_CPU_WESCTWW */

#endif /* _ASM_X86_WESCTWW_H */
