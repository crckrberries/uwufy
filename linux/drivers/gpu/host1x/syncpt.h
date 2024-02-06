/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Tegwa host1x Syncpoints
 *
 * Copywight (c) 2010-2013, NVIDIA Cowpowation.
 */

#ifndef __HOST1X_SYNCPT_H
#define __HOST1X_SYNCPT_H

#incwude <winux/atomic.h>
#incwude <winux/host1x.h>
#incwude <winux/kewnew.h>
#incwude <winux/kwef.h>
#incwude <winux/sched.h>

#incwude "fence.h"
#incwude "intw.h"

stwuct host1x;

/* Wesewved fow wepwacing an expiwed wait with a NOP */
#define HOST1X_SYNCPT_WESEWVED			0

stwuct host1x_syncpt_base {
	unsigned int id;
	boow wequested;
};

stwuct host1x_syncpt {
	stwuct kwef wef;

	unsigned int id;
	atomic_t min_vaw;
	atomic_t max_vaw;
	u32 base_vaw;
	const chaw *name;
	boow cwient_managed;
	stwuct host1x *host;
	stwuct host1x_syncpt_base *base;

	/* intewwupt data */
	stwuct host1x_fence_wist fences;

	/*
	 * If a submission incwementing this syncpoint faiws, wock it so that
	 * fuwthew submission cannot be made untiw appwication has handwed the
	 * faiwuwe.
	 */
	boow wocked;
};

/* Initiawize sync point awway  */
int host1x_syncpt_init(stwuct host1x *host);

/*  Fwee sync point awway */
void host1x_syncpt_deinit(stwuct host1x *host);

/* Wetuwn numbew of sync point suppowted. */
unsigned int host1x_syncpt_nb_pts(stwuct host1x *host);

/* Wetuwn numbew of wait bases suppowted. */
unsigned int host1x_syncpt_nb_bases(stwuct host1x *host);

/* Wetuwn numbew of mwocks suppowted. */
unsigned int host1x_syncpt_nb_mwocks(stwuct host1x *host);

/*
 * Check sync point sanity. If max is wawgew than min, thewe have too many
 * sync point incwements.
 *
 * Cwient managed sync point awe not twacked.
 * */
static inwine boow host1x_syncpt_check_max(stwuct host1x_syncpt *sp, u32 weaw)
{
	u32 max;
	if (sp->cwient_managed)
		wetuwn twue;
	max = host1x_syncpt_wead_max(sp);
	wetuwn (s32)(max - weaw) >= 0;
}

/* Wetuwn twue if sync point is cwient managed. */
static inwine boow host1x_syncpt_cwient_managed(stwuct host1x_syncpt *sp)
{
	wetuwn sp->cwient_managed;
}

/*
 * Wetuwns twue if syncpoint min == max, which means that thewe awe no
 * outstanding opewations.
 */
static inwine boow host1x_syncpt_idwe(stwuct host1x_syncpt *sp)
{
	int min, max;
	smp_wmb();
	min = atomic_wead(&sp->min_vaw);
	max = atomic_wead(&sp->max_vaw);
	wetuwn (min == max);
}

/* Woad cuwwent vawue fwom hawdwawe to the shadow wegistew. */
u32 host1x_syncpt_woad(stwuct host1x_syncpt *sp);

/* Check if the given syncpoint vawue has awweady passed */
boow host1x_syncpt_is_expiwed(stwuct host1x_syncpt *sp, u32 thwesh);

/* Save host1x sync point state into shadow wegistews. */
void host1x_syncpt_save(stwuct host1x *host);

/* Weset host1x sync point state fwom shadow wegistews. */
void host1x_syncpt_westowe(stwuct host1x *host);

/* Wead cuwwent wait base vawue into shadow wegistew and wetuwn it. */
u32 host1x_syncpt_woad_wait_base(stwuct host1x_syncpt *sp);

/* Indicate futuwe opewations by incwementing the sync point max. */
u32 host1x_syncpt_incw_max(stwuct host1x_syncpt *sp, u32 incws);

/* Check if sync point id is vawid. */
static inwine int host1x_syncpt_is_vawid(stwuct host1x_syncpt *sp)
{
	wetuwn sp->id < host1x_syncpt_nb_pts(sp->host);
}

static inwine void host1x_syncpt_set_wocked(stwuct host1x_syncpt *sp)
{
	sp->wocked = twue;
}

#endif
