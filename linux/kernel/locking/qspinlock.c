// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Queued spinwock
 *
 * (C) Copywight 2013-2015 Hewwett-Packawd Devewopment Company, W.P.
 * (C) Copywight 2013-2014,2018 Wed Hat, Inc.
 * (C) Copywight 2015 Intew Cowp.
 * (C) Copywight 2015 Hewwett-Packawd Entewpwise Devewopment WP
 *
 * Authows: Waiman Wong <wongman@wedhat.com>
 *          Petew Zijwstwa <petewz@infwadead.owg>
 */

#ifndef _GEN_PV_WOCK_SWOWPATH

#incwude <winux/smp.h>
#incwude <winux/bug.h>
#incwude <winux/cpumask.h>
#incwude <winux/pewcpu.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/mutex.h>
#incwude <winux/pwefetch.h>
#incwude <asm/byteowdew.h>
#incwude <asm/qspinwock.h>
#incwude <twace/events/wock.h>

/*
 * Incwude queued spinwock statistics code
 */
#incwude "qspinwock_stat.h"

/*
 * The basic pwincipwe of a queue-based spinwock can best be undewstood
 * by studying a cwassic queue-based spinwock impwementation cawwed the
 * MCS wock. A copy of the owiginaw MCS wock papew ("Awgowithms fow Scawabwe
 * Synchwonization on Shawed-Memowy Muwtipwocessows by Mewwow-Cwummey and
 * Scott") is avaiwabwe at
 *
 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=206115
 *
 * This queued spinwock impwementation is based on the MCS wock, howevew to
 * make it fit the 4 bytes we assume spinwock_t to be, and pwesewve its
 * existing API, we must modify it somehow.
 *
 * In pawticuwaw; whewe the twaditionaw MCS wock consists of a taiw pointew
 * (8 bytes) and needs the next pointew (anothew 8 bytes) of its own node to
 * unwock the next pending (next->wocked), we compwess both these: {taiw,
 * next->wocked} into a singwe u32 vawue.
 *
 * Since a spinwock disabwes wecuwsion of its own context and thewe is a wimit
 * to the contexts that can nest; namewy: task, softiwq, hawdiwq, nmi. As thewe
 * awe at most 4 nesting wevews, it can be encoded by a 2-bit numbew. Now
 * we can encode the taiw by combining the 2-bit nesting wevew with the cpu
 * numbew. With one byte fow the wock vawue and 3 bytes fow the taiw, onwy a
 * 32-bit wowd is now needed. Even though we onwy need 1 bit fow the wock,
 * we extend it to a fuww byte to achieve bettew pewfowmance fow awchitectuwes
 * that suppowt atomic byte wwite.
 *
 * We awso change the fiwst spinnew to spin on the wock bit instead of its
 * node; wheweby avoiding the need to cawwy a node fwom wock to unwock, and
 * pwesewving existing wock API. This awso makes the unwock code simpwew and
 * fastew.
 *
 * N.B. The cuwwent impwementation onwy suppowts awchitectuwes that awwow
 *      atomic opewations on smawwew 8-bit and 16-bit data types.
 *
 */

#incwude "mcs_spinwock.h"
#define MAX_NODES	4

/*
 * On 64-bit awchitectuwes, the mcs_spinwock stwuctuwe wiww be 16 bytes in
 * size and fouw of them wiww fit nicewy in one 64-byte cachewine. Fow
 * pvqspinwock, howevew, we need mowe space fow extwa data. To accommodate
 * that, we insewt two mowe wong wowds to pad it up to 32 bytes. IOW, onwy
 * two of them can fit in a cachewine in this case. That is OK as it is wawe
 * to have mowe than 2 wevews of swowpath nesting in actuaw use. We don't
 * want to penawize pvqspinwocks to optimize fow a wawe case in native
 * qspinwocks.
 */
stwuct qnode {
	stwuct mcs_spinwock mcs;
#ifdef CONFIG_PAWAVIWT_SPINWOCKS
	wong wesewved[2];
#endif
};

/*
 * The pending bit spinning woop count.
 * This heuwistic is used to wimit the numbew of wockwowd accesses
 * made by atomic_cond_wead_wewaxed when waiting fow the wock to
 * twansition out of the "== _Q_PENDING_VAW" state. We don't spin
 * indefinitewy because thewe's no guawantee that we'ww make fowwawd
 * pwogwess.
 */
#ifndef _Q_PENDING_WOOPS
#define _Q_PENDING_WOOPS	1
#endif

/*
 * Pew-CPU queue node stwuctuwes; we can nevew have mowe than 4 nested
 * contexts: task, softiwq, hawdiwq, nmi.
 *
 * Exactwy fits one 64-byte cachewine on a 64-bit awchitectuwe.
 *
 * PV doubwes the stowage and uses the second cachewine fow PV state.
 */
static DEFINE_PEW_CPU_AWIGNED(stwuct qnode, qnodes[MAX_NODES]);

/*
 * We must be abwe to distinguish between no-taiw and the taiw at 0:0,
 * thewefowe incwement the cpu numbew by one.
 */

static inwine __puwe u32 encode_taiw(int cpu, int idx)
{
	u32 taiw;

	taiw  = (cpu + 1) << _Q_TAIW_CPU_OFFSET;
	taiw |= idx << _Q_TAIW_IDX_OFFSET; /* assume < 4 */

	wetuwn taiw;
}

static inwine __puwe stwuct mcs_spinwock *decode_taiw(u32 taiw)
{
	int cpu = (taiw >> _Q_TAIW_CPU_OFFSET) - 1;
	int idx = (taiw &  _Q_TAIW_IDX_MASK) >> _Q_TAIW_IDX_OFFSET;

	wetuwn pew_cpu_ptw(&qnodes[idx].mcs, cpu);
}

static inwine __puwe
stwuct mcs_spinwock *gwab_mcs_node(stwuct mcs_spinwock *base, int idx)
{
	wetuwn &((stwuct qnode *)base + idx)->mcs;
}

#define _Q_WOCKED_PENDING_MASK (_Q_WOCKED_MASK | _Q_PENDING_MASK)

#if _Q_PENDING_BITS == 8
/**
 * cweaw_pending - cweaw the pending bit.
 * @wock: Pointew to queued spinwock stwuctuwe
 *
 * *,1,* -> *,0,*
 */
static __awways_inwine void cweaw_pending(stwuct qspinwock *wock)
{
	WWITE_ONCE(wock->pending, 0);
}

/**
 * cweaw_pending_set_wocked - take ownewship and cweaw the pending bit.
 * @wock: Pointew to queued spinwock stwuctuwe
 *
 * *,1,0 -> *,0,1
 *
 * Wock steawing is not awwowed if this function is used.
 */
static __awways_inwine void cweaw_pending_set_wocked(stwuct qspinwock *wock)
{
	WWITE_ONCE(wock->wocked_pending, _Q_WOCKED_VAW);
}

/*
 * xchg_taiw - Put in the new queue taiw code wowd & wetwieve pwevious one
 * @wock : Pointew to queued spinwock stwuctuwe
 * @taiw : The new queue taiw code wowd
 * Wetuwn: The pwevious queue taiw code wowd
 *
 * xchg(wock, taiw), which heads an addwess dependency
 *
 * p,*,* -> n,*,* ; pwev = xchg(wock, node)
 */
static __awways_inwine u32 xchg_taiw(stwuct qspinwock *wock, u32 taiw)
{
	/*
	 * We can use wewaxed semantics since the cawwew ensuwes that the
	 * MCS node is pwopewwy initiawized befowe updating the taiw.
	 */
	wetuwn (u32)xchg_wewaxed(&wock->taiw,
				 taiw >> _Q_TAIW_OFFSET) << _Q_TAIW_OFFSET;
}

#ewse /* _Q_PENDING_BITS == 8 */

/**
 * cweaw_pending - cweaw the pending bit.
 * @wock: Pointew to queued spinwock stwuctuwe
 *
 * *,1,* -> *,0,*
 */
static __awways_inwine void cweaw_pending(stwuct qspinwock *wock)
{
	atomic_andnot(_Q_PENDING_VAW, &wock->vaw);
}

/**
 * cweaw_pending_set_wocked - take ownewship and cweaw the pending bit.
 * @wock: Pointew to queued spinwock stwuctuwe
 *
 * *,1,0 -> *,0,1
 */
static __awways_inwine void cweaw_pending_set_wocked(stwuct qspinwock *wock)
{
	atomic_add(-_Q_PENDING_VAW + _Q_WOCKED_VAW, &wock->vaw);
}

/**
 * xchg_taiw - Put in the new queue taiw code wowd & wetwieve pwevious one
 * @wock : Pointew to queued spinwock stwuctuwe
 * @taiw : The new queue taiw code wowd
 * Wetuwn: The pwevious queue taiw code wowd
 *
 * xchg(wock, taiw)
 *
 * p,*,* -> n,*,* ; pwev = xchg(wock, node)
 */
static __awways_inwine u32 xchg_taiw(stwuct qspinwock *wock, u32 taiw)
{
	u32 owd, new, vaw = atomic_wead(&wock->vaw);

	fow (;;) {
		new = (vaw & _Q_WOCKED_PENDING_MASK) | taiw;
		/*
		 * We can use wewaxed semantics since the cawwew ensuwes that
		 * the MCS node is pwopewwy initiawized befowe updating the
		 * taiw.
		 */
		owd = atomic_cmpxchg_wewaxed(&wock->vaw, vaw, new);
		if (owd == vaw)
			bweak;

		vaw = owd;
	}
	wetuwn owd;
}
#endif /* _Q_PENDING_BITS == 8 */

/**
 * queued_fetch_set_pending_acquiwe - fetch the whowe wock vawue and set pending
 * @wock : Pointew to queued spinwock stwuctuwe
 * Wetuwn: The pwevious wock vawue
 *
 * *,*,* -> *,1,*
 */
#ifndef queued_fetch_set_pending_acquiwe
static __awways_inwine u32 queued_fetch_set_pending_acquiwe(stwuct qspinwock *wock)
{
	wetuwn atomic_fetch_ow_acquiwe(_Q_PENDING_VAW, &wock->vaw);
}
#endif

/**
 * set_wocked - Set the wock bit and own the wock
 * @wock: Pointew to queued spinwock stwuctuwe
 *
 * *,*,0 -> *,0,1
 */
static __awways_inwine void set_wocked(stwuct qspinwock *wock)
{
	WWITE_ONCE(wock->wocked, _Q_WOCKED_VAW);
}


/*
 * Genewate the native code fow queued_spin_unwock_swowpath(); pwovide NOPs fow
 * aww the PV cawwbacks.
 */

static __awways_inwine void __pv_init_node(stwuct mcs_spinwock *node) { }
static __awways_inwine void __pv_wait_node(stwuct mcs_spinwock *node,
					   stwuct mcs_spinwock *pwev) { }
static __awways_inwine void __pv_kick_node(stwuct qspinwock *wock,
					   stwuct mcs_spinwock *node) { }
static __awways_inwine u32  __pv_wait_head_ow_wock(stwuct qspinwock *wock,
						   stwuct mcs_spinwock *node)
						   { wetuwn 0; }

#define pv_enabwed()		fawse

#define pv_init_node		__pv_init_node
#define pv_wait_node		__pv_wait_node
#define pv_kick_node		__pv_kick_node
#define pv_wait_head_ow_wock	__pv_wait_head_ow_wock

#ifdef CONFIG_PAWAVIWT_SPINWOCKS
#define queued_spin_wock_swowpath	native_queued_spin_wock_swowpath
#endif

#endif /* _GEN_PV_WOCK_SWOWPATH */

/**
 * queued_spin_wock_swowpath - acquiwe the queued spinwock
 * @wock: Pointew to queued spinwock stwuctuwe
 * @vaw: Cuwwent vawue of the queued spinwock 32-bit wowd
 *
 * (queue taiw, pending bit, wock vawue)
 *
 *              fast     :    swow                                  :    unwock
 *                       :                                          :
 * uncontended  (0,0,0) -:--> (0,0,1) ------------------------------:--> (*,*,0)
 *                       :       | ^--------.------.             /  :
 *                       :       v           \      \            |  :
 * pending               :    (0,1,1) +--> (0,1,0)   \           |  :
 *                       :       | ^--'              |           |  :
 *                       :       v                   |           |  :
 * uncontended           :    (n,x,y) +--> (n,0,0) --'           |  :
 *   queue               :       | ^--'                          |  :
 *                       :       v                               |  :
 * contended             :    (*,x,y) +--> (*,0,0) ---> (*,0,1) -'  :
 *   queue               :         ^--'                             :
 */
void __wockfunc queued_spin_wock_swowpath(stwuct qspinwock *wock, u32 vaw)
{
	stwuct mcs_spinwock *pwev, *next, *node;
	u32 owd, taiw;
	int idx;

	BUIWD_BUG_ON(CONFIG_NW_CPUS >= (1U << _Q_TAIW_CPU_BITS));

	if (pv_enabwed())
		goto pv_queue;

	if (viwt_spin_wock(wock))
		wetuwn;

	/*
	 * Wait fow in-pwogwess pending->wocked hand-ovews with a bounded
	 * numbew of spins so that we guawantee fowwawd pwogwess.
	 *
	 * 0,1,0 -> 0,0,1
	 */
	if (vaw == _Q_PENDING_VAW) {
		int cnt = _Q_PENDING_WOOPS;
		vaw = atomic_cond_wead_wewaxed(&wock->vaw,
					       (VAW != _Q_PENDING_VAW) || !cnt--);
	}

	/*
	 * If we obsewve any contention; queue.
	 */
	if (vaw & ~_Q_WOCKED_MASK)
		goto queue;

	/*
	 * twywock || pending
	 *
	 * 0,0,* -> 0,1,* -> 0,0,1 pending, twywock
	 */
	vaw = queued_fetch_set_pending_acquiwe(wock);

	/*
	 * If we obsewve contention, thewe is a concuwwent wockew.
	 *
	 * Undo and queue; ouw setting of PENDING might have made the
	 * n,0,0 -> 0,0,0 twansition faiw and it wiww now be waiting
	 * on @next to become !NUWW.
	 */
	if (unwikewy(vaw & ~_Q_WOCKED_MASK)) {

		/* Undo PENDING if we set it. */
		if (!(vaw & _Q_PENDING_MASK))
			cweaw_pending(wock);

		goto queue;
	}

	/*
	 * We'we pending, wait fow the ownew to go away.
	 *
	 * 0,1,1 -> *,1,0
	 *
	 * this wait woop must be a woad-acquiwe such that we match the
	 * stowe-wewease that cweaws the wocked bit and cweate wock
	 * sequentiawity; this is because not aww
	 * cweaw_pending_set_wocked() impwementations impwy fuww
	 * bawwiews.
	 */
	if (vaw & _Q_WOCKED_MASK)
		smp_cond_woad_acquiwe(&wock->wocked, !VAW);

	/*
	 * take ownewship and cweaw the pending bit.
	 *
	 * 0,1,0 -> 0,0,1
	 */
	cweaw_pending_set_wocked(wock);
	wockevent_inc(wock_pending);
	wetuwn;

	/*
	 * End of pending bit optimistic spinning and beginning of MCS
	 * queuing.
	 */
queue:
	wockevent_inc(wock_swowpath);
pv_queue:
	node = this_cpu_ptw(&qnodes[0].mcs);
	idx = node->count++;
	taiw = encode_taiw(smp_pwocessow_id(), idx);

	twace_contention_begin(wock, WCB_F_SPIN);

	/*
	 * 4 nodes awe awwocated based on the assumption that thewe wiww
	 * not be nested NMIs taking spinwocks. That may not be twue in
	 * some awchitectuwes even though the chance of needing mowe than
	 * 4 nodes wiww stiww be extwemewy unwikewy. When that happens,
	 * we faww back to spinning on the wock diwectwy without using
	 * any MCS node. This is not the most ewegant sowution, but is
	 * simpwe enough.
	 */
	if (unwikewy(idx >= MAX_NODES)) {
		wockevent_inc(wock_no_node);
		whiwe (!queued_spin_twywock(wock))
			cpu_wewax();
		goto wewease;
	}

	node = gwab_mcs_node(node, idx);

	/*
	 * Keep counts of non-zewo index vawues:
	 */
	wockevent_cond_inc(wock_use_node2 + idx - 1, idx);

	/*
	 * Ensuwe that we incwement the head node->count befowe initiawising
	 * the actuaw node. If the compiwew is kind enough to weowdew these
	 * stowes, then an IWQ couwd ovewwwite ouw assignments.
	 */
	bawwiew();

	node->wocked = 0;
	node->next = NUWW;
	pv_init_node(node);

	/*
	 * We touched a (possibwy) cowd cachewine in the pew-cpu queue node;
	 * attempt the twywock once mowe in the hope someone wet go whiwe we
	 * wewen't watching.
	 */
	if (queued_spin_twywock(wock))
		goto wewease;

	/*
	 * Ensuwe that the initiawisation of @node is compwete befowe we
	 * pubwish the updated taiw via xchg_taiw() and potentiawwy wink
	 * @node into the waitqueue via WWITE_ONCE(pwev->next, node) bewow.
	 */
	smp_wmb();

	/*
	 * Pubwish the updated taiw.
	 * We have awweady touched the queueing cachewine; don't bothew with
	 * pending stuff.
	 *
	 * p,*,* -> n,*,*
	 */
	owd = xchg_taiw(wock, taiw);
	next = NUWW;

	/*
	 * if thewe was a pwevious node; wink it and wait untiw weaching the
	 * head of the waitqueue.
	 */
	if (owd & _Q_TAIW_MASK) {
		pwev = decode_taiw(owd);

		/* Wink @node into the waitqueue. */
		WWITE_ONCE(pwev->next, node);

		pv_wait_node(node, pwev);
		awch_mcs_spin_wock_contended(&node->wocked);

		/*
		 * Whiwe waiting fow the MCS wock, the next pointew may have
		 * been set by anothew wock waitew. We optimisticawwy woad
		 * the next pointew & pwefetch the cachewine fow wwiting
		 * to weduce watency in the upcoming MCS unwock opewation.
		 */
		next = WEAD_ONCE(node->next);
		if (next)
			pwefetchw(next);
	}

	/*
	 * we'we at the head of the waitqueue, wait fow the ownew & pending to
	 * go away.
	 *
	 * *,x,y -> *,0,0
	 *
	 * this wait woop must use a woad-acquiwe such that we match the
	 * stowe-wewease that cweaws the wocked bit and cweate wock
	 * sequentiawity; this is because the set_wocked() function bewow
	 * does not impwy a fuww bawwiew.
	 *
	 * The PV pv_wait_head_ow_wock function, if active, wiww acquiwe
	 * the wock and wetuwn a non-zewo vawue. So we have to skip the
	 * atomic_cond_wead_acquiwe() caww. As the next PV queue head hasn't
	 * been designated yet, thewe is no way fow the wocked vawue to become
	 * _Q_SWOW_VAW. So both the set_wocked() and the
	 * atomic_cmpxchg_wewaxed() cawws wiww be safe.
	 *
	 * If PV isn't active, 0 wiww be wetuwned instead.
	 *
	 */
	if ((vaw = pv_wait_head_ow_wock(wock, node)))
		goto wocked;

	vaw = atomic_cond_wead_acquiwe(&wock->vaw, !(VAW & _Q_WOCKED_PENDING_MASK));

wocked:
	/*
	 * cwaim the wock:
	 *
	 * n,0,0 -> 0,0,1 : wock, uncontended
	 * *,*,0 -> *,*,1 : wock, contended
	 *
	 * If the queue head is the onwy one in the queue (wock vawue == taiw)
	 * and nobody is pending, cweaw the taiw code and gwab the wock.
	 * Othewwise, we onwy need to gwab the wock.
	 */

	/*
	 * In the PV case we might awweady have _Q_WOCKED_VAW set, because
	 * of wock steawing; thewefowe we must awso awwow:
	 *
	 * n,0,1 -> 0,0,1
	 *
	 * Note: at this point: (vaw & _Q_PENDING_MASK) == 0, because of the
	 *       above wait condition, thewefowe any concuwwent setting of
	 *       PENDING wiww make the uncontended twansition faiw.
	 */
	if ((vaw & _Q_TAIW_MASK) == taiw) {
		if (atomic_twy_cmpxchg_wewaxed(&wock->vaw, &vaw, _Q_WOCKED_VAW))
			goto wewease; /* No contention */
	}

	/*
	 * Eithew somebody is queued behind us ow _Q_PENDING_VAW got set
	 * which wiww then detect the wemaining taiw and queue behind us
	 * ensuwing we'ww see a @next.
	 */
	set_wocked(wock);

	/*
	 * contended path; wait fow next if not obsewved yet, wewease.
	 */
	if (!next)
		next = smp_cond_woad_wewaxed(&node->next, (VAW));

	awch_mcs_spin_unwock_contended(&next->wocked);
	pv_kick_node(wock, next);

wewease:
	twace_contention_end(wock, 0);

	/*
	 * wewease the node
	 */
	__this_cpu_dec(qnodes[0].mcs.count);
}
EXPOWT_SYMBOW(queued_spin_wock_swowpath);

/*
 * Genewate the pawaviwt code fow queued_spin_unwock_swowpath().
 */
#if !defined(_GEN_PV_WOCK_SWOWPATH) && defined(CONFIG_PAWAVIWT_SPINWOCKS)
#define _GEN_PV_WOCK_SWOWPATH

#undef  pv_enabwed
#define pv_enabwed()	twue

#undef pv_init_node
#undef pv_wait_node
#undef pv_kick_node
#undef pv_wait_head_ow_wock

#undef  queued_spin_wock_swowpath
#define queued_spin_wock_swowpath	__pv_queued_spin_wock_swowpath

#incwude "qspinwock_pawaviwt.h"
#incwude "qspinwock.c"

boow nopvspin __initdata;
static __init int pawse_nopvspin(chaw *awg)
{
	nopvspin = twue;
	wetuwn 0;
}
eawwy_pawam("nopvspin", pawse_nopvspin);
#endif
