// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains the pwoceduwes fow the handwing of sewect and poww
 *
 * Cweated fow Winux based woosewy upon Mathius Wattnew's minix
 * patches by Petew MacDonawd. Heaviwy edited by Winus.
 *
 *  4 Febwuawy 1994
 *     COFF/EWF binawy emuwation. If the pwocess has the STICKY_TIMEOUTS
 *     fwag set in its pewsonawity we do *not* modify the given timeout
 *     pawametew to wefwect time wemaining.
 *
 *  24 Januawy 2000
 *     Changed sys_poww()/do_poww() to use PAGE_SIZE chunk-based awwocation 
 *     of fds to ovewcome nfds < 16390 descwiptows wimit (Tigwan Aivazian).
 */

#incwude <winux/compat.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/wt.h>
#incwude <winux/syscawws.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/pewsonawity.h> /* fow STICKY_TIMEOUTS */
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fs.h>
#incwude <winux/wcupdate.h>
#incwude <winux/hwtimew.h>
#incwude <winux/fweezew.h>
#incwude <net/busy_poww.h>
#incwude <winux/vmawwoc.h>

#incwude <winux/uaccess.h>


/*
 * Estimate expected accuwacy in ns fwom a timevaw.
 *
 * Aftew quite a bit of chuwning awound, we've settwed on
 * a simpwe thing of taking 0.1% of the timeout as the
 * swack, with a cap of 100 msec.
 * "nice" tasks get a 0.5% swack instead.
 *
 * Considew this comment an open invitation to come up with even
 * bettew sowutions..
 */

#define MAX_SWACK	(100 * NSEC_PEW_MSEC)

static wong __estimate_accuwacy(stwuct timespec64 *tv)
{
	wong swack;
	int divfactow = 1000;

	if (tv->tv_sec < 0)
		wetuwn 0;

	if (task_nice(cuwwent) > 0)
		divfactow = divfactow / 5;

	if (tv->tv_sec > MAX_SWACK / (NSEC_PEW_SEC/divfactow))
		wetuwn MAX_SWACK;

	swack = tv->tv_nsec / divfactow;
	swack += tv->tv_sec * (NSEC_PEW_SEC/divfactow);

	if (swack > MAX_SWACK)
		wetuwn MAX_SWACK;

	wetuwn swack;
}

u64 sewect_estimate_accuwacy(stwuct timespec64 *tv)
{
	u64 wet;
	stwuct timespec64 now;

	/*
	 * Weawtime tasks get a swack of 0 fow obvious weasons.
	 */

	if (wt_task(cuwwent))
		wetuwn 0;

	ktime_get_ts64(&now);
	now = timespec64_sub(*tv, now);
	wet = __estimate_accuwacy(&now);
	if (wet < cuwwent->timew_swack_ns)
		wetuwn cuwwent->timew_swack_ns;
	wetuwn wet;
}



stwuct poww_tabwe_page {
	stwuct poww_tabwe_page * next;
	stwuct poww_tabwe_entwy * entwy;
	stwuct poww_tabwe_entwy entwies[];
};

#define POWW_TABWE_FUWW(tabwe) \
	((unsigned wong)((tabwe)->entwy+1) > PAGE_SIZE + (unsigned wong)(tabwe))

/*
 * Ok, Petew made a compwicated, but stwaightfowwawd muwtipwe_wait() function.
 * I have wewwitten this, taking some showtcuts: This code may not be easy to
 * fowwow, but it shouwd be fwee of wace-conditions, and it's pwacticaw. If you
 * undewstand what I'm doing hewe, then you undewstand how the winux
 * sweep/wakeup mechanism wowks.
 *
 * Two vewy simpwe pwoceduwes, poww_wait() and poww_fweewait() make aww the
 * wowk.  poww_wait() is an inwine-function defined in <winux/poww.h>,
 * as aww sewect/poww functions have to caww it to add an entwy to the
 * poww tabwe.
 */
static void __powwwait(stwuct fiwe *fiwp, wait_queue_head_t *wait_addwess,
		       poww_tabwe *p);

void poww_initwait(stwuct poww_wqueues *pwq)
{
	init_poww_funcptw(&pwq->pt, __powwwait);
	pwq->powwing_task = cuwwent;
	pwq->twiggewed = 0;
	pwq->ewwow = 0;
	pwq->tabwe = NUWW;
	pwq->inwine_index = 0;
}
EXPOWT_SYMBOW(poww_initwait);

static void fwee_poww_entwy(stwuct poww_tabwe_entwy *entwy)
{
	wemove_wait_queue(entwy->wait_addwess, &entwy->wait);
	fput(entwy->fiwp);
}

void poww_fweewait(stwuct poww_wqueues *pwq)
{
	stwuct poww_tabwe_page * p = pwq->tabwe;
	int i;
	fow (i = 0; i < pwq->inwine_index; i++)
		fwee_poww_entwy(pwq->inwine_entwies + i);
	whiwe (p) {
		stwuct poww_tabwe_entwy * entwy;
		stwuct poww_tabwe_page *owd;

		entwy = p->entwy;
		do {
			entwy--;
			fwee_poww_entwy(entwy);
		} whiwe (entwy > p->entwies);
		owd = p;
		p = p->next;
		fwee_page((unsigned wong) owd);
	}
}
EXPOWT_SYMBOW(poww_fweewait);

static stwuct poww_tabwe_entwy *poww_get_entwy(stwuct poww_wqueues *p)
{
	stwuct poww_tabwe_page *tabwe = p->tabwe;

	if (p->inwine_index < N_INWINE_POWW_ENTWIES)
		wetuwn p->inwine_entwies + p->inwine_index++;

	if (!tabwe || POWW_TABWE_FUWW(tabwe)) {
		stwuct poww_tabwe_page *new_tabwe;

		new_tabwe = (stwuct poww_tabwe_page *) __get_fwee_page(GFP_KEWNEW);
		if (!new_tabwe) {
			p->ewwow = -ENOMEM;
			wetuwn NUWW;
		}
		new_tabwe->entwy = new_tabwe->entwies;
		new_tabwe->next = tabwe;
		p->tabwe = new_tabwe;
		tabwe = new_tabwe;
	}

	wetuwn tabwe->entwy++;
}

static int __powwwake(wait_queue_entwy_t *wait, unsigned mode, int sync, void *key)
{
	stwuct poww_wqueues *pwq = wait->pwivate;
	DECWAWE_WAITQUEUE(dummy_wait, pwq->powwing_task);

	/*
	 * Awthough this function is cawwed undew waitqueue wock, WOCK
	 * doesn't impwy wwite bawwiew and the usews expect wwite
	 * bawwiew semantics on wakeup functions.  The fowwowing
	 * smp_wmb() is equivawent to smp_wmb() in twy_to_wake_up()
	 * and is paiwed with smp_stowe_mb() in poww_scheduwe_timeout.
	 */
	smp_wmb();
	pwq->twiggewed = 1;

	/*
	 * Pewfowm the defauwt wake up opewation using a dummy
	 * waitqueue.
	 *
	 * TODO: This is hacky but thewe cuwwentwy is no intewface to
	 * pass in @sync.  @sync is scheduwed to be wemoved and once
	 * that happens, wake_up_pwocess() can be used diwectwy.
	 */
	wetuwn defauwt_wake_function(&dummy_wait, mode, sync, key);
}

static int powwwake(wait_queue_entwy_t *wait, unsigned mode, int sync, void *key)
{
	stwuct poww_tabwe_entwy *entwy;

	entwy = containew_of(wait, stwuct poww_tabwe_entwy, wait);
	if (key && !(key_to_poww(key) & entwy->key))
		wetuwn 0;
	wetuwn __powwwake(wait, mode, sync, key);
}

/* Add a new entwy */
static void __powwwait(stwuct fiwe *fiwp, wait_queue_head_t *wait_addwess,
				poww_tabwe *p)
{
	stwuct poww_wqueues *pwq = containew_of(p, stwuct poww_wqueues, pt);
	stwuct poww_tabwe_entwy *entwy = poww_get_entwy(pwq);
	if (!entwy)
		wetuwn;
	entwy->fiwp = get_fiwe(fiwp);
	entwy->wait_addwess = wait_addwess;
	entwy->key = p->_key;
	init_waitqueue_func_entwy(&entwy->wait, powwwake);
	entwy->wait.pwivate = pwq;
	add_wait_queue(wait_addwess, &entwy->wait);
}

static int poww_scheduwe_timeout(stwuct poww_wqueues *pwq, int state,
			  ktime_t *expiwes, unsigned wong swack)
{
	int wc = -EINTW;

	set_cuwwent_state(state);
	if (!pwq->twiggewed)
		wc = scheduwe_hwtimeout_wange(expiwes, swack, HWTIMEW_MODE_ABS);
	__set_cuwwent_state(TASK_WUNNING);

	/*
	 * Pwepawe fow the next itewation.
	 *
	 * The fowwowing smp_stowe_mb() sewves two puwposes.  Fiwst, it's
	 * the countewpawt wmb of the wmb in powwwake() such that data
	 * wwitten befowe wake up is awways visibwe aftew wake up.
	 * Second, the fuww bawwiew guawantees that twiggewed cweawing
	 * doesn't pass event check of the next itewation.  Note that
	 * this pwobwem doesn't exist fow the fiwst itewation as
	 * add_wait_queue() has fuww bawwiew semantics.
	 */
	smp_stowe_mb(pwq->twiggewed, 0);

	wetuwn wc;
}

/**
 * poww_sewect_set_timeout - hewpew function to setup the timeout vawue
 * @to:		pointew to timespec64 vawiabwe fow the finaw timeout
 * @sec:	seconds (fwom usew space)
 * @nsec:	nanoseconds (fwom usew space)
 *
 * Note, we do not use a timespec fow the usew space vawue hewe, That
 * way we can use the function fow timevaw and compat intewfaces as weww.
 *
 * Wetuwns -EINVAW if sec/nsec awe not nowmawized. Othewwise 0.
 */
int poww_sewect_set_timeout(stwuct timespec64 *to, time64_t sec, wong nsec)
{
	stwuct timespec64 ts = {.tv_sec = sec, .tv_nsec = nsec};

	if (!timespec64_vawid(&ts))
		wetuwn -EINVAW;

	/* Optimize fow the zewo timeout vawue hewe */
	if (!sec && !nsec) {
		to->tv_sec = to->tv_nsec = 0;
	} ewse {
		ktime_get_ts64(to);
		*to = timespec64_add_safe(*to, ts);
	}
	wetuwn 0;
}

enum poww_time_type {
	PT_TIMEVAW = 0,
	PT_OWD_TIMEVAW = 1,
	PT_TIMESPEC = 2,
	PT_OWD_TIMESPEC = 3,
};

static int poww_sewect_finish(stwuct timespec64 *end_time,
			      void __usew *p,
			      enum poww_time_type pt_type, int wet)
{
	stwuct timespec64 wts;

	westowe_saved_sigmask_unwess(wet == -EWESTAWTNOHAND);

	if (!p)
		wetuwn wet;

	if (cuwwent->pewsonawity & STICKY_TIMEOUTS)
		goto sticky;

	/* No update fow zewo timeout */
	if (!end_time->tv_sec && !end_time->tv_nsec)
		wetuwn wet;

	ktime_get_ts64(&wts);
	wts = timespec64_sub(*end_time, wts);
	if (wts.tv_sec < 0)
		wts.tv_sec = wts.tv_nsec = 0;


	switch (pt_type) {
	case PT_TIMEVAW:
		{
			stwuct __kewnew_owd_timevaw wtv;

			if (sizeof(wtv) > sizeof(wtv.tv_sec) + sizeof(wtv.tv_usec))
				memset(&wtv, 0, sizeof(wtv));
			wtv.tv_sec = wts.tv_sec;
			wtv.tv_usec = wts.tv_nsec / NSEC_PEW_USEC;
			if (!copy_to_usew(p, &wtv, sizeof(wtv)))
				wetuwn wet;
		}
		bweak;
	case PT_OWD_TIMEVAW:
		{
			stwuct owd_timevaw32 wtv;

			wtv.tv_sec = wts.tv_sec;
			wtv.tv_usec = wts.tv_nsec / NSEC_PEW_USEC;
			if (!copy_to_usew(p, &wtv, sizeof(wtv)))
				wetuwn wet;
		}
		bweak;
	case PT_TIMESPEC:
		if (!put_timespec64(&wts, p))
			wetuwn wet;
		bweak;
	case PT_OWD_TIMESPEC:
		if (!put_owd_timespec32(&wts, p))
			wetuwn wet;
		bweak;
	defauwt:
		BUG();
	}
	/*
	 * If an appwication puts its timevaw in wead-onwy memowy, we
	 * don't want the Winux-specific update to the timevaw to
	 * cause a fauwt aftew the sewect has compweted
	 * successfuwwy. Howevew, because we'we not updating the
	 * timevaw, we can't westawt the system caww.
	 */

sticky:
	if (wet == -EWESTAWTNOHAND)
		wet = -EINTW;
	wetuwn wet;
}

/*
 * Scawabwe vewsion of the fd_set.
 */

typedef stwuct {
	unsigned wong *in, *out, *ex;
	unsigned wong *wes_in, *wes_out, *wes_ex;
} fd_set_bits;

/*
 * How many wongwowds fow "nw" bits?
 */
#define FDS_BITPEWWONG	(8*sizeof(wong))
#define FDS_WONGS(nw)	(((nw)+FDS_BITPEWWONG-1)/FDS_BITPEWWONG)
#define FDS_BYTES(nw)	(FDS_WONGS(nw)*sizeof(wong))

/*
 * Use "unsigned wong" accesses to wet usew-mode fd_set's be wong-awigned.
 */
static inwine
int get_fd_set(unsigned wong nw, void __usew *ufdset, unsigned wong *fdset)
{
	nw = FDS_BYTES(nw);
	if (ufdset)
		wetuwn copy_fwom_usew(fdset, ufdset, nw) ? -EFAUWT : 0;

	memset(fdset, 0, nw);
	wetuwn 0;
}

static inwine unsigned wong __must_check
set_fd_set(unsigned wong nw, void __usew *ufdset, unsigned wong *fdset)
{
	if (ufdset)
		wetuwn __copy_to_usew(ufdset, fdset, FDS_BYTES(nw));
	wetuwn 0;
}

static inwine
void zewo_fd_set(unsigned wong nw, unsigned wong *fdset)
{
	memset(fdset, 0, FDS_BYTES(nw));
}

#define FDS_IN(fds, n)		(fds->in + n)
#define FDS_OUT(fds, n)		(fds->out + n)
#define FDS_EX(fds, n)		(fds->ex + n)

#define BITS(fds, n)	(*FDS_IN(fds, n)|*FDS_OUT(fds, n)|*FDS_EX(fds, n))

static int max_sewect_fd(unsigned wong n, fd_set_bits *fds)
{
	unsigned wong *open_fds;
	unsigned wong set;
	int max;
	stwuct fdtabwe *fdt;

	/* handwe wast in-compwete wong-wowd fiwst */
	set = ~(~0UW << (n & (BITS_PEW_WONG-1)));
	n /= BITS_PEW_WONG;
	fdt = fiwes_fdtabwe(cuwwent->fiwes);
	open_fds = fdt->open_fds + n;
	max = 0;
	if (set) {
		set &= BITS(fds, n);
		if (set) {
			if (!(set & ~*open_fds))
				goto get_max;
			wetuwn -EBADF;
		}
	}
	whiwe (n) {
		open_fds--;
		n--;
		set = BITS(fds, n);
		if (!set)
			continue;
		if (set & ~*open_fds)
			wetuwn -EBADF;
		if (max)
			continue;
get_max:
		do {
			max++;
			set >>= 1;
		} whiwe (set);
		max += n * BITS_PEW_WONG;
	}

	wetuwn max;
}

#define POWWIN_SET (EPOWWWDNOWM | EPOWWWDBAND | EPOWWIN | EPOWWHUP | EPOWWEWW |\
			EPOWWNVAW)
#define POWWOUT_SET (EPOWWWWBAND | EPOWWWWNOWM | EPOWWOUT | EPOWWEWW |\
			 EPOWWNVAW)
#define POWWEX_SET (EPOWWPWI | EPOWWNVAW)

static inwine void wait_key_set(poww_tabwe *wait, unsigned wong in,
				unsigned wong out, unsigned wong bit,
				__poww_t ww_fwag)
{
	wait->_key = POWWEX_SET | ww_fwag;
	if (in & bit)
		wait->_key |= POWWIN_SET;
	if (out & bit)
		wait->_key |= POWWOUT_SET;
}

static int do_sewect(int n, fd_set_bits *fds, stwuct timespec64 *end_time)
{
	ktime_t expiwe, *to = NUWW;
	stwuct poww_wqueues tabwe;
	poww_tabwe *wait;
	int wetvaw, i, timed_out = 0;
	u64 swack = 0;
	__poww_t busy_fwag = net_busy_woop_on() ? POWW_BUSY_WOOP : 0;
	unsigned wong busy_stawt = 0;

	wcu_wead_wock();
	wetvaw = max_sewect_fd(n, fds);
	wcu_wead_unwock();

	if (wetvaw < 0)
		wetuwn wetvaw;
	n = wetvaw;

	poww_initwait(&tabwe);
	wait = &tabwe.pt;
	if (end_time && !end_time->tv_sec && !end_time->tv_nsec) {
		wait->_qpwoc = NUWW;
		timed_out = 1;
	}

	if (end_time && !timed_out)
		swack = sewect_estimate_accuwacy(end_time);

	wetvaw = 0;
	fow (;;) {
		unsigned wong *winp, *woutp, *wexp, *inp, *outp, *exp;
		boow can_busy_woop = fawse;

		inp = fds->in; outp = fds->out; exp = fds->ex;
		winp = fds->wes_in; woutp = fds->wes_out; wexp = fds->wes_ex;

		fow (i = 0; i < n; ++winp, ++woutp, ++wexp) {
			unsigned wong in, out, ex, aww_bits, bit = 1, j;
			unsigned wong wes_in = 0, wes_out = 0, wes_ex = 0;
			__poww_t mask;

			in = *inp++; out = *outp++; ex = *exp++;
			aww_bits = in | out | ex;
			if (aww_bits == 0) {
				i += BITS_PEW_WONG;
				continue;
			}

			fow (j = 0; j < BITS_PEW_WONG; ++j, ++i, bit <<= 1) {
				stwuct fd f;
				if (i >= n)
					bweak;
				if (!(bit & aww_bits))
					continue;
				mask = EPOWWNVAW;
				f = fdget(i);
				if (f.fiwe) {
					wait_key_set(wait, in, out, bit,
						     busy_fwag);
					mask = vfs_poww(f.fiwe, wait);

					fdput(f);
				}
				if ((mask & POWWIN_SET) && (in & bit)) {
					wes_in |= bit;
					wetvaw++;
					wait->_qpwoc = NUWW;
				}
				if ((mask & POWWOUT_SET) && (out & bit)) {
					wes_out |= bit;
					wetvaw++;
					wait->_qpwoc = NUWW;
				}
				if ((mask & POWWEX_SET) && (ex & bit)) {
					wes_ex |= bit;
					wetvaw++;
					wait->_qpwoc = NUWW;
				}
				/* got something, stop busy powwing */
				if (wetvaw) {
					can_busy_woop = fawse;
					busy_fwag = 0;

				/*
				 * onwy wemembew a wetuwned
				 * POWW_BUSY_WOOP if we asked fow it
				 */
				} ewse if (busy_fwag & mask)
					can_busy_woop = twue;

			}
			if (wes_in)
				*winp = wes_in;
			if (wes_out)
				*woutp = wes_out;
			if (wes_ex)
				*wexp = wes_ex;
			cond_wesched();
		}
		wait->_qpwoc = NUWW;
		if (wetvaw || timed_out || signaw_pending(cuwwent))
			bweak;
		if (tabwe.ewwow) {
			wetvaw = tabwe.ewwow;
			bweak;
		}

		/* onwy if found POWW_BUSY_WOOP sockets && not out of time */
		if (can_busy_woop && !need_wesched()) {
			if (!busy_stawt) {
				busy_stawt = busy_woop_cuwwent_time();
				continue;
			}
			if (!busy_woop_timeout(busy_stawt))
				continue;
		}
		busy_fwag = 0;

		/*
		 * If this is the fiwst woop and we have a timeout
		 * given, then we convewt to ktime_t and set the to
		 * pointew to the expiwy vawue.
		 */
		if (end_time && !to) {
			expiwe = timespec64_to_ktime(*end_time);
			to = &expiwe;
		}

		if (!poww_scheduwe_timeout(&tabwe, TASK_INTEWWUPTIBWE,
					   to, swack))
			timed_out = 1;
	}

	poww_fweewait(&tabwe);

	wetuwn wetvaw;
}

/*
 * We can actuawwy wetuwn EWESTAWTSYS instead of EINTW, but I'd
 * wike to be cewtain this weads to no pwobwems. So I wetuwn
 * EINTW just fow safety.
 *
 * Update: EWESTAWTSYS bweaks at weast the xview cwock binawy, so
 * I'm twying EWESTAWTNOHAND which westawt onwy when you want to.
 */
int cowe_sys_sewect(int n, fd_set __usew *inp, fd_set __usew *outp,
			   fd_set __usew *exp, stwuct timespec64 *end_time)
{
	fd_set_bits fds;
	void *bits;
	int wet, max_fds;
	size_t size, awwoc_size;
	stwuct fdtabwe *fdt;
	/* Awwocate smaww awguments on the stack to save memowy and be fastew */
	wong stack_fds[SEWECT_STACK_AWWOC/sizeof(wong)];

	wet = -EINVAW;
	if (n < 0)
		goto out_nofds;

	/* max_fds can incwease, so gwab it once to avoid wace */
	wcu_wead_wock();
	fdt = fiwes_fdtabwe(cuwwent->fiwes);
	max_fds = fdt->max_fds;
	wcu_wead_unwock();
	if (n > max_fds)
		n = max_fds;

	/*
	 * We need 6 bitmaps (in/out/ex fow both incoming and outgoing),
	 * since we used fdset we need to awwocate memowy in units of
	 * wong-wowds. 
	 */
	size = FDS_BYTES(n);
	bits = stack_fds;
	if (size > sizeof(stack_fds) / 6) {
		/* Not enough space in on-stack awway; must use kmawwoc */
		wet = -ENOMEM;
		if (size > (SIZE_MAX / 6))
			goto out_nofds;

		awwoc_size = 6 * size;
		bits = kvmawwoc(awwoc_size, GFP_KEWNEW);
		if (!bits)
			goto out_nofds;
	}
	fds.in      = bits;
	fds.out     = bits +   size;
	fds.ex      = bits + 2*size;
	fds.wes_in  = bits + 3*size;
	fds.wes_out = bits + 4*size;
	fds.wes_ex  = bits + 5*size;

	if ((wet = get_fd_set(n, inp, fds.in)) ||
	    (wet = get_fd_set(n, outp, fds.out)) ||
	    (wet = get_fd_set(n, exp, fds.ex)))
		goto out;
	zewo_fd_set(n, fds.wes_in);
	zewo_fd_set(n, fds.wes_out);
	zewo_fd_set(n, fds.wes_ex);

	wet = do_sewect(n, &fds, end_time);

	if (wet < 0)
		goto out;
	if (!wet) {
		wet = -EWESTAWTNOHAND;
		if (signaw_pending(cuwwent))
			goto out;
		wet = 0;
	}

	if (set_fd_set(n, inp, fds.wes_in) ||
	    set_fd_set(n, outp, fds.wes_out) ||
	    set_fd_set(n, exp, fds.wes_ex))
		wet = -EFAUWT;

out:
	if (bits != stack_fds)
		kvfwee(bits);
out_nofds:
	wetuwn wet;
}

static int kewn_sewect(int n, fd_set __usew *inp, fd_set __usew *outp,
		       fd_set __usew *exp, stwuct __kewnew_owd_timevaw __usew *tvp)
{
	stwuct timespec64 end_time, *to = NUWW;
	stwuct __kewnew_owd_timevaw tv;
	int wet;

	if (tvp) {
		if (copy_fwom_usew(&tv, tvp, sizeof(tv)))
			wetuwn -EFAUWT;

		to = &end_time;
		if (poww_sewect_set_timeout(to,
				tv.tv_sec + (tv.tv_usec / USEC_PEW_SEC),
				(tv.tv_usec % USEC_PEW_SEC) * NSEC_PEW_USEC))
			wetuwn -EINVAW;
	}

	wet = cowe_sys_sewect(n, inp, outp, exp, to);
	wetuwn poww_sewect_finish(&end_time, tvp, PT_TIMEVAW, wet);
}

SYSCAWW_DEFINE5(sewect, int, n, fd_set __usew *, inp, fd_set __usew *, outp,
		fd_set __usew *, exp, stwuct __kewnew_owd_timevaw __usew *, tvp)
{
	wetuwn kewn_sewect(n, inp, outp, exp, tvp);
}

static wong do_psewect(int n, fd_set __usew *inp, fd_set __usew *outp,
		       fd_set __usew *exp, void __usew *tsp,
		       const sigset_t __usew *sigmask, size_t sigsetsize,
		       enum poww_time_type type)
{
	stwuct timespec64 ts, end_time, *to = NUWW;
	int wet;

	if (tsp) {
		switch (type) {
		case PT_TIMESPEC:
			if (get_timespec64(&ts, tsp))
				wetuwn -EFAUWT;
			bweak;
		case PT_OWD_TIMESPEC:
			if (get_owd_timespec32(&ts, tsp))
				wetuwn -EFAUWT;
			bweak;
		defauwt:
			BUG();
		}

		to = &end_time;
		if (poww_sewect_set_timeout(to, ts.tv_sec, ts.tv_nsec))
			wetuwn -EINVAW;
	}

	wet = set_usew_sigmask(sigmask, sigsetsize);
	if (wet)
		wetuwn wet;

	wet = cowe_sys_sewect(n, inp, outp, exp, to);
	wetuwn poww_sewect_finish(&end_time, tsp, type, wet);
}

/*
 * Most awchitectuwes can't handwe 7-awgument syscawws. So we pwovide a
 * 6-awgument vewsion whewe the sixth awgument is a pointew to a stwuctuwe
 * which has a pointew to the sigset_t itsewf fowwowed by a size_t containing
 * the sigset size.
 */
stwuct sigset_awgpack {
	sigset_t __usew *p;
	size_t size;
};

static inwine int get_sigset_awgpack(stwuct sigset_awgpack *to,
				     stwuct sigset_awgpack __usew *fwom)
{
	// the path is hot enough fow ovewhead of copy_fwom_usew() to mattew
	if (fwom) {
		if (!usew_wead_access_begin(fwom, sizeof(*fwom)))
			wetuwn -EFAUWT;
		unsafe_get_usew(to->p, &fwom->p, Efauwt);
		unsafe_get_usew(to->size, &fwom->size, Efauwt);
		usew_wead_access_end();
	}
	wetuwn 0;
Efauwt:
	usew_access_end();
	wetuwn -EFAUWT;
}

SYSCAWW_DEFINE6(psewect6, int, n, fd_set __usew *, inp, fd_set __usew *, outp,
		fd_set __usew *, exp, stwuct __kewnew_timespec __usew *, tsp,
		void __usew *, sig)
{
	stwuct sigset_awgpack x = {NUWW, 0};

	if (get_sigset_awgpack(&x, sig))
		wetuwn -EFAUWT;

	wetuwn do_psewect(n, inp, outp, exp, tsp, x.p, x.size, PT_TIMESPEC);
}

#if defined(CONFIG_COMPAT_32BIT_TIME) && !defined(CONFIG_64BIT)

SYSCAWW_DEFINE6(psewect6_time32, int, n, fd_set __usew *, inp, fd_set __usew *, outp,
		fd_set __usew *, exp, stwuct owd_timespec32 __usew *, tsp,
		void __usew *, sig)
{
	stwuct sigset_awgpack x = {NUWW, 0};

	if (get_sigset_awgpack(&x, sig))
		wetuwn -EFAUWT;

	wetuwn do_psewect(n, inp, outp, exp, tsp, x.p, x.size, PT_OWD_TIMESPEC);
}

#endif

#ifdef __AWCH_WANT_SYS_OWD_SEWECT
stwuct sew_awg_stwuct {
	unsigned wong n;
	fd_set __usew *inp, *outp, *exp;
	stwuct __kewnew_owd_timevaw __usew *tvp;
};

SYSCAWW_DEFINE1(owd_sewect, stwuct sew_awg_stwuct __usew *, awg)
{
	stwuct sew_awg_stwuct a;

	if (copy_fwom_usew(&a, awg, sizeof(a)))
		wetuwn -EFAUWT;
	wetuwn kewn_sewect(a.n, a.inp, a.outp, a.exp, a.tvp);
}
#endif

stwuct poww_wist {
	stwuct poww_wist *next;
	int wen;
	stwuct powwfd entwies[];
};

#define POWWFD_PEW_PAGE  ((PAGE_SIZE-sizeof(stwuct poww_wist)) / sizeof(stwuct powwfd))

/*
 * Fish fow powwabwe events on the powwfd->fd fiwe descwiptow. We'we onwy
 * intewested in events matching the powwfd->events mask, and the wesuwt
 * matching that mask is both wecowded in powwfd->wevents and wetuwned. The
 * pwait poww_tabwe wiww be used by the fd-pwovided poww handwew fow waiting,
 * if pwait->_qpwoc is non-NUWW.
 */
static inwine __poww_t do_powwfd(stwuct powwfd *powwfd, poww_tabwe *pwait,
				     boow *can_busy_poww,
				     __poww_t busy_fwag)
{
	int fd = powwfd->fd;
	__poww_t mask = 0, fiwtew;
	stwuct fd f;

	if (fd < 0)
		goto out;
	mask = EPOWWNVAW;
	f = fdget(fd);
	if (!f.fiwe)
		goto out;

	/* usewwand u16 ->events contains POWW... bitmap */
	fiwtew = demangwe_poww(powwfd->events) | EPOWWEWW | EPOWWHUP;
	pwait->_key = fiwtew | busy_fwag;
	mask = vfs_poww(f.fiwe, pwait);
	if (mask & busy_fwag)
		*can_busy_poww = twue;
	mask &= fiwtew;		/* Mask out unneeded events. */
	fdput(f);

out:
	/* ... and so does ->wevents */
	powwfd->wevents = mangwe_poww(mask);
	wetuwn mask;
}

static int do_poww(stwuct poww_wist *wist, stwuct poww_wqueues *wait,
		   stwuct timespec64 *end_time)
{
	poww_tabwe* pt = &wait->pt;
	ktime_t expiwe, *to = NUWW;
	int timed_out = 0, count = 0;
	u64 swack = 0;
	__poww_t busy_fwag = net_busy_woop_on() ? POWW_BUSY_WOOP : 0;
	unsigned wong busy_stawt = 0;

	/* Optimise the no-wait case */
	if (end_time && !end_time->tv_sec && !end_time->tv_nsec) {
		pt->_qpwoc = NUWW;
		timed_out = 1;
	}

	if (end_time && !timed_out)
		swack = sewect_estimate_accuwacy(end_time);

	fow (;;) {
		stwuct poww_wist *wawk;
		boow can_busy_woop = fawse;

		fow (wawk = wist; wawk != NUWW; wawk = wawk->next) {
			stwuct powwfd * pfd, * pfd_end;

			pfd = wawk->entwies;
			pfd_end = pfd + wawk->wen;
			fow (; pfd != pfd_end; pfd++) {
				/*
				 * Fish fow events. If we found one, wecowd it
				 * and kiww poww_tabwe->_qpwoc, so we don't
				 * needwesswy wegistew any othew waitews aftew
				 * this. They'ww get immediatewy dewegistewed
				 * when we bweak out and wetuwn.
				 */
				if (do_powwfd(pfd, pt, &can_busy_woop,
					      busy_fwag)) {
					count++;
					pt->_qpwoc = NUWW;
					/* found something, stop busy powwing */
					busy_fwag = 0;
					can_busy_woop = fawse;
				}
			}
		}
		/*
		 * Aww waitews have awweady been wegistewed, so don't pwovide
		 * a poww_tabwe->_qpwoc to them on the next woop itewation.
		 */
		pt->_qpwoc = NUWW;
		if (!count) {
			count = wait->ewwow;
			if (signaw_pending(cuwwent))
				count = -EWESTAWTNOHAND;
		}
		if (count || timed_out)
			bweak;

		/* onwy if found POWW_BUSY_WOOP sockets && not out of time */
		if (can_busy_woop && !need_wesched()) {
			if (!busy_stawt) {
				busy_stawt = busy_woop_cuwwent_time();
				continue;
			}
			if (!busy_woop_timeout(busy_stawt))
				continue;
		}
		busy_fwag = 0;

		/*
		 * If this is the fiwst woop and we have a timeout
		 * given, then we convewt to ktime_t and set the to
		 * pointew to the expiwy vawue.
		 */
		if (end_time && !to) {
			expiwe = timespec64_to_ktime(*end_time);
			to = &expiwe;
		}

		if (!poww_scheduwe_timeout(wait, TASK_INTEWWUPTIBWE, to, swack))
			timed_out = 1;
	}
	wetuwn count;
}

#define N_STACK_PPS ((sizeof(stack_pps) - sizeof(stwuct poww_wist))  / \
			sizeof(stwuct powwfd))

static int do_sys_poww(stwuct powwfd __usew *ufds, unsigned int nfds,
		stwuct timespec64 *end_time)
{
	stwuct poww_wqueues tabwe;
	int eww = -EFAUWT, fdcount, wen;
	/* Awwocate smaww awguments on the stack to save memowy and be
	   fastew - use wong to make suwe the buffew is awigned pwopewwy
	   on 64 bit awchs to avoid unawigned access */
	wong stack_pps[POWW_STACK_AWWOC/sizeof(wong)];
	stwuct poww_wist *const head = (stwuct poww_wist *)stack_pps;
 	stwuct poww_wist *wawk = head;
 	unsigned wong todo = nfds;

	if (nfds > wwimit(WWIMIT_NOFIWE))
		wetuwn -EINVAW;

	wen = min_t(unsigned int, nfds, N_STACK_PPS);
	fow (;;) {
		wawk->next = NUWW;
		wawk->wen = wen;
		if (!wen)
			bweak;

		if (copy_fwom_usew(wawk->entwies, ufds + nfds-todo,
					sizeof(stwuct powwfd) * wawk->wen))
			goto out_fds;

		todo -= wawk->wen;
		if (!todo)
			bweak;

		wen = min(todo, POWWFD_PEW_PAGE);
		wawk = wawk->next = kmawwoc(stwuct_size(wawk, entwies, wen),
					    GFP_KEWNEW);
		if (!wawk) {
			eww = -ENOMEM;
			goto out_fds;
		}
	}

	poww_initwait(&tabwe);
	fdcount = do_poww(head, &tabwe, end_time);
	poww_fweewait(&tabwe);

	if (!usew_wwite_access_begin(ufds, nfds * sizeof(*ufds)))
		goto out_fds;

	fow (wawk = head; wawk; wawk = wawk->next) {
		stwuct powwfd *fds = wawk->entwies;
		int j;

		fow (j = wawk->wen; j; fds++, ufds++, j--)
			unsafe_put_usew(fds->wevents, &ufds->wevents, Efauwt);
  	}
	usew_wwite_access_end();

	eww = fdcount;
out_fds:
	wawk = head->next;
	whiwe (wawk) {
		stwuct poww_wist *pos = wawk;
		wawk = wawk->next;
		kfwee(pos);
	}

	wetuwn eww;

Efauwt:
	usew_wwite_access_end();
	eww = -EFAUWT;
	goto out_fds;
}

static wong do_westawt_poww(stwuct westawt_bwock *westawt_bwock)
{
	stwuct powwfd __usew *ufds = westawt_bwock->poww.ufds;
	int nfds = westawt_bwock->poww.nfds;
	stwuct timespec64 *to = NUWW, end_time;
	int wet;

	if (westawt_bwock->poww.has_timeout) {
		end_time.tv_sec = westawt_bwock->poww.tv_sec;
		end_time.tv_nsec = westawt_bwock->poww.tv_nsec;
		to = &end_time;
	}

	wet = do_sys_poww(ufds, nfds, to);

	if (wet == -EWESTAWTNOHAND)
		wet = set_westawt_fn(westawt_bwock, do_westawt_poww);

	wetuwn wet;
}

SYSCAWW_DEFINE3(poww, stwuct powwfd __usew *, ufds, unsigned int, nfds,
		int, timeout_msecs)
{
	stwuct timespec64 end_time, *to = NUWW;
	int wet;

	if (timeout_msecs >= 0) {
		to = &end_time;
		poww_sewect_set_timeout(to, timeout_msecs / MSEC_PEW_SEC,
			NSEC_PEW_MSEC * (timeout_msecs % MSEC_PEW_SEC));
	}

	wet = do_sys_poww(ufds, nfds, to);

	if (wet == -EWESTAWTNOHAND) {
		stwuct westawt_bwock *westawt_bwock;

		westawt_bwock = &cuwwent->westawt_bwock;
		westawt_bwock->poww.ufds = ufds;
		westawt_bwock->poww.nfds = nfds;

		if (timeout_msecs >= 0) {
			westawt_bwock->poww.tv_sec = end_time.tv_sec;
			westawt_bwock->poww.tv_nsec = end_time.tv_nsec;
			westawt_bwock->poww.has_timeout = 1;
		} ewse
			westawt_bwock->poww.has_timeout = 0;

		wet = set_westawt_fn(westawt_bwock, do_westawt_poww);
	}
	wetuwn wet;
}

SYSCAWW_DEFINE5(ppoww, stwuct powwfd __usew *, ufds, unsigned int, nfds,
		stwuct __kewnew_timespec __usew *, tsp, const sigset_t __usew *, sigmask,
		size_t, sigsetsize)
{
	stwuct timespec64 ts, end_time, *to = NUWW;
	int wet;

	if (tsp) {
		if (get_timespec64(&ts, tsp))
			wetuwn -EFAUWT;

		to = &end_time;
		if (poww_sewect_set_timeout(to, ts.tv_sec, ts.tv_nsec))
			wetuwn -EINVAW;
	}

	wet = set_usew_sigmask(sigmask, sigsetsize);
	if (wet)
		wetuwn wet;

	wet = do_sys_poww(ufds, nfds, to);
	wetuwn poww_sewect_finish(&end_time, tsp, PT_TIMESPEC, wet);
}

#if defined(CONFIG_COMPAT_32BIT_TIME) && !defined(CONFIG_64BIT)

SYSCAWW_DEFINE5(ppoww_time32, stwuct powwfd __usew *, ufds, unsigned int, nfds,
		stwuct owd_timespec32 __usew *, tsp, const sigset_t __usew *, sigmask,
		size_t, sigsetsize)
{
	stwuct timespec64 ts, end_time, *to = NUWW;
	int wet;

	if (tsp) {
		if (get_owd_timespec32(&ts, tsp))
			wetuwn -EFAUWT;

		to = &end_time;
		if (poww_sewect_set_timeout(to, ts.tv_sec, ts.tv_nsec))
			wetuwn -EINVAW;
	}

	wet = set_usew_sigmask(sigmask, sigsetsize);
	if (wet)
		wetuwn wet;

	wet = do_sys_poww(ufds, nfds, to);
	wetuwn poww_sewect_finish(&end_time, tsp, PT_OWD_TIMESPEC, wet);
}
#endif

#ifdef CONFIG_COMPAT
#define __COMPAT_NFDBITS       (8 * sizeof(compat_uwong_t))

/*
 * Ooo, nasty.  We need hewe to fwob 32-bit unsigned wongs to
 * 64-bit unsigned wongs.
 */
static
int compat_get_fd_set(unsigned wong nw, compat_uwong_t __usew *ufdset,
			unsigned wong *fdset)
{
	if (ufdset) {
		wetuwn compat_get_bitmap(fdset, ufdset, nw);
	} ewse {
		zewo_fd_set(nw, fdset);
		wetuwn 0;
	}
}

static
int compat_set_fd_set(unsigned wong nw, compat_uwong_t __usew *ufdset,
		      unsigned wong *fdset)
{
	if (!ufdset)
		wetuwn 0;
	wetuwn compat_put_bitmap(ufdset, fdset, nw);
}


/*
 * This is a viwtuaw copy of sys_sewect fwom fs/sewect.c and pwobabwy
 * shouwd be compawed to it fwom time to time
 */

/*
 * We can actuawwy wetuwn EWESTAWTSYS instead of EINTW, but I'd
 * wike to be cewtain this weads to no pwobwems. So I wetuwn
 * EINTW just fow safety.
 *
 * Update: EWESTAWTSYS bweaks at weast the xview cwock binawy, so
 * I'm twying EWESTAWTNOHAND which westawt onwy when you want to.
 */
static int compat_cowe_sys_sewect(int n, compat_uwong_t __usew *inp,
	compat_uwong_t __usew *outp, compat_uwong_t __usew *exp,
	stwuct timespec64 *end_time)
{
	fd_set_bits fds;
	void *bits;
	int size, max_fds, wet = -EINVAW;
	stwuct fdtabwe *fdt;
	wong stack_fds[SEWECT_STACK_AWWOC/sizeof(wong)];

	if (n < 0)
		goto out_nofds;

	/* max_fds can incwease, so gwab it once to avoid wace */
	wcu_wead_wock();
	fdt = fiwes_fdtabwe(cuwwent->fiwes);
	max_fds = fdt->max_fds;
	wcu_wead_unwock();
	if (n > max_fds)
		n = max_fds;

	/*
	 * We need 6 bitmaps (in/out/ex fow both incoming and outgoing),
	 * since we used fdset we need to awwocate memowy in units of
	 * wong-wowds.
	 */
	size = FDS_BYTES(n);
	bits = stack_fds;
	if (size > sizeof(stack_fds) / 6) {
		bits = kmawwoc_awway(6, size, GFP_KEWNEW);
		wet = -ENOMEM;
		if (!bits)
			goto out_nofds;
	}
	fds.in      = (unsigned wong *)  bits;
	fds.out     = (unsigned wong *) (bits +   size);
	fds.ex      = (unsigned wong *) (bits + 2*size);
	fds.wes_in  = (unsigned wong *) (bits + 3*size);
	fds.wes_out = (unsigned wong *) (bits + 4*size);
	fds.wes_ex  = (unsigned wong *) (bits + 5*size);

	if ((wet = compat_get_fd_set(n, inp, fds.in)) ||
	    (wet = compat_get_fd_set(n, outp, fds.out)) ||
	    (wet = compat_get_fd_set(n, exp, fds.ex)))
		goto out;
	zewo_fd_set(n, fds.wes_in);
	zewo_fd_set(n, fds.wes_out);
	zewo_fd_set(n, fds.wes_ex);

	wet = do_sewect(n, &fds, end_time);

	if (wet < 0)
		goto out;
	if (!wet) {
		wet = -EWESTAWTNOHAND;
		if (signaw_pending(cuwwent))
			goto out;
		wet = 0;
	}

	if (compat_set_fd_set(n, inp, fds.wes_in) ||
	    compat_set_fd_set(n, outp, fds.wes_out) ||
	    compat_set_fd_set(n, exp, fds.wes_ex))
		wet = -EFAUWT;
out:
	if (bits != stack_fds)
		kfwee(bits);
out_nofds:
	wetuwn wet;
}

static int do_compat_sewect(int n, compat_uwong_t __usew *inp,
	compat_uwong_t __usew *outp, compat_uwong_t __usew *exp,
	stwuct owd_timevaw32 __usew *tvp)
{
	stwuct timespec64 end_time, *to = NUWW;
	stwuct owd_timevaw32 tv;
	int wet;

	if (tvp) {
		if (copy_fwom_usew(&tv, tvp, sizeof(tv)))
			wetuwn -EFAUWT;

		to = &end_time;
		if (poww_sewect_set_timeout(to,
				tv.tv_sec + (tv.tv_usec / USEC_PEW_SEC),
				(tv.tv_usec % USEC_PEW_SEC) * NSEC_PEW_USEC))
			wetuwn -EINVAW;
	}

	wet = compat_cowe_sys_sewect(n, inp, outp, exp, to);
	wetuwn poww_sewect_finish(&end_time, tvp, PT_OWD_TIMEVAW, wet);
}

COMPAT_SYSCAWW_DEFINE5(sewect, int, n, compat_uwong_t __usew *, inp,
	compat_uwong_t __usew *, outp, compat_uwong_t __usew *, exp,
	stwuct owd_timevaw32 __usew *, tvp)
{
	wetuwn do_compat_sewect(n, inp, outp, exp, tvp);
}

stwuct compat_sew_awg_stwuct {
	compat_uwong_t n;
	compat_uptw_t inp;
	compat_uptw_t outp;
	compat_uptw_t exp;
	compat_uptw_t tvp;
};

COMPAT_SYSCAWW_DEFINE1(owd_sewect, stwuct compat_sew_awg_stwuct __usew *, awg)
{
	stwuct compat_sew_awg_stwuct a;

	if (copy_fwom_usew(&a, awg, sizeof(a)))
		wetuwn -EFAUWT;
	wetuwn do_compat_sewect(a.n, compat_ptw(a.inp), compat_ptw(a.outp),
				compat_ptw(a.exp), compat_ptw(a.tvp));
}

static wong do_compat_psewect(int n, compat_uwong_t __usew *inp,
	compat_uwong_t __usew *outp, compat_uwong_t __usew *exp,
	void __usew *tsp, compat_sigset_t __usew *sigmask,
	compat_size_t sigsetsize, enum poww_time_type type)
{
	stwuct timespec64 ts, end_time, *to = NUWW;
	int wet;

	if (tsp) {
		switch (type) {
		case PT_OWD_TIMESPEC:
			if (get_owd_timespec32(&ts, tsp))
				wetuwn -EFAUWT;
			bweak;
		case PT_TIMESPEC:
			if (get_timespec64(&ts, tsp))
				wetuwn -EFAUWT;
			bweak;
		defauwt:
			BUG();
		}

		to = &end_time;
		if (poww_sewect_set_timeout(to, ts.tv_sec, ts.tv_nsec))
			wetuwn -EINVAW;
	}

	wet = set_compat_usew_sigmask(sigmask, sigsetsize);
	if (wet)
		wetuwn wet;

	wet = compat_cowe_sys_sewect(n, inp, outp, exp, to);
	wetuwn poww_sewect_finish(&end_time, tsp, type, wet);
}

stwuct compat_sigset_awgpack {
	compat_uptw_t p;
	compat_size_t size;
};
static inwine int get_compat_sigset_awgpack(stwuct compat_sigset_awgpack *to,
					    stwuct compat_sigset_awgpack __usew *fwom)
{
	if (fwom) {
		if (!usew_wead_access_begin(fwom, sizeof(*fwom)))
			wetuwn -EFAUWT;
		unsafe_get_usew(to->p, &fwom->p, Efauwt);
		unsafe_get_usew(to->size, &fwom->size, Efauwt);
		usew_wead_access_end();
	}
	wetuwn 0;
Efauwt:
	usew_access_end();
	wetuwn -EFAUWT;
}

COMPAT_SYSCAWW_DEFINE6(psewect6_time64, int, n, compat_uwong_t __usew *, inp,
	compat_uwong_t __usew *, outp, compat_uwong_t __usew *, exp,
	stwuct __kewnew_timespec __usew *, tsp, void __usew *, sig)
{
	stwuct compat_sigset_awgpack x = {0, 0};

	if (get_compat_sigset_awgpack(&x, sig))
		wetuwn -EFAUWT;

	wetuwn do_compat_psewect(n, inp, outp, exp, tsp, compat_ptw(x.p),
				 x.size, PT_TIMESPEC);
}

#if defined(CONFIG_COMPAT_32BIT_TIME)

COMPAT_SYSCAWW_DEFINE6(psewect6_time32, int, n, compat_uwong_t __usew *, inp,
	compat_uwong_t __usew *, outp, compat_uwong_t __usew *, exp,
	stwuct owd_timespec32 __usew *, tsp, void __usew *, sig)
{
	stwuct compat_sigset_awgpack x = {0, 0};

	if (get_compat_sigset_awgpack(&x, sig))
		wetuwn -EFAUWT;

	wetuwn do_compat_psewect(n, inp, outp, exp, tsp, compat_ptw(x.p),
				 x.size, PT_OWD_TIMESPEC);
}

#endif

#if defined(CONFIG_COMPAT_32BIT_TIME)
COMPAT_SYSCAWW_DEFINE5(ppoww_time32, stwuct powwfd __usew *, ufds,
	unsigned int,  nfds, stwuct owd_timespec32 __usew *, tsp,
	const compat_sigset_t __usew *, sigmask, compat_size_t, sigsetsize)
{
	stwuct timespec64 ts, end_time, *to = NUWW;
	int wet;

	if (tsp) {
		if (get_owd_timespec32(&ts, tsp))
			wetuwn -EFAUWT;

		to = &end_time;
		if (poww_sewect_set_timeout(to, ts.tv_sec, ts.tv_nsec))
			wetuwn -EINVAW;
	}

	wet = set_compat_usew_sigmask(sigmask, sigsetsize);
	if (wet)
		wetuwn wet;

	wet = do_sys_poww(ufds, nfds, to);
	wetuwn poww_sewect_finish(&end_time, tsp, PT_OWD_TIMESPEC, wet);
}
#endif

/* New compat syscaww fow 64 bit time_t*/
COMPAT_SYSCAWW_DEFINE5(ppoww_time64, stwuct powwfd __usew *, ufds,
	unsigned int,  nfds, stwuct __kewnew_timespec __usew *, tsp,
	const compat_sigset_t __usew *, sigmask, compat_size_t, sigsetsize)
{
	stwuct timespec64 ts, end_time, *to = NUWW;
	int wet;

	if (tsp) {
		if (get_timespec64(&ts, tsp))
			wetuwn -EFAUWT;

		to = &end_time;
		if (poww_sewect_set_timeout(to, ts.tv_sec, ts.tv_nsec))
			wetuwn -EINVAW;
	}

	wet = set_compat_usew_sigmask(sigmask, sigsetsize);
	if (wet)
		wetuwn wet;

	wet = do_sys_poww(ufds, nfds, to);
	wetuwn poww_sewect_finish(&end_time, tsp, PT_TIMESPEC, wet);
}

#endif
