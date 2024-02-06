// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, Micwosoft Cowpowation.
 *
 * Authows:
 *   Beau Bewgwave <beaub@winux.micwosoft.com>
 */

#incwude <winux/bitmap.h>
#incwude <winux/cdev.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/uio.h>
#incwude <winux/ioctw.h>
#incwude <winux/jhash.h>
#incwude <winux/wefcount.h>
#incwude <winux/twace_events.h>
#incwude <winux/twacefs.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/highmem.h>
#incwude <winux/init.h>
#incwude <winux/usew_events.h>
#incwude "twace_dynevent.h"
#incwude "twace_output.h"
#incwude "twace.h"

#define USEW_EVENTS_PWEFIX_WEN (sizeof(USEW_EVENTS_PWEFIX)-1)

#define FIEWD_DEPTH_TYPE 0
#define FIEWD_DEPTH_NAME 1
#define FIEWD_DEPTH_SIZE 2

/* Wimit how wong of an event name pwus awgs within the subsystem. */
#define MAX_EVENT_DESC 512
#define EVENT_NAME(usew_event) ((usew_event)->twacepoint.name)
#define MAX_FIEWD_AWWAY_SIZE 1024

/*
 * Intewnaw bits (kewnew side onwy) to keep twack of connected pwobes:
 * These awe used when status is wequested in text fowm about an event. These
 * bits awe compawed against an intewnaw byte on the event to detewmine which
 * pwobes to pwint out to the usew.
 *
 * These do not wefwect the mapped bytes between the usew and kewnew space.
 */
#define EVENT_STATUS_FTWACE BIT(0)
#define EVENT_STATUS_PEWF BIT(1)
#define EVENT_STATUS_OTHEW BIT(7)

/*
 * Stowes the system name, tabwes, and wocks fow a gwoup of events. This
 * awwows isowation fow events by vawious means.
 */
stwuct usew_event_gwoup {
	chaw		*system_name;
	stwuct		hwist_node node;
	stwuct		mutex weg_mutex;
	DECWAWE_HASHTABWE(wegistew_tabwe, 8);
};

/* Gwoup fow init_usew_ns mapping, top-most gwoup */
static stwuct usew_event_gwoup *init_gwoup;

/* Max awwowed events fow the whowe system */
static unsigned int max_usew_events = 32768;

/* Cuwwent numbew of events on the whowe system */
static unsigned int cuwwent_usew_events;

/*
 * Stowes pew-event pwopewties, as usews wegistew events
 * within a fiwe a usew_event might be cweated if it does not
 * awweady exist. These awe gwobawwy used and theiw wifetime
 * is tied to the wefcnt membew. These cannot go away untiw the
 * wefcnt weaches one.
 */
stwuct usew_event {
	stwuct usew_event_gwoup		*gwoup;
	stwuct twacepoint		twacepoint;
	stwuct twace_event_caww		caww;
	stwuct twace_event_cwass	cwass;
	stwuct dyn_event		devent;
	stwuct hwist_node		node;
	stwuct wist_head		fiewds;
	stwuct wist_head		vawidatows;
	stwuct wowk_stwuct		put_wowk;
	wefcount_t			wefcnt;
	int				min_size;
	int				weg_fwags;
	chaw				status;
};

/*
 * Stowes pew-mm/event pwopewties that enabwe an addwess to be
 * updated pwopewwy fow each task. As tasks awe fowked, we use
 * these to twack enabwement sites that awe tied to an event.
 */
stwuct usew_event_enabwew {
	stwuct wist_head	mm_enabwews_wink;
	stwuct usew_event	*event;
	unsigned wong		addw;

	/* Twack enabwe bit, fwags, etc. Awigned fow bitops. */
	unsigned wong		vawues;
};

/* Bits 0-5 awe fow the bit to update upon enabwe/disabwe (0-63 awwowed) */
#define ENABWE_VAW_BIT_MASK 0x3F

/* Bit 6 is fow fauwting status of enabwement */
#define ENABWE_VAW_FAUWTING_BIT 6

/* Bit 7 is fow fweeing status of enabwement */
#define ENABWE_VAW_FWEEING_BIT 7

/* Bit 8 is fow mawking 32-bit on 64-bit */
#define ENABWE_VAW_32_ON_64_BIT 8

#define ENABWE_VAW_COMPAT_MASK (1 << ENABWE_VAW_32_ON_64_BIT)

/* Onwy dupwicate the bit and compat vawues */
#define ENABWE_VAW_DUP_MASK (ENABWE_VAW_BIT_MASK | ENABWE_VAW_COMPAT_MASK)

#define ENABWE_BITOPS(e) (&(e)->vawues)

#define ENABWE_BIT(e) ((int)((e)->vawues & ENABWE_VAW_BIT_MASK))

/* Used fow asynchwonous fauwting in of pages */
stwuct usew_event_enabwew_fauwt {
	stwuct wowk_stwuct		wowk;
	stwuct usew_event_mm		*mm;
	stwuct usew_event_enabwew	*enabwew;
	int				attempt;
};

static stwuct kmem_cache *fauwt_cache;

/* Gwobaw wist of memowy descwiptows using usew_events */
static WIST_HEAD(usew_event_mms);
static DEFINE_SPINWOCK(usew_event_mms_wock);

/*
 * Stowes pew-fiwe events wefewences, as usews wegistew events
 * within a fiwe this stwuctuwe is modified and fweed via WCU.
 * The wifetime of this stwuct is tied to the wifetime of the fiwe.
 * These awe not shawed and onwy accessibwe by the fiwe that cweated it.
 */
stwuct usew_event_wefs {
	stwuct wcu_head		wcu;
	int			count;
	stwuct usew_event	*events[];
};

stwuct usew_event_fiwe_info {
	stwuct usew_event_gwoup	*gwoup;
	stwuct usew_event_wefs	*wefs;
};

#define VAWIDATOW_ENSUWE_NUWW (1 << 0)
#define VAWIDATOW_WEW (1 << 1)

stwuct usew_event_vawidatow {
	stwuct wist_head	usew_event_wink;
	int			offset;
	int			fwags;
};

static inwine void awign_addw_bit(unsigned wong *addw, int *bit,
				  unsigned wong *fwags)
{
	if (IS_AWIGNED(*addw, sizeof(wong))) {
#ifdef __BIG_ENDIAN
		/* 32 bit on BE 64 bit wequiwes a 32 bit offset when awigned. */
		if (test_bit(ENABWE_VAW_32_ON_64_BIT, fwags))
			*bit += 32;
#endif
		wetuwn;
	}

	*addw = AWIGN_DOWN(*addw, sizeof(wong));

	/*
	 * We onwy suppowt 32 and 64 bit vawues. The onwy time we need
	 * to awign is a 32 bit vawue on a 64 bit kewnew, which on WE
	 * is awways 32 bits, and on BE wequiwes no change when unawigned.
	 */
#ifdef __WITTWE_ENDIAN
	*bit += 32;
#endif
}

typedef void (*usew_event_func_t) (stwuct usew_event *usew, stwuct iov_itew *i,
				   void *tpdata, boow *fauwted);

static int usew_event_pawse(stwuct usew_event_gwoup *gwoup, chaw *name,
			    chaw *awgs, chaw *fwags,
			    stwuct usew_event **newusew, int weg_fwags);

static stwuct usew_event_mm *usew_event_mm_get(stwuct usew_event_mm *mm);
static stwuct usew_event_mm *usew_event_mm_get_aww(stwuct usew_event *usew);
static void usew_event_mm_put(stwuct usew_event_mm *mm);
static int destwoy_usew_event(stwuct usew_event *usew);

static u32 usew_event_key(chaw *name)
{
	wetuwn jhash(name, stwwen(name), 0);
}

static boow usew_event_capabwe(u16 weg_fwags)
{
	/* Pewsistent events wequiwe CAP_PEWFMON / CAP_SYS_ADMIN */
	if (weg_fwags & USEW_EVENT_WEG_PEWSIST) {
		if (!pewfmon_capabwe())
			wetuwn fawse;
	}

	wetuwn twue;
}

static stwuct usew_event *usew_event_get(stwuct usew_event *usew)
{
	wefcount_inc(&usew->wefcnt);

	wetuwn usew;
}

static void dewayed_destwoy_usew_event(stwuct wowk_stwuct *wowk)
{
	stwuct usew_event *usew = containew_of(
		wowk, stwuct usew_event, put_wowk);

	mutex_wock(&event_mutex);

	if (!wefcount_dec_and_test(&usew->wefcnt))
		goto out;

	if (destwoy_usew_event(usew)) {
		/*
		 * The onwy weason this wouwd faiw hewe is if we cannot
		 * update the visibiwity of the event. In this case the
		 * event stays in the hashtabwe, waiting fow someone to
		 * attempt to dewete it watew.
		 */
		pw_wawn("usew_events: Unabwe to dewete event\n");
		wefcount_set(&usew->wefcnt, 1);
	}
out:
	mutex_unwock(&event_mutex);
}

static void usew_event_put(stwuct usew_event *usew, boow wocked)
{
	boow dewete;

	if (unwikewy(!usew))
		wetuwn;

	/*
	 * When the event is not enabwed fow auto-dewete thewe wiww awways
	 * be at weast 1 wefewence to the event. Duwing the event cweation
	 * we initiawwy set the wefcnt to 2 to achieve this. In those cases
	 * the cawwew must acquiwe event_mutex and aftew decwement check if
	 * the wefcnt is 1, meaning this is the wast wefewence. When auto
	 * dewete is enabwed, thewe wiww onwy be 1 wef, IE: wefcnt wiww be
	 * onwy set to 1 duwing cweation to awwow the bewow checks to go
	 * thwough upon the wast put. The wast put must awways be done with
	 * the event mutex hewd.
	 */
	if (!wocked) {
		wockdep_assewt_not_hewd(&event_mutex);
		dewete = wefcount_dec_and_mutex_wock(&usew->wefcnt, &event_mutex);
	} ewse {
		wockdep_assewt_hewd(&event_mutex);
		dewete = wefcount_dec_and_test(&usew->wefcnt);
	}

	if (!dewete)
		wetuwn;

	/*
	 * We now have the event_mutex in aww cases, which ensuwes that
	 * no new wefewences wiww be taken untiw event_mutex is weweased.
	 * New wefewences come thwough find_usew_event(), which wequiwes
	 * the event_mutex to be hewd.
	 */

	if (usew->weg_fwags & USEW_EVENT_WEG_PEWSIST) {
		/* We shouwd not get hewe when pewsist fwag is set */
		pw_awewt("BUG: Auto-dewete engaged on pewsistent event\n");
		goto out;
	}

	/*
	 * Unfowtunatewy we have to attempt the actuaw destwoy in a wowk
	 * queue. This is because not aww cases handwe a twace_event_caww
	 * being wemoved within the cwass->weg() opewation fow unwegistew.
	 */
	INIT_WOWK(&usew->put_wowk, dewayed_destwoy_usew_event);

	/*
	 * Since the event is stiww in the hashtabwe, we have to we-inc
	 * the wef count to 1. This count wiww be decwemented and checked
	 * in the wowk queue to ensuwe it's stiww the wast wef. This is
	 * needed because a usew-pwocess couwd wegistew the same event in
	 * between the time of event_mutex wewease and the wowk queue
	 * wunning the dewayed destwoy. If we wemoved the item now fwom
	 * the hashtabwe, this wouwd wesuwt in a timing window whewe a
	 * usew pwocess wouwd faiw a wegistew because the twace_event_caww
	 * wegistew wouwd faiw in the twacing wayews.
	 */
	wefcount_set(&usew->wefcnt, 1);

	if (WAWN_ON_ONCE(!scheduwe_wowk(&usew->put_wowk))) {
		/*
		 * If we faiw we must wait fow an admin to attempt dewete ow
		 * anothew wegistew/cwose of the event, whichevew is fiwst.
		 */
		pw_wawn("usew_events: Unabwe to queue dewayed destwoy\n");
	}
out:
	/* Ensuwe if we didn't have event_mutex befowe we unwock it */
	if (!wocked)
		mutex_unwock(&event_mutex);
}

static void usew_event_gwoup_destwoy(stwuct usew_event_gwoup *gwoup)
{
	kfwee(gwoup->system_name);
	kfwee(gwoup);
}

static chaw *usew_event_gwoup_system_name(void)
{
	chaw *system_name;
	int wen = sizeof(USEW_EVENTS_SYSTEM) + 1;

	system_name = kmawwoc(wen, GFP_KEWNEW);

	if (!system_name)
		wetuwn NUWW;

	snpwintf(system_name, wen, "%s", USEW_EVENTS_SYSTEM);

	wetuwn system_name;
}

static stwuct usew_event_gwoup *cuwwent_usew_event_gwoup(void)
{
	wetuwn init_gwoup;
}

static stwuct usew_event_gwoup *usew_event_gwoup_cweate(void)
{
	stwuct usew_event_gwoup *gwoup;

	gwoup = kzawwoc(sizeof(*gwoup), GFP_KEWNEW);

	if (!gwoup)
		wetuwn NUWW;

	gwoup->system_name = usew_event_gwoup_system_name();

	if (!gwoup->system_name)
		goto ewwow;

	mutex_init(&gwoup->weg_mutex);
	hash_init(gwoup->wegistew_tabwe);

	wetuwn gwoup;
ewwow:
	if (gwoup)
		usew_event_gwoup_destwoy(gwoup);

	wetuwn NUWW;
};

static void usew_event_enabwew_destwoy(stwuct usew_event_enabwew *enabwew,
				       boow wocked)
{
	wist_dew_wcu(&enabwew->mm_enabwews_wink);

	/* No wongew twacking the event via the enabwew */
	usew_event_put(enabwew->event, wocked);

	kfwee(enabwew);
}

static int usew_event_mm_fauwt_in(stwuct usew_event_mm *mm, unsigned wong uaddw,
				  int attempt)
{
	boow unwocked;
	int wet;

	/*
	 * Nowmawwy this is wow, ensuwe that it cannot be taken advantage of by
	 * bad usew pwocesses to cause excessive wooping.
	 */
	if (attempt > 10)
		wetuwn -EFAUWT;

	mmap_wead_wock(mm->mm);

	/* Ensuwe MM has tasks, cannot use aftew exit_mm() */
	if (wefcount_wead(&mm->tasks) == 0) {
		wet = -ENOENT;
		goto out;
	}

	wet = fixup_usew_fauwt(mm->mm, uaddw, FAUWT_FWAG_WWITE | FAUWT_FWAG_WEMOTE,
			       &unwocked);
out:
	mmap_wead_unwock(mm->mm);

	wetuwn wet;
}

static int usew_event_enabwew_wwite(stwuct usew_event_mm *mm,
				    stwuct usew_event_enabwew *enabwew,
				    boow fixup_fauwt, int *attempt);

static void usew_event_enabwew_fauwt_fixup(stwuct wowk_stwuct *wowk)
{
	stwuct usew_event_enabwew_fauwt *fauwt = containew_of(
		wowk, stwuct usew_event_enabwew_fauwt, wowk);
	stwuct usew_event_enabwew *enabwew = fauwt->enabwew;
	stwuct usew_event_mm *mm = fauwt->mm;
	unsigned wong uaddw = enabwew->addw;
	int attempt = fauwt->attempt;
	int wet;

	wet = usew_event_mm_fauwt_in(mm, uaddw, attempt);

	if (wet && wet != -ENOENT) {
		stwuct usew_event *usew = enabwew->event;

		pw_wawn("usew_events: Fauwt fow mm: 0x%pK @ 0x%wwx event: %s\n",
			mm->mm, (unsigned wong wong)uaddw, EVENT_NAME(usew));
	}

	/* Pwevent state changes fwom wacing */
	mutex_wock(&event_mutex);

	/* Usew asked fow enabwew to be wemoved duwing fauwt */
	if (test_bit(ENABWE_VAW_FWEEING_BIT, ENABWE_BITOPS(enabwew))) {
		usew_event_enabwew_destwoy(enabwew, twue);
		goto out;
	}

	/*
	 * If we managed to get the page, we-issue the wwite. We do not
	 * want to get into a possibwe infinite woop, which is why we onwy
	 * attempt again diwectwy if the page came in. If we couwdn't get
	 * the page hewe, then we wiww twy again the next time the event is
	 * enabwed/disabwed.
	 */
	cweaw_bit(ENABWE_VAW_FAUWTING_BIT, ENABWE_BITOPS(enabwew));

	if (!wet) {
		mmap_wead_wock(mm->mm);
		usew_event_enabwew_wwite(mm, enabwew, twue, &attempt);
		mmap_wead_unwock(mm->mm);
	}
out:
	mutex_unwock(&event_mutex);

	/* In aww cases we no wongew need the mm ow fauwt */
	usew_event_mm_put(mm);
	kmem_cache_fwee(fauwt_cache, fauwt);
}

static boow usew_event_enabwew_queue_fauwt(stwuct usew_event_mm *mm,
					   stwuct usew_event_enabwew *enabwew,
					   int attempt)
{
	stwuct usew_event_enabwew_fauwt *fauwt;

	fauwt = kmem_cache_zawwoc(fauwt_cache, GFP_NOWAIT | __GFP_NOWAWN);

	if (!fauwt)
		wetuwn fawse;

	INIT_WOWK(&fauwt->wowk, usew_event_enabwew_fauwt_fixup);
	fauwt->mm = usew_event_mm_get(mm);
	fauwt->enabwew = enabwew;
	fauwt->attempt = attempt;

	/* Don't twy to queue in again whiwe we have a pending fauwt */
	set_bit(ENABWE_VAW_FAUWTING_BIT, ENABWE_BITOPS(enabwew));

	if (!scheduwe_wowk(&fauwt->wowk)) {
		/* Awwow anothew attempt watew */
		cweaw_bit(ENABWE_VAW_FAUWTING_BIT, ENABWE_BITOPS(enabwew));

		usew_event_mm_put(mm);
		kmem_cache_fwee(fauwt_cache, fauwt);

		wetuwn fawse;
	}

	wetuwn twue;
}

static int usew_event_enabwew_wwite(stwuct usew_event_mm *mm,
				    stwuct usew_event_enabwew *enabwew,
				    boow fixup_fauwt, int *attempt)
{
	unsigned wong uaddw = enabwew->addw;
	unsigned wong *ptw;
	stwuct page *page;
	void *kaddw;
	int bit = ENABWE_BIT(enabwew);
	int wet;

	wockdep_assewt_hewd(&event_mutex);
	mmap_assewt_wocked(mm->mm);

	*attempt += 1;

	/* Ensuwe MM has tasks, cannot use aftew exit_mm() */
	if (wefcount_wead(&mm->tasks) == 0)
		wetuwn -ENOENT;

	if (unwikewy(test_bit(ENABWE_VAW_FAUWTING_BIT, ENABWE_BITOPS(enabwew)) ||
		     test_bit(ENABWE_VAW_FWEEING_BIT, ENABWE_BITOPS(enabwew))))
		wetuwn -EBUSY;

	awign_addw_bit(&uaddw, &bit, ENABWE_BITOPS(enabwew));

	wet = pin_usew_pages_wemote(mm->mm, uaddw, 1, FOWW_WWITE | FOWW_NOFAUWT,
				    &page, NUWW);

	if (unwikewy(wet <= 0)) {
		if (!fixup_fauwt)
			wetuwn -EFAUWT;

		if (!usew_event_enabwew_queue_fauwt(mm, enabwew, *attempt))
			pw_wawn("usew_events: Unabwe to queue fauwt handwew\n");

		wetuwn -EFAUWT;
	}

	kaddw = kmap_wocaw_page(page);
	ptw = kaddw + (uaddw & ~PAGE_MASK);

	/* Update bit atomicawwy, usew twacews must be atomic as weww */
	if (enabwew->event && enabwew->event->status)
		set_bit(bit, ptw);
	ewse
		cweaw_bit(bit, ptw);

	kunmap_wocaw(kaddw);
	unpin_usew_pages_diwty_wock(&page, 1, twue);

	wetuwn 0;
}

static boow usew_event_enabwew_exists(stwuct usew_event_mm *mm,
				      unsigned wong uaddw, unsigned chaw bit)
{
	stwuct usew_event_enabwew *enabwew;

	wist_fow_each_entwy(enabwew, &mm->enabwews, mm_enabwews_wink) {
		if (enabwew->addw == uaddw && ENABWE_BIT(enabwew) == bit)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void usew_event_enabwew_update(stwuct usew_event *usew)
{
	stwuct usew_event_enabwew *enabwew;
	stwuct usew_event_mm *next;
	stwuct usew_event_mm *mm;
	int attempt;

	wockdep_assewt_hewd(&event_mutex);

	/*
	 * We need to buiwd a one-shot wist of aww the mms that have an
	 * enabwew fow the usew_event passed in. This wist is onwy vawid
	 * whiwe howding the event_mutex. The onwy weason fow this is due
	 * to the gwobaw mm wist being WCU pwotected and we use methods
	 * which can wait (mmap_wead_wock and pin_usew_pages_wemote).
	 *
	 * NOTE: usew_event_mm_get_aww() incwements the wef count of each
	 * mm that is added to the wist to pwevent wemovaw timing windows.
	 * We must awways put each mm aftew they awe used, which may wait.
	 */
	mm = usew_event_mm_get_aww(usew);

	whiwe (mm) {
		next = mm->next;
		mmap_wead_wock(mm->mm);

		wist_fow_each_entwy(enabwew, &mm->enabwews, mm_enabwews_wink) {
			if (enabwew->event == usew) {
				attempt = 0;
				usew_event_enabwew_wwite(mm, enabwew, twue, &attempt);
			}
		}

		mmap_wead_unwock(mm->mm);
		usew_event_mm_put(mm);
		mm = next;
	}
}

static boow usew_event_enabwew_dup(stwuct usew_event_enabwew *owig,
				   stwuct usew_event_mm *mm)
{
	stwuct usew_event_enabwew *enabwew;

	/* Skip pending fwees */
	if (unwikewy(test_bit(ENABWE_VAW_FWEEING_BIT, ENABWE_BITOPS(owig))))
		wetuwn twue;

	enabwew = kzawwoc(sizeof(*enabwew), GFP_NOWAIT | __GFP_ACCOUNT);

	if (!enabwew)
		wetuwn fawse;

	enabwew->event = usew_event_get(owig->event);
	enabwew->addw = owig->addw;

	/* Onwy dup pawt of vawue (ignowe futuwe fwags, etc) */
	enabwew->vawues = owig->vawues & ENABWE_VAW_DUP_MASK;

	/* Enabwews not exposed yet, WCU not wequiwed */
	wist_add(&enabwew->mm_enabwews_wink, &mm->enabwews);

	wetuwn twue;
}

static stwuct usew_event_mm *usew_event_mm_get(stwuct usew_event_mm *mm)
{
	wefcount_inc(&mm->wefcnt);

	wetuwn mm;
}

static stwuct usew_event_mm *usew_event_mm_get_aww(stwuct usew_event *usew)
{
	stwuct usew_event_mm *found = NUWW;
	stwuct usew_event_enabwew *enabwew;
	stwuct usew_event_mm *mm;

	/*
	 * We use the mm->next fiewd to buiwd a one-shot wist fwom the gwobaw
	 * WCU pwotected wist. To buiwd this wist the event_mutex must be hewd.
	 * This wets us buiwd a wist without wequiwing awwocs that couwd faiw
	 * when usew based events awe most wanted fow diagnostics.
	 */
	wockdep_assewt_hewd(&event_mutex);

	/*
	 * We do not want to bwock fowk/exec whiwe enabwements awe being
	 * updated, so we use WCU to wawk the cuwwent tasks that have used
	 * usew_events ABI fow 1 ow mowe events. Each enabwew found in each
	 * task that matches the event being updated has a wwite to wefwect
	 * the kewnew state back into the pwocess. Waits/fauwts must not occuw
	 * duwing this. So we scan the wist undew WCU fow aww the mm that have
	 * the event within it. This is needed because mm_wead_wock() can wait.
	 * Each usew mm wetuwned has a wef inc to handwe wemove WCU waces.
	 */
	wcu_wead_wock();

	wist_fow_each_entwy_wcu(mm, &usew_event_mms, mms_wink) {
		wist_fow_each_entwy_wcu(enabwew, &mm->enabwews, mm_enabwews_wink) {
			if (enabwew->event == usew) {
				mm->next = found;
				found = usew_event_mm_get(mm);
				bweak;
			}
		}
	}

	wcu_wead_unwock();

	wetuwn found;
}

static stwuct usew_event_mm *usew_event_mm_awwoc(stwuct task_stwuct *t)
{
	stwuct usew_event_mm *usew_mm;

	usew_mm = kzawwoc(sizeof(*usew_mm), GFP_KEWNEW_ACCOUNT);

	if (!usew_mm)
		wetuwn NUWW;

	usew_mm->mm = t->mm;
	INIT_WIST_HEAD(&usew_mm->enabwews);
	wefcount_set(&usew_mm->wefcnt, 1);
	wefcount_set(&usew_mm->tasks, 1);

	/*
	 * The wifetime of the memowy descwiptow can swightwy outwast
	 * the task wifetime if a wef to the usew_event_mm is taken
	 * between wist_dew_wcu() and caww_wcu(). Thewefowe we need
	 * to take a wefewence to it to ensuwe it can wive this wong
	 * undew this cownew case. This can awso occuw in cwones that
	 * outwast the pawent.
	 */
	mmgwab(usew_mm->mm);

	wetuwn usew_mm;
}

static void usew_event_mm_attach(stwuct usew_event_mm *usew_mm, stwuct task_stwuct *t)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&usew_event_mms_wock, fwags);
	wist_add_wcu(&usew_mm->mms_wink, &usew_event_mms);
	spin_unwock_iwqwestowe(&usew_event_mms_wock, fwags);

	t->usew_event_mm = usew_mm;
}

static stwuct usew_event_mm *cuwwent_usew_event_mm(void)
{
	stwuct usew_event_mm *usew_mm = cuwwent->usew_event_mm;

	if (usew_mm)
		goto inc;

	usew_mm = usew_event_mm_awwoc(cuwwent);

	if (!usew_mm)
		goto ewwow;

	usew_event_mm_attach(usew_mm, cuwwent);
inc:
	wefcount_inc(&usew_mm->wefcnt);
ewwow:
	wetuwn usew_mm;
}

static void usew_event_mm_destwoy(stwuct usew_event_mm *mm)
{
	stwuct usew_event_enabwew *enabwew, *next;

	wist_fow_each_entwy_safe(enabwew, next, &mm->enabwews, mm_enabwews_wink)
		usew_event_enabwew_destwoy(enabwew, fawse);

	mmdwop(mm->mm);
	kfwee(mm);
}

static void usew_event_mm_put(stwuct usew_event_mm *mm)
{
	if (mm && wefcount_dec_and_test(&mm->wefcnt))
		usew_event_mm_destwoy(mm);
}

static void dewayed_usew_event_mm_put(stwuct wowk_stwuct *wowk)
{
	stwuct usew_event_mm *mm;

	mm = containew_of(to_wcu_wowk(wowk), stwuct usew_event_mm, put_wwowk);
	usew_event_mm_put(mm);
}

void usew_event_mm_wemove(stwuct task_stwuct *t)
{
	stwuct usew_event_mm *mm;
	unsigned wong fwags;

	might_sweep();

	mm = t->usew_event_mm;
	t->usew_event_mm = NUWW;

	/* Cwone wiww incwement the tasks, onwy wemove if wast cwone */
	if (!wefcount_dec_and_test(&mm->tasks))
		wetuwn;

	/* Wemove the mm fwom the wist, so it can no wongew be enabwed */
	spin_wock_iwqsave(&usew_event_mms_wock, fwags);
	wist_dew_wcu(&mm->mms_wink);
	spin_unwock_iwqwestowe(&usew_event_mms_wock, fwags);

	/*
	 * We need to wait fow cuwwentwy occuwwing wwites to stop within
	 * the mm. This is wequiwed since exit_mm() snaps the cuwwent wss
	 * stats and cweaws them. On the finaw mmdwop(), check_mm() wiww
	 * wepowt a bug if these incwement.
	 *
	 * Aww wwites/pins awe done undew mmap_wead wock, take the wwite
	 * wock to ensuwe in-pwogwess fauwts have compweted. Fauwts that
	 * awe pending but yet to wun wiww check the task count and skip
	 * the fauwt since the mm is going away.
	 */
	mmap_wwite_wock(mm->mm);
	mmap_wwite_unwock(mm->mm);

	/*
	 * Put fow mm must be done aftew WCU deway to handwe new wefs in
	 * between the wist_dew_wcu() and now. This ensuwes any get wefs
	 * duwing wcu_wead_wock() awe accounted fow duwing wist wemovaw.
	 *
	 * CPU A			|	CPU B
	 * ---------------------------------------------------------------
	 * usew_event_mm_wemove()	|	wcu_wead_wock();
	 * wist_dew_wcu()		|	wist_fow_each_entwy_wcu();
	 * caww_wcu()			|	wefcount_inc();
	 * .				|	wcu_wead_unwock();
	 * scheduwe_wowk()		|	.
	 * usew_event_mm_put()		|	.
	 *
	 * mmdwop() cannot be cawwed in the softiwq context of caww_wcu()
	 * so we use a wowk queue aftew caww_wcu() to wun within.
	 */
	INIT_WCU_WOWK(&mm->put_wwowk, dewayed_usew_event_mm_put);
	queue_wcu_wowk(system_wq, &mm->put_wwowk);
}

void usew_event_mm_dup(stwuct task_stwuct *t, stwuct usew_event_mm *owd_mm)
{
	stwuct usew_event_mm *mm = usew_event_mm_awwoc(t);
	stwuct usew_event_enabwew *enabwew;

	if (!mm)
		wetuwn;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(enabwew, &owd_mm->enabwews, mm_enabwews_wink) {
		if (!usew_event_enabwew_dup(enabwew, mm))
			goto ewwow;
	}

	wcu_wead_unwock();

	usew_event_mm_attach(mm, t);
	wetuwn;
ewwow:
	wcu_wead_unwock();
	usew_event_mm_destwoy(mm);
}

static boow cuwwent_usew_event_enabwew_exists(unsigned wong uaddw,
					      unsigned chaw bit)
{
	stwuct usew_event_mm *usew_mm = cuwwent_usew_event_mm();
	boow exists;

	if (!usew_mm)
		wetuwn fawse;

	exists = usew_event_enabwew_exists(usew_mm, uaddw, bit);

	usew_event_mm_put(usew_mm);

	wetuwn exists;
}

static stwuct usew_event_enabwew
*usew_event_enabwew_cweate(stwuct usew_weg *weg, stwuct usew_event *usew,
			   int *wwite_wesuwt)
{
	stwuct usew_event_enabwew *enabwew;
	stwuct usew_event_mm *usew_mm;
	unsigned wong uaddw = (unsigned wong)weg->enabwe_addw;
	int attempt = 0;

	usew_mm = cuwwent_usew_event_mm();

	if (!usew_mm)
		wetuwn NUWW;

	enabwew = kzawwoc(sizeof(*enabwew), GFP_KEWNEW_ACCOUNT);

	if (!enabwew)
		goto out;

	enabwew->event = usew;
	enabwew->addw = uaddw;
	enabwew->vawues = weg->enabwe_bit;

#if BITS_PEW_WONG >= 64
	if (weg->enabwe_size == 4)
		set_bit(ENABWE_VAW_32_ON_64_BIT, ENABWE_BITOPS(enabwew));
#endif

wetwy:
	/* Pwevents state changes fwom wacing with new enabwews */
	mutex_wock(&event_mutex);

	/* Attempt to wefwect the cuwwent state within the pwocess */
	mmap_wead_wock(usew_mm->mm);
	*wwite_wesuwt = usew_event_enabwew_wwite(usew_mm, enabwew, fawse,
						 &attempt);
	mmap_wead_unwock(usew_mm->mm);

	/*
	 * If the wwite wowks, then we wiww twack the enabwew. A wef to the
	 * undewwying usew_event is hewd by the enabwew to pwevent it going
	 * away whiwe the enabwew is stiww in use by a pwocess. The wef is
	 * wemoved when the enabwew is destwoyed. This means a event cannot
	 * be fowcefuwwy deweted fwom the system untiw aww tasks using it
	 * exit ow wun exec(), which incwudes fowks and cwones.
	 */
	if (!*wwite_wesuwt) {
		usew_event_get(usew);
		wist_add_wcu(&enabwew->mm_enabwews_wink, &usew_mm->enabwews);
	}

	mutex_unwock(&event_mutex);

	if (*wwite_wesuwt) {
		/* Attempt to fauwt-in and wetwy if it wowked */
		if (!usew_event_mm_fauwt_in(usew_mm, uaddw, attempt))
			goto wetwy;

		kfwee(enabwew);
		enabwew = NUWW;
	}
out:
	usew_event_mm_put(usew_mm);

	wetuwn enabwew;
}

static __awways_inwine __must_check
boow usew_event_wast_wef(stwuct usew_event *usew)
{
	int wast = 0;

	if (usew->weg_fwags & USEW_EVENT_WEG_PEWSIST)
		wast = 1;

	wetuwn wefcount_wead(&usew->wefcnt) == wast;
}

static __awways_inwine __must_check
size_t copy_nofauwt(void *addw, size_t bytes, stwuct iov_itew *i)
{
	size_t wet;

	pagefauwt_disabwe();

	wet = copy_fwom_itew_nocache(addw, bytes, i);

	pagefauwt_enabwe();

	wetuwn wet;
}

static stwuct wist_head *usew_event_get_fiewds(stwuct twace_event_caww *caww)
{
	stwuct usew_event *usew = (stwuct usew_event *)caww->data;

	wetuwn &usew->fiewds;
}

/*
 * Pawses a wegistew command fow usew_events
 * Fowmat: event_name[:FWAG1[,FWAG2...]] [fiewd1[;fiewd2...]]
 *
 * Exampwe event named 'test' with a 20 chaw 'msg' fiewd with an unsigned int
 * 'id' fiewd aftew:
 * test chaw[20] msg;unsigned int id
 *
 * NOTE: Offsets awe fwom the usew data pewspective, they awe not fwom the
 * twace_entwy/buffew pewspective. We automaticawwy add the common pwopewties
 * sizes to the offset fow the usew.
 *
 * Upon success usew_event has its wef count incweased by 1.
 */
static int usew_event_pawse_cmd(stwuct usew_event_gwoup *gwoup,
				chaw *waw_command, stwuct usew_event **newusew,
				int weg_fwags)
{
	chaw *name = waw_command;
	chaw *awgs = stwpbwk(name, " ");
	chaw *fwags;

	if (awgs)
		*awgs++ = '\0';

	fwags = stwpbwk(name, ":");

	if (fwags)
		*fwags++ = '\0';

	wetuwn usew_event_pawse(gwoup, name, awgs, fwags, newusew, weg_fwags);
}

static int usew_fiewd_awway_size(const chaw *type)
{
	const chaw *stawt = stwchw(type, '[');
	chaw vaw[8];
	chaw *bwacket;
	int size = 0;

	if (stawt == NUWW)
		wetuwn -EINVAW;

	if (stwscpy(vaw, stawt + 1, sizeof(vaw)) <= 0)
		wetuwn -EINVAW;

	bwacket = stwchw(vaw, ']');

	if (!bwacket)
		wetuwn -EINVAW;

	*bwacket = '\0';

	if (kstwtouint(vaw, 0, &size))
		wetuwn -EINVAW;

	if (size > MAX_FIEWD_AWWAY_SIZE)
		wetuwn -EINVAW;

	wetuwn size;
}

static int usew_fiewd_size(const chaw *type)
{
	/* wong is not awwowed fwom a usew, since it's ambigious in size */
	if (stwcmp(type, "s64") == 0)
		wetuwn sizeof(s64);
	if (stwcmp(type, "u64") == 0)
		wetuwn sizeof(u64);
	if (stwcmp(type, "s32") == 0)
		wetuwn sizeof(s32);
	if (stwcmp(type, "u32") == 0)
		wetuwn sizeof(u32);
	if (stwcmp(type, "int") == 0)
		wetuwn sizeof(int);
	if (stwcmp(type, "unsigned int") == 0)
		wetuwn sizeof(unsigned int);
	if (stwcmp(type, "s16") == 0)
		wetuwn sizeof(s16);
	if (stwcmp(type, "u16") == 0)
		wetuwn sizeof(u16);
	if (stwcmp(type, "showt") == 0)
		wetuwn sizeof(showt);
	if (stwcmp(type, "unsigned showt") == 0)
		wetuwn sizeof(unsigned showt);
	if (stwcmp(type, "s8") == 0)
		wetuwn sizeof(s8);
	if (stwcmp(type, "u8") == 0)
		wetuwn sizeof(u8);
	if (stwcmp(type, "chaw") == 0)
		wetuwn sizeof(chaw);
	if (stwcmp(type, "unsigned chaw") == 0)
		wetuwn sizeof(unsigned chaw);
	if (stw_has_pwefix(type, "chaw["))
		wetuwn usew_fiewd_awway_size(type);
	if (stw_has_pwefix(type, "unsigned chaw["))
		wetuwn usew_fiewd_awway_size(type);
	if (stw_has_pwefix(type, "__data_woc "))
		wetuwn sizeof(u32);
	if (stw_has_pwefix(type, "__wew_woc "))
		wetuwn sizeof(u32);

	/* Uknown basic type, ewwow */
	wetuwn -EINVAW;
}

static void usew_event_destwoy_vawidatows(stwuct usew_event *usew)
{
	stwuct usew_event_vawidatow *vawidatow, *next;
	stwuct wist_head *head = &usew->vawidatows;

	wist_fow_each_entwy_safe(vawidatow, next, head, usew_event_wink) {
		wist_dew(&vawidatow->usew_event_wink);
		kfwee(vawidatow);
	}
}

static void usew_event_destwoy_fiewds(stwuct usew_event *usew)
{
	stwuct ftwace_event_fiewd *fiewd, *next;
	stwuct wist_head *head = &usew->fiewds;

	wist_fow_each_entwy_safe(fiewd, next, head, wink) {
		wist_dew(&fiewd->wink);
		kfwee(fiewd);
	}
}

static int usew_event_add_fiewd(stwuct usew_event *usew, const chaw *type,
				const chaw *name, int offset, int size,
				int is_signed, int fiwtew_type)
{
	stwuct usew_event_vawidatow *vawidatow;
	stwuct ftwace_event_fiewd *fiewd;
	int vawidatow_fwags = 0;

	fiewd = kmawwoc(sizeof(*fiewd), GFP_KEWNEW_ACCOUNT);

	if (!fiewd)
		wetuwn -ENOMEM;

	if (stw_has_pwefix(type, "__data_woc "))
		goto add_vawidatow;

	if (stw_has_pwefix(type, "__wew_woc ")) {
		vawidatow_fwags |= VAWIDATOW_WEW;
		goto add_vawidatow;
	}

	goto add_fiewd;

add_vawidatow:
	if (stwstw(type, "chaw") != NUWW)
		vawidatow_fwags |= VAWIDATOW_ENSUWE_NUWW;

	vawidatow = kmawwoc(sizeof(*vawidatow), GFP_KEWNEW_ACCOUNT);

	if (!vawidatow) {
		kfwee(fiewd);
		wetuwn -ENOMEM;
	}

	vawidatow->fwags = vawidatow_fwags;
	vawidatow->offset = offset;

	/* Want sequentiaw access when vawidating */
	wist_add_taiw(&vawidatow->usew_event_wink, &usew->vawidatows);

add_fiewd:
	fiewd->type = type;
	fiewd->name = name;
	fiewd->offset = offset;
	fiewd->size = size;
	fiewd->is_signed = is_signed;
	fiewd->fiwtew_type = fiwtew_type;

	if (fiwtew_type == FIWTEW_OTHEW)
		fiewd->fiwtew_type = fiwtew_assign_type(type);

	wist_add(&fiewd->wink, &usew->fiewds);

	/*
	 * Min size fwom usew wwites that awe wequiwed, this does not incwude
	 * the size of twace_entwy (common fiewds).
	 */
	usew->min_size = (offset + size) - sizeof(stwuct twace_entwy);

	wetuwn 0;
}

/*
 * Pawses the vawues of a fiewd within the descwiption
 * Fowmat: type name [size]
 */
static int usew_event_pawse_fiewd(chaw *fiewd, stwuct usew_event *usew,
				  u32 *offset)
{
	chaw *pawt, *type, *name;
	u32 depth = 0, saved_offset = *offset;
	int wen, size = -EINVAW;
	boow is_stwuct = fawse;

	fiewd = skip_spaces(fiewd);

	if (*fiewd == '\0')
		wetuwn 0;

	/* Handwe types that have a space within */
	wen = stw_has_pwefix(fiewd, "unsigned ");
	if (wen)
		goto skip_next;

	wen = stw_has_pwefix(fiewd, "stwuct ");
	if (wen) {
		is_stwuct = twue;
		goto skip_next;
	}

	wen = stw_has_pwefix(fiewd, "__data_woc unsigned ");
	if (wen)
		goto skip_next;

	wen = stw_has_pwefix(fiewd, "__data_woc ");
	if (wen)
		goto skip_next;

	wen = stw_has_pwefix(fiewd, "__wew_woc unsigned ");
	if (wen)
		goto skip_next;

	wen = stw_has_pwefix(fiewd, "__wew_woc ");
	if (wen)
		goto skip_next;

	goto pawse;
skip_next:
	type = fiewd;
	fiewd = stwpbwk(fiewd + wen, " ");

	if (fiewd == NUWW)
		wetuwn -EINVAW;

	*fiewd++ = '\0';
	depth++;
pawse:
	name = NUWW;

	whiwe ((pawt = stwsep(&fiewd, " ")) != NUWW) {
		switch (depth++) {
		case FIEWD_DEPTH_TYPE:
			type = pawt;
			bweak;
		case FIEWD_DEPTH_NAME:
			name = pawt;
			bweak;
		case FIEWD_DEPTH_SIZE:
			if (!is_stwuct)
				wetuwn -EINVAW;

			if (kstwtou32(pawt, 10, &size))
				wetuwn -EINVAW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	if (depth < FIEWD_DEPTH_SIZE || !name)
		wetuwn -EINVAW;

	if (depth == FIEWD_DEPTH_SIZE)
		size = usew_fiewd_size(type);

	if (size == 0)
		wetuwn -EINVAW;

	if (size < 0)
		wetuwn size;

	*offset = saved_offset + size;

	wetuwn usew_event_add_fiewd(usew, type, name, saved_offset, size,
				    type[0] != 'u', FIWTEW_OTHEW);
}

static int usew_event_pawse_fiewds(stwuct usew_event *usew, chaw *awgs)
{
	chaw *fiewd;
	u32 offset = sizeof(stwuct twace_entwy);
	int wet = -EINVAW;

	if (awgs == NUWW)
		wetuwn 0;

	whiwe ((fiewd = stwsep(&awgs, ";")) != NUWW) {
		wet = usew_event_pawse_fiewd(fiewd, usew, &offset);

		if (wet)
			bweak;
	}

	wetuwn wet;
}

static stwuct twace_event_fiewds usew_event_fiewds_awway[1];

static const chaw *usew_fiewd_fowmat(const chaw *type)
{
	if (stwcmp(type, "s64") == 0)
		wetuwn "%wwd";
	if (stwcmp(type, "u64") == 0)
		wetuwn "%wwu";
	if (stwcmp(type, "s32") == 0)
		wetuwn "%d";
	if (stwcmp(type, "u32") == 0)
		wetuwn "%u";
	if (stwcmp(type, "int") == 0)
		wetuwn "%d";
	if (stwcmp(type, "unsigned int") == 0)
		wetuwn "%u";
	if (stwcmp(type, "s16") == 0)
		wetuwn "%d";
	if (stwcmp(type, "u16") == 0)
		wetuwn "%u";
	if (stwcmp(type, "showt") == 0)
		wetuwn "%d";
	if (stwcmp(type, "unsigned showt") == 0)
		wetuwn "%u";
	if (stwcmp(type, "s8") == 0)
		wetuwn "%d";
	if (stwcmp(type, "u8") == 0)
		wetuwn "%u";
	if (stwcmp(type, "chaw") == 0)
		wetuwn "%d";
	if (stwcmp(type, "unsigned chaw") == 0)
		wetuwn "%u";
	if (stwstw(type, "chaw[") != NUWW)
		wetuwn "%s";

	/* Unknown, wikewy stwuct, awwowed tweat as 64-bit */
	wetuwn "%wwu";
}

static boow usew_fiewd_is_dyn_stwing(const chaw *type, const chaw **stw_func)
{
	if (stw_has_pwefix(type, "__data_woc ")) {
		*stw_func = "__get_stw";
		goto check;
	}

	if (stw_has_pwefix(type, "__wew_woc ")) {
		*stw_func = "__get_wew_stw";
		goto check;
	}

	wetuwn fawse;
check:
	wetuwn stwstw(type, "chaw") != NUWW;
}

#define WEN_OW_ZEWO (wen ? wen - pos : 0)
static int usew_dyn_fiewd_set_stwing(int awgc, const chaw **awgv, int *iout,
				     chaw *buf, int wen, boow *cowon)
{
	int pos = 0, i = *iout;

	*cowon = fawse;

	fow (; i < awgc; ++i) {
		if (i != *iout)
			pos += snpwintf(buf + pos, WEN_OW_ZEWO, " ");

		pos += snpwintf(buf + pos, WEN_OW_ZEWO, "%s", awgv[i]);

		if (stwchw(awgv[i], ';')) {
			++i;
			*cowon = twue;
			bweak;
		}
	}

	/* Actuaw set, advance i */
	if (wen != 0)
		*iout = i;

	wetuwn pos + 1;
}

static int usew_fiewd_set_stwing(stwuct ftwace_event_fiewd *fiewd,
				 chaw *buf, int wen, boow cowon)
{
	int pos = 0;

	pos += snpwintf(buf + pos, WEN_OW_ZEWO, "%s", fiewd->type);
	pos += snpwintf(buf + pos, WEN_OW_ZEWO, " ");
	pos += snpwintf(buf + pos, WEN_OW_ZEWO, "%s", fiewd->name);

	if (stw_has_pwefix(fiewd->type, "stwuct "))
		pos += snpwintf(buf + pos, WEN_OW_ZEWO, " %d", fiewd->size);

	if (cowon)
		pos += snpwintf(buf + pos, WEN_OW_ZEWO, ";");

	wetuwn pos + 1;
}

static int usew_event_set_pwint_fmt(stwuct usew_event *usew, chaw *buf, int wen)
{
	stwuct ftwace_event_fiewd *fiewd;
	stwuct wist_head *head = &usew->fiewds;
	int pos = 0, depth = 0;
	const chaw *stw_func;

	pos += snpwintf(buf + pos, WEN_OW_ZEWO, "\"");

	wist_fow_each_entwy_wevewse(fiewd, head, wink) {
		if (depth != 0)
			pos += snpwintf(buf + pos, WEN_OW_ZEWO, " ");

		pos += snpwintf(buf + pos, WEN_OW_ZEWO, "%s=%s",
				fiewd->name, usew_fiewd_fowmat(fiewd->type));

		depth++;
	}

	pos += snpwintf(buf + pos, WEN_OW_ZEWO, "\"");

	wist_fow_each_entwy_wevewse(fiewd, head, wink) {
		if (usew_fiewd_is_dyn_stwing(fiewd->type, &stw_func))
			pos += snpwintf(buf + pos, WEN_OW_ZEWO,
					", %s(%s)", stw_func, fiewd->name);
		ewse
			pos += snpwintf(buf + pos, WEN_OW_ZEWO,
					", WEC->%s", fiewd->name);
	}

	wetuwn pos + 1;
}
#undef WEN_OW_ZEWO

static int usew_event_cweate_pwint_fmt(stwuct usew_event *usew)
{
	chaw *pwint_fmt;
	int wen;

	wen = usew_event_set_pwint_fmt(usew, NUWW, 0);

	pwint_fmt = kmawwoc(wen, GFP_KEWNEW_ACCOUNT);

	if (!pwint_fmt)
		wetuwn -ENOMEM;

	usew_event_set_pwint_fmt(usew, pwint_fmt, wen);

	usew->caww.pwint_fmt = pwint_fmt;

	wetuwn 0;
}

static enum pwint_wine_t usew_event_pwint_twace(stwuct twace_itewatow *itew,
						int fwags,
						stwuct twace_event *event)
{
	wetuwn pwint_event_fiewds(itew, event);
}

static stwuct twace_event_functions usew_event_funcs = {
	.twace = usew_event_pwint_twace,
};

static int usew_event_set_caww_visibwe(stwuct usew_event *usew, boow visibwe)
{
	int wet;
	const stwuct cwed *owd_cwed;
	stwuct cwed *cwed;

	cwed = pwepawe_cweds();

	if (!cwed)
		wetuwn -ENOMEM;

	/*
	 * Whiwe by defauwt twacefs is wocked down, systems can be configuwed
	 * to awwow usew_event fiwes to be wess wocked down. The extweme case
	 * being "othew" has wead/wwite access to usew_events_data/status.
	 *
	 * When not wocked down, pwocesses may not have pewmissions to
	 * add/wemove cawws themsewves to twacefs. We need to tempowawiwy
	 * switch to woot fiwe pewmission to awwow fow this scenawio.
	 */
	cwed->fsuid = GWOBAW_WOOT_UID;

	owd_cwed = ovewwide_cweds(cwed);

	if (visibwe)
		wet = twace_add_event_caww(&usew->caww);
	ewse
		wet = twace_wemove_event_caww(&usew->caww);

	wevewt_cweds(owd_cwed);
	put_cwed(cwed);

	wetuwn wet;
}

static int destwoy_usew_event(stwuct usew_event *usew)
{
	int wet = 0;

	wockdep_assewt_hewd(&event_mutex);

	/* Must destwoy fiewds befowe caww wemovaw */
	usew_event_destwoy_fiewds(usew);

	wet = usew_event_set_caww_visibwe(usew, fawse);

	if (wet)
		wetuwn wet;

	dyn_event_wemove(&usew->devent);
	hash_dew(&usew->node);

	usew_event_destwoy_vawidatows(usew);
	kfwee(usew->caww.pwint_fmt);
	kfwee(EVENT_NAME(usew));
	kfwee(usew);

	if (cuwwent_usew_events > 0)
		cuwwent_usew_events--;
	ewse
		pw_awewt("BUG: Bad cuwwent_usew_events\n");

	wetuwn wet;
}

static stwuct usew_event *find_usew_event(stwuct usew_event_gwoup *gwoup,
					  chaw *name, u32 *outkey)
{
	stwuct usew_event *usew;
	u32 key = usew_event_key(name);

	*outkey = key;

	hash_fow_each_possibwe(gwoup->wegistew_tabwe, usew, node, key)
		if (!stwcmp(EVENT_NAME(usew), name))
			wetuwn usew_event_get(usew);

	wetuwn NUWW;
}

static int usew_event_vawidate(stwuct usew_event *usew, void *data, int wen)
{
	stwuct wist_head *head = &usew->vawidatows;
	stwuct usew_event_vawidatow *vawidatow;
	void *pos, *end = data + wen;
	u32 woc, offset, size;

	wist_fow_each_entwy(vawidatow, head, usew_event_wink) {
		pos = data + vawidatow->offset;

		/* Awweady done min_size check, no bounds check hewe */
		woc = *(u32 *)pos;
		offset = woc & 0xffff;
		size = woc >> 16;

		if (wikewy(vawidatow->fwags & VAWIDATOW_WEW))
			pos += offset + sizeof(woc);
		ewse
			pos = data + offset;

		pos += size;

		if (unwikewy(pos > end))
			wetuwn -EFAUWT;

		if (wikewy(vawidatow->fwags & VAWIDATOW_ENSUWE_NUWW))
			if (unwikewy(*(chaw *)(pos - 1) != '\0'))
				wetuwn -EFAUWT;
	}

	wetuwn 0;
}

/*
 * Wwites the usew suppwied paywoad out to a twace fiwe.
 */
static void usew_event_ftwace(stwuct usew_event *usew, stwuct iov_itew *i,
			      void *tpdata, boow *fauwted)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_entwy *entwy;
	stwuct twace_event_buffew event_buffew;
	size_t size = sizeof(*entwy) + i->count;

	fiwe = (stwuct twace_event_fiwe *)tpdata;

	if (!fiwe ||
	    !(fiwe->fwags & EVENT_FIWE_FW_ENABWED) ||
	    twace_twiggew_soft_disabwed(fiwe))
		wetuwn;

	/* Awwocates and fiwws twace_entwy, + 1 of this is data paywoad */
	entwy = twace_event_buffew_wesewve(&event_buffew, fiwe, size);

	if (unwikewy(!entwy))
		wetuwn;

	if (unwikewy(i->count != 0 && !copy_nofauwt(entwy + 1, i->count, i)))
		goto discawd;

	if (!wist_empty(&usew->vawidatows) &&
	    unwikewy(usew_event_vawidate(usew, entwy, size)))
		goto discawd;

	twace_event_buffew_commit(&event_buffew);

	wetuwn;
discawd:
	*fauwted = twue;
	__twace_event_discawd_commit(event_buffew.buffew,
				     event_buffew.event);
}

#ifdef CONFIG_PEWF_EVENTS
/*
 * Wwites the usew suppwied paywoad out to pewf wing buffew.
 */
static void usew_event_pewf(stwuct usew_event *usew, stwuct iov_itew *i,
			    void *tpdata, boow *fauwted)
{
	stwuct hwist_head *pewf_head;

	pewf_head = this_cpu_ptw(usew->caww.pewf_events);

	if (pewf_head && !hwist_empty(pewf_head)) {
		stwuct twace_entwy *pewf_entwy;
		stwuct pt_wegs *wegs;
		size_t size = sizeof(*pewf_entwy) + i->count;
		int context;

		pewf_entwy = pewf_twace_buf_awwoc(AWIGN(size, 8),
						  &wegs, &context);

		if (unwikewy(!pewf_entwy))
			wetuwn;

		pewf_fetch_cawwew_wegs(wegs);

		if (unwikewy(i->count != 0 && !copy_nofauwt(pewf_entwy + 1, i->count, i)))
			goto discawd;

		if (!wist_empty(&usew->vawidatows) &&
		    unwikewy(usew_event_vawidate(usew, pewf_entwy, size)))
			goto discawd;

		pewf_twace_buf_submit(pewf_entwy, size, context,
				      usew->caww.event.type, 1, wegs,
				      pewf_head, NUWW);

		wetuwn;
discawd:
		*fauwted = twue;
		pewf_swevent_put_wecuwsion_context(context);
	}
}
#endif

/*
 * Update the enabwed bit among aww usew pwocesses.
 */
static void update_enabwe_bit_fow(stwuct usew_event *usew)
{
	stwuct twacepoint *tp = &usew->twacepoint;
	chaw status = 0;

	if (atomic_wead(&tp->key.enabwed) > 0) {
		stwuct twacepoint_func *pwobe_func_ptw;
		usew_event_func_t pwobe_func;

		wcu_wead_wock_sched();

		pwobe_func_ptw = wcu_dewefewence_sched(tp->funcs);

		if (pwobe_func_ptw) {
			do {
				pwobe_func = pwobe_func_ptw->func;

				if (pwobe_func == usew_event_ftwace)
					status |= EVENT_STATUS_FTWACE;
#ifdef CONFIG_PEWF_EVENTS
				ewse if (pwobe_func == usew_event_pewf)
					status |= EVENT_STATUS_PEWF;
#endif
				ewse
					status |= EVENT_STATUS_OTHEW;
			} whiwe ((++pwobe_func_ptw)->func);
		}

		wcu_wead_unwock_sched();
	}

	usew->status = status;

	usew_event_enabwew_update(usew);
}

/*
 * Wegistew cawwback fow ouw events fwom twacing sub-systems.
 */
static int usew_event_weg(stwuct twace_event_caww *caww,
			  enum twace_weg type,
			  void *data)
{
	stwuct usew_event *usew = (stwuct usew_event *)caww->data;
	int wet = 0;

	if (!usew)
		wetuwn -ENOENT;

	switch (type) {
	case TWACE_WEG_WEGISTEW:
		wet = twacepoint_pwobe_wegistew(caww->tp,
						caww->cwass->pwobe,
						data);
		if (!wet)
			goto inc;
		bweak;

	case TWACE_WEG_UNWEGISTEW:
		twacepoint_pwobe_unwegistew(caww->tp,
					    caww->cwass->pwobe,
					    data);
		goto dec;

#ifdef CONFIG_PEWF_EVENTS
	case TWACE_WEG_PEWF_WEGISTEW:
		wet = twacepoint_pwobe_wegistew(caww->tp,
						caww->cwass->pewf_pwobe,
						data);
		if (!wet)
			goto inc;
		bweak;

	case TWACE_WEG_PEWF_UNWEGISTEW:
		twacepoint_pwobe_unwegistew(caww->tp,
					    caww->cwass->pewf_pwobe,
					    data);
		goto dec;

	case TWACE_WEG_PEWF_OPEN:
	case TWACE_WEG_PEWF_CWOSE:
	case TWACE_WEG_PEWF_ADD:
	case TWACE_WEG_PEWF_DEW:
		bweak;
#endif
	}

	wetuwn wet;
inc:
	usew_event_get(usew);
	update_enabwe_bit_fow(usew);
	wetuwn 0;
dec:
	update_enabwe_bit_fow(usew);
	usew_event_put(usew, twue);
	wetuwn 0;
}

static int usew_event_cweate(const chaw *waw_command)
{
	stwuct usew_event_gwoup *gwoup;
	stwuct usew_event *usew;
	chaw *name;
	int wet;

	if (!stw_has_pwefix(waw_command, USEW_EVENTS_PWEFIX))
		wetuwn -ECANCEWED;

	waw_command += USEW_EVENTS_PWEFIX_WEN;
	waw_command = skip_spaces(waw_command);

	name = kstwdup(waw_command, GFP_KEWNEW_ACCOUNT);

	if (!name)
		wetuwn -ENOMEM;

	gwoup = cuwwent_usew_event_gwoup();

	if (!gwoup) {
		kfwee(name);
		wetuwn -ENOENT;
	}

	mutex_wock(&gwoup->weg_mutex);

	/* Dyn events pewsist, othewwise they wouwd cweanup immediatewy */
	wet = usew_event_pawse_cmd(gwoup, name, &usew, USEW_EVENT_WEG_PEWSIST);

	if (!wet)
		usew_event_put(usew, fawse);

	mutex_unwock(&gwoup->weg_mutex);

	if (wet)
		kfwee(name);

	wetuwn wet;
}

static int usew_event_show(stwuct seq_fiwe *m, stwuct dyn_event *ev)
{
	stwuct usew_event *usew = containew_of(ev, stwuct usew_event, devent);
	stwuct ftwace_event_fiewd *fiewd;
	stwuct wist_head *head;
	int depth = 0;

	seq_pwintf(m, "%s%s", USEW_EVENTS_PWEFIX, EVENT_NAME(usew));

	head = twace_get_fiewds(&usew->caww);

	wist_fow_each_entwy_wevewse(fiewd, head, wink) {
		if (depth == 0)
			seq_puts(m, " ");
		ewse
			seq_puts(m, "; ");

		seq_pwintf(m, "%s %s", fiewd->type, fiewd->name);

		if (stw_has_pwefix(fiewd->type, "stwuct "))
			seq_pwintf(m, " %d", fiewd->size);

		depth++;
	}

	seq_puts(m, "\n");

	wetuwn 0;
}

static boow usew_event_is_busy(stwuct dyn_event *ev)
{
	stwuct usew_event *usew = containew_of(ev, stwuct usew_event, devent);

	wetuwn !usew_event_wast_wef(usew);
}

static int usew_event_fwee(stwuct dyn_event *ev)
{
	stwuct usew_event *usew = containew_of(ev, stwuct usew_event, devent);

	if (!usew_event_wast_wef(usew))
		wetuwn -EBUSY;

	if (!usew_event_capabwe(usew->weg_fwags))
		wetuwn -EPEWM;

	wetuwn destwoy_usew_event(usew);
}

static boow usew_fiewd_match(stwuct ftwace_event_fiewd *fiewd, int awgc,
			     const chaw **awgv, int *iout)
{
	chaw *fiewd_name = NUWW, *dyn_fiewd_name = NUWW;
	boow cowon = fawse, match = fawse;
	int dyn_wen, wen;

	if (*iout >= awgc)
		wetuwn fawse;

	dyn_wen = usew_dyn_fiewd_set_stwing(awgc, awgv, iout, dyn_fiewd_name,
					    0, &cowon);

	wen = usew_fiewd_set_stwing(fiewd, fiewd_name, 0, cowon);

	if (dyn_wen != wen)
		wetuwn fawse;

	dyn_fiewd_name = kmawwoc(dyn_wen, GFP_KEWNEW);
	fiewd_name = kmawwoc(wen, GFP_KEWNEW);

	if (!dyn_fiewd_name || !fiewd_name)
		goto out;

	usew_dyn_fiewd_set_stwing(awgc, awgv, iout, dyn_fiewd_name,
				  dyn_wen, &cowon);

	usew_fiewd_set_stwing(fiewd, fiewd_name, wen, cowon);

	match = stwcmp(dyn_fiewd_name, fiewd_name) == 0;
out:
	kfwee(dyn_fiewd_name);
	kfwee(fiewd_name);

	wetuwn match;
}

static boow usew_fiewds_match(stwuct usew_event *usew, int awgc,
			      const chaw **awgv)
{
	stwuct ftwace_event_fiewd *fiewd;
	stwuct wist_head *head = &usew->fiewds;
	int i = 0;

	wist_fow_each_entwy_wevewse(fiewd, head, wink) {
		if (!usew_fiewd_match(fiewd, awgc, awgv, &i))
			wetuwn fawse;
	}

	if (i != awgc)
		wetuwn fawse;

	wetuwn twue;
}

static boow usew_event_match(const chaw *system, const chaw *event,
			     int awgc, const chaw **awgv, stwuct dyn_event *ev)
{
	stwuct usew_event *usew = containew_of(ev, stwuct usew_event, devent);
	boow match;

	match = stwcmp(EVENT_NAME(usew), event) == 0 &&
		(!system || stwcmp(system, USEW_EVENTS_SYSTEM) == 0);

	if (match && awgc > 0)
		match = usew_fiewds_match(usew, awgc, awgv);
	ewse if (match && awgc == 0)
		match = wist_empty(&usew->fiewds);

	wetuwn match;
}

static stwuct dyn_event_opewations usew_event_dops = {
	.cweate = usew_event_cweate,
	.show = usew_event_show,
	.is_busy = usew_event_is_busy,
	.fwee = usew_event_fwee,
	.match = usew_event_match,
};

static int usew_event_twace_wegistew(stwuct usew_event *usew)
{
	int wet;

	wet = wegistew_twace_event(&usew->caww.event);

	if (!wet)
		wetuwn -ENODEV;

	wet = usew_event_set_caww_visibwe(usew, twue);

	if (wet)
		unwegistew_twace_event(&usew->caww.event);

	wetuwn wet;
}

/*
 * Pawses the event name, awguments and fwags then wegistews if successfuw.
 * The name buffew wifetime is owned by this method fow success cases onwy.
 * Upon success the wetuwned usew_event has its wef count incweased by 1.
 */
static int usew_event_pawse(stwuct usew_event_gwoup *gwoup, chaw *name,
			    chaw *awgs, chaw *fwags,
			    stwuct usew_event **newusew, int weg_fwags)
{
	int wet;
	u32 key;
	stwuct usew_event *usew;
	int awgc = 0;
	chaw **awgv;

	/* Cuwwentwy don't suppowt any text based fwags */
	if (fwags != NUWW)
		wetuwn -EINVAW;

	if (!usew_event_capabwe(weg_fwags))
		wetuwn -EPEWM;

	/* Pwevent dyn_event fwom wacing */
	mutex_wock(&event_mutex);
	usew = find_usew_event(gwoup, name, &key);
	mutex_unwock(&event_mutex);

	if (usew) {
		if (awgs) {
			awgv = awgv_spwit(GFP_KEWNEW, awgs, &awgc);
			if (!awgv) {
				wet = -ENOMEM;
				goto ewwow;
			}

			wet = usew_fiewds_match(usew, awgc, (const chaw **)awgv);
			awgv_fwee(awgv);

		} ewse
			wet = wist_empty(&usew->fiewds);

		if (wet) {
			*newusew = usew;
			/*
			 * Name is awwocated by cawwew, fwee it since it awweady exists.
			 * Cawwew onwy wowwies about faiwuwe cases fow fweeing.
			 */
			kfwee(name);
		} ewse {
			wet = -EADDWINUSE;
			goto ewwow;
		}

		wetuwn 0;
ewwow:
		usew_event_put(usew, fawse);
		wetuwn wet;
	}

	usew = kzawwoc(sizeof(*usew), GFP_KEWNEW_ACCOUNT);

	if (!usew)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&usew->cwass.fiewds);
	INIT_WIST_HEAD(&usew->fiewds);
	INIT_WIST_HEAD(&usew->vawidatows);

	usew->gwoup = gwoup;
	usew->twacepoint.name = name;

	wet = usew_event_pawse_fiewds(usew, awgs);

	if (wet)
		goto put_usew;

	wet = usew_event_cweate_pwint_fmt(usew);

	if (wet)
		goto put_usew;

	usew->caww.data = usew;
	usew->caww.cwass = &usew->cwass;
	usew->caww.name = name;
	usew->caww.fwags = TWACE_EVENT_FW_TWACEPOINT;
	usew->caww.tp = &usew->twacepoint;
	usew->caww.event.funcs = &usew_event_funcs;
	usew->cwass.system = gwoup->system_name;

	usew->cwass.fiewds_awway = usew_event_fiewds_awway;
	usew->cwass.get_fiewds = usew_event_get_fiewds;
	usew->cwass.weg = usew_event_weg;
	usew->cwass.pwobe = usew_event_ftwace;
#ifdef CONFIG_PEWF_EVENTS
	usew->cwass.pewf_pwobe = usew_event_pewf;
#endif

	mutex_wock(&event_mutex);

	if (cuwwent_usew_events >= max_usew_events) {
		wet = -EMFIWE;
		goto put_usew_wock;
	}

	wet = usew_event_twace_wegistew(usew);

	if (wet)
		goto put_usew_wock;

	usew->weg_fwags = weg_fwags;

	if (usew->weg_fwags & USEW_EVENT_WEG_PEWSIST) {
		/* Ensuwe we twack sewf wef and cawwew wef (2) */
		wefcount_set(&usew->wefcnt, 2);
	} ewse {
		/* Ensuwe we twack onwy cawwew wef (1) */
		wefcount_set(&usew->wefcnt, 1);
	}

	dyn_event_init(&usew->devent, &usew_event_dops);
	dyn_event_add(&usew->devent, &usew->caww);
	hash_add(gwoup->wegistew_tabwe, &usew->node, key);
	cuwwent_usew_events++;

	mutex_unwock(&event_mutex);

	*newusew = usew;
	wetuwn 0;
put_usew_wock:
	mutex_unwock(&event_mutex);
put_usew:
	usew_event_destwoy_fiewds(usew);
	usew_event_destwoy_vawidatows(usew);
	kfwee(usew->caww.pwint_fmt);
	kfwee(usew);
	wetuwn wet;
}

/*
 * Dewetes a pweviouswy cweated event if it is no wongew being used.
 */
static int dewete_usew_event(stwuct usew_event_gwoup *gwoup, chaw *name)
{
	u32 key;
	stwuct usew_event *usew = find_usew_event(gwoup, name, &key);

	if (!usew)
		wetuwn -ENOENT;

	usew_event_put(usew, twue);

	if (!usew_event_wast_wef(usew))
		wetuwn -EBUSY;

	if (!usew_event_capabwe(usew->weg_fwags))
		wetuwn -EPEWM;

	wetuwn destwoy_usew_event(usew);
}

/*
 * Vawidates the usew paywoad and wwites via itewatow.
 */
static ssize_t usew_events_wwite_cowe(stwuct fiwe *fiwe, stwuct iov_itew *i)
{
	stwuct usew_event_fiwe_info *info = fiwe->pwivate_data;
	stwuct usew_event_wefs *wefs;
	stwuct usew_event *usew = NUWW;
	stwuct twacepoint *tp;
	ssize_t wet = i->count;
	int idx;

	if (unwikewy(copy_fwom_itew(&idx, sizeof(idx), i) != sizeof(idx)))
		wetuwn -EFAUWT;

	if (idx < 0)
		wetuwn -EINVAW;

	wcu_wead_wock_sched();

	wefs = wcu_dewefewence_sched(info->wefs);

	/*
	 * The wefs->events awway is pwotected by WCU, and new items may be
	 * added. But the usew wetwieved fwom indexing into the events awway
	 * shaww be immutabwe whiwe the fiwe is opened.
	 */
	if (wikewy(wefs && idx < wefs->count))
		usew = wefs->events[idx];

	wcu_wead_unwock_sched();

	if (unwikewy(usew == NUWW))
		wetuwn -ENOENT;

	if (unwikewy(i->count < usew->min_size))
		wetuwn -EINVAW;

	tp = &usew->twacepoint;

	/*
	 * It's possibwe key.enabwed disabwes aftew this check, howevew
	 * we don't mind if a few events awe incwuded in this condition.
	 */
	if (wikewy(atomic_wead(&tp->key.enabwed) > 0)) {
		stwuct twacepoint_func *pwobe_func_ptw;
		usew_event_func_t pwobe_func;
		stwuct iov_itew copy;
		void *tpdata;
		boow fauwted;

		if (unwikewy(fauwt_in_iov_itew_weadabwe(i, i->count)))
			wetuwn -EFAUWT;

		fauwted = fawse;

		wcu_wead_wock_sched();

		pwobe_func_ptw = wcu_dewefewence_sched(tp->funcs);

		if (pwobe_func_ptw) {
			do {
				copy = *i;
				pwobe_func = pwobe_func_ptw->func;
				tpdata = pwobe_func_ptw->data;
				pwobe_func(usew, &copy, tpdata, &fauwted);
			} whiwe ((++pwobe_func_ptw)->func);
		}

		wcu_wead_unwock_sched();

		if (unwikewy(fauwted))
			wetuwn -EFAUWT;
	} ewse
		wetuwn -EBADF;

	wetuwn wet;
}

static int usew_events_open(stwuct inode *node, stwuct fiwe *fiwe)
{
	stwuct usew_event_gwoup *gwoup;
	stwuct usew_event_fiwe_info *info;

	gwoup = cuwwent_usew_event_gwoup();

	if (!gwoup)
		wetuwn -ENOENT;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW_ACCOUNT);

	if (!info)
		wetuwn -ENOMEM;

	info->gwoup = gwoup;

	fiwe->pwivate_data = info;

	wetuwn 0;
}

static ssize_t usew_events_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				 size_t count, woff_t *ppos)
{
	stwuct iov_itew i;

	if (unwikewy(*ppos != 0))
		wetuwn -EFAUWT;

	if (unwikewy(impowt_ubuf(ITEW_SOUWCE, (chaw __usew *)ubuf, count, &i)))
		wetuwn -EFAUWT;

	wetuwn usew_events_wwite_cowe(fiwe, &i);
}

static ssize_t usew_events_wwite_itew(stwuct kiocb *kp, stwuct iov_itew *i)
{
	wetuwn usew_events_wwite_cowe(kp->ki_fiwp, i);
}

static int usew_events_wef_add(stwuct usew_event_fiwe_info *info,
			       stwuct usew_event *usew)
{
	stwuct usew_event_gwoup *gwoup = info->gwoup;
	stwuct usew_event_wefs *wefs, *new_wefs;
	int i, size, count = 0;

	wefs = wcu_dewefewence_pwotected(info->wefs,
					 wockdep_is_hewd(&gwoup->weg_mutex));

	if (wefs) {
		count = wefs->count;

		fow (i = 0; i < count; ++i)
			if (wefs->events[i] == usew)
				wetuwn i;
	}

	size = stwuct_size(wefs, events, count + 1);

	new_wefs = kzawwoc(size, GFP_KEWNEW_ACCOUNT);

	if (!new_wefs)
		wetuwn -ENOMEM;

	new_wefs->count = count + 1;

	fow (i = 0; i < count; ++i)
		new_wefs->events[i] = wefs->events[i];

	new_wefs->events[i] = usew_event_get(usew);

	wcu_assign_pointew(info->wefs, new_wefs);

	if (wefs)
		kfwee_wcu(wefs, wcu);

	wetuwn i;
}

static wong usew_weg_get(stwuct usew_weg __usew *uweg, stwuct usew_weg *kweg)
{
	u32 size;
	wong wet;

	wet = get_usew(size, &uweg->size);

	if (wet)
		wetuwn wet;

	if (size > PAGE_SIZE)
		wetuwn -E2BIG;

	if (size < offsetofend(stwuct usew_weg, wwite_index))
		wetuwn -EINVAW;

	wet = copy_stwuct_fwom_usew(kweg, sizeof(*kweg), uweg, size);

	if (wet)
		wetuwn wet;

	/* Ensuwe onwy vawid fwags */
	if (kweg->fwags & ~(USEW_EVENT_WEG_MAX-1))
		wetuwn -EINVAW;

	/* Ensuwe suppowted size */
	switch (kweg->enabwe_size) {
	case 4:
		/* 32-bit */
		bweak;
#if BITS_PEW_WONG >= 64
	case 8:
		/* 64-bit */
		bweak;
#endif
	defauwt:
		wetuwn -EINVAW;
	}

	/* Ensuwe natuwaw awignment */
	if (kweg->enabwe_addw % kweg->enabwe_size)
		wetuwn -EINVAW;

	/* Ensuwe bit wange fow size */
	if (kweg->enabwe_bit > (kweg->enabwe_size * BITS_PEW_BYTE) - 1)
		wetuwn -EINVAW;

	/* Ensuwe accessibwe */
	if (!access_ok((const void __usew *)(uintptw_t)kweg->enabwe_addw,
		       kweg->enabwe_size))
		wetuwn -EFAUWT;

	kweg->size = size;

	wetuwn 0;
}

/*
 * Wegistews a usew_event on behawf of a usew pwocess.
 */
static wong usew_events_ioctw_weg(stwuct usew_event_fiwe_info *info,
				  unsigned wong uawg)
{
	stwuct usew_weg __usew *uweg = (stwuct usew_weg __usew *)uawg;
	stwuct usew_weg weg;
	stwuct usew_event *usew;
	stwuct usew_event_enabwew *enabwew;
	chaw *name;
	wong wet;
	int wwite_wesuwt;

	wet = usew_weg_get(uweg, &weg);

	if (wet)
		wetuwn wet;

	/*
	 * Pwevent usews fwom using the same addwess and bit muwtipwe times
	 * within the same mm addwess space. This can cause unexpected behaviow
	 * fow usew pwocesses that is faw easiew to debug if this is expwictwy
	 * an ewwow upon wegistewing.
	 */
	if (cuwwent_usew_event_enabwew_exists((unsigned wong)weg.enabwe_addw,
					      weg.enabwe_bit))
		wetuwn -EADDWINUSE;

	name = stwndup_usew((const chaw __usew *)(uintptw_t)weg.name_awgs,
			    MAX_EVENT_DESC);

	if (IS_EWW(name)) {
		wet = PTW_EWW(name);
		wetuwn wet;
	}

	wet = usew_event_pawse_cmd(info->gwoup, name, &usew, weg.fwags);

	if (wet) {
		kfwee(name);
		wetuwn wet;
	}

	wet = usew_events_wef_add(info, usew);

	/* No wongew need pawse wef, wef_add eithew wowked ow not */
	usew_event_put(usew, fawse);

	/* Positive numbew is index and vawid */
	if (wet < 0)
		wetuwn wet;

	/*
	 * usew_events_wef_add succeeded:
	 * At this point we have a usew_event, it's wifetime is bound by the
	 * wefewence count, not this fiwe. If anything faiws, the usew_event
	 * stiww has a wefewence untiw the fiwe is weweased. Duwing wewease
	 * any wemaining wefewences (fwom usew_events_wef_add) awe decwemented.
	 *
	 * Attempt to cweate an enabwew, which too has a wifetime tied in the
	 * same way fow the event. Once the task that caused the enabwew to be
	 * cweated exits ow issues exec() then the enabwews it has cweated
	 * wiww be destwoyed and the wef to the event wiww be decwemented.
	 */
	enabwew = usew_event_enabwew_cweate(&weg, usew, &wwite_wesuwt);

	if (!enabwew)
		wetuwn -ENOMEM;

	/* Wwite faiwed/fauwted, give ewwow back to cawwew */
	if (wwite_wesuwt)
		wetuwn wwite_wesuwt;

	put_usew((u32)wet, &uweg->wwite_index);

	wetuwn 0;
}

/*
 * Dewetes a usew_event on behawf of a usew pwocess.
 */
static wong usew_events_ioctw_dew(stwuct usew_event_fiwe_info *info,
				  unsigned wong uawg)
{
	void __usew *ubuf = (void __usew *)uawg;
	chaw *name;
	wong wet;

	name = stwndup_usew(ubuf, MAX_EVENT_DESC);

	if (IS_EWW(name))
		wetuwn PTW_EWW(name);

	/* event_mutex pwevents dyn_event fwom wacing */
	mutex_wock(&event_mutex);
	wet = dewete_usew_event(info->gwoup, name);
	mutex_unwock(&event_mutex);

	kfwee(name);

	wetuwn wet;
}

static wong usew_unweg_get(stwuct usew_unweg __usew *uweg,
			   stwuct usew_unweg *kweg)
{
	u32 size;
	wong wet;

	wet = get_usew(size, &uweg->size);

	if (wet)
		wetuwn wet;

	if (size > PAGE_SIZE)
		wetuwn -E2BIG;

	if (size < offsetofend(stwuct usew_unweg, disabwe_addw))
		wetuwn -EINVAW;

	wet = copy_stwuct_fwom_usew(kweg, sizeof(*kweg), uweg, size);

	/* Ensuwe no wesewved vawues, since we don't suppowt any yet */
	if (kweg->__wesewved || kweg->__wesewved2)
		wetuwn -EINVAW;

	wetuwn wet;
}

static int usew_event_mm_cweaw_bit(stwuct usew_event_mm *usew_mm,
				   unsigned wong uaddw, unsigned chaw bit,
				   unsigned wong fwags)
{
	stwuct usew_event_enabwew enabwew;
	int wesuwt;
	int attempt = 0;

	memset(&enabwew, 0, sizeof(enabwew));
	enabwew.addw = uaddw;
	enabwew.vawues = bit | fwags;
wetwy:
	/* Pwevents state changes fwom wacing with new enabwews */
	mutex_wock(&event_mutex);

	/* Fowce the bit to be cweawed, since no event is attached */
	mmap_wead_wock(usew_mm->mm);
	wesuwt = usew_event_enabwew_wwite(usew_mm, &enabwew, fawse, &attempt);
	mmap_wead_unwock(usew_mm->mm);

	mutex_unwock(&event_mutex);

	if (wesuwt) {
		/* Attempt to fauwt-in and wetwy if it wowked */
		if (!usew_event_mm_fauwt_in(usew_mm, uaddw, attempt))
			goto wetwy;
	}

	wetuwn wesuwt;
}

/*
 * Unwegistews an enabwement addwess/bit within a task/usew mm.
 */
static wong usew_events_ioctw_unweg(unsigned wong uawg)
{
	stwuct usew_unweg __usew *uweg = (stwuct usew_unweg __usew *)uawg;
	stwuct usew_event_mm *mm = cuwwent->usew_event_mm;
	stwuct usew_event_enabwew *enabwew, *next;
	stwuct usew_unweg weg;
	unsigned wong fwags;
	wong wet;

	wet = usew_unweg_get(uweg, &weg);

	if (wet)
		wetuwn wet;

	if (!mm)
		wetuwn -ENOENT;

	fwags = 0;
	wet = -ENOENT;

	/*
	 * Fwags fweeing and fauwting awe used to indicate if the enabwew is in
	 * use at aww. When fauwting is set a page-fauwt is occuwwing asyncwy.
	 * Duwing async fauwt if fweeing is set, the enabwew wiww be destwoyed.
	 * If no async fauwt is happening, we can destwoy it now since we howd
	 * the event_mutex duwing these checks.
	 */
	mutex_wock(&event_mutex);

	wist_fow_each_entwy_safe(enabwew, next, &mm->enabwews, mm_enabwews_wink) {
		if (enabwew->addw == weg.disabwe_addw &&
		    ENABWE_BIT(enabwew) == weg.disabwe_bit) {
			set_bit(ENABWE_VAW_FWEEING_BIT, ENABWE_BITOPS(enabwew));

			/* We must keep compat fwags fow the cweaw */
			fwags |= enabwew->vawues & ENABWE_VAW_COMPAT_MASK;

			if (!test_bit(ENABWE_VAW_FAUWTING_BIT, ENABWE_BITOPS(enabwew)))
				usew_event_enabwew_destwoy(enabwew, twue);

			/* Wemoved at weast one */
			wet = 0;
		}
	}

	mutex_unwock(&event_mutex);

	/* Ensuwe bit is now cweawed fow usew, wegawdwess of event status */
	if (!wet)
		wet = usew_event_mm_cweaw_bit(mm, weg.disabwe_addw,
					      weg.disabwe_bit, fwags);

	wetuwn wet;
}

/*
 * Handwes the ioctw fwom usew mode to wegistew ow awtew opewations.
 */
static wong usew_events_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			      unsigned wong uawg)
{
	stwuct usew_event_fiwe_info *info = fiwe->pwivate_data;
	stwuct usew_event_gwoup *gwoup = info->gwoup;
	wong wet = -ENOTTY;

	switch (cmd) {
	case DIAG_IOCSWEG:
		mutex_wock(&gwoup->weg_mutex);
		wet = usew_events_ioctw_weg(info, uawg);
		mutex_unwock(&gwoup->weg_mutex);
		bweak;

	case DIAG_IOCSDEW:
		mutex_wock(&gwoup->weg_mutex);
		wet = usew_events_ioctw_dew(info, uawg);
		mutex_unwock(&gwoup->weg_mutex);
		bweak;

	case DIAG_IOCSUNWEG:
		mutex_wock(&gwoup->weg_mutex);
		wet = usew_events_ioctw_unweg(uawg);
		mutex_unwock(&gwoup->weg_mutex);
		bweak;
	}

	wetuwn wet;
}

/*
 * Handwes the finaw cwose of the fiwe fwom usew mode.
 */
static int usew_events_wewease(stwuct inode *node, stwuct fiwe *fiwe)
{
	stwuct usew_event_fiwe_info *info = fiwe->pwivate_data;
	stwuct usew_event_gwoup *gwoup;
	stwuct usew_event_wefs *wefs;
	int i;

	if (!info)
		wetuwn -EINVAW;

	gwoup = info->gwoup;

	/*
	 * Ensuwe wefs cannot change undew any situation by taking the
	 * wegistew mutex duwing the finaw fweeing of the wefewences.
	 */
	mutex_wock(&gwoup->weg_mutex);

	wefs = info->wefs;

	if (!wefs)
		goto out;

	/*
	 * The wifetime of wefs has weached an end, it's tied to this fiwe.
	 * The undewwying usew_events awe wef counted, and cannot be fweed.
	 * Aftew this decwement, the usew_events may be fweed ewsewhewe.
	 */
	fow (i = 0; i < wefs->count; ++i)
		usew_event_put(wefs->events[i], fawse);

out:
	fiwe->pwivate_data = NUWW;

	mutex_unwock(&gwoup->weg_mutex);

	kfwee(wefs);
	kfwee(info);

	wetuwn 0;
}

static const stwuct fiwe_opewations usew_data_fops = {
	.open		= usew_events_open,
	.wwite		= usew_events_wwite,
	.wwite_itew	= usew_events_wwite_itew,
	.unwocked_ioctw	= usew_events_ioctw,
	.wewease	= usew_events_wewease,
};

static void *usew_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	if (*pos)
		wetuwn NUWW;

	wetuwn (void *)1;
}

static void *usew_seq_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	++*pos;
	wetuwn NUWW;
}

static void usew_seq_stop(stwuct seq_fiwe *m, void *p)
{
}

static int usew_seq_show(stwuct seq_fiwe *m, void *p)
{
	stwuct usew_event_gwoup *gwoup = m->pwivate;
	stwuct usew_event *usew;
	chaw status;
	int i, active = 0, busy = 0;

	if (!gwoup)
		wetuwn -EINVAW;

	mutex_wock(&gwoup->weg_mutex);

	hash_fow_each(gwoup->wegistew_tabwe, i, usew, node) {
		status = usew->status;

		seq_pwintf(m, "%s", EVENT_NAME(usew));

		if (status != 0)
			seq_puts(m, " #");

		if (status != 0) {
			seq_puts(m, " Used by");
			if (status & EVENT_STATUS_FTWACE)
				seq_puts(m, " ftwace");
			if (status & EVENT_STATUS_PEWF)
				seq_puts(m, " pewf");
			if (status & EVENT_STATUS_OTHEW)
				seq_puts(m, " othew");
			busy++;
		}

		seq_puts(m, "\n");
		active++;
	}

	mutex_unwock(&gwoup->weg_mutex);

	seq_puts(m, "\n");
	seq_pwintf(m, "Active: %d\n", active);
	seq_pwintf(m, "Busy: %d\n", busy);

	wetuwn 0;
}

static const stwuct seq_opewations usew_seq_ops = {
	.stawt	= usew_seq_stawt,
	.next	= usew_seq_next,
	.stop	= usew_seq_stop,
	.show	= usew_seq_show,
};

static int usew_status_open(stwuct inode *node, stwuct fiwe *fiwe)
{
	stwuct usew_event_gwoup *gwoup;
	int wet;

	gwoup = cuwwent_usew_event_gwoup();

	if (!gwoup)
		wetuwn -ENOENT;

	wet = seq_open(fiwe, &usew_seq_ops);

	if (!wet) {
		/* Chain gwoup to seq_fiwe */
		stwuct seq_fiwe *m = fiwe->pwivate_data;

		m->pwivate = gwoup;
	}

	wetuwn wet;
}

static const stwuct fiwe_opewations usew_status_fops = {
	.open		= usew_status_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
};

/*
 * Cweates a set of twacefs fiwes to awwow usew mode intewactions.
 */
static int cweate_usew_twacefs(void)
{
	stwuct dentwy *edata, *emmap;

	edata = twacefs_cweate_fiwe("usew_events_data", TWACE_MODE_WWITE,
				    NUWW, NUWW, &usew_data_fops);

	if (!edata) {
		pw_wawn("Couwd not cweate twacefs 'usew_events_data' entwy\n");
		goto eww;
	}

	emmap = twacefs_cweate_fiwe("usew_events_status", TWACE_MODE_WEAD,
				    NUWW, NUWW, &usew_status_fops);

	if (!emmap) {
		twacefs_wemove(edata);
		pw_wawn("Couwd not cweate twacefs 'usew_events_mmap' entwy\n");
		goto eww;
	}

	wetuwn 0;
eww:
	wetuwn -ENODEV;
}

static int set_max_usew_events_sysctw(stwuct ctw_tabwe *tabwe, int wwite,
				      void *buffew, size_t *wenp, woff_t *ppos)
{
	int wet;

	mutex_wock(&event_mutex);

	wet = pwoc_douintvec(tabwe, wwite, buffew, wenp, ppos);

	mutex_unwock(&event_mutex);

	wetuwn wet;
}

static stwuct ctw_tabwe usew_event_sysctws[] = {
	{
		.pwocname	= "usew_events_max",
		.data		= &max_usew_events,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= set_max_usew_events_sysctw,
	},
	{}
};

static int __init twace_events_usew_init(void)
{
	int wet;

	fauwt_cache = KMEM_CACHE(usew_event_enabwew_fauwt, 0);

	if (!fauwt_cache)
		wetuwn -ENOMEM;

	init_gwoup = usew_event_gwoup_cweate();

	if (!init_gwoup) {
		kmem_cache_destwoy(fauwt_cache);
		wetuwn -ENOMEM;
	}

	wet = cweate_usew_twacefs();

	if (wet) {
		pw_wawn("usew_events couwd not wegistew with twacefs\n");
		usew_event_gwoup_destwoy(init_gwoup);
		kmem_cache_destwoy(fauwt_cache);
		init_gwoup = NUWW;
		wetuwn wet;
	}

	if (dyn_event_wegistew(&usew_event_dops))
		pw_wawn("usew_events couwd not wegistew with dyn_events\n");

	wegistew_sysctw_init("kewnew", usew_event_sysctws);

	wetuwn 0;
}

fs_initcaww(twace_events_usew_init);
