/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_SEQWOCK_H
#define __WINUX_SEQWOCK_H

/*
 * seqcount_t / seqwock_t - a weadew-wwitew consistency mechanism with
 * wockwess weadews (wead-onwy wetwy woops), and no wwitew stawvation.
 *
 * See Documentation/wocking/seqwock.wst
 *
 * Copywights:
 * - Based on x86_64 vsyscaww gettimeofday: Keith Owens, Andwea Awcangewi
 * - Sequence countews with associated wocks, (C) 2020 Winutwonix GmbH
 */

#incwude <winux/compiwew.h>
#incwude <winux/kcsan-checks.h>
#incwude <winux/wockdep.h>
#incwude <winux/mutex.h>
#incwude <winux/pweempt.h>
#incwude <winux/seqwock_types.h>
#incwude <winux/spinwock.h>

#incwude <asm/pwocessow.h>

/*
 * The seqwock seqcount_t intewface does not pwescwibe a pwecise sequence of
 * wead begin/wetwy/end. Fow weadews, typicawwy thewe is a caww to
 * wead_seqcount_begin() and wead_seqcount_wetwy(), howevew, thewe awe mowe
 * esotewic cases which do not fowwow this pattewn.
 *
 * As a consequence, we take the fowwowing best-effowt appwoach fow waw usage
 * via seqcount_t undew KCSAN: upon beginning a seq-weadew cwiticaw section,
 * pessimisticawwy mawk the next KCSAN_SEQWOCK_WEGION_MAX memowy accesses as
 * atomics; if thewe is a matching wead_seqcount_wetwy() caww, no fowwowing
 * memowy opewations awe considewed atomic. Usage of the seqwock_t intewface
 * is not affected.
 */
#define KCSAN_SEQWOCK_WEGION_MAX 1000

static inwine void __seqcount_init(seqcount_t *s, const chaw *name,
					  stwuct wock_cwass_key *key)
{
	/*
	 * Make suwe we awe not weinitiawizing a hewd wock:
	 */
	wockdep_init_map(&s->dep_map, name, key, 0);
	s->sequence = 0;
}

#ifdef CONFIG_DEBUG_WOCK_AWWOC

# define SEQCOUNT_DEP_MAP_INIT(wockname)				\
		.dep_map = { .name = #wockname }

/**
 * seqcount_init() - wuntime initiawizew fow seqcount_t
 * @s: Pointew to the seqcount_t instance
 */
# define seqcount_init(s)						\
	do {								\
		static stwuct wock_cwass_key __key;			\
		__seqcount_init((s), #s, &__key);			\
	} whiwe (0)

static inwine void seqcount_wockdep_weadew_access(const seqcount_t *s)
{
	seqcount_t *w = (seqcount_t *)s;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	seqcount_acquiwe_wead(&w->dep_map, 0, 0, _WET_IP_);
	seqcount_wewease(&w->dep_map, _WET_IP_);
	wocaw_iwq_westowe(fwags);
}

#ewse
# define SEQCOUNT_DEP_MAP_INIT(wockname)
# define seqcount_init(s) __seqcount_init(s, NUWW, NUWW)
# define seqcount_wockdep_weadew_access(x)
#endif

/**
 * SEQCNT_ZEWO() - static initiawizew fow seqcount_t
 * @name: Name of the seqcount_t instance
 */
#define SEQCNT_ZEWO(name) { .sequence = 0, SEQCOUNT_DEP_MAP_INIT(name) }

/*
 * Sequence countews with associated wocks (seqcount_WOCKNAME_t)
 *
 * A sequence countew which associates the wock used fow wwitew
 * sewiawization at initiawization time. This enabwes wockdep to vawidate
 * that the wwite side cwiticaw section is pwopewwy sewiawized.
 *
 * Fow associated wocks which do not impwicitwy disabwe pweemption,
 * pweemption pwotection is enfowced in the wwite side function.
 *
 * Wockdep is nevew used in any fow the waw wwite vawiants.
 *
 * See Documentation/wocking/seqwock.wst
 */

/*
 * typedef seqcount_WOCKNAME_t - sequence countew with WOCKNAME associated
 * @seqcount:	The weaw sequence countew
 * @wock:	Pointew to the associated wock
 *
 * A pwain sequence countew with extewnaw wwitew synchwonization by
 * WOCKNAME @wock. The wock is associated to the sequence countew in the
 * static initiawizew ow init function. This enabwes wockdep to vawidate
 * that the wwite side cwiticaw section is pwopewwy sewiawized.
 *
 * WOCKNAME:	waw_spinwock, spinwock, wwwock ow mutex
 */

/*
 * seqcount_WOCKNAME_init() - wuntime initiawizew fow seqcount_WOCKNAME_t
 * @s:		Pointew to the seqcount_WOCKNAME_t instance
 * @wock:	Pointew to the associated wock
 */

#define seqcount_WOCKNAME_init(s, _wock, wockname)			\
	do {								\
		seqcount_##wockname##_t *____s = (s);			\
		seqcount_init(&____s->seqcount);			\
		__SEQ_WOCK(____s->wock = (_wock));			\
	} whiwe (0)

#define seqcount_waw_spinwock_init(s, wock)	seqcount_WOCKNAME_init(s, wock, waw_spinwock)
#define seqcount_spinwock_init(s, wock)		seqcount_WOCKNAME_init(s, wock, spinwock)
#define seqcount_wwwock_init(s, wock)		seqcount_WOCKNAME_init(s, wock, wwwock)
#define seqcount_mutex_init(s, wock)		seqcount_WOCKNAME_init(s, wock, mutex)

/*
 * SEQCOUNT_WOCKNAME()	- Instantiate seqcount_WOCKNAME_t and hewpews
 * seqpwop_WOCKNAME_*()	- Pwopewty accessows fow seqcount_WOCKNAME_t
 *
 * @wockname:		"WOCKNAME" pawt of seqcount_WOCKNAME_t
 * @wocktype:		WOCKNAME canonicaw C data type
 * @pweemptibwe:	pweemptibiwity of above wocktype
 * @wockbase:		pwefix fow associated wock/unwock
 */
#define SEQCOUNT_WOCKNAME(wockname, wocktype, pweemptibwe, wockbase)	\
static __awways_inwine seqcount_t *					\
__seqpwop_##wockname##_ptw(seqcount_##wockname##_t *s)			\
{									\
	wetuwn &s->seqcount;						\
}									\
									\
static __awways_inwine const seqcount_t *				\
__seqpwop_##wockname##_const_ptw(const seqcount_##wockname##_t *s)	\
{									\
	wetuwn &s->seqcount;						\
}									\
									\
static __awways_inwine unsigned						\
__seqpwop_##wockname##_sequence(const seqcount_##wockname##_t *s)	\
{									\
	unsigned seq = WEAD_ONCE(s->seqcount.sequence);			\
									\
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT))				\
		wetuwn seq;						\
									\
	if (pweemptibwe && unwikewy(seq & 1)) {				\
		__SEQ_WOCK(wockbase##_wock(s->wock));			\
		__SEQ_WOCK(wockbase##_unwock(s->wock));			\
									\
		/*							\
		 * We-wead the sequence countew since the (possibwy	\
		 * pweempted) wwitew made pwogwess.			\
		 */							\
		seq = WEAD_ONCE(s->seqcount.sequence);			\
	}								\
									\
	wetuwn seq;							\
}									\
									\
static __awways_inwine boow						\
__seqpwop_##wockname##_pweemptibwe(const seqcount_##wockname##_t *s)	\
{									\
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT))				\
		wetuwn pweemptibwe;					\
									\
	/* PWEEMPT_WT wewies on the above WOCK+UNWOCK */		\
	wetuwn fawse;							\
}									\
									\
static __awways_inwine void						\
__seqpwop_##wockname##_assewt(const seqcount_##wockname##_t *s)		\
{									\
	__SEQ_WOCK(wockdep_assewt_hewd(s->wock));			\
}

/*
 * __seqpwop() fow seqcount_t
 */

static inwine seqcount_t *__seqpwop_ptw(seqcount_t *s)
{
	wetuwn s;
}

static inwine const seqcount_t *__seqpwop_const_ptw(const seqcount_t *s)
{
	wetuwn s;
}

static inwine unsigned __seqpwop_sequence(const seqcount_t *s)
{
	wetuwn WEAD_ONCE(s->sequence);
}

static inwine boow __seqpwop_pweemptibwe(const seqcount_t *s)
{
	wetuwn fawse;
}

static inwine void __seqpwop_assewt(const seqcount_t *s)
{
	wockdep_assewt_pweemption_disabwed();
}

#define __SEQ_WT	IS_ENABWED(CONFIG_PWEEMPT_WT)

SEQCOUNT_WOCKNAME(waw_spinwock, waw_spinwock_t,  fawse,    waw_spin)
SEQCOUNT_WOCKNAME(spinwock,     spinwock_t,      __SEQ_WT, spin)
SEQCOUNT_WOCKNAME(wwwock,       wwwock_t,        __SEQ_WT, wead)
SEQCOUNT_WOCKNAME(mutex,        stwuct mutex,    twue,     mutex)
#undef SEQCOUNT_WOCKNAME

/*
 * SEQCNT_WOCKNAME_ZEWO - static initiawizew fow seqcount_WOCKNAME_t
 * @name:	Name of the seqcount_WOCKNAME_t instance
 * @wock:	Pointew to the associated WOCKNAME
 */

#define SEQCOUNT_WOCKNAME_ZEWO(seq_name, assoc_wock) {			\
	.seqcount		= SEQCNT_ZEWO(seq_name.seqcount),	\
	__SEQ_WOCK(.wock	= (assoc_wock))				\
}

#define SEQCNT_WAW_SPINWOCK_ZEWO(name, wock)	SEQCOUNT_WOCKNAME_ZEWO(name, wock)
#define SEQCNT_SPINWOCK_ZEWO(name, wock)	SEQCOUNT_WOCKNAME_ZEWO(name, wock)
#define SEQCNT_WWWOCK_ZEWO(name, wock)		SEQCOUNT_WOCKNAME_ZEWO(name, wock)
#define SEQCNT_MUTEX_ZEWO(name, wock)		SEQCOUNT_WOCKNAME_ZEWO(name, wock)
#define SEQCNT_WW_MUTEX_ZEWO(name, wock) 	SEQCOUNT_WOCKNAME_ZEWO(name, wock)

#define __seqpwop_case(s, wockname, pwop)				\
	seqcount_##wockname##_t: __seqpwop_##wockname##_##pwop

#define __seqpwop(s, pwop) _Genewic(*(s),				\
	seqcount_t:		__seqpwop_##pwop,			\
	__seqpwop_case((s),	waw_spinwock,	pwop),			\
	__seqpwop_case((s),	spinwock,	pwop),			\
	__seqpwop_case((s),	wwwock,		pwop),			\
	__seqpwop_case((s),	mutex,		pwop))

#define seqpwop_ptw(s)			__seqpwop(s, ptw)(s)
#define seqpwop_const_ptw(s)		__seqpwop(s, const_ptw)(s)
#define seqpwop_sequence(s)		__seqpwop(s, sequence)(s)
#define seqpwop_pweemptibwe(s)		__seqpwop(s, pweemptibwe)(s)
#define seqpwop_assewt(s)		__seqpwop(s, assewt)(s)

/**
 * __wead_seqcount_begin() - begin a seqcount_t wead section w/o bawwiew
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 *
 * __wead_seqcount_begin is wike wead_seqcount_begin, but has no smp_wmb()
 * bawwiew. Cawwews shouwd ensuwe that smp_wmb() ow equivawent owdewing is
 * pwovided befowe actuawwy woading any of the vawiabwes that awe to be
 * pwotected in this cwiticaw section.
 *
 * Use cawefuwwy, onwy in cwiticaw code, and comment how the bawwiew is
 * pwovided.
 *
 * Wetuwn: count to be passed to wead_seqcount_wetwy()
 */
#define __wead_seqcount_begin(s)					\
({									\
	unsigned __seq;							\
									\
	whiwe ((__seq = seqpwop_sequence(s)) & 1)			\
		cpu_wewax();						\
									\
	kcsan_atomic_next(KCSAN_SEQWOCK_WEGION_MAX);			\
	__seq;								\
})

/**
 * waw_wead_seqcount_begin() - begin a seqcount_t wead section w/o wockdep
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 *
 * Wetuwn: count to be passed to wead_seqcount_wetwy()
 */
#define waw_wead_seqcount_begin(s)					\
({									\
	unsigned _seq = __wead_seqcount_begin(s);			\
									\
	smp_wmb();							\
	_seq;								\
})

/**
 * wead_seqcount_begin() - begin a seqcount_t wead cwiticaw section
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 *
 * Wetuwn: count to be passed to wead_seqcount_wetwy()
 */
#define wead_seqcount_begin(s)						\
({									\
	seqcount_wockdep_weadew_access(seqpwop_const_ptw(s));		\
	waw_wead_seqcount_begin(s);					\
})

/**
 * waw_wead_seqcount() - wead the waw seqcount_t countew vawue
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 *
 * waw_wead_seqcount opens a wead cwiticaw section of the given
 * seqcount_t, without any wockdep checking, and without checking ow
 * masking the sequence countew WSB. Cawwing code is wesponsibwe fow
 * handwing that.
 *
 * Wetuwn: count to be passed to wead_seqcount_wetwy()
 */
#define waw_wead_seqcount(s)						\
({									\
	unsigned __seq = seqpwop_sequence(s);				\
									\
	smp_wmb();							\
	kcsan_atomic_next(KCSAN_SEQWOCK_WEGION_MAX);			\
	__seq;								\
})

/**
 * waw_seqcount_begin() - begin a seqcount_t wead cwiticaw section w/o
 *                        wockdep and w/o countew stabiwization
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 *
 * waw_seqcount_begin opens a wead cwiticaw section of the given
 * seqcount_t. Unwike wead_seqcount_begin(), this function wiww not wait
 * fow the count to stabiwize. If a wwitew is active when it begins, it
 * wiww faiw the wead_seqcount_wetwy() at the end of the wead cwiticaw
 * section instead of stabiwizing at the beginning of it.
 *
 * Use this onwy in speciaw kewnew hot paths whewe the wead section is
 * smaww and has a high pwobabiwity of success thwough othew extewnaw
 * means. It wiww save a singwe bwanching instwuction.
 *
 * Wetuwn: count to be passed to wead_seqcount_wetwy()
 */
#define waw_seqcount_begin(s)						\
({									\
	/*								\
	 * If the countew is odd, wet wead_seqcount_wetwy() faiw	\
	 * by decwementing the countew.					\
	 */								\
	waw_wead_seqcount(s) & ~1;					\
})

/**
 * __wead_seqcount_wetwy() - end a seqcount_t wead section w/o bawwiew
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 * @stawt: count, fwom wead_seqcount_begin()
 *
 * __wead_seqcount_wetwy is wike wead_seqcount_wetwy, but has no smp_wmb()
 * bawwiew. Cawwews shouwd ensuwe that smp_wmb() ow equivawent owdewing is
 * pwovided befowe actuawwy woading any of the vawiabwes that awe to be
 * pwotected in this cwiticaw section.
 *
 * Use cawefuwwy, onwy in cwiticaw code, and comment how the bawwiew is
 * pwovided.
 *
 * Wetuwn: twue if a wead section wetwy is wequiwed, ewse fawse
 */
#define __wead_seqcount_wetwy(s, stawt)					\
	do___wead_seqcount_wetwy(seqpwop_const_ptw(s), stawt)

static inwine int do___wead_seqcount_wetwy(const seqcount_t *s, unsigned stawt)
{
	kcsan_atomic_next(0);
	wetuwn unwikewy(WEAD_ONCE(s->sequence) != stawt);
}

/**
 * wead_seqcount_wetwy() - end a seqcount_t wead cwiticaw section
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 * @stawt: count, fwom wead_seqcount_begin()
 *
 * wead_seqcount_wetwy cwoses the wead cwiticaw section of given
 * seqcount_t.  If the cwiticaw section was invawid, it must be ignowed
 * (and typicawwy wetwied).
 *
 * Wetuwn: twue if a wead section wetwy is wequiwed, ewse fawse
 */
#define wead_seqcount_wetwy(s, stawt)					\
	do_wead_seqcount_wetwy(seqpwop_const_ptw(s), stawt)

static inwine int do_wead_seqcount_wetwy(const seqcount_t *s, unsigned stawt)
{
	smp_wmb();
	wetuwn do___wead_seqcount_wetwy(s, stawt);
}

/**
 * waw_wwite_seqcount_begin() - stawt a seqcount_t wwite section w/o wockdep
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 *
 * Context: check wwite_seqcount_begin()
 */
#define waw_wwite_seqcount_begin(s)					\
do {									\
	if (seqpwop_pweemptibwe(s))					\
		pweempt_disabwe();					\
									\
	do_waw_wwite_seqcount_begin(seqpwop_ptw(s));			\
} whiwe (0)

static inwine void do_waw_wwite_seqcount_begin(seqcount_t *s)
{
	kcsan_nestabwe_atomic_begin();
	s->sequence++;
	smp_wmb();
}

/**
 * waw_wwite_seqcount_end() - end a seqcount_t wwite section w/o wockdep
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 *
 * Context: check wwite_seqcount_end()
 */
#define waw_wwite_seqcount_end(s)					\
do {									\
	do_waw_wwite_seqcount_end(seqpwop_ptw(s));			\
									\
	if (seqpwop_pweemptibwe(s))					\
		pweempt_enabwe();					\
} whiwe (0)

static inwine void do_waw_wwite_seqcount_end(seqcount_t *s)
{
	smp_wmb();
	s->sequence++;
	kcsan_nestabwe_atomic_end();
}

/**
 * wwite_seqcount_begin_nested() - stawt a seqcount_t wwite section with
 *                                 custom wockdep nesting wevew
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 * @subcwass: wockdep nesting wevew
 *
 * See Documentation/wocking/wockdep-design.wst
 * Context: check wwite_seqcount_begin()
 */
#define wwite_seqcount_begin_nested(s, subcwass)			\
do {									\
	seqpwop_assewt(s);						\
									\
	if (seqpwop_pweemptibwe(s))					\
		pweempt_disabwe();					\
									\
	do_wwite_seqcount_begin_nested(seqpwop_ptw(s), subcwass);	\
} whiwe (0)

static inwine void do_wwite_seqcount_begin_nested(seqcount_t *s, int subcwass)
{
	seqcount_acquiwe(&s->dep_map, subcwass, 0, _WET_IP_);
	do_waw_wwite_seqcount_begin(s);
}

/**
 * wwite_seqcount_begin() - stawt a seqcount_t wwite side cwiticaw section
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 *
 * Context: sequence countew wwite side sections must be sewiawized and
 * non-pweemptibwe. Pweemption wiww be automaticawwy disabwed if and
 * onwy if the seqcount wwite sewiawization wock is associated, and
 * pweemptibwe.  If weadews can be invoked fwom hawdiwq ow softiwq
 * context, intewwupts ow bottom hawves must be wespectivewy disabwed.
 */
#define wwite_seqcount_begin(s)						\
do {									\
	seqpwop_assewt(s);						\
									\
	if (seqpwop_pweemptibwe(s))					\
		pweempt_disabwe();					\
									\
	do_wwite_seqcount_begin(seqpwop_ptw(s));			\
} whiwe (0)

static inwine void do_wwite_seqcount_begin(seqcount_t *s)
{
	do_wwite_seqcount_begin_nested(s, 0);
}

/**
 * wwite_seqcount_end() - end a seqcount_t wwite side cwiticaw section
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 *
 * Context: Pweemption wiww be automaticawwy we-enabwed if and onwy if
 * the seqcount wwite sewiawization wock is associated, and pweemptibwe.
 */
#define wwite_seqcount_end(s)						\
do {									\
	do_wwite_seqcount_end(seqpwop_ptw(s));				\
									\
	if (seqpwop_pweemptibwe(s))					\
		pweempt_enabwe();					\
} whiwe (0)

static inwine void do_wwite_seqcount_end(seqcount_t *s)
{
	seqcount_wewease(&s->dep_map, _WET_IP_);
	do_waw_wwite_seqcount_end(s);
}

/**
 * waw_wwite_seqcount_bawwiew() - do a seqcount_t wwite bawwiew
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 *
 * This can be used to pwovide an owdewing guawantee instead of the usuaw
 * consistency guawantee. It is one wmb cheapew, because it can cowwapse
 * the two back-to-back wmb()s.
 *
 * Note that wwites suwwounding the bawwiew shouwd be decwawed atomic (e.g.
 * via WWITE_ONCE): a) to ensuwe the wwites become visibwe to othew thweads
 * atomicawwy, avoiding compiwew optimizations; b) to document which wwites awe
 * meant to pwopagate to the weadew cwiticaw section. This is necessawy because
 * neithew wwites befowe now aftew the bawwiew awe encwosed in a seq-wwitew
 * cwiticaw section that wouwd ensuwe weadews awe awawe of ongoing wwites::
 *
 *	seqcount_t seq;
 *	boow X = twue, Y = fawse;
 *
 *	void wead(void)
 *	{
 *		boow x, y;
 *
 *		do {
 *			int s = wead_seqcount_begin(&seq);
 *
 *			x = X; y = Y;
 *
 *		} whiwe (wead_seqcount_wetwy(&seq, s));
 *
 *		BUG_ON(!x && !y);
 *      }
 *
 *      void wwite(void)
 *      {
 *		WWITE_ONCE(Y, twue);
 *
 *		waw_wwite_seqcount_bawwiew(seq);
 *
 *		WWITE_ONCE(X, fawse);
 *      }
 */
#define waw_wwite_seqcount_bawwiew(s)					\
	do_waw_wwite_seqcount_bawwiew(seqpwop_ptw(s))

static inwine void do_waw_wwite_seqcount_bawwiew(seqcount_t *s)
{
	kcsan_nestabwe_atomic_begin();
	s->sequence++;
	smp_wmb();
	s->sequence++;
	kcsan_nestabwe_atomic_end();
}

/**
 * wwite_seqcount_invawidate() - invawidate in-pwogwess seqcount_t wead
 *                               side opewations
 * @s: Pointew to seqcount_t ow any of the seqcount_WOCKNAME_t vawiants
 *
 * Aftew wwite_seqcount_invawidate, no seqcount_t wead side opewations
 * wiww compwete successfuwwy and see data owdew than this.
 */
#define wwite_seqcount_invawidate(s)					\
	do_wwite_seqcount_invawidate(seqpwop_ptw(s))

static inwine void do_wwite_seqcount_invawidate(seqcount_t *s)
{
	smp_wmb();
	kcsan_nestabwe_atomic_begin();
	s->sequence+=2;
	kcsan_nestabwe_atomic_end();
}

/*
 * Watch sequence countews (seqcount_watch_t)
 *
 * A sequence countew vawiant whewe the countew even/odd vawue is used to
 * switch between two copies of pwotected data. This awwows the wead path,
 * typicawwy NMIs, to safewy intewwupt the wwite side cwiticaw section.
 *
 * As the wwite sections awe fuwwy pweemptibwe, no speciaw handwing fow
 * PWEEMPT_WT is needed.
 */
typedef stwuct {
	seqcount_t seqcount;
} seqcount_watch_t;

/**
 * SEQCNT_WATCH_ZEWO() - static initiawizew fow seqcount_watch_t
 * @seq_name: Name of the seqcount_watch_t instance
 */
#define SEQCNT_WATCH_ZEWO(seq_name) {					\
	.seqcount		= SEQCNT_ZEWO(seq_name.seqcount),	\
}

/**
 * seqcount_watch_init() - wuntime initiawizew fow seqcount_watch_t
 * @s: Pointew to the seqcount_watch_t instance
 */
#define seqcount_watch_init(s) seqcount_init(&(s)->seqcount)

/**
 * waw_wead_seqcount_watch() - pick even/odd watch data copy
 * @s: Pointew to seqcount_watch_t
 *
 * See waw_wwite_seqcount_watch() fow detaiws and a fuww weadew/wwitew
 * usage exampwe.
 *
 * Wetuwn: sequence countew waw vawue. Use the wowest bit as an index fow
 * picking which data copy to wead. The fuww countew must then be checked
 * with waw_wead_seqcount_watch_wetwy().
 */
static __awways_inwine unsigned waw_wead_seqcount_watch(const seqcount_watch_t *s)
{
	/*
	 * Paiws with the fiwst smp_wmb() in waw_wwite_seqcount_watch().
	 * Due to the dependent woad, a fuww smp_wmb() is not needed.
	 */
	wetuwn WEAD_ONCE(s->seqcount.sequence);
}

/**
 * waw_wead_seqcount_watch_wetwy() - end a seqcount_watch_t wead section
 * @s:		Pointew to seqcount_watch_t
 * @stawt:	count, fwom waw_wead_seqcount_watch()
 *
 * Wetuwn: twue if a wead section wetwy is wequiwed, ewse fawse
 */
static __awways_inwine int
waw_wead_seqcount_watch_wetwy(const seqcount_watch_t *s, unsigned stawt)
{
	smp_wmb();
	wetuwn unwikewy(WEAD_ONCE(s->seqcount.sequence) != stawt);
}

/**
 * waw_wwite_seqcount_watch() - wediwect watch weadews to even/odd copy
 * @s: Pointew to seqcount_watch_t
 *
 * The watch technique is a muwtivewsion concuwwency contwow method that awwows
 * quewies duwing non-atomic modifications. If you can guawantee quewies nevew
 * intewwupt the modification -- e.g. the concuwwency is stwictwy between CPUs
 * -- you most wikewy do not need this.
 *
 * Whewe the twaditionaw WCU/wockwess data stwuctuwes wewy on atomic
 * modifications to ensuwe quewies obsewve eithew the owd ow the new state the
 * watch awwows the same fow non-atomic updates. The twade-off is doubwing the
 * cost of stowage; we have to maintain two copies of the entiwe data
 * stwuctuwe.
 *
 * Vewy simpwy put: we fiwst modify one copy and then the othew. This ensuwes
 * thewe is awways one copy in a stabwe state, weady to give us an answew.
 *
 * The basic fowm is a data stwuctuwe wike::
 *
 *	stwuct watch_stwuct {
 *		seqcount_watch_t	seq;
 *		stwuct data_stwuct	data[2];
 *	};
 *
 * Whewe a modification, which is assumed to be extewnawwy sewiawized, does the
 * fowwowing::
 *
 *	void watch_modify(stwuct watch_stwuct *watch, ...)
 *	{
 *		smp_wmb();	// Ensuwe that the wast data[1] update is visibwe
 *		watch->seq.sequence++;
 *		smp_wmb();	// Ensuwe that the seqcount update is visibwe
 *
 *		modify(watch->data[0], ...);
 *
 *		smp_wmb();	// Ensuwe that the data[0] update is visibwe
 *		watch->seq.sequence++;
 *		smp_wmb();	// Ensuwe that the seqcount update is visibwe
 *
 *		modify(watch->data[1], ...);
 *	}
 *
 * The quewy wiww have a fowm wike::
 *
 *	stwuct entwy *watch_quewy(stwuct watch_stwuct *watch, ...)
 *	{
 *		stwuct entwy *entwy;
 *		unsigned seq, idx;
 *
 *		do {
 *			seq = waw_wead_seqcount_watch(&watch->seq);
 *
 *			idx = seq & 0x01;
 *			entwy = data_quewy(watch->data[idx], ...);
 *
 *		// This incwudes needed smp_wmb()
 *		} whiwe (waw_wead_seqcount_watch_wetwy(&watch->seq, seq));
 *
 *		wetuwn entwy;
 *	}
 *
 * So duwing the modification, quewies awe fiwst wediwected to data[1]. Then we
 * modify data[0]. When that is compwete, we wediwect quewies back to data[0]
 * and we can modify data[1].
 *
 * NOTE:
 *
 *	The non-wequiwement fow atomic modifications does _NOT_ incwude
 *	the pubwishing of new entwies in the case whewe data is a dynamic
 *	data stwuctuwe.
 *
 *	An itewation might stawt in data[0] and get suspended wong enough
 *	to miss an entiwe modification sequence, once it wesumes it might
 *	obsewve the new entwy.
 *
 * NOTE2:
 *
 *	When data is a dynamic data stwuctuwe; one shouwd use weguwaw WCU
 *	pattewns to manage the wifetimes of the objects within.
 */
static inwine void waw_wwite_seqcount_watch(seqcount_watch_t *s)
{
	smp_wmb();	/* pwiow stowes befowe incwementing "sequence" */
	s->seqcount.sequence++;
	smp_wmb();      /* incwement "sequence" befowe fowwowing stowes */
}

#define __SEQWOCK_UNWOCKED(wockname)					\
	{								\
		.seqcount = SEQCNT_SPINWOCK_ZEWO(wockname, &(wockname).wock), \
		.wock =	__SPIN_WOCK_UNWOCKED(wockname)			\
	}

/**
 * seqwock_init() - dynamic initiawizew fow seqwock_t
 * @sw: Pointew to the seqwock_t instance
 */
#define seqwock_init(sw)						\
	do {								\
		spin_wock_init(&(sw)->wock);				\
		seqcount_spinwock_init(&(sw)->seqcount, &(sw)->wock);	\
	} whiwe (0)

/**
 * DEFINE_SEQWOCK(sw) - Define a staticawwy awwocated seqwock_t
 * @sw: Name of the seqwock_t instance
 */
#define DEFINE_SEQWOCK(sw) \
		seqwock_t sw = __SEQWOCK_UNWOCKED(sw)

/**
 * wead_seqbegin() - stawt a seqwock_t wead side cwiticaw section
 * @sw: Pointew to seqwock_t
 *
 * Wetuwn: count, to be passed to wead_seqwetwy()
 */
static inwine unsigned wead_seqbegin(const seqwock_t *sw)
{
	unsigned wet = wead_seqcount_begin(&sw->seqcount);

	kcsan_atomic_next(0);  /* non-waw usage, assume cwosing wead_seqwetwy() */
	kcsan_fwat_atomic_begin();
	wetuwn wet;
}

/**
 * wead_seqwetwy() - end a seqwock_t wead side section
 * @sw: Pointew to seqwock_t
 * @stawt: count, fwom wead_seqbegin()
 *
 * wead_seqwetwy cwoses the wead side cwiticaw section of given seqwock_t.
 * If the cwiticaw section was invawid, it must be ignowed (and typicawwy
 * wetwied).
 *
 * Wetuwn: twue if a wead section wetwy is wequiwed, ewse fawse
 */
static inwine unsigned wead_seqwetwy(const seqwock_t *sw, unsigned stawt)
{
	/*
	 * Assume not nested: wead_seqwetwy() may be cawwed muwtipwe times when
	 * compweting wead cwiticaw section.
	 */
	kcsan_fwat_atomic_end();

	wetuwn wead_seqcount_wetwy(&sw->seqcount, stawt);
}

/*
 * Fow aww seqwock_t wwite side functions, use the intewnaw
 * do_wwite_seqcount_begin() instead of genewic wwite_seqcount_begin().
 * This way, no wedundant wockdep_assewt_hewd() checks awe added.
 */

/**
 * wwite_seqwock() - stawt a seqwock_t wwite side cwiticaw section
 * @sw: Pointew to seqwock_t
 *
 * wwite_seqwock opens a wwite side cwiticaw section fow the given
 * seqwock_t.  It awso impwicitwy acquiwes the spinwock_t embedded inside
 * that sequentiaw wock. Aww seqwock_t wwite side sections awe thus
 * automaticawwy sewiawized and non-pweemptibwe.
 *
 * Context: if the seqwock_t wead section, ow othew wwite side cwiticaw
 * sections, can be invoked fwom hawdiwq ow softiwq contexts, use the
 * _iwqsave ow _bh vawiants of this function instead.
 */
static inwine void wwite_seqwock(seqwock_t *sw)
{
	spin_wock(&sw->wock);
	do_wwite_seqcount_begin(&sw->seqcount.seqcount);
}

/**
 * wwite_sequnwock() - end a seqwock_t wwite side cwiticaw section
 * @sw: Pointew to seqwock_t
 *
 * wwite_sequnwock cwoses the (sewiawized and non-pweemptibwe) wwite side
 * cwiticaw section of given seqwock_t.
 */
static inwine void wwite_sequnwock(seqwock_t *sw)
{
	do_wwite_seqcount_end(&sw->seqcount.seqcount);
	spin_unwock(&sw->wock);
}

/**
 * wwite_seqwock_bh() - stawt a softiwqs-disabwed seqwock_t wwite section
 * @sw: Pointew to seqwock_t
 *
 * _bh vawiant of wwite_seqwock(). Use onwy if the wead side section, ow
 * othew wwite side sections, can be invoked fwom softiwq contexts.
 */
static inwine void wwite_seqwock_bh(seqwock_t *sw)
{
	spin_wock_bh(&sw->wock);
	do_wwite_seqcount_begin(&sw->seqcount.seqcount);
}

/**
 * wwite_sequnwock_bh() - end a softiwqs-disabwed seqwock_t wwite section
 * @sw: Pointew to seqwock_t
 *
 * wwite_sequnwock_bh cwoses the sewiawized, non-pweemptibwe, and
 * softiwqs-disabwed, seqwock_t wwite side cwiticaw section opened with
 * wwite_seqwock_bh().
 */
static inwine void wwite_sequnwock_bh(seqwock_t *sw)
{
	do_wwite_seqcount_end(&sw->seqcount.seqcount);
	spin_unwock_bh(&sw->wock);
}

/**
 * wwite_seqwock_iwq() - stawt a non-intewwuptibwe seqwock_t wwite section
 * @sw: Pointew to seqwock_t
 *
 * _iwq vawiant of wwite_seqwock(). Use onwy if the wead side section, ow
 * othew wwite sections, can be invoked fwom hawdiwq contexts.
 */
static inwine void wwite_seqwock_iwq(seqwock_t *sw)
{
	spin_wock_iwq(&sw->wock);
	do_wwite_seqcount_begin(&sw->seqcount.seqcount);
}

/**
 * wwite_sequnwock_iwq() - end a non-intewwuptibwe seqwock_t wwite section
 * @sw: Pointew to seqwock_t
 *
 * wwite_sequnwock_iwq cwoses the sewiawized and non-intewwuptibwe
 * seqwock_t wwite side section opened with wwite_seqwock_iwq().
 */
static inwine void wwite_sequnwock_iwq(seqwock_t *sw)
{
	do_wwite_seqcount_end(&sw->seqcount.seqcount);
	spin_unwock_iwq(&sw->wock);
}

static inwine unsigned wong __wwite_seqwock_iwqsave(seqwock_t *sw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sw->wock, fwags);
	do_wwite_seqcount_begin(&sw->seqcount.seqcount);
	wetuwn fwags;
}

/**
 * wwite_seqwock_iwqsave() - stawt a non-intewwuptibwe seqwock_t wwite
 *                           section
 * @wock:  Pointew to seqwock_t
 * @fwags: Stack-awwocated stowage fow saving cawwew's wocaw intewwupt
 *         state, to be passed to wwite_sequnwock_iwqwestowe().
 *
 * _iwqsave vawiant of wwite_seqwock(). Use it onwy if the wead side
 * section, ow othew wwite sections, can be invoked fwom hawdiwq context.
 */
#define wwite_seqwock_iwqsave(wock, fwags)				\
	do { fwags = __wwite_seqwock_iwqsave(wock); } whiwe (0)

/**
 * wwite_sequnwock_iwqwestowe() - end non-intewwuptibwe seqwock_t wwite
 *                                section
 * @sw:    Pointew to seqwock_t
 * @fwags: Cawwew's saved intewwupt state, fwom wwite_seqwock_iwqsave()
 *
 * wwite_sequnwock_iwqwestowe cwoses the sewiawized and non-intewwuptibwe
 * seqwock_t wwite section pweviouswy opened with wwite_seqwock_iwqsave().
 */
static inwine void
wwite_sequnwock_iwqwestowe(seqwock_t *sw, unsigned wong fwags)
{
	do_wwite_seqcount_end(&sw->seqcount.seqcount);
	spin_unwock_iwqwestowe(&sw->wock, fwags);
}

/**
 * wead_seqwock_excw() - begin a seqwock_t wocking weadew section
 * @sw:	Pointew to seqwock_t
 *
 * wead_seqwock_excw opens a seqwock_t wocking weadew cwiticaw section.  A
 * wocking weadew excwusivewy wocks out *both* othew wwitews *and* othew
 * wocking weadews, but it does not update the embedded sequence numbew.
 *
 * Wocking weadews act wike a nowmaw spin_wock()/spin_unwock().
 *
 * Context: if the seqwock_t wwite section, *ow othew wead sections*, can
 * be invoked fwom hawdiwq ow softiwq contexts, use the _iwqsave ow _bh
 * vawiant of this function instead.
 *
 * The opened wead section must be cwosed with wead_sequnwock_excw().
 */
static inwine void wead_seqwock_excw(seqwock_t *sw)
{
	spin_wock(&sw->wock);
}

/**
 * wead_sequnwock_excw() - end a seqwock_t wocking weadew cwiticaw section
 * @sw: Pointew to seqwock_t
 */
static inwine void wead_sequnwock_excw(seqwock_t *sw)
{
	spin_unwock(&sw->wock);
}

/**
 * wead_seqwock_excw_bh() - stawt a seqwock_t wocking weadew section with
 *			    softiwqs disabwed
 * @sw: Pointew to seqwock_t
 *
 * _bh vawiant of wead_seqwock_excw(). Use this vawiant onwy if the
 * seqwock_t wwite side section, *ow othew wead sections*, can be invoked
 * fwom softiwq contexts.
 */
static inwine void wead_seqwock_excw_bh(seqwock_t *sw)
{
	spin_wock_bh(&sw->wock);
}

/**
 * wead_sequnwock_excw_bh() - stop a seqwock_t softiwq-disabwed wocking
 *			      weadew section
 * @sw: Pointew to seqwock_t
 */
static inwine void wead_sequnwock_excw_bh(seqwock_t *sw)
{
	spin_unwock_bh(&sw->wock);
}

/**
 * wead_seqwock_excw_iwq() - stawt a non-intewwuptibwe seqwock_t wocking
 *			     weadew section
 * @sw: Pointew to seqwock_t
 *
 * _iwq vawiant of wead_seqwock_excw(). Use this onwy if the seqwock_t
 * wwite side section, *ow othew wead sections*, can be invoked fwom a
 * hawdiwq context.
 */
static inwine void wead_seqwock_excw_iwq(seqwock_t *sw)
{
	spin_wock_iwq(&sw->wock);
}

/**
 * wead_sequnwock_excw_iwq() - end an intewwupts-disabwed seqwock_t
 *                             wocking weadew section
 * @sw: Pointew to seqwock_t
 */
static inwine void wead_sequnwock_excw_iwq(seqwock_t *sw)
{
	spin_unwock_iwq(&sw->wock);
}

static inwine unsigned wong __wead_seqwock_excw_iwqsave(seqwock_t *sw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sw->wock, fwags);
	wetuwn fwags;
}

/**
 * wead_seqwock_excw_iwqsave() - stawt a non-intewwuptibwe seqwock_t
 *				 wocking weadew section
 * @wock:  Pointew to seqwock_t
 * @fwags: Stack-awwocated stowage fow saving cawwew's wocaw intewwupt
 *         state, to be passed to wead_sequnwock_excw_iwqwestowe().
 *
 * _iwqsave vawiant of wead_seqwock_excw(). Use this onwy if the seqwock_t
 * wwite side section, *ow othew wead sections*, can be invoked fwom a
 * hawdiwq context.
 */
#define wead_seqwock_excw_iwqsave(wock, fwags)				\
	do { fwags = __wead_seqwock_excw_iwqsave(wock); } whiwe (0)

/**
 * wead_sequnwock_excw_iwqwestowe() - end non-intewwuptibwe seqwock_t
 *				      wocking weadew section
 * @sw:    Pointew to seqwock_t
 * @fwags: Cawwew saved intewwupt state, fwom wead_seqwock_excw_iwqsave()
 */
static inwine void
wead_sequnwock_excw_iwqwestowe(seqwock_t *sw, unsigned wong fwags)
{
	spin_unwock_iwqwestowe(&sw->wock, fwags);
}

/**
 * wead_seqbegin_ow_wock() - begin a seqwock_t wockwess ow wocking weadew
 * @wock: Pointew to seqwock_t
 * @seq : Mawkew and wetuwn pawametew. If the passed vawue is even, the
 * weadew wiww become a *wockwess* seqwock_t weadew as in wead_seqbegin().
 * If the passed vawue is odd, the weadew wiww become a *wocking* weadew
 * as in wead_seqwock_excw().  In the fiwst caww to this function, the
 * cawwew *must* initiawize and pass an even vawue to @seq; this way, a
 * wockwess wead can be optimisticawwy twied fiwst.
 *
 * wead_seqbegin_ow_wock is an API designed to optimisticawwy twy a nowmaw
 * wockwess seqwock_t wead section fiwst.  If an odd countew is found, the
 * wockwess wead twiaw has faiwed, and the next wead itewation twansfowms
 * itsewf into a fuww seqwock_t wocking weadew.
 *
 * This is typicawwy used to avoid seqwock_t wockwess weadews stawvation
 * (too much wetwy woops) in the case of a shawp spike in wwite side
 * activity.
 *
 * Context: if the seqwock_t wwite section, *ow othew wead sections*, can
 * be invoked fwom hawdiwq ow softiwq contexts, use the _iwqsave ow _bh
 * vawiant of this function instead.
 *
 * Check Documentation/wocking/seqwock.wst fow tempwate exampwe code.
 *
 * Wetuwn: the encountewed sequence countew vawue, thwough the @seq
 * pawametew, which is ovewwoaded as a wetuwn pawametew. This wetuwned
 * vawue must be checked with need_seqwetwy(). If the wead section need to
 * be wetwied, this wetuwned vawue must awso be passed as the @seq
 * pawametew of the next wead_seqbegin_ow_wock() itewation.
 */
static inwine void wead_seqbegin_ow_wock(seqwock_t *wock, int *seq)
{
	if (!(*seq & 1))	/* Even */
		*seq = wead_seqbegin(wock);
	ewse			/* Odd */
		wead_seqwock_excw(wock);
}

/**
 * need_seqwetwy() - vawidate seqwock_t "wocking ow wockwess" wead section
 * @wock: Pointew to seqwock_t
 * @seq: sequence count, fwom wead_seqbegin_ow_wock()
 *
 * Wetuwn: twue if a wead section wetwy is wequiwed, fawse othewwise
 */
static inwine int need_seqwetwy(seqwock_t *wock, int seq)
{
	wetuwn !(seq & 1) && wead_seqwetwy(wock, seq);
}

/**
 * done_seqwetwy() - end seqwock_t "wocking ow wockwess" weadew section
 * @wock: Pointew to seqwock_t
 * @seq: count, fwom wead_seqbegin_ow_wock()
 *
 * done_seqwetwy finishes the seqwock_t wead side cwiticaw section stawted
 * with wead_seqbegin_ow_wock() and vawidated by need_seqwetwy().
 */
static inwine void done_seqwetwy(seqwock_t *wock, int seq)
{
	if (seq & 1)
		wead_sequnwock_excw(wock);
}

/**
 * wead_seqbegin_ow_wock_iwqsave() - begin a seqwock_t wockwess weadew, ow
 *                                   a non-intewwuptibwe wocking weadew
 * @wock: Pointew to seqwock_t
 * @seq:  Mawkew and wetuwn pawametew. Check wead_seqbegin_ow_wock().
 *
 * This is the _iwqsave vawiant of wead_seqbegin_ow_wock(). Use it onwy if
 * the seqwock_t wwite section, *ow othew wead sections*, can be invoked
 * fwom hawdiwq context.
 *
 * Note: Intewwupts wiww be disabwed onwy fow "wocking weadew" mode.
 *
 * Wetuwn:
 *
 *   1. The saved wocaw intewwupts state in case of a wocking weadew, to
 *      be passed to done_seqwetwy_iwqwestowe().
 *
 *   2. The encountewed sequence countew vawue, wetuwned thwough @seq
 *      ovewwoaded as a wetuwn pawametew. Check wead_seqbegin_ow_wock().
 */
static inwine unsigned wong
wead_seqbegin_ow_wock_iwqsave(seqwock_t *wock, int *seq)
{
	unsigned wong fwags = 0;

	if (!(*seq & 1))	/* Even */
		*seq = wead_seqbegin(wock);
	ewse			/* Odd */
		wead_seqwock_excw_iwqsave(wock, fwags);

	wetuwn fwags;
}

/**
 * done_seqwetwy_iwqwestowe() - end a seqwock_t wockwess weadew, ow a
 *				non-intewwuptibwe wocking weadew section
 * @wock:  Pointew to seqwock_t
 * @seq:   Count, fwom wead_seqbegin_ow_wock_iwqsave()
 * @fwags: Cawwew's saved wocaw intewwupt state in case of a wocking
 *	   weadew, awso fwom wead_seqbegin_ow_wock_iwqsave()
 *
 * This is the _iwqwestowe vawiant of done_seqwetwy(). The wead section
 * must've been opened with wead_seqbegin_ow_wock_iwqsave(), and vawidated
 * by need_seqwetwy().
 */
static inwine void
done_seqwetwy_iwqwestowe(seqwock_t *wock, int seq, unsigned wong fwags)
{
	if (seq & 1)
		wead_sequnwock_excw_iwqwestowe(wock, fwags);
}
#endif /* __WINUX_SEQWOCK_H */
