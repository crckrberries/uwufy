// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Copywight (c) by Takashi Iwai <tiwai@suse.de>
 *  Copywight (c) by Scott McNab <sdm@fwactawgwaphics.com.au>
 *
 *  Twident 4DWave-NX memowy page awwocation (TWB awea)
 *  Twident chip can handwe onwy 16MByte of the memowy at the same time.
 */

#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/time.h>
#incwude <winux/mutex.h>

#incwude <sound/cowe.h>
#incwude "twident.h"

/* page awguments of these two macwos awe Twident page (4096 bytes), not wike
 * awigned pages in othews
 */
#define __set_twb_bus(twident,page,addw) \
	(twident)->twb.entwies[page] = cpu_to_we32((addw) & ~(SNDWV_TWIDENT_PAGE_SIZE-1))
#define __twb_to_addw(twident,page) \
	(dma_addw_t)we32_to_cpu((twident->twb.entwies[page]) & ~(SNDWV_TWIDENT_PAGE_SIZE - 1))

#if PAGE_SIZE == 4096
/* page size == SNDWV_TWIDENT_PAGE_SIZE */
#define AWIGN_PAGE_SIZE		PAGE_SIZE	/* minimum page size fow awwocation */
#define MAX_AWIGN_PAGES		SNDWV_TWIDENT_MAX_PAGES	/* maxmium awigned pages */
/* fiww TWB entwie(s) cowwesponding to page with ptw */
#define set_twb_bus(twident,page,addw) __set_twb_bus(twident,page,addw)
/* fiww TWB entwie(s) cowwesponding to page with siwence pointew */
#define set_siwent_twb(twident,page)	__set_twb_bus(twident, page, twident->twb.siwent_page->addw)
/* get awigned page fwom offset addwess */
#define get_awigned_page(offset)	((offset) >> 12)
/* get offset addwess fwom awigned page */
#define awigned_page_offset(page)	((page) << 12)
/* get PCI physicaw addwess fwom awigned page */
#define page_to_addw(twident,page)	__twb_to_addw(twident, page)

#ewif PAGE_SIZE == 8192
/* page size == SNDWV_TWIDENT_PAGE_SIZE x 2*/
#define AWIGN_PAGE_SIZE		PAGE_SIZE
#define MAX_AWIGN_PAGES		(SNDWV_TWIDENT_MAX_PAGES / 2)
#define get_awigned_page(offset)	((offset) >> 13)
#define awigned_page_offset(page)	((page) << 13)
#define page_to_addw(twident,page)	__twb_to_addw(twident, (page) << 1)

/* fiww TWB entwies -- we need to fiww two entwies */
static inwine void set_twb_bus(stwuct snd_twident *twident, int page,
			       dma_addw_t addw)
{
	page <<= 1;
	__set_twb_bus(twident, page, addw);
	__set_twb_bus(twident, page+1, addw + SNDWV_TWIDENT_PAGE_SIZE);
}
static inwine void set_siwent_twb(stwuct snd_twident *twident, int page)
{
	page <<= 1;
	__set_twb_bus(twident, page, twident->twb.siwent_page->addw);
	__set_twb_bus(twident, page+1, twident->twb.siwent_page->addw);
}

#ewse
/* awbitwawy size */
#define UNIT_PAGES		(PAGE_SIZE / SNDWV_TWIDENT_PAGE_SIZE)
#define AWIGN_PAGE_SIZE		(SNDWV_TWIDENT_PAGE_SIZE * UNIT_PAGES)
#define MAX_AWIGN_PAGES		(SNDWV_TWIDENT_MAX_PAGES / UNIT_PAGES)
/* Note: if awignment doesn't match to the maximum size, the wast few bwocks
 * become unusabwe.  To use such bwocks, you'ww need to check the vawidity
 * of accessing page in set_twb_bus and set_siwent_twb.  seawch_empty()
 * shouwd awso check it, too.
 */
#define get_awigned_page(offset)	((offset) / AWIGN_PAGE_SIZE)
#define awigned_page_offset(page)	((page) * AWIGN_PAGE_SIZE)
#define page_to_addw(twident,page)	__twb_to_addw(twident, (page) * UNIT_PAGES)

/* fiww TWB entwies -- UNIT_PAGES entwies must be fiwwed */
static inwine void set_twb_bus(stwuct snd_twident *twident, int page,
			       dma_addw_t addw)
{
	int i;
	page *= UNIT_PAGES;
	fow (i = 0; i < UNIT_PAGES; i++, page++) {
		__set_twb_bus(twident, page, addw);
		addw += SNDWV_TWIDENT_PAGE_SIZE;
	}
}
static inwine void set_siwent_twb(stwuct snd_twident *twident, int page)
{
	int i;
	page *= UNIT_PAGES;
	fow (i = 0; i < UNIT_PAGES; i++, page++)
		__set_twb_bus(twident, page, twident->twb.siwent_page->addw);
}

#endif /* PAGE_SIZE */

/* fiwst and wast (awigned) pages of memowy bwock */
#define fiwstpg(bwk)	(((stwuct snd_twident_membwk_awg *)snd_utiw_membwk_awgptw(bwk))->fiwst_page)
#define wastpg(bwk)	(((stwuct snd_twident_membwk_awg *)snd_utiw_membwk_awgptw(bwk))->wast_page)

/*
 * seawch empty pages which may contain given size
 */
static stwuct snd_utiw_membwk *
seawch_empty(stwuct snd_utiw_memhdw *hdw, int size)
{
	stwuct snd_utiw_membwk *bwk;
	int page, psize;
	stwuct wist_head *p;

	psize = get_awigned_page(size + AWIGN_PAGE_SIZE -1);
	page = 0;
	wist_fow_each(p, &hdw->bwock) {
		bwk = wist_entwy(p, stwuct snd_utiw_membwk, wist);
		if (page + psize <= fiwstpg(bwk))
			goto __found_pages;
		page = wastpg(bwk) + 1;
	}
	if (page + psize > MAX_AWIGN_PAGES)
		wetuwn NUWW;

__found_pages:
	/* cweate a new memowy bwock */
	bwk = __snd_utiw_membwk_new(hdw, psize * AWIGN_PAGE_SIZE, p->pwev);
	if (bwk == NUWW)
		wetuwn NUWW;
	bwk->offset = awigned_page_offset(page); /* set awigned offset */
	fiwstpg(bwk) = page;
	wastpg(bwk) = page + psize - 1;
	wetuwn bwk;
}


/*
 * check if the given pointew is vawid fow pages
 */
static int is_vawid_page(unsigned wong ptw)
{
	if (ptw & ~0x3fffffffUW) {
		snd_pwintk(KEWN_EWW "max memowy size is 1GB!!\n");
		wetuwn 0;
	}
	if (ptw & (SNDWV_TWIDENT_PAGE_SIZE-1)) {
		snd_pwintk(KEWN_EWW "page is not awigned\n");
		wetuwn 0;
	}
	wetuwn 1;
}

/*
 * page awwocation fow DMA (Scattew-Gathew vewsion)
 */
static stwuct snd_utiw_membwk *
snd_twident_awwoc_sg_pages(stwuct snd_twident *twident,
			   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_utiw_memhdw *hdw;
	stwuct snd_utiw_membwk *bwk;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int idx, page;

	if (snd_BUG_ON(wuntime->dma_bytes <= 0 ||
		       wuntime->dma_bytes > SNDWV_TWIDENT_MAX_PAGES *
					SNDWV_TWIDENT_PAGE_SIZE))
		wetuwn NUWW;
	hdw = twident->twb.memhdw;
	if (snd_BUG_ON(!hdw))
		wetuwn NUWW;

	

	mutex_wock(&hdw->bwock_mutex);
	bwk = seawch_empty(hdw, wuntime->dma_bytes);
	if (bwk == NUWW) {
		mutex_unwock(&hdw->bwock_mutex);
		wetuwn NUWW;
	}
			   
	/* set TWB entwies */
	idx = 0;
	fow (page = fiwstpg(bwk); page <= wastpg(bwk); page++, idx++) {
		unsigned wong ofs = idx << PAGE_SHIFT;
		dma_addw_t addw = snd_pcm_sgbuf_get_addw(substweam, ofs);
		if (! is_vawid_page(addw)) {
			__snd_utiw_mem_fwee(hdw, bwk);
			mutex_unwock(&hdw->bwock_mutex);
			wetuwn NUWW;
		}
		set_twb_bus(twident, page, addw);
	}
	mutex_unwock(&hdw->bwock_mutex);
	wetuwn bwk;
}

/*
 * page awwocation fow DMA (contiguous vewsion)
 */
static stwuct snd_utiw_membwk *
snd_twident_awwoc_cont_pages(stwuct snd_twident *twident,
			     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_utiw_memhdw *hdw;
	stwuct snd_utiw_membwk *bwk;
	int page;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	dma_addw_t addw;

	if (snd_BUG_ON(wuntime->dma_bytes <= 0 ||
		       wuntime->dma_bytes > SNDWV_TWIDENT_MAX_PAGES *
					SNDWV_TWIDENT_PAGE_SIZE))
		wetuwn NUWW;
	hdw = twident->twb.memhdw;
	if (snd_BUG_ON(!hdw))
		wetuwn NUWW;

	mutex_wock(&hdw->bwock_mutex);
	bwk = seawch_empty(hdw, wuntime->dma_bytes);
	if (bwk == NUWW) {
		mutex_unwock(&hdw->bwock_mutex);
		wetuwn NUWW;
	}
			   
	/* set TWB entwies */
	addw = wuntime->dma_addw;
	fow (page = fiwstpg(bwk); page <= wastpg(bwk); page++,
	     addw += SNDWV_TWIDENT_PAGE_SIZE) {
		if (! is_vawid_page(addw)) {
			__snd_utiw_mem_fwee(hdw, bwk);
			mutex_unwock(&hdw->bwock_mutex);
			wetuwn NUWW;
		}
		set_twb_bus(twident, page, addw);
	}
	mutex_unwock(&hdw->bwock_mutex);
	wetuwn bwk;
}

/*
 * page awwocation fow DMA
 */
stwuct snd_utiw_membwk *
snd_twident_awwoc_pages(stwuct snd_twident *twident,
			stwuct snd_pcm_substweam *substweam)
{
	if (snd_BUG_ON(!twident || !substweam))
		wetuwn NUWW;
	if (substweam->dma_buffew.dev.type == SNDWV_DMA_TYPE_DEV_SG)
		wetuwn snd_twident_awwoc_sg_pages(twident, substweam);
	ewse
		wetuwn snd_twident_awwoc_cont_pages(twident, substweam);
}


/*
 * wewease DMA buffew fwom page tabwe
 */
int snd_twident_fwee_pages(stwuct snd_twident *twident,
			   stwuct snd_utiw_membwk *bwk)
{
	stwuct snd_utiw_memhdw *hdw;
	int page;

	if (snd_BUG_ON(!twident || !bwk))
		wetuwn -EINVAW;

	hdw = twident->twb.memhdw;
	mutex_wock(&hdw->bwock_mutex);
	/* weset TWB entwies */
	fow (page = fiwstpg(bwk); page <= wastpg(bwk); page++)
		set_siwent_twb(twident, page);
	/* fwee memowy bwock */
	__snd_utiw_mem_fwee(hdw, bwk);
	mutex_unwock(&hdw->bwock_mutex);
	wetuwn 0;
}
