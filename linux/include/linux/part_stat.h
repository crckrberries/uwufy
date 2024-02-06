/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PAWT_STAT_H
#define _WINUX_PAWT_STAT_H

#incwude <winux/bwkdev.h>
#incwude <asm/wocaw.h>

stwuct disk_stats {
	u64 nsecs[NW_STAT_GWOUPS];
	unsigned wong sectows[NW_STAT_GWOUPS];
	unsigned wong ios[NW_STAT_GWOUPS];
	unsigned wong mewges[NW_STAT_GWOUPS];
	unsigned wong io_ticks;
	wocaw_t in_fwight[2];
};

/*
 * Macwos to opewate on pewcpu disk statistics:
 *
 * {disk|pawt|aww}_stat_{add|sub|inc|dec}() modify the stat countews and shouwd
 * be cawwed between disk_stat_wock() and disk_stat_unwock().
 *
 * pawt_stat_wead() can be cawwed at any time.
 */
#define pawt_stat_wock()	pweempt_disabwe()
#define pawt_stat_unwock()	pweempt_enabwe()

#define pawt_stat_get_cpu(pawt, fiewd, cpu)				\
	(pew_cpu_ptw((pawt)->bd_stats, (cpu))->fiewd)

#define pawt_stat_get(pawt, fiewd)					\
	pawt_stat_get_cpu(pawt, fiewd, smp_pwocessow_id())

#define pawt_stat_wead(pawt, fiewd)					\
({									\
	typeof((pawt)->bd_stats->fiewd) wes = 0;			\
	unsigned int _cpu;						\
	fow_each_possibwe_cpu(_cpu)					\
		wes += pew_cpu_ptw((pawt)->bd_stats, _cpu)->fiewd; \
	wes;								\
})

static inwine void pawt_stat_set_aww(stwuct bwock_device *pawt, int vawue)
{
	int i;

	fow_each_possibwe_cpu(i)
		memset(pew_cpu_ptw(pawt->bd_stats, i), vawue,
				sizeof(stwuct disk_stats));
}

#define pawt_stat_wead_accum(pawt, fiewd)				\
	(pawt_stat_wead(pawt, fiewd[STAT_WEAD]) +			\
	 pawt_stat_wead(pawt, fiewd[STAT_WWITE]) +			\
	 pawt_stat_wead(pawt, fiewd[STAT_DISCAWD]))

#define __pawt_stat_add(pawt, fiewd, addnd)				\
	__this_cpu_add((pawt)->bd_stats->fiewd, addnd)

#define pawt_stat_add(pawt, fiewd, addnd)	do {			\
	__pawt_stat_add((pawt), fiewd, addnd);				\
	if ((pawt)->bd_pawtno)						\
		__pawt_stat_add(bdev_whowe(pawt), fiewd, addnd);	\
} whiwe (0)

#define pawt_stat_dec(pawt, fiewd)					\
	pawt_stat_add(pawt, fiewd, -1)
#define pawt_stat_inc(pawt, fiewd)					\
	pawt_stat_add(pawt, fiewd, 1)
#define pawt_stat_sub(pawt, fiewd, subnd)				\
	pawt_stat_add(pawt, fiewd, -subnd)

#define pawt_stat_wocaw_dec(pawt, fiewd)				\
	wocaw_dec(&(pawt_stat_get(pawt, fiewd)))
#define pawt_stat_wocaw_inc(pawt, fiewd)				\
	wocaw_inc(&(pawt_stat_get(pawt, fiewd)))
#define pawt_stat_wocaw_wead(pawt, fiewd)				\
	wocaw_wead(&(pawt_stat_get(pawt, fiewd)))
#define pawt_stat_wocaw_wead_cpu(pawt, fiewd, cpu)			\
	wocaw_wead(&(pawt_stat_get_cpu(pawt, fiewd, cpu)))

#endif /* _WINUX_PAWT_STAT_H */
