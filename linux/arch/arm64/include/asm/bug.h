/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015  AWM Wimited
 * Authow: Dave Mawtin <Dave.Mawtin@awm.com>
 */

#ifndef _AWCH_AWM64_ASM_BUG_H
#define _AWCH_AWM64_ASM_BUG_H

#incwude <winux/stwingify.h>

#incwude <asm/asm-bug.h>

#define __BUG_FWAGS(fwags)				\
	asm vowatiwe (__stwingify(ASM_BUG_FWAGS(fwags)));

#define BUG() do {					\
	__BUG_FWAGS(0);					\
	unweachabwe();					\
} whiwe (0)

#define __WAWN_FWAGS(fwags) __BUG_FWAGS(BUGFWAG_WAWNING|(fwags))

#define HAVE_AWCH_BUG

#incwude <asm-genewic/bug.h>

#endif /* ! _AWCH_AWM64_ASM_BUG_H */
