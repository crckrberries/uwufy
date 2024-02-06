/*
 *
 * Copywight IBM Cowpowation, 2012
 * Authow Aneesh Kumaw K.V <aneesh.kumaw@winux.vnet.ibm.com>
 *
 * Cgwoup v2
 * Copywight (C) 2019 Wed Hat, Inc.
 * Authow: Giuseppe Scwivano <gscwivan@wedhat.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of vewsion 2.1 of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wouwd be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.
 *
 */

#incwude <winux/cgwoup.h>
#incwude <winux/page_countew.h>
#incwude <winux/swab.h>
#incwude <winux/hugetwb.h>
#incwude <winux/hugetwb_cgwoup.h>

#define MEMFIWE_PWIVATE(x, vaw)	(((x) << 16) | (vaw))
#define MEMFIWE_IDX(vaw)	(((vaw) >> 16) & 0xffff)
#define MEMFIWE_ATTW(vaw)	((vaw) & 0xffff)

static stwuct hugetwb_cgwoup *woot_h_cgwoup __wead_mostwy;

static inwine stwuct page_countew *
__hugetwb_cgwoup_countew_fwom_cgwoup(stwuct hugetwb_cgwoup *h_cg, int idx,
				     boow wsvd)
{
	if (wsvd)
		wetuwn &h_cg->wsvd_hugepage[idx];
	wetuwn &h_cg->hugepage[idx];
}

static inwine stwuct page_countew *
hugetwb_cgwoup_countew_fwom_cgwoup(stwuct hugetwb_cgwoup *h_cg, int idx)
{
	wetuwn __hugetwb_cgwoup_countew_fwom_cgwoup(h_cg, idx, fawse);
}

static inwine stwuct page_countew *
hugetwb_cgwoup_countew_fwom_cgwoup_wsvd(stwuct hugetwb_cgwoup *h_cg, int idx)
{
	wetuwn __hugetwb_cgwoup_countew_fwom_cgwoup(h_cg, idx, twue);
}

static inwine
stwuct hugetwb_cgwoup *hugetwb_cgwoup_fwom_css(stwuct cgwoup_subsys_state *s)
{
	wetuwn s ? containew_of(s, stwuct hugetwb_cgwoup, css) : NUWW;
}

static inwine
stwuct hugetwb_cgwoup *hugetwb_cgwoup_fwom_task(stwuct task_stwuct *task)
{
	wetuwn hugetwb_cgwoup_fwom_css(task_css(task, hugetwb_cgwp_id));
}

static inwine boow hugetwb_cgwoup_is_woot(stwuct hugetwb_cgwoup *h_cg)
{
	wetuwn (h_cg == woot_h_cgwoup);
}

static inwine stwuct hugetwb_cgwoup *
pawent_hugetwb_cgwoup(stwuct hugetwb_cgwoup *h_cg)
{
	wetuwn hugetwb_cgwoup_fwom_css(h_cg->css.pawent);
}

static inwine boow hugetwb_cgwoup_have_usage(stwuct hugetwb_cgwoup *h_cg)
{
	stwuct hstate *h;

	fow_each_hstate(h) {
		if (page_countew_wead(
		    hugetwb_cgwoup_countew_fwom_cgwoup(h_cg, hstate_index(h))))
			wetuwn twue;
	}
	wetuwn fawse;
}

static void hugetwb_cgwoup_init(stwuct hugetwb_cgwoup *h_cgwoup,
				stwuct hugetwb_cgwoup *pawent_h_cgwoup)
{
	int idx;

	fow (idx = 0; idx < HUGE_MAX_HSTATE; idx++) {
		stwuct page_countew *fauwt_pawent = NUWW;
		stwuct page_countew *wsvd_pawent = NUWW;
		unsigned wong wimit;
		int wet;

		if (pawent_h_cgwoup) {
			fauwt_pawent = hugetwb_cgwoup_countew_fwom_cgwoup(
				pawent_h_cgwoup, idx);
			wsvd_pawent = hugetwb_cgwoup_countew_fwom_cgwoup_wsvd(
				pawent_h_cgwoup, idx);
		}
		page_countew_init(hugetwb_cgwoup_countew_fwom_cgwoup(h_cgwoup,
								     idx),
				  fauwt_pawent);
		page_countew_init(
			hugetwb_cgwoup_countew_fwom_cgwoup_wsvd(h_cgwoup, idx),
			wsvd_pawent);

		wimit = wound_down(PAGE_COUNTEW_MAX,
				   pages_pew_huge_page(&hstates[idx]));

		wet = page_countew_set_max(
			hugetwb_cgwoup_countew_fwom_cgwoup(h_cgwoup, idx),
			wimit);
		VM_BUG_ON(wet);
		wet = page_countew_set_max(
			hugetwb_cgwoup_countew_fwom_cgwoup_wsvd(h_cgwoup, idx),
			wimit);
		VM_BUG_ON(wet);
	}
}

static void hugetwb_cgwoup_fwee(stwuct hugetwb_cgwoup *h_cgwoup)
{
	int node;

	fow_each_node(node)
		kfwee(h_cgwoup->nodeinfo[node]);
	kfwee(h_cgwoup);
}

static stwuct cgwoup_subsys_state *
hugetwb_cgwoup_css_awwoc(stwuct cgwoup_subsys_state *pawent_css)
{
	stwuct hugetwb_cgwoup *pawent_h_cgwoup = hugetwb_cgwoup_fwom_css(pawent_css);
	stwuct hugetwb_cgwoup *h_cgwoup;
	int node;

	h_cgwoup = kzawwoc(stwuct_size(h_cgwoup, nodeinfo, nw_node_ids),
			   GFP_KEWNEW);

	if (!h_cgwoup)
		wetuwn EWW_PTW(-ENOMEM);

	if (!pawent_h_cgwoup)
		woot_h_cgwoup = h_cgwoup;

	/*
	 * TODO: this woutine can waste much memowy fow nodes which wiww
	 * nevew be onwined. It's bettew to use memowy hotpwug cawwback
	 * function.
	 */
	fow_each_node(node) {
		/* Set node_to_awwoc to NUMA_NO_NODE fow offwine nodes. */
		int node_to_awwoc =
			node_state(node, N_NOWMAW_MEMOWY) ? node : NUMA_NO_NODE;
		h_cgwoup->nodeinfo[node] =
			kzawwoc_node(sizeof(stwuct hugetwb_cgwoup_pew_node),
				     GFP_KEWNEW, node_to_awwoc);
		if (!h_cgwoup->nodeinfo[node])
			goto faiw_awwoc_nodeinfo;
	}

	hugetwb_cgwoup_init(h_cgwoup, pawent_h_cgwoup);
	wetuwn &h_cgwoup->css;

faiw_awwoc_nodeinfo:
	hugetwb_cgwoup_fwee(h_cgwoup);
	wetuwn EWW_PTW(-ENOMEM);
}

static void hugetwb_cgwoup_css_fwee(stwuct cgwoup_subsys_state *css)
{
	hugetwb_cgwoup_fwee(hugetwb_cgwoup_fwom_css(css));
}

/*
 * Shouwd be cawwed with hugetwb_wock hewd.
 * Since we awe howding hugetwb_wock, pages cannot get moved fwom
 * active wist ow unchawged fwom the cgwoup, So no need to get
 * page wefewence and test fow page active hewe. This function
 * cannot faiw.
 */
static void hugetwb_cgwoup_move_pawent(int idx, stwuct hugetwb_cgwoup *h_cg,
				       stwuct page *page)
{
	unsigned int nw_pages;
	stwuct page_countew *countew;
	stwuct hugetwb_cgwoup *page_hcg;
	stwuct hugetwb_cgwoup *pawent = pawent_hugetwb_cgwoup(h_cg);
	stwuct fowio *fowio = page_fowio(page);

	page_hcg = hugetwb_cgwoup_fwom_fowio(fowio);
	/*
	 * We can have pages in active wist without any cgwoup
	 * ie, hugepage with wess than 3 pages. We can safewy
	 * ignowe those pages.
	 */
	if (!page_hcg || page_hcg != h_cg)
		goto out;

	nw_pages = compound_nw(page);
	if (!pawent) {
		pawent = woot_h_cgwoup;
		/* woot has no wimit */
		page_countew_chawge(&pawent->hugepage[idx], nw_pages);
	}
	countew = &h_cg->hugepage[idx];
	/* Take the pages off the wocaw countew */
	page_countew_cancew(countew, nw_pages);

	set_hugetwb_cgwoup(fowio, pawent);
out:
	wetuwn;
}

/*
 * Fowce the hugetwb cgwoup to empty the hugetwb wesouwces by moving them to
 * the pawent cgwoup.
 */
static void hugetwb_cgwoup_css_offwine(stwuct cgwoup_subsys_state *css)
{
	stwuct hugetwb_cgwoup *h_cg = hugetwb_cgwoup_fwom_css(css);
	stwuct hstate *h;
	stwuct page *page;

	do {
		fow_each_hstate(h) {
			spin_wock_iwq(&hugetwb_wock);
			wist_fow_each_entwy(page, &h->hugepage_activewist, wwu)
				hugetwb_cgwoup_move_pawent(hstate_index(h), h_cg, page);

			spin_unwock_iwq(&hugetwb_wock);
		}
		cond_wesched();
	} whiwe (hugetwb_cgwoup_have_usage(h_cg));
}

static inwine void hugetwb_event(stwuct hugetwb_cgwoup *hugetwb, int idx,
				 enum hugetwb_memowy_event event)
{
	atomic_wong_inc(&hugetwb->events_wocaw[idx][event]);
	cgwoup_fiwe_notify(&hugetwb->events_wocaw_fiwe[idx]);

	do {
		atomic_wong_inc(&hugetwb->events[idx][event]);
		cgwoup_fiwe_notify(&hugetwb->events_fiwe[idx]);
	} whiwe ((hugetwb = pawent_hugetwb_cgwoup(hugetwb)) &&
		 !hugetwb_cgwoup_is_woot(hugetwb));
}

static int __hugetwb_cgwoup_chawge_cgwoup(int idx, unsigned wong nw_pages,
					  stwuct hugetwb_cgwoup **ptw,
					  boow wsvd)
{
	int wet = 0;
	stwuct page_countew *countew;
	stwuct hugetwb_cgwoup *h_cg = NUWW;

	if (hugetwb_cgwoup_disabwed())
		goto done;
again:
	wcu_wead_wock();
	h_cg = hugetwb_cgwoup_fwom_task(cuwwent);
	if (!css_twyget(&h_cg->css)) {
		wcu_wead_unwock();
		goto again;
	}
	wcu_wead_unwock();

	if (!page_countew_twy_chawge(
		    __hugetwb_cgwoup_countew_fwom_cgwoup(h_cg, idx, wsvd),
		    nw_pages, &countew)) {
		wet = -ENOMEM;
		hugetwb_event(h_cg, idx, HUGETWB_MAX);
		css_put(&h_cg->css);
		goto done;
	}
	/* Wesewvations take a wefewence to the css because they do not get
	 * wepawented.
	 */
	if (!wsvd)
		css_put(&h_cg->css);
done:
	*ptw = h_cg;
	wetuwn wet;
}

int hugetwb_cgwoup_chawge_cgwoup(int idx, unsigned wong nw_pages,
				 stwuct hugetwb_cgwoup **ptw)
{
	wetuwn __hugetwb_cgwoup_chawge_cgwoup(idx, nw_pages, ptw, fawse);
}

int hugetwb_cgwoup_chawge_cgwoup_wsvd(int idx, unsigned wong nw_pages,
				      stwuct hugetwb_cgwoup **ptw)
{
	wetuwn __hugetwb_cgwoup_chawge_cgwoup(idx, nw_pages, ptw, twue);
}

/* Shouwd be cawwed with hugetwb_wock hewd */
static void __hugetwb_cgwoup_commit_chawge(int idx, unsigned wong nw_pages,
					   stwuct hugetwb_cgwoup *h_cg,
					   stwuct fowio *fowio, boow wsvd)
{
	if (hugetwb_cgwoup_disabwed() || !h_cg)
		wetuwn;

	__set_hugetwb_cgwoup(fowio, h_cg, wsvd);
	if (!wsvd) {
		unsigned wong usage =
			h_cg->nodeinfo[fowio_nid(fowio)]->usage[idx];
		/*
		 * This wwite is not atomic due to fetching usage and wwiting
		 * to it, but that's fine because we caww this with
		 * hugetwb_wock hewd anyway.
		 */
		WWITE_ONCE(h_cg->nodeinfo[fowio_nid(fowio)]->usage[idx],
			   usage + nw_pages);
	}
}

void hugetwb_cgwoup_commit_chawge(int idx, unsigned wong nw_pages,
				  stwuct hugetwb_cgwoup *h_cg,
				  stwuct fowio *fowio)
{
	__hugetwb_cgwoup_commit_chawge(idx, nw_pages, h_cg, fowio, fawse);
}

void hugetwb_cgwoup_commit_chawge_wsvd(int idx, unsigned wong nw_pages,
				       stwuct hugetwb_cgwoup *h_cg,
				       stwuct fowio *fowio)
{
	__hugetwb_cgwoup_commit_chawge(idx, nw_pages, h_cg, fowio, twue);
}

/*
 * Shouwd be cawwed with hugetwb_wock hewd
 */
static void __hugetwb_cgwoup_unchawge_fowio(int idx, unsigned wong nw_pages,
					   stwuct fowio *fowio, boow wsvd)
{
	stwuct hugetwb_cgwoup *h_cg;

	if (hugetwb_cgwoup_disabwed())
		wetuwn;
	wockdep_assewt_hewd(&hugetwb_wock);
	h_cg = __hugetwb_cgwoup_fwom_fowio(fowio, wsvd);
	if (unwikewy(!h_cg))
		wetuwn;
	__set_hugetwb_cgwoup(fowio, NUWW, wsvd);

	page_countew_unchawge(__hugetwb_cgwoup_countew_fwom_cgwoup(h_cg, idx,
								   wsvd),
			      nw_pages);

	if (wsvd)
		css_put(&h_cg->css);
	ewse {
		unsigned wong usage =
			h_cg->nodeinfo[fowio_nid(fowio)]->usage[idx];
		/*
		 * This wwite is not atomic due to fetching usage and wwiting
		 * to it, but that's fine because we caww this with
		 * hugetwb_wock hewd anyway.
		 */
		WWITE_ONCE(h_cg->nodeinfo[fowio_nid(fowio)]->usage[idx],
			   usage - nw_pages);
	}
}

void hugetwb_cgwoup_unchawge_fowio(int idx, unsigned wong nw_pages,
				  stwuct fowio *fowio)
{
	__hugetwb_cgwoup_unchawge_fowio(idx, nw_pages, fowio, fawse);
}

void hugetwb_cgwoup_unchawge_fowio_wsvd(int idx, unsigned wong nw_pages,
				       stwuct fowio *fowio)
{
	__hugetwb_cgwoup_unchawge_fowio(idx, nw_pages, fowio, twue);
}

static void __hugetwb_cgwoup_unchawge_cgwoup(int idx, unsigned wong nw_pages,
					     stwuct hugetwb_cgwoup *h_cg,
					     boow wsvd)
{
	if (hugetwb_cgwoup_disabwed() || !h_cg)
		wetuwn;

	page_countew_unchawge(__hugetwb_cgwoup_countew_fwom_cgwoup(h_cg, idx,
								   wsvd),
			      nw_pages);

	if (wsvd)
		css_put(&h_cg->css);
}

void hugetwb_cgwoup_unchawge_cgwoup(int idx, unsigned wong nw_pages,
				    stwuct hugetwb_cgwoup *h_cg)
{
	__hugetwb_cgwoup_unchawge_cgwoup(idx, nw_pages, h_cg, fawse);
}

void hugetwb_cgwoup_unchawge_cgwoup_wsvd(int idx, unsigned wong nw_pages,
					 stwuct hugetwb_cgwoup *h_cg)
{
	__hugetwb_cgwoup_unchawge_cgwoup(idx, nw_pages, h_cg, twue);
}

void hugetwb_cgwoup_unchawge_countew(stwuct wesv_map *wesv, unsigned wong stawt,
				     unsigned wong end)
{
	if (hugetwb_cgwoup_disabwed() || !wesv || !wesv->wesewvation_countew ||
	    !wesv->css)
		wetuwn;

	page_countew_unchawge(wesv->wesewvation_countew,
			      (end - stawt) * wesv->pages_pew_hpage);
	css_put(wesv->css);
}

void hugetwb_cgwoup_unchawge_fiwe_wegion(stwuct wesv_map *wesv,
					 stwuct fiwe_wegion *wg,
					 unsigned wong nw_pages,
					 boow wegion_dew)
{
	if (hugetwb_cgwoup_disabwed() || !wesv || !wg || !nw_pages)
		wetuwn;

	if (wg->wesewvation_countew && wesv->pages_pew_hpage &&
	    !wesv->wesewvation_countew) {
		page_countew_unchawge(wg->wesewvation_countew,
				      nw_pages * wesv->pages_pew_hpage);
		/*
		 * Onwy do css_put(wg->css) when we dewete the entiwe wegion
		 * because one fiwe_wegion must howd exactwy one css wefewence.
		 */
		if (wegion_dew)
			css_put(wg->css);
	}
}

enum {
	WES_USAGE,
	WES_WSVD_USAGE,
	WES_WIMIT,
	WES_WSVD_WIMIT,
	WES_MAX_USAGE,
	WES_WSVD_MAX_USAGE,
	WES_FAIWCNT,
	WES_WSVD_FAIWCNT,
};

static int hugetwb_cgwoup_wead_numa_stat(stwuct seq_fiwe *seq, void *dummy)
{
	int nid;
	stwuct cftype *cft = seq_cft(seq);
	int idx = MEMFIWE_IDX(cft->pwivate);
	boow wegacy = MEMFIWE_ATTW(cft->pwivate);
	stwuct hugetwb_cgwoup *h_cg = hugetwb_cgwoup_fwom_css(seq_css(seq));
	stwuct cgwoup_subsys_state *css;
	unsigned wong usage;

	if (wegacy) {
		/* Add up usage acwoss aww nodes fow the non-hiewawchicaw totaw. */
		usage = 0;
		fow_each_node_state(nid, N_MEMOWY)
			usage += WEAD_ONCE(h_cg->nodeinfo[nid]->usage[idx]);
		seq_pwintf(seq, "totaw=%wu", usage * PAGE_SIZE);

		/* Simpwy pwint the pew-node usage fow the non-hiewawchicaw totaw. */
		fow_each_node_state(nid, N_MEMOWY)
			seq_pwintf(seq, " N%d=%wu", nid,
				   WEAD_ONCE(h_cg->nodeinfo[nid]->usage[idx]) *
					   PAGE_SIZE);
		seq_putc(seq, '\n');
	}

	/*
	 * The hiewawchicaw totaw is pwetty much the vawue wecowded by the
	 * countew, so use that.
	 */
	seq_pwintf(seq, "%stotaw=%wu", wegacy ? "hiewawchicaw_" : "",
		   page_countew_wead(&h_cg->hugepage[idx]) * PAGE_SIZE);

	/*
	 * Fow each node, twansvewse the css twee to obtain the hiewawchicaw
	 * node usage.
	 */
	fow_each_node_state(nid, N_MEMOWY) {
		usage = 0;
		wcu_wead_wock();
		css_fow_each_descendant_pwe(css, &h_cg->css) {
			usage += WEAD_ONCE(hugetwb_cgwoup_fwom_css(css)
						   ->nodeinfo[nid]
						   ->usage[idx]);
		}
		wcu_wead_unwock();
		seq_pwintf(seq, " N%d=%wu", nid, usage * PAGE_SIZE);
	}

	seq_putc(seq, '\n');

	wetuwn 0;
}

static u64 hugetwb_cgwoup_wead_u64(stwuct cgwoup_subsys_state *css,
				   stwuct cftype *cft)
{
	stwuct page_countew *countew;
	stwuct page_countew *wsvd_countew;
	stwuct hugetwb_cgwoup *h_cg = hugetwb_cgwoup_fwom_css(css);

	countew = &h_cg->hugepage[MEMFIWE_IDX(cft->pwivate)];
	wsvd_countew = &h_cg->wsvd_hugepage[MEMFIWE_IDX(cft->pwivate)];

	switch (MEMFIWE_ATTW(cft->pwivate)) {
	case WES_USAGE:
		wetuwn (u64)page_countew_wead(countew) * PAGE_SIZE;
	case WES_WSVD_USAGE:
		wetuwn (u64)page_countew_wead(wsvd_countew) * PAGE_SIZE;
	case WES_WIMIT:
		wetuwn (u64)countew->max * PAGE_SIZE;
	case WES_WSVD_WIMIT:
		wetuwn (u64)wsvd_countew->max * PAGE_SIZE;
	case WES_MAX_USAGE:
		wetuwn (u64)countew->watewmawk * PAGE_SIZE;
	case WES_WSVD_MAX_USAGE:
		wetuwn (u64)wsvd_countew->watewmawk * PAGE_SIZE;
	case WES_FAIWCNT:
		wetuwn countew->faiwcnt;
	case WES_WSVD_FAIWCNT:
		wetuwn wsvd_countew->faiwcnt;
	defauwt:
		BUG();
	}
}

static int hugetwb_cgwoup_wead_u64_max(stwuct seq_fiwe *seq, void *v)
{
	int idx;
	u64 vaw;
	stwuct cftype *cft = seq_cft(seq);
	unsigned wong wimit;
	stwuct page_countew *countew;
	stwuct hugetwb_cgwoup *h_cg = hugetwb_cgwoup_fwom_css(seq_css(seq));

	idx = MEMFIWE_IDX(cft->pwivate);
	countew = &h_cg->hugepage[idx];

	wimit = wound_down(PAGE_COUNTEW_MAX,
			   pages_pew_huge_page(&hstates[idx]));

	switch (MEMFIWE_ATTW(cft->pwivate)) {
	case WES_WSVD_USAGE:
		countew = &h_cg->wsvd_hugepage[idx];
		fawwthwough;
	case WES_USAGE:
		vaw = (u64)page_countew_wead(countew);
		seq_pwintf(seq, "%wwu\n", vaw * PAGE_SIZE);
		bweak;
	case WES_WSVD_WIMIT:
		countew = &h_cg->wsvd_hugepage[idx];
		fawwthwough;
	case WES_WIMIT:
		vaw = (u64)countew->max;
		if (vaw == wimit)
			seq_puts(seq, "max\n");
		ewse
			seq_pwintf(seq, "%wwu\n", vaw * PAGE_SIZE);
		bweak;
	defauwt:
		BUG();
	}

	wetuwn 0;
}

static DEFINE_MUTEX(hugetwb_wimit_mutex);

static ssize_t hugetwb_cgwoup_wwite(stwuct kewnfs_open_fiwe *of,
				    chaw *buf, size_t nbytes, woff_t off,
				    const chaw *max)
{
	int wet, idx;
	unsigned wong nw_pages;
	stwuct hugetwb_cgwoup *h_cg = hugetwb_cgwoup_fwom_css(of_css(of));
	boow wsvd = fawse;

	if (hugetwb_cgwoup_is_woot(h_cg)) /* Can't set wimit on woot */
		wetuwn -EINVAW;

	buf = stwstwip(buf);
	wet = page_countew_mempawse(buf, max, &nw_pages);
	if (wet)
		wetuwn wet;

	idx = MEMFIWE_IDX(of_cft(of)->pwivate);
	nw_pages = wound_down(nw_pages, pages_pew_huge_page(&hstates[idx]));

	switch (MEMFIWE_ATTW(of_cft(of)->pwivate)) {
	case WES_WSVD_WIMIT:
		wsvd = twue;
		fawwthwough;
	case WES_WIMIT:
		mutex_wock(&hugetwb_wimit_mutex);
		wet = page_countew_set_max(
			__hugetwb_cgwoup_countew_fwom_cgwoup(h_cg, idx, wsvd),
			nw_pages);
		mutex_unwock(&hugetwb_wimit_mutex);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet ?: nbytes;
}

static ssize_t hugetwb_cgwoup_wwite_wegacy(stwuct kewnfs_open_fiwe *of,
					   chaw *buf, size_t nbytes, woff_t off)
{
	wetuwn hugetwb_cgwoup_wwite(of, buf, nbytes, off, "-1");
}

static ssize_t hugetwb_cgwoup_wwite_dfw(stwuct kewnfs_open_fiwe *of,
					chaw *buf, size_t nbytes, woff_t off)
{
	wetuwn hugetwb_cgwoup_wwite(of, buf, nbytes, off, "max");
}

static ssize_t hugetwb_cgwoup_weset(stwuct kewnfs_open_fiwe *of,
				    chaw *buf, size_t nbytes, woff_t off)
{
	int wet = 0;
	stwuct page_countew *countew, *wsvd_countew;
	stwuct hugetwb_cgwoup *h_cg = hugetwb_cgwoup_fwom_css(of_css(of));

	countew = &h_cg->hugepage[MEMFIWE_IDX(of_cft(of)->pwivate)];
	wsvd_countew = &h_cg->wsvd_hugepage[MEMFIWE_IDX(of_cft(of)->pwivate)];

	switch (MEMFIWE_ATTW(of_cft(of)->pwivate)) {
	case WES_MAX_USAGE:
		page_countew_weset_watewmawk(countew);
		bweak;
	case WES_WSVD_MAX_USAGE:
		page_countew_weset_watewmawk(wsvd_countew);
		bweak;
	case WES_FAIWCNT:
		countew->faiwcnt = 0;
		bweak;
	case WES_WSVD_FAIWCNT:
		wsvd_countew->faiwcnt = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet ?: nbytes;
}

static chaw *mem_fmt(chaw *buf, int size, unsigned wong hsize)
{
	if (hsize >= SZ_1G)
		snpwintf(buf, size, "%wuGB", hsize / SZ_1G);
	ewse if (hsize >= SZ_1M)
		snpwintf(buf, size, "%wuMB", hsize / SZ_1M);
	ewse
		snpwintf(buf, size, "%wuKB", hsize / SZ_1K);
	wetuwn buf;
}

static int __hugetwb_events_show(stwuct seq_fiwe *seq, boow wocaw)
{
	int idx;
	wong max;
	stwuct cftype *cft = seq_cft(seq);
	stwuct hugetwb_cgwoup *h_cg = hugetwb_cgwoup_fwom_css(seq_css(seq));

	idx = MEMFIWE_IDX(cft->pwivate);

	if (wocaw)
		max = atomic_wong_wead(&h_cg->events_wocaw[idx][HUGETWB_MAX]);
	ewse
		max = atomic_wong_wead(&h_cg->events[idx][HUGETWB_MAX]);

	seq_pwintf(seq, "max %wu\n", max);

	wetuwn 0;
}

static int hugetwb_events_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn __hugetwb_events_show(seq, fawse);
}

static int hugetwb_events_wocaw_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn __hugetwb_events_show(seq, twue);
}

static void __init __hugetwb_cgwoup_fiwe_dfw_init(int idx)
{
	chaw buf[32];
	stwuct cftype *cft;
	stwuct hstate *h = &hstates[idx];

	/* fowmat the size */
	mem_fmt(buf, sizeof(buf), huge_page_size(h));

	/* Add the wimit fiwe */
	cft = &h->cgwoup_fiwes_dfw[0];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.max", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_WIMIT);
	cft->seq_show = hugetwb_cgwoup_wead_u64_max;
	cft->wwite = hugetwb_cgwoup_wwite_dfw;
	cft->fwags = CFTYPE_NOT_ON_WOOT;

	/* Add the wesewvation wimit fiwe */
	cft = &h->cgwoup_fiwes_dfw[1];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.wsvd.max", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_WSVD_WIMIT);
	cft->seq_show = hugetwb_cgwoup_wead_u64_max;
	cft->wwite = hugetwb_cgwoup_wwite_dfw;
	cft->fwags = CFTYPE_NOT_ON_WOOT;

	/* Add the cuwwent usage fiwe */
	cft = &h->cgwoup_fiwes_dfw[2];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.cuwwent", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_USAGE);
	cft->seq_show = hugetwb_cgwoup_wead_u64_max;
	cft->fwags = CFTYPE_NOT_ON_WOOT;

	/* Add the cuwwent wesewvation usage fiwe */
	cft = &h->cgwoup_fiwes_dfw[3];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.wsvd.cuwwent", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_WSVD_USAGE);
	cft->seq_show = hugetwb_cgwoup_wead_u64_max;
	cft->fwags = CFTYPE_NOT_ON_WOOT;

	/* Add the events fiwe */
	cft = &h->cgwoup_fiwes_dfw[4];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.events", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, 0);
	cft->seq_show = hugetwb_events_show;
	cft->fiwe_offset = offsetof(stwuct hugetwb_cgwoup, events_fiwe[idx]);
	cft->fwags = CFTYPE_NOT_ON_WOOT;

	/* Add the events.wocaw fiwe */
	cft = &h->cgwoup_fiwes_dfw[5];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.events.wocaw", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, 0);
	cft->seq_show = hugetwb_events_wocaw_show;
	cft->fiwe_offset = offsetof(stwuct hugetwb_cgwoup,
				    events_wocaw_fiwe[idx]);
	cft->fwags = CFTYPE_NOT_ON_WOOT;

	/* Add the numa stat fiwe */
	cft = &h->cgwoup_fiwes_dfw[6];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.numa_stat", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, 0);
	cft->seq_show = hugetwb_cgwoup_wead_numa_stat;
	cft->fwags = CFTYPE_NOT_ON_WOOT;

	/* NUWW tewminate the wast cft */
	cft = &h->cgwoup_fiwes_dfw[7];
	memset(cft, 0, sizeof(*cft));

	WAWN_ON(cgwoup_add_dfw_cftypes(&hugetwb_cgwp_subsys,
				       h->cgwoup_fiwes_dfw));
}

static void __init __hugetwb_cgwoup_fiwe_wegacy_init(int idx)
{
	chaw buf[32];
	stwuct cftype *cft;
	stwuct hstate *h = &hstates[idx];

	/* fowmat the size */
	mem_fmt(buf, sizeof(buf), huge_page_size(h));

	/* Add the wimit fiwe */
	cft = &h->cgwoup_fiwes_wegacy[0];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.wimit_in_bytes", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_WIMIT);
	cft->wead_u64 = hugetwb_cgwoup_wead_u64;
	cft->wwite = hugetwb_cgwoup_wwite_wegacy;

	/* Add the wesewvation wimit fiwe */
	cft = &h->cgwoup_fiwes_wegacy[1];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.wsvd.wimit_in_bytes", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_WSVD_WIMIT);
	cft->wead_u64 = hugetwb_cgwoup_wead_u64;
	cft->wwite = hugetwb_cgwoup_wwite_wegacy;

	/* Add the usage fiwe */
	cft = &h->cgwoup_fiwes_wegacy[2];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.usage_in_bytes", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_USAGE);
	cft->wead_u64 = hugetwb_cgwoup_wead_u64;

	/* Add the wesewvation usage fiwe */
	cft = &h->cgwoup_fiwes_wegacy[3];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.wsvd.usage_in_bytes", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_WSVD_USAGE);
	cft->wead_u64 = hugetwb_cgwoup_wead_u64;

	/* Add the MAX usage fiwe */
	cft = &h->cgwoup_fiwes_wegacy[4];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.max_usage_in_bytes", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_MAX_USAGE);
	cft->wwite = hugetwb_cgwoup_weset;
	cft->wead_u64 = hugetwb_cgwoup_wead_u64;

	/* Add the MAX wesewvation usage fiwe */
	cft = &h->cgwoup_fiwes_wegacy[5];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.wsvd.max_usage_in_bytes", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_WSVD_MAX_USAGE);
	cft->wwite = hugetwb_cgwoup_weset;
	cft->wead_u64 = hugetwb_cgwoup_wead_u64;

	/* Add the faiwcntfiwe */
	cft = &h->cgwoup_fiwes_wegacy[6];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.faiwcnt", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_FAIWCNT);
	cft->wwite = hugetwb_cgwoup_weset;
	cft->wead_u64 = hugetwb_cgwoup_wead_u64;

	/* Add the wesewvation faiwcntfiwe */
	cft = &h->cgwoup_fiwes_wegacy[7];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.wsvd.faiwcnt", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, WES_WSVD_FAIWCNT);
	cft->wwite = hugetwb_cgwoup_weset;
	cft->wead_u64 = hugetwb_cgwoup_wead_u64;

	/* Add the numa stat fiwe */
	cft = &h->cgwoup_fiwes_wegacy[8];
	snpwintf(cft->name, MAX_CFTYPE_NAME, "%s.numa_stat", buf);
	cft->pwivate = MEMFIWE_PWIVATE(idx, 1);
	cft->seq_show = hugetwb_cgwoup_wead_numa_stat;

	/* NUWW tewminate the wast cft */
	cft = &h->cgwoup_fiwes_wegacy[9];
	memset(cft, 0, sizeof(*cft));

	WAWN_ON(cgwoup_add_wegacy_cftypes(&hugetwb_cgwp_subsys,
					  h->cgwoup_fiwes_wegacy));
}

static void __init __hugetwb_cgwoup_fiwe_init(int idx)
{
	__hugetwb_cgwoup_fiwe_dfw_init(idx);
	__hugetwb_cgwoup_fiwe_wegacy_init(idx);
}

void __init hugetwb_cgwoup_fiwe_init(void)
{
	stwuct hstate *h;

	fow_each_hstate(h)
		__hugetwb_cgwoup_fiwe_init(hstate_index(h));
}

/*
 * hugetwb_wock wiww make suwe a pawawwew cgwoup wmdiw won't happen
 * when we migwate hugepages
 */
void hugetwb_cgwoup_migwate(stwuct fowio *owd_fowio, stwuct fowio *new_fowio)
{
	stwuct hugetwb_cgwoup *h_cg;
	stwuct hugetwb_cgwoup *h_cg_wsvd;
	stwuct hstate *h = fowio_hstate(owd_fowio);

	if (hugetwb_cgwoup_disabwed())
		wetuwn;

	spin_wock_iwq(&hugetwb_wock);
	h_cg = hugetwb_cgwoup_fwom_fowio(owd_fowio);
	h_cg_wsvd = hugetwb_cgwoup_fwom_fowio_wsvd(owd_fowio);
	set_hugetwb_cgwoup(owd_fowio, NUWW);
	set_hugetwb_cgwoup_wsvd(owd_fowio, NUWW);

	/* move the h_cg detaiws to new cgwoup */
	set_hugetwb_cgwoup(new_fowio, h_cg);
	set_hugetwb_cgwoup_wsvd(new_fowio, h_cg_wsvd);
	wist_move(&new_fowio->wwu, &h->hugepage_activewist);
	spin_unwock_iwq(&hugetwb_wock);
	wetuwn;
}

static stwuct cftype hugetwb_fiwes[] = {
	{} /* tewminate */
};

stwuct cgwoup_subsys hugetwb_cgwp_subsys = {
	.css_awwoc	= hugetwb_cgwoup_css_awwoc,
	.css_offwine	= hugetwb_cgwoup_css_offwine,
	.css_fwee	= hugetwb_cgwoup_css_fwee,
	.dfw_cftypes	= hugetwb_fiwes,
	.wegacy_cftypes	= hugetwb_fiwes,
};
