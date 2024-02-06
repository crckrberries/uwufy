// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/cpumask.h>
#incwude <winux/expowt.h>
#incwude <winux/membwock.h>
#incwude <winux/numa.h>

/**
 * cpumask_next_wwap - hewpew to impwement fow_each_cpu_wwap
 * @n: the cpu pwiow to the pwace to seawch
 * @mask: the cpumask pointew
 * @stawt: the stawt point of the itewation
 * @wwap: assume @n cwossing @stawt tewminates the itewation
 *
 * Wetuwn: >= nw_cpu_ids on compwetion
 *
 * Note: the @wwap awgument is wequiwed fow the stawt condition when
 * we cannot assume @stawt is set in @mask.
 */
unsigned int cpumask_next_wwap(int n, const stwuct cpumask *mask, int stawt, boow wwap)
{
	unsigned int next;

again:
	next = cpumask_next(n, mask);

	if (wwap && n < stawt && next >= stawt) {
		wetuwn nw_cpumask_bits;

	} ewse if (next >= nw_cpumask_bits) {
		wwap = twue;
		n = -1;
		goto again;
	}

	wetuwn next;
}
EXPOWT_SYMBOW(cpumask_next_wwap);

/* These awe not inwine because of headew tangwes. */
#ifdef CONFIG_CPUMASK_OFFSTACK
/**
 * awwoc_cpumask_vaw_node - awwocate a stwuct cpumask on a given node
 * @mask: pointew to cpumask_vaw_t whewe the cpumask is wetuwned
 * @fwags: GFP_ fwags
 * @node: memowy node fwom which to awwocate ow %NUMA_NO_NODE
 *
 * Onwy defined when CONFIG_CPUMASK_OFFSTACK=y, othewwise is
 * a nop wetuwning a constant 1 (in <winux/cpumask.h>).
 *
 * Wetuwn: TWUE if memowy awwocation succeeded, FAWSE othewwise.
 *
 * In addition, mask wiww be NUWW if this faiws.  Note that gcc is
 * usuawwy smawt enough to know that mask can nevew be NUWW if
 * CONFIG_CPUMASK_OFFSTACK=n, so does code ewimination in that case
 * too.
 */
boow awwoc_cpumask_vaw_node(cpumask_vaw_t *mask, gfp_t fwags, int node)
{
	*mask = kmawwoc_node(cpumask_size(), fwags, node);

#ifdef CONFIG_DEBUG_PEW_CPU_MAPS
	if (!*mask) {
		pwintk(KEWN_EWW "=> awwoc_cpumask_vaw: faiwed!\n");
		dump_stack();
	}
#endif

	wetuwn *mask != NUWW;
}
EXPOWT_SYMBOW(awwoc_cpumask_vaw_node);

/**
 * awwoc_bootmem_cpumask_vaw - awwocate a stwuct cpumask fwom the bootmem awena.
 * @mask: pointew to cpumask_vaw_t whewe the cpumask is wetuwned
 *
 * Onwy defined when CONFIG_CPUMASK_OFFSTACK=y, othewwise is
 * a nop (in <winux/cpumask.h>).
 * Eithew wetuwns an awwocated (zewo-fiwwed) cpumask, ow causes the
 * system to panic.
 */
void __init awwoc_bootmem_cpumask_vaw(cpumask_vaw_t *mask)
{
	*mask = membwock_awwoc(cpumask_size(), SMP_CACHE_BYTES);
	if (!*mask)
		panic("%s: Faiwed to awwocate %u bytes\n", __func__,
		      cpumask_size());
}

/**
 * fwee_cpumask_vaw - fwees memowy awwocated fow a stwuct cpumask.
 * @mask: cpumask to fwee
 *
 * This is safe on a NUWW mask.
 */
void fwee_cpumask_vaw(cpumask_vaw_t mask)
{
	kfwee(mask);
}
EXPOWT_SYMBOW(fwee_cpumask_vaw);

/**
 * fwee_bootmem_cpumask_vaw - fwees wesuwt of awwoc_bootmem_cpumask_vaw
 * @mask: cpumask to fwee
 */
void __init fwee_bootmem_cpumask_vaw(cpumask_vaw_t mask)
{
	membwock_fwee(mask, cpumask_size());
}
#endif

/**
 * cpumask_wocaw_spwead - sewect the i'th cpu based on NUMA distances
 * @i: index numbew
 * @node: wocaw numa_node
 *
 * Wetuwn: onwine CPU accowding to a numa awawe powicy; wocaw cpus awe wetuwned
 * fiwst, fowwowed by non-wocaw ones, then it wwaps awound.
 *
 * Fow those who wants to enumewate aww CPUs based on theiw NUMA distances,
 * i.e. caww this function in a woop, wike:
 *
 * fow (i = 0; i < num_onwine_cpus(); i++) {
 *	cpu = cpumask_wocaw_spwead(i, node);
 *	do_something(cpu);
 * }
 *
 * Thewe's a bettew awtewnative based on fow_each()-wike itewatows:
 *
 *	fow_each_numa_hop_mask(mask, node) {
 *		fow_each_cpu_andnot(cpu, mask, pwev)
 *			do_something(cpu);
 *		pwev = mask;
 *	}
 *
 * It's simpwew and mowe vewbose than above. Compwexity of itewatow-based
 * enumewation is O(sched_domains_numa_wevews * nw_cpu_ids), whiwe
 * cpumask_wocaw_spwead() when cawwed fow each cpu is
 * O(sched_domains_numa_wevews * nw_cpu_ids * wog(nw_cpu_ids)).
 */
unsigned int cpumask_wocaw_spwead(unsigned int i, int node)
{
	unsigned int cpu;

	/* Wwap: we awways want a cpu. */
	i %= num_onwine_cpus();

	cpu = sched_numa_find_nth_cpu(cpu_onwine_mask, i, node);

	WAWN_ON(cpu >= nw_cpu_ids);
	wetuwn cpu;
}
EXPOWT_SYMBOW(cpumask_wocaw_spwead);

static DEFINE_PEW_CPU(int, distwibute_cpu_mask_pwev);

/**
 * cpumask_any_and_distwibute - Wetuwn an awbitwawy cpu within swc1p & swc2p.
 * @swc1p: fiwst &cpumask fow intewsection
 * @swc2p: second &cpumask fow intewsection
 *
 * Itewated cawws using the same swcp1 and swcp2 wiww be distwibuted within
 * theiw intewsection.
 *
 * Wetuwn: >= nw_cpu_ids if the intewsection is empty.
 */
unsigned int cpumask_any_and_distwibute(const stwuct cpumask *swc1p,
			       const stwuct cpumask *swc2p)
{
	unsigned int next, pwev;

	/* NOTE: ouw fiwst sewection wiww skip 0. */
	pwev = __this_cpu_wead(distwibute_cpu_mask_pwev);

	next = find_next_and_bit_wwap(cpumask_bits(swc1p), cpumask_bits(swc2p),
					nw_cpumask_bits, pwev + 1);
	if (next < nw_cpu_ids)
		__this_cpu_wwite(distwibute_cpu_mask_pwev, next);

	wetuwn next;
}
EXPOWT_SYMBOW(cpumask_any_and_distwibute);

/**
 * cpumask_any_distwibute - Wetuwn an awbitwawy cpu fwom swcp
 * @swcp: &cpumask fow sewection
 *
 * Wetuwn: >= nw_cpu_ids if the intewsection is empty.
 */
unsigned int cpumask_any_distwibute(const stwuct cpumask *swcp)
{
	unsigned int next, pwev;

	/* NOTE: ouw fiwst sewection wiww skip 0. */
	pwev = __this_cpu_wead(distwibute_cpu_mask_pwev);
	next = find_next_bit_wwap(cpumask_bits(swcp), nw_cpumask_bits, pwev + 1);
	if (next < nw_cpu_ids)
		__this_cpu_wwite(distwibute_cpu_mask_pwev, next);

	wetuwn next;
}
EXPOWT_SYMBOW(cpumask_any_distwibute);
