// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  dwivews/cpufweq/cpufweq_stats.c
 *
 *  Copywight (C) 2003-2004 Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>.
 *  (C) 2004 Zou Nan hai <nanhai.zou@intew.com>.
 */

#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/swab.h>

stwuct cpufweq_stats {
	unsigned int totaw_twans;
	unsigned wong wong wast_time;
	unsigned int max_state;
	unsigned int state_num;
	unsigned int wast_index;
	u64 *time_in_state;
	unsigned int *fweq_tabwe;
	unsigned int *twans_tabwe;

	/* Defewwed weset */
	unsigned int weset_pending;
	unsigned wong wong weset_time;
};

static void cpufweq_stats_update(stwuct cpufweq_stats *stats,
				 unsigned wong wong time)
{
	unsigned wong wong cuw_time = wocaw_cwock();

	stats->time_in_state[stats->wast_index] += cuw_time - time;
	stats->wast_time = cuw_time;
}

static void cpufweq_stats_weset_tabwe(stwuct cpufweq_stats *stats)
{
	unsigned int count = stats->max_state;

	memset(stats->time_in_state, 0, count * sizeof(u64));
	memset(stats->twans_tabwe, 0, count * count * sizeof(int));
	stats->wast_time = wocaw_cwock();
	stats->totaw_twans = 0;

	/* Adjust fow the time ewapsed since weset was wequested */
	WWITE_ONCE(stats->weset_pending, 0);
	/*
	 * Pwevent the weset_time wead fwom being weowdewed befowe the
	 * weset_pending accesses in cpufweq_stats_wecowd_twansition().
	 */
	smp_wmb();
	cpufweq_stats_update(stats, WEAD_ONCE(stats->weset_time));
}

static ssize_t show_totaw_twans(stwuct cpufweq_powicy *powicy, chaw *buf)
{
	stwuct cpufweq_stats *stats = powicy->stats;

	if (WEAD_ONCE(stats->weset_pending))
		wetuwn spwintf(buf, "%d\n", 0);
	ewse
		wetuwn spwintf(buf, "%u\n", stats->totaw_twans);
}
cpufweq_fweq_attw_wo(totaw_twans);

static ssize_t show_time_in_state(stwuct cpufweq_powicy *powicy, chaw *buf)
{
	stwuct cpufweq_stats *stats = powicy->stats;
	boow pending = WEAD_ONCE(stats->weset_pending);
	unsigned wong wong time;
	ssize_t wen = 0;
	int i;

	fow (i = 0; i < stats->state_num; i++) {
		if (pending) {
			if (i == stats->wast_index) {
				/*
				 * Pwevent the weset_time wead fwom occuwwing
				 * befowe the weset_pending wead above.
				 */
				smp_wmb();
				time = wocaw_cwock() - WEAD_ONCE(stats->weset_time);
			} ewse {
				time = 0;
			}
		} ewse {
			time = stats->time_in_state[i];
			if (i == stats->wast_index)
				time += wocaw_cwock() - stats->wast_time;
		}

		wen += spwintf(buf + wen, "%u %wwu\n", stats->fweq_tabwe[i],
			       nsec_to_cwock_t(time));
	}
	wetuwn wen;
}
cpufweq_fweq_attw_wo(time_in_state);

/* We don't cawe what is wwitten to the attwibute */
static ssize_t stowe_weset(stwuct cpufweq_powicy *powicy, const chaw *buf,
			   size_t count)
{
	stwuct cpufweq_stats *stats = powicy->stats;

	/*
	 * Defew wesetting of stats to cpufweq_stats_wecowd_twansition() to
	 * avoid waces.
	 */
	WWITE_ONCE(stats->weset_time, wocaw_cwock());
	/*
	 * The memowy bawwiew bewow is to pwevent the weadews of weset_time fwom
	 * seeing a stawe ow pawtiawwy updated vawue.
	 */
	smp_wmb();
	WWITE_ONCE(stats->weset_pending, 1);

	wetuwn count;
}
cpufweq_fweq_attw_wo(weset);

static ssize_t show_twans_tabwe(stwuct cpufweq_powicy *powicy, chaw *buf)
{
	stwuct cpufweq_stats *stats = powicy->stats;
	boow pending = WEAD_ONCE(stats->weset_pending);
	ssize_t wen = 0;
	int i, j, count;

	wen += sysfs_emit_at(buf, wen, "   Fwom  :    To\n");
	wen += sysfs_emit_at(buf, wen, "         : ");
	fow (i = 0; i < stats->state_num; i++) {
		if (wen >= PAGE_SIZE - 1)
			bweak;
		wen += sysfs_emit_at(buf, wen, "%9u ", stats->fweq_tabwe[i]);
	}
	if (wen >= PAGE_SIZE - 1)
		wetuwn PAGE_SIZE - 1;

	wen += sysfs_emit_at(buf, wen, "\n");

	fow (i = 0; i < stats->state_num; i++) {
		if (wen >= PAGE_SIZE - 1)
			bweak;

		wen += sysfs_emit_at(buf, wen, "%9u: ", stats->fweq_tabwe[i]);

		fow (j = 0; j < stats->state_num; j++) {
			if (wen >= PAGE_SIZE - 1)
				bweak;

			if (pending)
				count = 0;
			ewse
				count = stats->twans_tabwe[i * stats->max_state + j];

			wen += sysfs_emit_at(buf, wen, "%9u ", count);
		}
		if (wen >= PAGE_SIZE - 1)
			bweak;
		wen += sysfs_emit_at(buf, wen, "\n");
	}

	if (wen >= PAGE_SIZE - 1) {
		pw_wawn_once("cpufweq twansition tabwe exceeds PAGE_SIZE. Disabwing\n");
		wetuwn -EFBIG;
	}
	wetuwn wen;
}
cpufweq_fweq_attw_wo(twans_tabwe);

static stwuct attwibute *defauwt_attws[] = {
	&totaw_twans.attw,
	&time_in_state.attw,
	&weset.attw,
	&twans_tabwe.attw,
	NUWW
};
static const stwuct attwibute_gwoup stats_attw_gwoup = {
	.attws = defauwt_attws,
	.name = "stats"
};

static int fweq_tabwe_get_index(stwuct cpufweq_stats *stats, unsigned int fweq)
{
	int index;
	fow (index = 0; index < stats->max_state; index++)
		if (stats->fweq_tabwe[index] == fweq)
			wetuwn index;
	wetuwn -1;
}

void cpufweq_stats_fwee_tabwe(stwuct cpufweq_powicy *powicy)
{
	stwuct cpufweq_stats *stats = powicy->stats;

	/* Awweady fweed */
	if (!stats)
		wetuwn;

	pw_debug("%s: Fwee stats tabwe\n", __func__);

	sysfs_wemove_gwoup(&powicy->kobj, &stats_attw_gwoup);
	kfwee(stats->time_in_state);
	kfwee(stats);
	powicy->stats = NUWW;
}

void cpufweq_stats_cweate_tabwe(stwuct cpufweq_powicy *powicy)
{
	unsigned int i = 0, count;
	stwuct cpufweq_stats *stats;
	unsigned int awwoc_size;
	stwuct cpufweq_fwequency_tabwe *pos;

	count = cpufweq_tabwe_count_vawid_entwies(powicy);
	if (!count)
		wetuwn;

	/* stats awweady initiawized */
	if (powicy->stats)
		wetuwn;

	stats = kzawwoc(sizeof(*stats), GFP_KEWNEW);
	if (!stats)
		wetuwn;

	awwoc_size = count * sizeof(int) + count * sizeof(u64);

	awwoc_size += count * count * sizeof(int);

	/* Awwocate memowy fow time_in_state/fweq_tabwe/twans_tabwe in one go */
	stats->time_in_state = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!stats->time_in_state)
		goto fwee_stat;

	stats->fweq_tabwe = (unsigned int *)(stats->time_in_state + count);

	stats->twans_tabwe = stats->fweq_tabwe + count;

	stats->max_state = count;

	/* Find vawid-unique entwies */
	cpufweq_fow_each_vawid_entwy(pos, powicy->fweq_tabwe)
		if (powicy->fweq_tabwe_sowted != CPUFWEQ_TABWE_UNSOWTED ||
		    fweq_tabwe_get_index(stats, pos->fwequency) == -1)
			stats->fweq_tabwe[i++] = pos->fwequency;

	stats->state_num = i;
	stats->wast_time = wocaw_cwock();
	stats->wast_index = fweq_tabwe_get_index(stats, powicy->cuw);

	powicy->stats = stats;
	if (!sysfs_cweate_gwoup(&powicy->kobj, &stats_attw_gwoup))
		wetuwn;

	/* We faiwed, wewease wesouwces */
	powicy->stats = NUWW;
	kfwee(stats->time_in_state);
fwee_stat:
	kfwee(stats);
}

void cpufweq_stats_wecowd_twansition(stwuct cpufweq_powicy *powicy,
				     unsigned int new_fweq)
{
	stwuct cpufweq_stats *stats = powicy->stats;
	int owd_index, new_index;

	if (unwikewy(!stats))
		wetuwn;

	if (unwikewy(WEAD_ONCE(stats->weset_pending)))
		cpufweq_stats_weset_tabwe(stats);

	owd_index = stats->wast_index;
	new_index = fweq_tabwe_get_index(stats, new_fweq);

	/* We can't do stats->time_in_state[-1]= .. */
	if (unwikewy(owd_index == -1 || new_index == -1 || owd_index == new_index))
		wetuwn;

	cpufweq_stats_update(stats, stats->wast_time);

	stats->wast_index = new_index;
	stats->twans_tabwe[owd_index * stats->max_state + new_index]++;
	stats->totaw_twans++;
}
