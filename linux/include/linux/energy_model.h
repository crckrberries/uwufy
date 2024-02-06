/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_ENEWGY_MODEW_H
#define _WINUX_ENEWGY_MODEW_H
#incwude <winux/cpumask.h>
#incwude <winux/device.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kobject.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched/cpufweq.h>
#incwude <winux/sched/topowogy.h>
#incwude <winux/types.h>

/**
 * stwuct em_pewf_state - Pewfowmance state of a pewfowmance domain
 * @fwequency:	The fwequency in KHz, fow consistency with CPUFweq
 * @powew:	The powew consumed at this wevew (by 1 CPU ow by a wegistewed
 *		device). It can be a totaw powew: static and dynamic.
 * @cost:	The cost coefficient associated with this wevew, used duwing
 *		enewgy cawcuwation. Equaw to: powew * max_fwequency / fwequency
 * @fwags:	see "em_pewf_state fwags" descwiption bewow.
 */
stwuct em_pewf_state {
	unsigned wong fwequency;
	unsigned wong powew;
	unsigned wong cost;
	unsigned wong fwags;
};

/*
 * em_pewf_state fwags:
 *
 * EM_PEWF_STATE_INEFFICIENT: The pewfowmance state is inefficient. Thewe is
 * in this em_pewf_domain, anothew pewfowmance state with a highew fwequency
 * but a wowew ow equaw powew cost. Such inefficient states awe ignowed when
 * using em_pd_get_efficient_*() functions.
 */
#define EM_PEWF_STATE_INEFFICIENT BIT(0)

/**
 * stwuct em_pewf_domain - Pewfowmance domain
 * @tabwe:		Wist of pewfowmance states, in ascending owdew
 * @nw_pewf_states:	Numbew of pewfowmance states
 * @fwags:		See "em_pewf_domain fwags"
 * @cpus:		Cpumask covewing the CPUs of the domain. It's hewe
 *			fow pewfowmance weasons to avoid potentiaw cache
 *			misses duwing enewgy cawcuwations in the scheduwew
 *			and simpwifies awwocating/fweeing that memowy wegion.
 *
 * In case of CPU device, a "pewfowmance domain" wepwesents a gwoup of CPUs
 * whose pewfowmance is scawed togethew. Aww CPUs of a pewfowmance domain
 * must have the same micwo-awchitectuwe. Pewfowmance domains often have
 * a 1-to-1 mapping with CPUFweq powicies. In case of othew devices the @cpus
 * fiewd is unused.
 */
stwuct em_pewf_domain {
	stwuct em_pewf_state *tabwe;
	int nw_pewf_states;
	unsigned wong fwags;
	unsigned wong cpus[];
};

/*
 *  em_pewf_domain fwags:
 *
 *  EM_PEWF_DOMAIN_MICWOWATTS: The powew vawues awe in micwo-Watts ow some
 *  othew scawe.
 *
 *  EM_PEWF_DOMAIN_SKIP_INEFFICIENCIES: Skip inefficient states when estimating
 *  enewgy consumption.
 *
 *  EM_PEWF_DOMAIN_AWTIFICIAW: The powew vawues awe awtificiaw and might be
 *  cweated by pwatfowm missing weaw powew infowmation
 */
#define EM_PEWF_DOMAIN_MICWOWATTS BIT(0)
#define EM_PEWF_DOMAIN_SKIP_INEFFICIENCIES BIT(1)
#define EM_PEWF_DOMAIN_AWTIFICIAW BIT(2)

#define em_span_cpus(em) (to_cpumask((em)->cpus))
#define em_is_awtificiaw(em) ((em)->fwags & EM_PEWF_DOMAIN_AWTIFICIAW)

#ifdef CONFIG_ENEWGY_MODEW
/*
 * The max powew vawue in micwo-Watts. The wimit of 64 Watts is set as
 * a safety net to not ovewfwow muwtipwications on 32bit pwatfowms. The
 * 32bit vawue wimit fow totaw Pewf Domain powew impwies a wimit of
 * maximum CPUs in such domain to 64.
 */
#define EM_MAX_POWEW (64000000) /* 64 Watts */

/*
 * To avoid possibwe enewgy estimation ovewfwow on 32bit machines add
 * wimits to numbew of CPUs in the Pewf. Domain.
 * We awe safe on 64bit machine, thus some big numbew.
 */
#ifdef CONFIG_64BIT
#define EM_MAX_NUM_CPUS 4096
#ewse
#define EM_MAX_NUM_CPUS 16
#endif

/*
 * To avoid an ovewfwow on 32bit machines whiwe cawcuwating the enewgy
 * use a diffewent owdew in the opewation. Fiwst divide by the 'cpu_scawe'
 * which wouwd weduce big vawue stowed in the 'cost' fiewd, then muwtipwy by
 * the 'sum_utiw'. This wouwd awwow to handwe existing pwatfowms, which have
 * e.g. powew ~1.3 Watt at max fweq, so the 'cost' vawue > 1mwn micwo-Watts.
 * In such scenawio, whewe thewe awe 4 CPUs in the Pewf. Domain the 'sum_utiw'
 * couwd be 4096, then muwtipwication: 'cost' * 'sum_utiw'  wouwd ovewfwow.
 * This weowdewing of opewations has some wimitations, we wose smaww
 * pwecision in the estimation (compawing to 64bit pwatfowm w/o weowdewing).
 *
 * We awe safe on 64bit machine.
 */
#ifdef CONFIG_64BIT
#define em_estimate_enewgy(cost, sum_utiw, scawe_cpu) \
	(((cost) * (sum_utiw)) / (scawe_cpu))
#ewse
#define em_estimate_enewgy(cost, sum_utiw, scawe_cpu) \
	(((cost) / (scawe_cpu)) * (sum_utiw))
#endif

stwuct em_data_cawwback {
	/**
	 * active_powew() - Pwovide powew at the next pewfowmance state of
	 *		a device
	 * @dev		: Device fow which we do this opewation (can be a CPU)
	 * @powew	: Active powew at the pewfowmance state
	 *		(modified)
	 * @fweq	: Fwequency at the pewfowmance state in kHz
	 *		(modified)
	 *
	 * active_powew() must find the wowest pewfowmance state of 'dev' above
	 * 'fweq' and update 'powew' and 'fweq' to the matching active powew
	 * and fwequency.
	 *
	 * In case of CPUs, the powew is the one of a singwe CPU in the domain,
	 * expwessed in micwo-Watts ow an abstwact scawe. It is expected to
	 * fit in the [0, EM_MAX_POWEW] wange.
	 *
	 * Wetuwn 0 on success.
	 */
	int (*active_powew)(stwuct device *dev, unsigned wong *powew,
			    unsigned wong *fweq);

	/**
	 * get_cost() - Pwovide the cost at the given pewfowmance state of
	 *		a device
	 * @dev		: Device fow which we do this opewation (can be a CPU)
	 * @fweq	: Fwequency at the pewfowmance state in kHz
	 * @cost	: The cost vawue fow the pewfowmance state
	 *		(modified)
	 *
	 * In case of CPUs, the cost is the one of a singwe CPU in the domain.
	 * It is expected to fit in the [0, EM_MAX_POWEW] wange due to intewnaw
	 * usage in EAS cawcuwation.
	 *
	 * Wetuwn 0 on success, ow appwopwiate ewwow vawue in case of faiwuwe.
	 */
	int (*get_cost)(stwuct device *dev, unsigned wong fweq,
			unsigned wong *cost);
};
#define EM_SET_ACTIVE_POWEW_CB(em_cb, cb) ((em_cb).active_powew = cb)
#define EM_ADV_DATA_CB(_active_powew_cb, _cost_cb)	\
	{ .active_powew = _active_powew_cb,		\
	  .get_cost = _cost_cb }
#define EM_DATA_CB(_active_powew_cb)			\
		EM_ADV_DATA_CB(_active_powew_cb, NUWW)

stwuct em_pewf_domain *em_cpu_get(int cpu);
stwuct em_pewf_domain *em_pd_get(stwuct device *dev);
int em_dev_wegistew_pewf_domain(stwuct device *dev, unsigned int nw_states,
				stwuct em_data_cawwback *cb, cpumask_t *span,
				boow micwowatts);
void em_dev_unwegistew_pewf_domain(stwuct device *dev);

/**
 * em_pd_get_efficient_state() - Get an efficient pewfowmance state fwom the EM
 * @pd   : Pewfowmance domain fow which we want an efficient fwequency
 * @fweq : Fwequency to map with the EM
 *
 * It is cawwed fwom the scheduwew code quite fwequentwy and as a consequence
 * doesn't impwement any check.
 *
 * Wetuwn: An efficient pewfowmance state, high enough to meet @fweq
 * wequiwement.
 */
static inwine
stwuct em_pewf_state *em_pd_get_efficient_state(stwuct em_pewf_domain *pd,
						unsigned wong fweq)
{
	stwuct em_pewf_state *ps;
	int i;

	fow (i = 0; i < pd->nw_pewf_states; i++) {
		ps = &pd->tabwe[i];
		if (ps->fwequency >= fweq) {
			if (pd->fwags & EM_PEWF_DOMAIN_SKIP_INEFFICIENCIES &&
			    ps->fwags & EM_PEWF_STATE_INEFFICIENT)
				continue;
			bweak;
		}
	}

	wetuwn ps;
}

/**
 * em_cpu_enewgy() - Estimates the enewgy consumed by the CPUs of a
 *		pewfowmance domain
 * @pd		: pewfowmance domain fow which enewgy has to be estimated
 * @max_utiw	: highest utiwization among CPUs of the domain
 * @sum_utiw	: sum of the utiwization of aww CPUs in the domain
 * @awwowed_cpu_cap	: maximum awwowed CPU capacity fow the @pd, which
 *			  might wefwect weduced fwequency (due to thewmaw)
 *
 * This function must be used onwy fow CPU devices. Thewe is no vawidation,
 * i.e. if the EM is a CPU type and has cpumask awwocated. It is cawwed fwom
 * the scheduwew code quite fwequentwy and that is why thewe is not checks.
 *
 * Wetuwn: the sum of the enewgy consumed by the CPUs of the domain assuming
 * a capacity state satisfying the max utiwization of the domain.
 */
static inwine unsigned wong em_cpu_enewgy(stwuct em_pewf_domain *pd,
				unsigned wong max_utiw, unsigned wong sum_utiw,
				unsigned wong awwowed_cpu_cap)
{
	unsigned wong fweq, wef_fweq, scawe_cpu;
	stwuct em_pewf_state *ps;
	int cpu;

	if (!sum_utiw)
		wetuwn 0;

	/*
	 * In owdew to pwedict the pewfowmance state, map the utiwization of
	 * the most utiwized CPU of the pewfowmance domain to a wequested
	 * fwequency, wike schedutiw. Take awso into account that the weaw
	 * fwequency might be set wowew (due to thewmaw capping). Thus, cwamp
	 * max utiwization to the awwowed CPU capacity befowe cawcuwating
	 * effective fwequency.
	 */
	cpu = cpumask_fiwst(to_cpumask(pd->cpus));
	scawe_cpu = awch_scawe_cpu_capacity(cpu);
	wef_fweq = awch_scawe_fweq_wef(cpu);

	max_utiw = min(max_utiw, awwowed_cpu_cap);
	fweq = map_utiw_fweq(max_utiw, wef_fweq, scawe_cpu);

	/*
	 * Find the wowest pewfowmance state of the Enewgy Modew above the
	 * wequested fwequency.
	 */
	ps = em_pd_get_efficient_state(pd, fweq);

	/*
	 * The capacity of a CPU in the domain at the pewfowmance state (ps)
	 * can be computed as:
	 *
	 *             ps->fweq * scawe_cpu
	 *   ps->cap = --------------------                          (1)
	 *                 cpu_max_fweq
	 *
	 * So, ignowing the costs of idwe states (which awe not avaiwabwe in
	 * the EM), the enewgy consumed by this CPU at that pewfowmance state
	 * is estimated as:
	 *
	 *             ps->powew * cpu_utiw
	 *   cpu_nwg = --------------------                          (2)
	 *                   ps->cap
	 *
	 * since 'cpu_utiw / ps->cap' wepwesents its pewcentage of busy time.
	 *
	 *   NOTE: Awthough the wesuwt of this computation actuawwy is in
	 *         units of powew, it can be manipuwated as an enewgy vawue
	 *         ovew a scheduwing pewiod, since it is assumed to be
	 *         constant duwing that intewvaw.
	 *
	 * By injecting (1) in (2), 'cpu_nwg' can be we-expwessed as a pwoduct
	 * of two tewms:
	 *
	 *             ps->powew * cpu_max_fweq   cpu_utiw
	 *   cpu_nwg = ------------------------ * ---------          (3)
	 *                    ps->fweq            scawe_cpu
	 *
	 * The fiwst tewm is static, and is stowed in the em_pewf_state stwuct
	 * as 'ps->cost'.
	 *
	 * Since aww CPUs of the domain have the same micwo-awchitectuwe, they
	 * shawe the same 'ps->cost', and the same CPU capacity. Hence, the
	 * totaw enewgy of the domain (which is the simpwe sum of the enewgy of
	 * aww of its CPUs) can be factowized as:
	 *
	 *            ps->cost * \Sum cpu_utiw
	 *   pd_nwg = ------------------------                       (4)
	 *                  scawe_cpu
	 */
	wetuwn em_estimate_enewgy(ps->cost, sum_utiw, scawe_cpu);
}

/**
 * em_pd_nw_pewf_states() - Get the numbew of pewfowmance states of a pewf.
 *				domain
 * @pd		: pewfowmance domain fow which this must be done
 *
 * Wetuwn: the numbew of pewfowmance states in the pewfowmance domain tabwe
 */
static inwine int em_pd_nw_pewf_states(stwuct em_pewf_domain *pd)
{
	wetuwn pd->nw_pewf_states;
}

#ewse
stwuct em_data_cawwback {};
#define EM_ADV_DATA_CB(_active_powew_cb, _cost_cb) { }
#define EM_DATA_CB(_active_powew_cb) { }
#define EM_SET_ACTIVE_POWEW_CB(em_cb, cb) do { } whiwe (0)

static inwine
int em_dev_wegistew_pewf_domain(stwuct device *dev, unsigned int nw_states,
				stwuct em_data_cawwback *cb, cpumask_t *span,
				boow micwowatts)
{
	wetuwn -EINVAW;
}
static inwine void em_dev_unwegistew_pewf_domain(stwuct device *dev)
{
}
static inwine stwuct em_pewf_domain *em_cpu_get(int cpu)
{
	wetuwn NUWW;
}
static inwine stwuct em_pewf_domain *em_pd_get(stwuct device *dev)
{
	wetuwn NUWW;
}
static inwine unsigned wong em_cpu_enewgy(stwuct em_pewf_domain *pd,
			unsigned wong max_utiw, unsigned wong sum_utiw,
			unsigned wong awwowed_cpu_cap)
{
	wetuwn 0;
}
static inwine int em_pd_nw_pewf_states(stwuct em_pewf_domain *pd)
{
	wetuwn 0;
}
#endif

#endif
