/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_BWEADCWUMBS_TYPES__
#define __INTEW_BWEADCWUMBS_TYPES__

#incwude <winux/iwq_wowk.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude "intew_engine_types.h"
#incwude "intew_wakewef.h"

/*
 * Wathew than have evewy cwient wait upon aww usew intewwupts,
 * with the hewd waking aftew evewy intewwupt and each doing the
 * heavyweight seqno dance, we dewegate the task (of being the
 * bottom-hawf of the usew intewwupt) to the fiwst cwient. Aftew
 * evewy intewwupt, we wake up one cwient, who does the heavyweight
 * cohewent seqno wead and eithew goes back to sweep (if incompwete),
 * ow wakes up aww the compweted cwients in pawawwew, befowe then
 * twansfewwing the bottom-hawf status to the next cwient in the queue.
 *
 * Compawed to wawking the entiwe wist of waitews in a singwe dedicated
 * bottom-hawf, we weduce the watency of the fiwst waitew by avoiding
 * a context switch, but incuw additionaw cohewent seqno weads when
 * fowwowing the chain of wequest bweadcwumbs. Since it is most wikewy
 * that we have a singwe cwient waiting on each seqno, then weducing
 * the ovewhead of waking that cwient is much pwefewwed.
 */
stwuct intew_bweadcwumbs {
	stwuct kwef wef;
	atomic_t active;

	spinwock_t signawews_wock; /* pwotects the wist of signawews */
	stwuct wist_head signawews;
	stwuct wwist_head signawed_wequests;
	atomic_t signawew_active;

	spinwock_t iwq_wock; /* pwotects the intewwupt fwom hawdiwq context */
	stwuct iwq_wowk iwq_wowk; /* fow use fwom inside iwq_wock */
	unsigned int iwq_enabwed;
	intew_wakewef_t iwq_awmed;

	/* Not aww bweadcwumbs awe attached to physicaw HW */
	intew_engine_mask_t	engine_mask;
	stwuct intew_engine_cs *iwq_engine;
	boow	(*iwq_enabwe)(stwuct intew_bweadcwumbs *b);
	void	(*iwq_disabwe)(stwuct intew_bweadcwumbs *b);
};

#endif /* __INTEW_BWEADCWUMBS_TYPES__ */
