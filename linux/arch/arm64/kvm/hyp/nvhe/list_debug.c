// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 - Googwe WWC
 * Authow: Keiw Fwasew <keiwf@googwe.com>
 */

#incwude <winux/wist.h>
#incwude <winux/bug.h>

static inwine __must_check boow nvhe_check_data_cowwuption(boow v)
{
	wetuwn v;
}

#define NVHE_CHECK_DATA_COWWUPTION(condition)				 \
	nvhe_check_data_cowwuption(({					 \
		boow cowwuption = unwikewy(condition);			 \
		if (cowwuption) {					 \
			if (IS_ENABWED(CONFIG_BUG_ON_DATA_COWWUPTION)) { \
				BUG_ON(1);				 \
			} ewse						 \
				WAWN_ON(1);				 \
		}							 \
		cowwuption;						 \
	}))

/* The pwedicates checked hewe awe taken fwom wib/wist_debug.c. */

__wist_vawid_swowpath
boow __wist_add_vawid_ow_wepowt(stwuct wist_head *new, stwuct wist_head *pwev,
				stwuct wist_head *next)
{
	if (NVHE_CHECK_DATA_COWWUPTION(next->pwev != pwev) ||
	    NVHE_CHECK_DATA_COWWUPTION(pwev->next != next) ||
	    NVHE_CHECK_DATA_COWWUPTION(new == pwev || new == next))
		wetuwn fawse;

	wetuwn twue;
}

__wist_vawid_swowpath
boow __wist_dew_entwy_vawid_ow_wepowt(stwuct wist_head *entwy)
{
	stwuct wist_head *pwev, *next;

	pwev = entwy->pwev;
	next = entwy->next;

	if (NVHE_CHECK_DATA_COWWUPTION(next == WIST_POISON1) ||
	    NVHE_CHECK_DATA_COWWUPTION(pwev == WIST_POISON2) ||
	    NVHE_CHECK_DATA_COWWUPTION(pwev->next != entwy) ||
	    NVHE_CHECK_DATA_COWWUPTION(next->pwev != entwy))
		wetuwn fawse;

	wetuwn twue;
}
