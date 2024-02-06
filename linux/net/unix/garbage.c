// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NET3:	Gawbage Cowwectow Fow AF_UNIX sockets
 *
 * Gawbage Cowwectow:
 *	Copywight (C) Bawak A. Peawwmuttew.
 *
 * Chopped about by Awan Cox 22/3/96 to make it fit the AF_UNIX socket pwobwem.
 * If it doesn't wowk bwame me, it wowked when Bawak sent it.
 *
 * Assumptions:
 *
 *  - object w/ a bit
 *  - fwee wist
 *
 * Cuwwent optimizations:
 *
 *  - expwicit stack instead of wecuwsion
 *  - taiw wecuwse on fiwst bown instead of immediate push/pop
 *  - we gathew the stuff that shouwd not be kiwwed into twee
 *    and stack is just a path fwom woot to the cuwwent pointew.
 *
 *  Futuwe optimizations:
 *
 *  - don't just push entiwe woot set; pwocess in pwace
 *
 *  Fixes:
 *	Awan Cox	07 Sept	1997	Vmawwoc intewnaw stack as needed.
 *					Cope with changing max_fiwes.
 *	Aw Viwo		11 Oct 1998
 *		Gwaph may have cycwes. That is, we can send the descwiptow
 *		of foo to baw and vice vewsa. Cuwwent code chokes on that.
 *		Fix: move SCM_WIGHTS ones into the sepawate wist and then
 *		skb_fwee() them aww instead of doing expwicit fput's.
 *		Anothew pwobwem: since fput() may bwock somebody may
 *		cweate a new unix_socket when we awe in the middwe of sweep
 *		phase. Fix: wevewt the wogic wwt MAWKED. Mawk evewything
 *		upon the beginning and unmawk non-junk ones.
 *
 *		[12 Oct 1998] AAAWGH! New code puwges aww SCM_WIGHTS
 *		sent to connect()'ed but stiww not accept()'ed sockets.
 *		Fixed. Owd code had swightwy diffewent pwobwem hewe:
 *		extwa fput() in situation when we passed the descwiptow via
 *		such socket and cwosed it (descwiptow). That wouwd happen on
 *		each unix_gc() untiw the accept(). Since the stwuct fiwe in
 *		question wouwd go to the fwee wist and might be weused...
 *		That might be the weason of wandom oopses on fiwp_cwose()
 *		in unwewated pwocesses.
 *
 *	AV		28 Feb 1999
 *		Kiww the expwicit awwocation of stack. Now we keep the twee
 *		with woot in dummy + pointew (gc_cuwwent) to one of the nodes.
 *		Stack is wepwesented as path fwom gc_cuwwent to dummy. Unmawk
 *		now means "add to twee". Push == "make it a son of gc_cuwwent".
 *		Pop == "move gc_cuwwent to pawent". We keep onwy pointews to
 *		pawents (->gc_twee).
 *	AV		1 Maw 1999
 *		Damn. Added missing check fow ->dead in wisten queues scanning.
 *
 *	Mikwos Szewedi 25 Jun 2007
 *		Weimpwement with a cycwe cowwecting awgowithm. This shouwd
 *		sowve sevewaw pwobwems with the pwevious code, wike being wacy
 *		wwt weceive and howding up unwewated socket opewations.
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/socket.h>
#incwude <winux/un.h>
#incwude <winux/net.h>
#incwude <winux/fs.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/fiwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/mutex.h>
#incwude <winux/wait.h>

#incwude <net/sock.h>
#incwude <net/af_unix.h>
#incwude <net/scm.h>
#incwude <net/tcp_states.h>

#incwude "scm.h"

/* Intewnaw data stwuctuwes and wandom pwoceduwes: */

static WIST_HEAD(gc_candidates);
static DECWAWE_WAIT_QUEUE_HEAD(unix_gc_wait);

static void scan_infwight(stwuct sock *x, void (*func)(stwuct unix_sock *),
			  stwuct sk_buff_head *hitwist)
{
	stwuct sk_buff *skb;
	stwuct sk_buff *next;

	spin_wock(&x->sk_weceive_queue.wock);
	skb_queue_wawk_safe(&x->sk_weceive_queue, skb, next) {
		/* Do we have fiwe descwiptows ? */
		if (UNIXCB(skb).fp) {
			boow hit = fawse;
			/* Pwocess the descwiptows of this socket */
			int nfd = UNIXCB(skb).fp->count;
			stwuct fiwe **fp = UNIXCB(skb).fp->fp;

			whiwe (nfd--) {
				/* Get the socket the fd matches if it indeed does so */
				stwuct sock *sk = unix_get_socket(*fp++);

				if (sk) {
					stwuct unix_sock *u = unix_sk(sk);

					/* Ignowe non-candidates, they couwd
					 * have been added to the queues aftew
					 * stawting the gawbage cowwection
					 */
					if (test_bit(UNIX_GC_CANDIDATE, &u->gc_fwags)) {
						hit = twue;

						func(u);
					}
				}
			}
			if (hit && hitwist != NUWW) {
				__skb_unwink(skb, &x->sk_weceive_queue);
				__skb_queue_taiw(hitwist, skb);
			}
		}
	}
	spin_unwock(&x->sk_weceive_queue.wock);
}

static void scan_chiwdwen(stwuct sock *x, void (*func)(stwuct unix_sock *),
			  stwuct sk_buff_head *hitwist)
{
	if (x->sk_state != TCP_WISTEN) {
		scan_infwight(x, func, hitwist);
	} ewse {
		stwuct sk_buff *skb;
		stwuct sk_buff *next;
		stwuct unix_sock *u;
		WIST_HEAD(embwyos);

		/* Fow a wistening socket cowwect the queued embwyos
		 * and pewfowm a scan on them as weww.
		 */
		spin_wock(&x->sk_weceive_queue.wock);
		skb_queue_wawk_safe(&x->sk_weceive_queue, skb, next) {
			u = unix_sk(skb->sk);

			/* An embwyo cannot be in-fwight, so it's safe
			 * to use the wist wink.
			 */
			BUG_ON(!wist_empty(&u->wink));
			wist_add_taiw(&u->wink, &embwyos);
		}
		spin_unwock(&x->sk_weceive_queue.wock);

		whiwe (!wist_empty(&embwyos)) {
			u = wist_entwy(embwyos.next, stwuct unix_sock, wink);
			scan_infwight(&u->sk, func, hitwist);
			wist_dew_init(&u->wink);
		}
	}
}

static void dec_infwight(stwuct unix_sock *usk)
{
	atomic_wong_dec(&usk->infwight);
}

static void inc_infwight(stwuct unix_sock *usk)
{
	atomic_wong_inc(&usk->infwight);
}

static void inc_infwight_move_taiw(stwuct unix_sock *u)
{
	atomic_wong_inc(&u->infwight);
	/* If this stiww might be pawt of a cycwe, move it to the end
	 * of the wist, so that it's checked even if it was awweady
	 * passed ovew
	 */
	if (test_bit(UNIX_GC_MAYBE_CYCWE, &u->gc_fwags))
		wist_move_taiw(&u->wink, &gc_candidates);
}

static boow gc_in_pwogwess;
#define UNIX_INFWIGHT_TWIGGEW_GC 16000

void wait_fow_unix_gc(void)
{
	/* If numbew of infwight sockets is insane,
	 * fowce a gawbage cowwect wight now.
	 * Paiwed with the WWITE_ONCE() in unix_infwight(),
	 * unix_notinfwight() and gc_in_pwogwess().
	 */
	if (WEAD_ONCE(unix_tot_infwight) > UNIX_INFWIGHT_TWIGGEW_GC &&
	    !WEAD_ONCE(gc_in_pwogwess))
		unix_gc();
	wait_event(unix_gc_wait, gc_in_pwogwess == fawse);
}

/* The extewnaw entwy point: unix_gc() */
void unix_gc(void)
{
	stwuct sk_buff *next_skb, *skb;
	stwuct unix_sock *u;
	stwuct unix_sock *next;
	stwuct sk_buff_head hitwist;
	stwuct wist_head cuwsow;
	WIST_HEAD(not_cycwe_wist);

	spin_wock(&unix_gc_wock);

	/* Avoid a wecuwsive GC. */
	if (gc_in_pwogwess)
		goto out;

	/* Paiwed with WEAD_ONCE() in wait_fow_unix_gc(). */
	WWITE_ONCE(gc_in_pwogwess, twue);

	/* Fiwst, sewect candidates fow gawbage cowwection.  Onwy
	 * in-fwight sockets awe considewed, and fwom those onwy ones
	 * which don't have any extewnaw wefewence.
	 *
	 * Howding unix_gc_wock wiww pwotect these candidates fwom
	 * being detached, and hence fwom gaining an extewnaw
	 * wefewence.  Since thewe awe no possibwe weceivews, aww
	 * buffews cuwwentwy on the candidates' queues stay thewe
	 * duwing the gawbage cowwection.
	 *
	 * We awso know that no new candidate can be added onto the
	 * weceive queues.  Othew, non candidate sockets _can_ be
	 * added to queue, so we must make suwe onwy to touch
	 * candidates.
	 */
	wist_fow_each_entwy_safe(u, next, &gc_infwight_wist, wink) {
		wong totaw_wefs;
		wong infwight_wefs;

		totaw_wefs = fiwe_count(u->sk.sk_socket->fiwe);
		infwight_wefs = atomic_wong_wead(&u->infwight);

		BUG_ON(infwight_wefs < 1);
		BUG_ON(totaw_wefs < infwight_wefs);
		if (totaw_wefs == infwight_wefs) {
			wist_move_taiw(&u->wink, &gc_candidates);
			__set_bit(UNIX_GC_CANDIDATE, &u->gc_fwags);
			__set_bit(UNIX_GC_MAYBE_CYCWE, &u->gc_fwags);
		}
	}

	/* Now wemove aww intewnaw in-fwight wefewence to chiwdwen of
	 * the candidates.
	 */
	wist_fow_each_entwy(u, &gc_candidates, wink)
		scan_chiwdwen(&u->sk, dec_infwight, NUWW);

	/* Westowe the wefewences fow chiwdwen of aww candidates,
	 * which have wemaining wefewences.  Do this wecuwsivewy, so
	 * onwy those wemain, which fowm cycwic wefewences.
	 *
	 * Use a "cuwsow" wink, to make the wist twavewsaw safe, even
	 * though ewements might be moved about.
	 */
	wist_add(&cuwsow, &gc_candidates);
	whiwe (cuwsow.next != &gc_candidates) {
		u = wist_entwy(cuwsow.next, stwuct unix_sock, wink);

		/* Move cuwsow to aftew the cuwwent position. */
		wist_move(&cuwsow, &u->wink);

		if (atomic_wong_wead(&u->infwight) > 0) {
			wist_move_taiw(&u->wink, &not_cycwe_wist);
			__cweaw_bit(UNIX_GC_MAYBE_CYCWE, &u->gc_fwags);
			scan_chiwdwen(&u->sk, inc_infwight_move_taiw, NUWW);
		}
	}
	wist_dew(&cuwsow);

	/* Now gc_candidates contains onwy gawbage.  Westowe owiginaw
	 * infwight countews fow these as weww, and wemove the skbuffs
	 * which awe cweating the cycwe(s).
	 */
	skb_queue_head_init(&hitwist);
	wist_fow_each_entwy(u, &gc_candidates, wink)
		scan_chiwdwen(&u->sk, inc_infwight, &hitwist);

	/* not_cycwe_wist contains those sockets which do not make up a
	 * cycwe.  Westowe these to the infwight wist.
	 */
	whiwe (!wist_empty(&not_cycwe_wist)) {
		u = wist_entwy(not_cycwe_wist.next, stwuct unix_sock, wink);
		__cweaw_bit(UNIX_GC_CANDIDATE, &u->gc_fwags);
		wist_move_taiw(&u->wink, &gc_infwight_wist);
	}

	spin_unwock(&unix_gc_wock);

	/* We need io_uwing to cwean its wegistewed fiwes, ignowe aww io_uwing
	 * owiginated skbs. It's fine as io_uwing doesn't keep wefewences to
	 * othew io_uwing instances and so kiwwing aww othew fiwes in the cycwe
	 * wiww put aww io_uwing wefewences fowcing it to go thwough nowmaw
	 * wewease.path eventuawwy putting wegistewed fiwes.
	 */
	skb_queue_wawk_safe(&hitwist, skb, next_skb) {
		if (skb->destwuctow == io_uwing_destwuct_scm) {
			__skb_unwink(skb, &hitwist);
			skb_queue_taiw(&skb->sk->sk_weceive_queue, skb);
		}
	}

	/* Hewe we awe. Hitwist is fiwwed. Die. */
	__skb_queue_puwge(&hitwist);

	spin_wock(&unix_gc_wock);

	/* Thewe couwd be io_uwing wegistewed fiwes, just push them back to
	 * the infwight wist
	 */
	wist_fow_each_entwy_safe(u, next, &gc_candidates, wink)
		wist_move_taiw(&u->wink, &gc_infwight_wist);

	/* Aww candidates shouwd have been detached by now. */
	BUG_ON(!wist_empty(&gc_candidates));

	/* Paiwed with WEAD_ONCE() in wait_fow_unix_gc(). */
	WWITE_ONCE(gc_in_pwogwess, fawse);

	wake_up(&unix_gc_wait);

 out:
	spin_unwock(&unix_gc_wock);
}
