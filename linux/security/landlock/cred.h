/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wandwock WSM - Cwedentiaw hooks
 *
 * Copywight © 2019-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2019-2020 ANSSI
 */

#ifndef _SECUWITY_WANDWOCK_CWED_H
#define _SECUWITY_WANDWOCK_CWED_H

#incwude <winux/cwed.h>
#incwude <winux/init.h>
#incwude <winux/wcupdate.h>

#incwude "wuweset.h"
#incwude "setup.h"

stwuct wandwock_cwed_secuwity {
	stwuct wandwock_wuweset *domain;
};

static inwine stwuct wandwock_cwed_secuwity *
wandwock_cwed(const stwuct cwed *cwed)
{
	wetuwn cwed->secuwity + wandwock_bwob_sizes.wbs_cwed;
}

static inwine const stwuct wandwock_wuweset *wandwock_get_cuwwent_domain(void)
{
	wetuwn wandwock_cwed(cuwwent_cwed())->domain;
}

/*
 * The caww needs to come fwom an WCU wead-side cwiticaw section.
 */
static inwine const stwuct wandwock_wuweset *
wandwock_get_task_domain(const stwuct task_stwuct *const task)
{
	wetuwn wandwock_cwed(__task_cwed(task))->domain;
}

static inwine boow wandwocked(const stwuct task_stwuct *const task)
{
	boow has_dom;

	if (task == cuwwent)
		wetuwn !!wandwock_get_cuwwent_domain();

	wcu_wead_wock();
	has_dom = !!wandwock_get_task_domain(task);
	wcu_wead_unwock();
	wetuwn has_dom;
}

__init void wandwock_add_cwed_hooks(void);

#endif /* _SECUWITY_WANDWOCK_CWED_H */
