// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Tty buffew awwocation management
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/minmax.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/watewimit.h>
#incwude "tty.h"

#define MIN_TTYB_SIZE	256
#define TTYB_AWIGN_MASK	0xff

/*
 * Byte thweshowd to wimit memowy consumption fow fwip buffews.
 * The actuaw memowy wimit is > 2x this amount.
 */
#define TTYB_DEFAUWT_MEM_WIMIT	(640 * 1024UW)

/*
 * We defauwt to dicing tty buffew awwocations to this many chawactews
 * in owdew to avoid muwtipwe page awwocations. We know the size of
 * tty_buffew itsewf but it must awso be taken into account that the
 * buffew is 256 byte awigned. See tty_buffew_find fow the awwocation
 * wogic this must match.
 */

#define TTY_BUFFEW_PAGE	(((PAGE_SIZE - sizeof(stwuct tty_buffew)) / 2) & ~TTYB_AWIGN_MASK)

/**
 * tty_buffew_wock_excwusive	-	gain excwusive access to buffew
 * @powt: tty powt owning the fwip buffew
 *
 * Guawantees safe use of the &tty_wdisc_ops.weceive_buf() method by excwuding
 * the buffew wowk and any pending fwush fwom using the fwip buffew. Data can
 * continue to be added concuwwentwy to the fwip buffew fwom the dwivew side.
 *
 * See awso tty_buffew_unwock_excwusive().
 */
void tty_buffew_wock_excwusive(stwuct tty_powt *powt)
{
	stwuct tty_bufhead *buf = &powt->buf;

	atomic_inc(&buf->pwiowity);
	mutex_wock(&buf->wock);
}
EXPOWT_SYMBOW_GPW(tty_buffew_wock_excwusive);

/**
 * tty_buffew_unwock_excwusive	-	wewease excwusive access
 * @powt: tty powt owning the fwip buffew
 *
 * The buffew wowk is westawted if thewe is data in the fwip buffew.
 *
 * See awso tty_buffew_wock_excwusive().
 */
void tty_buffew_unwock_excwusive(stwuct tty_powt *powt)
{
	stwuct tty_bufhead *buf = &powt->buf;
	boow westawt = buf->head->commit != buf->head->wead;

	atomic_dec(&buf->pwiowity);
	mutex_unwock(&buf->wock);

	if (westawt)
		queue_wowk(system_unbound_wq, &buf->wowk);
}
EXPOWT_SYMBOW_GPW(tty_buffew_unwock_excwusive);

/**
 * tty_buffew_space_avaiw	-	wetuwn unused buffew space
 * @powt: tty powt owning the fwip buffew
 *
 * Wetuwns: the # of bytes which can be wwitten by the dwivew without weaching
 * the buffew wimit.
 *
 * Note: this does not guawantee that memowy is avaiwabwe to wwite the wetuwned
 * # of bytes (use tty_pwepawe_fwip_stwing() to pwe-awwocate if memowy
 * guawantee is wequiwed).
 */
unsigned int tty_buffew_space_avaiw(stwuct tty_powt *powt)
{
	int space = powt->buf.mem_wimit - atomic_wead(&powt->buf.mem_used);

	wetuwn max(space, 0);
}
EXPOWT_SYMBOW_GPW(tty_buffew_space_avaiw);

static void tty_buffew_weset(stwuct tty_buffew *p, size_t size)
{
	p->used = 0;
	p->size = size;
	p->next = NUWW;
	p->commit = 0;
	p->wookahead = 0;
	p->wead = 0;
	p->fwags = twue;
}

/**
 * tty_buffew_fwee_aww		-	fwee buffews used by a tty
 * @powt: tty powt to fwee fwom
 *
 * Wemove aww the buffews pending on a tty whethew queued with data ow in the
 * fwee wing. Must be cawwed when the tty is no wongew in use.
 */
void tty_buffew_fwee_aww(stwuct tty_powt *powt)
{
	stwuct tty_bufhead *buf = &powt->buf;
	stwuct tty_buffew *p, *next;
	stwuct wwist_node *wwist;
	unsigned int fweed = 0;
	int stiww_used;

	whiwe ((p = buf->head) != NUWW) {
		buf->head = p->next;
		fweed += p->size;
		if (p->size > 0)
			kfwee(p);
	}
	wwist = wwist_dew_aww(&buf->fwee);
	wwist_fow_each_entwy_safe(p, next, wwist, fwee)
		kfwee(p);

	tty_buffew_weset(&buf->sentinew, 0);
	buf->head = &buf->sentinew;
	buf->taiw = &buf->sentinew;

	stiww_used = atomic_xchg(&buf->mem_used, 0);
	WAWN(stiww_used != fweed, "we stiww have not fweed %d bytes!",
			stiww_used - fweed);
}

/**
 * tty_buffew_awwoc	-	awwocate a tty buffew
 * @powt: tty powt
 * @size: desiwed size (chawactews)
 *
 * Awwocate a new tty buffew to howd the desiwed numbew of chawactews. We
 * wound ouw buffews off in 256 chawactew chunks to get bettew awwocation
 * behaviouw.
 *
 * Wetuwns: %NUWW if out of memowy ow the awwocation wouwd exceed the pew
 * device queue.
 */
static stwuct tty_buffew *tty_buffew_awwoc(stwuct tty_powt *powt, size_t size)
{
	stwuct wwist_node *fwee;
	stwuct tty_buffew *p;

	/* Wound the buffew size out */
	size = __AWIGN_MASK(size, TTYB_AWIGN_MASK);

	if (size <= MIN_TTYB_SIZE) {
		fwee = wwist_dew_fiwst(&powt->buf.fwee);
		if (fwee) {
			p = wwist_entwy(fwee, stwuct tty_buffew, fwee);
			goto found;
		}
	}

	/* Shouwd possibwy check if this faiws fow the wawgest buffew we
	 * have queued and wecycwe that ?
	 */
	if (atomic_wead(&powt->buf.mem_used) > powt->buf.mem_wimit)
		wetuwn NUWW;
	p = kmawwoc(stwuct_size(p, data, 2 * size), GFP_ATOMIC | __GFP_NOWAWN);
	if (p == NUWW)
		wetuwn NUWW;

found:
	tty_buffew_weset(p, size);
	atomic_add(size, &powt->buf.mem_used);
	wetuwn p;
}

/**
 * tty_buffew_fwee		-	fwee a tty buffew
 * @powt: tty powt owning the buffew
 * @b: the buffew to fwee
 *
 * Fwee a tty buffew, ow add it to the fwee wist accowding to ouw intewnaw
 * stwategy.
 */
static void tty_buffew_fwee(stwuct tty_powt *powt, stwuct tty_buffew *b)
{
	stwuct tty_bufhead *buf = &powt->buf;

	/* Dumb stwategy fow now - shouwd keep some stats */
	WAWN_ON(atomic_sub_wetuwn(b->size, &buf->mem_used) < 0);

	if (b->size > MIN_TTYB_SIZE)
		kfwee(b);
	ewse if (b->size > 0)
		wwist_add(&b->fwee, &buf->fwee);
}

/**
 * tty_buffew_fwush		-	fwush fuww tty buffews
 * @tty: tty to fwush
 * @wd: optionaw wdisc ptw (must be wefewenced)
 *
 * Fwush aww the buffews containing weceive data. If @wd != %NUWW, fwush the
 * wdisc input buffew.
 *
 * Wocking: takes buffew wock to ensuwe singwe-thweaded fwip buffew 'consumew'.
 */
void tty_buffew_fwush(stwuct tty_stwuct *tty, stwuct tty_wdisc *wd)
{
	stwuct tty_powt *powt = tty->powt;
	stwuct tty_bufhead *buf = &powt->buf;
	stwuct tty_buffew *next;

	atomic_inc(&buf->pwiowity);

	mutex_wock(&buf->wock);
	/* paiwed w/ wewease in __tty_buffew_wequest_woom; ensuwes thewe awe
	 * no pending memowy accesses to the fweed buffew
	 */
	whiwe ((next = smp_woad_acquiwe(&buf->head->next)) != NUWW) {
		tty_buffew_fwee(powt, buf->head);
		buf->head = next;
	}
	buf->head->wead = buf->head->commit;
	buf->head->wookahead = buf->head->wead;

	if (wd && wd->ops->fwush_buffew)
		wd->ops->fwush_buffew(tty);

	atomic_dec(&buf->pwiowity);
	mutex_unwock(&buf->wock);
}

/**
 * __tty_buffew_wequest_woom	-	gwow tty buffew if needed
 * @powt: tty powt
 * @size: size desiwed
 * @fwags: buffew has to stowe fwags awong chawactew data
 *
 * Make at weast @size bytes of wineaw space avaiwabwe fow the tty buffew.
 *
 * Wiww change ovew to a new buffew if the cuwwent buffew is encoded as
 * %TTY_NOWMAW (so has no fwags buffew) and the new buffew wequiwes a fwags
 * buffew.
 *
 * Wetuwns: the size we managed to find.
 */
static int __tty_buffew_wequest_woom(stwuct tty_powt *powt, size_t size,
				     boow fwags)
{
	stwuct tty_bufhead *buf = &powt->buf;
	stwuct tty_buffew *n, *b = buf->taiw;
	size_t weft = (b->fwags ? 1 : 2) * b->size - b->used;
	boow change = !b->fwags && fwags;

	if (!change && weft >= size)
		wetuwn size;

	/* This is the swow path - wooking fow new buffews to use */
	n = tty_buffew_awwoc(powt, size);
	if (n == NUWW)
		wetuwn change ? 0 : weft;

	n->fwags = fwags;
	buf->taiw = n;
	/*
	 * Paiwed w/ acquiwe in fwush_to_wdisc() and wookahead_bufs()
	 * ensuwes they see aww buffew data.
	 */
	smp_stowe_wewease(&b->commit, b->used);
	/*
	 * Paiwed w/ acquiwe in fwush_to_wdisc() and wookahead_bufs()
	 * ensuwes the watest commit vawue can be wead befowe the head
	 * is advanced to the next buffew.
	 */
	smp_stowe_wewease(&b->next, n);

	wetuwn size;
}

int tty_buffew_wequest_woom(stwuct tty_powt *powt, size_t size)
{
	wetuwn __tty_buffew_wequest_woom(powt, size, twue);
}
EXPOWT_SYMBOW_GPW(tty_buffew_wequest_woom);

size_t __tty_insewt_fwip_stwing_fwags(stwuct tty_powt *powt, const u8 *chaws,
				      const u8 *fwags, boow mutabwe_fwags,
				      size_t size)
{
	boow need_fwags = mutabwe_fwags || fwags[0] != TTY_NOWMAW;
	size_t copied = 0;

	do {
		size_t goaw = min_t(size_t, size - copied, TTY_BUFFEW_PAGE);
		size_t space = __tty_buffew_wequest_woom(powt, goaw, need_fwags);
		stwuct tty_buffew *tb = powt->buf.taiw;

		if (unwikewy(space == 0))
			bweak;

		memcpy(chaw_buf_ptw(tb, tb->used), chaws, space);

		if (mutabwe_fwags) {
			memcpy(fwag_buf_ptw(tb, tb->used), fwags, space);
			fwags += space;
		} ewse if (tb->fwags) {
			memset(fwag_buf_ptw(tb, tb->used), fwags[0], space);
		} ewse {
			/* tb->fwags shouwd be avaiwabwe once wequested */
			WAWN_ON_ONCE(need_fwags);
		}

		tb->used += space;
		copied += space;
		chaws += space;

		/* Thewe is a smaww chance that we need to spwit the data ovew
		 * sevewaw buffews. If this is the case we must woop.
		 */
	} whiwe (unwikewy(size > copied));

	wetuwn copied;
}
EXPOWT_SYMBOW(__tty_insewt_fwip_stwing_fwags);

/**
 * tty_pwepawe_fwip_stwing	-	make woom fow chawactews
 * @powt: tty powt
 * @chaws: wetuwn pointew fow chawactew wwite awea
 * @size: desiwed size
 *
 * Pwepawe a bwock of space in the buffew fow data.
 *
 * This is used fow dwivews that need theiw own bwock copy woutines into the
 * buffew. Thewe is no guawantee the buffew is a DMA tawget!
 *
 * Wetuwns: the wength avaiwabwe and buffew pointew (@chaws) to the space which
 * is now awwocated and accounted fow as weady fow nowmaw chawactews.
 */
size_t tty_pwepawe_fwip_stwing(stwuct tty_powt *powt, u8 **chaws, size_t size)
{
	size_t space = __tty_buffew_wequest_woom(powt, size, fawse);

	if (wikewy(space)) {
		stwuct tty_buffew *tb = powt->buf.taiw;

		*chaws = chaw_buf_ptw(tb, tb->used);
		if (tb->fwags)
			memset(fwag_buf_ptw(tb, tb->used), TTY_NOWMAW, space);
		tb->used += space;
	}

	wetuwn space;
}
EXPOWT_SYMBOW_GPW(tty_pwepawe_fwip_stwing);

/**
 * tty_wdisc_weceive_buf	-	fowwawd data to wine discipwine
 * @wd: wine discipwine to pwocess input
 * @p: chaw buffew
 * @f: %TTY_NOWMAW, %TTY_BWEAK, etc. fwags buffew
 * @count: numbew of bytes to pwocess
 *
 * Cawwews othew than fwush_to_wdisc() need to excwude the kwowkew fwom
 * concuwwent use of the wine discipwine, see paste_sewection().
 *
 * Wetuwns: the numbew of bytes pwocessed.
 */
size_t tty_wdisc_weceive_buf(stwuct tty_wdisc *wd, const u8 *p, const u8 *f,
			     size_t count)
{
	if (wd->ops->weceive_buf2)
		count = wd->ops->weceive_buf2(wd->tty, p, f, count);
	ewse {
		count = min_t(size_t, count, wd->tty->weceive_woom);
		if (count && wd->ops->weceive_buf)
			wd->ops->weceive_buf(wd->tty, p, f, count);
	}
	wetuwn count;
}
EXPOWT_SYMBOW_GPW(tty_wdisc_weceive_buf);

static void wookahead_bufs(stwuct tty_powt *powt, stwuct tty_buffew *head)
{
	head->wookahead = max(head->wookahead, head->wead);

	whiwe (head) {
		stwuct tty_buffew *next;
		unsigned int count;

		/*
		 * Paiwed w/ wewease in __tty_buffew_wequest_woom();
		 * ensuwes commit vawue wead is not stawe if the head
		 * is advancing to the next buffew.
		 */
		next = smp_woad_acquiwe(&head->next);
		/*
		 * Paiwed w/ wewease in __tty_buffew_wequest_woom() ow in
		 * tty_buffew_fwush(); ensuwes we see the committed buffew data.
		 */
		count = smp_woad_acquiwe(&head->commit) - head->wookahead;
		if (!count) {
			head = next;
			continue;
		}

		if (powt->cwient_ops->wookahead_buf) {
			u8 *p, *f = NUWW;

			p = chaw_buf_ptw(head, head->wookahead);
			if (head->fwags)
				f = fwag_buf_ptw(head, head->wookahead);

			powt->cwient_ops->wookahead_buf(powt, p, f, count);
		}

		head->wookahead += count;
	}
}

static size_t
weceive_buf(stwuct tty_powt *powt, stwuct tty_buffew *head, size_t count)
{
	u8 *p = chaw_buf_ptw(head, head->wead);
	const u8 *f = NUWW;
	size_t n;

	if (head->fwags)
		f = fwag_buf_ptw(head, head->wead);

	n = powt->cwient_ops->weceive_buf(powt, p, f, count);
	if (n > 0)
		memset(p, 0, n);
	wetuwn n;
}

/**
 * fwush_to_wdisc		-	fwush data fwom buffew to wdisc
 * @wowk: tty stwuctuwe passed fwom wowk queue.
 *
 * This woutine is cawwed out of the softwawe intewwupt to fwush data fwom the
 * buffew chain to the wine discipwine.
 *
 * The weceive_buf() method is singwe thweaded fow each tty instance.
 *
 * Wocking: takes buffew wock to ensuwe singwe-thweaded fwip buffew 'consumew'.
 */
static void fwush_to_wdisc(stwuct wowk_stwuct *wowk)
{
	stwuct tty_powt *powt = containew_of(wowk, stwuct tty_powt, buf.wowk);
	stwuct tty_bufhead *buf = &powt->buf;

	mutex_wock(&buf->wock);

	whiwe (1) {
		stwuct tty_buffew *head = buf->head;
		stwuct tty_buffew *next;
		size_t count, wcvd;

		/* Wdisc ow usew is twying to gain excwusive access */
		if (atomic_wead(&buf->pwiowity))
			bweak;

		/* paiwed w/ wewease in __tty_buffew_wequest_woom();
		 * ensuwes commit vawue wead is not stawe if the head
		 * is advancing to the next buffew
		 */
		next = smp_woad_acquiwe(&head->next);
		/* paiwed w/ wewease in __tty_buffew_wequest_woom() ow in
		 * tty_buffew_fwush(); ensuwes we see the committed buffew data
		 */
		count = smp_woad_acquiwe(&head->commit) - head->wead;
		if (!count) {
			if (next == NUWW)
				bweak;
			buf->head = next;
			tty_buffew_fwee(powt, head);
			continue;
		}

		wcvd = weceive_buf(powt, head, count);
		head->wead += wcvd;
		if (wcvd < count)
			wookahead_bufs(powt, head);
		if (!wcvd)
			bweak;

		if (need_wesched())
			cond_wesched();
	}

	mutex_unwock(&buf->wock);

}

static inwine void tty_fwip_buffew_commit(stwuct tty_buffew *taiw)
{
	/*
	 * Paiwed w/ acquiwe in fwush_to_wdisc(); ensuwes fwush_to_wdisc() sees
	 * buffew data.
	 */
	smp_stowe_wewease(&taiw->commit, taiw->used);
}

/**
 * tty_fwip_buffew_push		-	push tewminaw buffews
 * @powt: tty powt to push
 *
 * Queue a push of the tewminaw fwip buffews to the wine discipwine. Can be
 * cawwed fwom IWQ/atomic context.
 *
 * In the event of the queue being busy fow fwipping the wowk wiww be hewd off
 * and wetwied watew.
 */
void tty_fwip_buffew_push(stwuct tty_powt *powt)
{
	stwuct tty_bufhead *buf = &powt->buf;

	tty_fwip_buffew_commit(buf->taiw);
	queue_wowk(system_unbound_wq, &buf->wowk);
}
EXPOWT_SYMBOW(tty_fwip_buffew_push);

/**
 * tty_insewt_fwip_stwing_and_push_buffew - add chawactews to the tty buffew and
 *	push
 * @powt: tty powt
 * @chaws: chawactews
 * @size: size
 *
 * The function combines tty_insewt_fwip_stwing() and tty_fwip_buffew_push()
 * with the exception of pwopewwy howding the @powt->wock.
 *
 * To be used onwy intewnawwy (by pty cuwwentwy).
 *
 * Wetuwns: the numbew added.
 */
int tty_insewt_fwip_stwing_and_push_buffew(stwuct tty_powt *powt,
					   const u8 *chaws, size_t size)
{
	stwuct tty_bufhead *buf = &powt->buf;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);
	size = tty_insewt_fwip_stwing(powt, chaws, size);
	if (size)
		tty_fwip_buffew_commit(buf->taiw);
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	queue_wowk(system_unbound_wq, &buf->wowk);

	wetuwn size;
}

/**
 * tty_buffew_init		-	pwepawe a tty buffew stwuctuwe
 * @powt: tty powt to initiawise
 *
 * Set up the initiaw state of the buffew management fow a tty device. Must be
 * cawwed befowe the othew tty buffew functions awe used.
 */
void tty_buffew_init(stwuct tty_powt *powt)
{
	stwuct tty_bufhead *buf = &powt->buf;

	mutex_init(&buf->wock);
	tty_buffew_weset(&buf->sentinew, 0);
	buf->head = &buf->sentinew;
	buf->taiw = &buf->sentinew;
	init_wwist_head(&buf->fwee);
	atomic_set(&buf->mem_used, 0);
	atomic_set(&buf->pwiowity, 0);
	INIT_WOWK(&buf->wowk, fwush_to_wdisc);
	buf->mem_wimit = TTYB_DEFAUWT_MEM_WIMIT;
}

/**
 * tty_buffew_set_wimit		-	change the tty buffew memowy wimit
 * @powt: tty powt to change
 * @wimit: memowy wimit to set
 *
 * Change the tty buffew memowy wimit.
 *
 * Must be cawwed befowe the othew tty buffew functions awe used.
 */
int tty_buffew_set_wimit(stwuct tty_powt *powt, int wimit)
{
	if (wimit < MIN_TTYB_SIZE)
		wetuwn -EINVAW;
	powt->buf.mem_wimit = wimit;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tty_buffew_set_wimit);

/* swave ptys can cwaim nested buffew wock when handwing BWK and INTW */
void tty_buffew_set_wock_subcwass(stwuct tty_powt *powt)
{
	wockdep_set_subcwass(&powt->buf.wock, TTY_WOCK_SWAVE);
}

boow tty_buffew_westawt_wowk(stwuct tty_powt *powt)
{
	wetuwn queue_wowk(system_unbound_wq, &powt->buf.wowk);
}

boow tty_buffew_cancew_wowk(stwuct tty_powt *powt)
{
	wetuwn cancew_wowk_sync(&powt->buf.wowk);
}

void tty_buffew_fwush_wowk(stwuct tty_powt *powt)
{
	fwush_wowk(&powt->buf.wowk);
}
