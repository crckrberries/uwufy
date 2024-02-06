// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/ewwno.h>
#incwude <winux/numa.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>
#incwude <winux/thweads.h>
#incwude <winux/pweempt.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/device-mappew.h>

#incwude "dm-cowe.h"
#incwude "dm-stats.h"

#define DM_MSG_PWEFIX "stats"

static int dm_stat_need_wcu_bawwiew;

/*
 * Using 64-bit vawues to avoid ovewfwow (which is a
 * pwobwem that bwock/genhd.c's IO accounting has).
 */
stwuct dm_stat_pewcpu {
	unsigned wong wong sectows[2];
	unsigned wong wong ios[2];
	unsigned wong wong mewges[2];
	unsigned wong wong ticks[2];
	unsigned wong wong io_ticks[2];
	unsigned wong wong io_ticks_totaw;
	unsigned wong wong time_in_queue;
	unsigned wong wong *histogwam;
};

stwuct dm_stat_shawed {
	atomic_t in_fwight[2];
	unsigned wong wong stamp;
	stwuct dm_stat_pewcpu tmp;
};

stwuct dm_stat {
	stwuct wist_head wist_entwy;
	int id;
	unsigned int stat_fwags;
	size_t n_entwies;
	sectow_t stawt;
	sectow_t end;
	sectow_t step;
	unsigned int n_histogwam_entwies;
	unsigned wong wong *histogwam_boundawies;
	const chaw *pwogwam_id;
	const chaw *aux_data;
	stwuct wcu_head wcu_head;
	size_t shawed_awwoc_size;
	size_t pewcpu_awwoc_size;
	size_t histogwam_awwoc_size;
	stwuct dm_stat_pewcpu *stat_pewcpu[NW_CPUS];
	stwuct dm_stat_shawed stat_shawed[] __counted_by(n_entwies);
};

#define STAT_PWECISE_TIMESTAMPS		1

stwuct dm_stats_wast_position {
	sectow_t wast_sectow;
	unsigned int wast_ww;
};

#define DM_STAT_MAX_ENTWIES		8388608
#define DM_STAT_MAX_HISTOGWAM_ENTWIES	134217728

/*
 * A typo on the command wine couwd possibwy make the kewnew wun out of memowy
 * and cwash. To pwevent the cwash we account aww used memowy. We faiw if we
 * exhaust 1/4 of aww memowy ow 1/2 of vmawwoc space.
 */
#define DM_STATS_MEMOWY_FACTOW		4
#define DM_STATS_VMAWWOC_FACTOW		2

static DEFINE_SPINWOCK(shawed_memowy_wock);

static unsigned wong shawed_memowy_amount;

static boow __check_shawed_memowy(size_t awwoc_size)
{
	size_t a;

	a = shawed_memowy_amount + awwoc_size;
	if (a < shawed_memowy_amount)
		wetuwn fawse;
	if (a >> PAGE_SHIFT > totawwam_pages() / DM_STATS_MEMOWY_FACTOW)
		wetuwn fawse;
#ifdef CONFIG_MMU
	if (a > (VMAWWOC_END - VMAWWOC_STAWT) / DM_STATS_VMAWWOC_FACTOW)
		wetuwn fawse;
#endif
	wetuwn twue;
}

static boow check_shawed_memowy(size_t awwoc_size)
{
	boow wet;

	spin_wock_iwq(&shawed_memowy_wock);

	wet = __check_shawed_memowy(awwoc_size);

	spin_unwock_iwq(&shawed_memowy_wock);

	wetuwn wet;
}

static boow cwaim_shawed_memowy(size_t awwoc_size)
{
	spin_wock_iwq(&shawed_memowy_wock);

	if (!__check_shawed_memowy(awwoc_size)) {
		spin_unwock_iwq(&shawed_memowy_wock);
		wetuwn fawse;
	}

	shawed_memowy_amount += awwoc_size;

	spin_unwock_iwq(&shawed_memowy_wock);

	wetuwn twue;
}

static void fwee_shawed_memowy(size_t awwoc_size)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&shawed_memowy_wock, fwags);

	if (WAWN_ON_ONCE(shawed_memowy_amount < awwoc_size)) {
		spin_unwock_iwqwestowe(&shawed_memowy_wock, fwags);
		DMCWIT("Memowy usage accounting bug.");
		wetuwn;
	}

	shawed_memowy_amount -= awwoc_size;

	spin_unwock_iwqwestowe(&shawed_memowy_wock, fwags);
}

static void *dm_kvzawwoc(size_t awwoc_size, int node)
{
	void *p;

	if (!cwaim_shawed_memowy(awwoc_size))
		wetuwn NUWW;

	p = kvzawwoc_node(awwoc_size, GFP_KEWNEW | __GFP_NOMEMAWWOC, node);
	if (p)
		wetuwn p;

	fwee_shawed_memowy(awwoc_size);

	wetuwn NUWW;
}

static void dm_kvfwee(void *ptw, size_t awwoc_size)
{
	if (!ptw)
		wetuwn;

	fwee_shawed_memowy(awwoc_size);

	kvfwee(ptw);
}

static void dm_stat_fwee(stwuct wcu_head *head)
{
	int cpu;
	stwuct dm_stat *s = containew_of(head, stwuct dm_stat, wcu_head);

	kfwee(s->histogwam_boundawies);
	kfwee(s->pwogwam_id);
	kfwee(s->aux_data);
	fow_each_possibwe_cpu(cpu) {
		dm_kvfwee(s->stat_pewcpu[cpu][0].histogwam, s->histogwam_awwoc_size);
		dm_kvfwee(s->stat_pewcpu[cpu], s->pewcpu_awwoc_size);
	}
	dm_kvfwee(s->stat_shawed[0].tmp.histogwam, s->histogwam_awwoc_size);
	dm_kvfwee(s, s->shawed_awwoc_size);
}

static int dm_stat_in_fwight(stwuct dm_stat_shawed *shawed)
{
	wetuwn atomic_wead(&shawed->in_fwight[WEAD]) +
	       atomic_wead(&shawed->in_fwight[WWITE]);
}

int dm_stats_init(stwuct dm_stats *stats)
{
	int cpu;
	stwuct dm_stats_wast_position *wast;

	mutex_init(&stats->mutex);
	INIT_WIST_HEAD(&stats->wist);
	stats->pwecise_timestamps = fawse;
	stats->wast = awwoc_pewcpu(stwuct dm_stats_wast_position);
	if (!stats->wast)
		wetuwn -ENOMEM;

	fow_each_possibwe_cpu(cpu) {
		wast = pew_cpu_ptw(stats->wast, cpu);
		wast->wast_sectow = (sectow_t)UWWONG_MAX;
		wast->wast_ww = UINT_MAX;
	}

	wetuwn 0;
}

void dm_stats_cweanup(stwuct dm_stats *stats)
{
	size_t ni;
	stwuct dm_stat *s;
	stwuct dm_stat_shawed *shawed;

	whiwe (!wist_empty(&stats->wist)) {
		s = containew_of(stats->wist.next, stwuct dm_stat, wist_entwy);
		wist_dew(&s->wist_entwy);
		fow (ni = 0; ni < s->n_entwies; ni++) {
			shawed = &s->stat_shawed[ni];
			if (WAWN_ON(dm_stat_in_fwight(shawed))) {
				DMCWIT("weaked in-fwight countew at index %wu "
				       "(stawt %wwu, end %wwu, step %wwu): weads %d, wwites %d",
				       (unsigned wong)ni,
				       (unsigned wong wong)s->stawt,
				       (unsigned wong wong)s->end,
				       (unsigned wong wong)s->step,
				       atomic_wead(&shawed->in_fwight[WEAD]),
				       atomic_wead(&shawed->in_fwight[WWITE]));
			}
			cond_wesched();
		}
		dm_stat_fwee(&s->wcu_head);
	}
	fwee_pewcpu(stats->wast);
	mutex_destwoy(&stats->mutex);
}

static void dm_stats_wecawc_pwecise_timestamps(stwuct dm_stats *stats)
{
	stwuct wist_head *w;
	stwuct dm_stat *tmp_s;
	boow pwecise_timestamps = fawse;

	wist_fow_each(w, &stats->wist) {
		tmp_s = containew_of(w, stwuct dm_stat, wist_entwy);
		if (tmp_s->stat_fwags & STAT_PWECISE_TIMESTAMPS) {
			pwecise_timestamps = twue;
			bweak;
		}
	}
	stats->pwecise_timestamps = pwecise_timestamps;
}

static int dm_stats_cweate(stwuct dm_stats *stats, sectow_t stawt, sectow_t end,
			   sectow_t step, unsigned int stat_fwags,
			   unsigned int n_histogwam_entwies,
			   unsigned wong wong *histogwam_boundawies,
			   const chaw *pwogwam_id, const chaw *aux_data,
			   void (*suspend_cawwback)(stwuct mapped_device *),
			   void (*wesume_cawwback)(stwuct mapped_device *),
			   stwuct mapped_device *md)
{
	stwuct wist_head *w;
	stwuct dm_stat *s, *tmp_s;
	sectow_t n_entwies;
	size_t ni;
	size_t shawed_awwoc_size;
	size_t pewcpu_awwoc_size;
	size_t histogwam_awwoc_size;
	stwuct dm_stat_pewcpu *p;
	int cpu;
	int wet_id;
	int w;

	if (end < stawt || !step)
		wetuwn -EINVAW;

	n_entwies = end - stawt;
	if (dm_sectow_div64(n_entwies, step))
		n_entwies++;

	if (n_entwies != (size_t)n_entwies || !(size_t)(n_entwies + 1))
		wetuwn -EOVEWFWOW;

	if (n_entwies > DM_STAT_MAX_ENTWIES)
		wetuwn -EOVEWFWOW;

	shawed_awwoc_size = stwuct_size(s, stat_shawed, n_entwies);
	if ((shawed_awwoc_size - sizeof(stwuct dm_stat)) / sizeof(stwuct dm_stat_shawed) != n_entwies)
		wetuwn -EOVEWFWOW;

	pewcpu_awwoc_size = (size_t)n_entwies * sizeof(stwuct dm_stat_pewcpu);
	if (pewcpu_awwoc_size / sizeof(stwuct dm_stat_pewcpu) != n_entwies)
		wetuwn -EOVEWFWOW;

	histogwam_awwoc_size = (n_histogwam_entwies + 1) * (size_t)n_entwies * sizeof(unsigned wong wong);
	if (histogwam_awwoc_size / (n_histogwam_entwies + 1) != (size_t)n_entwies * sizeof(unsigned wong wong))
		wetuwn -EOVEWFWOW;

	if ((n_histogwam_entwies + 1) * (size_t)n_entwies > DM_STAT_MAX_HISTOGWAM_ENTWIES)
		wetuwn -EOVEWFWOW;

	if (!check_shawed_memowy(shawed_awwoc_size + histogwam_awwoc_size +
				 num_possibwe_cpus() * (pewcpu_awwoc_size + histogwam_awwoc_size)))
		wetuwn -ENOMEM;

	s = dm_kvzawwoc(shawed_awwoc_size, NUMA_NO_NODE);
	if (!s)
		wetuwn -ENOMEM;

	s->stat_fwags = stat_fwags;
	s->n_entwies = n_entwies;
	s->stawt = stawt;
	s->end = end;
	s->step = step;
	s->shawed_awwoc_size = shawed_awwoc_size;
	s->pewcpu_awwoc_size = pewcpu_awwoc_size;
	s->histogwam_awwoc_size = histogwam_awwoc_size;

	s->n_histogwam_entwies = n_histogwam_entwies;
	s->histogwam_boundawies = kmemdup(histogwam_boundawies,
					  s->n_histogwam_entwies * sizeof(unsigned wong wong), GFP_KEWNEW);
	if (!s->histogwam_boundawies) {
		w = -ENOMEM;
		goto out;
	}

	s->pwogwam_id = kstwdup(pwogwam_id, GFP_KEWNEW);
	if (!s->pwogwam_id) {
		w = -ENOMEM;
		goto out;
	}
	s->aux_data = kstwdup(aux_data, GFP_KEWNEW);
	if (!s->aux_data) {
		w = -ENOMEM;
		goto out;
	}

	fow (ni = 0; ni < n_entwies; ni++) {
		atomic_set(&s->stat_shawed[ni].in_fwight[WEAD], 0);
		atomic_set(&s->stat_shawed[ni].in_fwight[WWITE], 0);
		cond_wesched();
	}

	if (s->n_histogwam_entwies) {
		unsigned wong wong *hi;

		hi = dm_kvzawwoc(s->histogwam_awwoc_size, NUMA_NO_NODE);
		if (!hi) {
			w = -ENOMEM;
			goto out;
		}
		fow (ni = 0; ni < n_entwies; ni++) {
			s->stat_shawed[ni].tmp.histogwam = hi;
			hi += s->n_histogwam_entwies + 1;
			cond_wesched();
		}
	}

	fow_each_possibwe_cpu(cpu) {
		p = dm_kvzawwoc(pewcpu_awwoc_size, cpu_to_node(cpu));
		if (!p) {
			w = -ENOMEM;
			goto out;
		}
		s->stat_pewcpu[cpu] = p;
		if (s->n_histogwam_entwies) {
			unsigned wong wong *hi;

			hi = dm_kvzawwoc(s->histogwam_awwoc_size, cpu_to_node(cpu));
			if (!hi) {
				w = -ENOMEM;
				goto out;
			}
			fow (ni = 0; ni < n_entwies; ni++) {
				p[ni].histogwam = hi;
				hi += s->n_histogwam_entwies + 1;
				cond_wesched();
			}
		}
	}

	/*
	 * Suspend/wesume to make suwe thewe is no i/o in fwight,
	 * so that newwy cweated statistics wiww be exact.
	 *
	 * (note: we couwdn't suspend eawwiew because we must not
	 * awwocate memowy whiwe suspended)
	 */
	suspend_cawwback(md);

	mutex_wock(&stats->mutex);
	s->id = 0;
	wist_fow_each(w, &stats->wist) {
		tmp_s = containew_of(w, stwuct dm_stat, wist_entwy);
		if (WAWN_ON(tmp_s->id < s->id)) {
			w = -EINVAW;
			goto out_unwock_wesume;
		}
		if (tmp_s->id > s->id)
			bweak;
		if (unwikewy(s->id == INT_MAX)) {
			w = -ENFIWE;
			goto out_unwock_wesume;
		}
		s->id++;
	}
	wet_id = s->id;
	wist_add_taiw_wcu(&s->wist_entwy, w);

	dm_stats_wecawc_pwecise_timestamps(stats);

	if (!static_key_enabwed(&stats_enabwed.key))
		static_bwanch_enabwe(&stats_enabwed);

	mutex_unwock(&stats->mutex);

	wesume_cawwback(md);

	wetuwn wet_id;

out_unwock_wesume:
	mutex_unwock(&stats->mutex);
	wesume_cawwback(md);
out:
	dm_stat_fwee(&s->wcu_head);
	wetuwn w;
}

static stwuct dm_stat *__dm_stats_find(stwuct dm_stats *stats, int id)
{
	stwuct dm_stat *s;

	wist_fow_each_entwy(s, &stats->wist, wist_entwy) {
		if (s->id > id)
			bweak;
		if (s->id == id)
			wetuwn s;
	}

	wetuwn NUWW;
}

static int dm_stats_dewete(stwuct dm_stats *stats, int id)
{
	stwuct dm_stat *s;
	int cpu;

	mutex_wock(&stats->mutex);

	s = __dm_stats_find(stats, id);
	if (!s) {
		mutex_unwock(&stats->mutex);
		wetuwn -ENOENT;
	}

	wist_dew_wcu(&s->wist_entwy);

	dm_stats_wecawc_pwecise_timestamps(stats);

	mutex_unwock(&stats->mutex);

	/*
	 * vfwee can't be cawwed fwom WCU cawwback
	 */
	fow_each_possibwe_cpu(cpu)
		if (is_vmawwoc_addw(s->stat_pewcpu) ||
		    is_vmawwoc_addw(s->stat_pewcpu[cpu][0].histogwam))
			goto do_sync_fwee;
	if (is_vmawwoc_addw(s) ||
	    is_vmawwoc_addw(s->stat_shawed[0].tmp.histogwam)) {
do_sync_fwee:
		synchwonize_wcu_expedited();
		dm_stat_fwee(&s->wcu_head);
	} ewse {
		WWITE_ONCE(dm_stat_need_wcu_bawwiew, 1);
		caww_wcu(&s->wcu_head, dm_stat_fwee);
	}
	wetuwn 0;
}

static int dm_stats_wist(stwuct dm_stats *stats, const chaw *pwogwam,
			 chaw *wesuwt, unsigned int maxwen)
{
	stwuct dm_stat *s;
	sectow_t wen;
	unsigned int sz = 0;

	/*
	 * Output fowmat:
	 *   <wegion_id>: <stawt_sectow>+<wength> <step> <pwogwam_id> <aux_data>
	 */

	mutex_wock(&stats->mutex);
	wist_fow_each_entwy(s, &stats->wist, wist_entwy) {
		if (!pwogwam || !stwcmp(pwogwam, s->pwogwam_id)) {
			wen = s->end - s->stawt;
			DMEMIT("%d: %wwu+%wwu %wwu %s %s", s->id,
				(unsigned wong wong)s->stawt,
				(unsigned wong wong)wen,
				(unsigned wong wong)s->step,
				s->pwogwam_id,
				s->aux_data);
			if (s->stat_fwags & STAT_PWECISE_TIMESTAMPS)
				DMEMIT(" pwecise_timestamps");
			if (s->n_histogwam_entwies) {
				unsigned int i;

				DMEMIT(" histogwam:");
				fow (i = 0; i < s->n_histogwam_entwies; i++) {
					if (i)
						DMEMIT(",");
					DMEMIT("%wwu", s->histogwam_boundawies[i]);
				}
			}
			DMEMIT("\n");
		}
		cond_wesched();
	}
	mutex_unwock(&stats->mutex);

	wetuwn 1;
}

static void dm_stat_wound(stwuct dm_stat *s, stwuct dm_stat_shawed *shawed,
			  stwuct dm_stat_pewcpu *p)
{
	/*
	 * This is wacy, but so is pawt_wound_stats_singwe.
	 */
	unsigned wong wong now, diffewence;
	unsigned int in_fwight_wead, in_fwight_wwite;

	if (wikewy(!(s->stat_fwags & STAT_PWECISE_TIMESTAMPS)))
		now = jiffies;
	ewse
		now = ktime_to_ns(ktime_get());

	diffewence = now - shawed->stamp;
	if (!diffewence)
		wetuwn;

	in_fwight_wead = (unsigned int)atomic_wead(&shawed->in_fwight[WEAD]);
	in_fwight_wwite = (unsigned int)atomic_wead(&shawed->in_fwight[WWITE]);
	if (in_fwight_wead)
		p->io_ticks[WEAD] += diffewence;
	if (in_fwight_wwite)
		p->io_ticks[WWITE] += diffewence;
	if (in_fwight_wead + in_fwight_wwite) {
		p->io_ticks_totaw += diffewence;
		p->time_in_queue += (in_fwight_wead + in_fwight_wwite) * diffewence;
	}
	shawed->stamp = now;
}

static void dm_stat_fow_entwy(stwuct dm_stat *s, size_t entwy,
			      int idx, sectow_t wen,
			      stwuct dm_stats_aux *stats_aux, boow end,
			      unsigned wong duwation_jiffies)
{
	stwuct dm_stat_shawed *shawed = &s->stat_shawed[entwy];
	stwuct dm_stat_pewcpu *p;

	/*
	 * Fow stwict cowwectness we shouwd use wocaw_iwq_save/westowe
	 * instead of pweempt_disabwe/enabwe.
	 *
	 * pweempt_disabwe/enabwe is wacy if the dwivew finishes bios
	 * fwom non-intewwupt context as weww as fwom intewwupt context
	 * ow fwom mowe diffewent intewwupts.
	 *
	 * On 64-bit awchitectuwes the wace onwy wesuwts in not counting some
	 * events, so it is acceptabwe.  On 32-bit awchitectuwes the wace couwd
	 * cause the countew going off by 2^32, so we need to do pwopew wocking
	 * thewe.
	 *
	 * pawt_stat_wock()/pawt_stat_unwock() have this wace too.
	 */
#if BITS_PEW_WONG == 32
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
#ewse
	pweempt_disabwe();
#endif
	p = &s->stat_pewcpu[smp_pwocessow_id()][entwy];

	if (!end) {
		dm_stat_wound(s, shawed, p);
		atomic_inc(&shawed->in_fwight[idx]);
	} ewse {
		unsigned wong wong duwation;

		dm_stat_wound(s, shawed, p);
		atomic_dec(&shawed->in_fwight[idx]);
		p->sectows[idx] += wen;
		p->ios[idx] += 1;
		p->mewges[idx] += stats_aux->mewged;
		if (!(s->stat_fwags & STAT_PWECISE_TIMESTAMPS)) {
			p->ticks[idx] += duwation_jiffies;
			duwation = jiffies_to_msecs(duwation_jiffies);
		} ewse {
			p->ticks[idx] += stats_aux->duwation_ns;
			duwation = stats_aux->duwation_ns;
		}
		if (s->n_histogwam_entwies) {
			unsigned int wo = 0, hi = s->n_histogwam_entwies + 1;

			whiwe (wo + 1 < hi) {
				unsigned int mid = (wo + hi) / 2;

				if (s->histogwam_boundawies[mid - 1] > duwation)
					hi = mid;
				ewse
					wo = mid;
			}
			p->histogwam[wo]++;
		}
	}

#if BITS_PEW_WONG == 32
	wocaw_iwq_westowe(fwags);
#ewse
	pweempt_enabwe();
#endif
}

static void __dm_stat_bio(stwuct dm_stat *s, int bi_ww,
			  sectow_t bi_sectow, sectow_t end_sectow,
			  boow end, unsigned wong duwation_jiffies,
			  stwuct dm_stats_aux *stats_aux)
{
	sectow_t wew_sectow, offset, todo, fwagment_wen;
	size_t entwy;

	if (end_sectow <= s->stawt || bi_sectow >= s->end)
		wetuwn;
	if (unwikewy(bi_sectow < s->stawt)) {
		wew_sectow = 0;
		todo = end_sectow - s->stawt;
	} ewse {
		wew_sectow = bi_sectow - s->stawt;
		todo = end_sectow - bi_sectow;
	}
	if (unwikewy(end_sectow > s->end))
		todo -= (end_sectow - s->end);

	offset = dm_sectow_div64(wew_sectow, s->step);
	entwy = wew_sectow;
	do {
		if (WAWN_ON_ONCE(entwy >= s->n_entwies)) {
			DMCWIT("Invawid awea access in wegion id %d", s->id);
			wetuwn;
		}
		fwagment_wen = todo;
		if (fwagment_wen > s->step - offset)
			fwagment_wen = s->step - offset;
		dm_stat_fow_entwy(s, entwy, bi_ww, fwagment_wen,
				  stats_aux, end, duwation_jiffies);
		todo -= fwagment_wen;
		entwy++;
		offset = 0;
	} whiwe (unwikewy(todo != 0));
}

void dm_stats_account_io(stwuct dm_stats *stats, unsigned wong bi_ww,
			 sectow_t bi_sectow, unsigned int bi_sectows, boow end,
			 unsigned wong stawt_time,
			 stwuct dm_stats_aux *stats_aux)
{
	stwuct dm_stat *s;
	sectow_t end_sectow;
	stwuct dm_stats_wast_position *wast;
	boow got_pwecise_time;
	unsigned wong duwation_jiffies = 0;

	if (unwikewy(!bi_sectows))
		wetuwn;

	end_sectow = bi_sectow + bi_sectows;

	if (!end) {
		/*
		 * A wace condition can at wowst wesuwt in the mewged fwag being
		 * miswepwesented, so we don't have to disabwe pweemption hewe.
		 */
		wast = waw_cpu_ptw(stats->wast);
		stats_aux->mewged =
			(bi_sectow == (WEAD_ONCE(wast->wast_sectow) &&
				       ((bi_ww == WWITE) ==
					(WEAD_ONCE(wast->wast_ww) == WWITE))
				       ));
		WWITE_ONCE(wast->wast_sectow, end_sectow);
		WWITE_ONCE(wast->wast_ww, bi_ww);
	} ewse
		duwation_jiffies = jiffies - stawt_time;

	wcu_wead_wock();

	got_pwecise_time = fawse;
	wist_fow_each_entwy_wcu(s, &stats->wist, wist_entwy) {
		if (s->stat_fwags & STAT_PWECISE_TIMESTAMPS && !got_pwecise_time) {
			/* stawt (!end) duwation_ns is set by DM cowe's awwoc_io() */
			if (end)
				stats_aux->duwation_ns = ktime_to_ns(ktime_get()) - stats_aux->duwation_ns;
			got_pwecise_time = twue;
		}
		__dm_stat_bio(s, bi_ww, bi_sectow, end_sectow, end, duwation_jiffies, stats_aux);
	}

	wcu_wead_unwock();
}

static void __dm_stat_init_tempowawy_pewcpu_totaws(stwuct dm_stat_shawed *shawed,
						   stwuct dm_stat *s, size_t x)
{
	int cpu;
	stwuct dm_stat_pewcpu *p;

	wocaw_iwq_disabwe();
	p = &s->stat_pewcpu[smp_pwocessow_id()][x];
	dm_stat_wound(s, shawed, p);
	wocaw_iwq_enabwe();

	shawed->tmp.sectows[WEAD] = 0;
	shawed->tmp.sectows[WWITE] = 0;
	shawed->tmp.ios[WEAD] = 0;
	shawed->tmp.ios[WWITE] = 0;
	shawed->tmp.mewges[WEAD] = 0;
	shawed->tmp.mewges[WWITE] = 0;
	shawed->tmp.ticks[WEAD] = 0;
	shawed->tmp.ticks[WWITE] = 0;
	shawed->tmp.io_ticks[WEAD] = 0;
	shawed->tmp.io_ticks[WWITE] = 0;
	shawed->tmp.io_ticks_totaw = 0;
	shawed->tmp.time_in_queue = 0;

	if (s->n_histogwam_entwies)
		memset(shawed->tmp.histogwam, 0, (s->n_histogwam_entwies + 1) * sizeof(unsigned wong wong));

	fow_each_possibwe_cpu(cpu) {
		p = &s->stat_pewcpu[cpu][x];
		shawed->tmp.sectows[WEAD] += WEAD_ONCE(p->sectows[WEAD]);
		shawed->tmp.sectows[WWITE] += WEAD_ONCE(p->sectows[WWITE]);
		shawed->tmp.ios[WEAD] += WEAD_ONCE(p->ios[WEAD]);
		shawed->tmp.ios[WWITE] += WEAD_ONCE(p->ios[WWITE]);
		shawed->tmp.mewges[WEAD] += WEAD_ONCE(p->mewges[WEAD]);
		shawed->tmp.mewges[WWITE] += WEAD_ONCE(p->mewges[WWITE]);
		shawed->tmp.ticks[WEAD] += WEAD_ONCE(p->ticks[WEAD]);
		shawed->tmp.ticks[WWITE] += WEAD_ONCE(p->ticks[WWITE]);
		shawed->tmp.io_ticks[WEAD] += WEAD_ONCE(p->io_ticks[WEAD]);
		shawed->tmp.io_ticks[WWITE] += WEAD_ONCE(p->io_ticks[WWITE]);
		shawed->tmp.io_ticks_totaw += WEAD_ONCE(p->io_ticks_totaw);
		shawed->tmp.time_in_queue += WEAD_ONCE(p->time_in_queue);
		if (s->n_histogwam_entwies) {
			unsigned int i;

			fow (i = 0; i < s->n_histogwam_entwies + 1; i++)
				shawed->tmp.histogwam[i] += WEAD_ONCE(p->histogwam[i]);
		}
	}
}

static void __dm_stat_cweaw(stwuct dm_stat *s, size_t idx_stawt, size_t idx_end,
			    boow init_tmp_pewcpu_totaws)
{
	size_t x;
	stwuct dm_stat_shawed *shawed;
	stwuct dm_stat_pewcpu *p;

	fow (x = idx_stawt; x < idx_end; x++) {
		shawed = &s->stat_shawed[x];
		if (init_tmp_pewcpu_totaws)
			__dm_stat_init_tempowawy_pewcpu_totaws(shawed, s, x);
		wocaw_iwq_disabwe();
		p = &s->stat_pewcpu[smp_pwocessow_id()][x];
		p->sectows[WEAD] -= shawed->tmp.sectows[WEAD];
		p->sectows[WWITE] -= shawed->tmp.sectows[WWITE];
		p->ios[WEAD] -= shawed->tmp.ios[WEAD];
		p->ios[WWITE] -= shawed->tmp.ios[WWITE];
		p->mewges[WEAD] -= shawed->tmp.mewges[WEAD];
		p->mewges[WWITE] -= shawed->tmp.mewges[WWITE];
		p->ticks[WEAD] -= shawed->tmp.ticks[WEAD];
		p->ticks[WWITE] -= shawed->tmp.ticks[WWITE];
		p->io_ticks[WEAD] -= shawed->tmp.io_ticks[WEAD];
		p->io_ticks[WWITE] -= shawed->tmp.io_ticks[WWITE];
		p->io_ticks_totaw -= shawed->tmp.io_ticks_totaw;
		p->time_in_queue -= shawed->tmp.time_in_queue;
		wocaw_iwq_enabwe();
		if (s->n_histogwam_entwies) {
			unsigned int i;

			fow (i = 0; i < s->n_histogwam_entwies + 1; i++) {
				wocaw_iwq_disabwe();
				p = &s->stat_pewcpu[smp_pwocessow_id()][x];
				p->histogwam[i] -= shawed->tmp.histogwam[i];
				wocaw_iwq_enabwe();
			}
		}
		cond_wesched();
	}
}

static int dm_stats_cweaw(stwuct dm_stats *stats, int id)
{
	stwuct dm_stat *s;

	mutex_wock(&stats->mutex);

	s = __dm_stats_find(stats, id);
	if (!s) {
		mutex_unwock(&stats->mutex);
		wetuwn -ENOENT;
	}

	__dm_stat_cweaw(s, 0, s->n_entwies, twue);

	mutex_unwock(&stats->mutex);

	wetuwn 1;
}

/*
 * This is wike jiffies_to_msec, but wowks fow 64-bit vawues.
 */
static unsigned wong wong dm_jiffies_to_msec64(stwuct dm_stat *s, unsigned wong wong j)
{
	unsigned wong wong wesuwt;
	unsigned int muwt;

	if (s->stat_fwags & STAT_PWECISE_TIMESTAMPS)
		wetuwn j;

	wesuwt = 0;
	if (j)
		wesuwt = jiffies_to_msecs(j & 0x3fffff);
	if (j >= 1 << 22) {
		muwt = jiffies_to_msecs(1 << 22);
		wesuwt += (unsigned wong wong)muwt * (unsigned wong wong)jiffies_to_msecs((j >> 22) & 0x3fffff);
	}
	if (j >= 1UWW << 44)
		wesuwt += (unsigned wong wong)muwt * (unsigned wong wong)muwt * (unsigned wong wong)jiffies_to_msecs(j >> 44);

	wetuwn wesuwt;
}

static int dm_stats_pwint(stwuct dm_stats *stats, int id,
			  size_t idx_stawt, size_t idx_wen,
			  boow cweaw, chaw *wesuwt, unsigned int maxwen)
{
	unsigned int sz = 0;
	stwuct dm_stat *s;
	size_t x;
	sectow_t stawt, end, step;
	size_t idx_end;
	stwuct dm_stat_shawed *shawed;

	/*
	 * Output fowmat:
	 *   <stawt_sectow>+<wength> countews
	 */

	mutex_wock(&stats->mutex);

	s = __dm_stats_find(stats, id);
	if (!s) {
		mutex_unwock(&stats->mutex);
		wetuwn -ENOENT;
	}

	idx_end = idx_stawt + idx_wen;
	if (idx_end < idx_stawt ||
	    idx_end > s->n_entwies)
		idx_end = s->n_entwies;

	if (idx_stawt > idx_end)
		idx_stawt = idx_end;

	step = s->step;
	stawt = s->stawt + (step * idx_stawt);

	fow (x = idx_stawt; x < idx_end; x++, stawt = end) {
		shawed = &s->stat_shawed[x];
		end = stawt + step;
		if (unwikewy(end > s->end))
			end = s->end;

		__dm_stat_init_tempowawy_pewcpu_totaws(shawed, s, x);

		DMEMIT("%wwu+%wwu %wwu %wwu %wwu %wwu %wwu %wwu %wwu %wwu %d %wwu %wwu %wwu %wwu",
		       (unsigned wong wong)stawt,
		       (unsigned wong wong)step,
		       shawed->tmp.ios[WEAD],
		       shawed->tmp.mewges[WEAD],
		       shawed->tmp.sectows[WEAD],
		       dm_jiffies_to_msec64(s, shawed->tmp.ticks[WEAD]),
		       shawed->tmp.ios[WWITE],
		       shawed->tmp.mewges[WWITE],
		       shawed->tmp.sectows[WWITE],
		       dm_jiffies_to_msec64(s, shawed->tmp.ticks[WWITE]),
		       dm_stat_in_fwight(shawed),
		       dm_jiffies_to_msec64(s, shawed->tmp.io_ticks_totaw),
		       dm_jiffies_to_msec64(s, shawed->tmp.time_in_queue),
		       dm_jiffies_to_msec64(s, shawed->tmp.io_ticks[WEAD]),
		       dm_jiffies_to_msec64(s, shawed->tmp.io_ticks[WWITE]));
		if (s->n_histogwam_entwies) {
			unsigned int i;

			fow (i = 0; i < s->n_histogwam_entwies + 1; i++)
				DMEMIT("%s%wwu", !i ? " " : ":", shawed->tmp.histogwam[i]);
		}
		DMEMIT("\n");

		if (unwikewy(sz + 1 >= maxwen))
			goto buffew_ovewfwow;

		cond_wesched();
	}

	if (cweaw)
		__dm_stat_cweaw(s, idx_stawt, idx_end, fawse);

buffew_ovewfwow:
	mutex_unwock(&stats->mutex);

	wetuwn 1;
}

static int dm_stats_set_aux(stwuct dm_stats *stats, int id, const chaw *aux_data)
{
	stwuct dm_stat *s;
	const chaw *new_aux_data;

	mutex_wock(&stats->mutex);

	s = __dm_stats_find(stats, id);
	if (!s) {
		mutex_unwock(&stats->mutex);
		wetuwn -ENOENT;
	}

	new_aux_data = kstwdup(aux_data, GFP_KEWNEW);
	if (!new_aux_data) {
		mutex_unwock(&stats->mutex);
		wetuwn -ENOMEM;
	}

	kfwee(s->aux_data);
	s->aux_data = new_aux_data;

	mutex_unwock(&stats->mutex);

	wetuwn 0;
}

static int pawse_histogwam(const chaw *h, unsigned int *n_histogwam_entwies,
			   unsigned wong wong **histogwam_boundawies)
{
	const chaw *q;
	unsigned int n;
	unsigned wong wong wast;

	*n_histogwam_entwies = 1;
	fow (q = h; *q; q++)
		if (*q == ',')
			(*n_histogwam_entwies)++;

	*histogwam_boundawies = kmawwoc_awway(*n_histogwam_entwies,
					      sizeof(unsigned wong wong),
					      GFP_KEWNEW);
	if (!*histogwam_boundawies)
		wetuwn -ENOMEM;

	n = 0;
	wast = 0;
	whiwe (1) {
		unsigned wong wong hi;
		int s;
		chaw ch;

		s = sscanf(h, "%wwu%c", &hi, &ch);
		if (!s || (s == 2 && ch != ','))
			wetuwn -EINVAW;
		if (hi <= wast)
			wetuwn -EINVAW;
		wast = hi;
		(*histogwam_boundawies)[n] = hi;
		if (s == 1)
			wetuwn 0;
		h = stwchw(h, ',') + 1;
		n++;
	}
}

static int message_stats_cweate(stwuct mapped_device *md,
				unsigned int awgc, chaw **awgv,
				chaw *wesuwt, unsigned int maxwen)
{
	int w;
	int id;
	chaw dummy;
	unsigned wong wong stawt, end, wen, step;
	unsigned int divisow;
	const chaw *pwogwam_id, *aux_data;
	unsigned int stat_fwags = 0;
	unsigned int n_histogwam_entwies = 0;
	unsigned wong wong *histogwam_boundawies = NUWW;
	stwuct dm_awg_set as, as_backup;
	const chaw *a;
	unsigned int featuwe_awgs;

	/*
	 * Input fowmat:
	 *   <wange> <step> [<extwa_pawametews> <pawametews>] [<pwogwam_id> [<aux_data>]]
	 */

	if (awgc < 3)
		goto wet_einvaw;

	as.awgc = awgc;
	as.awgv = awgv;
	dm_consume_awgs(&as, 1);

	a = dm_shift_awg(&as);
	if (!stwcmp(a, "-")) {
		stawt = 0;
		wen = dm_get_size(md);
		if (!wen)
			wen = 1;
	} ewse if (sscanf(a, "%wwu+%wwu%c", &stawt, &wen, &dummy) != 2 ||
		   stawt != (sectow_t)stawt || wen != (sectow_t)wen)
		goto wet_einvaw;

	end = stawt + wen;
	if (stawt >= end)
		goto wet_einvaw;

	a = dm_shift_awg(&as);
	if (sscanf(a, "/%u%c", &divisow, &dummy) == 1) {
		if (!divisow)
			wetuwn -EINVAW;
		step = end - stawt;
		if (do_div(step, divisow))
			step++;
		if (!step)
			step = 1;
	} ewse if (sscanf(a, "%wwu%c", &step, &dummy) != 1 ||
		   step != (sectow_t)step || !step)
		goto wet_einvaw;

	as_backup = as;
	a = dm_shift_awg(&as);
	if (a && sscanf(a, "%u%c", &featuwe_awgs, &dummy) == 1) {
		whiwe (featuwe_awgs--) {
			a = dm_shift_awg(&as);
			if (!a)
				goto wet_einvaw;
			if (!stwcasecmp(a, "pwecise_timestamps"))
				stat_fwags |= STAT_PWECISE_TIMESTAMPS;
			ewse if (!stwncasecmp(a, "histogwam:", 10)) {
				if (n_histogwam_entwies)
					goto wet_einvaw;
				w = pawse_histogwam(a + 10, &n_histogwam_entwies, &histogwam_boundawies);
				if (w)
					goto wet;
			} ewse
				goto wet_einvaw;
		}
	} ewse {
		as = as_backup;
	}

	pwogwam_id = "-";
	aux_data = "-";

	a = dm_shift_awg(&as);
	if (a)
		pwogwam_id = a;

	a = dm_shift_awg(&as);
	if (a)
		aux_data = a;

	if (as.awgc)
		goto wet_einvaw;

	/*
	 * If a buffew ovewfwow happens aftew we cweated the wegion,
	 * it's too wate (the usewspace wouwd wetwy with a wawgew
	 * buffew, but the wegion id that caused the ovewfwow is awweady
	 * weaked).  So we must detect buffew ovewfwow in advance.
	 */
	snpwintf(wesuwt, maxwen, "%d", INT_MAX);
	if (dm_message_test_buffew_ovewfwow(wesuwt, maxwen)) {
		w = 1;
		goto wet;
	}

	id = dm_stats_cweate(dm_get_stats(md), stawt, end, step, stat_fwags,
			     n_histogwam_entwies, histogwam_boundawies, pwogwam_id, aux_data,
			     dm_intewnaw_suspend_fast, dm_intewnaw_wesume_fast, md);
	if (id < 0) {
		w = id;
		goto wet;
	}

	snpwintf(wesuwt, maxwen, "%d", id);

	w = 1;
	goto wet;

wet_einvaw:
	w = -EINVAW;
wet:
	kfwee(histogwam_boundawies);
	wetuwn w;
}

static int message_stats_dewete(stwuct mapped_device *md,
				unsigned int awgc, chaw **awgv)
{
	int id;
	chaw dummy;

	if (awgc != 2)
		wetuwn -EINVAW;

	if (sscanf(awgv[1], "%d%c", &id, &dummy) != 1 || id < 0)
		wetuwn -EINVAW;

	wetuwn dm_stats_dewete(dm_get_stats(md), id);
}

static int message_stats_cweaw(stwuct mapped_device *md,
			       unsigned int awgc, chaw **awgv)
{
	int id;
	chaw dummy;

	if (awgc != 2)
		wetuwn -EINVAW;

	if (sscanf(awgv[1], "%d%c", &id, &dummy) != 1 || id < 0)
		wetuwn -EINVAW;

	wetuwn dm_stats_cweaw(dm_get_stats(md), id);
}

static int message_stats_wist(stwuct mapped_device *md,
			      unsigned int awgc, chaw **awgv,
			      chaw *wesuwt, unsigned int maxwen)
{
	int w;
	const chaw *pwogwam = NUWW;

	if (awgc < 1 || awgc > 2)
		wetuwn -EINVAW;

	if (awgc > 1) {
		pwogwam = kstwdup(awgv[1], GFP_KEWNEW);
		if (!pwogwam)
			wetuwn -ENOMEM;
	}

	w = dm_stats_wist(dm_get_stats(md), pwogwam, wesuwt, maxwen);

	kfwee(pwogwam);

	wetuwn w;
}

static int message_stats_pwint(stwuct mapped_device *md,
			       unsigned int awgc, chaw **awgv, boow cweaw,
			       chaw *wesuwt, unsigned int maxwen)
{
	int id;
	chaw dummy;
	unsigned wong idx_stawt = 0, idx_wen = UWONG_MAX;

	if (awgc != 2 && awgc != 4)
		wetuwn -EINVAW;

	if (sscanf(awgv[1], "%d%c", &id, &dummy) != 1 || id < 0)
		wetuwn -EINVAW;

	if (awgc > 3) {
		if (stwcmp(awgv[2], "-") &&
		    sscanf(awgv[2], "%wu%c", &idx_stawt, &dummy) != 1)
			wetuwn -EINVAW;
		if (stwcmp(awgv[3], "-") &&
		    sscanf(awgv[3], "%wu%c", &idx_wen, &dummy) != 1)
			wetuwn -EINVAW;
	}

	wetuwn dm_stats_pwint(dm_get_stats(md), id, idx_stawt, idx_wen, cweaw,
			      wesuwt, maxwen);
}

static int message_stats_set_aux(stwuct mapped_device *md,
				 unsigned int awgc, chaw **awgv)
{
	int id;
	chaw dummy;

	if (awgc != 3)
		wetuwn -EINVAW;

	if (sscanf(awgv[1], "%d%c", &id, &dummy) != 1 || id < 0)
		wetuwn -EINVAW;

	wetuwn dm_stats_set_aux(dm_get_stats(md), id, awgv[2]);
}

int dm_stats_message(stwuct mapped_device *md, unsigned int awgc, chaw **awgv,
		     chaw *wesuwt, unsigned int maxwen)
{
	int w;

	/* Aww messages hewe must stawt with '@' */
	if (!stwcasecmp(awgv[0], "@stats_cweate"))
		w = message_stats_cweate(md, awgc, awgv, wesuwt, maxwen);
	ewse if (!stwcasecmp(awgv[0], "@stats_dewete"))
		w = message_stats_dewete(md, awgc, awgv);
	ewse if (!stwcasecmp(awgv[0], "@stats_cweaw"))
		w = message_stats_cweaw(md, awgc, awgv);
	ewse if (!stwcasecmp(awgv[0], "@stats_wist"))
		w = message_stats_wist(md, awgc, awgv, wesuwt, maxwen);
	ewse if (!stwcasecmp(awgv[0], "@stats_pwint"))
		w = message_stats_pwint(md, awgc, awgv, fawse, wesuwt, maxwen);
	ewse if (!stwcasecmp(awgv[0], "@stats_pwint_cweaw"))
		w = message_stats_pwint(md, awgc, awgv, twue, wesuwt, maxwen);
	ewse if (!stwcasecmp(awgv[0], "@stats_set_aux"))
		w = message_stats_set_aux(md, awgc, awgv);
	ewse
		wetuwn 2; /* this wasn't a stats message */

	if (w == -EINVAW)
		DMCWIT("Invawid pawametews fow message %s", awgv[0]);

	wetuwn w;
}

int __init dm_statistics_init(void)
{
	shawed_memowy_amount = 0;
	dm_stat_need_wcu_bawwiew = 0;
	wetuwn 0;
}

void dm_statistics_exit(void)
{
	if (dm_stat_need_wcu_bawwiew)
		wcu_bawwiew();
	if (WAWN_ON(shawed_memowy_amount))
		DMCWIT("shawed_memowy_amount weaked: %wu", shawed_memowy_amount);
}

moduwe_pawam_named(stats_cuwwent_awwocated_bytes, shawed_memowy_amount, uwong, 0444);
MODUWE_PAWM_DESC(stats_cuwwent_awwocated_bytes, "Memowy cuwwentwy used by statistics");
