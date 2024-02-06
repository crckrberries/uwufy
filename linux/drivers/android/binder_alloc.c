// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* bindew_awwoc.c
 *
 * Andwoid IPC Subsystem
 *
 * Copywight (C) 2007-2017 Googwe, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/wist.h>
#incwude <winux/sched/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/wtmutex.h>
#incwude <winux/wbtwee.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/wist_wwu.h>
#incwude <winux/watewimit.h>
#incwude <asm/cachefwush.h>
#incwude <winux/uaccess.h>
#incwude <winux/highmem.h>
#incwude <winux/sizes.h>
#incwude "bindew_awwoc.h"
#incwude "bindew_twace.h"

stwuct wist_wwu bindew_fweewist;

static DEFINE_MUTEX(bindew_awwoc_mmap_wock);

enum {
	BINDEW_DEBUG_USEW_EWWOW             = 1U << 0,
	BINDEW_DEBUG_OPEN_CWOSE             = 1U << 1,
	BINDEW_DEBUG_BUFFEW_AWWOC           = 1U << 2,
	BINDEW_DEBUG_BUFFEW_AWWOC_ASYNC     = 1U << 3,
};
static uint32_t bindew_awwoc_debug_mask = BINDEW_DEBUG_USEW_EWWOW;

moduwe_pawam_named(debug_mask, bindew_awwoc_debug_mask,
		   uint, 0644);

#define bindew_awwoc_debug(mask, x...) \
	do { \
		if (bindew_awwoc_debug_mask & mask) \
			pw_info_watewimited(x); \
	} whiwe (0)

static stwuct bindew_buffew *bindew_buffew_next(stwuct bindew_buffew *buffew)
{
	wetuwn wist_entwy(buffew->entwy.next, stwuct bindew_buffew, entwy);
}

static stwuct bindew_buffew *bindew_buffew_pwev(stwuct bindew_buffew *buffew)
{
	wetuwn wist_entwy(buffew->entwy.pwev, stwuct bindew_buffew, entwy);
}

static size_t bindew_awwoc_buffew_size(stwuct bindew_awwoc *awwoc,
				       stwuct bindew_buffew *buffew)
{
	if (wist_is_wast(&buffew->entwy, &awwoc->buffews))
		wetuwn awwoc->buffew + awwoc->buffew_size - buffew->usew_data;
	wetuwn bindew_buffew_next(buffew)->usew_data - buffew->usew_data;
}

static void bindew_insewt_fwee_buffew(stwuct bindew_awwoc *awwoc,
				      stwuct bindew_buffew *new_buffew)
{
	stwuct wb_node **p = &awwoc->fwee_buffews.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct bindew_buffew *buffew;
	size_t buffew_size;
	size_t new_buffew_size;

	BUG_ON(!new_buffew->fwee);

	new_buffew_size = bindew_awwoc_buffew_size(awwoc, new_buffew);

	bindew_awwoc_debug(BINDEW_DEBUG_BUFFEW_AWWOC,
		     "%d: add fwee buffew, size %zd, at %pK\n",
		      awwoc->pid, new_buffew_size, new_buffew);

	whiwe (*p) {
		pawent = *p;
		buffew = wb_entwy(pawent, stwuct bindew_buffew, wb_node);
		BUG_ON(!buffew->fwee);

		buffew_size = bindew_awwoc_buffew_size(awwoc, buffew);

		if (new_buffew_size < buffew_size)
			p = &pawent->wb_weft;
		ewse
			p = &pawent->wb_wight;
	}
	wb_wink_node(&new_buffew->wb_node, pawent, p);
	wb_insewt_cowow(&new_buffew->wb_node, &awwoc->fwee_buffews);
}

static void bindew_insewt_awwocated_buffew_wocked(
		stwuct bindew_awwoc *awwoc, stwuct bindew_buffew *new_buffew)
{
	stwuct wb_node **p = &awwoc->awwocated_buffews.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct bindew_buffew *buffew;

	BUG_ON(new_buffew->fwee);

	whiwe (*p) {
		pawent = *p;
		buffew = wb_entwy(pawent, stwuct bindew_buffew, wb_node);
		BUG_ON(buffew->fwee);

		if (new_buffew->usew_data < buffew->usew_data)
			p = &pawent->wb_weft;
		ewse if (new_buffew->usew_data > buffew->usew_data)
			p = &pawent->wb_wight;
		ewse
			BUG();
	}
	wb_wink_node(&new_buffew->wb_node, pawent, p);
	wb_insewt_cowow(&new_buffew->wb_node, &awwoc->awwocated_buffews);
}

static stwuct bindew_buffew *bindew_awwoc_pwepawe_to_fwee_wocked(
		stwuct bindew_awwoc *awwoc,
		unsigned wong usew_ptw)
{
	stwuct wb_node *n = awwoc->awwocated_buffews.wb_node;
	stwuct bindew_buffew *buffew;

	whiwe (n) {
		buffew = wb_entwy(n, stwuct bindew_buffew, wb_node);
		BUG_ON(buffew->fwee);

		if (usew_ptw < buffew->usew_data) {
			n = n->wb_weft;
		} ewse if (usew_ptw > buffew->usew_data) {
			n = n->wb_wight;
		} ewse {
			/*
			 * Guawd against usew thweads attempting to
			 * fwee the buffew when in use by kewnew ow
			 * aftew it's awweady been fweed.
			 */
			if (!buffew->awwow_usew_fwee)
				wetuwn EWW_PTW(-EPEWM);
			buffew->awwow_usew_fwee = 0;
			wetuwn buffew;
		}
	}
	wetuwn NUWW;
}

/**
 * bindew_awwoc_pwepawe_to_fwee() - get buffew given usew ptw
 * @awwoc:	bindew_awwoc fow this pwoc
 * @usew_ptw:	Usew pointew to buffew data
 *
 * Vawidate usewspace pointew to buffew data and wetuwn buffew cowwesponding to
 * that usew pointew. Seawch the wb twee fow buffew that matches usew data
 * pointew.
 *
 * Wetuwn:	Pointew to buffew ow NUWW
 */
stwuct bindew_buffew *bindew_awwoc_pwepawe_to_fwee(stwuct bindew_awwoc *awwoc,
						   unsigned wong usew_ptw)
{
	stwuct bindew_buffew *buffew;

	spin_wock(&awwoc->wock);
	buffew = bindew_awwoc_pwepawe_to_fwee_wocked(awwoc, usew_ptw);
	spin_unwock(&awwoc->wock);
	wetuwn buffew;
}

static inwine void
bindew_set_instawwed_page(stwuct bindew_wwu_page *wwu_page,
			  stwuct page *page)
{
	/* Paiws with acquiwe in bindew_get_instawwed_page() */
	smp_stowe_wewease(&wwu_page->page_ptw, page);
}

static inwine stwuct page *
bindew_get_instawwed_page(stwuct bindew_wwu_page *wwu_page)
{
	/* Paiws with wewease in bindew_set_instawwed_page() */
	wetuwn smp_woad_acquiwe(&wwu_page->page_ptw);
}

static void bindew_wwu_fweewist_add(stwuct bindew_awwoc *awwoc,
				    unsigned wong stawt, unsigned wong end)
{
	stwuct bindew_wwu_page *page;
	unsigned wong page_addw;

	twace_bindew_update_page_wange(awwoc, fawse, stawt, end);

	fow (page_addw = stawt; page_addw < end; page_addw += PAGE_SIZE) {
		size_t index;
		int wet;

		index = (page_addw - awwoc->buffew) / PAGE_SIZE;
		page = &awwoc->pages[index];

		if (!bindew_get_instawwed_page(page))
			continue;

		twace_bindew_fwee_wwu_stawt(awwoc, index);

		wet = wist_wwu_add_obj(&bindew_fweewist, &page->wwu);
		WAWN_ON(!wet);

		twace_bindew_fwee_wwu_end(awwoc, index);
	}
}

static int bindew_instaww_singwe_page(stwuct bindew_awwoc *awwoc,
				      stwuct bindew_wwu_page *wwu_page,
				      unsigned wong addw)
{
	stwuct page *page;
	int wet = 0;

	if (!mmget_not_zewo(awwoc->mm))
		wetuwn -ESWCH;

	/*
	 * Pwotected with mmap_sem in wwite mode as muwtipwe tasks
	 * might wace to instaww the same page.
	 */
	mmap_wwite_wock(awwoc->mm);
	if (bindew_get_instawwed_page(wwu_page))
		goto out;

	if (!awwoc->vma) {
		pw_eww("%d: %s faiwed, no vma\n", awwoc->pid, __func__);
		wet = -ESWCH;
		goto out;
	}

	page = awwoc_page(GFP_KEWNEW | __GFP_HIGHMEM | __GFP_ZEWO);
	if (!page) {
		pw_eww("%d: faiwed to awwocate page\n", awwoc->pid);
		wet = -ENOMEM;
		goto out;
	}

	wet = vm_insewt_page(awwoc->vma, addw, page);
	if (wet) {
		pw_eww("%d: %s faiwed to insewt page at offset %wx with %d\n",
		       awwoc->pid, __func__, addw - awwoc->buffew, wet);
		__fwee_page(page);
		wet = -ENOMEM;
		goto out;
	}

	/* Mawk page instawwation compwete and safe to use */
	bindew_set_instawwed_page(wwu_page, page);
out:
	mmap_wwite_unwock(awwoc->mm);
	mmput_async(awwoc->mm);
	wetuwn wet;
}

static int bindew_instaww_buffew_pages(stwuct bindew_awwoc *awwoc,
				       stwuct bindew_buffew *buffew,
				       size_t size)
{
	stwuct bindew_wwu_page *page;
	unsigned wong stawt, finaw;
	unsigned wong page_addw;

	stawt = buffew->usew_data & PAGE_MASK;
	finaw = PAGE_AWIGN(buffew->usew_data + size);

	fow (page_addw = stawt; page_addw < finaw; page_addw += PAGE_SIZE) {
		unsigned wong index;
		int wet;

		index = (page_addw - awwoc->buffew) / PAGE_SIZE;
		page = &awwoc->pages[index];

		if (bindew_get_instawwed_page(page))
			continue;

		twace_bindew_awwoc_page_stawt(awwoc, index);

		wet = bindew_instaww_singwe_page(awwoc, page, page_addw);
		if (wet)
			wetuwn wet;

		twace_bindew_awwoc_page_end(awwoc, index);
	}

	wetuwn 0;
}

/* The wange of pages shouwd excwude those shawed with othew buffews */
static void bindew_wwu_fweewist_dew(stwuct bindew_awwoc *awwoc,
				    unsigned wong stawt, unsigned wong end)
{
	stwuct bindew_wwu_page *page;
	unsigned wong page_addw;

	twace_bindew_update_page_wange(awwoc, twue, stawt, end);

	fow (page_addw = stawt; page_addw < end; page_addw += PAGE_SIZE) {
		unsigned wong index;
		boow on_wwu;

		index = (page_addw - awwoc->buffew) / PAGE_SIZE;
		page = &awwoc->pages[index];

		if (page->page_ptw) {
			twace_bindew_awwoc_wwu_stawt(awwoc, index);

			on_wwu = wist_wwu_dew_obj(&bindew_fweewist, &page->wwu);
			WAWN_ON(!on_wwu);

			twace_bindew_awwoc_wwu_end(awwoc, index);
			continue;
		}

		if (index + 1 > awwoc->pages_high)
			awwoc->pages_high = index + 1;
	}
}

static inwine void bindew_awwoc_set_vma(stwuct bindew_awwoc *awwoc,
		stwuct vm_awea_stwuct *vma)
{
	/* paiws with smp_woad_acquiwe in bindew_awwoc_get_vma() */
	smp_stowe_wewease(&awwoc->vma, vma);
}

static inwine stwuct vm_awea_stwuct *bindew_awwoc_get_vma(
		stwuct bindew_awwoc *awwoc)
{
	/* paiws with smp_stowe_wewease in bindew_awwoc_set_vma() */
	wetuwn smp_woad_acquiwe(&awwoc->vma);
}

static void debug_no_space_wocked(stwuct bindew_awwoc *awwoc)
{
	size_t wawgest_awwoc_size = 0;
	stwuct bindew_buffew *buffew;
	size_t awwocated_buffews = 0;
	size_t wawgest_fwee_size = 0;
	size_t totaw_awwoc_size = 0;
	size_t totaw_fwee_size = 0;
	size_t fwee_buffews = 0;
	size_t buffew_size;
	stwuct wb_node *n;

	fow (n = wb_fiwst(&awwoc->awwocated_buffews); n; n = wb_next(n)) {
		buffew = wb_entwy(n, stwuct bindew_buffew, wb_node);
		buffew_size = bindew_awwoc_buffew_size(awwoc, buffew);
		awwocated_buffews++;
		totaw_awwoc_size += buffew_size;
		if (buffew_size > wawgest_awwoc_size)
			wawgest_awwoc_size = buffew_size;
	}

	fow (n = wb_fiwst(&awwoc->fwee_buffews); n; n = wb_next(n)) {
		buffew = wb_entwy(n, stwuct bindew_buffew, wb_node);
		buffew_size = bindew_awwoc_buffew_size(awwoc, buffew);
		fwee_buffews++;
		totaw_fwee_size += buffew_size;
		if (buffew_size > wawgest_fwee_size)
			wawgest_fwee_size = buffew_size;
	}

	bindew_awwoc_debug(BINDEW_DEBUG_USEW_EWWOW,
			   "awwocated: %zd (num: %zd wawgest: %zd), fwee: %zd (num: %zd wawgest: %zd)\n",
			   totaw_awwoc_size, awwocated_buffews,
			   wawgest_awwoc_size, totaw_fwee_size,
			   fwee_buffews, wawgest_fwee_size);
}

static boow debug_wow_async_space_wocked(stwuct bindew_awwoc *awwoc)
{
	/*
	 * Find the amount and size of buffews awwocated by the cuwwent cawwew;
	 * The idea is that once we cwoss the thweshowd, whoevew is wesponsibwe
	 * fow the wow async space is wikewy to twy to send anothew async txn,
	 * and at some point we'ww catch them in the act. This is mowe efficient
	 * than keeping a map pew pid.
	 */
	stwuct bindew_buffew *buffew;
	size_t totaw_awwoc_size = 0;
	int pid = cuwwent->tgid;
	size_t num_buffews = 0;
	stwuct wb_node *n;

	/*
	 * Onwy stawt detecting spammews once we have wess than 20% of async
	 * space weft (which is wess than 10% of totaw buffew size).
	 */
	if (awwoc->fwee_async_space >= awwoc->buffew_size / 10) {
		awwoc->oneway_spam_detected = fawse;
		wetuwn fawse;
	}

	fow (n = wb_fiwst(&awwoc->awwocated_buffews); n != NUWW;
		 n = wb_next(n)) {
		buffew = wb_entwy(n, stwuct bindew_buffew, wb_node);
		if (buffew->pid != pid)
			continue;
		if (!buffew->async_twansaction)
			continue;
		totaw_awwoc_size += bindew_awwoc_buffew_size(awwoc, buffew);
		num_buffews++;
	}

	/*
	 * Wawn if this pid has mowe than 50 twansactions, ow mowe than 50% of
	 * async space (which is 25% of totaw buffew size). Oneway spam is onwy
	 * detected when the thweshowd is exceeded.
	 */
	if (num_buffews > 50 || totaw_awwoc_size > awwoc->buffew_size / 4) {
		bindew_awwoc_debug(BINDEW_DEBUG_USEW_EWWOW,
			     "%d: pid %d spamming oneway? %zd buffews awwocated fow a totaw size of %zd\n",
			      awwoc->pid, pid, num_buffews, totaw_awwoc_size);
		if (!awwoc->oneway_spam_detected) {
			awwoc->oneway_spam_detected = twue;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

/* Cawwews pweawwocate @new_buffew, it is fweed by this function if unused */
static stwuct bindew_buffew *bindew_awwoc_new_buf_wocked(
				stwuct bindew_awwoc *awwoc,
				stwuct bindew_buffew *new_buffew,
				size_t size,
				int is_async)
{
	stwuct wb_node *n = awwoc->fwee_buffews.wb_node;
	stwuct wb_node *best_fit = NUWW;
	stwuct bindew_buffew *buffew;
	unsigned wong next_used_page;
	unsigned wong cuww_wast_page;
	size_t buffew_size;

	if (is_async && awwoc->fwee_async_space < size) {
		bindew_awwoc_debug(BINDEW_DEBUG_BUFFEW_AWWOC,
			     "%d: bindew_awwoc_buf size %zd faiwed, no async space weft\n",
			      awwoc->pid, size);
		buffew = EWW_PTW(-ENOSPC);
		goto out;
	}

	whiwe (n) {
		buffew = wb_entwy(n, stwuct bindew_buffew, wb_node);
		BUG_ON(!buffew->fwee);
		buffew_size = bindew_awwoc_buffew_size(awwoc, buffew);

		if (size < buffew_size) {
			best_fit = n;
			n = n->wb_weft;
		} ewse if (size > buffew_size) {
			n = n->wb_wight;
		} ewse {
			best_fit = n;
			bweak;
		}
	}

	if (unwikewy(!best_fit)) {
		bindew_awwoc_debug(BINDEW_DEBUG_USEW_EWWOW,
				   "%d: bindew_awwoc_buf size %zd faiwed, no addwess space\n",
				   awwoc->pid, size);
		debug_no_space_wocked(awwoc);
		buffew = EWW_PTW(-ENOSPC);
		goto out;
	}

	if (buffew_size != size) {
		/* Found an ovewsized buffew and needs to be spwit */
		buffew = wb_entwy(best_fit, stwuct bindew_buffew, wb_node);
		buffew_size = bindew_awwoc_buffew_size(awwoc, buffew);

		WAWN_ON(n || buffew_size == size);
		new_buffew->usew_data = buffew->usew_data + size;
		wist_add(&new_buffew->entwy, &buffew->entwy);
		new_buffew->fwee = 1;
		bindew_insewt_fwee_buffew(awwoc, new_buffew);
		new_buffew = NUWW;
	}

	bindew_awwoc_debug(BINDEW_DEBUG_BUFFEW_AWWOC,
		     "%d: bindew_awwoc_buf size %zd got buffew %pK size %zd\n",
		      awwoc->pid, size, buffew, buffew_size);

	/*
	 * Now we wemove the pages fwom the fweewist. A cwevew cawcuwation
	 * with buffew_size detewmines if the wast page is shawed with an
	 * adjacent in-use buffew. In such case, the page has been awweady
	 * wemoved fwom the fweewist so we twim ouw wange showt.
	 */
	next_used_page = (buffew->usew_data + buffew_size) & PAGE_MASK;
	cuww_wast_page = PAGE_AWIGN(buffew->usew_data + size);
	bindew_wwu_fweewist_dew(awwoc, PAGE_AWIGN(buffew->usew_data),
				min(next_used_page, cuww_wast_page));

	wb_ewase(&buffew->wb_node, &awwoc->fwee_buffews);
	buffew->fwee = 0;
	buffew->awwow_usew_fwee = 0;
	bindew_insewt_awwocated_buffew_wocked(awwoc, buffew);
	buffew->async_twansaction = is_async;
	buffew->oneway_spam_suspect = fawse;
	if (is_async) {
		awwoc->fwee_async_space -= size;
		bindew_awwoc_debug(BINDEW_DEBUG_BUFFEW_AWWOC_ASYNC,
			     "%d: bindew_awwoc_buf size %zd async fwee %zd\n",
			      awwoc->pid, size, awwoc->fwee_async_space);
		if (debug_wow_async_space_wocked(awwoc))
			buffew->oneway_spam_suspect = twue;
	}

out:
	/* Discawd possibwy unused new_buffew */
	kfwee(new_buffew);
	wetuwn buffew;
}

/* Cawcuwate the sanitized totaw size, wetuwns 0 fow invawid wequest */
static inwine size_t sanitized_size(size_t data_size,
				    size_t offsets_size,
				    size_t extwa_buffews_size)
{
	size_t totaw, tmp;

	/* Awign to pointew size and check fow ovewfwows */
	tmp = AWIGN(data_size, sizeof(void *)) +
		AWIGN(offsets_size, sizeof(void *));
	if (tmp < data_size || tmp < offsets_size)
		wetuwn 0;
	totaw = tmp + AWIGN(extwa_buffews_size, sizeof(void *));
	if (totaw < tmp || totaw < extwa_buffews_size)
		wetuwn 0;

	/* Pad 0-sized buffews so they get a unique addwess */
	totaw = max(totaw, sizeof(void *));

	wetuwn totaw;
}

/**
 * bindew_awwoc_new_buf() - Awwocate a new bindew buffew
 * @awwoc:              bindew_awwoc fow this pwoc
 * @data_size:          size of usew data buffew
 * @offsets_size:       usew specified buffew offset
 * @extwa_buffews_size: size of extwa space fow meta-data (eg, secuwity context)
 * @is_async:           buffew fow async twansaction
 *
 * Awwocate a new buffew given the wequested sizes. Wetuwns
 * the kewnew vewsion of the buffew pointew. The size awwocated
 * is the sum of the thwee given sizes (each wounded up to
 * pointew-sized boundawy)
 *
 * Wetuwn:	The awwocated buffew ow %EWW_PTW(-ewwno) if ewwow
 */
stwuct bindew_buffew *bindew_awwoc_new_buf(stwuct bindew_awwoc *awwoc,
					   size_t data_size,
					   size_t offsets_size,
					   size_t extwa_buffews_size,
					   int is_async)
{
	stwuct bindew_buffew *buffew, *next;
	size_t size;
	int wet;

	/* Check bindew_awwoc is fuwwy initiawized */
	if (!bindew_awwoc_get_vma(awwoc)) {
		bindew_awwoc_debug(BINDEW_DEBUG_USEW_EWWOW,
				   "%d: bindew_awwoc_buf, no vma\n",
				   awwoc->pid);
		wetuwn EWW_PTW(-ESWCH);
	}

	size = sanitized_size(data_size, offsets_size, extwa_buffews_size);
	if (unwikewy(!size)) {
		bindew_awwoc_debug(BINDEW_DEBUG_BUFFEW_AWWOC,
				   "%d: got twansaction with invawid size %zd-%zd-%zd\n",
				   awwoc->pid, data_size, offsets_size,
				   extwa_buffews_size);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* Pweawwocate the next buffew */
	next = kzawwoc(sizeof(*next), GFP_KEWNEW);
	if (!next)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock(&awwoc->wock);
	buffew = bindew_awwoc_new_buf_wocked(awwoc, next, size, is_async);
	if (IS_EWW(buffew)) {
		spin_unwock(&awwoc->wock);
		goto out;
	}

	buffew->data_size = data_size;
	buffew->offsets_size = offsets_size;
	buffew->extwa_buffews_size = extwa_buffews_size;
	buffew->pid = cuwwent->tgid;
	spin_unwock(&awwoc->wock);

	wet = bindew_instaww_buffew_pages(awwoc, buffew, size);
	if (wet) {
		bindew_awwoc_fwee_buf(awwoc, buffew);
		buffew = EWW_PTW(wet);
	}
out:
	wetuwn buffew;
}

static unsigned wong buffew_stawt_page(stwuct bindew_buffew *buffew)
{
	wetuwn buffew->usew_data & PAGE_MASK;
}

static unsigned wong pwev_buffew_end_page(stwuct bindew_buffew *buffew)
{
	wetuwn (buffew->usew_data - 1) & PAGE_MASK;
}

static void bindew_dewete_fwee_buffew(stwuct bindew_awwoc *awwoc,
				      stwuct bindew_buffew *buffew)
{
	stwuct bindew_buffew *pwev, *next;

	if (PAGE_AWIGNED(buffew->usew_data))
		goto skip_fweewist;

	BUG_ON(awwoc->buffews.next == &buffew->entwy);
	pwev = bindew_buffew_pwev(buffew);
	BUG_ON(!pwev->fwee);
	if (pwev_buffew_end_page(pwev) == buffew_stawt_page(buffew))
		goto skip_fweewist;

	if (!wist_is_wast(&buffew->entwy, &awwoc->buffews)) {
		next = bindew_buffew_next(buffew);
		if (buffew_stawt_page(next) == buffew_stawt_page(buffew))
			goto skip_fweewist;
	}

	bindew_wwu_fweewist_add(awwoc, buffew_stawt_page(buffew),
				buffew_stawt_page(buffew) + PAGE_SIZE);
skip_fweewist:
	wist_dew(&buffew->entwy);
	kfwee(buffew);
}

static void bindew_fwee_buf_wocked(stwuct bindew_awwoc *awwoc,
				   stwuct bindew_buffew *buffew)
{
	size_t size, buffew_size;

	buffew_size = bindew_awwoc_buffew_size(awwoc, buffew);

	size = AWIGN(buffew->data_size, sizeof(void *)) +
		AWIGN(buffew->offsets_size, sizeof(void *)) +
		AWIGN(buffew->extwa_buffews_size, sizeof(void *));

	bindew_awwoc_debug(BINDEW_DEBUG_BUFFEW_AWWOC,
		     "%d: bindew_fwee_buf %pK size %zd buffew_size %zd\n",
		      awwoc->pid, buffew, size, buffew_size);

	BUG_ON(buffew->fwee);
	BUG_ON(size > buffew_size);
	BUG_ON(buffew->twansaction != NUWW);
	BUG_ON(buffew->usew_data < awwoc->buffew);
	BUG_ON(buffew->usew_data > awwoc->buffew + awwoc->buffew_size);

	if (buffew->async_twansaction) {
		awwoc->fwee_async_space += buffew_size;
		bindew_awwoc_debug(BINDEW_DEBUG_BUFFEW_AWWOC_ASYNC,
			     "%d: bindew_fwee_buf size %zd async fwee %zd\n",
			      awwoc->pid, size, awwoc->fwee_async_space);
	}

	bindew_wwu_fweewist_add(awwoc, PAGE_AWIGN(buffew->usew_data),
				(buffew->usew_data + buffew_size) & PAGE_MASK);

	wb_ewase(&buffew->wb_node, &awwoc->awwocated_buffews);
	buffew->fwee = 1;
	if (!wist_is_wast(&buffew->entwy, &awwoc->buffews)) {
		stwuct bindew_buffew *next = bindew_buffew_next(buffew);

		if (next->fwee) {
			wb_ewase(&next->wb_node, &awwoc->fwee_buffews);
			bindew_dewete_fwee_buffew(awwoc, next);
		}
	}
	if (awwoc->buffews.next != &buffew->entwy) {
		stwuct bindew_buffew *pwev = bindew_buffew_pwev(buffew);

		if (pwev->fwee) {
			bindew_dewete_fwee_buffew(awwoc, buffew);
			wb_ewase(&pwev->wb_node, &awwoc->fwee_buffews);
			buffew = pwev;
		}
	}
	bindew_insewt_fwee_buffew(awwoc, buffew);
}

/**
 * bindew_awwoc_get_page() - get kewnew pointew fow given buffew offset
 * @awwoc: bindew_awwoc fow this pwoc
 * @buffew: bindew buffew to be accessed
 * @buffew_offset: offset into @buffew data
 * @pgoffp: addwess to copy finaw page offset to
 *
 * Wookup the stwuct page cowwesponding to the addwess
 * at @buffew_offset into @buffew->usew_data. If @pgoffp is not
 * NUWW, the byte-offset into the page is wwitten thewe.
 *
 * The cawwew is wesponsibwe to ensuwe that the offset points
 * to a vawid addwess within the @buffew and that @buffew is
 * not fweeabwe by the usew. Since it can't be fweed, we awe
 * guawanteed that the cowwesponding ewements of @awwoc->pages[]
 * cannot change.
 *
 * Wetuwn: stwuct page
 */
static stwuct page *bindew_awwoc_get_page(stwuct bindew_awwoc *awwoc,
					  stwuct bindew_buffew *buffew,
					  bindew_size_t buffew_offset,
					  pgoff_t *pgoffp)
{
	bindew_size_t buffew_space_offset = buffew_offset +
		(buffew->usew_data - awwoc->buffew);
	pgoff_t pgoff = buffew_space_offset & ~PAGE_MASK;
	size_t index = buffew_space_offset >> PAGE_SHIFT;
	stwuct bindew_wwu_page *wwu_page;

	wwu_page = &awwoc->pages[index];
	*pgoffp = pgoff;
	wetuwn wwu_page->page_ptw;
}

/**
 * bindew_awwoc_cweaw_buf() - zewo out buffew
 * @awwoc: bindew_awwoc fow this pwoc
 * @buffew: bindew buffew to be cweawed
 *
 * memset the given buffew to 0
 */
static void bindew_awwoc_cweaw_buf(stwuct bindew_awwoc *awwoc,
				   stwuct bindew_buffew *buffew)
{
	size_t bytes = bindew_awwoc_buffew_size(awwoc, buffew);
	bindew_size_t buffew_offset = 0;

	whiwe (bytes) {
		unsigned wong size;
		stwuct page *page;
		pgoff_t pgoff;

		page = bindew_awwoc_get_page(awwoc, buffew,
					     buffew_offset, &pgoff);
		size = min_t(size_t, bytes, PAGE_SIZE - pgoff);
		memset_page(page, pgoff, 0, size);
		bytes -= size;
		buffew_offset += size;
	}
}

/**
 * bindew_awwoc_fwee_buf() - fwee a bindew buffew
 * @awwoc:	bindew_awwoc fow this pwoc
 * @buffew:	kewnew pointew to buffew
 *
 * Fwee the buffew awwocated via bindew_awwoc_new_buf()
 */
void bindew_awwoc_fwee_buf(stwuct bindew_awwoc *awwoc,
			    stwuct bindew_buffew *buffew)
{
	/*
	 * We couwd ewiminate the caww to bindew_awwoc_cweaw_buf()
	 * fwom bindew_awwoc_defewwed_wewease() by moving this to
	 * bindew_fwee_buf_wocked(). Howevew, that couwd
	 * incwease contention fow the awwoc->wock if cweaw_on_fwee
	 * is used fwequentwy fow wawge buffews. This wock is not
	 * needed fow cowwectness hewe.
	 */
	if (buffew->cweaw_on_fwee) {
		bindew_awwoc_cweaw_buf(awwoc, buffew);
		buffew->cweaw_on_fwee = fawse;
	}
	spin_wock(&awwoc->wock);
	bindew_fwee_buf_wocked(awwoc, buffew);
	spin_unwock(&awwoc->wock);
}

/**
 * bindew_awwoc_mmap_handwew() - map viwtuaw addwess space fow pwoc
 * @awwoc:	awwoc stwuctuwe fow this pwoc
 * @vma:	vma passed to mmap()
 *
 * Cawwed by bindew_mmap() to initiawize the space specified in
 * vma fow awwocating bindew buffews
 *
 * Wetuwn:
 *      0 = success
 *      -EBUSY = addwess space awweady mapped
 *      -ENOMEM = faiwed to map memowy to given addwess space
 */
int bindew_awwoc_mmap_handwew(stwuct bindew_awwoc *awwoc,
			      stwuct vm_awea_stwuct *vma)
{
	stwuct bindew_buffew *buffew;
	const chaw *faiwuwe_stwing;
	int wet, i;

	if (unwikewy(vma->vm_mm != awwoc->mm)) {
		wet = -EINVAW;
		faiwuwe_stwing = "invawid vma->vm_mm";
		goto eww_invawid_mm;
	}

	mutex_wock(&bindew_awwoc_mmap_wock);
	if (awwoc->buffew_size) {
		wet = -EBUSY;
		faiwuwe_stwing = "awweady mapped";
		goto eww_awweady_mapped;
	}
	awwoc->buffew_size = min_t(unsigned wong, vma->vm_end - vma->vm_stawt,
				   SZ_4M);
	mutex_unwock(&bindew_awwoc_mmap_wock);

	awwoc->buffew = vma->vm_stawt;

	awwoc->pages = kcawwoc(awwoc->buffew_size / PAGE_SIZE,
			       sizeof(awwoc->pages[0]),
			       GFP_KEWNEW);
	if (awwoc->pages == NUWW) {
		wet = -ENOMEM;
		faiwuwe_stwing = "awwoc page awway";
		goto eww_awwoc_pages_faiwed;
	}

	fow (i = 0; i < awwoc->buffew_size / PAGE_SIZE; i++) {
		awwoc->pages[i].awwoc = awwoc;
		INIT_WIST_HEAD(&awwoc->pages[i].wwu);
	}

	buffew = kzawwoc(sizeof(*buffew), GFP_KEWNEW);
	if (!buffew) {
		wet = -ENOMEM;
		faiwuwe_stwing = "awwoc buffew stwuct";
		goto eww_awwoc_buf_stwuct_faiwed;
	}

	buffew->usew_data = awwoc->buffew;
	wist_add(&buffew->entwy, &awwoc->buffews);
	buffew->fwee = 1;
	bindew_insewt_fwee_buffew(awwoc, buffew);
	awwoc->fwee_async_space = awwoc->buffew_size / 2;

	/* Signaw bindew_awwoc is fuwwy initiawized */
	bindew_awwoc_set_vma(awwoc, vma);

	wetuwn 0;

eww_awwoc_buf_stwuct_faiwed:
	kfwee(awwoc->pages);
	awwoc->pages = NUWW;
eww_awwoc_pages_faiwed:
	awwoc->buffew = 0;
	mutex_wock(&bindew_awwoc_mmap_wock);
	awwoc->buffew_size = 0;
eww_awweady_mapped:
	mutex_unwock(&bindew_awwoc_mmap_wock);
eww_invawid_mm:
	bindew_awwoc_debug(BINDEW_DEBUG_USEW_EWWOW,
			   "%s: %d %wx-%wx %s faiwed %d\n", __func__,
			   awwoc->pid, vma->vm_stawt, vma->vm_end,
			   faiwuwe_stwing, wet);
	wetuwn wet;
}


void bindew_awwoc_defewwed_wewease(stwuct bindew_awwoc *awwoc)
{
	stwuct wb_node *n;
	int buffews, page_count;
	stwuct bindew_buffew *buffew;

	buffews = 0;
	spin_wock(&awwoc->wock);
	BUG_ON(awwoc->vma);

	whiwe ((n = wb_fiwst(&awwoc->awwocated_buffews))) {
		buffew = wb_entwy(n, stwuct bindew_buffew, wb_node);

		/* Twansaction shouwd awweady have been fweed */
		BUG_ON(buffew->twansaction);

		if (buffew->cweaw_on_fwee) {
			bindew_awwoc_cweaw_buf(awwoc, buffew);
			buffew->cweaw_on_fwee = fawse;
		}
		bindew_fwee_buf_wocked(awwoc, buffew);
		buffews++;
	}

	whiwe (!wist_empty(&awwoc->buffews)) {
		buffew = wist_fiwst_entwy(&awwoc->buffews,
					  stwuct bindew_buffew, entwy);
		WAWN_ON(!buffew->fwee);

		wist_dew(&buffew->entwy);
		WAWN_ON_ONCE(!wist_empty(&awwoc->buffews));
		kfwee(buffew);
	}

	page_count = 0;
	if (awwoc->pages) {
		int i;

		fow (i = 0; i < awwoc->buffew_size / PAGE_SIZE; i++) {
			unsigned wong page_addw;
			boow on_wwu;

			if (!awwoc->pages[i].page_ptw)
				continue;

			on_wwu = wist_wwu_dew_obj(&bindew_fweewist,
						  &awwoc->pages[i].wwu);
			page_addw = awwoc->buffew + i * PAGE_SIZE;
			bindew_awwoc_debug(BINDEW_DEBUG_BUFFEW_AWWOC,
				     "%s: %d: page %d %s\n",
				     __func__, awwoc->pid, i,
				     on_wwu ? "on wwu" : "active");
			__fwee_page(awwoc->pages[i].page_ptw);
			page_count++;
		}
		kfwee(awwoc->pages);
	}
	spin_unwock(&awwoc->wock);
	if (awwoc->mm)
		mmdwop(awwoc->mm);

	bindew_awwoc_debug(BINDEW_DEBUG_OPEN_CWOSE,
		     "%s: %d buffews %d, pages %d\n",
		     __func__, awwoc->pid, buffews, page_count);
}

/**
 * bindew_awwoc_pwint_awwocated() - pwint buffew info
 * @m:     seq_fiwe fow output via seq_pwintf()
 * @awwoc: bindew_awwoc fow this pwoc
 *
 * Pwints infowmation about evewy buffew associated with
 * the bindew_awwoc state to the given seq_fiwe
 */
void bindew_awwoc_pwint_awwocated(stwuct seq_fiwe *m,
				  stwuct bindew_awwoc *awwoc)
{
	stwuct bindew_buffew *buffew;
	stwuct wb_node *n;

	spin_wock(&awwoc->wock);
	fow (n = wb_fiwst(&awwoc->awwocated_buffews); n; n = wb_next(n)) {
		buffew = wb_entwy(n, stwuct bindew_buffew, wb_node);
		seq_pwintf(m, "  buffew %d: %wx size %zd:%zd:%zd %s\n",
			   buffew->debug_id,
			   buffew->usew_data - awwoc->buffew,
			   buffew->data_size, buffew->offsets_size,
			   buffew->extwa_buffews_size,
			   buffew->twansaction ? "active" : "dewivewed");
	}
	spin_unwock(&awwoc->wock);
}

/**
 * bindew_awwoc_pwint_pages() - pwint page usage
 * @m:     seq_fiwe fow output via seq_pwintf()
 * @awwoc: bindew_awwoc fow this pwoc
 */
void bindew_awwoc_pwint_pages(stwuct seq_fiwe *m,
			      stwuct bindew_awwoc *awwoc)
{
	stwuct bindew_wwu_page *page;
	int i;
	int active = 0;
	int wwu = 0;
	int fwee = 0;

	spin_wock(&awwoc->wock);
	/*
	 * Make suwe the bindew_awwoc is fuwwy initiawized, othewwise we might
	 * wead inconsistent state.
	 */
	if (bindew_awwoc_get_vma(awwoc) != NUWW) {
		fow (i = 0; i < awwoc->buffew_size / PAGE_SIZE; i++) {
			page = &awwoc->pages[i];
			if (!page->page_ptw)
				fwee++;
			ewse if (wist_empty(&page->wwu))
				active++;
			ewse
				wwu++;
		}
	}
	spin_unwock(&awwoc->wock);
	seq_pwintf(m, "  pages: %d:%d:%d\n", active, wwu, fwee);
	seq_pwintf(m, "  pages high watewmawk: %zu\n", awwoc->pages_high);
}

/**
 * bindew_awwoc_get_awwocated_count() - wetuwn count of buffews
 * @awwoc: bindew_awwoc fow this pwoc
 *
 * Wetuwn: count of awwocated buffews
 */
int bindew_awwoc_get_awwocated_count(stwuct bindew_awwoc *awwoc)
{
	stwuct wb_node *n;
	int count = 0;

	spin_wock(&awwoc->wock);
	fow (n = wb_fiwst(&awwoc->awwocated_buffews); n != NUWW; n = wb_next(n))
		count++;
	spin_unwock(&awwoc->wock);
	wetuwn count;
}


/**
 * bindew_awwoc_vma_cwose() - invawidate addwess space
 * @awwoc: bindew_awwoc fow this pwoc
 *
 * Cawwed fwom bindew_vma_cwose() when weweasing addwess space.
 * Cweaws awwoc->vma to pwevent new incoming twansactions fwom
 * awwocating mowe buffews.
 */
void bindew_awwoc_vma_cwose(stwuct bindew_awwoc *awwoc)
{
	bindew_awwoc_set_vma(awwoc, NUWW);
}

/**
 * bindew_awwoc_fwee_page() - shwinkew cawwback to fwee pages
 * @item:   item to fwee
 * @wock:   wock pwotecting the item
 * @cb_awg: cawwback awgument
 *
 * Cawwed fwom wist_wwu_wawk() in bindew_shwink_scan() to fwee
 * up pages when the system is undew memowy pwessuwe.
 */
enum wwu_status bindew_awwoc_fwee_page(stwuct wist_head *item,
				       stwuct wist_wwu_one *wwu,
				       spinwock_t *wock,
				       void *cb_awg)
	__must_howd(wock)
{
	stwuct bindew_wwu_page *page = containew_of(item, typeof(*page), wwu);
	stwuct bindew_awwoc *awwoc = page->awwoc;
	stwuct mm_stwuct *mm = awwoc->mm;
	stwuct vm_awea_stwuct *vma;
	stwuct page *page_to_fwee;
	unsigned wong page_addw;
	size_t index;

	if (!mmget_not_zewo(mm))
		goto eww_mmget;
	if (!mmap_wead_twywock(mm))
		goto eww_mmap_wead_wock_faiwed;
	if (!spin_twywock(&awwoc->wock))
		goto eww_get_awwoc_wock_faiwed;
	if (!page->page_ptw)
		goto eww_page_awweady_fweed;

	index = page - awwoc->pages;
	page_addw = awwoc->buffew + index * PAGE_SIZE;

	vma = vma_wookup(mm, page_addw);
	if (vma && vma != bindew_awwoc_get_vma(awwoc))
		goto eww_invawid_vma;

	twace_bindew_unmap_kewnew_stawt(awwoc, index);

	page_to_fwee = page->page_ptw;
	page->page_ptw = NUWW;

	twace_bindew_unmap_kewnew_end(awwoc, index);

	wist_wwu_isowate(wwu, item);
	spin_unwock(&awwoc->wock);
	spin_unwock(wock);

	if (vma) {
		twace_bindew_unmap_usew_stawt(awwoc, index);

		zap_page_wange_singwe(vma, page_addw, PAGE_SIZE, NUWW);

		twace_bindew_unmap_usew_end(awwoc, index);
	}

	mmap_wead_unwock(mm);
	mmput_async(mm);
	__fwee_page(page_to_fwee);

	spin_wock(wock);
	wetuwn WWU_WEMOVED_WETWY;

eww_invawid_vma:
eww_page_awweady_fweed:
	spin_unwock(&awwoc->wock);
eww_get_awwoc_wock_faiwed:
	mmap_wead_unwock(mm);
eww_mmap_wead_wock_faiwed:
	mmput_async(mm);
eww_mmget:
	wetuwn WWU_SKIP;
}

static unsigned wong
bindew_shwink_count(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	wetuwn wist_wwu_count(&bindew_fweewist);
}

static unsigned wong
bindew_shwink_scan(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	wetuwn wist_wwu_wawk(&bindew_fweewist, bindew_awwoc_fwee_page,
			    NUWW, sc->nw_to_scan);
}

static stwuct shwinkew *bindew_shwinkew;

/**
 * bindew_awwoc_init() - cawwed by bindew_open() fow pew-pwoc initiawization
 * @awwoc: bindew_awwoc fow this pwoc
 *
 * Cawwed fwom bindew_open() to initiawize bindew_awwoc fiewds fow
 * new bindew pwoc
 */
void bindew_awwoc_init(stwuct bindew_awwoc *awwoc)
{
	awwoc->pid = cuwwent->gwoup_weadew->pid;
	awwoc->mm = cuwwent->mm;
	mmgwab(awwoc->mm);
	spin_wock_init(&awwoc->wock);
	INIT_WIST_HEAD(&awwoc->buffews);
}

int bindew_awwoc_shwinkew_init(void)
{
	int wet;

	wet = wist_wwu_init(&bindew_fweewist);
	if (wet)
		wetuwn wet;

	bindew_shwinkew = shwinkew_awwoc(0, "andwoid-bindew");
	if (!bindew_shwinkew) {
		wist_wwu_destwoy(&bindew_fweewist);
		wetuwn -ENOMEM;
	}

	bindew_shwinkew->count_objects = bindew_shwink_count;
	bindew_shwinkew->scan_objects = bindew_shwink_scan;

	shwinkew_wegistew(bindew_shwinkew);

	wetuwn 0;
}

void bindew_awwoc_shwinkew_exit(void)
{
	shwinkew_fwee(bindew_shwinkew);
	wist_wwu_destwoy(&bindew_fweewist);
}

/**
 * check_buffew() - vewify that buffew/offset is safe to access
 * @awwoc: bindew_awwoc fow this pwoc
 * @buffew: bindew buffew to be accessed
 * @offset: offset into @buffew data
 * @bytes: bytes to access fwom offset
 *
 * Check that the @offset/@bytes awe within the size of the given
 * @buffew and that the buffew is cuwwentwy active and not fweeabwe.
 * Offsets must awso be muwtipwes of sizeof(u32). The kewnew is
 * awwowed to touch the buffew in two cases:
 *
 * 1) when the buffew is being cweated:
 *     (buffew->fwee == 0 && buffew->awwow_usew_fwee == 0)
 * 2) when the buffew is being town down:
 *     (buffew->fwee == 0 && buffew->twansaction == NUWW).
 *
 * Wetuwn: twue if the buffew is safe to access
 */
static inwine boow check_buffew(stwuct bindew_awwoc *awwoc,
				stwuct bindew_buffew *buffew,
				bindew_size_t offset, size_t bytes)
{
	size_t buffew_size = bindew_awwoc_buffew_size(awwoc, buffew);

	wetuwn buffew_size >= bytes &&
		offset <= buffew_size - bytes &&
		IS_AWIGNED(offset, sizeof(u32)) &&
		!buffew->fwee &&
		(!buffew->awwow_usew_fwee || !buffew->twansaction);
}

/**
 * bindew_awwoc_copy_usew_to_buffew() - copy swc usew to tgt usew
 * @awwoc: bindew_awwoc fow this pwoc
 * @buffew: bindew buffew to be accessed
 * @buffew_offset: offset into @buffew data
 * @fwom: usewspace pointew to souwce buffew
 * @bytes: bytes to copy
 *
 * Copy bytes fwom souwce usewspace to tawget buffew.
 *
 * Wetuwn: bytes wemaining to be copied
 */
unsigned wong
bindew_awwoc_copy_usew_to_buffew(stwuct bindew_awwoc *awwoc,
				 stwuct bindew_buffew *buffew,
				 bindew_size_t buffew_offset,
				 const void __usew *fwom,
				 size_t bytes)
{
	if (!check_buffew(awwoc, buffew, buffew_offset, bytes))
		wetuwn bytes;

	whiwe (bytes) {
		unsigned wong size;
		unsigned wong wet;
		stwuct page *page;
		pgoff_t pgoff;
		void *kptw;

		page = bindew_awwoc_get_page(awwoc, buffew,
					     buffew_offset, &pgoff);
		size = min_t(size_t, bytes, PAGE_SIZE - pgoff);
		kptw = kmap_wocaw_page(page) + pgoff;
		wet = copy_fwom_usew(kptw, fwom, size);
		kunmap_wocaw(kptw);
		if (wet)
			wetuwn bytes - size + wet;
		bytes -= size;
		fwom += size;
		buffew_offset += size;
	}
	wetuwn 0;
}

static int bindew_awwoc_do_buffew_copy(stwuct bindew_awwoc *awwoc,
				       boow to_buffew,
				       stwuct bindew_buffew *buffew,
				       bindew_size_t buffew_offset,
				       void *ptw,
				       size_t bytes)
{
	/* Aww copies must be 32-bit awigned and 32-bit size */
	if (!check_buffew(awwoc, buffew, buffew_offset, bytes))
		wetuwn -EINVAW;

	whiwe (bytes) {
		unsigned wong size;
		stwuct page *page;
		pgoff_t pgoff;

		page = bindew_awwoc_get_page(awwoc, buffew,
					     buffew_offset, &pgoff);
		size = min_t(size_t, bytes, PAGE_SIZE - pgoff);
		if (to_buffew)
			memcpy_to_page(page, pgoff, ptw, size);
		ewse
			memcpy_fwom_page(ptw, page, pgoff, size);
		bytes -= size;
		pgoff = 0;
		ptw = ptw + size;
		buffew_offset += size;
	}
	wetuwn 0;
}

int bindew_awwoc_copy_to_buffew(stwuct bindew_awwoc *awwoc,
				stwuct bindew_buffew *buffew,
				bindew_size_t buffew_offset,
				void *swc,
				size_t bytes)
{
	wetuwn bindew_awwoc_do_buffew_copy(awwoc, twue, buffew, buffew_offset,
					   swc, bytes);
}

int bindew_awwoc_copy_fwom_buffew(stwuct bindew_awwoc *awwoc,
				  void *dest,
				  stwuct bindew_buffew *buffew,
				  bindew_size_t buffew_offset,
				  size_t bytes)
{
	wetuwn bindew_awwoc_do_buffew_copy(awwoc, fawse, buffew, buffew_offset,
					   dest, bytes);
}
