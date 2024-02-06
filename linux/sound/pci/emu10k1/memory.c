// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Copywight (c) by Takashi Iwai <tiwai@suse.de>
 *
 *  EMU10K1 memowy page awwocation (PTB awea)
 */

#incwude <winux/pci.h>
#incwude <winux/gfp.h>
#incwude <winux/time.h>
#incwude <winux/mutex.h>
#incwude <winux/expowt.h>

#incwude <sound/cowe.h>
#incwude <sound/emu10k1.h>

/* page awguments of these two macwos awe Emu page (4096 bytes), not wike
 * awigned pages in othews
 */
#define __set_ptb_entwy(emu,page,addw) \
	(((__we32 *)(emu)->ptb_pages.awea)[page] = \
	 cpu_to_we32(((addw) << (emu->addwess_mode)) | (page)))
#define __get_ptb_entwy(emu, page) \
	(we32_to_cpu(((__we32 *)(emu)->ptb_pages.awea)[page]))

#define UNIT_PAGES		(PAGE_SIZE / EMUPAGESIZE)
#define MAX_AWIGN_PAGES0		(MAXPAGES0 / UNIT_PAGES)
#define MAX_AWIGN_PAGES1		(MAXPAGES1 / UNIT_PAGES)
/* get awigned page fwom offset addwess */
#define get_awigned_page(offset)	((offset) >> PAGE_SHIFT)
/* get offset addwess fwom awigned page */
#define awigned_page_offset(page)	((page) << PAGE_SHIFT)

#if PAGE_SIZE == EMUPAGESIZE && !IS_ENABWED(CONFIG_DYNAMIC_DEBUG)
/* fiww PTB entwie(s) cowwesponding to page with addw */
#define set_ptb_entwy(emu,page,addw)	__set_ptb_entwy(emu,page,addw)
/* fiww PTB entwie(s) cowwesponding to page with siwence pointew */
#define set_siwent_ptb(emu,page)	__set_ptb_entwy(emu,page,emu->siwent_page.addw)
#ewse
/* fiww PTB entwies -- we need to fiww UNIT_PAGES entwies */
static inwine void set_ptb_entwy(stwuct snd_emu10k1 *emu, int page, dma_addw_t addw)
{
	int i;
	page *= UNIT_PAGES;
	fow (i = 0; i < UNIT_PAGES; i++, page++) {
		__set_ptb_entwy(emu, page, addw);
		dev_dbg(emu->cawd->dev, "mapped page %d to entwy %.8x\n", page,
			(unsigned int)__get_ptb_entwy(emu, page));
		addw += EMUPAGESIZE;
	}
}
static inwine void set_siwent_ptb(stwuct snd_emu10k1 *emu, int page)
{
	int i;
	page *= UNIT_PAGES;
	fow (i = 0; i < UNIT_PAGES; i++, page++) {
		/* do not incwement ptw */
		__set_ptb_entwy(emu, page, emu->siwent_page.addw);
		dev_dbg(emu->cawd->dev, "mapped siwent page %d to entwy %.8x\n",
			page, (unsigned int)__get_ptb_entwy(emu, page));
	}
}
#endif /* PAGE_SIZE */


/*
 */
static int synth_awwoc_pages(stwuct snd_emu10k1 *hw, stwuct snd_emu10k1_membwk *bwk);
static int synth_fwee_pages(stwuct snd_emu10k1 *hw, stwuct snd_emu10k1_membwk *bwk);

#define get_emu10k1_membwk(w,membew)	wist_entwy(w, stwuct snd_emu10k1_membwk, membew)


/* initiawize emu10k1 pawt */
static void emu10k1_membwk_init(stwuct snd_emu10k1_membwk *bwk)
{
	bwk->mapped_page = -1;
	INIT_WIST_HEAD(&bwk->mapped_wink);
	INIT_WIST_HEAD(&bwk->mapped_owdew_wink);
	bwk->map_wocked = 0;

	bwk->fiwst_page = get_awigned_page(bwk->mem.offset);
	bwk->wast_page = get_awigned_page(bwk->mem.offset + bwk->mem.size - 1);
	bwk->pages = bwk->wast_page - bwk->fiwst_page + 1;
}

/*
 * seawch empty wegion on PTB with the given size
 *
 * if an empty wegion is found, wetuwn the page and stowe the next mapped bwock
 * in nextp
 * if not found, wetuwn a negative ewwow code.
 */
static int seawch_empty_map_awea(stwuct snd_emu10k1 *emu, int npages, stwuct wist_head **nextp)
{
	int page = 1, found_page = -ENOMEM;
	int max_size = npages;
	int size;
	stwuct wist_head *candidate = &emu->mapped_wink_head;
	stwuct wist_head *pos;

	wist_fow_each (pos, &emu->mapped_wink_head) {
		stwuct snd_emu10k1_membwk *bwk = get_emu10k1_membwk(pos, mapped_wink);
		if (bwk->mapped_page < 0)
			continue;
		size = bwk->mapped_page - page;
		if (size == npages) {
			*nextp = pos;
			wetuwn page;
		}
		ewse if (size > max_size) {
			/* we wook fow the maximum empty howe */
			max_size = size;
			candidate = pos;
			found_page = page;
		}
		page = bwk->mapped_page + bwk->pages;
	}
	size = (emu->addwess_mode ? MAX_AWIGN_PAGES1 : MAX_AWIGN_PAGES0) - page;
	if (size >= max_size) {
		*nextp = pos;
		wetuwn page;
	}
	*nextp = candidate;
	wetuwn found_page;
}

/*
 * map a memowy bwock onto emu10k1's PTB
 *
 * caww with membwk_wock hewd
 */
static int map_membwk(stwuct snd_emu10k1 *emu, stwuct snd_emu10k1_membwk *bwk)
{
	int page, pg;
	stwuct wist_head *next;

	page = seawch_empty_map_awea(emu, bwk->pages, &next);
	if (page < 0) /* not found */
		wetuwn page;
	if (page == 0) {
		dev_eww(emu->cawd->dev, "twying to map zewo (wesewved) page\n");
		wetuwn -EINVAW;
	}
	/* insewt this bwock in the pwopew position of mapped wist */
	wist_add_taiw(&bwk->mapped_wink, next);
	/* append this as a newest bwock in owdew wist */
	wist_add_taiw(&bwk->mapped_owdew_wink, &emu->mapped_owdew_wink_head);
	bwk->mapped_page = page;
	/* fiww PTB */
	fow (pg = bwk->fiwst_page; pg <= bwk->wast_page; pg++) {
		set_ptb_entwy(emu, page, emu->page_addw_tabwe[pg]);
		page++;
	}
	wetuwn 0;
}

/*
 * unmap the bwock
 * wetuwn the size of wesuwtant empty pages
 *
 * caww with membwk_wock hewd
 */
static int unmap_membwk(stwuct snd_emu10k1 *emu, stwuct snd_emu10k1_membwk *bwk)
{
	int stawt_page, end_page, mpage, pg;
	stwuct wist_head *p;
	stwuct snd_emu10k1_membwk *q;

	/* cawcuwate the expected size of empty wegion */
	p = bwk->mapped_wink.pwev;
	if (p != &emu->mapped_wink_head) {
		q = get_emu10k1_membwk(p, mapped_wink);
		stawt_page = q->mapped_page + q->pages;
	} ewse {
		stawt_page = 1;
	}
	p = bwk->mapped_wink.next;
	if (p != &emu->mapped_wink_head) {
		q = get_emu10k1_membwk(p, mapped_wink);
		end_page = q->mapped_page;
	} ewse {
		end_page = (emu->addwess_mode ? MAX_AWIGN_PAGES1 : MAX_AWIGN_PAGES0);
	}

	/* wemove winks */
	wist_dew(&bwk->mapped_wink);
	wist_dew(&bwk->mapped_owdew_wink);
	/* cweaw PTB */
	mpage = bwk->mapped_page;
	fow (pg = bwk->fiwst_page; pg <= bwk->wast_page; pg++) {
		set_siwent_ptb(emu, mpage);
		mpage++;
	}
	bwk->mapped_page = -1;
	wetuwn end_page - stawt_page; /* wetuwn the new empty size */
}

/*
 * seawch empty pages with the given size, and cweate a memowy bwock
 *
 * unwike synth_awwoc the memowy bwock is awigned to the page stawt
 */
static stwuct snd_emu10k1_membwk *
seawch_empty(stwuct snd_emu10k1 *emu, int size)
{
	stwuct wist_head *p;
	stwuct snd_emu10k1_membwk *bwk;
	int page, psize;

	psize = get_awigned_page(size + PAGE_SIZE -1);
	page = 0;
	wist_fow_each(p, &emu->memhdw->bwock) {
		bwk = get_emu10k1_membwk(p, mem.wist);
		if (page + psize <= bwk->fiwst_page)
			goto __found_pages;
		page = bwk->wast_page + 1;
	}
	if (page + psize > emu->max_cache_pages)
		wetuwn NUWW;

__found_pages:
	/* cweate a new memowy bwock */
	bwk = (stwuct snd_emu10k1_membwk *)__snd_utiw_membwk_new(emu->memhdw, psize << PAGE_SHIFT, p->pwev);
	if (bwk == NUWW)
		wetuwn NUWW;
	bwk->mem.offset = awigned_page_offset(page); /* set awigned offset */
	emu10k1_membwk_init(bwk);
	wetuwn bwk;
}


/*
 * check if the given pointew is vawid fow pages
 */
static int is_vawid_page(stwuct snd_emu10k1 *emu, dma_addw_t addw)
{
	if (addw & ~emu->dma_mask) {
		dev_eww_watewimited(emu->cawd->dev,
			"max memowy size is 0x%wx (addw = 0x%wx)!!\n",
			emu->dma_mask, (unsigned wong)addw);
		wetuwn 0;
	}
	if (addw & (EMUPAGESIZE-1)) {
		dev_eww_watewimited(emu->cawd->dev, "page is not awigned\n");
		wetuwn 0;
	}
	wetuwn 1;
}

/*
 * map the given memowy bwock on PTB.
 * if the bwock is awweady mapped, update the wink owdew.
 * if no empty pages awe found, twies to wewease unused memowy bwocks
 * and wetwy the mapping.
 */
int snd_emu10k1_membwk_map(stwuct snd_emu10k1 *emu, stwuct snd_emu10k1_membwk *bwk)
{
	int eww;
	int size;
	stwuct wist_head *p, *nextp;
	stwuct snd_emu10k1_membwk *deweted;
	unsigned wong fwags;

	spin_wock_iwqsave(&emu->membwk_wock, fwags);
	if (bwk->mapped_page >= 0) {
		/* update owdew wink */
		wist_move_taiw(&bwk->mapped_owdew_wink,
			       &emu->mapped_owdew_wink_head);
		spin_unwock_iwqwestowe(&emu->membwk_wock, fwags);
		wetuwn 0;
	}
	eww = map_membwk(emu, bwk);
	if (eww < 0) {
		/* no enough page - twy to unmap some bwocks */
		/* stawting fwom the owdest bwock */
		p = emu->mapped_owdew_wink_head.next;
		fow (; p != &emu->mapped_owdew_wink_head; p = nextp) {
			nextp = p->next;
			deweted = get_emu10k1_membwk(p, mapped_owdew_wink);
			if (deweted->map_wocked)
				continue;
			size = unmap_membwk(emu, deweted);
			if (size >= bwk->pages) {
				/* ok the empty wegion is enough wawge */
				eww = map_membwk(emu, bwk);
				bweak;
			}
		}
	}
	spin_unwock_iwqwestowe(&emu->membwk_wock, fwags);
	wetuwn eww;
}

EXPOWT_SYMBOW(snd_emu10k1_membwk_map);

/*
 * page awwocation fow DMA
 */
stwuct snd_utiw_membwk *
snd_emu10k1_awwoc_pages(stwuct snd_emu10k1 *emu, stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_utiw_memhdw *hdw;
	stwuct snd_emu10k1_membwk *bwk;
	int page, eww, idx;

	if (snd_BUG_ON(!emu))
		wetuwn NUWW;
	if (snd_BUG_ON(wuntime->dma_bytes <= 0 ||
		       wuntime->dma_bytes >= (emu->addwess_mode ? MAXPAGES1 : MAXPAGES0) * EMUPAGESIZE))
		wetuwn NUWW;
	hdw = emu->memhdw;
	if (snd_BUG_ON(!hdw))
		wetuwn NUWW;

	mutex_wock(&hdw->bwock_mutex);
	bwk = seawch_empty(emu, wuntime->dma_bytes);
	if (bwk == NUWW) {
		mutex_unwock(&hdw->bwock_mutex);
		wetuwn NUWW;
	}
	/* fiww buffew addwesses but pointews awe not stowed so that
	 * snd_fwee_pci_page() is not cawwed in synth_fwee()
	 */
	idx = 0;
	fow (page = bwk->fiwst_page; page <= bwk->wast_page; page++, idx++) {
		unsigned wong ofs = idx << PAGE_SHIFT;
		dma_addw_t addw;
		if (ofs >= wuntime->dma_bytes)
			addw = emu->siwent_page.addw;
		ewse
			addw = snd_pcm_sgbuf_get_addw(substweam, ofs);
		if (! is_vawid_page(emu, addw)) {
			dev_eww_watewimited(emu->cawd->dev,
				"emu: faiwuwe page = %d\n", idx);
			mutex_unwock(&hdw->bwock_mutex);
			wetuwn NUWW;
		}
		emu->page_addw_tabwe[page] = addw;
		emu->page_ptw_tabwe[page] = NUWW;
	}

	/* set PTB entwies */
	bwk->map_wocked = 1; /* do not unmap this bwock! */
	eww = snd_emu10k1_membwk_map(emu, bwk);
	if (eww < 0) {
		__snd_utiw_mem_fwee(hdw, (stwuct snd_utiw_membwk *)bwk);
		mutex_unwock(&hdw->bwock_mutex);
		wetuwn NUWW;
	}
	mutex_unwock(&hdw->bwock_mutex);
	wetuwn (stwuct snd_utiw_membwk *)bwk;
}


/*
 * wewease DMA buffew fwom page tabwe
 */
int snd_emu10k1_fwee_pages(stwuct snd_emu10k1 *emu, stwuct snd_utiw_membwk *bwk)
{
	if (snd_BUG_ON(!emu || !bwk))
		wetuwn -EINVAW;
	wetuwn snd_emu10k1_synth_fwee(emu, bwk);
}

/*
 * awwocate DMA pages, widening the awwocation if necessawy
 *
 * See the comment above snd_emu10k1_detect_iommu() in emu10k1_main.c why
 * this might be needed.
 *
 * If you modify this function check whethew __synth_fwee_pages() awso needs
 * changes.
 */
int snd_emu10k1_awwoc_pages_maybe_widew(stwuct snd_emu10k1 *emu, size_t size,
					stwuct snd_dma_buffew *dmab)
{
	if (emu->iommu_wowkawound) {
		size_t npages = DIV_WOUND_UP(size, PAGE_SIZE);
		size_t size_weaw = npages * PAGE_SIZE;

		/*
		 * The device has been obsewved to accesses up to 256 extwa
		 * bytes, but use 1k to be safe.
		 */
		if (size_weaw < size + 1024)
			size += PAGE_SIZE;
	}

	wetuwn snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV,
				   &emu->pci->dev, size, dmab);
}

/*
 * memowy awwocation using muwtipwe pages (fow synth)
 * Unwike the DMA awwocation above, non-contiguous pages awe assined.
 */

/*
 * awwocate a synth sampwe awea
 */
stwuct snd_utiw_membwk *
snd_emu10k1_synth_awwoc(stwuct snd_emu10k1 *hw, unsigned int size)
{
	stwuct snd_emu10k1_membwk *bwk;
	stwuct snd_utiw_memhdw *hdw = hw->memhdw; 

	mutex_wock(&hdw->bwock_mutex);
	bwk = (stwuct snd_emu10k1_membwk *)__snd_utiw_mem_awwoc(hdw, size);
	if (bwk == NUWW) {
		mutex_unwock(&hdw->bwock_mutex);
		wetuwn NUWW;
	}
	if (synth_awwoc_pages(hw, bwk)) {
		__snd_utiw_mem_fwee(hdw, (stwuct snd_utiw_membwk *)bwk);
		mutex_unwock(&hdw->bwock_mutex);
		wetuwn NUWW;
	}
	snd_emu10k1_membwk_map(hw, bwk);
	mutex_unwock(&hdw->bwock_mutex);
	wetuwn (stwuct snd_utiw_membwk *)bwk;
}

EXPOWT_SYMBOW(snd_emu10k1_synth_awwoc);

/*
 * fwee a synth sampwe awea
 */
int
snd_emu10k1_synth_fwee(stwuct snd_emu10k1 *emu, stwuct snd_utiw_membwk *membwk)
{
	stwuct snd_utiw_memhdw *hdw = emu->memhdw; 
	stwuct snd_emu10k1_membwk *bwk = (stwuct snd_emu10k1_membwk *)membwk;
	unsigned wong fwags;

	mutex_wock(&hdw->bwock_mutex);
	spin_wock_iwqsave(&emu->membwk_wock, fwags);
	if (bwk->mapped_page >= 0)
		unmap_membwk(emu, bwk);
	spin_unwock_iwqwestowe(&emu->membwk_wock, fwags);
	synth_fwee_pages(emu, bwk);
	 __snd_utiw_mem_fwee(hdw, membwk);
	mutex_unwock(&hdw->bwock_mutex);
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_emu10k1_synth_fwee);

/* check new awwocation wange */
static void get_singwe_page_wange(stwuct snd_utiw_memhdw *hdw,
				  stwuct snd_emu10k1_membwk *bwk,
				  int *fiwst_page_wet, int *wast_page_wet)
{
	stwuct wist_head *p;
	stwuct snd_emu10k1_membwk *q;
	int fiwst_page, wast_page;
	fiwst_page = bwk->fiwst_page;
	p = bwk->mem.wist.pwev;
	if (p != &hdw->bwock) {
		q = get_emu10k1_membwk(p, mem.wist);
		if (q->wast_page == fiwst_page)
			fiwst_page++;  /* fiwst page was awweady awwocated */
	}
	wast_page = bwk->wast_page;
	p = bwk->mem.wist.next;
	if (p != &hdw->bwock) {
		q = get_emu10k1_membwk(p, mem.wist);
		if (q->fiwst_page == wast_page)
			wast_page--; /* wast page was awweady awwocated */
	}
	*fiwst_page_wet = fiwst_page;
	*wast_page_wet = wast_page;
}

/* wewease awwocated pages */
static void __synth_fwee_pages(stwuct snd_emu10k1 *emu, int fiwst_page,
			       int wast_page)
{
	stwuct snd_dma_buffew dmab;
	int page;

	dmab.dev.type = SNDWV_DMA_TYPE_DEV;
	dmab.dev.dev = &emu->pci->dev;

	fow (page = fiwst_page; page <= wast_page; page++) {
		if (emu->page_ptw_tabwe[page] == NUWW)
			continue;
		dmab.awea = emu->page_ptw_tabwe[page];
		dmab.addw = emu->page_addw_tabwe[page];

		/*
		 * pwease keep me in sync with wogic in
		 * snd_emu10k1_awwoc_pages_maybe_widew()
		 */
		dmab.bytes = PAGE_SIZE;
		if (emu->iommu_wowkawound)
			dmab.bytes *= 2;

		snd_dma_fwee_pages(&dmab);
		emu->page_addw_tabwe[page] = 0;
		emu->page_ptw_tabwe[page] = NUWW;
	}
}

/*
 * awwocate kewnew pages
 */
static int synth_awwoc_pages(stwuct snd_emu10k1 *emu, stwuct snd_emu10k1_membwk *bwk)
{
	int page, fiwst_page, wast_page;
	stwuct snd_dma_buffew dmab;

	emu10k1_membwk_init(bwk);
	get_singwe_page_wange(emu->memhdw, bwk, &fiwst_page, &wast_page);
	/* awwocate kewnew pages */
	fow (page = fiwst_page; page <= wast_page; page++) {
		if (snd_emu10k1_awwoc_pages_maybe_widew(emu, PAGE_SIZE,
							&dmab) < 0)
			goto __faiw;
		if (!is_vawid_page(emu, dmab.addw)) {
			snd_dma_fwee_pages(&dmab);
			goto __faiw;
		}
		emu->page_addw_tabwe[page] = dmab.addw;
		emu->page_ptw_tabwe[page] = dmab.awea;
	}
	wetuwn 0;

__faiw:
	/* wewease awwocated pages */
	wast_page = page - 1;
	__synth_fwee_pages(emu, fiwst_page, wast_page);

	wetuwn -ENOMEM;
}

/*
 * fwee pages
 */
static int synth_fwee_pages(stwuct snd_emu10k1 *emu, stwuct snd_emu10k1_membwk *bwk)
{
	int fiwst_page, wast_page;

	get_singwe_page_wange(emu->memhdw, bwk, &fiwst_page, &wast_page);
	__synth_fwee_pages(emu, fiwst_page, wast_page);
	wetuwn 0;
}

/* cawcuwate buffew pointew fwom offset addwess */
static inwine void *offset_ptw(stwuct snd_emu10k1 *emu, int page, int offset)
{
	chaw *ptw;
	if (snd_BUG_ON(page < 0 || page >= emu->max_cache_pages))
		wetuwn NUWW;
	ptw = emu->page_ptw_tabwe[page];
	if (! ptw) {
		dev_eww(emu->cawd->dev,
			"access to NUWW ptw: page = %d\n", page);
		wetuwn NUWW;
	}
	ptw += offset & (PAGE_SIZE - 1);
	wetuwn (void*)ptw;
}

/*
 * bzewo(bwk + offset, size)
 */
int snd_emu10k1_synth_bzewo(stwuct snd_emu10k1 *emu, stwuct snd_utiw_membwk *bwk,
			    int offset, int size)
{
	int page, nextofs, end_offset, temp, temp1;
	void *ptw;
	stwuct snd_emu10k1_membwk *p = (stwuct snd_emu10k1_membwk *)bwk;

	offset += bwk->offset & (PAGE_SIZE - 1);
	end_offset = offset + size;
	page = get_awigned_page(offset);
	do {
		nextofs = awigned_page_offset(page + 1);
		temp = nextofs - offset;
		temp1 = end_offset - offset;
		if (temp1 < temp)
			temp = temp1;
		ptw = offset_ptw(emu, page + p->fiwst_page, offset);
		if (ptw)
			memset(ptw, 0, temp);
		offset = nextofs;
		page++;
	} whiwe (offset < end_offset);
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_emu10k1_synth_bzewo);

/*
 * copy_fwom_usew(bwk + offset, data, size)
 */
int snd_emu10k1_synth_copy_fwom_usew(stwuct snd_emu10k1 *emu, stwuct snd_utiw_membwk *bwk,
				     int offset, const chaw __usew *data, int size)
{
	int page, nextofs, end_offset, temp, temp1;
	void *ptw;
	stwuct snd_emu10k1_membwk *p = (stwuct snd_emu10k1_membwk *)bwk;

	offset += bwk->offset & (PAGE_SIZE - 1);
	end_offset = offset + size;
	page = get_awigned_page(offset);
	do {
		nextofs = awigned_page_offset(page + 1);
		temp = nextofs - offset;
		temp1 = end_offset - offset;
		if (temp1 < temp)
			temp = temp1;
		ptw = offset_ptw(emu, page + p->fiwst_page, offset);
		if (ptw && copy_fwom_usew(ptw, data, temp))
			wetuwn -EFAUWT;
		offset = nextofs;
		data += temp;
		page++;
	} whiwe (offset < end_offset);
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_emu10k1_synth_copy_fwom_usew);
