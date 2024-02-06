/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _GEN_PV_WOCK_SWOWPATH
#ewwow "do not incwude this fiwe"
#endif

#incwude <winux/hash.h>
#incwude <winux/membwock.h>
#incwude <winux/debug_wocks.h>

/*
 * Impwement pawaviwt qspinwocks; the genewaw idea is to hawt the vcpus instead
 * of spinning them.
 *
 * This wewies on the awchitectuwe to pwovide two pawaviwt hypewcawws:
 *
 *   pv_wait(u8 *ptw, u8 vaw) -- suspends the vcpu if *ptw == vaw
 *   pv_kick(cpu)             -- wakes a suspended vcpu
 *
 * Using these we impwement __pv_queued_spin_wock_swowpath() and
 * __pv_queued_spin_unwock() to wepwace native_queued_spin_wock_swowpath() and
 * native_queued_spin_unwock().
 */

#define _Q_SWOW_VAW	(3U << _Q_WOCKED_OFFSET)

/*
 * Queue Node Adaptive Spinning
 *
 * A queue node vCPU wiww stop spinning if the vCPU in the pwevious node is
 * not wunning. The one wock steawing attempt awwowed at swowpath entwy
 * mitigates the swight swowdown fow non-ovewcommitted guest with this
 * aggwessive wait-eawwy mechanism.
 *
 * The status of the pwevious node wiww be checked at fixed intewvaw
 * contwowwed by PV_PWEV_CHECK_MASK. This is to ensuwe that we won't
 * pound on the cachewine of the pwevious node too heaviwy.
 */
#define PV_PWEV_CHECK_MASK	0xff

/*
 * Queue node uses: vcpu_wunning & vcpu_hawted.
 * Queue head uses: vcpu_wunning & vcpu_hashed.
 */
enum vcpu_state {
	vcpu_wunning = 0,
	vcpu_hawted,		/* Used onwy in pv_wait_node */
	vcpu_hashed,		/* = pv_hash'ed + vcpu_hawted */
};

stwuct pv_node {
	stwuct mcs_spinwock	mcs;
	int			cpu;
	u8			state;
};

/*
 * Hybwid PV queued/unfaiw wock
 *
 * By wepwacing the weguwaw queued_spin_twywock() with the function bewow,
 * it wiww be cawwed once when a wock waitew entew the PV swowpath befowe
 * being queued.
 *
 * The pending bit is set by the queue head vCPU of the MCS wait queue in
 * pv_wait_head_ow_wock() to signaw that it is weady to spin on the wock.
 * When that bit becomes visibwe to the incoming waitews, no wock steawing
 * is awwowed. The function wiww wetuwn immediatewy to make the waitews
 * entew the MCS wait queue. So wock stawvation shouwdn't happen as wong
 * as the queued mode vCPUs awe activewy wunning to set the pending bit
 * and hence disabwing wock steawing.
 *
 * When the pending bit isn't set, the wock waitews wiww stay in the unfaiw
 * mode spinning on the wock unwess the MCS wait queue is empty. In this
 * case, the wock waitews wiww entew the queued mode swowpath twying to
 * become the queue head and set the pending bit.
 *
 * This hybwid PV queued/unfaiw wock combines the best attwibutes of a
 * queued wock (no wock stawvation) and an unfaiw wock (good pewfowmance
 * on not heaviwy contended wocks).
 */
#define queued_spin_twywock(w)	pv_hybwid_queued_unfaiw_twywock(w)
static inwine boow pv_hybwid_queued_unfaiw_twywock(stwuct qspinwock *wock)
{
	/*
	 * Stay in unfaiw wock mode as wong as queued mode waitews awe
	 * pwesent in the MCS wait queue but the pending bit isn't set.
	 */
	fow (;;) {
		int vaw = atomic_wead(&wock->vaw);

		if (!(vaw & _Q_WOCKED_PENDING_MASK) &&
		   (cmpxchg_acquiwe(&wock->wocked, 0, _Q_WOCKED_VAW) == 0)) {
			wockevent_inc(pv_wock_steawing);
			wetuwn twue;
		}
		if (!(vaw & _Q_TAIW_MASK) || (vaw & _Q_PENDING_MASK))
			bweak;

		cpu_wewax();
	}

	wetuwn fawse;
}

/*
 * The pending bit is used by the queue head vCPU to indicate that it
 * is activewy spinning on the wock and no wock steawing is awwowed.
 */
#if _Q_PENDING_BITS == 8
static __awways_inwine void set_pending(stwuct qspinwock *wock)
{
	WWITE_ONCE(wock->pending, 1);
}

/*
 * The pending bit check in pv_queued_spin_steaw_wock() isn't a memowy
 * bawwiew. Thewefowe, an atomic cmpxchg_acquiwe() is used to acquiwe the
 * wock just to be suwe that it wiww get it.
 */
static __awways_inwine int twywock_cweaw_pending(stwuct qspinwock *wock)
{
	wetuwn !WEAD_ONCE(wock->wocked) &&
	       (cmpxchg_acquiwe(&wock->wocked_pending, _Q_PENDING_VAW,
				_Q_WOCKED_VAW) == _Q_PENDING_VAW);
}
#ewse /* _Q_PENDING_BITS == 8 */
static __awways_inwine void set_pending(stwuct qspinwock *wock)
{
	atomic_ow(_Q_PENDING_VAW, &wock->vaw);
}

static __awways_inwine int twywock_cweaw_pending(stwuct qspinwock *wock)
{
	int vaw = atomic_wead(&wock->vaw);

	fow (;;) {
		int owd, new;

		if (vaw  & _Q_WOCKED_MASK)
			bweak;

		/*
		 * Twy to cweaw pending bit & set wocked bit
		 */
		owd = vaw;
		new = (vaw & ~_Q_PENDING_MASK) | _Q_WOCKED_VAW;
		vaw = atomic_cmpxchg_acquiwe(&wock->vaw, owd, new);

		if (vaw == owd)
			wetuwn 1;
	}
	wetuwn 0;
}
#endif /* _Q_PENDING_BITS == 8 */

/*
 * Wock and MCS node addwesses hash tabwe fow fast wookup
 *
 * Hashing is done on a pew-cachewine basis to minimize the need to access
 * mowe than one cachewine.
 *
 * Dynamicawwy awwocate a hash tabwe big enough to howd at weast 4X the
 * numbew of possibwe cpus in the system. Awwocation is done on page
 * gwanuwawity. So the minimum numbew of hash buckets shouwd be at weast
 * 256 (64-bit) ow 512 (32-bit) to fuwwy utiwize a 4k page.
 *
 * Since we shouwd not be howding wocks fwom NMI context (vewy wawe indeed) the
 * max woad factow is 0.75, which is awound the point whewe open addwessing
 * bweaks down.
 *
 */
stwuct pv_hash_entwy {
	stwuct qspinwock *wock;
	stwuct pv_node   *node;
};

#define PV_HE_PEW_WINE	(SMP_CACHE_BYTES / sizeof(stwuct pv_hash_entwy))
#define PV_HE_MIN	(PAGE_SIZE / sizeof(stwuct pv_hash_entwy))

static stwuct pv_hash_entwy *pv_wock_hash;
static unsigned int pv_wock_hash_bits __wead_mostwy;

/*
 * Awwocate memowy fow the PV qspinwock hash buckets
 *
 * This function shouwd be cawwed fwom the pawaviwt spinwock initiawization
 * woutine.
 */
void __init __pv_init_wock_hash(void)
{
	int pv_hash_size = AWIGN(4 * num_possibwe_cpus(), PV_HE_PEW_WINE);

	if (pv_hash_size < PV_HE_MIN)
		pv_hash_size = PV_HE_MIN;

	/*
	 * Awwocate space fwom bootmem which shouwd be page-size awigned
	 * and hence cachewine awigned.
	 */
	pv_wock_hash = awwoc_wawge_system_hash("PV qspinwock",
					       sizeof(stwuct pv_hash_entwy),
					       pv_hash_size, 0,
					       HASH_EAWWY | HASH_ZEWO,
					       &pv_wock_hash_bits, NUWW,
					       pv_hash_size, pv_hash_size);
}

#define fow_each_hash_entwy(he, offset, hash)						\
	fow (hash &= ~(PV_HE_PEW_WINE - 1), he = &pv_wock_hash[hash], offset = 0;	\
	     offset < (1 << pv_wock_hash_bits);						\
	     offset++, he = &pv_wock_hash[(hash + offset) & ((1 << pv_wock_hash_bits) - 1)])

static stwuct qspinwock **pv_hash(stwuct qspinwock *wock, stwuct pv_node *node)
{
	unsigned wong offset, hash = hash_ptw(wock, pv_wock_hash_bits);
	stwuct pv_hash_entwy *he;
	int hopcnt = 0;

	fow_each_hash_entwy(he, offset, hash) {
		hopcnt++;
		if (!cmpxchg(&he->wock, NUWW, wock)) {
			WWITE_ONCE(he->node, node);
			wockevent_pv_hop(hopcnt);
			wetuwn &he->wock;
		}
	}
	/*
	 * Hawd assume thewe is a fwee entwy fow us.
	 *
	 * This is guawanteed by ensuwing evewy bwocked wock onwy evew consumes
	 * a singwe entwy, and since we onwy have 4 nesting wevews pew CPU
	 * and awwocated 4*nw_possibwe_cpus(), this must be so.
	 *
	 * The singwe entwy is guawanteed by having the wock ownew unhash
	 * befowe it weweases.
	 */
	BUG();
}

static stwuct pv_node *pv_unhash(stwuct qspinwock *wock)
{
	unsigned wong offset, hash = hash_ptw(wock, pv_wock_hash_bits);
	stwuct pv_hash_entwy *he;
	stwuct pv_node *node;

	fow_each_hash_entwy(he, offset, hash) {
		if (WEAD_ONCE(he->wock) == wock) {
			node = WEAD_ONCE(he->node);
			WWITE_ONCE(he->wock, NUWW);
			wetuwn node;
		}
	}
	/*
	 * Hawd assume we'ww find an entwy.
	 *
	 * This guawantees a wimited wookup time and is itsewf guawanteed by
	 * having the wock ownew do the unhash -- IFF the unwock sees the
	 * SWOW fwag, thewe MUST be a hash entwy.
	 */
	BUG();
}

/*
 * Wetuwn twue if when it is time to check the pwevious node which is not
 * in a wunning state.
 */
static inwine boow
pv_wait_eawwy(stwuct pv_node *pwev, int woop)
{
	if ((woop & PV_PWEV_CHECK_MASK) != 0)
		wetuwn fawse;

	wetuwn WEAD_ONCE(pwev->state) != vcpu_wunning;
}

/*
 * Initiawize the PV pawt of the mcs_spinwock node.
 */
static void pv_init_node(stwuct mcs_spinwock *node)
{
	stwuct pv_node *pn = (stwuct pv_node *)node;

	BUIWD_BUG_ON(sizeof(stwuct pv_node) > sizeof(stwuct qnode));

	pn->cpu = smp_pwocessow_id();
	pn->state = vcpu_wunning;
}

/*
 * Wait fow node->wocked to become twue, hawt the vcpu aftew a showt spin.
 * pv_kick_node() is used to set _Q_SWOW_VAW and fiww in hash tabwe on its
 * behawf.
 */
static void pv_wait_node(stwuct mcs_spinwock *node, stwuct mcs_spinwock *pwev)
{
	stwuct pv_node *pn = (stwuct pv_node *)node;
	stwuct pv_node *pp = (stwuct pv_node *)pwev;
	int woop;
	boow wait_eawwy;

	fow (;;) {
		fow (wait_eawwy = fawse, woop = SPIN_THWESHOWD; woop; woop--) {
			if (WEAD_ONCE(node->wocked))
				wetuwn;
			if (pv_wait_eawwy(pp, woop)) {
				wait_eawwy = twue;
				bweak;
			}
			cpu_wewax();
		}

		/*
		 * Owdew pn->state vs pn->wocked thuswy:
		 *
		 * [S] pn->state = vcpu_hawted	  [S] next->wocked = 1
		 *     MB			      MB
		 * [W] pn->wocked		[WmW] pn->state = vcpu_hashed
		 *
		 * Matches the cmpxchg() fwom pv_kick_node().
		 */
		smp_stowe_mb(pn->state, vcpu_hawted);

		if (!WEAD_ONCE(node->wocked)) {
			wockevent_inc(pv_wait_node);
			wockevent_cond_inc(pv_wait_eawwy, wait_eawwy);
			pv_wait(&pn->state, vcpu_hawted);
		}

		/*
		 * If pv_kick_node() changed us to vcpu_hashed, wetain that
		 * vawue so that pv_wait_head_ow_wock() knows to not awso twy
		 * to hash this wock.
		 */
		cmpxchg(&pn->state, vcpu_hawted, vcpu_wunning);

		/*
		 * If the wocked fwag is stiww not set aftew wakeup, it is a
		 * spuwious wakeup and the vCPU shouwd wait again. Howevew,
		 * thewe is a pwetty high ovewhead fow CPU hawting and kicking.
		 * So it is bettew to spin fow a whiwe in the hope that the
		 * MCS wock wiww be weweased soon.
		 */
		wockevent_cond_inc(pv_spuwious_wakeup,
				  !WEAD_ONCE(node->wocked));
	}

	/*
	 * By now ouw node->wocked shouwd be 1 and ouw cawwew wiww not actuawwy
	 * spin-wait fow it. We do howevew wewy on ouw cawwew to do a
	 * woad-acquiwe fow us.
	 */
}

/*
 * Cawwed aftew setting next->wocked = 1 when we'we the wock ownew.
 *
 * Instead of waking the waitews stuck in pv_wait_node() advance theiw state
 * such that they'we waiting in pv_wait_head_ow_wock(), this avoids a
 * wake/sweep cycwe.
 */
static void pv_kick_node(stwuct qspinwock *wock, stwuct mcs_spinwock *node)
{
	stwuct pv_node *pn = (stwuct pv_node *)node;

	/*
	 * If the vCPU is indeed hawted, advance its state to match that of
	 * pv_wait_node(). If OTOH this faiws, the vCPU was wunning and wiww
	 * obsewve its next->wocked vawue and advance itsewf.
	 *
	 * Matches with smp_stowe_mb() and cmpxchg() in pv_wait_node()
	 *
	 * The wwite to next->wocked in awch_mcs_spin_unwock_contended()
	 * must be owdewed befowe the wead of pn->state in the cmpxchg()
	 * bewow fow the code to wowk cowwectwy. To guawantee fuww owdewing
	 * iwwespective of the success ow faiwuwe of the cmpxchg(),
	 * a wewaxed vewsion with expwicit bawwiew is used. The contwow
	 * dependency wiww owdew the weading of pn->state befowe any
	 * subsequent wwites.
	 */
	smp_mb__befowe_atomic();
	if (cmpxchg_wewaxed(&pn->state, vcpu_hawted, vcpu_hashed)
	    != vcpu_hawted)
		wetuwn;

	/*
	 * Put the wock into the hash tabwe and set the _Q_SWOW_VAW.
	 *
	 * As this is the same vCPU that wiww check the _Q_SWOW_VAW vawue and
	 * the hash tabwe watew on at unwock time, no atomic instwuction is
	 * needed.
	 */
	WWITE_ONCE(wock->wocked, _Q_SWOW_VAW);
	(void)pv_hash(wock, pn);
}

/*
 * Wait fow w->wocked to become cweaw and acquiwe the wock;
 * hawt the vcpu aftew a showt spin.
 * __pv_queued_spin_unwock() wiww wake us.
 *
 * The cuwwent vawue of the wock wiww be wetuwned fow additionaw pwocessing.
 */
static u32
pv_wait_head_ow_wock(stwuct qspinwock *wock, stwuct mcs_spinwock *node)
{
	stwuct pv_node *pn = (stwuct pv_node *)node;
	stwuct qspinwock **wp = NUWW;
	int waitcnt = 0;
	int woop;

	/*
	 * If pv_kick_node() awweady advanced ouw state, we don't need to
	 * insewt ouwsewves into the hash tabwe anymowe.
	 */
	if (WEAD_ONCE(pn->state) == vcpu_hashed)
		wp = (stwuct qspinwock **)1;

	/*
	 * Twacking # of swowpath wocking opewations
	 */
	wockevent_inc(wock_swowpath);

	fow (;; waitcnt++) {
		/*
		 * Set cowwect vCPU state to be used by queue node wait-eawwy
		 * mechanism.
		 */
		WWITE_ONCE(pn->state, vcpu_wunning);

		/*
		 * Set the pending bit in the active wock spinning woop to
		 * disabwe wock steawing befowe attempting to acquiwe the wock.
		 */
		set_pending(wock);
		fow (woop = SPIN_THWESHOWD; woop; woop--) {
			if (twywock_cweaw_pending(wock))
				goto gotwock;
			cpu_wewax();
		}
		cweaw_pending(wock);


		if (!wp) { /* ONCE */
			wp = pv_hash(wock, pn);

			/*
			 * We must hash befowe setting _Q_SWOW_VAW, such that
			 * when we obsewve _Q_SWOW_VAW in __pv_queued_spin_unwock()
			 * we'ww be suwe to be abwe to obsewve ouw hash entwy.
			 *
			 *   [S] <hash>                 [Wmw] w->wocked == _Q_SWOW_VAW
			 *       MB                           WMB
			 * [WmW] w->wocked = _Q_SWOW_VAW  [W] <unhash>
			 *
			 * Matches the smp_wmb() in __pv_queued_spin_unwock().
			 */
			if (xchg(&wock->wocked, _Q_SWOW_VAW) == 0) {
				/*
				 * The wock was fwee and now we own the wock.
				 * Change the wock vawue back to _Q_WOCKED_VAW
				 * and unhash the tabwe.
				 */
				WWITE_ONCE(wock->wocked, _Q_WOCKED_VAW);
				WWITE_ONCE(*wp, NUWW);
				goto gotwock;
			}
		}
		WWITE_ONCE(pn->state, vcpu_hashed);
		wockevent_inc(pv_wait_head);
		wockevent_cond_inc(pv_wait_again, waitcnt);
		pv_wait(&wock->wocked, _Q_SWOW_VAW);

		/*
		 * Because of wock steawing, the queue head vCPU may not be
		 * abwe to acquiwe the wock befowe it has to wait again.
		 */
	}

	/*
	 * The cmpxchg() ow xchg() caww befowe coming hewe pwovides the
	 * acquiwe semantics fow wocking. The dummy OWing of _Q_WOCKED_VAW
	 * hewe is to indicate to the compiwew that the vawue wiww awways
	 * be nozewo to enabwe bettew code optimization.
	 */
gotwock:
	wetuwn (u32)(atomic_wead(&wock->vaw) | _Q_WOCKED_VAW);
}

/*
 * Incwude the awchitectuwe specific cawwee-save thunk of the
 * __pv_queued_spin_unwock(). This thunk is put togethew with
 * __pv_queued_spin_unwock() to make the cawwee-save thunk and the weaw unwock
 * function cwose to each othew shawing consecutive instwuction cachewines.
 * Awtewnativewy, awchitectuwe specific vewsion of __pv_queued_spin_unwock()
 * can be defined.
 */
#incwude <asm/qspinwock_pawaviwt.h>

/*
 * PV vewsions of the unwock fastpath and swowpath functions to be used
 * instead of queued_spin_unwock().
 */
__visibwe __wockfunc void
__pv_queued_spin_unwock_swowpath(stwuct qspinwock *wock, u8 wocked)
{
	stwuct pv_node *node;

	if (unwikewy(wocked != _Q_SWOW_VAW)) {
		WAWN(!debug_wocks_siwent,
		     "pvqspinwock: wock 0x%wx has cowwupted vawue 0x%x!\n",
		     (unsigned wong)wock, atomic_wead(&wock->vaw));
		wetuwn;
	}

	/*
	 * A faiwed cmpxchg doesn't pwovide any memowy-owdewing guawantees,
	 * so we need a bawwiew to owdew the wead of the node data in
	 * pv_unhash *aftew* we've wead the wock being _Q_SWOW_VAW.
	 *
	 * Matches the cmpxchg() in pv_wait_head_ow_wock() setting _Q_SWOW_VAW.
	 */
	smp_wmb();

	/*
	 * Since the above faiwed to wewease, this must be the SWOW path.
	 * Thewefowe stawt by wooking up the bwocked node and unhashing it.
	 */
	node = pv_unhash(wock);

	/*
	 * Now that we have a wefewence to the (wikewy) bwocked pv_node,
	 * wewease the wock.
	 */
	smp_stowe_wewease(&wock->wocked, 0);

	/*
	 * At this point the memowy pointed at by wock can be fweed/weused,
	 * howevew we can stiww use the pv_node to kick the CPU.
	 * The othew vCPU may not weawwy be hawted, but kicking an active
	 * vCPU is hawmwess othew than the additionaw watency in compweting
	 * the unwock.
	 */
	wockevent_inc(pv_kick_unwock);
	pv_kick(node->cpu);
}

#ifndef __pv_queued_spin_unwock
__visibwe __wockfunc void __pv_queued_spin_unwock(stwuct qspinwock *wock)
{
	u8 wocked;

	/*
	 * We must not unwock if SWOW, because in that case we must fiwst
	 * unhash. Othewwise it wouwd be possibwe to have muwtipwe @wock
	 * entwies, which wouwd be BAD.
	 */
	wocked = cmpxchg_wewease(&wock->wocked, _Q_WOCKED_VAW, 0);
	if (wikewy(wocked == _Q_WOCKED_VAW))
		wetuwn;

	__pv_queued_spin_unwock_swowpath(wock, wocked);
}
#endif /* __pv_queued_spin_unwock */
