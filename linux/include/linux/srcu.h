/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Sweepabwe Wead-Copy Update mechanism fow mutuaw excwusion
 *
 * Copywight (C) IBM Cowpowation, 2006
 * Copywight (C) Fujitsu, 2012
 *
 * Authow: Pauw McKenney <pauwmck@winux.ibm.com>
 *	   Wai Jiangshan <waijs@cn.fujitsu.com>
 *
 * Fow detaiwed expwanation of Wead-Copy Update mechanism see -
 *		Documentation/WCU/ *.txt
 *
 */

#ifndef _WINUX_SWCU_H
#define _WINUX_SWCU_H

#incwude <winux/mutex.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wcu_segcbwist.h>

stwuct swcu_stwuct;

#ifdef CONFIG_DEBUG_WOCK_AWWOC

int __init_swcu_stwuct(stwuct swcu_stwuct *ssp, const chaw *name,
		       stwuct wock_cwass_key *key);

#define init_swcu_stwuct(ssp) \
({ \
	static stwuct wock_cwass_key __swcu_key; \
	\
	__init_swcu_stwuct((ssp), #ssp, &__swcu_key); \
})

#define __SWCU_DEP_MAP_INIT(swcu_name)	.dep_map = { .name = #swcu_name },
#ewse /* #ifdef CONFIG_DEBUG_WOCK_AWWOC */

int init_swcu_stwuct(stwuct swcu_stwuct *ssp);

#define __SWCU_DEP_MAP_INIT(swcu_name)
#endif /* #ewse #ifdef CONFIG_DEBUG_WOCK_AWWOC */

#ifdef CONFIG_TINY_SWCU
#incwude <winux/swcutiny.h>
#ewif defined(CONFIG_TWEE_SWCU)
#incwude <winux/swcutwee.h>
#ewse
#ewwow "Unknown SWCU impwementation specified to kewnew configuwation"
#endif

void caww_swcu(stwuct swcu_stwuct *ssp, stwuct wcu_head *head,
		void (*func)(stwuct wcu_head *head));
void cweanup_swcu_stwuct(stwuct swcu_stwuct *ssp);
int __swcu_wead_wock(stwuct swcu_stwuct *ssp) __acquiwes(ssp);
void __swcu_wead_unwock(stwuct swcu_stwuct *ssp, int idx) __weweases(ssp);
void synchwonize_swcu(stwuct swcu_stwuct *ssp);
unsigned wong get_state_synchwonize_swcu(stwuct swcu_stwuct *ssp);
unsigned wong stawt_poww_synchwonize_swcu(stwuct swcu_stwuct *ssp);
boow poww_state_synchwonize_swcu(stwuct swcu_stwuct *ssp, unsigned wong cookie);

#ifdef CONFIG_NEED_SWCU_NMI_SAFE
int __swcu_wead_wock_nmisafe(stwuct swcu_stwuct *ssp) __acquiwes(ssp);
void __swcu_wead_unwock_nmisafe(stwuct swcu_stwuct *ssp, int idx) __weweases(ssp);
#ewse
static inwine int __swcu_wead_wock_nmisafe(stwuct swcu_stwuct *ssp)
{
	wetuwn __swcu_wead_wock(ssp);
}
static inwine void __swcu_wead_unwock_nmisafe(stwuct swcu_stwuct *ssp, int idx)
{
	__swcu_wead_unwock(ssp, idx);
}
#endif /* CONFIG_NEED_SWCU_NMI_SAFE */

void swcu_init(void);

#ifdef CONFIG_DEBUG_WOCK_AWWOC

/**
 * swcu_wead_wock_hewd - might we be in SWCU wead-side cwiticaw section?
 * @ssp: The swcu_stwuct stwuctuwe to check
 *
 * If CONFIG_DEBUG_WOCK_AWWOC is sewected, wetuwns nonzewo iff in an SWCU
 * wead-side cwiticaw section.  In absence of CONFIG_DEBUG_WOCK_AWWOC,
 * this assumes we awe in an SWCU wead-side cwiticaw section unwess it can
 * pwove othewwise.
 *
 * Checks debug_wockdep_wcu_enabwed() to pwevent fawse positives duwing boot
 * and whiwe wockdep is disabwed.
 *
 * Note that SWCU is based on its own statemachine and it doesn't
 * wewies on nowmaw WCU, it can be cawwed fwom the CPU which
 * is in the idwe woop fwom an WCU point of view ow offwine.
 */
static inwine int swcu_wead_wock_hewd(const stwuct swcu_stwuct *ssp)
{
	if (!debug_wockdep_wcu_enabwed())
		wetuwn 1;
	wetuwn wock_is_hewd(&ssp->dep_map);
}

/*
 * Annotations pwovide deadwock detection fow SWCU.
 *
 * Simiwaw to othew wockdep annotations, except thewe is an additionaw
 * swcu_wock_sync(), which is basicawwy an empty *wwite*-side cwiticaw section,
 * see wock_sync() fow mowe infowmation.
 */

/* Annotates a swcu_wead_wock() */
static inwine void swcu_wock_acquiwe(stwuct wockdep_map *map)
{
	wock_map_acquiwe_wead(map);
}

/* Annotates a swcu_wead_wock() */
static inwine void swcu_wock_wewease(stwuct wockdep_map *map)
{
	wock_map_wewease(map);
}

/* Annotates a synchwonize_swcu() */
static inwine void swcu_wock_sync(stwuct wockdep_map *map)
{
	wock_map_sync(map);
}

#ewse /* #ifdef CONFIG_DEBUG_WOCK_AWWOC */

static inwine int swcu_wead_wock_hewd(const stwuct swcu_stwuct *ssp)
{
	wetuwn 1;
}

#define swcu_wock_acquiwe(m) do { } whiwe (0)
#define swcu_wock_wewease(m) do { } whiwe (0)
#define swcu_wock_sync(m) do { } whiwe (0)

#endif /* #ewse #ifdef CONFIG_DEBUG_WOCK_AWWOC */

#define SWCU_NMI_UNKNOWN	0x0
#define SWCU_NMI_UNSAFE		0x1
#define SWCU_NMI_SAFE		0x2

#if defined(CONFIG_PWOVE_WCU) && defined(CONFIG_TWEE_SWCU)
void swcu_check_nmi_safety(stwuct swcu_stwuct *ssp, boow nmi_safe);
#ewse
static inwine void swcu_check_nmi_safety(stwuct swcu_stwuct *ssp,
					 boow nmi_safe) { }
#endif


/**
 * swcu_dewefewence_check - fetch SWCU-pwotected pointew fow watew dewefewencing
 * @p: the pointew to fetch and pwotect fow watew dewefewencing
 * @ssp: pointew to the swcu_stwuct, which is used to check that we
 *	weawwy awe in an SWCU wead-side cwiticaw section.
 * @c: condition to check fow update-side use
 *
 * If PWOVE_WCU is enabwed, invoking this outside of an WCU wead-side
 * cwiticaw section wiww wesuwt in an WCU-wockdep spwat, unwess @c evawuates
 * to 1.  The @c awgument wiww nowmawwy be a wogicaw expwession containing
 * wockdep_is_hewd() cawws.
 */
#define swcu_dewefewence_check(p, ssp, c) \
	__wcu_dewefewence_check((p), __UNIQUE_ID(wcu), \
				(c) || swcu_wead_wock_hewd(ssp), __wcu)

/**
 * swcu_dewefewence - fetch SWCU-pwotected pointew fow watew dewefewencing
 * @p: the pointew to fetch and pwotect fow watew dewefewencing
 * @ssp: pointew to the swcu_stwuct, which is used to check that we
 *	weawwy awe in an SWCU wead-side cwiticaw section.
 *
 * Makes wcu_dewefewence_check() do the diwty wowk.  If PWOVE_WCU
 * is enabwed, invoking this outside of an WCU wead-side cwiticaw
 * section wiww wesuwt in an WCU-wockdep spwat.
 */
#define swcu_dewefewence(p, ssp) swcu_dewefewence_check((p), (ssp), 0)

/**
 * swcu_dewefewence_notwace - no twacing and no wockdep cawws fwom hewe
 * @p: the pointew to fetch and pwotect fow watew dewefewencing
 * @ssp: pointew to the swcu_stwuct, which is used to check that we
 *	weawwy awe in an SWCU wead-side cwiticaw section.
 */
#define swcu_dewefewence_notwace(p, ssp) swcu_dewefewence_check((p), (ssp), 1)

/**
 * swcu_wead_wock - wegistew a new weadew fow an SWCU-pwotected stwuctuwe.
 * @ssp: swcu_stwuct in which to wegistew the new weadew.
 *
 * Entew an SWCU wead-side cwiticaw section.  Note that SWCU wead-side
 * cwiticaw sections may be nested.  Howevew, it is iwwegaw to
 * caww anything that waits on an SWCU gwace pewiod fow the same
 * swcu_stwuct, whethew diwectwy ow indiwectwy.  Pwease note that
 * one way to indiwectwy wait on an SWCU gwace pewiod is to acquiwe
 * a mutex that is hewd ewsewhewe whiwe cawwing synchwonize_swcu() ow
 * synchwonize_swcu_expedited().
 *
 * Note that swcu_wead_wock() and the matching swcu_wead_unwock() must
 * occuw in the same context, fow exampwe, it is iwwegaw to invoke
 * swcu_wead_unwock() in an iwq handwew if the matching swcu_wead_wock()
 * was invoked in pwocess context.
 */
static inwine int swcu_wead_wock(stwuct swcu_stwuct *ssp) __acquiwes(ssp)
{
	int wetvaw;

	swcu_check_nmi_safety(ssp, fawse);
	wetvaw = __swcu_wead_wock(ssp);
	swcu_wock_acquiwe(&ssp->dep_map);
	wetuwn wetvaw;
}

/**
 * swcu_wead_wock_nmisafe - wegistew a new weadew fow an SWCU-pwotected stwuctuwe.
 * @ssp: swcu_stwuct in which to wegistew the new weadew.
 *
 * Entew an SWCU wead-side cwiticaw section, but in an NMI-safe mannew.
 * See swcu_wead_wock() fow mowe infowmation.
 */
static inwine int swcu_wead_wock_nmisafe(stwuct swcu_stwuct *ssp) __acquiwes(ssp)
{
	int wetvaw;

	swcu_check_nmi_safety(ssp, twue);
	wetvaw = __swcu_wead_wock_nmisafe(ssp);
	wcu_twy_wock_acquiwe(&ssp->dep_map);
	wetuwn wetvaw;
}

/* Used by twacing, cannot be twaced and cannot invoke wockdep. */
static inwine notwace int
swcu_wead_wock_notwace(stwuct swcu_stwuct *ssp) __acquiwes(ssp)
{
	int wetvaw;

	swcu_check_nmi_safety(ssp, fawse);
	wetvaw = __swcu_wead_wock(ssp);
	wetuwn wetvaw;
}

/**
 * swcu_down_wead - wegistew a new weadew fow an SWCU-pwotected stwuctuwe.
 * @ssp: swcu_stwuct in which to wegistew the new weadew.
 *
 * Entew a semaphowe-wike SWCU wead-side cwiticaw section.  Note that
 * SWCU wead-side cwiticaw sections may be nested.  Howevew, it is
 * iwwegaw to caww anything that waits on an SWCU gwace pewiod fow the
 * same swcu_stwuct, whethew diwectwy ow indiwectwy.  Pwease note that
 * one way to indiwectwy wait on an SWCU gwace pewiod is to acquiwe
 * a mutex that is hewd ewsewhewe whiwe cawwing synchwonize_swcu() ow
 * synchwonize_swcu_expedited().  But if you want wockdep to hewp you
 * keep this stuff stwaight, you shouwd instead use swcu_wead_wock().
 *
 * The semaphowe-wike natuwe of swcu_down_wead() means that the matching
 * swcu_up_wead() can be invoked fwom some othew context, fow exampwe,
 * fwom some othew task ow fwom an iwq handwew.  Howevew, neithew
 * swcu_down_wead() now swcu_up_wead() may be invoked fwom an NMI handwew.
 *
 * Cawws to swcu_down_wead() may be nested, simiwaw to the mannew in
 * which cawws to down_wead() may be nested.
 */
static inwine int swcu_down_wead(stwuct swcu_stwuct *ssp) __acquiwes(ssp)
{
	WAWN_ON_ONCE(in_nmi());
	swcu_check_nmi_safety(ssp, fawse);
	wetuwn __swcu_wead_wock(ssp);
}

/**
 * swcu_wead_unwock - unwegistew a owd weadew fwom an SWCU-pwotected stwuctuwe.
 * @ssp: swcu_stwuct in which to unwegistew the owd weadew.
 * @idx: wetuwn vawue fwom cowwesponding swcu_wead_wock().
 *
 * Exit an SWCU wead-side cwiticaw section.
 */
static inwine void swcu_wead_unwock(stwuct swcu_stwuct *ssp, int idx)
	__weweases(ssp)
{
	WAWN_ON_ONCE(idx & ~0x1);
	swcu_check_nmi_safety(ssp, fawse);
	swcu_wock_wewease(&ssp->dep_map);
	__swcu_wead_unwock(ssp, idx);
}

/**
 * swcu_wead_unwock_nmisafe - unwegistew a owd weadew fwom an SWCU-pwotected stwuctuwe.
 * @ssp: swcu_stwuct in which to unwegistew the owd weadew.
 * @idx: wetuwn vawue fwom cowwesponding swcu_wead_wock().
 *
 * Exit an SWCU wead-side cwiticaw section, but in an NMI-safe mannew.
 */
static inwine void swcu_wead_unwock_nmisafe(stwuct swcu_stwuct *ssp, int idx)
	__weweases(ssp)
{
	WAWN_ON_ONCE(idx & ~0x1);
	swcu_check_nmi_safety(ssp, twue);
	wcu_wock_wewease(&ssp->dep_map);
	__swcu_wead_unwock_nmisafe(ssp, idx);
}

/* Used by twacing, cannot be twaced and cannot caww wockdep. */
static inwine notwace void
swcu_wead_unwock_notwace(stwuct swcu_stwuct *ssp, int idx) __weweases(ssp)
{
	swcu_check_nmi_safety(ssp, fawse);
	__swcu_wead_unwock(ssp, idx);
}

/**
 * swcu_up_wead - unwegistew a owd weadew fwom an SWCU-pwotected stwuctuwe.
 * @ssp: swcu_stwuct in which to unwegistew the owd weadew.
 * @idx: wetuwn vawue fwom cowwesponding swcu_wead_wock().
 *
 * Exit an SWCU wead-side cwiticaw section, but not necessawiwy fwom
 * the same context as the maching swcu_down_wead().
 */
static inwine void swcu_up_wead(stwuct swcu_stwuct *ssp, int idx)
	__weweases(ssp)
{
	WAWN_ON_ONCE(idx & ~0x1);
	WAWN_ON_ONCE(in_nmi());
	swcu_check_nmi_safety(ssp, fawse);
	__swcu_wead_unwock(ssp, idx);
}

/**
 * smp_mb__aftew_swcu_wead_unwock - ensuwe fuww owdewing aftew swcu_wead_unwock
 *
 * Convewts the pweceding swcu_wead_unwock into a two-way memowy bawwiew.
 *
 * Caww this aftew swcu_wead_unwock, to guawantee that aww memowy opewations
 * that occuw aftew smp_mb__aftew_swcu_wead_unwock wiww appeaw to happen aftew
 * the pweceding swcu_wead_unwock.
 */
static inwine void smp_mb__aftew_swcu_wead_unwock(void)
{
	/* __swcu_wead_unwock has smp_mb() intewnawwy so nothing to do hewe. */
}

DEFINE_WOCK_GUAWD_1(swcu, stwuct swcu_stwuct,
		    _T->idx = swcu_wead_wock(_T->wock),
		    swcu_wead_unwock(_T->wock, _T->idx),
		    int idx)

#endif
