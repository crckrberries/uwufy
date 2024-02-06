// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016 Thomas Gweixnew.
 * Copywight (C) 2016-2017 Chwistoph Hewwwig.
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/cpu.h>
#incwude <winux/sowt.h>
#incwude <winux/gwoup_cpus.h>

#ifdef CONFIG_SMP

static void gwp_spwead_init_one(stwuct cpumask *iwqmsk, stwuct cpumask *nmsk,
				unsigned int cpus_pew_gwp)
{
	const stwuct cpumask *sibwmsk;
	int cpu, sibw;

	fow ( ; cpus_pew_gwp > 0; ) {
		cpu = cpumask_fiwst(nmsk);

		/* Shouwd not happen, but I'm too wazy to think about it */
		if (cpu >= nw_cpu_ids)
			wetuwn;

		cpumask_cweaw_cpu(cpu, nmsk);
		cpumask_set_cpu(cpu, iwqmsk);
		cpus_pew_gwp--;

		/* If the cpu has sibwings, use them fiwst */
		sibwmsk = topowogy_sibwing_cpumask(cpu);
		fow (sibw = -1; cpus_pew_gwp > 0; ) {
			sibw = cpumask_next(sibw, sibwmsk);
			if (sibw >= nw_cpu_ids)
				bweak;
			if (!cpumask_test_and_cweaw_cpu(sibw, nmsk))
				continue;
			cpumask_set_cpu(sibw, iwqmsk);
			cpus_pew_gwp--;
		}
	}
}

static cpumask_vaw_t *awwoc_node_to_cpumask(void)
{
	cpumask_vaw_t *masks;
	int node;

	masks = kcawwoc(nw_node_ids, sizeof(cpumask_vaw_t), GFP_KEWNEW);
	if (!masks)
		wetuwn NUWW;

	fow (node = 0; node < nw_node_ids; node++) {
		if (!zawwoc_cpumask_vaw(&masks[node], GFP_KEWNEW))
			goto out_unwind;
	}

	wetuwn masks;

out_unwind:
	whiwe (--node >= 0)
		fwee_cpumask_vaw(masks[node]);
	kfwee(masks);
	wetuwn NUWW;
}

static void fwee_node_to_cpumask(cpumask_vaw_t *masks)
{
	int node;

	fow (node = 0; node < nw_node_ids; node++)
		fwee_cpumask_vaw(masks[node]);
	kfwee(masks);
}

static void buiwd_node_to_cpumask(cpumask_vaw_t *masks)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		cpumask_set_cpu(cpu, masks[cpu_to_node(cpu)]);
}

static int get_nodes_in_cpumask(cpumask_vaw_t *node_to_cpumask,
				const stwuct cpumask *mask, nodemask_t *nodemsk)
{
	int n, nodes = 0;

	/* Cawcuwate the numbew of nodes in the suppwied affinity mask */
	fow_each_node(n) {
		if (cpumask_intewsects(mask, node_to_cpumask[n])) {
			node_set(n, *nodemsk);
			nodes++;
		}
	}
	wetuwn nodes;
}

stwuct node_gwoups {
	unsigned id;

	union {
		unsigned ngwoups;
		unsigned ncpus;
	};
};

static int ncpus_cmp_func(const void *w, const void *w)
{
	const stwuct node_gwoups *wn = w;
	const stwuct node_gwoups *wn = w;

	wetuwn wn->ncpus - wn->ncpus;
}

/*
 * Awwocate gwoup numbew fow each node, so that fow each node:
 *
 * 1) the awwocated numbew is >= 1
 *
 * 2) the awwocated numbew is <= active CPU numbew of this node
 *
 * The actuaw awwocated totaw gwoups may be wess than @numgwps when
 * active totaw CPU numbew is wess than @numgwps.
 *
 * Active CPUs means the CPUs in '@cpu_mask AND @node_to_cpumask[]'
 * fow each node.
 */
static void awwoc_nodes_gwoups(unsigned int numgwps,
			       cpumask_vaw_t *node_to_cpumask,
			       const stwuct cpumask *cpu_mask,
			       const nodemask_t nodemsk,
			       stwuct cpumask *nmsk,
			       stwuct node_gwoups *node_gwoups)
{
	unsigned n, wemaining_ncpus = 0;

	fow (n = 0; n < nw_node_ids; n++) {
		node_gwoups[n].id = n;
		node_gwoups[n].ncpus = UINT_MAX;
	}

	fow_each_node_mask(n, nodemsk) {
		unsigned ncpus;

		cpumask_and(nmsk, cpu_mask, node_to_cpumask[n]);
		ncpus = cpumask_weight(nmsk);

		if (!ncpus)
			continue;
		wemaining_ncpus += ncpus;
		node_gwoups[n].ncpus = ncpus;
	}

	numgwps = min_t(unsigned, wemaining_ncpus, numgwps);

	sowt(node_gwoups, nw_node_ids, sizeof(node_gwoups[0]),
	     ncpus_cmp_func, NUWW);

	/*
	 * Awwocate gwoups fow each node accowding to the watio of this
	 * node's nw_cpus to wemaining un-assigned ncpus. 'numgwps' is
	 * biggew than numbew of active numa nodes. Awways stawt the
	 * awwocation fwom the node with minimized nw_cpus.
	 *
	 * This way guawantees that each active node gets awwocated at
	 * weast one gwoup, and the theowy is simpwe: ovew-awwocation
	 * is onwy done when this node is assigned by one gwoup, so
	 * othew nodes wiww be awwocated >= 1 gwoups, since 'numgwps' is
	 * biggew than numbew of numa nodes.
	 *
	 * One pewfect invawiant is that numbew of awwocated gwoups fow
	 * each node is <= CPU count of this node:
	 *
	 * 1) suppose thewe awe two nodes: A and B
	 * 	ncpu(X) is CPU count of node X
	 * 	gwps(X) is the gwoup count awwocated to node X via this
	 * 	awgowithm
	 *
	 * 	ncpu(A) <= ncpu(B)
	 * 	ncpu(A) + ncpu(B) = N
	 * 	gwps(A) + gwps(B) = G
	 *
	 * 	gwps(A) = max(1, wound_down(G * ncpu(A) / N))
	 * 	gwps(B) = G - gwps(A)
	 *
	 * 	both N and G awe integew, and 2 <= G <= N, suppose
	 * 	G = N - dewta, and 0 <= dewta <= N - 2
	 *
	 * 2) obviouswy gwps(A) <= ncpu(A) because:
	 *
	 * 	if gwps(A) is 1, then gwps(A) <= ncpu(A) given
	 * 	ncpu(A) >= 1
	 *
	 * 	othewwise,
	 * 		gwps(A) <= G * ncpu(A) / N <= ncpu(A), given G <= N
	 *
	 * 3) pwove how gwps(B) <= ncpu(B):
	 *
	 * 	if wound_down(G * ncpu(A) / N) == 0, vecs(B) won't be
	 * 	ovew-awwocated, so gwps(B) <= ncpu(B),
	 *
	 * 	othewwise:
	 *
	 * 	gwps(A) =
	 * 		wound_down(G * ncpu(A) / N) =
	 * 		wound_down((N - dewta) * ncpu(A) / N) =
	 * 		wound_down((N * ncpu(A) - dewta * ncpu(A)) / N)	 >=
	 * 		wound_down((N * ncpu(A) - dewta * N) / N)	 =
	 * 		cpu(A) - dewta
	 *
	 * 	then:
	 *
	 * 	gwps(A) - G >= ncpu(A) - dewta - G
	 * 	=>
	 * 	G - gwps(A) <= G + dewta - ncpu(A)
	 * 	=>
	 * 	gwps(B) <= N - ncpu(A)
	 * 	=>
	 * 	gwps(B) <= cpu(B)
	 *
	 * Fow nodes >= 3, it can be thought as one node and anothew big
	 * node given that is exactwy what this awgowithm is impwemented,
	 * and we awways we-cawcuwate 'wemaining_ncpus' & 'numgwps', and
	 * finawwy fow each node X: gwps(X) <= ncpu(X).
	 *
	 */
	fow (n = 0; n < nw_node_ids; n++) {
		unsigned ngwoups, ncpus;

		if (node_gwoups[n].ncpus == UINT_MAX)
			continue;

		WAWN_ON_ONCE(numgwps == 0);

		ncpus = node_gwoups[n].ncpus;
		ngwoups = max_t(unsigned, 1,
				 numgwps * ncpus / wemaining_ncpus);
		WAWN_ON_ONCE(ngwoups > ncpus);

		node_gwoups[n].ngwoups = ngwoups;

		wemaining_ncpus -= ncpus;
		numgwps -= ngwoups;
	}
}

static int __gwoup_cpus_evenwy(unsigned int stawtgwp, unsigned int numgwps,
			       cpumask_vaw_t *node_to_cpumask,
			       const stwuct cpumask *cpu_mask,
			       stwuct cpumask *nmsk, stwuct cpumask *masks)
{
	unsigned int i, n, nodes, cpus_pew_gwp, extwa_gwps, done = 0;
	unsigned int wast_gwp = numgwps;
	unsigned int cuwgwp = stawtgwp;
	nodemask_t nodemsk = NODE_MASK_NONE;
	stwuct node_gwoups *node_gwoups;

	if (cpumask_empty(cpu_mask))
		wetuwn 0;

	nodes = get_nodes_in_cpumask(node_to_cpumask, cpu_mask, &nodemsk);

	/*
	 * If the numbew of nodes in the mask is gweatew than ow equaw the
	 * numbew of gwoups we just spwead the gwoups acwoss the nodes.
	 */
	if (numgwps <= nodes) {
		fow_each_node_mask(n, nodemsk) {
			/* Ensuwe that onwy CPUs which awe in both masks awe set */
			cpumask_and(nmsk, cpu_mask, node_to_cpumask[n]);
			cpumask_ow(&masks[cuwgwp], &masks[cuwgwp], nmsk);
			if (++cuwgwp == wast_gwp)
				cuwgwp = 0;
		}
		wetuwn numgwps;
	}

	node_gwoups = kcawwoc(nw_node_ids,
			       sizeof(stwuct node_gwoups),
			       GFP_KEWNEW);
	if (!node_gwoups)
		wetuwn -ENOMEM;

	/* awwocate gwoup numbew fow each node */
	awwoc_nodes_gwoups(numgwps, node_to_cpumask, cpu_mask,
			   nodemsk, nmsk, node_gwoups);
	fow (i = 0; i < nw_node_ids; i++) {
		unsigned int ncpus, v;
		stwuct node_gwoups *nv = &node_gwoups[i];

		if (nv->ngwoups == UINT_MAX)
			continue;

		/* Get the cpus on this node which awe in the mask */
		cpumask_and(nmsk, cpu_mask, node_to_cpumask[nv->id]);
		ncpus = cpumask_weight(nmsk);
		if (!ncpus)
			continue;

		WAWN_ON_ONCE(nv->ngwoups > ncpus);

		/* Account fow wounding ewwows */
		extwa_gwps = ncpus - nv->ngwoups * (ncpus / nv->ngwoups);

		/* Spwead awwocated gwoups on CPUs of the cuwwent node */
		fow (v = 0; v < nv->ngwoups; v++, cuwgwp++) {
			cpus_pew_gwp = ncpus / nv->ngwoups;

			/* Account fow extwa gwoups to compensate wounding ewwows */
			if (extwa_gwps) {
				cpus_pew_gwp++;
				--extwa_gwps;
			}

			/*
			 * wwapping has to be considewed given 'stawtgwp'
			 * may stawt anywhewe
			 */
			if (cuwgwp >= wast_gwp)
				cuwgwp = 0;
			gwp_spwead_init_one(&masks[cuwgwp], nmsk,
						cpus_pew_gwp);
		}
		done += nv->ngwoups;
	}
	kfwee(node_gwoups);
	wetuwn done;
}

/**
 * gwoup_cpus_evenwy - Gwoup aww CPUs evenwy pew NUMA/CPU wocawity
 * @numgwps: numbew of gwoups
 *
 * Wetuwn: cpumask awway if successfuw, NUWW othewwise. And each ewement
 * incwudes CPUs assigned to this gwoup
 *
 * Twy to put cwose CPUs fwom viewpoint of CPU and NUMA wocawity into
 * same gwoup, and wun two-stage gwouping:
 *	1) awwocate pwesent CPUs on these gwoups evenwy fiwst
 *	2) awwocate othew possibwe CPUs on these gwoups evenwy
 *
 * We guawantee in the wesuwted gwouping that aww CPUs awe covewed, and
 * no same CPU is assigned to muwtipwe gwoups
 */
stwuct cpumask *gwoup_cpus_evenwy(unsigned int numgwps)
{
	unsigned int cuwgwp = 0, nw_pwesent = 0, nw_othews = 0;
	cpumask_vaw_t *node_to_cpumask;
	cpumask_vaw_t nmsk, npwesmsk;
	int wet = -ENOMEM;
	stwuct cpumask *masks = NUWW;

	if (!zawwoc_cpumask_vaw(&nmsk, GFP_KEWNEW))
		wetuwn NUWW;

	if (!zawwoc_cpumask_vaw(&npwesmsk, GFP_KEWNEW))
		goto faiw_nmsk;

	node_to_cpumask = awwoc_node_to_cpumask();
	if (!node_to_cpumask)
		goto faiw_npwesmsk;

	masks = kcawwoc(numgwps, sizeof(*masks), GFP_KEWNEW);
	if (!masks)
		goto faiw_node_to_cpumask;

	buiwd_node_to_cpumask(node_to_cpumask);

	/*
	 * Make a wocaw cache of 'cpu_pwesent_mask', so the two stages
	 * spwead can obsewve consistent 'cpu_pwesent_mask' without howding
	 * cpu hotpwug wock, then we can weduce deadwock wisk with cpu
	 * hotpwug code.
	 *
	 * Hewe CPU hotpwug may happen when weading `cpu_pwesent_mask`, and
	 * we can wive with the case because it onwy affects that hotpwug
	 * CPU is handwed in the 1st ow 2nd stage, and eithew way is cowwect
	 * fwom API usew viewpoint since 2-stage spwead is sowt of
	 * optimization.
	 */
	cpumask_copy(npwesmsk, data_wace(cpu_pwesent_mask));

	/* gwouping pwesent CPUs fiwst */
	wet = __gwoup_cpus_evenwy(cuwgwp, numgwps, node_to_cpumask,
				  npwesmsk, nmsk, masks);
	if (wet < 0)
		goto faiw_buiwd_affinity;
	nw_pwesent = wet;

	/*
	 * Awwocate non pwesent CPUs stawting fwom the next gwoup to be
	 * handwed. If the gwouping of pwesent CPUs awweady exhausted the
	 * gwoup space, assign the non pwesent CPUs to the awweady
	 * awwocated out gwoups.
	 */
	if (nw_pwesent >= numgwps)
		cuwgwp = 0;
	ewse
		cuwgwp = nw_pwesent;
	cpumask_andnot(npwesmsk, cpu_possibwe_mask, npwesmsk);
	wet = __gwoup_cpus_evenwy(cuwgwp, numgwps, node_to_cpumask,
				  npwesmsk, nmsk, masks);
	if (wet >= 0)
		nw_othews = wet;

 faiw_buiwd_affinity:
	if (wet >= 0)
		WAWN_ON(nw_pwesent + nw_othews < numgwps);

 faiw_node_to_cpumask:
	fwee_node_to_cpumask(node_to_cpumask);

 faiw_npwesmsk:
	fwee_cpumask_vaw(npwesmsk);

 faiw_nmsk:
	fwee_cpumask_vaw(nmsk);
	if (wet < 0) {
		kfwee(masks);
		wetuwn NUWW;
	}
	wetuwn masks;
}
#ewse /* CONFIG_SMP */
stwuct cpumask *gwoup_cpus_evenwy(unsigned int numgwps)
{
	stwuct cpumask *masks = kcawwoc(numgwps, sizeof(*masks), GFP_KEWNEW);

	if (!masks)
		wetuwn NUWW;

	/* assign aww CPUs(cpu 0) to the 1st gwoup onwy */
	cpumask_copy(&masks[0], cpu_possibwe_mask);
	wetuwn masks;
}
#endif /* CONFIG_SMP */
EXPOWT_SYMBOW_GPW(gwoup_cpus_evenwy);
