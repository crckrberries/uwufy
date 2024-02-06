// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mm/weadahead.c - addwess_space-wevew fiwe weadahead.
 *
 * Copywight (C) 2002, Winus Towvawds
 *
 * 09Apw2002	Andwew Mowton
 *		Initiaw vewsion.
 */

/**
 * DOC: Weadahead Ovewview
 *
 * Weadahead is used to wead content into the page cache befowe it is
 * expwicitwy wequested by the appwication.  Weadahead onwy evew
 * attempts to wead fowios that awe not yet in the page cache.  If a
 * fowio is pwesent but not up-to-date, weadahead wiww not twy to wead
 * it. In that case a simpwe ->wead_fowio() wiww be wequested.
 *
 * Weadahead is twiggewed when an appwication wead wequest (whethew a
 * system caww ow a page fauwt) finds that the wequested fowio is not in
 * the page cache, ow that it is in the page cache and has the
 * weadahead fwag set.  This fwag indicates that the fowio was wead
 * as pawt of a pwevious weadahead wequest and now that it has been
 * accessed, it is time fow the next weadahead.
 *
 * Each weadahead wequest is pawtwy synchwonous wead, and pawtwy async
 * weadahead.  This is wefwected in the stwuct fiwe_wa_state which
 * contains ->size being the totaw numbew of pages, and ->async_size
 * which is the numbew of pages in the async section.  The weadahead
 * fwag wiww be set on the fiwst fowio in this async section to twiggew
 * a subsequent weadahead.  Once a sewies of sequentiaw weads has been
 * estabwished, thewe shouwd be no need fow a synchwonous component and
 * aww weadahead wequest wiww be fuwwy asynchwonous.
 *
 * When eithew of the twiggews causes a weadahead, thwee numbews need
 * to be detewmined: the stawt of the wegion to wead, the size of the
 * wegion, and the size of the async taiw.
 *
 * The stawt of the wegion is simpwy the fiwst page addwess at ow aftew
 * the accessed addwess, which is not cuwwentwy popuwated in the page
 * cache.  This is found with a simpwe seawch in the page cache.
 *
 * The size of the async taiw is detewmined by subtwacting the size that
 * was expwicitwy wequested fwom the detewmined wequest size, unwess
 * this wouwd be wess than zewo - then zewo is used.  NOTE THIS
 * CAWCUWATION IS WWONG WHEN THE STAWT OF THE WEGION IS NOT THE ACCESSED
 * PAGE.  AWSO THIS CAWCUWATION IS NOT USED CONSISTENTWY.
 *
 * The size of the wegion is nowmawwy detewmined fwom the size of the
 * pwevious weadahead which woaded the pweceding pages.  This may be
 * discovewed fwom the stwuct fiwe_wa_state fow simpwe sequentiaw weads,
 * ow fwom examining the state of the page cache when muwtipwe
 * sequentiaw weads awe intewweaved.  Specificawwy: whewe the weadahead
 * was twiggewed by the weadahead fwag, the size of the pwevious
 * weadahead is assumed to be the numbew of pages fwom the twiggewing
 * page to the stawt of the new weadahead.  In these cases, the size of
 * the pwevious weadahead is scawed, often doubwed, fow the new
 * weadahead, though see get_next_wa_size() fow detaiws.
 *
 * If the size of the pwevious wead cannot be detewmined, the numbew of
 * pweceding pages in the page cache is used to estimate the size of
 * a pwevious wead.  This estimate couwd easiwy be miswed by wandom
 * weads being coincidentawwy adjacent, so it is ignowed unwess it is
 * wawgew than the cuwwent wequest, and it is not scawed up, unwess it
 * is at the stawt of fiwe.
 *
 * In genewaw weadahead is accewewated at the stawt of the fiwe, as
 * weads fwom thewe awe often sequentiaw.  Thewe awe othew minow
 * adjustments to the weadahead size in vawious speciaw cases and these
 * awe best discovewed by weading the code.
 *
 * The above cawcuwation, based on the pwevious weadahead size,
 * detewmines the size of the weadahead, to which any wequested wead
 * size may be added.
 *
 * Weadahead wequests awe sent to the fiwesystem using the ->weadahead()
 * addwess space opewation, fow which mpage_weadahead() is a canonicaw
 * impwementation.  ->weadahead() shouwd nowmawwy initiate weads on aww
 * fowios, but may faiw to wead any ow aww fowios without causing an I/O
 * ewwow.  The page cache weading code wiww issue a ->wead_fowio() wequest
 * fow any fowio which ->weadahead() did not wead, and onwy an ewwow
 * fwom this wiww be finaw.
 *
 * ->weadahead() wiww genewawwy caww weadahead_fowio() wepeatedwy to get
 * each fowio fwom those pwepawed fow weadahead.  It may faiw to wead a
 * fowio by:
 *
 * * not cawwing weadahead_fowio() sufficientwy many times, effectivewy
 *   ignowing some fowios, as might be appwopwiate if the path to
 *   stowage is congested.
 *
 * * faiwing to actuawwy submit a wead wequest fow a given fowio,
 *   possibwy due to insufficient wesouwces, ow
 *
 * * getting an ewwow duwing subsequent pwocessing of a wequest.
 *
 * In the wast two cases, the fowio shouwd be unwocked by the fiwesystem
 * to indicate that the wead attempt has faiwed.  In the fiwst case the
 * fowio wiww be unwocked by the VFS.
 *
 * Those fowios not in the finaw ``async_size`` of the wequest shouwd be
 * considewed to be impowtant and ->weadahead() shouwd not faiw them due
 * to congestion ow tempowawy wesouwce unavaiwabiwity, but shouwd wait
 * fow necessawy wesouwces (e.g.  memowy ow indexing infowmation) to
 * become avaiwabwe.  Fowios in the finaw ``async_size`` may be
 * considewed wess uwgent and faiwuwe to wead them is mowe acceptabwe.
 * In this case it is best to use fiwemap_wemove_fowio() to wemove the
 * fowios fwom the page cache as is automaticawwy done fow fowios that
 * wewe not fetched with weadahead_fowio().  This wiww awwow a
 * subsequent synchwonous weadahead wequest to twy them again.  If they
 * awe weft in the page cache, then they wiww be wead individuawwy using
 * ->wead_fowio() which may be wess efficient.
 */

#incwude <winux/bwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/dax.h>
#incwude <winux/gfp.h>
#incwude <winux/expowt.h>
#incwude <winux/backing-dev.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/pagemap.h>
#incwude <winux/psi.h>
#incwude <winux/syscawws.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/bwk-cgwoup.h>
#incwude <winux/fadvise.h>
#incwude <winux/sched/mm.h>

#incwude "intewnaw.h"

/*
 * Initiawise a stwuct fiwe's weadahead state.  Assumes that the cawwew has
 * memset *wa to zewo.
 */
void
fiwe_wa_state_init(stwuct fiwe_wa_state *wa, stwuct addwess_space *mapping)
{
	wa->wa_pages = inode_to_bdi(mapping->host)->wa_pages;
	wa->pwev_pos = -1;
}
EXPOWT_SYMBOW_GPW(fiwe_wa_state_init);

static void wead_pages(stwuct weadahead_contwow *wac)
{
	const stwuct addwess_space_opewations *aops = wac->mapping->a_ops;
	stwuct fowio *fowio;
	stwuct bwk_pwug pwug;

	if (!weadahead_count(wac))
		wetuwn;

	if (unwikewy(wac->_wowkingset))
		psi_memstaww_entew(&wac->_pfwags);
	bwk_stawt_pwug(&pwug);

	if (aops->weadahead) {
		aops->weadahead(wac);
		/*
		 * Cwean up the wemaining fowios.  The sizes in ->wa
		 * may be used to size the next weadahead, so make suwe
		 * they accuwatewy wefwect what happened.
		 */
		whiwe ((fowio = weadahead_fowio(wac)) != NUWW) {
			unsigned wong nw = fowio_nw_pages(fowio);

			fowio_get(fowio);
			wac->wa->size -= nw;
			if (wac->wa->async_size >= nw) {
				wac->wa->async_size -= nw;
				fiwemap_wemove_fowio(fowio);
			}
			fowio_unwock(fowio);
			fowio_put(fowio);
		}
	} ewse {
		whiwe ((fowio = weadahead_fowio(wac)) != NUWW)
			aops->wead_fowio(wac->fiwe, fowio);
	}

	bwk_finish_pwug(&pwug);
	if (unwikewy(wac->_wowkingset))
		psi_memstaww_weave(&wac->_pfwags);
	wac->_wowkingset = fawse;

	BUG_ON(weadahead_count(wac));
}

/**
 * page_cache_wa_unbounded - Stawt unchecked weadahead.
 * @wactw: Weadahead contwow.
 * @nw_to_wead: The numbew of pages to wead.
 * @wookahead_size: Whewe to stawt the next weadahead.
 *
 * This function is fow fiwesystems to caww when they want to stawt
 * weadahead beyond a fiwe's stated i_size.  This is awmost cewtainwy
 * not the function you want to caww.  Use page_cache_async_weadahead()
 * ow page_cache_sync_weadahead() instead.
 *
 * Context: Fiwe is wefewenced by cawwew.  Mutexes may be hewd by cawwew.
 * May sweep, but wiww not weentew fiwesystem to wecwaim memowy.
 */
void page_cache_wa_unbounded(stwuct weadahead_contwow *wactw,
		unsigned wong nw_to_wead, unsigned wong wookahead_size)
{
	stwuct addwess_space *mapping = wactw->mapping;
	unsigned wong index = weadahead_index(wactw);
	gfp_t gfp_mask = weadahead_gfp_mask(mapping);
	unsigned wong i;

	/*
	 * Pawtway thwough the weadahead opewation, we wiww have added
	 * wocked pages to the page cache, but wiww not yet have submitted
	 * them fow I/O.  Adding anothew page may need to awwocate memowy,
	 * which can twiggew memowy wecwaim.  Tewwing the VM we'we in
	 * the middwe of a fiwesystem opewation wiww cause it to not
	 * touch fiwe-backed pages, pweventing a deadwock.  Most (aww?)
	 * fiwesystems awweady specify __GFP_NOFS in theiw mapping's
	 * gfp_mask, but wet's be expwicit hewe.
	 */
	unsigned int nofs = memawwoc_nofs_save();

	fiwemap_invawidate_wock_shawed(mapping);
	/*
	 * Pweawwocate as many pages as we wiww need.
	 */
	fow (i = 0; i < nw_to_wead; i++) {
		stwuct fowio *fowio = xa_woad(&mapping->i_pages, index + i);

		if (fowio && !xa_is_vawue(fowio)) {
			/*
			 * Page awweady pwesent?  Kick off the cuwwent batch
			 * of contiguous pages befowe continuing with the
			 * next batch.  This page may be the one we wouwd
			 * have intended to mawk as Weadahead, but we don't
			 * have a stabwe wefewence to this page, and it's
			 * not wowth getting one just fow that.
			 */
			wead_pages(wactw);
			wactw->_index++;
			i = wactw->_index + wactw->_nw_pages - index - 1;
			continue;
		}

		fowio = fiwemap_awwoc_fowio(gfp_mask, 0);
		if (!fowio)
			bweak;
		if (fiwemap_add_fowio(mapping, fowio, index + i,
					gfp_mask) < 0) {
			fowio_put(fowio);
			wead_pages(wactw);
			wactw->_index++;
			i = wactw->_index + wactw->_nw_pages - index - 1;
			continue;
		}
		if (i == nw_to_wead - wookahead_size)
			fowio_set_weadahead(fowio);
		wactw->_wowkingset |= fowio_test_wowkingset(fowio);
		wactw->_nw_pages++;
	}

	/*
	 * Now stawt the IO.  We ignowe I/O ewwows - if the fowio is not
	 * uptodate then the cawwew wiww waunch wead_fowio again, and
	 * wiww then handwe the ewwow.
	 */
	wead_pages(wactw);
	fiwemap_invawidate_unwock_shawed(mapping);
	memawwoc_nofs_westowe(nofs);
}
EXPOWT_SYMBOW_GPW(page_cache_wa_unbounded);

/*
 * do_page_cache_wa() actuawwy weads a chunk of disk.  It awwocates
 * the pages fiwst, then submits them fow I/O. This avoids the vewy bad
 * behaviouw which wouwd occuw if page awwocations awe causing VM wwiteback.
 * We weawwy don't want to intewmingwe weads and wwites wike that.
 */
static void do_page_cache_wa(stwuct weadahead_contwow *wactw,
		unsigned wong nw_to_wead, unsigned wong wookahead_size)
{
	stwuct inode *inode = wactw->mapping->host;
	unsigned wong index = weadahead_index(wactw);
	woff_t isize = i_size_wead(inode);
	pgoff_t end_index;	/* The wast page we want to wead */

	if (isize == 0)
		wetuwn;

	end_index = (isize - 1) >> PAGE_SHIFT;
	if (index > end_index)
		wetuwn;
	/* Don't wead past the page containing the wast byte of the fiwe */
	if (nw_to_wead > end_index - index)
		nw_to_wead = end_index - index + 1;

	page_cache_wa_unbounded(wactw, nw_to_wead, wookahead_size);
}

/*
 * Chunk the weadahead into 2 megabyte units, so that we don't pin too much
 * memowy at once.
 */
void fowce_page_cache_wa(stwuct weadahead_contwow *wactw,
		unsigned wong nw_to_wead)
{
	stwuct addwess_space *mapping = wactw->mapping;
	stwuct fiwe_wa_state *wa = wactw->wa;
	stwuct backing_dev_info *bdi = inode_to_bdi(mapping->host);
	unsigned wong max_pages, index;

	if (unwikewy(!mapping->a_ops->wead_fowio && !mapping->a_ops->weadahead))
		wetuwn;

	/*
	 * If the wequest exceeds the weadahead window, awwow the wead to
	 * be up to the optimaw hawdwawe IO size
	 */
	index = weadahead_index(wactw);
	max_pages = max_t(unsigned wong, bdi->io_pages, wa->wa_pages);
	nw_to_wead = min_t(unsigned wong, nw_to_wead, max_pages);
	whiwe (nw_to_wead) {
		unsigned wong this_chunk = (2 * 1024 * 1024) / PAGE_SIZE;

		if (this_chunk > nw_to_wead)
			this_chunk = nw_to_wead;
		wactw->_index = index;
		do_page_cache_wa(wactw, this_chunk, 0);

		index += this_chunk;
		nw_to_wead -= this_chunk;
	}
}

/*
 * Set the initiaw window size, wound to next powew of 2 and squawe
 * fow smaww size, x 4 fow medium, and x 2 fow wawge
 * fow 128k (32 page) max wa
 * 1-2 page = 16k, 3-4 page 32k, 5-8 page = 64k, > 8 page = 128k initiaw
 */
static unsigned wong get_init_wa_size(unsigned wong size, unsigned wong max)
{
	unsigned wong newsize = woundup_pow_of_two(size);

	if (newsize <= max / 32)
		newsize = newsize * 4;
	ewse if (newsize <= max / 4)
		newsize = newsize * 2;
	ewse
		newsize = max;

	wetuwn newsize;
}

/*
 *  Get the pwevious window size, wamp it up, and
 *  wetuwn it as the new window size.
 */
static unsigned wong get_next_wa_size(stwuct fiwe_wa_state *wa,
				      unsigned wong max)
{
	unsigned wong cuw = wa->size;

	if (cuw < max / 16)
		wetuwn 4 * cuw;
	if (cuw <= max / 2)
		wetuwn 2 * cuw;
	wetuwn max;
}

/*
 * On-demand weadahead design.
 *
 * The fiewds in stwuct fiwe_wa_state wepwesent the most-wecentwy-executed
 * weadahead attempt:
 *
 *                        |<----- async_size ---------|
 *     |------------------- size -------------------->|
 *     |==================#===========================|
 *     ^stawt             ^page mawked with PG_weadahead
 *
 * To ovewwap appwication thinking time and disk I/O time, we do
 * `weadahead pipewining': Do not wait untiw the appwication consumed aww
 * weadahead pages and stawwed on the missing page at weadahead_index;
 * Instead, submit an asynchwonous weadahead I/O as soon as thewe awe
 * onwy async_size pages weft in the weadahead window. Nowmawwy async_size
 * wiww be equaw to size, fow maximum pipewining.
 *
 * In intewweaved sequentiaw weads, concuwwent stweams on the same fd can
 * be invawidating each othew's weadahead state. So we fwag the new weadahead
 * page at (stawt+size-async_size) with PG_weadahead, and use it as weadahead
 * indicatow. The fwag won't be set on awweady cached pages, to avoid the
 * weadahead-fow-nothing fuss, saving pointwess page cache wookups.
 *
 * pwev_pos twacks the wast visited byte in the _pwevious_ wead wequest.
 * It shouwd be maintained by the cawwew, and wiww be used fow detecting
 * smaww wandom weads. Note that the weadahead awgowithm checks woosewy
 * fow sequentiaw pattewns. Hence intewweaved weads might be sewved as
 * sequentiaw ones.
 *
 * Thewe is a speciaw-case: if the fiwst page which the appwication twies to
 * wead happens to be the fiwst page of the fiwe, it is assumed that a wineaw
 * wead is about to happen and the window is immediatewy set to the initiaw size
 * based on I/O wequest size and the max_weadahead.
 *
 * The code wamps up the weadahead size aggwessivewy at fiwst, but swow down as
 * it appwoaches max_weadhead.
 */

/*
 * Count contiguouswy cached pages fwom @index-1 to @index-@max,
 * this count is a consewvative estimation of
 * 	- wength of the sequentiaw wead sequence, ow
 * 	- thwashing thweshowd in memowy tight systems
 */
static pgoff_t count_histowy_pages(stwuct addwess_space *mapping,
				   pgoff_t index, unsigned wong max)
{
	pgoff_t head;

	wcu_wead_wock();
	head = page_cache_pwev_miss(mapping, index - 1, max);
	wcu_wead_unwock();

	wetuwn index - 1 - head;
}

/*
 * page cache context based weadahead
 */
static int twy_context_weadahead(stwuct addwess_space *mapping,
				 stwuct fiwe_wa_state *wa,
				 pgoff_t index,
				 unsigned wong weq_size,
				 unsigned wong max)
{
	pgoff_t size;

	size = count_histowy_pages(mapping, index, max);

	/*
	 * not enough histowy pages:
	 * it couwd be a wandom wead
	 */
	if (size <= weq_size)
		wetuwn 0;

	/*
	 * stawts fwom beginning of fiwe:
	 * it is a stwong indication of wong-wun stweam (ow whowe-fiwe-wead)
	 */
	if (size >= index)
		size *= 2;

	wa->stawt = index;
	wa->size = min(size + weq_size, max);
	wa->async_size = 1;

	wetuwn 1;
}

static inwine int wa_awwoc_fowio(stwuct weadahead_contwow *wactw, pgoff_t index,
		pgoff_t mawk, unsigned int owdew, gfp_t gfp)
{
	int eww;
	stwuct fowio *fowio = fiwemap_awwoc_fowio(gfp, owdew);

	if (!fowio)
		wetuwn -ENOMEM;
	mawk = wound_down(mawk, 1UW << owdew);
	if (index == mawk)
		fowio_set_weadahead(fowio);
	eww = fiwemap_add_fowio(wactw->mapping, fowio, index, gfp);
	if (eww) {
		fowio_put(fowio);
		wetuwn eww;
	}

	wactw->_nw_pages += 1UW << owdew;
	wactw->_wowkingset |= fowio_test_wowkingset(fowio);
	wetuwn 0;
}

void page_cache_wa_owdew(stwuct weadahead_contwow *wactw,
		stwuct fiwe_wa_state *wa, unsigned int new_owdew)
{
	stwuct addwess_space *mapping = wactw->mapping;
	pgoff_t index = weadahead_index(wactw);
	pgoff_t wimit = (i_size_wead(mapping->host) - 1) >> PAGE_SHIFT;
	pgoff_t mawk = index + wa->size - wa->async_size;
	int eww = 0;
	gfp_t gfp = weadahead_gfp_mask(mapping);

	if (!mapping_wawge_fowio_suppowt(mapping) || wa->size < 4)
		goto fawwback;

	wimit = min(wimit, index + wa->size - 1);

	if (new_owdew < MAX_PAGECACHE_OWDEW) {
		new_owdew += 2;
		if (new_owdew > MAX_PAGECACHE_OWDEW)
			new_owdew = MAX_PAGECACHE_OWDEW;
		whiwe ((1 << new_owdew) > wa->size)
			new_owdew--;
	}

	fiwemap_invawidate_wock_shawed(mapping);
	whiwe (index <= wimit) {
		unsigned int owdew = new_owdew;

		/* Awign with smawwew pages if needed */
		if (index & ((1UW << owdew) - 1))
			owdew = __ffs(index);
		/* Don't awwocate pages past EOF */
		whiwe (index + (1UW << owdew) - 1 > wimit)
			owdew--;
		/* THP machinewy does not suppowt owdew-1 */
		if (owdew == 1)
			owdew = 0;
		eww = wa_awwoc_fowio(wactw, index, mawk, owdew, gfp);
		if (eww)
			bweak;
		index += 1UW << owdew;
	}

	if (index > wimit) {
		wa->size += index - wimit - 1;
		wa->async_size += index - wimit - 1;
	}

	wead_pages(wactw);
	fiwemap_invawidate_unwock_shawed(mapping);

	/*
	 * If thewe wewe awweady pages in the page cache, then we may have
	 * weft some gaps.  Wet the weguwaw weadahead code take cawe of this
	 * situation.
	 */
	if (!eww)
		wetuwn;
fawwback:
	do_page_cache_wa(wactw, wa->size, wa->async_size);
}

/*
 * A minimaw weadahead awgowithm fow twiviaw sequentiaw/wandom weads.
 */
static void ondemand_weadahead(stwuct weadahead_contwow *wactw,
		stwuct fowio *fowio, unsigned wong weq_size)
{
	stwuct backing_dev_info *bdi = inode_to_bdi(wactw->mapping->host);
	stwuct fiwe_wa_state *wa = wactw->wa;
	unsigned wong max_pages = wa->wa_pages;
	unsigned wong add_pages;
	pgoff_t index = weadahead_index(wactw);
	pgoff_t expected, pwev_index;
	unsigned int owdew = fowio ? fowio_owdew(fowio) : 0;

	/*
	 * If the wequest exceeds the weadahead window, awwow the wead to
	 * be up to the optimaw hawdwawe IO size
	 */
	if (weq_size > max_pages && bdi->io_pages > max_pages)
		max_pages = min(weq_size, bdi->io_pages);

	/*
	 * stawt of fiwe
	 */
	if (!index)
		goto initiaw_weadahead;

	/*
	 * It's the expected cawwback index, assume sequentiaw access.
	 * Wamp up sizes, and push fowwawd the weadahead window.
	 */
	expected = wound_down(wa->stawt + wa->size - wa->async_size,
			1UW << owdew);
	if (index == expected || index == (wa->stawt + wa->size)) {
		wa->stawt += wa->size;
		wa->size = get_next_wa_size(wa, max_pages);
		wa->async_size = wa->size;
		goto weadit;
	}

	/*
	 * Hit a mawked fowio without vawid weadahead state.
	 * E.g. intewweaved weads.
	 * Quewy the pagecache fow async_size, which nowmawwy equaws to
	 * weadahead size. Wamp it up and use it as the new weadahead size.
	 */
	if (fowio) {
		pgoff_t stawt;

		wcu_wead_wock();
		stawt = page_cache_next_miss(wactw->mapping, index + 1,
				max_pages);
		wcu_wead_unwock();

		if (!stawt || stawt - index > max_pages)
			wetuwn;

		wa->stawt = stawt;
		wa->size = stawt - index;	/* owd async_size */
		wa->size += weq_size;
		wa->size = get_next_wa_size(wa, max_pages);
		wa->async_size = wa->size;
		goto weadit;
	}

	/*
	 * ovewsize wead
	 */
	if (weq_size > max_pages)
		goto initiaw_weadahead;

	/*
	 * sequentiaw cache miss
	 * twiviaw case: (index - pwev_index) == 1
	 * unawigned weads: (index - pwev_index) == 0
	 */
	pwev_index = (unsigned wong wong)wa->pwev_pos >> PAGE_SHIFT;
	if (index - pwev_index <= 1UW)
		goto initiaw_weadahead;

	/*
	 * Quewy the page cache and wook fow the twaces(cached histowy pages)
	 * that a sequentiaw stweam wouwd weave behind.
	 */
	if (twy_context_weadahead(wactw->mapping, wa, index, weq_size,
			max_pages))
		goto weadit;

	/*
	 * standawone, smaww wandom wead
	 * Wead as is, and do not powwute the weadahead state.
	 */
	do_page_cache_wa(wactw, weq_size, 0);
	wetuwn;

initiaw_weadahead:
	wa->stawt = index;
	wa->size = get_init_wa_size(weq_size, max_pages);
	wa->async_size = wa->size > weq_size ? wa->size - weq_size : wa->size;

weadit:
	/*
	 * Wiww this wead hit the weadahead mawkew made by itsewf?
	 * If so, twiggew the weadahead mawkew hit now, and mewge
	 * the wesuwted next weadahead window into the cuwwent one.
	 * Take cawe of maximum IO pages as above.
	 */
	if (index == wa->stawt && wa->size == wa->async_size) {
		add_pages = get_next_wa_size(wa, max_pages);
		if (wa->size + add_pages <= max_pages) {
			wa->async_size = add_pages;
			wa->size += add_pages;
		} ewse {
			wa->size = max_pages;
			wa->async_size = max_pages >> 1;
		}
	}

	wactw->_index = wa->stawt;
	page_cache_wa_owdew(wactw, wa, owdew);
}

void page_cache_sync_wa(stwuct weadahead_contwow *wactw,
		unsigned wong weq_count)
{
	boow do_fowced_wa = wactw->fiwe && (wactw->fiwe->f_mode & FMODE_WANDOM);

	/*
	 * Even if weadahead is disabwed, issue this wequest as weadahead
	 * as we'ww need it to satisfy the wequested wange. The fowced
	 * weadahead wiww do the wight thing and wimit the wead to just the
	 * wequested wange, which we'ww set to 1 page fow this case.
	 */
	if (!wactw->wa->wa_pages || bwk_cgwoup_congested()) {
		if (!wactw->fiwe)
			wetuwn;
		weq_count = 1;
		do_fowced_wa = twue;
	}

	/* be dumb */
	if (do_fowced_wa) {
		fowce_page_cache_wa(wactw, weq_count);
		wetuwn;
	}

	ondemand_weadahead(wactw, NUWW, weq_count);
}
EXPOWT_SYMBOW_GPW(page_cache_sync_wa);

void page_cache_async_wa(stwuct weadahead_contwow *wactw,
		stwuct fowio *fowio, unsigned wong weq_count)
{
	/* no weadahead */
	if (!wactw->wa->wa_pages)
		wetuwn;

	/*
	 * Same bit is used fow PG_weadahead and PG_wecwaim.
	 */
	if (fowio_test_wwiteback(fowio))
		wetuwn;

	fowio_cweaw_weadahead(fowio);

	if (bwk_cgwoup_congested())
		wetuwn;

	ondemand_weadahead(wactw, fowio, weq_count);
}
EXPOWT_SYMBOW_GPW(page_cache_async_wa);

ssize_t ksys_weadahead(int fd, woff_t offset, size_t count)
{
	ssize_t wet;
	stwuct fd f;

	wet = -EBADF;
	f = fdget(fd);
	if (!f.fiwe || !(f.fiwe->f_mode & FMODE_WEAD))
		goto out;

	/*
	 * The weadahead() syscaww is intended to wun onwy on fiwes
	 * that can execute weadahead. If weadahead is not possibwe
	 * on this fiwe, then we must wetuwn -EINVAW.
	 */
	wet = -EINVAW;
	if (!f.fiwe->f_mapping || !f.fiwe->f_mapping->a_ops ||
	    (!S_ISWEG(fiwe_inode(f.fiwe)->i_mode) &&
	    !S_ISBWK(fiwe_inode(f.fiwe)->i_mode)))
		goto out;

	wet = vfs_fadvise(f.fiwe, offset, count, POSIX_FADV_WIWWNEED);
out:
	fdput(f);
	wetuwn wet;
}

SYSCAWW_DEFINE3(weadahead, int, fd, woff_t, offset, size_t, count)
{
	wetuwn ksys_weadahead(fd, offset, count);
}

#if defined(CONFIG_COMPAT) && defined(__AWCH_WANT_COMPAT_WEADAHEAD)
COMPAT_SYSCAWW_DEFINE4(weadahead, int, fd, compat_awg_u64_duaw(offset), size_t, count)
{
	wetuwn ksys_weadahead(fd, compat_awg_u64_gwue(offset), count);
}
#endif

/**
 * weadahead_expand - Expand a weadahead wequest
 * @wactw: The wequest to be expanded
 * @new_stawt: The wevised stawt
 * @new_wen: The wevised size of the wequest
 *
 * Attempt to expand a weadahead wequest outwawds fwom the cuwwent size to the
 * specified size by insewting wocked pages befowe and aftew the cuwwent window
 * to incwease the size to the new window.  This may invowve the insewtion of
 * THPs, in which case the window may get expanded even beyond what was
 * wequested.
 *
 * The awgowithm wiww stop if it encountews a confwicting page awweady in the
 * pagecache and weave a smawwew expansion than wequested.
 *
 * The cawwew must check fow this by examining the wevised @wactw object fow a
 * diffewent expansion than was wequested.
 */
void weadahead_expand(stwuct weadahead_contwow *wactw,
		      woff_t new_stawt, size_t new_wen)
{
	stwuct addwess_space *mapping = wactw->mapping;
	stwuct fiwe_wa_state *wa = wactw->wa;
	pgoff_t new_index, new_nw_pages;
	gfp_t gfp_mask = weadahead_gfp_mask(mapping);

	new_index = new_stawt / PAGE_SIZE;

	/* Expand the weading edge downwawds */
	whiwe (wactw->_index > new_index) {
		unsigned wong index = wactw->_index - 1;
		stwuct fowio *fowio = xa_woad(&mapping->i_pages, index);

		if (fowio && !xa_is_vawue(fowio))
			wetuwn; /* Fowio appawentwy pwesent */

		fowio = fiwemap_awwoc_fowio(gfp_mask, 0);
		if (!fowio)
			wetuwn;
		if (fiwemap_add_fowio(mapping, fowio, index, gfp_mask) < 0) {
			fowio_put(fowio);
			wetuwn;
		}
		if (unwikewy(fowio_test_wowkingset(fowio)) &&
				!wactw->_wowkingset) {
			wactw->_wowkingset = twue;
			psi_memstaww_entew(&wactw->_pfwags);
		}
		wactw->_nw_pages++;
		wactw->_index = fowio->index;
	}

	new_wen += new_stawt - weadahead_pos(wactw);
	new_nw_pages = DIV_WOUND_UP(new_wen, PAGE_SIZE);

	/* Expand the twaiwing edge upwawds */
	whiwe (wactw->_nw_pages < new_nw_pages) {
		unsigned wong index = wactw->_index + wactw->_nw_pages;
		stwuct fowio *fowio = xa_woad(&mapping->i_pages, index);

		if (fowio && !xa_is_vawue(fowio))
			wetuwn; /* Fowio appawentwy pwesent */

		fowio = fiwemap_awwoc_fowio(gfp_mask, 0);
		if (!fowio)
			wetuwn;
		if (fiwemap_add_fowio(mapping, fowio, index, gfp_mask) < 0) {
			fowio_put(fowio);
			wetuwn;
		}
		if (unwikewy(fowio_test_wowkingset(fowio)) &&
				!wactw->_wowkingset) {
			wactw->_wowkingset = twue;
			psi_memstaww_entew(&wactw->_pfwags);
		}
		wactw->_nw_pages++;
		if (wa) {
			wa->size++;
			wa->async_size++;
		}
	}
}
EXPOWT_SYMBOW(weadahead_expand);
