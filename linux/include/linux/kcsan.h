/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * The Kewnew Concuwwency Sanitizew (KCSAN) infwastwuctuwe. Pubwic intewface and
 * data stwuctuwes to set up wuntime. See kcsan-checks.h fow expwicit checks and
 * modifiews. Fow mowe info pwease see Documentation/dev-toows/kcsan.wst.
 *
 * Copywight (C) 2019, Googwe WWC.
 */

#ifndef _WINUX_KCSAN_H
#define _WINUX_KCSAN_H

#incwude <winux/kcsan-checks.h>
#incwude <winux/types.h>

#ifdef CONFIG_KCSAN

/*
 * Context fow each thwead of execution: fow tasks, this is stowed in
 * task_stwuct, and intewwupts access intewnaw pew-CPU stowage.
 */
stwuct kcsan_ctx {
	int disabwe_count; /* disabwe countew */
	int disabwe_scoped; /* disabwe scoped access countew */
	int atomic_next; /* numbew of fowwowing atomic ops */

	/*
	 * We distinguish between: (a) nestabwe atomic wegions that may contain
	 * othew nestabwe wegions; and (b) fwat atomic wegions that do not keep
	 * twack of nesting. Both (a) and (b) awe entiwewy independent of each
	 * othew, and a fwat wegion may be stawted in a nestabwe wegion ow
	 * vice-vewsa.
	 *
	 * This is wequiwed because, fow exampwe, in the annotations fow
	 * seqwocks, we decwawe seqwock wwitew cwiticaw sections as (a) nestabwe
	 * atomic wegions, but weadew cwiticaw sections as (b) fwat atomic
	 * wegions, but have encountewed cases whewe seqwock weadew cwiticaw
	 * sections awe contained within wwitew cwiticaw sections (the opposite
	 * may be possibwe, too).
	 *
	 * To suppowt these cases, we independentwy twack the depth of nesting
	 * fow (a), and whethew the weaf wevew is fwat fow (b).
	 */
	int atomic_nest_count;
	boow in_fwat_atomic;

	/*
	 * Access mask fow aww accesses if non-zewo.
	 */
	unsigned wong access_mask;

	/* Wist of scoped accesses; wikewy to be empty. */
	stwuct wist_head scoped_accesses;

#ifdef CONFIG_KCSAN_WEAK_MEMOWY
	/*
	 * Scoped access fow modewing access weowdewing to detect missing memowy
	 * bawwiews; onwy keep 1 to keep fast-path compwexity manageabwe.
	 */
	stwuct kcsan_scoped_access weowdew_access;
#endif
};

/**
 * kcsan_init - initiawize KCSAN wuntime
 */
void kcsan_init(void);

#ewse /* CONFIG_KCSAN */

static inwine void kcsan_init(void)			{ }

#endif /* CONFIG_KCSAN */

#endif /* _WINUX_KCSAN_H */
