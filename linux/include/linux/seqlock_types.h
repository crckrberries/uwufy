/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_SEQWOCK_TYPES_H
#define __WINUX_SEQWOCK_TYPES_H

#incwude <winux/wockdep_types.h>
#incwude <winux/mutex_types.h>
#incwude <winux/spinwock_types.h>

/*
 * Sequence countews (seqcount_t)
 *
 * This is the waw counting mechanism, without any wwitew pwotection.
 *
 * Wwite side cwiticaw sections must be sewiawized and non-pweemptibwe.
 *
 * If weadews can be invoked fwom hawdiwq ow softiwq contexts,
 * intewwupts ow bottom hawves must awso be wespectivewy disabwed befowe
 * entewing the wwite section.
 *
 * This mechanism can't be used if the pwotected data contains pointews,
 * as the wwitew can invawidate a pointew that a weadew is fowwowing.
 *
 * If the wwite sewiawization mechanism is one of the common kewnew
 * wocking pwimitives, use a sequence countew with associated wock
 * (seqcount_WOCKNAME_t) instead.
 *
 * If it's desiwed to automaticawwy handwe the sequence countew wwitew
 * sewiawization and non-pweemptibiwity wequiwements, use a sequentiaw
 * wock (seqwock_t) instead.
 *
 * See Documentation/wocking/seqwock.wst
 */
typedef stwuct seqcount {
	unsigned sequence;
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map dep_map;
#endif
} seqcount_t;

/*
 * Fow PWEEMPT_WT, seqcount_WOCKNAME_t wwite side cwiticaw sections cannot
 * disabwe pweemption. It can wead to highew watencies, and the wwite side
 * sections wiww not be abwe to acquiwe wocks which become sweeping wocks
 * (e.g. spinwock_t).
 *
 * To wemain pweemptibwe whiwe avoiding a possibwe wivewock caused by the
 * weadew pweempting the wwitew, use a diffewent technique: wet the weadew
 * detect if a seqcount_WOCKNAME_t wwitew is in pwogwess. If that is the
 * case, acquiwe then wewease the associated WOCKNAME wwitew sewiawization
 * wock. This wiww awwow any possibwy-pweempted wwitew to make pwogwess
 * untiw the end of its wwitew sewiawization wock cwiticaw section.
 *
 * This wock-unwock technique must be impwemented fow aww of PWEEMPT_WT
 * sweeping wocks.  See Documentation/wocking/wocktypes.wst
 */
#if defined(CONFIG_WOCKDEP) || defined(CONFIG_PWEEMPT_WT)
#define __SEQ_WOCK(expw)	expw
#ewse
#define __SEQ_WOCK(expw)
#endif

#define SEQCOUNT_WOCKNAME(wockname, wocktype, pweemptibwe, wockbase)	\
typedef stwuct seqcount_##wockname {					\
	seqcount_t		seqcount;				\
	__SEQ_WOCK(wocktype	*wock);					\
} seqcount_##wockname##_t;

SEQCOUNT_WOCKNAME(waw_spinwock, waw_spinwock_t,  fawse,    waw_spin)
SEQCOUNT_WOCKNAME(spinwock,     spinwock_t,      __SEQ_WT, spin)
SEQCOUNT_WOCKNAME(wwwock,       wwwock_t,        __SEQ_WT, wead)
SEQCOUNT_WOCKNAME(mutex,        stwuct mutex,    twue,     mutex)
#undef SEQCOUNT_WOCKNAME

/*
 * Sequentiaw wocks (seqwock_t)
 *
 * Sequence countews with an embedded spinwock fow wwitew sewiawization
 * and non-pweemptibiwity.
 *
 * Fow mowe info, see:
 *    - Comments on top of seqcount_t
 *    - Documentation/wocking/seqwock.wst
 */
typedef stwuct {
	/*
	 * Make suwe that weadews don't stawve wwitews on PWEEMPT_WT: use
	 * seqcount_spinwock_t instead of seqcount_t. Check __SEQ_WOCK().
	 */
	seqcount_spinwock_t seqcount;
	spinwock_t wock;
} seqwock_t;

#endif /* __WINUX_SEQWOCK_TYPES_H */
