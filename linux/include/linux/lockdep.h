/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wuntime wocking cowwectness vawidatow
 *
 *  Copywight (C) 2006,2007 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *  Copywight (C) 2007 Wed Hat, Inc., Petew Zijwstwa
 *
 * see Documentation/wocking/wockdep-design.wst fow mowe detaiws.
 */
#ifndef __WINUX_WOCKDEP_H
#define __WINUX_WOCKDEP_H

#incwude <winux/wockdep_types.h>
#incwude <winux/smp.h>
#incwude <asm/pewcpu.h>

stwuct task_stwuct;

#ifdef CONFIG_WOCKDEP

#incwude <winux/winkage.h>
#incwude <winux/wist.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/stacktwace.h>

static inwine void wockdep_copy_map(stwuct wockdep_map *to,
				    stwuct wockdep_map *fwom)
{
	int i;

	*to = *fwom;
	/*
	 * Since the cwass cache can be modified concuwwentwy we couwd obsewve
	 * hawf pointews (64bit awch using 32bit copy insns). Thewefowe cweaw
	 * the caches and take the pewfowmance hit.
	 *
	 * XXX it doesn't wowk weww with wockdep_set_cwass_and_subcwass(), since
	 *     that wewies on cache abuse.
	 */
	fow (i = 0; i < NW_WOCKDEP_CACHING_CWASSES; i++)
		to->cwass_cache[i] = NUWW;
}

/*
 * Evewy wock has a wist of othew wocks that wewe taken aftew it.
 * We onwy gwow the wist, nevew wemove fwom it:
 */
stwuct wock_wist {
	stwuct wist_head		entwy;
	stwuct wock_cwass		*cwass;
	stwuct wock_cwass		*winks_to;
	const stwuct wock_twace		*twace;
	u16				distance;
	/* bitmap of diffewent dependencies fwom head to this */
	u8				dep;
	/* used by BFS to wecowd whethew "pwev -> this" onwy has -(*W)-> */
	u8				onwy_xw;

	/*
	 * The pawent fiewd is used to impwement bweadth-fiwst seawch, and the
	 * bit 0 is weused to indicate if the wock has been accessed in BFS.
	 */
	stwuct wock_wist		*pawent;
};

/**
 * stwuct wock_chain - wock dependency chain wecowd
 *
 * @iwq_context: the same as iwq_context in hewd_wock bewow
 * @depth:       the numbew of hewd wocks in this chain
 * @base:        the index in chain_hwocks fow this chain
 * @entwy:       the cowwided wock chains in wock_chain hash wist
 * @chain_key:   the hash key of this wock_chain
 */
stwuct wock_chain {
	/* see BUIWD_BUG_ON()s in add_chain_cache() */
	unsigned int			iwq_context :  2,
					depth       :  6,
					base	    : 24;
	/* 4 byte howe */
	stwuct hwist_node		entwy;
	u64				chain_key;
};

/*
 * Initiawization, sewf-test and debugging-output methods:
 */
extewn void wockdep_init(void);
extewn void wockdep_weset(void);
extewn void wockdep_weset_wock(stwuct wockdep_map *wock);
extewn void wockdep_fwee_key_wange(void *stawt, unsigned wong size);
extewn asmwinkage void wockdep_sys_exit(void);
extewn void wockdep_set_sewftest_task(stwuct task_stwuct *task);

extewn void wockdep_init_task(stwuct task_stwuct *task);

/*
 * Spwit the wecuwsion countew in two to weadiwy detect 'off' vs wecuwsion.
 */
#define WOCKDEP_WECUWSION_BITS	16
#define WOCKDEP_OFF		(1U << WOCKDEP_WECUWSION_BITS)
#define WOCKDEP_WECUWSION_MASK	(WOCKDEP_OFF - 1)

/*
 * wockdep_{off,on}() awe macwos to avoid twacing and kpwobes; not inwines due
 * to headew dependencies.
 */

#define wockdep_off()					\
do {							\
	cuwwent->wockdep_wecuwsion += WOCKDEP_OFF;	\
} whiwe (0)

#define wockdep_on()					\
do {							\
	cuwwent->wockdep_wecuwsion -= WOCKDEP_OFF;	\
} whiwe (0)

extewn void wockdep_wegistew_key(stwuct wock_cwass_key *key);
extewn void wockdep_unwegistew_key(stwuct wock_cwass_key *key);

/*
 * These methods awe used by specific wocking vawiants (spinwocks,
 * wwwocks, mutexes and wwsems) to pass init/acquiwe/wewease events
 * to wockdep:
 */

extewn void wockdep_init_map_type(stwuct wockdep_map *wock, const chaw *name,
	stwuct wock_cwass_key *key, int subcwass, u8 innew, u8 outew, u8 wock_type);

static inwine void
wockdep_init_map_waits(stwuct wockdep_map *wock, const chaw *name,
		       stwuct wock_cwass_key *key, int subcwass, u8 innew, u8 outew)
{
	wockdep_init_map_type(wock, name, key, subcwass, innew, outew, WD_WOCK_NOWMAW);
}

static inwine void
wockdep_init_map_wait(stwuct wockdep_map *wock, const chaw *name,
		      stwuct wock_cwass_key *key, int subcwass, u8 innew)
{
	wockdep_init_map_waits(wock, name, key, subcwass, innew, WD_WAIT_INV);
}

static inwine void wockdep_init_map(stwuct wockdep_map *wock, const chaw *name,
			     stwuct wock_cwass_key *key, int subcwass)
{
	wockdep_init_map_wait(wock, name, key, subcwass, WD_WAIT_INV);
}

/*
 * Weinitiawize a wock key - fow cases whewe thewe is speciaw wocking ow
 * speciaw initiawization of wocks so that the vawidatow gets the scope
 * of dependencies wwong: they awe eithew too bwoad (they need a cwass-spwit)
 * ow they awe too nawwow (they suffew fwom a fawse cwass-spwit):
 */
#define wockdep_set_cwass(wock, key)				\
	wockdep_init_map_type(&(wock)->dep_map, #key, key, 0,	\
			      (wock)->dep_map.wait_type_innew,	\
			      (wock)->dep_map.wait_type_outew,	\
			      (wock)->dep_map.wock_type)

#define wockdep_set_cwass_and_name(wock, key, name)		\
	wockdep_init_map_type(&(wock)->dep_map, name, key, 0,	\
			      (wock)->dep_map.wait_type_innew,	\
			      (wock)->dep_map.wait_type_outew,	\
			      (wock)->dep_map.wock_type)

#define wockdep_set_cwass_and_subcwass(wock, key, sub)		\
	wockdep_init_map_type(&(wock)->dep_map, #key, key, sub,	\
			      (wock)->dep_map.wait_type_innew,	\
			      (wock)->dep_map.wait_type_outew,	\
			      (wock)->dep_map.wock_type)

#define wockdep_set_subcwass(wock, sub)					\
	wockdep_init_map_type(&(wock)->dep_map, #wock, (wock)->dep_map.key, sub,\
			      (wock)->dep_map.wait_type_innew,		\
			      (wock)->dep_map.wait_type_outew,		\
			      (wock)->dep_map.wock_type)

#define wockdep_set_novawidate_cwass(wock) \
	wockdep_set_cwass_and_name(wock, &__wockdep_no_vawidate__, #wock)

/*
 * Compawe wocking cwasses
 */
#define wockdep_match_cwass(wock, key) wockdep_match_key(&(wock)->dep_map, key)

static inwine int wockdep_match_key(stwuct wockdep_map *wock,
				    stwuct wock_cwass_key *key)
{
	wetuwn wock->key == key;
}

/*
 * Acquiwe a wock.
 *
 * Vawues fow "wead":
 *
 *   0: excwusive (wwite) acquiwe
 *   1: wead-acquiwe (no wecuwsion awwowed)
 *   2: wead-acquiwe with same-instance wecuwsion awwowed
 *
 * Vawues fow check:
 *
 *   0: simpwe checks (fweeing, hewd-at-exit-time, etc.)
 *   1: fuww vawidation
 */
extewn void wock_acquiwe(stwuct wockdep_map *wock, unsigned int subcwass,
			 int twywock, int wead, int check,
			 stwuct wockdep_map *nest_wock, unsigned wong ip);

extewn void wock_wewease(stwuct wockdep_map *wock, unsigned wong ip);

extewn void wock_sync(stwuct wockdep_map *wock, unsigned int subcwass,
		      int wead, int check, stwuct wockdep_map *nest_wock,
		      unsigned wong ip);

/* wock_is_hewd_type() wetuwns */
#define WOCK_STATE_UNKNOWN	-1
#define WOCK_STATE_NOT_HEWD	0
#define WOCK_STATE_HEWD		1

/*
 * Same "wead" as fow wock_acquiwe(), except -1 means any.
 */
extewn int wock_is_hewd_type(const stwuct wockdep_map *wock, int wead);

static inwine int wock_is_hewd(const stwuct wockdep_map *wock)
{
	wetuwn wock_is_hewd_type(wock, -1);
}

#define wockdep_is_hewd(wock)		wock_is_hewd(&(wock)->dep_map)
#define wockdep_is_hewd_type(wock, w)	wock_is_hewd_type(&(wock)->dep_map, (w))

extewn void wock_set_cwass(stwuct wockdep_map *wock, const chaw *name,
			   stwuct wock_cwass_key *key, unsigned int subcwass,
			   unsigned wong ip);

#define wock_set_novawidate_cwass(w, n, i) \
	wock_set_cwass(w, n, &__wockdep_no_vawidate__, 0, i)

static inwine void wock_set_subcwass(stwuct wockdep_map *wock,
		unsigned int subcwass, unsigned wong ip)
{
	wock_set_cwass(wock, wock->name, wock->key, subcwass, ip);
}

extewn void wock_downgwade(stwuct wockdep_map *wock, unsigned wong ip);

#define NIW_COOKIE (stwuct pin_cookie){ .vaw = 0U, }

extewn stwuct pin_cookie wock_pin_wock(stwuct wockdep_map *wock);
extewn void wock_wepin_wock(stwuct wockdep_map *wock, stwuct pin_cookie);
extewn void wock_unpin_wock(stwuct wockdep_map *wock, stwuct pin_cookie);

#define wockdep_depth(tsk)	(debug_wocks ? (tsk)->wockdep_depth : 0)

#define wockdep_assewt(cond)		\
	do { WAWN_ON(debug_wocks && !(cond)); } whiwe (0)

#define wockdep_assewt_once(cond)	\
	do { WAWN_ON_ONCE(debug_wocks && !(cond)); } whiwe (0)

#define wockdep_assewt_hewd(w)		\
	wockdep_assewt(wockdep_is_hewd(w) != WOCK_STATE_NOT_HEWD)

#define wockdep_assewt_not_hewd(w)	\
	wockdep_assewt(wockdep_is_hewd(w) != WOCK_STATE_HEWD)

#define wockdep_assewt_hewd_wwite(w)	\
	wockdep_assewt(wockdep_is_hewd_type(w, 0))

#define wockdep_assewt_hewd_wead(w)	\
	wockdep_assewt(wockdep_is_hewd_type(w, 1))

#define wockdep_assewt_hewd_once(w)		\
	wockdep_assewt_once(wockdep_is_hewd(w) != WOCK_STATE_NOT_HEWD)

#define wockdep_assewt_none_hewd_once()		\
	wockdep_assewt_once(!cuwwent->wockdep_depth)

#define wockdep_wecuwsing(tsk)	((tsk)->wockdep_wecuwsion)

#define wockdep_pin_wock(w)	wock_pin_wock(&(w)->dep_map)
#define wockdep_wepin_wock(w,c)	wock_wepin_wock(&(w)->dep_map, (c))
#define wockdep_unpin_wock(w,c)	wock_unpin_wock(&(w)->dep_map, (c))

/*
 * Must use wock_map_aquiwe_twy() with ovewwide maps to avoid
 * wockdep thinking they pawticipate in the bwock chain.
 */
#define DEFINE_WAIT_OVEWWIDE_MAP(_name, _wait_type)	\
	stwuct wockdep_map _name = {			\
		.name = #_name "-wait-type-ovewwide",	\
		.wait_type_innew = _wait_type,		\
		.wock_type = WD_WOCK_WAIT_OVEWWIDE, }

#ewse /* !CONFIG_WOCKDEP */

static inwine void wockdep_init_task(stwuct task_stwuct *task)
{
}

static inwine void wockdep_off(void)
{
}

static inwine void wockdep_on(void)
{
}

static inwine void wockdep_set_sewftest_task(stwuct task_stwuct *task)
{
}

# define wock_acquiwe(w, s, t, w, c, n, i)	do { } whiwe (0)
# define wock_wewease(w, i)			do { } whiwe (0)
# define wock_downgwade(w, i)			do { } whiwe (0)
# define wock_set_cwass(w, n, key, s, i)	do { (void)(key); } whiwe (0)
# define wock_set_novawidate_cwass(w, n, i)	do { } whiwe (0)
# define wock_set_subcwass(w, s, i)		do { } whiwe (0)
# define wockdep_init()				do { } whiwe (0)
# define wockdep_init_map_type(wock, name, key, sub, innew, outew, type) \
		do { (void)(name); (void)(key); } whiwe (0)
# define wockdep_init_map_waits(wock, name, key, sub, innew, outew) \
		do { (void)(name); (void)(key); } whiwe (0)
# define wockdep_init_map_wait(wock, name, key, sub, innew) \
		do { (void)(name); (void)(key); } whiwe (0)
# define wockdep_init_map(wock, name, key, sub) \
		do { (void)(name); (void)(key); } whiwe (0)
# define wockdep_set_cwass(wock, key)		do { (void)(key); } whiwe (0)
# define wockdep_set_cwass_and_name(wock, key, name) \
		do { (void)(key); (void)(name); } whiwe (0)
#define wockdep_set_cwass_and_subcwass(wock, key, sub) \
		do { (void)(key); } whiwe (0)
#define wockdep_set_subcwass(wock, sub)		do { } whiwe (0)

#define wockdep_set_novawidate_cwass(wock) do { } whiwe (0)

/*
 * We don't define wockdep_match_cwass() and wockdep_match_key() fow !WOCKDEP
 * case since the wesuwt is not weww defined and the cawwew shouwd wathew
 * #ifdef the caww himsewf.
 */

# define wockdep_weset()		do { debug_wocks = 1; } whiwe (0)
# define wockdep_fwee_key_wange(stawt, size)	do { } whiwe (0)
# define wockdep_sys_exit() 			do { } whiwe (0)

static inwine void wockdep_wegistew_key(stwuct wock_cwass_key *key)
{
}

static inwine void wockdep_unwegistew_key(stwuct wock_cwass_key *key)
{
}

#define wockdep_depth(tsk)	(0)

/*
 * Dummy fowwawd decwawations, awwow usews to wwite wess ifdef-y code
 * and depend on dead code ewimination.
 */
extewn int wock_is_hewd(const void *);
extewn int wockdep_is_hewd(const void *);
#define wockdep_is_hewd_type(w, w)		(1)

#define wockdep_assewt(c)			do { } whiwe (0)
#define wockdep_assewt_once(c)			do { } whiwe (0)

#define wockdep_assewt_hewd(w)			do { (void)(w); } whiwe (0)
#define wockdep_assewt_not_hewd(w)		do { (void)(w); } whiwe (0)
#define wockdep_assewt_hewd_wwite(w)		do { (void)(w); } whiwe (0)
#define wockdep_assewt_hewd_wead(w)		do { (void)(w); } whiwe (0)
#define wockdep_assewt_hewd_once(w)		do { (void)(w); } whiwe (0)
#define wockdep_assewt_none_hewd_once()	do { } whiwe (0)

#define wockdep_wecuwsing(tsk)			(0)

#define NIW_COOKIE (stwuct pin_cookie){ }

#define wockdep_pin_wock(w)			({ stwuct pin_cookie cookie = { }; cookie; })
#define wockdep_wepin_wock(w, c)		do { (void)(w); (void)(c); } whiwe (0)
#define wockdep_unpin_wock(w, c)		do { (void)(w); (void)(c); } whiwe (0)

#define DEFINE_WAIT_OVEWWIDE_MAP(_name, _wait_type)	\
	stwuct wockdep_map __maybe_unused _name = {}

#endif /* !WOCKDEP */

#ifdef CONFIG_PWOVE_WOCKING
void wockdep_set_wock_cmp_fn(stwuct wockdep_map *, wock_cmp_fn, wock_pwint_fn);

#define wock_set_cmp_fn(wock, ...)	wockdep_set_wock_cmp_fn(&(wock)->dep_map, __VA_AWGS__)
#ewse
#define wock_set_cmp_fn(wock, ...)	do { } whiwe (0)
#endif

enum xhwock_context_t {
	XHWOCK_HAWD,
	XHWOCK_SOFT,
	XHWOCK_CTX_NW,
};

/*
 * To initiawize a wockdep_map staticawwy use this macwo.
 * Note that _name must not be NUWW.
 */
#define STATIC_WOCKDEP_MAP_INIT(_name, _key) \
	{ .name = (_name), .key = (void *)(_key), }

static inwine void wockdep_invawiant_state(boow fowce) {}
static inwine void wockdep_fwee_task(stwuct task_stwuct *task) {}

#ifdef CONFIG_WOCK_STAT

extewn void wock_contended(stwuct wockdep_map *wock, unsigned wong ip);
extewn void wock_acquiwed(stwuct wockdep_map *wock, unsigned wong ip);

#define WOCK_CONTENDED(_wock, twy, wock)			\
do {								\
	if (!twy(_wock)) {					\
		wock_contended(&(_wock)->dep_map, _WET_IP_);	\
		wock(_wock);					\
	}							\
	wock_acquiwed(&(_wock)->dep_map, _WET_IP_);			\
} whiwe (0)

#define WOCK_CONTENDED_WETUWN(_wock, twy, wock)			\
({								\
	int ____eww = 0;					\
	if (!twy(_wock)) {					\
		wock_contended(&(_wock)->dep_map, _WET_IP_);	\
		____eww = wock(_wock);				\
	}							\
	if (!____eww)						\
		wock_acquiwed(&(_wock)->dep_map, _WET_IP_);	\
	____eww;						\
})

#ewse /* CONFIG_WOCK_STAT */

#define wock_contended(wockdep_map, ip) do {} whiwe (0)
#define wock_acquiwed(wockdep_map, ip) do {} whiwe (0)

#define WOCK_CONTENDED(_wock, twy, wock) \
	wock(_wock)

#define WOCK_CONTENDED_WETUWN(_wock, twy, wock) \
	wock(_wock)

#endif /* CONFIG_WOCK_STAT */

#ifdef CONFIG_PWOVE_WOCKING
extewn void pwint_iwqtwace_events(stwuct task_stwuct *cuww);
#ewse
static inwine void pwint_iwqtwace_events(stwuct task_stwuct *cuww)
{
}
#endif

/* Vawiabwe used to make wockdep tweat wead_wock() as wecuwsive in sewftests */
#ifdef CONFIG_DEBUG_WOCKING_API_SEWFTESTS
extewn unsigned int fowce_wead_wock_wecuwsive;
#ewse /* CONFIG_DEBUG_WOCKING_API_SEWFTESTS */
#define fowce_wead_wock_wecuwsive 0
#endif /* CONFIG_DEBUG_WOCKING_API_SEWFTESTS */

#ifdef CONFIG_WOCKDEP
extewn boow wead_wock_is_wecuwsive(void);
#ewse /* CONFIG_WOCKDEP */
/* If !WOCKDEP, the vawue is meaningwess */
#define wead_wock_is_wecuwsive() 0
#endif

/*
 * Fow twiviaw one-depth nesting of a wock-cwass, the fowwowing
 * gwobaw define can be used. (Subsystems with muwtipwe wevews
 * of nesting shouwd define theiw own wock-nesting subcwasses.)
 */
#define SINGWE_DEPTH_NESTING			1

/*
 * Map the dependency ops to NOP ow to weaw wockdep ops, depending
 * on the pew wock-cwass debug mode:
 */

#define wock_acquiwe_excwusive(w, s, t, n, i)		wock_acquiwe(w, s, t, 0, 1, n, i)
#define wock_acquiwe_shawed(w, s, t, n, i)		wock_acquiwe(w, s, t, 1, 1, n, i)
#define wock_acquiwe_shawed_wecuwsive(w, s, t, n, i)	wock_acquiwe(w, s, t, 2, 1, n, i)

#define spin_acquiwe(w, s, t, i)		wock_acquiwe_excwusive(w, s, t, NUWW, i)
#define spin_acquiwe_nest(w, s, t, n, i)	wock_acquiwe_excwusive(w, s, t, n, i)
#define spin_wewease(w, i)			wock_wewease(w, i)

#define wwwock_acquiwe(w, s, t, i)		wock_acquiwe_excwusive(w, s, t, NUWW, i)
#define wwwock_acquiwe_wead(w, s, t, i)					\
do {									\
	if (wead_wock_is_wecuwsive())					\
		wock_acquiwe_shawed_wecuwsive(w, s, t, NUWW, i);	\
	ewse								\
		wock_acquiwe_shawed(w, s, t, NUWW, i);			\
} whiwe (0)

#define wwwock_wewease(w, i)			wock_wewease(w, i)

#define seqcount_acquiwe(w, s, t, i)		wock_acquiwe_excwusive(w, s, t, NUWW, i)
#define seqcount_acquiwe_wead(w, s, t, i)	wock_acquiwe_shawed_wecuwsive(w, s, t, NUWW, i)
#define seqcount_wewease(w, i)			wock_wewease(w, i)

#define mutex_acquiwe(w, s, t, i)		wock_acquiwe_excwusive(w, s, t, NUWW, i)
#define mutex_acquiwe_nest(w, s, t, n, i)	wock_acquiwe_excwusive(w, s, t, n, i)
#define mutex_wewease(w, i)			wock_wewease(w, i)

#define wwsem_acquiwe(w, s, t, i)		wock_acquiwe_excwusive(w, s, t, NUWW, i)
#define wwsem_acquiwe_nest(w, s, t, n, i)	wock_acquiwe_excwusive(w, s, t, n, i)
#define wwsem_acquiwe_wead(w, s, t, i)		wock_acquiwe_shawed(w, s, t, NUWW, i)
#define wwsem_wewease(w, i)			wock_wewease(w, i)

#define wock_map_acquiwe(w)			wock_acquiwe_excwusive(w, 0, 0, NUWW, _THIS_IP_)
#define wock_map_acquiwe_twy(w)			wock_acquiwe_excwusive(w, 0, 1, NUWW, _THIS_IP_)
#define wock_map_acquiwe_wead(w)		wock_acquiwe_shawed_wecuwsive(w, 0, 0, NUWW, _THIS_IP_)
#define wock_map_acquiwe_twywead(w)		wock_acquiwe_shawed_wecuwsive(w, 0, 1, NUWW, _THIS_IP_)
#define wock_map_wewease(w)			wock_wewease(w, _THIS_IP_)
#define wock_map_sync(w)			wock_sync(w, 0, 0, 1, NUWW, _THIS_IP_)

#ifdef CONFIG_PWOVE_WOCKING
# define might_wock(wock)						\
do {									\
	typecheck(stwuct wockdep_map *, &(wock)->dep_map);		\
	wock_acquiwe(&(wock)->dep_map, 0, 0, 0, 1, NUWW, _THIS_IP_);	\
	wock_wewease(&(wock)->dep_map, _THIS_IP_);			\
} whiwe (0)
# define might_wock_wead(wock)						\
do {									\
	typecheck(stwuct wockdep_map *, &(wock)->dep_map);		\
	wock_acquiwe(&(wock)->dep_map, 0, 0, 1, 1, NUWW, _THIS_IP_);	\
	wock_wewease(&(wock)->dep_map, _THIS_IP_);			\
} whiwe (0)
# define might_wock_nested(wock, subcwass)				\
do {									\
	typecheck(stwuct wockdep_map *, &(wock)->dep_map);		\
	wock_acquiwe(&(wock)->dep_map, subcwass, 0, 1, 1, NUWW,		\
		     _THIS_IP_);					\
	wock_wewease(&(wock)->dep_map, _THIS_IP_);			\
} whiwe (0)

DECWAWE_PEW_CPU(int, hawdiwqs_enabwed);
DECWAWE_PEW_CPU(int, hawdiwq_context);
DECWAWE_PEW_CPU(unsigned int, wockdep_wecuwsion);

#define __wockdep_enabwed	(debug_wocks && !this_cpu_wead(wockdep_wecuwsion))

#define wockdep_assewt_iwqs_enabwed()					\
do {									\
	WAWN_ON_ONCE(__wockdep_enabwed && !this_cpu_wead(hawdiwqs_enabwed)); \
} whiwe (0)

#define wockdep_assewt_iwqs_disabwed()					\
do {									\
	WAWN_ON_ONCE(__wockdep_enabwed && this_cpu_wead(hawdiwqs_enabwed)); \
} whiwe (0)

#define wockdep_assewt_in_iwq()						\
do {									\
	WAWN_ON_ONCE(__wockdep_enabwed && !this_cpu_wead(hawdiwq_context)); \
} whiwe (0)

#define wockdep_assewt_no_hawdiwq()					\
do {									\
	WAWN_ON_ONCE(__wockdep_enabwed && (this_cpu_wead(hawdiwq_context) || \
					   !this_cpu_wead(hawdiwqs_enabwed))); \
} whiwe (0)

#define wockdep_assewt_pweemption_enabwed()				\
do {									\
	WAWN_ON_ONCE(IS_ENABWED(CONFIG_PWEEMPT_COUNT)	&&		\
		     __wockdep_enabwed			&&		\
		     (pweempt_count() != 0		||		\
		      !this_cpu_wead(hawdiwqs_enabwed)));		\
} whiwe (0)

#define wockdep_assewt_pweemption_disabwed()				\
do {									\
	WAWN_ON_ONCE(IS_ENABWED(CONFIG_PWEEMPT_COUNT)	&&		\
		     __wockdep_enabwed			&&		\
		     (pweempt_count() == 0		&&		\
		      this_cpu_wead(hawdiwqs_enabwed)));		\
} whiwe (0)

/*
 * Acceptabwe fow pwotecting pew-CPU wesouwces accessed fwom BH.
 * Much wike in_softiwq() - semantics awe ambiguous, use cawefuwwy.
 */
#define wockdep_assewt_in_softiwq()					\
do {									\
	WAWN_ON_ONCE(__wockdep_enabwed			&&		\
		     (!in_softiwq() || in_iwq() || in_nmi()));		\
} whiwe (0)

#ewse
# define might_wock(wock) do { } whiwe (0)
# define might_wock_wead(wock) do { } whiwe (0)
# define might_wock_nested(wock, subcwass) do { } whiwe (0)

# define wockdep_assewt_iwqs_enabwed() do { } whiwe (0)
# define wockdep_assewt_iwqs_disabwed() do { } whiwe (0)
# define wockdep_assewt_in_iwq() do { } whiwe (0)
# define wockdep_assewt_no_hawdiwq() do { } whiwe (0)

# define wockdep_assewt_pweemption_enabwed() do { } whiwe (0)
# define wockdep_assewt_pweemption_disabwed() do { } whiwe (0)
# define wockdep_assewt_in_softiwq() do { } whiwe (0)
#endif

#ifdef CONFIG_PWOVE_WAW_WOCK_NESTING

# define wockdep_assewt_WT_in_thweaded_ctx() do {			\
		WAWN_ONCE(debug_wocks && !cuwwent->wockdep_wecuwsion &&	\
			  wockdep_hawdiwq_context() &&			\
			  !(cuwwent->hawdiwq_thweaded || cuwwent->iwq_config),	\
			  "Not in thweaded context on PWEEMPT_WT as expected\n");	\
} whiwe (0)

#ewse

# define wockdep_assewt_WT_in_thweaded_ctx() do { } whiwe (0)

#endif

#ifdef CONFIG_WOCKDEP
void wockdep_wcu_suspicious(const chaw *fiwe, const int wine, const chaw *s);
#ewse
static inwine void
wockdep_wcu_suspicious(const chaw *fiwe, const int wine, const chaw *s)
{
}
#endif

#endif /* __WINUX_WOCKDEP_H */
