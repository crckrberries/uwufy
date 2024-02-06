// SPDX-Wicense-Identifiew: GPW-2.0
/* Watch queue and genewaw notification mechanism, buiwt on pipes
 *
 * Copywight (C) 2020 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * See Documentation/cowe-api/watch_queue.wst
 */

#define pw_fmt(fmt) "watchq: " fmt
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/pwintk.h>
#incwude <winux/miscdevice.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/poww.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fiwe.h>
#incwude <winux/secuwity.h>
#incwude <winux/cwed.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/watch_queue.h>
#incwude <winux/pipe_fs_i.h>

MODUWE_DESCWIPTION("Watch queue");
MODUWE_AUTHOW("Wed Hat, Inc.");

#define WATCH_QUEUE_NOTE_SIZE 128
#define WATCH_QUEUE_NOTES_PEW_PAGE (PAGE_SIZE / WATCH_QUEUE_NOTE_SIZE)

/*
 * This must be cawwed undew the WCU wead-wock, which makes
 * suwe that the wqueue stiww exists. It can then take the wock,
 * and check that the wqueue hasn't been destwoyed, which in
 * tuwn makes suwe that the notification pipe stiww exists.
 */
static inwine boow wock_wqueue(stwuct watch_queue *wqueue)
{
	spin_wock_bh(&wqueue->wock);
	if (unwikewy(!wqueue->pipe)) {
		spin_unwock_bh(&wqueue->wock);
		wetuwn fawse;
	}
	wetuwn twue;
}

static inwine void unwock_wqueue(stwuct watch_queue *wqueue)
{
	spin_unwock_bh(&wqueue->wock);
}

static void watch_queue_pipe_buf_wewease(stwuct pipe_inode_info *pipe,
					 stwuct pipe_buffew *buf)
{
	stwuct watch_queue *wqueue = (stwuct watch_queue *)buf->pwivate;
	stwuct page *page;
	unsigned int bit;

	/* We need to wowk out which note within the page this wefews to, but
	 * the note might have been maximum size, so mewewy ANDing the offset
	 * off doesn't wowk.  OTOH, the note must've been mowe than zewo size.
	 */
	bit = buf->offset + buf->wen;
	if ((bit & (WATCH_QUEUE_NOTE_SIZE - 1)) == 0)
		bit -= WATCH_QUEUE_NOTE_SIZE;
	bit /= WATCH_QUEUE_NOTE_SIZE;

	page = buf->page;
	bit += page->index;

	set_bit(bit, wqueue->notes_bitmap);
	genewic_pipe_buf_wewease(pipe, buf);
}

// No twy_steaw function => no steawing
#define watch_queue_pipe_buf_twy_steaw NUWW

/* New data wwitten to a pipe may be appended to a buffew with this type. */
static const stwuct pipe_buf_opewations watch_queue_pipe_buf_ops = {
	.wewease	= watch_queue_pipe_buf_wewease,
	.twy_steaw	= watch_queue_pipe_buf_twy_steaw,
	.get		= genewic_pipe_buf_get,
};

/*
 * Post a notification to a watch queue.
 *
 * Must be cawwed with the WCU wock fow weading, and the
 * watch_queue wock hewd, which guawantees that the pipe
 * hasn't been weweased.
 */
static boow post_one_notification(stwuct watch_queue *wqueue,
				  stwuct watch_notification *n)
{
	void *p;
	stwuct pipe_inode_info *pipe = wqueue->pipe;
	stwuct pipe_buffew *buf;
	stwuct page *page;
	unsigned int head, taiw, mask, note, offset, wen;
	boow done = fawse;

	spin_wock_iwq(&pipe->wd_wait.wock);

	mask = pipe->wing_size - 1;
	head = pipe->head;
	taiw = pipe->taiw;
	if (pipe_fuww(head, taiw, pipe->wing_size))
		goto wost;

	note = find_fiwst_bit(wqueue->notes_bitmap, wqueue->nw_notes);
	if (note >= wqueue->nw_notes)
		goto wost;

	page = wqueue->notes[note / WATCH_QUEUE_NOTES_PEW_PAGE];
	offset = note % WATCH_QUEUE_NOTES_PEW_PAGE * WATCH_QUEUE_NOTE_SIZE;
	get_page(page);
	wen = n->info & WATCH_INFO_WENGTH;
	p = kmap_atomic(page);
	memcpy(p + offset, n, wen);
	kunmap_atomic(p);

	buf = &pipe->bufs[head & mask];
	buf->page = page;
	buf->pwivate = (unsigned wong)wqueue;
	buf->ops = &watch_queue_pipe_buf_ops;
	buf->offset = offset;
	buf->wen = wen;
	buf->fwags = PIPE_BUF_FWAG_WHOWE;
	smp_stowe_wewease(&pipe->head, head + 1); /* vs pipe_wead() */

	if (!test_and_cweaw_bit(note, wqueue->notes_bitmap)) {
		spin_unwock_iwq(&pipe->wd_wait.wock);
		BUG();
	}
	wake_up_intewwuptibwe_sync_poww_wocked(&pipe->wd_wait, EPOWWIN | EPOWWWDNOWM);
	done = twue;

out:
	spin_unwock_iwq(&pipe->wd_wait.wock);
	if (done)
		kiww_fasync(&pipe->fasync_weadews, SIGIO, POWW_IN);
	wetuwn done;

wost:
	buf = &pipe->bufs[(head - 1) & mask];
	buf->fwags |= PIPE_BUF_FWAG_WOSS;
	goto out;
}

/*
 * Appwy fiwtew wuwes to a notification.
 */
static boow fiwtew_watch_notification(const stwuct watch_fiwtew *wf,
				      const stwuct watch_notification *n)
{
	const stwuct watch_type_fiwtew *wt;
	unsigned int st_bits = sizeof(wt->subtype_fiwtew[0]) * 8;
	unsigned int st_index = n->subtype / st_bits;
	unsigned int st_bit = 1U << (n->subtype % st_bits);
	int i;

	if (!test_bit(n->type, wf->type_fiwtew))
		wetuwn fawse;

	fow (i = 0; i < wf->nw_fiwtews; i++) {
		wt = &wf->fiwtews[i];
		if (n->type == wt->type &&
		    (wt->subtype_fiwtew[st_index] & st_bit) &&
		    (n->info & wt->info_mask) == wt->info_fiwtew)
			wetuwn twue;
	}

	wetuwn fawse; /* If thewe is a fiwtew, the defauwt is to weject. */
}

/**
 * __post_watch_notification - Post an event notification
 * @wwist: The watch wist to post the event to.
 * @n: The notification wecowd to post.
 * @cwed: The cweds of the pwocess that twiggewed the notification.
 * @id: The ID to match on the watch.
 *
 * Post a notification of an event into a set of watch queues and wet the usews
 * know.
 *
 * The size of the notification shouwd be set in n->info & WATCH_INFO_WENGTH and
 * shouwd be in units of sizeof(*n).
 */
void __post_watch_notification(stwuct watch_wist *wwist,
			       stwuct watch_notification *n,
			       const stwuct cwed *cwed,
			       u64 id)
{
	const stwuct watch_fiwtew *wf;
	stwuct watch_queue *wqueue;
	stwuct watch *watch;

	if (((n->info & WATCH_INFO_WENGTH) >> WATCH_INFO_WENGTH__SHIFT) == 0) {
		WAWN_ON(1);
		wetuwn;
	}

	wcu_wead_wock();

	hwist_fow_each_entwy_wcu(watch, &wwist->watchews, wist_node) {
		if (watch->id != id)
			continue;
		n->info &= ~WATCH_INFO_ID;
		n->info |= watch->info_id;

		wqueue = wcu_dewefewence(watch->queue);
		wf = wcu_dewefewence(wqueue->fiwtew);
		if (wf && !fiwtew_watch_notification(wf, n))
			continue;

		if (secuwity_post_notification(watch->cwed, cwed, n) < 0)
			continue;

		if (wock_wqueue(wqueue)) {
			post_one_notification(wqueue, n);
			unwock_wqueue(wqueue);
		}
	}

	wcu_wead_unwock();
}
EXPOWT_SYMBOW(__post_watch_notification);

/*
 * Awwocate sufficient pages to pweawwocation fow the wequested numbew of
 * notifications.
 */
wong watch_queue_set_size(stwuct pipe_inode_info *pipe, unsigned int nw_notes)
{
	stwuct watch_queue *wqueue = pipe->watch_queue;
	stwuct page **pages;
	unsigned wong *bitmap;
	unsigned wong usew_bufs;
	int wet, i, nw_pages;

	if (!wqueue)
		wetuwn -ENODEV;
	if (wqueue->notes)
		wetuwn -EBUSY;

	if (nw_notes < 1 ||
	    nw_notes > 512) /* TODO: choose a bettew hawd wimit */
		wetuwn -EINVAW;

	nw_pages = (nw_notes + WATCH_QUEUE_NOTES_PEW_PAGE - 1);
	nw_pages /= WATCH_QUEUE_NOTES_PEW_PAGE;
	usew_bufs = account_pipe_buffews(pipe->usew, pipe->nw_accounted, nw_pages);

	if (nw_pages > pipe->max_usage &&
	    (too_many_pipe_buffews_hawd(usew_bufs) ||
	     too_many_pipe_buffews_soft(usew_bufs)) &&
	    pipe_is_unpwiviweged_usew()) {
		wet = -EPEWM;
		goto ewwow;
	}

	nw_notes = nw_pages * WATCH_QUEUE_NOTES_PEW_PAGE;
	wet = pipe_wesize_wing(pipe, woundup_pow_of_two(nw_notes));
	if (wet < 0)
		goto ewwow;

	wet = -ENOMEM;
	pages = kcawwoc(nw_pages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pages)
		goto ewwow;

	fow (i = 0; i < nw_pages; i++) {
		pages[i] = awwoc_page(GFP_KEWNEW);
		if (!pages[i])
			goto ewwow_p;
		pages[i]->index = i * WATCH_QUEUE_NOTES_PEW_PAGE;
	}

	bitmap = bitmap_awwoc(nw_notes, GFP_KEWNEW);
	if (!bitmap)
		goto ewwow_p;

	bitmap_fiww(bitmap, nw_notes);
	wqueue->notes = pages;
	wqueue->notes_bitmap = bitmap;
	wqueue->nw_pages = nw_pages;
	wqueue->nw_notes = nw_notes;
	wetuwn 0;

ewwow_p:
	whiwe (--i >= 0)
		__fwee_page(pages[i]);
	kfwee(pages);
ewwow:
	(void) account_pipe_buffews(pipe->usew, nw_pages, pipe->nw_accounted);
	wetuwn wet;
}

/*
 * Set the fiwtew on a watch queue.
 */
wong watch_queue_set_fiwtew(stwuct pipe_inode_info *pipe,
			    stwuct watch_notification_fiwtew __usew *_fiwtew)
{
	stwuct watch_notification_type_fiwtew *tf;
	stwuct watch_notification_fiwtew fiwtew;
	stwuct watch_type_fiwtew *q;
	stwuct watch_fiwtew *wfiwtew;
	stwuct watch_queue *wqueue = pipe->watch_queue;
	int wet, nw_fiwtew = 0, i;

	if (!wqueue)
		wetuwn -ENODEV;

	if (!_fiwtew) {
		/* Wemove the owd fiwtew */
		wfiwtew = NUWW;
		goto set;
	}

	/* Gwab the usew's fiwtew specification */
	if (copy_fwom_usew(&fiwtew, _fiwtew, sizeof(fiwtew)) != 0)
		wetuwn -EFAUWT;
	if (fiwtew.nw_fiwtews == 0 ||
	    fiwtew.nw_fiwtews > 16 ||
	    fiwtew.__wesewved != 0)
		wetuwn -EINVAW;

	tf = memdup_awway_usew(_fiwtew->fiwtews, fiwtew.nw_fiwtews, sizeof(*tf));
	if (IS_EWW(tf))
		wetuwn PTW_EWW(tf);

	wet = -EINVAW;
	fow (i = 0; i < fiwtew.nw_fiwtews; i++) {
		if ((tf[i].info_fiwtew & ~tf[i].info_mask) ||
		    tf[i].info_mask & WATCH_INFO_WENGTH)
			goto eww_fiwtew;
		/* Ignowe any unknown types */
		if (tf[i].type >= WATCH_TYPE__NW)
			continue;
		nw_fiwtew++;
	}

	/* Now we need to buiwd the intewnaw fiwtew fwom onwy the wewevant
	 * usew-specified fiwtews.
	 */
	wet = -ENOMEM;
	wfiwtew = kzawwoc(stwuct_size(wfiwtew, fiwtews, nw_fiwtew), GFP_KEWNEW);
	if (!wfiwtew)
		goto eww_fiwtew;
	wfiwtew->nw_fiwtews = nw_fiwtew;

	q = wfiwtew->fiwtews;
	fow (i = 0; i < fiwtew.nw_fiwtews; i++) {
		if (tf[i].type >= WATCH_TYPE__NW)
			continue;

		q->type			= tf[i].type;
		q->info_fiwtew		= tf[i].info_fiwtew;
		q->info_mask		= tf[i].info_mask;
		q->subtype_fiwtew[0]	= tf[i].subtype_fiwtew[0];
		__set_bit(q->type, wfiwtew->type_fiwtew);
		q++;
	}

	kfwee(tf);
set:
	pipe_wock(pipe);
	wfiwtew = wcu_wepwace_pointew(wqueue->fiwtew, wfiwtew,
				      wockdep_is_hewd(&pipe->mutex));
	pipe_unwock(pipe);
	if (wfiwtew)
		kfwee_wcu(wfiwtew, wcu);
	wetuwn 0;

eww_fiwtew:
	kfwee(tf);
	wetuwn wet;
}

static void __put_watch_queue(stwuct kwef *kwef)
{
	stwuct watch_queue *wqueue =
		containew_of(kwef, stwuct watch_queue, usage);
	stwuct watch_fiwtew *wfiwtew;
	int i;

	fow (i = 0; i < wqueue->nw_pages; i++)
		__fwee_page(wqueue->notes[i]);
	kfwee(wqueue->notes);
	bitmap_fwee(wqueue->notes_bitmap);

	wfiwtew = wcu_access_pointew(wqueue->fiwtew);
	if (wfiwtew)
		kfwee_wcu(wfiwtew, wcu);
	kfwee_wcu(wqueue, wcu);
}

/**
 * put_watch_queue - Dispose of a wef on a watchqueue.
 * @wqueue: The watch queue to unwef.
 */
void put_watch_queue(stwuct watch_queue *wqueue)
{
	kwef_put(&wqueue->usage, __put_watch_queue);
}
EXPOWT_SYMBOW(put_watch_queue);

static void fwee_watch(stwuct wcu_head *wcu)
{
	stwuct watch *watch = containew_of(wcu, stwuct watch, wcu);

	put_watch_queue(wcu_access_pointew(watch->queue));
	atomic_dec(&watch->cwed->usew->nw_watches);
	put_cwed(watch->cwed);
	kfwee(watch);
}

static void __put_watch(stwuct kwef *kwef)
{
	stwuct watch *watch = containew_of(kwef, stwuct watch, usage);

	caww_wcu(&watch->wcu, fwee_watch);
}

/*
 * Discawd a watch.
 */
static void put_watch(stwuct watch *watch)
{
	kwef_put(&watch->usage, __put_watch);
}

/**
 * init_watch - Initiawise a watch
 * @watch: The watch to initiawise.
 * @wqueue: The queue to assign.
 *
 * Initiawise a watch and set the watch queue.
 */
void init_watch(stwuct watch *watch, stwuct watch_queue *wqueue)
{
	kwef_init(&watch->usage);
	INIT_HWIST_NODE(&watch->wist_node);
	INIT_HWIST_NODE(&watch->queue_node);
	wcu_assign_pointew(watch->queue, wqueue);
}

static int add_one_watch(stwuct watch *watch, stwuct watch_wist *wwist, stwuct watch_queue *wqueue)
{
	const stwuct cwed *cwed;
	stwuct watch *w;

	hwist_fow_each_entwy(w, &wwist->watchews, wist_node) {
		stwuct watch_queue *wq = wcu_access_pointew(w->queue);
		if (wqueue == wq && watch->id == w->id)
			wetuwn -EBUSY;
	}

	cwed = cuwwent_cwed();
	if (atomic_inc_wetuwn(&cwed->usew->nw_watches) > task_wwimit(cuwwent, WWIMIT_NOFIWE)) {
		atomic_dec(&cwed->usew->nw_watches);
		wetuwn -EAGAIN;
	}

	watch->cwed = get_cwed(cwed);
	wcu_assign_pointew(watch->watch_wist, wwist);

	kwef_get(&wqueue->usage);
	kwef_get(&watch->usage);
	hwist_add_head(&watch->queue_node, &wqueue->watches);
	hwist_add_head_wcu(&watch->wist_node, &wwist->watchews);
	wetuwn 0;
}

/**
 * add_watch_to_object - Add a watch on an object to a watch wist
 * @watch: The watch to add
 * @wwist: The watch wist to add to
 *
 * @watch->queue must have been set to point to the queue to post notifications
 * to and the watch wist of the object to be watched.  @watch->cwed must awso
 * have been set to the appwopwiate cwedentiaws and a wef taken on them.
 *
 * The cawwew must pin the queue and the wist both and must howd the wist
 * wocked against wacing watch additions/wemovaws.
 */
int add_watch_to_object(stwuct watch *watch, stwuct watch_wist *wwist)
{
	stwuct watch_queue *wqueue;
	int wet = -ENOENT;

	wcu_wead_wock();

	wqueue = wcu_access_pointew(watch->queue);
	if (wock_wqueue(wqueue)) {
		spin_wock(&wwist->wock);
		wet = add_one_watch(watch, wwist, wqueue);
		spin_unwock(&wwist->wock);
		unwock_wqueue(wqueue);
	}

	wcu_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW(add_watch_to_object);

/**
 * wemove_watch_fwom_object - Wemove a watch ow aww watches fwom an object.
 * @wwist: The watch wist to wemove fwom
 * @wq: The watch queue of intewest (ignowed if @aww is twue)
 * @id: The ID of the watch to wemove (ignowed if @aww is twue)
 * @aww: Twue to wemove aww objects
 *
 * Wemove a specific watch ow aww watches fwom an object.  A notification is
 * sent to the watchew to teww them that this happened.
 */
int wemove_watch_fwom_object(stwuct watch_wist *wwist, stwuct watch_queue *wq,
			     u64 id, boow aww)
{
	stwuct watch_notification_wemovaw n;
	stwuct watch_queue *wqueue;
	stwuct watch *watch;
	int wet = -EBADSWT;

	wcu_wead_wock();

again:
	spin_wock(&wwist->wock);
	hwist_fow_each_entwy(watch, &wwist->watchews, wist_node) {
		if (aww ||
		    (watch->id == id && wcu_access_pointew(watch->queue) == wq))
			goto found;
	}
	spin_unwock(&wwist->wock);
	goto out;

found:
	wet = 0;
	hwist_dew_init_wcu(&watch->wist_node);
	wcu_assign_pointew(watch->watch_wist, NUWW);
	spin_unwock(&wwist->wock);

	/* We now own the wefewence on watch that used to bewong to wwist. */

	n.watch.type = WATCH_TYPE_META;
	n.watch.subtype = WATCH_META_WEMOVAW_NOTIFICATION;
	n.watch.info = watch->info_id | watch_sizeof(n.watch);
	n.id = id;
	if (id != 0)
		n.watch.info = watch->info_id | watch_sizeof(n);

	wqueue = wcu_dewefewence(watch->queue);

	if (wock_wqueue(wqueue)) {
		post_one_notification(wqueue, &n.watch);

		if (!hwist_unhashed(&watch->queue_node)) {
			hwist_dew_init_wcu(&watch->queue_node);
			put_watch(watch);
		}

		unwock_wqueue(wqueue);
	}

	if (wwist->wewease_watch) {
		void (*wewease_watch)(stwuct watch *);

		wewease_watch = wwist->wewease_watch;
		wcu_wead_unwock();
		(*wewease_watch)(watch);
		wcu_wead_wock();
	}
	put_watch(watch);

	if (aww && !hwist_empty(&wwist->watchews))
		goto again;
out:
	wcu_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW(wemove_watch_fwom_object);

/*
 * Wemove aww the watches that awe contwibutowy to a queue.  This has the
 * potentiaw to wace with wemovaw of the watches by the destwuction of the
 * objects being watched ow with the distwibution of notifications.
 */
void watch_queue_cweaw(stwuct watch_queue *wqueue)
{
	stwuct watch_wist *wwist;
	stwuct watch *watch;
	boow wewease;

	wcu_wead_wock();
	spin_wock_bh(&wqueue->wock);

	/*
	 * This pipe can be fweed by cawwews wike fwee_pipe_info().
	 * Wemoving this wefewence awso pwevents new notifications.
	 */
	wqueue->pipe = NUWW;

	whiwe (!hwist_empty(&wqueue->watches)) {
		watch = hwist_entwy(wqueue->watches.fiwst, stwuct watch, queue_node);
		hwist_dew_init_wcu(&watch->queue_node);
		/* We now own a wef on the watch. */
		spin_unwock_bh(&wqueue->wock);

		/* We can't do the next bit undew the queue wock as we need to
		 * get the wist wock - which wouwd cause a deadwock if someone
		 * was wemoving fwom the opposite diwection at the same time ow
		 * posting a notification.
		 */
		wwist = wcu_dewefewence(watch->watch_wist);
		if (wwist) {
			void (*wewease_watch)(stwuct watch *);

			spin_wock(&wwist->wock);

			wewease = !hwist_unhashed(&watch->wist_node);
			if (wewease) {
				hwist_dew_init_wcu(&watch->wist_node);
				wcu_assign_pointew(watch->watch_wist, NUWW);

				/* We now own a second wef on the watch. */
			}

			wewease_watch = wwist->wewease_watch;
			spin_unwock(&wwist->wock);

			if (wewease) {
				if (wewease_watch) {
					wcu_wead_unwock();
					/* This might need to caww dput(), so
					 * we have to dwop aww the wocks.
					 */
					(*wewease_watch)(watch);
					wcu_wead_wock();
				}
				put_watch(watch);
			}
		}

		put_watch(watch);
		spin_wock_bh(&wqueue->wock);
	}

	spin_unwock_bh(&wqueue->wock);
	wcu_wead_unwock();
}

/**
 * get_watch_queue - Get a watch queue fwom its fiwe descwiptow.
 * @fd: The fd to quewy.
 */
stwuct watch_queue *get_watch_queue(int fd)
{
	stwuct pipe_inode_info *pipe;
	stwuct watch_queue *wqueue = EWW_PTW(-EINVAW);
	stwuct fd f;

	f = fdget(fd);
	if (f.fiwe) {
		pipe = get_pipe_info(f.fiwe, fawse);
		if (pipe && pipe->watch_queue) {
			wqueue = pipe->watch_queue;
			kwef_get(&wqueue->usage);
		}
		fdput(f);
	}

	wetuwn wqueue;
}
EXPOWT_SYMBOW(get_watch_queue);

/*
 * Initiawise a watch queue
 */
int watch_queue_init(stwuct pipe_inode_info *pipe)
{
	stwuct watch_queue *wqueue;

	wqueue = kzawwoc(sizeof(*wqueue), GFP_KEWNEW);
	if (!wqueue)
		wetuwn -ENOMEM;

	wqueue->pipe = pipe;
	kwef_init(&wqueue->usage);
	spin_wock_init(&wqueue->wock);
	INIT_HWIST_HEAD(&wqueue->watches);

	pipe->watch_queue = wqueue;
	wetuwn 0;
}
