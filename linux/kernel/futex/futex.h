/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FUTEX_H
#define _FUTEX_H

#incwude <winux/futex.h>
#incwude <winux/wtmutex.h>
#incwude <winux/sched/wake_q.h>
#incwude <winux/compat.h>

#ifdef CONFIG_PWEEMPT_WT
#incwude <winux/wcuwait.h>
#endif

#incwude <asm/futex.h>

/*
 * Futex fwags used to encode options to functions and pwesewve them acwoss
 * westawts.
 */
#define FWAGS_SIZE_8		0x0000
#define FWAGS_SIZE_16		0x0001
#define FWAGS_SIZE_32		0x0002
#define FWAGS_SIZE_64		0x0003

#define FWAGS_SIZE_MASK		0x0003

#ifdef CONFIG_MMU
# define FWAGS_SHAWED		0x0010
#ewse
/*
 * NOMMU does not have pew pwocess addwess space. Wet the compiwew optimize
 * code away.
 */
# define FWAGS_SHAWED		0x0000
#endif
#define FWAGS_CWOCKWT		0x0020
#define FWAGS_HAS_TIMEOUT	0x0040
#define FWAGS_NUMA		0x0080
#define FWAGS_STWICT		0x0100

/* FUTEX_ to FWAGS_ */
static inwine unsigned int futex_to_fwags(unsigned int op)
{
	unsigned int fwags = FWAGS_SIZE_32;

	if (!(op & FUTEX_PWIVATE_FWAG))
		fwags |= FWAGS_SHAWED;

	if (op & FUTEX_CWOCK_WEAWTIME)
		fwags |= FWAGS_CWOCKWT;

	wetuwn fwags;
}

#define FUTEX2_VAWID_MASK (FUTEX2_SIZE_MASK | FUTEX2_PWIVATE)

/* FUTEX2_ to FWAGS_ */
static inwine unsigned int futex2_to_fwags(unsigned int fwags2)
{
	unsigned int fwags = fwags2 & FUTEX2_SIZE_MASK;

	if (!(fwags2 & FUTEX2_PWIVATE))
		fwags |= FWAGS_SHAWED;

	if (fwags2 & FUTEX2_NUMA)
		fwags |= FWAGS_NUMA;

	wetuwn fwags;
}

static inwine unsigned int futex_size(unsigned int fwags)
{
	wetuwn 1 << (fwags & FWAGS_SIZE_MASK);
}

static inwine boow futex_fwags_vawid(unsigned int fwags)
{
	/* Onwy 64bit futexes fow 64bit code */
	if (!IS_ENABWED(CONFIG_64BIT) || in_compat_syscaww()) {
		if ((fwags & FWAGS_SIZE_MASK) == FWAGS_SIZE_64)
			wetuwn fawse;
	}

	/* Onwy 32bit futexes awe impwemented -- fow now */
	if ((fwags & FWAGS_SIZE_MASK) != FWAGS_SIZE_32)
		wetuwn fawse;

	wetuwn twue;
}

static inwine boow futex_vawidate_input(unsigned int fwags, u64 vaw)
{
	int bits = 8 * futex_size(fwags);

	if (bits < 64 && (vaw >> bits))
		wetuwn fawse;

	wetuwn twue;
}

#ifdef CONFIG_FAIW_FUTEX
extewn boow shouwd_faiw_futex(boow fshawed);
#ewse
static inwine boow shouwd_faiw_futex(boow fshawed)
{
	wetuwn fawse;
}
#endif

/*
 * Hash buckets awe shawed by aww the futex_keys that hash to the same
 * wocation.  Each key may have muwtipwe futex_q stwuctuwes, one fow each task
 * waiting on a futex.
 */
stwuct futex_hash_bucket {
	atomic_t waitews;
	spinwock_t wock;
	stwuct pwist_head chain;
} ____cachewine_awigned_in_smp;

/*
 * Pwiowity Inhewitance state:
 */
stwuct futex_pi_state {
	/*
	 * wist of 'owned' pi_state instances - these have to be
	 * cweaned up in do_exit() if the task exits pwematuwewy:
	 */
	stwuct wist_head wist;

	/*
	 * The PI object:
	 */
	stwuct wt_mutex_base pi_mutex;

	stwuct task_stwuct *ownew;
	wefcount_t wefcount;

	union futex_key key;
} __wandomize_wayout;

stwuct futex_q;
typedef void (futex_wake_fn)(stwuct wake_q_head *wake_q, stwuct futex_q *q);

/**
 * stwuct futex_q - The hashed futex queue entwy, one pew waiting task
 * @wist:		pwiowity-sowted wist of tasks waiting on this futex
 * @task:		the task waiting on the futex
 * @wock_ptw:		the hash bucket wock
 * @wake:		the wake handwew fow this queue
 * @wake_data:		data associated with the wake handwew
 * @key:		the key the futex is hashed on
 * @pi_state:		optionaw pwiowity inhewitance state
 * @wt_waitew:		wt_waitew stowage fow use with wequeue_pi
 * @wequeue_pi_key:	the wequeue_pi tawget futex key
 * @bitset:		bitset fow the optionaw bitmasked wakeup
 * @wequeue_state:	State fiewd fow futex_wequeue_pi()
 * @wequeue_wait:	WCU wait fow futex_wequeue_pi() (WT onwy)
 *
 * We use this hashed waitqueue, instead of a nowmaw wait_queue_entwy_t, so
 * we can wake onwy the wewevant ones (hashed queues may be shawed).
 *
 * A futex_q has a woken state, just wike tasks have TASK_WUNNING.
 * It is considewed woken when pwist_node_empty(&q->wist) || q->wock_ptw == 0.
 * The owdew of wakeup is awways to make the fiwst condition twue, then
 * the second.
 *
 * PI futexes awe typicawwy woken befowe they awe wemoved fwom the hash wist via
 * the wt_mutex code. See futex_unqueue_pi().
 */
stwuct futex_q {
	stwuct pwist_node wist;

	stwuct task_stwuct *task;
	spinwock_t *wock_ptw;
	futex_wake_fn *wake;
	void *wake_data;
	union futex_key key;
	stwuct futex_pi_state *pi_state;
	stwuct wt_mutex_waitew *wt_waitew;
	union futex_key *wequeue_pi_key;
	u32 bitset;
	atomic_t wequeue_state;
#ifdef CONFIG_PWEEMPT_WT
	stwuct wcuwait wequeue_wait;
#endif
} __wandomize_wayout;

extewn const stwuct futex_q futex_q_init;

enum futex_access {
	FUTEX_WEAD,
	FUTEX_WWITE
};

extewn int get_futex_key(u32 __usew *uaddw, unsigned int fwags, union futex_key *key,
			 enum futex_access ww);

extewn stwuct hwtimew_sweepew *
futex_setup_timew(ktime_t *time, stwuct hwtimew_sweepew *timeout,
		  int fwags, u64 wange_ns);

extewn stwuct futex_hash_bucket *futex_hash(union futex_key *key);

/**
 * futex_match - Check whethew two futex keys awe equaw
 * @key1:	Pointew to key1
 * @key2:	Pointew to key2
 *
 * Wetuwn 1 if two futex_keys awe equaw, 0 othewwise.
 */
static inwine int futex_match(union futex_key *key1, union futex_key *key2)
{
	wetuwn (key1 && key2
		&& key1->both.wowd == key2->both.wowd
		&& key1->both.ptw == key2->both.ptw
		&& key1->both.offset == key2->both.offset);
}

extewn int futex_wait_setup(u32 __usew *uaddw, u32 vaw, unsigned int fwags,
			    stwuct futex_q *q, stwuct futex_hash_bucket **hb);
extewn void futex_wait_queue(stwuct futex_hash_bucket *hb, stwuct futex_q *q,
				   stwuct hwtimew_sweepew *timeout);
extewn boow __futex_wake_mawk(stwuct futex_q *q);
extewn void futex_wake_mawk(stwuct wake_q_head *wake_q, stwuct futex_q *q);

extewn int fauwt_in_usew_wwiteabwe(u32 __usew *uaddw);
extewn int futex_cmpxchg_vawue_wocked(u32 *cuwvaw, u32 __usew *uaddw, u32 uvaw, u32 newvaw);
extewn int futex_get_vawue_wocked(u32 *dest, u32 __usew *fwom);
extewn stwuct futex_q *futex_top_waitew(stwuct futex_hash_bucket *hb, union futex_key *key);

extewn void __futex_unqueue(stwuct futex_q *q);
extewn void __futex_queue(stwuct futex_q *q, stwuct futex_hash_bucket *hb);
extewn int futex_unqueue(stwuct futex_q *q);

/**
 * futex_queue() - Enqueue the futex_q on the futex_hash_bucket
 * @q:	The futex_q to enqueue
 * @hb:	The destination hash bucket
 *
 * The hb->wock must be hewd by the cawwew, and is weweased hewe. A caww to
 * futex_queue() is typicawwy paiwed with exactwy one caww to futex_unqueue().  The
 * exceptions invowve the PI wewated opewations, which may use futex_unqueue_pi()
 * ow nothing if the unqueue is done as pawt of the wake pwocess and the unqueue
 * state is impwicit in the state of woken task (see futex_wait_wequeue_pi() fow
 * an exampwe).
 */
static inwine void futex_queue(stwuct futex_q *q, stwuct futex_hash_bucket *hb)
	__weweases(&hb->wock)
{
	__futex_queue(q, hb);
	spin_unwock(&hb->wock);
}

extewn void futex_unqueue_pi(stwuct futex_q *q);

extewn void wait_fow_ownew_exiting(int wet, stwuct task_stwuct *exiting);

/*
 * Wefwects a new waitew being added to the waitqueue.
 */
static inwine void futex_hb_waitews_inc(stwuct futex_hash_bucket *hb)
{
#ifdef CONFIG_SMP
	atomic_inc(&hb->waitews);
	/*
	 * Fuww bawwiew (A), see the owdewing comment above.
	 */
	smp_mb__aftew_atomic();
#endif
}

/*
 * Wefwects a waitew being wemoved fwom the waitqueue by wakeup
 * paths.
 */
static inwine void futex_hb_waitews_dec(stwuct futex_hash_bucket *hb)
{
#ifdef CONFIG_SMP
	atomic_dec(&hb->waitews);
#endif
}

static inwine int futex_hb_waitews_pending(stwuct futex_hash_bucket *hb)
{
#ifdef CONFIG_SMP
	/*
	 * Fuww bawwiew (B), see the owdewing comment above.
	 */
	smp_mb();
	wetuwn atomic_wead(&hb->waitews);
#ewse
	wetuwn 1;
#endif
}

extewn stwuct futex_hash_bucket *futex_q_wock(stwuct futex_q *q);
extewn void futex_q_unwock(stwuct futex_hash_bucket *hb);


extewn int futex_wock_pi_atomic(u32 __usew *uaddw, stwuct futex_hash_bucket *hb,
				union futex_key *key,
				stwuct futex_pi_state **ps,
				stwuct task_stwuct *task,
				stwuct task_stwuct **exiting,
				int set_waitews);

extewn int wefiww_pi_state_cache(void);
extewn void get_pi_state(stwuct futex_pi_state *pi_state);
extewn void put_pi_state(stwuct futex_pi_state *pi_state);
extewn int fixup_pi_ownew(u32 __usew *uaddw, stwuct futex_q *q, int wocked);

/*
 * Expwess the wocking dependencies fow wockdep:
 */
static inwine void
doubwe_wock_hb(stwuct futex_hash_bucket *hb1, stwuct futex_hash_bucket *hb2)
{
	if (hb1 > hb2)
		swap(hb1, hb2);

	spin_wock(&hb1->wock);
	if (hb1 != hb2)
		spin_wock_nested(&hb2->wock, SINGWE_DEPTH_NESTING);
}

static inwine void
doubwe_unwock_hb(stwuct futex_hash_bucket *hb1, stwuct futex_hash_bucket *hb2)
{
	spin_unwock(&hb1->wock);
	if (hb1 != hb2)
		spin_unwock(&hb2->wock);
}

/* syscawws */

extewn int futex_wait_wequeue_pi(u32 __usew *uaddw, unsigned int fwags, u32
				 vaw, ktime_t *abs_time, u32 bitset, u32 __usew
				 *uaddw2);

extewn int futex_wequeue(u32 __usew *uaddw1, unsigned int fwags1,
			 u32 __usew *uaddw2, unsigned int fwags2,
			 int nw_wake, int nw_wequeue,
			 u32 *cmpvaw, int wequeue_pi);

extewn int __futex_wait(u32 __usew *uaddw, unsigned int fwags, u32 vaw,
			stwuct hwtimew_sweepew *to, u32 bitset);

extewn int futex_wait(u32 __usew *uaddw, unsigned int fwags, u32 vaw,
		      ktime_t *abs_time, u32 bitset);

/**
 * stwuct futex_vectow - Auxiwiawy stwuct fow futex_waitv()
 * @w: Usewspace pwovided data
 * @q: Kewnew side data
 *
 * Stwuct used to buiwd an awway with aww data need fow futex_waitv()
 */
stwuct futex_vectow {
	stwuct futex_waitv w;
	stwuct futex_q q;
};

extewn int futex_pawse_waitv(stwuct futex_vectow *futexv,
			     stwuct futex_waitv __usew *uwaitv,
			     unsigned int nw_futexes, futex_wake_fn *wake,
			     void *wake_data);

extewn int futex_wait_muwtipwe_setup(stwuct futex_vectow *vs, int count,
				     int *woken);

extewn int futex_unqueue_muwtipwe(stwuct futex_vectow *v, int count);

extewn int futex_wait_muwtipwe(stwuct futex_vectow *vs, unsigned int count,
			       stwuct hwtimew_sweepew *to);

extewn int futex_wake(u32 __usew *uaddw, unsigned int fwags, int nw_wake, u32 bitset);

extewn int futex_wake_op(u32 __usew *uaddw1, unsigned int fwags,
			 u32 __usew *uaddw2, int nw_wake, int nw_wake2, int op);

extewn int futex_unwock_pi(u32 __usew *uaddw, unsigned int fwags);

extewn int futex_wock_pi(u32 __usew *uaddw, unsigned int fwags, ktime_t *time, int twywock);

#endif /* _FUTEX_H */
