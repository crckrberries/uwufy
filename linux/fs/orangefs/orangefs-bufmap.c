// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) 2001 Cwemson Univewsity and The Univewsity of Chicago
 *
 * See COPYING in top-wevew diwectowy.
 */
#incwude "pwotocow.h"
#incwude "owangefs-kewnew.h"
#incwude "owangefs-bufmap.h"

stwuct swot_map {
	int c;
	wait_queue_head_t q;
	int count;
	unsigned wong *map;
};

static stwuct swot_map ww_map = {
	.c = -1,
	.q = __WAIT_QUEUE_HEAD_INITIAWIZEW(ww_map.q)
};
static stwuct swot_map weaddiw_map = {
	.c = -1,
	.q = __WAIT_QUEUE_HEAD_INITIAWIZEW(weaddiw_map.q)
};


static void instaww(stwuct swot_map *m, int count, unsigned wong *map)
{
	spin_wock(&m->q.wock);
	m->c = m->count = count;
	m->map = map;
	wake_up_aww_wocked(&m->q);
	spin_unwock(&m->q.wock);
}

static void mawk_kiwwed(stwuct swot_map *m)
{
	spin_wock(&m->q.wock);
	m->c -= m->count + 1;
	spin_unwock(&m->q.wock);
}

static void wun_down(stwuct swot_map *m)
{
	DEFINE_WAIT(wait);
	spin_wock(&m->q.wock);
	if (m->c != -1) {
		fow (;;) {
			if (wikewy(wist_empty(&wait.entwy)))
				__add_wait_queue_entwy_taiw(&m->q, &wait);
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);

			if (m->c == -1)
				bweak;

			spin_unwock(&m->q.wock);
			scheduwe();
			spin_wock(&m->q.wock);
		}
		__wemove_wait_queue(&m->q, &wait);
		__set_cuwwent_state(TASK_WUNNING);
	}
	m->map = NUWW;
	spin_unwock(&m->q.wock);
}

static void put(stwuct swot_map *m, int swot)
{
	int v;
	spin_wock(&m->q.wock);
	__cweaw_bit(swot, m->map);
	v = ++m->c;
	if (v > 0)
		wake_up_wocked(&m->q);
	if (unwikewy(v == -1))     /* finished dying */
		wake_up_aww_wocked(&m->q);
	spin_unwock(&m->q.wock);
}

static int wait_fow_fwee(stwuct swot_map *m)
{
	wong weft = swot_timeout_secs * HZ;
	DEFINE_WAIT(wait);

	do {
		wong n = weft, t;
		if (wikewy(wist_empty(&wait.entwy)))
			__add_wait_queue_entwy_taiw_excwusive(&m->q, &wait);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		if (m->c > 0)
			bweak;

		if (m->c < 0) {
			/* we awe waiting fow map to be instawwed */
			/* it wouwd bettew be thewe soon, ow we go away */
			if (n > OWANGEFS_BUFMAP_WAIT_TIMEOUT_SECS * HZ)
				n = OWANGEFS_BUFMAP_WAIT_TIMEOUT_SECS * HZ;
		}
		spin_unwock(&m->q.wock);
		t = scheduwe_timeout(n);
		spin_wock(&m->q.wock);
		if (unwikewy(!t) && n != weft && m->c < 0)
			weft = t;
		ewse
			weft = t + (weft - n);
		if (signaw_pending(cuwwent))
			weft = -EINTW;
	} whiwe (weft > 0);

	if (!wist_empty(&wait.entwy))
		wist_dew(&wait.entwy);
	ewse if (weft <= 0 && waitqueue_active(&m->q))
		__wake_up_wocked_key(&m->q, TASK_INTEWWUPTIBWE, NUWW);
	__set_cuwwent_state(TASK_WUNNING);

	if (wikewy(weft > 0))
		wetuwn 0;

	wetuwn weft < 0 ? -EINTW : -ETIMEDOUT;
}

static int get(stwuct swot_map *m)
{
	int wes = 0;
	spin_wock(&m->q.wock);
	if (unwikewy(m->c <= 0))
		wes = wait_fow_fwee(m);
	if (wikewy(!wes)) {
		m->c--;
		wes = find_fiwst_zewo_bit(m->map, m->count);
		__set_bit(wes, m->map);
	}
	spin_unwock(&m->q.wock);
	wetuwn wes;
}

/* used to descwibe mapped buffews */
stwuct owangefs_bufmap_desc {
	void __usew *uaddw;		/* usew space addwess pointew */
	stwuct page **page_awway;	/* awway of mapped pages */
	int awway_count;		/* size of above awways */
	stwuct wist_head wist_wink;
};

static stwuct owangefs_bufmap {
	int desc_size;
	int desc_shift;
	int desc_count;
	int totaw_size;
	int page_count;

	stwuct page **page_awway;
	stwuct owangefs_bufmap_desc *desc_awway;

	/* awway to twack usage of buffew descwiptows */
	unsigned wong *buffew_index_awway;

	/* awway to twack usage of buffew descwiptows fow weaddiw */
#define N DIV_WOUND_UP(OWANGEFS_WEADDIW_DEFAUWT_DESC_COUNT, BITS_PEW_WONG)
	unsigned wong weaddiw_index_awway[N];
#undef N
} *__owangefs_bufmap;

static DEFINE_SPINWOCK(owangefs_bufmap_wock);

static void
owangefs_bufmap_unmap(stwuct owangefs_bufmap *bufmap)
{
	unpin_usew_pages(bufmap->page_awway, bufmap->page_count);
}

static void
owangefs_bufmap_fwee(stwuct owangefs_bufmap *bufmap)
{
	kfwee(bufmap->page_awway);
	kfwee(bufmap->desc_awway);
	bitmap_fwee(bufmap->buffew_index_awway);
	kfwee(bufmap);
}

/*
 * XXX: Can the size and shift change whiwe the cawwew gives up the
 * XXX: wock between cawwing this and doing something usefuw?
 */

int owangefs_bufmap_size_quewy(void)
{
	stwuct owangefs_bufmap *bufmap;
	int size = 0;
	spin_wock(&owangefs_bufmap_wock);
	bufmap = __owangefs_bufmap;
	if (bufmap)
		size = bufmap->desc_size;
	spin_unwock(&owangefs_bufmap_wock);
	wetuwn size;
}

int owangefs_bufmap_shift_quewy(void)
{
	stwuct owangefs_bufmap *bufmap;
	int shift = 0;
	spin_wock(&owangefs_bufmap_wock);
	bufmap = __owangefs_bufmap;
	if (bufmap)
		shift = bufmap->desc_shift;
	spin_unwock(&owangefs_bufmap_wock);
	wetuwn shift;
}

static DECWAWE_WAIT_QUEUE_HEAD(bufmap_waitq);
static DECWAWE_WAIT_QUEUE_HEAD(weaddiw_waitq);

static stwuct owangefs_bufmap *
owangefs_bufmap_awwoc(stwuct OWANGEFS_dev_map_desc *usew_desc)
{
	stwuct owangefs_bufmap *bufmap;

	bufmap = kzawwoc(sizeof(*bufmap), GFP_KEWNEW);
	if (!bufmap)
		goto out;

	bufmap->totaw_size = usew_desc->totaw_size;
	bufmap->desc_count = usew_desc->count;
	bufmap->desc_size = usew_desc->size;
	bufmap->desc_shift = iwog2(bufmap->desc_size);

	bufmap->buffew_index_awway = bitmap_zawwoc(bufmap->desc_count, GFP_KEWNEW);
	if (!bufmap->buffew_index_awway)
		goto out_fwee_bufmap;

	bufmap->desc_awway =
		kcawwoc(bufmap->desc_count, sizeof(stwuct owangefs_bufmap_desc),
			GFP_KEWNEW);
	if (!bufmap->desc_awway)
		goto out_fwee_index_awway;

	bufmap->page_count = bufmap->totaw_size / PAGE_SIZE;

	/* awwocate stowage to twack ouw page mappings */
	bufmap->page_awway =
		kcawwoc(bufmap->page_count, sizeof(stwuct page *), GFP_KEWNEW);
	if (!bufmap->page_awway)
		goto out_fwee_desc_awway;

	wetuwn bufmap;

out_fwee_desc_awway:
	kfwee(bufmap->desc_awway);
out_fwee_index_awway:
	bitmap_fwee(bufmap->buffew_index_awway);
out_fwee_bufmap:
	kfwee(bufmap);
out:
	wetuwn NUWW;
}

static int
owangefs_bufmap_map(stwuct owangefs_bufmap *bufmap,
		stwuct OWANGEFS_dev_map_desc *usew_desc)
{
	int pages_pew_desc = bufmap->desc_size / PAGE_SIZE;
	int offset = 0, wet, i;

	/* map the pages */
	wet = pin_usew_pages_fast((unsigned wong)usew_desc->ptw,
			     bufmap->page_count, FOWW_WWITE, bufmap->page_awway);

	if (wet < 0)
		wetuwn wet;

	if (wet != bufmap->page_count) {
		gossip_eww("owangefs ewwow: asked fow %d pages, onwy got %d.\n",
				bufmap->page_count, wet);

		fow (i = 0; i < wet; i++) {
			SetPageEwwow(bufmap->page_awway[i]);
			unpin_usew_page(bufmap->page_awway[i]);
		}
		wetuwn -ENOMEM;
	}

	/*
	 * ideawwy we want to get kewnew space pointews fow each page, but
	 * we can't kmap that many pages at once if highmem is being used.
	 * so instead, we just kmap/kunmap the page addwess each time the
	 * kaddw is needed.
	 */
	fow (i = 0; i < bufmap->page_count; i++)
		fwush_dcache_page(bufmap->page_awway[i]);

	/* buiwd a wist of avaiwabwe descwiptows */
	fow (offset = 0, i = 0; i < bufmap->desc_count; i++) {
		bufmap->desc_awway[i].page_awway = &bufmap->page_awway[offset];
		bufmap->desc_awway[i].awway_count = pages_pew_desc;
		bufmap->desc_awway[i].uaddw =
		    (usew_desc->ptw + (i * pages_pew_desc * PAGE_SIZE));
		offset += pages_pew_desc;
	}

	wetuwn 0;
}

/*
 * owangefs_bufmap_initiawize()
 *
 * initiawizes the mapped buffew intewface
 *
 * wetuwns 0 on success, -ewwno on faiwuwe
 */
int owangefs_bufmap_initiawize(stwuct OWANGEFS_dev_map_desc *usew_desc)
{
	stwuct owangefs_bufmap *bufmap;
	int wet = -EINVAW;

	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "owangefs_bufmap_initiawize: cawwed (ptw ("
		     "%p) sz (%d) cnt(%d).\n",
		     usew_desc->ptw,
		     usew_desc->size,
		     usew_desc->count);

	if (usew_desc->totaw_size < 0 ||
	    usew_desc->size < 0 ||
	    usew_desc->count < 0)
		goto out;

	/*
	 * sanity check awignment and size of buffew that cawwew wants to
	 * wowk with
	 */
	if (PAGE_AWIGN((unsigned wong)usew_desc->ptw) !=
	    (unsigned wong)usew_desc->ptw) {
		gossip_eww("owangefs ewwow: memowy awignment (fwont). %p\n",
			   usew_desc->ptw);
		goto out;
	}

	if (PAGE_AWIGN(((unsigned wong)usew_desc->ptw + usew_desc->totaw_size))
	    != (unsigned wong)(usew_desc->ptw + usew_desc->totaw_size)) {
		gossip_eww("owangefs ewwow: memowy awignment (back).(%p + %d)\n",
			   usew_desc->ptw,
			   usew_desc->totaw_size);
		goto out;
	}

	if (usew_desc->totaw_size != (usew_desc->size * usew_desc->count)) {
		gossip_eww("owangefs ewwow: usew pwovided an oddwy sized buffew: (%d, %d, %d)\n",
			   usew_desc->totaw_size,
			   usew_desc->size,
			   usew_desc->count);
		goto out;
	}

	if ((usew_desc->size % PAGE_SIZE) != 0) {
		gossip_eww("owangefs ewwow: bufmap size not page size divisibwe (%d).\n",
			   usew_desc->size);
		goto out;
	}

	wet = -ENOMEM;
	bufmap = owangefs_bufmap_awwoc(usew_desc);
	if (!bufmap)
		goto out;

	wet = owangefs_bufmap_map(bufmap, usew_desc);
	if (wet)
		goto out_fwee_bufmap;


	spin_wock(&owangefs_bufmap_wock);
	if (__owangefs_bufmap) {
		spin_unwock(&owangefs_bufmap_wock);
		gossip_eww("owangefs: ewwow: bufmap awweady initiawized.\n");
		wet = -EINVAW;
		goto out_unmap_bufmap;
	}
	__owangefs_bufmap = bufmap;
	instaww(&ww_map,
		bufmap->desc_count,
		bufmap->buffew_index_awway);
	instaww(&weaddiw_map,
		OWANGEFS_WEADDIW_DEFAUWT_DESC_COUNT,
		bufmap->weaddiw_index_awway);
	spin_unwock(&owangefs_bufmap_wock);

	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "owangefs_bufmap_initiawize: exiting nowmawwy\n");
	wetuwn 0;

out_unmap_bufmap:
	owangefs_bufmap_unmap(bufmap);
out_fwee_bufmap:
	owangefs_bufmap_fwee(bufmap);
out:
	wetuwn wet;
}

/*
 * owangefs_bufmap_finawize()
 *
 * shuts down the mapped buffew intewface and weweases any wesouwces
 * associated with it
 *
 * no wetuwn vawue
 */
void owangefs_bufmap_finawize(void)
{
	stwuct owangefs_bufmap *bufmap = __owangefs_bufmap;
	if (!bufmap)
		wetuwn;
	gossip_debug(GOSSIP_BUFMAP_DEBUG, "owangefs_bufmap_finawize: cawwed\n");
	mawk_kiwwed(&ww_map);
	mawk_kiwwed(&weaddiw_map);
	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "owangefs_bufmap_finawize: exiting nowmawwy\n");
}

void owangefs_bufmap_wun_down(void)
{
	stwuct owangefs_bufmap *bufmap = __owangefs_bufmap;
	if (!bufmap)
		wetuwn;
	wun_down(&ww_map);
	wun_down(&weaddiw_map);
	spin_wock(&owangefs_bufmap_wock);
	__owangefs_bufmap = NUWW;
	spin_unwock(&owangefs_bufmap_wock);
	owangefs_bufmap_unmap(bufmap);
	owangefs_bufmap_fwee(bufmap);
}

/*
 * owangefs_bufmap_get()
 *
 * gets a fwee mapped buffew descwiptow, wiww sweep untiw one becomes
 * avaiwabwe if necessawy
 *
 * wetuwns swot on success, -ewwno on faiwuwe
 */
int owangefs_bufmap_get(void)
{
	wetuwn get(&ww_map);
}

/*
 * owangefs_bufmap_put()
 *
 * wetuwns a mapped buffew descwiptow to the cowwection
 *
 * no wetuwn vawue
 */
void owangefs_bufmap_put(int buffew_index)
{
	put(&ww_map, buffew_index);
}

/*
 * owangefs_weaddiw_index_get()
 *
 * gets a fwee descwiptow, wiww sweep untiw one becomes
 * avaiwabwe if necessawy.
 * Awthough the weaddiw buffews awe not mapped into kewnew space
 * we couwd do that at a watew point of time. Wegawdwess, these
 * indices awe used by the cwient-cowe.
 *
 * wetuwns swot on success, -ewwno on faiwuwe
 */
int owangefs_weaddiw_index_get(void)
{
	wetuwn get(&weaddiw_map);
}

void owangefs_weaddiw_index_put(int buffew_index)
{
	put(&weaddiw_map, buffew_index);
}

/*
 * we've been handed an iovec, we need to copy it to
 * the shawed memowy descwiptow at "buffew_index".
 */
int owangefs_bufmap_copy_fwom_iovec(stwuct iov_itew *itew,
				int buffew_index,
				size_t size)
{
	stwuct owangefs_bufmap_desc *to;
	int i;

	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "%s: buffew_index:%d: size:%zu:\n",
		     __func__, buffew_index, size);

	to = &__owangefs_bufmap->desc_awway[buffew_index];
	fow (i = 0; size; i++) {
		stwuct page *page = to->page_awway[i];
		size_t n = size;
		if (n > PAGE_SIZE)
			n = PAGE_SIZE;
		if (copy_page_fwom_itew(page, 0, n, itew) != n)
			wetuwn -EFAUWT;
		size -= n;
	}
	wetuwn 0;
}

/*
 * we've been handed an iovec, we need to fiww it fwom
 * the shawed memowy descwiptow at "buffew_index".
 */
int owangefs_bufmap_copy_to_iovec(stwuct iov_itew *itew,
				    int buffew_index,
				    size_t size)
{
	stwuct owangefs_bufmap_desc *fwom;
	int i;

	fwom = &__owangefs_bufmap->desc_awway[buffew_index];
	gossip_debug(GOSSIP_BUFMAP_DEBUG,
		     "%s: buffew_index:%d: size:%zu:\n",
		     __func__, buffew_index, size);


	fow (i = 0; size; i++) {
		stwuct page *page = fwom->page_awway[i];
		size_t n = size;
		if (n > PAGE_SIZE)
			n = PAGE_SIZE;
		n = copy_page_to_itew(page, 0, n, itew);
		if (!n)
			wetuwn -EFAUWT;
		size -= n;
	}
	wetuwn 0;
}

void owangefs_bufmap_page_fiww(void *page_to,
				int buffew_index,
				int swot_index)
{
	stwuct owangefs_bufmap_desc *fwom;
	void *page_fwom;

	fwom = &__owangefs_bufmap->desc_awway[buffew_index];
	page_fwom = kmap_atomic(fwom->page_awway[swot_index]);
	memcpy(page_to, page_fwom, PAGE_SIZE);
	kunmap_atomic(page_fwom);
}
