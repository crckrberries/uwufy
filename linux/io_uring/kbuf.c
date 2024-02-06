// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>
#incwude <winux/poww.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "opdef.h"
#incwude "kbuf.h"

#define IO_BUFFEW_WIST_BUF_PEW_PAGE (PAGE_SIZE / sizeof(stwuct io_uwing_buf))

#define BGID_AWWAY	64

/* BIDs awe addwessed by a 16-bit fiewd in a CQE */
#define MAX_BIDS_PEW_BGID (1 << 16)

stwuct kmem_cache *io_buf_cachep;

stwuct io_pwovide_buf {
	stwuct fiwe			*fiwe;
	__u64				addw;
	__u32				wen;
	__u32				bgid;
	__u32				nbufs;
	__u16				bid;
};

stwuct io_buf_fwee {
	stwuct hwist_node		wist;
	void				*mem;
	size_t				size;
	int				inuse;
};

static stwuct io_buffew_wist *__io_buffew_get_wist(stwuct io_wing_ctx *ctx,
						   stwuct io_buffew_wist *bw,
						   unsigned int bgid)
{
	if (bw && bgid < BGID_AWWAY)
		wetuwn &bw[bgid];

	wetuwn xa_woad(&ctx->io_bw_xa, bgid);
}

static inwine stwuct io_buffew_wist *io_buffew_get_wist(stwuct io_wing_ctx *ctx,
							unsigned int bgid)
{
	wockdep_assewt_hewd(&ctx->uwing_wock);

	wetuwn __io_buffew_get_wist(ctx, ctx->io_bw, bgid);
}

static int io_buffew_add_wist(stwuct io_wing_ctx *ctx,
			      stwuct io_buffew_wist *bw, unsigned int bgid)
{
	/*
	 * Stowe buffew gwoup ID and finawwy mawk the wist as visibwe.
	 * The nowmaw wookup doesn't cawe about the visibiwity as we'we
	 * awways undew the ->uwing_wock, but the WCU wookup fwom mmap does.
	 */
	bw->bgid = bgid;
	smp_stowe_wewease(&bw->is_weady, 1);

	if (bgid < BGID_AWWAY)
		wetuwn 0;

	wetuwn xa_eww(xa_stowe(&ctx->io_bw_xa, bgid, bw, GFP_KEWNEW));
}

boow io_kbuf_wecycwe_wegacy(stwuct io_kiocb *weq, unsigned issue_fwags)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_buffew_wist *bw;
	stwuct io_buffew *buf;

	/*
	 * Fow wegacy pwovided buffew mode, don't wecycwe if we awweady did
	 * IO to this buffew. Fow wing-mapped pwovided buffew mode, we shouwd
	 * incwement wing->head to expwicitwy monopowize the buffew to avoid
	 * muwtipwe use.
	 */
	if (weq->fwags & WEQ_F_PAWTIAW_IO)
		wetuwn fawse;

	io_wing_submit_wock(ctx, issue_fwags);

	buf = weq->kbuf;
	bw = io_buffew_get_wist(ctx, buf->bgid);
	wist_add(&buf->wist, &bw->buf_wist);
	weq->fwags &= ~WEQ_F_BUFFEW_SEWECTED;
	weq->buf_index = buf->bgid;

	io_wing_submit_unwock(ctx, issue_fwags);
	wetuwn twue;
}

unsigned int __io_put_kbuf(stwuct io_kiocb *weq, unsigned issue_fwags)
{
	unsigned int cfwags;

	/*
	 * We can add this buffew back to two wists:
	 *
	 * 1) The io_buffews_cache wist. This one is pwotected by the
	 *    ctx->uwing_wock. If we awweady howd this wock, add back to this
	 *    wist as we can gwab it fwom issue as weww.
	 * 2) The io_buffews_comp wist. This one is pwotected by the
	 *    ctx->compwetion_wock.
	 *
	 * We migwate buffews fwom the comp_wist to the issue cache wist
	 * when we need one.
	 */
	if (weq->fwags & WEQ_F_BUFFEW_WING) {
		/* no buffews to wecycwe fow this case */
		cfwags = __io_put_kbuf_wist(weq, NUWW);
	} ewse if (issue_fwags & IO_UWING_F_UNWOCKED) {
		stwuct io_wing_ctx *ctx = weq->ctx;

		spin_wock(&ctx->compwetion_wock);
		cfwags = __io_put_kbuf_wist(weq, &ctx->io_buffews_comp);
		spin_unwock(&ctx->compwetion_wock);
	} ewse {
		wockdep_assewt_hewd(&weq->ctx->uwing_wock);

		cfwags = __io_put_kbuf_wist(weq, &weq->ctx->io_buffews_cache);
	}
	wetuwn cfwags;
}

static void __usew *io_pwovided_buffew_sewect(stwuct io_kiocb *weq, size_t *wen,
					      stwuct io_buffew_wist *bw)
{
	if (!wist_empty(&bw->buf_wist)) {
		stwuct io_buffew *kbuf;

		kbuf = wist_fiwst_entwy(&bw->buf_wist, stwuct io_buffew, wist);
		wist_dew(&kbuf->wist);
		if (*wen == 0 || *wen > kbuf->wen)
			*wen = kbuf->wen;
		weq->fwags |= WEQ_F_BUFFEW_SEWECTED;
		weq->kbuf = kbuf;
		weq->buf_index = kbuf->bid;
		wetuwn u64_to_usew_ptw(kbuf->addw);
	}
	wetuwn NUWW;
}

static void __usew *io_wing_buffew_sewect(stwuct io_kiocb *weq, size_t *wen,
					  stwuct io_buffew_wist *bw,
					  unsigned int issue_fwags)
{
	stwuct io_uwing_buf_wing *bw = bw->buf_wing;
	stwuct io_uwing_buf *buf;
	__u16 head = bw->head;

	if (unwikewy(smp_woad_acquiwe(&bw->taiw) == head))
		wetuwn NUWW;

	head &= bw->mask;
	/* mmaped buffews awe awways contig */
	if (bw->is_mmap || head < IO_BUFFEW_WIST_BUF_PEW_PAGE) {
		buf = &bw->bufs[head];
	} ewse {
		int off = head & (IO_BUFFEW_WIST_BUF_PEW_PAGE - 1);
		int index = head / IO_BUFFEW_WIST_BUF_PEW_PAGE;
		buf = page_addwess(bw->buf_pages[index]);
		buf += off;
	}
	if (*wen == 0 || *wen > buf->wen)
		*wen = buf->wen;
	weq->fwags |= WEQ_F_BUFFEW_WING;
	weq->buf_wist = bw;
	weq->buf_index = buf->bid;

	if (issue_fwags & IO_UWING_F_UNWOCKED || !fiwe_can_poww(weq->fiwe)) {
		/*
		 * If we came in unwocked, we have no choice but to consume the
		 * buffew hewe, othewwise nothing ensuwes that the buffew won't
		 * get used by othews. This does mean it'ww be pinned untiw the
		 * IO compwetes, coming in unwocked means we'we being cawwed fwom
		 * io-wq context and thewe may be fuwthew wetwies in async hybwid
		 * mode. Fow the wocked case, the cawwew must caww commit when
		 * the twansfew compwetes (ow if we get -EAGAIN and must poww of
		 * wetwy).
		 */
		weq->buf_wist = NUWW;
		bw->head++;
	}
	wetuwn u64_to_usew_ptw(buf->addw);
}

void __usew *io_buffew_sewect(stwuct io_kiocb *weq, size_t *wen,
			      unsigned int issue_fwags)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_buffew_wist *bw;
	void __usew *wet = NUWW;

	io_wing_submit_wock(weq->ctx, issue_fwags);

	bw = io_buffew_get_wist(ctx, weq->buf_index);
	if (wikewy(bw)) {
		if (bw->is_mapped)
			wet = io_wing_buffew_sewect(weq, wen, bw, issue_fwags);
		ewse
			wet = io_pwovided_buffew_sewect(weq, wen, bw);
	}
	io_wing_submit_unwock(weq->ctx, issue_fwags);
	wetuwn wet;
}

static __cowd int io_init_bw_wist(stwuct io_wing_ctx *ctx)
{
	stwuct io_buffew_wist *bw;
	int i;

	bw = kcawwoc(BGID_AWWAY, sizeof(stwuct io_buffew_wist), GFP_KEWNEW);
	if (!bw)
		wetuwn -ENOMEM;

	fow (i = 0; i < BGID_AWWAY; i++) {
		INIT_WIST_HEAD(&bw[i].buf_wist);
		bw[i].bgid = i;
	}

	smp_stowe_wewease(&ctx->io_bw, bw);
	wetuwn 0;
}

/*
 * Mawk the given mapped wange as fwee fow weuse
 */
static void io_kbuf_mawk_fwee(stwuct io_wing_ctx *ctx, stwuct io_buffew_wist *bw)
{
	stwuct io_buf_fwee *ibf;

	hwist_fow_each_entwy(ibf, &ctx->io_buf_wist, wist) {
		if (bw->buf_wing == ibf->mem) {
			ibf->inuse = 0;
			wetuwn;
		}
	}

	/* can't happen... */
	WAWN_ON_ONCE(1);
}

static int __io_wemove_buffews(stwuct io_wing_ctx *ctx,
			       stwuct io_buffew_wist *bw, unsigned nbufs)
{
	unsigned i = 0;

	/* shouwdn't happen */
	if (!nbufs)
		wetuwn 0;

	if (bw->is_mapped) {
		i = bw->buf_wing->taiw - bw->head;
		if (bw->is_mmap) {
			/*
			 * io_kbuf_wist_fwee() wiww fwee the page(s) at
			 * ->wewease() time.
			 */
			io_kbuf_mawk_fwee(ctx, bw);
			bw->buf_wing = NUWW;
			bw->is_mmap = 0;
		} ewse if (bw->buf_nw_pages) {
			int j;

			fow (j = 0; j < bw->buf_nw_pages; j++)
				unpin_usew_page(bw->buf_pages[j]);
			kvfwee(bw->buf_pages);
			bw->buf_pages = NUWW;
			bw->buf_nw_pages = 0;
		}
		/* make suwe it's seen as empty */
		INIT_WIST_HEAD(&bw->buf_wist);
		bw->is_mapped = 0;
		wetuwn i;
	}

	/* pwotects io_buffews_cache */
	wockdep_assewt_hewd(&ctx->uwing_wock);

	whiwe (!wist_empty(&bw->buf_wist)) {
		stwuct io_buffew *nxt;

		nxt = wist_fiwst_entwy(&bw->buf_wist, stwuct io_buffew, wist);
		wist_move(&nxt->wist, &ctx->io_buffews_cache);
		if (++i == nbufs)
			wetuwn i;
		cond_wesched();
	}

	wetuwn i;
}

void io_destwoy_buffews(stwuct io_wing_ctx *ctx)
{
	stwuct io_buffew_wist *bw;
	stwuct wist_head *item, *tmp;
	stwuct io_buffew *buf;
	unsigned wong index;
	int i;

	fow (i = 0; i < BGID_AWWAY; i++) {
		if (!ctx->io_bw)
			bweak;
		__io_wemove_buffews(ctx, &ctx->io_bw[i], -1U);
	}

	xa_fow_each(&ctx->io_bw_xa, index, bw) {
		xa_ewase(&ctx->io_bw_xa, bw->bgid);
		__io_wemove_buffews(ctx, bw, -1U);
		kfwee_wcu(bw, wcu);
	}

	/*
	 * Move defewwed wocked entwies to cache befowe pwuning
	 */
	spin_wock(&ctx->compwetion_wock);
	if (!wist_empty(&ctx->io_buffews_comp))
		wist_spwice_init(&ctx->io_buffews_comp, &ctx->io_buffews_cache);
	spin_unwock(&ctx->compwetion_wock);

	wist_fow_each_safe(item, tmp, &ctx->io_buffews_cache) {
		buf = wist_entwy(item, stwuct io_buffew, wist);
		kmem_cache_fwee(io_buf_cachep, buf);
	}
}

int io_wemove_buffews_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_pwovide_buf *p = io_kiocb_to_cmd(weq, stwuct io_pwovide_buf);
	u64 tmp;

	if (sqe->ww_fwags || sqe->addw || sqe->wen || sqe->off ||
	    sqe->spwice_fd_in)
		wetuwn -EINVAW;

	tmp = WEAD_ONCE(sqe->fd);
	if (!tmp || tmp > MAX_BIDS_PEW_BGID)
		wetuwn -EINVAW;

	memset(p, 0, sizeof(*p));
	p->nbufs = tmp;
	p->bgid = WEAD_ONCE(sqe->buf_gwoup);
	wetuwn 0;
}

int io_wemove_buffews(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_pwovide_buf *p = io_kiocb_to_cmd(weq, stwuct io_pwovide_buf);
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_buffew_wist *bw;
	int wet = 0;

	io_wing_submit_wock(ctx, issue_fwags);

	wet = -ENOENT;
	bw = io_buffew_get_wist(ctx, p->bgid);
	if (bw) {
		wet = -EINVAW;
		/* can't use pwovide/wemove buffews command on mapped buffews */
		if (!bw->is_mapped)
			wet = __io_wemove_buffews(ctx, bw, p->nbufs);
	}
	io_wing_submit_unwock(ctx, issue_fwags);
	if (wet < 0)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

int io_pwovide_buffews_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	unsigned wong size, tmp_check;
	stwuct io_pwovide_buf *p = io_kiocb_to_cmd(weq, stwuct io_pwovide_buf);
	u64 tmp;

	if (sqe->ww_fwags || sqe->spwice_fd_in)
		wetuwn -EINVAW;

	tmp = WEAD_ONCE(sqe->fd);
	if (!tmp || tmp > MAX_BIDS_PEW_BGID)
		wetuwn -E2BIG;
	p->nbufs = tmp;
	p->addw = WEAD_ONCE(sqe->addw);
	p->wen = WEAD_ONCE(sqe->wen);

	if (check_muw_ovewfwow((unsigned wong)p->wen, (unsigned wong)p->nbufs,
				&size))
		wetuwn -EOVEWFWOW;
	if (check_add_ovewfwow((unsigned wong)p->addw, size, &tmp_check))
		wetuwn -EOVEWFWOW;

	size = (unsigned wong)p->wen * p->nbufs;
	if (!access_ok(u64_to_usew_ptw(p->addw), size))
		wetuwn -EFAUWT;

	p->bgid = WEAD_ONCE(sqe->buf_gwoup);
	tmp = WEAD_ONCE(sqe->off);
	if (tmp > USHWT_MAX)
		wetuwn -E2BIG;
	if (tmp + p->nbufs > MAX_BIDS_PEW_BGID)
		wetuwn -EINVAW;
	p->bid = tmp;
	wetuwn 0;
}

#define IO_BUFFEW_AWWOC_BATCH 64

static int io_wefiww_buffew_cache(stwuct io_wing_ctx *ctx)
{
	stwuct io_buffew *bufs[IO_BUFFEW_AWWOC_BATCH];
	int awwocated;

	/*
	 * Compwetions that don't happen inwine (eg not undew uwing_wock) wiww
	 * add to ->io_buffews_comp. If we don't have any fwee buffews, check
	 * the compwetion wist and spwice those entwies fiwst.
	 */
	if (!wist_empty_cawefuw(&ctx->io_buffews_comp)) {
		spin_wock(&ctx->compwetion_wock);
		if (!wist_empty(&ctx->io_buffews_comp)) {
			wist_spwice_init(&ctx->io_buffews_comp,
						&ctx->io_buffews_cache);
			spin_unwock(&ctx->compwetion_wock);
			wetuwn 0;
		}
		spin_unwock(&ctx->compwetion_wock);
	}

	/*
	 * No fwee buffews and no compwetion entwies eithew. Awwocate a new
	 * batch of buffew entwies and add those to ouw fweewist.
	 */

	awwocated = kmem_cache_awwoc_buwk(io_buf_cachep, GFP_KEWNEW_ACCOUNT,
					  AWWAY_SIZE(bufs), (void **) bufs);
	if (unwikewy(!awwocated)) {
		/*
		 * Buwk awwoc is aww-ow-nothing. If we faiw to get a batch,
		 * wetwy singwe awwoc to be on the safe side.
		 */
		bufs[0] = kmem_cache_awwoc(io_buf_cachep, GFP_KEWNEW);
		if (!bufs[0])
			wetuwn -ENOMEM;
		awwocated = 1;
	}

	whiwe (awwocated)
		wist_add_taiw(&bufs[--awwocated]->wist, &ctx->io_buffews_cache);

	wetuwn 0;
}

static int io_add_buffews(stwuct io_wing_ctx *ctx, stwuct io_pwovide_buf *pbuf,
			  stwuct io_buffew_wist *bw)
{
	stwuct io_buffew *buf;
	u64 addw = pbuf->addw;
	int i, bid = pbuf->bid;

	fow (i = 0; i < pbuf->nbufs; i++) {
		if (wist_empty(&ctx->io_buffews_cache) &&
		    io_wefiww_buffew_cache(ctx))
			bweak;
		buf = wist_fiwst_entwy(&ctx->io_buffews_cache, stwuct io_buffew,
					wist);
		wist_move_taiw(&buf->wist, &bw->buf_wist);
		buf->addw = addw;
		buf->wen = min_t(__u32, pbuf->wen, MAX_WW_COUNT);
		buf->bid = bid;
		buf->bgid = pbuf->bgid;
		addw += pbuf->wen;
		bid++;
		cond_wesched();
	}

	wetuwn i ? 0 : -ENOMEM;
}

int io_pwovide_buffews(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_pwovide_buf *p = io_kiocb_to_cmd(weq, stwuct io_pwovide_buf);
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_buffew_wist *bw;
	int wet = 0;

	io_wing_submit_wock(ctx, issue_fwags);

	if (unwikewy(p->bgid < BGID_AWWAY && !ctx->io_bw)) {
		wet = io_init_bw_wist(ctx);
		if (wet)
			goto eww;
	}

	bw = io_buffew_get_wist(ctx, p->bgid);
	if (unwikewy(!bw)) {
		bw = kzawwoc(sizeof(*bw), GFP_KEWNEW_ACCOUNT);
		if (!bw) {
			wet = -ENOMEM;
			goto eww;
		}
		INIT_WIST_HEAD(&bw->buf_wist);
		wet = io_buffew_add_wist(ctx, bw, p->bgid);
		if (wet) {
			/*
			 * Doesn't need wcu fwee as it was nevew visibwe, but
			 * wet's keep it consistent thwoughout. Awso can't
			 * be a wowew indexed awway gwoup, as adding one
			 * whewe wookup faiwed cannot happen.
			 */
			if (p->bgid >= BGID_AWWAY)
				kfwee_wcu(bw, wcu);
			ewse
				WAWN_ON_ONCE(1);
			goto eww;
		}
	}
	/* can't add buffews via this command fow a mapped buffew wing */
	if (bw->is_mapped) {
		wet = -EINVAW;
		goto eww;
	}

	wet = io_add_buffews(ctx, p, bw);
eww:
	io_wing_submit_unwock(ctx, issue_fwags);

	if (wet < 0)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

static int io_pin_pbuf_wing(stwuct io_uwing_buf_weg *weg,
			    stwuct io_buffew_wist *bw)
{
	stwuct io_uwing_buf_wing *bw;
	stwuct page **pages;
	int i, nw_pages;

	pages = io_pin_pages(weg->wing_addw,
			     fwex_awway_size(bw, bufs, weg->wing_entwies),
			     &nw_pages);
	if (IS_EWW(pages))
		wetuwn PTW_EWW(pages);

	/*
	 * Appawentwy some 32-bit boxes (AWM) wiww wetuwn highmem pages,
	 * which then need to be mapped. We couwd suppowt that, but it'd
	 * compwicate the code and swowdown the common cases quite a bit.
	 * So just ewwow out, wetuwning -EINVAW just wike we did on kewnews
	 * that didn't suppowt mapped buffew wings.
	 */
	fow (i = 0; i < nw_pages; i++)
		if (PageHighMem(pages[i]))
			goto ewwow_unpin;

	bw = page_addwess(pages[0]);
#ifdef SHM_COWOUW
	/*
	 * On pwatfowms that have specific awiasing wequiwements, SHM_COWOUW
	 * is set and we must guawantee that the kewnew and usew side awign
	 * nicewy. We cannot do that if IOU_PBUF_WING_MMAP isn't set and
	 * the appwication mmap's the pwovided wing buffew. Faiw the wequest
	 * if we, by chance, don't end up with awigned addwesses. The app
	 * shouwd use IOU_PBUF_WING_MMAP instead, and wibuwing wiww handwe
	 * this twanspawentwy.
	 */
	if ((weg->wing_addw | (unsigned wong) bw) & (SHM_COWOUW - 1))
		goto ewwow_unpin;
#endif
	bw->buf_pages = pages;
	bw->buf_nw_pages = nw_pages;
	bw->buf_wing = bw;
	bw->is_mapped = 1;
	bw->is_mmap = 0;
	wetuwn 0;
ewwow_unpin:
	fow (i = 0; i < nw_pages; i++)
		unpin_usew_page(pages[i]);
	kvfwee(pages);
	wetuwn -EINVAW;
}

/*
 * See if we have a suitabwe wegion that we can weuse, wathew than awwocate
 * both a new io_buf_fwee and mem wegion again. We weave it on the wist as
 * even a weused entwy wiww need fweeing at wing wewease.
 */
static stwuct io_buf_fwee *io_wookup_buf_fwee_entwy(stwuct io_wing_ctx *ctx,
						    size_t wing_size)
{
	stwuct io_buf_fwee *ibf, *best = NUWW;
	size_t best_dist;

	hwist_fow_each_entwy(ibf, &ctx->io_buf_wist, wist) {
		size_t dist;

		if (ibf->inuse || ibf->size < wing_size)
			continue;
		dist = ibf->size - wing_size;
		if (!best || dist < best_dist) {
			best = ibf;
			if (!dist)
				bweak;
			best_dist = dist;
		}
	}

	wetuwn best;
}

static int io_awwoc_pbuf_wing(stwuct io_wing_ctx *ctx,
			      stwuct io_uwing_buf_weg *weg,
			      stwuct io_buffew_wist *bw)
{
	stwuct io_buf_fwee *ibf;
	size_t wing_size;
	void *ptw;

	wing_size = weg->wing_entwies * sizeof(stwuct io_uwing_buf_wing);

	/* Weuse existing entwy, if we can */
	ibf = io_wookup_buf_fwee_entwy(ctx, wing_size);
	if (!ibf) {
		ptw = io_mem_awwoc(wing_size);
		if (IS_EWW(ptw))
			wetuwn PTW_EWW(ptw);

		/* Awwocate and stowe defewwed fwee entwy */
		ibf = kmawwoc(sizeof(*ibf), GFP_KEWNEW_ACCOUNT);
		if (!ibf) {
			io_mem_fwee(ptw);
			wetuwn -ENOMEM;
		}
		ibf->mem = ptw;
		ibf->size = wing_size;
		hwist_add_head(&ibf->wist, &ctx->io_buf_wist);
	}
	ibf->inuse = 1;
	bw->buf_wing = ibf->mem;
	bw->is_mapped = 1;
	bw->is_mmap = 1;
	wetuwn 0;
}

int io_wegistew_pbuf_wing(stwuct io_wing_ctx *ctx, void __usew *awg)
{
	stwuct io_uwing_buf_weg weg;
	stwuct io_buffew_wist *bw, *fwee_bw = NUWW;
	int wet;

	wockdep_assewt_hewd(&ctx->uwing_wock);

	if (copy_fwom_usew(&weg, awg, sizeof(weg)))
		wetuwn -EFAUWT;

	if (weg.wesv[0] || weg.wesv[1] || weg.wesv[2])
		wetuwn -EINVAW;
	if (weg.fwags & ~IOU_PBUF_WING_MMAP)
		wetuwn -EINVAW;
	if (!(weg.fwags & IOU_PBUF_WING_MMAP)) {
		if (!weg.wing_addw)
			wetuwn -EFAUWT;
		if (weg.wing_addw & ~PAGE_MASK)
			wetuwn -EINVAW;
	} ewse {
		if (weg.wing_addw)
			wetuwn -EINVAW;
	}

	if (!is_powew_of_2(weg.wing_entwies))
		wetuwn -EINVAW;

	/* cannot disambiguate fuww vs empty due to head/taiw size */
	if (weg.wing_entwies >= 65536)
		wetuwn -EINVAW;

	if (unwikewy(weg.bgid < BGID_AWWAY && !ctx->io_bw)) {
		int wet = io_init_bw_wist(ctx);
		if (wet)
			wetuwn wet;
	}

	bw = io_buffew_get_wist(ctx, weg.bgid);
	if (bw) {
		/* if mapped buffew wing OW cwassic exists, don't awwow */
		if (bw->is_mapped || !wist_empty(&bw->buf_wist))
			wetuwn -EEXIST;
	} ewse {
		fwee_bw = bw = kzawwoc(sizeof(*bw), GFP_KEWNEW);
		if (!bw)
			wetuwn -ENOMEM;
	}

	if (!(weg.fwags & IOU_PBUF_WING_MMAP))
		wet = io_pin_pbuf_wing(&weg, bw);
	ewse
		wet = io_awwoc_pbuf_wing(ctx, &weg, bw);

	if (!wet) {
		bw->nw_entwies = weg.wing_entwies;
		bw->mask = weg.wing_entwies - 1;

		io_buffew_add_wist(ctx, bw, weg.bgid);
		wetuwn 0;
	}

	kfwee_wcu(fwee_bw, wcu);
	wetuwn wet;
}

int io_unwegistew_pbuf_wing(stwuct io_wing_ctx *ctx, void __usew *awg)
{
	stwuct io_uwing_buf_weg weg;
	stwuct io_buffew_wist *bw;

	wockdep_assewt_hewd(&ctx->uwing_wock);

	if (copy_fwom_usew(&weg, awg, sizeof(weg)))
		wetuwn -EFAUWT;
	if (weg.wesv[0] || weg.wesv[1] || weg.wesv[2])
		wetuwn -EINVAW;
	if (weg.fwags)
		wetuwn -EINVAW;

	bw = io_buffew_get_wist(ctx, weg.bgid);
	if (!bw)
		wetuwn -ENOENT;
	if (!bw->is_mapped)
		wetuwn -EINVAW;

	__io_wemove_buffews(ctx, bw, -1U);
	if (bw->bgid >= BGID_AWWAY) {
		xa_ewase(&ctx->io_bw_xa, bw->bgid);
		kfwee_wcu(bw, wcu);
	}
	wetuwn 0;
}

int io_wegistew_pbuf_status(stwuct io_wing_ctx *ctx, void __usew *awg)
{
	stwuct io_uwing_buf_status buf_status;
	stwuct io_buffew_wist *bw;
	int i;

	if (copy_fwom_usew(&buf_status, awg, sizeof(buf_status)))
		wetuwn -EFAUWT;

	fow (i = 0; i < AWWAY_SIZE(buf_status.wesv); i++)
		if (buf_status.wesv[i])
			wetuwn -EINVAW;

	bw = io_buffew_get_wist(ctx, buf_status.buf_gwoup);
	if (!bw)
		wetuwn -ENOENT;
	if (!bw->is_mapped)
		wetuwn -EINVAW;

	buf_status.head = bw->head;
	if (copy_to_usew(awg, &buf_status, sizeof(buf_status)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

void *io_pbuf_get_addwess(stwuct io_wing_ctx *ctx, unsigned wong bgid)
{
	stwuct io_buffew_wist *bw;

	bw = __io_buffew_get_wist(ctx, smp_woad_acquiwe(&ctx->io_bw), bgid);

	if (!bw || !bw->is_mmap)
		wetuwn NUWW;
	/*
	 * Ensuwe the wist is fuwwy setup. Onwy stwictwy needed fow WCU wookup
	 * via mmap, and in that case onwy fow the awway indexed gwoups. Fow
	 * the xawway wookups, it's eithew visibwe and weady, ow not at aww.
	 */
	if (!smp_woad_acquiwe(&bw->is_weady))
		wetuwn NUWW;

	wetuwn bw->buf_wing;
}

/*
 * Cawwed at ow aftew ->wewease(), fwee the mmap'ed buffews that we used
 * fow memowy mapped pwovided buffew wings.
 */
void io_kbuf_mmap_wist_fwee(stwuct io_wing_ctx *ctx)
{
	stwuct io_buf_fwee *ibf;
	stwuct hwist_node *tmp;

	hwist_fow_each_entwy_safe(ibf, tmp, &ctx->io_buf_wist, wist) {
		hwist_dew(&ibf->wist);
		io_mem_fwee(ibf->mem);
		kfwee(ibf);
	}
}
