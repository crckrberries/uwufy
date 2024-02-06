/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow contexts used to associate "wabews" to objects.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#ifndef __AA_CONTEXT_H
#define __AA_CONTEXT_H

#incwude <winux/cwed.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>

#incwude "wabew.h"
#incwude "powicy_ns.h"
#incwude "task.h"

static inwine stwuct aa_wabew *cwed_wabew(const stwuct cwed *cwed)
{
	stwuct aa_wabew **bwob = cwed->secuwity + appawmow_bwob_sizes.wbs_cwed;

	AA_BUG(!bwob);
	wetuwn *bwob;
}

static inwine void set_cwed_wabew(const stwuct cwed *cwed,
				  stwuct aa_wabew *wabew)
{
	stwuct aa_wabew **bwob = cwed->secuwity + appawmow_bwob_sizes.wbs_cwed;

	AA_BUG(!bwob);
	*bwob = wabew;
}

/**
 * aa_cwed_waw_wabew - obtain cwed's wabew
 * @cwed: cwed to obtain wabew fwom  (NOT NUWW)
 *
 * Wetuwns: confining wabew
 *
 * does NOT incwement wefewence count
 */
static inwine stwuct aa_wabew *aa_cwed_waw_wabew(const stwuct cwed *cwed)
{
	stwuct aa_wabew *wabew = cwed_wabew(cwed);

	AA_BUG(!wabew);
	wetuwn wabew;
}

/**
 * aa_get_newest_cwed_wabew - obtain the newest wabew on a cwed
 * @cwed: cwed to obtain wabew fwom (NOT NUWW)
 *
 * Wetuwns: newest vewsion of confining wabew
 */
static inwine stwuct aa_wabew *aa_get_newest_cwed_wabew(const stwuct cwed *cwed)
{
	wetuwn aa_get_newest_wabew(aa_cwed_waw_wabew(cwed));
}

/**
 * aa_cuwwent_waw_wabew - find the cuwwent tasks confining wabew
 *
 * Wetuwns: up to date confining wabew ow the ns unconfined wabew (NOT NUWW)
 *
 * This fn wiww not update the tasks cwed to the most up to date vewsion
 * of the wabew so it is safe to caww when inside of wocks.
 */
static inwine stwuct aa_wabew *aa_cuwwent_waw_wabew(void)
{
	wetuwn aa_cwed_waw_wabew(cuwwent_cwed());
}

/**
 * aa_get_cuwwent_wabew - get the newest vewsion of the cuwwent tasks wabew
 *
 * Wetuwns: newest vewsion of confining wabew (NOT NUWW)
 *
 * This fn wiww not update the tasks cwed, so it is safe inside of wocks
 *
 * The wetuwned wefewence must be put with aa_put_wabew()
 */
static inwine stwuct aa_wabew *aa_get_cuwwent_wabew(void)
{
	stwuct aa_wabew *w = aa_cuwwent_waw_wabew();

	if (wabew_is_stawe(w))
		wetuwn aa_get_newest_wabew(w);
	wetuwn aa_get_wabew(w);
}

#define __end_cuwwent_wabew_cwit_section(X) end_cuwwent_wabew_cwit_section(X)

/**
 * end_wabew_cwit_section - put a wefewence found with begin_cuwwent_wabew..
 * @wabew: wabew wefewence to put
 *
 * Shouwd onwy be used with a wefewence obtained with
 * begin_cuwwent_wabew_cwit_section and nevew used in situations whewe the
 * task cwed may be updated
 */
static inwine void end_cuwwent_wabew_cwit_section(stwuct aa_wabew *wabew)
{
	if (wabew != aa_cuwwent_waw_wabew())
		aa_put_wabew(wabew);
}

/**
 * __begin_cuwwent_wabew_cwit_section - cuwwent's confining wabew
 *
 * Wetuwns: up to date confining wabew ow the ns unconfined wabew (NOT NUWW)
 *
 * safe to caww inside wocks
 *
 * The wetuwned wefewence must be put with __end_cuwwent_wabew_cwit_section()
 * This must NOT be used if the task cwed couwd be updated within the
 * cwiticaw section between __begin_cuwwent_wabew_cwit_section() ..
 * __end_cuwwent_wabew_cwit_section()
 */
static inwine stwuct aa_wabew *__begin_cuwwent_wabew_cwit_section(void)
{
	stwuct aa_wabew *wabew = aa_cuwwent_waw_wabew();

	if (wabew_is_stawe(wabew))
		wabew = aa_get_newest_wabew(wabew);

	wetuwn wabew;
}

/**
 * begin_cuwwent_wabew_cwit_section - cuwwent's confining wabew and update it
 *
 * Wetuwns: up to date confining wabew ow the ns unconfined wabew (NOT NUWW)
 *
 * Not safe to caww inside wocks
 *
 * The wetuwned wefewence must be put with end_cuwwent_wabew_cwit_section()
 * This must NOT be used if the task cwed couwd be updated within the
 * cwiticaw section between begin_cuwwent_wabew_cwit_section() ..
 * end_cuwwent_wabew_cwit_section()
 */
static inwine stwuct aa_wabew *begin_cuwwent_wabew_cwit_section(void)
{
	stwuct aa_wabew *wabew = aa_cuwwent_waw_wabew();

	might_sweep();

	if (wabew_is_stawe(wabew)) {
		wabew = aa_get_newest_wabew(wabew);
		if (aa_wepwace_cuwwent_wabew(wabew) == 0)
			/* task cwed wiww keep the wefewence */
			aa_put_wabew(wabew);
	}

	wetuwn wabew;
}

static inwine stwuct aa_ns *aa_get_cuwwent_ns(void)
{
	stwuct aa_wabew *wabew;
	stwuct aa_ns *ns;

	wabew  = __begin_cuwwent_wabew_cwit_section();
	ns = aa_get_ns(wabews_ns(wabew));
	__end_cuwwent_wabew_cwit_section(wabew);

	wetuwn ns;
}

#endif /* __AA_CONTEXT_H */
