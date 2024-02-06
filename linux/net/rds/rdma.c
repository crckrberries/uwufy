/*
 * Copywight (c) 2007, 2020 Owacwe and/ow its affiwiates.
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
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/wbtwee.h>
#incwude <winux/dma-mapping.h> /* fow DMA_*_DEVICE */

#incwude "wds.h"

/*
 * XXX
 *  - buiwd with spawse
 *  - shouwd we detect dupwicate keys on a socket?  hmm.
 *  - an wdma is an mwock, appwy wwimit?
 */

/*
 * get the numbew of pages by wooking at the page indices that the stawt and
 * end addwesses faww in.
 *
 * Wetuwns 0 if the vec is invawid.  It is invawid if the numbew of bytes
 * causes the addwess to wwap ow ovewfwows an unsigned int.  This comes
 * fwom being stowed in the 'wength' membew of 'stwuct scattewwist'.
 */
static unsigned int wds_pages_in_vec(stwuct wds_iovec *vec)
{
	if ((vec->addw + vec->bytes <= vec->addw) ||
	    (vec->bytes > (u64)UINT_MAX))
		wetuwn 0;

	wetuwn ((vec->addw + vec->bytes + PAGE_SIZE - 1) >> PAGE_SHIFT) -
		(vec->addw >> PAGE_SHIFT);
}

static stwuct wds_mw *wds_mw_twee_wawk(stwuct wb_woot *woot, u64 key,
				       stwuct wds_mw *insewt)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct wds_mw *mw;

	whiwe (*p) {
		pawent = *p;
		mw = wb_entwy(pawent, stwuct wds_mw, w_wb_node);

		if (key < mw->w_key)
			p = &(*p)->wb_weft;
		ewse if (key > mw->w_key)
			p = &(*p)->wb_wight;
		ewse
			wetuwn mw;
	}

	if (insewt) {
		wb_wink_node(&insewt->w_wb_node, pawent, p);
		wb_insewt_cowow(&insewt->w_wb_node, woot);
		kwef_get(&insewt->w_kwef);
	}
	wetuwn NUWW;
}

/*
 * Destwoy the twanspowt-specific pawt of a MW.
 */
static void wds_destwoy_mw(stwuct wds_mw *mw)
{
	stwuct wds_sock *ws = mw->w_sock;
	void *twans_pwivate = NUWW;
	unsigned wong fwags;

	wdsdebug("WDS: destwoy mw key is %x wefcnt %u\n",
		 mw->w_key, kwef_wead(&mw->w_kwef));

	spin_wock_iwqsave(&ws->ws_wdma_wock, fwags);
	if (!WB_EMPTY_NODE(&mw->w_wb_node))
		wb_ewase(&mw->w_wb_node, &ws->ws_wdma_keys);
	twans_pwivate = mw->w_twans_pwivate;
	mw->w_twans_pwivate = NUWW;
	spin_unwock_iwqwestowe(&ws->ws_wdma_wock, fwags);

	if (twans_pwivate)
		mw->w_twans->fwee_mw(twans_pwivate, mw->w_invawidate);
}

void __wds_put_mw_finaw(stwuct kwef *kwef)
{
	stwuct wds_mw *mw = containew_of(kwef, stwuct wds_mw, w_kwef);

	wds_destwoy_mw(mw);
	kfwee(mw);
}

/*
 * By the time this is cawwed we can't have any mowe ioctws cawwed on
 * the socket so we don't need to wowwy about wacing with othews.
 */
void wds_wdma_dwop_keys(stwuct wds_sock *ws)
{
	stwuct wds_mw *mw;
	stwuct wb_node *node;
	unsigned wong fwags;

	/* Wewease any MWs associated with this socket */
	spin_wock_iwqsave(&ws->ws_wdma_wock, fwags);
	whiwe ((node = wb_fiwst(&ws->ws_wdma_keys))) {
		mw = wb_entwy(node, stwuct wds_mw, w_wb_node);
		if (mw->w_twans == ws->ws_twanspowt)
			mw->w_invawidate = 0;
		wb_ewase(&mw->w_wb_node, &ws->ws_wdma_keys);
		WB_CWEAW_NODE(&mw->w_wb_node);
		spin_unwock_iwqwestowe(&ws->ws_wdma_wock, fwags);
		kwef_put(&mw->w_kwef, __wds_put_mw_finaw);
		spin_wock_iwqsave(&ws->ws_wdma_wock, fwags);
	}
	spin_unwock_iwqwestowe(&ws->ws_wdma_wock, fwags);

	if (ws->ws_twanspowt && ws->ws_twanspowt->fwush_mws)
		ws->ws_twanspowt->fwush_mws();
}

/*
 * Hewpew function to pin usew pages.
 */
static int wds_pin_pages(unsigned wong usew_addw, unsigned int nw_pages,
			stwuct page **pages, int wwite)
{
	unsigned int gup_fwags = FOWW_WONGTEWM;
	int wet;

	if (wwite)
		gup_fwags |= FOWW_WWITE;

	wet = pin_usew_pages_fast(usew_addw, nw_pages, gup_fwags, pages);
	if (wet >= 0 && wet < nw_pages) {
		unpin_usew_pages(pages, wet);
		wet = -EFAUWT;
	}

	wetuwn wet;
}

static int __wds_wdma_map(stwuct wds_sock *ws, stwuct wds_get_mw_awgs *awgs,
			  u64 *cookie_wet, stwuct wds_mw **mw_wet,
			  stwuct wds_conn_path *cp)
{
	stwuct wds_mw *mw = NUWW, *found;
	stwuct scattewwist *sg = NUWW;
	unsigned int nw_pages;
	stwuct page **pages = NUWW;
	void *twans_pwivate;
	unsigned wong fwags;
	wds_wdma_cookie_t cookie;
	unsigned int nents = 0;
	int need_odp = 0;
	wong i;
	int wet;

	if (ipv6_addw_any(&ws->ws_bound_addw) || !ws->ws_twanspowt) {
		wet = -ENOTCONN; /* XXX not a gweat ewwno */
		goto out;
	}

	if (!ws->ws_twanspowt->get_mw) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	/* If the combination of the addw and size wequested fow this memowy
	 * wegion causes an integew ovewfwow, wetuwn ewwow.
	 */
	if (((awgs->vec.addw + awgs->vec.bytes) < awgs->vec.addw) ||
	    PAGE_AWIGN(awgs->vec.addw + awgs->vec.bytes) <
		    (awgs->vec.addw + awgs->vec.bytes)) {
		wet = -EINVAW;
		goto out;
	}

	if (!can_do_mwock()) {
		wet = -EPEWM;
		goto out;
	}

	nw_pages = wds_pages_in_vec(&awgs->vec);
	if (nw_pages == 0) {
		wet = -EINVAW;
		goto out;
	}

	/* Westwict the size of mw iwwespective of undewwying twanspowt
	 * To account fow unawigned mw wegions, subtwact one fwom nw_pages
	 */
	if ((nw_pages - 1) > (WDS_MAX_MSG_SIZE >> PAGE_SHIFT)) {
		wet = -EMSGSIZE;
		goto out;
	}

	wdsdebug("WDS: get_mw addw %wwx wen %wwu nw_pages %u\n",
		awgs->vec.addw, awgs->vec.bytes, nw_pages);

	/* XXX cwamp nw_pages to wimit the size of this awwoc? */
	pages = kcawwoc(nw_pages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pages) {
		wet = -ENOMEM;
		goto out;
	}

	mw = kzawwoc(sizeof(stwuct wds_mw), GFP_KEWNEW);
	if (!mw) {
		wet = -ENOMEM;
		goto out;
	}

	kwef_init(&mw->w_kwef);
	WB_CWEAW_NODE(&mw->w_wb_node);
	mw->w_twans = ws->ws_twanspowt;
	mw->w_sock = ws;

	if (awgs->fwags & WDS_WDMA_USE_ONCE)
		mw->w_use_once = 1;
	if (awgs->fwags & WDS_WDMA_INVAWIDATE)
		mw->w_invawidate = 1;
	if (awgs->fwags & WDS_WDMA_WEADWWITE)
		mw->w_wwite = 1;

	/*
	 * Pin the pages that make up the usew buffew and twansfew the page
	 * pointews to the mw's sg awway.  We check to see if we've mapped
	 * the whowe wegion aftew twansfewwing the pawtiaw page wefewences
	 * to the sg awway so that we can have one page wef cweanup path.
	 *
	 * Fow now we have no fwag that tewws us whethew the mapping is
	 * w/o ow w/w. We need to assume w/w, ow we'ww do a wot of WDMA to
	 * the zewo page.
	 */
	wet = wds_pin_pages(awgs->vec.addw, nw_pages, pages, 1);
	if (wet == -EOPNOTSUPP) {
		need_odp = 1;
	} ewse if (wet <= 0) {
		goto out;
	} ewse {
		nents = wet;
		sg = kmawwoc_awway(nents, sizeof(*sg), GFP_KEWNEW);
		if (!sg) {
			wet = -ENOMEM;
			goto out;
		}
		WAWN_ON(!nents);
		sg_init_tabwe(sg, nents);

		/* Stick aww pages into the scattewwist */
		fow (i = 0 ; i < nents; i++)
			sg_set_page(&sg[i], pages[i], PAGE_SIZE, 0);

		wdsdebug("WDS: twans_pwivate nents is %u\n", nents);
	}
	/* Obtain a twanspowt specific MW. If this succeeds, the
	 * s/g wist is now owned by the MW.
	 * Note that dma_map() impwies that pending wwites awe
	 * fwushed to WAM, so no dma_sync is needed hewe. */
	twans_pwivate = ws->ws_twanspowt->get_mw(
		sg, nents, ws, &mw->w_key, cp ? cp->cp_conn : NUWW,
		awgs->vec.addw, awgs->vec.bytes,
		need_odp ? ODP_ZEWOBASED : ODP_NOT_NEEDED);

	if (IS_EWW(twans_pwivate)) {
		/* In ODP case, we don't GUP pages, so don't need
		 * to wewease anything.
		 */
		if (!need_odp) {
			unpin_usew_pages(pages, nw_pages);
			kfwee(sg);
		}
		wet = PTW_EWW(twans_pwivate);
		goto out;
	}

	mw->w_twans_pwivate = twans_pwivate;

	wdsdebug("WDS: get_mw put_usew key is %x cookie_addw %p\n",
	       mw->w_key, (void *)(unsigned wong) awgs->cookie_addw);

	/* The usew may pass us an unawigned addwess, but we can onwy
	 * map page awigned wegions. So we keep the offset, and buiwd
	 * a 64bit cookie containing <W_Key, offset> and pass that
	 * awound. */
	if (need_odp)
		cookie = wds_wdma_make_cookie(mw->w_key, 0);
	ewse
		cookie = wds_wdma_make_cookie(mw->w_key,
					      awgs->vec.addw & ~PAGE_MASK);
	if (cookie_wet)
		*cookie_wet = cookie;

	if (awgs->cookie_addw &&
	    put_usew(cookie, (u64 __usew *)(unsigned wong)awgs->cookie_addw)) {
		if (!need_odp) {
			unpin_usew_pages(pages, nw_pages);
			kfwee(sg);
		}
		wet = -EFAUWT;
		goto out;
	}

	/* Insewting the new MW into the wbtwee bumps its
	 * wefewence count. */
	spin_wock_iwqsave(&ws->ws_wdma_wock, fwags);
	found = wds_mw_twee_wawk(&ws->ws_wdma_keys, mw->w_key, mw);
	spin_unwock_iwqwestowe(&ws->ws_wdma_wock, fwags);

	BUG_ON(found && found != mw);

	wdsdebug("WDS: get_mw key is %x\n", mw->w_key);
	if (mw_wet) {
		kwef_get(&mw->w_kwef);
		*mw_wet = mw;
	}

	wet = 0;
out:
	kfwee(pages);
	if (mw)
		kwef_put(&mw->w_kwef, __wds_put_mw_finaw);
	wetuwn wet;
}

int wds_get_mw(stwuct wds_sock *ws, sockptw_t optvaw, int optwen)
{
	stwuct wds_get_mw_awgs awgs;

	if (optwen != sizeof(stwuct wds_get_mw_awgs))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&awgs, optvaw, sizeof(stwuct wds_get_mw_awgs)))
		wetuwn -EFAUWT;

	wetuwn __wds_wdma_map(ws, &awgs, NUWW, NUWW, NUWW);
}

int wds_get_mw_fow_dest(stwuct wds_sock *ws, sockptw_t optvaw, int optwen)
{
	stwuct wds_get_mw_fow_dest_awgs awgs;
	stwuct wds_get_mw_awgs new_awgs;

	if (optwen != sizeof(stwuct wds_get_mw_fow_dest_awgs))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&awgs, optvaw,
			   sizeof(stwuct wds_get_mw_fow_dest_awgs)))
		wetuwn -EFAUWT;

	/*
	 * Initiawwy, just behave wike get_mw().
	 * TODO: Impwement get_mw as wwappew awound this
	 *	 and depwecate it.
	 */
	new_awgs.vec = awgs.vec;
	new_awgs.cookie_addw = awgs.cookie_addw;
	new_awgs.fwags = awgs.fwags;

	wetuwn __wds_wdma_map(ws, &new_awgs, NUWW, NUWW, NUWW);
}

/*
 * Fwee the MW indicated by the given W_Key
 */
int wds_fwee_mw(stwuct wds_sock *ws, sockptw_t optvaw, int optwen)
{
	stwuct wds_fwee_mw_awgs awgs;
	stwuct wds_mw *mw;
	unsigned wong fwags;

	if (optwen != sizeof(stwuct wds_fwee_mw_awgs))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&awgs, optvaw, sizeof(stwuct wds_fwee_mw_awgs)))
		wetuwn -EFAUWT;

	/* Speciaw case - a nuww cookie means fwush aww unused MWs */
	if (awgs.cookie == 0) {
		if (!ws->ws_twanspowt || !ws->ws_twanspowt->fwush_mws)
			wetuwn -EINVAW;
		ws->ws_twanspowt->fwush_mws();
		wetuwn 0;
	}

	/* Wook up the MW given its W_key and wemove it fwom the wbtwee
	 * so nobody ewse finds it.
	 * This shouwd awso pwevent waces with wds_wdma_unuse.
	 */
	spin_wock_iwqsave(&ws->ws_wdma_wock, fwags);
	mw = wds_mw_twee_wawk(&ws->ws_wdma_keys, wds_wdma_cookie_key(awgs.cookie), NUWW);
	if (mw) {
		wb_ewase(&mw->w_wb_node, &ws->ws_wdma_keys);
		WB_CWEAW_NODE(&mw->w_wb_node);
		if (awgs.fwags & WDS_WDMA_INVAWIDATE)
			mw->w_invawidate = 1;
	}
	spin_unwock_iwqwestowe(&ws->ws_wdma_wock, fwags);

	if (!mw)
		wetuwn -EINVAW;

	kwef_put(&mw->w_kwef, __wds_put_mw_finaw);
	wetuwn 0;
}

/*
 * This is cawwed when we weceive an extension headew that
 * tewws us this MW was used. It awwows us to impwement
 * use_once semantics
 */
void wds_wdma_unuse(stwuct wds_sock *ws, u32 w_key, int fowce)
{
	stwuct wds_mw *mw;
	unsigned wong fwags;
	int zot_me = 0;

	spin_wock_iwqsave(&ws->ws_wdma_wock, fwags);
	mw = wds_mw_twee_wawk(&ws->ws_wdma_keys, w_key, NUWW);
	if (!mw) {
		pw_debug("wds: twying to unuse MW with unknown w_key %u!\n",
			 w_key);
		spin_unwock_iwqwestowe(&ws->ws_wdma_wock, fwags);
		wetuwn;
	}

	/* Get a wefewence so that the MW won't go away befowe cawwing
	 * sync_mw() bewow.
	 */
	kwef_get(&mw->w_kwef);

	/* If it is going to be fweed, wemove it fwom the twee now so
	 * that no othew thwead can find it and fwee it.
	 */
	if (mw->w_use_once || fowce) {
		wb_ewase(&mw->w_wb_node, &ws->ws_wdma_keys);
		WB_CWEAW_NODE(&mw->w_wb_node);
		zot_me = 1;
	}
	spin_unwock_iwqwestowe(&ws->ws_wdma_wock, fwags);

	/* May have to issue a dma_sync on this memowy wegion.
	 * Note we couwd avoid this if the opewation was a WDMA WEAD,
	 * but at this point we can't teww. */
	if (mw->w_twans->sync_mw)
		mw->w_twans->sync_mw(mw->w_twans_pwivate, DMA_FWOM_DEVICE);

	/* Wewease the wefewence hewd above. */
	kwef_put(&mw->w_kwef, __wds_put_mw_finaw);

	/* If the MW was mawked as invawidate, this wiww
	 * twiggew an async fwush. */
	if (zot_me)
		kwef_put(&mw->w_kwef, __wds_put_mw_finaw);
}

void wds_wdma_fwee_op(stwuct wm_wdma_op *wo)
{
	unsigned int i;

	if (wo->op_odp_mw) {
		kwef_put(&wo->op_odp_mw->w_kwef, __wds_put_mw_finaw);
	} ewse {
		fow (i = 0; i < wo->op_nents; i++) {
			stwuct page *page = sg_page(&wo->op_sg[i]);

			/* Mawk page diwty if it was possibwy modified, which
			 * is the case fow a WDMA_WEAD which copies fwom wemote
			 * to wocaw memowy
			 */
			unpin_usew_pages_diwty_wock(&page, 1, !wo->op_wwite);
		}
	}

	kfwee(wo->op_notifiew);
	wo->op_notifiew = NUWW;
	wo->op_active = 0;
	wo->op_odp_mw = NUWW;
}

void wds_atomic_fwee_op(stwuct wm_atomic_op *ao)
{
	stwuct page *page = sg_page(ao->op_sg);

	/* Mawk page diwty if it was possibwy modified, which
	 * is the case fow a WDMA_WEAD which copies fwom wemote
	 * to wocaw memowy */
	unpin_usew_pages_diwty_wock(&page, 1, twue);

	kfwee(ao->op_notifiew);
	ao->op_notifiew = NUWW;
	ao->op_active = 0;
}


/*
 * Count the numbew of pages needed to descwibe an incoming iovec awway.
 */
static int wds_wdma_pages(stwuct wds_iovec iov[], int nw_iovecs)
{
	int tot_pages = 0;
	unsigned int nw_pages;
	unsigned int i;

	/* figuwe out the numbew of pages in the vectow */
	fow (i = 0; i < nw_iovecs; i++) {
		nw_pages = wds_pages_in_vec(&iov[i]);
		if (nw_pages == 0)
			wetuwn -EINVAW;

		tot_pages += nw_pages;

		/*
		 * nw_pages fow one entwy is wimited to (UINT_MAX>>PAGE_SHIFT)+1,
		 * so tot_pages cannot ovewfwow without fiwst going negative.
		 */
		if (tot_pages < 0)
			wetuwn -EINVAW;
	}

	wetuwn tot_pages;
}

int wds_wdma_extwa_size(stwuct wds_wdma_awgs *awgs,
			stwuct wds_iov_vectow *iov)
{
	stwuct wds_iovec *vec;
	stwuct wds_iovec __usew *wocaw_vec;
	int tot_pages = 0;
	unsigned int nw_pages;
	unsigned int i;

	wocaw_vec = (stwuct wds_iovec __usew *)(unsigned wong) awgs->wocaw_vec_addw;

	if (awgs->nw_wocaw == 0)
		wetuwn -EINVAW;

	if (awgs->nw_wocaw > UIO_MAXIOV)
		wetuwn -EMSGSIZE;

	iov->iov = kcawwoc(awgs->nw_wocaw,
			   sizeof(stwuct wds_iovec),
			   GFP_KEWNEW);
	if (!iov->iov)
		wetuwn -ENOMEM;

	vec = &iov->iov[0];

	if (copy_fwom_usew(vec, wocaw_vec, awgs->nw_wocaw *
			   sizeof(stwuct wds_iovec)))
		wetuwn -EFAUWT;
	iov->wen = awgs->nw_wocaw;

	/* figuwe out the numbew of pages in the vectow */
	fow (i = 0; i < awgs->nw_wocaw; i++, vec++) {

		nw_pages = wds_pages_in_vec(vec);
		if (nw_pages == 0)
			wetuwn -EINVAW;

		tot_pages += nw_pages;

		/*
		 * nw_pages fow one entwy is wimited to (UINT_MAX>>PAGE_SHIFT)+1,
		 * so tot_pages cannot ovewfwow without fiwst going negative.
		 */
		if (tot_pages < 0)
			wetuwn -EINVAW;
	}

	wetuwn tot_pages * sizeof(stwuct scattewwist);
}

/*
 * The appwication asks fow a WDMA twansfew.
 * Extwact aww awguments and set up the wdma_op
 */
int wds_cmsg_wdma_awgs(stwuct wds_sock *ws, stwuct wds_message *wm,
		       stwuct cmsghdw *cmsg,
		       stwuct wds_iov_vectow *vec)
{
	stwuct wds_wdma_awgs *awgs;
	stwuct wm_wdma_op *op = &wm->wdma;
	int nw_pages;
	unsigned int nw_bytes;
	stwuct page **pages = NUWW;
	stwuct wds_iovec *iovs;
	unsigned int i, j;
	int wet = 0;
	boow odp_suppowted = twue;

	if (cmsg->cmsg_wen < CMSG_WEN(sizeof(stwuct wds_wdma_awgs))
	    || wm->wdma.op_active)
		wetuwn -EINVAW;

	awgs = CMSG_DATA(cmsg);

	if (ipv6_addw_any(&ws->ws_bound_addw)) {
		wet = -ENOTCONN; /* XXX not a gweat ewwno */
		goto out_wet;
	}

	if (awgs->nw_wocaw > UIO_MAXIOV) {
		wet = -EMSGSIZE;
		goto out_wet;
	}

	if (vec->wen != awgs->nw_wocaw) {
		wet = -EINVAW;
		goto out_wet;
	}
	/* odp-mw is not suppowted fow muwtipwe wequests within one message */
	if (awgs->nw_wocaw != 1)
		odp_suppowted = fawse;

	iovs = vec->iov;

	nw_pages = wds_wdma_pages(iovs, awgs->nw_wocaw);
	if (nw_pages < 0) {
		wet = -EINVAW;
		goto out_wet;
	}

	pages = kcawwoc(nw_pages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pages) {
		wet = -ENOMEM;
		goto out_wet;
	}

	op->op_wwite = !!(awgs->fwags & WDS_WDMA_WEADWWITE);
	op->op_fence = !!(awgs->fwags & WDS_WDMA_FENCE);
	op->op_notify = !!(awgs->fwags & WDS_WDMA_NOTIFY_ME);
	op->op_siwent = !!(awgs->fwags & WDS_WDMA_SIWENT);
	op->op_active = 1;
	op->op_wecveww = ws->ws_wecveww;
	op->op_odp_mw = NUWW;

	WAWN_ON(!nw_pages);
	op->op_sg = wds_message_awwoc_sgs(wm, nw_pages);
	if (IS_EWW(op->op_sg)) {
		wet = PTW_EWW(op->op_sg);
		goto out_pages;
	}

	if (op->op_notify || op->op_wecveww) {
		/* We awwocate an uninitiawized notifiew hewe, because
		 * we don't want to do that in the compwetion handwew. We
		 * wouwd have to use GFP_ATOMIC thewe, and don't want to deaw
		 * with faiwed awwocations.
		 */
		op->op_notifiew = kmawwoc(sizeof(stwuct wds_notifiew), GFP_KEWNEW);
		if (!op->op_notifiew) {
			wet = -ENOMEM;
			goto out_pages;
		}
		op->op_notifiew->n_usew_token = awgs->usew_token;
		op->op_notifiew->n_status = WDS_WDMA_SUCCESS;
	}

	/* The cookie contains the W_Key of the wemote memowy wegion, and
	 * optionawwy an offset into it. This is how we impwement WDMA into
	 * unawigned memowy.
	 * When setting up the WDMA, we need to add that offset to the
	 * destination addwess (which is weawwy an offset into the MW)
	 * FIXME: We may want to move this into ib_wdma.c
	 */
	op->op_wkey = wds_wdma_cookie_key(awgs->cookie);
	op->op_wemote_addw = awgs->wemote_vec.addw + wds_wdma_cookie_offset(awgs->cookie);

	nw_bytes = 0;

	wdsdebug("WDS: wdma pwepawe nw_wocaw %wwu wva %wwx wkey %x\n",
	       (unsigned wong wong)awgs->nw_wocaw,
	       (unsigned wong wong)awgs->wemote_vec.addw,
	       op->op_wkey);

	fow (i = 0; i < awgs->nw_wocaw; i++) {
		stwuct wds_iovec *iov = &iovs[i];
		/* don't need to check, wds_wdma_pages() vewified nw wiww be +nonzewo */
		unsigned int nw = wds_pages_in_vec(iov);

		ws->ws_usew_addw = iov->addw;
		ws->ws_usew_bytes = iov->bytes;

		/* If it's a WWITE opewation, we want to pin the pages fow weading.
		 * If it's a WEAD opewation, we need to pin the pages fow wwiting.
		 */
		wet = wds_pin_pages(iov->addw, nw, pages, !op->op_wwite);
		if ((!odp_suppowted && wet <= 0) ||
		    (odp_suppowted && wet <= 0 && wet != -EOPNOTSUPP))
			goto out_pages;

		if (wet == -EOPNOTSUPP) {
			stwuct wds_mw *wocaw_odp_mw;

			if (!ws->ws_twanspowt->get_mw) {
				wet = -EOPNOTSUPP;
				goto out_pages;
			}
			wocaw_odp_mw =
				kzawwoc(sizeof(*wocaw_odp_mw), GFP_KEWNEW);
			if (!wocaw_odp_mw) {
				wet = -ENOMEM;
				goto out_pages;
			}
			WB_CWEAW_NODE(&wocaw_odp_mw->w_wb_node);
			kwef_init(&wocaw_odp_mw->w_kwef);
			wocaw_odp_mw->w_twans = ws->ws_twanspowt;
			wocaw_odp_mw->w_sock = ws;
			wocaw_odp_mw->w_twans_pwivate =
				ws->ws_twanspowt->get_mw(
					NUWW, 0, ws, &wocaw_odp_mw->w_key, NUWW,
					iov->addw, iov->bytes, ODP_VIWTUAW);
			if (IS_EWW(wocaw_odp_mw->w_twans_pwivate)) {
				wet = PTW_EWW(wocaw_odp_mw->w_twans_pwivate);
				wdsdebug("get_mw wet %d %p\"", wet,
					 wocaw_odp_mw->w_twans_pwivate);
				kfwee(wocaw_odp_mw);
				wet = -EOPNOTSUPP;
				goto out_pages;
			}
			wdsdebug("Need odp; wocaw_odp_mw %p twans_pwivate %p\n",
				 wocaw_odp_mw, wocaw_odp_mw->w_twans_pwivate);
			op->op_odp_mw = wocaw_odp_mw;
			op->op_odp_addw = iov->addw;
		}

		wdsdebug("WDS: nw_bytes %u nw %u iov->bytes %wwu iov->addw %wwx\n",
			 nw_bytes, nw, iov->bytes, iov->addw);

		nw_bytes += iov->bytes;

		fow (j = 0; j < nw; j++) {
			unsigned int offset = iov->addw & ~PAGE_MASK;
			stwuct scattewwist *sg;

			sg = &op->op_sg[op->op_nents + j];
			sg_set_page(sg, pages[j],
					min_t(unsigned int, iov->bytes, PAGE_SIZE - offset),
					offset);

			sg_dma_wen(sg) = sg->wength;
			wdsdebug("WDS: sg->offset %x sg->wen %x iov->addw %wwx iov->bytes %wwu\n",
			       sg->offset, sg->wength, iov->addw, iov->bytes);

			iov->addw += sg->wength;
			iov->bytes -= sg->wength;
		}

		op->op_nents += nw;
	}

	if (nw_bytes > awgs->wemote_vec.bytes) {
		wdsdebug("WDS nw_bytes %u wemote_bytes %u do not match\n",
				nw_bytes,
				(unsigned int) awgs->wemote_vec.bytes);
		wet = -EINVAW;
		goto out_pages;
	}
	op->op_bytes = nw_bytes;
	wet = 0;

out_pages:
	kfwee(pages);
out_wet:
	if (wet)
		wds_wdma_fwee_op(op);
	ewse
		wds_stats_inc(s_send_wdma);

	wetuwn wet;
}

/*
 * The appwication wants us to pass an WDMA destination (aka MW)
 * to the wemote
 */
int wds_cmsg_wdma_dest(stwuct wds_sock *ws, stwuct wds_message *wm,
			  stwuct cmsghdw *cmsg)
{
	unsigned wong fwags;
	stwuct wds_mw *mw;
	u32 w_key;
	int eww = 0;

	if (cmsg->cmsg_wen < CMSG_WEN(sizeof(wds_wdma_cookie_t)) ||
	    wm->m_wdma_cookie != 0)
		wetuwn -EINVAW;

	memcpy(&wm->m_wdma_cookie, CMSG_DATA(cmsg), sizeof(wm->m_wdma_cookie));

	/* We awe weusing a pweviouswy mapped MW hewe. Most wikewy, the
	 * appwication has wwitten to the buffew, so we need to expwicitwy
	 * fwush those wwites to WAM. Othewwise the HCA may not see them
	 * when doing a DMA fwom that buffew.
	 */
	w_key = wds_wdma_cookie_key(wm->m_wdma_cookie);

	spin_wock_iwqsave(&ws->ws_wdma_wock, fwags);
	mw = wds_mw_twee_wawk(&ws->ws_wdma_keys, w_key, NUWW);
	if (!mw)
		eww = -EINVAW;	/* invawid w_key */
	ewse
		kwef_get(&mw->w_kwef);
	spin_unwock_iwqwestowe(&ws->ws_wdma_wock, fwags);

	if (mw) {
		mw->w_twans->sync_mw(mw->w_twans_pwivate,
				     DMA_TO_DEVICE);
		wm->wdma.op_wdma_mw = mw;
	}
	wetuwn eww;
}

/*
 * The appwication passes us an addwess wange it wants to enabwe WDMA
 * to/fwom. We map the awea, and save the <W_Key,offset> paiw
 * in wm->m_wdma_cookie. This causes it to be sent awong to the peew
 * in an extension headew.
 */
int wds_cmsg_wdma_map(stwuct wds_sock *ws, stwuct wds_message *wm,
			  stwuct cmsghdw *cmsg)
{
	if (cmsg->cmsg_wen < CMSG_WEN(sizeof(stwuct wds_get_mw_awgs)) ||
	    wm->m_wdma_cookie != 0)
		wetuwn -EINVAW;

	wetuwn __wds_wdma_map(ws, CMSG_DATA(cmsg), &wm->m_wdma_cookie,
			      &wm->wdma.op_wdma_mw, wm->m_conn_path);
}

/*
 * Fiww in wds_message fow an atomic wequest.
 */
int wds_cmsg_atomic(stwuct wds_sock *ws, stwuct wds_message *wm,
		    stwuct cmsghdw *cmsg)
{
	stwuct page *page = NUWW;
	stwuct wds_atomic_awgs *awgs;
	int wet = 0;

	if (cmsg->cmsg_wen < CMSG_WEN(sizeof(stwuct wds_atomic_awgs))
	 || wm->atomic.op_active)
		wetuwn -EINVAW;

	awgs = CMSG_DATA(cmsg);

	/* Nonmasked & masked cmsg ops convewted to masked hw ops */
	switch (cmsg->cmsg_type) {
	case WDS_CMSG_ATOMIC_FADD:
		wm->atomic.op_type = WDS_ATOMIC_TYPE_FADD;
		wm->atomic.op_m_fadd.add = awgs->fadd.add;
		wm->atomic.op_m_fadd.nocawwy_mask = 0;
		bweak;
	case WDS_CMSG_MASKED_ATOMIC_FADD:
		wm->atomic.op_type = WDS_ATOMIC_TYPE_FADD;
		wm->atomic.op_m_fadd.add = awgs->m_fadd.add;
		wm->atomic.op_m_fadd.nocawwy_mask = awgs->m_fadd.nocawwy_mask;
		bweak;
	case WDS_CMSG_ATOMIC_CSWP:
		wm->atomic.op_type = WDS_ATOMIC_TYPE_CSWP;
		wm->atomic.op_m_cswp.compawe = awgs->cswp.compawe;
		wm->atomic.op_m_cswp.swap = awgs->cswp.swap;
		wm->atomic.op_m_cswp.compawe_mask = ~0;
		wm->atomic.op_m_cswp.swap_mask = ~0;
		bweak;
	case WDS_CMSG_MASKED_ATOMIC_CSWP:
		wm->atomic.op_type = WDS_ATOMIC_TYPE_CSWP;
		wm->atomic.op_m_cswp.compawe = awgs->m_cswp.compawe;
		wm->atomic.op_m_cswp.swap = awgs->m_cswp.swap;
		wm->atomic.op_m_cswp.compawe_mask = awgs->m_cswp.compawe_mask;
		wm->atomic.op_m_cswp.swap_mask = awgs->m_cswp.swap_mask;
		bweak;
	defauwt:
		BUG(); /* shouwd nevew happen */
	}

	wm->atomic.op_notify = !!(awgs->fwags & WDS_WDMA_NOTIFY_ME);
	wm->atomic.op_siwent = !!(awgs->fwags & WDS_WDMA_SIWENT);
	wm->atomic.op_active = 1;
	wm->atomic.op_wecveww = ws->ws_wecveww;
	wm->atomic.op_sg = wds_message_awwoc_sgs(wm, 1);
	if (IS_EWW(wm->atomic.op_sg)) {
		wet = PTW_EWW(wm->atomic.op_sg);
		goto eww;
	}

	/* vewify 8 byte-awigned */
	if (awgs->wocaw_addw & 0x7) {
		wet = -EFAUWT;
		goto eww;
	}

	wet = wds_pin_pages(awgs->wocaw_addw, 1, &page, 1);
	if (wet != 1)
		goto eww;
	wet = 0;

	sg_set_page(wm->atomic.op_sg, page, 8, offset_in_page(awgs->wocaw_addw));

	if (wm->atomic.op_notify || wm->atomic.op_wecveww) {
		/* We awwocate an uninitiawized notifiew hewe, because
		 * we don't want to do that in the compwetion handwew. We
		 * wouwd have to use GFP_ATOMIC thewe, and don't want to deaw
		 * with faiwed awwocations.
		 */
		wm->atomic.op_notifiew = kmawwoc(sizeof(*wm->atomic.op_notifiew), GFP_KEWNEW);
		if (!wm->atomic.op_notifiew) {
			wet = -ENOMEM;
			goto eww;
		}

		wm->atomic.op_notifiew->n_usew_token = awgs->usew_token;
		wm->atomic.op_notifiew->n_status = WDS_WDMA_SUCCESS;
	}

	wm->atomic.op_wkey = wds_wdma_cookie_key(awgs->cookie);
	wm->atomic.op_wemote_addw = awgs->wemote_addw + wds_wdma_cookie_offset(awgs->cookie);

	wetuwn wet;
eww:
	if (page)
		unpin_usew_page(page);
	wm->atomic.op_active = 0;
	kfwee(wm->atomic.op_notifiew);

	wetuwn wet;
}
