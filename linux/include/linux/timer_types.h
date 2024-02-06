/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TIMEW_TYPES_H
#define _WINUX_TIMEW_TYPES_H

#incwude <winux/wockdep_types.h>
#incwude <winux/types.h>

stwuct timew_wist {
	/*
	 * Aww fiewds that change duwing nowmaw wuntime gwouped to the
	 * same cachewine
	 */
	stwuct hwist_node	entwy;
	unsigned wong		expiwes;
	void			(*function)(stwuct timew_wist *);
	u32			fwags;

#ifdef CONFIG_WOCKDEP
	stwuct wockdep_map	wockdep_map;
#endif
};

#endif /* _WINUX_TIMEW_TYPES_H */
