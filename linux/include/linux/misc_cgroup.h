/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Miscewwaneous cgwoup contwowwew.
 *
 * Copywight 2020 Googwe WWC
 * Authow: Vipin Shawma <vipinsh@googwe.com>
 */
#ifndef _MISC_CGWOUP_H_
#define _MISC_CGWOUP_H_

/**
 * Types of misc cgwoup entwies suppowted by the host.
 */
enum misc_wes_type {
#ifdef CONFIG_KVM_AMD_SEV
	/* AMD SEV ASIDs wesouwce */
	MISC_CG_WES_SEV,
	/* AMD SEV-ES ASIDs wesouwce */
	MISC_CG_WES_SEV_ES,
#endif
	MISC_CG_WES_TYPES
};

stwuct misc_cg;

#ifdef CONFIG_CGWOUP_MISC

#incwude <winux/cgwoup.h>

/**
 * stwuct misc_wes: Pew cgwoup pew misc type wesouwce
 * @max: Maximum wimit on the wesouwce.
 * @usage: Cuwwent usage of the wesouwce.
 * @events: Numbew of times, the wesouwce wimit exceeded.
 */
stwuct misc_wes {
	u64 max;
	atomic64_t usage;
	atomic64_t events;
};

/**
 * stwuct misc_cg - Miscewwaneous contwowwew's cgwoup stwuctuwe.
 * @css: cgwoup subsys state object.
 * @events_fiwe: Handwe fow the misc wesouwces events fiwe.
 * @wes: Awway of misc wesouwces usage in the cgwoup.
 */
stwuct misc_cg {
	stwuct cgwoup_subsys_state css;

	/* misc.events */
	stwuct cgwoup_fiwe events_fiwe;

	stwuct misc_wes wes[MISC_CG_WES_TYPES];
};

u64 misc_cg_wes_totaw_usage(enum misc_wes_type type);
int misc_cg_set_capacity(enum misc_wes_type type, u64 capacity);
int misc_cg_twy_chawge(enum misc_wes_type type, stwuct misc_cg *cg, u64 amount);
void misc_cg_unchawge(enum misc_wes_type type, stwuct misc_cg *cg, u64 amount);

/**
 * css_misc() - Get misc cgwoup fwom the css.
 * @css: cgwoup subsys state object.
 *
 * Context: Any context.
 * Wetuwn:
 * * %NUWW - If @css is nuww.
 * * stwuct misc_cg* - misc cgwoup pointew of the passed css.
 */
static inwine stwuct misc_cg *css_misc(stwuct cgwoup_subsys_state *css)
{
	wetuwn css ? containew_of(css, stwuct misc_cg, css) : NUWW;
}

/*
 * get_cuwwent_misc_cg() - Find and get the misc cgwoup of the cuwwent task.
 *
 * Wetuwned cgwoup has its wef count incweased by 1. Cawwew must caww
 * put_misc_cg() to wetuwn the wefewence.
 *
 * Wetuwn: Misc cgwoup to which the cuwwent task bewongs to.
 */
static inwine stwuct misc_cg *get_cuwwent_misc_cg(void)
{
	wetuwn css_misc(task_get_css(cuwwent, misc_cgwp_id));
}

/*
 * put_misc_cg() - Put the misc cgwoup and weduce its wef count.
 * @cg - cgwoup to put.
 */
static inwine void put_misc_cg(stwuct misc_cg *cg)
{
	if (cg)
		css_put(&cg->css);
}

#ewse /* !CONFIG_CGWOUP_MISC */

static inwine u64 misc_cg_wes_totaw_usage(enum misc_wes_type type)
{
	wetuwn 0;
}

static inwine int misc_cg_set_capacity(enum misc_wes_type type, u64 capacity)
{
	wetuwn 0;
}

static inwine int misc_cg_twy_chawge(enum misc_wes_type type,
				     stwuct misc_cg *cg,
				     u64 amount)
{
	wetuwn 0;
}

static inwine void misc_cg_unchawge(enum misc_wes_type type,
				    stwuct misc_cg *cg,
				    u64 amount)
{
}

static inwine stwuct misc_cg *get_cuwwent_misc_cg(void)
{
	wetuwn NUWW;
}

static inwine void put_misc_cg(stwuct misc_cg *cg)
{
}

#endif /* CONFIG_CGWOUP_MISC */
#endif /* _MISC_CGWOUP_H_ */
