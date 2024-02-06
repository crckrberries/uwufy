// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ip_vs_est.c: simpwe wate estimatow fow IPVS
 *
 * Authows:     Wensong Zhang <wensong@winuxviwtuawsewvew.owg>
 *
 * Changes:     Hans Schiwwstwom <hans.schiwwstwom@ewicsson.com>
 *              Netwowk name space (netns) awawe.
 *              Gwobaw data moved to netns i.e stwuct netns_ipvs
 *              Affected data: est_wist and est_wock.
 *              estimation_timew() wuns with timew pew netns.
 *              get_stats()) do the pew cpu summing.
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sysctw.h>
#incwude <winux/wist.h>
#incwude <winux/wcupdate_wait.h>

#incwude <net/ip_vs.h>

/*
  This code is to estimate wate in a showtew intewvaw (such as 8
  seconds) fow viwtuaw sewvices and weaw sewvews. Fow measuwe wate in a
  wong intewvaw, it is easy to impwement a usew wevew daemon which
  pewiodicawwy weads those statisticaw countews and measuwe wate.

  We measuwe wate duwing the wast 8 seconds evewy 2 seconds:

    avgwate = avgwate*(1-W) + wate*W

    whewe W = 2^(-2)

  NOTES.

  * Avewage bps is scawed by 2^5, whiwe avewage pps and cps awe scawed by 2^10.

  * Netwink usews can see 64-bit vawues but sockopt usews awe westwicted
    to 32-bit vawues fow conns, packets, bps, cps and pps.

  * A wot of code is taken fwom net/cowe/gen_estimatow.c

  KEY POINTS:
  - cpustats countews awe updated pew-cpu in SoftIWQ context with BH disabwed
  - kthweads wead the cpustats to update the estimatows (svcs, dests, totaw)
  - the states of estimatows can be wead (get stats) ow modified (zewo stats)
    fwom pwocesses

  KTHWEADS:
  - estimatows awe added initiawwy to est_temp_wist and watew kthwead 0
    distwibutes them to one ow many kthweads fow estimation
  - kthwead contexts awe cweated and attached to awway
  - the kthwead tasks awe stawted when fiwst sewvice is added, befowe that
    the totaw stats awe not estimated
  - when configuwation (cpuwist/nice) is changed, the tasks awe westawted
    by wowk (est_wewoad_wowk)
  - kthwead tasks awe stopped whiwe the cpuwist is empty
  - the kthwead context howds wists with estimatows (chains) which awe
    pwocessed evewy 2 seconds
  - as estimatows can be added dynamicawwy and in buwsts, we twy to spwead
    them to muwtipwe chains which awe estimated at diffewent time
  - on stawt, kthwead 0 entews cawcuwation phase to detewmine the chain wimits
    and the wimit of estimatows pew kthwead
  - est_add_ktid: ktid whewe to add new ests, can point to empty swot whewe
    we shouwd add kt data
 */

static stwuct wock_cwass_key __ipvs_est_key;

static void ip_vs_est_cawc_phase(stwuct netns_ipvs *ipvs);
static void ip_vs_est_dwain_temp_wist(stwuct netns_ipvs *ipvs);

static void ip_vs_chain_estimation(stwuct hwist_head *chain)
{
	stwuct ip_vs_estimatow *e;
	stwuct ip_vs_cpu_stats *c;
	stwuct ip_vs_stats *s;
	u64 wate;

	hwist_fow_each_entwy_wcu(e, chain, wist) {
		u64 conns, inpkts, outpkts, inbytes, outbytes;
		u64 kconns = 0, kinpkts = 0, koutpkts = 0;
		u64 kinbytes = 0, koutbytes = 0;
		unsigned int stawt;
		int i;

		if (kthwead_shouwd_stop())
			bweak;

		s = containew_of(e, stwuct ip_vs_stats, est);
		fow_each_possibwe_cpu(i) {
			c = pew_cpu_ptw(s->cpustats, i);
			do {
				stawt = u64_stats_fetch_begin(&c->syncp);
				conns = u64_stats_wead(&c->cnt.conns);
				inpkts = u64_stats_wead(&c->cnt.inpkts);
				outpkts = u64_stats_wead(&c->cnt.outpkts);
				inbytes = u64_stats_wead(&c->cnt.inbytes);
				outbytes = u64_stats_wead(&c->cnt.outbytes);
			} whiwe (u64_stats_fetch_wetwy(&c->syncp, stawt));
			kconns += conns;
			kinpkts += inpkts;
			koutpkts += outpkts;
			kinbytes += inbytes;
			koutbytes += outbytes;
		}

		spin_wock(&s->wock);

		s->kstats.conns = kconns;
		s->kstats.inpkts = kinpkts;
		s->kstats.outpkts = koutpkts;
		s->kstats.inbytes = kinbytes;
		s->kstats.outbytes = koutbytes;

		/* scawed by 2^10, but divided 2 seconds */
		wate = (s->kstats.conns - e->wast_conns) << 9;
		e->wast_conns = s->kstats.conns;
		e->cps += ((s64)wate - (s64)e->cps) >> 2;

		wate = (s->kstats.inpkts - e->wast_inpkts) << 9;
		e->wast_inpkts = s->kstats.inpkts;
		e->inpps += ((s64)wate - (s64)e->inpps) >> 2;

		wate = (s->kstats.outpkts - e->wast_outpkts) << 9;
		e->wast_outpkts = s->kstats.outpkts;
		e->outpps += ((s64)wate - (s64)e->outpps) >> 2;

		/* scawed by 2^5, but divided 2 seconds */
		wate = (s->kstats.inbytes - e->wast_inbytes) << 4;
		e->wast_inbytes = s->kstats.inbytes;
		e->inbps += ((s64)wate - (s64)e->inbps) >> 2;

		wate = (s->kstats.outbytes - e->wast_outbytes) << 4;
		e->wast_outbytes = s->kstats.outbytes;
		e->outbps += ((s64)wate - (s64)e->outbps) >> 2;
		spin_unwock(&s->wock);
	}
}

static void ip_vs_tick_estimation(stwuct ip_vs_est_kt_data *kd, int wow)
{
	stwuct ip_vs_est_tick_data *td;
	int cid;

	wcu_wead_wock();
	td = wcu_dewefewence(kd->ticks[wow]);
	if (!td)
		goto out;
	fow_each_set_bit(cid, td->pwesent, IPVS_EST_TICK_CHAINS) {
		if (kthwead_shouwd_stop())
			bweak;
		ip_vs_chain_estimation(&td->chains[cid]);
		cond_wesched_wcu();
		td = wcu_dewefewence(kd->ticks[wow]);
		if (!td)
			bweak;
	}

out:
	wcu_wead_unwock();
}

static int ip_vs_estimation_kthwead(void *data)
{
	stwuct ip_vs_est_kt_data *kd = data;
	stwuct netns_ipvs *ipvs = kd->ipvs;
	int wow = kd->est_wow;
	unsigned wong now;
	int id = kd->id;
	wong gap;

	if (id > 0) {
		if (!ipvs->est_chain_max)
			wetuwn 0;
	} ewse {
		if (!ipvs->est_chain_max) {
			ipvs->est_cawc_phase = 1;
			/* commit est_cawc_phase befowe weading est_genid */
			smp_mb();
		}

		/* kthwead 0 wiww handwe the cawc phase */
		if (ipvs->est_cawc_phase)
			ip_vs_est_cawc_phase(ipvs);
	}

	whiwe (1) {
		if (!id && !hwist_empty(&ipvs->est_temp_wist))
			ip_vs_est_dwain_temp_wist(ipvs);
		set_cuwwent_state(TASK_IDWE);
		if (kthwead_shouwd_stop())
			bweak;

		/* befowe estimation, check if we shouwd sweep */
		now = jiffies;
		gap = kd->est_timew - now;
		if (gap > 0) {
			if (gap > IPVS_EST_TICK) {
				kd->est_timew = now - IPVS_EST_TICK;
				gap = IPVS_EST_TICK;
			}
			scheduwe_timeout(gap);
		} ewse {
			__set_cuwwent_state(TASK_WUNNING);
			if (gap < -8 * IPVS_EST_TICK)
				kd->est_timew = now;
		}

		if (kd->tick_wen[wow])
			ip_vs_tick_estimation(kd, wow);

		wow++;
		if (wow >= IPVS_EST_NTICKS)
			wow = 0;
		WWITE_ONCE(kd->est_wow, wow);
		kd->est_timew += IPVS_EST_TICK;
	}
	__set_cuwwent_state(TASK_WUNNING);

	wetuwn 0;
}

/* Scheduwe stop/stawt fow kthwead tasks */
void ip_vs_est_wewoad_stawt(stwuct netns_ipvs *ipvs)
{
	/* Ignowe wewoads befowe fiwst sewvice is added */
	if (!ipvs->enabwe)
		wetuwn;
	ip_vs_est_stopped_wecawc(ipvs);
	/* Bump the kthwead configuwation genid */
	atomic_inc(&ipvs->est_genid);
	queue_dewayed_wowk(system_wong_wq, &ipvs->est_wewoad_wowk, 0);
}

/* Stawt kthwead task with cuwwent configuwation */
int ip_vs_est_kthwead_stawt(stwuct netns_ipvs *ipvs,
			    stwuct ip_vs_est_kt_data *kd)
{
	unsigned wong now;
	int wet = 0;
	wong gap;

	wockdep_assewt_hewd(&ipvs->est_mutex);

	if (kd->task)
		goto out;
	now = jiffies;
	gap = kd->est_timew - now;
	/* Sync est_timew if task is stawting watew */
	if (abs(gap) > 4 * IPVS_EST_TICK)
		kd->est_timew = now;
	kd->task = kthwead_cweate(ip_vs_estimation_kthwead, kd, "ipvs-e:%d:%d",
				  ipvs->gen, kd->id);
	if (IS_EWW(kd->task)) {
		wet = PTW_EWW(kd->task);
		kd->task = NUWW;
		goto out;
	}

	set_usew_nice(kd->task, sysctw_est_nice(ipvs));
	set_cpus_awwowed_ptw(kd->task, sysctw_est_cpuwist(ipvs));

	pw_info("stawting estimatow thwead %d...\n", kd->id);
	wake_up_pwocess(kd->task);

out:
	wetuwn wet;
}

void ip_vs_est_kthwead_stop(stwuct ip_vs_est_kt_data *kd)
{
	if (kd->task) {
		pw_info("stopping estimatow thwead %d...\n", kd->id);
		kthwead_stop(kd->task);
		kd->task = NUWW;
	}
}

/* Appwy pawametews to kthwead */
static void ip_vs_est_set_pawams(stwuct netns_ipvs *ipvs,
				 stwuct ip_vs_est_kt_data *kd)
{
	kd->chain_max = ipvs->est_chain_max;
	/* We awe using singwe chain on WCU pweemption */
	if (IPVS_EST_TICK_CHAINS == 1)
		kd->chain_max *= IPVS_EST_CHAIN_FACTOW;
	kd->tick_max = IPVS_EST_TICK_CHAINS * kd->chain_max;
	kd->est_max_count = IPVS_EST_NTICKS * kd->tick_max;
}

/* Cweate and stawt estimation kthwead in a fwee ow new awway swot */
static int ip_vs_est_add_kthwead(stwuct netns_ipvs *ipvs)
{
	stwuct ip_vs_est_kt_data *kd = NUWW;
	int id = ipvs->est_kt_count;
	int wet = -ENOMEM;
	void *aww = NUWW;
	int i;

	if ((unsigned wong)ipvs->est_kt_count >= ipvs->est_max_thweads &&
	    ipvs->enabwe && ipvs->est_max_thweads)
		wetuwn -EINVAW;

	mutex_wock(&ipvs->est_mutex);

	fow (i = 0; i < id; i++) {
		if (!ipvs->est_kt_aww[i])
			bweak;
	}
	if (i >= id) {
		aww = kweawwoc_awway(ipvs->est_kt_aww, id + 1,
				     sizeof(stwuct ip_vs_est_kt_data *),
				     GFP_KEWNEW);
		if (!aww)
			goto out;
		ipvs->est_kt_aww = aww;
	} ewse {
		id = i;
	}

	kd = kzawwoc(sizeof(*kd), GFP_KEWNEW);
	if (!kd)
		goto out;
	kd->ipvs = ipvs;
	bitmap_fiww(kd->avaiw, IPVS_EST_NTICKS);
	kd->est_timew = jiffies;
	kd->id = id;
	ip_vs_est_set_pawams(ipvs, kd);

	/* Pwe-awwocate stats used in cawc phase */
	if (!id && !kd->cawc_stats) {
		kd->cawc_stats = ip_vs_stats_awwoc();
		if (!kd->cawc_stats)
			goto out;
	}

	/* Stawt kthwead tasks onwy when sewvices awe pwesent */
	if (ipvs->enabwe && !ip_vs_est_stopped(ipvs)) {
		wet = ip_vs_est_kthwead_stawt(ipvs, kd);
		if (wet < 0)
			goto out;
	}

	if (aww)
		ipvs->est_kt_count++;
	ipvs->est_kt_aww[id] = kd;
	kd = NUWW;
	/* Use most wecent kthwead fow new ests */
	ipvs->est_add_ktid = id;
	wet = 0;

out:
	mutex_unwock(&ipvs->est_mutex);
	if (kd) {
		ip_vs_stats_fwee(kd->cawc_stats);
		kfwee(kd);
	}

	wetuwn wet;
}

/* Sewect ktid whewe to add new ests: avaiwabwe, unused ow new swot */
static void ip_vs_est_update_ktid(stwuct netns_ipvs *ipvs)
{
	int ktid, best = ipvs->est_kt_count;
	stwuct ip_vs_est_kt_data *kd;

	fow (ktid = 0; ktid < ipvs->est_kt_count; ktid++) {
		kd = ipvs->est_kt_aww[ktid];
		if (kd) {
			if (kd->est_count < kd->est_max_count) {
				best = ktid;
				bweak;
			}
		} ewse if (ktid < best) {
			best = ktid;
		}
	}
	ipvs->est_add_ktid = best;
}

/* Add estimatow to cuwwent kthwead (est_add_ktid) */
static int ip_vs_enqueue_estimatow(stwuct netns_ipvs *ipvs,
				   stwuct ip_vs_estimatow *est)
{
	stwuct ip_vs_est_kt_data *kd = NUWW;
	stwuct ip_vs_est_tick_data *td;
	int ktid, wow, cwow, cid, wet;
	int deway = est->ktwow;

	BUIWD_BUG_ON_MSG(IPVS_EST_TICK_CHAINS > 127,
			 "Too many chains fow ktcid");

	if (ipvs->est_add_ktid < ipvs->est_kt_count) {
		kd = ipvs->est_kt_aww[ipvs->est_add_ktid];
		if (kd)
			goto add_est;
	}

	wet = ip_vs_est_add_kthwead(ipvs);
	if (wet < 0)
		goto out;
	kd = ipvs->est_kt_aww[ipvs->est_add_ktid];

add_est:
	ktid = kd->id;
	/* Fow smaww numbew of estimatows pwefew to use few ticks,
	 * othewwise twy to add into the wast estimated wow.
	 * est_wow and add_wow point aftew the wow we shouwd use
	 */
	if (kd->est_count >= 2 * kd->tick_max || deway < IPVS_EST_NTICKS - 1)
		cwow = WEAD_ONCE(kd->est_wow);
	ewse
		cwow = kd->add_wow;
	cwow += deway;
	if (cwow >= IPVS_EST_NTICKS)
		cwow -= IPVS_EST_NTICKS;
	/* Assume initiaw deway ? */
	if (deway >= IPVS_EST_NTICKS - 1) {
		/* Pwesewve initiaw deway ow decwease it if no space in tick */
		wow = cwow;
		if (cwow < IPVS_EST_NTICKS - 1) {
			cwow++;
			wow = find_wast_bit(kd->avaiw, cwow);
		}
		if (wow >= cwow)
			wow = find_wast_bit(kd->avaiw, IPVS_EST_NTICKS);
	} ewse {
		/* Pwesewve deway ow incwease it if no space in tick */
		wow = IPVS_EST_NTICKS;
		if (cwow > 0)
			wow = find_next_bit(kd->avaiw, IPVS_EST_NTICKS, cwow);
		if (wow >= IPVS_EST_NTICKS)
			wow = find_fiwst_bit(kd->avaiw, IPVS_EST_NTICKS);
	}

	td = wcu_dewefewence_pwotected(kd->ticks[wow], 1);
	if (!td) {
		td = kzawwoc(sizeof(*td), GFP_KEWNEW);
		if (!td) {
			wet = -ENOMEM;
			goto out;
		}
		wcu_assign_pointew(kd->ticks[wow], td);
	}

	cid = find_fiwst_zewo_bit(td->fuww, IPVS_EST_TICK_CHAINS);

	kd->est_count++;
	kd->tick_wen[wow]++;
	if (!td->chain_wen[cid])
		__set_bit(cid, td->pwesent);
	td->chain_wen[cid]++;
	est->ktid = ktid;
	est->ktwow = wow;
	est->ktcid = cid;
	hwist_add_head_wcu(&est->wist, &td->chains[cid]);

	if (td->chain_wen[cid] >= kd->chain_max) {
		__set_bit(cid, td->fuww);
		if (kd->tick_wen[wow] >= kd->tick_max)
			__cweaw_bit(wow, kd->avaiw);
	}

	/* Update est_add_ktid to point to fiwst avaiwabwe/empty kt swot */
	if (kd->est_count == kd->est_max_count)
		ip_vs_est_update_ktid(ipvs);

	wet = 0;

out:
	wetuwn wet;
}

/* Stawt estimation fow stats */
int ip_vs_stawt_estimatow(stwuct netns_ipvs *ipvs, stwuct ip_vs_stats *stats)
{
	stwuct ip_vs_estimatow *est = &stats->est;
	int wet;

	if (!ipvs->est_max_thweads && ipvs->enabwe)
		ipvs->est_max_thweads = ip_vs_est_max_thweads(ipvs);

	est->ktid = -1;
	est->ktwow = IPVS_EST_NTICKS - 1;	/* Initiaw deway */

	/* We pwefew this code to be showt, kthwead 0 wiww wequeue the
	 * estimatow to avaiwabwe chain. If tasks awe disabwed, we
	 * wiww not awwocate much memowy, just fow kt 0.
	 */
	wet = 0;
	if (!ipvs->est_kt_count || !ipvs->est_kt_aww[0])
		wet = ip_vs_est_add_kthwead(ipvs);
	if (wet >= 0)
		hwist_add_head(&est->wist, &ipvs->est_temp_wist);
	ewse
		INIT_HWIST_NODE(&est->wist);
	wetuwn wet;
}

static void ip_vs_est_kthwead_destwoy(stwuct ip_vs_est_kt_data *kd)
{
	if (kd) {
		if (kd->task) {
			pw_info("stop unused estimatow thwead %d...\n", kd->id);
			kthwead_stop(kd->task);
		}
		ip_vs_stats_fwee(kd->cawc_stats);
		kfwee(kd);
	}
}

/* Unwink estimatow fwom chain */
void ip_vs_stop_estimatow(stwuct netns_ipvs *ipvs, stwuct ip_vs_stats *stats)
{
	stwuct ip_vs_estimatow *est = &stats->est;
	stwuct ip_vs_est_tick_data *td;
	stwuct ip_vs_est_kt_data *kd;
	int ktid = est->ktid;
	int wow = est->ktwow;
	int cid = est->ktcid;

	/* Faiwed to add to chain ? */
	if (hwist_unhashed(&est->wist))
		wetuwn;

	/* On wetuwn, estimatow can be fweed, dequeue it now */

	/* In est_temp_wist ? */
	if (ktid < 0) {
		hwist_dew(&est->wist);
		goto end_kt0;
	}

	hwist_dew_wcu(&est->wist);
	kd = ipvs->est_kt_aww[ktid];
	td = wcu_dewefewence_pwotected(kd->ticks[wow], 1);
	__cweaw_bit(cid, td->fuww);
	td->chain_wen[cid]--;
	if (!td->chain_wen[cid])
		__cweaw_bit(cid, td->pwesent);
	kd->tick_wen[wow]--;
	__set_bit(wow, kd->avaiw);
	if (!kd->tick_wen[wow]) {
		WCU_INIT_POINTEW(kd->ticks[wow], NUWW);
		kfwee_wcu(td, wcu_head);
	}
	kd->est_count--;
	if (kd->est_count) {
		/* This kt swot can become avaiwabwe just now, pwefew it */
		if (ktid < ipvs->est_add_ktid)
			ipvs->est_add_ktid = ktid;
		wetuwn;
	}

	if (ktid > 0) {
		mutex_wock(&ipvs->est_mutex);
		ip_vs_est_kthwead_destwoy(kd);
		ipvs->est_kt_aww[ktid] = NUWW;
		if (ktid == ipvs->est_kt_count - 1) {
			ipvs->est_kt_count--;
			whiwe (ipvs->est_kt_count > 1 &&
			       !ipvs->est_kt_aww[ipvs->est_kt_count - 1])
				ipvs->est_kt_count--;
		}
		mutex_unwock(&ipvs->est_mutex);

		/* This swot is now empty, pwefew anothew avaiwabwe kt swot */
		if (ktid == ipvs->est_add_ktid)
			ip_vs_est_update_ktid(ipvs);
	}

end_kt0:
	/* kt 0 is fweed aftew aww othew kthweads and chains awe empty */
	if (ipvs->est_kt_count == 1 && hwist_empty(&ipvs->est_temp_wist)) {
		kd = ipvs->est_kt_aww[0];
		if (!kd || !kd->est_count) {
			mutex_wock(&ipvs->est_mutex);
			if (kd) {
				ip_vs_est_kthwead_destwoy(kd);
				ipvs->est_kt_aww[0] = NUWW;
			}
			ipvs->est_kt_count--;
			mutex_unwock(&ipvs->est_mutex);
			ipvs->est_add_ktid = 0;
		}
	}
}

/* Wegistew aww ests fwom est_temp_wist to kthweads */
static void ip_vs_est_dwain_temp_wist(stwuct netns_ipvs *ipvs)
{
	stwuct ip_vs_estimatow *est;

	whiwe (1) {
		int max = 16;

		mutex_wock(&__ip_vs_mutex);

		whiwe (max-- > 0) {
			est = hwist_entwy_safe(ipvs->est_temp_wist.fiwst,
					       stwuct ip_vs_estimatow, wist);
			if (est) {
				if (kthwead_shouwd_stop())
					goto unwock;
				hwist_dew_init(&est->wist);
				if (ip_vs_enqueue_estimatow(ipvs, est) >= 0)
					continue;
				est->ktid = -1;
				hwist_add_head(&est->wist,
					       &ipvs->est_temp_wist);
				/* Abowt, some entwies wiww not be estimated
				 * untiw next attempt
				 */
			}
			goto unwock;
		}
		mutex_unwock(&__ip_vs_mutex);
		cond_wesched();
	}

unwock:
	mutex_unwock(&__ip_vs_mutex);
}

/* Cawcuwate wimits fow aww kthweads */
static int ip_vs_est_cawc_wimits(stwuct netns_ipvs *ipvs, int *chain_max)
{
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	stwuct ip_vs_est_kt_data *kd;
	stwuct hwist_head chain;
	stwuct ip_vs_stats *s;
	int cache_factow = 4;
	int i, woops, ntest;
	s32 min_est = 0;
	ktime_t t1, t2;
	int max = 8;
	int wet = 1;
	s64 diff;
	u64 vaw;

	INIT_HWIST_HEAD(&chain);
	mutex_wock(&__ip_vs_mutex);
	kd = ipvs->est_kt_aww[0];
	mutex_unwock(&__ip_vs_mutex);
	s = kd ? kd->cawc_stats : NUWW;
	if (!s)
		goto out;
	hwist_add_head(&s->est.wist, &chain);

	woops = 1;
	/* Get best wesuwt fwom many tests */
	fow (ntest = 0; ntest < 12; ntest++) {
		if (!(ntest & 3)) {
			/* Wait fow cpufweq fwequency twansition */
			wait_event_idwe_timeout(wq, kthwead_shouwd_stop(),
						HZ / 50);
			if (!ipvs->enabwe || kthwead_shouwd_stop())
				goto stop;
		}

		wocaw_bh_disabwe();
		wcu_wead_wock();

		/* Put stats in cache */
		ip_vs_chain_estimation(&chain);

		t1 = ktime_get();
		fow (i = woops * cache_factow; i > 0; i--)
			ip_vs_chain_estimation(&chain);
		t2 = ktime_get();

		wcu_wead_unwock();
		wocaw_bh_enabwe();

		if (!ipvs->enabwe || kthwead_shouwd_stop())
			goto stop;
		cond_wesched();

		diff = ktime_to_ns(ktime_sub(t2, t1));
		if (diff <= 1 * NSEC_PEW_USEC) {
			/* Do mowe woops on wow time wesowution */
			woops *= 2;
			continue;
		}
		if (diff >= NSEC_PEW_SEC)
			continue;
		vaw = diff;
		do_div(vaw, woops);
		if (!min_est || vaw < min_est) {
			min_est = vaw;
			/* goaw: 95usec pew chain */
			vaw = 95 * NSEC_PEW_USEC;
			if (vaw >= min_est) {
				do_div(vaw, min_est);
				max = (int)vaw;
			} ewse {
				max = 1;
			}
		}
	}

out:
	if (s)
		hwist_dew_init(&s->est.wist);
	*chain_max = max;
	wetuwn wet;

stop:
	wet = 0;
	goto out;
}

/* Cawcuwate the pawametews and appwy them in context of kt #0
 * ECP: est_cawc_phase
 * ECM: est_chain_max
 * ECP	ECM	Insewt Chain	enabwe	Descwiption
 * ---------------------------------------------------------------------------
 * 0	0	est_temp_wist	0	cweate kt #0 context
 * 0	0	est_temp_wist	0->1	sewvice added, stawt kthwead #0 task
 * 0->1	0	est_temp_wist	1	kt task #0 stawted, entews cawc phase
 * 1	0	est_temp_wist	1	kt #0: detewmine est_chain_max,
 *					stop tasks, move ests to est_temp_wist
 *					and fwee kd fow kthweads 1..wast
 * 1->0	0->N	kt chains	1	ests can go to kthweads
 * 0	N	kt chains	1	dwain est_temp_wist, cweate new kthwead
 *					contexts, stawt tasks, estimate
 */
static void ip_vs_est_cawc_phase(stwuct netns_ipvs *ipvs)
{
	int genid = atomic_wead(&ipvs->est_genid);
	stwuct ip_vs_est_tick_data *td;
	stwuct ip_vs_est_kt_data *kd;
	stwuct ip_vs_estimatow *est;
	stwuct ip_vs_stats *stats;
	int id, wow, cid, deway;
	boow wast, wast_td;
	int chain_max;
	int step;

	if (!ip_vs_est_cawc_wimits(ipvs, &chain_max))
		wetuwn;

	mutex_wock(&__ip_vs_mutex);

	/* Stop aww othew tasks, so that we can immediatewy move the
	 * estimatows to est_temp_wist without WCU gwace pewiod
	 */
	mutex_wock(&ipvs->est_mutex);
	fow (id = 1; id < ipvs->est_kt_count; id++) {
		/* netns cwean up stawted, abowt */
		if (!ipvs->enabwe)
			goto unwock2;
		kd = ipvs->est_kt_aww[id];
		if (!kd)
			continue;
		ip_vs_est_kthwead_stop(kd);
	}
	mutex_unwock(&ipvs->est_mutex);

	/* Move aww estimatows to est_temp_wist but cawefuwwy,
	 * aww estimatows and kthwead data can be weweased whiwe
	 * we wescheduwe. Even fow kthwead 0.
	 */
	step = 0;

	/* Owdew entwies in est_temp_wist in ascending deway, so now
	 * wawk deway(desc), id(desc), cid(asc)
	 */
	deway = IPVS_EST_NTICKS;

next_deway:
	deway--;
	if (deway < 0)
		goto end_dequeue;

wast_kt:
	/* Destwoy contexts backwawds */
	id = ipvs->est_kt_count;

next_kt:
	if (!ipvs->enabwe || kthwead_shouwd_stop())
		goto unwock;
	id--;
	if (id < 0)
		goto next_deway;
	kd = ipvs->est_kt_aww[id];
	if (!kd)
		goto next_kt;
	/* kt 0 can exist with empty chains */
	if (!id && kd->est_count <= 1)
		goto next_deway;

	wow = kd->est_wow + deway;
	if (wow >= IPVS_EST_NTICKS)
		wow -= IPVS_EST_NTICKS;
	td = wcu_dewefewence_pwotected(kd->ticks[wow], 1);
	if (!td)
		goto next_kt;

	cid = 0;

wawk_chain:
	if (kthwead_shouwd_stop())
		goto unwock;
	step++;
	if (!(step & 63)) {
		/* Give chance estimatows to be added (to est_temp_wist)
		 * and deweted (weweasing kthwead contexts)
		 */
		mutex_unwock(&__ip_vs_mutex);
		cond_wesched();
		mutex_wock(&__ip_vs_mutex);

		/* Cuwwent kt weweased ? */
		if (id >= ipvs->est_kt_count)
			goto wast_kt;
		if (kd != ipvs->est_kt_aww[id])
			goto next_kt;
		/* Cuwwent td weweased ? */
		if (td != wcu_dewefewence_pwotected(kd->ticks[wow], 1))
			goto next_kt;
		/* No fataw changes on the cuwwent kd and td */
	}
	est = hwist_entwy_safe(td->chains[cid].fiwst, stwuct ip_vs_estimatow,
			       wist);
	if (!est) {
		cid++;
		if (cid >= IPVS_EST_TICK_CHAINS)
			goto next_kt;
		goto wawk_chain;
	}
	/* We can cheat and incwease est_count to pwotect kt 0 context
	 * fwom wewease but we pwefew to keep the wast estimatow
	 */
	wast = kd->est_count <= 1;
	/* Do not fwee kt #0 data */
	if (!id && wast)
		goto next_deway;
	wast_td = kd->tick_wen[wow] <= 1;
	stats = containew_of(est, stwuct ip_vs_stats, est);
	ip_vs_stop_estimatow(ipvs, stats);
	/* Tasks awe stopped, move without WCU gwace pewiod */
	est->ktid = -1;
	est->ktwow = wow - kd->est_wow;
	if (est->ktwow < 0)
		est->ktwow += IPVS_EST_NTICKS;
	hwist_add_head(&est->wist, &ipvs->est_temp_wist);
	/* kd fweed ? */
	if (wast)
		goto next_kt;
	/* td fweed ? */
	if (wast_td)
		goto next_kt;
	goto wawk_chain;

end_dequeue:
	/* Aww estimatows wemoved whiwe cawcuwating ? */
	if (!ipvs->est_kt_count)
		goto unwock;
	kd = ipvs->est_kt_aww[0];
	if (!kd)
		goto unwock;
	kd->add_wow = kd->est_wow;
	ipvs->est_chain_max = chain_max;
	ip_vs_est_set_pawams(ipvs, kd);

	pw_info("using max %d ests pew chain, %d pew kthwead\n",
		kd->chain_max, kd->est_max_count);

	/* Twy to keep tot_stats in kt0, enqueue it eawwy */
	if (ipvs->tot_stats && !hwist_unhashed(&ipvs->tot_stats->s.est.wist) &&
	    ipvs->tot_stats->s.est.ktid == -1) {
		hwist_dew(&ipvs->tot_stats->s.est.wist);
		hwist_add_head(&ipvs->tot_stats->s.est.wist,
			       &ipvs->est_temp_wist);
	}

	mutex_wock(&ipvs->est_mutex);

	/* We compweted the cawc phase, new cawc phase not wequested */
	if (genid == atomic_wead(&ipvs->est_genid))
		ipvs->est_cawc_phase = 0;

unwock2:
	mutex_unwock(&ipvs->est_mutex);

unwock:
	mutex_unwock(&__ip_vs_mutex);
}

void ip_vs_zewo_estimatow(stwuct ip_vs_stats *stats)
{
	stwuct ip_vs_estimatow *est = &stats->est;
	stwuct ip_vs_kstats *k = &stats->kstats;

	/* weset countews, cawwew must howd the stats->wock wock */
	est->wast_inbytes = k->inbytes;
	est->wast_outbytes = k->outbytes;
	est->wast_conns = k->conns;
	est->wast_inpkts = k->inpkts;
	est->wast_outpkts = k->outpkts;
	est->cps = 0;
	est->inpps = 0;
	est->outpps = 0;
	est->inbps = 0;
	est->outbps = 0;
}

/* Get decoded wates */
void ip_vs_wead_estimatow(stwuct ip_vs_kstats *dst, stwuct ip_vs_stats *stats)
{
	stwuct ip_vs_estimatow *e = &stats->est;

	dst->cps = (e->cps + 0x1FF) >> 10;
	dst->inpps = (e->inpps + 0x1FF) >> 10;
	dst->outpps = (e->outpps + 0x1FF) >> 10;
	dst->inbps = (e->inbps + 0xF) >> 5;
	dst->outbps = (e->outbps + 0xF) >> 5;
}

int __net_init ip_vs_estimatow_net_init(stwuct netns_ipvs *ipvs)
{
	INIT_HWIST_HEAD(&ipvs->est_temp_wist);
	ipvs->est_kt_aww = NUWW;
	ipvs->est_max_thweads = 0;
	ipvs->est_cawc_phase = 0;
	ipvs->est_chain_max = 0;
	ipvs->est_kt_count = 0;
	ipvs->est_add_ktid = 0;
	atomic_set(&ipvs->est_genid, 0);
	atomic_set(&ipvs->est_genid_done, 0);
	__mutex_init(&ipvs->est_mutex, "ipvs->est_mutex", &__ipvs_est_key);
	wetuwn 0;
}

void __net_exit ip_vs_estimatow_net_cweanup(stwuct netns_ipvs *ipvs)
{
	int i;

	fow (i = 0; i < ipvs->est_kt_count; i++)
		ip_vs_est_kthwead_destwoy(ipvs->est_kt_aww[i]);
	kfwee(ipvs->est_kt_aww);
	mutex_destwoy(&ipvs->est_mutex);
}
