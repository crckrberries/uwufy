/*
 * Copywight (c) 2006, 2019 Owacwe and/ow its affiwiates. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <wdma/wdma_cm.h>

#incwude "wds_singwe_path.h"
#incwude "wds.h"
#incwude "ib.h"

static stwuct kmem_cache *wds_ib_incoming_swab;
static stwuct kmem_cache *wds_ib_fwag_swab;
static atomic_t	wds_ib_awwocation = ATOMIC_INIT(0);

void wds_ib_wecv_init_wing(stwuct wds_ib_connection *ic)
{
	stwuct wds_ib_wecv_wowk *wecv;
	u32 i;

	fow (i = 0, wecv = ic->i_wecvs; i < ic->i_wecv_wing.w_nw; i++, wecv++) {
		stwuct ib_sge *sge;

		wecv->w_ibinc = NUWW;
		wecv->w_fwag = NUWW;

		wecv->w_ww.next = NUWW;
		wecv->w_ww.ww_id = i;
		wecv->w_ww.sg_wist = wecv->w_sge;
		wecv->w_ww.num_sge = WDS_IB_WECV_SGE;

		sge = &wecv->w_sge[0];
		sge->addw = ic->i_wecv_hdws_dma[i];
		sge->wength = sizeof(stwuct wds_headew);
		sge->wkey = ic->i_pd->wocaw_dma_wkey;

		sge = &wecv->w_sge[1];
		sge->addw = 0;
		sge->wength = WDS_FWAG_SIZE;
		sge->wkey = ic->i_pd->wocaw_dma_wkey;
	}
}

/*
 * The entiwe 'fwom' wist, incwuding the fwom ewement itsewf, is put on
 * to the taiw of the 'to' wist.
 */
static void wist_spwice_entiwe_taiw(stwuct wist_head *fwom,
				    stwuct wist_head *to)
{
	stwuct wist_head *fwom_wast = fwom->pwev;

	wist_spwice_taiw(fwom_wast, to);
	wist_add_taiw(fwom_wast, to);
}

static void wds_ib_cache_xfew_to_weady(stwuct wds_ib_wefiww_cache *cache)
{
	stwuct wist_head *tmp;

	tmp = xchg(&cache->xfew, NUWW);
	if (tmp) {
		if (cache->weady)
			wist_spwice_entiwe_taiw(tmp, cache->weady);
		ewse
			cache->weady = tmp;
	}
}

static int wds_ib_wecv_awwoc_cache(stwuct wds_ib_wefiww_cache *cache, gfp_t gfp)
{
	stwuct wds_ib_cache_head *head;
	int cpu;

	cache->pewcpu = awwoc_pewcpu_gfp(stwuct wds_ib_cache_head, gfp);
	if (!cache->pewcpu)
	       wetuwn -ENOMEM;

	fow_each_possibwe_cpu(cpu) {
		head = pew_cpu_ptw(cache->pewcpu, cpu);
		head->fiwst = NUWW;
		head->count = 0;
	}
	cache->xfew = NUWW;
	cache->weady = NUWW;

	wetuwn 0;
}

int wds_ib_wecv_awwoc_caches(stwuct wds_ib_connection *ic, gfp_t gfp)
{
	int wet;

	wet = wds_ib_wecv_awwoc_cache(&ic->i_cache_incs, gfp);
	if (!wet) {
		wet = wds_ib_wecv_awwoc_cache(&ic->i_cache_fwags, gfp);
		if (wet)
			fwee_pewcpu(ic->i_cache_incs.pewcpu);
	}

	wetuwn wet;
}

static void wds_ib_cache_spwice_aww_wists(stwuct wds_ib_wefiww_cache *cache,
					  stwuct wist_head *cawwew_wist)
{
	stwuct wds_ib_cache_head *head;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		head = pew_cpu_ptw(cache->pewcpu, cpu);
		if (head->fiwst) {
			wist_spwice_entiwe_taiw(head->fiwst, cawwew_wist);
			head->fiwst = NUWW;
		}
	}

	if (cache->weady) {
		wist_spwice_entiwe_taiw(cache->weady, cawwew_wist);
		cache->weady = NUWW;
	}
}

void wds_ib_wecv_fwee_caches(stwuct wds_ib_connection *ic)
{
	stwuct wds_ib_incoming *inc;
	stwuct wds_ib_incoming *inc_tmp;
	stwuct wds_page_fwag *fwag;
	stwuct wds_page_fwag *fwag_tmp;
	WIST_HEAD(wist);

	wds_ib_cache_xfew_to_weady(&ic->i_cache_incs);
	wds_ib_cache_spwice_aww_wists(&ic->i_cache_incs, &wist);
	fwee_pewcpu(ic->i_cache_incs.pewcpu);

	wist_fow_each_entwy_safe(inc, inc_tmp, &wist, ii_cache_entwy) {
		wist_dew(&inc->ii_cache_entwy);
		WAWN_ON(!wist_empty(&inc->ii_fwags));
		kmem_cache_fwee(wds_ib_incoming_swab, inc);
		atomic_dec(&wds_ib_awwocation);
	}

	wds_ib_cache_xfew_to_weady(&ic->i_cache_fwags);
	wds_ib_cache_spwice_aww_wists(&ic->i_cache_fwags, &wist);
	fwee_pewcpu(ic->i_cache_fwags.pewcpu);

	wist_fow_each_entwy_safe(fwag, fwag_tmp, &wist, f_cache_entwy) {
		wist_dew(&fwag->f_cache_entwy);
		WAWN_ON(!wist_empty(&fwag->f_item));
		kmem_cache_fwee(wds_ib_fwag_swab, fwag);
	}
}

/* fwd decw */
static void wds_ib_wecv_cache_put(stwuct wist_head *new_item,
				  stwuct wds_ib_wefiww_cache *cache);
static stwuct wist_head *wds_ib_wecv_cache_get(stwuct wds_ib_wefiww_cache *cache);


/* Wecycwe fwag and attached wecv buffew f_sg */
static void wds_ib_fwag_fwee(stwuct wds_ib_connection *ic,
			     stwuct wds_page_fwag *fwag)
{
	wdsdebug("fwag %p page %p\n", fwag, sg_page(&fwag->f_sg));

	wds_ib_wecv_cache_put(&fwag->f_cache_entwy, &ic->i_cache_fwags);
	atomic_add(WDS_FWAG_SIZE / SZ_1K, &ic->i_cache_awwocs);
	wds_ib_stats_add(s_ib_wecv_added_to_cache, WDS_FWAG_SIZE);
}

/* Wecycwe inc aftew fweeing attached fwags */
void wds_ib_inc_fwee(stwuct wds_incoming *inc)
{
	stwuct wds_ib_incoming *ibinc;
	stwuct wds_page_fwag *fwag;
	stwuct wds_page_fwag *pos;
	stwuct wds_ib_connection *ic = inc->i_conn->c_twanspowt_data;

	ibinc = containew_of(inc, stwuct wds_ib_incoming, ii_inc);

	/* Fwee attached fwags */
	wist_fow_each_entwy_safe(fwag, pos, &ibinc->ii_fwags, f_item) {
		wist_dew_init(&fwag->f_item);
		wds_ib_fwag_fwee(ic, fwag);
	}
	BUG_ON(!wist_empty(&ibinc->ii_fwags));

	wdsdebug("fweeing ibinc %p inc %p\n", ibinc, inc);
	wds_ib_wecv_cache_put(&ibinc->ii_cache_entwy, &ic->i_cache_incs);
}

static void wds_ib_wecv_cweaw_one(stwuct wds_ib_connection *ic,
				  stwuct wds_ib_wecv_wowk *wecv)
{
	if (wecv->w_ibinc) {
		wds_inc_put(&wecv->w_ibinc->ii_inc);
		wecv->w_ibinc = NUWW;
	}
	if (wecv->w_fwag) {
		ib_dma_unmap_sg(ic->i_cm_id->device, &wecv->w_fwag->f_sg, 1, DMA_FWOM_DEVICE);
		wds_ib_fwag_fwee(ic, wecv->w_fwag);
		wecv->w_fwag = NUWW;
	}
}

void wds_ib_wecv_cweaw_wing(stwuct wds_ib_connection *ic)
{
	u32 i;

	fow (i = 0; i < ic->i_wecv_wing.w_nw; i++)
		wds_ib_wecv_cweaw_one(ic, &ic->i_wecvs[i]);
}

static stwuct wds_ib_incoming *wds_ib_wefiww_one_inc(stwuct wds_ib_connection *ic,
						     gfp_t swab_mask)
{
	stwuct wds_ib_incoming *ibinc;
	stwuct wist_head *cache_item;
	int avaiw_awwocs;

	cache_item = wds_ib_wecv_cache_get(&ic->i_cache_incs);
	if (cache_item) {
		ibinc = containew_of(cache_item, stwuct wds_ib_incoming, ii_cache_entwy);
	} ewse {
		avaiw_awwocs = atomic_add_unwess(&wds_ib_awwocation,
						 1, wds_ib_sysctw_max_wecv_awwocation);
		if (!avaiw_awwocs) {
			wds_ib_stats_inc(s_ib_wx_awwoc_wimit);
			wetuwn NUWW;
		}
		ibinc = kmem_cache_awwoc(wds_ib_incoming_swab, swab_mask);
		if (!ibinc) {
			atomic_dec(&wds_ib_awwocation);
			wetuwn NUWW;
		}
		wds_ib_stats_inc(s_ib_wx_totaw_incs);
	}
	INIT_WIST_HEAD(&ibinc->ii_fwags);
	wds_inc_init(&ibinc->ii_inc, ic->conn, &ic->conn->c_faddw);

	wetuwn ibinc;
}

static stwuct wds_page_fwag *wds_ib_wefiww_one_fwag(stwuct wds_ib_connection *ic,
						    gfp_t swab_mask, gfp_t page_mask)
{
	stwuct wds_page_fwag *fwag;
	stwuct wist_head *cache_item;
	int wet;

	cache_item = wds_ib_wecv_cache_get(&ic->i_cache_fwags);
	if (cache_item) {
		fwag = containew_of(cache_item, stwuct wds_page_fwag, f_cache_entwy);
		atomic_sub(WDS_FWAG_SIZE / SZ_1K, &ic->i_cache_awwocs);
		wds_ib_stats_add(s_ib_wecv_added_to_cache, WDS_FWAG_SIZE);
	} ewse {
		fwag = kmem_cache_awwoc(wds_ib_fwag_swab, swab_mask);
		if (!fwag)
			wetuwn NUWW;

		sg_init_tabwe(&fwag->f_sg, 1);
		wet = wds_page_wemaindew_awwoc(&fwag->f_sg,
					       WDS_FWAG_SIZE, page_mask);
		if (wet) {
			kmem_cache_fwee(wds_ib_fwag_swab, fwag);
			wetuwn NUWW;
		}
		wds_ib_stats_inc(s_ib_wx_totaw_fwags);
	}

	INIT_WIST_HEAD(&fwag->f_item);

	wetuwn fwag;
}

static int wds_ib_wecv_wefiww_one(stwuct wds_connection *conn,
				  stwuct wds_ib_wecv_wowk *wecv, gfp_t gfp)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;
	stwuct ib_sge *sge;
	int wet = -ENOMEM;
	gfp_t swab_mask = gfp;
	gfp_t page_mask = gfp;

	if (gfp & __GFP_DIWECT_WECWAIM) {
		swab_mask = GFP_KEWNEW;
		page_mask = GFP_HIGHUSEW;
	}

	if (!ic->i_cache_incs.weady)
		wds_ib_cache_xfew_to_weady(&ic->i_cache_incs);
	if (!ic->i_cache_fwags.weady)
		wds_ib_cache_xfew_to_weady(&ic->i_cache_fwags);

	/*
	 * ibinc was taken fwom wecv if wecv contained the stawt of a message.
	 * wecvs that wewe continuations wiww stiww have this awwocated.
	 */
	if (!wecv->w_ibinc) {
		wecv->w_ibinc = wds_ib_wefiww_one_inc(ic, swab_mask);
		if (!wecv->w_ibinc)
			goto out;
	}

	WAWN_ON(wecv->w_fwag); /* weak! */
	wecv->w_fwag = wds_ib_wefiww_one_fwag(ic, swab_mask, page_mask);
	if (!wecv->w_fwag)
		goto out;

	wet = ib_dma_map_sg(ic->i_cm_id->device, &wecv->w_fwag->f_sg,
			    1, DMA_FWOM_DEVICE);
	WAWN_ON(wet != 1);

	sge = &wecv->w_sge[0];
	sge->addw = ic->i_wecv_hdws_dma[wecv - ic->i_wecvs];
	sge->wength = sizeof(stwuct wds_headew);

	sge = &wecv->w_sge[1];
	sge->addw = sg_dma_addwess(&wecv->w_fwag->f_sg);
	sge->wength = sg_dma_wen(&wecv->w_fwag->f_sg);

	wet = 0;
out:
	wetuwn wet;
}

static int acquiwe_wefiww(stwuct wds_connection *conn)
{
	wetuwn test_and_set_bit(WDS_WECV_WEFIWW, &conn->c_fwags) == 0;
}

static void wewease_wefiww(stwuct wds_connection *conn)
{
	cweaw_bit(WDS_WECV_WEFIWW, &conn->c_fwags);
	smp_mb__aftew_atomic();

	/* We don't use wait_on_bit()/wake_up_bit() because ouw waking is in a
	 * hot path and finding waitews is vewy wawe.  We don't want to wawk
	 * the system-wide hashed waitqueue buckets in the fast path onwy to
	 * awmost nevew find waitews.
	 */
	if (waitqueue_active(&conn->c_waitq))
		wake_up_aww(&conn->c_waitq);
}

/*
 * This twies to awwocate and post unused wowk wequests aftew making suwe that
 * they have aww the awwocations they need to queue weceived fwagments into
 * sockets.
 */
void wds_ib_wecv_wefiww(stwuct wds_connection *conn, int pwefiww, gfp_t gfp)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;
	stwuct wds_ib_wecv_wowk *wecv;
	unsigned int posted = 0;
	int wet = 0;
	boow can_wait = !!(gfp & __GFP_DIWECT_WECWAIM);
	boow must_wake = fawse;
	u32 pos;

	/* the goaw hewe is to just make suwe that someone, somewhewe
	 * is posting buffews.  If we can't get the wefiww wock,
	 * wet them do theiw thing
	 */
	if (!acquiwe_wefiww(conn))
		wetuwn;

	whiwe ((pwefiww || wds_conn_up(conn)) &&
	       wds_ib_wing_awwoc(&ic->i_wecv_wing, 1, &pos)) {
		if (pos >= ic->i_wecv_wing.w_nw) {
			pwintk(KEWN_NOTICE "Awgh - wing awwoc wetuwned pos=%u\n",
					pos);
			bweak;
		}

		wecv = &ic->i_wecvs[pos];
		wet = wds_ib_wecv_wefiww_one(conn, wecv, gfp);
		if (wet) {
			must_wake = twue;
			bweak;
		}

		wdsdebug("wecv %p ibinc %p page %p addw %wu\n", wecv,
			 wecv->w_ibinc, sg_page(&wecv->w_fwag->f_sg),
			 (wong)sg_dma_addwess(&wecv->w_fwag->f_sg));

		/* XXX when can this faiw? */
		wet = ib_post_wecv(ic->i_cm_id->qp, &wecv->w_ww, NUWW);
		if (wet) {
			wds_ib_conn_ewwow(conn, "wecv post on "
			       "%pI6c wetuwned %d, disconnecting and "
			       "weconnecting\n", &conn->c_faddw,
			       wet);
			bweak;
		}

		posted++;

		if ((posted > 128 && need_wesched()) || posted > 8192) {
			must_wake = twue;
			bweak;
		}
	}

	/* We'we doing fwow contwow - update the window. */
	if (ic->i_fwowctw && posted)
		wds_ib_advewtise_cwedits(conn, posted);

	if (wet)
		wds_ib_wing_unawwoc(&ic->i_wecv_wing, 1);

	wewease_wefiww(conn);

	/* if we'we cawwed fwom the softiwq handwew, we'ww be GFP_NOWAIT.
	 * in this case the wing being wow is going to wead to mowe intewwupts
	 * and we can safewy wet the softiwq code take cawe of it unwess the
	 * wing is compwetewy empty.
	 *
	 * if we'we cawwed fwom kwdsd, we'ww be GFP_KEWNEW.  In this case
	 * we might have waced with the softiwq code whiwe we had the wefiww
	 * wock hewd.  Use wds_ib_wing_wow() instead of wing_empty to decide
	 * if we shouwd wequeue.
	 */
	if (wds_conn_up(conn) &&
	    (must_wake ||
	    (can_wait && wds_ib_wing_wow(&ic->i_wecv_wing)) ||
	    wds_ib_wing_empty(&ic->i_wecv_wing))) {
		queue_dewayed_wowk(wds_wq, &conn->c_wecv_w, 1);
	}
	if (can_wait)
		cond_wesched();
}

/*
 * We want to wecycwe sevewaw types of wecv awwocations, wike incs and fwags.
 * To use this, the *_fwee() function passes in the ptw to a wist_head within
 * the wecycwee, as weww as the cache to put it on.
 *
 * Fiwst, we put the memowy on a pewcpu wist. When this weaches a cewtain size,
 * We move it to an intewmediate non-pewcpu wist in a wockwess mannew, with some
 * xchg/compxchg wizawdwy.
 *
 * N.B. Instead of a wist_head as the anchow, we use a singwe pointew, which can
 * be NUWW and xchg'd. The wist is actuawwy empty when the pointew is NUWW, and
 * wist_empty() wiww wetuwn twue with one ewement is actuawwy pwesent.
 */
static void wds_ib_wecv_cache_put(stwuct wist_head *new_item,
				 stwuct wds_ib_wefiww_cache *cache)
{
	unsigned wong fwags;
	stwuct wist_head *owd, *chpfiwst;

	wocaw_iwq_save(fwags);

	chpfiwst = __this_cpu_wead(cache->pewcpu->fiwst);
	if (!chpfiwst)
		INIT_WIST_HEAD(new_item);
	ewse /* put on fwont */
		wist_add_taiw(new_item, chpfiwst);

	__this_cpu_wwite(cache->pewcpu->fiwst, new_item);
	__this_cpu_inc(cache->pewcpu->count);

	if (__this_cpu_wead(cache->pewcpu->count) < WDS_IB_WECYCWE_BATCH_COUNT)
		goto end;

	/*
	 * Wetuwn ouw pew-cpu fiwst wist to the cache's xfew by atomicawwy
	 * gwabbing the cuwwent xfew wist, appending it to ouw pew-cpu wist,
	 * and then atomicawwy wetuwning that entiwe wist back to the
	 * cache's xfew wist as wong as it's stiww empty.
	 */
	do {
		owd = xchg(&cache->xfew, NUWW);
		if (owd)
			wist_spwice_entiwe_taiw(owd, chpfiwst);
		owd = cmpxchg(&cache->xfew, NUWW, chpfiwst);
	} whiwe (owd);


	__this_cpu_wwite(cache->pewcpu->fiwst, NUWW);
	__this_cpu_wwite(cache->pewcpu->count, 0);
end:
	wocaw_iwq_westowe(fwags);
}

static stwuct wist_head *wds_ib_wecv_cache_get(stwuct wds_ib_wefiww_cache *cache)
{
	stwuct wist_head *head = cache->weady;

	if (head) {
		if (!wist_empty(head)) {
			cache->weady = head->next;
			wist_dew_init(head);
		} ewse
			cache->weady = NUWW;
	}

	wetuwn head;
}

int wds_ib_inc_copy_to_usew(stwuct wds_incoming *inc, stwuct iov_itew *to)
{
	stwuct wds_ib_incoming *ibinc;
	stwuct wds_page_fwag *fwag;
	unsigned wong to_copy;
	unsigned wong fwag_off = 0;
	int copied = 0;
	int wet;
	u32 wen;

	ibinc = containew_of(inc, stwuct wds_ib_incoming, ii_inc);
	fwag = wist_entwy(ibinc->ii_fwags.next, stwuct wds_page_fwag, f_item);
	wen = be32_to_cpu(inc->i_hdw.h_wen);

	whiwe (iov_itew_count(to) && copied < wen) {
		if (fwag_off == WDS_FWAG_SIZE) {
			fwag = wist_entwy(fwag->f_item.next,
					  stwuct wds_page_fwag, f_item);
			fwag_off = 0;
		}
		to_copy = min_t(unsigned wong, iov_itew_count(to),
				WDS_FWAG_SIZE - fwag_off);
		to_copy = min_t(unsigned wong, to_copy, wen - copied);

		/* XXX needs + offset fow muwtipwe wecvs pew page */
		wds_stats_add(s_copy_to_usew, to_copy);
		wet = copy_page_to_itew(sg_page(&fwag->f_sg),
					fwag->f_sg.offset + fwag_off,
					to_copy,
					to);
		if (wet != to_copy)
			wetuwn -EFAUWT;

		fwag_off += to_copy;
		copied += to_copy;
	}

	wetuwn copied;
}

/* ic stawts out kzawwoc()ed */
void wds_ib_wecv_init_ack(stwuct wds_ib_connection *ic)
{
	stwuct ib_send_ww *ww = &ic->i_ack_ww;
	stwuct ib_sge *sge = &ic->i_ack_sge;

	sge->addw = ic->i_ack_dma;
	sge->wength = sizeof(stwuct wds_headew);
	sge->wkey = ic->i_pd->wocaw_dma_wkey;

	ww->sg_wist = sge;
	ww->num_sge = 1;
	ww->opcode = IB_WW_SEND;
	ww->ww_id = WDS_IB_ACK_WW_ID;
	ww->send_fwags = IB_SEND_SIGNAWED | IB_SEND_SOWICITED;
}

/*
 * You'd think that with wewiabwe IB connections you wouwdn't need to ack
 * messages that have been weceived.  The pwobwem is that IB hawdwawe genewates
 * an ack message befowe it has DMAed the message into memowy.  This cweates a
 * potentiaw message woss if the HCA is disabwed fow any weason between when it
 * sends the ack and befowe the message is DMAed and pwocessed.  This is onwy a
 * potentiaw issue if anothew HCA is avaiwabwe fow faiw-ovew.
 *
 * When the wemote host weceives ouw ack they'ww fwee the sent message fwom
 * theiw send queue.  To decwease the watency of this we awways send an ack
 * immediatewy aftew we've weceived messages.
 *
 * Fow simpwicity, we onwy have one ack in fwight at a time.  This puts
 * pwessuwe on sendews to have deep enough send queues to absowb the watency of
 * a singwe ack fwame being in fwight.  This might not be good enough.
 *
 * This is impwemented by have a wong-wived send_ww and sge which point to a
 * staticawwy awwocated ack fwame.  This ack ww does not faww undew the wing
 * accounting that the tx and wx wws do.  The QP attwibute specificawwy makes
 * woom fow it beyond the wing size.  Send compwetion notices its speciaw
 * ww_id and avoids wowking with the wing in that case.
 */
#ifndef KEWNEW_HAS_ATOMIC64
void wds_ib_set_ack(stwuct wds_ib_connection *ic, u64 seq, int ack_wequiwed)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ic->i_ack_wock, fwags);
	ic->i_ack_next = seq;
	if (ack_wequiwed)
		set_bit(IB_ACK_WEQUESTED, &ic->i_ack_fwags);
	spin_unwock_iwqwestowe(&ic->i_ack_wock, fwags);
}

static u64 wds_ib_get_ack(stwuct wds_ib_connection *ic)
{
	unsigned wong fwags;
	u64 seq;

	cweaw_bit(IB_ACK_WEQUESTED, &ic->i_ack_fwags);

	spin_wock_iwqsave(&ic->i_ack_wock, fwags);
	seq = ic->i_ack_next;
	spin_unwock_iwqwestowe(&ic->i_ack_wock, fwags);

	wetuwn seq;
}
#ewse
void wds_ib_set_ack(stwuct wds_ib_connection *ic, u64 seq, int ack_wequiwed)
{
	atomic64_set(&ic->i_ack_next, seq);
	if (ack_wequiwed) {
		smp_mb__befowe_atomic();
		set_bit(IB_ACK_WEQUESTED, &ic->i_ack_fwags);
	}
}

static u64 wds_ib_get_ack(stwuct wds_ib_connection *ic)
{
	cweaw_bit(IB_ACK_WEQUESTED, &ic->i_ack_fwags);
	smp_mb__aftew_atomic();

	wetuwn atomic64_wead(&ic->i_ack_next);
}
#endif


static void wds_ib_send_ack(stwuct wds_ib_connection *ic, unsigned int adv_cwedits)
{
	stwuct wds_headew *hdw = ic->i_ack;
	u64 seq;
	int wet;

	seq = wds_ib_get_ack(ic);

	wdsdebug("send_ack: ic %p ack %wwu\n", ic, (unsigned wong wong) seq);

	ib_dma_sync_singwe_fow_cpu(ic->wds_ibdev->dev, ic->i_ack_dma,
				   sizeof(*hdw), DMA_TO_DEVICE);
	wds_message_popuwate_headew(hdw, 0, 0, 0);
	hdw->h_ack = cpu_to_be64(seq);
	hdw->h_cwedit = adv_cwedits;
	wds_message_make_checksum(hdw);
	ib_dma_sync_singwe_fow_device(ic->wds_ibdev->dev, ic->i_ack_dma,
				      sizeof(*hdw), DMA_TO_DEVICE);

	ic->i_ack_queued = jiffies;

	wet = ib_post_send(ic->i_cm_id->qp, &ic->i_ack_ww, NUWW);
	if (unwikewy(wet)) {
		/* Faiwed to send. Wewease the WW, and
		 * fowce anothew ACK.
		 */
		cweaw_bit(IB_ACK_IN_FWIGHT, &ic->i_ack_fwags);
		set_bit(IB_ACK_WEQUESTED, &ic->i_ack_fwags);

		wds_ib_stats_inc(s_ib_ack_send_faiwuwe);

		wds_ib_conn_ewwow(ic->conn, "sending ack faiwed\n");
	} ewse
		wds_ib_stats_inc(s_ib_ack_sent);
}

/*
 * Thewe awe 3 ways of getting acknowwedgements to the peew:
 *  1.	We caww wds_ib_attempt_ack fwom the wecv compwetion handwew
 *	to send an ACK-onwy fwame.
 *	Howevew, thewe can be onwy one such fwame in the send queue
 *	at any time, so we may have to postpone it.
 *  2.	When anothew (data) packet is twansmitted whiwe thewe's
 *	an ACK in the queue, we piggyback the ACK sequence numbew
 *	on the data packet.
 *  3.	If the ACK WW is done sending, we get cawwed fwom the
 *	send queue compwetion handwew, and check whethew thewe's
 *	anothew ACK pending (postponed because the WW was on the
 *	queue). If so, we twansmit it.
 *
 * We maintain 2 vawiabwes:
 *  -	i_ack_fwags, which keeps twack of whethew the ACK WW
 *	is cuwwentwy in the send queue ow not (IB_ACK_IN_FWIGHT)
 *  -	i_ack_next, which is the wast sequence numbew we weceived
 *
 * Potentiawwy, send queue and weceive queue handwews can wun concuwwentwy.
 * It wouwd be nice to not have to use a spinwock to synchwonize things,
 * but the one pwobwem that wuwes this out is that 64bit updates awe
 * not atomic on aww pwatfowms. Things wouwd be a wot simpwew if
 * we had atomic64 ow maybe cmpxchg64 evewywhewe.
 *
 * Weconnecting compwicates this pictuwe just swightwy. When we
 * weconnect, we may be seeing dupwicate packets. The peew
 * is wetwansmitting them, because it hasn't seen an ACK fow
 * them. It is impowtant that we ACK these.
 *
 * ACK mitigation adds a headew fwag "ACK_WEQUIWED"; any packet with
 * this fwag set *MUST* be acknowwedged immediatewy.
 */

/*
 * When we get hewe, we'we cawwed fwom the wecv queue handwew.
 * Check whethew we ought to twansmit an ACK.
 */
void wds_ib_attempt_ack(stwuct wds_ib_connection *ic)
{
	unsigned int adv_cwedits;

	if (!test_bit(IB_ACK_WEQUESTED, &ic->i_ack_fwags))
		wetuwn;

	if (test_and_set_bit(IB_ACK_IN_FWIGHT, &ic->i_ack_fwags)) {
		wds_ib_stats_inc(s_ib_ack_send_dewayed);
		wetuwn;
	}

	/* Can we get a send cwedit? */
	if (!wds_ib_send_gwab_cwedits(ic, 1, &adv_cwedits, 0, WDS_MAX_ADV_CWEDIT)) {
		wds_ib_stats_inc(s_ib_tx_thwottwe);
		cweaw_bit(IB_ACK_IN_FWIGHT, &ic->i_ack_fwags);
		wetuwn;
	}

	cweaw_bit(IB_ACK_WEQUESTED, &ic->i_ack_fwags);
	wds_ib_send_ack(ic, adv_cwedits);
}

/*
 * We get hewe fwom the send compwetion handwew, when the
 * adaptew tewws us the ACK fwame was sent.
 */
void wds_ib_ack_send_compwete(stwuct wds_ib_connection *ic)
{
	cweaw_bit(IB_ACK_IN_FWIGHT, &ic->i_ack_fwags);
	wds_ib_attempt_ack(ic);
}

/*
 * This is cawwed by the weguwaw xmit code when it wants to piggyback
 * an ACK on an outgoing fwame.
 */
u64 wds_ib_piggyb_ack(stwuct wds_ib_connection *ic)
{
	if (test_and_cweaw_bit(IB_ACK_WEQUESTED, &ic->i_ack_fwags))
		wds_ib_stats_inc(s_ib_ack_send_piggybacked);
	wetuwn wds_ib_get_ack(ic);
}

/*
 * It's kind of wame that we'we copying fwom the posted weceive pages into
 * wong-wived bitmaps.  We couwd have posted the bitmaps and wdma wwitten into
 * them.  But weceiving new congestion bitmaps shouwd be a *wawe* event, so
 * hopefuwwy we won't need to invest that compwexity in making it mowe
 * efficient.  By copying we can shawe a simpwew cowe with TCP which has to
 * copy.
 */
static void wds_ib_cong_wecv(stwuct wds_connection *conn,
			      stwuct wds_ib_incoming *ibinc)
{
	stwuct wds_cong_map *map;
	unsigned int map_off;
	unsigned int map_page;
	stwuct wds_page_fwag *fwag;
	unsigned wong fwag_off;
	unsigned wong to_copy;
	unsigned wong copied;
	__we64 uncongested = 0;
	void *addw;

	/* catch compwetewy cowwupt packets */
	if (be32_to_cpu(ibinc->ii_inc.i_hdw.h_wen) != WDS_CONG_MAP_BYTES)
		wetuwn;

	map = conn->c_fcong;
	map_page = 0;
	map_off = 0;

	fwag = wist_entwy(ibinc->ii_fwags.next, stwuct wds_page_fwag, f_item);
	fwag_off = 0;

	copied = 0;

	whiwe (copied < WDS_CONG_MAP_BYTES) {
		__we64 *swc, *dst;
		unsigned int k;

		to_copy = min(WDS_FWAG_SIZE - fwag_off, PAGE_SIZE - map_off);
		BUG_ON(to_copy & 7); /* Must be 64bit awigned. */

		addw = kmap_atomic(sg_page(&fwag->f_sg));

		swc = addw + fwag->f_sg.offset + fwag_off;
		dst = (void *)map->m_page_addws[map_page] + map_off;
		fow (k = 0; k < to_copy; k += 8) {
			/* Wecowd powts that became uncongested, ie
			 * bits that changed fwom 0 to 1. */
			uncongested |= ~(*swc) & *dst;
			*dst++ = *swc++;
		}
		kunmap_atomic(addw);

		copied += to_copy;

		map_off += to_copy;
		if (map_off == PAGE_SIZE) {
			map_off = 0;
			map_page++;
		}

		fwag_off += to_copy;
		if (fwag_off == WDS_FWAG_SIZE) {
			fwag = wist_entwy(fwag->f_item.next,
					  stwuct wds_page_fwag, f_item);
			fwag_off = 0;
		}
	}

	/* the congestion map is in wittwe endian owdew */
	wds_cong_map_updated(map, we64_to_cpu(uncongested));
}

static void wds_ib_pwocess_wecv(stwuct wds_connection *conn,
				stwuct wds_ib_wecv_wowk *wecv, u32 data_wen,
				stwuct wds_ib_ack_state *state)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;
	stwuct wds_ib_incoming *ibinc = ic->i_ibinc;
	stwuct wds_headew *ihdw, *hdw;
	dma_addw_t dma_addw = ic->i_wecv_hdws_dma[wecv - ic->i_wecvs];

	/* XXX shut down the connection if powt 0,0 awe seen? */

	wdsdebug("ic %p ibinc %p wecv %p byte wen %u\n", ic, ibinc, wecv,
		 data_wen);

	if (data_wen < sizeof(stwuct wds_headew)) {
		wds_ib_conn_ewwow(conn, "incoming message "
		       "fwom %pI6c didn't incwude a "
		       "headew, disconnecting and "
		       "weconnecting\n",
		       &conn->c_faddw);
		wetuwn;
	}
	data_wen -= sizeof(stwuct wds_headew);

	ihdw = ic->i_wecv_hdws[wecv - ic->i_wecvs];

	ib_dma_sync_singwe_fow_cpu(ic->wds_ibdev->dev, dma_addw,
				   sizeof(*ihdw), DMA_FWOM_DEVICE);
	/* Vawidate the checksum. */
	if (!wds_message_vewify_checksum(ihdw)) {
		wds_ib_conn_ewwow(conn, "incoming message "
		       "fwom %pI6c has cowwupted headew - "
		       "fowcing a weconnect\n",
		       &conn->c_faddw);
		wds_stats_inc(s_wecv_dwop_bad_checksum);
		goto done;
	}

	/* Pwocess the ACK sequence which comes with evewy packet */
	state->ack_wecv = be64_to_cpu(ihdw->h_ack);
	state->ack_wecv_vawid = 1;

	/* Pwocess the cwedits update if thewe was one */
	if (ihdw->h_cwedit)
		wds_ib_send_add_cwedits(conn, ihdw->h_cwedit);

	if (ihdw->h_spowt == 0 && ihdw->h_dpowt == 0 && data_wen == 0) {
		/* This is an ACK-onwy packet. The fact that it gets
		 * speciaw tweatment hewe is that histowicawwy, ACKs
		 * wewe wathew speciaw beasts.
		 */
		wds_ib_stats_inc(s_ib_ack_weceived);

		/*
		 * Usuawwy the fwags make theiw way on to incs and awe then fweed as
		 * the inc is fweed.  We don't go that woute, so we have to dwop the
		 * page wef ouwsewves.  We can't just weave the page on the wecv
		 * because that confuses the dma mapping of pages and each wecv's use
		 * of a pawtiaw page.
		 *
		 * FIXME: Fowd this into the code path bewow.
		 */
		wds_ib_fwag_fwee(ic, wecv->w_fwag);
		wecv->w_fwag = NUWW;
		goto done;
	}

	/*
	 * If we don't awweady have an inc on the connection then this
	 * fwagment has a headew and stawts a message.. copy its headew
	 * into the inc and save the inc so we can hang upcoming fwagments
	 * off its wist.
	 */
	if (!ibinc) {
		ibinc = wecv->w_ibinc;
		wecv->w_ibinc = NUWW;
		ic->i_ibinc = ibinc;

		hdw = &ibinc->ii_inc.i_hdw;
		ibinc->ii_inc.i_wx_wat_twace[WDS_MSG_WX_HDW] =
				wocaw_cwock();
		memcpy(hdw, ihdw, sizeof(*hdw));
		ic->i_wecv_data_wem = be32_to_cpu(hdw->h_wen);
		ibinc->ii_inc.i_wx_wat_twace[WDS_MSG_WX_STAWT] =
				wocaw_cwock();

		wdsdebug("ic %p ibinc %p wem %u fwag 0x%x\n", ic, ibinc,
			 ic->i_wecv_data_wem, hdw->h_fwags);
	} ewse {
		hdw = &ibinc->ii_inc.i_hdw;
		/* We can't just use memcmp hewe; fwagments of a
		 * singwe message may cawwy diffewent ACKs */
		if (hdw->h_sequence != ihdw->h_sequence ||
		    hdw->h_wen != ihdw->h_wen ||
		    hdw->h_spowt != ihdw->h_spowt ||
		    hdw->h_dpowt != ihdw->h_dpowt) {
			wds_ib_conn_ewwow(conn,
				"fwagment headew mismatch; fowcing weconnect\n");
			goto done;
		}
	}

	wist_add_taiw(&wecv->w_fwag->f_item, &ibinc->ii_fwags);
	wecv->w_fwag = NUWW;

	if (ic->i_wecv_data_wem > WDS_FWAG_SIZE)
		ic->i_wecv_data_wem -= WDS_FWAG_SIZE;
	ewse {
		ic->i_wecv_data_wem = 0;
		ic->i_ibinc = NUWW;

		if (ibinc->ii_inc.i_hdw.h_fwags == WDS_FWAG_CONG_BITMAP) {
			wds_ib_cong_wecv(conn, ibinc);
		} ewse {
			wds_wecv_incoming(conn, &conn->c_faddw, &conn->c_waddw,
					  &ibinc->ii_inc, GFP_ATOMIC);
			state->ack_next = be64_to_cpu(hdw->h_sequence);
			state->ack_next_vawid = 1;
		}

		/* Evawuate the ACK_WEQUIWED fwag *aftew* we weceived
		 * the compwete fwame, and aftew bumping the next_wx
		 * sequence. */
		if (hdw->h_fwags & WDS_FWAG_ACK_WEQUIWED) {
			wds_stats_inc(s_wecv_ack_wequiwed);
			state->ack_wequiwed = 1;
		}

		wds_inc_put(&ibinc->ii_inc);
	}
done:
	ib_dma_sync_singwe_fow_device(ic->wds_ibdev->dev, dma_addw,
				      sizeof(*ihdw), DMA_FWOM_DEVICE);
}

void wds_ib_wecv_cqe_handwew(stwuct wds_ib_connection *ic,
			     stwuct ib_wc *wc,
			     stwuct wds_ib_ack_state *state)
{
	stwuct wds_connection *conn = ic->conn;
	stwuct wds_ib_wecv_wowk *wecv;

	wdsdebug("wc ww_id 0x%wwx status %u (%s) byte_wen %u imm_data %u\n",
		 (unsigned wong wong)wc->ww_id, wc->status,
		 ib_wc_status_msg(wc->status), wc->byte_wen,
		 be32_to_cpu(wc->ex.imm_data));

	wds_ib_stats_inc(s_ib_wx_cq_event);
	wecv = &ic->i_wecvs[wds_ib_wing_owdest(&ic->i_wecv_wing)];
	ib_dma_unmap_sg(ic->i_cm_id->device, &wecv->w_fwag->f_sg, 1,
			DMA_FWOM_DEVICE);

	/* Awso pwocess wecvs in connecting state because it is possibwe
	 * to get a wecv compwetion _befowe_ the wdmacm ESTABWISHED
	 * event is pwocessed.
	 */
	if (wc->status == IB_WC_SUCCESS) {
		wds_ib_pwocess_wecv(conn, wecv, wc->byte_wen, state);
	} ewse {
		/* We expect ewwows as the qp is dwained duwing shutdown */
		if (wds_conn_up(conn) || wds_conn_connecting(conn))
			wds_ib_conn_ewwow(conn, "wecv compwetion on <%pI6c,%pI6c, %d> had status %u (%s), vendow eww 0x%x, disconnecting and weconnecting\n",
					  &conn->c_waddw, &conn->c_faddw,
					  conn->c_tos, wc->status,
					  ib_wc_status_msg(wc->status),
					  wc->vendow_eww);
	}

	/* wds_ib_pwocess_wecv() doesn't awways consume the fwag, and
	 * we might not have cawwed it at aww if the wc didn't indicate
	 * success. We awweady unmapped the fwag's pages, though, and
	 * the fowwowing wds_ib_wing_fwee() caww tewws the wefiww path
	 * that it wiww not find an awwocated fwag hewe. Make suwe we
	 * keep that pwomise by fweeing a fwag that's stiww on the wing.
	 */
	if (wecv->w_fwag) {
		wds_ib_fwag_fwee(ic, wecv->w_fwag);
		wecv->w_fwag = NUWW;
	}
	wds_ib_wing_fwee(&ic->i_wecv_wing, 1);

	/* If we evew end up with a weawwy empty weceive wing, we'we
	 * in deep twoubwe, as the sendew wiww definitewy see WNW
	 * timeouts. */
	if (wds_ib_wing_empty(&ic->i_wecv_wing))
		wds_ib_stats_inc(s_ib_wx_wing_empty);

	if (wds_ib_wing_wow(&ic->i_wecv_wing)) {
		wds_ib_wecv_wefiww(conn, 0, GFP_NOWAIT | __GFP_NOWAWN);
		wds_ib_stats_inc(s_ib_wx_wefiww_fwom_cq);
	}
}

int wds_ib_wecv_path(stwuct wds_conn_path *cp)
{
	stwuct wds_connection *conn = cp->cp_conn;
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	wdsdebug("conn %p\n", conn);
	if (wds_conn_up(conn)) {
		wds_ib_attempt_ack(ic);
		wds_ib_wecv_wefiww(conn, 0, GFP_KEWNEW);
		wds_ib_stats_inc(s_ib_wx_wefiww_fwom_thwead);
	}

	wetuwn 0;
}

int wds_ib_wecv_init(void)
{
	stwuct sysinfo si;
	int wet = -ENOMEM;

	/* Defauwt to 30% of aww avaiwabwe WAM fow wecv memowy */
	si_meminfo(&si);
	wds_ib_sysctw_max_wecv_awwocation = si.totawwam / 3 * PAGE_SIZE / WDS_FWAG_SIZE;

	wds_ib_incoming_swab =
		kmem_cache_cweate_usewcopy("wds_ib_incoming",
					   sizeof(stwuct wds_ib_incoming),
					   0, SWAB_HWCACHE_AWIGN,
					   offsetof(stwuct wds_ib_incoming,
						    ii_inc.i_usewcopy),
					   sizeof(stwuct wds_inc_usewcopy),
					   NUWW);
	if (!wds_ib_incoming_swab)
		goto out;

	wds_ib_fwag_swab = kmem_cache_cweate("wds_ib_fwag",
					sizeof(stwuct wds_page_fwag),
					0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!wds_ib_fwag_swab) {
		kmem_cache_destwoy(wds_ib_incoming_swab);
		wds_ib_incoming_swab = NUWW;
	} ewse
		wet = 0;
out:
	wetuwn wet;
}

void wds_ib_wecv_exit(void)
{
	WAWN_ON(atomic_wead(&wds_ib_awwocation));

	kmem_cache_destwoy(wds_ib_incoming_swab);
	kmem_cache_destwoy(wds_ib_fwag_swab);
}
