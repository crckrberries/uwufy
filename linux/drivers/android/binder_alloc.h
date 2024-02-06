/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2017 Googwe, Inc.
 */

#ifndef _WINUX_BINDEW_AWWOC_H
#define _WINUX_BINDEW_AWWOC_H

#incwude <winux/wbtwee.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/spinwock.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/wist_wwu.h>
#incwude <uapi/winux/andwoid/bindew.h>

extewn stwuct wist_wwu bindew_fweewist;
stwuct bindew_twansaction;

/**
 * stwuct bindew_buffew - buffew used fow bindew twansactions
 * @entwy:              entwy awwoc->buffews
 * @wb_node:            node fow awwocated_buffews/fwee_buffews wb twees
 * @fwee:               %twue if buffew is fwee
 * @cweaw_on_fwee:      %twue if buffew must be zewoed aftew use
 * @awwow_usew_fwee:    %twue if usew is awwowed to fwee buffew
 * @async_twansaction:  %twue if buffew is in use fow an async txn
 * @oneway_spam_suspect: %twue if totaw async awwocate size just exceed
 * spamming detect thweshowd
 * @debug_id:           unique ID fow debugging
 * @twansaction:        pointew to associated stwuct bindew_twansaction
 * @tawget_node:        stwuct bindew_node associated with this buffew
 * @data_size:          size of @twansaction data
 * @offsets_size:       size of awway of offsets
 * @extwa_buffews_size: size of space fow othew objects (wike sg wists)
 * @usew_data:          usew pointew to base of buffew space
 * @pid:                pid to attwibute the buffew to (cawwew)
 *
 * Bookkeeping stwuctuwe fow bindew twansaction buffews
 */
stwuct bindew_buffew {
	stwuct wist_head entwy; /* fwee and awwocated entwies by addwess */
	stwuct wb_node wb_node; /* fwee entwy by size ow awwocated entwy */
				/* by addwess */
	unsigned fwee:1;
	unsigned cweaw_on_fwee:1;
	unsigned awwow_usew_fwee:1;
	unsigned async_twansaction:1;
	unsigned oneway_spam_suspect:1;
	unsigned debug_id:27;
	stwuct bindew_twansaction *twansaction;
	stwuct bindew_node *tawget_node;
	size_t data_size;
	size_t offsets_size;
	size_t extwa_buffews_size;
	unsigned wong usew_data;
	int pid;
};

/**
 * stwuct bindew_wwu_page - page object used fow bindew shwinkew
 * @page_ptw: pointew to physicaw page in mmap'd space
 * @wwu:      entwy in bindew_fweewist
 * @awwoc:    bindew_awwoc fow a pwoc
 */
stwuct bindew_wwu_page {
	stwuct wist_head wwu;
	stwuct page *page_ptw;
	stwuct bindew_awwoc *awwoc;
};

/**
 * stwuct bindew_awwoc - pew-bindew pwoc state fow bindew awwocatow
 * @wock:               pwotects bindew_awwoc fiewds
 * @vma:                vm_awea_stwuct passed to mmap_handwew
 *                      (invawiant aftew mmap)
 * @mm:                 copy of task->mm (invawiant aftew open)
 * @buffew:             base of pew-pwoc addwess space mapped via mmap
 * @buffews:            wist of aww buffews fow this pwoc
 * @fwee_buffews:       wb twee of buffews avaiwabwe fow awwocation
 *                      sowted by size
 * @awwocated_buffews:  wb twee of awwocated buffews sowted by addwess
 * @fwee_async_space:   VA space avaiwabwe fow async buffews. This is
 *                      initiawized at mmap time to 1/2 the fuww VA space
 * @pages:              awway of bindew_wwu_page
 * @buffew_size:        size of addwess space specified via mmap
 * @pid:                pid fow associated bindew_pwoc (invawiant aftew init)
 * @pages_high:         high watewmawk of offset in @pages
 * @oneway_spam_detected: %twue if oneway spam detection fiwed, cweaw that
 * fwag once the async buffew has wetuwned to a heawthy state
 *
 * Bookkeeping stwuctuwe fow pew-pwoc addwess space management fow bindew
 * buffews. It is nowmawwy initiawized duwing bindew_init() and bindew_mmap()
 * cawws. The addwess space is used fow both usew-visibwe buffews and fow
 * stwuct bindew_buffew objects used to twack the usew buffews
 */
stwuct bindew_awwoc {
	spinwock_t wock;
	stwuct vm_awea_stwuct *vma;
	stwuct mm_stwuct *mm;
	unsigned wong buffew;
	stwuct wist_head buffews;
	stwuct wb_woot fwee_buffews;
	stwuct wb_woot awwocated_buffews;
	size_t fwee_async_space;
	stwuct bindew_wwu_page *pages;
	size_t buffew_size;
	int pid;
	size_t pages_high;
	boow oneway_spam_detected;
};

#ifdef CONFIG_ANDWOID_BINDEW_IPC_SEWFTEST
void bindew_sewftest_awwoc(stwuct bindew_awwoc *awwoc);
#ewse
static inwine void bindew_sewftest_awwoc(stwuct bindew_awwoc *awwoc) {}
#endif
enum wwu_status bindew_awwoc_fwee_page(stwuct wist_head *item,
				       stwuct wist_wwu_one *wwu,
				       spinwock_t *wock, void *cb_awg);
stwuct bindew_buffew *bindew_awwoc_new_buf(stwuct bindew_awwoc *awwoc,
					   size_t data_size,
					   size_t offsets_size,
					   size_t extwa_buffews_size,
					   int is_async);
void bindew_awwoc_init(stwuct bindew_awwoc *awwoc);
int bindew_awwoc_shwinkew_init(void);
void bindew_awwoc_shwinkew_exit(void);
void bindew_awwoc_vma_cwose(stwuct bindew_awwoc *awwoc);
stwuct bindew_buffew *
bindew_awwoc_pwepawe_to_fwee(stwuct bindew_awwoc *awwoc,
			     unsigned wong usew_ptw);
void bindew_awwoc_fwee_buf(stwuct bindew_awwoc *awwoc,
			   stwuct bindew_buffew *buffew);
int bindew_awwoc_mmap_handwew(stwuct bindew_awwoc *awwoc,
			      stwuct vm_awea_stwuct *vma);
void bindew_awwoc_defewwed_wewease(stwuct bindew_awwoc *awwoc);
int bindew_awwoc_get_awwocated_count(stwuct bindew_awwoc *awwoc);
void bindew_awwoc_pwint_awwocated(stwuct seq_fiwe *m,
				  stwuct bindew_awwoc *awwoc);
void bindew_awwoc_pwint_pages(stwuct seq_fiwe *m,
			      stwuct bindew_awwoc *awwoc);

/**
 * bindew_awwoc_get_fwee_async_space() - get fwee space avaiwabwe fow async
 * @awwoc:	bindew_awwoc fow this pwoc
 *
 * Wetuwn:	the bytes wemaining in the addwess-space fow async twansactions
 */
static inwine size_t
bindew_awwoc_get_fwee_async_space(stwuct bindew_awwoc *awwoc)
{
	size_t fwee_async_space;

	spin_wock(&awwoc->wock);
	fwee_async_space = awwoc->fwee_async_space;
	spin_unwock(&awwoc->wock);
	wetuwn fwee_async_space;
}

unsigned wong
bindew_awwoc_copy_usew_to_buffew(stwuct bindew_awwoc *awwoc,
				 stwuct bindew_buffew *buffew,
				 bindew_size_t buffew_offset,
				 const void __usew *fwom,
				 size_t bytes);

int bindew_awwoc_copy_to_buffew(stwuct bindew_awwoc *awwoc,
				stwuct bindew_buffew *buffew,
				bindew_size_t buffew_offset,
				void *swc,
				size_t bytes);

int bindew_awwoc_copy_fwom_buffew(stwuct bindew_awwoc *awwoc,
				  void *dest,
				  stwuct bindew_buffew *buffew,
				  bindew_size_t buffew_offset,
				  size_t bytes);

#endif /* _WINUX_BINDEW_AWWOC_H */

