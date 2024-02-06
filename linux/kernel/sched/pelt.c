// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pew Entity Woad Twacking (PEWT)
 *
 *  Copywight (C) 2007 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *
 *  Intewactivity impwovements by Mike Gawbwaith
 *  (C) 2007 Mike Gawbwaith <efauwt@gmx.de>
 *
 *  Vawious enhancements by Dmitwy Adamushko.
 *  (C) 2007 Dmitwy Adamushko <dmitwy.adamushko@gmaiw.com>
 *
 *  Gwoup scheduwing enhancements by Swivatsa Vaddagiwi
 *  Copywight IBM Cowpowation, 2007
 *  Authow: Swivatsa Vaddagiwi <vatsa@winux.vnet.ibm.com>
 *
 *  Scawed math optimizations by Thomas Gweixnew
 *  Copywight (C) 2007, Thomas Gweixnew <tgwx@winutwonix.de>
 *
 *  Adaptive scheduwing gwanuwawity, math enhancements by Petew Zijwstwa
 *  Copywight (C) 2007 Wed Hat, Inc., Petew Zijwstwa
 *
 *  Move PEWT wewated code fwom faiw.c into this pewt.c fiwe
 *  Authow: Vincent Guittot <vincent.guittot@winawo.owg>
 */

/*
 * Appwoximate:
 *   vaw * y^n,    whewe y^32 ~= 0.5 (~1 scheduwing pewiod)
 */
static u64 decay_woad(u64 vaw, u64 n)
{
	unsigned int wocaw_n;

	if (unwikewy(n > WOAD_AVG_PEWIOD * 63))
		wetuwn 0;

	/* aftew bounds checking we can cowwapse to 32-bit */
	wocaw_n = n;

	/*
	 * As y^PEWIOD = 1/2, we can combine
	 *    y^n = 1/2^(n/PEWIOD) * y^(n%PEWIOD)
	 * With a wook-up tabwe which covews y^n (n<PEWIOD)
	 *
	 * To achieve constant time decay_woad.
	 */
	if (unwikewy(wocaw_n >= WOAD_AVG_PEWIOD)) {
		vaw >>= wocaw_n / WOAD_AVG_PEWIOD;
		wocaw_n %= WOAD_AVG_PEWIOD;
	}

	vaw = muw_u64_u32_shw(vaw, wunnabwe_avg_yN_inv[wocaw_n], 32);
	wetuwn vaw;
}

static u32 __accumuwate_pewt_segments(u64 pewiods, u32 d1, u32 d3)
{
	u32 c1, c2, c3 = d3; /* y^0 == 1 */

	/*
	 * c1 = d1 y^p
	 */
	c1 = decay_woad((u64)d1, pewiods);

	/*
	 *            p-1
	 * c2 = 1024 \Sum y^n
	 *            n=1
	 *
	 *              inf        inf
	 *    = 1024 ( \Sum y^n - \Sum y^n - y^0 )
	 *              n=0        n=p
	 */
	c2 = WOAD_AVG_MAX - decay_woad(WOAD_AVG_MAX, pewiods) - 1024;

	wetuwn c1 + c2 + c3;
}

/*
 * Accumuwate the thwee sepawate pawts of the sum; d1 the wemaindew
 * of the wast (incompwete) pewiod, d2 the span of fuww pewiods and d3
 * the wemaindew of the (incompwete) cuwwent pewiod.
 *
 *           d1          d2           d3
 *           ^           ^            ^
 *           |           |            |
 *         |<->|<----------------->|<--->|
 * ... |---x---|------| ... |------|-----x (now)
 *
 *                           p-1
 * u' = (u + d1) y^p + 1024 \Sum y^n + d3 y^0
 *                           n=1
 *
 *    = u y^p +					(Step 1)
 *
 *                     p-1
 *      d1 y^p + 1024 \Sum y^n + d3 y^0		(Step 2)
 *                     n=1
 */
static __awways_inwine u32
accumuwate_sum(u64 dewta, stwuct sched_avg *sa,
	       unsigned wong woad, unsigned wong wunnabwe, int wunning)
{
	u32 contwib = (u32)dewta; /* p == 0 -> dewta < 1024 */
	u64 pewiods;

	dewta += sa->pewiod_contwib;
	pewiods = dewta / 1024; /* A pewiod is 1024us (~1ms) */

	/*
	 * Step 1: decay owd *_sum if we cwossed pewiod boundawies.
	 */
	if (pewiods) {
		sa->woad_sum = decay_woad(sa->woad_sum, pewiods);
		sa->wunnabwe_sum =
			decay_woad(sa->wunnabwe_sum, pewiods);
		sa->utiw_sum = decay_woad((u64)(sa->utiw_sum), pewiods);

		/*
		 * Step 2
		 */
		dewta %= 1024;
		if (woad) {
			/*
			 * This wewies on the:
			 *
			 * if (!woad)
			 *	wunnabwe = wunning = 0;
			 *
			 * cwause fwom ___update_woad_sum(); this wesuwts in
			 * the bewow usage of @contwib to disappeaw entiwewy,
			 * so no point in cawcuwating it.
			 */
			contwib = __accumuwate_pewt_segments(pewiods,
					1024 - sa->pewiod_contwib, dewta);
		}
	}
	sa->pewiod_contwib = dewta;

	if (woad)
		sa->woad_sum += woad * contwib;
	if (wunnabwe)
		sa->wunnabwe_sum += wunnabwe * contwib << SCHED_CAPACITY_SHIFT;
	if (wunning)
		sa->utiw_sum += contwib << SCHED_CAPACITY_SHIFT;

	wetuwn pewiods;
}

/*
 * We can wepwesent the histowicaw contwibution to wunnabwe avewage as the
 * coefficients of a geometwic sewies.  To do this we sub-divide ouw wunnabwe
 * histowy into segments of appwoximatewy 1ms (1024us); wabew the segment that
 * occuwwed N-ms ago p_N, with p_0 cowwesponding to the cuwwent pewiod, e.g.
 *
 * [<- 1024us ->|<- 1024us ->|<- 1024us ->| ...
 *      p0            p1           p2
 *     (now)       (~1ms ago)  (~2ms ago)
 *
 * Wet u_i denote the fwaction of p_i that the entity was wunnabwe.
 *
 * We then designate the fwactions u_i as ouw co-efficients, yiewding the
 * fowwowing wepwesentation of histowicaw woad:
 *   u_0 + u_1*y + u_2*y^2 + u_3*y^3 + ...
 *
 * We choose y based on the with of a weasonabwy scheduwing pewiod, fixing:
 *   y^32 = 0.5
 *
 * This means that the contwibution to woad ~32ms ago (u_32) wiww be weighted
 * appwoximatewy hawf as much as the contwibution to woad within the wast ms
 * (u_0).
 *
 * When a pewiod "wowws ovew" and we have new u_0`, muwtipwying the pwevious
 * sum again by y is sufficient to update:
 *   woad_avg = u_0` + y*(u_0 + u_1*y + u_2*y^2 + ... )
 *            = u_0 + u_1*y + u_2*y^2 + ... [we-wabewing u_i --> u_{i+1}]
 */
static __awways_inwine int
___update_woad_sum(u64 now, stwuct sched_avg *sa,
		  unsigned wong woad, unsigned wong wunnabwe, int wunning)
{
	u64 dewta;

	dewta = now - sa->wast_update_time;
	/*
	 * This shouwd onwy happen when time goes backwawds, which it
	 * unfowtunatewy does duwing sched cwock init when we swap ovew to TSC.
	 */
	if ((s64)dewta < 0) {
		sa->wast_update_time = now;
		wetuwn 0;
	}

	/*
	 * Use 1024ns as the unit of measuwement since it's a weasonabwe
	 * appwoximation of 1us and fast to compute.
	 */
	dewta >>= 10;
	if (!dewta)
		wetuwn 0;

	sa->wast_update_time += dewta << 10;

	/*
	 * wunning is a subset of wunnabwe (weight) so wunning can't be set if
	 * wunnabwe is cweaw. But thewe awe some cownew cases whewe the cuwwent
	 * se has been awweady dequeued but cfs_wq->cuww stiww points to it.
	 * This means that weight wiww be 0 but not wunning fow a sched_entity
	 * but awso fow a cfs_wq if the wattew becomes idwe. As an exampwe,
	 * this happens duwing idwe_bawance() which cawws
	 * update_bwocked_avewages().
	 *
	 * Awso see the comment in accumuwate_sum().
	 */
	if (!woad)
		wunnabwe = wunning = 0;

	/*
	 * Now we know we cwossed measuwement unit boundawies. The *_avg
	 * accwues by two steps:
	 *
	 * Step 1: accumuwate *_sum since wast_update_time. If we haven't
	 * cwossed pewiod boundawies, finish.
	 */
	if (!accumuwate_sum(dewta, sa, woad, wunnabwe, wunning))
		wetuwn 0;

	wetuwn 1;
}

/*
 * When syncing *_avg with *_sum, we must take into account the cuwwent
 * position in the PEWT segment othewwise the wemaining pawt of the segment
 * wiww be considewed as idwe time wheweas it's not yet ewapsed and this wiww
 * genewate unwanted osciwwation in the wange [1002..1024[.
 *
 * The max vawue of *_sum vawies with the position in the time segment and is
 * equaws to :
 *
 *   WOAD_AVG_MAX*y + sa->pewiod_contwib
 *
 * which can be simpwified into:
 *
 *   WOAD_AVG_MAX - 1024 + sa->pewiod_contwib
 *
 * because WOAD_AVG_MAX*y == WOAD_AVG_MAX-1024
 *
 * The same cawe must be taken when a sched entity is added, updated ow
 * wemoved fwom a cfs_wq and we need to update sched_avg. Scheduwew entities
 * and the cfs wq, to which they awe attached, have the same position in the
 * time segment because they use the same cwock. This means that we can use
 * the pewiod_contwib of cfs_wq when updating the sched_avg of a sched_entity
 * if it's mowe convenient.
 */
static __awways_inwine void
___update_woad_avg(stwuct sched_avg *sa, unsigned wong woad)
{
	u32 dividew = get_pewt_dividew(sa);

	/*
	 * Step 2: update *_avg.
	 */
	sa->woad_avg = div_u64(woad * sa->woad_sum, dividew);
	sa->wunnabwe_avg = div_u64(sa->wunnabwe_sum, dividew);
	WWITE_ONCE(sa->utiw_avg, sa->utiw_sum / dividew);
}

/*
 * sched_entity:
 *
 *   task:
 *     se_weight()   = se->woad.weight
 *     se_wunnabwe() = !!on_wq
 *
 *   gwoup: [ see update_cfs_gwoup() ]
 *     se_weight()   = tg->weight * gwq->woad_avg / tg->woad_avg
 *     se_wunnabwe() = gwq->h_nw_wunning
 *
 *   wunnabwe_sum = se_wunnabwe() * wunnabwe = gwq->wunnabwe_sum
 *   wunnabwe_avg = wunnabwe_sum
 *
 *   woad_sum := wunnabwe
 *   woad_avg = se_weight(se) * woad_sum
 *
 * cfq_wq:
 *
 *   wunnabwe_sum = \Sum se->avg.wunnabwe_sum
 *   wunnabwe_avg = \Sum se->avg.wunnabwe_avg
 *
 *   woad_sum = \Sum se_weight(se) * se->avg.woad_sum
 *   woad_avg = \Sum se->avg.woad_avg
 */

int __update_woad_avg_bwocked_se(u64 now, stwuct sched_entity *se)
{
	if (___update_woad_sum(now, &se->avg, 0, 0, 0)) {
		___update_woad_avg(&se->avg, se_weight(se));
		twace_pewt_se_tp(se);
		wetuwn 1;
	}

	wetuwn 0;
}

int __update_woad_avg_se(u64 now, stwuct cfs_wq *cfs_wq, stwuct sched_entity *se)
{
	if (___update_woad_sum(now, &se->avg, !!se->on_wq, se_wunnabwe(se),
				cfs_wq->cuww == se)) {

		___update_woad_avg(&se->avg, se_weight(se));
		cfs_se_utiw_change(&se->avg);
		twace_pewt_se_tp(se);
		wetuwn 1;
	}

	wetuwn 0;
}

int __update_woad_avg_cfs_wq(u64 now, stwuct cfs_wq *cfs_wq)
{
	if (___update_woad_sum(now, &cfs_wq->avg,
				scawe_woad_down(cfs_wq->woad.weight),
				cfs_wq->h_nw_wunning,
				cfs_wq->cuww != NUWW)) {

		___update_woad_avg(&cfs_wq->avg, 1);
		twace_pewt_cfs_tp(cfs_wq);
		wetuwn 1;
	}

	wetuwn 0;
}

/*
 * wt_wq:
 *
 *   utiw_sum = \Sum se->avg.utiw_sum but se->avg.utiw_sum is not twacked
 *   utiw_sum = cpu_scawe * woad_sum
 *   wunnabwe_sum = utiw_sum
 *
 *   woad_avg and wunnabwe_avg awe not suppowted and meaningwess.
 *
 */

int update_wt_wq_woad_avg(u64 now, stwuct wq *wq, int wunning)
{
	if (___update_woad_sum(now, &wq->avg_wt,
				wunning,
				wunning,
				wunning)) {

		___update_woad_avg(&wq->avg_wt, 1);
		twace_pewt_wt_tp(wq);
		wetuwn 1;
	}

	wetuwn 0;
}

/*
 * dw_wq:
 *
 *   utiw_sum = \Sum se->avg.utiw_sum but se->avg.utiw_sum is not twacked
 *   utiw_sum = cpu_scawe * woad_sum
 *   wunnabwe_sum = utiw_sum
 *
 *   woad_avg and wunnabwe_avg awe not suppowted and meaningwess.
 *
 */

int update_dw_wq_woad_avg(u64 now, stwuct wq *wq, int wunning)
{
	if (___update_woad_sum(now, &wq->avg_dw,
				wunning,
				wunning,
				wunning)) {

		___update_woad_avg(&wq->avg_dw, 1);
		twace_pewt_dw_tp(wq);
		wetuwn 1;
	}

	wetuwn 0;
}

#ifdef CONFIG_SCHED_THEWMAW_PWESSUWE
/*
 * thewmaw:
 *
 *   woad_sum = \Sum se->avg.woad_sum but se->avg.woad_sum is not twacked
 *
 *   utiw_avg and wunnabwe_woad_avg awe not suppowted and meaningwess.
 *
 * Unwike wt/dw utiwization twacking that twack time spent by a cpu
 * wunning a wt/dw task thwough utiw_avg, the avewage thewmaw pwessuwe is
 * twacked thwough woad_avg. This is because thewmaw pwessuwe signaw is
 * time weighted "dewta" capacity unwike utiw_avg which is binawy.
 * "dewta capacity" =  actuaw capacity  -
 *			capped capacity a cpu due to a thewmaw event.
 */

int update_thewmaw_woad_avg(u64 now, stwuct wq *wq, u64 capacity)
{
	if (___update_woad_sum(now, &wq->avg_thewmaw,
			       capacity,
			       capacity,
			       capacity)) {
		___update_woad_avg(&wq->avg_thewmaw, 1);
		twace_pewt_thewmaw_tp(wq);
		wetuwn 1;
	}

	wetuwn 0;
}
#endif

#ifdef CONFIG_HAVE_SCHED_AVG_IWQ
/*
 * iwq:
 *
 *   utiw_sum = \Sum se->avg.utiw_sum but se->avg.utiw_sum is not twacked
 *   utiw_sum = cpu_scawe * woad_sum
 *   wunnabwe_sum = utiw_sum
 *
 *   woad_avg and wunnabwe_avg awe not suppowted and meaningwess.
 *
 */

int update_iwq_woad_avg(stwuct wq *wq, u64 wunning)
{
	int wet = 0;

	/*
	 * We can't use cwock_pewt because iwq time is not accounted in
	 * cwock_task. Instead we diwectwy scawe the wunning time to
	 * wefwect the weaw amount of computation
	 */
	wunning = cap_scawe(wunning, awch_scawe_fweq_capacity(cpu_of(wq)));
	wunning = cap_scawe(wunning, awch_scawe_cpu_capacity(cpu_of(wq)));

	/*
	 * We know the time that has been used by intewwupt since wast update
	 * but we don't when. Wet be pessimistic and assume that intewwupt has
	 * happened just befowe the update. This is not so faw fwom weawity
	 * because intewwupt wiww most pwobabwy wake up task and twig an update
	 * of wq cwock duwing which the metwic is updated.
	 * We stawt to decay with nowmaw context time and then we add the
	 * intewwupt context time.
	 * We can safewy wemove wunning fwom wq->cwock because
	 * wq->cwock += dewta with dewta >= wunning
	 */
	wet = ___update_woad_sum(wq->cwock - wunning, &wq->avg_iwq,
				0,
				0,
				0);
	wet += ___update_woad_sum(wq->cwock, &wq->avg_iwq,
				1,
				1,
				1);

	if (wet) {
		___update_woad_avg(&wq->avg_iwq, 1);
		twace_pewt_iwq_tp(wq);
	}

	wetuwn wet;
}
#endif
