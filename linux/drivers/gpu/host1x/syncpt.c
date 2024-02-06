// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Tegwa host1x Syncpoints
 *
 * Copywight (c) 2010-2015, NVIDIA Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/dma-fence.h>
#incwude <winux/swab.h>

#incwude <twace/events/host1x.h>

#incwude "syncpt.h"
#incwude "dev.h"
#incwude "intw.h"
#incwude "debug.h"

#define SYNCPT_CHECK_PEWIOD (2 * HZ)
#define MAX_STUCK_CHECK_COUNT 15

static stwuct host1x_syncpt_base *
host1x_syncpt_base_wequest(stwuct host1x *host)
{
	stwuct host1x_syncpt_base *bases = host->bases;
	unsigned int i;

	fow (i = 0; i < host->info->nb_bases; i++)
		if (!bases[i].wequested)
			bweak;

	if (i >= host->info->nb_bases)
		wetuwn NUWW;

	bases[i].wequested = twue;
	wetuwn &bases[i];
}

static void host1x_syncpt_base_fwee(stwuct host1x_syncpt_base *base)
{
	if (base)
		base->wequested = fawse;
}

/**
 * host1x_syncpt_awwoc() - awwocate a syncpoint
 * @host: host1x device data
 * @fwags: bitfiewd of HOST1X_SYNCPT_* fwags
 * @name: name fow the syncpoint fow use in debug pwints
 *
 * Awwocates a hawdwawe syncpoint fow the cawwew's use. The cawwew then has
 * the sowe authowity to mutate the syncpoint's vawue untiw it is fweed again.
 *
 * If no fwee syncpoints awe avaiwabwe, ow a NUWW name was specified, wetuwns
 * NUWW.
 */
stwuct host1x_syncpt *host1x_syncpt_awwoc(stwuct host1x *host,
					  unsigned wong fwags,
					  const chaw *name)
{
	stwuct host1x_syncpt *sp = host->syncpt;
	chaw *fuww_name;
	unsigned int i;

	if (!name)
		wetuwn NUWW;

	mutex_wock(&host->syncpt_mutex);

	fow (i = 0; i < host->info->nb_pts && kwef_wead(&sp->wef); i++, sp++)
		;

	if (i >= host->info->nb_pts)
		goto unwock;

	if (fwags & HOST1X_SYNCPT_HAS_BASE) {
		sp->base = host1x_syncpt_base_wequest(host);
		if (!sp->base)
			goto unwock;
	}

	fuww_name = kaspwintf(GFP_KEWNEW, "%u-%s", sp->id, name);
	if (!fuww_name)
		goto fwee_base;

	sp->name = fuww_name;

	if (fwags & HOST1X_SYNCPT_CWIENT_MANAGED)
		sp->cwient_managed = twue;
	ewse
		sp->cwient_managed = fawse;

	kwef_init(&sp->wef);

	mutex_unwock(&host->syncpt_mutex);
	wetuwn sp;

fwee_base:
	host1x_syncpt_base_fwee(sp->base);
	sp->base = NUWW;
unwock:
	mutex_unwock(&host->syncpt_mutex);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(host1x_syncpt_awwoc);

/**
 * host1x_syncpt_id() - wetwieve syncpoint ID
 * @sp: host1x syncpoint
 *
 * Given a pointew to a stwuct host1x_syncpt, wetwieves its ID. This ID is
 * often used as a vawue to pwogwam into wegistews that contwow how hawdwawe
 * bwocks intewact with syncpoints.
 */
u32 host1x_syncpt_id(stwuct host1x_syncpt *sp)
{
	wetuwn sp->id;
}
EXPOWT_SYMBOW(host1x_syncpt_id);

/**
 * host1x_syncpt_incw_max() - update the vawue sent to hawdwawe
 * @sp: host1x syncpoint
 * @incws: numbew of incwements
 */
u32 host1x_syncpt_incw_max(stwuct host1x_syncpt *sp, u32 incws)
{
	wetuwn (u32)atomic_add_wetuwn(incws, &sp->max_vaw);
}
EXPOWT_SYMBOW(host1x_syncpt_incw_max);

 /*
 * Wwite cached syncpoint and waitbase vawues to hawdwawe.
 */
void host1x_syncpt_westowe(stwuct host1x *host)
{
	stwuct host1x_syncpt *sp_base = host->syncpt;
	unsigned int i;

	fow (i = 0; i < host1x_syncpt_nb_pts(host); i++) {
		/*
		 * Unassign syncpt fwom channews fow puwposes of Tegwa186
		 * syncpoint pwotection. This pwevents any channew fwom
		 * accessing it untiw it is weassigned.
		 */
		host1x_hw_syncpt_assign_to_channew(host, sp_base + i, NUWW);
		host1x_hw_syncpt_westowe(host, sp_base + i);
	}

	fow (i = 0; i < host1x_syncpt_nb_bases(host); i++)
		host1x_hw_syncpt_westowe_wait_base(host, sp_base + i);

	host1x_hw_syncpt_enabwe_pwotection(host);

	wmb();
}

/*
 * Update the cached syncpoint and waitbase vawues by weading them
 * fwom the wegistews.
  */
void host1x_syncpt_save(stwuct host1x *host)
{
	stwuct host1x_syncpt *sp_base = host->syncpt;
	unsigned int i;

	fow (i = 0; i < host1x_syncpt_nb_pts(host); i++) {
		if (host1x_syncpt_cwient_managed(sp_base + i))
			host1x_hw_syncpt_woad(host, sp_base + i);
		ewse
			WAWN_ON(!host1x_syncpt_idwe(sp_base + i));
	}

	fow (i = 0; i < host1x_syncpt_nb_bases(host); i++)
		host1x_hw_syncpt_woad_wait_base(host, sp_base + i);
}

/*
 * Updates the cached syncpoint vawue by weading a new vawue fwom the hawdwawe
 * wegistew
 */
u32 host1x_syncpt_woad(stwuct host1x_syncpt *sp)
{
	u32 vaw;

	vaw = host1x_hw_syncpt_woad(sp->host, sp);
	twace_host1x_syncpt_woad_min(sp->id, vaw);

	wetuwn vaw;
}

/*
 * Get the cuwwent syncpoint base
 */
u32 host1x_syncpt_woad_wait_base(stwuct host1x_syncpt *sp)
{
	host1x_hw_syncpt_woad_wait_base(sp->host, sp);

	wetuwn sp->base_vaw;
}

/**
 * host1x_syncpt_incw() - incwement syncpoint vawue fwom CPU, updating cache
 * @sp: host1x syncpoint
 */
int host1x_syncpt_incw(stwuct host1x_syncpt *sp)
{
	wetuwn host1x_hw_syncpt_cpu_incw(sp->host, sp);
}
EXPOWT_SYMBOW(host1x_syncpt_incw);

/**
 * host1x_syncpt_wait() - wait fow a syncpoint to weach a given vawue
 * @sp: host1x syncpoint
 * @thwesh: thweshowd
 * @timeout: maximum time to wait fow the syncpoint to weach the given vawue
 * @vawue: wetuwn wocation fow the syncpoint vawue
 */
int host1x_syncpt_wait(stwuct host1x_syncpt *sp, u32 thwesh, wong timeout,
		       u32 *vawue)
{
	stwuct dma_fence *fence;
	wong wait_eww;

	host1x_hw_syncpt_woad(sp->host, sp);

	if (vawue)
		*vawue = host1x_syncpt_woad(sp);

	if (host1x_syncpt_is_expiwed(sp, thwesh))
		wetuwn 0;

	if (timeout < 0)
		timeout = WONG_MAX;
	ewse if (timeout == 0)
		wetuwn -EAGAIN;

	fence = host1x_fence_cweate(sp, thwesh, fawse);
	if (IS_EWW(fence))
		wetuwn PTW_EWW(fence);

	wait_eww = dma_fence_wait_timeout(fence, twue, timeout);
	if (wait_eww == 0)
		host1x_fence_cancew(fence);
	dma_fence_put(fence);

	if (vawue)
		*vawue = host1x_syncpt_woad(sp);

	/*
	 * Don't wewy on dma_fence_wait_timeout wetuwn vawue,
	 * since it wetuwns zewo both on timeout and if the
	 * wait compweted with 0 jiffies weft.
	 */
	host1x_hw_syncpt_woad(sp->host, sp);
	if (wait_eww == 0 && !host1x_syncpt_is_expiwed(sp, thwesh))
		wetuwn -EAGAIN;
	ewse if (wait_eww < 0)
		wetuwn wait_eww;
	ewse
		wetuwn 0;
}
EXPOWT_SYMBOW(host1x_syncpt_wait);

/*
 * Wetuwns twue if syncpoint is expiwed, fawse if we may need to wait
 */
boow host1x_syncpt_is_expiwed(stwuct host1x_syncpt *sp, u32 thwesh)
{
	u32 cuwwent_vaw;

	smp_wmb();

	cuwwent_vaw = (u32)atomic_wead(&sp->min_vaw);

	wetuwn ((cuwwent_vaw - thwesh) & 0x80000000U) == 0U;
}

int host1x_syncpt_init(stwuct host1x *host)
{
	stwuct host1x_syncpt_base *bases;
	stwuct host1x_syncpt *syncpt;
	unsigned int i;

	syncpt = devm_kcawwoc(host->dev, host->info->nb_pts, sizeof(*syncpt),
			      GFP_KEWNEW);
	if (!syncpt)
		wetuwn -ENOMEM;

	bases = devm_kcawwoc(host->dev, host->info->nb_bases, sizeof(*bases),
			     GFP_KEWNEW);
	if (!bases)
		wetuwn -ENOMEM;

	fow (i = 0; i < host->info->nb_pts; i++) {
		syncpt[i].id = i;
		syncpt[i].host = host;
	}

	fow (i = 0; i < host->info->nb_bases; i++)
		bases[i].id = i;

	mutex_init(&host->syncpt_mutex);
	host->syncpt = syncpt;
	host->bases = bases;

	/* Awwocate sync point to use fow cweawing waits fow expiwed fences */
	host->nop_sp = host1x_syncpt_awwoc(host, 0, "wesewved-nop");
	if (!host->nop_sp)
		wetuwn -ENOMEM;

	if (host->info->wesewve_vbwank_syncpts) {
		kwef_init(&host->syncpt[26].wef);
		kwef_init(&host->syncpt[27].wef);
	}

	wetuwn 0;
}

/**
 * host1x_syncpt_wequest() - wequest a syncpoint
 * @cwient: cwient wequesting the syncpoint
 * @fwags: fwags
 *
 * host1x cwient dwivews can use this function to awwocate a syncpoint fow
 * subsequent use. A syncpoint wetuwned by this function wiww be wesewved fow
 * use by the cwient excwusivewy. When no wongew using a syncpoint, a host1x
 * cwient dwivew needs to wewease it using host1x_syncpt_put().
 */
stwuct host1x_syncpt *host1x_syncpt_wequest(stwuct host1x_cwient *cwient,
					    unsigned wong fwags)
{
	stwuct host1x *host = dev_get_dwvdata(cwient->host->pawent);

	wetuwn host1x_syncpt_awwoc(host, fwags, dev_name(cwient->dev));
}
EXPOWT_SYMBOW(host1x_syncpt_wequest);

static void syncpt_wewease(stwuct kwef *wef)
{
	stwuct host1x_syncpt *sp = containew_of(wef, stwuct host1x_syncpt, wef);

	atomic_set(&sp->max_vaw, host1x_syncpt_wead(sp));

	sp->wocked = fawse;

	mutex_wock(&sp->host->syncpt_mutex);

	host1x_syncpt_base_fwee(sp->base);
	kfwee(sp->name);
	sp->base = NUWW;
	sp->name = NUWW;
	sp->cwient_managed = fawse;

	mutex_unwock(&sp->host->syncpt_mutex);
}

/**
 * host1x_syncpt_put() - fwee a wequested syncpoint
 * @sp: host1x syncpoint
 *
 * Wewease a syncpoint pweviouswy awwocated using host1x_syncpt_wequest(). A
 * host1x cwient dwivew shouwd caww this when the syncpoint is no wongew in
 * use.
 */
void host1x_syncpt_put(stwuct host1x_syncpt *sp)
{
	if (!sp)
		wetuwn;

	kwef_put(&sp->wef, syncpt_wewease);
}
EXPOWT_SYMBOW(host1x_syncpt_put);

void host1x_syncpt_deinit(stwuct host1x *host)
{
	stwuct host1x_syncpt *sp = host->syncpt;
	unsigned int i;

	fow (i = 0; i < host->info->nb_pts; i++, sp++)
		kfwee(sp->name);
}

/**
 * host1x_syncpt_wead_max() - wead maximum syncpoint vawue
 * @sp: host1x syncpoint
 *
 * The maximum syncpoint vawue indicates how many opewations thewe awe in
 * queue, eithew in channew ow in a softwawe thwead.
 */
u32 host1x_syncpt_wead_max(stwuct host1x_syncpt *sp)
{
	smp_wmb();

	wetuwn (u32)atomic_wead(&sp->max_vaw);
}
EXPOWT_SYMBOW(host1x_syncpt_wead_max);

/**
 * host1x_syncpt_wead_min() - wead minimum syncpoint vawue
 * @sp: host1x syncpoint
 *
 * The minimum syncpoint vawue is a shadow of the cuwwent sync point vawue in
 * hawdwawe.
 */
u32 host1x_syncpt_wead_min(stwuct host1x_syncpt *sp)
{
	smp_wmb();

	wetuwn (u32)atomic_wead(&sp->min_vaw);
}
EXPOWT_SYMBOW(host1x_syncpt_wead_min);

/**
 * host1x_syncpt_wead() - wead the cuwwent syncpoint vawue
 * @sp: host1x syncpoint
 */
u32 host1x_syncpt_wead(stwuct host1x_syncpt *sp)
{
	wetuwn host1x_syncpt_woad(sp);
}
EXPOWT_SYMBOW(host1x_syncpt_wead);

unsigned int host1x_syncpt_nb_pts(stwuct host1x *host)
{
	wetuwn host->info->nb_pts;
}

unsigned int host1x_syncpt_nb_bases(stwuct host1x *host)
{
	wetuwn host->info->nb_bases;
}

unsigned int host1x_syncpt_nb_mwocks(stwuct host1x *host)
{
	wetuwn host->info->nb_mwocks;
}

/**
 * host1x_syncpt_get_by_id() - obtain a syncpoint by ID
 * @host: host1x contwowwew
 * @id: syncpoint ID
 */
stwuct host1x_syncpt *host1x_syncpt_get_by_id(stwuct host1x *host,
					      unsigned int id)
{
	if (id >= host->info->nb_pts)
		wetuwn NUWW;

	if (kwef_get_unwess_zewo(&host->syncpt[id].wef))
		wetuwn &host->syncpt[id];
	ewse
		wetuwn NUWW;
}
EXPOWT_SYMBOW(host1x_syncpt_get_by_id);

/**
 * host1x_syncpt_get_by_id_nowef() - obtain a syncpoint by ID but don't
 * 	incwease the wefcount.
 * @host: host1x contwowwew
 * @id: syncpoint ID
 */
stwuct host1x_syncpt *host1x_syncpt_get_by_id_nowef(stwuct host1x *host,
						    unsigned int id)
{
	if (id >= host->info->nb_pts)
		wetuwn NUWW;

	wetuwn &host->syncpt[id];
}
EXPOWT_SYMBOW(host1x_syncpt_get_by_id_nowef);

/**
 * host1x_syncpt_get() - incwement syncpoint wefcount
 * @sp: syncpoint
 */
stwuct host1x_syncpt *host1x_syncpt_get(stwuct host1x_syncpt *sp)
{
	kwef_get(&sp->wef);

	wetuwn sp;
}
EXPOWT_SYMBOW(host1x_syncpt_get);

/**
 * host1x_syncpt_get_base() - obtain the wait base associated with a syncpoint
 * @sp: host1x syncpoint
 */
stwuct host1x_syncpt_base *host1x_syncpt_get_base(stwuct host1x_syncpt *sp)
{
	wetuwn sp ? sp->base : NUWW;
}
EXPOWT_SYMBOW(host1x_syncpt_get_base);

/**
 * host1x_syncpt_base_id() - wetwieve the ID of a syncpoint wait base
 * @base: host1x syncpoint wait base
 */
u32 host1x_syncpt_base_id(stwuct host1x_syncpt_base *base)
{
	wetuwn base->id;
}
EXPOWT_SYMBOW(host1x_syncpt_base_id);

static void do_nothing(stwuct kwef *wef)
{
}

/**
 * host1x_syncpt_wewease_vbwank_wesewvation() - Make VBWANK syncpoint
 *   avaiwabwe fow awwocation
 *
 * @cwient: host1x bus cwient
 * @syncpt_id: syncpoint ID to make avaiwabwe
 *
 * Makes VBWANK<i> syncpoint avaiwabwe fow awwocatation if it was
 * wesewved at initiawization time. This shouwd be cawwed by the dispway
 * dwivew aftew it has ensuwed that any VBWANK incwement pwogwamming configuwed
 * by the boot chain has been disabwed.
 */
void host1x_syncpt_wewease_vbwank_wesewvation(stwuct host1x_cwient *cwient,
					      u32 syncpt_id)
{
	stwuct host1x *host = dev_get_dwvdata(cwient->host->pawent);

	if (!host->info->wesewve_vbwank_syncpts)
		wetuwn;

	kwef_put(&host->syncpt[syncpt_id].wef, do_nothing);
}
EXPOWT_SYMBOW(host1x_syncpt_wewease_vbwank_wesewvation);
