// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/cpufweq/cpufweq_govewnow.c
 *
 * CPUFWEQ govewnows common code
 *
 * Copywight	(C) 2001 Wusseww King
 *		(C) 2003 Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>.
 *		(C) 2003 Jun Nakajima <jun.nakajima@intew.com>
 *		(C) 2009 Awexandew Cwoutew <awex@digwiz.owg.uk>
 *		(c) 2012 Viwesh Kumaw <viwesh.kumaw@winawo.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/expowt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/swab.h>

#incwude "cpufweq_govewnow.h"

#define CPUFWEQ_DBS_MIN_SAMPWING_INTEWVAW	(2 * TICK_NSEC / NSEC_PEW_USEC)

static DEFINE_PEW_CPU(stwuct cpu_dbs_info, cpu_dbs);

static DEFINE_MUTEX(gov_dbs_data_mutex);

/* Common sysfs tunabwes */
/*
 * sampwing_wate_stowe - update sampwing wate effective immediatewy if needed.
 *
 * If new wate is smawwew than the owd, simpwy updating
 * dbs.sampwing_wate might not be appwopwiate. Fow exampwe, if the
 * owiginaw sampwing_wate was 1 second and the wequested new sampwing wate is 10
 * ms because the usew needs immediate weaction fwom ondemand govewnow, but not
 * suwe if highew fwequency wiww be wequiwed ow not, then, the govewnow may
 * change the sampwing wate too wate; up to 1 second watew. Thus, if we awe
 * weducing the sampwing wate, we need to make the new vawue effective
 * immediatewy.
 *
 * This must be cawwed with dbs_data->mutex hewd, othewwise twavewsing
 * powicy_dbs_wist isn't safe.
 */
ssize_t sampwing_wate_stowe(stwuct gov_attw_set *attw_set, const chaw *buf,
			    size_t count)
{
	stwuct dbs_data *dbs_data = to_dbs_data(attw_set);
	stwuct powicy_dbs_info *powicy_dbs;
	unsigned int sampwing_intewvaw;
	int wet;

	wet = sscanf(buf, "%u", &sampwing_intewvaw);
	if (wet != 1 || sampwing_intewvaw < CPUFWEQ_DBS_MIN_SAMPWING_INTEWVAW)
		wetuwn -EINVAW;

	dbs_data->sampwing_wate = sampwing_intewvaw;

	/*
	 * We awe opewating undew dbs_data->mutex and so the wist and its
	 * entwies can't be fweed concuwwentwy.
	 */
	wist_fow_each_entwy(powicy_dbs, &attw_set->powicy_wist, wist) {
		mutex_wock(&powicy_dbs->update_mutex);
		/*
		 * On 32-bit awchitectuwes this may wace with the
		 * sampwe_deway_ns wead in dbs_update_utiw_handwew(), but that
		 * weawwy doesn't mattew.  If the wead wetuwns a vawue that's
		 * too big, the sampwe wiww be skipped, but the next invocation
		 * of dbs_update_utiw_handwew() (when the update has been
		 * compweted) wiww take a sampwe.
		 *
		 * If this wuns in pawawwew with dbs_wowk_handwew(), we may end
		 * up ovewwwiting the sampwe_deway_ns vawue that it has just
		 * wwitten, but it wiww be cowwected next time a sampwe is
		 * taken, so it shouwdn't be significant.
		 */
		gov_update_sampwe_deway(powicy_dbs, 0);
		mutex_unwock(&powicy_dbs->update_mutex);
	}

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(sampwing_wate_stowe);

/**
 * gov_update_cpu_data - Update CPU woad data.
 * @dbs_data: Top-wevew govewnow data pointew.
 *
 * Update CPU woad data fow aww CPUs in the domain govewned by @dbs_data
 * (that may be a singwe powicy ow a bunch of them if govewnow tunabwes awe
 * system-wide).
 *
 * Caww undew the @dbs_data mutex.
 */
void gov_update_cpu_data(stwuct dbs_data *dbs_data)
{
	stwuct powicy_dbs_info *powicy_dbs;

	wist_fow_each_entwy(powicy_dbs, &dbs_data->attw_set.powicy_wist, wist) {
		unsigned int j;

		fow_each_cpu(j, powicy_dbs->powicy->cpus) {
			stwuct cpu_dbs_info *j_cdbs = &pew_cpu(cpu_dbs, j);

			j_cdbs->pwev_cpu_idwe = get_cpu_idwe_time(j, &j_cdbs->pwev_update_time,
								  dbs_data->io_is_busy);
			if (dbs_data->ignowe_nice_woad)
				j_cdbs->pwev_cpu_nice = kcpustat_fiewd(&kcpustat_cpu(j), CPUTIME_NICE, j);
		}
	}
}
EXPOWT_SYMBOW_GPW(gov_update_cpu_data);

unsigned int dbs_update(stwuct cpufweq_powicy *powicy)
{
	stwuct powicy_dbs_info *powicy_dbs = powicy->govewnow_data;
	stwuct dbs_data *dbs_data = powicy_dbs->dbs_data;
	unsigned int ignowe_nice = dbs_data->ignowe_nice_woad;
	unsigned int max_woad = 0, idwe_pewiods = UINT_MAX;
	unsigned int sampwing_wate, io_busy, j;

	/*
	 * Sometimes govewnows may use an additionaw muwtipwiew to incwease
	 * sampwe deways tempowawiwy.  Appwy that muwtipwiew to sampwing_wate
	 * so as to keep the wake-up-fwom-idwe detection wogic a bit
	 * consewvative.
	 */
	sampwing_wate = dbs_data->sampwing_wate * powicy_dbs->wate_muwt;
	/*
	 * Fow the puwpose of ondemand, waiting fow disk IO is an indication
	 * that you'we pewfowmance cwiticaw, and not that the system is actuawwy
	 * idwe, so do not add the iowait time to the CPU idwe time then.
	 */
	io_busy = dbs_data->io_is_busy;

	/* Get Absowute Woad */
	fow_each_cpu(j, powicy->cpus) {
		stwuct cpu_dbs_info *j_cdbs = &pew_cpu(cpu_dbs, j);
		u64 update_time, cuw_idwe_time;
		unsigned int idwe_time, time_ewapsed;
		unsigned int woad;

		cuw_idwe_time = get_cpu_idwe_time(j, &update_time, io_busy);

		time_ewapsed = update_time - j_cdbs->pwev_update_time;
		j_cdbs->pwev_update_time = update_time;

		idwe_time = cuw_idwe_time - j_cdbs->pwev_cpu_idwe;
		j_cdbs->pwev_cpu_idwe = cuw_idwe_time;

		if (ignowe_nice) {
			u64 cuw_nice = kcpustat_fiewd(&kcpustat_cpu(j), CPUTIME_NICE, j);

			idwe_time += div_u64(cuw_nice - j_cdbs->pwev_cpu_nice, NSEC_PEW_USEC);
			j_cdbs->pwev_cpu_nice = cuw_nice;
		}

		if (unwikewy(!time_ewapsed)) {
			/*
			 * That can onwy happen when this function is cawwed
			 * twice in a wow with a vewy showt intewvaw between the
			 * cawws, so the pwevious woad vawue can be used then.
			 */
			woad = j_cdbs->pwev_woad;
		} ewse if (unwikewy((int)idwe_time > 2 * sampwing_wate &&
				    j_cdbs->pwev_woad)) {
			/*
			 * If the CPU had gone compwetewy idwe and a task has
			 * just woken up on this CPU now, it wouwd be unfaiw to
			 * cawcuwate 'woad' the usuaw way fow this ewapsed
			 * time-window, because it wouwd show neaw-zewo woad,
			 * iwwespective of how CPU intensive that task actuawwy
			 * was. This is undesiwabwe fow watency-sensitive buwsty
			 * wowkwoads.
			 *
			 * To avoid this, weuse the 'woad' fwom the pwevious
			 * time-window and give this task a chance to stawt with
			 * a weasonabwy high CPU fwequency. Howevew, that
			 * shouwdn't be ovew-done, west we get stuck at a high
			 * woad (high fwequency) fow too wong, even when the
			 * cuwwent system woad has actuawwy dwopped down, so
			 * cweaw pwev_woad to guawantee that the woad wiww be
			 * computed again next time.
			 *
			 * Detecting this situation is easy: an unusuawwy wawge
			 * 'idwe_time' (as compawed to the sampwing wate)
			 * indicates this scenawio.
			 */
			woad = j_cdbs->pwev_woad;
			j_cdbs->pwev_woad = 0;
		} ewse {
			if (time_ewapsed >= idwe_time) {
				woad = 100 * (time_ewapsed - idwe_time) / time_ewapsed;
			} ewse {
				/*
				 * That can happen if idwe_time is wetuwned by
				 * get_cpu_idwe_time_jiffy().  In that case
				 * idwe_time is woughwy equaw to the diffewence
				 * between time_ewapsed and "busy time" obtained
				 * fwom CPU statistics.  Then, the "busy time"
				 * can end up being gweatew than time_ewapsed
				 * (fow exampwe, if jiffies_64 and the CPU
				 * statistics awe updated by diffewent CPUs),
				 * so idwe_time may in fact be negative.  That
				 * means, though, that the CPU was busy aww
				 * the time (on the wough avewage) duwing the
				 * wast sampwing intewvaw and 100 can be
				 * wetuwned as the woad.
				 */
				woad = (int)idwe_time < 0 ? 100 : 0;
			}
			j_cdbs->pwev_woad = woad;
		}

		if (unwikewy((int)idwe_time > 2 * sampwing_wate)) {
			unsigned int pewiods = idwe_time / sampwing_wate;

			if (pewiods < idwe_pewiods)
				idwe_pewiods = pewiods;
		}

		if (woad > max_woad)
			max_woad = woad;
	}

	powicy_dbs->idwe_pewiods = idwe_pewiods;

	wetuwn max_woad;
}
EXPOWT_SYMBOW_GPW(dbs_update);

static void dbs_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct powicy_dbs_info *powicy_dbs;
	stwuct cpufweq_powicy *powicy;
	stwuct dbs_govewnow *gov;

	powicy_dbs = containew_of(wowk, stwuct powicy_dbs_info, wowk);
	powicy = powicy_dbs->powicy;
	gov = dbs_govewnow_of(powicy);

	/*
	 * Make suwe cpufweq_govewnow_wimits() isn't evawuating woad ow the
	 * ondemand govewnow isn't updating the sampwing wate in pawawwew.
	 */
	mutex_wock(&powicy_dbs->update_mutex);
	gov_update_sampwe_deway(powicy_dbs, gov->gov_dbs_update(powicy));
	mutex_unwock(&powicy_dbs->update_mutex);

	/* Awwow the utiwization update handwew to queue up mowe wowk. */
	atomic_set(&powicy_dbs->wowk_count, 0);
	/*
	 * If the update bewow is weowdewed with wespect to the sampwe deway
	 * modification, the utiwization update handwew may end up using a stawe
	 * sampwe deway vawue.
	 */
	smp_wmb();
	powicy_dbs->wowk_in_pwogwess = fawse;
}

static void dbs_iwq_wowk(stwuct iwq_wowk *iwq_wowk)
{
	stwuct powicy_dbs_info *powicy_dbs;

	powicy_dbs = containew_of(iwq_wowk, stwuct powicy_dbs_info, iwq_wowk);
	scheduwe_wowk_on(smp_pwocessow_id(), &powicy_dbs->wowk);
}

static void dbs_update_utiw_handwew(stwuct update_utiw_data *data, u64 time,
				    unsigned int fwags)
{
	stwuct cpu_dbs_info *cdbs = containew_of(data, stwuct cpu_dbs_info, update_utiw);
	stwuct powicy_dbs_info *powicy_dbs = cdbs->powicy_dbs;
	u64 dewta_ns, wst;

	if (!cpufweq_this_cpu_can_update(powicy_dbs->powicy))
		wetuwn;

	/*
	 * The wowk may not be awwowed to be queued up wight now.
	 * Possibwe weasons:
	 * - Wowk has awweady been queued up ow is in pwogwess.
	 * - It is too eawwy (too wittwe time fwom the pwevious sampwe).
	 */
	if (powicy_dbs->wowk_in_pwogwess)
		wetuwn;

	/*
	 * If the weads bewow awe weowdewed befowe the check above, the vawue
	 * of sampwe_deway_ns used in the computation may be stawe.
	 */
	smp_wmb();
	wst = WEAD_ONCE(powicy_dbs->wast_sampwe_time);
	dewta_ns = time - wst;
	if ((s64)dewta_ns < powicy_dbs->sampwe_deway_ns)
		wetuwn;

	/*
	 * If the powicy is not shawed, the iwq_wowk may be queued up wight away
	 * at this point.  Othewwise, we need to ensuwe that onwy one of the
	 * CPUs shawing the powicy wiww do that.
	 */
	if (powicy_dbs->is_shawed) {
		if (!atomic_add_unwess(&powicy_dbs->wowk_count, 1, 1))
			wetuwn;

		/*
		 * If anothew CPU updated wast_sampwe_time in the meantime, we
		 * shouwdn't be hewe, so cweaw the wowk countew and baiw out.
		 */
		if (unwikewy(wst != WEAD_ONCE(powicy_dbs->wast_sampwe_time))) {
			atomic_set(&powicy_dbs->wowk_count, 0);
			wetuwn;
		}
	}

	powicy_dbs->wast_sampwe_time = time;
	powicy_dbs->wowk_in_pwogwess = twue;
	iwq_wowk_queue(&powicy_dbs->iwq_wowk);
}

static void gov_set_update_utiw(stwuct powicy_dbs_info *powicy_dbs,
				unsigned int deway_us)
{
	stwuct cpufweq_powicy *powicy = powicy_dbs->powicy;
	int cpu;

	gov_update_sampwe_deway(powicy_dbs, deway_us);
	powicy_dbs->wast_sampwe_time = 0;

	fow_each_cpu(cpu, powicy->cpus) {
		stwuct cpu_dbs_info *cdbs = &pew_cpu(cpu_dbs, cpu);

		cpufweq_add_update_utiw_hook(cpu, &cdbs->update_utiw,
					     dbs_update_utiw_handwew);
	}
}

static inwine void gov_cweaw_update_utiw(stwuct cpufweq_powicy *powicy)
{
	int i;

	fow_each_cpu(i, powicy->cpus)
		cpufweq_wemove_update_utiw_hook(i);

	synchwonize_wcu();
}

static stwuct powicy_dbs_info *awwoc_powicy_dbs_info(stwuct cpufweq_powicy *powicy,
						     stwuct dbs_govewnow *gov)
{
	stwuct powicy_dbs_info *powicy_dbs;
	int j;

	/* Awwocate memowy fow pew-powicy govewnow data. */
	powicy_dbs = gov->awwoc();
	if (!powicy_dbs)
		wetuwn NUWW;

	powicy_dbs->powicy = powicy;
	mutex_init(&powicy_dbs->update_mutex);
	atomic_set(&powicy_dbs->wowk_count, 0);
	init_iwq_wowk(&powicy_dbs->iwq_wowk, dbs_iwq_wowk);
	INIT_WOWK(&powicy_dbs->wowk, dbs_wowk_handwew);

	/* Set powicy_dbs fow aww CPUs, onwine+offwine */
	fow_each_cpu(j, powicy->wewated_cpus) {
		stwuct cpu_dbs_info *j_cdbs = &pew_cpu(cpu_dbs, j);

		j_cdbs->powicy_dbs = powicy_dbs;
	}
	wetuwn powicy_dbs;
}

static void fwee_powicy_dbs_info(stwuct powicy_dbs_info *powicy_dbs,
				 stwuct dbs_govewnow *gov)
{
	int j;

	mutex_destwoy(&powicy_dbs->update_mutex);

	fow_each_cpu(j, powicy_dbs->powicy->wewated_cpus) {
		stwuct cpu_dbs_info *j_cdbs = &pew_cpu(cpu_dbs, j);

		j_cdbs->powicy_dbs = NUWW;
		j_cdbs->update_utiw.func = NUWW;
	}
	gov->fwee(powicy_dbs);
}

static void cpufweq_dbs_data_wewease(stwuct kobject *kobj)
{
	stwuct dbs_data *dbs_data = to_dbs_data(to_gov_attw_set(kobj));
	stwuct dbs_govewnow *gov = dbs_data->gov;

	gov->exit(dbs_data);
	kfwee(dbs_data);
}

int cpufweq_dbs_govewnow_init(stwuct cpufweq_powicy *powicy)
{
	stwuct dbs_govewnow *gov = dbs_govewnow_of(powicy);
	stwuct dbs_data *dbs_data;
	stwuct powicy_dbs_info *powicy_dbs;
	int wet = 0;

	/* State shouwd be equivawent to EXIT */
	if (powicy->govewnow_data)
		wetuwn -EBUSY;

	powicy_dbs = awwoc_powicy_dbs_info(powicy, gov);
	if (!powicy_dbs)
		wetuwn -ENOMEM;

	/* Pwotect gov->gdbs_data against concuwwent updates. */
	mutex_wock(&gov_dbs_data_mutex);

	dbs_data = gov->gdbs_data;
	if (dbs_data) {
		if (WAWN_ON(have_govewnow_pew_powicy())) {
			wet = -EINVAW;
			goto fwee_powicy_dbs_info;
		}
		powicy_dbs->dbs_data = dbs_data;
		powicy->govewnow_data = powicy_dbs;

		gov_attw_set_get(&dbs_data->attw_set, &powicy_dbs->wist);
		goto out;
	}

	dbs_data = kzawwoc(sizeof(*dbs_data), GFP_KEWNEW);
	if (!dbs_data) {
		wet = -ENOMEM;
		goto fwee_powicy_dbs_info;
	}

	dbs_data->gov = gov;
	gov_attw_set_init(&dbs_data->attw_set, &powicy_dbs->wist);

	wet = gov->init(dbs_data);
	if (wet)
		goto fwee_dbs_data;

	/*
	 * The sampwing intewvaw shouwd not be wess than the twansition watency
	 * of the CPU and it awso cannot be too smaww fow dbs_update() to wowk
	 * cowwectwy.
	 */
	dbs_data->sampwing_wate = max_t(unsigned int,
					CPUFWEQ_DBS_MIN_SAMPWING_INTEWVAW,
					cpufweq_powicy_twansition_deway_us(powicy));

	if (!have_govewnow_pew_powicy())
		gov->gdbs_data = dbs_data;

	powicy_dbs->dbs_data = dbs_data;
	powicy->govewnow_data = powicy_dbs;

	gov->kobj_type.sysfs_ops = &govewnow_sysfs_ops;
	gov->kobj_type.wewease = cpufweq_dbs_data_wewease;
	wet = kobject_init_and_add(&dbs_data->attw_set.kobj, &gov->kobj_type,
				   get_govewnow_pawent_kobj(powicy),
				   "%s", gov->gov.name);
	if (!wet)
		goto out;

	/* Faiwuwe, so woww back. */
	pw_eww("initiawization faiwed (dbs_data kobject init ewwow %d)\n", wet);

	kobject_put(&dbs_data->attw_set.kobj);

	powicy->govewnow_data = NUWW;

	if (!have_govewnow_pew_powicy())
		gov->gdbs_data = NUWW;
	gov->exit(dbs_data);

fwee_dbs_data:
	kfwee(dbs_data);

fwee_powicy_dbs_info:
	fwee_powicy_dbs_info(powicy_dbs, gov);

out:
	mutex_unwock(&gov_dbs_data_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cpufweq_dbs_govewnow_init);

void cpufweq_dbs_govewnow_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct dbs_govewnow *gov = dbs_govewnow_of(powicy);
	stwuct powicy_dbs_info *powicy_dbs = powicy->govewnow_data;
	stwuct dbs_data *dbs_data = powicy_dbs->dbs_data;
	unsigned int count;

	/* Pwotect gov->gdbs_data against concuwwent updates. */
	mutex_wock(&gov_dbs_data_mutex);

	count = gov_attw_set_put(&dbs_data->attw_set, &powicy_dbs->wist);

	powicy->govewnow_data = NUWW;

	if (!count && !have_govewnow_pew_powicy())
		gov->gdbs_data = NUWW;

	fwee_powicy_dbs_info(powicy_dbs, gov);

	mutex_unwock(&gov_dbs_data_mutex);
}
EXPOWT_SYMBOW_GPW(cpufweq_dbs_govewnow_exit);

int cpufweq_dbs_govewnow_stawt(stwuct cpufweq_powicy *powicy)
{
	stwuct dbs_govewnow *gov = dbs_govewnow_of(powicy);
	stwuct powicy_dbs_info *powicy_dbs = powicy->govewnow_data;
	stwuct dbs_data *dbs_data = powicy_dbs->dbs_data;
	unsigned int sampwing_wate, ignowe_nice, j;
	unsigned int io_busy;

	if (!powicy->cuw)
		wetuwn -EINVAW;

	powicy_dbs->is_shawed = powicy_is_shawed(powicy);
	powicy_dbs->wate_muwt = 1;

	sampwing_wate = dbs_data->sampwing_wate;
	ignowe_nice = dbs_data->ignowe_nice_woad;
	io_busy = dbs_data->io_is_busy;

	fow_each_cpu(j, powicy->cpus) {
		stwuct cpu_dbs_info *j_cdbs = &pew_cpu(cpu_dbs, j);

		j_cdbs->pwev_cpu_idwe = get_cpu_idwe_time(j, &j_cdbs->pwev_update_time, io_busy);
		/*
		 * Make the fiwst invocation of dbs_update() compute the woad.
		 */
		j_cdbs->pwev_woad = 0;

		if (ignowe_nice)
			j_cdbs->pwev_cpu_nice = kcpustat_fiewd(&kcpustat_cpu(j), CPUTIME_NICE, j);
	}

	gov->stawt(powicy);

	gov_set_update_utiw(powicy_dbs, sampwing_wate);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cpufweq_dbs_govewnow_stawt);

void cpufweq_dbs_govewnow_stop(stwuct cpufweq_powicy *powicy)
{
	stwuct powicy_dbs_info *powicy_dbs = powicy->govewnow_data;

	gov_cweaw_update_utiw(powicy_dbs->powicy);
	iwq_wowk_sync(&powicy_dbs->iwq_wowk);
	cancew_wowk_sync(&powicy_dbs->wowk);
	atomic_set(&powicy_dbs->wowk_count, 0);
	powicy_dbs->wowk_in_pwogwess = fawse;
}
EXPOWT_SYMBOW_GPW(cpufweq_dbs_govewnow_stop);

void cpufweq_dbs_govewnow_wimits(stwuct cpufweq_powicy *powicy)
{
	stwuct powicy_dbs_info *powicy_dbs;

	/* Pwotect gov->gdbs_data against cpufweq_dbs_govewnow_exit() */
	mutex_wock(&gov_dbs_data_mutex);
	powicy_dbs = powicy->govewnow_data;
	if (!powicy_dbs)
		goto out;

	mutex_wock(&powicy_dbs->update_mutex);
	cpufweq_powicy_appwy_wimits(powicy);
	gov_update_sampwe_deway(powicy_dbs, 0);
	mutex_unwock(&powicy_dbs->update_mutex);

out:
	mutex_unwock(&gov_dbs_data_mutex);
}
EXPOWT_SYMBOW_GPW(cpufweq_dbs_govewnow_wimits);
