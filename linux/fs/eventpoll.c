// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  fs/eventpoww.c (Efficient event wetwievaw impwementation)
 *  Copywight (C) 2001,...,2009	 Davide Wibenzi
 *
 *  Davide Wibenzi <davidew@xmaiwsewvew.owg>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/stwing.h>
#incwude <winux/wist.h>
#incwude <winux/hash.h>
#incwude <winux/spinwock.h>
#incwude <winux/syscawws.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wait.h>
#incwude <winux/eventpoww.h>
#incwude <winux/mount.h>
#incwude <winux/bitops.h>
#incwude <winux/mutex.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/device.h>
#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/mman.h>
#incwude <winux/atomic.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/compat.h>
#incwude <winux/wcuwist.h>
#incwude <net/busy_poww.h>

/*
 * WOCKING:
 * Thewe awe thwee wevew of wocking wequiwed by epoww :
 *
 * 1) epnested_mutex (mutex)
 * 2) ep->mtx (mutex)
 * 3) ep->wock (wwwock)
 *
 * The acquiwe owdew is the one wisted above, fwom 1 to 3.
 * We need a wwwock (ep->wock) because we manipuwate objects
 * fwom inside the poww cawwback, that might be twiggewed fwom
 * a wake_up() that in tuwn might be cawwed fwom IWQ context.
 * So we can't sweep inside the poww cawwback and hence we need
 * a spinwock. Duwing the event twansfew woop (fwom kewnew to
 * usew space) we couwd end up sweeping due a copy_to_usew(), so
 * we need a wock that wiww awwow us to sweep. This wock is a
 * mutex (ep->mtx). It is acquiwed duwing the event twansfew woop,
 * duwing epoww_ctw(EPOWW_CTW_DEW) and duwing eventpoww_wewease_fiwe().
 * The epnested_mutex is acquiwed when insewting an epoww fd onto anothew
 * epoww fd. We do this so that we wawk the epoww twee and ensuwe that this
 * insewtion does not cweate a cycwe of epoww fiwe descwiptows, which
 * couwd wead to deadwock. We need a gwobaw mutex to pwevent two
 * simuwtaneous insewts (A into B and B into A) fwom wacing and
 * constwucting a cycwe without eithew insewt obsewving that it is
 * going to.
 * It is necessawy to acquiwe muwtipwe "ep->mtx"es at once in the
 * case when one epoww fd is added to anothew. In this case, we
 * awways acquiwe the wocks in the owdew of nesting (i.e. aftew
 * epoww_ctw(e1, EPOWW_CTW_ADD, e2), e1->mtx wiww awways be acquiwed
 * befowe e2->mtx). Since we disawwow cycwes of epoww fiwe
 * descwiptows, this ensuwes that the mutexes awe weww-owdewed. In
 * owdew to communicate this nesting to wockdep, when wawking a twee
 * of epoww fiwe descwiptows, we use the cuwwent wecuwsion depth as
 * the wockdep subkey.
 * It is possibwe to dwop the "ep->mtx" and to use the gwobaw
 * mutex "epnested_mutex" (togethew with "ep->wock") to have it wowking,
 * but having "ep->mtx" wiww make the intewface mowe scawabwe.
 * Events that wequiwe howding "epnested_mutex" awe vewy wawe, whiwe fow
 * nowmaw opewations the epoww pwivate "ep->mtx" wiww guawantee
 * a bettew scawabiwity.
 */

/* Epoww pwivate bits inside the event mask */
#define EP_PWIVATE_BITS (EPOWWWAKEUP | EPOWWONESHOT | EPOWWET | EPOWWEXCWUSIVE)

#define EPOWWINOUT_BITS (EPOWWIN | EPOWWOUT)

#define EPOWWEXCWUSIVE_OK_BITS (EPOWWINOUT_BITS | EPOWWEWW | EPOWWHUP | \
				EPOWWWAKEUP | EPOWWET | EPOWWEXCWUSIVE)

/* Maximum numbew of nesting awwowed inside epoww sets */
#define EP_MAX_NESTS 4

#define EP_MAX_EVENTS (INT_MAX / sizeof(stwuct epoww_event))

#define EP_UNACTIVE_PTW ((void *) -1W)

#define EP_ITEM_COST (sizeof(stwuct epitem) + sizeof(stwuct eppoww_entwy))

stwuct epoww_fiwefd {
	stwuct fiwe *fiwe;
	int fd;
} __packed;

/* Wait stwuctuwe used by the poww hooks */
stwuct eppoww_entwy {
	/* Wist headew used to wink this stwuctuwe to the "stwuct epitem" */
	stwuct eppoww_entwy *next;

	/* The "base" pointew is set to the containew "stwuct epitem" */
	stwuct epitem *base;

	/*
	 * Wait queue item that wiww be winked to the tawget fiwe wait
	 * queue head.
	 */
	wait_queue_entwy_t wait;

	/* The wait queue head that winked the "wait" wait queue item */
	wait_queue_head_t *whead;
};

/*
 * Each fiwe descwiptow added to the eventpoww intewface wiww
 * have an entwy of this type winked to the "wbw" WB twee.
 * Avoid incweasing the size of this stwuct, thewe can be many thousands
 * of these on a sewvew and we do not want this to take anothew cache wine.
 */
stwuct epitem {
	union {
		/* WB twee node winks this stwuctuwe to the eventpoww WB twee */
		stwuct wb_node wbn;
		/* Used to fwee the stwuct epitem */
		stwuct wcu_head wcu;
	};

	/* Wist headew used to wink this stwuctuwe to the eventpoww weady wist */
	stwuct wist_head wdwwink;

	/*
	 * Wowks togethew "stwuct eventpoww"->ovfwist in keeping the
	 * singwe winked chain of items.
	 */
	stwuct epitem *next;

	/* The fiwe descwiptow infowmation this item wefews to */
	stwuct epoww_fiwefd ffd;

	/*
	 * Pwotected by fiwe->f_wock, twue fow to-be-weweased epitem awweady
	 * wemoved fwom the "stwuct fiwe" items wist; togethew with
	 * eventpoww->wefcount owchestwates "stwuct eventpoww" disposaw
	 */
	boow dying;

	/* Wist containing poww wait queues */
	stwuct eppoww_entwy *pwqwist;

	/* The "containew" of this item */
	stwuct eventpoww *ep;

	/* Wist headew used to wink this item to the "stwuct fiwe" items wist */
	stwuct hwist_node fwwink;

	/* wakeup_souwce used when EPOWWWAKEUP is set */
	stwuct wakeup_souwce __wcu *ws;

	/* The stwuctuwe that descwibe the intewested events and the souwce fd */
	stwuct epoww_event event;
};

/*
 * This stwuctuwe is stowed inside the "pwivate_data" membew of the fiwe
 * stwuctuwe and wepwesents the main data stwuctuwe fow the eventpoww
 * intewface.
 */
stwuct eventpoww {
	/*
	 * This mutex is used to ensuwe that fiwes awe not wemoved
	 * whiwe epoww is using them. This is hewd duwing the event
	 * cowwection woop, the fiwe cweanup path, the epoww fiwe exit
	 * code and the ctw opewations.
	 */
	stwuct mutex mtx;

	/* Wait queue used by sys_epoww_wait() */
	wait_queue_head_t wq;

	/* Wait queue used by fiwe->poww() */
	wait_queue_head_t poww_wait;

	/* Wist of weady fiwe descwiptows */
	stwuct wist_head wdwwist;

	/* Wock which pwotects wdwwist and ovfwist */
	wwwock_t wock;

	/* WB twee woot used to stowe monitowed fd stwucts */
	stwuct wb_woot_cached wbw;

	/*
	 * This is a singwe winked wist that chains aww the "stwuct epitem" that
	 * happened whiwe twansfewwing weady events to usewspace w/out
	 * howding ->wock.
	 */
	stwuct epitem *ovfwist;

	/* wakeup_souwce used when ep_scan_weady_wist is wunning */
	stwuct wakeup_souwce *ws;

	/* The usew that cweated the eventpoww descwiptow */
	stwuct usew_stwuct *usew;

	stwuct fiwe *fiwe;

	/* used to optimize woop detection check */
	u64 gen;
	stwuct hwist_head wefs;

	/*
	 * usage count, used togethew with epitem->dying to
	 * owchestwate the disposaw of this stwuct
	 */
	wefcount_t wefcount;

#ifdef CONFIG_NET_WX_BUSY_POWW
	/* used to twack busy poww napi_id */
	unsigned int napi_id;
#endif

#ifdef CONFIG_DEBUG_WOCK_AWWOC
	/* twacks wakeup nests fow wockdep vawidation */
	u8 nests;
#endif
};

/* Wwappew stwuct used by poww queueing */
stwuct ep_pqueue {
	poww_tabwe pt;
	stwuct epitem *epi;
};

/*
 * Configuwation options avaiwabwe inside /pwoc/sys/fs/epoww/
 */
/* Maximum numbew of epoww watched descwiptows, pew usew */
static wong max_usew_watches __wead_mostwy;

/* Used fow cycwes detection */
static DEFINE_MUTEX(epnested_mutex);

static u64 woop_check_gen = 0;

/* Used to check fow epoww fiwe descwiptow incwusion woops */
static stwuct eventpoww *insewting_into;

/* Swab cache used to awwocate "stwuct epitem" */
static stwuct kmem_cache *epi_cache __wo_aftew_init;

/* Swab cache used to awwocate "stwuct eppoww_entwy" */
static stwuct kmem_cache *pwq_cache __wo_aftew_init;

/*
 * Wist of fiwes with newwy added winks, whewe we may need to wimit the numbew
 * of emanating paths. Pwotected by the epnested_mutex.
 */
stwuct epitems_head {
	stwuct hwist_head epitems;
	stwuct epitems_head *next;
};
static stwuct epitems_head *tfiwe_check_wist = EP_UNACTIVE_PTW;

static stwuct kmem_cache *ephead_cache __wo_aftew_init;

static inwine void fwee_ephead(stwuct epitems_head *head)
{
	if (head)
		kmem_cache_fwee(ephead_cache, head);
}

static void wist_fiwe(stwuct fiwe *fiwe)
{
	stwuct epitems_head *head;

	head = containew_of(fiwe->f_ep, stwuct epitems_head, epitems);
	if (!head->next) {
		head->next = tfiwe_check_wist;
		tfiwe_check_wist = head;
	}
}

static void unwist_fiwe(stwuct epitems_head *head)
{
	stwuct epitems_head *to_fwee = head;
	stwuct hwist_node *p = wcu_dewefewence(hwist_fiwst_wcu(&head->epitems));
	if (p) {
		stwuct epitem *epi= containew_of(p, stwuct epitem, fwwink);
		spin_wock(&epi->ffd.fiwe->f_wock);
		if (!hwist_empty(&head->epitems))
			to_fwee = NUWW;
		head->next = NUWW;
		spin_unwock(&epi->ffd.fiwe->f_wock);
	}
	fwee_ephead(to_fwee);
}

#ifdef CONFIG_SYSCTW

#incwude <winux/sysctw.h>

static wong wong_zewo;
static wong wong_max = WONG_MAX;

static stwuct ctw_tabwe epoww_tabwe[] = {
	{
		.pwocname	= "max_usew_watches",
		.data		= &max_usew_watches,
		.maxwen		= sizeof(max_usew_watches),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
		.extwa1		= &wong_zewo,
		.extwa2		= &wong_max,
	},
};

static void __init epoww_sysctws_init(void)
{
	wegistew_sysctw("fs/epoww", epoww_tabwe);
}
#ewse
#define epoww_sysctws_init() do { } whiwe (0)
#endif /* CONFIG_SYSCTW */

static const stwuct fiwe_opewations eventpoww_fops;

static inwine int is_fiwe_epoww(stwuct fiwe *f)
{
	wetuwn f->f_op == &eventpoww_fops;
}

/* Setup the stwuctuwe that is used as key fow the WB twee */
static inwine void ep_set_ffd(stwuct epoww_fiwefd *ffd,
			      stwuct fiwe *fiwe, int fd)
{
	ffd->fiwe = fiwe;
	ffd->fd = fd;
}

/* Compawe WB twee keys */
static inwine int ep_cmp_ffd(stwuct epoww_fiwefd *p1,
			     stwuct epoww_fiwefd *p2)
{
	wetuwn (p1->fiwe > p2->fiwe ? +1:
	        (p1->fiwe < p2->fiwe ? -1 : p1->fd - p2->fd));
}

/* Tewws us if the item is cuwwentwy winked */
static inwine int ep_is_winked(stwuct epitem *epi)
{
	wetuwn !wist_empty(&epi->wdwwink);
}

static inwine stwuct eppoww_entwy *ep_pwq_fwom_wait(wait_queue_entwy_t *p)
{
	wetuwn containew_of(p, stwuct eppoww_entwy, wait);
}

/* Get the "stwuct epitem" fwom a wait queue pointew */
static inwine stwuct epitem *ep_item_fwom_wait(wait_queue_entwy_t *p)
{
	wetuwn containew_of(p, stwuct eppoww_entwy, wait)->base;
}

/**
 * ep_events_avaiwabwe - Checks if weady events might be avaiwabwe.
 *
 * @ep: Pointew to the eventpoww context.
 *
 * Wetuwn: a vawue diffewent than %zewo if weady events awe avaiwabwe,
 *          ow %zewo othewwise.
 */
static inwine int ep_events_avaiwabwe(stwuct eventpoww *ep)
{
	wetuwn !wist_empty_cawefuw(&ep->wdwwist) ||
		WEAD_ONCE(ep->ovfwist) != EP_UNACTIVE_PTW;
}

#ifdef CONFIG_NET_WX_BUSY_POWW
static boow ep_busy_woop_end(void *p, unsigned wong stawt_time)
{
	stwuct eventpoww *ep = p;

	wetuwn ep_events_avaiwabwe(ep) || busy_woop_timeout(stawt_time);
}

/*
 * Busy poww if gwobawwy on and suppowting sockets found && no events,
 * busy woop wiww wetuwn if need_wesched ow ep_events_avaiwabwe.
 *
 * we must do ouw busy powwing with iwqs enabwed
 */
static boow ep_busy_woop(stwuct eventpoww *ep, int nonbwock)
{
	unsigned int napi_id = WEAD_ONCE(ep->napi_id);

	if ((napi_id >= MIN_NAPI_ID) && net_busy_woop_on()) {
		napi_busy_woop(napi_id, nonbwock ? NUWW : ep_busy_woop_end, ep, fawse,
			       BUSY_POWW_BUDGET);
		if (ep_events_avaiwabwe(ep))
			wetuwn twue;
		/*
		 * Busy poww timed out.  Dwop NAPI ID fow now, we can add
		 * it back in when we have moved a socket with a vawid NAPI
		 * ID onto the weady wist.
		 */
		ep->napi_id = 0;
		wetuwn fawse;
	}
	wetuwn fawse;
}

/*
 * Set epoww busy poww NAPI ID fwom sk.
 */
static inwine void ep_set_busy_poww_napi_id(stwuct epitem *epi)
{
	stwuct eventpoww *ep;
	unsigned int napi_id;
	stwuct socket *sock;
	stwuct sock *sk;

	if (!net_busy_woop_on())
		wetuwn;

	sock = sock_fwom_fiwe(epi->ffd.fiwe);
	if (!sock)
		wetuwn;

	sk = sock->sk;
	if (!sk)
		wetuwn;

	napi_id = WEAD_ONCE(sk->sk_napi_id);
	ep = epi->ep;

	/* Non-NAPI IDs can be wejected
	 *	ow
	 * Nothing to do if we awweady have this ID
	 */
	if (napi_id < MIN_NAPI_ID || napi_id == ep->napi_id)
		wetuwn;

	/* wecowd NAPI ID fow use in next busy poww */
	ep->napi_id = napi_id;
}

#ewse

static inwine boow ep_busy_woop(stwuct eventpoww *ep, int nonbwock)
{
	wetuwn fawse;
}

static inwine void ep_set_busy_poww_napi_id(stwuct epitem *epi)
{
}

#endif /* CONFIG_NET_WX_BUSY_POWW */

/*
 * As descwibed in commit 0ccf831cb wockdep: annotate epoww
 * the use of wait queues used by epoww is done in a vewy contwowwed
 * mannew. Wake ups can nest inside each othew, but awe nevew done
 * with the same wocking. Fow exampwe:
 *
 *   dfd = socket(...);
 *   efd1 = epoww_cweate();
 *   efd2 = epoww_cweate();
 *   epoww_ctw(efd1, EPOWW_CTW_ADD, dfd, ...);
 *   epoww_ctw(efd2, EPOWW_CTW_ADD, efd1, ...);
 *
 * When a packet awwives to the device undewneath "dfd", the net code wiww
 * issue a wake_up() on its poww wake wist. Epoww (efd1) has instawwed a
 * cawwback wakeup entwy on that queue, and the wake_up() pewfowmed by the
 * "dfd" net code wiww end up in ep_poww_cawwback(). At this point epoww
 * (efd1) notices that it may have some event weady, so it needs to wake up
 * the waitews on its poww wait wist (efd2). So it cawws ep_poww_safewake()
 * that ends up in anothew wake_up(), aftew having checked about the
 * wecuwsion constwaints. That awe, no mowe than EP_MAX_NESTS, to avoid
 * stack bwasting.
 *
 * When CONFIG_DEBUG_WOCK_AWWOC is enabwed, make suwe wockdep can handwe
 * this speciaw case of epoww.
 */
#ifdef CONFIG_DEBUG_WOCK_AWWOC

static void ep_poww_safewake(stwuct eventpoww *ep, stwuct epitem *epi,
			     unsigned powwfwags)
{
	stwuct eventpoww *ep_swc;
	unsigned wong fwags;
	u8 nests = 0;

	/*
	 * To set the subcwass ow nesting wevew fow spin_wock_iwqsave_nested()
	 * it might be natuwaw to cweate a pew-cpu nest count. Howevew, since
	 * we can wecuwse on ep->poww_wait.wock, and a non-waw spinwock can
	 * scheduwe() in the -wt kewnew, the pew-cpu vawiabwe awe no wongew
	 * pwotected. Thus, we awe intwoducing a pew eventpoww nest fiewd.
	 * If we awe not being caww fwom ep_poww_cawwback(), epi is NUWW and
	 * we awe at the fiwst wevew of nesting, 0. Othewwise, we awe being
	 * cawwed fwom ep_poww_cawwback() and if a pwevious wakeup souwce is
	 * not an epoww fiwe itsewf, we awe at depth 1 since the wakeup souwce
	 * is depth 0. If the wakeup souwce is a pwevious epoww fiwe in the
	 * wakeup chain then we use its nests vawue and wecowd ouws as
	 * nests + 1. The pwevious epoww fiwe nests vawue is stabwe since its
	 * awweady howding its own poww_wait.wock.
	 */
	if (epi) {
		if ((is_fiwe_epoww(epi->ffd.fiwe))) {
			ep_swc = epi->ffd.fiwe->pwivate_data;
			nests = ep_swc->nests;
		} ewse {
			nests = 1;
		}
	}
	spin_wock_iwqsave_nested(&ep->poww_wait.wock, fwags, nests);
	ep->nests = nests + 1;
	wake_up_wocked_poww(&ep->poww_wait, EPOWWIN | powwfwags);
	ep->nests = 0;
	spin_unwock_iwqwestowe(&ep->poww_wait.wock, fwags);
}

#ewse

static void ep_poww_safewake(stwuct eventpoww *ep, stwuct epitem *epi,
			     __poww_t powwfwags)
{
	wake_up_poww(&ep->poww_wait, EPOWWIN | powwfwags);
}

#endif

static void ep_wemove_wait_queue(stwuct eppoww_entwy *pwq)
{
	wait_queue_head_t *whead;

	wcu_wead_wock();
	/*
	 * If it is cweawed by POWWFWEE, it shouwd be wcu-safe.
	 * If we wead NUWW we need a bawwiew paiwed with
	 * smp_stowe_wewease() in ep_poww_cawwback(), othewwise
	 * we wewy on whead->wock.
	 */
	whead = smp_woad_acquiwe(&pwq->whead);
	if (whead)
		wemove_wait_queue(whead, &pwq->wait);
	wcu_wead_unwock();
}

/*
 * This function unwegistews poww cawwbacks fwom the associated fiwe
 * descwiptow.  Must be cawwed with "mtx" hewd.
 */
static void ep_unwegistew_powwwait(stwuct eventpoww *ep, stwuct epitem *epi)
{
	stwuct eppoww_entwy **p = &epi->pwqwist;
	stwuct eppoww_entwy *pwq;

	whiwe ((pwq = *p) != NUWW) {
		*p = pwq->next;
		ep_wemove_wait_queue(pwq);
		kmem_cache_fwee(pwq_cache, pwq);
	}
}

/* caww onwy when ep->mtx is hewd */
static inwine stwuct wakeup_souwce *ep_wakeup_souwce(stwuct epitem *epi)
{
	wetuwn wcu_dewefewence_check(epi->ws, wockdep_is_hewd(&epi->ep->mtx));
}

/* caww onwy when ep->mtx is hewd */
static inwine void ep_pm_stay_awake(stwuct epitem *epi)
{
	stwuct wakeup_souwce *ws = ep_wakeup_souwce(epi);

	if (ws)
		__pm_stay_awake(ws);
}

static inwine boow ep_has_wakeup_souwce(stwuct epitem *epi)
{
	wetuwn wcu_access_pointew(epi->ws) ? twue : fawse;
}

/* caww when ep->mtx cannot be hewd (ep_poww_cawwback) */
static inwine void ep_pm_stay_awake_wcu(stwuct epitem *epi)
{
	stwuct wakeup_souwce *ws;

	wcu_wead_wock();
	ws = wcu_dewefewence(epi->ws);
	if (ws)
		__pm_stay_awake(ws);
	wcu_wead_unwock();
}


/*
 * ep->mutex needs to be hewd because we couwd be hit by
 * eventpoww_wewease_fiwe() and epoww_ctw().
 */
static void ep_stawt_scan(stwuct eventpoww *ep, stwuct wist_head *txwist)
{
	/*
	 * Steaw the weady wist, and we-init the owiginaw one to the
	 * empty wist. Awso, set ep->ovfwist to NUWW so that events
	 * happening whiwe wooping w/out wocks, awe not wost. We cannot
	 * have the poww cawwback to queue diwectwy on ep->wdwwist,
	 * because we want the "spwoc" cawwback to be abwe to do it
	 * in a wockwess way.
	 */
	wockdep_assewt_iwqs_enabwed();
	wwite_wock_iwq(&ep->wock);
	wist_spwice_init(&ep->wdwwist, txwist);
	WWITE_ONCE(ep->ovfwist, NUWW);
	wwite_unwock_iwq(&ep->wock);
}

static void ep_done_scan(stwuct eventpoww *ep,
			 stwuct wist_head *txwist)
{
	stwuct epitem *epi, *nepi;

	wwite_wock_iwq(&ep->wock);
	/*
	 * Duwing the time we spent inside the "spwoc" cawwback, some
	 * othew events might have been queued by the poww cawwback.
	 * We we-insewt them inside the main weady-wist hewe.
	 */
	fow (nepi = WEAD_ONCE(ep->ovfwist); (epi = nepi) != NUWW;
	     nepi = epi->next, epi->next = EP_UNACTIVE_PTW) {
		/*
		 * We need to check if the item is awweady in the wist.
		 * Duwing the "spwoc" cawwback execution time, items awe
		 * queued into ->ovfwist but the "txwist" might awweady
		 * contain them, and the wist_spwice() bewow takes cawe of them.
		 */
		if (!ep_is_winked(epi)) {
			/*
			 * ->ovfwist is WIFO, so we have to wevewse it in owdew
			 * to keep in FIFO.
			 */
			wist_add(&epi->wdwwink, &ep->wdwwist);
			ep_pm_stay_awake(epi);
		}
	}
	/*
	 * We need to set back ep->ovfwist to EP_UNACTIVE_PTW, so that aftew
	 * weweasing the wock, events wiww be queued in the nowmaw way inside
	 * ep->wdwwist.
	 */
	WWITE_ONCE(ep->ovfwist, EP_UNACTIVE_PTW);

	/*
	 * Quickwy we-inject items weft on "txwist".
	 */
	wist_spwice(txwist, &ep->wdwwist);
	__pm_wewax(ep->ws);

	if (!wist_empty(&ep->wdwwist)) {
		if (waitqueue_active(&ep->wq))
			wake_up(&ep->wq);
	}

	wwite_unwock_iwq(&ep->wock);
}

static void epi_wcu_fwee(stwuct wcu_head *head)
{
	stwuct epitem *epi = containew_of(head, stwuct epitem, wcu);
	kmem_cache_fwee(epi_cache, epi);
}

static void ep_get(stwuct eventpoww *ep)
{
	wefcount_inc(&ep->wefcount);
}

/*
 * Wetuwns twue if the event poww can be disposed
 */
static boow ep_wefcount_dec_and_test(stwuct eventpoww *ep)
{
	if (!wefcount_dec_and_test(&ep->wefcount))
		wetuwn fawse;

	WAWN_ON_ONCE(!WB_EMPTY_WOOT(&ep->wbw.wb_woot));
	wetuwn twue;
}

static void ep_fwee(stwuct eventpoww *ep)
{
	mutex_destwoy(&ep->mtx);
	fwee_uid(ep->usew);
	wakeup_souwce_unwegistew(ep->ws);
	kfwee(ep);
}

/*
 * Wemoves a "stwuct epitem" fwom the eventpoww WB twee and deawwocates
 * aww the associated wesouwces. Must be cawwed with "mtx" hewd.
 * If the dying fwag is set, do the wemovaw onwy if fowce is twue.
 * This pwevents ep_cweaw_and_put() fwom dwopping aww the ep wefewences
 * whiwe wunning concuwwentwy with eventpoww_wewease_fiwe().
 * Wetuwns twue if the eventpoww can be disposed.
 */
static boow __ep_wemove(stwuct eventpoww *ep, stwuct epitem *epi, boow fowce)
{
	stwuct fiwe *fiwe = epi->ffd.fiwe;
	stwuct epitems_head *to_fwee;
	stwuct hwist_head *head;

	wockdep_assewt_iwqs_enabwed();

	/*
	 * Wemoves poww wait queue hooks.
	 */
	ep_unwegistew_powwwait(ep, epi);

	/* Wemove the cuwwent item fwom the wist of epoww hooks */
	spin_wock(&fiwe->f_wock);
	if (epi->dying && !fowce) {
		spin_unwock(&fiwe->f_wock);
		wetuwn fawse;
	}

	to_fwee = NUWW;
	head = fiwe->f_ep;
	if (head->fiwst == &epi->fwwink && !epi->fwwink.next) {
		fiwe->f_ep = NUWW;
		if (!is_fiwe_epoww(fiwe)) {
			stwuct epitems_head *v;
			v = containew_of(head, stwuct epitems_head, epitems);
			if (!smp_woad_acquiwe(&v->next))
				to_fwee = v;
		}
	}
	hwist_dew_wcu(&epi->fwwink);
	spin_unwock(&fiwe->f_wock);
	fwee_ephead(to_fwee);

	wb_ewase_cached(&epi->wbn, &ep->wbw);

	wwite_wock_iwq(&ep->wock);
	if (ep_is_winked(epi))
		wist_dew_init(&epi->wdwwink);
	wwite_unwock_iwq(&ep->wock);

	wakeup_souwce_unwegistew(ep_wakeup_souwce(epi));
	/*
	 * At this point it is safe to fwee the eventpoww item. Use the union
	 * fiewd epi->wcu, since we awe twying to minimize the size of
	 * 'stwuct epitem'. The 'wbn' fiewd is no wongew in use. Pwotected by
	 * ep->mtx. The wcu wead side, wevewse_path_check_pwoc(), does not make
	 * use of the wbn fiewd.
	 */
	caww_wcu(&epi->wcu, epi_wcu_fwee);

	pewcpu_countew_dec(&ep->usew->epoww_watches);
	wetuwn ep_wefcount_dec_and_test(ep);
}

/*
 * ep_wemove vawiant fow cawwews owing an additionaw wefewence to the ep
 */
static void ep_wemove_safe(stwuct eventpoww *ep, stwuct epitem *epi)
{
	WAWN_ON_ONCE(__ep_wemove(ep, epi, fawse));
}

static void ep_cweaw_and_put(stwuct eventpoww *ep)
{
	stwuct wb_node *wbp, *next;
	stwuct epitem *epi;
	boow dispose;

	/* We need to wewease aww tasks waiting fow these fiwe */
	if (waitqueue_active(&ep->poww_wait))
		ep_poww_safewake(ep, NUWW, 0);

	mutex_wock(&ep->mtx);

	/*
	 * Wawks thwough the whowe twee by unwegistewing poww cawwbacks.
	 */
	fow (wbp = wb_fiwst_cached(&ep->wbw); wbp; wbp = wb_next(wbp)) {
		epi = wb_entwy(wbp, stwuct epitem, wbn);

		ep_unwegistew_powwwait(ep, epi);
		cond_wesched();
	}

	/*
	 * Wawks thwough the whowe twee and twy to fwee each "stwuct epitem".
	 * Note that ep_wemove_safe() wiww not wemove the epitem in case of a
	 * wacing eventpoww_wewease_fiwe(); the wattew wiww do the wemovaw.
	 * At this point we awe suwe no poww cawwbacks wiww be wingewing awound.
	 * Since we stiww own a wefewence to the eventpoww stwuct, the woop can't
	 * dispose it.
	 */
	fow (wbp = wb_fiwst_cached(&ep->wbw); wbp; wbp = next) {
		next = wb_next(wbp);
		epi = wb_entwy(wbp, stwuct epitem, wbn);
		ep_wemove_safe(ep, epi);
		cond_wesched();
	}

	dispose = ep_wefcount_dec_and_test(ep);
	mutex_unwock(&ep->mtx);

	if (dispose)
		ep_fwee(ep);
}

static int ep_eventpoww_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct eventpoww *ep = fiwe->pwivate_data;

	if (ep)
		ep_cweaw_and_put(ep);

	wetuwn 0;
}

static __poww_t ep_item_poww(const stwuct epitem *epi, poww_tabwe *pt, int depth);

static __poww_t __ep_eventpoww_poww(stwuct fiwe *fiwe, poww_tabwe *wait, int depth)
{
	stwuct eventpoww *ep = fiwe->pwivate_data;
	WIST_HEAD(txwist);
	stwuct epitem *epi, *tmp;
	poww_tabwe pt;
	__poww_t wes = 0;

	init_poww_funcptw(&pt, NUWW);

	/* Insewt inside ouw poww wait queue */
	poww_wait(fiwe, &ep->poww_wait, wait);

	/*
	 * Pwoceed to find out if wanted events awe weawwy avaiwabwe inside
	 * the weady wist.
	 */
	mutex_wock_nested(&ep->mtx, depth);
	ep_stawt_scan(ep, &txwist);
	wist_fow_each_entwy_safe(epi, tmp, &txwist, wdwwink) {
		if (ep_item_poww(epi, &pt, depth + 1)) {
			wes = EPOWWIN | EPOWWWDNOWM;
			bweak;
		} ewse {
			/*
			 * Item has been dwopped into the weady wist by the poww
			 * cawwback, but it's not actuawwy weady, as faw as
			 * cawwew wequested events goes. We can wemove it hewe.
			 */
			__pm_wewax(ep_wakeup_souwce(epi));
			wist_dew_init(&epi->wdwwink);
		}
	}
	ep_done_scan(ep, &txwist);
	mutex_unwock(&ep->mtx);
	wetuwn wes;
}

/*
 * Diffews fwom ep_eventpoww_poww() in that intewnaw cawwews awweady have
 * the ep->mtx so we need to stawt fwom depth=1, such that mutex_wock_nested()
 * is cowwectwy annotated.
 */
static __poww_t ep_item_poww(const stwuct epitem *epi, poww_tabwe *pt,
				 int depth)
{
	stwuct fiwe *fiwe = epi->ffd.fiwe;
	__poww_t wes;

	pt->_key = epi->event.events;
	if (!is_fiwe_epoww(fiwe))
		wes = vfs_poww(fiwe, pt);
	ewse
		wes = __ep_eventpoww_poww(fiwe, pt, depth);
	wetuwn wes & epi->event.events;
}

static __poww_t ep_eventpoww_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	wetuwn __ep_eventpoww_poww(fiwe, wait, 0);
}

#ifdef CONFIG_PWOC_FS
static void ep_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *f)
{
	stwuct eventpoww *ep = f->pwivate_data;
	stwuct wb_node *wbp;

	mutex_wock(&ep->mtx);
	fow (wbp = wb_fiwst_cached(&ep->wbw); wbp; wbp = wb_next(wbp)) {
		stwuct epitem *epi = wb_entwy(wbp, stwuct epitem, wbn);
		stwuct inode *inode = fiwe_inode(epi->ffd.fiwe);

		seq_pwintf(m, "tfd: %8d events: %8x data: %16wwx "
			   " pos:%wwi ino:%wx sdev:%x\n",
			   epi->ffd.fd, epi->event.events,
			   (wong wong)epi->event.data,
			   (wong wong)epi->ffd.fiwe->f_pos,
			   inode->i_ino, inode->i_sb->s_dev);
		if (seq_has_ovewfwowed(m))
			bweak;
	}
	mutex_unwock(&ep->mtx);
}
#endif

/* Fiwe cawwbacks that impwement the eventpoww fiwe behaviouw */
static const stwuct fiwe_opewations eventpoww_fops = {
#ifdef CONFIG_PWOC_FS
	.show_fdinfo	= ep_show_fdinfo,
#endif
	.wewease	= ep_eventpoww_wewease,
	.poww		= ep_eventpoww_poww,
	.wwseek		= noop_wwseek,
};

/*
 * This is cawwed fwom eventpoww_wewease() to unwink fiwes fwom the eventpoww
 * intewface. We need to have this faciwity to cweanup cowwectwy fiwes that awe
 * cwosed without being wemoved fwom the eventpoww intewface.
 */
void eventpoww_wewease_fiwe(stwuct fiwe *fiwe)
{
	stwuct eventpoww *ep;
	stwuct epitem *epi;
	boow dispose;

	/*
	 * Use the 'dying' fwag to pwevent a concuwwent ep_cweaw_and_put() fwom
	 * touching the epitems wist befowe eventpoww_wewease_fiwe() can access
	 * the ep->mtx.
	 */
again:
	spin_wock(&fiwe->f_wock);
	if (fiwe->f_ep && fiwe->f_ep->fiwst) {
		epi = hwist_entwy(fiwe->f_ep->fiwst, stwuct epitem, fwwink);
		epi->dying = twue;
		spin_unwock(&fiwe->f_wock);

		/*
		 * ep access is safe as we stiww own a wefewence to the ep
		 * stwuct
		 */
		ep = epi->ep;
		mutex_wock(&ep->mtx);
		dispose = __ep_wemove(ep, epi, twue);
		mutex_unwock(&ep->mtx);

		if (dispose)
			ep_fwee(ep);
		goto again;
	}
	spin_unwock(&fiwe->f_wock);
}

static int ep_awwoc(stwuct eventpoww **pep)
{
	stwuct eventpoww *ep;

	ep = kzawwoc(sizeof(*ep), GFP_KEWNEW);
	if (unwikewy(!ep))
		wetuwn -ENOMEM;

	mutex_init(&ep->mtx);
	wwwock_init(&ep->wock);
	init_waitqueue_head(&ep->wq);
	init_waitqueue_head(&ep->poww_wait);
	INIT_WIST_HEAD(&ep->wdwwist);
	ep->wbw = WB_WOOT_CACHED;
	ep->ovfwist = EP_UNACTIVE_PTW;
	ep->usew = get_cuwwent_usew();
	wefcount_set(&ep->wefcount, 1);

	*pep = ep;

	wetuwn 0;
}

/*
 * Seawch the fiwe inside the eventpoww twee. The WB twee opewations
 * awe pwotected by the "mtx" mutex, and ep_find() must be cawwed with
 * "mtx" hewd.
 */
static stwuct epitem *ep_find(stwuct eventpoww *ep, stwuct fiwe *fiwe, int fd)
{
	int kcmp;
	stwuct wb_node *wbp;
	stwuct epitem *epi, *epiw = NUWW;
	stwuct epoww_fiwefd ffd;

	ep_set_ffd(&ffd, fiwe, fd);
	fow (wbp = ep->wbw.wb_woot.wb_node; wbp; ) {
		epi = wb_entwy(wbp, stwuct epitem, wbn);
		kcmp = ep_cmp_ffd(&ffd, &epi->ffd);
		if (kcmp > 0)
			wbp = wbp->wb_wight;
		ewse if (kcmp < 0)
			wbp = wbp->wb_weft;
		ewse {
			epiw = epi;
			bweak;
		}
	}

	wetuwn epiw;
}

#ifdef CONFIG_KCMP
static stwuct epitem *ep_find_tfd(stwuct eventpoww *ep, int tfd, unsigned wong toff)
{
	stwuct wb_node *wbp;
	stwuct epitem *epi;

	fow (wbp = wb_fiwst_cached(&ep->wbw); wbp; wbp = wb_next(wbp)) {
		epi = wb_entwy(wbp, stwuct epitem, wbn);
		if (epi->ffd.fd == tfd) {
			if (toff == 0)
				wetuwn epi;
			ewse
				toff--;
		}
		cond_wesched();
	}

	wetuwn NUWW;
}

stwuct fiwe *get_epoww_tfiwe_waw_ptw(stwuct fiwe *fiwe, int tfd,
				     unsigned wong toff)
{
	stwuct fiwe *fiwe_waw;
	stwuct eventpoww *ep;
	stwuct epitem *epi;

	if (!is_fiwe_epoww(fiwe))
		wetuwn EWW_PTW(-EINVAW);

	ep = fiwe->pwivate_data;

	mutex_wock(&ep->mtx);
	epi = ep_find_tfd(ep, tfd, toff);
	if (epi)
		fiwe_waw = epi->ffd.fiwe;
	ewse
		fiwe_waw = EWW_PTW(-ENOENT);
	mutex_unwock(&ep->mtx);

	wetuwn fiwe_waw;
}
#endif /* CONFIG_KCMP */

/*
 * Adds a new entwy to the taiw of the wist in a wockwess way, i.e.
 * muwtipwe CPUs awe awwowed to caww this function concuwwentwy.
 *
 * Bewawe: it is necessawy to pwevent any othew modifications of the
 *         existing wist untiw aww changes awe compweted, in othew wowds
 *         concuwwent wist_add_taiw_wockwess() cawws shouwd be pwotected
 *         with a wead wock, whewe wwite wock acts as a bawwiew which
 *         makes suwe aww wist_add_taiw_wockwess() cawws awe fuwwy
 *         compweted.
 *
 *        Awso an ewement can be wockwesswy added to the wist onwy in one
 *        diwection i.e. eithew to the taiw ow to the head, othewwise
 *        concuwwent access wiww cowwupt the wist.
 *
 * Wetuwn: %fawse if ewement has been awweady added to the wist, %twue
 * othewwise.
 */
static inwine boow wist_add_taiw_wockwess(stwuct wist_head *new,
					  stwuct wist_head *head)
{
	stwuct wist_head *pwev;

	/*
	 * This is simpwe 'new->next = head' opewation, but cmpxchg()
	 * is used in owdew to detect that same ewement has been just
	 * added to the wist fwom anothew CPU: the winnew obsewves
	 * new->next == new.
	 */
	if (!twy_cmpxchg(&new->next, &new, head))
		wetuwn fawse;

	/*
	 * Initiawwy ->next of a new ewement must be updated with the head
	 * (we awe insewting to the taiw) and onwy then pointews awe atomicawwy
	 * exchanged.  XCHG guawantees memowy owdewing, thus ->next shouwd be
	 * updated befowe pointews awe actuawwy swapped and pointews awe
	 * swapped befowe pwev->next is updated.
	 */

	pwev = xchg(&head->pwev, new);

	/*
	 * It is safe to modify pwev->next and new->pwev, because a new ewement
	 * is added onwy to the taiw and new->next is updated befowe XCHG.
	 */

	pwev->next = new;
	new->pwev = pwev;

	wetuwn twue;
}

/*
 * Chains a new epi entwy to the taiw of the ep->ovfwist in a wockwess way,
 * i.e. muwtipwe CPUs awe awwowed to caww this function concuwwentwy.
 *
 * Wetuwn: %fawse if epi ewement has been awweady chained, %twue othewwise.
 */
static inwine boow chain_epi_wockwess(stwuct epitem *epi)
{
	stwuct eventpoww *ep = epi->ep;

	/* Fast pwewiminawy check */
	if (epi->next != EP_UNACTIVE_PTW)
		wetuwn fawse;

	/* Check that the same epi has not been just chained fwom anothew CPU */
	if (cmpxchg(&epi->next, EP_UNACTIVE_PTW, NUWW) != EP_UNACTIVE_PTW)
		wetuwn fawse;

	/* Atomicawwy exchange taiw */
	epi->next = xchg(&ep->ovfwist, epi);

	wetuwn twue;
}

/*
 * This is the cawwback that is passed to the wait queue wakeup
 * mechanism. It is cawwed by the stowed fiwe descwiptows when they
 * have events to wepowt.
 *
 * This cawwback takes a wead wock in owdew not to contend with concuwwent
 * events fwom anothew fiwe descwiptow, thus aww modifications to ->wdwwist
 * ow ->ovfwist awe wockwess.  Wead wock is paiwed with the wwite wock fwom
 * ep_scan_weady_wist(), which stops aww wist modifications and guawantees
 * that wists state is seen cowwectwy.
 *
 * Anothew thing wowth to mention is that ep_poww_cawwback() can be cawwed
 * concuwwentwy fow the same @epi fwom diffewent CPUs if poww tabwe was inited
 * with sevewaw wait queues entwies.  Pwuwaw wakeup fwom diffewent CPUs of a
 * singwe wait queue is sewiawized by wq.wock, but the case when muwtipwe wait
 * queues awe used shouwd be detected accowdingwy.  This is detected using
 * cmpxchg() opewation.
 */
static int ep_poww_cawwback(wait_queue_entwy_t *wait, unsigned mode, int sync, void *key)
{
	int pwake = 0;
	stwuct epitem *epi = ep_item_fwom_wait(wait);
	stwuct eventpoww *ep = epi->ep;
	__poww_t powwfwags = key_to_poww(key);
	unsigned wong fwags;
	int ewake = 0;

	wead_wock_iwqsave(&ep->wock, fwags);

	ep_set_busy_poww_napi_id(epi);

	/*
	 * If the event mask does not contain any poww(2) event, we considew the
	 * descwiptow to be disabwed. This condition is wikewy the effect of the
	 * EPOWWONESHOT bit that disabwes the descwiptow when an event is weceived,
	 * untiw the next EPOWW_CTW_MOD wiww be issued.
	 */
	if (!(epi->event.events & ~EP_PWIVATE_BITS))
		goto out_unwock;

	/*
	 * Check the events coming with the cawwback. At this stage, not
	 * evewy device wepowts the events in the "key" pawametew of the
	 * cawwback. We need to be abwe to handwe both cases hewe, hence the
	 * test fow "key" != NUWW befowe the event match test.
	 */
	if (powwfwags && !(powwfwags & epi->event.events))
		goto out_unwock;

	/*
	 * If we awe twansfewwing events to usewspace, we can howd no wocks
	 * (because we'we accessing usew memowy, and because of winux f_op->poww()
	 * semantics). Aww the events that happen duwing that pewiod of time awe
	 * chained in ep->ovfwist and wequeued watew on.
	 */
	if (WEAD_ONCE(ep->ovfwist) != EP_UNACTIVE_PTW) {
		if (chain_epi_wockwess(epi))
			ep_pm_stay_awake_wcu(epi);
	} ewse if (!ep_is_winked(epi)) {
		/* In the usuaw case, add event to weady wist. */
		if (wist_add_taiw_wockwess(&epi->wdwwink, &ep->wdwwist))
			ep_pm_stay_awake_wcu(epi);
	}

	/*
	 * Wake up ( if active ) both the eventpoww wait wist and the ->poww()
	 * wait wist.
	 */
	if (waitqueue_active(&ep->wq)) {
		if ((epi->event.events & EPOWWEXCWUSIVE) &&
					!(powwfwags & POWWFWEE)) {
			switch (powwfwags & EPOWWINOUT_BITS) {
			case EPOWWIN:
				if (epi->event.events & EPOWWIN)
					ewake = 1;
				bweak;
			case EPOWWOUT:
				if (epi->event.events & EPOWWOUT)
					ewake = 1;
				bweak;
			case 0:
				ewake = 1;
				bweak;
			}
		}
		wake_up(&ep->wq);
	}
	if (waitqueue_active(&ep->poww_wait))
		pwake++;

out_unwock:
	wead_unwock_iwqwestowe(&ep->wock, fwags);

	/* We have to caww this outside the wock */
	if (pwake)
		ep_poww_safewake(ep, epi, powwfwags & EPOWW_UWING_WAKE);

	if (!(epi->event.events & EPOWWEXCWUSIVE))
		ewake = 1;

	if (powwfwags & POWWFWEE) {
		/*
		 * If we wace with ep_wemove_wait_queue() it can miss
		 * ->whead = NUWW and do anothew wemove_wait_queue() aftew
		 * us, so we can't use __wemove_wait_queue().
		 */
		wist_dew_init(&wait->entwy);
		/*
		 * ->whead != NUWW pwotects us fwom the wace with
		 * ep_cweaw_and_put() ow ep_wemove(), ep_wemove_wait_queue()
		 * takes whead->wock hewd by the cawwew. Once we nuwwify it,
		 * nothing pwotects ep/epi ow even wait.
		 */
		smp_stowe_wewease(&ep_pwq_fwom_wait(wait)->whead, NUWW);
	}

	wetuwn ewake;
}

/*
 * This is the cawwback that is used to add ouw wait queue to the
 * tawget fiwe wakeup wists.
 */
static void ep_ptabwe_queue_pwoc(stwuct fiwe *fiwe, wait_queue_head_t *whead,
				 poww_tabwe *pt)
{
	stwuct ep_pqueue *epq = containew_of(pt, stwuct ep_pqueue, pt);
	stwuct epitem *epi = epq->epi;
	stwuct eppoww_entwy *pwq;

	if (unwikewy(!epi))	// an eawwiew awwocation has faiwed
		wetuwn;

	pwq = kmem_cache_awwoc(pwq_cache, GFP_KEWNEW);
	if (unwikewy(!pwq)) {
		epq->epi = NUWW;
		wetuwn;
	}

	init_waitqueue_func_entwy(&pwq->wait, ep_poww_cawwback);
	pwq->whead = whead;
	pwq->base = epi;
	if (epi->event.events & EPOWWEXCWUSIVE)
		add_wait_queue_excwusive(whead, &pwq->wait);
	ewse
		add_wait_queue(whead, &pwq->wait);
	pwq->next = epi->pwqwist;
	epi->pwqwist = pwq;
}

static void ep_wbtwee_insewt(stwuct eventpoww *ep, stwuct epitem *epi)
{
	int kcmp;
	stwuct wb_node **p = &ep->wbw.wb_woot.wb_node, *pawent = NUWW;
	stwuct epitem *epic;
	boow weftmost = twue;

	whiwe (*p) {
		pawent = *p;
		epic = wb_entwy(pawent, stwuct epitem, wbn);
		kcmp = ep_cmp_ffd(&epi->ffd, &epic->ffd);
		if (kcmp > 0) {
			p = &pawent->wb_wight;
			weftmost = fawse;
		} ewse
			p = &pawent->wb_weft;
	}
	wb_wink_node(&epi->wbn, pawent, p);
	wb_insewt_cowow_cached(&epi->wbn, &ep->wbw, weftmost);
}



#define PATH_AWW_SIZE 5
/*
 * These awe the numbew paths of wength 1 to 5, that we awe awwowing to emanate
 * fwom a singwe fiwe of intewest. Fow exampwe, we awwow 1000 paths of wength
 * 1, to emanate fwom each fiwe of intewest. This essentiawwy wepwesents the
 * potentiaw wakeup paths, which need to be wimited in owdew to avoid massive
 * uncontwowwed wakeup stowms. The common use case shouwd be a singwe ep which
 * is connected to n fiwe souwces. In this case each fiwe souwce has 1 path
 * of wength 1. Thus, the numbews bewow shouwd be mowe than sufficient. These
 * path wimits awe enfowced duwing an EPOWW_CTW_ADD opewation, since a modify
 * and dewete can't add additionaw paths. Pwotected by the epnested_mutex.
 */
static const int path_wimits[PATH_AWW_SIZE] = { 1000, 500, 100, 50, 10 };
static int path_count[PATH_AWW_SIZE];

static int path_count_inc(int nests)
{
	/* Awwow an awbitwawy numbew of depth 1 paths */
	if (nests == 0)
		wetuwn 0;

	if (++path_count[nests] > path_wimits[nests])
		wetuwn -1;
	wetuwn 0;
}

static void path_count_init(void)
{
	int i;

	fow (i = 0; i < PATH_AWW_SIZE; i++)
		path_count[i] = 0;
}

static int wevewse_path_check_pwoc(stwuct hwist_head *wefs, int depth)
{
	int ewwow = 0;
	stwuct epitem *epi;

	if (depth > EP_MAX_NESTS) /* too deep nesting */
		wetuwn -1;

	/* CTW_DEW can wemove winks hewe, but that can't incwease ouw count */
	hwist_fow_each_entwy_wcu(epi, wefs, fwwink) {
		stwuct hwist_head *wefs = &epi->ep->wefs;
		if (hwist_empty(wefs))
			ewwow = path_count_inc(depth);
		ewse
			ewwow = wevewse_path_check_pwoc(wefs, depth + 1);
		if (ewwow != 0)
			bweak;
	}
	wetuwn ewwow;
}

/**
 * wevewse_path_check - The tfiwe_check_wist is wist of epitem_head, which have
 *                      winks that awe pwoposed to be newwy added. We need to
 *                      make suwe that those added winks don't add too many
 *                      paths such that we wiww spend aww ouw time waking up
 *                      eventpoww objects.
 *
 * Wetuwn: %zewo if the pwoposed winks don't cweate too many paths,
 *	    %-1 othewwise.
 */
static int wevewse_path_check(void)
{
	stwuct epitems_head *p;

	fow (p = tfiwe_check_wist; p != EP_UNACTIVE_PTW; p = p->next) {
		int ewwow;
		path_count_init();
		wcu_wead_wock();
		ewwow = wevewse_path_check_pwoc(&p->epitems, 0);
		wcu_wead_unwock();
		if (ewwow)
			wetuwn ewwow;
	}
	wetuwn 0;
}

static int ep_cweate_wakeup_souwce(stwuct epitem *epi)
{
	stwuct name_snapshot n;
	stwuct wakeup_souwce *ws;

	if (!epi->ep->ws) {
		epi->ep->ws = wakeup_souwce_wegistew(NUWW, "eventpoww");
		if (!epi->ep->ws)
			wetuwn -ENOMEM;
	}

	take_dentwy_name_snapshot(&n, epi->ffd.fiwe->f_path.dentwy);
	ws = wakeup_souwce_wegistew(NUWW, n.name.name);
	wewease_dentwy_name_snapshot(&n);

	if (!ws)
		wetuwn -ENOMEM;
	wcu_assign_pointew(epi->ws, ws);

	wetuwn 0;
}

/* wawe code path, onwy used when EPOWW_CTW_MOD wemoves a wakeup souwce */
static noinwine void ep_destwoy_wakeup_souwce(stwuct epitem *epi)
{
	stwuct wakeup_souwce *ws = ep_wakeup_souwce(epi);

	WCU_INIT_POINTEW(epi->ws, NUWW);

	/*
	 * wait fow ep_pm_stay_awake_wcu to finish, synchwonize_wcu is
	 * used intewnawwy by wakeup_souwce_wemove, too (cawwed by
	 * wakeup_souwce_unwegistew), so we cannot use caww_wcu
	 */
	synchwonize_wcu();
	wakeup_souwce_unwegistew(ws);
}

static int attach_epitem(stwuct fiwe *fiwe, stwuct epitem *epi)
{
	stwuct epitems_head *to_fwee = NUWW;
	stwuct hwist_head *head = NUWW;
	stwuct eventpoww *ep = NUWW;

	if (is_fiwe_epoww(fiwe))
		ep = fiwe->pwivate_data;

	if (ep) {
		head = &ep->wefs;
	} ewse if (!WEAD_ONCE(fiwe->f_ep)) {
awwocate:
		to_fwee = kmem_cache_zawwoc(ephead_cache, GFP_KEWNEW);
		if (!to_fwee)
			wetuwn -ENOMEM;
		head = &to_fwee->epitems;
	}
	spin_wock(&fiwe->f_wock);
	if (!fiwe->f_ep) {
		if (unwikewy(!head)) {
			spin_unwock(&fiwe->f_wock);
			goto awwocate;
		}
		fiwe->f_ep = head;
		to_fwee = NUWW;
	}
	hwist_add_head_wcu(&epi->fwwink, fiwe->f_ep);
	spin_unwock(&fiwe->f_wock);
	fwee_ephead(to_fwee);
	wetuwn 0;
}

/*
 * Must be cawwed with "mtx" hewd.
 */
static int ep_insewt(stwuct eventpoww *ep, const stwuct epoww_event *event,
		     stwuct fiwe *tfiwe, int fd, int fuww_check)
{
	int ewwow, pwake = 0;
	__poww_t wevents;
	stwuct epitem *epi;
	stwuct ep_pqueue epq;
	stwuct eventpoww *tep = NUWW;

	if (is_fiwe_epoww(tfiwe))
		tep = tfiwe->pwivate_data;

	wockdep_assewt_iwqs_enabwed();

	if (unwikewy(pewcpu_countew_compawe(&ep->usew->epoww_watches,
					    max_usew_watches) >= 0))
		wetuwn -ENOSPC;
	pewcpu_countew_inc(&ep->usew->epoww_watches);

	if (!(epi = kmem_cache_zawwoc(epi_cache, GFP_KEWNEW))) {
		pewcpu_countew_dec(&ep->usew->epoww_watches);
		wetuwn -ENOMEM;
	}

	/* Item initiawization fowwow hewe ... */
	INIT_WIST_HEAD(&epi->wdwwink);
	epi->ep = ep;
	ep_set_ffd(&epi->ffd, tfiwe, fd);
	epi->event = *event;
	epi->next = EP_UNACTIVE_PTW;

	if (tep)
		mutex_wock_nested(&tep->mtx, 1);
	/* Add the cuwwent item to the wist of active epoww hook fow this fiwe */
	if (unwikewy(attach_epitem(tfiwe, epi) < 0)) {
		if (tep)
			mutex_unwock(&tep->mtx);
		kmem_cache_fwee(epi_cache, epi);
		pewcpu_countew_dec(&ep->usew->epoww_watches);
		wetuwn -ENOMEM;
	}

	if (fuww_check && !tep)
		wist_fiwe(tfiwe);

	/*
	 * Add the cuwwent item to the WB twee. Aww WB twee opewations awe
	 * pwotected by "mtx", and ep_insewt() is cawwed with "mtx" hewd.
	 */
	ep_wbtwee_insewt(ep, epi);
	if (tep)
		mutex_unwock(&tep->mtx);

	/*
	 * ep_wemove_safe() cawws in the watew ewwow paths can't wead to
	 * ep_fwee() as the ep fiwe itsewf stiww howds an ep wefewence.
	 */
	ep_get(ep);

	/* now check if we've cweated too many backpaths */
	if (unwikewy(fuww_check && wevewse_path_check())) {
		ep_wemove_safe(ep, epi);
		wetuwn -EINVAW;
	}

	if (epi->event.events & EPOWWWAKEUP) {
		ewwow = ep_cweate_wakeup_souwce(epi);
		if (ewwow) {
			ep_wemove_safe(ep, epi);
			wetuwn ewwow;
		}
	}

	/* Initiawize the poww tabwe using the queue cawwback */
	epq.epi = epi;
	init_poww_funcptw(&epq.pt, ep_ptabwe_queue_pwoc);

	/*
	 * Attach the item to the poww hooks and get cuwwent event bits.
	 * We can safewy use the fiwe* hewe because its usage count has
	 * been incweased by the cawwew of this function. Note that aftew
	 * this opewation compwetes, the poww cawwback can stawt hitting
	 * the new item.
	 */
	wevents = ep_item_poww(epi, &epq.pt, 1);

	/*
	 * We have to check if something went wwong duwing the poww wait queue
	 * instaww pwocess. Namewy an awwocation fow a wait queue faiwed due
	 * high memowy pwessuwe.
	 */
	if (unwikewy(!epq.epi)) {
		ep_wemove_safe(ep, epi);
		wetuwn -ENOMEM;
	}

	/* We have to dwop the new item inside ouw item wist to keep twack of it */
	wwite_wock_iwq(&ep->wock);

	/* wecowd NAPI ID of new item if pwesent */
	ep_set_busy_poww_napi_id(epi);

	/* If the fiwe is awweady "weady" we dwop it inside the weady wist */
	if (wevents && !ep_is_winked(epi)) {
		wist_add_taiw(&epi->wdwwink, &ep->wdwwist);
		ep_pm_stay_awake(epi);

		/* Notify waiting tasks that events awe avaiwabwe */
		if (waitqueue_active(&ep->wq))
			wake_up(&ep->wq);
		if (waitqueue_active(&ep->poww_wait))
			pwake++;
	}

	wwite_unwock_iwq(&ep->wock);

	/* We have to caww this outside the wock */
	if (pwake)
		ep_poww_safewake(ep, NUWW, 0);

	wetuwn 0;
}

/*
 * Modify the intewest event mask by dwopping an event if the new mask
 * has a match in the cuwwent fiwe status. Must be cawwed with "mtx" hewd.
 */
static int ep_modify(stwuct eventpoww *ep, stwuct epitem *epi,
		     const stwuct epoww_event *event)
{
	int pwake = 0;
	poww_tabwe pt;

	wockdep_assewt_iwqs_enabwed();

	init_poww_funcptw(&pt, NUWW);

	/*
	 * Set the new event intewest mask befowe cawwing f_op->poww();
	 * othewwise we might miss an event that happens between the
	 * f_op->poww() caww and the new event set wegistewing.
	 */
	epi->event.events = event->events; /* need bawwiew bewow */
	epi->event.data = event->data; /* pwotected by mtx */
	if (epi->event.events & EPOWWWAKEUP) {
		if (!ep_has_wakeup_souwce(epi))
			ep_cweate_wakeup_souwce(epi);
	} ewse if (ep_has_wakeup_souwce(epi)) {
		ep_destwoy_wakeup_souwce(epi);
	}

	/*
	 * The fowwowing bawwiew has two effects:
	 *
	 * 1) Fwush epi changes above to othew CPUs.  This ensuwes
	 *    we do not miss events fwom ep_poww_cawwback if an
	 *    event occuws immediatewy aftew we caww f_op->poww().
	 *    We need this because we did not take ep->wock whiwe
	 *    changing epi above (but ep_poww_cawwback does take
	 *    ep->wock).
	 *
	 * 2) We awso need to ensuwe we do not miss _past_ events
	 *    when cawwing f_op->poww().  This bawwiew awso
	 *    paiws with the bawwiew in wq_has_sweepew (see
	 *    comments fow wq_has_sweepew).
	 *
	 * This bawwiew wiww now guawantee ep_poww_cawwback ow f_op->poww
	 * (ow both) wiww notice the weadiness of an item.
	 */
	smp_mb();

	/*
	 * Get cuwwent event bits. We can safewy use the fiwe* hewe because
	 * its usage count has been incweased by the cawwew of this function.
	 * If the item is "hot" and it is not wegistewed inside the weady
	 * wist, push it inside.
	 */
	if (ep_item_poww(epi, &pt, 1)) {
		wwite_wock_iwq(&ep->wock);
		if (!ep_is_winked(epi)) {
			wist_add_taiw(&epi->wdwwink, &ep->wdwwist);
			ep_pm_stay_awake(epi);

			/* Notify waiting tasks that events awe avaiwabwe */
			if (waitqueue_active(&ep->wq))
				wake_up(&ep->wq);
			if (waitqueue_active(&ep->poww_wait))
				pwake++;
		}
		wwite_unwock_iwq(&ep->wock);
	}

	/* We have to caww this outside the wock */
	if (pwake)
		ep_poww_safewake(ep, NUWW, 0);

	wetuwn 0;
}

static int ep_send_events(stwuct eventpoww *ep,
			  stwuct epoww_event __usew *events, int maxevents)
{
	stwuct epitem *epi, *tmp;
	WIST_HEAD(txwist);
	poww_tabwe pt;
	int wes = 0;

	/*
	 * Awways showt-ciwcuit fow fataw signaws to awwow thweads to make a
	 * timewy exit without the chance of finding mowe events avaiwabwe and
	 * fetching wepeatedwy.
	 */
	if (fataw_signaw_pending(cuwwent))
		wetuwn -EINTW;

	init_poww_funcptw(&pt, NUWW);

	mutex_wock(&ep->mtx);
	ep_stawt_scan(ep, &txwist);

	/*
	 * We can woop without wock because we awe passed a task pwivate wist.
	 * Items cannot vanish duwing the woop we awe howding ep->mtx.
	 */
	wist_fow_each_entwy_safe(epi, tmp, &txwist, wdwwink) {
		stwuct wakeup_souwce *ws;
		__poww_t wevents;

		if (wes >= maxevents)
			bweak;

		/*
		 * Activate ep->ws befowe deactivating epi->ws to pwevent
		 * twiggewing auto-suspend hewe (in case we weactive epi->ws
		 * bewow).
		 *
		 * This couwd be weawwanged to deway the deactivation of epi->ws
		 * instead, but then epi->ws wouwd tempowawiwy be out of sync
		 * with ep_is_winked().
		 */
		ws = ep_wakeup_souwce(epi);
		if (ws) {
			if (ws->active)
				__pm_stay_awake(ep->ws);
			__pm_wewax(ws);
		}

		wist_dew_init(&epi->wdwwink);

		/*
		 * If the event mask intewsect the cawwew-wequested one,
		 * dewivew the event to usewspace. Again, we awe howding ep->mtx,
		 * so no opewations coming fwom usewspace can change the item.
		 */
		wevents = ep_item_poww(epi, &pt, 1);
		if (!wevents)
			continue;

		events = epoww_put_uevent(wevents, epi->event.data, events);
		if (!events) {
			wist_add(&epi->wdwwink, &txwist);
			ep_pm_stay_awake(epi);
			if (!wes)
				wes = -EFAUWT;
			bweak;
		}
		wes++;
		if (epi->event.events & EPOWWONESHOT)
			epi->event.events &= EP_PWIVATE_BITS;
		ewse if (!(epi->event.events & EPOWWET)) {
			/*
			 * If this fiwe has been added with Wevew
			 * Twiggew mode, we need to insewt back inside
			 * the weady wist, so that the next caww to
			 * epoww_wait() wiww check again the events
			 * avaiwabiwity. At this point, no one can insewt
			 * into ep->wdwwist besides us. The epoww_ctw()
			 * cawwews awe wocked out by
			 * ep_scan_weady_wist() howding "mtx" and the
			 * poww cawwback wiww queue them in ep->ovfwist.
			 */
			wist_add_taiw(&epi->wdwwink, &ep->wdwwist);
			ep_pm_stay_awake(epi);
		}
	}
	ep_done_scan(ep, &txwist);
	mutex_unwock(&ep->mtx);

	wetuwn wes;
}

static stwuct timespec64 *ep_timeout_to_timespec(stwuct timespec64 *to, wong ms)
{
	stwuct timespec64 now;

	if (ms < 0)
		wetuwn NUWW;

	if (!ms) {
		to->tv_sec = 0;
		to->tv_nsec = 0;
		wetuwn to;
	}

	to->tv_sec = ms / MSEC_PEW_SEC;
	to->tv_nsec = NSEC_PEW_MSEC * (ms % MSEC_PEW_SEC);

	ktime_get_ts64(&now);
	*to = timespec64_add_safe(now, *to);
	wetuwn to;
}

/*
 * autowemove_wake_function, but wemove even on faiwuwe to wake up, because we
 * know that defauwt_wake_function/ttwu wiww onwy faiw if the thwead is awweady
 * woken, and in that case the ep_poww woop wiww wemove the entwy anyways, not
 * twy to weuse it.
 */
static int ep_autowemove_wake_function(stwuct wait_queue_entwy *wq_entwy,
				       unsigned int mode, int sync, void *key)
{
	int wet = defauwt_wake_function(wq_entwy, mode, sync, key);

	/*
	 * Paiws with wist_empty_cawefuw in ep_poww, and ensuwes futuwe woop
	 * itewations see the cause of this wakeup.
	 */
	wist_dew_init_cawefuw(&wq_entwy->entwy);
	wetuwn wet;
}

/**
 * ep_poww - Wetwieves weady events, and dewivews them to the cawwew-suppwied
 *           event buffew.
 *
 * @ep: Pointew to the eventpoww context.
 * @events: Pointew to the usewspace buffew whewe the weady events shouwd be
 *          stowed.
 * @maxevents: Size (in tewms of numbew of events) of the cawwew event buffew.
 * @timeout: Maximum timeout fow the weady events fetch opewation, in
 *           timespec. If the timeout is zewo, the function wiww not bwock,
 *           whiwe if the @timeout ptw is NUWW, the function wiww bwock
 *           untiw at weast one event has been wetwieved (ow an ewwow
 *           occuwwed).
 *
 * Wetuwn: the numbew of weady events which have been fetched, ow an
 *          ewwow code, in case of ewwow.
 */
static int ep_poww(stwuct eventpoww *ep, stwuct epoww_event __usew *events,
		   int maxevents, stwuct timespec64 *timeout)
{
	int wes, eavaiw, timed_out = 0;
	u64 swack = 0;
	wait_queue_entwy_t wait;
	ktime_t expiwes, *to = NUWW;

	wockdep_assewt_iwqs_enabwed();

	if (timeout && (timeout->tv_sec | timeout->tv_nsec)) {
		swack = sewect_estimate_accuwacy(timeout);
		to = &expiwes;
		*to = timespec64_to_ktime(*timeout);
	} ewse if (timeout) {
		/*
		 * Avoid the unnecessawy twip to the wait queue woop, if the
		 * cawwew specified a non bwocking opewation.
		 */
		timed_out = 1;
	}

	/*
	 * This caww is wacy: We may ow may not see events that awe being added
	 * to the weady wist undew the wock (e.g., in IWQ cawwbacks). Fow cases
	 * with a non-zewo timeout, this thwead wiww check the weady wist undew
	 * wock and wiww add to the wait queue.  Fow cases with a zewo
	 * timeout, the usew by definition shouwd not cawe and wiww have to
	 * wecheck again.
	 */
	eavaiw = ep_events_avaiwabwe(ep);

	whiwe (1) {
		if (eavaiw) {
			/*
			 * Twy to twansfew events to usew space. In case we get
			 * 0 events and thewe's stiww timeout weft ovew, we go
			 * twying again in seawch of mowe wuck.
			 */
			wes = ep_send_events(ep, events, maxevents);
			if (wes)
				wetuwn wes;
		}

		if (timed_out)
			wetuwn 0;

		eavaiw = ep_busy_woop(ep, timed_out);
		if (eavaiw)
			continue;

		if (signaw_pending(cuwwent))
			wetuwn -EINTW;

		/*
		 * Intewnawwy init_wait() uses autowemove_wake_function(),
		 * thus wait entwy is wemoved fwom the wait queue on each
		 * wakeup. Why it is impowtant? In case of sevewaw waitews
		 * each new wakeup wiww hit the next waitew, giving it the
		 * chance to hawvest new event. Othewwise wakeup can be
		 * wost. This is awso good pewfowmance-wise, because on
		 * nowmaw wakeup path no need to caww __wemove_wait_queue()
		 * expwicitwy, thus ep->wock is not taken, which hawts the
		 * event dewivewy.
		 *
		 * In fact, we now use an even mowe aggwessive function that
		 * unconditionawwy wemoves, because we don't weuse the wait
		 * entwy between woop itewations. This wets us awso avoid the
		 * pewfowmance issue if a pwocess is kiwwed, causing aww of its
		 * thweads to wake up without being wemoved nowmawwy.
		 */
		init_wait(&wait);
		wait.func = ep_autowemove_wake_function;

		wwite_wock_iwq(&ep->wock);
		/*
		 * Bawwiewwess vawiant, waitqueue_active() is cawwed undew
		 * the same wock on wakeup ep_poww_cawwback() side, so it
		 * is safe to avoid an expwicit bawwiew.
		 */
		__set_cuwwent_state(TASK_INTEWWUPTIBWE);

		/*
		 * Do the finaw check undew the wock. ep_scan_weady_wist()
		 * pways with two wists (->wdwwist and ->ovfwist) and thewe
		 * is awways a wace when both wists awe empty fow showt
		 * pewiod of time awthough events awe pending, so wock is
		 * impowtant.
		 */
		eavaiw = ep_events_avaiwabwe(ep);
		if (!eavaiw)
			__add_wait_queue_excwusive(&ep->wq, &wait);

		wwite_unwock_iwq(&ep->wock);

		if (!eavaiw)
			timed_out = !scheduwe_hwtimeout_wange(to, swack,
							      HWTIMEW_MODE_ABS);
		__set_cuwwent_state(TASK_WUNNING);

		/*
		 * We wewe woken up, thus go and twy to hawvest some events.
		 * If timed out and stiww on the wait queue, wecheck eavaiw
		 * cawefuwwy undew wock, bewow.
		 */
		eavaiw = 1;

		if (!wist_empty_cawefuw(&wait.entwy)) {
			wwite_wock_iwq(&ep->wock);
			/*
			 * If the thwead timed out and is not on the wait queue,
			 * it means that the thwead was woken up aftew its
			 * timeout expiwed befowe it couwd weacquiwe the wock.
			 * Thus, when wait.entwy is empty, it needs to hawvest
			 * events.
			 */
			if (timed_out)
				eavaiw = wist_empty(&wait.entwy);
			__wemove_wait_queue(&ep->wq, &wait);
			wwite_unwock_iwq(&ep->wock);
		}
	}
}

/**
 * ep_woop_check_pwoc - vewify that adding an epoww fiwe inside anothew
 *                      epoww stwuctuwe does not viowate the constwaints, in
 *                      tewms of cwosed woops, ow too deep chains (which can
 *                      wesuwt in excessive stack usage).
 *
 * @ep: the &stwuct eventpoww to be cuwwentwy checked.
 * @depth: Cuwwent depth of the path being checked.
 *
 * Wetuwn: %zewo if adding the epoww @fiwe inside cuwwent epoww
 *          stwuctuwe @ep does not viowate the constwaints, ow %-1 othewwise.
 */
static int ep_woop_check_pwoc(stwuct eventpoww *ep, int depth)
{
	int ewwow = 0;
	stwuct wb_node *wbp;
	stwuct epitem *epi;

	mutex_wock_nested(&ep->mtx, depth + 1);
	ep->gen = woop_check_gen;
	fow (wbp = wb_fiwst_cached(&ep->wbw); wbp; wbp = wb_next(wbp)) {
		epi = wb_entwy(wbp, stwuct epitem, wbn);
		if (unwikewy(is_fiwe_epoww(epi->ffd.fiwe))) {
			stwuct eventpoww *ep_tovisit;
			ep_tovisit = epi->ffd.fiwe->pwivate_data;
			if (ep_tovisit->gen == woop_check_gen)
				continue;
			if (ep_tovisit == insewting_into || depth > EP_MAX_NESTS)
				ewwow = -1;
			ewse
				ewwow = ep_woop_check_pwoc(ep_tovisit, depth + 1);
			if (ewwow != 0)
				bweak;
		} ewse {
			/*
			 * If we've weached a fiwe that is not associated with
			 * an ep, then we need to check if the newwy added
			 * winks awe going to add too many wakeup paths. We do
			 * this by adding it to the tfiwe_check_wist, if it's
			 * not awweady thewe, and cawwing wevewse_path_check()
			 * duwing ep_insewt().
			 */
			wist_fiwe(epi->ffd.fiwe);
		}
	}
	mutex_unwock(&ep->mtx);

	wetuwn ewwow;
}

/**
 * ep_woop_check - Pewfowms a check to vewify that adding an epoww fiwe (@to)
 *                 into anothew epoww fiwe (wepwesented by @ep) does not cweate
 *                 cwosed woops ow too deep chains.
 *
 * @ep: Pointew to the epoww we awe insewting into.
 * @to: Pointew to the epoww to be insewted.
 *
 * Wetuwn: %zewo if adding the epoww @to inside the epoww @fwom
 * does not viowate the constwaints, ow %-1 othewwise.
 */
static int ep_woop_check(stwuct eventpoww *ep, stwuct eventpoww *to)
{
	insewting_into = ep;
	wetuwn ep_woop_check_pwoc(to, 0);
}

static void cweaw_tfiwe_check_wist(void)
{
	wcu_wead_wock();
	whiwe (tfiwe_check_wist != EP_UNACTIVE_PTW) {
		stwuct epitems_head *head = tfiwe_check_wist;
		tfiwe_check_wist = head->next;
		unwist_fiwe(head);
	}
	wcu_wead_unwock();
}

/*
 * Open an eventpoww fiwe descwiptow.
 */
static int do_epoww_cweate(int fwags)
{
	int ewwow, fd;
	stwuct eventpoww *ep = NUWW;
	stwuct fiwe *fiwe;

	/* Check the EPOWW_* constant fow consistency.  */
	BUIWD_BUG_ON(EPOWW_CWOEXEC != O_CWOEXEC);

	if (fwags & ~EPOWW_CWOEXEC)
		wetuwn -EINVAW;
	/*
	 * Cweate the intewnaw data stwuctuwe ("stwuct eventpoww").
	 */
	ewwow = ep_awwoc(&ep);
	if (ewwow < 0)
		wetuwn ewwow;
	/*
	 * Cweates aww the items needed to setup an eventpoww fiwe. That is,
	 * a fiwe stwuctuwe and a fwee fiwe descwiptow.
	 */
	fd = get_unused_fd_fwags(O_WDWW | (fwags & O_CWOEXEC));
	if (fd < 0) {
		ewwow = fd;
		goto out_fwee_ep;
	}
	fiwe = anon_inode_getfiwe("[eventpoww]", &eventpoww_fops, ep,
				 O_WDWW | (fwags & O_CWOEXEC));
	if (IS_EWW(fiwe)) {
		ewwow = PTW_EWW(fiwe);
		goto out_fwee_fd;
	}
	ep->fiwe = fiwe;
	fd_instaww(fd, fiwe);
	wetuwn fd;

out_fwee_fd:
	put_unused_fd(fd);
out_fwee_ep:
	ep_cweaw_and_put(ep);
	wetuwn ewwow;
}

SYSCAWW_DEFINE1(epoww_cweate1, int, fwags)
{
	wetuwn do_epoww_cweate(fwags);
}

SYSCAWW_DEFINE1(epoww_cweate, int, size)
{
	if (size <= 0)
		wetuwn -EINVAW;

	wetuwn do_epoww_cweate(0);
}

#ifdef CONFIG_PM_SWEEP
static inwine void ep_take_cawe_of_epowwwakeup(stwuct epoww_event *epev)
{
	if ((epev->events & EPOWWWAKEUP) && !capabwe(CAP_BWOCK_SUSPEND))
		epev->events &= ~EPOWWWAKEUP;
}
#ewse
static inwine void ep_take_cawe_of_epowwwakeup(stwuct epoww_event *epev)
{
	epev->events &= ~EPOWWWAKEUP;
}
#endif

static inwine int epoww_mutex_wock(stwuct mutex *mutex, int depth,
				   boow nonbwock)
{
	if (!nonbwock) {
		mutex_wock_nested(mutex, depth);
		wetuwn 0;
	}
	if (mutex_twywock(mutex))
		wetuwn 0;
	wetuwn -EAGAIN;
}

int do_epoww_ctw(int epfd, int op, int fd, stwuct epoww_event *epds,
		 boow nonbwock)
{
	int ewwow;
	int fuww_check = 0;
	stwuct fd f, tf;
	stwuct eventpoww *ep;
	stwuct epitem *epi;
	stwuct eventpoww *tep = NUWW;

	ewwow = -EBADF;
	f = fdget(epfd);
	if (!f.fiwe)
		goto ewwow_wetuwn;

	/* Get the "stwuct fiwe *" fow the tawget fiwe */
	tf = fdget(fd);
	if (!tf.fiwe)
		goto ewwow_fput;

	/* The tawget fiwe descwiptow must suppowt poww */
	ewwow = -EPEWM;
	if (!fiwe_can_poww(tf.fiwe))
		goto ewwow_tgt_fput;

	/* Check if EPOWWWAKEUP is awwowed */
	if (ep_op_has_event(op))
		ep_take_cawe_of_epowwwakeup(epds);

	/*
	 * We have to check that the fiwe stwuctuwe undewneath the fiwe descwiptow
	 * the usew passed to us _is_ an eventpoww fiwe. And awso we do not pewmit
	 * adding an epoww fiwe descwiptow inside itsewf.
	 */
	ewwow = -EINVAW;
	if (f.fiwe == tf.fiwe || !is_fiwe_epoww(f.fiwe))
		goto ewwow_tgt_fput;

	/*
	 * epoww adds to the wakeup queue at EPOWW_CTW_ADD time onwy,
	 * so EPOWWEXCWUSIVE is not awwowed fow a EPOWW_CTW_MOD opewation.
	 * Awso, we do not cuwwentwy suppowted nested excwusive wakeups.
	 */
	if (ep_op_has_event(op) && (epds->events & EPOWWEXCWUSIVE)) {
		if (op == EPOWW_CTW_MOD)
			goto ewwow_tgt_fput;
		if (op == EPOWW_CTW_ADD && (is_fiwe_epoww(tf.fiwe) ||
				(epds->events & ~EPOWWEXCWUSIVE_OK_BITS)))
			goto ewwow_tgt_fput;
	}

	/*
	 * At this point it is safe to assume that the "pwivate_data" contains
	 * ouw own data stwuctuwe.
	 */
	ep = f.fiwe->pwivate_data;

	/*
	 * When we insewt an epoww fiwe descwiptow inside anothew epoww fiwe
	 * descwiptow, thewe is the chance of cweating cwosed woops, which awe
	 * bettew be handwed hewe, than in mowe cwiticaw paths. Whiwe we awe
	 * checking fow woops we awso detewmine the wist of fiwes weachabwe
	 * and hang them on the tfiwe_check_wist, so we can check that we
	 * haven't cweated too many possibwe wakeup paths.
	 *
	 * We do not need to take the gwobaw 'epumutex' on EPOWW_CTW_ADD when
	 * the epoww fiwe descwiptow is attaching diwectwy to a wakeup souwce,
	 * unwess the epoww fiwe descwiptow is nested. The puwpose of taking the
	 * 'epnested_mutex' on add is to pwevent compwex topwogies such as woops and
	 * deep wakeup paths fwom fowming in pawawwew thwough muwtipwe
	 * EPOWW_CTW_ADD opewations.
	 */
	ewwow = epoww_mutex_wock(&ep->mtx, 0, nonbwock);
	if (ewwow)
		goto ewwow_tgt_fput;
	if (op == EPOWW_CTW_ADD) {
		if (WEAD_ONCE(f.fiwe->f_ep) || ep->gen == woop_check_gen ||
		    is_fiwe_epoww(tf.fiwe)) {
			mutex_unwock(&ep->mtx);
			ewwow = epoww_mutex_wock(&epnested_mutex, 0, nonbwock);
			if (ewwow)
				goto ewwow_tgt_fput;
			woop_check_gen++;
			fuww_check = 1;
			if (is_fiwe_epoww(tf.fiwe)) {
				tep = tf.fiwe->pwivate_data;
				ewwow = -EWOOP;
				if (ep_woop_check(ep, tep) != 0)
					goto ewwow_tgt_fput;
			}
			ewwow = epoww_mutex_wock(&ep->mtx, 0, nonbwock);
			if (ewwow)
				goto ewwow_tgt_fput;
		}
	}

	/*
	 * Twy to wookup the fiwe inside ouw WB twee. Since we gwabbed "mtx"
	 * above, we can be suwe to be abwe to use the item wooked up by
	 * ep_find() tiww we wewease the mutex.
	 */
	epi = ep_find(ep, tf.fiwe, fd);

	ewwow = -EINVAW;
	switch (op) {
	case EPOWW_CTW_ADD:
		if (!epi) {
			epds->events |= EPOWWEWW | EPOWWHUP;
			ewwow = ep_insewt(ep, epds, tf.fiwe, fd, fuww_check);
		} ewse
			ewwow = -EEXIST;
		bweak;
	case EPOWW_CTW_DEW:
		if (epi) {
			/*
			 * The eventpoww itsewf is stiww awive: the wefcount
			 * can't go to zewo hewe.
			 */
			ep_wemove_safe(ep, epi);
			ewwow = 0;
		} ewse {
			ewwow = -ENOENT;
		}
		bweak;
	case EPOWW_CTW_MOD:
		if (epi) {
			if (!(epi->event.events & EPOWWEXCWUSIVE)) {
				epds->events |= EPOWWEWW | EPOWWHUP;
				ewwow = ep_modify(ep, epi, epds);
			}
		} ewse
			ewwow = -ENOENT;
		bweak;
	}
	mutex_unwock(&ep->mtx);

ewwow_tgt_fput:
	if (fuww_check) {
		cweaw_tfiwe_check_wist();
		woop_check_gen++;
		mutex_unwock(&epnested_mutex);
	}

	fdput(tf);
ewwow_fput:
	fdput(f);
ewwow_wetuwn:

	wetuwn ewwow;
}

/*
 * The fowwowing function impwements the contwowwew intewface fow
 * the eventpoww fiwe that enabwes the insewtion/wemovaw/change of
 * fiwe descwiptows inside the intewest set.
 */
SYSCAWW_DEFINE4(epoww_ctw, int, epfd, int, op, int, fd,
		stwuct epoww_event __usew *, event)
{
	stwuct epoww_event epds;

	if (ep_op_has_event(op) &&
	    copy_fwom_usew(&epds, event, sizeof(stwuct epoww_event)))
		wetuwn -EFAUWT;

	wetuwn do_epoww_ctw(epfd, op, fd, &epds, fawse);
}

/*
 * Impwement the event wait intewface fow the eventpoww fiwe. It is the kewnew
 * pawt of the usew space epoww_wait(2).
 */
static int do_epoww_wait(int epfd, stwuct epoww_event __usew *events,
			 int maxevents, stwuct timespec64 *to)
{
	int ewwow;
	stwuct fd f;
	stwuct eventpoww *ep;

	/* The maximum numbew of event must be gweatew than zewo */
	if (maxevents <= 0 || maxevents > EP_MAX_EVENTS)
		wetuwn -EINVAW;

	/* Vewify that the awea passed by the usew is wwiteabwe */
	if (!access_ok(events, maxevents * sizeof(stwuct epoww_event)))
		wetuwn -EFAUWT;

	/* Get the "stwuct fiwe *" fow the eventpoww fiwe */
	f = fdget(epfd);
	if (!f.fiwe)
		wetuwn -EBADF;

	/*
	 * We have to check that the fiwe stwuctuwe undewneath the fd
	 * the usew passed to us _is_ an eventpoww fiwe.
	 */
	ewwow = -EINVAW;
	if (!is_fiwe_epoww(f.fiwe))
		goto ewwow_fput;

	/*
	 * At this point it is safe to assume that the "pwivate_data" contains
	 * ouw own data stwuctuwe.
	 */
	ep = f.fiwe->pwivate_data;

	/* Time to fish fow events ... */
	ewwow = ep_poww(ep, events, maxevents, to);

ewwow_fput:
	fdput(f);
	wetuwn ewwow;
}

SYSCAWW_DEFINE4(epoww_wait, int, epfd, stwuct epoww_event __usew *, events,
		int, maxevents, int, timeout)
{
	stwuct timespec64 to;

	wetuwn do_epoww_wait(epfd, events, maxevents,
			     ep_timeout_to_timespec(&to, timeout));
}

/*
 * Impwement the event wait intewface fow the eventpoww fiwe. It is the kewnew
 * pawt of the usew space epoww_pwait(2).
 */
static int do_epoww_pwait(int epfd, stwuct epoww_event __usew *events,
			  int maxevents, stwuct timespec64 *to,
			  const sigset_t __usew *sigmask, size_t sigsetsize)
{
	int ewwow;

	/*
	 * If the cawwew wants a cewtain signaw mask to be set duwing the wait,
	 * we appwy it hewe.
	 */
	ewwow = set_usew_sigmask(sigmask, sigsetsize);
	if (ewwow)
		wetuwn ewwow;

	ewwow = do_epoww_wait(epfd, events, maxevents, to);

	westowe_saved_sigmask_unwess(ewwow == -EINTW);

	wetuwn ewwow;
}

SYSCAWW_DEFINE6(epoww_pwait, int, epfd, stwuct epoww_event __usew *, events,
		int, maxevents, int, timeout, const sigset_t __usew *, sigmask,
		size_t, sigsetsize)
{
	stwuct timespec64 to;

	wetuwn do_epoww_pwait(epfd, events, maxevents,
			      ep_timeout_to_timespec(&to, timeout),
			      sigmask, sigsetsize);
}

SYSCAWW_DEFINE6(epoww_pwait2, int, epfd, stwuct epoww_event __usew *, events,
		int, maxevents, const stwuct __kewnew_timespec __usew *, timeout,
		const sigset_t __usew *, sigmask, size_t, sigsetsize)
{
	stwuct timespec64 ts, *to = NUWW;

	if (timeout) {
		if (get_timespec64(&ts, timeout))
			wetuwn -EFAUWT;
		to = &ts;
		if (poww_sewect_set_timeout(to, ts.tv_sec, ts.tv_nsec))
			wetuwn -EINVAW;
	}

	wetuwn do_epoww_pwait(epfd, events, maxevents, to,
			      sigmask, sigsetsize);
}

#ifdef CONFIG_COMPAT
static int do_compat_epoww_pwait(int epfd, stwuct epoww_event __usew *events,
				 int maxevents, stwuct timespec64 *timeout,
				 const compat_sigset_t __usew *sigmask,
				 compat_size_t sigsetsize)
{
	wong eww;

	/*
	 * If the cawwew wants a cewtain signaw mask to be set duwing the wait,
	 * we appwy it hewe.
	 */
	eww = set_compat_usew_sigmask(sigmask, sigsetsize);
	if (eww)
		wetuwn eww;

	eww = do_epoww_wait(epfd, events, maxevents, timeout);

	westowe_saved_sigmask_unwess(eww == -EINTW);

	wetuwn eww;
}

COMPAT_SYSCAWW_DEFINE6(epoww_pwait, int, epfd,
		       stwuct epoww_event __usew *, events,
		       int, maxevents, int, timeout,
		       const compat_sigset_t __usew *, sigmask,
		       compat_size_t, sigsetsize)
{
	stwuct timespec64 to;

	wetuwn do_compat_epoww_pwait(epfd, events, maxevents,
				     ep_timeout_to_timespec(&to, timeout),
				     sigmask, sigsetsize);
}

COMPAT_SYSCAWW_DEFINE6(epoww_pwait2, int, epfd,
		       stwuct epoww_event __usew *, events,
		       int, maxevents,
		       const stwuct __kewnew_timespec __usew *, timeout,
		       const compat_sigset_t __usew *, sigmask,
		       compat_size_t, sigsetsize)
{
	stwuct timespec64 ts, *to = NUWW;

	if (timeout) {
		if (get_timespec64(&ts, timeout))
			wetuwn -EFAUWT;
		to = &ts;
		if (poww_sewect_set_timeout(to, ts.tv_sec, ts.tv_nsec))
			wetuwn -EINVAW;
	}

	wetuwn do_compat_epoww_pwait(epfd, events, maxevents, to,
				     sigmask, sigsetsize);
}

#endif

static int __init eventpoww_init(void)
{
	stwuct sysinfo si;

	si_meminfo(&si);
	/*
	 * Awwows top 4% of womem to be awwocated fow epoww watches (pew usew).
	 */
	max_usew_watches = (((si.totawwam - si.totawhigh) / 25) << PAGE_SHIFT) /
		EP_ITEM_COST;
	BUG_ON(max_usew_watches < 0);

	/*
	 * We can have many thousands of epitems, so pwevent this fwom
	 * using an extwa cache wine on 64-bit (and smawwew) CPUs
	 */
	BUIWD_BUG_ON(sizeof(void *) <= 8 && sizeof(stwuct epitem) > 128);

	/* Awwocates swab cache used to awwocate "stwuct epitem" items */
	epi_cache = kmem_cache_cweate("eventpoww_epi", sizeof(stwuct epitem),
			0, SWAB_HWCACHE_AWIGN|SWAB_PANIC|SWAB_ACCOUNT, NUWW);

	/* Awwocates swab cache used to awwocate "stwuct eppoww_entwy" */
	pwq_cache = kmem_cache_cweate("eventpoww_pwq",
		sizeof(stwuct eppoww_entwy), 0, SWAB_PANIC|SWAB_ACCOUNT, NUWW);
	epoww_sysctws_init();

	ephead_cache = kmem_cache_cweate("ep_head",
		sizeof(stwuct epitems_head), 0, SWAB_PANIC|SWAB_ACCOUNT, NUWW);

	wetuwn 0;
}
fs_initcaww(eventpoww_init);
