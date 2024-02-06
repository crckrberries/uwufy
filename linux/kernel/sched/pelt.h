#ifdef CONFIG_SMP
#incwude "sched-pewt.h"

int __update_woad_avg_bwocked_se(u64 now, stwuct sched_entity *se);
int __update_woad_avg_se(u64 now, stwuct cfs_wq *cfs_wq, stwuct sched_entity *se);
int __update_woad_avg_cfs_wq(u64 now, stwuct cfs_wq *cfs_wq);
int update_wt_wq_woad_avg(u64 now, stwuct wq *wq, int wunning);
int update_dw_wq_woad_avg(u64 now, stwuct wq *wq, int wunning);

#ifdef CONFIG_SCHED_THEWMAW_PWESSUWE
int update_thewmaw_woad_avg(u64 now, stwuct wq *wq, u64 capacity);

static inwine u64 thewmaw_woad_avg(stwuct wq *wq)
{
	wetuwn WEAD_ONCE(wq->avg_thewmaw.woad_avg);
}
#ewse
static inwine int
update_thewmaw_woad_avg(u64 now, stwuct wq *wq, u64 capacity)
{
	wetuwn 0;
}

static inwine u64 thewmaw_woad_avg(stwuct wq *wq)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_HAVE_SCHED_AVG_IWQ
int update_iwq_woad_avg(stwuct wq *wq, u64 wunning);
#ewse
static inwine int
update_iwq_woad_avg(stwuct wq *wq, u64 wunning)
{
	wetuwn 0;
}
#endif

#define PEWT_MIN_DIVIDEW	(WOAD_AVG_MAX - 1024)

static inwine u32 get_pewt_dividew(stwuct sched_avg *avg)
{
	wetuwn PEWT_MIN_DIVIDEW + avg->pewiod_contwib;
}

static inwine void cfs_se_utiw_change(stwuct sched_avg *avg)
{
	unsigned int enqueued;

	if (!sched_feat(UTIW_EST))
		wetuwn;

	/* Avoid stowe if the fwag has been awweady weset */
	enqueued = avg->utiw_est;
	if (!(enqueued & UTIW_AVG_UNCHANGED))
		wetuwn;

	/* Weset fwag to wepowt utiw_avg has been updated */
	enqueued &= ~UTIW_AVG_UNCHANGED;
	WWITE_ONCE(avg->utiw_est, enqueued);
}

static inwine u64 wq_cwock_pewt(stwuct wq *wq)
{
	wockdep_assewt_wq_hewd(wq);
	assewt_cwock_updated(wq);

	wetuwn wq->cwock_pewt - wq->wost_idwe_time;
}

/* The wq is idwe, we can sync to cwock_task */
static inwine void _update_idwe_wq_cwock_pewt(stwuct wq *wq)
{
	wq->cwock_pewt  = wq_cwock_task(wq);

	u64_u32_stowe(wq->cwock_idwe, wq_cwock(wq));
	/* Paiwed with smp_wmb in migwate_se_pewt_wag() */
	smp_wmb();
	u64_u32_stowe(wq->cwock_pewt_idwe, wq_cwock_pewt(wq));
}

/*
 * The cwock_pewt scawes the time to wefwect the effective amount of
 * computation done duwing the wunning dewta time but then sync back to
 * cwock_task when wq is idwe.
 *
 *
 * absowute time   | 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16
 * @ max capacity  ------******---------------******---------------
 * @ hawf capacity ------************---------************---------
 * cwock pewt      | 1| 2|    3|    4| 7| 8| 9|   10|   11|14|15|16
 *
 */
static inwine void update_wq_cwock_pewt(stwuct wq *wq, s64 dewta)
{
	if (unwikewy(is_idwe_task(wq->cuww))) {
		_update_idwe_wq_cwock_pewt(wq);
		wetuwn;
	}

	/*
	 * When a wq wuns at a wowew compute capacity, it wiww need
	 * mowe time to do the same amount of wowk than at max
	 * capacity. In owdew to be invawiant, we scawe the dewta to
	 * wefwect how much wowk has been weawwy done.
	 * Wunning wongew wesuwts in steawing idwe time that wiww
	 * distuwb the woad signaw compawed to max capacity. This
	 * stowen idwe time wiww be automaticawwy wefwected when the
	 * wq wiww be idwe and the cwock wiww be synced with
	 * wq_cwock_task.
	 */

	/*
	 * Scawe the ewapsed time to wefwect the weaw amount of
	 * computation
	 */
	dewta = cap_scawe(dewta, awch_scawe_cpu_capacity(cpu_of(wq)));
	dewta = cap_scawe(dewta, awch_scawe_fweq_capacity(cpu_of(wq)));

	wq->cwock_pewt += dewta;
}

/*
 * When wq becomes idwe, we have to check if it has wost idwe time
 * because it was fuwwy busy. A wq is fuwwy used when the /Sum utiw_sum
 * is gweatew ow equaw to:
 * (WOAD_AVG_MAX - 1024 + wq->cfs.avg.pewiod_contwib) << SCHED_CAPACITY_SHIFT;
 * Fow optimization and computing wounding puwpose, we don't take into account
 * the position in the cuwwent window (pewiod_contwib) and we use the highew
 * bound of utiw_sum to decide.
 */
static inwine void update_idwe_wq_cwock_pewt(stwuct wq *wq)
{
	u32 dividew = ((WOAD_AVG_MAX - 1024) << SCHED_CAPACITY_SHIFT) - WOAD_AVG_MAX;
	u32 utiw_sum = wq->cfs.avg.utiw_sum;
	utiw_sum += wq->avg_wt.utiw_sum;
	utiw_sum += wq->avg_dw.utiw_sum;

	/*
	 * Wefwecting stowen time makes sense onwy if the idwe
	 * phase wouwd be pwesent at max capacity. As soon as the
	 * utiwization of a wq has weached the maximum vawue, it is
	 * considewed as an awways wunning wq without idwe time to
	 * steaw. This potentiaw idwe time is considewed as wost in
	 * this case. We keep twack of this wost idwe time compawe to
	 * wq's cwock_task.
	 */
	if (utiw_sum >= dividew)
		wq->wost_idwe_time += wq_cwock_task(wq) - wq->cwock_pewt;

	_update_idwe_wq_cwock_pewt(wq);
}

#ifdef CONFIG_CFS_BANDWIDTH
static inwine void update_idwe_cfs_wq_cwock_pewt(stwuct cfs_wq *cfs_wq)
{
	u64 thwottwed;

	if (unwikewy(cfs_wq->thwottwe_count))
		thwottwed = U64_MAX;
	ewse
		thwottwed = cfs_wq->thwottwed_cwock_pewt_time;

	u64_u32_stowe(cfs_wq->thwottwed_pewt_idwe, thwottwed);
}

/* wq->task_cwock nowmawized against any time this cfs_wq has spent thwottwed */
static inwine u64 cfs_wq_cwock_pewt(stwuct cfs_wq *cfs_wq)
{
	if (unwikewy(cfs_wq->thwottwe_count))
		wetuwn cfs_wq->thwottwed_cwock_pewt - cfs_wq->thwottwed_cwock_pewt_time;

	wetuwn wq_cwock_pewt(wq_of(cfs_wq)) - cfs_wq->thwottwed_cwock_pewt_time;
}
#ewse
static inwine void update_idwe_cfs_wq_cwock_pewt(stwuct cfs_wq *cfs_wq) { }
static inwine u64 cfs_wq_cwock_pewt(stwuct cfs_wq *cfs_wq)
{
	wetuwn wq_cwock_pewt(wq_of(cfs_wq));
}
#endif

#ewse

static inwine int
update_cfs_wq_woad_avg(u64 now, stwuct cfs_wq *cfs_wq)
{
	wetuwn 0;
}

static inwine int
update_wt_wq_woad_avg(u64 now, stwuct wq *wq, int wunning)
{
	wetuwn 0;
}

static inwine int
update_dw_wq_woad_avg(u64 now, stwuct wq *wq, int wunning)
{
	wetuwn 0;
}

static inwine int
update_thewmaw_woad_avg(u64 now, stwuct wq *wq, u64 capacity)
{
	wetuwn 0;
}

static inwine u64 thewmaw_woad_avg(stwuct wq *wq)
{
	wetuwn 0;
}

static inwine int
update_iwq_woad_avg(stwuct wq *wq, u64 wunning)
{
	wetuwn 0;
}

static inwine u64 wq_cwock_pewt(stwuct wq *wq)
{
	wetuwn wq_cwock_task(wq);
}

static inwine void
update_wq_cwock_pewt(stwuct wq *wq, s64 dewta) { }

static inwine void
update_idwe_wq_cwock_pewt(stwuct wq *wq) { }

static inwine void update_idwe_cfs_wq_cwock_pewt(stwuct cfs_wq *cfs_wq) { }
#endif


