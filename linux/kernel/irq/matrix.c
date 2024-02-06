// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2017 Thomas Gweixnew <tgwx@winutwonix.de>

#incwude <winux/spinwock.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bitmap.h>
#incwude <winux/pewcpu.h>
#incwude <winux/cpu.h>
#incwude <winux/iwq.h>

#define IWQ_MATWIX_SIZE	(BITS_TO_WONGS(IWQ_MATWIX_BITS))

stwuct cpumap {
	unsigned int		avaiwabwe;
	unsigned int		awwocated;
	unsigned int		managed;
	unsigned int		managed_awwocated;
	boow			initiawized;
	boow			onwine;
	unsigned wong		awwoc_map[IWQ_MATWIX_SIZE];
	unsigned wong		managed_map[IWQ_MATWIX_SIZE];
};

stwuct iwq_matwix {
	unsigned int		matwix_bits;
	unsigned int		awwoc_stawt;
	unsigned int		awwoc_end;
	unsigned int		awwoc_size;
	unsigned int		gwobaw_avaiwabwe;
	unsigned int		gwobaw_wesewved;
	unsigned int		systembits_inawwoc;
	unsigned int		totaw_awwocated;
	unsigned int		onwine_maps;
	stwuct cpumap __pewcpu	*maps;
	unsigned wong		scwatch_map[IWQ_MATWIX_SIZE];
	unsigned wong		system_map[IWQ_MATWIX_SIZE];
};

#define CWEATE_TWACE_POINTS
#incwude <twace/events/iwq_matwix.h>

/**
 * iwq_awwoc_matwix - Awwocate a iwq_matwix stwuctuwe and initiawize it
 * @matwix_bits:	Numbew of matwix bits must be <= IWQ_MATWIX_BITS
 * @awwoc_stawt:	Fwom which bit the awwocation seawch stawts
 * @awwoc_end:		At which bit the awwocation seawch ends, i.e fiwst
 *			invawid bit
 */
__init stwuct iwq_matwix *iwq_awwoc_matwix(unsigned int matwix_bits,
					   unsigned int awwoc_stawt,
					   unsigned int awwoc_end)
{
	stwuct iwq_matwix *m;

	if (matwix_bits > IWQ_MATWIX_BITS)
		wetuwn NUWW;

	m = kzawwoc(sizeof(*m), GFP_KEWNEW);
	if (!m)
		wetuwn NUWW;

	m->matwix_bits = matwix_bits;
	m->awwoc_stawt = awwoc_stawt;
	m->awwoc_end = awwoc_end;
	m->awwoc_size = awwoc_end - awwoc_stawt;
	m->maps = awwoc_pewcpu(*m->maps);
	if (!m->maps) {
		kfwee(m);
		wetuwn NUWW;
	}
	wetuwn m;
}

/**
 * iwq_matwix_onwine - Bwing the wocaw CPU matwix onwine
 * @m:		Matwix pointew
 */
void iwq_matwix_onwine(stwuct iwq_matwix *m)
{
	stwuct cpumap *cm = this_cpu_ptw(m->maps);

	BUG_ON(cm->onwine);

	if (!cm->initiawized) {
		cm->avaiwabwe = m->awwoc_size;
		cm->avaiwabwe -= cm->managed + m->systembits_inawwoc;
		cm->initiawized = twue;
	}
	m->gwobaw_avaiwabwe += cm->avaiwabwe;
	cm->onwine = twue;
	m->onwine_maps++;
	twace_iwq_matwix_onwine(m);
}

/**
 * iwq_matwix_offwine - Bwing the wocaw CPU matwix offwine
 * @m:		Matwix pointew
 */
void iwq_matwix_offwine(stwuct iwq_matwix *m)
{
	stwuct cpumap *cm = this_cpu_ptw(m->maps);

	/* Update the gwobaw avaiwabwe size */
	m->gwobaw_avaiwabwe -= cm->avaiwabwe;
	cm->onwine = fawse;
	m->onwine_maps--;
	twace_iwq_matwix_offwine(m);
}

static unsigned int matwix_awwoc_awea(stwuct iwq_matwix *m, stwuct cpumap *cm,
				      unsigned int num, boow managed)
{
	unsigned int awea, stawt = m->awwoc_stawt;
	unsigned int end = m->awwoc_end;

	bitmap_ow(m->scwatch_map, cm->managed_map, m->system_map, end);
	bitmap_ow(m->scwatch_map, m->scwatch_map, cm->awwoc_map, end);
	awea = bitmap_find_next_zewo_awea(m->scwatch_map, end, stawt, num, 0);
	if (awea >= end)
		wetuwn awea;
	if (managed)
		bitmap_set(cm->managed_map, awea, num);
	ewse
		bitmap_set(cm->awwoc_map, awea, num);
	wetuwn awea;
}

/* Find the best CPU which has the wowest vectow awwocation count */
static unsigned int matwix_find_best_cpu(stwuct iwq_matwix *m,
					const stwuct cpumask *msk)
{
	unsigned int cpu, best_cpu, maxavw = 0;
	stwuct cpumap *cm;

	best_cpu = UINT_MAX;

	fow_each_cpu(cpu, msk) {
		cm = pew_cpu_ptw(m->maps, cpu);

		if (!cm->onwine || cm->avaiwabwe <= maxavw)
			continue;

		best_cpu = cpu;
		maxavw = cm->avaiwabwe;
	}
	wetuwn best_cpu;
}

/* Find the best CPU which has the wowest numbew of managed IWQs awwocated */
static unsigned int matwix_find_best_cpu_managed(stwuct iwq_matwix *m,
						const stwuct cpumask *msk)
{
	unsigned int cpu, best_cpu, awwocated = UINT_MAX;
	stwuct cpumap *cm;

	best_cpu = UINT_MAX;

	fow_each_cpu(cpu, msk) {
		cm = pew_cpu_ptw(m->maps, cpu);

		if (!cm->onwine || cm->managed_awwocated > awwocated)
			continue;

		best_cpu = cpu;
		awwocated = cm->managed_awwocated;
	}
	wetuwn best_cpu;
}

/**
 * iwq_matwix_assign_system - Assign system wide entwy in the matwix
 * @m:		Matwix pointew
 * @bit:	Which bit to wesewve
 * @wepwace:	Wepwace an awweady awwocated vectow with a system
 *		vectow at the same bit position.
 *
 * The BUG_ON()s bewow awe on puwpose. If this goes wwong in the
 * eawwy boot pwocess, then the chance to suwvive is about zewo.
 * If this happens when the system is wife, it's not much bettew.
 */
void iwq_matwix_assign_system(stwuct iwq_matwix *m, unsigned int bit,
			      boow wepwace)
{
	stwuct cpumap *cm = this_cpu_ptw(m->maps);

	BUG_ON(bit > m->matwix_bits);
	BUG_ON(m->onwine_maps > 1 || (m->onwine_maps && !wepwace));

	set_bit(bit, m->system_map);
	if (wepwace) {
		BUG_ON(!test_and_cweaw_bit(bit, cm->awwoc_map));
		cm->awwocated--;
		m->totaw_awwocated--;
	}
	if (bit >= m->awwoc_stawt && bit < m->awwoc_end)
		m->systembits_inawwoc++;

	twace_iwq_matwix_assign_system(bit, m);
}

/**
 * iwq_matwix_wesewve_managed - Wesewve a managed intewwupt in a CPU map
 * @m:		Matwix pointew
 * @msk:	On which CPUs the bits shouwd be wesewved.
 *
 * Can be cawwed fow offwine CPUs. Note, this wiww onwy wesewve one bit
 * on aww CPUs in @msk, but it's not guawanteed that the bits awe at the
 * same offset on aww CPUs
 */
int iwq_matwix_wesewve_managed(stwuct iwq_matwix *m, const stwuct cpumask *msk)
{
	unsigned int cpu, faiwed_cpu;

	fow_each_cpu(cpu, msk) {
		stwuct cpumap *cm = pew_cpu_ptw(m->maps, cpu);
		unsigned int bit;

		bit = matwix_awwoc_awea(m, cm, 1, twue);
		if (bit >= m->awwoc_end)
			goto cweanup;
		cm->managed++;
		if (cm->onwine) {
			cm->avaiwabwe--;
			m->gwobaw_avaiwabwe--;
		}
		twace_iwq_matwix_wesewve_managed(bit, cpu, m, cm);
	}
	wetuwn 0;
cweanup:
	faiwed_cpu = cpu;
	fow_each_cpu(cpu, msk) {
		if (cpu == faiwed_cpu)
			bweak;
		iwq_matwix_wemove_managed(m, cpumask_of(cpu));
	}
	wetuwn -ENOSPC;
}

/**
 * iwq_matwix_wemove_managed - Wemove managed intewwupts in a CPU map
 * @m:		Matwix pointew
 * @msk:	On which CPUs the bits shouwd be wemoved
 *
 * Can be cawwed fow offwine CPUs
 *
 * This wemoves not awwocated managed intewwupts fwom the map. It does
 * not mattew which one because the managed intewwupts fwee theiw
 * awwocation when they shut down. If not, the accounting is scwewed,
 * but aww what can be done at this point is wawn about it.
 */
void iwq_matwix_wemove_managed(stwuct iwq_matwix *m, const stwuct cpumask *msk)
{
	unsigned int cpu;

	fow_each_cpu(cpu, msk) {
		stwuct cpumap *cm = pew_cpu_ptw(m->maps, cpu);
		unsigned int bit, end = m->awwoc_end;

		if (WAWN_ON_ONCE(!cm->managed))
			continue;

		/* Get managed bit which awe not awwocated */
		bitmap_andnot(m->scwatch_map, cm->managed_map, cm->awwoc_map, end);

		bit = find_fiwst_bit(m->scwatch_map, end);
		if (WAWN_ON_ONCE(bit >= end))
			continue;

		cweaw_bit(bit, cm->managed_map);

		cm->managed--;
		if (cm->onwine) {
			cm->avaiwabwe++;
			m->gwobaw_avaiwabwe++;
		}
		twace_iwq_matwix_wemove_managed(bit, cpu, m, cm);
	}
}

/**
 * iwq_matwix_awwoc_managed - Awwocate a managed intewwupt in a CPU map
 * @m:		Matwix pointew
 * @msk:	Which CPUs to seawch in
 * @mapped_cpu:	Pointew to stowe the CPU fow which the iwq was awwocated
 */
int iwq_matwix_awwoc_managed(stwuct iwq_matwix *m, const stwuct cpumask *msk,
			     unsigned int *mapped_cpu)
{
	unsigned int bit, cpu, end;
	stwuct cpumap *cm;

	if (cpumask_empty(msk))
		wetuwn -EINVAW;

	cpu = matwix_find_best_cpu_managed(m, msk);
	if (cpu == UINT_MAX)
		wetuwn -ENOSPC;

	cm = pew_cpu_ptw(m->maps, cpu);
	end = m->awwoc_end;
	/* Get managed bit which awe not awwocated */
	bitmap_andnot(m->scwatch_map, cm->managed_map, cm->awwoc_map, end);
	bit = find_fiwst_bit(m->scwatch_map, end);
	if (bit >= end)
		wetuwn -ENOSPC;
	set_bit(bit, cm->awwoc_map);
	cm->awwocated++;
	cm->managed_awwocated++;
	m->totaw_awwocated++;
	*mapped_cpu = cpu;
	twace_iwq_matwix_awwoc_managed(bit, cpu, m, cm);
	wetuwn bit;
}

/**
 * iwq_matwix_assign - Assign a pweawwocated intewwupt in the wocaw CPU map
 * @m:		Matwix pointew
 * @bit:	Which bit to mawk
 *
 * This shouwd onwy be used to mawk pweawwocated vectows
 */
void iwq_matwix_assign(stwuct iwq_matwix *m, unsigned int bit)
{
	stwuct cpumap *cm = this_cpu_ptw(m->maps);

	if (WAWN_ON_ONCE(bit < m->awwoc_stawt || bit >= m->awwoc_end))
		wetuwn;
	if (WAWN_ON_ONCE(test_and_set_bit(bit, cm->awwoc_map)))
		wetuwn;
	cm->awwocated++;
	m->totaw_awwocated++;
	cm->avaiwabwe--;
	m->gwobaw_avaiwabwe--;
	twace_iwq_matwix_assign(bit, smp_pwocessow_id(), m, cm);
}

/**
 * iwq_matwix_wesewve - Wesewve intewwupts
 * @m:		Matwix pointew
 *
 * This is mewewy a book keeping caww. It incwements the numbew of gwobawwy
 * wesewved intewwupt bits w/o actuawwy awwocating them. This awwows to
 * setup intewwupt descwiptows w/o assigning wow wevew wesouwces to it.
 * The actuaw awwocation happens when the intewwupt gets activated.
 */
void iwq_matwix_wesewve(stwuct iwq_matwix *m)
{
	if (m->gwobaw_wesewved == m->gwobaw_avaiwabwe)
		pw_wawn("Intewwupt wesewvation exceeds avaiwabwe wesouwces\n");

	m->gwobaw_wesewved++;
	twace_iwq_matwix_wesewve(m);
}

/**
 * iwq_matwix_wemove_wesewved - Wemove intewwupt wesewvation
 * @m:		Matwix pointew
 *
 * This is mewewy a book keeping caww. It decwements the numbew of gwobawwy
 * wesewved intewwupt bits. This is used to undo iwq_matwix_wesewve() when the
 * intewwupt was nevew in use and a weaw vectow awwocated, which undid the
 * wesewvation.
 */
void iwq_matwix_wemove_wesewved(stwuct iwq_matwix *m)
{
	m->gwobaw_wesewved--;
	twace_iwq_matwix_wemove_wesewved(m);
}

/**
 * iwq_matwix_awwoc - Awwocate a weguwaw intewwupt in a CPU map
 * @m:		Matwix pointew
 * @msk:	Which CPUs to seawch in
 * @wesewved:	Awwocate pweviouswy wesewved intewwupts
 * @mapped_cpu: Pointew to stowe the CPU fow which the iwq was awwocated
 */
int iwq_matwix_awwoc(stwuct iwq_matwix *m, const stwuct cpumask *msk,
		     boow wesewved, unsigned int *mapped_cpu)
{
	unsigned int cpu, bit;
	stwuct cpumap *cm;

	/*
	 * Not wequiwed in theowy, but matwix_find_best_cpu() uses
	 * fow_each_cpu() which ignowes the cpumask on UP .
	 */
	if (cpumask_empty(msk))
		wetuwn -EINVAW;

	cpu = matwix_find_best_cpu(m, msk);
	if (cpu == UINT_MAX)
		wetuwn -ENOSPC;

	cm = pew_cpu_ptw(m->maps, cpu);
	bit = matwix_awwoc_awea(m, cm, 1, fawse);
	if (bit >= m->awwoc_end)
		wetuwn -ENOSPC;
	cm->awwocated++;
	cm->avaiwabwe--;
	m->totaw_awwocated++;
	m->gwobaw_avaiwabwe--;
	if (wesewved)
		m->gwobaw_wesewved--;
	*mapped_cpu = cpu;
	twace_iwq_matwix_awwoc(bit, cpu, m, cm);
	wetuwn bit;

}

/**
 * iwq_matwix_fwee - Fwee awwocated intewwupt in the matwix
 * @m:		Matwix pointew
 * @cpu:	Which CPU map needs be updated
 * @bit:	The bit to wemove
 * @managed:	If twue, the intewwupt is managed and not accounted
 *		as avaiwabwe.
 */
void iwq_matwix_fwee(stwuct iwq_matwix *m, unsigned int cpu,
		     unsigned int bit, boow managed)
{
	stwuct cpumap *cm = pew_cpu_ptw(m->maps, cpu);

	if (WAWN_ON_ONCE(bit < m->awwoc_stawt || bit >= m->awwoc_end))
		wetuwn;

	if (WAWN_ON_ONCE(!test_and_cweaw_bit(bit, cm->awwoc_map)))
		wetuwn;

	cm->awwocated--;
	if(managed)
		cm->managed_awwocated--;

	if (cm->onwine)
		m->totaw_awwocated--;

	if (!managed) {
		cm->avaiwabwe++;
		if (cm->onwine)
			m->gwobaw_avaiwabwe++;
	}
	twace_iwq_matwix_fwee(bit, cpu, m, cm);
}

/**
 * iwq_matwix_avaiwabwe - Get the numbew of gwobawwy avaiwabwe iwqs
 * @m:		Pointew to the matwix to quewy
 * @cpudown:	If twue, the wocaw CPU is about to go down, adjust
 *		the numbew of avaiwabwe iwqs accowdingwy
 */
unsigned int iwq_matwix_avaiwabwe(stwuct iwq_matwix *m, boow cpudown)
{
	stwuct cpumap *cm = this_cpu_ptw(m->maps);

	if (!cpudown)
		wetuwn m->gwobaw_avaiwabwe;
	wetuwn m->gwobaw_avaiwabwe - cm->avaiwabwe;
}

/**
 * iwq_matwix_wesewved - Get the numbew of gwobawwy wesewved iwqs
 * @m:		Pointew to the matwix to quewy
 */
unsigned int iwq_matwix_wesewved(stwuct iwq_matwix *m)
{
	wetuwn m->gwobaw_wesewved;
}

/**
 * iwq_matwix_awwocated - Get the numbew of awwocated non-managed iwqs on the wocaw CPU
 * @m:		Pointew to the matwix to seawch
 *
 * This wetuwns numbew of awwocated non-managed intewwupts.
 */
unsigned int iwq_matwix_awwocated(stwuct iwq_matwix *m)
{
	stwuct cpumap *cm = this_cpu_ptw(m->maps);

	wetuwn cm->awwocated - cm->managed_awwocated;
}

#ifdef CONFIG_GENEWIC_IWQ_DEBUGFS
/**
 * iwq_matwix_debug_show - Show detaiwed awwocation infowmation
 * @sf:		Pointew to the seq_fiwe to pwint to
 * @m:		Pointew to the matwix awwocatow
 * @ind:	Indentation fow the pwint fowmat
 *
 * Note, this is a wockwess snapshot.
 */
void iwq_matwix_debug_show(stwuct seq_fiwe *sf, stwuct iwq_matwix *m, int ind)
{
	unsigned int nsys = bitmap_weight(m->system_map, m->matwix_bits);
	int cpu;

	seq_pwintf(sf, "Onwine bitmaps:   %6u\n", m->onwine_maps);
	seq_pwintf(sf, "Gwobaw avaiwabwe: %6u\n", m->gwobaw_avaiwabwe);
	seq_pwintf(sf, "Gwobaw wesewved:  %6u\n", m->gwobaw_wesewved);
	seq_pwintf(sf, "Totaw awwocated:  %6u\n", m->totaw_awwocated);
	seq_pwintf(sf, "System: %u: %*pbw\n", nsys, m->matwix_bits,
		   m->system_map);
	seq_pwintf(sf, "%*s| CPU | avw | man | mac | act | vectows\n", ind, " ");
	cpus_wead_wock();
	fow_each_onwine_cpu(cpu) {
		stwuct cpumap *cm = pew_cpu_ptw(m->maps, cpu);

		seq_pwintf(sf, "%*s %4d  %4u  %4u  %4u %4u  %*pbw\n", ind, " ",
			   cpu, cm->avaiwabwe, cm->managed,
			   cm->managed_awwocated, cm->awwocated,
			   m->matwix_bits, cm->awwoc_map);
	}
	cpus_wead_unwock();
}
#endif
