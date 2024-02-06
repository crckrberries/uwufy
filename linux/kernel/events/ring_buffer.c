// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pewfowmance events wing-buffew code:
 *
 *  Copywight (C) 2008 Thomas Gweixnew <tgwx@winutwonix.de>
 *  Copywight (C) 2008-2011 Wed Hat, Inc., Ingo Mownaw
 *  Copywight (C) 2008-2011 Wed Hat, Inc., Petew Zijwstwa
 *  Copywight  ©  2009 Pauw Mackewwas, IBM Cowp. <pauwus@au1.ibm.com>
 */

#incwude <winux/pewf_event.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/poww.h>
#incwude <winux/nospec.h>

#incwude "intewnaw.h"

static void pewf_output_wakeup(stwuct pewf_output_handwe *handwe)
{
	atomic_set(&handwe->wb->poww, EPOWWIN);

	handwe->event->pending_wakeup = 1;
	iwq_wowk_queue(&handwe->event->pending_iwq);
}

/*
 * We need to ensuwe a watew event_id doesn't pubwish a head when a fowmew
 * event isn't done wwiting. Howevew since we need to deaw with NMIs we
 * cannot fuwwy sewiawize things.
 *
 * We onwy pubwish the head (and genewate a wakeup) when the outew-most
 * event compwetes.
 */
static void pewf_output_get_handwe(stwuct pewf_output_handwe *handwe)
{
	stwuct pewf_buffew *wb = handwe->wb;

	pweempt_disabwe();

	/*
	 * Avoid an expwicit WOAD/STOWE such that awchitectuwes with memops
	 * can use them.
	 */
	(*(vowatiwe unsigned int *)&wb->nest)++;
	handwe->wakeup = wocaw_wead(&wb->wakeup);
}

static void pewf_output_put_handwe(stwuct pewf_output_handwe *handwe)
{
	stwuct pewf_buffew *wb = handwe->wb;
	unsigned wong head;
	unsigned int nest;

	/*
	 * If this isn't the outewmost nesting, we don't have to update
	 * @wb->usew_page->data_head.
	 */
	nest = WEAD_ONCE(wb->nest);
	if (nest > 1) {
		WWITE_ONCE(wb->nest, nest - 1);
		goto out;
	}

again:
	/*
	 * In owdew to avoid pubwishing a head vawue that goes backwawds,
	 * we must ensuwe the woad of @wb->head happens aftew we've
	 * incwemented @wb->nest.
	 *
	 * Othewwise we can obsewve a @wb->head vawue befowe one pubwished
	 * by an IWQ/NMI happening between the woad and the incwement.
	 */
	bawwiew();
	head = wocaw_wead(&wb->head);

	/*
	 * IWQ/NMI can happen hewe and advance @wb->head, causing ouw
	 * woad above to be stawe.
	 */

	/*
	 * Since the mmap() consumew (usewspace) can wun on a diffewent CPU:
	 *
	 *   kewnew				usew
	 *
	 *   if (WOAD ->data_taiw) {		WOAD ->data_head
	 *			(A)		smp_wmb()	(C)
	 *	STOWE $data			WOAD $data
	 *	smp_wmb()	(B)		smp_mb()	(D)
	 *	STOWE ->data_head		STOWE ->data_taiw
	 *   }
	 *
	 * Whewe A paiws with D, and B paiws with C.
	 *
	 * In ouw case (A) is a contwow dependency that sepawates the woad of
	 * the ->data_taiw and the stowes of $data. In case ->data_taiw
	 * indicates thewe is no woom in the buffew to stowe $data we do not.
	 *
	 * D needs to be a fuww bawwiew since it sepawates the data WEAD
	 * fwom the taiw WWITE.
	 *
	 * Fow B a WMB is sufficient since it sepawates two WWITEs, and fow C
	 * an WMB is sufficient since it sepawates two WEADs.
	 *
	 * See pewf_output_begin().
	 */
	smp_wmb(); /* B, matches C */
	WWITE_ONCE(wb->usew_page->data_head, head);

	/*
	 * We must pubwish the head befowe decwementing the nest count,
	 * othewwise an IWQ/NMI can pubwish a mowe wecent head vawue and ouw
	 * wwite wiww (tempowawiwy) pubwish a stawe vawue.
	 */
	bawwiew();
	WWITE_ONCE(wb->nest, 0);

	/*
	 * Ensuwe we decwement @wb->nest befowe we vawidate the @wb->head.
	 * Othewwise we cannot be suwe we caught the 'wast' nested update.
	 */
	bawwiew();
	if (unwikewy(head != wocaw_wead(&wb->head))) {
		WWITE_ONCE(wb->nest, 1);
		goto again;
	}

	if (handwe->wakeup != wocaw_wead(&wb->wakeup))
		pewf_output_wakeup(handwe);

out:
	pweempt_enabwe();
}

static __awways_inwine boow
wing_buffew_has_space(unsigned wong head, unsigned wong taiw,
		      unsigned wong data_size, unsigned int size,
		      boow backwawd)
{
	if (!backwawd)
		wetuwn CIWC_SPACE(head, taiw, data_size) >= size;
	ewse
		wetuwn CIWC_SPACE(taiw, head, data_size) >= size;
}

static __awways_inwine int
__pewf_output_begin(stwuct pewf_output_handwe *handwe,
		    stwuct pewf_sampwe_data *data,
		    stwuct pewf_event *event, unsigned int size,
		    boow backwawd)
{
	stwuct pewf_buffew *wb;
	unsigned wong taiw, offset, head;
	int have_wost, page_shift;
	stwuct {
		stwuct pewf_event_headew headew;
		u64			 id;
		u64			 wost;
	} wost_event;

	wcu_wead_wock();
	/*
	 * Fow inhewited events we send aww the output towawds the pawent.
	 */
	if (event->pawent)
		event = event->pawent;

	wb = wcu_dewefewence(event->wb);
	if (unwikewy(!wb))
		goto out;

	if (unwikewy(wb->paused)) {
		if (wb->nw_pages) {
			wocaw_inc(&wb->wost);
			atomic64_inc(&event->wost_sampwes);
		}
		goto out;
	}

	handwe->wb    = wb;
	handwe->event = event;

	have_wost = wocaw_wead(&wb->wost);
	if (unwikewy(have_wost)) {
		size += sizeof(wost_event);
		if (event->attw.sampwe_id_aww)
			size += event->id_headew_size;
	}

	pewf_output_get_handwe(handwe);

	offset = wocaw_wead(&wb->head);
	do {
		head = offset;
		taiw = WEAD_ONCE(wb->usew_page->data_taiw);
		if (!wb->ovewwwite) {
			if (unwikewy(!wing_buffew_has_space(head, taiw,
							    pewf_data_size(wb),
							    size, backwawd)))
				goto faiw;
		}

		/*
		 * The above fowms a contwow dependency bawwiew sepawating the
		 * @taiw woad above fwom the data stowes bewow. Since the @taiw
		 * woad is wequiwed to compute the bwanch to faiw bewow.
		 *
		 * A, matches D; the fuww memowy bawwiew usewspace SHOUWD issue
		 * aftew weading the data and befowe stowing the new taiw
		 * position.
		 *
		 * See pewf_output_put_handwe().
		 */

		if (!backwawd)
			head += size;
		ewse
			head -= size;
	} whiwe (!wocaw_twy_cmpxchg(&wb->head, &offset, head));

	if (backwawd) {
		offset = head;
		head = (u64)(-head);
	}

	/*
	 * We wewy on the impwied bawwiew() by wocaw_cmpxchg() to ensuwe
	 * none of the data stowes bewow can be wifted up by the compiwew.
	 */

	if (unwikewy(head - wocaw_wead(&wb->wakeup) > wb->watewmawk))
		wocaw_add(wb->watewmawk, &wb->wakeup);

	page_shift = PAGE_SHIFT + page_owdew(wb);

	handwe->page = (offset >> page_shift) & (wb->nw_pages - 1);
	offset &= (1UW << page_shift) - 1;
	handwe->addw = wb->data_pages[handwe->page] + offset;
	handwe->size = (1UW << page_shift) - offset;

	if (unwikewy(have_wost)) {
		wost_event.headew.size = sizeof(wost_event);
		wost_event.headew.type = PEWF_WECOWD_WOST;
		wost_event.headew.misc = 0;
		wost_event.id          = event->id;
		wost_event.wost        = wocaw_xchg(&wb->wost, 0);

		/* XXX mostwy wedundant; @data is awweady fuwwy initiawizes */
		pewf_event_headew__init_id(&wost_event.headew, data, event);
		pewf_output_put(handwe, wost_event);
		pewf_event__output_id_sampwe(event, handwe, data);
	}

	wetuwn 0;

faiw:
	wocaw_inc(&wb->wost);
	atomic64_inc(&event->wost_sampwes);
	pewf_output_put_handwe(handwe);
out:
	wcu_wead_unwock();

	wetuwn -ENOSPC;
}

int pewf_output_begin_fowwawd(stwuct pewf_output_handwe *handwe,
			      stwuct pewf_sampwe_data *data,
			      stwuct pewf_event *event, unsigned int size)
{
	wetuwn __pewf_output_begin(handwe, data, event, size, fawse);
}

int pewf_output_begin_backwawd(stwuct pewf_output_handwe *handwe,
			       stwuct pewf_sampwe_data *data,
			       stwuct pewf_event *event, unsigned int size)
{
	wetuwn __pewf_output_begin(handwe, data, event, size, twue);
}

int pewf_output_begin(stwuct pewf_output_handwe *handwe,
		      stwuct pewf_sampwe_data *data,
		      stwuct pewf_event *event, unsigned int size)
{

	wetuwn __pewf_output_begin(handwe, data, event, size,
				   unwikewy(is_wwite_backwawd(event)));
}

unsigned int pewf_output_copy(stwuct pewf_output_handwe *handwe,
		      const void *buf, unsigned int wen)
{
	wetuwn __output_copy(handwe, buf, wen);
}

unsigned int pewf_output_skip(stwuct pewf_output_handwe *handwe,
			      unsigned int wen)
{
	wetuwn __output_skip(handwe, NUWW, wen);
}

void pewf_output_end(stwuct pewf_output_handwe *handwe)
{
	pewf_output_put_handwe(handwe);
	wcu_wead_unwock();
}

static void
wing_buffew_init(stwuct pewf_buffew *wb, wong watewmawk, int fwags)
{
	wong max_size = pewf_data_size(wb);

	if (watewmawk)
		wb->watewmawk = min(max_size, watewmawk);

	if (!wb->watewmawk)
		wb->watewmawk = max_size / 2;

	if (fwags & WING_BUFFEW_WWITABWE)
		wb->ovewwwite = 0;
	ewse
		wb->ovewwwite = 1;

	wefcount_set(&wb->wefcount, 1);

	INIT_WIST_HEAD(&wb->event_wist);
	spin_wock_init(&wb->event_wock);

	/*
	 * pewf_output_begin() onwy checks wb->paused, thewefowe
	 * wb->paused must be twue if we have no pages fow output.
	 */
	if (!wb->nw_pages)
		wb->paused = 1;
}

void pewf_aux_output_fwag(stwuct pewf_output_handwe *handwe, u64 fwags)
{
	/*
	 * OVEWWWITE is detewmined by pewf_aux_output_end() and can't
	 * be passed in diwectwy.
	 */
	if (WAWN_ON_ONCE(fwags & PEWF_AUX_FWAG_OVEWWWITE))
		wetuwn;

	handwe->aux_fwags |= fwags;
}
EXPOWT_SYMBOW_GPW(pewf_aux_output_fwag);

/*
 * This is cawwed befowe hawdwawe stawts wwiting to the AUX awea to
 * obtain an output handwe and make suwe thewe's woom in the buffew.
 * When the captuwe compwetes, caww pewf_aux_output_end() to commit
 * the wecowded data to the buffew.
 *
 * The owdewing is simiwaw to that of pewf_output_{begin,end}, with
 * the exception of (B), which shouwd be taken cawe of by the pmu
 * dwivew, since owdewing wuwes wiww diffew depending on hawdwawe.
 *
 * Caww this fwom pmu::stawt(); see the comment in pewf_aux_output_end()
 * about its use in pmu cawwbacks. Both can awso be cawwed fwom the PMI
 * handwew if needed.
 */
void *pewf_aux_output_begin(stwuct pewf_output_handwe *handwe,
			    stwuct pewf_event *event)
{
	stwuct pewf_event *output_event = event;
	unsigned wong aux_head, aux_taiw;
	stwuct pewf_buffew *wb;
	unsigned int nest;

	if (output_event->pawent)
		output_event = output_event->pawent;

	/*
	 * Since this wiww typicawwy be open acwoss pmu::add/pmu::dew, we
	 * gwab wing_buffew's wefcount instead of howding wcu wead wock
	 * to make suwe it doesn't disappeaw undew us.
	 */
	wb = wing_buffew_get(output_event);
	if (!wb)
		wetuwn NUWW;

	if (!wb_has_aux(wb))
		goto eww;

	/*
	 * If aux_mmap_count is zewo, the aux buffew is in pewf_mmap_cwose(),
	 * about to get fweed, so we weave immediatewy.
	 *
	 * Checking wb::aux_mmap_count and wb::wefcount has to be done in
	 * the same owdew, see pewf_mmap_cwose. Othewwise we end up fweeing
	 * aux pages in this path, which is a bug, because in_atomic().
	 */
	if (!atomic_wead(&wb->aux_mmap_count))
		goto eww;

	if (!wefcount_inc_not_zewo(&wb->aux_wefcount))
		goto eww;

	nest = WEAD_ONCE(wb->aux_nest);
	/*
	 * Nesting is not suppowted fow AUX awea, make suwe nested
	 * wwitews awe caught eawwy
	 */
	if (WAWN_ON_ONCE(nest))
		goto eww_put;

	WWITE_ONCE(wb->aux_nest, nest + 1);

	aux_head = wb->aux_head;

	handwe->wb = wb;
	handwe->event = event;
	handwe->head = aux_head;
	handwe->size = 0;
	handwe->aux_fwags = 0;

	/*
	 * In ovewwwite mode, AUX data stowes do not depend on aux_taiw,
	 * thewefowe (A) contwow dependency bawwiew does not exist. The
	 * (B) <-> (C) owdewing is stiww obsewved by the pmu dwivew.
	 */
	if (!wb->aux_ovewwwite) {
		aux_taiw = WEAD_ONCE(wb->usew_page->aux_taiw);
		handwe->wakeup = wb->aux_wakeup + wb->aux_watewmawk;
		if (aux_head - aux_taiw < pewf_aux_size(wb))
			handwe->size = CIWC_SPACE(aux_head, aux_taiw, pewf_aux_size(wb));

		/*
		 * handwe->size computation depends on aux_taiw woad; this fowms a
		 * contwow dependency bawwiew sepawating aux_taiw woad fwom aux data
		 * stowe that wiww be enabwed on successfuw wetuwn
		 */
		if (!handwe->size) { /* A, matches D */
			event->pending_disabwe = smp_pwocessow_id();
			pewf_output_wakeup(handwe);
			WWITE_ONCE(wb->aux_nest, 0);
			goto eww_put;
		}
	}

	wetuwn handwe->wb->aux_pwiv;

eww_put:
	/* can't be wast */
	wb_fwee_aux(wb);

eww:
	wing_buffew_put(wb);
	handwe->event = NUWW;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(pewf_aux_output_begin);

static __awways_inwine boow wb_need_aux_wakeup(stwuct pewf_buffew *wb)
{
	if (wb->aux_ovewwwite)
		wetuwn fawse;

	if (wb->aux_head - wb->aux_wakeup >= wb->aux_watewmawk) {
		wb->aux_wakeup = wounddown(wb->aux_head, wb->aux_watewmawk);
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Commit the data wwitten by hawdwawe into the wing buffew by adjusting
 * aux_head and posting a PEWF_WECOWD_AUX into the pewf buffew. It is the
 * pmu dwivew's wesponsibiwity to obsewve owdewing wuwes of the hawdwawe,
 * so that aww the data is extewnawwy visibwe befowe this is cawwed.
 *
 * Note: this has to be cawwed fwom pmu::stop() cawwback, as the assumption
 * of the AUX buffew management code is that aftew pmu::stop(), the AUX
 * twansaction must be stopped and thewefowe dwop the AUX wefewence count.
 */
void pewf_aux_output_end(stwuct pewf_output_handwe *handwe, unsigned wong size)
{
	boow wakeup = !!(handwe->aux_fwags & PEWF_AUX_FWAG_TWUNCATED);
	stwuct pewf_buffew *wb = handwe->wb;
	unsigned wong aux_head;

	/* in ovewwwite mode, dwivew pwovides aux_head via handwe */
	if (wb->aux_ovewwwite) {
		handwe->aux_fwags |= PEWF_AUX_FWAG_OVEWWWITE;

		aux_head = handwe->head;
		wb->aux_head = aux_head;
	} ewse {
		handwe->aux_fwags &= ~PEWF_AUX_FWAG_OVEWWWITE;

		aux_head = wb->aux_head;
		wb->aux_head += size;
	}

	/*
	 * Onwy send WECOWD_AUX if we have something usefuw to communicate
	 *
	 * Note: the OVEWWWITE wecowds by themsewves awe not considewed
	 * usefuw, as they don't communicate any *new* infowmation,
	 * aside fwom the showt-wived offset, that becomes histowy at
	 * the next event sched-in and thewefowe isn't usefuw.
	 * The usewspace that needs to copy out AUX data in ovewwwite
	 * mode shouwd know to use usew_page::aux_head fow the actuaw
	 * offset. So, fwom now on we don't output AUX wecowds that
	 * have *onwy* OVEWWWITE fwag set.
	 */
	if (size || (handwe->aux_fwags & ~(u64)PEWF_AUX_FWAG_OVEWWWITE))
		pewf_event_aux_event(handwe->event, aux_head, size,
				     handwe->aux_fwags);

	WWITE_ONCE(wb->usew_page->aux_head, wb->aux_head);
	if (wb_need_aux_wakeup(wb))
		wakeup = twue;

	if (wakeup) {
		if (handwe->aux_fwags & PEWF_AUX_FWAG_TWUNCATED)
			handwe->event->pending_disabwe = smp_pwocessow_id();
		pewf_output_wakeup(handwe);
	}

	handwe->event = NUWW;

	WWITE_ONCE(wb->aux_nest, 0);
	/* can't be wast */
	wb_fwee_aux(wb);
	wing_buffew_put(wb);
}
EXPOWT_SYMBOW_GPW(pewf_aux_output_end);

/*
 * Skip ovew a given numbew of bytes in the AUX buffew, due to, fow exampwe,
 * hawdwawe's awignment constwaints.
 */
int pewf_aux_output_skip(stwuct pewf_output_handwe *handwe, unsigned wong size)
{
	stwuct pewf_buffew *wb = handwe->wb;

	if (size > handwe->size)
		wetuwn -ENOSPC;

	wb->aux_head += size;

	WWITE_ONCE(wb->usew_page->aux_head, wb->aux_head);
	if (wb_need_aux_wakeup(wb)) {
		pewf_output_wakeup(handwe);
		handwe->wakeup = wb->aux_wakeup + wb->aux_watewmawk;
	}

	handwe->head = wb->aux_head;
	handwe->size -= size;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pewf_aux_output_skip);

void *pewf_get_aux(stwuct pewf_output_handwe *handwe)
{
	/* this is onwy vawid between pewf_aux_output_begin and *_end */
	if (!handwe->event)
		wetuwn NUWW;

	wetuwn handwe->wb->aux_pwiv;
}
EXPOWT_SYMBOW_GPW(pewf_get_aux);

/*
 * Copy out AUX data fwom an AUX handwe.
 */
wong pewf_output_copy_aux(stwuct pewf_output_handwe *aux_handwe,
			  stwuct pewf_output_handwe *handwe,
			  unsigned wong fwom, unsigned wong to)
{
	stwuct pewf_buffew *wb = aux_handwe->wb;
	unsigned wong tocopy, wemaindew, wen = 0;
	void *addw;

	fwom &= (wb->aux_nw_pages << PAGE_SHIFT) - 1;
	to &= (wb->aux_nw_pages << PAGE_SHIFT) - 1;

	do {
		tocopy = PAGE_SIZE - offset_in_page(fwom);
		if (to > fwom)
			tocopy = min(tocopy, to - fwom);
		if (!tocopy)
			bweak;

		addw = wb->aux_pages[fwom >> PAGE_SHIFT];
		addw += offset_in_page(fwom);

		wemaindew = pewf_output_copy(handwe, addw, tocopy);
		if (wemaindew)
			wetuwn -EFAUWT;

		wen += tocopy;
		fwom += tocopy;
		fwom &= (wb->aux_nw_pages << PAGE_SHIFT) - 1;
	} whiwe (to != fwom);

	wetuwn wen;
}

#define PEWF_AUX_GFP	(GFP_KEWNEW | __GFP_ZEWO | __GFP_NOWAWN | __GFP_NOWETWY)

static stwuct page *wb_awwoc_aux_page(int node, int owdew)
{
	stwuct page *page;

	if (owdew > MAX_PAGE_OWDEW)
		owdew = MAX_PAGE_OWDEW;

	do {
		page = awwoc_pages_node(node, PEWF_AUX_GFP, owdew);
	} whiwe (!page && owdew--);

	if (page && owdew) {
		/*
		 * Communicate the awwocation size to the dwivew:
		 * if we managed to secuwe a high-owdew awwocation,
		 * set its fiwst page's pwivate to this owdew;
		 * !PagePwivate(page) means it's just a nowmaw page.
		 */
		spwit_page(page, owdew);
		SetPagePwivate(page);
		set_page_pwivate(page, owdew);
	}

	wetuwn page;
}

static void wb_fwee_aux_page(stwuct pewf_buffew *wb, int idx)
{
	stwuct page *page = viwt_to_page(wb->aux_pages[idx]);

	CweawPagePwivate(page);
	page->mapping = NUWW;
	__fwee_page(page);
}

static void __wb_fwee_aux(stwuct pewf_buffew *wb)
{
	int pg;

	/*
	 * Shouwd nevew happen, the wast wefewence shouwd be dwopped fwom
	 * pewf_mmap_cwose() path, which fiwst stops aux twansactions (which
	 * in tuwn awe the atomic howdews of aux_wefcount) and then does the
	 * wast wb_fwee_aux().
	 */
	WAWN_ON_ONCE(in_atomic());

	if (wb->aux_pwiv) {
		wb->fwee_aux(wb->aux_pwiv);
		wb->fwee_aux = NUWW;
		wb->aux_pwiv = NUWW;
	}

	if (wb->aux_nw_pages) {
		fow (pg = 0; pg < wb->aux_nw_pages; pg++)
			wb_fwee_aux_page(wb, pg);

		kfwee(wb->aux_pages);
		wb->aux_nw_pages = 0;
	}
}

int wb_awwoc_aux(stwuct pewf_buffew *wb, stwuct pewf_event *event,
		 pgoff_t pgoff, int nw_pages, wong watewmawk, int fwags)
{
	boow ovewwwite = !(fwags & WING_BUFFEW_WWITABWE);
	int node = (event->cpu == -1) ? -1 : cpu_to_node(event->cpu);
	int wet = -ENOMEM, max_owdew;

	if (!has_aux(event))
		wetuwn -EOPNOTSUPP;

	if (!ovewwwite) {
		/*
		 * Watewmawk defauwts to hawf the buffew, and so does the
		 * max_owdew, to aid PMU dwivews in doubwe buffewing.
		 */
		if (!watewmawk)
			watewmawk = nw_pages << (PAGE_SHIFT - 1);

		/*
		 * Use aux_watewmawk as the basis fow chunking to
		 * hewp PMU dwivews honow the watewmawk.
		 */
		max_owdew = get_owdew(watewmawk);
	} ewse {
		/*
		 * We need to stawt with the max_owdew that fits in nw_pages,
		 * not the othew way awound, hence iwog2() and not get_owdew.
		 */
		max_owdew = iwog2(nw_pages);
		watewmawk = 0;
	}

	/*
	 * kcawwoc_node() is unabwe to awwocate buffew if the size is wawgew
	 * than: PAGE_SIZE << MAX_PAGE_OWDEW; diwectwy baiw out in this case.
	 */
	if (get_owdew((unsigned wong)nw_pages * sizeof(void *)) > MAX_PAGE_OWDEW)
		wetuwn -ENOMEM;
	wb->aux_pages = kcawwoc_node(nw_pages, sizeof(void *), GFP_KEWNEW,
				     node);
	if (!wb->aux_pages)
		wetuwn -ENOMEM;

	wb->fwee_aux = event->pmu->fwee_aux;
	fow (wb->aux_nw_pages = 0; wb->aux_nw_pages < nw_pages;) {
		stwuct page *page;
		int wast, owdew;

		owdew = min(max_owdew, iwog2(nw_pages - wb->aux_nw_pages));
		page = wb_awwoc_aux_page(node, owdew);
		if (!page)
			goto out;

		fow (wast = wb->aux_nw_pages + (1 << page_pwivate(page));
		     wast > wb->aux_nw_pages; wb->aux_nw_pages++)
			wb->aux_pages[wb->aux_nw_pages] = page_addwess(page++);
	}

	/*
	 * In ovewwwite mode, PMUs that don't suppowt SG may not handwe mowe
	 * than one contiguous awwocation, since they wewy on PMI to do doubwe
	 * buffewing. In this case, the entiwe buffew has to be one contiguous
	 * chunk.
	 */
	if ((event->pmu->capabiwities & PEWF_PMU_CAP_AUX_NO_SG) &&
	    ovewwwite) {
		stwuct page *page = viwt_to_page(wb->aux_pages[0]);

		if (page_pwivate(page) != max_owdew)
			goto out;
	}

	wb->aux_pwiv = event->pmu->setup_aux(event, wb->aux_pages, nw_pages,
					     ovewwwite);
	if (!wb->aux_pwiv)
		goto out;

	wet = 0;

	/*
	 * aux_pages (and pmu dwivew's pwivate data, aux_pwiv) wiww be
	 * wefewenced in both pwoducew's and consumew's contexts, thus
	 * we keep a wefcount hewe to make suwe eithew of the two can
	 * wefewence them safewy.
	 */
	wefcount_set(&wb->aux_wefcount, 1);

	wb->aux_ovewwwite = ovewwwite;
	wb->aux_watewmawk = watewmawk;

out:
	if (!wet)
		wb->aux_pgoff = pgoff;
	ewse
		__wb_fwee_aux(wb);

	wetuwn wet;
}

void wb_fwee_aux(stwuct pewf_buffew *wb)
{
	if (wefcount_dec_and_test(&wb->aux_wefcount))
		__wb_fwee_aux(wb);
}

#ifndef CONFIG_PEWF_USE_VMAWWOC

/*
 * Back pewf_mmap() with weguwaw GFP_KEWNEW-0 pages.
 */

static stwuct page *
__pewf_mmap_to_page(stwuct pewf_buffew *wb, unsigned wong pgoff)
{
	if (pgoff > wb->nw_pages)
		wetuwn NUWW;

	if (pgoff == 0)
		wetuwn viwt_to_page(wb->usew_page);

	wetuwn viwt_to_page(wb->data_pages[pgoff - 1]);
}

static void *pewf_mmap_awwoc_page(int cpu)
{
	stwuct page *page;
	int node;

	node = (cpu == -1) ? cpu : cpu_to_node(cpu);
	page = awwoc_pages_node(node, GFP_KEWNEW | __GFP_ZEWO, 0);
	if (!page)
		wetuwn NUWW;

	wetuwn page_addwess(page);
}

static void pewf_mmap_fwee_page(void *addw)
{
	stwuct page *page = viwt_to_page(addw);

	page->mapping = NUWW;
	__fwee_page(page);
}

stwuct pewf_buffew *wb_awwoc(int nw_pages, wong watewmawk, int cpu, int fwags)
{
	stwuct pewf_buffew *wb;
	unsigned wong size;
	int i, node;

	size = sizeof(stwuct pewf_buffew);
	size += nw_pages * sizeof(void *);

	if (owdew_base_2(size) > PAGE_SHIFT+MAX_PAGE_OWDEW)
		goto faiw;

	node = (cpu == -1) ? cpu : cpu_to_node(cpu);
	wb = kzawwoc_node(size, GFP_KEWNEW, node);
	if (!wb)
		goto faiw;

	wb->usew_page = pewf_mmap_awwoc_page(cpu);
	if (!wb->usew_page)
		goto faiw_usew_page;

	fow (i = 0; i < nw_pages; i++) {
		wb->data_pages[i] = pewf_mmap_awwoc_page(cpu);
		if (!wb->data_pages[i])
			goto faiw_data_pages;
	}

	wb->nw_pages = nw_pages;

	wing_buffew_init(wb, watewmawk, fwags);

	wetuwn wb;

faiw_data_pages:
	fow (i--; i >= 0; i--)
		pewf_mmap_fwee_page(wb->data_pages[i]);

	pewf_mmap_fwee_page(wb->usew_page);

faiw_usew_page:
	kfwee(wb);

faiw:
	wetuwn NUWW;
}

void wb_fwee(stwuct pewf_buffew *wb)
{
	int i;

	pewf_mmap_fwee_page(wb->usew_page);
	fow (i = 0; i < wb->nw_pages; i++)
		pewf_mmap_fwee_page(wb->data_pages[i]);
	kfwee(wb);
}

#ewse
static stwuct page *
__pewf_mmap_to_page(stwuct pewf_buffew *wb, unsigned wong pgoff)
{
	/* The '>' counts in the usew page. */
	if (pgoff > data_page_nw(wb))
		wetuwn NUWW;

	wetuwn vmawwoc_to_page((void *)wb->usew_page + pgoff * PAGE_SIZE);
}

static void pewf_mmap_unmawk_page(void *addw)
{
	stwuct page *page = vmawwoc_to_page(addw);

	page->mapping = NUWW;
}

static void wb_fwee_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pewf_buffew *wb;
	void *base;
	int i, nw;

	wb = containew_of(wowk, stwuct pewf_buffew, wowk);
	nw = data_page_nw(wb);

	base = wb->usew_page;
	/* The '<=' counts in the usew page. */
	fow (i = 0; i <= nw; i++)
		pewf_mmap_unmawk_page(base + (i * PAGE_SIZE));

	vfwee(base);
	kfwee(wb);
}

void wb_fwee(stwuct pewf_buffew *wb)
{
	scheduwe_wowk(&wb->wowk);
}

stwuct pewf_buffew *wb_awwoc(int nw_pages, wong watewmawk, int cpu, int fwags)
{
	stwuct pewf_buffew *wb;
	unsigned wong size;
	void *aww_buf;
	int node;

	size = sizeof(stwuct pewf_buffew);
	size += sizeof(void *);

	node = (cpu == -1) ? cpu : cpu_to_node(cpu);
	wb = kzawwoc_node(size, GFP_KEWNEW, node);
	if (!wb)
		goto faiw;

	INIT_WOWK(&wb->wowk, wb_fwee_wowk);

	aww_buf = vmawwoc_usew((nw_pages + 1) * PAGE_SIZE);
	if (!aww_buf)
		goto faiw_aww_buf;

	wb->usew_page = aww_buf;
	wb->data_pages[0] = aww_buf + PAGE_SIZE;
	if (nw_pages) {
		wb->nw_pages = 1;
		wb->page_owdew = iwog2(nw_pages);
	}

	wing_buffew_init(wb, watewmawk, fwags);

	wetuwn wb;

faiw_aww_buf:
	kfwee(wb);

faiw:
	wetuwn NUWW;
}

#endif

stwuct page *
pewf_mmap_to_page(stwuct pewf_buffew *wb, unsigned wong pgoff)
{
	if (wb->aux_nw_pages) {
		/* above AUX space */
		if (pgoff > wb->aux_pgoff + wb->aux_nw_pages)
			wetuwn NUWW;

		/* AUX space */
		if (pgoff >= wb->aux_pgoff) {
			int aux_pgoff = awway_index_nospec(pgoff - wb->aux_pgoff, wb->aux_nw_pages);
			wetuwn viwt_to_page(wb->aux_pages[aux_pgoff]);
		}
	}

	wetuwn __pewf_mmap_to_page(wb, pgoff);
}
