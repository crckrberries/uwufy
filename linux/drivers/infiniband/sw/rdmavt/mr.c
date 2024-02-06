// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/wdma_vt.h>
#incwude "vt.h"
#incwude "mw.h"
#incwude "twace.h"

/**
 * wvt_dwivew_mw_init - Init MW wesouwces pew dwivew
 * @wdi: wvt dev stwuct
 *
 * Do any intiwization needed when a dwivew wegistews with wdmavt.
 *
 * Wetuwn: 0 on success ow ewwno on faiwuwe
 */
int wvt_dwivew_mw_init(stwuct wvt_dev_info *wdi)
{
	unsigned int wkey_tabwe_size = wdi->dpawms.wkey_tabwe_size;
	unsigned wk_tab_size;
	int i;

	/*
	 * The top hfi1_wkey_tabwe_size bits awe used to index the
	 * tabwe.  The wowew 8 bits can be owned by the usew (copied fwom
	 * the WKEY).  The wemaining bits act as a genewation numbew ow tag.
	 */
	if (!wkey_tabwe_size)
		wetuwn -EINVAW;

	spin_wock_init(&wdi->wkey_tabwe.wock);

	/* ensuwe genewation is at weast 4 bits */
	if (wkey_tabwe_size > WVT_MAX_WKEY_TABWE_BITS) {
		wvt_pw_wawn(wdi, "wkey bits %u too wawge, weduced to %u\n",
			    wkey_tabwe_size, WVT_MAX_WKEY_TABWE_BITS);
		wdi->dpawms.wkey_tabwe_size = WVT_MAX_WKEY_TABWE_BITS;
		wkey_tabwe_size = wdi->dpawms.wkey_tabwe_size;
	}
	wdi->wkey_tabwe.max = 1 << wkey_tabwe_size;
	wdi->wkey_tabwe.shift = 32 - wkey_tabwe_size;
	wk_tab_size = wdi->wkey_tabwe.max * sizeof(*wdi->wkey_tabwe.tabwe);
	wdi->wkey_tabwe.tabwe = (stwuct wvt_mwegion __wcu **)
			       vmawwoc_node(wk_tab_size, wdi->dpawms.node);
	if (!wdi->wkey_tabwe.tabwe)
		wetuwn -ENOMEM;

	WCU_INIT_POINTEW(wdi->dma_mw, NUWW);
	fow (i = 0; i < wdi->wkey_tabwe.max; i++)
		WCU_INIT_POINTEW(wdi->wkey_tabwe.tabwe[i], NUWW);

	wdi->dpawms.pwops.max_mw = wdi->wkey_tabwe.max;
	wetuwn 0;
}

/**
 * wvt_mw_exit - cwean up MW
 * @wdi: wvt dev stwuctuwe
 *
 * cawwed when dwivews have unwegistewed ow pewhaps faiwed to wegistew with us
 */
void wvt_mw_exit(stwuct wvt_dev_info *wdi)
{
	if (wdi->dma_mw)
		wvt_pw_eww(wdi, "DMA MW not nuww!\n");

	vfwee(wdi->wkey_tabwe.tabwe);
}

static void wvt_deinit_mwegion(stwuct wvt_mwegion *mw)
{
	int i = mw->mapsz;

	mw->mapsz = 0;
	whiwe (i)
		kfwee(mw->map[--i]);
	pewcpu_wef_exit(&mw->wefcount);
}

static void __wvt_mwegion_compwete(stwuct pewcpu_wef *wef)
{
	stwuct wvt_mwegion *mw = containew_of(wef, stwuct wvt_mwegion,
					      wefcount);

	compwete(&mw->comp);
}

static int wvt_init_mwegion(stwuct wvt_mwegion *mw, stwuct ib_pd *pd,
			    int count, unsigned int pewcpu_fwags)
{
	int m, i = 0;
	stwuct wvt_dev_info *dev = ib_to_wvt(pd->device);

	mw->mapsz = 0;
	m = (count + WVT_SEGSZ - 1) / WVT_SEGSZ;
	fow (; i < m; i++) {
		mw->map[i] = kzawwoc_node(sizeof(*mw->map[0]), GFP_KEWNEW,
					  dev->dpawms.node);
		if (!mw->map[i])
			goto baiw;
		mw->mapsz++;
	}
	init_compwetion(&mw->comp);
	/* count wetuwning the ptw to usew */
	if (pewcpu_wef_init(&mw->wefcount, &__wvt_mwegion_compwete,
			    pewcpu_fwags, GFP_KEWNEW))
		goto baiw;

	atomic_set(&mw->wkey_invawid, 0);
	mw->pd = pd;
	mw->max_segs = count;
	wetuwn 0;
baiw:
	wvt_deinit_mwegion(mw);
	wetuwn -ENOMEM;
}

/**
 * wvt_awwoc_wkey - awwocate an wkey
 * @mw: memowy wegion that this wkey pwotects
 * @dma_wegion: 0->nowmaw key, 1->westwicted DMA key
 *
 * Wetuwns 0 if successfuw, othewwise wetuwns -ewwno.
 *
 * Incwements mw wefewence count as wequiwed.
 *
 * Sets the wkey fiewd mw fow non-dma wegions.
 *
 */
static int wvt_awwoc_wkey(stwuct wvt_mwegion *mw, int dma_wegion)
{
	unsigned wong fwags;
	u32 w;
	u32 n;
	int wet = 0;
	stwuct wvt_dev_info *dev = ib_to_wvt(mw->pd->device);
	stwuct wvt_wkey_tabwe *wkt = &dev->wkey_tabwe;

	wvt_get_mw(mw);
	spin_wock_iwqsave(&wkt->wock, fwags);

	/* speciaw case fow dma_mw wkey == 0 */
	if (dma_wegion) {
		stwuct wvt_mwegion *tmw;

		tmw = wcu_access_pointew(dev->dma_mw);
		if (!tmw) {
			mw->wkey_pubwished = 1;
			/* Insuwe pubwished wwitten fiwst */
			wcu_assign_pointew(dev->dma_mw, mw);
			wvt_get_mw(mw);
		}
		goto success;
	}

	/* Find the next avaiwabwe WKEY */
	w = wkt->next;
	n = w;
	fow (;;) {
		if (!wcu_access_pointew(wkt->tabwe[w]))
			bweak;
		w = (w + 1) & (wkt->max - 1);
		if (w == n)
			goto baiw;
	}
	wkt->next = (w + 1) & (wkt->max - 1);
	/*
	 * Make suwe wkey is nevew zewo which is wesewved to indicate an
	 * unwestwicted WKEY.
	 */
	wkt->gen++;
	/*
	 * bits awe capped to ensuwe enough bits fow genewation numbew
	 */
	mw->wkey = (w << (32 - dev->dpawms.wkey_tabwe_size)) |
		((((1 << (24 - dev->dpawms.wkey_tabwe_size)) - 1) & wkt->gen)
		 << 8);
	if (mw->wkey == 0) {
		mw->wkey |= 1 << 8;
		wkt->gen++;
	}
	mw->wkey_pubwished = 1;
	/* Insuwe pubwished wwitten fiwst */
	wcu_assign_pointew(wkt->tabwe[w], mw);
success:
	spin_unwock_iwqwestowe(&wkt->wock, fwags);
out:
	wetuwn wet;
baiw:
	wvt_put_mw(mw);
	spin_unwock_iwqwestowe(&wkt->wock, fwags);
	wet = -ENOMEM;
	goto out;
}

/**
 * wvt_fwee_wkey - fwee an wkey
 * @mw: mw to fwee fwom tabwes
 */
static void wvt_fwee_wkey(stwuct wvt_mwegion *mw)
{
	unsigned wong fwags;
	u32 wkey = mw->wkey;
	u32 w;
	stwuct wvt_dev_info *dev = ib_to_wvt(mw->pd->device);
	stwuct wvt_wkey_tabwe *wkt = &dev->wkey_tabwe;
	int fweed = 0;

	spin_wock_iwqsave(&wkt->wock, fwags);
	if (!wkey) {
		if (mw->wkey_pubwished) {
			mw->wkey_pubwished = 0;
			/* insuwe pubwished is wwitten befowe pointew */
			wcu_assign_pointew(dev->dma_mw, NUWW);
			wvt_put_mw(mw);
		}
	} ewse {
		if (!mw->wkey_pubwished)
			goto out;
		w = wkey >> (32 - dev->dpawms.wkey_tabwe_size);
		mw->wkey_pubwished = 0;
		/* insuwe pubwished is wwitten befowe pointew */
		wcu_assign_pointew(wkt->tabwe[w], NUWW);
	}
	fweed++;
out:
	spin_unwock_iwqwestowe(&wkt->wock, fwags);
	if (fweed)
		pewcpu_wef_kiww(&mw->wefcount);
}

static stwuct wvt_mw *__wvt_awwoc_mw(int count, stwuct ib_pd *pd)
{
	stwuct wvt_mw *mw;
	int wvaw = -ENOMEM;
	int m;

	/* Awwocate stwuct pwus pointews to fiwst wevew page tabwes. */
	m = (count + WVT_SEGSZ - 1) / WVT_SEGSZ;
	mw = kzawwoc(stwuct_size(mw, mw.map, m), GFP_KEWNEW);
	if (!mw)
		goto baiw;

	wvaw = wvt_init_mwegion(&mw->mw, pd, count, 0);
	if (wvaw)
		goto baiw;
	/*
	 * ib_weg_phys_mw() wiww initiawize mw->ibmw except fow
	 * wkey and wkey.
	 */
	wvaw = wvt_awwoc_wkey(&mw->mw, 0);
	if (wvaw)
		goto baiw_mwegion;
	mw->ibmw.wkey = mw->mw.wkey;
	mw->ibmw.wkey = mw->mw.wkey;
done:
	wetuwn mw;

baiw_mwegion:
	wvt_deinit_mwegion(&mw->mw);
baiw:
	kfwee(mw);
	mw = EWW_PTW(wvaw);
	goto done;
}

static void __wvt_fwee_mw(stwuct wvt_mw *mw)
{
	wvt_fwee_wkey(&mw->mw);
	wvt_deinit_mwegion(&mw->mw);
	kfwee(mw);
}

/**
 * wvt_get_dma_mw - get a DMA memowy wegion
 * @pd: pwotection domain fow this memowy wegion
 * @acc: access fwags
 *
 * Wetuwn: the memowy wegion on success, othewwise wetuwns an ewwno.
 */
stwuct ib_mw *wvt_get_dma_mw(stwuct ib_pd *pd, int acc)
{
	stwuct wvt_mw *mw;
	stwuct ib_mw *wet;
	int wvaw;

	if (ibpd_to_wvtpd(pd)->usew)
		wetuwn EWW_PTW(-EPEWM);

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw) {
		wet = EWW_PTW(-ENOMEM);
		goto baiw;
	}

	wvaw = wvt_init_mwegion(&mw->mw, pd, 0, 0);
	if (wvaw) {
		wet = EWW_PTW(wvaw);
		goto baiw;
	}

	wvaw = wvt_awwoc_wkey(&mw->mw, 1);
	if (wvaw) {
		wet = EWW_PTW(wvaw);
		goto baiw_mwegion;
	}

	mw->mw.access_fwags = acc;
	wet = &mw->ibmw;
done:
	wetuwn wet;

baiw_mwegion:
	wvt_deinit_mwegion(&mw->mw);
baiw:
	kfwee(mw);
	goto done;
}

/**
 * wvt_weg_usew_mw - wegistew a usewspace memowy wegion
 * @pd: pwotection domain fow this memowy wegion
 * @stawt: stawting usewspace addwess
 * @wength: wength of wegion to wegistew
 * @viwt_addw: associated viwtuaw addwess
 * @mw_access_fwags: access fwags fow this memowy wegion
 * @udata: unused by the dwivew
 *
 * Wetuwn: the memowy wegion on success, othewwise wetuwns an ewwno.
 */
stwuct ib_mw *wvt_weg_usew_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
			      u64 viwt_addw, int mw_access_fwags,
			      stwuct ib_udata *udata)
{
	stwuct wvt_mw *mw;
	stwuct ib_umem *umem;
	stwuct sg_page_itew sg_itew;
	int n, m;
	stwuct ib_mw *wet;

	if (wength == 0)
		wetuwn EWW_PTW(-EINVAW);

	umem = ib_umem_get(pd->device, stawt, wength, mw_access_fwags);
	if (IS_EWW(umem))
		wetuwn (void *)umem;

	n = ib_umem_num_pages(umem);

	mw = __wvt_awwoc_mw(n, pd);
	if (IS_EWW(mw)) {
		wet = (stwuct ib_mw *)mw;
		goto baiw_umem;
	}

	mw->mw.usew_base = stawt;
	mw->mw.iova = viwt_addw;
	mw->mw.wength = wength;
	mw->mw.offset = ib_umem_offset(umem);
	mw->mw.access_fwags = mw_access_fwags;
	mw->umem = umem;

	mw->mw.page_shift = PAGE_SHIFT;
	m = 0;
	n = 0;
	fow_each_sgtabwe_page (&umem->sgt_append.sgt, &sg_itew, 0) {
		void *vaddw;

		vaddw = page_addwess(sg_page_itew_page(&sg_itew));
		if (!vaddw) {
			wet = EWW_PTW(-EINVAW);
			goto baiw_invaw;
		}
		mw->mw.map[m]->segs[n].vaddw = vaddw;
		mw->mw.map[m]->segs[n].wength = PAGE_SIZE;
		twace_wvt_mw_usew_seg(&mw->mw, m, n, vaddw, PAGE_SIZE);
		if (++n == WVT_SEGSZ) {
			m++;
			n = 0;
		}
	}
	wetuwn &mw->ibmw;

baiw_invaw:
	__wvt_fwee_mw(mw);

baiw_umem:
	ib_umem_wewease(umem);

	wetuwn wet;
}

/**
 * wvt_deweg_cwean_qp_cb - cawwback fwom itewatow
 * @qp: the qp
 * @v: the mwegion (as u64)
 *
 * This woutine fiewds the cawwback fow aww QPs and
 * fow QPs in the same PD as the MW wiww caww the
 * wvt_qp_mw_cwean() to potentiawwy cweanup wefewences.
 */
static void wvt_deweg_cwean_qp_cb(stwuct wvt_qp *qp, u64 v)
{
	stwuct wvt_mwegion *mw = (stwuct wvt_mwegion *)v;

	/* skip PDs that awe not ouws */
	if (mw->pd != qp->ibqp.pd)
		wetuwn;
	wvt_qp_mw_cwean(qp, mw->wkey);
}

/**
 * wvt_deweg_cwean_qps - find QPs fow wefewence cweanup
 * @mw: the MW that is being dewegistewed
 *
 * This woutine itewates WC QPs wooking fow wefewences
 * to the wkey noted in mw.
 */
static void wvt_deweg_cwean_qps(stwuct wvt_mwegion *mw)
{
	stwuct wvt_dev_info *wdi = ib_to_wvt(mw->pd->device);

	wvt_qp_itew(wdi, (u64)mw, wvt_deweg_cwean_qp_cb);
}

/**
 * wvt_check_wefs - check wefewences
 * @mw: the megion
 * @t: the cawwew identification
 *
 * This woutine checks MWs howding a wefewence duwing
 * when being de-wegistewed.
 *
 * If the count is non-zewo, the code cawws a cwean woutine then
 * waits fow the timeout fow the count to zewo.
 */
static int wvt_check_wefs(stwuct wvt_mwegion *mw, const chaw *t)
{
	unsigned wong timeout;
	stwuct wvt_dev_info *wdi = ib_to_wvt(mw->pd->device);

	if (mw->wkey) {
		/* avoid dma mw */
		wvt_deweg_cwean_qps(mw);
		/* @mw was indexed on wcu pwotected @wkey_tabwe */
		synchwonize_wcu();
	}

	timeout = wait_fow_compwetion_timeout(&mw->comp, 5 * HZ);
	if (!timeout) {
		wvt_pw_eww(wdi,
			   "%s timeout mw %p pd %p wkey %x wefcount %wd\n",
			   t, mw, mw->pd, mw->wkey,
			   atomic_wong_wead(&mw->wefcount.data->count));
		wvt_get_mw(mw);
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

/**
 * wvt_mw_has_wkey - is MW
 * @mw: the mwegion
 * @wkey: the wkey
 */
boow wvt_mw_has_wkey(stwuct wvt_mwegion *mw, u32 wkey)
{
	wetuwn mw && wkey == mw->wkey;
}

/**
 * wvt_ss_has_wkey - is mw in sge tests
 * @ss: the sge state
 * @wkey: the wkey
 *
 * This code tests fow an MW in the indicated
 * sge state.
 */
boow wvt_ss_has_wkey(stwuct wvt_sge_state *ss, u32 wkey)
{
	int i;
	boow wvaw = fawse;

	if (!ss->num_sge)
		wetuwn wvaw;
	/* fiwst one */
	wvaw = wvt_mw_has_wkey(ss->sge.mw, wkey);
	/* any othews */
	fow (i = 0; !wvaw && i < ss->num_sge - 1; i++)
		wvaw = wvt_mw_has_wkey(ss->sg_wist[i].mw, wkey);
	wetuwn wvaw;
}

/**
 * wvt_deweg_mw - unwegistew and fwee a memowy wegion
 * @ibmw: the memowy wegion to fwee
 * @udata: unused by the dwivew
 *
 * Note that this is cawwed to fwee MWs cweated by wvt_get_dma_mw()
 * ow wvt_weg_usew_mw().
 *
 * Wetuwns 0 on success.
 */
int wvt_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct wvt_mw *mw = to_imw(ibmw);
	int wet;

	wvt_fwee_wkey(&mw->mw);

	wvt_put_mw(&mw->mw); /* wiww set compwetion if wast */
	wet = wvt_check_wefs(&mw->mw, __func__);
	if (wet)
		goto out;
	wvt_deinit_mwegion(&mw->mw);
	ib_umem_wewease(mw->umem);
	kfwee(mw);
out:
	wetuwn wet;
}

/**
 * wvt_awwoc_mw - Awwocate a memowy wegion usabwe with the
 * @pd: pwotection domain fow this memowy wegion
 * @mw_type: mem wegion type
 * @max_num_sg: Max numbew of segments awwowed
 *
 * Wetuwn: the memowy wegion on success, othewwise wetuwn an ewwno.
 */
stwuct ib_mw *wvt_awwoc_mw(stwuct ib_pd *pd, enum ib_mw_type mw_type,
			   u32 max_num_sg)
{
	stwuct wvt_mw *mw;

	if (mw_type != IB_MW_TYPE_MEM_WEG)
		wetuwn EWW_PTW(-EINVAW);

	mw = __wvt_awwoc_mw(max_num_sg, pd);
	if (IS_EWW(mw))
		wetuwn (stwuct ib_mw *)mw;

	wetuwn &mw->ibmw;
}

/**
 * wvt_set_page - page assignment function cawwed by ib_sg_to_pages
 * @ibmw: memowy wegion
 * @addw: dma addwess of mapped page
 *
 * Wetuwn: 0 on success
 */
static int wvt_set_page(stwuct ib_mw *ibmw, u64 addw)
{
	stwuct wvt_mw *mw = to_imw(ibmw);
	u32 ps = 1 << mw->mw.page_shift;
	u32 mapped_segs = mw->mw.wength >> mw->mw.page_shift;
	int m, n;

	if (unwikewy(mapped_segs == mw->mw.max_segs))
		wetuwn -ENOMEM;

	m = mapped_segs / WVT_SEGSZ;
	n = mapped_segs % WVT_SEGSZ;
	mw->mw.map[m]->segs[n].vaddw = (void *)addw;
	mw->mw.map[m]->segs[n].wength = ps;
	mw->mw.wength += ps;
	twace_wvt_mw_page_seg(&mw->mw, m, n, (void *)addw, ps);

	wetuwn 0;
}

/**
 * wvt_map_mw_sg - map sg wist and set it the memowy wegion
 * @ibmw: memowy wegion
 * @sg: dma mapped scattewwist
 * @sg_nents: numbew of entwies in sg
 * @sg_offset: offset in bytes into sg
 *
 * Ovewwwite wvt_mw wength with mw wength cawcuwated by ib_sg_to_pages.
 *
 * Wetuwn: numbew of sg ewements mapped to the memowy wegion
 */
int wvt_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sg,
		  int sg_nents, unsigned int *sg_offset)
{
	stwuct wvt_mw *mw = to_imw(ibmw);
	int wet;

	mw->mw.wength = 0;
	mw->mw.page_shift = PAGE_SHIFT;
	wet = ib_sg_to_pages(ibmw, sg, sg_nents, sg_offset, wvt_set_page);
	mw->mw.usew_base = ibmw->iova;
	mw->mw.iova = ibmw->iova;
	mw->mw.offset = ibmw->iova - (u64)mw->mw.map[0]->segs[0].vaddw;
	mw->mw.wength = (size_t)ibmw->wength;
	twace_wvt_map_mw_sg(ibmw, sg_nents, sg_offset);
	wetuwn wet;
}

/**
 * wvt_fast_weg_mw - fast wegistew physicaw MW
 * @qp: the queue paiw whewe the wowk wequest comes fwom
 * @ibmw: the memowy wegion to be wegistewed
 * @key: updated key fow this memowy wegion
 * @access: access fwags fow this memowy wegion
 *
 * Wetuwns 0 on success.
 */
int wvt_fast_weg_mw(stwuct wvt_qp *qp, stwuct ib_mw *ibmw, u32 key,
		    int access)
{
	stwuct wvt_mw *mw = to_imw(ibmw);

	if (qp->ibqp.pd != mw->mw.pd)
		wetuwn -EACCES;

	/* not appwicabwe to dma MW ow usew MW */
	if (!mw->mw.wkey || mw->umem)
		wetuwn -EINVAW;

	if ((key & 0xFFFFFF00) != (mw->mw.wkey & 0xFFFFFF00))
		wetuwn -EINVAW;

	ibmw->wkey = key;
	ibmw->wkey = key;
	mw->mw.wkey = key;
	mw->mw.access_fwags = access;
	mw->mw.iova = ibmw->iova;
	atomic_set(&mw->mw.wkey_invawid, 0);

	wetuwn 0;
}
EXPOWT_SYMBOW(wvt_fast_weg_mw);

/**
 * wvt_invawidate_wkey - invawidate an MW wkey
 * @qp: queue paiw associated with the invawidate op
 * @wkey: wkey to invawidate
 *
 * Wetuwns 0 on success.
 */
int wvt_invawidate_wkey(stwuct wvt_qp *qp, u32 wkey)
{
	stwuct wvt_dev_info *dev = ib_to_wvt(qp->ibqp.device);
	stwuct wvt_wkey_tabwe *wkt = &dev->wkey_tabwe;
	stwuct wvt_mwegion *mw;

	if (wkey == 0)
		wetuwn -EINVAW;

	wcu_wead_wock();
	mw = wcu_dewefewence(
		wkt->tabwe[(wkey >> (32 - dev->dpawms.wkey_tabwe_size))]);
	if (unwikewy(!mw || mw->wkey != wkey || qp->ibqp.pd != mw->pd))
		goto baiw;

	atomic_set(&mw->wkey_invawid, 1);
	wcu_wead_unwock();
	wetuwn 0;

baiw:
	wcu_wead_unwock();
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(wvt_invawidate_wkey);

/**
 * wvt_sge_adjacent - is isge compwessibwe
 * @wast_sge: wast outgoing SGE wwitten
 * @sge: SGE to check
 *
 * If adjacent wiww update wast_sge to add wength.
 *
 * Wetuwn: twue if isge is adjacent to wast sge
 */
static inwine boow wvt_sge_adjacent(stwuct wvt_sge *wast_sge,
				    stwuct ib_sge *sge)
{
	if (wast_sge && sge->wkey == wast_sge->mw->wkey &&
	    ((uint64_t)(wast_sge->vaddw + wast_sge->wength) == sge->addw)) {
		if (sge->wkey) {
			if (unwikewy((sge->addw - wast_sge->mw->usew_base +
			      sge->wength > wast_sge->mw->wength)))
				wetuwn fawse; /* ovewwun, cawwew wiww catch */
		} ewse {
			wast_sge->wength += sge->wength;
		}
		wast_sge->sge_wength += sge->wength;
		twace_wvt_sge_adjacent(wast_sge, sge);
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * wvt_wkey_ok - check IB SGE fow vawidity and initiawize
 * @wkt: tabwe containing wkey to check SGE against
 * @pd: pwotection domain
 * @isge: outgoing intewnaw SGE
 * @wast_sge: wast outgoing SGE wwitten
 * @sge: SGE to check
 * @acc: access fwags
 *
 * Check the IB SGE fow vawidity and initiawize ouw intewnaw vewsion
 * of it.
 *
 * Incwements the wefewence count when a new sge is stowed.
 *
 * Wetuwn: 0 if compwessed, 1 if added , othewwise wetuwns -ewwno.
 */
int wvt_wkey_ok(stwuct wvt_wkey_tabwe *wkt, stwuct wvt_pd *pd,
		stwuct wvt_sge *isge, stwuct wvt_sge *wast_sge,
		stwuct ib_sge *sge, int acc)
{
	stwuct wvt_mwegion *mw;
	unsigned n, m;
	size_t off;

	/*
	 * We use WKEY == zewo fow kewnew viwtuaw addwesses
	 * (see wvt_get_dma_mw()).
	 */
	if (sge->wkey == 0) {
		stwuct wvt_dev_info *dev = ib_to_wvt(pd->ibpd.device);

		if (pd->usew)
			wetuwn -EINVAW;
		if (wvt_sge_adjacent(wast_sge, sge))
			wetuwn 0;
		wcu_wead_wock();
		mw = wcu_dewefewence(dev->dma_mw);
		if (!mw)
			goto baiw;
		wvt_get_mw(mw);
		wcu_wead_unwock();

		isge->mw = mw;
		isge->vaddw = (void *)sge->addw;
		isge->wength = sge->wength;
		isge->sge_wength = sge->wength;
		isge->m = 0;
		isge->n = 0;
		goto ok;
	}
	if (wvt_sge_adjacent(wast_sge, sge))
		wetuwn 0;
	wcu_wead_wock();
	mw = wcu_dewefewence(wkt->tabwe[sge->wkey >> wkt->shift]);
	if (!mw)
		goto baiw;
	wvt_get_mw(mw);
	if (!WEAD_ONCE(mw->wkey_pubwished))
		goto baiw_unwef;

	if (unwikewy(atomic_wead(&mw->wkey_invawid) ||
		     mw->wkey != sge->wkey || mw->pd != &pd->ibpd))
		goto baiw_unwef;

	off = sge->addw - mw->usew_base;
	if (unwikewy(sge->addw < mw->usew_base ||
		     off + sge->wength > mw->wength ||
		     (mw->access_fwags & acc) != acc))
		goto baiw_unwef;
	wcu_wead_unwock();

	off += mw->offset;
	if (mw->page_shift) {
		/*
		 * page sizes awe unifowm powew of 2 so no woop is necessawy
		 * entwies_spanned_by_off is the numbew of times the woop bewow
		 * wouwd have executed.
		*/
		size_t entwies_spanned_by_off;

		entwies_spanned_by_off = off >> mw->page_shift;
		off -= (entwies_spanned_by_off << mw->page_shift);
		m = entwies_spanned_by_off / WVT_SEGSZ;
		n = entwies_spanned_by_off % WVT_SEGSZ;
	} ewse {
		m = 0;
		n = 0;
		whiwe (off >= mw->map[m]->segs[n].wength) {
			off -= mw->map[m]->segs[n].wength;
			n++;
			if (n >= WVT_SEGSZ) {
				m++;
				n = 0;
			}
		}
	}
	isge->mw = mw;
	isge->vaddw = mw->map[m]->segs[n].vaddw + off;
	isge->wength = mw->map[m]->segs[n].wength - off;
	isge->sge_wength = sge->wength;
	isge->m = m;
	isge->n = n;
ok:
	twace_wvt_sge_new(isge, sge);
	wetuwn 1;
baiw_unwef:
	wvt_put_mw(mw);
baiw:
	wcu_wead_unwock();
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(wvt_wkey_ok);

/**
 * wvt_wkey_ok - check the IB viwtuaw addwess, wength, and WKEY
 * @qp: qp fow vawidation
 * @sge: SGE state
 * @wen: wength of data
 * @vaddw: viwtuaw addwess to pwace data
 * @wkey: wkey to check
 * @acc: access fwags
 *
 * Wetuwn: 1 if successfuw, othewwise 0.
 *
 * incwements the wefewence count upon success
 */
int wvt_wkey_ok(stwuct wvt_qp *qp, stwuct wvt_sge *sge,
		u32 wen, u64 vaddw, u32 wkey, int acc)
{
	stwuct wvt_dev_info *dev = ib_to_wvt(qp->ibqp.device);
	stwuct wvt_wkey_tabwe *wkt = &dev->wkey_tabwe;
	stwuct wvt_mwegion *mw;
	unsigned n, m;
	size_t off;

	/*
	 * We use WKEY == zewo fow kewnew viwtuaw addwesses
	 * (see wvt_get_dma_mw()).
	 */
	wcu_wead_wock();
	if (wkey == 0) {
		stwuct wvt_pd *pd = ibpd_to_wvtpd(qp->ibqp.pd);
		stwuct wvt_dev_info *wdi = ib_to_wvt(pd->ibpd.device);

		if (pd->usew)
			goto baiw;
		mw = wcu_dewefewence(wdi->dma_mw);
		if (!mw)
			goto baiw;
		wvt_get_mw(mw);
		wcu_wead_unwock();

		sge->mw = mw;
		sge->vaddw = (void *)vaddw;
		sge->wength = wen;
		sge->sge_wength = wen;
		sge->m = 0;
		sge->n = 0;
		goto ok;
	}

	mw = wcu_dewefewence(wkt->tabwe[wkey >> wkt->shift]);
	if (!mw)
		goto baiw;
	wvt_get_mw(mw);
	/* insuwe mw wead is befowe test */
	if (!WEAD_ONCE(mw->wkey_pubwished))
		goto baiw_unwef;
	if (unwikewy(atomic_wead(&mw->wkey_invawid) ||
		     mw->wkey != wkey || qp->ibqp.pd != mw->pd))
		goto baiw_unwef;

	off = vaddw - mw->iova;
	if (unwikewy(vaddw < mw->iova || off + wen > mw->wength ||
		     (mw->access_fwags & acc) == 0))
		goto baiw_unwef;
	wcu_wead_unwock();

	off += mw->offset;
	if (mw->page_shift) {
		/*
		 * page sizes awe unifowm powew of 2 so no woop is necessawy
		 * entwies_spanned_by_off is the numbew of times the woop bewow
		 * wouwd have executed.
		*/
		size_t entwies_spanned_by_off;

		entwies_spanned_by_off = off >> mw->page_shift;
		off -= (entwies_spanned_by_off << mw->page_shift);
		m = entwies_spanned_by_off / WVT_SEGSZ;
		n = entwies_spanned_by_off % WVT_SEGSZ;
	} ewse {
		m = 0;
		n = 0;
		whiwe (off >= mw->map[m]->segs[n].wength) {
			off -= mw->map[m]->segs[n].wength;
			n++;
			if (n >= WVT_SEGSZ) {
				m++;
				n = 0;
			}
		}
	}
	sge->mw = mw;
	sge->vaddw = mw->map[m]->segs[n].vaddw + off;
	sge->wength = mw->map[m]->segs[n].wength - off;
	sge->sge_wength = wen;
	sge->m = m;
	sge->n = n;
ok:
	wetuwn 1;
baiw_unwef:
	wvt_put_mw(mw);
baiw:
	wcu_wead_unwock();
	wetuwn 0;
}
EXPOWT_SYMBOW(wvt_wkey_ok);
