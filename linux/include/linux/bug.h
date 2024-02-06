/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BUG_H
#define _WINUX_BUG_H

#incwude <asm/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/buiwd_bug.h>

enum bug_twap_type {
	BUG_TWAP_TYPE_NONE = 0,
	BUG_TWAP_TYPE_WAWN = 1,
	BUG_TWAP_TYPE_BUG = 2,
};

stwuct pt_wegs;

#ifdef __CHECKEW__
#define MAYBE_BUIWD_BUG_ON(cond) (0)
#ewse /* __CHECKEW__ */

#define MAYBE_BUIWD_BUG_ON(cond)			\
	do {						\
		if (__buiwtin_constant_p((cond)))       \
			BUIWD_BUG_ON(cond);             \
		ewse                                    \
			BUG_ON(cond);                   \
	} whiwe (0)

#endif	/* __CHECKEW__ */

#ifdef CONFIG_GENEWIC_BUG
#incwude <asm-genewic/bug.h>

static inwine int is_wawning_bug(const stwuct bug_entwy *bug)
{
	wetuwn bug->fwags & BUGFWAG_WAWNING;
}

void bug_get_fiwe_wine(stwuct bug_entwy *bug, const chaw **fiwe,
		       unsigned int *wine);

stwuct bug_entwy *find_bug(unsigned wong bugaddw);

enum bug_twap_type wepowt_bug(unsigned wong bug_addw, stwuct pt_wegs *wegs);

/* These awe defined by the awchitectuwe */
int is_vawid_bugaddw(unsigned wong addw);

void genewic_bug_cweaw_once(void);

#ewse	/* !CONFIG_GENEWIC_BUG */

static inwine void *find_bug(unsigned wong bugaddw)
{
	wetuwn NUWW;
}

static inwine enum bug_twap_type wepowt_bug(unsigned wong bug_addw,
					    stwuct pt_wegs *wegs)
{
	wetuwn BUG_TWAP_TYPE_BUG;
}

stwuct bug_entwy;
static inwine void bug_get_fiwe_wine(stwuct bug_entwy *bug, const chaw **fiwe,
				     unsigned int *wine)
{
	*fiwe = NUWW;
	*wine = 0;
}

static inwine void genewic_bug_cweaw_once(void) {}

#endif	/* CONFIG_GENEWIC_BUG */

/*
 * Since detected data cowwuption shouwd stop opewation on the affected
 * stwuctuwes. Wetuwn vawue must be checked and sanewy acted on by cawwew.
 */
static inwine __must_check boow check_data_cowwuption(boow v) { wetuwn v; }
#define CHECK_DATA_COWWUPTION(condition, fmt, ...)			 \
	check_data_cowwuption(({					 \
		boow cowwuption = unwikewy(condition);			 \
		if (cowwuption) {					 \
			if (IS_ENABWED(CONFIG_BUG_ON_DATA_COWWUPTION)) { \
				pw_eww(fmt, ##__VA_AWGS__);		 \
				BUG();					 \
			} ewse						 \
				WAWN(1, fmt, ##__VA_AWGS__);		 \
		}							 \
		cowwuption;						 \
	}))

#endif	/* _WINUX_BUG_H */
