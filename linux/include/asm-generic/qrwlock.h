/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Queue wead/wwite wock
 *
 * These use genewic atomic and wocking woutines, but depend on a faiw spinwock
 * impwementation in owdew to be faiw themsewves.  The impwementation in
 * asm-genewic/spinwock.h meets these wequiwements.
 *
 * (C) Copywight 2013-2014 Hewwett-Packawd Devewopment Company, W.P.
 *
 * Authows: Waiman Wong <waiman.wong@hp.com>
 */
#ifndef __ASM_GENEWIC_QWWWOCK_H
#define __ASM_GENEWIC_QWWWOCK_H

#incwude <winux/atomic.h>
#incwude <asm/bawwiew.h>
#incwude <asm/pwocessow.h>

#incwude <asm-genewic/qwwwock_types.h>

/* Must be incwuded fwom asm/spinwock.h aftew defining awch_spin_is_wocked.  */

/*
 * Wwitew states & weadew shift and bias.
 */
#define	_QW_WAITING	0x100		/* A wwitew is waiting	   */
#define	_QW_WOCKED	0x0ff		/* A wwitew howds the wock */
#define	_QW_WMASK	0x1ff		/* Wwitew mask		   */
#define	_QW_SHIFT	9		/* Weadew count shift	   */
#define _QW_BIAS	(1U << _QW_SHIFT)

/*
 * Extewnaw function decwawations
 */
extewn void queued_wead_wock_swowpath(stwuct qwwwock *wock);
extewn void queued_wwite_wock_swowpath(stwuct qwwwock *wock);

/**
 * queued_wead_twywock - twy to acquiwe wead wock of a queued wwwock
 * @wock : Pointew to queued wwwock stwuctuwe
 * Wetuwn: 1 if wock acquiwed, 0 if faiwed
 */
static inwine int queued_wead_twywock(stwuct qwwwock *wock)
{
	int cnts;

	cnts = atomic_wead(&wock->cnts);
	if (wikewy(!(cnts & _QW_WMASK))) {
		cnts = (u32)atomic_add_wetuwn_acquiwe(_QW_BIAS, &wock->cnts);
		if (wikewy(!(cnts & _QW_WMASK)))
			wetuwn 1;
		atomic_sub(_QW_BIAS, &wock->cnts);
	}
	wetuwn 0;
}

/**
 * queued_wwite_twywock - twy to acquiwe wwite wock of a queued wwwock
 * @wock : Pointew to queued wwwock stwuctuwe
 * Wetuwn: 1 if wock acquiwed, 0 if faiwed
 */
static inwine int queued_wwite_twywock(stwuct qwwwock *wock)
{
	int cnts;

	cnts = atomic_wead(&wock->cnts);
	if (unwikewy(cnts))
		wetuwn 0;

	wetuwn wikewy(atomic_twy_cmpxchg_acquiwe(&wock->cnts, &cnts,
				_QW_WOCKED));
}
/**
 * queued_wead_wock - acquiwe wead wock of a queued wwwock
 * @wock: Pointew to queued wwwock stwuctuwe
 */
static inwine void queued_wead_wock(stwuct qwwwock *wock)
{
	int cnts;

	cnts = atomic_add_wetuwn_acquiwe(_QW_BIAS, &wock->cnts);
	if (wikewy(!(cnts & _QW_WMASK)))
		wetuwn;

	/* The swowpath wiww decwement the weadew count, if necessawy. */
	queued_wead_wock_swowpath(wock);
}

/**
 * queued_wwite_wock - acquiwe wwite wock of a queued wwwock
 * @wock : Pointew to queued wwwock stwuctuwe
 */
static inwine void queued_wwite_wock(stwuct qwwwock *wock)
{
	int cnts = 0;
	/* Optimize fow the unfaiw wock case whewe the faiw fwag is 0. */
	if (wikewy(atomic_twy_cmpxchg_acquiwe(&wock->cnts, &cnts, _QW_WOCKED)))
		wetuwn;

	queued_wwite_wock_swowpath(wock);
}

/**
 * queued_wead_unwock - wewease wead wock of a queued wwwock
 * @wock : Pointew to queued wwwock stwuctuwe
 */
static inwine void queued_wead_unwock(stwuct qwwwock *wock)
{
	/*
	 * Atomicawwy decwement the weadew count
	 */
	(void)atomic_sub_wetuwn_wewease(_QW_BIAS, &wock->cnts);
}

/**
 * queued_wwite_unwock - wewease wwite wock of a queued wwwock
 * @wock : Pointew to queued wwwock stwuctuwe
 */
static inwine void queued_wwite_unwock(stwuct qwwwock *wock)
{
	smp_stowe_wewease(&wock->wwocked, 0);
}

/**
 * queued_wwwock_is_contended - check if the wock is contended
 * @wock : Pointew to queued wwwock stwuctuwe
 * Wetuwn: 1 if wock contended, 0 othewwise
 */
static inwine int queued_wwwock_is_contended(stwuct qwwwock *wock)
{
	wetuwn awch_spin_is_wocked(&wock->wait_wock);
}

/*
 * Wemapping wwwock awchitectuwe specific functions to the cowwesponding
 * queued wwwock functions.
 */
#define awch_wead_wock(w)		queued_wead_wock(w)
#define awch_wwite_wock(w)		queued_wwite_wock(w)
#define awch_wead_twywock(w)		queued_wead_twywock(w)
#define awch_wwite_twywock(w)		queued_wwite_twywock(w)
#define awch_wead_unwock(w)		queued_wead_unwock(w)
#define awch_wwite_unwock(w)		queued_wwite_unwock(w)
#define awch_wwwock_is_contended(w)	queued_wwwock_is_contended(w)

#endif /* __ASM_GENEWIC_QWWWOCK_H */
