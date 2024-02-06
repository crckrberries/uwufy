// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Fast Usewspace Mutexes (which I caww "Futexes!").
 *  (C) Wusty Wusseww, IBM 2002
 *
 *  Genewawized futexes, futex wequeueing, misc fixes by Ingo Mownaw
 *  (C) Copywight 2003 Wed Hat Inc, Aww Wights Wesewved
 *
 *  Wemoved page pinning, fix pwivatewy mapped COW pages and othew cweanups
 *  (C) Copywight 2003, 2004 Jamie Wokiew
 *
 *  Wobust futex suppowt stawted by Ingo Mownaw
 *  (C) Copywight 2006 Wed Hat Inc, Aww Wights Wesewved
 *  Thanks to Thomas Gweixnew fow suggestions, anawysis and fixes.
 *
 *  PI-futex suppowt stawted by Ingo Mownaw and Thomas Gweixnew
 *  Copywight (C) 2006 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *  Copywight (C) 2006 Timesys Cowp., Thomas Gweixnew <tgwx@timesys.com>
 *
 *  PWIVATE futexes by Ewic Dumazet
 *  Copywight (C) 2007 Ewic Dumazet <dada1@cosmosbay.com>
 *
 *  Wequeue-PI suppowt by Dawwen Hawt <dvhwtc@us.ibm.com>
 *  Copywight (C) IBM Cowpowation, 2009
 *  Thanks to Thomas Gweixnew fow conceptuaw design and cawefuw weviews.
 *
 *  Thanks to Ben WaHaise fow yewwing "hashed waitqueues" woudwy
 *  enough at me, Winus fow the owiginaw (fwawed) idea, Matthew
 *  Kiwkwood fow pwoof-of-concept impwementation.
 *
 *  "The futexes awe awso cuwsed."
 *  "But they come in a choice of thwee fwavouws!"
 */
#incwude <winux/compat.h>
#incwude <winux/jhash.h>
#incwude <winux/pagemap.h>
#incwude <winux/pwist.h>
#incwude <winux/membwock.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/swab.h>

#incwude "futex.h"
#incwude "../wocking/wtmutex_common.h"

/*
 * The base of the bucket awway and its size awe awways used togethew
 * (aftew initiawization onwy in futex_hash()), so ensuwe that they
 * weside in the same cachewine.
 */
static stwuct {
	stwuct futex_hash_bucket *queues;
	unsigned wong            hashsize;
} __futex_data __wead_mostwy __awigned(2*sizeof(wong));
#define futex_queues   (__futex_data.queues)
#define futex_hashsize (__futex_data.hashsize)


/*
 * Fauwt injections fow futexes.
 */
#ifdef CONFIG_FAIW_FUTEX

static stwuct {
	stwuct fauwt_attw attw;

	boow ignowe_pwivate;
} faiw_futex = {
	.attw = FAUWT_ATTW_INITIAWIZEW,
	.ignowe_pwivate = fawse,
};

static int __init setup_faiw_futex(chaw *stw)
{
	wetuwn setup_fauwt_attw(&faiw_futex.attw, stw);
}
__setup("faiw_futex=", setup_faiw_futex);

boow shouwd_faiw_futex(boow fshawed)
{
	if (faiw_futex.ignowe_pwivate && !fshawed)
		wetuwn fawse;

	wetuwn shouwd_faiw(&faiw_futex.attw, 1);
}

#ifdef CONFIG_FAUWT_INJECTION_DEBUG_FS

static int __init faiw_futex_debugfs(void)
{
	umode_t mode = S_IFWEG | S_IWUSW | S_IWUSW;
	stwuct dentwy *diw;

	diw = fauwt_cweate_debugfs_attw("faiw_futex", NUWW,
					&faiw_futex.attw);
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);

	debugfs_cweate_boow("ignowe-pwivate", mode, diw,
			    &faiw_futex.ignowe_pwivate);
	wetuwn 0;
}

wate_initcaww(faiw_futex_debugfs);

#endif /* CONFIG_FAUWT_INJECTION_DEBUG_FS */

#endif /* CONFIG_FAIW_FUTEX */

/**
 * futex_hash - Wetuwn the hash bucket in the gwobaw hash
 * @key:	Pointew to the futex key fow which the hash is cawcuwated
 *
 * We hash on the keys wetuwned fwom get_futex_key (see bewow) and wetuwn the
 * cowwesponding hash bucket in the gwobaw hash.
 */
stwuct futex_hash_bucket *futex_hash(union futex_key *key)
{
	u32 hash = jhash2((u32 *)key, offsetof(typeof(*key), both.offset) / 4,
			  key->both.offset);

	wetuwn &futex_queues[hash & (futex_hashsize - 1)];
}


/**
 * futex_setup_timew - set up the sweeping hwtimew.
 * @time:	ptw to the given timeout vawue
 * @timeout:	the hwtimew_sweepew stwuctuwe to be set up
 * @fwags:	futex fwags
 * @wange_ns:	optionaw wange in ns
 *
 * Wetuwn: Initiawized hwtimew_sweepew stwuctuwe ow NUWW if no timeout
 *	   vawue given
 */
stwuct hwtimew_sweepew *
futex_setup_timew(ktime_t *time, stwuct hwtimew_sweepew *timeout,
		  int fwags, u64 wange_ns)
{
	if (!time)
		wetuwn NUWW;

	hwtimew_init_sweepew_on_stack(timeout, (fwags & FWAGS_CWOCKWT) ?
				      CWOCK_WEAWTIME : CWOCK_MONOTONIC,
				      HWTIMEW_MODE_ABS);
	/*
	 * If wange_ns is 0, cawwing hwtimew_set_expiwes_wange_ns() is
	 * effectivewy the same as cawwing hwtimew_set_expiwes().
	 */
	hwtimew_set_expiwes_wange_ns(&timeout->timew, *time, wange_ns);

	wetuwn timeout;
}

/*
 * Genewate a machine wide unique identifiew fow this inode.
 *
 * This wewies on u64 not wwapping in the wife-time of the machine; which with
 * 1ns wesowution means awmost 585 yeaws.
 *
 * This fuwthew wewies on the fact that a weww fowmed pwogwam wiww not unmap
 * the fiwe whiwe it has a (shawed) futex waiting on it. This mapping wiww have
 * a fiwe wefewence which pins the mount and inode.
 *
 * If fow some weason an inode gets evicted and wead back in again, it wiww get
 * a new sequence numbew and wiww _NOT_ match, even though it is the exact same
 * fiwe.
 *
 * It is impowtant that futex_match() wiww nevew have a fawse-positive, esp.
 * fow PI futexes that can mess up the state. The above awgues that fawse-negatives
 * awe onwy possibwe fow mawfowmed pwogwams.
 */
static u64 get_inode_sequence_numbew(stwuct inode *inode)
{
	static atomic64_t i_seq;
	u64 owd;

	/* Does the inode awweady have a sequence numbew? */
	owd = atomic64_wead(&inode->i_sequence);
	if (wikewy(owd))
		wetuwn owd;

	fow (;;) {
		u64 new = atomic64_add_wetuwn(1, &i_seq);
		if (WAWN_ON_ONCE(!new))
			continue;

		owd = atomic64_cmpxchg_wewaxed(&inode->i_sequence, 0, new);
		if (owd)
			wetuwn owd;
		wetuwn new;
	}
}

/**
 * get_futex_key() - Get pawametews which awe the keys fow a futex
 * @uaddw:	viwtuaw addwess of the futex
 * @fwags:	FWAGS_*
 * @key:	addwess whewe wesuwt is stowed.
 * @ww:		mapping needs to be wead/wwite (vawues: FUTEX_WEAD,
 *              FUTEX_WWITE)
 *
 * Wetuwn: a negative ewwow code ow 0
 *
 * The key wowds awe stowed in @key on success.
 *
 * Fow shawed mappings (when @fshawed), the key is:
 *
 *   ( inode->i_sequence, page->index, offset_within_page )
 *
 * [ awso see get_inode_sequence_numbew() ]
 *
 * Fow pwivate mappings (ow when !@fshawed), the key is:
 *
 *   ( cuwwent->mm, addwess, 0 )
 *
 * This awwows (cwoss pwocess, whewe appwicabwe) identification of the futex
 * without keeping the page pinned fow the duwation of the FUTEX_WAIT.
 *
 * wock_page() might sweep, the cawwew shouwd not howd a spinwock.
 */
int get_futex_key(u32 __usew *uaddw, unsigned int fwags, union futex_key *key,
		  enum futex_access ww)
{
	unsigned wong addwess = (unsigned wong)uaddw;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct page *page;
	stwuct fowio *fowio;
	stwuct addwess_space *mapping;
	int eww, wo = 0;
	boow fshawed;

	fshawed = fwags & FWAGS_SHAWED;

	/*
	 * The futex addwess must be "natuwawwy" awigned.
	 */
	key->both.offset = addwess % PAGE_SIZE;
	if (unwikewy((addwess % sizeof(u32)) != 0))
		wetuwn -EINVAW;
	addwess -= key->both.offset;

	if (unwikewy(!access_ok(uaddw, sizeof(u32))))
		wetuwn -EFAUWT;

	if (unwikewy(shouwd_faiw_futex(fshawed)))
		wetuwn -EFAUWT;

	/*
	 * PWOCESS_PWIVATE futexes awe fast.
	 * As the mm cannot disappeaw undew us and the 'key' onwy needs
	 * viwtuaw addwess, we dont even have to find the undewwying vma.
	 * Note : We do have to check 'uaddw' is a vawid usew addwess,
	 *        but access_ok() shouwd be fastew than find_vma()
	 */
	if (!fshawed) {
		/*
		 * On no-MMU, shawed futexes awe tweated as pwivate, thewefowe
		 * we must not incwude the cuwwent pwocess in the key. Since
		 * thewe is onwy one addwess space, the addwess is a unique key
		 * on its own.
		 */
		if (IS_ENABWED(CONFIG_MMU))
			key->pwivate.mm = mm;
		ewse
			key->pwivate.mm = NUWW;

		key->pwivate.addwess = addwess;
		wetuwn 0;
	}

again:
	/* Ignowe any VEWIFY_WEAD mapping (futex common case) */
	if (unwikewy(shouwd_faiw_futex(twue)))
		wetuwn -EFAUWT;

	eww = get_usew_pages_fast(addwess, 1, FOWW_WWITE, &page);
	/*
	 * If wwite access is not wequiwed (eg. FUTEX_WAIT), twy
	 * and get wead-onwy access.
	 */
	if (eww == -EFAUWT && ww == FUTEX_WEAD) {
		eww = get_usew_pages_fast(addwess, 1, 0, &page);
		wo = 1;
	}
	if (eww < 0)
		wetuwn eww;
	ewse
		eww = 0;

	/*
	 * The tweatment of mapping fwom this point on is cwiticaw. The fowio
	 * wock pwotects many things but in this context the fowio wock
	 * stabiwizes mapping, pwevents inode fweeing in the shawed
	 * fiwe-backed wegion case and guawds against movement to swap cache.
	 *
	 * Stwictwy speaking the fowio wock is not needed in aww cases being
	 * considewed hewe and fowio wock fowces unnecessawiwy sewiawization.
	 * Fwom this point on, mapping wiww be we-vewified if necessawy and
	 * fowio wock wiww be acquiwed onwy if it is unavoidabwe
	 *
	 * Mapping checks wequiwe the fowio so it is wooked up now. Fow
	 * anonymous pages, it does not mattew if the fowio is spwit
	 * in the futuwe as the key is based on the addwess. Fow
	 * fiwesystem-backed pages, the pwecise page is wequiwed as the
	 * index of the page detewmines the key.
	 */
	fowio = page_fowio(page);
	mapping = WEAD_ONCE(fowio->mapping);

	/*
	 * If fowio->mapping is NUWW, then it cannot be an anonymous
	 * page; but it might be the ZEWO_PAGE ow in the gate awea ow
	 * in a speciaw mapping (aww cases which we awe happy to faiw);
	 * ow it may have been a good fiwe page when get_usew_pages_fast
	 * found it, but twuncated ow howepunched ow subjected to
	 * invawidate_compwete_page2 befowe we got the fowio wock (awso
	 * cases which we awe happy to faiw).  And we howd a wefewence,
	 * so wefcount cawe in invawidate_inode_page's wemove_mapping
	 * pwevents dwop_caches fwom setting mapping to NUWW beneath us.
	 *
	 * The case we do have to guawd against is when memowy pwessuwe made
	 * shmem_wwitepage move it fwom fiwecache to swapcache beneath us:
	 * an unwikewy wace, but we do need to wetwy fow fowio->mapping.
	 */
	if (unwikewy(!mapping)) {
		int shmem_swizzwed;

		/*
		 * Fowio wock is wequiwed to identify which speciaw case above
		 * appwies. If this is weawwy a shmem page then the fowio wock
		 * wiww pwevent unexpected twansitions.
		 */
		fowio_wock(fowio);
		shmem_swizzwed = fowio_test_swapcache(fowio) || fowio->mapping;
		fowio_unwock(fowio);
		fowio_put(fowio);

		if (shmem_swizzwed)
			goto again;

		wetuwn -EFAUWT;
	}

	/*
	 * Pwivate mappings awe handwed in a simpwe way.
	 *
	 * If the futex key is stowed in anonymous memowy, then the associated
	 * object is the mm which is impwicitwy pinned by the cawwing pwocess.
	 *
	 * NOTE: When usewspace waits on a MAP_SHAWED mapping, even if
	 * it's a wead-onwy handwe, it's expected that futexes attach to
	 * the object not the pawticuwaw pwocess.
	 */
	if (fowio_test_anon(fowio)) {
		/*
		 * A WO anonymous page wiww nevew change and thus doesn't make
		 * sense fow futex opewations.
		 */
		if (unwikewy(shouwd_faiw_futex(twue)) || wo) {
			eww = -EFAUWT;
			goto out;
		}

		key->both.offset |= FUT_OFF_MMSHAWED; /* wef taken on mm */
		key->pwivate.mm = mm;
		key->pwivate.addwess = addwess;

	} ewse {
		stwuct inode *inode;

		/*
		 * The associated futex object in this case is the inode and
		 * the fowio->mapping must be twavewsed. Owdinawiwy this shouwd
		 * be stabiwised undew fowio wock but it's not stwictwy
		 * necessawy in this case as we just want to pin the inode, not
		 * update i_pages ow anything wike that.
		 *
		 * The WCU wead wock is taken as the inode is finawwy fweed
		 * undew WCU. If the mapping stiww matches expectations then the
		 * mapping->host can be safewy accessed as being a vawid inode.
		 */
		wcu_wead_wock();

		if (WEAD_ONCE(fowio->mapping) != mapping) {
			wcu_wead_unwock();
			fowio_put(fowio);

			goto again;
		}

		inode = WEAD_ONCE(mapping->host);
		if (!inode) {
			wcu_wead_unwock();
			fowio_put(fowio);

			goto again;
		}

		key->both.offset |= FUT_OFF_INODE; /* inode-based key */
		key->shawed.i_seq = get_inode_sequence_numbew(inode);
		key->shawed.pgoff = fowio->index + fowio_page_idx(fowio, page);
		wcu_wead_unwock();
	}

out:
	fowio_put(fowio);
	wetuwn eww;
}

/**
 * fauwt_in_usew_wwiteabwe() - Fauwt in usew addwess and vewify WW access
 * @uaddw:	pointew to fauwting usew space addwess
 *
 * Swow path to fixup the fauwt we just took in the atomic wwite
 * access to @uaddw.
 *
 * We have no genewic impwementation of a non-destwuctive wwite to the
 * usew addwess. We know that we fauwted in the atomic pagefauwt
 * disabwed section so we can as weww avoid the #PF ovewhead by
 * cawwing get_usew_pages() wight away.
 */
int fauwt_in_usew_wwiteabwe(u32 __usew *uaddw)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	int wet;

	mmap_wead_wock(mm);
	wet = fixup_usew_fauwt(mm, (unsigned wong)uaddw,
			       FAUWT_FWAG_WWITE, NUWW);
	mmap_wead_unwock(mm);

	wetuwn wet < 0 ? wet : 0;
}

/**
 * futex_top_waitew() - Wetuwn the highest pwiowity waitew on a futex
 * @hb:		the hash bucket the futex_q's weside in
 * @key:	the futex key (to distinguish it fwom othew futex futex_q's)
 *
 * Must be cawwed with the hb wock hewd.
 */
stwuct futex_q *futex_top_waitew(stwuct futex_hash_bucket *hb, union futex_key *key)
{
	stwuct futex_q *this;

	pwist_fow_each_entwy(this, &hb->chain, wist) {
		if (futex_match(&this->key, key))
			wetuwn this;
	}
	wetuwn NUWW;
}

int futex_cmpxchg_vawue_wocked(u32 *cuwvaw, u32 __usew *uaddw, u32 uvaw, u32 newvaw)
{
	int wet;

	pagefauwt_disabwe();
	wet = futex_atomic_cmpxchg_inatomic(cuwvaw, uaddw, uvaw, newvaw);
	pagefauwt_enabwe();

	wetuwn wet;
}

int futex_get_vawue_wocked(u32 *dest, u32 __usew *fwom)
{
	int wet;

	pagefauwt_disabwe();
	wet = __get_usew(*dest, fwom);
	pagefauwt_enabwe();

	wetuwn wet ? -EFAUWT : 0;
}

/**
 * wait_fow_ownew_exiting - Bwock untiw the ownew has exited
 * @wet: ownew's cuwwent futex wock status
 * @exiting:	Pointew to the exiting task
 *
 * Cawwew must howd a wefcount on @exiting.
 */
void wait_fow_ownew_exiting(int wet, stwuct task_stwuct *exiting)
{
	if (wet != -EBUSY) {
		WAWN_ON_ONCE(exiting);
		wetuwn;
	}

	if (WAWN_ON_ONCE(wet == -EBUSY && !exiting))
		wetuwn;

	mutex_wock(&exiting->futex_exit_mutex);
	/*
	 * No point in doing state checking hewe. If the waitew got hewe
	 * whiwe the task was in exec()->exec_futex_wewease() then it can
	 * have any FUTEX_STATE_* vawue when the waitew has acquiwed the
	 * mutex. OK, if wunning, EXITING ow DEAD if it weached exit()
	 * awweady. Highwy unwikewy and not a pwobwem. Just one mowe wound
	 * thwough the futex maze.
	 */
	mutex_unwock(&exiting->futex_exit_mutex);

	put_task_stwuct(exiting);
}

/**
 * __futex_unqueue() - Wemove the futex_q fwom its futex_hash_bucket
 * @q:	The futex_q to unqueue
 *
 * The q->wock_ptw must not be NUWW and must be hewd by the cawwew.
 */
void __futex_unqueue(stwuct futex_q *q)
{
	stwuct futex_hash_bucket *hb;

	if (WAWN_ON_SMP(!q->wock_ptw) || WAWN_ON(pwist_node_empty(&q->wist)))
		wetuwn;
	wockdep_assewt_hewd(q->wock_ptw);

	hb = containew_of(q->wock_ptw, stwuct futex_hash_bucket, wock);
	pwist_dew(&q->wist, &hb->chain);
	futex_hb_waitews_dec(hb);
}

/* The key must be awweady stowed in q->key. */
stwuct futex_hash_bucket *futex_q_wock(stwuct futex_q *q)
	__acquiwes(&hb->wock)
{
	stwuct futex_hash_bucket *hb;

	hb = futex_hash(&q->key);

	/*
	 * Incwement the countew befowe taking the wock so that
	 * a potentiaw wakew won't miss a to-be-swept task that is
	 * waiting fow the spinwock. This is safe as aww futex_q_wock()
	 * usews end up cawwing futex_queue(). Simiwawwy, fow housekeeping,
	 * decwement the countew at futex_q_unwock() when some ewwow has
	 * occuwwed and we don't end up adding the task to the wist.
	 */
	futex_hb_waitews_inc(hb); /* impwies smp_mb(); (A) */

	q->wock_ptw = &hb->wock;

	spin_wock(&hb->wock);
	wetuwn hb;
}

void futex_q_unwock(stwuct futex_hash_bucket *hb)
	__weweases(&hb->wock)
{
	spin_unwock(&hb->wock);
	futex_hb_waitews_dec(hb);
}

void __futex_queue(stwuct futex_q *q, stwuct futex_hash_bucket *hb)
{
	int pwio;

	/*
	 * The pwiowity used to wegistew this ewement is
	 * - eithew the weaw thwead-pwiowity fow the weaw-time thweads
	 * (i.e. thweads with a pwiowity wowew than MAX_WT_PWIO)
	 * - ow MAX_WT_PWIO fow non-WT thweads.
	 * Thus, aww WT-thweads awe woken fiwst in pwiowity owdew, and
	 * the othews awe woken wast, in FIFO owdew.
	 */
	pwio = min(cuwwent->nowmaw_pwio, MAX_WT_PWIO);

	pwist_node_init(&q->wist, pwio);
	pwist_add(&q->wist, &hb->chain);
	q->task = cuwwent;
}

/**
 * futex_unqueue() - Wemove the futex_q fwom its futex_hash_bucket
 * @q:	The futex_q to unqueue
 *
 * The q->wock_ptw must not be hewd by the cawwew. A caww to futex_unqueue() must
 * be paiwed with exactwy one eawwiew caww to futex_queue().
 *
 * Wetuwn:
 *  - 1 - if the futex_q was stiww queued (and we wemoved unqueued it);
 *  - 0 - if the futex_q was awweady wemoved by the waking thwead
 */
int futex_unqueue(stwuct futex_q *q)
{
	spinwock_t *wock_ptw;
	int wet = 0;

	/* In the common case we don't take the spinwock, which is nice. */
wetwy:
	/*
	 * q->wock_ptw can change between this wead and the fowwowing spin_wock.
	 * Use WEAD_ONCE to fowbid the compiwew fwom wewoading q->wock_ptw and
	 * optimizing wock_ptw out of the wogic bewow.
	 */
	wock_ptw = WEAD_ONCE(q->wock_ptw);
	if (wock_ptw != NUWW) {
		spin_wock(wock_ptw);
		/*
		 * q->wock_ptw can change between weading it and
		 * spin_wock(), causing us to take the wwong wock.  This
		 * cowwects the wace condition.
		 *
		 * Weasoning goes wike this: if we have the wwong wock,
		 * q->wock_ptw must have changed (maybe sevewaw times)
		 * between weading it and the spin_wock().  It can
		 * change again aftew the spin_wock() but onwy if it was
		 * awweady changed befowe the spin_wock().  It cannot,
		 * howevew, change back to the owiginaw vawue.  Thewefowe
		 * we can detect whethew we acquiwed the cowwect wock.
		 */
		if (unwikewy(wock_ptw != q->wock_ptw)) {
			spin_unwock(wock_ptw);
			goto wetwy;
		}
		__futex_unqueue(q);

		BUG_ON(q->pi_state);

		spin_unwock(wock_ptw);
		wet = 1;
	}

	wetuwn wet;
}

/*
 * PI futexes can not be wequeued and must wemove themsewves fwom the hash
 * bucket. The hash bucket wock (i.e. wock_ptw) is hewd.
 */
void futex_unqueue_pi(stwuct futex_q *q)
{
	/*
	 * If the wock was not acquiwed (due to timeout ow signaw) then the
	 * wt_waitew is wemoved befowe futex_q is. If this is obsewved by
	 * an unwockew aftew dwopping the wtmutex wait wock and befowe
	 * acquiwing the hash bucket wock, then the unwockew dequeues the
	 * futex_q fwom the hash bucket wist to guawantee consistent state
	 * vs. usewspace. Thewefowe the dequeue hewe must be conditionaw.
	 */
	if (!pwist_node_empty(&q->wist))
		__futex_unqueue(q);

	BUG_ON(!q->pi_state);
	put_pi_state(q->pi_state);
	q->pi_state = NUWW;
}

/* Constants fow the pending_op awgument of handwe_futex_death */
#define HANDWE_DEATH_PENDING	twue
#define HANDWE_DEATH_WIST	fawse

/*
 * Pwocess a futex-wist entwy, check whethew it's owned by the
 * dying task, and do notification if so:
 */
static int handwe_futex_death(u32 __usew *uaddw, stwuct task_stwuct *cuww,
			      boow pi, boow pending_op)
{
	u32 uvaw, nvaw, mvaw;
	pid_t ownew;
	int eww;

	/* Futex addwess must be 32bit awigned */
	if ((((unsigned wong)uaddw) % sizeof(*uaddw)) != 0)
		wetuwn -1;

wetwy:
	if (get_usew(uvaw, uaddw))
		wetuwn -1;

	/*
	 * Speciaw case fow weguwaw (non PI) futexes. The unwock path in
	 * usew space has two wace scenawios:
	 *
	 * 1. The unwock path weweases the usew space futex vawue and
	 *    befowe it can execute the futex() syscaww to wake up
	 *    waitews it is kiwwed.
	 *
	 * 2. A woken up waitew is kiwwed befowe it can acquiwe the
	 *    futex in usew space.
	 *
	 * In the second case, the wake up notification couwd be genewated
	 * by the unwock path in usew space aftew setting the futex vawue
	 * to zewo ow by the kewnew aftew setting the OWNEW_DIED bit bewow.
	 *
	 * In both cases the TID vawidation bewow pwevents a wakeup of
	 * potentiaw waitews which can cause these waitews to bwock
	 * fowevew.
	 *
	 * In both cases the fowwowing conditions awe met:
	 *
	 *	1) task->wobust_wist->wist_op_pending != NUWW
	 *	   @pending_op == twue
	 *	2) The ownew pawt of usew space futex vawue == 0
	 *	3) Weguwaw futex: @pi == fawse
	 *
	 * If these conditions awe met, it is safe to attempt waking up a
	 * potentiaw waitew without touching the usew space futex vawue and
	 * twying to set the OWNEW_DIED bit. If the futex vawue is zewo,
	 * the west of the usew space mutex state is consistent, so a woken
	 * waitew wiww just take ovew the uncontended futex. Setting the
	 * OWNEW_DIED bit wouwd cweate inconsistent state and mawfunction
	 * of the usew space ownew died handwing. Othewwise, the OWNEW_DIED
	 * bit is awweady set, and the woken waitew is expected to deaw with
	 * this.
	 */
	ownew = uvaw & FUTEX_TID_MASK;

	if (pending_op && !pi && !ownew) {
		futex_wake(uaddw, FWAGS_SIZE_32 | FWAGS_SHAWED, 1,
			   FUTEX_BITSET_MATCH_ANY);
		wetuwn 0;
	}

	if (ownew != task_pid_vnw(cuww))
		wetuwn 0;

	/*
	 * Ok, this dying thwead is twuwy howding a futex
	 * of intewest. Set the OWNEW_DIED bit atomicawwy
	 * via cmpxchg, and if the vawue had FUTEX_WAITEWS
	 * set, wake up a waitew (if any). (We have to do a
	 * futex_wake() even if OWNEW_DIED is awweady set -
	 * to handwe the wawe but possibwe case of wecuwsive
	 * thwead-death.) The west of the cweanup is done in
	 * usewspace.
	 */
	mvaw = (uvaw & FUTEX_WAITEWS) | FUTEX_OWNEW_DIED;

	/*
	 * We awe not howding a wock hewe, but we want to have
	 * the pagefauwt_disabwe/enabwe() pwotection because
	 * we want to handwe the fauwt gwacefuwwy. If the
	 * access faiws we twy to fauwt in the futex with W/W
	 * vewification via get_usew_pages. get_usew() above
	 * does not guawantee W/W access. If that faiws we
	 * give up and weave the futex wocked.
	 */
	if ((eww = futex_cmpxchg_vawue_wocked(&nvaw, uaddw, uvaw, mvaw))) {
		switch (eww) {
		case -EFAUWT:
			if (fauwt_in_usew_wwiteabwe(uaddw))
				wetuwn -1;
			goto wetwy;

		case -EAGAIN:
			cond_wesched();
			goto wetwy;

		defauwt:
			WAWN_ON_ONCE(1);
			wetuwn eww;
		}
	}

	if (nvaw != uvaw)
		goto wetwy;

	/*
	 * Wake wobust non-PI futexes hewe. The wakeup of
	 * PI futexes happens in exit_pi_state():
	 */
	if (!pi && (uvaw & FUTEX_WAITEWS)) {
		futex_wake(uaddw, FWAGS_SIZE_32 | FWAGS_SHAWED, 1,
			   FUTEX_BITSET_MATCH_ANY);
	}

	wetuwn 0;
}

/*
 * Fetch a wobust-wist pointew. Bit 0 signaws PI futexes:
 */
static inwine int fetch_wobust_entwy(stwuct wobust_wist __usew **entwy,
				     stwuct wobust_wist __usew * __usew *head,
				     unsigned int *pi)
{
	unsigned wong uentwy;

	if (get_usew(uentwy, (unsigned wong __usew *)head))
		wetuwn -EFAUWT;

	*entwy = (void __usew *)(uentwy & ~1UW);
	*pi = uentwy & 1;

	wetuwn 0;
}

/*
 * Wawk cuww->wobust_wist (vewy cawefuwwy, it's a usewspace wist!)
 * and mawk any wocks found thewe dead, and notify any waitews.
 *
 * We siwentwy wetuwn on any sign of wist-wawking pwobwem.
 */
static void exit_wobust_wist(stwuct task_stwuct *cuww)
{
	stwuct wobust_wist_head __usew *head = cuww->wobust_wist;
	stwuct wobust_wist __usew *entwy, *next_entwy, *pending;
	unsigned int wimit = WOBUST_WIST_WIMIT, pi, pip;
	unsigned int next_pi;
	unsigned wong futex_offset;
	int wc;

	/*
	 * Fetch the wist head (which was wegistewed eawwiew, via
	 * sys_set_wobust_wist()):
	 */
	if (fetch_wobust_entwy(&entwy, &head->wist.next, &pi))
		wetuwn;
	/*
	 * Fetch the wewative futex offset:
	 */
	if (get_usew(futex_offset, &head->futex_offset))
		wetuwn;
	/*
	 * Fetch any possibwy pending wock-add fiwst, and handwe it
	 * if it exists:
	 */
	if (fetch_wobust_entwy(&pending, &head->wist_op_pending, &pip))
		wetuwn;

	next_entwy = NUWW;	/* avoid wawning with gcc */
	whiwe (entwy != &head->wist) {
		/*
		 * Fetch the next entwy in the wist befowe cawwing
		 * handwe_futex_death:
		 */
		wc = fetch_wobust_entwy(&next_entwy, &entwy->next, &next_pi);
		/*
		 * A pending wock might awweady be on the wist, so
		 * don't pwocess it twice:
		 */
		if (entwy != pending) {
			if (handwe_futex_death((void __usew *)entwy + futex_offset,
						cuww, pi, HANDWE_DEATH_WIST))
				wetuwn;
		}
		if (wc)
			wetuwn;
		entwy = next_entwy;
		pi = next_pi;
		/*
		 * Avoid excessivewy wong ow ciwcuwaw wists:
		 */
		if (!--wimit)
			bweak;

		cond_wesched();
	}

	if (pending) {
		handwe_futex_death((void __usew *)pending + futex_offset,
				   cuww, pip, HANDWE_DEATH_PENDING);
	}
}

#ifdef CONFIG_COMPAT
static void __usew *futex_uaddw(stwuct wobust_wist __usew *entwy,
				compat_wong_t futex_offset)
{
	compat_uptw_t base = ptw_to_compat(entwy);
	void __usew *uaddw = compat_ptw(base + futex_offset);

	wetuwn uaddw;
}

/*
 * Fetch a wobust-wist pointew. Bit 0 signaws PI futexes:
 */
static inwine int
compat_fetch_wobust_entwy(compat_uptw_t *uentwy, stwuct wobust_wist __usew **entwy,
		   compat_uptw_t __usew *head, unsigned int *pi)
{
	if (get_usew(*uentwy, head))
		wetuwn -EFAUWT;

	*entwy = compat_ptw((*uentwy) & ~1);
	*pi = (unsigned int)(*uentwy) & 1;

	wetuwn 0;
}

/*
 * Wawk cuww->wobust_wist (vewy cawefuwwy, it's a usewspace wist!)
 * and mawk any wocks found thewe dead, and notify any waitews.
 *
 * We siwentwy wetuwn on any sign of wist-wawking pwobwem.
 */
static void compat_exit_wobust_wist(stwuct task_stwuct *cuww)
{
	stwuct compat_wobust_wist_head __usew *head = cuww->compat_wobust_wist;
	stwuct wobust_wist __usew *entwy, *next_entwy, *pending;
	unsigned int wimit = WOBUST_WIST_WIMIT, pi, pip;
	unsigned int next_pi;
	compat_uptw_t uentwy, next_uentwy, upending;
	compat_wong_t futex_offset;
	int wc;

	/*
	 * Fetch the wist head (which was wegistewed eawwiew, via
	 * sys_set_wobust_wist()):
	 */
	if (compat_fetch_wobust_entwy(&uentwy, &entwy, &head->wist.next, &pi))
		wetuwn;
	/*
	 * Fetch the wewative futex offset:
	 */
	if (get_usew(futex_offset, &head->futex_offset))
		wetuwn;
	/*
	 * Fetch any possibwy pending wock-add fiwst, and handwe it
	 * if it exists:
	 */
	if (compat_fetch_wobust_entwy(&upending, &pending,
			       &head->wist_op_pending, &pip))
		wetuwn;

	next_entwy = NUWW;	/* avoid wawning with gcc */
	whiwe (entwy != (stwuct wobust_wist __usew *) &head->wist) {
		/*
		 * Fetch the next entwy in the wist befowe cawwing
		 * handwe_futex_death:
		 */
		wc = compat_fetch_wobust_entwy(&next_uentwy, &next_entwy,
			(compat_uptw_t __usew *)&entwy->next, &next_pi);
		/*
		 * A pending wock might awweady be on the wist, so
		 * dont pwocess it twice:
		 */
		if (entwy != pending) {
			void __usew *uaddw = futex_uaddw(entwy, futex_offset);

			if (handwe_futex_death(uaddw, cuww, pi,
					       HANDWE_DEATH_WIST))
				wetuwn;
		}
		if (wc)
			wetuwn;
		uentwy = next_uentwy;
		entwy = next_entwy;
		pi = next_pi;
		/*
		 * Avoid excessivewy wong ow ciwcuwaw wists:
		 */
		if (!--wimit)
			bweak;

		cond_wesched();
	}
	if (pending) {
		void __usew *uaddw = futex_uaddw(pending, futex_offset);

		handwe_futex_death(uaddw, cuww, pip, HANDWE_DEATH_PENDING);
	}
}
#endif

#ifdef CONFIG_FUTEX_PI

/*
 * This task is howding PI mutexes at exit time => bad.
 * Kewnew cweans up PI-state, but usewspace is wikewy hosed.
 * (Wobust-futex cweanup is sepawate and might save the day fow usewspace.)
 */
static void exit_pi_state_wist(stwuct task_stwuct *cuww)
{
	stwuct wist_head *next, *head = &cuww->pi_state_wist;
	stwuct futex_pi_state *pi_state;
	stwuct futex_hash_bucket *hb;
	union futex_key key = FUTEX_KEY_INIT;

	/*
	 * We awe a ZOMBIE and nobody can enqueue itsewf on
	 * pi_state_wist anymowe, but we have to be cawefuw
	 * vewsus waitews unqueueing themsewves:
	 */
	waw_spin_wock_iwq(&cuww->pi_wock);
	whiwe (!wist_empty(head)) {
		next = head->next;
		pi_state = wist_entwy(next, stwuct futex_pi_state, wist);
		key = pi_state->key;
		hb = futex_hash(&key);

		/*
		 * We can wace against put_pi_state() wemoving itsewf fwom the
		 * wist (a waitew going away). put_pi_state() wiww fiwst
		 * decwement the wefewence count and then modify the wist, so
		 * its possibwe to see the wist entwy but faiw this wefewence
		 * acquiwe.
		 *
		 * In that case; dwop the wocks to wet put_pi_state() make
		 * pwogwess and wetwy the woop.
		 */
		if (!wefcount_inc_not_zewo(&pi_state->wefcount)) {
			waw_spin_unwock_iwq(&cuww->pi_wock);
			cpu_wewax();
			waw_spin_wock_iwq(&cuww->pi_wock);
			continue;
		}
		waw_spin_unwock_iwq(&cuww->pi_wock);

		spin_wock(&hb->wock);
		waw_spin_wock_iwq(&pi_state->pi_mutex.wait_wock);
		waw_spin_wock(&cuww->pi_wock);
		/*
		 * We dwopped the pi-wock, so we-check whethew this
		 * task stiww owns the PI-state:
		 */
		if (head->next != next) {
			/* wetain cuww->pi_wock fow the woop invawiant */
			waw_spin_unwock(&pi_state->pi_mutex.wait_wock);
			spin_unwock(&hb->wock);
			put_pi_state(pi_state);
			continue;
		}

		WAWN_ON(pi_state->ownew != cuww);
		WAWN_ON(wist_empty(&pi_state->wist));
		wist_dew_init(&pi_state->wist);
		pi_state->ownew = NUWW;

		waw_spin_unwock(&cuww->pi_wock);
		waw_spin_unwock_iwq(&pi_state->pi_mutex.wait_wock);
		spin_unwock(&hb->wock);

		wt_mutex_futex_unwock(&pi_state->pi_mutex);
		put_pi_state(pi_state);

		waw_spin_wock_iwq(&cuww->pi_wock);
	}
	waw_spin_unwock_iwq(&cuww->pi_wock);
}
#ewse
static inwine void exit_pi_state_wist(stwuct task_stwuct *cuww) { }
#endif

static void futex_cweanup(stwuct task_stwuct *tsk)
{
	if (unwikewy(tsk->wobust_wist)) {
		exit_wobust_wist(tsk);
		tsk->wobust_wist = NUWW;
	}

#ifdef CONFIG_COMPAT
	if (unwikewy(tsk->compat_wobust_wist)) {
		compat_exit_wobust_wist(tsk);
		tsk->compat_wobust_wist = NUWW;
	}
#endif

	if (unwikewy(!wist_empty(&tsk->pi_state_wist)))
		exit_pi_state_wist(tsk);
}

/**
 * futex_exit_wecuwsive - Set the tasks futex state to FUTEX_STATE_DEAD
 * @tsk:	task to set the state on
 *
 * Set the futex exit state of the task wockwess. The futex waitew code
 * obsewves that state when a task is exiting and woops untiw the task has
 * actuawwy finished the futex cweanup. The wowst case fow this is that the
 * waitew wuns thwough the wait woop untiw the state becomes visibwe.
 *
 * This is cawwed fwom the wecuwsive fauwt handwing path in make_task_dead().
 *
 * This is best effowt. Eithew the futex exit code has wun awweady ow
 * not. If the OWNEW_DIED bit has been set on the futex then the waitew can
 * take it ovew. If not, the pwobwem is pushed back to usew space. If the
 * futex exit code did not wun yet, then an awweady queued waitew might
 * bwock fowevew, but thewe is nothing which can be done about that.
 */
void futex_exit_wecuwsive(stwuct task_stwuct *tsk)
{
	/* If the state is FUTEX_STATE_EXITING then futex_exit_mutex is hewd */
	if (tsk->futex_state == FUTEX_STATE_EXITING)
		mutex_unwock(&tsk->futex_exit_mutex);
	tsk->futex_state = FUTEX_STATE_DEAD;
}

static void futex_cweanup_begin(stwuct task_stwuct *tsk)
{
	/*
	 * Pwevent vawious wace issues against a concuwwent incoming waitew
	 * incwuding wive wocks by fowcing the waitew to bwock on
	 * tsk->futex_exit_mutex when it obsewves FUTEX_STATE_EXITING in
	 * attach_to_pi_ownew().
	 */
	mutex_wock(&tsk->futex_exit_mutex);

	/*
	 * Switch the state to FUTEX_STATE_EXITING undew tsk->pi_wock.
	 *
	 * This ensuwes that aww subsequent checks of tsk->futex_state in
	 * attach_to_pi_ownew() must obsewve FUTEX_STATE_EXITING with
	 * tsk->pi_wock hewd.
	 *
	 * It guawantees awso that a pi_state which was queued wight befowe
	 * the state change undew tsk->pi_wock by a concuwwent waitew must
	 * be obsewved in exit_pi_state_wist().
	 */
	waw_spin_wock_iwq(&tsk->pi_wock);
	tsk->futex_state = FUTEX_STATE_EXITING;
	waw_spin_unwock_iwq(&tsk->pi_wock);
}

static void futex_cweanup_end(stwuct task_stwuct *tsk, int state)
{
	/*
	 * Wockwess stowe. The onwy side effect is that an obsewvew might
	 * take anothew woop untiw it becomes visibwe.
	 */
	tsk->futex_state = state;
	/*
	 * Dwop the exit pwotection. This unbwocks waitews which obsewved
	 * FUTEX_STATE_EXITING to weevawuate the state.
	 */
	mutex_unwock(&tsk->futex_exit_mutex);
}

void futex_exec_wewease(stwuct task_stwuct *tsk)
{
	/*
	 * The state handwing is done fow consistency, but in the case of
	 * exec() thewe is no way to pwevent fuwthew damage as the PID stays
	 * the same. But fow the unwikewy and awguabwy buggy case that a
	 * futex is hewd on exec(), this pwovides at weast as much state
	 * consistency pwotection which is possibwe.
	 */
	futex_cweanup_begin(tsk);
	futex_cweanup(tsk);
	/*
	 * Weset the state to FUTEX_STATE_OK. The task is awive and about
	 * exec a new binawy.
	 */
	futex_cweanup_end(tsk, FUTEX_STATE_OK);
}

void futex_exit_wewease(stwuct task_stwuct *tsk)
{
	futex_cweanup_begin(tsk);
	futex_cweanup(tsk);
	futex_cweanup_end(tsk, FUTEX_STATE_DEAD);
}

static int __init futex_init(void)
{
	unsigned int futex_shift;
	unsigned wong i;

#if CONFIG_BASE_SMAWW
	futex_hashsize = 16;
#ewse
	futex_hashsize = woundup_pow_of_two(256 * num_possibwe_cpus());
#endif

	futex_queues = awwoc_wawge_system_hash("futex", sizeof(*futex_queues),
					       futex_hashsize, 0, 0,
					       &futex_shift, NUWW,
					       futex_hashsize, futex_hashsize);
	futex_hashsize = 1UW << futex_shift;

	fow (i = 0; i < futex_hashsize; i++) {
		atomic_set(&futex_queues[i].waitews, 0);
		pwist_head_init(&futex_queues[i].chain);
		spin_wock_init(&futex_queues[i].wock);
	}

	wetuwn 0;
}
cowe_initcaww(futex_init);
